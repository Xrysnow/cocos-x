/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2020 C4games Ltd.
 Copyright (c) 2022 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "renderer/CCRenderer.h"

#include <algorithm>

#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCCallbackCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCTexture2D.h"

#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "2d/CCCamera.h"
#include "2d/CCScene.h"
#include "xxhash.h"

#include "renderer/backend/Backend.h"
#include "renderer/backend/RenderTarget.h"
#ifdef CC_USE_GFX
    #include "gfx-base/GFXDef-common.h"
    #include "renderer/backend/gfx/DeviceGFX.h"
    #include "backend/gfx/BufferGFX.h"
#endif

using DepthStencilFlags = cocos2d::backend::DepthStencilFlags;
using TargetBufferFlags = cocos2d::backend::TargetBufferFlags;

NS_CC_BEGIN

#ifdef CC_USE_GFX
class TriangleBufferPool
{
public:
    struct TriangleBuffer
    {
        RefPtr<backend::BufferGFX> vb;
        RefPtr<backend::BufferGFX> ib;
        bool used              = false;
    };
    struct VertexBuffer
    {
        std::vector<V3F_C4B_T2F> data;
        size_t used = 0;
    };
    struct IndexBuffer
    {
        std::vector<uint16_t> data;
        size_t used = 0;
    };

private:
    static constexpr size_t dataBlockSize = 16384;
    std::multimap<size_t, TriangleBuffer> buffers;
    std::multimap<size_t, TriangleBuffer> usedBuffers;
    std::multimap<size_t, VertexBuffer> vDatas;
    std::multimap<size_t, IndexBuffer> iDatas;
    size_t tbVTotal = 0;
    size_t tbITotal = 0;
    size_t tbVUsed  = 0;
    size_t tbIUsed  = 0;

    size_t vbTotal = 0;
    size_t vbUsed  = 0;
    size_t ibTotal = 0;
    size_t ibUsed  = 0;

public:
    TriangleBuffer nextBuffer(size_t vnum, size_t inum)
    {
        constexpr auto vstride = sizeof(V3F_C4B_T2F);
        constexpr auto istride = sizeof(uint16_t);
        auto vsize       = vnum * vstride;
        auto isize       = inum * istride;
        size_t lastVSizeMax = 0;
        const auto key = vnum + inum;
        for (auto it = buffers.lower_bound(key); it != buffers.end(); ++it)
        {
            const auto vs = it->second.vb->getSize();
            const auto is = it->second.ib->getSize();
            if (vs >= vsize && is >= isize && !it->second.used)
            {
                it->second.used = true;
                tbVUsed += vs;
                tbIUsed += is;
                auto copy = it->second;
                usedBuffers.insert(std::pair(key, copy));
                buffers.erase(it);
                return copy;
            }
            lastVSizeMax = std::max(lastVSizeMax, it->second.vb->getSize());
        }
        // when buffer increases continuously, performance can be bad,
        // so we give redundancy here
        if (vnum > 256 && vsize < lastVSizeMax * 1.5)
        {
            vsize = size_t(vnum * 1.3) * vstride;
            isize = size_t(inum * 1.3) * istride;
        }

        TriangleBuffer b;
        const auto device = backend::Device::getInstance();
        const auto d      = dynamic_cast<backend::DeviceGFX*>(device);
        CC_ASSERT(d);
        b.vb = static_cast<backend::BufferGFX*>(
            d->newBuffer(vsize, vstride, backend::BufferType::VERTEX, backend::BufferUsage::DYNAMIC));
        b.ib = static_cast<backend::BufferGFX*>(
            d->newBuffer(isize, istride, backend::BufferType::INDEX, backend::BufferUsage::DYNAMIC));
        CC_ASSERT(b.vb);
        CC_ASSERT(b.ib);
        b.vb->autorelease();
        b.ib->autorelease();
        b.used = true;
        usedBuffers.insert(std::pair(vnum + inum, b));
        tbVTotal += vsize;
        tbITotal += isize;
        tbVUsed  += vsize;
        tbIUsed  += isize;
        return b;
    }
    V3F_C4B_T2F* nextVertexData(size_t vnum)
    {
        for (auto it = vDatas.lower_bound(vnum); it != vDatas.end(); ++it)
        {
            const auto used   = it->second.used;
            const auto unused = (ssize_t)it->second.data.size() - (ssize_t)used;
            if (unused >= vnum)
            {
                it->second.used += vnum;
                vbUsed          += vnum;
                return it->second.data.data() + used;
            }
        }
        const auto size = std::max(vnum, dataBlockSize);
        auto it         = vDatas.insert(std::pair(size, VertexBuffer{}));
        it->second.data.resize(size);
        it->second.used = vnum;
        vbTotal         += size;
        vbUsed          += vnum;
        return it->second.data.data();
    }
    uint16_t* nextIndexData(size_t inum)
    {
        for (auto it = iDatas.lower_bound(inum); it != iDatas.end(); ++it)
        {
            const auto used   = it->second.used;
            const auto unused = (ssize_t)it->second.data.size() - (ssize_t)used;
            if (unused >= inum)
            {
                it->second.used += inum;
                ibUsed         += inum;
                return it->second.data.data() + used;
            }
        }
        const auto size = std::max(inum, dataBlockSize);
        auto it         = iDatas.insert(std::pair(size, IndexBuffer{}));
        it->second.data.resize(size);
        it->second.used = inum;
        ibTotal         += size;
        ibUsed          += inum;
        return it->second.data.data();
    }
    void reuse()
    {
        {
            for (auto&& it : buffers)
            {
                tbVTotal -= it.second.vb->getSize();
                tbITotal -= it.second.ib->getSize();
            }
            buffers.clear();
            buffers = usedBuffers;
            usedBuffers.clear();
        }
        for (auto& it : buffers)
            it.second.used = false;
        tbVUsed = 0;
        tbIUsed = 0;
        //
        {
            // remove unused
            for (auto it = vDatas.begin(); it != vDatas.end();)
            {
                if (it->second.used == 0)
                {
                    vbTotal -= it->second.data.size();
                    it = vDatas.erase(it);
                }
                else
                    ++it;
            }
        }
        for (auto& it : vDatas)
            it.second.used = 0;
        vbUsed = 0;
        //
        {
            // remove unused
            for (auto it = iDatas.begin(); it != iDatas.end();)
            {
                if (it->second.used == 0)
                {
                    ibTotal -= it->second.data.size();
                    it = iDatas.erase(it);
                }
                else
                    ++it;
            }
        }
        for (auto& it : iDatas)
            it.second.used = 0;
        ibUsed = 0;
    }
    void reset()
    {
        buffers.clear();
        usedBuffers.clear();
        vDatas.clear();
        iDatas.clear();
        tbVTotal = 0;
        tbITotal = 0;
        tbVUsed = 0;
        tbIUsed = 0;
        vbTotal = 0;
        vbUsed = 0;
        ibTotal = 0;
        ibUsed = 0;
    }
    size_t getMemorySize() const
    {
        size_t total = buffers.size() * sizeof(TriangleBuffer);
        for (auto&& it : buffers)
        {
            total += it.second.ib->getSize();
            total += it.second.vb->getSize();
        }
        for (auto&& it : vDatas)
            total += sizeof(it.first) + sizeof(it.second) + it.second.data.capacity() * sizeof(V3F_C4B_T2F);
        for (auto&& it : iDatas)
            total += sizeof(it.first) + sizeof(it.second) + it.second.data.capacity() * sizeof(uint16_t);
        return total;
    }
};
static TriangleBufferPool GlobalTriangleBufferPool;
#endif  // CC_USE_GFX

