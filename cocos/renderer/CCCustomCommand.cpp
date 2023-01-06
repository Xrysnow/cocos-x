/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/CCCustomCommand.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"
#include "base/ccUtils.h"
#include <stddef.h>
#ifdef CC_USE_GFX
#include "renderer/backend/gfx/DeviceGFX.h"
#include "renderer/backend/gfx/BufferGFX.h"
#include "renderer/backend/gfx/UtilsGFX.h"
#endif

NS_CC_BEGIN

CustomCommand::CustomCommand()
{
    _type = RenderCommand::Type::CUSTOM_COMMAND;
}

CustomCommand::~CustomCommand()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

CustomCommand::CustomCommand(const CustomCommand& rhs)
{
    this->assign(rhs);
}

CustomCommand::CustomCommand(CustomCommand&& rhs)
{
    this->assign(std::move(rhs));
}

CustomCommand& CustomCommand::operator=(const CustomCommand& rhs)
{
    this->assign(rhs);
    return *this;
}

CustomCommand& CustomCommand::operator=(CustomCommand&& rhs)
{
    this->assign(std::move(rhs));
    return *this;
}
// Note: The use of offsetof below is technically undefined until C++17
// because State is not a standard layout type. However, all compilers
// currently provide well-defined behavior as an extension (which is
// demonstrated since constexpr evaluation must diagnose all undefined
// behavior). However, GCC and Clang also warn about this use of offsetof,
// which must be suppressed.
// see also: https://github.com/google/benchmark/pull/629
#if defined(__INTEL_COMPILER)
    #pragma warning push
    #pragma warning(disable : 1875)
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif
void CustomCommand::assign(const CustomCommand& rhs)
{
    if (this != &rhs)
    {
        auto podOffset = offsetof(CustomCommand, _type);
        auto podSize   = offsetof(CustomCommand, _beforeCallback) - podOffset;
        memcpy((uint8_t*)this + podOffset, (const uint8_t*)&rhs + podOffset, podSize);

        CC_SAFE_RETAIN(_vertexBuffer);
        CC_SAFE_RETAIN(_indexBuffer);

        _beforeCallback = rhs._beforeCallback;
        _afterCallback  = rhs._afterCallback;
    }
}

void CustomCommand::assign(CustomCommand&& rhs)
{
    if (this != &rhs)
    {
        auto podOffset = offsetof(CustomCommand, _type);
        auto podSize   = offsetof(CustomCommand, _beforeCallback) - podOffset;
        memcpy((uint8_t*)this + podOffset, (const uint8_t*)&rhs + podOffset, podSize);

        _beforeCallback = std::move(rhs._beforeCallback);
        _afterCallback  = std::move(rhs._afterCallback);

        rhs._vertexBuffer = rhs._indexBuffer = nullptr;
        rhs._pipelineDescriptor.programState = nullptr;
    }
}
#if defined(__INTEL_COMPILER)
    #pragma warning pop
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

void CustomCommand::init(float depth, const cocos2d::Mat4& modelViewTransform, unsigned int flags)
{
    RenderCommand::init(depth, modelViewTransform, flags);
}

void CustomCommand::init(float globalZOrder)
{
    _globalOrder = globalZOrder;
}

void CustomCommand::init(float globalZOrder, const BlendFunc& blendFunc)
{
    _globalOrder = globalZOrder;

    auto& blendDescriptor                = _pipelineDescriptor.blendDescriptor;
    blendDescriptor.blendEnabled         = true;
    blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendFunc.src;
    blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendFunc.dst;
}

void CustomCommand::createVertexBuffer(std::size_t vertexSize, std::size_t capacity, BufferUsage usage)
{
    CC_SAFE_RELEASE(_vertexBuffer);

    _vertexCapacity  = capacity;
    _vertexDrawCount = capacity;
#ifdef CC_USE_GFX
    cc::gfx::BufferInfo info;
    info.usage = cc::gfx::BufferUsageBit::VERTEX;
    info.memUsage = backend::UtilsGFX::toMemoryUsage(usage);
    info.size = vertexSize * capacity;
    info.stride = vertexSize;
    _vertexBuffer = new backend::BufferGFX(info);
#else
    auto device   = backend::Device::getInstance();
    _vertexBuffer = device->newBuffer(vertexSize * capacity, backend::BufferType::VERTEX, usage);
#endif
}

void CustomCommand::createIndexBuffer(IndexFormat format, std::size_t capacity, BufferUsage usage)
{
    CC_SAFE_RELEASE(_indexBuffer);

    _indexFormat    = format;
    _indexSize      = computeIndexSize();
    _indexCapacity  = capacity;
    _indexDrawCount = capacity;
#ifdef CC_USE_GFX
    cc::gfx::BufferInfo info;
    info.usage = cc::gfx::BufferUsageBit::INDEX;
    info.memUsage = backend::UtilsGFX::toMemoryUsage(usage);
    info.size = _indexSize * capacity;
    info.stride = _indexSize;
    _indexBuffer = new backend::BufferGFX(info);
#else
    auto device  = backend::Device::getInstance();
    _indexBuffer = device->newBuffer(_indexSize * capacity, backend::BufferType::INDEX, usage);
#endif
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t offset, std::size_t length)
{
    assert(_vertexBuffer);
    _vertexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t offset, std::size_t length)
{
    assert(_indexBuffer);
    _indexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::setVertexBuffer(backend::Buffer* vertexBuffer)
{
    if (_vertexBuffer == vertexBuffer)
        return;

    CC_SAFE_RELEASE(_vertexBuffer);
    _vertexBuffer = vertexBuffer;
    CC_SAFE_RETAIN(_vertexBuffer);
}

void CustomCommand::setIndexBuffer(backend::Buffer* indexBuffer, IndexFormat format)
{
    if (_indexBuffer == indexBuffer && _indexFormat == format)
        return;

    CC_SAFE_RELEASE(_indexBuffer);
    _indexBuffer = indexBuffer;
    CC_SAFE_RETAIN(_indexBuffer);

    _indexFormat = format;
    _indexSize   = computeIndexSize();
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t length)
{
    assert(_vertexBuffer);
    _vertexBuffer->updateData(data, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t length)
{
    assert(_indexBuffer);
    _indexBuffer->updateData(data, length);
}

std::size_t CustomCommand::computeIndexSize() const
{
    if (IndexFormat::U_SHORT == _indexFormat)
        return sizeof(unsigned short);
    else
        return sizeof(unsigned int);
}

NS_CC_END
