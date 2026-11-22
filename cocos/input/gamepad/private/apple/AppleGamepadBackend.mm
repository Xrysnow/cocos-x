#include "../PlatformGamepadBackend.h"

#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#import <CoreHaptics/CoreHaptics.h>
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#import <IOKit/hid/IOHIDManager.h>
#import <IOKit/hid/IOHIDUsageTables.h>
#endif

#include <algorithm>
#include <cmath>
#include <map>
#include <tuple>

namespace cc::input::detail {
namespace {

constexpr auto appleId = std::uint64_t{0x4743};
constexpr float gravity = 9.80665f;
constexpr auto touchpadClick = static_cast<unsigned>(Button::TouchpadClick);
constexpr std::array buttonNames{
    "a", "b", "x", "y", "back", "guide", "start", "leftstick", "rightstick", "leftshoulder", "rightshoulder",
    "dpup", "dpdown", "dpleft", "dpright", "misc1", "paddle1", "paddle2", "paddle3", "paddle4", "touchpad",
    "misc2", "misc3", "misc4", "misc5", "misc6"
};
constexpr std::array axisNames{"leftx", "lefty", "rightx", "righty", "lefttrigger", "righttrigger"};

std::int16_t signedAxis(float value)
{
    return static_cast<std::int16_t>(std::lround(std::clamp(value, -1.f, 1.f) * (value < 0 ? 32768.f : 32767.f)));
}

bool isMfiAlias(NSString* name, NSDictionary<NSString*, GCControllerElement*>* elements, bool joyConPair)
{
    if (joyConPair && [name isEqualToString:@"Button Home"])
        return true;
    for (NSString* prefix in @[@"Left Thumbstick ", @"Right Thumbstick ", @"Direction Pad ", @"Cardinal Direction Pad ",
                               @"Touchpad 1 ", @"Touchpad 2 "])
    {
        if (![name hasPrefix:prefix]) continue;
        NSString* part = [name substringFromIndex:prefix.length];
        const bool x = [part isEqualToString:@"X Axis"], y = [part isEqualToString:@"Y Axis"];
        const bool horizontal = [part isEqualToString:@"Left"] || [part isEqualToString:@"Right"];
        const bool vertical = [part isEqualToString:@"Up"] || [part isEqualToString:@"Down"];
        if ([prefix hasPrefix:@"Touchpad"])
            return x || y || horizontal || vertical;
        const auto has = [&](NSString* suffix) { return elements[[prefix stringByAppendingString:suffix]] != nil; };
        if ([prefix hasSuffix:@"Thumbstick "])
            return (horizontal && has(@"X Axis")) || (vertical && has(@"Y Axis"));
        return (x && has(@"Left") && has(@"Right")) || (y && has(@"Up") && has(@"Down"));
    }
    return false;
}

struct Device {
    GCController* controller;
    std::array<GCControllerButtonInput*, ButtonCount> buttons{};
    std::array<GCControllerAxisInput*, 4> sticks{};
    std::array<GCControllerButtonInput*, 2> triggers{};
    std::array<NSString*, ButtonCount> extraButtonNames{};
    std::array<GCControllerDirectionPad*, 2> touchpads{};
    std::array<GCControllerDirectionPadValueChangedHandler, 2> originalTouchHandlers{};
    std::array<std::optional<Contact>, 2> contacts{};
    GCControllerButtonValueChangedHandler originalTouchpadClickHandler = nil;
    bool usesLegacyTouchpadClick = false;
    std::array<CHHapticEngine*, 2> engines{};
    std::array<id<CHHapticPatternPlayer>, 2> players{};
    std::array<GCHapticsLocality, 2> haptics{};
    dispatch_queue_t originalQueue;
    dispatch_queue_t originalPhysicalQueue = nil;
    NSInteger originalStateQueueDepth = 1;
    bool buffered = false;
    EndpointKey key;
    EndpointDescriptor descriptor;
    RawState raw;
    std::vector<RawChange> changes;
    std::bitset<SensorCount> sensors;
    std::uint64_t cursor = 0;

