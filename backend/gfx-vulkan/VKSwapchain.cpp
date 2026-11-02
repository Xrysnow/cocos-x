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

#include "VKSwapchain.h"
#include "VKCommands.h"
#include "VKDevice.h"
#include "VKGPUObjects.h"
#include "VKQueue.h"
#include "VKRenderPass.h"
#include "VKTexture.h"
#include "VKUtils.h"

#if CC_SWAPPY_ENABLED
    #include "platform/android/AndroidPlatform.h"
    #include "swappy/swappyVk.h"
    #include "swappy/swappy_common.h"
#endif

using cc::gfx::VsyncMode;

namespace {
// human-readable name for a VkPresentModeKHR
const char *presentModeName(VkPresentModeKHR mode) {
    switch (mode) {
        case VK_PRESENT_MODE_IMMEDIATE_KHR: return "IMMEDIATE";
        case VK_PRESENT_MODE_MAILBOX_KHR: return "MAILBOX";
        case VK_PRESENT_MODE_FIFO_KHR: return "FIFO";
        case VK_PRESENT_MODE_FIFO_RELAXED_KHR: return "FIFO_RELAXED";
        case VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR: return "SHARED_DEMAND_REFRESH";
        case VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR: return "SHARED_CONTINUOUS_REFRESH";
        default: return "UNKNOWN";
    }
}

// best present mode for vsyncMode from the surface-supported set; shared by doInit and
// every (re)creation so runtime setVSyncMode() toggles take effect
VkPresentModeKHR selectPresentModeForVsync(VsyncMode vsyncMode, const ccstd::vector<VkPresentModeKHR> &supportedModes) {
    ccstd::vector<VkPresentModeKHR> priorityList;
    switch (vsyncMode) {
        case VsyncMode::OFF: priorityList = {VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR}; break;
        case VsyncMode::ON: priorityList = {VK_PRESENT_MODE_FIFO_KHR}; break;
        case VsyncMode::RELAXED: priorityList = {VK_PRESENT_MODE_FIFO_RELAXED_KHR, VK_PRESENT_MODE_FIFO_KHR}; break;
        case VsyncMode::MAILBOX: priorityList = {VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR}; break;
        case VsyncMode::HALF: priorityList = {VK_PRESENT_MODE_FIFO_KHR}; break; // no easy fallback
    }

    VkPresentModeKHR best = VK_PRESENT_MODE_FIFO_KHR;

    // UNASSIGNED-BestPractices-vkCreateSwapchainKHR-swapchain-presentmode-not-fifo
#if !defined(VK_USE_PLATFORM_ANDROID_KHR)
    for (VkPresentModeKHR presentMode : priorityList) {
        if (std::find(supportedModes.begin(), supportedModes.end(), presentMode) != supportedModes.end()) {
            best = presentMode;
            break;
        }
    }
#endif

    return best;
}
} // namespace

