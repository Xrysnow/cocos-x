#include "BufferGFX.h"
#include <cassert>
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCEventDispatcher.h"
#include "UtilsGFX.h"

using namespace cc;

CC_BACKEND_BEGIN

BufferGFX::BufferGFX(std::size_t size, BufferType type, BufferUsage usage)
: Buffer(size, type, usage)
{
    //NOTE: this should not be used
    gfx::BufferInfo info;
    switch (type)
    {
    case BufferType::VERTEX:
        info.usage = gfx::BufferUsageBit::VERTEX;
        // note: stride should be specified here but none now
        info.stride = sizeof(V3F_C4B_T2F);
        break;
    case BufferType::INDEX:
        info.usage = gfx::BufferUsageBit::INDEX;
        // note: stride should be specified here but in CommandBufferGFX::drawElements now
        info.stride = 2;
        break;
    default: ;
    }
    info.memUsage = UtilsGFX::toMemoryUsage(usage);
    info.size = size;
	_buffer = gfx::Device::getInstance()->createBuffer(info);
    CC_ASSERT(_buffer);
}

BufferGFX::BufferGFX(const cc::gfx::BufferInfo& bufferInfo)
    : Buffer(bufferInfo.size, BufferType::VERTEX, BufferUsage::STATIC)
{
    if (bufferInfo.size == 0 ||
        bufferInfo.usage == gfx::BufferUsageBit::NONE ||
        bufferInfo.memUsage == gfx::MemoryUsageBit::NONE)
    {
        log("%s: invalid buffer info, size=%d, usage=%d, memUsage=%d", __FUNCTION__,
            bufferInfo.size, (int)bufferInfo.usage, (int)bufferInfo.memUsage);
        CC_ASSERT(false);
    }
    _buffer = gfx::Device::getInstance()->createBuffer(bufferInfo);
    CC_ASSERT(_buffer);
    updateInfo();
}

BufferGFX::BufferGFX(const cc::gfx::BufferViewInfo& bufferViewInfo)
    : Buffer(bufferViewInfo.range, BufferType::VERTEX, BufferUsage::STATIC)
{
    if (bufferViewInfo.range == 0 ||
        !bufferViewInfo.buffer ||
        bufferViewInfo.offset + bufferViewInfo.range > bufferViewInfo.buffer->getSize())
    {
        log("%s: invalid buffer view info, range=%d, offset=%d", __FUNCTION__,
            bufferViewInfo.range, bufferViewInfo.offset);
        CC_ASSERT(false);
    }
    _isView = true;
    _buffer = bufferViewInfo.buffer;
    CC_ASSERT(_buffer);
    updateInfo();
}

BufferGFX::~BufferGFX()
{
    if(!_isView)
	{
	    CC_SAFE_DELETE(_buffer);
	}
}

void BufferGFX::usingDefaultStoredData(bool needDefaultStoredData)
{
}

void BufferGFX::updateInfo()
{
    switch (_buffer->getUsage())
    {
    case gfx::BufferUsageBit::NONE: break;
    case gfx::BufferUsageBit::TRANSFER_SRC: _type = (BufferType)5; break;
    case gfx::BufferUsageBit::TRANSFER_DST: _type = (BufferType)6; break;
    case gfx::BufferUsageBit::INDEX: _type = BufferType::INDEX; break;
    case gfx::BufferUsageBit::VERTEX: _type = BufferType::VERTEX; break;
    case gfx::BufferUsageBit::UNIFORM: _type = (BufferType)2; break;
    case gfx::BufferUsageBit::STORAGE: _type = (BufferType)3; break;
    case gfx::BufferUsageBit::INDIRECT: _type = (BufferType)4; break;
    default:;
    }
    switch (_buffer->getMemUsage())
    {
    case gfx::MemoryUsageBit::NONE: break;
    case gfx::MemoryUsageBit::DEVICE: _usage = BufferUsage::STATIC; break;
    case gfx::MemoryUsageBit::HOST: _usage = BufferUsage::DYNAMIC; break;
    default:;
    }
}

void BufferGFX::updateData(void* data, std::size_t size)
{
    update(data, size);
}

void BufferGFX::updateSubData(void* data, std::size_t offset, std::size_t size)
{
    update(data, size, offset);
}

void BufferGFX::update(const void* data, std::size_t size, std::size_t offset)
{
    if (size == 0 || size > _size || !data)
    {
        CCASSERT(false, "invalid parameter to update buffer");
        return;
    }
    if (offset + size > _size)
    {
        CCASSERT(false, "buffer size overflow");
        return;
    }
    if (_isView)
    {
        CCASSERT(false, "can't update buffer view");
        return;
    }
    if (!_buffer)
    {
	    CCASSERT(false, "invalid buffer");
        return;
    }
    //NOTE: 'offset' requires modified gfx
    _buffer->update(data, size, offset);
}

CC_BACKEND_END
