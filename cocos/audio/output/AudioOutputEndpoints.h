#pragma once

#include "AudioDirectBackend.h"
#include <atomic>

namespace cc::audio::detail {

struct EndpointStatus {
    std::atomic<bool> connected{true};
    std::atomic<bool> rearManaged{false};
    std::atomic<bool> managedReady{false};
};

struct OutputEndpoint {
    AudioEndpointId id;
    DirectEndpoint platform;
    std::shared_ptr<EndpointStatus> status;
};

AudioResult<std::vector<OutputEndpoint>> refreshOutputEndpoints();
AudioResult<OutputEndpoint> findOutputEndpoint(AudioEndpointId id);
void invalidateOutputEndpoints();
bool hasManagedOutputEndpoints();
bool isRearChannel(AudioChannelPosition position);
bool hasBodyLayout(const DirectEndpoint& endpoint);

} // namespace cc::audio::detail
