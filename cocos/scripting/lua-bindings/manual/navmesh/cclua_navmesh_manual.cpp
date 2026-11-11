/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "scripting/lua-bindings/manual/navmesh/cclua_navmesh_manual.h"
#include "scripting/lua-bindings/auto/cclua_navmesh_auto.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "navmesh/CCNavMesh.h"

int lua_cc_navmesh_NavMeshAgent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshAgent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_navmesh_NavMeshAgent_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMeshAgent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMeshAgent");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:NavMeshAgent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_navmesh_NavMeshAgent_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_navmesh_NavMeshAgent_getUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshAgent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshAgent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_navmesh_NavMeshAgent_getUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_navmesh_NavMeshAgent_getUserData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getUserData();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getUserData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_navmesh_NavMeshAgent_getUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_navmesh_NavMeshAgent_setUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshAgent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshAgent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_navmesh_NavMeshAgent_setUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_navmesh_NavMeshAgent_setUserData'", nullptr);
            return 0;
        }
        cobj->setUserData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setUserData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_navmesh_NavMeshAgent_setUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_navmesh_NavMeshObstacle_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_navmesh_NavMeshObstacle_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMeshObstacle();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMeshObstacle");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:NavMeshObstacle",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_navmesh_NavMeshObstacle_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_navmesh_NavMesh_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_navmesh_NavMesh_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMesh();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMesh");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:NavMesh",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_navmesh_NavMesh_constructor'.",&tolua_err);
#endif

    return 0;
}

int register_all_cc_navmesh_manual(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.NavMeshAgent");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_navmesh_NavMeshAgent_constructor);
        tolua_function(L, "getUserData", lua_cc_navmesh_NavMeshAgent_getUserData);
        tolua_function(L, "setUserData", lua_cc_navmesh_NavMeshAgent_setUserData);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.NavMeshObstacle");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_navmesh_NavMeshObstacle_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.NavMesh");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_navmesh_NavMesh_constructor);
    }
    lua_pop(L, 1);
    return 0;
}

int register_navmesh_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1)) register_all_cc_navmesh(L);
    lua_pop(L, 1);
    return 1;
}
#endif