namespace cc {
namespace gfx {

CCVKSwapchain::CCVKSwapchain() {
    _typedID = generateObjectID<decltype(this)>();
    _preRotationEnabled = ENABLE_PRE_ROTATION;
    _surfaceStatus = SurfaceStatus::UNINITIALIZED;
}

CCVKSwapchain::~CCVKSwapchain() {
    destroy();
}

void CCVKSwapchain::doInit(const SwapchainInfo &info) {
    auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();
    _gpuSwapchain = ccnew CCVKGPUSwapchain;
    gpuDevice->swapchains.insert(_gpuSwapchain);

    _surfaceStatus = SurfaceStatus::FAILED;
    if (!info.windowHandle || !info.width || !info.height) {
        _surfaceStatus = (!info.width || !info.height) ? SurfaceStatus::ZERO_SIZE : SurfaceStatus::SURFACE_LOST;
        CC_LOG_ERROR("Vulkan swapchain rejected missing window/zero size (%ux%u)", info.width, info.height);
        return;
    }
    createVkSurface();
    if (_gpuSwapchain->vkSurface == VK_NULL_HANDLE) return;
    const auto checkResult = [this](VkResult result) {
        if (result == VK_SUCCESS) return true;
        setAcquireResult(result);
        CC_LOG_ERROR("Vulkan swapchain initialization failed: %d", result);
        return false;
    };

    ///////////////////// Parameter Selection /////////////////////

    uint32_t queueFamilyPropertiesCount = utils::toUint(gpuContext->queueFamilyProperties.size());
    _gpuSwapchain->queueFamilyPresentables.resize(queueFamilyPropertiesCount);
    for (uint32_t propertyIndex = 0U; propertyIndex < queueFamilyPropertiesCount; propertyIndex++) {
        if (!checkResult(vkGetPhysicalDeviceSurfaceSupportKHR(gpuContext->physicalDevice, propertyIndex,
                                             _gpuSwapchain->vkSurface, &_gpuSwapchain->queueFamilyPresentables[propertyIndex]))) return;
    }

    // find other possible queues if not presentable
    auto *queue = static_cast<CCVKQueue *>(CCVKDevice::getInstance()->getQueue());
    if (!_gpuSwapchain->queueFamilyPresentables[queue->gpuQueue()->queueFamilyIndex]) {
        auto &indices = queue->gpuQueue()->possibleQueueFamilyIndices;
        indices.erase(std::remove_if(indices.begin(), indices.end(), [this](uint32_t i) {
                          return !_gpuSwapchain->queueFamilyPresentables[i];
                      }),
                      indices.end());
        if (indices.empty()) {
            CC_LOG_ERROR("No Vulkan queue can present to this surface");
            return;
        }
        cmdFuncCCVKGetDeviceQueue(CCVKDevice::getInstance(), queue->gpuQueue());
    }

    Format colorFmt = Format::BGRA8;
    Format depthStencilFmt = Format::DEPTH_STENCIL;

    if (_gpuSwapchain->vkSurface != VK_NULL_HANDLE) {
        _gpuSwapchain->fullScreenExclusiveAllowed = queryFullScreenExclusiveMode();

        VkSurfaceCapabilitiesKHR surfaceCapabilities{};
        if (canQuerySurfaceCapabilities2()) {
            // query the capabilities a swapchain would get when created
            // in the selected full-screen exclusive mode
            VkPhysicalDeviceSurfaceInfo2KHR surfaceInfo{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR};
            surfaceInfo.surface = _gpuSwapchain->vkSurface;
#ifdef VK_USE_PLATFORM_WIN32_KHR
            if (_gpuSwapchain->fullScreenExclusiveAllowed) {
                VkSurfaceFullScreenExclusiveInfoEXT fullScreenExclusiveInfo{VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT};
                fullScreenExclusiveInfo.fullScreenExclusive = _gpuSwapchain->fullScreenExclusiveMode;
                // VUID-VkPhysicalDeviceSurfaceInfo2KHR-pNext-02672: win32 monitor struct required
                // for APPLICATION_CONTROLLED / ALLOWED on a Win32 surface
                VkSurfaceFullScreenExclusiveWin32InfoEXT fullScreenExclusiveWin32Info{VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT};
                fullScreenExclusiveWin32Info.hmonitor = _windowHandle ? MonitorFromWindow(static_cast<HWND>(_windowHandle), MONITOR_DEFAULTTONEAREST) : VK_NULL_HANDLE;
                fullScreenExclusiveInfo.pNext = &fullScreenExclusiveWin32Info;
                surfaceInfo.pNext = &fullScreenExclusiveInfo;
            }
#endif
            VkSurfaceCapabilities2KHR surfaceCapabilities2{VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR};
            if (!checkResult(vkGetPhysicalDeviceSurfaceCapabilities2KHR(gpuContext->physicalDevice, &surfaceInfo, &surfaceCapabilities2))) return;
            surfaceCapabilities = surfaceCapabilities2.surfaceCapabilities;
        } else {
            if (!checkResult(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &surfaceCapabilities))) return;
        }

        uint32_t surfaceFormatCount = 0U;
        if (!checkResult(vkGetPhysicalDeviceSurfaceFormatsKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &surfaceFormatCount, nullptr))) return;
        ccstd::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        if (!checkResult(vkGetPhysicalDeviceSurfaceFormatsKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &surfaceFormatCount, surfaceFormats.data()))) return;

