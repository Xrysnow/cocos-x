#include "platform/SystemInfoInternal.h"
#include "platform/SystemNetworkSignal.h"
#include <chrono>
#include <optional>
#include <thread>

namespace cc {
namespace {
using Clock = std::chrono::steady_clock;

// The first watcher installs the OS callbacks, the last one removes them.
class NetworkLease {
public:
    explicit NetworkLease(bool watch) : active(watch) {
        if (active) {
            std::lock_guard lock(mutex);
            if (users++ == 0) system_info::startNetworkEvents();
        }
    }
    ~NetworkLease() {
        if (active) {
            std::lock_guard lock(mutex);
            if (--users == 0) system_info::stopNetworkEvents();
        }
    }
private:
    bool active;
    static std::mutex mutex;
    static unsigned users;
};
std::mutex NetworkLease::mutex;
unsigned NetworkLease::users = 0;
}

ValueMap SystemInfo::getBatteryStatus() {
    return system_info::finish(system_info::readBattery(), {"present", "chargeFraction", "chargingState", "powerSource"});
}
ValueMap SystemInfo::getPowerProfile() {
    return system_info::finish(system_info::readPowerProfile(), {"profile", "powerPlan", "governors", "energyPreferences"});
}
ValueMap SystemInfo::getResourceLimits() {
    return system_info::finish(system_info::readLimits(), {"allowedCpus", "cpuQuota", "memoryLimit"});
}

struct SystemInfoSubscription::State : std::enable_shared_from_this<State> {
    bool network, memory, battery;
    std::string path;
    std::chrono::milliseconds interval;
    SystemInfo::Callback callback;
    SystemInfo::Dispatcher dispatch;
    // These fields are protected by signal.mutex. Sampling and callbacks run unlocked.
    system_info::NetworkSignal& signal = system_info::networkSignal();
    bool running = true, paused = false, finished = false, scheduled = false;
    uint64_t epoch = 0;
    std::thread::id worker, invoking;
    ValueMap pending;

    ValueMap sample() const {
        if (network) return SystemInfo::getNetworkState();
        ValueMap result;
        result["ok"] = true;
        result["observedAt"] = static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
            Clock::now().time_since_epoch()).count());
        if (memory) result["memory"] = SystemInfo::getMemoryUsage();
        if (battery) result["battery"] = SystemInfo::getBatteryStatus();
        if (!path.empty()) result["disk"] = SystemInfo::getDiskSpace(path);
        return result;
    }

    void deliver(uint64_t ticket) {
        SystemInfo::Callback fn;
        ValueMap snapshot;
        {
            std::lock_guard lock(signal.mutex);
            if (!running || paused || ticket != epoch || !scheduled) return;
            fn = callback;
            snapshot.swap(pending);
            invoking = std::this_thread::get_id();
        }
        try { if (!snapshot.empty()) fn(std::move(snapshot)); }
        catch (...) {
            std::lock_guard lock(signal.mutex);
            running = false;
        }
        {
            std::lock_guard lock(signal.mutex);
            invoking = {};
            if (ticket == epoch) scheduled = false;
        }
        signal.changed.notify_all();
    }

    void loop() {
        NetworkLease lease(network);
        std::optional<uint64_t> lastRevision;
        uint64_t lastEpoch = 0;
        std::unique_lock lock(signal.mutex);
        worker = std::this_thread::get_id();
        while (running) {
            signal.changed.wait(lock, [&] { return !running || !paused; });
            if (!running) break;
            auto ticket = epoch;
            auto generation = signal.generation;
            if (ticket != lastEpoch) lastRevision.reset();
            lastEpoch = ticket;
            lock.unlock();
            auto snapshot = sample();
            lock.lock();
            if (!running || paused || ticket != epoch) continue;
            bool publish = true;
            if (network) {
                auto revision = snapshot.at("revision").asUint64();
                publish = !lastRevision || *lastRevision != revision;
                lastRevision = revision;
            }
            if (publish) pending = std::move(snapshot);
            if (callback && !pending.empty() && !scheduled && invoking == std::thread::id{}) {
                scheduled = true;
                // Queued work cannot prolong a subscription or call a stopped consumer.
                auto task = [weak = weak_from_this(), ticket] {
                    if (auto state = weak.lock()) state->deliver(ticket);
                };
                lock.unlock();
                if (dispatch) dispatch(std::move(task)); else task();
                lock.lock();
            }
            signal.changed.wait_for(lock, interval, [&] {
                return !running || paused || ticket != epoch || (network && signal.generation != generation);
            });
        }
    }
};

