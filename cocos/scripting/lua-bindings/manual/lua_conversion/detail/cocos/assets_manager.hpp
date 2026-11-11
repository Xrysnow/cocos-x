#pragma once

#include "value_types.hpp"
#include "assets-manager/Manifest.h"

namespace lua
{
    template<>
    struct to_lua<cocos2d::extension::ManifestAsset>
    {
        static void F(lua_State* L, const cocos2d::extension::ManifestAsset& inValue)
        {
            if (!L)
                return;

            // Lua allocation may collect objects: stabilize the native data first.
            const auto snapshot = inValue;
            lua_createtable(L, 0, 5);
            native_to_luaval_field(L, -1, "md5", snapshot.md5);
            native_to_luaval_field(L, -1, "path", snapshot.path);
            native_to_luaval_field(L, -1, "compressed", snapshot.compressed);
            native_to_luaval_field(L, -1, "size", snapshot.size);
            native_to_luaval_field(L, -1, "downloadState", snapshot.downloadState);
        }
    };
}
