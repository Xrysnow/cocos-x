#pragma once

#include "audio/AudioSource.h"
#include "cclua_gamepad_views.hpp"
#include "lua_conversion/lua_conversion_tolua.hpp"

#include <cmath>

namespace cc::input::gamepad_lua {

int fail(lua_State* L, Error error);
void pushResult(lua_State* L, const DeviceInfo* value);
void pushResult(lua_State* L, std::span<const DeviceId> value);
void pushResult(lua_State* L, const RawView& value);
void pushResult(lua_State* L, std::span<const Contact> value);
void pushResult(lua_State* L, const Motion& value);
void pushResult(lua_State* L, const Power& value);
void pushResult(lua_State* L, const MappingResult& value);
void pushResult(lua_State* L, const ImportReport& value);
void pushResult(lua_State* L, IntrusivePtr<LuaSubscription>&& value);
void pushResult(lua_State* L, IntrusivePtr<LuaHapticPlayback>&& value);

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

// Validate the Lua number before narrowing it to the enum's underlying type.
template<auto Last>
struct gamepad_enum_read {
    template<bool Checked>
    static bool F(lua_State* L, int index, decltype(Last)* out)
    {
        if (lua_type(L, index) != LUA_TNUMBER)
            return false;
        const auto number = lua_tonumber(L, index);
        if (!(number >= 0 && number <= static_cast<lua_Number>(Last)) || std::trunc(number) != number)
            return false;
        *out = static_cast<decltype(Last)>(number);
        return true;
    }
};

template<> struct binding_read<cc::input::Button> : gamepad_enum_read<cc::input::Button::Misc6> {};
template<> struct binding_read<cc::input::Axis> : gamepad_enum_read<cc::input::Axis::RightTrigger> {};
template<> struct binding_read<cc::input::Sensor> : gamepad_enum_read<cc::input::Sensor::GyroRight> {};
template<> struct binding_read<cc::input::Feature> : gamepad_enum_read<cc::input::Feature::BodyHaptics> {};
template<> struct binding_read<cc::input::Side> : gamepad_enum_read<cc::input::Side::Right> {};
template<> struct binding_read<cc::input::TriggerMode> : gamepad_enum_read<cc::input::TriggerMode::Vibration> {};
template<> struct binding_read<cc::input::Channel> : gamepad_enum_read<cc::input::Channel::Lights> {};
template<> struct binding_read<cc::input::MappingSource> : gamepad_enum_read<cc::input::MappingSource::User> {};

template<class T>
struct to_lua<cc::input::Result<T>> {
    static void F(lua_State* L, cc::input::Result<T>&& result)
    {
        if (result)
            cc::input::gamepad_lua::pushResult(L, std::move(*result.value));
        else
            cc::input::gamepad_lua::fail(L, result.error);
    }
};

template<> struct to_lua<cc::input::gamepad_lua::NoResults> {
    static void F(lua_State*, cc::input::gamepad_lua::NoResults) {}
};

template<> struct to_lua<cc::input::Error> {
    static void F(lua_State* L, cc::input::Error error);
};

template<> struct to_lua<cc::input::HapticPlaybackSnapshot> {
    static void F(lua_State* L, const cc::input::HapticPlaybackSnapshot& snapshot);
};

} // namespace lua
