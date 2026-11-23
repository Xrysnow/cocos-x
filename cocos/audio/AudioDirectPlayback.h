#pragma once

#include "platform/PlatformDefine.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace cc {

enum class AudioEndpointId : std::uint64_t {};
enum class AudioChannelPosition {
    FrontLeft, FrontRight, FrontCenter, Lfe, RearLeft, RearRight, SideLeft, SideRight
};

struct AudioOutputChannel {
    AudioChannelPosition position;
    bool managed = false;
};

struct AudioOutputEndpoint {
    AudioEndpointId id;
    std::string name;
    bool isDefault = false;
    std::vector<AudioOutputChannel> channels;
};

struct AudioChannelRoute {
    unsigned input;
    AudioChannelPosition output;
};

enum class AudioOutputError {
    None, InvalidArgument, Unsupported, Disconnected, ChannelManaged, Busy, QueueFull, BackendFailure
};

template<class T>
class AudioResult {
public:
    AudioResult(T value) : _value(std::move(value)) {}
    AudioResult(AudioOutputError error) : _error(error) {}

    explicit operator bool() const noexcept { return _value.has_value(); }
    AudioOutputError error() const noexcept { return _error; }
    T& value() & { return _value.value(); }
    const T& value() const & { return _value.value(); }
    T&& value() && { return std::move(_value).value(); }

private:
    std::optional<T> _value;
    AudioOutputError _error = AudioOutputError::None;
};

enum class AudioPlaybackState { Ready, Buffering, Playing, Paused, Stopped, Ended, Failed, Closed };

struct AudioDirectPlaybackSnapshot {
    AudioPlaybackState state = AudioPlaybackState::Ready;
    AudioOutputError error = AudioOutputError::None;
    double positionSeconds = 0;
    std::optional<double> durationSeconds;
    float gain = 1;
    bool looping = false;
    bool seekable = false;
};

namespace audio::detail { struct DirectPlaybackAccess; }

// An owning handle. Call its methods and destroy it on the engine thread.
class CC_DLL AudioDirectPlayback {
public:
    AudioDirectPlayback(AudioDirectPlayback&&) noexcept;
    AudioDirectPlayback& operator=(AudioDirectPlayback&&) noexcept;
    ~AudioDirectPlayback();

    AudioOutputError play();
    AudioOutputError pause();
    AudioOutputError resume();
    AudioOutputError stop();
    AudioOutputError seekTime(double seconds);
    AudioOutputError setLooping(bool enabled);
    AudioOutputError setGain(float gain);
    AudioDirectPlaybackSnapshot snapshot() const;
    void close() noexcept;

private:
    friend struct audio::detail::DirectPlaybackAccess;
    struct Session;
    explicit AudioDirectPlayback(std::shared_ptr<Session> session);
    std::shared_ptr<Session> _session;
};

} // namespace cc
