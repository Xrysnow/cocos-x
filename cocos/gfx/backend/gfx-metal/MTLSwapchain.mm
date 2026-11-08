/****************************************************************************
 Copyright (c) 2021-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#import "../gfx-base/GFXDef-common.h"
#import "MTLSwapchain.h"
#if CC_PLATFORM != CC_PLATFORM_MACOS
    #import <UIKit/UIView.h>
#endif
#import "MTLGPUObjects.h"
#import "MTLDevice.h"
#import "base/Log.h"
#include <cstdlib>

#if CC_PLATFORM == CC_PLATFORM_MACOS && __has_feature(objc_arc)
#error "GFX Metal on macOS requires -fno-objc-arc"
#endif

namespace cc {
namespace gfx {
namespace {
uint32_t diagnosticCount(const char *name, uint32_t fallback = 0) {
#if CC_DEBUG > 0
    const char *value = std::getenv(name);
    if (value && *value) {
        char *end = nullptr;
        const auto count = std::strtoul(value, &end, 10);
        if (end != value && !*end && count <= UINT32_MAX) {
            return static_cast<uint32_t>(count);
        }
    }
#endif
    return fallback;
}
} // namespace

CCMTLSwapchain::CCMTLSwapchain() = default;

CCMTLSwapchain::~CCMTLSwapchain() {
    destroy();
}

void CCMTLSwapchain::doInit(const SwapchainInfo &info) {
    _trace = diagnosticCount("CC_P2_TRACE_METAL") != 0;
    _nilDrawableBegin = diagnosticCount("CC_P2_NIL_DRAWABLE_BEGIN", 1);
    _nilDrawableCount = diagnosticCount("CC_P2_NIL_DRAWABLE_COUNT");
    if (diagnosticCount("CC_P2_FAIL_SURFACE")) {
        CC_LOG_ERROR("GFX Metal: injected surface initialization failure");
        return;
    }
    if (!info.width || !info.height) {
        CC_LOG_ERROR("GFX Metal: swapchain requires positive framebuffer dimensions");
        return;
    }

    CAMetalLayer *layer = nil;
#if CC_PLATFORM == CC_PLATFORM_MACOS
    // AppKit views must only be accessed on the main thread. The bridge resolves
    // this layer before any DeviceAgent message can run on the device thread.
    layer = static_cast<CAMetalLayer *>(info.nativeRenderSurface);
#elif CC_EDITOR
    layer = static_cast<CAMetalLayer *>(info.windowHandle);
#else
    layer = static_cast<CAMetalLayer *>(static_cast<UIView *>(info.windowHandle).layer);
#endif
    auto *device = CCMTLDevice::getInstance();
    id<MTLDevice> mtlDevice = device ? static_cast<id<MTLDevice>>(device->getMTLDevice()) : nil;
    if (![layer isKindOfClass:[CAMetalLayer class]] || !mtlDevice) {
        CC_LOG_ERROR("GFX Metal: missing CAMetalLayer or actual Metal device");
        return;
    }
    if (layer.device && layer.device != mtlDevice) {
        CC_LOG_ERROR("GFX Metal: surface belongs to a different Metal device");
        return;
    }
    if (layer.pixelFormat != MTLPixelFormatInvalid && layer.pixelFormat != MTLPixelFormatBGRA8Unorm) {
        CC_LOG_ERROR("GFX Metal: surface pixel format must be BGRA8Unorm");
        return;
    }

    _gpuSwapchainObj = ccnew CCMTLGPUSwapChainObject;
    _gpuSwapchainObj->mtlLayer = [layer retain];
    layer.device = mtlDevice;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.framebufferOnly = NO;
    layer.drawableSize = CGSizeMake(info.width, info.height);
    if (@available(macOS 10.13, iOS 11.0, *)) {
        layer.allowsNextDrawableTimeout = YES;
    }
    setVSyncMode(_vsyncMode);

    _colorTexture = ccnew CCMTLTexture;
    _depthStencilTexture = ccnew CCMTLTexture;
    SwapchainTextureInfo textureInfo;
    textureInfo.swapchain = this;
    textureInfo.format = Format::BGRA8;
    textureInfo.width = info.width;
    textureInfo.height = info.height;
    initTexture(textureInfo, _colorTexture);
    textureInfo.format = Format::DEPTH_STENCIL;
    initTexture(textureInfo, _depthStencilTexture);
    if (!depthStencilTexture()->getMTLTexture()) {
        CC_LOG_ERROR("GFX Metal: failed to allocate swapchain depth/stencil attachment");
        doDestroy();
        return;
    }

    device->registerSwapchain(this);
    _registered = true;
    _surfaceInitialized.store(true);
    if (_trace) {
        CC_LOG_INFO("P2 Metal surface: layer=%p device=%p B=%ux%u format=%lu timeout=1",
                    layer, mtlDevice, info.width, info.height, static_cast<unsigned long>(layer.pixelFormat));
    }
}

void CCMTLSwapchain::setVSyncMode(VsyncMode mode) {
    _vsyncMode = mode;
    if (!_gpuSwapchainObj || !_gpuSwapchainObj->mtlLayer) return;
    auto *layer = _gpuSwapchainObj->mtlLayer;
    // Presentation is driven by the Metal queue, including on DeviceAgent's
    // thread, rather than by an AppKit/Core Animation transaction.
    layer.presentsWithTransaction = NO;
#if CC_PLATFORM == CC_PLATFORM_MACOS
    switch (mode) {
        case VsyncMode::OFF:
            layer.displaySyncEnabled = NO;
            break;
        case VsyncMode::ON:
        case VsyncMode::RELAXED:
        case VsyncMode::MAILBOX:
        case VsyncMode::HALF:
            layer.displaySyncEnabled = YES;
            break;
        default:
            layer.displaySyncEnabled = YES;
            break;
    }
    if (_trace) {
        CC_LOG_INFO("P2 Metal vsync: requested=%u displaySyncEnabled=%d presentsWithTransaction=%d",
                    static_cast<unsigned>(mode), layer.displaySyncEnabled, layer.presentsWithTransaction);
    }
#endif
}

void CCMTLSwapchain::doDestroy() {
    _surfaceInitialized.store(false);
    if (!_gpuSwapchainObj) return;
    auto *device = CCMTLDevice::getInstance();
    if (device) device->waitForIdle();
    if (_registered && device) device->unRegisterSwapchain(this);
    _registered = false;
    release();
    CC_SAFE_DESTROY_NULL(_colorTexture);
    CC_SAFE_DESTROY_NULL(_depthStencilTexture);
    [_gpuSwapchainObj->mtlLayer release];
    _gpuSwapchainObj->mtlLayer = nil;
    CC_SAFE_DELETE(_gpuSwapchainObj);
    if (_trace) CC_LOG_INFO("P2 Metal surface destroyed: drawable=0 layer=0 registered=0");
}

void CCMTLSwapchain::doDestroySurface() {
    if (!_gpuSwapchainObj) return;
    CCMTLDevice::getInstance()->waitForIdle();
    release();
    _surfaceInitialized.store(false);
    [_gpuSwapchainObj->mtlLayer release];
    _gpuSwapchainObj->mtlLayer = nil;
}

void CCMTLSwapchain::doResize(uint32_t width, uint32_t height, SurfaceTransform /*transform*/) {
    if (!isSurfaceInitialized() || !width || !height) return;
    CCMTLDevice::getInstance()->waitForIdle();
    release();
    const auto oldWidth = getWidth();
    const auto oldHeight = getHeight();
    _depthStencilTexture->resize(width, height);
    auto depth = depthStencilTexture()->getMTLTexture();
    if (!depth || depth.width != width || depth.height != height) {
        // Texture::resize publishes its requested size even if allocation failed.
        // Keep the old dimensions visible so a later frame can safely retry.
        SwapchainTextureInfo info;
        info.swapchain = this;
        info.format = Format::DEPTH_STENCIL;
        info.width = oldWidth;
        info.height = oldHeight;
        updateTextureInfo(info, _depthStencilTexture);
        CC_LOG_ERROR("GFX Metal: failed to resize depth/stencil attachment");
        return;
    }
    _colorTexture->resize(width, height);
    _gpuSwapchainObj->mtlLayer.drawableSize = CGSizeMake(width, height);
    ++_generation;
}

