#include "../PlatformGamepadBackend.h"

#include "platform/android/jni/JniHelper.h"

#include <algorithm>
#include <map>
#include <mutex>

namespace cc::input::detail {
namespace {

constexpr auto backendId = std::uint64_t{0x414e};
constexpr auto javaBridge = "org/cocos/lib/CocosGamepads";
constexpr std::array buttonNames{"a", "b", "x", "y", "back", "guide", "start", "leftstick", "rightstick",
                                 "leftshoulder", "rightshoulder", "dpup", "dpdown", "dpleft", "dpright"};
constexpr std::array axisNames{"leftx", "lefty", "rightx", "righty", "lefttrigger", "righttrigger"};

struct Device {
    jint id;
    EndpointKey key;
    EndpointDescriptor descriptor;
    RawState state;
    std::uint64_t cursor = 0;
    bool claimed = false;

    AttachedEndpoint attachment() const { return {key, descriptor, {state, cursor, {}}}; }
};

struct Bridge {
    std::mutex mutex;
    std::map<jint, Device> devices;
    ReportSink* sink = nullptr;
    jlong host = 0;
    bool running = false;
    bool active = true;

    Device* find(jlong owner, jint id, jlong endpoint)
    {
        const auto found = devices.find(id);
        return running && owner == host && found != devices.end() && found->second.key.endpoint == static_cast<std::uint64_t>(endpoint)
            ? &found->second : nullptr;
    }

    Device* find(EndpointKey key)
    {
        const auto found = std::ranges::find_if(devices, [&](const auto& item) { return item.second.key == key; });
        return found == devices.end() ? nullptr : &found->second;
    }

    void detach(jint id)
    {
        const auto found = devices.find(id);
        if (found == devices.end())
            return;
        if (sink)
            sink->detached(found->second.key);
        devices.erase(found);
    }
};

Bridge& bridge()
{
    static Bridge value;
    return value;
}

ReportTime clock(jlong milliseconds)
{
    ReportTime result;
    if (milliseconds > 0)
    {
        result.sourceNs = static_cast<std::uint64_t>(milliseconds) * 1000000ULL;
        result.quality = TimeQuality::ConvertedOS;
    }
    return result;
}

std::string utf8(JNIEnv* env, jstring text)
{
    if (!text)
        return {};
    const char* bytes = env->GetStringUTFChars(text, nullptr);
    if (!bytes)
        return {};
    std::string value(bytes);
    env->ReleaseStringUTFChars(text, bytes);
    return value;
}

class AndroidBackend final : public GamepadBackend {
public:
    ~AndroidBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (b.sink) return Error::Busy;
        b.sink = _sink = &sink;
        b.active = true;
        for (auto& [id, device] : b.devices)
        {
            auto attached = device.attachment();
            sink.attached(attached.key, std::move(attached.descriptor), std::move(attached.initial));
        }
        return Error::None;
    }

    void stop() noexcept override
    {
        if (!_sink) return;
        setActive(false);
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (b.sink == _sink) b.sink = nullptr;
        for (auto& [id, device] : b.devices) device.claimed = false;
        _sink = nullptr;
    }

    void setActive(bool active) override
    {
        if (!_sink) return;
        auto& b = bridge();
        jlong host;
        {
            std::lock_guard lock(b.mutex);
            b.active = active;
            host = b.host;
        }
        JniHelper::callStaticBooleanMethod(javaBridge, "setActive", host, static_cast<jboolean>(active));
    }

    void requestBaseline(EndpointKey key) override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (auto* device = b.find(key); b.sink && device)
            b.sink->baseline(key, {device->state, device->cursor, {}});
    }

