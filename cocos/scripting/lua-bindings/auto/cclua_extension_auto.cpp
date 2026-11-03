#include "cclua_extension_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_extension_compat.hpp"
#include "assets-manager/AssetsManager.h"
#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/Manifest.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "Particle3D/CCParticle3DRender.h"
#include "Particle3D/PU/CCPUEmitter.h"
#include "Particle3D/PU/CCPUAffector.h"
#include "Particle3D/PU/CCPUObserver.h"
#include "Particle3D/CCParticle3DAffector.h"
#include "Particle3D/PU/CCPUBehaviour.h"
#include "Particle3D/PU/CCPUListener.h"
#include "Particle3D/CCParticle3DEmitter.h"

int lua_cocos2d_extension_AssetsManager_checkUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:checkUpdate");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::extension::AssetsManager::*)()>(&cocos2d::extension::AssetsManager::checkUpdate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_deleteVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:deleteVersion");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::extension::AssetsManager::*)()>(&cocos2d::extension::AssetsManager::deleteVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_getConnectionTimeout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getConnectionTimeout");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::extension::AssetsManager::*)()>(&cocos2d::extension::AssetsManager::getConnectionTimeout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_getPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getPackageUrl");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::extension::AssetsManager::*)()const>(&cocos2d::extension::AssetsManager::getPackageUrl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_getStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getStoragePath");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::extension::AssetsManager::*)()const>(&cocos2d::extension::AssetsManager::getStoragePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getVersion");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::AssetsManager::*)()>(&cocos2d::extension::AssetsManager::getVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_getVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getVersionFileUrl");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::extension::AssetsManager::*)()const>(&cocos2d::extension::AssetsManager::getVersionFileUrl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManager_setConnectionTimeout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setConnectionTimeout");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::extension::AssetsManager::*)(unsigned int)>(&cocos2d::extension::AssetsManager::setConnectionTimeout));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_extension_AssetsManager_setPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setPackageUrl");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::extension::AssetsManager::*)(const char*)>(&cocos2d::extension::AssetsManager::setPackageUrl));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_extension_AssetsManager_setStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setStoragePath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::extension::AssetsManager::*)(const char*)>(&cocos2d::extension::AssetsManager::setStoragePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_extension_AssetsManager_setVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setVersionFileUrl");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::extension::AssetsManager::*)(const char*)>(&cocos2d::extension::AssetsManager::setVersionFileUrl));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_extension_AssetsManager_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:update");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::extension::AssetsManager::*)()>(&cocos2d::extension::AssetsManager::update));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccAssetsManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::extension::AssetsManager, "AssetsManager", "cc.AssetsManager",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("checkUpdate", lua_cocos2d_extension_AssetsManager_checkUpdate);
	LUA_METHOD("deleteVersion", lua_cocos2d_extension_AssetsManager_deleteVersion);
	LUA_METHOD("getConnectionTimeout", lua_cocos2d_extension_AssetsManager_getConnectionTimeout);
	LUA_METHOD("getPackageUrl", lua_cocos2d_extension_AssetsManager_getPackageUrl);
	LUA_METHOD("getStoragePath", lua_cocos2d_extension_AssetsManager_getStoragePath);
	LUA_METHOD("getVersion", lua_cocos2d_extension_AssetsManager_getVersion);
	LUA_METHOD("getVersionFileUrl", lua_cocos2d_extension_AssetsManager_getVersionFileUrl);
	LUA_METHOD("setConnectionTimeout", lua_cocos2d_extension_AssetsManager_setConnectionTimeout);
	LUA_METHOD("setPackageUrl", lua_cocos2d_extension_AssetsManager_setPackageUrl);
	LUA_METHOD("setStoragePath", lua_cocos2d_extension_AssetsManager_setStoragePath);
	LUA_METHOD("setVersionFileUrl", lua_cocos2d_extension_AssetsManager_setVersionFileUrl);
	LUA_METHOD("update", lua_cocos2d_extension_AssetsManager_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_extension_EventAssetsManagerEx_getAssetId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getAssetId");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getAssetId));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getAssetsManagerEx(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getAssetsManagerEx");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::extension::AssetsManagerEx*(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getAssetsManagerEx));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getCURLECode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getCURLECode");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getCURLECode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getCURLMCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getCURLMCode");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getCURLMCode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getEventCode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::extension::EventAssetsManagerEx::EventCode(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getEventCode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getMessage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getMessage");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getMessage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getPercent");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getPercent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_EventAssetsManagerEx_getPercentByFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getPercentByFile");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::extension::EventAssetsManagerEx::*)()const>(&cocos2d::extension::EventAssetsManagerEx::getPercentByFile));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccEventAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::extension::EventAssetsManagerEx, "EventAssetsManagerEx", "cc.EventAssetsManagerEx",
		cocos2d::EventCustom, "cc.EventCustom",
		nullptr, nullptr);
	LUA_METHOD("getAssetId", lua_cocos2d_extension_EventAssetsManagerEx_getAssetId);
	LUA_METHOD("getAssetsManagerEx", lua_cocos2d_extension_EventAssetsManagerEx_getAssetsManagerEx);
	LUA_METHOD("getCURLECode", lua_cocos2d_extension_EventAssetsManagerEx_getCURLECode);
	LUA_METHOD("getCURLMCode", lua_cocos2d_extension_EventAssetsManagerEx_getCURLMCode);
	LUA_METHOD("getEventCode", lua_cocos2d_extension_EventAssetsManagerEx_getEventCode);
	LUA_METHOD("getMessage", lua_cocos2d_extension_EventAssetsManagerEx_getMessage);
	LUA_METHOD("getPercent", lua_cocos2d_extension_EventAssetsManagerEx_getPercent);
	LUA_METHOD("getPercentByFile", lua_cocos2d_extension_EventAssetsManagerEx_getPercentByFile);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
extern int luaReg_Extension_ccAssetsManager(lua_State* lua_S);
extern int luaReg_Extension_ccEventAssetsManagerEx(lua_State* lua_S);
extern int luaReg_Extension_ccManifest(lua_State* lua_S);
extern int luaReg_Extension_ccAssetsManagerEx(lua_State* lua_S);
extern int luaReg_Extension_ccEventListenerAssetsManagerEx(lua_State* lua_S);
extern int luaReg_Extension_ccParticleSystem3D(lua_State* lua_S);
extern int luaReg_Extension_ccPUParticleSystem3D(lua_State* lua_S);

int register_all_cc_extension(lua_State* lua_S)
{
	luaReg_Extension_ccAssetsManager(lua_S);
	luaReg_Extension_ccEventAssetsManagerEx(lua_S);
	luaReg_Extension_ccManifest(lua_S);
	luaReg_Extension_ccAssetsManagerEx(lua_S);
	luaReg_Extension_ccEventListenerAssetsManagerEx(lua_S);
	luaReg_Extension_ccParticleSystem3D(lua_S);
	luaReg_Extension_ccPUParticleSystem3D(lua_S);
	return 0;
}
