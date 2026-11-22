/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/desktop/GLViewImpl-desktop.h"
#include "platform/FileDialogInternal.h"
#include "platform/desktop/TextInputGLFW.h"
#include "platform/Application.h"
#include "base/Configuration.h"
#include "base/Director.h"
#include "base/Touch.h"
#include "base/EventDispatcher.h"
#include "base/EventKeyboard.h"
#include "base/EventMouse.h"
#include "base/ccUtils.h"
#include "base/ccUTF8.h"
#include "2d/Camera.h"

#if CC_ICON_SET_SUPPORT
#include "platform/Image.h"
#endif
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
#include "glad/gl.h"
#include "glad/egl.h"
#endif
#include "renderer/Renderer.h"

#include "gfx-base/GFXDef-common.h"
#include "gfx-base/GFXSwapchain.h"
#include "GFXDeviceManager.h"
#include "renderer/backend/gfx/DeviceGFX.h"
#include "base/threading/MessageQueue.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/mac/GLViewImpl-desktop-mac.h"
#if !defined(CC_USE_METAL) || defined(CC_USE_VULKAN) || defined(CC_USE_GLES2) || defined(CC_USE_GLES3)
#error "macOS GLViewImpl requires GFX Metal only."
#endif
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#else
#define GLFW_EXPOSE_NATIVE_EGL
#ifdef CC_GLFW_WAYLAND
#define GLFW_EXPOSE_NATIVE_WAYLAND
#endif
#ifdef CC_GLFW_X11
#define GLFW_EXPOSE_NATIVE_X11
#endif
#ifndef Status
#define Status int
#endif
#endif
#include "glfw3native.h"
#endif

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <unordered_map>

static void GFXBeforeScreenResize()
{
    const auto agent = cc::gfx::DeviceAgent::getInstance();
    if (agent)
    {
        agent->getMessageQueue()->kickAndWait();
    }
}

static void SetDeviceFullScreenExclusiveMode(bool acquire)
{
    auto device = cc::gfx::Device::getInstance();
    if (!device)
        return;
    const auto& swapchains = device->getSwapchains();
    if (swapchains.empty())
        return;
    if (acquire)
        swapchains[0]->acquireFullScreenExclusiveMode();
    else
        swapchains[0]->releaseFullScreenExclusiveMode();
}

NS_CC_BEGIN

class GLFWEventHandler
{
public:
    static void onGLFWError(int errorID, const char* errorDesc)
    {
        if (_view)
            _view->onGLFWError(errorID, errorDesc);
    }

    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
    {
        if (_view)
            _view->onGLFWMouseCallBack(window, button, action, modify);
    }

    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseMoveCallBack(window, x, y);
    }

    static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
    {
        if (_view)
            _view->onGLFWMouseScrollCallback(window, x, y);
    }

    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (_view)
            _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }

    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character)
    {
        if (_view)
            _view->onGLFWCharCallback(window, character);
    }

    static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
    {
        if (_view)
            _view->onGLFWWindowPosCallback(windows, x, y);
    }

    static void setGLViewImpl(GLViewImpl* view) { _view = view; }

    static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
    {
        if (_view)
        {
            _view->onGLFWWindowIconifyCallback(window, iconified);
        }
    }

    static void onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
    {
        if (_view)
        {
            _view->onGLFWWindowFocusCallback(window, focused);
        }
    }

private:
    static GLViewImpl* _view;
};
GLViewImpl* GLFWEventHandler::_view = nullptr;

const std::string GLViewImpl::EVENT_WINDOW_RESIZED   = "glview_window_resized";
const std::string GLViewImpl::EVENT_WINDOW_FOCUSED   = "glview_window_focused";
const std::string GLViewImpl::EVENT_WINDOW_UNFOCUSED = "glview_window_unfocused";

////////////////////////////////////////////////////

static GLFWmonitor* getCurrentMonitor(GLFWwindow* window) {
#ifdef CC_GLFW_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
    {
        // A Wayland client cannot query its window position.
        auto* monitor = glfwGetWindowMonitor(window);
        return monitor ? monitor : glfwGetPrimaryMonitor();
    }
#endif
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    int windowX, windowY, windowWidth, windowHeight;
    glfwGetWindowPos(window, &windowX, &windowY);
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    const auto windowCenterX = windowX + windowWidth * 0.5f;
    const auto windowCenterY = windowY + windowHeight * 0.5f;

    for (int i = 0; i < monitorCount; i++) {
        int monitorX, monitorY;
        glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);

        int monitorWidth, monitorHeight;
        glfwGetMonitorWorkarea(monitors[i],
            &monitorX, &monitorY,
            &monitorWidth, &monitorHeight);

        if (windowCenterX >= monitorX &&
            windowCenterX < (monitorX + monitorWidth) &&
            windowCenterY >= monitorY &&
            windowCenterY < (monitorY + monitorHeight)) {
            return monitors[i];
        }
    }
    return glfwGetPrimaryMonitor();
}

struct keyCodeItem
{
    int glfwKeyCode;
    EventKeyboard::KeyCode keyCode;
};

