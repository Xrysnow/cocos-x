#include "SystemSnapshot-android.h"
#include "platform/SystemCgroupInfo.h"

#include <sched.h>

#include <cerrno>
#include <filesystem>
#include <fstream>
#include <set>

namespace cc::system_info
{
namespace
{
constexpr auto powerClass = "org/cocos/lib/CocosSystemPower";
const std::filesystem::path cpuRoot = "/sys/devices/system/cpu";

struct PowerValues
{
    std::set<std::string> values;
    bool denied = false;

    void collect(const std::filesystem::path& file)
    {
        errno = 0;
        std::ifstream in(file);
        if (!in)
        {
            denied |= errno == EACCES || errno == EPERM;
            return;
        }
        std::string value;
        if (in >> value)
            values.insert(std::move(value));
    }

    void publish(ValueMap& result, const char* field) const
    {
        if (!values.empty())
        {
            ValueVector entries;
            for (const auto& value : values)
                entries.emplace_back(value);
            result[field] = Value(std::move(entries));
        }
        else if (denied)
            missing(result, field, "permissionDenied");
    }
};

void readCpuPolicies(const std::filesystem::path& directory, std::string_view prefix,
                     PowerValues& governors, PowerValues& preferences)
{
    std::error_code ec;
    for (std::filesystem::directory_iterator it(directory, ec), end; it != end && !ec; it.increment(ec))
    {
        const auto name = it->path().filename().string();
        if (!name.starts_with(prefix) || !android::number<unsigned>(std::string_view(name).substr(prefix.size())))
            continue;
        const auto policy = prefix == "cpu" ? it->path() / "cpufreq" : it->path();
        governors.collect(policy / "scaling_governor");
        preferences.collect(policy / "energy_performance_preference");
    }
    if (ec == std::errc::permission_denied)
    {
        governors.denied = true;
        preferences.denied = true;
    }
}

void readAffinity(ValueMap& result)
{
    // This is the effective CPU set of the calling thread, including cpuset
    // restrictions. Grow the mask if the running kernel has more CPUs.
    for (int count = CPU_SETSIZE; count <= 65536; count *= 2)
    {
        const size_t size = CPU_ALLOC_SIZE(count);
        cpu_set_t* mask = CPU_ALLOC(count);
        if (!mask)
            return;
        const int status = sched_getaffinity(0, size, mask);
        const int error = errno;
        ValueVector ids;
        if (status == 0)
        {
            for (int id = 0; id < count; ++id)
            {
                if (CPU_ISSET_S(id, size, mask))
                    ids.emplace_back(id);
            }
        }
        CPU_FREE(mask);
        if (status == 0)
        {
            result["allowedCpus"] = Value(std::move(ids));
            return;
        }
        if (error != EINVAL)
        {
            if (error == EACCES || error == EPERM)
                missing(result, "allowedCpus", "permissionDenied");
            return;
        }
    }
}
} // namespace

ValueMap readPowerProfile()
{
    auto result = android::snapshot(powerClass, "profile");
    if (const auto mode = result.find("lowPowerMode"); mode != result.end())
        mode->second = Value(mode->second.asString() == "true");
    PowerValues governors;
    PowerValues preferences;
    readCpuPolicies(cpuRoot / "cpufreq", "policy", governors, preferences);
    if (governors.values.empty() || preferences.values.empty())
        readCpuPolicies(cpuRoot, "cpu", governors, preferences);
    governors.publish(result, "governors");
    preferences.publish(result, "energyPreferences");
    return result;
}

ValueMap readBattery()
{
    auto result = android::snapshot(powerClass, "battery");
    if (const auto present = result.find("present"); present != result.end())
        present->second = Value(present->second.asString() == "true");
    const auto level = android::takeNumber<unsigned>(result, "level");
    const auto scale = android::takeNumber<unsigned>(result, "scale");
    if (level && scale && *scale != 0 && *level <= *scale)
        result["chargeFraction"] = Value(static_cast<double>(*level) / *scale);
    return result;
}

ValueMap readLimits()
{
    ValueMap result;
    readAffinity(result);
    readCgroupLimits(result);
    return result;
}
} // namespace cc::system_info
