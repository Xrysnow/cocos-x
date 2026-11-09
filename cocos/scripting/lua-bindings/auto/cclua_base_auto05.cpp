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


int luaReg_Core_ccEventFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventFocus, "EventFocus", "cc.EventFocus",
		cocos2d::EventFocus, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerAcceleration_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerAcceleration", "cc.EventListenerAcceleration:init");
	LUA_TRY_INVOKE_R(1, (static_cast<bool(cocos2d::EventListenerAcceleration::*)(const std::function<void(cocos2d::Acceleration*, cocos2d::Event*)>&)>(&cocos2d::EventListenerAcceleration::init)));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerAcceleration, "EventListenerAcceleration", "cc.EventListenerAcceleration",
		cocos2d::EventListenerAcceleration, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerAcceleration_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerFocus_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerFocus::*)()>(&cocos2d::EventListenerFocus::init));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerFocus, "EventListenerFocus", "cc.EventListenerFocus",
		cocos2d::EventListenerFocus, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerFocus_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerKeyboard_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerKeyboard", "cc.EventListenerKeyboard:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerKeyboard::*)()>(&cocos2d::EventListenerKeyboard::init));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerKeyboard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerKeyboard, "EventListenerKeyboard", "cc.EventListenerKeyboard",
		cocos2d::EventListenerKeyboard, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerKeyboard_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventMouse_getCursorX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getCursorX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getCursorY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getCursorY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getDelta");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getDelta));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getMouseButton");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventMouse::MouseButton(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getMouseButton));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getPreviousLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getPreviousLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getPreviousLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getPreviousLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getScrollX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getScrollX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getScrollY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getScrollY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getStartLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getStartLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getStartLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getStartLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setCursorPosition");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventMouse::*)(float, float)>(&cocos2d::EventMouse::setCursorPosition)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventMouse_setMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setMouseButton");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventMouse::*)(cocos2d::EventMouse::MouseButton)>(&cocos2d::EventMouse::setMouseButton));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventMouse_setScrollData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setScrollData");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventMouse::*)(float, float)>(&cocos2d::EventMouse::setScrollData)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventMouse, "EventMouse", "cc.EventMouse",
		cocos2d::EventMouse, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getCursorX", lua_cocos2d_EventMouse_getCursorX);
	LUA_METHOD("getCursorY", lua_cocos2d_EventMouse_getCursorY);
	LUA_METHOD("getDelta", lua_cocos2d_EventMouse_getDelta);
	LUA_METHOD("getLocation", lua_cocos2d_EventMouse_getLocation);
	LUA_METHOD("getLocationInView", lua_cocos2d_EventMouse_getLocationInView);
	LUA_METHOD("getMouseButton", lua_cocos2d_EventMouse_getMouseButton);
	LUA_METHOD("getPreviousLocation", lua_cocos2d_EventMouse_getPreviousLocation);
	LUA_METHOD("getPreviousLocationInView", lua_cocos2d_EventMouse_getPreviousLocationInView);
	LUA_METHOD("getScrollX", lua_cocos2d_EventMouse_getScrollX);
	LUA_METHOD("getScrollY", lua_cocos2d_EventMouse_getScrollY);
	LUA_METHOD("getStartLocation", lua_cocos2d_EventMouse_getStartLocation);
	LUA_METHOD("getStartLocationInView", lua_cocos2d_EventMouse_getStartLocationInView);
	LUA_METHOD("setCursorPosition", lua_cocos2d_EventMouse_setCursorPosition);
	LUA_METHOD("setMouseButton", lua_cocos2d_EventMouse_setMouseButton);
	LUA_METHOD("setScrollData", lua_cocos2d_EventMouse_setScrollData);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerMouse_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerMouse", "cc.EventListenerMouse:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerMouse::*)()>(&cocos2d::EventListenerMouse::init));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerMouse, "EventListenerMouse", "cc.EventListenerMouse",
		cocos2d::EventListenerMouse, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerMouse_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerTouchOneByOne_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerTouchOneByOne::*)()>(&cocos2d::EventListenerTouchOneByOne::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerTouchOneByOne_isSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:isSwallowTouches");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerTouchOneByOne::*)()>(&cocos2d::EventListenerTouchOneByOne::isSwallowTouches));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerTouchOneByOne_setSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:setSwallowTouches");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventListenerTouchOneByOne::*)(bool)>(&cocos2d::EventListenerTouchOneByOne::setSwallowTouches));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListenerTouchOneByOne(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerTouchOneByOne, "EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne",
		cocos2d::EventListenerTouchOneByOne, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerTouchOneByOne_init);
	LUA_METHOD("isSwallowTouches", lua_cocos2d_EventListenerTouchOneByOne_isSwallowTouches);
	LUA_METHOD("setSwallowTouches", lua_cocos2d_EventListenerTouchOneByOne_setSwallowTouches);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerTouchAllAtOnce_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerTouchAllAtOnce::*)()>(&cocos2d::EventListenerTouchAllAtOnce::init));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerTouchAllAtOnce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerTouchAllAtOnce, "EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce",
		cocos2d::EventListenerTouchAllAtOnce, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerTouchAllAtOnce_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionCamera_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getCenter");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::ActionCamera::*)()const>(&cocos2d::ActionCamera::getCenter));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_getEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getEye");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::ActionCamera::*)()const>(&cocos2d::ActionCamera::getEye));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_getUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getUp");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::ActionCamera::*)()const>(&cocos2d::ActionCamera::getUp));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_setCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setCenter");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionCamera::*)(const cocos2d::Vec3&)>(&cocos2d::ActionCamera::setCenter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionCamera_setEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setEye");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ActionCamera::*)(float, float, float)>(&cocos2d::ActionCamera::setEye)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionCamera::*)(const cocos2d::Vec3&)>(&cocos2d::ActionCamera::setEye));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cocos2d_ActionCamera_setUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setUp");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionCamera::*)(const cocos2d::Vec3&)>(&cocos2d::ActionCamera::setUp));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionCamera, "ActionCamera", "cc.ActionCamera",
		cocos2d::ActionCamera, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getCenter", lua_cocos2d_ActionCamera_getCenter);
	LUA_METHOD("getEye", lua_cocos2d_ActionCamera_getEye);
	LUA_METHOD("getUp", lua_cocos2d_ActionCamera_getUp);
	LUA_METHOD("setCenter", lua_cocos2d_ActionCamera_setCenter);
	LUA_METHOD("setEye", lua_cocos2d_ActionCamera_setEye);
	LUA_METHOD("setUp", lua_cocos2d_ActionCamera_setUp);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_OrbitCamera_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:initWithDuration");
	LUA_TRY_INVOKE_R(7, (static_cast<bool(cocos2d::OrbitCamera::*)(float, float, float, float, float, float, float)>(&cocos2d::OrbitCamera::initWithDuration)));
	LUA_INVOKE_FOOTER("7");
}
int lua_cocos2d_OrbitCamera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:create");
	LUA_TRY_INVOKE_R(7, (static_cast<cocos2d::OrbitCamera*(*)(float, float, float, float, float, float, float)>(&cocos2d::OrbitCamera::create)));
	LUA_SINVOKE_FOOTER("7");
}
int luaReg_Core_ccOrbitCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::OrbitCamera, "OrbitCamera", "cc.OrbitCamera",
		cocos2d::OrbitCamera, "cc.ActionCamera",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_OrbitCamera_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_OrbitCamera_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CardinalSplineTo_getPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:getPoints");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PointArray*(cocos2d::CardinalSplineTo::*)()>(&cocos2d::CardinalSplineTo::getPoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CardinalSplineTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::CardinalSplineTo::*)(float, cocos2d::PointArray*, float)>(&cocos2d::CardinalSplineTo::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_CardinalSplineTo_updatePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:updatePosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CardinalSplineTo::*)(const cocos2d::Vec2&)>(&cocos2d::CardinalSplineTo::updatePosition));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccCardinalSplineTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineTo, "CardinalSplineTo", "cc.CardinalSplineTo",
		cocos2d::CardinalSplineTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getPoints", lua_cocos2d_CardinalSplineTo_getPoints);
	LUA_METHOD("initWithDuration", lua_cocos2d_CardinalSplineTo_initWithDuration);
	LUA_METHOD("updatePosition", lua_cocos2d_CardinalSplineTo_updatePosition);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCardinalSplineBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineBy, "CardinalSplineBy", "cc.CardinalSplineBy",
		cocos2d::CardinalSplineBy, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
