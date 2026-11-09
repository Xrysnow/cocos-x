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

int lua_cocos2d_SkewBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewBy", "cc.SkewBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::SkewBy::*)(float, float, float)>(&cocos2d::SkewBy::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewBy", "cc.SkewBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SkewBy*(*)(float, float, float)>(&cocos2d::SkewBy::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewBy, "SkewBy", "cc.SkewBy",
		cocos2d::SkewBy, "cc.SkewTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpBy", "cc.JumpBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::JumpBy::*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpBy::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpBy", "cc.JumpBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::JumpBy*(*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpBy::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpBy, "JumpBy", "cc.JumpBy",
		cocos2d::JumpBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTo", "cc.JumpTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::JumpTo::*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpTo::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTo", "cc.JumpTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::JumpTo*(*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpTo::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpTo, "JumpTo", "cc.JumpTo",
		cocos2d::JumpTo, "cc.JumpBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccBezierBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierBy, "BezierBy", "cc.BezierBy",
		cocos2d::BezierBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccBezierTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierTo, "BezierTo", "cc.BezierTo",
		cocos2d::BezierTo, "cc.BezierBy",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ScaleTo::*)(float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ScaleTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ScaleTo*(*)(float, float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ScaleTo*(*)(float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ScaleTo*(*)(float, float)>(&cocos2d::ScaleTo::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleTo, "ScaleTo", "cc.ScaleTo",
		cocos2d::ScaleTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ScaleTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ScaleTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleBy", "cc.ScaleBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ScaleBy*(*)(float, float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ScaleBy*(*)(float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ScaleBy*(*)(float, float)>(&cocos2d::ScaleBy::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleBy, "ScaleBy", "cc.ScaleBy",
		cocos2d::ScaleBy, "cc.ScaleTo",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ScaleBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Blink_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Blink", "cc.Blink:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Blink::*)(float, int)>(&cocos2d::Blink::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Blink_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Blink", "cc.Blink:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Blink*(*)(float, int)>(&cocos2d::Blink::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBlink(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Blink, "Blink", "cc.Blink",
		cocos2d::Blink, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_Blink_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_Blink_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeTo", "cc.FadeTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FadeTo::*)(float, uint8_t)>(&cocos2d::FadeTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FadeTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeTo", "cc.FadeTo:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeTo*(*)(float, uint8_t)>(&cocos2d::FadeTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeTo, "FadeTo", "cc.FadeTo",
		cocos2d::FadeTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_FadeTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_FadeTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeIn_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeIn", "cc.FadeIn:setReverseAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeIn::*)(cocos2d::FadeTo*)>(&cocos2d::FadeIn::setReverseAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeIn", "cc.FadeIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FadeIn*(*)(float)>(&cocos2d::FadeIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeIn, "FadeIn", "cc.FadeIn",
		cocos2d::FadeIn, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeIn_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOut_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOut", "cc.FadeOut:setReverseAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeOut::*)(cocos2d::FadeTo*)>(&cocos2d::FadeOut::setReverseAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOut", "cc.FadeOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FadeOut*(*)(float)>(&cocos2d::FadeOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOut, "FadeOut", "cc.FadeOut",
		cocos2d::FadeOut, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeOut_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TintTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintTo", "cc.TintTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TintTo::*)(float, uint8_t, uint8_t, uint8_t)>(&cocos2d::TintTo::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintTo", "cc.TintTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TintTo*(*)(float, uint8_t, uint8_t, uint8_t)>(&cocos2d::TintTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TintTo*(*)(float, const cocos2d::Color3B&)>(&cocos2d::TintTo::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Core_ccTintTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintTo, "TintTo", "cc.TintTo",
		cocos2d::TintTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
