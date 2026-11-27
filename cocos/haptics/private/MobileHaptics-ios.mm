#include "AppleHapticDriver.h"
#import <dispatch/dispatch.h>
#include <algorithm>
#include <cmath>
#include <map>

namespace cc::haptics::detail
{
namespace
{
using E = input::Error;
CHHapticDynamicParameterID parameterId(AppleControl control)
{
    return control == AppleControl::Intensity ? CHHapticDynamicParameterIDHapticIntensityControl
                                              : CHHapticDynamicParameterIDHapticSharpnessControl;
}
CHHapticEvent* event(const AppleEvent& e)
{
    auto intensity = [[CHHapticEventParameter alloc] initWithParameterID:CHHapticEventParameterIDHapticIntensity
                                                                   value:e.intensity];
    auto sharpness = [[CHHapticEventParameter alloc] initWithParameterID:CHHapticEventParameterIDHapticSharpness
                                                                   value:e.sharpness];
    if (e.duration == 0)
        return [[CHHapticEvent alloc] initWithEventType:CHHapticEventTypeHapticTransient
                                             parameters:@[ intensity, sharpness ]
                                           relativeTime:e.time];
    return [[CHHapticEvent alloc] initWithEventType:CHHapticEventTypeHapticContinuous
                                         parameters:@[ intensity, sharpness ]
                                       relativeTime:e.time
                                           duration:e.duration];
}
NSArray<CHHapticDynamicParameter*>* parameters(const std::vector<AppleParameter>& values)
{
    auto result = [NSMutableArray<CHHapticDynamicParameter*> arrayWithCapacity:values.size()];
    for (auto& p : values)
        [result addObject:[[CHHapticDynamicParameter alloc] initWithParameterID:parameterId(p.control)
                                                                          value:p.value
                                                                   relativeTime:p.time]];
    return result;
}
CHHapticParameterCurve* curve(const AppleParameterCurve& c)
{
    auto points = [NSMutableArray<CHHapticParameterCurveControlPoint*> arrayWithCapacity:c.points.size()];
    for (auto p : c.points)
        [points addObject:[[CHHapticParameterCurveControlPoint alloc] initWithRelativeTime:p.time value:p.value]];
    return [[CHHapticParameterCurve alloc] initWithParameterID:parameterId(c.control)
                                                 controlPoints:points
                                                  relativeTime:0];
}
void appendCurves(ApplePattern& pattern, AppleControl control, const std::vector<AppleCurvePoint>& points)
{
    for (size_t i = 0; i + 1 < points.size();)
    {
        size_t last = std::min(i + 15, points.size() - 1);
        AppleParameterCurve c{control, points[i].time, {}};
        for (size_t j = i; j <= last; ++j)
            c.points.push_back({points[j].time - c.time, points[j].value});
        pattern.curves.push_back(std::move(c));
        i = last;
    }
}
ApplePattern preset(const MobileCommand& cmd, double late)
{
    ApplePattern pattern;
    std::vector<AppleCurvePoint> intensity, sharpness;
    double offset = 0;
    for (auto& s : cmd.packet.samples)
    {
        const auto next = offset + s.durationMs * .001;
        if (next > late)
        {
            const double at = std::max(0., offset - late);
            // Hold the last segment value up to the next edge; do not interpolate across silence.
            if (!intensity.empty() && at - intensity.back().time > .0001)
            {
                intensity.push_back({at - .0001, intensity.back().value});
                sharpness.push_back({at - .0001, sharpness.back().value});
            }
            intensity.push_back({at, s.amplitude});
            sharpness.push_back({at, s.sharpness - .5f});
        }
        offset = next;
    }
    if (!intensity.empty() && std::ranges::any_of(intensity, [](auto& p) { return p.value > 0; }))
    {
        double length = offset - late;
        intensity.push_back({length, intensity.back().value});
        sharpness.push_back({length, sharpness.back().value});
        pattern.events.push_back({0, length, 1, .5f});
        appendCurves(pattern, AppleControl::Intensity, intensity);
        appendCurves(pattern, AppleControl::Sharpness, sharpness);
    }
    // Keep transients on their own player: bed dynamic parameters must not scale native impulses.
    return pattern;
}
struct EngineState
{
    std::atomic_bool valid{true};
    std::atomic_bool expectedStop{false};
};
class AppleDriver final : public MobileDriver
{
    std::function<CHHapticEngine*()> factory;
    std::function<void()> interrupted;
    CHHapticEngine* engine = nil;
    std::shared_ptr<EngineState> state;
    struct Player
    {
        id<CHHapticAdvancedPatternPlayer> native;
        double origin;
        std::shared_ptr<std::atomic_bool> finished;
    };
    std::vector<Player> presetPlayers;
    std::optional<Player> raw;
    std::uint64_t rawId{};
    E start()
    {
        if (engine && state->valid.load())
            return E::None;
        if (engine)
        {
            if (stop() != E::None)
                return E::BackendFailure;
        }
        engine = factory();
        if (!engine)
            return E::Unsupported;
        state           = std::make_shared<EngineState>();
        auto generation = state;
        auto notify     = interrupted;
        auto invalidate = ^{
          if (!generation->expectedStop && generation->valid.exchange(false) && notify)
              notify();
        };
        engine.resetHandler   = ^{ invalidate(); };
        engine.stoppedHandler = ^(CHHapticEngineStoppedReason reason) {
          if (reason != CHHapticEngineStoppedReasonNotifyWhenFinished)
              invalidate();
        };
        engine.playsHapticsOnly    = YES;
        engine.autoShutdownEnabled = NO;
        if (![engine startAndReturnError:nil])
        {
            state->expectedStop = true;
            engine              = nil;
            return E::BackendFailure;
        }
        return E::None;
    }
    E stop()
    {
        if (!engine)
            return E::None;
        state->expectedStop         = true;
        auto ok                     = std::make_shared<std::atomic_bool>(false);
        dispatch_semaphore_t signal = dispatch_semaphore_create(0);
        [engine stopWithCompletionHandler:^(NSError* error) {
          ok->store(error == nil);
          dispatch_semaphore_signal(signal);
        }];
        if (dispatch_semaphore_wait(signal, dispatch_time(DISPATCH_TIME_NOW, 190 * NSEC_PER_MSEC)) || !ok->load())
            return E::BackendFailure;
        engine.resetHandler   = nil;
        engine.stoppedHandler = nil;
        raw.reset();
        rawId = 0;
        presetPlayers.clear();
        engine = nil;
        return E::None;
    }
    std::optional<Player> play(const ApplePattern& p, double origin, const MobileGate& gate)
    {
        auto events = [NSMutableArray<CHHapticEvent*> arrayWithCapacity:p.events.size()];
        for (auto& e : p.events)
            [events addObject:event(e)];
        auto pattern = [[CHHapticPattern alloc] initWithEvents:events parameters:parameters(p.parameters) error:nil];
        auto player  = pattern ? [engine createAdvancedPlayerWithPattern:pattern error:nil] : nil;
        if (!player)
            return {};
        auto done                = std::make_shared<std::atomic_bool>(false);
        player.completionHandler = ^(NSError*) { done->store(true); };
        player.loopEnabled       = NO;
        if ((gate && !gate->load()) || ![player startAtTime:origin error:nil])
            return {};
        for (auto& c : p.curves)
            if (![player scheduleParameterCurve:curve(c) atTime:origin + c.time error:nil])
            {
                [player cancelAndReturnError:nil];
                return {};
            }
        return Player{player, origin, done};
    }

public:
    AppleDriver(std::function<CHHapticEngine*()> f, std::function<void()> n)
        : factory(std::move(f)), interrupted(std::move(n))
    {
    }
    E prepare() override
    {
        @autoreleasepool
        {
            return start();
        }
    }
    E execute(const MobileCommand& cmd) override
    {
        @autoreleasepool
        {
            using K = MobileCommand::Kind;
            if (cmd.kind == K::Stop)
                return stop();
            if (cmd.kind == K::Apple && raw && !raw->finished->load())
            {
                if (!cmd.replace)
                    return E::Busy;
                auto e = stop();
                if (e != E::None)
                    return e;
            }
            if (cmd.kind == K::Preset && cmd.replace)
            {
                auto status = stop();
                if (status != E::None)
                    return status;
            }
            auto e = start();
            if (e != E::None)
                return e;
            const auto now = mobileNow();
            if (cmd.gate && !cmd.gate->load())
                return E::Busy;
            if (cmd.kind == K::Apple && now - cmd.startUs >= 500000)
                return E::Busy;
            if (cmd.kind != K::Apple && now >= cmd.endUs && !(cmd.immediateStart && now - cmd.startUs < 8000))
                return mobileNoOutput;
            const double origin = engine.currentTime + std::max<Time>(0, cmd.startUs - now) / double(Second);
            std::erase_if(presetPlayers, [](const Player& p) { return p.finished->load(); });
            if (cmd.kind == K::Apple)
            {
                raw   = play(std::get<ApplePattern>(cmd.raw), origin, cmd.gate);
                rawId = cmd.player;
                return raw ? E::None : E::BackendFailure;
            }
            if (cmd.kind == K::Parameters || cmd.kind == K::Curve)
            {
                if (!raw || raw->finished->load() || rawId != cmd.player)
                    return E::InvalidArgument;
                if (cmd.kind == K::Parameters)
                {
                    auto list = parameters(std::get<AppleParameters>(cmd.raw).parameters);
                    return [raw->native sendParameters:list atTime:raw->origin error:nil] ? E::None : E::BackendFailure;
                }
                auto& c = std::get<AppleParameterCurve>(cmd.raw);
                return [raw->native scheduleParameterCurve:curve(c) atTime:raw->origin + c.time error:nil]
                           ? E::None
                           : E::BackendFailure;
            }
            if (cmd.kind != K::Preset)
                return E::Unsupported;
            const double late = cmd.immediateStart && now - cmd.startUs < 8000
                                    ? 0.
                                    : std::max<Time>(0, now - cmd.startUs) / double(Second);
            auto bed          = preset(cmd, late);
            ApplePattern pulses;
            for (auto p : cmd.packet.transients)
                if (p.time + .008 >= late)
                {
                    p.time = std::max(0., p.time - late);
                    pulses.events.push_back(p);
                }
            for (auto* pattern : {&bed, &pulses})
                if (!pattern->events.empty())
                {
                    auto player = play(*pattern, origin, cmd.gate);
                    if (!player)
                        return E::BackendFailure;
                    presetPlayers.push_back(std::move(*player));
                }
            return E::None;
        }
    }
};
}  // namespace
std::unique_ptr<MobileDriver> makeAppleHapticDriver(
    std::function<CHHapticEngine*()> factory, std::function<void()> interrupted)
{
    return std::make_unique<AppleDriver>(std::move(factory), std::move(interrupted));
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
std::shared_ptr<MobileOutput> makeMobileOutput(int id)
{
    if (id != -1 || ![[CHHapticEngine capabilitiesForHardware] supportsHaptics])
        return {};
    return queueMobileDriver(
        {MobilePlatform::Apple, true, false, true, false},
        makeAppleHapticDriver([] { return [[CHHapticEngine alloc] initAndReturnError:nil]; }, mobileReset));
}
#endif
}  // namespace cc::haptics::detail
