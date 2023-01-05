#pragma once
#include "base/ccMacros.h"
#include "renderer/backend/Types.h"
#include "gfx/backend/GFXDeviceManager.h"
#include "glslang/Public/ShaderLang.h"

CC_BACKEND_BEGIN

class UtilsGFX
{
public:

	static cc::gfx::Format toAttributeType(VertexFormat vertexFormat);

	static uint32_t getUniformStd140Alignment(cc::gfx::Type type, uint32_t count);
	static uint32_t getUniformStd140Size(cc::gfx::Type type, uint32_t count);
	static uint32_t getUniformStd140Offset(cc::gfx::Type type, uint32_t count, uint32_t base);
	static uint32_t getUniformStructStd140Size(uint32_t totalSize);

	static cc::gfx::Filter toMagFilter(SamplerFilter magFilter);

	static cc::gfx::Filter toMinFilter(SamplerFilter minFilter, bool hasMipmaps, bool isPow2);

	static cc::gfx::Address toAddressMode(SamplerAddressMode addressMode, bool isPow2);

	static void toTypes(PixelFormat textureFormat, cc::gfx::Format& format, bool& isCompressed);

	static cc::gfx::ComparisonFunc toComareFunction(CompareFunction compareFunction);

	static cc::gfx::StencilOp toStencilOperation(StencilOperation stencilOperation);

	static cc::gfx::BlendOp toBlendOperation(BlendOperation blendOperation);

	static cc::gfx::BlendFactor toBlendFactor(BlendFactor blendFactor);

	static cc::gfx::PrimitiveMode toPrimitiveType(PrimitiveType primitiveType);

	static cc::gfx::CullMode toCullMode(CullMode mode);

	static cc::gfx::MemoryUsageBit toMemoryUsage(BufferUsage usage);

	static cc::gfx::Format toFormat(cc::gfx::Type t);

	static cc::gfx::Texture* getTexture(TextureBackend* texture);
	static cc::gfx::Sampler* getSampler(TextureBackend* texture);

	static void glslangInitialize();

	static cc::gfx::Type toType(const glslang::TType* t);

	static EShLanguage toGLSLangShaderStage(cc::gfx::ShaderStageFlagBit type);
	static glslang::EShTargetClientVersion toGLSLangClientVersion(int vkMinorVersion);
	static glslang::EShTargetLanguageVersion toGLSLangTargetVersion(int vkMinorVersion);

	static std::vector<uint32_t> compileGLSLtoSPIRV(
		cc::gfx::ShaderStageFlagBit stage,
		const std::string& source,
		int vkMinorVersion = 2);

	static std::string compileSPIRVtoGLSL(
		const std::vector<uint32_t>& spirv,
		uint32_t version,
		bool isES
	);

	static const TBuiltInResource DefaultTBuiltInResource;
};

CC_BACKEND_END
