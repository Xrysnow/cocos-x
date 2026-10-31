/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "scripting/lua-bindings/manual/3d/cclua_3d_manual.h"
#include "scripting/lua-bindings/auto/cclua_3d_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_geometry_auto.hpp"
#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "3d/CCBundle3D.h"
#include "3d/CCMeshRenderer.h"
#include "3d/CCTerrain.h"

int cclua_3d_MeshRenderer_getAABB(lua_State* L)
{
    int argc                = 0;
    cocos2d::MeshRenderer* cobj = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(L, 1, "cc.MeshRenderer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(L, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'cclua_3d_MeshRenderer_getAABB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;
    if (argc == 0)
    {
        cocos2d::AABB* ret = const_cast<cocos2d::AABB*>(&(cobj->getAABB()));
        object_to_luaval<cocos2d::AABB>(L, "cc.AABB", (cocos2d::AABB*)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getAABB", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_MeshRenderer_getAABB'.", &tolua_err);
#endif
    return 0;
}

int cclua_3d_MeshRenderer_createAsync(lua_State* L)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(L, 1, "cc.MeshRenderer", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    do
    {
        if (argc == 3)
        {
            std::string modelPath;
            ok &= luaval_to_std_string(L, 2, &modelPath, "cc.MeshRenderer:createAsync");
            if (!ok)
                break;
            std::string texturePath;
            ok &= luaval_to_std_string(L, 3, &texturePath, "cc.MeshRenderer:createAsync");
            if (!ok)
                break;

#if CC_DEBUG >= 1
            if (!toluafix_isfunction(L, 4, "LUA_FUNCTION", 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            LUA_FUNCTION handler = toluafix_ref_function(L, 4, 0);

            cocos2d::MeshRenderer::createAsync(
                modelPath, texturePath,
                [=](cocos2d::MeshRenderer* mesh, void* callbackparam) {
                    auto* callbackStack = LuaEngine::getInstance()->getLuaStack();
                    callbackStack->executeCallback([=]() mutable -> int {
                        auto stack = LuaEngine::getInstance()->getLuaStack();
                        int id     = (mesh) ? (int)mesh->_ID : -1;
                        int* luaID = (mesh) ? &mesh->_luaID : nullptr;
                        toluafix_pushusertype_ccobject(stack->getLuaState(), id, luaID, (void*)mesh, "cc.MeshRenderer");
                        stack->executeFunctionByHandler(handler, 1);

                        return 0;
                    });
                },
                nullptr);

            lua_settop(L, 1);
            return 1;
        }
    } while (0);
    ok = true;
    do
    {
        if (argc == 2)
        {
            std::string modelPath;
            ok &= luaval_to_std_string(L, 2, &modelPath, "cc.MeshRenderer:createAsync");
            if (!ok)
                break;

#if CC_DEBUG >= 1
            if (!toluafix_isfunction(L, 3, "LUA_FUNCTION", 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            LUA_FUNCTION handler = toluafix_ref_function(L, 3, 0);

            cocos2d::MeshRenderer::createAsync(
                modelPath,
                [=](cocos2d::MeshRenderer* mesh, void* callbackparam) {
                    auto* callbackStack = LuaEngine::getInstance()->getLuaStack();
                    callbackStack->executeCallback([=]() mutable -> int {
                        auto stack = LuaEngine::getInstance()->getLuaStack();
                        int id     = (mesh) ? (int)mesh->_ID : -1;
                        int* luaID = (mesh) ? &mesh->_luaID : nullptr;
                        toluafix_pushusertype_ccobject(stack->getLuaState(), id, luaID, (void*)mesh, "cc.MeshRenderer");
                        stack->executeFunctionByHandler(handler, 1);

                        return 0;
                    });
                },
                nullptr);

            lua_settop(L, 1);
            return 1;
        }
    } while (0);
    ok = true;
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", "cc.MeshRenderer:createAsync", argc, 3);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_MeshRenderer_createAsync'.", &tolua_err);
#endif
    return 0;
}

static void extendMeshRenderer(lua_State* L)
{
    lua_pushstring(L, "cc.MeshRenderer");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "getAABB", cclua_3d_MeshRenderer_getAABB);
        tolua_function(L, "createAsync", cclua_3d_MeshRenderer_createAsync);
    }
    lua_pop(L, 1);
}

bool luaval_to_terraindata(lua_State* L, int lo, cocos2d::Terrain::TerrainData* outValue, const char* funcName = "")
{
    if (nullptr == L || nullptr == outValue)
        return false;

    bool ok = true;
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if CC_DEBUG >= 1
        luaval_to_native_err(L, "#ferror:", &tolua_err, funcName);
        ok = false;
#endif
    }

    if (ok)
    {
        lua_pushstring(L, "_chunkSize");
        lua_gettable(L, lo);
        if (!lua_isnil(L, lua_gettop(L)))
        {
            luaval_to_size(L, lua_gettop(L), &(outValue->_chunkSize));
        }
        else
        {
            outValue->_chunkSize = cocos2d::Size(32, 32);
        }
        lua_pop(L, 1);

        lua_pushstring(L, "_heightMapSrc");
        lua_gettable(L, lo);
        outValue->_heightMapSrc = tolua_tocppstring(L, -1, "");
        lua_pop(L, 1);

        lua_pushstring(L, "_alphaMapSrc");
        lua_gettable(L, lo);
        outValue->_alphaMapSrc = const_cast<char*>(tolua_tocppstring(L, -1, ""));
        lua_pop(L, 1);

        lua_pushstring(L, "_detailMaps");
        lua_gettable(L, lo);
        if (lua_istable(L, -1))
        {
            size_t len = lua_objlen(L, -1);
            for (size_t i = 0; i < len; i++)
            {
                lua_pushnumber(L, i + 1);
                lua_gettable(L, -2);
                if (lua_istable(L, -1))
                {
                    lua_pushstring(L, "_detailMapSrc");
                    lua_gettable(L, -2);
                    outValue->_detailMaps[i]._detailMapSrc = tolua_tocppstring(L, -1, "");
                    lua_pop(L, 1);

                    lua_pushstring(L, "_detailMapSize");
                    lua_gettable(L, -2);
                    outValue->_detailMaps[i]._detailMapSize = lua_isnil(L, -1) ? 0.0f : (float)lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
            }
        }
        lua_pop(L, 1);

        lua_pushstring(L, "_mapHeight");
        lua_gettable(L, lo);
        outValue->_mapHeight = lua_isnil(L, -1) ? 2.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "_mapScale");
        lua_gettable(L, lo);
        outValue->_mapScale = lua_isnil(L, -1) ? 0.1f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "_detailMapAmount");
        lua_gettable(L, lo);
        outValue->_detailMapAmount = lua_isnil(L, -1) ? 0 : (int)lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "_skirtHeightRatio");
        lua_gettable(L, lo);
        outValue->_skirtHeightRatio = lua_isnil(L, -1) ? 1.0f : (float)lua_tonumber(L, -1);
        lua_pop(L, 1);
    }

    return ok;
}