    Device(GCController* controller, EndpointKey key) : controller(controller), originalQueue(controller.handlerQueue), key(key)
    {
        auto pad = controller.extendedGamepad;
        auto micro = controller.microGamepad;
        const auto bind = [&](Button name, GCControllerButtonInput* input) { buttons[static_cast<unsigned>(name)] = input; };
        const auto bindTouchpad = [&](GCControllerButtonInput* click, GCControllerDirectionPad* primary,
                                      GCControllerDirectionPad* secondary) {
            bind(Button::TouchpadClick, click);
            if (primary && secondary)
            {
                touchpads = {primary, secondary};
                descriptor.capabilities.fingersPerPad = {static_cast<unsigned>(touchpads.size())};
            }
        };
        bind(Button::South, pad ? pad.buttonA : micro.buttonA);
        bind(Button::East, pad.buttonB);
        bind(Button::West, pad ? pad.buttonX : micro.buttonX);
        bind(Button::North, pad.buttonY);
        auto dpad = pad ? pad.dpad : micro.dpad;
        bind(Button::DpadUp, dpad.up);
        bind(Button::DpadDown, dpad.down);
        bind(Button::DpadLeft, dpad.left);
        bind(Button::DpadRight, dpad.right);
        bind(Button::LeftShoulder, pad.leftShoulder);
        bind(Button::RightShoulder, pad.rightShoulder);
        if (@available(macOS 10.15, iOS 13.0, tvOS 13.0, *))
        {
            bind(Button::Start, pad ? pad.buttonMenu : micro.buttonMenu);
            bind(Button::LeftStick, pad.leftThumbstickButton);
            bind(Button::RightStick, pad.rightThumbstickButton);
            if ([pad isKindOfClass:GCDualShockGamepad.class])
            {
                auto dual = (GCDualShockGamepad*)pad;
                bindTouchpad(dual.touchpadButton, dual.touchpadPrimary, dual.touchpadSecondary);
            }
        }
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
        {
            bind(Button::Back, pad.buttonOptions);
            bind(Button::Guide, pad.buttonHome);
            if (controller.motion.hasRotationRate)
                descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Gyro));
            if (controller.motion.hasGravityAndUserAcceleration)
                descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Accel));
            if (controller.light)
                descriptor.capabilities.features.set(static_cast<unsigned>(Feature::RgbLed));
            auto localities = controller.haptics.supportedLocalities;
            if ([localities containsObject:GCHapticsLocalityLeftHandle] && [localities containsObject:GCHapticsLocalityRightHandle])
                haptics = {GCHapticsLocalityLeftHandle, GCHapticsLocalityRightHandle};
            else if ([localities containsObject:GCHapticsLocalityDefault])
                haptics[0] = GCHapticsLocalityDefault;
            if (haptics[0])
                descriptor.capabilities.features.set(static_cast<unsigned>(Feature::BodyRumble));
        }
        if (@available(macOS 11.3, iOS 14.5, tvOS 14.5, *))
        {
            if ([pad isKindOfClass:GCDualSenseGamepad.class])
            {
                auto dual = (GCDualSenseGamepad*)pad;
                bindTouchpad(dual.touchpadButton, dual.touchpadPrimary, dual.touchpadSecondary);
                // DualSense reports total acceleration without separating gravity and user motion.
                if (controller.motion)
                    descriptor.capabilities.sensors.set(static_cast<unsigned>(Sensor::Accel));
                for (auto feature : {Feature::AdaptiveLeft, Feature::AdaptiveRight})
                    descriptor.capabilities.features.set(static_cast<unsigned>(feature));
                descriptor.capabilities.triggerLimits = {TriggerLimits{true, false}, TriggerLimits{true, false}};
            }
        }
        sticks = {pad.leftThumbstick.xAxis, pad.leftThumbstick.yAxis, pad.rightThumbstick.xAxis, pad.rightThumbstick.yAxis};
        triggers = {pad.leftTrigger, pad.rightTrigger};
        const auto* vendor = controller.vendorName.UTF8String;
        descriptor.name = vendor ? vendor : "Apple Game Controller";
        auto& layout = descriptor.layout;
        layout.id = pad ? "apple-gc-extended-v1" : "apple-gc-micro-v1";
        layout.buttonCount = ButtonCount;
        layout.axisCount = AxisCount;
        layout.buttonPresent.resize(ButtonCount);
        layout.axisPresent.resize(AxisCount);
        const auto map = [&](auto& presence, unsigned i, bool available, const char* logical, const char* kind) {
            presence[i] = available;
            if (available)
                layout.builtInMapping += std::string(logical) + ":" + kind + std::to_string(i) + ",";
        };
        for (unsigned i = 0; i < buttons.size(); ++i)
            map(layout.buttonPresent, i, buttons[i] != nil, buttonNames[i], "b");
        for (unsigned i = 0; i < axisNames.size(); ++i)
            map(layout.axisPresent, i, i < sticks.size() ? sticks[i] != nil : triggers[i - sticks.size()] != nil,
                axisNames[i], "a");
        if (pad) configureMfi();
        raw.buttons.resize(layout.buttonCount);
        raw.axes.resize(AxisCount);
        raw.axesKnown = layout.axisPresent;
        sample();
        if (auto value = power())
            descriptor.power = *value;
    }

    void configureMfi()
    {
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
        {
            auto profile = controller.physicalInputProfile;
            auto elements = profile.elements;
            auto category = controller.productCategory;
            const bool joyConPair = [category isEqualToString:@"Nintendo Switch Joy-Con (L/R)"];
            std::uint16_t vendor = 0x05ac, product = 4;
            NSString* name = controller.vendorName ?: (category ?: @"MFi Gamepad");
            const bool dualSenseEdge = [category isEqualToString:@"DualSense Edge"] ||
                [name hasPrefix:@"DualSense Edge"];
            if ([name hasPrefix:@"Backbone One"])
            {
                vendor = 0x358a;
                product = [category isEqualToString:@"DualSense"] ? 0x0104 : 0x0103;
            }
            else if (dualSenseEdge || [category isEqualToString:@"DualShock 4"] || [category isEqualToString:@"DualSense"])
            {
                vendor = 0x054c;
                product = dualSenseEdge ? 0x0df2 : [category isEqualToString:@"DualSense"] ? 0x0ce6 : 0x09cc;
            }
            else if ([category isEqualToString:@"Xbox One"])
            {
                vendor = 0x045e;
                if (profile.buttons[GCInputXboxPaddleOne]) { product = 0x0b05; name = @"Xbox One Elite 2 Controller"; }
                else if (profile.buttons[@"Button Share"]) { product = 0x0b13; name = @"Xbox Series X Controller"; }
                else { product = 0x02e0; name = @"Xbox One Wireless Controller"; }
            }
            else if ([category hasPrefix:@"Nintendo Switch Joy-Con"] || [category isEqualToString:@"Switch Pro Controller"])
            {
                vendor = 0x057e;
                product = [category hasSuffix:@"(L)"] ? 0x2006 : [category hasSuffix:@"(R)"] ? 0x2007 :
                          joyConPair ? 0x2008 : 0x2009;
            }

            auto& layout = descriptor.layout;
            const auto extra = [&](Button button, NSString* key) {
                const auto index = static_cast<unsigned>(button);
                if (auto input = profile.buttons[key]; !buttons[index] && input)
                {
                    buttons[index] = input;
                    extraButtonNames[index] = key;
                    layout.buttonPresent[index] = 1;
                    layout.builtInMapping += std::string(buttonNames[index]) + ":b" + std::to_string(index) + ',';
                }
            };
            if (vendor == 0x054c)
                extra(Button::TouchpadClick, GCInputDualShockTouchpadButton);
#if (__MAC_OS_X_VERSION_MAX_ALLOWED >= 140400) || (__IPHONE_OS_VERSION_MAX_ALLOWED >= 170400) || \
    (__TV_OS_VERSION_MAX_ALLOWED >= 170400) || (__VISION_OS_VERSION_MAX_ALLOWED >= 10100)
            if (dualSenseEdge)
                if (@available(macOS 14.4, iOS 17.4, tvOS 17.4, visionOS 1.1, *))
                {
                    extra(Button::LeftPaddle1, GCInputBackLeftButton(0));
                    extra(Button::RightPaddle1, GCInputBackRightButton(0));
                }
#endif
            if (vendor == 0x045e)
            {
                extra(Button::Misc1, @"Button Share");
                extra(Button::RightPaddle1, GCInputXboxPaddleOne);
                extra(Button::LeftPaddle1, GCInputXboxPaddleTwo);
                extra(Button::RightPaddle2, GCInputXboxPaddleThree);
                extra(Button::LeftPaddle2, GCInputXboxPaddleFour);
            }

            SdlInputIndices indices;
            std::vector<std::string> axisKeys, buttonKeys;
            for (NSString* key in [[elements allKeys] sortedArrayUsingSelector:@selector(caseInsensitiveCompare:)])
            {
                if (isMfiAlias(key, elements, joyConPair)) continue;
                auto control = elements[key];
                const bool isButton = [control isKindOfClass:GCControllerButtonInput.class];
                const auto trigger = std::find(triggers.begin(), triggers.end(), control);
                const bool isTrigger = trigger != triggers.end();
                if (isButton)
                {
                    buttonKeys.emplace_back(key.UTF8String);
                    const auto native = std::find(buttons.begin(), buttons.end(), control);
                    if (native != buttons.end())
                        indices.buttons.emplace_back(static_cast<unsigned>(native - buttons.begin()));
                    else if (isTrigger)
                        indices.buttons.emplace_back(ButtonCount + static_cast<unsigned>(trigger - triggers.begin()));
                    else
                        indices.buttons.emplace_back(std::nullopt);
                }
                if (control.analog && (isButton || [control isKindOfClass:GCControllerAxisInput.class]))
                {
                    axisKeys.emplace_back(key.UTF8String);
                    const auto stick = std::find(sticks.begin(), sticks.end(), control);
                    if (stick != sticks.end())
                    {
                        const auto index = static_cast<unsigned>(stick - sticks.begin());
                        indices.axes.emplace_back(SdlAxisIndex{index, index % 2 ? AxisEncoding::Inverted : AxisEncoding::Signed});
                    }
                    else if (isTrigger)
                        indices.axes.emplace_back(SdlAxisIndex{4 + static_cast<unsigned>(trigger - triggers.begin()),
                            AxisEncoding::PositiveHalf});
                    else
                        indices.axes.emplace_back(std::nullopt);
                }
            }
            if (indices.buttons.empty() && indices.axes.empty()) return;
            auto signature = DeviceGuid::nameChecksum(0, name.UTF8String);
            for (const auto& key : axisKeys) signature = DeviceGuid::nameChecksum(signature, key);
            for (const auto& key : buttonKeys) signature = DeviceGuid::nameChecksum(signature, key);
            layout.guid = DeviceGuid::make(5, vendor, product, signature, {}, name.UTF8String, 'm', 4);
            layout.sdlIndices = std::move(indices);
            layout.buttonCount += static_cast<unsigned>(triggers.size());
            for (const auto& trigger : triggers) layout.buttonPresent.push_back(trigger != nil);
        }
    }

    void sample(id snapshot = nil)
    {
        changes.clear();
        const auto set = [&](RawKind type, auto& values, unsigned index, auto value) {
            if (values[index] != value)
            {
                values[index] = value;
                changes.push_back({type, index, value});
            }
        };
        if (@available(macOS 14.0, iOS 17.0, tvOS 17.0, *))
            if (id<GCDevicePhysicalInputState> capture = snapshot)
            {
                const std::array<GCInputButtonName, ButtonCount> names{
                    GCInputButtonA, GCInputButtonB, GCInputButtonX, GCInputButtonY,
                    GCInputButtonOptions, GCInputButtonHome, GCInputButtonMenu, GCInputLeftThumbstickButton,
                    GCInputRightThumbstickButton, GCInputLeftShoulder, GCInputRightShoulder
                };
                const auto digital = [&](unsigned i, id<GCPressedStateInput> input) {
                    if (buttons[i]) set(RawKind::Button, raw.buttons, i, static_cast<std::uint8_t>(input.pressed));
                };
                for (unsigned i = 0; i < names.size(); ++i)
                {
                    if (i == touchpadClick) continue;
                    if (GCInputButtonName name = names[i] ?: (GCInputButtonName)extraButtonNames[i])
                        digital(i, capture.buttons[name].pressedInput);
                }
                auto dp = capture.dpads[GCInputDirectionPad];
                digital(static_cast<unsigned>(Button::DpadUp), dp.up);
                digital(static_cast<unsigned>(Button::DpadDown), dp.down);
                digital(static_cast<unsigned>(Button::DpadLeft), dp.left);
                digital(static_cast<unsigned>(Button::DpadRight), dp.right);
                if (!usesLegacyTouchpadClick)
                    if (auto click = capture.buttons[GCInputDualShockTouchpadButton])
                        digital(touchpadClick, click.pressedInput);
                auto left = capture.dpads[GCInputLeftThumbstick];
                auto right = capture.dpads[GCInputRightThumbstick];
                const std::array analog{left.xAxis.value, -left.yAxis.value, right.xAxis.value, -right.yAxis.value};
                for (unsigned i = 0; i < analog.size(); ++i)
                    if (sticks[i]) set(RawKind::Axis, raw.axes, i, signedAxis(analog[i]));
                const std::array pressure{capture.buttons[GCInputLeftTrigger].pressedInput.value,
                                          capture.buttons[GCInputRightTrigger].pressedInput.value};
                for (unsigned i = 0; i < pressure.size(); ++i)
                    if (triggers[i])
                        set(RawKind::Axis, raw.axes, i + 4,
                            static_cast<std::int16_t>(std::lround(std::clamp(pressure[i], 0.f, 1.f) * 65535.f) - 32768));
                if (descriptor.layout.sdlIndices)
                {
                    set(RawKind::Button, raw.buttons, ButtonCount,
                        static_cast<std::uint8_t>(capture.buttons[GCInputLeftTrigger].pressedInput.pressed));
                    set(RawKind::Button, raw.buttons, ButtonCount + 1,
                        static_cast<std::uint8_t>(capture.buttons[GCInputRightTrigger].pressedInput.pressed));
                }
                return;
            }
        for (unsigned i = 0; i < buttons.size(); ++i)
            set(RawKind::Button, raw.buttons, i, static_cast<std::uint8_t>(buttons[i].pressed));
        for (unsigned i = 0; i < sticks.size(); ++i)
            set(RawKind::Axis, raw.axes, i, signedAxis(sticks[i].value * (i % 2 ? -1.f : 1.f)));
        for (unsigned i = 0; i < triggers.size(); ++i)
            if (triggers[i])
            {
                set(RawKind::Axis, raw.axes, i + 4,
                    static_cast<std::int16_t>(std::lround(std::clamp(triggers[i].value, 0.f, 1.f) * 65535.f) - 32768));
                if (descriptor.layout.sdlIndices)
                    set(RawKind::Button, raw.buttons, ButtonCount + i, static_cast<std::uint8_t>(triggers[i].pressed));
            }
    }

    std::optional<Power> power() const
    {
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
            if (auto battery = controller.battery; battery && battery.batteryLevel >= 0)
            {
                auto state = Power::State::Unknown;
                if (battery.batteryState == GCDeviceBatteryStateDischarging) state = Power::State::OnBattery;
                else if (battery.batteryState == GCDeviceBatteryStateCharging) state = Power::State::Charging;
                else if (battery.batteryState == GCDeviceBatteryStateFull) state = Power::State::Charged;
                return Power{state, static_cast<unsigned>(std::lround(std::min(battery.batteryLevel, 1.f) * 100)), {}};
            }
        return {};
    }

    void activateSensors(bool active)
    {
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
            if (controller.motion.sensorsRequireManualActivation)
                controller.motion.sensorsActive = active && sensors.any();
    }

    void stopRumble(bool release)
    {
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
            for (unsigned i = 0; i < players.size(); ++i)
            {
                [players[i] stopAtTime:0 error:nil];
                players[i] = nil;
                if (release)
                {
                    [engines[i] stopWithCompletionHandler:nil];
                    engines[i] = nil;
                }
            }
    }

    Error output(const OutputCommand& command)
    {
        if (@available(macOS 11.3, iOS 14.5, tvOS 14.5, *))
            if ([controller.extendedGamepad isKindOfClass:GCDualSenseGamepad.class])
            {
                auto dual = (GCDualSenseGamepad*)controller.extendedGamepad;
                if (const auto* t = std::get_if<AdaptiveTrigger>(&command))
                {
                    auto trigger = t->side == Side::Left ? dual.leftTrigger : dual.rightTrigger;
                    if (t->mode == TriggerMode::Off) [trigger setModeOff];
                    else if (t->mode == TriggerMode::Resistance)
                        [trigger setModeFeedbackWithStartPosition:t->start resistiveStrength:t->strength];
                    else return Error::Unsupported;
                    return Error::None;
                }
                if (const auto* s = std::get_if<Stop>(&command))
                {
                    if (s->channel == Channel::All || s->channel == Channel::AdaptiveLeft) [dual.leftTrigger setModeOff];
                    if (s->channel == Channel::All || s->channel == Channel::AdaptiveRight) [dual.rightTrigger setModeOff];
                }
            }
        if (const auto* stop = std::get_if<Stop>(&command))
        {
            if (stop->channel == Channel::All || stop->channel == Channel::Body) stopRumble(false);
            if (stop->channel == Channel::All || stop->channel == Channel::Lights)
                output(Rgb{});
            return Error::None;
        }
        if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
        {
            if (const auto* color = std::get_if<Rgb>(&command); color && controller.light)
            {
                controller.light.color = [[GCColor alloc] initWithRed:color->r / 255.f green:color->g / 255.f blue:color->b / 255.f];
                return Error::None;
            }
            if (const auto* rumble = std::get_if<Rumble>(&command); rumble && haptics[0])
            {
                stopRumble(false);
                if (rumble->duration.count() == 0)
                    return Error::None;
                const std::array values{haptics[1] ? rumble->low : std::max(rumble->low, rumble->high), rumble->high};
                for (unsigned i = 0; i < haptics.size(); ++i)
                {
                    if (!haptics[i] || values[i] == 0)
                        continue;
                    auto engine = engines[i];
                    if (!engine)
                        engine = engines[i] = [controller.haptics createEngineWithLocality:haptics[i]];
                    if (!engine || ![engine startAndReturnError:nil])
                    {
                        stopRumble(true);
                        return Error::BackendFailure;
                    }
                    auto intensity = [[CHHapticEventParameter alloc] initWithParameterID:CHHapticEventParameterIDHapticIntensity value:values[i]];
                    auto event = [[CHHapticEvent alloc] initWithEventType:CHHapticEventTypeHapticContinuous
                        parameters:@[intensity] relativeTime:0 duration:rumble->duration.count() / 1000.0];
                    auto pattern = [[CHHapticPattern alloc] initWithEvents:@[event] parameters:@[] error:nil];
                    players[i] = pattern ? [engine createPlayerWithPattern:pattern error:nil] : nil;
                    if (![players[i] startAtTime:0 error:nil])
                    {
                        stopRumble(true);
                        return Error::BackendFailure;
                    }
                }
                return Error::None;
            }
        }
        return Error::Unsupported;
    }

    void clear()
    {
        for (unsigned i = 0; i < touchpads.size(); ++i)
            touchpads[i].valueChangedHandler = originalTouchHandlers[i];
        if (usesLegacyTouchpadClick)
            buttons[touchpadClick].pressedChangedHandler = originalTouchpadClickHandler;
        if (@available(macOS 14.0, iOS 17.0, tvOS 17.0, *))
            if (buffered)
            {
                id<GCDevicePhysicalInput> input = (id<GCDevicePhysicalInput>)controller.input;
                input.inputStateAvailableHandler = nil;
                input.inputStateQueueDepth = originalStateQueueDepth;
                input.queue = originalPhysicalQueue;
            }
        controller.extendedGamepad.valueChangedHandler = nil;
        controller.microGamepad.valueChangedHandler = nil;
        controller.motion.valueChangedHandler = nil;
        controller.handlerQueue = originalQueue;
        activateSensors(false);
        output(Stop{});
        stopRumble(true);
    }
};