static std::unordered_map<int, EventKeyboard::KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
    /* The unknown key */
    {GLFW_KEY_UNKNOWN, EventKeyboard::KeyCode::KEY_NONE},

    /* Printable keys */
    {GLFW_KEY_SPACE, EventKeyboard::KeyCode::KEY_SPACE},
    {GLFW_KEY_APOSTROPHE, EventKeyboard::KeyCode::KEY_APOSTROPHE},
    {GLFW_KEY_COMMA, EventKeyboard::KeyCode::KEY_COMMA},
    {GLFW_KEY_MINUS, EventKeyboard::KeyCode::KEY_MINUS},
    {GLFW_KEY_PERIOD, EventKeyboard::KeyCode::KEY_PERIOD},
    {GLFW_KEY_SLASH, EventKeyboard::KeyCode::KEY_SLASH},
    {GLFW_KEY_0, EventKeyboard::KeyCode::KEY_0},
    {GLFW_KEY_1, EventKeyboard::KeyCode::KEY_1},
    {GLFW_KEY_2, EventKeyboard::KeyCode::KEY_2},
    {GLFW_KEY_3, EventKeyboard::KeyCode::KEY_3},
    {GLFW_KEY_4, EventKeyboard::KeyCode::KEY_4},
    {GLFW_KEY_5, EventKeyboard::KeyCode::KEY_5},
    {GLFW_KEY_6, EventKeyboard::KeyCode::KEY_6},
    {GLFW_KEY_7, EventKeyboard::KeyCode::KEY_7},
    {GLFW_KEY_8, EventKeyboard::KeyCode::KEY_8},
    {GLFW_KEY_9, EventKeyboard::KeyCode::KEY_9},
    {GLFW_KEY_SEMICOLON, EventKeyboard::KeyCode::KEY_SEMICOLON},
    {GLFW_KEY_EQUAL, EventKeyboard::KeyCode::KEY_EQUAL},
    {GLFW_KEY_A, EventKeyboard::KeyCode::KEY_A},
    {GLFW_KEY_B, EventKeyboard::KeyCode::KEY_B},
    {GLFW_KEY_C, EventKeyboard::KeyCode::KEY_C},
    {GLFW_KEY_D, EventKeyboard::KeyCode::KEY_D},
    {GLFW_KEY_E, EventKeyboard::KeyCode::KEY_E},
    {GLFW_KEY_F, EventKeyboard::KeyCode::KEY_F},
    {GLFW_KEY_G, EventKeyboard::KeyCode::KEY_G},
    {GLFW_KEY_H, EventKeyboard::KeyCode::KEY_H},
    {GLFW_KEY_I, EventKeyboard::KeyCode::KEY_I},
    {GLFW_KEY_J, EventKeyboard::KeyCode::KEY_J},
    {GLFW_KEY_K, EventKeyboard::KeyCode::KEY_K},
    {GLFW_KEY_L, EventKeyboard::KeyCode::KEY_L},
    {GLFW_KEY_M, EventKeyboard::KeyCode::KEY_M},
    {GLFW_KEY_N, EventKeyboard::KeyCode::KEY_N},
    {GLFW_KEY_O, EventKeyboard::KeyCode::KEY_O},
    {GLFW_KEY_P, EventKeyboard::KeyCode::KEY_P},
    {GLFW_KEY_Q, EventKeyboard::KeyCode::KEY_Q},
    {GLFW_KEY_R, EventKeyboard::KeyCode::KEY_R},
    {GLFW_KEY_S, EventKeyboard::KeyCode::KEY_S},
    {GLFW_KEY_T, EventKeyboard::KeyCode::KEY_T},
    {GLFW_KEY_U, EventKeyboard::KeyCode::KEY_U},
    {GLFW_KEY_V, EventKeyboard::KeyCode::KEY_V},
    {GLFW_KEY_W, EventKeyboard::KeyCode::KEY_W},
    {GLFW_KEY_X, EventKeyboard::KeyCode::KEY_X},
    {GLFW_KEY_Y, EventKeyboard::KeyCode::KEY_Y},
    {GLFW_KEY_Z, EventKeyboard::KeyCode::KEY_Z},
    {GLFW_KEY_LEFT_BRACKET, EventKeyboard::KeyCode::KEY_LEFT_BRACKET},
    {GLFW_KEY_BACKSLASH, EventKeyboard::KeyCode::KEY_BACK_SLASH},
    {GLFW_KEY_RIGHT_BRACKET, EventKeyboard::KeyCode::KEY_RIGHT_BRACKET},
    {GLFW_KEY_GRAVE_ACCENT, EventKeyboard::KeyCode::KEY_GRAVE},
    {GLFW_KEY_WORLD_1, EventKeyboard::KeyCode::KEY_GRAVE},
    {GLFW_KEY_WORLD_2, EventKeyboard::KeyCode::KEY_NONE},

    /* Function keys */
    {GLFW_KEY_ESCAPE, EventKeyboard::KeyCode::KEY_ESCAPE},
    {GLFW_KEY_ENTER, EventKeyboard::KeyCode::KEY_ENTER},
    {GLFW_KEY_TAB, EventKeyboard::KeyCode::KEY_TAB},
    {GLFW_KEY_BACKSPACE, EventKeyboard::KeyCode::KEY_BACKSPACE},
    {GLFW_KEY_INSERT, EventKeyboard::KeyCode::KEY_INSERT},
    {GLFW_KEY_DELETE, EventKeyboard::KeyCode::KEY_DELETE},
    {GLFW_KEY_RIGHT, EventKeyboard::KeyCode::KEY_RIGHT_ARROW},
    {GLFW_KEY_LEFT, EventKeyboard::KeyCode::KEY_LEFT_ARROW},
    {GLFW_KEY_DOWN, EventKeyboard::KeyCode::KEY_DOWN_ARROW},
    {GLFW_KEY_UP, EventKeyboard::KeyCode::KEY_UP_ARROW},
    {GLFW_KEY_PAGE_UP, EventKeyboard::KeyCode::KEY_PG_UP},
    {GLFW_KEY_PAGE_DOWN, EventKeyboard::KeyCode::KEY_PG_DOWN},
    {GLFW_KEY_HOME, EventKeyboard::KeyCode::KEY_HOME},
    {GLFW_KEY_END, EventKeyboard::KeyCode::KEY_END},
    {GLFW_KEY_CAPS_LOCK, EventKeyboard::KeyCode::KEY_CAPS_LOCK},
    {GLFW_KEY_SCROLL_LOCK, EventKeyboard::KeyCode::KEY_SCROLL_LOCK},
    {GLFW_KEY_NUM_LOCK, EventKeyboard::KeyCode::KEY_NUM_LOCK},
    {GLFW_KEY_PRINT_SCREEN, EventKeyboard::KeyCode::KEY_PRINT},
    {GLFW_KEY_PAUSE, EventKeyboard::KeyCode::KEY_PAUSE},
    {GLFW_KEY_F1, EventKeyboard::KeyCode::KEY_F1},
    {GLFW_KEY_F2, EventKeyboard::KeyCode::KEY_F2},
    {GLFW_KEY_F3, EventKeyboard::KeyCode::KEY_F3},
    {GLFW_KEY_F4, EventKeyboard::KeyCode::KEY_F4},
    {GLFW_KEY_F5, EventKeyboard::KeyCode::KEY_F5},
    {GLFW_KEY_F6, EventKeyboard::KeyCode::KEY_F6},
    {GLFW_KEY_F7, EventKeyboard::KeyCode::KEY_F7},
    {GLFW_KEY_F8, EventKeyboard::KeyCode::KEY_F8},
    {GLFW_KEY_F9, EventKeyboard::KeyCode::KEY_F9},
    {GLFW_KEY_F10, EventKeyboard::KeyCode::KEY_F10},
    {GLFW_KEY_F11, EventKeyboard::KeyCode::KEY_F11},
    {GLFW_KEY_F12, EventKeyboard::KeyCode::KEY_F12},
    {GLFW_KEY_F13, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F14, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F15, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F16, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F17, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F18, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F19, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F20, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F21, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F22, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F23, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F24, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_F25, EventKeyboard::KeyCode::KEY_NONE},
    {GLFW_KEY_KP_0, EventKeyboard::KeyCode::KEY_0},
    {GLFW_KEY_KP_1, EventKeyboard::KeyCode::KEY_1},
    {GLFW_KEY_KP_2, EventKeyboard::KeyCode::KEY_2},
    {GLFW_KEY_KP_3, EventKeyboard::KeyCode::KEY_3},
    {GLFW_KEY_KP_4, EventKeyboard::KeyCode::KEY_4},
    {GLFW_KEY_KP_5, EventKeyboard::KeyCode::KEY_5},
    {GLFW_KEY_KP_6, EventKeyboard::KeyCode::KEY_6},
    {GLFW_KEY_KP_7, EventKeyboard::KeyCode::KEY_7},
    {GLFW_KEY_KP_8, EventKeyboard::KeyCode::KEY_8},
    {GLFW_KEY_KP_9, EventKeyboard::KeyCode::KEY_9},
    {GLFW_KEY_KP_DECIMAL, EventKeyboard::KeyCode::KEY_PERIOD},
    {GLFW_KEY_KP_DIVIDE, EventKeyboard::KeyCode::KEY_KP_DIVIDE},
    {GLFW_KEY_KP_MULTIPLY, EventKeyboard::KeyCode::KEY_KP_MULTIPLY},
    {GLFW_KEY_KP_SUBTRACT, EventKeyboard::KeyCode::KEY_KP_MINUS},
    {GLFW_KEY_KP_ADD, EventKeyboard::KeyCode::KEY_KP_PLUS},
    {GLFW_KEY_KP_ENTER, EventKeyboard::KeyCode::KEY_KP_ENTER},
    {GLFW_KEY_KP_EQUAL, EventKeyboard::KeyCode::KEY_EQUAL},
    {GLFW_KEY_LEFT_SHIFT, EventKeyboard::KeyCode::KEY_LEFT_SHIFT},
    {GLFW_KEY_LEFT_CONTROL, EventKeyboard::KeyCode::KEY_LEFT_CTRL},
    {GLFW_KEY_LEFT_ALT, EventKeyboard::KeyCode::KEY_LEFT_ALT},
    {GLFW_KEY_LEFT_SUPER, EventKeyboard::KeyCode::KEY_HYPER},
    {GLFW_KEY_RIGHT_SHIFT, EventKeyboard::KeyCode::KEY_RIGHT_SHIFT},
    {GLFW_KEY_RIGHT_CONTROL, EventKeyboard::KeyCode::KEY_RIGHT_CTRL},
    {GLFW_KEY_RIGHT_ALT, EventKeyboard::KeyCode::KEY_RIGHT_ALT},
    {GLFW_KEY_RIGHT_SUPER, EventKeyboard::KeyCode::KEY_HYPER},
    {GLFW_KEY_MENU, EventKeyboard::KeyCode::KEY_MENU},
    {GLFW_KEY_LAST, EventKeyboard::KeyCode::KEY_NONE}};

