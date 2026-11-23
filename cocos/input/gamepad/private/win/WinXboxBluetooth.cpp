#include "WinXboxBluetooth.h"

#include <algorithm>

namespace cc::input::detail {

WinXboxBluetooth::WinXboxBluetooth(const std::wstring& path, XboxBluetoothModel model, unsigned outputLength)
    : _reports(model)
{
    if (outputLength < XboxBluetoothOutputSize)
        return;
    _writer = openHid(path, GENERIC_WRITE, FILE_FLAG_OVERLAPPED);
    if (_writer)
        _event.reset(CreateEventW(nullptr, TRUE, FALSE, nullptr));
    if (_event)
        _buffer.resize(outputLength);
}

WinXboxBluetooth::~WinXboxBluetooth()
{
    stop();
}

bool WinXboxBluetooth::write(const XboxRumbleState& state)
{
    if (!_event)
        return false;
    const auto packet = state.bluetoothReport();
    std::ranges::copy(packet, _buffer.begin());
    return writeHid(_writer.get(), _event.get(), _buffer);
}

void WinXboxBluetooth::decode(WinInputEndpoint& device, std::span<const std::uint8_t> packet,
                              ReportSink& sink, ReportTime time)
{
    const auto sample = _reports.decode(packet);
    if (!sample)
        return;
    constexpr unsigned guide = static_cast<unsigned>(Button::Guide);
    std::array<RawChange, ButtonCount + AxisCount + 1> changes{};
    unsigned count = 0;
    const auto update = [&](RawKind kind, unsigned index, auto& current, auto value) {
        if (current != value)
        {
            current = value;
            changes[count++] = {kind, index, value};
        }
    };
    if (sample->controls)
    {
        const auto& controls = *sample->controls;
        for (unsigned i = 0; i < device.state.buttons.size(); ++i)
            if (i != guide)
                update(RawKind::Button, i, device.state.buttons[i], controls.buttons[i]);
        for (unsigned i = 0; i < device.state.axes.size(); ++i)
        {
            update(RawKind::Axis, i, device.state.axes[i], controls.axes[i]);
            device.state.axesKnown[i] = 1;
        }
        update(RawKind::Hat, 0, device.state.hats[0], controls.hat);
    }
    if (sample->guide)
        update(RawKind::Button, guide, device.state.buttons[guide], static_cast<std::uint8_t>(*sample->guide));

    if (sample->controls && !_seenControls)
    {
        _seenControls = true;
        device.sendBaseline(sink, time);
        count = 0;
    }
    if (sample->controls && !_feedback && _event && _probeAttempts < 3 && time.receivedNs >= _probeAt)
    {
        ++_probeAttempts;
        _probeAt = time.receivedNs + 250000000;
        if (write(_rumble))
        {
            _feedback = true;
            auto& caps = device.descriptor.capabilities;
            caps.features.set(static_cast<unsigned>(Feature::BodyRumble));
            caps.features.set(static_cast<unsigned>(Feature::TriggerRumble));
            sink.capabilitiesChanged(device.key, caps);
        }
    }
    std::optional<Power> power;
    const auto& previous = device.descriptor.power;
    if (sample->power && (sample->power->state != previous.state || sample->power->level != previous.level ||
                         sample->power->percent != previous.percent))
    {
        device.descriptor.power = *sample->power;
        power = sample->power;
    }
    if ((_seenControls && count) || power)
        sink.report(device.key, {std::span(changes).first(_seenControls ? count : 0), {}, {},
                                 power, ++device.cursor, time});
}

Error WinXboxBluetooth::submit(const OutputCommand& command)
{
    if (!_feedback)
        return Error::Unsupported;
    if (_stopPending && !std::holds_alternative<Stop>(command))
        return Error::Busy;
    auto next = _rumble;
    if (!next.apply(command, nowNs()))
        return Error::Unsupported;
    if (!write(next))
        return Error::BackendFailure;
    _rumble = next;
    _stopPending = false;
    return Error::None;
}

void WinXboxBluetooth::stop()
{
    if (_rumble.active())
    {
        const XboxRumbleState neutral;
        _stopPending = !write(neutral);
        if (_stopPending)
            _retryAt = nowNs() + XboxBluetoothRumbleIntervalNs;
        else
            _rumble = neutral;
    }
}

void WinXboxBluetooth::poll()
{
    const auto now = nowNs();
    if (now < _retryAt)
        return;
    if (_stopPending)
    {
        stop();
        return;
    }
    auto next = _rumble;
    if (next.expire(now))
    {
        if (write(next))
            _rumble = next;
        else
            _retryAt = now + XboxBluetoothRumbleIntervalNs;
    }
}

} // namespace cc::input::detail
