#pragma once
#include "audio/AudioStream.h"
#include "io/Stream.h"

NS_CC_BEGIN

// An owned Atomic adapter. It does not change legacy autoreleased factories.
class CC_DLL AudioStreamAdapter final : public AudioStream
{
public:
    AudioStreamAdapter(RefConstructionToken token, io::StreamPtr stream);
    AudioStreamAdapter(RefConstructionToken token, io::StreamPtr stream, ReopenFactory reopen);
    static io::Result<ThreadSafeRefPtr<AudioStreamAdapter>> create(io::StreamPtr stream);
    static io::Result<ThreadSafeRefPtr<AudioStreamAdapter>> create(io::StreamPtr stream, ReopenFactory reopen);

    uint64_t size() override;
    uint64_t tell() override;
    bool seek(SeekOrigin origin, int64_t offset) override;
    bool read(uint8_t* destination, uint64_t length, uint64_t* bytesRead = nullptr) override;
    void lock() override;
    void unlock() override;
    ReopenFactory getReopenFactory() const override { return _reopen; }
    bool hasIoError() const noexcept override { return _failed; }
    const io::IoResult& lastResult() const noexcept { return _lastResult; }

private:
    bool fail(io::StreamError error);
    io::StreamPtr _stream;
    ReopenFactory _reopen;
    io::IoResult _lastResult{};
    bool _failed = false;
};

NS_CC_END
