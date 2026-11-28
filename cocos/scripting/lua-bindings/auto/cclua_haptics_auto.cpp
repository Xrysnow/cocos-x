#include "cclua_haptics_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/haptics/cclua_haptics_conversions.hpp"

static_assert(lua::value_type<cc::haptics::HapticClip>::value, "ValueTypes requires a shared runtime trait for cc::haptics::HapticClip");
static_assert(lua::value_type<cc::haptics::HapticService>::value, "ValueTypes requires a shared runtime trait for cc::haptics::HapticService");
static_assert(lua::value_type<cc::haptics::HapticScope>::value, "ValueTypes requires a shared runtime trait for cc::haptics::HapticScope");
static_assert(lua::value_type<cc::haptics::RawSession>::value, "ValueTypes requires a shared runtime trait for cc::haptics::RawSession");
static_assert(lua::value_type<cc::haptics::HapticTime>::value, "ValueTypes requires a shared runtime trait for cc::haptics::HapticTime");
static_assert(lua::value_type<cc::haptics::PlaybackId>::value, "ValueTypes requires a shared runtime trait for cc::haptics::PlaybackId");
static_assert(lua::value_type<cc::haptics::OperationId>::value, "ValueTypes requires a shared runtime trait for cc::haptics::OperationId");
int luaReg_cc_haptics_cchapticsAssetFormat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("AssetFormat");
	LUA_ENUM_ENTRY("Auto", cc::haptics::AssetFormat::Auto);
	LUA_ENUM_ENTRY("MetaHaptic", cc::haptics::AssetFormat::MetaHaptic);
	LUA_ENUM_ENTRY("AppleAhap", cc::haptics::AssetFormat::AppleAhap);
	LUA_ENUM_ENTRY("RichTapHeV1", cc::haptics::AssetFormat::RichTapHeV1);
	LUA_ENUM_ENTRY("RichTapHeV2", cc::haptics::AssetFormat::RichTapHeV2);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsImportPolicy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("ImportPolicy");
	LUA_ENUM_ENTRY("Compatible", cc::haptics::ImportPolicy::Compatible);
	LUA_ENUM_ENTRY("Strict", cc::haptics::ImportPolicy::Strict);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsError(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("Error");
	LUA_ENUM_ENTRY("InvalidAsset", cc::haptics::Error::InvalidAsset);
	LUA_ENUM_ENTRY("Unsupported", cc::haptics::Error::Unsupported);
	LUA_ENUM_ENTRY("InvalidArgument", cc::haptics::Error::InvalidArgument);
	LUA_ENUM_ENTRY("IoError", cc::haptics::Error::IoError);
	LUA_ENUM_ENTRY("QueueFull", cc::haptics::Error::QueueFull);
	LUA_ENUM_ENTRY("Busy", cc::haptics::Error::Busy);
	LUA_ENUM_ENTRY("NotFocused", cc::haptics::Error::NotFocused);
	LUA_ENUM_ENTRY("StaleTarget", cc::haptics::Error::StaleTarget);
	LUA_ENUM_ENTRY("Unavailable", cc::haptics::Error::Unavailable);
	LUA_ENUM_ENTRY("NotFound", cc::haptics::Error::NotFound);
	LUA_ENUM_ENTRY("RecordGone", cc::haptics::Error::RecordGone);
	LUA_ENUM_ENTRY("TimedOut", cc::haptics::Error::TimedOut);
	LUA_ENUM_ENTRY("BackendFailure", cc::haptics::Error::BackendFailure);
	LUA_ENUM_ENTRY("Cancelled", cc::haptics::Error::Cancelled);
	LUA_ENUM_ENTRY("PermissionDenied", cc::haptics::Error::PermissionDenied);
	LUA_ENUM_ENTRY("Disabled", cc::haptics::Error::Disabled);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_haptics_HapticClip_durationMs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticClip", "cc.haptics.HapticClip:durationMs");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticClip::durationMs);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticClip_format(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticClip", "cc.haptics.HapticClip:format");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticClip::format);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticClip_importPolicy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticClip", "cc.haptics.HapticClip:importPolicy");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticClip::importPolicy);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticClip_load(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.haptics.HapticClip", "cc.haptics.HapticClip:load");
	if (argc == 2 && !ok && !lua::haptic_detail::stringArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(2, &cc::haptics::HapticClip::load);
	}
	if (argc == 1 && !ok && !lua::haptic_detail::stringArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::haptics::HapticClip::load(std::move(arg0));}});
	}
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_haptics_HapticClip_parse(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.haptics.HapticClip", "cc.haptics.HapticClip:parse");
	if (argc == 2 && !ok && !lua::haptic_detail::stringArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(2, &cc::haptics::HapticClip::parse);
	}
	if (argc == 1 && !ok && !lua::haptic_detail::stringArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::haptics::HapticClip::parse(std::move(arg0));}});
	}
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_cc_haptics_cchapticsHapticClip(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::HapticClip, "HapticClip", "cc.haptics.HapticClip",
		nullptr, lua::value_collect<cc::haptics::HapticClip>);
	LUA_METHOD("durationMs", lua_cc_haptics_HapticClip_durationMs);
	LUA_METHOD("format", lua_cc_haptics_HapticClip_format);
	LUA_METHOD("importPolicy", lua_cc_haptics_HapticClip_importPolicy);
	LUA_METHOD("load", lua_cc_haptics_HapticClip_load);
	LUA_METHOD("parse", lua_cc_haptics_HapticClip_parse);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::HapticClip>(lua_S, "cc.haptics.HapticClip");
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsMobilePlatform(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("MobilePlatform");
	LUA_ENUM_ENTRY("None", cc::haptics::MobilePlatform::None);
	LUA_ENUM_ENTRY("Android", cc::haptics::MobilePlatform::Android);
	LUA_ENUM_ENTRY("Apple", cc::haptics::MobilePlatform::Apple);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsAndroidEffect(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("AndroidEffect");
	LUA_ENUM_ENTRY("Click", cc::haptics::AndroidEffect::Click);
	LUA_ENUM_ENTRY("DoubleClick", cc::haptics::AndroidEffect::DoubleClick);
	LUA_ENUM_ENTRY("Tick", cc::haptics::AndroidEffect::Tick);
	LUA_ENUM_ENTRY("HeavyClick", cc::haptics::AndroidEffect::HeavyClick);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsAppleControl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("AppleControl");
	LUA_ENUM_ENTRY("Intensity", cc::haptics::AppleControl::Intensity);
	LUA_ENUM_ENTRY("Sharpness", cc::haptics::AppleControl::Sharpness);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsTrack(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("Track");
	LUA_ENUM_ENTRY("Normal", cc::haptics::Track::Normal);
	LUA_ENUM_ENTRY("Burst", cc::haptics::Track::Burst);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsStartPolicy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("StartPolicy");
	LUA_ENUM_ENTRY("Auto", cc::haptics::StartPolicy::Auto);
	LUA_ENUM_ENTRY("FixedTimeline", cc::haptics::StartPolicy::FixedTimeline);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsOwner(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("Owner");
	LUA_ENUM_ENTRY("Idle", cc::haptics::Owner::Idle);
	LUA_ENUM_ENTRY("Preset", cc::haptics::Owner::Preset);
	LUA_ENUM_ENTRY("LegacyRumble", cc::haptics::Owner::LegacyRumble);
	LUA_ENUM_ENTRY("LegacyPcm", cc::haptics::Owner::LegacyPcm);
	LUA_ENUM_ENTRY("Raw", cc::haptics::Owner::Raw);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsAvailability(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("Availability");
	LUA_ENUM_ENTRY("Available", cc::haptics::Availability::Available);
	LUA_ENUM_ENTRY("Stopping", cc::haptics::Availability::Stopping);
	LUA_ENUM_ENTRY("RouteFault", cc::haptics::Availability::RouteFault);
	LUA_ENUM_ENTRY("NotFocused", cc::haptics::Availability::NotFocused);
	LUA_ENUM_ENTRY("Disabled", cc::haptics::Availability::Disabled);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsPlaybackState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("PlaybackState");
	LUA_ENUM_ENTRY("Scheduled", cc::haptics::PlaybackState::Scheduled);
	LUA_ENUM_ENTRY("Active", cc::haptics::PlaybackState::Active);
	LUA_ENUM_ENTRY("Completed", cc::haptics::PlaybackState::Completed);
	LUA_ENUM_ENTRY("Stopped", cc::haptics::PlaybackState::Stopped);
	LUA_ENUM_ENTRY("Preempted", cc::haptics::PlaybackState::Preempted);
	LUA_ENUM_ENTRY("Dropped", cc::haptics::PlaybackState::Dropped);
	LUA_ENUM_ENTRY("Coalesced", cc::haptics::PlaybackState::Coalesced);
	LUA_ENUM_ENTRY("Failed", cc::haptics::PlaybackState::Failed);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsStopReason(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("StopReason");
	LUA_ENUM_ENTRY("None", cc::haptics::StopReason::None);
	LUA_ENUM_ENTRY("Requested", cc::haptics::StopReason::Requested);
	LUA_ENUM_ENTRY("Priority", cc::haptics::StopReason::Priority);
	LUA_ENUM_ENTRY("FocusLost", cc::haptics::StopReason::FocusLost);
	LUA_ENUM_ENTRY("EndpointLost", cc::haptics::StopReason::EndpointLost);
	LUA_ENUM_ENTRY("Replaced", cc::haptics::StopReason::Replaced);
	LUA_ENUM_ENTRY("IdleExpired", cc::haptics::StopReason::IdleExpired);
	LUA_ENUM_ENTRY("Disabled", cc::haptics::StopReason::Disabled);
	LUA_ENUM_ENTRY("Reconfigured", cc::haptics::StopReason::Reconfigured);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsOperationState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("OperationState");
	LUA_ENUM_ENTRY("Pending", cc::haptics::OperationState::Pending);
	LUA_ENUM_ENTRY("Succeeded", cc::haptics::OperationState::Succeeded);
	LUA_ENUM_ENTRY("Failed", cc::haptics::OperationState::Failed);
	LUA_ENUM_ENTRY("Cancelled", cc::haptics::OperationState::Cancelled);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsAcquirePolicy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("AcquirePolicy");
	LUA_ENUM_ENTRY("IfIdle", cc::haptics::AcquirePolicy::IfIdle);
	LUA_ENUM_ENTRY("InterruptPreset", cc::haptics::AcquirePolicy::InterruptPreset);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_haptics_cchapticsRawState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_ENUM_DEF("RawState");
	LUA_ENUM_ENTRY("Pending", cc::haptics::RawState::Pending);
	LUA_ENUM_ENTRY("Ready", cc::haptics::RawState::Ready);
	LUA_ENUM_ENTRY("Closed", cc::haptics::RawState::Closed);
	LUA_ENUM_ENTRY("Failed", cc::haptics::RawState::Failed);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}

int luaReg_cc_haptics_cchapticsPlaybackId(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::PlaybackId, "PlaybackId", "cc.haptics.PlaybackId",
		nullptr, lua::value_collect<cc::haptics::PlaybackId>);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::PlaybackId>(lua_S, "cc.haptics.PlaybackId");
	LUA_ENTRY_END(2);
	return 0;
}

int luaReg_cc_haptics_cchapticsOperationId(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::OperationId, "OperationId", "cc.haptics.OperationId",
		nullptr, lua::value_collect<cc::haptics::OperationId>);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::OperationId>(lua_S, "cc.haptics.OperationId");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_haptics_HapticTime_afterMs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticTime", "cc.haptics.HapticTime:afterMs");
	if (argc == 1 && !ok && !lua::haptic_detail::numberArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticTime::afterMs);
	}
	LUA_INVOKE_FOOTER("1");
}
int luaReg_cc_haptics_cchapticsHapticTime(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::HapticTime, "HapticTime", "cc.haptics.HapticTime",
		nullptr, lua::value_collect<cc::haptics::HapticTime>);
	LUA_METHOD("afterMs", lua_cc_haptics_HapticTime_afterMs);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::HapticTime>(lua_S, "cc.haptics.HapticTime");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_haptics_RawSession_cancel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:cancel");
	LUA_TRY_INVOKE_R(0, &cc::haptics::RawSession::cancel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_RawSession_close(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:close");
	LUA_TRY_INVOKE_R(0, static_cast<void(cc::haptics::RawSession::*)()>(&cc::haptics::RawSession::close));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_RawSession_composition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:composition");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::composition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_RawSession_envelope(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:envelope");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::envelope);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_RawSession_oneShot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:oneShot");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::oneShot);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_RawSession_playPattern(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:playPattern");
	if (argc == 2 && !ok && !lua::haptic_detail::booleanArgument(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, &cc::haptics::RawSession::playPattern);
	}
	LUA_TRY_INVOKE_R(1, ([](cc::haptics::RawSession* obj,const cc::haptics::ApplePattern& arg0){{return obj->playPattern(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_haptics_RawSession_predefined(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:predefined");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::predefined);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_RawSession_sendCurve(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:sendCurve");
	LUA_TRY_INVOKE_R(2, &cc::haptics::RawSession::sendCurve);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_haptics_RawSession_sendParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:sendParameters");
	LUA_TRY_INVOKE_R(2, &cc::haptics::RawSession::sendParameters);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_haptics_RawSession_state(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:state");
	LUA_TRY_INVOKE_R(0, &cc::haptics::RawSession::state);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_RawSession_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:stop");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::stop);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_RawSession_waveform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.RawSession", "cc.haptics.RawSession:waveform");
	LUA_TRY_INVOKE_R(1, &cc::haptics::RawSession::waveform);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_cc_haptics_cchapticsRawSession(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::RawSession, "RawSession", "cc.haptics.RawSession",
		nullptr, lua::value_collect<cc::haptics::RawSession>);
	LUA_METHOD("cancel", lua_cc_haptics_RawSession_cancel);
	LUA_METHOD("close", lua_cc_haptics_RawSession_close);
	LUA_METHOD("composition", lua_cc_haptics_RawSession_composition);
	LUA_METHOD("envelope", lua_cc_haptics_RawSession_envelope);
	LUA_METHOD("oneShot", lua_cc_haptics_RawSession_oneShot);
	LUA_METHOD("playPattern", lua_cc_haptics_RawSession_playPattern);
	LUA_METHOD("predefined", lua_cc_haptics_RawSession_predefined);
	LUA_METHOD("sendCurve", lua_cc_haptics_RawSession_sendCurve);
	LUA_METHOD("sendParameters", lua_cc_haptics_RawSession_sendParameters);
	LUA_METHOD("state", lua_cc_haptics_RawSession_state);
	LUA_METHOD("stop", lua_cc_haptics_RawSession_stop);
	LUA_METHOD("waveform", lua_cc_haptics_RawSession_waveform);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::RawSession>(lua_S, "cc.haptics.RawSession");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_haptics_HapticScope_acquireRaw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:acquireRaw");
	LUA_TRY_INVOKE_R(2, &cc::haptics::HapticScope::acquireRaw);
	LUA_TRY_INVOKE_R(1, ([](cc::haptics::HapticScope* obj,cc::haptics::TargetId arg0){{return obj->acquireRaw(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_haptics_HapticScope_close(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:close");
	LUA_TRY_INVOKE_R(0, static_cast<void(cc::haptics::HapticScope::*)()>(&cc::haptics::HapticScope::close));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticScope_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:play");
	LUA_TRY_INVOKE_R(3, &cc::haptics::HapticScope::play);
	LUA_TRY_INVOKE_R(2, ([](cc::haptics::HapticScope* obj,cc::haptics::TargetId arg0,const cc::haptics::HapticClip& arg1){{return obj->play(std::move(arg0),arg1);}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_haptics_HapticScope_readOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:readOperation");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticScope::readOperation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticScope_readPlayback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:readPlayback");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticScope::readPlayback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticScope_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:stop");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticScope::stop);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticScope_stopTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticScope", "cc.haptics.HapticScope:stopTarget");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticScope::stopTarget);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_cc_haptics_cchapticsHapticScope(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::HapticScope, "HapticScope", "cc.haptics.HapticScope",
		nullptr, lua::value_collect<cc::haptics::HapticScope>);
	LUA_METHOD("acquireRaw", lua_cc_haptics_HapticScope_acquireRaw);
	LUA_METHOD("close", lua_cc_haptics_HapticScope_close);
	LUA_METHOD("play", lua_cc_haptics_HapticScope_play);
	LUA_METHOD("readOperation", lua_cc_haptics_HapticScope_readOperation);
	LUA_METHOD("readPlayback", lua_cc_haptics_HapticScope_readPlayback);
	LUA_METHOD("stop", lua_cc_haptics_HapticScope_stop);
	LUA_METHOD("stopTarget", lua_cc_haptics_HapticScope_stopTarget);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::HapticScope>(lua_S, "cc.haptics.HapticScope");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_haptics_HapticService_capabilities(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:capabilities");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticService::capabilities);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticService_createScope(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:createScope");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticService::createScope);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticService_enumerate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:enumerate");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticService::enumerate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticService_gamepad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:gamepad");
	if (argc == 1 && !ok && !lua::haptic_detail::deviceArgument(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticService::gamepad);
	}
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticService_handset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:handset");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticService::handset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticService_now(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:now");
	LUA_TRY_INVOKE_R(0, &cc::haptics::HapticService::now);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_haptics_HapticService_preparePcm(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:preparePcm");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticService::preparePcm);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticService_setCalibration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:setCalibration");
	LUA_TRY_INVOKE_R(2, &cc::haptics::HapticService::setCalibration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_haptics_HapticService_setOutputSettings(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:setOutputSettings");
	LUA_TRY_INVOKE_R(1, &cc::haptics::HapticService::setOutputSettings);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_haptics_HapticService_setPcmModeTiming(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.haptics.HapticService", "cc.haptics.HapticService:setPcmModeTiming");
	LUA_TRY_INVOKE_R(2, &cc::haptics::HapticService::setPcmModeTiming);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_cc_haptics_cchapticsHapticService(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("haptics");
	LUA_CLS_DEF(cc::haptics::HapticService, "HapticService", "cc.haptics.HapticService",
		nullptr, lua::value_collect<cc::haptics::HapticService>);
	LUA_METHOD("capabilities", lua_cc_haptics_HapticService_capabilities);
	LUA_METHOD("createScope", lua_cc_haptics_HapticService_createScope);
	LUA_METHOD("enumerate", lua_cc_haptics_HapticService_enumerate);
	LUA_METHOD("gamepad", lua_cc_haptics_HapticService_gamepad);
	LUA_METHOD("handset", lua_cc_haptics_HapticService_handset);
	LUA_METHOD("now", lua_cc_haptics_HapticService_now);
	LUA_METHOD("preparePcm", lua_cc_haptics_HapticService_preparePcm);
	LUA_METHOD("setCalibration", lua_cc_haptics_HapticService_setCalibration);
	LUA_METHOD("setOutputSettings", lua_cc_haptics_HapticService_setOutputSettings);
	LUA_METHOD("setPcmModeTiming", lua_cc_haptics_HapticService_setPcmModeTiming);
	LUA_CLS_END();
	lua::register_value_metatable<cc::haptics::HapticService>(lua_S, "cc.haptics.HapticService");
	LUA_ENTRY_END(2);
	return 0;
}

int register_cc_haptics_manual(lua_State* lua_S);

int register_all_cc_haptics(lua_State* lua_S)
{
	luaReg_cc_haptics_cchapticsAssetFormat(lua_S);
	luaReg_cc_haptics_cchapticsImportPolicy(lua_S);
	luaReg_cc_haptics_cchapticsError(lua_S);
	luaReg_cc_haptics_cchapticsHapticClip(lua_S);
	luaReg_cc_haptics_cchapticsMobilePlatform(lua_S);
	luaReg_cc_haptics_cchapticsAndroidEffect(lua_S);
	luaReg_cc_haptics_cchapticsAppleControl(lua_S);
	luaReg_cc_haptics_cchapticsTrack(lua_S);
	luaReg_cc_haptics_cchapticsStartPolicy(lua_S);
	luaReg_cc_haptics_cchapticsOwner(lua_S);
	luaReg_cc_haptics_cchapticsAvailability(lua_S);
	luaReg_cc_haptics_cchapticsPlaybackState(lua_S);
	luaReg_cc_haptics_cchapticsStopReason(lua_S);
	luaReg_cc_haptics_cchapticsOperationState(lua_S);
	luaReg_cc_haptics_cchapticsAcquirePolicy(lua_S);
	luaReg_cc_haptics_cchapticsRawState(lua_S);
	luaReg_cc_haptics_cchapticsPlaybackId(lua_S);
	luaReg_cc_haptics_cchapticsOperationId(lua_S);
	luaReg_cc_haptics_cchapticsHapticTime(lua_S);
	luaReg_cc_haptics_cchapticsRawSession(lua_S);
	luaReg_cc_haptics_cchapticsHapticScope(lua_S);
	luaReg_cc_haptics_cchapticsHapticService(lua_S);
	return register_cc_haptics_manual(lua_S);
}