// helper
static bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getGlobalOrder() < b->getGlobalOrder();
}

static bool compare3DCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getDepth() > b->getDepth();
}

// queue
RenderQueue::RenderQueue()
{
}

void RenderQueue::emplace_back(RenderCommand* command)
{
    float z = command->getGlobalOrder();
    if (z < 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_NEG].emplace_back(command);
    }
    else if (z > 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_POS].emplace_back(command);
    }
    else
    {
        if (command->is3D())
        {
            if (command->isTransparent())
            {
                _commands[QUEUE_GROUP::TRANSPARENT_3D].emplace_back(command);
            }
            else
            {
                _commands[QUEUE_GROUP::OPAQUE_3D].emplace_back(command);
            }
        }
        else
        {
            _commands[QUEUE_GROUP::GLOBALZ_ZERO].emplace_back(command);
        }
    }
}

ssize_t RenderQueue::size() const
{
    ssize_t result(0);
    for (int index = 0; index < QUEUE_GROUP::QUEUE_COUNT; ++index)
    {
        result += _commands[index].size();
    }

    return result;
}

void RenderQueue::sort()
{
    // Don't sort _queue0, it already comes sorted
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::TRANSPARENT_3D]),
                     std::end(_commands[QUEUE_GROUP::TRANSPARENT_3D]), compare3DCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_NEG]), std::end(_commands[QUEUE_GROUP::GLOBALZ_NEG]),
                     compareRenderCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_POS]), std::end(_commands[QUEUE_GROUP::GLOBALZ_POS]),
                     compareRenderCommand);
}

RenderCommand* RenderQueue::operator[](ssize_t index) const
{
    for (int queIndex = 0; queIndex < QUEUE_GROUP::QUEUE_COUNT; ++queIndex)
    {
        if (index < static_cast<ssize_t>(_commands[queIndex].size()))
            return _commands[queIndex][index];
        else
        {
            index -= _commands[queIndex].size();
        }
    }

    CCASSERT(false, "invalid index");
    return nullptr;
}

