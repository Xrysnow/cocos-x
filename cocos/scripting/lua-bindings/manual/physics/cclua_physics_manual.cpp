/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

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

#include "scripting/lua-bindings/manual/physics/cclua_physics_manual.hpp"
#if CC_USE_PHYSICS
#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/base/LuaScriptHandlerMgr.h"
#include "2d/Scene.h"
#include <cmath>
#include <limits>
#include <new>
#include <type_traits>
#include <vector>

namespace physics_binding {
// Pointer/count and geometric preconditions only; elements use shared Vec2 conversion.
template<bool Closed> struct Points {
    cc::Vec2* data = nullptr;
    int size = 0;
    int count() const { return size; }
};
using PolygonPoints = Points<true>;
using ChainPoints = Points<false>;
struct ContactSnapshot {
    bool present = false;
    cc::PhysicsContactData value;
};
using HandlerType = cc::ScriptHandlerMgr::HandlerType;
using RayCallback = std::function<bool(cc::PhysicsWorld*, const cc::PhysicsRayCastInfo&)>;
using QueryCallback = std::function<bool(cc::PhysicsWorld*, cc::PhysicsShape*)>;
}

namespace lua {
template<bool Closed> struct to_native<physics_binding::Points<Closed>> {
    static bool F(lua_State* L, int lo, physics_binding::Points<Closed>* outValue, const char* fName = "") {
        LUA_CHECK_TO_NATIVE;
        if (!lua_istable(L, lo)) return false;
        const size_t count = lua_objlen(L, lo);
        if (count < (Closed ? 3u : 2u) || count > static_cast<size_t>(std::numeric_limits<int>::max()))
            return false;
        // Reject holes/extra keys before allocation; a Lua length is not a dense-array guarantee.
        size_t keys = 0;
        lua_pushnil(L);
        while (lua_next(L, lo)) {
            const lua_Number key = lua_tonumber(L, -2);
            if (lua_type(L, -2) != LUA_TNUMBER || key < 1 || key > count || std::floor(key) != key) {
                lua_settop(L, top);
                return false;
            }
            ++keys;
            lua_pop(L, 1);
        }
        if (keys != count) return false;
        if (count > std::numeric_limits<size_t>::max() / sizeof(cc::Vec2)) return false;
        // Lua owns the contiguous scratch buffer. A later point/material/offset metamethod may
        // raise or collect garbage without bypassing a native heap owner's destructor.
        static_assert(std::is_trivially_destructible_v<cc::Vec2>);
        auto* values = static_cast<cc::Vec2*>(lua_newuserdata(L, count * sizeof(cc::Vec2)));
        for (size_t i = 0; i < count; ++i) new (values + i) cc::Vec2();
        if (!luaval_to_native_array_inplace(L, lo, values, count, fName)) return false;
        double twiceArea = 0;
        for (size_t i = 0; i < count; ++i) {
            const auto& current = values[i];
            if (!std::isfinite(current.x) || !std::isfinite(current.y)) return false;
            if (i && current == values[i - 1]) return false;
            if constexpr (Closed) {
                const auto& next = values[(i + 1) % count];
                twiceArea += double(current.x) * next.y - double(current.y) * next.x;
            }
        }
        if constexpr (Closed) {
            if (values[0] == values[count - 1] || twiceArea == 0) return false;
        }
        *outValue = {values, static_cast<int>(count)};
        return true;
    }
};
template<> struct to_lua<physics_binding::ContactSnapshot> {
    static void F(lua_State* L, const physics_binding::ContactSnapshot& snapshot) {
        if (snapshot.present) native_to_luaval(L, snapshot.value);
        else lua_pushnil(L);
    }
};
}

