#pragma once
#include "haptics/private/HapticMixer.h"
#include <atomic>
#include <variant>

namespace cc::haptics::detail
{
struct MobileCapabilities
{
    MobilePlatform platform = MobilePlatform::None;
    bool amplitude{}, envelope{}, canStop{}, conflictsWithGamepads{}, stereo{};
    const char* envelopeStatus = "NotApplicable";  // Static route diagnostic for the public snapshot.
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
    MobileEffect raw;
    std::uint64_t player{};
    Time startUs{}, endUs{};
    bool replace{};
    bool immediateStart{};
    std::shared_ptr<const std::atomic_bool> gate;  // Recheck after a cold native start or replacement.
};
inline constexpr auto mobileNoOutput = static_cast<input::Error>(256);  // No nonzero native call was made.
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
Result<Time> validateMobileEffect(const MobileEffect& effect, MobileCapabilities caps);
MobilePacket mobilePacket(
    HapticMixer& mixer, Time begin, Time end, MobilePlatform platform, const std::function<void(Id)>& contributed);
}  // namespace cc::haptics::detail