using Identity = void*;
Identity identity(GCController* controller) { return (__bridge void*)controller; }

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
std::optional<RawKind> hidKind(unsigned page, unsigned usage)
{
    if (page == kHIDPage_Button || page == kHIDPage_Consumer)
        return RawKind::Button;
    if (page == kHIDPage_GenericDesktop)
    {
        if (usage >= kHIDUsage_GD_X && usage <= kHIDUsage_GD_Wheel) return RawKind::Axis;
        if (usage == kHIDUsage_GD_Hatswitch) return RawKind::Hat;
        if ((usage >= kHIDUsage_GD_DPadUp && usage <= kHIDUsage_GD_DPadLeft) || usage == kHIDUsage_GD_Start ||
            usage == kHIDUsage_GD_Select || usage == kHIDUsage_GD_SystemMainMenu) return RawKind::Button;
    }
    if (page == kHIDPage_Simulation && (usage == kHIDUsage_Sim_Rudder || usage == kHIDUsage_Sim_Throttle ||
        usage == kHIDUsage_Sim_Accelerator || usage == kHIDUsage_Sim_Brake))
        return RawKind::Axis;
    return {};
}

struct HidDevice {
    struct Control {
        IOHIDElementRef element;
        RawKind kind;
        unsigned index;
    };
    EndpointKey key;
    EndpointDescriptor descriptor;
    RawState raw;
    std::shared_ptr<const void> elements;
    std::map<IOHIDElementCookie, Control> controls;
    std::uint64_t cursor = 0;

