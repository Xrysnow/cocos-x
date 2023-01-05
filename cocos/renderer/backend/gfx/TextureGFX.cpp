#include "TextureGFX.h"
#include "base/ccMacros.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"
#include "platform/CCPlatformConfig.h"
#include "UtilsGFX.h"
#include <cstring>

using namespace cc;

CC_BACKEND_BEGIN

#define ISPOW2(n) (((n) & (n-1)) == 0)

namespace {
	gfx::Filter getMipmapFilter(SamplerFilter filter)
	{
		switch (filter)
		{
		case SamplerFilter::NEAREST: break;
		case SamplerFilter::NEAREST_MIPMAP_NEAREST: return gfx::Filter::POINT;
		case SamplerFilter::NEAREST_MIPMAP_LINEAR: return gfx::Filter::LINEAR;
		case SamplerFilter::LINEAR: break;
		case SamplerFilter::LINEAR_MIPMAP_LINEAR: return gfx::Filter::LINEAR;
		case SamplerFilter::LINEAR_MIPMAP_NEAREST: return gfx::Filter::POINT;
		case SamplerFilter::DONT_CARE: break;
		default:;
		}
		return gfx::Filter::NONE;
	}
	bool canGenerateMipmap(gfx::Device* device, uint32_t w, uint32_t h)
	{
		const auto api = device->getGfxAPI();
		const auto legacy = api == gfx::API::WEBGL;
		if (legacy)
			return ISPOW2(w) && ISPOW2(h);
		return true;
	}
}

Texture2DGFX::Texture2DGFX(const TextureDescriptor& descriptor)
{
	// descriptor may not ready, should wait updateData
	_textureType = TextureType::TEXTURE_2D;
	_info.type = gfx::TextureType::TEX2D;
	Texture2DGFX::updateTextureDescriptor(descriptor);
}

bool Texture2DGFX::isParameterValid()
{
	return _width != 0 && _height != 0 && _textureFormat != PixelFormat::NONE;
}

void Texture2DGFX::initWithZeros()
{
	// !!!Only used for depth stencil render buffer
	// For example, a texture used as depth buffer will not invoke updateData(), see cpp-tests 'Effect Basic/Effects
	// Advanced'.
	// FIXME: Don't call at Texture2DGL::updateTextureDescriptor, when the texture is compressed, initWithZeros will
	// cause GL Error: 0x501 We call at here once to ensure depth buffer works well. Ensure the final data size at least
	// 4 byte

	_width = (std::max)(_width, (uint32_t)1);
	_height = (std::max)(_height, (uint32_t)1);
	_bitsPerPixel = (std::max)(_bitsPerPixel, (uint8_t)(8 * 4));
	_info.width = _width;
	_info.height = _height;

	if (!_texture)
		resetTexture();

	//NOTE: size can be different sometime (DS texture)
	auto size = _width * _height * _bitsPerPixel / 8;
	const auto size1 = gfx::formatSize(_texture->getFormat(), _width, _height, 1);
	if (size != size1)
		size = size1;
	const auto data = (uint8_t*)malloc(size);
	if (data)
	{
		std::memset(data, 0, size);
		updateData(data, _width, _height, 0);
		free(data);
	}
}

void Texture2DGFX::resetTexture()
{
	CC_SAFE_DELETE(_texture);
	if (!isParameterValid())
	{
		CCASSERT(false, "invalid texture parameter");
	}
	_sampler = gfx::Device::getInstance()->getSampler(_sinfo);
	_texture = gfx::Device::getInstance()->createTexture(_info);
}

