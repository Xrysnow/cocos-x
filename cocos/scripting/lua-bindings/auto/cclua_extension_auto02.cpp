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

int lua_cocos2d_extension_EventListenerAssetsManagerEx_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerAssetsManagerEx", "cc.EventListenerAssetsManagerEx:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::extension::EventListenerAssetsManagerEx*(*)(cocos2d::extension::AssetsManagerEx*, const std::function<void (cocos2d::extension::EventAssetsManagerEx *)>&)>(&cocos2d::extension::EventListenerAssetsManagerEx::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Extension_ccEventListenerAssetsManagerEx(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::extension::EventListenerAssetsManagerEx, "EventListenerAssetsManagerEx", "cc.EventListenerAssetsManagerEx",
		cocos2d::EventListenerCustom, "cc.EventListenerCustom",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_extension_EventListenerAssetsManagerEx_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSystem3D_addAffector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:addAffector");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(cocos2d::Particle3DAffector*)>(&cocos2d::ParticleSystem3D::addAffector));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_getAliveParticleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getAliveParticleCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ParticleSystem3D::*)()const>(&cocos2d::ParticleSystem3D::getAliveParticleCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_getParticleQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getParticleQuota");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::ParticleSystem3D::*)()const>(&cocos2d::ParticleSystem3D::getParticleQuota));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_getRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getRender");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Particle3DRender*(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::getRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_getState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:getState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSystem3D::State(cocos2d::ParticleSystem3D::*)()const>(&cocos2d::ParticleSystem3D::getState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem3D::*)()const>(&cocos2d::ParticleSystem3D::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_isKeepLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:isKeepLocal");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem3D::*)()const>(&cocos2d::ParticleSystem3D::isKeepLocal));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_pauseParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:pauseParticleSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::pauseParticleSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_removeAffector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:removeAffector");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(int)>(&cocos2d::ParticleSystem3D::removeAffector));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_removeAllAffector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:removeAllAffector");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::removeAllAffector));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_resumeParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:resumeParticleSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::resumeParticleSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_setEmitter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setEmitter");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(cocos2d::Particle3DEmitter*)>(&cocos2d::ParticleSystem3D::setEmitter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(bool)>(&cocos2d::ParticleSystem3D::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_setKeepLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setKeepLocal");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(bool)>(&cocos2d::ParticleSystem3D::setKeepLocal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_setParticleQuota(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setParticleQuota");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(unsigned int)>(&cocos2d::ParticleSystem3D::setParticleQuota));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_setRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:setRender");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem3D::*)(cocos2d::Particle3DRender*)>(&cocos2d::ParticleSystem3D::setRender));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem3D_startParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:startParticleSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::startParticleSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem3D_stopParticleSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem3D", "cc.ParticleSystem3D:stopParticleSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem3D::*)()>(&cocos2d::ParticleSystem3D::stopParticleSystem));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Extension_ccParticleSystem3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSystem3D, "ParticleSystem3D", "cc.ParticleSystem3D",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addAffector", lua_cocos2d_ParticleSystem3D_addAffector);
	LUA_METHOD("getAliveParticleCount", lua_cocos2d_ParticleSystem3D_getAliveParticleCount);
	LUA_METHOD("getParticleQuota", lua_cocos2d_ParticleSystem3D_getParticleQuota);
	LUA_METHOD("getRender", lua_cocos2d_ParticleSystem3D_getRender);
	LUA_METHOD("getState", lua_cocos2d_ParticleSystem3D_getState);
	LUA_METHOD("isEnabled", lua_cocos2d_ParticleSystem3D_isEnabled);
	LUA_METHOD("isKeepLocal", lua_cocos2d_ParticleSystem3D_isKeepLocal);
	LUA_METHOD("pauseParticleSystem", lua_cocos2d_ParticleSystem3D_pauseParticleSystem);
	LUA_METHOD("removeAffector", lua_cocos2d_ParticleSystem3D_removeAffector);
	LUA_METHOD("removeAllAffector", lua_cocos2d_ParticleSystem3D_removeAllAffector);
	LUA_METHOD("resumeParticleSystem", lua_cocos2d_ParticleSystem3D_resumeParticleSystem);
	LUA_METHOD("setEmitter", lua_cocos2d_ParticleSystem3D_setEmitter);
	LUA_METHOD("setEnabled", lua_cocos2d_ParticleSystem3D_setEnabled);
	LUA_METHOD("setKeepLocal", lua_cocos2d_ParticleSystem3D_setKeepLocal);
	LUA_METHOD("setParticleQuota", lua_cocos2d_ParticleSystem3D_setParticleQuota);
	LUA_METHOD("setRender", lua_cocos2d_ParticleSystem3D_setRender);
	LUA_METHOD("startParticleSystem", lua_cocos2d_ParticleSystem3D_startParticleSystem);
	LUA_METHOD("stopParticleSystem", lua_cocos2d_ParticleSystem3D_stopParticleSystem);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
