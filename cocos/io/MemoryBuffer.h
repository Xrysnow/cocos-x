#pragma once
#include "base/CCRefPtr.h"
#include "io/StreamTypes.h"
#include <limits>
#include <vector>

namespace cocos2d::io
{
class MemoryStream;

// Shared buffers are immutable. Mutable storage is private to one MemoryStream;
// freeze() publishes it only after disabling writes through that stream.
class CC_DLL MemoryBuffer final : public Ref
{
public:
    explicit MemoryBuffer(RefConstructionToken token);
    static constexpr size_t MaxSize = static_cast<size_t>(std::numeric_limits<int64_t>::max());

    static Result<ThreadSafeRefPtr<MemoryBuffer>> copy(const void* source, size_t length);
    static Result<ThreadSafeRefPtr<MemoryBuffer>> move(std::vector<uint8_t> bytes);
    // The caller must keep borrowed storage immutable and alive. An optional
    // owner extends its lifetime, but cannot prevent external mutable aliases.
    static Result<ThreadSafeRefPtr<MemoryBuffer>> borrow(
        const void* source, size_t length, ThreadSafeRefPtr<Ref> owner = {});

    const uint8_t* data() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

private:
    friend class MemoryStream;
    std::vector<uint8_t> _owned;
    const uint8_t* _borrowedData = nullptr;
    uint8_t* _writableData = nullptr;
    size_t _borrowedSize = 0;
    size_t _maxCapacity = MaxSize;
    bool _borrowed = false;
    bool _writable = false;
    bool _resizable = false;
    ThreadSafeRefPtr<Ref> _owner;
};
}
