#include "../PlatformGamepadBackend.h"
#include "LinuxSonyHid.h"

#include <linux/input.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef CC_GAMEPAD_HAVE_UDEV
#include <libudev.h>
#endif

#include <algorithm>
#include <cerrno>
#include <filesystem>
#include <map>
#include <mutex>
#include <ranges>
#include <set>
#include <thread>
#include <utility>

namespace cc::input::detail {
namespace {

class File {
public:
    explicit File(int value = -1) : _value(value) {}
    File(File&& old) noexcept : _value(std::exchange(old._value, -1)) {}
    File& operator=(File&& old) noexcept { std::swap(_value, old._value); return *this; }
    ~File() { if (_value >= 0) ::close(_value); }
    int get() const { return _value; }
    explicit operator bool() const { return _value >= 0; }

private:
    int _value;
};

template<unsigned Last>
struct Bits {
    std::array<unsigned char, Last / 8 + 1> bytes{};
    bool has(unsigned index) const { return (bytes[index / 8] & (1u << (index % 8))) != 0; }
};

constexpr std::string_view deviceDirectory = "/dev/input";
constexpr unsigned firstHat = ABS_HAT0X;
constexpr unsigned lastHat = ABS_HAT3Y;

bool sameHidDevice(const std::string& path, const std::string& parent)
{
    std::error_code error;
    const auto file = std::filesystem::path(path).filename();
    const auto target = std::filesystem::canonical(std::filesystem::path("/sys/class/input") / file / "device", error);
    return !error && target.native().starts_with(parent + "/");
}

std::int16_t scaled(int value, const input_absinfo& range)
{
    if (range.minimum >= range.maximum)
        return 0;
    const auto offset = static_cast<std::int64_t>(std::clamp(value, range.minimum, range.maximum)) - range.minimum;
    return static_cast<std::int16_t>(offset * 65535 / (static_cast<std::int64_t>(range.maximum) - range.minimum)
                                     - 32768);
}

int hatDirection(int value, const input_absinfo& range)
{
    // Digital hats are usually -1/0/1. Some drivers report 0/1/2 instead.
    const auto delta = 2 * static_cast<std::int64_t>(value) - range.minimum - range.maximum;
    const auto halfRange = static_cast<std::int64_t>(range.maximum) - range.minimum;
    return delta > halfRange / 2 ? 1 : delta < -halfRange / 2 ? -1 : 0;
}

std::uint8_t hat(int x, int y)
{
    return static_cast<std::uint8_t>((y < 0 ? 1 : y > 0 ? 4 : 0) | (x > 0 ? 2 : x < 0 ? 8 : 0));
}

std::string name(int fd, unsigned long request)
{
    std::array<char, 256> value{};
    if (::ioctl(fd, request, value.data()) <= 0)
        return {};
    value.back() = '\0';
    return value.data();
}

struct Device {
    File fd;
    dev_t inodeDevice = 0;
    ino_t inode = 0;
    EndpointKey key{};
    EndpointDescriptor descriptor;
    RawState state;
    std::map<unsigned, unsigned> buttons, axes, hats;
    std::map<unsigned, input_absinfo> ranges;
    std::array<std::pair<int, int>, 4> hatValues{};
    std::vector<input_event> pending;
    std::vector<RawChange> changes;
    std::uint64_t cursor = 0;
    bool dropping = false;
    bool monotonic = false;
    int effect = -1;

    bool sample()
    {
        Bits<KEY_MAX> keys;
        if (::ioctl(fd.get(), EVIOCGKEY(keys.bytes.size()), keys.bytes.data()) < 0)
            return false;
        for (const auto& [code, index] : buttons)
            state.buttons[index] = keys.has(code);
        for (auto& [code, range] : ranges)
        {
            if (::ioctl(fd.get(), EVIOCGABS(code), &range) < 0)
                return false;
            if (const auto axis = axes.find(code); axis != axes.end())
                state.axes[axis->second] = scaled(range.value, range);
        }
        for (const auto& [code, index] : hats)
        {
            auto& [x, y] = hatValues[(code - firstHat) / 2];
            const auto horizontal = ranges.find(code), vertical = ranges.find(code + 1);
            x = horizontal == ranges.end() ? 0 : hatDirection(horizontal->second.value, horizontal->second);
            y = vertical == ranges.end() ? 0 : hatDirection(vertical->second.value, vertical->second);
            state.hats[index] = hat(x, y);
        }
        return true;
    }

