#include "scripting/lua-bindings/auto/cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

// Platform registration and merged aliases.

int lua_cc_base_GLViewImpl_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:create");
    LUA_TRY_INVOKE_R(1, ([](std::string_view name) { return cc::GLViewImpl::create(name); }));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, bool resizable) { return cc::GLViewImpl::create(name, resizable); }));
#endif
    LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_base_GLViewImpl_createWithRect(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithRect");
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, cc::Rect rect) { return cc::GLViewImpl::createWithRect(name, rect); }));
    LUA_TRY_INVOKE_R(3, ([](std::string_view name, cc::Rect rect, float zoom) { return cc::GLViewImpl::createWithRect(name, rect, zoom); }));
#if CC_TARGET_PLATFORM != CC_PLATFORM_IOS
    LUA_TRY_INVOKE_R(4, ([](std::string_view name, cc::Rect rect, float zoom, bool resizable) { return cc::GLViewImpl::createWithRect(name, rect, zoom, resizable); }));
    LUA_SINVOKE_FOOTER("2,3,4");
#else
    LUA_SINVOKE_FOOTER("2,3");
#endif
}

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
int lua_register_cc_base_EventListenerController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerController, "EventListenerController", "cc.EventListenerController", cc::EventListener, "cc.EventListener", nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_base_EventController_getControllerEventType(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getControllerEventType");
    LUA_TRY_INVOKE_R(0, static_cast<cc::EventController::ControllerEventType(cc::EventController::*)()const>(&cc::EventController::getControllerEventType));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setConnectStatus(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setConnectStatus");
    LUA_TRY_INVOKE(1, static_cast<void(cc::EventController::*)(bool)>(&cc::EventController::setConnectStatus));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_isConnected(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:isConnected");
    LUA_TRY_INVOKE_R(0, static_cast<bool(cc::EventController::*)()const>(&cc::EventController::isConnected));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setKeyCode");
    LUA_TRY_INVOKE(1, static_cast<void(cc::EventController::*)(int)>(&cc::EventController::setKeyCode));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_getController(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getController");
    LUA_TRY_INVOKE_R(0, static_cast<cc::Controller*(cc::EventController::*)()const>(&cc::EventController::getController));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_getKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getKeyCode");
    LUA_TRY_INVOKE_R(0, static_cast<int(cc::EventController::*)()const>(&cc::EventController::getKeyCode));
    LUA_INVOKE_FOOTER("0");
}

int lua_register_cc_base_EventController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventController, "EventController", "cc.EventController", cc::Event, "cc.Event", nullptr, nullptr);
	LUA_METHOD("getControllerEventType", lua_cc_base_EventController_getControllerEventType);
	LUA_METHOD("setConnectStatus", lua_cc_base_EventController_setConnectStatus);
	LUA_METHOD("isConnected", lua_cc_base_EventController_isConnected);
	LUA_METHOD("setKeyCode", lua_cc_base_EventController_setKeyCode);
	LUA_METHOD("getController", lua_cc_base_EventController_getController);
	LUA_METHOD("getKeyCode", lua_cc_base_EventController_getKeyCode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int lua_cc_base_Node_removeFromParentAndCleanup(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeFromParent");
    LUA_TRY_INVOKE(0, static_cast<void(cc::Node::*)()>(&cc::Node::removeFromParent));
    LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(bool)>(&cc::Node::removeFromParentAndCleanup));
    LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_base_Node_removeAllChildrenWithCleanup(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeAllChildren");
    LUA_TRY_INVOKE(0, static_cast<void(cc::Node::*)()>(&cc::Node::removeAllChildren));
    LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(bool)>(&cc::Node::removeAllChildrenWithCleanup));
    LUA_INVOKE_FOOTER("0,1");
}


int register_all_cc_base_retained(lua_State* L)
{
    luaL_getmetatable(L, "cc.Node");
    if (lua_istable(L, -1)) {
        tolua_function(L, "removeFromParent", lua_cc_base_Node_removeFromParentAndCleanup);
        tolua_function(L, "removeAllChildren", lua_cc_base_Node_removeAllChildrenWithCleanup);
    }
    lua_pop(L, 1);
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
	lua_register_cc_base_EventListenerController(L);
	lua_register_cc_base_EventController(L);
#endif
	luaL_getmetatable(L, "cc.GLViewImpl");
	if (lua_istable(L, -1)) {
		tolua_function(L, "create", lua_cc_base_GLViewImpl_create);
		tolua_function(L, "createWithRect", lua_cc_base_GLViewImpl_createWithRect);
	}
	lua_pop(L, 1);
	return 0;
}
