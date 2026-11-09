#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"

int lua_cocos2d_TintBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintBy", "cc.TintBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TintBy::*)(float, int16_t, int16_t, int16_t)>(&cocos2d::TintBy::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintBy", "cc.TintBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TintBy*(*)(float, int16_t, int16_t, int16_t)>(&cocos2d::TintBy::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTintBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintBy, "TintBy", "cc.TintBy",
		cocos2d::TintBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintBy_create);
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
		cocos2d::DelayTime, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_DelayTime_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animate_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getAnimation");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Animation*(cocos2d::Animate::*)()const>(&cocos2d::Animate::getAnimation));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Animation*(cocos2d::Animate::*)()>(&cocos2d::Animate::getAnimation));
	LUA_INVOKE_FOOTER("0");
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
		cocos2d::Animate, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocos2d_Animate_getAnimation);
	LUA_METHOD("getCurrentFrameIndex", lua_cocos2d_Animate_getCurrentFrameIndex);
	LUA_METHOD("initWithAnimation", lua_cocos2d_Animate_initWithAnimation);
	LUA_METHOD("setAnimation", lua_cocos2d_Animate_setAnimation);
	LUA_METHOD("create", lua_cocos2d_Animate_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TargetedAction_getForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:getForcedTarget");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Node*(cocos2d::TargetedAction::*)()const>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Node*(cocos2d::TargetedAction::*)()>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TargetedAction_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:initWithTarget");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TargetedAction::*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::initWithTarget)));
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TargetedAction*(*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTargetedAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TargetedAction, "TargetedAction", "cc.TargetedAction",
		cocos2d::TargetedAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getForcedTarget", lua_cocos2d_TargetedAction_getForcedTarget);
	LUA_METHOD("initWithTarget", lua_cocos2d_TargetedAction_initWithTarget);
	LUA_METHOD("setForcedTarget", lua_cocos2d_TargetedAction_setForcedTarget);
	LUA_METHOD("create", lua_cocos2d_TargetedAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionFloat_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:initWithDuration");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ActionFloat::*)(float, float, float, cocos2d::ActionFloat::ActionFloatCallback)>(&cocos2d::ActionFloat::initWithDuration)));
	}
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ActionFloat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:create");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ActionFloat*(*)(float, float, float, cocos2d::ActionFloat::ActionFloatCallback)>(&cocos2d::ActionFloat::create)));
	}
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionFloat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionFloat, "ActionFloat", "cc.ActionFloat",
		cocos2d::ActionFloat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionFloat_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ActionFloat_create);
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
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::getBoolForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getBoolForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getDoubleForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<double(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::getDoubleForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<double(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getDoubleForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getFloatForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::getFloatForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<float(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getFloatForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getIntegerForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::getIntegerForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getIntegerForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getLargeIntForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int64_t(cocos2d::UserDefault::*)(const char*, int64_t)>(&cocos2d::UserDefault::getLargeIntForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getLargeIntForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getStringForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<std::string_view(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::getStringForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<std::string_view(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getStringForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_setBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setBoolForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::setBoolForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setDoubleForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::setDoubleForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setEncryptEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setEncryptEnabled");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::UserDefault::*)(bool, std::string_view, std::string_view)>(&cocos2d::UserDefault::setEncryptEnabled)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_UserDefault_setFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setFloatForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::setFloatForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setIntegerForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::setIntegerForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setLargeIntForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, int64_t)>(&cocos2d::UserDefault::setLargeIntForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setStringForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::setStringForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::UserDefault*(*)()>(&cocos2d::UserDefault::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccUserDefault(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::UserDefault, "UserDefault", "cc.UserDefault",
		cocos2d::UserDefault, "",
		nullptr, nullptr);
	LUA_METHOD("deleteValueForKey", lua_cocos2d_UserDefault_deleteValueForKey);
	LUA_METHOD("flush", lua_cocos2d_UserDefault_flush);
	LUA_METHOD("getBoolForKey", lua_cocos2d_UserDefault_getBoolForKey);
	LUA_METHOD("getDoubleForKey", lua_cocos2d_UserDefault_getDoubleForKey);
	LUA_METHOD("getFloatForKey", lua_cocos2d_UserDefault_getFloatForKey);
	LUA_METHOD("getIntegerForKey", lua_cocos2d_UserDefault_getIntegerForKey);
	LUA_METHOD("getLargeIntForKey", lua_cocos2d_UserDefault_getLargeIntForKey);
	LUA_METHOD("getStringForKey", lua_cocos2d_UserDefault_getStringForKey);
	LUA_METHOD("setBoolForKey", lua_cocos2d_UserDefault_setBoolForKey);
	LUA_METHOD("setDoubleForKey", lua_cocos2d_UserDefault_setDoubleForKey);
	LUA_METHOD("setEncryptEnabled", lua_cocos2d_UserDefault_setEncryptEnabled);
	LUA_METHOD("setFloatForKey", lua_cocos2d_UserDefault_setFloatForKey);
	LUA_METHOD("setIntegerForKey", lua_cocos2d_UserDefault_setIntegerForKey);
	LUA_METHOD("setLargeIntForKey", lua_cocos2d_UserDefault_setLargeIntForKey);
	LUA_METHOD("setStringForKey", lua_cocos2d_UserDefault_setStringForKey);
	LUA_METHOD("getInstance", lua_cocos2d_UserDefault_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccAppDirectory(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("AppDirectory");
	LUA_ENUM_ENTRY("PersistentData", cocos2d::AppDirectory::PersistentData);
	LUA_ENUM_ENTRY("TransientData", cocos2d::AppDirectory::TransientData);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccDirectoryStatus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("DirectoryStatus");
	LUA_ENUM_ENTRY("Ok", cocos2d::DirectoryStatus::Ok);
	LUA_ENUM_ENTRY("NotInitialized", cocos2d::DirectoryStatus::NotInitialized);
	LUA_ENUM_ENTRY("InvalidArgument", cocos2d::DirectoryStatus::InvalidArgument);
	LUA_ENUM_ENTRY("InUse", cocos2d::DirectoryStatus::InUse);
	LUA_ENUM_ENTRY("Unavailable", cocos2d::DirectoryStatus::Unavailable);
	LUA_ENUM_ENTRY("PermissionDenied", cocos2d::DirectoryStatus::PermissionDenied);
	LUA_ENUM_ENTRY("NotDirectory", cocos2d::DirectoryStatus::NotDirectory);
	LUA_ENUM_ENTRY("IoError", cocos2d::DirectoryStatus::IoError);
	LUA_ENUM_ENTRY("Unsupported", cocos2d::DirectoryStatus::Unsupported);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FileUtils_addSearchPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:addSearchPath");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, const bool)>(&cocos2d::FileUtils::addSearchPath)));
	LUA_TRY_INVOKE(1, ([](cocos2d::FileUtils* obj,std::string_view arg0){{return obj->addSearchPath(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_createDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:createDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::createDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::createDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_ensureAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:ensureAppDirectory");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::DirectoryResult(cocos2d::FileUtils::*)(cocos2d::AppDirectory, std::string_view)const>(&cocos2d::FileUtils::ensureAppDirectory)));
	LUA_TRY_INVOKE_R(1, ([](const cocos2d::FileUtils* obj,cocos2d::AppDirectory arg0){{return obj->ensureAppDirectory(std::move(arg0));}}));
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
	LUA_TRY_INVOKE_R(2, (static_cast<std::string(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::fullPathFromRelativeFile)));
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
int lua_cocos2d_FileUtils_getFileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileSize");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(int64_t)>)const>(&cocos2d::FileUtils::getFileSize)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getFileSize));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_getNativeWritableAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getNativeWritableAbsolutePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getNativeWritableAbsolutePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getOriginalSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getOriginalSearchPaths");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<std::string>(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getOriginalSearchPaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getPersistentDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getPersistentDataPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getPersistentDataPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSearchPaths");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<std::string>(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getSearchPaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getStringFromFile_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getStringFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getStringFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getSuitableFOpen(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSuitableFOpen");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::getSuitableFOpen));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getTransientDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getTransientDataPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getTransientDataPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getValueMapFromData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromData");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ValueMap(cocos2d::FileUtils::*)(const char*, int)const>(&cocos2d::FileUtils::getValueMapFromData)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getValueMapFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueMap(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getValueMapFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getValueVectorFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueVectorFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueVector(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getValueVectorFromFile));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_FileUtils_isDirectoryExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::isDirectoryExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isDirectoryExist));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_isDirectoryExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExistInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isDirectoryExistInternal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isFileExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::isFileExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isFileExist));
	LUA_INVOKE_FOOTER("1,2");
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
int lua_cocos2d_FileUtils_listFiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFiles");
	LUA_TRY_INVOKE_R(1, static_cast<std::vector<std::string>(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::listFiles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_listFilesAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(std::vector<std::string>)>)const>(&cocos2d::FileUtils::listFilesAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_listFilesRecursivelyAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesRecursivelyAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(std::vector<std::string>)>)const>(&cocos2d::FileUtils::listFilesRecursivelyAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_purgeCachedEntries(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:purgeCachedEntries");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::FileUtils::*)()>(&cocos2d::FileUtils::purgeCachedEntries));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_queryAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:queryAppDirectory");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::DirectoryResult(cocos2d::FileUtils::*)(cocos2d::AppDirectory)const>(&cocos2d::FileUtils::queryAppDirectory));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_removeDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::removeDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::removeDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_removeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeFile");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::removeFile)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::removeFile));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_renameFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:renameFile");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::string_view)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::renameFile)));
	LUA_INVOKE_FOOTER("2,3,4");
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
int lua_cocos2d_FileUtils_setSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setSearchPaths");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(const std::vector<std::string>&)>(&cocos2d::FileUtils::setSearchPaths));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setWritablePath");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::setWritablePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_writeStringToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeStringToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(std::string, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeStringToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::writeStringToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_writeToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeToFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueMap&, std::string_view)const>(&cocos2d::FileUtils::writeToFile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_writeValueMapToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueMapToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(cocos2d::ValueMap, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeValueMapToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueMap&, std::string_view)const>(&cocos2d::FileUtils::writeValueMapToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_writeValueVectorToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueVectorToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(cocos2d::ValueVector, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeValueVectorToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueVector&, std::string_view)const>(&cocos2d::FileUtils::writeValueVectorToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_getFileShortName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileShortName");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(*)(std::string_view)>(&cocos2d::FileUtils::getFileShortName));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::FileUtils*(*)()>(&cocos2d::FileUtils::getInstance));
	LUA_SINVOKE_FOOTER("0");
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
	LUA_CLS_DEF_BASE(cocos2d::FileUtils, "FileUtils", "cc.FileUtils",
		cocos2d::FileUtils, "",
		nullptr, nullptr);
	LUA_METHOD("addSearchPath", lua_cocos2d_FileUtils_addSearchPath);
	LUA_METHOD("createDirectory", lua_cocos2d_FileUtils_createDirectory);
	LUA_METHOD("ensureAppDirectory", lua_cocos2d_FileUtils_ensureAppDirectory);
	LUA_METHOD("fullPathForFilename", lua_cocos2d_FileUtils_fullPathForFilename);
	LUA_METHOD("fullPathFromRelativeFile", lua_cocos2d_FileUtils_fullPathFromRelativeFile);
	LUA_METHOD("getDefaultResourceRootPath", lua_cocos2d_FileUtils_getDefaultResourceRootPath);
	LUA_METHOD("getFileExtension", lua_cocos2d_FileUtils_getFileExtension);
	LUA_METHOD("getFileSize", lua_cocos2d_FileUtils_getFileSize);
	LUA_METHOD("getNativeWritableAbsolutePath", lua_cocos2d_FileUtils_getNativeWritableAbsolutePath);
	LUA_METHOD("getOriginalSearchPaths", lua_cocos2d_FileUtils_getOriginalSearchPaths);
	LUA_METHOD("getPersistentDataPath", lua_cocos2d_FileUtils_getPersistentDataPath);
	LUA_METHOD("getSearchPaths", lua_cocos2d_FileUtils_getSearchPaths);
	LUA_METHOD("getStringFromFile", lua_cocos2d_FileUtils_getStringFromFile_1);
	LUA_METHOD("getSuitableFOpen", lua_cocos2d_FileUtils_getSuitableFOpen);
	LUA_METHOD("getTransientDataPath", lua_cocos2d_FileUtils_getTransientDataPath);
	LUA_METHOD("getValueMapFromData", lua_cocos2d_FileUtils_getValueMapFromData);
	LUA_METHOD("getValueMapFromFile", lua_cocos2d_FileUtils_getValueMapFromFile);
	LUA_METHOD("getValueVectorFromFile", lua_cocos2d_FileUtils_getValueVectorFromFile);
	LUA_METHOD("getWritablePath", lua_cocos2d_FileUtils_getWritablePath);
	LUA_METHOD("isAbsolutePath", lua_cocos2d_FileUtils_isAbsolutePath);
	LUA_METHOD("isDirectoryExist", lua_cocos2d_FileUtils_isDirectoryExist);
	LUA_METHOD("isDirectoryExistInternal", lua_cocos2d_FileUtils_isDirectoryExistInternal);
	LUA_METHOD("isFileExist", lua_cocos2d_FileUtils_isFileExist);
	LUA_METHOD("isFileExistInternal", lua_cocos2d_FileUtils_isFileExistInternal);
	LUA_METHOD("isPopupNotify", lua_cocos2d_FileUtils_isPopupNotify);
	LUA_METHOD("listFiles", lua_cocos2d_FileUtils_listFiles);
	LUA_METHOD("listFilesAsync", lua_cocos2d_FileUtils_listFilesAsync);
	LUA_METHOD("listFilesRecursivelyAsync", lua_cocos2d_FileUtils_listFilesRecursivelyAsync);
	LUA_METHOD("purgeCachedEntries", lua_cocos2d_FileUtils_purgeCachedEntries);
	LUA_METHOD("queryAppDirectory", lua_cocos2d_FileUtils_queryAppDirectory);
	LUA_METHOD("removeDirectory", lua_cocos2d_FileUtils_removeDirectory);
	LUA_METHOD("removeFile", lua_cocos2d_FileUtils_removeFile);
	LUA_METHOD("renameFile", lua_cocos2d_FileUtils_renameFile);
	LUA_METHOD("setDefaultResourceRootPath", lua_cocos2d_FileUtils_setDefaultResourceRootPath);
	LUA_METHOD("setPopupNotify", lua_cocos2d_FileUtils_setPopupNotify);
	LUA_METHOD("setSearchPaths", lua_cocos2d_FileUtils_setSearchPaths);
	LUA_METHOD("setWritablePath", lua_cocos2d_FileUtils_setWritablePath);
	LUA_METHOD("writeStringToFile", lua_cocos2d_FileUtils_writeStringToFile);
	LUA_METHOD("writeToFile", lua_cocos2d_FileUtils_writeToFile);
	LUA_METHOD("writeValueMapToFile", lua_cocos2d_FileUtils_writeValueMapToFile);
	LUA_METHOD("writeValueVectorToFile", lua_cocos2d_FileUtils_writeValueVectorToFile);
	LUA_METHOD("getFileShortName", lua_cocos2d_FileUtils_getFileShortName);
	LUA_METHOD("getInstance", lua_cocos2d_FileUtils_getInstance);
	LUA_METHOD("isAbsolutePathInternal", lua_cocos2d_FileUtils_isAbsolutePathInternal);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventAcceleration, "EventAcceleration", "cc.EventAcceleration",
		cocos2d::EventAcceleration, "cc.Event",
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
		cocos2d::EventCustom, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventName", lua_cocos2d_EventCustom_getEventName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventDispatcher_addCustomEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addCustomEventListener");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EventListenerCustom*(cocos2d::EventDispatcher::*)(std::string_view, const std::function<void(cocos2d::EventCustom*)>&)>(&cocos2d::EventDispatcher::addCustomEventListener)));
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithFixedPriority");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::addEventListenerWithFixedPriority)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, cocos2d::Node*)>(&cocos2d::EventDispatcher::addEventListenerWithSceneGraphPriority)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::pauseEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->pauseEventListenersForTarget(arg0);}}));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::removeEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->removeEventListenersForTarget(arg0);}}));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::resumeEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->resumeEventListenersForTarget(arg0);}}));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::setPriority)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventDispatcher(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventDispatcher, "EventDispatcher", "cc.EventDispatcher",
		cocos2d::EventDispatcher, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addCustomEventListener", lua_cocos2d_EventDispatcher_addCustomEventListener);
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