void RenderQueue::clear()
{
    for (int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
    {
        _commands[i].clear();
    }
}

void RenderQueue::realloc(size_t reserveSize)
{
    for (int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
    {
        _commands[i].clear();
        _commands[i].reserve(reserveSize);
    }
}

//
//
//
static const int DEFAULT_RENDER_QUEUE = 0;

//
// constructors, destructor, init
//
Renderer::Renderer()
{
    _groupCommandManager = new GroupCommandManager();

    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);

    _renderGroups.emplace_back();
    _queuedTriangleCommands.reserve(BATCH_TRIAGCOMMAND_RESERVED_SIZE);

    // for the batched TriangleCommand
#ifdef CC_USE_GFX
    _triBatchesToDraw = new TriBatchToDraw[_triBatchesToDrawCapacity];
#else
    _triBatchesToDraw = (TriBatchToDraw*)malloc(sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
#endif
}

Renderer::~Renderer()
{
    _renderGroups.clear();

    for (auto&& clearCommand : _callbackCommandsPool)
        delete clearCommand;
    _callbackCommandsPool.clear();

    for (auto&& clearCommand : _groupCommandPool)
        delete clearCommand;
    _groupCommandPool.clear();

    _groupCommandManager->release();

#ifdef CC_USE_GFX
    delete[] _triBatchesToDraw;
    GlobalTriangleBufferPool.reset();
#else
    free(_triBatchesToDraw);
#endif
    CC_SAFE_RELEASE(_depthStencilState);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_defaultRT);
    CC_SAFE_RELEASE(_offscreenRT);
}

void Renderer::init()
{
    // Should invoke _triangleCommandBufferManager.init() first.
    _triangleCommandBufferManager.init();
    _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
    _indexBuffer  = _triangleCommandBufferManager.getIndexBuffer();

    auto device    = backend::Device::getInstance();
    _commandBuffer = device->newCommandBuffer();
    // @MTL: the depth stencil flags must same render target and _dsDesc
    _dsDesc.flags = DepthStencilFlags::ALL;
    _defaultRT    = device->newDefaultRenderTarget(TargetBufferFlags::COLOR | TargetBufferFlags::DEPTH_AND_STENCIL);

    _currentRT      = _defaultRT;
    _renderPipeline = device->newRenderPipeline();
    _commandBuffer->setRenderPipeline(_renderPipeline);

    _depthStencilState = device->newDepthStencilState();
    _commandBuffer->setDepthStencilState(_depthStencilState);
}

backend::RenderTarget* Renderer::getOffscreenRenderTarget()
{
    if (_offscreenRT != nullptr)
        return _offscreenRT;
    return (_offscreenRT = backend::Device::getInstance()->newRenderTarget(TargetBufferFlags::COLOR |
                                                                           TargetBufferFlags::DEPTH_AND_STENCIL));
}

void Renderer::addCallbackCommand(std::function<void()> func, float globalZOrder)
{
    auto cmd = nextCallbackCommand();
    cmd->init(globalZOrder);
    cmd->func = std::move(func);
    addCommand(cmd);
}

void Renderer::addCommand(RenderCommand* command)
{
    int renderQueueID = _commandGroupStack.top();
    addCommand(command, renderQueueID);
}

void Renderer::addCommand(RenderCommand* command, int renderQueueID)
{
    CCASSERT(!_isRendering, "Cannot add command while rendering");
    CCASSERT(renderQueueID >= 0, "Invalid render queue");
    CCASSERT(command->getType() != RenderCommand::Type::UNKNOWN_COMMAND, "Invalid Command Type");

    _renderGroups[renderQueueID].emplace_back(command);
}

GroupCommand* Renderer::getNextGroupCommand()
{
    if (_groupCommandPool.empty())
    {
        return new GroupCommand();
    }

    auto* command = _groupCommandPool.back();
    _groupCommandPool.pop_back();
    command->reset();

    return command;
}

void Renderer::pushGroup(int renderQueueID)
{
    CCASSERT(!_isRendering, "Cannot change render queue while rendering");
    _commandGroupStack.push(renderQueueID);
}

void Renderer::popGroup()
{
    CCASSERT(!_isRendering, "Cannot change render queue while rendering");
    _commandGroupStack.pop();
}

int Renderer::createRenderQueue()
{
    RenderQueue newRenderQueue;
    _renderGroups.emplace_back(newRenderQueue);
    return (int)_renderGroups.size() - 1;
}

void Renderer::processGroupCommand(GroupCommand* command)
{
    flush();

    int renderQueueID = ((GroupCommand*)command)->getRenderQueueID();

    pushStateBlock();
    // apply default state for all render queues
    setDepthTest(false);
    setDepthWrite(false);
    setCullMode(backend::CullMode::NONE);
    visitRenderQueue(_renderGroups[renderQueueID]);
    popStateBlock();
}

void Renderer::processRenderCommand(RenderCommand* command)
{
    auto commandType = command->getType();
    switch (commandType)
    {
    case RenderCommand::Type::TRIANGLES_COMMAND:
    {
        // flush other queues
        flush3D();

        auto cmd = static_cast<TrianglesCommand*>(command);

        // flush own queue when buffer is full
        if (_queuedTotalVertexCount + cmd->getVertexCount() > VBO_SIZE ||
            _queuedTotalIndexCount + cmd->getIndexCount() > INDEX_VBO_SIZE)
        {
            CCASSERT(cmd->getVertexCount() >= 0 && cmd->getVertexCount() < VBO_SIZE,
                     "VBO for vertex is not big enough, please break the data down or use customized render command");
            CCASSERT(cmd->getIndexCount() >= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE,
                     "VBO for index is not big enough, please break the data down or use customized render command");
            drawBatchedTriangles();

            _queuedTotalIndexCount = _queuedTotalVertexCount = 0;
#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
            _queuedIndexCount = _queuedVertexCount = 0;
            _triangleCommandBufferManager.prepareNextBuffer();
            _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
            _indexBuffer  = _triangleCommandBufferManager.getIndexBuffer();
#endif
        }

        // queue it
        _queuedTriangleCommands.emplace_back(cmd);
#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
        _queuedIndexCount  += cmd->getIndexCount();
        _queuedVertexCount += cmd->getVertexCount();
#endif
        _queuedTotalVertexCount += cmd->getVertexCount();
        _queuedTotalIndexCount  += cmd->getIndexCount();
    }
    break;
    case RenderCommand::Type::MESH_COMMAND:
        flush2D();
        drawMeshCommand(command);
        break;
    case RenderCommand::Type::GROUP_COMMAND:
        processGroupCommand(static_cast<GroupCommand*>(command));
        _groupCommandPool.emplace_back(static_cast<GroupCommand*>(command));
        break;
    case RenderCommand::Type::CUSTOM_COMMAND:
        flush();
        drawCustomCommand(command);
        break;
    case RenderCommand::Type::CALLBACK_COMMAND:
        flush();
        static_cast<CallbackCommand*>(command)->execute();
        _callbackCommandsPool.emplace_back(static_cast<CallbackCommand*>(command));
        break;
    default:
        assert(false);
        break;
    }
}

void Renderer::visitRenderQueue(RenderQueue& queue)
{
    //
    // Process Global-Z < 0 Objects
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_NEG));

    //
    // Process Opaque Object
    //
    pushStateBlock();
    setDepthTest(true);  // enable depth test in 3D queue by default
    setDepthWrite(true);
    setCullMode(backend::CullMode::BACK);
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::OPAQUE_3D));

    //
    // Process 3D Transparent object
    //
    setDepthWrite(false);
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::TRANSPARENT_3D));
    popStateBlock();

    //
    // Process Global-Z = 0 Queue
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO));

    //
    // Process Global-Z > 0 Queue
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_POS));
}