    AttachedEndpoint attachment() const { return {key, descriptor, {state, cursor, {}}}; }

    void neutral() const
    {
        if (effect >= 0)
        {
            input_event event{};
            event.type = EV_FF;
            event.code = static_cast<__u16>(effect);
            ::write(fd.get(), &event, sizeof(event));
        }
    }

    void closeOutput() const
    {
        neutral();
        if (effect >= 0)
            ::ioctl(fd.get(), EVIOCRMFF, effect);
    }

    Error applyOutput(const OutputCommand& command)
    {
        if (const auto* stop = std::get_if<Stop>(&command))
        {
            if (stop->channel != Channel::All && stop->channel != Channel::Body)
                return Error::Unsupported;
            neutral();
            return Error::None;
        }
        const auto* rumble = std::get_if<Rumble>(&command);
        if (!rumble || !descriptor.capabilities.features.test(static_cast<unsigned>(Feature::BodyRumble)))
            return Error::Unsupported;
        if (rumble->duration.count() == 0 || (rumble->low == 0.f && rumble->high == 0.f))
        {
            neutral();
            return Error::None;
        }
        ff_effect payload{};
        payload.type = FF_RUMBLE;
        payload.id = static_cast<__s16>(effect);
        payload.replay.length = static_cast<__u16>(rumble->duration.count());
        payload.u.rumble.strong_magnitude = static_cast<__u16>(rumble->low * 65535.f + .5f);
        payload.u.rumble.weak_magnitude = static_cast<__u16>(rumble->high * 65535.f + .5f);
        if (::ioctl(fd.get(), EVIOCSFF, &payload) < 0)
            return Error::BackendFailure;
        effect = payload.id;
        input_event event{};
        event.type = EV_FF;
        event.code = static_cast<__u16>(effect);
        event.value = 1;
        return ::write(fd.get(), &event, sizeof(event)) == sizeof(event) ? Error::None : Error::BackendFailure;
    }

    void flush(ReportSink& sink, const input_event& boundary)
    {
        ReportTime time;
        if (monotonic && boundary.input_event_sec >= 0 && boundary.input_event_usec >= 0)
        {
            time.sourceNs = static_cast<std::uint64_t>(boundary.input_event_sec) * 1000000000ULL +
                            static_cast<std::uint64_t>(boundary.input_event_usec) * 1000ULL;
            time.quality = TimeQuality::ConvertedOS;
        }
        const auto publish = [&] {
            if (!changes.empty())
                sink.report(key, {changes, {}, {}, {}, ++cursor, time});
            changes.clear();
        };
        const auto set = [&](RawKind kind, unsigned index, auto& old, auto value) {
            if (old == value)
                return;
            if (std::ranges::any_of(changes, [&](const auto& c) { return c.kind == kind && c.index == index; }))
                publish();
            old = value;
            changes.push_back({kind, index, value});
        };
        auto lastHatValues = hatValues;
        for (const auto& event : pending)
        {
            if (event.type == EV_KEY && event.value != 2)
            {
                if (const auto it = buttons.find(event.code); it != buttons.end())
                    set(RawKind::Button, it->second, state.buttons[it->second], static_cast<std::uint8_t>(event.value != 0));
            }
            else if (event.type == EV_ABS)
            {
                if (const auto it = axes.find(event.code); it != axes.end())
                    set(RawKind::Axis, it->second, state.axes[it->second], scaled(event.value, ranges.at(event.code)));
                else if (event.code >= firstHat && event.code <= lastHat && hats.contains(event.code & ~1u))
                {
                    auto& [x, y] = lastHatValues[(event.code - firstHat) / 2];
                    if (const auto range = ranges.find(event.code); range != ranges.end())
                        (event.code % 2 ? y : x) = hatDirection(event.value, range->second);
                }
            }
        }
        for (const auto& [code, index] : hats)
        {
            const auto& [x, y] = lastHatValues[(code - firstHat) / 2];
            set(RawKind::Hat, index, state.hats[index], hat(x, y));
        }
        hatValues = lastHatValues;
        publish();
        pending.clear();
    }

