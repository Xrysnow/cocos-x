#include "audio/AudioEngine.h"
#include "AudioDirectRenderer.h"
#include "AudioOutputEndpoints.h"
#include "AudioOutputIntegration.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <limits>
#include <mutex>
#include <thread>

NS_CC_BEGIN
using namespace audio::detail;

namespace {

using Error = AudioOutputError;
using State = AudioPlaybackState;
constexpr auto pollInterval = std::chrono::milliseconds(2);

struct Route {
    unsigned input;
    unsigned slot;
};

bool active(State state)
{
    return state == State::Buffering || state == State::Playing || state == State::Paused;
}

} // namespace

struct AudioDirectPlayback::Session {
    AudioDirectInput input;
    OutputEndpoint endpoint;
    std::vector<Route> routes;
    unsigned channelCount = 0;
    bool rearOutput = false;
    bool managed = false;

    mutable std::mutex mutex;
    std::condition_variable changed;
    AudioDirectPlaybackSnapshot snapshot;
    std::atomic<bool> looping{false};
    std::stop_source readCancellation{std::nostopstate};
    std::thread reader;
    std::thread output;
    std::deque<DirectBlock> queued;
    bool closing = false;
    bool outputExited = false;
    bool outputStarted = false;
    bool requireStopEvidence = false;
    Error stopEvidence = Error::None;
    bool running = false;
    bool paused = false;
    bool permitted = false;
    bool eof = false;
    std::uint64_t firstFrame = 0;
    std::uint64_t generation = 0;
    std::uint64_t outputGeneration = 0;
    std::uint64_t pauseRevision = 0;
    std::uint64_t pauseAcknowledged = 0;

    Error canPlay() const
    {
        if (snapshot.state == State::Closed)
            return Error::InvalidArgument;
        if (!endpoint.status->connected || snapshot.error == Error::Disconnected)
            return Error::Disconnected;
        if (!managed && rearOutput && endpoint.status->rearManaged)
            return Error::ChannelManaged;
        if (managed && !endpoint.status->managedReady)
            return Error::Busy;
        if (snapshot.state == State::Failed)
            return snapshot.error;
        return Error::None;
    }

    void reset(std::uint64_t frame)
    {
        readCancellation.request_stop();
        firstFrame = frame;
        ++generation;
        queued.clear();
        eof = false;
        changed.notify_all();
    }

    void waitForOutput(std::unique_lock<std::mutex>& lock)
    {
        if (outputStarted)
            changed.wait(lock, [&] { return outputGeneration == generation || outputExited; });
    }

    void fail(Error error)
    {
        snapshot.error = error;
        snapshot.state = error == Error::Disconnected || error == Error::ChannelManaged ? State::Stopped : State::Failed;
        if (error == Error::ChannelManaged)
            snapshot.positionSeconds = 0;
        running = paused = false;
        reset(0);
    }

    void stop(std::unique_lock<std::mutex>& lock, Error error)
    {
        snapshot.state = State::Stopped;
        snapshot.error = error;
        snapshot.positionSeconds = 0;
        running = paused = false;
        reset(0);
        waitForOutput(lock);
    }

    void close() noexcept
    {
        {
            std::lock_guard lock(mutex);
            if (closing)
                return;
            closing = true;
            running = false;
            snapshot.state = State::Closed;
            snapshot.error = Error::None;
            reset(0);
        }
        if (output.joinable())
            output.join();
        if (reader.joinable())
            reader.join();
        input.pcm.reset();
        input.openDecoder = {};
    }

    bool startWorkers(std::unique_lock<std::mutex>& lock)
    {
        if (output.joinable())
            return true;
        try
        {
            output = std::thread([this] {
                try { outputLoop(); }
                catch (...) {
                    std::lock_guard lock(mutex);
                    outputExited = true;
                    if (requireStopEvidence)
                        stopEvidence = Error::BackendFailure;
                    if (!closing)
                        fail(Error::BackendFailure);
                    changed.notify_all();
                }
            });
            outputStarted = true;
            reader = std::thread([this] { readLoop(); });
            return true;
        }
        catch (...)
        {
            closing = true;
            changed.notify_all();
            lock.unlock();
            if (output.joinable())
                output.join();
            lock.lock();
            closing = outputExited = outputStarted = false;
            return false;
        }
    }