void Renderer::doVisitRenderQueue(const std::vector<RenderCommand*>& renderCommands)
{
    for (const auto& command : renderCommands)
    {
        processRenderCommand(command);
    }
    flush();
}

void Renderer::render()
{
    // TODO: setup camera or MVP
    _isRendering = true;
    //    if (_glViewAssigned)
    {
        // Process render commands
        // 1. Sort render commands based on ID
        for (auto&& renderqueue : _renderGroups)
        {
            renderqueue.sort();
        }
        visitRenderQueue(_renderGroups[0]);
    }
    clean();
    _isRendering = false;
}

bool Renderer::beginFrame()
{
#ifdef CC_USE_GFX
    _filledVertex = 0;
    _filledIndex  = 0;
#endif
    return _commandBuffer->beginFrame();
}

void Renderer::endFrame()
{
    _commandBuffer->endFrame();

#if !defined(CC_USE_GFX) && defined(CC_USE_METAL)
    _triangleCommandBufferManager.putbackAllBuffers();
    _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
    _indexBuffer  = _triangleCommandBufferManager.getIndexBuffer();
#endif
    _queuedTotalIndexCount  = 0;
    _queuedTotalVertexCount = 0;
    GlobalTriangleBufferPool.reuse();
}

void Renderer::clean()
{
    // Clear render group
    for (size_t j = 0, size = _renderGroups.size(); j < size; j++)
    {
        // commands are owned by nodes
        //  for (const auto &cmd : _renderGroups[j])
        //  {
        //      cmd->releaseToCommandPool();
        //  }
        _renderGroups[j].clear();
    }

    // Clear batch commands
    _queuedTriangleCommands.clear();
}

void Renderer::setDepthTest(bool value)
{
    if (value)
    {
        _currentRT->addFlag(TargetBufferFlags::DEPTH);
        _dsDesc.addFlag(DepthStencilFlags::DEPTH_TEST);
    }
    else
    {
        _currentRT->removeFlag(TargetBufferFlags::DEPTH);
        _dsDesc.removeFlag(DepthStencilFlags::DEPTH_TEST);
    }
}

void Renderer::setStencilTest(bool value)
{
    if (value)
    {
        _currentRT->addFlag(TargetBufferFlags::STENCIL);
        _dsDesc.addFlag(DepthStencilFlags::STENCIL_TEST);
    }
    else
    {
        _currentRT->removeFlag(TargetBufferFlags::STENCIL);
        _dsDesc.removeFlag(DepthStencilFlags::STENCIL_TEST);
    }
}

void Renderer::setDepthWrite(bool value)
{
    if (value)
        _dsDesc.addFlag(DepthStencilFlags::DEPTH_WRITE);
    else
        _dsDesc.removeFlag(DepthStencilFlags::DEPTH_WRITE);
}

void Renderer::setDepthCompareFunction(backend::CompareFunction func)
{
    _dsDesc.depthCompareFunction = func;
}

backend::CompareFunction Renderer::getDepthCompareFunction() const
{
    return _dsDesc.depthCompareFunction;
}

bool Renderer::Renderer::getDepthTest() const
{
    return bitmask::any(_dsDesc.flags, DepthStencilFlags::DEPTH_TEST);
}

bool Renderer::getStencilTest() const
{
    return bitmask::any(_dsDesc.flags, DepthStencilFlags::STENCIL_TEST);
}

bool Renderer::getDepthWrite() const
{
    return bitmask::any(_dsDesc.flags, DepthStencilFlags::DEPTH_WRITE);
}

void Renderer::setStencilCompareFunction(backend::CompareFunction func, unsigned int ref, unsigned int readMask)
{
    _dsDesc.frontFaceStencil.stencilCompareFunction = func;
    _dsDesc.backFaceStencil.stencilCompareFunction  = func;

    _dsDesc.frontFaceStencil.readMask = readMask;
    _dsDesc.backFaceStencil.readMask  = readMask;

    _stencilRef = ref;
}

void Renderer::setStencilOperation(backend::StencilOperation stencilFailureOp, backend::StencilOperation depthFailureOp,
                                   backend::StencilOperation stencilDepthPassOp)
{
    _dsDesc.frontFaceStencil.stencilFailureOperation = stencilFailureOp;
    _dsDesc.backFaceStencil.stencilFailureOperation  = stencilFailureOp;

    _dsDesc.frontFaceStencil.depthFailureOperation = depthFailureOp;
    _dsDesc.backFaceStencil.depthFailureOperation  = depthFailureOp;

    _dsDesc.frontFaceStencil.depthStencilPassOperation = stencilDepthPassOp;
    _dsDesc.backFaceStencil.depthStencilPassOperation  = stencilDepthPassOp;
}

void Renderer::setStencilWriteMask(unsigned int mask)
{
    _dsDesc.frontFaceStencil.writeMask = mask;
    _dsDesc.backFaceStencil.writeMask  = mask;
}

backend::StencilOperation Renderer::getStencilFailureOperation() const
{
    return _dsDesc.frontFaceStencil.stencilFailureOperation;
}

