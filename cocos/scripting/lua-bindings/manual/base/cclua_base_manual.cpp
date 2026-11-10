/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021-2022 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "scripting/lua-bindings/manual/base/cclua_base_manual.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#if defined(_MSC_VER) || defined(__MINGW32__)
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
#endif

#include "2d/CCActionCamera.h"
#include "2d/CCActionCatmullRom.h"
#include "2d/CCActionGrid.h"
#include "2d/CCActionInterval.h"
#include "2d/CCAtlasNode.h"
#include "2d/CCCamera.h"
#include "2d/CCMenu.h"
#include "2d/CCMenuItem.h"
#include "2d/CCMotionStreak.h"
#include "2d/CCParticleBatchNode.h"
#include "2d/CCParticleSystem.h"
#include "2d/CCScene.h"
#include "2d/CCSpriteBatchNode.h"
#include "2d/CCFastTMXLayer.h"
#include "2d/CCFastTMXTiledMap.h"
#include "2d/CCRenderTexture.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerKeyboard.h"
#include "base/CCEventListenerMouse.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCProperties.h"
#include "base/CCScheduler.h"
#include "base/CCUserDefault.h"
#include "base/ccUtils.h"
#include "platform/CCApplication.h"
#include "platform/CCDevice.h"
#include "platform/CCFileUtils.h"
#include "platform/CCGLView.h"
#include "renderer/CCTextureCache.h"
#include "renderer/ccShaders.h"

void LuaNode::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    LuaEngine::getInstance()->getLuaStack()->executeCallback([&]() -> int {
        int handler =
            ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::LUANODE_DRAW);
        if (0 != handler)
        {
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            auto* L         = stack->getLuaState();

            lua_newtable(L);
            for (int i = 0; i < 16; i++)
            {
                stack->pushFloat(transform.m[i]);
                lua_rawseti(L, -2, i + 1);
            }

            stack->pushFloat(_globalZOrder);
            stack->executeFunctionByHandler(handler, 2);
            stack->clean();
        }
        return 0;
    });
}

static void tolua_reg_LuaNode_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "cc.LuaNode");
}

static int tolua_collect_LuaNode(lua_State* tolua_S)
{
    LuaNode* self = (LuaNode*)tolua_tousertype(tolua_S, 1, 0);
    Mtolua_delete(self);
    return 0;
}

#ifndef TOLUA_DISABLE_tolua_Cocos2d_LuaNode_create00
static int tolua_Cocos2d_LuaNode_create00(lua_State* tolua_S)
{
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.LuaNode", 0, &tolua_err) || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
    #endif
    {
        LuaNode* luaNode = new LuaNode();
        luaNode->autorelease();
        int nID     = (int)luaNode->_ID;
        int* pLuaID = &luaNode->_luaID;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)luaNode, "cc.LuaNode");
    }
    return 1;
    #ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'create'.", &tolua_err);
    return 0;
    #endif
}
#endif

static int tolua_Cocos2d_LuaNode_registerScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.LuaNode", 0, &tolua_err) ||
        (tolua_isvaluenil(tolua_S, 2, &tolua_err) || !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err)) ||
        !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        LuaNode* luaNode     = (LuaNode*)tolua_tousertype(tolua_S, 1, 0);
        LUA_FUNCTION handler = (toluafix_ref_function(tolua_S, 2, 0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)luaNode, handler,
                                                          ScriptHandlerMgr::HandlerType::LUANODE_DRAW);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'registerScriptDrawHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_LuaNode_unregisterScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.LuaNode", 0, &tolua_err) || !tolua_isnoobj(tolua_S, 2, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        LuaNode* luaNode = (LuaNode*)tolua_tousertype(tolua_S, 1, 0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)luaNode,
                                                             ScriptHandlerMgr::HandlerType::LUANODE_DRAW);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'unregisterScriptDrawhandler'.", &tolua_err);
    return 0;
#endif
}

TOLUA_API int tolua_luanode_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_LuaNode_type(tolua_S);
    tolua_module(tolua_S, "cc", 0);
    tolua_beginmodule(tolua_S, "cc");
    tolua_cclass(tolua_S, "LuaNode", "cc.LuaNode", "cc.Node", tolua_collect_LuaNode);
    tolua_beginmodule(tolua_S, "LuaNode");
    tolua_function(tolua_S, "create", tolua_Cocos2d_LuaNode_create00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}

int register_luanode_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    lua_pushstring(tolua_S, "cc.LuaNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "registerScriptDrawHandler");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_LuaNode_registerScriptDrawHandler00);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptDrawHandler");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_LuaNode_unregisterScriptDrawHandler00);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
    return 1;
}

// Shape the existing variadic Lua factories into one shared container input.
static void pack_factory_arguments(lua_State* L, int argc)
{
    lua_createtable(L, argc, 0);
    for (int i = 0; i < argc; ++i)
    {
        lua_pushvalue(L, i + 2);
        lua_rawseti(L, -2, i + 1);
    }
    lua_replace(L, 2);
    lua_settop(L, 2);
}

static int tolua_cocos2d_Menu_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.Menu", "cc.Menu:create");
    LUA_TRY_INVOKE_R(0, []() { return cocos2d::Menu::create(); });
    if (argc > 0)
    {
        pack_factory_arguments(lua_S, argc);
        LUA_TRY_INVOKE_R(argc, [](const cocos2d::Vector<cocos2d::MenuItem*>& items) {
            return cocos2d::Menu::createWithArray(items);
        });
    }
    LUA_SINVOKE_FOOTER("at least 1");
}

static int tocclua_Menu_alignItemsInRows(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc   = 0;
    Menu* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Menu", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<Menu*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'cclua_Menu_alignItemsInRows'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        ValueVector items;
        if (luavals_variadic_to_ccvaluevector(tolua_S, argc, &items))
        {
            self->alignItemsInRowsWithArray(items);
        }
        return 0;
    }

    luaL_error(tolua_S,
               "'alignItemsInRows' has wrong number of arguments in tocclua_Menu_alignItemsInRows: %d, was "
               "expecting %d\n",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'alignItemsInRows'.\n", &tolua_err);
#endif
    return 0;
}

static int tocclua_Menu_alignItemsInColumns(lua_State* tolua_S)
{

    if (nullptr == tolua_S)
        return 0;

    int argc   = 0;
    Menu* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Menu", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<Menu*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_Menu_alignItemsInColumns'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        ValueVector items;
        if (luavals_variadic_to_ccvaluevector(tolua_S, argc, &items))
        {
            self->alignItemsInColumnsWithArray(items);
        }
        return 0;
    }

    luaL_error(tolua_S,
               "'alignItemsInColumns' has wrong number of arguments in tocclua_Menu_alignItemsInColumns: %d, "
               "was expecting %d\n",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_Menu_alignItemsInColumns'.\n", &tolua_err);
#endif
    return 0;
}

static int tolua_cocos2d_MenuItemToggle_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:create");
    if (argc > 0)
    {
        pack_factory_arguments(lua_S, argc);
        LUA_TRY_INVOKE_R(argc, [](const cocos2d::Vector<cocos2d::MenuItem*>& items) {
            auto* menu = cocos2d::MenuItemToggle::create();
            for (auto* item : items)
                menu->addSubItem(item);
            menu->setSelectedIndex(0);
            return menu;
        });
    }
    LUA_SINVOKE_FOOTER("at least 1");
}

static int tolua_cocos2d_MenuItem_registerScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc       = 0;
    MenuItem* cobj = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.MenuItem", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler'\n", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler,
                                                          ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.MenuItem:registerScriptTapHandler", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_unregisterScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc       = 0;
    MenuItem* cobj = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.MenuItem", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)cobj, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.MenuItem:unregisterScriptTapHandler", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler'.", &tolua_err);
    return 0;
#endif
}

static int executeScriptTouchHandler(Layer* layer, EventTouch::EventCode eventType, Touch* touch, Event* event)
{
    TouchScriptData data(eventType, layer, touch, event);
    ScriptEvent scriptEvent(kTouchEvent, &data);
    return ScriptEngineManager::sendEventToLua(scriptEvent);
}

static int executeScriptTouchesHandler(Layer* layer,
                                       EventTouch::EventCode eventType,
                                       const std::vector<Touch*>& touches,
                                       Event* event)
{
    TouchesScriptData data(eventType, layer, touches, event);
    ScriptEvent scriptEvent(kTouchesEvent, &data);
    return ScriptEngineManager::sendEventToLua(scriptEvent);
}

static void setTouchEnabledForLayer(Layer* layer, bool enabled)
{
    if (nullptr == layer)
        return;

    // TODO:
}

// Only for v2.x lua compatibility
static int cclua_Layer_setTouchPriority(lua_State* L)
{
    return 0;
}

