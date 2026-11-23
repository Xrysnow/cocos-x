#pragma once

#include "platform/PlatformDefine.h"

#include <array>
#include <bitset>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace cc::input {

class CC_DLL GamepadService;
namespace detail {
class DeviceRegistry;
class FrameBuilder;
}

enum class DeviceId : std::uint32_t {};
enum class CommandId : std::uint32_t {};

enum class Button : std::uint8_t {
    South, East, West, North, Back, Guide, Start, LeftStick, RightStick,
    LeftShoulder, RightShoulder, DpadUp, DpadDown, DpadLeft, DpadRight,
    Misc1, RightPaddle1, LeftPaddle1, RightPaddle2, LeftPaddle2, TouchpadClick,
    Misc2, Misc3, Misc4, Misc5, Misc6
};

enum class Axis { LeftX, LeftY, RightX, RightY, LeftTrigger, RightTrigger };
enum class Sensor { Accel, Gyro, AccelLeft, GyroLeft, AccelRight, GyroRight };
enum class Side { Left, Right };
enum class Feature {
    BodyRumble, TriggerRumble, MonoLed, RgbLed, PlayerLights, AdaptiveLeft, AdaptiveRight, BodyHaptics
};
enum class Reason {
    Physical, Connect, Disconnect, FocusLost, FocusGained, Remap, Resync, Configuration, Command
};
enum class Error {
    None, Unsupported, Disconnected, Busy, PermissionDenied, InvalidArgument,
    NoMapping, BackendFailure, QueueFull, StaleFrame
};
enum class TimeQuality { ReceiveOnly, ConvertedOS, CalibratedDevice };
enum class GamepadType : std::uint8_t {
    Unknown, XboxCompatible, DualShock4, DualSense, DualSenseEdge,
    SwitchPro, JoyConLeft, JoyConRight, JoyConPair
};

inline constexpr unsigned ButtonCount = static_cast<unsigned>(Button::Misc6) + 1;
inline constexpr unsigned AxisCount = static_cast<unsigned>(Axis::RightTrigger) + 1;
inline constexpr unsigned SensorCount = static_cast<unsigned>(Sensor::GyroRight) + 1;
inline constexpr unsigned FeatureCount = static_cast<unsigned>(Feature::BodyHaptics) + 1;

template<class T>
struct Result {
    std::optional<T> value;
    Error error = Error::None;
    explicit operator bool() const noexcept { return value.has_value(); }
};

struct DeviceInfo {
    DeviceId id{};
    std::string name;
    std::string mappingGuid;
    std::string layout;
    std::string mappingName;
    std::optional<std::uint16_t> vendor;
    std::optional<std::uint16_t> product;
    std::optional<std::uint16_t> version;
    std::optional<std::string> serial;
    GamepadType controllerType = GamepadType::Unknown; // Reported by the primary input endpoint.
};

struct TriggerLimits {
    bool resistance = false;
    bool vibration = false;
    float minHz = 0;
    float maxHz = 0;
    bool operator==(const TriggerLimits&) const = default;
};

class CC_DLL Capabilities {
public:
    bool has(Button) const noexcept;
    bool has(Axis) const noexcept;
    bool has(Sensor) const noexcept;
    bool has(Feature) const noexcept;
    std::span<const unsigned> fingersPerPad() const noexcept;
    std::optional<float> nominalHz(Sensor) const noexcept;
    std::optional<TriggerLimits> triggerLimits(Side) const noexcept;
    std::uint32_t playerLightMask() const noexcept;

private:
    friend class detail::DeviceRegistry;
    friend class detail::FrameBuilder;
    friend class GamepadService;

    std::bitset<ButtonCount> _buttons;
    std::bitset<AxisCount> _axes;
    std::bitset<SensorCount> _sensors;
    std::bitset<FeatureCount> _features;
    std::vector<unsigned> _fingersPerPad;
    std::array<std::optional<float>, SensorCount> _nominalHz{};
    std::array<std::optional<TriggerLimits>, 2> _triggerLimits{};
    std::uint32_t _playerLightMask = 0;
};

enum class ContactPhase { Down, Move, Up, Cancel };
struct Contact {
    unsigned pad = 0;
    unsigned finger = 0;
    ContactPhase phase = ContactPhase::Down;
    float x = 0;
    float y = 0;
    std::optional<float> pressure;
};

struct Motion {
    Sensor sensor = Sensor::Accel;
    std::array<float, 3> xyz{};
    std::optional<std::uint64_t> deviceTimeNs;
};

enum class PowerState { Unknown, OnBattery, Charging, Charged, External };
struct Power {
    using State = PowerState;
    State state = State::Unknown;
    std::optional<unsigned> percent;
    std::optional<unsigned> level;  // 0..3 for devices that report a coarse level.
};

enum class Link { Unknown, Wired, Wireless };

} // namespace cc::input
