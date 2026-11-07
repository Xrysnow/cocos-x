#pragma once
#include "platform/CCPlatformMacros.h"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <utility>

namespace cocos2d::io
{
enum class SeekOrigin { Begin, Current, End };
enum class Capability : uint32_t
{
    None = 0, Read = 1, Write = 2, Seek = 4, Resize = 8, Sync = 16, Append = 32
};
constexpr Capability operator|(Capability a, Capability b) noexcept
{
    return static_cast<Capability>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
constexpr Capability operator&(Capability a, Capability b) noexcept
{
    return static_cast<Capability>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
constexpr bool hasCapability(Capability value, Capability required) noexcept
{
    return (value & required) == required;
}
enum class ErrorCode
{
    None, InvalidArgument, Closed, NotSupported, PermissionDenied, NotFound,
    AlreadyExists, OutOfRange, Overflow, NoSpace, OutOfMemory, IoError,
    NoProgress, LimitExceeded, InvalidBackend, WouldBlock, Cancelled, Timeout
};
enum class ErrorDomain { None, Errno, Win32, Curl, CurlMulti, Http };
struct StreamError
{
    ErrorCode code = ErrorCode::None;
    int nativeCode = 0;
    ErrorDomain domain = ErrorDomain::None;
    explicit operator bool() const noexcept { return code != ErrorCode::None; }
};
template<class T>
struct Result
{
    T value{};
    StreamError error{};
    explicit operator bool() const noexcept { return !error; }
    static Result success(T value) { return {std::move(value), {}}; }
    static Result failure(StreamError error) { return {T{}, error}; }
};
template<>
struct Result<void>
{
    StreamError error{};
    explicit operator bool() const noexcept { return !error; }
    static Result success() { return {}; }
    static Result failure(StreamError error) { return {error}; }
};
using Status = Result<void>;
enum class IoStatus { Ok, EndOfStream, WouldBlock, Cancelled, Timeout, Error };
struct IoResult
{
    size_t transferred = 0;
    IoStatus status = IoStatus::Ok;
    StreamError error{};
    explicit operator bool() const noexcept { return status == IoStatus::Ok; }
    static IoResult success(size_t count) { return {count, IoStatus::Ok, {}}; }
    static IoResult failure(StreamError error, size_t count = 0)
    {
        return {count, IoStatus::Error, error};
    }
};
struct CopyResult
{
    uint64_t consumed = 0;
    uint64_t transferred = 0;
    IoStatus status = IoStatus::Ok;
    StreamError error{};
    explicit operator bool() const noexcept { return status == IoStatus::Ok; }
};
struct BufferOptions
{
    size_t readCapacity = 64 * 1024;
    size_t writeCapacity = 64 * 1024;
};
}
