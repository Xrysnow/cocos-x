#include "cclua_gamepad.hpp"
#include "cclua_gamepad_conversions.hpp"

#include "base/Director.h"
#include "scripting/lua-bindings/auto/cclua_gamepad_auto.hpp"
#include "lua.hpp"
#include "tolua++.h"

namespace {
using namespace cc::input;
using cc::input::gamepad_lua::fail;

constexpr const char* cursorType = "cc.gamepad.EventCursor";
constexpr const char* leaseType = "cc.gamepad.Subscription";
constexpr const char* hapticType = "cc.gamepad.HapticPlayback";
GamepadService& pads()
{
    return cc::Director::getInstance()->getGamepads();
}

template<class T>
void field(lua_State* L, const char* name, const T& value)
{
    lua::native_to_luaval_field(L, -1, name, value);
}

// Standard Ref userdata borrows from the engine. These two types give Lua one
// reference and release it at collection. The pool protects the factory result
// if allocating the userdata raises a Lua error.
template<class T>
void pushOwnedRef(lua_State* L, cc::IntrusivePtr<T>&& owner, const char* type)
{
    if (!L)
        return;
    if (!owner)
    {
        lua_pushnil(L);
        return;
    }
    auto* ref = static_cast<cc::Ref*>(cc::transferToAutoreleasePool(std::move(owner)));
    luaL_getmetatable(L, type);
    auto** slot = static_cast<void**>(lua_newuserdata(L, sizeof(void*)));
    *slot = nullptr;
    lua_insert(L, -2);
    lua_setmetatable(L, -2);
    ref->retain();
    *slot = ref;
}

int collectOwnedRef(lua_State* L)
{
    if (lua_objlen(L, 1) != sizeof(void*))
        return 0;
    auto** slot = static_cast<void**>(luaL_checkudata(L, 1, lua_tostring(L, lua_upvalueindex(1))));
    if (auto* ref = static_cast<cc::Ref*>(std::exchange(*slot, nullptr)))
        ref->release();
    return 0;
}

void registerOwnedRef(lua_State* L, const char* type)
{
    luaL_getmetatable(L, type);
    lua_pushstring(L, type);
    lua_pushcclosure(L, collectOwnedRef, 1);
    lua_setfield(L, -2, "__gc");
    lua_pushstring(L, type);
    lua_setfield(L, -2, "__metatable");
    lua_pop(L, 1);
}

int callCursor(lua_State* L)
{
    EventCursor* cursor = nullptr;
    if (lua_type(L, 1) != LUA_TUSERDATA || !lua::read_value_pointer(L, 1, &cursor))
        return luaL_argerror(L, 1, cursorType);

    const int top = lua_gettop(L);
    lua::native_to_luaval(L, cursor->next());
    return lua_gettop(L) - top;
}

}

namespace cc::input::gamepad_lua {

namespace {
template<class LuaHandle, class Handle>
Result<IntrusivePtr<LuaHandle>> own(Result<Handle> result)
{
    if (!result)
        return {{}, result.error};
    return {IntrusivePtr<LuaHandle>(new LuaHandle(std::move(*result.value)))};
}
}

Error LuaHapticPlayback::seekTime(double seconds)
{
    return _playback.seekTime(seconds);
}

Error LuaHapticPlayback::setLooping(bool enabled)
{
    return _playback.setLooping(enabled);
}

Error LuaHapticPlayback::setIntensity(float intensity)
{
    return _playback.setIntensity(intensity);
}

Error LuaHapticPlayback::close() noexcept
{
    _playback.close();
    return Error::None;
}

Frame frame()
{
    return pads().frame();
}

Result<MappingResult> addGamepadMapping(std::string_view line, MappingSource source)
{
    return {pads().addGamepadMapping(line, source)};
}

Result<ImportReport> importMappings(std::string_view text, MappingSource source)
{
    return {pads().importMappings(text, source)};
}

Result<MappingResult> setLocalBindings(DeviceId id, std::string_view layoutId,
                                       std::string_view fields)
{
    return {pads().setLocalBindings(id, layoutId, fields)};
}

Result<std::string> mappingFor(DeviceId id)
{
    return pads().mappingFor(id);
}

Error clearPlayer(DeviceId id)
{
    return pads().clearPlayer(id);
}

Error assignPlayer(DeviceId id, std::optional<unsigned> slot)
{
    return pads().assignPlayer(id, slot);
}

Result<IntrusivePtr<LuaSubscription>> watchRaw(DeviceId id)
{
    return own<LuaSubscription>(pads().watchRaw(id));
}

Result<IntrusivePtr<LuaSubscription>> subscribeSensor(DeviceId id, Sensor sensor,
                                                      unsigned depth)
{
    return own<LuaSubscription>(pads().subscribeSensor(id, sensor, depth));
}

Result<IntrusivePtr<LuaHapticPlayback>> createHapticPlayback(DeviceId id, AudioSource* source)
{
    if (!source)
        return {{}, Error::InvalidArgument};
    return own<LuaHapticPlayback>(pads().createHapticPlayback(id, *source));
}

Result<CommandId> rumble(DeviceId id, float low, float high, unsigned durationMs)
{
    return pads().rumble(id, low, high, durationMs);
}

Result<CommandId> triggerRumble(DeviceId id, float left, float right, unsigned durationMs)
{
    return pads().triggerRumble(id, left, right, durationMs);
}

Result<CommandId> rgb(DeviceId id, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return pads().rgb(id, r, g, b);
}

Result<CommandId> playerLights(DeviceId id, unsigned mask)
{
    return pads().playerLights(id, mask);
}

Result<CommandId> adaptiveTrigger(DeviceId id, Side side, TriggerMode mode, float start, float strength, float hz)
{
    return pads().adaptiveTrigger(id, side, mode, start, strength, hz);
}

Result<CommandId> stop(DeviceId id, Channel channel)
{
    return pads().stop(id, channel);
}

int fail(lua_State* L, Error error)
{
    lua_pushnil(L);
    lua::native_to_luaval(L, static_cast<int>(error));
    return 2;
}

} // namespace cc::input::gamepad_lua

