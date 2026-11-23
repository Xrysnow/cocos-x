#pragma once

#include "input/gamepad/GamepadOutput.h"

#include <memory>
#include <string_view>

namespace cc::input {

struct RawView {
    std::span<const std::uint8_t> buttons;
    std::span<const std::uint8_t> hats;
    std::span<const std::int16_t> axes;
};

class CC_DLL PadView {
public:
    const DeviceInfo& info() const noexcept;
    const Capabilities& caps() const noexcept;
    bool mapped() const noexcept;
    std::string_view inputLayout() const noexcept;
    std::string_view mappingStatus() const noexcept;
    std::uint32_t mappingRevision() const noexcept;
    bool down(Button) const noexcept;
    bool pressed(Button) const noexcept;
    bool released(Button) const noexcept;
    std::optional<std::int16_t> axisValue(Axis) const noexcept;
    std::optional<float> axis(Axis) const noexcept;
    std::string_view label(Button) const noexcept;
    RawView raw() const noexcept;
    std::span<const Contact> contacts() const noexcept;
    std::optional<Motion> latest(Sensor) const noexcept;
    Power power() const noexcept;
    Link link() const noexcept;
    std::optional<unsigned> player() const noexcept;

private:
    friend class detail::DeviceRegistry;
    friend class detail::FrameBuilder;
    friend class GamepadService;

    DeviceInfo _info;
    Capabilities _caps;
    bool _mapped = false;
    std::string_view _mappingStatus = "RawOnly";
    std::uint32_t _mappingRevision = 0;
    std::string _exportedMapping;
    std::bitset<ButtonCount> _down;
    std::bitset<ButtonCount> _pressed;
    std::bitset<ButtonCount> _released;
    std::array<std::int16_t, AxisCount> _axes{};
    std::array<std::string, ButtonCount> _labels;
    std::vector<std::uint8_t> _rawButtons;
    std::vector<std::uint8_t> _rawHats;
    std::vector<std::int16_t> _rawAxes;
    std::vector<Contact> _contacts;
    std::array<std::optional<Motion>, SensorCount> _motion{};
    Power _power;
    Link _link = Link::Unknown;
    std::optional<unsigned> _player;
};

enum class EventKind { Device, Button, Axis, Raw, Contact, Motion, Power, InputGap, OutputDone };
enum class Change {
    Connected, Disconnected, MappingChanged, CapabilitiesChanged, BaselineReady,
    FocusLost, FocusGained, PlayerChanged
};
enum class RawKind { Button, Axis, Hat };
struct ButtonEdge { Button button; bool down; };
struct AxisChange { Axis axis; std::int16_t value; };
struct RawChange { RawKind kind; unsigned index; int value; };
struct DeviceChange { Change kind; std::uint32_t revision; };
enum class GapCause { QueueOverflow, DriverOverflow, SensorOverflow, ClockReset };
struct InputGap { GapCause cause; std::optional<unsigned> lostCount; };

using Payload = std::variant<DeviceChange, ButtonEdge, AxisChange, RawChange,
                             Contact, Motion, Power, InputGap, OutputDone>;

struct GamepadEvent {
    DeviceId device{};
    std::uint64_t reportSeq = 0;
    std::uint64_t receivedNs = 0;
    std::uint32_t subIndex = 0;
    std::optional<std::uint64_t> sourceNs;
    TimeQuality timeQuality = TimeQuality::ReceiveOnly;
    Reason reason = Reason::Physical;
    Payload payload;
};

// Keep a stamp with a borrowed view to check its lifetime on the engine thread.
class FrameStamp {
public:
    FrameStamp() = default;

    bool current() const noexcept {
        const auto epoch = _epoch.lock();
        return epoch && *epoch == _tick;
    }

private:
    friend class GamepadFrame;

    FrameStamp(const std::weak_ptr<const std::uint64_t>& epoch, std::uint64_t tick) noexcept
        : _epoch(epoch), _tick(tick) {}

    std::weak_ptr<const std::uint64_t> _epoch;
    std::uint64_t _tick = 0;
};

// All borrowed views are valid until the next publish or service destruction.
class CC_DLL GamepadFrame {
public:
    std::uint64_t tick() const noexcept;
    std::uint64_t cutoffNs() const noexcept;
    std::span<const DeviceId> devices() const noexcept;
    const PadView* find(DeviceId id) const noexcept;
    std::span<const GamepadEvent> events() const noexcept;
    FrameStamp stamp() const noexcept;

private:
    friend class detail::FrameBuilder;
    friend class GamepadService;

    std::uint64_t _tick = 0;
    std::uint64_t _cutoffNs = 0;
    std::vector<DeviceId> _devices;
    std::vector<PadView> _pads;
    std::vector<GamepadEvent> _events;
    std::weak_ptr<const std::uint64_t> _epoch;
};

} // namespace cc::input
