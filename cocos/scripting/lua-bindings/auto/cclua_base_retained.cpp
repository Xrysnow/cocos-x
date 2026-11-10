#include "scripting/lua-bindings/auto/cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

// GLContextAttrs stubs, platform registration and merged aliases.




// Retained: existing unsupported layout/value stub.
int lua_cc_base_GLView_setGLContextAttrs(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        GLContextAttrs arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR GLContextAttrs
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_setGLContextAttrs'", nullptr);
            return 0;
        }
        cocos2d::GLView::setGLContextAttrs(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLView:setGLContextAttrs",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_setGLContextAttrs'.",&tolua_err);
#endif
    return 0;
}

// Retained: existing unsupported layout/value stub.
int lua_cc_base_GLView_getGLContextAttrs(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getGLContextAttrs'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::GLView::getGLContextAttrs();
        #pragma warning NO CONVERSION FROM NATIVE FOR GLContextAttrs;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLView:getGLContextAttrs",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getGLContextAttrs'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_GLViewImpl_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:create");
    LUA_TRY_INVOKE_R(1, ([](std::string_view name) { return cocos2d::GLViewImpl::create(name); }));
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, bool resizable) { return cocos2d::GLViewImpl::create(name, resizable); }));
#endif
    LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_base_GLViewImpl_createWithRect(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithRect");
    LUA_TRY_INVOKE_R(2, ([](std::string_view name, cocos2d::Rect rect) { return cocos2d::GLViewImpl::createWithRect(name, rect); }));
    LUA_TRY_INVOKE_R(3, ([](std::string_view name, cocos2d::Rect rect, float zoom) { return cocos2d::GLViewImpl::createWithRect(name, rect, zoom); }));
    LUA_TRY_INVOKE_R(4, ([](std::string_view name, cocos2d::Rect rect, float zoom, bool resizable) { return cocos2d::GLViewImpl::createWithRect(name, rect, zoom, resizable); }));
    LUA_SINVOKE_FOOTER("2,3,4");
}

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
int lua_register_cc_base_EventListenerController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerController, "EventListenerController", "cc.EventListenerController", cocos2d::EventListener, "cc.EventListener", nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_base_EventController_getControllerEventType(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getControllerEventType");
    LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventController::ControllerEventType(cocos2d::EventController::*)()const>(&cocos2d::EventController::getControllerEventType));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setConnectStatus(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setConnectStatus");
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventController::*)(bool)>(&cocos2d::EventController::setConnectStatus));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_isConnected(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:isConnected");
    LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventController::*)()const>(&cocos2d::EventController::isConnected));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_setKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:setKeyCode");
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventController::*)(int)>(&cocos2d::EventController::setKeyCode));
    LUA_INVOKE_FOOTER("1");
}

int lua_cc_base_EventController_getController(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getController");
    LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Controller*(cocos2d::EventController::*)()const>(&cocos2d::EventController::getController));
    LUA_INVOKE_FOOTER("0");
}

int lua_cc_base_EventController_getKeyCode(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventController", "cc.EventController:getKeyCode");
    LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::EventController::*)()const>(&cocos2d::EventController::getKeyCode));
    LUA_INVOKE_FOOTER("0");
}

int lua_register_cc_base_EventController(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventController, "EventController", "cc.EventController", cocos2d::Event, "cc.Event", nullptr, nullptr);
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
    LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::removeFromParent));
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::removeFromParentAndCleanup));
    LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_base_Node_removeAllChildrenWithCleanup(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeAllChildren");
    LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::removeAllChildren));
    LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::removeAllChildrenWithCleanup));
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
	luaL_getmetatable(L, "cc.GLView");
	if (lua_istable(L, -1)) {
		tolua_function(L, "setGLContextAttrs", lua_cc_base_GLView_setGLContextAttrs);
		tolua_function(L, "getGLContextAttrs", lua_cc_base_GLView_getGLContextAttrs);
	}
	lua_pop(L, 1);
	luaL_getmetatable(L, "cc.GLViewImpl");
	if (lua_istable(L, -1)) {
		tolua_function(L, "create", lua_cc_base_GLViewImpl_create);
		tolua_function(L, "createWithRect", lua_cc_base_GLViewImpl_createWithRect);
	}
	lua_pop(L, 1);
	return 0;
}
