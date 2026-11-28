#pragma once

#include "../GamepadBackend.h"
#include "haptics/private/HapticControl.h"

namespace cc::input {

struct HapticPlayback::Session {
    AudioDirectPlayback audio;
    mutable std::mutex gainMutex;
    float intensity = 1, strength = 1;
    DeviceId device;
    detail::EndpointKey hid;
    AudioEndpointId endpoint;
    detail::OutputRouter* router;
    std::weak_ptr<int> lifetime;
    std::atomic<HapticStopReason> stopReason{HapticStopReason::None};
    std::weak_ptr<haptics::detail::PcmSource> managed;
    Session(AudioDirectPlayback audio, DeviceId device, detail::EndpointKey hid, AudioEndpointId endpoint,
            detail::OutputRouter* router, std::weak_ptr<int> lifetime)
        : audio(std::move(audio)),device(device),hid(hid),endpoint(endpoint),router(router),lifetime(std::move(lifetime)) {}
};

namespace detail {
Error mapAudioError(AudioOutputError error);
}

} // namespace cc::input
