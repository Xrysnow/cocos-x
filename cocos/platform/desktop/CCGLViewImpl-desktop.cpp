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

#include "platform/desktop/CCGLViewImpl-desktop.h"
#include "platform/CCApplication.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventMouse.h"
#include "base/CCIMEDispatcher.h"
#include "base/ccUtils.h"
#include "base/ccUTF8.h"
#include "2d/CCCamera.h"

#if defined(_WIN32)
#include "glfw3ext.h"
#endif
#if CC_ICON_SET_SUPPORT
#include "platform/CCImage.h"
#endif
#include "glad/gl.h"
#include "glad/egl.h"
#include "renderer/CCRenderer.h"

#ifdef CC_USE_GFX
#include "gfx-base/GFXDef-common.h"
#include "GFXDeviceManager.h"
#include "renderer/backend/gfx/DeviceGFX.h"
#include "base/threading/MessageQueue.h"
static void GFXBeforeScreenResize()
{
    const auto agent = cc::gfx::DeviceAgent::getInstance();
    if (agent)
    {
        agent->getMessageQueue()->kickAndWait();
    }
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#else
#define GLFW_EXPOSE_NATIVE_EGL
#define GLFW_EXPOSE_NATIVE_X11
#ifndef Status
#define Status int
#endif
#endif
#include "glfw3native.h"

#include <cmath>
#include <unordered_map>

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

    // Notes: Unused on windows or macos Metal renderer backend
    // static void onGLFWframebufferSize(GLFWwindow* window, int w, int h)
    // {
    //     if (_view)
    //         _view->onGLFWframebufferSize(window, w, h);
    // }

    static void onGLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        if (_view)
            _view->onGLFWWindowSizeCallback(window, width, height);
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
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    int windowX, windowY, windowWidth, windowHeight;
    glfwGetWindowPos(window, &windowX, &windowY);
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);

    const auto windowCenterX = windowX + ((float)windowWidth / 2) * xscale;
    const auto windowCenterY = windowY + ((float)windowHeight / 2) * yscale;

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
#if defined(_WIN32)
        glfwxInit();
#else
        glfwInit();
#endif
    }
}

GLViewImpl::~GLViewImpl()
{
    CCLOGINFO("deallocing GLViewImpl: %p", this);
    GLFWEventHandler::setGLViewImpl(nullptr);
#if defined(_WIN32)
    glfwxTerminate();
#else
    glfwTerminate();
#endif
}

GLViewImpl* GLViewImpl::create(std::string_view viewName)
{
    return GLViewImpl::create(viewName, false);
}