//////////////////////////////////////////////////////////////////////////
// implement GLViewImpl
//////////////////////////////////////////////////////////////////////////

GLViewImpl::GLViewImpl(bool initglfw)
    : _captured(false)
    , _isInRetinaMonitor(false)
    , _isRetinaEnabled(false)
    , _retinaFactor(1)
    , _frameZoomFactor(1.0f)
    , _mainWindow(nullptr)
    , _monitor(nullptr)
    , _mouseX(0.0f)
    , _mouseY(0.0f)
{
    _viewName = "cocos2dx";
    g_keyCodeMap.clear();
    for (auto&& item : g_keyCodeStructArray)
    {
        g_keyCodeMap[item.glfwKeyCode] = item.keyCode;
    }

    GLFWEventHandler::setGLViewImpl(this);
    if (initglfw)
    {
        glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
        glfwInit();
    }
}

GLViewImpl::~GLViewImpl()
{
    CCLOGINFO("deallocing GLViewImpl: %p", this);
    GLFWEventHandler::setGLViewImpl(nullptr);
    TextInputGLFW::detachWindows(getTextInputService());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    backend::DeviceGFX::shutdownSurface();
    detail::destroyMacWindowBridge(_macBridge);
    _macBridge = nullptr;
#endif
    glfwTerminate();
}

cc::IntrusivePtr<GLViewImpl> GLViewImpl::create(std::string_view viewName)
{
    return GLViewImpl::create(viewName, false);
}

cc::IntrusivePtr<GLViewImpl> GLViewImpl::create(std::string_view viewName, bool resizable)
{
    cc::IntrusivePtr ret{new GLViewImpl};
    if (ret->initWithRect(viewName, Rect(0, 0, 960, 640), 1.0f, resizable))
    {
        return ret;
    }
    return nullptr;
}

cc::IntrusivePtr<GLViewImpl> GLViewImpl::createWithRect(std::string_view viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    cc::IntrusivePtr ret{new GLViewImpl};
    if (ret->initWithRect(viewName, rect, frameZoomFactor, resizable))
    {
        return ret;
    }
    return nullptr;
}

cc::IntrusivePtr<GLViewImpl> GLViewImpl::createWithFullScreen(std::string_view viewName)
{
    cc::IntrusivePtr ret{new GLViewImpl()};
    if (ret->initWithFullScreen(viewName))
    {
        return ret;
    }
    return nullptr;
}

cc::IntrusivePtr<GLViewImpl> GLViewImpl::createWithFullScreen(std::string_view viewName,
                                             const GLFWvidmode& videoMode,
                                             GLFWmonitor* monitor)
{
    cc::IntrusivePtr ret{new GLViewImpl()};
    if (ret->initWithFullscreen(viewName, videoMode, monitor))
    {
        return ret;
    }
    return nullptr;
}

