#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#endif

int lua_cocos2d_MotionStreak3D_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cocos2d::MotionStreak3D::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getStroke");
	LUA_TRY_INVOKE_R(0, &cocos2d::MotionStreak3D::getStroke);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getSweepAxis");
	LUA_TRY_INVOKE_R(0, &cocos2d::MotionStreak3D::getSweepAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getTexture");
	LUA_TRY_INVOKE_R(0, &cocos2d::MotionStreak3D::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_MotionStreak3D_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, &cocos2d::MotionStreak3D::isStartingPositionInitialized);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:reset");
	LUA_TRY_INVOKE(0, &cocos2d::MotionStreak3D::reset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setBlendFunc");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::setStartingPositionInitialized);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStroke");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::setStroke);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setSweepAxis");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::setSweepAxis);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setTexture");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:tintWithColor");
	LUA_TRY_INVOKE(1, &cocos2d::MotionStreak3D::tintWithColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cocos2d::MotionStreak3D>(*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cocos2d::MotionStreak3D>(*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak3D, "MotionStreak3D", "cc.MotionStreak3D",
		cocos2d::MotionStreak3D, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_MotionStreak3D_getBlendFunc);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak3D_getStroke);
	LUA_METHOD("getSweepAxis", lua_cocos2d_MotionStreak3D_getSweepAxis);
	LUA_METHOD("getTexture", lua_cocos2d_MotionStreak3D_getTexture);
	LUA_METHOD("initWithFade", lua_cocos2d_MotionStreak3D_initWithFade);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak3D_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak3D_reset);
	LUA_METHOD("setBlendFunc", lua_cocos2d_MotionStreak3D_setBlendFunc);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak3D_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak3D_setStroke);
	LUA_METHOD("setSweepAxis", lua_cocos2d_MotionStreak3D_setSweepAxis);
	LUA_METHOD("setTexture", lua_cocos2d_MotionStreak3D_setTexture);
	LUA_METHOD("tintWithColor", lua_cocos2d_MotionStreak3D_tintWithColor);
	LUA_METHOD("create", lua_cocos2d_MotionStreak3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ComponentLua_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ComponentLua", "cc.ComponentLua:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::ComponentLua::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccComponentLua(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ComponentLua, "ComponentLua", "cc.ComponentLua",
		cocos2d::ComponentLua, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ComponentLua_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
