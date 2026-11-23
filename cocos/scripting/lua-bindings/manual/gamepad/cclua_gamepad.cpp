#include "cclua_gamepad.hpp"

#include "base/Director.h"
#include "input/gamepad/GamepadService.h"
#include "lua.hpp"
#include "tolua++.h"

#include <cmath>
#include <limits>
#include <memory>
#include <type_traits>

namespace {
using namespace cc::input;
using namespace std::string_view_literals;

constexpr const char* frameType = "cc.gamepad.Frame";
constexpr const char* padType = "cc.gamepad.Pad";
constexpr const char* leaseType = "cc.gamepad.Subscription";
constexpr const char* hapticType = "cc.gamepad.HapticPlayback";
using HapticHandle = std::optional<HapticPlayback>;
constexpr std::array buttons{
    "south"sv, "east"sv, "west"sv, "north"sv, "back"sv, "guide"sv, "start"sv, "leftstick"sv, "rightstick"sv,
    "leftshoulder"sv, "rightshoulder"sv, "dpup"sv, "dpdown"sv, "dpleft"sv, "dpright"sv,
    "misc1"sv, "rightpaddle1"sv, "leftpaddle1"sv, "rightpaddle2"sv, "leftpaddle2"sv, "touchpad"sv,
    "misc2"sv, "misc3"sv, "misc4"sv, "misc5"sv, "misc6"sv
};
constexpr std::array axes{"leftx"sv, "lefty"sv, "rightx"sv, "righty"sv, "lefttrigger"sv, "righttrigger"sv};
constexpr std::array sensors{"accel"sv, "gyro"sv, "accelLeft"sv, "gyroLeft"sv, "accelRight"sv, "gyroRight"sv};
constexpr std::array features{"bodyRumble"sv, "triggerRumble"sv, "monoLed"sv, "rgbLed"sv,
                              "playerLights"sv, "adaptiveLeft"sv, "adaptiveRight"sv, "bodyHaptics"sv};
constexpr std::array reasons{"physical"sv, "connect"sv, "disconnect"sv, "focusLost"sv, "focusGained"sv,
                             "remap"sv, "resync"sv, "configuration"sv, "command"sv};
constexpr std::array errors{"None"sv, "Unsupported"sv, "Disconnected"sv, "Busy"sv, "PermissionDenied"sv,
                            "InvalidArgument"sv, "NoMapping"sv, "BackendFailure"sv, "QueueFull"sv, "StaleFrame"sv};
constexpr std::array changes{"connected"sv, "disconnected"sv, "mappingChanged"sv, "capabilitiesChanged"sv,
                             "baselineReady"sv, "focusLost"sv, "focusGained"sv, "playerChanged"sv};
constexpr std::array sides{"left"sv, "right"sv};
constexpr std::array modes{"off"sv, "resistance"sv, "vibration"sv};
constexpr std::array channels{"all"sv, "body"sv, "triggers"sv, "adaptiveLeft"sv, "adaptiveRight"sv, "lights"sv};
constexpr std::array sources{"builtIn"sv, "application"sv, "user"sv};
constexpr std::array playbackStates{"ready"sv, "buffering"sv, "playing"sv, "paused"sv,
                                    "stopped"sv, "ended"sv, "failed"sv, "closed"sv};
constexpr std::array stopReasons{"none"sv, "requested"sv, "replaced"sv, "focusLost"sv,
                                 "endpointLost"sv, "disconnected"sv};
static_assert(buttons.size() == ButtonCount && axes.size() == AxisCount &&
              sensors.size() == SensorCount && features.size() == FeatureCount);

template<class T>
struct View {
    FrameStamp stamp;
    const T* pointer;
};

GamepadService& pads()
{
    return cc::Director::getInstance()->getGamepads();
}

std::string_view string(lua_State* L, int i)
{
    if (lua_type(L, i) != LUA_TSTRING)
        return {};
    std::size_t size;
    const auto* bytes = lua_tolstring(L, i, &size);
    return {bytes, size};
}

template<class E, std::size_t N>
std::optional<E> lookup(std::string_view key, const std::array<std::string_view, N>& names)
{
    for (std::size_t i = 0; i < names.size(); ++i)
        if (names[i] == key)
            return static_cast<E>(i);
    return {};
}

template<class T>
std::optional<T> number(lua_State* L, int i)
{
    if (lua_type(L, i) != LUA_TNUMBER)
        return {};
    const auto value = lua_tonumber(L, i);
    if (!std::isfinite(value) || value < std::numeric_limits<T>::lowest() || value > std::numeric_limits<T>::max())
        return {};
    if constexpr (std::is_integral_v<T>)
        if (std::trunc(value) != value)
            return {};
    return static_cast<T>(value);
}

void push(lua_State* L, std::string_view value) { lua_pushlstring(L, value.data() ? value.data() : "", value.size()); }
void push(lua_State* L, bool value) { lua_pushboolean(L, value); }
void push(lua_State* L, const char* value) { lua_pushstring(L, value); }
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

int fail(lua_State* L, Error error)
{
    lua_pushnil(L);
    push(L, errors[static_cast<unsigned>(error)]);
    return 2;
}

template<class T>
void userdata(lua_State* L, const char* metatable, T value)
{
    auto* storage = static_cast<T*>(lua_newuserdata(L, sizeof(T)));
    luaL_getmetatable(L, metatable);
    lua_setmetatable(L, -2);
    std::construct_at(storage, std::move(value));
}

template<class T>
int finalize(lua_State* L)
{
    std::destroy_at(static_cast<T*>(lua_touserdata(L, 1)));
    return 0;
}

template<class T>
const T* current(lua_State* L, int index, const char* type)
{
    const auto& view = *static_cast<View<T>*>(luaL_checkudata(L, index, type));
    return view.stamp.current() ? view.pointer : nullptr;
}

void addContact(lua_State* L, const Contact& contact)
{
    constexpr std::array phases{"down"sv, "move"sv, "up"sv, "cancel"sv};
    field(L, "pad", contact.pad);
    field(L, "finger", contact.finger);
    field(L, "phase", phases[static_cast<unsigned>(contact.phase)]);
    field(L, "x", contact.x);
    field(L, "y", contact.y);
    field(L, "pressure", contact.pressure);
}

void addMotion(lua_State* L, const Motion& motion)
{
    field(L, "sensor", sensors[static_cast<unsigned>(motion.sensor)]);
    list(L, std::span<const float>(motion.xyz));
    lua_setfield(L, -2, "xyz");
}

void addPower(lua_State* L, const Power& power)
{
    constexpr std::array states{"unknown"sv, "onBattery"sv, "charging"sv, "charged"sv, "external"sv};
    field(L, "state", states[static_cast<unsigned>(power.state)]);
    field(L, "percent", power.percent);
    field(L, "level", power.level);
}

void event(lua_State* L, const GamepadEvent& e, std::uint64_t cutoff, std::size_t sequence)
{
    lua_createtable(L, 0, 10);
    field(L, "device", e.device);
    field(L, "order", sequence);
    field(L, "reason", reasons[static_cast<unsigned>(e.reason)]);
    constexpr std::array qualities{"receiveOnly"sv, "convertedOS"sv, "calibratedDevice"sv};
    field(L, "timeQuality", qualities[static_cast<unsigned>(e.timeQuality)]);
    const auto delta = e.receivedNs >= cutoff ? static_cast<double>(e.receivedNs - cutoff)
                                              : -static_cast<double>(cutoff - e.receivedNs);
    field(L, "offsetUs", delta / 1000.0);
    std::visit([&](const auto& payload) {
        using T = std::decay_t<decltype(payload)>;
        if constexpr (std::is_same_v<T, DeviceChange>)
        {
            field(L, "kind", changes[static_cast<unsigned>(payload.kind)]);
            field(L, "revision", payload.revision);
        }
        else if constexpr (std::is_same_v<T, ButtonEdge>)
        {
            field(L, "kind", "button");
            field(L, "button", buttons[static_cast<unsigned>(payload.button)]);
            field(L, "down", payload.down);
        }
        else if constexpr (std::is_same_v<T, AxisChange>)
        {
            field(L, "kind", "axis");
            field(L, "axis", axes[static_cast<unsigned>(payload.axis)]);
            field(L, "value", payload.value);
        }
        else if constexpr (std::is_same_v<T, RawChange>)
        {
            constexpr std::array kinds{"button"sv, "axis"sv, "hat"sv};
            field(L, "kind", "raw");
            field(L, "control", kinds[static_cast<unsigned>(payload.kind)]);
            field(L, "index", payload.index);
            field(L, "value", payload.value);
        }
        else if constexpr (std::is_same_v<T, Contact>)
        {
            field(L, "kind", "contact");
            addContact(L, payload);
        }
        else if constexpr (std::is_same_v<T, Motion>)
        {
            field(L, "kind", "motion");
            addMotion(L, payload);
        }
        else if constexpr (std::is_same_v<T, Power>)
        {
            field(L, "kind", "power");
            addPower(L, payload);
        }
        else if constexpr (std::is_same_v<T, InputGap>)
        {
            constexpr std::array causes{"queueOverflow"sv, "driverOverflow"sv, "sensorOverflow"sv, "clockReset"sv};
            field(L, "kind", "inputGap");
            field(L, "cause", causes[static_cast<unsigned>(payload.cause)]);
            field(L, "lostCount", payload.lostCount);
        }
        else if constexpr (std::is_same_v<T, OutputDone>)
        {
            constexpr std::array statuses{"applied"sv, "superseded"sv, "cancelled"sv, "failed"sv};
            field(L, "kind", "outputDone");
            field(L, "command", payload.command);
            field(L, "status", statuses[static_cast<unsigned>(payload.status)]);
            field(L, "error", errors[static_cast<unsigned>(payload.error)]);
        }
    }, e.payload);
}

int frame(lua_State* L)
{
    const auto& f = pads().frame();
    userdata(L, frameType, View<GamepadFrame>{f.stamp(), &f});
    return 1;
}

template<auto Getter>
int frameValue(lua_State* L)
{
    const auto* f = current<GamepadFrame>(L, 1, frameType);
    if (!f)
        return fail(L, Error::StaleFrame);
    push(L, (f->*Getter)());
    return 1;
}

int devices(lua_State* L)
{
    const auto* f = current<GamepadFrame>(L, 1, frameType);
    if (!f)
        return fail(L, Error::StaleFrame);
    list(L, f->devices());
    return 1;
}

int find(lua_State* L)
{
    const auto* f = current<GamepadFrame>(L, 1, frameType);
    if (!f)
        return fail(L, Error::StaleFrame);
    const auto id = number<std::uint32_t>(L, 2);
    if (!id)
        return fail(L, Error::InvalidArgument);
    if (const auto* pad = f->find(static_cast<DeviceId>(*id)))
        userdata(L, padType, View<PadView>{f->stamp(), pad});
    else
        lua_pushnil(L);
    return 1;
}

int nextEvent(lua_State* L)
{
    const auto* f = current<GamepadFrame>(L, lua_upvalueindex(1), frameType);
    if (!f)
        return fail(L, Error::StaleFrame);
    const auto index = number<std::uint32_t>(L, lua_upvalueindex(2));
    if (!index || *index >= f->events().size())
        return 0;
    push(L, *index + 1);
    lua_replace(L, lua_upvalueindex(2));
    event(L, f->events()[*index], f->cutoffNs(), *index + 1);
    return 1;
}

int events(lua_State* L)
{
    if (!current<GamepadFrame>(L, 1, frameType))
        return fail(L, Error::StaleFrame);
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, nextEvent, 2);
    return 1;
}

