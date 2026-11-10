#pragma once
#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion.hpp"
#include "ui/GUIDefine.h"
#include "ui/UILayoutParameter.h"

namespace lua
{
    // UI value snapshots use the same field and scalar rules as other modules.
    LUA_TO_NATIVE_STRUCT4(cocos2d::ui::Margin, left, top, right, bottom);
    LUA_TO_LUA_STRUCT4(cocos2d::ui::Margin, left, top, right, bottom);
    // ResourceData is output-only; it has no Lua native identity or ownership.
    LUA_TO_LUA_STRUCT3(cocos2d::ResourceData, type, file, plist);
}
