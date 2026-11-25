#pragma once

#include "platform/SystemInfoInternal.h"
#include "platform/linux/SystemInfo-linux-private.h"

#include <algorithm>
#include <limits>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

namespace cc::system_info
{
namespace cgroup_detail
{
using namespace linux_detail;

struct Membership
{
    std::string_view unified;
    std::string_view cpu;
    std::string_view memory;
};

inline bool includes(std::string_view list, std::string_view value)
{
    auto items = words(list, ",");
    return std::find(items.begin(), items.end(), value) != items.end();
}

inline Membership membership(std::string_view contents)
{
    Membership result;
    for (auto line : words(contents, "\n"))
    {
        auto first = line.find(':');
        if (first == line.npos)
            continue;
        auto last = line.find(':', first + 1);
        if (last == line.npos)
            continue;
        auto controllers = line.substr(first + 1, last - first - 1);
        auto path = line.substr(last + 1);
        if (path.empty() || path.front() != '/')
            continue;
        if (controllers.empty() && line.substr(0, first) == "0")
            result.unified = path;
        if (includes(controllers, "cpu"))
            result.cpu = path;
        if (includes(controllers, "memory"))
            result.memory = path;
    }
    return result;
}

inline std::string decodeMountPath(std::string_view path)
{
    std::string result;
    for (size_t i = 0; i < path.size(); ++i)
    {
        auto code = path[i] == '\\' ? path.substr(i + 1, 3) : std::string_view{};
        if (code.size() == 3 && code.find_first_not_of("01234567") == code.npos)
        {
            result += static_cast<char>((code[0] - '0') * 64 + (code[1] - '0') * 8 + code[2] - '0');
            i += 3;
        }
        else
            result += path[i];
    }
    return result;
}

struct Mount
{
    std::filesystem::path root;
    std::filesystem::path mountPoint;
    std::filesystem::path directory;
    bool unified = false;
};

inline std::optional<Mount> locate(std::string_view mountInfo, std::string_view controller, std::string_view path,
                                  bool unified)
{
    if (path.empty())
        return std::nullopt;
    std::filesystem::path member(path);
    if (std::find(member.begin(), member.end(), "..") != member.end())
        return std::nullopt; // The process membership is outside this cgroup namespace's root.
    std::optional<Mount> best;
    for (auto line : words(mountInfo, "\n"))
    {
        auto separator = line.find(" - ");
        if (separator == line.npos)
            continue;
        auto before = words(line.substr(0, separator));
        auto after = words(line.substr(separator + 3));
        if (before.size() < 5 || after.size() < 3 ||
            (unified ? after[0] != "cgroup2" : after[0] != "cgroup" || !includes(after[2], controller)))
            continue;
        std::filesystem::path root(decodeMountPath(before[3]));
        auto relative = member.lexically_relative(root);
        if (relative.empty() || *relative.begin() == "..")
            continue;
        std::filesystem::path mountPoint(decodeMountPath(before[4]));
        if (!best || root.native().size() < best->root.native().size())
        {
            auto directory = relative == "." ? mountPoint : mountPoint / relative;
            best = Mount{std::move(root), std::move(mountPoint), std::move(directory), unified};
        }
    }
    return best;
}

template <typename T>
struct Limit
{
    std::optional<T> value;
    const char* reason = nullptr;
};

inline const char* missingReason(int error)
{
    return error == EACCES || error == EPERM ? "permissionDenied" : "unknown";
}

inline bool absent(int error)
{
    return error == ENOENT || error == ENOTDIR;
}

inline Limit<double> cpuLimit(const std::filesystem::path& directory, bool unified)
{
    int error = 0;
    auto text = readText(directory / (unified ? "cpu.max" : "cpu.cfs_quota_us"), &error);
    if (!text)
        return {std::nullopt, absent(error) ? nullptr : missingReason(error)};
    std::optional<uint64_t> period;
    std::optional<uint64_t> quota;
    if (unified)
    {
        auto fields = words(*text);
        if (fields.size() != 2)
            return {std::nullopt, "unknown"};
        if (fields[0] == "max")
            return {};
        quota = number<uint64_t>(fields[0]);
        period = number<uint64_t>(fields[1]);
    }
    else
    {
        if (*text == "-1")
            return {};
        quota = number<uint64_t>(*text);
        period = readNumber<uint64_t>(directory / "cpu.cfs_period_us", &error);
    }
    if (!quota || !period || *period == 0)
        return {std::nullopt, missingReason(error)};
    return {static_cast<double>(*quota) / *period, nullptr};
}

inline uint64_t unlimitedMemoryV1()
{
    auto pageSize = sysconf(_SC_PAGESIZE);
    if (pageSize <= 0)
        return std::numeric_limits<uint64_t>::max();
    // The value is generated by the kernel's PAGE_COUNTER_MAX, even for a 32-bit client.
    struct utsname kernel{};
    if (uname(&kernel) == 0 && std::string_view(kernel.machine).find("64") != std::string_view::npos)
        return (static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) / pageSize) * pageSize;
    auto longMax = static_cast<uint64_t>(std::numeric_limits<long>::max());
    return sizeof(long) == 4 ? longMax * pageSize : (longMax / pageSize) * pageSize;
}

inline Limit<uint64_t> memoryV1(const std::filesystem::path& directory)
{
    int error = 0;
    auto text = readText(directory / "memory.stat", &error);
    if (!text)
        return {std::nullopt, missingReason(error)};
    for (auto line : words(*text, "\n"))
    {
        constexpr std::string_view key = "hierarchical_memory_limit ";
        if (!line.starts_with(key))
            continue;
        auto value = number<uint64_t>(line.substr(key.size()));
        if (!value)
            break;
        if (*value == unlimitedMemoryV1())
            return {std::nullopt, "unlimited"};
        return {value, nullptr};
    }
    return {std::nullopt, "unknown"};
}

inline Limit<uint64_t> memoryLimit(const std::filesystem::path& directory, bool)
{
    int error = 0;
    auto text = readText(directory / "memory.max", &error);
    if (!text)
        return {std::nullopt, absent(error) ? nullptr : missingReason(error)};
    if (*text == "max")
        return {};
    auto value = number<uint64_t>(*text);
    return {value, value ? nullptr : "unknown"};
}

template <typename T>
Limit<T> ancestorLimit(const Mount& mount, Limit<T> (*readLimit)(const std::filesystem::path&, bool))
{
    // A subtree mount cannot expose constraints imposed by a hidden ancestor.
    // A cgroup namespace can report its subtree as "/" in mountinfo. The actual
    // kernfs hierarchy root has inode 1, independent of its namespace view.
    struct stat root{};
    if (mount.root != "/")
        return {std::nullopt, "unknown"};
    if (stat(mount.mountPoint.c_str(), &root) != 0)
        return {std::nullopt, missingReason(errno)};
    if (root.st_ino != 1)
        return {std::nullopt, "unknown"};
    Limit<T> result;
    for (auto directory = mount.directory;; directory = directory.parent_path())
    {
        std::error_code error;
        if (!std::filesystem::is_directory(directory, error))
            return {std::nullopt, missingReason(error.value())};
        auto limit = readLimit(directory, mount.unified);
        if (limit.reason)
            return limit;
        if (limit.value && (!result.value || *limit.value < *result.value))
            result.value = limit.value;
        if (directory == mount.mountPoint)
            break;
    }
    if (!result.value)
        result.reason = "unlimited";
    return result;
}

template <typename T>
void addLimit(ValueMap& result, const char* field, Limit<T> limit)
{
    if (limit.value)
        result[field] = *limit.value;
    else if (limit.reason)
        missing(result, field, limit.reason);
}
}

