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
#include "3d/CCBundle3D.h"
#include "3d/CCMeshRenderer.h"
#include "3d/CCTerrain.h"

// ThreeD bridges only: shared conversion/invocation owns checks, diagnostics and callbacks.
namespace three_d_binding {
struct AABBBorrow { cocos2d::AABB* pointer; };
struct HeightNormal { float height; cocos2d::Vec3 normal; };
struct Intersection { bool hit; cocos2d::Vec3 point; };
}
namespace lua {
template<> struct to_lua<three_d_binding::AABBBorrow> {
    static void F(lua_State* L, const three_d_binding::AABBBorrow& value) {
        // Preserve the existing cached identity without assigning ownership or a Ref owner.
        tolua_pushusertype(L, value.pointer, "cc.AABB");
    }
};
template<> struct to_lua<three_d_binding::HeightNormal> {
    static void F(lua_State* L, const three_d_binding::HeightNormal& value) {
        native_to_luaval(L, value.height);
        native_to_luaval(L, value.normal);
    }
};
template<> struct to_lua<three_d_binding::Intersection> {
    static void F(lua_State* L, const three_d_binding::Intersection& value) {
        native_to_luaval(L, value.hit);
        native_to_luaval(L, value.point);
    }
};
}

int cclua_3d_MeshRenderer_getAABB(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getAABB");
    // Explicit non-owning borrow. Ref self is not an automatically retained value owner.
    const auto borrow = [](cocos2d::MeshRenderer* self) -> three_d_binding::AABBBorrow {
        return {const_cast<cocos2d::AABB*>(&self->getAABB())};
    };
    LUA_TRY_INVOKE_R(0, borrow);
    LUA_INVOKE_FOOTER("0");
}

int cclua_3d_MeshRenderer_createAsync(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:createAsync");
    const auto start = [](std::string_view model, std::string_view texture,
                          std::function<void(cocos2d::MeshRenderer*)> callback) {
        cocos2d::MeshRenderer::createAsync(model, texture,
            [callback = std::move(callback)](cocos2d::MeshRenderer* mesh, void*) { callback(mesh); }, nullptr);
    };
    if (argc == 2 || argc == 3) {
        // Required callable in both checks modes; the owned converter handles its lifetime.
        if (lua_type(lua_S, argc + 1) != LUA_TFUNCTION) arg_cur = argc;
        else {
            LUA_TRY_INVOKE(3, start);
            const auto shortStart = [&](std::string_view model, std::function<void(cocos2d::MeshRenderer*)> callback) {
                start(model, "", std::move(callback));
            };
            LUA_TRY_INVOKE(2, shortStart);
        }
    }
    LUA_SINVOKE_FOOTER("2,3");
}

int cclua_3d_Terrain_getHeight(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getHeight");
    const auto xy = [](const cocos2d::Terrain* self, float x, float z) { return self->getHeight(x, z); };
    const auto point = [](const cocos2d::Terrain* self, const cocos2d::Vec2& pos) { return self->getHeight(pos); };
    LUA_TRY_INVOKE_R(2, xy);
    LUA_TRY_INVOKE_R(1, point);
    LUA_INVOKE_FOOTER("1,2");
}

int cclua_3d_Terrain_getHeightWithNormal(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getHeightWithNormal");
    const auto xy = [](const cocos2d::Terrain* self, float x, float z) {
        three_d_binding::HeightNormal result{};
        result.height = self->getHeight(x, z, &result.normal);
        return result;
    };
    const auto point = [&](const cocos2d::Terrain* self, const cocos2d::Vec2& pos) { return xy(self, pos.x, pos.y); };
    LUA_TRY_INVOKE_R(2, xy);
    LUA_TRY_INVOKE_R(1, point);
    LUA_INVOKE_FOOTER("1,2");
}

int cclua_3d_Terrain_intersectRay(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:intersectRay");
    const auto intersect = [](const cocos2d::Terrain* self, const cocos2d::Ray& ray) {
        three_d_binding::Intersection result{};
        result.hit = self->getIntersectionPoint(ray, result.point);
        return result;
    };
    LUA_TRY_INVOKE_R(1, intersect);
    LUA_INVOKE_FOOTER("1");
}

static int register_all_cc_3d_manual(lua_State* L)
{
    lua_pushstring(L, "cc.MeshRenderer");
    lua_rawget(L, LUA_REGISTRYINDEX);
    tolua_function(L, "getAABB", cclua_3d_MeshRenderer_getAABB);
    tolua_function(L, "createAsync", cclua_3d_MeshRenderer_createAsync);
    lua_pop(L, 1);
    lua_pushstring(L, "cc.Terrain");
    lua_rawget(L, LUA_REGISTRYINDEX);
    tolua_function(L, "getHeight", cclua_3d_Terrain_getHeight);
    tolua_function(L, "getHeightWithNormal", cclua_3d_Terrain_getHeightWithNormal);
    tolua_function(L, "intersectRay", cclua_3d_Terrain_intersectRay);
    lua_pop(L, 1);
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
