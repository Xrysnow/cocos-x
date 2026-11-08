#import <Foundation/Foundation.h>
#include "platform/CCAppDirectories.h"

NS_CC_BEGIN

DirectoryResult queryAppleAppDirectory(AppDirectory kind, const std::string& appId)
{
    @autoreleasepool
    {
        NSError* error = nil;
        const auto search = kind == AppDirectory::PersistentData ? NSApplicationSupportDirectory : NSCachesDirectory;
        NSURL* url = [[NSFileManager defaultManager] URLForDirectory:search
            inDomain:NSUserDomainMask appropriateForURL:nil create:NO error:&error];
        if (!url)
        {
            const auto status = error && ([[error domain] isEqualToString:NSCocoaErrorDomain]) &&
                ([error code] == NSFileReadNoPermissionError || [error code] == NSFileWriteNoPermissionError)
                ? DirectoryStatus::PermissionDenied : DirectoryStatus::Unavailable;
            const char* domain = error ? [[error domain] UTF8String] : nullptr;
            return {status, {}, domain ? domain : "cocoa", error ? static_cast<std::int64_t>([error code]) : 0};
        }
        const char* native = [[url path] UTF8String];
        if (!native || !*native)
            return {DirectoryStatus::Unsupported, {}, "cocoa", 0};
        std::string path(native);
        if (path.back() != '/')
            path.push_back('/');
        path += appId;
        path += kind == AppDirectory::PersistentData ? "/data/" : "/";
        return {DirectoryStatus::Ok, std::move(path), {}, 0};
    }
}

NS_CC_END