    void requestTopology() override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (!b.sink) return;
        std::vector<AttachedEndpoint> snapshot;
        for (auto& [id, device] : b.devices)
        {
            ++device.key.generation;
            device.claimed = false;
            snapshot.push_back(device.attachment());
        }
        b.sink->topology(std::move(snapshot));
    }

    void setClaimed(EndpointKey key, bool claimed) override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (auto* device = b.find(key))
            device->claimed = claimed;
    }

    Error setSensor(EndpointKey key, Sensor sensor, bool enabled) override
    {
        if (sensor != Sensor::Accel && sensor != Sensor::Gyro) return Error::Unsupported;
        auto& b = bridge();
        jlong host;
        jint id;
        {
            std::lock_guard lock(b.mutex);
            const auto* device = b.find(key);
            if (!device) return Error::Disconnected;
            if (!device->descriptor.capabilities.sensors.test(static_cast<unsigned>(sensor))) return Error::Unsupported;
            host = b.host;
            id = device->id;
        }
        return JniHelper::callStaticBooleanMethod(javaBridge, "setSensor", host, id, static_cast<jlong>(key.endpoint),
                    static_cast<jint>(sensor), static_cast<jboolean>(enabled))
            ? Error::None : Error::Disconnected;
    }

    Error submit(EndpointKey key, const NativeCommand& command) override
    {
        auto& b = bridge();
        jlong host;
        jint id;
        {
            std::lock_guard lock(b.mutex);
            auto* device = b.find(key);
            if (!device) return Error::Disconnected;
            host = b.host;
            id = device->id;
        }
        jint operation = 0, value = 0;
        jfloat amount = 0;
        if (const auto* rumble = std::get_if<Rumble>(&command.command))
        {
            value = static_cast<jint>(rumble->duration.count());
            amount = std::max(rumble->low, rumble->high);
        }
        else if (const auto* color = std::get_if<Rgb>(&command.command))
        {
            operation = 1;
            value = static_cast<jint>(0xff000000u | (static_cast<unsigned>(color->r) << 16) |
                (static_cast<unsigned>(color->g) << 8) | color->b);
        }
        else if (const auto* stop = std::get_if<Stop>(&command.command))
        {
            if (stop->channel == Channel::Lights) operation = 2;
            else if (stop->channel == Channel::All) operation = 3;
            else if (stop->channel != Channel::Body) return Error::Unsupported;
        }
        else
            return Error::Unsupported;
        return JniHelper::callStaticBooleanMethod(javaBridge, "queueOutput", host, id, static_cast<jlong>(key.endpoint),
                    static_cast<jlong>(key.generation), static_cast<jlong>(command.id), operation, value, amount)
            ? Error::None : Error::Disconnected;
    }

private:
    ReportSink* _sink = nullptr;
};

} // namespace

std::unique_ptr<GamepadBackend> makeAndroidGamepadBackend() { return std::make_unique<AndroidBackend>(); }

} // namespace cc::input::detail

using namespace cc::input;
using namespace cc::input::detail;

