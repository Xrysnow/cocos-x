/****************************************************************************
 Copyright (c) 2019-2023 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include "gfx-agent/DeviceAgent.h"
#include "gfx-validator/DeviceValidator.h"

#ifdef CC_USE_VULKAN
    #include "gfx-vulkan/VKDevice.h"
#endif

#ifdef CC_USE_METAL
    #include "gfx-metal/MTLDevice.h"
#endif

#ifdef CC_USE_GLES3
    #include "gfx-gles3/GLES3Device.h"
#endif

#ifdef CC_USE_GLES2
    #include "gfx-gles2/GLES2Device.h"
#endif

#include "gfx-empty/EmptyDevice.h"

namespace cc {
namespace gfx {
class CC_DLL DeviceManager final {
public:
    static bool DETACH_DEVICE_THREAD;
    static bool FORCE_DISABLE_VALIDATION;
    static bool FORCE_ENABLE_VALIDATION;

    static Device* create(const DeviceInfo& info, API preferredAPI = API::UNKNOWN) {
        Device* device = nullptr;
        switch (preferredAPI)
        {
        case API::GLES2:
#ifdef CC_USE_GLES2
            if (tryCreate<GLES2Device>(info, &device))
                return device;
#endif
            break;
        case API::GLES3:
#ifdef CC_USE_GLES3
            if (tryCreate<GLES3Device>(info, &device))
                return device;
#endif
            break;
        case API::METAL:
#ifdef CC_USE_METAL
            if (tryCreate<CCMTLDevice>(info, &device))
                return device;
#endif
            break;
        case API::VULKAN:
#ifdef CC_USE_VULKAN
            if (tryCreate<CCVKDevice>(info, &device))
                return device;
#endif
            break;
        case API::UNKNOWN:
            if (tryCreate<EmptyDevice>(info, &device))
                return device;
            break;
        case API::NVN:
        case API::WEBGL:
        case API::WEBGL2:
        case API::WEBGPU:
        default:
            break;
        }

#ifdef CC_USE_VULKAN
        if (preferredAPI != API::VULKAN && tryCreate<CCVKDevice>(info, &device))
            return device;
#endif
#ifdef CC_USE_METAL
        if (preferredAPI != API::METAL && tryCreate<CCMTLDevice>(info, &device))
            return device;
#endif
#ifdef CC_USE_GLES3
        if (preferredAPI != API::GLES3 && tryCreate<GLES3Device>(info, &device))
            return device;
#endif
#ifdef CC_USE_GLES2
        if (preferredAPI != API::GLES2 && tryCreate<GLES2Device>(info, &device))
            return device;
#endif
        if (tryCreate<EmptyDevice>(info, &device))
            return device;

        return nullptr;
    }

    static void destroy() {
        CC_SAFE_DESTROY(Device::instance);
    }

    static bool isDetachDeviceThread() {
        return DETACH_DEVICE_THREAD && Device::isSupportDetachDeviceThread;
    }

private:
    template <typename DeviceCtor, typename Enable = std::enable_if_t<std::is_base_of<Device, DeviceCtor>::value>>
    static bool tryCreate(const DeviceInfo &info, Device **pDevice) {
        Device *device = ccnew DeviceCtor;

        if (isDetachDeviceThread()) {
            device = ccnew gfx::DeviceAgent(device);
        }

#if !defined(CC_SERVER_MODE)
        if ((CC_DEBUG > 0 && !FORCE_DISABLE_VALIDATION) || FORCE_ENABLE_VALIDATION) {
            device = ccnew gfx::DeviceValidator(device);
        }
#endif

        if (!device->initialize(info)) {
            CC_SAFE_DELETE(device);
            return false;
        }
        *pDevice = device;

        return true;
    }

#ifndef CC_DEBUG
    static constexpr int CC_DEBUG{0};
#endif
};

} // namespace gfx
} // namespace cc
