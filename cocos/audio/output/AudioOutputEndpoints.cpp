#include "AudioOutputEndpoints.h"
#include "AudioOutputIntegration.h"
#include <algorithm>
#include <array>
#include <mutex>
#include <unordered_map>

namespace cc::audio::detail {

namespace {

struct Endpoints {
    std::mutex refreshMutex;
    std::mutex mutex;
    std::unordered_map<std::string, OutputEndpoint> current;
    std::unordered_map<std::string, std::weak_ptr<GripSafety>> gripHistory;
    std::uint64_t nextId = 0;
};

Endpoints& endpoints()
{
    static Endpoints registry;
    return registry;
}

} // namespace

bool isRearChannel(AudioChannelPosition position)
{
    return position == AudioChannelPosition::RearLeft || position == AudioChannelPosition::RearRight;
}

std::shared_ptr<GripSafety> gripSafetyFor(const DirectEndpoint& device)
{
    auto& registry = endpoints();
    std::lock_guard lock(registry.mutex);
    std::erase_if(registry.gripHistory, [](const auto& entry) { return entry.second.expired(); });
    // Backend endpoint keys can change while the previous stream still owns its stop fence.
    const auto key = !device.containerId.empty() ? "container/" + device.containerId :
                     !device.usbPath.empty() ? "usb/" + device.usbPath : "endpoint/" + device.key;
    auto& history = registry.gripHistory[key];
    if (auto retained = history.lock()) return retained;
    auto fresh = std::make_shared<GripSafety>();
    history = fresh;
    return fresh;
}

bool hasBodyLayout(const DirectEndpoint& endpoint)
{
    using Position = AudioChannelPosition;
    constexpr std::array quad{Position::FrontLeft, Position::FrontRight, Position::RearLeft, Position::RearRight};
    return endpoint.sampleRate == 48000 && std::is_permutation(endpoint.channels.begin(), endpoint.channels.end(),
        quad.begin(), quad.end());
}

AudioResult<std::vector<OutputEndpoint>> refreshOutputEndpoints()
{
    auto& registry = endpoints();
    std::lock_guard refreshLock(registry.refreshMutex);
    auto listed = enumeratePlatformEndpoints();
    std::lock_guard lock(registry.mutex);
    if (!listed)
    {
        if (listed.error() == AudioOutputError::Disconnected)
        {
            for (auto& [key, endpoint] : registry.current)
                endpoint.status->connected = false;
            registry.current.clear();
        }
        return listed.error();
    }

    std::vector<OutputEndpoint> result;
    std::unordered_map<std::string, OutputEndpoint> current;
    for (auto& entry : listed.value())
    {
        if (entry.key.empty() || current.find(entry.key) != current.end())
            continue;
        auto found = registry.current.find(entry.key);
        if (found != registry.current.end())
        {
            const auto& old = found->second.platform;
            if (entry.containerId != old.containerId || entry.usbPath != old.usbPath ||
                entry.sampleRate != old.sampleRate || entry.channels != old.channels || entry.canRoute != old.canRoute)
            {
                // An endpoint key can survive a profile switch or device replacement.
                found->second.status->connected = false;
                found = registry.current.end();
            }
        }
        OutputEndpoint endpoint = found == registry.current.end()
            ? OutputEndpoint{AudioEndpointId{++registry.nextId}, entry, std::make_shared<EndpointStatus>()}
            : OutputEndpoint{found->second.id, entry, found->second.status};
        current.emplace(entry.key, endpoint);
        result.push_back(std::move(endpoint));
    }
    for (auto& [key, endpoint] : registry.current)
        if (current.find(key) == current.end())
            endpoint.status->connected = false;
    registry.current.swap(current);
    return result;
}

AudioResult<OutputEndpoint> findOutputEndpoint(AudioEndpointId id)
{
    auto listed = refreshOutputEndpoints();
    if (!listed)
        return listed.error();
    for (auto& endpoint : listed.value())
        if (endpoint.id == id)
            return std::move(endpoint);
    return AudioOutputError::Disconnected;
}

AudioResult<std::vector<OutputIdentity>> enumOutputIdentities()
{
    auto listed = refreshOutputEndpoints();
    if (!listed)
        return listed.error();
    std::vector<OutputIdentity> result;
    for (const auto& endpoint : listed.value())
        result.push_back({endpoint.id, endpoint.platform.containerId, endpoint.platform.usbPath,
            hasBodyLayout(endpoint.platform)});
    return result;
}

bool requiresFrontStereo(const std::string& mainDeviceName, bool useDefault)
{
    auto& registry = endpoints();
    std::lock_guard lock(registry.mutex);
    for (const auto& [key, endpoint] : registry.current)
    {
        const auto& platform = endpoint.platform;
        if (!endpoint.status->rearManaged)
            continue;
        if (useDefault ? platform.isDefault : (!mainDeviceName.empty() &&
            (mainDeviceName == platform.mainDeviceName || mainDeviceName == platform.deviceSelector)))
            return true;
    }
    return false;
}

bool hasManagedOutputEndpoints()
{
    auto& registry = endpoints();
    std::lock_guard lock(registry.mutex);
    return std::any_of(registry.current.begin(), registry.current.end(), [](const auto& entry) {
        return entry.second.status->rearManaged.load();
    });
}

std::string managedDefaultDeviceName()
{
    auto& registry = endpoints();
    std::lock_guard lock(registry.mutex);
    for (const auto& [key, endpoint] : registry.current)
        if (endpoint.platform.isDefault && endpoint.status->rearManaged)
            return endpoint.platform.deviceSelector;
    return {};
}

void invalidateOutputEndpoints()
{
    auto& registry = endpoints();
    std::lock_guard refreshLock(registry.refreshMutex);
    std::lock_guard lock(registry.mutex);
    for (auto& [key, endpoint] : registry.current)
        endpoint.status->connected = false;
    registry.current.clear();
}

} // namespace cc::audio::detail