backend::StencilOperation Renderer::getStencilPassDepthFailureOperation() const
{
    return _dsDesc.frontFaceStencil.depthFailureOperation;
}

backend::StencilOperation Renderer::getStencilDepthPassOperation() const
{
    return _dsDesc.frontFaceStencil.depthStencilPassOperation;
}

backend::CompareFunction Renderer::getStencilCompareFunction() const
{
    return _dsDesc.depthCompareFunction;
}

unsigned int Renderer::getStencilReadMask() const
{
    return _dsDesc.frontFaceStencil.readMask;
}

unsigned int Renderer::getStencilWriteMask() const
{
    return _dsDesc.frontFaceStencil.writeMask;
}

unsigned int Renderer::getStencilReferenceValue() const
{
    return _stencilRef;
}

void Renderer::setDepthStencilDesc(const backend::DepthStencilDescriptor& dsDesc)
{
    _dsDesc = dsDesc;
}

const backend::DepthStencilDescriptor& Renderer::getDepthStencilDesc() const
{
    return _dsDesc;
}

void Renderer::setViewPort(int x, int y, unsigned int w, unsigned int h)
{
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = w;
    _viewport.h = h;
}

void Renderer::fillVerticesAndIndices(const TrianglesCommand* cmd, unsigned int vertexBufferOffset)
{
#ifndef CC_USE_GFX
    size_t vertexCount = cmd->getVertexCount();
    memcpy(&_verts[_filledVertex], cmd->getVertices(), sizeof(V3F_C4B_T2F) * vertexCount);

    if (!c->isSkipModelView())
    {
        // fill vertex, and convert them to world coordinates
        const Mat4& modelView = cmd->getModelView();
        for (size_t i = 0; i < vertexCount; ++i)
        {
            modelView.transformPoint(&(_verts[i + _filledVertex].vertices));
        }
    }

    // fill index
    const unsigned short* indices = cmd->getIndices();
    size_t indexCount             = cmd->getIndexCount();
    for (size_t i = 0; i < indexCount; ++i)
    {
        _indices[_filledIndex + i] = vertexBufferOffset + _filledVertex + indices[i];
    }

    _filledVertex += vertexCount;
    _filledIndex  += indexCount;
#endif
}

#ifdef CC_USE_GFX
void Renderer::drawBatchedTriangles()
{
    if (_queuedTriangleCommands.empty())
        return;

    /************** 1: Setup up vertices/indices *************/

    _triBatchesToDraw[0].indicesToDraw = 0;
    _triBatchesToDraw[0].cmd           = nullptr;

    int batchesTotal   = 0;
    int prevMaterialID = -1;
    bool firstCommand  = true;

    for (const auto& cmd : _queuedTriangleCommands)
    {
        auto currentMaterialID = cmd->getMaterialID();
        const bool indicesFull = _triBatchesToDraw[batchesTotal].indicesToDraw + cmd->getIndexCount() >= (1u << 16);
        const bool batchable = !cmd->isSkipBatching() && !indicesFull;

        // in the same batch ?
        if (batchable && (prevMaterialID == currentMaterialID || firstCommand))
        {
            CC_ASSERT((firstCommand || _triBatchesToDraw[batchesTotal].cmd->getMaterialID() == cmd->getMaterialID()) &&
                      "argh... error in logic");
            if (_triBatchesToDraw[batchesTotal].indicesToDraw == 0)
                _triBatchesToDraw[batchesTotal].cmds = {cmd};
            else
                _triBatchesToDraw[batchesTotal].cmds.push_back(cmd);
            _triBatchesToDraw[batchesTotal].indicesToDraw += cmd->getIndexCount();
            _triBatchesToDraw[batchesTotal].cmd           = cmd;
        }
        else
        {
            // is this the first one?
            if (!firstCommand)
            {
                batchesTotal++;
            }

            _triBatchesToDraw[batchesTotal].cmd           = cmd;
            _triBatchesToDraw[batchesTotal].cmds          = {cmd};
            _triBatchesToDraw[batchesTotal].indicesToDraw = (int)cmd->getIndexCount();

            // is this a single batch ? Prevent creating a batch group then
            if (!batchable)
                currentMaterialID = -1;
        }

        // capacity full ?
        if (batchesTotal + 1 >= _triBatchesToDrawCapacity)
        {
            int newSize           = _triBatchesToDrawCapacity * 1.4;
            auto triBatchesToDraw = new TriBatchToDraw[newSize];
            for (int i = 0; i < _triBatchesToDrawCapacity; ++i)
                triBatchesToDraw[i] = _triBatchesToDraw[i];
            delete[] _triBatchesToDraw;
            _triBatchesToDraw         = triBatchesToDraw;
            _triBatchesToDrawCapacity = newSize;
        }

        prevMaterialID = currentMaterialID;
        firstCommand   = false;
    }
    batchesTotal++;

    /************** 2: Draw *************/
    beginRenderPass();

    for (int i = 0; i < batchesTotal; ++i)
    {
        const auto& tb = _triBatchesToDraw[i];
        size_t vTotal  = 0;
        size_t iTotal  = 0;
        for (auto& c : tb.cmds)
        {
            vTotal += c->getVertexCount();
            iTotal += c->getIndexCount();
        }
        const auto vbuffer = GlobalTriangleBufferPool.nextVertexData(vTotal);
        const auto ibuffer = GlobalTriangleBufferPool.nextIndexData(iTotal);
        size_t vCurrent    = 0;
        size_t iCurrent    = 0;
        for (auto& c : tb.cmds)
        {
            const auto vcount = c->getVertexCount();
            const auto icount = c->getIndexCount();
            memcpy(vbuffer + vCurrent, c->getVertices(), sizeof(V3F_C4B_T2F) * vcount);
            if (!c->isSkipModelView())
            {
                const auto& modelView = c->getModelView();
                for (size_t j = 0; j < vcount; ++j)
                    modelView.transformPoint(&((vbuffer + vCurrent + j)->vertices));
            }
            const auto indices = c->getIndices();
            for (size_t j = 0; j < icount; ++j)
                ibuffer[iCurrent + j] = vCurrent + indices[j];
            vCurrent += vcount;
            iCurrent += icount;
        }
        auto b = GlobalTriangleBufferPool.nextBuffer(vTotal, iTotal);
        b.vb->updateData(vbuffer, sizeof(V3F_C4B_T2F) * vTotal);
        b.ib->updateData(ibuffer, sizeof(uint16_t) * iTotal);
        _filledVertex += vTotal;
        _filledIndex  += iTotal;
        CC_ASSERT(iTotal == tb.indicesToDraw);

        // beginRenderPass(tb.cmd);
        _commandBuffer->setVertexBuffer(b.vb);
        _commandBuffer->setIndexBuffer(b.ib);
        auto& pipelineDescriptor = tb.cmd->getPipelineDescriptor();
        _commandBuffer->updatePipelineState(_currentRT, tb.cmd->getPipelineDescriptor());
        _commandBuffer->setProgramState(pipelineDescriptor.programState);
        _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE, backend::IndexFormat::U_SHORT, tb.indicesToDraw,
                                     0);

        //_commandBuffer->endRenderPass();

        _drawnBatches++;
        _drawnVertices += tb.indicesToDraw;
    }

    endRenderPass();
    /************** 3: Cleanup *************/
    _queuedTriangleCommands.clear();
}

