#pragma once

#include "GamepadBackend.h"
#include "BindingPlan.h"
#include "MappingDatabase.h"

#include <map>
#include <set>

namespace cc::input::detail {

struct Endpoint {
    EndpointDescriptor descriptor;
    std::uint64_t cursor;
    bool awaitingBaseline = false;
    bool focusBaseline = false;
};

struct Device {
    PadView view;
    EndpointKey primary;
    std::map<EndpointKey, Endpoint> endpoints;
    RawState raw;
    MappingSelection mapping;
    std::shared_ptr<const MappingSelection> local;
    std::shared_ptr<const MappingSelection> requestedLocal;
    std::optional<unsigned> reservedPlayer;
    std::bitset<ButtonCount> suppressedButtons;
    LogicalState logical;
    unsigned rawWatchers = 0;
    std::array<std::multiset<unsigned>, SensorCount> sensorDepths;
};

class DeviceRegistry {
public:
    Device* find(DeviceId);
    const Device* find(DeviceId) const;
    Device* find(EndpointKey);
    Device* associated(EndpointKey, const EndpointDescriptor&);
    bool acceptGeneration(EndpointKey);
    std::optional<EndpointKey> previousGeneration(EndpointKey) const;
    Device* create(EndpointKey, EndpointDescriptor, RawBaseline);
    void addEndpoint(Device&, EndpointKey, EndpointDescriptor, std::uint64_t);
    void removeEndpoint(Device&, EndpointKey);
    void replacePrimary(Device&, EndpointKey, EndpointDescriptor, RawBaseline);
    void erase(DeviceId);
    void refreshCapabilities(Device&);
    std::optional<EndpointKey> owner(const Device&, Feature) const;
    std::optional<EndpointKey> owner(const Device&, Sensor) const;
    Error canReservePlayer(DeviceId, std::optional<unsigned>) const;
    std::map<DeviceId, Device>& devices() { return _devices; }

    static bool validBaseline(const RawLayout&, const RawState&);

private:
    void setPrimary(Device&, EndpointKey, RawBaseline);

    std::map<DeviceId, Device> _devices;
    std::map<EndpointKey, DeviceId> _routes;
    std::map<std::pair<std::uint64_t, std::uint64_t>, std::uint64_t> _generations;
};

} // namespace cc::input::detail
