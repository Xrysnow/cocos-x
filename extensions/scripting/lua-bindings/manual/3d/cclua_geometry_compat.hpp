#pragma once
#include "../lua_conversion/lua_conversion.hpp"

// Legacy geometry methods silently return no values on argument conversion
// failure. Invalid receivers and arity still raise; constructors use the
// unchanged static footer. Keep this policy local to the migrated module.
#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_)\
    if (arg_cur == -1)\
        return luaL_error(lua_S, "wrong number of arguments in '%s': %d, expects %s", LUA_FNAME, argc, Expected_);\
    else if (arg_cur == 0)\
        return luaL_error(lua_S, "invalid class object in '%s'", LUA_FNAME);\
    return 0;
