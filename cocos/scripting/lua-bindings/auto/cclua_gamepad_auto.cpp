#include "cclua_gamepad_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/gamepad/cclua_gamepad_conversions.hpp"

static_assert(lua::value_type<cc::input::gamepad_lua::Frame>::value, "ValueTypes requires a shared runtime trait for cc::input::gamepad_lua::Frame");
static_assert(lua::value_type<cc::input::gamepad_lua::Pad>::value, "ValueTypes requires a shared runtime trait for cc::input::gamepad_lua::Pad");
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
int lua_cc_input_gamepad_lua_Frame_devices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:devices");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::span<const cc::input::DeviceId>>(cc::input::gamepad_lua::Frame::*)()const>(&cc::input::gamepad_lua::Frame::devices));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Frame_tick(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Frame", "cc.gamepad.Frame:tick");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<double>(cc::input::gamepad_lua::Frame::*)()const>(&cc::input::gamepad_lua::Frame::tick));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::gamepad_lua::Frame, "Frame", "cc.gamepad.Frame",
		nullptr, lua::value_collect<cc::input::gamepad_lua::Frame>);
	LUA_METHOD("devices", lua_cc_input_gamepad_lua_Frame_devices);
	LUA_METHOD("tick", lua_cc_input_gamepad_lua_Frame_tick);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::gamepad_lua::Frame>(lua_S, "cc.gamepad.Frame");
	LUA_ENTRY_END(2);
	return 0;
}
int lua_cc_input_gamepad_lua_Pad_info(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:info");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<const cc::input::DeviceInfo *>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::info));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Pad_inputLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:inputLayout");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::string_view>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::inputLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Pad_mapped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mapped");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<bool>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::mapped));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Pad_mappingRevision(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mappingRevision");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<unsigned int>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::mappingRevision));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Pad_mappingStatus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:mappingStatus");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::string_view>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::mappingStatus));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_input_gamepad_lua_Pad_player(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.gamepad.Pad", "cc.gamepad.Pad:player");
	LUA_TRY_INVOKE_R(0, static_cast<cc::input::Result<std::optional<unsigned int>>(cc::input::gamepad_lua::Pad::*)()const>(&cc::input::gamepad_lua::Pad::player));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_cc_gamepad_ccgamepadPad(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENTRY("gamepad");
	LUA_CLS_DEF(cc::input::gamepad_lua::Pad, "Pad", "cc.gamepad.Pad",
		nullptr, lua::value_collect<cc::input::gamepad_lua::Pad>);
	LUA_METHOD("info", lua_cc_input_gamepad_lua_Pad_info);
	LUA_METHOD("inputLayout", lua_cc_input_gamepad_lua_Pad_inputLayout);
	LUA_METHOD("mapped", lua_cc_input_gamepad_lua_Pad_mapped);
	LUA_METHOD("mappingRevision", lua_cc_input_gamepad_lua_Pad_mappingRevision);
	LUA_METHOD("mappingStatus", lua_cc_input_gamepad_lua_Pad_mappingStatus);
	LUA_METHOD("player", lua_cc_input_gamepad_lua_Pad_player);
	LUA_CLS_END();
	lua::register_value_metatable<cc::input::gamepad_lua::Pad>(lua_S, "cc.gamepad.Pad");
	LUA_ENTRY_END(2);
	return 0;
}

int register_cc_gamepad_manual(lua_State* lua_S);

int register_all_cc_gamepad(lua_State* lua_S)
{
	luaReg_cc_gamepad_ccgamepadGamepadType(lua_S);
	luaReg_cc_gamepad_ccgamepadFrame(lua_S);
	luaReg_cc_gamepad_ccgamepadPad(lua_S);
	return register_cc_gamepad_manual(lua_S);
}