    void readLoop()
    {
        std::unique_lock lock(mutex);
        std::uint64_t seen = 0;
        while (!closing)
        {
            changed.wait(lock, [&] { return closing || (running && generation != seen); });
            if (closing)
                break;
            seen = generation;
            const auto frame = firstFrame;
            readCancellation = std::stop_source();
            const auto cancellation = readCancellation.get_token();
            lock.unlock();
            try
            {
                DirectRenderer renderer(input, endpoint.platform.sampleRate, looping, cancellation);
                const bool opened = renderer.start(frame);
                lock.lock();
                if (!closing && generation == seen && !opened)
                    fail(Error::BackendFailure);
                while (!closing && running && generation == seen)
                {
                    changed.wait(lock, [&] {
                        return closing || !running || generation != seen || queued.size() < outputQueueBlocks;
                    });
                    if (closing || !running || generation != seen)
                        break;

                    DirectBlock block;
                    lock.unlock();
                    const bool decoded = renderer.fill(block);
                    lock.lock();
                    if (closing || !running || generation != seen)
                        break;
                    if (!decoded)
                    {
                        fail(Error::BackendFailure);
                        break;
                    }
                    if (block.count != 0)
                        queued.push_back(std::move(block));
                    eof = renderer.finished();
                    changed.notify_all();
                    if (eof)
                        break;
                }
                // The decoder and stream are destroyed on this thread, outside the session lock.
                lock.unlock();
            }
            catch (...)
            {
                if (!lock.owns_lock())
                    lock.lock();
                if (!closing && generation == seen)
                    fail(Error::BackendFailure);
                lock.unlock();
            }
            lock.lock();
        }
    }

    Error submit(OutputStream& stream, const DirectBlock& block)
    {
        std::array<std::int16_t, outputBlockFrames * 8> samples{};
        for (unsigned frame = 0; frame < block.count; ++frame)
        {
            for (const auto& route : routes)
            {
                const float value = block.frames[frame].sample[route.input] * snapshot.gain;
                samples[frame * channelCount + route.slot] = static_cast<std::int16_t>(
                    std::clamp(value, -32768.0f, 32767.0f));
            }
        }
        return stream.submit(samples.data(), block.count);
    }

