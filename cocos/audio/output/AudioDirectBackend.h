#pragma once

#include "audio/AudioDirectPlayback.h"
#include <cstddef>

namespace cc::audio::detail {

inline constexpr unsigned outputBlockFrames = 256;
inline constexpr unsigned outputQueueBlocks = 8;

struct DirectEndpoint {
    std::string key;
    std::string name;
    std::string mainDeviceName;
    std::string deviceSelector;
    std::string containerId;
    std::string usbPath;
    bool isDefault = false;
    unsigned sampleRate = 0;
    std::vector<AudioChannelPosition> channels;
    bool canRoute = true;
};

struct OutputProgress {
    std::uint64_t consumedFrames = 0;
    unsigned availableBlocks = 0;
    bool drained = false;
};

// One bounded stream per playback. All calls, including destruction, run on
// its output thread. Starts inactive and counts only consumed source PCM.
class OutputStream {
public:
    virtual ~OutputStream() = default;
    virtual AudioOutputError submit(const std::int16_t* pcm, std::size_t frames) = 0;
    virtual AudioOutputError setPaused(bool paused) = 0;
    virtual AudioOutputError drain() = 0;
    // Stop sample production and wait for the last possible device sample.
    virtual AudioOutputError stopWithEvidence() { return AudioOutputError::Unsupported; }
    virtual AudioResult<OutputProgress> poll() = 0;
};

AudioResult<std::vector<DirectEndpoint>> enumeratePlatformEndpoints();
AudioResult<std::unique_ptr<OutputStream>> openPlatformOutput(const DirectEndpoint& endpoint);
void shutdownPlatformOutput() noexcept;

} // namespace cc::audio::detail
