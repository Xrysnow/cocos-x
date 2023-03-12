#include "RenderPipelineGFX.h"
#include "ShaderModuleGFX.h"
#include "DepthStencilStateGFX.h"
#include "ProgramGFX.h"
#include "UtilsGFX.h"

using namespace cc;

CC_BACKEND_BEGIN

void RenderPipelineGFX::update(const RenderTarget*, const PipelineDescriptor& pipelineDescirptor)
{
    if (_programGFX != pipelineDescirptor.programState->getProgram())
    {
        _programGFX = static_cast<ProgramGFX*>(pipelineDescirptor.programState->getProgram());
    }
    // save
    _blendDescriptor = pipelineDescirptor.blendDescriptor;
}

void RenderPipelineGFX::doUpdate(gfx::PipelineStateInfo* psinfo)
{
    if (!psinfo)
        return;
    auto& target     = psinfo->blendState.targets.at(0);
    auto& descriptor = _blendDescriptor;
    if (descriptor.blendEnabled)
    {
        target.blend         = 1;
        target.blendSrc      = UtilsGFX::toBlendFactor(descriptor.sourceRGBBlendFactor);
        target.blendDst      = UtilsGFX::toBlendFactor(descriptor.destinationRGBBlendFactor);
        target.blendEq       = UtilsGFX::toBlendOperation(descriptor.rgbBlendOperation);
        target.blendSrcAlpha = UtilsGFX::toBlendFactor(descriptor.sourceAlphaBlendFactor);
        target.blendDstAlpha = UtilsGFX::toBlendFactor(descriptor.destinationAlphaBlendFactor);
        target.blendAlphaEq  = UtilsGFX::toBlendOperation(descriptor.alphaBlendOperation);
    }
    else
    {
        target.blend = 0;
    }

    const auto writeMaskRed   = bitmask::any(descriptor.writeMask, ColorWriteMask::RED);
    const auto writeMaskGreen = bitmask::any(descriptor.writeMask, ColorWriteMask::GREEN);
    const auto writeMaskBlue  = bitmask::any(descriptor.writeMask, ColorWriteMask::BLUE);
    const auto writeMaskAlpha = bitmask::any(descriptor.writeMask, ColorWriteMask::ALPHA);

    target.blendColorMask = gfx::ColorMask::NONE;
    if (writeMaskRed)
        target.blendColorMask |= gfx::ColorMask::R;
    if (writeMaskGreen)
        target.blendColorMask |= gfx::ColorMask::G;
    if (writeMaskBlue)
        target.blendColorMask |= gfx::ColorMask::B;
    if (writeMaskAlpha)
        target.blendColorMask |= gfx::ColorMask::A;
}

CC_BACKEND_END
