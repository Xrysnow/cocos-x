#pragma once

#include "../drivers/XboxBluetoothReports.h"

#include <filesystem>
#include <memory>

namespace cc::input::detail {

// An Xbox Bluetooth hidraw interface associated with an existing evdev gamepad.
// It supplies battery updates and may own the four vibration motors.
class LinuxXboxBluetooth {
public:
    static std::unique_ptr<LinuxXboxBluetooth> open(const std::filesystem::path& hidParent,
                                                    unsigned vendor, unsigned product);
    ~LinuxXboxBluetooth();

    int fd() const { return _fd; }
    bool present() const;
    bool read();
    const std::optional<Power>& power() const { return _power; }

    bool canProbeOutput() const { return _validInput && _outputCandidate && !_outputReady; }
    void probeOutput(bool canClaimOutput);
    bool outputReady() const { return _outputReady; }
    std::optional<std::uint64_t> nextDeadline() const { return _rumble.deadline(); }
    Error submit(const OutputCommand& command, std::uint64_t now);
    void tick(std::uint64_t now);
    void neutral();

private:
    LinuxXboxBluetooth(int fd, std::filesystem::path path, XboxBluetoothModel model, bool outputCandidate);
    bool write(const XboxRumbleState& next) const;
    bool apply(const XboxRumbleState& next);

    int _fd;
    std::filesystem::path _path;
    XboxBluetoothReports _reports;
    XboxRumbleState _rumble;
    std::optional<Power> _power;
    bool _validInput = false;
    bool _outputCandidate;
    bool _outputReady = false;
};

} // namespace cc::input::detail