bool GLViewImpl::initWithRect(std::string_view viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    setViewName(viewName);

#if CC_DEBUG && (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // Opt-in cold-start coverage until Lua can configure GLContextAttrs.vsync.
    if (const char* initialVSync = std::getenv("CC_P2_INITIAL_VSYNC"))
    {
        if (initialVSync[0] == '0' && initialVSync[1] == '\0')
            _glContextAttrs.vsync = false;
        else if (initialVSync[0] == '1' && initialVSync[1] == '\0')
            _glContextAttrs.vsync = true;
        CC_LOG_INFO("P2 diagnostic: initial VSync request %s, effective %s",
            initialVSync, _glContextAttrs.vsync ? "on" : "off");
    }
    auto diagnosticCount = [](const char* name) -> unsigned long long {
        const char* value = std::getenv(name);
        if (!value || value[0] < '0' || value[0] > '9')
            return 0;
        char* end = nullptr;
        const auto count = std::strtoull(value, &end, 10);
        return end && *end == '\0' ? count : 0;
    };
    _p2ZeroSizeBegin = diagnosticCount("CC_P2_ZERO_SIZE_BEGIN");
    _p2ZeroSizeCount = diagnosticCount("CC_P2_ZERO_SIZE_COUNT");
    if (_p2ZeroSizeCount && !_p2ZeroSizeBegin)
        _p2ZeroSizeBegin = 1;
#endif

    _frameZoomFactor = frameZoomFactor;
    bool useGL = CC_TARGET_PLATFORM != CC_PLATFORM_MAC;
    auto desiredApi = cc::gfx::API::VULKAN;
    bool allowApiFallback = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    desiredApi = cc::gfx::API::METAL;
    const auto& configuredAPI = Configuration::getInstance()->getValue("GFXDesiredAPI");
    if (!configuredAPI.isNull())
    {
        const auto family = configuredAPI.getTypeFamily();
        const bool numeric = family == Value::Type::INTEGER || family == Value::Type::FLOAT ||
                             family == Value::Type::DOUBLE;
        if (!numeric || configuredAPI.asDouble() != static_cast<double>(desiredApi))
        {
            CC_LOG_ERROR("macOS GLViewImpl: GFXDesiredAPI must be Metal (%d), got %s",
                static_cast<int>(desiredApi), configuredAPI.getDescription().c_str());
            return false;
        }
    }
    useGL = false;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
    const auto configAPI = Configuration::getInstance()->getValue("GFXDesiredAPI").asInt((int)desiredApi);
    if (0 <= configAPI && configAPI <= (int)cc::gfx::API::WEBGPU)
	    desiredApi = (cc::gfx::API)configAPI;
#ifdef CC_GLFW_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
    {
        // GFX's EGL swapchains own an EGL native window. A wl_surface is valid
        // for Vulkan WSI but cannot be used as an EGL native window.
        if (desiredApi != cc::gfx::API::VULKAN && desiredApi != cc::gfx::API::UNKNOWN)
        {
            CC_LOG_ERROR("Native Wayland requires the Vulkan renderer. Select the X11 platform for GLES.");
            return false;
        }
        allowApiFallback = false;
    }
#endif
    useGL = !(desiredApi == cc::gfx::API::VULKAN || desiredApi == cc::gfx::API::METAL || desiredApi == cc::gfx::API::UNKNOWN);
    if (!useGL)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }
    else
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#if CC_DEBUG
        glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif
    }
#endif

    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RED_BITS, _glContextAttrs.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, _glContextAttrs.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, _glContextAttrs.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS, _glContextAttrs.alphaBits);
    glfwWindowHint(GLFW_DEPTH_BITS, _glContextAttrs.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS, _glContextAttrs.stencilBits);

    glfwWindowHint(GLFW_SAMPLES, _glContextAttrs.multisamplingCount);

    glfwWindowHint(GLFW_VISIBLE, _glContextAttrs.visible);
    glfwWindowHint(GLFW_DECORATED, _glContextAttrs.decorated);

    int neededWidth  = (int)(rect.size.width * _frameZoomFactor);
    int neededHeight = (int)(rect.size.height * _frameZoomFactor);

    _mainWindow = glfwCreateWindow(neededWidth, neededHeight, _viewName.c_str(), _monitor, nullptr);

    if (!_mainWindow)
    {
        std::string message = "Can't create window";
        if (!_glfwError.empty())
        {
            message.append("\nMore info: \n");
            message.append(_glfwError);
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        // No GLView has been installed in Director yet; the legacy alert assumes one exists.
        CC_LOG_ERROR("macOS GLViewImpl: %s", message.c_str());
#else
        ccMessageBox(message.c_str(), "Error launch application");
        utils::killCurrentProcess();  // kill current process, don't cause crash when driver issue.
#endif
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    _macBridge = detail::createMacWindowBridge(_mainWindow);
    if (!_macBridge)
    {
        CC_LOG_ERROR("macOS GLViewImpl: failed to create the Cocoa window bridge");
        return false;
    }
#endif

    /*
     *  Note that the created window and context may differ from what you requested,
     *  as not all parameters and hints are
     *  [hard constraints](@ref window_hints_hard).  This includes the size of the
     *  window, especially for full screen windows.  To retrieve the actual
     *  attributes of the created window and context, use queries like @ref
     *  glfwGetWindowAttrib and @ref glfwGetWindowSize.
     *
     *  see declaration glfwCreateWindow
     */
    int realW = 0, realH = 0;
    glfwGetWindowSize(_mainWindow, &realW, &realH);
    if (realW > 0)
    {
        rect.size.width = realW / _frameZoomFactor;
    }
    if (realH > 0)
    {
        rect.size.height = realH / _frameZoomFactor;
    }

    if (useGL)
    {
        glfwMakeContextCurrent(_mainWindow);
    }

    glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetWindowIconifyCallback(_mainWindow, GLFWEventHandler::onGLFWWindowIconifyCallback);
    glfwSetWindowFocusCallback(_mainWindow, GLFWEventHandler::onGLFWWindowFocusCallback);
    glfwSetWindowContentScaleCallback(_mainWindow, [](GLFWwindow* window, float, float) {
        TextInputGLFW::handleGeometry(window);
    });

    GLView::setFrameSize(rect.size.width, rect.size.height);
    setTextInputWindow(TextInputGLFW::attachWindow(getTextInputService(), _mainWindow, [this](const TextInputArea& area) {
        auto converted = textInputAreaToWindow(area);
        if (!converted || area.space == TextInputSpace::window)
            return converted;

        int width = 0, height = 0;
        glfwGetWindowSize(_mainWindow, &width, &height);
        const auto frame = getFrameSize();
        if (width <= 0 || height <= 0 || frame.width <= 0 || frame.height <= 0)
            return std::optional<TextInputArea>{};
        const double scaleX = width / static_cast<double>(frame.width);
        const double scaleY = height / static_cast<double>(frame.height);
        const auto scale = [scaleX, scaleY](TextInputRect& rect) {
            rect.x *= scaleX;
            rect.y *= scaleY;
            rect.width *= scaleX;
            rect.height *= scaleY;
        };
        scale(converted->caret);
        scale(converted->line);
        if (converted->clip)
            scale(*converted->clip);
        return converted;
    }));

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    if (useGL)
    {
        if (!gladLoaderLoadEGL(EGL_DEFAULT_DISPLAY) || !gladLoadGLES2(glfwGetProcAddress))
        {
            ccMessageBox("Failed to load glad", "OpenGL error");
            return false;
        }
        if (!eglGetDisplay)
        {
            ccMessageBox("Failed to load glad EGL", "OpenGL error");
            return false;
        }
        if (!glGetError)
        {
            ccMessageBox("Failed to load glad GLES", "OpenGL error");
            return false;
        }
    }
#endif

    void* hdl = getRenderSurfaceHandle();
    CC_ASSERT(hdl);

    const auto& cfgMT = Configuration::getInstance()->getValue("GFXMultithreaded");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // Each creation applies its own setting, including after an earlier false override.
    cc::gfx::DeviceManager::DETACH_DEVICE_THREAD =
        cfgMT.getType() != Value::Type::BOOLEAN || cfgMT.asBool();
#endif
    if (cfgMT.getType() == Value::Type::BOOLEAN && !cfgMT.asBool())
    {
        cc::gfx::DeviceManager::DETACH_DEVICE_THREAD = false;
        CC_LOG_INFO("Disable detach thread");
    }
    else
    {
        CC_LOG_INFO("Enable detach thread");
    }
    cc::gfx::DeviceInfo info;
    const auto device = cc::gfx::DeviceManager::create(info, desiredApi, allowApiFallback);
    if (!device)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        CC_LOG_ERROR("macOS GLViewImpl: failed to create a GFX Metal device");
#else
        ccMessageBox("Failed to create device", "Error");
#endif
        return false;
    }

    const auto api = device->getGfxAPI();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    if (api != cc::gfx::API::METAL)
    {
        CC_LOG_ERROR("macOS GLViewImpl: Metal device creation fell back to unsupported API %d",
            static_cast<int>(api));
        // No renderer adapter or swapchain exists yet; destroy the rejected GFX device first.
        device->destroy();
        delete device;
        return false;
    }
#else
    if (api != desiredApi)
    {
        CC_LOG_WARNING("Device API is not desired, changed from %d to %d",
            (int)desiredApi, (int)api);
    }
#endif

    refreshRenderSurfaceState();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    backend::DeviceGFX::setSwapchainInfo(hdl, _glContextAttrs.vsync,
        static_cast<uint32_t>(_renderFramebufferSize.width),
        static_cast<uint32_t>(_renderFramebufferSize.height), detail::getMacMetalLayer(_macBridge));
    CC_LOG_INFO("macOS Metal surface: window %.0fx%.0f, framebuffer %.0fx%.0f, VSync %s",
        _renderWindowSize.width, _renderWindowSize.height,
        _renderFramebufferSize.width, _renderFramebufferSize.height,
        _glContextAttrs.vsync ? "on" : "off");
#else
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    if (api == cc::gfx::API::VULKAN)
        hdl = _mainWindow; // glfwCreateWindowSurface selects the active WSI.
#endif
    backend::DeviceGFX::setSwapchainInfo(hdl, true,
        static_cast<uint32_t>(_renderFramebufferSize.width),
        static_cast<uint32_t>(_renderFramebufferSize.height));
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    if (useGL)
        glfwSwapInterval(_glContextAttrs.vsync ? 1 : 0);
#endif

    const auto& cfgExclusive = Configuration::getInstance()->getValue("CreateWithFullScreenExclusive");
    if (_monitor && cfgExclusive.getType() == Value::Type::BOOLEAN)
    {
        // apply config
        setFullscreen(cfgExclusive.asBool());
    }
    return true;
}

