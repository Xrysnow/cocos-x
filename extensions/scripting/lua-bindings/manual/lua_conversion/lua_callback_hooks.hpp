#pragma once
#include "platform/CCPlatformMacros.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

namespace lua {
// Follow CC_DEBUG > 0, independently of conversion checks (CC_LUA_BINDING_CHECKS).
// Every translation unit sharing a VM must use the same build configuration.
#if CC_DEBUG > 0
inline constexpr bool callback_debug_hooks_enabled = true;
#else
inline constexpr bool callback_debug_hooks_enabled = false;
#endif

inline int _callback_hooks_disabled(lua_State* L) {
    return luaL_error(L, "debug hooks are disabled (CC_DEBUG <= 0)");
}

inline int _initialize_callback_hooks(lua_State* L) {
    lua_settop(L, 0);
    lua_pushliteral(L, "debug");
    lua_rawget(L, LUA_GLOBALSINDEX);
    if (!lua_istable(L, -1)) return luaL_error(L, "debug library is not initialized");
    lua_pushliteral(L, "sethook");
    lua_pushcfunction(L, _callback_hooks_disabled);
    lua_rawset(L, -3);
    return 0;
}

// Owner thread, immediately after luaL_openlibs and before executing scripts or
// exporting library functions. Release has no runtime switch back to debug.
// Native modules must use set_callback_debug_hook below. Reopening the debug
// library, retained pre-init setters, FFI calls to lua_sethook and tampering with
// private bridge frames/registry entries violate the trusted-host contract.
inline bool initialize_callback_hooks(lua_State* L) {
    if (!L) return false;
    if constexpr (callback_debug_hooks_enabled) return true;
    lua_sethook(L, nullptr, 0, 0);
    const int top = lua_gettop(L);
    const int status = lua_cpcall(L, _initialize_callback_hooks, nullptr);
    lua_settop(L, top);
    return status == 0;
}

inline bool set_callback_debug_hook(lua_State* L, lua_Hook hook, int mask, int count) {
    if (!L) return false;
    if constexpr (!callback_debug_hooks_enabled) {
        if (hook && (mask & (LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE | LUA_MASKCOUNT))) return false;
    }
    return lua_sethook(L, hook, mask, count) != 0;
}
}
