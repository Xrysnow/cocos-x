#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_Liquid_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Liquid::*)()const>(&cocos2d::Liquid::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Liquid_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Liquid::*)()const>(&cocos2d::Liquid::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Liquid_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Liquid::*)(float)>(&cocos2d::Liquid::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Liquid_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Liquid::*)(float)>(&cocos2d::Liquid::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccLiquid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Liquid, "Liquid", "cc.Liquid",
		cocos2d::Grid3DAction, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Liquid_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Liquid_getAmplitudeRate);
	LUA_METHOD("setAmplitude", lua_cocos2d_Liquid_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Liquid_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Waves_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Waves::*)()const>(&cocos2d::Waves::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Waves::*)()const>(&cocos2d::Waves::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Waves::*)(float)>(&cocos2d::Waves::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Waves::*)(float)>(&cocos2d::Waves::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccWaves(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Waves, "Waves", "cc.Waves",
		cocos2d::Grid3DAction, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Waves_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Waves_getAmplitudeRate);
	LUA_METHOD("setAmplitude", lua_cocos2d_Waves_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Waves_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Twirl_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Twirl::*)()const>(&cocos2d::Twirl::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Twirl::*)()const>(&cocos2d::Twirl::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Twirl::*)(float)>(&cocos2d::Twirl::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Twirl_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Twirl::*)(float)>(&cocos2d::Twirl::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTwirl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Twirl, "Twirl", "cc.Twirl",
		cocos2d::Grid3DAction, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Twirl_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Twirl_getAmplitudeRate);
	LUA_METHOD("setAmplitude", lua_cocos2d_Twirl_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Twirl_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionManager_addAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:addAction");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ActionManager::*)(cocos2d::Action*, cocos2d::Node*, bool)>(&cocos2d::ActionManager::addAction));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ActionManager_getActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getActionByTag");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Action*(cocos2d::ActionManager::*)(int, const cocos2d::Node*)const>(&cocos2d::ActionManager::getActionByTag));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_getNumberOfRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActions");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ActionManager::*)()const>(&cocos2d::ActionManager::getNumberOfRunningActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionManager_getNumberOfRunningActionsInTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActionsInTarget");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::ActionManager::*)(const cocos2d::Node*)const>(&cocos2d::ActionManager::getNumberOfRunningActionsInTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionManager_getNumberOfRunningActionsInTargetByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActionsInTargetByTag");
	LUA_TRY_INVOKE_R(2, static_cast<size_t(cocos2d::ActionManager::*)(const cocos2d::Node*, int)>(&cocos2d::ActionManager::getNumberOfRunningActionsInTargetByTag));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_pauseTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:pauseTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(cocos2d::Node*)>(&cocos2d::ActionManager::pauseTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionManager_removeAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(cocos2d::Action*)>(&cocos2d::ActionManager::removeAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionManager_removeActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeActionByTag");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ActionManager::*)(int, cocos2d::Node*)>(&cocos2d::ActionManager::removeActionByTag));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_removeActionsByFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeActionsByFlags");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ActionManager::*)(unsigned int, cocos2d::Node*)>(&cocos2d::ActionManager::removeActionsByFlags));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_removeAllActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActions");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ActionManager::*)()>(&cocos2d::ActionManager::removeAllActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionManager_removeAllActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActionsByTag");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ActionManager::*)(int, cocos2d::Node*)>(&cocos2d::ActionManager::removeAllActionsByTag));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_removeAllActionsFromTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActionsFromTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(cocos2d::Node*)>(&cocos2d::ActionManager::removeAllActionsFromTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionManager_resumeTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:resumeTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(cocos2d::Node*)>(&cocos2d::ActionManager::resumeTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionManager_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:update");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(float)>(&cocos2d::ActionManager::update));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionManager, "ActionManager", "cc.ActionManager",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAction", lua_cocos2d_ActionManager_addAction);
	LUA_METHOD("getActionByTag", lua_cocos2d_ActionManager_getActionByTag);
	LUA_METHOD("getNumberOfRunningActions", lua_cocos2d_ActionManager_getNumberOfRunningActions);
	LUA_METHOD("getNumberOfRunningActionsInTarget", lua_cocos2d_ActionManager_getNumberOfRunningActionsInTarget);
	LUA_METHOD("getNumberOfRunningActionsInTargetByTag", lua_cocos2d_ActionManager_getNumberOfRunningActionsInTargetByTag);
	LUA_METHOD("pauseTarget", lua_cocos2d_ActionManager_pauseTarget);
	LUA_METHOD("removeAction", lua_cocos2d_ActionManager_removeAction);
	LUA_METHOD("removeActionByTag", lua_cocos2d_ActionManager_removeActionByTag);
	LUA_METHOD("removeActionsByFlags", lua_cocos2d_ActionManager_removeActionsByFlags);
	LUA_METHOD("removeAllActions", lua_cocos2d_ActionManager_removeAllActions);
	LUA_METHOD("removeAllActionsByTag", lua_cocos2d_ActionManager_removeAllActionsByTag);
	LUA_METHOD("removeAllActionsFromTarget", lua_cocos2d_ActionManager_removeAllActionsFromTarget);
	LUA_METHOD("resumeTarget", lua_cocos2d_ActionManager_resumeTarget);
	LUA_METHOD("update", lua_cocos2d_ActionManager_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccPageTurn3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PageTurn3D, "PageTurn3D", "cc.PageTurn3D",
		cocos2d::Grid3DAction, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProgressTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::ProgressTo::*)(float, float)>(&cocos2d::ProgressTo::initWithDuration));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ProgressTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ProgressTo*(*)(float, float)>(&cocos2d::ProgressTo::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccProgressTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressTo, "ProgressTo", "cc.ProgressTo",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ProgressTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ProgressTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProgressFromTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressFromTo", "cc.ProgressFromTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, static_cast<bool(cocos2d::ProgressFromTo::*)(float, float, float)>(&cocos2d::ProgressFromTo::initWithDuration));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ProgressFromTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressFromTo", "cc.ProgressFromTo:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ProgressFromTo*(*)(float, float, float)>(&cocos2d::ProgressFromTo::create));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccProgressFromTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressFromTo, "ProgressFromTo", "cc.ProgressFromTo",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ProgressFromTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ProgressFromTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccShakyTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShakyTiles3D, "ShakyTiles3D", "cc.ShakyTiles3D",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccShatteredTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShatteredTiles3D, "ShatteredTiles3D", "cc.ShatteredTiles3D",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccShuffleTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShuffleTiles, "ShuffleTiles", "cc.ShuffleTiles",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccFadeOutTRTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutTRTiles, "FadeOutTRTiles", "cc.FadeOutTRTiles",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccFadeOutBLTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutBLTiles, "FadeOutBLTiles", "cc.FadeOutBLTiles",
		cocos2d::FadeOutTRTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