bool GLViewImpl::initWithFullScreen(std::string_view viewName)
{
    // Create fullscreen window on primary monitor at its current video mode.
    _monitor = glfwGetPrimaryMonitor();
    if (!_monitor)
        return false;

    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    if (!videoMode)
        return false;
    return initWithRect(viewName, Rect(0, 0, (float)videoMode->width, (float)videoMode->height), 1.0f, false);
}

bool GLViewImpl::initWithFullscreen(std::string_view viewname, const GLFWvidmode& videoMode, GLFWmonitor* monitor)
{
    // Create fullscreen on specified monitor at the specified video mode.
    _monitor = monitor;
    if (!_monitor)
        return false;

    // These are soft constraints. If the video mode is retrieved at runtime, the resulting window and context should
    // match these exactly. If invalid attribs are passed (eg. from an outdated cache), window creation will NOT fail
    // but the actual window/context may differ.
    glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
    glfwWindowHint(GLFW_RED_BITS, videoMode.redBits);
    glfwWindowHint(GLFW_BLUE_BITS, videoMode.blueBits);
    glfwWindowHint(GLFW_GREEN_BITS, videoMode.greenBits);

    return initWithRect(viewname, Rect(0, 0, (float)videoMode.width, (float)videoMode.height), 1.0f, false);
}

bool GLViewImpl::isOpenGLReady()
{
    return nullptr != _mainWindow;
}

void GLViewImpl::end()
{
    dialog::forgetView(this);
    GLFWEventHandler::setGLViewImpl(nullptr);
    _renderSurfaceAvailable = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    backend::DeviceGFX::shutdownSurface();
#endif
    if (_mainWindow)
    {
        TextInputGLFW::detachWindow(_mainWindow);
        setTextInputWindow(0);
        glfwSetWindowShouldClose(_mainWindow, 1);
        _mainWindow = nullptr;
    }
    // Release self. Otherwise, GLViewImpl could not be freed.
    release();
}

void GLViewImpl::swapBuffers()
{
    // gfx presents through its own swapchain; no GLFW swap is needed.
}

bool GLViewImpl::windowShouldClose()
{
    if (_mainWindow)
        return glfwWindowShouldClose(_mainWindow) ? true : false;
    else
        return true;
}

void GLViewImpl::pollEvents()
{
    if (!_mainWindow)
        return;
    glfwPollEvents();
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    TextInputGLFW::pollNativeEvents();
#endif
    refreshRenderSurfaceState(true);
    GLView::pollEvents();
}

