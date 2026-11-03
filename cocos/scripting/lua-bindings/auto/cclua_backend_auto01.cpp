#include "cclua_backend_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_backend_compat.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_CoreBackend_ccbTextureCubemapBackend(lua_State* lua_S)
{
	LUA_ENTRY("ccb");
	LUA_CLS_DEF_BASE(cocos2d::backend::TextureCubemapBackend, "TextureCubemapBackend", "ccb.TextureCubemapBackend",
		cocos2d::backend::TextureBackend, "ccb.TextureBackend",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_Device_newProgram(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccb.Device", "ccb.Device:newProgram");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::backend::Program*(cocos2d::backend::Device::*)(std::string_view, std::string_view)>(&cocos2d::backend::Device::newProgram));
	LUA_INVOKE_FOOTER("2");
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
		cocos2d::Ref, "ccb.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("newProgram", lua_cocos2d_backend_Device_newProgram);
	LUA_METHOD("getInstance", lua_cocos2d_backend_Device_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
