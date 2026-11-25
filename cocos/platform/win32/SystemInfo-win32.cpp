#include "platform/SystemInfoInternal.h"
#include <windows.h>
#include <winternl.h>
#include <wbemidl.h>
#include <powrprof.h>
#include <wrl/client.h>
#include <algorithm>
#include <ctime>
#include <vector>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "powrprof.lib")

namespace cc::system_info {
namespace {
std::string utf8(const wchar_t* value, int length) {
    if (!value || !length) return {};
    int size = WideCharToMultiByte(CP_UTF8, 0, value, length, nullptr, 0, nullptr, nullptr);
    std::string result(size, '\0');
    if (size) WideCharToMultiByte(CP_UTF8, 0, value, length, result.data(), size, nullptr, nullptr);
    return result;
}

void registryString(ValueMap& out, const char* field, const wchar_t* path, const wchar_t* name) {
    wchar_t data[512]{};
    DWORD bytes = sizeof(data);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, path, name, RRF_RT_REG_SZ, nullptr, data, &bytes) == ERROR_SUCCESS && data[0])
        out[field] = utf8(data, static_cast<int>(wcslen(data)));
}

void readIdentifiers(ValueMap& out) {
    using Microsoft::WRL::ComPtr;
    auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) return;
    struct Apartment { bool owns; ~Apartment() { if (owns) CoUninitialize(); } } apartment{SUCCEEDED(hr)};
    ComPtr<IWbemLocator> locator;
    ComPtr<IWbemServices> services;
    ComPtr<IEnumWbemClassObject> rows;
    if (FAILED(CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&locator)))) return;
    BSTR ns = SysAllocString(L"ROOT\\CIMV2");
    hr = locator->ConnectServer(ns, nullptr, nullptr, nullptr, 0, nullptr, nullptr, &services);
    SysFreeString(ns);
    if (SUCCEEDED(hr)) hr = CoSetProxyBlanket(services.Get(), RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                                             RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
    if (SUCCEEDED(hr)) {
        BSTR language = SysAllocString(L"WQL");
        BSTR query = SysAllocString(L"SELECT UUID,IdentifyingNumber FROM Win32_ComputerSystemProduct");
        hr = services->ExecQuery(language, query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &rows);
        SysFreeString(query);
        SysFreeString(language);
    }
    ComPtr<IWbemClassObject> row;
    ULONG count = 0;
    if (SUCCEEDED(hr)) hr = rows->Next(1500, 1, &row, &count);
    if (FAILED(hr) || !count) {
        if (hr == E_ACCESSDENIED || hr == WBEM_E_ACCESS_DENIED) {
            missing(out, "uuid", "permissionDenied");
            missing(out, "serialNumber", "permissionDenied");
        }
        return;
    }
    for (auto [key, property] : {std::pair{"uuid", L"UUID"}, {"serialNumber", L"IdentifyingNumber"}}) {
        VARIANT value{};
        if (SUCCEEDED(row->Get(property, 0, &value, nullptr, nullptr)) && value.vt == VT_BSTR) {
            auto s = utf8(value.bstrVal, SysStringLen(value.bstrVal));
            if (!s.empty() && s != "00000000-0000-0000-0000-000000000000" && s != "FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF"
                && s != "Default string" && s != "To be filled by O.E.M.") out[key] = std::move(s);
        }
        VariantClear(&value);
    }
}

using Topology = SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;
ValueVector logicalIds(const PROCESSOR_RELATIONSHIP& group) {
    ValueVector ids;
    for (WORD i = 0; i < group.GroupCount; ++i) {
        const auto mask = group.GroupMask[i];
        for (unsigned bit = 0; bit < sizeof(mask.Mask) * 8; ++bit)
            if (mask.Mask & (KAFFINITY{1} << bit)) ids.emplace_back(mask.Group * 64u + bit);
    }
    return ids;
}

