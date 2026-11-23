#include "input/gamepad/GamepadService.h"

#include "FrameBuilder.h"

namespace cc::input {
using namespace detail;

class GamepadService::Impl {
public:
    Impl(std::unique_ptr<GamepadBackend> backend, std::size_t reports, std::size_t controls, StartMode startMode)
        : queue(reports, controls), backend(std::move(backend)),
          output(registry, queue, this->backend.get()), builder(registry, output, this->backend.get()),
          pendingStart(this->backend != nullptr)
    {
        if (startMode == StartMode::Immediate)
            startBackend();
    }

    ~Impl()
    {
        lifetime.reset();
        output.shutdownHaptics();
        queue.close();
        if (backend && !pendingStart)
        {
            backend->setActive(false);
            backend->stop();
        }
    }

    void startBackend()
    {
        if (!pendingStart)
            return;
        std::lock_guard lock(focusMutex);
        pendingStart = false;
        if (backend->start(queue) != Error::None)
            backend->stop();
        else if (!focused)
            backend->setActive(false);
    }

    void drain()
    {
        queue.drain(batch);
        builder.consume(batch);
        if (output.refreshHaptics())
        {
            queue.drain(batch);
            builder.consume(batch);
        }
    }

    bool stage(std::shared_ptr<MappingDatabase> database)
    {
        if (database->revision() != mappings->revision() && !queue.control(MappingFence{database}))
            return false;
        mappings = std::move(database);
        return true;
    }

