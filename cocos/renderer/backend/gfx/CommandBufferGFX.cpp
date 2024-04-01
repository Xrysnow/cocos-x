#include "CommandBufferGFX.h"
#include "BufferGFX.h"
#include "RenderPipelineGFX.h"
#include "TextureGFX.h"
#include "DepthStencilStateGFX.h"
#include "ProgramGFX.h"
#include "base/ccMacros.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "UtilsGFX.h"
#include "DeviceGFX.h"
#include "RenderTargetGFX.h"
#include "renderer/backend/RenderTarget.h"
#include <algorithm>

using namespace cc;

//#define USE_IA_CACHE
static std::vector<gfx::InputAssembler*> InputAssemblerRec;

CC_BACKEND_BEGIN

CommandBufferGFX::CommandBufferGFX()
{
    // get the primary command buffer
    _cb = gfx::Device::getInstance()->getCommandBuffer();
    // NOTE: when resizing, engine will pause/resume at anywhere
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(
        "glview_window_resized", [this](EventCustom*) { _screenResized = true; });
    //
    _pstateInfoHash = XXH32_createState();
}

CommandBufferGFX::~CommandBufferGFX()
{
    cleanResources();
    // NOTE: _renderPipeline belongs to Renderer
    CC_SAFE_RELEASE_NULL(_defaultFBO);

    for (auto&& it : _renderPasses)
    {
        CC_SAFE_RELEASE(it.second);
    }
    _renderPasses.clear();

    for (auto&& it : _pstates)
    {
        CC_SAFE_DELETE(it.second);
    }
    _pstates.clear();

    for (auto&& it : _inputAssemblers)
    {
        CC_SAFE_DELETE(it.second);
    }
    _inputAssemblers.clear();

    for (auto&& p : swapchains)
        delete p;
    swapchains.clear();

    XXH32_freeState(_pstateInfoHash);
}

bool CommandBufferGFX::beginFrame()
{
    // NOTE: drawing between resizing and here should be skipped, otherwise the backend will be stuck
    if (_screenResized)
    {
        const auto view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
#ifdef CC_PLATFORM_PC
        void* hdl       = view->getWindowHandle();
#else
        void* hdl       = nullptr;
#endif

        const auto fsize = Director::getInstance()->getOpenGLView()->getFrameSize();
        for (auto& sw : swapchains)
        {
            sw->resize(fsize.width, fsize.height, gfx::SurfaceTransform::IDENTITY);
        }
        DeviceGFX::setSwapchainInfo(hdl, ((DeviceGFX*)DeviceGFX::getInstance())->getVsync(), fsize.width, fsize.height);

        resetDefaultFBO();
        _currentFBO    = _defaultFBO;
        _screenResized = false;
    }

    if (swapchains.empty())
    {
        const auto d = (DeviceGFX*)Device::getInstance();
        gfx::SwapchainInfo info;
        info.windowHandle = d->getWindowHandle();
        info.vsyncMode    = d->getVsync() ? gfx::VsyncMode::ON : gfx::VsyncMode::OFF;
        info.width        = d->getWidth();
        info.height       = d->getHeight();
        const auto sw     = gfx::Device::getInstance()->createSwapchain(info);
        swapchains.push_back(sw);
    }
    // NOTE: default FBO should be created after 'acquire'
    gfx::Device::getInstance()->acquire(swapchains);

    if (!_defaultFBO)
        resetDefaultFBO();
    _cb->begin();
    return true;
}

