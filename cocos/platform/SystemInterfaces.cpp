#include "platform/SystemInfoInternal.h"

#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#else
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#if defined(__APPLE__)
#include <TargetConditionals.h>
#include <net/if_dl.h>
#else
#include <netpacket/packet.h>
#endif
#endif

namespace cc {
namespace {
std::string mac(const unsigned char* bytes, size_t count) {
    std::string result;
    if (!count || std::all_of(bytes, bytes + count, [](auto b) { return b == 0; })) return result;
    for (size_t i = 0; i < count; ++i) {
        char octet[4];
        std::snprintf(octet, sizeof(octet), "%02x", bytes[i]);
        if (i) result.push_back(':');
        result += octet;
    }
    return result;
}

void addAddress(ValueMap& row, const sockaddr* address) {
    if (!address) return;
    const int family = address->sa_family;
    const void* bytes;
    unsigned scope = 0;
    if (family == AF_INET) bytes = &reinterpret_cast<const sockaddr_in*>(address)->sin_addr;
    else if (family == AF_INET6) {
        const auto* v6 = reinterpret_cast<const sockaddr_in6*>(address);
        bytes = &v6->sin6_addr;
        scope = v6->sin6_scope_id;
    } else return;
    char host[INET6_ADDRSTRLEN];
    if (!inet_ntop(family, bytes, host, sizeof(host))) return;
    std::string value(host);
    if (scope) value += "%" + std::to_string(scope);
    auto& addresses = row[family == AF_INET ? "ipv4" : "ipv6"].asValueVector();
    addresses.emplace_back(std::move(value));
}

void initAddresses(ValueMap& row, bool addresses) {
    if (addresses) {
        row["ipv4"] = ValueVector{};
        row["ipv6"] = ValueVector{};
    } else {
        for (auto key : {"ipv4", "ipv6", "mac"}) system_info::missing(row, key, "withheld");
    }
}
#if defined(_WIN32)
std::string utf8(const wchar_t* s) {
    if (!s || !*s) return {};
    const auto n = static_cast<int>(wcslen(s));
    const int size = WideCharToMultiByte(CP_UTF8, 0, s, n, nullptr, 0, nullptr, nullptr);
    std::string result(size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s, n, result.data(), size, nullptr, nullptr);
    return result;
}
#endif
}

ValueMap SystemInfo::getNetworkInterfaces(bool addresses) {
    ValueVector interfaces;
#if defined(_WIN32)
    ULONG size = 16384;
    std::vector<unsigned char> buffer;
    ULONG status;
    do {
        buffer.resize(size);
        status = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_ALL_INTERFACES | GAA_FLAG_SKIP_MULTICAST |
            GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_SERVER | (addresses ? 0 : GAA_FLAG_SKIP_UNICAST),
            nullptr, reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buffer.data()), &size);
    } while (status == ERROR_BUFFER_OVERFLOW);
    if (status != NO_ERROR && status != ERROR_NO_DATA)
        return system_info::failure("platformError", "GetAdaptersAddresses", status);
    for (auto* p = status == ERROR_NO_DATA ? nullptr : reinterpret_cast<IP_ADAPTER_ADDRESSES*>(buffer.data()); p; p = p->Next) {
        ValueMap row;
        row["index"] = static_cast<unsigned>(p->IfIndex ? p->IfIndex : p->Ipv6IfIndex);
        row["name"] = utf8(p->FriendlyName);
        row["description"] = utf8(p->Description);
        row["up"] = p->OperStatus == IfOperStatusUp;
        row["loopback"] = p->IfType == IF_TYPE_SOFTWARE_LOOPBACK;
        initAddresses(row, addresses);
        if (addresses) {
            auto physical = mac(p->PhysicalAddress, p->PhysicalAddressLength);
            if (!physical.empty()) row["mac"] = std::move(physical);
            for (auto* a = p->FirstUnicastAddress; a; a = a->Next) addAddress(row, a->Address.lpSockaddr);
        }
        interfaces.emplace_back(system_info::finish(std::move(row), {"mac"}));
    }
#else
    ifaddrs* first = nullptr;
    if (getifaddrs(&first) != 0)
        return system_info::failure(errno == EACCES ? "permissionDenied" : "platformError", "getifaddrs", errno);
    struct Guard { ifaddrs* list; ~Guard() { freeifaddrs(list); } } guard{first};
    std::map<std::string, ValueMap> rows;
    for (auto* p = first; p; p = p->ifa_next) {
        if (!p->ifa_name) continue;
        auto [it, fresh] = rows.try_emplace(p->ifa_name);
        auto& row = it->second;
        if (fresh) {
            row["name"] = it->first;
            if (auto index = if_nametoindex(p->ifa_name)) row["index"] = index;
            row["up"] = bool(p->ifa_flags & IFF_UP);
            row["loopback"] = bool(p->ifa_flags & IFF_LOOPBACK);
            initAddresses(row, addresses);
        }
        if (!addresses || !p->ifa_addr) continue;
        addAddress(row, p->ifa_addr);
        std::string physical;
#if defined(__APPLE__)
        if (p->ifa_addr->sa_family == AF_LINK) {
            auto* link = reinterpret_cast<const sockaddr_dl*>(p->ifa_addr);
            physical = mac(reinterpret_cast<const unsigned char*>(LLADDR(link)), link->sdl_alen);
        }
#else
        if (p->ifa_addr->sa_family == AF_PACKET) {
            auto* link = reinterpret_cast<const sockaddr_ll*>(p->ifa_addr);
            physical = mac(link->sll_addr, std::min<size_t>(link->sll_halen, sizeof(link->sll_addr)));
        }
#endif
        if (!physical.empty()) row["mac"] = std::move(physical);
    }
    for (auto& [name, row] : rows)
        interfaces.emplace_back(system_info::finish(std::move(row), {"index", "description", "mac"}));
#endif
    ValueMap result;
    result["interfaces"] = std::move(interfaces);
#if defined(__APPLE__) && TARGET_OS_SIMULATOR
    result["source"] = "simulatorHost";
#endif
    return system_info::finish(std::move(result), {});
}
} // namespace cc
