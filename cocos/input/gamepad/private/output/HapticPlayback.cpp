#include "HapticPlaybackSession.h"
#include "OutputRouter.h"

#include <cmath>

namespace cc::input {

Error detail::mapAudioError(AudioOutputError error)
{
    switch (error)
    {
    case AudioOutputError::None: return Error::None;
    case AudioOutputError::InvalidArgument: return Error::InvalidArgument;
    case AudioOutputError::Unsupported: return Error::Unsupported;
    case AudioOutputError::Disconnected: return Error::Disconnected;
    case AudioOutputError::ChannelManaged:
    case AudioOutputError::Busy: return Error::Busy;
    case AudioOutputError::QueueFull: return Error::QueueFull;
    case AudioOutputError::BackendFailure: return Error::BackendFailure;
    }
    return Error::BackendFailure;
}

HapticPlayback::HapticPlayback(std::shared_ptr<Session> session) : _session(std::move(session)) {}
HapticPlayback::HapticPlayback(HapticPlayback&&) noexcept = default;

HapticPlayback& HapticPlayback::operator=(HapticPlayback&& other) noexcept
{
    if (this != &other)
    {
        close();
        _session = std::move(other._session);
    }
    return *this;
}

HapticPlayback::~HapticPlayback() { close(); }

Error HapticPlayback::play()
{
    if (!_session || _session->lifetime.expired())
        return Error::Disconnected;
    return _session->router->playHaptics(_session);
}

Error HapticPlayback::pause()
{
    return _session ? detail::mapAudioError(_session->audio.pause()) : Error::Disconnected;
}

Error HapticPlayback::resume()
{
    if (!_session || _session->lifetime.expired()) return Error::Disconnected;
    const auto state = _session->audio.snapshot();
    if (state.error != AudioOutputError::None) return detail::mapAudioError(state.error);
    if(state.state != AudioPlaybackState::Playing && state.state != AudioPlaybackState::Buffering &&
       state.state != AudioPlaybackState::Paused)return Error::InvalidArgument;
    if(auto port=_session->managed.lock(); port && !_session->router->_control.ownsPcm(_session->device,port))
        return Error::InvalidArgument;
    return detail::mapAudioError(_session->audio.resume());
}

Error HapticPlayback::stop()
{
    if (!_session || _session->lifetime.expired())
        return Error::Disconnected;
    return _session->router->stopHaptics(*_session, HapticStopReason::Requested);
}

Error HapticPlayback::seekTime(double seconds)
{
    return _session ? detail::mapAudioError(_session->audio.seekTime(seconds)) : Error::Disconnected;
}

Error HapticPlayback::setLooping(bool enabled)
{
    return _session ? detail::mapAudioError(_session->audio.setLooping(enabled)) : Error::Disconnected;
}

Error HapticPlayback::setIntensity(float intensity)
{
    if (!std::isfinite(intensity) || intensity < 0 || intensity > 1)
        return Error::InvalidArgument;
    return _session ? detail::mapAudioError(_session->audio.setGain(intensity)) : Error::Disconnected;
}

HapticPlaybackSnapshot HapticPlayback::snapshot() const
{
    if (!_session)
        return {};
    const auto snap = _session->audio.snapshot();
    const auto reason = snap.error == AudioOutputError::Disconnected &&
        _session->stopReason != HapticStopReason::Disconnected ? HapticStopReason::EndpointLost : _session->stopReason.load();
    return {snap.state, detail::mapAudioError(snap.error), snap.positionSeconds, snap.durationSeconds,
            snap.gain, snap.looping, snap.seekable, reason};
}

void HapticPlayback::close() noexcept
{
    if (!_session)
        return;
    if (!_session->lifetime.expired())
        _session->router->closeHaptics(*_session);
    _session->audio.close();
}

} // namespace cc::input