void CommandBufferGFX::beginRenderPass(const RenderTarget* renderTarget, const RenderPassDescriptor& descirptor)
{
    const auto rt   = (const RenderTargetGFX*)renderTarget;
    auto clearFlags = gfx::ClearFlagBit::NONE;
    if (bitmask::any(descirptor.flags.clear, TargetBufferFlags::COLOR))
        clearFlags |= gfx::ClearFlagBit::COLOR;
    if (bitmask::any(descirptor.flags.clear, TargetBufferFlags::DEPTH))
        clearFlags |= gfx::ClearFlagBit::DEPTH;
    if (bitmask::any(descirptor.flags.clear, TargetBufferFlags::STENCIL))
        clearFlags |= gfx::ClearFlagBit::STENCIL;

    rt->update();
    auto info = rt->getInfo();
    // NOTE: color is always required
    if (rt->isDefaultRenderTarget() || info.colorTextures.empty())
    {
        _currentFBO     = _defaultFBO;
        _currentFBOSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    }
    else
    {
        info.renderPass = getRenderPass(clearFlags, (bool)info.depthStencilTexture, info.colorTextures[0]->getFormat());
        CC_ASSERT(info.renderPass->getColorAttachments()[0].format == info.colorTextures[0]->getFormat());
        _currentFBO     = gfx::Device::getInstance()->createFramebuffer(info);
        _generatedFBO.emplace_back(_currentFBO);

        // textures are retained in RenderTarget
        //_tmpTextures.pushBack(rt->_color[0].texture);
        // if (rt->_depth.texture)
        //	_tmpTextures.pushBack(rt->_depth.texture);

        const auto tex         = info.colorTextures[0];
        _currentFBOSize.width  = tex->getWidth();
        _currentFBOSize.height = tex->getHeight();
    }

    const auto& clearColor = descirptor.clearColorValue;
    gfx::Color color;
    color.x = clearColor[0];
    color.y = clearColor[1];
    color.z = clearColor[2];
    color.w = clearColor[3];
    // NOTE: (x,y) is left-bottom in opengl, but left-top in vulkan
    gfx::Rect rect;
    rect.x      = _viewPort.left;
    rect.y      = _viewPort.top;
    rect.width  = _viewPort.width;
    rect.height = _viewPort.height;

    if (clearFlags != gfx::ClearFlagBit::NONE && _scissorEnabled)
    {
        const auto left = std::max(_viewPort.left, _scissorRect.x);
        const auto top = std::max(_viewPort.top, _scissorRect.y);
        const auto right = std::min(_viewPort.left + _viewPort.width, _scissorRect.x + _scissorRect.width);
        const auto bottom = std::min(_viewPort.top + _viewPort.height, _scissorRect.y + _scissorRect.height);
        print("viewport=%d,%d,%d,%d | scissor=%d,%d,%d,%d",
            _viewPort.left, _viewPort.top, _viewPort.width, _viewPort.height,
            _scissorRect.x, _scissorRect.y, _scissorRect.width, _scissorRect.height
        );
    }

    CC_ASSERT(_currentFBO);
    if (_currentFBO == _defaultFBO)
        _currentPass = getRenderPass(clearFlags, true, _currentFBO->getColorTextures()[0]->getFormat());
    else
        _currentPass = _currentFBO->getRenderPass();
    // rect will be both viewport and scissor
    // NOTE: in vulkan, viewport of the whole render pass is decided here
    _cb->beginRenderPass(
        _currentPass, _currentFBO, rect, {color}, descirptor.clearDepthValue, (int)descirptor.clearStencilValue);
}

void CommandBufferGFX::setRenderPipeline(RenderPipeline* renderPipeline)
{
    _renderPipeline = static_cast<RenderPipelineGFX*>(renderPipeline);
}

void CommandBufferGFX::setViewport(int x, int y, unsigned int w, unsigned int h)
{
    _viewPort.left   = x;
    _viewPort.top    = y;
    _viewPort.width  = w;
    _viewPort.height = h;
    // NOTE: flip viewport will cause error on validation layer, so we flip through projection
#if 0
    if (gfx::Device::getInstance()->getGfxAPI() == gfx::API::VULKAN && _currentFBO == _defaultFBO)
    {
        _viewPort.top = _currentFBOSize.height - _viewPort.top;
        _viewPort.height = -_viewPort.height;
    }
#endif
    _cb->setViewport(_viewPort);
}

void CommandBufferGFX::setCullMode(CullMode mode)
{
    _cullMode = mode;
}

void CommandBufferGFX::setWinding(Winding winding)
{
    _pstateinfo.rasterizerState.isFrontFaceCCW = winding == Winding::COUNTER_CLOCK_WISE ? 1 : 0;
}

void CommandBufferGFX::setIndexBuffer(Buffer* buffer)
{
    CC_ASSERT(buffer);
    if (!buffer || _indexBuffer == buffer)
        return;
    _indexBuffer = static_cast<BufferGFX*>(buffer);
}

