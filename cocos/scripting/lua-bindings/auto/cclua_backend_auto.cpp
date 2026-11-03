#include "cclua_backend_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_backend_compat.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"

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
		cocos2d::Ref, "ccb.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("getFragmentShader", lua_cocos2d_backend_Program_getFragmentShader);
	LUA_METHOD("getMaxFragmentLocation", lua_cocos2d_backend_Program_getMaxFragmentLocation);
	LUA_METHOD("getMaxVertexLocation", lua_cocos2d_backend_Program_getMaxVertexLocation);
	LUA_METHOD("getProgramType", lua_cocos2d_backend_Program_getProgramType);
	LUA_METHOD("getUniformBufferSize", lua_cocos2d_backend_Program_getUniformBufferSize);
	LUA_METHOD("getVertexShader", lua_cocos2d_backend_Program_getVertexShader);
	LUA_METHOD("setProgramType", lua_cocos2d_backend_Program_setProgramType);
	LUA_METHOD("getBuiltinProgram", lua_cocos2d_backend_Program_getBuiltinProgram);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int luaReg_CoreBackend_ccbVertexLayout(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF(cocos2d::backend::VertexLayout, "VertexLayout", "ccb.VertexLayout",
		nullptr, nullptr);
	LUA_METHOD("getStride", lua_cocos2d_backend_VertexLayout_getStride);
	LUA_METHOD("getVertexStepMode", lua_cocos2d_backend_VertexLayout_getVertexStepMode);
	LUA_METHOD("isValid", lua_cocos2d_backend_VertexLayout_isValid);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_ProgramState_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::ProgramState*(cocos2d::backend::ProgramState::*)()const>(&cocos2d::backend::ProgramState::clone));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_backend_ProgramState_setParameterAutoBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.ProgramState", "ccb.ProgramState:setParameterAutoBinding");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::backend::ProgramState::*)(std::string_view, std::string_view)>(&cocos2d::backend::ProgramState::setParameterAutoBinding));
	LUA_INVOKE_FOOTER("2");
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
int luaReg_CoreBackend_ccbProgramState(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::ProgramState, "ProgramState", "ccb.ProgramState",
		cocos2d::Ref, "ccb.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_backend_ProgramState_clone);
	LUA_METHOD("getProgram", lua_cocos2d_backend_ProgramState_getProgram);
	LUA_METHOD("getUniformID", lua_cocos2d_backend_ProgramState_getUniformID);
	LUA_METHOD("setParameterAutoBinding", lua_cocos2d_backend_ProgramState_setParameterAutoBinding);
	LUA_METHOD("setVertexStride", lua_cocos2d_backend_ProgramState_setVertexStride);
	LUA_METHOD("updateUniformID", lua_cocos2d_backend_ProgramState_updateUniformID);
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
int luaReg_CoreBackend_ccbTextureBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::TextureBackend, "TextureBackend", "ccb.TextureBackend",
		cocos2d::Ref, "ccb.cocos2d.Ref",
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
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_CoreBackend_ccbTexture2DBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::Texture2DBackend, "Texture2DBackend", "ccb.Texture2DBackend",
		cocos2d::backend::TextureBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
extern int luaReg_CoreBackend_ccbProgram(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbVertexLayout(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbProgramState(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbTextureBackend(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbTexture2DBackend(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbTextureCubemapBackend(lua_State* lua_S);
extern int luaReg_CoreBackend_ccbDevice(lua_State* lua_S);

int register_all_cc_backend(lua_State* lua_S)
{
	luaReg_CoreBackend_ccbProgram(lua_S);
	luaReg_CoreBackend_ccbVertexLayout(lua_S);
	luaReg_CoreBackend_ccbProgramState(lua_S);
	luaReg_CoreBackend_ccbTextureBackend(lua_S);
	luaReg_CoreBackend_ccbTexture2DBackend(lua_S);
	luaReg_CoreBackend_ccbTextureCubemapBackend(lua_S);
	luaReg_CoreBackend_ccbDevice(lua_S);
	return register_all_cc_backend_retained(lua_S);
}
