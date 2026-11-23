#pragma once

#include "input/gamepad/GamepadFrame.h"

namespace cc::input::detail {

struct PadState {
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

struct FrameData {
    std::uint64_t _cutoffNs = 0;
    std::vector<DeviceId> _devices;
    std::vector<PadState> _pads;
    std::vector<GamepadEvent> _events;
};

} // namespace cc::input::detail