        uint32_t presentModeCount = 0U;
        if (!checkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &presentModeCount, nullptr))) return;
        ccstd::vector<VkPresentModeKHR> presentModes(presentModeCount);
        if (!checkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &presentModeCount, presentModes.data()))) return;

        if (!surfaceFormatCount || !presentModeCount) {
            CC_LOG_ERROR("Vulkan surface has no supported format or present mode");
            return;
        }

        VkFormat colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
        VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        // If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
        // there is no preferred format, so we assume VK_FORMAT_B8G8R8A8_UNORM
        if ((surfaceFormatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)) {
            colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
            colorSpace = surfaceFormats[0].colorSpace;
        } else {
            // iterate over the list of available surface format and
            // check for the presence of VK_FORMAT_B8G8R8A8_UNORM
            bool imageFormatFound = false;
            for (VkSurfaceFormatKHR &surfaceFormat : surfaceFormats) {
                if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {
                    colorFormat = surfaceFormat.format;
                    colorSpace = surfaceFormat.colorSpace;
                    imageFormatFound = true;
                    break;
                }
            }

            // in case VK_FORMAT_B8G8R8A8_UNORM is not available
            // select the first available color format
            if (!imageFormatFound) {
                colorFormat = surfaceFormats[0].format;
                colorSpace = surfaceFormats[0].colorSpace;
                switch (colorFormat) {
                    case VK_FORMAT_R8G8B8A8_UNORM: colorFmt = Format::RGBA8; break;
                    case VK_FORMAT_R8G8B8A8_SRGB: colorFmt = Format::SRGB8_A8; break;
                    case VK_FORMAT_R5G6B5_UNORM_PACK16: colorFmt = Format::R5G6B5; break;
                    case VK_FORMAT_B8G8R8A8_UNORM: colorFmt = Format::BGRA8; break;
                    default:
                        CC_LOG_ERROR("Unsupported Vulkan surface format: %d", colorFormat);
                        return;
                }
            }
        }

        // Select a present mode for the swapchain
        VkPresentModeKHR swapchainPresentMode = selectPresentModeForVsync(_vsyncMode, presentModes);
        CC_LOG_INFO("Swapchain present mode is %s", presentModeName(swapchainPresentMode));
        // The GFX-side format decides whether readbacks need a channel swizzle
        // (CCVKDevice::copyTextureToBuffers), so make it visible in the log.
        CC_LOG_INFO("Swapchain color format is %s", GFX_FORMAT_INFOS[toNumber(colorFmt)].name.c_str());

        // Determine the number of images
        uint32_t desiredNumberOfSwapchainImages = std::max(gpuDevice->backBufferCount, surfaceCapabilities.minImageCount);
        if (surfaceCapabilities.maxImageCount) desiredNumberOfSwapchainImages = std::min(desiredNumberOfSwapchainImages, surfaceCapabilities.maxImageCount);
        CC_LOG_INFO("Swapchain desired image count is %d", desiredNumberOfSwapchainImages);

        VkExtent2D imageExtent = {1U, 1U};

        // Find a supported composite alpha format (not all devices support alpha opaque)
        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        // Simply select the first composite alpha format available
        ccstd::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
        };
        for (VkCompositeAlphaFlagBitsKHR compositeAlphaFlag : compositeAlphaFlags) {
            if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlag) {
                compositeAlpha = compositeAlphaFlag;
                break;
            };
        }
        VkImageUsageFlags imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        // Enable transfer source on swap chain images if supported
        if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
            imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        }

        // Enable transfer destination on swap chain images if supported
        if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
            imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        }

        // The swapchain color texture is referenced by no-clear (LOAD) passes and post-effect
        // paths with SHADER_READ_ONLY initial/final layouts (VUID-vkCmdBeginRenderPass-initialLayout-00897),
        // so the image must carry SAMPLED usage; the GFX-side TextureInfo already declares
        // SAMPLED for the swapchain texture, and the swapchain creation must honor it.
        if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_SAMPLED_BIT) {
            imageUsage |= VK_IMAGE_USAGE_SAMPLED_BIT;
        }

        _gpuSwapchain->createInfo.surface = _gpuSwapchain->vkSurface;
        _gpuSwapchain->createInfo.minImageCount = desiredNumberOfSwapchainImages;
        _gpuSwapchain->createInfo.imageFormat = colorFormat;
        _gpuSwapchain->createInfo.imageColorSpace = colorSpace;
        _gpuSwapchain->createInfo.imageExtent = imageExtent;
        _gpuSwapchain->createInfo.imageUsage = imageUsage;
        _gpuSwapchain->createInfo.imageArrayLayers = 1;
        _gpuSwapchain->createInfo.preTransform = VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        _gpuSwapchain->createInfo.compositeAlpha = compositeAlpha;
        _gpuSwapchain->createInfo.presentMode = swapchainPresentMode;
        _gpuSwapchain->createInfo.clipped = VK_TRUE; // Setting clipped to VK_TRUE allows the implementation to discard rendering outside of the surface area
    }
    ///////////////////// Texture Creation /////////////////////
    auto width = static_cast<int32_t>(info.width);
    auto height = static_cast<int32_t>(info.height);
    _colorTexture = ccnew CCVKTexture;
    _depthStencilTexture = ccnew CCVKTexture;

    SwapchainTextureInfo textureInfo;
    textureInfo.swapchain = this;
    textureInfo.format = colorFmt;
    textureInfo.width = width;
    textureInfo.height = height;
    initTexture(textureInfo, _colorTexture);

    textureInfo.format = depthStencilFmt;
    initTexture(textureInfo, _depthStencilTexture);

    checkSwapchainStatus(info.width, info.height);
}

void CCVKSwapchain::doDestroy() {
    _drawableAcquired = false;
    _surfaceStatus = SurfaceStatus::UNINITIALIZED;
    if (!_gpuSwapchain) return;

    CCVKDevice::getInstance()->waitAllFences();

    _depthStencilTexture = nullptr;
    _colorTexture = nullptr;

    auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();

    destroySwapchain(gpuDevice);

    if (_gpuSwapchain->vkSurface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(gpuContext->vkInstance, _gpuSwapchain->vkSurface, nullptr);
        _gpuSwapchain->vkSurface = VK_NULL_HANDLE;
    }

    gpuDevice->swapchains.erase(_gpuSwapchain);
    _gpuSwapchain = nullptr;
}

void CCVKSwapchain::doResize(uint32_t width, uint32_t height, SurfaceTransform /*transform*/) {
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) return;
    if (!width || !height) {
        _drawableAcquired = false;
        _surfaceStatus = SurfaceStatus::ZERO_SIZE;
        return;
    }
    checkSwapchainStatus(width, height); // the orientation info from system event is not reliable
}

