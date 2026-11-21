#include "scripting/lua-bindings/auto/cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/ProtectedNode.h"
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
	luaL_getmetatable(L, "cc.GLViewImpl");
	if (lua_istable(L, -1)) {
		tolua_function(L, "create", lua_cc_base_GLViewImpl_create);
		tolua_function(L, "createWithRect", lua_cc_base_GLViewImpl_createWithRect);
	}
	lua_pop(L, 1);
	return 0;
}