void GLViewImpl::refreshRenderSurfaceState(bool polled)
{
    // GLFW can change the backing without sending a logical window-size event.
    // Publish both sizes together before the renderer acquires the next frame.
    const auto previousWindowSize = _renderWindowSize;
    const auto previousFramebufferSize = _renderFramebufferSize;
    int windowWidth = 0, windowHeight = 0;
    int pixelWidth = 0, pixelHeight = 0;
    if (_mainWindow)
    {
        glfwGetWindowSize(_mainWindow, &windowWidth, &windowHeight);
        glfwGetFramebufferSize(_mainWindow, &pixelWidth, &pixelHeight);
    }
    _renderWindowSize.set(std::max(windowWidth, 0), std::max(windowHeight, 0));
    _renderFramebufferSize.set(std::max(pixelWidth, 0), std::max(pixelHeight, 0));
    _renderSurfaceAvailable = _mainWindow &&
        windowWidth > 0 && windowHeight > 0 && pixelWidth > 0 && pixelHeight > 0 &&
        glfwGetWindowAttrib(_mainWindow, GLFW_ICONIFIED) == GLFW_FALSE &&
        glfwWindowShouldClose(_mainWindow) == GLFW_FALSE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    _renderSurfaceAvailable = _renderSurfaceAvailable && _macBridge &&
        glfwGetWindowAttrib(_mainWindow, GLFW_VISIBLE) == GLFW_TRUE;
#if CC_DEBUG
    if (polled)
    {
        ++_p2RenderSurfacePolls;
        if (_p2ZeroSizeCount && _p2RenderSurfacePolls >= _p2ZeroSizeBegin &&
            _p2RenderSurfacePolls - _p2ZeroSizeBegin < _p2ZeroSizeCount)
        {
            if (_p2RenderSurfacePolls == _p2ZeroSizeBegin)
                CC_LOG_INFO("P2 diagnostic: zero framebuffer begin at poll %llu for %llu polls",
                    _p2RenderSurfacePolls, _p2ZeroSizeCount);
            _renderFramebufferSize = Vec2::ZERO;
            _renderSurfaceAvailable = false;
        }
        else if (_p2ZeroSizeCount && _p2RenderSurfacePolls >= _p2ZeroSizeBegin &&
                 _p2RenderSurfacePolls - _p2ZeroSizeBegin == _p2ZeroSizeCount)
        {
            CC_LOG_INFO("P2 diagnostic: zero framebuffer end at poll %llu, actual %.0fx%.0f",
                _p2RenderSurfacePolls, _renderFramebufferSize.width, _renderFramebufferSize.height);
        }
    }
#endif
#endif

    if (!polled || !_renderSurfaceAvailable)
        return;

    auto* director = Director::getInstance();
    if (director->getOpenGLView() != this)
        return;

    const Vec2 frameSize = _renderWindowSize / _frameZoomFactor;
    const bool layoutChanged = _screenSize != frameSize;
    const bool surfaceChanged = _renderWindowSize != previousWindowSize ||
                                _renderFramebufferSize != previousFramebufferSize;
    if (layoutChanged)
    {
        GLView::setFrameSize(frameSize.width, frameSize.height);
        updateDesignResolutionSize();
    }
    else if (surfaceChanged)
    {
        director->setViewport();
    }
    if (layoutChanged || surfaceChanged)
    {
        TextInputGLFW::handleGeometry(_mainWindow);
        director->getEventDispatcher()->dispatchCustomEvent(EVENT_WINDOW_RESIZED, nullptr);
    }
}

void GLViewImpl::enableRetina(bool enabled)
{  // official v4 comment follow sources
   // #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
   //     _isRetinaEnabled = enabled;
   //     if (_isRetinaEnabled)
   //     {
   //         _retinaFactor = 1;
   //     }
   //     else
   //     {
   //         _retinaFactor = 2;
   //     }
   //     updateFrameSize();
   // #endif
}

#if CC_ICON_SET_SUPPORT
void GLViewImpl::setIcon(std::string_view filename) const
{
    this->setIcon(std::vector<std::string_view>{filename});
}

void GLViewImpl::setIcon(const std::vector<std::string_view>& filelist) const
{
    if (filelist.empty())
        return;
    std::vector<cc::IntrusivePtr<Image>> icons;
    for (auto const& filename : filelist)
    {
        cc::IntrusivePtr icon{new Image()};
        if (icon->initWithImageFile(filename))
        {
            icons.emplace_back(std::move(icon));
        }
    }

    if (icons.empty())
        return;  // No valid images
    size_t iconsCount = icons.size();
    std::vector<GLFWimage> images(iconsCount);
    for (size_t i = 0; i < iconsCount; i++)
    {
        auto& image  = images[i];
        auto& icon   = icons[i];
        image.width  = icon->getWidth();
        image.height = icon->getHeight();
        image.pixels = icon->getData();
    };

    GLFWwindow* window = this->getWindow();
    glfwSetWindowIcon(window, iconsCount, images.data());

}

void GLViewImpl::setDefaultIcon() const
{
    GLFWwindow* window = this->getWindow();
    glfwSetWindowIcon(window, 0, nullptr);
}
#endif /* CC_ICON_SET_SUPPORT */