bool CCVKSwapchain::checkSwapchainStatus(uint32_t width, uint32_t height) {
    _drawableAcquired = false;
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) return false;
    if (!_gpuSwapchain || _gpuSwapchain->vkSurface == VK_NULL_HANDLE) {
        _surfaceStatus = SurfaceStatus::SURFACE_LOST;
        return false;
    }
    const auto checkResult = [this](VkResult result) {
        if (result == VK_SUCCESS) return true;
        setAcquireResult(result);
        CC_LOG_ERROR("Vulkan swapchain update failed: %d", result);
        return false;
    };
    auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    if (!checkResult(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &surfaceCapabilities))) return false;

    // surfaceCapabilities.currentExtent seems to remain the same
    // during any size/orientation change events on android devices
    // so we prefer the system input (oriented size) here
    uint32_t newWidth = width ? width : surfaceCapabilities.currentExtent.width;
    uint32_t newHeight = height ? height : surfaceCapabilities.currentExtent.height;

    if (newWidth == UINT32_MAX) newWidth = _colorTexture->getWidth();
    if (newHeight == UINT32_MAX) newHeight = _colorTexture->getHeight();
    if (!newWidth || !newHeight) {
        _gpuSwapchain->lastPresentResult = VK_NOT_READY;
        _surfaceStatus = SurfaceStatus::ZERO_SIZE;
        return false;
    }

    if (_gpuSwapchain->vkSwapchain != VK_NULL_HANDLE && _gpuSwapchain->createInfo.imageExtent.width == newWidth &&
        _gpuSwapchain->createInfo.imageExtent.height == newHeight && _gpuSwapchain->lastPresentResult == VK_SUCCESS
        && !_vsyncModeChanged) {
        _surfaceStatus = SurfaceStatus::READY;
        return true;
    }

    const auto oldPresentMode = _gpuSwapchain->createInfo.presentMode;

    // re-derive the present mode from _vsyncMode at every (re)creation (runtime setVSyncMode support)
    uint32_t presentModeCount = 0U;
    if (!checkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &presentModeCount, nullptr))) return false;
    ccstd::vector<VkPresentModeKHR> presentModes(presentModeCount);
    if (!checkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(gpuContext->physicalDevice, _gpuSwapchain->vkSurface, &presentModeCount, presentModes.data()))) return false;
    _gpuSwapchain->createInfo.presentMode = selectPresentModeForVsync(_vsyncMode, presentModes);

    CC_LOG_INFO("Recreate swapchain: %dx%d -> %dx%d, present: %s -> %s, vsync: %d",
        _gpuSwapchain->createInfo.imageExtent.width,
        _gpuSwapchain->createInfo.imageExtent.height,
        newWidth,
        newHeight,
        presentModeName(oldPresentMode),
        presentModeName(_gpuSwapchain->createInfo.presentMode),
        static_cast<uint32_t>(_vsyncMode));

    if (newWidth == static_cast<uint32_t>(-1)) {
        _gpuSwapchain->createInfo.imageExtent.width = _colorTexture->getWidth();
        _gpuSwapchain->createInfo.imageExtent.height = _colorTexture->getHeight();
    } else {
        _gpuSwapchain->createInfo.imageExtent.width = newWidth;
        _gpuSwapchain->createInfo.imageExtent.height = newHeight;
    }

    if (newWidth == 0 || newHeight == 0) {
        _gpuSwapchain->lastPresentResult = VK_NOT_READY;
        _surfaceStatus = SurfaceStatus::ZERO_SIZE;
        return false;
    }

    _gpuSwapchain->createInfo.surface = _gpuSwapchain->vkSurface;
    _gpuSwapchain->createInfo.oldSwapchain = _gpuSwapchain->vkSwapchain;

    CCVKDevice::getInstance()->waitAllFences();
    if (!checkResult(vkDeviceWaitIdle(gpuDevice->vkDevice))) return false;

    setupFullScreenExclusiveInfo();

    VkSwapchainKHR vkSwapchain = VK_NULL_HANDLE;
    VkResult createResult = vkCreateSwapchainKHR(gpuDevice->vkDevice, &_gpuSwapchain->createInfo, nullptr, &vkSwapchain);
    if (createResult != VK_SUCCESS) {
        // VK_CHECK is a no-op in release builds: never continue with a NULL swapchain
        CC_LOG_ERROR("Failed to create swapchain: %d", createResult);
        setAcquireResult(createResult);
        return false;
    }
    _vsyncModeChanged = false;

    destroySwapchain(gpuDevice, true); // deferred: old chain retired until its fence is waited

    _gpuSwapchain->vkSwapchain = vkSwapchain;

    uint32_t imageCount;
    if (!checkResult(vkGetSwapchainImagesKHR(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain, &imageCount, nullptr))) return false;
    if (!imageCount) {
        _surfaceStatus = SurfaceStatus::FAILED;
        CC_LOG_ERROR("Vulkan swapchain returned no images");
        return false;
    }
    // The CPU/GPU frame-resource ring is fixed when the device is initialized.
    // Surface image count is independent: descriptors and HOST|DEVICE buffers may
    // already own ring-sized instances before this first swapchain is created.
    // Growing only the pools/hubs here leaves those objects indexed out of bounds.
    CC_LOG_INFO("Vulkan swapchain images=%u frame-resource ring=%u", imageCount, gpuDevice->backBufferCount);
    _gpuSwapchain->swapchainImages.resize(imageCount);
    if (!checkResult(vkGetSwapchainImagesKHR(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain, &imageCount, _gpuSwapchain->swapchainImages.data()))) return false;

    // one render-finished semaphore per swapchain image: reusing sem[i] is safe because
    // image i cannot be acquired again until its previous present has completed
    _gpuSwapchain->presentSemaphores.clear();
    _gpuSwapchain->presentSemaphores.reserve(imageCount);
    for (uint32_t i = 0U; i < imageCount; ++i) {
        VkSemaphore semaphore = VK_NULL_HANDLE;
        VkSemaphoreCreateInfo semaphoreInfo{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        if (!checkResult(vkCreateSemaphore(gpuDevice->vkDevice, &semaphoreInfo, nullptr, &semaphore))) return false;
        _gpuSwapchain->presentSemaphores.push_back(semaphore);
    }

    ++_generation;

    // should skip size check, since the old swapchain has already been destroyed
    static_cast<CCVKTexture *>(_colorTexture.get())->_info.width = 1;
    static_cast<CCVKTexture *>(_depthStencilTexture.get())->_info.width = 1;
    _colorTexture->resize(newWidth, newHeight);
    _depthStencilTexture->resize(newWidth, newHeight);

    // The initial UNDEFINED→(PRESENT/DEPTH_STENCIL) transition is recorded per image at
    // its first acquisition (recordInitialTransition from VKDevice::acquire, executed
    // with the frame's submit): using a presentable image — layout transitions included
    // — before vkAcquireNextImageKHR is invalid (UNASSIGNED-non-acquired-swapchain-image-used).
    // currentAccessTypes keeps the "after the initial transition" state the rest of the
    // pipeline deduces against.
    _gpuSwapchain->imageInitialized.assign(imageCount, false);

    auto *colorGPUTexture = static_cast<CCVKTexture *>(_colorTexture.get())->gpuTexture();
    auto *depthStencilGPUTexture = static_cast<CCVKTexture *>(_depthStencilTexture.get())->gpuTexture();
    colorGPUTexture->currentAccessTypes.assign(1, THSVS_ACCESS_PRESENT);
    depthStencilGPUTexture->currentAccessTypes.assign(1, THSVS_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ);

    // automatic recovery: whenever the swapchain is (re)created while exclusive full screen
    // mode has been requested and not released (fullScreenExclusiveRequested), try to acquire
    // it again for the new swapchain; on failure the request stays pending and the next
    // swapchain recreation (resize / full-screen mode loss) retries automatically
    if (_gpuSwapchain->fullScreenExclusiveRequested) {
        attemptFullScreenExclusiveAcquire();
    }

    _gpuSwapchain->lastPresentResult = VK_SUCCESS;
    _surfaceStatus = SurfaceStatus::READY;

    // Android Game Frame Pacing:swappy
#if CC_SWAPPY_ENABLED

    auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();
    int32_t fps = cc::BasePlatform::getPlatform()->getFps();

    uint64_t frameRefreshIntervalNS;
    auto *platform = static_cast<AndroidPlatform *>(cc::BasePlatform::getPlatform());
    auto *window = CC_GET_SYSTEM_WINDOW(_windowId);
    void *windowHandle = reinterpret_cast<void *>(window->getWindowHandle());
    SwappyVk_initAndGetRefreshCycleDuration(static_cast<JNIEnv *>(platform->getEnv()),
                                            static_cast<jobject>(platform->getActivity()),
                                            gpuContext->physicalDevice,
                                            gpuDevice->vkDevice,
                                            _gpuSwapchain->vkSwapchain,
                                            &frameRefreshIntervalNS);
    SwappyVk_setSwapIntervalNS(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain, fps ? 1000000000L / fps : frameRefreshIntervalNS);
    SwappyVk_setWindow(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain, static_cast<ANativeWindow *>(windowHandle));
#endif

    return true;
}

