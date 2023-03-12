#pragma once
#include "renderer/backend/DepthStencilState.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

class DepthStencilStateGFX : public DepthStencilState
{
public:
    DepthStencilStateGFX() = default;

    void apply(cc::gfx::PipelineStateInfo* info, unsigned int stRefValueFront, unsigned int stRefValueBack) const;
    static void reset(cc::gfx::PipelineStateInfo* info);
};

CC_BACKEND_END
