#include "DeviceRegistry.h"

#include <algorithm>
#include <atomic>
#include <limits>

namespace cc::input::detail {

namespace {
std::optional<DeviceId> nextDeviceId()
{
    static std::atomic<std::uint32_t> last{0};
    auto value = last.load(std::memory_order_relaxed);
    do
    {
        if (value == std::numeric_limits<std::uint32_t>::max())
            return std::nullopt;
    } while (!last.compare_exchange_weak(value, value + 1, std::memory_order_relaxed));
    return static_cast<DeviceId>(value + 1);
}
}

Device* DeviceRegistry::find(DeviceId id)
{
    const auto entry = _devices.find(id);
    return entry == _devices.end() ? nullptr : &entry->second;
}

const Device* DeviceRegistry::find(DeviceId id) const
{
    const auto entry = _devices.find(id);
    return entry == _devices.end() ? nullptr : &entry->second;
}

Device* DeviceRegistry::find(EndpointKey key)
{
    const auto route = _routes.find(key);
    return route == _routes.end() ? nullptr : find(route->second);
}

Device* DeviceRegistry::associated(EndpointKey key, const EndpointDescriptor& descriptor)
{
    if (descriptor.physicalAssociation.empty())
        return nullptr;
    for (auto& [id, device] : _devices)
    {
        const auto& primary = device.endpoints.at(device.primary).descriptor;
        if (device.primary.backend == key.backend && primary.physicalAssociation == descriptor.physicalAssociation)
            return &device;
    }
    return nullptr;
}

std::optional<EndpointKey> DeviceRegistry::previousGeneration(EndpointKey key) const
{
    const auto entry = _generations.find({key.backend, key.endpoint});
    if (entry == _generations.end())
        return std::nullopt;
    return EndpointKey{key.backend, key.endpoint, entry->second};
}

bool DeviceRegistry::acceptGeneration(EndpointKey key)
{
    auto& generation = _generations[{key.backend, key.endpoint}];
    if (key.generation <= generation)
        return false;
    generation = key.generation;
    return true;
}

bool DeviceRegistry::validBaseline(const RawLayout& layout, const RawState& raw)
{
    return raw.buttons.size() == layout.buttonCount && raw.axes.size() == layout.axisCount &&
           raw.hats.size() == layout.hatCount &&
           (raw.axesKnown.empty() || raw.axesKnown.size() == layout.axisCount);
}

Device* DeviceRegistry::create(EndpointKey key, EndpointDescriptor descriptor, RawBaseline baseline)
{
    const auto id = nextDeviceId();
    if (!id)
        return nullptr;
    auto& device = _devices.try_emplace(*id).first->second;
    device.view._info.id = *id;
    addEndpoint(device, key, std::move(descriptor), baseline.cursor);
    setPrimary(device, key, std::move(baseline));
    return &device;
}

void DeviceRegistry::addEndpoint(Device& device, EndpointKey key, EndpointDescriptor descriptor,
                                 std::uint64_t cursor)
{
    device.endpoints.emplace(key, Endpoint{std::move(descriptor), cursor});
    _routes.emplace(key, device.view._info.id);
    refreshCapabilities(device);
}

void DeviceRegistry::removeEndpoint(Device& device, EndpointKey key)
{
    _routes.erase(key);
    device.endpoints.erase(key);
    if (device.hapticOwner == key)
        device.hapticOwner.reset();
    refreshCapabilities(device);
}

void DeviceRegistry::replacePrimary(Device& device, EndpointKey key, EndpointDescriptor descriptor,
                                    RawBaseline baseline)
{
    removeEndpoint(device, device.primary);
    addEndpoint(device, key, std::move(descriptor), baseline.cursor);
    setPrimary(device, key, std::move(baseline));
}

void DeviceRegistry::setPrimary(Device& device, EndpointKey key, RawBaseline baseline)
{
    device.primary = key;
    const auto& descriptor = device.endpoints.at(key).descriptor;
    auto& info = device.view._info;
    if (info.layout != descriptor.layout.id)
    {
        device.local.reset();
        device.requestedLocal.reset();
    }
    info.name = descriptor.name;
    info.layout = descriptor.layout.id;
    info.mappingGuid = descriptor.layout.guid ? descriptor.layout.guid->str() : "";
    info.vendor = descriptor.vendor;
    info.product = descriptor.product;
    info.version = descriptor.version;
    info.serial = descriptor.serial;
    device.raw = std::move(baseline.state);
    device.view._power = descriptor.power;
    device.view._link = descriptor.link;
}

void DeviceRegistry::erase(DeviceId id)
{
    if (auto* device = find(id))
    {
        for (const auto& [key, endpoint] : device->endpoints)
            _routes.erase(key);
        _devices.erase(id);
    }
}

void DeviceRegistry::refreshCapabilities(Device& device)
{
    auto& caps = device.view._caps;
    caps._sensors.reset();
    caps._features.reset();
    caps._fingersPerPad.clear();
    caps._nominalHz = {};
    caps._triggerLimits = {};
    caps._playerLightMask = 0;
    for (const auto& [key, endpoint] : device.endpoints)
    {
        const auto& source = endpoint.descriptor.capabilities;
        if (caps._fingersPerPad.empty())
            caps._fingersPerPad = source.fingersPerPad;
        for (std::size_t i = 0; i < SensorCount; ++i)
        {
            if (source.sensors[i] && !caps._sensors[i])
                caps._nominalHz[i] = source.nominalHz[i];
        }
        if (source.features[static_cast<std::size_t>(Feature::PlayerLights)] &&
            !caps.has(Feature::PlayerLights))
            caps._playerLightMask = source.playerLightMask;
        for (std::size_t i = 0; i < source.triggerLimits.size(); ++i)
        {
            if (source.features[static_cast<std::size_t>(Feature::AdaptiveLeft) + i] &&
                !caps._features[static_cast<std::size_t>(Feature::AdaptiveLeft) + i])
                caps._triggerLimits[i] = source.triggerLimits[i];
        }
        caps._sensors |= source.sensors;
        caps._features |= source.features;
    }
    caps._features.set(static_cast<unsigned>(Feature::BodyHaptics), device.hapticOwner.has_value());
}

std::optional<EndpointKey> DeviceRegistry::owner(const Device& device, Feature feature) const
{
    if (feature == Feature::BodyHaptics)
        return device.hapticOwner;
    for (const auto& [key, endpoint] : device.endpoints)
        if (endpoint.descriptor.capabilities.features.test(static_cast<std::size_t>(feature)))
            return key;
    return std::nullopt;
}

std::optional<EndpointKey> DeviceRegistry::owner(const Device& device, Sensor sensor) const
{
    const auto index = static_cast<std::size_t>(sensor);
    if (index < SensorCount)
        for (const auto& [key, endpoint] : device.endpoints)
            if (endpoint.descriptor.capabilities.sensors[index])
                return key;
    return std::nullopt;
}

Error DeviceRegistry::canReservePlayer(DeviceId id, std::optional<unsigned> slot) const
{
    if (!find(id))
        return Error::Disconnected;
    if (slot)
        for (const auto& [other, device] : _devices)
            if (other != id && device.reservedPlayer == slot)
                return Error::Busy;
    return Error::None;
}

} // namespace cc::input::detail
