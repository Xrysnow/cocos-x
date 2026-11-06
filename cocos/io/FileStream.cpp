#include "io/FileStream.h"
#include "platform/CCFileUtils.h"
#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <limits>
#include <new>
#include <stdexcept>

namespace cocos2d::io
{
namespace
{
StreamError fileError(int error)
{
    ErrorCode code = ErrorCode::IoError;
    switch (error)
    {
    case EINVAL: code = ErrorCode::InvalidArgument; break;
    case EBADF: case EACCES: case EPERM: code = ErrorCode::PermissionDenied; break;
    case ENOENT: code = ErrorCode::NotFound; break;
    case EEXIST: code = ErrorCode::AlreadyExists; break;
    case ENOSPC: code = ErrorCode::NoSpace; break;
    case ENOMEM: code = ErrorCode::OutOfMemory; break;
    case EOVERFLOW: case EFBIG: code = ErrorCode::Overflow; break;
    case ENOSYS: code = ErrorCode::NotSupported; break;
    default: break;
    }
    return {code, error, error ? ErrorDomain::Errno : ErrorDomain::None};
}
}

FileStream::FileStream(RefConstructionToken token, std::unique_ptr<cocos2d::FileStream> backend,
                       FileOpenOptions options)
    : Stream(token), _backend(std::move(backend)), _options(options)
{}

FileStream::~FileStream() { close(); }

Result<ThreadSafeRefPtr<FileStream>> FileStream::open(std::string_view path, FileOpenOptions options)
{
    using Output = Result<ThreadSafeRefPtr<FileStream>>;
    cocos2d::FileStream::Mode mode;
    if (path.empty() || path.find('\0') != std::string_view::npos ||
        !cocos2d::FileStream::encodeOpenOptions(options, mode))
        return Output::failure({ErrorCode::InvalidArgument});
    try
    {
        auto fileUtils = FileUtils::getInstance();
        if (!fileUtils)
            return Output::failure({ErrorCode::IoError});
        std::string target(path);
        // Resolve existing resource inputs; never search for a write destination.
        if (options.access == FileAccess::Read)
            target = fileUtils->fullPathForFilename(target);
        if (target.empty())
            return Output::failure({ErrorCode::NotFound});
        if (fileUtils->isDirectoryExist(target))
            return Output::failure({ErrorCode::InvalidArgument});
        errno = 0;
        auto backend = fileUtils->openFileStream(target, mode);
        if (!backend)
            return Output::failure(fileError(errno));
        return fromBackend(std::move(backend), options);
    }
    catch (const std::bad_alloc&) { return Output::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return Output::failure({ErrorCode::Overflow}); }
}

Result<ThreadSafeRefPtr<FileStream>> FileStream::fromBackend(std::unique_ptr<cocos2d::FileStream> backend,
                                                          FileOpenOptions options)
{
    using Output = Result<ThreadSafeRefPtr<FileStream>>;
    cocos2d::FileStream::Mode mode;
    if (!cocos2d::FileStream::encodeOpenOptions(options, mode))
        return Output::failure({ErrorCode::InvalidArgument});
    if (!backend || !backend->isOpen())
        return Output::failure({ErrorCode::Closed});
    if ((options.access != FileAccess::Write && !backend->isReadable()) ||
        (options.access != FileAccess::Read && !backend->isWritable()))
        return Output::failure({ErrorCode::PermissionDenied});
    errno = 0;
    const auto length = backend->size();
    if (length < 0)
        return Output::failure(fileError(errno));
    errno = 0;
    const auto position = backend->tell();
    if (position < 0)
        return Output::failure(fileError(errno));
    if (position > length && options.access == FileAccess::Read)
        return Output::failure({ErrorCode::OutOfRange});
    if (options.append)
    {
        errno = 0;
        if (backend->seek(0, SEEK_END) != 0)
            return Output::failure(fileError(errno));
        if (backend->tell() != length)
            return Output::failure({ErrorCode::InvalidBackend});
    }
    try
    {
        return Output::success(makeThreadSafeRef<FileStream>(std::move(backend), options));
    }
    catch (const std::bad_alloc&) { return Output::failure({ErrorCode::OutOfMemory}); }
}

Capability FileStream::capabilities() const noexcept
{
    if (!isOpen())
        return Capability::None;
    Capability result = Capability::Seek;
    if (_options.access != FileAccess::Write && _backend->isReadable())
        result = result | Capability::Read;
    if (_options.access != FileAccess::Read && _backend->isWritable())
    {
        result = result | Capability::Write;
        if (_backend->canResize()) result = result | Capability::Resize;
        if (_backend->canSync()) result = result | Capability::Sync;
        if (_options.append) result = result | Capability::Append;
    }
    return result;
}

bool FileStream::isOpen() const noexcept { return _backend && _backend->isOpen(); }

StreamError FileStream::stateError() const
{
    if (!isOpen())
        return {ErrorCode::Closed};
    return _fault;
}

IoResult FileStream::read(void* destination, size_t length)
{
    if (const auto error = stateError()) return IoResult::failure(error);
    if (!hasCapability(capabilities(), Capability::Read))
        return IoResult::failure({ErrorCode::PermissionDenied});
    if (!length) return IoResult::success(0);
    if (!destination) return IoResult::failure({ErrorCode::InvalidArgument});
    const auto previous = tell();
    if (!previous) return IoResult::failure(previous.error);
    const auto chunk = static_cast<unsigned int>(std::min(length, size_t(std::numeric_limits<int>::max())));
    errno = 0;
    const int count = _backend->read(destination, chunk);
    if (count < 0)
    {
        const auto error = fileError(errno);
        if (_backend->tell() != previous.value)
            _fault = error;
        return IoResult::failure(error);
    }
    if (static_cast<unsigned int>(count) > chunk)
        return IoResult::failure(_fault = {ErrorCode::InvalidBackend});
    if (!count)
        return {0, IoStatus::EndOfStream, {}};
    return IoResult::success(static_cast<size_t>(count));
}

IoResult FileStream::write(const void* source, size_t length)
{
    if (const auto error = stateError()) return IoResult::failure(error);
    if (!hasCapability(capabilities(), Capability::Write))
        return IoResult::failure({ErrorCode::PermissionDenied});
    if (!length) return IoResult::success(0);
    if (!source) return IoResult::failure({ErrorCode::InvalidArgument});
    const auto previous = tell();
    if (!previous) return IoResult::failure(previous.error);
    auto writePosition = previous.value;
    if (_options.append)
    {
        const auto end = size();
        if (!end) return IoResult::failure(end.error);
        if (!end.value) return IoResult::failure({ErrorCode::InvalidBackend});
        writePosition = *end.value;
    }
    if (length > static_cast<uint64_t>(std::numeric_limits<int64_t>::max() - writePosition))
        return IoResult::failure({ErrorCode::Overflow});
    if (_options.append)
    {
        // Delegates need not open their backend with O_APPEND. Seek before each
        // write, while native append handles retain their atomic append flag.
        errno = 0;
        if (_backend->seek(writePosition, SEEK_SET) != 0)
        {
            const auto error = fileError(errno);
            if (_backend->tell() != previous.value)
                _fault = error;
            return IoResult::failure(error);
        }
        if (_backend->tell() != writePosition)
            return IoResult::failure(_fault = {ErrorCode::InvalidBackend});
    }
    const auto chunk = static_cast<unsigned int>(std::min(length, size_t(std::numeric_limits<int>::max())));
    errno = 0;
    const int count = _backend->write(source, chunk);
    if (count < 0)
    {
        const auto error = fileError(errno);
        if (_backend->tell() != previous.value)
            _fault = error;
        return IoResult::failure(error);
    }
    if (static_cast<unsigned int>(count) > chunk)
        return IoResult::failure(_fault = {ErrorCode::InvalidBackend});
    if (!count)
        return IoResult::failure({ErrorCode::NoProgress});
    return IoResult::success(static_cast<size_t>(count));
}

Result<int64_t> FileStream::tell() const
{
    if (const auto error = stateError()) return Result<int64_t>::failure(error);
    errno = 0;
    const auto position = _backend->tell();
    if (position < 0)
        return Result<int64_t>::failure(_fault = fileError(errno));
    return Result<int64_t>::success(position);
}

Result<std::optional<int64_t>> FileStream::size() const
{
    if (const auto error = stateError()) return Result<std::optional<int64_t>>::failure(error);
    errno = 0;
    const auto length = _backend->size();
    if (length < 0)
        return Result<std::optional<int64_t>>::failure(_fault = fileError(errno));
    return Result<std::optional<int64_t>>::success(length);
}

Status FileStream::seek(SeekOrigin origin, int64_t offset)
{
    const auto position = tell();
    if (!position) return Status::failure(position.error);
    const auto length = size();
    if (!length) return Status::failure(length.error);
    const auto target = detail::seekTarget(origin, offset, position.value, length.value,
                                         hasCapability(capabilities(), Capability::Write));
    if (!target) return Status::failure(target.error);
    errno = 0;
    if (_backend->seek(target.value, SEEK_SET) != 0)
    {
        const auto error = fileError(errno);
        if (_backend->tell() != position.value)
            _fault = error;
        return Status::failure(error);
    }
    if (_backend->tell() != target.value)
        return Status::failure(_fault = {ErrorCode::InvalidBackend});
    return Status::success();
}

Status FileStream::resize(int64_t length)
{
    if (const auto error = stateError()) return Status::failure(error);
    if (length < 0) return Status::failure({ErrorCode::InvalidArgument});
    if (!hasCapability(capabilities(), Capability::Resize))
        return Status::failure({ErrorCode::NotSupported});
    const auto previous = tell();
    if (!previous) return Status::failure(previous.error);
    errno = 0;
    if (_backend->resize(length) != 0)
    {
        const auto error = fileError(errno);
        if (_backend->tell() != previous.value)
            _fault = error;
        return Status::failure(error);
    }
    const auto target = std::min(previous.value, length);
    if (_backend->tell() != target)
    {
        errno = 0;
        if (_backend->seek(target, SEEK_SET) != 0 || _backend->tell() != target)
            return Status::failure(_fault = fileError(errno));
    }
    return Status::success();
}

Status FileStream::flush()
{
    const auto error = stateError();
    return error ? Status::failure(error) : Status::success();
}

Status FileStream::sync()
{
    if (const auto error = stateError()) return Status::failure(error);
    if (!hasCapability(capabilities(), Capability::Sync))
        return Status::failure({ErrorCode::NotSupported});
    errno = 0;
    return _backend->sync() == 0 ? Status::success() : Status::failure(fileError(errno));
}

Status FileStream::close()
{
    if (!_backend)
        return _closeResult;
    // Once close was attempted, never retry its descriptor. It might have been
    // consumed even if close reported an error.
    errno = 0;
    if (_backend->close() != 0)
        _closeResult = Status::failure(fileError(errno));
    _backend.reset();
    return _closeResult;
}
}
