#include "platform/SystemInfoInternal.h"
#include "platform/SystemNetworkSignal.h"
#include <chrono>
#include <mutex>

namespace cc::system_info {
NetworkSignal& networkSignal() {
    // OS notifications may arrive during static teardown.
    static auto* signal = new NetworkSignal;
    return *signal;
}
void networkChanged() {
    auto& signal = networkSignal();
    {
        std::lock_guard lock(signal.mutex);
        ++signal.generation;
    }
    signal.changed.notify_all();
}
}

namespace cc {
ValueMap SystemInfo::getNetworkState() {
    static std::mutex mutex;
    static ValueMap previous;
    static uint64_t revision = 0;
    std::lock_guard lock(mutex);
    auto state = system_info::finish(system_info::readNetwork(), {"primaryType", "cellularGeneration", "isMetered", "isVpn", "costHint"});
    // Both directions matter when an optional field appears within a nested map.
    if (!(previous == state && state == previous)) {
        previous = state;
        ++revision;
    }
    state["revision"] = revision;
    state["observedAt"] = static_cast<int64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
    return state;
}
}
