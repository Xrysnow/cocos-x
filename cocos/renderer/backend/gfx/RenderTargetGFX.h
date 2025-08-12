#pragma once
#include "../RenderTarget.h"
#include "base/RefMap.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

class DeviceGFX;

class RenderTargetGFX : public RenderTarget
{
public:
    static RenderTargetGFX* createDefault(const cc::gfx::Swapchain* swapchain = nullptr);

    RenderTargetGFX(bool defaultRenderTarget);
    ~RenderTargetGFX() override;

    bool isDefault() const { return _defaultRenderTarget || info.colorTextures.empty(); }
    void update() const;

    const cc::gfx::FramebufferInfo& getInfo() const { return info; }
    cc::gfx::Framebuffer* getFramebuffer(cc::gfx::ClearFlagBit clearFlags = cc::gfx::ClearFlagBit::ALL) const;

private:
    bool hasDepthStencil() const;
    void generateFramebuffers() const;
    static cc::gfx::RenderPass* getRenderPass(
        cc::gfx::ClearFlagBit clearFlags, bool hasDepthStencil, cc::gfx::Format format);

    mutable cc::gfx::FramebufferInfo info;
    mutable cc::RefMap<uint32_t, cc::gfx::Framebuffer*> framebuffers;
    mutable cc::RefVector<cc::gfx::Texture*> textures;
    static std::unordered_map<uint32_t, cc::gfx::RenderPass*> renderPasses;
};

CC_BACKEND_END
