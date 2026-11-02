/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

https://axmol.dev/

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
#include "platform/android/CCApplication-android.h"
#include "platform/android/CCGLViewImpl-android.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCTextureCache.h"
#include "base/CCConfiguration.h"
#include "renderer/backend/gfx/DeviceGFX.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "base/threading/MessageQueue.h"
#include "platform/android/jni/JniHelper.h"

#include <android/log.h>
#include <android/api-level.h>
#include <jni.h>
#include <android/native_window_jni.h>
#include <memory>
#include <chrono>
#include <sys/syscall.h>
#include <unistd.h>


#define LOG_TAG "main"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void cocos_android_app_init(JNIEnv* env) __attribute__((weak));

USING_NS_CC;

namespace {
constexpr const char* HOST_TAG = "CocosRenderHost";
unsigned windowReferences = 0;
struct WindowRelease {
    void operator()(ANativeWindow* window) const {
        if (window) {
            ANativeWindow_release(window);
            --windowReferences;
        }
    }
};
std::unique_ptr<ANativeWindow, WindowRelease> hostWindow;
Director* hostDirector = nullptr;
jlong hostSession = 0;
jlong hostGeneration = 0;
jlong closedSession = 0;
bool hostResumed = false;
bool hostReady = false;
bool hostFailed = false;
bool appCreated = false;
bool firstPresent = false;
uint64_t presentBaseline = 0;
int hostWidth = 0;
int hostHeight = 0;
Size hostSurfaceSize;
enum class HostState { WaitingSurface, SurfaceReady, Detaching, Suspended, SurfaceFailed, Closing, Closed };
HostState hostState = HostState::WaitingSurface;
bool hostClosing = false;
bool hostDeviceLost = false;
bool hostUnrecoverableSurface = false;
bool applicationStarted = false;

void setHostState(HostState state)
{
    static const char* names[] = {"WaitingSurface", "SurfaceReady", "Detaching", "Suspended",
                                 "SurfaceFailed", "Closing", "Closed"};
    hostState = state;
    __android_log_print(ANDROID_LOG_INFO, HOST_TAG,
        "state=%s session=%lld generation=%lld resumed=%d windowRefs=%u",
        names[(int)state], (long long)hostSession, (long long)hostGeneration, hostResumed, windowReferences);
}

bool currentSurface(jlong session, jlong generation)
{
    const bool current = session == hostSession && generation == hostGeneration && session > closedSession;
    if (!current)
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG,
            "stale-event session=%lld generation=%lld current=%lld/%lld",
            (long long)session, (long long)generation, (long long)hostSession, (long long)hostGeneration);
    return current;
}

void syncDevice()
{
    if (auto* agent = cc::gfx::DeviceAgent::getInstance())
        agent->getMessageQueue()->kickAndWait();
}

void detachWindow()
{
    hostReady = false;
    hostSurfaceSize = Size::ZERO;
    if (hostWindow)
    {
        setHostState(HostState::Detaching);
        const auto started = std::chrono::steady_clock::now();
        if (!backend::DeviceGFX::detachSurface()) hostUnrecoverableSurface = true;
        hostDeviceLost = hostDeviceLost || backend::DeviceGFX::hasDeviceLost();
        syncDevice();
        hostWindow.reset();
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG, "detach-complete elapsedUs=%lld windowRefs=%u",
            (long long)std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now() - started).count(), windowReferences);
    }
    hostWidth = hostHeight = 0;
    if (!hostClosing)
        setHostState(hostDeviceLost || hostUnrecoverableSurface ? HostState::SurfaceFailed :
                     hostDirector ? HostState::Suspended : HostState::WaitingSurface);
}

