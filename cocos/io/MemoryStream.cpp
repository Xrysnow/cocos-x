#include "io/MemoryStream.h"
#include <algorithm>
#include <cstring>
#include <new>
#include <stdexcept>

namespace cocos2d::io
{
Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::fromOwned(
    ThreadSafeRefPtr<MemoryBuffer> buffer, bool writable, size_t maxCapacity)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    if (maxCapacity > MemoryBuffer::MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (buffer->size() > maxCapacity || buffer->capacity() > maxCapacity)
        return R::failure({ErrorCode::LimitExceeded});
    try
    {
        auto stream = makeThreadSafeRef<MemoryStream>();
        buffer->_writable = writable;
        buffer->_resizable = writable;
        buffer->_maxCapacity = maxCapacity;
        stream->_mutable = writable ? buffer.get() : nullptr;
        stream->_buffer = std::move(buffer);
        return R::success(std::move(stream));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::create(size_t initialSize, size_t maxCapacity)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    if (initialSize > MemoryBuffer::MaxSize || maxCapacity > MemoryBuffer::MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (initialSize > maxCapacity)
        return R::failure({ErrorCode::LimitExceeded});
    try
    {
        return move(std::vector<uint8_t>(initialSize, 0), true, maxCapacity);
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return R::failure({ErrorCode::LimitExceeded}); }
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::copy(
    const void* source, size_t length, bool writable, size_t maxCapacity)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    if (maxCapacity > MemoryBuffer::MaxSize || length > MemoryBuffer::MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (length > maxCapacity)
        return R::failure({ErrorCode::LimitExceeded});
    auto buffer = MemoryBuffer::copy(source, length);
    return buffer ? fromOwned(std::move(buffer.value), writable, maxCapacity) : R::failure(buffer.error);
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::move(
    std::vector<uint8_t> bytes, bool writable, size_t maxCapacity)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    if (maxCapacity > MemoryBuffer::MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (bytes.size() > maxCapacity || bytes.capacity() > maxCapacity)
        return R::failure({ErrorCode::LimitExceeded});
    auto buffer = MemoryBuffer::move(std::move(bytes));
    return buffer ? fromOwned(std::move(buffer.value), writable, maxCapacity) : R::failure(buffer.error);
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::fromBuffer(ThreadSafeRefPtr<const MemoryBuffer> buffer)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    if (!buffer || buffer->_writable)
        return R::failure({ErrorCode::InvalidArgument});
    try
    {
        auto stream = makeThreadSafeRef<MemoryStream>();
        stream->_buffer = std::move(buffer);
        return R::success(std::move(stream));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::borrow(
    const void* source, size_t length, ThreadSafeRefPtr<Ref> owner)
{
    auto buffer = MemoryBuffer::borrow(source, length, std::move(owner));
    return buffer ? fromBuffer(std::move(buffer.value))
                  : Result<ThreadSafeRefPtr<MemoryStream>>::failure(buffer.error);
}

Result<ThreadSafeRefPtr<MemoryStream>> MemoryStream::borrowWritable(
    void* source, size_t length, ThreadSafeRefPtr<Ref> owner)
{
    using R = Result<ThreadSafeRefPtr<MemoryStream>>;
    auto buffer = MemoryBuffer::borrow(source, length, std::move(owner));
    if (!buffer)
        return R::failure(buffer.error);
    try
    {
        auto stream = makeThreadSafeRef<MemoryStream>();
        buffer.value->_writable = true;
        buffer.value->_writableData = static_cast<uint8_t*>(source);
        stream->_mutable = buffer.value.get();
        stream->_buffer = std::move(buffer.value);
        return R::success(std::move(stream));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
}

Capability MemoryStream::capabilities() const noexcept
{
    if (!_buffer)
        return Capability::None;
    auto result = Capability::Read | Capability::Seek;
    if (_mutable)
        result = result | Capability::Write;
    if (_mutable && _mutable->_resizable)
        result = result | Capability::Resize;
    return result;
}

IoResult MemoryStream::read(void* destination, size_t length)
{
    if (!_buffer)
        return IoResult::failure({ErrorCode::Closed});
    if (!length)
        return IoResult::success(0);
    if (!destination)
        return IoResult::failure({ErrorCode::InvalidArgument});
    const auto available = _position < static_cast<int64_t>(_buffer->size())
                               ? _buffer->size() - static_cast<size_t>(_position) : 0;
    const auto count = std::min(length, available);
    if (count)
        std::memmove(destination, _buffer->data() + static_cast<size_t>(_position), count);
    _position += static_cast<int64_t>(count);
    return {count, count == length ? IoStatus::Ok : IoStatus::EndOfStream, {}};
}

IoResult MemoryStream::write(const void* source, size_t length)
{
    if (!_buffer)
        return IoResult::failure({ErrorCode::Closed});
    if (!_mutable)
        return IoResult::failure({ErrorCode::PermissionDenied});
    if (!length)
        return IoResult::success(0);
    if (!source)
        return IoResult::failure({ErrorCode::InvalidArgument});
    if (static_cast<uint64_t>(length) > static_cast<uint64_t>(std::numeric_limits<int64_t>::max() - _position))
        return IoResult::failure({ErrorCode::Overflow});

    size_t count = length;
    if (_mutable->_resizable)
    {
        if (static_cast<uint64_t>(_position) + length > _mutable->_maxCapacity)
            return IoResult::failure({ErrorCode::LimitExceeded});
    }
    else
    {
        const auto remaining = _position < static_cast<int64_t>(_buffer->size())
                                   ? _buffer->size() - static_cast<size_t>(_position) : 0;
        count = std::min(length, remaining);
    }

    // An input alias must be preserved across vector reallocation. uintptr_t
    // comparisons avoid ordering or subtracting pointers to unrelated objects.
    const auto sourceAddress = reinterpret_cast<uintptr_t>(source);
    const auto beginAddress = reinterpret_cast<uintptr_t>(_buffer->data());
    const auto oldSize = _buffer->size();
    const bool sourceInside = oldSize && sourceAddress >= beginAddress && sourceAddress - beginAddress < oldSize;
    if (sourceInside && count > oldSize - static_cast<size_t>(sourceAddress - beginAddress))
        return IoResult::failure({ErrorCode::InvalidArgument});
    const bool overlaps = count && oldSize &&
        (sourceAddress <= beginAddress ? beginAddress - sourceAddress < count : sourceAddress - beginAddress < oldSize);
    const auto target = static_cast<uint64_t>(_position) + count;
    std::vector<uint8_t> saved;
    if (overlaps && target > oldSize)
    {
        try
        {
            saved.resize(count);
            std::memcpy(saved.data(), source, count);
            source = saved.data();
        }
        catch (const std::bad_alloc&) { return IoResult::failure({ErrorCode::OutOfMemory}); }
        catch (const std::length_error&) { return IoResult::failure({ErrorCode::LimitExceeded}); }
    }
    if (target > oldSize)
    {
        auto resized = resize(static_cast<int64_t>(target));
        if (!resized)
            return IoResult::failure(resized.error);
    }
    if (count)
    {
        auto data = _mutable->_borrowed ? _mutable->_writableData : _mutable->_owned.data();
        std::memmove(data + static_cast<size_t>(_position), source, count);
        _position += static_cast<int64_t>(count);
    }
    return count == length ? IoResult::success(count) : IoResult::failure({ErrorCode::NoSpace}, count);
}

Result<int64_t> MemoryStream::tell() const
{
    return _buffer ? Result<int64_t>::success(_position) : Result<int64_t>::failure({ErrorCode::Closed});
}

Result<std::optional<int64_t>> MemoryStream::size() const
{
    using R = Result<std::optional<int64_t>>;
    return _buffer ? R::success(static_cast<int64_t>(_buffer->size())) : R::failure({ErrorCode::Closed});
}

Status MemoryStream::seek(SeekOrigin origin, int64_t offset)
{
    if (!_buffer)
        return Status::failure({ErrorCode::Closed});
    auto target = detail::seekTarget(origin, offset, _position, static_cast<int64_t>(_buffer->size()),
                                     _mutable && _mutable->_resizable);
    if (!target)
        return Status::failure(target.error);
    _position = target.value;
    return Status::success();
}

Status MemoryStream::resize(int64_t length)
{
    if (!_buffer)
        return Status::failure({ErrorCode::Closed});
    if (!_mutable || !_mutable->_resizable)
        return Status::failure({ErrorCode::NotSupported});
    if (length < 0)
        return Status::failure({ErrorCode::InvalidArgument});
    if (static_cast<uint64_t>(length) > _mutable->_maxCapacity)
        return Status::failure({ErrorCode::LimitExceeded});
    try
    {
        const auto count = static_cast<size_t>(length);
        if (count > _mutable->_owned.capacity())
        {
            // Allocate exact-size storage rather than vector's growth heuristic,
            // so its spare capacity cannot silently exceed the configured limit.
            std::vector<uint8_t> replacement(count, 0);
            if (replacement.capacity() > _mutable->_maxCapacity)
                return Status::failure({ErrorCode::LimitExceeded});
            std::copy(_mutable->_owned.begin(), _mutable->_owned.end(), replacement.begin());
            _mutable->_owned.swap(replacement);
        }
        else
            _mutable->_owned.resize(count, 0);
        if (_position > length)
            _position = length;
        return Status::success();
    }
    catch (const std::bad_alloc&) { return Status::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return Status::failure({ErrorCode::LimitExceeded}); }
}

Status MemoryStream::reserve(size_t capacity)
{
    if (!_buffer)
        return Status::failure({ErrorCode::Closed});
    if (!_mutable || !_mutable->_resizable)
        return Status::failure({ErrorCode::NotSupported});
    if (capacity > _mutable->_maxCapacity)
        return Status::failure({ErrorCode::LimitExceeded});
    if (capacity <= _buffer->capacity())
        return Status::success();
    try
    {
        std::vector<uint8_t> replacement;
        replacement.reserve(capacity);
        if (replacement.capacity() > _mutable->_maxCapacity)
            return Status::failure({ErrorCode::LimitExceeded});
        replacement.assign(_mutable->_owned.begin(), _mutable->_owned.end());
        _mutable->_owned.swap(replacement);
        return Status::success();
    }
    catch (const std::bad_alloc&) { return Status::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return Status::failure({ErrorCode::LimitExceeded}); }
}

Result<ThreadSafeRefPtr<const MemoryBuffer>> MemoryStream::freeze()
{
    using R = Result<ThreadSafeRefPtr<const MemoryBuffer>>;
    if (!_buffer)
        return R::failure({ErrorCode::Closed});
    if (_mutable)
    {
        _mutable->_writable = false;
        _mutable->_resizable = false;
        _mutable->_writableData = nullptr;
        _mutable = nullptr;
    }
    _position = std::min(_position, static_cast<int64_t>(_buffer->size()));
    return R::success(_buffer);
}

Status MemoryStream::close()
{
    _mutable = nullptr;
    _buffer.reset();
    _position = 0;
    return Status::success();
}
}
