#pragma once

#include "cclua_gamepad_views.hpp"
#include "lua_conversion/lua_conversion_tolua.hpp"

namespace cc::input::gamepad_lua {

int fail(lua_State* L, Error error);
void pushResult(lua_State* L, const DeviceInfo* value);
void pushResult(lua_State* L, std::span<const DeviceId> value);

template<class T>
void pushResult(lua_State* L, const T& value)
{
    lua::native_to_luaval(L, value);
}

template<class T>
void pushResult(lua_State* L, const std::optional<T>& value)
{
    if (value)
        pushResult(L, *value);
    else
        lua_pushnil(L);
}

} // namespace cc::input::gamepad_lua

namespace lua {

template<> struct value_type<cc::input::gamepad_lua::Frame> : std::true_type {};
template<> struct value_type<cc::input::gamepad_lua::Pad> : std::true_type {};

template<class T>
struct to_lua<cc::input::Result<T>> {
    static void F(lua_State* L, const cc::input::Result<T>& result)
    {
        if (result)
            cc::input::gamepad_lua::pushResult(L, *result.value);
        else
            cc::input::gamepad_lua::fail(L, result.error);
    }
};

} // namespace lua