int resizeWindow(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        hostReady = false;
        hostSurfaceSize = Size::ZERO;
        setHostState(HostState::WaitingSurface);
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG, "waiting-zero-size session=%lld generation=%lld size=%dx%d",
            (long long)hostSession, (long long)hostGeneration, width, height);
        return 0;
    }
    if (!hostWindow || !hostDirector || hostFailed)
        return hostFailed ? -1 : 0;
    if (hostWidth != width || hostHeight != height)
    {
        if (!backend::DeviceGFX::resizeSurface(width, height))
        {
            hostReady = false;
            hostFailed = true;
            hostDeviceLost = backend::DeviceGFX::hasDeviceLost();
            setHostState(HostState::SurfaceFailed);
            __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "surface-failed: resize deviceLost=%d", hostDeviceLost);
            return -1;
        }
        hostWidth = width;
        hostHeight = height;
        hostSurfaceSize = Size(float(width), float(height));
        auto* view = hostDirector->getOpenGLView();
        const auto design = view->getDesignResolutionSize();
        const auto policy = view->getResolutionPolicy();
        view->setFrameSize(width, height);
        if (design.width > 0 && design.height > 0 && policy != ResolutionPolicy::UNKNOWN)
            view->setDesignResolutionSize(design.width, design.height, policy);
        auto* device = backend::DeviceGFX::getInstance();
        backend::DeviceGFX::setSwapchainInfo(hostWindow.get(), device->getVsync(), width, height);
        hostDirector->getEventDispatcher()->dispatchCustomEvent("glview_window_resized");
        Application::getInstance()->applicationScreenSizeChanged(width, height);
    }
    hostSurfaceSize = Size(float(width), float(height));
    hostReady = true;
    setHostState(HostState::SurfaceReady);
    return 1;
}
}

// Called only on the engine thread, including during Application::run bootstrap.
Size cocos_android_render_host_size()
{
    return hostWindow && !hostClosing && !hostFailed ? hostSurfaceSize : Size::ZERO;
}

// GLView::end can run from Director::mainLoop before it deletes the device.
void cocos_android_render_host_ended()
{
    hostReady = false;
    hostSurfaceSize = Size::ZERO;
    hostResumed = false;
    hostClosing = true;
    // Director calls here before deleting its renderer/device. Drain and release
    // the window while the facade and its command buffers still exist.
    backend::DeviceGFX::shutdownSurface();
    syncDevice();
    hostWindow.reset();
    hostDirector = nullptr;
    closedSession = hostSession;
    applicationStarted = false;
    setHostState(HostState::Closed);
}

