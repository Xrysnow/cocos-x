#pragma once
#include "../conversion.hpp"
#include "3d/CCTerrain.h"
#include <cmath>

namespace lua {
namespace terrain_detail {
inline bool chunkSize(lua_State* L, int index, cocos2d::Vec2* value, const char* name) {
    lua_getfield(L, index, "_chunkSize");
    bool ok = lua_isnil(L, -1);
    if (!ok && lua_istable(L, -1)) {
        const int size = lua_gettop(L);
        // This descriptor uses Vec2 fields, not the historical Size aliases.
        ok = luaval_field_to_native(L, size, "x", &value->x, name) &&
             luaval_field_to_native(L, size, "y", &value->y, name);
    }
    lua_pop(L, 1);
    return ok;
}
template<class T>
bool optional(lua_State* L, int index, const char* key, T* value, const char* name) {
    lua_getfield(L, index, key);
    const bool ok = lua_isnil(L, -1) || luaval_to_native(L, -1, value, name);
    lua_pop(L, 1);
    return ok;
}
}

template<> struct to_native<cocos2d::Terrain::DetailMap> {
    static bool F(lua_State* L, int lo, cocos2d::Terrain::DetailMap* out, const char* name = "") {
        if (!L || !out || !lua_istable(L, lo)) return false;
        if (lo < 0) lo = lua_gettop(L) + lo + 1;
        cocos2d::Terrain::DetailMap value;
        // Preserve the Lua descriptor default, distinct from the native constructor's 35.
        value._detailMapSize = 0;
        if (!terrain_detail::optional(L, lo, "_detailMapSrc", &value._detailMapSrc, name) ||
            !terrain_detail::optional(L, lo, "_detailMapSize", &value._detailMapSize, name)) return false;
        *out = std::move(value);
        return true;
    }
};

template<> struct to_lua<cocos2d::Terrain::DetailMap> {
    static void F(lua_State* L, const cocos2d::Terrain::DetailMap& value) {
        lua_createtable(L, 0, 2);
        native_to_luaval_field(L, -1, "_detailMapSrc", value._detailMapSrc);
        native_to_luaval_field(L, -1, "_detailMapSize", value._detailMapSize);
    }
};

template<> struct to_native<cocos2d::Terrain::TerrainData> {
    static bool F(lua_State* L, int lo, cocos2d::Terrain::TerrainData* out, const char* name = "") {
        if (!L || !out || !lua_istable(L, lo)) return false;
        if (lo < 0) lo = lua_gettop(L) + lo + 1;
        cocos2d::Terrain::TerrainData value;
        value._chunkSize = cocos2d::Vec2(32, 32);
        value._mapHeight = 2;
        value._mapScale = 0.1f;
        value._detailMapAmount = 0;
        value._skirtHeightRatio = 1;
        if (!terrain_detail::chunkSize(L, lo, &value._chunkSize, name) ||
            !terrain_detail::optional(L, lo, "_heightMapSrc", &value._heightMapSrc, name) ||
            !terrain_detail::optional(L, lo, "_alphaMapSrc", &value._alphaMapSrc, name) ||
            !terrain_detail::optional(L, lo, "_mapHeight", &value._mapHeight, name) ||
            !terrain_detail::optional(L, lo, "_mapScale", &value._mapScale, name) ||
            !terrain_detail::optional(L, lo, "_detailMapAmount", &value._detailMapAmount, name) ||
            !terrain_detail::optional(L, lo, "_skirtHeightRatio", &value._skirtHeightRatio, name)) return false;
        lua_getfield(L, lo, "_detailMaps");
        size_t count = 0;
        bool ok = lua_isnil(L, -1);
        if (lua_istable(L, -1)) {
            const int maps = lua_gettop(L);
            const size_t length = lua_objlen(L, maps);
            ok = length <= 4;
            // Check all keys too: Lua's length alone does not bound sparse entries.
            lua_pushnil(L);
            while (lua_next(L, maps)) {
                const lua_Number key = lua_tonumber(L, -2);
                ok = ok && lua_type(L, -2) == LUA_TNUMBER && key >= 1 && key <= length && key == std::floor(key);
                ++count;
                lua_pop(L, 1);
            }
            ok = ok && count == length;
            for (size_t i = 0; ok && i < length; ++i) {
                lua_rawgeti(L, maps, static_cast<int>(i + 1));
                ok = luaval_to_native(L, -1, &value._detailMaps[i], name);
                lua_pop(L, 1);
            }
        }
        lua_pop(L, 1);
        if (!ok || value._detailMapAmount < 0 || value._detailMapAmount > 4 ||
            static_cast<size_t>(value._detailMapAmount) > count) return false;
        *out = std::move(value);
        return true;
    }
};

template<> struct to_lua<cocos2d::Terrain::TerrainData> {
    static void F(lua_State* L, const cocos2d::Terrain::TerrainData& value) {
        lua_createtable(L, 0, 8);
        native_to_luaval_field(L, -1, "_chunkSize", value._chunkSize);
        native_to_luaval_field(L, -1, "_heightMapSrc", value._heightMapSrc);
        native_to_luaval_field(L, -1, "_alphaMapSrc", value._alphaMapSrc);
        lua_createtable(L, 4, 0);
        for (int i = 0; i < 4; ++i) {
            native_to_luaval(L, value._detailMaps[i]);
            lua_rawseti(L, -2, i + 1);
        }
        lua_setfield(L, -2, "_detailMaps");
        native_to_luaval_field(L, -1, "_mapHeight", value._mapHeight);
        native_to_luaval_field(L, -1, "_mapScale", value._mapScale);
        native_to_luaval_field(L, -1, "_detailMapAmount", value._detailMapAmount);
        native_to_luaval_field(L, -1, "_skirtHeightRatio", value._skirtHeightRatio);
    }
};
}
