#include "cclua_haptics.hpp"
#include "cclua_haptics_conversions.hpp"
#include "base/Director.h"
#include "scripting/lua-bindings/auto/cclua_haptics_auto.hpp"

namespace {
namespace h = cc::haptics;
struct Lifetime { std::weak_ptr<const void> token; };
constexpr auto lifetimeName = "cc.haptics.ServiceLifetime";
char lifetimeKey;

int directorGetHaptics(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.Director", "cc.Director:getHaptics");
    LUA_TRY_INVOKE_R(0, [](const cc::Director& director) { return lua::borrow_value(director.getHaptics()); });
    LUA_INVOKE_FOOTER("0");
}

template<class T> int equalValues(lua_State* L)
{
    const T *left = nullptr, *right = nullptr;
    bool ok = lua_type(L,1) == LUA_TUSERDATA && lua_type(L,2) == LUA_TUSERDATA &&
              lua::read_value_pointer(L,1,&left) && lua::read_value_pointer(L,2,&right);
    if constexpr (std::is_same_v<T,h::HapticService>) lua_pushboolean(L,ok && left == right);
    else if constexpr (requires (T t) { t.id; }) lua_pushboolean(L,ok && left->id == right->id);
    else lua_pushboolean(L,ok && *left == *right);
    return 1;
}
template<class T> void equality(lua_State* L, const char* type)
{
    luaL_getmetatable(L,type);
    lua_pushcfunction(L,equalValues<T>);
    lua_setfield(L,-2,"__eq");
    lua_pop(L,1);
}
template<class T> void registerPrivateType(lua_State* L,const char* name)
{
    tolua_usertype(L,name);
    lua::registerLuaType<T>(name,name);
    lua::register_value_metatable<T>(L,name);
}
constexpr char facade[] = R"lua(
local h = cc.haptics
local lastService, scope
local function service() return cc.Director:getInstance():getHaptics() end
local function defaultScope()
    local current = service()
    if lastService ~= current or not scope then
        if scope then scope:close() end
        local created, err = current:createScope()
        scope, lastService = created, current
        if not created then return nil, err end
    end
    return scope
end
local function checked(method, receiver, ...)
    local ok, result, err = pcall(method, receiver, ...)
    if not ok then return nil, {code="invalidArgument", diagnostics={}} end
    if result == nil then return nil, err end
    return result
end
for _, name in ipairs({"load","parse"}) do
    h[name] = function(...)
        local result, err = checked(h.HapticClip[name], h.HapticClip, ...)
        if not result then return nil, err end
        return result.clip, result.diagnostics
    end
end
for _, name in ipairs({"enumerate","handset","gamepad","capabilities","now","createScope","setCalibration",
                       "setOutputSettings","setPcmModeTiming","preparePcm"}) do
    h[name] = function(...)
        local s = service()
        return checked(s[name],s,...)
    end
end
for _, name in ipairs({"play","stop","stopTarget","readPlayback","readOperation","acquireRaw"}) do
    h[name] = function(...)
        local s, err = defaultScope()
        if not s then return nil, err end
        return checked(s[name],s,...)
    end
end
h.android, h.apple = {}, {}
for group, methods in pairs({[h.android]={"oneShot","waveform","predefined","composition","envelope","cancel"},
                            [h.apple]={"playPattern","sendParameters","sendCurve","stop"}}) do
    for _, name in ipairs(methods) do
        group[name] = function(raw,...) return checked(h.RawSession[name],raw,...) end
    end
end
)lua";
}
template<> struct lua::value_type<Lifetime> : std::true_type {};
void lua::to_lua<lua::borrowed_value<h::HapticService>>::F(lua_State* L, borrowed_value<h::HapticService> value)
{
    if (!value.pointer) { lua_pushnil(L); return; }
    push_value_owned(L,new Lifetime{value.pointer->lifetimeToken()});
    const int token = lua_gettop(L);
    auto** slot = _prepare_value_userdata<h::HapticService>(L,false,0);
    lua_getfenv(L,-1);
    lua_pushlightuserdata(L,&lifetimeKey);
    lua_pushvalue(L,token);
    lua_rawset(L,-3);
    lua_pop(L,1);
    lua_remove(L,token);
    *slot = value.pointer;
}
bool lua::value_userdata_lifetime<h::HapticService>::valid(lua_State* L,int index)
{
    if (lua_type(L,index) != LUA_TUSERDATA) return false;
    lua_getfenv(L,index);
    lua_pushlightuserdata(L,&lifetimeKey);
    lua_rawget(L,-2);
    auto** slot = static_cast<Lifetime**>(luaL_testudata(L,-1,lifetimeName));
    bool valid = slot && *slot && !(*slot)->token.expired();
    lua_pop(L,2);
    return valid;
}
int register_cc_haptics_manual(lua_State* L)
{
    using Target = lua::haptic_detail::Identity<h::TargetId>;
    using Player = lua::haptic_detail::Identity<h::RawPlayerId>;
    registerPrivateType<Lifetime>(L,lifetimeName);
    registerPrivateType<Target>(L,"cc.haptics.TargetId");
    registerPrivateType<Player>(L,"cc.haptics.RawPlayerId");
    equality<Target>(L,"cc.haptics.TargetId");
    equality<Player>(L,"cc.haptics.RawPlayerId");
    equality<h::PlaybackId>(L,"cc.haptics.PlaybackId");
    equality<h::OperationId>(L,"cc.haptics.OperationId");
    equality<h::HapticService>(L,"cc.haptics.HapticService");
    luaL_getmetatable(L,"cc.Director");
    lua_pushcfunction(L,directorGetHaptics);
    lua_setfield(L,-2,"getHaptics");
    lua_pop(L,1);
    if (luaL_loadbuffer(L,facade,sizeof(facade)-1,"@cc/haptics.lua") || lua_pcall(L,0,0,0))
        return lua_error(L);
    return 0;
}
int register_cc_haptics(lua_State* L)
{
    lua_getfield(L,LUA_REGISTRYINDEX,"cc.haptics.registered");
    bool done = lua_toboolean(L,-1);
    lua_pop(L,1);
    if (!done) {
        tolua_beginmodule(L,nullptr);
        register_all_cc_haptics(L);
        tolua_endmodule(L);
        lua_pushboolean(L,1);
        lua_setfield(L,LUA_REGISTRYINDEX,"cc.haptics.registered");
    }
    return 0;
}
