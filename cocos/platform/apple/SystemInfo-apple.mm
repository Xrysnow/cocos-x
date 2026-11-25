#include "platform/SystemInfoInternal.h"

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <IOKit/IOKitLib.h>
#endif

#include <mach/mach.h>
#include <mach/mach_time.h>
#include <sys/sysctl.h>
#include <sys/time.h>

#include <algorithm>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

namespace cc::system_info
{
namespace
{
template<typename T>
std::optional<T> sysctlValue(const char* key)
{
    T value{};
    size_t size = sizeof(value);
    if (sysctlbyname(key, &value, &size, nullptr, 0) == 0 && size == sizeof(value))
        return value;
    return std::nullopt;
}

std::string sysctlText(const char* key)
{
    size_t size = 0;
    if (sysctlbyname(key, nullptr, &size, nullptr, 0) != 0 || size == 0)
        return {};
    std::string value(size, '\0');
    if (sysctlbyname(key, value.data(), &size, nullptr, 0) != 0)
        return {};
    value.resize(size);
    if (!value.empty() && value.back() == '\0')
        value.pop_back();
    return value;
}

void putText(ValueMap& result, const char* field, std::string value)
{
    if (!value.empty())
        result[field] = Value(std::move(value));
}

void putCount(ValueMap& result, const char* field, const char* key)
{
    if (auto count = sysctlValue<uint32_t>(key); count && *count > 0)
        result[field] = Value(*count);
}

std::string processVersion()
{
    const auto version = NSProcessInfo.processInfo.operatingSystemVersion;
    if (version.majorVersion <= 0)
        return {};
    auto text = std::to_string(version.majorVersion) + "." + std::to_string(version.minorVersion);
    if (version.patchVersion > 0)
        text += "." + std::to_string(version.patchVersion);
    return text;
}

#if TARGET_OS_OSX
const char* macChassis(std::string_view model)
{
    if (model.starts_with("MacBook"))
        return "laptop";
    if (model.starts_with("iMac"))
        return "allInOne";
    if (model.starts_with("Macmini") || model.starts_with("MacStudio"))
        return "miniPc";
    if (model.starts_with("MacPro"))
        return "desktop";
    if (model.starts_with("Xserve"))
        return "server";
    return nullptr;
}

void readMacIdentifiers(ValueMap& result)
{
    const auto matching = IOServiceMatching("IOPlatformExpertDevice");
    if (!matching)
        return;
    const auto service = IOServiceGetMatchingService(kIOMainPortDefault, matching);
    if (!service)
        return;

    id serial = CFBridgingRelease(IORegistryEntryCreateCFProperty(
        service, CFSTR(kIOPlatformSerialNumberKey), kCFAllocatorDefault, 0));
    id uuid = CFBridgingRelease(IORegistryEntryCreateCFProperty(
        service, CFSTR(kIOPlatformUUIDKey), kCFAllocatorDefault, 0));
    IOObjectRelease(service);
    if ([serial isKindOfClass:NSString.class] && [serial length] > 0)
        putText(result, "serialNumber", [serial UTF8String] ?: "");
    if ([uuid isKindOfClass:NSString.class])
    {
        NSUUID* parsed = [[NSUUID alloc] initWithUUIDString:uuid];
        putText(result, "uuid", parsed.UUIDString.UTF8String ?: "");
    }
}
#else
std::string mobileModel()
{
#if TARGET_OS_SIMULATOR
    return NSProcessInfo.processInfo.environment[@"SIMULATOR_MODEL_IDENTIFIER"].UTF8String ?: "";
#else
    return sysctlText("hw.machine");
#endif
}
#endif

ValueVector cpuFlags()
{
    ValueVector result;
#if defined(__arm64__)
    constexpr struct
    {
        const char* key;
        const char* feature;
    } features[] = {
        {"hw.optional.neon", "neon"},
        {"hw.optional.arm.FEAT_AES", "aes"},
        {"hw.optional.arm.FEAT_CRC32", "crc32"},
        {"hw.optional.arm.FEAT_DotProd", "dotprod"},
        {"hw.optional.arm.FEAT_FP16", "fp16"},
        {"hw.optional.arm.FEAT_LSE", "lse"},
        {"hw.optional.arm.FEAT_PMULL", "pmull"},
        {"hw.optional.arm.FEAT_RDM", "rdm"},
        {"hw.optional.arm.FEAT_SHA1", "sha1"},
        {"hw.optional.arm.FEAT_SHA256", "sha256"},
        {"hw.optional.arm.FEAT_SHA3", "sha3"},
        {"hw.optional.arm.FEAT_SHA512", "sha512"},
    };
    for (const auto& feature : features)
    {
        if (sysctlValue<uint32_t>(feature.key).value_or(0) != 0)
            result.emplace_back(feature.feature);
    }
#elif defined(__x86_64__)
    for (const auto* key : {"machdep.cpu.features", "machdep.cpu.leaf7_features", "machdep.cpu.extfeatures"})
    {
        std::istringstream tokens(sysctlText(key));
        std::string feature;
        while (tokens >> feature)
        {
            for (auto& letter : feature)
            {
                if (letter >= 'A' && letter <= 'Z')
                    letter = static_cast<char>(letter - 'A' + 'a');
            }
            result.emplace_back(std::move(feature));
        }
    }
#endif
    return result;
}

ValueVector cpuClusters()
{
    ValueVector result;
    const auto count = sysctlValue<uint32_t>("hw.nperflevels").value_or(0);
    for (uint32_t id = 0; id < count; ++id)
    {
        const auto prefix = "hw.perflevel" + std::to_string(id);
        ValueMap cluster;
        putCount(cluster, "physicalCores", (prefix + ".physicalcpu").c_str());
        putCount(cluster, "logicalCores", (prefix + ".logicalcpu").c_str());
        if (cluster.empty())
            continue;

        auto name = sysctlText((prefix + ".name").c_str());
        if (name == "Performance")
            cluster["type"] = Value("performance");
        else if (name == "Efficiency")
            cluster["type"] = Value("efficiency");
        cluster["id"] = Value(id);
        result.emplace_back(std::move(cluster));
    }
    return result;
}
}

ValueMap readComputer(bool identifiers)
{
    @autoreleasepool
    {
        ValueMap result;
        result["vendor"] = Value("Apple");
#if TARGET_OS_OSX
        result["family"] = Value("Mac");
        auto model = sysctlText("hw.model");
        if (const auto* chassis = macChassis(model))
            result["chassis"] = Value(chassis);
        putText(result, "model", std::move(model));
#if defined(__arm64__)
        auto brand = sysctlText("machdep.cpu.brand_string");
        if (brand.starts_with("Apple M"))
            putText(result, "socModel", std::move(brand));
#endif
        if (identifiers)
            readMacIdentifiers(result);
#else
        auto model = mobileModel();
        if (model.starts_with("iPad"))
        {
            result["family"] = Value("iPad");
            result["chassis"] = Value("tablet");
        }
        else if (model.starts_with("iPhone"))
        {
            result["family"] = Value("iPhone");
            result["chassis"] = Value("phone");
        }
        else if (model.starts_with("iPod"))
            result["family"] = Value("iPod");

        putText(result, "model", std::move(model));
        if (identifiers)
        {
            missing(result, "serialNumber", "unsupported");
            missing(result, "uuid", "unsupported");
        }
#if TARGET_OS_SIMULATOR
        result["source"] = Value("simulatorDevice");
#endif
#endif
        return result;
    }
}

ValueMap readOs()
{
    @autoreleasepool
    {
        ValueMap result;
#if TARGET_OS_OSX
        const char* name = "macOS";
        auto version = sysctlText("kern.osproductversion");
#else
        const char* name = mobileModel().starts_with("iPad") ? "iPadOS" : "iOS";
        std::string version;
#endif
        if (version.empty())
            version = processVersion();
        result["family"] = Value(name);
        result["name"] = Value(name);
        putText(result, "version", std::move(version));
#if TARGET_OS_SIMULATOR
        result["source"] = Value("simulatorDevice");
#else
        putText(result, "build", sysctlText("kern.osversion"));
        putText(result, "kernel", sysctlText("kern.osrelease"));
#endif
#if defined(__arm64__)
        result["architecture"] = Value("arm64");
#elif defined(__x86_64__)
        result["architecture"] = Value("x86_64");
#endif
        result["bits"] = Value(static_cast<unsigned int>(sizeof(void*) * 8));
        result["architectureScope"] = Value("process");
        return result;
    }
}

ValueMap readCpu()
{
    ValueMap result;
#if defined(__arm64__)
    result["vendor"] = Value("Apple");
#else
    putText(result, "vendor", sysctlText("machdep.cpu.vendor"));
#endif
    putText(result, "model", sysctlText("machdep.cpu.brand_string"));
    putCount(result, "physicalCores", "hw.physicalcpu");
    putCount(result, "logicalCores", "hw.logicalcpu");

    auto packageCount = sysctlValue<uint32_t>("hw.packages").value_or(0);
    if (packageCount > 0)
        result["packageCount"] = Value(packageCount);
    if (packageCount == 1)
    {
        ValueMap package{{"id", Value(0u)}};
        for (const auto* field : {"vendor", "model", "physicalCores", "logicalCores"})
        {
            if (auto value = result.find(field); value != result.end())
                package[field] = value->second;
        }
        result["packages"] = Value(ValueVector{Value(std::move(package))});
    }

    auto flags = cpuFlags();
    if (!flags.empty())
        result["flags"] = Value(std::move(flags));
    auto clusters = cpuClusters();
    if (!clusters.empty())
        result["clusters"] = Value(std::move(clusters));
#if TARGET_OS_SIMULATOR
    result["source"] = Value("simulatorHost");
#endif
    return result;
}

ValueMap readMemory()
{
    @autoreleasepool
    {
        ValueMap result;
        const auto total = NSProcessInfo.processInfo.physicalMemory;
        if (total > 0)
            result["total"] = Value(static_cast<uint64_t>(total));

        const auto host = mach_host_self();
        vm_size_t pageSize = 0;
        vm_statistics64_data_t stats{};
        mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
        const auto pageStatus = host_page_size(host, &pageSize);
        const auto statsStatus = host_statistics64(host, HOST_VM_INFO64, reinterpret_cast<host_info64_t>(&stats), &count);
        mach_port_deallocate(mach_task_self(), host);
        if (pageStatus == KERN_SUCCESS && statsStatus == KERN_SUCCESS && pageSize > 0)
        {
            // XNU includes speculative pages in free_count. Inactive pages are potentially reclaimable.
            const auto freePages = stats.free_count - std::min(stats.free_count, stats.speculative_count);
            const auto availablePages = static_cast<uint64_t>(stats.free_count) + stats.inactive_count;
            const auto available = availablePages * static_cast<uint64_t>(pageSize);
            result["free"] = Value(static_cast<uint64_t>(freePages) * static_cast<uint64_t>(pageSize));
            result["available"] = Value(total > 0 ? std::min(static_cast<uint64_t>(total), available) : available);
            result["availableSource"] = Value("machVmEstimate");
        }
        else
        {
            const auto status = pageStatus != KERN_SUCCESS ? pageStatus : statsStatus;
            if (total == 0)
                return failure("platformError", "Mach VM statistics", status, "Mach");
        }
#if TARGET_OS_SIMULATOR
        result["source"] = Value("simulatorHost");
#endif
        return result;
    }
}

ValueMap readUptime()
{
    ValueMap result;
    mach_timebase_info_data_t timebase{};
    const auto status = mach_timebase_info(&timebase);
    if (status == KERN_SUCCESS && timebase.denom != 0)
    {
        const auto elapsed = static_cast<__uint128_t>(mach_continuous_time()) * timebase.numer / timebase.denom;
        result["seconds"] = Value(static_cast<uint64_t>(elapsed / 1'000'000'000));
    }
    if (auto boot = sysctlValue<timeval>("kern.boottime"); boot && boot->tv_sec > 0)
        result["bootTime"] = Value(static_cast<uint64_t>(boot->tv_sec));
    if (result.empty())
        return failure("platformError", "mach_timebase_info / kern.boottime", status, "Mach");
#if TARGET_OS_SIMULATOR
    result["source"] = Value("simulatorHost");
#endif
    return result;
}
}
