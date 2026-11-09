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

int lua_cocos2d_EaseQuinticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionOut", "cc.EaseQuinticActionOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuinticActionOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuinticActionOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionOut, "EaseQuinticActionOut", "cc.EaseQuinticActionOut",
		cocos2d::EaseQuinticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuinticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionInOut", "cc.EaseQuinticActionInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuinticActionInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuinticActionInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionInOut, "EaseQuinticActionInOut", "cc.EaseQuinticActionInOut",
		cocos2d::EaseQuinticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionIn", "cc.EaseCircleActionIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCircleActionIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCircleActionIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionIn, "EaseCircleActionIn", "cc.EaseCircleActionIn",
		cocos2d::EaseCircleActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionOut", "cc.EaseCircleActionOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCircleActionOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCircleActionOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionOut, "EaseCircleActionOut", "cc.EaseCircleActionOut",
		cocos2d::EaseCircleActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionInOut", "cc.EaseCircleActionInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCircleActionInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCircleActionInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionInOut, "EaseCircleActionInOut", "cc.EaseCircleActionInOut",
		cocos2d::EaseCircleActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionIn", "cc.EaseCubicActionIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCubicActionIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCubicActionIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionIn, "EaseCubicActionIn", "cc.EaseCubicActionIn",
		cocos2d::EaseCubicActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionOut", "cc.EaseCubicActionOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCubicActionOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCubicActionOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionOut, "EaseCubicActionOut", "cc.EaseCubicActionOut",
		cocos2d::EaseCubicActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionInOut", "cc.EaseCubicActionInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseCubicActionInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseCubicActionInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionInOut, "EaseCubicActionInOut", "cc.EaseCubicActionInOut",
		cocos2d::EaseCubicActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseIn", "cc.EaseIn:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseIn*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseIn::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseIn, "EaseIn", "cc.EaseIn",
		cocos2d::EaseIn, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseOut", "cc.EaseOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseOut*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseOut::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseOut, "EaseOut", "cc.EaseOut",
		cocos2d::EaseOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseInOut", "cc.EaseInOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EaseInOut*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseInOut::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseInOut, "EaseInOut", "cc.EaseInOut",
		cocos2d::EaseInOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElastic_getPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:getPeriod");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EaseElastic::*)()const>(&cocos2d::EaseElastic::getPeriod));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EaseElastic_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:initWithAction");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::EaseElastic::*)(cocos2d::ActionInterval*, float)>(&cocos2d::EaseElastic::initWithAction)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::EaseElastic* obj,cocos2d::ActionInterval* arg0){{return obj->initWithAction(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EaseElastic_setPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:setPeriod");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EaseElastic::*)(float)>(&cocos2d::EaseElastic::setPeriod));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseElastic(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElastic, "EaseElastic", "cc.EaseElastic",
		cocos2d::EaseElastic, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getPeriod", lua_cocos2d_EaseElastic_getPeriod);
	LUA_METHOD("initWithAction", lua_cocos2d_EaseElastic_initWithAction);
	LUA_METHOD("setPeriod", lua_cocos2d_EaseElastic_setPeriod);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
