#pragma once
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include <cstring>
#include <cstdio>


// Preserve this module's legacy checked conversions independently of Release's
// global binding setting. Numeric strings and nil booleans remain accepted;
// The listener factory additionally preserves its CC_DEBUG-dependent inputs.
namespace extension_binding
{
template<typename T> struct callback_type : std::false_type {};
template<typename R, typename... Args>
struct callback_type<std::function<R(Args...)>> : std::true_type {};

template<typename Arg>
bool prepare_value(lua_State* L, int index, const char* name)
{
	using T = std::remove_cv_t<std::remove_reference_t<Arg>>;
	if constexpr (std::is_enum_v<T> || std::is_same_v<T, int>) {
		int value;
		if (!luaval_to_int32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_same_v<T, unsigned int>) {
		unsigned int value;
		if (!luaval_to_uint32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_floating_point_v<T>) {
		double value;
		if (!luaval_to_number(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (callback_type<T>::value) {
		return lua_isfunction(L, index);
	}
	return true;
}

template<typename... Args, size_t... Index>
bool prepare_arguments(lua_State* L, const char* name, std::index_sequence<Index...>)
{
	const int first = lua_gettop(L) - int(sizeof...(Args)) + 1;
	return (prepare_value<Args>(L, first + int(Index), name) && ...);
}

template<typename T> struct prepare_signature;
template<typename R, typename... Args>
struct prepare_signature<R(*)(Args...)> {
	static bool run(lua_State* L, const char* name) {
		return prepare_arguments<Args...>(L, name, std::index_sequence_for<Args...>{});
	}
};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...)> : prepare_signature<R(*)(Args...)> {};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...) const> : prepare_signature<R(*)(Args...)> {};

template<typename F>
bool prepare(lua_State* L, const char* name, const F&)
{
    // The old manual factory checks argument types only in CC_DEBUG. In
    // Release a non-function handler has refid 0 and dispatch is a no-op.
    // Keep that defined legacy branch without rooting the invalid Lua value.
    if (std::strcmp(name, "cc.EventListenerAssetsManagerEx:create") == 0) {
#if CC_DEBUG >= 1
        tolua_Error error{};
        if (!tolua_isusertype(L, 2, "cc.AssetsManagerEx", 0, &error))
            tolua_error(L, "#ferror in function 'cclua_Extension_EventListenerAssetsManagerEx_create'.", &error);
        if (!lua_isfunction(L, 3)) {
            error.index = 3; error.array = 0; error.type = "[not function]";
            tolua_error(L, "#ferror in function 'cclua_Extension_EventListenerAssetsManagerEx_create'.", &error);
        }
#else
        if (!lua_isfunction(L, 3)) {
            lua_pushcfunction(L, [](lua_State*) -> int { return 0; });
            lua_replace(L, 3);
        }
#endif
    }
	using T = std::decay_t<F>;
	if constexpr (std::is_class_v<T>)
		return prepare_signature<typename lua::function_traits<T>::pointer>::run(L, name);
	else
		return prepare_signature<T>::run(L, name);
}

inline void check_receiver(lua_State* L, const char* type, const char* name, bool member)
{
#if CC_DEBUG >= 1
    tolua_Error error{};
    const bool valid = member ? tolua_isusertype(L, 1, type, 0, &error)
                              : tolua_isusertable(L, 1, type, 0, &error);
    char native[192];
    if (std::strcmp(name, "cc.EventListenerAssetsManagerEx:create") == 0)
        std::snprintf(native, sizeof(native), "cclua_Extension_EventListenerAssetsManagerEx_create");
    else {
        std::snprintf(native, sizeof(native), "lua_cc_extension_%s", name + 3);
        for (char* p = native; *p; ++p) if (*p == ':') *p = '_';
    }
    if (!valid) {
        char message[256];
        std::snprintf(message, sizeof(message), "#ferror in function '%s'.", native);
        tolua_error(L, message, &error);
    }
    if (member && !tolua_tousertype(L, 1, nullptr)) {
        char message[256];
        std::snprintf(message, sizeof(message), "invalid 'cobj' in function '%s'", native);
        tolua_error(L, message, nullptr);
    }
#else
    (void)L; (void)type; (void)name; (void)member;
#endif
}
inline int fail(lua_State* L, const char* name, int argc, int attempted)
{
    struct Error { const char* name; const char* native; const char* format; const char* label; int expected; bool overload; };
    static const Error errors[] = {
        {"cc.AssetsManager:setStoragePath", "lua_cc_extension_AssetsManager_setStoragePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setStoragePath", 1, false},
        {"cc.AssetsManager:setPackageUrl", "lua_cc_extension_AssetsManager_setPackageUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setPackageUrl", 1, false},
        {"cc.AssetsManager:checkUpdate", "lua_cc_extension_AssetsManager_checkUpdate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:checkUpdate", 0, false},
        {"cc.AssetsManager:getStoragePath", "lua_cc_extension_AssetsManager_getStoragePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getStoragePath", 0, false},
        {"cc.AssetsManager:update", "lua_cc_extension_AssetsManager_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:update", 0, false},
        {"cc.AssetsManager:setConnectionTimeout", "lua_cc_extension_AssetsManager_setConnectionTimeout", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setConnectionTimeout", 1, false},
        {"cc.AssetsManager:setVersionFileUrl", "lua_cc_extension_AssetsManager_setVersionFileUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setVersionFileUrl", 1, false},
        {"cc.AssetsManager:getPackageUrl", "lua_cc_extension_AssetsManager_getPackageUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getPackageUrl", 0, false},
        {"cc.AssetsManager:getConnectionTimeout", "lua_cc_extension_AssetsManager_getConnectionTimeout", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getConnectionTimeout", 0, false},
        {"cc.AssetsManager:getVersion", "lua_cc_extension_AssetsManager_getVersion", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersion", 0, false},
        {"cc.AssetsManager:getVersionFileUrl", "lua_cc_extension_AssetsManager_getVersionFileUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersionFileUrl", 0, false},
        {"cc.AssetsManager:deleteVersion", "lua_cc_extension_AssetsManager_deleteVersion", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:deleteVersion", 0, false},
        {"cc.EventAssetsManagerEx:getAssetsManagerEx", "lua_cc_extension_EventAssetsManagerEx_getAssetsManagerEx", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getAssetsManagerEx", 0, false},
        {"cc.EventAssetsManagerEx:getAssetId", "lua_cc_extension_EventAssetsManagerEx_getAssetId", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getAssetId", 0, false},
        {"cc.EventAssetsManagerEx:getCURLECode", "lua_cc_extension_EventAssetsManagerEx_getCURLECode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getCURLECode", 0, false},
        {"cc.EventAssetsManagerEx:getMessage", "lua_cc_extension_EventAssetsManagerEx_getMessage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getMessage", 0, false},
        {"cc.EventAssetsManagerEx:getCURLMCode", "lua_cc_extension_EventAssetsManagerEx_getCURLMCode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getCURLMCode", 0, false},
        {"cc.EventAssetsManagerEx:getPercentByFile", "lua_cc_extension_EventAssetsManagerEx_getPercentByFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getPercentByFile", 0, false},
        {"cc.EventAssetsManagerEx:getEventCode", "lua_cc_extension_EventAssetsManagerEx_getEventCode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getEventCode", 0, false},
        {"cc.EventAssetsManagerEx:getPercent", "lua_cc_extension_EventAssetsManagerEx_getPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:getPercent", 0, false},
        {"cc.Manifest:getManifestFileUrl", "lua_cc_extension_Manifest_getManifestFileUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getManifestFileUrl", 0, false},
        {"cc.Manifest:isVersionLoaded", "lua_cc_extension_Manifest_isVersionLoaded", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:isVersionLoaded", 0, false},
        {"cc.Manifest:isLoaded", "lua_cc_extension_Manifest_isLoaded", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:isLoaded", 0, false},
        {"cc.Manifest:getPackageUrl", "lua_cc_extension_Manifest_getPackageUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getPackageUrl", 0, false},
        {"cc.Manifest:getVersion", "lua_cc_extension_Manifest_getVersion", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getVersion", 0, false},
        {"cc.Manifest:getVersionFileUrl", "lua_cc_extension_Manifest_getVersionFileUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getVersionFileUrl", 0, false},
        {"cc.Manifest:getSearchPaths", "lua_cc_extension_Manifest_getSearchPaths", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Manifest:getSearchPaths", 0, false},
        {"cc.AssetsManagerEx:getState", "lua_cc_extension_AssetsManagerEx_getState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getState", 0, false},
        {"cc.AssetsManagerEx:getMaxConcurrentTask", "lua_cc_extension_AssetsManagerEx_getMaxConcurrentTask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getMaxConcurrentTask", 0, false},
        {"cc.AssetsManagerEx:checkUpdate", "lua_cc_extension_AssetsManagerEx_checkUpdate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:checkUpdate", 0, false},
        {"cc.AssetsManagerEx:getStoragePath", "lua_cc_extension_AssetsManagerEx_getStoragePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getStoragePath", 0, false},
        {"cc.AssetsManagerEx:update", "lua_cc_extension_AssetsManagerEx_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:update", 0, false},
        {"cc.AssetsManagerEx:setMaxConcurrentTask", "lua_cc_extension_AssetsManagerEx_setMaxConcurrentTask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:setMaxConcurrentTask", 1, false},
        {"cc.AssetsManagerEx:getLocalManifest", "lua_cc_extension_AssetsManagerEx_getLocalManifest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getLocalManifest", 0, false},
        {"cc.AssetsManagerEx:getRemoteManifest", "lua_cc_extension_AssetsManagerEx_getRemoteManifest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getRemoteManifest", 0, false},
        {"cc.AssetsManagerEx:downloadFailedAssets", "lua_cc_extension_AssetsManagerEx_downloadFailedAssets", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:downloadFailedAssets", 0, false},
        {"cc.AssetsManagerEx:create", "lua_cc_extension_AssetsManagerEx_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManagerEx:create", 2, false},
        {"cc.ParticleSystem3D:removeAffector", "lua_cc_extension_ParticleSystem3D_removeAffector", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:removeAffector", 1, false},
        {"cc.ParticleSystem3D:resumeParticleSystem", "lua_cc_extension_ParticleSystem3D_resumeParticleSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:resumeParticleSystem", 0, false},
        {"cc.ParticleSystem3D:removeAllAffector", "lua_cc_extension_ParticleSystem3D_removeAllAffector", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:removeAllAffector", 0, false},
        {"cc.ParticleSystem3D:addAffector", "lua_cc_extension_ParticleSystem3D_addAffector", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:addAffector", 1, false},
        {"cc.ParticleSystem3D:startParticleSystem", "lua_cc_extension_ParticleSystem3D_startParticleSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:startParticleSystem", 0, false},
        {"cc.ParticleSystem3D:isEnabled", "lua_cc_extension_ParticleSystem3D_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:isEnabled", 0, false},
        {"cc.ParticleSystem3D:getRender", "lua_cc_extension_ParticleSystem3D_getRender", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getRender", 0, false},
        {"cc.ParticleSystem3D:setEmitter", "lua_cc_extension_ParticleSystem3D_setEmitter", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setEmitter", 1, false},
        {"cc.ParticleSystem3D:isKeepLocal", "lua_cc_extension_ParticleSystem3D_isKeepLocal", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:isKeepLocal", 0, false},
        {"cc.ParticleSystem3D:setEnabled", "lua_cc_extension_ParticleSystem3D_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setEnabled", 1, false},
        {"cc.ParticleSystem3D:getParticleQuota", "lua_cc_extension_ParticleSystem3D_getParticleQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getParticleQuota", 0, false},
        {"cc.ParticleSystem3D:getBlendFunc", "lua_cc_extension_ParticleSystem3D_getBlendFunc", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getBlendFunc", 0, false},
        {"cc.ParticleSystem3D:pauseParticleSystem", "lua_cc_extension_ParticleSystem3D_pauseParticleSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:pauseParticleSystem", 0, false},
        {"cc.ParticleSystem3D:getState", "lua_cc_extension_ParticleSystem3D_getState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getState", 0, false},
        {"cc.ParticleSystem3D:getAliveParticleCount", "lua_cc_extension_ParticleSystem3D_getAliveParticleCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getAliveParticleCount", 0, false},
        {"cc.ParticleSystem3D:setParticleQuota", "lua_cc_extension_ParticleSystem3D_setParticleQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setParticleQuota", 1, false},
        {"cc.ParticleSystem3D:setRender", "lua_cc_extension_ParticleSystem3D_setRender", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setRender", 1, false},
        {"cc.ParticleSystem3D:stopParticleSystem", "lua_cc_extension_ParticleSystem3D_stopParticleSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:stopParticleSystem", 0, false},
        {"cc.ParticleSystem3D:setKeepLocal", "lua_cc_extension_ParticleSystem3D_setKeepLocal", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setKeepLocal", 1, false},
        {"cc.PUParticleSystem3D:initWithFilePath", "lua_cc_extension_PUParticleSystem3D_initWithFilePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:initWithFilePath", 1, false},
        {"cc.PUParticleSystem3D:getParticleSystemScaleVelocity", "lua_cc_extension_PUParticleSystem3D_getParticleSystemScaleVelocity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getParticleSystemScaleVelocity", 0, false},
        {"cc.PUParticleSystem3D:setEmittedSystemQuota", "lua_cc_extension_PUParticleSystem3D_setEmittedSystemQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setEmittedSystemQuota", 1, false},
        {"cc.PUParticleSystem3D:getDefaultDepth", "lua_cc_extension_PUParticleSystem3D_getDefaultDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getDefaultDepth", 0, false},
        {"cc.PUParticleSystem3D:getEmittedSystemQuota", "lua_cc_extension_PUParticleSystem3D_getEmittedSystemQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getEmittedSystemQuota", 0, false},
        {"cc.PUParticleSystem3D:initWithFilePathAndMaterialPath", "lua_cc_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:initWithFilePathAndMaterialPath", 2, false},
        {"cc.PUParticleSystem3D:clearAllParticles", "lua_cc_extension_PUParticleSystem3D_clearAllParticles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:clearAllParticles", 0, false},
        {"cc.PUParticleSystem3D:getMaterialName", "lua_cc_extension_PUParticleSystem3D_getMaterialName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getMaterialName", 0, false},
        {"cc.PUParticleSystem3D:calulateRotationOffset", "lua_cc_extension_PUParticleSystem3D_calulateRotationOffset", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:calulateRotationOffset", 0, false},
        {"cc.PUParticleSystem3D:getMaxVelocity", "lua_cc_extension_PUParticleSystem3D_getMaxVelocity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getMaxVelocity", 0, false},
        {"cc.PUParticleSystem3D:forceUpdate", "lua_cc_extension_PUParticleSystem3D_forceUpdate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:forceUpdate", 1, false},
        {"cc.PUParticleSystem3D:getTimeElapsedSinceStart", "lua_cc_extension_PUParticleSystem3D_getTimeElapsedSinceStart", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getTimeElapsedSinceStart", 0, false},
        {"cc.PUParticleSystem3D:removeAllBehaviourTemplate", "lua_cc_extension_PUParticleSystem3D_removeAllBehaviourTemplate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:removeAllBehaviourTemplate", 0, false},
        {"cc.PUParticleSystem3D:getEmittedEmitterQuota", "lua_cc_extension_PUParticleSystem3D_getEmittedEmitterQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getEmittedEmitterQuota", 0, false},
        {"cc.PUParticleSystem3D:forceEmission", "lua_cc_extension_PUParticleSystem3D_forceEmission", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:forceEmission", 2, false},
        {"cc.PUParticleSystem3D:addListener", "lua_cc_extension_PUParticleSystem3D_addListener", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:addListener", 1, false},
        {"cc.PUParticleSystem3D:isMarkedForEmission", "lua_cc_extension_PUParticleSystem3D_isMarkedForEmission", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:isMarkedForEmission", 0, false},
        {"cc.PUParticleSystem3D:getDefaultWidth", "lua_cc_extension_PUParticleSystem3D_getDefaultWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getDefaultWidth", 0, false},
        {"cc.PUParticleSystem3D:setEmittedEmitterQuota", "lua_cc_extension_PUParticleSystem3D_setEmittedEmitterQuota", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setEmittedEmitterQuota", 1, false},
        {"cc.PUParticleSystem3D:setMarkedForEmission", "lua_cc_extension_PUParticleSystem3D_setMarkedForEmission", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setMarkedForEmission", 1, false},
        {"cc.PUParticleSystem3D:clone", "lua_cc_extension_PUParticleSystem3D_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:clone", 0, false},
        {"cc.PUParticleSystem3D:addEmitter", "lua_cc_extension_PUParticleSystem3D_addEmitter", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:addEmitter", 1, false},
        {"cc.PUParticleSystem3D:addBehaviourTemplate", "lua_cc_extension_PUParticleSystem3D_addBehaviourTemplate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:addBehaviourTemplate", 1, false},
        {"cc.PUParticleSystem3D:setDefaultWidth", "lua_cc_extension_PUParticleSystem3D_setDefaultWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setDefaultWidth", 1, false},
        {"cc.PUParticleSystem3D:copyAttributesTo", "lua_cc_extension_PUParticleSystem3D_copyAttributesTo", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:copyAttributesTo", 1, false},
        {"cc.PUParticleSystem3D:setMaterialName", "lua_cc_extension_PUParticleSystem3D_setMaterialName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setMaterialName", 1, false},
        {"cc.PUParticleSystem3D:getParentParticleSystem", "lua_cc_extension_PUParticleSystem3D_getParentParticleSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getParentParticleSystem", 0, false},
        {"cc.PUParticleSystem3D:removeListener", "lua_cc_extension_PUParticleSystem3D_removeListener", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:removeListener", 1, false},
        {"cc.PUParticleSystem3D:setMaxVelocity", "lua_cc_extension_PUParticleSystem3D_setMaxVelocity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setMaxVelocity", 1, false},
        {"cc.PUParticleSystem3D:getDefaultHeight", "lua_cc_extension_PUParticleSystem3D_getDefaultHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getDefaultHeight", 0, false},
        {"cc.PUParticleSystem3D:getDerivedPosition", "lua_cc_extension_PUParticleSystem3D_getDerivedPosition", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getDerivedPosition", 0, false},
        {"cc.PUParticleSystem3D:removeAllEmitter", "lua_cc_extension_PUParticleSystem3D_removeAllEmitter", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:removeAllEmitter", 0, false},
        {"cc.PUParticleSystem3D:setParticleSystemScaleVelocity", "lua_cc_extension_PUParticleSystem3D_setParticleSystemScaleVelocity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setParticleSystemScaleVelocity", 1, false},
        {"cc.PUParticleSystem3D:getDerivedScale", "lua_cc_extension_PUParticleSystem3D_getDerivedScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:getDerivedScale", 0, false},
        {"cc.PUParticleSystem3D:setDefaultHeight", "lua_cc_extension_PUParticleSystem3D_setDefaultHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setDefaultHeight", 1, false},
        {"cc.PUParticleSystem3D:removeAllListener", "lua_cc_extension_PUParticleSystem3D_removeAllListener", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:removeAllListener", 0, false},
        {"cc.PUParticleSystem3D:initSystem", "lua_cc_extension_PUParticleSystem3D_initSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:initSystem", 1, false},
        {"cc.PUParticleSystem3D:makeParticleLocal", "lua_cc_extension_PUParticleSystem3D_makeParticleLocal", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:makeParticleLocal", 1, false},
        {"cc.PUParticleSystem3D:removerAllObserver", "lua_cc_extension_PUParticleSystem3D_removerAllObserver", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:removerAllObserver", 0, false},
        {"cc.PUParticleSystem3D:setDefaultDepth", "lua_cc_extension_PUParticleSystem3D_setDefaultDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:setDefaultDepth", 1, false},
        {"cc.PUParticleSystem3D:addObserver", "lua_cc_extension_PUParticleSystem3D_addObserver", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:addObserver", 1, false},
        {"cc.PUParticleSystem3D:create", "lua_cc_extension_PUParticleSystem3D_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.PUParticleSystem3D:create", 2, true},
        {"cc.EventListenerAssetsManagerEx:create", "cclua_Extension_EventListenerAssetsManagerEx_create", "%s has wrong number of arguments: %d, was expecting %d \n", "create", 2, false},
    };
    for (const auto& e : errors) if (std::strcmp(name, e.name) == 0) {
        if (attempted != -1 && !e.overload) {
            if (std::strcmp(name, "cc.EventListenerAssetsManagerEx:create") == 0) {
                tolua_Error error{};
                tolua_error(L, "#ferror in function 'cclua_Extension_EventListenerAssetsManagerEx_create'.", &error);
            } else {
                char text[256];
                std::snprintf(text, sizeof(text), "invalid arguments in function '%s'", e.native);
                tolua_error(L, text, nullptr);
            }
            return 0;
        }
        return luaL_error(L, e.format, e.label, argc, e.expected);
    }
    return luaL_error(L, "unmapped Extension binding: %s", name);
}
}

#undef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	extension_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, true); \
	const auto* extension_self = tolua_tousertype(lua_S, 1, nullptr); \
	(void)extension_self; \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = true; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	extension_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, false); \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = false; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto extension_fn = (Fn_); \
		arg_cur = 0; \
		if (extension_binding::prepare(lua_S, LUA_FNAME, extension_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, extension_fn, &native_results); \
			if (ok) { lua_settop(lua_S, 1); return 1; } \
		} \
	}

#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto extension_fn = (Fn_); \
		arg_cur = 0; \
		if (extension_binding::prepare(lua_S, LUA_FNAME, extension_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, extension_fn, &native_results); \
			if (ok) { return native_results; } \
		} \
	}

#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    return extension_binding::fail(lua_S, LUA_FNAME, argc, arg_cur);
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)
