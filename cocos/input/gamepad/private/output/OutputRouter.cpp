#include "OutputRouter.h"
#include "HapticPlaybackSession.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace cc::input::detail {
namespace {

constexpr std::array channels{Channel::Body, Channel::Triggers, Channel::AdaptiveLeft,
                              Channel::AdaptiveRight, Channel::Lights};

std::optional<EndpointKey> owner(const DeviceRegistry& registry, const Device& device, Channel channel)
{
    switch (channel)
    {
    case Channel::Body:
        if (auto rumble = registry.owner(device, Feature::BodyRumble))
            return rumble;
        return registry.owner(device, Feature::BodyHaptics);
    case Channel::Triggers: return registry.owner(device, Feature::TriggerRumble);
    case Channel::AdaptiveLeft: return registry.owner(device, Feature::AdaptiveLeft);
    case Channel::AdaptiveRight: return registry.owner(device, Feature::AdaptiveRight);
    case Channel::Lights:
        for (auto feature : {Feature::RgbLed, Feature::MonoLed, Feature::PlayerLights})
            if (auto result = registry.owner(device, feature))
                return result;
        return std::nullopt;
    default: return std::nullopt;
    }
}

bool unit(float value)
{
    return std::isfinite(value) && value >= 0 && value <= 1;
}

bool validDuration(std::chrono::milliseconds duration)
{
    return duration >= std::chrono::milliseconds::zero() && duration <= std::chrono::seconds(60);
}

struct Request {
    Channel channel;
    std::optional<Feature> feature;
    Error error = Error::None;
    std::chrono::milliseconds duration{};
};

Request validate(const OutputCommand& command, const Capabilities& caps)
{
    if (const auto* rumble = std::get_if<Rumble>(&command))
        return {Channel::Body, Feature::BodyRumble,
            unit(rumble->low) && unit(rumble->high) && validDuration(rumble->duration)
                ? Error::None : Error::InvalidArgument, rumble->duration};
    if (const auto* rumble = std::get_if<TriggerRumble>(&command))
        return {Channel::Triggers, Feature::TriggerRumble,
            unit(rumble->left) && unit(rumble->right) && validDuration(rumble->duration)
                ? Error::None : Error::InvalidArgument, rumble->duration};
    if (const auto* rgb = std::get_if<Rgb>(&command))
        return {Channel::Lights, caps.has(Feature::RgbLed) ? Feature::RgbLed : Feature::MonoLed,
            caps.has(Feature::RgbLed) || (rgb->r == rgb->g && rgb->g == rgb->b)
                ? Error::None : Error::Unsupported};
    if (const auto* lights = std::get_if<PlayerLights>(&command))
        return {Channel::Lights, Feature::PlayerLights,
            !caps.has(Feature::PlayerLights) || (lights->mask & ~caps.playerLightMask()) == 0
                ? Error::None : Error::InvalidArgument};
    if (const auto* trigger = std::get_if<AdaptiveTrigger>(&command))
    {
        const auto side = trigger->side;
        if (side != Side::Left && side != Side::Right)
            return {Channel::All, {}, Error::InvalidArgument};
        Request result{side == Side::Left ? Channel::AdaptiveLeft : Channel::AdaptiveRight,
                       side == Side::Left ? Feature::AdaptiveLeft : Feature::AdaptiveRight};
        if (trigger->mode == TriggerMode::Off)
            return result;
        if (!unit(trigger->start) || !unit(trigger->strength))
            result.error = Error::InvalidArgument;
        else if (const auto limits = caps.triggerLimits(side); limits)
        {
            switch (trigger->mode)
            {
            case TriggerMode::Resistance:
                if (!limits->resistance) result.error = Error::Unsupported;
                break;
            case TriggerMode::Vibration:
                if (!limits->vibration) result.error = Error::Unsupported;
                else if (!(std::isfinite(trigger->hz) && trigger->hz > 0 &&
                           trigger->hz >= limits->minHz && trigger->hz <= limits->maxHz))
                    result.error = Error::InvalidArgument;
                break;
            default: result.error = Error::InvalidArgument; break;
            }
        }
        else
            result.error = Error::Unsupported;
        return result;
    }
    const auto channel = std::get<Stop>(command).channel;
    return {channel, {}, channel == Channel::All || std::ranges::find(channels, channel) != channels.end()
        ? Error::None : Error::InvalidArgument};
}

bool isStop(const OutputCommand& command)
{
    if (const auto* value = std::get_if<Rumble>(&command))
        return value->duration.count() == 0 || (value->low == 0 && value->high == 0);
    if (const auto* value = std::get_if<TriggerRumble>(&command))
        return value->duration.count() == 0 || (value->left == 0 && value->right == 0);
    if (const auto* value = std::get_if<AdaptiveTrigger>(&command))
        return value->mode == TriggerMode::Off;
    return std::holds_alternative<Stop>(command);
}
}

OutputRouter::OutputRouter(DeviceRegistry& registry, ReportQueue& queue, GamepadBackend* backend)
    : _registry(registry), _queue(queue), _backend(backend),
      _service(std::make_shared<haptics::detail::HapticControl>(backend,queue)),
      _control(haptics::detail::HapticControl::get(_service)) {}