static int cclua_Layer_setTouchEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setTouchEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        setTouchEnabledForLayer(self, enabled);
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setTouchEnabled", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setTouchEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_isTouchEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_isTouchEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        // TODO:
        tolua_pushboolean(L, 0);
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isTouchEnabled", argc, 0);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_isTouchEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_setTouchMode(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setTouchMode'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        int32_t mode = (int32_t)tolua_tonumber(L, 2, 0);
        // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setTouchMode", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setTouchMode'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_getTouchMode(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_getTouchMode'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        int32_t ret = 0;
        tolua_pushnumber(L, (lua_Number)ret);  // TODO:

        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:getTouchMode", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_getTouchMode'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_setSwallowsTouches(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setSwallowsTouches'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif

        bool swallowsTouches = tolua_toboolean(L, 2, 0);
        // TODO:

        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setSwallowsTouches", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setSwallowsTouches'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_isSwallowsTouches(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_isSwallowsTouches'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        lua_pushboolean(L, 0);  // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isSwallowsTouches", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_isSwallowsTouches'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_setKeyboardEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setKeyboardEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setKeyboardEnabled", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setKeyboardEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_isKeyboardEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_isKeyboardEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isKeyboardEnabled", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_isKeyboardEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_setAccelerometerEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setAccelerometerEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setAccelerometerEnabled", argc,
               1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setAccelerometerEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_isAccelerometerEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_isAccelerometerEnabled'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        // TODO:
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isAccelerometerEnabled", argc,
               0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_isAccelerometerEnabled'.", &tolua_err);
    return 0;
#endif
}

static int cclua_Layer_setAccelerometerInterval(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_Layer_setAccelerometerInterval'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        float interval = (float)tolua_tonumber(L, 2, 0);
        Device::setAccelerometerInterval(interval);
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setAccelerometerInterval", argc,
               1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_Layer_setAccelerometerInterval'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc >= 1 && argc <= 4)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        bool isMultiTouches  = false;
        int priority         = 0;
        bool swallowTouches  = true;

        if (argc >= 2)
        {
#if CC_DEBUG >= 1
            if (!tolua_isboolean(tolua_S, 3, 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            isMultiTouches = (bool)tolua_toboolean(tolua_S, 3, false);
        }

        if (argc >= 3)
        {
#if CC_DEBUG >= 1
            if (!tolua_isnumber(tolua_S, 4, 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            priority = (int)tolua_tonumber(tolua_S, 4, 0);
        }

        if (argc == 4)
        {
#if CC_DEBUG >= 1
            if (!tolua_isboolean(tolua_S, 5, 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            swallowTouches = (bool)tolua_toboolean(tolua_S, 5, true);
        }

        Touch::DispatchMode touchesMode = Touch::DispatchMode::ALL_AT_ONCE;
        if (!isMultiTouches)
            touchesMode = Touch::DispatchMode::ONE_BY_ONE;

        // TODO:
        // ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler,
        // ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:registerScriptTouchHandler", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (0 == argc)
    {
        // TODO:
        // ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:unregisterScriptTouchHandler", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptKeypadHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:registerScriptKeypadHandler", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_registerScriptKeypadHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptKeypadHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (0 == argc)
    {
        // TODO:
        // ScriptHandlerMgr::getInstance()->removeObjectHandler(self, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:unregisterScriptKeypadHandler", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_unregisterScriptKeypadHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptAccelerateHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptAccelerateHandler'\n",
                    NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler,
                                                          ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:registerScriptAccelerateHandler", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_registerScriptAccelerateHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptAccelerateHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc    = 0;
    Layer* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Layer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptAccelerateHandler'\n",
                    NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (0 == argc)
    {
        // TODO:
        // ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self,
        // ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Layer:unregisterScriptAccelerateHandler", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Layer_unregisterScriptAccelerateHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Scheduler_scheduleScriptFunc(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc        = 0;
    Scheduler* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Scheduler", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (3 == argc)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) || !tolua_isboolean(tolua_S, 4, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler   = toluafix_ref_function(tolua_S, 2, 0);
        float interval         = (float)tolua_tonumber(tolua_S, 3, 0);
        bool paused            = (bool)tolua_toboolean(tolua_S, 4, 0);
        unsigned int tolua_ret = (unsigned int)self->scheduleScriptFunc(handler, interval, paused);
        tolua_pushnumber(tolua_S, (lua_Number)tolua_ret);
        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Scheduler:scheduleScriptFunc",
               argc, 3);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Scheduler_unscheduleScriptEntry(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc        = 0;
    Scheduler* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Scheduler", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif

        unsigned int scheduleScriptEntryID = ((unsigned int)tolua_tonumber(tolua_S, 2, 0));
        self->unscheduleScriptEntry(scheduleScriptEntryID);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Scheduler:unscheduleScriptEntry", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Sequence_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.Sequence", "cc.Sequence:create");
    if (argc > 0)
    {
        if (!(argc == 1 && lua_istable(lua_S, 2)))
            pack_factory_arguments(lua_S, argc);
        LUA_TRY_INVOKE_R(argc, [](const cocos2d::Vector<cocos2d::FiniteTimeAction*>& items) {
            return cocos2d::Sequence::create(items);
        });
    }
    LUA_SINVOKE_FOOTER("at least 1");
}

// The data table remains a Lua upvalue, so copies of the owned callback keep
// its identity until the final action/clone releases the callable.
static int callfunc_with_data(lua_State* L)
{
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_pushvalue(L, 1);
    lua_pushvalue(L, lua_upvalueindex(2));
    lua_call(L, 2, 0);
    return 0;
}

static int tolua_cocos2d_CallFunc_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.CallFunc", "cc.CallFunc:create");
    if (argc == 1 || argc == 2)
    {
        if (!lua_isfunction(lua_S, 2))
            arg_cur = 1;
        else if (argc == 2 && !lua_istable(lua_S, 3))
            arg_cur = 2;
        else
        {
            if (argc == 2)
            {
                lua_pushvalue(lua_S, 2);
                lua_pushvalue(lua_S, 3);
                lua_pushcclosure(lua_S, callfunc_with_data, 2);
                lua_replace(lua_S, 2);
                lua_settop(lua_S, 2);
            }
            LUA_TRY_INVOKE_R(1, [](std::function<void(cocos2d::Node*)> callback) -> cocos2d::CallFunc* {
                return cocos2d::LuaCallFunc::create(callback);
            });
            LUA_TRY_INVOKE_R(2, [](std::function<void(cocos2d::Node*)> callback) -> cocos2d::CallFunc* {
                return cocos2d::LuaCallFunc::create(callback);
            });
        }
    }
    LUA_SINVOKE_FOOTER("1,2");
}

static int tolua_cocos2d_Node_registerScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc   = 0;
    Node* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Node", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Node_registerScriptHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
            goto tolua_lerror;
#endif

        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::NODE);

        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:registerScriptHandler",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Node_registerScriptHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unregisterScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc   = 0;
    Node* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Node", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Node_unregisterScriptHandler'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::NODE);
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:unregisterScriptHandler",
               argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Node_unregisterScriptHandler'.", &tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc   = 0;
    Node* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Node", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
            goto tolua_lerror;
#endif

        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        int priority         = 0;
        if (lua::luaval_to_native(tolua_S, 3, &priority, "cc.Node:scheduleUpdateWithPriorityLua"))
        {
            self->scheduleUpdateWithPriorityLua(handler, priority);
        }
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.Node:scheduleUpdateWithPriorityLua", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unscheduleUpdate(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    int argc   = 0;
    Node* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.Node", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tolua_cocos2d_Node_unscheduleUpdate'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (0 == argc)
    {
        self->unscheduleUpdate();
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:unscheduleUpdate", argc,
               0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Node_unscheduleUpdate'.", &tolua_err);
    return 0;
#endif
}

#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
static int cclua_Scene_setNavMeshDebugCamera(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMeshDebugCamera");
    LUA_TRY_INVOKE(1, &cocos2d::Scene::setNavMeshDebugCamera);
    LUA_INVOKE_FOOTER("1");
}
static int cclua_Scene_setNavMesh(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMesh");
    LUA_TRY_INVOKE(1, &cocos2d::Scene::setNavMesh);
    LUA_INVOKE_FOOTER("1");
}
static int cclua_Scene_getNavMesh(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getNavMesh");
    LUA_TRY_INVOKE_R(0, &cocos2d::Scene::getNavMesh);
    LUA_INVOKE_FOOTER("0");
}
#endif

static int tolua_cocos2d_Spawn_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.Spawn", "cc.Spawn:create");
    if (argc > 0)
    {
        if (!(argc == 1 && lua_istable(lua_S, 2)))
            pack_factory_arguments(lua_S, argc);
        LUA_TRY_INVOKE_R(argc, [](const cocos2d::Vector<cocos2d::FiniteTimeAction*>& items) {
            return cocos2d::Spawn::create(items);
        });
    }
    LUA_SINVOKE_FOOTER("at least 1");
}

// Native spline factories consume a PointArray; Lua keeps its array input.
static cocos2d::PointArray* make_control_points(const std::vector<cocos2d::Vec2>& values)
{
    auto* points = cocos2d::PointArray::create(values.size());
    if (points)
        for (const auto& value : values)
            points->addControlPoint(value);
    return points;
}

static int lua_cocos2d_CardinalSplineBy_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.CardinalSplineBy", "cc.CardinalSplineBy:create");
    if (argc == 3 && lua_istable(lua_S, 3) && lua_objlen(lua_S, 3) == 0)
        arg_cur = 2;
    else
    {
        LUA_TRY_INVOKE_R(3, [](float duration, const std::vector<cocos2d::Vec2>& values, float tension) {
            return cocos2d::CardinalSplineBy::create(duration, make_control_points(values), tension);
        });
    }
    LUA_SINVOKE_FOOTER("3");
}

static int tolua_cocos2d_CatmullRomBy_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.CatmullRomBy", "cc.CatmullRomBy:create");
    if (argc == 2 && lua_istable(lua_S, 3) && lua_objlen(lua_S, 3) == 0)
        arg_cur = 2;
    else
    {
        LUA_TRY_INVOKE_R(2, [](float duration, const std::vector<cocos2d::Vec2>& values) {
            return cocos2d::CatmullRomBy::create(duration, make_control_points(values));
        });
    }
    LUA_SINVOKE_FOOTER("2");
}

static int tolua_cocos2d_CatmullRomTo_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.CatmullRomTo", "cc.CatmullRomTo:create");
    if (argc == 2 && lua_istable(lua_S, 3) && lua_objlen(lua_S, 3) == 0)
        arg_cur = 2;
    else
    {
        LUA_TRY_INVOKE_R(2, [](float duration, const std::vector<cocos2d::Vec2>& values) {
            return cocos2d::CatmullRomTo::create(duration, make_control_points(values));
        });
    }
    LUA_SINVOKE_FOOTER("2");
}

static int tocclua_DrawNode_drawPolygon(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawPolygon");
    if (argc == 5)
    {
        bool bounds = false;
        int results = 0;
        ok = lua::invoke_binding<false, true>(lua_S, arg_cur,
            [&](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& points,
                int count, const cocos2d::Color4F& fill, float border, const cocos2d::Color4F& color) {
                bounds = count > 0 && static_cast<size_t>(count) <= points.size();
                if (bounds) node->drawPolygon(points.data(), count, fill, border, color);
            }, results);
        if (ok && bounds) { lua_settop(lua_S, 1); return 1; }
        if (ok) arg_cur = 2;
    }
    LUA_INVOKE_FOOTER("5");
}

static int tocclua_DrawNode_drawSolidPoly(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSolidPoly");
    if (argc == 3)
    {
        bool bounds = false;
        int results = 0;
        ok = lua::invoke_binding<false, true>(lua_S, arg_cur,
            [&](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& points,
                unsigned int count, const cocos2d::Color4F& color) {
                bounds = count > 0 && static_cast<size_t>(count) <= points.size();
                if (bounds) node->drawSolidPoly(points.data(), count, color);
            }, results);
        if (ok && bounds) { lua_settop(lua_S, 1); return 1; }
        if (ok) arg_cur = 2;
    }
    LUA_INVOKE_FOOTER("3");
}

static int tocclua_DrawNode_drawPoly(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawPoly");
    if (argc == 4)
    {
        bool bounds = false;
        int results = 0;
        ok = lua::invoke_binding<false, true>(lua_S, arg_cur,
            [&](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& points,
                unsigned int count, bool close, const cocos2d::Color4F& color) {
                bounds = count > 0 && static_cast<size_t>(count) <= points.size();
                if (bounds) node->drawPoly(points.data(), count, close, color);
            }, results);
        if (ok && bounds) { lua_settop(lua_S, 1); return 1; }
        if (ok) arg_cur = 2;
    }
    LUA_INVOKE_FOOTER("4");
}

static int tocclua_DrawNode_drawCardinalSpline(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCardinalSpline");
    if (argc == 4 && lua_istable(lua_S, 2) && lua_objlen(lua_S, 2) == 0)
        arg_cur = 1;
    else
    {
        LUA_TRY_INVOKE(4, [](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& values, float tension, unsigned int segments, const cocos2d::Color4F& color) {
            node->drawCardinalSpline(make_control_points(values), tension, segments, color);
        });
    }
    LUA_INVOKE_FOOTER("4");
}

static int tocclua_DrawNode_drawCatmullRom(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCatmullRom");
    if (argc == 3 && lua_istable(lua_S, 2) && lua_objlen(lua_S, 2) == 0)
        arg_cur = 1;
    else
    {
        LUA_TRY_INVOKE(3, [](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& values, unsigned int segments, const cocos2d::Color4F& color) {
            node->drawCatmullRom(make_control_points(values), segments, color);
        });
    }
    LUA_INVOKE_FOOTER("3");
}

static int tocclua_DrawNode_drawPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawPoints");
    bool bounds = false;
    int results = 0;
    if (argc == 3)
        ok = lua::invoke_binding<false, true>(lua_S, arg_cur,
            [&](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& points,
                unsigned int count, const cocos2d::Color4F& color) {
                bounds = count > 0 && count <= points.size();
                if (bounds) node->drawPoints(points.data(), count, color);
            }, results);
    else if (argc == 4)
        ok = lua::invoke_binding<false, true>(lua_S, arg_cur,
            [&](cocos2d::DrawNode* node, const std::vector<cocos2d::Vec2>& points,
                unsigned int count, float size, const cocos2d::Color4F& color) {
                bounds = count > 0 && count <= points.size();
                if (bounds) node->drawPoints(points.data(), count, size, color);
            }, results);
    if (ok && bounds) { lua_settop(lua_S, 1); return 1; }
    if (ok) arg_cur = 2;
    LUA_INVOKE_FOOTER("3,4");
}

static int tocclua_LayerMultiplex_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:create");
    if (argc > 0)
    {
        pack_factory_arguments(lua_S, argc);
        LUA_TRY_INVOKE_R(argc, [](const cocos2d::Vector<cocos2d::Node*>& items) {
            return cocos2d::LayerMultiplex::createWithArray(items);
        });
    }
    LUA_SINVOKE_FOOTER("at least 1");
}

