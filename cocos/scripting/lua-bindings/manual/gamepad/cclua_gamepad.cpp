#include "cclua_gamepad.hpp"
#include "cclua_gamepad_conversions.hpp"

#include "base/Director.h"
#include "scripting/lua-bindings/auto/cclua_gamepad_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "lua.hpp"
#include "tolua++.h"

#include <type_traits>

namespace {
using namespace cc::input;
using cc::input::gamepad_lua::fail;
using cc::input::gamepad_lua::Frame;

constexpr const char* frameType = "cc.gamepad.Frame";
constexpr const char* leaseType = "cc.gamepad.Subscription";
constexpr const char* hapticType = "cc.gamepad.HapticPlayback";
GamepadService& pads()
{
    return cc::Director::getInstance()->getGamepads();
}

void push(lua_State* L, std::string_view value) { lua_pushlstring(L, value.data() ? value.data() : "", value.size()); }
void push(lua_State* L, bool value) { lua_pushboolean(L, value); }
void push(lua_State* L, const std::string& value) { push(L, std::string_view(value)); }
template<class T> requires (std::is_arithmetic_v<T> || std::is_enum_v<T>)
void push(lua_State* L, T value) { lua_pushnumber(L, static_cast<lua_Number>(value)); }

template<class T>
void push(lua_State* L, const std::optional<T>& value)
{
    if (value)
        push(L, *value);
    else
        lua_pushnil(L);
}

template<class T>
void field(lua_State* L, const char* name, const T& value)
{
    push(L, value);
    lua_setfield(L, -2, name);
}

template<class T>
void list(lua_State* L, std::span<const T> values)
{
    lua_createtable(L, static_cast<int>(values.size()), 0);
    int index = 1;
    for (const auto& value : values)
    {
        push(L, value);
        lua_rawseti(L, -2, index++);
    }
}

// Standard Ref userdata borrows from the engine. These two types give Lua one
// reference and release it at collection. The pool protects the factory result
// if allocating the userdata raises a Lua error.
template<class T>
void pushOwnedRef(lua_State* L, cc::IntrusivePtr<T>&& owner, const char* type)
{
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

template<class T>
auto current(lua_State* L, int index, const char* type)
{
    const T* view = nullptr;
    if (lua_type(L, index) != LUA_TUSERDATA || !lua::read_value_pointer(L, index, &view))
    {
        luaL_argerror(L, index, type);
        return decltype(view->current()){};
    }
    return view->current();
}

void addContact(lua_State* L, const Contact& contact)
{
    field(L, "pad", contact.pad);
    field(L, "finger", contact.finger);
    field(L, "phase", contact.phase);
    field(L, "x", contact.x);
    field(L, "y", contact.y);
    field(L, "pressure", contact.pressure);
}

void addMotion(lua_State* L, const Motion& motion)
{
    field(L, "sensor", motion.sensor);
    list(L, std::span<const float>(motion.xyz));
    lua_setfield(L, -2, "xyz");
}

void addPower(lua_State* L, const Power& power)
{
    field(L, "state", power.state);
    field(L, "percent", power.percent);
    field(L, "level", power.level);
}

void event(lua_State* L, const GamepadEvent& e, std::uint64_t cutoff, std::size_t sequence)
{
    lua_createtable(L, 0, 10);
    field(L, "device", e.device);
    field(L, "order", sequence);
    field(L, "reason", e.reason);
    field(L, "timeQuality", e.timeQuality);
    const auto delta = e.receivedNs >= cutoff ? static_cast<double>(e.receivedNs - cutoff)
                                              : -static_cast<double>(cutoff - e.receivedNs);
    field(L, "offsetUs", delta / 1000.0);
    std::visit([&](const auto& payload) {
        using T = std::decay_t<decltype(payload)>;
        if constexpr (std::is_same_v<T, DeviceChange>)
        {
            field(L, "kind", EventKind::Device);
            field(L, "change", payload.kind);
            field(L, "revision", payload.revision);
        }
        else if constexpr (std::is_same_v<T, ButtonEdge>)
        {
            field(L, "kind", EventKind::Button);
            field(L, "button", payload.button);
            field(L, "down", payload.down);
        }
        else if constexpr (std::is_same_v<T, AxisChange>)
        {
            field(L, "kind", EventKind::Axis);
            field(L, "axis", payload.axis);
            field(L, "value", payload.value);
        }
        else if constexpr (std::is_same_v<T, RawChange>)
        {
            field(L, "kind", EventKind::Raw);
            field(L, "control", payload.kind);
            field(L, "index", payload.index);
            field(L, "value", payload.value);
        }
        else if constexpr (std::is_same_v<T, Contact>)
        {
            field(L, "kind", EventKind::Contact);
            addContact(L, payload);
        }
        else if constexpr (std::is_same_v<T, Motion>)
        {
            field(L, "kind", EventKind::Motion);
            addMotion(L, payload);
        }
        else if constexpr (std::is_same_v<T, Power>)
        {
            field(L, "kind", EventKind::Power);
            addPower(L, payload);
        }
        else if constexpr (std::is_same_v<T, InputGap>)
        {
            field(L, "kind", EventKind::InputGap);
            field(L, "cause", payload.cause);
            field(L, "lostCount", payload.lostCount);
        }
        else if constexpr (std::is_same_v<T, OutputDone>)
        {
            field(L, "kind", EventKind::OutputDone);
            field(L, "command", payload.command);
            field(L, "status", payload.status);
            field(L, "error", payload.error);
        }
    }, e.payload);
}

int nextEvent(lua_State* L)
{
    const auto* f = current<Frame>(L, lua_upvalueindex(1), frameType);
    if (!f)
        return fail(L, Error::StaleFrame);
    const auto index = static_cast<std::size_t>(lua_tointeger(L, lua_upvalueindex(2)));
    if (index >= f->events().size())
        return 0;
    push(L, index + 1);
    lua_replace(L, lua_upvalueindex(2));
    event(L, f->events()[index], f->cutoffNs(), index + 1);
    return 1;
}

int events(lua_State* L)
{
    if (!current<Frame>(L, 1, frameType))
        return fail(L, Error::StaleFrame);
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, nextEvent, 2);
    return 1;
}

void diagnostics(lua_State* L, const std::vector<Diagnostic>& values)
{
    lua_createtable(L, static_cast<int>(values.size()), 0);
    int index = 1;
    for (const auto& value : values)
    {
        lua_createtable(L, 0, 4);
        field(L, "line", value.line);
        field(L, "column", value.column);
        field(L, "code", value.code);
        field(L, "message", value.message);
        lua_rawseti(L, -2, index++);
    }
}


}

