#pragma once
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "physics3d/CCPhysics3D.h"
#include <cstdio>
#include <cstring>

int register_all_cc_physics3d_retained(lua_State* L);

// Module-local legacy conversions and diagnostics. Keep Release checks enabled
// without changing the shared runtime or broadening the public Physics3D API.
namespace physics3d_binding
{
inline void wrapper_name(char* result, size_t size, const char* name)
{
    std::snprintf(result, size, "%s%s", std::strcmp(name, "cc.Physics3DObject:setCollisionCallback") == 0 ? "cclua_physics3d_" : "lua_cc_physics3d_", name + 3);
    for (auto* part = result; *part; ++part) if (*part == ':') *part = '_';
}

inline int invalid(lua_State* L, const char* name)
{
    char wrapper[192]; wrapper_name(wrapper, sizeof(wrapper), name);
    return luaL_error(L, "invalid arguments in function '%s'", wrapper);
}

inline int failed(lua_State* L, const char* name, int argc, int tried, int expected)
{
    if (std::strcmp(name, "cc.Physics3DRigidBody:setAngularFactor") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", name, argc, 1);
    if (std::strcmp(name, "cc.Physics3DRigidBody:removeConstraint") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", name, argc, 1);
    if (std::strcmp(name, "cc.Physics3DPointToPointConstraint:init") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", name, argc, 2);
    if (std::strcmp(name, "cc.Physics3DPointToPointConstraint:create") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", name, argc, 2);
    if (std::strcmp(name, "cc.Physics3DHingeConstraint:getHingeAngle") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", name, argc, 0);
    if (std::strcmp(name, "cc.Physics3DHingeConstraint:create") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", name, argc, 4);
    if (std::strcmp(name, "cc.Physics3DConeTwistConstraint:create") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", name, argc, 2);
    if (std::strcmp(name, "cc.Physics3D6DofConstraint:create") == 0) return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", name, argc, 5);
    if (tried != -1) return invalid(L, name);
    return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", name, argc, expected);
}

inline void receiver(lua_State* L, const char* type, const char* name, bool member)
{
#if CC_DEBUG >= 1
    tolua_Error error;
    char wrapper[192]; wrapper_name(wrapper, sizeof(wrapper), name);
    if (!(member ? tolua_isusertype(L, 1, type, 0, &error) : tolua_isusertable(L, 1, type, 0, &error))) {
        char message[256]; std::snprintf(message, sizeof(message), "#ferror in function '%s'.", wrapper);
        tolua_error(L, message, &error);
    }
    if (member && !tolua_tousertype(L, 1, nullptr))
        luaL_error(L, "invalid 'cobj' in function '%s'", wrapper);
#endif
}

template<typename Arg>
bool prepare_value(lua_State* L, int index, const char* name)
{
    using T = std::remove_cv_t<std::remove_reference_t<Arg>>;
    if constexpr (std::is_same_v<T, bool>) {
        bool value;
        if (!luaval_to_boolean(L, index, &value, name)) return false;
        lua_pushboolean(L, value); lua_replace(L, index);
    } else if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
        T value;
        bool ok;
        if constexpr (std::is_unsigned_v<T>) ok = luaval_to_uint32(L, index, reinterpret_cast<unsigned int*>(&value), name);
        else ok = luaval_to_int32(L, index, reinterpret_cast<int*>(&value), name);
        if (!ok) return false;
        lua_pushnumber(L, value); lua_replace(L, index);
    } else if constexpr (std::is_enum_v<T>) {
        int value;
        if (!luaval_to_int32(L, index, &value, name)) return false;
        lua_pushnumber(L, value); lua_replace(L, index);
    } else if constexpr (std::is_floating_point_v<T>) {
        double value;
        if (!luaval_to_number(L, index, &value, name)) return false;
        lua_pushnumber(L, value); lua_replace(L, index);
    } else if constexpr (std::is_same_v<T, cocos2d::Vec3>) {
        cocos2d::Vec3 value;
        if (!luaval_to_vec3(L, index, &value, name)) return false;
        vec3_to_luaval(L, value); lua_replace(L, index);
    } else if constexpr (std::is_same_v<T, cocos2d::Mat4>) {
        cocos2d::Mat4 value;
        if (!luaval_to_mat4(L, index, &value, name)) return false;
        mat4_to_luaval(L, value); lua_replace(L, index);
    } else if constexpr (std::is_same_v<T, cocos2d::Physics3DObject::CollisionCallbackFunc>) {
        if (!lua_isfunction(L, index)) {
#if CC_DEBUG >= 1
            tolua_Error error;
            toluafix_isfunction(L, index, "LUA_FUNCTION", 0, &error);
            tolua_error(L, "#ferror in function 'cclua_physics3d_Physics3DObject_setCollisionCallback'.", &error);
#else
            // Legacy Release installed a nonempty handler-0 no-op callback.
            lua_pushcfunction(L, [](lua_State*) { return 0; }); lua_replace(L, index);
#endif
        }
        return true;
    }
    return true;
}

template<typename... Args, size_t... Index>
bool prepare_arguments(lua_State* L, const char* name, std::index_sequence<Index...>)
{
    const int first = lua_gettop(L) - int(sizeof...(Args)) + 1;
    return (prepare_value<Args>(L, first + int(Index), name) && ...);
}
template<typename T> struct prepare_signature;
template<typename R, typename... Args>
struct prepare_signature<R(*)(Args...)> {
    static bool run(lua_State* L, const char* name) {
        return prepare_arguments<Args...>(L, name, std::index_sequence_for<Args...>{});
    }
};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...)> : prepare_signature<R(*)(Args...)> {};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...) const> : prepare_signature<R(*)(Args...)> {};
template<typename F> bool prepare(lua_State* L, const char* name, const F&)
{
    using T = std::decay_t<F>;
    if constexpr (std::is_class_v<T>)
        return prepare_signature<typename lua::function_traits<T>::pointer>::run(L, name);
    else return prepare_signature<T>::run(L, name);
}
}

#undef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_) \
    constexpr auto LUA_FNAME = FName_; \
    physics3d_binding::receiver(lua_S, CName_, LUA_FNAME, true); \
    const int argc = lua_gettop(lua_S) - 1; \
    constexpr bool binding_member_self = true; \
    int arg_cur = -1; bool ok = false;
#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
    constexpr auto LUA_FNAME = FName_; \
    physics3d_binding::receiver(lua_S, CName_, LUA_FNAME, false); \
    const int argc = lua_gettop(lua_S) - 1; \
    constexpr bool binding_member_self = false; \
    int arg_cur = -1; bool ok = false;
#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        if (physics3d_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) { lua_settop(lua_S, 1); return 1; } \
        } \
    }
#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        if (physics3d_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) return results; \
        } \
    }
#undef LUA_TRY_INVOKE_OVERLOAD
#define LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        const int saved_top = lua_gettop(lua_S); \
        luaL_checkstack(lua_S, saved_top, "Physics3D overload arguments"); \
        for (int i = 1; i <= saved_top; ++i) lua_pushvalue(lua_S, i); \
        if (physics3d_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) { lua_settop(lua_S, 1); return 1; } \
        } \
        lua_settop(lua_S, saved_top); \
    }
#undef LUA_TRY_INVOKE_R_OVERLOAD
#define LUA_TRY_INVOKE_R_OVERLOAD(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        const int saved_top = lua_gettop(lua_S); \
        luaL_checkstack(lua_S, saved_top, "Physics3D overload arguments"); \
        for (int i = 1; i <= saved_top; ++i) lua_pushvalue(lua_S, i); \
        if (physics3d_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) return results; \
        } \
        lua_settop(lua_S, saved_top); \
    }
#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    return physics3d_binding::failed(lua_S, LUA_FNAME, argc, arg_cur, Expected_[0] - '0');
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)
#endif
