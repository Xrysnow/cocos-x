#include "RenderTargetGFX.h"
#include "DeviceGFX.h"
#include "TextureGFX.h"
#include "UtilsGFX.h"
#include "gfx/backend/GFXDeviceManager.h"

using namespace cc;

CC_BACKEND_BEGIN

std::unordered_map<uint32_t, gfx::RenderPass*> RenderTargetGFX::renderPasses;

RenderTargetGFX* RenderTargetGFX::createDefault(const gfx::Swapchain* swapchain)
{
    auto ret = new RenderTargetGFX(true);
    if (swapchain)
    {
        ret->info.colorTextures = { swapchain->getColorTexture() };
        ret->info.depthStencilTexture = swapchain->getDepthStencilTexture();
    }
    else
    {
        const auto d = (DeviceGFX*)backend::Device::getInstance();
        gfx::TextureInfo info;
        info.usage =
            gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED | gfx::TextureUsageBit::TRANSFER_SRC;
        info.format = gfx::Format::RGBA8;
        info.width = d->getWidth();
        info.height = d->getHeight();
        auto ct = gfx::Device::getInstance()->createTexture(info);
        ret->info.colorTextures = { ct };
        gfx::TextureInfo info1;
        info1.usage = gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED |
            gfx::TextureUsageBit::TRANSFER_SRC;
        info1.format = gfx::Format::DEPTH_STENCIL;
        info1.width = d->getWidth();
        info1.height = d->getHeight();
        auto dst = gfx::Device::getInstance()->createTexture(info1);
        ret->info.depthStencilTexture = dst;
    }
    ret->generateFramebuffers();
    return ret;
}

RenderTargetGFX::RenderTargetGFX(bool defaultRenderTarget) : RenderTarget(defaultRenderTarget)
{
}

RenderTargetGFX::~RenderTargetGFX()
{
    // framebuffers should be destroyed before textures
    framebuffers.clear();
    textures.clear();
}

void RenderTargetGFX::update() const
{
    if (!_dirty)
        return;
    if (_defaultRenderTarget)
    {
        _dirty = false;
        return;
    }
    info.colorTextures.clear();
    info.depthStencilTexture = nullptr;
#if CC_DEBUG
    uint32_t width  = 0;
    uint32_t height = 0;
#endif  // CC_DEBUG
    if (bitmask::any(_flags, TargetBufferFlags::COLOR_ALL))
    {
        for (size_t i = 0; i < MAX_COLOR_ATTCHMENT; ++i)
        {
            if (bitmask::any(_flags, getMRTColorFlag(i)))
            {
                const auto tex = _color[i].texture;
                // tex cannot be nullptr
                if (!tex)
                    continue;
                const auto fmt   = tex->getTextureFormat();
                const auto usage = tex->getTextureUsage();
                if (fmt != PixelFormat::RGBA8888 || usage != TextureUsage::RENDER_TARGET)
                {
                    CC_LOG_ERROR("%s: invalid color attachment, format=%d, usage=%d", __FUNCTION__, (int)fmt, (int)usage);
                    CC_ASSERT(false);
                    continue;
                }
                info.colorTextures.emplace_back(UtilsGFX::getTexture(tex));
#if CC_DEBUG
                if (!UtilsGFX::getTexture(tex))
                {
                    CC_ASSERT(false);
                }
                if (width == 0)
                {
                    width  = tex->getWidth();
                    height = tex->getHeight();
                }
                else if (width != tex->getWidth() || height != tex->getHeight())
                {
                    CC_LOG_ERROR(
                        "color texture size mismatch: (%d,%d)/(%d,%d)",
                        width,
                        height,
                        tex->getWidth(),
                        tex->getHeight());
                    CC_ASSERT(false);
                }
#endif  // CC_DEBUG
            }
        }
    }
#if CC_DEBUG
    if (info.colorTextures.empty())
    {
        CC_ASSERT(false);
    }
#endif  // CC_DEBUG
    // depth and stencil are always packed
    const auto dsTex = _depth.texture ? _depth.texture : _stencil.texture;
    if (dsTex)
    {
        const auto fmt   = dsTex->getTextureFormat();
        const auto usage = dsTex->getTextureUsage();
        if (fmt != PixelFormat::D24S8 || usage != TextureUsage::RENDER_TARGET)
        {
            CC_LOG_ERROR("%s: invalid DS attachment, format=%d, usage=%d", __FUNCTION__, (int)fmt, (int)usage);
            CC_ASSERT(false);
        }
        else
        {
            info.depthStencilTexture = UtilsGFX::getTexture(dsTex);
#if CC_DEBUG
            if (width && (width != dsTex->getWidth() || height != dsTex->getHeight()))
            {
                CC_LOG_ERROR(
                    "ds texture size mismatch: (%d,%d)/(%d,%d)", width, height, dsTex->getWidth(), dsTex->getHeight());
                CC_ASSERT(false);
            }
#endif  // CC_DEBUG
        }
    }
    generateFramebuffers();
    _dirty = false;
}