void CommandBufferGFX::setVertexBuffer(Buffer* buffer)
{
    CC_ASSERT(buffer);
    if (!buffer || _vertexBuffer == buffer)
        return;
    _vertexBuffer = static_cast<BufferGFX*>(buffer);
}

void CommandBufferGFX::setProgramState(ProgramState* programState)
{
    _programState = programState;
}

void CommandBufferGFX::drawArrays(PrimitiveType primitiveType, std::size_t start, std::size_t count, bool wireframe)
{
    if (_screenResized)
        return;
    if (!wireframe)
    {
        _pstateinfo.primitive                   = UtilsGFX::toPrimitiveType(primitiveType);
        _pstateinfo.rasterizerState.polygonMode = gfx::PolygonMode::FILL;
    }
    else
    {
        _pstateinfo.primitive                   = gfx::PrimitiveMode::LINE_LIST;
        _pstateinfo.rasterizerState.polygonMode = gfx::PolygonMode::LINE;
    }
    gfx::DrawInfo dinfo;
    dinfo.vertexCount = count;
    dinfo.firstVertex = start;
    prepareDrawing(false, dinfo);
    cleanResources();
}

void CommandBufferGFX::drawElements(
    PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset, bool wireframe)
{
    if (_screenResized)
        return;
    if (!wireframe)
    {
        _pstateinfo.primitive                   = UtilsGFX::toPrimitiveType(primitiveType);
        _pstateinfo.rasterizerState.polygonMode = gfx::PolygonMode::FILL;
    }
    else
    {
        _pstateinfo.primitive                   = gfx::PrimitiveMode::LINE_LIST;
        _pstateinfo.rasterizerState.polygonMode = gfx::PolygonMode::LINE;
    }
    gfx::DrawInfo dinfo;
    dinfo.indexCount = count;
    dinfo.firstIndex = offset / _indexBuffer->getHandler()->getStride();
    prepareDrawing(true, dinfo);
    cleanResources();
}

void CommandBufferGFX::endRenderPass()
{
    _cb->endRenderPass();
    _currentPass = nullptr;
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    _programState = nullptr;
}

void CommandBufferGFX::endFrame()
{
    CC_ASSERT(!_currentPass);
    _cb->end();
    gfx::Device::getInstance()->flushCommands({_cb});
    gfx::Device::getInstance()->getQueue()->submit({_cb});
    // present will wait
    gfx::Device::getInstance()->present();

    // clean
    for (auto& p : InputAssemblerRec)
    {
        CC_SAFE_DELETE(p);
    }
    InputAssemblerRec.clear();
    for (auto& p : _generatedFBO)
    {
        CC_SAFE_DELETE(p);
    }
    _generatedFBO.clear();
    _currentFBO = _defaultFBO;
    _tmpTextures.clear();
}

void CommandBufferGFX::setDepthStencilState(DepthStencilState* depthStencilState)
{
    _depthStencilStateGFX = dynamic_cast<DepthStencilStateGFX*>(depthStencilState);
    CC_ASSERT(_depthStencilStateGFX);
}

void CommandBufferGFX::updateDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    CC_ASSERT(_depthStencilStateGFX);
    _depthStencilStateGFX->update(descriptor);
}

void CommandBufferGFX::updatePipelineState(const RenderTarget* rt, const PipelineDescriptor& descriptor)
{
    _renderPipeline->update(rt, descriptor);
}

void CommandBufferGFX::setLineWidth(float lineWidth)
{
    if (lineWidth > 0.0f)
        _pstateinfo.rasterizerState.lineWidth = lineWidth;
    else
        _pstateinfo.rasterizerState.lineWidth = 1.f;
}

void CommandBufferGFX::setScissorRect(bool isEnabled, float x, float y, float width, float height)
{
    _scissorEnabled = isEnabled;
    gfx::Rect rect;
    if (isEnabled)
    {
        // flip in vulkan
        const auto api = gfx::Device::getInstance()->getGfxAPI();
        if (api == gfx::API::VULKAN && _currentFBO)
        {
            const auto h = _currentFBOSize.height;
            y            = h - y - height;
        }
        rect.x      = (int32_t)x;
        rect.y      = (int32_t)y;
        rect.width  = (uint32_t)width;
        rect.height = (uint32_t)height;
    }
    else
    {
        // TODO: use viewport?
        // rect.width = _currentFBOSize.width;
        // rect.height = _currentFBOSize.height;

        // rect.x = _viewPort.left;
        // rect.y = _viewPort.top;
        // rect.width = _viewPort.width;
        // rect.height = _viewPort.height;
        // const auto api = gfx::Device::getInstance()->getGfxAPI();
        // if (api == gfx::API::VULKAN && _currentFBO)
        //{
        //	const auto h = _currentFBOSize.height;
        //	rect.y = h - rect.y - rect.height;
        // }

        rect.width  = 32768;
        rect.height = 32768;
    }
    _scissorRect = rect;
    _cb->setScissor(rect);
}

