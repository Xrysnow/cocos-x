#include "DepthStencilStateGFX.h"
#include "UtilsGFX.h"

CC_BACKEND_BEGIN

void DepthStencilStateGFX::apply(
    cc::gfx::PipelineStateInfo* info, unsigned int stRefValueFront, unsigned int stRefValueBack) const
{
    if (!info)
        return;

    auto& s            = info->depthStencilState;
    const auto dsFlags = _depthStencilInfo.flags;

    // depth test
    s.depthTest  = bitmask::any(dsFlags, DepthStencilFlags::DEPTH_TEST) ? 1 : 0;
    s.depthWrite = bitmask::any(dsFlags, DepthStencilFlags::DEPTH_WRITE) ? 1 : 0;
    s.depthFunc  = UtilsGFX::toComareFunction(_depthStencilInfo.depthCompareFunction);

    // stencil test
    if (bitmask::any(dsFlags, DepthStencilFlags::DEPTH_TEST))
    {
        s.stencilTestFront = 1;
        s.stencilTestBack  = 1;

        s.stencilRefFront = stRefValueFront;
        s.stencilRefBack  = stRefValueBack;

        const bool requires_same = cc::gfx::Device::getInstance()->getRenderer().substr(0, 5) == "ANGLE";
        auto& front              = _depthStencilInfo.frontFaceStencil;
        auto& back = requires_same ? _depthStencilInfo.frontFaceStencil : _depthStencilInfo.backFaceStencil;

        s.stencilFuncFront = UtilsGFX::toComareFunction(front.stencilCompareFunction);
        s.stencilFuncBack  = UtilsGFX::toComareFunction(back.stencilCompareFunction);

        s.stencilFailOpFront = UtilsGFX::toStencilOperation(front.stencilFailureOperation);
        s.stencilFailOpBack  = UtilsGFX::toStencilOperation(back.stencilFailureOperation);

        s.stencilZFailOpFront = UtilsGFX::toStencilOperation(front.depthFailureOperation);
        s.stencilZFailOpBack  = UtilsGFX::toStencilOperation(back.depthFailureOperation);

        s.stencilPassOpFront = UtilsGFX::toStencilOperation(front.depthStencilPassOperation);
        s.stencilPassOpBack  = UtilsGFX::toStencilOperation(back.depthStencilPassOperation);

        s.stencilReadMaskFront = front.readMask;
        s.stencilReadMaskBack  = back.readMask;

        s.stencilWriteMaskFront = front.writeMask;
        s.stencilWriteMaskBack  = back.writeMask;
    }
    else
    {
        s.stencilTestFront = 0;
        s.stencilTestBack  = 0;
    }
}

void DepthStencilStateGFX::reset(cc::gfx::PipelineStateInfo* info)
{
    if (!info)
        return;

    auto& s            = info->depthStencilState;
    s.depthTest        = 0;
    s.depthWrite       = 0;
    s.stencilTestFront = 0;
    s.stencilTestBack  = 0;
}

CC_BACKEND_END
