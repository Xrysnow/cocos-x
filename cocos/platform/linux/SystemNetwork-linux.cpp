#include "platform/SystemInfoInternal.h"
#include "platform/linux/SystemInfo-linux-bus.h"
#include "platform/linux/SystemInfo-linux-private.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <mutex>
#include <thread>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cc::system_info
{
namespace
{
using namespace linux_detail;

class FileDescriptor
{
public:
    explicit FileDescriptor(int fd = -1) : _fd(fd) {}
    ~FileDescriptor()
    {
        if (_fd >= 0)
            close(_fd);
    }
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;
    int get() const { return _fd; }

private:
    int _fd;
};

struct Route
{
    int interface = 0;
    int error = 0;
    unsigned int prefix = 0;
    bool ambiguous = false;
    bool operator==(const Route&) const = default;
};

template <typename Body>
struct NetlinkRequest
{
    nlmsghdr header{};
    Body body{};
    alignas(rtattr) std::array<unsigned char, 64> attributes{};

    NetlinkRequest(uint16_t type)
    {
        header.nlmsg_len = NLMSG_LENGTH(sizeof(Body));
        header.nlmsg_type = type;
        header.nlmsg_flags = NLM_F_REQUEST;
    }

    void add(uint16_t type, const void* value, size_t size)
    {
        auto offset = NLMSG_ALIGN(header.nlmsg_len) - NLMSG_ALIGN(NLMSG_LENGTH(sizeof(Body)));
        auto attribute = reinterpret_cast<rtattr*>(attributes.data() + offset);
        attribute->rta_type = type;
        attribute->rta_len = RTA_LENGTH(size);
        std::memcpy(RTA_DATA(attribute), value, size);
        header.nlmsg_len = NLMSG_ALIGN(header.nlmsg_len) + RTA_LENGTH(size);
    }
};

class RouteSocket
{
    FileDescriptor _socket{socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE)};
    uint32_t _sequence = 0;
    int _error = 0;
    alignas(nlmsghdr) std::array<char, 16 * 1024> _buffer{};

public:
    RouteSocket()
    {
        const timeval timeout{0, 150'000};
        sockaddr_nl address{};
        address.nl_family = AF_NETLINK;
        if (_socket.get() < 0 || bind(_socket.get(), reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0 ||
            setsockopt(_socket.get(), SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
            _error = errno;
    }

    template <typename Body>
    const nlmsghdr* query(NetlinkRequest<Body>& request, uint16_t replyType, int& error)
    {
        error = _error;
        if (error)
            return nullptr;
        request.header.nlmsg_seq = ++_sequence;
        sockaddr_nl peer{};
        peer.nl_family = AF_NETLINK;
        if (sendto(_socket.get(), &request, request.header.nlmsg_len, 0,
                   reinterpret_cast<sockaddr*>(&peer), sizeof(peer)) < 0)
        {
            error = errno;
            return nullptr;
        }
        for (;;)
        {
            socklen_t addressLength = sizeof(peer);
            auto bytes = recvfrom(_socket.get(), _buffer.data(), _buffer.size(), MSG_TRUNC,
                                  reinterpret_cast<sockaddr*>(&peer), &addressLength);
            if (bytes < 0)
            {
                if (errno == EINTR)
                    continue;
                error = errno;
                return nullptr;
            }
            if (bytes == 0 || static_cast<size_t>(bytes) > _buffer.size())
            {
                error = EMSGSIZE;
                return nullptr;
            }
            if (peer.nl_pid != 0)
                continue;
            int remaining = static_cast<int>(bytes);
            for (auto message = reinterpret_cast<nlmsghdr*>(_buffer.data()); NLMSG_OK(message, remaining);
                 message = NLMSG_NEXT(message, remaining))
            {
                if (message->nlmsg_seq != _sequence)
                    continue;
                if (message->nlmsg_type == NLMSG_ERROR && NLMSG_PAYLOAD(message, 0) >= sizeof(nlmsgerr))
                    error = -static_cast<const nlmsgerr*>(NLMSG_DATA(message))->error;
                else if (message->nlmsg_type == replyType)
                    return message;
                else
                    error = EPROTO;
                return nullptr;
            }
        }
    }
};

std::string_view attrText(const rtattr* attribute)
{
    auto data = static_cast<const char*>(RTA_DATA(attribute));
    return {data, strnlen(data, RTA_PAYLOAD(attribute))};
}

int attributeInt(const rtattr* attribute)
{
    int value = 0;
    if (RTA_PAYLOAD(attribute) == sizeof(value))
        std::memcpy(&value, RTA_DATA(attribute), sizeof(value));
    return value;
}

Route lookup(RouteSocket& socket, int family, const char* destination)
{
    NetlinkRequest<rtmsg> request(RTM_GETROUTE);
    request.body.rtm_family = family;
    const size_t length = family == AF_INET ? sizeof(in_addr) : sizeof(in6_addr);
    request.body.rtm_dst_len = length * 8;
    request.body.rtm_flags = RTM_F_FIB_MATCH;
    std::array<unsigned char, sizeof(in6_addr)> address{};
    if (inet_pton(family, destination, address.data()) != 1)
        return {.error = EINVAL};
    request.add(RTA_DST, address.data(), length);
    uint32_t uid = geteuid();
    request.add(RTA_UID, &uid, sizeof(uid));

    Route result;
    auto reply = socket.query(request, RTM_NEWROUTE, result.error);
    if (!reply)
    {
        if (result.error == ESRCH || result.error == ENETUNREACH || result.error == EHOSTUNREACH ||
            result.error == EAFNOSUPPORT)
            result.error = 0;
        return result;
    }
    if (NLMSG_PAYLOAD(reply, 0) < sizeof(rtmsg))
        return {.error = EPROTO};
    auto route = static_cast<const rtmsg*>(NLMSG_DATA(reply));
    if (route->rtm_type != RTN_UNICAST)
        return {.ambiguous = true};
    result.prefix = route->rtm_dst_len;
    int bytes = RTM_PAYLOAD(reply);
    for (auto attr = RTM_RTA(route); RTA_OK(attr, bytes); attr = RTA_NEXT(attr, bytes))
    {
        if (attr->rta_type == RTA_OIF)
            result.interface = attributeInt(attr);
        if (attr->rta_type == RTA_NH_ID)
            result.ambiguous = true;
        if (attr->rta_type != RTA_MULTIPATH)
            continue;
        int size = RTA_PAYLOAD(attr);
        for (auto hop = static_cast<const rtnexthop*>(RTA_DATA(attr)); RTNH_OK(hop, size); hop = RTNH_NEXT(hop))
        {
            size -= RTNH_ALIGN(hop->rtnh_len);
            if (hop->rtnh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN))
                continue;
            if (result.interface && result.interface != hop->rtnh_ifindex)
                result.ambiguous = true;
            result.interface = hop->rtnh_ifindex;
        }
    }
    result.ambiguous |= result.interface == 0;
    return result;
}

Route defaultRoute(RouteSocket& socket, int family)
{
    // Netlink resolves the running process's routing policy without sending packets.
    // Look in separate broad prefixes to detect policy conflicts and split defaults.
    auto first = lookup(socket, family, family == AF_INET ? "9.9.9.9" : "2606:4700::1111");
    auto second = lookup(socket, family, family == AF_INET ? "208.67.222.222" : "2a00:1450::1");
    if (first.error || second.error)
        return {.error = first.error ? first.error : second.error};
    if (first.ambiguous || second.ambiguous || first.interface != second.interface)
        return {.ambiguous = true};
    const unsigned int broadPrefix = family == AF_INET ? 1 : 3;
    if (first.interface && (first.prefix > broadPrefix || second.prefix > broadPrefix))
        return {.ambiguous = true};
    return first;
}

struct Link
{
    std::string name;
    std::string kind;
    std::string_view transport;
    bool possibleTunnel = false;
};

Link readLink(RouteSocket& socket, int interface)
{
    NetlinkRequest<ifinfomsg> request(RTM_GETLINK);
    request.body.ifi_index = interface;
    int error = 0;
    auto reply = socket.query(request, RTM_NEWLINK, error);
    if (!reply || NLMSG_PAYLOAD(reply, 0) < sizeof(ifinfomsg))
        return {};
    Link link;
    auto info = static_cast<const ifinfomsg*>(NLMSG_DATA(reply));
    int bytes = IFLA_PAYLOAD(reply);
    for (auto attr = IFLA_RTA(info); RTA_OK(attr, bytes); attr = RTA_NEXT(attr, bytes))
    {
        if (attr->rta_type == IFLA_IFNAME)
            link.name = attrText(attr);
        if (attr->rta_type != IFLA_LINKINFO)
            continue;
        int nestedBytes = RTA_PAYLOAD(attr);
        for (auto nested = static_cast<const rtattr*>(RTA_DATA(attr)); RTA_OK(nested, nestedBytes);
             nested = RTA_NEXT(nested, nestedBytes))
            if (nested->rta_type == IFLA_INFO_KIND)
                link.kind = attrText(nested);
    }
    if (link.name.empty())
        return link;
    auto path = std::filesystem::path("/sys/class/net") / link.name;
    auto uevent = readText(path / "uevent");
    auto properties = uevent ? words(*uevent, "\n") : std::vector<std::string_view>{};
    auto hasType = [&properties](std::string_view kind) {
        return std::find(properties.begin(), properties.end(), kind) != properties.end();
    };
    std::error_code ignored;
    if (hasType("DEVTYPE=wlan") || std::filesystem::exists(path / "phy80211", ignored) ||
        std::filesystem::exists(path / "wireless", ignored))
        link.transport = "wifi";
    else if (hasType("DEVTYPE=wwan") || link.kind == "wwan" || link.kind == "rmnet")
        link.transport = "cellular";
    else if (hasType("DEVTYPE=bluetooth") || info->ifi_type == ARPHRD_IEEE802154)
        link.transport = hasType("DEVTYPE=bluetooth") ? "bluetooth" : "other";
    else
    {
        constexpr std::array tunnelKinds{"wireguard", "tun", "xfrm", "vti", "vti6", "gre", "gretap", "ip6gre",
                                         "ip6gretap", "ipip", "sit", "ip6tnl", "ovpn", "ovpn-dco", "amneziawg"};
        link.possibleTunnel = std::find(tunnelKinds.begin(), tunnelKinds.end(), link.kind) != tunnelKinds.end() ||
                              info->ifi_type == ARPHRD_NONE || info->ifi_type == ARPHRD_PPP;
        if (!link.possibleTunnel)
        {
            // Ethernet-framed bridges and bonds can hide a different physical transport.
            if (info->ifi_type == ARPHRD_ETHER && (link.kind.empty() || link.kind == "veth"))
                link.transport = "ethernet";
            else
                link.transport = "other";
        }
    }
    return link;
}

constexpr auto managerName = "org.freedesktop.NetworkManager";
constexpr auto managerPath = "/org/freedesktop/NetworkManager";
constexpr auto deviceInterface = "org.freedesktop.NetworkManager.Device";
constexpr auto activeInterface = "org.freedesktop.NetworkManager.Connection.Active";
constexpr auto modemName = "org.freedesktop.ModemManager1";
constexpr auto modemPath = "/org/freedesktop/ModemManager1";
constexpr auto modemInterface = "org.freedesktop.ModemManager1.Modem";
constexpr auto bearerInterface = "org.freedesktop.ModemManager1.Bearer";

struct Device
{
    std::string path;
    std::string active;
    std::string_view transport;
    unsigned int metered = 0;
};

Device managedDevice(const SystemBus& bus, const char* owner, const std::string& name)
{
    auto reply = bus.call(owner, managerPath, managerName, "GetDeviceByIpIface", "s", name.c_str());
    const char* path = nullptr;
    if (!SystemBus::read(reply, "o", &path) ||
        bus.scalar<unsigned int>(owner, path, deviceInterface, "State", "u") != 100)
        return {};
    auto ipInterface = bus.text(owner, path, deviceInterface, "IpInterface");
    auto active = bus.text(owner, path, deviceInterface, "ActiveConnection", "o");
    if (ipInterface != name || !active || *active == "/" ||
        bus.scalar<unsigned int>(owner, active->c_str(), activeInterface, "State", "u") != 2)
        return {};
    Device result{path, std::move(*active), {},
                  bus.scalar<unsigned int>(owner, path, deviceInterface, "Metered", "u").value_or(0)};
    switch (bus.scalar<unsigned int>(owner, path, deviceInterface, "DeviceType", "u").value_or(0))
    {
    case 1: result.transport = "ethernet"; break;
    case 2: result.transport = "wifi"; break;
    case 5: result.transport = "bluetooth"; break;
    case 8: result.transport = "cellular"; break;
    }
    if (bus.text(owner, path, deviceInterface, "ActiveConnection", "o") != result.active)
        return {};
    return result;
}

bool matchesLocalAddress(const SystemBus& bus, const char* owner, const char* active, const Link& link, int family)
{
    auto path = bus.text(owner, active, activeInterface, family == AF_INET ? "Ip4Config" : "Ip6Config", "o");
    if (!path || *path == "/")
        return false;
    auto message = bus.property(owner, path->c_str(),
        family == AF_INET ? "org.freedesktop.NetworkManager.IP4Config" : "org.freedesktop.NetworkManager.IP6Config",
        "AddressData", "aa{sv}");
    if (!SystemBus::enter(message, 'a', "a{sv}"))
        return false;
    ifaddrs* addresses = nullptr;
    if (getifaddrs(&addresses) != 0)
        return false;
    std::unique_ptr<ifaddrs, decltype(&freeifaddrs)> local(addresses, freeifaddrs);
    while (SystemBus::enter(message, 'a', "{sv}"))
    {
        while (SystemBus::enter(message, 'e', "sv"))
        {
            const char* key = nullptr;
            if (!SystemBus::read(message, "s", &key))
                return false;
            if (std::string_view(key) == "address" && SystemBus::enter(message, 'v', "s"))
            {
                const char* configured = nullptr;
                if (!SystemBus::read(message, "s", &configured) || !SystemBus::exit(message))
                    return false;
                std::array<unsigned char, sizeof(in6_addr)> bytes{};
                if (inet_pton(family, configured, bytes.data()) == 1)
                {
                    for (auto address = addresses; address; address = address->ifa_next)
                    {
                        auto value = address->ifa_addr;
                        if (!value || value->sa_family != family || address->ifa_name != link.name)
                            continue;
                        if (family == AF_INET &&
                            std::memcmp(bytes.data(), &reinterpret_cast<sockaddr_in*>(value)->sin_addr,
                                        sizeof(in_addr)) == 0)
                            return true;
                        if (family == AF_INET6 &&
                            std::memcmp(bytes.data(), &reinterpret_cast<sockaddr_in6*>(value)->sin6_addr,
                                        sizeof(in6_addr)) == 0)
                            return true;
                    }
                }
            }
            else if (!SystemBus::skip(message, "v"))
                return false;
            if (!SystemBus::exit(message))
                return false;
        }
        if (!SystemBus::exit(message))
            return false;
    }
    return false;
}

std::optional<std::string> defaultVpn(const SystemBus& bus, const char* owner, const Link& link, bool ipv4, bool ipv6)
{
    auto active = bus.paths(owner, managerPath, managerName, "ActiveConnections");
    if (!active)
        return std::nullopt;
    std::optional<std::string> result;
    for (const auto& path : *active)
    {
        if (bus.scalar<int>(owner, path.c_str(), activeInterface, "Vpn", "b") != 1 ||
            bus.scalar<unsigned int>(owner, path.c_str(), activeInterface, "State", "u") != 2)
            continue;
        if (ipv4 && (bus.scalar<int>(owner, path.c_str(), activeInterface, "Default", "b") != 1 ||
                     !matchesLocalAddress(bus, owner, path.c_str(), link, AF_INET)))
            continue;
        if (ipv6 && (bus.scalar<int>(owner, path.c_str(), activeInterface, "Default6", "b") != 1 ||
                     !matchesLocalAddress(bus, owner, path.c_str(), link, AF_INET6)))
            continue;
        if (result)
            return std::nullopt;
        result = path;
    }
    return result;
}

Device vpnUnderlay(const SystemBus& bus, const char* owner)
{
    auto primary = bus.text(owner, managerPath, managerName, "PrimaryConnection", "o");
    if (!primary || *primary == "/" ||
        bus.scalar<int>(owner, primary->c_str(), activeInterface, "Vpn", "b") != 0)
        return {};
    auto devices = bus.paths(owner, primary->c_str(), activeInterface, "Devices");
    if (!devices || devices->size() != 1)
        return {};
    auto name = bus.text(owner, devices->front().c_str(), deviceInterface, "IpInterface");
    if (!name || name->empty())
        return {};
    auto device = managedDevice(bus, owner, *name);
    if (device.active != *primary)
        return {};
    return device;
}

const char* cellularGeneration(const SystemBus& bus, const std::string& interface)
{
    auto owner = bus.owner(modemName);
    if (!owner)
        return nullptr;
    auto objects = bus.call(owner->c_str(), modemPath, "org.freedesktop.DBus.ObjectManager", "GetManagedObjects", "");
    if (!SystemBus::enter(objects, 'a', "{oa{sa{sv}}}"))
        return nullptr;
    std::optional<unsigned int> access;
    while (SystemBus::enter(objects, 'e', "oa{sa{sv}}"))
    {
        const char* path = nullptr;
        if (!SystemBus::read(objects, "o", &path) || !SystemBus::skip(objects, "a{sa{sv}}") ||
            !SystemBus::exit(objects))
            return nullptr;
        if (!std::string_view(path).starts_with("/org/freedesktop/ModemManager1/Modem/"))
            continue;
        auto bearers = bus.paths(owner->c_str(), path, modemInterface, "Bearers");
        if (!bearers)
            continue;
        for (const auto& bearer : *bearers)
        {
            if (bus.text(owner->c_str(), bearer.c_str(), bearerInterface, "Interface") != interface ||
                bus.scalar<int>(owner->c_str(), bearer.c_str(), bearerInterface, "Connected", "b") != 1)
                continue;
            auto technologies = bus.scalar<unsigned int>(owner->c_str(), path, modemInterface, "AccessTechnologies", "u");
            if (!technologies || (access && *access != *technologies))
                return nullptr;
            access = *technologies;
        }
    }
    if (!SystemBus::exit(objects) || !access)
        return nullptr;
    constexpr unsigned int nr = 1 << 15;
    constexpr unsigned int lte = (1 << 14) | (1 << 16) | (1 << 17);
    constexpr unsigned int thirdGeneration = (0x1f << 5) | (0x7 << 11);
    constexpr unsigned int secondGeneration = (0xf << 1) | (1 << 10);
    if (*access & ~(nr | lte | thirdGeneration | secondGeneration))
        return nullptr;
    if (*access & nr)
        return "5G";
    if (*access & lte)
        return "4G";
    if (*access & thirdGeneration)
        return "3G";
    return *access & secondGeneration ? "2G" : nullptr;
}

void addMetered(ValueMap& result, unsigned int metered)
{
    switch (metered)
    {
    case 1: result["isMetered"] = true; break;
    case 2: result["isMetered"] = false; break;
    case 3: result["costHint"] = "likelyMetered"; break;
    case 4: result["costHint"] = "likelyUnmetered"; break;
    }
}

void watchKernel(std::stop_token stop, int wake)
{
    FileDescriptor events(socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC | SOCK_NONBLOCK, NETLINK_ROUTE));
    if (events.get() < 0)
        return;
    sockaddr_nl address{};
    address.nl_family = AF_NETLINK;
    address.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR | RTMGRP_IPV4_ROUTE |
                        RTMGRP_IPV6_ROUTE | RTMGRP_IPV4_RULE;
    if (bind(events.get(), reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0)
        return;
    for (int group : {RTNLGRP_IPV6_RULE, RTNLGRP_NEXTHOP})
        setsockopt(events.get(), SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &group, sizeof(group));
    std::array<pollfd, 2> descriptors{{{events.get(), POLLIN, 0}, {wake, POLLIN, 0}}};
    std::array<char, 16 * 1024> message{};
    while (!stop.stop_requested())
    {
        if (poll(descriptors.data(), descriptors.size(), -1) < 0)
        {
            if (errno == EINTR)
                continue;
            return;
        }
        if (descriptors[1].revents || stop.stop_requested())
            return;
        if (!(descriptors[0].revents & (POLLIN | POLLERR)))
            return;
        // Drain a bounded batch so subscribe/stop stays responsive under traffic.
        for (int i = 0; i < 32; ++i)
            if (recv(events.get(), message.data(), message.size(), 0) < 0)
                break;
        networkChanged();
    }
}

struct NetworkEvents
{
    std::mutex mutex;
    std::optional<FileDescriptor> wake;
    std::jthread worker;

    void start()
    {
        if (worker.joinable())
            return;
        wake.emplace(eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK));
        if (wake->get() >= 0)
        {
            try
            {
                worker = std::jthread(watchKernel, wake->get());
                return;
            }
            catch (const std::system_error&)
            {
                // The common subscription can still refresh by polling.
            }
        }
        wake.reset();
    }

    void stop()
    {
        if (worker.joinable())
        {
            worker.request_stop();
            uint64_t event = 1;
            while (write(wake->get(), &event, sizeof(event)) < 0 && errno == EINTR)
            {
            }
            worker.join();
        }
        wake.reset();
    }

    ~NetworkEvents() { stop(); }
};

NetworkEvents& events()
{
    static NetworkEvents state;
    return state;
}
}

ValueMap readNetwork()
{
    RouteSocket socket;
    auto ipv4 = defaultRoute(socket, AF_INET);
    auto ipv6 = defaultRoute(socket, AF_INET6);
    if (ipv4.error && ipv6.error)
    {
        auto code = ipv4.error == EACCES || ipv4.error == EPERM ? "permissionDenied" : "ioError";
        return failure(code, "rtnetlink RTM_GETROUTE", ipv4.error);
    }
    if (ipv4.ambiguous || ipv6.ambiguous || ipv4.error || ipv6.error)
        return {};
    ValueMap result;
    if (!ipv4.interface && !ipv6.interface)
    {
        result["primaryType"] = "none";
        for (auto field : {"cellularGeneration", "isMetered", "isVpn", "costHint"})
            missing(result, field, "notApplicable");
        return result;
    }

    auto link = readLink(socket, ipv4.interface ? ipv4.interface : ipv6.interface);
    if (link.name.empty())
        return {};
    if (ipv4.interface && ipv6.interface && ipv4.interface != ipv6.interface)
    {
        auto other = readLink(socket, ipv6.interface);
        if (!link.transport.empty() && link.transport == other.transport)
            result["primaryType"] = link.transport;
        if (!link.transport.empty() && !other.transport.empty() && link.transport != "cellular" && other.transport != "cellular")
            missing(result, "cellularGeneration", "notApplicable");
        return result;
    }

    SystemBus bus;
    auto owner = bus.owner(managerName);
    auto transport = link.transport;
    std::string cellularInterface = link.name;
    if (link.kind == "wireguard" || link.kind == "ovpn" || link.kind == "ovpn-dco" || link.kind == "amneziawg")
        result["isVpn"] = true;
    if (owner && link.possibleTunnel)
    {
        auto vpn = defaultVpn(bus, owner->c_str(), link, ipv4.interface != 0, ipv6.interface != 0);
        if (vpn)
        {
            result["isVpn"] = true;
            // The primary connection identifies the route to this confirmed default VPN.
            auto underlay = vpnUnderlay(bus, owner->c_str());
            transport = underlay.transport;
            if (transport == "cellular")
                cellularInterface = bus.text(owner->c_str(), underlay.path.c_str(), deviceInterface, "IpInterface").value_or("");
        }
    }
    else if (owner)
    {
        auto device = managedDevice(bus, owner->c_str(), link.name);
        if (!device.transport.empty())
            transport = device.transport;
        addMetered(result, device.metered);
    }
    // Tunnels without a verified underlay and split/policy paths stay unknown.
    if (!transport.empty())
    {
        result["primaryType"] = transport;
        if (transport == "cellular")
        {
            if (!cellularInterface.empty())
                if (auto generation = cellularGeneration(bus, cellularInterface))
                    result["cellularGeneration"] = generation;
        }
        else
            missing(result, "cellularGeneration", "notApplicable");
    }
    // A changed route can otherwise combine a previous connection with current policy.
    if (defaultRoute(socket, AF_INET) != ipv4 || defaultRoute(socket, AF_INET6) != ipv6)
        return {};
    return result;
}

void startNetworkEvents()
{
    auto& state = events();
    std::lock_guard lock(state.mutex);
    state.start();
}

void stopNetworkEvents()
{
    auto& state = events();
    std::lock_guard lock(state.mutex);
    state.stop();
}
} // namespace cc::system_info
