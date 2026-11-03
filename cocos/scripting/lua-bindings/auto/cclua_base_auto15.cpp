#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_ParticleSystemQuad_listenRendererRecreated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:listenRendererRecreated");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::EventCustom*)>(&cocos2d::ParticleSystemQuad::listenRendererRecreated));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystemQuad_setDisplayFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:setDisplayFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::SpriteFrame*)>(&cocos2d::ParticleSystemQuad::setDisplayFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystemQuad_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSystemQuad*(*)(int)>(&cocos2d::ParticleSystemQuad::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSystemQuad(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSystemQuad, "ParticleSystemQuad", "cc.ParticleSystemQuad",
		cocos2d::ParticleSystem, "cc.ParticleSystem",
		nullptr, nullptr);
	LUA_METHOD("listenRendererRecreated", lua_cocos2d_ParticleSystemQuad_listenRendererRecreated);
	LUA_METHOD("setDisplayFrame", lua_cocos2d_ParticleSystemQuad_setDisplayFrame);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSystemQuad_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleFire_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFire", "cc.ParticleFire:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleFire*(*)()>(&cocos2d::ParticleFire::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleFire_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFire", "cc.ParticleFire:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleFire*(*)(int)>(&cocos2d::ParticleFire::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFire(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleFire, "ParticleFire", "cc.ParticleFire",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleFire_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFire_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleFireworks_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleFireworks*(*)()>(&cocos2d::ParticleFireworks::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleFireworks_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleFireworks*(*)(int)>(&cocos2d::ParticleFireworks::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFireworks(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleFireworks, "ParticleFireworks", "cc.ParticleFireworks",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleFireworks_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFireworks_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSun_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSun*(*)()>(&cocos2d::ParticleSun::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSun_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSun*(*)(int)>(&cocos2d::ParticleSun::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSun(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSun, "ParticleSun", "cc.ParticleSun",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleSun_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSun_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleGalaxy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleGalaxy*(*)()>(&cocos2d::ParticleGalaxy::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleGalaxy_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleGalaxy*(*)(int)>(&cocos2d::ParticleGalaxy::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleGalaxy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleGalaxy, "ParticleGalaxy", "cc.ParticleGalaxy",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleGalaxy_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleGalaxy_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleFlower_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleFlower*(*)()>(&cocos2d::ParticleFlower::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleFlower_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleFlower*(*)(int)>(&cocos2d::ParticleFlower::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFlower(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleFlower, "ParticleFlower", "cc.ParticleFlower",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleFlower_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFlower_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleMeteor_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleMeteor*(*)()>(&cocos2d::ParticleMeteor::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleMeteor_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleMeteor*(*)(int)>(&cocos2d::ParticleMeteor::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleMeteor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleMeteor, "ParticleMeteor", "cc.ParticleMeteor",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleMeteor_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleMeteor_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSpiral_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSpiral*(*)()>(&cocos2d::ParticleSpiral::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSpiral_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSpiral*(*)(int)>(&cocos2d::ParticleSpiral::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSpiral(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSpiral, "ParticleSpiral", "cc.ParticleSpiral",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleSpiral_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSpiral_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleExplosion_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleExplosion*(*)()>(&cocos2d::ParticleExplosion::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleExplosion_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleExplosion*(*)(int)>(&cocos2d::ParticleExplosion::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleExplosion(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleExplosion, "ParticleExplosion", "cc.ParticleExplosion",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleExplosion_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleExplosion_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSmoke_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSmoke*(*)()>(&cocos2d::ParticleSmoke::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSmoke_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSmoke*(*)(int)>(&cocos2d::ParticleSmoke::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSmoke(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSmoke, "ParticleSmoke", "cc.ParticleSmoke",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleSmoke_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSmoke_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSnow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSnow*(*)()>(&cocos2d::ParticleSnow::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSnow_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSnow*(*)(int)>(&cocos2d::ParticleSnow::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSnow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSnow, "ParticleSnow", "cc.ParticleSnow",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleSnow_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSnow_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleRain_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleRain*(*)()>(&cocos2d::ParticleRain::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleRain_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleRain*(*)(int)>(&cocos2d::ParticleRain::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleRain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleRain, "ParticleRain", "cc.ParticleRain",
		cocos2d::ParticleSystemQuad, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleRain_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleRain_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
