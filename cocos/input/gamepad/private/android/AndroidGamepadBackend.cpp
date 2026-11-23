#include "../PlatformGamepadBackend.h"
#include "../drivers/SonyHidReports.h"
#include "../drivers/XboxBluetoothReports.h"
#include "../mapping/DeviceGuid.h"

#include "platform/android/jni/JniHelper.h"

#include <algorithm>
#include <deque>
#include <map>
#include <mutex>

namespace cc::input::detail {
namespace {

constexpr auto backendId = std::uint64_t{0x414e};
constexpr auto javaBridge = "org/cocos/lib/CocosGamepads";
constexpr std::array buttonNames{"a", "b", "x", "y", "back", "guide", "start", "leftstick", "rightstick",
                                 "leftshoulder", "rightshoulder", "dpup", "dpdown", "dpleft", "dpright"};
constexpr std::array axisNames{"leftx", "lefty", "rightx", "righty", "lefttrigger", "righttrigger"};
constexpr unsigned rawButtonCount = 36, maxAxes = 64;
constexpr auto usbTransport = DualSenseTransport::Usb;

struct UsbWrite {
    SonyHidOutput output;
    CommandId id{};
    std::uint64_t generation = 0;
};

struct UsbState {
    explicit UsbState(SonyHidModel model) : reports(model, usbTransport), output(model) {}

    SonyHidReports reports;
    std::bitset<SensorCount> sensors;
    SonyHidOutput output;
    std::deque<NativeCommand> pending;
    std::optional<UsbWrite> writing;
    bool neutral = true;
};

struct Device {
    jint id;
    EndpointKey key;
    EndpointDescriptor descriptor;
    RawState state;
    std::array<std::optional<Contact>, 2> fingers;
    std::unique_ptr<UsbState> usb;
    std::uint64_t cursor = 0;
    bool claimed = false;
    bool published = false;

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
        if (sink && found->second.published)
            sink->detached(found->second.key);
        devices.erase(found);
    }

    void publish(Device& device)
    {
        device.published = true;
        if (sink)
        {
            auto attached = device.attachment();
            sink->attached(attached.key, std::move(attached.descriptor), std::move(attached.initial));
        }
    }

    void cancelUsb(Device& device)
    {
        auto& usb = *device.usb;
        if (sink)
        {
            for (const auto& command : usb.pending)
                if (command.id != CommandId{}) sink->outputCompleted(device.key, command.id, Error::Busy);
            if (usb.writing && usb.writing->id != CommandId{} && usb.writing->generation == device.key.generation)
                sink->outputCompleted(device.key, usb.writing->id, Error::Busy);
        }
        if (usb.writing) usb.writing->id = {};
        usb.pending.clear();
        usb.neutral = true;
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

std::span<const std::uint8_t> readUsbFeature(JNIEnv* env, jbyteArray report,
                                             std::span<std::uint8_t> bytes)
{
    if (!report) return {};
    const auto size = env->GetArrayLength(report);
    if (size <= 0 || static_cast<std::size_t>(size) > bytes.size()) return {};
    env->GetByteArrayRegion(report, 0, size, reinterpret_cast<jbyte*>(bytes.data()));
    return bytes.first(static_cast<std::size_t>(size));
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
            if (!device.published) continue;
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
            if (!active)
                for (auto& [id, device] : b.devices)
                {
                    device.fingers = {};
                    if (device.usb) b.cancelUsb(device);
                }
            host = b.host;
        }
        JniHelper::callStaticBooleanMethod(javaBridge, "setActive", host, static_cast<jboolean>(active));
    }

    void requestBaseline(EndpointKey key) override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (auto* device = b.find(key); b.sink && device && device->published)
        {
            device->fingers = {};
            b.sink->baseline(key, {device->state, device->cursor, {}});
        }
    }

