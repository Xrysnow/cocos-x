#pragma once
#include "scripting/lua-bindings/manual/lua_conversion/lua_conversion.hpp"

// P4 only replaces these event methods. The complete UI class definitions,
// inheritance, constructors and unrelated manual methods remain with UI.
#undef LUA_CLS_DEF
#define LUA_CLS_DEF(T_, TType_, TName_, Ctor_, Dtor_) \
    luaL_getmetatable(lua_S, (TName_)); \
    if (!lua_istable(lua_S, -1)) \
        return luaL_error(lua_S, "UI event extension requires '%s'", (TName_));
#undef LUA_CLS_DEF_BASE
#define LUA_CLS_DEF_BASE(T_, TType_, TName_, BT_, BName_, Ctor_, Dtor_) \
    LUA_CLS_DEF(T_, TType_, TName_, Ctor_, Dtor_)
#undef LUA_CLS_END
#define LUA_CLS_END() lua_pop(lua_S, 1);

// A single selected callback still needs checked conversion in Release.
#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_)