void lua::to_lua<cc::input::OutputDone>::F(lua_State* L, const OutputDone& value)
{
    lua_createtable(L, 0, 3);
    field(L, "command", value.command);
    field(L, "status", value.status);
    field(L, "error", static_cast<int>(value.error));
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

void lua::to_lua<cc::input::MappingResult>::F(lua_State* L, const MappingResult& value)
{
    native_to_luaval(L, value.sdlCode());
    native_to_luaval(L, value.diagnostics);
}

void lua::to_lua<cc::input::ImportReport>::F(lua_State* L, const ImportReport& value)
{
    lua_createtable(L, 0, 7);
    field(L, "added", value.added);
    field(L, "replaced", value.replaced);
    field(L, "unchanged", value.unchanged);
    field(L, "skipped", value.skipped);
    field(L, "failed", value.failed);
    field(L, "batchError", static_cast<int>(value.batchError));
    field(L, "diagnostics", value.diagnostics);
}

void lua::to_lua<cc::IntrusivePtr<cc::input::gamepad_lua::LuaSubscription>>::F(
    lua_State* L, cc::IntrusivePtr<cc::input::gamepad_lua::LuaSubscription>&& value)
{
    pushOwnedRef(L, std::move(value), leaseType);
}

void lua::to_lua<cc::IntrusivePtr<cc::input::gamepad_lua::LuaHapticPlayback>>::F(
    lua_State* L, cc::IntrusivePtr<cc::input::gamepad_lua::LuaHapticPlayback>&& value)
{
    pushOwnedRef(L, std::move(value), hapticType);
}

void lua::to_lua<cc::input::Error>::F(lua_State* L, cc::input::Error error)
{
    if (error == Error::None)
        lua_pushboolean(L, 1);
    else
        fail(L, error);
}

void lua::to_lua<cc::input::HapticPlaybackSnapshot>::F(lua_State* L,
                                                     const cc::input::HapticPlaybackSnapshot& snapshot)
{
    lua_createtable(L, 0, 8);
    field(L, "state", snapshot.state);
    field(L, "error", static_cast<int>(snapshot.error));
    field(L, "positionSeconds", snapshot.positionSeconds);
    field(L, "durationSeconds", snapshot.durationSeconds);
    field(L, "intensity", snapshot.intensity);
    field(L, "looping", snapshot.looping);
    field(L, "seekable", snapshot.seekable);
    field(L, "stopReason", snapshot.stopReason);
}

int register_cc_gamepad_manual(lua_State* L)
{
    registerOwnedRef(L, leaseType);
    registerOwnedRef(L, hapticType);
    const luaL_Reg functions[]{{}};
    luaL_register(L, "cc.gamepad", functions);
    lua_pop(L, 1);
    luaL_getmetatable(L, cursorType);
    lua_pushcfunction(L, callCursor);
    lua_setfield(L, -2, "__call");
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
