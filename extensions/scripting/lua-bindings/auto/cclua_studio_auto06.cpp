#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_timeline_EventFrame_getEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:getEvent");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::timeline::EventFrame::*)()const>(&cocostudio::timeline::EventFrame::getEvent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_EventFrame_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::EventFrame::*)()>(&cocostudio::timeline::EventFrame::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_EventFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::EventFrame*(*)()>(&cocostudio::timeline::EventFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsEventFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::EventFrame, "EventFrame", "ccs.EventFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getEvent", lua_cocostudio_timeline_EventFrame_getEvent);
	LUA_METHOD("init", lua_cocostudio_timeline_EventFrame_init);
	LUA_METHOD("create", lua_cocostudio_timeline_EventFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ZOrderFrame_getZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:getZOrder");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ZOrderFrame::*)()const>(&cocostudio::timeline::ZOrderFrame::getZOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ZOrderFrame_setZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:setZOrder");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ZOrderFrame::*)(int)>(&cocostudio::timeline::ZOrderFrame::setZOrder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ZOrderFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ZOrderFrame*(*)()>(&cocostudio::timeline::ZOrderFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsZOrderFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ZOrderFrame, "ZOrderFrame", "ccs.ZOrderFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getZOrder", lua_cocostudio_timeline_ZOrderFrame_getZOrder);
	LUA_METHOD("setZOrder", lua_cocostudio_timeline_ZOrderFrame_setZOrder);
	LUA_METHOD("create", lua_cocostudio_timeline_ZOrderFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_BlendFuncFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BlendFuncFrame", "ccs.BlendFuncFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::BlendFuncFrame*(*)()>(&cocostudio::timeline::BlendFuncFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBlendFuncFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::BlendFuncFrame, "BlendFuncFrame", "ccs.BlendFuncFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_timeline_BlendFuncFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_PlayableFrame_getPlayableAct(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:getPlayableAct");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::timeline::PlayableFrame::*)()const>(&cocostudio::timeline::PlayableFrame::getPlayableAct));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_PlayableFrame_setPlayableAct(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:setPlayableAct");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::PlayableFrame::*)(std::string)>(&cocostudio::timeline::PlayableFrame::setPlayableAct));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_PlayableFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::PlayableFrame*(*)()>(&cocostudio::timeline::PlayableFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsPlayableFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::PlayableFrame, "PlayableFrame", "ccs.PlayableFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getPlayableAct", lua_cocostudio_timeline_PlayableFrame_getPlayableAct);
	LUA_METHOD("setPlayableAct", lua_cocostudio_timeline_PlayableFrame_setPlayableAct);
	LUA_METHOD("create", lua_cocostudio_timeline_PlayableFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_Timeline_addFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:addFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*)>(&cocostudio::timeline::Timeline::addFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Timeline*(cocostudio::timeline::Timeline::*)()>(&cocostudio::timeline::Timeline::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getActionTimeline");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getActionTimeline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_gotoFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:gotoFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::gotoFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_insertFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:insertFrame");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*, int)>(&cocostudio::timeline::Timeline::insertFrame));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_Timeline_removeFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:removeFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*)>(&cocostudio::timeline::Timeline::removeFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setActionTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::Timeline::setActionTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocos2d::Node*)>(&cocostudio::timeline::Timeline::setNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_stepToFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:stepToFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::stepToFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Timeline", "ccs.Timeline:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Timeline*(*)()>(&cocostudio::timeline::Timeline::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsTimeline(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::Timeline, "Timeline", "ccs.Timeline",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addFrame", lua_cocostudio_timeline_Timeline_addFrame);
	LUA_METHOD("clone", lua_cocostudio_timeline_Timeline_clone);
	LUA_METHOD("getActionTag", lua_cocostudio_timeline_Timeline_getActionTag);
	LUA_METHOD("getActionTimeline", lua_cocostudio_timeline_Timeline_getActionTimeline);
	LUA_METHOD("getNode", lua_cocostudio_timeline_Timeline_getNode);
	LUA_METHOD("gotoFrame", lua_cocostudio_timeline_Timeline_gotoFrame);
	LUA_METHOD("insertFrame", lua_cocostudio_timeline_Timeline_insertFrame);
	LUA_METHOD("removeFrame", lua_cocostudio_timeline_Timeline_removeFrame);
	LUA_METHOD("setActionTag", lua_cocostudio_timeline_Timeline_setActionTag);
	LUA_METHOD("setActionTimeline", lua_cocostudio_timeline_Timeline_setActionTimeline);
	LUA_METHOD("setNode", lua_cocostudio_timeline_Timeline_setNode);
	LUA_METHOD("stepToFrame", lua_cocostudio_timeline_Timeline_stepToFrame);
	LUA_METHOD("create", lua_cocostudio_timeline_Timeline_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineData_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimelineData::*)()const>(&cocostudio::timeline::ActionTimelineData::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::timeline::ActionTimelineData::*)(int)>(&cocostudio::timeline::ActionTimelineData::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineData_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineData::*)(int)>(&cocostudio::timeline::ActionTimelineData::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimelineData*(*)(int)>(&cocostudio::timeline::ActionTimelineData::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionTimelineData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimelineData, "ActionTimelineData", "ccs.ActionTimelineData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActionTag", lua_cocostudio_timeline_ActionTimelineData_getActionTag);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimelineData_init);
	LUA_METHOD("setActionTag", lua_cocostudio_timeline_ActionTimelineData_setActionTag);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimelineData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimeline_addTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:addTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(cocostudio::timeline::Timeline*)>(&cocostudio::timeline::ActionTimeline::addTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_clearFrameEndCallFuncs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearFrameEndCallFuncs");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearFrameEndCallFuncs));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_clearFrameEventCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearFrameEventCallFunc");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearFrameEventCallFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_clearLastFrameCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearLastFrameCallFunc");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearLastFrameCallFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getCurrentFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getCurrentFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getCurrentFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getEndFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getEndFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getEndFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getStartFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getStartFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getStartFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getTimeSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getTimeSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getTimeSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:gotoFrameAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:gotoFrameAndPlay");
	LUA_TRY_INVOKE(4, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, int, int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay));
	LUA_TRY_INVOKE(3, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay));
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay));
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocostudio_timeline_ActionTimeline_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_isPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:isPlaying");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::isPlaying));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:pause");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::pause));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:play");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::string, bool)>(&cocostudio::timeline::ActionTimeline::play));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimeline_removeAnimationInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeAnimationInfo");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::string)>(&cocostudio::timeline::ActionTimeline::removeAnimationInfo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFuncs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeFrameEndCallFuncs");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::removeFrameEndCallFuncs));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_removeTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(cocostudio::timeline::Timeline*)>(&cocostudio::timeline::ActionTimeline::removeTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:resume");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::resume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_setCurrentFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setCurrentFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::setCurrentFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setDuration");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::setDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setFrameEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setFrameEventCallFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::function<void (cocostudio::timeline::Frame *)>)>(&cocostudio::timeline::ActionTimeline::setFrameEventCallFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setTimeSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setTimeSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(float)>(&cocostudio::timeline::ActionTimeline::setTimeSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(*)()>(&cocostudio::timeline::ActionTimeline::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsActionTimeline(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimeline, "ActionTimeline", "ccs.ActionTimeline",
		cocos2d::Action, "ccs.cocos2d.Action",
		nullptr, nullptr);
	LUA_METHOD("addTimeline", lua_cocostudio_timeline_ActionTimeline_addTimeline);
	LUA_METHOD("clearFrameEndCallFuncs", lua_cocostudio_timeline_ActionTimeline_clearFrameEndCallFuncs);
	LUA_METHOD("clearFrameEventCallFunc", lua_cocostudio_timeline_ActionTimeline_clearFrameEventCallFunc);
	LUA_METHOD("clearLastFrameCallFunc", lua_cocostudio_timeline_ActionTimeline_clearLastFrameCallFunc);
	LUA_METHOD("getCurrentFrame", lua_cocostudio_timeline_ActionTimeline_getCurrentFrame);
	LUA_METHOD("getDuration", lua_cocostudio_timeline_ActionTimeline_getDuration);
	LUA_METHOD("getEndFrame", lua_cocostudio_timeline_ActionTimeline_getEndFrame);
	LUA_METHOD("getStartFrame", lua_cocostudio_timeline_ActionTimeline_getStartFrame);
	LUA_METHOD("getTimeSpeed", lua_cocostudio_timeline_ActionTimeline_getTimeSpeed);
	LUA_METHOD("gotoFrameAndPause", lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPause);
	LUA_METHOD("gotoFrameAndPlay", lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPlay);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimeline_init);
	LUA_METHOD("isPlaying", lua_cocostudio_timeline_ActionTimeline_isPlaying);
	LUA_METHOD("pause", lua_cocostudio_timeline_ActionTimeline_pause);
	LUA_METHOD("play", lua_cocostudio_timeline_ActionTimeline_play);
	LUA_METHOD("removeAnimationInfo", lua_cocostudio_timeline_ActionTimeline_removeAnimationInfo);
	LUA_METHOD("removeFrameEndCallFuncs", lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFuncs);
	LUA_METHOD("removeTimeline", lua_cocostudio_timeline_ActionTimeline_removeTimeline);
	LUA_METHOD("resume", lua_cocostudio_timeline_ActionTimeline_resume);
	LUA_METHOD("setCurrentFrame", lua_cocostudio_timeline_ActionTimeline_setCurrentFrame);
	LUA_METHOD("setDuration", lua_cocostudio_timeline_ActionTimeline_setDuration);
	LUA_METHOD("setFrameEventCallFunc", lua_cocostudio_timeline_ActionTimeline_setFrameEventCallFunc_1);
	LUA_METHOD("setTimeSpeed", lua_cocostudio_timeline_ActionTimeline_setTimeSpeed);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimeline_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineNode_getActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:getActionTimeline");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineNode::*)()>(&cocostudio::timeline::ActionTimelineNode::getActionTimeline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineNode_getRoot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:getRoot");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::timeline::ActionTimelineNode::*)()>(&cocostudio::timeline::ActionTimelineNode::getRoot));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineNode_setActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:setActionTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineNode::*)(cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::ActionTimelineNode::setActionTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineNode_setRoot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:setRoot");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineNode::*)(cocos2d::Node*)>(&cocostudio::timeline::ActionTimelineNode::setRoot));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::timeline::ActionTimelineNode*(*)(cocos2d::Node*, cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::ActionTimelineNode::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Studio_ccsActionTimelineNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimelineNode, "ActionTimelineNode", "ccs.ActionTimelineNode",
		cocos2d::Node, "ccs.cocos2d.Node",
		nullptr, nullptr);
	LUA_METHOD("getActionTimeline", lua_cocostudio_timeline_ActionTimelineNode_getActionTimeline);
	LUA_METHOD("getRoot", lua_cocostudio_timeline_ActionTimelineNode_getRoot);
	LUA_METHOD("setActionTimeline", lua_cocostudio_timeline_ActionTimelineNode_setActionTimeline);
	LUA_METHOD("setRoot", lua_cocostudio_timeline_ActionTimelineNode_setRoot);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimelineNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
