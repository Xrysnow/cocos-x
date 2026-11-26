#include "platform/DisplayInternal.h"
#import <UIKit/UIKit.h>
#include "platform/ios/GLViewImpl-ios.h"
#include <cmath>
#include <algorithm>

namespace cc::display {
namespace {
using Screen = UIScreen;
Key keyOf(Screen* screen) { return reinterpret_cast<Key>((__bridge void*)screen); }
NSArray* screens()
{
    NSMutableOrderedSet* result = [NSMutableOrderedSet orderedSet];
    for (UIScene* scene in UIApplication.sharedApplication.connectedScenes)
        if ([scene isKindOfClass:UIWindowScene.class]) [result addObject:((UIWindowScene*)scene).screen];
    return result.array;
}
}
std::optional<Keys> enumerate()
{
    if (![NSThread isMainThread]) return {};
    Keys keys;
    for (Screen* screen in screens()) keys.push_back(keyOf(screen));
    return keys;
}
Key primary() { return 0; }
std::optional<DisplayInfo> read(Key key)
{
    if (![NSThread isMainThread]) return {};
    NSArray* all = screens();
    for (Screen* screen in all) {
        if (keyOf(screen) != key) continue;
        DisplayInfo info;
        auto bounds = screen.bounds;
        const auto width = std::round(bounds.size.width);
        const auto height = std::round(bounds.size.height);
        if (width > 0 && height > 0 && width <= INT32_MAX && height <= INT32_MAX)
            info.geometry = DisplayRect{0, 0, int(width), int(height)};
        info.devicePixelRatio = screen.scale;
        CGSize mode = screen.currentMode.size;
        if ((bounds.size.width > bounds.size.height) != (mode.width > mode.height)) std::swap(mode.width, mode.height);
        if (mode.width > 0 && mode.height > 0 && mode.width <= INT32_MAX && mode.height <= INT32_MAX)
            info.pixelSize = DisplaySize{int(mode.width), int(mode.height)};
        return info;
    }
    return {};
}
}
namespace cc {
std::optional<DisplayInfo> GLViewImpl::getCurrentDisplayInfo() const
{
    if (![NSThread isMainThread]) return {};
    UIView* host = (__bridge UIView*)getEAGLView();
    return display::snapshot(display::keyOf(host.window.windowScene.screen));
}

}
