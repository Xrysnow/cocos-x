#include "io/BufferedStream.h"
#include <algorithm>
#include <cstring>
#include <limits>
#include <new>
#include <stdexcept>

namespace cocos2d::io
{
namespace
{
Status validateOptions(BufferOptions options)
{
    const auto maxSize = std::vector<uint8_t>{}.max_size();
    const auto valid = [maxSize](size_t size) {
        return size <= maxSize && static_cast<uint64_t>(size) <= static_cast<uint64_t>(INT64_MAX);
    };
    return valid(options.readCapacity) && valid(options.writeCapacity)
        ? Status::success() : Status::failure({ErrorCode::Overflow});
}

StreamError terminalError(const IoResult& result)
{
    if (result.error)
        return result.error;
    switch (result.status)
    {
    case IoStatus::WouldBlock: return {ErrorCode::WouldBlock};
    case IoStatus::Cancelled: return {ErrorCode::Cancelled};
    case IoStatus::Timeout: return {ErrorCode::Timeout};
    default: return {ErrorCode::IoError};
    }
}

IoResult ioFailure(StreamError error, size_t transferred = 0)
{
    // flush/seek use Status, but byte operations preserve control-flow results
    // rather than changing a queued write's WouldBlock into a generic error.
    switch (error.code)
    {
    case ErrorCode::WouldBlock: return {transferred, IoStatus::WouldBlock, {}};
    case ErrorCode::Cancelled: return {transferred, IoStatus::Cancelled, {}};
    case ErrorCode::Timeout: return {transferred, IoStatus::Timeout, {}};
    default: return IoResult::failure(error, transferred);
    }
}

bool fitsPosition(int64_t position, size_t length)
{
    return static_cast<uint64_t>(length) <= static_cast<uint64_t>(INT64_MAX - position);
}

StreamError validateTransfer(const IoResult& result, size_t requested, bool writing)
{
    if (result.transferred > requested)
        return {ErrorCode::InvalidBackend};
    switch (result.status)
    {
    case IoStatus::Ok:
        if (result.error)
            return {ErrorCode::InvalidBackend};
        if (requested && !result.transferred)
            return {ErrorCode::NoProgress};
        break;
    case IoStatus::Error:
        if (!result.error)
            return {ErrorCode::InvalidBackend};
        break;
    case IoStatus::EndOfStream:
        if (writing || result.error || result.transferred == requested)
            return {ErrorCode::InvalidBackend};
        break;
    case IoStatus::WouldBlock:
    case IoStatus::Cancelled:
    case IoStatus::Timeout:
        if (result.error)
            return {ErrorCode::InvalidBackend};
        break;
    default:
        return {ErrorCode::InvalidBackend};
    }
    return {};
}
}

Result<ThreadSafeRefPtr<BufferedStream>> BufferedStream::create(StreamPtr source, BufferOptions options)
{
    try
    {
        auto stream = makeThreadSafeRef<BufferedStream>();
        const auto result = stream->init(std::move(source), options);
        if (!result)
            return Result<ThreadSafeRefPtr<BufferedStream>>::failure(result.error);
        return Result<ThreadSafeRefPtr<BufferedStream>>::success(std::move(stream));
    }
    catch (const std::bad_alloc&)
    {
        return Result<ThreadSafeRefPtr<BufferedStream>>::failure({ErrorCode::OutOfMemory});
    }
}

Status BufferedStream::init(StreamPtr source, BufferOptions options)
{
    if (!source || !source->isOpen())
        return Status::failure({ErrorCode::Closed});
    auto status = validateOptions(options);
    if (!status)
        return status;
    const auto capabilities = source->capabilities();
    // A single cursor cannot support switching between prefetched input and
    // output without repositioning. Read-only sequential input is supported.
    if (hasCapability(capabilities, Capability::Read | Capability::Write) &&
        !hasCapability(capabilities, Capability::Seek))
        return Status::failure({ErrorCode::NotSupported});
    const auto position = source->tell();
    if (!position)
        return Status::failure(position.error);
    if (position.value < 0)
        return Status::failure({ErrorCode::InvalidBackend});
    _source = std::move(source);
    _capabilities = capabilities;
    _options = options;
    _position = _backendPosition = position.value;
    _open = true;
    return Status::success();
}

BufferedStream::~BufferedStream()
{
    if (_open)
    {
        close();
        if (_open)
        {
            // Explicit close reports and preserves flush failures. Destruction
            // must still release the owned backend even if it cannot be flushed.
            _source->close();
            _open = false;
        }
    }
}

bool BufferedStream::isOpen() const noexcept
{
    return _open && _source && _source->isOpen();
}

Status BufferedStream::checkOpen() const
{
    if (!isOpen())
        return Status::failure({ErrorCode::Closed});
    return _fault ? Status::failure(_fault) : Status::success();
}

const void* BufferedStream::cursorIdentity() const noexcept
{
    return _source ? _source->cursorIdentity() : this;
}

StreamError BufferedStream::failBackend()
{
    _fault = {ErrorCode::InvalidBackend};
    return _fault;
}

Status BufferedStream::ensureBuffer(std::vector<uint8_t>& buffer, size_t capacity)
{
    if (buffer.size() == capacity)
        return Status::success();
    try
    {
        buffer.resize(capacity);
        return Status::success();
    }
    catch (const std::bad_alloc&)
    {
        return Status::failure({ErrorCode::OutOfMemory});
    }
    catch (const std::length_error&)
    {
        return Status::failure({ErrorCode::Overflow});
    }
}

void BufferedStream::clearReadBuffer() noexcept
{
    _readStart = _position;
    _readCount = _readIndex = 0;
    _readTerminal = {};
}

Status BufferedStream::seekBackend(int64_t target)
{
    const auto status = _source->seek(SeekOrigin::Begin, target);
    const auto observed = _source->tell();
    if (!status)
    {
        if (!observed || observed.value != _backendPosition)
            _fault = status.error;
        return status;
    }
    if (!observed || observed.value != target)
        return Status::failure(failBackend());
    _backendPosition = target;
    return Status::success();
}

Status BufferedStream::alignReadPosition()
{
    if (_backendPosition != _position)
    {
        if (!hasCapability(_capabilities, Capability::Seek))
            return Status::failure({ErrorCode::NotSupported});
        const auto status = seekBackend(_position);
        if (!status)
            return status;
    }
    clearReadBuffer();
    return Status::success();
}

Result<int64_t> BufferedStream::tell() const
{
    const auto status = checkOpen();
    return status ? Result<int64_t>::success(_position) : Result<int64_t>::failure(status.error);
}

Result<std::optional<int64_t>> BufferedStream::size() const
{
    const auto status = checkOpen();
    if (!status)
        return Result<std::optional<int64_t>>::failure(status.error);
    auto length = _source->size();
    if (!length)
        return length;
    if (length.value && *length.value < 0)
        return Result<std::optional<int64_t>>::failure({ErrorCode::InvalidBackend});
    if (length.value && _writeCount)
        length.value = std::max(*length.value, _writeStart + static_cast<int64_t>(_writeCount));
    return length;
}

IoResult BufferedStream::read(void* destination, size_t length)
{
    auto status = checkOpen();
    if (!status)
        return ioFailure(status.error);
    if (!hasCapability(_capabilities, Capability::Read))
        return IoResult::failure({ErrorCode::PermissionDenied});
    if (length == 0)
        return IoResult::success(0);
    if (!destination)
        return IoResult::failure({ErrorCode::InvalidArgument});
    if (!fitsPosition(_position, length))
        return IoResult::failure({ErrorCode::Overflow});
    status = drainWrites();
    if (!status)
        return ioFailure(status.error);

    auto output = static_cast<uint8_t*>(destination);
    size_t total = 0;
    while (total < length)
    {
        const auto available = _readCount - _readIndex;
        if (available)
        {
            const auto count = std::min(available, length - total);
            std::memcpy(output + total, _readBuffer.data() + _readIndex, count);
            _readIndex += count;
            _position += static_cast<int64_t>(count);
            total += count;
            if (total == length)
            {
                if (_readIndex == _readCount && _readTerminal.status != IoStatus::Ok &&
                    _readTerminal.status != IoStatus::EndOfStream)
                {
                    auto terminal = _readTerminal;
                    _readTerminal = {};
                    terminal.transferred = total;
                    return terminal;
                }
                return IoResult::success(total);
            }
        }
        if (_readTerminal.status != IoStatus::Ok)
        {
            auto terminal = _readTerminal;
            _readTerminal = {};
            terminal.transferred = total;
            return terminal;
        }
        clearReadBuffer();
        const auto remaining = length - total;
        if (_options.readCapacity == 0 || remaining >= _options.readCapacity)
        {
            auto result = _source->read(output + total, remaining);
            if (const auto error = validateTransfer(result, remaining, false))
                return IoResult::failure(error.code == ErrorCode::InvalidBackend ? failBackend() : error, total);
            _position += static_cast<int64_t>(result.transferred);
            _backendPosition += static_cast<int64_t>(result.transferred);
            result.transferred += total;
            return result;
        }
        status = ensureBuffer(_readBuffer, _options.readCapacity);
        if (!status)
            return ioFailure(status.error, total);
        const auto request = static_cast<size_t>(std::min<uint64_t>(
            _readBuffer.size(), static_cast<uint64_t>(INT64_MAX - _backendPosition)));
        if (!request)
            return IoResult::failure({ErrorCode::Overflow}, total);
        const auto result = _source->read(_readBuffer.data(), request);
        if (const auto error = validateTransfer(result, request, false))
            return IoResult::failure(error.code == ErrorCode::InvalidBackend ? failBackend() : error, total);
        _readStart = _position;
        _readCount = result.transferred;
        _readIndex = 0;
        _backendPosition += static_cast<int64_t>(result.transferred);
        if (result.status != IoStatus::Ok)
            _readTerminal = {0, result.status, result.error};
    }
    return IoResult::success(total);
}

Status BufferedStream::observeWritePosition(size_t transferred)
{
    if (hasCapability(_capabilities, Capability::Append))
    {
        const auto position = _source->tell();
        if (!position || position.value < 0)
            return Status::failure(failBackend());
        _position = _backendPosition = position.value;
    }
    else
    {
        _position += static_cast<int64_t>(transferred);
        _backendPosition += static_cast<int64_t>(transferred);
    }
    return Status::success();
}

IoResult BufferedStream::write(const void* source, size_t length)
{
    auto status = checkOpen();
    if (!status)
        return ioFailure(status.error);
    if (!hasCapability(_capabilities, Capability::Write))
        return IoResult::failure({ErrorCode::PermissionDenied});
    if (length == 0)
        return IoResult::success(0);
    if (!source)
        return IoResult::failure({ErrorCode::InvalidArgument});
    if (!hasCapability(_capabilities, Capability::Append) && !fitsPosition(_position, length))
        return IoResult::failure({ErrorCode::Overflow});
    // Pending writes already place the backend behind the logical position;
    // only reconcile prefetched input when no output is pending.
    if (!_writeCount)
    {
        status = alignReadPosition();
        if (!status)
            return ioFailure(status.error);
    }
    const auto input = static_cast<const uint8_t*>(source);
    size_t total = 0;
    while (total < length)
    {
        if (_writeCount == _options.writeCapacity && _writeCount)
        {
            status = drainWrites();
            if (!status)
                return ioFailure(status.error, total);
        }
        const auto remaining = length - total;
        if (!_writeCount && (_options.writeCapacity == 0 ||
            hasCapability(_capabilities, Capability::Append) || remaining >= _options.writeCapacity))
        {
            auto result = _source->write(input + total, remaining);
            if (const auto error = validateTransfer(result, remaining, true))
                return IoResult::failure(error.code == ErrorCode::InvalidBackend ? failBackend() : error, total);
            status = observeWritePosition(result.transferred);
            if (!status)
                return ioFailure(status.error, total + result.transferred);
            result.transferred += total;
            return result;
        }
        status = ensureBuffer(_writeBuffer, _options.writeCapacity);
        if (!status)
            return ioFailure(status.error, total);
        if (!_writeCount)
            _writeStart = _position;
        const auto count = std::min(remaining, _writeBuffer.size() - _writeCount);
        std::memcpy(_writeBuffer.data() + _writeCount, input + total, count);
        _writeCount += count;
        _position += static_cast<int64_t>(count);
        total += count;
    }
    return IoResult::success(total);
}

Status BufferedStream::drainWrites()
{
    while (_writeCount)
    {
        const auto result = _source->write(_writeBuffer.data(), _writeCount);
        if (const auto error = validateTransfer(result, _writeCount, true))
            return Status::failure(error.code == ErrorCode::InvalidBackend ? failBackend() : error);
        if (result.transferred)
        {
            _writeCount -= result.transferred;
            _writeStart += static_cast<int64_t>(result.transferred);
            _backendPosition += static_cast<int64_t>(result.transferred);
            if (_writeCount)
                std::memmove(_writeBuffer.data(), _writeBuffer.data() + result.transferred, _writeCount);
        }
        if (result.status != IoStatus::Ok)
            return Status::failure(terminalError(result));
    }
    return Status::success();
}

Status BufferedStream::flush()
{
    const auto status = checkOpen();
    if (!status)
        return status;
    const auto drained = drainWrites();
    return drained ? _source->flush() : drained;
}

Status BufferedStream::sync()
{
    auto status = checkOpen();
    if (!status)
        return status;
    if (!hasCapability(_capabilities, Capability::Sync))
        return Status::failure({ErrorCode::NotSupported});
    status = flush();
    return status ? _source->sync() : status;
}

Status BufferedStream::seek(SeekOrigin origin, int64_t offset)
{
    auto status = checkOpen();
    if (!status)
        return status;
    if (!hasCapability(_capabilities, Capability::Seek))
        return Status::failure({ErrorCode::NotSupported});
    const auto length = size();
    if (!length)
        return Status::failure(length.error);
    const auto target = detail::seekTarget(origin, offset, _position, length.value,
        hasCapability(_capabilities, Capability::Write | Capability::Resize));
    if (!target)
        return Status::failure(target.error);
    if (!_writeCount && _readCount && target.value >= _readStart &&
        static_cast<uint64_t>(target.value - _readStart) <= _readCount)
    {
        _readIndex = static_cast<size_t>(target.value - _readStart);
        _position = target.value;
        // No backend reposition occurred: an as-yet-unreported terminal result
        // still belongs to the end of these cached bytes and must not be lost.
        return Status::success();
    }
    status = drainWrites();
    if (!status)
        return status;
    status = seekBackend(target.value);
    if (status)
    {
        _position = target.value;
        clearReadBuffer();
    }
    return status;
}

Status BufferedStream::resize(int64_t length)
{
    auto status = checkOpen();
    if (!status)
        return status;
    if (length < 0)
        return Status::failure({ErrorCode::InvalidArgument});
    if (!hasCapability(_capabilities, Capability::Resize))
        return Status::failure({ErrorCode::NotSupported});
    status = drainWrites();
    if (!status)
        return status;
    status = alignReadPosition();
    if (!status)
        return status;
    status = _source->resize(length);
    const auto observed = _source->tell();
    if (!status)
    {
        if (!observed || observed.value != _backendPosition)
            _fault = status.error;
        return status;
    }
    if (!observed || observed.value != std::min(_position, length))
        return Status::failure(failBackend());
    _position = _backendPosition = observed.value;
    clearReadBuffer();
    return Status::success();
}

Status BufferedStream::setBufferOptions(BufferOptions options)
{
    auto status = checkOpen();
    if (!status)
        return status;
    status = validateOptions(options);
    if (!status)
        return status;
    if (options.readCapacity == _options.readCapacity && options.writeCapacity == _options.writeCapacity)
        return Status::success();
    const auto unread = _readCount - _readIndex;
    const bool discardRead = unread > options.readCapacity;
    if (discardRead && !hasCapability(_capabilities, Capability::Seek))
        return Status::failure({ErrorCode::NotSupported});
    // Re-reading can reconstruct data, but cannot reconstruct a transient
    // terminal event already observed while prefetching those data.
    if (discardRead && _readTerminal.status != IoStatus::Ok && _readTerminal.status != IoStatus::EndOfStream)
        return Status::failure({ErrorCode::NotSupported});

    std::vector<uint8_t> nextRead;
    std::vector<uint8_t> nextWrite;
    // Preserve lazy allocation for directions that have never used a cache.
    if (!_readBuffer.empty() && hasCapability(_capabilities, Capability::Read))
    {
        status = ensureBuffer(nextRead, options.readCapacity);
        if (!status)
            return status;
    }
    if (!_writeBuffer.empty() && !hasCapability(_capabilities, Capability::Append))
    {
        status = ensureBuffer(nextWrite, options.writeCapacity);
        if (!status)
            return status;
    }
    status = flush();
    if (!status)
        return status;
    if (discardRead)
    {
        status = alignReadPosition();
        if (!status)
            return status;
    }
    else
    {
        if (unread)
            std::memcpy(nextRead.data(), _readBuffer.data() + _readIndex, unread);
        _readStart = _position;
        _readCount = unread;
        _readIndex = 0;
    }
    _readBuffer.swap(nextRead);
    _writeBuffer.swap(nextWrite);
    _options = options;
    return Status::success();
}

Status BufferedStream::close()
{
    if (!_open)
        return _closeResult;
    const auto status = flush();
    if (!status)
        return status;
    _closeResult = _source->close();
    _open = false;
    clearReadBuffer();
    std::vector<uint8_t>{}.swap(_readBuffer);
    std::vector<uint8_t>{}.swap(_writeBuffer);
    return _closeResult;
}
}