void CCVKSwapchain::setAcquireResult(VkResult result) {
    // A new Surface cannot repair a lost VkDevice. Keep the terminal result
    // visible through detach and refuse later successful surface-only retries.
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) {
        _drawableAcquired = false;
        return;
    }
    _drawableAcquired = result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR;
    if (_gpuSwapchain) _gpuSwapchain->lastPresentResult = result;
    switch (result) {
        case VK_SUCCESS:
        case VK_SUBOPTIMAL_KHR: _surfaceStatus = SurfaceStatus::READY; break;
        case VK_NOT_READY:
        case VK_TIMEOUT:
        case VK_ERROR_OUT_OF_DATE_KHR:
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: _surfaceStatus = SurfaceStatus::OUT_OF_DATE; break;
        case VK_ERROR_SURFACE_LOST_KHR: _surfaceStatus = SurfaceStatus::SURFACE_LOST; break;
        case VK_ERROR_DEVICE_LOST: _surfaceStatus = SurfaceStatus::DEVICE_LOST; break;
        default: _surfaceStatus = SurfaceStatus::FAILED; break;
    }
}

void CCVKSwapchain::setPresentResult(VkResult result) {
    const bool acquired = _drawableAcquired.load();
    setAcquireResult(result);
    _drawableAcquired = false;
    if (acquired && (result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR)) ++_presentCount;
}

