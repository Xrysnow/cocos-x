#pragma once
#include "renderer/backend/Macros.h"
#include "renderer/backend/CommandBuffer.h"
#include "base/CCEventListenerCustom.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "math/CCMath.h"
#include <vector>

CC_BACKEND_BEGIN

class ProgramStateGFX;
class Texture2DGFX;
class BufferGFX;
class RenderPipelineGFX;
class ProgramGFX;
class DepthStencilStateGFX;

class CommandBufferGFX final : public CommandBuffer
{
public:
	CommandBufferGFX();
	~CommandBufferGFX() override;

	virtual bool beginFrame() override;

	virtual void beginRenderPass(
		const RenderTarget* renderTarget,
		const RenderPassDescriptor& descriptor) override;

	virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;

	virtual void setViewport(int x, int y, unsigned int w, unsigned int h) override;

	virtual void setCullMode(CullMode mode) override;

	virtual void setWinding(Winding winding) override;

	virtual void setVertexBuffer(Buffer* buffer) override;

	virtual void setProgramState(ProgramState* programState) override;

	virtual void setIndexBuffer(Buffer* buffer) override;

	virtual void drawArrays(
		PrimitiveType primitiveType,
		std::size_t start,
		std::size_t count,
		bool wireframe = false) override;

	virtual void drawElements(
		PrimitiveType primitiveType,
		IndexFormat indexType,
		std::size_t count,
		std::size_t offset,
		bool wireframe = false) override;

	virtual void endRenderPass() override;

	virtual void endFrame() override;

	virtual void setLineWidth(float lineWidth) override;

	virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;

	virtual void setDepthStencilState(DepthStencilState* depthStencilState) override;

	virtual void updateDepthStencilState(const DepthStencilDescriptor& descriptor) override;

	virtual void updatePipelineState(const RenderTarget* rt, const PipelineDescriptor& descriptor) override;

	virtual void readPixels(RenderTarget* rt, std::function<void(const PixelBufferDescriptor&)> callback) override;

private:
	struct Viewport
	{
		int x = 0;
		int y = 0;
		unsigned int w = 0;
		unsigned int h = 0;
	};

	//void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);
	void prepareDrawing();
	static cc::gfx::AttributeList getAttributesFromProgramState(ProgramState* state);
	void setUniforms(ProgramGFX* program);
	void cleanResources();
	cc::gfx::RenderPass* getRenderPass(
		cc::gfx::ClearFlagBit clearFlags,
		bool hasDepthStencil,
		cc::gfx::Format format = cc::gfx::Format::RGBA8);
	void resetDefaultFBO();
	void readPixels(RenderTarget* rt,
		int x,
		int y,
		uint32_t width,
		uint32_t height,
		uint32_t bytesPerRow,
		PixelBufferDescriptor& pbd);

	std::vector<cc::gfx::Swapchain*> swapchains;
	std::vector<cc::gfx::Texture*> colorTextures;
	cc::gfx::Texture* dsTexture = nullptr;

	cc::gfx::CommandBuffer* _cb = nullptr;
	std::vector<cc::gfx::Framebuffer*> _generatedFBO;
	cc::gfx::Framebuffer* _defaultFBO = nullptr;
	cc::gfx::Framebuffer* _currentFBO = nullptr;
	Size _currentFBOSize;
	cc::gfx::RenderPass* _currentPass = nullptr;
	std::vector<cc::gfx::PipelineState*> _pstate;
	std::vector<cc::gfx::PipelineLayout*> _pLayout;
	cc::gfx::PipelineStateInfo _pstateinfo;
	std::vector<cc::gfx::Buffer*> _uniformBuffer;
	std::vector<cc::gfx::DescriptorSetLayout*> _dsLayout;
	std::vector<cc::gfx::DescriptorSet*> _ds;
	std::vector<cc::gfx::InputAssembler*> _inputAssembler;
	BufferGFX* _vertexBuffer = nullptr;
	BufferGFX* _indexBuffer = nullptr;
	ProgramState* _programState = nullptr;
	RenderPipelineGFX* _renderPipeline = nullptr;
	CullMode _cullMode = CullMode::NONE;
	DepthStencilStateGFX* _depthStencilStateGFX = nullptr;
	cc::gfx::Viewport _viewPort;
	std::unordered_map<uint32_t, cc::gfx::RenderPass*> _renderPasses;
	cocos2d::Vector<TextureBackend*> _tmpTextures;
	bool _screenResized = false;
	bool _scissorEnabled = false;
	cc::gfx::Rect _scissorRect;

#if CC_ENABLE_CACHE_TEXTURE_DATA
	EventListenerCustom* _backToForegroundListener = nullptr;
#endif
};

CC_BACKEND_END