    static std::optional<HidDevice> open(IOHIDDeviceRef device, EndpointKey key)
    {
        // The platform identifies devices that GameController owns, even if
        // its connect notification arrives after IOHIDManager's notification.
        if (@available(macOS 11.0, *))
            if ([GCController supportsHIDDevice:device]) return {};
        auto elements = IOHIDDeviceCopyMatchingElements(device, nullptr, kIOHIDOptionsTypeNone);
        if (!elements) return {};
        std::vector<Control> sorted;
        for (CFIndex i = 0; i < CFArrayGetCount(elements); ++i)
        {
            auto element = (IOHIDElementRef)CFArrayGetValueAtIndex(elements, i);
            const auto type = IOHIDElementGetType(element);
            if (type != kIOHIDElementTypeInput_Button && type != kIOHIDElementTypeInput_Axis &&
                type != kIOHIDElementTypeInput_Misc)
                continue;
            const auto page = IOHIDElementGetUsagePage(element);
            const auto usage = IOHIDElementGetUsage(element);
            if (const auto kind = hidKind(page, usage))
                sorted.push_back({element, *kind, 0});
        }
        std::ranges::sort(sorted, {}, [](const Control& x) {
            return std::tuple{x.kind, IOHIDElementGetUsage(x.element), IOHIDElementGetCookie(x.element)};
        });
        HidDevice result{};
        result.key = key;
        result.elements = std::shared_ptr<const void>(elements, CFRelease);
        auto& descriptor = result.descriptor;
        auto& layout = descriptor.layout;
        layout.id = "macos-iohid-v1";
        const std::array counts{&layout.buttonCount, &layout.axisCount, &layout.hatCount};
        bool uniqueOrder = true;
        std::optional<std::pair<RawKind, unsigned>> previous;
        for (auto control : sorted)
        {
            control.index = *counts[static_cast<unsigned>(control.kind)];
            if (result.controls.emplace(IOHIDElementGetCookie(control.element), control).second)
            {
                const auto usage = IOHIDElementGetUsage(control.element);
                const auto next = std::pair{control.kind, usage};
                uniqueOrder &= previous != next;
                previous = next;
                ++*counts[static_cast<unsigned>(control.kind)];
                layout.id += "/" + std::to_string(static_cast<unsigned>(control.kind)) + ":" +
                    std::to_string(usage);
                if (control.kind == RawKind::Axis)
                    layout.axisPresent.push_back(IOHIDElementGetLogicalMin(control.element) <
                                                 IOHIDElementGetLogicalMax(control.element));
            }
        }
        if (result.controls.empty()) return {};
        const auto value = [&](CFStringRef key) {
            const auto property = IOHIDDeviceGetProperty(device, key);
            int number = 0;
            if (property && CFGetTypeID(property) == CFNumberGetTypeID() &&
                CFNumberGetValue(static_cast<CFNumberRef>(property), kCFNumberIntType, &number) &&
                number > 0 && number <= 65535)
                return std::optional{static_cast<std::uint16_t>(number)};
            return std::optional<std::uint16_t>{};
        };
        const auto text = [&](CFStringRef key) -> std::string {
            const auto property = IOHIDDeviceGetProperty(device, key);
            if (property && CFGetTypeID(property) == CFStringGetTypeID())
                if (const auto* utf8 = ((__bridge NSString*)property).UTF8String)
                    return utf8;
            return {};
        };
        const auto name = text(CFSTR(kIOHIDProductKey));
        descriptor.name = name.empty() ? "macOS HID Joystick" : name;
        descriptor.vendor = value(CFSTR(kIOHIDVendorIDKey));
        descriptor.product = value(CFSTR(kIOHIDProductIDKey));
        descriptor.version = value(CFSTR(kIOHIDVersionNumberKey));
        // Equal usages across different collections depend on enumeration order.
        if (uniqueOrder)
            layout.guid = DeviceGuid::make(3, descriptor.vendor.value_or(0), descriptor.product.value_or(0),
                descriptor.version.value_or(0), text(CFSTR(kIOHIDManufacturerKey)), name);
        result.raw.buttons.resize(layout.buttonCount);
        result.raw.axes.resize(layout.axisCount);
        result.raw.axesKnown.resize(layout.axisCount);
        result.raw.hats.resize(layout.hatCount);
        result.sample(device);
        return result;
    }