    bool read(ReportSink& sink)
    {
        std::array<input_event, 64> buffer{};
        for (unsigned batch = 0; batch < 16; ++batch)
        {
            const auto count = ::read(fd.get(), buffer.data(), sizeof(buffer));
            if (count < 0)
                return errno == EAGAIN || errno == EINTR;
            if (count == 0 || count % sizeof(input_event) != 0)
                return false;
            for (const auto& event : std::span(buffer).first(static_cast<std::size_t>(count) / sizeof(input_event)))
            {
                if ((event.type == EV_SYN && event.code == SYN_DROPPED) || pending.size() == 4096)
                {
                    if (!dropping)
                        sink.desynchronized(key, {GapCause::DriverOverflow, {}});
                    dropping = true;
                    pending.clear();
                }
                else if (event.type == EV_SYN && event.code == SYN_REPORT)
                {
                    if (dropping)
                    {
                        if (!sample())
                            return false;
                        dropping = false;
                        sink.baseline(key, {state, ++cursor, {}});
                        // Kernel state may include the remainder of this read.
                        return true;
                    }
                    flush(sink, event);
                }
                else if (!dropping && (event.type == EV_KEY || event.type == EV_ABS))
                    pending.push_back(event);
            }
        }
        return true;
    }
};

void describeControls(Device& pad, const Bits<KEY_MAX>& keys, const Bits<ABS_MAX>& abs)
{
    auto& layout = pad.descriptor.layout;
    layout.id = "linux-evdev-v1";
    const auto addButton = [&](unsigned code) {
        if (keys.has(code))
        {
            pad.buttons.emplace(code, layout.buttonCount++);
            layout.id += "/b" + std::to_string(code);
        }
    };
    for (unsigned code = BTN_JOYSTICK; code < KEY_MAX; ++code)
        addButton(code);
    for (unsigned code = 0; code < BTN_JOYSTICK; ++code)
        addButton(code);
    for (unsigned code = 0; code < ABS_MAX; ++code)
    {
        input_absinfo range{};
        if (abs.has(code) && ::ioctl(pad.fd.get(), EVIOCGABS(code), &range) >= 0)
            pad.ranges.emplace(code, range);
    }
    const auto qualifies = [&](unsigned code, auto predicate) {
        const auto axis = pad.ranges.find(code);
        return axis == pad.ranges.end() || predicate(axis->second);
    };
    const auto threeStates = [](const input_absinfo& range) { return range.minimum == -1 && range.maximum == 1; };
    const auto uncalibrated = [](const input_absinfo& range) { return !range.fuzz && !range.flat && !range.resolution; };
    for (unsigned code = 0; code < ABS_MAX; ++code)
    {
        if (code >= firstHat && code <= lastHat && code % 2 == 0 &&
            (pad.ranges.contains(code) || pad.ranges.contains(code + 1)) &&
            ((qualifies(code, threeStates) && qualifies(code + 1, threeStates)) ||
             (qualifies(code, uncalibrated) && qualifies(code + 1, uncalibrated))))
        {
            pad.hats.emplace(code, layout.hatCount++);
            layout.id += "/h" + std::to_string(code++);
            continue;
        }
        if (const auto axis = pad.ranges.find(code); axis != pad.ranges.end())
        {
            pad.axes.emplace(code, layout.axisCount++);
            layout.axisPresent.push_back(axis->second.minimum < axis->second.maximum);
            layout.id += "/a" + std::to_string(code);
        }
    }
    pad.state.buttons.resize(layout.buttonCount);
    pad.state.axes.resize(layout.axisCount);
    pad.state.hats.resize(layout.hatCount);

    constexpr std::pair<unsigned, std::string_view> buttonNames[]{
        {BTN_SOUTH, "a"}, {BTN_EAST, "b"}, {BTN_WEST, "x"}, {BTN_NORTH, "y"},
        {BTN_TL, "leftshoulder"}, {BTN_TR, "rightshoulder"}, {BTN_SELECT, "back"},
        {BTN_START, "start"}, {BTN_MODE, "guide"}, {BTN_THUMBL, "leftstick"}, {BTN_THUMBR, "rightstick"},
        {BTN_DPAD_UP, "dpup"}, {BTN_DPAD_RIGHT, "dpright"}, {BTN_DPAD_DOWN, "dpdown"}, {BTN_DPAD_LEFT, "dpleft"},
    };
    if (!keys.has(BTN_SOUTH) || !keys.has(BTN_EAST))
        return;
    const auto bind = [&](std::string_view output, std::string input) {
        layout.builtInMapping += std::string(output) + ":" + input + ",";
    };
    for (const auto& [code, output] : buttonNames)
        if (const auto index = pad.buttons.find(code); index != pad.buttons.end())
            bind(output, "b" + std::to_string(index->second));
    constexpr std::pair<unsigned, std::string_view> axisNames[]{
        {ABS_X, "leftx"}, {ABS_Y, "lefty"}, {ABS_RX, "rightx"}, {ABS_RY, "righty"},
        {ABS_Z, "lefttrigger"}, {ABS_RZ, "righttrigger"},
    };
    for (const auto& [code, output] : axisNames)
        if (const auto index = pad.axes.find(code); index != pad.axes.end())
            bind(output, "a" + std::to_string(index->second));
    if (const auto index = pad.hats.find(firstHat); index != pad.hats.end())
    {
        const auto prefix = "h" + std::to_string(index->second) + ".";
        for (unsigned i = 0; i < 4; ++i)
            if (!keys.has(buttonNames[11 + i].first))
                bind(buttonNames[11 + i].second, prefix + std::to_string(1u << i));
    }
}

std::optional<Device> openDevice(const std::string& path, bool joystick)
{
    Device pad;
    pad.fd = File(::open(path.c_str(), O_RDWR | O_CLOEXEC | O_NONBLOCK));
    const bool writable = static_cast<bool>(pad.fd);
    if (!writable)
        pad.fd = File(::open(path.c_str(), O_RDONLY | O_CLOEXEC | O_NONBLOCK));
    if (!pad.fd)
        return {};
    const auto fd = pad.fd.get();
    Bits<KEY_MAX> keys;
    Bits<ABS_MAX> abs;
    if (::ioctl(fd, EVIOCGBIT(EV_KEY, keys.bytes.size()), keys.bytes.data()) < 0 ||
        ::ioctl(fd, EVIOCGBIT(EV_ABS, abs.bytes.size()), abs.bytes.data()) < 0)
        return {};
    if (!joystick)
    {
        bool hasGameButton = false;
        for (unsigned code = BTN_JOYSTICK; code < BTN_DIGI; ++code)
            hasGameButton |= keys.has(code);
        if (!hasGameButton)
            return {};
    }
    input_id id{};
    struct stat stat{};
    if (::ioctl(fd, EVIOCGID, &id) < 0 || ::fstat(fd, &stat) != 0)
        return {};
    pad.inodeDevice = stat.st_rdev;
    pad.inode = stat.st_ino;
    auto& descriptor = pad.descriptor;
    descriptor.name = name(fd, EVIOCGNAME(256));
    descriptor.layout.guid = DeviceGuid::make(id.bustype, id.vendor, id.product, id.version, {}, descriptor.name);
    if (descriptor.name.empty())
        descriptor.name = "Linux Gamepad";
    descriptor.vendor = id.vendor;
    descriptor.product = id.product;
    descriptor.version = id.version;
    if (auto serial = name(fd, EVIOCGUNIQ(256)); !serial.empty())
        descriptor.serial = std::move(serial);
    descriptor.link = id.bustype == BUS_BLUETOOTH ? Link::Wireless : id.bustype == BUS_USB ? Link::Wired : Link::Unknown;
    describeControls(pad, keys, abs);
    if (pad.buttons.empty() || !pad.sample())
        return {};
    Bits<FF_MAX> feedback;
    if (writable && ::ioctl(fd, EVIOCGBIT(EV_FF, feedback.bytes.size()), feedback.bytes.data()) >= 0 &&
        feedback.has(FF_RUMBLE))
        descriptor.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble));
    auto clock = CLOCK_MONOTONIC;
    pad.monotonic = ::ioctl(fd, EVIOCSCLOCKID, &clock) == 0;
    return pad;
}

