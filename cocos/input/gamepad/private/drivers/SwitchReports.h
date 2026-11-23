#pragma once

#include "../GamepadBackend.h"

namespace cc::input::detail {

enum class SwitchModel : std::uint8_t { JoyConLeft = 1, JoyConRight = 2, Pro = 3 };
std::optional<SwitchModel> switchModel(unsigned vendor, unsigned product);
const char* switchName(SwitchModel model);
GamepadType switchGamepadType(SwitchModel model);
void configureSwitchLayout(RawLayout& layout, SwitchModel model);

struct SwitchInput {
    std::array<std::uint8_t, 20> buttons{};
    std::array<std::int16_t, 6> axes{};
    std::uint8_t hat = 0;
    std::optional<Power> power;
    std::array<Motion, 6> motion{};
    unsigned motionCount = 0;
};

inline constexpr std::uint16_t SwitchFactorySticks = 0x603d, SwitchUserSticks = 0x8010;
inline constexpr std::uint16_t SwitchFactoryImu = 0x6020, SwitchUserImu = 0x8026;

class SwitchReports {
public:
    explicit SwitchReports(SwitchModel model) : _model(model) {}

    std::optional<SwitchInput> decode(std::span<const std::uint8_t> packet, bool motion);
    void calibrate(std::uint16_t address, std::span<const std::uint8_t> data);

private:
    struct StickAxis {
        int center = 2048, negative = 1003, positive = 1003;
        std::int16_t scale(int value, bool inverted);
    };

    SwitchModel _model;
    std::array<StickAxis, 4> _stick;
    std::array<StickAxis, 4> _simple{{{32768, 16384, 16383}, {32768, 16384, 16383},
                                     {32768, 16384, 16383}, {32768, 16384, 16383}}};
    std::bitset<2> _userStick;
    std::array<int, 6> _imuOrigin{};
    std::array<float, 6> _imuScale{9.80665f / 4096, 9.80665f / 4096, 9.80665f / 4096,
                                   0.01745329252f / 14.2842f, 0.01745329252f / 14.2842f,
                                   0.01745329252f / 14.2842f};
    bool _factoryImu = false;
};

using SwitchPacket = std::array<std::uint8_t, 64>;
using SwitchMotors = std::array<std::uint8_t, 8>;
inline constexpr SwitchMotors SwitchNeutralRumble{0, 1, 0x40, 0x40, 0, 1, 0x40, 0x40};
SwitchMotors encodeSwitchRumble(SwitchModel model, float low, float high);

struct SwitchRequest {
    std::uint8_t id;
    bool usb = false;
    std::array<std::uint8_t, 5> data{};
    unsigned size = 0;

    static SwitchRequest spi(std::uint16_t address, std::uint8_t length);
    std::optional<std::span<const std::uint8_t>> reply(std::span<const std::uint8_t> packet) const;
};

class SwitchOutput {
public:
    SwitchPacket usb(std::uint8_t command) const;
    SwitchPacket subcommand(const SwitchRequest& request, const SwitchMotors& motors);
    SwitchPacket rumble(const SwitchMotors& motors);

private:
    SwitchPacket motorPacket(std::uint8_t report, const SwitchMotors& motors);
    std::uint8_t _sequence = 0;
};

} // namespace cc::input::detail
