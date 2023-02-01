#pragma once
#include "renderer/backend/Device.h"

CC_BACKEND_BEGIN

/**
 * Use to create resoureces.
 */
class DeviceGFX : public Device
{
	void* windowHandle = nullptr;
	uint32_t width = 0;
	uint32_t height = 0;
	bool vsync = true;
public:
	static DeviceGFX* getInstance();
	static void setSwapchainInfo(void* windowHandle, bool vsync, uint32_t width, uint32_t height);
	static bool isAvailable();
	static void destroy();

	enum API : uint32_t {
		UNKNOWN,
		GLES2,
		GLES3,
		METAL,
		VULKAN,
		NVN,
		WEBGL,
		WEBGL2,
		WEBGPU,
	};

	static API getAPI();

	DeviceGFX();
	~DeviceGFX();

	/**
	 * New a CommandBuffer object, not auto released.
	 * @return A CommandBuffer object.
	 */
	CommandBuffer* newCommandBuffer() override;

	/**
	 * New a Buffer object, not auto released.
	 * @param size Specifies the size in bytes of the buffer object's new data store.
	 * @param type Specifies the target buffer object. The symbolic constant must be BufferType::VERTEX or BufferType::INDEX.
	 * @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be BufferUsage::STATIC, BufferUsage::DYNAMIC.
	 * @return A Buffer object.
	 */
	Buffer* newBuffer(std::size_t size, BufferType type, BufferUsage usage) override;
	Buffer* newBuffer(uint32_t size, uint32_t stride, BufferType type, BufferUsage usage);

	/**
	 * New a TextureBackend object, not auto released.
	 * @param descriptor Specifies texture description.
	 * @return A TextureBackend object.
	 */
	TextureBackend* newTexture(const TextureDescriptor& descriptor) override;

	RenderTarget* newDefaultRenderTarget(TargetBufferFlags rtf) override;

	RenderTarget* newRenderTarget(TargetBufferFlags rtf,
		TextureBackend* colorAttachment = nullptr,
		TextureBackend* depthAttachment = nullptr,
		TextureBackend* stencilAttachhment = nullptr) override;

	/**
	 * Create an auto released DepthStencilState object.
	 * @return An auto release DepthStencilState object.
	 */
	DepthStencilState* newDepthStencilState() override;

	/**
	 * New a RenderPipeline object, not auto released.
	 * @return A RenderPipeline object.
	 */
	RenderPipeline* newRenderPipeline() override;

	/**
	 * Design for metal.
	 */
	void setFrameBufferOnly(bool frameBufferOnly) override {}

	/**
	 * New a Program, not auto released.
	 * @param vertexShader Specifes this is a vertex shader source.
	 * @param fragmentShader Specifes this is a fragment shader source.
	 * @return A Program instance.
	 */
	Program* newProgram(std::string_view vertexShader, std::string_view fragmentShader) override;

	enum class Type : uint32_t {
		UNKNOWN,
		BOOL,
		BOOL2,
		BOOL3,
		BOOL4,
		INT,
		INT2,
		INT3,
		INT4,
		UINT,
		UINT2,
		UINT3,
		UINT4,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MAT2,
		MAT2X3,
		MAT2X4,
		MAT3X2,
		MAT3,
		MAT3X4,
		MAT4X2,
		MAT4X3,
		MAT4,
		// combined image samplers
		SAMPLER1D,
		SAMPLER1D_ARRAY,
		SAMPLER2D,
		SAMPLER2D_ARRAY,
		SAMPLER3D,
		SAMPLER_CUBE,
		// sampler
		SAMPLER,
		// sampled textures
		TEXTURE1D,
		TEXTURE1D_ARRAY,
		TEXTURE2D,
		TEXTURE2D_ARRAY,
		TEXTURE3D,
		TEXTURE_CUBE,
		// storage images
		IMAGE1D,
		IMAGE1D_ARRAY,
		IMAGE2D,
		IMAGE2D_ARRAY,
		IMAGE3D,
		IMAGE_CUBE,
		// input attachment
		SUBPASS_INPUT,
		COUNT,
	};
	enum class MemoryAccessBit : uint32_t {
		NONE = 0,
		READ_ONLY = 0x1,
		WRITE_ONLY = 0x2,
		READ_WRITE = READ_ONLY | WRITE_ONLY,
	};
	using MemoryAccess = MemoryAccessBit;
	enum class ShaderStageFlagBit : uint32_t {
		NONE = 0x0,
		VERTEX = 0x1,
		CONTROL = 0x2,
		EVALUATION = 0x4,
		GEOMETRY = 0x8,
		FRAGMENT = 0x10,
		COMPUTE = 0x20,
		ALL = 0x3f,
	};
	using ShaderStageFlags = ShaderStageFlagBit;
	struct Uniform {
		std::string name;
		Type     type{ Type::UNKNOWN };
		uint32_t count{ 0 };
	};
	using UniformList = std::vector<Uniform>;
	struct UniformBlock {
		uint32_t    set{ 0 };
		uint32_t    binding{ 0 };
		std::string name;
		UniformList members;
		uint32_t    count{ 0 };
	};
	using UniformBlockList = std::vector<UniformBlock>;
	struct UniformSamplerTexture {
		uint32_t set{ 0 };
		uint32_t binding{ 0 };
		std::string name;
		Type     type{ Type::UNKNOWN };
		uint32_t count{ 0 };
	};
	using UniformSamplerTextureList = std::vector<UniformSamplerTexture>;
	struct UniformStorageBuffer {
		uint32_t     set{ 0 };
		uint32_t     binding{ 0 };
		std::string  name;
		uint32_t     count{ 0 };
		MemoryAccess memoryAccess{ MemoryAccessBit::READ_WRITE };
	};
	using UniformStorageBufferList = std::vector<UniformStorageBuffer>;
	struct ShaderStage {
		ShaderStageFlagBit stage{ ShaderStageFlagBit::NONE };
		std::string        source;
	};
	using ShaderStageList = std::vector<ShaderStage>;
	struct Attribute {
		std::string    name;
		VertexFormat   format{ VertexFormat::FLOAT };
		bool     isNormalized{ false };
		uint32_t stream{ 0 };
		bool     isInstanced{ false };
		uint32_t location{ 0 };
	};
	using AttributeList = std::vector<Attribute>;
	struct ShaderInfo {
		std::string                name;
		ShaderStageList            stages;
		AttributeList              attributes;
		UniformBlockList           blocks;
		UniformStorageBufferList   buffers;
		UniformSamplerTextureList  samplerTextures;
	};

	Program* newProgram(const ShaderInfo& info);

	void* getWindowHandle() const { return windowHandle; }
	uint32_t getWidth() const { return width; }
	uint32_t getHeight() const { return height; }
	bool getVsync() const { return vsync; }

protected:
	/**
	 * New a shaderModule, not auto released.
	 * @param stage Specifies whether is vertex shader or fragment shader.
	 * @param source Specifies shader source.
	 * @return A ShaderModule object.
	 */
	ShaderModule* newShaderModule(backend::ShaderStage stage, std::string_view source) override;

	static void initBuiltinShaderInfo();
};

CC_BACKEND_END
