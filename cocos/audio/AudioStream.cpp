#include "AudioStream.h"
#include "AudioCommon.h"
#include "platform/FileUtils.h"
#include "platform/PosixFileStream.h"
#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <limits>
#include <memory>
#include <mutex>
#include <new>
#include <typeinfo>
#include <utility>

NS_CC_BEGIN

namespace
{
	AudioStream::FileOpener fileOpener;

	class AudioFileStream final : public AudioStream
	{
	public:
		explicit AudioFileStream(std::unique_ptr<FileStream> file, ReopenFactory reopen = {})
			: file(std::move(file)), reopen(std::move(reopen))
		{
		}

		uint64_t size() override
		{
			if (failed)
				return 0;
			const auto result = file->size();
			if (result < 0)
				return fail("size"), 0;
			return static_cast<uint64_t>(result);
		}

		uint64_t tell() override
		{
			if (failed)
				return 0;
			const auto result = file->tell();
			if (result < 0)
				return fail("tell"), 0;
			return static_cast<uint64_t>(result);
		}

		bool seek(SeekOrigin origin, int64_t offset) override
		{
			if (failed)
				return false;
			const auto length = size();
			uint64_t base = 0;
			switch (origin)
			{
			case SeekOrigin::BEGINNING: break;
			case SeekOrigin::CURRENT: base = tell(); break;
			case SeekOrigin::END: base = length; break;
			default: return false;
			}
			if (failed || base > static_cast<uint64_t>(std::numeric_limits<int64_t>::max()))
				return false;
			const auto signedBase = static_cast<int64_t>(base);
			if ((offset < 0 && offset < -signedBase) ||
				(offset >= 0 && offset > std::numeric_limits<int64_t>::max() - signedBase))
				return false;
			const auto target = signedBase + offset;
			if (static_cast<uint64_t>(target) > length)
				return false;
			if (file->seek(target, SEEK_SET) != 0)
				return fail("seek");
			const auto position = file->tell();
			if (position < 0 || position != target)
				return fail("seek/tell");
			return true;
		}

		bool read(uint8_t* dst, uint64_t length, uint64_t* bytesRead) override
		{
			if (bytesRead)
				*bytesRead = 0;
			if (length == 0)
				return true;
			if (failed || !dst || length > std::numeric_limits<size_t>::max())
				return false;
			uint64_t total = 0;
			while (total < length)
			{
				const auto chunk = static_cast<unsigned int>(std::min<uint64_t>(
					length - total, static_cast<uint64_t>(std::numeric_limits<int>::max())));
				const auto count = file->read(dst + static_cast<size_t>(total), chunk);
				if (count < 0 || static_cast<unsigned int>(count) > chunk)
					return fail("read");
				if (count == 0)
					return false;
				total += static_cast<unsigned int>(count);
				if (bytesRead)
					*bytesRead = total;
			}
			return true;
		}

		void lock() override { mutex.lock(); }
		void unlock() override { mutex.unlock(); }
		ReopenFactory getReopenFactory() const override { return reopen; }
		bool hasIoError() const noexcept override { return failed; }

	private:
		bool fail(const char* operation)
		{
			AudioInternal::logging("[AERRO] AudioFileStream %s failed; stream disabled", operation);
			// The public size/tell contract is unsigned. Once a backend operation
			// fails, expose zero for both and reject further I/O instead of leaking
			// a wrapped negative value into decoder remaining-byte arithmetic.
			failed = true;
			return false;
		}

		std::unique_ptr<FileStream> file;
		ReopenFactory reopen;
		std::mutex mutex;
		bool failed = false;
	};

	AudioStream::ReopenFactory nativeFileReopener(const FileStream& file, const std::string& fullPath)
	{
		// Only native streams can prove the identity of both opened handles.
		if (typeid(file) != typeid(PosixFileStream))
			return {};
		const auto identity = static_cast<const PosixFileStream&>(file).getIdentity();
		if (!identity)
			return {};
		std::string path;
		try
		{
			std::error_code error;
			const auto absolute = std::filesystem::absolute(std::filesystem::u8path(fullPath), error);
			if (error)
				return {};
			const auto encoded = absolute.u8string();
			path.assign(reinterpret_cast<const char*>(encoded.data()), encoded.size());
		}
		catch (const std::filesystem::filesystem_error&) { return {}; }
		return [path = std::move(path), expected = *identity]() -> cc::IntrusivePtr<AudioStream>
		{
			auto reader = std::make_unique<PosixFileStream>();
			if (!reader->open(path, FileStream::Mode::READ) || reader->getIdentity() != expected)
				return nullptr;
			return cc::IntrusivePtr{new (std::nothrow) AudioFileStream(std::move(reader))};
		};
	}

	cc::IntrusivePtr<AudioStream> openAudioHit(const FileHit& hit)
	{
		auto stream = FileUtils::openRead(hit);
		if (!stream || !stream.value || !stream.value->isOpen())
			return nullptr;
		auto& file = stream.value;
		const auto length = file->size();
		const auto position = file->tell();
		if (length < 0 || position < 0 || position > length)
			return nullptr;
		if (position != 0 && (file->seek(0, SEEK_SET) != 0 || file->tell() != 0))
			return nullptr;
		AudioStream::ReopenFactory reopen;
		if (hit.entry().nativePath)
			reopen = nativeFileReopener(*file, *hit.entry().nativePath);
		else
		{
			reopen = [hit]() -> cc::IntrusivePtr<AudioStream>
			{
				auto reopened = FileUtils::openRead(hit);
				if (!reopened || !reopened.value || !reopened.value->isOpen())
					return nullptr;
				return cc::IntrusivePtr{new (std::nothrow) AudioFileStream(std::move(reopened.value))};
			};
		}
		return cc::IntrusivePtr{new (std::nothrow) AudioFileStream(std::move(file), std::move(reopen))};
	}
}

void AudioStream::setFileOpener(FileOpener opener)
{
	fileOpener = std::move(opener);
}

cc::IntrusivePtr<AudioStream> AudioStream::createFromFile(const std::string& path)
{
	if (path.empty())
		return nullptr;
	if (fileOpener)
		return fileOpener(path);
	auto fileUtils = FileUtils::getInstance();
	if (!fileUtils)
		return nullptr;
	const auto hit = fileUtils->findFile(path);
	return hit ? openAudioHit(hit.value) : nullptr;
}

cc::IntrusivePtr<AudioStream> AudioStream::createFromLocalFile(const std::string& path)
{
	if (path.empty())
		return nullptr;
	auto fileUtils = FileUtils::getInstance();
	if (!fileUtils)
		return nullptr;
	const auto hit = fileUtils->findPlatformFile(path);
	return hit ? openAudioHit(hit.value) : nullptr;
}

NS_CC_END