template<auto Getter>
int padValue(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    push(L, (p->*Getter)());
    return 1;
}

template<class E, const auto& Names, auto Getter>
int padControl(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    const auto key = lookup<E>(string(L, 2), Names);
    if (!key)
        return fail(L, Error::InvalidArgument);
    push(L, (p->*Getter)(*key));
    return 1;
}

int info(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    const auto& i = p->info();
    lua_createtable(L, 0, 10);
    field(L, "id", i.id);
    field(L, "name", i.name);
    field(L, "mappingGuid", i.mappingGuid);
    field(L, "layout", i.layout);
    field(L, "mappingName", i.mappingName);
    field(L, "vendor", i.vendor);
    field(L, "product", i.product);
    field(L, "version", i.version);
    field(L, "serial", i.serial);
    return 1;
}

int raw(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    const auto value = p->raw();
    lua_createtable(L, 0, 3);
    list(L, value.buttons);
    lua_setfield(L, -2, "buttons");
    list(L, value.axes);
    lua_setfield(L, -2, "axes");
    list(L, value.hats);
    lua_setfield(L, -2, "hats");
    return 1;
}

int has(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    const auto key = string(L, 2);
    const auto& caps = p->caps();
    if (const auto button = lookup<Button>(key, buttons)) push(L, caps.has(*button));
    else if (const auto axis = lookup<Axis>(key, axes)) push(L, caps.has(*axis));
    else if (const auto sensor = lookup<Sensor>(key, sensors)) push(L, caps.has(*sensor));
    else if (const auto feature = lookup<Feature>(key, features)) push(L, caps.has(*feature));
    else return fail(L, Error::InvalidArgument);
    return 1;
}