using InputPaths = std::map<std::string, bool>;

class Monitor {
public:
    explicit Monitor(int epoll) : _epoll(epoll)
    {
#ifdef CC_GAMEPAD_HAVE_UDEV
        _udev = udev_new();
        if (_udev)
            _monitor = udev_monitor_new_from_netlink(_udev, "udev");
        if (_monitor)
        {
            udev_monitor_filter_add_match_subsystem_devtype(_monitor, "input", nullptr);
            if (udev_monitor_enable_receiving(_monitor) == 0 && watch(udev_monitor_get_fd(_monitor)))
                return;
            udev_monitor_unref(std::exchange(_monitor, nullptr));
        }
#endif
        _notify = File(inotify_init1(IN_NONBLOCK | IN_CLOEXEC));
        if (_notify)
            watch(_notify.get());
    }

    ~Monitor()
    {
#ifdef CC_GAMEPAD_HAVE_UDEV
        if (_monitor) udev_monitor_unref(_monitor);
        if (_udev) udev_unref(_udev);
#endif
    }

    int fd() const
    {
#ifdef CC_GAMEPAD_HAVE_UDEV
        if (_monitor) return udev_monitor_get_fd(_monitor);
#endif
        return _notify.get();
    }

    void consume()
    {
#ifdef CC_GAMEPAD_HAVE_UDEV
        if (_monitor)
        {
            while (auto* device = udev_monitor_receive_device(_monitor))
                udev_device_unref(device);
            return;
        }
#endif
        std::array<char, 4096> buffer{};
        while (::read(fd(), buffer.data(), buffer.size()) > 0) {}
    }