void terraindata_to_luaval(lua_State* L, const cocos2d::Terrain::TerrainData& inValue)
{
    if (nullptr == L)
        return;

    lua_newtable(L);
    lua_pushstring(L, "_chunkSize");
    size_to_luaval(L, inValue._chunkSize);
    lua_rawset(L, -3);

    if (inValue._heightMapSrc.length() > 0)
    {
        lua_pushstring(L, "_heightMapSrc");
        lua_pushstring(L, inValue._heightMapSrc.c_str());
        lua_rawset(L, -3);
    }

    if (!inValue._alphaMapSrc.empty())
    {
        lua_pushstring(L, "_alphaMapSrc");
        lua_pushstring(L, inValue._alphaMapSrc.c_str());
        lua_rawset(L, -3);
    }

    lua_pushstring(L, "_detailMaps");
    lua_newtable(L);
    for (int i = 0; i < 4; i++)
    {

        lua_pushnumber(L, (lua_Number)i + 1);
        lua_newtable(L);

        lua_pushstring(L, "_detailMapSrc");
        lua_pushstring(L, inValue._detailMaps[i]._detailMapSrc.c_str());
        lua_rawset(L, -3);

        lua_pushstring(L, "_detailMapSize");
        lua_pushnumber(L, (lua_Number)inValue._detailMaps[i]._detailMapSize);
        lua_rawset(L, -3);

        lua_rawset(L, -3);
    }
    lua_rawset(L, -3);

    lua_pushstring(L, "_mapHeight");
    lua_pushnumber(L, (lua_Number)inValue._mapHeight);
    lua_rawset(L, -3);

    lua_pushstring(L, "_mapScale");
    lua_pushnumber(L, (lua_Number)inValue._mapScale);
    lua_rawset(L, -3);

    lua_pushstring(L, "_detailMapAmount");
    lua_pushnumber(L, (lua_Number)inValue._detailMapAmount);
    lua_rawset(L, -3);

    lua_pushstring(L, "_skirtHeightRatio");
    lua_pushnumber(L, (lua_Number)inValue._skirtHeightRatio);
    lua_rawset(L, -3);
}

