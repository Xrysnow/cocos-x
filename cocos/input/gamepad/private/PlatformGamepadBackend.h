#pragma once

#include "GamepadBackend.h"

namespace cc::input::detail {

std::unique_ptr<GamepadBackend> makeLinuxGamepadBackend();
std::unique_ptr<GamepadBackend> makeAppleGamepadBackend();
std::unique_ptr<GamepadBackend> makeAndroidGamepadBackend();

} // namespace cc::input::detail