void topology(ValueMap& cpu) {
    DWORD size = 0;
    std::vector<BYTE> buffer;
    while (!GetLogicalProcessorInformationEx(RelationAll, reinterpret_cast<Topology*>(buffer.data()), &size)) {
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || size <= buffer.size()) return;
        buffer.resize(size);
    }
    ValueVector packages, cores;
    std::vector<const CACHE_RELATIONSHIP*> caches;
    unsigned count = 0;
    for (size_t offset = 0; offset < size;) {
        const auto* item = reinterpret_cast<const Topology*>(buffer.data() + offset);
        if (!item->Size || item->Size > size - offset) return;
        if (item->Relationship == RelationCache) caches.push_back(&item->Cache);
        if (item->Relationship == RelationProcessorCore || item->Relationship == RelationProcessorPackage) {
            auto ids = logicalIds(item->Processor);
            ValueMap row;
            row["threads"] = static_cast<unsigned>(ids.size());
            row["logicalCpus"] = std::move(ids);
            if (item->Relationship == RelationProcessorCore) {
                row["id"] = static_cast<unsigned>(cores.size());
                row["efficiencyClass"] = static_cast<unsigned>(item->Processor.EfficiencyClass);
                count += row["threads"].asUint();
                cores.emplace_back(std::move(row));
            } else {
                row["id"] = static_cast<unsigned>(packages.size());
                packages.emplace_back(std::move(row));
            }
        }
        offset += item->Size;
    }
    struct ProcessorPower { ULONG number, maxMhz, currentMhz, limitMhz, maxIdle, currentIdle; };
    std::vector<ProcessorPower> frequencies(count);
    const bool haveFrequencies = GetActiveProcessorGroupCount() == 1 && count &&
        CallNtPowerInformation(ProcessorInformation, nullptr, 0, frequencies.data(),
            static_cast<ULONG>(frequencies.size() * sizeof(ProcessorPower))) == 0;
    for (auto& core : cores) {
        auto& row = core.asValueMap();
        const auto& ids = row.at("logicalCpus").asValueVector();
        if (ids.empty()) continue;
        const unsigned id = ids.front().asUint();
        if (haveFrequencies && id < frequencies.size() && frequencies[id].number == id && frequencies[id].maxMhz)
            row["maxFrequency"] = uint64_t(frequencies[id].maxMhz) * 1000000;
        for (const auto& p : packages) {
            const auto& members = p.asValueMap().at("logicalCpus").asValueVector();
            if (std::find(members.begin(), members.end(), ids.front()) != members.end())
                row["packageId"] = p.asValueMap().at("id");
        }
        for (const auto cache : caches) {
            if (cache->GroupMask.Group != id / 64 || id % 64 >= sizeof(KAFFINITY) * 8 ||
                !(cache->GroupMask.Mask & (KAFFINITY{1} << (id % 64)))) continue;
            const char* key = cache->Level == 3 ? "l3" : cache->Level == 2 ? "l2" :
                cache->Level == 1 && cache->Type == CacheData ? "l1Data" :
                cache->Level == 1 && cache->Type == CacheInstruction ? "l1Instruction" : nullptr;
            if (key) row[key] = static_cast<uint64_t>(cache->CacheSize);
        }
    }
    for (auto& package : packages) {
        auto& row = package.asValueMap();
        row["logicalCores"] = row.at("threads");
        unsigned physical = 0;
        for (const auto& core : cores) {
            const auto& info = core.asValueMap();
            if (info.contains("packageId") && info.at("packageId") == row.at("id")) ++physical;
        }
        row["physicalCores"] = physical;
        if (packages.size() == 1)
            for (auto key : {"vendor", "model", "flags"})
                if (cpu.contains(key)) row[key] = cpu.at(key);
    }
    cpu["logicalCores"] = count;
    cpu["physicalCores"] = static_cast<unsigned>(cores.size());
    cpu["cores"] = std::move(cores);
    cpu["packages"] = std::move(packages);
}
}

ValueMap readComputer(bool identifiers) {
    ValueMap out;
    const auto path = L"HARDWARE\\DESCRIPTION\\System\\BIOS";
    for (auto [key, name] : {std::pair{"vendor", L"SystemManufacturer"}, {"model", L"SystemProductName"},
                              {"version", L"SystemVersion"}, {"sku", L"SystemSKU"}, {"family", L"SystemFamily"}})
        registryString(out, key, path, name);
    if (identifiers) readIdentifiers(out);
    switch (PowerDeterminePlatformRoleEx(POWER_PLATFORM_ROLE_V2)) {
    case PlatformRoleDesktop: case PlatformRoleWorkstation: out["chassis"] = "desktop"; break;
    case PlatformRoleMobile: out["chassis"] = "laptop"; break;
    case PlatformRoleSlate: out["chassis"] = "tablet"; break;
    case PlatformRoleEnterpriseServer: case PlatformRoleSOHOServer: case PlatformRolePerformanceServer:
        out["chassis"] = "server"; break;
    default: break;
    }
    out["source"] = "Windows registry / platform role";
    return out;
}