    InputPaths list()
    {
        InputPaths paths;
#ifdef CC_GAMEPAD_HAVE_UDEV
        if (_monitor)
        {
            auto* scan = udev_enumerate_new(_udev);
            if (!scan)
                return paths;
            udev_enumerate_add_match_subsystem(scan, "input");
            udev_enumerate_scan_devices(scan);
            udev_list_entry* item = nullptr;
            udev_list_entry_foreach(item, udev_enumerate_get_list_entry(scan))
            {
                auto* device = udev_device_new_from_syspath(_udev, udev_list_entry_get_name(item));
                if (!device)
                    continue;
                const char* node = udev_device_get_devnode(device);
                const char* joystick = udev_device_get_property_value(device, "ID_INPUT_JOYSTICK");
                if (node && std::string_view(node).starts_with("/dev/input/event"))
                    paths.emplace(node, joystick && std::string_view(joystick) == "1");
                udev_device_unref(device);
            }
            udev_enumerate_unref(scan);
            return paths;
        }
#endif
        if (_notify)
            inotify_add_watch(_notify.get(), deviceDirectory.data(), IN_CREATE | IN_DELETE | IN_ATTRIB | IN_MOVED_TO | IN_MOVED_FROM);
        std::error_code error;
        for (std::filesystem::directory_iterator it(deviceDirectory, error), done; !error && it != done; it.increment(error))
            if (it->path().filename().native().starts_with("event"))
                paths.emplace(it->path().native(), false);
        return paths;
    }

    bool watch(int fd) const
    {
        epoll_event event{};
        event.events = EPOLLIN;
        event.data.fd = fd;
        return epoll_ctl(_epoll, EPOLL_CTL_ADD, fd, &event) == 0;
    }

private:
    int _epoll;
    File _notify;
#ifdef CC_GAMEPAD_HAVE_UDEV
    udev* _udev = nullptr;
    udev_monitor* _monitor = nullptr;
#endif
};

class EvdevBackend final : public GamepadBackend {
public:
    ~EvdevBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (_worker.joinable())
            return Error::Busy;
        _wake = File(eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK));
        _epoll = File(epoll_create1(EPOLL_CLOEXEC));
        if (!_wake || !_epoll)
            return Error::BackendFailure;
        epoll_event event{};
        event.events = EPOLLIN;
        event.data.fd = _wake.get();
        if (epoll_ctl(_epoll.get(), EPOLL_CTL_ADD, _wake.get(), &event) != 0)
            return Error::BackendFailure;
        _sink = &sink;
        _worker = std::thread([this] { run(); });
        return Error::None;
    }

    void stop() noexcept override
    {
        if (!_worker.joinable())
            return;
        {
            std::lock_guard lock(_mutex);
            _quitting = true;
        }
        wake();
        _worker.join();
        _quitting = false;
        _active = true;
        _resetEffects = false;
        _topology = false;
        _commands.clear();
        _baselines.clear();
        _sensorRequests.clear();
        _sink = nullptr;
    }

    void setActive(bool active) override
    {
        {
            std::lock_guard lock(_mutex);
            _active = active;
            _resetEffects |= !active;
        }
        wake();
    }

    void requestBaseline(EndpointKey key) override
    {
        {
            std::lock_guard lock(_mutex);
            _baselines.insert(key);
        }
        wake();
    }

    void requestTopology() override
    {
        {
            std::lock_guard lock(_mutex);
            _topology = true;
        }
        wake();
    }

    Error submit(EndpointKey key, const NativeCommand& command) override
    {
        {
            std::lock_guard lock(_mutex);
            if (_commands.size() >= 256 && !std::holds_alternative<Stop>(command.command))
                return Error::QueueFull;
            _commands.emplace_back(key, command);
        }
        wake();
        return Error::None;
    }

    Error setSensor(EndpointKey key, Sensor sensor, bool enabled) override
    {
        if (sensor != Sensor::Gyro && sensor != Sensor::Accel)
            return Error::Unsupported;
        {
            std::lock_guard lock(_mutex);
            _sensorRequests[{key, sensor}] = enabled;
        }
        wake();
        return Error::None;
    }

