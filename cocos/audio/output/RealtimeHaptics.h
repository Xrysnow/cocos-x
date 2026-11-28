#pragma once
#include "audio/AudioDirectPlayback.h"
#include <array>
#include <atomic>
#include <functional>
#include <condition_variable>

namespace cc::audio::detail {
using GripBlock = std::array<std::array<float, 2>, 256>;
struct GripWindow {
    std::uint64_t firstFrame{};
    std::int64_t startUs{};
};
struct GripStreamTrace {
    unsigned peakQueuedFrames{};
    std::uint64_t generation{};
    std::optional<std::uint64_t> lastNonzeroFrame, discardBound;
    std::optional<std::int64_t> firstSubmitUs, discardUs;
};
struct GripProgress {
    bool prepared{};
    bool finished{};
    AudioOutputError error{};
    std::optional<GripWindow> window;
    GripStreamTrace trace;
};
// Methods are nonblocking except stop(), which joins the output thread and
// returns its discard evidence. Only that thread touches the platform stream.
class RealtimeHaptics {
public:
    virtual ~RealtimeHaptics() = default;
    virtual GripProgress poll() = 0;
    virtual void enable() = 0;
    virtual void supply(GripWindow window, std::function<GripBlock()> render,
                        std::function<void(AudioOutputError, bool)> submitted) = 0;
    virtual AudioOutputError stop() = 0;
};
std::shared_ptr<RealtimeHaptics> prepareRealtimeHaptics(AudioEndpointId endpoint,
                                                        std::shared_ptr<std::atomic_bool> permit,
                                                        std::condition_variable& controlWake);
} // namespace cc::audio::detail
