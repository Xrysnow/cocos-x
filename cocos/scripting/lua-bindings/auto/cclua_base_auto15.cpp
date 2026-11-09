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

int lua_cocos2d_ParticleFireworks_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleFireworks::*)()>(&cocos2d::ParticleFireworks::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleFireworks_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleFireworks::*)(int)>(&cocos2d::ParticleFireworks::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleFireworks, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleFireworks_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleFireworks_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleFireworks_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFireworks_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSun_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSun::*)()>(&cocos2d::ParticleSun::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSun_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSun::*)(int)>(&cocos2d::ParticleSun::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleSun, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleSun_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleSun_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleSun_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSun_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleGalaxy_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleGalaxy::*)()>(&cocos2d::ParticleGalaxy::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleGalaxy_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleGalaxy::*)(int)>(&cocos2d::ParticleGalaxy::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleGalaxy, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleGalaxy_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleGalaxy_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleGalaxy_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleGalaxy_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleFlower_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleFlower::*)()>(&cocos2d::ParticleFlower::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleFlower_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleFlower::*)(int)>(&cocos2d::ParticleFlower::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleFlower, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleFlower_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleFlower_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleFlower_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFlower_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleMeteor_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleMeteor::*)()>(&cocos2d::ParticleMeteor::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleMeteor_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleMeteor::*)(int)>(&cocos2d::ParticleMeteor::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleMeteor, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleMeteor_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleMeteor_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleMeteor_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleMeteor_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSpiral_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSpiral::*)()>(&cocos2d::ParticleSpiral::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSpiral_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSpiral::*)(int)>(&cocos2d::ParticleSpiral::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleSpiral, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleSpiral_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleSpiral_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleSpiral_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSpiral_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleExplosion_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleExplosion::*)()>(&cocos2d::ParticleExplosion::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleExplosion_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleExplosion::*)(int)>(&cocos2d::ParticleExplosion::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleExplosion, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleExplosion_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleExplosion_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleExplosion_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleExplosion_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSmoke_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSmoke::*)()>(&cocos2d::ParticleSmoke::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSmoke_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSmoke::*)(int)>(&cocos2d::ParticleSmoke::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleSmoke, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleSmoke_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleSmoke_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleSmoke_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSmoke_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSnow_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSnow::*)()>(&cocos2d::ParticleSnow::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSnow_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSnow::*)(int)>(&cocos2d::ParticleSnow::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleSnow, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleSnow_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleSnow_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleSnow_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSnow_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleRain_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleRain::*)()>(&cocos2d::ParticleRain::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleRain_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleRain::*)(int)>(&cocos2d::ParticleRain::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleRain, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ParticleRain_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleRain_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cocos2d_ParticleRain_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleRain_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProgressTimer_getBarChangeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getBarChangeRate");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getBarChangeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getMidpoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getMidpoint");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getMidpoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getPercentage");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getPercentage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getSprite");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getSprite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ProgressTimer::Type(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_initWithSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:initWithSprite");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ProgressTimer::*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::initWithSprite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_isReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:isReverseDirection");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ProgressTimer::*)()>(&cocos2d::ProgressTimer::isReverseDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_setBarChangeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setBarChangeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(const cocos2d::Vec2&)>(&cocos2d::ProgressTimer::setBarChangeRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setMidpoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setMidpoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(const cocos2d::Vec2&)>(&cocos2d::ProgressTimer::setMidpoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setPercentage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(float)>(&cocos2d::ProgressTimer::setPercentage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setReverseDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(bool)>(&cocos2d::ProgressTimer::setReverseDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setSprite");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::setSprite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(cocos2d::ProgressTimer::Type)>(&cocos2d::ProgressTimer::setType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ProgressTimer*(*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccProgressTimer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressTimer, "ProgressTimer", "cc.ProgressTimer",
		cocos2d::ProgressTimer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBarChangeRate", lua_cocos2d_ProgressTimer_getBarChangeRate);
	LUA_METHOD("getMidpoint", lua_cocos2d_ProgressTimer_getMidpoint);
	LUA_METHOD("getPercentage", lua_cocos2d_ProgressTimer_getPercentage);
	LUA_METHOD("getSprite", lua_cocos2d_ProgressTimer_getSprite);
	LUA_METHOD("getType", lua_cocos2d_ProgressTimer_getType);
	LUA_METHOD("initWithSprite", lua_cocos2d_ProgressTimer_initWithSprite);
	LUA_METHOD("isReverseDirection", lua_cocos2d_ProgressTimer_isReverseDirection);
	LUA_METHOD("setBarChangeRate", lua_cocos2d_ProgressTimer_setBarChangeRate);
	LUA_METHOD("setMidpoint", lua_cocos2d_ProgressTimer_setMidpoint);
	LUA_METHOD("setPercentage", lua_cocos2d_ProgressTimer_setPercentage);
	LUA_METHOD("setReverseDirection", lua_cocos2d_ProgressTimer_setReverseDirection);
	LUA_METHOD("setSprite", lua_cocos2d_ProgressTimer_setSprite);
	LUA_METHOD("setType", lua_cocos2d_ProgressTimer_setType);
	LUA_METHOD("create", lua_cocos2d_ProgressTimer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProtectedNode_addProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:addProtectedChild");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int, int)>(&cocos2d::ProtectedNode::addProtectedChild)));
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int)>(&cocos2d::ProtectedNode::addProtectedChild)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*)>(&cocos2d::ProtectedNode::addProtectedChild));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_ProtectedNode_disableCascadeColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:disableCascadeColor");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::disableCascadeColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_disableCascadeOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:disableCascadeOpacity");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::disableCascadeOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_getProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:getProtectedChildByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::ProtectedNode::*)(int)>(&cocos2d::ProtectedNode::getProtectedChildByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProtectedNode_removeAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildren");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::removeAllProtectedChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_removeAllProtectedChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProtectedNode::*)(bool)>(&cocos2d::ProtectedNode::removeAllProtectedChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProtectedNode_removeProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, bool)>(&cocos2d::ProtectedNode::removeProtectedChild)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ProtectedNode* obj,cocos2d::Node* arg0){{return obj->removeProtectedChild(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ProtectedNode_removeProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChildByTag");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ProtectedNode::*)(int, bool)>(&cocos2d::ProtectedNode::removeProtectedChildByTag)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ProtectedNode* obj,int arg0){{return obj->removeProtectedChildByTag(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ProtectedNode_reorderProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:reorderProtectedChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int)>(&cocos2d::ProtectedNode::reorderProtectedChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ProtectedNode_sortAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:sortAllProtectedChildren");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::sortAllProtectedChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ProtectedNode*(*)()>(&cocos2d::ProtectedNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccProtectedNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProtectedNode, "ProtectedNode", "cc.ProtectedNode",
		cocos2d::ProtectedNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addProtectedChild", lua_cocos2d_ProtectedNode_addProtectedChild);
	LUA_METHOD("disableCascadeColor", lua_cocos2d_ProtectedNode_disableCascadeColor);
	LUA_METHOD("disableCascadeOpacity", lua_cocos2d_ProtectedNode_disableCascadeOpacity);
	LUA_METHOD("getProtectedChildByTag", lua_cocos2d_ProtectedNode_getProtectedChildByTag);
	LUA_METHOD("removeAllProtectedChildren", lua_cocos2d_ProtectedNode_removeAllProtectedChildren);
	LUA_METHOD("removeAllProtectedChildrenWithCleanup", lua_cocos2d_ProtectedNode_removeAllProtectedChildrenWithCleanup);
	LUA_METHOD("removeProtectedChild", lua_cocos2d_ProtectedNode_removeProtectedChild);
	LUA_METHOD("removeProtectedChildByTag", lua_cocos2d_ProtectedNode_removeProtectedChildByTag);
	LUA_METHOD("reorderProtectedChild", lua_cocos2d_ProtectedNode_reorderProtectedChild);
	LUA_METHOD("sortAllProtectedChildren", lua_cocos2d_ProtectedNode_sortAllProtectedChildren);
	LUA_METHOD("create", lua_cocos2d_ProtectedNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