void CommandBufferGFX::readPixels(RenderTarget* rt, std::function<void(const PixelBufferDescriptor&)> callback)
{
    PixelBufferDescriptor pbd;
    auto tex = _defaultFBO->getColorTextures()[0];
    gfx::BufferTextureCopy copy;
    if (rt->isDefaultRenderTarget())
    {
        // read from screen
        copy.texOffset.x      = _viewPort.left;
        copy.texOffset.y      = _viewPort.top;
        copy.texExtent.width  = _viewPort.width;
        copy.texExtent.height = _viewPort.height;
    }
    else
    {
        // read from attachment 0
        tex = UtilsGFX::getTexture(rt->_color[0].texture);
        CC_ASSERT(tex);
        copy.texOffset.x      = 0;
        copy.texOffset.y      = 0;
        copy.texExtent.width  = tex->getWidth();
        copy.texExtent.height = tex->getHeight();
    }
    const auto size = gfx::formatSize(tex->getFormat(), copy.texExtent.width, copy.texExtent.height, 1);
    pbd._data.resize(size);
    pbd._width                 = copy.texExtent.width;
    pbd._height                = copy.texExtent.height;
    gfx::BufferSrcList buffers = {pbd._data.data()};
    cc::gfx::Device::getInstance()->copyTextureToBuffers(tex, buffers, {copy});
    if (callback)
        callback(pbd);
}