void OutputRouter::publishBodyRoutes()
{
    std::map<DeviceId,EndpointKey> current;
    std::erase_if(_unconfirmedBody,[&](auto id){return !_registry.find(id);});
    std::erase_if(_retiredBody,[&](auto id){
        if(_registry.find(id))return false;
        _control.removeGamepad(id,true);
        return true;
    });
    for (auto& [id,device] : _registry.devices()) {
        auto key = _registry.owner(device,Feature::BodyRumble);
        auto paired=_hapticRoutes.find(id);
        if(paired!=_hapticRoutes.end() && device.endpoints.contains(paired->second.hid) &&
           device.endpoints.at(paired->second.hid).descriptor.capabilities.features.test(static_cast<unsigned>(Feature::BodyRumble)))
            key=paired->second.hid;
        if(key && !_unconfirmedBody.contains(id) && device.endpoints.at(*key).descriptor.capabilities.acknowledgedBodyStop) {
            current.emplace(id,*key);
            _retiredBody.erase(id);
            if(!_bodyRoutes.contains(id) || _bodyRoutes.at(id)!=*key)
                _control.publishGamepad(id,*key);
        }
    }
    for(auto& [id,key]:_bodyRoutes)if(!current.contains(id)){
        bool disconnected=_registry.find(id)==nullptr;
        _control.removeGamepad(id,disconnected);
        if(!disconnected)_retiredBody.insert(id);
    }
    _bodyRoutes.swap(current);
}

Result<CommandId> OutputRouter::submit(DeviceId id, const OutputCommand& command)
{
    const auto* device = _registry.find(id);
    if (!device)
        return {{}, Error::Disconnected};
    if (!_backend)
        return {{}, Error::Unsupported};
    const auto request = validate(command, device->view._caps);
    if (request.error != Error::None)
        return {{}, request.error};
    if (_commandId >= 0x7fffffffu-channels.size())
        return {{}, Error::QueueFull};

    const bool stopping = isStop(command);
    const auto commandId = static_cast<CommandId>(++_commandId);
    std::map<Channel, EndpointKey> routes;
    const auto haptics = _haptics.find(id);
    auto activeOwner = [&](Channel channel) -> std::optional<EndpointKey> {
        if (channel == Channel::Body && haptics != _haptics.end())
            return haptics->second.session->hid;
        const auto effect = _effects.find({id, channel});
        if (effect != _effects.end())
            return effect->second.endpoint;
        return owner(_registry, *device, channel);
    };
    if (request.channel == Channel::All)
    {
        for (const auto channel : channels)
            if (auto endpoint = activeOwner(channel))
                routes.emplace(channel, *endpoint);
    }
    else
    {
        auto endpoint = request.feature ? _registry.owner(*device, *request.feature)
                                        : owner(_registry, *device, request.channel);
        if (request.feature == Feature::BodyRumble)
        {
            const auto paired = _hapticRoutes.find(id);
            if (paired != _hapticRoutes.end() && device->endpoints.at(paired->second.hid).descriptor.capabilities
                .features.test(static_cast<unsigned>(Feature::BodyRumble)))
                endpoint = paired->second.hid;
        }
        if (std::holds_alternative<Stop>(command) || (stopping && request.channel == Channel::Body))
            endpoint = activeOwner(request.channel);
        if (endpoint)
            routes.emplace(request.channel, *endpoint);
    }
    if (routes.empty())
        return {{}, Error::Unsupported};

    const OutputCommand operation = stopping ? OutputCommand{Stop{request.channel}} : command;
    const auto body = routes.find(Channel::Body);
    std::optional<std::promise<bool>> ready;
    std::shared_future<bool> bodyReady;
    if (haptics != _haptics.end() && body != routes.end())
        bodyReady = ready.emplace().get_future().share();
    std::map<CommandId,EndpointKey> accepted;
    auto receiptLifetime=std::make_shared<int>(0);
    std::set<Channel> acceptedChannels;
    Error error = Error::None;
    for (const auto& [channel, endpoint] : routes)
    {
        auto ticket = accepted.empty() ? commandId : static_cast<CommandId>(++_commandId);
        _queue.expectCompletion(endpoint,ticket,receiptLifetime);
        auto part = stopping ? OutputCommand{Stop{channel}} : operation;
        Error status;
        if(channel==Channel::Body && _bodyRoutes.contains(id))
            status=_control.legacy(id,part,stopping && std::holds_alternative<Rumble>(command),
                [queue=&_queue,endpoint,ticket](Error e){queue->outputCompleted(endpoint,ticket,e);});
        else if(channel==Channel::Body && _control.retiring(id))
            status=Error::Busy;
        else
            status=_backend->submit(endpoint,{ticket,part,false,
                ready && channel==Channel::Body ? bodyReady : std::shared_future<bool>{}});
        if(status==Error::None){
            accepted.emplace(ticket,endpoint);acceptedChannels.insert(channel);
            if(channel==Channel::Body && !_bodyRoutes.contains(id) && !stopping)_unconfirmedBody.insert(id);
        }
        else error=status;
    }
    if (accepted.empty())
        return {{}, error};

    if (ready && acceptedChannels.contains(Channel::Body))
    {
        const auto session = haptics->second.session;
        const auto stopped = stopHaptics(*session, stopping ? HapticStopReason::Requested :
            HapticStopReason::Replaced, body->second != session->hid);
        ready->set_value(stopped == Error::None || stopped == Error::Disconnected);
    }

    std::set<Channel> replaced;
    for (const auto& [channel, endpoint] : routes)
    {
        if (!acceptedChannels.contains(channel))
            continue;
        replaced.insert(channel);
        if(channel==Channel::Body && _bodyRoutes.contains(id))continue;
        const Route route{id, channel};
        if (auto previous = _effects.find(route); previous != _effects.end() &&
            previous->second.endpoint != endpoint)
            _backend->submit(previous->second.endpoint, {CommandId{}, Stop{channel}});
        if (stopping)
            _effects.erase(route);
        else
        {
            const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(request.duration).count();
            _effects[route] = {endpoint, ns == 0 ? 0 : nowNs() + static_cast<std::uint64_t>(ns), commandId};
        }
    }
    for (auto notice : finish(id, Completion::Superseded, replaced))
        _queue.outputNotice(notice);
    _pending.emplace(commandId, Pending{id, std::move(accepted), std::move(replaced), error,std::move(receiptLifetime)});
    return {commandId, Error::None};
}