void CCVKSwapchain::recordInitialTransition(uint32_t imageIndex) {
    // layout of a brand-new swapchain image is UNDEFINED; presentable images may only be
    // used — layout transitions included — after vkAcquireNextImageKHR, so the initial
    // transition is recorded here (executed by the frame's submit, right after the
    // acquire) instead of immediately after vkCreateSwapchainKHR
    auto *colorGPUTexture = static_cast<CCVKTexture *>(_colorTexture.get())->gpuTexture();
    auto *depthStencilGPUTexture = static_cast<CCVKTexture *>(_depthStencilTexture.get())->gpuTexture();
    const bool hasStencil = GFX_FORMAT_INFOS[toNumber(_depthStencilTexture->getFormat())].hasStencil;

    ThsvsImageBarrier tempBarrier{};
    tempBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    tempBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    tempBarrier.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
    tempBarrier.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

    ccstd::vector<VkImageMemoryBarrier> barriers(2, VkImageMemoryBarrier{});
    VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    VkPipelineStageFlags tempSrcStageMask = 0;
    VkPipelineStageFlags tempDstStageMask = 0;

    tempBarrier.nextAccessCount = 1;
    tempBarrier.pNextAccesses = getAccessType(AccessFlagBit::PRESENT);
    tempBarrier.image = _gpuSwapchain->swapchainImages[imageIndex];
    tempBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    thsvsGetVulkanImageMemoryBarrier(tempBarrier, &tempSrcStageMask, &tempDstStageMask, &barriers[0]);
    srcStageMask |= tempSrcStageMask;
    dstStageMask |= tempDstStageMask;

    tempBarrier.nextAccessCount = 1;
    tempBarrier.pNextAccesses = getAccessType(AccessFlagBit::DEPTH_STENCIL_ATTACHMENT_WRITE);
    tempBarrier.image = depthStencilGPUTexture->swapchainVkImages[imageIndex];
    tempBarrier.subresourceRange.aspectMask = hasStencil ? VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT : VK_IMAGE_ASPECT_DEPTH_BIT;
    thsvsGetVulkanImageMemoryBarrier(tempBarrier, &tempSrcStageMask, &tempDstStageMask, &barriers[1]);
    srcStageMask |= tempSrcStageMask;
    dstStageMask |= tempDstStageMask;

    CCVKDevice::getInstance()->gpuTransportHub()->checkIn(
        [&](const CCVKGPUCommandBuffer *gpuCommandBuffer) {
            vkCmdPipelineBarrier(gpuCommandBuffer->vkCommandBuffer, srcStageMask, dstStageMask, 0, 0, nullptr, 0, nullptr,
                                 utils::toUint(barriers.size()), barriers.data());
        },
        false); // recorded (not immediate): submitted with the frame, after the acquire
}

void CCVKSwapchain::destroySwapchain(CCVKGPUDevice *gpuDevice, bool defer) {
    if (_gpuSwapchain->vkSwapchain != VK_NULL_HANDLE) {
        if (!defer && gpuDevice->vkDevice != VK_NULL_HANDLE) {
            // Submit fences do not cover the queue's subsequent presentation.
            // Drain it before destroying the swapchain and its present semaphores.
            const auto idleResult = vkDeviceWaitIdle(gpuDevice->vkDevice);
            if (idleResult != VK_SUCCESS) {
                setAcquireResult(idleResult);
                CC_LOG_ERROR("Vulkan swapchain teardown idle failed: %d", idleResult);
            }
        }
        _gpuSwapchain->swapchainImages.clear();

        // note: keep fullScreenExclusiveRequested, the new swapchain will re-acquire it
        releaseFullScreenExclusiveModeInternal();

        if (defer) {
            // commands recorded before the recreation may still reference the old image
            // views: keep the swapchain and its texture views alive via retiredSwapchains.
            // The old present semaphores move along so their lifetime always matches the
            // swapchain (presents on the old chain may still wait on them).
            auto *colorTexture  = static_cast<CCVKTexture *>(_colorTexture.get());
            auto *depthTexture  = static_cast<CCVKTexture *>(_depthStencilTexture.get());
            // the entry owns the old handles; present() decides when it is due
            gpuDevice->retiredSwapchains.push_back({gpuDevice->vkDevice,
                                                    _gpuSwapchain->vkSwapchain,
                                                    gpuDevice->frameIndex,
                                                    colorTexture->gpuTexture(),
                                                    colorTexture->gpuTextureView(),
                                                    depthTexture->gpuTexture(),
                                                    depthTexture->gpuTextureView(),
                                                    std::move(_gpuSwapchain->presentSemaphores)});
        } else {
#if CC_SWAPPY_ENABLED
            SwappyVk_destroySwapchain(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain);
#endif
            vkDestroySwapchainKHR(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain, nullptr);
            for (VkSemaphore semaphore : _gpuSwapchain->presentSemaphores) {
                vkDestroySemaphore(gpuDevice->vkDevice, semaphore, nullptr);
            }
            _gpuSwapchain->presentSemaphores.clear();
        }
        _gpuSwapchain->vkSwapchain = VK_NULL_HANDLE;
        // reset index only after device not ready
        _gpuSwapchain->curImageIndex = 0;
        gpuDevice->curBackBufferIndex = 0;
    }
}

void CCVKSwapchain::doDestroySurface() {
    _drawableAcquired = false;
    if (_surfaceStatus.load() != SurfaceStatus::DEVICE_LOST)
        _surfaceStatus = SurfaceStatus::UNINITIALIZED;
    if (!_gpuSwapchain || _gpuSwapchain->vkSurface == VK_NULL_HANDLE) return;
    auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();

    CCVKDevice::getInstance()->waitAllFences();
    destroySwapchain(gpuDevice);
    // Retired swapchains from an earlier resize also belong to native surfaces.
    // Drain presentation before removing them; none may outlive vkDestroySurface.
    if (!gpuDevice->retiredSwapchains.empty()) {
        const auto idleResult = vkDeviceWaitIdle(gpuDevice->vkDevice);
        if (idleResult != VK_SUCCESS) setAcquireResult(idleResult);
        gpuDevice->retiredSwapchains.clear();
    }
    _gpuSwapchain->lastPresentResult = VK_NOT_READY;

    vkDestroySurfaceKHR(gpuContext->vkInstance, _gpuSwapchain->vkSurface, nullptr);
    _gpuSwapchain->vkSurface = VK_NULL_HANDLE;
}

