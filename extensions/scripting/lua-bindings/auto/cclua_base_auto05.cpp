#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_Core_ccEventFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventFocus, "EventFocus", "cc.EventFocus",
		cocos2d::Event, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerAcceleration, "EventListenerAcceleration", "cc.EventListenerAcceleration",
		cocos2d::EventListener, "cc.EventListener",
		nullptr, nullptr);
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
		cocos2d::EventListener, "cc.EventListener",
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
		cocos2d::EventListener, "cc.EventListener",
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
int lua_cocos2d_EventMouse_getMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getMouseButton");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventMouse::MouseButton(cocos2d::EventMouse::*)()const>(&cocos2d::EventMouse::getMouseButton));
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
int lua_cocos2d_EventMouse_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setCursorPosition");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventMouse::*)(float, float)>(&cocos2d::EventMouse::setCursorPosition));
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventMouse::*)(float, float)>(&cocos2d::EventMouse::setScrollData));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventMouse, "EventMouse", "cc.EventMouse",
		cocos2d::Event, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getCursorX", lua_cocos2d_EventMouse_getCursorX);
	LUA_METHOD("getCursorY", lua_cocos2d_EventMouse_getCursorY);
	LUA_METHOD("getMouseButton", lua_cocos2d_EventMouse_getMouseButton);
	LUA_METHOD("getScrollX", lua_cocos2d_EventMouse_getScrollX);
	LUA_METHOD("getScrollY", lua_cocos2d_EventMouse_getScrollY);
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
		cocos2d::EventListener, "cc.EventListener",
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
		cocos2d::EventListener, "cc.EventListener",
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
		cocos2d::EventListener, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerTouchAllAtOnce_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccActionCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionCamera, "ActionCamera", "cc.ActionCamera",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_OrbitCamera_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:initWithDuration");
	LUA_TRY_INVOKE_R(7, static_cast<bool(cocos2d::OrbitCamera::*)(float, float, float, float, float, float, float)>(&cocos2d::OrbitCamera::initWithDuration));
	LUA_INVOKE_FOOTER("7");
}
int lua_cocos2d_OrbitCamera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:create");
	LUA_TRY_INVOKE_R(7, static_cast<cocos2d::OrbitCamera*(*)(float, float, float, float, float, float, float)>(&cocos2d::OrbitCamera::create));
	LUA_SINVOKE_FOOTER("7");
}
int luaReg_Core_ccOrbitCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::OrbitCamera, "OrbitCamera", "cc.OrbitCamera",
		cocos2d::ActionCamera, "cc.ActionCamera",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_OrbitCamera_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_OrbitCamera_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCardinalSplineTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineTo, "CardinalSplineTo", "cc.CardinalSplineTo",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCardinalSplineBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineBy, "CardinalSplineBy", "cc.CardinalSplineBy",
		cocos2d::CardinalSplineTo, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