CCMTLTexture *CCMTLSwapchain::colorTexture() {
    return static_cast<CCMTLTexture *>(_colorTexture.get());
}

CCMTLTexture *CCMTLSwapchain::depthStencilTexture() {
    return static_cast<CCMTLTexture *>(_depthStencilTexture.get());
}

id<CAMetalDrawable> CCMTLSwapchain::currentDrawable() {
    return _gpuSwapchainObj ? _gpuSwapchainObj->currentDrawable : nil;
}

void CCMTLSwapchain::release() {
    _drawableAcquired.store(false);
    if (!_gpuSwapchainObj) return;
    auto drawable = _gpuSwapchainObj->currentDrawable;
    _gpuSwapchainObj->currentDrawable = nil;
    if (_colorTexture) colorTexture()->update();
    [drawable release];
}

void CCMTLSwapchain::releaseAcquiredDrawable() {
    release();
}

void CCMTLSwapchain::acquire() {
    // A previous unsubmitted acquisition must not be reused by the next frame.
    release();
    if (!isSurfaceInitialized()) return;
    ++_acquireCount;
    const bool injectNil = _acquireCount >= _nilDrawableBegin &&
                          _acquireCount - _nilDrawableBegin < _nilDrawableCount;
    @autoreleasepool {
        // Exactly one attempt per frame. allowsNextDrawableTimeout permits nil;
        // no retry loop can prevent event processing and window restoration.
        if (!injectNil) {
            _gpuSwapchainObj->currentDrawable = [[_gpuSwapchainObj->mtlLayer nextDrawable] retain];
        }
        auto texture = [currentDrawable() texture];
        auto depth = depthStencilTexture()->getMTLTexture();
        if (texture && depth && texture.width == getWidth() && texture.height == getHeight() &&
            depth.width == getWidth() && depth.height == getHeight() &&
            texture.pixelFormat == MTLPixelFormatBGRA8Unorm &&
            texture.device == _gpuSwapchainObj->mtlLayer.device) {
            colorTexture()->update();
            _drawableAcquired.store(true);
        } else {
            release();
        }
    }
    const bool acquired = hasAcquiredDrawable();
    if (_trace && (!_acquireLogged || acquired != _lastAcquireResult)) {
        CC_LOG_INFO("P2 Metal acquire: attempt=%llu drawable=%d injected=%d B=%ux%u",
                    static_cast<unsigned long long>(_acquireCount), acquired, injectNil, getWidth(), getHeight());
    }
    _acquireLogged = true;
    _lastAcquireResult = acquired;
}

void CCMTLSwapchain::doCreateSurface(void * /*windowHandle*/) {
    CC_LOG_ERROR("GFX Metal: replace a native surface by recreating the swapchain with SwapchainInfo");
}

} // namespace gfx
} // namespace cc