#else

void Renderer::drawBatchedTriangles()
{
    if (_queuedTriangleCommands.empty())
        return;

        /************** 1: Setup up vertices/indices *************/
    #ifdef CC_USE_METAL
    unsigned int vertexBufferFillOffset = _queuedTotalVertexCount - _queuedVertexCount;
    unsigned int indexBufferFillOffset = _queuedTotalIndexCount - _queuedIndexCount;
    #else
    unsigned int vertexBufferFillOffset = 0;
    unsigned int indexBufferFillOffset  = 0;
    #endif

    _triBatchesToDraw[0].offset = indexBufferFillOffset;
    _triBatchesToDraw[0].indicesToDraw = 0;
    _triBatchesToDraw[0].cmd = nullptr;

    int batchesTotal = 0;
    uint32_t prevMaterialID = 0;
    bool firstCommand = true;

    _filledVertex = 0;
    _filledIndex = 0;

    for (const auto& cmd : _queuedTriangleCommands)
    {
        auto currentMaterialID = cmd->getMaterialID();
        const bool batchable = !cmd->isSkipBatching();

        fillVerticesAndIndices(cmd, vertexBufferFillOffset);

        // in the same batch ?
        if (batchable && (prevMaterialID == currentMaterialID || firstCommand))
        {
            CC_ASSERT((firstCommand || _triBatchesToDraw[batchesTotal].cmd->getMaterialID() == cmd->getMaterialID()) &&
                      "argh... error in logic");
            _triBatchesToDraw[batchesTotal].indicesToDraw += cmd->getIndexCount();
            _triBatchesToDraw[batchesTotal].cmd = cmd;
        }
        else
        {
            // is this the first one?
            if (!firstCommand)
            {
                batchesTotal++;
                _triBatchesToDraw[batchesTotal].offset =
                    _triBatchesToDraw[batchesTotal - 1].offset + _triBatchesToDraw[batchesTotal - 1].indicesToDraw;
            }

            _triBatchesToDraw[batchesTotal].cmd = cmd;
            _triBatchesToDraw[batchesTotal].indicesToDraw = (int)cmd->getIndexCount();

            // is this a single batch ? Prevent creating a batch group then
            if (!batchable)
                currentMaterialID = 0;
        }

        // capacity full ?
        if (batchesTotal + 1 >= _triBatchesToDrawCapacity)
        {
            _triBatchesToDrawCapacity *= 1.4;
            _triBatchesToDraw =
                (TriBatchToDraw*)realloc(_triBatchesToDraw, sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
        }

        prevMaterialID = currentMaterialID;
        firstCommand = false;
    }
    batchesTotal++;
    #ifdef CC_USE_METAL
    _vertexBuffer->updateSubData(_verts, vertexBufferFillOffset * sizeof(_verts[0]), _filledVertex * sizeof(_verts[0]));
    _indexBuffer->updateSubData(_indices, indexBufferFillOffset * sizeof(_indices[0]),
                                _filledIndex * sizeof(_indices[0]));
    #else
    _vertexBuffer->updateData(_verts, _filledVertex * sizeof(_verts[0]));
    _indexBuffer->updateData(_indices, _filledIndex * sizeof(_indices[0]));
    #endif

    /************** 2: Draw *************/
    beginRenderPass();

    _commandBuffer->setVertexBuffer(_vertexBuffer);
    _commandBuffer->setIndexBuffer(_indexBuffer);

    for (int i = 0; i < batchesTotal; ++i)
    {
        auto& drawInfo = _triBatchesToDraw[i];
        _commandBuffer->updatePipelineState(_currentRT, drawInfo.cmd->getPipelineDescriptor());
        auto& pipelineDescriptor = drawInfo.cmd->getPipelineDescriptor();
        _commandBuffer->setProgramState(pipelineDescriptor.programState);
        _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE, backend::IndexFormat::U_SHORT,
                                     drawInfo.indicesToDraw, drawInfo.offset * sizeof(_indices[0]));

        _drawnBatches++;
        _drawnVertices += _triBatchesToDraw[i].indicesToDraw;
    }

    endRenderPass();

    /************** 3: Cleanup *************/
    _queuedTriangleCommands.clear();

    #ifdef CC_USE_METAL
    _queuedIndexCount = 0;
    _queuedVertexCount = 0;
    #endif
}
#endif

