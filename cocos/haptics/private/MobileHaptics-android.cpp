#include "MobileHaptics.h"
#include "platform/android/jni/JniHelper.h"
#include <algorithm>
#include <cmath>

namespace cc::haptics::detail
{
// Java performs its final gate check on this same attached output thread.
thread_local MobileGate currentVibrationGate;
namespace
{
using E                      = input::Error;
constexpr const char* bridge = "org/cocos/lib/CocosHaptics";
struct Payload
{
    int kind{};
    std::vector<jlong> durations;
    std::vector<jint> amplitudes;
    std::vector<jfloat> values;
    void step(jlong ms, int amp, float texture = -1)
    {
        if (ms <= 0)
            return;
        if (!amplitudes.empty() && amplitudes.back() == amp && (texture < 0 || values.back() == texture))
            durations.back() += ms;
        else
        {
            durations.push_back(ms);
            amplitudes.push_back(amp);
            if (texture >= 0)
                values.push_back(texture);
        }
    }
};
class AndroidDriver final : public MobileDriver
{
    jobject actuator;
    jmethodID executeMethod, stopMethod;

public:
    AndroidDriver(jobject ref, jmethodID run, jmethodID stop) : actuator(ref), executeMethod(run), stopMethod(stop) {}
    ~AndroidDriver() override
    {
        if (auto* env = JniHelper::getEnv())
            env->DeleteGlobalRef(actuator);
    }
    E execute(const MobileCommand& cmd) override
    {
        auto* env = JniHelper::getEnv();
        if (!env)
            return E::BackendFailure;
        if (cmd.kind == MobileCommand::Kind::Stop)
        {
            auto e = env->CallIntMethod(actuator, stopMethod);
            if (env->ExceptionCheck())
            {
                env->ExceptionClear();
                return E::BackendFailure;
            }
            return static_cast<E>(e);
        }
        Payload p;
        if (cmd.kind == MobileCommand::Kind::Preset)
        {
            auto late = mobileNow() - cmd.startUs;
            auto skip = cmd.immediateStart && late < 8000 ? 0 : std::max<Time>(0, late / 1000);
            for (auto& s : cmd.packet.samples)
            {
                auto cut  = std::min<Time>(s.durationMs, skip);
                skip     -= cut;
                p.step(s.durationMs - cut, std::clamp(int(std::lround(s.amplitude * 255)), 0, 255), s.sharpness);
            }
            if (p.amplitudes.empty() || std::ranges::none_of(p.amplitudes, [](auto a) { return a > 0; }))
                return mobileNoOutput;
        }
        else if (auto pulse = std::get_if<AndroidOneShot>(&cmd.raw))
        {
            p.kind = 1;
            p.step(pulse->durationMs, pulse->amplitude);
        }
        else if (auto wave = std::get_if<AndroidWaveform>(&cmd.raw))
        {
            p.kind = 2;
            for (auto& s : wave->steps)
                p.step(s.durationMs, s.amplitude);
        }
        else if (auto c = std::get_if<AndroidComposition>(&cmd.raw))
        {
            p.kind = 3;
            for (auto& s : c->steps)
            {
                p.durations.push_back(s.delayMs);
                p.amplitudes.push_back(s.id);
                p.values.push_back(s.scale);
            }
        }
        else if (auto envelope = std::get_if<AndroidEnvelope>(&cmd.raw))
        {
            p.kind = envelope->frequency ? 5 : 4;
            for (auto& s : envelope->points)
            {
                p.durations.push_back(s.durationMs);
                p.values.push_back(s.amplitude);
            }
            for (auto& s : envelope->points)
                p.values.push_back(s.texture);
        }
        else
            return E::Unsupported;
        if (env->PushLocalFrame(4) < 0)
        {
            env->ExceptionClear();
            return E::BackendFailure;
        }
        auto d   = env->NewLongArray(p.durations.size());
        auto a   = env->NewIntArray(p.amplitudes.size());
        auto v   = env->NewFloatArray(p.values.size());
        E result = E::BackendFailure;
        if (d && a && v)
        {
            if (!p.durations.empty())
                env->SetLongArrayRegion(d, 0, p.durations.size(), p.durations.data());
            if (!p.amplitudes.empty())
                env->SetIntArrayRegion(a, 0, p.amplitudes.size(), p.amplitudes.data());
            if (!p.values.empty())
                env->SetFloatArrayRegion(v, 0, p.values.size(), p.values.data());
            if (!env->ExceptionCheck())
            {
                currentVibrationGate = cmd.gate;
                result               = static_cast<E>(env->CallIntMethod(actuator, executeMethod, p.kind, d, a, v));
                currentVibrationGate.reset();
            }
        }
        if (env->ExceptionCheck())
        {
            env->ExceptionClear();
            result = E::BackendFailure;
        }
        env->PopLocalFrame(nullptr);
        return result;
    }
};
}  // namespace
std::shared_ptr<MobileOutput> makeMobileOutput(int id)
{
    JniMethodInfo info;
    if (!JniHelper::getStaticMethodInfo(info, bridge, "open", "(I)Lorg/cocos/lib/CocosHaptics;"))
        return {};
    auto* env  = info.env;
    auto local = env->CallStaticObjectMethod(info.classID, info.methodID, jint(id));
    std::shared_ptr<MobileOutput> port;
    if (local && !env->ExceptionCheck())
    {
        auto caps = env->GetMethodID(info.classID, "capabilities", "()I");
        auto run  = env->GetMethodID(info.classID, "execute", "(I[J[I[F)I");
        auto stop = env->GetMethodID(info.classID, "stop", "()I");
        if (caps && run && stop)
        {
            int flags = env->CallIntMethod(local, caps);
            if (!env->ExceptionCheck())
                if (auto ref = env->NewGlobalRef(local))
                    port = queueMobileDriver(
                        {MobilePlatform::Android, bool(flags & 1), bool(flags & 2), bool(flags & 8), bool(flags & 4),
                         false, (flags & 16) ? "NotBuilt" : (flags & 32) ? "SystemTooOld" : "DeviceUnsupported"},
                        std::make_unique<AndroidDriver>(ref, run, stop));
        }
    }
    if (env->ExceptionCheck())
        env->ExceptionClear();
    env->DeleteLocalRef(local);
    env->DeleteLocalRef(info.classID);
    return port;
}
}  // namespace cc::haptics::detail
extern "C" {
JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosHaptics_nativePermitted(JNIEnv*, jclass)
{
    auto& gate = cc::haptics::detail::currentVibrationGate;
    return gate && gate->load();
}
JNIEXPORT void JNICALL Java_org_cocos_lib_CocosHaptics_nativeFocus(JNIEnv*, jclass, jboolean active)
{
    cc::haptics::detail::mobileFocus(active);
}
JNIEXPORT void JNICALL Java_org_cocos_lib_CocosHaptics_nativeRouting(JNIEnv*, jclass, jboolean forwarded)
{
    cc::haptics::detail::mobileForwarding(forwarded);
}
JNIEXPORT void JNICALL Java_org_cocos_lib_CocosHaptics_nativeVibrate(JNIEnv*, jclass, jfloat seconds)
{
    cc::haptics::detail::mobileVibrate(seconds);
}
}
