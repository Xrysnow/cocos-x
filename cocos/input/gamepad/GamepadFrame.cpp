#include "input/gamepad/GamepadFrame.h"

#include <algorithm>

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

const DeviceInfo& PadView::info() const noexcept {
    return _info;
}

const Capabilities& PadView::caps() const noexcept {
    return _caps;
}

bool PadView::mapped() const noexcept {
    return _mapped;
}

std::string_view PadView::inputLayout() const noexcept {
    return _info.layout;
}

std::string_view PadView::mappingStatus() const noexcept {
    return _mappingStatus;
}

std::uint32_t PadView::mappingRevision() const noexcept {
    return _mappingRevision;
}

bool PadView::down(Button button) const noexcept {
    return contains(_down, button);
}

bool PadView::pressed(Button button) const noexcept {
    return contains(_pressed, button);
}

bool PadView::released(Button button) const noexcept {
    return contains(_released, button);
}

std::optional<std::int16_t> PadView::axisValue(Axis axis) const noexcept {
    if (!_caps.has(axis)) {
        return std::nullopt;
    }
    return _axes[static_cast<std::size_t>(axis)];
}

std::optional<float> PadView::axis(Axis axis) const noexcept {
    const auto value = axisValue(axis);
    if (!value) {
        return std::nullopt;
    }
    const float scale = *value < 0 ? 32768.f : 32767.f;
    return *value / scale;
}

std::string_view PadView::label(Button button) const noexcept {
    const auto index = static_cast<std::size_t>(button);
    if (index >= _labels.size()) {
        return {};
    }
    if (!_labels[index].empty()) {
        return _labels[index];
    }
    return positionLabels[index];
}

RawView PadView::raw() const noexcept {
    return {_rawButtons, _rawHats, _rawAxes};
}

std::span<const Contact> PadView::contacts() const noexcept {
    return _contacts;
}

std::optional<Motion> PadView::latest(Sensor sensor) const noexcept {
    const auto index = static_cast<std::size_t>(sensor);
    return index < _motion.size() ? _motion[index] : std::nullopt;
}

Power PadView::power() const noexcept {
    return _power;
}

Link PadView::link() const noexcept {
    return _link;
}

std::optional<unsigned> PadView::player() const noexcept {
    return _player;
}

std::uint64_t GamepadFrame::tick() const noexcept {
    return _tick;
}

std::uint64_t GamepadFrame::cutoffNs() const noexcept {
    return _cutoffNs;
}

std::span<const DeviceId> GamepadFrame::devices() const noexcept {
    return _devices;
}

const PadView* GamepadFrame::find(DeviceId id) const noexcept {
    const auto pad = std::find_if(_pads.begin(), _pads.end(), [id](const PadView& candidate) {
        return candidate.info().id == id;
    });
    return pad != _pads.end() ? &*pad : nullptr;
}

std::span<const GamepadEvent> GamepadFrame::events() const noexcept {
    return _events;
}

FrameStamp GamepadFrame::stamp() const noexcept {
    return {_epoch, _tick};
}

} // namespace cc::input
