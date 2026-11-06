#include "io/Stream.h"
#include <algorithm>
#include <limits>
#include <new>
#include <stdexcept>

namespace cocos2d::io
{
namespace
{
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

StreamError statusError(const IoResult& result)
{
    switch (result.status)
    {
    case IoStatus::WouldBlock: return {ErrorCode::WouldBlock};
    case IoStatus::Cancelled: return {ErrorCode::Cancelled};
    case IoStatus::Timeout: return {ErrorCode::Timeout};
    case IoStatus::Error: return result.error;
    default: return {};
    }
}
}

Stream::Stream(RefConstructionToken token) : Ref(token)
{
    if (getReferenceThreading() != RefThreading::Atomic)
        throw std::invalid_argument("Stream requires Atomic reference counting");
}

IoResult Stream::write(const void*, size_t)
{
    return IoResult::failure({isOpen() ? ErrorCode::NotSupported : ErrorCode::Closed});
}

Status Stream::resize(int64_t)
{
    return Status::failure({isOpen() ? ErrorCode::NotSupported : ErrorCode::Closed});
}

Status Stream::flush()
{
    return isOpen() ? Status::success() : Status::failure({ErrorCode::Closed});
}

Status Stream::sync()
{
    return Status::failure({isOpen() ? ErrorCode::NotSupported : ErrorCode::Closed});
}

IoResult Stream::readExact(void* destination, size_t length)
{
    if (!isOpen())
        return IoResult::failure({ErrorCode::Closed});
    if (!hasCapability(capabilities(), Capability::Read))
        return IoResult::failure({ErrorCode::NotSupported});
    if (length && !destination)
        return IoResult::failure({ErrorCode::InvalidArgument});
    size_t total = 0;
    do
    {
        const auto remaining = length - total;
        auto result = read(length ? static_cast<uint8_t*>(destination) + total : destination, remaining);
        if (auto error = validateTransfer(result, remaining, false))
            return IoResult::failure(error, total);
        total += result.transferred;
        if (result.status != IoStatus::Ok)
            return {total, result.status, result.error};
    } while (total < length);
    return IoResult::success(total);
}

IoResult Stream::writeAll(const void* source, size_t length)
{
    if (!isOpen())
        return IoResult::failure({ErrorCode::Closed});
    if (!hasCapability(capabilities(), Capability::Write))
        return IoResult::failure({ErrorCode::NotSupported});
    if (length && !source)
        return IoResult::failure({ErrorCode::InvalidArgument});
    size_t total = 0;
    do
    {
        const auto remaining = length - total;
        auto result = write(length ? static_cast<const uint8_t*>(source) + total : source, remaining);
        if (auto error = validateTransfer(result, remaining, true))
            return IoResult::failure(error, total);
        total += result.transferred;
        if (result.status != IoStatus::Ok)
            return {total, result.status, result.error};
    } while (total < length);
    return IoResult::success(total);
}

CopyResult Stream::copyTo(Stream& destination, uint64_t length, size_t bufferSize)
{
    CopyResult result;
    const auto fail = [&result](StreamError error) {
        result.status = IoStatus::Error;
        result.error = error;
        return result;
    };
    if (cursorIdentity() == destination.cursorIdentity() || !bufferSize)
        return fail({ErrorCode::InvalidArgument});
    if (!isOpen() || !destination.isOpen())
        return fail({ErrorCode::Closed});
    if (!hasCapability(capabilities(), Capability::Read) ||
        !hasCapability(destination.capabilities(), Capability::Write))
        return fail({ErrorCode::NotSupported});
    if (!length)
        return result;
    try
    {
        std::vector<uint8_t> buffer(static_cast<size_t>(std::min<uint64_t>(length, bufferSize)));
        while (result.consumed < length)
        {
            const auto requested = static_cast<size_t>(std::min<uint64_t>(length - result.consumed, buffer.size()));
            auto input = read(buffer.data(), requested);
            if (auto error = validateTransfer(input, requested, false))
                return fail(error);
            result.consumed += input.transferred;
            if (input.transferred)
            {
                const auto output = destination.writeAll(buffer.data(), input.transferred);
                result.transferred += output.transferred;
                if (output.status != IoStatus::Ok)
                {
                    result.status = output.status;
                    result.error = output.error;
                    return result;
                }
            }
            if (input.status != IoStatus::Ok)
            {
                result.status = input.status;
                result.error = input.error;
                return result;
            }
        }
        return result;
    }
    catch (const std::bad_alloc&) { return fail({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return fail({ErrorCode::LimitExceeded}); }
}

Result<std::vector<uint8_t>> Stream::readAll(size_t maxBytes)
{
    Result<std::vector<uint8_t>> result;
    if (!isOpen())
    {
        result.error = {ErrorCode::Closed};
        return result;
    }
    if (!hasCapability(capabilities(), Capability::Read))
    {
        result.error = {ErrorCode::NotSupported};
        return result;
    }
    const auto initialSize = size();
    if (!initialSize)
    {
        result.error = initialSize.error;
        return result;
    }
    if (initialSize.value && *initialSize.value < 0)
    {
        result.error = {ErrorCode::InvalidBackend};
        return result;
    }
    try
    {
        while (result.value.size() < maxBytes)
        {
            const auto oldSize = result.value.size();
            const auto requested = std::min(maxBytes - oldSize, size_t{64 * 1024});
            result.value.resize(oldSize + requested);
            const auto input = read(result.value.data() + oldSize, requested);
            if (auto error = validateTransfer(input, requested, false))
            {
                result.value.resize(oldSize);
                result.error = error;
                return result;
            }
            result.value.resize(oldSize + input.transferred);
            if (input.status == IoStatus::EndOfStream)
                return result;
            if (input.status != IoStatus::Ok)
            {
                result.error = statusError(input);
                return result;
            }
        }
        // A bounded read must never consume an extra byte to probe EOF. Known
        // length can establish completion; an unknown length cannot.
        const auto currentSize = size();
        if (!currentSize)
            result.error = currentSize.error;
        else if (currentSize.value)
        {
            const auto position = tell();
            if (!position)
                result.error = position.error;
            else if (position.value < 0 || *currentSize.value < 0)
                result.error = {ErrorCode::InvalidBackend};
            else if (position.value < *currentSize.value)
                result.error = {ErrorCode::LimitExceeded};
        }
        else
            result.error = {ErrorCode::LimitExceeded};
        return result;
    }
    catch (const std::bad_alloc&)
    {
        result.error = {ErrorCode::OutOfMemory};
        return result;
    }
    catch (const std::length_error&)
    {
        result.error = {ErrorCode::LimitExceeded};
        return result;
    }
}

namespace detail
{
Result<int64_t> seekTarget(SeekOrigin origin, int64_t offset, int64_t position,
                           std::optional<int64_t> length, bool allowBeyondEnd)
{
    using R = Result<int64_t>;
    if (position < 0 || (length && *length < 0))
        return R::failure({ErrorCode::InvalidBackend});
    int64_t base = 0;
    switch (origin)
    {
    case SeekOrigin::Begin: break;
    case SeekOrigin::Current: base = position; break;
    case SeekOrigin::End:
        if (!length)
            return R::failure({ErrorCode::NotSupported});
        base = *length;
        break;
    default: return R::failure({ErrorCode::InvalidArgument});
    }
    if (offset < -base)
        return R::failure({ErrorCode::OutOfRange});
    if (offset > std::numeric_limits<int64_t>::max() - base)
        return R::failure({ErrorCode::Overflow});
    const auto target = base + offset;
    if (!allowBeyondEnd && length && target > *length)
        return R::failure({ErrorCode::OutOfRange});
    return R::success(target);
}
}
}
