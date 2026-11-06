#include "FFAvio.h"
#include <cerrno>
#include <cstdio>
#include <new>

extern "C" {
#include <libavformat/avio.h>
#include <libavutil/error.h>
#include <libavutil/mem.h>
}

using namespace cocos2d::io;
using namespace ffmpeg;

namespace
{
	int toAvError(StreamError error)
	{
		switch (error.code)
		{
		case ErrorCode::NotSupported: return AVERROR(ENOSYS);
		case ErrorCode::InvalidArgument:
		case ErrorCode::OutOfRange: return AVERROR(EINVAL);
		case ErrorCode::Overflow: return AVERROR(EOVERFLOW);
		case ErrorCode::OutOfMemory: return AVERROR(ENOMEM);
		case ErrorCode::Cancelled: return AVERROR_EXIT;
		case ErrorCode::Timeout: return AVERROR(ETIMEDOUT);
		default: return AVERROR(EIO);
		}
	}

	int readStatus(const IoResult& result)
	{
		switch (result.status)
		{
		case IoStatus::Ok: return result.transferred ? 0 : AVERROR(EIO);
		case IoStatus::EndOfStream: return AVERROR_EOF;
		// Probing and playback in this adapter require synchronous input.
		case IoStatus::WouldBlock: return AVERROR(ENOSYS);
		case IoStatus::Cancelled: return AVERROR_EXIT;
		case IoStatus::Timeout: return AVERROR(ETIMEDOUT);
		case IoStatus::Error: return toAvError(result.error);
		}
		return AVERROR(EIO);
	}
}

AvioInput::AvioInput(StreamPtr input) : source(std::move(input)) {}

std::unique_ptr<AvioInput> AvioInput::create(StreamPtr source)
{
	if (!source || !source->isOpen() || !hasCapability(source->capabilities(), Capability::Read))
		return nullptr;
	const auto position = source->tell();
	if (!position || position.value != 0)
		return nullptr;

	auto input = std::unique_ptr<AvioInput>(new (std::nothrow) AvioInput(std::move(source)));
	if (!input)
		return nullptr;
	constexpr int bufferSize = 32 * 1024;
	auto buffer = static_cast<uint8_t*>(av_malloc(bufferSize));
	if (!buffer)
		return nullptr;
	input->context = avio_alloc_context(buffer, bufferSize, 0, input.get(), read, nullptr, seek);
	if (!input->context)
	{
		av_free(buffer);
		return nullptr;
	}
	// Even a sequential source can report a known length through AVSEEK_SIZE.
	input->context->seekable = hasCapability(input->source->capabilities(), Capability::Seek)
		? AVIO_SEEKABLE_NORMAL : 0;
	return input;
}

AvioInput::~AvioInput()
{
	if (context)
	{
		av_freep(&context->buffer);
		avio_context_free(&context);
	}
}

int AvioInput::readError() const
{
	return terminalRead == AVERROR_EOF ? 0 : terminalRead;
}

int AvioInput::read(void* opaque, uint8_t* buffer, int length) noexcept
{
	auto& input = *static_cast<AvioInput*>(opaque);
	if (input.terminalRead)
		return input.terminalRead;
	if (length <= 0)
		return AVERROR(EINVAL);
	try
	{
		const auto result = input.source->read(buffer, static_cast<size_t>(length));
		if (result.transferred > static_cast<size_t>(length))
			return input.terminalRead = AVERROR(EIO);
		input.terminalRead = readStatus(result);
		return result.transferred ? static_cast<int>(result.transferred) : input.terminalRead;
	}
	catch (const std::bad_alloc&) { return input.terminalRead = AVERROR(ENOMEM); }
	catch (...) { return input.terminalRead = AVERROR(EIO); }
}

int64_t AvioInput::seek(void* opaque, int64_t offset, int whence) noexcept
{
	auto& input = *static_cast<AvioInput*>(opaque);
	whence &= ~AVSEEK_FORCE;
	try
	{
		if (whence == AVSEEK_SIZE)
		{
			const auto size = input.source->size();
			if (!size)
				return toAvError(size.error);
			return size.value && *size.value >= 0 ? *size.value : AVERROR(ENOSYS);
		}
		if (!input.context->seekable)
			return AVERROR(ESPIPE);
		if (const auto error = input.readError())
			return error;

		SeekOrigin origin;
		switch (whence)
		{
		case SEEK_SET: origin = SeekOrigin::Begin; break;
		case SEEK_CUR: origin = SeekOrigin::Current; break;
		case SEEK_END: origin = SeekOrigin::End; break;
		default: return AVERROR(EINVAL);
		}
		const auto status = input.source->seek(origin, offset);
		if (!status)
			return toAvError(status.error);
		const auto position = input.source->tell();
		if (!position || position.value < 0)
			return input.terminalRead = position ? AVERROR(EIO) : toAvError(position.error);
		input.terminalRead = 0;
		return position.value;
	}
	catch (const std::bad_alloc&) { return input.terminalRead = AVERROR(ENOMEM); }
	catch (...) { return input.terminalRead = AVERROR(EIO); }
}
