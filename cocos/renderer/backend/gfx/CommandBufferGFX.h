#pragma once
#include "renderer/backend/Macros.h"
#include "renderer/backend/CommandBuffer.h"
#include "renderer/backend/gfx/BufferGFX.h"
#include "renderer/backend/gfx/RenderTargetGFX.h"
#include "base/CCEventListenerCustom.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "gfx/base/RefMap.h"
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

    bool beginFrame() override;

    void beginRenderPass(const RenderTarget* renderTarget, const RenderPassDescriptor& descriptor) override;

    void setRenderPipeline(RenderPipeline* renderPipeline) override;

    void setViewport(int x, int y, unsigned int w, unsigned int h) override;

    void setCullMode(CullMode mode) override;

    void setWinding(Winding winding) override;

    void setVertexBuffer(Buffer* buffer) override;

    void setProgramState(ProgramState* programState) override;

    void setIndexBuffer(Buffer* buffer) override;

    void drawArrays(
        PrimitiveType primitiveType, std::size_t start, std::size_t count, bool wireframe = false) override;

    void drawElements(
        PrimitiveType primitiveType,
        IndexFormat indexType,
        std::size_t count,
        std::size_t offset,
        bool wireframe = false) override;

    void endRenderPass() override;

    void endFrame() override;

    void setLineWidth(float lineWidth) override;

    void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;

    void setDepthStencilState(DepthStencilState* depthStencilState) override;

    void updateDepthStencilState(const DepthStencilDescriptor& descriptor) override;

    void updatePipelineState(const RenderTarget* rt, const PipelineDescriptor& descriptor) override;

    void readPixels(RenderTarget* rt, std::function<void(const PixelBufferDescriptor&)> callback) override;

private:
    struct Viewport
    {
        int x          = 0;
        int y          = 0;
        unsigned int w = 0;
        unsigned int h = 0;
    };

    void prepareDrawing(bool useIndex, const cc::gfx::DrawInfo& drawInfo);
    cc::gfx::AttributeList getAttributesFromProgramState(ProgramState* state);
    static cc::gfx::AttributeList generateAttributeList(ProgramState* state);
    void setUniforms(ProgramGFX* program);
    void cleanResources();
    void resetDefaultFBO();

    std::vector<cc::gfx::Swapchain*> swapchains;

    cc::gfx::CommandBuffer* _cb = nullptr;
    RenderTargetGFX* _defaultRT = nullptr;
    cc::IntrusivePtr<cc::gfx::Framebuffer> _currentFBO;
    cc::gfx::Extent _currentFBOSize;
    cc::RefVector<cc::gfx::Framebuffer*> _usedFBOs;

    cc::gfx::RenderPass* _currentPass = nullptr;
    cc::RefMap<uint32_t, cc::gfx::PipelineState*> _pstates;
    std::vector<cc::gfx::PipelineLayout*> _pLayout;
    cc::gfx::PipelineStateInfo _pstateinfo;
    XXH32_state_s* _pstateInfoHash = nullptr;
    cc::RefMap<uint32_t, cc::gfx::InputAssembler*> _inputAssemblers;
    cc::RefMap<uint32_t, cc::gfx::InputAssembler*> _usedInputAssemblers;
    std::unordered_map<uint32_t, cc::RefVector<cc::gfx::Buffer*>> _inputAssemblerBuffers;
    std::array<const void*, 3> _inputAssemblerHash = {};
    cocos2d::RefPtr<BufferGFX> _vertexBuffer;
    cocos2d::RefPtr<BufferGFX> _indexBuffer;
    cocos2d::RefPtr<ProgramState> _programState;
    RenderPipelineGFX* _renderPipeline          = nullptr;
    CullMode _cullMode                          = CullMode::NONE;
    DepthStencilStateGFX* _depthStencilStateGFX = nullptr;
    cc::gfx::Viewport _viewPort;
    std::unordered_map<const VertexLayout*, cc::gfx::AttributeList> _attributeLists;
    cocos2d::Vector<TextureBackend*> _tmpTextures;
    bool _screenResized  = false;
    bool _scissorEnabled = false;
    cc::gfx::Rect _scissorRect;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundListener = nullptr;
#endif
};

CC_BACKEND_END