void Renderer::drawCustomCommand(RenderCommand* command)
{
    auto cmd = static_cast<CustomCommand*>(command);

    if (cmd->getBeforeCallback())
        cmd->getBeforeCallback()();

    beginRenderPass();
    _commandBuffer->setVertexBuffer(cmd->getVertexBuffer());

    _commandBuffer->updatePipelineState(_currentRT, cmd->getPipelineDescriptor());
    _commandBuffer->setProgramState(cmd->getPipelineDescriptor().programState);

    auto drawType = cmd->getDrawType();
    _commandBuffer->setLineWidth(cmd->getLineWidth());
    if (CustomCommand::DrawType::ELEMENT == drawType)
    {
        _commandBuffer->setIndexBuffer(cmd->getIndexBuffer());
        _commandBuffer->drawElements(cmd->getPrimitiveType(), cmd->getIndexFormat(), cmd->getIndexDrawCount(),
                                     cmd->getIndexDrawOffset(), cmd->isWireframe());
        _drawnVertices += cmd->getIndexDrawCount();
    }
    else
    {
        _commandBuffer->drawArrays(cmd->getPrimitiveType(), cmd->getVertexDrawStart(), cmd->getVertexDrawCount(),
                                   cmd->isWireframe());
        _drawnVertices += cmd->getVertexDrawCount();
    }
    _drawnBatches++;
    endRenderPass();

    if (cmd->getAfterCallback())
        cmd->getAfterCallback()();
}

void Renderer::drawMeshCommand(RenderCommand* command)
{
    // MeshCommand and CustomCommand are identical while rendering.
    drawCustomCommand(command);
}

void Renderer::flush()
{
    flush2D();
    flush3D();
}

void Renderer::flush2D()
{
    flushTriangles();
}

void Renderer::flush3D()
{
    // TODO 3d instanced rendering
    // https://learnopengl.com/Advanced-OpenGL/Instancing
}

void Renderer::flushTriangles()
{
    drawBatchedTriangles();
}

// helpers
bool Renderer::checkVisibility(const Mat4& transform, const Vec2& size)
{
    auto director = Director::getInstance();
    auto scene    = director->getRunningScene();

    // If draw to Rendertexture, return true directly.
    //  only cull the default camera. The culling algorithm is valid for default camera.
    if (!scene || (scene && scene->_defaultCamera != Camera::getVisitingCamera()))
        return true;

    Rect visibleRect(director->getVisibleOrigin(), director->getVisibleSize());

    // transform center point to screen space
    float hSizeX = size.width / 2;
    float hSizeY = size.height / 2;
    Vec3 v3p(hSizeX, hSizeY, 0);
    transform.transformPoint(&v3p);
    Vec2 v2p = Camera::getVisitingCamera()->projectGL(v3p);

    // convert content size to world coordinates
    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]),
                          fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]),
                          fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));

    // enlarge visible rect half size in screen coord
    visibleRect.origin.x    -= wshw;
    visibleRect.origin.y    -= wshh;
    visibleRect.size.width  += wshw * 2;
    visibleRect.size.height += wshh * 2;
    bool ret                = visibleRect.containsPoint(v2p);
    return ret;
}

void Renderer::readPixels(backend::RenderTarget* rt,
                          std::function<void(const backend::PixelBufferDescriptor&)> callback)
{
    assert(!!rt);
    // read pixels from screen, metal renderer backend: screen texture must not be a framebufferOnly
    if (rt == _defaultRT)
        backend::Device::getInstance()->setFrameBufferOnly(false);

    _commandBuffer->readPixels(rt, std::move(callback));
}

void Renderer::beginRenderPass()
{
#ifdef CC_USE_GFX
    // CommandBufferGFX::beginRenderPass requires viewport
    _commandBuffer->setViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
#endif  // CC_USE_GFX
    _commandBuffer->beginRenderPass(_currentRT, _renderPassDesc);
    _commandBuffer->updateDepthStencilState(_dsDesc);
    _commandBuffer->setStencilReferenceValue(_stencilRef);
#ifndef CC_USE_GFX
    _commandBuffer->setViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
#endif  // !CC_USE_GFX
    _commandBuffer->setCullMode(_cullMode);
    _commandBuffer->setWinding(_winding);
    _commandBuffer->setScissorRect(_scissorState.isEnabled, _scissorState.rect.x, _scissorState.rect.y,
                                   _scissorState.rect.width, _scissorState.rect.height);
}

void Renderer::endRenderPass()
{
    _commandBuffer->endRenderPass();
}

void Renderer::clear(ClearFlag flags, const Color4F& color, float depth, unsigned int stencil, float globalOrder)
{
    _clearFlag = flags;

    CallbackCommand* command = nextCallbackCommand();
    command->init(globalOrder);
    command->func = [=]() -> void {
        backend::RenderPassDescriptor descriptor;

        descriptor.flags.clear = flags;
        if (bitmask::any(flags, ClearFlag::COLOR))
        {
            _clearColor                = color;
            descriptor.clearColorValue = {color.r, color.g, color.b, color.a};
        }

        if (bitmask::any(flags, ClearFlag::DEPTH))
            descriptor.clearDepthValue = depth;

        if (bitmask::any(flags, ClearFlag::STENCIL))
            descriptor.clearStencilValue = stencil;

        _commandBuffer->beginRenderPass(_currentRT, descriptor);
        _commandBuffer->endRenderPass();
    };
    addCommand(command);
}

