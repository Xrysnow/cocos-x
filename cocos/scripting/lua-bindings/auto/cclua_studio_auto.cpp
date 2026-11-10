#include "cclua_studio_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_ActionFrame_getAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:getAction");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ActionInterval*(cocostudio::ActionFrame::*)(float, cocostudio::ActionFrame*)>(&cocostudio::ActionFrame::getAction)));
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
int lua_cocostudio_ActionFrame_setEasingParameter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFrame", "ccs.ActionFrame:setEasingParameter");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionFrame::*)(std::vector<float>&)>(&cocostudio::ActionFrame::setEasingParameter));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::ActionFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionFrame_getAction);
	LUA_METHOD("getEasingType", lua_cocostudio_ActionFrame_getEasingType);
	LUA_METHOD("getFrameIndex", lua_cocostudio_ActionFrame_getFrameIndex);
	LUA_METHOD("getFrameTime", lua_cocostudio_ActionFrame_getFrameTime);
	LUA_METHOD("getFrameType", lua_cocostudio_ActionFrame_getFrameType);
	LUA_METHOD("setEasingParameter", lua_cocostudio_ActionFrame_setEasingParameter);
	LUA_METHOD("setEasingType", lua_cocostudio_ActionFrame_setEasingType);
	LUA_METHOD("setFrameIndex", lua_cocostudio_ActionFrame_setFrameIndex);
	LUA_METHOD("setFrameTime", lua_cocostudio_ActionFrame_setFrameTime);
	LUA_METHOD("setFrameType", lua_cocostudio_ActionFrame_setFrameType);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionMoveFrame_getAction_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionMoveFrame", "ccs.ActionMoveFrame:getAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionMoveFrame::*)(float)>(&cocostudio::ActionMoveFrame::getAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionMoveFrame_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionMoveFrame", "ccs.ActionMoveFrame:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocostudio::ActionMoveFrame::*)()>(&cocostudio::ActionMoveFrame::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionMoveFrame_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionMoveFrame", "ccs.ActionMoveFrame:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionMoveFrame::*)(cocos2d::Vec2)>(&cocostudio::ActionMoveFrame::setPosition));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionMoveFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionMoveFrame, "ActionMoveFrame", "ccs.ActionMoveFrame",
		cocostudio::ActionMoveFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionMoveFrame_getAction_1);
	LUA_METHOD("getPosition", lua_cocostudio_ActionMoveFrame_getPosition);
	LUA_METHOD("setPosition", lua_cocostudio_ActionMoveFrame_setPosition);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionScaleFrame_getAction_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionScaleFrame", "ccs.ActionScaleFrame:getAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionScaleFrame::*)(float)>(&cocostudio::ActionScaleFrame::getAction));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::ActionScaleFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionScaleFrame_getAction_1);
	LUA_METHOD("getScaleX", lua_cocostudio_ActionScaleFrame_getScaleX);
	LUA_METHOD("getScaleY", lua_cocostudio_ActionScaleFrame_getScaleY);
	LUA_METHOD("setScaleX", lua_cocostudio_ActionScaleFrame_setScaleX);
	LUA_METHOD("setScaleY", lua_cocostudio_ActionScaleFrame_setScaleY);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionRotationFrame_getAction_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionRotationFrame", "ccs.ActionRotationFrame:getAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionRotationFrame::*)(float)>(&cocostudio::ActionRotationFrame::getAction));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ActionInterval*(cocostudio::ActionRotationFrame::*)(float, cocostudio::ActionFrame*)>(&cocostudio::ActionRotationFrame::getAction)));
	LUA_INVOKE_FOOTER("1,2");
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
		cocostudio::ActionRotationFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionRotationFrame_getAction_1);
	LUA_METHOD("getRotation", lua_cocostudio_ActionRotationFrame_getRotation);
	LUA_METHOD("setRotation", lua_cocostudio_ActionRotationFrame_setRotation);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionFadeFrame_getAction_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionFadeFrame", "ccs.ActionFadeFrame:getAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionFadeFrame::*)(float)>(&cocostudio::ActionFadeFrame::getAction));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::ActionFadeFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionFadeFrame_getAction_1);
	LUA_METHOD("getOpacity", lua_cocostudio_ActionFadeFrame_getOpacity);
	LUA_METHOD("setOpacity", lua_cocostudio_ActionFadeFrame_setOpacity);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ActionTintFrame_getAction_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTintFrame", "ccs.ActionTintFrame:getAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocostudio::ActionTintFrame::*)(float)>(&cocostudio::ActionTintFrame::getAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ActionTintFrame_getColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTintFrame", "ccs.ActionTintFrame:getColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocostudio::ActionTintFrame::*)()>(&cocostudio::ActionTintFrame::getColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ActionTintFrame_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTintFrame", "ccs.ActionTintFrame:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ActionTintFrame::*)(cocos2d::Color3B)>(&cocostudio::ActionTintFrame::setColor));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionTintFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionTintFrame, "ActionTintFrame", "ccs.ActionTintFrame",
		cocostudio::ActionTintFrame, "ccs.ActionFrame",
		nullptr, nullptr);
	LUA_METHOD("getAction", lua_cocostudio_ActionTintFrame_getAction_1);
	LUA_METHOD("getColor", lua_cocostudio_ActionTintFrame_getColor);
	LUA_METHOD("setColor", lua_cocostudio_ActionTintFrame_setColor);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
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
		cocostudio::ActionObject, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentTime", lua_cocostudio_ActionObject_getCurrentTime);
	LUA_METHOD("getLoop", lua_cocostudio_ActionObject_getLoop);
	LUA_METHOD("getName", lua_cocostudio_ActionObject_getName);
	LUA_METHOD("getTotalTime", lua_cocostudio_ActionObject_getTotalTime);
	LUA_METHOD("getUnitTime", lua_cocostudio_ActionObject_getUnitTime);
	LUA_METHOD("isPlaying", lua_cocostudio_ActionObject_isPlaying);
	LUA_METHOD("pause", lua_cocostudio_ActionObject_pause);
	LUA_METHOD("play", lua_cocostudio_ActionObject_play);
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::getActionByName)));
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
	LUA_TRY_INVOKE_R(3, (static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*, cocos2d::CallFunc*)>(&cocostudio::ActionManagerEx::playActionByName)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::playActionByName)));
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::ActionObject*(cocostudio::ActionManagerEx::*)(const char*, const char*)>(&cocostudio::ActionManagerEx::stopActionByName)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ActionManagerEx_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionManagerEx", "ccs.ActionManagerEx:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ActionManagerEx*(*)()>(&cocostudio::ActionManagerEx::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsActionManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ActionManagerEx, "ActionManagerEx", "ccs.ActionManagerEx",
		cocostudio::ActionManagerEx, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActionByName", lua_cocostudio_ActionManagerEx_getActionByName);
	LUA_METHOD("getStudioVersionNumber", lua_cocostudio_ActionManagerEx_getStudioVersionNumber);
	LUA_METHOD("playActionByName", lua_cocostudio_ActionManagerEx_playActionByName);
	LUA_METHOD("releaseActions", lua_cocostudio_ActionManagerEx_releaseActions);
	LUA_METHOD("stopActionByName", lua_cocostudio_ActionManagerEx_stopActionByName);
	LUA_METHOD("getInstance", lua_cocostudio_ActionManagerEx_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_BaseData_a_getter(lua_State* lua_S)
{
	LUA_CUR_FNAME("ccs.BaseData.a/getter");
	auto cobj = LUA_TO_COBJ(cocostudio::BaseData*, 1);
	LUA_PUSH_NATIVE(cobj->a);
	return 1;
}
int lua_cocostudio_BaseData_a_setter(lua_State* lua_S)
{
	LUA_CUR_FNAME("ccs.BaseData.a/setter");
	auto cobj = LUA_TO_COBJ(cocostudio::BaseData*, 1);
	LUA_NATIVE_SETTER(cobj->a, 2);
	return 0;
}
int lua_cocostudio_BaseData_getColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BaseData", "ccs.BaseData:getColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color4B(cocostudio::BaseData::*)()>(&cocostudio::BaseData::getColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_BaseData_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BaseData", "ccs.BaseData:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::BaseData::*)(const cocos2d::Color4B&)>(&cocostudio::BaseData::setColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_BaseData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BaseData", "ccs.BaseData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BaseData*(*)()>(&cocostudio::BaseData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBaseData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BaseData, "BaseData", "ccs.BaseData",
		cocostudio::BaseData, "cc.Ref",
		nullptr, nullptr);
	LUA_FIELD("a", lua_cocostudio_BaseData_a_getter, lua_cocostudio_BaseData_a_setter);
	LUA_METHOD("getColor", lua_cocostudio_BaseData_getColor);
	LUA_METHOD("setColor", lua_cocostudio_BaseData_setColor);
	LUA_METHOD("create", lua_cocostudio_BaseData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_DisplayData_copy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayData", "ccs.DisplayData:copy");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayData::*)(cocostudio::DisplayData*)>(&cocostudio::DisplayData::copy));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayData_changeDisplayToTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.DisplayData", "ccs.DisplayData:changeDisplayToTexture");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(*)(std::string_view)>(&cocostudio::DisplayData::changeDisplayToTexture));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.DisplayData", "ccs.DisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayData*(*)()>(&cocostudio::DisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::DisplayData, "DisplayData", "ccs.DisplayData",
		cocostudio::DisplayData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("copy", lua_cocostudio_DisplayData_copy);
	LUA_METHOD("changeDisplayToTexture", lua_cocostudio_DisplayData_changeDisplayToTexture);
	LUA_METHOD("create", lua_cocostudio_DisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_SpriteDisplayData_copy_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SpriteDisplayData", "ccs.SpriteDisplayData:copy");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::SpriteDisplayData::*)(cocostudio::DisplayData*)>(&cocostudio::SpriteDisplayData::copy));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_SpriteDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SpriteDisplayData", "ccs.SpriteDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::SpriteDisplayData*(*)()>(&cocostudio::SpriteDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSpriteDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::SpriteDisplayData, "SpriteDisplayData", "ccs.SpriteDisplayData",
		cocostudio::SpriteDisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("copy", lua_cocostudio_SpriteDisplayData_copy_1);
	LUA_METHOD("create", lua_cocostudio_SpriteDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureDisplayData", "ccs.ArmatureDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureDisplayData*(*)()>(&cocostudio::ArmatureDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureDisplayData, "ArmatureDisplayData", "ccs.ArmatureDisplayData",
		cocostudio::ArmatureDisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ArmatureDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ParticleDisplayData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ParticleDisplayData", "ccs.ParticleDisplayData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ParticleDisplayData*(*)()>(&cocostudio::ParticleDisplayData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsParticleDisplayData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ParticleDisplayData, "ParticleDisplayData", "ccs.ParticleDisplayData",
		cocostudio::ParticleDisplayData, "ccs.DisplayData",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ParticleDisplayData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_BoneData_addDisplayData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:addDisplayData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::BoneData::*)(cocostudio::DisplayData*)>(&cocostudio::BoneData::addDisplayData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_BoneData_getDisplayData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:getDisplayData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::DisplayData*(cocostudio::BoneData::*)(int)>(&cocostudio::BoneData::getDisplayData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_BoneData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneData", "ccs.BoneData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::BoneData::*)()>(&cocostudio::BoneData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_BoneData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BoneData", "ccs.BoneData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BoneData*(*)()>(&cocostudio::BoneData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBoneData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BoneData, "BoneData", "ccs.BoneData",
		cocostudio::BoneData, "ccs.BaseData",
		nullptr, nullptr);
	LUA_METHOD("addDisplayData", lua_cocostudio_BoneData_addDisplayData);
	LUA_METHOD("getDisplayData", lua_cocostudio_BoneData_getDisplayData);
	LUA_METHOD("init", lua_cocostudio_BoneData_init);
	LUA_METHOD("create", lua_cocostudio_BoneData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureData_addBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:addBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureData::*)(cocostudio::BoneData*)>(&cocostudio::ArmatureData::addBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureData_getBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:getBoneData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::BoneData*(cocostudio::ArmatureData::*)(std::string_view)>(&cocostudio::ArmatureData::getBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureData::*)()>(&cocostudio::ArmatureData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureData", "ccs.ArmatureData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureData*(*)()>(&cocostudio::ArmatureData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureData, "ArmatureData", "ccs.ArmatureData",
		cocostudio::ArmatureData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addBoneData", lua_cocostudio_ArmatureData_addBoneData);
	LUA_METHOD("getBoneData", lua_cocostudio_ArmatureData_getBoneData);
	LUA_METHOD("init", lua_cocostudio_ArmatureData_init);
	LUA_METHOD("create", lua_cocostudio_ArmatureData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_FrameData_copy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.FrameData", "ccs.FrameData:copy");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::FrameData::*)(const cocostudio::BaseData*)>(&cocostudio::FrameData::copy));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_FrameData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.FrameData", "ccs.FrameData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::FrameData*(*)()>(&cocostudio::FrameData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsFrameData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::FrameData, "FrameData", "ccs.FrameData",
		cocostudio::FrameData, "ccs.BaseData",
		nullptr, nullptr);
	LUA_METHOD("copy", lua_cocostudio_FrameData_copy);
	LUA_METHOD("create", lua_cocostudio_FrameData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_MovementBoneData_addFrameData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:addFrameData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::MovementBoneData::*)(cocostudio::FrameData*)>(&cocostudio::MovementBoneData::addFrameData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementBoneData_getFrameData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:getFrameData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::FrameData*(cocostudio::MovementBoneData::*)(int)>(&cocostudio::MovementBoneData::getFrameData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementBoneData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::MovementBoneData::*)()>(&cocostudio::MovementBoneData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_MovementBoneData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::MovementBoneData*(*)()>(&cocostudio::MovementBoneData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsMovementBoneData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::MovementBoneData, "MovementBoneData", "ccs.MovementBoneData",
		cocostudio::MovementBoneData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addFrameData", lua_cocostudio_MovementBoneData_addFrameData);
	LUA_METHOD("getFrameData", lua_cocostudio_MovementBoneData_getFrameData);
	LUA_METHOD("init", lua_cocostudio_MovementBoneData_init);
	LUA_METHOD("create", lua_cocostudio_MovementBoneData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_MovementData_addMovementBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementData", "ccs.MovementData:addMovementBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::MovementData::*)(cocostudio::MovementBoneData*)>(&cocostudio::MovementData::addMovementBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementData_getMovementBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementData", "ccs.MovementData:getMovementBoneData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::MovementBoneData*(cocostudio::MovementData::*)(std::string_view)>(&cocostudio::MovementData::getMovementBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.MovementData", "ccs.MovementData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::MovementData*(*)()>(&cocostudio::MovementData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsMovementData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::MovementData, "MovementData", "ccs.MovementData",
		cocostudio::MovementData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addMovementBoneData", lua_cocostudio_MovementData_addMovementBoneData);
	LUA_METHOD("getMovementBoneData", lua_cocostudio_MovementData_getMovementBoneData);
	LUA_METHOD("create", lua_cocostudio_MovementData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_AnimationData_addMovement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:addMovement");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::AnimationData::*)(cocostudio::MovementData*)>(&cocostudio::AnimationData::addMovement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_AnimationData_getMovement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:getMovement");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::MovementData*(cocostudio::AnimationData::*)(std::string_view)>(&cocostudio::AnimationData::getMovement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_AnimationData_getMovementCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:getMovementCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocostudio::AnimationData::*)()>(&cocostudio::AnimationData::getMovementCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_AnimationData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::AnimationData*(*)()>(&cocostudio::AnimationData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsAnimationData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::AnimationData, "AnimationData", "ccs.AnimationData",
		cocostudio::AnimationData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addMovement", lua_cocostudio_AnimationData_addMovement);
	LUA_METHOD("getMovement", lua_cocostudio_AnimationData_getMovement);
	LUA_METHOD("getMovementCount", lua_cocostudio_AnimationData_getMovementCount);
	LUA_METHOD("create", lua_cocostudio_AnimationData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ContourData_addVertex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ContourData", "ccs.ContourData:addVertex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ContourData::*)(cocos2d::Vec2&)>(&cocostudio::ContourData::addVertex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ContourData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ContourData", "ccs.ContourData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ContourData::*)()>(&cocostudio::ContourData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ContourData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ContourData", "ccs.ContourData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ContourData*(*)()>(&cocostudio::ContourData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsContourData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ContourData, "ContourData", "ccs.ContourData",
		cocostudio::ContourData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addVertex", lua_cocostudio_ContourData_addVertex);
	LUA_METHOD("init", lua_cocostudio_ContourData_init);
	LUA_METHOD("create", lua_cocostudio_ContourData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_TextureData_addContourData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:addContourData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::TextureData::*)(cocostudio::ContourData*)>(&cocostudio::TextureData::addContourData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_TextureData_getContourData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:getContourData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::ContourData*(cocostudio::TextureData::*)(int)>(&cocostudio::TextureData::getContourData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_TextureData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::TextureData::*)()>(&cocostudio::TextureData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_TextureData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.TextureData", "ccs.TextureData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::TextureData*(*)()>(&cocostudio::TextureData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsTextureData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::TextureData, "TextureData", "ccs.TextureData",
		cocostudio::TextureData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addContourData", lua_cocostudio_TextureData_addContourData);
	LUA_METHOD("getContourData", lua_cocostudio_TextureData_getContourData);
	LUA_METHOD("init", lua_cocostudio_TextureData_init);
	LUA_METHOD("create", lua_cocostudio_TextureData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Tween_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:getAnimation");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureAnimation*(cocostudio::Tween::*)()const>(&cocostudio::Tween::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Tween_gotoAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:gotoAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(int)>(&cocostudio::Tween::gotoAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_gotoAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:gotoAndPlay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(int)>(&cocostudio::Tween::gotoAndPlay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::Tween::*)(cocostudio::Bone*)>(&cocostudio::Tween::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_play_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:play");
	LUA_TRY_INVOKE(5, (static_cast<void(cocostudio::Tween::*)(cocostudio::MovementBoneData*, int, int, int, int)>(&cocostudio::Tween::play)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocostudio_Tween_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(cocostudio::ArmatureAnimation*)>(&cocostudio::Tween::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Tween", "ccs.Tween:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Tween*(*)(cocostudio::Bone*)>(&cocostudio::Tween::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsTween(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Tween, "Tween", "ccs.Tween",
		cocostudio::Tween, "ccs.ProcessBase",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocostudio_Tween_getAnimation);
	LUA_METHOD("gotoAndPause", lua_cocostudio_Tween_gotoAndPause);
	LUA_METHOD("gotoAndPlay", lua_cocostudio_Tween_gotoAndPlay);
	LUA_METHOD("init", lua_cocostudio_Tween_init);
	LUA_METHOD("play", lua_cocostudio_Tween_play_1);
	LUA_METHOD("setAnimation", lua_cocostudio_Tween_setAnimation);
	LUA_METHOD("create", lua_cocostudio_Tween_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_DisplayManager_addDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:addDisplay");
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::DisplayManager::*)(cocos2d::Node*, int)>(&cocostudio::DisplayManager::addDisplay)));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::DisplayManager::*)(cocostudio::DisplayData*, int)>(&cocostudio::DisplayManager::addDisplay)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_DisplayManager_changeDisplayWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:changeDisplayWithIndex");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::DisplayManager::*)(int, bool)>(&cocostudio::DisplayManager::changeDisplayWithIndex)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_DisplayManager_changeDisplayWithName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:changeDisplayWithName");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::DisplayManager::*)(std::string_view, bool)>(&cocostudio::DisplayManager::changeDisplayWithName)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_DisplayManager_containPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:containPoint");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocostudio::DisplayManager::*)(float, float)>(&cocostudio::DisplayManager::containPoint)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::DisplayManager::*)(cocos2d::Vec2&)>(&cocostudio::DisplayManager::containPoint));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_DisplayManager_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getAnchorPointInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getAnchorPointInPoints");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getAnchorPointInPoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getBoundingBox(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getBoundingBox");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getBoundingBox));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getContentSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Size(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getContentSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getCurrentDisplayIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getCurrentDisplayIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getCurrentDisplayIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getDisplayRenderNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getDisplayRenderNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getDisplayRenderNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getDisplayRenderNodeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getDisplayRenderNodeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayType(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getDisplayRenderNodeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::DisplayManager::*)(cocostudio::Bone*)>(&cocostudio::DisplayManager::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_isForceChangeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:isForceChangeDisplay");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::isForceChangeDisplay));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:isVisible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::isVisible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_removeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:removeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(int)>(&cocostudio::DisplayManager::removeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_setForceChangeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:setForceChangeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(bool)>(&cocostudio::DisplayManager::setForceChangeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:setVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(bool)>(&cocostudio::DisplayManager::setVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::DisplayManager*(*)(cocostudio::Bone*)>(&cocostudio::DisplayManager::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsDisplayManager(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::DisplayManager, "DisplayManager", "ccs.DisplayManager",
		cocostudio::DisplayManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addDisplay", lua_cocostudio_DisplayManager_addDisplay);
	LUA_METHOD("changeDisplayWithIndex", lua_cocostudio_DisplayManager_changeDisplayWithIndex);
	LUA_METHOD("changeDisplayWithName", lua_cocostudio_DisplayManager_changeDisplayWithName);
	LUA_METHOD("containPoint", lua_cocostudio_DisplayManager_containPoint);
	LUA_METHOD("getAnchorPoint", lua_cocostudio_DisplayManager_getAnchorPoint);
	LUA_METHOD("getAnchorPointInPoints", lua_cocostudio_DisplayManager_getAnchorPointInPoints);
	LUA_METHOD("getBoundingBox", lua_cocostudio_DisplayManager_getBoundingBox);
	LUA_METHOD("getContentSize", lua_cocostudio_DisplayManager_getContentSize);
	LUA_METHOD("getCurrentDisplayIndex", lua_cocostudio_DisplayManager_getCurrentDisplayIndex);
	LUA_METHOD("getDisplayRenderNode", lua_cocostudio_DisplayManager_getDisplayRenderNode);
	LUA_METHOD("getDisplayRenderNodeType", lua_cocostudio_DisplayManager_getDisplayRenderNodeType);
	LUA_METHOD("init", lua_cocostudio_DisplayManager_init);
	LUA_METHOD("isForceChangeDisplay", lua_cocostudio_DisplayManager_isForceChangeDisplay);
	LUA_METHOD("isVisible", lua_cocostudio_DisplayManager_isVisible);
	LUA_METHOD("removeDisplay", lua_cocostudio_DisplayManager_removeDisplay);
	LUA_METHOD("setForceChangeDisplay", lua_cocostudio_DisplayManager_setForceChangeDisplay);
	LUA_METHOD("setVisible", lua_cocostudio_DisplayManager_setVisible);
	LUA_METHOD("create", lua_cocostudio_DisplayManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Bone_addChildBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:addChildBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*)>(&cocostudio::Bone::addChildBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_addDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:addDisplay");
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::Bone::*)(cocos2d::Node*, int)>(&cocostudio::Bone::addDisplay)));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::Bone::*)(cocostudio::DisplayData*, int)>(&cocostudio::Bone::addDisplay)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_changeDisplayWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:changeDisplayWithIndex");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Bone::*)(int, bool)>(&cocostudio::Bone::changeDisplayWithIndex)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_changeDisplayWithName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:changeDisplayWithName");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Bone::*)(std::string_view, bool)>(&cocostudio::Bone::changeDisplayWithName)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_getArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getArmature");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Armature*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getArmature));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::BlendFunc(cocostudio::Bone::*)()>(&cocostudio::Bone::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getBoneData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BoneData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getBoneData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getChildArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getChildArmature");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Armature*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getChildArmature));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayManager");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayManager*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getDisplayManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayRenderNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayRenderNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::Bone::*)()>(&cocostudio::Bone::getDisplayRenderNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayRenderNodeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayRenderNodeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayType(cocostudio::Bone::*)()>(&cocostudio::Bone::getDisplayRenderNodeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getIgnoreMovementBoneData_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getIgnoreMovementBoneData");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()const>(&cocostudio::Bone::isIgnoreMovementBoneData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getNodeToArmatureTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getNodeToArmatureTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocostudio::Bone::*)()const>(&cocostudio::Bone::getNodeToArmatureTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getParentBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Bone::*)()>(&cocostudio::Bone::getParentBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getTween(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getTween");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Tween*(cocostudio::Bone::*)()>(&cocostudio::Bone::getTween));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getTweenData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getTweenData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::FrameData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getTweenData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getWorldInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getWorldInfo");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BaseData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getWorldInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::Bone::*)(std::string_view)>(&cocostudio::Bone::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_isBlendDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isBlendDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()>(&cocostudio::Bone::isBlendDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_isIgnoreMovementBoneData_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isIgnoreMovementBoneData");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()const>(&cocostudio::Bone::isIgnoreMovementBoneData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_isTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isTransformDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()>(&cocostudio::Bone::isTransformDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_removeChildBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:removeChildBone");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*, bool)>(&cocostudio::Bone::removeChildBone)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_removeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:removeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(int)>(&cocostudio::Bone::removeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_removeFromParent_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:removeFromParent");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::removeFromParent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setArmature");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Armature*)>(&cocostudio::Bone::setArmature));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setBlendDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setBlendDirty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::setBlendDirty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(const cocos2d::BlendFunc&)>(&cocostudio::Bone::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::BoneData*)>(&cocostudio::Bone::setBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setChildArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setChildArmature");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Armature*)>(&cocostudio::Bone::setChildArmature));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setIgnoreMovementBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setIgnoreMovementBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::setIgnoreMovementBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setParentBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*)>(&cocostudio::Bone::setParentBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setTransformDirty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::setTransformDirty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_updateColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:updateColor");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Bone::*)()>(&cocostudio::Bone::updateColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_updateZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:updateZOrder");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Bone::*)()>(&cocostudio::Bone::updateZOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Bone", "ccs.Bone:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Bone*(*)(std::string_view)>(&cocostudio::Bone::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(*)()>(&cocostudio::Bone::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Studio_ccsBone(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Bone, "Bone", "ccs.Bone",
		cocostudio::Bone, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addChildBone", lua_cocostudio_Bone_addChildBone);
	LUA_METHOD("addDisplay", lua_cocostudio_Bone_addDisplay);
	LUA_METHOD("changeDisplayWithIndex", lua_cocostudio_Bone_changeDisplayWithIndex);
	LUA_METHOD("changeDisplayWithName", lua_cocostudio_Bone_changeDisplayWithName);
	LUA_METHOD("getArmature", lua_cocostudio_Bone_getArmature);
	LUA_METHOD("getBlendFunc", lua_cocostudio_Bone_getBlendFunc);
	LUA_METHOD("getBoneData", lua_cocostudio_Bone_getBoneData);
	LUA_METHOD("getChildArmature", lua_cocostudio_Bone_getChildArmature);
	LUA_METHOD("getDisplayManager", lua_cocostudio_Bone_getDisplayManager);
	LUA_METHOD("getDisplayRenderNode", lua_cocostudio_Bone_getDisplayRenderNode);
	LUA_METHOD("getDisplayRenderNodeType", lua_cocostudio_Bone_getDisplayRenderNodeType);
	LUA_METHOD("getIgnoreMovementBoneData", lua_cocostudio_Bone_getIgnoreMovementBoneData_1);
	LUA_METHOD("getNodeToArmatureTransform", lua_cocostudio_Bone_getNodeToArmatureTransform);
	LUA_METHOD("getParentBone", lua_cocostudio_Bone_getParentBone);
	LUA_METHOD("getTween", lua_cocostudio_Bone_getTween);
	LUA_METHOD("getTweenData", lua_cocostudio_Bone_getTweenData);
	LUA_METHOD("getWorldInfo", lua_cocostudio_Bone_getWorldInfo);
	LUA_METHOD("init", lua_cocostudio_Bone_init_1);
	LUA_METHOD("isBlendDirty", lua_cocostudio_Bone_isBlendDirty);
	LUA_METHOD("isIgnoreMovementBoneData", lua_cocostudio_Bone_isIgnoreMovementBoneData_1);
	LUA_METHOD("isTransformDirty", lua_cocostudio_Bone_isTransformDirty);
	LUA_METHOD("removeChildBone", lua_cocostudio_Bone_removeChildBone);
	LUA_METHOD("removeDisplay", lua_cocostudio_Bone_removeDisplay);
	LUA_METHOD("removeFromParent", lua_cocostudio_Bone_removeFromParent_1);
	LUA_METHOD("setArmature", lua_cocostudio_Bone_setArmature);
	LUA_METHOD("setBlendDirty", lua_cocostudio_Bone_setBlendDirty);
	LUA_METHOD("setBlendFunc", lua_cocostudio_Bone_setBlendFunc);
	LUA_METHOD("setBoneData", lua_cocostudio_Bone_setBoneData);
	LUA_METHOD("setChildArmature", lua_cocostudio_Bone_setChildArmature);
	LUA_METHOD("setIgnoreMovementBoneData", lua_cocostudio_Bone_setIgnoreMovementBoneData);
	LUA_METHOD("setParentBone", lua_cocostudio_Bone_setParentBone);
	LUA_METHOD("setTransformDirty", lua_cocostudio_Bone_setTransformDirty);
	LUA_METHOD("updateColor", lua_cocostudio_Bone_updateColor);
	LUA_METHOD("updateZOrder", lua_cocostudio_Bone_updateZOrder);
	LUA_METHOD("create", lua_cocostudio_Bone_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_BatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BatchNode", "ccs.BatchNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BatchNode*(*)()>(&cocostudio::BatchNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BatchNode, "BatchNode", "ccs.BatchNode",
		cocostudio::BatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_BatchNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureAnimation_getAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getAnimationData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::AnimationData*(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getAnimationData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getCurrentMovementID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getCurrentMovementID");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getCurrentMovementID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getMovementCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getMovementCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getMovementCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getSpeedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getSpeedScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getSpeedScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_gotoAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:gotoAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(int)>(&cocostudio::ArmatureAnimation::gotoAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_gotoAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:gotoAndPlay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(int)>(&cocostudio::ArmatureAnimation::gotoAndPlay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::ArmatureAnimation::*)(cocostudio::Armature*)>(&cocostudio::ArmatureAnimation::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_play_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:play");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureAnimation::*)(std::string_view, int, int)>(&cocostudio::ArmatureAnimation::play)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureAnimation* obj,std::string_view arg0,int arg1){{return obj->play(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocostudio::ArmatureAnimation* obj,std::string_view arg0){{return obj->play(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocostudio_ArmatureAnimation_playWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:playWithIndex");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureAnimation::*)(int, int, int)>(&cocostudio::ArmatureAnimation::playWithIndex)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureAnimation* obj,int arg0,int arg1){{return obj->playWithIndex(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocostudio::ArmatureAnimation* obj,int arg0){{return obj->playWithIndex(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocostudio_ArmatureAnimation_playWithIndexes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:playWithIndexes");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureAnimation::*)(const std::vector<int>&, int, bool)>(&cocostudio::ArmatureAnimation::playWithIndexes)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureAnimation* obj,const std::vector<int>& arg0,int arg1){{return obj->playWithIndexes(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocostudio::ArmatureAnimation* obj,const std::vector<int>& arg0){{return obj->playWithIndexes(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocostudio_ArmatureAnimation_playWithNames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:playWithNames");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureAnimation::*)(const std::vector<std::string>&, int, bool)>(&cocostudio::ArmatureAnimation::playWithNames)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureAnimation* obj,const std::vector<std::string>& arg0,int arg1){{return obj->playWithNames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocostudio::ArmatureAnimation* obj,const std::vector<std::string>& arg0){{return obj->playWithNames(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocostudio_ArmatureAnimation_setAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setAnimationData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(cocostudio::AnimationData*)>(&cocostudio::ArmatureAnimation::setAnimationData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setFrameEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setFrameEventCallFunc");
	LUA_TRY_INVOKE(1, (static_cast<void(cocostudio::ArmatureAnimation::*)(std::function<void(cocostudio::Bone*, std::string_view, int, int)>)>(&cocostudio::ArmatureAnimation::setFrameEventCallFunc)));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setMovementEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setMovementEventCallFunc");
	LUA_TRY_INVOKE(1, (static_cast<void(cocostudio::ArmatureAnimation::*)(std::function<void(cocostudio::Armature*, cocostudio::MovementEventType, std::string_view)>)>(&cocostudio::ArmatureAnimation::setMovementEventCallFunc)));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setSpeedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setSpeedScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(float)>(&cocostudio::ArmatureAnimation::setSpeedScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::ArmatureAnimation*(*)(cocostudio::Armature*)>(&cocostudio::ArmatureAnimation::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsArmatureAnimation(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureAnimation, "ArmatureAnimation", "ccs.ArmatureAnimation",
		cocostudio::ArmatureAnimation, "ccs.ProcessBase",
		nullptr, nullptr);
	LUA_METHOD("getAnimationData", lua_cocostudio_ArmatureAnimation_getAnimationData);
	LUA_METHOD("getCurrentMovementID", lua_cocostudio_ArmatureAnimation_getCurrentMovementID);
	LUA_METHOD("getMovementCount", lua_cocostudio_ArmatureAnimation_getMovementCount);
	LUA_METHOD("getSpeedScale", lua_cocostudio_ArmatureAnimation_getSpeedScale);
	LUA_METHOD("gotoAndPause", lua_cocostudio_ArmatureAnimation_gotoAndPause);
	LUA_METHOD("gotoAndPlay", lua_cocostudio_ArmatureAnimation_gotoAndPlay);
	LUA_METHOD("init", lua_cocostudio_ArmatureAnimation_init);
	LUA_METHOD("play", lua_cocostudio_ArmatureAnimation_play_1);
	LUA_METHOD("playWithIndex", lua_cocostudio_ArmatureAnimation_playWithIndex);
	LUA_METHOD("playWithIndexes", lua_cocostudio_ArmatureAnimation_playWithIndexes);
	LUA_METHOD("playWithNames", lua_cocostudio_ArmatureAnimation_playWithNames);
	LUA_METHOD("setAnimationData", lua_cocostudio_ArmatureAnimation_setAnimationData);
	LUA_METHOD("setFrameEventCallFunc", lua_cocostudio_ArmatureAnimation_setFrameEventCallFunc_1);
	LUA_METHOD("setMovementEventCallFunc", lua_cocostudio_ArmatureAnimation_setMovementEventCallFunc_1);
	LUA_METHOD("setSpeedScale", lua_cocostudio_ArmatureAnimation_setSpeedScale);
	LUA_METHOD("create", lua_cocostudio_ArmatureAnimation_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureDataManager_addAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addAnimationData");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view, cocostudio::AnimationData*, std::string_view)>(&cocostudio::ArmatureDataManager::addAnimationData)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureDataManager* obj,std::string_view arg0,cocostudio::AnimationData* arg1){{return obj->addAnimationData(std::move(arg0),arg1);}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_ArmatureDataManager_addArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addArmatureData");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view, cocostudio::ArmatureData*, std::string_view)>(&cocostudio::ArmatureDataManager::addArmatureData)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureDataManager* obj,std::string_view arg0,cocostudio::ArmatureData* arg1){{return obj->addArmatureData(std::move(arg0),arg1);}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_ArmatureDataManager_addArmatureFileInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addArmatureFileInfo");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view, std::string_view, std::string_view)>(&cocostudio::ArmatureDataManager::addArmatureFileInfo)));
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::addArmatureFileInfo));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cocostudio_ArmatureDataManager_addRelativeData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addRelativeData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::addRelativeData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_addSpriteFrameFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addSpriteFrameFromFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view, std::string_view, std::string_view)>(&cocostudio::ArmatureDataManager::addSpriteFrameFromFile)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureDataManager* obj,std::string_view arg0,std::string_view arg1){{return obj->addSpriteFrameFromFile(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_ArmatureDataManager_addTextureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:addTextureData");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view, cocostudio::TextureData*, std::string_view)>(&cocostudio::ArmatureDataManager::addTextureData)));
	LUA_TRY_INVOKE(2, ([](cocostudio::ArmatureDataManager* obj,std::string_view arg0,cocostudio::TextureData* arg1){{return obj->addTextureData(std::move(arg0),arg1);}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_ArmatureDataManager_getAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getAnimationData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::AnimationData*(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::getAnimationData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_getAnimationDatas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getAnimationDatas");
	LUA_TRY_INVOKE_R(0, (static_cast<const cocos2d::Map<std::string, cocostudio::AnimationData *, hlookup::string_hash, hlookup::equal_to>&(cocostudio::ArmatureDataManager::*)()const>(&cocostudio::ArmatureDataManager::getAnimationDatas)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_getArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getArmatureData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::ArmatureData*(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::getArmatureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_getArmatureDatas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getArmatureDatas");
	LUA_TRY_INVOKE_R(0, (static_cast<const cocos2d::Map<std::string, cocostudio::ArmatureData *, hlookup::string_hash, hlookup::equal_to>&(cocostudio::ArmatureDataManager::*)()const>(&cocostudio::ArmatureDataManager::getArmatureDatas)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_getTextureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getTextureData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::TextureData*(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::getTextureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_getTextureDatas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getTextureDatas");
	LUA_TRY_INVOKE_R(0, (static_cast<const cocos2d::Map<std::string, cocostudio::TextureData *, hlookup::string_hash, hlookup::equal_to>&(cocostudio::ArmatureDataManager::*)()const>(&cocostudio::ArmatureDataManager::getTextureDatas)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureDataManager::*)()>(&cocostudio::ArmatureDataManager::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_isAutoLoadSpriteFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:isAutoLoadSpriteFile");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureDataManager::*)()>(&cocostudio::ArmatureDataManager::isAutoLoadSpriteFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_removeAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:removeAnimationData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::removeAnimationData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_removeArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:removeArmatureData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::removeArmatureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_removeArmatureFileInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:removeArmatureFileInfo");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::removeArmatureFileInfo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_removeTextureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:removeTextureData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureDataManager::*)(std::string_view)>(&cocostudio::ArmatureDataManager::removeTextureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureDataManager_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureDataManager*(*)()>(&cocostudio::ArmatureDataManager::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureDataManager(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureDataManager, "ArmatureDataManager", "ccs.ArmatureDataManager",
		cocostudio::ArmatureDataManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAnimationData", lua_cocostudio_ArmatureDataManager_addAnimationData);
	LUA_METHOD("addArmatureData", lua_cocostudio_ArmatureDataManager_addArmatureData);
	LUA_METHOD("addArmatureFileInfo", lua_cocostudio_ArmatureDataManager_addArmatureFileInfo);
	LUA_METHOD("addRelativeData", lua_cocostudio_ArmatureDataManager_addRelativeData);
	LUA_METHOD("addSpriteFrameFromFile", lua_cocostudio_ArmatureDataManager_addSpriteFrameFromFile);
	LUA_METHOD("addTextureData", lua_cocostudio_ArmatureDataManager_addTextureData);
	LUA_METHOD("getAnimationData", lua_cocostudio_ArmatureDataManager_getAnimationData);
	LUA_METHOD("getAnimationDatas", lua_cocostudio_ArmatureDataManager_getAnimationDatas);
	LUA_METHOD("getArmatureData", lua_cocostudio_ArmatureDataManager_getArmatureData);
	LUA_METHOD("getArmatureDatas", lua_cocostudio_ArmatureDataManager_getArmatureDatas);
	LUA_METHOD("getTextureData", lua_cocostudio_ArmatureDataManager_getTextureData);
	LUA_METHOD("getTextureDatas", lua_cocostudio_ArmatureDataManager_getTextureDatas);
	LUA_METHOD("init", lua_cocostudio_ArmatureDataManager_init);
	LUA_METHOD("isAutoLoadSpriteFile", lua_cocostudio_ArmatureDataManager_isAutoLoadSpriteFile);
	LUA_METHOD("removeAnimationData", lua_cocostudio_ArmatureDataManager_removeAnimationData);
	LUA_METHOD("removeArmatureData", lua_cocostudio_ArmatureDataManager_removeArmatureData);
	LUA_METHOD("removeArmatureFileInfo", lua_cocostudio_ArmatureDataManager_removeArmatureFileInfo);
	LUA_METHOD("removeTextureData", lua_cocostudio_ArmatureDataManager_removeTextureData);
	LUA_METHOD("getInstance", lua_cocostudio_ArmatureDataManager_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Armature_addBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:addBone");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*, std::string_view)>(&cocostudio::Armature::addBone)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_changeBoneParent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:changeBoneParent");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*, std::string_view)>(&cocostudio::Armature::changeBoneParent)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getAnimation");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureAnimation*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getArmatureData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureData*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getArmatureData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getArmatureTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getArmatureTransformDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Armature::*)()const>(&cocostudio::Armature::getArmatureTransformDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBatchNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BatchNode*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getBatchNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocostudio::Armature::*)()const>(&cocostudio::Armature::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBone");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Bone*(cocostudio::Armature::*)(std::string_view)const>(&cocostudio::Armature::getBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_getBoneAtPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBoneAtPoint");
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::Bone*(cocostudio::Armature::*)(float, float)const>(&cocostudio::Armature::getBoneAtPoint)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_getBoneDic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBoneDic");
	LUA_TRY_INVOKE_R(0, (static_cast<const cocos2d::Map<std::string, cocostudio::Bone *, hlookup::string_hash, hlookup::equal_to>&(cocostudio::Armature::*)()const>(&cocostudio::Armature::getBoneDic)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getOffsetPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getOffsetPoints");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocostudio::Armature::*)()const>(&cocostudio::Armature::getOffsetPoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getParentBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getParentBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getVersion");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::Armature::*)()const>(&cocostudio::Armature::getVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::Armature::*)(std::string_view)>(&cocostudio::Armature::init));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocostudio::Armature::*)(std::string_view, cocostudio::Bone*)>(&cocostudio::Armature::init)));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_Armature_removeBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:removeBone");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*, bool)>(&cocostudio::Armature::removeBone)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::ArmatureAnimation*)>(&cocostudio::Armature::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setArmatureData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::ArmatureData*)>(&cocostudio::Armature::setArmatureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setBatchNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::BatchNode*)>(&cocostudio::Armature::setBatchNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(const cocos2d::BlendFunc&)>(&cocostudio::Armature::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setParentBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*)>(&cocostudio::Armature::setParentBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setVersion");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(float)>(&cocostudio::Armature::setVersion));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_updateOffsetPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:updateOffsetPoint");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Armature::*)()>(&cocostudio::Armature::updateOffsetPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Armature", "ccs.Armature:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::Armature*(*)(std::string_view, cocostudio::Bone*)>(&cocostudio::Armature::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Armature*(*)(std::string_view)>(&cocostudio::Armature::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Armature*(*)()>(&cocostudio::Armature::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int luaReg_Studio_ccsArmature(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Armature, "Armature", "ccs.Armature",
		cocostudio::Armature, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addBone", lua_cocostudio_Armature_addBone);
	LUA_METHOD("changeBoneParent", lua_cocostudio_Armature_changeBoneParent);
	LUA_METHOD("getAnimation", lua_cocostudio_Armature_getAnimation);
	LUA_METHOD("getArmatureData", lua_cocostudio_Armature_getArmatureData);
	LUA_METHOD("getArmatureTransformDirty", lua_cocostudio_Armature_getArmatureTransformDirty);
	LUA_METHOD("getBatchNode", lua_cocostudio_Armature_getBatchNode);
	LUA_METHOD("getBlendFunc", lua_cocostudio_Armature_getBlendFunc);
	LUA_METHOD("getBone", lua_cocostudio_Armature_getBone);
	LUA_METHOD("getBoneAtPoint", lua_cocostudio_Armature_getBoneAtPoint);
	LUA_METHOD("getBoneDic", lua_cocostudio_Armature_getBoneDic);
	LUA_METHOD("getOffsetPoints", lua_cocostudio_Armature_getOffsetPoints);
	LUA_METHOD("getParentBone", lua_cocostudio_Armature_getParentBone);
	LUA_METHOD("getVersion", lua_cocostudio_Armature_getVersion);
	LUA_METHOD("init", lua_cocostudio_Armature_init_1);
	LUA_METHOD("removeBone", lua_cocostudio_Armature_removeBone);
	LUA_METHOD("setAnimation", lua_cocostudio_Armature_setAnimation);
	LUA_METHOD("setArmatureData", lua_cocostudio_Armature_setArmatureData);
	LUA_METHOD("setBatchNode", lua_cocostudio_Armature_setBatchNode);
	LUA_METHOD("setBlendFunc", lua_cocostudio_Armature_setBlendFunc);
	LUA_METHOD("setParentBone", lua_cocostudio_Armature_setParentBone);
	LUA_METHOD("setVersion", lua_cocostudio_Armature_setVersion);
	LUA_METHOD("updateOffsetPoint", lua_cocostudio_Armature_updateOffsetPoint);
	LUA_METHOD("create", lua_cocostudio_Armature_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Skin_getBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Skin::*)()const>(&cocostudio::Skin::getBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_getDisplayName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getDisplayName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::Skin::*)()const>(&cocostudio::Skin::getDisplayName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_getNodeToWorldTransformAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getNodeToWorldTransformAR");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocostudio::Skin::*)()const>(&cocostudio::Skin::getNodeToWorldTransformAR));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_setBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:setBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Skin::*)(cocostudio::Bone*)>(&cocostudio::Skin::setBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Skin_updateArmatureTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:updateArmatureTransform");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Skin::*)()>(&cocostudio::Skin::updateArmatureTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Skin", "ccs.Skin:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Skin*(*)(std::string_view)>(&cocostudio::Skin::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Skin*(*)()>(&cocostudio::Skin::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int lua_cocostudio_Skin_createWithSpriteFrameName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Skin", "ccs.Skin:createWithSpriteFrameName");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Skin*(*)(std::string_view)>(&cocostudio::Skin::createWithSpriteFrameName));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsSkin(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Skin, "Skin", "ccs.Skin",
		cocostudio::Skin, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("getBone", lua_cocostudio_Skin_getBone);
	LUA_METHOD("getDisplayName", lua_cocostudio_Skin_getDisplayName);
	LUA_METHOD("getNodeToWorldTransformAR", lua_cocostudio_Skin_getNodeToWorldTransformAR);
	LUA_METHOD("setBone", lua_cocostudio_Skin_setBone);
	LUA_METHOD("updateArmatureTransform", lua_cocostudio_Skin_updateArmatureTransform);
	LUA_METHOD("create", lua_cocostudio_Skin_create);
	LUA_METHOD("createWithSpriteFrameName", lua_cocostudio_Skin_createWithSpriteFrameName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ComAttribute_getBool(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:getBool");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocostudio::ComAttribute::*)(std::string_view, bool)const>(&cocostudio::ComAttribute::getBool)));
	LUA_TRY_INVOKE_R(1, ([](const cocostudio::ComAttribute* obj,std::string_view arg0){{return obj->getBool(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_ComAttribute_getFloat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:getFloat");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocostudio::ComAttribute::*)(std::string_view, float)const>(&cocostudio::ComAttribute::getFloat)));
	LUA_TRY_INVOKE_R(1, ([](const cocostudio::ComAttribute* obj,std::string_view arg0){{return obj->getFloat(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_ComAttribute_getInt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:getInt");
	LUA_TRY_INVOKE_R(2, (static_cast<int(cocostudio::ComAttribute::*)(std::string_view, int)const>(&cocostudio::ComAttribute::getInt)));
	LUA_TRY_INVOKE_R(1, ([](const cocostudio::ComAttribute* obj,std::string_view arg0){{return obj->getInt(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_ComAttribute_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:getString");
	LUA_TRY_INVOKE_R(2, (static_cast<std::string(cocostudio::ComAttribute::*)(std::string_view, std::string_view)const>(&cocostudio::ComAttribute::getString)));
	LUA_TRY_INVOKE_R(1, ([](const cocostudio::ComAttribute* obj,std::string_view arg0){{return obj->getString(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocostudio_ComAttribute_parse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:parse");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::ComAttribute::*)(std::string_view)>(&cocostudio::ComAttribute::parse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAttribute_setBool(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:setBool");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::ComAttribute::*)(std::string_view, bool)>(&cocostudio::ComAttribute::setBool)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ComAttribute_setFloat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:setFloat");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::ComAttribute::*)(std::string_view, float)>(&cocostudio::ComAttribute::setFloat)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ComAttribute_setInt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:setInt");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::ComAttribute::*)(std::string_view, int)>(&cocostudio::ComAttribute::setInt)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ComAttribute_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:setString");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::ComAttribute::*)(std::string_view, std::string_view)>(&cocostudio::ComAttribute::setString)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_ComAttribute_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComAttribute*(*)()>(&cocostudio::ComAttribute::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComAttribute_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComAttribute::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComAttribute(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComAttribute, "ComAttribute", "ccs.ComAttribute",
		cocostudio::ComAttribute, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getBool", lua_cocostudio_ComAttribute_getBool);
	LUA_METHOD("getFloat", lua_cocostudio_ComAttribute_getFloat);
	LUA_METHOD("getInt", lua_cocostudio_ComAttribute_getInt);
	LUA_METHOD("getString", lua_cocostudio_ComAttribute_getString);
	LUA_METHOD("parse", lua_cocostudio_ComAttribute_parse);
	LUA_METHOD("setBool", lua_cocostudio_ComAttribute_setBool);
	LUA_METHOD("setFloat", lua_cocostudio_ComAttribute_setFloat);
	LUA_METHOD("setInt", lua_cocostudio_ComAttribute_setInt);
	LUA_METHOD("setString", lua_cocostudio_ComAttribute_setString);
	LUA_METHOD("create", lua_cocostudio_ComAttribute_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComAttribute_createInstance);
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
	tolua_open(lua_S);
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
	return 0;
}
