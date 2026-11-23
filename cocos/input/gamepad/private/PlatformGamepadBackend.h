#pragma once

#include "GamepadBackend.h"

namespace cc::input::detail {

// Reserve known device channels before the host starts its main mixer.
CC_DLL void primeGamepadAudioPolicy();
std::vector<HapticAudioIdentity> connectedHapticAudioIdentities();

std::unique_ptr<GamepadBackend> makeLinuxGamepadBackend();
std::unique_ptr<GamepadBackend> makeAppleGamepadBackend();
std::unique_ptr<GamepadBackend> makeAndroidGamepadBackend();

} // namespace cc::input::detail
