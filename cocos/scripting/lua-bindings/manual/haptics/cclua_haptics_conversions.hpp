#pragma once
#include "haptics/HapticService.h"
#include "lua_conversion/lua_conversion.hpp"
#include "lua_conversion/detail/record.hpp"
#include <array>
#include <tuple>

namespace lua::haptic_detail {
namespace h = cc::haptics;
template<class T> struct Identity { T id; };

// Generated wrappers use these guards before the shared LuaJIT scalar conversions.
inline bool numberArgument(lua_State* L, int index)
{
    return lua_type(L, index) == LUA_TNUMBER && std::isfinite(lua_tonumber(L, index));
}
inline bool deviceArgument(lua_State* L, int index)
{
    if (!numberArgument(L, index)) return false;
    const auto id = lua_tonumber(L, index);
    return id >= 0 && id <= UINT32_MAX && id == std::floor(id);
}
inline bool stringArgument(lua_State* L, int index) { return lua_type(L, index) == LUA_TSTRING; }
inline bool booleanArgument(lua_State* L, int index) { return lua_type(L, index) == LUA_TBOOLEAN; }

template<class E> struct Names;
template<> struct Names<h::Track> {
    using E = h::Track;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Normal, "normal"},
        {E::Burst, "burst"}
    };
};
template<> struct Names<h::StartPolicy> {
    using E = h::StartPolicy;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Auto, "auto"},
        {E::FixedTimeline, "fixedTimeline"}
    };
};
template<> struct Names<h::AcquirePolicy> {
    using E = h::AcquirePolicy;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::IfIdle, "ifIdle"},
        {E::InterruptPreset, "interruptPreset"}
    };
};
template<> struct Names<h::AssetFormat> {
    using E = h::AssetFormat;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Auto, "auto"},
        {E::MetaHaptic, "metaHaptic"},
        {E::AppleAhap, "appleAhap"}
    };
};
template<> struct Names<h::ImportPolicy> {
    using E = h::ImportPolicy;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Compatible, "compatible"},
        {E::Strict, "strict"}
    };
};
template<> struct Names<h::AppleControl> {
    using E = h::AppleControl;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Intensity, "intensity"},
        {E::Sharpness, "sharpness"}
    };
};
template<> struct Names<h::AndroidEffect> {
    using E = h::AndroidEffect;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Click, "click"},
        {E::DoubleClick, "doubleClick"},
        {E::Tick, "tick"},
        {E::HeavyClick, "heavyClick"}
    };
};
template<> struct Names<h::Owner> {
    using E = h::Owner;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Idle, "idle"},
        {E::Preset, "preset"},
        {E::LegacyRumble, "legacyRumble"},
        {E::LegacyPcm, "legacyPcm"},
        {E::Raw, "raw"}
    };
};
template<> struct Names<h::Availability> {
    using E = h::Availability;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Available, "available"},
        {E::Stopping, "stopping"},
        {E::RouteFault, "routeFault"},
        {E::NotFocused, "notFocused"},
        {E::Disabled, "disabled"}
    };
};
template<> struct Names<h::Error> {
    using E = h::Error;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::InvalidAsset, "invalidAsset"},
        {E::Unsupported, "unsupported"},
        {E::InvalidArgument, "invalidArgument"},
        {E::IoError, "ioError"},
        {E::QueueFull, "queueFull"},
        {E::Busy, "busy"},
        {E::NotFocused, "notFocused"},
        {E::StaleTarget, "staleTarget"},
        {E::Unavailable, "unavailable"},
        {E::NotFound, "notFound"},
        {E::RecordGone, "recordGone"},
        {E::TimedOut, "timedOut"},
        {E::BackendFailure, "backendFailure"},
        {E::Cancelled, "cancelled"},
        {E::PermissionDenied, "permissionDenied"},
        {E::Disabled, "disabled"}
    };
};
template<> struct Names<h::PlaybackState> {
    using E = h::PlaybackState;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Scheduled, "scheduled"},
        {E::Active, "active"},
        {E::Completed, "completed"},
        {E::Stopped, "stopped"},
        {E::Preempted, "preempted"},
        {E::Dropped, "dropped"},
        {E::Coalesced, "coalesced"},
        {E::Failed, "failed"}
    };
};
template<> struct Names<h::StopReason> {
    using E = h::StopReason;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::None, "none"},
        {E::Requested, "requested"},
        {E::Priority, "priority"},
        {E::FocusLost, "focusLost"},
        {E::EndpointLost, "endpointLost"},
        {E::Replaced, "replaced"},
        {E::IdleExpired, "idleExpired"},
        {E::Disabled, "disabled"},
        {E::Reconfigured, "reconfigured"}
    };
};
template<> struct Names<h::MobilePlatform> {
    using E = h::MobilePlatform;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::None, "none"},
        {E::Android, "android"},
        {E::Apple, "apple"}
    };
};
template<> struct Names<h::OperationState> {
    using E = h::OperationState;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Pending, "pending"},
        {E::Succeeded, "succeeded"},
        {E::Failed, "failed"},
        {E::Cancelled, "cancelled"}
    };
};
template<> struct Names<h::RawState> {
    using E = h::RawState;
    static constexpr std::pair<E, std::string_view> values[]{
        {E::Pending, "pending"},
        {E::Ready, "ready"},
        {E::Closed, "closed"},
        {E::Failed, "failed"}
    };
};
template<class E> bool readEnum(lua_State* L, int i, E& result)
{
    const int type = lua_type(L, i);
    if (type != LUA_TSTRING && type != LUA_TNUMBER) return false;
    size_t len = 0;
    const char* string = type == LUA_TSTRING ? lua_tolstring(L, i, &len) : nullptr;
    for (auto [value, name] : Names<E>::values) {
        if (string ? name == std::string_view(string, len) : lua_tonumber(L,i) == static_cast<int>(value)) {
            result = value;
            return true;
        }
    }
    return false;
}