inline void readCgroupLimits(ValueMap& result)
{
    using namespace cgroup_detail;
    int error = 0;
    auto cgroups = readText("/proc/self/cgroup", &error);
    auto mounts = cgroups ? readText("/proc/self/mountinfo", &error) : std::nullopt;
    if (!cgroups || !mounts)
    {
        missing(result, "cpuQuota", missingReason(error));
        missing(result, "memoryLimit", missingReason(error));
        return;
    }
    auto process = membership(*cgroups);
    auto cpuMount = locate(*mounts, "cpu", process.cpu.empty() ? process.unified : process.cpu, process.cpu.empty());
    auto memoryMount = locate(*mounts, "memory", process.memory.empty() ? process.unified : process.memory, process.memory.empty());
    auto cpu = cpuMount ? ancestorLimit(*cpuMount, cpuLimit) : Limit<double>{};
    Limit<uint64_t> memory;
    if (memoryMount)
        memory = memoryMount->unified ? ancestorLimit(*memoryMount, memoryLimit) : memoryV1(memoryMount->directory);
    if (readText("/proc/self/cgroup") != cgroups)
    {
        missing(result, "cpuQuota", "pending");
        missing(result, "memoryLimit", "pending");
        return;
    }
    addLimit(result, "cpuQuota", cpu);
    addLimit(result, "memoryLimit", memory);
}
} // namespace cc::system_info
