#include "HapticControl.h"
#include "AndroidWriteBudget.h"
#include "GripSynth.h"
#include "haptics/private/HapticMixer.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <map>
#include <thread>

namespace cc::haptics::detail
{
namespace
{
using namespace std::chrono_literals;
using input::Channel;
using input::DeviceId;
using input::Rumble;
using input::Stop;
using Done    = std::function<void(NativeError)>;
using Receipt = std::shared_ptr<std::atomic<int>>;
using Gate    = std::shared_ptr<std::atomic_bool>;
Time clockUs()
{
    return static_cast<Time>(input::detail::nowNs() / 1000);
}
constexpr Time GridUs = 20000, LeaseUs = 120000, StopUs = 250000;
std::atomic_uint64_t nextIdentity{1};
template <class T>
Result<T> fail(Error e)
{
    return {{}, ErrorInfo{e, {}}};
}
bool final(PlaybackState s)
{
    return s >= PlaybackState::Completed;
}

struct Scheduled
{
    PlaybackId id;
    HapticClip clip;
    Request options;
    Time received, due, span;
    bool immediate;
};
struct VoiceRecord
{
    PlaybackId id;
    Time end;
    bool constant{};
};
struct MotorFrame
{
    Channels levels{};
    std::vector<PlaybackId> contributors;
    Time due{}, end{};
};
struct Write
{
    Receipt receipt;
    Time at{};
    Done done;
    std::vector<PlaybackId> contributors;
    bool pcmSamples{};
    Time rawSpan{};  // Raw patterns use the native start receipt as their lifetime anchor.
    std::shared_ptr<std::atomic<Time>> pcmSubmittedAt;
};
struct Handover
{
    Owner mode = Owner::Idle;
    Rumble rumble;
    Done done;
    std::shared_ptr<PcmSource> pcm;
    std::uint64_t raw{};
};
struct Fence
{
    Endpoint endpoint;
    Gate gate = std::make_shared<std::atomic_bool>(true);
    Receipt receipt;
    Time deadline{}, retry{};
    unsigned attempts{};
    bool needsNative{};
    bool audioStopped{};
    bool audioFault{};
    bool disconnected{};
    bool resumeOnMotors{};
    unsigned exitMs{};
    Time exitReady{};
    StopReason reason{};
    std::optional<OperationId> operation;
    bool uncertainOriginal{};
    std::optional<Write> originalWrite; // Collect the last in-flight start outcome before releasing its writer.
    std::shared_ptr<MobileOutput> mobile;
    Done done;
};
struct Target
{
    TargetInfo info;
    Endpoint route{};
    bool rawCapable = false, interrupt = true, published = true;
    std::shared_ptr<MobileOutput> mobile;
    MobileCapabilities caps;
    std::optional<Owner> restricted;
    AndroidWriteBudget writeBudget;
    std::uint64_t player{};
    Time playerOrigin{};
    Time batchUs = 125000;
    Receipt preparing;
    Time prepareAt{}, legacyNext{};
    Rumble legacyEffect{};
    Owner owner = Owner::Idle;
    Gate gate   = std::make_shared<std::atomic_bool>(true);
    Endpoint writer{};
    bool written = false, fault = false;
    std::optional<Fence> fence;
    std::optional<Handover> successor;
    std::optional<Write> write;
    std::optional<MotorFrame> frame;
    std::unique_ptr<HapticMixer> mixer, stableCheckpoint;
    Time stableStart{}, heDrainUntil{};
    std::optional<PlaybackId> original; // Owns this generation's pending or started native document.
    std::vector<Scheduled> scheduled;
    std::map<Id, VoiceRecord> voices;
    std::vector<Terminal> ends;
    Time nextGrid{}, lastWrite{}, expires{};
    Channels last{};
    std::shared_ptr<PcmSource> pcm;
    std::optional<AudioEndpointId> paired;
    PcmModeTiming timing;
    HapticCalibration profile;
    bool reproject{};
    std::optional<PcmOutputTrace> trace;
    bool pcmUnavailable{}, pcmLive{};
    std::shared_ptr<audio::detail::RealtimeHaptics> realtime, warm;
    Gate warmGate;
    Time warmUntil{};
    std::shared_ptr<GripSynth> synth;
    Receipt modeWrite;
    Time modeReady{}, audioEpochUs{};
    std::optional<std::uint64_t> firstAudioFrame;
    std::future<NativeError> audioJob;
    bool enabling = false;
    std::uint64_t raw{};
};
struct ScopeCounts
{
    std::uint64_t play{}, operation{};
};
struct RawRecord
{
    std::uint64_t scope;
    TargetId target;
    RawSnapshot snap;
    Time idleSince;
};
using RecordId = std::variant<PlaybackId, OperationId>;

void revokePending(Target& t, std::map<std::uint64_t, RawRecord>& leases, Error error)
{
    if (!t.successor)
        return;
    if (t.successor->raw && leases.contains(t.successor->raw))
        leases.at(t.successor->raw).snap = {RawState::Failed, error};
    if (t.successor->done)
        t.successor->done(NativeError::Busy);
    t.successor.reset();
}
}  // namespace

struct HapticControl::State
{
    input::detail::GamepadBackend* backend;
    input::detail::ReportQueue& queue;
    std::mutex mutex;
    std::condition_variable wake;
    std::condition_variable changed;
    bool active = true, closing = false;
    bool applicationActive = true, directorActive = true;
    OutputSettings settings;
    std::shared_ptr<const void> lifetime = std::make_shared<int>(0);
    bool enabled() const { return settings.enabled && settings.strength > 0; }
    std::uint64_t compatScope{};
    std::uint64_t generation = nextIdentity++;
    std::uint32_t sequence   = 0x80000000u;
    std::map<TargetId, Target> targets;
    std::map<std::optional<DeviceId>, TargetId> routes;
    std::map<std::uint64_t, ScopeCounts> scopes;
    std::map<PlaybackId, PlaybackSnapshot> plays;
    std::map<OperationId, OperationSnapshot> operations;
    std::deque<RecordId> terminalOrder;
    std::map<std::uint64_t, RawRecord> leases;
    std::thread worker;
    State(input::detail::GamepadBackend* b, input::detail::ReportQueue& q) : backend(b), queue(q) {}
    void retain(RecordId id)
    {
        terminalOrder.push_back(id);
        if (terminalOrder.size() > 512)
        {
            std::visit(
                [&](auto old) {
                    using T = decltype(old);
                    if constexpr (std::is_same_v<T, PlaybackId>)
                        plays.erase(old);
                    else
                        operations.erase(old);
                },
                terminalOrder.front());
            terminalOrder.pop_front();
        }
    }
    void finish(PlaybackId id, PlaybackState state, StopReason reason = {}, std::optional<Error> error = {})
    {
        auto it = plays.find(id);
        if (it == plays.end() || final(it->second.state))
            return;
        it->second.state  = state;
        it->second.reason = reason;
        it->second.error  = error;
        retain(id);
    }
    void finishOp(std::optional<OperationId> id, std::optional<Error> error = {})
    {
        if (!id || !operations.contains(*id))
            return;
        auto& op = operations.at(*id);
        if (op.state != OperationState::Pending)
            return;
        op.state = error ? OperationState::Failed : OperationState::Succeeded;
        op.error = error;
        if (!error)
            op.confirmedUs = clockUs();
        retain(*id);
    }
    void dropScheduled(Target& t, StopReason reason)
    {
        for (auto& e : t.scheduled)
            finish(e.id, PlaybackState::Stopped, reason);
        t.scheduled.clear();
    }
    void recordSubmission(const Write& write)
    {
        for (auto id : write.contributors)
            if (auto it = plays.find(id); it != plays.end())
            {
                it->second.submitted = true;
                it->second.usedRealtimePcm |= write.pcmSamples;
                if (!it->second.firstSubmitUs)
                    it->second.firstSubmitUs = write.pcmSubmittedAt ? write.pcmSubmittedAt->load() : write.at;
            }
    }
    void endVoices(Target& t, StopReason why)
    {
        for (auto& [key, v] : t.voices)
            finish(v.id, why == StopReason::Replaced ? PlaybackState::Preempted : PlaybackState::Stopped, why);
        t.voices.clear();
        t.ends.clear();
        t.mixer.reset();
    }
    void startStop(Target& t, StopReason why, bool resumeOnMotors = false)
    {
        if (t.fence)
        {
            if (t.fence->resumeOnMotors && !resumeOnMotors)
            {
                t.fence->resumeOnMotors = false;
                endVoices(t, why);
            }
            return;
        }
        // The service may begin HE after start() returns. Let an uncontested
        // finite effect drain before issuing a natural stop, which would otherwise
        // cut off its last event. A real interruption always stops immediately.
        // This grace is not silence evidence: the ordinary stop fence still follows.
        if (why == StopReason::None && clockUs() < t.heDrainUntil) return;
        t.heDrainUntil = 0;
        if (t.warmGate) t.warmGate->store(false);
        t.gate->store(false);
        if (t.write && (t.write->receipt->load() == int(NativeError::None) ||
                        t.write->receipt->load() == int(mobileHeSubmitted)))
            recordSubmission(*t.write);
        if (why == StopReason::Reconfigured && t.stableCheckpoint && t.mixer->now() > clockUs())
        {
            // A mobile batch may have rendered past the wall clock and retired a
            // still-playing voice. Reproject from its last uncommitted timeline.
            t.mixer = std::move(t.stableCheckpoint);
            std::erase_if(t.ends, [&](const auto& end) { return end.at > t.mixer->now(); });
        }
        if (!resumeOnMotors) endVoices(t, why);
        t.stableCheckpoint.reset();
        t.frame.reset();
        if (t.write && t.write->done)
        {
            auto rc = t.write->receipt->load();
            t.write->done(rc < 0 ? NativeError::Busy : static_cast<NativeError>(rc));
        }
        Fence f;
        if (t.original && t.write) f.originalWrite = std::move(t.write);
        t.original.reset();
        t.write.reset();
        t.preparing.reset();
        if (t.raw && leases.contains(t.raw))
            leases.at(t.raw).snap = {RawState::Closed, {}, why};
        f.endpoint    = t.writer;
        f.mobile      = t.mobile;
        f.deadline    = clockUs() + StopUs;
        f.needsNative = t.written;
        f.reason      = why;
        f.resumeOnMotors = resumeOnMotors;
        if (t.pcm && t.written)
        {
            f.exitMs = t.timing.exitMs;
            f.deadline += Time(t.timing.enterMs + f.exitMs) * 1000;
        }
        t.pcmLive = false;
        t.fence       = std::move(f);
        wake.notify_one();
    }
    void publish(std::optional<DeviceId> device, Endpoint key, bool interrupt, bool release)
    {
        if (auto it = routes.find(device); it != routes.end())
        {
            auto& t = targets.at(it->second);
            if (t.route != key)
            {
                dropScheduled(t, StopReason::EndpointLost);
                revokePending(t, leases, Error::StaleTarget);
                startStop(t, StopReason::EndpointLost);
            }
            t.route      = key;
            t.interrupt  = interrupt;
            t.rawCapable = release;
            t.published  = true;
        }
        else
        {
            auto id        = static_cast<TargetId>(nextIdentity++);
            auto& t        = targets[id];
            t.info         = {id, device};
            t.route        = key;
            t.interrupt    = interrupt;
            t.rawCapable   = release;
            routes[device] = id;
        }
    }
    void stopAfterWriteError(Target& t, NativeError error, Error failure)
    {
        if (error == NativeError::Disconnected)
        {
            dropScheduled(t, StopReason::EndpointLost);
            revokePending(t, leases, Error::StaleTarget);
        }
        else
            for (auto& [key, voice] : t.voices)
                finish(voice.id, PlaybackState::Failed, {}, failure);
        startStop(t, StopReason::EndpointLost);
    }
    std::pair<Receipt, NativeError> send(
        Endpoint endpoint, input::OutputCommand command, Gate gate, Time deadline = 0, bool waveform = false)
    {
        if (!backend || sequence == UINT32_MAX)
            return {{}, NativeError::QueueFull};
        auto id     = static_cast<input::CommandId>(++sequence);
        auto result = std::make_shared<std::atomic<int>>(-1);
        queue.expectBody(endpoint, id, result);
        input::detail::NativeCommand cmd{
            id, std::move(command), waveform, {}, std::move(gate), static_cast<std::uint64_t>(deadline) * 1000};
        auto error = backend->submit(endpoint, cmd);
        return {result, error};
    }
    bool compatPendingOrPlaying(const Target& target) const
    {
        if (!compatScope)
            return false;
        return std::ranges::any_of(target.scheduled, [&](const auto& v) { return v.id.scope == compatScope; }) ||
               std::ranges::any_of(target.voices, [&](const auto& v) { return v.second.id.scope == compatScope; });
    }
    bool conflicts(const Target& target) const
    {
        for (const auto& [id, other] : targets)
        {
            if (&target == &other || target.info.device.has_value() == other.info.device.has_value())
                continue;
            if ((target.caps.conflictsWithGamepads || other.caps.conflictsWithGamepads) &&
                (other.owner != Owner::Idle || other.fence || other.restricted))
                return true;
        }
        return false;
    }
    std::pair<Receipt, NativeError> mobileWrite(Target& t, MobileCommand cmd)
    {
        auto receipt = std::make_shared<std::atomic<int>>(-1);
        auto now     = clockUs();
        if (t.caps.platform == MobilePlatform::Android)
        {
            if (t.writeBudget.availableAt(now) > now)
                return {{}, NativeError::QueueFull};
            t.writeBudget.record(now);
        }
        auto e = t.mobile->submit(std::move(cmd), t.gate, receipt);
        return {receipt, e};
    }
    std::pair<Receipt, NativeError> motorWrite(Target& t, const Rumble& r, Time deadline)
    {
        auto scaled = r;
        const auto peak = static_cast<float>(settings.strength * t.profile.peakCap);
        const auto powerBound = static_cast<float>(settings.strength * std::sqrt(t.profile.energyCap));
        const auto length = std::hypot(r.low, r.high);
        auto scale = static_cast<float>(settings.strength);
        if (length > 0 && (settings.strength < 1 || t.profile.energyCap < 1))
            scale = std::min(scale, powerBound / length);
        scaled.low = std::min(peak, r.low * scale);
        scaled.high = std::min(peak, r.high * scale);
        if (!t.mobile)
            return send(t.writer, scaled, t.gate, deadline);
        MobileCommand cmd;
        cmd.startUs        = clockUs();
        cmd.endUs          = std::min(deadline, cmd.startUs + Second);
        cmd.immediateStart = true;
        t.legacyEffect     = r;
        t.legacyNext       = cmd.endUs;
        auto duration      = static_cast<unsigned>(std::max<Time>(1, (cmd.endUs - cmd.startUs + 999) / 1000));
        cmd.packet.samples.push_back({duration, t.caps.stereo ? scaled.low : std::max(scaled.low, scaled.high), 0.5f, scaled.high, 0.5f});
        return mobileWrite(t, std::move(cmd));
    }
    void install(Target& t, Handover next, Time now)
    {
        if (next.mode != Owner::Preset && t.warmGate) t.warmGate->store(false);
        t.gate      = std::make_shared<std::atomic_bool>(true);
        t.owner     = next.mode;
        t.writer    = t.route;
        t.written   = false;
        t.last      = {};
        t.lastWrite = 0;
        t.expires   = 0;
        if (next.mode == Owner::Raw)
        {
            t.raw   = next.raw;
            auto it = leases.find(next.raw);
            if (it != leases.end())
            {
                it->second.snap      = {RawState::Ready, {}};
                it->second.idleSince = now;
            }
        }
        else if (next.mode == Owner::LegacyRumble || next.mode == Owner::LegacyPcm)
        {
            bool pcm = next.mode == Owner::LegacyPcm;
            t.pcm    = next.pcm;
            if (pcm)
            {
                t.writer = t.pcm->hid;
                if (t.pcm->setStrength) t.pcm->setStrength(nativeCeiling(t));
            }
            else
                t.expires = now + next.rumble.duration.count() * 1000;
            auto [receipt, e] =
                pcm ? send(t.writer, Stop{Channel::Body}, t.gate, 0, true) : motorWrite(t, next.rumble, t.expires);
            if (e != NativeError::None)
            {
                if (next.done)
                    next.done(e);
                startStop(t, StopReason::Replaced);
                return;
            }
            t.written = true;
            t.write   = Write{receipt, now, std::move(next.done), {}};
        }
    }
    void fault(Target& t, Error error)
    {
        t.fault = true;
        if (t.fence)
        {
            if (t.fence->resumeOnMotors)
            {
                t.fence->resumeOnMotors = false;
                endVoices(t, StopReason::EndpointLost);
                dropScheduled(t, StopReason::EndpointLost);
            }
            finishOp(t.fence->operation, error);
            if (t.fence->done)
            {
                t.fence->done(NativeError::BackendFailure);
                t.fence->done = {};
            }
        }
        revokePending(t, leases, error);
    }
    void fenceStep(Target& t, Time now)
    {
        auto& f = *t.fence;
        if (now >= f.deadline && !t.fault)
            fault(t, Error::TimedOut);
        if (t.pcm && !f.audioStopped)
        {
            if (f.audioFault && !f.disconnected)
                return;
            if (f.audioFault)
                f.audioStopped = true;
            if (t.audioJob.valid())
            {
                if (t.audioJob.wait_for(0ms) != std::future_status::ready)
                    return;
                auto result = t.audioJob.get();
                if (!t.enabling && result != NativeError::None && result != NativeError::Disconnected &&
                    !f.disconnected)
                {
                    f.audioFault = true;
                    fault(t, Error::BackendFailure);
                    return;
                }
                if (!t.enabling)
                    f.audioStopped = true;
                t.enabling = false;
            }
            if (!f.audioStopped)
            {
                t.audioJob =
                    std::async(std::launch::async, [pcm = t.pcm, why = f.reason] { return pcm->silence(why); });
                return;
            }
        }
        if (f.originalWrite)
        {
            const int rc = f.originalWrite->receipt->load();
            if (rc < 0 && !f.disconnected && now < f.deadline) return;
            if (rc == int(mobileOriginalDeclined)) f.needsNative = false;
            f.uncertainOriginal = rc < 0 || rc == int(NativeError::BackendFailure);
            if (rc == int(NativeError::None) || rc == int(mobileHeSubmitted)) recordSubmission(*f.originalWrite);
            f.originalWrite.reset();
        }
        if (f.needsNative)
        {
            if (!f.receipt)
            {
                if (f.retry > now || f.attempts >= 3)
                    return;
                Receipt r;
                NativeError e;
                if (f.mobile)
                {
                    r = std::make_shared<std::atomic<int>>(-1);
                    MobileCommand stop;
                    stop.kind = MobileCommand::Kind::Stop;
                    e         = f.mobile->submit(std::move(stop), f.gate, r);
                }
                else
                    std::tie(r, e) = send(f.endpoint, Stop{Channel::Body}, f.gate);
                if (e == NativeError::QueueFull || e == NativeError::Busy)
                {
                    f.retry = now + 10000;
                    return;
                }
                if (e != NativeError::None && e != NativeError::Disconnected)
                {
                    ++f.attempts;
                    f.retry = now + 50000;
                    return;
                }
                if (e == NativeError::None)
                    f.receipt = r;
            }
            if (f.receipt)
            {
                auto value = f.receipt->load();
                if (value < 0)
                    return;
                if (value == int(NativeError::Unsupported) && f.mobile && !f.mobile->capabilities().canStop)
                {
                    // Cancellation has reached the platform, but it cannot prove silence to another owner.
                    t.restricted = t.owner;
                    // A possibly started author player has no reliable phase or
                    // cancellation boundary. Even a same-owner rewrite must wait
                    // for silence or disconnect. The ordinary fence deadline faults it.
                    if (f.uncertainOriginal && !f.disconnected) return;
                    finishOp(f.operation, Error::Unsupported);
                    if (f.done)
                    {
                        f.done(NativeError::Unsupported);
                        f.done = {};
                    }
                    revokePending(t, leases, Error::Unsupported);
                }
                else if (value != int(NativeError::None) && value != int(NativeError::Disconnected))
                {
                    f.receipt.reset();
                    ++f.attempts;
                    f.retry = now + 20000;
                    return;
                }
            }
        }
        if (f.exitMs && !f.disconnected)
        {
            if (!f.exitReady) {
                f.exitReady = now + Time(f.exitMs) * 1000;
                if (t.realtime && t.trace && f.receipt && f.receipt->load() == int(NativeError::None))
                    t.trace->exitWriteUs = now;
            }
            if (now < f.exitReady) return;
        }
        // A finite mobile preset may replace itself on the same vibrator after
        // cancellation, even where physical silence cannot be certified to Raw.
        const bool samePreset = f.reason == StopReason::Reconfigured && f.mobile &&
                                t.restricted == Owner::Preset && t.owner == Owner::Preset &&
                                f.receipt && f.receipt->load() == int(NativeError::Unsupported);
        bool resume = f.resumeOnMotors && enabled() && active && t.published && !t.fault && !f.disconnected &&
                      (!f.needsNative || samePreset || (f.receipt && f.receipt->load() == int(NativeError::None)));
        if (f.resumeOnMotors && !resume)
        {
            endVoices(t, StopReason::EndpointLost);
            dropScheduled(t, StopReason::EndpointLost);
        }
        f.gate->store(false);
        finishOp(f.operation);
        if (f.done)
            f.done(NativeError::None);
        t.fence.reset();
        t.pcm.reset();
        if (t.realtime && t.trace)
        {
            copyAudioTrace(t);
            if (!t.fault && t.trace->exitWriteUs) t.trace->silentUs = now;
        }
        t.realtime.reset();
        t.synth.reset();
        t.modeWrite.reset();
        t.modeReady = 0;
        t.firstAudioFrame.reset();
        t.raw     = 0;
        t.player  = 0;
        t.owner   = Owner::Idle;
        t.fault   = false;
        t.written = false;
        if (resume && !t.reproject)
        {
            if (t.mixer) t.mixer->resumeOnMotors(now);
            t.nextGrid = t.mixer ? t.mixer->now() : 0;
            install(t, Handover{Owner::Preset}, now);
        }
        t.reproject = resume && t.reproject;
        if (t.successor)
        {
            auto next = std::move(*t.successor);
            t.successor.reset();
            if (enabled() && active && t.published)
                install(t, std::move(next), now);
        }
    }
    void retire(Target& t, Time now)
    {
        for (auto it = t.ends.begin(); it != t.ends.end();)
        {
            if (it->at > now)
            {
                ++it;
                continue;
            }
            auto found = t.voices.find(it->id);
            if (found != t.voices.end())
            {
                auto id = found->second.id;
                if (it->outcome == Outcome::Coalesced && t.voices.contains(it->mergedInto) && plays.contains(id))
                    plays.at(id).mergedInto = t.voices.at(it->mergedInto).id;
                switch (it->outcome)
                {
                case Outcome::Ended:
                    finish(id, PlaybackState::Completed);
                    break;
                case Outcome::Preempted:
                    finish(id, PlaybackState::Preempted, StopReason::Priority);
                    break;
                case Outcome::Dropped:
                    finish(id, PlaybackState::Dropped, StopReason::Priority);
                    break;
                case Outcome::Coalesced:
                    finish(id, PlaybackState::Coalesced);
                    break;
                case Outcome::Stopped:
                    finish(id, PlaybackState::Stopped, StopReason::Requested);
                    break;
                }
                t.voices.erase(found);
            }
            it = t.ends.erase(it);
        }
    }
    Calibration calibration(const Target& t, bool pcm) const
    {
        Calibration c;
        const auto& p = t.profile;
        c.layout = pcm || (t.mobile && t.caps.stereo) ? Layout::LeftRight :
                   t.mobile || !t.info.device ? Layout::Mono : Layout::LowHigh;
        c.gain = p.gain;
        c.gamma = p.gamma;
        c.continuousGain = p.continuousGain;
        c.transientGain = p.transientGain;
        c.strength = settings.strength;
        c.textureBias = p.textureBias;
        c.textureScale = p.textureScale;
        c.channelGain = c.layout == Layout::Mono ? Channels{p.monoGain, 0} : Channels{p.leftGain, p.rightGain};
        c.cap = {p.peakCap, p.peakCap};
        c.totalCap = std::sqrt(p.energyCap);
        c.pulseWidth = t.mobile ? 1000 : GridUs;
        return c;
    }
    float nativeCeiling(const Target& t) const
    {
        return static_cast<float>(settings.strength * std::min(t.profile.peakCap, std::sqrt(t.profile.energyCap)));
    }
    void refreshSettings(Target& t)
    {
        if (!enabled())
        {
            if (t.warmGate) t.warmGate->store(false);
            dropScheduled(t, StopReason::Disabled);
            revokePending(t, leases, Error::Disabled);
            if (t.owner != Owner::Idle || t.fence) startStop(t, StopReason::Disabled);
        }
        else if (t.owner == Owner::Preset && !t.fence)
        {
            // Revoke immutable batches first, then continue the surviving mixer at
            // its absolute logical time. A real stop or focus loss cancels the resume.
            t.reproject = true;
            startStop(t, StopReason::Reconfigured, true);
        }
        else if (t.owner != Owner::Idle && !t.fence)
            startStop(t, StopReason::Reconfigured);
        if (t.successor && !enabled()) revokePending(t, leases, Error::Disabled);
        wake.notify_one();
    }
    void setFocus(bool value, bool platform)
    {
        (platform ? applicationActive : directorActive) = value;
        bool next                                       = applicationActive && directorActive;
        if (next == active)
            return;
        active = next;
        if (!active)
            for (auto& [id, t] : targets)
            {
                if (t.warmGate) t.warmGate->store(false);
                dropScheduled(t, StopReason::FocusLost);
                revokePending(t, leases, Error::NotFocused);
                if (t.owner != Owner::Idle)
                    startStop(t, StopReason::FocusLost);
            }
        wake.notify_one();
    }
    static void copyAudioTrace(Target& t)
    {
        auto src = t.realtime->poll().trace;
        t.trace->peakQueuedFrames = src.peakQueuedFrames;
        t.trace->generation = src.generation;
        t.trace->lastNonzeroFrame = src.lastNonzeroFrame;
        t.trace->discardBound = src.discardBound;
        t.trace->firstSubmitUs = src.firstSubmitUs;
        t.trace->discardUs = src.discardUs;
    }
    bool readyPcm(Target& t, Time now);
    void render(Target& t, Time now);
    void runTarget(Target& t, Time now);
    void run()
    {
        std::unique_lock lock(mutex);
        while (!closing)
        {
            bool work = false;
            auto now  = clockUs();
            for (auto& [id, t] : targets)
            {
                runTarget(t, now);
                work |= t.owner != Owner::Idle || t.fence.has_value() || !t.scheduled.empty() || t.warm != nullptr;
            }
            std::erase_if(targets, [&](const auto& p) {
                if (p.second.published || p.second.fence || p.second.owner != Owner::Idle)
                    return false;
                auto it = routes.find(p.second.info.device);
                if (it != routes.end() && it->second == p.first)
                    routes.erase(it);
                return true;
            });
            changed.notify_all();
            if (work)
                wake.wait_for(lock, 2ms);
            else
                wake.wait(lock);
        }
    }
};

void HapticControl::State::render(Target& t, Time now)
{
    // Leave the next mix interval unconsumed while another writer uses the vibrator budget.
    if (t.caps.platform == MobilePlatform::Android && t.writeBudget.availableAt(now) > now)
        return;
    std::optional<audio::detail::GripWindow> window;
    if (t.realtime)
    {
        window = t.realtime->poll().window;
        if (!window || t.write) return;
        if (!t.firstAudioFrame)
        {
            t.firstAudioFrame = window->firstFrame;
            t.audioEpochUs = window->startUs;
        }
    }
    bool replacement = false;
    if (t.stableCheckpoint && now >= t.stableStart + 200000 && now < t.nextGrid &&
        std::ranges::any_of(t.scheduled, [&](auto& v) { return v.due <= now; }))
    {
        t.mixer = std::move(t.stableCheckpoint);
        std::erase_if(t.ends, [&](auto& e) { return e.at > now; });
        t.nextGrid  = now;
        replacement = true;
    }
    const Time lookAhead = t.caps.platform == MobilePlatform::Apple ? 20000 : 0;
    if ((!window && t.nextGrid > now + lookAhead) || t.frame)
        return;
    if (!t.mixer)
        t.mixer = std::make_unique<HapticMixer>(calibration(t, window.has_value()));
    else if (t.reproject)
        t.mixer->recalibrate(calibration(t, window.has_value()), now);
    t.reproject = false;
    Time begin = t.nextGrid ? t.nextGrid : now;
    if (window)
        begin = t.audioEpochUs + Time(window->firstFrame - *t.firstAudioFrame) * Second / 48000;
    else if (now - begin > 8000)
        begin = now;
    for (auto& s : t.scheduled)
        if (!window && s.due <= now && !s.immediate && !t.nextGrid)
            begin = std::min(begin, std::max(now - 8000, s.due));
    t.mixer->skipTo(begin);
    if (window) t.mixer->sampleBlockStart();
    bool immediateStart = false;
    // A candidate exists only in the admission pass that consumes its Scheduled record.
    // Restoring a mixer checkpoint therefore cannot retry an original.
    std::optional<HapticClip> candidate;
    for (auto it = t.scheduled.begin(); it != t.scheduled.end();)
    {
        if (it->due > (window ? begin + 5333 : now))
        {
            ++it;
            continue;
        }
        if (!t.nextGrid && it->immediate)
            immediateStart = true;
        auto logical  = it->immediate ? std::max(it->received, begin) : it->due;
        auto accepted = t.mixer->submitAt(it->clip, it->options, it->received, logical);
        if (accepted.value)
        {
            auto& snap          = plays.at(it->id);
            snap.logicalStartUs = logical;
            snap.state          = PlaybackState::Active;
            const auto& clip    = ClipAccess::get(it->clip);
            auto flat           = [](const Curve& c) {
                return c.empty() || std::ranges::all_of(c, [&](const Point& p) { return p.value == c.front().value; });
            };
            bool constant = t.mobile && clip.pulses.empty() && clip.layers.size() == 1 &&
                            clip.layers.front().start == 0 && clip.layers.front().end == clip.duration &&
                            flat(clip.amplitude) && flat(clip.frequency) && flat(clip.layers.front().envelope) &&
                            flat(clip.layers.front().textureOffset) &&
                            std::ranges::all_of(clip.controls, [](const auto& v) { return v.empty(); });
            if (t.mobile && !t.info.device && !t.written && !replacement && t.voices.empty() &&
                !t.nextGrid && it->immediate && logical == begin && it->options.gain == 1 &&
                it->options.pan == 0 && it->options.iterations == 1 && it->options.track == Track::Normal &&
                settings.strength == 1 && t.profile == HapticCalibration{} && clip.nativeEligible)
            {
                const bool he = clip.heFitsPlayer && !t.caps.envelope &&
                    ((clip.format == AssetFormat::RichTapHeV1 && t.caps.heV1) ||
                     (clip.format == AssetFormat::RichTapHeV2 && t.caps.heV2));
                // Native transients have device-specific tails. Overlapping native
                // layers may sum differently from the portable power allocator.
                bool apple = clip.format == AssetFormat::AppleAhap && t.caps.ahap && clip.pulses.empty();
                Time previousEnd = 0;
                for (const auto& layer : clip.layers)
                {
                    apple &= layer.start >= previousEnd;
                    previousEnd = layer.tail;
                }
                if (he || apple) candidate = it->clip;
            }
            t.voices.emplace(*accepted.value, VoiceRecord{it->id, logical + it->span, constant});
        }
        else
            finish(it->id, PlaybackState::Failed, {}, accepted.error->code);
        it = t.scheduled.erase(it);
    }
    if (window)
    {
        if (t.voices.empty()) return;
        const Time end = t.audioEpochUs + Time(window->firstFrame - *t.firstAudioFrame + 256) * Second / 48000;
        std::vector<Entry> entries;
        std::vector<Id> activeVoices;
        std::vector<PlaybackId> contributors;
        for (auto& [voice, rec] : t.voices) activeVoices.push_back(voice);
        t.mixer->advance(end, [&](const Entry& entry) {
            if (entry.reason != Reason::None || (entry.amplitude[0] == 0 && entry.amplitude[1] == 0)) return;
            entries.push_back(entry);
            if (auto found = t.voices.find(entry.key.playback); found != t.voices.end() &&
                std::find(contributors.begin(), contributors.end(), found->second.id) == contributors.end())
                contributors.push_back(found->second.id);
        });
        auto receipt = std::make_shared<std::atomic<int>>(-1);
        auto submittedAt = std::make_shared<std::atomic<Time>>(0);
        t.realtime->supply(*window,
            [synth=t.synth, first=window->firstFrame, begin, entries=std::move(entries), active=std::move(activeVoices)] {
                return synth->render(first, begin, entries, active);
            }, [receipt, submittedAt](AudioOutputError e, bool sound) {
                if (e == AudioOutputError::None && sound) submittedAt->store(clockUs());
                receipt->store(e == AudioOutputError::None ? int(sound ? NativeError::None : mobileNoOutput)
                                                            : int(NativeError::BackendFailure));
            });
        t.write = Write{receipt, now, {}, std::move(contributors)};
        t.write->pcmSamples = true;
        t.write->pcmSubmittedAt = std::move(submittedAt);
        t.nextGrid = end;
        auto ends = t.mixer->takeTerminals();
        t.ends.insert(t.ends.end(), ends.begin(), ends.end());
        return;
    }
    if (t.mobile)
    {
        if (t.voices.empty())
            return;
        Time lastEnd = begin;
        for (auto& [id, v] : t.voices)
            lastEnd = std::max(lastEnd, v.end);
        bool constant = t.voices.size() == 1 && t.voices.begin()->second.constant;
        // A constant loop can span many source iterations in one finite native effect.
        Time width = constant ? Second : (t.caps.platform == MobilePlatform::Apple ? 40000 : t.batchUs);
        Time writableEnd = begin + width;
        for (auto& future : t.scheduled)
            if (future.due > begin)
                writableEnd = std::min(writableEnd, future.due);
        Time end = std::min(writableEnd, lastEnd);
        if (end <= begin)
        {
            if (begin > now)
                return;
            end = begin + 1;
        }
        t.stableCheckpoint = t.mixer->checkpoint();
        t.stableStart = begin;
        std::vector<PlaybackId> contributors;
        auto packet = mobilePacket(*t.mixer, begin, end, t.caps.platform, [&](Id id) {
            if (auto v = t.voices.find(id);
                v != t.voices.end() &&
                std::find(contributors.begin(), contributors.end(), v->second.id) == contributors.end())
                contributors.push_back(v->second.id);
        });
        const bool nonzero =
            !packet.transients.empty() || !packet.rightTransients.empty() ||
            std::ranges::any_of(packet.samples, [](auto& p) { return p.amplitude > 0 || p.rightAmplitude > 0; });
        if (nonzero)
        {
            MobileCommand cmd;
            // Reserve the start jitter as well as the content. A late native call
            // must neither truncate its tail nor extend into the next voice's window.
            const Time startSlack = std::min({Time(8000), writableEnd - lastEnd, end - begin});
            if (candidate && t.voices.size() == 1 && contributors.size() == 1 && startSlack > 0)
            {
                cmd.original = std::move(candidate);
                cmd.player = contributors.front().serial;
                cmd.latestOriginalStartUs = begin + startSlack;
                t.original = contributors.front();
            }
            cmd.packet         = std::move(packet);
            cmd.startUs        = begin;
            cmd.endUs          = end;
            cmd.immediateStart = immediateStart;
            cmd.replace        = replacement;
            auto [receipt, e]  = mobileWrite(t, std::move(cmd));
            if (e == NativeError::None)
            {
                t.write   = Write{receipt, now, {}, std::move(contributors)};
                t.written = true;
                t.expires = t.original ? end + startSlack : end;
            }
            else if (t.original)
            {
                t.original.reset();
                t.mixer = std::move(t.stableCheckpoint);
                t.nextGrid = now;
                if (e != NativeError::QueueFull && e != NativeError::Busy)
                    stopAfterWriteError(t, e, Error::BackendFailure);
                return;
            }
            else if (e != NativeError::QueueFull && e != NativeError::Busy)
            {
                stopAfterWriteError(t, e, Error::BackendFailure);
                return;
            }
        }
        t.nextGrid = end;
        auto ends  = t.mixer->takeTerminals();
        t.ends.insert(t.ends.end(), ends.begin(), ends.end());
        return;
    }
    Time end = begin + GridUs;
    MotorFrame frame;
    frame.due = end;
    Channels energy{}, peak{}, instant{};
    Time instantAt = -1;
    auto savePeak  = [&] {
        if (instant[0] + instant[1] > peak[0] + peak[1])
            peak = instant;
    };
    t.mixer->advance(end, [&](const Entry& e) {
        if (e.reason != Reason::None || (e.amplitude[0] == 0 && e.amplitude[1] == 0))
            return;
        frame.due = std::min(frame.due, e.at);
        if (auto v = t.voices.find(e.key.playback); v != t.voices.end())
        {
            frame.end = std::max(frame.end, v->second.end);
            if (std::find(frame.contributors.begin(), frame.contributors.end(), v->second.id) ==
                frame.contributors.end())
                frame.contributors.push_back(v->second.id);
        }
        if (e.pulse && instantAt != e.at)
        {
            savePeak();
            instant   = {};
            instantAt = e.at;
        }
        for (int k = 0; k < 2; ++k)
        {
            double p = e.amplitude[k] * e.amplitude[k];
            if (e.pulse)
                instant[k] += p;
            else
                energy[k] += p * double(std::max<Time>(0, std::min(end, e.validUntil) - e.at)) / GridUs;
        }
    });
    savePeak();
    double sum = 0;
    for (int k = 0; k < 2; ++k)
    {
        energy[k]  = std::max(energy[k], peak[k]);
        sum       += energy[k];
    }
    for (int k = 0; k < 2; ++k)
        frame.levels[k] = std::floor(31 * std::sqrt(energy[k] / std::max(1., sum))) / 31.;
    if (frame.contributors.empty())
        frame.due = begin;
    t.frame    = std::move(frame);
    t.nextGrid = end;
    auto ends  = t.mixer->takeTerminals();
    t.ends.insert(t.ends.end(), ends.begin(), ends.end());
}

bool HapticControl::State::readyPcm(Target& t, Time now)
{
    auto status = t.realtime->poll();
    if (status.error != AudioOutputError::None)
    {
        t.pcmUnavailable = true;
        if (!t.written)
        {
            // Only silence reached the audio endpoint. The same request can use the ordinary motor.
            t.realtime.reset();
            t.pcm.reset();
            t.synth.reset();
            return true;
        }
        startStop(t, StopReason::EndpointLost, true);
        return false;
    }
    if (!t.pcmLive && now - t.prepareAt > 500000)
    {
        t.pcmUnavailable = true;
        startStop(t, StopReason::EndpointLost, true);
        return false;
    }
    if (!status.prepared) return false;
    if (!t.modeWrite)
    {
        auto [receipt, rc] = send(t.writer, Stop{Channel::Body}, t.gate, 0, true);
        if (rc == NativeError::QueueFull || rc == NativeError::Busy) return false;
        if (rc != NativeError::None)
        {
            t.pcmUnavailable = true;
            startStop(t, StopReason::EndpointLost, true);
            return false;
        }
        t.written = true;
        t.modeWrite = std::move(receipt);
        return false;
    }
    if (t.pcmLive) return true;
    const int result = t.modeWrite->load();
    if (result < 0) return false;
    if (result != int(NativeError::None))
    {
        t.pcmUnavailable = true;
        startStop(t, StopReason::EndpointLost, true);
        return false;
    }
    if (!t.modeReady)
    {
        t.modeReady = now + Time(t.timing.enterMs) * 1000;
        t.trace->modeWriteUs = now;
    }
    if (now < t.modeReady) return false;
    t.realtime->enable();
    t.pcmLive = true;
    return true;
}
void HapticControl::State::runTarget(Target& t, Time now)
{
    if (t.warm)
    {
        if (now >= t.warmUntil) t.warmGate->store(false);
        const auto status = t.warm->poll();
        if (status.finished)
        {
            if (t.warmGate->load() && status.error != AudioOutputError::None) t.pcmUnavailable = true;
            t.warm.reset();
            t.warmGate.reset();
        }
    }
    if (t.fence)
        fenceStep(t, now);
    bool due = std::any_of(t.scheduled.begin(), t.scheduled.end(), [&](auto& s) { return s.due <= now; });
    if (t.fence && t.fence->resumeOnMotors) return;
    if (due && (t.fence || conflicts(t) || (t.restricted && *t.restricted != Owner::Preset) ||
                (t.owner != Owner::Idle && t.owner != Owner::Preset)))
    {
        std::erase_if(t.scheduled, [&](auto& s) {
            if (s.due > now)
                return false;
            finish(s.id, PlaybackState::Failed, {}, t.fault ? Error::Unavailable : Error::Busy);
            return true;
        });
        due = false;
    }
    if (t.fence)
        return;
    if (t.write)
    {
        int rc = t.write->receipt->load();
        if (rc >= 0)
        {
            auto w = std::move(*t.write);
            t.write.reset();
            auto error = static_cast<NativeError>(rc);
            if (error == mobileHeSubmitted)
            {
                // Match the handset profile's 125 ms asynchronous startup allowance.
                // Retain the current Preset writer, so incoming voices can still
                // render or interrupt at their ordinary admission boundary.
                t.heDrainUntil = now + (t.nextGrid - t.stableStart) + 125000;
                error = NativeError::None;
            }
            if (t.original && error == mobileOriginalDeclined)
            {
                // Construction or policy checks failed before start. The first
                // writable suffix belongs to the same logical voice.
                t.original.reset();
                t.written = false;
                t.mixer = std::move(t.stableCheckpoint);
                t.ends.clear(); // The original was the only voice in this interval.
                t.nextGrid = now;
                t.expires = 0;
                error = mobileNoOutput;
            }
            else if (t.original && error == NativeError::BackendFailure)
            {
                t.reproject = true;
                startStop(t, StopReason::Reconfigured, true);
                t.fence->uncertainOriginal = true;
                return;
            }
            if (t.original && error == NativeError::None)
                t.expires = std::min(t.expires, now + t.nextGrid - t.stableStart);
            if (error == NativeError::None && w.rawSpan)
            {
                t.playerOrigin = now;
                t.expires      = now + w.rawSpan;
            }
            if (w.done)
                w.done(error);
            if (error == mobileNoOutput)
                error = NativeError::None;
            else if (error == NativeError::None)
                recordSubmission(w);
            if (error != NativeError::None || now - w.at > 500000)
            {
                if (t.realtime)
                {
                    t.pcmUnavailable = true;
                    startStop(t, StopReason::EndpointLost, true);
                }
                else
                    stopAfterWriteError(t, error, error == NativeError::None ? Error::TimedOut : Error::BackendFailure);
                return;
            }
            if (t.owner == Owner::LegacyPcm && t.pcm)
            {
                t.enabling = true;
                t.audioJob = std::async(std::launch::async, [pcm = t.pcm, gate = t.gate, guard = t.timing.enterMs] {
                    if (guard) std::this_thread::sleep_for(std::chrono::milliseconds(guard));
                    return gate->load() ? pcm->enable() : NativeError::Busy;
                });
            }
        }
        else if (now - t.write->at > 500000)
        {
            for (auto& [key, v] : t.voices)
                finish(v.id, PlaybackState::Failed, {}, Error::TimedOut);
            startStop(t, StopReason::EndpointLost);
            return;
        }
    }
    if (t.owner == Owner::LegacyPcm && t.pcm && !t.write)
    {
        if (t.audioJob.valid())
        {
            if (t.audioJob.wait_for(0ms) != std::future_status::ready)
                return;
            t.enabling = false;
            if (t.audioJob.get() != NativeError::None)
            {
                startStop(t, StopReason::EndpointLost);
                return;
            }
        }
        if (t.pcm->ended())
            startStop(t, StopReason::None);
        return;
    }
    if (t.mobile && t.owner == Owner::LegacyRumble && !t.write && now >= t.legacyNext && now < t.expires)
    {
        auto [receipt, error] = motorWrite(t, t.legacyEffect, t.expires);
        if (error == NativeError::None)
            t.write = Write{receipt, now, {}, {}};
        else if (error != NativeError::QueueFull && error != NativeError::Busy)
            stopAfterWriteError(t, error, Error::BackendFailure);
        return;
    }
    if (t.owner == Owner::LegacyRumble && now >= t.expires)
    {
        startStop(t, StopReason::None);
        return;
    }
    if (t.owner == Owner::Raw && leases.contains(t.raw) &&
        now - std::max(t.expires, leases.at(t.raw).idleSince) >= 2000000)
    {
        startStop(t, StopReason::IdleExpired);
        return;
    }
    if ((due || (t.reproject && !t.voices.empty())) && t.owner == Owner::Idle && enabled())
    {
        install(t, Handover{Owner::Preset}, now);
        t.nextGrid = 0;
        if (t.paired && t.timing.enterMs && !t.pcmUnavailable)
        {
            if (t.warm && t.warmGate->load())
            {
                t.realtime = std::move(t.warm);
                t.gate = std::move(t.warmGate);
            }
            else
                t.realtime = audio::detail::prepareRealtimeHaptics(*t.paired, t.gate, wake);
            t.trace.emplace();
            t.synth = std::make_shared<GripSynth>();
            t.pcm = std::make_shared<PcmSource>();
            t.pcm->hid = t.route;
            t.pcm->silence = [stream=t.realtime](StopReason) {
                auto rc = stream->stop();
                return rc == AudioOutputError::None ? NativeError::None :
                       rc == AudioOutputError::Disconnected ? NativeError::Disconnected : NativeError::BackendFailure;
            };
            t.prepareAt = now;
        }
        if (t.mobile)
        {
            t.preparing = std::make_shared<std::atomic<int>>(-1);
            t.prepareAt = now;
            auto e      = t.mobile->prepare(t.gate, t.preparing);
            if (e != NativeError::None)
                t.preparing->store(int(e));
        }
    }
    if (t.owner != Owner::Preset)
        return;
    if (t.realtime && !readyPcm(t, now)) return;
    if (t.preparing)
    {
        auto rc = t.preparing->load();
        if (rc < 0 && now - t.prepareAt < 500000)
            return;
        t.preparing.reset();
        if (rc != int(NativeError::None))
        {
            for (auto& p : t.scheduled)
                finish(p.id, PlaybackState::Failed, {}, rc < 0 ? Error::TimedOut : Error::BackendFailure);
            t.scheduled.clear();
            startStop(t, StopReason::EndpointLost);
            return;
        }
    }
    if (t.original && !t.write)
    {
        if (now < t.expires)
        {
            if (due)
            {
                t.reproject = true;
                startStop(t, StopReason::Reconfigured, true);
            }
            return;
        }
        // The full mixer interval was already consumed. Complete this generation
        // and release its finite player before dequeuing another preset.
        finish(*t.original, PlaybackState::Completed);
        t.voices.clear();
        if (!due && now < t.heDrainUntil) return;
        t.reproject = !t.scheduled.empty();
        startStop(t, t.reproject ? StopReason::Reconfigured : StopReason::None, t.reproject);
        return;
    }
    if (!t.write)
        retire(t, now);
    if (t.frame && t.nextGrid + 8000 <= now)
        t.frame.reset();
    if (!t.mobile || !t.write)
        render(t, now);
    if (t.frame && t.frame->due <= now && !t.write)
    {
        auto frame = std::move(*t.frame);
        t.frame.reset();
        bool nonzero       = frame.levels[0] > 0 || frame.levels[1] > 0;
        bool levelsChanged = t.last != frame.levels;
        if ((nonzero && frame.end > now && (levelsChanged || now + GridUs + 2000 >= t.expires)) ||
            (!nonzero && levelsChanged))
        {
            if (nonzero && now - t.lastWrite < 10000)
            {
                frame.due = t.lastWrite + 10000;
                t.frame   = std::move(frame);
                return;
            }
            auto deadline = std::min(frame.end, now + LeaseUs);
            auto duration = std::chrono::milliseconds(std::max<Time>(1, (deadline - now + 999) / 1000));
            input::OutputCommand command =
                nonzero ? input::OutputCommand{Rumble{float(frame.levels[0]), float(frame.levels[1]), duration}}
                        : input::OutputCommand{Stop{Channel::Body}};
            auto [r, e] = send(t.writer, command, t.gate, nonzero ? deadline : 0);
            if (e == NativeError::None)
            {
                t.write     = Write{r, now, {}, nonzero ? std::move(frame.contributors) : std::vector<PlaybackId>{}};
                t.written   = true;
                t.last      = frame.levels;
                t.expires   = deadline;
                t.lastWrite = now;
            }
            else if (e != NativeError::Busy && e != NativeError::QueueFull)
            {
                stopAfterWriteError(t, e, Error::BackendFailure);
                return;
            }
        }
    }
    if (t.voices.empty() && !t.write && !due)
        startStop(t, StopReason::None);
}

HapticControl::HapticControl(input::detail::GamepadBackend* backend, input::detail::ReportQueue& queue)
    : _state(std::make_unique<State>(backend, queue))
{
    _state->worker = std::thread([s = _state.get()] { s->run(); });
}
HapticControl::~HapticControl()
{
    shutdown();
}
void HapticControl::shutdown()
{
    auto& s = *_state;
    {
        std::lock_guard lock(s.mutex);
        if (s.closing)
            return;
        for (auto& [id, t] : s.targets)
        {
            if (t.warmGate) t.warmGate->store(false);
            t.gate->store(false);
            if (t.fence)
                t.fence->gate->store(false);
        }
        s.closing = true;
        s.lifetime.reset();
        s.scopes.clear();
        s.wake.notify_all();
        s.changed.notify_all();
    }
    s.worker.join();
    for (auto& [id, t] : s.targets)
    {
        if (t.audioJob.valid())
            t.audioJob.wait();
        if (t.pcm)
            t.pcm->silence(StopReason::FocusLost);
        auto port = t.fence ? t.fence->mobile : t.mobile;
        if (port && t.written)
        {
            MobileCommand stop;
            stop.kind    = MobileCommand::Kind::Stop;
            auto receipt = std::make_shared<std::atomic<int>>(-1);
            if (port->submit(std::move(stop), std::make_shared<std::atomic_bool>(true), receipt) == NativeError::None)
            {
                const auto until = clockUs() + StopUs;
                while (receipt->load() < 0 && clockUs() < until)
                    std::this_thread::sleep_for(2ms);
            }
        }
    }
}
void HapticControl::resetScopes()
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    for (auto& [id, t] : s.targets)
    {
        if (t.warmGate) t.warmGate->store(false);
        s.dropScheduled(t, StopReason::FocusLost);
        revokePending(t, s.leases, Error::NotFocused);
        if (t.owner != Owner::Idle || t.fence) s.startStop(t, StopReason::FocusLost);
    }
    s.wake.notify_one();
    s.scopes.clear();
    s.compatScope = 0;
    s.plays.clear();
    s.operations.clear();
    s.terminalOrder.clear();
    s.leases.clear();
    s.generation = nextIdentity++;
    s.lifetime = std::make_shared<int>(0);
    // Keep outstanding stop fences while invalidating the previous Director's target handles.
    std::map<TargetId, Target> refreshed;
    for (auto& [id, t] : s.targets)
    {
        auto freshId = id;
        if (t.published)
        {
            freshId                 = static_cast<TargetId>(nextIdentity++);
            t.info.target           = freshId;
            s.routes[t.info.device] = freshId;
        }
        refreshed.emplace(freshId, std::move(t));
    }
    s.targets.swap(refreshed);
}
void HapticControl::focused(bool active)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    s.setFocus(active, false);
}
void HapticControl::platformFocus(bool active)
{
    std::lock_guard lock(_state->mutex);
    _state->setFocus(active, true);
}
void HapticControl::publishMobile(std::shared_ptr<MobileOutput> port, std::optional<DeviceId> device, Endpoint key)
{
    if (!port)
        return;
    auto caps = port->capabilities();
    auto& s   = *_state;
    std::lock_guard lock(s.mutex);
    if (auto i = s.routes.find(device); i != s.routes.end())
    {
        auto& old = s.targets.at(i->second);
        if (old.mobile != port && old.owner != Owner::Idle)
        {
            s.dropScheduled(old, StopReason::EndpointLost);
            revokePending(old, s.leases, Error::StaleTarget);
            s.startStop(old, StopReason::EndpointLost);
        }
    }
    s.publish(device, key, caps.canStop, !device && caps.canStop);
    auto& t  = s.targets.at(s.routes.at(device));
    t.caps   = caps;
    t.mobile = std::move(port);
}
void HapticControl::forwarding(bool enabled)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (auto i = s.routes.find(std::nullopt); i != s.routes.end())
    {
        auto& phone = s.targets.at(i->second);
        if (phone.caps.conflictsWithGamepads == enabled)
            return;
        phone.caps.conflictsWithGamepads = enabled;
        if (enabled && phone.owner != Owner::Idle && s.conflicts(phone))
        {
            s.dropScheduled(phone, StopReason::EndpointLost);
            s.startStop(phone, StopReason::EndpointLost);
            for (auto& [id, t] : s.targets)
                if (t.info.device && t.owner != Owner::Idle)
                {
                    s.dropScheduled(t, StopReason::EndpointLost);
                    s.startStop(t, StopReason::EndpointLost);
                }
        }
    }
}
void HapticControl::compatVibrate(float seconds)
{
    if (!std::isfinite(seconds))
        return;
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(std::nullopt);
    if (!s.enabled() || !s.active || s.closing || it == s.routes.end())
        return;
    auto& t = s.targets.at(it->second);
    if (!t.mobile || t.owner != Owner::Idle || t.fence || t.fault || s.conflicts(t) || !t.scheduled.empty() ||
        (t.restricted && *t.restricted != Owner::Preset))
        return;
    const bool apple = t.caps.platform == MobilePlatform::Apple;
    if (!apple && seconds <= 0)
        return;
    auto data    = std::make_shared<ClipData>();
    data->format = AssetFormat::AppleAhap;
    data->policy = ImportPolicy::Compatible;
    data->nodes  = 1;
    if (apple)
    {
        data->pulses.push_back({0, 0, 1., .5});
    }
    else
    {
        data->duration = data->renderEnd = std::max<Time>(1000, std::llround(std::min(30.f, seconds) * Second));
        Layer layer;
        layer.end = layer.tail = data->duration;
        layer.intensity        = 1;
        layer.sharpness        = .5;
        data->layers.push_back(layer);
    }
    if (!s.compatScope)
    {
        s.compatScope = nextIdentity++;
        s.scopes.try_emplace(s.compatScope);
    }
    auto now = clockUs();
    PlaybackId id;
    id.scope  = s.compatScope;
    id.serial = ++s.scopes.at(s.compatScope).play;
    Request req;
    req.scope = s.compatScope;
    auto span = std::max<Time>(1000, data->duration);
    t.scheduled.push_back({id, ClipAccess::make(data), std::move(req), now, now, span, true});
    s.plays[id].requestedUs = now;
    s.wake.notify_one();
}
void HapticControl::publishGamepad(DeviceId device, Endpoint key)
{
    std::lock_guard lock(_state->mutex);
    _state->publish(device, key, true, false);
    auto& t = _state->targets.at(_state->routes.at(device));
    t.mobile.reset();
    t.caps = {};
}
void HapticControl::pairPcm(DeviceId device, std::optional<AudioEndpointId> endpoint)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(device);
    if (it == s.routes.end()) return;
    auto& t = s.targets.at(it->second);
    if (t.paired == endpoint) return;
    if (t.warmGate) t.warmGate->store(false);
    if (t.realtime)
        s.startStop(t, StopReason::EndpointLost, true);
    else if (t.pcm)
    {
        s.dropScheduled(t, StopReason::EndpointLost);
        revokePending(t, s.leases, Error::StaleTarget);
        s.startStop(t, StopReason::EndpointLost);
    }
    t.paired = endpoint;
    t.timing = {};
    t.pcmUnavailable = false;
}
Status HapticControl::setPcmModeTiming(TargetId id, const PcmModeTiming& timing)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published) return {ErrorInfo{Error::StaleTarget,{}}};
    auto& t = it->second;
    if (!t.paired) return {ErrorInfo{Error::Unsupported,{}}};
    if (timing.enterMs > 200 || timing.exitMs > 200 || bool(timing.enterMs) != bool(timing.exitMs))
        return {ErrorInfo{Error::InvalidArgument,{}}};
    if (t.owner != Owner::Idle || t.fence || !t.scheduled.empty()) return {ErrorInfo{Error::Busy,{}}};
    if (t.warmGate) t.warmGate->store(false);
    t.timing = timing;
    t.pcmUnavailable = false;
    return {};
}
std::weak_ptr<const void> HapticControl::lifetimeToken() const
{
    std::lock_guard lock(_state->mutex);
    return _state->lifetime;
}
Status HapticControl::setCalibration(TargetId id, const HapticCalibration& p)
{
    auto within = [](double x, double lo, double hi) { return x >= lo && x <= hi; };
    if (p.version != 1 || !within(p.gain,0,4) || !within(p.gamma,.5,2.5) ||
        !within(p.continuousGain,0,4) || !within(p.transientGain,0,4) || !within(p.leftGain,0,4) ||
        !within(p.rightGain,0,4) || !within(p.monoGain,0,4) || !within(p.textureBias,-1,1) ||
        !within(p.textureScale,0,4) || !within(p.peakCap,0,1) || !within(p.energyCap,0,1))
        return {ErrorInfo{Error::InvalidArgument,{}}};
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published) return {ErrorInfo{Error::StaleTarget,{}}};
    if (it->second.profile == p) return {};
    it->second.profile = p;
    s.refreshSettings(it->second);
    return {};
}
Status HapticControl::setOutputSettings(const OutputSettings& settings)
{
    if (!(settings.strength >= 0 && settings.strength <= 1)) return {ErrorInfo{Error::InvalidArgument,{}}};
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (s.settings.enabled == settings.enabled && s.settings.strength == settings.strength) return {};
    s.settings = settings;
    for (auto& [id,t] : s.targets) s.refreshSettings(t);
    return {};
}
Status HapticControl::preparePcm(TargetId id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    const auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published) return {ErrorInfo{Error::StaleTarget,{}}};
    auto& t = it->second;
    if (!s.enabled()) return {ErrorInfo{Error::Disabled,{}}};
    if (!s.active) return {ErrorInfo{Error::NotFocused,{}}};
    if (!t.paired || !t.timing.enterMs || t.pcmUnavailable) return {ErrorInfo{Error::Unsupported,{}}};
    if (t.owner != Owner::Idle || t.fence || !t.scheduled.empty() || (t.warm && !t.warmGate->load()))
        return {ErrorInfo{Error::Busy,{}}};
    if (!t.warm)
    {
        t.warmGate = std::make_shared<std::atomic_bool>(true);
        t.warm = audio::detail::prepareRealtimeHaptics(*t.paired, t.warmGate, s.wake);
    }
    t.warmUntil = clockUs() + 2 * Second;
    s.wake.notify_one();
    return {};
}
bool HapticControl::retiring(DeviceId device) const
{
    std::lock_guard lock(_state->mutex);
    auto it = _state->routes.find(device);
    return it != _state->routes.end() && !_state->targets.at(it->second).published;
}
void HapticControl::removeGamepad(DeviceId device, bool disconnected)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(device);
    if (it == s.routes.end())
        return;
    auto& t     = s.targets.at(it->second);
    t.published = false;
    s.dropScheduled(t, StopReason::EndpointLost);
    revokePending(t, s.leases, Error::StaleTarget);
    s.startStop(t, StopReason::EndpointLost);
    if (disconnected)
    {
        t.fence->needsNative  = false;
        t.fence->disconnected = true;
        s.routes.erase(it);
    }
}
std::vector<TargetInfo> HapticControl::enumerate() const
{
    std::lock_guard lock(_state->mutex);
    std::vector<TargetInfo> result;
    for (auto& [id, t] : _state->targets)
        if (t.published)
            result.push_back(t.info);
    return result;
}
Result<TargetId> HapticControl::target(std::optional<DeviceId> id) const
{
    std::lock_guard lock(_state->mutex);
    auto it = _state->routes.find(id);
    if (it == _state->routes.end() || !_state->targets.at(it->second).published)
        return fail<TargetId>(Error::Unsupported);
    return {it->second, {}};
}
Result<Capabilities> HapticControl::capabilities(TargetId id) const
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published)
        return fail<Capabilities>(Error::StaleTarget);
    auto& t = it->second;
    if (t.realtime && t.trace) State::copyAudioTrace(t);
    auto trace = t.trace;
    bool prepared = t.realtime && t.realtime->poll().prepared;
    bool preparing = false;
    if (t.warm && t.warmGate->load())
    {
        const auto warm = t.warm->poll();
        trace.emplace();
        trace->generation = warm.trace.generation;
        trace->peakQueuedFrames = warm.trace.peakQueuedFrames;
        prepared = warm.prepared;
        preparing = !prepared && !warm.finished;
    }
    return {
        Capabilities{
            t.owner,
            t.fault     ? Availability::RouteFault
            : !s.enabled() ? Availability::Disabled
            : !s.active ? Availability::NotFocused
            : t.fence   ? Availability::Stopping
                        : Availability::Available,
            t.interrupt,
            t.caps.platform,
            !t.mobile || t.caps.amplitude,
            t.caps.platform == MobilePlatform::Apple,
            t.caps.envelope,
            t.rawCapable,
            t.caps.envelope ? "Available" : t.caps.envelopeStatus,
            t.paired.has_value(), prepared, t.pcmLive, std::move(trace), preparing},
        {}};
}
HapticTime HapticControl::now() const
{
    std::lock_guard lock(_state->mutex);
    HapticTime t;
    t.us         = clockUs();
    t.generation = _state->generation;
    return t;
}
Result<HapticScope> HapticControl::scope(std::weak_ptr<HapticControl> control)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (s.closing || s.scopes.size() >= 512)
        return fail<HapticScope>(Error::QueueFull);
    auto id = nextIdentity++;
    s.scopes.emplace(id, ScopeCounts{});
    return {HapticScope(control, id), {}};
}

