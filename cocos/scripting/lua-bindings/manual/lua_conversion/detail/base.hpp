#pragma once
#include "platform/CCPlatformMacros.h"
#include "tolua++.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>

#ifndef CC_LUA_BINDING_CHECKS
#if CC_DEBUG > 0
#define CC_LUA_BINDING_CHECKS 1
#else
#define CC_LUA_BINDING_CHECKS 0
#endif
#endif

extern std::unordered_map<uintptr_t, const char*> g_luaType;
extern std::unordered_map<std::string, const char*> g_typeCast;

namespace lua
{
	constexpr int LUA_TPROTO = LUA_TTHREAD + 1;
    constexpr int LUA_TCDATA = LUA_TTHREAD + 2;

	template<typename T, class Enable = void> struct to_native {};
	template<typename T, class Enable = void> struct owned_callback_push;
	template<typename T, class Enable = void> struct owned_callback_read;

	template<typename T, class Enable = void> struct to_lua {};

    template<typename T>
    const char* _getClassNameByType()
    {
		using key_type = decltype(g_luaType)::key_type;
		using type = std::conditional_t<std::is_integral_v<key_type>, key_type, const char*>;
		const auto key = reinterpret_cast<type>(typeid(T).name());
        const auto it = g_luaType.find(key);
        if (it != g_luaType.end())
            return it->second;
        return "";
    }

    template<typename T>
    std::string getClassNameByType()
    {
        return _getClassNameByType<T>();
    }

    template<typename T>
    void registerLuaType(const char* luaType, const char* castType)
    {
		using key_type = decltype(g_luaType)::key_type;
		using type = std::conditional_t<std::is_integral_v<key_type>, key_type, const char*>;
		const auto key = reinterpret_cast<type>(typeid(T).name());
        g_luaType[key] = luaType;
        g_typeCast[castType] = luaType;
    }

    inline int push_table_instance(lua_State* L, int lo)
    {
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return 0;
        }
        if (lua_istable(L, lo)) {
            lua_pushstring(L, ".c_instance");
            lua_gettable(L, lo);
            if (lua_type(L, -1) == LUA_TUSERDATA) {
                lua_replace(L, lo);
                return 1;
            }
            lua_pop(L, 1);
            return 0;
        }
        return 0;
    }

    inline int isusertype(lua_State* L, int lo, const char* type)
    {
        if (!L || !type || !*type)
            return 0;
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return 0;
        }
        if (lo == 0 || lo > lua_gettop(L))
            return 0;
        if (lua_type(L, lo) != LUA_TUSERDATA) {
            if (!push_table_instance(L, lo)) {
                return 0;
            }
        }
        if (lua_objlen(L, lo) != sizeof(void*))
            return 0;
        if (lua_getmetatable(L, lo))
        {
            lua_rawget(L, LUA_REGISTRYINDEX); // registry[metatable] = type name
            const char *tn = lua_tostring(L, -1);
            const int r = tn && (strcmp(tn, type) == 0);
            lua_pop(L, 1);
            if (r)
                return 1;
            else
            {
                lua_pushstring(L, "tolua_super");
                lua_rawget(L, LUA_REGISTRYINDEX);
                if (!lua_istable(L, -1)) {
                    lua_pop(L, 1);
                    return 0;
                }
                lua_getmetatable(L, lo);
                lua_rawget(L, -2); // super[metatable]
                if (lua_istable(L, -1))
                {
                    lua_pushstring(L, type);
                    lua_rawget(L, -2); // super[metatable][type]
                    const int b = lua_toboolean(L, -1);
                    lua_pop(L, 3);
                    if (b)
                        return 1;
                }
                else
                    lua_pop(L, 2);
            }
        }
        return 0;
    }

    inline void* _tousertype(lua_State* L, int lo)
    {
        if (!L)
            return nullptr;
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return nullptr;
        }
        if (lo == 0 || lo > lua_gettop(L))
            return nullptr;
        if (lua_type(L, lo) != LUA_TUSERDATA) {
            if (!push_table_instance(L, lo))
                return nullptr;
        }
        if (lua_objlen(L, lo) != sizeof(void*))
            return nullptr;
        const auto u = lua_touserdata(L, lo);
        return u ? *(void**)u : nullptr;
    }

	inline bool is_indexable(lua_State* L, int lo)
	{
		const auto t = lua_type(L, lo);
		return t == LUA_TTABLE || t == LUA_TUSERDATA || t == LUA_TCDATA;
	}

	////////////////////////////////////////////////////////////////////////////////

	// Preserves pseudo-indices; returns 0 for invalid stack indices.
	inline int _absolute_index(lua_State* L, int lo) {
		if (!L) return 0;
		if (lo <= LUA_REGISTRYINDEX) return lo;
		const int top = lua_gettop(L);
		if (lo < 0) lo += top + 1;
		return lo > 0 && lo <= top ? lo : 0;
	}
}

#define LUA_CHECK_TO_NATIVE\
	const auto top = L ? lua_gettop(L) : 0;\
	do {\
		if (nullptr == L || nullptr == outValue || !(lo = ::lua::_absolute_index(L, lo)))\
			return false;\
	} while (false)
