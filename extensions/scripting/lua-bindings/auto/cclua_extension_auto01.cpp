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

int lua_cocos2d_extension_Manifest_getManifestFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getManifestFileUrl");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::getManifestFileUrl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_getPackageUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getPackageUrl");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::getPackageUrl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getSearchPaths");
	LUA_TRY_INVOKE_R(0, static_cast<std::vector<std::string>(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::getSearchPaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getVersion");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::getVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_getVersionFileUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:getVersionFileUrl");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::getVersionFileUrl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_isLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:isLoaded");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::isLoaded));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_Manifest_isVersionLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Manifest", "cc.Manifest:isVersionLoaded");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::extension::Manifest::*)()const>(&cocos2d::extension::Manifest::isVersionLoaded));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccManifest(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::extension::Manifest, "Manifest", "cc.Manifest",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getManifestFileUrl", lua_cocos2d_extension_Manifest_getManifestFileUrl);
	LUA_METHOD("getPackageUrl", lua_cocos2d_extension_Manifest_getPackageUrl);
	LUA_METHOD("getSearchPaths", lua_cocos2d_extension_Manifest_getSearchPaths);
	LUA_METHOD("getVersion", lua_cocos2d_extension_Manifest_getVersion);
	LUA_METHOD("getVersionFileUrl", lua_cocos2d_extension_Manifest_getVersionFileUrl);
	LUA_METHOD("isLoaded", lua_cocos2d_extension_Manifest_isLoaded);
	LUA_METHOD("isVersionLoaded", lua_cocos2d_extension_Manifest_isVersionLoaded);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_extension_AssetsManagerEx_checkUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:checkUpdate");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::extension::AssetsManagerEx::*)()>(&cocos2d::extension::AssetsManagerEx::checkUpdate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_downloadFailedAssets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:downloadFailedAssets");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::extension::AssetsManagerEx::*)()>(&cocos2d::extension::AssetsManagerEx::downloadFailedAssets));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_getLocalManifest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getLocalManifest");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::extension::Manifest*(cocos2d::extension::AssetsManagerEx::*)()const>(&cocos2d::extension::AssetsManagerEx::getLocalManifest));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_getMaxConcurrentTask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getMaxConcurrentTask");
	LUA_TRY_INVOKE_R(0, static_cast<const int(cocos2d::extension::AssetsManagerEx::*)()const>(&cocos2d::extension::AssetsManagerEx::getMaxConcurrentTask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_getRemoteManifest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getRemoteManifest");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::extension::Manifest*(cocos2d::extension::AssetsManagerEx::*)()const>(&cocos2d::extension::AssetsManagerEx::getRemoteManifest));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_getState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::extension::AssetsManagerEx::State(cocos2d::extension::AssetsManagerEx::*)()const>(&cocos2d::extension::AssetsManagerEx::getState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_getStoragePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:getStoragePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::extension::AssetsManagerEx::*)()const>(&cocos2d::extension::AssetsManagerEx::getStoragePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_setMaxConcurrentTask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:setMaxConcurrentTask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::extension::AssetsManagerEx::*)(const int)>(&cocos2d::extension::AssetsManagerEx::setMaxConcurrentTask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_extension_AssetsManagerEx_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:update");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::extension::AssetsManagerEx::*)()>(&cocos2d::extension::AssetsManagerEx::update));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_extension_AssetsManagerEx_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AssetsManagerEx", "cc.AssetsManagerEx:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::extension::AssetsManagerEx*(*)(std::string_view, std::string_view)>(&cocos2d::extension::AssetsManagerEx::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Extension_ccAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::extension::AssetsManagerEx, "AssetsManagerEx", "cc.AssetsManagerEx",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("checkUpdate", lua_cocos2d_extension_AssetsManagerEx_checkUpdate);
	LUA_METHOD("downloadFailedAssets", lua_cocos2d_extension_AssetsManagerEx_downloadFailedAssets);
	LUA_METHOD("getLocalManifest", lua_cocos2d_extension_AssetsManagerEx_getLocalManifest);
	LUA_METHOD("getMaxConcurrentTask", lua_cocos2d_extension_AssetsManagerEx_getMaxConcurrentTask);
	LUA_METHOD("getRemoteManifest", lua_cocos2d_extension_AssetsManagerEx_getRemoteManifest);
	LUA_METHOD("getState", lua_cocos2d_extension_AssetsManagerEx_getState);
	LUA_METHOD("getStoragePath", lua_cocos2d_extension_AssetsManagerEx_getStoragePath);
	LUA_METHOD("setMaxConcurrentTask", lua_cocos2d_extension_AssetsManagerEx_setMaxConcurrentTask);
	LUA_METHOD("update", lua_cocos2d_extension_AssetsManagerEx_update);
	LUA_METHOD("create", lua_cocos2d_extension_AssetsManagerEx_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
