#pragma once
#include "renderer/backend/Buffer.h"
#include "base/CCEventListenerCustom.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

class BufferGFX : public Buffer
{
public:
    BufferGFX(std::size_t size, BufferType type, BufferUsage usage);
    BufferGFX(const cc::gfx::BufferInfo& bufferInfo);
    BufferGFX(const cc::gfx::BufferViewInfo& bufferViewInfo);
    ~BufferGFX() override;

    void updateData(void* data, std::size_t size) override;
    void updateSubData(void* data, std::size_t offset, std::size_t size) override;
    void update(const void* data, std::size_t size, std::size_t offset = 0);
    // no usage
    void usingDefaultStoredData(bool needDefaultStoredData) override;

    cc::gfx::Buffer* getHandler() const { return _buffer; }

private:
    void updateInfo();

    cc::IntrusivePtr<cc::gfx::Buffer> _buffer;
    bool _isView = false;
};

CC_BACKEND_END
