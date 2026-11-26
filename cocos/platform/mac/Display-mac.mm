#include "platform/DisplayInternal.h"
#import <AppKit/AppKit.h>
#include "platform/desktop/GLViewImpl-desktop.h"
#include <cmath>
#include <limits>
#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3native.h"
namespace cc::display {
namespace {
using Screen = NSScreen;
Key keyOf(Screen* screen) { return [screen.deviceDescription[@"NSScreenNumber"] unsignedIntValue]; }
NSArray* screens() { return [NSScreen screens]; }
std::optional<DisplayRect> rect(CGRect frame, double top, bool workArea)
{
    const double x = workArea ? std::ceil(CGRectGetMinX(frame)) : std::round(CGRectGetMinX(frame));
    const double y = workArea ? std::ceil(top - CGRectGetMaxY(frame)) : std::round(top - CGRectGetMaxY(frame));
    const double w = (workArea ? std::floor(CGRectGetMaxX(frame)) : std::round(CGRectGetMaxX(frame))) - x;
    const double h = (workArea ? std::floor(top - CGRectGetMinY(frame)) : std::round(top - CGRectGetMinY(frame))) - y;
    if (!(x >= INT32_MIN && x <= INT32_MAX && y >= INT32_MIN && y <= INT32_MAX &&
          w >= 0 && w <= INT32_MAX && h >= 0 && h <= INT32_MAX)) return {};
    return DisplayRect{int(x), int(y), int(w), int(h)};
}
}
std::optional<Keys> enumerate()
{
    if (![NSThread isMainThread]) return {};
    Keys keys;
    for (Screen* screen in screens()) keys.push_back(keyOf(screen));
    return keys;
}
Key primary() { return [NSThread isMainThread] ? keyOf([screens() firstObject]) : 0; }
std::optional<DisplayInfo> read(Key key)
{
    if (![NSThread isMainThread]) return {};
    NSArray* all = screens();
    for (Screen* screen in all) {
        if (keyOf(screen) != key) continue;
        DisplayInfo info;
        NSScreen* main = [all firstObject];
        const auto top = NSMaxY(main.frame);
        info.coordinateSpace = DisplayCoordinateSpace::Desktop;
        info.geometry = rect(screen.frame, top, false);
        info.availableGeometry = rect(screen.visibleFrame, top, true);
        if (@available(macOS 10.15, *)) {
            if (const char* name = screen.localizedName.UTF8String) info.name = name;
        }
        info.devicePixelRatio = screen.backingScaleFactor;
        if (auto mode = CGDisplayCopyDisplayMode(static_cast<CGDirectDisplayID>(key))) {
            auto w = CGDisplayModeGetPixelWidth(mode), h = CGDisplayModeGetPixelHeight(mode);
            if (w && h && w <= INT32_MAX && h <= INT32_MAX) info.pixelSize = DisplaySize{int(w), int(h)};
            auto hz = CGDisplayModeGetRefreshRate(mode);
            if (std::isfinite(hz) && hz > 0) info.refreshRateHz = hz;
            CGDisplayModeRelease(mode);
        }
        return info;
    }
    return {};
}
}
namespace cc {
std::optional<DisplayInfo> GLViewImpl::getCurrentDisplayInfo() const
{
    if (![NSThread isMainThread]) return {};
    if (!_mainWindow) return {};
    NSWindow* window = glfwGetCocoaWindow(_mainWindow);
    return display::snapshot(display::keyOf(window.screen));
}
GLFWmonitor* GLViewImpl::resolveDisplayMonitor(DisplayId id)
{
    auto key = display::keyForId(id);
    int count = 0;
    auto list = glfwGetMonitors(&count);
    for (int i = 0; key && i < count; ++i)
        if (glfwGetCocoaMonitor(list[i]) == key) return list[i];
    return nullptr;
}
}
