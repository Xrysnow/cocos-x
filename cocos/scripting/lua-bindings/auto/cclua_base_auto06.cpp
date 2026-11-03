#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_Core_ccCatmullRomTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CatmullRomTo, "CatmullRomTo", "cc.CatmullRomTo",
		cocos2d::CardinalSplineTo, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCatmullRomBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CatmullRomBy, "CatmullRomBy", "cc.CatmullRomBy",
		cocos2d::CardinalSplineBy, "cc.CardinalSplineBy",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionEase_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::ActionEase::*)()>(&cocos2d::ActionEase::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionEase_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:initWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ActionEase::*)(cocos2d::ActionInterval*)>(&cocos2d::ActionEase::initWithAction));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionEase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionEase, "ActionEase", "cc.ActionEase",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_ActionEase_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_ActionEase_initWithAction);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseRateAction_getRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:getRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EaseRateAction::*)()const>(&cocos2d::EaseRateAction::getRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EaseRateAction_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:initWithAction");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::EaseRateAction::*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseRateAction::initWithAction));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EaseRateAction_setRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:setRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EaseRateAction::*)(float)>(&cocos2d::EaseRateAction::setRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EaseRateAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::EaseRateAction*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseRateAction::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseRateAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseRateAction, "EaseRateAction", "cc.EaseRateAction",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getRate", lua_cocos2d_EaseRateAction_getRate);
	LUA_METHOD("initWithAction", lua_cocos2d_EaseRateAction_initWithAction);
	LUA_METHOD("setRate", lua_cocos2d_EaseRateAction_setRate);
	LUA_METHOD("create", lua_cocos2d_EaseRateAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialIn", "cc.EaseExponentialIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseExponentialIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseExponentialIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialIn, "EaseExponentialIn", "cc.EaseExponentialIn",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialOut", "cc.EaseExponentialOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseExponentialOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseExponentialOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialOut, "EaseExponentialOut", "cc.EaseExponentialOut",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialInOut", "cc.EaseExponentialInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseExponentialInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseExponentialInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialInOut, "EaseExponentialInOut", "cc.EaseExponentialInOut",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineIn", "cc.EaseSineIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseSineIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseSineIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineIn, "EaseSineIn", "cc.EaseSineIn",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineOut", "cc.EaseSineOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseSineOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseSineOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineOut, "EaseSineOut", "cc.EaseSineOut",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineInOut", "cc.EaseSineInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseSineInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseSineInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineInOut, "EaseSineInOut", "cc.EaseSineInOut",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEaseBounce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounce, "EaseBounce", "cc.EaseBounce",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBounceIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceIn", "cc.EaseBounceIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBounceIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBounceIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceIn, "EaseBounceIn", "cc.EaseBounceIn",
		cocos2d::ActionEase, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
