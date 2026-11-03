#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_SpriteFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrame*(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::SpriteFrame::*)()>(&cocos2d::SpriteFrame::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::hasAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasCenterRect");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::hasCenterRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_isRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:isRotated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::isRotated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_setRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRotated");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(bool)>(&cocos2d::SpriteFrame::setRotated));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*)>(&cocos2d::SpriteFrame::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccSpriteFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteFrame, "SpriteFrame", "cc.SpriteFrame",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_SpriteFrame_clone);
	LUA_METHOD("getTexture", lua_cocos2d_SpriteFrame_getTexture);
	LUA_METHOD("hasAnchorPoint", lua_cocos2d_SpriteFrame_hasAnchorPoint);
	LUA_METHOD("hasCenterRect", lua_cocos2d_SpriteFrame_hasCenterRect);
	LUA_METHOD("isRotated", lua_cocos2d_SpriteFrame_isRotated);
	LUA_METHOD("setRotated", lua_cocos2d_SpriteFrame_setRotated);
	LUA_METHOD("setTexture", lua_cocos2d_SpriteFrame_setTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int luaReg_Core_ccAnimationFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationFrame, "AnimationFrame", "cc.AnimationFrame",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_AnimationFrame_clone);
	LUA_METHOD("getDelayUnits", lua_cocos2d_AnimationFrame_getDelayUnits);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_AnimationFrame_getSpriteFrame);
	LUA_METHOD("setDelayUnits", lua_cocos2d_AnimationFrame_setDelayUnits);
	LUA_METHOD("setSpriteFrame", lua_cocos2d_AnimationFrame_setSpriteFrame);
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
int lua_cocos2d_Animation_setDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setDelayPerUnit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(float)>(&cocos2d::Animation::setDelayPerUnit));
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
int luaReg_Core_ccAnimation(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation, "Animation", "cc.Animation",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_Animation_addSpriteFrame);
	LUA_METHOD("addSpriteFrameWithFile", lua_cocos2d_Animation_addSpriteFrameWithFile);
	LUA_METHOD("clone", lua_cocos2d_Animation_clone);
	LUA_METHOD("getDelayPerUnit", lua_cocos2d_Animation_getDelayPerUnit);
	LUA_METHOD("getDuration", lua_cocos2d_Animation_getDuration);
	LUA_METHOD("getLoops", lua_cocos2d_Animation_getLoops);
	LUA_METHOD("getRestoreOriginalFrame", lua_cocos2d_Animation_getRestoreOriginalFrame);
	LUA_METHOD("getTotalDelayUnits", lua_cocos2d_Animation_getTotalDelayUnits);
	LUA_METHOD("init", lua_cocos2d_Animation_init);
	LUA_METHOD("setDelayPerUnit", lua_cocos2d_Animation_setDelayPerUnit);
	LUA_METHOD("setLoops", lua_cocos2d_Animation_setLoops);
	LUA_METHOD("setRestoreOriginalFrame", lua_cocos2d_Animation_setRestoreOriginalFrame);
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
		cocos2d::FiniteTimeAction, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_ActionInterval_getAmplitudeRate);
	LUA_METHOD("getElapsed", lua_cocos2d_ActionInterval_getElapsed);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionInterval_initWithDuration);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_ActionInterval_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Sequence_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Sequence::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Sequence::initWithTwoActions));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSequence(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Sequence, "Sequence", "cc.Sequence",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
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
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Repeat::*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::initWithAction));
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
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Repeat*(*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccRepeat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Repeat, "Repeat", "cc.Repeat",
		cocos2d::ActionInterval, "cc.ActionInterval",
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
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_RepeatForever_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_RepeatForever_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_RepeatForever_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_RepeatForever_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Spawn_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Spawn::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Spawn::initWithTwoActions));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSpawn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Spawn, "Spawn", "cc.Spawn",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Spawn_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccRotateTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateTo, "RotateTo", "cc.RotateTo",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccRotateBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateBy, "RotateBy", "cc.RotateBy",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccMoveBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveBy, "MoveBy", "cc.MoveBy",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccMoveTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveTo, "MoveTo", "cc.MoveTo",
		cocos2d::MoveBy, "cc.MoveBy",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