void Texture2DGFX::updateTextureDescriptor(const TextureDescriptor& descriptor, int index)
{
	TextureBackend::updateTextureDescriptor(descriptor);
	UtilsGFX::toTypes(_textureFormat, _info.format, _isCompressed);
	updateSamplerDescriptor(descriptor.samplerDescriptor);
	// check format
	if (_info.format != gfx::Format::UNKNOWN)
	{
		const auto feature = gfx::Device::getInstance()->getFormatFeatures(_info.format);
		if (!gfx::hasAnyFlags(feature, gfx::FormatFeature::RENDER_TARGET | gfx::FormatFeature::SAMPLED_TEXTURE))
		{
			CC_LOG_ERROR("pixel format %s is not supported (feature=0x%x)", gfx::GFX_FORMAT_INFOS[gfx::toNumber(_info.format)].name.c_str(), (int)feature);
		}
	}

	_info.width = _width;
	_info.height = _height;
	// 'usage' is used in vk and metal
	if (_textureUsage == TextureUsage::RENDER_TARGET)
	{
		if (_textureFormat == PixelFormat::D24S8)
			_info.usage = gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
		else // should be RGBA8
			_info.usage = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
	}
	else
	{
		_info.usage = gfx::TextureUsageBit::TRANSFER_DST | gfx::TextureUsageBit::SAMPLED;
	}
	// Update data here because `updateData()` may not be invoked later.
	//if (isParameterValid() && _textureFormat != PixelFormat::D24S8)
	if (descriptor.textureUsage == TextureUsage::RENDER_TARGET)
	{
		initWithZeros();
	}
}

Texture2DGFX::~Texture2DGFX()
{
	CC_SAFE_DELETE(_texture);
}

void Texture2DGFX::updateSamplerDescriptor(const SamplerDescriptor& sampler)
{
	_hasMipmaps = false;
	if (!_isCompressed)
	{
		// use minFilter to judge mipmap
		_sinfo.mipFilter = getMipmapFilter(sampler.minFilter);
		_hasMipmaps = _sinfo.mipFilter != gfx::Filter::NONE;
	}
	if (_hasMipmaps)
	{
		_info.flags |= gfx::TextureFlagBit::GEN_MIPMAP;
	}
	const bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
	_sinfo.magFilter = UtilsGFX::toMagFilter(sampler.magFilter);
	_sinfo.minFilter = UtilsGFX::toMinFilter(sampler.minFilter, _hasMipmaps, isPow2);
	_sinfo.addressU = UtilsGFX::toAddressMode(sampler.sAddressMode, isPow2);
	_sinfo.addressV = UtilsGFX::toAddressMode(sampler.tAddressMode, isPow2);
	_sinfo.addressW = _sinfo.addressU;
}

void Texture2DGFX::update(const gfx::BufferDataList& buffers, const gfx::BufferTextureCopyList& regions)
{
	gfx::Device::getInstance()->copyBuffersToTexture(buffers, _texture, regions);
}

void Texture2DGFX::updateData(uint8_t* data, std::size_t width, std::size_t height, std::size_t level, int index)
{
	updateSubData(0, 0, width, height, level, data);
}

void Texture2DGFX::updateCompressedData(uint8_t* data, std::size_t width, std::size_t height,
	std::size_t dataLen, std::size_t level, int index)
{
	updateCompressedSubData(0, 0, width, height, dataLen, level, data);
}

void Texture2DGFX::updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data, int index)
{
	if (!_texture)
		resetTexture();
	gfx::BufferTextureCopy region;
	region.texOffset.x = xoffset;
	region.texOffset.y = yoffset;
	region.texExtent.width = width;
	region.texExtent.height = height;
	region.texSubres.mipLevel = level;
	update({ data }, { region });
}

void Texture2DGFX::updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width,
	std::size_t height, std::size_t dataLen, std::size_t level,
	uint8_t* data, int index)
{
	if (!_texture)
		resetTexture();
	gfx::BufferTextureCopy region;
	region.texOffset.x = xoffset;
	region.texOffset.y = yoffset;
	region.texExtent.width = width;
	region.texExtent.height = height;
	region.texSubres.mipLevel = level;
	update({ data }, { region });
}

void Texture2DGFX::generateMipmaps()
{
	if (_textureUsage == TextureUsage::RENDER_TARGET || _isCompressed)
		return;
	// mipmaps can only be generated in copyBuffersToTexture,
	// but it's called on create
	//_hasMipmaps = true;
}

