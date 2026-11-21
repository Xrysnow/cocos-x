#pragma once

#include "../GamepadBackend.h"

namespace cc::input::detail {

enum class DualSenseTransport { Usb, Bluetooth };

struct DualSenseCalibration {
    std::array<float, 6> bias{};
    std::array<float, 6> scale{};
};

struct DualSenseInput {
    std::array<std::uint8_t, 14> buttons{};
    std::array<std::int16_t, 6> axes{};
    std::uint8_t hat = 0;
    std::array<std::optional<Contact>, 2> fingers{};
    std::array<Motion, 2> motion{};
    Power power;
};

std::optional<DualSenseCalibration> decodeDualSenseCalibration(DualSenseTransport transport,
                                                                std::span<const std::uint8_t> packet);
std::optional<DualSenseInput> decodeDualSenseInput(DualSenseTransport transport,
                                                  std::span<const std::uint8_t> packet,
                                                  const std::optional<DualSenseCalibration>& calibration);
std::vector<Contact> dualSenseTouchChanges(const std::array<std::optional<Contact>, 2>& old,
                                           const std::array<std::optional<Contact>, 2>& next);

class DualSenseOutput {
public:
    // Supply this monotonic time when accepting a command and when checking expiry.
    bool apply(const OutputCommand& command, std::uint64_t now);
    bool expire(std::uint64_t now);
    bool hasTimedRumble() const noexcept { return _expires.has_value(); }
    std::span<const std::uint8_t> encode(DualSenseTransport transport, unsigned usbLength = 63);

private:
    std::array<std::uint8_t, 78> _packet{};
    std::array<AdaptiveTrigger, 2> _triggers{};
    Rgb _rgb{};
    PlayerLights _lights{};
    std::uint8_t _low = 0, _high = 0, _sequence = 0;
    std::optional<std::uint64_t> _expires;
};

} // namespace cc::input::detail
