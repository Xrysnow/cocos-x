#include "platform/SystemCgroupInfo.h"
#include "platform/SystemInfoInternal.h"
#include "platform/linux/SystemInfo-linux-bus.h"
#include "platform/linux/SystemInfo-linux-private.h"

#include <cmath>
#include <set>
#include <tuple>
#include <sched.h>

namespace cc::system_info
{
namespace
{
using namespace linux_detail;

constexpr auto upowerName = "org.freedesktop.UPower";
constexpr auto upowerPath = "/org/freedesktop/UPower";
constexpr auto displayDevice = "/org/freedesktop/UPower/devices/DisplayDevice";

struct Battery
{
    std::optional<bool> present;
    std::optional<double> fraction;
    const char* state = nullptr;
    const char* source = nullptr;
    bool denied = false;
};

const char* upowerState(unsigned int state)
{
    switch (state)
    {
    case 1: return "charging";
    case 2: return "discharging";
    case 4: return "full";
    case 5: return "notCharging";
    }
    return nullptr;
}

Battery upowerBattery()
{
    SystemBus bus;
    auto owner = bus.owner(upowerName);
    if (!owner)
        return {};
    auto message = bus.call(owner->c_str(), displayDevice, "org.freedesktop.DBus.Properties", "GetAll", "s",
                            "org.freedesktop.UPower.Device");
    if (!SystemBus::enter(message, 'a', "{sv}"))
        return {};
    std::optional<unsigned int> type;
    std::optional<int> present;
    std::optional<double> percentage;
    std::optional<double> energyFull;
    unsigned int state = 0;
    while (SystemBus::enter(message, 'e', "sv"))
    {
        const char* name = nullptr;
        if (!SystemBus::read(message, "s", &name))
            return {};
        std::string_view property(name);
        if ((property == "Type" || property == "State") && SystemBus::enter(message, 'v', "u"))
        {
            unsigned int value = 0;
            if (!SystemBus::read(message, "u", &value) || !SystemBus::exit(message))
                return {};
            if (property == "Type")
                type = value;
            else
                state = value;
        }
        else if (property == "IsPresent" && SystemBus::enter(message, 'v', "b"))
        {
            int value = 0;
            if (!SystemBus::read(message, "b", &value) || !SystemBus::exit(message))
                return {};
            present = value;
        }
        else if ((property == "Percentage" || property == "EnergyFull") && SystemBus::enter(message, 'v', "d"))
        {
            double value = 0;
            if (!SystemBus::read(message, "d", &value) || !SystemBus::exit(message))
                return {};
            if (property == "Percentage")
                percentage = value;
            else
                energyFull = value;
        }
        else if (!SystemBus::skip(message, "v"))
            return {};
        if (!SystemBus::exit(message))
            return {};
    }
    if (!SystemBus::exit(message))
        return {};
    Battery result;
    if (type == 2 && present)
    {
        result.present = *present != 0;
        if (*present)
        {
            // UPower uses Percentage=0 for unsupported devices without energy
            // data. An empty state or a known full charge capacity makes zero observable.
            if (percentage && std::isfinite(*percentage) && *percentage >= 0 && *percentage <= 100 &&
                (*percentage > 0 || state == 3 || (energyFull && *energyFull > 0)))
                result.fraction = *percentage / 100;
            result.state = upowerState(state);
        }
    }
    auto onBattery = bus.scalar<int>(owner->c_str(), upowerPath, upowerName, "OnBattery", "b");
    if (onBattery == 1)
        result.source = "battery";
    else if (onBattery == 0 && result.present == true)
        result.source = "external";
    return result;
}

std::string_view powerSupplyProperty(const std::string& values, std::string_view key)
{
    auto prefix = "POWER_SUPPLY_" + std::string(key) + "=";
    for (auto line : words(values, "\n"))
        if (line.starts_with(prefix))
            return line.substr(prefix.size());
    return {};
}

const char* powerSupplyState(std::string_view state)
{
    if (state == "Charging")
        return "charging";
    if (state == "Discharging")
        return "discharging";
    if (state == "Full")
        return "full";
    if (state == "Not charging")
        return "notCharging";
    return nullptr;
}

Battery kernelBattery()
{
    Battery result;
    std::error_code error;
    size_t batteryCount = 0;
    bool incomplete = false;
    const char* singleBatteryState = nullptr;
    std::optional<double> singleBatteryFraction;
    bool external = false;
    bool linePowerOffline = false;
    for (std::filesystem::directory_iterator supply("/sys/class/power_supply", error), end;
         !error && supply != end; supply.increment(error))
    {
        int readError = 0;
        auto values = readText(supply->path() / "uevent", &readError);
        if (!values)
        {
            result.denied |= readError == EACCES || readError == EPERM;
            incomplete = true;
            continue;
        }
        auto type = powerSupplyProperty(*values, "TYPE");
        auto scope = powerSupplyProperty(*values, "SCOPE");
        if (scope == "Device")
            continue;
        if (type == "Battery")
        {
            auto present = number<int>(powerSupplyProperty(*values, "PRESENT"));
            if (present == 0)
                continue;
            auto status = powerSupplyProperty(*values, "STATUS");
            auto capacity = number<unsigned int>(powerSupplyProperty(*values, "CAPACITY"));
            if (!present && status.empty() && !capacity)
            {
                incomplete = true;
                continue;
            }
            ++batteryCount;
            singleBatteryState = powerSupplyState(status);
            singleBatteryFraction = capacity && *capacity <= 100 ? std::optional<double>(*capacity / 100.0) : std::nullopt;
        }
        // Peripheral supplies are excluded above. An explicitly system-scoped
        // USB input also covers USB-C laptops without a separate Mains device.
        else if (type == "Mains" || (scope == "System" && (type.starts_with("USB") || type == "Wireless")))
        {
            auto online = number<int>(powerSupplyProperty(*values, "ONLINE"));
            external |= online == 1;
            linePowerOffline |= online == 0;
        }
    }
    result.denied |= error.value() == EACCES || error.value() == EPERM;
    if (batteryCount || (!error && !incomplete))
        result.present = batteryCount > 0;
    if (batteryCount == 1 && !error && !incomplete)
    {
        result.state = singleBatteryState;
        result.fraction = singleBatteryFraction;
    }
    if (external)
        result.source = "external";
    else if (!error && !incomplete &&
             ((batteryCount == 1 && singleBatteryState && std::string_view(singleBatteryState) == "discharging") ||
              (linePowerOffline && batteryCount > 0)))
        result.source = "battery";
    return result;
}

void addPolicyValues(ValueMap& result)
{
    std::set<std::string> governors;
    std::set<std::string> preferences;
    std::error_code error;
    int governorError = 0;
    int preferenceError = 0;
    for (std::filesystem::directory_iterator policy("/sys/devices/system/cpu/cpufreq", error), end;
         !error && policy != end; policy.increment(error))
    {
        if (!policy->path().filename().string().starts_with("policy"))
            continue;
        int readError = 0;
        if (auto value = readText(policy->path() / "scaling_governor", &readError); value && !value->empty())
            governors.insert(std::move(*value));
        else if (readError == EACCES || readError == EPERM)
            governorError = readError;
        if (auto value = readText(policy->path() / "energy_performance_preference", &readError); value && !value->empty())
            preferences.insert(std::move(*value));
        else if (readError == EACCES || readError == EPERM)
            preferenceError = readError;
    }
    if (error.value() == EACCES || error.value() == EPERM)
        governorError = preferenceError = error.value();
    for (const auto& [field, entries, denied] :
         {std::tuple{"governors", &governors, governorError},
          std::tuple{"energyPreferences", &preferences, preferenceError}})
    {
        if (denied)
        {
            missing(result, field, "permissionDenied");
            continue;
        }
        if (entries->empty())
            continue;
        ValueVector values;
        for (const auto& entry : *entries)
            values.emplace_back(entry);
        result[field] = std::move(values);
    }
}

std::optional<std::string> readProfile()
{
    SystemBus bus;
    if (auto owner = bus.owner("org.freedesktop.UPower.PowerProfiles"))
    {
        auto profile = bus.text(owner->c_str(), "/org/freedesktop/UPower/PowerProfiles",
                                "org.freedesktop.UPower.PowerProfiles", "ActiveProfile");
        if (profile && !profile->empty())
            return profile;
    }
    if (auto owner = bus.owner("net.hadess.PowerProfiles"))
    {
        auto profile = bus.text(owner->c_str(), "/net/hadess/PowerProfiles", "net.hadess.PowerProfiles", "ActiveProfile");
        if (profile && !profile->empty())
            return profile;
    }
    return readText("/sys/firmware/acpi/platform_profile");
}

void addAllowedCpus(ValueMap& result)
{
    // Linux affinity is per thread. Use the process leader consistently even
    // when invoked from the sampling thread.
    int error = 0;
    for (size_t count = CPU_SETSIZE; count <= 1'048'576; count *= 2)
    {
        std::unique_ptr<cpu_set_t, decltype(&free)> mask(CPU_ALLOC(count), free);
        if (!mask)
            break;
        size_t size = CPU_ALLOC_SIZE(count);
        CPU_ZERO_S(size, mask.get());
        if (sched_getaffinity(getpid(), size, mask.get()) == 0)
        {
            ValueVector cpus;
            for (size_t cpu = 0; cpu < count; ++cpu)
                if (CPU_ISSET_S(cpu, size, mask.get()))
                    cpus.emplace_back(static_cast<unsigned int>(cpu));
            result["allowedCpus"] = std::move(cpus);
            return;
        }
        error = errno;
        if (error != EINVAL)
            break;
    }
    auto status = readText("/proc/self/status");
    if (status)
    {
        for (auto line : words(*status, "\n"))
        {
            constexpr std::string_view key = "Cpus_allowed_list:";
            if (!line.starts_with(key))
                continue;
            auto allowed = cpuList(line.substr(key.size()));
            if (allowed.empty())
                break;
            ValueVector cpus;
            for (auto cpu : allowed)
                cpus.emplace_back(cpu);
            result["allowedCpus"] = std::move(cpus);
            return;
        }
    }
    if (error == EACCES || error == EPERM)
        missing(result, "allowedCpus", "permissionDenied");
}
}

ValueMap readBattery()
{
    auto battery = upowerBattery();
    auto kernel = kernelBattery();
    if (!battery.present)
    {
        battery.present = kernel.present;
        battery.fraction = kernel.fraction;
        battery.state = kernel.state;
    }
    else if (battery.present == true && kernel.present == true)
    {
        if (!battery.fraction)
            battery.fraction = kernel.fraction;
        if (!battery.state)
            battery.state = kernel.state;
    }
    if (!battery.source)
        battery.source = kernel.source;
    ValueMap result;
    if (battery.present)
        result["present"] = *battery.present;
    else if (kernel.denied)
        missing(result, "present", "permissionDenied");
    if (battery.present == false)
    {
        missing(result, "chargeFraction", "notApplicable");
        missing(result, "chargingState", "notApplicable");
    }
    else
    {
        if (battery.fraction)
            result["chargeFraction"] = *battery.fraction;
        if (battery.state)
            result["chargingState"] = battery.state;
    }
    if (battery.source)
        result["powerSource"] = battery.source;
    return result;
}

ValueMap readPowerProfile()
{
    ValueMap result;
    if (auto profile = readProfile(); profile && !profile->empty())
    {
        result["powerPlan"] = *profile;
        if (*profile == "power-saver" || *profile == "low-power")
            result["profile"] = "powerSaver";
        else if (*profile == "balanced" || *profile == "performance")
            result["profile"] = *profile;
    }
    addPolicyValues(result);
    return result;
}

ValueMap readLimits()
{
    ValueMap result;
    addAllowedCpus(result);
    readCgroupLimits(result);
    return result;
}
} // namespace cc::system_info