template<class E> struct EnumOutput {
    static void F(lua_State* L, E value) {
        for (auto [v, name] : Names<E>::values)
            if (v == value) { lua_pushlstring(L, name.data(), name.size()); return; }
        lua_pushnil(L);
    }
};

template<class T> struct Fields;
template<class T, class V> struct Member { const char* name; V T::*pointer; };
template<class T, class V> constexpr auto field(const char* name, V T::*pointer) { return Member<T,V>{name, pointer}; }
template<> struct Fields<h::ImportOptions> {
    using T = h::ImportOptions;
    static constexpr auto members = std::tuple{
        field("format", &T::format),
        field("policy", &T::policy)
    };
};
template<> struct Fields<h::PlayOptions> {
    using T = h::PlayOptions;
    static constexpr auto members = std::tuple{
        field("track", &T::track),
        field("priority", &T::priority),
        field("gain", &T::gain),
        field("pan", &T::pan),
        field("startAfterMs", &T::startAfterMs),
        field("startAt", &T::startAt),
        field("startPolicy", &T::startPolicy),
        field("iterations", &T::iterations),
        field("requireAmplitude", &T::requireAmplitude),
        field("requireNativeScheduled", &T::requireNativeScheduled),
        field("mergeKey", &T::mergeKey)
    };
};
template<> struct Fields<h::PcmModeTiming> {
    using T = h::PcmModeTiming;
    static constexpr auto members = std::tuple{
        field("enterMs", &T::enterMs),
        field("exitMs", &T::exitMs)
    };
};
template<> struct Fields<h::OutputSettings> {
    using T = h::OutputSettings;
    static constexpr auto members = std::tuple{
        field("enabled", &T::enabled),
        field("strength", &T::strength)
    };
};
template<> struct Fields<h::HapticCalibration> {
    using T = h::HapticCalibration;
    static constexpr auto members = std::tuple{
        field("version", &T::version),
        field("gain", &T::gain),
        field("continuousGain", &T::continuousGain),
        field("transientGain", &T::transientGain),
        field("gamma", &T::gamma),
        field("leftGain", &T::leftGain),
        field("rightGain", &T::rightGain),
        field("monoGain", &T::monoGain),
        field("textureBias", &T::textureBias),
        field("textureScale", &T::textureScale),
        field("peakCap", &T::peakCap),
        field("energyCap", &T::energyCap)
    };
};
template<> struct Fields<h::AndroidOneShot> {
    using T = h::AndroidOneShot;
    static constexpr auto members = std::tuple{
        field("durationMs", &T::durationMs),
        field("amplitude", &T::amplitude)
    };
};
template<> struct Fields<h::AndroidStep> {
    using T = h::AndroidStep;
    static constexpr auto members = std::tuple{
        field("durationMs", &T::durationMs),
        field("amplitude", &T::amplitude)
    };
};
template<> struct Fields<h::AndroidWaveform> {
    using T = h::AndroidWaveform;
    static constexpr auto members = std::tuple{
        field("steps", &T::steps)
    };
};
template<> struct Fields<h::AndroidPrimitive> {
    using T = h::AndroidPrimitive;
    static constexpr auto members = std::tuple{
        field("id", &T::id),
        field("scale", &T::scale),
        field("delayMs", &T::delayMs)
    };
};
template<> struct Fields<h::AndroidComposition> {
    using T = h::AndroidComposition;
    static constexpr auto members = std::tuple{
        field("steps", &T::steps)
    };
};
template<> struct Fields<h::AndroidControlPoint> {
    using T = h::AndroidControlPoint;
    static constexpr auto members = std::tuple{
        field("durationMs", &T::durationMs),
        field("amplitude", &T::amplitude),
        field("texture", &T::texture)
    };
};
template<> struct Fields<h::AndroidEnvelope> {
    using T = h::AndroidEnvelope;
    static constexpr auto members = std::tuple{
        field("frequency", &T::frequency),
        field("points", &T::points)
    };
};
template<> struct Fields<h::AppleEvent> {
    using T = h::AppleEvent;
    static constexpr auto members = std::tuple{
        field("time", &T::time),
        field("duration", &T::duration),
        field("intensity", &T::intensity),
        field("sharpness", &T::sharpness)
    };
};
template<> struct Fields<h::AppleParameter> {
    using T = h::AppleParameter;
    static constexpr auto members = std::tuple{
        field("control", &T::control),
        field("time", &T::time),
        field("value", &T::value)
    };
};
template<> struct Fields<h::AppleParameters> {
    using T = h::AppleParameters;
    static constexpr auto members = std::tuple{
        field("parameters", &T::parameters)
    };
};
template<> struct Fields<h::AppleCurvePoint> {
    using T = h::AppleCurvePoint;
    static constexpr auto members = std::tuple{
        field("time", &T::time),
        field("value", &T::value)
    };
};
template<> struct Fields<h::AppleParameterCurve> {
    using T = h::AppleParameterCurve;
    static constexpr auto members = std::tuple{
        field("control", &T::control),
        field("time", &T::time),
        field("points", &T::points)
    };
};
template<> struct Fields<h::ApplePattern> {
    using T = h::ApplePattern;
    static constexpr auto members = std::tuple{
        field("events", &T::events),
        field("parameters", &T::parameters),
        field("curves", &T::curves)
    };
};