int contacts(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    lua_createtable(L, static_cast<int>(p->contacts().size()), 0);
    int index = 1;
    for (const auto& contact : p->contacts())
    {
        lua_createtable(L, 0, 6);
        addContact(L, contact);
        lua_rawseti(L, -2, index++);
    }
    return 1;
}

int latest(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    const auto sensor = lookup<Sensor>(string(L, 2), sensors);
    if (!sensor)
        return fail(L, Error::InvalidArgument);
    if (const auto motion = p->latest(*sensor))
    {
        lua_createtable(L, 0, 2);
        addMotion(L, *motion);
    }
    else
        lua_pushnil(L);
    return 1;
}

int power(lua_State* L)
{
    const auto* p = current<PadView>(L, 1, padType);
    if (!p)
        return fail(L, Error::StaleFrame);
    lua_createtable(L, 0, 3);
    addPower(L, p->power());
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

std::optional<MappingSource> source(lua_State* L)
{
    if (lua_isnoneornil(L, 2))
        return MappingSource::Application;
    return lookup<MappingSource>(string(L, 2), sources);
}

int addMapping(lua_State* L)
{
    const auto from = source(L);
    if (!from || lua_type(L, 1) != LUA_TSTRING)
        return fail(L, Error::InvalidArgument);
    const auto result = pads().addGamepadMapping(string(L, 1), *from);
    push(L, result.sdlCode());
    diagnostics(L, result.diagnostics);
    return 2;
}

int importMappings(lua_State* L)
{
    const auto from = source(L);
    if (!from || lua_type(L, 1) != LUA_TSTRING)
        return fail(L, Error::InvalidArgument);
    const auto result = pads().importMappings(string(L, 1), *from);
    lua_createtable(L, 0, 7);
    field(L, "added", result.added);
    field(L, "replaced", result.replaced);
    field(L, "unchanged", result.unchanged);
    field(L, "skipped", result.skipped);
    field(L, "failed", result.failed);
    field(L, "batchError", errors[static_cast<unsigned>(result.batchError)]);
    diagnostics(L, result.diagnostics);
    lua_setfield(L, -2, "diagnostics");
    return 1;
}

int setLocal(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    if (!id || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING)
        return fail(L, Error::InvalidArgument);
    const auto result = pads().setLocalBindings(static_cast<DeviceId>(*id), string(L, 2), string(L, 3));
    push(L, result.sdlCode());
    diagnostics(L, result.diagnostics);
    return 2;
}

int mappingFor(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    if (!id)
        return fail(L, Error::InvalidArgument);
    const auto result = pads().mappingFor(static_cast<DeviceId>(*id));
    if (!result)
        return fail(L, result.error);
    push(L, *result.value);
    return 1;
}

int assignPlayer(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    const auto player = number<unsigned>(L, 2);
    if (!id || (!player && !lua_isnoneornil(L, 2)))
        return fail(L, Error::InvalidArgument);
    const auto result = pads().assignPlayer(static_cast<DeviceId>(*id), player);
    if (result != Error::None)
        return fail(L, result);
    push(L, true);
    return 1;
}

int close(lua_State* L)
{
    static_cast<Subscription*>(luaL_checkudata(L, 1, leaseType))->close();
    return 0;
}

int lease(lua_State* L, Result<Subscription> result)
{
    if (!result)
        return fail(L, result.error);
    userdata(L, leaseType, std::move(*result.value));
    return 1;
}

int watchRaw(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    return id ? lease(L, pads().watchRaw(static_cast<DeviceId>(*id))) : fail(L, Error::InvalidArgument);
}

int subscribeSensor(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    const auto sensor = lookup<Sensor>(string(L, 2), sensors);
    const auto depth = number<unsigned>(L, 3);
    if (!id || !sensor || !depth)
        return fail(L, Error::InvalidArgument);
    return lease(L, pads().subscribeSensor(static_cast<DeviceId>(*id), *sensor, *depth));
}

int createHapticPlayback(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    tolua_Error typeError{};
    if (!id || !tolua_isusertype(L, 2, "cc.AudioSource", 0, &typeError))
        return fail(L, Error::InvalidArgument);
    auto* source = static_cast<cc::AudioSource*>(tolua_tousertype(L, 2, nullptr));
    if (!source)
        return fail(L, Error::InvalidArgument);
    userdata(L, hapticType, HapticHandle{});
    auto result = pads().createHapticPlayback(static_cast<DeviceId>(*id), *source);
    if (!result)
        return fail(L, result.error);
    *static_cast<HapticHandle*>(lua_touserdata(L, -1)) = std::move(result.value);
    return 1;
}

HapticPlayback& haptic(lua_State* L)
{
    return **static_cast<HapticHandle*>(luaL_checkudata(L, 1, hapticType));
}

int hapticResult(lua_State* L, Error error)
{
    if (error != Error::None)
        return fail(L, error);
    lua_pushboolean(L, 1);
    return 1;
}

template<auto Method>
int controlHaptics(lua_State* L)
{
    return hapticResult(L, (haptic(L).*Method)());
}

int closeHaptics(lua_State* L)
{
    haptic(L).close();
    return hapticResult(L, Error::None);
}

int seekHaptics(lua_State* L)
{
    const auto seconds = number<double>(L, 2);
    return seconds ? hapticResult(L, haptic(L).seekTime(*seconds)) : fail(L, Error::InvalidArgument);
}

int loopHaptics(lua_State* L)
{
    if (!lua_isboolean(L, 2))
        return fail(L, Error::InvalidArgument);
    return hapticResult(L, haptic(L).setLooping(lua_toboolean(L, 2) != 0));
}

int setHapticIntensity(lua_State* L)
{
    const auto intensity = number<float>(L, 2);
    return intensity ? hapticResult(L, haptic(L).setIntensity(*intensity)) : fail(L, Error::InvalidArgument);
}

int hapticsSnapshot(lua_State* L)
{
    const auto snapshot = haptic(L).snapshot();
    lua_createtable(L, 0, 8);
    field(L, "state", playbackStates[static_cast<unsigned>(snapshot.state)]);
    field(L, "error", errors[static_cast<unsigned>(snapshot.error)]);
    field(L, "positionSeconds", snapshot.positionSeconds);
    field(L, "durationSeconds", snapshot.durationSeconds);
    field(L, "intensity", snapshot.intensity);
    field(L, "looping", snapshot.looping);
    field(L, "seekable", snapshot.seekable);
    field(L, "stopReason", stopReasons[static_cast<unsigned>(snapshot.stopReason)]);
    return 1;
}

template<class T>
std::optional<T> parameter(lua_State* L, const char* name)
{
    lua_pushstring(L, name);
    lua_rawget(L, 2);
    const auto value = number<T>(L, -1);
    lua_pop(L, 1);
    return value;
}

std::string_view parameter(lua_State* L, const char* name)
{
    lua_pushstring(L, name);
    lua_rawget(L, 2);
    const auto value = string(L, -1);
    lua_pop(L, 1);
    return value;
}

std::optional<OutputCommand> command(lua_State* L)
{
    const auto kind = parameter(L, "kind");
    if (kind == "rumble" || kind == "triggerRumble")
    {
        const auto duration = parameter<unsigned>(L, "durationMs");
        const auto low = parameter<float>(L, kind == "rumble" ? "low" : "left");
        const auto high = parameter<float>(L, kind == "rumble" ? "high" : "right");
        if (duration && low && high)
        {
            const auto time = std::chrono::milliseconds(*duration);
            if (kind == "rumble")
                return Rumble{*low, *high, time};
            return TriggerRumble{*low, *high, time};
        }
    }
    else if (kind == "rgb")
    {
        const auto red = parameter<std::uint8_t>(L, "r");
        const auto green = parameter<std::uint8_t>(L, "g");
        const auto blue = parameter<std::uint8_t>(L, "b");
        if (red && green && blue)
            return Rgb{*red, *green, *blue};
    }
    else if (kind == "playerLights")
    {
        if (const auto mask = parameter<std::uint32_t>(L, "mask"))
            return PlayerLights{*mask};
    }
    else if (kind == "adaptiveTrigger")
    {
        const auto side = lookup<Side>(parameter(L, "side"), sides);
        const auto mode = lookup<TriggerMode>(parameter(L, "mode"), modes);
        if (side && mode && *mode == TriggerMode::Off)
            return AdaptiveTrigger{*side, *mode};
        const auto start = parameter<float>(L, "start");
        const auto strength = parameter<float>(L, "strength");
        const auto hz = parameter<float>(L, "hz");
        if (side && mode && start && strength && (*mode != TriggerMode::Vibration || hz))
            return AdaptiveTrigger{*side, *mode, *start, *strength, hz.value_or(0)};
    }
    else if (kind == "stop")
    {
        lua_pushliteral(L, "channel");
        lua_rawget(L, 2);
        const auto channel = lua_isnil(L, -1) ? Channel::All : lookup<Channel>(string(L, -1), channels);
        lua_pop(L, 1);
        if (channel)
            return Stop{*channel};
    }
    return {};
}

int submit(lua_State* L)
{
    const auto id = number<std::uint32_t>(L, 1);
    if (!id || !lua_istable(L, 2))
        return fail(L, Error::InvalidArgument);
    const auto output = command(L);
    if (!output)
        return fail(L, Error::InvalidArgument);
    const auto result = pads().submit(static_cast<DeviceId>(*id), *output);
    if (!result)
        return fail(L, result.error);
    push(L, *result.value);
    return 1;
}

void metatable(lua_State* L, const char* name, lua_CFunction gc, const luaL_Reg* methods)
{
    luaL_newmetatable(L, name);
    lua_pushcfunction(L, gc);
    lua_setfield(L, -2, "__gc");
    lua_pushstring(L, name);
    lua_setfield(L, -2, "__metatable");
    lua_newtable(L);
    luaL_register(L, nullptr, methods);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);
}
}

