#include "haptics/private/HapticMixer.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <tuple>
#include "rapidjson/encodings.h"
#include "rapidjson/memorystream.h"

namespace cc::haptics::detail
{
namespace
{
constexpr Time Never             = std::numeric_limits<Time>::max();
constexpr unsigned ResourceLimit = 32;
constexpr Time Window            = 8000;
constexpr Time FadeTime          = 3000;
constexpr Time Grid              = 1000;
constexpr double BurstShare      = .81;
double power(Channels a)
{
    return a[0] * a[0] + a[1] * a[1];
}
bool within(double x, double a, double b)
{
    return x >= a && x <= b;
}
bool validKey(std::string_view s)
{
    if (s.size() > 64)
        return false;
    rapidjson::MemoryStream stream(s.data(), s.size());
    while (stream.Tell() < s.size())
    {
        unsigned cp{};
        if (!rapidjson::UTF8<>::Decode(stream, &cp) || cp == 0)
            return false;
    }
    return true;
}

struct Voice
{
    HapticClip handle;
    Request request;
    Id id;
    Time received, start, end;
    unsigned priority;
    const ClipData& data() const { return ClipAccess::get(handle); }
    Channels last{};
    double lastTexture{};
};
bool higher(const Voice& a, const Voice& b)
{
    if (a.request.track != b.request.track)
        return a.request.track == Track::Burst;
    if (a.priority != b.priority)
        return a.priority > b.priority;
    return std::tie(a.start, a.id) < std::tie(b.start, b.id);
}
bool canMerge(const Voice& v, const Voice& incoming)
{
    auto& a = v.request;
    auto& b = incoming.request;
    if (v.end <= incoming.received || &v.data() != &incoming.data() || a.mergeKey.empty())
        return false;
    // A pulse that has already fired may still occupy power. It has no mutable gain.
    Time finalOrigin   = v.start + (a.iterations - 1) * v.data().duration;
    const auto& pulses = v.data().pulses;
    bool mutablePulse  = !pulses.empty() && finalOrigin + pulses.back().at >= incoming.received;
    bool mutableBed    = std::any_of(v.data().layers.begin(), v.data().layers.end(), [&](auto& layer) {
        return finalOrigin + layer.tail > incoming.received;
    });
    return (mutablePulse || mutableBed) && a.mergeKey == b.mergeKey && a.scope == b.scope && a.track == b.track &&
           a.pan == b.pan && a.iterations == b.iterations && v.priority == incoming.priority && a.route == b.route &&
           a.startAt == b.startAt && (a.startAt || incoming.received - v.received <= 24000);
}
Channels project(const Calibration& c, Sample sample, const Request& r, bool pulse)
{
    auto input       = std::clamp(sample.amplitude * r.gain, 0., 1.);
    double amplitude = std::pow(input * c.gain * (pulse ? c.transientGain : c.continuousGain), c.gamma);
    double balance   = 0;
    if (c.layout == Layout::LeftRight)
        balance = (r.pan + 1) * .5;
    if (c.layout == Layout::LowHigh)
    {
        double u = std::clamp((sample.texture - .25) * 2, 0., 1.);
        balance  = u * u * (3 - 2 * u);
    }
    return {amplitude * std::sqrt(1 - balance) * c.channelGain[0], amplitude * std::sqrt(balance) * c.channelGain[1]};
}

struct Budget
{
    Channels channels;
    double total;
    void debit(Channels p)
    {
        for (int k = 0; k < 2; ++k)
            channels[k] = std::max(0., channels[k] - p[k]);
        total = std::max(0., total - p[0] - p[1]);
    }
    double fraction(Channels demand) const
    {
        double ratio = 1, sum = demand[0] + demand[1];
        if (sum > 0)
            ratio = std::min(ratio, total / sum);
        for (int k = 0; k < 2; ++k)
            if (demand[k] > 0)
                ratio = std::min(ratio, channels[k] / demand[k]);
        return ratio;
    }
};
struct Batch
{
    std::vector<Entry> pulses, layers;
    void allocate(std::vector<Entry>& list, Budget& remaining, Budget* burst, double gain)
    {
        Channels demand{};
        for (auto& e : list)
            for (int k = 0; k < 2; ++k)
                demand[k] += std::pow(e.amplitude[k] * gain, 2);
        double f = remaining.fraction(demand);
        if (burst)
            f = std::min(f, burst->fraction(demand));
        double scale = std::sqrt(f) * gain;
        for (auto& e : list)
        {
            if (scale == 0 && power(e.amplitude) > 0 && e.reason == Reason::None)
                e.reason = Reason::Budget;
            for (double& a : e.amplitude)
                a *= scale;
        }
        Channels used{f * demand[0], f * demand[1]};
        remaining.debit(used);
        if (burst)
            burst->debit(used);
    }
};
struct Candidate
{
    Key key;
    Time at;
    Track track;
    unsigned priority, mask;
    double energy;
};
bool preferred(const Candidate& a, const Candidate& b)
{
    if (a.track != b.track)
        return a.track == Track::Burst;
    if (a.priority != b.priority)
        return a.priority > b.priority;
    if (a.energy != b.energy)
        return a.energy > b.energy;
    return std::tie(a.key.playback, a.key.ordinal, a.key.iteration) <
           std::tie(b.key.playback, b.key.ordinal, b.key.iteration);
}
unsigned maskOf(Channels level)
{
    return (level[0] > 0 ? 1u : 0u) | (level[1] > 0 ? 2u : 0u);
}
unsigned eventMask(Layout layout, Channels level)
{
    // Slow/fast rumble channels express texture on a single target, not independent locations.
    return layout == Layout::LeftRight ? maskOf(level) : unsigned(power(level) > 0);
}
struct EventWindow
{
    Time end = -1;
    unsigned lockedMask{};
    bool dirty = true;
    std::vector<Candidate> ranked, winners;
};
struct Fade
{
    Id id, incoming;
    Track track;
    Time start;
    Channels amplitude;
    double texture;
};
struct HeldPulse
{
    Time end;
    Track track;
    Channels amplitude;
    Key key;
};

// Visit just the iterations whose pulse range intersects [begin,end). The source
// vector is ordered and shared by every iteration.
template <class Fn>
void visitPulses(const Voice& v, Time begin, Time end, Fn visit)
{
    const auto& d = v.data();
    if (d.pulses.empty() || end <= v.start || begin >= v.end)
        return;
    Time length    = d.duration;
    unsigned first = 0;
    if (length && begin > v.start + d.pulses.back().at)
        first = unsigned((begin - v.start - d.pulses.back().at + length - 1) / length);
    for (unsigned i = first; i < v.request.iterations; ++i)
    {
        Time origin = v.start + i * length;
        if (origin + d.pulses.front().at >= end)
            break;
        auto it = std::lower_bound(
            d.pulses.begin(), d.pulses.end(), begin - origin, [](auto& p, Time t) { return p.at < t; });
        for (; it != d.pulses.end() && origin + it->at < end; ++it)
            visit(*it, i, origin + it->at);
    }
}
}  // namespace
struct HapticMixer::State
{
    Calibration calibration;
    Time clock{}, next = Never, lastSample{};
    double duck{}, duckTarget{};
    Id sequence{};
    std::vector<Voice> active, pending;
    std::vector<Fade> fades;
    std::vector<HeldPulse> held;
    std::vector<Reservation> reservations;
    std::vector<Terminal> terminals;
    EventWindow window;

