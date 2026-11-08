/****************************************************************************
 Copyright (c) 2021-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

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

#include <cstdlib>
#include "GLES3Swapchain.h"
#include "GLES3Device.h"
#include "GLES3GPUObjects.h"
#include "GLES3Swapchain.h"
#include "GLES3Texture.h"

#if CC_SWAPPY_ENABLED
    #include "platform/android/AndroidPlatform.h"
    #include "swappy/swappyGL.h"
#endif

#if (CC_PLATFORM == CC_PLATFORM_ANDROID)
    #include "android/native_window.h"
#elif CC_PLATFORM == CC_PLATFORM_OHOS
    #include <native_layer.h>
    #include <native_layer_jni.h>
#endif

namespace cc {
namespace gfx {

GLES3Swapchain::GLES3Swapchain() {
    _typedID = generateObjectID<decltype(this)>();
    _surfaceStatus = SurfaceStatus::UNINITIALIZED;
}

GLES3Swapchain::~GLES3Swapchain() {
    destroy();
}

void GLES3Swapchain::doInit(const SwapchainInfo &info) {
    auto width = static_cast<int32_t>(info.width);
    auto height = static_cast<int32_t>(info.height);
    const auto *context = GLES3Device::getInstance()->context();
    _gpuSwapchain = ccnew GLES3GPUSwapchain;
    _surfaceStatus = SurfaceStatus::FAILED;
    if (!info.windowHandle || !info.width || !info.height) {
        _surfaceStatus = (!info.width || !info.height) ? SurfaceStatus::ZERO_SIZE : SurfaceStatus::SURFACE_LOST;
        CC_LOG_ERROR("GLES3 swapchain rejected missing window/zero size (%ux%u)", info.width, info.height);
        return;
    }
#if CC_PLATFORM == CC_PLATFORM_LINUX
    auto window = reinterpret_cast<EGLNativeWindowType>(info.windowHandle);
#else
    auto *window = reinterpret_cast<EGLNativeWindowType>(info.windowHandle);
#endif

#if CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_OHOS
    EGLint nFmt;
    if (eglGetConfigAttrib(context->eglDisplay, context->eglConfig, EGL_NATIVE_VISUAL_ID, &nFmt) == EGL_FALSE) {
        CC_LOG_ERROR("Getting configuration attributes failed.");
        return;
    }

    #if CC_SWAPPY_ENABLED
    bool enableSwappy = true;
    auto *platform = static_cast<AndroidPlatform *>(cc::BasePlatform::getPlatform());
    enableSwappy &= SwappyGL_init(static_cast<JNIEnv *>(platform->getEnv()), static_cast<jobject>(platform->getActivity()));
    int32_t fps = cc::BasePlatform::getPlatform()->getFps();
    if (enableSwappy) {
        if (!fps)
            SwappyGL_setSwapIntervalNS(SWAPPY_SWAP_60FPS);
        else
            SwappyGL_setSwapIntervalNS(1000000000L / fps); //ns
        enableSwappy &= SwappyGL_setWindow(window);
        _gpuSwapchain->swappyEnabled = enableSwappy;
    } else {
        CC_LOG_ERROR("Failed to enable Swappy in current GL swapchain, fallback instead.");
    }

    #endif

    #if CC_PLATFORM == CC_PLATFORM_ANDROID
    ANativeWindow_setBuffersGeometry(window, width, height, nFmt);
    #elif CC_PLATFORM == CC_PLATFORM_OHOS
    NativeLayerHandle(window, NativeLayerOps::SET_WIDTH_AND_HEIGHT, width, height);
    NativeLayerHandle(window, NativeLayerOps::SET_FORMAT, nFmt);
    #endif
#endif

    _gpuSwapchain->eglSurface = eglCreateWindowSurface(context->eglDisplay, context->eglConfig, window, nullptr);
    if (_gpuSwapchain->eglSurface == EGL_NO_SURFACE) {
        CC_LOG_ERROR("Create window surface failed: 0x%x", eglGetError());
        return;
    }

    switch (_vsyncMode) {
        case VsyncMode::OFF: _gpuSwapchain->eglSwapInterval = 0; break;
        case VsyncMode::ON:
        case VsyncMode::RELAXED: _gpuSwapchain->eglSwapInterval = 1; break;
        case VsyncMode::MAILBOX: _gpuSwapchain->eglSwapInterval = 0; break;
        case VsyncMode::HALF: _gpuSwapchain->eglSwapInterval = 2; break;
        default: break;
    }

    ///////////////////// Texture Creation /////////////////////

    _colorTexture = ccnew GLES3Texture;
    _depthStencilTexture = ccnew GLES3Texture;

    SwapchainTextureInfo textureInfo;
    textureInfo.swapchain = this;
    textureInfo.format = Format::RGBA8;
    textureInfo.width = width;
    textureInfo.height = height;
    initTexture(textureInfo, _colorTexture);

    textureInfo.format = Format::DEPTH_STENCIL;
    initTexture(textureInfo, _depthStencilTexture);

    _gpuSwapchain->gpuColorTexture = static_cast<GLES3Texture *>(_colorTexture.get())->gpuTexture();
    _surfaceStatus = SurfaceStatus::READY;
    ++_generation;
}

void GLES3Swapchain::doDestroy() {
    _drawableAcquired = false;
    if (!_gpuSwapchain) return;

#if CC_SWAPPY_ENABLED
    if (_gpuSwapchain->swappyEnabled) {
        SwappyGL_destroy();
    }
#endif

    CC_SAFE_DESTROY(_depthStencilTexture)
    CC_SAFE_DESTROY(_colorTexture)
    doDestroySurface();
    if (_gpuSwapchain->eglSurface != EGL_NO_SURFACE) {
        CC_LOG_ERROR("FATAL: GLES3 final destruction cannot retire the retained EGLSurface; aborting process");
        std::abort();
    }
    CC_SAFE_DELETE(_gpuSwapchain);
}

void GLES3Swapchain::doResize(uint32_t width, uint32_t height, SurfaceTransform /*transform*/) {
    _drawableAcquired = false;
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) return;
    if (!width || !height) {
        _surfaceStatus = SurfaceStatus::ZERO_SIZE;
        return;
    }
    if (!_colorTexture || !_depthStencilTexture) return;
    // Complete the old default-framebuffer work before changing attachment info.
    // doDestroySurface binds the persistent pbuffer, preserving the EGL context.
    doDestroySurface();
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST || _surfaceStatus.load() == SurfaceStatus::FAILED) return;
    _colorTexture->resize(width, height);
    _depthStencilTexture->resize(width, height);

    if (_windowHandle) {
        doCreateSurface(_windowHandle);
    }
}

