#pragma once

#include "base/Ref.h"
#include "input/gamepad/GamepadService.h"

namespace cc::input::gamepad_lua {

class Pad {
public:
    Pad(const GamepadFrame& frame, const PadView& pad) : _stamp(frame.stamp()), _pad(&pad) {}
    const PadView* current() const noexcept { return _stamp.current() ? _pad : nullptr; }
    Result<const DeviceInfo*> info() const noexcept;
    Result<bool> mapped() const noexcept;
    Result<std::string_view> inputLayout() const noexcept;
    Result<std::string_view> mappingStatus() const noexcept;
    Result<std::uint32_t> mappingRevision() const noexcept;
    Result<std::optional<unsigned>> player() const noexcept;
    Result<bool> down(Button key) const noexcept;
    Result<bool> pressed(Button key) const noexcept;
    Result<bool> released(Button key) const noexcept;
    Result<std::string_view> label(Button key) const noexcept;
    Result<std::optional<float>> axis(Axis key) const noexcept;
    Result<std::optional<std::int16_t>> axisValue(Axis key) const noexcept;
    Result<bool> hasButton(Button key) const noexcept;
    Result<bool> hasAxis(Axis key) const noexcept;
    Result<bool> hasSensor(Sensor key) const noexcept;
    Result<bool> hasFeature(Feature key) const noexcept;
    Result<RawView> raw() const noexcept;
    Result<std::span<const Contact>> contacts() const noexcept;
    Result<std::optional<Motion>> latest(Sensor sensor) const noexcept;
    Result<Power> power() const noexcept;

private:
    FrameStamp _stamp;
    const PadView* _pad;
};

class Frame {
public:
    explicit Frame(const GamepadFrame& frame) : _stamp(frame.stamp()), _frame(&frame) {}
    const GamepadFrame* current() const noexcept { return _stamp.current() ? _frame : nullptr; }
    Result<double> tick() const noexcept;
    Result<std::span<const DeviceId>> devices() const noexcept;
    Result<std::optional<Pad>> find(DeviceId id) const noexcept;

private:
    FrameStamp _stamp;
    const GamepadFrame* _frame;
};

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
Error assignPlayer(DeviceId id, unsigned slot);
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
