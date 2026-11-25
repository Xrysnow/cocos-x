#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/ProtectedNode.h"
#include "base/AsyncTaskPool.h"
#include "scripting/lua-bindings/manual/ComponentLua.h"
#include "renderer/Renderer.h"
#include "renderer/PipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/Physics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/NavMesh.h"
#endif

int lua_cc_FileUtils_addSearchPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:addSearchPath");
	LUA_TRY_INVOKE(2, &cc::FileUtils::addSearchPath);
	LUA_TRY_INVOKE(1, ([](cc::FileUtils* obj,std::string_view arg0){{return obj->addSearchPath(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_createDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:createDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::createDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::createDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_ensureAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:ensureAppDirectory");
	LUA_TRY_INVOKE_R(2, &cc::FileUtils::ensureAppDirectory);
	LUA_TRY_INVOKE_R(1, ([](const cc::FileUtils* obj,cc::AppDirectory arg0){{return obj->ensureAppDirectory(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_fullPathForFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathForFilename");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::fullPathForFilename);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_fullPathForDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathForDirectory");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::fullPathForDirectory);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_fullPathFromRelativeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathFromRelativeFile");
	LUA_TRY_INVOKE_R(2, &cc::FileUtils::fullPathFromRelativeFile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FileUtils_getDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getDefaultResourceRootPath");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getDefaultResourceRootPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getFileExtension(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileExtension");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::getFileExtension);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getFileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileSize");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(int64_t)>)const>(&cc::FileUtils::getFileSize)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::getFileSize));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_getNativeWritableAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getNativeWritableAbsolutePath");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getNativeWritableAbsolutePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getOriginalSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getOriginalSearchPaths");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getOriginalSearchPaths);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getPersistentDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getPersistentDataPath");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getPersistentDataPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSearchPaths");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getSearchPaths);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getStringFromFile_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getStringFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::getStringFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getSuitableFOpen(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSuitableFOpen");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::getSuitableFOpen);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getTransientDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getTransientDataPath");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getTransientDataPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_getValueMapFromData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromData");
	LUA_TRY_INVOKE_R(2, &cc::FileUtils::getValueMapFromData);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FileUtils_getValueMapFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromFile");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::getValueMapFromFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getValueVectorFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueVectorFromFile");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::getValueVectorFromFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getWritablePath");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getWritablePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_isAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePath");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::isAbsolutePath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_isDirectoryExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::isDirectoryExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::isDirectoryExist));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_isDirectoryExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExistInternal");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::isDirectoryExistInternal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_isFileExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::isFileExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::isFileExist));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_isFileExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExistInternal");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::isFileExistInternal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_isPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isPopupNotify");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::isPopupNotify);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_listFiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFiles");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::listFiles);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_listFilesAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesAsync");
	LUA_TRY_INVOKE(2, &cc::FileUtils::listFilesAsync);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FileUtils_listFilesRecursivelyAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesRecursivelyAsync");
	LUA_TRY_INVOKE(2, &cc::FileUtils::listFilesRecursivelyAsync);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FileUtils_purgeCachedEntries(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:purgeCachedEntries");
	LUA_TRY_INVOKE(0, &cc::FileUtils::purgeCachedEntries);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FileUtils_queryAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:queryAppDirectory");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::queryAppDirectory);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_removeDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::removeDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::removeDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_removeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeFile");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::removeFile)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::FileUtils::*)(std::string_view)const>(&cc::FileUtils::removeFile));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_FileUtils_renameFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:renameFile");
	LUA_TRY_INVOKE(4, (static_cast<void(cc::FileUtils::*)(std::string_view, std::string_view, std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::renameFile)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cc::FileUtils::*)(std::string_view, std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cc::FileUtils::*)(std::string_view, std::string_view, std::string_view)const>(&cc::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::FileUtils::*)(std::string_view, std::string_view)const>(&cc::FileUtils::renameFile)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cc_FileUtils_setDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setDefaultResourceRootPath");
	LUA_TRY_INVOKE(1, &cc::FileUtils::setDefaultResourceRootPath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_setPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setPopupNotify");
	LUA_TRY_INVOKE(1, &cc::FileUtils::setPopupNotify);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_setSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setSearchPaths");
	LUA_TRY_INVOKE(1, &cc::FileUtils::setSearchPaths);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_setWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setWritablePath");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::setWritablePath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FileUtils_writeStringToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeStringToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::FileUtils::*)(std::string, std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::writeStringToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::FileUtils::*)(std::string_view, std::string_view)const>(&cc::FileUtils::writeStringToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_FileUtils_writeToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeToFile");
	LUA_TRY_INVOKE_R(2, &cc::FileUtils::writeToFile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FileUtils_writeValueMapToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueMapToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::FileUtils::*)(cc::ValueMap, std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::writeValueMapToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::FileUtils::*)(const cc::ValueMap&, std::string_view)const>(&cc::FileUtils::writeValueMapToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_FileUtils_writeValueVectorToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueVectorToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::FileUtils::*)(cc::ValueVector, std::string_view, std::function<void(bool)>)const>(&cc::FileUtils::writeValueVectorToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::FileUtils::*)(const cc::ValueVector&, std::string_view)const>(&cc::FileUtils::writeValueVectorToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_FileUtils_getFileShortName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileShortName");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::getFileShortName);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_FileUtils_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::FileUtils::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_FileUtils_isAbsolutePathInternal(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePathInternal");
	LUA_TRY_INVOKE_R(1, &cc::FileUtils::isAbsolutePathInternal);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFileUtils(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FileUtils, "FileUtils", "cc.FileUtils",
		cc::FileUtils, "",
		nullptr, nullptr);
	LUA_METHOD("addSearchPath", lua_cc_FileUtils_addSearchPath);
	LUA_METHOD("createDirectory", lua_cc_FileUtils_createDirectory);
	LUA_METHOD("ensureAppDirectory", lua_cc_FileUtils_ensureAppDirectory);
	LUA_METHOD("fullPathForFilename", lua_cc_FileUtils_fullPathForFilename);
	LUA_METHOD("fullPathForDirectory", lua_cc_FileUtils_fullPathForDirectory);
	LUA_METHOD("fullPathFromRelativeFile", lua_cc_FileUtils_fullPathFromRelativeFile);
	LUA_METHOD("getDefaultResourceRootPath", lua_cc_FileUtils_getDefaultResourceRootPath);
	LUA_METHOD("getFileExtension", lua_cc_FileUtils_getFileExtension);
	LUA_METHOD("getFileSize", lua_cc_FileUtils_getFileSize);
	LUA_METHOD("getNativeWritableAbsolutePath", lua_cc_FileUtils_getNativeWritableAbsolutePath);
	LUA_METHOD("getOriginalSearchPaths", lua_cc_FileUtils_getOriginalSearchPaths);
	LUA_METHOD("getPersistentDataPath", lua_cc_FileUtils_getPersistentDataPath);
	LUA_METHOD("getSearchPaths", lua_cc_FileUtils_getSearchPaths);
	LUA_METHOD("getStringFromFile", lua_cc_FileUtils_getStringFromFile_1);
	LUA_METHOD("getSuitableFOpen", lua_cc_FileUtils_getSuitableFOpen);
	LUA_METHOD("getTransientDataPath", lua_cc_FileUtils_getTransientDataPath);
	LUA_METHOD("getValueMapFromData", lua_cc_FileUtils_getValueMapFromData);
	LUA_METHOD("getValueMapFromFile", lua_cc_FileUtils_getValueMapFromFile);
	LUA_METHOD("getValueVectorFromFile", lua_cc_FileUtils_getValueVectorFromFile);
	LUA_METHOD("getWritablePath", lua_cc_FileUtils_getWritablePath);
	LUA_METHOD("isAbsolutePath", lua_cc_FileUtils_isAbsolutePath);
	LUA_METHOD("isDirectoryExist", lua_cc_FileUtils_isDirectoryExist);
	LUA_METHOD("isDirectoryExistInternal", lua_cc_FileUtils_isDirectoryExistInternal);
	LUA_METHOD("isFileExist", lua_cc_FileUtils_isFileExist);
	LUA_METHOD("isFileExistInternal", lua_cc_FileUtils_isFileExistInternal);
	LUA_METHOD("isPopupNotify", lua_cc_FileUtils_isPopupNotify);
	LUA_METHOD("listFiles", lua_cc_FileUtils_listFiles);
	LUA_METHOD("listFilesAsync", lua_cc_FileUtils_listFilesAsync);
	LUA_METHOD("listFilesRecursivelyAsync", lua_cc_FileUtils_listFilesRecursivelyAsync);
	LUA_METHOD("purgeCachedEntries", lua_cc_FileUtils_purgeCachedEntries);
	LUA_METHOD("queryAppDirectory", lua_cc_FileUtils_queryAppDirectory);
	LUA_METHOD("removeDirectory", lua_cc_FileUtils_removeDirectory);
	LUA_METHOD("removeFile", lua_cc_FileUtils_removeFile);
	LUA_METHOD("renameFile", lua_cc_FileUtils_renameFile);
	LUA_METHOD("setDefaultResourceRootPath", lua_cc_FileUtils_setDefaultResourceRootPath);
	LUA_METHOD("setPopupNotify", lua_cc_FileUtils_setPopupNotify);
	LUA_METHOD("setSearchPaths", lua_cc_FileUtils_setSearchPaths);
	LUA_METHOD("setWritablePath", lua_cc_FileUtils_setWritablePath);
	LUA_METHOD("writeStringToFile", lua_cc_FileUtils_writeStringToFile);
	LUA_METHOD("writeToFile", lua_cc_FileUtils_writeToFile);
	LUA_METHOD("writeValueMapToFile", lua_cc_FileUtils_writeValueMapToFile);
	LUA_METHOD("writeValueVectorToFile", lua_cc_FileUtils_writeValueVectorToFile);
	LUA_METHOD("getFileShortName", lua_cc_FileUtils_getFileShortName);
	LUA_METHOD("getInstance", lua_cc_FileUtils_getInstance);
	LUA_METHOD("isAbsolutePathInternal", lua_cc_FileUtils_isAbsolutePathInternal);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventAcceleration, "EventAcceleration", "cc.EventAcceleration",
		cc::EventAcceleration, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventCustom_getEventName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventCustom", "cc.EventCustom:getEventName");
	LUA_TRY_INVOKE_R(0, &cc::EventCustom::getEventName);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventCustom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventCustom, "EventCustom", "cc.EventCustom",
		cc::EventCustom, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventName", lua_cc_EventCustom_getEventName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventDispatcher_addCustomEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addCustomEventListener");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, &cc::EventDispatcher::addCustomEventListener);
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_EventDispatcher_addEventListenerWithFixedPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithFixedPriority");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::addEventListenerWithFixedPriority);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_EventDispatcher_addEventListenerWithSceneGraphPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::addEventListenerWithSceneGraphPriority);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_EventDispatcher_dispatchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:dispatchEvent");
	LUA_TRY_INVOKE(1, &cc::EventDispatcher::dispatchEvent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_hasEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:hasEventListener");
	LUA_TRY_INVOKE_R(1, &cc::EventDispatcher::hasEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::EventDispatcher::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventDispatcher_pauseEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:pauseEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::pauseEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cc::EventDispatcher* obj,cc::Node* arg0){{return obj->pauseEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_EventDispatcher_removeAllEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeAllEventListeners");
	LUA_TRY_INVOKE(0, &cc::EventDispatcher::removeAllEventListeners);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventDispatcher_removeCustomEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeCustomEventListeners");
	LUA_TRY_INVOKE(1, &cc::EventDispatcher::removeCustomEventListeners);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_removeEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListener");
	LUA_TRY_INVOKE(1, &cc::EventDispatcher::removeEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_removeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::removeEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cc::EventDispatcher* obj,cc::Node* arg0){{return obj->removeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_EventDispatcher_removeEventListenersForType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForType");
	LUA_TRY_INVOKE(1, &cc::EventDispatcher::removeEventListenersForType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_resumeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:resumeEventListenersForTarget");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::resumeEventListenersForTarget);
	LUA_TRY_INVOKE(1, ([](cc::EventDispatcher* obj,cc::Node* arg0){{return obj->resumeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_EventDispatcher_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setEnabled");
	LUA_TRY_INVOKE(1, &cc::EventDispatcher::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventDispatcher_setPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setPriority");
	LUA_TRY_INVOKE(2, &cc::EventDispatcher::setPriority);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventDispatcher(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventDispatcher, "EventDispatcher", "cc.EventDispatcher",
		cc::EventDispatcher, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addCustomEventListener", lua_cc_EventDispatcher_addCustomEventListener);
	LUA_METHOD("addEventListenerWithFixedPriority", lua_cc_EventDispatcher_addEventListenerWithFixedPriority);
	LUA_METHOD("addEventListenerWithSceneGraphPriority", lua_cc_EventDispatcher_addEventListenerWithSceneGraphPriority);
	LUA_METHOD("dispatchEvent", lua_cc_EventDispatcher_dispatchEvent);
	LUA_METHOD("hasEventListener", lua_cc_EventDispatcher_hasEventListener);
	LUA_METHOD("isEnabled", lua_cc_EventDispatcher_isEnabled);
	LUA_METHOD("pauseEventListenersForTarget", lua_cc_EventDispatcher_pauseEventListenersForTarget);
	LUA_METHOD("removeAllEventListeners", lua_cc_EventDispatcher_removeAllEventListeners);
	LUA_METHOD("removeCustomEventListeners", lua_cc_EventDispatcher_removeCustomEventListeners);
	LUA_METHOD("removeEventListener", lua_cc_EventDispatcher_removeEventListener);
	LUA_METHOD("removeEventListenersForTarget", lua_cc_EventDispatcher_removeEventListenersForTarget);
	LUA_METHOD("removeEventListenersForType", lua_cc_EventDispatcher_removeEventListenersForType);
	LUA_METHOD("resumeEventListenersForTarget", lua_cc_EventDispatcher_resumeEventListenersForTarget);
	LUA_METHOD("setEnabled", lua_cc_EventDispatcher_setEnabled);
	LUA_METHOD("setPriority", lua_cc_EventDispatcher_setPriority);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventFocus, "EventFocus", "cc.EventFocus",
		cc::EventFocus, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerAcceleration_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerAcceleration", "cc.EventListenerAcceleration:init");
	LUA_TRY_INVOKE_R(1, &cc::EventListenerAcceleration::init);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerAcceleration, "EventListenerAcceleration", "cc.EventListenerAcceleration",
		cc::EventListenerAcceleration, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_EventListenerAcceleration_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerFocus_clone_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListener>(cc::EventListenerFocus::*)()>(&cc::EventListenerFocus::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerFocus_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:init");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerFocus::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerFocus_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListenerFocus>(*)()>(&cc::EventListenerFocus::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerFocus, "EventListenerFocus", "cc.EventListenerFocus",
		cc::EventListenerFocus, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cc_EventListenerFocus_clone_1);
	LUA_METHOD("init", lua_cc_EventListenerFocus_init);
	LUA_METHOD("create", lua_cc_EventListenerFocus_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerKeyboard_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerKeyboard", "cc.EventListenerKeyboard:init");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerKeyboard::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerKeyboard_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerKeyboard", "cc.EventListenerKeyboard:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListenerKeyboard>(*)()>(&cc::EventListenerKeyboard::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerKeyboard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerKeyboard, "EventListenerKeyboard", "cc.EventListenerKeyboard",
		cc::EventListenerKeyboard, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_EventListenerKeyboard_init);
	LUA_METHOD("create", lua_cc_EventListenerKeyboard_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventMouse_getCursorX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorX");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getCursorX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getCursorY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getCursorY");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getCursorY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getDelta");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getDelta);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocation");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getMouseButton");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getMouseButton);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getPreviousLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocation");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getPreviousLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getPreviousLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getPreviousLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getPreviousLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getScrollX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollX");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getScrollX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getScrollY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getScrollY");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getScrollY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getStartLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocation");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getStartLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_getStartLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:getStartLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::EventMouse::getStartLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventMouse_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setCursorPosition");
	LUA_TRY_INVOKE(2, &cc::EventMouse::setCursorPosition);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_EventMouse_setMouseButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setMouseButton");
	LUA_TRY_INVOKE(1, &cc::EventMouse::setMouseButton);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventMouse_setScrollData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventMouse", "cc.EventMouse:setScrollData");
	LUA_TRY_INVOKE(2, &cc::EventMouse::setScrollData);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventMouse, "EventMouse", "cc.EventMouse",
		cc::EventMouse, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getCursorX", lua_cc_EventMouse_getCursorX);
	LUA_METHOD("getCursorY", lua_cc_EventMouse_getCursorY);
	LUA_METHOD("getDelta", lua_cc_EventMouse_getDelta);
	LUA_METHOD("getLocation", lua_cc_EventMouse_getLocation);
	LUA_METHOD("getLocationInView", lua_cc_EventMouse_getLocationInView);
	LUA_METHOD("getMouseButton", lua_cc_EventMouse_getMouseButton);
	LUA_METHOD("getPreviousLocation", lua_cc_EventMouse_getPreviousLocation);
	LUA_METHOD("getPreviousLocationInView", lua_cc_EventMouse_getPreviousLocationInView);
	LUA_METHOD("getScrollX", lua_cc_EventMouse_getScrollX);
	LUA_METHOD("getScrollY", lua_cc_EventMouse_getScrollY);
	LUA_METHOD("getStartLocation", lua_cc_EventMouse_getStartLocation);
	LUA_METHOD("getStartLocationInView", lua_cc_EventMouse_getStartLocationInView);
	LUA_METHOD("setCursorPosition", lua_cc_EventMouse_setCursorPosition);
	LUA_METHOD("setMouseButton", lua_cc_EventMouse_setMouseButton);
	LUA_METHOD("setScrollData", lua_cc_EventMouse_setScrollData);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerMouse_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerMouse", "cc.EventListenerMouse:init");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerMouse::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerMouse_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerMouse", "cc.EventListenerMouse:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListenerMouse>(*)()>(&cc::EventListenerMouse::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerMouse(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerMouse, "EventListenerMouse", "cc.EventListenerMouse",
		cc::EventListenerMouse, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_EventListenerMouse_init);
	LUA_METHOD("create", lua_cc_EventListenerMouse_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerTouchOneByOne_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:init");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerTouchOneByOne::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerTouchOneByOne_isSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:isSwallowTouches");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerTouchOneByOne::isSwallowTouches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerTouchOneByOne_setSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:setSwallowTouches");
	LUA_TRY_INVOKE(1, &cc::EventListenerTouchOneByOne::setSwallowTouches);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EventListenerTouchOneByOne_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListenerTouchOneByOne>(*)()>(&cc::EventListenerTouchOneByOne::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerTouchOneByOne(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerTouchOneByOne, "EventListenerTouchOneByOne", "cc.EventListenerTouchOneByOne",
		cc::EventListenerTouchOneByOne, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_EventListenerTouchOneByOne_init);
	LUA_METHOD("isSwallowTouches", lua_cc_EventListenerTouchOneByOne_isSwallowTouches);
	LUA_METHOD("setSwallowTouches", lua_cc_EventListenerTouchOneByOne_setSwallowTouches);
	LUA_METHOD("create", lua_cc_EventListenerTouchOneByOne_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerTouchAllAtOnce_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce:init");
	LUA_TRY_INVOKE_R(0, &cc::EventListenerTouchAllAtOnce::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListenerTouchAllAtOnce_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::EventListenerTouchAllAtOnce>(*)()>(&cc::EventListenerTouchAllAtOnce::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerTouchAllAtOnce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerTouchAllAtOnce, "EventListenerTouchAllAtOnce", "cc.EventListenerTouchAllAtOnce",
		cc::EventListenerTouchAllAtOnce, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_EventListenerTouchAllAtOnce_init);
	LUA_METHOD("create", lua_cc_EventListenerTouchAllAtOnce_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionCamera_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getCenter");
	LUA_TRY_INVOKE_R(0, &cc::ActionCamera::getCenter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionCamera_getEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getEye");
	LUA_TRY_INVOKE_R(0, &cc::ActionCamera::getEye);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionCamera_getUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:getUp");
	LUA_TRY_INVOKE_R(0, &cc::ActionCamera::getUp);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionCamera_reverse_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:reverse");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Action>(cc::ActionCamera::*)()const>(&cc::ActionCamera::reverse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionCamera_setCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setCenter");
	LUA_TRY_INVOKE(1, &cc::ActionCamera::setCenter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionCamera_setEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setEye");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::ActionCamera::*)(float, float, float)>(&cc::ActionCamera::setEye)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::ActionCamera::*)(const cc::Vec3&)>(&cc::ActionCamera::setEye));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cc_ActionCamera_setUp(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionCamera", "cc.ActionCamera:setUp");
	LUA_TRY_INVOKE(1, &cc::ActionCamera::setUp);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionCamera, "ActionCamera", "cc.ActionCamera",
		cc::ActionCamera, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getCenter", lua_cc_ActionCamera_getCenter);
	LUA_METHOD("getEye", lua_cc_ActionCamera_getEye);
	LUA_METHOD("getUp", lua_cc_ActionCamera_getUp);
	LUA_METHOD("reverse", lua_cc_ActionCamera_reverse_1);
	LUA_METHOD("setCenter", lua_cc_ActionCamera_setCenter);
	LUA_METHOD("setEye", lua_cc_ActionCamera_setEye);
	LUA_METHOD("setUp", lua_cc_ActionCamera_setUp);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_OrbitCamera_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:initWithDuration");
	LUA_TRY_INVOKE_R(7, &cc::OrbitCamera::initWithDuration);
	LUA_INVOKE_FOOTER("7");
}
int lua_cc_OrbitCamera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OrbitCamera", "cc.OrbitCamera:create");
	LUA_TRY_INVOKE_R(7, &cc::OrbitCamera::create);
	LUA_SINVOKE_FOOTER("7");
}
int luaReg_Core_ccOrbitCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::OrbitCamera, "OrbitCamera", "cc.OrbitCamera",
		cc::OrbitCamera, "cc.ActionCamera",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_OrbitCamera_initWithDuration);
	LUA_METHOD("create", lua_cc_OrbitCamera_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CardinalSplineTo_getPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:getPoints");
	LUA_TRY_INVOKE_R(0, &cc::CardinalSplineTo::getPoints);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CardinalSplineTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::CardinalSplineTo::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_CardinalSplineTo_updatePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CardinalSplineTo", "cc.CardinalSplineTo:updatePosition");
	LUA_TRY_INVOKE(1, &cc::CardinalSplineTo::updatePosition);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccCardinalSplineTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CardinalSplineTo, "CardinalSplineTo", "cc.CardinalSplineTo",
		cc::CardinalSplineTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getPoints", lua_cc_CardinalSplineTo_getPoints);
	LUA_METHOD("initWithDuration", lua_cc_CardinalSplineTo_initWithDuration);
	LUA_METHOD("updatePosition", lua_cc_CardinalSplineTo_updatePosition);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccCardinalSplineBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CardinalSplineBy, "CardinalSplineBy", "cc.CardinalSplineBy",
		cc::CardinalSplineBy, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CatmullRomTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CatmullRomTo", "cc.CatmullRomTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::CatmullRomTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccCatmullRomTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CatmullRomTo, "CatmullRomTo", "cc.CatmullRomTo",
		cc::CatmullRomTo, "cc.CardinalSplineTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_CatmullRomTo_initWithDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CatmullRomBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CatmullRomBy", "cc.CatmullRomBy:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::CatmullRomBy::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccCatmullRomBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CatmullRomBy, "CatmullRomBy", "cc.CatmullRomBy",
		cc::CatmullRomBy, "cc.CardinalSplineBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_CatmullRomBy_initWithDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionEase_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cc::ActionEase::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionEase_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionEase", "cc.ActionEase:initWithAction");
	LUA_TRY_INVOKE_R(1, &cc::ActionEase::initWithAction);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionEase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionEase, "ActionEase", "cc.ActionEase",
		cc::ActionEase, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cc_ActionEase_getInnerAction);
	LUA_METHOD("initWithAction", lua_cc_ActionEase_initWithAction);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseRateAction_getRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:getRate");
	LUA_TRY_INVOKE_R(0, &cc::EaseRateAction::getRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EaseRateAction_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:initWithAction");
	LUA_TRY_INVOKE_R(2, &cc::EaseRateAction::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_EaseRateAction_setRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:setRate");
	LUA_TRY_INVOKE(1, &cc::EaseRateAction::setRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_EaseRateAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseRateAction", "cc.EaseRateAction:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseRateAction::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseRateAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseRateAction, "EaseRateAction", "cc.EaseRateAction",
		cc::EaseRateAction, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getRate", lua_cc_EaseRateAction_getRate);
	LUA_METHOD("initWithAction", lua_cc_EaseRateAction_initWithAction);
	LUA_METHOD("setRate", lua_cc_EaseRateAction_setRate);
	LUA_METHOD("create", lua_cc_EaseRateAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseExponentialIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialIn", "cc.EaseExponentialIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseExponentialIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseExponentialIn, "EaseExponentialIn", "cc.EaseExponentialIn",
		cc::EaseExponentialIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseExponentialIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseExponentialOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialOut", "cc.EaseExponentialOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseExponentialOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseExponentialOut, "EaseExponentialOut", "cc.EaseExponentialOut",
		cc::EaseExponentialOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseExponentialOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseExponentialInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseExponentialInOut", "cc.EaseExponentialInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseExponentialInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseExponentialInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseExponentialInOut, "EaseExponentialInOut", "cc.EaseExponentialInOut",
		cc::EaseExponentialInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseExponentialInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseSineIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineIn", "cc.EaseSineIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseSineIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseSineIn, "EaseSineIn", "cc.EaseSineIn",
		cc::EaseSineIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseSineIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseSineOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineOut", "cc.EaseSineOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseSineOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseSineOut, "EaseSineOut", "cc.EaseSineOut",
		cc::EaseSineOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseSineOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseSineInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseSineInOut", "cc.EaseSineInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseSineInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseSineInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseSineInOut, "EaseSineInOut", "cc.EaseSineInOut",
		cc::EaseSineInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseSineInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEaseBounce(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBounce, "EaseBounce", "cc.EaseBounce",
		cc::EaseBounce, "cc.ActionEase",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBounceIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceIn", "cc.EaseBounceIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBounceIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBounceIn, "EaseBounceIn", "cc.EaseBounceIn",
		cc::EaseBounceIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBounceIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBounceOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceOut", "cc.EaseBounceOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBounceOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBounceOut, "EaseBounceOut", "cc.EaseBounceOut",
		cc::EaseBounceOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBounceOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBounceInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBounceInOut", "cc.EaseBounceInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBounceInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBounceInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBounceInOut, "EaseBounceInOut", "cc.EaseBounceInOut",
		cc::EaseBounceInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBounceInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBackIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackIn", "cc.EaseBackIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBackIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBackIn, "EaseBackIn", "cc.EaseBackIn",
		cc::EaseBackIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBackIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBackOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackOut", "cc.EaseBackOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBackOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBackOut, "EaseBackOut", "cc.EaseBackOut",
		cc::EaseBackOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBackOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBackInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBackInOut", "cc.EaseBackInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBackInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBackInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBackInOut, "EaseBackInOut", "cc.EaseBackInOut",
		cc::EaseBackInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseBackInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuadraticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionIn", "cc.EaseQuadraticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuadraticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuadraticActionIn, "EaseQuadraticActionIn", "cc.EaseQuadraticActionIn",
		cc::EaseQuadraticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuadraticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuadraticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionOut", "cc.EaseQuadraticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuadraticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuadraticActionOut, "EaseQuadraticActionOut", "cc.EaseQuadraticActionOut",
		cc::EaseQuadraticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuadraticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuadraticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuadraticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuadraticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuadraticActionInOut, "EaseQuadraticActionInOut", "cc.EaseQuadraticActionInOut",
		cc::EaseQuadraticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuadraticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuarticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionIn", "cc.EaseQuarticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuarticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuarticActionIn, "EaseQuarticActionIn", "cc.EaseQuarticActionIn",
		cc::EaseQuarticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuarticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuarticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionOut", "cc.EaseQuarticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuarticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuarticActionOut, "EaseQuarticActionOut", "cc.EaseQuarticActionOut",
		cc::EaseQuarticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuarticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuarticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuarticActionInOut", "cc.EaseQuarticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuarticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuarticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuarticActionInOut, "EaseQuarticActionInOut", "cc.EaseQuarticActionInOut",
		cc::EaseQuarticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuarticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuinticActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionIn", "cc.EaseQuinticActionIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuinticActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuinticActionIn, "EaseQuinticActionIn", "cc.EaseQuinticActionIn",
		cc::EaseQuinticActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuinticActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuinticActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionOut", "cc.EaseQuinticActionOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuinticActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuinticActionOut, "EaseQuinticActionOut", "cc.EaseQuinticActionOut",
		cc::EaseQuinticActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuinticActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseQuinticActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseQuinticActionInOut", "cc.EaseQuinticActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseQuinticActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseQuinticActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseQuinticActionInOut, "EaseQuinticActionInOut", "cc.EaseQuinticActionInOut",
		cc::EaseQuinticActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseQuinticActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCircleActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionIn", "cc.EaseCircleActionIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCircleActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCircleActionIn, "EaseCircleActionIn", "cc.EaseCircleActionIn",
		cc::EaseCircleActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCircleActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCircleActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionOut", "cc.EaseCircleActionOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCircleActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCircleActionOut, "EaseCircleActionOut", "cc.EaseCircleActionOut",
		cc::EaseCircleActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCircleActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCircleActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCircleActionInOut", "cc.EaseCircleActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCircleActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCircleActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCircleActionInOut, "EaseCircleActionInOut", "cc.EaseCircleActionInOut",
		cc::EaseCircleActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCircleActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCubicActionIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionIn", "cc.EaseCubicActionIn:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCubicActionIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCubicActionIn, "EaseCubicActionIn", "cc.EaseCubicActionIn",
		cc::EaseCubicActionIn, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCubicActionIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCubicActionOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionOut", "cc.EaseCubicActionOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCubicActionOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCubicActionOut, "EaseCubicActionOut", "cc.EaseCubicActionOut",
		cc::EaseCubicActionOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCubicActionOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseCubicActionInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseCubicActionInOut", "cc.EaseCubicActionInOut:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseCubicActionInOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseCubicActionInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseCubicActionInOut, "EaseCubicActionInOut", "cc.EaseCubicActionInOut",
		cc::EaseCubicActionInOut, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseCubicActionInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseIn", "cc.EaseIn:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseIn::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseIn, "EaseIn", "cc.EaseIn",
		cc::EaseIn, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseOut", "cc.EaseOut:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseOut::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseOut, "EaseOut", "cc.EaseOut",
		cc::EaseOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseInOut", "cc.EaseInOut:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseInOut::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEaseInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseInOut, "EaseInOut", "cc.EaseInOut",
		cc::EaseInOut, "cc.EaseRateAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseElastic_getPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:getPeriod");
	LUA_TRY_INVOKE_R(0, &cc::EaseElastic::getPeriod);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EaseElastic_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:initWithAction");
	LUA_TRY_INVOKE_R(2, &cc::EaseElastic::initWithAction);
	LUA_TRY_INVOKE_R(1, ([](cc::EaseElastic* obj,cc::ActionInterval* arg0){{return obj->initWithAction(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_EaseElastic_setPeriod(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseElastic", "cc.EaseElastic:setPeriod");
	LUA_TRY_INVOKE(1, &cc::EaseElastic::setPeriod);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseElastic(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseElastic, "EaseElastic", "cc.EaseElastic",
		cc::EaseElastic, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("getPeriod", lua_cc_EaseElastic_getPeriod);
	LUA_METHOD("initWithAction", lua_cc_EaseElastic_initWithAction);
	LUA_METHOD("setPeriod", lua_cc_EaseElastic_setPeriod);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseElasticIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticIn", "cc.EaseElasticIn:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseElasticIn::create);
	LUA_TRY_INVOKE_R(1, [](cc::ActionInterval* arg0){{return cc::EaseElasticIn::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseElasticIn, "EaseElasticIn", "cc.EaseElasticIn",
		cc::EaseElasticIn, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseElasticIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseElasticOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticOut", "cc.EaseElasticOut:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseElasticOut::create);
	LUA_TRY_INVOKE_R(1, [](cc::ActionInterval* arg0){{return cc::EaseElasticOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseElasticOut, "EaseElasticOut", "cc.EaseElasticOut",
		cc::EaseElasticOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseElasticOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseElasticInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseElasticInOut", "cc.EaseElasticInOut:create");
	LUA_TRY_INVOKE_R(2, &cc::EaseElasticInOut::create);
	LUA_TRY_INVOKE_R(1, [](cc::ActionInterval* arg0){{return cc::EaseElasticInOut::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccEaseElasticInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseElasticInOut, "EaseElasticInOut", "cc.EaseElasticInOut",
		cc::EaseElasticInOut, "cc.EaseElastic",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EaseElasticInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EaseBezierAction_setBezierParamer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:setBezierParamer");
	LUA_TRY_INVOKE(4, &cc::EaseBezierAction::setBezierParamer);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_EaseBezierAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EaseBezierAction", "cc.EaseBezierAction:create");
	LUA_TRY_INVOKE_R(1, &cc::EaseBezierAction::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccEaseBezierAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EaseBezierAction, "EaseBezierAction", "cc.EaseBezierAction",
		cc::EaseBezierAction, "cc.ActionEase",
		nullptr, nullptr);
	LUA_METHOD("setBezierParamer", lua_cc_EaseBezierAction_setBezierParamer);
	LUA_METHOD("create", lua_cc_EaseBezierAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccActionInstant(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionInstant, "ActionInstant", "cc.ActionInstant",
		cc::ActionInstant, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Show_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Show", "cc.Show:create");
	LUA_TRY_INVOKE_R(0, &cc::Show::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccShow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Show, "Show", "cc.Show",
		cc::Show, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_Show_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Hide_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Hide", "cc.Hide:create");
	LUA_TRY_INVOKE_R(0, &cc::Hide::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccHide(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Hide, "Hide", "cc.Hide",
		cc::Hide, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_Hide_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ToggleVisibility_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ToggleVisibility", "cc.ToggleVisibility:create");
	LUA_TRY_INVOKE_R(0, &cc::ToggleVisibility::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccToggleVisibility(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ToggleVisibility, "ToggleVisibility", "cc.ToggleVisibility",
		cc::ToggleVisibility, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_ToggleVisibility_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_RemoveSelf_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:init");
	LUA_TRY_INVOKE_R(1, &cc::RemoveSelf::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RemoveSelf_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RemoveSelf", "cc.RemoveSelf:create");
	LUA_TRY_INVOKE_R(1, &cc::RemoveSelf::create);
	LUA_TRY_INVOKE_R(0, [](){{return cc::RemoveSelf::create();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccRemoveSelf(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RemoveSelf, "RemoveSelf", "cc.RemoveSelf",
		cc::RemoveSelf, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_RemoveSelf_init);
	LUA_METHOD("create", lua_cc_RemoveSelf_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FlipX_initWithFlipX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX", "cc.FlipX:initWithFlipX");
	LUA_TRY_INVOKE_R(1, &cc::FlipX::initWithFlipX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX", "cc.FlipX:create");
	LUA_TRY_INVOKE_R(1, &cc::FlipX::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FlipX, "FlipX", "cc.FlipX",
		cc::FlipX, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipX", lua_cc_FlipX_initWithFlipX);
	LUA_METHOD("create", lua_cc_FlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FlipY_initWithFlipY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipY", "cc.FlipY:initWithFlipY");
	LUA_TRY_INVOKE_R(1, &cc::FlipY::initWithFlipY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY", "cc.FlipY:create");
	LUA_TRY_INVOKE_R(1, &cc::FlipY::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FlipY, "FlipY", "cc.FlipY",
		cc::FlipY, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithFlipY", lua_cc_FlipY_initWithFlipY);
	LUA_METHOD("create", lua_cc_FlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Place_initWithPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Place", "cc.Place:initWithPosition");
	LUA_TRY_INVOKE_R(1, &cc::Place::initWithPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Place_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Place", "cc.Place:create");
	LUA_TRY_INVOKE_R(1, &cc::Place::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccPlace(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Place, "Place", "cc.Place",
		cc::Place, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithPosition", lua_cc_Place_initWithPosition);
	LUA_METHOD("create", lua_cc_Place_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CallFunc_execute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CallFunc", "cc.CallFunc:execute");
	LUA_TRY_INVOKE(0, &cc::CallFunc::execute);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccCallFunc(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CallFunc, "CallFunc", "cc.CallFunc",
		cc::CallFunc, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("execute", lua_cc_CallFunc_execute);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_GridAction_getGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:getGrid");
	LUA_TRY_INVOKE_R(0, &cc::GridAction::getGrid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridAction_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::GridAction::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_GridAction_reverse_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:reverse");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Action>(cc::GridAction::*)()const>(&cc::GridAction::reverse));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGridAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::GridAction, "GridAction", "cc.GridAction",
		cc::GridAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getGrid", lua_cc_GridAction_getGrid);
	LUA_METHOD("initWithDuration", lua_cc_GridAction_initWithDuration);
	LUA_METHOD("reverse", lua_cc_GridAction_reverse_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Grid3DAction_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3DAction", "cc.Grid3DAction:getGridRect");
	LUA_TRY_INVOKE_R(0, &cc::Grid3DAction::getGridRect);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Grid3DAction, "Grid3DAction", "cc.Grid3DAction",
		cc::Grid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_METHOD("getGridRect", lua_cc_Grid3DAction_getGridRect);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTiledGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TiledGrid3DAction, "TiledGrid3DAction", "cc.TiledGrid3DAction",
		cc::TiledGrid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_StopGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.StopGrid", "cc.StopGrid:create");
	LUA_TRY_INVOKE_R(0, &cc::StopGrid::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccStopGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::StopGrid, "StopGrid", "cc.StopGrid",
		cc::StopGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_StopGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ReuseGrid_initWithTimes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:initWithTimes");
	LUA_TRY_INVOKE_R(1, &cc::ReuseGrid::initWithTimes);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ReuseGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:create");
	LUA_TRY_INVOKE_R(1, &cc::ReuseGrid::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccReuseGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ReuseGrid, "ReuseGrid", "cc.ReuseGrid",
		cc::ReuseGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithTimes", lua_cc_ReuseGrid_initWithTimes);
	LUA_METHOD("create", lua_cc_ReuseGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Waves3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::Waves3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Waves3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::Waves3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Waves3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::Waves3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Waves3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::Waves3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Waves3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::Waves3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Waves3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves3D", "cc.Waves3D:create");
	LUA_TRY_INVOKE_R(4, &cc::Waves3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccWaves3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Waves3D, "Waves3D", "cc.Waves3D",
		cc::Waves3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_Waves3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_Waves3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cc_Waves3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_Waves3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_Waves3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cc_Waves3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FlipX3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithDuration");
	LUA_TRY_INVOKE_R(1, &cc::FlipX3D::initWithDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FlipX3D_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithSize");
	LUA_TRY_INVOKE_R(2, &cc::FlipX3D::initWithSize);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FlipX3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:create");
	LUA_TRY_INVOKE_R(1, &cc::FlipX3D::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FlipX3D, "FlipX3D", "cc.FlipX3D",
		cc::FlipX3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_FlipX3D_initWithDuration);
	LUA_METHOD("initWithSize", lua_cc_FlipX3D_initWithSize);
	LUA_METHOD("create", lua_cc_FlipX3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FlipY3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY3D", "cc.FlipY3D:create");
	LUA_TRY_INVOKE_R(1, &cc::FlipY3D::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FlipY3D, "FlipY3D", "cc.FlipY3D",
		cc::FlipY3D, "cc.FlipX3D",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_FlipY3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Lens3D_getLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getLensEffect");
	LUA_TRY_INVOKE_R(0, &cc::Lens3D::getLensEffect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Lens3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getPosition");
	LUA_TRY_INVOKE_R(0, &cc::Lens3D::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Lens3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::Lens3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Lens3D_setConcave(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setConcave");
	LUA_TRY_INVOKE(1, &cc::Lens3D::setConcave);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Lens3D_setLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setLensEffect");
	LUA_TRY_INVOKE(1, &cc::Lens3D::setLensEffect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Lens3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setPosition");
	LUA_TRY_INVOKE(1, &cc::Lens3D::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Lens3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Lens3D", "cc.Lens3D:create");
	LUA_TRY_INVOKE_R(4, &cc::Lens3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLens3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Lens3D, "Lens3D", "cc.Lens3D",
		cc::Lens3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getLensEffect", lua_cc_Lens3D_getLensEffect);
	LUA_METHOD("getPosition", lua_cc_Lens3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cc_Lens3D_initWithDuration);
	LUA_METHOD("setConcave", lua_cc_Lens3D_setConcave);
	LUA_METHOD("setLensEffect", lua_cc_Lens3D_setLensEffect);
	LUA_METHOD("setPosition", lua_cc_Lens3D_setPosition);
	LUA_METHOD("create", lua_cc_Lens3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Ripple3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::Ripple3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ripple3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::Ripple3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ripple3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getPosition");
	LUA_TRY_INVOKE_R(0, &cc::Ripple3D::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ripple3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:initWithDuration");
	LUA_TRY_INVOKE_R(6, &cc::Ripple3D::initWithDuration);
	LUA_INVOKE_FOOTER("6");
}
int lua_cc_Ripple3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::Ripple3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Ripple3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::Ripple3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Ripple3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setPosition");
	LUA_TRY_INVOKE(1, &cc::Ripple3D::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Ripple3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:create");
	LUA_TRY_INVOKE_R(6, &cc::Ripple3D::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccRipple3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Ripple3D, "Ripple3D", "cc.Ripple3D",
		cc::Ripple3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_Ripple3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_Ripple3D_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cc_Ripple3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cc_Ripple3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_Ripple3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_Ripple3D_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cc_Ripple3D_setPosition);
	LUA_METHOD("create", lua_cc_Ripple3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Shaky3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::Shaky3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Shaky3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:create");
	LUA_TRY_INVOKE_R(4, &cc::Shaky3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShaky3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Shaky3D, "Shaky3D", "cc.Shaky3D",
		cc::Shaky3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_Shaky3D_initWithDuration);
	LUA_METHOD("create", lua_cc_Shaky3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Liquid_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::Liquid::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Liquid_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::Liquid::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Liquid_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::Liquid::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Liquid_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::Liquid::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Liquid_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Liquid", "cc.Liquid:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::Liquid::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Liquid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Liquid", "cc.Liquid:create");
	LUA_TRY_INVOKE_R(4, &cc::Liquid::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLiquid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Liquid, "Liquid", "cc.Liquid",
		cc::Liquid, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_Liquid_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_Liquid_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cc_Liquid_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_Liquid_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_Liquid_setAmplitudeRate);
	LUA_METHOD("create", lua_cc_Liquid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Waves_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::Waves::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Waves_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::Waves::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Waves_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:initWithDuration");
	LUA_TRY_INVOKE_R(6, &cc::Waves::initWithDuration);
	LUA_INVOKE_FOOTER("6");
}
int lua_cc_Waves_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::Waves::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Waves_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves", "cc.Waves:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::Waves::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Waves_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves", "cc.Waves:create");
	LUA_TRY_INVOKE_R(6, &cc::Waves::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccWaves(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Waves, "Waves", "cc.Waves",
		cc::Waves, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_Waves_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_Waves_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cc_Waves_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_Waves_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_Waves_setAmplitudeRate);
	LUA_METHOD("create", lua_cc_Waves_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Twirl_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::Twirl::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Twirl_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::Twirl::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Twirl_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:getPosition");
	LUA_TRY_INVOKE_R(0, &cc::Twirl::getPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Twirl_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:initWithDuration");
	LUA_TRY_INVOKE_R(5, &cc::Twirl::initWithDuration);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_Twirl_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::Twirl::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Twirl_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::Twirl::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Twirl_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Twirl", "cc.Twirl:setPosition");
	LUA_TRY_INVOKE(1, &cc::Twirl::setPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Twirl_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Twirl", "cc.Twirl:create");
	LUA_TRY_INVOKE_R(5, &cc::Twirl::create);
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccTwirl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Twirl, "Twirl", "cc.Twirl",
		cc::Twirl, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_Twirl_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_Twirl_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cc_Twirl_getPosition);
	LUA_METHOD("initWithDuration", lua_cc_Twirl_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_Twirl_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_Twirl_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cc_Twirl_setPosition);
	LUA_METHOD("create", lua_cc_Twirl_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionManager_addAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:addAction");
	LUA_TRY_INVOKE(3, &cc::ActionManager::addAction);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_ActionManager_getActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getActionByTag");
	LUA_TRY_INVOKE_R(2, &cc::ActionManager::getActionByTag);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ActionManager_getNumberOfRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActions");
	LUA_TRY_INVOKE_R(0, &cc::ActionManager::getNumberOfRunningActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionManager_getNumberOfRunningActionsInTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActionsInTarget");
	LUA_TRY_INVOKE_R(1, &cc::ActionManager::getNumberOfRunningActionsInTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_getNumberOfRunningActionsInTargetByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:getNumberOfRunningActionsInTargetByTag");
	LUA_TRY_INVOKE_R(2, &cc::ActionManager::getNumberOfRunningActionsInTargetByTag);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ActionManager_pauseAllRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:pauseAllRunningActions");
	LUA_TRY_INVOKE_R(0, &cc::ActionManager::pauseAllRunningActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionManager_pauseTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:pauseTarget");
	LUA_TRY_INVOKE(1, &cc::ActionManager::pauseTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_removeAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAction");
	LUA_TRY_INVOKE(1, &cc::ActionManager::removeAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_removeActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeActionByTag");
	LUA_TRY_INVOKE(2, &cc::ActionManager::removeActionByTag);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ActionManager_removeActionsByFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeActionsByFlags");
	LUA_TRY_INVOKE(2, &cc::ActionManager::removeActionsByFlags);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ActionManager_removeAllActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActions");
	LUA_TRY_INVOKE(0, &cc::ActionManager::removeAllActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionManager_removeAllActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActionsByTag");
	LUA_TRY_INVOKE(2, &cc::ActionManager::removeAllActionsByTag);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ActionManager_removeAllActionsFromTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:removeAllActionsFromTarget");
	LUA_TRY_INVOKE(1, &cc::ActionManager::removeAllActionsFromTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_resumeTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:resumeTarget");
	LUA_TRY_INVOKE(1, &cc::ActionManager::resumeTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_resumeTargets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:resumeTargets");
	LUA_TRY_INVOKE(1, &cc::ActionManager::resumeTargets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionManager_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionManager", "cc.ActionManager:update");
	LUA_TRY_INVOKE(1, &cc::ActionManager::update);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionManager, "ActionManager", "cc.ActionManager",
		cc::ActionManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAction", lua_cc_ActionManager_addAction);
	LUA_METHOD("getActionByTag", lua_cc_ActionManager_getActionByTag);
	LUA_METHOD("getNumberOfRunningActions", lua_cc_ActionManager_getNumberOfRunningActions);
	LUA_METHOD("getNumberOfRunningActionsInTarget", lua_cc_ActionManager_getNumberOfRunningActionsInTarget);
	LUA_METHOD("getNumberOfRunningActionsInTargetByTag", lua_cc_ActionManager_getNumberOfRunningActionsInTargetByTag);
	LUA_METHOD("pauseAllRunningActions", lua_cc_ActionManager_pauseAllRunningActions);
	LUA_METHOD("pauseTarget", lua_cc_ActionManager_pauseTarget);
	LUA_METHOD("removeAction", lua_cc_ActionManager_removeAction);
	LUA_METHOD("removeActionByTag", lua_cc_ActionManager_removeActionByTag);
	LUA_METHOD("removeActionsByFlags", lua_cc_ActionManager_removeActionsByFlags);
	LUA_METHOD("removeAllActions", lua_cc_ActionManager_removeAllActions);
	LUA_METHOD("removeAllActionsByTag", lua_cc_ActionManager_removeAllActionsByTag);
	LUA_METHOD("removeAllActionsFromTarget", lua_cc_ActionManager_removeAllActionsFromTarget);
	LUA_METHOD("resumeTarget", lua_cc_ActionManager_resumeTarget);
	LUA_METHOD("resumeTargets", lua_cc_ActionManager_resumeTargets);
	LUA_METHOD("update", lua_cc_ActionManager_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_PageTurn3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PageTurn3D", "cc.PageTurn3D:create");
	LUA_TRY_INVOKE_R(2, &cc::PageTurn3D::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccPageTurn3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::PageTurn3D, "PageTurn3D", "cc.PageTurn3D",
		cc::PageTurn3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_PageTurn3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ProgressTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::ProgressTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ProgressTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTo", "cc.ProgressTo:create");
	LUA_TRY_INVOKE_R(2, &cc::ProgressTo::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccProgressTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ProgressTo, "ProgressTo", "cc.ProgressTo",
		cc::ProgressTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ProgressTo_initWithDuration);
	LUA_METHOD("create", lua_cc_ProgressTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ProgressFromTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressFromTo", "cc.ProgressFromTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::ProgressFromTo::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_ProgressFromTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressFromTo", "cc.ProgressFromTo:create");
	LUA_TRY_INVOKE_R(3, &cc::ProgressFromTo::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccProgressFromTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ProgressFromTo, "ProgressFromTo", "cc.ProgressFromTo",
		cc::ProgressFromTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ProgressFromTo_initWithDuration);
	LUA_METHOD("create", lua_cc_ProgressFromTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ShakyTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShakyTiles3D", "cc.ShakyTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::ShakyTiles3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_ShakyTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShakyTiles3D", "cc.ShakyTiles3D:create");
	LUA_TRY_INVOKE_R(4, &cc::ShakyTiles3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShakyTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ShakyTiles3D, "ShakyTiles3D", "cc.ShakyTiles3D",
		cc::ShakyTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ShakyTiles3D_initWithDuration);
	LUA_METHOD("create", lua_cc_ShakyTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ShatteredTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShatteredTiles3D", "cc.ShatteredTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::ShatteredTiles3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_ShatteredTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShatteredTiles3D", "cc.ShatteredTiles3D:create");
	LUA_TRY_INVOKE_R(4, &cc::ShatteredTiles3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShatteredTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ShatteredTiles3D, "ShatteredTiles3D", "cc.ShatteredTiles3D",
		cc::ShatteredTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ShatteredTiles3D_initWithDuration);
	LUA_METHOD("create", lua_cc_ShatteredTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ShuffleTiles_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:getDelta");
	LUA_TRY_INVOKE_R(1, &cc::ShuffleTiles::getDelta);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ShuffleTiles_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::ShuffleTiles::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_ShuffleTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShuffleTiles", "cc.ShuffleTiles:create");
	LUA_TRY_INVOKE_R(3, &cc::ShuffleTiles::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccShuffleTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ShuffleTiles, "ShuffleTiles", "cc.ShuffleTiles",
		cc::ShuffleTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getDelta", lua_cc_ShuffleTiles_getDelta);
	LUA_METHOD("initWithDuration", lua_cc_ShuffleTiles_initWithDuration);
	LUA_METHOD("create", lua_cc_ShuffleTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeOutTRTiles_testFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:testFunc");
	LUA_TRY_INVOKE_R(2, &cc::FadeOutTRTiles::testFunc);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FadeOutTRTiles_transformTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:transformTile");
	LUA_TRY_INVOKE(2, &cc::FadeOutTRTiles::transformTile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FadeOutTRTiles_turnOffTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:turnOffTile");
	LUA_TRY_INVOKE(1, &cc::FadeOutTRTiles::turnOffTile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FadeOutTRTiles_turnOnTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:turnOnTile");
	LUA_TRY_INVOKE(1, &cc::FadeOutTRTiles::turnOnTile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FadeOutTRTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutTRTiles", "cc.FadeOutTRTiles:create");
	LUA_TRY_INVOKE_R(2, &cc::FadeOutTRTiles::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutTRTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeOutTRTiles, "FadeOutTRTiles", "cc.FadeOutTRTiles",
		cc::FadeOutTRTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("testFunc", lua_cc_FadeOutTRTiles_testFunc);
	LUA_METHOD("transformTile", lua_cc_FadeOutTRTiles_transformTile);
	LUA_METHOD("turnOffTile", lua_cc_FadeOutTRTiles_turnOffTile);
	LUA_METHOD("turnOnTile", lua_cc_FadeOutTRTiles_turnOnTile);
	LUA_METHOD("create", lua_cc_FadeOutTRTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeOutBLTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutBLTiles", "cc.FadeOutBLTiles:create");
	LUA_TRY_INVOKE_R(2, &cc::FadeOutBLTiles::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutBLTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeOutBLTiles, "FadeOutBLTiles", "cc.FadeOutBLTiles",
		cc::FadeOutBLTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_FadeOutBLTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeOutUpTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutUpTiles", "cc.FadeOutUpTiles:create");
	LUA_TRY_INVOKE_R(2, &cc::FadeOutUpTiles::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutUpTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeOutUpTiles, "FadeOutUpTiles", "cc.FadeOutUpTiles",
		cc::FadeOutUpTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_FadeOutUpTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeOutDownTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutDownTiles", "cc.FadeOutDownTiles:create");
	LUA_TRY_INVOKE_R(2, &cc::FadeOutDownTiles::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutDownTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeOutDownTiles, "FadeOutDownTiles", "cc.FadeOutDownTiles",
		cc::FadeOutDownTiles, "cc.FadeOutUpTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_FadeOutDownTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TurnOffTiles_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::TurnOffTiles::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_TurnOffTiles_turnOffTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:turnOffTile");
	LUA_TRY_INVOKE(1, &cc::TurnOffTiles::turnOffTile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TurnOffTiles_turnOnTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:turnOnTile");
	LUA_TRY_INVOKE(1, &cc::TurnOffTiles::turnOnTile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TurnOffTiles>(*)(float, const cc::Vec2&, unsigned int)>(&cc::TurnOffTiles::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TurnOffTiles>(*)(float, const cc::Vec2&)>(&cc::TurnOffTiles::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TurnOffTiles, "TurnOffTiles", "cc.TurnOffTiles",
		cc::TurnOffTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_TurnOffTiles_initWithDuration);
	LUA_METHOD("turnOffTile", lua_cc_TurnOffTiles_turnOffTile);
	LUA_METHOD("turnOnTile", lua_cc_TurnOffTiles_turnOnTile);
	LUA_METHOD("create", lua_cc_TurnOffTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_WavesTiles3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::WavesTiles3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_WavesTiles3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::WavesTiles3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_WavesTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::WavesTiles3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_WavesTiles3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::WavesTiles3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_WavesTiles3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::WavesTiles3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_WavesTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:create");
	LUA_TRY_INVOKE_R(4, &cc::WavesTiles3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccWavesTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::WavesTiles3D, "WavesTiles3D", "cc.WavesTiles3D",
		cc::WavesTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_WavesTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_WavesTiles3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cc_WavesTiles3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_WavesTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_WavesTiles3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cc_WavesTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
