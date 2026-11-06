#pragma once
#include "audio/AudioStream.h"
#include "io/Stream.h"

NS_CC_BEGIN

// An owned Atomic adapter. It does not change legacy autoreleased factories.
class CC_DLL AudioStreamAdapter final : public AudioStream
{
public:
    AudioStreamAdapter(RefConstructionToken token, io::StreamPtr stream);
    static io::Result<ThreadSafeRefPtr<AudioStreamAdapter>> create(io::StreamPtr stream);

    uint64_t size() override;
    uint64_t tell() override;
    bool seek(SeekOrigin origin, int64_t offset) override;
    bool read(uint8_t* destination, uint64_t length, uint64_t* bytesRead = nullptr) override;
    void lock() override;
    void unlock() override;
    const io::IoResult& lastResult() const noexcept { return _lastResult; }

private:
    bool fail(io::StreamError error);
    io::StreamPtr _stream;
    io::IoResult _lastResult{};
    bool _failed = false;
};

NS_CC_END