extern "C" {
JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeHost(JNIEnv*, jclass, jlong host, jboolean started)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if ((started && host <= b.host) || (!started && host != b.host)) return;
    while (!b.devices.empty())
        b.detach(b.devices.begin()->first);
    b.host = host;
    b.running = started;
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeAttach(
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jstring name, jint vendor, jint product, jint buttons,
    jint axes, jboolean feedback, jint additional)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if (!b.running || host != b.host) return;
    b.detach(id);
    Device device{};
    device.id = id;
    device.key = {backendId, static_cast<std::uint64_t>(endpoint), 1};
    auto& descriptor = device.descriptor;
    descriptor.name = utf8(env, name);
    if (descriptor.name.empty()) descriptor.name = "Android Gamepad";
    if (vendor > 0 && vendor <= 65535) descriptor.vendor = static_cast<std::uint16_t>(vendor);
    if (product > 0 && product <= 65535) descriptor.product = static_cast<std::uint16_t>(product);
    descriptor.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble), feedback);
    descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Accel), (additional & 1) != 0);
    descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Gyro), (additional & 2) != 0);
    descriptor.capabilities.features.set(static_cast<unsigned>(Feature::RgbLed), (additional & 4) != 0);
    auto& layout = descriptor.layout;
    layout.id = "android-physical-v1/" + std::to_string(buttons) + "/" + std::to_string(axes);
    layout.buttonCount = buttonNames.size();
    layout.axisCount = axisNames.size();
    device.state.buttons.resize(buttonNames.size());
    device.state.axes.resize(axisNames.size());
    const auto describe = [&](auto names, auto mask, const char* prefix, auto& present) {
        for (unsigned i = 0; i < names.size(); ++i)
        {
            const bool available = (mask & (1 << i)) != 0;
            present.push_back(available);
            if (available)
                layout.builtInMapping += std::string(names[i]) + ":" + prefix + std::to_string(i) + ",";
        }
    };
    describe(buttonNames, buttons, "b", layout.buttonPresent);
    describe(axisNames, axes, "a", layout.axisPresent);
    device.state.axesKnown = layout.axisPresent;
    device.state.axes[4] = device.state.axes[5] = -32768;
    auto& inserted = b.devices.emplace(id, std::move(device)).first->second;
    if (b.sink)
    {
        auto attached = inserted.attachment();
        b.sink->attached(attached.key, std::move(attached.descriptor), std::move(attached.initial));
    }
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeDetach(JNIEnv*, jclass, jlong host, jint id, jlong endpoint)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if (b.find(host, id, endpoint))
        b.detach(id);
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosGamepads_nativeClaimed(JNIEnv*, jclass, jlong host, jint id, jlong endpoint)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    const auto* device = b.find(host, id, endpoint);
    return device && device->claimed;
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosGamepads_nativeKey(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jint index, jboolean down, jlong timestamp)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || index < 0 || static_cast<unsigned>(index) >= buttonNames.size()) return false;
    auto& value = device->state.buttons[index];
    if (value != down)
    {
        value = down;
        const std::array changes{RawChange{RawKind::Button, static_cast<unsigned>(index), value}};
        if (b.sink) b.sink->report(device->key, {changes, {}, {}, {}, ++device->cursor, clock(timestamp)});
    }
    return device->claimed;
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosGamepads_nativeMotion(
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jlongArray times, jshortArray input)
{
    if (!times || !input) return false;
    const auto count = env->GetArrayLength(times);
    constexpr unsigned stride = axisNames.size() + 2;
    if (count <= 0 || count > 1024 || env->GetArrayLength(input) != count * stride)
        return false;
    std::vector<jlong> timestamps(count);
    std::vector<jshort> values(count * stride);
    env->GetLongArrayRegion(times, 0, count, timestamps.data());
    env->GetShortArrayRegion(input, 0, static_cast<jsize>(values.size()), values.data());
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device) return false;
    std::array<RawChange, 10> changes{};
    for (unsigned row = 0; row < timestamps.size(); ++row)
    {
        unsigned size = 0;
        const auto* sample = values.data() + row * stride;
        for (unsigned i = 0; i < axisNames.size(); ++i)
            if (device->descriptor.layout.axisPresent[i] && device->state.axes[i] != sample[i])
            {
                device->state.axes[i] = sample[i];
                changes[size++] = {RawKind::Axis, i, sample[i]};
            }
        constexpr unsigned up = 11, down = 12, left = 13, right = 14;
        const auto direction = [&](unsigned index, bool pressed) {
            auto& previous = device->state.buttons[index];
            if (previous != pressed)
            {
                previous = pressed;
                changes[size++] = {RawKind::Button, index, previous};
            }
        };
        if (sample[6] != 2) { direction(left, sample[6] < 0); direction(right, sample[6] > 0); }
        if (sample[7] != 2) { direction(up, sample[7] < 0); direction(down, sample[7] > 0); }
        if (b.sink && size)
            b.sink->report(device->key, {std::span(changes).first(size), {}, {}, {}, ++device->cursor, clock(timestamps[row])});
    }
    return device->claimed;
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeSensor(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jint index, jlong timestamp, jfloat x, jfloat y, jfloat z)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || !b.sink || !b.active || index < 0 || index >= 2)
        return;
    const std::array motion{Motion{static_cast<Sensor>(index), {x, y, z},
        timestamp > 0 ? std::optional{static_cast<std::uint64_t>(timestamp)} : std::nullopt}};
    b.sink->report(device->key, {{}, {}, motion, {}, ++device->cursor, {}});
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeOutputDone(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jlong generation, jlong command, jint status)
{
    if (!command) return;
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if (auto* device = b.find(host, id, endpoint); device && b.sink &&
        device->key.generation == static_cast<std::uint64_t>(generation))
    {
        const auto error = status == 0 ? Error::None : status == 1 ? Error::Busy
            : status == 2 ? Error::PermissionDenied : Error::BackendFailure;
        b.sink->outputCompleted(device->key, static_cast<CommandId>(command), error);
    }
}
}
