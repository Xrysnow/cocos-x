#pragma once
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "navmesh/CCNavMesh.h"
#include <cstdio>
#include <cstring>

int register_all_cc_navmesh_manual(lua_State* L);

// Module-local legacy conversions and diagnostics. Keep Release checks enabled
// without changing the shared runtime or broadening the public NavMesh API.
namespace navmesh_binding
{
inline void wrapper_name(char* result, size_t size, const char* name)
{
    std::snprintf(result, size, "%s%s", std::strcmp(name, "cc.NavMeshAgent:move") == 0 ? "cclua_navmesh_" : "lua_cc_navmesh_", name + 3);
    for (auto* part = result; *part; ++part) if (*part == ':') *part = '_';
}

inline int invalid(lua_State* L, const char* name)
{
    char wrapper[192]; wrapper_name(wrapper, sizeof(wrapper), name);
    return luaL_error(L, "invalid arguments in function '%s'", wrapper);
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
    } else if constexpr (std::is_same_v<T, unsigned char>) {
        uint16_t value;
        if (!luaval_to_uint16(L, index, &value, name)) return false;
        lua_pushnumber(L, static_cast<unsigned char>(value)); lua_replace(L, index);
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
    } else if constexpr (std::is_same_v<T, cocos2d::NavMeshAgent::MoveCallback>) {
        if (!lua_isfunction(L, index)) {
#if CC_DEBUG >= 1
            tolua_Error error;
            toluafix_isfunction(L, index, "LUA_FUNCTION", 0, &error);
            tolua_error(L, "#ferror in function 'cclua_navmesh_NavMeshAgent_move'.", &error);
#else
            // Legacy Release ref_function returned handler 0 for every nonfunction.
            lua_pushnil(L); lua_replace(L, index);
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
    navmesh_binding::receiver(lua_S, CName_, LUA_FNAME, true); \
    const int argc = lua_gettop(lua_S) - 1; \
    constexpr bool binding_member_self = true; \
    int arg_cur = -1; bool ok = false;
#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
    constexpr auto LUA_FNAME = FName_; \
    navmesh_binding::receiver(lua_S, CName_, LUA_FNAME, false); \
    const int argc = lua_gettop(lua_S) - 1; \
    constexpr bool binding_member_self = false; \
    int arg_cur = -1; bool ok = false;
#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        if (navmesh_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) { lua_settop(lua_S, 1); return 1; } \
        } \
    }
#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
    if (argc == (ARGC_)) { \
        auto fn = (Fn_); arg_cur = 0; \
        if (navmesh_binding::prepare(lua_S, LUA_FNAME, fn)) { \
            int results = 0; \
            ok = lua::_invoke_native<true, true, false, binding_member_self>(lua_S, arg_cur, fn, &results); \
            if (ok) return results; \
        } \
    }
#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    if (arg_cur != -1) return navmesh_binding::invalid(lua_S, LUA_FNAME); \
    return luaL_error(lua_S, "%s has wrong number of arguments: %d, was expecting %d \n", LUA_FNAME, argc, Expected_[0] - '0');
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)
#endif