int cclua_3d_Terrain_create(lua_State* L)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(L, 1, "cc.Terrain", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    if (argc == 1)
    {
        cocos2d::Terrain::TerrainData arg0;
        ok &= luaval_to_terraindata(L, 2, &arg0);
        if (!ok)
        {
            tolua_error(L, "invalid arguments in function 'cclua_3d_Terrain_create'", nullptr);
            return 0;
        }
        cocos2d::Terrain* ret = cocos2d::Terrain::create(arg0);
        object_to_luaval<cocos2d::Terrain>(L, "cc.Terrain", (cocos2d::Terrain*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Terrain::TerrainData arg0;
        cocos2d::Terrain::CrackFixedType arg1;

        ok &= luaval_to_terraindata(L, 2, &arg0);
        ok &= luaval_to_int32(L, 3, (int*)&arg1, "cc.Terrain:create");
        if (!ok)
        {
            tolua_error(L, "invalid arguments in function 'cclua_3d_Terrain_create'", nullptr);
            return 0;
        }
        cocos2d::Terrain* ret = cocos2d::Terrain::create(arg0, arg1);
        object_to_luaval<cocos2d::Terrain>(L, "cc.Terrain", (cocos2d::Terrain*)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Terrain:create", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_Terrain_create'.", &tolua_err);
#endif
    return 0;
}

int cclua_3d_Terrain_getHeight(lua_State* L)
{
    int argc               = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok                = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(L, 1, "cc.Terrain", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (cocos2d::Terrain*)tolua_tousertype(L, 1, 0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'cclua_3d_Terrain_getHeight'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(L) - 1;
    do
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(L, 2, &arg0, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            double ret = cobj->getHeight(arg0);
            tolua_pushnumber(L, (lua_Number)ret);
            return 1;
        }
    } while (0);
    ok = true;
    do
    {
        if (argc == 2)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(L, 2, &arg0, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            cocos2d::Vec3* arg1;
            ok &= luaval_to_object<cocos2d::Vec3>(L, 3, "cc.Vec3", &arg1, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            double ret = cobj->getHeight(arg0, arg1);
            tolua_pushnumber(L, (lua_Number)ret);
            vec3_to_luaval(L, *arg1);
            return 2;
        }
    } while (0);
    ok = true;
    do
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(L, 2, &arg0, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            double arg1;
            ok &= luaval_to_number(L, 3, &arg1, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            double ret = cobj->getHeight(arg0, arg1);
            tolua_pushnumber(L, (lua_Number)ret);
            return 1;
        }
    } while (0);
    ok = true;
    do
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(L, 2, &arg0, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            double arg1;
            ok &= luaval_to_number(L, 3, &arg1, "cc.Terrain:getHeight");

            if (!ok)
            {
                break;
            }
            cocos2d::Vec3 arg2;
            ok &= luaval_to_vec3(L, 4, &arg2);

            if (!ok)
            {
                break;
            }
            double ret = cobj->getHeight(arg0, arg1, &arg2);
            tolua_pushnumber(L, (lua_Number)ret);
            vec3_to_luaval(L, arg2);
            return 2;
        }
    } while (0);
    ok = true;
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getHeight", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_Terrain_getHeight'.", &tolua_err);
#endif

    return 0;
}

int cclua_3d_Terrain_getIntersectionPoint(lua_State* tolua_S)
{
    int argc               = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok                = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.Terrain", 0, &tolua_err))
        goto tolua_lerror;
#endif
    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S, 1, 0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_3d_Terrain_getIntersectionPoint'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S) - 1;
    do
    {
        if (argc == 2)
        {
            cocos2d::Ray* arg0 = nullptr;
            ok &= luaval_to_object<cocos2d::Ray>(tolua_S, 2, "cc.Ray", &arg0, "cc.Terrain:getIntersectionPoint");

            if (!ok)
            {
                break;
            }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.Terrain:getIntersectionPoint");

            if (!ok)
            {
                break;
            }
            bool ret = cobj->getIntersectionPoint(*arg0, arg1);
            tolua_pushboolean(tolua_S, (bool)ret);
            vec3_to_luaval(tolua_S, arg1);
            return 2;
        }
    } while (0);
    ok = true;
    do
    {
        if (argc == 1)
        {
            cocos2d::Ray* arg0;
            ok &= luaval_to_object<cocos2d::Ray>(tolua_S, 2, "cc.Ray", &arg0, "cc.Terrain:getIntersectionPoint");

            if (!ok)
            {
                break;
            }
            cocos2d::Vec3 ret = cobj->getIntersectionPoint(*arg0);
            vec3_to_luaval(tolua_S, ret);
            return 1;
        }
    } while (0);
    ok = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getIntersectionPoint",
               argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_3d_Terrain_getIntersectionPoint'.", &tolua_err);
#endif

    return 0;
}

static void extendTerrain(lua_State* L)
{
    lua_pushstring(L, "cc.Terrain");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "create", cclua_3d_Terrain_create);
        tolua_function(L, "getHeight", cclua_3d_Terrain_getHeight);
        tolua_function(L, "getIntersectionPoint", cclua_3d_Terrain_getIntersectionPoint);
    }
    lua_pop(L, 1);
}

int cclua_3d_Bundle3D_getTrianglesList(lua_State* L)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(L, 1, "cc.Bundle3D", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(L, 2, &arg0, "cc.Bundle3D:getTrianglesList");
        if (!ok)
        {
            tolua_error(L, "invalid arguments in function 'cclua_3d_Bundle3D_getTrianglesList'", nullptr);
            return 0;
        }

        std::vector<cocos2d::Vec3> ret = cocos2d::Bundle3D::getTrianglesList(arg0);
        std_vector_vec3_to_luaval(L, ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Bundle3D:getTrianglesList", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_Bundle3D_getTrianglesList'.", &tolua_err);
#endif
    return 0;
}

void extendBundle3D(lua_State* L)
{
    lua_pushstring(L, "cc.Bundle3D");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "getTrianglesList", cclua_3d_Bundle3D_getTrianglesList);
    }
    lua_pop(L, 1);
}