CallbackCommand* Renderer::nextCallbackCommand()
{
    CallbackCommand* cmd = nullptr;
    if (!_callbackCommandsPool.empty())
    {
        cmd = _callbackCommandsPool.back();
        cmd->reset();
        _callbackCommandsPool.pop_back();
    }
    else
        cmd = new CallbackCommand();
    return cmd;
}

const Color4F& Renderer::getClearColor() const
{
    return _clearColor;
}

float Renderer::getClearDepth() const
{
    return _renderPassDesc.clearDepthValue;
}

unsigned int Renderer::getClearStencil() const
{
    return _renderPassDesc.clearStencilValue;
}

ClearFlag Renderer::getClearFlag() const
{
    return _clearFlag;
}

RenderTargetFlag Renderer::getRenderTargetFlag() const
{
    return _currentRT->getTargetFlags();
}

void Renderer::setScissorTest(bool enabled)
{
    _scissorState.isEnabled = enabled;
}

bool Renderer::getScissorTest() const
{
    return _scissorState.isEnabled;
}

const ScissorRect& Renderer::getScissorRect() const
{
    return _scissorState.rect;
}

void Renderer::setScissorRect(float x, float y, float width, float height)
{
    _scissorState.rect.x      = x;
    _scissorState.rect.y      = y;
    _scissorState.rect.width  = width;
    _scissorState.rect.height = height;
}

// TriangleCommandBufferManager
Renderer::TriangleCommandBufferManager::~TriangleCommandBufferManager()
{
    for (auto&& vertexBuffer : _vertexBufferPool)
        vertexBuffer->release();

    for (auto&& indexBuffer : _indexBufferPool)
        indexBuffer->release();
}

void Renderer::TriangleCommandBufferManager::init()
{
    createBuffer();
}

void Renderer::TriangleCommandBufferManager::putbackAllBuffers()
{
    _currentBufferIndex = 0;
}

void Renderer::TriangleCommandBufferManager::prepareNextBuffer()
{
    if (_currentBufferIndex < (int)_vertexBufferPool.size() - 1)
    {
        ++_currentBufferIndex;
        return;
    }

    createBuffer();
    ++_currentBufferIndex;
}

backend::Buffer* Renderer::TriangleCommandBufferManager::getVertexBuffer() const
{
    return _vertexBufferPool[_currentBufferIndex];
}

backend::Buffer* Renderer::TriangleCommandBufferManager::getIndexBuffer() const
{
    return _indexBufferPool[_currentBufferIndex];
}

void Renderer::TriangleCommandBufferManager::createBuffer()
{
    backend::Buffer* vertexBuffer = nullptr;
    backend::Buffer* indexBuffer  = nullptr;
    const auto device             = backend::Device::getInstance();
#if defined(CC_USE_GFX)
    const auto d           = static_cast<backend::DeviceGFX*>(device);
    constexpr auto vstride = sizeof(_verts[0]);
    constexpr auto istride = sizeof(_indices[0]);
    vertexBuffer =
        d->newBuffer(VBO_SIZE * vstride, vstride, backend::BufferType::VERTEX, backend::BufferUsage::DYNAMIC);
    if (!vertexBuffer)
        return;
    indexBuffer =
        d->newBuffer(INDEX_VBO_SIZE * istride, istride, backend::BufferType::INDEX, backend::BufferUsage::DYNAMIC);
    if (!indexBuffer)
    {
        vertexBuffer->release();
        return;
    }
#elif defined(CC_USE_METAL)
    // Metal doesn't need to update buffer to make sure it has the correct size.
    vertexBuffer = device->newBuffer(Renderer::VBO_SIZE * sizeof(_verts[0]), backend::BufferType::VERTEX,
                                     backend::BufferUsage::DYNAMIC);
    if (!vertexBuffer)
        return;

    indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE * sizeof(_indices[0]), backend::BufferType::INDEX,
                                    backend::BufferUsage::DYNAMIC);
    if (!indexBuffer)
    {
        vertexBuffer->release();
        return;
    }
#else
    auto tmpData = malloc(Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F));
    if (!tmpData)
        return;

    vertexBuffer = device->newBuffer(Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F), backend::BufferType::VERTEX,
                                     backend::BufferUsage::DYNAMIC);
    if (!vertexBuffer)
    {
        free(tmpData);
        return;
    }
    vertexBuffer->updateData(tmpData, Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F));

    indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE * sizeof(unsigned short), backend::BufferType::INDEX,
                                    backend::BufferUsage::DYNAMIC);
    if (!indexBuffer)
    {
        free(tmpData);
        vertexBuffer->release();
        return;
    }
    indexBuffer->updateData(tmpData, Renderer::INDEX_VBO_SIZE * sizeof(unsigned short));

    free(tmpData);
#endif

    _vertexBufferPool.emplace_back(vertexBuffer);
    _indexBufferPool.emplace_back(indexBuffer);
}

void Renderer::pushStateBlock()
{
    StateBlock block;
    block.depthTest  = getDepthTest();
    block.depthWrite = getDepthWrite();
    block.cullMode   = getCullMode();
    _stateBlockStack.emplace_back(block);
}

void Renderer::popStateBlock()
{
    auto& block = _stateBlockStack.back();
    setDepthTest(block.depthTest);
    setDepthWrite(block.depthWrite);
    setCullMode(block.cullMode);
    _stateBlockStack.pop_back();
}

NS_CC_END
