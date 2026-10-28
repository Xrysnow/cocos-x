#include "AudioStream.h"
#include "AudioCommon.h"
#include "platform/CCFileUtils.h"
#include "platform/CCFileStream.h"
#include <algorithm>
#include <cstdio>
#include <limits>
#include <memory>
#include <mutex>
#include <new>
#include <utility>

NS_CC_BEGIN

namespace
{
	AudioStream::FileOpener fileOpener;

	class AudioFileStream final : public AudioStream
	{
	public:
		explicit AudioFileStream(std::unique_ptr<FileStream> file)
			: file(std::move(file))
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
		std::mutex mutex;
		bool failed = false;
	};
}

void AudioStream::setFileOpener(FileOpener opener)
{
	fileOpener = std::move(opener);
}

AudioStream* AudioStream::createFromFile(const std::string& path)
{
	if (path.empty())
		return nullptr;
	return fileOpener ? fileOpener(path) : createFromLocalFile(path);
}

AudioStream* AudioStream::createFromLocalFile(const std::string& path)
{
	if (path.empty())
		return nullptr;
	auto fileUtils = FileUtils::getInstance();
	if (!fileUtils)
		return nullptr;
	const auto fullPath = fileUtils->fullPathForFilename(path);
	if (fullPath.empty() || fileUtils->isDirectoryExist(fullPath))
		return nullptr;
	auto file = fileUtils->openFileStream(fullPath, FileStream::Mode::READ);
	if (!file || !file->isOpen())
		return nullptr;
	const auto length = file->size();
	const auto position = file->tell();
	if (length < 0 || position < 0 || position > length)
		return nullptr;
	if (position != 0 && (file->seek(0, SEEK_SET) != 0 || file->tell() != 0))
		return nullptr;
	auto result = new (std::nothrow) AudioFileStream(std::move(file));
	if (!result)
		return nullptr;
	result->autorelease();
	return result;
}

NS_CC_END
