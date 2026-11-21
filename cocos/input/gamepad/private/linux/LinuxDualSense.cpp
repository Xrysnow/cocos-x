#include "LinuxDualSense.h"

#include <linux/hidraw.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <filesystem>

namespace cc::input::detail {

std::unique_ptr<LinuxDualSense> LinuxDualSense::open(const std::string& path, EndpointKey key)
{
    auto device = std::unique_ptr<LinuxDualSense>(new LinuxDualSense);
    device->_fd = ::open(path.c_str(), O_RDWR | O_NONBLOCK | O_CLOEXEC);
    device->_writable = device->_fd >= 0;
    if (!device->_writable)
        device->_fd = ::open(path.c_str(), O_RDONLY | O_NONBLOCK | O_CLOEXEC);
    if (device->_fd < 0)
        return {};
    hidraw_devinfo info{};
    if (::ioctl(device->_fd, HIDIOCGRAWINFO, &info) != 0 || info.vendor != 0x054c || info.product != 0x0ce6 ||
        (info.bustype != BUS_USB && info.bustype != BUS_BLUETOOTH))
        return {};
    std::error_code error;
    const auto name = std::filesystem::path(path).filename();
    device->_association = std::filesystem::canonical(std::filesystem::path("/sys/class/hidraw") / name / "device", error);
    if (error || device->_association.empty())
        return {};
    device->_transport = info.bustype == BUS_USB ? DualSenseTransport::Usb : DualSenseTransport::Bluetooth;
    device->_key = key;
    auto& descriptor = device->_descriptor;
    descriptor.name = "DualSense Wireless Controller";
    descriptor.vendor = 0x054c;
    descriptor.product = 0x0ce6;
    descriptor.link = info.bustype == BUS_USB ? Link::Wired : Link::Wireless;
    if (std::array<char, 128> serial{}; ::ioctl(device->_fd, HIDIOCGRAWUNIQ(serial.size()), serial.data()) > 0)
    {
        serial.back() = '\0';
        if (serial.front()) descriptor.serial = serial.data();
    }
    descriptor.physicalAssociation = device->_association;
    auto& layout = descriptor.layout;
    layout.id = "linux-dualsense-hid-v1";
    layout.guid = DeviceGuid::make(info.bustype, *descriptor.vendor, *descriptor.product, 0, {}, descriptor.name, 'h');
    layout.legacyHidapi = true;
    layout.buttonCount = 14;
    layout.axisCount = 6;
    layout.hatCount = 1;
    layout.builtInMapping =
        "a:b0,b:b1,x:b2,y:b3,back:b4,guide:b5,start:b6,leftstick:b7,rightstick:b8,"
        "leftshoulder:b9,rightshoulder:b10,touchpad:b11,misc1:b12,"
        "leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:a4,righttrigger:a5,"
        "dpup:h0.1,dpright:h0.2,dpdown:h0.4,dpleft:h0.8,face:sony";
    device->_raw.buttons.resize(layout.buttonCount);
    device->_raw.axes.resize(layout.axisCount);
    device->_raw.hats.resize(layout.hatCount);
    auto& caps = descriptor.capabilities;
    caps.fingersPerPad = {2};
    std::array<std::uint8_t, 41> calibration{0x05};
    if (::ioctl(device->_fd, HIDIOCGFEATURE(calibration.size()), calibration.data()) == static_cast<int>(calibration.size()))
        device->_calibration = decodeDualSenseCalibration(device->_transport, calibration);
    // Report nominal timing and touch even when a transport refuses feature reads.
    if (device->_calibration)
    {
        caps.sensors.set(static_cast<unsigned>(Sensor::Gyro));
        caps.sensors.set(static_cast<unsigned>(Sensor::Accel));
    }
    if (device->_writable)
    {
        for (auto feature : {Feature::BodyRumble, Feature::RgbLed, Feature::PlayerLights, Feature::AdaptiveLeft, Feature::AdaptiveRight})
            caps.features.set(static_cast<unsigned>(feature));
        caps.playerLightMask = 31;
        caps.triggerLimits = {TriggerLimits{true, true, 1, 255}, TriggerLimits{true, true, 1, 255}};
    }
    return device;
}

LinuxDualSense::~LinuxDualSense()
{
    neutral();
    if (_fd >= 0)
        ::close(_fd);
}

bool LinuxDualSense::read(ReportSink& sink)
{
    std::array<std::uint8_t, 256> buffer{};
    for (unsigned iteration = 0; iteration < 64; ++iteration)
    {
        const auto size = ::read(_fd, buffer.data(), buffer.size());
        if (size <= 0)
            return size == -1 && (errno == EAGAIN || errno == EINTR);
        const auto sample = decodeDualSenseInput(_transport, std::span(buffer).first(static_cast<std::size_t>(size)), _calibration);
        if (!sample)
            continue;
        std::array<RawChange, 21> changes{};
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
        const auto touch = dualSenseTouchChanges(_fingers, sample->fingers);
        _fingers = sample->fingers;
        std::array<Motion, 2> motion{};
        unsigned motionCount = 0;
        for (const auto& value : sample->motion)
            if (_sensors.test(static_cast<unsigned>(value.sensor)))
                motion[motionCount++] = value;
        if (!_attached)
        {
            _attached = true;
            sink.attached(_key, _descriptor, baseline());
            count = 0;
        }
        if (count || !touch.empty() || motionCount || power)
            sink.report(_key, {std::span(changes).first(count), touch, std::span(motion).first(motionCount), power, ++_cursor, {}});
    }
    return true;
}

AttachedEndpoint LinuxDualSense::snapshot()
{
    ++_key.generation;
    _fingers = {};
    _sensors.reset();
    return {_key, _descriptor, baseline()};
}

void LinuxDualSense::setSensor(Sensor sensor, bool enabled)
{
    if (_descriptor.capabilities.sensors.test(static_cast<unsigned>(sensor)))
        _sensors.set(static_cast<unsigned>(sensor), enabled);
}

bool LinuxDualSense::write(DualSenseOutput& state)
{
    const auto bytes = state.encode(_transport);
    return ::write(_fd, bytes.data(), bytes.size()) == static_cast<ssize_t>(bytes.size());
}

Error LinuxDualSense::submit(const OutputCommand& command)
{
    if (!_writable || !_attached)
        return Error::Unsupported;
    auto candidate = _output;
    if (!candidate.apply(command, nowNs()))
        return Error::Unsupported;
    if (!write(candidate))
        return Error::BackendFailure;
    _output = candidate;
    _hasOutput = true;
    if (const auto* rumble = std::get_if<Rumble>(&command))
        _timed = rumble->duration.count() > 0 && (rumble->low > 0 || rumble->high > 0);
    else if (const auto* stop = std::get_if<Stop>(&command); stop && (stop->channel == Channel::All || stop->channel == Channel::Body))
        _timed = false;
    return Error::None;
}

void LinuxDualSense::neutral()
{
    if (_hasOutput)
    {
        _output.apply(Stop{}, nowNs());
        write(_output);
        _hasOutput = false;
        _timed = false;
    }
    _fingers = {};
}

void LinuxDualSense::expire(std::uint64_t now)
{
    auto candidate = _output;
    if (_timed && candidate.expire(now) && write(candidate))
    {
        _output = candidate;
        _timed = false;
    }
}

} // namespace cc::input::detail
