#include "platform/SystemInfoInternal.h"

#import <Foundation/Foundation.h>
#import <Network/Network.h>
#import <TargetConditionals.h>

#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
#import <CoreTelephony/CTTelephonyNetworkInfo.h>

@interface CCSystemDataServiceObserver : NSObject <CTTelephonyNetworkInfoDelegate>
@property(nonatomic, copy) dispatch_block_t notifyChange;
@end

@implementation CCSystemDataServiceObserver
- (void)dataServiceIdentifierDidChange:(NSString*)identifier
{
    if (auto notify = self.notifyChange)
        notify();
}
@end
#endif

#include <memory>
#include <mutex>

namespace cc::system_info
{
namespace
{
ValueMap unresolvedPath(const char* reason)
{
    ValueMap result;
    for (const auto* field : {"primaryType", "cellularGeneration", "isMetered", "isVpn", "costHint"})
        missing(result, field, reason);
#if TARGET_OS_SIMULATOR
    result["source"] = Value("simulatorHost");
#endif
    return result;
}

const char* primaryTransport(nw_path_t path)
{
    constexpr struct
    {
        nw_interface_type_t type;
        const char* name;
    } candidates[] = {
        {nw_interface_type_wifi, "wifi"},
        {nw_interface_type_cellular, "cellular"},
        {nw_interface_type_wired, "ethernet"},
        {nw_interface_type_loopback, "other"},
        {nw_interface_type_other, nullptr},
    };
    const char* transport = nullptr;
    for (const auto& candidate : candidates)
    {
        if (!nw_path_uses_interface_type(path, candidate.type))
            continue;
        if (transport || !candidate.name)
            return nullptr;
        transport = candidate.name;
    }
    return transport;
}

#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
const char* generationForRadio(NSString* radio)
{
    if ([radio isEqualToString:CTRadioAccessTechnologyGPRS]
        || [radio isEqualToString:CTRadioAccessTechnologyEdge]
        || [radio isEqualToString:CTRadioAccessTechnologyCDMA1x])
        return "2G";
    if ([radio isEqualToString:CTRadioAccessTechnologyWCDMA]
        || [radio isEqualToString:CTRadioAccessTechnologyHSDPA]
        || [radio isEqualToString:CTRadioAccessTechnologyHSUPA]
        || [radio isEqualToString:CTRadioAccessTechnologyCDMAEVDORev0]
        || [radio isEqualToString:CTRadioAccessTechnologyCDMAEVDORevA]
        || [radio isEqualToString:CTRadioAccessTechnologyCDMAEVDORevB]
        || [radio isEqualToString:CTRadioAccessTechnologyeHRPD])
        return "3G";
    if ([radio isEqualToString:CTRadioAccessTechnologyLTE])
        return "4G";
    if (@available(iOS 14.1, *))
    {
        if ([radio isEqualToString:CTRadioAccessTechnologyNRNSA] || [radio isEqualToString:CTRadioAccessTechnologyNR])
            return "5G";
    }
    return nullptr;
}

void readCellularGeneration(ValueMap& result, CTTelephonyNetworkInfo* telephony)
{
    if (@available(iOS 13.0, *))
    {
        NSString* service = telephony.dataServiceIdentifier;
        if (service.length == 0)
            return;
        NSString* radio = telephony.serviceCurrentRadioAccessTechnology[service];
        if (!radio || ![service isEqualToString:telephony.dataServiceIdentifier])
            return;
        if (const auto* name = generationForRadio(radio))
            result["cellularGeneration"] = Value(name);
        if (const auto* name = radio.UTF8String; name && *name)
            result["cellularRadioTechnology"] = Value(name);
    }
}
#endif

class PathObserver
{
public:
    ~PathObserver()
    {
        if (monitor_)
            nw_path_monitor_cancel(monitor_);
#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
        if (radioNotification_)
            [NSNotificationCenter.defaultCenter removeObserver:radioNotification_];
        if (@available(iOS 13.0, *))
            telephony_.delegate = nil;
#endif
    }

