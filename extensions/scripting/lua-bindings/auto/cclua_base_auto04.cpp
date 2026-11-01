#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_Core_ccTintTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintTo, "TintTo", "cc.TintTo",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTintBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintBy, "TintBy", "cc.TintBy",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_DelayTime_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DelayTime", "cc.DelayTime:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::DelayTime*(*)(float)>(&cocos2d::DelayTime::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDelayTime(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DelayTime, "DelayTime", "cc.DelayTime",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_DelayTime_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animate_getCurrentFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getCurrentFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Animate::*)()>(&cocos2d::Animate::getCurrentFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate_initWithAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:initWithAnimation");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Animate::*)(cocos2d::Animation*)>(&cocos2d::Animate::initWithAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate::*)(cocos2d::Animation*)>(&cocos2d::Animate::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate", "cc.Animate:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animate*(*)(cocos2d::Animation*)>(&cocos2d::Animate::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAnimate(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animate, "Animate", "cc.Animate",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getCurrentFrameIndex", lua_cocos2d_Animate_getCurrentFrameIndex);
	LUA_METHOD("initWithAnimation", lua_cocos2d_Animate_initWithAnimation);
	LUA_METHOD("setAnimation", lua_cocos2d_Animate_setAnimation);
	LUA_METHOD("create", lua_cocos2d_Animate_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TargetedAction_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:initWithTarget");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::TargetedAction::*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::initWithTarget));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TargetedAction_setForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:setForcedTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TargetedAction::*)(cocos2d::Node*)>(&cocos2d::TargetedAction::setForcedTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TargetedAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TargetedAction*(*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTargetedAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TargetedAction, "TargetedAction", "cc.TargetedAction",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithTarget", lua_cocos2d_TargetedAction_initWithTarget);
	LUA_METHOD("setForcedTarget", lua_cocos2d_TargetedAction_setForcedTarget);
	LUA_METHOD("create", lua_cocos2d_TargetedAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccActionFloat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionFloat, "ActionFloat", "cc.ActionFloat",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Properties_exists(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:exists");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Properties::*)(const char*)const>(&cocos2d::Properties::exists));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Properties_getBool(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getBool");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Properties::*)(const char*, bool)const>(&cocos2d::Properties::getBool));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Properties* obj,const char* arg0){{return obj->getBool(arg0);}});
	LUA_TRY_INVOKE_R(0, [](const cocos2d::Properties* obj){{return obj->getBool();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_Properties_getFloat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getFloat");
	LUA_TRY_INVOKE_R(1, static_cast<float(cocos2d::Properties::*)(const char*)const>(&cocos2d::Properties::getFloat));
	LUA_TRY_INVOKE_R(0, [](const cocos2d::Properties* obj){{return obj->getFloat();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Properties_getId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getId");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Properties::*)()const>(&cocos2d::Properties::getId));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Properties_getInt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getInt");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::Properties::*)(const char*)const>(&cocos2d::Properties::getInt));
	LUA_TRY_INVOKE_R(0, [](const cocos2d::Properties* obj){{return obj->getInt();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Properties_getNextProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getNextProperty");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::Properties::*)()>(&cocos2d::Properties::getNextProperty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Properties_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getString");
	LUA_TRY_INVOKE_R(2, static_cast<const char*(cocos2d::Properties::*)(const char*, const char*)const>(&cocos2d::Properties::getString));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Properties* obj,const char* arg0){{return obj->getString(arg0);}});
	LUA_TRY_INVOKE_R(0, [](const cocos2d::Properties* obj){{return obj->getString();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_Properties_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getType");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Properties::Type(cocos2d::Properties::*)(const char*)const>(&cocos2d::Properties::getType));
	LUA_TRY_INVOKE_R(0, [](const cocos2d::Properties* obj){{return obj->getType();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Properties_getVariable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:getVariable");
	LUA_TRY_INVOKE_R(2, static_cast<const char*(cocos2d::Properties::*)(const char*, const char*)const>(&cocos2d::Properties::getVariable));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Properties* obj,const char* arg0){{return obj->getVariable(arg0);}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Properties_rewind(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:rewind");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Properties::*)()>(&cocos2d::Properties::rewind));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Properties_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:setString");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Properties::*)(const char*, const char*)>(&cocos2d::Properties::setString));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Properties_setVariable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Properties", "cc.Properties:setVariable");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Properties::*)(const char*, const char*)>(&cocos2d::Properties::setVariable));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccProperties(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::Properties, "Properties", "cc.Properties",
		nullptr, nullptr);
	LUA_METHOD("exists", lua_cocos2d_Properties_exists);
	LUA_METHOD("getBool", lua_cocos2d_Properties_getBool);
	LUA_METHOD("getFloat", lua_cocos2d_Properties_getFloat);
	LUA_METHOD("getId", lua_cocos2d_Properties_getId);
	LUA_METHOD("getInt", lua_cocos2d_Properties_getInt);
	LUA_METHOD("getNextProperty", lua_cocos2d_Properties_getNextProperty);
	LUA_METHOD("getString", lua_cocos2d_Properties_getString);
	LUA_METHOD("getType", lua_cocos2d_Properties_getType);
	LUA_METHOD("getVariable", lua_cocos2d_Properties_getVariable);
	LUA_METHOD("rewind", lua_cocos2d_Properties_rewind);
	LUA_METHOD("setString", lua_cocos2d_Properties_setString);
	LUA_METHOD("setVariable", lua_cocos2d_Properties_setVariable);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_UserDefault_deleteValueForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:deleteValueForKey");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::deleteValueForKey));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_UserDefault_flush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:flush");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::UserDefault::*)()>(&cocos2d::UserDefault::flush));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_UserDefault_getBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getBoolForKey");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::getBoolForKey));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getBoolForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getDoubleForKey");
	LUA_TRY_INVOKE_R(2, static_cast<double(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::getDoubleForKey));
	LUA_TRY_INVOKE_R(1, static_cast<double(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getDoubleForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getFloatForKey");
	LUA_TRY_INVOKE_R(2, static_cast<float(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::getFloatForKey));
	LUA_TRY_INVOKE_R(1, static_cast<float(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getFloatForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getIntegerForKey");
	LUA_TRY_INVOKE_R(2, static_cast<int(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::getIntegerForKey));
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getIntegerForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getStringForKey");
	LUA_TRY_INVOKE_R(2, static_cast<std::string_view(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::getStringForKey));
	LUA_TRY_INVOKE_R(1, static_cast<std::string_view(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getStringForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_setBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setBoolForKey");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::setBoolForKey));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setDoubleForKey");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::setDoubleForKey));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setEncryptEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setEncryptEnabled");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::UserDefault::*)(bool, std::string_view, std::string_view)>(&cocos2d::UserDefault::setEncryptEnabled));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_UserDefault_setFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setFloatForKey");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::setFloatForKey));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setIntegerForKey");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::setIntegerForKey));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setStringForKey");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::setStringForKey));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccUserDefault(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::UserDefault, "UserDefault", "cc.UserDefault",
		nullptr, nullptr);
	LUA_METHOD("deleteValueForKey", lua_cocos2d_UserDefault_deleteValueForKey);
	LUA_METHOD("flush", lua_cocos2d_UserDefault_flush);
	LUA_METHOD("getBoolForKey", lua_cocos2d_UserDefault_getBoolForKey);
	LUA_METHOD("getDoubleForKey", lua_cocos2d_UserDefault_getDoubleForKey);
	LUA_METHOD("getFloatForKey", lua_cocos2d_UserDefault_getFloatForKey);
	LUA_METHOD("getIntegerForKey", lua_cocos2d_UserDefault_getIntegerForKey);
	LUA_METHOD("getStringForKey", lua_cocos2d_UserDefault_getStringForKey);
	LUA_METHOD("setBoolForKey", lua_cocos2d_UserDefault_setBoolForKey);
	LUA_METHOD("setDoubleForKey", lua_cocos2d_UserDefault_setDoubleForKey);
	LUA_METHOD("setEncryptEnabled", lua_cocos2d_UserDefault_setEncryptEnabled);
	LUA_METHOD("setFloatForKey", lua_cocos2d_UserDefault_setFloatForKey);
	LUA_METHOD("setIntegerForKey", lua_cocos2d_UserDefault_setIntegerForKey);
	LUA_METHOD("setStringForKey", lua_cocos2d_UserDefault_setStringForKey);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FileUtils_addSearchPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:addSearchPath");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::FileUtils::*)(std::string_view, const bool)>(&cocos2d::FileUtils::addSearchPath));
	LUA_TRY_INVOKE(1, [](cocos2d::FileUtils* obj,std::string_view arg0){{return obj->addSearchPath(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_fullPathForFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathForFilename");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::fullPathForFilename));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_fullPathFromRelativeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathFromRelativeFile");
	LUA_TRY_INVOKE_R(2, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::fullPathFromRelativeFile));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getDefaultResourceRootPath");
	LUA_TRY_INVOKE_R(0, static_cast<const std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getDefaultResourceRootPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getFileExtension(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileExtension");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getFileExtension));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getNativeWritableAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getNativeWritableAbsolutePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getNativeWritableAbsolutePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getWritablePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getWritablePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_isAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePath");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isAbsolutePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isDirectoryExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExistInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isDirectoryExistInternal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isFileExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExistInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isFileExistInternal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isPopupNotify");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::isPopupNotify));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_purgeCachedEntries(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:purgeCachedEntries");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::FileUtils::*)()>(&cocos2d::FileUtils::purgeCachedEntries));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_setDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setDefaultResourceRootPath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::setDefaultResourceRootPath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setPopupNotify");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(bool)>(&cocos2d::FileUtils::setPopupNotify));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setWritablePath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::setWritablePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getFileShortName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileShortName");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(*)(std::string_view)>(&cocos2d::FileUtils::getFileShortName));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isAbsolutePathInternal(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePathInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(*)(std::string_view)>(&cocos2d::FileUtils::isAbsolutePathInternal));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFileUtils(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::FileUtils, "FileUtils", "cc.FileUtils",
		nullptr, nullptr);
	LUA_METHOD("addSearchPath", lua_cocos2d_FileUtils_addSearchPath);
	LUA_METHOD("fullPathForFilename", lua_cocos2d_FileUtils_fullPathForFilename);
	LUA_METHOD("fullPathFromRelativeFile", lua_cocos2d_FileUtils_fullPathFromRelativeFile);
	LUA_METHOD("getDefaultResourceRootPath", lua_cocos2d_FileUtils_getDefaultResourceRootPath);
	LUA_METHOD("getFileExtension", lua_cocos2d_FileUtils_getFileExtension);
	LUA_METHOD("getNativeWritableAbsolutePath", lua_cocos2d_FileUtils_getNativeWritableAbsolutePath);
	LUA_METHOD("getWritablePath", lua_cocos2d_FileUtils_getWritablePath);
	LUA_METHOD("isAbsolutePath", lua_cocos2d_FileUtils_isAbsolutePath);
	LUA_METHOD("isDirectoryExistInternal", lua_cocos2d_FileUtils_isDirectoryExistInternal);
	LUA_METHOD("isFileExistInternal", lua_cocos2d_FileUtils_isFileExistInternal);
	LUA_METHOD("isPopupNotify", lua_cocos2d_FileUtils_isPopupNotify);
	LUA_METHOD("purgeCachedEntries", lua_cocos2d_FileUtils_purgeCachedEntries);
	LUA_METHOD("setDefaultResourceRootPath", lua_cocos2d_FileUtils_setDefaultResourceRootPath);
	LUA_METHOD("setPopupNotify", lua_cocos2d_FileUtils_setPopupNotify);
	LUA_METHOD("setWritablePath", lua_cocos2d_FileUtils_setWritablePath);
	LUA_METHOD("getFileShortName", lua_cocos2d_FileUtils_getFileShortName);
	LUA_METHOD("isAbsolutePathInternal", lua_cocos2d_FileUtils_isAbsolutePathInternal);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventAcceleration, "EventAcceleration", "cc.EventAcceleration",
		cocos2d::Event, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventCustom_getEventName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventCustom", "cc.EventCustom:getEventName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::EventCustom::*)()const>(&cocos2d::EventCustom::getEventName));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventCustom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventCustom, "EventCustom", "cc.EventCustom",
		cocos2d::Event, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventName", lua_cocos2d_EventCustom_getEventName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithFixedPriority");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::addEventListenerWithFixedPriority));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, cocos2d::Node*)>(&cocos2d::EventDispatcher::addEventListenerWithSceneGraphPriority));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_dispatchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:dispatchEvent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Event*)>(&cocos2d::EventDispatcher::dispatchEvent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_hasEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:hasEventListener");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::EventDispatcher::*)(std::string_view)const>(&cocos2d::EventDispatcher::hasEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventDispatcher::*)()const>(&cocos2d::EventDispatcher::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_pauseEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:pauseEventListenersForTarget");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::pauseEventListenersForTarget));
	LUA_TRY_INVOKE(1, [](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->pauseEventListenersForTarget(arg0);}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeAllEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeAllEventListeners");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::EventDispatcher::*)()>(&cocos2d::EventDispatcher::removeAllEventListeners));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_removeCustomEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeCustomEventListeners");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(std::string_view)>(&cocos2d::EventDispatcher::removeCustomEventListeners));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*)>(&cocos2d::EventDispatcher::removeEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForTarget");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::removeEventListenersForTarget));
	LUA_TRY_INVOKE(1, [](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->removeEventListenersForTarget(arg0);}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener::Type)>(&cocos2d::EventDispatcher::removeEventListenersForType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_resumeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:resumeEventListenersForTarget");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::resumeEventListenersForTarget));
	LUA_TRY_INVOKE(1, [](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->resumeEventListenersForTarget(arg0);}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(bool)>(&cocos2d::EventDispatcher::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_setPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setPriority");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::setPriority));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventDispatcher(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventDispatcher, "EventDispatcher", "cc.EventDispatcher",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addEventListenerWithFixedPriority", lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority);
	LUA_METHOD("addEventListenerWithSceneGraphPriority", lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority);
	LUA_METHOD("dispatchEvent", lua_cocos2d_EventDispatcher_dispatchEvent);
	LUA_METHOD("hasEventListener", lua_cocos2d_EventDispatcher_hasEventListener);
	LUA_METHOD("isEnabled", lua_cocos2d_EventDispatcher_isEnabled);
	LUA_METHOD("pauseEventListenersForTarget", lua_cocos2d_EventDispatcher_pauseEventListenersForTarget);
	LUA_METHOD("removeAllEventListeners", lua_cocos2d_EventDispatcher_removeAllEventListeners);
	LUA_METHOD("removeCustomEventListeners", lua_cocos2d_EventDispatcher_removeCustomEventListeners);
	LUA_METHOD("removeEventListener", lua_cocos2d_EventDispatcher_removeEventListener);
	LUA_METHOD("removeEventListenersForTarget", lua_cocos2d_EventDispatcher_removeEventListenersForTarget);
	LUA_METHOD("removeEventListenersForType", lua_cocos2d_EventDispatcher_removeEventListenersForType);
	LUA_METHOD("resumeEventListenersForTarget", lua_cocos2d_EventDispatcher_resumeEventListenersForTarget);
	LUA_METHOD("setEnabled", lua_cocos2d_EventDispatcher_setEnabled);
	LUA_METHOD("setPriority", lua_cocos2d_EventDispatcher_setPriority);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
