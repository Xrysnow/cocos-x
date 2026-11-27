#pragma once
#include "ClipData.h"
#include <algorithm>
#include <deque>

namespace cc::haptics::detail
{
// Admission and native dispatch have separate clocks of observation. Each must
// count failed attempts and enforce the same half-open one-second window.
class AndroidWriteBudget
{
    std::deque<Time> recent;

public:
    Time availableAt(Time now) const
    {
        if (recent.empty())
            return now;
        Time next = std::max(now, recent.back() + 24000);
        return recent.size() == 8 ? std::max(next, recent.front() + Second) : next;
    }
    void record(Time now)
    {
        if (recent.size() == 8)
            recent.pop_front();
        recent.push_back(now);
    }
};
}  // namespace cc::haptics::detail