static int register_all_cc_3d_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendMeshRenderer(L);
    extendTerrain(L);
    extendBundle3D(L);
    return 0;
}

int cclua_3d_AABB_getCorners(lua_State* L)
{
    const int inputTop = lua_gettop(L);
    int argc            = 0;
    const cocos2d::AABB* cobj = nullptr;
    bool ok             = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(L, 1, "cc.AABB", 0, &tolua_err))
        goto tolua_lerror;
#endif

    if (!lua::luaval_to_native(L, 1, &cobj) || !cobj)
        return luaL_error(L, "invalid class object in 'cc.AABB:getCorners'");

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'cclua_3d_AABB_getCorners'", nullptr);
        return 0;
    }
#endif

    argc = inputTop - 1;
    if (argc == 1)
    {
        cocos2d::Vec3* arg0;

        ok &= luaval_to_object<cocos2d::Vec3>(L, 2, "cc.Vec3", &arg0, "cc.AABB:getCorners");
        if (!ok)
            return 0;
        cobj->getCorners(arg0);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:getCorners", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_AABB_getCorners'.", &tolua_err);
#endif

    return 0;
}

int cclua_3d_AABB_updateMinMax(lua_State* L)
{
    const int inputTop = lua_gettop(L);
    int argc            = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok             = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(L, 1, "cc.AABB", 0, &tolua_err))
        goto tolua_lerror;
#endif

    if (!lua::luaval_to_native(L, 1, &cobj) || !cobj)
        return luaL_error(L, "invalid class object in 'cc.AABB:updateMinMax'");

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'cclua_3d_AABB_updateMinMax'", nullptr);
        return 0;
    }
#endif

    argc = inputTop - 1;
    if (argc == 2)
    {
        const cocos2d::Vec3* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<const cocos2d::Vec3>(L, 2, "cc.Vec3", &arg0, "cc.AABB:updateMinMax");

        ok &= luaval_to_ssize_t(L, 3, &arg1, "cc.AABB:updateMinMax");
        if (!ok)
            return 0;
        cobj->updateMinMax(arg0, arg1);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:updateMinMax", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_AABB_updateMinMax'.", &tolua_err);
#endif

    return 0;
}

int cclua_3d_OBB_getCorners(lua_State* L)
{
    const int inputTop = lua_gettop(L);
    int argc           = 0;
    const cocos2d::OBB* cobj = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(L, 1, "cc.OBB", 0, &tolua_err))
        goto tolua_lerror;
