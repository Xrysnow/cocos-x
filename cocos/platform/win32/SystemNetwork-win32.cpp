#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <ras.h>
#include <raserror.h>
#include <roapi.h>
#include <winrt/Windows.Networking.Connectivity.h>
#include "platform/SystemInfoInternal.h"
#include <optional>

#pragma comment(lib, "windowsapp.lib")
#pragma comment(lib, "rasapi32.lib")

namespace cc::system_info {
namespace {
using namespace winrt::Windows::Networking::Connectivity;
struct Apartment {
    HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
    ~Apartment() { if (SUCCEEDED(hr)) RoUninitialize(); }
};
struct Route {
    bool readable = false;
    bool exists = false;
    bool ambiguous = false;
    NET_LUID luid{};
};

Route defaultRoute() {
    Route result;
    PMIB_IPFORWARD_TABLE2 table = nullptr;
    if (GetIpForwardTable2(AF_UNSPEC, &table) != NO_ERROR) return result;
    result.readable = true;
    // Metrics are comparable only within each address family.
    struct Best { uint64_t metric = UINT64_MAX; NET_LUID luid{}; bool tied = false; };
    Best v4, v6;
    for (ULONG i = 0; i < table->NumEntries; ++i) {
        const auto& route = table->Table[i];
        if (route.DestinationPrefix.PrefixLength || !route.ValidLifetime || route.Loopback) continue;
        MIB_IPINTERFACE_ROW iface{};
        iface.Family = route.DestinationPrefix.Prefix.si_family;
        iface.InterfaceLuid = route.InterfaceLuid;
        if (GetIpInterfaceEntry(&iface) != NO_ERROR || !iface.Connected) continue;
        auto& best = iface.Family == AF_INET ? v4 : v6;
        const uint64_t metric = uint64_t(route.Metric) + iface.Metric;
        if (metric < best.metric) best = {metric, iface.InterfaceLuid, false};
        else if (metric == best.metric && best.luid.Value != iface.InterfaceLuid.Value) best.tied = true;
    }
    FreeMibTable(table);
    result.luid = v4.luid.Value ? v4.luid : v6.luid;
    result.exists = result.luid.Value != 0;
    result.ambiguous = v4.tied || v6.tied || (v4.luid.Value && v6.luid.Value && v4.luid.Value != v6.luid.Value);
    return result;
}

bool routeIsRasVpn(NET_LUID luid) {
    DWORD bytes = sizeof(RASCONNW), count = 0;
    std::vector<RASCONNW> connections(1);
    DWORD status;
    do {
        connections.resize((bytes + sizeof(RASCONNW) - 1) / sizeof(RASCONNW));
        connections[0].dwSize = sizeof(RASCONNW);
        status = RasEnumConnectionsW(connections.data(), &bytes, &count);
    } while (status == ERROR_BUFFER_TOO_SMALL);
    if (status != ERROR_SUCCESS) return false;
    for (DWORD i = 0; i < count; ++i) {
        if (_wcsicmp(connections[i].szDeviceType, L"vpn") != 0) continue;
        RASPPPIPW projected{};
        projected.dwSize = sizeof(projected);
        DWORD size = sizeof(projected);
        if (RasGetProjectionInfoW(connections[i].hrasconn, RASP_PppIp, &projected, &size) != ERROR_SUCCESS || projected.dwError) continue;
        MIB_UNICASTIPADDRESS_ROW addr{};
        addr.InterfaceLuid = luid;
        addr.Address.Ipv4.sin_family = AF_INET;
        if (InetPtonW(AF_INET, projected.szIpAddress, &addr.Address.Ipv4.sin_addr) == 1 &&
            GetUnicastIpAddressEntry(&addr) == NO_ERROR) return true;
    }
    return false;
}

const char* transport(unsigned type) {
    switch (type) {
    case IF_TYPE_IEEE80211: return "wifi";
    case IF_TYPE_ETHERNET_CSMACD: return "ethernet";
    case IF_TYPE_WWANPP: case IF_TYPE_WWANPP2: return "cellular";
    default: return nullptr;
    }
}
const char* generation(WwanDataClass value) {
    using W = WwanDataClass;
    switch (value) {
    case W::Gprs: case W::Edge: case W::Cdma1xRtt: return "2G";
    case W::Umts: case W::Hsdpa: case W::Hsupa: case W::Cdma1xEvdo:
    case W::Cdma1xEvdoRevA: case W::Cdma1xEvdv: case W::Cdma3xRtt: case W::Cdma1xEvdoRevB: return "3G";
    case W::LteAdvanced: case W::CdmaUmb: return "4G";
    case W::NewRadioNonStandalone: case W::NewRadioStandalone: return "5G";
    default: return nullptr;
    }
}

HANDLE routeNotification{};
winrt::event_token token{};
void CALLBACK onRoute(void*, PMIB_IPFORWARD_ROW2, MIB_NOTIFICATION_TYPE) { networkChanged(); }
}

ValueMap readNetwork() {
    ValueMap out;
    out["source"] = "IP Helper / NetworkInformation";
    const auto route = defaultRoute();
    if (route.exists && !route.ambiguous) {
        MIB_IF_ROW2 row{};
        row.InterfaceLuid = route.luid;
        if (GetIfEntry2(&row) == NO_ERROR) {
            if (const char* type = transport(row.Type)) out["primaryType"] = type;
        }
        if (routeIsRasVpn(route.luid)) out["isVpn"] = true;
    }

    Apartment apartment;
    if (SUCCEEDED(apartment.hr) || apartment.hr == RPC_E_CHANGED_MODE) {
        try {
            auto profile = NetworkInformation::GetInternetConnectionProfile();
            if (profile) {
                auto adapter = profile.NetworkAdapter();
                NET_LUID luid{};
                bool matches = false;
                if (adapter) {
                    GUID guid = adapter.NetworkAdapterId();
                    matches = !route.ambiguous && ConvertInterfaceGuidToLuid(&guid, &luid) == NO_ERROR &&
                        (!route.exists || route.luid.Value == luid.Value);
                }
                if (matches) {
                    if (profile.IsWwanConnectionProfile()) out["primaryType"] = "cellular";
                    else if (profile.IsWlanConnectionProfile()) out["primaryType"] = "wifi";
                    else if (const char* type = transport(adapter.IanaInterfaceType())) out["primaryType"] = type;
                    auto cost = profile.GetConnectionCost().NetworkCostType();
                    if (cost == NetworkCostType::Unrestricted) out["isMetered"] = false;
                    if (cost == NetworkCostType::Fixed || cost == NetworkCostType::Variable) out["isMetered"] = true;
                    if (auto wwan = profile.WwanConnectionProfileDetails()) {
                        if (auto g = generation(wwan.GetCurrentDataClass())) out["cellularGeneration"] = g;
                    }
                }
            } else if (route.readable && !route.exists) {
                out["primaryType"] = "none";
                for (auto k : {"isVpn", "isMetered", "costHint"}) missing(out, k, "notApplicable");
            }
        } catch (const winrt::hresult_error& e) {
            if (e.code() == E_ACCESSDENIED && !out.contains("isMetered")) missing(out, "isMetered", "permissionDenied");
        }
    }
    if (out.contains("primaryType") && out.at("primaryType").asStringRef() != "cellular")
        missing(out, "cellularGeneration", "notApplicable");
    const auto current = defaultRoute();
    if (route.luid.Value != current.luid.Value || route.ambiguous != current.ambiguous ||
        route.readable != current.readable) return failure("pending", "default route changed");
    return out;
}

void startNetworkEvents() {
    NotifyRouteChange2(AF_UNSPEC, onRoute, nullptr, FALSE, &routeNotification);
    Apartment apartment;
    try {
        token = NetworkInformation::NetworkStatusChanged([](auto const&) { networkChanged(); });
    } catch (const winrt::hresult_error&) {}
}
void stopNetworkEvents() {
    if (routeNotification) CancelMibChangeNotify2(routeNotification);
    routeNotification = nullptr;
    Apartment apartment;
    if (token.value) NetworkInformation::NetworkStatusChanged(token);
    token = {};
}
} // namespace cc::system_info