    void outputLoop()
    {
        struct Submitted {
            std::uint64_t start;
            DirectBlock block;
        };
        std::unique_ptr<OutputStream> stream;
        std::deque<Submitted> submitted;
        std::uint64_t sent = 0;
        bool started = false;
        bool streamPaused = true;
        bool draining = false;
        std::unique_lock lock(mutex);
        const auto releaseStream = [&] {
            const bool proveStop = requireStopEvidence && stream && sent != 0;
            lock.unlock();
            const auto evidence = proveStop ? stream->stopWithEvidence() : Error::None;
            stream.reset();
            lock.lock();
            if (evidence != Error::None)
                stopEvidence = evidence;
        };
        while (!closing)
        {
            if (outputGeneration != generation)
            {
                releaseStream();
                submitted.clear();
                sent = 0;
                started = draining = false;
                streamPaused = true;
                outputGeneration = generation;
                pauseAcknowledged = pauseRevision;
                changed.notify_all();
            }
            if (closing)
                break;
            if (!running)
            {
                changed.wait(lock, [&] { return closing || running || outputGeneration != generation; });
                continue;
            }

            const auto error = canPlay();
            if (error != Error::None)
            {
                fail(error);
                continue;
            }
            if (!stream)
            {
                if (eof && queued.empty())
                {
                    snapshot.state = State::Ended;
                    running = false;
                    continue;
                }
                if (queued.size() < 2 && !eof)
                {
                    pauseAcknowledged = pauseRevision;
                    changed.notify_all();
                    changed.wait_for(lock, pollInterval);
                    continue;
                }
                const auto openingGeneration = generation;
                lock.unlock();
                auto opened = openPlatformOutput(endpoint.platform);
                lock.lock();
                if (opened)
                    stream = std::move(opened).value();
                if (closing || generation != openingGeneration)
                    continue;
                if (!opened)
                {
                    fail(opened.error());
                    continue;
                }
            }

            const bool enabled = !paused && (!managed || permitted);
            if (!enabled && !streamPaused)
            {
                if (const auto pauseError = stream->setPaused(true); pauseError != Error::None)
                {
                    fail(pauseError);
                    continue;
                }
                streamPaused = true;
            }

            auto progress = stream->poll();
            if (!progress)
            {
                fail(progress.error());
                continue;
            }
            const auto played = std::min(progress.value().consumedFrames, sent);
            if (started && (played != 0 || progress.value().drained))
            {
                while (!submitted.empty() && played >= submitted.front().start + submitted.front().block.count)
                {
                    const auto& block = submitted.front().block;
                    snapshot.positionSeconds = block.frames[block.count - 1].position;
                    submitted.pop_front();
                }
                if (!submitted.empty() && played > submitted.front().start)
                {
                    const auto& item = submitted.front();
                    snapshot.positionSeconds = item.block.frames[played - item.start - 1].position;
                }
                if (!paused)
                    snapshot.state = State::Playing;
            }
            pauseAcknowledged = pauseRevision;
            changed.notify_all();
            if (draining && progress.value().drained)
            {
                snapshot.state = State::Ended;
                running = paused = false;
                reset(0);
                continue;
            }

            unsigned capacity = progress.value().availableBlocks;
            while (enabled && capacity && !queued.empty() && submitted.size() < 2 * outputQueueBlocks)
            {
                if (canPlay() != Error::None)
                    break;
                const auto submitError = submit(*stream, queued.front());
                if (submitError == Error::QueueFull)
                    break;
                if (submitError != Error::None)
                {
                    fail(submitError);
                    break;
                }
                const auto frames = queued.front().count;
                submitted.push_back({sent, std::move(queued.front())});
                sent += frames;
                queued.pop_front();
                --capacity;
                changed.notify_all();
            }
            if (!running)
                continue;
            if (enabled && streamPaused && sent != 0)
            {
                if (const auto resumeError = stream->setPaused(false); resumeError != Error::None)
                {
                    fail(resumeError);
                    continue;
                }
                started = true;
                streamPaused = false;
            }
            if (enabled && eof && queued.empty() && !draining)
            {
                if (const auto drainError = stream->drain(); drainError != Error::None)
                {
                    fail(drainError);
                    continue;
                }
                draining = true;
            }
            changed.wait_for(lock, pollInterval);
        }
        releaseStream();
        outputExited = true;
        changed.notify_all();
    }
};

namespace audio::detail {

struct DirectPlaybackAccess {
    using Session = AudioDirectPlayback::Session;

    static std::vector<std::weak_ptr<Session>>& sessions()
    {
        static std::vector<std::weak_ptr<Session>> registry;
        return registry;
    }

