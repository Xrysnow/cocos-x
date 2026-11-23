#pragma once

#include "input/gamepad/GamepadOutput.h"

#include <cstddef>
#include <memory>
#include <string_view>
#include <utility>

namespace cc::input {

struct RawView {
    std::span<const std::uint8_t> buttons;
    std::span<const std::uint8_t> hats;
    std::span<const std::int16_t> axes;
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
    EventKind kind = EventKind::Device;
    std::size_t order = 0;
    double offsetUs = 0;
};

namespace detail {
struct PadState;
struct FrameData;

struct FrameStamp {
    bool current() const noexcept {
        const auto live = epoch.lock();
        return live && *live == tick;
    }

    std::weak_ptr<const std::uint64_t> epoch;
    std::uint64_t tick;
};
} // namespace detail

// Queries report StaleFrame after the next publish or service destruction.
// Borrowed data returned by a successful query is valid for that same interval.
class CC_DLL Pad {
public:
    Result<const DeviceInfo*> info() const noexcept;
    Result<bool> mapped() const noexcept;
    Result<std::string_view> inputLayout() const noexcept;
    Result<std::string_view> mappingStatus() const noexcept;
    Result<std::uint32_t> mappingRevision() const noexcept;
    Result<bool> down(Button) const noexcept;
    Result<bool> pressed(Button) const noexcept;
    Result<bool> released(Button) const noexcept;
    Result<std::optional<std::int16_t>> axisValue(Axis) const noexcept;
    Result<std::optional<float>> axis(Axis) const noexcept;
    Result<std::string_view> label(Button) const noexcept;
    Result<RawView> raw() const noexcept;
    Result<std::span<const Contact>> contacts() const noexcept;
    Result<std::optional<Motion>> latest(Sensor) const noexcept;
    Result<Power> power() const noexcept;
    Result<Link> link() const noexcept;
    Result<std::optional<unsigned>> player() const noexcept;
    Result<bool> hasButton(Button) const noexcept;
    Result<bool> hasAxis(Axis) const noexcept;
    Result<bool> hasSensor(Sensor) const noexcept;
    Result<bool> hasFeature(Feature) const noexcept;
    Result<std::span<const unsigned>> fingersPerPad() const noexcept;
    Result<std::optional<float>> nominalHz(Sensor) const noexcept;
    Result<std::optional<TriggerLimits>> triggerLimits(Side) const noexcept;
    Result<std::uint32_t> playerLightMask() const noexcept;

private:
    friend class Frame;
    friend class GamepadService;

    Pad(const detail::PadState* data, const detail::FrameStamp& stamp) noexcept : _data(data), _stamp(stamp) {}
    template<class Read> auto query(Read read) const noexcept;

    const detail::PadState* _data;
    detail::FrameStamp _stamp;
};

class CC_DLL EventCursor {
public:
    Result<std::optional<GamepadEvent>> next() noexcept;

private:
    friend class Frame;

    EventCursor(const detail::FrameData* data, const detail::FrameStamp& stamp) noexcept : _data(data), _stamp(stamp) {}

    const detail::FrameData* _data;
    detail::FrameStamp _stamp;
    std::size_t _index = 0;
};

class CC_DLL Frame {
public:
    using TimeResult = Result<std::uint64_t>;

    TimeResult tick() const noexcept;
    TimeResult cutoffNs() const noexcept;
    Result<std::span<const DeviceId>> devices() const noexcept;
    Result<std::optional<Pad>> find(DeviceId id) const noexcept;
    Result<EventCursor> events() const noexcept;

private:
    friend class detail::FrameBuilder;

    Frame(const detail::FrameData* data, detail::FrameStamp stamp) noexcept : _data(data), _stamp(std::move(stamp)) {}

    const detail::FrameData* _data;
    detail::FrameStamp _stamp;
};

} // namespace cc::input
