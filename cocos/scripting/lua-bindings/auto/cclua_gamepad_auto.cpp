#include "cclua_gamepad_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/gamepad/cclua_gamepad_conversions.hpp"

static_assert(lua::value_type<cc::input::Frame>::value, "ValueTypes requires a shared runtime trait for cc::input::Frame");
static_assert(lua::value_type<cc::input::Pad>::value, "ValueTypes requires a shared runtime trait for cc::input::Pad");
static_assert(lua::value_type<cc::input::EventCursor>::value, "ValueTypes requires a shared runtime trait for cc::input::EventCursor");
static_assert(lua::value_type<cc::input::GamepadService>::value, "ValueTypes requires a shared runtime trait for cc::input::GamepadService");
static_assert(lua::value_type<cc::input::Subscription>::value, "ValueTypes requires a shared runtime trait for cc::input::Subscription");
static_assert(lua::value_type<cc::input::HapticPlayback>::value, "ValueTypes requires a shared runtime trait for cc::input::HapticPlayback");
int luaReg_cc_gamepad_ccgamepadButton(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Button");
	LUA_ENUM_ENTRY("South", cc::input::Button::South);
	LUA_ENUM_ENTRY("East", cc::input::Button::East);
	LUA_ENUM_ENTRY("West", cc::input::Button::West);
	LUA_ENUM_ENTRY("North", cc::input::Button::North);
	LUA_ENUM_ENTRY("Back", cc::input::Button::Back);
	LUA_ENUM_ENTRY("Guide", cc::input::Button::Guide);
	LUA_ENUM_ENTRY("Start", cc::input::Button::Start);
	LUA_ENUM_ENTRY("LeftStick", cc::input::Button::LeftStick);
	LUA_ENUM_ENTRY("RightStick", cc::input::Button::RightStick);
	LUA_ENUM_ENTRY("LeftShoulder", cc::input::Button::LeftShoulder);
	LUA_ENUM_ENTRY("RightShoulder", cc::input::Button::RightShoulder);
	LUA_ENUM_ENTRY("DpadUp", cc::input::Button::DpadUp);
	LUA_ENUM_ENTRY("DpadDown", cc::input::Button::DpadDown);
	LUA_ENUM_ENTRY("DpadLeft", cc::input::Button::DpadLeft);
	LUA_ENUM_ENTRY("DpadRight", cc::input::Button::DpadRight);
	LUA_ENUM_ENTRY("Misc1", cc::input::Button::Misc1);
	LUA_ENUM_ENTRY("RightPaddle1", cc::input::Button::RightPaddle1);
	LUA_ENUM_ENTRY("LeftPaddle1", cc::input::Button::LeftPaddle1);
	LUA_ENUM_ENTRY("RightPaddle2", cc::input::Button::RightPaddle2);
	LUA_ENUM_ENTRY("LeftPaddle2", cc::input::Button::LeftPaddle2);
	LUA_ENUM_ENTRY("TouchpadClick", cc::input::Button::TouchpadClick);
	LUA_ENUM_ENTRY("Misc2", cc::input::Button::Misc2);
	LUA_ENUM_ENTRY("Misc3", cc::input::Button::Misc3);
	LUA_ENUM_ENTRY("Misc4", cc::input::Button::Misc4);
	LUA_ENUM_ENTRY("Misc5", cc::input::Button::Misc5);
	LUA_ENUM_ENTRY("Misc6", cc::input::Button::Misc6);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadAxis(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Axis");
	LUA_ENUM_ENTRY("LeftX", cc::input::Axis::LeftX);
	LUA_ENUM_ENTRY("LeftY", cc::input::Axis::LeftY);
	LUA_ENUM_ENTRY("RightX", cc::input::Axis::RightX);
	LUA_ENUM_ENTRY("RightY", cc::input::Axis::RightY);
	LUA_ENUM_ENTRY("LeftTrigger", cc::input::Axis::LeftTrigger);
	LUA_ENUM_ENTRY("RightTrigger", cc::input::Axis::RightTrigger);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadSensor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Sensor");
	LUA_ENUM_ENTRY("Accel", cc::input::Sensor::Accel);
	LUA_ENUM_ENTRY("Gyro", cc::input::Sensor::Gyro);
	LUA_ENUM_ENTRY("AccelLeft", cc::input::Sensor::AccelLeft);
	LUA_ENUM_ENTRY("GyroLeft", cc::input::Sensor::GyroLeft);
	LUA_ENUM_ENTRY("AccelRight", cc::input::Sensor::AccelRight);
	LUA_ENUM_ENTRY("GyroRight", cc::input::Sensor::GyroRight);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadSide(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Side");
	LUA_ENUM_ENTRY("Left", cc::input::Side::Left);
	LUA_ENUM_ENTRY("Right", cc::input::Side::Right);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadFeature(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Feature");
	LUA_ENUM_ENTRY("BodyRumble", cc::input::Feature::BodyRumble);
	LUA_ENUM_ENTRY("TriggerRumble", cc::input::Feature::TriggerRumble);
	LUA_ENUM_ENTRY("MonoLed", cc::input::Feature::MonoLed);
	LUA_ENUM_ENTRY("RgbLed", cc::input::Feature::RgbLed);
	LUA_ENUM_ENTRY("PlayerLights", cc::input::Feature::PlayerLights);
	LUA_ENUM_ENTRY("AdaptiveLeft", cc::input::Feature::AdaptiveLeft);
	LUA_ENUM_ENTRY("AdaptiveRight", cc::input::Feature::AdaptiveRight);
	LUA_ENUM_ENTRY("BodyHaptics", cc::input::Feature::BodyHaptics);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadReason(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Reason");
	LUA_ENUM_ENTRY("Physical", cc::input::Reason::Physical);
	LUA_ENUM_ENTRY("Connect", cc::input::Reason::Connect);
	LUA_ENUM_ENTRY("Disconnect", cc::input::Reason::Disconnect);
	LUA_ENUM_ENTRY("FocusLost", cc::input::Reason::FocusLost);
	LUA_ENUM_ENTRY("FocusGained", cc::input::Reason::FocusGained);
	LUA_ENUM_ENTRY("Remap", cc::input::Reason::Remap);
	LUA_ENUM_ENTRY("Resync", cc::input::Reason::Resync);
	LUA_ENUM_ENTRY("Configuration", cc::input::Reason::Configuration);
	LUA_ENUM_ENTRY("Command", cc::input::Reason::Command);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadError(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Error");
	LUA_ENUM_ENTRY("None", cc::input::Error::None);
	LUA_ENUM_ENTRY("Unsupported", cc::input::Error::Unsupported);
	LUA_ENUM_ENTRY("Disconnected", cc::input::Error::Disconnected);
	LUA_ENUM_ENTRY("Busy", cc::input::Error::Busy);
	LUA_ENUM_ENTRY("PermissionDenied", cc::input::Error::PermissionDenied);
	LUA_ENUM_ENTRY("InvalidArgument", cc::input::Error::InvalidArgument);
	LUA_ENUM_ENTRY("NoMapping", cc::input::Error::NoMapping);
	LUA_ENUM_ENTRY("BackendFailure", cc::input::Error::BackendFailure);
	LUA_ENUM_ENTRY("QueueFull", cc::input::Error::QueueFull);
	LUA_ENUM_ENTRY("StaleFrame", cc::input::Error::StaleFrame);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadTimeQuality(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("TimeQuality");
	LUA_ENUM_ENTRY("ReceiveOnly", cc::input::TimeQuality::ReceiveOnly);
	LUA_ENUM_ENTRY("ConvertedOS", cc::input::TimeQuality::ConvertedOS);
	LUA_ENUM_ENTRY("CalibratedDevice", cc::input::TimeQuality::CalibratedDevice);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadGamepadType(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("GamepadType");
	LUA_ENUM_ENTRY("Unknown", cc::input::GamepadType::Unknown);
	LUA_ENUM_ENTRY("XboxCompatible", cc::input::GamepadType::XboxCompatible);
	LUA_ENUM_ENTRY("DualShock4", cc::input::GamepadType::DualShock4);
	LUA_ENUM_ENTRY("DualSense", cc::input::GamepadType::DualSense);
	LUA_ENUM_ENTRY("DualSenseEdge", cc::input::GamepadType::DualSenseEdge);
	LUA_ENUM_ENTRY("SwitchPro", cc::input::GamepadType::SwitchPro);
	LUA_ENUM_ENTRY("JoyConLeft", cc::input::GamepadType::JoyConLeft);
	LUA_ENUM_ENTRY("JoyConRight", cc::input::GamepadType::JoyConRight);
	LUA_ENUM_ENTRY("JoyConPair", cc::input::GamepadType::JoyConPair);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadContactPhase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("ContactPhase");
	LUA_ENUM_ENTRY("Down", cc::input::ContactPhase::Down);
	LUA_ENUM_ENTRY("Move", cc::input::ContactPhase::Move);
	LUA_ENUM_ENTRY("Up", cc::input::ContactPhase::Up);
	LUA_ENUM_ENTRY("Cancel", cc::input::ContactPhase::Cancel);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadPowerState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("PowerState");
	LUA_ENUM_ENTRY("Unknown", cc::input::PowerState::Unknown);
	LUA_ENUM_ENTRY("OnBattery", cc::input::PowerState::OnBattery);
	LUA_ENUM_ENTRY("Charging", cc::input::PowerState::Charging);
	LUA_ENUM_ENTRY("Charged", cc::input::PowerState::Charged);
	LUA_ENUM_ENTRY("External", cc::input::PowerState::External);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadLink(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Link");
	LUA_ENUM_ENTRY("Unknown", cc::input::Link::Unknown);
	LUA_ENUM_ENTRY("Wired", cc::input::Link::Wired);
	LUA_ENUM_ENTRY("Wireless", cc::input::Link::Wireless);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccAudioPlaybackState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("AudioPlaybackState");
	LUA_ENUM_ENTRY("Ready", cc::AudioPlaybackState::Ready);
	LUA_ENUM_ENTRY("Buffering", cc::AudioPlaybackState::Buffering);
	LUA_ENUM_ENTRY("Playing", cc::AudioPlaybackState::Playing);
	LUA_ENUM_ENTRY("Paused", cc::AudioPlaybackState::Paused);
	LUA_ENUM_ENTRY("Stopped", cc::AudioPlaybackState::Stopped);
	LUA_ENUM_ENTRY("Ended", cc::AudioPlaybackState::Ended);
	LUA_ENUM_ENTRY("Failed", cc::AudioPlaybackState::Failed);
	LUA_ENUM_ENTRY("Closed", cc::AudioPlaybackState::Closed);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadHapticStopReason(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("HapticStopReason");
	LUA_ENUM_ENTRY("None", cc::input::HapticStopReason::None);
	LUA_ENUM_ENTRY("Requested", cc::input::HapticStopReason::Requested);
	LUA_ENUM_ENTRY("Replaced", cc::input::HapticStopReason::Replaced);
	LUA_ENUM_ENTRY("FocusLost", cc::input::HapticStopReason::FocusLost);
	LUA_ENUM_ENTRY("EndpointLost", cc::input::HapticStopReason::EndpointLost);
	LUA_ENUM_ENTRY("Disconnected", cc::input::HapticStopReason::Disconnected);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_HapticPlayback_close(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:close");
	LUA_TRY_INVOKE_R(0, static_cast<void(cc::input::HapticPlayback::*)()>(&cc::input::HapticPlayback::close));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_HapticPlayback_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:pause");
	LUA_TRY_INVOKE_R(0, &cc::input::HapticPlayback::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_HapticPlayback_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:play");
	LUA_TRY_INVOKE_R(0, &cc::input::HapticPlayback::play);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_HapticPlayback_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:resume");
	LUA_TRY_INVOKE_R(0, &cc::input::HapticPlayback::resume);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_HapticPlayback_seekTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:seekTime");
	LUA_TRY_INVOKE_R(1, &cc::input::HapticPlayback::seekTime);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_HapticPlayback_setIntensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:setIntensity");
	LUA_TRY_INVOKE_R(1, &cc::input::HapticPlayback::setIntensity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_HapticPlayback_setLooping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:setLooping");
	LUA_TRY_INVOKE_R(1, &cc::input::HapticPlayback::setLooping);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_HapticPlayback_snapshot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:snapshot");
	LUA_TRY_INVOKE_R(0, &cc::input::HapticPlayback::snapshot);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_HapticPlayback_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.HapticPlayback", "cc.gamepad.HapticPlayback:stop");
	LUA_TRY_INVOKE_R(0, &cc::input::HapticPlayback::stop);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadHapticPlayback(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::HapticPlayback, "HapticPlayback", "cc.gamepad.HapticPlayback",
		nullptr, lua::value_collect<cc::input::HapticPlayback>);
	LUA_METHOD("close", lua_cc_input_HapticPlayback_close);
	LUA_METHOD("pause", lua_cc_input_HapticPlayback_pause);
	LUA_METHOD("play", lua_cc_input_HapticPlayback_play);
	LUA_METHOD("resume", lua_cc_input_HapticPlayback_resume);
	LUA_METHOD("seekTime", lua_cc_input_HapticPlayback_seekTime);
	LUA_METHOD("setIntensity", lua_cc_input_HapticPlayback_setIntensity);
	LUA_METHOD("setLooping", lua_cc_input_HapticPlayback_setLooping);
	LUA_METHOD("snapshot", lua_cc_input_HapticPlayback_snapshot);
	LUA_METHOD("stop", lua_cc_input_HapticPlayback_stop);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::HapticPlayback>(lua_S, "cc.gamepad.HapticPlayback");
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadTriggerMode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("TriggerMode");
	LUA_ENUM_ENTRY("Off", cc::input::TriggerMode::Off);
	LUA_ENUM_ENTRY("Resistance", cc::input::TriggerMode::Resistance);
	LUA_ENUM_ENTRY("Vibration", cc::input::TriggerMode::Vibration);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadChannel(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Channel");
	LUA_ENUM_ENTRY("All", cc::input::Channel::All);
	LUA_ENUM_ENTRY("Body", cc::input::Channel::Body);
	LUA_ENUM_ENTRY("Triggers", cc::input::Channel::Triggers);
	LUA_ENUM_ENTRY("AdaptiveLeft", cc::input::Channel::AdaptiveLeft);
	LUA_ENUM_ENTRY("AdaptiveRight", cc::input::Channel::AdaptiveRight);
	LUA_ENUM_ENTRY("Lights", cc::input::Channel::Lights);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadCompletion(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Completion");
	LUA_ENUM_ENTRY("Applied", cc::input::Completion::Applied);
	LUA_ENUM_ENTRY("Superseded", cc::input::Completion::Superseded);
	LUA_ENUM_ENTRY("Cancelled", cc::input::Completion::Cancelled);
	LUA_ENUM_ENTRY("Failed", cc::input::Completion::Failed);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadEventKind(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("EventKind");
	LUA_ENUM_ENTRY("Device", cc::input::EventKind::Device);
	LUA_ENUM_ENTRY("Button", cc::input::EventKind::Button);
	LUA_ENUM_ENTRY("Axis", cc::input::EventKind::Axis);
	LUA_ENUM_ENTRY("Raw", cc::input::EventKind::Raw);
	LUA_ENUM_ENTRY("Contact", cc::input::EventKind::Contact);
	LUA_ENUM_ENTRY("Motion", cc::input::EventKind::Motion);
	LUA_ENUM_ENTRY("Power", cc::input::EventKind::Power);
	LUA_ENUM_ENTRY("InputGap", cc::input::EventKind::InputGap);
	LUA_ENUM_ENTRY("OutputDone", cc::input::EventKind::OutputDone);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadChange(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("Change");
	LUA_ENUM_ENTRY("Connected", cc::input::Change::Connected);
	LUA_ENUM_ENTRY("Disconnected", cc::input::Change::Disconnected);
	LUA_ENUM_ENTRY("MappingChanged", cc::input::Change::MappingChanged);
	LUA_ENUM_ENTRY("CapabilitiesChanged", cc::input::Change::CapabilitiesChanged);
	LUA_ENUM_ENTRY("BaselineReady", cc::input::Change::BaselineReady);
	LUA_ENUM_ENTRY("FocusLost", cc::input::Change::FocusLost);
	LUA_ENUM_ENTRY("FocusGained", cc::input::Change::FocusGained);
	LUA_ENUM_ENTRY("PlayerChanged", cc::input::Change::PlayerChanged);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadRawKind(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("RawKind");
	LUA_ENUM_ENTRY("Button", cc::input::RawKind::Button);
	LUA_ENUM_ENTRY("Axis", cc::input::RawKind::Axis);
	LUA_ENUM_ENTRY("Hat", cc::input::RawKind::Hat);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadGapCause(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("GapCause");
	LUA_ENUM_ENTRY("QueueOverflow", cc::input::GapCause::QueueOverflow);
	LUA_ENUM_ENTRY("DriverOverflow", cc::input::GapCause::DriverOverflow);
	LUA_ENUM_ENTRY("SensorOverflow", cc::input::GapCause::SensorOverflow);
	LUA_ENUM_ENTRY("ClockReset", cc::input::GapCause::ClockReset);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_Pad_axis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:axis");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<float>>(cc::input::Pad::*)(cc::input::Axis)const>(&cc::input::Pad::axis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_axisValue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:axisValue");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<short>>(cc::input::Pad::*)(cc::input::Axis)const>(&cc::input::Pad::axisValue));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_contacts(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:contacts");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::span<const cc::input::Contact>>(cc::input::Pad::*)()const>(&cc::input::Pad::contacts));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_down(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:down");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Button)const>(&cc::input::Pad::down));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_fingersPerPad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:fingersPerPad");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::span<const unsigned int>>(cc::input::Pad::*)()const>(&cc::input::Pad::fingersPerPad));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_hasAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:hasAxis");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Axis)const>(&cc::input::Pad::hasAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_hasButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:hasButton");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Button)const>(&cc::input::Pad::hasButton));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_hasFeature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:hasFeature");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Feature)const>(&cc::input::Pad::hasFeature));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_hasSensor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:hasSensor");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Sensor)const>(&cc::input::Pad::hasSensor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_info(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:info");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<const cc::input::DeviceInfo *>(cc::input::Pad::*)()const>(&cc::input::Pad::info));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_inputLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:inputLayout");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::string_view>(cc::input::Pad::*)()const>(&cc::input::Pad::inputLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_label(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:label");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::string_view>(cc::input::Pad::*)(cc::input::Button)const>(&cc::input::Pad::label));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_latest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:latest");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<cc::input::Motion>>(cc::input::Pad::*)(cc::input::Sensor)const>(&cc::input::Pad::latest));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_link(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:link");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<cc::input::Link>(cc::input::Pad::*)()const>(&cc::input::Pad::link));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_mapped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mapped");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<bool>(cc::input::Pad::*)()const>(&cc::input::Pad::mapped));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_mappingRevision(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mappingRevision");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<unsigned int>(cc::input::Pad::*)()const>(&cc::input::Pad::mappingRevision));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_mappingStatus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mappingStatus");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::string_view>(cc::input::Pad::*)()const>(&cc::input::Pad::mappingStatus));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_nominalHz(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:nominalHz");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<float>>(cc::input::Pad::*)(cc::input::Sensor)const>(&cc::input::Pad::nominalHz));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_player(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:player");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::optional<unsigned int>>(cc::input::Pad::*)()const>(&cc::input::Pad::player));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_playerLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:playerLightMask");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<unsigned int>(cc::input::Pad::*)()const>(&cc::input::Pad::playerLightMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_power(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:power");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<cc::input::Power>(cc::input::Pad::*)()const>(&cc::input::Pad::power));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_pressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:pressed");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Button)const>(&cc::input::Pad::pressed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_raw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:raw");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<cc::input::RawView>(cc::input::Pad::*)()const>(&cc::input::Pad::raw));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Pad_released(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:released");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<bool>(cc::input::Pad::*)(cc::input::Button)const>(&cc::input::Pad::released));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Pad_triggerLimits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:triggerLimits");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<cc::input::TriggerLimits>>(cc::input::Pad::*)(cc::input::Side)const>(&cc::input::Pad::triggerLimits));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_cc_gamepad_ccgamepadPad(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::Pad, "Pad", "cc.gamepad.Pad",
		nullptr, lua::value_collect<cc::input::Pad>);
	LUA_METHOD("axis", lua_cc_input_Pad_axis);
	LUA_METHOD("axisValue", lua_cc_input_Pad_axisValue);
	LUA_METHOD("contacts", lua_cc_input_Pad_contacts);
	LUA_METHOD("down", lua_cc_input_Pad_down);
	LUA_METHOD("fingersPerPad", lua_cc_input_Pad_fingersPerPad);
	LUA_METHOD("hasAxis", lua_cc_input_Pad_hasAxis);
	LUA_METHOD("hasButton", lua_cc_input_Pad_hasButton);
	LUA_METHOD("hasFeature", lua_cc_input_Pad_hasFeature);
	LUA_METHOD("hasSensor", lua_cc_input_Pad_hasSensor);
	LUA_METHOD("info", lua_cc_input_Pad_info);
	LUA_METHOD("inputLayout", lua_cc_input_Pad_inputLayout);
	LUA_METHOD("label", lua_cc_input_Pad_label);
	LUA_METHOD("latest", lua_cc_input_Pad_latest);
	LUA_METHOD("link", lua_cc_input_Pad_link);
	LUA_METHOD("mapped", lua_cc_input_Pad_mapped);
	LUA_METHOD("mappingRevision", lua_cc_input_Pad_mappingRevision);
	LUA_METHOD("mappingStatus", lua_cc_input_Pad_mappingStatus);
	LUA_METHOD("nominalHz", lua_cc_input_Pad_nominalHz);
	LUA_METHOD("player", lua_cc_input_Pad_player);
	LUA_METHOD("playerLightMask", lua_cc_input_Pad_playerLightMask);
	LUA_METHOD("power", lua_cc_input_Pad_power);
	LUA_METHOD("pressed", lua_cc_input_Pad_pressed);
	LUA_METHOD("raw", lua_cc_input_Pad_raw);
	LUA_METHOD("released", lua_cc_input_Pad_released);
	LUA_METHOD("triggerLimits", lua_cc_input_Pad_triggerLimits);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::Pad>(lua_S, "cc.gamepad.Pad");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_EventCursor_next(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.EventCursor", "cc.gamepad.EventCursor:next");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::optional<cc::input::GamepadEvent>>(cc::input::EventCursor::*)()>(&cc::input::EventCursor::next));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadEventCursor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::EventCursor, "EventCursor", "cc.gamepad.EventCursor",
		nullptr, lua::value_collect<cc::input::EventCursor>);
	LUA_METHOD("next", lua_cc_input_EventCursor_next);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::EventCursor>(lua_S, "cc.gamepad.EventCursor");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_Frame_cutoffNs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:cutoffNs");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Frame::TimeResult(cc::input::Frame::*)()const>(&cc::input::Frame::cutoffNs));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Frame_devices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:devices");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::span<const cc::input::DeviceId>>(cc::input::Frame::*)()const>(&cc::input::Frame::devices));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Frame_events(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:events");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<cc::input::EventCursor>(cc::input::Frame::*)()const>(&cc::input::Frame::events));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_Frame_find(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:find");
	LUA_TRY_INVOKE_R(1, static_cast<cc::input::Result<std::optional<cc::input::Pad>>(cc::input::Frame::*)(cc::input::DeviceId)const>(&cc::input::Frame::find));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_Frame_tick(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:tick");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Frame::TimeResult(cc::input::Frame::*)()const>(&cc::input::Frame::tick));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::Frame, "Frame", "cc.gamepad.Frame",
		nullptr, lua::value_collect<cc::input::Frame>);
	LUA_METHOD("cutoffNs", lua_cc_input_Frame_cutoffNs);
	LUA_METHOD("devices", lua_cc_input_Frame_devices);
	LUA_METHOD("events", lua_cc_input_Frame_events);
	LUA_METHOD("find", lua_cc_input_Frame_find);
	LUA_METHOD("tick", lua_cc_input_Frame_tick);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::Frame>(lua_S, "cc.gamepad.Frame");
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadMappingSource(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("MappingSource");
	LUA_ENUM_ENTRY("BuiltIn", cc::input::MappingSource::BuiltIn);
	LUA_ENUM_ENTRY("Application", cc::input::MappingSource::Application);
	LUA_ENUM_ENTRY("User", cc::input::MappingSource::User);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int luaReg_cc_gamepad_ccgamepadMappingChange(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_ENUM_DEF("MappingChange");
	LUA_ENUM_ENTRY("Added", cc::input::MappingChange::Added);
	LUA_ENUM_ENTRY("Replaced", cc::input::MappingChange::Replaced);
	LUA_ENUM_ENTRY("Unchanged", cc::input::MappingChange::Unchanged);
	LUA_ENUM_ENTRY("Shadowed", cc::input::MappingChange::Shadowed);
	LUA_ENUM_ENTRY("ConditionSkipped", cc::input::MappingChange::ConditionSkipped);
	LUA_ENUM_ENTRY("Error", cc::input::MappingChange::Error);
	LUA_ENUM_END();
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_Subscription_close(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Subscription", "cc.gamepad.Subscription:close");
	LUA_TRY_INVOKE_R(0, static_cast<void(cc::input::Subscription::*)()>(&cc::input::Subscription::close));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadSubscription(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::Subscription, "Subscription", "cc.gamepad.Subscription",
		nullptr, lua::value_collect<cc::input::Subscription>);
	LUA_METHOD("close", lua_cc_input_Subscription_close);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::Subscription>(lua_S, "cc.gamepad.Subscription");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_GamepadService_adaptiveTrigger(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:adaptiveTrigger");
	LUA_TRY_INVOKE_R(6, &cc::input::GamepadService::adaptiveTrigger);
	LUA_INVOKE_FOOTER("6");
}
int lua_cc_input_GamepadService_addGamepadMapping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:addGamepadMapping");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::addGamepadMapping);
	LUA_TRY_INVOKE_R(1, ([](cc::input::GamepadService* obj,std::string_view arg0){{return obj->addGamepadMapping(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_input_GamepadService_assignPlayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:assignPlayer");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::assignPlayer);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_input_GamepadService_clearPlayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:clearPlayer");
	LUA_TRY_INVOKE_R(1, &cc::input::GamepadService::clearPlayer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_GamepadService_createHapticPlayback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:createHapticPlayback");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::createHapticPlayback);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_input_GamepadService_frame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:frame");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Frame(cc::input::GamepadService::*)()const>(&cc::input::GamepadService::frame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_GamepadService_importMappings(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:importMappings");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::importMappings);
	LUA_TRY_INVOKE_R(1, ([](cc::input::GamepadService* obj,std::string_view arg0){{return obj->importMappings(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_input_GamepadService_mappingFor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:mappingFor");
	LUA_TRY_INVOKE_R(1, &cc::input::GamepadService::mappingFor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_input_GamepadService_playerLights(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:playerLights");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::playerLights);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_input_GamepadService_rgb(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:rgb");
	LUA_TRY_INVOKE_R(4, &cc::input::GamepadService::rgb);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_input_GamepadService_rumble(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:rumble");
	LUA_TRY_INVOKE_R(4, &cc::input::GamepadService::rumble);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_input_GamepadService_setLocalBindings(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:setLocalBindings");
	LUA_TRY_INVOKE_R(3, &cc::input::GamepadService::setLocalBindings);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_input_GamepadService_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:stop");
	LUA_TRY_INVOKE_R(2, &cc::input::GamepadService::stop);
	LUA_TRY_INVOKE_R(1, ([](cc::input::GamepadService* obj,cc::input::DeviceId arg0){{return obj->stop(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_input_GamepadService_subscribeSensor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:subscribeSensor");
	LUA_TRY_INVOKE_R(3, &cc::input::GamepadService::subscribeSensor);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_input_GamepadService_triggerRumble(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:triggerRumble");
	LUA_TRY_INVOKE_R(4, &cc::input::GamepadService::triggerRumble);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_input_GamepadService_watchRaw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.GamepadService", "cc.gamepad.GamepadService:watchRaw");
	LUA_TRY_INVOKE_R(1, &cc::input::GamepadService::watchRaw);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_cc_gamepad_ccgamepadGamepadService(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::GamepadService, "GamepadService", "cc.gamepad.GamepadService",
		nullptr, lua::value_collect<cc::input::GamepadService>);
	LUA_METHOD("adaptiveTrigger", lua_cc_input_GamepadService_adaptiveTrigger);
	LUA_METHOD("addGamepadMapping", lua_cc_input_GamepadService_addGamepadMapping);
	LUA_METHOD("assignPlayer", lua_cc_input_GamepadService_assignPlayer);
	LUA_METHOD("clearPlayer", lua_cc_input_GamepadService_clearPlayer);
	LUA_METHOD("createHapticPlayback", lua_cc_input_GamepadService_createHapticPlayback);
	LUA_METHOD("frame", lua_cc_input_GamepadService_frame);
	LUA_METHOD("importMappings", lua_cc_input_GamepadService_importMappings);
	LUA_METHOD("mappingFor", lua_cc_input_GamepadService_mappingFor);
	LUA_METHOD("playerLights", lua_cc_input_GamepadService_playerLights);
	LUA_METHOD("rgb", lua_cc_input_GamepadService_rgb);
	LUA_METHOD("rumble", lua_cc_input_GamepadService_rumble);
	LUA_METHOD("setLocalBindings", lua_cc_input_GamepadService_setLocalBindings);
	LUA_METHOD("stop", lua_cc_input_GamepadService_stop);
	LUA_METHOD("subscribeSensor", lua_cc_input_GamepadService_subscribeSensor);
	LUA_METHOD("triggerRumble", lua_cc_input_GamepadService_triggerRumble);
	LUA_METHOD("watchRaw", lua_cc_input_GamepadService_watchRaw);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::GamepadService>(lua_S, "cc.gamepad.GamepadService");
	LUA_ENTRY_END(2);
	return 0;
}

int register_cc_gamepad_manual(lua_State* lua_S);

int register_all_cc_gamepad(lua_State* lua_S)
{
	luaReg_cc_gamepad_ccgamepadButton(lua_S);
	luaReg_cc_gamepad_ccgamepadAxis(lua_S);
	luaReg_cc_gamepad_ccgamepadSensor(lua_S);
	luaReg_cc_gamepad_ccgamepadSide(lua_S);
	luaReg_cc_gamepad_ccgamepadFeature(lua_S);
	luaReg_cc_gamepad_ccgamepadReason(lua_S);
	luaReg_cc_gamepad_ccgamepadError(lua_S);
	luaReg_cc_gamepad_ccgamepadTimeQuality(lua_S);
	luaReg_cc_gamepad_ccgamepadGamepadType(lua_S);
	luaReg_cc_gamepad_ccgamepadContactPhase(lua_S);
	luaReg_cc_gamepad_ccgamepadPowerState(lua_S);
	luaReg_cc_gamepad_ccgamepadLink(lua_S);
	luaReg_cc_gamepad_ccAudioPlaybackState(lua_S);
	luaReg_cc_gamepad_ccgamepadHapticStopReason(lua_S);
	luaReg_cc_gamepad_ccgamepadHapticPlayback(lua_S);
	luaReg_cc_gamepad_ccgamepadTriggerMode(lua_S);
	luaReg_cc_gamepad_ccgamepadChannel(lua_S);
	luaReg_cc_gamepad_ccgamepadCompletion(lua_S);
	luaReg_cc_gamepad_ccgamepadEventKind(lua_S);
	luaReg_cc_gamepad_ccgamepadChange(lua_S);
	luaReg_cc_gamepad_ccgamepadRawKind(lua_S);
	luaReg_cc_gamepad_ccgamepadGapCause(lua_S);
	luaReg_cc_gamepad_ccgamepadPad(lua_S);
	luaReg_cc_gamepad_ccgamepadEventCursor(lua_S);
	luaReg_cc_gamepad_ccgamepadFrame(lua_S);
	luaReg_cc_gamepad_ccgamepadMappingSource(lua_S);
	luaReg_cc_gamepad_ccgamepadMappingChange(lua_S);
	luaReg_cc_gamepad_ccgamepadSubscription(lua_S);
	luaReg_cc_gamepad_ccgamepadGamepadService(lua_S);
	return register_cc_gamepad_manual(lua_S);
}
