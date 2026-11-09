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

int lua_cocos2d_TransitionSlideInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInT", "cc.TransitionSlideInT:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSlideInT*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInT::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInT, "TransitionSlideInT", "cc.TransitionSlideInT",
		cocos2d::TransitionSlideInT, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionShrinkGrow_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionShrinkGrow::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionShrinkGrow::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionShrinkGrow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionShrinkGrow*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionShrinkGrow::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionShrinkGrow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionShrinkGrow, "TransitionShrinkGrow", "cc.TransitionShrinkGrow",
		cocos2d::TransitionShrinkGrow, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionShrinkGrow_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionShrinkGrow_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipX", "cc.TransitionFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipX, "TransitionFlipX", "cc.TransitionFlipX",
		cocos2d::TransitionFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipY", "cc.TransitionFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipY, "TransitionFlipY", "cc.TransitionFlipY",
		cocos2d::TransitionFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipAngular", "cc.TransitionFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipAngular, "TransitionFlipAngular", "cc.TransitionFlipAngular",
		cocos2d::TransitionFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipX", "cc.TransitionZoomFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipX, "TransitionZoomFlipX", "cc.TransitionZoomFlipX",
		cocos2d::TransitionZoomFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipY", "cc.TransitionZoomFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipY, "TransitionZoomFlipY", "cc.TransitionZoomFlipY",
		cocos2d::TransitionZoomFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipAngular, "TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular",
		cocos2d::TransitionZoomFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFade_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TransitionFade::*)(float, cocos2d::Scene*, const cocos2d::Color3B&)>(&cocos2d::TransitionFade::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TransitionFade::*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFade::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_TransitionFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFade*(*)(float, cocos2d::Scene*, const cocos2d::Color3B&)>(&cocos2d::TransitionFade::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFade*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFade::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFade, "TransitionFade", "cc.TransitionFade",
		cocos2d::TransitionFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionFade_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionCrossFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionCrossFade", "cc.TransitionCrossFade:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionCrossFade*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionCrossFade::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionCrossFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionCrossFade, "TransitionCrossFade", "cc.TransitionCrossFade",
		cocos2d::TransitionCrossFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionCrossFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionTurnOffTiles_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionTurnOffTiles::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionTurnOffTiles::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionTurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionTurnOffTiles*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionTurnOffTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionTurnOffTiles, "TransitionTurnOffTiles", "cc.TransitionTurnOffTiles",
		cocos2d::TransitionTurnOffTiles, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionTurnOffTiles_easeActionWithAction);
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
int lua_cocos2d_TransitionSplitCols_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSplitCols::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionSplitCols::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionSplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSplitCols*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitCols::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitCols, "TransitionSplitCols", "cc.TransitionSplitCols",
		cocos2d::TransitionSplitCols, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionSplitCols_action);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionSplitCols_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
