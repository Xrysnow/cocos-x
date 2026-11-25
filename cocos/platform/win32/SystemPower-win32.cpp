#include "platform/SystemInfoInternal.h"
#include <windows.h>
#include <powrprof.h>
#include <algorithm>
#pragma comment(lib, "powrprof.lib")

namespace cc::system_info {
ValueMap readBattery() {
    SYSTEM_POWER_STATUS status{};
    if (!GetSystemPowerStatus(&status)) return failure("platformError", "GetSystemPowerStatus", GetLastError());
    ValueMap out;
    if (status.ACLineStatus <= 1) out["powerSource"] = status.ACLineStatus ? "external" : "battery";
    if (status.BatteryFlag != 255) out["present"] = !(status.BatteryFlag & 128);
    if (status.BatteryFlag != 255 && (status.BatteryFlag & 128)) {
        missing(out, "chargeFraction", "notApplicable");
        missing(out, "chargingState", "notApplicable");
    } else {
        if (status.BatteryLifePercent <= 100) out["chargeFraction"] = status.BatteryLifePercent / 100.0;
        if (status.BatteryFlag != 255 && (status.BatteryFlag & 8)) out["chargingState"] = "charging";
        else if (status.ACLineStatus == 0) out["chargingState"] = "discharging";
        else if (status.BatteryFlag != 255 && status.ACLineStatus == 1)
            out["chargingState"] = status.BatteryLifePercent == 100 ? "full" : "notCharging";
    }
    out["source"] = "GetSystemPowerStatus";
    return out;
}

ValueMap readPowerProfile() {
    ValueMap out;
    GUID* scheme = nullptr;
    if (PowerGetActiveScheme(nullptr, &scheme) == ERROR_SUCCESS && scheme) {
        wchar_t id[40]{};
        char guid[40]{};
        if (StringFromGUID2(*scheme, id, 40) && WideCharToMultiByte(CP_UTF8, 0, id, -1, guid, sizeof(guid), nullptr, nullptr))
            out["powerPlan"] = guid;
        if (IsEqualGUID(*scheme, GUID_MIN_POWER_SAVINGS)) out["profile"] = "performance";
        if (IsEqualGUID(*scheme, GUID_MAX_POWER_SAVINGS)) out["profile"] = "powerSaver";
        if (IsEqualGUID(*scheme, GUID_TYPICAL_POWER_SAVINGS)) out["profile"] = "balanced";
        LocalFree(scheme);
    }
    SYSTEM_POWER_STATUS power{};
    if (GetSystemPowerStatus(&power)) out["lowPowerMode"] = power.SystemStatusFlag == 1;
    missing(out, "governors", "notApplicable");
    missing(out, "energyPreferences", "unsupported");
    return out;
}

ValueMap readLimits() {
    ValueMap out;
    USHORT count = 1;
    USHORT group = 0;
    DWORD_PTR affinity = 0, system = 0;
    if (GetProcessGroupAffinity(GetCurrentProcess(), &count, &group) && count == 1 &&
        GetProcessAffinityMask(GetCurrentProcess(), &affinity, &system) && affinity) {
        ValueVector cpus;
        for (unsigned bit = 0; bit < sizeof(affinity) * 8; ++bit)
            if (affinity & (DWORD_PTR{1} << bit)) cpus.emplace_back(group * 64u + bit);
        out["allowedCpus"] = std::move(cpus);
    }
    BOOL inJob = FALSE;
    if (!IsProcessInJob(GetCurrentProcess(), nullptr, &inJob)) return out;
    if (!inJob) {
        missing(out, "cpuQuota", "unlimited");
        missing(out, "memoryLimit", "unlimited");
        return out;
    }
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
    if (QueryInformationJobObject(nullptr, JobObjectExtendedLimitInformation, &limits, sizeof(limits), nullptr)) {
        const DWORD flags = limits.BasicLimitInformation.LimitFlags;
        uint64_t bound = UINT64_MAX;
        if (flags & JOB_OBJECT_LIMIT_JOB_MEMORY) bound = limits.JobMemoryLimit;
        if (flags & JOB_OBJECT_LIMIT_PROCESS_MEMORY) bound = (std::min)(bound, uint64_t(limits.ProcessMemoryLimit));
        if (bound != UINT64_MAX) out["memoryLimit"] = bound;
    }
    JOBOBJECT_CPU_RATE_CONTROL_INFORMATION rate{};
    if (QueryInformationJobObject(nullptr, JobObjectCpuRateControlInformation, &rate, sizeof(rate), nullptr) &&
        (rate.ControlFlags & JOB_OBJECT_CPU_RATE_CONTROL_ENABLE)) {
        unsigned cap = 0;
        if (rate.ControlFlags & JOB_OBJECT_CPU_RATE_CONTROL_HARD_CAP) cap = rate.CpuRate;
        if (rate.ControlFlags & JOB_OBJECT_CPU_RATE_CONTROL_MIN_MAX_RATE) cap = rate.MaxRate;
        const auto processors = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
        if (cap && processors) out["cpuQuota"] = cap / 10000.0 * processors;
    }
    out["source"] = "process affinity / immediate Windows Job";
    return out;
}
} // namespace cc::system_info
