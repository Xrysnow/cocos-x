#pragma once

#include "base/Value.h"

namespace cc {

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
};

} // namespace cc