GLViewImpl* GLViewImpl::create(std::string_view viewName, bool resizable)
{
    auto ret = new GLViewImpl;
    if (ret->initWithRect(viewName, Rect(0, 0, 960, 640), 1.0f, resizable))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithRect(std::string_view viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    auto ret = new GLViewImpl;
    if (ret->initWithRect(viewName, rect, frameZoomFactor, resizable))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(std::string_view viewName)
{
    auto ret = new GLViewImpl();
    if (ret->initWithFullScreen(viewName))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(std::string_view viewName,
                                             const GLFWvidmode& videoMode,
                                             GLFWmonitor* monitor)
{
    auto ret = new GLViewImpl();
    if (ret->initWithFullscreen(viewName, videoMode, monitor))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GLViewImpl::initWithRect(std::string_view viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    setViewName(viewName);

    _frameZoomFactor = frameZoomFactor;
    bool useGL = CC_TARGET_PLATFORM != CC_PLATFORM_MAC;
#if defined(CC_USE_GFX)
    auto desiredApi = cc::gfx::API::VULKAN;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    DesiredAPI = cc::gfx::API::METAL;
#endif
    auto configAPI = Configuration::getInstance()->getValue("GFXDesiredAPI").asInt();
    if (0 < configAPI && configAPI <= (int)cc::gfx::API::WEBGPU)
	    desiredApi = (cc::gfx::API)configAPI;
    useGL = !(desiredApi == cc::gfx::API::VULKAN || desiredApi == cc::gfx::API::METAL);
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
#elif defined(CC_USE_ANGLE)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#elif defined(CC_USE_METAL)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    glfwxSetParent((HWND)_glContextAttrs.viewParent);
#endif

    _mainWindow = glfwCreateWindow(neededWidth, neededHeight, _viewName.c_str(), _monitor, nullptr);

    if (_mainWindow == nullptr)
    {
        std::string message = "Can't create window";
        if (!_glfwError.empty())
        {
            message.append("\nMore info: \n");
            message.append(_glfwError);
        }

        ccMessageBox(message.c_str(), "Error launch application");
        utils::killCurrentProcess();  // kill current process, don't cause crash when driver issue.
        return false;
    }

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
    if (realW != neededWidth)
    {
        rect.size.width = realW / _frameZoomFactor;
    }
    if (realH != neededHeight)
    {
        rect.size.height = realH / _frameZoomFactor;
    }

    glfwMakeContextCurrent(_mainWindow);

    glfwSetMouseButtonCallback(_mainWindow, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_mainWindow, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_mainWindow, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_mainWindow, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_mainWindow, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_mainWindow, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetWindowSizeCallback(_mainWindow, GLFWEventHandler::onGLFWWindowSizeCallback);
    glfwSetWindowIconifyCallback(_mainWindow, GLFWEventHandler::onGLFWWindowIconifyCallback);
    glfwSetWindowFocusCallback(_mainWindow, GLFWEventHandler::onGLFWWindowFocusCallback);

    setFrameSize(rect.size.width, rect.size.height);

#if defined(CC_USE_GFX)

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

    void* hdl = getWindowHandle();
    CC_ASSERT(hdl);

    cc::gfx::DeviceInfo info;
    const auto device = cc::gfx::DeviceManager::create(info, desiredApi);
    if (!device)
    {
        ccMessageBox("Failed to create device", "Error");
        return false;
    }

    backend::DeviceGFX::setSwapchainInfo(hdl, true, rect.size.width, rect.size.height);

    auto configMT = Configuration::getInstance()->getValue("GFXMultithreaded");
    const auto agent = dynamic_cast<cc::gfx::DeviceAgent*>(device);
    if (agent && configMT.getType() == Value::Type::BOOLEAN)
    {
        agent->setMultithreaded(configMT.asBool());
    }

#elif (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

    loadGL();

    // check OpenGL version at first
    const char* glVersion = glGetString ? (const char*)glGetString(GL_VERSION) : nullptr;

    if (!glVersion || (strlen(glVersion) <= 3 && utils::atof(glVersion) < 1.5 && nullptr == strstr(glVersion, "ANGLE")))
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
                "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
                glVersion ? glVersion : "unknown");
        ccMessageBox(strComplain, "Invalid OpenGL version");
        utils::killCurrentProcess();  // kill current process, don't cause crash when driver issue.
        return false;
    }

#ifndef CC_USE_ANGLE
    // Enable point size by default.
#    if defined(GL_VERSION_2_0)
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
#    else
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
#    endif
    if (_glContextAttrs.multisamplingCount > 0)
        glEnable(GL_MULTISAMPLE);
#endif
    CHECK_GL_ERROR_DEBUG();

#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    if (useGL)
        glfwSwapInterval(_glContextAttrs.vsync ? 1 : 0);
#endif

//    // GLFW v3.2 no longer emits "onGLFWWindowSizeFunCallback" at creation time. Force default viewport:
//    setViewPortInPoints(0, 0, neededWidth, neededHeight);
//
    return true;
}

bool GLViewImpl::initWithFullScreen(std::string_view viewName)
{
    // Create fullscreen window on primary monitor at its current video mode.
    _monitor = glfwGetPrimaryMonitor();
    if (nullptr == _monitor)
        return false;

    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    return initWithRect(viewName, Rect(0, 0, (float)videoMode->width, (float)videoMode->height), 1.0f, false);
}

bool GLViewImpl::initWithFullscreen(std::string_view viewname, const GLFWvidmode& videoMode, GLFWmonitor* monitor)
{
    // Create fullscreen on specified monitor at the specified video mode.
    _monitor = monitor;
    if (nullptr == _monitor)
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
    if (_mainWindow)
    {
        glfwSetWindowShouldClose(_mainWindow, 1);
        _mainWindow = nullptr;
    }
    // Release self. Otherwise, GLViewImpl could not be freed.
    release();
}

void GLViewImpl::swapBuffers()
{
#ifndef CC_USE_GFX
    if (_mainWindow)
        glfwSwapBuffers(_mainWindow);
#endif
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
    glfwPollEvents();
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

void GLViewImpl::setIMEKeyboardState(bool /*bOpen*/) {}

#if CC_ICON_SET_SUPPORT
void GLViewImpl::setIcon(std::string_view filename) const
{
    this->setIcon(std::vector<std::string_view>{filename});
}

void GLViewImpl::setIcon(const std::vector<std::string_view>& filelist) const
{
    if (filelist.empty())
        return;
    std::vector<Image*> icons;
    for (auto const& filename : filelist)
    {
        Image* icon = new Image();
        if (icon->initWithImageFile(filename))
        {
            icons.emplace_back(icon);
        }
        else
        {
            CC_SAFE_DELETE(icon);
        }
    }

    if (icons.empty())
        return;  // No valid images
    size_t iconsCount = icons.size();
    auto images       = new GLFWimage[iconsCount];
    for (size_t i = 0; i < iconsCount; i++)
    {
        auto& image  = images[i];
        auto& icon   = icons[i];
        image.width  = icon->getWidth();
        image.height = icon->getHeight();
        image.pixels = icon->getData();
    };

    GLFWwindow* window = this->getWindow();
    glfwSetWindowIcon(window, iconsCount, images);

    CC_SAFE_DELETE_ARRAY(images);
    for (auto&& icon : icons)
    {
        CC_SAFE_DELETE(icon);
    }
}

void GLViewImpl::setDefaultIcon() const
{
    GLFWwindow* window = this->getWindow();
    glfwSetWindowIcon(window, 0, nullptr);
}
#endif /* CC_ICON_SET_SUPPORT */

void GLViewImpl::setCursorVisible(bool isVisible)
{
    if (_mainWindow == NULL)
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
    updateFrameSize();
}

float GLViewImpl::getFrameZoomFactor() const
{
    return _frameZoomFactor;
}

bool GLViewImpl::isFullscreen() const
{
    return (_monitor != nullptr);
}

void GLViewImpl::setFullscreen()
{
    setFullscreen(-1, -1, -1);
}

void GLViewImpl::setFullscreen(int w, int h, int refreshRate)
{
    auto monitor = isFullscreen() ? glfwGetWindowMonitor(_mainWindow) : getCurrentMonitor(_mainWindow);
    if (nullptr == monitor)
    {
        return;
    }
    this->setFullscreen(monitor, w, h, refreshRate);
}

void GLViewImpl::setFullscreen(int monitorIndex)
{
    setFullscreen(monitorIndex, -1, -1, -1);
}

void GLViewImpl::setFullscreen(int monitorIndex, int w, int h, int refreshRate)
{
    int count              = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    if (monitorIndex < 0 || monitorIndex >= count)
    {
        return;
    }
    GLFWmonitor* monitor = monitors[monitorIndex];
    if (nullptr == monitor)
    {
        return;
    }
    this->setFullscreen(monitor, w, h, refreshRate);
}

void GLViewImpl::setFullscreen(GLFWmonitor* monitor, int w, int h, int refreshRate)
{
    _monitor = monitor;

    const GLFWvidmode* videoMode = glfwGetVideoMode(_monitor);
    if (w == -1)
        w = videoMode->width;
    if (h == -1)
        h = videoMode->height;
    if (refreshRate == -1)
        refreshRate = videoMode->refreshRate;

    glfwSetWindowMonitor(_mainWindow, _monitor, 0, 0, w, h, refreshRate);

    updateWindowSize();
}

void GLViewImpl::setWindowed(int width, int height)
{
    if (!this->isFullscreen())
    {
        this->setFrameSize((float)width, (float)height);
    }
    else
    {
        GLFWmonitor* monitor = getCurrentMonitor(_mainWindow);
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        int xpos = 0, ypos = 0;
        glfwGetMonitorPos(monitor, &xpos, &ypos);
        xpos += (int)((videoMode->width - width) * 0.5f);
        ypos += (int)((videoMode->height - height) * 0.5f);
        _monitor = nullptr;
        glfwSetWindowMonitor(_mainWindow, nullptr, xpos, ypos, width, height, GLFW_DONT_CARE);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        // on mac window will sometimes lose title when windowed
        glfwSetWindowTitle(_mainWindow, _viewName.c_str());
#endif

        updateWindowSize();
    }
}

void GLViewImpl::updateWindowSize()
{
    int w = 0, h = 0;
    glfwGetFramebufferSize(_mainWindow, &w, &h);
    int frameWidth  = w / _frameZoomFactor;
    int frameHeight = h / _frameZoomFactor;
    setFrameSize(frameWidth, frameHeight);
    updateDesignResolutionSize();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_RESIZED, nullptr);
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
    if (nullptr != monitor)
    {
        const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
        Vec2 size                    = Vec2((float)videoMode->width, (float)videoMode->height);
        return size;
    }
    return Vec2::ZERO;
}

GLFWmonitor* GLViewImpl::getMonitor() const
{
    GLFWmonitor* monitor = getCurrentMonitor(_mainWindow);
    if (nullptr == monitor)
    {
        monitor = glfwGetWindowMonitor(getWindow());
    }
    return monitor;
}

void GLViewImpl::updateFrameSize()
{
    if (_screenSize.width > 0 && _screenSize.height > 0)
    {
        int w = 0, h = 0;
        glfwGetWindowSize(_mainWindow, &w, &h);

        int frameBufferW = 0, frameBufferH = 0;
        glfwGetFramebufferSize(_mainWindow, &frameBufferW, &frameBufferH);

        // if (frameBufferW == 2 * w && frameBufferH == 2 * h)
        // {
        //     if (_isRetinaEnabled)
        //     {
        //         _retinaFactor = 1;
        //     }
        //     else
        //     {
        //         _retinaFactor = 2;
        //     }
        //     glfwSetWindowSize(_mainWindow, _screenSize.width/2 * _retinaFactor * _frameZoomFactor, _screenSize.height/2 * _retinaFactor * _frameZoomFactor);

        //     _isInRetinaMonitor = true;
        // }
        // else
        {
            if (_isInRetinaMonitor)
            {
                _retinaFactor = 1;
            }
#ifdef CC_USE_GFX
            GFXBeforeScreenResize();
#endif
            glfwSetWindowSize(_mainWindow,
                (int)(_screenSize.width * _retinaFactor * _frameZoomFactor),
                (int)(_screenSize.height * _retinaFactor * _frameZoomFactor));

            _isInRetinaMonitor = false;
        }
    }
}

void GLViewImpl::setFrameSize(float width, float height)
{
    GLView::setFrameSize(width, height);
    updateFrameSize();
}

void GLViewImpl::setViewPortInPoints(float x, float y, float w, float h)
{
    Viewport vp;
    vp.x = (int)(x * _scaleX * _retinaFactor * _frameZoomFactor +
                 _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor);
    vp.y = (int)(y * _scaleY * _retinaFactor * _frameZoomFactor +
                 _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor);
    vp.w = (unsigned int)(w * _scaleX * _retinaFactor * _frameZoomFactor);
    vp.h = (unsigned int)(h * _scaleY * _retinaFactor * _frameZoomFactor);
    Camera::setDefaultViewport(vp);
}

void GLViewImpl::setScissorInPoints(float x, float y, float w, float h)
{
    auto x1       = (int)(x * _scaleX * _retinaFactor * _frameZoomFactor +
                    _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor);
    auto y1       = (int)(y * _scaleY * _retinaFactor * _frameZoomFactor +
                    _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor);
    auto width1   = (unsigned int)(w * _scaleX * _retinaFactor * _frameZoomFactor);
    auto height1  = (unsigned int)(h * _scaleY * _retinaFactor * _frameZoomFactor);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setScissorRect(x1, y1, width1, height1);

}

Rect GLViewImpl::getScissorRect() const
{
    auto renderer = Director::getInstance()->getRenderer();
    auto& rect    = renderer->getScissorRect();

    float x = (rect.x - _viewPortRect.origin.x * _retinaFactor * _frameZoomFactor) /
              (_scaleX * _retinaFactor * _frameZoomFactor);
    float y = (rect.y - _viewPortRect.origin.y * _retinaFactor * _frameZoomFactor) /
              (_scaleY * _retinaFactor * _frameZoomFactor);
    float w = rect.width / (_scaleX * _retinaFactor * _frameZoomFactor);
    float h = rect.height / (_scaleY * _retinaFactor * _frameZoomFactor);
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
    return glfwGetCocoaWindow(_mainWindow);
}
id GLViewImpl::getNSGLContext()
{
    return glfwGetNSGLContext(_mainWindow);
}
#else
void* GLViewImpl::getLinuxWindow()
{
    return (void*)glfwGetX11Window(_mainWindow);
}
#endif

void* GLViewImpl::getWindowHandle()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return glfwGetWin32Window(_mainWindow);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return (void*)glfwGetCocoaWindow(_mainWindow);
#else
    return (void*)glfwGetX11Window(_mainWindow);
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
        event.setMouseButton(static_cast<cocos2d::EventMouse::MouseButton>(button));
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }
    else if (GLFW_RELEASE == action)
    {
        EventMouse event(EventMouse::MouseEventType::MOUSE_UP);
        event.setCursorPosition(cursorX, cursorY);
        event.setMouseButton(static_cast<cocos2d::EventMouse::MouseButton>(button));
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
        event.setMouseButton(static_cast<cocos2d::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_LEFT));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        event.setMouseButton(static_cast<cocos2d::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_RIGHT));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {
        event.setMouseButton(static_cast<cocos2d::EventMouse::MouseButton>(GLFW_MOUSE_BUTTON_MIDDLE));
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

void GLViewImpl::onGLFWKeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
    if (GLFW_REPEAT != action)
    {
        EventKeyboard event(g_keyCodeMap[key], GLFW_PRESS == action);
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchEvent(&event);
    }

    if (GLFW_RELEASE != action)
    {
        switch (g_keyCodeMap[key])
        {
        case EventKeyboard::KeyCode::KEY_BACKSPACE:
            IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
            break;
        case EventKeyboard::KeyCode::KEY_HOME:
        case EventKeyboard::KeyCode::KEY_KP_HOME:
        case EventKeyboard::KeyCode::KEY_DELETE:
        case EventKeyboard::KeyCode::KEY_KP_DELETE:
        case EventKeyboard::KeyCode::KEY_END:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            IMEDispatcher::sharedDispatcher()->dispatchControlKey(g_keyCodeMap[key]);
            break;
        default:
            break;
        }
    }
}

void GLViewImpl::onGLFWCharCallback(GLFWwindow* /*window*/, unsigned int character)
{
    char16_t wcharString[2] = {(char16_t)character, 0};
    std::string utf8String;

    StringUtils::UTF16ToUTF8(wcharString, utf8String);
    static std::set<std::string> controlUnicode = {
        "\xEF\x9C\x80",  // up
        "\xEF\x9C\x81",  // down
        "\xEF\x9C\x82",  // left
        "\xEF\x9C\x83",  // right
        "\xEF\x9C\xA8",  // delete
        "\xEF\x9C\xA9",  // home
        "\xEF\x9C\xAB",  // end
        "\xEF\x9C\xAC",  // pageup
        "\xEF\x9C\xAD",  // pagedown
        "\xEF\x9C\xB9"   // clear
    };
    // Check for send control key
    if (controlUnicode.find(utf8String) == controlUnicode.end())
    {
        IMEDispatcher::sharedDispatcher()->dispatchInsertText(utf8String.c_str(), utf8String.size());
    }
}

void GLViewImpl::onGLFWWindowPosCallback(GLFWwindow* /*window*/, int x, int y)
{
    Director::getInstance()->setViewport();
    if (isFullscreen())
    {
        _monitor = getCurrentMonitor(_mainWindow);
    }
}

void GLViewImpl::onGLFWWindowSizeCallback(GLFWwindow* /*window*/, int w, int h)
{
    // should skip fullscreen
    if (isFullscreen())
    {
        return;
    }
    if (w && h && _resolutionPolicy != ResolutionPolicy::UNKNOWN)
    {
        const float frameWidth  = w / _frameZoomFactor;
        const float frameHeight = h / _frameZoomFactor;
        setFrameSize(frameWidth, frameHeight);
        Director::getInstance()->setViewport();

        /*
         x-studio spec, fix view size incorrect when window size changed.
         The original code behavior:
         1. first time enter full screen: w,h=1920,1080
         2. second or later enter full screen: will trigger 2 times WindowSizeCallback
           1). w,h=976,679
           2). w,h=1024,768

         @remark: we should use glfwSetWindowMonitor to control the window size in full screen mode
         @see also: updateWindowSize (call after enter/exit full screen mode)
        */
        updateDesignResolutionSize();

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_RESIZED, nullptr);
    }
}