    std::optional<RawChange> update(IOHIDValueRef value)
    {
        const auto element = IOHIDValueGetElement(value);
        const auto item = controls.find(IOHIDElementGetCookie(element));
        if (item == controls.end()) return {};
        const auto& control = item->second;
        const auto index = control.index;
        const auto physical = IOHIDValueGetIntegerValue(value);
        const auto set = [&](auto& values, auto next) -> std::optional<RawChange> {
            if (values[index] == next) return {};
            values[index] = next;
            return RawChange{control.kind, index, next};
        };
        if (control.kind == RawKind::Button)
            return set(raw.buttons, static_cast<std::uint8_t>(physical != 0));
        const auto minimum = IOHIDElementGetLogicalMin(element);
        const auto maximum = IOHIDElementGetLogicalMax(element);
        if (minimum >= maximum)
            return {};
        if (control.kind == RawKind::Hat)
        {
            constexpr std::array hats{1, 3, 2, 6, 4, 12, 8, 9};
            const auto position = physical - minimum;
            const auto count = maximum - minimum + 1;
            const auto mask = position >= 0 && position < count ? hats[(position * 8 / count) % 8] : 0;
            return set(raw.hats, static_cast<std::uint8_t>(mask));
        }
        const auto ratio = static_cast<double>(std::clamp(physical, minimum, maximum) - minimum) / (maximum - minimum);
        const bool known = std::exchange(raw.axesKnown[index], 1);
        const auto normalized = static_cast<std::int16_t>(std::lround(ratio * 65535) - 32768);
        if (!known)
        {
            raw.axes[index] = normalized;
            return RawChange{control.kind, index, normalized};
        }
        return set(raw.axes, normalized);
    }

