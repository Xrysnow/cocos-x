#include "OutputRouter.h"
#include "HapticPlaybackSession.h"
#include "../PlatformGamepadBackend.h"
#include "audio/output/AudioOutputIntegration.h"

#include <algorithm>
#include <limits>

namespace cc::input::detail {
namespace {

AudioOutputError waveformError(Error error)
{
    switch (error)
    {
    case Error::Disconnected: return AudioOutputError::Disconnected;
    case Error::Busy:
    case Error::PermissionDenied: return AudioOutputError::Busy;
    case Error::Unsupported: return AudioOutputError::Unsupported;
    case Error::QueueFull: return AudioOutputError::QueueFull;
    default: return AudioOutputError::BackendFailure;
    }
}

bool matches(const HapticAudioIdentity& hid, const audio::detail::OutputIdentity& endpoint)
{
    const bool container = !hid.containerId.empty() && !endpoint.containerId.empty();
    const bool usb = !hid.usbPath.empty() && !endpoint.usbPath.empty();
    return (container || usb) && (!container || hid.containerId == endpoint.containerId) &&
           (!usb || hid.usbPath == endpoint.usbPath);
}

const audio::detail::OutputIdentity* pairedOutput(const HapticAudioIdentity& hid,
                                                   std::span<const audio::detail::OutputIdentity> outputs)
{
    const auto match = [&](const auto& endpoint) { return matches(hid, endpoint); };
    const auto paired = std::ranges::find_if(outputs, match);
    if (paired == outputs.end() || std::find_if(std::next(paired), outputs.end(), match) != outputs.end())
        return nullptr;
    return &*paired;
}

bool hasAudioIdentity(const Endpoint& endpoint)
{
    const auto& hid = endpoint.descriptor.hapticAudio;
    return !hid.containerId.empty() || !hid.usbPath.empty();
}

bool connectionLost(HapticStopReason reason)
{
    return reason == HapticStopReason::EndpointLost || reason == HapticStopReason::Disconnected;
}

} // namespace

void primeGamepadAudioPolicy()
{
#if defined(_WIN32) || (defined(__linux__) && !defined(__ANDROID__))
    const auto devices = connectedHapticAudioIdentities();
    if (devices.empty())
        return;
    const auto outputs = audio::detail::enumOutputIdentities();
    if (!outputs)
        return;
    for (const auto& device : devices)
        if (const auto* paired = pairedOutput(device, outputs.value()))
            audio::detail::reserveManagedOutput(paired->id);
#endif
}

Result<HapticPlayback> OutputRouter::createHapticPlayback(DeviceId id, AudioSource& source)
{
    const auto* device = _registry.find(id);
    if (!device)
        return {{}, Error::Disconnected};
    const auto route = _hapticRoutes.find(id);
    if (route == _hapticRoutes.end())
        return {{}, std::ranges::any_of(device->endpoints, [](const auto& entry) {
            return hasAudioIdentity(entry.second) && !entry.second.descriptor.hapticAudio.writable;
        }) ? Error::Busy : Error::Unsupported};
    auto playback = audio::detail::createManagedPlayback(source, route->second.endpoint);
    if (!playback)
        return {{}, mapAudioError(playback.error())};
    auto session = std::make_shared<HapticSession>(std::move(playback).value(), id,
        route->second.hid, route->second.endpoint, this, _hapticLifetime);
    std::erase_if(_sessions, [](const auto& weak) { return weak.expired(); });
    _sessions.push_back(session);
    return {HapticPlayback(std::move(session)), Error::None};
}

Error OutputRouter::playHaptics(const std::shared_ptr<HapticSession>& session)
{
    const auto snapshot = session->audio.snapshot();
    if (snapshot.error != AudioOutputError::None)
        return mapAudioError(snapshot.error);
    if (snapshot.state == AudioPlaybackState::Closed)
        return Error::Disconnected;
    const auto id = session->device;
    const auto route = _hapticRoutes.find(id);
    if (!_registry.find(id) || route == _hapticRoutes.end() ||
        route->second != HapticRoute{session->hid, session->endpoint})
        return Error::Disconnected;
    if (!_focused)
        return Error::Busy;
    if (_bodyRoutes.contains(id)) {
        audio::detail::requireManagedStopEvidence(session->audio);
        if(auto previous=session->managed.lock()) {
            if(_control.ownsPcm(id,previous)) {
                if(snapshot.state==AudioPlaybackState::Paused)return mapAudioError(session->audio.resume());
                return Error::None;
            }
            return _control.playPcm(id,std::move(previous));
        }
        auto port=std::make_shared<haptics::detail::PcmSource>();
        port->hid=session->hid;
        port->setStrength=[session](float strength) {
            std::lock_guard lock(session->gainMutex);
            session->strength = strength;
            session->audio.setGain(strength * session->intensity);
        };
        port->enable=[session] {
            auto e=session->audio.play();
            if(e==AudioOutputError::None)e=audio::detail::setManagedPlaybackEnabled(session->audio,true);
            if(e!=AudioOutputError::None)audio::detail::failManagedPlayback(session->audio,e);
            return mapAudioError(e);
        };
        port->silence=[session](haptics::StopReason why) {
            auto e=audio::detail::setManagedPlaybackEnabled(session->audio,false);
            auto reason=why==haptics::StopReason::FocusLost ? HapticStopReason::FocusLost :
                why==haptics::StopReason::Replaced ? HapticStopReason::Replaced :
                why==haptics::StopReason::EndpointLost ? HapticStopReason::EndpointLost :
                why==haptics::StopReason::Requested ? HapticStopReason::Requested : HapticStopReason::None;
            if(why!=haptics::StopReason::None && session->audio.snapshot().state!=AudioPlaybackState::Closed){
                const auto stopped=session->audio.stop();
                if(e==AudioOutputError::None)e=stopped;
            }
            session->stopReason.store(reason);
            return mapAudioError(e);
        };
        port->ended=[session]{auto state=session->audio.snapshot().state;
            return state==AudioPlaybackState::Ended || state==AudioPlaybackState::Failed || state==AudioPlaybackState::Closed;};
        session->managed=port;session->stopReason.store(HapticStopReason::None);
        return _control.playPcm(id,std::move(port));
    }
    if(_control.retiring(id))return Error::Busy;
    const auto active = _haptics.find(id);
    if (active != _haptics.end() && active->second.session == session)
        return mapAudioError(session->audio.play());
    if (_commandId >= 0x7fffffffu)
        return Error::QueueFull;

    const auto previous = _effects.find({id, Channel::Body});
    // An older rumble route can predate pairing. Confirm its stop before
    // switching a different HID endpoint to waveform mode.
    const auto commandEndpoint = previous == _effects.end() ? session->hid : previous->second.endpoint;
    const bool waveformMode = commandEndpoint == session->hid;
    const auto command = static_cast<CommandId>(++_commandId);
    std::promise<bool> ready;
    const auto accepted = _backend->submit(commandEndpoint, {command, Stop{Channel::Body}, waveformMode,
                                                              ready.get_future().share()});
    if (accepted != Error::None)
        return accepted;

    const auto preparing = session->audio.play();
    if (preparing != AudioOutputError::None)
    {
        ready.set_value(false);
        return mapAudioError(preparing);
    }
    if (active != _haptics.end())
    {
        const auto stopped = stopHaptics(*active->second.session, HapticStopReason::Replaced, false);
        if (stopped != Error::None && stopped != Error::Disconnected)
        {
            ready.set_value(false);
            audio::detail::failManagedPlayback(session->audio, AudioOutputError::BackendFailure);
            _backend->submit(session->hid, {CommandId{}, Stop{Channel::Body}});
            return Error::None;
        }
    }
    if (previous != _effects.end())
        _effects.erase(previous);
    for (const auto& notice : finish(id, Completion::Superseded, {Channel::Body}))
        _queue.outputNotice(notice);
    session->stopReason = HapticStopReason::None;
    _haptics.insert_or_assign(id, ActiveHaptics{session, commandEndpoint, command});
    _unconfirmedBody.insert(id);
    ready.set_value(true);
    return Error::None;
}

Error OutputRouter::stopHaptics(HapticSession& session, HapticStopReason reason, bool neutralize)
{
    if(auto port=session.managed.lock()){
        return _control.stopPcm(session.device,port,reason==HapticStopReason::Requested ? haptics::StopReason::Requested :
                         reason==HapticStopReason::FocusLost ? haptics::StopReason::FocusLost : haptics::StopReason::EndpointLost);
    }
    const auto active = _haptics.find(session.device);
    const bool ownsGrip = active != _haptics.end() && active->second.session.get() == &session;
    if (!ownsGrip && reason != HapticStopReason::Requested)
        return Error::None;
    const bool closed = session.audio.snapshot().state == AudioPlaybackState::Closed;
    auto error = closed ? AudioOutputError::Disconnected : AudioOutputError::None;
    if (!closed)
    {
        if (ownsGrip)
            error = audio::detail::setManagedPlaybackEnabled(session.audio, false);
        if (reason == HapticStopReason::Replaced || reason == HapticStopReason::FocusLost ||
            reason == HapticStopReason::Requested)
        {
            const auto stopped = session.audio.stop();
            if (!ownsGrip)
                error = stopped;
        }
        if (connectionLost(reason))
            audio::detail::failManagedPlayback(session.audio, AudioOutputError::Disconnected);
    }
    if (reason != HapticStopReason::None && (ownsGrip || error == AudioOutputError::None))
        session.stopReason = reason;
    if (ownsGrip)
    {
        if (neutralize && _backend)
            _backend->submit(session.hid, {CommandId{}, Stop{Channel::Body}});
        _haptics.erase(active);
    }
    return mapAudioError(error);
}

void OutputRouter::closeHaptics(HapticSession& session) noexcept
{
    if(auto port=session.managed.lock())_control.stopPcm(session.device,port,haptics::StopReason::Requested);
    const auto active = _haptics.find(session.device);
    if (active != _haptics.end() && active->second.session.get() == &session)
        stopHaptics(session, HapticStopReason::Requested);
}

bool OutputRouter::completeHaptics(const NativeCompletion& completion)
{
    const auto found = std::ranges::find_if(_haptics, [&](const auto& entry) {
        return entry.second.arming == completion.id && entry.second.modeCommandEndpoint == completion.key;
    });
    if (found == _haptics.end())
        return false;
    auto session = found->second.session;
    auto error = completion.error;
    if (error == Error::None && completion.key != session->hid)
    {
        error = _backend->submit(session->hid, {completion.id, Stop{Channel::Body}, true});
        if (error == Error::None)
        {
            found->second.modeCommandEndpoint = session->hid;
            return true;
        }
    }
    found->second.arming = CommandId{};
    const auto status = error == Error::None ? audio::detail::setManagedPlaybackEnabled(session->audio, true)
                                             : waveformError(error);
    if (status != AudioOutputError::None)
    {
        const auto reason = status == AudioOutputError::Disconnected ? HapticStopReason::EndpointLost
                                                                    : HapticStopReason::None;
        audio::detail::failManagedPlayback(session->audio, status);
        stopHaptics(*session, reason);
    }
    return true;
}

void OutputRouter::pollHaptics()
{
    for (auto it = _haptics.begin(); it != _haptics.end();)
    {
        const auto session = (it++)->second.session;
        const auto snap = session->audio.snapshot();
        if (snap.error == AudioOutputError::Disconnected)
            stopHaptics(*session, HapticStopReason::EndpointLost);
        else if (snap.state == AudioPlaybackState::Ended || snap.state == AudioPlaybackState::Failed ||
                 snap.state == AudioPlaybackState::Closed)
            stopHaptics(*session, HapticStopReason::None);
    }
}

void OutputRouter::invalidateHaptics(DeviceId id, const HapticRoute& route, HapticStopReason reason)
{
    if (const auto active = _haptics.find(id); active != _haptics.end())
    {
        const auto session = active->second.session;
        if (session->hid == route.hid && session->endpoint == route.endpoint)
            stopHaptics(*session, reason);
    }
    for (const auto& weak : _sessions)
    {
        if (auto session = weak.lock(); session && session->device == id &&
            session->hid == route.hid && session->endpoint == route.endpoint &&
            session->audio.snapshot().state != AudioPlaybackState::Closed)
        {
            audio::detail::failManagedPlayback(session->audio, AudioOutputError::Disconnected);
            session->stopReason = reason;
        }
    }
}

bool OutputRouter::refreshHaptics()
{
    const auto now = nowNs();
    if (now < _nextPairScan)
        return false;
    _nextPairScan = now + 250'000'000;

    std::map<DeviceId, HapticRoute> routes;
    const auto& devices = _registry.devices();
    if (std::ranges::any_of(devices, [](const auto& entry) {
        return std::ranges::any_of(entry.second.endpoints, [](const auto& endpoint) {
            return hasAudioIdentity(endpoint.second);
        });
    }))
    {
        const auto outputs = audio::detail::enumOutputIdentities();
        if (outputs)
        {
            for (const auto& [id, device] : devices)
            {
                std::optional<HapticRoute> route;
                for (const auto& [key, endpoint] : device.endpoints)
                {
                    const auto& identity = endpoint.descriptor.hapticAudio;
                    const auto* paired = pairedOutput(identity, outputs.value());
                    if (!paired)
                        continue;
                    const auto previous = _hapticRoutes.find(id);
                    const auto error = previous != _hapticRoutes.end() && previous->second.endpoint == paired->id
                        ? AudioOutputError::None : audio::detail::registerManagedOutput(paired->id);
                    if (identity.writable && paired->supportsBodyOutput && error == AudioOutputError::None)
                    {
                        if (route && (route->endpoint != paired->id || route->hid != key))
                        {
                            route.reset();
                            break;
                        }
                        route = HapticRoute{key, paired->id};
                    }
                }
                if (route)
                    routes.emplace(id, *route);
            }
        }
    }

    // Distinct device IDs must not issue simultaneous permits for the same grips.
    std::map<AudioEndpointId, unsigned> matchesPerEndpoint;
    for (const auto& [device, route] : routes)
        ++matchesPerEndpoint[route.endpoint];
    std::erase_if(routes, [&](const auto& match) { return matchesPerEndpoint.at(match.second.endpoint) != 1; });

    bool changed = false;
    for (const auto& [id, old] : _hapticRoutes)
    {
        const auto replacement = routes.find(id);
        if (replacement != routes.end() && replacement->second == old)
            continue;
        invalidateHaptics(id, old, HapticStopReason::EndpointLost);
        if (replacement == routes.end())
        {
            _queue.hapticCapability({id, {}});
            changed = true;
        }
    }
    for (const auto& [id, route] : routes)
    {
        const auto previous = _hapticRoutes.find(id);
        if (previous == _hapticRoutes.end() || previous->second != route)
        {
            _queue.hapticCapability({id, route.hid});
            changed = true;
        }
    }
    _hapticRoutes.swap(routes);
    return changed;
}

void OutputRouter::setFocused(bool focused)
{
    _focused = focused;
    _control.focused(focused);
    if (!_focused)
    {
        _focusCutoff=static_cast<CommandId>(_commandId);
        while (!_haptics.empty())
        {
            const auto session = _haptics.begin()->second.session;
            stopHaptics(*session, HapticStopReason::FocusLost);
        }
    }
}

void OutputRouter::shutdownHaptics() noexcept
{
    setFocused(false);
    _control.shutdown();
    _hapticLifetime.reset();
    for (const auto& weak : _sessions)
        if (const auto session = weak.lock())
            session->audio.close();
    _sessions.clear();
}

} // namespace cc::input::detail
