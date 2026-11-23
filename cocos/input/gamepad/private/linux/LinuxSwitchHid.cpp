#include "LinuxSwitchHid.h"

#include <fcntl.h>
#include <linux/hidraw.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <filesystem>

namespace cc::input::detail {
namespace {

constexpr std::uint64_t replyTimeout = 120000000, rumbleRefresh = 50000000;
constexpr std::uint64_t simpleGrace = 100000000, fullReportTimeout = 500000000;
constexpr unsigned maxAttempts = 3;

enum SetupStep { Handshake, HighSpeed, SecondHandshake, ForceUsb, ReportMode,
                 FactorySticks, UserSticks, FactoryImu, UserImu, Vibration, SetupDone };

const std::array<SwitchRequest, SetupDone> setup{{
    {0x02, true}, {0x03, true}, {0x02, true}, {0x04, true},
    {0x03, false, {0x30}, 1},
    SwitchRequest::spi(SwitchFactorySticks, 18), SwitchRequest::spi(SwitchUserSticks, 22),
    SwitchRequest::spi(SwitchFactoryImu, 24), SwitchRequest::spi(SwitchUserImu, 20),
    {0x48, false, {1}, 1}
}};

SwitchRequest imuRequest(bool enabled)
{
    return {0x40, false, {static_cast<std::uint8_t>(enabled)}, 1};
}

} // namespace

std::unique_ptr<LinuxSwitchHid> LinuxSwitchHid::open(const std::string& path, EndpointKey key)
{
    const int fd = ::open(path.c_str(), O_RDWR | O_NONBLOCK | O_CLOEXEC);
    if (fd < 0)
        return {};
    hidraw_devinfo info{};
    const auto model = ::ioctl(fd, HIDIOCGRAWINFO, &info) == 0 ?
        switchModel(static_cast<std::uint16_t>(info.vendor), static_cast<std::uint16_t>(info.product)) : std::nullopt;
    if (!model || (info.bustype != BUS_USB && info.bustype != BUS_BLUETOOTH))
    {
        ::close(fd);
        return {};
    }
    std::error_code error;
    const auto node = std::filesystem::canonical(
        std::filesystem::path("/sys/class/hidraw") / std::filesystem::path(path).filename() / "device", error);
    if (error || node.empty())
    {
        ::close(fd);
        return {};
    }
    const bool kernelManaged = std::filesystem::read_symlink(node / "driver", error).filename() == "nintendo";
    // hid-nintendo registers hidraw before it initializes the controller and
    // registers input. Wait for the latter before sending any subcommands.
    if (kernelManaged && !std::filesystem::is_directory(node / "input", error))
    {
        ::close(fd);
        return {};
    }
    EndpointDescriptor descriptor;
    descriptor.name = switchName(*model);
    descriptor.controllerType = switchGamepadType(*model);
    descriptor.vendor = static_cast<std::uint16_t>(info.vendor);
    descriptor.product = static_cast<std::uint16_t>(info.product);
    descriptor.link = info.bustype == BUS_USB ? Link::Wired : Link::Wireless;
    descriptor.physicalAssociation = node.native();
    if (std::array<char, 128> serial{}; ::ioctl(fd, HIDIOCGRAWUNIQ(serial.size()), serial.data()) > 0)
    {
        serial.back() = '\0';
        if (serial.front()) descriptor.serial = serial.data();
    }
    return std::make_unique<LinuxSwitchHid>(fd, key, *model, std::move(descriptor), kernelManaged);
}

LinuxSwitchHid::LinuxSwitchHid(int fd, EndpointKey key, SwitchModel model, EndpointDescriptor descriptor,
                               bool kernelManaged)
    : _fd(fd), _key(key), _descriptor(std::move(descriptor)), _model(model),
      _usb(_descriptor.link == Link::Wired), _kernelManaged(kernelManaged), _reports(model),
      _setupStep(kernelManaged ? FactorySticks : _usb ? Handshake : ReportMode)
{
    auto& layout = _descriptor.layout;
    layout.id = _usb ? "linux-switch-usb-v1" : "linux-switch-bluetooth-v1";
    layout.id += model == SwitchModel::Pro ? "/pro" : model == SwitchModel::JoyConLeft ? "/left" : "/right";
    layout.guid = DeviceGuid::make(_usb ? BUS_USB : BUS_BLUETOOTH, *_descriptor.vendor, *_descriptor.product,
                                   0, {}, _descriptor.name, 'h', static_cast<std::uint8_t>(model));
    layout.legacyHidapi = true;
    configureSwitchLayout(layout, model);
    _raw.buttons.resize(layout.buttonCount);
    _raw.axes.resize(layout.axisCount);
    _raw.axesKnown.assign(layout.axisCount, 1);
    _raw.hats.resize(layout.hatCount);
}

LinuxSwitchHid::~LinuxSwitchHid()
{
    neutral();
    if (_imuWritten) write(_output.subcommand(imuRequest(false), SwitchNeutralRumble));
    restoreReportMode();
    ::close(_fd);
}

bool LinuxSwitchHid::write(const SwitchPacket& packet) const
{
    const auto size = _usb ? packet.size() : 49u;
    return ::write(_fd, packet.data(), size) == static_cast<ssize_t>(size);
}

bool LinuxSwitchHid::read(ReportSink& sink, const std::function<void()>& beforeAttach)
{
    std::array<std::uint8_t, 512> buffer{};
    for (unsigned iteration = 0; iteration < 64; ++iteration)
    {
        const auto size = ::read(_fd, buffer.data(), buffer.size());
        if (size <= 0)
            return size < 0 && (errno == EAGAIN || errno == EINTR);
        receive(std::span(buffer).first(static_cast<std::size_t>(size)), sink, beforeAttach, {});
    }
    return true;
}

void LinuxSwitchHid::receive(std::span<const std::uint8_t> packet, ReportSink& sink,
                             const std::function<void()>& beforeAttach, ReportTime time)
{
    if (_setupStep < SetupDone && _setupAttempts)
    {
        const auto& request = setup[_setupStep];
        if (const auto reply = request.reply(packet))
        {
            if (_setupStep >= FactorySticks && _setupStep <= UserImu)
                _reports.calibrate(static_cast<std::uint16_t>(request.data[0] | (request.data[1] << 8)), *reply);
            if (_setupStep == Vibration)
            {
                _vibrationReady = true;
                _attachBy = time.receivedNs + fullReportTimeout;
            }
            ++_setupStep;
            _setupAttempts = 0;
            _setupAt = 0;
            return;
        }
    }
    if (!_kernelManaged && _imuAttemptsLeft < maxAttempts && imuRequest(_imuTarget).reply(packet))
        _imuAttemptsLeft = 0;

    if (_lastFull && time.receivedNs - _lastFull < simpleGrace && packet.front() == 0x3f)
        return;
    const auto sample = _reports.decode(packet, _active && _sensors.any());
    if (!sample)
        return;
    if (!_startedInFullMode)
        _startedInFullMode = sample->power.has_value() && !_modeRequested;
    if (sample->power) _lastFull = time.receivedNs;
    if (!_attached && (!_vibrationReady || !sample->power))
        return;

    constexpr auto maxChanges = std::tuple_size_v<decltype(SwitchInput::buttons)> +
        std::tuple_size_v<decltype(SwitchInput::axes)> + 1;
    std::array<RawChange, maxChanges> changes{};
    unsigned count = 0;
    const auto update = [&](RawKind kind, unsigned index, auto& current, auto value) {
        if (current != value)
        {
            current = value;
            changes[count++] = {kind, index, value};
        }
    };
    for (unsigned i = 0; i < _raw.buttons.size(); ++i)
        update(RawKind::Button, i, _raw.buttons[i], sample->buttons[i]);
    for (unsigned i = 0; i < _raw.axes.size(); ++i)
        update(RawKind::Axis, i, _raw.axes[i], sample->axes[i]);
    if (!_raw.hats.empty())
        update(RawKind::Hat, 0, _raw.hats[0], sample->hat);
    _lastInput = time;
    std::optional<Power> power;
    if (sample->power && (sample->power->state != _descriptor.power.state ||
                         sample->power->percent != _descriptor.power.percent))
    {
        _descriptor.power = *sample->power;
        power = sample->power;
    }
    if (!_attached)
    {
        auto& caps = _descriptor.capabilities;
        caps.features.set(static_cast<unsigned>(Feature::BodyRumble));
        caps.features.set(static_cast<unsigned>(Feature::PlayerLights));
        caps.playerLightMask = 0x0f;
        for (auto sensor : {Sensor::Accel, Sensor::Gyro})
        {
            const auto index = static_cast<unsigned>(sensor);
            caps.sensors.set(index);
            caps.nominalHz[index] = 200.f;
        }
        beforeAttach();
        _attached = true;
        _attachBy = 0;
        sink.attached(_key, _descriptor, baseline());
        return;
    }
    std::array<Motion, 6> motion{};
    unsigned motionCount = 0;
    for (const auto& value : std::span(sample->motion).first(sample->motionCount))
        if (_sensors.test(static_cast<unsigned>(value.sensor)))
            motion[motionCount++] = value;
    if (count || motionCount || power)
        sink.report(_key, {std::span(changes).first(count), {}, std::span(motion).first(motionCount),
                           power, ++_cursor, time});
}

void LinuxSwitchHid::configure(std::uint64_t now)
{
    // hid-nintendo performs USB setup and enables full reports and IMU.
    if ((_kernelManaged && !_lastFull) || now < _setupAt)
        return;
    if (_setupAttempts == maxAttempts)
    {
        ++_setupStep;
        _setupAttempts = 0;
        if (_setupStep == SetupDone) restoreReportMode();
        return;
    }
    const auto& request = setup[_setupStep];
    const bool written = write(request.usb ? _output.usb(request.id) :
                               _output.subcommand(request, SwitchNeutralRumble));
    if (_setupStep == ReportMode) _modeRequested |= written;
    if (_setupStep == ForceUsb && written)
    {
        ++_setupStep; // Force USB has no acknowledgement.
        _setupAttempts = 0;
        return;
    }
    ++_setupAttempts;
    _setupAt = now + replyTimeout;
}

void LinuxSwitchHid::restoreReportMode()
{
    // evdev's generic Bluetooth path may only recognize simple reports.
    if (_modeRequested && !_usb && !_startedInFullMode.value_or(false) &&
        write(_output.subcommand({0x03, false, {0x3f}, 1}, SwitchNeutralRumble)))
        _modeRequested = false;
}

void LinuxSwitchHid::updateImu(std::uint64_t now)
{
    if (_kernelManaged || !_attached)
        return;
    const bool enabled = _active && _sensors.any();
    if (_imuTarget != enabled)
    {
        _imuTarget = enabled;
        _imuAttemptsLeft = maxAttempts;
        // Leave time for a previous enable or disable acknowledgement to drain.
    }
    if (_imuAttemptsLeft && now >= _imuAt)
    {
        if (write(_output.subcommand(imuRequest(enabled), _motors)))
            _imuWritten = enabled;
        --_imuAttemptsLeft;
        _imuAt = now + replyTimeout;
    }
}

AttachedEndpoint LinuxSwitchHid::snapshot()
{
    neutral();
    ++_key.generation;
    _sensors.reset();
    return {_key, _descriptor, baseline()};
}

void LinuxSwitchHid::setSensor(Sensor sensor, bool enabled)
{
    if (sensor == Sensor::Gyro || sensor == Sensor::Accel)
        _sensors.set(static_cast<unsigned>(sensor), enabled);
}

Error LinuxSwitchHid::submit(const OutputCommand& command)
{
    if (!_attached)
        return Error::Unsupported;
    const auto* stop = std::get_if<Stop>(&command);
    if (_stopPending && !stop)
        return Error::Busy;
    const auto now = nowNs();
    const bool stopBody = stop && (stop->channel == Channel::All || stop->channel == Channel::Body);
    const bool stopLights = stop && (stop->channel == Channel::All || stop->channel == Channel::Lights);
    const auto* rumble = std::get_if<Rumble>(&command);
    const auto motors = rumble ? encodeSwitchRumble(_model, rumble->low, rumble->high) :
        stopBody ? SwitchNeutralRumble : _motors;
    if (const auto* lights = std::get_if<PlayerLights>(&command); lights || (stopLights && _lights))
    {
        const auto mask = static_cast<std::uint8_t>(lights ? lights->mask & 0x0f : 0);
        if (!write(_output.subcommand({0x30, false, {mask}, 1}, motors)))
            return Error::BackendFailure;
        _lights = mask;
    }
    else if (rumble || (stopBody && _rumbleEnd))
    {
        if (!write(_output.rumble(motors)))
            return Error::BackendFailure;
    }
    else if (!stopBody && !stopLights)
        return Error::Unsupported;
    _motors = motors;
    if (rumble)
    {
        _rumbleEnd = now + static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(rumble->duration).count());
        _rumbleAt = std::min(now + rumbleRefresh, _rumbleEnd);
    }
    else if (stopBody)
        _rumbleEnd = 0;
    return Error::None;
}

