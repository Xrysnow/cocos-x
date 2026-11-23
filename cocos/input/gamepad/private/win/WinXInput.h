#pragma once

#include "../GamepadBackend.h"

#include <Windows.h>
#include <Xinput.h>

#include <functional>
#include <memory>

namespace cc::input::detail {

// Kept at the system API boundary so tests exercise the same poller, decoding
// and output routing without loading another process or substituting OS DLLs.
class XInputApi {
public:
    virtual ~XInputApi() = default;
    virtual DWORD read(DWORD slot, XINPUT_STATE&) noexcept = 0;
    virtual DWORD capabilities(DWORD slot, XINPUT_CAPABILITIES&) noexcept = 0;
    virtual DWORD vibrate(DWORD slot, XINPUT_VIBRATION) noexcept = 0;
    virtual std::optional<Power> power(DWORD slot) noexcept = 0;
};

std::unique_ptr<GamepadBackend> makeXInputBackend(std::unique_ptr<XInputApi> api);
std::unique_ptr<GamepadBackend> makeWinGamepadBackend(std::function<bool()> enableWgi = {});

} // namespace cc::input::detail