void CommandBufferGFX::prepareDrawing(bool useIndex, const gfx::DrawInfo& drawInfo)
{
    _pstateinfo.inputState.attributes = getAttributesFromProgramState(_programState);
    _inputAssemblerHash[0] = _programState->getVertexLayout();
    if (_pstateinfo.inputState.attributes.empty())
    {
        _pstateinfo.inputState.attributes = _renderPipeline->getProgram()->getHandler()->getAttributes();
        _inputAssemblerHash[0] = _renderPipeline->getProgram()->getHandler();
    }
    _pstateinfo.dynamicStates =
        // gfx::DynamicStateFlagBit::VIEWPORT |
        // gfx::DynamicStateFlagBit::SCISSOR |
        gfx::DynamicStateFlagBit::LINE_WIDTH;

    const auto& program = _renderPipeline->getProgram();
    _pstateinfo.shader  = program->getHandler();
    CC_ASSERT(_currentPass);  // between 'beginRenderPass' and 'endRenderPass'
    _pstateinfo.renderPass = _currentPass;

    setUniforms(program);

    // Set depth/stencil state.
    if (_depthStencilStateGFX)
    {
        _depthStencilStateGFX->apply(&_pstateinfo, _stencilReferenceValueFront, _stencilReferenceValueBack);
    }
    else
    {
        DepthStencilStateGFX::reset(&_pstateinfo);
    }

    // Set cull mode.
    _pstateinfo.rasterizerState.cullMode = UtilsGFX::toCullMode(_cullMode);
    _pstateinfo.pipelineLayout = program->getDefaultPipelineLayout();
    // put states in _renderPipeline into _pstateinfo
    _renderPipeline->doUpdate(&_pstateinfo);

    XXH32_reset(_pstateInfoHash, 0);
    // for _pstateinfo.inputState.attributes
    XXH32_update(_pstateInfoHash, _inputAssemblerHash.data(), sizeof(void*));
    // merge continous members
    XXH32_update(_pstateInfoHash, &_pstateinfo.shader,
        sizeof(void*) * 3);
    XXH32_update(_pstateInfoHash, &_pstateinfo.rasterizerState,
        sizeof(_pstateinfo.rasterizerState) + sizeof(_pstateinfo.depthStencilState));
    XXH32_update(_pstateInfoHash, &_pstateinfo.blendState,
        sizeof(_pstateinfo.blendState.isA2C) + sizeof(_pstateinfo.blendState.isIndepend) + sizeof(_pstateinfo.blendState.blendColor));
    XXH32_update(_pstateInfoHash, _pstateinfo.blendState.targets.data(),
        sizeof(gfx::BlendTarget));
    XXH32_update(_pstateInfoHash, &_pstateinfo.primitive,
        sizeof(_pstateinfo.primitive) + sizeof(_pstateinfo.dynamicStates) + sizeof(_pstateinfo.bindPoint) + sizeof(_pstateinfo.subpass));
    const auto pstateKey = XXH32_digest(_pstateInfoHash);
    if (const auto it = _pstates.find(pstateKey); it != _pstates.end())
    {
        _cb->bindPipelineState(it->second);
    }
    else
    {
        const auto pstate = gfx::Device::getInstance()->createPipelineState(_pstateinfo);
        _pstates[pstateKey] = pstate;
        _cb->bindPipelineState(pstate);
    }

#ifdef USE_IA_CACHE
    _inputAssemblerHash[1] = _vertexBuffer->getHandler();
    if(useIndex)
        _inputAssemblerHash[2] = _indexBuffer->getHandler();
    const auto iaKey = XXH32(_inputAssemblerHash.data(), sizeof(void*) * (useIndex ? 3 : 2), 0);
    if (const auto it = _inputAssemblers.find(iaKey); it != _inputAssemblers.end())
    {
        it->second->setDrawInfo(drawInfo);
        _cb->bindInputAssembler(it->second);
    }
    else
#endif
    {
        gfx::InputAssemblerInfo info;
        info.attributes = _pstateinfo.inputState.attributes;
        info.vertexBuffers.push_back(_vertexBuffer->getHandler());
        if (useIndex)
            info.indexBuffer = _indexBuffer->getHandler();
        const auto inputAssembler = gfx::Device::getInstance()->createInputAssembler(info);
        inputAssembler->setDrawInfo(drawInfo);
#ifdef USE_IA_CACHE
        _inputAssemblers[iaKey] = inputAssembler;
#else
        InputAssemblerRec.push_back(inputAssembler);
#endif
        _cb->bindInputAssembler(inputAssembler);
    }

    _cb->draw(drawInfo);
}

gfx::AttributeList CommandBufferGFX::getAttributesFromProgramState(ProgramState* state)
{
    //NOTE: layout is mutable for a state, so always use layout as key
    if (!state)
        return {};
    const auto key = state->getVertexLayout();
    const auto it = _attributeLists.find(key);
    if (it != _attributeLists.end())
        return it->second;
    const auto list = generateAttributeList(state);
    _attributeLists[key] = list;
    return list;
}

gfx::AttributeList CommandBufferGFX::generateAttributeList(ProgramState* state)
{
    if (!state || !state->getVertexLayout())
        return {};
    const auto layout = state->getVertexLayout();
    const auto& attrs = layout->getAttributes();
    if (layout->isValid() && !attrs.empty())
    {
        // TODO: check stride and offset
        // const auto stride = layout->getStride();
        gfx::AttributeList dest;
        std::map<size_t, gfx::Attribute> sorted;
        for (auto& it : attrs)
        {
            const auto index = it.second.index;
            if (index >= attrs.size())
                continue;
            gfx::Attribute a;
            a.name                   = it.second.name;
            a.location               = index;
            a.format                 = UtilsGFX::toAttributeType(it.second.format);
            a.isNormalized           = it.second.needToBeNormallized;
            sorted[it.second.offset] = a;
        }
        for (auto& it : sorted)
        {
            dest.push_back(it.second);
        }
        bool ok = true;
        for (auto& it : dest)
        {
            if (it.format == gfx::Format::UNKNOWN)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            return dest;
        }
    }
    return {};
}

void CommandBufferGFX::setUniforms(ProgramGFX* program)
{
    if (!_programState)
        return;

    for (auto& cb : _programState->getCallbackUniforms())
    {
        if (cb.second)
        {
            cb.second(_programState, cb.first);
        }
        else
        {
            CC_ASSERT(false);
        }
    }

    auto stateGFX = program->getState(_programState);
    CC_ASSERT(stateGFX);
    auto ds = stateGFX->getDescriptorSet();
    stateGFX->bindBuffers(0);
    stateGFX->bindTextures(0);
    ds->update();

    _cb->bindDescriptorSet(0, ds);
}

