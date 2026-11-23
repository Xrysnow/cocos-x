#include "FrameData.h"

#include <algorithm>
#include <type_traits>

namespace cc::input {
namespace {

template<std::size_t Count, class Control>
bool contains(const std::bitset<Count>& mask, Control control) noexcept {
    const auto index = static_cast<std::size_t>(control);
    return index < Count && mask[index];
}

constexpr std::array<std::string_view, ButtonCount> positionLabels{
    "South", "East", "West", "North", "Back", "Guide", "Start", "Left Stick", "Right Stick",
    "Left Shoulder", "Right Shoulder", "D-pad Up", "D-pad Down", "D-pad Left", "D-pad Right",
    "Misc 1", "Right Paddle 1", "Left Paddle 1", "Right Paddle 2", "Left Paddle 2", "Touchpad Click",
    "Misc 2", "Misc 3", "Misc 4", "Misc 5", "Misc 6"
};

std::optional<std::int16_t> readAxis(const detail::PadState& state, Axis axis) noexcept {
    if (!state._caps.has(axis))
        return std::nullopt;
    return state._axes[static_cast<std::size_t>(axis)];
}

// Entries follow the alternatives in Payload.
constexpr std::array eventKinds{
    EventKind::Device, EventKind::Button, EventKind::Axis, EventKind::Raw,
    EventKind::Contact, EventKind::Motion, EventKind::Power, EventKind::InputGap, EventKind::OutputDone
};
static_assert(eventKinds.size() == std::variant_size_v<Payload>);

} // namespace

bool Capabilities::has(Button button) const noexcept {
    return contains(_buttons, button);
}

bool Capabilities::has(Axis axis) const noexcept {
    return contains(_axes, axis);
}

bool Capabilities::has(Sensor sensor) const noexcept {
    return contains(_sensors, sensor);
}

bool Capabilities::has(Feature feature) const noexcept {
    return contains(_features, feature);
}

std::span<const unsigned> Capabilities::fingersPerPad() const noexcept {
    return _fingersPerPad;
}

std::optional<float> Capabilities::nominalHz(Sensor sensor) const noexcept {
    const auto index = static_cast<std::size_t>(sensor);
    return index < _nominalHz.size() ? _nominalHz[index] : std::nullopt;
}

std::optional<TriggerLimits> Capabilities::triggerLimits(Side side) const noexcept {
    const auto index = static_cast<std::size_t>(side);
    return index < _triggerLimits.size() ? _triggerLimits[index] : std::nullopt;
}

std::uint32_t Capabilities::playerLightMask() const noexcept {
    return _playerLightMask;
}

template<class Read>
auto Pad::query(Read read) const noexcept {
    using Value = std::invoke_result_t<Read, const detail::PadState&>;
    if (!_stamp.current())
        return Result<Value>{{}, Error::StaleFrame};
    return Result<Value>{read(*_data)};
}

Result<const DeviceInfo*> Pad::info() const noexcept {
    return query([](const detail::PadState& state) { return &state._info; });
}

Result<bool> Pad::mapped() const noexcept {
    return query([](const detail::PadState& state) { return state._mapped; });
}

Result<std::string_view> Pad::inputLayout() const noexcept {
    return query([](const detail::PadState& state) { return std::string_view{state._info.layout}; });
}

Result<std::string_view> Pad::mappingStatus() const noexcept {
    return query([](const detail::PadState& state) { return state._mappingStatus; });
}

Result<std::uint32_t> Pad::mappingRevision() const noexcept {
    return query([](const detail::PadState& state) { return state._mappingRevision; });
}

Result<bool> Pad::down(Button button) const noexcept {
    return query([button](const detail::PadState& state) { return contains(state._down, button); });
}

Result<bool> Pad::pressed(Button button) const noexcept {
    return query([button](const detail::PadState& state) { return contains(state._pressed, button); });
}

Result<bool> Pad::released(Button button) const noexcept {
    return query([button](const detail::PadState& state) { return contains(state._released, button); });
}

Result<RawView> Pad::raw() const noexcept {
    return query([](const detail::PadState& state) { return RawView{state._rawButtons, state._rawHats, state._rawAxes}; });
}

Result<std::span<const Contact>> Pad::contacts() const noexcept {
    return query([](const detail::PadState& state) { return std::span<const Contact>{state._contacts}; });
}

Result<Power> Pad::power() const noexcept {
    return query([](const detail::PadState& state) { return state._power; });
}

Result<Link> Pad::link() const noexcept {
    return query([](const detail::PadState& state) { return state._link; });
}

Result<std::optional<unsigned>> Pad::player() const noexcept {
    return query([](const detail::PadState& state) { return state._player; });
}

Result<bool> Pad::hasButton(Button key) const noexcept {
    return query([key](const detail::PadState& state) { return state._caps.has(key); });
}

Result<bool> Pad::hasAxis(Axis key) const noexcept {
    return query([key](const detail::PadState& state) { return state._caps.has(key); });
}

Result<bool> Pad::hasSensor(Sensor key) const noexcept {
    return query([key](const detail::PadState& state) { return state._caps.has(key); });
}

Result<bool> Pad::hasFeature(Feature key) const noexcept {
    return query([key](const detail::PadState& state) { return state._caps.has(key); });
}

Result<std::span<const unsigned>> Pad::fingersPerPad() const noexcept {
    return query([](const detail::PadState& state) { return state._caps.fingersPerPad(); });
}

Result<std::optional<float>> Pad::nominalHz(Sensor sensor) const noexcept {
    return query([sensor](const detail::PadState& state) { return state._caps.nominalHz(sensor); });
}

Result<std::optional<TriggerLimits>> Pad::triggerLimits(Side side) const noexcept {
    return query([side](const detail::PadState& state) { return state._caps.triggerLimits(side); });
}

Result<std::uint32_t> Pad::playerLightMask() const noexcept {
    return query([](const detail::PadState& state) { return state._caps.playerLightMask(); });
}

Result<std::optional<std::int16_t>> Pad::axisValue(Axis axis) const noexcept {
    return query([axis](const detail::PadState& state) { return readAxis(state, axis); });
}

Result<std::optional<float>> Pad::axis(Axis axis) const noexcept {
    return query([axis](const detail::PadState& state) -> std::optional<float> {
        const auto value = readAxis(state, axis);
        if (!value)
            return std::nullopt;
        const float scale = *value < 0 ? 32768.f : 32767.f;
        return *value / scale;
    });
}

Result<std::string_view> Pad::label(Button button) const noexcept {
    return query([button](const detail::PadState& state) -> std::string_view {
        const auto index = static_cast<std::size_t>(button);
        if (index >= state._labels.size())
            return {};
        if (!state._labels[index].empty())
            return state._labels[index];
        return positionLabels[index];
    });
}

Result<std::optional<Motion>> Pad::latest(Sensor sensor) const noexcept {
    return query([sensor](const detail::PadState& state) {
        const auto index = static_cast<std::size_t>(sensor);
        return index < state._motion.size() ? state._motion[index] : std::nullopt;
    });
}

Frame::TimeResult Frame::tick() const noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    return {_stamp.tick};
}