    void sample(IOHIDDeviceRef device)
    {
        for (const auto& [cookie, control] : controls)
        {
            IOHIDValueRef value = nullptr;
            if (IOHIDDeviceGetValue(device, control.element, &value) == kIOReturnSuccess && value)
                update(value);
        }
    }
};
#endif

struct State : std::enable_shared_from_this<State> {
    dispatch_queue_t queue = dispatch_queue_create("org.cocos.gamepad", DISPATCH_QUEUE_SERIAL);
    ReportSink* sink = nullptr;
    std::map<Identity, Device> devices;
    std::uint64_t next = 0;
    bool active = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    IOHIDManagerRef hid = nullptr;
    dispatch_semaphore_t hidCancelled = dispatch_semaphore_create(0);
    std::map<IOHIDDeviceRef, HidDevice> hidDevices;

    void startHid()
    {
        hid = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
        if (!hid) return;
        const auto matches = @[
            @{@kIOHIDDeviceUsagePageKey: @(kHIDPage_GenericDesktop), @kIOHIDDeviceUsageKey: @(kHIDUsage_GD_Joystick)},
            @{@kIOHIDDeviceUsagePageKey: @(kHIDPage_GenericDesktop), @kIOHIDDeviceUsageKey: @(kHIDUsage_GD_GamePad)}];
        IOHIDManagerSetDeviceMatchingMultiple(hid, (__bridge CFArrayRef)matches);
        IOHIDManagerRegisterDeviceMatchingCallback(hid, [](void* context, IOReturn status, void*, IOHIDDeviceRef device) {
            auto& state = *static_cast<State*>(context);
            if (!state.sink || status != kIOReturnSuccess || state.hidDevices.contains(device)) return;
            if (auto pad = HidDevice::open(device, {appleId, ++state.next, 1}))
            {
                auto& inserted = state.hidDevices.emplace(device, std::move(*pad)).first->second;
                state.sink->attached(inserted.key, inserted.descriptor, {inserted.raw, inserted.cursor, {}});
            }
        }, this);
        IOHIDManagerRegisterDeviceRemovalCallback(hid, [](void* context, IOReturn, void*, IOHIDDeviceRef device) {
            auto& state = *static_cast<State*>(context);
            if (const auto found = state.hidDevices.find(device); found != state.hidDevices.end())
            {
                if (state.sink) state.sink->detached(found->second.key);
                state.hidDevices.erase(found);
            }
        }, this);
        IOHIDManagerRegisterInputValueCallback(hid, [](void* context, IOReturn status, void*, IOHIDValueRef value) {
            auto& state = *static_cast<State*>(context);
            if (!state.sink || status != kIOReturnSuccess || !value) return;
            const auto index = state.hidDevices.find(IOHIDElementGetDevice(IOHIDValueGetElement(value)));
            if (index == state.hidDevices.end()) return;
            auto& pad = index->second;
            if (auto change = pad.update(value))
            {
                const std::array changes{*change};
                state.sink->report(pad.key, {changes, {}, {}, {}, ++pad.cursor, {}});
            }
        }, this);
        IOHIDManagerSetDispatchQueue(hid, queue);
        const auto signal = hidCancelled;
        IOHIDManagerSetCancelHandler(hid, ^{ dispatch_semaphore_signal(signal); });
        IOHIDManagerOpen(hid, kIOHIDOptionsTypeNone);
        IOHIDManagerActivate(hid);
    }
#endif

