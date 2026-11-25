#include "SystemSnapshot-android.h"

#include <sys/utsname.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

namespace cc::system_info
{
namespace
{
constexpr auto systemClass = "org/cocos/lib/CocosSystemInfo";
constexpr auto cpuRoot = "/sys/devices/system/cpu/";

std::string_view trim(std::string_view value)
{
    constexpr std::string_view whitespace = " \t\r\n";
    const auto first = value.find_first_not_of(whitespace);
    if (first == std::string_view::npos)
        return {};
    return value.substr(first, value.find_last_not_of(whitespace) - first + 1);
}

std::string lineFrom(const std::string& path)
{
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);
    return std::string(trim(line));
}

std::vector<int> cpuList(std::string value)
{
    std::replace(value.begin(), value.end(), ',', ' ');
    std::istringstream in(value);
    std::vector<int> ids;
    for (std::string token; in >> token;)
    {
        const auto separator = token.find('-');
        const auto first = android::number<int>(std::string_view(token).substr(0, separator));
        const auto last = separator == std::string::npos
                              ? first
                              : android::number<int>(std::string_view(token).substr(separator + 1));
        if (!first || !last || *first < 0 || *last < *first || *last >= 65536)
            return {};
        for (int id = *first; id <= *last; ++id)
            ids.push_back(id);
    }
    std::sort(ids.begin(), ids.end());
    ids.erase(std::unique(ids.begin(), ids.end()), ids.end());
    return ids;
}

ValueVector cpuValues(const std::vector<int>& ids)
{
    ValueVector values;
    for (int id : ids)
        values.emplace_back(id);
    return values;
}

using CpuGroups = std::map<int, std::vector<int>>;

CpuGroups readGroups(const std::vector<int>& ids, const char* attribute)
{
    CpuGroups groups;
    for (int id : ids)
    {
        auto members = cpuList(lineFrom(std::string(cpuRoot) + "cpu" + std::to_string(id) + attribute));
        if (!std::binary_search(members.begin(), members.end(), id)
            || !std::includes(ids.begin(), ids.end(), members.begin(), members.end()))
            return {};
        const int group = members.front();
        const auto [existing, inserted] = groups.try_emplace(group, std::move(members));
        if (!inserted && existing->second != members)
            return {};
    }
    std::set<int> seen;
    for (const auto& [_, members] : groups)
    {
        for (int id : members)
        {
            if (!seen.insert(id).second)
                return {};
        }
    }
    return groups;
}

void readCoreFrequencies(const std::string& root, ValueMap& core)
{
    for (const auto& [field, file] : {std::pair{"baseFrequency", "base_frequency"},
                                     std::pair{"maxFrequency", "cpuinfo_max_freq"}})
    {
        const auto khz = android::number<uint64_t>(lineFrom(root + file));
        if (khz && *khz > 0 && *khz <= UINT64_MAX / 1000)
            core[field] = Value(*khz * 1000);
    }
}

void readCoreCaches(const std::string& root, ValueMap& core)
{
    for (int index = 0; index < 16; ++index)
    {
        const auto directory = root + "index" + std::to_string(index) + '/';
        const auto level = android::number<int>(lineFrom(directory + "level"));
        if (!level)
            break;
        auto size = lineFrom(directory + "size");
        if (size.empty())
            continue;
        uint64_t scale = 1;
        if (size.back() == 'K' || size.back() == 'M')
        {
            scale = size.back() == 'K' ? 1024 : 1024 * 1024;
            size.pop_back();
        }
        const auto bytes = android::number<uint64_t>(size);
        if (!bytes || *bytes == 0 || *bytes > UINT64_MAX / scale)
            continue;
        const auto type = lineFrom(directory + "type");
        if (*level == 1)
        {
            if (type == "Data" || type == "Unified")
                core["l1Data"] = Value(*bytes * scale);
            if (type == "Instruction" || type == "Unified")
                core["l1Instruction"] = Value(*bytes * scale);
        }
        else if (type == "Unified" || type == "Data")
        {
            if (*level == 2)
                core["l2"] = Value(*bytes * scale);
            if (*level == 3)
                core["l3"] = Value(*bytes * scale);
        }
    }
}

void readCpuDescription(ValueMap& result)
{
    std::ifstream in("/proc/cpuinfo");
    std::set<std::string> vendors;
    std::set<std::string> models;
    std::set<std::string> flags;
    bool firstFlags = true;
    for (std::string line; std::getline(in, line);)
    {
        const auto separator = line.find(':');
        if (separator == std::string::npos)
            continue;
        const auto key = trim(std::string_view(line).substr(0, separator));
        const auto value = trim(std::string_view(line).substr(separator + 1));
        if (value.empty())
            continue;
        if (key == "vendor_id")
            vendors.emplace(value);
        else if (key == "CPU implementer")
            vendors.emplace(value == "0x41" ? "ARM" : "implementer " + std::string(value));
        else if (key == "model name" && !value.starts_with("ARMv"))
            models.emplace(value);
        else if (key == "flags" || key == "Features")
        {
            std::istringstream names{std::string(value)};
            std::set<std::string> current;
            for (std::string flag; names >> flag;)
                current.insert(std::move(flag));
            if (firstFlags)
            {
                flags = std::move(current);
                firstFlags = false;
            }
            else
            {
                std::set<std::string> common;
                std::set_intersection(flags.begin(), flags.end(), current.begin(), current.end(),
                                      std::inserter(common, common.end()));
                flags = std::move(common);
            }
        }
    }
    if (vendors.size() == 1)
        result["vendor"] = Value(*vendors.begin());
    if (models.size() == 1)
        result["model"] = Value(*models.begin());
    if (!firstFlags)
    {
        ValueVector values;
        for (const auto& flag : flags)
            values.emplace_back(flag);
        result["flags"] = Value(std::move(values));
    }
}
} // namespace

