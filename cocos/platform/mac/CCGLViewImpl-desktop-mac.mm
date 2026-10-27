#include "platform/mac/CCGLViewImpl-desktop-mac.h"

#include <Cocoa/Cocoa.h>
#include <QuartzCore/CAMetalLayer.h>
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
    // These references are owned independently of the view's layer attachment.
    CAMetalLayer* metalLayer;
    CALayer* previousLayer;
    BOOL previousWantsLayer;
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

        auto* bridge = new (std::nothrow) MacWindowBridge{
            cocoaWindow, contentView, nil, nil, [contentView wantsLayer]};
        if (!bridge)
            return nullptr;

        bridge->previousLayer = [[contentView layer] retain];
        bridge->metalLayer = [[CAMetalLayer alloc] init];
        if (!bridge->metalLayer)
        {
            [bridge->previousLayer release];
            delete bridge;
            return nullptr;
        }

        // AppKit owns geometry; the Metal actor sets device, pixel format,
        // drawableSize and presentation properties before the first acquire.
        [bridge->metalLayer setFrame:[contentView bounds]];
        [bridge->metalLayer setAutoresizingMask:kCALayerWidthSizable | kCALayerHeightSizable];
        [bridge->metalLayer setContentsScale:[cocoaWindow backingScaleFactor]];
        [contentView setWantsLayer:YES];
        [contentView setLayer:bridge->metalLayer];
        if ([contentView layer] != bridge->metalLayer)
        {
            destroyMacWindowBridge(bridge);
            return nullptr;
        }
        return bridge;
    }
}

void destroyMacWindowBridge(MacWindowBridge* bridge)
{
    if (!bridge)
        return;

    assert([NSThread isMainThread] && "Mac window bridge destruction requires the main thread");
    // The caller has already drained and destroyed the GFX surface. GLFW's
    // view must remain alive until its previous layer state has been restored.
    [bridge->contentView setLayer:bridge->previousLayer];
    [bridge->contentView setWantsLayer:bridge->previousWantsLayer];
    [bridge->metalLayer release];
    [bridge->previousLayer release];
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

void* getMacMetalLayer(const MacWindowBridge* bridge)
{
    return bridge ? static_cast<void*>(bridge->metalLayer) : nullptr;
}

void* getMacNSGLContext(const MacWindowBridge* /*bridge*/)
{
    return nullptr;
}

} // namespace detail
} // namespace cocos2d