    void report(Identity identity, bool motion, id capture = nil)
    {
        const auto found = devices.find(identity);
        if (!sink || found == devices.end()) return;
        auto& device = found->second;
        if (capture || !device.buffered || !motion)
            device.sample(capture);
        else
            device.changes.clear();
        std::array<Motion, 2> values{};
        unsigned count = 0;
        if (motion && active)
        {
            auto sensor = device.controller.motion;
            if (device.sensors.test(static_cast<unsigned>(Sensor::Gyro)))
            {
                const auto v = sensor.rotationRate;
                values[count++] = {Sensor::Gyro, {static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z)}, {}};
            }
            if (@available(macOS 11.0, iOS 14.0, tvOS 14.0, *))
                if (device.sensors.test(static_cast<unsigned>(Sensor::Accel)))
                {
                    const auto v = sensor.acceleration;
                    values[count++] = {Sensor::Accel, {static_cast<float>(v.x) * gravity,
                        static_cast<float>(v.y) * gravity, static_cast<float>(v.z) * gravity}, {}};
                }
        }
        auto power = device.power();
        if (power && device.descriptor.power.state == power->state && device.descriptor.power.percent == power->percent)
            power.reset();
        if (power) device.descriptor.power = *power;
        if (!device.changes.empty() || count || power)
            sink->report(device.key, {device.changes, {}, std::span(values).first(count), power, ++device.cursor, {}});
    }

    void reportTouchpadClick(Identity identity, bool pressed)
    {
        const auto found = devices.find(identity);
        if (!sink || found == devices.end()) return;
        auto& device = found->second;
        auto& value = device.raw.buttons[touchpadClick];
        if (value == pressed) return;
        value = pressed;
        const std::array changes{RawChange{RawKind::Button, touchpadClick, value}};
        sink->report(device.key, {changes, {}, {}, {}, ++device.cursor, {}});
    }

    void reportTouch(Device& device, unsigned finger, float x, float y)
    {
        if (!active || !std::isfinite(x) || !std::isfinite(y)) return;
        auto& previous = device.contacts[finger];
        Contact change;
        // GameController exposes direction-pad axes for the two finger slots.
        // A released slot returns to neutral and has no separate touch flag.
        if (x == 0 && y == 0)
        {
            if (!previous) return;
            change = *previous;
            change.phase = ContactPhase::Up;
            previous.reset();
        }
        else
        {
            change = {0, finger, previous ? ContactPhase::Move : ContactPhase::Down,
                (std::clamp(x, -1.f, 1.f) + 1.f) * .5f, (1.f - std::clamp(y, -1.f, 1.f)) * .5f, {}};
            if (previous && previous->x == change.x && previous->y == change.y) return;
            previous = change;
        }
        sink->report(device.key, {{}, std::span(&change, 1), {}, {}, ++device.cursor, {}});
    }

    void refreshTouch(Device& device)
    {
        device.contacts.fill({});
        for (unsigned finger = 0; finger < device.touchpads.size(); ++finger)
            if (auto pad = device.touchpads[finger])
                reportTouch(device, finger, pad.xAxis.value, pad.yAxis.value);
    }

    void attach(GCController* controller)
    {
        if (!sink || (!controller.extendedGamepad && !controller.microGamepad))
            return;
        const auto key = identity(controller);
        if (devices.contains(key)) return;
        auto& device = devices.try_emplace(key, controller, EndpointKey{appleId, ++next, 1}).first->second;
        controller.handlerQueue = queue;
        const auto weak = weak_from_this();
        if (@available(macOS 14.0, iOS 17.0, tvOS 17.0, *))
            if (controller.extendedGamepad && !controller.snapshot && controller.input)
            {
                id<GCDevicePhysicalInput> input = (id<GCDevicePhysicalInput>)controller.input;
                device.buffered = true;
                device.originalPhysicalQueue = input.queue;
                device.originalStateQueueDepth = std::max<NSInteger>(1, input.inputStateQueueDepth);
                input.queue = queue;
                input.inputStateQueueDepth = 64;
                input.inputStateAvailableHandler = ^(id<GCDevicePhysicalInput> source) {
                    if (auto self = weak.lock())
                        while (auto state = source.nextInputState)
                            self->report(key, false, state);
                };
                if (auto click = device.buttons[touchpadClick]; click && !input.buttons[GCInputDualShockTouchpadButton])
                {
                    // Some extended profiles omit the click from their buffered elements.
                    device.usesLegacyTouchpadClick = true;
                    auto previous = device.originalTouchpadClickHandler = click.pressedChangedHandler;
                    click.pressedChangedHandler = ^(GCControllerButtonInput* button, float value, BOOL pressed) {
                        if (auto self = weak.lock()) self->reportTouchpadClick(key, pressed);
                        if (previous) previous(button, value, pressed);
                    };
                }
            }
        if (!device.buffered)
        {
            controller.extendedGamepad.valueChangedHandler = ^(GCExtendedGamepad*, GCControllerElement*) {
                if (auto self = weak.lock()) self->report(key, false);
            };
            controller.microGamepad.valueChangedHandler = ^(GCMicroGamepad*, GCControllerElement*) {
                if (auto self = weak.lock()) self->report(key, false);
            };
        }
        controller.motion.valueChangedHandler = ^(GCMotion*) {
            if (auto self = weak.lock()) self->report(key, true);
        };
        for (unsigned finger = 0; finger < device.touchpads.size(); ++finger)
            if (auto pad = device.touchpads[finger])
            {
                auto previous = device.originalTouchHandlers[finger] = pad.valueChangedHandler;
                pad.valueChangedHandler = ^(GCControllerDirectionPad* direction, float x, float y) {
                    if (auto self = weak.lock(); self && self->sink)
                        if (auto found = self->devices.find(key); found != self->devices.end())
                            self->reportTouch(found->second, finger, x, y);
                    if (previous) previous(direction, x, y);
                };
            }
        sink->attached(device.key, device.descriptor, {device.raw, device.cursor, {}});
        refreshTouch(device);
    }

    void detach(Identity id)
    {
        if (const auto found = devices.find(id); found != devices.end())
        {
            found->second.clear();
            if (sink) sink->detached(found->second.key);
            devices.erase(found);
        }
    }

    Device* find(EndpointKey key)
    {
        const auto found = std::ranges::find_if(devices, [&](auto& item) { return item.second.key == key; });
        return found == devices.end() ? nullptr : &found->second;
    }
};

