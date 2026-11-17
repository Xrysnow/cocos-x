#include "cclua_extension_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "assets-manager/AssetsManager.h"
#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/Manifest.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

int lua_cc_extension_AssetsManager_checkUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:checkUpdate");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::checkUpdate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_deleteVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:deleteVersion");
	LUA_TRY_INVOKE(0, &cc::extension::AssetsManager::deleteVersion);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_getConnectionTimeout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getConnectionTimeout");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::getConnectionTimeout);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_getPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getPackageUrl");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::getPackageUrl);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_getStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getStoragePath");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::getStoragePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getVersion");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::getVersion);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_getVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:getVersionFileUrl");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManager::getVersionFileUrl);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_setConnectionTimeout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setConnectionTimeout");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManager::setConnectionTimeout);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManager_setPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setPackageUrl");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManager::setPackageUrl);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManager_setStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setStoragePath");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManager::setStoragePath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManager_setVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:setVersionFileUrl");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManager::setVersionFileUrl);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManager_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:update");
	LUA_TRY_INVOKE(0, static_cast<void(cc::extension::AssetsManager::*)()>(&cc::extension::AssetsManager::update));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AssetsManager", "cc.AssetsManager:create");
	if (argc == 6 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else if (argc == 6 && !ok && lua_isnil(lua_S, 6)) { arg_cur = 5; } else if (argc == 6 && !ok && lua_isnil(lua_S, 7)) { arg_cur = 6; } else {
	LUA_TRY_INVOKE_R(6, &cc::extension::AssetsManager::create);
	}
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Extension_ccAssetsManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::extension::AssetsManager, "AssetsManager", "cc.AssetsManager",
		cc::extension::AssetsManager, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("checkUpdate", lua_cc_extension_AssetsManager_checkUpdate);
	LUA_METHOD("deleteVersion", lua_cc_extension_AssetsManager_deleteVersion);
	LUA_METHOD("getConnectionTimeout", lua_cc_extension_AssetsManager_getConnectionTimeout);
	LUA_METHOD("getPackageUrl", lua_cc_extension_AssetsManager_getPackageUrl);
	LUA_METHOD("getStoragePath", lua_cc_extension_AssetsManager_getStoragePath);
	LUA_METHOD("getVersion", lua_cc_extension_AssetsManager_getVersion);
	LUA_METHOD("getVersionFileUrl", lua_cc_extension_AssetsManager_getVersionFileUrl);
	LUA_METHOD("setConnectionTimeout", lua_cc_extension_AssetsManager_setConnectionTimeout);
	LUA_METHOD("setPackageUrl", lua_cc_extension_AssetsManager_setPackageUrl);
	LUA_METHOD("setStoragePath", lua_cc_extension_AssetsManager_setStoragePath);
	LUA_METHOD("setVersionFileUrl", lua_cc_extension_AssetsManager_setVersionFileUrl);
	LUA_METHOD("update", lua_cc_extension_AssetsManager_update);
	LUA_METHOD("create", lua_cc_extension_AssetsManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_extension_EventAssetsManagerEx_getAssetId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getAssetId");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getAssetId);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getAssetsManagerEx(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getAssetsManagerEx");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getAssetsManagerEx);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getCURLECode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getCURLECode");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getCURLECode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getCURLMCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getCURLMCode");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getCURLMCode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getEventCode");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getEventCode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getMessage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getMessage");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getMessage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getPercent");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getPercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_EventAssetsManagerEx_getPercentByFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventAssetsManagerEx", "cc.EventAssetsManagerEx:getPercentByFile");
	LUA_TRY_INVOKE_R(0, &cc::extension::EventAssetsManagerEx::getPercentByFile);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccEventAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::extension::EventAssetsManagerEx, "EventAssetsManagerEx", "cc.EventAssetsManagerEx",
		cc::extension::EventAssetsManagerEx, "cc.EventCustom",
		nullptr, nullptr);
	LUA_METHOD("getAssetId", lua_cc_extension_EventAssetsManagerEx_getAssetId);
	LUA_METHOD("getAssetsManagerEx", lua_cc_extension_EventAssetsManagerEx_getAssetsManagerEx);
	LUA_METHOD("getCURLECode", lua_cc_extension_EventAssetsManagerEx_getCURLECode);
	LUA_METHOD("getCURLMCode", lua_cc_extension_EventAssetsManagerEx_getCURLMCode);
	LUA_METHOD("getEventCode", lua_cc_extension_EventAssetsManagerEx_getEventCode);
	LUA_METHOD("getMessage", lua_cc_extension_EventAssetsManagerEx_getMessage);
	LUA_METHOD("getPercent", lua_cc_extension_EventAssetsManagerEx_getPercent);
	LUA_METHOD("getPercentByFile", lua_cc_extension_EventAssetsManagerEx_getPercentByFile);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_extension_Manifest_getManifestFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getManifestFileUrl");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::getManifestFileUrl);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_getPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getPackageUrl");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::getPackageUrl);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getSearchPaths");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::getSearchPaths);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getVersion");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::getVersion);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_getVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getVersionFileUrl");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::getVersionFileUrl);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_isLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:isLoaded");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::isLoaded);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_Manifest_isVersionLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:isVersionLoaded");
	LUA_TRY_INVOKE_R(0, &cc::extension::Manifest::isVersionLoaded);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccManifest(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::extension::Manifest, "Manifest", "cc.Manifest",
		cc::extension::Manifest, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getManifestFileUrl", lua_cc_extension_Manifest_getManifestFileUrl);
	LUA_METHOD("getPackageUrl", lua_cc_extension_Manifest_getPackageUrl);
	LUA_METHOD("getSearchPaths", lua_cc_extension_Manifest_getSearchPaths);
	LUA_METHOD("getVersion", lua_cc_extension_Manifest_getVersion);
	LUA_METHOD("getVersionFileUrl", lua_cc_extension_Manifest_getVersionFileUrl);
	LUA_METHOD("isLoaded", lua_cc_extension_Manifest_isLoaded);
	LUA_METHOD("isVersionLoaded", lua_cc_extension_Manifest_isVersionLoaded);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_extension_AssetsManagerEx_checkUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:checkUpdate");
	LUA_TRY_INVOKE(0, &cc::extension::AssetsManagerEx::checkUpdate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_downloadFailedAssets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:downloadFailedAssets");
	LUA_TRY_INVOKE(0, &cc::extension::AssetsManagerEx::downloadFailedAssets);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_getLocalManifest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getLocalManifest");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManagerEx::getLocalManifest);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_getMaxConcurrentTask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getMaxConcurrentTask");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManagerEx::getMaxConcurrentTask);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_getRemoteManifest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getRemoteManifest");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManagerEx::getRemoteManifest);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_getState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getState");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManagerEx::getState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_getStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getStoragePath");
	LUA_TRY_INVOKE_R(0, &cc::extension::AssetsManagerEx::getStoragePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_setMaxConcurrentTask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:setMaxConcurrentTask");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManagerEx::setMaxConcurrentTask);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManagerEx_setVerifyCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:setVerifyCallback");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManagerEx::setVerifyCallback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManagerEx_setVersionCompareHandle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:setVersionCompareHandle");
	LUA_TRY_INVOKE(1, &cc::extension::AssetsManagerEx::setVersionCompareHandle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_extension_AssetsManagerEx_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:update");
	LUA_TRY_INVOKE(0, &cc::extension::AssetsManagerEx::update);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_extension_AssetsManagerEx_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:create");
	LUA_TRY_INVOKE_R(2, &cc::extension::AssetsManagerEx::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Extension_ccAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::extension::AssetsManagerEx, "AssetsManagerEx", "cc.AssetsManagerEx",
		cc::extension::AssetsManagerEx, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("checkUpdate", lua_cc_extension_AssetsManagerEx_checkUpdate);
	LUA_METHOD("downloadFailedAssets", lua_cc_extension_AssetsManagerEx_downloadFailedAssets);
	LUA_METHOD("getLocalManifest", lua_cc_extension_AssetsManagerEx_getLocalManifest);
	LUA_METHOD("getMaxConcurrentTask", lua_cc_extension_AssetsManagerEx_getMaxConcurrentTask);
	LUA_METHOD("getRemoteManifest", lua_cc_extension_AssetsManagerEx_getRemoteManifest);
	LUA_METHOD("getState", lua_cc_extension_AssetsManagerEx_getState);
	LUA_METHOD("getStoragePath", lua_cc_extension_AssetsManagerEx_getStoragePath);
	LUA_METHOD("setMaxConcurrentTask", lua_cc_extension_AssetsManagerEx_setMaxConcurrentTask);
	LUA_METHOD("setVerifyCallback", lua_cc_extension_AssetsManagerEx_setVerifyCallback);
	LUA_METHOD("setVersionCompareHandle", lua_cc_extension_AssetsManagerEx_setVersionCompareHandle);
	LUA_METHOD("update", lua_cc_extension_AssetsManagerEx_update);
	LUA_METHOD("create", lua_cc_extension_AssetsManagerEx_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_extension_EventListenerAssetsManagerEx_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerAssetsManagerEx", "cc.EventListenerAssetsManagerEx:init");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, &cc::extension::EventListenerAssetsManagerEx::init);
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_extension_EventListenerAssetsManagerEx_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerAssetsManagerEx", "cc.EventListenerAssetsManagerEx:create");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, &cc::extension::EventListenerAssetsManagerEx::create);
	}
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Extension_ccEventListenerAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::extension::EventListenerAssetsManagerEx, "EventListenerAssetsManagerEx", "cc.EventListenerAssetsManagerEx",
		cc::extension::EventListenerAssetsManagerEx, "cc.EventListenerCustom",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_extension_EventListenerAssetsManagerEx_init);
	LUA_METHOD("create", lua_cc_extension_EventListenerAssetsManagerEx_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSystem3D_getAliveParticleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getAliveParticleCount");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::getAliveParticleCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_getParticleQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getParticleQuota");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::getParticleQuota);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_getState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getState");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::getState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_isKeepLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:isKeepLocal");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem3D::isKeepLocal);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_pauseParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:pauseParticleSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem3D::pauseParticleSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_removeAffector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:removeAffector");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem3D::removeAffector);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem3D_removeAllAffector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:removeAllAffector");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem3D::removeAllAffector);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_resumeParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:resumeParticleSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem3D::resumeParticleSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem3D::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem3D_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setEnabled");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem3D::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem3D_setKeepLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setKeepLocal");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem3D::setKeepLocal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem3D_setParticleQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setParticleQuota");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem3D::setParticleQuota);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem3D_startParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:startParticleSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem3D::startParticleSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem3D_stopParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:stopParticleSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem3D::stopParticleSystem);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccParticleSystem3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSystem3D, "ParticleSystem3D", "cc.ParticleSystem3D",
		cc::ParticleSystem3D, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAliveParticleCount", lua_cc_ParticleSystem3D_getAliveParticleCount);
	LUA_METHOD("getBlendFunc", lua_cc_ParticleSystem3D_getBlendFunc);
	LUA_METHOD("getParticleQuota", lua_cc_ParticleSystem3D_getParticleQuota);
	LUA_METHOD("getState", lua_cc_ParticleSystem3D_getState);
	LUA_METHOD("isEnabled", lua_cc_ParticleSystem3D_isEnabled);
	LUA_METHOD("isKeepLocal", lua_cc_ParticleSystem3D_isKeepLocal);
	LUA_METHOD("pauseParticleSystem", lua_cc_ParticleSystem3D_pauseParticleSystem);
	LUA_METHOD("removeAffector", lua_cc_ParticleSystem3D_removeAffector);
	LUA_METHOD("removeAllAffector", lua_cc_ParticleSystem3D_removeAllAffector);
	LUA_METHOD("resumeParticleSystem", lua_cc_ParticleSystem3D_resumeParticleSystem);
	LUA_METHOD("setBlendFunc", lua_cc_ParticleSystem3D_setBlendFunc);
	LUA_METHOD("setEnabled", lua_cc_ParticleSystem3D_setEnabled);
	LUA_METHOD("setKeepLocal", lua_cc_ParticleSystem3D_setKeepLocal);
	LUA_METHOD("setParticleQuota", lua_cc_ParticleSystem3D_setParticleQuota);
	LUA_METHOD("startParticleSystem", lua_cc_ParticleSystem3D_startParticleSystem);
	LUA_METHOD("stopParticleSystem", lua_cc_ParticleSystem3D_stopParticleSystem);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_PUParticleSystem3D_calulateRotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:calulateRotationOffset");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::calulateRotationOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_clearAllParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:clearAllParticles");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::clearAllParticles);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:clone");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_copyAttributesTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:copyAttributesTo");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::copyAttributesTo);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_forceUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:forceUpdate");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::forceUpdate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_getDefaultDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultDepth");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getDefaultDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getDefaultHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultHeight");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getDefaultHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getDefaultWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultWidth");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getDefaultWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getDerivedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDerivedPosition");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getDerivedPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getDerivedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDerivedScale");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getDerivedScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getEmittedEmitterQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getEmittedEmitterQuota");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getEmittedEmitterQuota);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getEmittedSystemQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getEmittedSystemQuota");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getEmittedSystemQuota);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getMaterialName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getMaterialName");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getMaterialName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getMaxVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getMaxVelocity");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getMaxVelocity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getParentParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getParentParticleSystem");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getParentParticleSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getParticleSystemScaleVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getParticleSystemScaleVelocity");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getParticleSystemScaleVelocity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_getTimeElapsedSinceStart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getTimeElapsedSinceStart");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::getTimeElapsedSinceStart);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_initSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initSystem");
	LUA_TRY_INVOKE_R(1, &cc::PUParticleSystem3D::initSystem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_initWithFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initWithFilePath");
	LUA_TRY_INVOKE_R(1, &cc::PUParticleSystem3D::initWithFilePath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_initWithFilePathAndMaterialPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initWithFilePathAndMaterialPath");
	LUA_TRY_INVOKE_R(2, &cc::PUParticleSystem3D::initWithFilePathAndMaterialPath);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_PUParticleSystem3D_isMarkedForEmission(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:isMarkedForEmission");
	LUA_TRY_INVOKE_R(0, &cc::PUParticleSystem3D::isMarkedForEmission);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_removeAllBehaviourTemplate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllBehaviourTemplate");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::removeAllBehaviourTemplate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_removeAllEmitter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllEmitter");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::removeAllEmitter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_removeAllListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllListener");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::removeAllListener);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_removerAllObserver(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removerAllObserver");
	LUA_TRY_INVOKE(0, &cc::PUParticleSystem3D::removerAllObserver);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PUParticleSystem3D_rotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:rotationOffset");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::rotationOffset);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setDefaultDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultDepth");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setDefaultDepth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setDefaultHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultHeight");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setDefaultHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setDefaultWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultWidth");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setDefaultWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setEmittedEmitterQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setEmittedEmitterQuota");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setEmittedEmitterQuota);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setEmittedSystemQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setEmittedSystemQuota");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setEmittedSystemQuota);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setMarkedForEmission(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMarkedForEmission");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setMarkedForEmission);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setMaterialName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMaterialName");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setMaterialName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setMaxVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMaxVelocity");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setMaxVelocity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_setParticleSystemScaleVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setParticleSystemScaleVelocity");
	LUA_TRY_INVOKE(1, &cc::PUParticleSystem3D::setParticleSystemScaleVelocity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PUParticleSystem3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::PUParticleSystem3D>(*)(std::string_view, std::string_view)>(&cc::PUParticleSystem3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::PUParticleSystem3D>(*)(std::string_view)>(&cc::PUParticleSystem3D::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::PUParticleSystem3D>(*)()>(&cc::PUParticleSystem3D::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int luaReg_Extension_ccPUParticleSystem3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::PUParticleSystem3D, "PUParticleSystem3D", "cc.PUParticleSystem3D",
		cc::PUParticleSystem3D, "cc.ParticleSystem3D",
		nullptr, nullptr);
	LUA_METHOD("calulateRotationOffset", lua_cc_PUParticleSystem3D_calulateRotationOffset);
	LUA_METHOD("clearAllParticles", lua_cc_PUParticleSystem3D_clearAllParticles);
	LUA_METHOD("clone", lua_cc_PUParticleSystem3D_clone);
	LUA_METHOD("copyAttributesTo", lua_cc_PUParticleSystem3D_copyAttributesTo);
	LUA_METHOD("forceUpdate", lua_cc_PUParticleSystem3D_forceUpdate);
	LUA_METHOD("getDefaultDepth", lua_cc_PUParticleSystem3D_getDefaultDepth);
	LUA_METHOD("getDefaultHeight", lua_cc_PUParticleSystem3D_getDefaultHeight);
	LUA_METHOD("getDefaultWidth", lua_cc_PUParticleSystem3D_getDefaultWidth);
	LUA_METHOD("getDerivedPosition", lua_cc_PUParticleSystem3D_getDerivedPosition);
	LUA_METHOD("getDerivedScale", lua_cc_PUParticleSystem3D_getDerivedScale);
	LUA_METHOD("getEmittedEmitterQuota", lua_cc_PUParticleSystem3D_getEmittedEmitterQuota);
	LUA_METHOD("getEmittedSystemQuota", lua_cc_PUParticleSystem3D_getEmittedSystemQuota);
	LUA_METHOD("getMaterialName", lua_cc_PUParticleSystem3D_getMaterialName);
	LUA_METHOD("getMaxVelocity", lua_cc_PUParticleSystem3D_getMaxVelocity);
	LUA_METHOD("getParentParticleSystem", lua_cc_PUParticleSystem3D_getParentParticleSystem);
	LUA_METHOD("getParticleSystemScaleVelocity", lua_cc_PUParticleSystem3D_getParticleSystemScaleVelocity);
	LUA_METHOD("getTimeElapsedSinceStart", lua_cc_PUParticleSystem3D_getTimeElapsedSinceStart);
	LUA_METHOD("initSystem", lua_cc_PUParticleSystem3D_initSystem);
	LUA_METHOD("initWithFilePath", lua_cc_PUParticleSystem3D_initWithFilePath);
	LUA_METHOD("initWithFilePathAndMaterialPath", lua_cc_PUParticleSystem3D_initWithFilePathAndMaterialPath);
	LUA_METHOD("isMarkedForEmission", lua_cc_PUParticleSystem3D_isMarkedForEmission);
	LUA_METHOD("removeAllBehaviourTemplate", lua_cc_PUParticleSystem3D_removeAllBehaviourTemplate);
	LUA_METHOD("removeAllEmitter", lua_cc_PUParticleSystem3D_removeAllEmitter);
	LUA_METHOD("removeAllListener", lua_cc_PUParticleSystem3D_removeAllListener);
	LUA_METHOD("removerAllObserver", lua_cc_PUParticleSystem3D_removerAllObserver);
	LUA_METHOD("rotationOffset", lua_cc_PUParticleSystem3D_rotationOffset);
	LUA_METHOD("setDefaultDepth", lua_cc_PUParticleSystem3D_setDefaultDepth);
	LUA_METHOD("setDefaultHeight", lua_cc_PUParticleSystem3D_setDefaultHeight);
	LUA_METHOD("setDefaultWidth", lua_cc_PUParticleSystem3D_setDefaultWidth);
	LUA_METHOD("setEmittedEmitterQuota", lua_cc_PUParticleSystem3D_setEmittedEmitterQuota);
	LUA_METHOD("setEmittedSystemQuota", lua_cc_PUParticleSystem3D_setEmittedSystemQuota);
	LUA_METHOD("setMarkedForEmission", lua_cc_PUParticleSystem3D_setMarkedForEmission);
	LUA_METHOD("setMaterialName", lua_cc_PUParticleSystem3D_setMaterialName);
	LUA_METHOD("setMaxVelocity", lua_cc_PUParticleSystem3D_setMaxVelocity);
	LUA_METHOD("setParticleSystemScaleVelocity", lua_cc_PUParticleSystem3D_setParticleSystemScaleVelocity);
	LUA_METHOD("create", lua_cc_PUParticleSystem3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

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
