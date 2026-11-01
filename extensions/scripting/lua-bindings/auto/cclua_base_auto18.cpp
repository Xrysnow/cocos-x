#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_TransitionCrossFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionCrossFade", "cc.TransitionCrossFade:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionCrossFade*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionCrossFade::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionCrossFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionCrossFade, "TransitionCrossFade", "cc.TransitionCrossFade",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionCrossFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionTurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionTurnOffTiles*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionTurnOffTiles::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionTurnOffTiles, "TransitionTurnOffTiles", "cc.TransitionTurnOffTiles",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionTurnOffTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSplitCols_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:action");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSplitCols::*)()>(&cocos2d::TransitionSplitCols::action));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionSplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSplitCols*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitCols::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitCols, "TransitionSplitCols", "cc.TransitionSplitCols",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionSplitCols_action);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitRows", "cc.TransitionSplitRows:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSplitRows*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitRows::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitRows, "TransitionSplitRows", "cc.TransitionSplitRows",
		cocos2d::TransitionSplitCols, "cc.TransitionSplitCols",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeTR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFadeTR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeTR::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeTR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeTR, "TransitionFadeTR", "cc.TransitionFadeTR",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeTR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeBL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeBL", "cc.TransitionFadeBL:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFadeBL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeBL::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeBL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeBL, "TransitionFadeBL", "cc.TransitionFadeBL",
		cocos2d::TransitionFadeTR, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeBL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeUp_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeUp", "cc.TransitionFadeUp:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFadeUp*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeUp::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeUp(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeUp, "TransitionFadeUp", "cc.TransitionFadeUp",
		cocos2d::TransitionFadeTR, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeUp_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeDown_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeDown", "cc.TransitionFadeDown:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFadeDown*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeDown::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeDown(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeDown, "TransitionFadeDown", "cc.TransitionFadeDown",
		cocos2d::TransitionFadeTR, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeDown_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionPageTurn_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:initWithDuration");
	LUA_TRY_INVOKE_R(3, static_cast<bool(cocos2d::TransitionPageTurn::*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::initWithDuration));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TransitionPageTurn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionPageTurn*(*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::create));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionPageTurn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionPageTurn, "TransitionPageTurn", "cc.TransitionPageTurn",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionPageTurn_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionPageTurn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgress_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgress", "cc.TransitionProgress:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionProgress*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgress::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgress(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgress, "TransitionProgress", "cc.TransitionProgress",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgress_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionProgressRadialCCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCCW::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCCW, "TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW",
		cocos2d::TransitionProgress, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCW", "cc.TransitionProgressRadialCW:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionProgressRadialCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCW::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCW, "TransitionProgressRadialCW", "cc.TransitionProgressRadialCW",
		cocos2d::TransitionProgress, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