void Texture2DGFX::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
	if (!callback)
		return;
	//NOTE: 'copyTextureToBuffers' will wait if backend is multithreaded
	const auto device = gfx::Device::getInstance();
	const auto size = gfx::formatSize(_texture->getFormat(), width, height, 1);
	auto buffer = new uint8_t[size];
	gfx::BufferTextureCopy copy;
	copy.texOffset.x = x;
	copy.texOffset.y = y;
	copy.texExtent.width = width;
	copy.texExtent.height = height;
	gfx::BufferSrcList buffers = { buffer };
	device->copyTextureToBuffers(_texture, buffers, { copy });
	if (callback)
		callback(buffer, width, height);
	delete[] buffer;
}

TextureCubeGFX::TextureCubeGFX(const TextureDescriptor& descriptor)
{
	if (_width == 0 || _height == 0 || _width != _height)
	{
		CCASSERT(false, "invalid texture size");
	}
	_textureType = TextureType::TEXTURE_CUBE;
	_info.type = gfx::TextureType::CUBE;
	TextureCubeGFX::updateTextureDescriptor(descriptor);
	_sampler = gfx::Device::getInstance()->getSampler(_sinfo);
	_texture = gfx::Device::getInstance()->createTexture(_info);
}

void TextureCubeGFX::updateTextureDescriptor(const TextureDescriptor& descriptor, int index)
{
	TextureBackend::updateTextureDescriptor(descriptor);
	UtilsGFX::toTypes(descriptor.textureFormat, _info.format, _isCompressed);
	updateSamplerDescriptor(descriptor.samplerDescriptor);
	_info.width = _width;
	_info.height = _height;
	if (_textureUsage == TextureUsage::RENDER_TARGET)
	{
		if (_textureFormat == PixelFormat::D24S8)
			_info.usage = gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
		else // should be RGBA8
			_info.usage = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
	}
	else
	{
		_info.usage = gfx::TextureUsageBit::TRANSFER_DST | gfx::TextureUsageBit::SAMPLED;
	}
}

TextureCubeGFX::~TextureCubeGFX()
{
	CC_SAFE_DELETE(_texture);
}

void TextureCubeGFX::updateSamplerDescriptor(const SamplerDescriptor& sampler)
{
	_hasMipmaps = false;
	if (!_isCompressed)
	{
		// use minFilter to judge mipmap
		_sinfo.mipFilter = getMipmapFilter(sampler.minFilter);
		_hasMipmaps = _sinfo.mipFilter != gfx::Filter::NONE;
	}
	if (_hasMipmaps)
	{
		_info.flags |= gfx::TextureFlagBit::GEN_MIPMAP;
	}
	const bool isPow2 = ISPOW2(_width) && ISPOW2(_height);
	_sinfo.magFilter = UtilsGFX::toMagFilter(sampler.magFilter);
	_sinfo.minFilter = UtilsGFX::toMinFilter(sampler.minFilter, _hasMipmaps, isPow2);
	_sinfo.addressU = UtilsGFX::toAddressMode(sampler.sAddressMode, isPow2);
	_sinfo.addressV = UtilsGFX::toAddressMode(sampler.tAddressMode, isPow2);
	_sinfo.addressW = _sinfo.addressU;
}

void TextureCubeGFX::updateFaceData(TextureCubeFace side, void* data, int index)
{
	gfx::BufferTextureCopy region;
	region.texExtent.width = _width;
	region.texExtent.height = _height;
	region.texSubres.baseArrayLayer = (int)side;
	region.texSubres.layerCount = 1;
	gfx::Device::getInstance()->copyBuffersToTexture({ (const uint8_t*)data }, _texture, { region });
}

void TextureCubeGFX::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
	// not supported
}

void TextureCubeGFX::generateMipmaps()
{
}

//

TextureGFX::TextureGFX(const cc::gfx::TextureInfo& info)
	: TextureBackend()
{
	_info = info;
	_isPow2 = ISPOW2(info.width) && ISPOW2(info.height);
	_hasMipmaps = gfx::hasFlag(_info.flags, gfx::TextureFlagBit::GEN_MIPMAP);
	_textureType = (TextureType)3;
	_texture = gfx::Device::getInstance()->createTexture(info);
}

