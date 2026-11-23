#pragma once

#include "input/gamepad/GamepadTypes.h"
#include "audio/AudioDirectPlayback.h"

#include <chrono>
#include <memory>
#include <variant>

namespace cc { class AudioSource; }

namespace cc::input {

namespace detail { class OutputRouter; }

struct Rumble {
    float low = 0;
    float high = 0;
    std::chrono::milliseconds duration{};
};

enum class HapticStopReason { None, Requested, Replaced, FocusLost, EndpointLost, Disconnected };

struct HapticPlaybackSnapshot {
    AudioPlaybackState state = AudioPlaybackState::Closed;
    Error error = Error::None;
    double positionSeconds = 0;
    std::optional<double> durationSeconds;
    float intensity = 1;
    bool looping = false;
    bool seekable = false;
    HapticStopReason stopReason = HapticStopReason::None;
};

// An owning handle. Call its methods and destroy it on the engine thread.
class CC_DLL HapticPlayback {
public:
    HapticPlayback(HapticPlayback&&) noexcept;
    HapticPlayback& operator=(HapticPlayback&&) noexcept;
    ~HapticPlayback();

    Error play();
    Error pause();
    Error resume();
    Error stop();
    Error seekTime(double seconds);
    Error setLooping(bool enabled);
    Error setIntensity(float intensity);
    HapticPlaybackSnapshot snapshot() const;
    void close() noexcept;

private:
    friend class detail::OutputRouter;
    struct Session;
    explicit HapticPlayback(std::shared_ptr<Session> session);
    std::shared_ptr<Session> _session;
};

struct TriggerRumble {
    float left = 0;
    float right = 0;
    std::chrono::milliseconds duration{};
};

struct Rgb {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
};

struct PlayerLights { std::uint32_t mask = 0; };

enum class TriggerMode { Off, Resistance, Vibration };
struct AdaptiveTrigger {
    Side side = Side::Left;
    TriggerMode mode = TriggerMode::Off;
    float start = 0;
    float strength = 0;
    float hz = 0;
};

enum class Channel { All, Body, Triggers, AdaptiveLeft, AdaptiveRight, Lights };
struct Stop { Channel channel = Channel::All; };

using OutputCommand = std::variant<Rumble, TriggerRumble, Rgb, PlayerLights, AdaptiveTrigger, Stop>;

enum class Completion { Applied, Superseded, Cancelled, Failed };
struct OutputDone {
    CommandId command{};
    Completion status = Completion::Failed;
    Error error = Error::None;
};

} // namespace cc::input
