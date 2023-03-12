#pragma once
#include "renderer/backend/RenderPipeline.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "ProgramGFX.h"

CC_BACKEND_BEGIN

class RenderPipelineGFX : public RenderPipeline
{
public:
    RenderPipelineGFX() = default;

    void update(const RenderTarget*, const PipelineDescriptor& pipelineDescirptor) override;
    void doUpdate(cc::gfx::PipelineStateInfo* psinfo);

    ProgramGFX* getProgram() const { return _programGFX; }

private:
    cocos2d::RefPtr<ProgramGFX> _programGFX;
    BlendDescriptor _blendDescriptor;
};

CC_BACKEND_END