void GLViewImpl::setCursorVisible(bool isVisible)
{
    if (!_mainWindow)
        return;

    if (isVisible)
        glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else
        glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void GLViewImpl::setFrameZoomFactor(float zoomFactor)
{
    CCASSERT(zoomFactor > 0.0f, "zoomFactor must be larger than 0");

    if (std::abs(_frameZoomFactor - zoomFactor) < FLT_EPSILON)
    {
        return;
    }

    _frameZoomFactor = zoomFactor;
    setFrameSize(_screenSize.width, _screenSize.height);
}

float GLViewImpl::getFrameZoomFactor() const
{
    return _frameZoomFactor;
}

bool GLViewImpl::isFullscreen() const
{
    return _monitor != nullptr || _borderlessFullscreen;
}

void GLViewImpl::setFullscreen(bool exclusive)
{
    setFullscreen(-1, -1, -1, exclusive);
}

void GLViewImpl::setFullscreen(int w, int h, int refreshRate, bool exclusive)
{
    auto monitor = glfwGetWindowMonitor(_mainWindow);
    if (!monitor)
        monitor = getCurrentMonitor(_mainWindow);
    if (!monitor)
        return;
    this->setFullscreen(monitor, w, h, refreshRate, exclusive);
}

void GLViewImpl::setFullscreen(int monitorIndex, bool exclusive)
{
    setFullscreen(monitorIndex, -1, -1, -1, exclusive);
}

void GLViewImpl::setFullscreen(int monitorIndex, int w, int h, int refreshRate, bool exclusive)
{
    int count              = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    if (monitorIndex < 0 || monitorIndex >= count)
    {
        return;
    }
    GLFWmonitor* monitor = monitors[monitorIndex];
    if (!monitor)
    {
        return;
    }
    this->setFullscreen(monitor, w, h, refreshRate, exclusive);
}

void GLViewImpl::setFullscreen(GLFWmonitor* monitor, int w, int h, int refreshRate, bool exclusive)
{
    if (!monitor)
        return;
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    // A locked or disconnected desktop can retain a monitor without a mode.
    if (!videoMode)
        return;
    if (w == -1)
        w = videoMode->width;
    if (h == -1)
        h = videoMode->height;
    if (refreshRate == -1)
        refreshRate = videoMode->refreshRate;
    if (w <= 0 || h <= 0)
        return;

    GFXBeforeScreenResize();
    int xpos = 0, ypos = 0;
    if (!exclusive)
    {
        if (_monitor)
            SetDeviceFullScreenExclusiveMode(false);
        // borderless fullscreen is a special window mode
        glfwSetWindowAttrib(_mainWindow, GLFW_DECORATED, GLFW_FALSE);
        glfwGetMonitorPos(monitor, &xpos, &ypos);
        _monitor = nullptr;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        const auto api = cc::gfx::Device::getInstance()->getGfxAPI();
        if (api == cc::gfx::API::GLES2 || api == cc::gfx::API::GLES3)
        {
            // GLES workaround: a surface that exactly matches the monitor size may
            // be taken over by the driver into exclusive fullscreen automatically;
            // this will keep the window in borderless mode
            h -= 1;
        }
#endif
    }
    else
    {
        // move from another exclusive monitor
        if (_monitor && _monitor != monitor)
            SetDeviceFullScreenExclusiveMode(false);
        _monitor = monitor;
    }

    _borderlessFullscreen = !exclusive;
    auto* windowMonitor = _monitor;
#ifdef CC_GLFW_WAYLAND
    // The compositor supplies the logical fullscreen size for its output.
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
        windowMonitor = monitor;
#endif
    glfwSetWindowMonitor(
        _mainWindow,
        windowMonitor,
        xpos, ypos, w, h, refreshRate);

    if (exclusive)
        SetDeviceFullScreenExclusiveMode(true);
}

void GLViewImpl::setWindowed(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;
    if (!this->isFullscreen())
    {
        this->setFrameSize((float)width, (float)height);
    }
    else
    {
        GFXBeforeScreenResize();
        if (_monitor)
            SetDeviceFullScreenExclusiveMode(false);
        const int windowWidth = static_cast<int>(width * _frameZoomFactor);
        const int windowHeight = static_cast<int>(height * _frameZoomFactor);
        int xpos = 0, ypos = 0;
#ifdef CC_GLFW_WAYLAND
        if (glfwGetPlatform() != GLFW_PLATFORM_WAYLAND)
#endif
        {
            auto* monitor = getCurrentMonitor(_mainWindow);
            const auto* videoMode = monitor ? glfwGetVideoMode(monitor) : nullptr;
            if (videoMode)
            {
                glfwGetMonitorPos(monitor, &xpos, &ypos);
                xpos += (videoMode->width - windowWidth) / 2;
                ypos += (videoMode->height - windowHeight) / 2;
            }
            else
            {
                glfwGetWindowPos(_mainWindow, &xpos, &ypos);
            }
        }
        _monitor = nullptr;
        _borderlessFullscreen = false;
        glfwSetWindowMonitor(_mainWindow, nullptr, xpos, ypos, windowWidth, windowHeight, GLFW_DONT_CARE);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        // on mac window will sometimes lose title when windowed
        glfwSetWindowTitle(_mainWindow, _viewName.c_str());
#endif
    }
    if (glfwGetWindowAttrib(_mainWindow, GLFW_DECORATED) == GLFW_FALSE)
        glfwSetWindowAttrib(_mainWindow, GLFW_DECORATED, GLFW_TRUE);
}

int GLViewImpl::getMonitorCount() const
{
    int count = 0;
    glfwGetMonitors(&count);
    return count;
}

Vec2 GLViewImpl::getMonitorSize() const
{
    GLFWmonitor* monitor = getMonitor();
    if (monitor)
    {
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        if (videoMode)
            return { (float)videoMode->width, (float)videoMode->height };
    }
    return Vec2::ZERO;
}

GLFWmonitor* GLViewImpl::getMonitor() const
{
    GLFWmonitor* monitor = getCurrentMonitor(_mainWindow);
    if (!monitor)
    {
        monitor = glfwGetWindowMonitor(getWindow());
    }
    return monitor;
}

void GLViewImpl::setFrameSize(float width, float height)
{
    if (!_mainWindow || width <= 0 || height <= 0)
        return;
    // The next window poll publishes the size accepted by GLFW and the compositor.
    GFXBeforeScreenResize();
    glfwSetWindowSize(_mainWindow, static_cast<int>(width * _frameZoomFactor),
        static_cast<int>(height * _frameZoomFactor));
}

Vec2 GLViewImpl::getFrameToFramebufferScale() const
{
    if (_screenSize.x > 0 && _screenSize.y > 0 &&
        _renderFramebufferSize.x > 0 && _renderFramebufferSize.y > 0)
    {
        return {_renderFramebufferSize.x / _screenSize.x,
                _renderFramebufferSize.y / _screenSize.y};
    }
    const auto scale = _retinaFactor * _frameZoomFactor;
    return {scale, scale};
}

void GLViewImpl::setViewPortInPoints(float x, float y, float w, float h)
{
    const auto scale = getFrameToFramebufferScale();
    Viewport vp;
    vp.x = static_cast<int>((x * _scaleX + _viewPortRect.origin.x) * scale.x);
    vp.y = static_cast<int>((y * _scaleY + _viewPortRect.origin.y) * scale.y);
    vp.w = static_cast<unsigned int>(w * _scaleX * scale.x);
    vp.h = static_cast<unsigned int>(h * _scaleY * scale.y);
    Camera::setDefaultViewport(vp);
}

void GLViewImpl::setScissorInPoints(float x, float y, float w, float h)
{
    const auto scale = getFrameToFramebufferScale();
    const auto pixelX = static_cast<int>((x * _scaleX + _viewPortRect.origin.x) * scale.x);
    const auto pixelY = static_cast<int>((y * _scaleY + _viewPortRect.origin.y) * scale.y);
    const auto pixelWidth = static_cast<unsigned int>(w * _scaleX * scale.x);
    const auto pixelHeight = static_cast<unsigned int>(h * _scaleY * scale.y);
    Director::getInstance()->getRenderer()->setScissorRect(pixelX, pixelY, pixelWidth, pixelHeight);
}

Rect GLViewImpl::getScissorRect() const
{
    const auto scale = getFrameToFramebufferScale();
    const auto& rect = Director::getInstance()->getRenderer()->getScissorRect();
    const float x = (rect.x / scale.x - _viewPortRect.origin.x) / _scaleX;
    const float y = (rect.y / scale.y - _viewPortRect.origin.y) / _scaleY;
    const float w = rect.width / (scale.x * _scaleX);
    const float h = rect.height / (scale.y * _scaleY);
    return Rect(x, y, w, h);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
HWND GLViewImpl::getWin32Window()
{
    return glfwGetWin32Window(_mainWindow);
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
id GLViewImpl::getCocoaWindow()
{
    return reinterpret_cast<id>(detail::getMacWindowHandle(_macBridge));
}
id GLViewImpl::getNSGLContext()
{
    return reinterpret_cast<id>(detail::getMacNSGLContext(_macBridge));
}
#else
void* GLViewImpl::getLinuxWindow()
{
#ifdef CC_GLFW_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
        return glfwGetWaylandWindow(_mainWindow);
#endif
#ifdef CC_GLFW_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
        return reinterpret_cast<void*>(glfwGetX11Window(_mainWindow));
#endif
    return nullptr;
}
#endif

void* GLViewImpl::getWindowHandle()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return glfwGetWin32Window(_mainWindow);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return detail::getMacWindowHandle(_macBridge);
#else
    return getLinuxWindow();
#endif
}

void* GLViewImpl::getRenderSurfaceHandle()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return detail::getMacRenderSurfaceHandle(_macBridge);
#else
    return getWindowHandle();
#endif
}

void GLViewImpl::onGLFWError(int errorID, const char* errorDesc)
{
    if (_mainWindow)
    {
        _glfwError = StringUtils::format("GLFWError #%d Happen, %s", errorID, errorDesc);
    }
    else
    {
        _glfwError.append(StringUtils::format("GLFWError #%d Happen, %s\n", errorID, errorDesc));
    }
    CC_LOG_ERROR("%s", _glfwError.c_str());
}

void GLViewImpl::onGLFWMouseCallBack(GLFWwindow* /*window*/, int button, int action, int /*modify*/)
{
    if (GLFW_MOUSE_BUTTON_LEFT == button)
    {
        if (GLFW_PRESS == action)
        {
            _captured = true;
            if (this->getViewPortRect().equals(Rect::ZERO) ||
                this->getViewPortRect().containsPoint(Vec2(_mouseX, _mouseY)))
            {
                intptr_t id = 0;
                this->handleTouchesBegin(1, &id, &_mouseX, &_mouseY);
            }
        }
        else if (GLFW_RELEASE == action)
        {
            if (_captured)
            {
                _captured   = false;
                intptr_t id = 0;
                this->handleTouchesEnd(1, &id, &_mouseX, &_mouseY);
            }
        }
    }

    // Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    if (GLFW_PRESS == action)
    {
        EventMouse event(EventMouse::MouseEventType::MOUSE_DOWN);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(static_cast<cc::EventMouse::MouseButton>(button));
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    else if (GLFW_RELEASE == action)
    {
        EventMouse event(EventMouse::MouseEventType::MOUSE_UP);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(static_cast<cc::EventMouse::MouseButton>(button));
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
}

void GLViewImpl::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
    _mouseX = (float)x;
    _mouseY = (float)y;

    _mouseX /= this->getFrameZoomFactor();
    _mouseY /= this->getFrameZoomFactor();

    if (_isInRetinaMonitor)
    {
        if (_retinaFactor == 1)
        {
            _mouseX *= 2;
            _mouseY *= 2;
        }
    }

    if (_captured)
    {
        intptr_t id = 0;
        this->handleTouchesMove(1, &id, &_mouseX, &_mouseY);
    }

    // Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;

    EventMouse event(EventMouse::MouseEventType::MOUSE_MOVE);
    // Set current button
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        event.setMouseButton(static_cast<cc::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_LEFT));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        event.setMouseButton(static_cast<cc::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_RIGHT));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        event.setMouseButton(static_cast<cc::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_MIDDLE));
    }
    event.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onGLFWMouseScrollCallback(GLFWwindow* /*window*/, double x, double y)
{
    EventMouse event(EventMouse::MouseEventType::MOUSE_SCROLL);
    // Because OpenGL and cocos2d-x uses different Y axis, we need to convert the coordinate here
    float cursorX = (_mouseX - _viewPortRect.origin.x) / _scaleX;
    float cursorY = (_viewPortRect.origin.y + _viewPortRect.size.height - _mouseY) / _scaleY;
    event.setScrollData((float)x, -(float)y);
    event.setCursorPosition(cursorX, cursorY);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GLViewImpl::onGLFWKeyCallback(GLFWwindow* window, int key, int /*scancode*/, int action, int mods)
{
    // Resolve the text target before a game listener can open a field in response to this key.
    if (action != GLFW_RELEASE && getTextInputService().hasTextFocus())
    {
        if (TextInputGLFW::isKeyConsumed(window))
            return;
        TextInputGLFW::handleKey(window, key, mods);
    }
    if (GLFW_REPEAT != action)
    {
        EventKeyboard event(g_keyCodeMap[key], GLFW_PRESS == action);
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchEvent(&event);
    }
}

void GLViewImpl::onGLFWCharCallback(GLFWwindow* window, unsigned int character)
{
    TextInputGLFW::handleCharacter(window, character);
}

void GLViewImpl::onGLFWWindowPosCallback(GLFWwindow* window, int x, int y)
{
    TextInputGLFW::handleGeometry(window);
    Director::getInstance()->setViewport();
    if (_monitor)
    {
        _monitor = getCurrentMonitor(_mainWindow);
    }
}

void GLViewImpl::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    Director::getInstance()->setGamepadWindowFocus(
        this, iconified == GLFW_FALSE && glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE);
    TextInputGLFW::handleGeometry(window);
    if (iconified == GLFW_TRUE)
    {
        Application::getInstance()->applicationDidEnterBackground();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("glview_window_iconified", nullptr);
    }
    else
    {
        Application::getInstance()->applicationWillEnterForeground();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("glview_window_uniconified", nullptr);
    }
}

void GLViewImpl::onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
{
    Director::getInstance()->setGamepadWindowFocus(
        this, focused == GLFW_TRUE && glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_FALSE);
    TextInputGLFW::handleFocus(window, focused == GLFW_TRUE);
    if (focused == GLFW_TRUE)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_FOCUSED, nullptr);
    }
    else
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_UNFOCUSED, nullptr);
    }
}

NS_CC_END // end of namespace cc;
