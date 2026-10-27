#pragma once

struct GLFWwindow;

namespace cocos2d
{
namespace detail
{

struct MacWindowBridge;

// Create and destroy on the main thread, while the GLFW window is still alive.
// GLFW retains ownership of the native window and content view.
MacWindowBridge* createMacWindowBridge(GLFWwindow* window);
void destroyMacWindowBridge(MacWindowBridge* bridge);

// Borrowed handles cached at creation; these queries do not access AppKit.
void* getMacWindowHandle(const MacWindowBridge* bridge);        // NSWindow*
void* getMacRenderSurfaceHandle(const MacWindowBridge* bridge); // NSView*

// A GLFW_NO_API window has no NSGL context.
void* getMacNSGLContext(const MacWindowBridge* bridge);

} // namespace detail
} // namespace cocos2d