    void requestTopology() override
    {
        auto& b = bridge();
        std::lock_guard lock(b.mutex);
        if (!b.sink) return;
        std::vector<AttachedEndpoint> snapshot;
        for (auto& [id, device] : b.devices)
        {
            if (!device.published) continue;
            if (device.usb) b.cancelUsb(device);
            ++device.key.generation;
            device.claimed = false;
            device.fingers = {};
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
            auto* device = b.find(key);
            if (!device) return Error::Disconnected;
            if (!device->descriptor.capabilities.sensors.test(static_cast<unsigned>(sensor))) return Error::Unsupported;
            if (device->usb)
            {
                device->usb->sensors.set(static_cast<unsigned>(sensor), enabled);
                return Error::None;
            }
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
            if (device->usb)
            {
                auto& usb = *device->usb;
                if (!b.active && !std::holds_alternative<Stop>(command.command)) return Error::Busy;
                if (usb.pending.size() >= 32) return Error::Busy;
                usb.pending.push_back(command);
                return Error::None;
            }
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
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jstring name, jstring identity, jint vendor, jint product,
    jlong buttons, jint guidButtons, jint guidAxes, jstring axisLayout, jint axisCount, jintArray defaultAxes,
    jboolean feedback, jint additional)
{
    std::array<jint, axisNames.size()> axisIndices;
    if (axisCount < 0 || axisCount > static_cast<jint>(maxAxes) || !defaultAxes ||
        env->GetArrayLength(defaultAxes) != static_cast<jsize>(axisIndices.size()))
        return;
    env->GetIntArrayRegion(defaultAxes, 0, static_cast<jsize>(axisIndices.size()), axisIndices.data());
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
    if (descriptor.vendor && descriptor.product && isKnownXboxProduct(*descriptor.vendor, *descriptor.product))
        descriptor.controllerType = GamepadType::XboxCompatible;
    descriptor.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble), feedback);
    descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Accel), (additional & 1) != 0);
    descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Gyro), (additional & 2) != 0);
    descriptor.capabilities.features.set(static_cast<unsigned>(Feature::RgbLed), (additional & 4) != 0);
    if (additional & 8) descriptor.capabilities.fingersPerPad = {2};
    auto& layout = descriptor.layout;
    layout.id = "android-sdl-v2/" + std::to_string(buttons) + utf8(env, axisLayout);
    layout.guid = DeviceGuid::android(descriptor.vendor.value_or(0), descriptor.product.value_or(0), utf8(env, identity),
        static_cast<std::uint16_t>(guidButtons), static_cast<std::uint16_t>(guidAxes));
    layout.usesVersion = false;
    layout.buttonCount = rawButtonCount;
    layout.axisCount = static_cast<unsigned>(axisCount);
    device.state.buttons.resize(layout.buttonCount);
    device.state.axes.resize(layout.axisCount);
    device.state.axesKnown.resize(layout.axisCount);
    for (unsigned i = 0; i < layout.buttonCount; ++i)
    {
        const bool available = (static_cast<std::uint64_t>(buttons) & (std::uint64_t{1} << i)) != 0;
        layout.buttonPresent.push_back(available);
        if (available && i < buttonNames.size())
            layout.builtInMapping += std::string(buttonNames[i]) + ":b" + std::to_string(i) + ",";
    }
    for (unsigned i = 0; i < axisNames.size(); ++i)
    {
        const auto index = axisIndices[i];
        if (index >= 0 && index < axisCount)
            layout.builtInMapping += std::string(axisNames[i]) + ":a" + std::to_string(index) + ",";
        else if (i >= 4 && layout.buttonPresent[i + 11])
            layout.builtInMapping += std::string(axisNames[i]) + ":b" + std::to_string(i + 11) + ",";
    }
    auto& inserted = b.devices.emplace(id, std::move(device)).first->second;
    b.publish(inserted);
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
    if (!device || index < 0 || static_cast<unsigned>(index) >= device->state.buttons.size()) return false;
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
    const auto valueCount = env->GetArrayLength(input);
    if (count <= 0 || count > 1024 || valueCount < count * 2 || valueCount > count * static_cast<jsize>(maxAxes + 2))
        return false;
    std::vector<jlong> timestamps(count);
    std::vector<jshort> values(valueCount);
    env->GetLongArrayRegion(times, 0, count, timestamps.data());
    env->GetShortArrayRegion(input, 0, static_cast<jsize>(values.size()), values.data());
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device) return false;
    const auto axes = device->descriptor.layout.axisCount;
    const auto stride = axes + 2;
    if (values.size() != timestamps.size() * stride) return false;
    std::array<RawChange, maxAxes + 4> changes{};
    for (unsigned row = 0; row < timestamps.size(); ++row)
    {
        unsigned size = 0;
        const auto* sample = values.data() + row * stride;
        for (unsigned i = 0; i < axes; ++i)
            if (!device->state.axesKnown[i] || device->state.axes[i] != sample[i])
            {
                device->state.axes[i] = sample[i];
                device->state.axesKnown[i] = 1;
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
        if (sample[axes] != 2) { direction(left, sample[axes] < 0); direction(right, sample[axes] > 0); }
        if (sample[axes + 1] != 2) { direction(up, sample[axes + 1] < 0); direction(down, sample[axes + 1] > 0); }
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

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeSensorCapabilities(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jint mask)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device) return;
    auto& caps = device->descriptor.capabilities;
    const auto previous = caps.sensors;
    caps.sensors.set(static_cast<unsigned>(Sensor::Accel), (mask & 1) != 0);
    caps.sensors.set(static_cast<unsigned>(Sensor::Gyro), (mask & 2) != 0);
    if (b.sink && caps.sensors != previous) b.sink->capabilitiesChanged(device->key, caps);
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosGamepads_nativeTouch(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jint first, jfloat firstX, jfloat firstY,
    jint second, jfloat secondX, jfloat secondY, jboolean cancelled, jlong timestamp)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || !b.active || device->descriptor.capabilities.fingersPerPad.empty()) return;
    std::array<std::optional<Contact>, 2> current;
    if (!cancelled && first >= 0) current[0] = Contact{0, static_cast<unsigned>(first), ContactPhase::Move, firstX, firstY, {}};
    if (!cancelled && second >= 0) current[1] = Contact{0, static_cast<unsigned>(second), ContactPhase::Move, secondX, secondY, {}};
    auto changes = dualSenseTouchChanges(device->fingers, current);
    if (cancelled)
        for (auto& contact : changes) contact.phase = ContactPhase::Cancel;
    device->fingers = current;
    if (b.sink && !changes.empty())
        b.sink->report(device->key, {{}, changes, {}, {}, ++device->cursor, clock(timestamp)});
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

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeOpen(
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jint product,
    jbyteArray calibration, jbyteArray firmware)
{
    const auto model = sonyHidModel(0x054c, static_cast<unsigned>(product));
    if (!model) return false;
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if (!b.running || host != b.host || id >= 0 || b.devices.contains(id)) return false;
    Device device{};
    device.id = id;
    device.key = {backendId, static_cast<std::uint64_t>(endpoint), 1};
    device.usb = std::make_unique<UsbState>(*model);
    std::array<std::uint8_t, 64> bytes{};
    device.usb->reports.calibrate(readUsbFeature(env, calibration, bytes));
    device.usb->output.configureRumble(*model, usbTransport, decodeDualSenseFirmware(readUsbFeature(env, firmware, bytes)));
    auto& descriptor = device.descriptor;
    const bool ds4 = *model == SonyHidModel::DualShock4;
    descriptor.name = sonyHidName(*model);
    descriptor.controllerType = sonyGamepadType(*model);
    descriptor.vendor = 0x054c;
    descriptor.product = static_cast<std::uint16_t>(product);
    descriptor.link = Link::Wired;
    auto& caps = descriptor.capabilities;
    caps.fingersPerPad = {2};
    const bool motion = *model != SonyHidModel::DualSense || device.usb->reports.hasCalibration();
    caps.sensors.set(static_cast<unsigned>(Sensor::Accel), motion);
    caps.sensors.set(static_cast<unsigned>(Sensor::Gyro), motion);
    caps.features.set(static_cast<unsigned>(Feature::BodyRumble));
    caps.features.set(static_cast<unsigned>(Feature::RgbLed));
    if (!ds4)
    {
        for (auto feature : {Feature::PlayerLights, Feature::AdaptiveLeft, Feature::AdaptiveRight})
            caps.features.set(static_cast<unsigned>(feature));
        caps.playerLightMask = 31;
        caps.triggerLimits = {TriggerLimits{true, true, 1, 255}, TriggerLimits{true, true, 1, 255}};
    }
    auto& layout = descriptor.layout;
    layout.id = ds4 ? "android-dualshock4-usb-v1" : *model == SonyHidModel::DualSenseEdge ?
        "android-dualsense-edge-usb-v1" : "android-dualsense-usb-v1";
    layout.guid = DeviceGuid::make(3, *descriptor.vendor, *descriptor.product, 0, {}, descriptor.name, 'h');
    layout.legacyHidapi = true;
    configureSonyHidLayout(layout, *model);
    device.state.buttons.resize(layout.buttonCount);
    device.state.axes.resize(layout.axisCount);
    device.state.axesKnown.assign(layout.axisCount, 1);
    device.state.hats.resize(layout.hatCount);
    b.devices.emplace(id, std::move(device));
    return true;
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeRead(
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jbyteArray packet, jint length)
{
    std::array<std::uint8_t, 64> bytes;
    if (!packet || length <= 0 || static_cast<std::size_t>(length) > bytes.size() || length > env->GetArrayLength(packet))
        return false;
    env->GetByteArrayRegion(packet, 0, length, reinterpret_cast<jbyte*>(bytes.data()));
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || !device->usb) return false;
    const auto sample = device->usb->reports.decode(std::span(bytes).first(static_cast<std::size_t>(length)));
    if (!sample) return false;

    std::array<RawChange, DualSenseEdgeButtonCount + 7> changes{};
    unsigned count = 0;
    const auto update = [&](RawKind kind, auto& previous, unsigned index, auto value) {
        if (previous[index] != value)
        {
            previous[index] = value;
            changes[count++] = {kind, index, value};
        }
    };
    for (unsigned i = 0; i < device->state.buttons.size(); ++i)
        update(RawKind::Button, device->state.buttons, i, sample->buttons[i]);
    for (unsigned i = 0; i < sample->axes.size(); ++i)
        update(RawKind::Axis, device->state.axes, i, sample->axes[i]);
    update(RawKind::Hat, device->state.hats, 0, sample->hat);
    std::optional<Power> power;
    if (const auto& previous = device->descriptor.power;
        previous.state != sample->power.state || previous.percent != sample->power.percent)
    {
        power = sample->power;
        device->descriptor.power = *power;
    }
    if (!device->published)
    {
        b.publish(*device);
        count = 0;
        power.reset();
    }
    std::vector<Contact> contacts;
    std::array<Motion, 2> motion{};
    unsigned motionCount = 0;
    if (b.active)
    {
        if (sample->hasTouchSample)
        {
            contacts = dualSenseTouchChanges(device->fingers, sample->fingers);
            device->fingers = sample->fingers;
        }
        for (const auto& value : sample->motion)
            if (device->usb->sensors.test(static_cast<unsigned>(value.sensor))) motion[motionCount++] = value;
    }
    if (b.sink && (count || !contacts.empty() || motionCount || power))
        b.sink->report(device->key, {std::span(changes).first(count), contacts,
            std::span(motion).first(motionCount), power, ++device->cursor, {}});
    return true;
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeNextOutput(
    JNIEnv* env, jclass, jlong host, jint id, jlong endpoint, jbyteArray packet)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || !device->usb || device->usb->writing) return false;
    auto& usb = *device->usb;
    UsbWrite write{usb.output, {}, device->key.generation};
    if (usb.neutral)
    {
        write.output.apply(Stop{}, nowNs());
        usb.neutral = false;
    }
    else if (!usb.pending.empty())
    {
        const auto command = usb.pending.front();
        usb.pending.pop_front();
        write.id = command.id;
        if (!write.output.apply(command.command, nowNs()))
        {
            if (b.sink && command.id != CommandId{})
                b.sink->outputCompleted(device->key, command.id, Error::InvalidArgument);
            return false;
        }
    }
    else if (!write.output.expire(nowNs())) return false;
    const auto bytes = write.output.encode(usbTransport);
    if (bytes.empty() || !packet || bytes.size() != static_cast<std::size_t>(env->GetArrayLength(packet)))
        return false;
    env->SetByteArrayRegion(packet, 0, static_cast<jsize>(bytes.size()), reinterpret_cast<const jbyte*>(bytes.data()));
    usb.writing = std::move(write);
    return true;
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeOutputDone(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint, jboolean success)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    auto* device = b.find(host, id, endpoint);
    if (!device || !device->usb || !device->usb->writing) return;
    auto& usb = *device->usb;
    if (success) usb.output = usb.writing->output;
    if (b.sink && usb.writing->id != CommandId{} && usb.writing->generation == device->key.generation)
        b.sink->outputCompleted(device->key, usb.writing->id, success ? Error::None : Error::BackendFailure);
    usb.writing.reset();
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeClose(
    JNIEnv*, jclass, jlong host, jint id, jlong endpoint)
{
    auto& b = bridge();
    std::lock_guard lock(b.mutex);
    if (b.find(host, id, endpoint)) b.detach(id);
}

JNIEXPORT jboolean JNICALL Java_org_cocos_lib_CocosSonyGamepadUsb_nativeNeutral(
    JNIEnv* env, jclass, jint product, jbyteArray packet)
{
    const auto model = sonyHidModel(0x054c, static_cast<unsigned>(product));
    if (!model || !packet) return false;
    SonyHidOutput output(*model);
    output.apply(Stop{}, nowNs());
    const auto bytes = output.encode(usbTransport);
    if (bytes.empty() || bytes.size() != static_cast<std::size_t>(env->GetArrayLength(packet))) return false;
    env->SetByteArrayRegion(packet, 0, static_cast<jsize>(bytes.size()), reinterpret_cast<const jbyte*>(bytes.data()));
    return true;
}
}