#endif

    if (!lua::luaval_to_native(L, 1, &cobj) || !cobj)
        return luaL_error(L, "invalid class object in 'cc.OBB:getCorners'");

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L, "invalid 'cobj' in function 'cclua_3d_OBB_getCorners'", nullptr);
        return 0;
    }
#endif

    argc = inputTop - 1;
    if (argc == 1)
    {
        cocos2d::Vec3* arg0;
#if CC_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif

        size_t len = lua_objlen(L, 2);
        if (len == 0)
        {
            luaL_error(L, "Table's len equal 0");
            return 0;
        }

        arg0 = new cocos2d::Vec3[len];
        for (int i = 1; i <= len; i++)
        {
            lua_pushnumber(L, i);
            lua_gettable(L, 2);
            if (lua_isnil(L, -1))
            {
                arg0[i - 1] = cocos2d::Vec3(0, 0, 0);
            }
            else
            {
                luaval_to_vec3(L, -1, &arg0[i - 1], "cc.OBB:getCorners");
            }
            lua_pop(L, 1);
        }

        cobj->getCorners(arg0);

        lua_newtable(L);

        for (int i = 1; i <= len; i++)
        {
            lua_pushnumber(L, i);
            vec3_to_luaval(L, arg0[i - 1]);
            lua_rawset(L, -3);
        }
        CC_SAFE_DELETE_ARRAY(arg0);

        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:getCorners", argc, 1);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_OBB_getCorners'.", &tolua_err);
#endif

    return 0;
}

int cclua_3d_Ray_intersects(lua_State* L)
{
    const int inputTop = lua_gettop(L);
    int argc           = 0;
    const cocos2d::Ray* self = nullptr;
    bool ok            = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.Ray", 0, &tolua_err))
        goto tolua_lerror;
#endif

    if (!lua::luaval_to_native(L, 1, &self) || !self)
        return luaL_error(L, "invalid class object in 'cc.Ray:intersects'");
#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_3d_Ray_intersects'\n", nullptr);
        return 0;
    }
#endif
    argc = inputTop - 1;
    if (1 == argc)
    {
        const cocos2d::OBB* arg0 = nullptr;
        ok &= lua::luaval_to_native(L, 2, &arg0, "cc.Ray:intersects") && arg0;

        if (!ok)
            return 0;

        float distance;
        bool ret = self->intersects(*arg0, &distance);
        tolua_pushboolean(L, ret);
        tolua_pushnumber(L, (lua_Number)distance);
        return 2;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ray:intersects", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_3d_Ray_intersects'.", &tolua_err);
    return 0;
#endif
}

// Retain the old native Vec3-buffer constructor; ordinary constructors are generated.
static int cclua_3d_OBB_constructor(lua_State* L)
{
    if (lua_gettop(L) - 1 != 2)
        return lua_tocfunction(L, lua_upvalueindex(1))(L);

    const cocos2d::Vec3* points = nullptr;
    int count = 0;
    if (!luaval_to_object<const cocos2d::Vec3>(L, 2, "cc.Vec3", &points, "cc.OBB:OBB") || !points ||
        !luaval_to_int32(L, 3, &count, "cc.OBB:OBB"))
        return luaL_error(L, "invalid arguments in 'cc.OBB:OBB'");
    lua::push_value_owned(L, new cocos2d::OBB(points, count));
    return 1;
}

int register_all_cocos3d_manual_class(lua_State* L)
{
    register_all_cc_geometry(L);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.AABB");
    tolua_function(L, "getCorners", cclua_3d_AABB_getCorners);
    tolua_function(L, "updateMinMax", cclua_3d_AABB_updateMinMax);
    lua_pop(L, 1);

    lua_getfield(L, LUA_REGISTRYINDEX, "cc.OBB");
    tolua_function(L, "getCorners", cclua_3d_OBB_getCorners);
    lua_getfield(L, -1, "new");
    lua_pushcclosure(L, cclua_3d_OBB_constructor, 1);
    lua_setfield(L, -2, "new");
    lua_pop(L, 1);

    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Ray");
    tolua_function(L, "intersects", cclua_3d_Ray_intersects);
    lua_pop(L, 1);
    return 0;
}

int register_cocos3d_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1))  // stack:...,_G,
    {
        register_all_cc_3d(L);
        register_all_cc_3d_manual(L);
        register_all_cocos3d_manual_class(L);
    }
    lua_pop(L, 1);

    return 1;
}
