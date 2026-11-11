#pragma once
#include "conversion.hpp"
#include <cmath>
#include <initializer_list>
#include <limits>
#include <string_view>
#include <type_traits>

namespace lua::record_detail
{
    // Record schemas read their own fields without invoking Lua metamethods.
    inline bool fields(lua_State* L, int index, std::initializer_list<std::string_view> names)
    {
        if (!L || lua_type(L, index) != LUA_TTABLE) return false;
        index = _absolute_index(L, index);
        lua_pushnil(L);
        while (lua_next(L, index)) {
            bool known = false;
            if (lua_type(L, -2) == LUA_TSTRING) {
                size_t length = 0;
                const char* key = lua_tolstring(L, -2, &length);
                for (const auto name : names)
                    if (std::string_view(key, length) == name) { known = true; break; }
            }
            lua_pop(L, 1);
            if (!known) { lua_pop(L, 1); return false; }
        }
        return true;
    }

    template<typename T>
    bool number(lua_State* L, int index, const char* key, T* out, const char* name)
    {
        static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>);
        static_assert(!std::is_integral_v<T> || std::numeric_limits<T>::digits <= std::numeric_limits<double>::digits);
        index = _absolute_index(L, index);
        lua_pushstring(L, key);
        lua_rawget(L, index);
        if (lua_isnil(L, -1)) { lua_pop(L, 1); return true; }
        double value = 0;
        bool ok = luaval_to_native(L, -1, &value, name) && std::isfinite(value) &&
            value >= static_cast<double>(std::numeric_limits<T>::lowest()) &&
            value <= static_cast<double>(std::numeric_limits<T>::max());
        if constexpr (std::is_integral_v<T>) ok = ok && std::trunc(value) == value;
        lua_pop(L, 1);
        if (ok) *out = static_cast<T>(value);
        return ok;
    }

    template<typename T>
    bool enumeration(lua_State* L, int index, const char* key, T* out,
        std::initializer_list<T> choices, const char* name)
    {
        static_assert(std::is_enum_v<T>);
        index = _absolute_index(L, index);
        lua_pushstring(L, key);
        lua_rawget(L, index);
        if (lua_isnil(L, -1)) { lua_pop(L, 1); return true; }
        double value = 0;
        const bool ok = luaval_to_native(L, -1, &value, name) && std::isfinite(value);
        lua_pop(L, 1);
        if (ok) for (const auto choice : choices) {
            if (value == static_cast<double>(static_cast<std::underlying_type_t<T>>(choice))) {
                *out = choice;
                return true;
            }
        }
        return false;
    }
}