void CommandBufferGFX::cleanResources()
{
    _indexBuffer = nullptr;
    _vertexBuffer = nullptr;
    _programState = nullptr;
}

cc::gfx::RenderPass* CommandBufferGFX::getRenderPass(
    cc::gfx::ClearFlagBit clearFlags, bool hasDepthStencil, cc::gfx::Format format)
{
    // format can be different
    const auto key = (uint32_t)clearFlags + ((uint32_t)format << 8) + (hasDepthStencil ? 0U : (1U << 31));
    if (_renderPasses.count(key))
    {
        return _renderPasses[key];
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
        binfo.prevAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
        binfo.nextAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
        ca.barrier         = gfx::Device::getInstance()->getGeneralBarrier(binfo);
    }
    info.colorAttachments = {ca};
    if (hasDepthStencil)
    {
        auto& dsa = info.depthStencilAttachment;
        // should be D24S8
        dsa.format = gfx::Format::DEPTH_STENCIL;
        // dsa.stencilStoreOp = gfx::StoreOp::DISCARD;
        // dsa.depthStoreOp = gfx::StoreOp::DISCARD;
        if (!gfx::hasAllFlags(clearFlags, gfx::ClearFlagBit::DEPTH_STENCIL))
        {
            if (!gfx::hasFlag(clearFlags, gfx::ClearFlagBit::DEPTH))
                dsa.depthLoadOp = gfx::LoadOp::LOAD;
            if (!gfx::hasFlag(clearFlags, gfx::ClearFlagBit::STENCIL))
                dsa.stencilLoadOp = gfx::LoadOp::LOAD;
            gfx::GeneralBarrierInfo binfo;
            binfo.prevAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
            binfo.nextAccesses = gfx::AccessFlagBit::FRAGMENT_SHADER_READ_TEXTURE;
            dsa.barrier        = gfx::Device::getInstance()->getGeneralBarrier(binfo);
        }
    }
    const auto rp = gfx::Device::getInstance()->createRenderPass(info);
    CC_ASSERT(rp);
    CC_SAFE_ADD_REF(rp);
    _renderPasses[key] = rp;
    return rp;
}

void CommandBufferGFX::resetDefaultFBO()
{
    CC_SAFE_RELEASE_NULL(_defaultFBO);
    gfx::FramebufferInfo fbinfo;
    const auto d = (DeviceGFX*)backend::Device::getInstance();
    for (auto& t : colorTextures)
    {
        CC_SAFE_DELETE(t);
    }
    CC_SAFE_DELETE(dsTexture);

    if (swapchains.empty())
    {
        fbinfo.renderPass = getRenderPass(gfx::ClearFlagBit::ALL, true);
        gfx::TextureInfo info;
        info.usage =
            gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED | gfx::TextureUsageBit::TRANSFER_SRC;
        info.format = gfx::Format::RGBA8;
        info.width  = d->getWidth();
        info.height = d->getHeight();
        auto ct     = gfx::Device::getInstance()->createTexture(info);
        CC_ASSERT(ct);
        fbinfo.colorTextures = {ct};
        gfx::TextureInfo info1;
        info1.usage = gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED |
                      gfx::TextureUsageBit::TRANSFER_SRC;
        info1.format = gfx::Format::DEPTH_STENCIL;
        info1.width  = d->getWidth();
        info1.height = d->getHeight();
        auto dst     = gfx::Device::getInstance()->createTexture(info1);
        CC_ASSERT(dst);
        fbinfo.depthStencilTexture = dst;
    }
    else
    {
        // get from default swapchain
        const auto sw              = swapchains[0];
        fbinfo.renderPass          = getRenderPass(gfx::ClearFlagBit::ALL, true, sw->getColorTexture()->getFormat());
        fbinfo.colorTextures       = {sw->getColorTexture()};
        fbinfo.depthStencilTexture = sw->getDepthStencilTexture();
    }
    _defaultFBO = gfx::Device::getInstance()->createFramebuffer(fbinfo);
    CC_SAFE_ADD_REF(_defaultFBO);
}

CC_BACKEND_END