private:
    void wake() const
    {
        constexpr std::uint64_t signal = 1;
        ::write(_wake.get(), &signal, sizeof(signal));
    }

    auto remove(std::map<std::string, Device>::iterator device)
    {
        device->second.closeOutput();
        _sink->detached(device->second.key);
        return _devices.erase(device);
    }

    auto removeHid(std::map<std::string, std::unique_ptr<LinuxSonyHid>>::iterator node)
    {
        if (node->second->attached())
            _sink->detached(node->second->key());
        return _hid.erase(node);
    }

    void refreshHid(const Monitor& monitor)
    {
        for (auto it = _hid.begin(); it != _hid.end();)
        {
            std::error_code error;
            if (!std::filesystem::exists(it->first, error))
                it = removeHid(it);
            else
                ++it;
        }
        std::error_code error;
        for (std::filesystem::directory_iterator it("/dev", error), done; !error && it != done; it.increment(error))
        {
            const auto& path = it->path();
            if (!path.filename().native().starts_with("hidraw") || _hid.contains(path.native()))
                continue;
            auto device = LinuxSonyHid::open(path.native(), {0x4c4e, _nextEndpoint + 1, 1});
            if (device && monitor.watch(device->fd()))
            {
                ++_nextEndpoint;
                _hid.emplace(path.native(), std::move(device));
            }
        }
    }

    void refresh(Monitor& monitor)
    {
        refreshHid(monitor);
        const auto hidden = [&](const std::string& path) {
            return std::ranges::any_of(_hid, [&](const auto& entry) {
                return entry.second->attached() && sameHidDevice(path, entry.second->association());
            });
        };
        const auto paths = monitor.list();
        for (auto it = _devices.begin(); it != _devices.end();)
        {
            struct stat status{};
            if (paths.contains(it->first) && !hidden(it->first) && ::stat(it->first.c_str(), &status) == 0 &&
                status.st_rdev == it->second.inodeDevice && status.st_ino == it->second.inode)
                ++it;
            else
                it = remove(it);
        }
        for (const auto& [path, joystick] : paths)
        {
            if (_devices.contains(path) || hidden(path))
                continue;
            if (auto device = openDevice(path, joystick); device && monitor.watch(device->fd.get()))
            {
                device->key = {0x4c4e, ++_nextEndpoint, 1};
                auto attachment = device->attachment();
                _devices.emplace(path, std::move(*device));
                _sink->attached(attachment.key, std::move(attachment.descriptor), std::move(attachment.initial));
            }
        }
    }

    bool process(Monitor& monitor)
    {
        std::set<EndpointKey> baselines;
        std::vector<std::pair<EndpointKey, NativeCommand>> commands;
        std::map<std::pair<EndpointKey, Sensor>, bool> sensors;
        bool topology, active, reset;
        {
            std::lock_guard lock(_mutex);
            if (_quitting)
                return false;
            baselines.swap(_baselines);
            commands.swap(_commands);
            sensors.swap(_sensorRequests);
            topology = std::exchange(_topology, false);
            reset = std::exchange(_resetEffects, false);
            active = _active;
        }
        if (topology)
            refresh(monitor);
        std::vector<AttachedEndpoint> snapshot;
        for (auto& [path, device] : _hid)
        {
            if (!device->attached())
                continue;
            if (reset)
                device->neutral();
            if (topology)
                snapshot.push_back(device->snapshot());
            else if (baselines.contains(device->key()))
                _sink->baseline(device->key(), device->baseline());
            device->expire(nowNs());
        }
        for (const auto& [request, enabled] : sensors)
            for (auto& [path, device] : _hid)
                if (device->key() == request.first)
                    device->setSensor(request.second, enabled);
        for (auto& [path, device] : _devices)
        {
            if (reset)
                device.neutral();
            if (topology || baselines.contains(device.key))
            {
                device.read(*_sink);
                if (device.sample())
                {
                    device.pending.clear();
                    device.dropping = false;
                    if (topology)
                    {
                        ++device.key.generation;
                        snapshot.push_back(device.attachment());
                    }
                    else
                        _sink->baseline(device.key, {device.state, ++device.cursor, {}});
                }
            }
        }
        if (topology)
            _sink->topology(std::move(snapshot));
        for (const auto& [key, command] : commands)
        {
            const auto it = std::ranges::find_if(_devices, [&](const auto& item) { return item.second.key == key; });
            Error status = Error::Disconnected;
            const auto hid = std::ranges::find_if(_hid, [&](const auto& item) { return item.second->key() == key; });
            const bool blocked = (!active || reset) && !std::holds_alternative<Stop>(command.command);
            if (hid != _hid.end()) status = blocked ? Error::Busy : hid->second->submit(command.command);
            else if (it != _devices.end()) status = blocked ? Error::Busy : it->second.applyOutput(command.command);
            if (command.id != CommandId{})
                _sink->outputCompleted(key, command.id, status);
        }
        return true;
    }

    void run()
    {
        Monitor monitor(_epoll.get());
        refresh(monitor);
        auto nextScan = nowNs() + 1000000000ULL;
        while (process(monitor))
        {
            std::array<epoll_event, 16> events{};
            const bool timed = std::ranges::any_of(_hid, [](const auto& item) { return item.second->hasTimedOutput(); });
            const auto count = epoll_wait(_epoll.get(), events.data(), static_cast<int>(events.size()), timed ? 4 : 1000);
            if (count < 0 && errno != EINTR)
                break;
            bool rescan = nowNs() >= nextScan;
            for (int i = 0; i < count; ++i)
            {
                const auto fd = events[i].data.fd;
                if (fd == _wake.get())
                {
                    std::uint64_t ignored;
                    ::read(fd, &ignored, sizeof(ignored));
                }
                else if (fd == monitor.fd())
                {
                    monitor.consume();
                    rescan = true;
                }
                else if (const auto it = std::ranges::find_if(_hid, [&](const auto& item) {
                    return item.second->fd() == fd;
                }); it != _hid.end())
                {
                    const auto attached = it->second->attached();
                    if (!it->second->read(*_sink))
                    {
                        removeHid(it);
                        rescan = true;
                    }
                    else if (!attached && it->second->attached())
                    {
                        for (auto mirror = _devices.begin(); mirror != _devices.end();)
                        {
                            if (sameHidDevice(mirror->first, it->second->association()))
                                mirror = remove(mirror);
                            else
                                ++mirror;
                        }
                    }
                }
                else if (const auto it = std::ranges::find_if(_devices, [&](const auto& item) {
                    return item.second.fd.get() == fd;
                }); it != _devices.end() && !it->second.read(*_sink))
                    remove(it);
            }
            if (rescan)
            {
                refresh(monitor);
                nextScan = nowNs() + 1000000000ULL;
            }
        }
        for (auto& [path, device] : _devices)
            device.closeOutput();
        _devices.clear();
        _hid.clear();
    }

    ReportSink* _sink = nullptr;
    File _wake, _epoll;
    std::thread _worker;
    std::mutex _mutex;
    std::map<std::string, Device> _devices;
    std::map<std::string, std::unique_ptr<LinuxSonyHid>> _hid;
    std::vector<std::pair<EndpointKey, NativeCommand>> _commands;
    std::set<EndpointKey> _baselines;
    std::map<std::pair<EndpointKey, Sensor>, bool> _sensorRequests;
    std::uint64_t _nextEndpoint = 0;
    bool _quitting = false, _active = true, _resetEffects = false, _topology = false;
};

} // namespace

std::unique_ptr<GamepadBackend> makeLinuxGamepadBackend() { return std::make_unique<EvdevBackend>(); }

} // namespace cc::input::detail