namespace cc::input::gamepad_lua {

namespace {
template<auto Getter, class T>
auto query(const T* view) noexcept -> Result<decltype((view->*Getter)())>
{
    if (!view)
        return {{}, Error::StaleFrame};
    return {(view->*Getter)()};
}

template<auto Getter, class T, class Key>
auto query(const T* view, Key key) noexcept -> Result<decltype((view->*Getter)(key))>
{
    if (!view)
        return {{}, Error::StaleFrame};
    return {(view->*Getter)(key)};
}

template<class LuaHandle, class Handle>
Result<IntrusivePtr<LuaHandle>> own(Result<Handle> result)
{
    if (!result)
        return {{}, result.error};
    return {IntrusivePtr<LuaHandle>(new LuaHandle(std::move(*result.value)))};
}
}

Result<double> Frame::tick() const noexcept
{
    if (const auto* frame = current())
        return {static_cast<double>(frame->tick())};
    return {{}, Error::StaleFrame};
}

Result<std::span<const DeviceId>> Frame::devices() const noexcept
{
    return query<&GamepadFrame::devices>(current());
}

Result<std::optional<Pad>> Frame::find(DeviceId id) const noexcept
{
    const auto* frame = current();
    if (!frame)
        return {{}, Error::StaleFrame};
    if (const auto* pad = frame->find(id))
        return {std::optional<Pad>(std::in_place, *frame, *pad)};
    return {std::optional<Pad>{}};
}

Result<const DeviceInfo*> Pad::info() const noexcept
{
    if (const auto* pad = current())
        return {&pad->info()};
    return {{}, Error::StaleFrame};
}

Result<bool> Pad::mapped() const noexcept
{
    return query<&PadView::mapped>(current());
}

Result<std::string_view> Pad::inputLayout() const noexcept
{
    return query<&PadView::inputLayout>(current());
}

Result<std::string_view> Pad::mappingStatus() const noexcept
{
    return query<&PadView::mappingStatus>(current());
}

Result<std::uint32_t> Pad::mappingRevision() const noexcept
{
    return query<&PadView::mappingRevision>(current());
}

Result<std::optional<unsigned>> Pad::player() const noexcept
{
    return query<&PadView::player>(current());
}

Result<bool> Pad::down(Button key) const noexcept
{
    return query<&PadView::down>(current(), key);
}

Result<bool> Pad::pressed(Button key) const noexcept
{
    return query<&PadView::pressed>(current(), key);
}

Result<bool> Pad::released(Button key) const noexcept
{
    return query<&PadView::released>(current(), key);
}

Result<std::string_view> Pad::label(Button key) const noexcept
{
    return query<&PadView::label>(current(), key);
}

Result<std::optional<float>> Pad::axis(Axis key) const noexcept
{
    return query<&PadView::axis>(current(), key);
}

Result<std::optional<std::int16_t>> Pad::axisValue(Axis key) const noexcept
{
    return query<&PadView::axisValue>(current(), key);
}

Result<bool> Pad::hasButton(Button key) const noexcept
{
    if (const auto* pad = current())
        return {pad->caps().has(key)};
    return {{}, Error::StaleFrame};
}

Result<bool> Pad::hasAxis(Axis key) const noexcept
{
    if (const auto* pad = current())
        return {pad->caps().has(key)};
    return {{}, Error::StaleFrame};
}

Result<bool> Pad::hasSensor(Sensor key) const noexcept
{
    if (const auto* pad = current())
        return {pad->caps().has(key)};
    return {{}, Error::StaleFrame};
}

Result<bool> Pad::hasFeature(Feature key) const noexcept
{
    if (const auto* pad = current())
        return {pad->caps().has(key)};
    return {{}, Error::StaleFrame};
}

Result<RawView> Pad::raw() const noexcept
{
    return query<&PadView::raw>(current());
}

Result<std::span<const Contact>> Pad::contacts() const noexcept
{
    return query<&PadView::contacts>(current());
}

Result<std::optional<Motion>> Pad::latest(Sensor sensor) const noexcept
{
    return query<&PadView::latest>(current(), sensor);
}

Result<Power> Pad::power() const noexcept
{
    return query<&PadView::power>(current());
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
    return Frame(pads().frame());
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
    return pads().assignPlayer(id, std::nullopt);
}

Error assignPlayer(DeviceId id, unsigned slot)
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
    return pads().submit(id, Rumble{low, high, std::chrono::milliseconds(durationMs)});
}