extern "C" {

// ndk break compatibility, refer to https://github.com/cocos2d/cocos2d-x/issues/16267 for detail information
// should remove it when using NDK r13 since NDK r13 will add back bsd_signal()
#if __ANDROID_API__ > 19
    #include <signal.h>
    #include <dlfcn.h>
typedef __sighandler_t (*bsd_signal_func_t)(int, __sighandler_t);
bsd_signal_func_t bsd_signal_func = NULL;

__sighandler_t bsd_signal(int s, __sighandler_t f)
{
    if (bsd_signal_func == NULL)
    {
        // For now (up to Android 7.0) this is always available
        bsd_signal_func = (bsd_signal_func_t)dlsym(RTLD_DEFAULT, "bsd_signal");

        if (bsd_signal_func == NULL)
        {
            __android_log_assert("", "bsd_signal_wrapper", "bsd_signal symbol not found!");
        }
    }
    return bsd_signal_func(s, f);
}
#endif  // __ANDROID_API__ > 19

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

JNIEXPORT jint JNICALL Java_org_cocos_lib_CocosRenderHost_nativeAttach(
    JNIEnv* env, jclass, jobject surface, jlong session, jlong generation,
    jint width, jint height)
{
    if (hostClosing || session <= closedSession || session < hostSession ||
        (session == hostSession && generation < hostGeneration))
    {
        currentSurface(session, generation);
        return 0;
    }
    if (hostDeviceLost || hostUnrecoverableSurface)
    {
        __android_log_print(ANDROID_LOG_ERROR, HOST_TAG,
            "render-host-terminal deviceLost=%d surfaceCleanupFailed=%d: restart application required",
            hostDeviceLost, hostUnrecoverableSurface);
        return -1;
    }
    const bool sameWindow = hostWindow && session == hostSession && generation == hostGeneration;
    if (sameWindow)
        return resizeWindow(width, height);
    detachWindow();
    if (hostDeviceLost || hostUnrecoverableSurface) return -1;
    hostSession = session;
    hostGeneration = generation;
    hostFailed = false;
    firstPresent = false;
    if (width <= 0 || height <= 0)
        return resizeWindow(0, 0);
    if (!surface)
        return -1;
    hostWindow.reset(ANativeWindow_fromSurface(env, surface));
    if (hostWindow) ++windowReferences;
    if (!hostWindow)
    {
        hostFailed = true;
        setHostState(HostState::SurfaceFailed);
        __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "surface-failed: ANativeWindow_fromSurface returned null");
        return -1;
    }

    // Publish the accepted attach dimensions before Lua's startup queries.
    hostSurfaceSize = Size(float(width), float(height));
    auto* config = Configuration::getInstance();
    auto preferred = cc::gfx::API::VULKAN;
    const int configured = config->getValue("GFXDesiredAPI", Value((int)preferred)).asInt();
    if (configured == (int)cc::gfx::API::VULKAN || configured == (int)cc::gfx::API::GLES3)
        preferred = (cc::gfx::API)configured;
    if (!cc::gfx::Device::getInstance())
    {
        cc::gfx::DeviceInfo info;
        auto* device = cc::gfx::DeviceManager::create(info, preferred);
        if (!device || device->getGfxAPI() == cc::gfx::API::UNKNOWN || device->getGfxAPI() == cc::gfx::API::GLES2)
        {
            __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "empty-device-rejected preferred=%d actual=%d",
                (int)preferred, device ? (int)device->getGfxAPI() : -1);
            if (device) { device->destroy(); delete device; }
            hostFailed = true;
            hostWindow.reset();
            setHostState(HostState::SurfaceFailed);
            return -1;
        }
        auto* agent = cc::gfx::DeviceAgent::getInstance();
        if (agent)
        {
            bool useThreads = config->getValue("GFXMultithreaded", Value(true)).asBool();
            agent->setMultithreaded(useThreads);
        }
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG,
            "device-ready preferred=%d actual=%d engineTid=%ld agent=%d multithreaded=%d validator=%d session=%lld generation=%lld size=%dx%d",
            (int)preferred, (int)device->getGfxAPI(), syscall(SYS_gettid), agent != nullptr,
            agent && agent->isMultithreaded(), cc::gfx::DeviceValidator::getInstance() != nullptr,
            (long long)session, (long long)generation, width, height);
    }
    backend::DeviceGFX::setSwapchainInfo(hostWindow.get(), true, width, height);
    if (!appCreated)
    {
        cocos_android_app_init(env);
        appCreated = true;
    }
    if (!hostDirector)
    {
        if (applicationStarted || hostClosing)
            return -1;
        hostDirector = Director::getInstance();
        auto* view = GLViewImpl::create("cocos-gfx");
        if (!view)
        {
            hostFailed = true;
            hostUnrecoverableSurface = true;
            setHostState(HostState::SurfaceFailed);
            return -1;
        }
        view->setFrameSize(width, height);
        hostDirector->setOpenGLView(view);
        if (Application::getInstance()->run() != -1)
        {
            hostFailed = true;
            hostUnrecoverableSurface = true;
            setHostState(HostState::SurfaceFailed);
            __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "surface-failed: application launch failed");
            return -1;
        }
        applicationStarted = true;
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG, "application-started session=%lld (once per process)",
            (long long)session);
        // Activity may have paused while bootstrap was pending.
        if (!hostResumed)
            Application::getInstance()->applicationDidEnterBackground();
    }
    else if (!backend::DeviceGFX::attachSurface(hostWindow.get(), width, height))
    {
        hostFailed = true;
        setHostState(HostState::SurfaceFailed);
        __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "surface-failed: reattach failed");
        return -1;
    }
    presentBaseline = backend::DeviceGFX::getPresentCount();
    return resizeWindow(width, height);
}

