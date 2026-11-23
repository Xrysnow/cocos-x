#pragma once

#include "../core/DeviceRegistry.h"
#include "../core/ReportQueue.h"

#include <set>

namespace cc::input::detail {

class OutputRouter {
public:
    OutputRouter(DeviceRegistry&, ReportQueue&, GamepadBackend*);
    Result<HapticPlayback> createHapticPlayback(DeviceId, AudioSource&);
    Result<CommandId> submit(DeviceId, const OutputCommand&);
    std::optional<OutputNotice> complete(const NativeCompletion&);
    std::vector<OutputNotice> cancel(DeviceId, std::optional<EndpointKey> endpoint = {},
                                    HapticStopReason reason = HapticStopReason::Disconnected);
    void expire(std::uint64_t now);
    bool refreshHaptics();
    void rescanHaptics() { _nextPairScan = 0; }
    void setFocused(bool focused);
    void shutdownHaptics() noexcept;

private:
    friend class ::cc::input::HapticPlayback;
    using HapticSession = HapticPlayback::Session;

    struct HapticRoute {
        EndpointKey hid;
        AudioEndpointId endpoint;
        bool operator==(const HapticRoute&) const = default;
    };

    struct ActiveHaptics {
        std::shared_ptr<HapticSession> session;
        EndpointKey modeCommandEndpoint;
        CommandId arming{};
    };

    using Route = std::pair<DeviceId, Channel>;
    struct Effect {
        EndpointKey endpoint;
        std::uint64_t deadline;
    };
    struct Pending {
        DeviceId device;
        std::set<EndpointKey> endpoints;
        std::set<Channel> channels;
        Error error = Error::None;
    };

    std::vector<OutputNotice> finish(DeviceId, Completion, const std::set<Channel>&,
                                     std::optional<EndpointKey> endpoint = {});
    Error playHaptics(const std::shared_ptr<HapticSession>&);
    Error stopHaptics(HapticSession&, HapticStopReason, bool neutralize = true);
    void closeHaptics(HapticSession&) noexcept;
    void invalidateHaptics(DeviceId, const HapticRoute&, HapticStopReason);
    void pollHaptics();
    bool completeHaptics(const NativeCompletion&);

    DeviceRegistry& _registry;
    ReportQueue& _queue;
    GamepadBackend* _backend;
    std::uint32_t _commandId = 0;
    std::map<Route, Effect> _effects;
    std::map<CommandId, Pending> _pending;
    std::map<DeviceId, HapticRoute> _hapticRoutes;
    std::map<DeviceId, ActiveHaptics> _haptics;
    std::vector<std::weak_ptr<HapticSession>> _sessions;
    std::shared_ptr<int> _hapticLifetime = std::make_shared<int>(0);
    std::uint64_t _nextPairScan = 0;
    bool _focused = true;
};

} // namespace cc::input::detail
