#pragma once

#include "AudioDirectBackend.h"
#include "GripLimiter.h"
#include <chrono>
#include <mutex>
#include <atomic>

namespace cc::audio::detail {

// Both file and synthesized PCM use this history for the paired rear channels.
struct GripSafety {
    using Clock = std::chrono::steady_clock;
    std::mutex mutex;
    GripLimiter limiter;
    Clock::time_point nextOwner = Clock::now() + std::chrono::milliseconds(100);
    void discarded() {
        std::lock_guard lock(mutex);
        nextOwner = Clock::now() + std::chrono::milliseconds(100);
    }
    bool ready() {
        std::lock_guard lock(mutex);
        return Clock::now() >= nextOwner;
    }
};
struct EndpointStatus {
    std::atomic<bool> connected{true};
    std::atomic<bool> rearManaged{false};
    std::atomic<bool> managedReady{false};
    std::once_flag initializeGrip;
    std::shared_ptr<GripSafety> grip;  // Installed before publishing managedReady.
};

struct OutputEndpoint {
    AudioEndpointId id;
    DirectEndpoint platform;
    std::shared_ptr<EndpointStatus> status;
};

AudioResult<std::vector<OutputEndpoint>> refreshOutputEndpoints();
AudioResult<OutputEndpoint> findOutputEndpoint(AudioEndpointId id);
std::shared_ptr<GripSafety> gripSafetyFor(const DirectEndpoint& device);
void invalidateOutputEndpoints();
bool hasManagedOutputEndpoints();
bool isRearChannel(AudioChannelPosition position);
bool hasBodyLayout(const DirectEndpoint& endpoint);

} // namespace cc::audio::detail