ValueMap readOs() {
    ValueMap out;
    out["family"] = "Windows";
    out["name"] = "Windows";
    out["source"] = "RtlGetVersion / GetNativeSystemInfo";
    out["architectureScope"] = "system";
    RTL_OSVERSIONINFOEXW info{};
    info.dwOSVersionInfoSize = sizeof(info);
    using VersionFn = LONG (WINAPI*)(PRTL_OSVERSIONINFOW);
    auto version = reinterpret_cast<VersionFn>(GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion"));
    if (version && version(reinterpret_cast<PRTL_OSVERSIONINFOW>(&info)) == 0) {
        auto v = std::to_string(info.dwMajorVersion) + "." + std::to_string(info.dwMinorVersion) + "." + std::to_string(info.dwBuildNumber);
        out["version"] = v;
        out["kernel"] = "Windows NT " + v;
        out["build"] = std::to_string(info.dwBuildNumber);
        if (info.wProductType == VER_NT_WORKSTATION && info.dwMajorVersion == 10)
            out["marketingName"] = info.dwBuildNumber >= 22000 ? "Windows 11" : "Windows 10";
        else registryString(out, "marketingName", L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName");
    }
    SYSTEM_INFO sys{};
    GetNativeSystemInfo(&sys);
    switch (sys.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64: out["architecture"] = "x86_64"; out["bits"] = 64; break;
    case PROCESSOR_ARCHITECTURE_ARM64: out["architecture"] = "arm64"; out["bits"] = 64; break;
    case PROCESSOR_ARCHITECTURE_INTEL: out["architecture"] = "x86"; out["bits"] = 32; break;
    case PROCESSOR_ARCHITECTURE_ARM: out["architecture"] = "arm"; out["bits"] = 32; break;
    }
    return out;
}

ValueMap readCpu() {
    ValueMap out;
    auto path = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
    registryString(out, "model", path, L"ProcessorNameString");
    registryString(out, "vendor", path, L"VendorIdentifier");
    ValueVector flags;
    for (auto [feature, name] : {std::pair{PF_XMMI64_INSTRUCTIONS_AVAILABLE, "sse2"},
                                  {PF_SSE3_INSTRUCTIONS_AVAILABLE, "sse3"}, {PF_ARM_NEON_INSTRUCTIONS_AVAILABLE, "neon"},
                                  {PF_AVX_INSTRUCTIONS_AVAILABLE, "avx"}, {PF_AVX2_INSTRUCTIONS_AVAILABLE, "avx2"}})
        if (IsProcessorFeaturePresent(feature)) flags.emplace_back(name);
    out["flags"] = std::move(flags);
    topology(out);
    out["source"] = "GetLogicalProcessorInformationEx / IsProcessorFeaturePresent / registry";
    return out;
}

ValueMap readMemory() {
    MEMORYSTATUSEX memory{};
    memory.dwLength = sizeof(memory);
    if (!GlobalMemoryStatusEx(&memory)) return failure("platformError", "GlobalMemoryStatusEx", GetLastError());
    ValueMap out;
    out["total"] = static_cast<uint64_t>(memory.ullTotalPhys);
    out["available"] = static_cast<uint64_t>(memory.ullAvailPhys);
    missing(out, "free", "unsupported");
    return out;
}

ValueMap readUptime() {
    ValueMap out;
    auto seconds = static_cast<uint64_t>(GetTickCount64() / 1000);
    out["seconds"] = seconds;
    out["bootTime"] = static_cast<int64_t>(std::time(nullptr)) - static_cast<int64_t>(seconds);
    out["source"] = "GetTickCount64 / estimated boot time";
    return out;
}
} // namespace cc::system_info
