#include "FrameBuilder.h"

#include <algorithm>

namespace cc::input::detail {
namespace {
template<class T>
bool setRaw(std::vector<T>& values, unsigned index, int value, int minimum, int maximum)
{
    if (index >= values.size() || value < minimum || value > maximum || values[index] == value)
        return false;
    values[index] = static_cast<T>(value);
    return true;
}

std::optional<EndpointKey> touchOwner(const Device& device)
{
    for (const auto& [key, endpoint] : device.endpoints)
        if (!endpoint.descriptor.capabilities.fingersPerPad.empty())
            return key;
    return std::nullopt;
}

}

FrameBuilder::FrameBuilder(DeviceRegistry& registry, OutputRouter& output, GamepadBackend* backend)
    : _registry(registry), _output(output), _backend(backend),
      _mapping(std::make_shared<MappingDatabase>())
{
    _frame._epoch = _epoch;
    _events.reserve(256);
    _frame._events.reserve(256);
}

void FrameBuilder::consume(ReportBatch& batch)
{
    for (auto& record : batch.records)
    {
        _record = &record;
        _subIndex = 0;
        std::visit([this](auto& item) { apply(item); }, record.data);
    }
    _record = nullptr;
}

void FrameBuilder::publish(std::uint64_t cutoff)
{
    ++*_epoch;
    _frame._tick = *_epoch;
    _frame._cutoffNs = cutoff;
    _frame._events.swap(_events);
    _events.clear();
    _frame._devices.clear();
    _frame._pads.resize(_registry.devices().size());
    std::size_t index = 0;
    for (auto& [id, device] : _registry.devices())
    {
        _frame._devices.push_back(id);
        auto& pad = _frame._pads[index++];
        // Reuse frame storage in steady state, including raw vectors.
        pad._info = device.view._info;
        pad._caps = device.view._caps;
        pad._mapped = device.view._mapped;
        pad._mappingStatus = device.view._mappingStatus;
        pad._mappingRevision = device.view._mappingRevision;
        pad._exportedMapping = device.mapping.exported;
        pad._down = device.view._down;
        pad._pressed = device.view._pressed;
        pad._released = device.view._released;
        pad._axes = device.view._axes;
        pad._labels = device.view._labels;
        pad._rawButtons = device.raw.buttons;
        pad._rawHats = device.raw.hats;
        pad._rawAxes = device.raw.axes;
        pad._contacts = device.view._contacts;
        pad._motion = device.view._motion;
        pad._power = device.view._power;
        pad._link = device.view._link;
        pad._player = device.view._player;
        device.view._pressed.reset();
        device.view._released.reset();
    }
}

void FrameBuilder::emit(DeviceId id, Reason reason, Payload payload)
{
    _events.push_back({id, _record->seq, _record->time.receivedNs, _subIndex++,
        _record->time.sourceNs, _record->time.quality, reason, std::move(payload)});
}

void FrameBuilder::deviceChange(Device& device, Change change, Reason reason)
{
    emit(device.view._info.id, reason, DeviceChange{change, device.view._mappingRevision});
}

void FrameBuilder::refreshMapping(Device& device, Reason reason, bool force)
{
    const auto& rawLayout = device.endpoints.at(device.primary).descriptor.layout;
    auto selected = device.local ? *device.local : _mapping->select(rawLayout, device.view._info.name);
    if (!force && device.mapping == selected)
        return;
    const bool wasSuppressed = device.suppressedButtons.any();
    if (reason == Reason::Remap)
        release(device, reason);
    device.mapping = std::move(selected);
    auto& view = device.view;
    ++view._mappingRevision;
    view._caps._buttons = device.mapping.plan.buttons();
    view._caps._axes = device.mapping.plan.axes();
    view._mapped = view._caps._buttons.any() || view._caps._axes.any();
    view._info.mappingName = device.mapping.name;
    view._mappingStatus = device.mapping.status;
    for (unsigned button = 0; button < ButtonCount; ++button)
        view._labels[button] = device.mapping.plan.label(static_cast<Button>(button));
    if (reason == Reason::Remap)
        deviceChange(device, Change::MappingChanged, reason);
    evaluate(device, reason, true, wasSuppressed);
}

void FrameBuilder::evaluate(Device& device, Reason reason, bool baseline, bool suppressHeld,
                            std::span<const RawChange> changes)
{
    if (!_active || device.endpoints.at(device.primary).awaitingBaseline)
        device.logical = {};
    else if (baseline)
        device.mapping.plan.evaluate(device.raw, device.logical);
    else
        device.mapping.plan.update(device.raw, changes, device.logical);
    auto next = device.logical;
    auto& view = device.view;
    if (suppressHeld)
        device.suppressedButtons = next.buttons;
    device.suppressedButtons &= next.buttons;
    next.buttons &= ~device.suppressedButtons;
    if (!baseline)
    {
        const auto changed = view._down ^ next.buttons;
        for (unsigned i = 0; i < ButtonCount; ++i)
        {
            if (!changed[i])
                continue;
            const bool down = next.buttons[i];
            if (down && reason == Reason::Physical)
                view._pressed[i] = true;
            if (!down)
                view._released[i] = true;
            emit(view._info.id, reason, ButtonEdge{static_cast<Button>(i), down});
        }
        for (unsigned i = 0; i < AxisCount; ++i)
            if (view._axes[i] != next.axes[i])
                emit(view._info.id, reason, AxisChange{static_cast<Axis>(i), next.axes[i]});
    }
    view._down = next.buttons;
    view._axes = next.axes;
}

void FrameBuilder::release(Device& device, Reason reason)
{
    auto& view = device.view;
    for (unsigned i = 0; i < ButtonCount; ++i)
    {
        if (view._down[i])
        {
            view._released[i] = true;
            emit(view._info.id, reason, ButtonEdge{static_cast<Button>(i), false});
        }
    }
    view._down.reset();
    for (unsigned i = 0; i < AxisCount; ++i)
        if (view._axes[i] != 0)
            emit(view._info.id, reason, AxisChange{static_cast<Axis>(i), 0});
    view._axes.fill(0);
    for (auto contact : view._contacts)
    {
        contact.phase = ContactPhase::Cancel;
        emit(view._info.id, reason, contact);
    }
    view._contacts.clear();
    view._motion.fill({});
}

void FrameBuilder::releaseAuxiliary(Device& device, EndpointKey key, Reason reason)
{
    auto& view = device.view;
    if (touchOwner(device) == key)
    {
        for (auto contact : view._contacts)
        {
            contact.phase = ContactPhase::Cancel;
            emit(view._info.id, reason, contact);
        }
        view._contacts.clear();
    }
    for (unsigned i = 0; i < SensorCount; ++i)
        if (_registry.owner(device, static_cast<Sensor>(i)) == key)
            view._motion[i].reset();
}

void FrameBuilder::apply(Attach& attach)
{
    const auto& descriptor = attach.descriptor;
    if (!descriptor.auxiliary && !DeviceRegistry::validBaseline(descriptor.layout, attach.initial.state))
        return;
    const auto key = attach.key;
    const auto prior = _registry.previousGeneration(key);
    if (!_registry.acceptGeneration(key))
        return;
    _output.rescanHaptics();
    auto* associated = _registry.associated(key, descriptor);
    auto* previous = prior ? _registry.find(*prior) : nullptr;
    if (previous && previous != associated)
        remove(*previous, *prior, Reason::Disconnect);
    if (descriptor.auxiliary)
    {
        if (associated)
        {
            if (previous == associated && *prior != associated->primary)
                remove(*associated, *prior, Reason::Resync);
            _registry.addEndpoint(*associated, key, std::move(attach.descriptor), attach.initial.cursor);
            deviceChange(*associated, Change::CapabilitiesChanged, Reason::Configuration);
        }
        return;
    }
    if (associated)
    {
        release(*associated, Reason::Resync);
        for (auto notice : _output.cancel(associated->view._info.id, associated->primary))
            apply(notice);
        _registry.replacePrimary(*associated, key, std::move(attach.descriptor), std::move(attach.initial));
        refreshMapping(*associated, Reason::Remap, true);
        deviceChange(*associated, Change::BaselineReady, Reason::Resync);
    }
    else if (auto* device = _registry.create(key, std::move(attach.descriptor), std::move(attach.initial)))
    {
        refreshMapping(*device, Reason::Connect, true);
        deviceChange(*device, Change::Connected, Reason::Connect);
    }
}

void FrameBuilder::apply(Report& report)
{
    auto* device = _registry.find(report.key);
    if (!device)
        return;
    auto& endpoint = device->endpoints.at(report.key);
    if (endpoint.awaitingBaseline || report.cursor <= endpoint.cursor)
        return;
    endpoint.cursor = report.cursor;

    if (report.key == device->primary)
    {
        auto& raw = device->raw;
        bool updated = false;
        for (auto change : report.changes)
        {
            bool changed = false;
            switch (change.kind)
            {
            case RawKind::Button:
                changed = setRaw(raw.buttons, change.index, change.value, 0, 1);
                break;
            case RawKind::Hat:
                changed = setRaw(raw.hats, change.index, change.value, 0, 15);
                break;
            case RawKind::Axis:
                changed = setRaw(raw.axes, change.index, change.value, -32768, 32767);
                if (change.index < raw.axesKnown.size() && change.value >= -32768 && change.value <= 32767)
                    changed |= std::exchange(raw.axesKnown[change.index], std::uint8_t{1}) == 0;
                break;
            }
            updated |= changed;
            if (_active && changed && device->rawWatchers != 0)
                emit(device->view._info.id, Reason::Physical, change);
        }
        if (_active && updated)
            evaluate(*device, Reason::Physical, false, false, report.changes.view());
    }
    if (_active)
        refreshAuxiliary(*device, report);
}

void FrameBuilder::refreshAuxiliary(Device& device, Report& report)
{
    auto& view = device.view;
    const auto& endpoint = device.endpoints.at(report.key).descriptor.capabilities;
    if (!report.contacts.view().empty() && touchOwner(device) == report.key)
    {
        for (auto contact : report.contacts)
        {
            if (contact.pad >= endpoint.fingersPerPad.size())
                continue;
            auto existing = std::ranges::find_if(view._contacts, [&](const Contact& value) {
                return contact.pad == value.pad && contact.finger == value.finger;
            });
            const auto phase = contact.phase;
            if (phase == ContactPhase::Down && existing == view._contacts.end())
            {
                const auto count = std::ranges::count(view._contacts, contact.pad, &Contact::pad);
                if (static_cast<unsigned>(count) >= endpoint.fingersPerPad[contact.pad])
                    continue;
                view._contacts.push_back(contact);
            }
            else if (existing == view._contacts.end())
                continue;
            else if (phase == ContactPhase::Up || phase == ContactPhase::Cancel)
                view._contacts.erase(existing);
            else
                *existing = contact;
            emit(view._info.id, Reason::Physical, contact);
        }
    }
    for (auto motion : report.motion)
    {
        if (_registry.owner(device, motion.sensor) == report.key &&
            !device.sensorDepths[static_cast<unsigned>(motion.sensor)].empty())
        {
            view._motion[static_cast<unsigned>(motion.sensor)] = motion;
            emit(view._info.id, Reason::Physical, motion);
        }
    }
    if (report.key == device.primary && report.power)
    {
        const auto& power = *report.power;
        if (power.state != view._power.state || power.percent != view._power.percent ||
            power.level != view._power.level)
        {
            view._power = power;
            emit(view._info.id, Reason::Physical, power);
        }
    }
}

void FrameBuilder::apply(Baseline& baseline)
{
    auto* device = _registry.find(baseline.key);
    if (!device)
        return;
    auto& endpoint = device->endpoints.at(baseline.key);
    const bool primary = device->primary == baseline.key;
    if (baseline.snapshot.cursor < endpoint.cursor ||
        (primary && !DeviceRegistry::validBaseline(endpoint.descriptor.layout, baseline.snapshot.state)))
        return;
    endpoint.cursor = baseline.snapshot.cursor;
    endpoint.awaitingBaseline = false;
    if (primary)
    {
        device->raw = std::move(baseline.snapshot.state);
        evaluate(*device, Reason::Resync, true, endpoint.focusBaseline);
    }
    const auto reason = endpoint.focusBaseline ? Reason::FocusGained : Reason::Resync;
    endpoint.focusBaseline = false;
    deviceChange(*device, Change::BaselineReady, reason);
}

void FrameBuilder::apply(CapabilityUpdate& update)
{
    if (auto* device = _registry.find(update.key))
    {
        for (auto notice : _output.cancel(device->view._info.id, update.key, HapticStopReason::None))
            apply(notice);
        device->endpoints.at(update.key).descriptor.capabilities = std::move(update.capabilities);
        _registry.refreshCapabilities(*device);
        deviceChange(*device, Change::CapabilitiesChanged, Reason::Configuration);
    }
}

void FrameBuilder::apply(HapticCapabilityUpdate& update)
{
    if (auto* device = _registry.find(update.device))
    {
        if (update.owner && !device->endpoints.contains(*update.owner))
            return;
        if (device->hapticOwner == update.owner)
            return;
        device->hapticOwner = update.owner;
        _registry.refreshCapabilities(*device);
        deviceChange(*device, Change::CapabilitiesChanged, Reason::Configuration);
    }
}

void FrameBuilder::remove(Device& device, EndpointKey key, Reason reason)
{
    const auto id = device.view._info.id;
    const bool primary = key == device.primary;
    for (auto notice : _output.cancel(id, primary ? std::nullopt : std::optional{key}))
        apply(notice);
    if (primary)
    {
        release(device, reason);
        deviceChange(device, Change::Disconnected, reason);
        _registry.erase(id);
    }
    else
    {
        releaseAuxiliary(device, key, reason);
        _registry.removeEndpoint(device, key);
        deviceChange(device, Change::CapabilitiesChanged, reason);
    }
}

void FrameBuilder::apply(Detach& detach)
{
    if (auto* device = _registry.find(detach.key))
        remove(*device, detach.key, Reason::Disconnect);
}

void FrameBuilder::apply(Desync& desync)
{
    if (auto* device = _registry.find(desync.key))
    {
        emit(device->view._info.id, Reason::Resync, desync.gap);
        if (device->primary == desync.key)
            release(*device, Reason::Resync);
        else
            releaseAuxiliary(*device, desync.key, Reason::Resync);
        device->endpoints.at(desync.key).awaitingBaseline = true;
        if (_backend)
            _backend->requestBaseline(desync.key);
    }
}

void FrameBuilder::requestBaselines(Device& device)
{
    if (_backend)
        for (auto& [key, endpoint] : device.endpoints)
        {
            endpoint.awaitingBaseline = true;
            endpoint.focusBaseline = true;
            _backend->requestBaseline(key);
        }
}

void FrameBuilder::apply(Focus& focus)
{
    _active = focus.active;
    const auto reason = _active ? Reason::FocusGained : Reason::FocusLost;
    if (_registry.devices().empty())
        emit(DeviceId{}, reason, DeviceChange{_active ? Change::FocusGained : Change::FocusLost, 0});
    for (auto& [id, device] : _registry.devices())
    {
        if (_active)
        {
            evaluate(device, reason, true, true);
            requestBaselines(device);
        }
        else
        {
            device.view._pressed.reset();
            release(device, reason);
            for (auto notice : _output.cancel(id, {}, HapticStopReason::FocusLost))
                apply(notice);
        }
        deviceChange(device, _active ? Change::FocusGained : Change::FocusLost, reason);
    }
}

void FrameBuilder::apply(MappingFence& fence)
{
    _mapping = std::move(fence.database);
    for (auto& [id, device] : _registry.devices())
        refreshMapping(device, Reason::Remap);
}

void FrameBuilder::apply(LocalFence& fence)
{
    if (auto* device = _registry.find(fence.id); device && device->view._info.layout == fence.layout)
    {
        device->local = std::move(fence.selection);
        refreshMapping(*device, Reason::Remap);
    }
}

void FrameBuilder::apply(PlayerFence& fence)
{
    if (auto* device = _registry.find(fence.id); device && device->view._player != fence.slot)
    {
        device->view._player = fence.slot;
        if (_backend)
            _backend->setClaimed(device->primary, fence.slot.has_value());
        deviceChange(*device, Change::PlayerChanged, Reason::Configuration);
    }
}

void FrameBuilder::apply(NativeCompletion& completion)
{
    if (auto notice = _output.complete(completion))
        apply(*notice);
}

void FrameBuilder::apply(OutputNotice& notice)
{
    emit(notice.device, Reason::Command, notice.done);
}

void FrameBuilder::apply(TopologyLoss&)
{
    emit(DeviceId{}, Reason::Resync, InputGap{GapCause::QueueOverflow, std::nullopt});
    while (!_registry.devices().empty())
    {
        auto& device = _registry.devices().begin()->second;
        remove(device, device.primary, Reason::Resync);
    }
    if (_backend)
        _backend->requestTopology();
}

void FrameBuilder::apply(TopologySnapshot& snapshot)
{
    // A fresh enumeration can contain auxiliary endpoints before their input owner.
    for (auto& endpoint : snapshot.endpoints)
        if (!endpoint.descriptor.auxiliary)
            apply(endpoint);
    for (auto& endpoint : snapshot.endpoints)
        if (endpoint.descriptor.auxiliary)
            apply(endpoint);
}

} // namespace cc::input::detail
