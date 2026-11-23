#pragma once

#include "input/gamepad/GamepadFrame.h"

namespace cc::input::gamepad_lua {

class Frame {
public:
    explicit Frame(const GamepadFrame& frame) : _stamp(frame.stamp()), _frame(&frame) {}

    const GamepadFrame* current() const noexcept { return _stamp.current() ? _frame : nullptr; }
    Result<double> tick() const noexcept;
    Result<std::span<const DeviceId>> devices() const noexcept;

private:
    FrameStamp _stamp;
    const GamepadFrame* _frame;
};

class Pad {
public:
    Pad(const GamepadFrame& frame, const PadView& pad) : _stamp(frame.stamp()), _pad(&pad) {}

    const PadView* current() const noexcept { return _stamp.current() ? _pad : nullptr; }
    Result<const DeviceInfo*> info() const noexcept;
    Result<bool> mapped() const noexcept;
    Result<std::string_view> inputLayout() const noexcept;
    Result<std::string_view> mappingStatus() const noexcept;
    Result<std::uint32_t> mappingRevision() const noexcept;
    Result<std::optional<unsigned>> player() const noexcept;

private:
    FrameStamp _stamp;
    const PadView* _pad;
};

} // namespace cc::input::gamepad_lua
