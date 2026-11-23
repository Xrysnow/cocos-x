#pragma once

#include "base/Ref.h"
#include "input/gamepad/GamepadService.h"

namespace cc::input::gamepad_lua {

struct NoResults {};

class LuaSubscription final : public Ref {
public:
    explicit LuaSubscription(Subscription subscription) : _subscription(std::move(subscription)) {}
    NoResults close() noexcept { _subscription.close(); return {}; }

private:
    Subscription _subscription;
};

class LuaHapticPlayback final : public Ref {
public:
    explicit LuaHapticPlayback(HapticPlayback playback) : _playback(std::move(playback)) {}
    Error play() { return _playback.play(); }
    Error pause() { return _playback.pause(); }
    Error resume() { return _playback.resume(); }
    Error stop() { return _playback.stop(); }
    Error seekTime(double seconds);
    Error setLooping(bool enabled);
    Error setIntensity(float intensity);
    HapticPlaybackSnapshot snapshot() const { return _playback.snapshot(); }
    Error close() noexcept;

private:
    HapticPlayback _playback;
};

Frame frame();
Result<MappingResult> addGamepadMapping(std::string_view line,
                                       MappingSource source = MappingSource::Application);
Result<ImportReport> importMappings(std::string_view text,
                                    MappingSource source = MappingSource::Application);
Result<MappingResult> setLocalBindings(DeviceId id, std::string_view layoutId,
                                       std::string_view fields);
Result<std::string> mappingFor(DeviceId id);
Error clearPlayer(DeviceId id);
Error assignPlayer(DeviceId id, std::optional<unsigned> slot);
Result<IntrusivePtr<LuaSubscription>> watchRaw(DeviceId id);
Result<IntrusivePtr<LuaSubscription>> subscribeSensor(DeviceId id, Sensor sensor,
                                                      unsigned depth);
Result<IntrusivePtr<LuaHapticPlayback>> createHapticPlayback(DeviceId id,
                                                             AudioSource* source);
Result<CommandId> rumble(DeviceId id, float low, float high, unsigned durationMs);
Result<CommandId> triggerRumble(DeviceId id, float left, float right, unsigned durationMs);
Result<CommandId> rgb(DeviceId id, std::uint8_t r, std::uint8_t g, std::uint8_t b);
Result<CommandId> playerLights(DeviceId id, unsigned mask);
Result<CommandId> adaptiveTrigger(DeviceId id, Side side, TriggerMode mode, float start, float strength, float hz);
Result<CommandId> stop(DeviceId id, Channel channel = Channel::All);

} // namespace cc::input::gamepad_lua
