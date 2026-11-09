#include "cclua_backend_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"

static_assert(lua::value_type<cocos2d::backend::VertexLayout>::value, "ValueTypes requires a shared runtime trait for cocos2d::backend::VertexLayout");
int luaReg_CoreBackend_ccbBufferUsage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BufferUsage");
	LUA_ENUM_ENTRY("STATIC", cocos2d::backend::BufferUsage::STATIC);
	LUA_ENUM_ENTRY("DYNAMIC", cocos2d::backend::BufferUsage::DYNAMIC);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBufferType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BufferType");
	LUA_ENUM_ENTRY("VERTEX", cocos2d::backend::BufferType::VERTEX);
	LUA_ENUM_ENTRY("INDEX", cocos2d::backend::BufferType::INDEX);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbShaderStage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("ShaderStage");
	LUA_ENUM_ENTRY("VERTEX", cocos2d::backend::ShaderStage::VERTEX);
	LUA_ENUM_ENTRY("FRAGMENT", cocos2d::backend::ShaderStage::FRAGMENT);
	LUA_ENUM_ENTRY("VERTEX_AND_FRAGMENT", cocos2d::backend::ShaderStage::VERTEX_AND_FRAGMENT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbVertexFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("VertexFormat");
	LUA_ENUM_ENTRY("FLOAT4", cocos2d::backend::VertexFormat::FLOAT4);
	LUA_ENUM_ENTRY("FLOAT3", cocos2d::backend::VertexFormat::FLOAT3);
	LUA_ENUM_ENTRY("FLOAT2", cocos2d::backend::VertexFormat::FLOAT2);
	LUA_ENUM_ENTRY("FLOAT", cocos2d::backend::VertexFormat::FLOAT);
	LUA_ENUM_ENTRY("INT4", cocos2d::backend::VertexFormat::INT4);
	LUA_ENUM_ENTRY("INT3", cocos2d::backend::VertexFormat::INT3);
	LUA_ENUM_ENTRY("INT2", cocos2d::backend::VertexFormat::INT2);
	LUA_ENUM_ENTRY("INT", cocos2d::backend::VertexFormat::INT);
	LUA_ENUM_ENTRY("USHORT4", cocos2d::backend::VertexFormat::USHORT4);
	LUA_ENUM_ENTRY("USHORT2", cocos2d::backend::VertexFormat::USHORT2);
	LUA_ENUM_ENTRY("UBYTE4", cocos2d::backend::VertexFormat::UBYTE4);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbPixelFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("PixelFormat");
	LUA_ENUM_ENTRY("PVRTC4", cocos2d::backend::PixelFormat::PVRTC4);
	LUA_ENUM_ENTRY("PVRTC4A", cocos2d::backend::PixelFormat::PVRTC4A);
	LUA_ENUM_ENTRY("PVRTC2", cocos2d::backend::PixelFormat::PVRTC2);
	LUA_ENUM_ENTRY("PVRTC2A", cocos2d::backend::PixelFormat::PVRTC2A);
	LUA_ENUM_ENTRY("ETC1", cocos2d::backend::PixelFormat::ETC1);
	LUA_ENUM_ENTRY("ETC2_RGB", cocos2d::backend::PixelFormat::ETC2_RGB);
	LUA_ENUM_ENTRY("ETC2_RGBA", cocos2d::backend::PixelFormat::ETC2_RGBA);
	LUA_ENUM_ENTRY("S3TC_DXT1", cocos2d::backend::PixelFormat::S3TC_DXT1);
	LUA_ENUM_ENTRY("S3TC_DXT3", cocos2d::backend::PixelFormat::S3TC_DXT3);
	LUA_ENUM_ENTRY("S3TC_DXT5", cocos2d::backend::PixelFormat::S3TC_DXT5);
	LUA_ENUM_ENTRY("ATC_RGB", cocos2d::backend::PixelFormat::ATC_RGB);
	LUA_ENUM_ENTRY("ATC_EXPLICIT_ALPHA", cocos2d::backend::PixelFormat::ATC_EXPLICIT_ALPHA);
	LUA_ENUM_ENTRY("ATC_INTERPOLATED_ALPHA", cocos2d::backend::PixelFormat::ATC_INTERPOLATED_ALPHA);
	LUA_ENUM_ENTRY("ASTC4x4", cocos2d::backend::PixelFormat::ASTC4x4);
	LUA_ENUM_ENTRY("ASTC5x5", cocos2d::backend::PixelFormat::ASTC5x5);
	LUA_ENUM_ENTRY("ASTC6x6", cocos2d::backend::PixelFormat::ASTC6x6);
	LUA_ENUM_ENTRY("ASTC8x5", cocos2d::backend::PixelFormat::ASTC8x5);
	LUA_ENUM_ENTRY("ASTC8x6", cocos2d::backend::PixelFormat::ASTC8x6);
	LUA_ENUM_ENTRY("ASTC8x8", cocos2d::backend::PixelFormat::ASTC8x8);
	LUA_ENUM_ENTRY("ASTC10x5", cocos2d::backend::PixelFormat::ASTC10x5);
	LUA_ENUM_ENTRY("RGBA8", cocos2d::backend::PixelFormat::RGBA8888);
	LUA_ENUM_ENTRY("BGRA8", cocos2d::backend::PixelFormat::BGRA8888);
	LUA_ENUM_ENTRY("RGB8", cocos2d::backend::PixelFormat::RGB888);
	LUA_ENUM_ENTRY("RGB565", cocos2d::backend::PixelFormat::RGB565);
	LUA_ENUM_ENTRY("RGBA4", cocos2d::backend::PixelFormat::RGBA4444);
	LUA_ENUM_ENTRY("RGB5A1", cocos2d::backend::PixelFormat::RGB5A1);
	LUA_ENUM_ENTRY("A8", cocos2d::backend::PixelFormat::A8);
	LUA_ENUM_ENTRY("L8", cocos2d::backend::PixelFormat::I8);
	LUA_ENUM_ENTRY("LA8", cocos2d::backend::PixelFormat::AI88);
	LUA_ENUM_ENTRY("D24S8", cocos2d::backend::PixelFormat::D24S8);
	LUA_ENUM_ENTRY("COUNT", cocos2d::backend::PixelFormat::COUNT);
	LUA_ENUM_ENTRY("NONE", cocos2d::backend::PixelFormat::NONE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureUsage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureUsage");
	LUA_ENUM_ENTRY("READ", cocos2d::backend::TextureUsage::READ);
	LUA_ENUM_ENTRY("WRITE", cocos2d::backend::TextureUsage::WRITE);
	LUA_ENUM_ENTRY("RENDER_TARGET", cocos2d::backend::TextureUsage::RENDER_TARGET);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbIndexFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("IndexFormat");
	LUA_ENUM_ENTRY("U_SHORT", cocos2d::backend::IndexFormat::U_SHORT);
	LUA_ENUM_ENTRY("U_INT", cocos2d::backend::IndexFormat::U_INT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbVertexStepMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("VertexStepMode");
	LUA_ENUM_ENTRY("VERTEX", cocos2d::backend::VertexStepMode::VERTEX);
	LUA_ENUM_ENTRY("INSTANCE", cocos2d::backend::VertexStepMode::INSTANCE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbPrimitiveType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("PrimitiveType");
	LUA_ENUM_ENTRY("POINT", cocos2d::backend::PrimitiveType::POINT);
	LUA_ENUM_ENTRY("LINE", cocos2d::backend::PrimitiveType::LINE);
	LUA_ENUM_ENTRY("LINE_LOOP", cocos2d::backend::PrimitiveType::LINE_LOOP);
	LUA_ENUM_ENTRY("LINE_STRIP", cocos2d::backend::PrimitiveType::LINE_STRIP);
	LUA_ENUM_ENTRY("TRIANGLE", cocos2d::backend::PrimitiveType::TRIANGLE);
	LUA_ENUM_ENTRY("TRIANGLE_STRIP", cocos2d::backend::PrimitiveType::TRIANGLE_STRIP);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureType");
	LUA_ENUM_ENTRY("TEXTURE_2D", cocos2d::backend::TextureType::TEXTURE_2D);
	LUA_ENUM_ENTRY("TEXTURE_CUBE", cocos2d::backend::TextureType::TEXTURE_CUBE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbSamplerAddressMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("SamplerAddressMode");
	LUA_ENUM_ENTRY("REPEAT", cocos2d::backend::SamplerAddressMode::REPEAT);
	LUA_ENUM_ENTRY("MIRROR_REPEAT", cocos2d::backend::SamplerAddressMode::MIRROR_REPEAT);
	LUA_ENUM_ENTRY("CLAMP_TO_EDGE", cocos2d::backend::SamplerAddressMode::CLAMP_TO_EDGE);
	LUA_ENUM_ENTRY("DONT_CARE", cocos2d::backend::SamplerAddressMode::DONT_CARE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbSamplerFilter(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("SamplerFilter");
	LUA_ENUM_ENTRY("NEAREST", cocos2d::backend::SamplerFilter::NEAREST);
	LUA_ENUM_ENTRY("NEAREST_MIPMAP_NEAREST", cocos2d::backend::SamplerFilter::NEAREST_MIPMAP_NEAREST);
	LUA_ENUM_ENTRY("NEAREST_MIPMAP_LINEAR", cocos2d::backend::SamplerFilter::NEAREST_MIPMAP_LINEAR);
	LUA_ENUM_ENTRY("LINEAR", cocos2d::backend::SamplerFilter::LINEAR);
	LUA_ENUM_ENTRY("LINEAR_MIPMAP_LINEAR", cocos2d::backend::SamplerFilter::LINEAR_MIPMAP_LINEAR);
	LUA_ENUM_ENTRY("LINEAR_MIPMAP_NEAREST", cocos2d::backend::SamplerFilter::LINEAR_MIPMAP_NEAREST);
	LUA_ENUM_ENTRY("DONT_CARE", cocos2d::backend::SamplerFilter::DONT_CARE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbStencilOperation(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("StencilOperation");
	LUA_ENUM_ENTRY("KEEP", cocos2d::backend::StencilOperation::KEEP);
	LUA_ENUM_ENTRY("ZERO", cocos2d::backend::StencilOperation::ZERO);
	LUA_ENUM_ENTRY("REPLACE", cocos2d::backend::StencilOperation::REPLACE);
	LUA_ENUM_ENTRY("INVERT", cocos2d::backend::StencilOperation::INVERT);
	LUA_ENUM_ENTRY("INCREMENT_WRAP", cocos2d::backend::StencilOperation::INCREMENT_WRAP);
	LUA_ENUM_ENTRY("DECREMENT_WRAP", cocos2d::backend::StencilOperation::DECREMENT_WRAP);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbCompareFunction(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("CompareFunction");
	LUA_ENUM_ENTRY("NEVER", cocos2d::backend::CompareFunction::NEVER);
	LUA_ENUM_ENTRY("LESS", cocos2d::backend::CompareFunction::LESS);
	LUA_ENUM_ENTRY("LESS_EQUAL", cocos2d::backend::CompareFunction::LESS_EQUAL);
	LUA_ENUM_ENTRY("GREATER", cocos2d::backend::CompareFunction::GREATER);
	LUA_ENUM_ENTRY("GREATER_EQUAL", cocos2d::backend::CompareFunction::GREATER_EQUAL);
	LUA_ENUM_ENTRY("EQUAL", cocos2d::backend::CompareFunction::EQUAL);
	LUA_ENUM_ENTRY("NOT_EQUAL", cocos2d::backend::CompareFunction::NOT_EQUAL);
	LUA_ENUM_ENTRY("ALWAYS", cocos2d::backend::CompareFunction::ALWAYS);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBlendOperation(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BlendOperation");
	LUA_ENUM_ENTRY("ADD", cocos2d::backend::BlendOperation::ADD);
	LUA_ENUM_ENTRY("SUBTRACT", cocos2d::backend::BlendOperation::SUBTRACT);
	LUA_ENUM_ENTRY("RESERVE_SUBTRACT", cocos2d::backend::BlendOperation::RESERVE_SUBTRACT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBlendFactor(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BlendFactor");
	LUA_ENUM_ENTRY("ZERO", cocos2d::backend::BlendFactor::ZERO);
	LUA_ENUM_ENTRY("ONE", cocos2d::backend::BlendFactor::ONE);
	LUA_ENUM_ENTRY("SRC_COLOR", cocos2d::backend::BlendFactor::SRC_COLOR);
	LUA_ENUM_ENTRY("ONE_MINUS_SRC_COLOR", cocos2d::backend::BlendFactor::ONE_MINUS_SRC_COLOR);
	LUA_ENUM_ENTRY("SRC_ALPHA", cocos2d::backend::BlendFactor::SRC_ALPHA);
	LUA_ENUM_ENTRY("ONE_MINUS_SRC_ALPHA", cocos2d::backend::BlendFactor::ONE_MINUS_SRC_ALPHA);
	LUA_ENUM_ENTRY("DST_COLOR", cocos2d::backend::BlendFactor::DST_COLOR);
	LUA_ENUM_ENTRY("ONE_MINUS_DST_COLOR", cocos2d::backend::BlendFactor::ONE_MINUS_DST_COLOR);
	LUA_ENUM_ENTRY("DST_ALPHA", cocos2d::backend::BlendFactor::DST_ALPHA);
	LUA_ENUM_ENTRY("ONE_MINUS_DST_ALPHA", cocos2d::backend::BlendFactor::ONE_MINUS_DST_ALPHA);
	LUA_ENUM_ENTRY("CONSTANT_ALPHA", cocos2d::backend::BlendFactor::CONSTANT_ALPHA);
	LUA_ENUM_ENTRY("SRC_ALPHA_SATURATE", cocos2d::backend::BlendFactor::SRC_ALPHA_SATURATE);
	LUA_ENUM_ENTRY("ONE_MINUS_CONSTANT_ALPHA", cocos2d::backend::BlendFactor::ONE_MINUS_CONSTANT_ALPHA);
	LUA_ENUM_ENTRY("BLEND_CLOLOR", cocos2d::backend::BlendFactor::BLEND_CLOLOR);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbColorWriteMask(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("ColorWriteMask");
	LUA_ENUM_ENTRY("RED_BIT", cocos2d::backend::ColorWriteMask::RED_BIT);
	LUA_ENUM_ENTRY("GREEN_BIT", cocos2d::backend::ColorWriteMask::GREEN_BIT);
	LUA_ENUM_ENTRY("BLUE_BIT", cocos2d::backend::ColorWriteMask::BLUE_BIT);
	LUA_ENUM_ENTRY("ALPHA_BIT", cocos2d::backend::ColorWriteMask::ALPHA_BIT);
	LUA_ENUM_ENTRY("NONE", cocos2d::backend::ColorWriteMask::NONE);
	LUA_ENUM_ENTRY("RED", cocos2d::backend::ColorWriteMask::RED);
	LUA_ENUM_ENTRY("GREEN", cocos2d::backend::ColorWriteMask::GREEN);
	LUA_ENUM_ENTRY("BLUE", cocos2d::backend::ColorWriteMask::BLUE);
	LUA_ENUM_ENTRY("ALPHA", cocos2d::backend::ColorWriteMask::ALPHA);
	LUA_ENUM_ENTRY("ALL", cocos2d::backend::ColorWriteMask::ALL);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbCullMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("CullMode");
	LUA_ENUM_ENTRY("NONE", cocos2d::backend::CullMode::NONE);
	LUA_ENUM_ENTRY("BACK", cocos2d::backend::CullMode::BACK);
	LUA_ENUM_ENTRY("FRONT", cocos2d::backend::CullMode::FRONT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbWinding(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("Winding");
	LUA_ENUM_ENTRY("CLOCK_WISE", cocos2d::backend::Winding::CLOCK_WISE);
	LUA_ENUM_ENTRY("COUNTER_CLOCK_WISE", cocos2d::backend::Winding::COUNTER_CLOCK_WISE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureCubeFace(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureCubeFace");
	LUA_ENUM_ENTRY("POSITIVE_X", cocos2d::backend::TextureCubeFace::POSITIVE_X);
	LUA_ENUM_ENTRY("NEGATIVE_X", cocos2d::backend::TextureCubeFace::NEGATIVE_X);
	LUA_ENUM_ENTRY("POSITIVE_Y", cocos2d::backend::TextureCubeFace::POSITIVE_Y);
	LUA_ENUM_ENTRY("NEGATIVE_Y", cocos2d::backend::TextureCubeFace::NEGATIVE_Y);
	LUA_ENUM_ENTRY("POSITIVE_Z", cocos2d::backend::TextureCubeFace::POSITIVE_Z);
	LUA_ENUM_ENTRY("NEGATIVE_Z", cocos2d::backend::TextureCubeFace::NEGATIVE_Z);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_Program_getActiveAttributes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getActiveAttributes");
	LUA_TRY_INVOKE_R(0, (static_cast<const std::unordered_map<std::string, cocos2d::backend::AttributeBindInfo>&(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getActiveAttributes)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_getAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::backend::Program::*)(std::string_view)const>(&cocos2d::backend::Program::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getBuiltinAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::backend::Program::*)(cocos2d::backend::Attribute)const>(&cocos2d::backend::Program::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getBuiltinUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::UniformLocation(cocos2d::backend::Program::*)(cocos2d::backend::Uniform)const>(&cocos2d::backend::Program::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getFragmentShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getFragmentShader");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getFragmentShader));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_getMaxFragmentLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getMaxFragmentLocation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getMaxFragmentLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_getMaxVertexLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getMaxVertexLocation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getMaxVertexLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_getProgramType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getProgramType");
	LUA_TRY_INVOKE_R(0, static_cast<uint32_t(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getProgramType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_getUniformBufferSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getUniformBufferSize");
	LUA_TRY_INVOKE_R(1, static_cast<std::size_t(cocos2d::backend::Program::*)(cocos2d::backend::ShaderStage)const>(&cocos2d::backend::Program::getUniformBufferSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::UniformLocation(cocos2d::backend::Program::*)(std::string_view)const>(&cocos2d::backend::Program::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getVertexShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getVertexShader");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::backend::Program::*)()const>(&cocos2d::backend::Program::getVertexShader));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_Program_setProgramType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:setProgramType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::Program::*)(uint32_t)>(&cocos2d::backend::Program::setProgramType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_Program_getBuiltinProgram(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinProgram");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::Program*(*)(uint32_t)>(&cocos2d::backend::Program::getBuiltinProgram));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbProgram(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::Program, "Program", "ccb.Program",
		cocos2d::backend::Program, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActiveAttributes", lua_cocos2d_backend_Program_getActiveAttributes);
	LUA_METHOD("getAttributeLocation", lua_cocos2d_backend_Program_getAttributeLocation_1);
	LUA_METHOD("getBuiltinAttributeLocation", lua_cocos2d_backend_Program_getBuiltinAttributeLocation_1);
	LUA_METHOD("getBuiltinUniformLocation", lua_cocos2d_backend_Program_getBuiltinUniformLocation_1);
	LUA_METHOD("getFragmentShader", lua_cocos2d_backend_Program_getFragmentShader);
	LUA_METHOD("getMaxFragmentLocation", lua_cocos2d_backend_Program_getMaxFragmentLocation);
	LUA_METHOD("getMaxVertexLocation", lua_cocos2d_backend_Program_getMaxVertexLocation);
	LUA_METHOD("getProgramType", lua_cocos2d_backend_Program_getProgramType);
	LUA_METHOD("getUniformBufferSize", lua_cocos2d_backend_Program_getUniformBufferSize);
	LUA_METHOD("getUniformLocation", lua_cocos2d_backend_Program_getUniformLocation_1);
	LUA_METHOD("getVertexShader", lua_cocos2d_backend_Program_getVertexShader);
	LUA_METHOD("setProgramType", lua_cocos2d_backend_Program_setProgramType);
	LUA_METHOD("getBuiltinProgram", lua_cocos2d_backend_Program_getBuiltinProgram);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_VertexLayout_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:new");
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cocos2d::backend::VertexLayout());}});
	LUA_SINVOKE_FOOTER("0");
}
// Impl No Dtor
int lua_cocos2d_backend_VertexLayout_getStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:getStride");
	LUA_TRY_INVOKE_R(0, static_cast<std::size_t(cocos2d::backend::VertexLayout::*)()const>(&cocos2d::backend::VertexLayout::getStride));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_VertexLayout_getVertexStepMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:getVertexStepMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::VertexStepMode(cocos2d::backend::VertexLayout::*)()const>(&cocos2d::backend::VertexLayout::getVertexStepMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_VertexLayout_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:isValid");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::backend::VertexLayout::*)()const>(&cocos2d::backend::VertexLayout::isValid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_VertexLayout_setAttribute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:setAttribute");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::backend::VertexLayout::*)(std::string_view, std::size_t, cocos2d::backend::VertexFormat, std::size_t, bool)>(&cocos2d::backend::VertexLayout::setAttribute)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_backend_VertexLayout_setStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:setStride");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::VertexLayout::*)(std::size_t)>(&cocos2d::backend::VertexLayout::setStride));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbVertexLayout(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::VertexLayout, "VertexLayout", "ccb.VertexLayout",
		cocos2d::backend::VertexLayout, "",
		lua_cocos2d_backend_VertexLayout_new, lua::value_collect<cocos2d::backend::VertexLayout>);
	LUA_METHOD("new", lua_cocos2d_backend_VertexLayout_new);
	LUA_METHOD("getStride", lua_cocos2d_backend_VertexLayout_getStride);
	LUA_METHOD("getVertexStepMode", lua_cocos2d_backend_VertexLayout_getVertexStepMode);
	LUA_METHOD("isValid", lua_cocos2d_backend_VertexLayout_isValid);
	LUA_METHOD("setAttribute", lua_cocos2d_backend_VertexLayout_setAttribute);
	LUA_METHOD("setStride", lua_cocos2d_backend_VertexLayout_setStride);
	LUA_CLS_END();
	lua::register_value_metatable<cocos2d::backend::VertexLayout>(lua_S, "ccb.VertexLayout");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_ProgramState_getAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::backend::ProgramState::*)(std::string_view)const>(&cocos2d::backend::ProgramState::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_getBuiltinAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getBuiltinAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::backend::ProgramState::*)(cocos2d::backend::Attribute)const>(&cocos2d::backend::ProgramState::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_getBuiltinUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getBuiltinUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::UniformLocation(cocos2d::backend::ProgramState::*)(cocos2d::backend::Uniform)const>(&cocos2d::backend::ProgramState::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_getProgram(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getProgram");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::Program*(cocos2d::backend::ProgramState::*)()const>(&cocos2d::backend::ProgramState::getProgram));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_ProgramState_getUniformID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getUniformID");
	LUA_TRY_INVOKE_R(0, static_cast<uint32_t(cocos2d::backend::ProgramState::*)()>(&cocos2d::backend::ProgramState::getUniformID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_ProgramState_getUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::UniformLocation(cocos2d::backend::ProgramState::*)(std::string_view)const>(&cocos2d::backend::ProgramState::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_setParameterAutoBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setParameterAutoBinding");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::backend::ProgramState::*)(std::string_view, std::string_view)>(&cocos2d::backend::ProgramState::setParameterAutoBinding)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_backend_ProgramState_setTexture_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::ProgramState::*)(cocos2d::backend::TextureBackend*)>(&cocos2d::backend::ProgramState::setTexture));
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::backend::ProgramState::*)(const cocos2d::backend::UniformLocation&, int, cocos2d::backend::TextureBackend*)>(&cocos2d::backend::ProgramState::setTexture)));
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::backend::ProgramState::*)(const cocos2d::backend::UniformLocation&, int, int, cocos2d::backend::TextureBackend*)>(&cocos2d::backend::ProgramState::setTexture)));
	LUA_INVOKE_FOOTER("1,3,4");
}
int lua_cocos2d_backend_ProgramState_setVertexAttrib(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexAttrib");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::backend::ProgramState::*)(std::string_view, std::size_t, cocos2d::backend::VertexFormat, std::size_t, bool)>(&cocos2d::backend::ProgramState::setVertexAttrib)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_backend_ProgramState_setVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexLayout");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::ProgramState::*)(const cocos2d::backend::VertexLayout&)>(&cocos2d::backend::ProgramState::setVertexLayout));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_setVertexStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexStride");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::ProgramState::*)(uint32_t)>(&cocos2d::backend::ProgramState::setVertexStride));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ProgramState_updateUniformID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:updateUniformID");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::ProgramState::*)(int)>(&cocos2d::backend::ProgramState::updateUniformID));
	LUA_TRY_INVOKE(0, [](cocos2d::backend::ProgramState* obj){{return obj->updateUniformID();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_backend_ProgramState_validateSharedVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:validateSharedVertexLayout");
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::ProgramState::*)(std::function<void(cocos2d::backend::Program*)>)>(&cocos2d::backend::ProgramState::validateSharedVertexLayout));
	}
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbProgramState(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::ProgramState, "ProgramState", "ccb.ProgramState",
		cocos2d::backend::ProgramState, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getAttributeLocation", lua_cocos2d_backend_ProgramState_getAttributeLocation_1);
	LUA_METHOD("getBuiltinAttributeLocation", lua_cocos2d_backend_ProgramState_getBuiltinAttributeLocation_1);
	LUA_METHOD("getBuiltinUniformLocation", lua_cocos2d_backend_ProgramState_getBuiltinUniformLocation_1);
	LUA_METHOD("getProgram", lua_cocos2d_backend_ProgramState_getProgram);
	LUA_METHOD("getUniformID", lua_cocos2d_backend_ProgramState_getUniformID);
	LUA_METHOD("getUniformLocation", lua_cocos2d_backend_ProgramState_getUniformLocation_1);
	LUA_METHOD("setParameterAutoBinding", lua_cocos2d_backend_ProgramState_setParameterAutoBinding);
	LUA_METHOD("setTexture", lua_cocos2d_backend_ProgramState_setTexture_1);
	LUA_METHOD("setVertexAttrib", lua_cocos2d_backend_ProgramState_setVertexAttrib);
	LUA_METHOD("setVertexLayout", lua_cocos2d_backend_ProgramState_setVertexLayout);
	LUA_METHOD("setVertexStride", lua_cocos2d_backend_ProgramState_setVertexStride);
	LUA_METHOD("updateUniformID", lua_cocos2d_backend_ProgramState_updateUniformID);
	LUA_METHOD("validateSharedVertexLayout", lua_cocos2d_backend_ProgramState_validateSharedVertexLayout);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_TextureBackend_generateMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:generateMipmaps");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::backend::TextureBackend::*)()>(&cocos2d::backend::TextureBackend::generateMipmaps));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getHandler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getHandler");
	LUA_TRY_INVOKE_R(1, static_cast<uintptr_t(cocos2d::backend::TextureBackend::*)(int)const>(&cocos2d::backend::TextureBackend::getHandler));
	LUA_TRY_INVOKE_R(0, [](const cocos2d::backend::TextureBackend* obj){{return obj->getHandler();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_backend_TextureBackend_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getHeight");
	LUA_TRY_INVOKE_R(0, static_cast<uint32_t(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getTextureFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureFormat");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::PixelFormat(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getTextureFormat));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getTextureType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::TextureType(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getTextureType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getTextureUsage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureUsage");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::TextureUsage(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getTextureUsage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getWidth");
	LUA_TRY_INVOKE_R(0, static_cast<uint32_t(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::getWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_hasMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:hasMipmaps");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::backend::TextureBackend::*)()const>(&cocos2d::backend::TextureBackend::hasMipmaps));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_TextureBackend_updateSamplerDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:updateSamplerDescriptor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::backend::TextureBackend::*)(const cocos2d::backend::SamplerDescriptor&)>(&cocos2d::backend::TextureBackend::updateSamplerDescriptor));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbTextureBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::TextureBackend, "TextureBackend", "ccb.TextureBackend",
		cocos2d::backend::TextureBackend, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("generateMipmaps", lua_cocos2d_backend_TextureBackend_generateMipmaps);
	LUA_METHOD("getCount", lua_cocos2d_backend_TextureBackend_getCount);
	LUA_METHOD("getHandler", lua_cocos2d_backend_TextureBackend_getHandler);
	LUA_METHOD("getHeight", lua_cocos2d_backend_TextureBackend_getHeight);
	LUA_METHOD("getTextureFormat", lua_cocos2d_backend_TextureBackend_getTextureFormat);
	LUA_METHOD("getTextureType", lua_cocos2d_backend_TextureBackend_getTextureType);
	LUA_METHOD("getTextureUsage", lua_cocos2d_backend_TextureBackend_getTextureUsage);
	LUA_METHOD("getWidth", lua_cocos2d_backend_TextureBackend_getWidth);
	LUA_METHOD("hasMipmaps", lua_cocos2d_backend_TextureBackend_hasMipmaps);
	LUA_METHOD("updateSamplerDescriptor", lua_cocos2d_backend_TextureBackend_updateSamplerDescriptor);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_CoreBackend_ccbTexture2DBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::Texture2DBackend, "Texture2DBackend", "ccb.Texture2DBackend",
		cocos2d::backend::Texture2DBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_CoreBackend_ccbTextureCubemapBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::TextureCubemapBackend, "TextureCubemapBackend", "ccb.TextureCubemapBackend",
		cocos2d::backend::TextureCubemapBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_Device_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.Device", "ccb.Device:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::Device*(*)()>(&cocos2d::backend::Device::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_CoreBackend_ccbDevice(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::Device, "Device", "ccb.Device",
		cocos2d::backend::Device, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getInstance", lua_cocos2d_backend_Device_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int register_all_cc_backend_manual(lua_State* lua_S);

int register_all_cc_backend(lua_State* lua_S)
{
	tolua_open(lua_S);
	luaReg_CoreBackend_ccbBufferUsage(lua_S);
	luaReg_CoreBackend_ccbBufferType(lua_S);
	luaReg_CoreBackend_ccbShaderStage(lua_S);
	luaReg_CoreBackend_ccbVertexFormat(lua_S);
	luaReg_CoreBackend_ccbPixelFormat(lua_S);
	luaReg_CoreBackend_ccbTextureUsage(lua_S);
	luaReg_CoreBackend_ccbIndexFormat(lua_S);
	luaReg_CoreBackend_ccbVertexStepMode(lua_S);
	luaReg_CoreBackend_ccbPrimitiveType(lua_S);
	luaReg_CoreBackend_ccbTextureType(lua_S);
	luaReg_CoreBackend_ccbSamplerAddressMode(lua_S);
	luaReg_CoreBackend_ccbSamplerFilter(lua_S);
	luaReg_CoreBackend_ccbStencilOperation(lua_S);
	luaReg_CoreBackend_ccbCompareFunction(lua_S);
	luaReg_CoreBackend_ccbBlendOperation(lua_S);
	luaReg_CoreBackend_ccbBlendFactor(lua_S);
	luaReg_CoreBackend_ccbColorWriteMask(lua_S);
	luaReg_CoreBackend_ccbCullMode(lua_S);
	luaReg_CoreBackend_ccbWinding(lua_S);
	luaReg_CoreBackend_ccbTextureCubeFace(lua_S);
	luaReg_CoreBackend_ccbProgram(lua_S);
	luaReg_CoreBackend_ccbVertexLayout(lua_S);
	luaReg_CoreBackend_ccbProgramState(lua_S);
	luaReg_CoreBackend_ccbTextureBackend(lua_S);
	luaReg_CoreBackend_ccbTexture2DBackend(lua_S);
	luaReg_CoreBackend_ccbTextureCubemapBackend(lua_S);
	luaReg_CoreBackend_ccbDevice(lua_S);
	return register_all_cc_backend_manual(lua_S);
}