static int tocclua_FileUtils_getDataFromFile(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc        = 0;
    FileUtils* self = nullptr;
    bool ok         = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.FileUtils", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<FileUtils*>(tolua_tousertype(tolua_S, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_FileUtils_getDataFromFile'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (1 == argc)
    {
        const char* arg0;
        std::string arg0_tmp;
        ok &= lua::luaval_to_native(tolua_S, 2, &arg0_tmp, "cc.FileUtils:getDataFromFile");
        arg0 = arg0_tmp.c_str();
        if (ok)
        {
            auto data = FileUtils::getInstance()->getDataFromFile(arg0);
            if (!data.isNull())
                lua_pushlstring(tolua_S, reinterpret_cast<const char*>(data.getBytes()),
                                static_cast<size_t>(data.getSize()));

            return 1;
        }
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.FileUtils:getDataFromFile",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_FileUtils_getDataFromFile'.", &tolua_err);
    return 0;
#endif
}

static int tocclua_Texture2D_setTexParameters(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setTexParameters");
    LUA_TRY_INVOKE(4, [](cocos2d::Texture2D* texture, cocos2d::backend::SamplerFilter min,
        cocos2d::backend::SamplerFilter mag, cocos2d::backend::SamplerAddressMode s,
        cocos2d::backend::SamplerAddressMode t) {
        texture->setTexParameters(cocos2d::Texture2D::TexParams(min, mag, s, t));
    });
    LUA_INVOKE_FOOTER("4");
}

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
static int cclua_Scene_getPhysics3DWorld(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysics3DWorld");
    LUA_TRY_INVOKE_R(0, &cocos2d::Scene::getPhysics3DWorld);
    LUA_INVOKE_FOOTER("0");
}
static int cclua_Scene_setPhysics3DDebugCamera(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setPhysics3DDebugCamera");
    LUA_TRY_INVOKE(1, &cocos2d::Scene::setPhysics3DDebugCamera);
    LUA_INVOKE_FOOTER("1");
}
#endif

static void extendScene(lua_State* L)
{
    lua_pushstring(L, "cc.Scene");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
        tolua_function(L, "getPhysics3DWorld", cclua_Scene_getPhysics3DWorld);
        tolua_function(L, "setPhysics3DDebugCamera", cclua_Scene_setPhysics3DDebugCamera);
#endif
#if CC_USE_NAVMESH
        tolua_function(L, "setNavMeshDebugCamera", cclua_Scene_setNavMeshDebugCamera);
        tolua_function(L, "setNavMesh", cclua_Scene_setNavMesh);
        tolua_function(L, "getNavMesh", cclua_Scene_getNavMesh);
#endif
    }
    lua_pop(L, 1);
}

