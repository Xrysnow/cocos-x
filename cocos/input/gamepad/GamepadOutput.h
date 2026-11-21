#pragma once

#include "input/gamepad/GamepadTypes.h"

#include <chrono>
#include <variant>

namespace cc::input {

struct Rumble {
    float low = 0;
    float high = 0;
    std::chrono::milliseconds duration{};
};

struct TriggerRumble {
    float left = 0;
    float right = 0;
    std::chrono::milliseconds duration{};
};

struct Rgb {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
};

struct PlayerLights { std::uint32_t mask = 0; };

enum class TriggerMode { Off, Resistance, Vibration };
struct AdaptiveTrigger {
    Side side = Side::Left;
    TriggerMode mode = TriggerMode::Off;
    float start = 0;
    float strength = 0;
    float hz = 0;
};

enum class Channel { All, Body, Triggers, AdaptiveLeft, AdaptiveRight, Lights };
struct Stop { Channel channel = Channel::All; };

using OutputCommand = std::variant<Rumble, TriggerRumble, Rgb, PlayerLights, AdaptiveTrigger, Stop>;

enum class Completion { Applied, Superseded, Cancelled, Failed };
struct OutputDone {
    CommandId command{};
    Completion status = Completion::Failed;
    Error error = Error::None;
};

} // namespace cc::input
