#pragma once

#include "DualSenseReports.h"

namespace cc::input::detail {

enum class DualShock4Transport { Usb, Bluetooth, WirelessAdapter };

struct DualShock4Input : DualSenseInput {
    bool hasTouchSample = false; // A report with no samples leaves current contacts intact.
};

bool isDualShock4Product(std::uint16_t vendor, std::uint16_t product) noexcept;
std::optional<DualSenseCalibration> decodeDualShock4Calibration(DualShock4Transport transport,
                                                               std::span<const std::uint8_t> packet);
std::optional<DualShock4Input> decodeDualShock4Input(DualShock4Transport transport,
                                                   std::span<const std::uint8_t> packet,
                                                   const std::optional<DualSenseCalibration>& calibration);
std::optional<DualSenseControls> decodeDualShock4Simple(DualShock4Transport transport,
                                                       std::span<const std::uint8_t> packet);

class DualShock4SensorClock {
public:
    // Sample each full report so the 16-bit counter can be unwrapped.
    std::uint64_t sampleTimeNs(std::uint16_t ticks);
    void reset() noexcept;

private:
    std::optional<std::uint16_t> _lastTick;
    std::uint64_t _ticks = 0;
};

class DualShock4Output {
public:
    bool apply(const OutputCommand& command, std::uint64_t now, bool cancelBody = false);
    bool expire(std::uint64_t now, bool cancelBody = false);
    bool hasTimedRumble() const noexcept { return _expires.has_value(); }
    std::span<const std::uint8_t> encode(DualShock4Transport transport, unsigned usbLength = 32,
                                         bool enableOnly = false);

private:
    std::array<std::uint8_t, 78> _packet{};
    Rgb _rgb{};
    std::uint8_t _low = 0, _high = 0, _effectFlags = 0;
    std::optional<std::uint64_t> _expires;
};

} // namespace cc::input::detail