static void extendTexture2D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Texture2D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "setTexParameters");
        lua_pushcfunction(tolua_S, tocclua_Texture2D_setTexParameters);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItem(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItem");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "registerScriptTapHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_MenuItem_registerScriptTapHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptTapHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_MenuItem_unregisterScriptTapHandler);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemToggle(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItemToggle");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_MenuItemToggle_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenu(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Menu");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Menu_create);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "alignItemsInRows");
        lua_pushcfunction(tolua_S, tocclua_Menu_alignItemsInRows);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "alignItemsInColumns");
        lua_pushcfunction(tolua_S, tocclua_Menu_alignItemsInColumns);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Node");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "registerScriptHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Node_registerScriptHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Node_unregisterScriptHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "scheduleUpdateWithPriorityLua");
        lua_pushcfunction(tolua_S, tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unscheduleUpdate");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Node_unscheduleUpdate);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Layer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "registerScriptTouchHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptTouchHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptTouchHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptTouchHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);

        tolua_function(tolua_S, "setTouchEnabled", cclua_Layer_setTouchEnabled);
        tolua_function(tolua_S, "isTouchEnabled", cclua_Layer_isTouchEnabled);
        tolua_function(tolua_S, "setTouchMode", cclua_Layer_setTouchMode);
        tolua_function(tolua_S, "getTouchMode", cclua_Layer_getTouchMode);
        tolua_function(tolua_S, "setSwallowsTouches", cclua_Layer_setSwallowsTouches);
        tolua_function(tolua_S, "isSwallowsTouches", cclua_Layer_isSwallowsTouches);
        tolua_function(tolua_S, "setKeyboardEnabled", cclua_Layer_setKeyboardEnabled);
        tolua_function(tolua_S, "isKeyboardEnabled", cclua_Layer_isKeyboardEnabled);
        tolua_function(tolua_S, "setAccelerometerEnabled", cclua_Layer_setAccelerometerEnabled);
        tolua_function(tolua_S, "isAccelerometerEnabled", cclua_Layer_isAccelerometerEnabled);
        tolua_function(tolua_S, "setAccelerometerInterval", cclua_Layer_setAccelerometerInterval);
    }
    lua_pop(tolua_S, 1);
}

static void extendScheduler(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Scheduler");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "scheduleScriptFunc");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Scheduler_scheduleScriptFunc);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unscheduleScriptEntry");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Scheduler_unscheduleScriptEntry);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSequence(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Sequence");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Sequence_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCallFunc(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CallFunc");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_CallFunc_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSpawn(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Spawn");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Spawn_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCardinalSplineBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CardinalSplineBy");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, lua_cocos2d_CardinalSplineBy_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCatmullRomBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CatmullRomBy");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_CatmullRomBy_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCatmullRomTo(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CatmullRomTo");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tolua_cocos2d_CatmullRomTo_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendDrawNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.DrawNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "drawPolygon");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawPolygon);
        lua_rawset(tolua_S, -3);

        lua_pushstring(tolua_S, "drawSolidPoly");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawSolidPoly);
        lua_rawset(tolua_S, -3);

        lua_pushstring(tolua_S, "drawPoly");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawPoly);
        lua_rawset(tolua_S, -3);

        lua_pushstring(tolua_S, "drawCardinalSpline");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawCardinalSpline);
        lua_rawset(tolua_S, -3);

        lua_pushstring(tolua_S, "drawCatmullRom");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawCatmullRom);
        lua_rawset(tolua_S, -3);

        lua_pushstring(tolua_S, "drawPoints");
        lua_pushcfunction(tolua_S, tocclua_DrawNode_drawPoints);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendLayerMultiplex(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.LayerMultiplex");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "create");
        lua_pushcfunction(tolua_S, tocclua_LayerMultiplex_create);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendFileUtils(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S, "getDataFromFile");
        lua_pushcfunction(tolua_S, tocclua_FileUtils_getDataFromFile);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

NS_CC_BEGIN
EventListenerAcceleration* LuaEventListenerAcceleration::create()
{
    EventListenerAcceleration* eventAcceleration = new EventListenerAcceleration();
    if (eventAcceleration->init([=](Acceleration* acc, Event* event) {
            LuaEventAccelerationData listenerData((void*)acc, event);
            BasicScriptData data(eventAcceleration, (void*)&listenerData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::EVENT_ACC, (void*)&data);
        }))
    {
        eventAcceleration->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(eventAcceleration);
    }
    return eventAcceleration;
}

NS_CC_END

static int tocclua_LuaEventListenerAcceleration_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc = 0;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerAcceleration", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler                          = toluafix_ref_function(tolua_S, 2, 0);
        cocos2d::EventListenerAcceleration* tolua_ret = cocos2d::LuaEventListenerAcceleration::create();
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)tolua_ret, handler,
                                                          ScriptHandlerMgr::HandlerType::EVENT_ACC);
        int ID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret, "cc.EventListenerAcceleration");

        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerAcceleration:create", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_LuaEventListenerAcceleration_create'.", &tolua_err);
    return 0;
#endif
}

static void extendEventListenerAcceleration(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerAcceleration");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "create", tocclua_LuaEventListenerAcceleration_create);
    }
    lua_pop(tolua_S, 1);
}

static void cloneKeyboardHandler(const EventListenerKeyboard* src,
                                 EventListenerKeyboard* dst,
                                 ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;

    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler =
            cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED:
        {
            dst->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                LuaEventKeyboarData listenerData((int)keyCode, event);
                BasicScriptData data((void*)dst, (void*)&listenerData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED:
        {
            dst->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                LuaEventKeyboarData listenerData((int)keyCode, event);
                BasicScriptData data((void*)dst, (void*)&listenerData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        default:
            break;
        }
    }
}

static int tocclua_EventListenerKeyboard_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                    = 0;
    EventListenerKeyboard* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerKeyboard", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerKeyboard*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_EventListenerKeyboard_clone'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        cocos2d::EventListenerKeyboard* tolua_ret = cocos2d::EventListenerKeyboard::create();
        if (nullptr == tolua_ret)
            return 0;

        cloneKeyboardHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED);
        cloneKeyboardHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED);

        int ID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret, "cc.EventListenerKeyboard");

        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerKeyboard:clone",
               argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerKeyboard_clone'.", &tolua_err);
    return 0;
#endif
}

static int tocclua_EventListenerKeyboard_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                    = 0;
    EventListenerKeyboard* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerKeyboard", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerKeyboard*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,
                    "invalid 'self' in function 'tocclua_EventListenerKeyboard_registerScriptHandler'\n",
                    nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif

        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::HandlerType type =
            static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED:
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            self->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                LuaEventKeyboarData listenerData((int)keyCode, event);
                BasicScriptData data((void*)self, (void*)&listenerData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED:
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            self->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                LuaEventKeyboarData listenerData((int)keyCode, event);
                BasicScriptData data((void*)self, (void*)&listenerData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        default:
            break;
        }

        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerKeyboard:registerScriptHandler", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerKeyboard_registerScriptHandler'.",
                &tolua_err);
    return 0;
#endif
}

static void extendEventListenerKeyboard(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerKeyboard");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "registerScriptHandler", tocclua_EventListenerKeyboard_registerScriptHandler);
        tolua_function(tolua_S, "clone", tocclua_EventListenerKeyboard_clone);
    }
    lua_pop(tolua_S, 1);
}

static void cloneTouchOneByOneHandler(const EventListenerTouchOneByOne* src,
                                      EventListenerTouchOneByOne* dst,
                                      ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;

    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler =
            cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN:
        {
            dst->onTouchBegan = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)dst, (void*)&touchData);
                return LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED:
        {
            dst->onTouchMoved = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)dst, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED:
        {
            dst->onTouchEnded = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)dst, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED:
        {
            dst->onTouchCancelled = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)dst, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        default:
            break;
        }
    }
}

static int tocclua_EventListenerTouchOneByOne_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                         = 0;
    EventListenerTouchOneByOne* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchOneByOne", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerTouchOneByOne*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_EventListenerTouchOneByOne_clone'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        cocos2d::EventListenerTouchOneByOne* tolua_ret = cocos2d::EventListenerTouchOneByOne::create();
        if (nullptr == tolua_ret)
            return 0;

        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED);
        tolua_ret->setSwallowTouches(self->isSwallowTouches());

        int ID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret, "cc.EventListenerTouchOneByOne");

        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerTouchOneByOne:create", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerTouchOneByOne_clone'.", &tolua_err);
    return 0;
#endif
}

static int tocclua_EventListenerTouchOneByOne_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                         = 0;
    EventListenerTouchOneByOne* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchOneByOne", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerTouchOneByOne*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,
                    "invalid 'self' in function 'tocclua_EventListenerTouchOneByOne_registerScriptHandler'\n",
                    nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::HandlerType type =
            static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN:
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);

            self->onTouchBegan = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)self, (void*)&touchData);
                return LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED:
        {
            self->onTouchMoved = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)self, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED:
        {
            self->onTouchEnded = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)self, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED:
        {
            self->onTouchCancelled = [=](Touch* touch, Event* event) {
                LuaEventTouchData touchData(touch, event);
                BasicScriptData data((void*)self, (void*)&touchData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        default:
            break;
        }
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerTouchOneByOne:registerScriptHandler", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerTouchOneByOne_registerScriptHandler'.",
                &tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchOneByOne(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerTouchOneByOne");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "registerScriptHandler",
                       tocclua_EventListenerTouchOneByOne_registerScriptHandler);
        tolua_function(tolua_S, "clone", tocclua_EventListenerTouchOneByOne_clone);
    }
    lua_pop(tolua_S, 1);
}

