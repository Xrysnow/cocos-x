#include "platform/SystemInfoInternal.h"

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>
#if TARGET_OS_OSX
#import <IOKit/ps/IOPowerSources.h>
#import <IOKit/ps/IOPSKeys.h>
#elif !TARGET_OS_SIMULATOR
#import <UIKit/UIDevice.h>
#endif

#include <memory>
#include <mutex>
#include <optional>

namespace cc::system_info
{
namespace
{
ValueMap unavailableBattery(const char* reason)
{
    ValueMap result;
    for (const auto* field : {"present", "chargeFraction", "chargingState", "powerSource"})
        missing(result, field, reason);
    return result;
}

#if TARGET_OS_OSX
std::optional<bool> boolean(NSDictionary* values, NSString* key)
{
    const auto value = (__bridge CFTypeRef)values[key];
    if (value && CFGetTypeID(value) == CFBooleanGetTypeID())
        return CFBooleanGetValue(static_cast<CFBooleanRef>(value));
    return std::nullopt;
}

ValueMap macBattery()
{
    __attribute__((objc_precise_lifetime)) id snapshot = CFBridgingRelease(IOPSCopyPowerSourcesInfo());
    if (!snapshot)
        return failure("platformError", "IOPSCopyPowerSourcesInfo");
    const auto blob = (__bridge CFTypeRef)snapshot;

    ValueMap result;
    NSString* source = (__bridge NSString*)IOPSGetProvidingPowerSourceType(blob);
    const bool external = [source isEqualToString:@kIOPMACPowerKey] || [source isEqualToString:@kIOPMUPSPowerKey];
    const bool batteryPower = [source isEqualToString:@kIOPMBatteryPowerKey];
    if (external)
        result["powerSource"] = Value("external");
    else if (batteryPower)
        result["powerSource"] = Value("battery");

    NSArray* sources = CFBridgingRelease(IOPSCopyPowerSourcesList(blob));
    if (!sources)
        return result;

    size_t presentCount = 0;
    bool unknownPresence = false;
    NSDictionary* battery = nil;
    for (id handle in sources)
    {
        NSDictionary* info = (__bridge NSDictionary*)IOPSGetPowerSourceDescription(blob, (__bridge CFTypeRef)handle);
        NSString* type = info[@kIOPSTypeKey];
        NSString* transport = info[@kIOPSTransportTypeKey];
        if ([type isEqualToString:@kIOPSUPSType])
            continue;
        if (![type isEqualToString:@kIOPSInternalBatteryType] && ![transport isEqualToString:@kIOPSInternalType])
        {
            unknownPresence = true;
            continue;
        }

        const auto present = boolean(info, @kIOPSIsPresentKey);
        if (!present)
            unknownPresence = true;
        else if (*present)
        {
            ++presentCount;
            battery = info;
        }
    }

    if (presentCount || batteryPower)
        result["present"] = Value(true);
    else if (!unknownPresence)
    {
        result["present"] = Value(false);
        missing(result, "chargingState", "notApplicable");
        missing(result, "chargeFraction", "notApplicable");
    }
    if (presentCount != 1 || unknownPresence)
        return result;

    NSNumber* current = battery[@kIOPSCurrentCapacityKey];
    NSNumber* maximum = battery[@kIOPSMaxCapacityKey];
    if ([current isKindOfClass:NSNumber.class] && [maximum isKindOfClass:NSNumber.class])
    {
        const double now = current.doubleValue;
        const double max = maximum.doubleValue;
        if (max > 0 && now >= 0 && now <= max)
            result["chargeFraction"] = Value(now / max);
    }

    const auto charging = boolean(battery, @kIOPSIsChargingKey);
    if (charging == true)
        result["chargingState"] = Value("charging");
    else if (batteryPower)
        result["chargingState"] = Value("discharging");
    else if (external && charging == false)
    {
        if (auto charged = boolean(battery, @kIOPSIsChargedKey))
            result["chargingState"] = Value(*charged ? "full" : "notCharging");
    }
    return result;
}
#elif !TARGET_OS_SIMULATOR
ValueMap sampleBatteryOnMainThread()
{
    UIDevice* device = UIDevice.currentDevice;
    const bool wasEnabled = device.batteryMonitoringEnabled;
    if (!wasEnabled)
        device.batteryMonitoringEnabled = YES;
    const auto state = device.batteryState;
    const auto fraction = device.batteryLevel;
    if (!wasEnabled)
        device.batteryMonitoringEnabled = NO;

    ValueMap result;
    if (fraction >= 0 && fraction <= 1)
        result["chargeFraction"] = Value(static_cast<double>(fraction));
    switch (state)
    {
        case UIDeviceBatteryStateUnplugged:
            result["chargingState"] = Value("discharging");
            result["powerSource"] = Value("battery");
            break;
        case UIDeviceBatteryStateCharging:
            result["chargingState"] = Value("charging");
            result["powerSource"] = Value("external");
            break;
        case UIDeviceBatteryStateFull:
            result["chargingState"] = Value("full");
            result["powerSource"] = Value("external");
            break;
        case UIDeviceBatteryStateUnknown:
            break;
    }
    if (!result.empty())
        result["present"] = Value(true);
    return result;
}

struct MobileBatteryCache
{
    std::mutex mutex;
    ValueMap values = unavailableBattery("pending");
    bool scheduled = false;
};

ValueMap mobileBattery()
{
    static const auto cache = std::make_shared<MobileBatteryCache>();
    if (NSThread.isMainThread)
    {
        auto result = sampleBatteryOnMainThread();
        std::lock_guard lock(cache->mutex);
        cache->values = result;
        return result;
    }

    std::lock_guard lock(cache->mutex);
    if (!cache->scheduled)
    {
        cache->scheduled = true;
        const auto destination = cache;
        // Waiting synchronously here can deadlock a main-thread subscriber stop.
        dispatch_async(dispatch_get_main_queue(), ^{
            auto result = sampleBatteryOnMainThread();
            std::lock_guard lock(destination->mutex);
            destination->values = std::move(result);
            destination->scheduled = false;
        });
    }
    return cache->values;
}
#endif
}

ValueMap readBattery()
{
    @autoreleasepool
    {
#if TARGET_OS_OSX
        return macBattery();
#elif TARGET_OS_SIMULATOR
        auto result = unavailableBattery("unsupported");
        result["source"] = Value("simulatorDevice");
        return result;
#else
        return mobileBattery();
#endif
    }
}

ValueMap readPowerProfile()
{
    @autoreleasepool
    {
        ValueMap result;
        missing(result, "powerPlan", "unsupported");
        missing(result, "governors", "unsupported");
#if TARGET_OS_SIMULATOR
        missing(result, "profile", "unsupported");
        missing(result, "energyPreferences", "unsupported");
        result["source"] = Value("simulatorDevice");
#else
        if (@available(macOS 12.0, iOS 9.0, *))
        {
            const bool lowPower = NSProcessInfo.processInfo.lowPowerModeEnabled;
            result["lowPowerMode"] = Value(lowPower);
            if (lowPower)
            {
                result["profile"] = Value("powerSaver");
                result["energyPreferences"] = Value(ValueVector{Value("lowPowerMode")});
            }
            else
                result["energyPreferences"] = Value(ValueVector{});
        }
#endif
        return result;
    }
}

ValueMap readLimits()
{
    ValueMap result;
    missing(result, "allowedCpus", "unsupported");
    missing(result, "cpuQuota", "unsupported");
    missing(result, "memoryLimit", "unsupported");
    return result;
}
}
