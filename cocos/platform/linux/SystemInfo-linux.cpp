#include "platform/SystemInfoInternal.h"
#include "platform/linux/SystemInfo-linux-private.h"

#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

namespace cc::system_info
{
namespace
{
using namespace linux_detail;
using TextFields = std::map<std::string_view, std::string_view>;

constexpr auto cpuRoot = "/sys/devices/system/cpu";
constexpr auto dmiRoot = "/sys/devices/virtual/dmi/id";

const char* fileFailure(int error)
{
    return error == EACCES || error == EPERM ? "permissionDenied" : "ioError";
}

void addText(ValueMap& result, const char* key, const std::filesystem::path& path)
{
    int error = 0;
    auto value = readText(path, &error);
    if (value && !value->empty() && *value != "To Be Filled By O.E.M." && *value != "Default string" &&
        *value != "Not Specified" && *value != "None")
        result[key] = std::move(*value);
    else if (error == EACCES || error == EPERM)
        missing(result, key, "permissionDenied");
}

const char* dmiChassis(unsigned int type)
{
    switch (type & 0x7f)
    {
    case 3: case 4: case 5: case 6: case 7:
        return "desktop";
    case 8: case 9: case 10: case 14: case 31: case 32:
        return "laptop";
    case 13:
        return "allInOne";
    case 17: case 23: case 28: case 29:
        return "server";
    case 30:
        return "tablet";
    case 35: case 36:
        return "miniPc";
    case 1: case 11: case 12: case 15: case 16: case 18: case 19: case 20:
    case 21: case 22: case 24: case 25: case 26: case 27: case 33: case 34:
        return "other";
    default:
        return nullptr;
    }
}

void addUuid(ValueMap& result, const std::filesystem::path& path)
{
    int error = 0;
    auto uuid = readText(path, &error);
    if (!uuid)
    {
        if (error == EACCES || error == EPERM)
            missing(result, "uuid", "permissionDenied");
        return;
    }
    if (uuid->size() != 36)
        return;
    bool allZero = true;
    bool allF = true;
    for (size_t i = 0; i < uuid->size(); ++i)
    {
        char& digit = (*uuid)[i];
        if (i == 8 || i == 13 || i == 18 || i == 23)
        {
            if (digit != '-')
                return;
            continue;
        }
        if (digit >= 'A' && digit <= 'F')
            digit += 'a' - 'A';
        if ((digit < '0' || digit > '9') && (digit < 'a' || digit > 'f'))
            return;
        allZero &= digit == '0';
        allF &= digit == 'f';
    }
    if (!allZero && !allF)
        result["uuid"] = std::move(*uuid);
}

std::string releaseValue(std::string_view value)
{
    value = trim(value);
    if (value.size() < 2 || (value.front() != '\'' && value.front() != '"'))
        return std::string(value);
    char quote = value.front();
    if (value.back() != quote)
        return {};
    value.remove_prefix(1);
    value.remove_suffix(1);
    if (quote == '\'')
        return std::string(value);
    std::string decoded;
    for (size_t i = 0; i < value.size(); ++i)
    {
        if (value[i] == '\\' && i + 1 < value.size() && std::string_view(R"("\$`)").find(value[i + 1]) != std::string_view::npos)
            ++i;
        decoded += value[i];
    }
    return decoded;
}

unsigned int architectureBits(std::string_view architecture)
{
    if (architecture == "x86_64" || architecture == "aarch64" || architecture == "aarch64_be" ||
        architecture == "s390x" || architecture == "loongarch64" || architecture == "alpha" ||
        architecture == "ia64" || architecture == "sw_64" || architecture == "sparc64" ||
        architecture.starts_with("ppc64") || architecture.starts_with("mips64") || architecture == "riscv64")
        return 64;
    if (architecture == "i386" || architecture == "i486" || architecture == "i586" || architecture == "i686" ||
        architecture.starts_with("armv") || architecture == "ppc" || architecture == "mips" ||
        architecture == "riscv32" || architecture == "s390" || architecture == "sparc")
        return 32;
    return 0;
}

// Views remain valid while the original contents of /proc/cpuinfo are stored.
std::map<unsigned int, TextFields> parseCpuInfo(std::string_view contents, TextFields& global)
{
    std::map<unsigned int, TextFields> processors;
    TextFields* fields = &global;
    for (auto line : words(contents, "\n"))
    {
        auto separator = line.find(':');
        if (separator == line.npos)
            continue;
        auto key = trim(line.substr(0, separator));
        auto value = trim(line.substr(separator + 1));
        if (key == "processor")
        {
            if (auto cpu = number<unsigned int>(value))
                fields = &processors[*cpu];
        }
        else if (!value.empty())
            fields->insert_or_assign(key, value);
    }
    return processors;
}

std::string_view findText(const TextFields& fields, std::initializer_list<std::string_view> keys)
{
    for (auto key : keys)
    {
        auto value = fields.find(key);
        if (value != fields.end())
            return value->second;
    }
    return {};
}

struct CpuText
{
    std::string_view vendor;
    std::string_view model;
    std::optional<std::set<std::string_view>> flags;
};

CpuText cpuText(const TextFields& fields, const TextFields& global)
{
    CpuText result;
    result.vendor = findText(fields, {"vendor_id", "vendor"});
    if (result.vendor.empty())
        result.vendor = findText(global, {"vendor_id", "vendor"});
    result.model = findText(fields, {"model name", "Processor", "cpu"});
    if (result.model.empty())
        result.model = findText(global, {"model name", "Processor", "cpu"});
    auto features = findText(fields, {"flags", "Features"});
    if (features.empty())
        features = findText(global, {"flags", "Features"});
    if (!features.empty())
    {
        auto flags = words(features);
        result.flags.emplace(flags.begin(), flags.end());
    }
    return result;
}

void mergeCpuText(std::optional<CpuText>& summary, CpuText cpu)
{
    if (!summary)
    {
        summary = std::move(cpu);
        return;
    }
    if (summary->model != cpu.model)
        summary->model = {};
    if (summary->vendor != cpu.vendor)
        summary->vendor = {};
    if (summary->flags && cpu.flags)
    {
        std::set<std::string_view> common;
        std::set_intersection(summary->flags->begin(), summary->flags->end(), cpu.flags->begin(), cpu.flags->end(),
                              std::inserter(common, common.end()));
        summary->flags = std::move(common);
    }
    else
        summary->flags.reset();
}

void addCpuText(ValueMap& result, const std::optional<CpuText>& info)
{
    if (!info)
        return;
    if (!info->vendor.empty())
        result["vendor"] = info->vendor;
    if (!info->model.empty())
        result["model"] = info->model;
    if (info->flags)
    {
        ValueVector flags;
        for (auto flag : *info->flags)
            flags.emplace_back(flag);
        result["flags"] = std::move(flags);
    }
}

ValueVector cpuNumbers(const std::vector<unsigned int>& cpus)
{
    ValueVector result;
    for (auto cpu : cpus)
        result.emplace_back(cpu);
    return result;
}

std::optional<uint64_t> scaledBytes(std::string_view text)
{
    text = trim(text);
    auto digits = text.find_first_not_of("0123456789");
    auto value = number<uint64_t>(text.substr(0, digits));
    if (!value)
        return std::nullopt;
    auto suffix = digits == text.npos ? std::string_view{} : trim(text.substr(digits));
    uint64_t scale = 1;
    if (suffix == "K" || suffix == "kB")
        scale = 1024;
    else if (suffix == "M")
        scale = 1024 * 1024;
    else if (!suffix.empty())
        return std::nullopt;
    if (*value > std::numeric_limits<uint64_t>::max() / scale)
        return std::nullopt;
    return *value * scale;
}

void addCoreDetails(ValueMap& fields, const std::filesystem::path& cpuPath)
{
    std::error_code error;
    for (std::filesystem::directory_iterator entry(cpuPath / "cache", error), end; !error && entry != end; entry.increment(error))
    {
        const auto& path = entry->path();
        if (!path.filename().string().starts_with("index"))
            continue;
        auto level = readNumber<unsigned int>(path / "level");
        auto type = readText(path / "type");
        auto sizeText = readText(path / "size");
        auto size = sizeText ? scaledBytes(*sizeText) : std::nullopt;
        if (!level || !type || !size)
            continue;
        if (*level == 1 && (*type == "Data" || *type == "Unified"))
            fields["l1Data"] = *size;
        if (*level == 1 && (*type == "Instruction" || *type == "Unified"))
            fields["l1Instruction"] = *size;
        if (*level == 2 && *type == "Unified")
            fields["l2"] = *size;
        if (*level == 3 && *type == "Unified")
            fields["l3"] = *size;
    }
    for (const auto& [file, field] : {std::pair{"base_frequency", "baseFrequency"},
                                      std::pair{"cpuinfo_max_freq", "maxFrequency"}})
        if (auto frequency = readNumber<uint64_t>(cpuPath / "cpufreq" / file);
            frequency && *frequency > 0 && *frequency <= std::numeric_limits<uint64_t>::max() / 1000)
            fields[field] = *frequency * 1000;
}

struct CpuGroup
{
    std::vector<unsigned int> cpus;
    std::set<unsigned int> cores;
    std::optional<CpuText> summary;
};

ValueMap describeGroup(int id, CpuGroup& group, bool completeCores)
{
    ValueMap result;
    result["id"] = id;
    result["logicalCores"] = static_cast<unsigned int>(group.cpus.size());
    result["logicalCpus"] = cpuNumbers(group.cpus);
    if (completeCores)
        result["physicalCores"] = static_cast<unsigned int>(group.cores.size());
    addCpuText(result, group.summary);
    return result;
}
}

ValueMap readComputer(bool identifiers)
{
    ValueMap result;
    std::filesystem::path dmi(dmiRoot);
    addText(result, "vendor", dmi / "sys_vendor");
    addText(result, "model", dmi / "product_name");
    addText(result, "family", dmi / "product_family");
    addText(result, "version", dmi / "product_version");
    addText(result, "sku", dmi / "product_sku");
    if (!result.contains("model"))
    {
        // Device Tree string properties are terminated by NUL rather than a newline.
        auto model = readText("/sys/firmware/devicetree/base/model");
        if (model)
        {
            model->resize(std::min(model->size(), model->find('\0')));
            if (!model->empty())
                result["model"] = std::move(*model);
        }
    }
    if (auto type = readNumber<unsigned int>(dmi / "chassis_type"))
        if (auto chassis = dmiChassis(*type))
            result["chassis"] = chassis;
    addText(result, "socModel", "/sys/devices/soc0/soc_id");
    if (identifiers)
    {
        addText(result, "serialNumber", dmi / "product_serial");
        addUuid(result, dmi / "product_uuid");
    }
    return result;
}

ValueMap readOs()
{
    struct utsname system{};
    if (uname(&system) != 0)
        return failure("ioError", "uname", errno);
    ValueMap result;
    result["family"] = "Linux";
    result["name"] = "Linux";
    result["kernel"] = system.release;
    result["architecture"] = system.machine;
    result["architectureScope"] = "system";
    result["source"] = "uname";
    if (auto bits = architectureBits(system.machine))
        result["bits"] = bits;
    auto release = readText("/etc/os-release");
    if (!release)
        release = readText("/usr/lib/os-release");
    if (!release)
        return result;
    for (auto line : words(*release, "\n"))
    {
        auto separator = line.find('=');
        if (separator == line.npos)
            continue;
        auto key = trim(line.substr(0, separator));
        auto value = releaseValue(line.substr(separator + 1));
        if (value.empty())
            continue;
        if (key == "NAME")
            result["name"] = std::move(value);
        else if (key == "PRETTY_NAME")
            result["marketingName"] = std::move(value);
        else if (key == "VERSION_ID")
            result["version"] = std::move(value);
        else if (key == "BUILD_ID")
            result["build"] = std::move(value);
    }
    result["source"] = "os-release";
    return result;
}

ValueMap readCpu()
{
    auto infoText = readText("/proc/cpuinfo");
    TextFields global;
    auto processors = infoText ? parseCpuInfo(*infoText, global) : std::map<unsigned int, TextFields>{};
    auto onlineText = readText(std::filesystem::path(cpuRoot) / "online");
    auto cpus = onlineText ? cpuList(*onlineText) : std::vector<unsigned int>{};
    if (cpus.empty())
        for (const auto& [cpu, ignored] : processors)
            cpus.push_back(cpu);

    ValueMap result;
    if (cpus.empty())
    {
        auto count = sysconf(_SC_NPROCESSORS_ONLN);
        if (count <= 0)
            return failure("ioError", "sysconf(_SC_NPROCESSORS_ONLN)", errno);
        result["logicalCores"] = static_cast<uint64_t>(count);
        addCpuText(result, cpuText(global, global));
        return result;
    }
    result["logicalCores"] = static_cast<unsigned int>(cpus.size());
    std::set<unsigned int> online(cpus.begin(), cpus.end());
    std::optional<CpuText> summary;
    std::set<unsigned int> describedCores;
    auto completeCores = true;
    auto completePackages = true;
    auto completeClusters = true;
    std::map<int, CpuGroup> packages;
    std::map<std::pair<int, int>, CpuGroup> clusters;
    ValueVector cores;
    for (auto cpu : cpus)
    {
        auto cpuPath = std::filesystem::path(cpuRoot) / ("cpu" + std::to_string(cpu));
        auto topology = cpuPath / "topology";
        auto package = readNumber<int>(topology / "physical_package_id");
        auto cluster = readNumber<int>(topology / "cluster_id");
        auto siblings = readText(topology / "core_cpus_list");
        if (!siblings)
            siblings = readText(topology / "thread_siblings_list");
        auto threads = siblings ? cpuList(*siblings) : std::vector<unsigned int>{};
        std::erase_if(threads, [&online](auto thread) { return !online.contains(thread); });
        if (std::find(threads.begin(), threads.end(), cpu) == threads.end())
            threads.clear();
        completeCores &= !threads.empty();
        completePackages &= package && *package >= 0;
        completeClusters &= cluster && *cluster >= 0;
        auto info = processors.find(cpu);
        auto cpuInfo = cpuText(info == processors.end() ? global : info->second, global);
        mergeCpuText(summary, cpuInfo);
        if (package && *package >= 0)
        {
            auto& group = packages[*package];
            group.cpus.push_back(cpu);
            mergeCpuText(group.summary, cpuInfo);
            if (!threads.empty())
                group.cores.insert(threads.front());
        }
        if (cluster && *cluster >= 0)
        {
            auto& group = clusters[{package.value_or(-1), *cluster}];
            group.cpus.push_back(cpu);
            mergeCpuText(group.summary, cpuInfo);
            if (!threads.empty())
                group.cores.insert(threads.front());
        }
        if (threads.empty() || !describedCores.insert(threads.front()).second)
            continue;
        ValueMap core;
        if (auto coreId = readNumber<int>(topology / "core_id"); coreId && *coreId >= 0)
            core["id"] = *coreId;
        if (package && *package >= 0)
            core["packageId"] = *package;
        core["threads"] = static_cast<unsigned int>(threads.size());
        core["logicalCpus"] = cpuNumbers(threads);
        addCoreDetails(core, cpuPath);
        cores.emplace_back(std::move(core));
    }
    addCpuText(result, summary);
    if (completeCores)
    {
        result["physicalCores"] = static_cast<unsigned int>(cores.size());
        result["cores"] = std::move(cores);
    }
    if (completePackages)
    {
        ValueVector groups;
        for (auto& [id, group] : packages)
            groups.emplace_back(describeGroup(id, group, completeCores));
        result["packages"] = std::move(groups);
    }
    if (completeClusters && (!completePackages || clusters.size() > packages.size()))
    {
        ValueVector groups;
        for (auto& [ids, group] : clusters)
        {
            auto fields = describeGroup(ids.second, group, completeCores);
            if (ids.first >= 0)
                fields["packageId"] = ids.first;
            groups.emplace_back(std::move(fields));
        }
        result["clusters"] = std::move(groups);
    }
    return result;
}

ValueMap readMemory()
{
    int error = 0;
    auto memory = readText("/proc/meminfo", &error);
    ValueMap result;
    if (memory)
    {
        for (auto line : words(*memory, "\n"))
        {
            auto separator = line.find(':');
            if (separator == line.npos)
                continue;
            auto key = line.substr(0, separator);
            if (key != "MemTotal" && key != "MemFree" && key != "MemAvailable")
                continue;
            if (auto bytes = scaledBytes(line.substr(separator + 1)))
                result[key == "MemTotal" ? "total" : key == "MemFree" ? "free" : "available"] = *bytes;
        }
        if (result.contains("total") && result.contains("free"))
            return result;
    }
    struct sysinfo stats{};
    if (sysinfo(&stats) != 0)
        return failure(fileFailure(error ? error : errno), "read /proc/meminfo or sysinfo", error ? error : errno);
    if (!result.contains("total"))
        result["total"] = static_cast<uint64_t>(stats.totalram) * stats.mem_unit;
    if (!result.contains("free"))
        result["free"] = static_cast<uint64_t>(stats.freeram) * stats.mem_unit;
    if (!memory && (error == EACCES || error == EPERM))
        missing(result, "available", "permissionDenied");
    return result;
}

ValueMap readUptime()
{
    timespec elapsed{};
    if (clock_gettime(CLOCK_BOOTTIME, &elapsed) != 0)
        return failure("ioError", "clock_gettime(CLOCK_BOOTTIME)", errno);
    ValueMap result;
    result["seconds"] = static_cast<uint64_t>(elapsed.tv_sec);
    if (auto stat = readText("/proc/stat"))
    {
        for (auto line : words(*stat, "\n"))
        {
            if (!line.starts_with("btime "))
                continue;
            if (auto boot = number<int64_t>(line.substr(6)))
                result["bootTime"] = *boot;
            break;
        }
    }
    if (!result.contains("bootTime"))
    {
        timespec realtime{};
        if (clock_gettime(CLOCK_REALTIME, &realtime) == 0)
            result["bootTime"] = static_cast<int64_t>(realtime.tv_sec) - elapsed.tv_sec -
                                 (realtime.tv_nsec < elapsed.tv_nsec ? 1 : 0);
    }
    return result;
}
} // namespace cc::system_info
