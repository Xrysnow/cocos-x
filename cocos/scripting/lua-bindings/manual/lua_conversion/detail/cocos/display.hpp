#pragma once
#include "../invoke.hpp"
#include "platform/Display.h"
#include <charconv>

namespace lua {
template<> struct to_native<cc::DisplayId> {
    static bool F(lua_State* L, int index, cc::DisplayId* out, const char* = "") {
        if (lua_type(L, index) != LUA_TSTRING) return false;
        size_t length = 0;
        auto first = lua_tolstring(L, index, &length);
        uint64_t value = 0;
        auto result = std::from_chars(first, first + length, value);
        if (result.ec != std::errc{} || result.ptr != first + length) return false;
        *out = cc::DisplayId{value};
        return true;
    }
};
template<> struct binding_read<cc::DisplayId> {
    template<bool Checked>
    static bool F(lua_State* L, int index, cc::DisplayId* out) { return to_native<cc::DisplayId>::F(L, index, out); }
};
template<> struct to_lua<cc::DisplayId> {
    static void F(lua_State* L, cc::DisplayId id) {
        char buffer[32];
        auto end = std::to_chars(buffer, buffer + sizeof(buffer), static_cast<uint64_t>(id)).ptr;
        lua_pushlstring(L, buffer, end - buffer);
    }
};
template<> struct to_lua<cc::DisplaySize> {
    static void F(lua_State* L, const cc::DisplaySize& value) {
        lua_createtable(L, 0, 2);
        native_to_luaval_field(L, -1, "width", value.width);
        native_to_luaval_field(L, -1, "height", value.height);
    }
};
template<> struct to_lua<cc::DisplayRect> {
    static void F(lua_State* L, const cc::DisplayRect& value) {
        lua_createtable(L, 0, 4);
        native_to_luaval_field(L, -1, "x", value.x);
        native_to_luaval_field(L, -1, "y", value.y);
        native_to_luaval_field(L, -1, "width", value.width);
        native_to_luaval_field(L, -1, "height", value.height);
    }
};
template<> struct to_lua<cc::DisplayAxisValues> {
    static void F(lua_State* L, const cc::DisplayAxisValues& value) {
        lua_createtable(L, 0, 2);
        native_to_luaval_field(L, -1, "x", value.x);
        native_to_luaval_field(L, -1, "y", value.y);
    }
};
template<> struct to_lua<cc::DisplayInfo> {
    static void F(lua_State* L, const cc::DisplayInfo& value) {
        lua_createtable(L, 0, 12);
        native_to_luaval_field(L, -1, "id", value.id);
        native_to_luaval_field(L, -1, "coordinateSpace", value.coordinateSpace);
        native_to_luaval_field(L, -1, "name", value.name);
        native_to_luaval_field(L, -1, "geometry", value.geometry);
        native_to_luaval_field(L, -1, "availableGeometry", value.availableGeometry);
        native_to_luaval_field(L, -1, "pixelSize", value.pixelSize);
        native_to_luaval_field(L, -1, "physicalSizeMm", value.physicalSizeMm);
        native_to_luaval_field(L, -1, "contentScale", value.contentScale);
        native_to_luaval_field(L, -1, "devicePixelRatio", value.devicePixelRatio);
        native_to_luaval_field(L, -1, "logicalDpi", value.logicalDpi);
        native_to_luaval_field(L, -1, "physicalDpi", value.physicalDpi);
        native_to_luaval_field(L, -1, "refreshRateHz", value.refreshRateHz);
    }
};
}
