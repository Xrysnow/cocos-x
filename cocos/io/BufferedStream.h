#pragma once
#include "io/Stream.h"

namespace cocos2d::io
{
// Owns cursor access to source for its lifetime. Do not access source directly
// while wrapped. Append streams always write through; writeCapacity is retained
// as configuration but does not allocate an append write buffer.
class CC_DLL BufferedStream final : public Stream
{
public:
    static Result<ThreadSafeRefPtr<BufferedStream>> create(StreamPtr source, BufferOptions options = {});

    explicit BufferedStream(RefConstructionToken token) : Stream(token) {}
    ~BufferedStream() override;

    Capability capabilities() const noexcept override { return _capabilities; }
    bool isOpen() const noexcept override;
    IoResult read(void* destination, size_t length) override;
    IoResult write(const void* source, size_t length) override;
    Result<int64_t> tell() const override;
    Result<std::optional<int64_t>> size() const override;
    Status seek(SeekOrigin origin, int64_t offset) override;
    Status resize(int64_t length) override;
    Status flush() override;
    Status sync() override;
    Status close() override;
    const void* cursorIdentity() const noexcept override;

    BufferOptions getBufferOptions() const noexcept { return _options; }
    // Requires the same external synchronization as read/write. A failed change
    // keeps the old capacities and all unsubmitted/unconsumed data.
    Status setBufferOptions(BufferOptions options);

private:
    Status init(StreamPtr source, BufferOptions options);
    Status checkOpen() const;
    Status seekBackend(int64_t target);
    Status alignReadPosition();
    Status drainWrites();
    Status ensureBuffer(std::vector<uint8_t>& buffer, size_t capacity);
    Status observeWritePosition(size_t transferred);
    void clearReadBuffer() noexcept;
    StreamError failBackend();

    StreamPtr _source;
    Capability _capabilities = Capability::None;
    BufferOptions _options{};
    bool _open = false;
    StreamError _fault{};
    Status _closeResult{};
    int64_t _position = 0;
    int64_t _backendPosition = 0;

    std::vector<uint8_t> _readBuffer;
    int64_t _readStart = 0;
    size_t _readCount = 0;
    size_t _readIndex = 0;
    IoResult _readTerminal{};

    std::vector<uint8_t> _writeBuffer;
    int64_t _writeStart = 0;
    size_t _writeCount = 0;
};
}
