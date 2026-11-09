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

int lua_cocos2d_AnimationFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AnimationFrame*(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getDelayUnits");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getDelayUnits));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrame*(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getSpriteFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getUserInfo");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::AnimationFrame::*)(cocos2d::SpriteFrame*, float, const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::initWithSpriteFrame)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_AnimationFrame_setDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setDelayUnits");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(float)>(&cocos2d::AnimationFrame::setDelayUnits));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(cocos2d::SpriteFrame*)>(&cocos2d::AnimationFrame::setSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setUserInfo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::setUserInfo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::AnimationFrame*(*)(cocos2d::SpriteFrame*, float, const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccAnimationFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationFrame, "AnimationFrame", "cc.AnimationFrame",
		cocos2d::AnimationFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_AnimationFrame_clone);
	LUA_METHOD("getDelayUnits", lua_cocos2d_AnimationFrame_getDelayUnits);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_AnimationFrame_getSpriteFrame);
	LUA_METHOD("getUserInfo", lua_cocos2d_AnimationFrame_getUserInfo);
	LUA_METHOD("initWithSpriteFrame", lua_cocos2d_AnimationFrame_initWithSpriteFrame);
	LUA_METHOD("setDelayUnits", lua_cocos2d_AnimationFrame_setDelayUnits);
	LUA_METHOD("setSpriteFrame", lua_cocos2d_AnimationFrame_setSpriteFrame);
	LUA_METHOD("setUserInfo", lua_cocos2d_AnimationFrame_setUserInfo);
	LUA_METHOD("create", lua_cocos2d_AnimationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animation_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(cocos2d::SpriteFrame*)>(&cocos2d::Animation::addSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithFile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(std::string_view)>(&cocos2d::Animation::addSpriteFrameWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Animation::*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::Animation::addSpriteFrameWithTexture)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animation_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Animation*(cocos2d::Animation::*)()const>(&cocos2d::Animation::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDelayPerUnit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getDelayPerUnit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getFrames");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::AnimationFrame *>&(cocos2d::Animation::*)()const>(&cocos2d::Animation::getFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getLoops");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Animation::*)()const>(&cocos2d::Animation::getLoops));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getRestoreOriginalFrame");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Animation::*)()const>(&cocos2d::Animation::getRestoreOriginalFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getTotalDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getTotalDelayUnits");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getTotalDelayUnits));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Animation::*)()>(&cocos2d::Animation::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_initWithAnimationFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithAnimationFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&, float, unsigned int)>(&cocos2d::Animation::initWithAnimationFrames)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Animation_initWithSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::SpriteFrame *>&, float, unsigned int)>(&cocos2d::Animation::initWithSpriteFrames)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return obj->initWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return obj->initWithSpriteFrames(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_Animation_setDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setDelayPerUnit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(float)>(&cocos2d::Animation::setDelayPerUnit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setFrames");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&)>(&cocos2d::Animation::setFrames));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setLoops");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(unsigned int)>(&cocos2d::Animation::setLoops));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setRestoreOriginalFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(bool)>(&cocos2d::Animation::setRestoreOriginalFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Animation*(*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&, float, unsigned int)>(&cocos2d::Animation::create)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::AnimationFrame *>& arg0,float arg1){{return cocos2d::Animation::create(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Animation*(*)()>(&cocos2d::Animation::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cocos2d_Animation_createWithSpriteFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:createWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Animation*(*)(const cocos2d::Vector<cocos2d::SpriteFrame *>&, float, unsigned int)>(&cocos2d::Animation::createWithSpriteFrames)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return cocos2d::Animation::createWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return cocos2d::Animation::createWithSpriteFrames(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Core_ccAnimation(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation, "Animation", "cc.Animation",
		cocos2d::Animation, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_Animation_addSpriteFrame);
	LUA_METHOD("addSpriteFrameWithFile", lua_cocos2d_Animation_addSpriteFrameWithFile);
	LUA_METHOD("addSpriteFrameWithTexture", lua_cocos2d_Animation_addSpriteFrameWithTexture);
	LUA_METHOD("clone", lua_cocos2d_Animation_clone);
	LUA_METHOD("getDelayPerUnit", lua_cocos2d_Animation_getDelayPerUnit);
	LUA_METHOD("getDuration", lua_cocos2d_Animation_getDuration);
	LUA_METHOD("getFrames", lua_cocos2d_Animation_getFrames);
	LUA_METHOD("getLoops", lua_cocos2d_Animation_getLoops);
	LUA_METHOD("getRestoreOriginalFrame", lua_cocos2d_Animation_getRestoreOriginalFrame);
	LUA_METHOD("getTotalDelayUnits", lua_cocos2d_Animation_getTotalDelayUnits);
	LUA_METHOD("init", lua_cocos2d_Animation_init);
	LUA_METHOD("initWithAnimationFrames", lua_cocos2d_Animation_initWithAnimationFrames);
	LUA_METHOD("initWithSpriteFrames", lua_cocos2d_Animation_initWithSpriteFrames);
	LUA_METHOD("setDelayPerUnit", lua_cocos2d_Animation_setDelayPerUnit);
	LUA_METHOD("setFrames", lua_cocos2d_Animation_setFrames);
	LUA_METHOD("setLoops", lua_cocos2d_Animation_setLoops);
	LUA_METHOD("setRestoreOriginalFrame", lua_cocos2d_Animation_setRestoreOriginalFrame);
	LUA_METHOD("create", lua_cocos2d_Animation_create);
	LUA_METHOD("createWithSpriteFrames", lua_cocos2d_Animation_createWithSpriteFrames);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionInterval_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ActionInterval::*)()>(&cocos2d::ActionInterval::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_getElapsed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getElapsed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ActionInterval::*)()>(&cocos2d::ActionInterval::getElapsed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:initWithDuration");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ActionInterval::*)(float)>(&cocos2d::ActionInterval::initWithDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionInterval_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionInterval::*)(float)>(&cocos2d::ActionInterval::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionInterval(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionInterval, "ActionInterval", "cc.ActionInterval",
		cocos2d::ActionInterval, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_ActionInterval_getAmplitudeRate);
	LUA_METHOD("getElapsed", lua_cocos2d_ActionInterval_getElapsed);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionInterval_initWithDuration);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_ActionInterval_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Sequence_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Sequence::*)(const cocos2d::Vector<cocos2d::FiniteTimeAction *>&)>(&cocos2d::Sequence::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sequence_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Sequence::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Sequence::initWithTwoActions)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSequence(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Sequence, "Sequence", "cc.Sequence",
		cocos2d::Sequence, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Sequence_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Sequence_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Repeat_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::FiniteTimeAction*(cocos2d::Repeat::*)()>(&cocos2d::Repeat::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Repeat_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:initWithAction");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Repeat::*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::initWithAction)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Repeat_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:setInnerAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Repeat::*)(cocos2d::FiniteTimeAction*)>(&cocos2d::Repeat::setInnerAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Repeat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Repeat", "cc.Repeat:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Repeat*(*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccRepeat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Repeat, "Repeat", "cc.Repeat",
		cocos2d::Repeat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_Repeat_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_Repeat_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_Repeat_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_Repeat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RepeatForever_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::RepeatForever::*)()>(&cocos2d::RepeatForever::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RepeatForever_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:initWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::RepeatForever::*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::initWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:setInnerAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RepeatForever::*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::setInnerAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::RepeatForever*(*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccRepeatForever(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RepeatForever, "RepeatForever", "cc.RepeatForever",
		cocos2d::RepeatForever, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_RepeatForever_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_RepeatForever_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_RepeatForever_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_RepeatForever_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Spawn_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Spawn::*)(const cocos2d::Vector<cocos2d::FiniteTimeAction *>&)>(&cocos2d::Spawn::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Spawn_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Spawn::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Spawn::initWithTwoActions)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSpawn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Spawn, "Spawn", "cc.Spawn",
		cocos2d::Spawn, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Spawn_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Spawn_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateTo", "cc.RotateTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateTo::*)(float, float, float)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::RotateTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateTo", "cc.RotateTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::RotateTo*(*)(float, float, float)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateTo*(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateTo*(*)(float, float)>(&cocos2d::RotateTo::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateTo, "RotateTo", "cc.RotateTo",
		cocos2d::RotateTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateBy", "cc.RotateBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateBy::*)(float, float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateBy", "cc.RotateBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::RotateBy*(*)(float, float, float)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateBy*(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateBy*(*)(float, float)>(&cocos2d::RotateBy::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateBy, "RotateBy", "cc.RotateBy",
		cocos2d::RotateBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveBy", "cc.MoveBy:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveBy", "cc.MoveBy:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveBy*(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveBy*(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveBy, "MoveBy", "cc.MoveBy",
		cocos2d::MoveBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveTo", "cc.MoveTo:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveTo", "cc.MoveTo:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveTo*(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveTo*(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveTo, "MoveTo", "cc.MoveTo",
		cocos2d::MoveTo, "cc.MoveBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SkewTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewTo", "cc.SkewTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::SkewTo::*)(float, float, float)>(&cocos2d::SkewTo::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewTo", "cc.SkewTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SkewTo*(*)(float, float, float)>(&cocos2d::SkewTo::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewTo, "SkewTo", "cc.SkewTo",
		cocos2d::SkewTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