SystemInfoSubscription::SystemInfoSubscription(std::shared_ptr<State> state)
    : _state(std::move(state)) {}
SystemInfoSubscription& SystemInfoSubscription::operator=(SystemInfoSubscription&& other) noexcept {
    if (this != &other) {
        stop();
        _state = std::move(other._state);
    }
    return *this;
}
SystemInfoSubscription::~SystemInfoSubscription() { stop(); }

bool SystemInfoSubscription::isRunning() const {
    if (!_state) return false;
    std::lock_guard lock(_state->signal.mutex);
    return _state->running;
}
ValueMap SystemInfoSubscription::poll() {
    if (!_state) return {};
    std::lock_guard lock(_state->signal.mutex);
    ValueMap value;
    if (!_state->callback) value.swap(_state->pending);
    return value;
}
void SystemInfoSubscription::setPaused(bool paused) {
    if (!_state) return;
    auto& s = *_state;
    std::lock_guard lock(s.signal.mutex);
    if (!s.running || s.paused == paused) return;
    s.paused = paused;
    ++s.epoch;
    s.scheduled = false;
    s.pending.clear();
    s.signal.changed.notify_all();
}
void SystemInfoSubscription::stop() {
    auto s = _state;
    if (!s) return;
    std::unique_lock lock(s->signal.mutex);
    s->running = false;
    s->pending.clear();
    s->signal.changed.notify_all();
    const auto caller = std::this_thread::get_id();
    if (caller == s->worker || caller == s->invoking) return;
    s->signal.changed.wait(lock, [&] { return s->finished && s->invoking == std::thread::id{}; });
}

std::optional<SystemInfoSubscription> SystemInfo::subscribe(bool network, int intervalMs, bool memory, bool battery,
    std::string_view path, Callback callback, Dispatcher dispatch) {
    if (intervalMs <= 0 || (!network && !memory && !battery && path.empty())) return {};
    auto s = std::make_shared<SystemInfoSubscription::State>();
    s->network = network;
    s->interval = std::chrono::milliseconds(intervalMs);
    s->memory = memory;
    s->battery = battery;
    s->path = path;
    s->callback = std::move(callback);
    s->dispatch = std::move(dispatch);
    SystemInfoSubscription handle(s);
    try {
        std::thread([s] {
            try { s->loop(); } catch (...) {}
            std::lock_guard lock(s->signal.mutex);
            s->finished = true;
            s->running = false;
            s->signal.changed.notify_all();
        }).detach();
    } catch (const std::system_error&) {
        s->finished = true;
        s->running = false;
        return {};
    }
    return handle;
}
std::optional<SystemInfoSubscription> SystemInfo::watchNetwork() {
    return subscribeNetwork({});
}
std::optional<SystemInfoSubscription> SystemInfo::monitor(int intervalMs, bool memory, bool battery, std::string_view path) {
    return subscribeMonitor(intervalMs, memory, battery, path, {});
}
std::optional<SystemInfoSubscription> SystemInfo::subscribeNetwork(Callback callback, Dispatcher dispatch) {
    return subscribe(true, 5000, false, false, {}, std::move(callback), std::move(dispatch));
}
std::optional<SystemInfoSubscription> SystemInfo::subscribeMonitor(int intervalMs, bool memory, bool battery,
    std::string_view path, Callback callback, Dispatcher dispatch) {
    return subscribe(false, intervalMs, memory, battery, path, std::move(callback), std::move(dispatch));
}
} // namespace cc