void GLES3Swapchain::doDestroySurface() {
    _drawableAcquired = false;
    if (_surfaceStatus.load() != SurfaceStatus::DEVICE_LOST)
        _surfaceStatus = SurfaceStatus::UNINITIALIZED;
    if (!_gpuSwapchain) return;
    if (_gpuSwapchain->eglSurface != EGL_NO_SURFACE) {
        auto *context = GLES3Device::getInstance()->context();
        const auto surface = _gpuSwapchain->eglSurface;
        const auto currentContext = eglGetCurrentContext();
        const bool ownedWindowContext = (currentContext != EGL_NO_CONTEXT && currentContext == context->eglDefaultContext) ||
            eglGetCurrentSurface(EGL_DRAW) == surface || eglGetCurrentSurface(EGL_READ) == surface;
        const auto detached = [surface]() {
            return eglGetCurrentSurface(EGL_DRAW) != surface && eglGetCurrentSurface(EGL_READ) != surface;
        };
        // Detach the old EGLSurface while its Android Surface is still valid.
        if (currentContext != EGL_NO_CONTEXT) glFinish();
        const bool preserved = context->bindContext(true);
        if (!preserved) {
            const auto pbufferError = context->lastError;
            // Safely losing the current context is terminal for this device;
            // never resume the scene with incomplete GL state/resource ownership.
            const bool unbound = context->bindContext(false);
            const auto unbindError = context->lastError;
            _surfaceStatus = pbufferError == EGL_CONTEXT_LOST || unbindError == EGL_CONTEXT_LOST
                ? SurfaceStatus::DEVICE_LOST : SurfaceStatus::FAILED;
            if (!unbound || !detached()) {
                const bool released = eglReleaseThread && eglReleaseThread() == EGL_TRUE;
                const auto releaseError = released ? EGL_SUCCESS : eglGetError();
                CC_LOG_ERROR("GLES3 detach fallback: pbuffer=0x%x unbind=0x%x releaseThread=%d error=0x%x",
                             pbufferError, unbindError, released, releaseError);
            }
            if (!ownedWindowContext || !detached()) {
                CC_LOG_ERROR("FATAL: GLES3 cannot prove old EGLSurface is unbound; aborting process before Surface destruction acknowledgement");
                std::abort();
            }
            CC_LOG_ERROR("GLES3 window safely unbound but context preservation failed (0x%x); rendering stopped, application restart required",
                         pbufferError);
        } else if (!detached()) {
            CC_LOG_ERROR("FATAL: GLES3 pbuffer bind left the old EGLSurface current; aborting process");
            std::abort();
        }
        if (eglDestroySurface(context->eglDisplay, surface) == EGL_FALSE) {
            const auto error = eglGetError();
            if (_surfaceStatus.load() != SurfaceStatus::DEVICE_LOST)
                _surfaceStatus = error == EGL_CONTEXT_LOST ? SurfaceStatus::DEVICE_LOST : SurfaceStatus::FAILED;
            CC_LOG_ERROR("Destroy window surface failed: 0x%x; retaining EGLSurface for cleanup", error);
            return;
        }
        _gpuSwapchain->eglSurface = EGL_NO_SURFACE;
    }
}

