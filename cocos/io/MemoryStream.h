#pragma once
#include "io/MemoryBuffer.h"
#include "io/Stream.h"

namespace cocos2d::io
{
class CC_DLL MemoryStream final : public Stream
{
public:
    explicit MemoryStream(RefConstructionToken token) : Stream(token) {}

    static Result<ThreadSafeRefPtr<MemoryStream>> create(
        size_t initialSize = 0, size_t maxCapacity = MemoryBuffer::MaxSize);
    static Result<ThreadSafeRefPtr<MemoryStream>> copy(
        const void* source, size_t length, bool writable = true,
        size_t maxCapacity = MemoryBuffer::MaxSize);
    static Result<ThreadSafeRefPtr<MemoryStream>> move(
        std::vector<uint8_t> bytes, bool writable = true,
        size_t maxCapacity = MemoryBuffer::MaxSize);
    static Result<ThreadSafeRefPtr<MemoryStream>> fromBuffer(ThreadSafeRefPtr<const MemoryBuffer> buffer);
    static Result<ThreadSafeRefPtr<MemoryStream>> borrow(
        const void* source, size_t length, ThreadSafeRefPtr<Ref> owner = {});
    static Result<ThreadSafeRefPtr<MemoryStream>> borrowWritable(
        void* source, size_t length, ThreadSafeRefPtr<Ref> owner = {});

    Capability capabilities() const noexcept override;
    bool isOpen() const noexcept override { return static_cast<bool>(_buffer); }
    IoResult read(void* destination, size_t length) override;
    IoResult write(const void* source, size_t length) override;
    Result<int64_t> tell() const override;
    Result<std::optional<int64_t>> size() const override;
    Status seek(SeekOrigin origin, int64_t offset) override;
    Status resize(int64_t length) override;
    Status close() override;
    Status reserve(size_t capacity);

    // Views are invalidated by storage growth or close. They do not grant writes.
    const uint8_t* data() const noexcept { return _buffer ? _buffer->data() : nullptr; }
    size_t capacity() const noexcept { return _buffer ? _buffer->capacity() : 0; }
    // Permanently disables writes and clamps a cursor beyond EOF. For borrowed
    // memory, callers must also stop modifying all external aliases.
    Result<ThreadSafeRefPtr<const MemoryBuffer>> freeze();

private:
    static Result<ThreadSafeRefPtr<MemoryStream>> fromOwned(
        ThreadSafeRefPtr<MemoryBuffer> buffer, bool writable, size_t maxCapacity);
    ThreadSafeRefPtr<const MemoryBuffer> _buffer;
    MemoryBuffer* _mutable = nullptr;
    int64_t _position = 0;
};
}
