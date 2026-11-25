#pragma once
#include <condition_variable>
#include <cstdint>
#include <mutex>

namespace cc::system_info {
struct NetworkSignal {
    std::mutex mutex;
    std::condition_variable changed;
    uint64_t generation = 0;
};
NetworkSignal& networkSignal();
}