Frame::TimeResult Frame::cutoffNs() const noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    return {_data->_cutoffNs};
}

Result<std::span<const DeviceId>> Frame::devices() const noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    return {std::span<const DeviceId>{_data->_devices}};
}

Result<std::optional<Pad>> Frame::find(DeviceId id) const noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    const auto pad = std::ranges::find(_data->_pads, id, [](const detail::PadState& state) {
        return state._info.id;
    });
    if (pad == _data->_pads.end())
        return {std::optional<Pad>{}};
    return {std::optional{Pad(&*pad, _stamp)}};
}

Result<EventCursor> Frame::events() const noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    return {EventCursor(_data, _stamp)};
}

Result<std::optional<GamepadEvent>> EventCursor::next() noexcept {
    if (!_stamp.current())
        return {{}, Error::StaleFrame};
    if (_index == _data->_events.size())
        return {std::optional<GamepadEvent>{}};

    auto event = _data->_events[_index++];
    event.kind = eventKinds[event.payload.index()];
    event.order = _index;
    const auto cutoff = _data->_cutoffNs;
    const double delta = event.receivedNs >= cutoff ? static_cast<double>(event.receivedNs - cutoff)
                                                  : -static_cast<double>(cutoff - event.receivedNs);
    event.offsetUs = delta / 1000.0;
    return {std::optional{std::move(event)}};
}

} // namespace cc::input
