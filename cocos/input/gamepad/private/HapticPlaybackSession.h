#pragma once

#include "GamepadBackend.h"

namespace cc::input {

struct HapticPlayback::Session {
    AudioDirectPlayback audio;
    DeviceId device;
    detail::EndpointKey hid;
    AudioEndpointId endpoint;
    detail::OutputRouter* router;
    std::weak_ptr<int> lifetime;
    HapticStopReason stopReason = HapticStopReason::None;
};

namespace detail {
Error mapAudioError(AudioOutputError error);
}

} // namespace cc::input