Result<CommandId> triggerRumble(DeviceId id, float left, float right, unsigned durationMs)
{
    return pads().submit(id, TriggerRumble{left, right, std::chrono::milliseconds(durationMs)});
}

Result<CommandId> rgb(DeviceId id, std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    return pads().submit(id, Rgb{r, g, b});
}

Result<CommandId> playerLights(DeviceId id, unsigned mask)
{
    return pads().submit(id, PlayerLights{mask});
}

Result<CommandId> adaptiveTrigger(DeviceId id, Side side, TriggerMode mode, float start, float strength, float hz)
{
    return pads().submit(id, AdaptiveTrigger{side, mode, start, strength, hz});
}

Result<CommandId> stop(DeviceId id, Channel channel)
{
    return pads().submit(id, Stop{channel});
}

int fail(lua_State* L, Error error)
{
    lua_pushnil(L);
    push(L, error);
    return 2;
}

void pushResult(lua_State* L, const DeviceInfo* value)
{
    const auto& info = *value;
    lua_createtable(L, 0, 10);
    field(L, "id", info.id);
    field(L, "name", info.name);
    field(L, "mappingGuid", info.mappingGuid);
    field(L, "layout", info.layout);
    field(L, "mappingName", info.mappingName);
    field(L, "vendor", info.vendor);
    field(L, "product", info.product);
    field(L, "version", info.version);
    field(L, "serial", info.serial);
    lua::native_to_luaval(L, info.controllerType);
    lua_setfield(L, -2, "controllerType");
}

void pushResult(lua_State* L, std::span<const DeviceId> value)
{
    list(L, value);
}

void pushResult(lua_State* L, const RawView& value)
{
    lua_createtable(L, 0, 3);
    list(L, value.buttons);
    lua_setfield(L, -2, "buttons");
    list(L, value.axes);
    lua_setfield(L, -2, "axes");
    list(L, value.hats);
    lua_setfield(L, -2, "hats");
}

void pushResult(lua_State* L, std::span<const Contact> values)
{
    lua_createtable(L, static_cast<int>(values.size()), 0);
    int index = 1;
    for (const auto& contact : values)
    {
        lua_createtable(L, 0, 6);
        addContact(L, contact);
        lua_rawseti(L, -2, index++);
    }
}

void pushResult(lua_State* L, const Motion& value)
{
    lua_createtable(L, 0, 2);
    addMotion(L, value);
}

void pushResult(lua_State* L, const Power& value)
{
    lua_createtable(L, 0, 3);
    addPower(L, value);
}

void pushResult(lua_State* L, const MappingResult& value)
{
    push(L, value.sdlCode());
    diagnostics(L, value.diagnostics);
}

void pushResult(lua_State* L, const ImportReport& value)
{
    lua_createtable(L, 0, 7);
    field(L, "added", value.added);
    field(L, "replaced", value.replaced);
    field(L, "unchanged", value.unchanged);
    field(L, "skipped", value.skipped);
    field(L, "failed", value.failed);
    field(L, "batchError", value.batchError);
    diagnostics(L, value.diagnostics);
    lua_setfield(L, -2, "diagnostics");
}

void pushResult(lua_State* L, IntrusivePtr<LuaSubscription>&& value)
{
    pushOwnedRef(L, std::move(value), leaseType);
}

void pushResult(lua_State* L, IntrusivePtr<LuaHapticPlayback>&& value)
{
    pushOwnedRef(L, std::move(value), hapticType);
}

} // namespace cc::input::gamepad_lua

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
    field(L, "error", snapshot.error);
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
    tolua_beginmodule(L, "Frame");
    tolua_function(L, "events", events);
    tolua_endmodule(L);
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
