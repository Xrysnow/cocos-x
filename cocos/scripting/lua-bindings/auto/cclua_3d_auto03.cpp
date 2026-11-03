#include "cclua_3d_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_3d_compat.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"

int lua_cocos2d_Bundle3D_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:clear");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Bundle3D::*)()>(&cocos2d::Bundle3D::clear));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Bundle3D_load(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:load");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Bundle3D::*)(std::string_view)>(&cocos2d::Bundle3D::load));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Bundle3D_destroyBundle(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:destroyBundle");
	LUA_TRY_INVOKE(1, static_cast<void(*)(cocos2d::Bundle3D*)>(&cocos2d::Bundle3D::destroyBundle));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Bundle3D_parseGLDataType(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseGLDataType");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::backend::VertexFormat(*)(std::string_view, int)>(&cocos2d::Bundle3D::parseGLDataType));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Bundle3D_parseSamplerAddressMode(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseSamplerAddressMode");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::SamplerAddressMode(*)(std::string_view)>(&cocos2d::Bundle3D::parseSamplerAddressMode));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccBundle3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::Bundle3D, "Bundle3D", "cc.Bundle3D",
		nullptr, nullptr);
	LUA_METHOD("clear", lua_cocos2d_Bundle3D_clear);
	LUA_METHOD("load", lua_cocos2d_Bundle3D_load);
	LUA_METHOD("destroyBundle", lua_cocos2d_Bundle3D_destroyBundle);
	LUA_METHOD("parseGLDataType", lua_cocos2d_Bundle3D_parseGLDataType);
	LUA_METHOD("parseSamplerAddressMode", lua_cocos2d_Bundle3D_parseSamplerAddressMode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
