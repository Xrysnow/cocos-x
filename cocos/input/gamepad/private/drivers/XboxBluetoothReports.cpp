/*
  Xbox Bluetooth protocol adapted from SDL 3.4.20 (SDL_hidapi_xboxone.c).
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "XboxBluetoothReports.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace cc::input::detail {
namespace {

constexpr unsigned microsoftVendor = 0x045e;
constexpr unsigned buttonIndex(Button button)
{
    return static_cast<unsigned>(button);
}

constexpr std::array paddleButtons{Button::RightPaddle1, Button::LeftPaddle1,
                                   Button::RightPaddle2, Button::LeftPaddle2};
constexpr std::array<std::uint8_t, 9> hats{0, 1, 3, 2, 6, 4, 12, 8, 9};

unsigned word(std::span<const std::uint8_t> bytes)
{
    return bytes[0] | (static_cast<unsigned>(bytes[1]) << 8);
}

std::int16_t trigger(unsigned value)
{
    const auto position = static_cast<int>(value & 0x3ff);
    return static_cast<std::int16_t>(position == 0x3ff ? 32767 : position * 64 - 32768);
}

struct ButtonBit {
    Button button;
    std::uint8_t mask;
};

void setButtons(XboxBluetoothControls& controls, std::uint8_t value, std::span<const ButtonBit> bits)
{
    for (const auto& [button, mask] : bits)
        controls.buttons[buttonIndex(button)] = (value & mask) != 0;
}

void decodeButtons16(XboxBluetoothControls& controls, std::span<const std::uint8_t> bytes)
{
    constexpr ButtonBit face[] = {
        {Button::South, 0x01}, {Button::East, 0x02}, {Button::West, 0x04}, {Button::North, 0x08},
        {Button::LeftShoulder, 0x10}, {Button::RightShoulder, 0x20}, {Button::Back, 0x40},
        {Button::Start, 0x80}
    };
    constexpr ButtonBit sticks[] = {{Button::LeftStick, 0x01}, {Button::RightStick, 0x02}};
    setButtons(controls, bytes[14], face);
    setButtons(controls, bytes[15], sticks);
}

void decodeButtons(XboxBluetoothControls& controls, std::span<const std::uint8_t> bytes,
                   XboxBluetoothModel model)
{
    constexpr ButtonBit face[] = {
        {Button::South, 0x01}, {Button::East, 0x02}, {Button::West, 0x08}, {Button::North, 0x10},
        {Button::LeftShoulder, 0x40}, {Button::RightShoulder, 0x80}
    };
    constexpr ButtonBit other[] = {
        {Button::Start, 0x08}, {Button::LeftStick, 0x20}, {Button::RightStick, 0x40}
    };
    setButtons(controls, bytes[14], face);
    setButtons(controls, bytes[15], other);
    const bool extra = (bytes[16] & 1) != 0;
    controls.buttons[buttonIndex(Button::Back)] =
        (bytes[15] & 0x04) != 0 || (model != XboxBluetoothModel::Series && extra);
    controls.buttons[buttonIndex(Button::Misc1)] = model == XboxBluetoothModel::Series && extra;
}

void decodePaddles(XboxBluetoothControls& controls, std::span<const std::uint8_t> bytes)
{
    unsigned paddle, mapped;
    switch (bytes.size())
    {
    case 20: paddle = 19; mapped = 17; break; // Firmware 5.13+
    case 39: paddle = 17; mapped = 19; break;
    case 55: paddle = 33; mapped = 35; break;
    default: return;
    }

    controls.hasPaddles = true;
    if (bytes[mapped])
        return;
    for (unsigned i = 0; i < paddleButtons.size(); ++i)
        controls.buttons[buttonIndex(paddleButtons[i])] = (bytes[paddle] & (1u << i)) != 0;
}

bool validRumble(float first, float second, std::chrono::milliseconds duration)
{
    return first >= 0 && first <= 1 && second >= 0 && second <= 1 &&
           duration >= std::chrono::milliseconds::zero() && duration <= std::chrono::seconds(60);
}

std::uint8_t magnitude(float strength)
{
    return static_cast<std::uint8_t>(std::lround(strength * 100.f));
}

} // namespace

std::optional<XboxBluetoothModel> xboxBluetoothModel(unsigned vendor, unsigned product)
{
    if (vendor != microsoftVendor)
        return {};
    switch (product)
    {
    case 0x02e0:
    case 0x02fd:
    case 0x0b20: return XboxBluetoothModel::OneS;
    case 0x0b13: return XboxBluetoothModel::Series;
    case 0x0b05:
    case 0x0b22: return XboxBluetoothModel::Elite2;
    default: return {};
    }
}

bool isMicrosoftXboxGamepad(unsigned vendor, unsigned product)
{
    if (vendor != microsoftVendor)
        return false;
    switch (product)
    {
    case 0x02d1: // Xbox One
    case 0x02dd: // Xbox One (updated firmware)
    case 0x02e3: // Xbox Elite Series 1
    case 0x02ea: // Xbox One S
    case 0x02ff: // XboxGIP software identity
    case 0x0b00: // Xbox Elite Series 2
    case 0x0b12: // Xbox Series
        return true;
    default:
        return xboxBluetoothModel(vendor, product).has_value();
    }
}

bool isKnownXboxProduct(unsigned vendor, unsigned product)
{
    return isMicrosoftXboxGamepad(vendor, product) || (vendor == microsoftVendor && product == 0x028e);
}

const char* xboxBluetoothName(XboxBluetoothModel model)
{
    switch (model)
    {
    case XboxBluetoothModel::OneS: return "Xbox One S Controller";
    case XboxBluetoothModel::Series: return "Xbox Series Controller";
    case XboxBluetoothModel::Elite2: return "Xbox Elite Series 2 Controller";
    }
    return "Xbox Controller";
}

void configureXboxBluetoothLayout(RawLayout& layout, XboxBluetoothModel model)
{
    layout.buttonCount = buttonIndex(Button::LeftPaddle2) + 1;
    layout.axisCount = AxisCount;
    layout.hatCount = 1;
    layout.buttonPresent.assign(layout.buttonCount, 0);
    std::fill_n(layout.buttonPresent.begin(), buttonIndex(Button::RightShoulder) + 1, std::uint8_t{1});
    layout.builtInMapping =
        "a:b0,b:b1,x:b2,y:b3,back:b4,guide:b5,start:b6,leftstick:b7,rightstick:b8,"
        "leftshoulder:b9,rightshoulder:b10,dpup:h0.1,dpright:h0.2,dpdown:h0.4,dpleft:h0.8,"
        "leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:a4,righttrigger:a5";
    if (model == XboxBluetoothModel::Series)
    {
        layout.buttonPresent[buttonIndex(Button::Misc1)] = 1;
        layout.builtInMapping += ",misc1:b15";
    }
    else if (model == XboxBluetoothModel::Elite2)
    {
        for (auto button : paddleButtons)
            layout.buttonPresent[buttonIndex(button)] = 1;
        layout.builtInMapping += ",paddle1:b16,paddle2:b17,paddle3:b18,paddle4:b19";
    }
}

std::optional<XboxBluetoothInput> XboxBluetoothReports::decode(std::span<const std::uint8_t> bytes)
{
    if (bytes.size() < 2)
        return {};
    XboxBluetoothInput input;
    switch (bytes.front())
    {
    case 0x01:
    {
        const bool legacy = bytes.size() == 16 && _model == XboxBluetoothModel::OneS;
        if (!legacy && bytes.size() < 17)
            return {};
        auto& controls = input.controls.emplace();
        for (unsigned i = 0; i < 4; ++i)
            controls.axes[i] = static_cast<std::int16_t>(static_cast<int>(word(bytes.subspan(1 + 2 * i))) - 32768);
        controls.axes[static_cast<unsigned>(Axis::LeftTrigger)] = trigger(word(bytes.subspan(9)));
        controls.axes[static_cast<unsigned>(Axis::RightTrigger)] = trigger(word(bytes.subspan(11)));
        const auto hat = bytes[13] & 0x0fu;
        controls.hat = hat < hats.size() ? hats[hat] : 0;
        if (legacy)
            decodeButtons16(controls, bytes);
        else
        {
            decodeButtons(controls, bytes, _model);
            if (!_separateGuide)
                input.guide = (bytes[15] & 0x10) != 0;
            if (_model == XboxBluetoothModel::Elite2)
                decodePaddles(controls, bytes);
        }
        break;
    }
    case 0x02:
        _separateGuide = true;
        input.guide = (bytes[1] & 1) != 0;
        break;
    case 0x04:
        input.power = Power{(bytes[1] & 0x0c) == 0 ? Power::State::Charging : Power::State::OnBattery,
                            {}, bytes[1] & 3u};
        break;
    default:
        return {};
    }
    return input;
}

bool xboxBluetoothHasRumbleOutput(std::span<const std::uint8_t> hidDescriptor)
{
    struct ReportGlobals {
        std::uint32_t id = 0, size = 0, count = 0;
    };
    ReportGlobals globals;
    std::vector<ReportGlobals> stack;
    constexpr auto reportBits = (XboxBluetoothOutputSize - 1) * 8;
    std::uint64_t bits = 0;
    while (!hidDescriptor.empty())
    {
        const auto item = hidDescriptor.front();
        hidDescriptor = hidDescriptor.subspan(1);
        if (item == 0xfe)
        {
            if (hidDescriptor.size() < 2 || hidDescriptor.size() - 2 < hidDescriptor.front())
                return false;
            hidDescriptor = hidDescriptor.subspan(2 + hidDescriptor.front());
            continue;
        }
        const auto sizeCode = item & 3u;
        const auto size = sizeCode == 3 ? 4 : sizeCode;
        if (hidDescriptor.size() < size)
            return false;
        std::uint32_t value = 0;
        for (unsigned i = 0; i < size; ++i)
            value |= static_cast<std::uint32_t>(hidDescriptor[i]) << (8 * i);
        hidDescriptor = hidDescriptor.subspan(size);

        switch (item & 0xfc)
        {
        case 0x74: globals.size = value; break;  // Report Size
        case 0x84: globals.id = value; break;    // Report ID
        case 0x94: globals.count = value; break; // Report Count
        case 0xa4: stack.push_back(globals); break;
        case 0xb4:
            if (stack.empty())
                return false;
            globals = stack.back();
            stack.pop_back();
            break;
        case 0x90: // Output
            if (globals.id == 0x03)
            {
                const auto fieldBits = static_cast<std::uint64_t>(globals.size) * globals.count;
                if (fieldBits > reportBits - bits)
                    return false;
                bits += fieldBits;
            }
            break;
        }
    }
    return bits == reportBits && stack.empty();
}

void XboxRumbleState::Pair::set(float firstStrength, float secondStrength,
                                std::chrono::milliseconds duration, std::uint64_t time)
{
    if (duration.count() == 0 || (firstStrength == 0 && secondStrength == 0))
    {
        *this = {};
        return;
    }
    first = firstStrength;
    second = secondStrength;
    const auto ns = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count());
    deadline = time + std::min(ns, std::numeric_limits<std::uint64_t>::max() - time);
}

bool XboxRumbleState::Pair::expire(std::uint64_t time)
{
    if (!deadline || (*deadline > time && bodyGateOpen(gate)))
        return false;
    *this = {};
    return true;
}

bool XboxRumbleState::apply(const OutputCommand& command, std::uint64_t time, const NativeBodyGate& gate)
{
    if (const auto* body = std::get_if<Rumble>(&command))
    {
        if (!validRumble(body->low, body->high, body->duration))
            return false;
        expire(time);
        if (!bodyGateOpen(gate))
            return false;
        _body.set(body->low, body->high, body->duration, time);
        _body.gate = _body.deadline ? gate : NativeBodyGate{};
        return true;
    }
    if (const auto* triggers = std::get_if<TriggerRumble>(&command))
    {
        if (!validRumble(triggers->left, triggers->right, triggers->duration))
            return false;
        expire(time);
        _triggers.set(triggers->left, triggers->right, triggers->duration, time);
        return true;
    }
    if (const auto* stop = std::get_if<Stop>(&command))
    {
        switch (stop->channel)
        {
        case Channel::All:
            _body = {};
            _triggers = {};
            return true;
        case Channel::Body:
            _body = {};
            _triggers.expire(time);
            return true;
        case Channel::Triggers:
            _triggers = {};
            _body.expire(time);
            return true;
        default:
            break;
        }
    }
    return false;
}

bool XboxRumbleState::expire(std::uint64_t time)
{
    const bool bodyExpired = _body.expire(time);
    const bool triggersExpired = _triggers.expire(time);
    return bodyExpired || triggersExpired;
}

XboxRumbleMotors XboxRumbleState::motors() const
{
    return {_body.first, _body.second, _triggers.first, _triggers.second};
}

std::optional<std::uint64_t> XboxRumbleState::deadline() const
{
    if (_body.deadline && _triggers.deadline)
        return std::min(*_body.deadline, *_triggers.deadline);
    return _body.deadline ? _body.deadline : _triggers.deadline;
}

bool XboxRumbleState::active() const
{
    return _body.deadline.has_value() || _triggers.deadline.has_value();
}

std::array<std::uint8_t, XboxBluetoothOutputSize> XboxRumbleState::bluetoothReport() const
{
    return {0x03, 0x0f, magnitude(_triggers.first), magnitude(_triggers.second),
            magnitude(_body.first), magnitude(_body.second), 0xff, 0x00, 0xeb};
}

} // namespace cc::input::detail