void LinuxSwitchHid::neutral()
{
    _stopPending = (_rumbleEnd || _lights) && submit(Stop{}) != Error::None;
    if (_stopPending)
    {
        _motors = SwitchNeutralRumble;
        _stopAt = nowNs() + rumbleRefresh;
    }
}

void LinuxSwitchHid::tick(std::uint64_t now, bool active)
{
    _active = active;
    if (_attachBy && now >= _attachBy)
    {
        _attachBy = 0;
        _vibrationReady = false;
        restoreReportMode();
    }
    if (_setupStep < SetupDone)
    {
        configure(now);
        return;
    }
    if (_stopPending && now >= _stopAt)
        neutral();
    if (!_stopPending && _rumbleEnd && now >= _rumbleAt)
    {
        if (now >= _rumbleEnd)
        {
            if (submit(Stop{Channel::Body}) == Error::BackendFailure)
            {
                _motors = SwitchNeutralRumble;
                _rumbleAt = now + rumbleRefresh;
            }
        }
        else
        {
            write(_output.rumble(_motors));
            _rumbleAt = std::min(now + rumbleRefresh, _rumbleEnd);
        }
    }
    updateImu(now);
}

bool LinuxSwitchHid::needsPolling() const
{
    return (_setupStep < SetupDone && (!_kernelManaged || _lastFull)) ||
        _attachBy || _stopPending || _rumbleEnd || _imuAttemptsLeft;
}

} // namespace cc::input::detail
