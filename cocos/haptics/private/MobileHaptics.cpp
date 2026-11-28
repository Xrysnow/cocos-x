#include "MobileHaptics.h"
#include "AndroidWriteBudget.h"
#include "HapticControl.h"
#include <algorithm>
#include <cmath>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

namespace cc::haptics::detail
{
using Native = input::Error;
Time mobileNow()
{
    return input::detail::nowNs() / 1000;
}
namespace
{
class OutputQueue final : public MobileOutput
{
    struct Job
    {
        MobileCommand command;
        MobileGate gate;
        MobileReceipt receipt;
    };
    MobileCapabilities caps;
    std::unique_ptr<MobileDriver> driver;
    std::mutex mutex;
    std::condition_variable ready;
    std::deque<Job> jobs;
    bool closing = false;
    std::thread worker;
    void run()
    {
        AndroidWriteBudget writeBudget;
        bool needsStop = false;
        for (;;)
        {
            std::unique_lock lock(mutex);
            ready.wait(lock, [&] { return closing || !jobs.empty(); });
            if (closing)
                break;
            auto job = std::move(jobs.front());
            jobs.pop_front();
            lock.unlock();
            auto now            = mobileNow();
            const bool stopping = job.command.kind == MobileCommand::Kind::Stop;
            const bool rawStart =
                job.command.kind == MobileCommand::Kind::Android || job.command.kind == MobileCommand::Kind::Apple;
            job.command.gate = job.gate;
            Native result    = Native::Busy;
            if (job.command.kind == MobileCommand::Kind::Prepare)
            {
                job.receipt->store(int(job.gate->load() ? driver->prepare() : Native::Busy));
                continue;
            }
            // A queued preset can arrive just before the worker's window opens even
            // when admission met its own deadline. Wait only while its samples are live.
            if (caps.platform == MobilePlatform::Android && job.command.kind == MobileCommand::Kind::Preset)
            {
                const auto until = std::min(writeBudget.availableAt(now), job.command.endUs);
                if (until > now)
                {
                    lock.lock();
                    ready.wait_for(lock, std::chrono::microseconds(until - now),
                                   [&] { return closing || !job.gate->load(); });
                    const bool shutdown = closing;
                    lock.unlock();
                    if (shutdown || !job.gate->load())
                    {
                        job.receipt->store(int(Native::Busy));
                        continue;
                    }
                    now = mobileNow();
                }
                if (now >= job.command.endUs && !(job.command.immediateStart && now - job.command.startUs < 8000))
                {
                    job.receipt->store(int(mobileNoOutput));
                    continue;
                }
            }
            if (job.gate->load() &&
                (stopping || (rawStart && now - job.command.startUs < 500000) || now < job.command.endUs ||
                 (job.command.immediateStart && now - job.command.startUs < 8000)))
            {
                if (!stopping && caps.platform == MobilePlatform::Android && writeBudget.availableAt(now) > now)
                    result = job.command.kind == MobileCommand::Kind::Preset ? mobileNoOutput : Native::QueueFull;
                else
                {
                    result = driver->execute(job.command);
                    // JNI validation and effect construction precede vibrate(). Its return
                    // time bounds the attempt even if the output thread was descheduled.
                    if (!stopping && caps.platform == MobilePlatform::Android)
                        writeBudget.record(mobileNow());
                    if (stopping)
                        needsStop =
                            result != Native::None && result != Native::Unsupported && result != Native::Disconnected;
                    else if (result == Native::None || result == Native::BackendFailure)
                        needsStop = true;
                }
            }
            job.receipt->store(int(result));
        }
        if (needsStop)
        {
            MobileCommand stop;
            stop.kind = MobileCommand::Kind::Stop;
            driver->execute(stop);
        }
    }

public:
    OutputQueue(MobileCapabilities caps_, std::unique_ptr<MobileDriver> d)
        : caps(caps_), driver(std::move(d)), worker([this] { run(); })
    {
    }
    ~OutputQueue() override
    {
        {
            std::lock_guard lock(mutex);
            closing = true;
            for (auto& j : jobs)
                j.receipt->store(int(Native::Disconnected));
            jobs.clear();
        }
        ready.notify_one();
        worker.join();
    }
    MobileCapabilities capabilities() const override { return caps; }
    Native prepare(MobileGate gate, MobileReceipt r) override
    {
        MobileCommand cmd;
        cmd.kind = MobileCommand::Kind::Prepare;
        return submit(std::move(cmd), std::move(gate), std::move(r));
    }
    Native submit(MobileCommand cmd, MobileGate gate, MobileReceipt receipt) override
    {
        std::lock_guard lock(mutex);
        if (closing)
            return Native::Disconnected;
        if (jobs.size() >= (cmd.kind == MobileCommand::Kind::Stop ? 17u : 16u))
            return Native::QueueFull;
        jobs.push_back({std::move(cmd), std::move(gate), std::move(receipt)});
        ready.notify_one();
        return Native::None;
    }
};
struct Host
{
    std::mutex mutex;
    std::weak_ptr<HapticControl> control;
    bool active = false;
};
Host& host()
{
    static Host state;
    return state;
}
bool unit(double value)
{
    return value >= 0 && value <= 1;
}
bool timeOk(double time)
{
    return time >= 0 && time <= 5;
}
bool parameterOk(AppleControl c, float value)
{
    return c == AppleControl::Intensity ? unit(value) : c == AppleControl::Sharpness && value >= -1 && value <= 1;
}
bool curveOk(const AppleParameterCurve& c)
{
    if (!timeOk(c.time) || c.points.empty() || c.points.size() > 16)
        return false;
    double prev = -1;
    for (auto& p : c.points)
    {
        if (!timeOk(p.time) || p.time <= prev || !timeOk(c.time + p.time) || !parameterOk(c.control, p.value))
            return false;
        prev = p.time;
    }
    return true;
}
}  // namespace
std::shared_ptr<MobileOutput> queueMobileDriver(MobileCapabilities caps, std::unique_ptr<MobileDriver> driver)
{
    return std::make_shared<OutputQueue>(caps, std::move(driver));
}
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS
std::shared_ptr<MobileOutput> makeMobileOutput(int)
{
    return {};
}
#endif
void attachMobileHost(HapticService& service)
{
    auto port     = makeMobileOutput();
    auto& control = HapticControl::get(service);
    if (port)
        control.publishMobile(std::move(port));
    auto& state = host();
    std::lock_guard lock(state.mutex);
    state.control = control.weak(service);
    control.platformFocus(state.active);
}
void mobileFocus(bool active)
{
    auto& state = host();
    std::lock_guard lock(state.mutex);
    state.active = active;
    if (auto c = state.control.lock())
        c->platformFocus(active);
}
void mobileReset()
{
    auto& state = host();
    std::lock_guard lock(state.mutex);
    if (auto c = state.control.lock())
    {
        c->platformFocus(false);
        c->platformFocus(state.active);
    }
}
void mobileForwarding(bool enabled)
{
    auto& state = host();
    std::lock_guard lock(state.mutex);
    if (auto c = state.control.lock())
        c->forwarding(enabled);
}
void mobileVibrate(float seconds)
{
    auto& state = host();
    std::shared_ptr<HapticControl> control;
    {
        std::lock_guard lock(state.mutex);
        control = state.control.lock();
    }
    if (control)
        control->compatVibrate(seconds);
}

Result<Time> validateMobileEffect(const MobileEffect& effect, MobileCapabilities caps)
{
    auto bad = [](Error e = Error::InvalidArgument) -> Result<Time> { return {{}, ErrorInfo{e, {}}}; };
    auto ms  = [&](unsigned duration) -> Result<Time> {
        return duration > 0 && duration <= 1000 ? Result<Time>{Time(duration) * 1000, {}} : bad();
    };
    if (effect.index() >= 1 && effect.index() <= 5)
    {
        if (caps.platform != MobilePlatform::Android)
            return bad(Error::Unsupported);
        if (auto p = std::get_if<AndroidOneShot>(&effect))
        {
            if (p->amplitude != -1 && (p->amplitude < 1 || p->amplitude > 255))
                return bad();
            if (!caps.amplitude && p->amplitude != -1 && p->amplitude != 255)
                return bad(Error::Unsupported);
            return ms(p->durationMs);
        }
        if (auto w = std::get_if<AndroidWaveform>(&effect))
        {
            if (w->steps.empty() || w->steps.size() > 128)
                return bad();
            unsigned total = 0;
            bool on        = false;
            for (auto& step : w->steps)
            {
                if (step.durationMs == 0 || step.durationMs > 1000 - total || step.amplitude < -1 ||
                    step.amplitude > 255)
                    return bad();
                if (!caps.amplitude && step.amplitude > 0 && step.amplitude < 255)
                    return bad(Error::Unsupported);
                total += step.durationMs;
                on    |= step.amplitude != 0;
            }
            return on ? ms(total) : bad();
        }
        if (auto e = std::get_if<AndroidEnvelope>(&effect))
        {
            if (!caps.envelope)
                return bad(Error::Unsupported);
            if (e->points.empty() || e->points.size() > 64 || e->points.back().amplitude != 0)
                return bad();
            unsigned total = 0;
            bool on        = false;
            for (auto& p : e->points)
            {
                if (!p.durationMs || p.durationMs > 1000 - total || !unit(p.amplitude) ||
                    !(e->frequency ? (std::isfinite(p.texture) && p.texture > 0) : unit(p.texture)))
                    return bad();
                total += p.durationMs;
                on    |= p.amplitude > 0;
            }
            return on ? ms(total) : bad();
        }
        if (auto c = std::get_if<AndroidComposition>(&effect))
        {
            if (c->steps.empty() || c->steps.size() > 16)
                return bad();
            unsigned delay = 0;
            for (auto& p : c->steps)
            {
                if (!p.id || p.id > 8 || !unit(p.scale) || p.delayMs > 1000 - delay)
                    return bad();
                delay += p.delayMs;
            }
            // The platform verifies every primitive and its measured duration before submitting.
            return ms(1000);
        }
        return bad(Error::Unsupported);  // Predefined effects expose no portable finite duration.
    }
    if (caps.platform != MobilePlatform::Apple)
        return bad(Error::Unsupported);
    double end  = 0;
    auto params = [&](const auto& list) {
        if (list.size() > 128)
            return false;
        double prev = -1;
        for (auto& p : list)
        {
            if (!timeOk(p.time) || p.time < prev || !parameterOk(p.control, p.value))
                return false;
            prev = p.time;
            end  = std::max(end, p.time);
        }
        return true;
    };
    if (auto p = std::get_if<ApplePattern>(&effect))
    {
        if (p->events.empty() || p->events.size() > 128 || p->curves.size() > 32 || !params(p->parameters))
            return bad();
        double prev = -1;
        for (auto& e : p->events)
        {
            if (!timeOk(e.time) || e.time < prev || !timeOk(e.duration) || !timeOk(e.time + e.duration) ||
                !unit(e.intensity) || !unit(e.sharpness))
                return bad();
            prev = e.time;
            end  = std::max(end, e.time + e.duration);
        }
        for (auto& c : p->curves)
        {
            if (!curveOk(c))
                return bad();
            end = std::max(end, c.time + c.points.back().time);
        }
    }
    else if (auto parameters = std::get_if<AppleParameters>(&effect))
    {
        if (parameters->parameters.empty() || !params(parameters->parameters))
            return bad();
    }
    else if (auto c = std::get_if<AppleParameterCurve>(&effect))
    {
        if (!curveOk(*c))
            return bad();
        end = c->time + c->points.back().time;
    }
    else
        return bad();
    return {std::max<Time>(1000, std::llround(end * Second)), {}};
}

MobilePacket mobilePacket(
    HapticMixer& mixer, Time begin, Time end, MobilePlatform platform, const std::function<void(Id)>& contributed)
{
    struct Bucket
    {
        Channels energy{}, quality{};
    };
    const auto n = static_cast<size_t>((end - begin + 999) / 1000);
    std::vector<Bucket> bins(n);
    MobilePacket packet;
    mixer.advance(end, [&](const Entry& e) {
        if (e.reason != Reason::None || (e.amplitude[0] <= 0 && e.amplitude[1] <= 0))
            return;
        contributed(e.key.playback);
        if (e.pulse && platform == MobilePlatform::Apple)
        {
            for (unsigned side = 0; side != 2; ++side)
                if (e.amplitude[side] > 0)
                    (side ? packet.rightTransients : packet.transients)
                        .push_back({double(e.at - begin) / Second, 0, float(e.amplitude[side]), float(e.texture)});
            return;
        }
        auto from = std::max(begin, e.at), to = std::min(end, e.validUntil);
        while (from < to)
        {
            const auto i    = static_cast<size_t>((from - begin) / 1000);
            const Time stop = std::min(to, begin + Time(i + 1) * 1000);
            for (unsigned side = 0; side != 2; ++side)
            {
                const double power     = e.amplitude[side] * e.amplitude[side] * double(stop - from) / 1000;
                bins[i].energy[side]  += power;
                bins[i].quality[side] += power * e.texture;
            }
            from = stop;
        }
    });
    for (auto bin : bins)
    {
        auto amplitude = [&](unsigned side) {
            return float(std::floor(255 * std::sqrt(std::min(1., bin.energy[side]))) / 255);
        };
        auto quality = [&](unsigned side) {
            return bin.energy[side] > 0 ? float(std::round(255 * bin.quality[side] / bin.energy[side]) / 255) : 0.f;
        };
        MobileSample value{1, amplitude(0), quality(0), amplitude(1), quality(1)};
        if (!packet.samples.empty() && packet.samples.back().amplitude == value.amplitude &&
            packet.samples.back().sharpness == value.sharpness &&
            packet.samples.back().rightAmplitude == value.rightAmplitude &&
            packet.samples.back().rightSharpness == value.rightSharpness)
            ++packet.samples.back().durationMs;
        else
            packet.samples.push_back(value);
    }
    return packet;
}
}  // namespace cc::haptics::detail
