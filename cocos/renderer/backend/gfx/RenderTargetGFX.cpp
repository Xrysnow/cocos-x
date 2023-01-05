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
    if (!_defaultRenderTarget)
    {
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
                    const auto fmt = tex->getTextureFormat();
                    const auto usage = tex->getTextureUsage();
                    if (fmt != PixelFormat::RGBA8888 || usage != TextureUsage::RENDER_TARGET)
                    {
                        log("%s: invalid color attachment, format=%d, usage=%d",
                            __FUNCTION__, (int)fmt, (int)usage);
                        CC_ASSERT(false);
                        continue;
                    }
                    info.colorTextures.emplace_back(UtilsGFX::getTexture(tex));
                }
            }
        }
        // depth and stencil are always packed
        const auto dsTex = _depth.texture ? _depth.texture : _stencil.texture;
        if (dsTex)
        {
            const auto fmt = dsTex->getTextureFormat();
            const auto usage = dsTex->getTextureUsage();
	        if (fmt != PixelFormat::D24S8 || usage != TextureUsage::RENDER_TARGET)
	        {
                log("%s: invalid DS attachment, format=%d, usage=%d",
                    __FUNCTION__, (int)fmt, (int)usage);
                CC_ASSERT(false);
            }
	        else
		        info.depthStencilTexture = UtilsGFX::getTexture(dsTex);
        }
    }
    _dirty = false;
}

CC_BACKEND_END