Result<PlaybackId> HapticControl::play(
    std::uint64_t scope, TargetId target, const HapticClip& clip, const PlayOptions& opt)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (!s.scopes.contains(scope))
        return fail<PlaybackId>(Error::NotFound);
    if (!s.enabled()) return fail<PlaybackId>(Error::Disabled);
    if (!s.active)
        return fail<PlaybackId>(Error::NotFocused);
    auto it = s.targets.find(target);
    if (it == s.targets.end() || !it->second.published)
        return fail<PlaybackId>(Error::StaleTarget);
    auto& t = it->second;
    if (t.fault)
        return fail<PlaybackId>(Error::Unavailable);
    if ((opt.requireAmplitude && t.mobile && !t.caps.amplitude) ||
        (opt.requireNativeScheduled && t.caps.platform != MobilePlatform::Apple))
        return fail<PlaybackId>(Error::Unsupported);
    if (s.compatPendingOrPlaying(t) || s.conflicts(t) || (t.restricted && *t.restricted != Owner::Preset))
        return fail<PlaybackId>(Error::Busy);
    auto now = clockUs();
    if (!std::isfinite(opt.startAfterMs) || opt.startAfterMs < 0 || opt.startAfterMs > 5000 ||
        (opt.startAt && (opt.startAfterMs != 0 || opt.startAt->generation != s.generation)) ||
        (opt.startPolicy != StartPolicy::Auto && opt.startPolicy != StartPolicy::FixedTimeline))
        return fail<PlaybackId>(Error::InvalidArgument);
    auto due       = opt.startAt ? opt.startAt->us : now + std::llround(opt.startAfterMs * 1000);
    bool immediate = !opt.startAt && opt.startAfterMs == 0 && opt.startPolicy == StartPolicy::Auto;
    Request request{
        opt.track,
        opt.priority,
        opt.gain,
        opt.pan,
        opt.iterations,
        scope,
        0,
        opt.mergeKey,
        immediate ? std::nullopt : std::optional<Time>{due}};
    Calibration calibration;
    calibration.pulseWidth = t.mobile ? 1000 : GridUs;
    HapticMixer validator(calibration);
    auto valid = validator.submitAt(clip, request, now, due);
    if (!valid.value)
        return {{}, valid.error};
    const bool resumingPreset = t.fence && t.fence->resumeOnMotors && t.fence->reason == StopReason::Reconfigured;
    if ((t.fence && !resumingPreset) || (due <= now && t.owner != Owner::Idle && t.owner != Owner::Preset))
        return fail<PlaybackId>(Error::Busy);
    if (t.scheduled.size() >= 32 || s.scopes.at(scope).play == UINT64_MAX)
        return fail<PlaybackId>(Error::QueueFull);
    auto& d  = ClipAccess::get(clip);
    Time end = d.renderEnd;
    if (!d.pulses.empty())
        end = std::max(end, d.pulses.back().at + calibration.pulseWidth);
    PlaybackId id;
    id.scope  = scope;
    id.serial = ++s.scopes.at(scope).play;
    t.scheduled.push_back({id, clip, std::move(request), now, due, end + (opt.iterations - 1) * d.duration, immediate});
    s.plays[id].requestedUs = now;
    if (t.original && due < t.expires && (due <= now || (t.write && t.write->receipt->load() < 0)))
    {
        t.reproject = true;
        s.startStop(t, StopReason::Reconfigured, true);
    }
    s.wake.notify_one();
    return {id, {}};
}
Status HapticControl::stop(std::uint64_t scope, PlaybackId id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (id.scope != scope || !s.scopes.contains(scope) || !id.serial || id.serial > s.scopes.at(scope).play)
        return {ErrorInfo{Error::NotFound, {}}};
    for (auto& [key, t] : s.targets)
    {
        bool affected = std::erase_if(t.scheduled, [&](auto& p) { return p.id == id; }) != 0;
        for (auto it = t.voices.begin(); it != t.voices.end(); ++it)
            if (it->second.id == id)
            {
                affected = true;
                t.mixer->stop(it->first);
                if (t.stableCheckpoint)
                    t.stableCheckpoint->stop(it->first);
                t.voices.erase(it);
                t.frame.reset();
                break;
            }
        if (affected && t.owner == Owner::Preset && t.voices.empty() && t.scheduled.empty())
            s.startStop(t, StopReason::Requested);
        else if (affected && t.original == id)
        {
            t.reproject = true;
            s.startStop(t, StopReason::Reconfigured, true);
        }
    }
    s.finish(id, PlaybackState::Stopped, StopReason::Requested);
    s.wake.notify_one();
    return {};
}
Result<PlaybackSnapshot> HapticControl::read(std::uint64_t scope, PlaybackId id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (scope != id.scope || !s.scopes.contains(scope) || !id.serial || id.serial > s.scopes.at(scope).play)
        return fail<PlaybackSnapshot>(Error::NotFound);
    auto it = s.plays.find(id);
    if (it == s.plays.end())
        return fail<PlaybackSnapshot>(Error::RecordGone);
    auto value = it->second;
    if (final(value.state))
    {
        s.plays.erase(it);
        std::erase(s.terminalOrder, RecordId{id});
    }
    return {value, {}};
}
Result<OperationSnapshot> HapticControl::read(std::uint64_t scope, OperationId id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (scope != id.scope || !s.scopes.contains(scope) || !id.serial || id.serial > s.scopes.at(scope).operation)
        return fail<OperationSnapshot>(Error::NotFound);
    auto it = s.operations.find(id);
    if (it == s.operations.end())
        return fail<OperationSnapshot>(Error::RecordGone);
    auto value = it->second;
    if (value.state != OperationState::Pending)
    {
        s.operations.erase(it);
        std::erase(s.terminalOrder, RecordId{id});
    }
    return {value, {}};
}
Result<OperationId> HapticControl::stopTarget(std::uint64_t scope, TargetId id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (!s.scopes.contains(scope))
        return fail<OperationId>(Error::NotFound);
    auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published)
        return fail<OperationId>(Error::StaleTarget);
    auto& t = it->second;
    if (t.owner == Owner::Idle && t.restricted)
        return fail<OperationId>(Error::Unsupported);
    if (t.fault)
        return fail<OperationId>(Error::Unavailable);
    if (t.fence && t.fence->operation)
        return fail<OperationId>(Error::Busy);
    OperationId op;
    op.scope  = scope;
    op.serial = ++s.scopes.at(scope).operation;
    s.operations.emplace(op, OperationSnapshot{});
    s.dropScheduled(t, StopReason::Requested);
    revokePending(t, s.leases, Error::Cancelled);
    s.startStop(t, StopReason::Requested);
    t.fence->operation = op;
    return {op, {}};
}
Result<RawSession> HapticControl::acquire(
    std::weak_ptr<HapticControl> control, std::uint64_t scope, TargetId id, AcquirePolicy policy)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (!s.scopes.contains(scope))
        return fail<RawSession>(Error::NotFound);
    if (!s.enabled()) return fail<RawSession>(Error::Disabled);
    if (!s.active)
        return fail<RawSession>(Error::NotFocused);
    auto it = s.targets.find(id);
    if (it == s.targets.end() || !it->second.published)
        return fail<RawSession>(Error::StaleTarget);
    auto& t = it->second;
    if (t.info.device || !t.rawCapable)
        return fail<RawSession>(Error::Unsupported);
    if (t.fault)
        return fail<RawSession>(Error::Unavailable);
    if ((t.owner == Owner::Idle && s.compatPendingOrPlaying(t)) || s.conflicts(t) ||
        (t.restricted && *t.restricted != Owner::Raw))
        return fail<RawSession>(Error::Busy);
    if (t.fence || (t.owner != Owner::Idle && (t.owner != Owner::Preset || policy != AcquirePolicy::InterruptPreset)))
        return fail<RawSession>(Error::Busy);
    if (t.owner == Owner::Preset && t.written && !t.interrupt)
        return fail<RawSession>(Error::Unsupported);
    auto raw = nextIdentity++;
    Handover next;
    next.mode = Owner::Raw;
    next.raw  = raw;
    s.leases.emplace(raw, RawRecord{scope, id, {RawState::Pending, {}}, clockUs()});
    if (t.owner == Owner::Idle)
        s.install(t, std::move(next), clockUs());
    else
    {
        t.successor = next;
        s.startStop(t, StopReason::Replaced);
    }
    s.wake.notify_one();
    return {RawSession(control, raw), {}};
}
RawSnapshot HapticControl::rawState(std::uint64_t id) const
{
    std::lock_guard lock(_state->mutex);
    auto it = _state->leases.find(id);
    return it == _state->leases.end() ? RawSnapshot{} : it->second.snap;
}
Result<OperationId> HapticControl::cancelRaw(std::uint64_t id, std::optional<RawPlayerId> player)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.leases.find(id);
    if (it == s.leases.end() || !s.scopes.contains(it->second.scope))
        return fail<OperationId>(Error::NotFound);
    auto& r = it->second;
    if (r.snap.state != RawState::Ready && r.snap.state != RawState::Pending)
        return fail<OperationId>(Error::NotFound);
    auto& t = s.targets.at(r.target);
    if (player && (!t.player || clockUs() >= t.expires || t.player != static_cast<std::uint64_t>(*player)))
        return fail<OperationId>(Error::NotFound);
    if (r.snap.state == RawState::Pending && t.owner == Owner::Raw && t.fence)
        return fail<OperationId>(Error::Busy);
    OperationId op;
    op.scope  = r.scope;
    op.serial = ++s.scopes.at(r.scope).operation;
    s.operations.emplace(op, OperationSnapshot{});
    if (r.snap.state == RawState::Pending)
    {
        t.successor.reset();
        r.snap = {RawState::Closed, Error::Cancelled};
    }
    else if (t.written)
    {
        s.startStop(t, StopReason::Requested);
        t.fence->operation = op;
        Handover next;
        next.mode   = Owner::Raw;
        next.raw    = id;
        t.successor = next;
        r.snap      = {RawState::Pending, {}};
        return {op, {}};
    }
    r.idleSince = clockUs();
    s.finishOp(op);
    return {op, {}};
}
Result<OperationId> HapticControl::stopPlayer(std::uint64_t lease, RawPlayerId player)
{
    // Validate and cancel under the same lock; a racing replacement cannot be stopped.
    return cancelRaw(lease, player);
}
Result<OperationId> HapticControl::rawCommand(std::uint64_t lease, MobileCommand cmd)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto record = s.leases.find(lease);
    if (record == s.leases.end() || !s.scopes.contains(record->second.scope))
        return fail<OperationId>(Error::NotFound);
    if (record->second.snap.state == RawState::Pending)
        return fail<OperationId>(Error::Busy);
    if (record->second.snap.state != RawState::Ready)
        return fail<OperationId>(Error::NotFound);
    auto& t = s.targets.at(record->second.target);
    if (!t.mobile)
        return fail<OperationId>(Error::Unsupported);
    auto valid = validateMobileEffect(cmd.raw, t.caps);
    if (!valid.value)
        return {{}, valid.error};
    const auto ceiling = s.nativeCeiling(t);
    if (!s.enabled()) return fail<OperationId>(Error::Disabled);
    if (ceiling < 1 && !limitMobileEffect(cmd.raw, t.caps, ceiling))
        return fail<OperationId>(Error::Unsupported);
    if (t.fence || t.write || !s.active || t.raw != lease)
        return fail<OperationId>(Error::Busy);
    auto now    = clockUs();
    bool update = cmd.kind == MobileCommand::Kind::Parameters || cmd.kind == MobileCommand::Kind::Curve;
    if (update)
    {
        if (!cmd.player || t.player != cmd.player || now >= t.expires)
            return fail<OperationId>(Error::NotFound);
        if (*valid.value > t.expires - t.playerOrigin)
            return fail<OperationId>(Error::InvalidArgument);
        cmd.startUs = t.playerOrigin;
        cmd.endUs   = t.expires;
    }
    else
    {
        if (t.player && now < t.expires && !cmd.replace)
            return fail<OperationId>(Error::Busy);
        cmd.startUs = now;
        cmd.endUs   = now + *valid.value;
    }
    const auto player  = cmd.player;
    const auto expires = cmd.endUs;
    auto [receipt, e]  = s.mobileWrite(t, std::move(cmd));
    if (e != NativeError::None)
        return fail<OperationId>(e == NativeError::QueueFull ? Error::QueueFull : Error::BackendFailure);
    if (!update)
    {
        t.expires      = expires;
        t.player       = player;
        t.playerOrigin = now;
    }
    t.written                = true;
    record->second.idleSince = now;
    OperationId op;
    op.scope  = record->second.scope;
    op.serial = ++s.scopes.at(op.scope).operation;
    s.operations.emplace(op, OperationSnapshot{});
    t.write = Write{
        receipt,
        now,
        [&s, op](NativeError result) {
            std::optional<Error> error;
            switch (result)
            {
            case NativeError::None:
                break;
            case NativeError::Unsupported:
                error = Error::Unsupported;
                break;
            case NativeError::InvalidArgument:
                error = Error::InvalidArgument;
                break;
            case NativeError::QueueFull:
                error = Error::QueueFull;
                break;
            case NativeError::Busy:
                error = Error::Busy;
                break;
            case NativeError::PermissionDenied:
                error = Error::PermissionDenied;
                break;
            default:
                error = Error::BackendFailure;
                break;
            }
            s.finishOp(op, error);
        },
        {}};
    t.write->rawSpan = update ? 0 : *valid.value;
    s.wake.notify_one();
    return {op, {}};
}
void HapticControl::closeRaw(std::uint64_t id)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.leases.find(id);
    if (it == s.leases.end())
        return;
    auto target = s.targets.find(it->second.target);
    if (target != s.targets.end())
    {
        auto& t = target->second;
        if (t.successor && t.successor->raw == id)
            t.successor.reset();
        if (t.raw == id)
            s.startStop(t, StopReason::Requested);
    }
    s.leases.erase(it);
}
void HapticControl::close(std::uint64_t scope)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (!s.scopes.erase(scope))
        return;
    for (auto& [id, t] : s.targets)
    {
        std::erase_if(t.scheduled, [&](auto& p) { return p.id.scope == scope; });
        std::erase_if(t.voices, [&](auto& p) {
            if (p.second.id.scope != scope)
                return false;
            t.mixer->stop(p.first);
            if (t.stableCheckpoint)
                t.stableCheckpoint->stop(p.first);
            t.frame.reset();
            return true;
        });
        if (t.successor && t.successor->raw && s.leases.at(t.successor->raw).scope == scope)
            t.successor.reset();
        if ((t.raw && s.leases.contains(t.raw) && s.leases.at(t.raw).scope == scope) ||
            (t.owner == Owner::Preset && t.voices.empty() && t.scheduled.empty()))
            s.startStop(t, StopReason::Requested);
        else if (t.original && t.original->scope == scope)
        {
            t.reproject = true;
            s.startStop(t, StopReason::Reconfigured, true);
        }
    }
    std::erase_if(s.leases, [&](auto& p) { return p.second.scope == scope; });
    std::erase_if(s.plays, [&](auto& p) { return p.first.scope == scope; });
    std::erase_if(s.operations, [&](auto& p) { return p.first.scope == scope; });
    std::erase_if(s.terminalOrder, [&](auto& p) { return std::visit([&](auto id) { return id.scope == scope; }, p); });
    s.wake.notify_one();
}

