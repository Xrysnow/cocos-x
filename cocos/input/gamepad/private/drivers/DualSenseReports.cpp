#include "DualSenseReports.h"

#include <algorithm>
#include <bit>
#include <cmath>
#include <numbers>

namespace cc::input::detail {
namespace {

constexpr float radians = std::numbers::pi_v<float> / 180.f;
constexpr float gravity = 9.80665f;

std::uint32_t crc(std::uint8_t seed, std::span<const std::uint8_t> packet)
{
    std::uint32_t value = (0xffffffffu ^ seed);
    const auto octet = [&] {
        for (unsigned bit = 0; bit < 8; ++bit)
            value = (value >> 1) ^ ((value & 1u) ? 0xedb88320u : 0u);
    };
    octet();
    for (auto byte : packet)
    {
        value ^= byte;
        octet();
    }
    return ~value;
}

std::uint32_t little(std::span<const std::uint8_t> bytes)
{
    std::uint32_t value = 0;
    for (unsigned i = 0; i < bytes.size(); ++i)
        value |= static_cast<std::uint32_t>(bytes[i]) << (i * 8);
    return value;
}

void store(std::span<std::uint8_t> bytes, std::uint32_t value)
{
    for (auto& byte : bytes)
    {
        byte = static_cast<std::uint8_t>(value);
        value >>= 8;
    }
}

int signedSample(std::span<const std::uint8_t> bytes, unsigned offset)
{
    return std::bit_cast<std::int16_t>(static_cast<std::uint16_t>(little(bytes.subspan(offset, 2))));
}

std::int16_t stick(std::uint8_t value)
{
    const int centered = static_cast<int>(value) - 128;
    return static_cast<std::int16_t>(centered < 0 ? centered * 256 : centered * 32767 / 127);
}

void encodeTrigger(const AdaptiveTrigger& trigger, std::span<std::uint8_t> bytes)
{
    bytes[0] = 0x05;
    if (trigger.mode == TriggerMode::Off || trigger.strength <= 0)
        return;
    bytes[0] = trigger.mode == TriggerMode::Resistance ? 0x21 : 0x26;
    const auto start = static_cast<unsigned>(std::lround(trigger.start * 9));
    const auto strength = static_cast<unsigned>(std::max(1l, std::lround(trigger.strength * 8))) - 1;
    std::uint32_t force = 0;
    for (auto zone = start; zone < 10; ++zone)
        force |= strength << (3 * zone);
    store(bytes.subspan(1, 2), (0x3ffu << start) & 0x3ffu);
    store(bytes.subspan(3, 4), force);
    if (trigger.mode == TriggerMode::Vibration)
        bytes[9] = static_cast<std::uint8_t>(std::lround(trigger.hz));
}

} // namespace

std::optional<DualSenseCalibration> decodeDualSenseCalibration(DualSenseTransport transport,
                                                                std::span<const std::uint8_t> packet)
{
    if (packet.size() != 41 || packet.front() != 0x05)
        return {};
    if (transport == DualSenseTransport::Bluetooth && crc(0xa3, packet.first(37)) != little(packet.last(4)))
        return {};
    const auto speed = signedSample(packet, 19) + signedSample(packet, 21);
    if (speed <= 0)
        return {};
    DualSenseCalibration result;
    for (unsigned axis = 0; axis < 3; ++axis)
    {
        const auto bias = signedSample(packet, 1 + axis * 2);
        const auto counts = std::abs(signedSample(packet, 7 + axis * 4) - bias) +
                            std::abs(signedSample(packet, 9 + axis * 4) - bias);
        const auto positive = signedSample(packet, 23 + axis * 4);
        const auto negative = signedSample(packet, 25 + axis * 4);
        if (counts == 0 || positive <= negative)
            return {};
        result.bias[axis] = static_cast<float>(bias);
        result.scale[axis] = static_cast<float>(speed) * radians / static_cast<float>(counts);
        result.bias[3 + axis] = (positive + negative) / 2.f;
        result.scale[3 + axis] = 2 * gravity / static_cast<float>(positive - negative);
    }
    return result;
}

std::optional<DualSenseInput> decodeDualSenseInput(DualSenseTransport transport, std::span<const std::uint8_t> packet,
                                                   const std::optional<DualSenseCalibration>& calibration)
{
    if (packet.size() != (transport == DualSenseTransport::Usb ? 64 : 78) ||
        packet.front() != (transport == DualSenseTransport::Usb ? 0x01 : 0x31))
        return {};
    if (transport == DualSenseTransport::Bluetooth && crc(0xa1, packet.first(74)) != little(packet.last(4)))
        return {};
    const auto data = packet.subspan(transport == DualSenseTransport::Usb ? 1 : 2);
    DualSenseInput result;
    constexpr std::array positions{1, 3, 2, 6, 4, 12, 8, 9};
    const auto dir = data[7] & 15u;
    if (dir < positions.size())
        result.hat = static_cast<std::uint8_t>(positions[dir]);
    constexpr std::array<unsigned, 14> offsets{5, 6, 4, 7, 12, 16, 13, 14, 15, 8, 9, 17, 18, 10};
    for (unsigned i = 0; i < offsets.size(); ++i)
        result.buttons[i] = (data[7 + offsets[i] / 8] >> (offsets[i] % 8)) & 1u;
    for (unsigned i = 0; i < 4; ++i)
        result.axes[i] = stick(data[i]);
    for (unsigned i = 4; i < 6; ++i)
        result.axes[i] = static_cast<std::int16_t>(data[i] * 257 - 32768);
    for (unsigned i = 0; i < result.fingers.size(); ++i)
    {
        const auto point = data.subspan(32 + i * 4, 4);
        if ((point[0] & 0x80u) == 0)
            result.fingers[i] = Contact{0, static_cast<unsigned>(point[0] & 0x7fu), ContactPhase::Move,
                std::min(1.f, ((point[2] & 15) * 256 + point[1]) / 1919.f),
                std::min(1.f, (point[3] * 16 + (point[2] >> 4)) / 1079.f), {}};
    }
    result.motion[0].sensor = Sensor::Gyro;
    result.motion[1].sensor = Sensor::Accel;
    for (unsigned axis = 0; axis < 6; ++axis)
    {
        const auto raw = static_cast<float>(signedSample(data, 15 + axis * 2));
        const auto value = calibration ? (raw - calibration->bias[axis]) * calibration->scale[axis]
                                       : raw * (axis < 3 ? radians / 16.f : gravity / 8192.f);
        result.motion[axis / 3].xyz[axis % 3] = value;
    }
    const auto state = data[52] >> 4;
    const auto capacity = data[52] & 15u;
    if (state <= 2 && capacity <= 10)
        result.power = {state == 0 ? Power::State::OnBattery : state == 1 ? Power::State::Charging : Power::State::Charged,
                        state == 2 ? 100u : std::min(100u, capacity * 10u + 5u), {}};
    return result;
}

std::vector<Contact> dualSenseTouchChanges(const std::array<std::optional<Contact>, 2>& old,
                                           const std::array<std::optional<Contact>, 2>& next)
{
    std::vector<Contact> result;
    const auto find = [](const auto& points, unsigned id) {
        return std::ranges::find_if(points, [id](const auto& point) { return point && point->finger == id; });
    };
    for (const auto& point : old)
        if (point && find(next, point->finger) == next.end())
        {
            result.push_back(*point);
            result.back().phase = ContactPhase::Up;
        }
    for (const auto& point : next)
        if (point)
        {
            const auto previous = find(old, point->finger);
            if (previous == old.end() || (*previous)->x != point->x || (*previous)->y != point->y)
            {
                result.push_back(*point);
                result.back().phase = previous == old.end() ? ContactPhase::Down : ContactPhase::Move;
            }
        }
    return result;
}

bool DualSenseOutput::apply(const OutputCommand& command, std::uint64_t now)
{
    const auto unit = [](float value) { return std::isfinite(value) && 0 <= value && value <= 1; };
    if (const auto* rumble = std::get_if<Rumble>(&command))
    {
        if (!unit(rumble->low) || !unit(rumble->high) || rumble->duration.count() < 0 ||
            rumble->duration > std::chrono::seconds(60))
            return false;
        _low = static_cast<std::uint8_t>(std::lround(rumble->low * 255));
        _high = static_cast<std::uint8_t>(std::lround(rumble->high * 255));
        if (rumble->duration.count() == 0) _low = _high = 0;
        if (_low || _high) _expires = now + static_cast<std::uint64_t>(rumble->duration.count()) * 1000000;
        else _expires.reset();
    }
    else if (const auto* rgb = std::get_if<Rgb>(&command))
        _rgb = *rgb;
    else if (const auto* lights = std::get_if<PlayerLights>(&command); lights && lights->mask <= 31)
        _lights = *lights;
    else if (const auto* trigger = std::get_if<AdaptiveTrigger>(&command))
    {
        if ((trigger->side != Side::Left && trigger->side != Side::Right) ||
            (trigger->mode != TriggerMode::Off && (!unit(trigger->start) || !unit(trigger->strength))) ||
            (trigger->mode == TriggerMode::Vibration && (!std::isfinite(trigger->hz) || trigger->hz < 1 || trigger->hz > 255)) ||
            (trigger->mode != TriggerMode::Off && trigger->mode != TriggerMode::Resistance && trigger->mode != TriggerMode::Vibration))
            return false;
        _triggers[static_cast<unsigned>(trigger->side)] = *trigger;
    }
    else if (const auto* stop = std::get_if<Stop>(&command))
    {
        const auto channel = stop->channel;
        if (channel == Channel::All || channel == Channel::Body)
        {
            _low = _high = 0;
            _expires.reset();
        }
        if (channel == Channel::All || channel == Channel::AdaptiveLeft) _triggers[0] = {};
        if (channel == Channel::All || channel == Channel::AdaptiveRight) _triggers[1] = {};
        if (channel == Channel::All || channel == Channel::Lights) { _rgb = {}; _lights = {}; }
        return channel == Channel::All || channel == Channel::Body || channel == Channel::AdaptiveLeft ||
               channel == Channel::AdaptiveRight || channel == Channel::Lights;
    }
    else
        return false;
    return true;
}

bool DualSenseOutput::expire(std::uint64_t now)
{
    if (!_expires || now < *_expires)
        return false;
    _expires.reset();
    _low = _high = 0;
    return true;
}

std::span<const std::uint8_t> DualSenseOutput::encode(DualSenseTransport transport, unsigned usbLength)
{
    _packet.fill(0);
    const bool wireless = transport == DualSenseTransport::Bluetooth;
    if (!wireless && (usbLength < 48 || usbLength > 64))
        return {};
    _packet[0] = wireless ? 0x31 : 0x02;
    if (wireless)
    {
        _packet[1] = static_cast<std::uint8_t>((_sequence++ & 15u) << 4);
        _packet[2] = 0x10;
    }
    const auto data = std::span(_packet).subspan(wireless ? 3 : 1);
    data[0] = 0x0f; // Enable compatible vibration and independent trigger channels.
    data[1] = 0x14; // RGB and five player indicators.
    data[2] = _high;
    data[3] = _low;
    encodeTrigger(_triggers[1], data.subspan(10, 11));
    encodeTrigger(_triggers[0], data.subspan(21, 11));
    data[43] = static_cast<std::uint8_t>(_lights.mask);
    data[44] = _rgb.r;
    data[45] = _rgb.g;
    data[46] = _rgb.b;
    if (wireless)
        store(std::span(_packet).last(4), crc(0xa2, std::span(_packet).first(74)));
    return std::span(_packet).first(wireless ? _packet.size() : usbLength);
}

} // namespace cc::input::detail
