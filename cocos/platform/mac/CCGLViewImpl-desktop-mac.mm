#include "platform/mac/CCGLViewImpl-desktop-mac.h"

#include <Cocoa/Cocoa.h>
#include <cassert>
#include <new>

#define GLFW_INCLUDE_NONE
#include "glfw3.h"
#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3native.h"

#if __has_feature(objc_arc)
#error "CCGLViewImpl-desktop-mac.mm requires -fno-objc-arc"
#endif

namespace cocos2d
{
namespace detail
{

struct MacWindowBridge
{
    // Borrowed from GLFW. Do not retain or release these objects.
    NSWindow* window;
    NSView* contentView;
};

MacWindowBridge* createMacWindowBridge(GLFWwindow* window)
{
    const bool mainThread = [NSThread isMainThread];
    assert(mainThread && "Mac window bridge creation requires the main thread");
    if (!mainThread || !window)
        return nullptr;

    @autoreleasepool
    {
        NSWindow* cocoaWindow = glfwGetCocoaWindow(window);
        if (!cocoaWindow)
            return nullptr;

        NSView* contentView = [cocoaWindow contentView];
        if (!contentView)
            return nullptr;

        return new (std::nothrow) MacWindowBridge{cocoaWindow, contentView};
    }
}

void destroyMacWindowBridge(MacWindowBridge* bridge)
{
    if (!bridge)
        return;

    assert([NSThread isMainThread] && "Mac window bridge destruction requires the main thread");
    delete bridge;
}

void* getMacWindowHandle(const MacWindowBridge* bridge)
{
    return bridge ? static_cast<void*>(bridge->window) : nullptr;
}

void* getMacRenderSurfaceHandle(const MacWindowBridge* bridge)
{
    return bridge ? static_cast<void*>(bridge->contentView) : nullptr;
}

void* getMacNSGLContext(const MacWindowBridge* /*bridge*/)
{
    return nullptr;
}

} // namespace detail
} // namespace cocos2d
