#pragma once

#include "audio/AudioSource.h"
#include "input/gamepad/GamepadService.h"
#include "lua_conversion/lua_conversion_tolua.hpp"

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
LUA_TO_LUA_STRUCT(cc::input::OutputDone, command, status, error)
LUA_TO_LUA_STRUCT(cc::input::DeviceInfo, id, name, mappingGuid, layout, mappingName,
                  vendor, product, version, serial, controllerType)
LUA_TO_LUA_STRUCT(cc::input::MappingResult, change, diagnostics)
LUA_TO_LUA_STRUCT(cc::input::ImportReport, added, replaced, unchanged, skipped, failed, diagnostics, batchError)
LUA_TO_LUA_STRUCT(cc::input::HapticPlaybackSnapshot, state, error, positionSeconds, durationSeconds,
                  intensity, looping, seekable, stopReason)

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

template<> struct value_type<cc::input::Frame> : std::true_type {};
template<> struct value_type<cc::input::Pad> : std::true_type {};
template<> struct value_type<cc::input::EventCursor> : std::true_type {};
template<> struct value_type<cc::input::GamepadService> : std::true_type {};
template<> struct value_type<cc::input::Subscription> : std::true_type {};
template<> struct value_type<cc::input::HapticPlayback> : std::true_type {};

template<> struct to_lua<borrowed_value<cc::input::GamepadService>> {
    static void F(lua_State* L, borrowed_value<cc::input::GamepadService> value);
};

template<> struct value_userdata_lifetime<cc::input::GamepadService> {
    static constexpr bool guarded = true;
    static bool valid(lua_State* L, int index);
};

template<> struct to_lua<cc::input::Subscription> {
    static void F(lua_State* L, cc::input::Subscription&& value)
    {
        if (L)
            push_value_owned(L, new cc::input::Subscription(std::move(value)));
    }
};

template<> struct to_lua<cc::input::HapticPlayback> {
    static void F(lua_State* L, cc::input::HapticPlayback&& value)
    {
        if (L)
            push_value_owned(L, new cc::input::HapticPlayback(std::move(value)));
    }
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
        else {
            lua_pushnil(L);
            native_to_luaval(L, result.error);
        }
    }
};

} // namespace lua