static void cloneTouchAllAtOnceHandler(const EventListenerTouchAllAtOnce* src,
                                       EventListenerTouchAllAtOnce* dst,
                                       ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;

    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler =
            cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN:
        {
            dst->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)dst, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED:
        {
            dst->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)dst, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED:
        {
            dst->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)dst, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED:
        {
            dst->onTouchesCancelled = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)dst, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        default:
            break;
        }
    }
}

static int tocclua_EventListenerTouchAllAtOnce_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                          = 0;
    EventListenerTouchAllAtOnce* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchAllAtOnce", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerTouchAllAtOnce*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_EventListenerTouchAllAtOnce_clone'\n",
                    nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        cocos2d::EventListenerTouchAllAtOnce* tolua_ret = cocos2d::EventListenerTouchAllAtOnce::create();
        if (nullptr == tolua_ret)
            return 0;

        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED);

        int ID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret, "cc.EventListenerTouchAllAtOnce");

        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerTouchAllAtOnce:clone", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerTouchAllAtOnce_clone'.", &tolua_err);
    return 0;
#endif
}

static int tocclua_EventListenerTouchAllAtOnce_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                          = 0;
    EventListenerTouchAllAtOnce* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchAllAtOnce", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerTouchAllAtOnce*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,
                    "invalid 'self' in function 'tocclua_EventListenerTouchAllAtOnce_registerScriptHandler'\n",
                    nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::HandlerType type =
            static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN:
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);

            self->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)self, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED:
        {
            self->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)self, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED:
        {
            self->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)self, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED:
        {
            self->onTouchesCancelled = [=](const std::vector<Touch*>& touches, Event* event) {
                LuaEventTouchesData touchesData(touches, event);
                BasicScriptData data((void*)self, (void*)&touchesData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        default:
            break;
        }
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerTouchAllAtOnce:registerScriptHandler", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerTouchAllAtOnce_registerScriptHandler'.",
                &tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchAllAtOnce(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerTouchAllAtOnce");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "registerScriptHandler",
                       tocclua_EventListenerTouchAllAtOnce_registerScriptHandler);
        tolua_function(tolua_S, "clone", tocclua_EventListenerTouchAllAtOnce_clone);
    }
    lua_pop(tolua_S, 1);
}

static void cloneMouseHandler(const EventListenerMouse* src,
                              EventListenerMouse* dst,
                              ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;

    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler =
            cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN:
        {
            dst->onMouseDown = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)dst, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP:
        {
            dst->onMouseUp = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)dst, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE:
        {
            dst->onMouseMove = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)dst, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL:
        {
            dst->onMouseScroll = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)dst, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        default:
            break;
        }
    }
}

static int tocclua_EventListenerMouse_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                 = 0;
    EventListenerMouse* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerMouse", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerMouse*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_EventListenerMouse_clone'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        cocos2d::EventListenerMouse* tolua_ret = cocos2d::EventListenerMouse::create();
        if (nullptr == tolua_ret)
            return 0;

        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP);

        int ID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret, "cc.EventListenerMouse");

        return 1;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerMouse:clone", argc,
               0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerMouse_clone'.", &tolua_err);
    return 0;
#endif
}

static int tocclua_EventListenerMouse_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    int argc                 = 0;
    EventListenerMouse* self = nullptr;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerMouse", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<EventListenerMouse*>(tolua_tousertype(tolua_S, 1, 0));
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'tocclua_EventListenerMouse_registerScriptHandler'\n",
                    nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
        ScriptHandlerMgr::HandlerType type =
            static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));

        switch (type)
        {
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN:
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);

            self->onMouseDown = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)self, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP:
        {
            self->onMouseUp = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)self, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE:
        {
            self->onMouseMove = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)self, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL:
        {
            self->onMouseScroll = [=](Event* event) {
                LuaEventMouseData mouseData(event);
                BasicScriptData data((void*)self, (void*)&mouseData);
                LuaEngine::getInstance()->handleEvent(type, (void*)&data);
            };

            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
        }
        break;
        default:
            break;
        }
        return 0;
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n",
               "cc.EventListenerMouse:registerScriptHandler", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tocclua_EventListenerMouse_registerScriptHandler'.", &tolua_err);
    return 0;
#endif
}

static void extendEventListenerMouse(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerMouse");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "registerScriptHandler", tocclua_EventListenerMouse_registerScriptHandler);
        tolua_function(tolua_S, "clone", tocclua_EventListenerMouse_clone);
    }
    lua_pop(tolua_S, 1);
}

static int cclua_Console_send(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Console", "cc.Console:send");
    LUA_TRY_INVOKE(2, [](cocos2d::Console*, int descriptor, const std::string& data) {
        ::send(descriptor, data.data(), data.size(), 0);
    });
    LUA_INVOKE_FOOTER("2");
}

static int cclua_Console_wait(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Console", "cc.Console:wait");
    LUA_TRY_INVOKE(1, [](cocos2d::Console*, int seconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(int64_t(seconds) * 1000));
    });
    LUA_INVOKE_FOOTER("1");
}

static int cclua_Console_addCommand(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Console", "cc.Console:addCommand");
    if (argc == 2 && lua_isnil(lua_S, 3))
        arg_cur = 2;
    else
    {
        LUA_TRY_INVOKE(2, ([](cocos2d::Console* console, const cocos2d::ValueMap& metadata,
            std::function<void(int, std::string_view)> callback) {
            const auto name = metadata.find("name");
            const auto help = metadata.find("help");
            cocos2d::Console::Command command = {
                name != metadata.end() ? name->second.asString() : std::string(),
                help != metadata.end() ? help->second.asString() : std::string(),
                std::move(callback)};
            console->addCommand(command);
        }));
    }
    LUA_INVOKE_FOOTER("2");
}

static void extendConsole(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Console");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "wait", cclua_Console_wait);
        tolua_function(tolua_S, "send", cclua_Console_send);
        tolua_function(tolua_S, "addCommand", cclua_Console_addCommand);
    }
    lua_pop(tolua_S, 1);
}

static int cclua_OrbitCamera_sphericalRadius(lua_State* tolua_S)
{
    int argc                   = 0;
    cocos2d::OrbitCamera* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.OrbitCamera", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = (cocos2d::OrbitCamera*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!self)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_OrbitCamera_sphericalRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 3)
    {
#if CC_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err) || !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif

        float newRadius = (float)tolua_tonumber(tolua_S, 2, 0);
        float zenith    = (float)tolua_tonumber(tolua_S, 3, 0);
        float azimuth   = (float)tolua_tonumber(tolua_S, 4, 0);

        self->sphericalRadius(&newRadius, &zenith, &azimuth);

        tolua_pushnumber(tolua_S, (lua_Number)newRadius);
        tolua_pushnumber(tolua_S, (lua_Number)zenith);
        tolua_pushnumber(tolua_S, (lua_Number)azimuth);

        return 3;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OrbitCamera:sphericalRadius",
               argc, 3);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_OrbitCamera_sphericalRadius'.", &tolua_err);
#endif

    return 0;
}

static void extendOrbitCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.OrbitCamera");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "sphericalRadius", cclua_OrbitCamera_sphericalRadius);
    }
    lua_pop(tolua_S, 1);
}

int cclua_TMXLayer_getTileGIDAt(lua_State* tolua_S)
{
    int argc                = 0;
    cocos2d::TMXLayer* cobj = nullptr;
    bool ok                 = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.TMXLayer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXLayer*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_TMXLayer_getTileGIDAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= lua::luaval_to_native(tolua_S, 2, &arg0, "cc.TMXLayer:getTileGIDAt");
        if (!ok)
            return 0;
        unsigned int ret = cobj->getTileGIDAt(arg0);
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushnumber(tolua_S, (lua_Number)0);
        return 2;
    }
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        int arg1;

        ok &= lua::luaval_to_native(tolua_S, 2, &arg0, "cc.TMXLayer:getTileGIDAt");
        ok &= lua::luaval_to_native(tolua_S, 3, &arg1, "cc.TMXLayer:getTileGIDAt");

        if (!ok)
            return 0;

        unsigned int ret = cobj->getTileGIDAt(arg0, (cocos2d::TMXTileFlags*)&arg1);
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushnumber(tolua_S, (lua_Number)arg1);
        return 2;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayer:getTileGIDAt", argc,
               1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_TMXLayer_getTileGIDAt'.", &tolua_err);
#endif

    return 0;
}

int cclua_TMXLayer_setTiles(lua_State* tolua_S)
{
    int argc                = 0;
    cocos2d::TMXLayer* cobj = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.TMXLayer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXLayer*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_TMXLayer_setTiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        uint32_t* arg0 = nullptr;
#if CC_DEBUG >= 1
        if (!tolua_istable(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif

        size_t len = lua_objlen(tolua_S, 2);
        if (len == 0)
        {
            luaL_error(tolua_S, "Table's len equal 0");
            return 0;
        }
        arg0 = new uint32_t[len];
        for (size_t i = 1; i <= len; i++)
        {
            arg0[i - 1] = (uint32_t)tolua_tofieldnumber(tolua_S, 2, i, 0);
        }

        cobj->setTiles(arg0);

        CC_SAFE_DELETE_ARRAY(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayer:setTiles", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_TMXLayer_setTiles'.", &tolua_err);
#endif

    return 0;
}

static void extendTMXLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.TMXLayer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "getTileGIDAt", cclua_TMXLayer_getTileGIDAt);
        tolua_function(tolua_S, "setTiles", cclua_TMXLayer_setTiles);
    }
    lua_pop(tolua_S, 1);
}

