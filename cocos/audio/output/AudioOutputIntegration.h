#pragma once

#include "audio/AudioDirectPlayback.h"

namespace cc {

class AudioSource;

namespace audio::detail {

struct OutputIdentity {
    AudioEndpointId id;
    std::string containerId;
    std::string usbPath;
    bool supportsBodyOutput;
};

AudioResult<std::vector<OutputIdentity>> enumOutputIdentities();
AudioOutputError reserveManagedOutput(AudioEndpointId endpoint);
AudioOutputError registerManagedOutput(AudioEndpointId endpoint);
AudioResult<AudioDirectPlayback> createManagedPlayback(AudioSource& source, AudioEndpointId endpoint);
AudioOutputError setManagedPlaybackEnabled(AudioDirectPlayback& playback, bool enabled);
void requireManagedStopEvidence(AudioDirectPlayback& playback);
void failManagedPlayback(AudioDirectPlayback& playback, AudioOutputError error);

bool requiresFrontStereo(const std::string& mainDeviceName, bool useDefault);
std::string managedDefaultDeviceName();
void shutdownDirectOutput() noexcept;

} // namespace audio::detail
} // namespace cc
