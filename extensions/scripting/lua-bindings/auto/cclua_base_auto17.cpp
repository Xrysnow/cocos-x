#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_TransitionSlideInL_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:action");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSlideInL::*)()>(&cocos2d::TransitionSlideInL::action));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionSlideInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSlideInL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInL::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInL, "TransitionSlideInL", "cc.TransitionSlideInL",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionSlideInL_action);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInR", "cc.TransitionSlideInR:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSlideInR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInR::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInR, "TransitionSlideInR", "cc.TransitionSlideInR",
		cocos2d::TransitionSlideInL, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInB", "cc.TransitionSlideInB:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSlideInB*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInB::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInB, "TransitionSlideInB", "cc.TransitionSlideInB",
		cocos2d::TransitionSlideInL, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInT", "cc.TransitionSlideInT:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionSlideInT*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInT::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInT, "TransitionSlideInT", "cc.TransitionSlideInT",
		cocos2d::TransitionSlideInL, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionShrinkGrow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionShrinkGrow*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionShrinkGrow::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionShrinkGrow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionShrinkGrow, "TransitionShrinkGrow", "cc.TransitionShrinkGrow",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionShrinkGrow_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipX", "cc.TransitionFlipX:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipX::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipX::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipX, "TransitionFlipX", "cc.TransitionFlipX",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipY", "cc.TransitionFlipY:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipY::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipY::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipY, "TransitionFlipY", "cc.TransitionFlipY",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipAngular", "cc.TransitionFlipAngular:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipAngular::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipAngular::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipAngular, "TransitionFlipAngular", "cc.TransitionFlipAngular",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipX", "cc.TransitionZoomFlipX:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipX::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipX::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipX, "TransitionZoomFlipX", "cc.TransitionZoomFlipX",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipY", "cc.TransitionZoomFlipY:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipY::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipY::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipY, "TransitionZoomFlipY", "cc.TransitionZoomFlipY",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipAngular::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipAngular::create));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipAngular, "TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular",
		cocos2d::TransitionSceneOriented, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTransitionFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFade, "TransitionFade", "cc.TransitionFade",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