void CCVKSwapchain::doCreateSurface(void *windowHandle) { // NOLINT
    if (_surfaceStatus.load() == SurfaceStatus::DEVICE_LOST) return;
    if (!_gpuSwapchain || _gpuSwapchain->vkSurface != VK_NULL_HANDLE) return;
    if (!windowHandle || !_colorTexture || !_depthStencilTexture) {
        _surfaceStatus = SurfaceStatus::FAILED;
        return;
    }
    createVkSurface();
#if CC_PLATFORM == CC_PLATFORM_ANDROID
    //TODO: get viwe size
    //auto *window = CC_GET_SYSTEM_WINDOW(_windowId);
    //auto viewSize = window->getViewSize();
    //checkSwapchainStatus(viewSize.width, viewSize.height);
    checkSwapchainStatus();
#else
    checkSwapchainStatus();
#endif
}

void CCVKSwapchain::createVkSurface() {
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkAndroidSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.window = reinterpret_cast<ANativeWindow *>(_windowHandle);
    const auto result = vkCreateAndroidSurfaceKHR(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface);
    if (result != VK_SUCCESS) {
        setAcquireResult(result);
        CC_LOG_ERROR("vkCreateAndroidSurfaceKHR failed: %d", result);
    }
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.hinstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
    surfaceCreateInfo.hwnd = reinterpret_cast<HWND>(_windowHandle);
    VK_CHECK(vkCreateWin32SurfaceKHR(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface));
#elif defined(VK_USE_PLATFORM_VI_NN)
    VkViSurfaceCreateInfoNN surfaceCreateInfo{VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN};
    surfaceCreateInfo.window = _windowHandle;
    VK_CHECK(vkCreateViSurfaceNN(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface));
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
    VkMacOSSurfaceCreateInfoMVK surfaceCreateInfo{VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK};
    surfaceCreateInfo.pView = _windowHandle;
    VK_CHECK(vkCreateMacOSSurfaceMVK(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface));
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.display = nullptr; // TODO
    surfaceCreateInfo.surface = reinterpret_cast<wl_surface *>(_windowHandle);
    VK_CHECK(vkCreateWaylandSurfaceKHR(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface));
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR surfaceCreateInfo{VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
    surfaceCreateInfo.connection = nullptr; // TODO
    surfaceCreateInfo.window = reinterpret_cast<uint64_t>(_windowHandle);
    VK_CHECK(vkCreateXcbSurfaceKHR(gpuContext->vkInstance, &surfaceCreateInfo, nullptr, &_gpuSwapchain->vkSurface));
#else
    #pragma error Platform not supported
#endif
}

bool CCVKSwapchain::canQuerySurfaceCapabilities2() const {
    // the KHR_get_surface_capabilities2 instance extension is requested unconditionally at
    // instance creation; only query with caps-2 when it was actually enabled (calling the
    // function without the extension is undefined / reported by validation layers)
    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();
    return gpuContext->checkExtension(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);
}

bool CCVKSwapchain::isFullScreenExclusiveSupported() const {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    return CCVKDevice::getInstance()->checkExtension(VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME);
#else
    return false;
#endif
}

bool CCVKSwapchain::queryFullScreenExclusiveMode() {
    _gpuSwapchain->fullScreenExclusiveAllowed = false;
#ifdef VK_USE_PLATFORM_WIN32_KHR
    if (!isFullScreenExclusiveSupported() || !vkGetPhysicalDeviceSurfacePresentModes2EXT) {
        return false;
    }

    const auto *gpuContext = CCVKDevice::getInstance()->gpuContext();

    // probe the surface for a supported full-screen-exclusive mode before the
    // swapchain is created: the surface info carries the mode hint, the query
    // only succeeds for modes this surface can actually present
    const VkFullScreenExclusiveEXT preferredModes[]{
        VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT,
        VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT,
    };
    for (VkFullScreenExclusiveEXT mode : preferredModes) {
        VkPhysicalDeviceSurfaceInfo2KHR surfaceInfo{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR};
        surfaceInfo.surface = _gpuSwapchain->vkSurface;
        VkSurfaceFullScreenExclusiveInfoEXT fullScreenExclusiveInfo{VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT};
        fullScreenExclusiveInfo.fullScreenExclusive = mode;
        // VUID-VkPhysicalDeviceSurfaceInfo2KHR-pNext-02672: for APPLICATION_CONTROLLED /
        // ALLOWED on a Win32 surface, the win32 monitor struct must be chained as well
        VkSurfaceFullScreenExclusiveWin32InfoEXT fullScreenExclusiveWin32Info{VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT};
        fullScreenExclusiveWin32Info.hmonitor = _windowHandle ? MonitorFromWindow(static_cast<HWND>(_windowHandle), MONITOR_DEFAULTTONEAREST) : VK_NULL_HANDLE;
        fullScreenExclusiveInfo.pNext = &fullScreenExclusiveWin32Info;
        surfaceInfo.pNext = &fullScreenExclusiveInfo;

        uint32_t presentModeCount = 0U;
        if (vkGetPhysicalDeviceSurfacePresentModes2EXT(gpuContext->physicalDevice, &surfaceInfo, &presentModeCount, nullptr) != VK_SUCCESS) {
            continue; // the surface does not support this full-screen-exclusive mode
        }

        _gpuSwapchain->fullScreenExclusiveMode = mode;
        _gpuSwapchain->fullScreenExclusiveAllowed = true;
        CC_LOG_INFO("Avalible full screen exclusive mode: %s",
            mode == VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT ? "APPLICATION_CONTROLLED" : "ALLOWED");
        return true;
    }
    return false;
#else
    return false;
#endif
}

void CCVKSwapchain::setupFullScreenExclusiveInfo() {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    // re-query the supported full-screen exclusive mode before each swapchain creation
    // (the surface may have moved to another monitor / display config changed)
    _gpuSwapchain->fullScreenExclusiveAllowed = queryFullScreenExclusiveMode();
    if (!_gpuSwapchain->fullScreenExclusiveAllowed) {
        _gpuSwapchain->createInfo.pNext = nullptr;
        return;
    }

    auto &fullScreenExclusiveInfo = _gpuSwapchain->fullScreenExclusiveInfo;
    fullScreenExclusiveInfo.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT;
    fullScreenExclusiveInfo.pNext = nullptr;
    fullScreenExclusiveInfo.fullScreenExclusive = _gpuSwapchain->fullScreenExclusiveMode;

    // VUID-VkSwapchainCreateInfoKHR-pNext-02679: for APPLICATION_CONTROLLED / ALLOWED on a Win32
    // surface the win32 monitor struct must be chained as well (the monitor is selected here;
    // when omitted the system uses the monitor the surface's window is located on)
    auto &fullScreenExclusiveWin32Info = _gpuSwapchain->fullScreenExclusiveWin32Info;
    fullScreenExclusiveWin32Info.sType = VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT;
    fullScreenExclusiveWin32Info.pNext = nullptr;
    fullScreenExclusiveWin32Info.hmonitor = _windowHandle ? MonitorFromWindow(static_cast<HWND>(_windowHandle), MONITOR_DEFAULTTONEAREST) : VK_NULL_HANDLE;
    fullScreenExclusiveInfo.pNext = &fullScreenExclusiveWin32Info;

    _gpuSwapchain->createInfo.pNext = &fullScreenExclusiveInfo;
#else
    _gpuSwapchain->createInfo.pNext = nullptr;
#endif
}

void CCVKSwapchain::acquireFullScreenExclusiveMode() {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    // fail early only when the device does not support the extension at all;
    // a temporarily unavailable surface mode (fullScreenExclusiveAllowed == false)
    // must not drop the request: the intent is kept and retried automatically on the
    // next swapchain recreation
    if (!isFullScreenExclusiveSupported()) {
        return;
    }
    _gpuSwapchain->fullScreenExclusiveRequested = true;
    attemptFullScreenExclusiveAcquire();
#endif
}

void CCVKSwapchain::attemptFullScreenExclusiveAcquire() {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    // fullScreenExclusiveAllowed == false means the current swapchain was NOT created
    // with the exclusive mode chain; calling vkAcquireFullScreenExclusiveModeEXT on it
    // would violate the spec, so the attempt is deferred to the next recreation
    // (fullScreenExclusiveRequested is kept and retried automatically)
    if (!_gpuSwapchain->fullScreenExclusiveAllowed || !_gpuSwapchain->fullScreenExclusiveRequested) return;
    if (_gpuSwapchain->fullScreenExclusiveAcquired) return;

    const auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    VkResult res = vkAcquireFullScreenExclusiveModeEXT(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain);
    if (res == VK_SUCCESS) {
        _gpuSwapchain->fullScreenExclusiveAcquired = true;
        CC_LOG_INFO("Full screen exclusive mode acquired");
    } else if (res == VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT) {
        // the mode was already lost (e.g. another application took exclusive mode):
        // stay in windowed mode, the swapchain remains valid and the next swapchain
        // recreation (resize / mode loss recovery) will retry the acquisition,
        // fullScreenExclusiveRequested is intentionally kept
        CC_LOG_WARNING("Failed to acquire full screen exclusive mode: mode lost");
    } else {
        CC_LOG_WARNING("Failed to acquire full screen exclusive mode: %d", res);
    }
#endif
}

void CCVKSwapchain::releaseFullScreenExclusiveMode() {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    _gpuSwapchain->fullScreenExclusiveRequested = false;
    releaseFullScreenExclusiveModeInternal();
#endif
}

void CCVKSwapchain::setVSyncMode(VsyncMode mode) {
    if (_vsyncMode == mode) return;
    _vsyncMode = mode;
    _vsyncModeChanged = true;
}

void CCVKSwapchain::releaseFullScreenExclusiveModeInternal() {
#ifdef VK_USE_PLATFORM_WIN32_KHR
    if (!_gpuSwapchain->fullScreenExclusiveAcquired)
        return;
    const auto *gpuDevice = CCVKDevice::getInstance()->gpuDevice();
    VkResult res = vkReleaseFullScreenExclusiveModeEXT(gpuDevice->vkDevice, _gpuSwapchain->vkSwapchain);
    if (res != VK_SUCCESS) {
        CC_LOG_WARNING("Failed to release full screen exclusive mode: %d", res);
    }
    _gpuSwapchain->fullScreenExclusiveAcquired = false;
#endif
}

} // namespace gfx
} // namespace cc