int cclua_physics_PhysicsBody_createPolygon(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createPolygon");
    const auto full = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material, cc::Vec2 offset) {
        return cc::PhysicsBody::createPolygon(points.data, points.count(), material, offset);
    };
    const auto materialOnly = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsBody::createPolygon(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsBody::createPolygon(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsBody_createEdgePolygon(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createEdgePolygon");
    const auto full = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material, float border) {
        return cc::PhysicsBody::createEdgePolygon(points.data, points.count(), material, border);
    };
    const auto materialOnly = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsBody::createEdgePolygon(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsBody::createEdgePolygon(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsBody_createEdgeChain(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createEdgeChain");
    const auto full = [](physics_binding::ChainPoints points, const cc::PhysicsMaterial& material, float border) {
        return cc::PhysicsBody::createEdgeChain(points.data, points.count(), material, border);
    };
    const auto materialOnly = [](physics_binding::ChainPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsBody::createEdgeChain(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::ChainPoints points) {
        return cc::PhysicsBody::createEdgeChain(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsShapePolygon_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:create");
    const auto full = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material, cc::Vec2 offset) {
        return cc::PhysicsShapePolygon::create(points.data, points.count(), material, offset);
    };
    const auto materialOnly = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsShapePolygon::create(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsShapePolygon::create(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsShapeEdgePolygon_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShapeEdgePolygon", "cc.PhysicsShapeEdgePolygon:create");
    const auto full = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material, float border) {
        return cc::PhysicsShapeEdgePolygon::create(points.data, points.count(), material, border);
    };
    const auto materialOnly = [](physics_binding::PolygonPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsShapeEdgePolygon::create(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsShapeEdgePolygon::create(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsShapeEdgeChain_create(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShapeEdgeChain", "cc.PhysicsShapeEdgeChain:create");
    const auto full = [](physics_binding::ChainPoints points, const cc::PhysicsMaterial& material, float border) {
        return cc::PhysicsShapeEdgeChain::create(points.data, points.count(), material, border);
    };
    const auto materialOnly = [](physics_binding::ChainPoints points, const cc::PhysicsMaterial& material) {
        return cc::PhysicsShapeEdgeChain::create(points.data, points.count(), material);
    };
    const auto pointsOnly = [](physics_binding::ChainPoints points) {
        return cc::PhysicsShapeEdgeChain::create(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, full);
    LUA_TRY_INVOKE_R(2, materialOnly);
    LUA_TRY_INVOKE_R(1, pointsOnly);
    LUA_SINVOKE_FOOTER("1,2,3");
}

int cclua_physics_PhysicsShape_recenterPoints(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:recenterPoints");
    const auto recenter = [](physics_binding::PolygonPoints points, const cc::Vec2& center) {
        cc::PhysicsShape::recenterPoints(points.data, points.count(), center);
        return std::vector<cc::Vec2>(points.data, points.data + points.count());
    };
    const auto origin = [](physics_binding::PolygonPoints points) {
        cc::PhysicsShape::recenterPoints(points.data, points.count());
        return std::vector<cc::Vec2>(points.data, points.data + points.count());
    };
    LUA_TRY_INVOKE_R(2, recenter);
    LUA_TRY_INVOKE_R(1, origin);
    LUA_SINVOKE_FOOTER("1,2");
}

int cclua_physics_PhysicsShape_getPolygonCenter(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getPolygonCenter");
    const auto center = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsShape::getPolygonCenter(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(1, center);
    LUA_SINVOKE_FOOTER("1");
}

int cclua_physics_PhysicsShapePolygon_calculateArea(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:calculateArea");
    const auto area = [](physics_binding::PolygonPoints points) {
        return cc::PhysicsShapePolygon::calculateArea(points.data, points.count());
    };
    LUA_TRY_INVOKE_R(1, area);
    LUA_SINVOKE_FOOTER("1");
}

int cclua_physics_PhysicsShapePolygon_calculateMoment(lua_State* lua_S)
{
    LUA_SINVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:calculateMoment");
    const auto offset = [](float mass, physics_binding::PolygonPoints points, const cc::Vec2& offset) {
        return cc::PhysicsShapePolygon::calculateMoment(mass, points.data, points.count(), offset);
    };
    const auto origin = [](float mass, physics_binding::PolygonPoints points) {
        return cc::PhysicsShapePolygon::calculateMoment(mass, points.data, points.count());
    };
    LUA_TRY_INVOKE_R(3, offset);
    LUA_TRY_INVOKE_R(2, origin);
    LUA_SINVOKE_FOOTER("2,3");
}

int cclua_physics_PhysicsShapeBox_getPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsShapeBox", "cc.PhysicsShapeBox:getPoints");
    const auto points = [](const cc::PhysicsShapeBox* self) {
        std::vector<cc::Vec2> result(4);
        self->getPoints(result.data());
        return result;
    };
    LUA_TRY_INVOKE_R(0, points);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsShapeEdgeBox_getPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsShapeEdgeBox", "cc.PhysicsShapeEdgeBox:getPoints");
    const auto points = [](const cc::PhysicsShapeEdgeBox* self) {
        std::vector<cc::Vec2> result(4);
        self->getPoints(result.data());
        return result;
    };
    LUA_TRY_INVOKE_R(0, points);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsShapePolygon_getPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:getPoints");
    const auto points = [](const cc::PhysicsShapePolygon* self) {
        std::vector<cc::Vec2> result(self->getPointsCount());
        self->getPoints(result.data());
        return result;
    };
    LUA_TRY_INVOKE_R(0, points);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsShapeEdgePolygon_getPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsShapeEdgePolygon", "cc.PhysicsShapeEdgePolygon:getPoints");
    const auto points = [](const cc::PhysicsShapeEdgePolygon* self) {
        std::vector<cc::Vec2> result(self->getPointsCount());
        self->getPoints(result.data());
        return result;
    };
    LUA_TRY_INVOKE_R(0, points);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsShapeEdgeChain_getPoints(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsShapeEdgeChain", "cc.PhysicsShapeEdgeChain:getPoints");
    const auto points = [](const cc::PhysicsShapeEdgeChain* self) {
        std::vector<cc::Vec2> result(self->getPointsCount());
        self->getPoints(result.data());
        return result;
    };
    LUA_TRY_INVOKE_R(0, points);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsContact_getContactData(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsContact", "cc.PhysicsContact:getContactData");
    const auto snapshot = [](const cc::PhysicsContact* self) {
        physics_binding::ContactSnapshot result;
        if (const auto* data = self->getContactData()) { result.present = true; result.value = *data; }
        return result;
    };
    LUA_TRY_INVOKE_R(0, snapshot);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsContact_getPreContactData(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsContact", "cc.PhysicsContact:getPreContactData");
    const auto snapshot = [](const cc::PhysicsContact* self) {
        physics_binding::ContactSnapshot result;
        if (const auto* data = self->getPreContactData()) { result.present = true; result.value = *data; }
        return result;
    };
    LUA_TRY_INVOKE_R(0, snapshot);
    LUA_INVOKE_FOOTER("0");
}

int cclua_physics_PhysicsWorld_getScene(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getScene");
    // Scene is an existing Ref object; do not copy a Scene value from the native reference.
    const auto scene = [](const cc::PhysicsWorld* self) { return &self->getScene(); };
    LUA_TRY_INVOKE_R(0, scene);
    LUA_INVOKE_FOOTER("0");
}

namespace physics_binding {
template<typename T> bool snapshotArgument(lua_State* L, int index, const char* name) {
    T value{};
    if (!lua::luaval_to_native(L, index, &value, name)) return false;
    lua::native_to_luaval(L, value);
    lua_replace(L, index);
    return true;
}
}

int cclua_physics_PhysicsWorld_rayCast(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:rayCast");
    const auto query = [](cc::PhysicsWorld* self, physics_binding::RayCallback callback,
                          const cc::Vec2& start, const cc::Vec2& ended) {
        self->rayCast([callback = std::move(callback)](cc::PhysicsWorld& world,
            const cc::PhysicsRayCastInfo& info, void*) { return callback(&world, info); }, start, ended, nullptr);
    };
    if (argc == 3) {
        if (lua_type(lua_S, 2) != LUA_TFUNCTION) arg_cur = 1;
        else if (!physics_binding::snapshotArgument<cc::Vec2>(lua_S, 3, LUA_FNAME)) arg_cur = 2;
        else if (!physics_binding::snapshotArgument<cc::Vec2>(lua_S, 4, LUA_FNAME)) arg_cur = 3;
        else { LUA_TRY_INVOKE(3, query); }
    }
    LUA_INVOKE_FOOTER("3");
}

int cclua_physics_PhysicsWorld_queryRect(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:queryRect");
    const auto query = [](cc::PhysicsWorld* self, physics_binding::QueryCallback callback,
                          const cc::Rect& geometry) {
        self->queryRect([callback = std::move(callback)](cc::PhysicsWorld& world,
            cc::PhysicsShape& shape, void*) { return callback(&world, &shape); }, geometry, nullptr);
    };
    if (argc == 2) {
        if (lua_type(lua_S, 2) != LUA_TFUNCTION) arg_cur = 1;
        else if (!physics_binding::snapshotArgument<cc::Rect>(lua_S, 3, LUA_FNAME)) arg_cur = 2;
        else { LUA_TRY_INVOKE(2, query); }
    }
    LUA_INVOKE_FOOTER("2");
}

int cclua_physics_PhysicsWorld_queryPoint(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:queryPoint");
    const auto query = [](cc::PhysicsWorld* self, physics_binding::QueryCallback callback,
                          const cc::Vec2& geometry) {
        self->queryPoint([callback = std::move(callback)](cc::PhysicsWorld& world,
            cc::PhysicsShape& shape, void*) { return callback(&world, &shape); }, geometry, nullptr);
    };
    if (argc == 2) {
        if (lua_type(lua_S, 2) != LUA_TFUNCTION) arg_cur = 1;
        else if (!physics_binding::snapshotArgument<cc::Vec2>(lua_S, 3, LUA_FNAME)) arg_cur = 2;
        else { LUA_TRY_INVOKE(2, query); }
    }
    LUA_INVOKE_FOOTER("2");
}

int cclua_physics_EventListenerPhysicsContact_registerScriptHandler(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventListenerPhysicsContact", "cc.EventListenerPhysicsContact:registerScriptHandler");
    using HandlerType = physics_binding::HandlerType;
    if (argc == 2) {
        HandlerType type;
        // Validate the channel before the shared callable converter owns a Lua reference.
        if (!lua::luaval_to_native(lua_S, 3, &type)) arg_cur = 2;
        else switch (type) {
        case HandlerType::EVENT_PHYSICS_CONTACT_BEGIN: {
            const auto assign = [](cc::EventListenerPhysicsContact* self,
                                  std::function<bool(cc::PhysicsContact*)> callback, HandlerType) {
                if (!callback) self->onContactBegin = nullptr;
                else self->onContactBegin = [callback = std::move(callback)](cc::PhysicsContact& contact) {
                    return callback(&contact);
                };
            };
            LUA_TRY_INVOKE(2, assign);
            break;
        }
        case HandlerType::EVENT_PHYSICS_CONTACT_PRESOLVE: {
            const auto assign = [](cc::EventListenerPhysicsContact* self,
                std::function<bool(cc::PhysicsContact*, cc::PhysicsContactPreSolve*)> callback, HandlerType) {
                if (!callback) self->onContactPreSolve = nullptr;
                else self->onContactPreSolve = [callback = std::move(callback)](cc::PhysicsContact& contact,
                    cc::PhysicsContactPreSolve& solve) { return callback(&contact, &solve); };
            };
            LUA_TRY_INVOKE(2, assign);
            break;
        }
        case HandlerType::EVENT_PHYSICS_CONTACT_POSTSOLVE: {
            const auto assign = [](cc::EventListenerPhysicsContact* self,
                std::function<void(cc::PhysicsContact*, const cc::PhysicsContactPostSolve*)> callback, HandlerType) {
                if (!callback) self->onContactPostSolve = nullptr;
                else self->onContactPostSolve = [callback = std::move(callback)](cc::PhysicsContact& contact,
                    const cc::PhysicsContactPostSolve& solve) { callback(&contact, &solve); };
            };
            LUA_TRY_INVOKE(2, assign);
            break;
        }
        case HandlerType::EVENT_PHYSICS_CONTACT_SEPARATE: {
            const auto assign = [](cc::EventListenerPhysicsContact* self,
                                  std::function<void(cc::PhysicsContact*)> callback, HandlerType) {
                if (!callback) self->onContactSeparate = nullptr;
                else self->onContactSeparate = [callback = std::move(callback)](cc::PhysicsContact& contact) {
                    callback(&contact);
                };
            };
            LUA_TRY_INVOKE(2, assign);
            break;
        }
        default: arg_cur = 2; break;
        }
    }
    LUA_INVOKE_FOOTER("2");
}

int register_all_cc_physics_manual(lua_State* lua_S)
{
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsBody");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "createPolygon", cclua_physics_PhysicsBody_createPolygon);
        tolua_function(lua_S, "createEdgePolygon", cclua_physics_PhysicsBody_createEdgePolygon);
        tolua_function(lua_S, "createEdgeChain", cclua_physics_PhysicsBody_createEdgeChain);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShape");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "recenterPoints", cclua_physics_PhysicsShape_recenterPoints);
        tolua_function(lua_S, "getPolygonCenter", cclua_physics_PhysicsShape_getPolygonCenter);
        tolua_function(lua_S, "getPolyonCenter", cclua_physics_PhysicsShape_getPolygonCenter);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShapeBox");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "getPoints", cclua_physics_PhysicsShapeBox_getPoints);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShapeEdgeBox");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "getPoints", cclua_physics_PhysicsShapeEdgeBox_getPoints);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShapePolygon");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "create", cclua_physics_PhysicsShapePolygon_create);
        tolua_function(lua_S, "getPoints", cclua_physics_PhysicsShapePolygon_getPoints);
        tolua_function(lua_S, "calculateArea", cclua_physics_PhysicsShapePolygon_calculateArea);
        tolua_function(lua_S, "calculateMoment", cclua_physics_PhysicsShapePolygon_calculateMoment);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShapeEdgePolygon");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "create", cclua_physics_PhysicsShapeEdgePolygon_create);
        tolua_function(lua_S, "getPoints", cclua_physics_PhysicsShapeEdgePolygon_getPoints);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsShapeEdgeChain");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "create", cclua_physics_PhysicsShapeEdgeChain_create);
        tolua_function(lua_S, "getPoints", cclua_physics_PhysicsShapeEdgeChain_getPoints);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsContact");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "getContactData", cclua_physics_PhysicsContact_getContactData);
        tolua_function(lua_S, "getPreContactData", cclua_physics_PhysicsContact_getPreContactData);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.PhysicsWorld");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "getScene", cclua_physics_PhysicsWorld_getScene);
        tolua_function(lua_S, "rayCast", cclua_physics_PhysicsWorld_rayCast);
        tolua_function(lua_S, "queryRect", cclua_physics_PhysicsWorld_queryRect);
        tolua_function(lua_S, "queryPoint", cclua_physics_PhysicsWorld_queryPoint);
        tolua_constant(lua_S, "DEBUGDRAW_NONE", cc::PhysicsWorld::DEBUGDRAW_NONE);
        tolua_constant(lua_S, "DEBUGDRAW_SHAPE", cc::PhysicsWorld::DEBUGDRAW_SHAPE);
        tolua_constant(lua_S, "DEBUGDRAW_JOINT", cc::PhysicsWorld::DEBUGDRAW_JOINT);
        tolua_constant(lua_S, "DEBUGDRAW_CONTACT", cc::PhysicsWorld::DEBUGDRAW_CONTACT);
        tolua_constant(lua_S, "DEBUGDRAW_ALL", cc::PhysicsWorld::DEBUGDRAW_ALL);
    }
    lua_pop(lua_S, 1);
    lua_getfield(lua_S, LUA_REGISTRYINDEX, "cc.EventListenerPhysicsContact");
    if (lua_istable(lua_S, -1)) {
        tolua_function(lua_S, "registerScriptHandler", cclua_physics_EventListenerPhysicsContact_registerScriptHandler);
    }
    lua_pop(lua_S, 1);
    // LuaStack leaves the global table on the stack, as in the original registration.
    tolua_constant(lua_S, "PHYSICS_INFINITY", cc::PHYSICS_INFINITY);
    return 0;
}
#endif // CC_USE_PHYSICS