template<class T> bool read(lua_State* L, int i, T& out);
template<class T> bool read(lua_State* L, int i, std::optional<T>& out)
{
    T item{};
    if (!read(L, i, item)) return false;
    out = std::move(item);
    return true;
}
template<class T> bool read(lua_State* L, int i, std::vector<T>& out)
{
    if (!lua_istable(L,i)) return false;
    i = _absolute_index(L,i);
    const size_t count = lua_objlen(L,i);
    if (count > 128) return false;
    // Reject holes, out-of-range keys and metadata even when Lua's length stops early.
    size_t seen = 0;
    lua_pushnil(L);
    while (lua_next(L,i)) {
        const double key = lua_tonumber(L,-2);
        const bool inRange = lua_type(L,-2) == LUA_TNUMBER && key >= 1 && key <= count && key == std::floor(key);
        lua_pop(L,1);
        if (!inRange) { lua_pop(L,1); return false; }
        ++seen;
    }
    if (seen != count) return false;
    out.resize(count);
    for (size_t n = 0; n < count; ++n) {
        lua_rawgeti(L,i,static_cast<int>(n + 1));
        bool ok = read(L,-1,out[n]);
        lua_pop(L,1);
        if (!ok) return false;
    }
    return true;
}
template<class T> bool read(lua_State* L, int i, T& out)
{
    if constexpr (std::is_same_v<T,bool>) {
        if (!lua_isboolean(L,i)) return false;
        out = lua_toboolean(L,i) != 0;
    } else if constexpr (std::is_arithmetic_v<T>) {
        if (lua_type(L,i) != LUA_TNUMBER) return false;
        double n = lua_tonumber(L,i);
        if (!std::isfinite(n) || n < std::numeric_limits<T>::lowest() || n > std::numeric_limits<T>::max()) return false;
        if constexpr (std::is_integral_v<T>) if (n != std::floor(n)) return false;
        out = static_cast<T>(n);
    } else if constexpr (std::is_same_v<T,std::string>) {
        if (lua_type(L,i) != LUA_TSTRING) return false;
        size_t n;
        auto* s = lua_tolstring(L,i,&n);
        out.assign(s,n);
    } else if constexpr (std::is_enum_v<T>) {
        return readEnum(L,i,out);
    } else if constexpr (requires { Fields<T>::members; }) {
        i = _absolute_index(L,i);
        T result{};
        auto decode = [&](auto member) {
            lua_pushstring(L,member.name);
            lua_rawget(L,i);
            bool ok = lua_isnil(L,-1) || read(L,-1,result.*member.pointer);
            lua_pop(L,1);
            return ok;
        };
        bool ok = std::apply([&](auto... m) {
            return record_detail::fields(L,i,{m.name...}) && (decode(m) && ...);
        },Fields<T>::members);
        if (!ok) return false;
        out = std::move(result);
    } else {
        return lua_type(L,i) == LUA_TUSERDATA && luaval_to_native(L,i,&out);
    }
    return true;
}
template<class T> struct Input {
    static bool F(lua_State* L, int i, T* out, const char* = "") { return out && read(L,i,*out); }
};
template<class T> struct StrictArgument {
    template<bool> static bool F(lua_State* L,int i,T* out) { return to_native<T>::F(L,i,out); }
};
template<class T> struct IdOutput {
    static void F(lua_State* L,T id) { native_to_luaval(L,Identity<T>{id}); }
};
template<class T> struct IdInput {
    static bool F(lua_State* L,int i,T* out,const char* = "") {
        const Identity<T>* p = nullptr;
        if (!out || lua_type(L,i) != LUA_TUSERDATA || !read_value_pointer(L,i,&p)) return false;
        *out = p->id;
        return true;
    }
};
} // namespace lua::haptic_detail

