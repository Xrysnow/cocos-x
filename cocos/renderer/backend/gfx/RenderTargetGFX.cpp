#include "RenderTargetGFX.h"
#include "DeviceGFX.h"
#include "TextureGFX.h"
#include "UtilsGFX.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

RenderTargetGFX::RenderTargetGFX(bool defaultRenderTarget) : RenderTarget(defaultRenderTarget)
{
}

RenderTargetGFX::~RenderTargetGFX()
{
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
                    print("%s: invalid color attachment, format=%d, usage=%d", __FUNCTION__, (int)fmt, (int)usage);
                    CC_ASSERT(false);
                    continue;
                }
                info.colorTextures.emplace_back(UtilsGFX::getTexture(tex));
#if CC_DEBUG
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
    // depth and stencil are always packed
    const auto dsTex = _depth.texture ? _depth.texture : _stencil.texture;
    if (dsTex)
    {
        const auto fmt   = dsTex->getTextureFormat();
        const auto usage = dsTex->getTextureUsage();
        if (fmt != PixelFormat::D24S8 || usage != TextureUsage::RENDER_TARGET)
        {
            print("%s: invalid DS attachment, format=%d, usage=%d", __FUNCTION__, (int)fmt, (int)usage);
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
    _dirty = false;
}

CC_BACKEND_END