int register_cc_gamepad(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.gamepad.registered");
    const bool registered = lua_toboolean(L, -1);
    lua_pop(L, 1);
    if (registered)
        return 0;

    const luaL_Reg frameMethods[]{
        {"tick", frameValue<&GamepadFrame::tick>}, {"devices", devices}, {"find", find}, {"events", events}, {}
    };
    const luaL_Reg padMethods[]{
        {"info", info}, {"mapped", padValue<&PadView::mapped>}, {"inputLayout", padValue<&PadView::inputLayout>},
        {"mappingStatus", padValue<&PadView::mappingStatus>}, {"mappingRevision", padValue<&PadView::mappingRevision>},
        {"player", padValue<&PadView::player>}, {"has", has}, {"raw", raw}, {"contacts", contacts},
        {"latest", latest}, {"power", power},
        {"down", padControl<Button, buttons, &PadView::down>}, {"pressed", padControl<Button, buttons, &PadView::pressed>},
        {"released", padControl<Button, buttons, &PadView::released>}, {"label", padControl<Button, buttons, &PadView::label>},
        {"axis", padControl<Axis, axes, &PadView::axis>}, {"axisValue", padControl<Axis, axes, &PadView::axisValue>}, {}
    };
    const luaL_Reg leaseMethods[]{{"close", close}, {}};
    const luaL_Reg hapticMethods[]{
        {"play", controlHaptics<&HapticPlayback::play>}, {"pause", controlHaptics<&HapticPlayback::pause>},
        {"resume", controlHaptics<&HapticPlayback::resume>}, {"stop", controlHaptics<&HapticPlayback::stop>},
        {"seekTime", seekHaptics}, {"setLooping", loopHaptics}, {"setIntensity", setHapticIntensity},
        {"snapshot", hapticsSnapshot}, {"close", closeHaptics}, {}
    };
    const luaL_Reg functions[]{
        {"frame", frame}, {"addGamepadMapping", addMapping}, {"importMappings", importMappings},
        {"setLocalBindings", setLocal}, {"mappingFor", mappingFor}, {"assignPlayer", assignPlayer},
        {"watchRaw", watchRaw}, {"subscribeSensor", subscribeSensor}, {"createHapticPlayback", createHapticPlayback},
        {"submit", submit}, {}
    };
    metatable(L, frameType, finalize<View<GamepadFrame>>, frameMethods);
    metatable(L, padType, finalize<View<PadView>>, padMethods);
    metatable(L, leaseType, finalize<Subscription>, leaseMethods);
    metatable(L, hapticType, finalize<HapticHandle>, hapticMethods);
    luaL_register(L, "cc.gamepad", functions);
    lua_pop(L, 1);
    lua_pushboolean(L, 1);
    lua_setfield(L, LUA_REGISTRYINDEX, "cc.gamepad.registered");
    return 0;
}
