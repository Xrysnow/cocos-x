#pragma once

#include "input/gamepad/GamepadTypes.h"

#include <linux/input.h>

#include <cstdint>
#include <map>
#include <string>

namespace cc::input::detail {

bool evdevDigitalHat(const input_absinfo* x, const input_absinfo* y);
std::string evdevGamepadMapping(std::uint16_t vendor, bool xpad,
    const std::map<unsigned, unsigned>& buttons, const std::map<unsigned, unsigned>& axes,
    const std::map<unsigned, unsigned>& hats, const std::map<unsigned, input_absinfo>& ranges);
float evdevMotionScale(Sensor sensor, int resolution);
std::array<float, 3> evdevMotionCoordinates(std::uint16_t vendor, const std::array<float, 3>& values);

} // namespace cc::input::detail
