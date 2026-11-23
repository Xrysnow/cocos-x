#pragma once

#include "audio/AudioSource.h"
#include "cclua_gamepad_views.hpp"
#include "lua_conversion/lua_conversion_tolua.hpp"

#include <cmath>

namespace cc::input::gamepad_lua {

int fail(lua_State* L, Error error);

} // namespace cc::input::gamepad_lua

namespace lua {

LUA_TO_LUA_STRUCT(cc::input::RawView, buttons, axes, hats)
LUA_TO_LUA_STRUCT(cc::input::Diagnostic, line, column, code, message)
LUA_TO_LUA_STRUCT(cc::input::Contact, pad, finger, phase, x, y, pressure)
LUA_TO_LUA_STRUCT(cc::input::Motion, sensor, xyz)
LUA_TO_LUA_STRUCT(cc::input::Power, state, percent, level)
LUA_TO_LUA_STRUCT(cc::input::DeviceInfo, id, name, mappingGuid, layout, mappingName,
                  vendor, product, version, serial, controllerType)

template<> struct to_lua<const cc::input::DeviceInfo*> {
    static void F(lua_State* L, const cc::input::DeviceInfo* info)
    {
        if (!L) return;
        if (info)
            native_to_luaval(L, *info);
        else
            lua_pushnil(L);
    }
};

template<> struct to_lua<cc::input::MappingResult> {
    static void F(lua_State* L, const cc::input::MappingResult& value);
};

template<> struct to_lua<cc::input::ImportReport> {
    static void F(lua_State* L, const cc::input::ImportReport& value);
};

template<> struct to_lua<cc::IntrusivePtr<cc::input::gamepad_lua::LuaSubscription>> {
    static void F(lua_State* L, cc::IntrusivePtr<cc::input::gamepad_lua::LuaSubscription>&& value);
};

template<> struct to_lua<cc::IntrusivePtr<cc::input::gamepad_lua::LuaHapticPlayback>> {
    static void F(lua_State* L, cc::IntrusivePtr<cc::input::gamepad_lua::LuaHapticPlayback>&& value);
};

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
            native_to_luaval(L, std::move(*result.value));
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