    static AudioResult<AudioDirectPlayback> create(AudioSource& source, AudioEndpointId id,
        const std::vector<AudioChannelRoute>& map, bool managed)
    {
        if (map.empty() && !managed)
            return Error::InvalidArgument;
        auto input = captureAudioDirectInput(source);
        if ((!input.pcm && !input.openDecoder) || input.channels < 1 || input.channels > 2 ||
            input.sampleRate <= 0 || (input.bitDepth != 8 && input.bitDepth != 16))
            return Error::Unsupported;

        const std::vector<AudioChannelRoute> bodyMap{{0, AudioChannelPosition::RearLeft},
            {static_cast<unsigned>(input.channels - 1), AudioChannelPosition::RearRight}};
        const auto& selected = managed ? bodyMap : map;
        std::array<bool, 8> seen{};
        for (const auto& route : selected)
        {
            const auto position = static_cast<unsigned>(route.output);
            if (route.input >= static_cast<unsigned>(input.channels) || position >= seen.size() || seen[position])
                return Error::InvalidArgument;
            seen[position] = true;
        }

        const auto layout = findOutputEndpoint(id);
        if (!layout)
            return layout.error();
        auto endpoint = layout.value();
        const auto& channels = endpoint.platform.channels;
        if (!endpoint.platform.canRoute || endpoint.platform.sampleRate == 0 || channels.empty() || channels.size() > 8 ||
            (managed && !hasBodyLayout(endpoint.platform)))
            return Error::Unsupported;
        if (managed && !endpoint.status->managedReady)
            return Error::Busy;
        const bool rear = std::any_of(selected.begin(), selected.end(), [](const auto& route) {
            return isRearChannel(route.output);
        });
        if (rear && !managed && endpoint.status->rearManaged)
            return Error::ChannelManaged;

        std::vector<Route> routes;
        for (const auto& route : selected)
        {
            const auto slot = std::find(channels.begin(), channels.end(), route.output);
            if (slot == channels.end())
                return Error::Unsupported;
            routes.push_back({route.input, static_cast<unsigned>(slot - channels.begin())});
        }

        auto session = std::make_shared<Session>();
        session->snapshot.seekable = input.seekable;
        if (input.totalFrames)
            session->snapshot.durationSeconds = static_cast<double>(*input.totalFrames) / input.sampleRate;
        session->input = std::move(input);
        session->channelCount = static_cast<unsigned>(channels.size());
        session->endpoint = std::move(endpoint);
        session->routes = std::move(routes);
        session->rearOutput = rear;
        session->managed = managed;
        auto& registry = sessions();
        registry.erase(std::remove_if(registry.begin(), registry.end(), [](const auto& entry) { return entry.expired(); }),
            registry.end());
        registry.emplace_back(session);
        return AudioDirectPlayback(std::move(session));
    }

    static void revoke(AudioEndpointId id)
    {
        for (const auto& entry : sessions())
        {
            if (auto session = entry.lock(); session && session->endpoint.id == id && session->rearOutput && !session->managed)
            {
                std::unique_lock lock(session->mutex);
                if (active(session->snapshot.state))
                    session->stop(lock, Error::ChannelManaged);
                else if (session->snapshot.error == Error::ChannelManaged)
                    session->waitForOutput(lock);
            }
        }
    }

    static Error reserve(const OutputEndpoint& endpoint)
    {
        if (!endpoint.status->rearManaged.exchange(true))
            revoke(endpoint.id);
        return AudioEngine::applyManagedOutputPolicy(endpoint.platform.mainDeviceName, endpoint.platform.deviceSelector,
            endpoint.platform.isDefault) ? Error::None : Error::Unsupported;
    }

    static void requireEvidence(AudioDirectPlayback& handle)
    {
        if (auto session = handle._session) {
            std::lock_guard lock(session->mutex);
            session->requireStopEvidence = true;
        }
    }

    static Error enable(AudioDirectPlayback& handle, bool enabled)
    {
        auto session = handle._session;
        if (!session || !session->managed)
            return Error::InvalidArgument;
        std::unique_lock lock(session->mutex);
        if (session->closing) {
            if (enabled || !session->requireStopEvidence)
                return Error::InvalidArgument;
            session->changed.wait(lock, [&] { return !session->outputStarted || session->outputExited; });
            return session->stopEvidence;
        }
        if (enabled)
        {
            if (const auto error = session->canPlay(); error != Error::None)
                return error;
        }
        session->permitted = enabled;
        if (!enabled)
        {
            if (active(session->snapshot.state))
                session->stop(lock, Error::None);
            else
                session->waitForOutput(lock);
        }
        session->changed.notify_all();
        return enabled ? Error::None : session->stopEvidence;
    }