void GLES3Swapchain::doCreateSurface(void *windowHandle) {
    _drawableAcquired = false;
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) return;
    if (_surfaceStatus.load() == SurfaceStatus::FAILED && _gpuSwapchain && _gpuSwapchain->eglSurface != EGL_NO_SURFACE) {
        CC_LOG_ERROR("Cannot rebind while a failed EGLSurface destruction is pending");
        return;
    }
    _surfaceStatus = SurfaceStatus::FAILED;
    if (!_gpuSwapchain || !_colorTexture || !_depthStencilTexture || !windowHandle) return;
    auto *context = GLES3Device::getInstance()->context();
#if CC_PLATFORM == CC_PLATFORM_LINUX
    auto window = reinterpret_cast<EGLNativeWindowType>(windowHandle);
#else
    auto *window = reinterpret_cast<EGLNativeWindowType>(windowHandle);
#endif

    EGLint nFmt = 0;
    if (eglGetConfigAttrib(context->eglDisplay, context->eglConfig, EGL_NATIVE_VISUAL_ID, &nFmt) == EGL_FALSE) {
        CC_LOG_ERROR("Getting configuration attributes failed.");
        return;
    }

    auto width = static_cast<int>(_colorTexture->getWidth());
    auto height = static_cast<int>(_colorTexture->getHeight());
    CC_UNUSED_PARAM(width);
    CC_UNUSED_PARAM(height);

#if CC_SWAPPY_ENABLED
    if (_gpuSwapchain->swappyEnabled) {
        _gpuSwapchain->swappyEnabled &= SwappyGL_setWindow(window);
    }
#endif

#if CC_PLATFORM == CC_PLATFORM_ANDROID
    ANativeWindow_setBuffersGeometry(window, width, height, nFmt);
#elif CC_PLATFORM == CC_PLATFORM_OHOS
    NativeLayerHandle(window, NativeLayerOps::SET_WIDTH_AND_HEIGHT, width, height);
    NativeLayerHandle(window, SET_FORMAT, nFmt);
#endif

    if (_gpuSwapchain->eglSurface == EGL_NO_SURFACE) {
        _gpuSwapchain->eglSurface = eglCreateWindowSurface(context->eglDisplay, context->eglConfig, window, nullptr);
        if (_gpuSwapchain->eglSurface == EGL_NO_SURFACE) {
            const auto error = eglGetError();
            _surfaceStatus = error == EGL_CONTEXT_LOST ? SurfaceStatus::DEVICE_LOST :
                (error == EGL_BAD_SURFACE || error == EGL_BAD_NATIVE_WINDOW ? SurfaceStatus::SURFACE_LOST : SurfaceStatus::FAILED);
            CC_LOG_ERROR("Recreate window surface failed: 0x%x", error);
            return;
        }
    }

    if (!context->makeCurrent(_gpuSwapchain, _gpuSwapchain)) {
        _surfaceStatus = context->lastError == EGL_CONTEXT_LOST ? SurfaceStatus::DEVICE_LOST : SurfaceStatus::FAILED;
        return;
    }
    _surfaceStatus = SurfaceStatus::READY;
    ++_generation;
}

bool GLES3Swapchain::acquireDrawable() {
    _drawableAcquired = false;
    if (!isSurfaceInitialized() || !_gpuSwapchain || _gpuSwapchain->eglSurface == EGL_NO_SURFACE) return false;
    auto *context = GLES3Device::getInstance()->context();
    if (!context->makeCurrent(_gpuSwapchain, _gpuSwapchain)) {
        _surfaceStatus = context->lastError == EGL_CONTEXT_LOST ? SurfaceStatus::DEVICE_LOST : SurfaceStatus::SURFACE_LOST;
        return false;
    }
    _drawableAcquired = true;
    return true;
}

void GLES3Swapchain::presentDrawable() {
    if (!_drawableAcquired.exchange(false)) return;
    const auto result = GLES3Device::getInstance()->context()->present(_gpuSwapchain);
    if (result == EGL_SUCCESS) {
        ++_presentCount;
    } else {
        _surfaceStatus = result == EGL_CONTEXT_LOST ? SurfaceStatus::DEVICE_LOST :
            (result == EGL_BAD_SURFACE || result == EGL_BAD_NATIVE_WINDOW ? SurfaceStatus::SURFACE_LOST : SurfaceStatus::FAILED);
    }
}

} // namespace gfx
} // namespace cc