gfx::Framebuffer* RenderTargetGFX::getFramebuffer(cc::gfx::ClearFlagBit clearFlags) const
{
    if (!hasDepthStencil())
    {
        clearFlags &= ~gfx::ClearFlagBit::DEPTH_STENCIL;
    }
    if (framebuffers.empty())
    {
        generateFramebuffers();
    }
#if CC_DEBUG
    if (!framebuffers.at((uint32_t)clearFlags))
    {
        CC_LOG_ERROR("no framebuffer for clear flags: %d, hasDepthStencil: %d", (int)clearFlags, (int)hasDepthStencil());
    }
#endif  // CC_DEBUG
    return framebuffers.at((uint32_t)clearFlags);
}

bool RenderTargetGFX::hasDepthStencil() const
{
    return _depth.texture || _stencil.texture || _defaultRenderTarget;
}

void RenderTargetGFX::generateFramebuffers() const
{
    framebuffers.clear();
    textures.clear();
    // hold textures
    for (auto&& t : info.colorTextures)
        textures.pushBack(t);
    if (info.depthStencilTexture)
        textures.pushBack(info.depthStencilTexture);
    //
    auto clearTypeEnd = (uint32_t)gfx::ClearFlagBit::ALL;
    const auto hasDS = hasDepthStencil();
    if (!hasDS)
        clearTypeEnd = (uint32_t)gfx::ClearFlagBit::COLOR;
    const auto colorFormat = info.colorTextures[0]->getFormat();
    for (uint32_t i = 0; i <= clearTypeEnd; ++i)
    {
        info.renderPass = getRenderPass((gfx::ClearFlagBit)i, hasDS, colorFormat);
        framebuffers.insert(i, gfx::Device::getInstance()->createFramebuffer(info));
    }
}

gfx::RenderPass* RenderTargetGFX::getRenderPass(
    gfx::ClearFlagBit clearFlags,
    bool hasDepthStencil,
    gfx::Format format)
{
    const auto key = (uint32_t)clearFlags + ((uint32_t)format << 8) + (hasDepthStencil ? 0U : (1U << 31));
    const auto find = renderPasses.find(key);
    if (find != renderPasses.end())
    {
        return find->second;
    }
    gfx::RenderPassInfo info;
    gfx::ColorAttachment ca;
    // should be RGBA8, but can be BGRA8 in vulkan
    ca.format = format;
    // default loadOp is CLEAR
    if (!gfx::hasFlag(clearFlags, gfx::ClearFlagBit::COLOR))
    {
        // TODO: should be DISACARD if is skybox
        ca.loadOp = gfx::LoadOp::LOAD;
        gfx::GeneralBarrierInfo binfo;
        binfo.nextAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
        // must be same as nextAccesses if not clear
        binfo.prevAccesses = binfo.nextAccesses;
        ca.barrier = gfx::Device::getInstance()->getGeneralBarrier(binfo);
    }
    info.colorAttachments = { ca };
    if (hasDepthStencil)
    {
        auto& dsa = info.depthStencilAttachment;
        // should be D24S8
        dsa.format = gfx::Format::DEPTH_STENCIL;
        if (!gfx::hasAllFlags(clearFlags, gfx::ClearFlagBit::DEPTH_STENCIL))
        {
            if (!gfx::hasFlag(clearFlags, gfx::ClearFlagBit::DEPTH))
                dsa.depthLoadOp = gfx::LoadOp::LOAD;
            if (!gfx::hasFlag(clearFlags, gfx::ClearFlagBit::STENCIL))
                dsa.stencilLoadOp = gfx::LoadOp::LOAD;
            gfx::GeneralBarrierInfo binfo;
            binfo.nextAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
            binfo.prevAccesses = binfo.nextAccesses;
            dsa.barrier = gfx::Device::getInstance()->getGeneralBarrier(binfo);
        }
    }
    const auto rp = gfx::Device::getInstance()->createRenderPass(info);
    renderPasses[key] = rp;
    return rp;
}

CC_BACKEND_END
