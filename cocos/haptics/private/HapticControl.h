#pragma once
#include "haptics/private/MobileHaptics.h"
#include "input/gamepad/private/core/ReportQueue.h"
#include "audio/output/RealtimeHaptics.h"
#include <functional>

namespace cc::haptics::detail
{
using Endpoint    = input::detail::EndpointKey;
using NativeError = input::Error;
struct PcmSource
{
    Endpoint hid;
    std::function<NativeError()> enable;
    std::function<NativeError(StopReason)> silence;
    std::function<bool()> ended;
};

class HapticControl
{
public:
    HapticControl(input::detail::GamepadBackend*, input::detail::ReportQueue&);
    ~HapticControl();
    static HapticControl& get(HapticService& service) { return *service._control; }
    void shutdown();
    void resetScopes();
    void focused(bool active);
    void platformFocus(bool active);
    void forwarding(bool enabled);
    void compatVibrate(float seconds);
    void publishMobile(std::shared_ptr<MobileOutput>, std::optional<input::DeviceId> device = {}, Endpoint key = {});
    Result<OperationId> rawCommand(std::uint64_t lease, MobileCommand command);
    Result<OperationId> stopPlayer(std::uint64_t lease, RawPlayerId player);
    std::weak_ptr<HapticControl> weak(HapticService& service) { return service._control; }
    void publishGamepad(input::DeviceId, Endpoint);
    void pairPcm(input::DeviceId, std::optional<AudioEndpointId>);
    Status preparePcm(TargetId);
    Status setPcmModeTiming(TargetId, const PcmModeTiming&);
    void removeGamepad(input::DeviceId, bool disconnected);
    bool retiring(input::DeviceId) const;
    NativeError legacy(
        input::DeviceId, const input::OutputCommand&, bool zeroRumble, std::function<void(NativeError)> completed);
    NativeError playPcm(input::DeviceId, std::shared_ptr<PcmSource>);
    NativeError stopPcm(input::DeviceId, const std::shared_ptr<PcmSource>&, StopReason reason);
    bool ownsPcm(input::DeviceId, const std::shared_ptr<PcmSource>&) const;

    std::vector<TargetInfo> enumerate() const;
    Result<TargetId> target(std::optional<input::DeviceId>) const;
    Result<Capabilities> capabilities(TargetId) const;
    HapticTime now() const;
    Result<HapticScope> scope(std::weak_ptr<HapticControl>);
    void close(std::uint64_t scope);
    Result<PlaybackId> play(std::uint64_t, TargetId, const HapticClip&, const PlayOptions&);
    Status stop(std::uint64_t, PlaybackId);
    Result<PlaybackSnapshot> read(std::uint64_t, PlaybackId);
    Result<OperationId> stopTarget(std::uint64_t, TargetId);
    Result<OperationSnapshot> read(std::uint64_t, OperationId);
    Result<RawSession> acquire(std::weak_ptr<HapticControl>, std::uint64_t, TargetId, AcquirePolicy);
    RawSnapshot rawState(std::uint64_t) const;
    Result<OperationId> cancelRaw(std::uint64_t, std::optional<RawPlayerId> player = {});
    void closeRaw(std::uint64_t);

private:
    struct State;
    std::unique_ptr<State> _state;
};
}  // namespace cc::haptics::detail