    void change()
    {
        next         = std::min(next, clock);
        window.dirty = true;
    }
    void admit(Time at)
    {
        std::erase_if(active, [&](const Voice& v) {
            if (v.end > at)
                return false;
            terminals.push_back({v.id, Outcome::Ended, v.end});
            window.dirty = true;
            return true;
        });
        auto due = pending.begin();
        for (; due != pending.end() && due->start <= at; ++due)
        {
            if (due->end <= at) {
                terminals.push_back({due->id, Outcome::Ended, due->end});
                continue;
            }
            auto track     = due->request.track;
            unsigned count = 0;
            auto victim    = active.end();
            for (auto it = active.begin(); it != active.end(); ++it)
                if (it->request.track == track)
                {
                    ++count;
                    if (victim == active.end() || higher(*victim, *it))
                        victim = it;
                }
            if (count == (track == Track::Burst ? 3u : 8u))
            {
                if (due->priority <= victim->priority)
                {
                    terminals.push_back({due->id, Outcome::Dropped, at});
                    continue;
                }
                terminals.push_back({victim->id, Outcome::Preempted, at});
                std::erase_if(fades, [&](auto& f) { return f.track == track; });
                if (power(victim->last) > 0)
                    fades.push_back({victim->id, due->id, track, at, victim->last, victim->lastTexture});
                active.erase(victim);
            }
            active.push_back(std::move(*due));
            window.dirty = true;
        }
        pending.erase(pending.begin(), due);
        std::sort(active.begin(), active.end(), higher);
    }
    void rank(Time at)
    {
        if (window.end <= at)
        {
            bool any = false;
            for (auto& v : active)
                visitPulses(v, at, at + 1, [&](auto&, unsigned, Time) { any = true; });
            if (!any)
                return;
            window     = EventWindow{};
            window.end = at + Window;
        }
        if (!window.dirty)
            return;
        window.ranked.clear();
        window.winners.clear();
        for (const auto& v : active)
            visitPulses(v, at, window.end, [&](const Pulse& p, unsigned i, Time t) {
                auto level = project(calibration, v.data().sample(p), v.request, true);
                Candidate cand{{v.id, i, p.ordinal}, t, v.request.track, v.priority,
                               eventMask(calibration.layout, level), power(level)};
                auto pos = std::lower_bound(window.ranked.begin(), window.ranked.end(), cand, preferred);
                if (pos != window.ranked.end() || window.ranked.size() < ResourceLimit)
                {
                    window.ranked.insert(pos, cand);
                    if (window.ranked.size() > ResourceLimit)
                        window.ranked.pop_back();
                }
            });
        unsigned mask = window.lockedMask;
        // Native pulses may have been submitted ahead of the sampling cursor.
        for (const auto& r : reservations)
            if (r.sourceIsPulse && r.source && r.begin >= window.end - Window && r.begin < window.end)
                mask |= eventMask(calibration.layout, r.amplitude);
        for (auto& cand : window.ranked)
            if (cand.mask && !(cand.mask & mask))
            {
                window.winners.push_back(cand);
                mask |= cand.mask;
            }
        window.dirty = false;
    }
    void plan(Time at, const std::function<void(const Entry&)>& sink);
    Time nextBoundary(Time at) const;
};

Time HapticMixer::State::nextBoundary(Time at) const
{
    Time nextAt = pending.empty() ? Never : pending.front().start;
    if (!active.empty() || !fades.empty() || !held.empty() || !reservations.empty())
        nextAt = std::min(nextAt, at > Never - Grid ? Never : (at / Grid + 1) * Grid);
    for (auto& r : reservations)
    {
        if (r.begin > at)
            nextAt = std::min(nextAt, r.begin);
        nextAt = std::min(nextAt, r.end);
    }
    for (auto& p : held)
        nextAt = std::min(nextAt, p.end);
    for (auto& f : fades)
        nextAt = std::min(nextAt, f.start + FadeTime);
    for (auto& v : active)
    {
        auto length = v.data().duration;
        nextAt      = std::min(nextAt, v.end);
        // Most assets finish within one iteration. Locate their next knot in logarithmic time.
        auto& knots = v.data().boundaries;
        if (length && !knots.empty() && knots.back() <= length)
        {
            Time local     = at - v.start;
            auto iteration = local / length;
            if (iteration < v.request.iterations)
            {
                auto it = std::upper_bound(knots.begin(), knots.end(), local % length);
                if (it != knots.end())
                    nextAt = std::min(nextAt, v.start + iteration * length + *it);
                if (iteration + 1 < v.request.iterations)
                    nextAt = std::min(nextAt, v.start + (iteration + 1) * length + knots.front());
            }
            continue;
        }
        // Release tails can cross several iterations. Jump directly in each offset series.
        for (auto offset : v.data().boundaries)
        {
            Time base = v.start + offset;
            Time i    = 0;
            if (at >= base)
            {
                if (!length)
                    continue;
                i = (at - base) / length + 1;
            }
            if (i < v.request.iterations)
                nextAt = std::min(nextAt, base + i * length);
        }
    }
    return nextAt;
}

void HapticMixer::State::plan(Time at, const std::function<void(const Entry&)>& sink)
{
    admit(at);
    std::erase_if(held, [&](auto& p) { return p.end <= at; });
    std::erase_if(fades, [&](auto& f) { return f.start + FadeTime <= at; });
    std::erase_if(reservations, [&](auto& r) { return r.end <= at; });
    const auto& c = calibration;
    Budget remaining{
        {std::pow(c.cap[0] * c.strength, 2), std::pow(c.cap[1] * c.strength, 2)}, std::pow(c.totalCap * c.strength, 2)};
    const double total = remaining.total;
    Budget burst{{BurstShare * remaining.channels[0], BurstShare * remaining.channels[1]}, BurstShare * total};
    unsigned blocked   = 0;
    double lockedBurst = 0;
    auto lock          = [&](Track track, Channels a) {
        Channels p{a[0] * a[0], a[1] * a[1]};
        remaining.debit(p);
        if (track == Track::Burst)
        {
            burst.debit(p);
            lockedBurst += p[0] + p[1];
        }
    };
    auto maskFor = [&](const Reservation& r) {
        return r.channelMask ? r.channelMask : (c.layout == Layout::Mono ? 1u : 3u);
    };
    auto unreserved = [&](Channels level, Key key, bool pulse) {
        for (const auto& r : reservations)
            if (at >= r.begin && r.sourceIsPulse == pulse && r.source == key)
            {
                for (int k = 0; k < 2; ++k)
                    if (maskFor(r) & (1u << k))
                        level[k] = 0;
            }
        return level;
    };
    for (auto& p : held)
        lock(p.track, unreserved(p.amplitude, p.key, true));
    for (auto& r : reservations)
        if (at >= r.begin)
        {
            lock(r.track, r.amplitude);
            if (!r.canOverlay)
                blocked |= maskFor(r);
        }
    rank(at);
    // A Burst batch belongs to one voice. Normal layers share proportional allocation.
    std::vector<Batch> bursts;
    Batch normal;
    unsigned layers = 0;
    auto constrain  = [&](Entry& e) {
        auto initial = power(e.amplitude);
        for (int k = 0; k < 2; ++k)
            if (blocked & (1u << k))
                e.amplitude[k] = 0;
        if (initial > 0 && !power(e.amplitude))
            e.reason = Reason::Locked;
    };
    for (auto& v : active)
    {
        const auto& d = v.data();
        auto track    = v.request.track;
        auto& batch   = track == Track::Burst ? bursts.emplace_back() : normal;
        v.last        = {};
        v.lastTexture = 0;
        double fadeIn = 1;
        for (auto& fade : fades)
            if (fade.incoming == v.id)
                fadeIn = double(at - fade.start) / FadeTime;
        visitPulses(v, at, at + 1, [&](const Pulse& p, unsigned i, Time t) {
            auto sample = d.sample(p);
            Entry e{
                t,
                t,
                {v.id, i, p.ordinal},
                track,
                true,
                project(c, sample, v.request, true),
                Reason::None,
                sample.texture};
            auto matches   = [&](const Candidate& candidate) { return candidate.key == e.key; };
            bool submitted = std::any_of(reservations.begin(), reservations.end(), [&](const Reservation& r) {
                return r.sourceIsPulse && r.source == e.key && r.begin <= at;
            });
            if (submitted)
            {
                e.amplitude        = {};
                e.reason           = Reason::Locked;
                window.lockedMask |= eventMask(c.layout, project(c, sample, v.request, true));
                sink(e);
                return;
            }
            if (std::none_of(window.winners.begin(), window.winners.end(), matches))
            {
                e.reason    = std::any_of(window.ranked.begin(), window.ranked.end(), matches) ? Reason::Window
                                                                                               : Reason::Capacity;
                e.amplitude = {};
                sink(e);
                return;
            }
            constrain(e);
            batch.pulses.push_back(e);
        });
        std::optional<Entry> overflow;
        for (const auto& layer : d.layers)
        {
            Time first = 0, last = v.request.iterations - 1;
            if (at < v.start + layer.start)
                continue;
            if (d.duration)
            {
                if (at >= v.start + layer.tail)
                    first = (at - v.start - layer.tail) / d.duration + 1;
                last = std::min(last, (at - v.start - layer.start) / d.duration);
            }
            for (Time i = first; i <= last; ++i)
            {
                Time local = at - v.start - i * d.duration;
                if (local >= layer.tail)
                    continue;
                Entry e{at, at, {v.id, static_cast<unsigned>(i), layer.ordinal}, track, false, {}};
                // A long release on a microsecond loop can overlap thousands of
                // earlier iterations. Skip the whole range without sampling it.
                if (layers >= ResourceLimit)
                {
                    if (!overflow)
                    {
                        e.reason = Reason::Capacity;
                        e.count  = 0;
                        overflow = e;
                    }
                    overflow->count += static_cast<unsigned>(last - i + 1);
                    break;
                }
                ++layers;
                auto s      = d.sample(layer, local);
                e.amplitude = project(c, s, v.request, false);
                for (double& a : e.amplitude)
                    a *= fadeIn;
                e.texture  = s.texture;
                auto level = unreserved(e.amplitude, e.key, false);
                if (power(e.amplitude) > 0 && !power(level))
                    e.reason = Reason::Locked;
                e.amplitude = level;
                constrain(e);
                batch.layers.push_back(e);
            }
        }
        if (overflow)
            sink(*overflow);
    }
    for (auto& f : fades)
    {
        Entry e{at, at, {f.id, 0, std::numeric_limits<unsigned>::max()}, f.track, false, f.amplitude};
        e.texture = f.texture;
        for (auto& a : e.amplitude)
            a *= 1. - double(at - f.start) / FadeTime;
        constrain(e);
        (f.track == Track::Burst ? bursts.emplace_back() : normal).layers.push_back(e);
    }
    double availableBefore = remaining.total;
    for (auto& batch : bursts)
    {
        batch.allocate(batch.pulses, remaining, &burst, 1);
        batch.allocate(batch.layers, remaining, &burst, 1);
    }
    // Integrate the previous target up to this exact control/source boundary.
    const double elapsed = double(at - lastSample);
    duck                 = duckTarget + (duck - duckTarget) * std::exp(-elapsed / (duckTarget > duck ? 3000. : 35000.));
    lastSample           = at;
    duckTarget =
        total > 0 ? .65 * std::sqrt(std::clamp((lockedBurst + availableBefore - remaining.total) / total, 0., 1.)) : 0;
    normal.allocate(normal.pulses, remaining, nullptr, 1 - duck);
    normal.allocate(normal.layers, remaining, nullptr, 1 - duck);
    auto emit = [&](Batch& batch) {
        for (auto& e : batch.pulses)
        {
            if (power(e.amplitude) > 0)
            {
                e.lockedUntil = at + c.pulseWidth;
                held.push_back({e.lockedUntil, e.track, e.amplitude, e.key});
            }
            // A final budget/lock suppression also decides this window. A later
            // recomputation must not promote a runner-up on the same channels.
            auto winner =
                std::find_if(window.winners.begin(), window.winners.end(), [&](auto& p) { return p.key == e.key; });
            window.lockedMask |= winner->mask;
            e.validUntil = e.lockedUntil;
            sink(e);
        }
        for (auto& e : batch.layers)
        {
            auto voice = std::find_if(active.begin(), active.end(), [&](auto& v) { return v.id == e.key.playback; });
            if (voice != active.end())
            {
                double previousPower = power(voice->last);
                double addedPower    = power(e.amplitude);
                if (addedPower > 0)
                    voice->lastTexture =
                        (voice->lastTexture * previousPower + e.texture * addedPower) / (previousPower + addedPower);
                for (int k = 0; k < 2; ++k)
                    voice->last[k] = std::hypot(voice->last[k], e.amplitude[k]);
            }
            e.validUntil = next;
            sink(e);
        }
    };
    // The validity of a bed also ends at a newly submitted pulse's release.
    next = nextBoundary(at);
    for (auto& batch : bursts)
        for (auto& e : batch.pulses)
            if (power(e.amplitude) > 0)
                next = std::min(next, at + c.pulseWidth);
    for (auto& e : normal.pulses)
        if (power(e.amplitude) > 0)
            next = std::min(next, at + c.pulseWidth);
    for (auto& batch : bursts)
        emit(batch);
    emit(normal);
}

HapticMixer::HapticMixer(Calibration c) : _state(std::make_unique<State>())
{
    if ((c.layout != Layout::Mono && c.layout != Layout::LeftRight && c.layout != Layout::LowHigh) ||
        !within(c.gamma, .5, 2.5) || !within(c.strength, 0, 1) || !within(c.totalCap, 0, 1) || c.pulseWidth <= 0 ||
        c.pulseWidth > Second || !within(c.gain, 0, 4) || !within(c.continuousGain, 0, 4) ||
        !within(c.transientGain, 0, 4))
        throw std::invalid_argument("Invalid haptic calibration");
    for (int k = 0; k < 2; ++k)
        if (!within(c.channelGain[k], 0, 4) || !within(c.cap[k], 0, 1))
            throw std::invalid_argument("Invalid haptic channel calibration");
    _state->calibration = c;
}
HapticMixer::~HapticMixer() = default;
std::unique_ptr<HapticMixer> HapticMixer::checkpoint() const {
    auto copy=std::make_unique<HapticMixer>(_state->calibration);
    *copy->_state=*_state;
    return copy;
}
Time HapticMixer::now() const
{
    return _state->clock;
}

Result<Id> HapticMixer::submit(const HapticClip& clip, const Request& r)
{
    if (r.startAt && *r.startAt < now()) return {{},ErrorInfo{Error::InvalidArgument,{}}};
    return submitAt(clip, r, now(), r.startAt.value_or(now()));
}
void HapticMixer::skipTo(Time t)
{
    if (t <= _state->clock) return;
    _state->clock = t;
    _state->next = t;
    _state->window.dirty = true;
}
Result<Id> HapticMixer::submitAt(const HapticClip& clip, const Request& r, Time received, Time start)
{
    auto& s  = *_state;
    auto bad = [](std::string message, Error code = Error::InvalidArgument) -> Result<Id> {
        return {{}, ErrorInfo{code, {{"$", "PlaybackError", std::move(message)}}}};
    };
    auto& d = ClipAccess::get(clip);
    if (s.sequence == std::numeric_limits<Id>::max())
        return bad("Playback identity exhausted", Error::QueueFull);
    if ((r.track != Track::Normal && r.track != Track::Burst) || start > Never - 40 * Second || start < 0 ||
        start - received > 5 * Second || !within(r.gain, 0, 1) || !within(r.pan, -1, 1) ||
        r.priority.value_or(0) > 255 || !validKey(r.mergeKey) || !r.iterations || r.iterations > 65535 ||
        d.nodes > 65536 / r.iterations || (r.iterations != 1 && (!d.duration || r.track == Track::Burst)))
        return bad("Invalid playback bounds or options");
    Time renderEnd = d.renderEnd;
    if (!d.pulses.empty())
        renderEnd = std::max(renderEnd, d.pulses.back().at + s.calibration.pulseWidth);
    Time span = renderEnd + (r.iterations - 1) * d.duration;
    if (span > (r.track == Track::Burst ? Second : 30 * Second))
        return bad("Playback and rendering tail exceed track limit");
    Voice voice{
        clip,
        r,
        s.sequence + 1,
        received,
        start,
        start + span,
        r.priority.value_or(r.track == Track::Burst ? 128u : 64u)};
    for (auto* pool : {&s.active, &s.pending})
        for (auto& other : *pool)
            if (canMerge(other, voice))
            {
                other.request.gain = std::max(other.request.gain, r.gain);
                s.terminals.push_back({++s.sequence, Outcome::Coalesced, s.clock, other.id});
                s.change();
                return {s.sequence, {}};
            }
    if (s.pending.size() >= 32)
        return bad("Pending request capacity exhausted", Error::QueueFull);
    s.pending.push_back(std::move(voice));
    std::sort(s.pending.begin(), s.pending.end(), [](auto& a, auto& b) {
        return a.start != b.start ? a.start < b.start : higher(a, b);
    });
    ++s.sequence;
    s.change();
    return {s.sequence, {}};
}
bool HapticMixer::stop(Id id)
{
    auto& s = *_state;
    for (auto* pool : {&s.active, &s.pending})
        if (std::erase_if(*pool, [&](auto& v) { return v.id == id; }))
        {
            s.terminals.push_back({id, Outcome::Stopped, s.clock});
            s.change();
            return true;
        }
    return false;
}
bool HapticMixer::reserve(const Reservation& r)
{
    auto& s       = *_state;
    auto physical = s.calibration.layout == Layout::Mono ? 1u : 3u;
    auto channels = r.channelMask ? r.channelMask : physical;
    if ((channels & ~physical) || (maskOf(r.amplitude) & ~channels) ||
        (r.track != Track::Normal && r.track != Track::Burst) || r.end <= r.begin || r.end <= s.clock || r.begin < 0 ||
        r.end > Never - 40 * Second || !within(r.amplitude[0], 0, 1) || !within(r.amplitude[1], 0, 1))
        return false;
    auto it =
        std::find_if(s.reservations.begin(), s.reservations.end(), [&](auto& old) { return old.token == r.token; });
    if (it != s.reservations.end())
        return it->begin == r.begin && it->end == r.end && it->amplitude == r.amplitude && it->track == r.track &&
               it->source == r.source && it->canOverlay == r.canOverlay && it->channelMask == r.channelMask &&
               it->sourceIsPulse == r.sourceIsPulse;
    if (r.source && std::any_of(s.reservations.begin(), s.reservations.end(), [&](const Reservation& old) {
            auto oldMask = old.channelMask ? old.channelMask : physical;
            return old.source == r.source && old.sourceIsPulse == r.sourceIsPulse && (channels & oldMask) &&
                   old.begin < r.end && r.begin < old.end;
        }))
        return false;
    s.reservations.push_back(r);
    s.change();
    return true;
}
void HapticMixer::advance(Time until, const std::function<void(const Entry&)>& sink)
{
    auto& s = *_state;
    if (until < s.clock)
        throw std::invalid_argument("Haptic clock must be monotonic");
    while (s.next < until)
        s.plan(s.next, sink);
    s.clock = until;
}
std::vector<Terminal> HapticMixer::takeTerminals()
{
    std::vector<Terminal> result;
    result.swap(_state->terminals);
    return result;
}
}  // namespace cc::haptics::detail
