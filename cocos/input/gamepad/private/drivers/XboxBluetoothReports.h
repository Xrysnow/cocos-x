#pragma once

#include "../GamepadBackend.h"

namespace cc::input::detail {

enum class XboxBluetoothModel { OneS, Series, Elite2 };
std::optional<XboxBluetoothModel> xboxBluetoothModel(unsigned vendor, unsigned product);
bool isMicrosoftXboxGamepad(unsigned vendor, unsigned product);
const char* xboxBluetoothName(XboxBluetoothModel model);
void configureXboxBluetoothLayout(RawLayout& layout, XboxBluetoothModel model);
bool xboxBluetoothHasRumbleOutput(std::span<const std::uint8_t> hidDescriptor);

struct XboxBluetoothControls {
    // Indexed by Button and Axis. Guide and the hat have separate fields.
    std::array<std::uint8_t, 20> buttons{};
    std::array<std::int16_t, AxisCount> axes{};
    std::uint8_t hat = 0;
    bool hasPaddles = false;
};

struct XboxBluetoothInput {
    std::optional<XboxBluetoothControls> controls;
    std::optional<bool> guide;
    std::optional<Power> power;
};

class XboxBluetoothReports {
public:
    explicit XboxBluetoothReports(XboxBluetoothModel model) : _model(model) {}

    std::optional<XboxBluetoothInput> decode(std::span<const std::uint8_t> bytes);

private:
    XboxBluetoothModel _model;
    bool _separateGuide = false;
};

struct XboxRumbleMotors {
    float low = 0;
    float high = 0;
    float left = 0;
    float right = 0;
};

inline constexpr unsigned XboxBluetoothOutputSize = 9;
inline constexpr std::uint64_t XboxBluetoothRumbleIntervalNs = 50'000'000;

class XboxRumbleState {
public:
    bool apply(const OutputCommand& command, std::uint64_t nowNs);
    bool expire(std::uint64_t nowNs);
    XboxRumbleMotors motors() const;
    std::optional<std::uint64_t> deadline() const;
    bool active() const;
    std::array<std::uint8_t, XboxBluetoothOutputSize> bluetoothReport() const;

private:
    struct Pair {
        float first = 0;
        float second = 0;
        std::optional<std::uint64_t> deadline;

        void set(float first, float second, std::chrono::milliseconds duration, std::uint64_t nowNs);
        bool expire(std::uint64_t nowNs);
    };

    Pair _body;
    Pair _triggers;
};

} // namespace cc::input::detail
