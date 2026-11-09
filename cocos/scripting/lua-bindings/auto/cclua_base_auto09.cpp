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

int lua_cocos2d_EaseElasticIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticIn", "cc.EaseElasticIn:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseElasticIn*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseElasticIn::create)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticIn::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticIn, "EaseElasticIn", "cc.EaseElasticIn",
		cocos2d::EaseElasticIn, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElasticOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticOut", "cc.EaseElasticOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseElasticOut*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseElasticOut::create)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticOut, "EaseElasticOut", "cc.EaseElasticOut",
		cocos2d::EaseElasticOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElasticInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticInOut", "cc.EaseElasticInOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseElasticInOut*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseElasticInOut::create)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticInOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticInOut, "EaseElasticInOut", "cc.EaseElasticInOut",
		cocos2d::EaseElasticInOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBezierAction_setBezierParamer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:setBezierParamer");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::EaseBezierAction::*)(float, float, float, float)>(&cocos2d::EaseBezierAction::setBezierParamer)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_EaseBezierAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBezierAction*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBezierAction::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBezierAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBezierAction, "EaseBezierAction", "cc.EaseBezierAction",
		cocos2d::EaseBezierAction, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("setBezierParamer", lua_cocos2d_EaseBezierAction_setBezierParamer);
	LUA_METHOD("create", lua_cocos2d_EaseBezierAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccActionInstant(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionInstant, "ActionInstant", "cc.ActionInstant",
		cocos2d::ActionInstant, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Show_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Show", "cc.Show:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Show*(*)()>(&cocos2d::Show::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccShow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Show, "Show", "cc.Show",
		cocos2d::Show, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_Show_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Hide_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Hide", "cc.Hide:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Hide*(*)()>(&cocos2d::Hide::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccHide(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Hide, "Hide", "cc.Hide",
		cocos2d::Hide, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_Hide_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ToggleVisibility_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ToggleVisibility", "cc.ToggleVisibility:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ToggleVisibility*(*)()>(&cocos2d::ToggleVisibility::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccToggleVisibility(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ToggleVisibility, "ToggleVisibility", "cc.ToggleVisibility",
		cocos2d::ToggleVisibility, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ToggleVisibility_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RemoveSelf_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::RemoveSelf::*)(bool)>(&cocos2d::RemoveSelf::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RemoveSelf_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::RemoveSelf*(*)(bool)>(&cocos2d::RemoveSelf::create));
	LUA_TRY_INVOKE_R(0, [](){{return cocos2d::RemoveSelf::create();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccRemoveSelf(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RemoveSelf, "RemoveSelf", "cc.RemoveSelf",
		cocos2d::RemoveSelf, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_RemoveSelf_init);
	LUA_METHOD("create", lua_cocos2d_RemoveSelf_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipX_initWithFlipX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX", "cc.FlipX:initWithFlipX");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FlipX::*)(bool)>(&cocos2d::FlipX::initWithFlipX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX", "cc.FlipX:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FlipX*(*)(bool)>(&cocos2d::FlipX::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipX, "FlipX", "cc.FlipX",
		cocos2d::FlipX, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipX", lua_cocos2d_FlipX_initWithFlipX);
	LUA_METHOD("create", lua_cocos2d_FlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipY_initWithFlipY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipY", "cc.FlipY:initWithFlipY");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FlipY::*)(bool)>(&cocos2d::FlipY::initWithFlipY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY", "cc.FlipY:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FlipY*(*)(bool)>(&cocos2d::FlipY::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipY, "FlipY", "cc.FlipY",
		cocos2d::FlipY, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipY", lua_cocos2d_FlipY_initWithFlipY);
	LUA_METHOD("create", lua_cocos2d_FlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Place_initWithPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Place", "cc.Place:initWithPosition");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Place::*)(const cocos2d::Vec2&)>(&cocos2d::Place::initWithPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Place_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Place", "cc.Place:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Place*(*)(const cocos2d::Vec2&)>(&cocos2d::Place::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccPlace(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Place, "Place", "cc.Place",
		cocos2d::Place, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithPosition", lua_cocos2d_Place_initWithPosition);
	LUA_METHOD("create", lua_cocos2d_Place_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