namespace lua {
template<> struct value_type<cc::haptics::HapticClip> : std::true_type {};
template<> struct value_type<cc::haptics::HapticService> : std::true_type {};
template<> struct value_type<cc::haptics::HapticScope> : std::true_type {};
template<> struct value_type<cc::haptics::RawSession> : std::true_type {};
template<> struct value_type<cc::haptics::HapticTime> : std::true_type {};
template<> struct value_type<cc::haptics::PlaybackId> : std::true_type {};
template<> struct value_type<cc::haptics::OperationId> : std::true_type {};
template<> struct value_type<haptic_detail::Identity<cc::haptics::TargetId>> : std::true_type {};
template<> struct to_native<cc::haptics::TargetId> : haptic_detail::IdInput<cc::haptics::TargetId> {};
template<> struct to_lua<cc::haptics::TargetId> : haptic_detail::IdOutput<cc::haptics::TargetId> {};
template<> struct binding_read<cc::haptics::TargetId> : haptic_detail::StrictArgument<cc::haptics::TargetId> {};
template<> struct value_type<haptic_detail::Identity<cc::haptics::RawPlayerId>> : std::true_type {};
template<> struct to_native<cc::haptics::RawPlayerId> : haptic_detail::IdInput<cc::haptics::RawPlayerId> {};
template<> struct to_lua<cc::haptics::RawPlayerId> : haptic_detail::IdOutput<cc::haptics::RawPlayerId> {};
template<> struct binding_read<cc::haptics::RawPlayerId> : haptic_detail::StrictArgument<cc::haptics::RawPlayerId> {};
template<> struct to_lua<borrowed_value<cc::haptics::HapticService>> {
    static void F(lua_State* L, borrowed_value<cc::haptics::HapticService> service);
};
template<> struct value_userdata_lifetime<cc::haptics::HapticService> {
    static constexpr bool guarded = true;
    static bool valid(lua_State* L, int index);
};
template<> struct to_native<cc::haptics::ImportOptions> : haptic_detail::Input<cc::haptics::ImportOptions> {};
template<> struct to_native<cc::haptics::PlayOptions> : haptic_detail::Input<cc::haptics::PlayOptions> {};
template<> struct to_native<cc::haptics::PcmModeTiming> : haptic_detail::Input<cc::haptics::PcmModeTiming> {};
template<> struct to_native<cc::haptics::OutputSettings> : haptic_detail::Input<cc::haptics::OutputSettings> {};
template<> struct to_native<cc::haptics::HapticCalibration> : haptic_detail::Input<cc::haptics::HapticCalibration> {};
template<> struct to_native<cc::haptics::AndroidOneShot> : haptic_detail::Input<cc::haptics::AndroidOneShot> {};
template<> struct to_native<cc::haptics::AndroidStep> : haptic_detail::Input<cc::haptics::AndroidStep> {};
template<> struct to_native<cc::haptics::AndroidWaveform> : haptic_detail::Input<cc::haptics::AndroidWaveform> {};
template<> struct to_native<cc::haptics::AndroidPrimitive> : haptic_detail::Input<cc::haptics::AndroidPrimitive> {};
template<> struct to_native<cc::haptics::AndroidComposition> : haptic_detail::Input<cc::haptics::AndroidComposition> {};
template<> struct to_native<cc::haptics::AndroidControlPoint> : haptic_detail::Input<cc::haptics::AndroidControlPoint> {};
template<> struct to_native<cc::haptics::AndroidEnvelope> : haptic_detail::Input<cc::haptics::AndroidEnvelope> {};
template<> struct to_native<cc::haptics::AppleEvent> : haptic_detail::Input<cc::haptics::AppleEvent> {};
template<> struct to_native<cc::haptics::AppleParameter> : haptic_detail::Input<cc::haptics::AppleParameter> {};
template<> struct to_native<cc::haptics::AppleParameters> : haptic_detail::Input<cc::haptics::AppleParameters> {};
template<> struct to_native<cc::haptics::AppleCurvePoint> : haptic_detail::Input<cc::haptics::AppleCurvePoint> {};
template<> struct to_native<cc::haptics::AppleParameterCurve> : haptic_detail::Input<cc::haptics::AppleParameterCurve> {};
template<> struct to_native<cc::haptics::ApplePattern> : haptic_detail::Input<cc::haptics::ApplePattern> {};
template<> struct to_native<cc::haptics::AcquirePolicy> : haptic_detail::Input<cc::haptics::AcquirePolicy> {};
template<> struct binding_read<cc::haptics::AcquirePolicy> : haptic_detail::StrictArgument<cc::haptics::AcquirePolicy> {};
template<> struct to_native<cc::haptics::AndroidEffect> : haptic_detail::Input<cc::haptics::AndroidEffect> {};
template<> struct binding_read<cc::haptics::AndroidEffect> : haptic_detail::StrictArgument<cc::haptics::AndroidEffect> {};
template<> struct to_lua<cc::haptics::Error> : haptic_detail::EnumOutput<cc::haptics::Error> {};
template<> struct to_lua<cc::haptics::Owner> : haptic_detail::EnumOutput<cc::haptics::Owner> {};
template<> struct to_lua<cc::haptics::Availability> : haptic_detail::EnumOutput<cc::haptics::Availability> {};
template<> struct to_lua<cc::haptics::PlaybackState> : haptic_detail::EnumOutput<cc::haptics::PlaybackState> {};
template<> struct to_lua<cc::haptics::StopReason> : haptic_detail::EnumOutput<cc::haptics::StopReason> {};
template<> struct to_lua<cc::haptics::MobilePlatform> : haptic_detail::EnumOutput<cc::haptics::MobilePlatform> {};
template<> struct to_lua<cc::haptics::OperationState> : haptic_detail::EnumOutput<cc::haptics::OperationState> {};
template<> struct to_lua<cc::haptics::RawState> : haptic_detail::EnumOutput<cc::haptics::RawState> {};
LUA_TO_LUA_STRUCT(cc::haptics::Diagnostic, path, code, message)
LUA_TO_LUA_STRUCT(cc::haptics::ErrorInfo, code, diagnostics)
LUA_TO_LUA_STRUCT(cc::haptics::ImportResult, clip, diagnostics)
LUA_TO_LUA_STRUCT(cc::haptics::TargetInfo, target, device)
LUA_TO_LUA_STRUCT(cc::haptics::PcmOutputTrace, peakQueuedFrames, generation, lastNonzeroFrame, discardBound, modeWriteUs, firstSubmitUs, discardUs, exitWriteUs, silentUs)
template<> struct to_lua<cc::haptics::Capabilities> {
    static void F(lua_State* L, const cc::haptics::Capabilities& record) {
        lua_createtable(L, 0, 14);
        native_to_luaval_field(L, -1, "owner", record.owner);
        native_to_luaval_field(L, -1, "availability", record.availability);
        native_to_luaval_field(L, -1, "canInterruptPreset", record.canInterruptPreset);
        native_to_luaval_field(L, -1, "platform", record.platform);
        native_to_luaval_field(L, -1, "amplitude", record.amplitude);
        native_to_luaval_field(L, -1, "nativeScheduled", record.nativeScheduled);
        native_to_luaval_field(L, -1, "envelope", record.envelope);
        native_to_luaval_field(L, -1, "canReleaseRaw", record.canReleaseRaw);
        native_to_luaval_field(L, -1, "envelopeStatus", record.envelopeStatus);
        native_to_luaval_field(L, -1, "pcmCandidate", record.pcmCandidate);
        native_to_luaval_field(L, -1, "pcmPrepared", record.pcmPrepared);
        native_to_luaval_field(L, -1, "realtimePcm", record.realtimePcm);
        native_to_luaval_field(L, -1, "pcmTrace", record.pcmTrace);
        native_to_luaval_field(L, -1, "pcmPreparing", record.pcmPreparing);
    }
};
LUA_TO_LUA_STRUCT(cc::haptics::PlaybackSnapshot, state, reason, error, submitted, requestedUs, logicalStartUs, firstSubmitUs, mergedInto, usedRealtimePcm)
LUA_TO_LUA_STRUCT(cc::haptics::OperationSnapshot, state, error, confirmedUs)
LUA_TO_LUA_STRUCT(cc::haptics::RawPlayback, player, operation)
LUA_TO_LUA_STRUCT(cc::haptics::RawSnapshot, state, error, reason)
template<class T> struct to_lua<cc::haptics::Result<T>> {
    static void F(lua_State* L, cc::haptics::Result<T>&& result) {
        if (result.value) native_to_luaval(L,std::move(*result.value));
        else { lua_pushnil(L); native_to_luaval(L,*result.error); }
    }
};
template<> struct to_lua<cc::haptics::Status> {
    static void F(lua_State* L,const cc::haptics::Status& status) {
        if (!status.error) lua_pushboolean(L,1);
        else { lua_pushnil(L); native_to_luaval(L,*status.error); }
    }
};
} // namespace lua
