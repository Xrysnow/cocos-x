#include "LinuxSonyHid.h"
#include "../PlatformGamepadBackend.h"

#include <linux/hidraw.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <filesystem>
#include <fstream>

namespace cc::input::detail {
namespace {

template<std::size_t Size>
std::span<const std::uint8_t> readFeature(int fd, std::array<std::uint8_t, Size>& buffer)
{
    const auto length = ::ioctl(fd, HIDIOCGFEATURE(buffer.size()), buffer.data());
    if (length <= 0 || static_cast<std::size_t>(length) > buffer.size()) return {};
    return std::span(buffer).first(static_cast<std::size_t>(length));
}

std::optional<unsigned> usbProperty(const std::filesystem::path& path, const char* name)
{
    unsigned value = 0;
    if (std::ifstream(path / name) >> std::hex >> value)
        return value;
    return {};
}

bool isSonyUsbController(const std::filesystem::path& path, unsigned vendor)
{
    if (vendor != 0x054c)
        return false;
    const auto product = usbProperty(path, "idProduct");
    return product == 0x0ce6 || product == 0x0df2;
}

std::string usbParent(std::filesystem::path path)
{
    const auto root = path.root_path();
    while (!path.empty() && path != root)
    {
        if (const auto vendor = usbProperty(path, "idVendor"))
            return isSonyUsbController(path, *vendor) ? path.string() : std::string{};
        path = path.parent_path();
    }
    return {};
}

} // namespace

std::vector<HapticAudioIdentity> connectedHapticAudioIdentities()
{
    namespace fs = std::filesystem;
    std::vector<HapticAudioIdentity> result;
    std::error_code error;
    for (fs::directory_iterator device("/sys/bus/usb/devices", error), end;
         !error && device != end; device.increment(error))
    {
        const auto vendor = usbProperty(device->path(), "idVendor");
        if (!vendor || !isSonyUsbController(device->path(), *vendor))
            continue;
        std::error_code resolveError;
        const auto path = fs::canonical(device->path(), resolveError);
        if (!resolveError)
            result.push_back({{}, path.string(), false});
    }
    return result;
}

LinuxSonyHid::LinuxSonyHid(int fd, bool writable, SonyHidModel model, DualSenseTransport transport, EndpointKey key)
    : _fd(fd), _writable(writable),
      _releaseLights(writable && model != SonyHidModel::DualShock4 && transport == DualSenseTransport::Bluetooth),
      _transport(transport), _key(key), _reports(model, transport), _output(model)
{}

std::unique_ptr<LinuxSonyHid> LinuxSonyHid::open(const std::string& path, EndpointKey key)
{
    auto fd = ::open(path.c_str(), O_RDWR | O_NONBLOCK | O_CLOEXEC);
    const bool writable = fd >= 0;
    if (!writable) fd = ::open(path.c_str(), O_RDONLY | O_NONBLOCK | O_CLOEXEC);
    if (fd < 0)
        return {};
    hidraw_devinfo info{};
    const auto model = ::ioctl(fd, HIDIOCGRAWINFO, &info) == 0 ?
        sonyHidModel(static_cast<std::uint16_t>(info.vendor), static_cast<std::uint16_t>(info.product)) : std::nullopt;
    if (!model || (info.bustype != BUS_USB && info.bustype != BUS_BLUETOOTH))
    {
        ::close(fd);
        return {};
    }
    const auto transport = info.bustype == BUS_USB ? DualSenseTransport::Usb : DualSenseTransport::Bluetooth;
    auto device = std::unique_ptr<LinuxSonyHid>(new LinuxSonyHid(fd, writable, *model, transport, key));
    std::error_code error;
    const auto name = std::filesystem::path(path).filename();
    device->_association = std::filesystem::canonical(std::filesystem::path("/sys/class/hidraw") / name / "device", error);
    if (error || device->_association.empty())
        return {};
    auto& descriptor = device->_descriptor;
    const bool ds4 = *model == SonyHidModel::DualShock4;
    const bool edge = *model == SonyHidModel::DualSenseEdge;
    descriptor.name = sonyHidName(*model);
    descriptor.controllerType = sonyGamepadType(*model);
    descriptor.vendor = static_cast<std::uint16_t>(info.vendor);
    descriptor.product = static_cast<std::uint16_t>(info.product);
    descriptor.link = info.bustype == BUS_USB ? Link::Wired : Link::Wireless;
    if (std::array<char, 128> serial{}; ::ioctl(device->_fd, HIDIOCGRAWUNIQ(serial.size()), serial.data()) > 0)
    {
        serial.back() = '\0';
        if (serial.front()) descriptor.serial = serial.data();
    }
    descriptor.physicalAssociation = device->_association;
    if (!ds4 && transport == DualSenseTransport::Usb)
    {
        descriptor.hapticAudio.usbPath = usbParent(device->_association);
        descriptor.hapticAudio.writable = writable;
    }
    auto& layout = descriptor.layout;
    layout.id = ds4 ? "linux-dualshock4-hid-v1" : edge ? "linux-dualsense-edge-hid-v1" : "linux-dualsense-hid-v1";
    layout.guid = DeviceGuid::make(info.bustype, *descriptor.vendor, *descriptor.product, 0, {}, descriptor.name, 'h');
    layout.legacyHidapi = true;
    configureSonyHidLayout(layout, *model, 14);
    device->_raw.buttons.resize(layout.buttonCount);
    device->_raw.axes.resize(layout.axisCount);
    device->_raw.hats.resize(layout.hatCount);
    auto& caps = descriptor.capabilities;
    caps.fingersPerPad = {2};
    if (ds4 && transport == DualSenseTransport::Usb)
    {
        std::array<std::uint8_t, 37> calibration{0x02};
        device->_reports.calibrate(readFeature(fd, calibration));
    }
    else
    {
        if (ds4)
        {
            // Reading report 0x02 requests full Bluetooth reports on an official DS4.
            std::array<std::uint8_t, 37> enable{0x02};
            readFeature(fd, enable);
        }
        else
        {
            std::array<std::uint8_t, 64> firmware{DualSenseFirmwareReportId};
            device->_output.configureRumble(*model, transport, decodeDualSenseFirmware(readFeature(fd, firmware)));
        }
        std::array<std::uint8_t, 41> calibration{0x05};
        device->_reports.calibrate(readFeature(fd, calibration));
    }
    // Official enhanced reports have nominal sensor values if calibration cannot be read.
    if (ds4 || edge || device->_reports.hasCalibration())
    {
        caps.sensors.set(static_cast<unsigned>(Sensor::Gyro));
        caps.sensors.set(static_cast<unsigned>(Sensor::Accel));
    }
    if (writable)
    {
        caps.features.set(static_cast<unsigned>(Feature::BodyRumble));
        caps.acknowledgedBodyStop = true;
        caps.features.set(static_cast<unsigned>(Feature::RgbLed));
        if (!ds4)
        {
            for (auto feature : {Feature::PlayerLights, Feature::AdaptiveLeft, Feature::AdaptiveRight})
                caps.features.set(static_cast<unsigned>(feature));
            caps.playerLightMask = 31;
            caps.triggerLimits = {TriggerLimits{true, true, 1, 255}, TriggerLimits{true, true, 1, 255}};
        }
    }
    return device;
}

LinuxSonyHid::~LinuxSonyHid()
{
    neutral();
    if (_fd >= 0)
        ::close(_fd);
}

bool LinuxSonyHid::read(ReportSink& sink, const std::function<void()>& beforeAttach)
{
    std::array<std::uint8_t, 256> buffer{};
    for (unsigned iteration = 0; iteration < 64; ++iteration)
    {
        const auto size = ::read(_fd, buffer.data(), buffer.size());
        if (size <= 0)
            return size == -1 && (errno == EAGAIN || errno == EINTR);
        const auto report = std::span(buffer).first(static_cast<std::size_t>(size));
        const auto sample = _reports.decode(report);
        if (!sample)
        {
            if (!_attached && _writable && !_enableRequested && _transport == DualSenseTransport::Bluetooth &&
                _reports.simple(report))
            {
                _enableRequested = true;
                write(_output, DualSenseOutputKind::EnableBluetooth);
            }
            continue;
        }
        if (_releaseLights)
        {
            const auto now = nowNs();
            if (_firstFull == 0) _firstFull = now;
            // DualSense must finish its Bluetooth light animation before accepting colors.
            if (_hasOutput && !_resetOutput && now >= _retryLightsAt &&
                (sample->sensorTicks >= 10200000 || now - _firstFull >= 3400000000ULL))
            {
                _retryLightsAt = now + 250000000;
                auto next = _output;
                next.expire(now);
                _releaseLights = !write(next, DualSenseOutputKind::ReleaseBluetoothLights) || !write(next);
                if (!_releaseLights)
                    _output = next;
            }
        }
        std::array<RawChange, DualSenseEdgeButtonCount + 7> changes{};
        unsigned count = 0;
        const auto update = [&](RawKind kind, auto& old, unsigned index, auto next) {
            if (old[index] != next)
            {
                old[index] = next;
                changes[count++] = {kind, index, next};
            }
        };
        for (unsigned i = 0; i < _raw.buttons.size(); ++i)
            update(RawKind::Button, _raw.buttons, i, sample->buttons[i]);
        for (unsigned i = 0; i < sample->axes.size(); ++i)
            update(RawKind::Axis, _raw.axes, i, sample->axes[i]);
        update(RawKind::Hat, _raw.hats, 0, sample->hat);
        std::optional<Power> power;
        const auto& oldPower = _descriptor.power;
        if (oldPower.state != sample->power.state || oldPower.percent != sample->power.percent)
            power = sample->power;
        if (power)
            _descriptor.power = *power;
        std::vector<Contact> touch;
        if (sample->hasTouchSample)
        {
            touch = dualSenseTouchChanges(_fingers, sample->fingers);
            _fingers = sample->fingers;
        }
        std::array<Motion, 2> motion{};
        unsigned motionCount = 0;
        for (const auto& value : sample->motion)
            if (_sensors.test(static_cast<unsigned>(value.sensor)))
                motion[motionCount++] = value;
        if (!_attached)
        {
            beforeAttach();
            _attached = true;
            sink.attached(_key, _descriptor, baseline());
            count = 0;
        }
        if (count || !touch.empty() || motionCount || power)
            sink.report(_key, {std::span(changes).first(count), touch, std::span(motion).first(motionCount), power, ++_cursor, {}});
    }
    return true;
}

AttachedEndpoint LinuxSonyHid::snapshot()
{
    if (_waveformMode)
        submit(Stop{Channel::Body});
    ++_key.generation;
    _fingers = {};
    _sensors.reset();
    return {_key, _descriptor, baseline()};
}

void LinuxSonyHid::setSensor(Sensor sensor, bool enabled)
{
    if (_descriptor.capabilities.sensors.test(static_cast<unsigned>(sensor)))
        _sensors.set(static_cast<unsigned>(sensor), enabled);
}

bool LinuxSonyHid::write(SonyHidOutput& state, DualSenseOutputKind kind)
{
    const auto bytes = state.encode(_transport, 0, kind);
    return !bytes.empty() && ::write(_fd, bytes.data(), bytes.size()) == static_cast<ssize_t>(bytes.size());
}

Error LinuxSonyHid::submit(const OutputCommand& command, const NativeBodyGate& gate)
{
    if (!_writable || !_attached)
        return Error::Unsupported;
    auto candidate = _output;
    const auto* stop = std::get_if<Stop>(&command);
    const bool stopAll = stop && stop->channel == Channel::All;
    const bool stopBody = stop && stop->channel == Channel::Body;
    if (_resetOutput && !stopAll && !stopBody)
        return Error::Busy;
    const bool allNeutral = stopAll || _resetOutput;
    const bool stopsWaveform = std::holds_alternative<Rumble>(command) ||
        stopAll || stopBody;
    if (stopsWaveform)
        candidate.setHapticsMode(false);
    if (!candidate.apply(allNeutral ? OutputCommand{Stop{}} : command, nowNs(), gate))
        return bodyGateOpen(gate) ? Error::Unsupported : Error::Busy;
    if (!write(candidate))
        return Error::BackendFailure;
    _output = candidate;
    _hasOutput = !allNeutral;
    _resetOutput = false;
    if (stopsWaveform)
        _waveformMode = false;
    return Error::None;
}

Error LinuxSonyHid::startWaveform()
{
    if (!_attached || !_writable || _descriptor.hapticAudio.usbPath.empty())
        return Error::Unsupported;
    if (_resetOutput)
        return Error::Busy;
    auto next = _output;
    if (!next.setHapticsMode(true) || !write(next))
        return Error::BackendFailure;
    _output = next;
    _hasOutput = true;
    _waveformMode = true;
    return Error::None;
}

void LinuxSonyHid::neutral()
{
    if (_hasOutput)
        _resetOutput = submit(Stop{}) != Error::None;
    _fingers = {};
}


void LinuxSonyHid::tick(std::uint64_t now, bool)
{
    if (_resetOutput)
    {
        neutral();
        return;
    }
    auto candidate = _output;
    if (candidate.expire(now) && write(candidate))
        _output = candidate;
}

} // namespace cc::input::detail
