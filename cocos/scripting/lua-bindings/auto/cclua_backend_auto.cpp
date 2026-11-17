#include "cclua_backend_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"

static_assert(lua::value_type<cc::backend::VertexLayout>::value, "ValueTypes requires a shared runtime trait for cc::backend::VertexLayout");
int luaReg_CoreBackend_ccbBufferUsage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BufferUsage");
	LUA_ENUM_ENTRY("STATIC", cc::backend::BufferUsage::STATIC);
	LUA_ENUM_ENTRY("DYNAMIC", cc::backend::BufferUsage::DYNAMIC);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBufferType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BufferType");
	LUA_ENUM_ENTRY("VERTEX", cc::backend::BufferType::VERTEX);
	LUA_ENUM_ENTRY("INDEX", cc::backend::BufferType::INDEX);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbShaderStage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("ShaderStage");
	LUA_ENUM_ENTRY("VERTEX", cc::backend::ShaderStage::VERTEX);
	LUA_ENUM_ENTRY("FRAGMENT", cc::backend::ShaderStage::FRAGMENT);
	LUA_ENUM_ENTRY("VERTEX_AND_FRAGMENT", cc::backend::ShaderStage::VERTEX_AND_FRAGMENT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbVertexFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("VertexFormat");
	LUA_ENUM_ENTRY("FLOAT4", cc::backend::VertexFormat::FLOAT4);
	LUA_ENUM_ENTRY("FLOAT3", cc::backend::VertexFormat::FLOAT3);
	LUA_ENUM_ENTRY("FLOAT2", cc::backend::VertexFormat::FLOAT2);
	LUA_ENUM_ENTRY("FLOAT", cc::backend::VertexFormat::FLOAT);
	LUA_ENUM_ENTRY("INT4", cc::backend::VertexFormat::INT4);
	LUA_ENUM_ENTRY("INT3", cc::backend::VertexFormat::INT3);
	LUA_ENUM_ENTRY("INT2", cc::backend::VertexFormat::INT2);
	LUA_ENUM_ENTRY("INT", cc::backend::VertexFormat::INT);
	LUA_ENUM_ENTRY("USHORT4", cc::backend::VertexFormat::USHORT4);
	LUA_ENUM_ENTRY("USHORT2", cc::backend::VertexFormat::USHORT2);
	LUA_ENUM_ENTRY("UBYTE4", cc::backend::VertexFormat::UBYTE4);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbPixelFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("PixelFormat");
	LUA_ENUM_ENTRY("PVRTC4", cc::backend::PixelFormat::PVRTC4);
	LUA_ENUM_ENTRY("PVRTC4A", cc::backend::PixelFormat::PVRTC4A);
	LUA_ENUM_ENTRY("PVRTC2", cc::backend::PixelFormat::PVRTC2);
	LUA_ENUM_ENTRY("PVRTC2A", cc::backend::PixelFormat::PVRTC2A);
	LUA_ENUM_ENTRY("ETC1", cc::backend::PixelFormat::ETC1);
	LUA_ENUM_ENTRY("ETC2_RGB", cc::backend::PixelFormat::ETC2_RGB);
	LUA_ENUM_ENTRY("ETC2_RGBA", cc::backend::PixelFormat::ETC2_RGBA);
	LUA_ENUM_ENTRY("S3TC_DXT1", cc::backend::PixelFormat::S3TC_DXT1);
	LUA_ENUM_ENTRY("S3TC_DXT3", cc::backend::PixelFormat::S3TC_DXT3);
	LUA_ENUM_ENTRY("S3TC_DXT5", cc::backend::PixelFormat::S3TC_DXT5);
	LUA_ENUM_ENTRY("ATC_RGB", cc::backend::PixelFormat::ATC_RGB);
	LUA_ENUM_ENTRY("ATC_EXPLICIT_ALPHA", cc::backend::PixelFormat::ATC_EXPLICIT_ALPHA);
	LUA_ENUM_ENTRY("ATC_INTERPOLATED_ALPHA", cc::backend::PixelFormat::ATC_INTERPOLATED_ALPHA);
	LUA_ENUM_ENTRY("ASTC4x4", cc::backend::PixelFormat::ASTC4x4);
	LUA_ENUM_ENTRY("ASTC5x5", cc::backend::PixelFormat::ASTC5x5);
	LUA_ENUM_ENTRY("ASTC6x6", cc::backend::PixelFormat::ASTC6x6);
	LUA_ENUM_ENTRY("ASTC8x5", cc::backend::PixelFormat::ASTC8x5);
	LUA_ENUM_ENTRY("ASTC8x6", cc::backend::PixelFormat::ASTC8x6);
	LUA_ENUM_ENTRY("ASTC8x8", cc::backend::PixelFormat::ASTC8x8);
	LUA_ENUM_ENTRY("ASTC10x5", cc::backend::PixelFormat::ASTC10x5);
	LUA_ENUM_ENTRY("RGBA8", cc::backend::PixelFormat::RGBA8888);
	LUA_ENUM_ENTRY("BGRA8", cc::backend::PixelFormat::BGRA8888);
	LUA_ENUM_ENTRY("RGB8", cc::backend::PixelFormat::RGB888);
	LUA_ENUM_ENTRY("RGB565", cc::backend::PixelFormat::RGB565);
	LUA_ENUM_ENTRY("RGBA4", cc::backend::PixelFormat::RGBA4444);
	LUA_ENUM_ENTRY("RGB5A1", cc::backend::PixelFormat::RGB5A1);
	LUA_ENUM_ENTRY("A8", cc::backend::PixelFormat::A8);
	LUA_ENUM_ENTRY("L8", cc::backend::PixelFormat::I8);
	LUA_ENUM_ENTRY("LA8", cc::backend::PixelFormat::AI88);
	LUA_ENUM_ENTRY("D24S8", cc::backend::PixelFormat::D24S8);
	LUA_ENUM_ENTRY("COUNT", cc::backend::PixelFormat::COUNT);
	LUA_ENUM_ENTRY("NONE", cc::backend::PixelFormat::NONE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureUsage(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureUsage");
	LUA_ENUM_ENTRY("READ", cc::backend::TextureUsage::READ);
	LUA_ENUM_ENTRY("WRITE", cc::backend::TextureUsage::WRITE);
	LUA_ENUM_ENTRY("RENDER_TARGET", cc::backend::TextureUsage::RENDER_TARGET);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbIndexFormat(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("IndexFormat");
	LUA_ENUM_ENTRY("U_SHORT", cc::backend::IndexFormat::U_SHORT);
	LUA_ENUM_ENTRY("U_INT", cc::backend::IndexFormat::U_INT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbVertexStepMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("VertexStepMode");
	LUA_ENUM_ENTRY("VERTEX", cc::backend::VertexStepMode::VERTEX);
	LUA_ENUM_ENTRY("INSTANCE", cc::backend::VertexStepMode::INSTANCE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbPrimitiveType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("PrimitiveType");
	LUA_ENUM_ENTRY("POINT", cc::backend::PrimitiveType::POINT);
	LUA_ENUM_ENTRY("LINE", cc::backend::PrimitiveType::LINE);
	LUA_ENUM_ENTRY("LINE_LOOP", cc::backend::PrimitiveType::LINE_LOOP);
	LUA_ENUM_ENTRY("LINE_STRIP", cc::backend::PrimitiveType::LINE_STRIP);
	LUA_ENUM_ENTRY("TRIANGLE", cc::backend::PrimitiveType::TRIANGLE);
	LUA_ENUM_ENTRY("TRIANGLE_STRIP", cc::backend::PrimitiveType::TRIANGLE_STRIP);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureType(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureType");
	LUA_ENUM_ENTRY("TEXTURE_2D", cc::backend::TextureType::TEXTURE_2D);
	LUA_ENUM_ENTRY("TEXTURE_CUBE", cc::backend::TextureType::TEXTURE_CUBE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbSamplerAddressMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("SamplerAddressMode");
	LUA_ENUM_ENTRY("REPEAT", cc::backend::SamplerAddressMode::REPEAT);
	LUA_ENUM_ENTRY("MIRROR_REPEAT", cc::backend::SamplerAddressMode::MIRROR_REPEAT);
	LUA_ENUM_ENTRY("CLAMP_TO_EDGE", cc::backend::SamplerAddressMode::CLAMP_TO_EDGE);
	LUA_ENUM_ENTRY("DONT_CARE", cc::backend::SamplerAddressMode::DONT_CARE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbSamplerFilter(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("SamplerFilter");
	LUA_ENUM_ENTRY("NEAREST", cc::backend::SamplerFilter::NEAREST);
	LUA_ENUM_ENTRY("NEAREST_MIPMAP_NEAREST", cc::backend::SamplerFilter::NEAREST_MIPMAP_NEAREST);
	LUA_ENUM_ENTRY("NEAREST_MIPMAP_LINEAR", cc::backend::SamplerFilter::NEAREST_MIPMAP_LINEAR);
	LUA_ENUM_ENTRY("LINEAR", cc::backend::SamplerFilter::LINEAR);
	LUA_ENUM_ENTRY("LINEAR_MIPMAP_LINEAR", cc::backend::SamplerFilter::LINEAR_MIPMAP_LINEAR);
	LUA_ENUM_ENTRY("LINEAR_MIPMAP_NEAREST", cc::backend::SamplerFilter::LINEAR_MIPMAP_NEAREST);
	LUA_ENUM_ENTRY("DONT_CARE", cc::backend::SamplerFilter::DONT_CARE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbStencilOperation(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("StencilOperation");
	LUA_ENUM_ENTRY("KEEP", cc::backend::StencilOperation::KEEP);
	LUA_ENUM_ENTRY("ZERO", cc::backend::StencilOperation::ZERO);
	LUA_ENUM_ENTRY("REPLACE", cc::backend::StencilOperation::REPLACE);
	LUA_ENUM_ENTRY("INVERT", cc::backend::StencilOperation::INVERT);
	LUA_ENUM_ENTRY("INCREMENT_WRAP", cc::backend::StencilOperation::INCREMENT_WRAP);
	LUA_ENUM_ENTRY("DECREMENT_WRAP", cc::backend::StencilOperation::DECREMENT_WRAP);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbCompareFunction(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("CompareFunction");
	LUA_ENUM_ENTRY("NEVER", cc::backend::CompareFunction::NEVER);
	LUA_ENUM_ENTRY("LESS", cc::backend::CompareFunction::LESS);
	LUA_ENUM_ENTRY("LESS_EQUAL", cc::backend::CompareFunction::LESS_EQUAL);
	LUA_ENUM_ENTRY("GREATER", cc::backend::CompareFunction::GREATER);
	LUA_ENUM_ENTRY("GREATER_EQUAL", cc::backend::CompareFunction::GREATER_EQUAL);
	LUA_ENUM_ENTRY("EQUAL", cc::backend::CompareFunction::EQUAL);
	LUA_ENUM_ENTRY("NOT_EQUAL", cc::backend::CompareFunction::NOT_EQUAL);
	LUA_ENUM_ENTRY("ALWAYS", cc::backend::CompareFunction::ALWAYS);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBlendOperation(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BlendOperation");
	LUA_ENUM_ENTRY("ADD", cc::backend::BlendOperation::ADD);
	LUA_ENUM_ENTRY("SUBTRACT", cc::backend::BlendOperation::SUBTRACT);
	LUA_ENUM_ENTRY("RESERVE_SUBTRACT", cc::backend::BlendOperation::RESERVE_SUBTRACT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbBlendFactor(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("BlendFactor");
	LUA_ENUM_ENTRY("ZERO", cc::backend::BlendFactor::ZERO);
	LUA_ENUM_ENTRY("ONE", cc::backend::BlendFactor::ONE);
	LUA_ENUM_ENTRY("SRC_COLOR", cc::backend::BlendFactor::SRC_COLOR);
	LUA_ENUM_ENTRY("ONE_MINUS_SRC_COLOR", cc::backend::BlendFactor::ONE_MINUS_SRC_COLOR);
	LUA_ENUM_ENTRY("SRC_ALPHA", cc::backend::BlendFactor::SRC_ALPHA);
	LUA_ENUM_ENTRY("ONE_MINUS_SRC_ALPHA", cc::backend::BlendFactor::ONE_MINUS_SRC_ALPHA);
	LUA_ENUM_ENTRY("DST_COLOR", cc::backend::BlendFactor::DST_COLOR);
	LUA_ENUM_ENTRY("ONE_MINUS_DST_COLOR", cc::backend::BlendFactor::ONE_MINUS_DST_COLOR);
	LUA_ENUM_ENTRY("DST_ALPHA", cc::backend::BlendFactor::DST_ALPHA);
	LUA_ENUM_ENTRY("ONE_MINUS_DST_ALPHA", cc::backend::BlendFactor::ONE_MINUS_DST_ALPHA);
	LUA_ENUM_ENTRY("CONSTANT_ALPHA", cc::backend::BlendFactor::CONSTANT_ALPHA);
	LUA_ENUM_ENTRY("SRC_ALPHA_SATURATE", cc::backend::BlendFactor::SRC_ALPHA_SATURATE);
	LUA_ENUM_ENTRY("ONE_MINUS_CONSTANT_ALPHA", cc::backend::BlendFactor::ONE_MINUS_CONSTANT_ALPHA);
	LUA_ENUM_ENTRY("BLEND_CLOLOR", cc::backend::BlendFactor::BLEND_CLOLOR);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbColorWriteMask(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("ColorWriteMask");
	LUA_ENUM_ENTRY("RED_BIT", cc::backend::ColorWriteMask::RED_BIT);
	LUA_ENUM_ENTRY("GREEN_BIT", cc::backend::ColorWriteMask::GREEN_BIT);
	LUA_ENUM_ENTRY("BLUE_BIT", cc::backend::ColorWriteMask::BLUE_BIT);
	LUA_ENUM_ENTRY("ALPHA_BIT", cc::backend::ColorWriteMask::ALPHA_BIT);
	LUA_ENUM_ENTRY("NONE", cc::backend::ColorWriteMask::NONE);
	LUA_ENUM_ENTRY("RED", cc::backend::ColorWriteMask::RED);
	LUA_ENUM_ENTRY("GREEN", cc::backend::ColorWriteMask::GREEN);
	LUA_ENUM_ENTRY("BLUE", cc::backend::ColorWriteMask::BLUE);
	LUA_ENUM_ENTRY("ALPHA", cc::backend::ColorWriteMask::ALPHA);
	LUA_ENUM_ENTRY("ALL", cc::backend::ColorWriteMask::ALL);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbCullMode(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("CullMode");
	LUA_ENUM_ENTRY("NONE", cc::backend::CullMode::NONE);
	LUA_ENUM_ENTRY("BACK", cc::backend::CullMode::BACK);
	LUA_ENUM_ENTRY("FRONT", cc::backend::CullMode::FRONT);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbWinding(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("Winding");
	LUA_ENUM_ENTRY("CLOCK_WISE", cc::backend::Winding::CLOCK_WISE);
	LUA_ENUM_ENTRY("COUNTER_CLOCK_WISE", cc::backend::Winding::COUNTER_CLOCK_WISE);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_CoreBackend_ccbTextureCubeFace(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_ENUM_DEF("TextureCubeFace");
	LUA_ENUM_ENTRY("POSITIVE_X", cc::backend::TextureCubeFace::POSITIVE_X);
	LUA_ENUM_ENTRY("NEGATIVE_X", cc::backend::TextureCubeFace::NEGATIVE_X);
	LUA_ENUM_ENTRY("POSITIVE_Y", cc::backend::TextureCubeFace::POSITIVE_Y);
	LUA_ENUM_ENTRY("NEGATIVE_Y", cc::backend::TextureCubeFace::NEGATIVE_Y);
	LUA_ENUM_ENTRY("POSITIVE_Z", cc::backend::TextureCubeFace::POSITIVE_Z);
	LUA_ENUM_ENTRY("NEGATIVE_Z", cc::backend::TextureCubeFace::NEGATIVE_Z);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_Program_getActiveAttributes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getActiveAttributes");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getActiveAttributes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_getAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cc::backend::Program::*)(std::string_view)const>(&cc::backend::Program::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getBuiltinAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cc::backend::Program::*)(cc::backend::Attribute)const>(&cc::backend::Program::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getBuiltinUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cc::backend::UniformLocation(cc::backend::Program::*)(cc::backend::Uniform)const>(&cc::backend::Program::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getFragmentShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getFragmentShader");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getFragmentShader);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_getMaxFragmentLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getMaxFragmentLocation");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getMaxFragmentLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_getMaxVertexLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getMaxVertexLocation");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getMaxVertexLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_getProgramType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getProgramType");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getProgramType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_getUniformBufferSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getUniformBufferSize");
	LUA_TRY_INVOKE_R(1, &cc::backend::Program::getUniformBufferSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cc::backend::UniformLocation(cc::backend::Program::*)(std::string_view)const>(&cc::backend::Program::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getVertexShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:getVertexShader");
	LUA_TRY_INVOKE_R(0, &cc::backend::Program::getVertexShader);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_Program_setProgramType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Program", "ccb.Program:setProgramType");
	LUA_TRY_INVOKE(1, &cc::backend::Program::setProgramType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_Program_getBuiltinProgram(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.Program", "ccb.Program:getBuiltinProgram");
	LUA_TRY_INVOKE_R(1, &cc::backend::Program::getBuiltinProgram);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbProgram(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::Program, "Program", "ccb.Program",
		cc::backend::Program, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActiveAttributes", lua_cc_backend_Program_getActiveAttributes);
	LUA_METHOD("getAttributeLocation", lua_cc_backend_Program_getAttributeLocation_1);
	LUA_METHOD("getBuiltinAttributeLocation", lua_cc_backend_Program_getBuiltinAttributeLocation_1);
	LUA_METHOD("getBuiltinUniformLocation", lua_cc_backend_Program_getBuiltinUniformLocation_1);
	LUA_METHOD("getFragmentShader", lua_cc_backend_Program_getFragmentShader);
	LUA_METHOD("getMaxFragmentLocation", lua_cc_backend_Program_getMaxFragmentLocation);
	LUA_METHOD("getMaxVertexLocation", lua_cc_backend_Program_getMaxVertexLocation);
	LUA_METHOD("getProgramType", lua_cc_backend_Program_getProgramType);
	LUA_METHOD("getUniformBufferSize", lua_cc_backend_Program_getUniformBufferSize);
	LUA_METHOD("getUniformLocation", lua_cc_backend_Program_getUniformLocation_1);
	LUA_METHOD("getVertexShader", lua_cc_backend_Program_getVertexShader);
	LUA_METHOD("setProgramType", lua_cc_backend_Program_setProgramType);
	LUA_METHOD("getBuiltinProgram", lua_cc_backend_Program_getBuiltinProgram);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_VertexLayout_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:new");
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cc::backend::VertexLayout());}});
	LUA_SINVOKE_FOOTER("0");
}
// Impl No Dtor
int lua_cc_backend_VertexLayout_getStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:getStride");
	LUA_TRY_INVOKE_R(0, &cc::backend::VertexLayout::getStride);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_VertexLayout_getVertexStepMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:getVertexStepMode");
	LUA_TRY_INVOKE_R(0, &cc::backend::VertexLayout::getVertexStepMode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_VertexLayout_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:isValid");
	LUA_TRY_INVOKE_R(0, &cc::backend::VertexLayout::isValid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_VertexLayout_setAttribute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:setAttribute");
	LUA_TRY_INVOKE(5, &cc::backend::VertexLayout::setAttribute);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_backend_VertexLayout_setStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.VertexLayout", "ccb.VertexLayout:setStride");
	LUA_TRY_INVOKE(1, &cc::backend::VertexLayout::setStride);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbVertexLayout(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::VertexLayout, "VertexLayout", "ccb.VertexLayout",
		cc::backend::VertexLayout, "",
		lua_cc_backend_VertexLayout_new, lua::value_collect<cc::backend::VertexLayout>);
	LUA_METHOD("new", lua_cc_backend_VertexLayout_new);
	LUA_METHOD("getStride", lua_cc_backend_VertexLayout_getStride);
	LUA_METHOD("getVertexStepMode", lua_cc_backend_VertexLayout_getVertexStepMode);
	LUA_METHOD("isValid", lua_cc_backend_VertexLayout_isValid);
	LUA_METHOD("setAttribute", lua_cc_backend_VertexLayout_setAttribute);
	LUA_METHOD("setStride", lua_cc_backend_VertexLayout_setStride);
	LUA_CLS_END();
	lua::register_value_metatable<cc::backend::VertexLayout>(lua_S, "ccb.VertexLayout");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_ProgramState_getAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cc::backend::ProgramState::*)(std::string_view)const>(&cc::backend::ProgramState::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_getBuiltinAttributeLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getBuiltinAttributeLocation");
	LUA_TRY_INVOKE_R(1, static_cast<int(cc::backend::ProgramState::*)(cc::backend::Attribute)const>(&cc::backend::ProgramState::getAttributeLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_getBuiltinUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getBuiltinUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cc::backend::UniformLocation(cc::backend::ProgramState::*)(cc::backend::Uniform)const>(&cc::backend::ProgramState::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_getProgram(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getProgram");
	LUA_TRY_INVOKE_R(0, &cc::backend::ProgramState::getProgram);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_ProgramState_getUniformID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getUniformID");
	LUA_TRY_INVOKE_R(0, &cc::backend::ProgramState::getUniformID);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_ProgramState_getUniformLocation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:getUniformLocation");
	LUA_TRY_INVOKE_R(1, static_cast<cc::backend::UniformLocation(cc::backend::ProgramState::*)(std::string_view)const>(&cc::backend::ProgramState::getUniformLocation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_setParameterAutoBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setParameterAutoBinding");
	LUA_TRY_INVOKE(2, &cc::backend::ProgramState::setParameterAutoBinding);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_backend_ProgramState_setTexture_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cc::backend::ProgramState::*)(cc::backend::TextureBackend*)>(&cc::backend::ProgramState::setTexture));
	LUA_TRY_INVOKE(3, (static_cast<void(cc::backend::ProgramState::*)(const cc::backend::UniformLocation&, int, cc::backend::TextureBackend*)>(&cc::backend::ProgramState::setTexture)));
	LUA_TRY_INVOKE(4, (static_cast<void(cc::backend::ProgramState::*)(const cc::backend::UniformLocation&, int, int, cc::backend::TextureBackend*)>(&cc::backend::ProgramState::setTexture)));
	LUA_INVOKE_FOOTER("1,3,4");
}
int lua_cc_backend_ProgramState_setVertexAttrib(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexAttrib");
	LUA_TRY_INVOKE(5, &cc::backend::ProgramState::setVertexAttrib);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_backend_ProgramState_setVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexLayout");
	LUA_TRY_INVOKE(1, &cc::backend::ProgramState::setVertexLayout);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_setVertexStride(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setVertexStride");
	LUA_TRY_INVOKE(1, &cc::backend::ProgramState::setVertexStride);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_backend_ProgramState_updateUniformID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:updateUniformID");
	LUA_TRY_INVOKE(1, &cc::backend::ProgramState::updateUniformID);
	LUA_TRY_INVOKE(0, [](cc::backend::ProgramState* obj){{return obj->updateUniformID();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_backend_ProgramState_validateSharedVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:validateSharedVertexLayout");
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, &cc::backend::ProgramState::validateSharedVertexLayout);
	}
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbProgramState(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::ProgramState, "ProgramState", "ccb.ProgramState",
		cc::backend::ProgramState, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getAttributeLocation", lua_cc_backend_ProgramState_getAttributeLocation_1);
	LUA_METHOD("getBuiltinAttributeLocation", lua_cc_backend_ProgramState_getBuiltinAttributeLocation_1);
	LUA_METHOD("getBuiltinUniformLocation", lua_cc_backend_ProgramState_getBuiltinUniformLocation_1);
	LUA_METHOD("getProgram", lua_cc_backend_ProgramState_getProgram);
	LUA_METHOD("getUniformID", lua_cc_backend_ProgramState_getUniformID);
	LUA_METHOD("getUniformLocation", lua_cc_backend_ProgramState_getUniformLocation_1);
	LUA_METHOD("setParameterAutoBinding", lua_cc_backend_ProgramState_setParameterAutoBinding);
	LUA_METHOD("setTexture", lua_cc_backend_ProgramState_setTexture_1);
	LUA_METHOD("setVertexAttrib", lua_cc_backend_ProgramState_setVertexAttrib);
	LUA_METHOD("setVertexLayout", lua_cc_backend_ProgramState_setVertexLayout);
	LUA_METHOD("setVertexStride", lua_cc_backend_ProgramState_setVertexStride);
	LUA_METHOD("updateUniformID", lua_cc_backend_ProgramState_updateUniformID);
	LUA_METHOD("validateSharedVertexLayout", lua_cc_backend_ProgramState_validateSharedVertexLayout);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_TextureBackend_generateMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:generateMipmaps");
	LUA_TRY_INVOKE(0, &cc::backend::TextureBackend::generateMipmaps);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getCount");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getHandler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getHandler");
	LUA_TRY_INVOKE_R(1, &cc::backend::TextureBackend::getHandler);
	LUA_TRY_INVOKE_R(0, [](const cc::backend::TextureBackend* obj){{return obj->getHandler();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_backend_TextureBackend_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getHeight");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getTextureFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureFormat");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getTextureFormat);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getTextureType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureType");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getTextureType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getTextureUsage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getTextureUsage");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getTextureUsage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:getWidth");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::getWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_hasMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:hasMipmaps");
	LUA_TRY_INVOKE_R(0, &cc::backend::TextureBackend::hasMipmaps);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_TextureBackend_updateSamplerDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.TextureBackend", "ccb.TextureBackend:updateSamplerDescriptor");
	LUA_TRY_INVOKE(1, &cc::backend::TextureBackend::updateSamplerDescriptor);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_CoreBackend_ccbTextureBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::TextureBackend, "TextureBackend", "ccb.TextureBackend",
		cc::backend::TextureBackend, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("generateMipmaps", lua_cc_backend_TextureBackend_generateMipmaps);
	LUA_METHOD("getCount", lua_cc_backend_TextureBackend_getCount);
	LUA_METHOD("getHandler", lua_cc_backend_TextureBackend_getHandler);
	LUA_METHOD("getHeight", lua_cc_backend_TextureBackend_getHeight);
	LUA_METHOD("getTextureFormat", lua_cc_backend_TextureBackend_getTextureFormat);
	LUA_METHOD("getTextureType", lua_cc_backend_TextureBackend_getTextureType);
	LUA_METHOD("getTextureUsage", lua_cc_backend_TextureBackend_getTextureUsage);
	LUA_METHOD("getWidth", lua_cc_backend_TextureBackend_getWidth);
	LUA_METHOD("hasMipmaps", lua_cc_backend_TextureBackend_hasMipmaps);
	LUA_METHOD("updateSamplerDescriptor", lua_cc_backend_TextureBackend_updateSamplerDescriptor);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_CoreBackend_ccbTexture2DBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::Texture2DBackend, "Texture2DBackend", "ccb.Texture2DBackend",
		cc::backend::Texture2DBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_CoreBackend_ccbTextureCubemapBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::TextureCubemapBackend, "TextureCubemapBackend", "ccb.TextureCubemapBackend",
		cc::backend::TextureCubemapBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_Device_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccb.Device", "ccb.Device:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::backend::Device::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_CoreBackend_ccbDevice(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cc::backend::Device, "Device", "ccb.Device",
		cc::backend::Device, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getInstance", lua_cc_backend_Device_getInstance);
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
