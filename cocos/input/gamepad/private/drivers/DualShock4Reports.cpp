/*
  DualShock 4 report handling adapted from SDL 3.4.20's SDL_hidapi_ps4.c.
  This is an altered implementation for the cocos-x gamepad service.

  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
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

#include "DualShock4Reports.h"
#include "SonyReportBits.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace cc::input::detail {
namespace {

constexpr float gyroScale = std::numbers::pi_v<float> / (180.f * 16.f);
constexpr float gravity = 9.80665f;
constexpr float accelScale = gravity / 8192.f;
constexpr std::size_t usbInputLength = 64, bluetoothInputLength = 78;
constexpr std::uint8_t rumbleFlag = 1, lightFlag = 2;

using playstation::crc;
using playstation::little;
using playstation::signedSample;
using playstation::store;

DualSenseControls decodeControls(std::span<const std::uint8_t> data)
{
    DualSenseControls result;
    constexpr std::array<std::uint8_t, 8> hats{1, 3, 2, 6, 4, 12, 8, 9};
    const auto direction = data[4] & 0x0fu;
    if (direction < hats.size())
        result.hat = hats[direction];

    // Canonical Sony layout. The microphone and Edge controls are absent on the DS4.
    constexpr std::array<unsigned, 12> buttonBits{5, 6, 4, 7, 12, 16, 13, 14, 15, 8, 9, 17};
    for (unsigned index = 0; index < buttonBits.size(); ++index)
    {
        const auto bit = buttonBits[index];
        result.buttons[index] = static_cast<std::uint8_t>((data[4 + bit / 8] >> (bit % 8)) & 1);
    }
    for (unsigned index = 0; index < 4; ++index)
        result.axes[index] = static_cast<std::int16_t>(data[index] * 257 - 32768);
    for (unsigned index = 0; index < 2; ++index)
    {
        const auto digital = static_cast<std::uint8_t>((data[5] >> (2 + index)) & 1);
        const auto analog = data[7 + index];
        result.buttons[13 + index] = digital;
        result.axes[4 + index] = static_cast<std::int16_t>(analog == 0 && digital ? 32767 : analog * 257 - 32768);
    }
    return result;
}

Power decodePower(std::uint8_t status)
{
    const auto level = status & 0x0fu;
    const auto percent = std::min(100u, level * 10u + 5u);
    if ((status & 0x10) == 0)
        return {Power::State::OnBattery, percent, {}};
    if (level <= 10)
        return {Power::State::Charging, percent, {}};
    if (level == 11)
        return {Power::State::Charged, 100u, {}};
    return {};
}

bool hasNativeBluetoothPayload(std::span<const std::uint8_t> packet)
{
    // The Slim can send a 128-byte 0x01 report over Bluetooth with a USB-layout payload.
    // Windows also pads the 10-byte 0x01 report, so padding alone cannot establish the format.
    return packet.size() >= 128 && std::ranges::any_of(packet.subspan(10, usbInputLength - 10),
                                                        [](std::uint8_t byte) { return byte != 0; });
}

} // namespace

bool isDualShock4Product(std::uint16_t vendor, std::uint16_t product) noexcept
{
    return vendor == 0x054c && (product == 0x05c4 || product == 0x09cc);
}

std::optional<DualSenseCalibration> decodeDualShock4Calibration(DualShock4Transport transport,
                                                               std::span<const std::uint8_t> packet)
{
    const bool bluetooth = transport == DualShock4Transport::Bluetooth;
    if (packet.size() < 35 || packet.front() != (bluetooth ? 0x05 : 0x02))
        return {};
    if (bluetooth && (packet.size() < 41 || crc(0xa3, packet.first(37)) != little(packet.subspan(37, 4))))
        return {};
    const auto speed = signedSample(packet, 19) + signedSample(packet, 21);
    if (speed <= 0)
        return {};

    DualSenseCalibration result;
    const bool groupedGyro = transport != DualShock4Transport::Usb;
    for (unsigned axis = 0; axis < 3; ++axis)
    {
        const auto bias = signedSample(packet, 1 + axis * 2);
        const auto positive = signedSample(packet, 7 + axis * (groupedGyro ? 2 : 4));
        const auto negative = signedSample(packet, groupedGyro ? 13 + axis * 2 : 9 + axis * 4);
        const auto counts = std::abs(positive - bias) + std::abs(negative - bias);
        const auto accelPositive = signedSample(packet, 23 + axis * 4);
        const auto accelNegative = signedSample(packet, 25 + axis * 4);
        const auto range = accelPositive - accelNegative;
        if (positive == negative || range <= 0)
            return {};
        const auto gyroRatio = static_cast<float>(speed * 16) / static_cast<float>(counts);
        const auto accelRatio = 16384.f / static_cast<float>(range);
        const auto accelBias = accelPositive - range / 2;
        if (std::abs(bias) > 1024 || std::abs(accelBias) > 1024 ||
            std::abs(1.f - gyroRatio) > .5f || std::abs(1.f - accelRatio) > .5f)
            return {};
        result.bias[axis] = static_cast<float>(bias);
        result.scale[axis] = gyroRatio * gyroScale;
        result.bias[3 + axis] = static_cast<float>(accelBias);
        result.scale[3 + axis] = accelRatio * accelScale;
    }
    return result;
}

std::optional<DualShock4Input> decodeDualShock4Input(DualShock4Transport transport,
                                                   std::span<const std::uint8_t> packet,
                                                   const std::optional<DualSenseCalibration>& calibration)
{
    if (packet.empty())
        return {};
    const bool bluetooth = transport == DualShock4Transport::Bluetooth;
    std::span<const std::uint8_t> data;
    unsigned maxTouchSamples = 3;
    if (packet.front() == 0x01)
    {
        if (packet.size() < usbInputLength || (packet[31] & 0x04) ||
            (bluetooth && !hasNativeBluetoothPayload(packet)))
            return {};
        data = packet.subspan(1, usbInputLength - 1);
    }
    else if (bluetooth && packet.front() >= 0x11 && packet.front() <= 0x19)
    {
        if (packet.size() < bluetoothInputLength || !(packet[1] & 0x80) ||
            crc(0xa1, packet.first(74)) != little(packet.subspan(74, 4)))
            return {};
        data = packet.subspan(3, 71);
        maxTouchSamples = 4;
    }
    else
        return {};

    const auto touchSamples = data[32];
    if (touchSamples > maxTouchSamples)
        return {};

    DualShock4Input result;
    static_cast<DualSenseControls&>(result) = decodeControls(data);
    result.sensorTicks = little(data.subspan(9, 2));
    result.power = decodePower(data[29]);
    result.hasTouchSample = touchSamples != 0;
    if (result.hasTouchSample)
        for (unsigned index = 0; index < result.fingers.size(); ++index)
        {
            const auto point = data.subspan(34 + index * 4, 4);
            if (point[0] & 0x80)
                continue;
            const auto x = (point[2] & 0x0f) * 256 + point[1];
            const auto y = point[3] * 16 + (point[2] >> 4);
            result.fingers[index] = Contact{0, static_cast<unsigned>(point[0] & 0x7fu), ContactPhase::Move,
                std::min(1.f, static_cast<float>(x) / 1920.f),
                std::min(1.f, static_cast<float>(y) / 920.f), {}};
        }

    result.motion[0].sensor = Sensor::Gyro;
    result.motion[1].sensor = Sensor::Accel;
    for (unsigned axis = 0; axis < 6; ++axis)
    {
        const auto raw = static_cast<float>(signedSample(data, 12 + axis * 2));
        result.motion[axis / 3].xyz[axis % 3] = calibration
            ? (raw - calibration->bias[axis]) * calibration->scale[axis]
            : raw * (axis < 3 ? gyroScale : accelScale);
    }
    return result;
}

std::optional<DualSenseControls> decodeDualShock4Simple(DualShock4Transport transport,
                                                       std::span<const std::uint8_t> packet)
{
    if (packet.size() < 10 || packet.front() != 0x01)
        return {};
    if (transport == DualShock4Transport::Bluetooth ? hasNativeBluetoothPayload(packet) : packet.size() != 10)
        return {};
    return decodeControls(packet.subspan(1, 9));
}

std::uint64_t DualShock4SensorClock::sampleTimeNs(std::uint16_t ticks)
{
    if (_lastTick)
        _ticks += static_cast<std::uint16_t>(ticks - *_lastTick);
    _lastTick = ticks;
    return _ticks * 16000 / 3;
}

void DualShock4SensorClock::reset() noexcept
{
    _lastTick.reset();
    _ticks = 0;
}

bool DualShock4Output::apply(const OutputCommand& command, std::uint64_t now, bool cancelBody)
{
    const auto unit = [](float value) { return std::isfinite(value) && 0 <= value && value <= 1; };
    if (const auto* rumble = std::get_if<Rumble>(&command))
    {
        if (!unit(rumble->low) || !unit(rumble->high) || rumble->duration.count() < 0 ||
            rumble->duration > std::chrono::seconds(60))
            return false;
        _low = static_cast<std::uint8_t>(std::lround(rumble->low * 255));
        _high = static_cast<std::uint8_t>(std::lround(rumble->high * 255));
        if (rumble->duration.count() == 0)
            _low = _high = 0;
        if (_low || _high)
            _expires = now + static_cast<std::uint64_t>(rumble->duration.count()) * 1000000;
        else
            _expires.reset();
        _effectFlags = rumbleFlag;
    }
    else if (const auto* rgb = std::get_if<Rgb>(&command))
    {
        _rgb = *rgb;
        _effectFlags = lightFlag | (expire(now, cancelBody) ? rumbleFlag : 0);
    }
    else if (const auto* stop = std::get_if<Stop>(&command))
    {
        switch (stop->channel)
        {
        case Channel::All: _effectFlags = rumbleFlag | lightFlag; break;
        case Channel::Body: _effectFlags = rumbleFlag; break;
        case Channel::Lights: _effectFlags = lightFlag | (expire(now, cancelBody) ? rumbleFlag : 0); break;
        default: return false;
        }
        if (_effectFlags & rumbleFlag)
        {
            _expires.reset();
            _low = _high = 0;
        }
        if (_effectFlags & lightFlag)
            _rgb = {};
    }
    else
        return false;
    return true;
}

bool DualShock4Output::expire(std::uint64_t now, bool cancelBody)
{
    if (!_expires || (!cancelBody && now < *_expires))
        return false;
    _expires.reset();
    _low = _high = 0;
    _effectFlags = rumbleFlag;
    return true;
}

std::span<const std::uint8_t> DualShock4Output::encode(DualShock4Transport transport, unsigned usbLength,
                                                       bool enableOnly)
{
    const bool bluetooth = transport == DualShock4Transport::Bluetooth;
    if (!bluetooth && (usbLength < 32 || usbLength > _packet.size() || enableOnly))
        return {};
    _packet.fill(0);
    _packet[0] = bluetooth ? 0x11 : 0x05;
    if (bluetooth)
        _packet[1] = 0xc4; // HID framing, CRC and a 4 ms report interval.
    if (!enableOnly)
    {
        // Apply only the selected channel while retaining the rest of the device state.
        _packet[bluetooth ? 3 : 1] = _effectFlags;
        const unsigned offset = bluetooth ? 6 : 4;
        _packet[offset] = _high;
        _packet[offset + 1] = _low;
        _packet[offset + 2] = _rgb.r;
        _packet[offset + 3] = _rgb.g;
        _packet[offset + 4] = _rgb.b;
    }
    if (bluetooth)
        store(std::span(_packet).last(4), crc(0xa2, std::span(_packet).first(74)));
    return std::span(_packet).first(bluetooth ? _packet.size() : usbLength);
}

} // namespace cc::input::detail
