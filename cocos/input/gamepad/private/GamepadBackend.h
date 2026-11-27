#pragma once

#include "mapping/SdlMappingParser.h"
#include "input/gamepad/GamepadFrame.h"

#include <algorithm>
#include <atomic>
#include <bitset>
#include <chrono>
#include <compare>
#include <future>

namespace cc::haptics::detail { class MobileOutput; }
namespace cc::input::detail {

// Reserve space for native stops even when the output data queue is full.
inline constexpr std::size_t outputStopReserve = 16;

using NativeBodyGate = std::shared_ptr<const std::atomic_bool>;

inline bool bodyGateOpen(const NativeBodyGate& gate) noexcept
{
    return !gate || gate->load(std::memory_order_acquire);
}

struct SdlAxisIndex {
    unsigned index;
    AxisEncoding encoding;
};

struct SdlInputIndices {
    std::vector<std::optional<unsigned>> buttons;
    std::vector<std::optional<SdlAxisIndex>> axes;
};

struct EndpointKey {
    std::uint64_t backend, endpoint, generation;
    auto operator<=>(const EndpointKey&) const = default;
};

struct RawLayout {
    std::string id;
    unsigned buttonCount = 0, axisCount = 0, hatCount = 0;
    std::optional<DeviceGuid> guid;
    bool usesVersion = true;
    bool xinput = false;
    bool legacyHidapi = false;
    std::optional<SdlInputIndices> sdlIndices;
    std::string builtInMapping;
    // Empty leaves all indices present. A zero preserves an index without
    // advertising its absent hardware control to the binding compiler.
    std::vector<std::uint8_t> buttonPresent, axisPresent, hatPresent;
};

struct RawState {
    std::vector<std::uint8_t> buttons, hats;
    std::vector<std::int16_t> axes;
    std::vector<std::uint8_t> axesKnown;
};

struct EndpointCapabilities {
    std::bitset<SensorCount> sensors;
    std::bitset<FeatureCount> features;
    std::vector<unsigned> fingersPerPad;
    std::array<std::optional<float>, SensorCount> nominalHz;
    std::array<std::optional<TriggerLimits>, 2> triggerLimits;
    std::uint32_t playerLightMask = 0;
    // Body rumble expires without an engine frame, and a successful Body
    // stop completion means the native output accepted the neutral state.
    bool acknowledgedBodyStop = false;
    bool mobileHaptics = false; ///< The selected endpoint provides a finite mobile output queue.
};

struct HapticAudioIdentity {
    std::string containerId, usbPath;
    bool writable = false;
};

struct EndpointDescriptor {
    RawLayout layout;
    std::string name;
    std::optional<std::uint16_t> vendor, product, version;
    std::optional<std::string> serial;
    // Verified by the backend, scoped to its instance. Never infer this from GUID.
    std::string physicalAssociation;
    bool auxiliary = false;
    EndpointCapabilities capabilities;
    Power power{};
    Link link = Link::Unknown;
    HapticAudioIdentity hapticAudio;
    GamepadType controllerType = GamepadType::Unknown;
};

inline std::uint64_t nowNs()
{
    using namespace std::chrono;
    return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
}

struct ReportTime {
    std::uint64_t receivedNs = nowNs();
    std::optional<std::uint64_t> sourceNs;
    TimeQuality quality = TimeQuality::ReceiveOnly;
};

struct RawBaseline {
    RawState state;
    // Per-open capture cursor. Baseline includes input through this cursor.
    std::uint64_t cursor = 0;
    ReportTime time;
};

struct AttachedEndpoint {
    EndpointKey key;
    EndpointDescriptor descriptor;
    RawBaseline initial;
};

struct ReportView {
    // One atomic input change set. Submit successive transitions of the same
    // control as separate reports, even when delivered by the same system call.
    std::span<const RawChange> changes;
    std::span<const Contact> contacts;
    std::span<const Motion> motion;
    std::optional<Power> power;
    std::uint64_t cursor = 0;
    ReportTime time;
};

struct NativeCommand {
    CommandId id; // Zero for housekeeping stops, which do not complete.
    OutputCommand command;
    bool waveformMode = false;
    std::shared_future<bool> bodyReady{};
    // Revoked before a replacement queues its stop on the same endpoint.
    NativeBodyGate bodyGate{};
    std::uint64_t bodyDeadlineNs = 0;

    bool canApply() const noexcept
    {
        try
        {
            return (!bodyReady.valid() || bodyReady.get()) && bodyGateOpen(bodyGate);
        }
        catch (const std::future_error&) { return false; }
    }

    OutputCommand commandAt(std::uint64_t now) const
    {
        if (const auto* rumble = std::get_if<Rumble>(&command); rumble && bodyDeadlineNs)
        {
            // Round down so the native duration cannot extend the deadline.
            const auto remainingMs = bodyDeadlineNs > now ? (bodyDeadlineNs - now) / 1'000'000 : 0;
            if (!remainingMs)
                return Stop{Channel::Body};
            return Rumble{rumble->low, rumble->high,
                std::min(rumble->duration, std::chrono::milliseconds(remainingMs))};
        }
        return command;
    }
};

class ReportSink {
public:
    virtual ~ReportSink() = default;
    virtual void attached(EndpointKey, EndpointDescriptor, RawBaseline) = 0;
    // All borrowed payload data is copied before report() returns.
    virtual void report(EndpointKey, const ReportView&) = 0;
    virtual void baseline(EndpointKey, RawBaseline) = 0;
    virtual void capabilitiesChanged(EndpointKey, EndpointCapabilities) = 0;
    virtual void desynchronized(EndpointKey, InputGap) = 0;
    virtual void detached(EndpointKey) = 0;
    virtual void topology(std::vector<AttachedEndpoint>) = 0;
    virtual void outputCompleted(EndpointKey, CommandId, Error) = 0;
};

class GamepadBackend {
public:
    virtual ~GamepadBackend() = default;
    virtual std::shared_ptr<haptics::detail::MobileOutput> mobileOutput(EndpointKey) { return {}; }
    virtual Error start(ReportSink&) = 0;
    // Deactivation must interrupt output even with no further logic ticks.
    virtual void setActive(bool) = 0;
    virtual void requestBaseline(EndpointKey) = 0;
    // Re-enumerate after topology loss. Publish a single snapshot with new
    // open generations before reports from those generations.
    virtual void requestTopology() = 0;
    virtual Error setSensor(EndpointKey, Sensor, bool) { return Error::Unsupported; }
    virtual void setClaimed(EndpointKey, bool) {}
    // Queue promptly. Accepted operations complete through ReportSink.
    // On a route with acknowledgedBodyStop, complete a Body stop successfully
    // only after applying the native stop or establishing that Body is idle.
    virtual Error submit(EndpointKey, const NativeCommand&) = 0;
    // Unregister, wake workers, and wait for callbacks before returning.
    virtual void stop() noexcept = 0;
};

} // namespace cc::input::detail