    void start(std::weak_ptr<PathObserver> self)
    {
        monitor_ = nw_path_monitor_create();
        if (!monitor_)
        {
            snapshot_ = failure("platformError", "nw_path_monitor_create");
            return;
        }

        const auto queue = dispatch_queue_create("org.cocos.system-info.network", DISPATCH_QUEUE_SERIAL);
#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
        telephony_ = [[CTTelephonyNetworkInfo alloc] init];
        dispatch_block_t radioChanged = ^{
            dispatch_async(queue, ^{
                if (auto observer = self.lock(); observer && observer->path_)
                    observer->publish();
            });
        };
        if (@available(iOS 13.0, *))
        {
            dataServiceObserver_ = [[CCSystemDataServiceObserver alloc] init];
            dataServiceObserver_.notifyChange = radioChanged;
            telephony_.delegate = dataServiceObserver_;
        }
        radioNotification_ = [NSNotificationCenter.defaultCenter
            addObserverForName:CTServiceRadioAccessTechnologyDidChangeNotification
                        object:nil
                         queue:nil
                    usingBlock:^(NSNotification*) { radioChanged(); }];
#endif
        nw_path_monitor_set_queue(monitor_, queue);
        nw_path_monitor_set_update_handler(monitor_, ^(nw_path_t path) {
            if (auto observer = self.lock())
            {
                observer->path_ = path;
                observer->publish();
            }
        });
        nw_path_monitor_start(monitor_);
    }

    ValueMap snapshot()
    {
        std::lock_guard lock(snapshotMutex_);
        return snapshot_;
    }

private:
    ValueMap readPath()
    {
        const auto status = nw_path_get_status(path_);
        if (status == nw_path_status_satisfiable)
            return unresolvedPath("pending");
        if (status == nw_path_status_invalid)
            return unresolvedPath("unknown");
        if (status == nw_path_status_unsatisfied)
        {
            if (@available(macOS 11.0, iOS 14.2, *))
            {
                const auto reason = nw_path_get_unsatisfied_reason(path_);
                if (reason == nw_path_unsatisfied_reason_cellular_denied
                    || reason == nw_path_unsatisfied_reason_wifi_denied
                    || reason == nw_path_unsatisfied_reason_local_network_denied)
                    return unresolvedPath("permissionDenied");
            }
            auto result = unresolvedPath("notApplicable");
            result.at("missing").asValueMap().erase("primaryType");
            result["primaryType"] = Value("none");
            return result;
        }

        ValueMap result;
        missing(result, "isMetered", "unknown");
        missing(result, "isVpn", "unknown");
        result["costHint"] = Value(nw_path_is_expensive(path_) ? "expensive" : "notExpensive");
#if TARGET_OS_SIMULATOR
        result["source"] = Value("simulatorHost");
#endif
        if (const auto* transport = primaryTransport(path_))
        {
            result["primaryType"] = Value(transport);
            if (std::string_view(transport) != "cellular")
                missing(result, "cellularGeneration", "notApplicable");
#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
            else
                readCellularGeneration(result, telephony_);
#endif
        }
        return result;
    }

    void publish()
    {
        @autoreleasepool
        {
            auto result = readPath();
            {
                std::lock_guard lock(snapshotMutex_);
                snapshot_ = std::move(result);
            }
            networkChanged();
        }
    }

    nw_path_monitor_t monitor_ = nullptr;
    // Path and telephony refreshes run on the same serial queue.
    nw_path_t path_ = nullptr;
#if TARGET_OS_IOS && !TARGET_OS_SIMULATOR
    CTTelephonyNetworkInfo* telephony_ = nil;
    CCSystemDataServiceObserver* dataServiceObserver_ = nil;
    id radioNotification_ = nil;
#endif
    std::mutex snapshotMutex_;
    ValueMap snapshot_ = unresolvedPath("pending");
};

std::mutex observerMutex;
std::shared_ptr<PathObserver> observer;

std::shared_ptr<PathObserver> getOrStartObserver()
{
    std::lock_guard lock(observerMutex);
    if (!observer)
    {
        observer = std::make_shared<PathObserver>();
        observer->start(observer);
    }
    return observer;
}
}

void startNetworkEvents()
{
    getOrStartObserver();
}

void stopNetworkEvents()
{
    std::shared_ptr<PathObserver> old;
    {
        std::lock_guard lock(observerMutex);
        old.swap(observer);
    }
}

ValueMap readNetwork()
{
    return getOrStartObserver()->snapshot();
}
}
