#include "EvdevGamepadLayout.h"

#include <numbers>
#include <string_view>

namespace cc::input::detail {

bool evdevDigitalHat(const input_absinfo* x, const input_absinfo* y)
{
    if (!x && !y) return false;
    const auto threeStates = [](const input_absinfo* range) {
        return !range || (range->minimum == -1 && range->maximum == 1);
    };
    const auto uncalibrated = [](const input_absinfo* range) {
        return !range || (!range->fuzz && !range->flat && !range->resolution);
    };
    return (threeStates(x) && threeStates(y)) || (uncalibrated(x) && uncalibrated(y));
}

float evdevMotionScale(Sensor sensor, int resolution)
{
    if (resolution <= 0) return 0;
    const auto units = sensor == Sensor::Accel ? 9.80665f : std::numbers::pi_v<float> / 180.f;
    return units / static_cast<float>(resolution);
}

std::array<float, 3> evdevMotionCoordinates(std::uint16_t vendor, const std::array<float, 3>& values)
{
    // Match the engine coordinates for the hid-nintendo driver.
    return vendor == 0x057e ? std::array{-values[1], values[2], -values[0]} : values;
}

std::string evdevGamepadMapping(std::uint16_t vendor, bool xpad,
    const std::map<unsigned, unsigned>& buttons, const std::map<unsigned, unsigned>& axes,
    const std::map<unsigned, unsigned>& hats, const std::map<unsigned, input_absinfo>& ranges)
{
    if (!buttons.contains(BTN_GAMEPAD))
        return {};

    std::string mapping;
    const auto bind = [&](std::string_view output, std::string input) {
        mapping += output;
        mapping += ':';
        mapping += input;
        mapping += ',';
    };
    const auto button = [&](unsigned code, std::string_view output) {
        const auto index = buttons.find(code);
        if (index == buttons.end()) return false;
        bind(output, "b" + std::to_string(index->second));
        return true;
    };
    const auto hasAxis = [&](unsigned code) {
        const auto range = ranges.find(code);
        return axes.contains(code) && range != ranges.end() && range->second.minimum < range->second.maximum;
    };
    const auto axis = [&](unsigned code, std::string_view output, std::string_view sign = "") {
        if (!hasAxis(code)) return false;
        bind(output, std::string(sign) + 'a' + std::to_string(axes.at(code)));
        return true;
    };
    const auto hat = [&](unsigned code, unsigned direction, std::string_view output) {
        const auto index = hats.find(code & ~1u);
        if (index == hats.end() || !ranges.contains(code)) return false;
        bind(output, "h" + std::to_string(index->second) + '.' + std::to_string(direction));
        return true;
    };

    constexpr std::pair<unsigned, std::string_view> controls[]{
        {BTN_SOUTH, "a"}, {BTN_EAST, "b"}, {BTN_SELECT, "back"}, {BTN_START, "start"},
        {BTN_MODE, "guide"}, {BTN_THUMBL, "leftstick"}, {BTN_THUMBR, "rightstick"}, {KEY_RECORD, "misc1"},
    };
    for (const auto& [code, output] : controls)
        button(code, output);
    const bool xbox = xpad || vendor == 0x045e;
    button(xbox ? BTN_X : BTN_WEST, "x");
    button(xbox ? BTN_Y : BTN_NORTH, "y");

    const auto shoulder = [&](std::string_view output, unsigned key, unsigned code, unsigned direction) {
        if (!button(key, output) && !hat(code, direction, output))
            axis(code, output);
    };
    shoulder("leftshoulder", BTN_TL, ABS_HAT1Y, 4);
    shoulder("rightshoulder", BTN_TR, ABS_HAT1X, 2);

    const bool separateTriggers = (hasAxis(ABS_HAT2Y) || hasAxis(ABS_BRAKE)) &&
                                  (hasAxis(ABS_HAT2X) || hasAxis(ABS_GAS));
    const bool rightOnZ = separateTriggers && !(hasAxis(ABS_RX) && hasAxis(ABS_RY)) && hasAxis(ABS_Z) && hasAxis(ABS_RZ);
    axis(ABS_X, "leftx");
    axis(ABS_Y, "lefty");
    axis(rightOnZ ? ABS_Z : ABS_RX, "rightx");
    axis(rightOnZ ? ABS_RZ : ABS_RY, "righty");
    const auto trigger = [&](std::string_view output, unsigned code, unsigned direction,
                             unsigned pedal, unsigned legacy, unsigned digital) {
        if (!axis(code, output) && !axis(pedal, output) && (rightOnZ || !axis(legacy, output)) &&
            !hat(code, direction, output))
            button(digital, output);
    };
    trigger("lefttrigger", ABS_HAT2Y, 4, ABS_BRAKE, ABS_Z, BTN_TL2);
    trigger("righttrigger", ABS_HAT2X, 2, ABS_GAS, ABS_RZ, BTN_TR2);

    const bool xpadDpad = xpad && buttons.contains(BTN_TRIGGER_HAPPY1) && buttons.contains(BTN_TRIGGER_HAPPY2) &&
                          buttons.contains(BTN_TRIGGER_HAPPY3) && buttons.contains(BTN_TRIGGER_HAPPY4);
    const auto dpad = [&](std::string_view output, unsigned direct, unsigned code, unsigned direction,
                          std::string_view sign, unsigned legacy) {
        if (!button(direct, output) && !hat(code, direction, output) && !axis(code, output, sign) && xpadDpad)
            button(legacy, output);
    };
    dpad("dpup", BTN_DPAD_UP, ABS_HAT0Y, 1, "-", BTN_TRIGGER_HAPPY3);
    dpad("dpright", BTN_DPAD_RIGHT, ABS_HAT0X, 2, "+", BTN_TRIGGER_HAPPY2);
    dpad("dpdown", BTN_DPAD_DOWN, ABS_HAT0Y, 4, "+", BTN_TRIGGER_HAPPY4);
    dpad("dpleft", BTN_DPAD_LEFT, ABS_HAT0X, 8, "-", BTN_TRIGGER_HAPPY1);

    const bool elite = vendor == 0x045e && buttons.contains(BTN_TRIGGER_HAPPY5) &&
        buttons.contains(BTN_TRIGGER_HAPPY6) && buttons.contains(BTN_TRIGGER_HAPPY7) && buttons.contains(BTN_TRIGGER_HAPPY8);
    const auto paddle = [&](std::string_view output, unsigned code, unsigned legacy) {
        if (!button(code, output) && elite)
            button(legacy, output);
    };
    // BTN_GRIPL/R and BTN_GRIPL2/R2, including builds with older kernel headers.
    paddle("paddle1", 0x225, BTN_TRIGGER_HAPPY5);
    paddle("paddle2", 0x224, BTN_TRIGGER_HAPPY7);
    paddle("paddle3", 0x227, BTN_TRIGGER_HAPPY6);
    paddle("paddle4", 0x226, BTN_TRIGGER_HAPPY8);
    return mapping;
}

} // namespace cc::input::detail
