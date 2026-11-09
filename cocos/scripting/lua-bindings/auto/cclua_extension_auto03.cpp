#include "cclua_extension_auto.hpp"
#include "scripting/lua-bindings/manual/extension/cclua_extension_conversions.h"
#include "assets-manager/AssetsManager.h"
#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/Manifest.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

int lua_cocos2d_PUParticleSystem3D_calulateRotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:calulateRotationOffset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::calulateRotationOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_clearAllParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:clearAllParticles");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::clearAllParticles));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PUParticleSystem3D*(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_copyAttributesTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:copyAttributesTo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(cocos2d::PUParticleSystem3D*)>(&cocos2d::PUParticleSystem3D::copyAttributesTo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_forceUpdate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:forceUpdate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(float)>(&cocos2d::PUParticleSystem3D::forceUpdate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_getDefaultDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultDepth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getDefaultDepth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getDefaultHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getDefaultHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getDefaultWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDefaultWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getDefaultWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getDerivedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDerivedPosition");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::getDerivedPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getDerivedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getDerivedScale");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::getDerivedScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getEmittedEmitterQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getEmittedEmitterQuota");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getEmittedEmitterQuota));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getEmittedSystemQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getEmittedSystemQuota");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getEmittedSystemQuota));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getMaterialName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getMaterialName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getMaterialName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getMaxVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getMaxVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getMaxVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getParentParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getParentParticleSystem");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PUParticleSystem3D*(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getParentParticleSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getParticleSystemScaleVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getParticleSystemScaleVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getParticleSystemScaleVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_getTimeElapsedSinceStart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:getTimeElapsedSinceStart");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::getTimeElapsedSinceStart));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_initSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initSystem");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::PUParticleSystem3D::*)(std::string_view)>(&cocos2d::PUParticleSystem3D::initSystem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_initWithFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initWithFilePath");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::PUParticleSystem3D::*)(std::string_view)>(&cocos2d::PUParticleSystem3D::initWithFilePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_initWithFilePathAndMaterialPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:initWithFilePathAndMaterialPath");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::PUParticleSystem3D::*)(std::string_view, std::string_view)>(&cocos2d::PUParticleSystem3D::initWithFilePathAndMaterialPath)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_PUParticleSystem3D_isMarkedForEmission(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:isMarkedForEmission");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PUParticleSystem3D::*)()const>(&cocos2d::PUParticleSystem3D::isMarkedForEmission));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_removeAllBehaviourTemplate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllBehaviourTemplate");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::removeAllBehaviourTemplate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_removeAllEmitter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllEmitter");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::removeAllEmitter));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_removeAllListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removeAllListener");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::removeAllListener));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_removerAllObserver(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:removerAllObserver");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PUParticleSystem3D::*)()>(&cocos2d::PUParticleSystem3D::removerAllObserver));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PUParticleSystem3D_rotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:rotationOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(cocos2d::Vec3&)>(&cocos2d::PUParticleSystem3D::rotationOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setDefaultDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultDepth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(const float)>(&cocos2d::PUParticleSystem3D::setDefaultDepth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setDefaultHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(const float)>(&cocos2d::PUParticleSystem3D::setDefaultHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setDefaultWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setDefaultWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(const float)>(&cocos2d::PUParticleSystem3D::setDefaultWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setEmittedEmitterQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setEmittedEmitterQuota");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(unsigned int)>(&cocos2d::PUParticleSystem3D::setEmittedEmitterQuota));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setEmittedSystemQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setEmittedSystemQuota");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(unsigned int)>(&cocos2d::PUParticleSystem3D::setEmittedSystemQuota));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setMarkedForEmission(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMarkedForEmission");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(bool)>(&cocos2d::PUParticleSystem3D::setMarkedForEmission));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setMaterialName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMaterialName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(std::string_view)>(&cocos2d::PUParticleSystem3D::setMaterialName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setMaxVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setMaxVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(float)>(&cocos2d::PUParticleSystem3D::setMaxVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_setParticleSystemScaleVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:setParticleSystemScaleVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PUParticleSystem3D::*)(float)>(&cocos2d::PUParticleSystem3D::setParticleSystemScaleVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PUParticleSystem3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PUParticleSystem3D", "cc.PUParticleSystem3D:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::PUParticleSystem3D*(*)(std::string_view, std::string_view)>(&cocos2d::PUParticleSystem3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::PUParticleSystem3D*(*)(std::string_view)>(&cocos2d::PUParticleSystem3D::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PUParticleSystem3D*(*)()>(&cocos2d::PUParticleSystem3D::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int luaReg_Extension_ccPUParticleSystem3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PUParticleSystem3D, "PUParticleSystem3D", "cc.PUParticleSystem3D",
		cocos2d::PUParticleSystem3D, "cc.ParticleSystem3D",
		nullptr, nullptr);
	LUA_METHOD("calulateRotationOffset", lua_cocos2d_PUParticleSystem3D_calulateRotationOffset);
	LUA_METHOD("clearAllParticles", lua_cocos2d_PUParticleSystem3D_clearAllParticles);
	LUA_METHOD("clone", lua_cocos2d_PUParticleSystem3D_clone);
	LUA_METHOD("copyAttributesTo", lua_cocos2d_PUParticleSystem3D_copyAttributesTo);
	LUA_METHOD("forceUpdate", lua_cocos2d_PUParticleSystem3D_forceUpdate);
	LUA_METHOD("getDefaultDepth", lua_cocos2d_PUParticleSystem3D_getDefaultDepth);
	LUA_METHOD("getDefaultHeight", lua_cocos2d_PUParticleSystem3D_getDefaultHeight);
	LUA_METHOD("getDefaultWidth", lua_cocos2d_PUParticleSystem3D_getDefaultWidth);
	LUA_METHOD("getDerivedPosition", lua_cocos2d_PUParticleSystem3D_getDerivedPosition);
	LUA_METHOD("getDerivedScale", lua_cocos2d_PUParticleSystem3D_getDerivedScale);
	LUA_METHOD("getEmittedEmitterQuota", lua_cocos2d_PUParticleSystem3D_getEmittedEmitterQuota);
	LUA_METHOD("getEmittedSystemQuota", lua_cocos2d_PUParticleSystem3D_getEmittedSystemQuota);
	LUA_METHOD("getMaterialName", lua_cocos2d_PUParticleSystem3D_getMaterialName);
	LUA_METHOD("getMaxVelocity", lua_cocos2d_PUParticleSystem3D_getMaxVelocity);
	LUA_METHOD("getParentParticleSystem", lua_cocos2d_PUParticleSystem3D_getParentParticleSystem);
	LUA_METHOD("getParticleSystemScaleVelocity", lua_cocos2d_PUParticleSystem3D_getParticleSystemScaleVelocity);
	LUA_METHOD("getTimeElapsedSinceStart", lua_cocos2d_PUParticleSystem3D_getTimeElapsedSinceStart);
	LUA_METHOD("initSystem", lua_cocos2d_PUParticleSystem3D_initSystem);
	LUA_METHOD("initWithFilePath", lua_cocos2d_PUParticleSystem3D_initWithFilePath);
	LUA_METHOD("initWithFilePathAndMaterialPath", lua_cocos2d_PUParticleSystem3D_initWithFilePathAndMaterialPath);
	LUA_METHOD("isMarkedForEmission", lua_cocos2d_PUParticleSystem3D_isMarkedForEmission);
	LUA_METHOD("removeAllBehaviourTemplate", lua_cocos2d_PUParticleSystem3D_removeAllBehaviourTemplate);
	LUA_METHOD("removeAllEmitter", lua_cocos2d_PUParticleSystem3D_removeAllEmitter);
	LUA_METHOD("removeAllListener", lua_cocos2d_PUParticleSystem3D_removeAllListener);
	LUA_METHOD("removerAllObserver", lua_cocos2d_PUParticleSystem3D_removerAllObserver);
	LUA_METHOD("rotationOffset", lua_cocos2d_PUParticleSystem3D_rotationOffset);
	LUA_METHOD("setDefaultDepth", lua_cocos2d_PUParticleSystem3D_setDefaultDepth);
	LUA_METHOD("setDefaultHeight", lua_cocos2d_PUParticleSystem3D_setDefaultHeight);
	LUA_METHOD("setDefaultWidth", lua_cocos2d_PUParticleSystem3D_setDefaultWidth);
	LUA_METHOD("setEmittedEmitterQuota", lua_cocos2d_PUParticleSystem3D_setEmittedEmitterQuota);
	LUA_METHOD("setEmittedSystemQuota", lua_cocos2d_PUParticleSystem3D_setEmittedSystemQuota);
	LUA_METHOD("setMarkedForEmission", lua_cocos2d_PUParticleSystem3D_setMarkedForEmission);
	LUA_METHOD("setMaterialName", lua_cocos2d_PUParticleSystem3D_setMaterialName);
	LUA_METHOD("setMaxVelocity", lua_cocos2d_PUParticleSystem3D_setMaxVelocity);
	LUA_METHOD("setParticleSystemScaleVelocity", lua_cocos2d_PUParticleSystem3D_setParticleSystemScaleVelocity);
	LUA_METHOD("create", lua_cocos2d_PUParticleSystem3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
