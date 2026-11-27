#include "LinuxXboxBluetooth.h"

#include <fcntl.h>
#include <linux/hidraw.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cerrno>
#include <utility>

namespace cc::input::detail {
namespace {

bool hasRumbleReport(int fd)
{
    int length = 0;
    hidraw_report_descriptor descriptor{};
    if (::ioctl(fd, HIDIOCGRDESCSIZE, &length) != 0 || length <= 0 ||
        static_cast<unsigned>(length) > sizeof(descriptor.value))
        return false;
    descriptor.size = static_cast<__u32>(length);
    return ::ioctl(fd, HIDIOCGRDESC, &descriptor) == 0 && descriptor.size > 0 &&
           descriptor.size <= sizeof(descriptor.value) &&
           xboxBluetoothHasRumbleOutput(std::span(descriptor.value).first(descriptor.size));
}

} // namespace

std::unique_ptr<LinuxXboxBluetooth> LinuxXboxBluetooth::open(const std::filesystem::path& hidParent,
                                                           unsigned vendor, unsigned product)
{
    const auto model = xboxBluetoothModel(vendor, product);
    if (!model || hidParent.empty())
        return {};

    std::unique_ptr<LinuxXboxBluetooth> selected;
    std::error_code error;
    for (std::filesystem::directory_iterator it(hidParent / "hidraw", error), end;
         !error && it != end; it.increment(error))
    {
        const auto node = it->path().filename();
        if (!node.native().starts_with("hidraw"))
            continue;
        const auto path = std::filesystem::path("/dev") / node;
        auto fd = ::open(path.c_str(), O_RDWR | O_CLOEXEC | O_NONBLOCK);
        const bool writable = fd >= 0;
        if (!writable)
            fd = ::open(path.c_str(), O_RDONLY | O_CLOEXEC | O_NONBLOCK);
        if (fd < 0)
            continue;
        hidraw_devinfo info{};
        std::error_code nodeError;
        const auto parent = std::filesystem::canonical(std::filesystem::path("/sys/class/hidraw") /
                                                      node / "device", nodeError);
        if (nodeError || parent != hidParent || ::ioctl(fd, HIDIOCGRAWINFO, &info) != 0 ||
            info.bustype != BUS_BLUETOOTH || static_cast<std::uint16_t>(info.vendor) != vendor ||
            static_cast<std::uint16_t>(info.product) != product)
        {
            ::close(fd);
            continue;
        }
        auto candidate = std::unique_ptr<LinuxXboxBluetooth>(
            new LinuxXboxBluetooth(fd, path, *model, writable && hasRumbleReport(fd)));
        if (!candidate->present())
            continue;
        if (selected)
            return {};
        selected = std::move(candidate);
    }
    return selected;
}

LinuxXboxBluetooth::LinuxXboxBluetooth(int fd, std::filesystem::path path, XboxBluetoothModel model,
                                       bool outputCandidate)
    : _fd(fd), _path(std::move(path)), _reports(model), _outputCandidate(outputCandidate)
{
}

LinuxXboxBluetooth::~LinuxXboxBluetooth()
{
    neutral();
    ::close(_fd);
}

bool LinuxXboxBluetooth::present() const
{
    struct stat handle{}, path{};
    return ::fstat(_fd, &handle) == 0 && ::stat(_path.c_str(), &path) == 0 &&
           handle.st_ino == path.st_ino && handle.st_rdev == path.st_rdev;
}

bool LinuxXboxBluetooth::read()
{
    std::array<std::uint8_t, 256> bytes{};
    for (unsigned i = 0; i < 64; ++i)
    {
        const auto count = ::read(_fd, bytes.data(), bytes.size());
        if (count <= 0)
            return count < 0 && (errno == EAGAIN || errno == EINTR);
        if (const auto decoded = _reports.decode(std::span(bytes).first(static_cast<std::size_t>(count))))
        {
            _validInput |= decoded->controls.has_value();
            if (decoded->power)
                _power = decoded->power;
        }
    }
    return true;
}

bool LinuxXboxBluetooth::write(const XboxRumbleState& next) const
{
    const auto report = next.bluetoothReport();
    ssize_t count;
    do
        count = ::write(_fd, report.data(), report.size());
    while (count < 0 && errno == EINTR);
    return count == static_cast<ssize_t>(report.size());
}

void LinuxXboxBluetooth::probeOutput(bool canClaimOutput)
{
    if (canProbeOutput())
    {
        _outputReady = canClaimOutput && write(_rumble);
        _outputCandidate = _outputReady;
    }
}

bool LinuxXboxBluetooth::apply(const XboxRumbleState& next)
{
    if (!write(next))
    {
        neutral();
        _outputCandidate = _outputReady = false;
        return false;
    }
    _rumble = next;
    return true;
}

Error LinuxXboxBluetooth::submit(const OutputCommand& command, std::uint64_t now, const NativeBodyGate& gate)
{
    if (!_outputReady)
        return Error::Unsupported;
    auto next = _rumble;
    if (!next.apply(command, now, gate))
        return bodyGateOpen(gate) ? Error::Unsupported : Error::Busy;
    return apply(next) ? Error::None : Error::BackendFailure;
}

void LinuxXboxBluetooth::tick(std::uint64_t now)
{
    if (!_outputReady || !_rumble.active())
        return;
    auto next = _rumble;
    if (next.expire(now))
        apply(next);
}

void LinuxXboxBluetooth::neutral()
{
    if (!_rumble.active())
        return;
    _rumble = {};
    if (!write(_rumble))
        _outputCandidate = _outputReady = false;
}

} // namespace cc::input::detail
