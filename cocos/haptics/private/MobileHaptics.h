#pragma once
#include "haptics/private/HapticMixer.h"
#include <algorithm>
#include <atomic>
#include <variant>

namespace cc::haptics::detail
{
struct MobileCapabilities
{
    MobilePlatform platform = MobilePlatform::None;
    bool amplitude{}, envelope{}, canStop{}, conflictsWithGamepads{}, stereo{};
    const char* envelopeStatus = "NotApplicable";  // Static route diagnostic for the public snapshot.
    bool heV1{}, heV2{}, ahap{};
};
struct MobileSample
{
    unsigned durationMs{};
    float amplitude{}, sharpness{}, rightAmplitude{}, rightSharpness{};
};
struct MobilePacket
{
    std::vector<MobileSample> samples;
    std::vector<AppleEvent> transients, rightTransients;
};
using MobileEffect = std::variant<
    std::monostate,
    AndroidOneShot,
    AndroidWaveform,
    AndroidEffect,
    AndroidComposition,
    AndroidEnvelope,
    ApplePattern,
    AppleParameters,
    AppleParameterCurve>;
struct MobileCommand
{
    enum class Kind
    {
        Preset,
        Android,
        Apple,
        Parameters,
        Curve,
        Stop,
        Prepare
    };
    Kind kind = Kind::Preset;
    MobilePacket packet;
    std::optional<HapticClip> original; // Present only for the first, exclusive preset submission.
    MobileEffect raw;
    std::uint64_t player{};
    Time startUs{}, endUs{};
    bool replace{};
    bool immediateStart{};
    Time latestOriginalStartUs{}; // Exclusive, bounded by the complete native span and the writable window.
    Time originalDeadline() const
    {
        return latestOriginalStartUs ? latestOriginalStartUs : std::min(endUs, startUs + 8000);
    }
    std::shared_ptr<const std::atomic_bool> gate;  // Recheck after a cold native start or replacement.
};
inline constexpr auto mobileNoOutput = static_cast<input::Error>(256);  // No nonzero native call was made.
inline constexpr auto mobileOriginalDeclined = static_cast<input::Error>(257); // Proven not started.
inline constexpr auto mobileHeSubmitted = static_cast<input::Error>(258); // Finite, asynchronous handset HE start.
using MobileGate                     = std::shared_ptr<const std::atomic_bool>;
using MobileReceipt                  = std::shared_ptr<std::atomic<int>>;
class MobileOutput
{
public:
    virtual ~MobileOutput()                         = default;
    virtual MobileCapabilities capabilities() const = 0;
    virtual input::Error prepare(MobileGate, MobileReceipt r)
    {
        r->store(int(input::Error::None));
        return input::Error::None;
    }
    virtual input::Error submit(MobileCommand command, MobileGate gate, MobileReceipt receipt) = 0;
};
// Platform work runs on one output thread per physical route. Stop is ordered
// after in-flight writes and reports native evidence separately from acceptance.
class MobileDriver
{
public:
    virtual ~MobileDriver() = default;
    virtual input::Error prepare() { return input::Error::None; }
    virtual input::Error execute(const MobileCommand& command) = 0;
};
std::shared_ptr<MobileOutput> queueMobileDriver(MobileCapabilities caps, std::unique_ptr<MobileDriver> driver);
std::shared_ptr<MobileOutput> makeMobileOutput(int inputDevice = -1);
void attachMobileHost(HapticService& service);
void mobileFocus(bool active);
void mobileVibrate(float seconds);
void mobileReset();
void mobileForwarding(bool enabled);
Time mobileNow();
bool limitMobileEffect(MobileEffect& effect, MobileCapabilities caps, float ceiling);
Result<Time> validateMobileEffect(const MobileEffect& effect, MobileCapabilities caps);
MobilePacket mobilePacket(
    HapticMixer& mixer, Time begin, Time end, MobilePlatform platform, const std::function<void(Id)>& contributed);
}  // namespace cc::haptics::detail