static int cclua_FastTMXLayer_getTileGIDAt(lua_State* tolua_S)
{
    int argc                    = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok                     = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.FastTMXLayer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_FastTMXLayer_getTileGIDAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= lua::luaval_to_native(tolua_S, 2, &arg0, "cc.FastTMXLayer:getTileGIDAt");
        if (!ok)
            return 0;
        int ret = cobj->getTileGIDAt(arg0);
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushnumber(tolua_S, (lua_Number)0);
        return 2;
    }
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        int arg1 = 0;

        ok &= lua::luaval_to_native(tolua_S, 2, &arg0, "cc.FastTMXLayer:getTileGIDAt");
        ok &= lua::luaval_to_native(tolua_S, 3, &arg1, "cc.FastTMXLayer:getTileGIDAt");

        if (!ok)
            return 0;

        unsigned int ret = cobj->getTileGIDAt(arg0, (cocos2d::TMXTileFlags*)&arg1);
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushnumber(tolua_S, (lua_Number)arg1);
        return 2;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getTileGIDAt",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_FastTMXLayer_getTileGIDAt'.", &tolua_err);
#endif

    return 0;
}

static void extendFastTMXLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FastTMXLayer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "getTileGIDAt", cclua_FastTMXLayer_getTileGIDAt);
    }
    lua_pop(tolua_S, 1);
}

int cclua_Application_isIOS64bit(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Application", "cc.Application:isIOS64bit");
    const auto platformCheck = [](cocos2d::Application* application) {
#if defined(__LP64__)
        return application->getTargetPlatform() == cocos2d::Application::Platform::iOS;
#else
        return false;
#endif
    };
    LUA_TRY_INVOKE_R(0, platformCheck);
    LUA_INVOKE_FOOTER("0");
}

int cclua_Application_is64BitMobileDevice(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Application", "cc.Application:is64BitMobileDevice");
    const auto platformCheck = [](cocos2d::Application* application) {
#if defined(__arm64__) || defined(__aarch64__)
        const auto platform = application->getTargetPlatform();
        return platform == cocos2d::Application::Platform::iOS || platform == cocos2d::Application::Platform::Android;
#else
        return false;
#endif
    };
    LUA_TRY_INVOKE_R(0, platformCheck);
    LUA_INVOKE_FOOTER("0");
}

static void extendApplication(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Application");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "isIOS64bit", cclua_Application_isIOS64bit);
        tolua_function(tolua_S, "is64BitMobileDevice", cclua_Application_is64BitMobileDevice);
    }
    lua_pop(tolua_S, 1);
}

int cclua_Camera_unproject(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:unproject");
    LUA_TRY_INVOKE_R(1, [](cocos2d::Camera* camera, const cocos2d::Vec3& point) {
        return camera->unproject(point);
    });
    LUA_TRY_INVOKE_R(3, [](cocos2d::Camera* camera, const cocos2d::Size& viewport,
        cocos2d::Vec3 point, cocos2d::Vec3 result) {
        camera->unproject(viewport, &point, &result);
        return result;
    });
    LUA_INVOKE_FOOTER("1,3");
}

static void extendCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Camera");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "unproject", cclua_Camera_unproject);
    }
    lua_pop(tolua_S, 1);
}

int cclua_get_PipelineDescriptor_programState(lua_State* tolua_S)
{
    cocos2d::PipelineDescriptor* cobj = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.PipelineDescriptor", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::PipelineDescriptor*)tolua_tousertype(tolua_S, 1, 0);
#if CC_DEBUG >= 1
    if (nullptr == cobj)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'cclua_get_PipelineDescriptor_programState'\n",
                    nullptr);
        return 0;
    }
#endif
    tolua_pushusertype(tolua_S, cobj->programState, "ccb.ProgramState");
    return 1;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_get_PipelineDescriptor_programState'.", &tolua_err);
    return 0;
#endif
}

int cclua_set_PipelineDescriptor_programState(lua_State* tolua_S)
{
    int argc                          = 0;
    cocos2d::PipelineDescriptor* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.PipelineDescriptor", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = (cocos2d::PipelineDescriptor*)tolua_tousertype(tolua_S, 1, 0);
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S, "invalid 'self' in function 'cclua_set_PipelineDescriptor_programState'\n",
                    nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (1 == argc)
    {
        cocos2d::backend::ProgramState* programState = nullptr;
        luaval_to_object<cocos2d::backend::ProgramState>(tolua_S, 2, "ccb.ProgramState", &programState,
                                                         "cclua_set_PipelineDescriptor_programState");
        self->programState = programState;
        return 0;
    }

    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_set_PipelineDescriptor_programState'.", &tolua_err);
    return 0;
#endif
}

static void extendPipelineDescriptor(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.PipelineDescriptor");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_variable(tolua_S, "programState", cclua_get_PipelineDescriptor_programState,
                       cclua_set_PipelineDescriptor_programState);
    }
    lua_pop(tolua_S, 1);
}

//extern int cclua_Director_setStatsDisplay(lua_State* tolua_S);
//static void extendDirector(lua_State* tolua_S)
//{
//    lua_pushstring(tolua_S, "cc.Director");
//    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
//    if (lua_istable(tolua_S, -1))
//    {
//        lua_pushstring(tolua_S, "setDisplayStats");
//        lua_pushcfunction(tolua_S, cclua_Director_setStatsDisplay);
//        lua_rawset(tolua_S, -3);
//    }
//    lua_pop(tolua_S, 1);
//}

int register_all_cc_manual(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    extendNode(tolua_S);
    extendScene(tolua_S);
    extendLayer(tolua_S);
    extendMenuItem(tolua_S);
    extendMenuItemToggle(tolua_S);
    extendMenu(tolua_S);
    extendScheduler(tolua_S);
    extendSequence(tolua_S);
    extendCallFunc(tolua_S);
    extendSpawn(tolua_S);
    extendCardinalSplineBy(tolua_S);
    extendCatmullRomBy(tolua_S);
    extendCatmullRomTo(tolua_S);
    extendDrawNode(tolua_S);
    extendLayerMultiplex(tolua_S);
    extendFileUtils(tolua_S);
    extendTexture2D(tolua_S);
    extendEventListenerKeyboard(tolua_S);
    extendEventListenerTouchOneByOne(tolua_S);
    extendEventListenerTouchAllAtOnce(tolua_S);
    extendEventListenerMouse(tolua_S);
    extendEventListenerAcceleration(tolua_S);
    extendPipelineDescriptor(tolua_S);

    extendConsole(tolua_S);
    extendOrbitCamera(tolua_S);
    extendTMXLayer(tolua_S);
    extendFastTMXLayer(tolua_S);
    extendApplication(tolua_S);
    extendCamera(tolua_S);
    return 0;
}

static int tolua_cocos2d_utils_captureNode(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.utils", "cc.utils:captureNode");
    if ((argc == 2 || argc == 3) && lua_isnil(lua_S, 3))
        arg_cur = 2;
    else
    {
        LUA_TRY_INVOKE(2, [](cocos2d::Node* node, std::function<void(cocos2d::RefPtr<cocos2d::Image>)> callback) {
            cocos2d::utils::captureNode(node, std::move(callback));
        });
        LUA_TRY_INVOKE(3, &cocos2d::utils::captureNode);
    }
    LUA_SINVOKE_FOOTER("2,3");
}

static int tolua_cocos2d_utils_captureScreen(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.utils", "cc.utils:captureScreen");
    if (argc == 2 && lua_isnil(lua_S, 2))
        arg_cur = 1;
    else
    {
        LUA_TRY_INVOKE(2, static_cast<void(*)(std::function<void(bool, std::string_view)>, std::string_view)>(&cocos2d::utils::captureScreen));
    }
    LUA_SINVOKE_FOOTER("2");
}

static int tolua_cocos2d_utils_findChildren(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.utils", "cc.utils:findChildren");
    LUA_TRY_INVOKE_R(2, [](cocos2d::Node* node, std::string_view name) {
        return cocos2d::utils::findChildren(*node, name);
    });
    LUA_SINVOKE_FOOTER("2");
}

static int tolua_cocos2d_utils_findChild(lua_State* lua_S)
{
    LUA_GINVOKE_HEADER("cc.utils", "cc.utils.findChild");
    LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Node*(*)(cocos2d::Node*, std::string_view)>(&cocos2d::utils::findChild));
    LUA_GINVOKE_FOOTER("2");
}

int register_all_cc_module_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    tolua_open(tolua_S);
    tolua_module(tolua_S, "cc", 0);
    tolua_beginmodule(tolua_S, "cc");
    tolua_module(tolua_S, "utils", 0);
    tolua_beginmodule(tolua_S, "utils");
    tolua_function(tolua_S, "captureNode", tolua_cocos2d_utils_captureNode);
    tolua_function(tolua_S, "captureScreen", tolua_cocos2d_utils_captureScreen);
    tolua_function(tolua_S, "findChildren", tolua_cocos2d_utils_findChildren);
    tolua_function(tolua_S, "findChild", tolua_cocos2d_utils_findChild);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);

    return 0;
}

