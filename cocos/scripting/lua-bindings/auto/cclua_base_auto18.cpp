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

int lua_cocos2d_TransitionSplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitRows", "cc.TransitionSplitRows:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSplitRows*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitRows::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitRows, "TransitionSplitRows", "cc.TransitionSplitRows",
		cocos2d::TransitionSplitRows, "cc.TransitionSplitCols",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeTR_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:actionWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionFadeTR::*)(const cocos2d::Vec2&)>(&cocos2d::TransitionFadeTR::actionWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionFadeTR_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionFadeTR::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionFadeTR::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionFadeTR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeTR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeTR::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeTR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeTR, "TransitionFadeTR", "cc.TransitionFadeTR",
		cocos2d::TransitionFadeTR, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cocos2d_TransitionFadeTR_actionWithSize);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionFadeTR_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeTR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeBL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeBL", "cc.TransitionFadeBL:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeBL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeBL::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeBL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeBL, "TransitionFadeBL", "cc.TransitionFadeBL",
		cocos2d::TransitionFadeBL, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeBL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeUp_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeUp", "cc.TransitionFadeUp:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeUp*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeUp::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeUp(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeUp, "TransitionFadeUp", "cc.TransitionFadeUp",
		cocos2d::TransitionFadeUp, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeUp_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeDown_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeDown", "cc.TransitionFadeDown:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeDown*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeDown::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeDown(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeDown, "TransitionFadeDown", "cc.TransitionFadeDown",
		cocos2d::TransitionFadeDown, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeDown_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionPageTurn_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:actionWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionPageTurn::*)(const cocos2d::Vec2&)>(&cocos2d::TransitionPageTurn::actionWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionPageTurn_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TransitionPageTurn::*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TransitionPageTurn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionPageTurn*(*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionPageTurn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionPageTurn, "TransitionPageTurn", "cc.TransitionPageTurn",
		cocos2d::TransitionPageTurn, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cocos2d_TransitionPageTurn_actionWithSize);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionPageTurn_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionPageTurn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgress_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgress", "cc.TransitionProgress:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgress*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgress::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgress(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgress, "TransitionProgress", "cc.TransitionProgress",
		cocos2d::TransitionProgress, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgress_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressRadialCCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCCW::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCCW, "TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW",
		cocos2d::TransitionProgressRadialCCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCW", "cc.TransitionProgressRadialCW:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressRadialCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCW::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCW, "TransitionProgressRadialCW", "cc.TransitionProgressRadialCW",
		cocos2d::TransitionProgressRadialCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressHorizontal_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressHorizontal", "cc.TransitionProgressHorizontal:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressHorizontal*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressHorizontal::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressHorizontal(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressHorizontal, "TransitionProgressHorizontal", "cc.TransitionProgressHorizontal",
		cocos2d::TransitionProgressHorizontal, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressHorizontal_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressVertical_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressVertical", "cc.TransitionProgressVertical:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressVertical*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressVertical::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressVertical(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressVertical, "TransitionProgressVertical", "cc.TransitionProgressVertical",
		cocos2d::TransitionProgressVertical, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressVertical_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressInOut", "cc.TransitionProgressInOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressInOut*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressInOut::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressInOut, "TransitionProgressInOut", "cc.TransitionProgressInOut",
		cocos2d::TransitionProgressInOut, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
