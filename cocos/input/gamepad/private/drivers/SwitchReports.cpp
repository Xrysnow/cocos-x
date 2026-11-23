/*
  Switch input, calibration and rumble adapted from SDL 3.4.20 (SDL_hidapi_switch.c).
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

#include "SwitchReports.h"

#include <algorithm>
#include <bit>
#include <cmath>
#include <numbers>

namespace cc::input::detail {
namespace {

constexpr auto axisMin = std::int16_t{-32768};
constexpr auto axisMax = std::int16_t{32767};
constexpr unsigned capture = 15, rightSl = 16, leftSr = 17, rightSr = 18, leftSl = 19;

unsigned word(std::span<const std::uint8_t> bytes)
{
    return bytes[0] | (static_cast<unsigned>(bytes[1]) << 8);
}

int signedWord(std::span<const std::uint8_t> bytes)
{
    return std::bit_cast<std::int16_t>(static_cast<std::uint16_t>(word(bytes)));
}

std::array<int, 2> packedStick(std::span<const std::uint8_t> bytes)
{
    return {static_cast<int>(word(bytes) & 0xfff), (bytes[2] << 4) | (bytes[1] >> 4)};
}

void setButtons(SwitchInput& input, unsigned bits, std::array<unsigned, 8> indices)
{
    for (unsigned i = 0; i < indices.size(); ++i)
        if (indices[i] < input.buttons.size())
            input.buttons[indices[i]] = static_cast<std::uint8_t>((bits >> i) & 1);
}

constexpr unsigned absent = 20;
constexpr std::array<std::uint8_t, 9> hats{1, 3, 2, 6, 4, 12, 8, 9, 0};

void decodeSimpleButtons(SwitchInput& input, SwitchModel model, std::span<const std::uint8_t> data)
{
    setButtons(input, data[0], {0, 1, 2, 3, 9, 10, absent, absent});
    if (model == SwitchModel::Pro)
    {
        setButtons(input, data[1], {4, 6, 7, 8, 5, capture, absent, absent});
        input.axes[4] = data[0] & 0x40 ? axisMax : axisMin;
        input.axes[5] = (data[0] | data[1]) & 0x80 ? axisMax : axisMin;
    }
    else if (model == SwitchModel::JoyConLeft)
        setButtons(input, data[1], {6, absent, 7, absent, absent, 5, leftSr, leftSl});
    else
        setButtons(input, data[1], {absent, 6, 7, absent, 5, absent, rightSl, rightSr});
}

void decodeFullButtons(SwitchInput& input, SwitchModel model, std::span<const std::uint8_t> data)
{
    if (model == SwitchModel::JoyConLeft)
    {
        setButtons(input, data[1], {6, absent, absent, 7, absent, 5, absent, absent});
        setButtons(input, data[2], {1, 2, 3, 0, 10, 9, leftSr, leftSl});
    }
    else if (model == SwitchModel::JoyConRight)
    {
        setButtons(input, data[0], {3, 1, 2, 0, 10, 9, rightSl, rightSr});
        setButtons(input, data[1], {absent, 6, 7, absent, 5, absent, absent, absent});
    }
    else
    {
        setButtons(input, data[0], {2, 3, 0, 1, absent, absent, 10, absent});
        setButtons(input, data[1], {4, 6, 8, 7, 5, capture, absent, absent});
        input.buttons[static_cast<unsigned>(Button::LeftShoulder)] = (data[2] & 0x40) != 0;
        input.axes[4] = data[2] & 0x80 ? axisMax : axisMin;
        input.axes[5] = data[0] & 0x80 ? axisMax : axisMin;
        // Wire order is down, up, right, left.
        input.hat = static_cast<std::uint8_t>(((data[2] & 1) << 2) | ((data[2] & 2) >> 1) |
                                              ((data[2] & 4) >> 1) | (data[2] & 8));
    }
}

constexpr std::array<std::uint16_t, 101> amplitudes{
    0, 514, 775, 921, 1096, 1303, 1550, 1843, 2192, 2606, 3100, 3686, 4383, 5213, 6199, 7372,
    7698, 8039, 8395, 8767, 9155, 9560, 9984, 10426, 10887, 11369, 11873, 12398, 12947, 13520,
    14119, 14744, 15067, 15397, 15734, 16079, 16431, 16790, 17158, 17534, 17918, 18310, 18711,
    19121, 19540, 19967, 20405, 20851, 21308, 21775, 22251, 22739, 23236, 23745, 24265, 24797,
    25340, 25894, 26462, 27041, 27633, 28238, 28856, 29488, 30134, 30794, 31468, 32157, 32861,
    33581, 34316, 35068, 35836, 36620, 37422, 38242, 39079, 39935, 40809, 41703, 42616, 43549,
    44503, 45477, 46473, 47491, 48531, 49593, 50679, 51789, 52923, 54082, 55266, 56476, 57713,
    58977, 60268, 61588, 62936, 64315, 65535
};

unsigned amplitudeIndex(float amplitude)
{
    const auto value = std::lround(std::clamp(amplitude, 0.f, 1.f) * 65535.f);
    return static_cast<unsigned>(std::ranges::lower_bound(amplitudes, value) - amplitudes.begin());
}

} // namespace

std::optional<SwitchModel> switchModel(unsigned vendor, unsigned product)
{
    if (vendor == 0x057e)
        switch (product)
        {
        case 0x2006: return SwitchModel::JoyConLeft;
        case 0x2007: return SwitchModel::JoyConRight;
        case 0x2009: return SwitchModel::Pro;
        }
    return {};
}

GamepadType switchGamepadType(SwitchModel model)
{
    switch (model)
    {
    case SwitchModel::JoyConLeft: return GamepadType::JoyConLeft;
    case SwitchModel::JoyConRight: return GamepadType::JoyConRight;
    case SwitchModel::Pro: return GamepadType::SwitchPro;
    }
    return GamepadType::Unknown;
}

const char* switchName(SwitchModel model)
{
    switch (model)
    {
    case SwitchModel::JoyConLeft: return "Nintendo Switch Joy-Con (L)";
    case SwitchModel::JoyConRight: return "Nintendo Switch Joy-Con (R)";
    case SwitchModel::Pro: return "Nintendo Switch Pro Controller";
    }
    return "Nintendo Switch Controller";
}

void configureSwitchLayout(RawLayout& layout, SwitchModel model)
{
    const bool pro = model == SwitchModel::Pro;
    layout.buttonCount = 20;
    layout.axisCount = pro ? 6 : 2;
    layout.hatCount = pro ? 1 : 0;
    layout.buttonPresent.assign(layout.buttonCount, 0);
    for (auto index : {0, 1, 2, 3, 5, 6, 7, 9, 10})
        layout.buttonPresent[index] = 1;
    layout.builtInMapping = "a:b0,b:b1,x:b2,y:b3,guide:b5,start:b6,leftstick:b7,"
                            "leftshoulder:b9,rightshoulder:b10,leftx:a0,lefty:a1";
    if (pro)
    {
        for (auto index : {4u, 8u, capture})
            layout.buttonPresent[index] = 1;
        layout.builtInMapping += ",back:b4,rightstick:b8,misc1:b15,rightx:a2,righty:a3,"
                                "lefttrigger:a4,righttrigger:a5,dpup:h0.1,dpright:h0.2,dpdown:h0.4,"
                                "dpleft:h0.8,face:bayx";
    }
    else if (model == SwitchModel::JoyConLeft)
    {
        layout.buttonPresent[leftSr] = layout.buttonPresent[leftSl] = 1;
        layout.builtInMapping += ",paddle2:b17,paddle4:b19";
    }
    else
    {
        layout.buttonPresent[rightSl] = layout.buttonPresent[rightSr] = 1;
        layout.builtInMapping += ",paddle1:b16,paddle3:b18";
    }
}

std::int16_t SwitchReports::StickAxis::scale(int value, bool inverted)
{
    const auto offset = value - center;
    auto& extent = offset < 0 ? negative : positive;
    extent = std::max(extent, std::abs(offset));
    const auto directed = inverted ? -offset : offset;
    return static_cast<std::int16_t>(directed * (directed < 0 ? 32768 : 32767) / extent);
}

void SwitchReports::calibrate(std::uint16_t address, std::span<const std::uint8_t> data)
{
    const bool userSticks = address == SwitchUserSticks;
    if ((userSticks && data.size() == 22) || (address == SwitchFactorySticks && data.size() == 18))
    {
        for (unsigned stick = 0; stick < 2; ++stick)
        {
            auto block = data.subspan(stick * (userSticks ? 11 : 9));
            if (userSticks)
            {
                if (word(block) != 0xa1b2) continue;
                block = block.subspan(2);
            }
            else if (_userStick[stick])
                continue;
            const auto center = packedStick(block.subspan(stick == 0 ? 3 : 0));
            const auto minimum = packedStick(block.subspan(stick == 0 ? 6 : 3));
            const auto maximum = packedStick(block.subspan(stick == 0 ? 0 : 6));
            if (std::ranges::any_of(center, [](int v) { return v <= 0 || v >= 4095; }) ||
                std::ranges::any_of(minimum, [](int v) { return v <= 0 || v >= 4095; }) ||
                std::ranges::any_of(maximum, [](int v) { return v <= 0 || v >= 4095; }))
                continue;
            for (unsigned axis = 0; axis < 2; ++axis)
                _stick[stick * 2 + axis] = {center[axis], std::max(1, minimum[axis] * 7 / 10),
                                            std::max(1, maximum[axis] * 7 / 10)};
            _userStick[stick] = userSticks;
        }
    }
    else if (address == SwitchFactoryImu && data.size() == 24)
    {
        auto scales = _imuScale;
        std::array<int, 6> origins{};
        for (unsigned i = 0; i < origins.size(); ++i)
        {
            const unsigned offset = i < 3 ? i * 2 : 12 + (i - 3) * 2;
            origins[i] = signedWord(data.subspan(offset));
            const auto range = signedWord(data.subspan(offset + 6)) - origins[i];
            if (range <= 0) return;
            scales[i] = (i < 3 ? 4 * 9.80665f : 936 * std::numbers::pi_v<float> / 180) /
                static_cast<float>(range);
        }
        _imuOrigin = origins;
        _imuScale = scales;
        _factoryImu = true;
    }
    else if (address == SwitchUserImu && data.size() == 20 && _factoryImu && word(data) == 0xa1b2)
    {
        auto scales = _imuScale;
        auto origins = _imuOrigin;
        for (unsigned i = 0; i < origins.size(); ++i)
        {
            const unsigned offset = i < 3 ? 2 + i * 2 : 14 + (i - 3) * 2;
            const auto newOrigin = signedWord(data.subspan(offset));
            const auto multiplier = i < 3 ? 4 * 9.80665f : 936 * std::numbers::pi_v<float> / 180;
            const auto range = multiplier / scales[i] + static_cast<float>(origins[i] - newOrigin);
            if (range <= 0) return;
            scales[i] = multiplier / range;
            origins[i] = newOrigin;
        }
        _imuOrigin = origins;
        _imuScale = scales;
    }
}

std::optional<SwitchInput> SwitchReports::decode(std::span<const std::uint8_t> packet, bool motion)
{
    if (packet.empty()) return {};
    SwitchInput input;
    const bool pro = _model == SwitchModel::Pro;
    const bool right = _model == SwitchModel::JoyConRight;
    if (packet[0] == 0x3f && packet.size() >= (pro ? 12u : 4u))
    {
        decodeSimpleButtons(input, _model, packet.subspan(1));
        const auto hat = hats[std::min<unsigned>(packet[3], 8)];
        if (pro)
        {
            input.hat = hat;
            for (unsigned i = 0; i < 4; ++i)
                input.axes[i] = _simple[i].scale(static_cast<int>(word(packet.subspan(4 + 2 * i))), false);
        }
        else
        {
            input.axes[0] = hat & 2 ? axisMax : hat & 8 ? axisMin : 0;
            input.axes[1] = hat & 4 ? axisMax : hat & 1 ? axisMin : 0;
        }
    }
    else if ((packet[0] == 0x30 || packet[0] == 0x31) && packet.size() >= 49)
    {
        decodeFullButtons(input, _model, packet.subspan(3, 3));
        if (pro)
        {
            for (unsigned i = 0; i < 4; i += 2)
            {
                const auto stick = packedStick(packet.subspan(6 + i / 2 * 3));
                input.axes[i] = _stick[i].scale(stick[0], false);
                input.axes[i + 1] = _stick[i + 1].scale(stick[1], true);
            }
        }
        else
        {
            const auto stick = packedStick(packet.subspan(right ? 9 : 6));
            const auto axis = right ? 2u : 0u;
            input.axes[0] = _stick[axis + 1].scale(stick[1], !right);
            input.axes[1] = _stick[axis].scale(stick[0], !right);
        }
        const auto level = std::min((packet[2] & 0xe0u) >> 5, 4u);
        const bool charging = (packet[2] & 0x10u) != 0;
        input.power = Power{charging ? (level == 4 ? Power::State::Charged : Power::State::Charging)
                                     : Power::State::OnBattery, level * 25, {}};
        if (motion && std::ranges::any_of(packet.subspan(13, 36), [](auto byte) { return byte != 0; }))
        {
            for (unsigned sample = 3; sample > 0; --sample)
            {
                const auto bytes = packet.subspan(13 + (sample - 1) * 12, 12);
                for (unsigned kind = 0; kind < 2; ++kind)
                {
                    std::array<float, 3> raw{};
                    for (unsigned axis = 0; axis < 3; ++axis)
                    {
                        const auto index = kind * 3 + axis;
                        const auto origin = kind == 0 ? 0 : _imuOrigin[index];
                        raw[axis] = static_cast<float>(signedWord(bytes.subspan(index * 2)) - origin) *
                            _imuScale[index];
                    }
                    std::array<float, 3> xyz{-raw[1], raw[2], -raw[0]};
                    if (_model == SwitchModel::JoyConLeft) xyz = {xyz[2], xyz[1], -xyz[0]};
                    if (right) xyz = {-xyz[2], -xyz[1], -xyz[0]};
                    input.motion[input.motionCount++] = {kind == 0 ? Sensor::Accel : Sensor::Gyro, xyz, {}};
                }
            }
        }
    }
    else
        return {};
    return input;
}

SwitchMotors encodeSwitchRumble(SwitchModel model, float low, float high)
{
    const auto lf = amplitudeIndex(low);
    const auto hf = static_cast<std::uint8_t>(amplitudeIndex(high) * 2);
    if (!lf && !hf)
        return SwitchNeutralRumble;
    if (model == SwitchModel::Pro)
    {
        // Keep the channels on separate actuators. The first band supports
        // both the 160 Hz left carrier and the 320 Hz right carrier.
        auto motors = SwitchNeutralRumble;
        if (lf)
        {
            motors[0] = 0x80;
            motors[1] = static_cast<std::uint8_t>(lf * 2);
        }
        motors[5] |= hf; // Preserve the 320 Hz frequency bit.
        return motors;
    }
    const auto lowBand = static_cast<std::uint8_t>(0x3d | ((lf & 1u) << 7));
    const auto lowAmp = static_cast<std::uint8_t>(0x40 + lf / 2);
    return {0x74, hf, lowBand, lowAmp, 0x74, hf, lowBand, lowAmp};
}

SwitchRequest SwitchRequest::spi(std::uint16_t address, std::uint8_t length)
{
    return {0x10, false, {static_cast<std::uint8_t>(address), static_cast<std::uint8_t>(address >> 8),
                          0, 0, length}, 5};
}

std::optional<std::span<const std::uint8_t>> SwitchRequest::reply(std::span<const std::uint8_t> packet) const
{
    if (usb)
    {
        if (packet.size() >= 2 && packet[0] == 0x81 && packet[1] == id)
            return packet.subspan(2);
        return {};
    }
    if (packet.size() < 15 || packet[0] != 0x21 || !(packet[13] & 0x80) || packet[14] != id)
        return {};
    auto payload = packet.subspan(15);
    if (id == 0x10)
    {
        if (payload.size() < data.size() + data[4] || !std::ranges::equal(payload.first(data.size()), data))
            return {};
        payload = payload.subspan(data.size(), data[4]);
    }
    return payload;
}

SwitchPacket SwitchOutput::usb(std::uint8_t command) const
{
    return {0x80, command};
}

SwitchPacket SwitchOutput::motorPacket(std::uint8_t report, const SwitchMotors& motors)
{
    SwitchPacket packet{report, _sequence};
    _sequence = static_cast<std::uint8_t>((_sequence + 1) & 0x0f);
    std::ranges::copy(motors, packet.begin() + 2);
    return packet;
}

SwitchPacket SwitchOutput::subcommand(const SwitchRequest& request, const SwitchMotors& motors)
{
    auto packet = motorPacket(0x01, motors);
    packet[10] = request.id;
    std::ranges::copy(std::span(request.data).first(request.size), packet.begin() + 11);
    return packet;
}

SwitchPacket SwitchOutput::rumble(const SwitchMotors& motors)
{
    return motorPacket(0x10, motors);
}

} // namespace cc::input::detail
