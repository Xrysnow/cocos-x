#pragma once

#include "../GamepadBackend.h"

#include <memory>

namespace cc::input::detail {

inline constexpr std::uint64_t WinWgiId = 4;
bool isWinWgiXboxProduct(unsigned vendor, unsigned product);
bool winWgiApiAvailable();
std::unique_ptr<GamepadBackend> makeWinWgiBackend();

} // namespace cc::input::detail