void GLViewImpl::onGLFWWindowIconifyCallback(GLFWwindow* /*window*/, int iconified)
{
    if (iconified == GLFW_TRUE)
    {
        Application::getInstance()->applicationDidEnterBackground();
    }
    else
    {
        Application::getInstance()->applicationWillEnterForeground();
    }
}

void GLViewImpl::onGLFWWindowFocusCallback(GLFWwindow* /*window*/, int focused)
{
    if (focused == GLFW_TRUE)
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_FOCUSED, nullptr);
    }
    else
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GLViewImpl::EVENT_WINDOW_UNFOCUSED, nullptr);
    }
}

static bool loadFboExtensions()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) && !defined(CC_USE_ANGLE) && !defined(CC_USE_GFX)
    const char* gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

    // If the current opengl driver doesn't have framebuffers methods, check if an extension exists
    if (glGenFramebuffers == nullptr)
    {
        log("OpenGL: glGenFramebuffers is nullptr, try to detect an extension");
        if (strstr(gl_extensions, "ARB_framebuffer_object"))
        {
            log("OpenGL: ARB_framebuffer_object is supported");

            glIsRenderbuffer      = (PFNGLISRENDERBUFFERPROC)glfwGetProcAddress("glIsRenderbuffer");
            glBindRenderbuffer    = (PFNGLBINDRENDERBUFFERPROC)glfwGetProcAddress("glBindRenderbuffer");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glfwGetProcAddress("glDeleteRenderbuffers");
            glGenRenderbuffers    = (PFNGLGENRENDERBUFFERSPROC)glfwGetProcAddress("glGenRenderbuffers");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glfwGetProcAddress("glRenderbufferStorage");
            glGetRenderbufferParameteriv =
                (PFNGLGETRENDERBUFFERPARAMETERIVPROC)glfwGetProcAddress("glGetRenderbufferParameteriv");
            glIsFramebuffer          = (PFNGLISFRAMEBUFFERPROC)glfwGetProcAddress("glIsFramebuffer");
            glBindFramebuffer        = (PFNGLBINDFRAMEBUFFERPROC)glfwGetProcAddress("glBindFramebuffer");
            glDeleteFramebuffers     = (PFNGLDELETEFRAMEBUFFERSPROC)glfwGetProcAddress("glDeleteFramebuffers");
            glGenFramebuffers        = (PFNGLGENFRAMEBUFFERSPROC)glfwGetProcAddress("glGenFramebuffers");
            glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glfwGetProcAddress("glCheckFramebufferStatus");
            glFramebufferTexture1D   = (PFNGLFRAMEBUFFERTEXTURE1DPROC)glfwGetProcAddress("glFramebufferTexture1D");
            glFramebufferTexture2D   = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glfwGetProcAddress("glFramebufferTexture2D");
            glFramebufferTexture3D   = (PFNGLFRAMEBUFFERTEXTURE3DPROC)glfwGetProcAddress("glFramebufferTexture3D");
            glFramebufferRenderbuffer =
                (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glfwGetProcAddress("glFramebufferRenderbuffer");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)glfwGetProcAddress(
                "glGetFramebufferAttachmentParameteriv");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
        }
        else if (strstr(gl_extensions, "EXT_framebuffer_object"))
        {
            log("OpenGL: EXT_framebuffer_object is supported");
            glIsRenderbuffer      = (PFNGLISRENDERBUFFERPROC)glfwGetProcAddress("glIsRenderbufferEXT");
            glBindRenderbuffer    = (PFNGLBINDRENDERBUFFERPROC)glfwGetProcAddress("glBindRenderbufferEXT");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glfwGetProcAddress("glDeleteRenderbuffersEXT");
            glGenRenderbuffers    = (PFNGLGENRENDERBUFFERSPROC)glfwGetProcAddress("glGenRenderbuffersEXT");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glfwGetProcAddress("glRenderbufferStorageEXT");
            glGetRenderbufferParameteriv =
                (PFNGLGETRENDERBUFFERPARAMETERIVPROC)glfwGetProcAddress("glGetRenderbufferParameterivEXT");
            glIsFramebuffer      = (PFNGLISFRAMEBUFFERPROC)glfwGetProcAddress("glIsFramebufferEXT");
            glBindFramebuffer    = (PFNGLBINDFRAMEBUFFERPROC)glfwGetProcAddress("glBindFramebufferEXT");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glfwGetProcAddress("glDeleteFramebuffersEXT");
            glGenFramebuffers    = (PFNGLGENFRAMEBUFFERSPROC)glfwGetProcAddress("glGenFramebuffersEXT");
            glCheckFramebufferStatus =
                (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glfwGetProcAddress("glCheckFramebufferStatusEXT");
            glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)glfwGetProcAddress("glFramebufferTexture1DEXT");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glfwGetProcAddress("glFramebufferTexture2DEXT");
            glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)glfwGetProcAddress("glFramebufferTexture3DEXT");
            glFramebufferRenderbuffer =
                (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glfwGetProcAddress("glFramebufferRenderbufferEXT");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)glfwGetProcAddress(
                "glGetFramebufferAttachmentParameterivEXT");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmapEXT");
        }
        else if (strstr(gl_extensions, "GL_ANGLE_framebuffer_blit"))
        {
            log("OpenGL: GL_ANGLE_framebuffer_object is supported");

            glIsRenderbuffer      = (PFNGLISRENDERBUFFERPROC)glfwGetProcAddress("glIsRenderbufferOES");
            glBindRenderbuffer    = (PFNGLBINDRENDERBUFFERPROC)glfwGetProcAddress("glBindRenderbufferOES");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glfwGetProcAddress("glDeleteRenderbuffersOES");
            glGenRenderbuffers    = (PFNGLGENRENDERBUFFERSPROC)glfwGetProcAddress("glGenRenderbuffersOES");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glfwGetProcAddress("glRenderbufferStorageOES");
            // glGetRenderbufferParameteriv =
            // (PFNGLGETRENDERBUFFERPARAMETERIVPROC)glfwGetProcAddress("glGetRenderbufferParameterivOES");
            glIsFramebuffer      = (PFNGLISFRAMEBUFFERPROC)glfwGetProcAddress("glIsFramebufferOES");
            glBindFramebuffer    = (PFNGLBINDFRAMEBUFFERPROC)glfwGetProcAddress("glBindFramebufferOES");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glfwGetProcAddress("glDeleteFramebuffersOES");
            glGenFramebuffers    = (PFNGLGENFRAMEBUFFERSPROC)glfwGetProcAddress("glGenFramebuffersOES");
            glCheckFramebufferStatus =
                (PFNGLCHECKFRAMEBUFFERSTATUSPROC)glfwGetProcAddress("glCheckFramebufferStatusOES");
            glFramebufferRenderbuffer =
                (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glfwGetProcAddress("glFramebufferRenderbufferOES");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glfwGetProcAddress("glFramebufferTexture2DOES");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)glfwGetProcAddress(
                "glGetFramebufferAttachmentParameterivOES");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmapOES");
        }
        else
        {
            log("OpenGL: No framebuffers extension is supported");
            log("OpenGL: Any call to Fbo will crash!");
            return false;
        }
    }
#endif
    return true;
}

// helper
bool GLViewImpl::loadGL()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

#ifndef CC_USE_ANGLE
    if (!gladLoaderLoadEGL(EGL_DEFAULT_DISPLAY) || !gladLoadGLES2(glfwGetProcAddress))
    {
        ccMessageBox("Failed to Load glad", "OpenGL error");
        return false;
    }

    if (GLAD_GL_ES_VERSION_2_0 && glGenFramebuffers)
    {
        log("Ready for GLSL");
    }
    else
    {
        log("Not totally ready :(");
        return false;
    }
#endif // !CC_USE_ANGLE

    loadFboExtensions();

#endif //#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)

    return true;
}

NS_CC_END // end of namespace cocos2d;
