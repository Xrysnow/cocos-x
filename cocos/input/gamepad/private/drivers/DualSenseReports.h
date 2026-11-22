#pragma once

#include "../GamepadBackend.h"

namespace cc::input::detail {

enum class DualSenseModel { Standard, Edge };
enum class DualSenseTransport { Usb, Bluetooth };
enum class DualSenseOutputKind { Effects, EnableBluetooth, ReleaseBluetoothLights };

inline constexpr unsigned DualSenseBaseButtonCount = 15;
inline constexpr unsigned DualSenseEdgeButtonCount = 19;
inline constexpr std::uint8_t DualSenseFirmwareReportId = 0x20;

std::optional<DualSenseModel> dualSenseModel(unsigned vendor, unsigned product);
std::optional<std::uint16_t> decodeDualSenseFirmware(std::span<const std::uint8_t> packet);

struct DualSenseCalibration {
    std::array<float, 6> bias{};
    std::array<float, 6> scale{};
};

struct DualSenseControls {
    // The first 15 indices are shared with the standard model. Edge appends
    // left Fn, right Fn, left rear and right rear in that order.
    std::array<std::uint8_t, DualSenseEdgeButtonCount> buttons{};
    std::array<std::int16_t, 6> axes{};
    std::uint8_t hat = 0;
};

struct DualSenseInput : DualSenseControls {
    std::array<std::optional<Contact>, 2> fingers{};
    std::array<Motion, 2> motion{};
    Power power;
    std::uint32_t sensorTicks = 0;
};

std::optional<DualSenseCalibration> decodeDualSenseCalibration(DualSenseTransport transport,
                                                                std::span<const std::uint8_t> packet);
std::optional<DualSenseInput> decodeDualSenseInput(DualSenseTransport transport,
                                                  std::span<const std::uint8_t> packet,
                                                  const std::optional<DualSenseCalibration>& calibration,
                                                  DualSenseModel model = DualSenseModel::Standard);
std::optional<DualSenseControls> decodeDualSenseBluetoothSimple(std::span<const std::uint8_t> packet);
std::vector<Contact> dualSenseTouchChanges(const std::array<std::optional<Contact>, 2>& old,
                                           const std::array<std::optional<Contact>, 2>& next);

class DualSenseOutput {
public:
    void configureRumble(DualSenseModel model, DualSenseTransport transport,
                         std::optional<std::uint16_t> firmwareVersion);

    // Supply this monotonic time when accepting a command and when checking expiry.
    bool apply(const OutputCommand& command, std::uint64_t now);
    bool expire(std::uint64_t now);
    bool hasTimedRumble() const noexcept { return _expires.has_value(); }
    std::span<const std::uint8_t> encode(DualSenseTransport transport, unsigned usbLength = 63,
                                         DualSenseOutputKind kind = DualSenseOutputKind::Effects);

private:
    std::array<std::uint8_t, 78> _packet{};
    std::array<AdaptiveTrigger, 2> _triggers{};
    Rgb _rgb{};
    PlayerLights _lights{};
    std::uint8_t _low = 0, _high = 0, _sequence = 0;
    bool _enhancedRumble = false;
    std::optional<std::uint64_t> _expires;
};

} // namespace cc::input::detail
