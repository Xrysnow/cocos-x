#pragma once
#include "../RenderTarget.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

class DeviceGFX;

class RenderTargetGFX : public RenderTarget
{
public:
    /*
     * generateFBO, false, use for screen framebuffer
     */
    RenderTargetGFX(bool defaultRenderTarget);
    ~RenderTargetGFX() override;

    void update() const;

    cc::gfx::FramebufferInfo getInfo() const { return info; }

private:
    mutable cc::gfx::FramebufferInfo info;
};

CC_BACKEND_END
