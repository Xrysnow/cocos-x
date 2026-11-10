#include "cclua_studio_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "scripting/lua-bindings/manual/cocostudio/CustomGUIReader.h"

int lua_cocostudio_ComExtensionData_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ComExtensionData::*)()const>(&cocostudio::ComExtensionData::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_getCustomProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:getCustomProperty");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::ComExtensionData::*)()const>(&cocostudio::ComExtensionData::getCustomProperty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComExtensionData::*)(int)>(&cocostudio::ComExtensionData::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComExtensionData_setCustomProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:setCustomProperty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComExtensionData::*)(std::string_view)>(&cocostudio::ComExtensionData::setCustomProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComExtensionData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComExtensionData*(*)()>(&cocostudio::ComExtensionData::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComExtensionData::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComExtensionData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComExtensionData, "ComExtensionData", "ccs.ComExtensionData",
		cocostudio::ComExtensionData, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getActionTag", lua_cocostudio_ComExtensionData_getActionTag);
	LUA_METHOD("getCustomProperty", lua_cocostudio_ComExtensionData_getCustomProperty);
	LUA_METHOD("setActionTag", lua_cocostudio_ComExtensionData_setActionTag);
	LUA_METHOD("setCustomProperty", lua_cocostudio_ComExtensionData_setCustomProperty);
	LUA_METHOD("create", lua_cocostudio_ComExtensionData_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComExtensionData_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_CustomGUIReader_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.CustomGUIReader", "ccs.CustomGUIReader:create");
	if (argc == 3 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else if (argc == 3 && !ok && lua_isnil(lua_S, 4)) { arg_cur = 3; } else {
	LUA_TRY_INVOKE_R(3, (static_cast<cocostudio::CustomGUIReader*(*)(std::string_view, cocostudio::CustomGUIReader::CreateFunction, cocostudio::CustomGUIReader::SetPropsFunction)>(&cocostudio::CustomGUIReader::create)));
	}
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Studio_ccsCustomGUIReader(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::CustomGUIReader, "CustomGUIReader", "ccs.CustomGUIReader",
		cocostudio::CustomGUIReader, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_CustomGUIReader_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
