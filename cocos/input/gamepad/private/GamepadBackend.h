#pragma once

#include "SdlMappingParser.h"
#include "input/gamepad/GamepadFrame.h"

#include <bitset>
#include <chrono>
#include <compare>

namespace cc::input::detail {

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
    virtual Error submit(EndpointKey, const NativeCommand&) = 0;
    // Unregister, wake workers, and wait for callbacks before returning.
    virtual void stop() noexcept = 0;
};

} // namespace cc::input::detail
