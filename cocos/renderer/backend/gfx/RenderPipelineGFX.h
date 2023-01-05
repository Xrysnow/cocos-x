#pragma once
#include "renderer/backend/RenderPipeline.h"
#include "gfx/backend/GFXDeviceManager.h"
#include <vector>

CC_BACKEND_BEGIN

class ProgramGFX;

class RenderPipelineGFX : public RenderPipeline
{
public:
	RenderPipelineGFX() = default;
	~RenderPipelineGFX() override;

	void update(
		const RenderTarget*,
		const PipelineDescriptor& pipelineDescirptor) override;

	void doUpdate(cc::gfx::PipelineStateInfo* psinfo);

	ProgramGFX* getProgram() const { return _programGFX; }

private:
	ProgramGFX* _programGFX = nullptr;
	BlendDescriptor _blendDescriptor;
};

CC_BACKEND_END
