#pragma once
#include "haptics/private/ClipData.h"
#include "haptics/HapticService.h"
#include <functional>

namespace cc::haptics::detail
{
using ::cc::haptics::Track;
enum class Layout
{
    Mono,
    LeftRight,
    LowHigh
};
enum class Outcome
{
    Ended,
    Preempted,
    Dropped,
    Coalesced,
    Stopped
};
enum class Reason
{
    None,
    Window,
    Priority,
    Capacity,
    Budget,
    Locked
};
using Id       = std::uint64_t;
using Channels = std::array<double, 2>;
struct Request
{
    Track track = Track::Normal;
    std::optional<unsigned> priority;
    double gain = 1, pan = 0;
    unsigned iterations = 1;
    Id scope = 0, route = 0;
    std::string mergeKey;
    std::optional<Time> startAt;  // null = immediate Auto; supplied = fixed, even if equal to now.
};
struct Calibration
{
    Layout layout = Layout::Mono;
    double gain = 1, continuousGain = 1, transientGain = 1, gamma = 1, strength = 1;
    Channels channelGain{1, 1}, cap{1, 1};
    double totalCap = 1;
    Time pulseWidth = 1000;
};
struct Key
{
    Id playback{};
    unsigned iteration{}, ordinal{};  // Zero-based.
    bool operator==(const Key&) const = default;
};
struct Entry
{
    Time at{}, lockedUntil{};
    Key key{};
    Track track{};
    bool pulse{};
    Channels amplitude{};
    Reason reason{};
    double texture{};    // Normalized source quality, subsequently weighted by allocated power.
    Time validUntil{};   // Exclusive end of this sample or pulse. A later request may revise an unlocked bed.
    unsigned count = 1;  // A Capacity layer record represents this many omitted layers, starting at key.
};
struct Terminal
{
    Id id;
    Outcome outcome;
    Time at;
    Id mergedInto{};
};
struct Reservation
{
    Id token;  // Idempotent native submission identity.
    Time begin, end;
    Channels amplitude;
    Track track     = Track::Normal;
    bool canOverlay = true;
    std::optional<Key> source;  // Replaces this source's contribution through end.
    unsigned channelMask{};     // 0 selects all physical channels, including silent channels of a committed batch.
    bool sourceIsPulse = false;
};
class HapticMixer
{
public:
    explicit HapticMixer(Calibration calibration = {});
    ~HapticMixer();
    HapticMixer(const HapticMixer&)            = delete;
    HapticMixer& operator=(const HapticMixer&) = delete;
    Result<Id> submit(const HapticClip& clip, const Request& request = {});
    Result<Id> submitAt(const HapticClip& clip, const Request& request, Time received, Time logicalStart);
    // Skip expired samples after a late wakeup, retaining the absolute source phase.
    void skipTo(Time time);
    bool stop(Id id);
    bool reserve(const Reservation& reservation);
    // Commit [now(), until) on the absolute control grid and exact source boundaries.
    // Callback entries describe allocated layers or decided events, including suppression.
    // The synchronous output consumer must not throw or reenter the mixer.
    void advance(Time until, const std::function<void(const Entry&)>& sink);
    Time now() const;
    std::vector<Terminal> takeTerminals();

private:
    struct State;
    std::unique_ptr<State> _state;
};
}  // namespace cc::haptics::detail