std::optional<OutputNotice> OutputRouter::complete(const NativeCompletion& completion)
{
    if (completeHaptics(completion))
        return std::nullopt;
    auto entry = _pending.find(completion.id);
    if(entry==_pending.end())entry=std::ranges::find_if(_pending,[&](const auto& p){return p.second.tickets.contains(completion.id);});
    if (entry == _pending.end()) return {};
    auto ticket=entry->second.tickets.find(completion.id);
    if(ticket==entry->second.tickets.end() || ticket->second!=completion.key)
        return std::nullopt;
    auto& pending = entry->second;
    pending.tickets.erase(ticket);
    if (completion.error != Error::None)
        pending.error = completion.error;
    if (!pending.tickets.empty())
        return std::nullopt;
    const auto error = pending.error;
    const OutputNotice notice{pending.device,
        {entry->first, error == Error::None ? Completion::Applied : Completion::Failed, error}};
    _pending.erase(entry);
    return notice;
}

std::vector<OutputNotice> OutputRouter::finish(DeviceId id, Completion status,
                                               const std::set<Channel>& replaced,
                                               std::optional<EndpointKey> endpoint, std::optional<CommandId> through)
{
    std::vector<OutputNotice> notices;
    for (auto it = _pending.begin(); it != _pending.end();)
    {
        const auto& pending = it->second;
        if ((!through || it->first<=*through) && pending.device == id && (!endpoint || std::ranges::any_of(pending.tickets,[&](auto& p){return p.second==*endpoint;})) &&
            (status!=Completion::Superseded || pending.channels.size()==1) &&
            (replaced.empty() || std::ranges::any_of(replaced, [&](Channel ch) { return pending.channels.contains(ch); })))
        {
            notices.push_back({id, {it->first, status, Error::None}});
            it = _pending.erase(it);
        }
        else
            ++it;
    }
    return notices;
}

std::vector<OutputNotice> OutputRouter::cancel(DeviceId id, std::optional<EndpointKey> endpoint,
                                               HapticStopReason reason)
{
    if (reason == HapticStopReason::Disconnected)
    {
        const auto paired = _hapticRoutes.find(id);
        if (paired != _hapticRoutes.end() && (!endpoint || paired->second.hid == *endpoint))
        {
            invalidateHaptics(id, paired->second, reason);
            _hapticRoutes.erase(paired);
            _queue.hapticCapability({id, {}});
            rescanHaptics();
        }
    }
    const auto through = reason==HapticStopReason::FocusLost ? std::optional{_focusCutoff} : std::nullopt;
    for (auto it = _effects.begin(); it != _effects.end();)
    {
        if ((!through || it->second.issued<=*through) && it->first.first == id && (!endpoint || *endpoint == it->second.endpoint))
        {
            if (_backend)
                _backend->submit(it->second.endpoint, {CommandId{}, Stop{it->first.second}});
            it = _effects.erase(it);
        }
        else
            ++it;
    }
    return finish(id, Completion::Cancelled, {}, endpoint, through);
}

void OutputRouter::expire(std::uint64_t now)
{
    pollHaptics();
    for (auto it = _effects.begin(); it != _effects.end();)
    {
        const auto& [endpoint, deadline, issued] = it->second;
        if (deadline != 0 && deadline <= now)
        {
            const auto result = _backend->submit(endpoint, {CommandId{}, Stop{it->first.second}});
            if (result != Error::QueueFull && result != Error::Busy)
                it = _effects.erase(it);
            else
                ++it;
        }
        else
            ++it;
    }
}

} // namespace cc::input::detail
