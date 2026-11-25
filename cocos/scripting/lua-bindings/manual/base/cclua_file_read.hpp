#pragma once

#include "platform/FileReadAdapter.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include <charconv>
#include <limits>
#include <new>
#include <utility>

namespace cc::luaio
{
inline std::string_view checkString(lua_State* L, int index)
{
    size_t size;
    const auto data = luaL_checklstring(L, index, &size);
    return {data, size};
}

inline void pushString(lua_State* L, std::string_view value)
{
    lua_pushlstring(L, value.empty() ? "" : value.data(), value.size());
}

template<class Integer>
void pushDecimal(lua_State* L, Integer value)
{
    char buffer[std::numeric_limits<Integer>::digits10 + 3];
    const auto result = std::to_chars(buffer, buffer + sizeof(buffer), value);
    lua_pushlstring(L, buffer, result.ptr - buffer);
}

template<class Integer>
void pushExact(lua_State* L, Integer value)
{
    constexpr int64_t maxExact = 9007199254740991;
    if (std::cmp_greater(value, maxExact) || std::cmp_less(value, -maxExact))
        pushDecimal(L, value);
    else
        lua_pushnumber(L, static_cast<lua_Number>(value));
}

inline void setString(lua_State* L, const char* name, std::string_view value)
{
    pushString(L, value);
    lua_setfield(L, -2, name);
}

inline void setNumber(lua_State* L, const char* name, lua_Number value)
{
    lua_pushnumber(L, value);
    lua_setfield(L, -2, name);
}

inline int pushError(lua_State* L, io::StreamError error)
{
    lua_pushnil(L);
    lua_createtable(L, 0, 3);
    setNumber(L, "code", static_cast<int>(error.code));
    setNumber(L, "domain", static_cast<int>(error.domain));
    setNumber(L, "nativeCode", error.nativeCode);
    return 2;
}

inline int pushStatus(lua_State* L, io::Status status)
{
    if (!status)
        return pushError(L, status.error);
    lua_pushboolean(L, true);
    return 1;
}

template<class T, class... Args>
void pushObject(lua_State* L, const char* metatable, Args&&... args)
{
    new (lua_newuserdata(L, sizeof(T))) T(std::forward<Args>(args)...);
    luaL_getmetatable(L, metatable);
    lua_setmetatable(L, -2);
}

template<class T>
const T& checkObject(lua_State* L, int index, const char* metatable)
{
    return *static_cast<const T*>(luaL_checkudata(L, index, metatable));
}

inline const FileHit& checkFileHit(lua_State* L, int index)
{
    return checkObject<FileHit>(L, index, "cc.FileHit");
}

template<class T>
int destroyObject(lua_State* L)
{
    static_cast<T*>(lua_touserdata(L, 1))->~T();
    return 0;
}
}
