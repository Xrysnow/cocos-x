#pragma once
#include "base/CCRefPtr.h"
#include "io/StreamTypes.h"
#include <mutex>
#include <vector>

namespace cocos2d::io
{
class Stream;
using StreamPtr = ThreadSafeRefPtr<Stream>;

// Atomic ownership does not synchronize cursor operations. Lock complete I/O
// sequences when sharing a stream; operations never acquire this lock themselves.
class CC_DLL Stream : public Ref
{
public:
    virtual ~Stream() = default;
    virtual Capability capabilities() const noexcept = 0;
    virtual bool isOpen() const noexcept = 0;
    virtual IoResult read(void* destination, size_t length) = 0;
    virtual IoResult write(const void* source, size_t length);
    virtual Result<int64_t> tell() const = 0;
    virtual Result<std::optional<int64_t>> size() const = 0;
    virtual Status seek(SeekOrigin origin, int64_t offset) = 0;
    virtual Status resize(int64_t length);
    virtual Status flush();
    virtual Status sync();
    virtual Status close() = 0;

    virtual void lock() { _mutex.lock(); }
    virtual bool tryLock() { return _mutex.try_lock(); }
    virtual void unlock() { _mutex.unlock(); }
    // Wrappers must return their underlying cursor identity.
    virtual const void* cursorIdentity() const noexcept { return this; }

    IoResult readExact(void* destination, size_t length);
    IoResult writeAll(const void* source, size_t length);
    CopyResult copyTo(Stream& destination, uint64_t length, size_t bufferSize = 64 * 1024);
    // Partial data remains in value on failure; no byte is consumed beyond maxBytes.
    Result<std::vector<uint8_t>> readAll(size_t maxBytes);

protected:
    explicit Stream(RefConstructionToken token);

private:
    std::mutex _mutex;
};

class StreamLock final
{
public:
    explicit StreamLock(StreamPtr stream) : _stream(std::move(stream))
    {
        if (_stream)
            _stream->lock();
    }
    ~StreamLock()
    {
        if (_stream)
            _stream->unlock();
    }
    StreamLock(const StreamLock&) = delete;
    StreamLock& operator=(const StreamLock&) = delete;
private:
    StreamPtr _stream;
};

namespace detail
{
CC_DLL Result<int64_t> seekTarget(SeekOrigin origin, int64_t offset, int64_t position,
                                 std::optional<int64_t> length, bool allowBeyondEnd);
}
}
