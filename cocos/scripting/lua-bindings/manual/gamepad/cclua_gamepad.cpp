#include "cclua_gamepad.hpp"
#include "cclua_gamepad_conversions.hpp"

#include "base/Director.h"
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/auto/cclua_gamepad_auto.hpp"

namespace {
using namespace cc::input;
struct ServiceLifetime {
    std::weak_ptr<const void> token;
};
constexpr const char* lifetimeType = "cc.gamepad.ServiceLifetime";
char lifetimeKey;

int directorGetGamepads(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Director", "cc.Director:getGamepads");
    LUA_TRY_INVOKE_R(0, [](const cc::Director& director) {
        return lua::borrow_value(director.getGamepads());
    });
    LUA_INVOKE_FOOTER("0");
}

template<class T>
void field(lua_State* L, const char* name, const T& value)
{
    lua::native_to_luaval_field(L, -1, name, value);
}
}

template<> struct lua::value_type<ServiceLifetime> : std::true_type {};

void lua::to_lua<lua::borrowed_value<cc::input::GamepadService>>::F(
    lua_State* L, borrowed_value<GamepadService> value)
{
    if (!L) return;
    if (!value.pointer) {
        lua_pushnil(L);
        return;
    }
    // Capture the lifetime before allocations can run Lua finalizers.
    push_value_owned(L, new ServiceLifetime{value.pointer->lifetimeToken()});
    const int lifetime = lua_gettop(L);
    auto** serviceSlot = _prepare_value_userdata<GamepadService>(L, false, 0);
    lua_getfenv(L, -1);
    lua_pushlightuserdata(L, &lifetimeKey);
    lua_pushvalue(L, lifetime);
    lua_rawset(L, -3);
    lua_pop(L, 1);
    lua_remove(L, lifetime);
    *serviceSlot = value.pointer;
}

bool lua::value_userdata_lifetime<cc::input::GamepadService>::valid(lua_State* L, int index)
{
    if (lua_type(L, index) != LUA_TUSERDATA)
        return false;
    lua_getfenv(L, index);
    lua_pushlightuserdata(L, &lifetimeKey);
    lua_rawget(L, -2);
    auto** slot = static_cast<ServiceLifetime**>(luaL_testudata(L, -1, lifetimeType));
    const bool live = slot && *slot && !(*slot)->token.expired();
    lua_pop(L, 2);
    return live;
}

void lua::to_lua<cc::input::GamepadEvent>::F(lua_State* L, const GamepadEvent& value)
{
    lua_createtable(L, 0, 11);
    field(L, "device", value.device);
    field(L, "reportSeq", value.reportSeq);
    field(L, "receivedNs", value.receivedNs);
    field(L, "subIndex", value.subIndex);
    field(L, "sourceNs", value.sourceNs);
    field(L, "timeQuality", value.timeQuality);
    field(L, "reason", value.reason);
    field(L, "kind", value.kind);
    field(L, "order", value.order);
    field(L, "offsetUs", value.offsetUs);
    std::visit([L](const auto& payload) { field(L, "payload", payload); }, value.payload);
}

int register_cc_gamepad_manual(lua_State* L)
{
    tolua_usertype(L, lifetimeType);
    lua::registerLuaType<ServiceLifetime>(lifetimeType, lifetimeType);
    lua::register_value_metatable<ServiceLifetime>(L, lifetimeType);

    luaL_getmetatable(L, "cc.Director");
    lua_pushcfunction(L, directorGetGamepads);
    lua_setfield(L, -2, "getGamepads");
    lua_pop(L, 1);

    const luaL_Reg functions[]{{}};
    luaL_register(L, "cc.gamepad", functions);
    lua_pop(L, 1);
    return 0;
}

int register_cc_gamepad(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.gamepad.registered");
    const bool registered = lua_toboolean(L, -1);
    lua_pop(L, 1);
    if (registered)
        return 0;

    tolua_beginmodule(L, nullptr);
    register_all_cc_gamepad(L);
    tolua_endmodule(L);
    lua_pushboolean(L, 1);
    lua_setfield(L, LUA_REGISTRYINDEX, "cc.gamepad.registered");
    return 0;
}