TextureGFX::~TextureGFX()
{
	CC_SAFE_DELETE(_texture);
}

TextureGFX* TextureGFX::create(const cc::gfx::TextureInfo& info)
{
	auto p = new (std::nothrow) TextureGFX(info);
	if (p && p->getHandler())
	{
		p->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(p);
	}
	return p;
}

void TextureGFX::setSampler(const cc::gfx::SamplerInfo& sinfo)
{
	_sinfo = sinfo;
	_sampler = gfx::Device::getInstance()->getSampler(_sinfo);
}

void TextureGFX::setSampler(cc::gfx::Sampler* sampler)
{
	_sampler = sampler;
	if (!sampler)
		_sinfo = {};
	else
		_sinfo = _sampler->getInfo();
}

void TextureGFX::update(const uint8_t* buffer)
{
	gfx::BufferTextureCopy region;
	region.texExtent.width = _info.width;
	region.texExtent.height = _info.height;
	update(buffer, region);
}

void TextureGFX::update(
	const uint8_t* buffer,
	const cc::gfx::BufferTextureCopy& region)
{
	update(
		gfx::BufferDataList{ buffer },
		gfx::BufferTextureCopyList{ region });
}

void TextureGFX::update(
	const cc::gfx::BufferDataList& buffers,
	const cc::gfx::BufferTextureCopyList& regions)
{
	CC_ASSERT(buffers.size() == regions.size());
	gfx::Device::getInstance()->copyBuffersToTexture(buffers, _texture, regions);
}

uint32_t TextureGFX::getDataSize()
{
	return gfx::formatSize(_texture->getFormat(), _info.width, _info.height, 1);
}

uint32_t TextureGFX::getDataSize(uint32_t width, uint32_t height)
{
	return gfx::formatSize(_texture->getFormat(), width, height, 1);
}

uint32_t TextureGFX::getDataSize(const cc::gfx::BufferTextureCopy& region)
{
	return gfx::formatSize(
		_texture->getFormat(),
		region.texExtent.width,
		region.texExtent.height,
		1) * region.texSubres.layerCount;
}

uint32_t TextureGFX::getData(uint8_t* buffer)
{
	const auto size = getDataSize();
	if (buffer)
	{
		gfx::BufferSrcList buffers{ buffer };
		gfx::BufferTextureCopy region;
		region.texExtent.width = _info.width;
		region.texExtent.height = _info.height;
		gfx::Device::getInstance()->copyTextureToBuffers(_texture, buffers, { region });
	}
	return size;
}

uint32_t TextureGFX::getData(std::vector<uint8_t>& buffer)
{

	gfx::BufferTextureCopy region;
	region.texExtent.width = _info.width;
	region.texExtent.height = _info.height;
	return getData(buffer, region);
}

uint32_t TextureGFX::getData(std::vector<uint8_t>& buffer,
	int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	gfx::BufferTextureCopy region;
	region.texOffset.x = x;
	region.texOffset.y = y;
	region.texExtent.width = width;
	region.texExtent.height = height;
	return getData(buffer, region);
}

uint32_t TextureGFX::getData(
	std::vector<uint8_t>& buffer,
	const cc::gfx::BufferTextureCopy& region)
{
	const auto size = getDataSize(region);
	if (buffer.size() < size)
		buffer.resize(size);
	gfx::BufferSrcList buffers{ buffer.data() };
	gfx::Device::getInstance()->copyTextureToBuffers(_texture, buffers, { region });
	return size;
}

void TextureGFX::updateTextureDescriptor(const TextureDescriptor& descriptor, int index)
{
	CC_ASSERT(false);
}

void TextureGFX::updateSamplerDescriptor(const SamplerDescriptor& sampler)
{
	CC_ASSERT(false);
}

void TextureGFX::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage,
	std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
	CC_ASSERT(false);
}

void TextureGFX::generateMipmaps()
{
	CC_ASSERT(false);
}

CC_BACKEND_END