    static void fail(AudioDirectPlayback& handle, Error error)
    {
        auto session = handle._session;
        if (!session || !session->managed)
            return;
        std::unique_lock lock(session->mutex);
        if (session->closing)
            return;
        session->permitted = false;
        session->fail(error);
        session->waitForOutput(lock);
    }
};

AudioResult<AudioDirectPlayback> createManagedPlayback(AudioSource& source, AudioEndpointId endpoint)
{
    return DirectPlaybackAccess::create(source, endpoint, {}, true);
}

AudioOutputError setManagedPlaybackEnabled(AudioDirectPlayback& playback, bool enabled)
{
    return DirectPlaybackAccess::enable(playback, enabled);
}

void requireManagedStopEvidence(AudioDirectPlayback& playback)
{
    DirectPlaybackAccess::requireEvidence(playback);
}

void failManagedPlayback(AudioDirectPlayback& playback, AudioOutputError error)
{
    DirectPlaybackAccess::fail(playback, error);
}

AudioOutputError reserveManagedOutput(AudioEndpointId id)
{
    const auto endpoint = findOutputEndpoint(id);
    return endpoint ? DirectPlaybackAccess::reserve(endpoint.value()) : endpoint.error();
}

AudioOutputError registerManagedOutput(AudioEndpointId id)
{
    const auto endpoint = findOutputEndpoint(id);
    if (!endpoint)
        return endpoint.error();
    const auto& info = endpoint.value();
    const bool bodyLayout = hasBodyLayout(info.platform);
    if (bodyLayout && info.status->managedReady)
        return Error::None;
    const auto policyError = DirectPlaybackAccess::reserve(info);
    if (policyError != Error::None)
        return policyError;
    if (!bodyLayout)
        return Error::Unsupported;
    auto probe = openPlatformOutput(info.platform);
    if (!probe)
        return probe.error();
    info.status->managedReady = true;
    return Error::None;
}

void shutdownDirectOutput() noexcept
{
    for (const auto& entry : DirectPlaybackAccess::sessions())
        if (auto session = entry.lock())
            session->close();
    DirectPlaybackAccess::sessions().clear();
    invalidateOutputEndpoints();
    shutdownPlatformOutput();
}

} // namespace audio::detail

AudioDirectPlayback::AudioDirectPlayback(std::shared_ptr<Session> session) : _session(std::move(session)) {}
AudioDirectPlayback::AudioDirectPlayback(AudioDirectPlayback&&) noexcept = default;

AudioDirectPlayback& AudioDirectPlayback::operator=(AudioDirectPlayback&& other) noexcept
{
    if (this != &other)
    {
        close();
        _session = std::move(other._session);
    }
    return *this;
}

AudioDirectPlayback::~AudioDirectPlayback() { close(); }

AudioOutputError AudioDirectPlayback::play()
{
    if (!_session)
        return Error::InvalidArgument;
    std::unique_lock lock(_session->mutex);
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    if (active(_session->snapshot.state))
    {
        if (_session->paused)
        {
            _session->paused = false;
            _session->snapshot.state = State::Buffering;
            _session->changed.notify_all();
        }
        return Error::None;
    }
    lock.unlock();
    const auto verified = findOutputEndpoint(_session->endpoint.id);
    lock.lock();
    if (!verified)
    {
        if (verified.error() == Error::Disconnected)
            _session->fail(Error::Disconnected);
        return verified.error();
    }
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    if (!verified.value().platform.canRoute || verified.value().platform.channels != _session->endpoint.platform.channels ||
        verified.value().platform.sampleRate != _session->endpoint.platform.sampleRate)
        return Error::Unsupported;
    if (!_session->startWorkers(lock))
        return Error::BackendFailure;
    const bool restart = _session->snapshot.state == State::Ended;
    _session->reset(restart ? 0 : _session->firstFrame);
    if (restart)
        _session->snapshot.positionSeconds = 0;
    _session->snapshot.state = State::Buffering;
    _session->snapshot.error = Error::None;
    _session->running = true;
    _session->changed.notify_all();
    return Error::None;
}

AudioOutputError AudioDirectPlayback::pause()
{
    if (!_session)
        return Error::InvalidArgument;
    std::unique_lock lock(_session->mutex);
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    if (_session->paused)
        return Error::None;
    if (!_session->running)
        return Error::InvalidArgument;
    _session->paused = true;
    _session->snapshot.state = State::Paused;
    ++_session->pauseRevision;
    _session->changed.notify_all();
    _session->changed.wait(lock, [&] {
        return !_session->running || _session->pauseAcknowledged == _session->pauseRevision;
    });
    return _session->snapshot.error;
}