ValueMap readComputer(bool identifiers)
{
    return android::snapshot(systemClass, "computer", "(Z)[Ljava/lang/String;", static_cast<jboolean>(identifiers));
}

ValueMap readOs()
{
    auto result = android::snapshot(systemClass, "os");
    if (const auto item = result.find("abi"); item != result.end())
    {
        const std::string abi = item->second.asString();
        result.erase(item);
        if (abi == "arm64-v8a")
            result["architecture"] = Value("aarch64");
        else if (abi == "armeabi-v7a" || abi == "armeabi")
            result["architecture"] = Value("arm");
        else
            result["architecture"] = Value(abi);
        if (abi == "armeabi-v7a" || abi == "armeabi" || abi == "x86")
            result["bits"] = Value(32);
        else if (abi == "arm64-v8a" || abi == "x86_64" || abi == "riscv64")
            result["bits"] = Value(64);
        result["source"] = Value("system");
    }
    utsname info{};
    if (uname(&info) == 0)
        result["kernel"] = Value(info.release);
    return result;
}

ValueMap readCpu()
{
    ValueMap result;
    const auto ids = cpuList(lineFrom(std::string(cpuRoot) + "present"));
    const auto count = ids.empty() ? sysconf(_SC_NPROCESSORS_CONF) : static_cast<long>(ids.size());
    if (count > 0)
        result["logicalCores"] = Value(static_cast<int>(count));
    readCpuDescription(result);

    const auto cores = readGroups(ids, "/topology/thread_siblings_list");
    if (!cores.empty())
    {
        ValueVector values;
        for (const auto& [id, threads] : cores)
        {
            ValueMap core;
            core["id"] = Value(id);
            core["threads"] = Value(static_cast<int>(threads.size()));
            core["logicalCpus"] = Value(cpuValues(threads));
            const auto coreRoot = std::string(cpuRoot) + "cpu" + std::to_string(id);
            readCoreFrequencies(coreRoot + "/cpufreq/", core);
            readCoreCaches(coreRoot + "/cache/", core);
            values.emplace_back(std::move(core));
        }
        result["physicalCores"] = Value(static_cast<int>(values.size()));
        result["cores"] = Value(std::move(values));
    }

    auto clusters = readGroups(ids, "/topology/cluster_cpus_list");
    const bool explicitTopology = !clusters.empty();
    if (!explicitTopology)
        clusters = readGroups(ids, "/cpufreq/related_cpus");
    if (!clusters.empty())
    {
        ValueVector values;
        for (const auto& [id, threads] : clusters)
        {
            ValueMap cluster;
            cluster["id"] = Value(id);
            cluster["logicalCpus"] = Value(cpuValues(threads));
            cluster["logicalCores"] = Value(static_cast<int>(threads.size()));
            cluster["source"] = Value(explicitTopology ? "kernelTopology" : "cpufreqPolicy");
            values.emplace_back(std::move(cluster));
        }
        result["clusters"] = Value(std::move(values));
    }
    return result;
}

ValueMap readMemory()
{
    auto result = android::snapshot(systemClass, "memory");
    for (const char* key : {"total", "available"})
    {
        if (const auto bytes = android::takeNumber<uint64_t>(result, key))
            result[key] = Value(*bytes);
    }
    std::ifstream in("/proc/meminfo");
    for (std::string line; std::getline(in, line);)
    {
        if (!line.starts_with("MemFree:"))
            continue;
        std::istringstream parts(line.substr(8));
        uint64_t kib = 0;
        std::string units;
        if (parts >> kib >> units && units == "kB" && kib <= UINT64_MAX / 1024)
            result["free"] = Value(kib * 1024);
        break;
    }
    return result;
}

ValueMap readUptime()
{
    auto result = android::snapshot(systemClass, "uptime");
    if (const auto ms = android::takeNumber<uint64_t>(result, "elapsedMillis"))
        result["seconds"] = Value(*ms / 1000.0);
    if (const auto ms = android::takeNumber<uint64_t>(result, "bootMillis"))
        result["bootTime"] = Value(*ms / 1000);
    return result;
}
} // namespace cc::system_info