    ReportQueue queue;
    std::unique_ptr<GamepadBackend> backend;
    DeviceRegistry registry;
    OutputRouter output;
    FrameBuilder builder;
    ReportBatch batch;
    std::shared_ptr<const MappingDatabase> mappings = std::make_shared<MappingDatabase>();
    std::shared_ptr<int> lifetime = std::make_shared<int>(0);
    std::mutex focusMutex;
    bool focused = true;
    bool pendingStart;
};

namespace {
MappingResult mappingError(std::string code, std::string message)
{
    return {MappingChange::Error, {{0, 0, std::move(code), std::move(message)}}};
}
}

GamepadService::GamepadService() : GamepadService(nullptr, 0, 256) {}

GamepadService::GamepadService(std::unique_ptr<GamepadBackend> backend, std::size_t reports,
                               std::size_t controls, StartMode startMode)
    : _impl(std::make_unique<Impl>(std::move(backend), reports, controls, startMode)) {}

GamepadService::~GamepadService() = default;

Frame GamepadService::frame() const noexcept
{
    return _impl->builder.frame();
}

std::weak_ptr<const void> GamepadService::lifetimeToken() const noexcept
{
    return _impl->lifetime;
}

void GamepadService::maintain(bool paused)
{
    _impl->startBackend();
    if (paused)
        _impl->drain();
    _impl->output.expire(nowNs());
}

void GamepadService::publish()
{
    _impl->drain();
    _impl->builder.publish(_impl->batch.cutoff);
}

void GamepadService::setFocused(bool focused)
{
    std::lock_guard lock(_impl->focusMutex);
    if (focused == _impl->focused)
        return;
    _impl->focused = focused;
    _impl->queue.focus(focused);
    _impl->output.setFocused(focused);
    if (_impl->backend && !_impl->pendingStart)
        _impl->backend->setActive(focused);
}

MappingResult GamepadService::addGamepadMapping(std::string_view line, MappingSource source)
{
    auto candidate = std::make_shared<MappingDatabase>(*_impl->mappings);
    auto result = candidate->add(line, source);
    if (result.change != MappingChange::Error && !_impl->stage(std::move(candidate)))
        return mappingError("queue-full", "Mapping change queue is full");
    return result;
}

ImportReport GamepadService::importMappings(std::string_view utf8, MappingSource source)
{
    auto candidate = std::make_shared<MappingDatabase>(*_impl->mappings);
    auto result = candidate->import(utf8, source);
    if (result.batchError == Error::None && !_impl->stage(std::move(candidate)))
    {
        result.added = result.replaced = 0;
        result.batchError = Error::QueueFull;
        result.diagnostics.push_back({0, 0, "queue-full", "Mapping change queue is full"});
    }
    return result;
}

MappingResult GamepadService::setLocalBindings(DeviceId id, std::string_view layoutId,
                                                std::string_view bindingFields)
{
    auto* device = _impl->registry.find(id);
    if (!device)
        return mappingError("disconnected", "The device is no longer connected");
    const auto& layout = device->endpoints.at(device->primary).descriptor.layout;
    if (layout.id != layoutId)
        return mappingError("layout-mismatch", "Use the current device layout for local bindings");
    auto selected = _impl->mappings->local(layout, bindingFields, device->view._info.name);
    if (selected.result.change == MappingChange::Unchanged)
    {
        if (!device->requestedLocal)
            return std::move(selected.result);
        if (!_impl->queue.control(LocalFence{id, std::string(layoutId), {}}))
            return mappingError("queue-full", "Mapping change queue is full");
        device->requestedLocal.reset();
        selected.result.change = MappingChange::Replaced;
        return std::move(selected.result);
    }
    if (selected.result.change != MappingChange::Added)
        return std::move(selected.result);
    if (device->requestedLocal && *device->requestedLocal == selected.selection)
    {
        selected.result.change = MappingChange::Unchanged;
        return std::move(selected.result);
    }
    selected.result.change = device->requestedLocal ? MappingChange::Replaced : MappingChange::Added;
    auto mapping = std::make_shared<MappingSelection>(std::move(selected.selection));
    if (!_impl->queue.control(LocalFence{id, std::string(layoutId), mapping}))
        return mappingError("queue-full", "Mapping change queue is full");
    device->requestedLocal = std::move(mapping);
    return std::move(selected.result);
}

Result<std::string> GamepadService::mappingFor(DeviceId id) const
{
    const auto result = frame().find(id);
    if (!result)
        return {{}, result.error};
    if (!*result.value)
        return {{}, Error::Disconnected};
    const auto& mapping = (*result.value)->_data->_exportedMapping;
    if (mapping.empty())
        return {{}, Error::NoMapping};
    return {mapping, Error::None};
}

Error GamepadService::assignPlayer(DeviceId id, std::optional<unsigned> slot)
{
    const auto status = _impl->registry.canReservePlayer(id, slot);
    if (status != Error::None)
        return status;
    auto& device = *_impl->registry.find(id);
    if (device.reservedPlayer == slot)
        return Error::None;
    if (!_impl->queue.control(PlayerFence{id, slot}))
        return Error::QueueFull;
    device.reservedPlayer = slot;
    return Error::None;
}

Error GamepadService::clearPlayer(DeviceId id)
{
    return assignPlayer(id, std::nullopt);
}

Result<Subscription> GamepadService::watchRaw(DeviceId id)
{
    auto* device = _impl->registry.find(id);
    if (!device)
        return {{}, Error::Disconnected};
    Subscription lease([this, lifetime = std::weak_ptr(_impl->lifetime), id]() noexcept {
        if (!lifetime.expired())
            if (auto* current = _impl->registry.find(id))
                --current->rawWatchers;
    });
    ++device->rawWatchers;
    return {std::move(lease), Error::None};
}

Result<Subscription> GamepadService::subscribeSensor(DeviceId id, Sensor type, unsigned depth)
{
    auto* device = _impl->registry.find(id);
    if (!device)
        return {{}, Error::Disconnected};
    if (static_cast<unsigned>(type) >= SensorCount || depth == 0 || depth > 4096)
        return {{}, Error::InvalidArgument};
    const auto endpoint = _impl->registry.owner(*device, type);
    if (!endpoint || !_impl->backend)
        return {{}, Error::Unsupported};
    auto& depths = device->sensorDepths[static_cast<unsigned>(type)];
    Subscription lease([this, lifetime = std::weak_ptr(_impl->lifetime), id, type, depth,
                        subscribedEndpoint = *endpoint]() noexcept {
        if (lifetime.expired())
            return;
        if (auto* current = _impl->registry.find(id))
        {
            auto& subscriptions = current->sensorDepths[static_cast<unsigned>(type)];
            if (const auto entry = subscriptions.find(depth); entry != subscriptions.end())
            {
                subscriptions.erase(entry);
                if (subscriptions.empty())
                {
                    // The native endpoint can temporarily lose a companion sensor while the pad stays connected.
                    const auto owner = _impl->registry.owner(*current, type).value_or(subscribedEndpoint);
                    _impl->backend->setSensor(owner, type, false);
                }
            }
        }
    });
    const bool first = depths.empty();
    depths.insert(depth);
    if (first)
    {
        const auto error = _impl->backend->setSensor(*endpoint, type, true);
        if (error != Error::None)
        {
            depths.clear();
            return {{}, error};
        }
    }
    return {std::move(lease), Error::None};
}

Result<CommandId> GamepadService::submit(DeviceId id, const OutputCommand& command)
{
    std::lock_guard lock(_impl->focusMutex);
    if (!_impl->registry.find(id))
        return {{}, Error::Disconnected};
    if (!_impl->focused)
        return {{}, Error::Busy};
    return _impl->output.submit(id, command);
}

Result<CommandId> GamepadService::rumble(DeviceId id, float low, float high, unsigned durationMs)
{
    return submit(id, Rumble{low, high, std::chrono::milliseconds(durationMs)});
}

Result<CommandId> GamepadService::triggerRumble(DeviceId id, float left, float right, unsigned durationMs)
{
    return submit(id, TriggerRumble{left, right, std::chrono::milliseconds(durationMs)});
}

Result<CommandId> GamepadService::rgb(DeviceId id, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return submit(id, Rgb{r, g, b});
}

Result<CommandId> GamepadService::playerLights(DeviceId id, unsigned mask)
{
    return submit(id, PlayerLights{mask});
}

Result<CommandId> GamepadService::adaptiveTrigger(DeviceId id, Side side, TriggerMode mode, float start, float strength, float hz)
{
    return submit(id, AdaptiveTrigger{side, mode, start, strength, hz});
}

Result<CommandId> GamepadService::stop(DeviceId id, Channel channel)
{
    return submit(id, Stop{channel});
}

Result<HapticPlayback> GamepadService::createHapticPlayback(DeviceId id, AudioSource& source)
{
    return _impl->output.createHapticPlayback(id, source);
}

} // namespace cc::input
