#pragma once

#include "input/gamepad/GamepadFrame.h"
#include "input/gamepad/GamepadMapping.h"

#include <functional>
#include <memory>
#include <utility>

namespace cc {
class Director;
}

namespace cc::input {

namespace detail {
class GamepadBackend;
}

// Close or destroy on the engine thread. A lease can outlive its device or service.
class Subscription {
public:
    Subscription(Subscription&& other) noexcept : _onClose(std::exchange(other._onClose, {})) {}

    Subscription& operator=(Subscription&& other) noexcept {
        if (this != &other) {
            close();
            _onClose = std::exchange(other._onClose, {});
        }
        return *this;
    }

    ~Subscription() { close(); }

    void close() noexcept {
        if (auto callback = std::exchange(_onClose, {})) {
            callback();
        }
    }

private:
    friend class GamepadService;

    explicit Subscription(std::function<void()> onClose) : _onClose(std::move(onClose)) {}

    std::function<void()> _onClose;
};

// Director owns the service. Public operations take place on the engine thread.
class CC_DLL GamepadService {
public:
    GamepadService();
    ~GamepadService();

    GamepadService(const GamepadService&) = delete;
    GamepadService& operator=(const GamepadService&) = delete;

    Frame frame() const noexcept;
    std::weak_ptr<const void> lifetimeToken() const noexcept;
    MappingResult setLocalBindings(DeviceId id, std::string_view layoutId,
                                   std::string_view bindingFields);
    MappingResult addGamepadMapping(std::string_view line,
                                    MappingSource source = MappingSource::Application);
    ImportReport importMappings(std::string_view utf8,
                                MappingSource source = MappingSource::Application);
    Result<std::string> mappingFor(DeviceId id) const;
    Error assignPlayer(DeviceId id, std::optional<unsigned> slot);
    Error clearPlayer(DeviceId id);
    Result<Subscription> subscribeSensor(DeviceId id, Sensor type, unsigned depth);
    Result<Subscription> watchRaw(DeviceId id);
    Result<CommandId> submit(DeviceId id, const OutputCommand& command);
    Result<CommandId> rumble(DeviceId id, float low, float high, unsigned durationMs);
    Result<CommandId> triggerRumble(DeviceId id, float left, float right, unsigned durationMs);
    Result<CommandId> rgb(DeviceId id, std::uint8_t r, std::uint8_t g, std::uint8_t b);
    Result<CommandId> playerLights(DeviceId id, unsigned mask);
    Result<CommandId> adaptiveTrigger(DeviceId id, Side side, TriggerMode mode, float start, float strength, float hz);
    Result<CommandId> stop(DeviceId id, Channel channel = Channel::All);
    Result<HapticPlayback> createHapticPlayback(DeviceId id, AudioSource& source);

private:
    friend class ::cc::Director;
    friend class GamepadTestAccess;

    enum class StartMode { Immediate, FirstFrame };
    GamepadService(std::unique_ptr<detail::GamepadBackend> backend, std::size_t reportCapacity,
                   std::size_t controlCapacity, StartMode startMode = StartMode::Immediate);
    void maintain(bool paused);
    void publish();
    void setFocused(bool focused);

    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // namespace cc::input