class AppleBackend final : public GamepadBackend {
public:
    ~AppleBackend() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (_state) return Error::Busy;
        auto state = _state = std::make_shared<State>();
        state->sink = &sink;
        auto weak = std::weak_ptr(state);
        auto notifications = NSNotificationCenter.defaultCenter;
        _connect = [notifications addObserverForName:GCControllerDidConnectNotification object:nil queue:nil
            usingBlock:^(NSNotification* event) {
                if (auto live = weak.lock())
                {
                    GCController* controller = event.object;
                    dispatch_async(live->queue, ^{ live->attach(controller); });
                }
            }];
        _disconnect = [notifications addObserverForName:GCControllerDidDisconnectNotification object:nil queue:nil
            usingBlock:^(NSNotification* event) {
                if (auto live = weak.lock())
                {
                    GCController* controller = event.object;
                    dispatch_async(live->queue, ^{ live->detach(identity(controller)); });
                }
            }];
        dispatch_async(state->queue, ^{
            for (GCController* controller in GCController.controllers) state->attach(controller);
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
            state->startHid();
#endif
        });
        return Error::None;
    }

    void stop() noexcept override
    {
        auto state = std::move(_state);
        if (!state) return;
        auto notifications = NSNotificationCenter.defaultCenter;
        [notifications removeObserver:_connect];
        [notifications removeObserver:_disconnect];
        _connect = _disconnect = nil;
        dispatch_sync(state->queue, ^{
            state->sink = nullptr;
            for (auto& [id, device] : state->devices) device.clear();
            state->devices.clear();
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
            if (state->hid) IOHIDManagerCancel(state->hid);
            state->hidDevices.clear();
#endif
        });
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        if (state->hid)
        {
            dispatch_semaphore_wait(state->hidCancelled, DISPATCH_TIME_FOREVER);
            IOHIDManagerClose(state->hid, kIOHIDOptionsTypeNone);
            CFRelease(state->hid);
        }
#endif
    }

    void setActive(bool active) override
    {
        if (auto state = _state)
            dispatch_async(state->queue, ^{
                state->active = active;
                for (auto& [id, device] : state->devices)
                {
                    device.activateSensors(active);
                    if (!active) { device.output(Stop{}); device.stopRumble(true); }
                }
            });
    }

    void requestBaseline(EndpointKey key) override
    {
        if (auto state = _state)
            dispatch_async(state->queue, ^{
                if (auto* device = state->find(key); state->sink && device)
                {
                    device->sample();
                    state->sink->baseline(key, {device->raw, device->cursor, {}});
                    state->refreshTouch(*device);
                }
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
                else if (state->sink)
                    for (auto& [native, device] : state->hidDevices)
                        if (device.key == key)
                        {
                            device.sample(native);
                            state->sink->baseline(key, {device.raw, device.cursor, {}});
                        }
#endif
            });
    }

    void requestTopology() override
    {
        if (auto state = _state)
            dispatch_async(state->queue, ^{
                if (!state->sink) return;
                std::vector<AttachedEndpoint> snapshot;
                for (auto& [id, device] : state->devices)
                {
                    ++device.key.generation;
                    device.sample();
                    snapshot.push_back({device.key, device.descriptor, {device.raw, device.cursor, {}}});
                }
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
                for (auto& [native, device] : state->hidDevices)
                {
                    ++device.key.generation;
                    device.sample(native);
                    snapshot.push_back({device.key, device.descriptor, {device.raw, device.cursor, {}}});
                }
#endif
                state->sink->topology(std::move(snapshot));
                for (auto& [id, device] : state->devices)
                    state->refreshTouch(device);
            });
    }

    Error setSensor(EndpointKey key, Sensor sensor, bool enabled) override
    {
        auto state = _state;
        if (!state) return Error::Disconnected;
        __block Error status = Error::Disconnected;
        dispatch_sync(state->queue, ^{
            if (auto* device = state->find(key))
            {
                device->sensors.set(static_cast<unsigned>(sensor), enabled);
                device->activateSensors(state->active);
                status = Error::None;
            }
        });
        return status;
    }

    Error submit(EndpointKey key, const NativeCommand& command) override
    {
        auto state = _state;
        if (!state) return Error::Disconnected;
        auto request = command;
        dispatch_async(state->queue, ^{
            auto* device = state->find(key);
            const auto status = !device ? Error::Disconnected
                : !state->active && !std::holds_alternative<Stop>(request.command) ? Error::Busy
                : device->output(request.command);
            if (state->sink && request.id != CommandId{}) state->sink->outputCompleted(key, request.id, status);
        });
        return Error::None;
    }

private:
    std::shared_ptr<State> _state;
    id _connect = nil, _disconnect = nil;
};

} // namespace

std::unique_ptr<GamepadBackend> makeAppleGamepadBackend() { return std::make_unique<AppleBackend>(); }

} // namespace cc::input::detail
