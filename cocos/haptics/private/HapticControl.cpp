#include "HapticControl.h"
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
    StopReason reason{};
    std::optional<OperationId> operation;
    Done done;
};
struct Target
{
    TargetInfo info;
    Endpoint route{};
    bool rawCapable = false, interrupt = true, published = true;
    Owner owner = Owner::Idle;
    Gate gate   = std::make_shared<std::atomic_bool>(true);
    Endpoint writer{};
    bool written = false, fault = false;
    std::optional<Fence> fence;
    std::optional<Handover> successor;
    std::optional<Write> write;
    std::optional<MotorFrame> frame;
    std::unique_ptr<HapticMixer> mixer;
    std::vector<Scheduled> scheduled;
    std::map<Id, VoiceRecord> voices;
    std::vector<Terminal> ends;
    Time nextGrid{}, lastWrite{}, expires{};
    Channels last{};
    std::shared_ptr<PcmSource> pcm;
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
                if (!it->second.firstSubmitUs)
                    it->second.firstSubmitUs = write.at;
            }
    }
    void startStop(Target& t, StopReason why)
    {
        if (t.fence)
            return;
        t.gate->store(false);
        if (t.write && t.write->receipt->load() == int(NativeError::None))
            recordSubmission(*t.write);
        for (auto& [key, v] : t.voices)
            finish(v.id, why == StopReason::Replaced ? PlaybackState::Preempted : PlaybackState::Stopped, why);
        t.voices.clear();
        t.ends.clear();
        t.mixer.reset();
        t.frame.reset();
        if (t.write && t.write->done)
        {
            auto rc = t.write->receipt->load();
            t.write->done(rc < 0 ? NativeError::Busy : static_cast<NativeError>(rc));
        }
        t.write.reset();
        if (t.raw && leases.contains(t.raw))
            leases.at(t.raw).snap = {RawState::Closed, {}, why};
        Fence f;
        f.endpoint    = t.writer;
        f.deadline    = clockUs() + StopUs;
        f.needsNative = t.written;
        f.reason      = why;
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
    void install(Target& t, Handover next, Time now)
    {
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
                t.writer = t.pcm->hid;
            else
                t.expires = now + next.rumble.duration.count() * 1000;
            auto [receipt, e] = send(
                t.writer,
                pcm ? input::OutputCommand{Stop{Channel::Body}} : input::OutputCommand{next.rumble},
                t.gate,
                t.expires,
                pcm);
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
        if (f.needsNative)
        {
            if (!f.receipt)
            {
                if (f.retry > now || f.attempts >= 3)
                    return;
                auto [r, e] = send(f.endpoint, Stop{Channel::Body}, f.gate);
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
                if (value != int(NativeError::None) && value != int(NativeError::Disconnected))
                {
                    f.receipt.reset();
                    ++f.attempts;
                    f.retry = now + 20000;
                    return;
                }
            }
        }
        f.gate->store(false);
        finishOp(f.operation);
        if (f.done)
            f.done(NativeError::None);
        t.fence.reset();
        t.pcm.reset();
        t.raw     = 0;
        t.owner   = Owner::Idle;
        t.fault   = false;
        t.written = false;
        if (t.successor)
        {
            auto next = std::move(*t.successor);
            t.successor.reset();
            if (active && t.published)
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
                work |= t.owner != Owner::Idle || t.fence.has_value() || !t.scheduled.empty();
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
    if (t.nextGrid > now || t.frame)
        return;
    if (!t.mixer)
    {
        Calibration c;
        c.layout     = t.info.device ? Layout::LowHigh : Layout::Mono;
        c.pulseWidth = GridUs;
        t.mixer      = std::make_unique<HapticMixer>(c);
    }
    Time begin = t.nextGrid ? t.nextGrid : now;
    if (now - begin > 8000)
        begin = now;
    for (auto& s : t.scheduled)
        if (s.due <= now && !s.immediate && !t.nextGrid)
            begin = std::min(begin, std::max(now - 8000, s.due));
    t.mixer->skipTo(begin);
    for (auto it = t.scheduled.begin(); it != t.scheduled.end();)
    {
        if (it->due > now)
        {
            ++it;
            continue;
        }
        auto logical  = it->immediate ? std::max(it->received, begin) : it->due;
        auto accepted = t.mixer->submitAt(it->clip, it->options, it->received, logical);
        if (accepted.value)
        {
            auto& snap          = plays.at(it->id);
            snap.logicalStartUs = logical;
            snap.state          = PlaybackState::Active;
            t.voices.emplace(*accepted.value, VoiceRecord{it->id, logical + it->span});
        }
        else
            finish(it->id, PlaybackState::Failed, {}, accepted.error->code);
        it = t.scheduled.erase(it);
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

void HapticControl::State::runTarget(Target& t, Time now)
{
    if (t.fence)
        fenceStep(t, now);
    bool due = std::any_of(t.scheduled.begin(), t.scheduled.end(), [&](auto& s) { return s.due <= now; });
    if (due && (t.fence || (t.owner != Owner::Idle && t.owner != Owner::Preset)))
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
            if (w.done)
                w.done(error);
            if (error != NativeError::None || now - w.at > 500000)
            {
                stopAfterWriteError(t, error, error == NativeError::None ? Error::TimedOut : Error::BackendFailure);
                return;
            }
            recordSubmission(w);
            if (t.owner == Owner::LegacyPcm && t.pcm)
            {
                t.enabling = true;
                t.audioJob = std::async(std::launch::async, [pcm = t.pcm, gate = t.gate] {
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
    if (due && t.owner == Owner::Idle)
    {
        install(t, Handover{Owner::Preset}, now);
        t.nextGrid = 0;
    }
    if (t.owner != Owner::Preset)
        return;
    if (!t.write)
        retire(t, now);
    if (t.frame && t.nextGrid + 8000 <= now)
        t.frame.reset();
    render(t, now);
    if (t.frame && t.frame->due <= now && !t.write)
    {
        auto frame = std::move(*t.frame);
        t.frame.reset();
        bool nonzero = frame.levels[0] > 0 || frame.levels[1] > 0;
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
            t.gate->store(false);
            if (t.fence)
                t.fence->gate->store(false);
        }
        s.closing = true;
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
    }
}
void HapticControl::resetScopes()
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    s.scopes.clear();
    s.plays.clear();
    s.operations.clear();
    s.terminalOrder.clear();
    s.leases.clear();
    s.generation = nextIdentity++;
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
    if (s.active == active)
        return;
    s.active = active;
    if (!active)
        for (auto& [id, t] : s.targets)
        {
            s.dropScheduled(t, StopReason::FocusLost);
            revokePending(t, s.leases, Error::NotFocused);
            if (t.owner != Owner::Idle)
                s.startStop(t, StopReason::FocusLost);
        }
    s.wake.notify_one();
}
void HapticControl::publishGamepad(DeviceId device, Endpoint key)
{
    std::lock_guard lock(_state->mutex);
    _state->publish(device, key, true, false);
}
void HapticControl::publishHandset(Endpoint key, bool interrupt, bool release)
{
    std::lock_guard lock(_state->mutex);
    _state->publish({}, key, interrupt, release);
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
    return {
        Capabilities{
            t.owner,
            t.fault     ? Availability::RouteFault
            : !s.active ? Availability::NotFocused
            : t.fence   ? Availability::Stopping
                        : Availability::Available,
            t.interrupt,
            t.rawCapable},
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
    if (!s.active)
        return fail<PlaybackId>(Error::NotFocused);
    auto it = s.targets.find(target);
    if (it == s.targets.end() || !it->second.published)
        return fail<PlaybackId>(Error::StaleTarget);
    auto& t = it->second;
    if (t.fault)
        return fail<PlaybackId>(Error::Unavailable);
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
    calibration.pulseWidth = GridUs;
    HapticMixer validator(calibration);
    auto valid = validator.submitAt(clip, request, now, due);
    if (!valid.value)
        return {{}, valid.error};
    if (t.fence || (due <= now && t.owner != Owner::Idle && t.owner != Owner::Preset))
        return fail<PlaybackId>(Error::Busy);
    if (t.scheduled.size() >= 32 || s.scopes.at(scope).play == UINT64_MAX)
        return fail<PlaybackId>(Error::QueueFull);
    auto& d  = ClipAccess::get(clip);
    Time end = d.renderEnd;
    if (!d.pulses.empty())
        end = std::max(end, d.pulses.back().at + GridUs);
    PlaybackId id;
    id.scope  = scope;
    id.serial = ++s.scopes.at(scope).play;
    t.scheduled.push_back({id, clip, std::move(request), now, due, end + (opt.iterations - 1) * d.duration, immediate});
    s.plays[id].requestedUs = now;
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
                t.voices.erase(it);
                t.frame.reset();
                break;
            }
        if (affected && t.owner == Owner::Preset && t.voices.empty() && t.scheduled.empty())
            s.startStop(t, StopReason::Requested);
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
Result<OperationId> HapticControl::cancelRaw(std::uint64_t id)
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
Result<OperationId> HapticControl::submitRaw(const RawSession& session, const Rumble& r)
{
    auto& s = *_state;
    std::lock_guard lock(s.mutex);
    if (session._control.lock().get() != this || !s.leases.contains(session._id))
        return fail<OperationId>(Error::NotFound);
    auto& lease = s.leases.at(session._id);
    if (lease.snap.state == RawState::Pending)
        return fail<OperationId>(Error::Busy);
    if (lease.snap.state != RawState::Ready || !s.targets.contains(lease.target))
        return fail<OperationId>(Error::NotFound);
    auto& t = s.targets.at(lease.target);
    if (!s.active || t.raw != session._id || t.fence || t.write)
        return fail<OperationId>(Error::Busy);
    if (!(r.low >= 0 && r.low <= 1 && r.high >= 0 && r.high <= 1) || (r.low == 0 && r.high == 0) ||
        r.duration.count() <= 0 || r.duration.count() > 1000)
        return fail<OperationId>(Error::InvalidArgument);
    auto now              = clockUs();
    auto deadline         = now + r.duration.count() * 1000;
    auto [receipt, error] = s.send(t.writer, r, t.gate, deadline);
    if (error != NativeError::None)
        return fail<OperationId>(error == NativeError::QueueFull ? Error::QueueFull : Error::BackendFailure);
    OperationId op;
    op.scope  = lease.scope;
    op.serial = ++s.scopes.at(lease.scope).operation;
    s.operations.emplace(op, OperationSnapshot{});
    t.written = true;
    t.expires = deadline;
    t.write   = Write{
        receipt,
        now,
        [&s, op](NativeError e) {
            s.finishOp(op, e == NativeError::None ? std::nullopt : std::optional{Error::Cancelled});
        },
        {}};
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
            t.frame.reset();
            return true;
        });
        if (t.successor && t.successor->raw && s.leases.at(t.successor->raw).scope == scope)
            t.successor.reset();
        if ((t.raw && s.leases.contains(t.raw) && s.leases.at(t.raw).scope == scope) ||
            (t.owner == Owner::Preset && t.voices.empty() && t.scheduled.empty()))
            s.startStop(t, StopReason::Requested);
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
    if (!s.active)
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
        auto [receipt, e] = s.send(t.writer, next.rumble, gate, deadline);
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
    if (!s.active || t.fence || t.fault)
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
