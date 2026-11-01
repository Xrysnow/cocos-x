#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_ActionFrame_getAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getAction");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ActionInterval*(cocostudio::ActionFrame::*)(float, cocostudio::ActionFrame*)>(&cocostudio::ActionFrame::getAction));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionFrame::*)(float)>(&cocostudio::ActionFrame::getAction));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_ActionFrame_getEasingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getEasingType");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ActionFrame::*)()>(&cocostudio::ActionFrame::getEasingType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionFrame_getFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ActionFrame::*)()>(&cocostudio::ActionFrame::getFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionFrame_getFrameTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getFrameTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionFrame::*)()>(&cocostudio::ActionFrame::getFrameTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionFrame_getFrameType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getFrameType");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ActionFrame::*)()>(&cocostudio::ActionFrame::getFrameType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionFrame_setEasingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:setEasingType");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFrame::*)(int)>(&cocostudio::ActionFrame::setEasingType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionFrame_setFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:setFrameIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFrame::*)(int)>(&cocostudio::ActionFrame::setFrameIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionFrame_setFrameTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:setFrameTime");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFrame::*)(float)>(&cocostudio::ActionFrame::setFrameTime));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionFrame_setFrameType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:setFrameType");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFrame::*)(int)>(&cocostudio::ActionFrame::setFrameType));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionFrame, "ActionFrame", "ccs.ActionFrame",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionFrame_getAction);
	LUA_METHOD("getEasingType", lua_cocostudio_ActionFrame_getEasingType);
	LUA_METHOD("getFrameIndex", lua_cocostudio_ActionFrame_getFrameIndex);
	LUA_METHOD("getFrameTime", lua_cocostudio_ActionFrame_getFrameTime);
	LUA_METHOD("getFrameType", lua_cocostudio_ActionFrame_getFrameType);
	LUA_METHOD("setEasingType", lua_cocostudio_ActionFrame_setEasingType);
	LUA_METHOD("setFrameIndex", lua_cocostudio_ActionFrame_setFrameIndex);
	LUA_METHOD("setFrameTime", lua_cocostudio_ActionFrame_setFrameTime);
	LUA_METHOD("setFrameType", lua_cocostudio_ActionFrame_setFrameType);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Studio_ccsActionMoveFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionMoveFrame, "ActionMoveFrame", "ccs.ActionMoveFrame",
		cocostudio::ActionFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionScaleFrame_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionScaleFrame", "ccs.ActionScaleFrame:getScaleX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionScaleFrame::*)()>(&cocostudio::ActionScaleFrame::getScaleX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionScaleFrame_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionScaleFrame", "ccs.ActionScaleFrame:getScaleY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionScaleFrame::*)()>(&cocostudio::ActionScaleFrame::getScaleY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionScaleFrame_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionScaleFrame", "ccs.ActionScaleFrame:setScaleX");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionScaleFrame::*)(float)>(&cocostudio::ActionScaleFrame::setScaleX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionScaleFrame_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionScaleFrame", "ccs.ActionScaleFrame:setScaleY");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionScaleFrame::*)(float)>(&cocostudio::ActionScaleFrame::setScaleY));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionScaleFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionScaleFrame, "ActionScaleFrame", "ccs.ActionScaleFrame",
		cocostudio::ActionFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getScaleX", lua_cocostudio_ActionScaleFrame_getScaleX);
	LUA_METHOD("getScaleY", lua_cocostudio_ActionScaleFrame_getScaleY);
	LUA_METHOD("setScaleX", lua_cocostudio_ActionScaleFrame_setScaleX);
	LUA_METHOD("setScaleY", lua_cocostudio_ActionScaleFrame_setScaleY);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionRotationFrame_getRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionRotationFrame", "ccs.ActionRotationFrame:getRotation");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionRotationFrame::*)()>(&cocostudio::ActionRotationFrame::getRotation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionRotationFrame_setRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionRotationFrame", "ccs.ActionRotationFrame:setRotation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionRotationFrame::*)(float)>(&cocostudio::ActionRotationFrame::setRotation));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionRotationFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionRotationFrame, "ActionRotationFrame", "ccs.ActionRotationFrame",
		cocostudio::ActionFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getRotation", lua_cocostudio_ActionRotationFrame_getRotation);
	LUA_METHOD("setRotation", lua_cocostudio_ActionRotationFrame_setRotation);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionFadeFrame_getOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFadeFrame", "ccs.ActionFadeFrame:getOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ActionFadeFrame::*)()>(&cocostudio::ActionFadeFrame::getOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionFadeFrame_setOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFadeFrame", "ccs.ActionFadeFrame:setOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFadeFrame::*)(int)>(&cocostudio::ActionFadeFrame::setOpacity));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionFadeFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionFadeFrame, "ActionFadeFrame", "ccs.ActionFadeFrame",
		cocostudio::ActionFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getOpacity", lua_cocostudio_ActionFadeFrame_getOpacity);
	LUA_METHOD("setOpacity", lua_cocostudio_ActionFadeFrame_setOpacity);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Studio_ccsActionTintFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionTintFrame, "ActionTintFrame", "ccs.ActionTintFrame",
		cocostudio::ActionFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionObject_addActionNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:addActionNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(cocostudio::ActionNode*)>(&cocostudio::ActionObject::addActionNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_getCurrentTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:getCurrentTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::getCurrentTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_getLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:getLoop");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::getLoop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:getName");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_getTotalTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:getTotalTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::getTotalTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_getUnitTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:getUnitTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::getUnitTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_isPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:isPlaying");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::isPlaying));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:pause");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::pause));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:play");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(cocos2d::CallFunc*)>(&cocostudio::ActionObject::play));
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::play));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocostudio_ActionObject_removeActionNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:removeActionNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(cocostudio::ActionNode*)>(&cocostudio::ActionObject::removeActionNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_setCurrentTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:setCurrentTime");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(float)>(&cocostudio::ActionObject::setCurrentTime));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_setLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:setLoop");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(bool)>(&cocostudio::ActionObject::setLoop));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(const char*)>(&cocostudio::ActionObject::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_setUnitTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:setUnitTime");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(float)>(&cocostudio::ActionObject::setUnitTime));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_simulationActionUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:simulationActionUpdate");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(float)>(&cocostudio::ActionObject::simulationActionUpdate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionObject_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ActionObject::*)()>(&cocostudio::ActionObject::stop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionObject_updateToFrameByTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionObject", "ccs.ActionObject:updateToFrameByTime");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionObject::*)(float)>(&cocostudio::ActionObject::updateToFrameByTime));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionObject(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionObject, "ActionObject", "ccs.ActionObject",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addActionNode", lua_cocostudio_ActionObject_addActionNode);
	LUA_METHOD("getCurrentTime", lua_cocostudio_ActionObject_getCurrentTime);
	LUA_METHOD("getLoop", lua_cocostudio_ActionObject_getLoop);
	LUA_METHOD("getName", lua_cocostudio_ActionObject_getName);
	LUA_METHOD("getTotalTime", lua_cocostudio_ActionObject_getTotalTime);
	LUA_METHOD("getUnitTime", lua_cocostudio_ActionObject_getUnitTime);
	LUA_METHOD("isPlaying", lua_cocostudio_ActionObject_isPlaying);
	LUA_METHOD("pause", lua_cocostudio_ActionObject_pause);
	LUA_METHOD("play", lua_cocostudio_ActionObject_play);
	LUA_METHOD("removeActionNode", lua_cocostudio_ActionObject_removeActionNode);
	LUA_METHOD("setCurrentTime", lua_cocostudio_ActionObject_setCurrentTime);
	LUA_METHOD("setLoop", lua_cocostudio_ActionObject_setLoop);
	LUA_METHOD("setName", lua_cocostudio_ActionObject_setName);
	LUA_METHOD("setUnitTime", lua_cocostudio_ActionObject_setUnitTime);
	LUA_METHOD("simulationActionUpdate", lua_cocostudio_ActionObject_simulationActionUpdate);
	LUA_METHOD("stop", lua_cocostudio_ActionObject_stop);
	LUA_METHOD("updateToFrameByTime", lua_cocostudio_ActionObject_updateToFrameByTime);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionManagerEx_getActionByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:getActionByName");
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::getActionByName));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ActionManagerEx_getStudioVersionNumber(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:getStudioVersionNumber");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ActionManagerEx::*)()const>(&cocostudio::ActionManagerEx::getStudioVersionNumber));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionManagerEx_playActionByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:playActionByName");
	LUA_TRY_INVOKE_R(3, static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*, cocos2d::CallFunc*)>(&cocostudio::ActionManagerEx::playActionByName));
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::playActionByName));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_ActionManagerEx_releaseActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:releaseActions");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ActionManagerEx::*)()>(&cocostudio::ActionManagerEx::releaseActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionManagerEx_stopActionByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:stopActionByName");
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::stopActionByName));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Studio_ccsActionManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionManagerEx, "ActionManagerEx", "ccs.ActionManagerEx",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActionByName", lua_cocostudio_ActionManagerEx_getActionByName);
	LUA_METHOD("getStudioVersionNumber", lua_cocostudio_ActionManagerEx_getStudioVersionNumber);
	LUA_METHOD("playActionByName", lua_cocostudio_ActionManagerEx_playActionByName);
	LUA_METHOD("releaseActions", lua_cocostudio_ActionManagerEx_releaseActions);
	LUA_METHOD("stopActionByName", lua_cocostudio_ActionManagerEx_stopActionByName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
extern int luaReg_Studio_ccsActionFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionMoveFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionScaleFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionRotationFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionFadeFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionTintFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsActionObject(lua_State* lua_S);
extern int luaReg_Studio_ccsActionManagerEx(lua_State* lua_S);
extern int luaReg_Studio_ccsBaseData(lua_State* lua_S);
extern int luaReg_Studio_ccsDisplayData(lua_State* lua_S);
extern int luaReg_Studio_ccsSpriteDisplayData(lua_State* lua_S);
extern int luaReg_Studio_ccsArmatureDisplayData(lua_State* lua_S);
extern int luaReg_Studio_ccsParticleDisplayData(lua_State* lua_S);
extern int luaReg_Studio_ccsBoneData(lua_State* lua_S);
extern int luaReg_Studio_ccsArmatureData(lua_State* lua_S);
extern int luaReg_Studio_ccsFrameData(lua_State* lua_S);
extern int luaReg_Studio_ccsMovementBoneData(lua_State* lua_S);
extern int luaReg_Studio_ccsMovementData(lua_State* lua_S);
extern int luaReg_Studio_ccsAnimationData(lua_State* lua_S);
extern int luaReg_Studio_ccsContourData(lua_State* lua_S);
extern int luaReg_Studio_ccsTextureData(lua_State* lua_S);
extern int luaReg_Studio_ccsTween(lua_State* lua_S);
extern int luaReg_Studio_ccsDisplayManager(lua_State* lua_S);
extern int luaReg_Studio_ccsBone(lua_State* lua_S);
extern int luaReg_Studio_ccsBatchNode(lua_State* lua_S);
extern int luaReg_Studio_ccsArmatureAnimation(lua_State* lua_S);
extern int luaReg_Studio_ccsArmatureDataManager(lua_State* lua_S);
extern int luaReg_Studio_ccsArmature(lua_State* lua_S);
extern int luaReg_Studio_ccsSkin(lua_State* lua_S);
extern int luaReg_Studio_ccsComAttribute(lua_State* lua_S);
extern int luaReg_Studio_ccsComAudio(lua_State* lua_S);
extern int luaReg_Studio_ccsComController(lua_State* lua_S);
extern int luaReg_Studio_ccsComRender(lua_State* lua_S);
extern int luaReg_Studio_ccsGUIReader(lua_State* lua_S);
extern int luaReg_Studio_ccsSceneReader(lua_State* lua_S);
extern int luaReg_Studio_ccsActionTimelineCache(lua_State* lua_S);
extern int luaReg_Studio_ccsFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsVisibleFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsTextureFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsRotationFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsSkewFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsRotationSkewFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsPositionFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsScaleFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsAnchorPointFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsInnerActionFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsColorFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsAlphaFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsEventFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsZOrderFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsBlendFuncFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsPlayableFrame(lua_State* lua_S);
extern int luaReg_Studio_ccsTimeline(lua_State* lua_S);
extern int luaReg_Studio_ccsActionTimelineData(lua_State* lua_S);
extern int luaReg_Studio_ccsActionTimeline(lua_State* lua_S);
extern int luaReg_Studio_ccsActionTimelineNode(lua_State* lua_S);
extern int luaReg_Studio_ccsBoneNode(lua_State* lua_S);
extern int luaReg_Studio_ccsSkeletonNode(lua_State* lua_S);
extern int luaReg_Studio_ccsComExtensionData(lua_State* lua_S);

int register_all_cc_studio(lua_State* lua_S)
{
	luaReg_Studio_ccsActionFrame(lua_S);
	luaReg_Studio_ccsActionMoveFrame(lua_S);
	luaReg_Studio_ccsActionScaleFrame(lua_S);
	luaReg_Studio_ccsActionRotationFrame(lua_S);
	luaReg_Studio_ccsActionFadeFrame(lua_S);
	luaReg_Studio_ccsActionTintFrame(lua_S);
	luaReg_Studio_ccsActionObject(lua_S);
	luaReg_Studio_ccsActionManagerEx(lua_S);
	luaReg_Studio_ccsBaseData(lua_S);
	luaReg_Studio_ccsDisplayData(lua_S);
	luaReg_Studio_ccsSpriteDisplayData(lua_S);
	luaReg_Studio_ccsArmatureDisplayData(lua_S);
	luaReg_Studio_ccsParticleDisplayData(lua_S);
	luaReg_Studio_ccsBoneData(lua_S);
	luaReg_Studio_ccsArmatureData(lua_S);
	luaReg_Studio_ccsFrameData(lua_S);
	luaReg_Studio_ccsMovementBoneData(lua_S);
	luaReg_Studio_ccsMovementData(lua_S);
	luaReg_Studio_ccsAnimationData(lua_S);
	luaReg_Studio_ccsContourData(lua_S);
	luaReg_Studio_ccsTextureData(lua_S);
	luaReg_Studio_ccsTween(lua_S);
	luaReg_Studio_ccsDisplayManager(lua_S);
	luaReg_Studio_ccsBone(lua_S);
	luaReg_Studio_ccsBatchNode(lua_S);
	luaReg_Studio_ccsArmatureAnimation(lua_S);
	luaReg_Studio_ccsArmatureDataManager(lua_S);
	luaReg_Studio_ccsArmature(lua_S);
	luaReg_Studio_ccsSkin(lua_S);
	luaReg_Studio_ccsComAttribute(lua_S);
	luaReg_Studio_ccsComAudio(lua_S);
	luaReg_Studio_ccsComController(lua_S);
	luaReg_Studio_ccsComRender(lua_S);
	luaReg_Studio_ccsGUIReader(lua_S);
	luaReg_Studio_ccsSceneReader(lua_S);
	luaReg_Studio_ccsActionTimelineCache(lua_S);
	luaReg_Studio_ccsFrame(lua_S);
	luaReg_Studio_ccsVisibleFrame(lua_S);
	luaReg_Studio_ccsTextureFrame(lua_S);
	luaReg_Studio_ccsRotationFrame(lua_S);
	luaReg_Studio_ccsSkewFrame(lua_S);
	luaReg_Studio_ccsRotationSkewFrame(lua_S);
	luaReg_Studio_ccsPositionFrame(lua_S);
	luaReg_Studio_ccsScaleFrame(lua_S);
	luaReg_Studio_ccsAnchorPointFrame(lua_S);
	luaReg_Studio_ccsInnerActionFrame(lua_S);
	luaReg_Studio_ccsColorFrame(lua_S);
	luaReg_Studio_ccsAlphaFrame(lua_S);
	luaReg_Studio_ccsEventFrame(lua_S);
	luaReg_Studio_ccsZOrderFrame(lua_S);
	luaReg_Studio_ccsBlendFuncFrame(lua_S);
	luaReg_Studio_ccsPlayableFrame(lua_S);
	luaReg_Studio_ccsTimeline(lua_S);
	luaReg_Studio_ccsActionTimelineData(lua_S);
	luaReg_Studio_ccsActionTimeline(lua_S);
	luaReg_Studio_ccsActionTimelineNode(lua_S);
	luaReg_Studio_ccsBoneNode(lua_S);
	luaReg_Studio_ccsSkeletonNode(lua_S);
	luaReg_Studio_ccsComExtensionData(lua_S);
	return register_all_cc_studio_retained(lua_S);
}