JNIEXPORT jint JNICALL Java_org_cocos_lib_CocosRenderHost_nativeResize(JNIEnv*, jclass,
    jlong session, jlong generation, jint width, jint height)
{
    if (!currentSurface(session, generation)) return 0;
    return resizeWindow(width, height);
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderHost_nativeDetach(JNIEnv*, jclass,
    jlong session, jlong generation)
{
    if (!currentSurface(session, generation)) return;
    detachWindow();
    __android_log_print(ANDROID_LOG_INFO, HOST_TAG, "surface-detached session=%lld generation=%lld",
        (long long)session, (long long)generation);
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderHost_nativeSetResumed(JNIEnv*, jclass,
    jlong session, jboolean resumed)
{
    if (hostClosing || session <= closedSession || session < hostSession) return;
    if (session > hostSession)
    {
        detachWindow();
        hostSession = session;
        hostGeneration = 0;
    }
    const bool value = resumed == JNI_TRUE;
    if (value == hostResumed) return;
    hostResumed = value;
    if (!hostDirector) return;
    if (value)
    {
        Application::getInstance()->applicationWillEnterForeground();
        hostDirector->getEventDispatcher()->dispatchCustomEvent(EVENT_COME_TO_FOREGROUND);
    }
    else
    {
        Application::getInstance()->applicationDidEnterBackground();
        hostDirector->getEventDispatcher()->dispatchCustomEvent(EVENT_COME_TO_BACKGROUND);
    }
}

JNIEXPORT jint JNICALL Java_org_cocos_lib_CocosRenderHost_nativeRender(JNIEnv*, jclass,
    jlong session, jlong generation)
{
    if (!currentSurface(session, generation)) return 0;
    if (!hostReady || !hostResumed || !hostDirector)
        return hostFailed ? -1 : 0;
    hostDirector->mainLoop();
    if (!hostDirector) return -1;
    syncDevice();
    if (backend::DeviceGFX::hasSurfaceFailed())
    {
        hostReady = false;
        hostFailed = true;
        hostDeviceLost = backend::DeviceGFX::hasDeviceLost();
        setHostState(HostState::SurfaceFailed);
        __android_log_print(ANDROID_LOG_ERROR, HOST_TAG, "surface-failed session=%lld generation=%lld deviceLost=%d (no API switch after bootstrap)",
            (long long)session, (long long)generation, hostDeviceLost);
        return -1;
    }
    if (!firstPresent && backend::DeviceGFX::getPresentCount() > presentBaseline)
    {
        firstPresent = true;
        __android_log_print(ANDROID_LOG_INFO, HOST_TAG, "first-present actual=%d session=%lld generation=%lld size=%dx%d engineTid=%ld",
            (int)cc::gfx::Device::getInstance()->getGfxAPI(), (long long)session,
            (long long)generation, hostWidth, hostHeight, syscall(SYS_gettid));
    }
    return 1;
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderHost_nativeClose(JNIEnv*, jclass, jlong session)
{
    if (session != hostSession || session <= closedSession) return;
    closedSession = session;
    hostResumed = false;
    hostClosing = true;
    setHostState(HostState::Closing);
    detachWindow();
    backend::DeviceGFX::shutdownSurface();
    // Final destruction is separate from a temporary Surface detach.
    if (hostDirector)
    {
        auto* director = hostDirector;
        hostDirector = nullptr;
        director->end();
        director->mainLoop();
    }
    setHostState(HostState::Closed);
}

JNIEXPORT jintArray JNICALL Java_org_cocos_lib_CocosActivity_getGLContextAttrs(JNIEnv* env, jclass)
{
    cocos2d::Application::getInstance()->initGLContextAttrs();
    GLContextAttrs _glContextAttrs = GLView::getGLContextAttrs();

    int tmp[7] = {_glContextAttrs.redBits,           _glContextAttrs.greenBits, _glContextAttrs.blueBits,
                  _glContextAttrs.alphaBits,         _glContextAttrs.depthBits, _glContextAttrs.stencilBits,
                  _glContextAttrs.multisamplingCount};

    jintArray glContextAttrsJava = env->NewIntArray(7);
    env->SetIntArrayRegion(glContextAttrsJava, 0, 7, tmp);

    return glContextAttrsJava;
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeOnSurfaceChanged(JNIEnv*, jclass, jint w, jint h)
{
    cocos2d::Application::getInstance()->applicationScreenSizeChanged(w, h);
}

}
