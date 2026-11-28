#pragma once

#include "audio/AudioDirectPlayback.h"

#include <array>
#include <atomic>
#include <cstddef>

namespace cc::audio::detail {

inline constexpr unsigned outputBlockFrames = 256;
inline constexpr unsigned outputQueueBlocks = 8;
inline constexpr unsigned realtimeSampleRate = 48000;
inline constexpr unsigned realtimePrefillFrames = 512;
inline constexpr unsigned realtimeQueueFrames = 768;
inline constexpr unsigned realtimeMaxQuantumFrames = realtimePrefillFrames;
inline constexpr std::uint64_t realtimeClockTimeoutNs = 100'000'000;
inline constexpr std::uint64_t realtimeMaxTailNs = 200'000'000;
inline constexpr std::array realtimeChannels{AudioChannelPosition::FrontLeft, AudioChannelPosition::FrontRight,
                                             AudioChannelPosition::RearLeft, AudioChannelPosition::RearRight};

inline std::uint64_t nextRealtimeClockGeneration()
{
    static std::atomic_uint64_t generation{0};
    return ++generation;
}

inline bool validRealtimeBlock(const std::int16_t* pcm, std::size_t frames, bool silenceOnly,
                               std::array<unsigned, 2> front = {0, 1})
{
    if (!pcm || frames != outputBlockFrames)
        return false;
    for (std::size_t i = 0; i < frames; ++i, pcm += realtimeChannels.size())
        if (pcm[front[0]] || pcm[front[1]] || (silenceOnly && (pcm[0] || pcm[1] || pcm[2] || pcm[3])))
            return false;
    return true;
}

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

struct RealtimeOutputClock {
    std::uint64_t generation = 0;
    std::uint64_t observedNs = 0;
    // Both device positions use the same 48 kHz presentation timeline.
    std::uint64_t deviceFrame = 0;
    std::uint64_t nextWriteFrame = 0;
    // Source PCM frames presented, estimated from a valid native timing sample.
    std::uint64_t consumedFrames = 0;
};

struct RealtimeOutputProgress {
    unsigned queuedFrames = 0;
    unsigned availableBlocks = 0;
    std::optional<RealtimeOutputClock> clock;
};

struct RealtimeOutputStop {
    std::uint64_t generation = 0;
    // Exclusive presentation-frame bound for all output from this generation.
    std::uint64_t lastPossibleDeviceFrame = 0;
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
    virtual void setRealtimeGate(std::shared_ptr<const std::atomic_bool>) {}
    // Local queue capacity excludes native graph and hardware tail latency.
    virtual AudioResult<RealtimeOutputProgress> pollRealtime() { return AudioOutputError::Unsupported; }
    // Permanently close the producer and wait for native stop evidence.
    virtual AudioResult<RealtimeOutputStop> discardRealtime() { return AudioOutputError::Unsupported; }
};

AudioResult<std::vector<DirectEndpoint>> enumeratePlatformEndpoints();
AudioResult<std::unique_ptr<OutputStream>> openPlatformOutput(const DirectEndpoint& endpoint);
AudioResult<std::unique_ptr<OutputStream>> openPlatformRealtimeOutput(const DirectEndpoint& endpoint);
void shutdownPlatformOutput() noexcept;

} // namespace cc::audio::detail
