#pragma once

#include "audio/AudioSource.h"
#include "cclua_gamepad_views.hpp"
#include "lua_conversion/lua_conversion_tolua.hpp"

namespace cc::input::gamepad_lua {

int fail(lua_State* L, Error error);

} // namespace cc::input::gamepad_lua

namespace lua {

LUA_TO_LUA_STRUCT(cc::input::RawView, buttons, axes, hats)
LUA_TO_LUA_STRUCT(cc::input::Diagnostic, line, column, code, message)
LUA_TO_LUA_STRUCT(cc::input::Contact, pad, finger, phase, x, y, pressure)
LUA_TO_LUA_STRUCT(cc::input::Motion, sensor, xyz, deviceTimeNs)
LUA_TO_LUA_STRUCT(cc::input::Power, state, percent, level)
LUA_TO_LUA_STRUCT(cc::input::TriggerLimits, resistance, vibration, minHz, maxHz)
LUA_TO_LUA_STRUCT(cc::input::DeviceChange, kind, revision)
LUA_TO_LUA_STRUCT(cc::input::ButtonEdge, button, down)
LUA_TO_LUA_STRUCT(cc::input::AxisChange, axis, value)
LUA_TO_LUA_STRUCT(cc::input::RawChange, kind, index, value)
LUA_TO_LUA_STRUCT(cc::input::InputGap, cause, lostCount)
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

template<> struct value_type<cc::input::Frame> : std::true_type {};
template<> struct value_type<cc::input::Pad> : std::true_type {};
template<> struct value_type<cc::input::EventCursor> : std::true_type {};

template<> struct to_lua<cc::input::OutputDone> {
    static void F(lua_State* L, const cc::input::OutputDone& value);
};

template<> struct to_lua<cc::input::GamepadEvent> {
    static void F(lua_State* L, const cc::input::GamepadEvent& value);
};

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
