#pragma once

#include "base/Value.h"
#include <optional>
#include <functional>
#include <memory>

namespace cc {

class CC_DLL SystemInfoSubscription final {
public:
    ~SystemInfoSubscription();
    SystemInfoSubscription(SystemInfoSubscription&& other) noexcept = default;
    SystemInfoSubscription& operator=(SystemInfoSubscription&& other) noexcept;
    SystemInfoSubscription(const SystemInfoSubscription&) = delete;
    SystemInfoSubscription& operator=(const SystemInfoSubscription&) = delete;
    bool isRunning() const;
    void stop();
    void setPaused(bool paused);
    // Consumes the latest undelivered snapshot. An empty map means none is ready.
    ValueMap poll();
private:
    struct State;
    explicit SystemInfoSubscription(std::shared_ptr<State> state);
    std::shared_ptr<State> _state;
    friend class SystemInfo;
};

// Snapshots own their data. ok=false provides error/context/nativeCode.
// A missing field has its reason in missing; zero and false are ordinary values.
class CC_DLL SystemInfo final {
public:
    SystemInfo() = delete;
    static ValueMap getComputer(bool identifiers = false);
    static ValueMap getOs();
    static ValueMap getCpu();
    static ValueMap getUptime();
    static ValueMap getMemoryUsage();
    static ValueMap getDiskSpace(std::string_view path);
    static ValueMap getNetworkInterfaces(bool addresses = false);
    static ValueMap getNetworkState();
    static ValueMap getBatteryStatus();
    static ValueMap getPowerProfile();
    static ValueMap getResourceLimits();
    static std::optional<SystemInfoSubscription> watchNetwork();
    static std::optional<SystemInfoSubscription> monitor(int intervalMs, bool memory, bool battery, std::string_view path);

    using Callback = std::function<void(ValueMap)>;
    using Dispatcher = std::function<void(std::function<void()>)>;
    // Native owners may supply an executor. Without one the worker invokes the callback.
    static std::optional<SystemInfoSubscription> subscribeNetwork(Callback callback, Dispatcher dispatch = {});
    static std::optional<SystemInfoSubscription> subscribeMonitor(int intervalMs, bool memory, bool battery,
        std::string_view path, Callback callback, Dispatcher dispatch = {});
private:
    static std::optional<SystemInfoSubscription> subscribe(bool network, int intervalMs, bool memory, bool battery,
        std::string_view path, Callback callback, Dispatcher dispatch);
};

} // namespace cc
