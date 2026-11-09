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
int lua_cocos2d_Liquid_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Liquid::*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Liquid::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
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
int lua_cocos2d_Liquid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Liquid", "cc.Liquid:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Liquid*(*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Liquid::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLiquid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Liquid, "Liquid", "cc.Liquid",
		cocos2d::Liquid, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Liquid_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Liquid_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Liquid_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Liquid_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Liquid_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Liquid_create);
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
int lua_cocos2d_Waves_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:initWithDuration");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::Waves::*)(float, const cocos2d::Vec2&, unsigned int, float, bool, bool)>(&cocos2d::Waves::initWithDuration)));
	LUA_INVOKE_FOOTER("6");
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
int lua_cocos2d_Waves_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves", "cc.Waves:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::Waves*(*)(float, const cocos2d::Vec2&, unsigned int, float, bool, bool)>(&cocos2d::Waves::create)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccWaves(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Waves, "Waves", "cc.Waves",
		cocos2d::Waves, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Waves_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Waves_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Waves_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Waves_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Waves_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Waves_create);
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
int lua_cocos2d_Twirl_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Twirl::*)()const>(&cocos2d::Twirl::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:initWithDuration");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::Twirl::*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Twirl::initWithDuration)));
	LUA_INVOKE_FOOTER("5");
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
int lua_cocos2d_Twirl_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Twirl::*)(const cocos2d::Vec2&)>(&cocos2d::Twirl::setPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Twirl_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Twirl", "cc.Twirl:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::Twirl*(*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Twirl::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccTwirl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Twirl, "Twirl", "cc.Twirl",
		cocos2d::Twirl, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Twirl_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Twirl_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cocos2d_Twirl_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Twirl_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Twirl_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Twirl_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cocos2d_Twirl_setPosition);
	LUA_METHOD("create", lua_cocos2d_Twirl_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionManager_addAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:addAction");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ActionManager::*)(cocos2d::Action*, cocos2d::Node*, bool)>(&cocos2d::ActionManager::addAction)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ActionManager_getActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getActionByTag");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Action*(cocos2d::ActionManager::*)(int, const cocos2d::Node*)const>(&cocos2d::ActionManager::getActionByTag)));
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
	LUA_TRY_INVOKE_R(2, (static_cast<size_t(cocos2d::ActionManager::*)(const cocos2d::Node*, int)>(&cocos2d::ActionManager::getNumberOfRunningActionsInTargetByTag)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_pauseAllRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:pauseAllRunningActions");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocos2d::Node *>(cocos2d::ActionManager::*)()>(&cocos2d::ActionManager::pauseAllRunningActions));
	LUA_INVOKE_FOOTER("0");
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ActionManager::*)(int, cocos2d::Node*)>(&cocos2d::ActionManager::removeActionByTag)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ActionManager_removeActionsByFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeActionsByFlags");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ActionManager::*)(unsigned int, cocos2d::Node*)>(&cocos2d::ActionManager::removeActionsByFlags)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ActionManager::*)(int, cocos2d::Node*)>(&cocos2d::ActionManager::removeAllActionsByTag)));
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
int lua_cocos2d_ActionManager_resumeTargets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:resumeTargets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionManager::*)(const cocos2d::Vector<cocos2d::Node *>&)>(&cocos2d::ActionManager::resumeTargets));
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
		cocos2d::ActionManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAction", lua_cocos2d_ActionManager_addAction);
	LUA_METHOD("getActionByTag", lua_cocos2d_ActionManager_getActionByTag);
	LUA_METHOD("getNumberOfRunningActions", lua_cocos2d_ActionManager_getNumberOfRunningActions);
	LUA_METHOD("getNumberOfRunningActionsInTarget", lua_cocos2d_ActionManager_getNumberOfRunningActionsInTarget);
	LUA_METHOD("getNumberOfRunningActionsInTargetByTag", lua_cocos2d_ActionManager_getNumberOfRunningActionsInTargetByTag);
	LUA_METHOD("pauseAllRunningActions", lua_cocos2d_ActionManager_pauseAllRunningActions);
	LUA_METHOD("pauseTarget", lua_cocos2d_ActionManager_pauseTarget);
	LUA_METHOD("removeAction", lua_cocos2d_ActionManager_removeAction);
	LUA_METHOD("removeActionByTag", lua_cocos2d_ActionManager_removeActionByTag);
	LUA_METHOD("removeActionsByFlags", lua_cocos2d_ActionManager_removeActionsByFlags);
	LUA_METHOD("removeAllActions", lua_cocos2d_ActionManager_removeAllActions);
	LUA_METHOD("removeAllActionsByTag", lua_cocos2d_ActionManager_removeAllActionsByTag);
	LUA_METHOD("removeAllActionsFromTarget", lua_cocos2d_ActionManager_removeAllActionsFromTarget);
	LUA_METHOD("resumeTarget", lua_cocos2d_ActionManager_resumeTarget);
	LUA_METHOD("resumeTargets", lua_cocos2d_ActionManager_resumeTargets);
	LUA_METHOD("update", lua_cocos2d_ActionManager_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PageTurn3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PageTurn3D", "cc.PageTurn3D:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::PageTurn3D*(*)(float, const cocos2d::Vec2&)>(&cocos2d::PageTurn3D::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccPageTurn3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PageTurn3D, "PageTurn3D", "cc.PageTurn3D",
		cocos2d::PageTurn3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_PageTurn3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProgressTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ProgressTo::*)(float, float)>(&cocos2d::ProgressTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ProgressTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ProgressTo*(*)(float, float)>(&cocos2d::ProgressTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccProgressTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressTo, "ProgressTo", "cc.ProgressTo",
		cocos2d::ProgressTo, "cc.ActionInterval",
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
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ProgressFromTo::*)(float, float, float)>(&cocos2d::ProgressFromTo::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ProgressFromTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressFromTo", "cc.ProgressFromTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ProgressFromTo*(*)(float, float, float)>(&cocos2d::ProgressFromTo::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccProgressFromTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressFromTo, "ProgressFromTo", "cc.ProgressFromTo",
		cocos2d::ProgressFromTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ProgressFromTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ProgressFromTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ShakyTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShakyTiles3D", "cc.ShakyTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ShakyTiles3D::*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::ShakyTiles3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ShakyTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShakyTiles3D", "cc.ShakyTiles3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ShakyTiles3D*(*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::ShakyTiles3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShakyTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShakyTiles3D, "ShakyTiles3D", "cc.ShakyTiles3D",
		cocos2d::ShakyTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ShakyTiles3D_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ShakyTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ShatteredTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShatteredTiles3D", "cc.ShatteredTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ShatteredTiles3D::*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::ShatteredTiles3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ShatteredTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShatteredTiles3D", "cc.ShatteredTiles3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ShatteredTiles3D*(*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::ShatteredTiles3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShatteredTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShatteredTiles3D, "ShatteredTiles3D", "cc.ShatteredTiles3D",
		cocos2d::ShatteredTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ShatteredTiles3D_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ShatteredTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ShuffleTiles_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:getDelta");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::ShuffleTiles::*)(const cocos2d::Vec2&)const>(&cocos2d::ShuffleTiles::getDelta));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ShuffleTiles_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ShuffleTiles::*)(float, const cocos2d::Vec2&, unsigned int)>(&cocos2d::ShuffleTiles::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ShuffleTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ShuffleTiles*(*)(float, const cocos2d::Vec2&, unsigned int)>(&cocos2d::ShuffleTiles::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccShuffleTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ShuffleTiles, "ShuffleTiles", "cc.ShuffleTiles",
		cocos2d::ShuffleTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getDelta", lua_cocos2d_ShuffleTiles_getDelta);
	LUA_METHOD("initWithDuration", lua_cocos2d_ShuffleTiles_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ShuffleTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOutTRTiles_testFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:testFunc");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocos2d::FadeOutTRTiles::*)(const cocos2d::Vec2&, float)>(&cocos2d::FadeOutTRTiles::testFunc)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FadeOutTRTiles_transformTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:transformTile");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FadeOutTRTiles::*)(const cocos2d::Vec2&, float)>(&cocos2d::FadeOutTRTiles::transformTile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FadeOutTRTiles_turnOffTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:turnOffTile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeOutTRTiles::*)(const cocos2d::Vec2&)>(&cocos2d::FadeOutTRTiles::turnOffTile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeOutTRTiles_turnOnTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:turnOnTile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeOutTRTiles::*)(const cocos2d::Vec2&)>(&cocos2d::FadeOutTRTiles::turnOnTile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeOutTRTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeOutTRTiles*(*)(float, const cocos2d::Vec2&)>(&cocos2d::FadeOutTRTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutTRTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutTRTiles, "FadeOutTRTiles", "cc.FadeOutTRTiles",
		cocos2d::FadeOutTRTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("testFunc", lua_cocos2d_FadeOutTRTiles_testFunc);
	LUA_METHOD("transformTile", lua_cocos2d_FadeOutTRTiles_transformTile);
	LUA_METHOD("turnOffTile", lua_cocos2d_FadeOutTRTiles_turnOffTile);
	LUA_METHOD("turnOnTile", lua_cocos2d_FadeOutTRTiles_turnOnTile);
	LUA_METHOD("create", lua_cocos2d_FadeOutTRTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOutBLTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutBLTiles", "cc.FadeOutBLTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeOutBLTiles*(*)(float, const cocos2d::Vec2&)>(&cocos2d::FadeOutBLTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutBLTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutBLTiles, "FadeOutBLTiles", "cc.FadeOutBLTiles",
		cocos2d::FadeOutBLTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_FadeOutBLTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