AudioOutputError AudioDirectPlayback::resume()
{
    if (!_session || !active(snapshot().state))
        return _session && snapshot().error != Error::None ? snapshot().error : Error::InvalidArgument;
    return play();
}

AudioOutputError AudioDirectPlayback::stop()
{
    if (!_session)
        return Error::InvalidArgument;
    std::unique_lock lock(_session->mutex);
    if (_session->closing || _session->snapshot.state == State::Failed)
        return _session->closing ? Error::InvalidArgument : _session->snapshot.error;
    const auto error = _session->canPlay();
    _session->stop(lock, error);
    return error;
}

AudioOutputError AudioDirectPlayback::seekTime(double seconds)
{
    if (!_session || !std::isfinite(seconds) || seconds < 0)
        return Error::InvalidArgument;
    std::unique_lock lock(_session->mutex);
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    if (!_session->input.seekable)
        return Error::Unsupported;
    auto& state = _session->snapshot;
    const auto frameValue = seconds * _session->input.sampleRate;
    if ((state.durationSeconds && seconds > *state.durationSeconds) ||
        frameValue >= static_cast<double>(std::numeric_limits<std::int64_t>::max()))
        return Error::InvalidArgument;
    const bool end = state.durationSeconds && seconds == *state.durationSeconds;
    const auto frame = end ? *_session->input.totalFrames : static_cast<std::uint64_t>(frameValue);
    state.positionSeconds = static_cast<double>(frame) / _session->input.sampleRate;
    if (end)
    {
        state.state = State::Ended;
        _session->running = _session->paused = false;
    }
    else if (_session->running)
        state.state = _session->paused ? State::Paused : State::Buffering;
    else if (state.state == State::Ended)
        state.state = State::Ready;
    _session->reset(frame);
    _session->waitForOutput(lock);
    return Error::None;
}

AudioOutputError AudioDirectPlayback::setLooping(bool enabled)
{
    if (!_session)
        return Error::InvalidArgument;
    std::lock_guard lock(_session->mutex);
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    if (enabled && !_session->input.seekable)
        return Error::Unsupported;
    _session->looping = _session->snapshot.looping = enabled;
    return Error::None;
}

AudioOutputError AudioDirectPlayback::setGain(float gain)
{
    if (!_session || !std::isfinite(gain) || gain < 0)
        return Error::InvalidArgument;
    std::lock_guard lock(_session->mutex);
    if (const auto error = _session->canPlay(); error != Error::None)
        return error;
    _session->snapshot.gain = gain;
    return Error::None;
}

AudioDirectPlaybackSnapshot AudioDirectPlayback::snapshot() const
{
    if (!_session)
    {
        AudioDirectPlaybackSnapshot result;
        result.state = State::Closed;
        return result;
    }
    std::lock_guard lock(_session->mutex);
    auto result = _session->snapshot;
    if (result.state != State::Closed && !_session->endpoint.status->connected)
    {
        result.state = State::Stopped;
        result.error = Error::Disconnected;
    }
    return result;
}

void AudioDirectPlayback::close() noexcept
{
    if (_session)
        _session->close();
}

AudioResult<std::vector<AudioOutputEndpoint>> AudioEngine::getOutputEndpoints()
{
    auto listed = refreshOutputEndpoints();
    if (!listed)
        return listed.error();
    std::vector<AudioOutputEndpoint> result;
    for (auto& entry : listed.value())
    {
        AudioOutputEndpoint endpoint{entry.id, std::move(entry.platform.name), entry.platform.isDefault, {}};
        for (const auto position : entry.platform.channels)
            endpoint.channels.push_back({position, isRearChannel(position) && entry.status->rearManaged});
        result.push_back(std::move(endpoint));
    }
    return result;
}

AudioResult<AudioDirectPlayback> AudioEngine::createDirectPlayback(AudioSource& source, AudioEndpointId endpoint,
    const std::vector<AudioChannelRoute>& channelMap)
{
    return DirectPlaybackAccess::create(source, endpoint, channelMap, false);
}

NS_CC_END