NativeError HapticControl::legacy(DeviceId id, const input::OutputCommand& cmd, bool zero, Done done)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(id);
    if (it == s.routes.end())
        return NativeError::Unsupported;
    auto& t = s.targets.at(it->second);
    if ((!s.enabled() && !std::holds_alternative<Stop>(cmd)) || !s.active)
        return NativeError::Busy;
    if (!std::holds_alternative<Stop>(cmd) &&
        (s.conflicts(t) || (t.restricted && *t.restricted != Owner::LegacyRumble) ||
         (t.mobile && !t.interrupt && t.written && t.owner != Owner::LegacyRumble)))
        return NativeError::Busy;
    if (std::holds_alternative<Stop>(cmd))
    {
        if (zero && t.owner != Owner::LegacyPcm && t.owner != Owner::LegacyRumble)
        {
            done(NativeError::None);
            return NativeError::None;
        }
        if (t.fault)
            return NativeError::BackendFailure;
        if (t.fence && (t.fence->done || zero))
        {
            if (zero)
            {
                done(NativeError::None);
                return NativeError::None;
            }
            return NativeError::Busy;
        }
        if (!zero)
        {
            s.dropScheduled(t, StopReason::Requested);
            revokePending(t, s.leases, Error::Cancelled);
        }
        s.startStop(t, StopReason::Requested);
        t.fence->done = std::move(done);
        return NativeError::None;
    }
    Handover next;
    next.mode   = Owner::LegacyRumble;
    next.rumble = std::get<Rumble>(cmd);
    next.done   = std::move(done);
    if (t.fault)
        return NativeError::Busy;
    if (t.fence)
    {
        if (t.owner != Owner::LegacyRumble || t.fence->reason != StopReason::None || t.successor)
            return NativeError::Busy;
        t.successor = std::move(next);
        s.wake.notify_one();
        return NativeError::None;
    }
    if (t.owner == Owner::LegacyRumble)
    {
        auto gate         = std::make_shared<std::atomic_bool>(true);
        auto now          = clockUs();
        auto deadline     = now + next.rumble.duration.count() * 1000;
        auto oldGate      = t.gate;
        t.gate            = gate;
        auto [receipt, e] = s.motorWrite(t, next.rumble, deadline);
        t.gate            = oldGate;
        if (e != NativeError::None)
            return e;
        if (t.write && t.write->done)
            t.write->done(NativeError::Busy);
        t.gate->store(false);
        t.gate    = std::move(gate);
        t.expires = deadline;
        t.written = true;
        t.write   = Write{receipt, now, std::move(next.done), {}};
    }
    else if (t.owner == Owner::Idle)
        s.install(t, std::move(next), clockUs());
    else
    {
        t.successor = std::move(next);
        s.startStop(t, StopReason::Replaced);
    }
    s.wake.notify_one();
    return NativeError::None;
}
NativeError HapticControl::playPcm(DeviceId id, std::shared_ptr<PcmSource> pcm)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(id);
    if (it == s.routes.end())
        return NativeError::Unsupported;
    auto& t = s.targets.at(it->second);
    if (s.active && !t.fault && t.successor && t.successor->pcm == pcm)
        return NativeError::None;
    if (!s.enabled() || !s.active || t.fence || t.fault)
        return NativeError::Busy;
    if (t.pcm == pcm)
        return NativeError::None;
    Handover next;
    next.mode = Owner::LegacyPcm;
    next.pcm  = std::move(pcm);
    if (t.owner == Owner::Idle)
        s.install(t, std::move(next), clockUs());
    else
    {
        t.successor = std::move(next);
        s.startStop(t, StopReason::Replaced);
    }
    s.wake.notify_one();
    return NativeError::None;
}
bool HapticControl::ownsPcm(DeviceId device, const std::shared_ptr<PcmSource>& pcm) const
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    auto it = s.routes.find(device);
    if (it == s.routes.end())
        return false;
    auto& t = s.targets.at(it->second);
    return pcm && !t.fence && t.pcm == pcm;
}
NativeError HapticControl::stopPcm(DeviceId device, const std::shared_ptr<PcmSource>& pcm, StopReason reason)
{
    auto& s = *_state;
    std::unique_lock lock(s.mutex);
    auto it = s.routes.find(device);
    if (!pcm)
        return NativeError::InvalidArgument;
    if (it == s.routes.end())
    {
        lock.unlock();
        return pcm->silence(reason);
    }
    const auto id = it->second;
    auto& t       = s.targets.at(it->second);
    if (t.successor && t.successor->pcm == pcm)
        t.successor.reset();
    if (t.pcm != pcm)
    {
        lock.unlock();
        return pcm->silence(reason);
    }
    s.startStop(t, reason);
    auto done = [&] {
        const auto p = s.targets.find(id);
        return s.closing || p == s.targets.end() || p->second.pcm != pcm ||
               (p->second.fence && (p->second.fence->audioStopped || p->second.fence->audioFault));
    };
    if (!s.changed.wait_for(lock, std::chrono::microseconds(StopUs), done))
        return NativeError::BackendFailure;
    auto p = s.targets.find(id);
    if (p != s.targets.end() && p->second.pcm == pcm && p->second.fence && p->second.fence->audioFault)
        return NativeError::BackendFailure;
    return NativeError::None;
}
}  // namespace cc::haptics::detail
