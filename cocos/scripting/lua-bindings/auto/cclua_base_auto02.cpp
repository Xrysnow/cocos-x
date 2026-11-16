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
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#endif

int lua_cocos2d_ActionFloat_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:initWithDuration");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, &cocos2d::ActionFloat::initWithDuration);
	}
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ActionFloat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:create");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, &cocos2d::ActionFloat::create);
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
	LUA_TRY_INVOKE(1, &cocos2d::UserDefault::deleteValueForKey);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_UserDefault_flush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:flush");
	LUA_TRY_INVOKE(0, &cocos2d::UserDefault::flush);
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
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setBoolForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setDoubleForKey");
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setDoubleForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setEncryptEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setEncryptEnabled");
	LUA_TRY_INVOKE(3, &cocos2d::UserDefault::setEncryptEnabled);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_UserDefault_setFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setFloatForKey");
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setFloatForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setIntegerForKey");
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setIntegerForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setLargeIntForKey");
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setLargeIntForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setStringForKey");
	LUA_TRY_INVOKE(2, &cocos2d::UserDefault::setStringForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::UserDefault::getInstance);
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
	LUA_TRY_INVOKE(2, &cocos2d::FileUtils::addSearchPath);
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
	LUA_TRY_INVOKE_R(2, &cocos2d::FileUtils::ensureAppDirectory);
	LUA_TRY_INVOKE_R(1, ([](const cocos2d::FileUtils* obj,cocos2d::AppDirectory arg0){{return obj->ensureAppDirectory(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_fullPathForFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathForFilename");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::fullPathForFilename);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_fullPathFromRelativeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathFromRelativeFile");
	LUA_TRY_INVOKE_R(2, &cocos2d::FileUtils::fullPathFromRelativeFile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getDefaultResourceRootPath");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getDefaultResourceRootPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getFileExtension(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileExtension");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::getFileExtension);
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
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getNativeWritableAbsolutePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getOriginalSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getOriginalSearchPaths");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getOriginalSearchPaths);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getPersistentDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getPersistentDataPath");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getPersistentDataPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSearchPaths");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getSearchPaths);
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
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::getSuitableFOpen);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getTransientDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getTransientDataPath");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getTransientDataPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getValueMapFromData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromData");
	LUA_TRY_INVOKE_R(2, &cocos2d::FileUtils::getValueMapFromData);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getValueMapFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromFile");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::getValueMapFromFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getValueVectorFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueVectorFromFile");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::getValueVectorFromFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getWritablePath");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getWritablePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_isAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePath");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::isAbsolutePath);
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
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::isDirectoryExistInternal);
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
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::isFileExistInternal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isPopupNotify");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::isPopupNotify);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_listFiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFiles");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::listFiles);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_listFilesAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesAsync");
	LUA_TRY_INVOKE(2, &cocos2d::FileUtils::listFilesAsync);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_listFilesRecursivelyAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesRecursivelyAsync");
	LUA_TRY_INVOKE(2, &cocos2d::FileUtils::listFilesRecursivelyAsync);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_purgeCachedEntries(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:purgeCachedEntries");
	LUA_TRY_INVOKE(0, &cocos2d::FileUtils::purgeCachedEntries);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_queryAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:queryAppDirectory");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::queryAppDirectory);
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
	LUA_TRY_INVOKE(1, &cocos2d::FileUtils::setDefaultResourceRootPath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setPopupNotify");
	LUA_TRY_INVOKE(1, &cocos2d::FileUtils::setPopupNotify);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setSearchPaths");
	LUA_TRY_INVOKE(1, &cocos2d::FileUtils::setSearchPaths);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setWritablePath");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::setWritablePath);
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
	LUA_TRY_INVOKE_R(2, &cocos2d::FileUtils::writeToFile);
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
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::getFileShortName);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::FileUtils::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_isAbsolutePathInternal(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePathInternal");
	LUA_TRY_INVOKE_R(1, &cocos2d::FileUtils::isAbsolutePathInternal);
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
	LUA_TRY_INVOKE_R(0, &cocos2d::EventCustom::getEventName);
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
	LUA_TRY_INVOKE_R(2, &cocos2d::EventDispatcher::addCustomEventListener);
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithFixedPriority");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::addEventListenerWithFixedPriority);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::addEventListenerWithSceneGraphPriority);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_dispatchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:dispatchEvent");
	LUA_TRY_INVOKE(1, &cocos2d::EventDispatcher::dispatchEvent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_hasEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:hasEventListener");
	LUA_TRY_INVOKE_R(1, &cocos2d::EventDispatcher::hasEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:isEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventDispatcher::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_pauseEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:pauseEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::pauseEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->pauseEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeAllEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeAllEventListeners");
	LUA_TRY_INVOKE(0, &cocos2d::EventDispatcher::removeAllEventListeners);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_removeCustomEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeCustomEventListeners");
	LUA_TRY_INVOKE(1, &cocos2d::EventDispatcher::removeCustomEventListeners);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::EventDispatcher::removeEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::removeEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->removeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForType");
	LUA_TRY_INVOKE(1, &cocos2d::EventDispatcher::removeEventListenersForType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_resumeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:resumeEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::resumeEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->resumeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::EventDispatcher::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_setPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setPriority");
	LUA_TRY_INVOKE(2, &cocos2d::EventDispatcher::setPriority);
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

int luaReg_Core_ccEventFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventFocus, "EventFocus", "cc.EventFocus",
		cocos2d::EventFocus, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerAcceleration_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerAcceleration", "cc.EventListenerAcceleration:init");
	LUA_TRY_INVOKE_R(1, &cocos2d::EventListenerAcceleration::init);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerAcceleration, "EventListenerAcceleration", "cc.EventListenerAcceleration",
		cocos2d::EventListenerAcceleration, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerAcceleration_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerFocus_clone_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListener>(cocos2d::EventListenerFocus::*)()>(&cocos2d::EventListenerFocus::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerFocus_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerFocus::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerFocus_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListenerFocus>(*)()>(&cocos2d::EventListenerFocus::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerFocus, "EventListenerFocus", "cc.EventListenerFocus",
		cocos2d::EventListenerFocus, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_EventListenerFocus_clone_1);
	LUA_METHOD("init", lua_cocos2d_EventListenerFocus_init);
	LUA_METHOD("create", lua_cocos2d_EventListenerFocus_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerKeyboard_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerKeyboard", "cc.EventListenerKeyboard:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerKeyboard::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerKeyboard_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerKeyboard", "cc.EventListenerKeyboard:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListenerKeyboard>(*)()>(&cocos2d::EventListenerKeyboard::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerKeyboard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerKeyboard, "EventListenerKeyboard", "cc.EventListenerKeyboard",
		cocos2d::EventListenerKeyboard, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerKeyboard_init);
	LUA_METHOD("create", lua_cocos2d_EventListenerKeyboard_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventMouse_getCursorX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorX");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getCursorX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getCursorY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorY");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getCursorY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getDelta");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getDelta);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocation");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocationInView");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getMouseButton");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getMouseButton);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getPreviousLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocation");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getPreviousLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getPreviousLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocationInView");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getPreviousLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getScrollX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollX");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getScrollX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getScrollY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollY");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getScrollY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getStartLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocation");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getStartLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_getStartLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocationInView");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventMouse::getStartLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventMouse_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setCursorPosition");
	LUA_TRY_INVOKE(2, &cocos2d::EventMouse::setCursorPosition);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventMouse_setMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setMouseButton");
	LUA_TRY_INVOKE(1, &cocos2d::EventMouse::setMouseButton);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventMouse_setScrollData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setScrollData");
	LUA_TRY_INVOKE(2, &cocos2d::EventMouse::setScrollData);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventMouse, "EventMouse", "cc.EventMouse",
		cocos2d::EventMouse, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getCursorX", lua_cocos2d_EventMouse_getCursorX);
	LUA_METHOD("getCursorY", lua_cocos2d_EventMouse_getCursorY);
	LUA_METHOD("getDelta", lua_cocos2d_EventMouse_getDelta);
	LUA_METHOD("getLocation", lua_cocos2d_EventMouse_getLocation);
	LUA_METHOD("getLocationInView", lua_cocos2d_EventMouse_getLocationInView);
	LUA_METHOD("getMouseButton", lua_cocos2d_EventMouse_getMouseButton);
	LUA_METHOD("getPreviousLocation", lua_cocos2d_EventMouse_getPreviousLocation);
	LUA_METHOD("getPreviousLocationInView", lua_cocos2d_EventMouse_getPreviousLocationInView);
	LUA_METHOD("getScrollX", lua_cocos2d_EventMouse_getScrollX);
	LUA_METHOD("getScrollY", lua_cocos2d_EventMouse_getScrollY);
	LUA_METHOD("getStartLocation", lua_cocos2d_EventMouse_getStartLocation);
	LUA_METHOD("getStartLocationInView", lua_cocos2d_EventMouse_getStartLocationInView);
	LUA_METHOD("setCursorPosition", lua_cocos2d_EventMouse_setCursorPosition);
	LUA_METHOD("setMouseButton", lua_cocos2d_EventMouse_setMouseButton);
	LUA_METHOD("setScrollData", lua_cocos2d_EventMouse_setScrollData);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerMouse_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerMouse", "cc.EventListenerMouse:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerMouse::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerMouse_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerMouse", "cc.EventListenerMouse:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListenerMouse>(*)()>(&cocos2d::EventListenerMouse::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerMouse, "EventListenerMouse", "cc.EventListenerMouse",
		cocos2d::EventListenerMouse, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerMouse_init);
	LUA_METHOD("create", lua_cocos2d_EventListenerMouse_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerTouchOneByOne_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerTouchOneByOne::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerTouchOneByOne_isSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:isSwallowTouches");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerTouchOneByOne::isSwallowTouches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerTouchOneByOne_setSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:setSwallowTouches");
	LUA_TRY_INVOKE(1, &cocos2d::EventListenerTouchOneByOne::setSwallowTouches);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventListenerTouchOneByOne_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListenerTouchOneByOne>(*)()>(&cocos2d::EventListenerTouchOneByOne::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerTouchOneByOne(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerTouchOneByOne, "EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne",
		cocos2d::EventListenerTouchOneByOne, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerTouchOneByOne_init);
	LUA_METHOD("isSwallowTouches", lua_cocos2d_EventListenerTouchOneByOne_isSwallowTouches);
	LUA_METHOD("setSwallowTouches", lua_cocos2d_EventListenerTouchOneByOne_setSwallowTouches);
	LUA_METHOD("create", lua_cocos2d_EventListenerTouchOneByOne_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerTouchAllAtOnce_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::EventListenerTouchAllAtOnce::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListenerTouchAllAtOnce_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::EventListenerTouchAllAtOnce>(*)()>(&cocos2d::EventListenerTouchAllAtOnce::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerTouchAllAtOnce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerTouchAllAtOnce, "EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce",
		cocos2d::EventListenerTouchAllAtOnce, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerTouchAllAtOnce_init);
	LUA_METHOD("create", lua_cocos2d_EventListenerTouchAllAtOnce_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionCamera_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getCenter");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionCamera::getCenter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_getEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getEye");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionCamera::getEye);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_getUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getUp");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionCamera::getUp);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_reverse_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:reverse");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::Action>(cocos2d::ActionCamera::*)()const>(&cocos2d::ActionCamera::reverse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionCamera_setCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setCenter");
	LUA_TRY_INVOKE(1, &cocos2d::ActionCamera::setCenter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionCamera_setEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setEye");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ActionCamera::*)(float, float, float)>(&cocos2d::ActionCamera::setEye)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionCamera::*)(const cocos2d::Vec3&)>(&cocos2d::ActionCamera::setEye));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cocos2d_ActionCamera_setUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setUp");
	LUA_TRY_INVOKE(1, &cocos2d::ActionCamera::setUp);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionCamera, "ActionCamera", "cc.ActionCamera",
		cocos2d::ActionCamera, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getCenter", lua_cocos2d_ActionCamera_getCenter);
	LUA_METHOD("getEye", lua_cocos2d_ActionCamera_getEye);
	LUA_METHOD("getUp", lua_cocos2d_ActionCamera_getUp);
	LUA_METHOD("reverse", lua_cocos2d_ActionCamera_reverse_1);
	LUA_METHOD("setCenter", lua_cocos2d_ActionCamera_setCenter);
	LUA_METHOD("setEye", lua_cocos2d_ActionCamera_setEye);
	LUA_METHOD("setUp", lua_cocos2d_ActionCamera_setUp);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_OrbitCamera_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:initWithDuration");
	LUA_TRY_INVOKE_R(7, &cocos2d::OrbitCamera::initWithDuration);
	LUA_INVOKE_FOOTER("7");
}
int lua_cocos2d_OrbitCamera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:create");
	LUA_TRY_INVOKE_R(7, &cocos2d::OrbitCamera::create);
	LUA_SINVOKE_FOOTER("7");
}
int luaReg_Core_ccOrbitCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::OrbitCamera, "OrbitCamera", "cc.OrbitCamera",
		cocos2d::OrbitCamera, "cc.ActionCamera",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_OrbitCamera_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_OrbitCamera_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CardinalSplineTo_getPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:getPoints");
	LUA_TRY_INVOKE_R(0, &cocos2d::CardinalSplineTo::getPoints);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CardinalSplineTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cocos2d::CardinalSplineTo::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_CardinalSplineTo_updatePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:updatePosition");
	LUA_TRY_INVOKE(1, &cocos2d::CardinalSplineTo::updatePosition);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccCardinalSplineTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineTo, "CardinalSplineTo", "cc.CardinalSplineTo",
		cocos2d::CardinalSplineTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getPoints", lua_cocos2d_CardinalSplineTo_getPoints);
	LUA_METHOD("initWithDuration", lua_cocos2d_CardinalSplineTo_initWithDuration);
	LUA_METHOD("updatePosition", lua_cocos2d_CardinalSplineTo_updatePosition);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCardinalSplineBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CardinalSplineBy, "CardinalSplineBy", "cc.CardinalSplineBy",
		cocos2d::CardinalSplineBy, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CatmullRomTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CatmullRomTo", "cc.CatmullRomTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::CatmullRomTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccCatmullRomTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CatmullRomTo, "CatmullRomTo", "cc.CatmullRomTo",
		cocos2d::CatmullRomTo, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_CatmullRomTo_initWithDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CatmullRomBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CatmullRomBy", "cc.CatmullRomBy:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::CatmullRomBy::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccCatmullRomBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CatmullRomBy, "CatmullRomBy", "cc.CatmullRomBy",
		cocos2d::CatmullRomBy, "cc.CardinalSplineBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_CatmullRomBy_initWithDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionEase_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionEase::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionEase_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:initWithAction");
	LUA_TRY_INVOKE_R(1, &cocos2d::ActionEase::initWithAction);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionEase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionEase, "ActionEase", "cc.ActionEase",
		cocos2d::ActionEase, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_ActionEase_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_ActionEase_initWithAction);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseRateAction_getRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:getRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::EaseRateAction::getRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EaseRateAction_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:initWithAction");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseRateAction::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EaseRateAction_setRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:setRate");
	LUA_TRY_INVOKE(1, &cocos2d::EaseRateAction::setRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EaseRateAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseRateAction::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseRateAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseRateAction, "EaseRateAction", "cc.EaseRateAction",
		cocos2d::EaseRateAction, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getRate", lua_cocos2d_EaseRateAction_getRate);
	LUA_METHOD("initWithAction", lua_cocos2d_EaseRateAction_initWithAction);
	LUA_METHOD("setRate", lua_cocos2d_EaseRateAction_setRate);
	LUA_METHOD("create", lua_cocos2d_EaseRateAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialIn", "cc.EaseExponentialIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseExponentialIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialIn, "EaseExponentialIn", "cc.EaseExponentialIn",
		cocos2d::EaseExponentialIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialOut", "cc.EaseExponentialOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseExponentialOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialOut, "EaseExponentialOut", "cc.EaseExponentialOut",
		cocos2d::EaseExponentialOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseExponentialInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialInOut", "cc.EaseExponentialInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseExponentialInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseExponentialInOut, "EaseExponentialInOut", "cc.EaseExponentialInOut",
		cocos2d::EaseExponentialInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseExponentialInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineIn", "cc.EaseSineIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseSineIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineIn, "EaseSineIn", "cc.EaseSineIn",
		cocos2d::EaseSineIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineOut", "cc.EaseSineOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseSineOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineOut, "EaseSineOut", "cc.EaseSineOut",
		cocos2d::EaseSineOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseSineInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineInOut", "cc.EaseSineInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseSineInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseSineInOut, "EaseSineInOut", "cc.EaseSineInOut",
		cocos2d::EaseSineInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseSineInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEaseBounce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounce, "EaseBounce", "cc.EaseBounce",
		cocos2d::EaseBounce, "cc.ActionEase",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBounceIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceIn", "cc.EaseBounceIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBounceIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceIn, "EaseBounceIn", "cc.EaseBounceIn",
		cocos2d::EaseBounceIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBounceOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceOut", "cc.EaseBounceOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBounceOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceOut, "EaseBounceOut", "cc.EaseBounceOut",
		cocos2d::EaseBounceOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBounceInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceInOut", "cc.EaseBounceInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBounceInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBounceInOut, "EaseBounceInOut", "cc.EaseBounceInOut",
		cocos2d::EaseBounceInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBounceInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackIn", "cc.EaseBackIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBackIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackIn, "EaseBackIn", "cc.EaseBackIn",
		cocos2d::EaseBackIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackOut", "cc.EaseBackOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBackOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackOut, "EaseBackOut", "cc.EaseBackOut",
		cocos2d::EaseBackOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBackInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackInOut", "cc.EaseBackInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBackInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBackInOut, "EaseBackInOut", "cc.EaseBackInOut",
		cocos2d::EaseBackInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseBackInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionIn", "cc.EaseQuadraticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuadraticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionIn, "EaseQuadraticActionIn", "cc.EaseQuadraticActionIn",
		cocos2d::EaseQuadraticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionOut", "cc.EaseQuadraticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuadraticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionOut, "EaseQuadraticActionOut", "cc.EaseQuadraticActionOut",
		cocos2d::EaseQuadraticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuadraticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuadraticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuadraticActionInOut, "EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut",
		cocos2d::EaseQuadraticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuadraticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionIn", "cc.EaseQuarticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuarticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionIn, "EaseQuarticActionIn", "cc.EaseQuarticActionIn",
		cocos2d::EaseQuarticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionOut", "cc.EaseQuarticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuarticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionOut, "EaseQuarticActionOut", "cc.EaseQuarticActionOut",
		cocos2d::EaseQuarticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuarticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionInOut", "cc.EaseQuarticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuarticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuarticActionInOut, "EaseQuarticActionInOut", "cc.EaseQuarticActionInOut",
		cocos2d::EaseQuarticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuarticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuinticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionIn", "cc.EaseQuinticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuinticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionIn, "EaseQuinticActionIn", "cc.EaseQuinticActionIn",
		cocos2d::EaseQuinticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuinticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionOut", "cc.EaseQuinticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuinticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionOut, "EaseQuinticActionOut", "cc.EaseQuinticActionOut",
		cocos2d::EaseQuinticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseQuinticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionInOut", "cc.EaseQuinticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseQuinticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseQuinticActionInOut, "EaseQuinticActionInOut", "cc.EaseQuinticActionInOut",
		cocos2d::EaseQuinticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseQuinticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionIn", "cc.EaseCircleActionIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCircleActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionIn, "EaseCircleActionIn", "cc.EaseCircleActionIn",
		cocos2d::EaseCircleActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionOut", "cc.EaseCircleActionOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCircleActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionOut, "EaseCircleActionOut", "cc.EaseCircleActionOut",
		cocos2d::EaseCircleActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCircleActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionInOut", "cc.EaseCircleActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCircleActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCircleActionInOut, "EaseCircleActionInOut", "cc.EaseCircleActionInOut",
		cocos2d::EaseCircleActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCircleActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionIn", "cc.EaseCubicActionIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCubicActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionIn, "EaseCubicActionIn", "cc.EaseCubicActionIn",
		cocos2d::EaseCubicActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionOut", "cc.EaseCubicActionOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCubicActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionOut, "EaseCubicActionOut", "cc.EaseCubicActionOut",
		cocos2d::EaseCubicActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseCubicActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionInOut", "cc.EaseCubicActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseCubicActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseCubicActionInOut, "EaseCubicActionInOut", "cc.EaseCubicActionInOut",
		cocos2d::EaseCubicActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseCubicActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseIn", "cc.EaseIn:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseIn::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseIn, "EaseIn", "cc.EaseIn",
		cocos2d::EaseIn, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseOut", "cc.EaseOut:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseOut::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseOut, "EaseOut", "cc.EaseOut",
		cocos2d::EaseOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseInOut", "cc.EaseInOut:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseInOut::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseInOut, "EaseInOut", "cc.EaseInOut",
		cocos2d::EaseInOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElastic_getPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:getPeriod");
	LUA_TRY_INVOKE_R(0, &cocos2d::EaseElastic::getPeriod);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EaseElastic_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:initWithAction");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseElastic::initWithAction);
	LUA_TRY_INVOKE_R(1, ([](cocos2d::EaseElastic* obj,cocos2d::ActionInterval* arg0){{return obj->initWithAction(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EaseElastic_setPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:setPeriod");
	LUA_TRY_INVOKE(1, &cocos2d::EaseElastic::setPeriod);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseElastic(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElastic, "EaseElastic", "cc.EaseElastic",
		cocos2d::EaseElastic, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getPeriod", lua_cocos2d_EaseElastic_getPeriod);
	LUA_METHOD("initWithAction", lua_cocos2d_EaseElastic_initWithAction);
	LUA_METHOD("setPeriod", lua_cocos2d_EaseElastic_setPeriod);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElasticIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticIn", "cc.EaseElasticIn:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseElasticIn::create);
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticIn::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticIn, "EaseElasticIn", "cc.EaseElasticIn",
		cocos2d::EaseElasticIn, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElasticOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticOut", "cc.EaseElasticOut:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseElasticOut::create);
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticOut, "EaseElasticOut", "cc.EaseElasticOut",
		cocos2d::EaseElasticOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseElasticInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticInOut", "cc.EaseElasticInOut:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::EaseElasticInOut::create);
	LUA_TRY_INVOKE_R(1, [](cocos2d::ActionInterval* arg0){{return cocos2d::EaseElasticInOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseElasticInOut, "EaseElasticInOut", "cc.EaseElasticInOut",
		cocos2d::EaseElasticInOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EaseElasticInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EaseBezierAction_setBezierParamer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:setBezierParamer");
	LUA_TRY_INVOKE(4, &cocos2d::EaseBezierAction::setBezierParamer);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_EaseBezierAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::EaseBezierAction::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBezierAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EaseBezierAction, "EaseBezierAction", "cc.EaseBezierAction",
		cocos2d::EaseBezierAction, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("setBezierParamer", lua_cocos2d_EaseBezierAction_setBezierParamer);
	LUA_METHOD("create", lua_cocos2d_EaseBezierAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccActionInstant(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionInstant, "ActionInstant", "cc.ActionInstant",
		cocos2d::ActionInstant, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Show_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Show", "cc.Show:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::Show::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccShow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Show, "Show", "cc.Show",
		cocos2d::Show, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_Show_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Hide_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Hide", "cc.Hide:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::Hide::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccHide(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Hide, "Hide", "cc.Hide",
		cocos2d::Hide, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_Hide_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ToggleVisibility_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ToggleVisibility", "cc.ToggleVisibility:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ToggleVisibility::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccToggleVisibility(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ToggleVisibility, "ToggleVisibility", "cc.ToggleVisibility",
		cocos2d::ToggleVisibility, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ToggleVisibility_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RemoveSelf_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:init");
	LUA_TRY_INVOKE_R(1, &cocos2d::RemoveSelf::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RemoveSelf_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::RemoveSelf::create);
	LUA_TRY_INVOKE_R(0, [](){{return cocos2d::RemoveSelf::create();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccRemoveSelf(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RemoveSelf, "RemoveSelf", "cc.RemoveSelf",
		cocos2d::RemoveSelf, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_RemoveSelf_init);
	LUA_METHOD("create", lua_cocos2d_RemoveSelf_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipX_initWithFlipX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX", "cc.FlipX:initWithFlipX");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipX::initWithFlipX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX", "cc.FlipX:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipX::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipX, "FlipX", "cc.FlipX",
		cocos2d::FlipX, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipX", lua_cocos2d_FlipX_initWithFlipX);
	LUA_METHOD("create", lua_cocos2d_FlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipY_initWithFlipY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipY", "cc.FlipY:initWithFlipY");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipY::initWithFlipY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY", "cc.FlipY:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipY::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipY, "FlipY", "cc.FlipY",
		cocos2d::FlipY, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipY", lua_cocos2d_FlipY_initWithFlipY);
	LUA_METHOD("create", lua_cocos2d_FlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Place_initWithPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Place", "cc.Place:initWithPosition");
	LUA_TRY_INVOKE_R(1, &cocos2d::Place::initWithPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Place_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Place", "cc.Place:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::Place::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccPlace(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Place, "Place", "cc.Place",
		cocos2d::Place, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithPosition", lua_cocos2d_Place_initWithPosition);
	LUA_METHOD("create", lua_cocos2d_Place_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CallFunc_execute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CallFunc", "cc.CallFunc:execute");
	LUA_TRY_INVOKE(0, &cocos2d::CallFunc::execute);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccCallFunc(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CallFunc, "CallFunc", "cc.CallFunc",
		cocos2d::CallFunc, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("execute", lua_cocos2d_CallFunc_execute);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GridAction_getGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:getGrid");
	LUA_TRY_INVOKE_R(0, &cocos2d::GridAction::getGrid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridAction_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::GridAction::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_GridAction_reverse_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:reverse");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::Action>(cocos2d::GridAction::*)()const>(&cocos2d::GridAction::reverse));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGridAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GridAction, "GridAction", "cc.GridAction",
		cocos2d::GridAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getGrid", lua_cocos2d_GridAction_getGrid);
	LUA_METHOD("initWithDuration", lua_cocos2d_GridAction_initWithDuration);
	LUA_METHOD("reverse", lua_cocos2d_GridAction_reverse_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Grid3DAction_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3DAction", "cc.Grid3DAction:getGridRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::Grid3DAction::getGridRect);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Grid3DAction, "Grid3DAction", "cc.Grid3DAction",
		cocos2d::Grid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_METHOD("getGridRect", lua_cocos2d_Grid3DAction_getGridRect);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTiledGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TiledGrid3DAction, "TiledGrid3DAction", "cc.TiledGrid3DAction",
		cocos2d::TiledGrid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_StopGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.StopGrid", "cc.StopGrid:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::StopGrid::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccStopGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::StopGrid, "StopGrid", "cc.StopGrid",
		cocos2d::StopGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_StopGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ReuseGrid_initWithTimes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:initWithTimes");
	LUA_TRY_INVOKE_R(1, &cocos2d::ReuseGrid::initWithTimes);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ReuseGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::ReuseGrid::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccReuseGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ReuseGrid, "ReuseGrid", "cc.ReuseGrid",
		cocos2d::ReuseGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithTimes", lua_cocos2d_ReuseGrid_initWithTimes);
	LUA_METHOD("create", lua_cocos2d_ReuseGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Waves3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cocos2d::Waves3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Waves3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::Waves3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Waves3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cocos2d::Waves3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::Waves3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves3D", "cc.Waves3D:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::Waves3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccWaves3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Waves3D, "Waves3D", "cc.Waves3D",
		cocos2d::Waves3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Waves3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Waves3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Waves3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Waves3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Waves3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Waves3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipX3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithDuration");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipX3D::initWithDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipX3D_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithSize");
	LUA_TRY_INVOKE_R(2, &cocos2d::FlipX3D::initWithSize);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FlipX3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipX3D::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipX3D, "FlipX3D", "cc.FlipX3D",
		cocos2d::FlipX3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_FlipX3D_initWithDuration);
	LUA_METHOD("initWithSize", lua_cocos2d_FlipX3D_initWithSize);
	LUA_METHOD("create", lua_cocos2d_FlipX3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipY3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY3D", "cc.FlipY3D:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FlipY3D::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipY3D, "FlipY3D", "cc.FlipY3D",
		cocos2d::FlipY3D, "cc.FlipX3D",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_FlipY3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Lens3D_getLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getLensEffect");
	LUA_TRY_INVOKE_R(0, &cocos2d::Lens3D::getLensEffect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Lens3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::Lens3D::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Lens3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::Lens3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Lens3D_setConcave(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setConcave");
	LUA_TRY_INVOKE(1, &cocos2d::Lens3D::setConcave);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_setLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setLensEffect");
	LUA_TRY_INVOKE(1, &cocos2d::Lens3D::setLensEffect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setPosition");
	LUA_TRY_INVOKE(1, &cocos2d::Lens3D::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Lens3D", "cc.Lens3D:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::Lens3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLens3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Lens3D, "Lens3D", "cc.Lens3D",
		cocos2d::Lens3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getLensEffect", lua_cocos2d_Lens3D_getLensEffect);
	LUA_METHOD("getPosition", lua_cocos2d_Lens3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Lens3D_initWithDuration);
	LUA_METHOD("setConcave", lua_cocos2d_Lens3D_setConcave);
	LUA_METHOD("setLensEffect", lua_cocos2d_Lens3D_setLensEffect);
	LUA_METHOD("setPosition", lua_cocos2d_Lens3D_setPosition);
	LUA_METHOD("create", lua_cocos2d_Lens3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Ripple3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cocos2d::Ripple3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Ripple3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::Ripple3D::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:initWithDuration");
	LUA_TRY_INVOKE_R(6, &cocos2d::Ripple3D::initWithDuration);
	LUA_INVOKE_FOOTER("6");
}
int lua_cocos2d_Ripple3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cocos2d::Ripple3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::Ripple3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setPosition");
	LUA_TRY_INVOKE(1, &cocos2d::Ripple3D::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:create");
	LUA_TRY_INVOKE_R(6, &cocos2d::Ripple3D::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccRipple3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Ripple3D, "Ripple3D", "cc.Ripple3D",
		cocos2d::Ripple3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Ripple3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Ripple3D_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cocos2d_Ripple3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Ripple3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Ripple3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Ripple3D_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cocos2d_Ripple3D_setPosition);
	LUA_METHOD("create", lua_cocos2d_Ripple3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Shaky3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::Shaky3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Shaky3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::Shaky3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShaky3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Shaky3D, "Shaky3D", "cc.Shaky3D",
		cocos2d::Shaky3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_Shaky3D_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_Shaky3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Liquid_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cocos2d::Liquid::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Liquid_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Liquid::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Liquid_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::Liquid::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Liquid_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitude");
	LUA_TRY_INVOKE(1, &cocos2d::Liquid::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Liquid_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::Liquid::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Liquid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Liquid", "cc.Liquid:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::Liquid::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLiquid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Liquid, "Liquid", "cc.Liquid",
		cocos2d::Liquid, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Liquid_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Liquid_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Liquid_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Liquid_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Liquid_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Liquid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Waves_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cocos2d::Waves::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Waves::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:initWithDuration");
	LUA_TRY_INVOKE_R(6, &cocos2d::Waves::initWithDuration);
	LUA_INVOKE_FOOTER("6");
}
int lua_cocos2d_Waves_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitude");
	LUA_TRY_INVOKE(1, &cocos2d::Waves::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::Waves::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves", "cc.Waves:create");
	LUA_TRY_INVOKE_R(6, &cocos2d::Waves::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccWaves(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Waves, "Waves", "cc.Waves",
		cocos2d::Waves, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Waves_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Waves_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Waves_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Waves_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Waves_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Waves_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Twirl_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cocos2d::Twirl::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Twirl::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::Twirl::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Twirl_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:initWithDuration");
	LUA_TRY_INVOKE_R(5, &cocos2d::Twirl::initWithDuration);
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_Twirl_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitude");
	LUA_TRY_INVOKE(1, &cocos2d::Twirl::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Twirl_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::Twirl::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Twirl_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setPosition");
	LUA_TRY_INVOKE(1, &cocos2d::Twirl::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Twirl_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Twirl", "cc.Twirl:create");
	LUA_TRY_INVOKE_R(5, &cocos2d::Twirl::create);
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccTwirl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Twirl, "Twirl", "cc.Twirl",
		cocos2d::Twirl, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Twirl_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Twirl_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cocos2d_Twirl_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Twirl_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Twirl_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Twirl_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cocos2d_Twirl_setPosition);
	LUA_METHOD("create", lua_cocos2d_Twirl_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
