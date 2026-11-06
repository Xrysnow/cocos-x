#include "io/MemoryBuffer.h"
#include <cstring>
#include <new>
#include <stdexcept>

namespace cocos2d::io
{
MemoryBuffer::MemoryBuffer(RefConstructionToken token) : Ref(token)
{
    if (getReferenceThreading() != RefThreading::Atomic)
        throw std::invalid_argument("MemoryBuffer requires Atomic reference counting");
}

Result<ThreadSafeRefPtr<MemoryBuffer>> MemoryBuffer::copy(const void* source, size_t length)
{
    using R = Result<ThreadSafeRefPtr<MemoryBuffer>>;
    if (length > MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (length && !source)
        return R::failure({ErrorCode::InvalidArgument});
    try
    {
        auto buffer = makeThreadSafeRef<MemoryBuffer>();
        buffer->_owned.resize(length);
        if (length)
            std::memcpy(buffer->_owned.data(), source, length);
        return R::success(std::move(buffer));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return R::failure({ErrorCode::LimitExceeded}); }
}

Result<ThreadSafeRefPtr<MemoryBuffer>> MemoryBuffer::move(std::vector<uint8_t> bytes)
{
    using R = Result<ThreadSafeRefPtr<MemoryBuffer>>;
    if (bytes.size() > MaxSize || bytes.capacity() > MaxSize)
        return R::failure({ErrorCode::Overflow});
    try
    {
        auto buffer = makeThreadSafeRef<MemoryBuffer>();
        buffer->_owned = std::move(bytes);
        return R::success(std::move(buffer));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
}

Result<ThreadSafeRefPtr<MemoryBuffer>> MemoryBuffer::borrow(
    const void* source, size_t length, ThreadSafeRefPtr<Ref> owner)
{
    using R = Result<ThreadSafeRefPtr<MemoryBuffer>>;
    if (length > MaxSize)
        return R::failure({ErrorCode::Overflow});
    if (length && !source)
        return R::failure({ErrorCode::InvalidArgument});
    try
    {
        auto buffer = makeThreadSafeRef<MemoryBuffer>();
        buffer->_borrowed = true;
        buffer->_borrowedData = static_cast<const uint8_t*>(source);
        buffer->_borrowedSize = length;
        buffer->_maxCapacity = length;
        buffer->_owner = std::move(owner);
        return R::success(std::move(buffer));
    }
    catch (const std::bad_alloc&) { return R::failure({ErrorCode::OutOfMemory}); }
}

const uint8_t* MemoryBuffer::data() const noexcept
{
    return _borrowed ? _borrowedData : _owned.data();
}

size_t MemoryBuffer::size() const noexcept
{
    return _borrowed ? _borrowedSize : _owned.size();
}

size_t MemoryBuffer::capacity() const noexcept
{
    return _borrowed ? _borrowedSize : _owned.capacity();
}
}
