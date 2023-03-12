#pragma once
#include "renderer/backend/Texture.h"
#include "base/CCEventListenerCustom.h"
#include "gfx/backend/GFXDeviceManager.h"

CC_BACKEND_BEGIN

class Texture2DGFX : public Texture2DBackend
{
public:
    Texture2DGFX(const TextureDescriptor& descriptor);
    ~Texture2DGFX() override;

    void updateData(uint8_t* data, std::size_t width, std::size_t height, std::size_t level, int index = 0) override;

    void updateCompressedData(
        uint8_t* data, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level, int index = 0)
        override;

    void updateSubData(
        std::size_t xoffset,
        std::size_t yoffset,
        std::size_t width,
        std::size_t height,
        std::size_t level,
        uint8_t* data,
        int index = 0) override;

    void updateCompressedSubData(
        std::size_t xoffset,
        std::size_t yoffset,
        std::size_t width,
        std::size_t height,
        std::size_t dataLen,
        std::size_t level,
        uint8_t* data,
        int index = 0) override;

    void updateSamplerDescriptor(const SamplerDescriptor& sampler) override;

    void update(const cc::gfx::BufferDataList& buffers, const cc::gfx::BufferTextureCopyList& regions);

    void getBytes(
        std::size_t x,
        std::size_t y,
        std::size_t width,
        std::size_t height,
        bool flipImage,
        std::function<void(const unsigned char*, std::size_t, std::size_t)> callback);

    void generateMipmaps() override;

    void updateTextureDescriptor(const TextureDescriptor& descriptor, int index = 0) override;

    cc::gfx::Texture* getHandler() const { return _texture; }
    cc::gfx::Sampler* getSampler() const { return _sampler; }

private:
    bool isParameterValid();
    void initWithZeros();
    void resetTexture();

    cc::gfx::TextureInfo _info;
    cc::gfx::SamplerInfo _sinfo;
    cc::IntrusivePtr<cc::gfx::Texture> _texture;
    cc::gfx::Sampler* _sampler               = nullptr;
    EventListener* _backToForegroundListener = nullptr;
};

class TextureCubeGFX : public TextureCubemapBackend
{
public:
    TextureCubeGFX(const TextureDescriptor& descriptor);
    ~TextureCubeGFX() override;

    void updateSamplerDescriptor(const SamplerDescriptor& sampler) override;

    void updateFaceData(TextureCubeFace side, void* data, int index = 0) override;

    void getBytes(
        std::size_t x,
        std::size_t y,
        std::size_t width,
        std::size_t height,
        bool flipImage,
        std::function<void(const unsigned char*, std::size_t, std::size_t)> callback);

    void generateMipmaps() override;

    void updateTextureDescriptor(const TextureDescriptor& descriptor, int index = 0) override;

    cc::gfx::Texture* getHandler() const { return _texture; }
    cc::gfx::Sampler* getSampler() const { return _sampler; }

private:
    cc::gfx::TextureInfo _info;
    cc::gfx::SamplerInfo _sinfo;
    cc::IntrusivePtr<cc::gfx::Texture> _texture;
    cc::gfx::Sampler* _sampler               = nullptr;
    EventListener* _backToForegroundListener = nullptr;
};
// TODO:
class TextureGFX : public TextureBackend
{
    TextureGFX(const cc::gfx::TextureInfo& info);

public:
    ~TextureGFX() override;

    static TextureGFX* create(const cc::gfx::TextureInfo& info);

    void setSampler(const cc::gfx::SamplerInfo& sinfo);
    void setSampler(cc::gfx::Sampler* sampler);

    cc::gfx::Texture* getHandler() const { return _texture; }
    cc::gfx::Sampler* getSampler() const { return _sampler; }
    uint32_t getWidth() const override { return _texture->getWidth(); }
    uint32_t getHeight() const override { return _texture->getHeight(); }
    uint32_t getSize() const { return _texture->getSize(); }
    cc::gfx::Format getFormat() const { return _texture->getFormat(); }

    void update(const uint8_t* buffer);
    void update(const uint8_t* buffer, const cc::gfx::BufferTextureCopy& region);
    void update(const cc::gfx::BufferDataList& buffers, const cc::gfx::BufferTextureCopyList& regions);

    uint32_t getDataSize();
    uint32_t getDataSize(uint32_t width, uint32_t height);
    uint32_t getDataSize(const cc::gfx::BufferTextureCopy& region);
    uint32_t getData(uint8_t* buffer);
    uint32_t getData(std::vector<uint8_t>& buffer);
    uint32_t getData(std::vector<uint8_t>& buffer, int32_t x, int32_t y, uint32_t width, uint32_t height);
    uint32_t getData(std::vector<uint8_t>& buffer, const cc::gfx::BufferTextureCopy& region);

protected:
    void updateTextureDescriptor(const TextureDescriptor& descriptor, int index = 0) override;
    void updateSamplerDescriptor(const SamplerDescriptor& sampler) override;

    void getBytes(
        std::size_t x,
        std::size_t y,
        std::size_t width,
        std::size_t height,
        bool flipImage,
        std::function<void(const unsigned char*, std::size_t, std::size_t)> callback);
    void generateMipmaps() override;

private:
    cc::gfx::TextureInfo _info;
    cc::gfx::SamplerInfo _sinfo;
    cc::IntrusivePtr<cc::gfx::Texture> _texture;
    cc::gfx::Sampler* _sampler = nullptr;
    bool _isPow2               = true;
};

CC_BACKEND_END
