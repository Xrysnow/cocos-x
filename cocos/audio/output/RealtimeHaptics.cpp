#include "RealtimeHaptics.h"
#include "AudioOutputEndpoints.h"
#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

namespace cc::audio::detail {
namespace {
using Error = AudioOutputError;
using namespace std::chrono_literals;
class RealtimeSession final : public RealtimeHaptics {
    using Receipt = std::function<void(Error, bool)>;
    AudioEndpointId id;
    std::shared_ptr<std::atomic_bool> permit;
    std::mutex mutex;
    std::condition_variable changed;
    std::condition_variable& controlWake;
    GripProgress progress;
    bool enabled{}, closing{};
    GripBlock samples{};
    std::function<GripBlock()> render;
    Receipt complete;
    Error stopped{};
    std::once_flag joined;
    std::thread worker;

    // Native queue positions belong to one opened device clock generation.
    Error pump(OutputEndpoint& endpoint, OutputStream& stream, bool& delivered) {
        std::array<std::int16_t, outputBlockFrames * 4> silence{};
        const auto& channels = endpoint.platform.channels;
        unsigned left = std::find(channels.begin(), channels.end(), AudioChannelPosition::RearLeft) - channels.begin();
        unsigned right = std::find(channels.begin(), channels.end(), AudioChannelPosition::RearRight) - channels.begin();
        stream.setRealtimeGate(permit);
        for (unsigned count = 0; count < realtimePrefillFrames; count += outputBlockFrames) {
            const auto rc = stream.submit(silence.data(), outputBlockFrames);
            if (rc != Error::None) return rc;
        }
        if (const auto rc = stream.setPaused(false); rc != Error::None) return rc;
        std::optional<std::uint64_t> generation, cursor;
        auto clockDeadline = std::chrono::steady_clock::now() + 400ms;
        std::unique_lock lock(mutex);
        progress.trace.peakQueuedFrames = realtimePrefillFrames;
        while (!closing && permit->load()) {
            lock.unlock();
            auto status = stream.pollRealtime();
            lock.lock();
            if (!endpoint.status->connected) return Error::Disconnected;
            if (!status) return status.error();
            const auto& state = status.value();
            progress.trace.peakQueuedFrames = std::max(progress.trace.peakQueuedFrames, state.queuedFrames);
            if (state.queuedFrames > realtimeQueueFrames) return Error::BackendFailure;
            if (!state.clock) {
                progress.prepared = false;
                if (std::chrono::steady_clock::now() >= clockDeadline) return Error::Unsupported;
            } else {
                const auto& clock = *state.clock;
                if ((generation && *generation != clock.generation) || clock.nextWriteFrame < clock.deviceFrame)
                    return Error::Disconnected;
                generation = clock.generation;
                clockDeadline = std::chrono::steady_clock::now() + 100ms;
                progress.trace.generation = clock.generation;
                progress.prepared = endpoint.status->grip->ready();
                if (progress.prepared && enabled && state.availableBlocks &&
                    state.queuedFrames <= realtimeQueueFrames - outputBlockFrames) {
                    // While earlier frames remain queued, adjacent blocks share the same
                    // frame grid. After an underrun, jump over elapsed device frames.
                    const auto first = !cursor || !state.queuedFrames ? std::max(cursor.value_or(0), clock.nextWriteFrame)
                                                                      : *cursor;
                    if (!progress.window) {
                        const auto ahead = first > clock.deviceFrame ? first - clock.deviceFrame : 0;
                        progress.window = GripWindow{first, static_cast<std::int64_t>(clock.observedNs / 1000 + ahead * 1000000 / 48000)};
                        controlWake.notify_one();
                    }
                    if (complete) {
                        if (render) {
                            auto makeBlock = std::move(render);
                            lock.unlock();
                            samples = makeBlock();
                            lock.lock();
                            if (closing || !permit->load()) break;
                        }
                        const auto skip = static_cast<unsigned>(std::min<std::uint64_t>(outputBlockFrames,
                            first > progress.window->firstFrame ? first - progress.window->firstFrame : 0));
                        if (skip == outputBlockFrames) {
                            complete(Error::None, false);
                            complete = {};
                            progress.window.reset();
                        } else {
                            auto& safety = *endpoint.status->grip;
                            std::lock_guard energyLock(safety.mutex);
                            const auto before = safety.limiter.checkpoint(outputBlockFrames);
                            auto block = silence;
                            std::optional<std::uint64_t> lastNonzero;
                            for (unsigned i = 0; i < outputBlockFrames; ++i) {
                                const auto input = i + skip < outputBlockFrames ? samples[i + skip] : std::array<float,2>{};
                                const auto out = safety.limiter.process(input[0], input[1]);
                                block[i * 4 + left] = out[0];
                                block[i * 4 + right] = out[1];
                                if (out[0] != 0 || out[1] != 0) lastNonzero = first + i;
                            }
                            if (!permit->load()) {
                                safety.limiter.restore(before);
                                break;
                            }
                            lock.unlock();
                            const auto rc = stream.submit(block.data(), outputBlockFrames);
                            lock.lock();
                            if (rc == Error::QueueFull) {
                                safety.limiter.restore(before);
                            } else {
                                // Even an uncertain native write counts toward the final possible sample.
                                if (lastNonzero) {
                                    delivered = true;
                                    progress.trace.lastNonzeroFrame = lastNonzero;
                                    if (rc == Error::None && !progress.trace.firstSubmitUs)
                                        progress.trace.firstSubmitUs = std::chrono::duration_cast<std::chrono::microseconds>(
                                            std::chrono::steady_clock::now().time_since_epoch()).count();
                                }
                                if (rc == Error::None)
                                    progress.trace.peakQueuedFrames = std::max(progress.trace.peakQueuedFrames,
                                                                               state.queuedFrames + outputBlockFrames);
                                complete(rc, rc == Error::None && lastNonzero.has_value());
                                complete = {};
                                controlWake.notify_one();
                                progress.window.reset();
                                if (rc != Error::None) return rc;
                                cursor = first + outputBlockFrames;
                            }
                        }
                    }
                }
            }
            if (!enabled && state.queuedFrames <= realtimePrefillFrames - outputBlockFrames && state.availableBlocks) {
                auto rc = stream.submit(silence.data(), outputBlockFrames);
                if (rc != Error::None && rc != Error::QueueFull) return rc;
            }
            changed.wait_for(lock, 1ms);
        }
        return Error::None;
    }
    void run() {
#ifdef _WIN32
        // A standalone consumer may never enter Application::run(). Match its timer
        // resolution while this stream services 5.33 ms deadlines.
        struct TimerResolution {
            bool acquired = timeBeginPeriod(1) == TIMERR_NOERROR;
            ~TimerResolution() { if (acquired) timeEndPeriod(1); }
        } timerResolution;
#endif
        auto endpoint = findOutputEndpoint(id);
        Error error = endpoint ? Error::Unsupported : endpoint.error();
        if (endpoint && endpoint.value().status->managedReady && hasBodyLayout(endpoint.value().platform)) {
            auto opened = openPlatformRealtimeOutput(endpoint.value().platform);
            if (opened) {
                auto& stream = *opened.value();
                bool delivered = false;
                error = pump(endpoint.value(), stream, delivered);
                auto evidence = stream.discardRealtime();
                if (delivered) {
                    std::lock_guard lock(mutex);
                    stopped = !evidence ? evidence.error() :
                              evidence.value().generation != progress.trace.generation ? Error::BackendFailure : Error::None;
                    if (stopped == Error::None) {
                        progress.trace.discardBound = evidence.value().lastPossibleDeviceFrame;
                        progress.trace.discardUs = std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::steady_clock::now().time_since_epoch()).count();
                    }
                    endpoint.value().status->grip->discarded();
                }
            } else {
                error = opened.error();
            }
        }
        std::lock_guard lock(mutex);
        progress.window.reset();
        progress.prepared = false;
        progress.finished = true;
        controlWake.notify_one();
        progress.error = error;
        if (complete) { complete(error == Error::None ? Error::Busy : error, false); complete = {}; }
    }
public:
    RealtimeSession(AudioEndpointId id_, std::shared_ptr<std::atomic_bool> p, std::condition_variable& wake)
        : id(id_), permit(std::move(p)), controlWake(wake), worker([this] { run(); }) {}
    ~RealtimeSession() override { stop(); }
    GripProgress poll() override { std::lock_guard lock(mutex); return progress; }
    void enable() override { std::lock_guard lock(mutex); enabled = true; changed.notify_all(); }
    void supply(GripWindow window, std::function<GripBlock()> makeBlock, Receipt receipt) override {
        std::lock_guard lock(mutex);
        if (!progress.window || progress.window->firstFrame != window.firstFrame || closing || complete) {
            receipt(Error::Busy, false);
            return;
        }
        render = std::move(makeBlock);
        complete = std::move(receipt);
        changed.notify_all();
    }
    Error stop() override {
        { std::lock_guard lock(mutex); closing = true; changed.notify_all(); }
        std::call_once(joined, [this] { worker.join(); });
        return stopped;
    }
};
} // namespace
std::shared_ptr<RealtimeHaptics> prepareRealtimeHaptics(AudioEndpointId endpoint,
                                                       std::shared_ptr<std::atomic_bool> permit,
                                                       std::condition_variable& controlWake) {
    return std::make_shared<RealtimeSession>(endpoint, std::move(permit), controlWake);
}
} // namespace cc::audio::detail
