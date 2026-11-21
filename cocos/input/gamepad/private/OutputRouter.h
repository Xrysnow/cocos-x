#pragma once

#include "DeviceRegistry.h"
#include "ReportQueue.h"

#include <set>

namespace cc::input::detail {

class OutputRouter {
public:
    OutputRouter(DeviceRegistry&, ReportQueue&, GamepadBackend*);
    Result<CommandId> submit(DeviceId, const OutputCommand&);
    std::optional<OutputNotice> complete(const NativeCompletion&);
    std::vector<OutputNotice> cancel(DeviceId, std::optional<EndpointKey> endpoint = {});
    void expire(std::uint64_t now);

private:
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

    DeviceRegistry& _registry;
    ReportQueue& _queue;
    GamepadBackend* _backend;
    std::uint32_t _commandId = 0;
    std::map<Route, Effect> _effects;
    std::map<CommandId, Pending> _pending;
};

} // namespace cc::input::detail
