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

int lua_cocos2d_EaseBounceOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceOut", "cc.EaseBounceOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBounceOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBounceOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceOut, "EaseBounceOut", "cc.EaseBounceOut",
		cocos2d::EaseBounceOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBounceInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceInOut", "cc.EaseBounceInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBounceInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBounceInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceInOut, "EaseBounceInOut", "cc.EaseBounceInOut",
		cocos2d::EaseBounceInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackIn", "cc.EaseBackIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBackIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBackIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackIn, "EaseBackIn", "cc.EaseBackIn",
		cocos2d::EaseBackIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackOut", "cc.EaseBackOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBackOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBackOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackOut, "EaseBackOut", "cc.EaseBackOut",
		cocos2d::EaseBackOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackInOut", "cc.EaseBackInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseBackInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseBackInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackInOut, "EaseBackInOut", "cc.EaseBackInOut",
		cocos2d::EaseBackInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionIn", "cc.EaseQuadraticActionIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuadraticActionIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuadraticActionIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionIn, "EaseQuadraticActionIn", "cc.EaseQuadraticActionIn",
		cocos2d::EaseQuadraticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionOut", "cc.EaseQuadraticActionOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuadraticActionOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuadraticActionOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionOut, "EaseQuadraticActionOut", "cc.EaseQuadraticActionOut",
		cocos2d::EaseQuadraticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuadraticActionInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuadraticActionInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionInOut, "EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut",
		cocos2d::EaseQuadraticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionIn", "cc.EaseQuarticActionIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuarticActionIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuarticActionIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionIn, "EaseQuarticActionIn", "cc.EaseQuarticActionIn",
		cocos2d::EaseQuarticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionOut", "cc.EaseQuarticActionOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuarticActionOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuarticActionOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionOut, "EaseQuarticActionOut", "cc.EaseQuarticActionOut",
		cocos2d::EaseQuarticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionInOut", "cc.EaseQuarticActionInOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuarticActionInOut*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuarticActionInOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionInOut, "EaseQuarticActionInOut", "cc.EaseQuarticActionInOut",
		cocos2d::EaseQuarticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuinticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionIn", "cc.EaseQuinticActionIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EaseQuinticActionIn*(*)(cocos2d::ActionInterval*)>(&cocos2d::EaseQuinticActionIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionIn, "EaseQuinticActionIn", "cc.EaseQuinticActionIn",
		cocos2d::EaseQuinticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