static int tolua_cocos2d_Mat4_getInversed(lua_State* tolua_S)
{
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S, 1, 0, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::Mat4 mat;
        bool ok = lua::luaval_to_native(tolua_S, 1, &mat);
        if (ok)
        {
            lua::native_to_luaval(tolua_S, mat.getInversed());
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'mat4_getInversed'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Mat4_transformVector(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 2 || argc == 3) /* Allow 3 arguments for compatibility with old version */
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 mat;
            cocos2d::Vec4 vector;
            cocos2d::Vec4 dst;
            ok &= lua::luaval_to_native(tolua_S, 1, &mat);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 2, &vector);
            if (!ok)
                return 0;

            mat.transformVector(vector, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }
    else if (argc == 5 || argc == 6) /* Allow 6 arguments for compatibility with old version */
    {
        /*
         float x, float y, float z, float w, Vec3* dst
         */
#if CC_DEBUG >= 1
        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) || !tolua_isnumber(tolua_S, 4, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 5, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 mat;
            float x, y, z, w;
            cocos2d::Vec3 dst;
            ok &= lua::luaval_to_native(tolua_S, 1, &mat);
            if (!ok)
                return 0;

            x = tolua_tonumber(tolua_S, 2, 0);
            y = tolua_tonumber(tolua_S, 3, 0);
            z = tolua_tonumber(tolua_S, 4, 0);
            w = tolua_tonumber(tolua_S, 5, 0);

            mat.transformVector(x, y, z, w, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'mat4_transformVector'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Mat4_decompose(lua_State* tolua_S)
{
#if CC_DEBUG >= 1
    tolua_Error tolua_err;

    if (!tolua_istable(tolua_S, 1, 0, &tolua_err) ||
        (!lua_isnil(tolua_S, 2) && !tolua_istable(tolua_S, 2, 0, &tolua_err)) ||
        (!lua_isnil(tolua_S, 3) && !tolua_istable(tolua_S, 3, 0, &tolua_err)) ||
        (!lua_isnil(tolua_S, 4) && !tolua_istable(tolua_S, 4, 0, &tolua_err)))
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::Mat4 mat;
        cocos2d::Vec3 scale;
        cocos2d::Quaternion rotation;
        cocos2d::Vec3 translation;
        bool ok = true;

        ok &= lua::luaval_to_native(tolua_S, 1, &mat);
        if (!ok)
            return 0;

        if (lua_isnil(tolua_S, 2) && !lua_isnil(tolua_S, 3) && !lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 3, &rotation);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 4, &translation);
            if (!ok)
                return 0;

            mat.decompose(nullptr, &rotation, &translation);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua::native_to_luaval(tolua_S, rotation);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua::native_to_luaval(tolua_S, translation);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        if (lua_isnil(tolua_S, 2) && lua_isnil(tolua_S, 3) && !lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 4, &translation);
            if (!ok)
                return 0;

            mat.decompose(nullptr, nullptr, &translation);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua::native_to_luaval(tolua_S, translation);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        if (!lua_isnil(tolua_S, 2) && lua_isnil(tolua_S, 3) && !lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 2, &scale);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 4, &translation);
            if (!ok)
                return 0;

            mat.decompose(&scale, nullptr, &translation);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua::native_to_luaval(tolua_S, scale);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua::native_to_luaval(tolua_S, translation);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        if (!lua_isnil(tolua_S, 2) && lua_isnil(tolua_S, 3) && lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 2, &scale);
            if (!ok)
                return 0;

            mat.decompose(&scale, nullptr, nullptr);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua::native_to_luaval(tolua_S, scale);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        if (!lua_isnil(tolua_S, 2) && !lua_isnil(tolua_S, 3) && lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 2, &scale);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 3, &rotation);
            if (!ok)
                return 0;

            mat.decompose(&scale, &rotation, nullptr);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua::native_to_luaval(tolua_S, scale);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua::native_to_luaval(tolua_S, rotation);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        if (lua_isnil(tolua_S, 2) && !lua_isnil(tolua_S, 3) && lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 3, &rotation);
            if (!ok)
                return 0;

            mat.decompose(nullptr, &rotation, nullptr);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua::native_to_luaval(tolua_S, rotation);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua_pushnil(tolua_S);
            lua_rawset(tolua_S, -3);
        }

        if (!lua_isnil(tolua_S, 2) && !lua_isnil(tolua_S, 3) && !lua_isnil(tolua_S, 4))
        {
            ok &= lua::luaval_to_native(tolua_S, 2, &scale);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 3, &rotation);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 4, &translation);
            if (!ok)
                return 0;

            mat.decompose(&scale, &rotation, &translation);

            lua_newtable(tolua_S);

            lua_pushstring(tolua_S, "scale");
            lua::native_to_luaval(tolua_S, scale);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "rotation");
            lua::native_to_luaval(tolua_S, rotation);
            lua_rawset(tolua_S, -3);

            lua_pushstring(tolua_S, "translation");
            lua::native_to_luaval(tolua_S, translation);
            lua_rawset(tolua_S, -3);

            return 1;
        }

        return 0;
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'mat4_decompose'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Vec3_cross(lua_State* tolua_S)
{
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    if (2 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec3 cobj;
            cocos2d::Vec3 v;

            bool ok = true;

            ok &= lua::luaval_to_native(tolua_S, 1, &cobj);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 2, &v);
            if (!ok)
                return 0;

            cobj.cross(v);

            lua::native_to_luaval(tolua_S, cobj);
            return 1;
        }
    }
    else if (3 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err) ||
            !tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec3 v1;
            cocos2d::Vec3 v2;
            cocos2d::Vec3 dst;
            bool ok = true;

            ok &= lua::luaval_to_native(tolua_S, 1, &v1);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 2, &v2);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 3, &dst);
            if (!ok)
                return 0;

            cocos2d::Vec3::cross(v1, v2, &dst);

            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'MathUtil_gcrossVec3'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Mat4_multiply(lua_State* tolua_S)
{
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::Mat4 mat1;
        bool ok = lua::luaval_to_native(tolua_S, 1, &mat1);
        if (!ok)
            return 0;

        cocos2d::Mat4 mat2;
        ok = lua::luaval_to_native(tolua_S, 2, &mat2);
        if (!ok)
            return 0;

        cocos2d::Mat4 ret = mat1 * mat2;
        lua::native_to_luaval(tolua_S, ret);
        return 1;
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'mat4_multiply'.", &tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Mat4_translate(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_istable(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 mat;
            cocos2d::Vec3 vec3;
            ok &= lua::luaval_to_native(tolua_S, 1, &mat);
            if (!ok)
                return 0;

            ok &= lua::luaval_to_native(tolua_S, 2, &vec3);
            if (!ok)
                return 0;

            mat.translate(vec3);
            lua::native_to_luaval(tolua_S, mat);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Mat4_translate'.", &tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Mat4_createRotationZ(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 2)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_isnumber(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 mat;
            float angle;
            ok &= lua::luaval_to_native(tolua_S, 1, &mat);
            if (!ok)
                return 0;
            angle = (float)lua_tonumber(tolua_S, 2);
            cocos2d::Mat4::createRotationZ(angle, &mat);
            lua::native_to_luaval(tolua_S, mat);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Mat4_createRotationZ'.", &tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Mat4_setIdentity(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 mat;
            ok &= lua::luaval_to_native(tolua_S, 1, &mat);
            if (!ok)
                return 0;
            mat.setIdentity();
            lua::native_to_luaval(tolua_S, mat);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Mat4_setIdentity'.", &tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Mat4_createTranslation(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 3)
    {
#if CC_DEBUG >= 1

        if (!tolua_isnumber(tolua_S, 1, 0, &tolua_err) || !tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 dst;
            float xTranslation = (float)lua_tonumber(tolua_S, 1);
            float yTranslation = (float)lua_tonumber(tolua_S, 2);
            float zTranslation = (float)lua_tonumber(tolua_S, 3);

            cocos2d::Mat4::createTranslation(xTranslation, yTranslation, zTranslation, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }
    else if (argc == 1)
    {
#if CC_DEBUG >= 1
        if (!tolua_istable(tolua_S, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec3 translation;
            cocos2d::Mat4 dst;

            ok &= lua::luaval_to_native(tolua_S, 1, &translation, "cc.Mat4.createTranslation");
            if (!ok)
                return 0;

            cocos2d::Mat4::createTranslation(translation, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Mat4_createTranslation'.", &tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Mat4_createRotation(lua_State* tolua_S)
{
    bool ok  = true;
    int argc = lua_gettop(tolua_S);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Quaternion quat;
            cocos2d::Mat4 dst;

            ok &= lua::luaval_to_native(tolua_S, 1, &quat, "cc.Mat4.createRotation");
            if (!ok)
                return 0;

            cocos2d::Mat4::createRotation(quat, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }
    else if (argc == 2)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(tolua_S, 1, 0, &tolua_err) || !tolua_isnumber(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec3 axis;
            cocos2d::Mat4 dst;

            ok &= lua::luaval_to_native(tolua_S, 1, &axis, "cc.Mat4.createRotation");
            if (!ok)
                return 0;

            float angle = (float)tolua_tonumber(tolua_S, 2, 0);

            cocos2d::Mat4::createRotation(axis, angle, &dst);
            lua::native_to_luaval(tolua_S, dst);
            return 1;
        }
    }

    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'tolua_cocos2d_Mat4_createRotation'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Vec2_new(lua_State* L)
{
    lua::native_to_luaval(L, Vec2{static_cast<float>(lua_tonumber(L, 1)), static_cast<float>(lua_tonumber(L, 2))});
    return 1;
}

static int tolua_cocos2d_Vec3_new(lua_State* L)
{
    lua::native_to_luaval(L, Vec3{static_cast<float>(lua_tonumber(L, 1)), static_cast<float>(lua_tonumber(L, 2)),
                                  static_cast<float>(lua_tonumber(L, 3))});
    return 1;
}

static int tolua_cocos2d_Vec4_new(lua_State* L)
{
    lua::native_to_luaval(L, Vec4{static_cast<float>(lua_tonumber(L, 1)), static_cast<float>(lua_tonumber(L, 2)),
                                  static_cast<float>(lua_tonumber(L, 3)), static_cast<float>(lua_tonumber(L, 4))});
    return 1;
}

int register_all_cc_math_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    tolua_module(tolua_S, nullptr, 0);
    tolua_beginmodule(tolua_S, nullptr);
    tolua_function(tolua_S, "mat4_getInversed", tolua_cocos2d_Mat4_getInversed);
    tolua_function(tolua_S, "mat4_transformVector", tolua_cocos2d_Mat4_transformVector);
    tolua_function(tolua_S, "mat4_decompose", tolua_cocos2d_Mat4_decompose);
    tolua_function(tolua_S, "mat4_multiply", tolua_cocos2d_Mat4_multiply);
    tolua_function(tolua_S, "mat4_translate", tolua_cocos2d_Mat4_translate);
    tolua_function(tolua_S, "mat4_createRotationZ", tolua_cocos2d_Mat4_createRotationZ);
    tolua_function(tolua_S, "mat4_setIdentity", tolua_cocos2d_Mat4_setIdentity);
    tolua_function(tolua_S, "mat4_createTranslation", tolua_cocos2d_Mat4_createTranslation);
    tolua_function(tolua_S, "mat4_createRotation", tolua_cocos2d_Mat4_createRotation);
    tolua_function(tolua_S, "vec3_cross", tolua_cocos2d_Vec3_cross);
    tolua_function(tolua_S, "vec2_new", tolua_cocos2d_Vec2_new);
    tolua_function(tolua_S, "vec3_new", tolua_cocos2d_Vec3_new);
    tolua_function(tolua_S, "vec4_new", tolua_cocos2d_Vec4_new);
    tolua_endmodule(tolua_S);
    return 0;
}

int register_all_cc_shaders_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
#define set_lua_field(field)             \
    do                                   \
    {                                    \
        lua_pushstring(tolua_S, #field); \
        lua_pushstring(tolua_S, field);  \
        lua_rawset(tolua_S, -3);         \
    } while (false)

    tolua_open(tolua_S);
    tolua_module(tolua_S, "cc", 0);
    tolua_beginmodule(tolua_S, "cc");
    set_lua_field(positionColor_vert);
    set_lua_field(positionColor_frag);
    set_lua_field(positionTexture_vert);
    set_lua_field(positionTexture_frag);
    set_lua_field(positionTextureColor_vert);
    set_lua_field(positionTextureColor_frag);
    set_lua_field(positionTextureColorAlphaTest_frag);
    set_lua_field(label_normal_frag);
    set_lua_field(label_distanceNormal_frag);
    set_lua_field(labelOutline_frag);
    set_lua_field(labelDistanceFieldGlow_frag);
    set_lua_field(lineColor3D_frag);
    set_lua_field(lineColor3D_vert);
    set_lua_field(positionColorLengthTexture_vert);
    set_lua_field(positionColorLengthTexture_frag);
    set_lua_field(positionColorTextureAsPointsize_vert);
    set_lua_field(position_vert);
    set_lua_field(layer_radialGradient_frag);
    set_lua_field(grayScale_frag);
    set_lua_field(positionUColor_vert);
    set_lua_field(dualSampler_frag);
    set_lua_field(dualSampler_gray_frag);
    set_lua_field(cameraClear_vert);
    set_lua_field(cameraClear_frag);
    set_lua_field(CC3D_color_frag);
    set_lua_field(CC3D_colorNormal_frag);
    set_lua_field(CC3D_colorNormalTexture_frag);
    set_lua_field(CC3D_colorTexture_frag);
    set_lua_field(CC3D_particleTexture_frag);
    set_lua_field(CC3D_particleColor_frag);
    set_lua_field(CC3D_particle_vert);
    set_lua_field(CC3D_positionNormalTexture_vert);
    set_lua_field(CC3D_skinPositionNormalTexture_vert);
    set_lua_field(CC3D_positionTexture_vert);
    set_lua_field(CC3D_skinPositionTexture_vert);
    set_lua_field(CC3D_skybox_frag);
    set_lua_field(CC3D_skybox_vert);
    set_lua_field(CC3D_terrain_frag);
    set_lua_field(CC3D_terrain_vert);
    tolua_endmodule(tolua_S);
    return 0;
}

static int tolua_cocos2d_bytearray_vec2(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec2 arg;
            ok &= lua::luaval_to_native(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_vec3(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec3 arg;
            ok &= lua::luaval_to_native(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_vec4(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Vec4 arg;
            ok &= lua::luaval_to_native(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_mat4(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            cocos2d::Mat4 arg;
            ok &= lua::luaval_to_native(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_int(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_isnumber(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            int arg;
            ok &= lua::luaval_to_native(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_float(lua_State* L)
{
    bool ok  = true;
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_isnumber(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            float arg;
            ok &= luaval_to_float(L, 1, &arg, "tolua_cocos2d_bytearray_template");
            if (!ok)
                return 0;

            lua_pop(L, 1);
            lua_newtable(L);
            uint8_t* bytes = (uint8_t*)&arg;
            for (auto idx = 0; idx < sizeof(arg); idx++)
            {
                lua_pushnumber(L, bytes[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_template'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_intv(lua_State* L)
{
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            int size = lua_objlen(L, 1);
            std::vector<uint8_t> arg(size * sizeof(int));

            int e;
            int* p = (int*)arg.data();

            for (auto idx = 0; idx < size; idx++)
            {
                lua_rawgeti(L, 1, idx + 1);
                lua::luaval_to_native(L, -1, &e, "tolua_cocos2d_bytearray_elev");
                p[idx] = e;
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            lua_newtable(L);
            for (size_t idx = 0; idx < arg.size(); idx++)
            {
                lua_pushnumber(L, arg[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_elev'.", &tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_bytearray_floatv(lua_State* L)
{
    int argc = lua_gettop(L);

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    if (argc == 1)
    {
#if CC_DEBUG >= 1

        if (!tolua_istable(L, 1, 0, &tolua_err))
            goto tolua_lerror;
        else
#endif
        {
            int size = lua_objlen(L, 1);
            std::vector<uint8_t> arg(size * sizeof(float));

            float e;
            float* p = (float*)arg.data();

            for (auto idx = 0; idx < size; idx++)
            {
                lua_rawgeti(L, 1, idx + 1);
                luaval_to_float(L, -1, &e, "tolua_cocos2d_bytearray_elev");
                p[idx] = e;
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            lua_newtable(L);
            for (auto idx = 0; idx < arg.size(); idx++)
            {
                lua_pushnumber(L, arg[idx]);
                lua_rawseti(L, 1, idx + 1);
            }
            return 1;
        }
    }
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'tolua_cocos2d_bytearray_elev'.", &tolua_err);
    return 0;
#endif
}

int register_all_cc_bytearray_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;

    tolua_module(tolua_S, "cc", 0);
    tolua_beginmodule(tolua_S, "cc");
    tolua_module(tolua_S, "bytearray", 0);
    tolua_beginmodule(tolua_S, "bytearray");
    tolua_function(tolua_S, "from_vec2", tolua_cocos2d_bytearray_vec2);
    tolua_function(tolua_S, "from_vec3", tolua_cocos2d_bytearray_vec3);
    tolua_function(tolua_S, "from_vec4", tolua_cocos2d_bytearray_vec4);
    tolua_function(tolua_S, "from_mat4", tolua_cocos2d_bytearray_mat4);
    tolua_function(tolua_S, "from_int", tolua_cocos2d_bytearray_int);
    tolua_function(tolua_S, "from_float", tolua_cocos2d_bytearray_float);
    tolua_function(tolua_S, "from_intv", tolua_cocos2d_bytearray_intv);
    tolua_function(tolua_S, "from_floatv", tolua_cocos2d_bytearray_floatv);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 0;
}
