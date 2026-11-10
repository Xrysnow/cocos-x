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

int lua_cocos2d_ParticleSystem_addAnimationIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addAnimationIndex");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ParticleSystem::*)(unsigned short, cocos2d::Rect, bool)>(&cocos2d::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cocos2d::ParticleSystem* obj,unsigned short arg0,cocos2d::Rect arg1){{return obj->addAnimationIndex(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ParticleSystem::*)(unsigned short, cocos2d::SpriteFrame*)>(&cocos2d::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ParticleSystem::*)(unsigned short, std::string_view)>(&cocos2d::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cocos2d::ParticleSystem::*)(cocos2d::SpriteFrame*)>(&cocos2d::ParticleSystem::addAnimationIndex));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cocos2d::ParticleSystem::*)(std::string_view)>(&cocos2d::ParticleSystem::addAnimationIndex));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_ParticleSystem_addEmissionShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addEmissionShape");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::EmissionShape)>(&cocos2d::ParticleSystem::addEmissionShape));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_addParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addParticles");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ParticleSystem::*)(int, int, int)>(&cocos2d::ParticleSystem::addParticles)));
	LUA_TRY_INVOKE(2, ([](cocos2d::ParticleSystem* obj,int arg0,int arg1){{return obj->addParticles(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ParticleSystem* obj,int arg0){{return obj->addParticles(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_ParticleSystem_getAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAngleVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAngleVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAtlasIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAtlasIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getBatchNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleBatchNode*(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getBatchNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEmissionRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEmissionRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEmissionRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEmitterMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEmitterMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSystem::Mode(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEmitterMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndColorVar");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndColorVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndRadiusVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndRadiusVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSizeVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSizeVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSpin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSpin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getEndSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSpinVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSpinVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getFixedFPS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getFixedFPS");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getFixedFPS));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getGravity");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getGravity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHSV");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::HSV&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getHSV));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getHSVVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHSVVar");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::HSV&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getHSVVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getHue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHue");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getHue));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getHueVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHueVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getHueVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getLife(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getLife");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getLife));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getLifeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getLifeVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getLifeVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getParticleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getParticleCount");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getParticleCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getPosVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getPosVar");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getPosVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getPositionType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSystem::PositionType(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getPositionType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getRadialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRadialAccel");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRadialAccel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getRadialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRadialAccelVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRadialAccelVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getResourceFile");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getResourceFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getRotatePerSecond(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotatePerSecond");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotatePerSecond));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getRotatePerSecondVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotatePerSecondVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotatePerSecondVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getRotationIsDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotationIsDir");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotationIsDir));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSourcePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSourcePosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSourcePosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnAngleVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnAngleVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnFadeIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnFadeIn");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnFadeIn));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnFadeInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnFadeInVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnFadeInVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnScaleIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnScaleIn");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnScaleIn));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpawnScaleInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnScaleInVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getSpawnScaleInVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getSpeedVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpeedVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSpeedVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartColorVar");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartColorVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartRadiusVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartRadiusVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSizeVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSizeVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSpin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSpin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getStartSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSpinVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSpinVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTangentialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTangentialAccel");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTangentialAccel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTangentialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTangentialAccelVar");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTangentialAccelVar));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTimeScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getTimeScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTotalAnimationIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTotalAnimationIndices");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getTotalAnimationIndices));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_getTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTotalParticles");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTotalParticles));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_initWithDictionary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithDictionary");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ParticleSystem::*)(const cocos2d::ValueMap&, std::string_view)>(&cocos2d::ParticleSystem::initWithDictionary)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSystem::*)(const cocos2d::ValueMap&)>(&cocos2d::ParticleSystem::initWithDictionary));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ParticleSystem_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSystem::*)(std::string_view)>(&cocos2d::ParticleSystem::initWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_initWithTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_isActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isActive");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isActive));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isAnimationReversed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAnimationReversed");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isAnimationReversed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isAnimationSpeedTimescaleIndependent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAnimationSpeedTimescaleIndependent");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isAnimationSpeedTimescaleIndependent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isAutoRemoveOnFinish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAutoRemoveOnFinish");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isAutoRemoveOnFinish));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isBlendAdditive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isBlendAdditive");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isBlendAdditive));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isEmissionShapes");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isEmissionShapes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isEmitterAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isEmitterAnimated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isEmitterAnimated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isFull(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isFull");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isFull));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isHSV");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isHSV));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isLifeAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isLifeAnimated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isLifeAnimated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isLoopAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isLoopAnimated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isLoopAnimated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isPaused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isPaused");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isPaused));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_isSourcePositionCompatible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isSourcePositionCompatible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isSourcePositionCompatible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_pauseEmissions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:pauseEmissions");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::pauseEmissions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_postStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:postStep");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::postStep));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_resetAnimationDescriptors(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetAnimationDescriptors");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resetAnimationDescriptors));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_resetAnimationIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetAnimationIndices");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resetAnimationIndices));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_resetEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetEmissionShapes");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resetEmissionShapes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_resetSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resetSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_resimulate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resimulate");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystem::*)(float, float)>(&cocos2d::ParticleSystem::resimulate)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ParticleSystem* obj,float arg0){{return obj->resimulate(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, [](cocos2d::ParticleSystem* obj){{return obj->resimulate();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_ParticleSystem_resumeEmissions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resumeEmissions");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resumeEmissions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_setAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAngleVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setAngleVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setAnimationDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationDescriptor");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::ParticleSystem::*)(unsigned short, float, float, const std::vector<unsigned short>&, bool)>(&cocos2d::ParticleSystem::setAnimationDescriptor)));
	LUA_TRY_INVOKE(4, ([](cocos2d::ParticleSystem* obj,unsigned short arg0,float arg1,float arg2,const std::vector<unsigned short>& arg3){{return obj->setAnimationDescriptor(std::move(arg0),std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystem::*)(const std::vector<unsigned short>&, bool)>(&cocos2d::ParticleSystem::setAnimationDescriptor)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ParticleSystem* obj,const std::vector<unsigned short>& arg0){{return obj->setAnimationDescriptor(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,4,5");
}
int lua_cocos2d_ParticleSystem_setAnimationIndicesAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationIndicesAtlas");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystem::*)(unsigned int, cocos2d::ParticleSystem::TexAnimDir)>(&cocos2d::ParticleSystem::setAnimationIndicesAtlas)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ParticleSystem* obj,unsigned int arg0){{return obj->setAnimationIndicesAtlas(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::setAnimationIndicesAtlas));
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_ParticleSystem_setAnimationReverse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationReverse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setAnimationReverse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setAnimationSpeedTimescaleIndependent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationSpeedTimescaleIndependent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setAnimationSpeedTimescaleIndependent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAtlasIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::setAtlasIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setAutoRemoveOnFinish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAutoRemoveOnFinish");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setAutoRemoveOnFinish));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBatchNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleBatchNode*)>(&cocos2d::ParticleSystem::setBatchNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setBlendAdditive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBlendAdditive");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setBlendAdditive));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::BlendFunc&)>(&cocos2d::ParticleSystem::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setDuration");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEmissionRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEmissionRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEmissionShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionShape");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystem::*)(unsigned short, cocos2d::EmissionShape)>(&cocos2d::ParticleSystem::setEmissionShape)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleSystem_setEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionShapes");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setEmissionShapes));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEmitterAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmitterAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setEmitterAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEmitterMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmitterMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleSystem::Mode)>(&cocos2d::ParticleSystem::setEmitterMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setEndColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndColorVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setEndColorVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndRadius");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndRadius));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndRadiusVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndRadiusVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSizeVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSizeVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSpin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSpin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setEndSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSpinVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSpinVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setFixedFPS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setFixedFPS");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setFixedFPS));
	LUA_TRY_INVOKE(0, [](cocos2d::ParticleSystem* obj){{return obj->setFixedFPS();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ParticleSystem_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHSV");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::HSV&)>(&cocos2d::ParticleSystem::setHSV));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setHSVVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHSVVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::HSV&)>(&cocos2d::ParticleSystem::setHSVVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setHue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHue");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setHue));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setHueVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHueVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setHueVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setLife(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLife");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setLife));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setLifeAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLifeAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setLifeAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setLifeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLifeVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setLifeVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setLoopAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLoopAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setLoopAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setMultiAnimationRandom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setMultiAnimationRandom");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::setMultiAnimationRandom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_setMultiAnimationRandomSpecific(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setMultiAnimationRandomSpecific");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const std::vector<unsigned short>&)>(&cocos2d::ParticleSystem::setMultiAnimationRandomSpecific));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setPosVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setPosVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setPosVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setPositionType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleSystem::PositionType)>(&cocos2d::ParticleSystem::setPositionType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRadialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRadialAccel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRadialAccel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRadialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRadialAccelVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRadialAccelVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRectForUndefinedIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRectForUndefinedIndices");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::Rect)>(&cocos2d::ParticleSystem::setRectForUndefinedIndices));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRotatePerSecond(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotatePerSecond");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRotatePerSecond));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRotatePerSecondVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotatePerSecondVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRotatePerSecondVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setRotationIsDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotationIsDir");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setRotationIsDir));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSourcePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSourcePosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setSourcePosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSourcePositionCompatible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSourcePositionCompatible");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setSourcePositionCompatible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnAngleVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnAngleVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnFadeIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnFadeIn");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnFadeIn));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnFadeInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnFadeInVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnFadeInVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnScaleIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnScaleIn");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnScaleIn));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpawnScaleInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnScaleInVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpawnScaleInVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setSpeedVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpeedVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpeedVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setStartColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartColorVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setStartColorVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartRadius");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartRadius));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartRadiusVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartRadiusVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSizeVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSizeVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSpin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSpin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setStartSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSpinVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSpinVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setTangentialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTangentialAccel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setTangentialAccel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setTangentialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTangentialAccelVar");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setTangentialAccelVar));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::Texture2D*)>(&cocos2d::ParticleSystem::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTimeScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setTimeScale));
	LUA_TRY_INVOKE(0, [](cocos2d::ParticleSystem* obj){{return obj->setTimeScale();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ParticleSystem_setTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTotalParticles");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::setTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_simulate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:simulate");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystem::*)(float, float)>(&cocos2d::ParticleSystem::simulate)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ParticleSystem* obj,float arg0){{return obj->simulate(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, [](cocos2d::ParticleSystem* obj){{return obj->simulate();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_ParticleSystem_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:start");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::start));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::stop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_stopSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:stopSystem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::stopSystem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_updateParticleQuads(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:updateParticleQuads");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::updateParticleQuads));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_updateWithNoTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:updateWithNoTime");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::updateWithNoTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleSystem_useHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:useHSV");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::useHSV));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSystem*(*)(std::string_view)>(&cocos2d::ParticleSystem::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_createCircleShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createCircleShape");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, float, float)>(&cocos2d::ParticleSystem::createCircleShape)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Vec2 arg0,float arg1){{return cocos2d::ParticleSystem::createCircleShape(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_cocos2d_ParticleSystem_createConeShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createConeShape");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, float, float, float, float)>(&cocos2d::ParticleSystem::createConeShape)));
	LUA_TRY_INVOKE_R(4, ([](cocos2d::Vec2 arg0,float arg1,float arg2,float arg3){{return cocos2d::ParticleSystem::createConeShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_SINVOKE_FOOTER("4,5");
}
int lua_cocos2d_ParticleSystem_createConeTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createConeTorusShape");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, float, float, float, float, float)>(&cocos2d::ParticleSystem::createConeTorusShape)));
	LUA_TRY_INVOKE_R(5, ([](cocos2d::Vec2 arg0,float arg1,float arg2,float arg3,float arg4){{return cocos2d::ParticleSystem::createConeTorusShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_SINVOKE_FOOTER("5,6");
}
int lua_cocos2d_ParticleSystem_createMaskShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createMaskShape");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::EmissionShape(*)(std::string_view, cocos2d::Vec2, cocos2d::Vec2, cocos2d::Vec2, float)>(&cocos2d::ParticleSystem::createMaskShape)));
	LUA_TRY_INVOKE_R(4, ([](std::string_view arg0,cocos2d::Vec2 arg1,cocos2d::Vec2 arg2,cocos2d::Vec2 arg3){{return cocos2d::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,cocos2d::Vec2 arg1,cocos2d::Vec2 arg2){{return cocos2d::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,cocos2d::Vec2 arg1){{return cocos2d::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ParticleSystem::createMaskShape(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2,3,4,5");
}
int lua_cocos2d_ParticleSystem_createPointShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createPointShape");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2)>(&cocos2d::ParticleSystem::createPointShape));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_createRectShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createRectShape");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, cocos2d::Size)>(&cocos2d::ParticleSystem::createRectShape)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleSystem_createRectTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createRectTorusShape");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, cocos2d::Size, cocos2d::Size)>(&cocos2d::ParticleSystem::createRectTorusShape)));
	LUA_SINVOKE_FOOTER("3");
}
int lua_cocos2d_ParticleSystem_createTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createTorusShape");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::EmissionShape(*)(cocos2d::Vec2, float, float, float)>(&cocos2d::ParticleSystem::createTorusShape)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Vec2 arg0,float arg1,float arg2){{return cocos2d::ParticleSystem::createTorusShape(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int lua_cocos2d_ParticleSystem_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSystem*(*)(int)>(&cocos2d::ParticleSystem::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleSystem_getAllParticleSystems(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAllParticleSystems");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocos2d::ParticleSystem *>&(*)()>(&cocos2d::ParticleSystem::getAllParticleSystems));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParticleSystem(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSystem, "ParticleSystem", "cc.ParticleSystem",
		cocos2d::ParticleSystem, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addAnimationIndex", lua_cocos2d_ParticleSystem_addAnimationIndex);
	LUA_METHOD("addEmissionShape", lua_cocos2d_ParticleSystem_addEmissionShape);
	LUA_METHOD("addParticles", lua_cocos2d_ParticleSystem_addParticles);
	LUA_METHOD("getAngle", lua_cocos2d_ParticleSystem_getAngle);
	LUA_METHOD("getAngleVar", lua_cocos2d_ParticleSystem_getAngleVar);
	LUA_METHOD("getAtlasIndex", lua_cocos2d_ParticleSystem_getAtlasIndex);
	LUA_METHOD("getBatchNode", lua_cocos2d_ParticleSystem_getBatchNode);
	LUA_METHOD("getBlendFunc", lua_cocos2d_ParticleSystem_getBlendFunc);
	LUA_METHOD("getDuration", lua_cocos2d_ParticleSystem_getDuration);
	LUA_METHOD("getEmissionRate", lua_cocos2d_ParticleSystem_getEmissionRate);
	LUA_METHOD("getEmitterMode", lua_cocos2d_ParticleSystem_getEmitterMode);
	LUA_METHOD("getEndColor", lua_cocos2d_ParticleSystem_getEndColor);
	LUA_METHOD("getEndColorVar", lua_cocos2d_ParticleSystem_getEndColorVar);
	LUA_METHOD("getEndRadius", lua_cocos2d_ParticleSystem_getEndRadius);
	LUA_METHOD("getEndRadiusVar", lua_cocos2d_ParticleSystem_getEndRadiusVar);
	LUA_METHOD("getEndSize", lua_cocos2d_ParticleSystem_getEndSize);
	LUA_METHOD("getEndSizeVar", lua_cocos2d_ParticleSystem_getEndSizeVar);
	LUA_METHOD("getEndSpin", lua_cocos2d_ParticleSystem_getEndSpin);
	LUA_METHOD("getEndSpinVar", lua_cocos2d_ParticleSystem_getEndSpinVar);
	LUA_METHOD("getFixedFPS", lua_cocos2d_ParticleSystem_getFixedFPS);
	LUA_METHOD("getGravity", lua_cocos2d_ParticleSystem_getGravity);
	LUA_METHOD("getHSV", lua_cocos2d_ParticleSystem_getHSV);
	LUA_METHOD("getHSVVar", lua_cocos2d_ParticleSystem_getHSVVar);
	LUA_METHOD("getHue", lua_cocos2d_ParticleSystem_getHue);
	LUA_METHOD("getHueVar", lua_cocos2d_ParticleSystem_getHueVar);
	LUA_METHOD("getLife", lua_cocos2d_ParticleSystem_getLife);
	LUA_METHOD("getLifeVar", lua_cocos2d_ParticleSystem_getLifeVar);
	LUA_METHOD("getParticleCount", lua_cocos2d_ParticleSystem_getParticleCount);
	LUA_METHOD("getPosVar", lua_cocos2d_ParticleSystem_getPosVar);
	LUA_METHOD("getPositionType", lua_cocos2d_ParticleSystem_getPositionType);
	LUA_METHOD("getRadialAccel", lua_cocos2d_ParticleSystem_getRadialAccel);
	LUA_METHOD("getRadialAccelVar", lua_cocos2d_ParticleSystem_getRadialAccelVar);
	LUA_METHOD("getResourceFile", lua_cocos2d_ParticleSystem_getResourceFile);
	LUA_METHOD("getRotatePerSecond", lua_cocos2d_ParticleSystem_getRotatePerSecond);
	LUA_METHOD("getRotatePerSecondVar", lua_cocos2d_ParticleSystem_getRotatePerSecondVar);
	LUA_METHOD("getRotationIsDir", lua_cocos2d_ParticleSystem_getRotationIsDir);
	LUA_METHOD("getSourcePosition", lua_cocos2d_ParticleSystem_getSourcePosition);
	LUA_METHOD("getSpawnAngle", lua_cocos2d_ParticleSystem_getSpawnAngle);
	LUA_METHOD("getSpawnAngleVar", lua_cocos2d_ParticleSystem_getSpawnAngleVar);
	LUA_METHOD("getSpawnFadeIn", lua_cocos2d_ParticleSystem_getSpawnFadeIn);
	LUA_METHOD("getSpawnFadeInVar", lua_cocos2d_ParticleSystem_getSpawnFadeInVar);
	LUA_METHOD("getSpawnScaleIn", lua_cocos2d_ParticleSystem_getSpawnScaleIn);
	LUA_METHOD("getSpawnScaleInVar", lua_cocos2d_ParticleSystem_getSpawnScaleInVar);
	LUA_METHOD("getSpeed", lua_cocos2d_ParticleSystem_getSpeed);
	LUA_METHOD("getSpeedVar", lua_cocos2d_ParticleSystem_getSpeedVar);
	LUA_METHOD("getStartColor", lua_cocos2d_ParticleSystem_getStartColor);
	LUA_METHOD("getStartColorVar", lua_cocos2d_ParticleSystem_getStartColorVar);
	LUA_METHOD("getStartRadius", lua_cocos2d_ParticleSystem_getStartRadius);
	LUA_METHOD("getStartRadiusVar", lua_cocos2d_ParticleSystem_getStartRadiusVar);
	LUA_METHOD("getStartSize", lua_cocos2d_ParticleSystem_getStartSize);
	LUA_METHOD("getStartSizeVar", lua_cocos2d_ParticleSystem_getStartSizeVar);
	LUA_METHOD("getStartSpin", lua_cocos2d_ParticleSystem_getStartSpin);
	LUA_METHOD("getStartSpinVar", lua_cocos2d_ParticleSystem_getStartSpinVar);
	LUA_METHOD("getTangentialAccel", lua_cocos2d_ParticleSystem_getTangentialAccel);
	LUA_METHOD("getTangentialAccelVar", lua_cocos2d_ParticleSystem_getTangentialAccelVar);
	LUA_METHOD("getTexture", lua_cocos2d_ParticleSystem_getTexture);
	LUA_METHOD("getTimeScale", lua_cocos2d_ParticleSystem_getTimeScale);
	LUA_METHOD("getTotalAnimationIndices", lua_cocos2d_ParticleSystem_getTotalAnimationIndices);
	LUA_METHOD("getTotalParticles", lua_cocos2d_ParticleSystem_getTotalParticles);
	LUA_METHOD("initWithDictionary", lua_cocos2d_ParticleSystem_initWithDictionary);
	LUA_METHOD("initWithFile", lua_cocos2d_ParticleSystem_initWithFile);
	LUA_METHOD("initWithTotalParticles", lua_cocos2d_ParticleSystem_initWithTotalParticles);
	LUA_METHOD("isActive", lua_cocos2d_ParticleSystem_isActive);
	LUA_METHOD("isAnimationReversed", lua_cocos2d_ParticleSystem_isAnimationReversed);
	LUA_METHOD("isAnimationSpeedTimescaleIndependent", lua_cocos2d_ParticleSystem_isAnimationSpeedTimescaleIndependent);
	LUA_METHOD("isAutoRemoveOnFinish", lua_cocos2d_ParticleSystem_isAutoRemoveOnFinish);
	LUA_METHOD("isBlendAdditive", lua_cocos2d_ParticleSystem_isBlendAdditive);
	LUA_METHOD("isEmissionShapes", lua_cocos2d_ParticleSystem_isEmissionShapes);
	LUA_METHOD("isEmitterAnimated", lua_cocos2d_ParticleSystem_isEmitterAnimated);
	LUA_METHOD("isFull", lua_cocos2d_ParticleSystem_isFull);
	LUA_METHOD("isHSV", lua_cocos2d_ParticleSystem_isHSV);
	LUA_METHOD("isLifeAnimated", lua_cocos2d_ParticleSystem_isLifeAnimated);
	LUA_METHOD("isLoopAnimated", lua_cocos2d_ParticleSystem_isLoopAnimated);
	LUA_METHOD("isPaused", lua_cocos2d_ParticleSystem_isPaused);
	LUA_METHOD("isSourcePositionCompatible", lua_cocos2d_ParticleSystem_isSourcePositionCompatible);
	LUA_METHOD("pauseEmissions", lua_cocos2d_ParticleSystem_pauseEmissions);
	LUA_METHOD("postStep", lua_cocos2d_ParticleSystem_postStep);
	LUA_METHOD("resetAnimationDescriptors", lua_cocos2d_ParticleSystem_resetAnimationDescriptors);
	LUA_METHOD("resetAnimationIndices", lua_cocos2d_ParticleSystem_resetAnimationIndices);
	LUA_METHOD("resetEmissionShapes", lua_cocos2d_ParticleSystem_resetEmissionShapes);
	LUA_METHOD("resetSystem", lua_cocos2d_ParticleSystem_resetSystem);
	LUA_METHOD("resimulate", lua_cocos2d_ParticleSystem_resimulate);
	LUA_METHOD("resumeEmissions", lua_cocos2d_ParticleSystem_resumeEmissions);
	LUA_METHOD("setAngle", lua_cocos2d_ParticleSystem_setAngle);
	LUA_METHOD("setAngleVar", lua_cocos2d_ParticleSystem_setAngleVar);
	LUA_METHOD("setAnimationDescriptor", lua_cocos2d_ParticleSystem_setAnimationDescriptor);
	LUA_METHOD("setAnimationIndicesAtlas", lua_cocos2d_ParticleSystem_setAnimationIndicesAtlas);
	LUA_METHOD("setAnimationReverse", lua_cocos2d_ParticleSystem_setAnimationReverse);
	LUA_METHOD("setAnimationSpeedTimescaleIndependent", lua_cocos2d_ParticleSystem_setAnimationSpeedTimescaleIndependent);
	LUA_METHOD("setAtlasIndex", lua_cocos2d_ParticleSystem_setAtlasIndex);
	LUA_METHOD("setAutoRemoveOnFinish", lua_cocos2d_ParticleSystem_setAutoRemoveOnFinish);
	LUA_METHOD("setBatchNode", lua_cocos2d_ParticleSystem_setBatchNode);
	LUA_METHOD("setBlendAdditive", lua_cocos2d_ParticleSystem_setBlendAdditive);
	LUA_METHOD("setBlendFunc", lua_cocos2d_ParticleSystem_setBlendFunc);
	LUA_METHOD("setDuration", lua_cocos2d_ParticleSystem_setDuration);
	LUA_METHOD("setEmissionRate", lua_cocos2d_ParticleSystem_setEmissionRate);
	LUA_METHOD("setEmissionShape", lua_cocos2d_ParticleSystem_setEmissionShape);
	LUA_METHOD("setEmissionShapes", lua_cocos2d_ParticleSystem_setEmissionShapes);
	LUA_METHOD("setEmitterAnimation", lua_cocos2d_ParticleSystem_setEmitterAnimation);
	LUA_METHOD("setEmitterMode", lua_cocos2d_ParticleSystem_setEmitterMode);
	LUA_METHOD("setEndColor", lua_cocos2d_ParticleSystem_setEndColor);
	LUA_METHOD("setEndColorVar", lua_cocos2d_ParticleSystem_setEndColorVar);
	LUA_METHOD("setEndRadius", lua_cocos2d_ParticleSystem_setEndRadius);
	LUA_METHOD("setEndRadiusVar", lua_cocos2d_ParticleSystem_setEndRadiusVar);
	LUA_METHOD("setEndSize", lua_cocos2d_ParticleSystem_setEndSize);
	LUA_METHOD("setEndSizeVar", lua_cocos2d_ParticleSystem_setEndSizeVar);
	LUA_METHOD("setEndSpin", lua_cocos2d_ParticleSystem_setEndSpin);
	LUA_METHOD("setEndSpinVar", lua_cocos2d_ParticleSystem_setEndSpinVar);
	LUA_METHOD("setFixedFPS", lua_cocos2d_ParticleSystem_setFixedFPS);
	LUA_METHOD("setGravity", lua_cocos2d_ParticleSystem_setGravity);
	LUA_METHOD("setHSV", lua_cocos2d_ParticleSystem_setHSV);
	LUA_METHOD("setHSVVar", lua_cocos2d_ParticleSystem_setHSVVar);
	LUA_METHOD("setHue", lua_cocos2d_ParticleSystem_setHue);
	LUA_METHOD("setHueVar", lua_cocos2d_ParticleSystem_setHueVar);
	LUA_METHOD("setLife", lua_cocos2d_ParticleSystem_setLife);
	LUA_METHOD("setLifeAnimation", lua_cocos2d_ParticleSystem_setLifeAnimation);
	LUA_METHOD("setLifeVar", lua_cocos2d_ParticleSystem_setLifeVar);
	LUA_METHOD("setLoopAnimation", lua_cocos2d_ParticleSystem_setLoopAnimation);
	LUA_METHOD("setMultiAnimationRandom", lua_cocos2d_ParticleSystem_setMultiAnimationRandom);
	LUA_METHOD("setMultiAnimationRandomSpecific", lua_cocos2d_ParticleSystem_setMultiAnimationRandomSpecific);
	LUA_METHOD("setPosVar", lua_cocos2d_ParticleSystem_setPosVar);
	LUA_METHOD("setPositionType", lua_cocos2d_ParticleSystem_setPositionType);
	LUA_METHOD("setRadialAccel", lua_cocos2d_ParticleSystem_setRadialAccel);
	LUA_METHOD("setRadialAccelVar", lua_cocos2d_ParticleSystem_setRadialAccelVar);
	LUA_METHOD("setRectForUndefinedIndices", lua_cocos2d_ParticleSystem_setRectForUndefinedIndices);
	LUA_METHOD("setRotatePerSecond", lua_cocos2d_ParticleSystem_setRotatePerSecond);
	LUA_METHOD("setRotatePerSecondVar", lua_cocos2d_ParticleSystem_setRotatePerSecondVar);
	LUA_METHOD("setRotationIsDir", lua_cocos2d_ParticleSystem_setRotationIsDir);
	LUA_METHOD("setSourcePosition", lua_cocos2d_ParticleSystem_setSourcePosition);
	LUA_METHOD("setSourcePositionCompatible", lua_cocos2d_ParticleSystem_setSourcePositionCompatible);
	LUA_METHOD("setSpawnAngle", lua_cocos2d_ParticleSystem_setSpawnAngle);
	LUA_METHOD("setSpawnAngleVar", lua_cocos2d_ParticleSystem_setSpawnAngleVar);
	LUA_METHOD("setSpawnFadeIn", lua_cocos2d_ParticleSystem_setSpawnFadeIn);
	LUA_METHOD("setSpawnFadeInVar", lua_cocos2d_ParticleSystem_setSpawnFadeInVar);
	LUA_METHOD("setSpawnScaleIn", lua_cocos2d_ParticleSystem_setSpawnScaleIn);
	LUA_METHOD("setSpawnScaleInVar", lua_cocos2d_ParticleSystem_setSpawnScaleInVar);
	LUA_METHOD("setSpeed", lua_cocos2d_ParticleSystem_setSpeed);
	LUA_METHOD("setSpeedVar", lua_cocos2d_ParticleSystem_setSpeedVar);
	LUA_METHOD("setStartColor", lua_cocos2d_ParticleSystem_setStartColor);
	LUA_METHOD("setStartColorVar", lua_cocos2d_ParticleSystem_setStartColorVar);
	LUA_METHOD("setStartRadius", lua_cocos2d_ParticleSystem_setStartRadius);
	LUA_METHOD("setStartRadiusVar", lua_cocos2d_ParticleSystem_setStartRadiusVar);
	LUA_METHOD("setStartSize", lua_cocos2d_ParticleSystem_setStartSize);
	LUA_METHOD("setStartSizeVar", lua_cocos2d_ParticleSystem_setStartSizeVar);
	LUA_METHOD("setStartSpin", lua_cocos2d_ParticleSystem_setStartSpin);
	LUA_METHOD("setStartSpinVar", lua_cocos2d_ParticleSystem_setStartSpinVar);
	LUA_METHOD("setTangentialAccel", lua_cocos2d_ParticleSystem_setTangentialAccel);
	LUA_METHOD("setTangentialAccelVar", lua_cocos2d_ParticleSystem_setTangentialAccelVar);
	LUA_METHOD("setTexture", lua_cocos2d_ParticleSystem_setTexture);
	LUA_METHOD("setTimeScale", lua_cocos2d_ParticleSystem_setTimeScale);
	LUA_METHOD("setTotalParticles", lua_cocos2d_ParticleSystem_setTotalParticles);
	LUA_METHOD("simulate", lua_cocos2d_ParticleSystem_simulate);
	LUA_METHOD("start", lua_cocos2d_ParticleSystem_start);
	LUA_METHOD("stop", lua_cocos2d_ParticleSystem_stop);
	LUA_METHOD("stopSystem", lua_cocos2d_ParticleSystem_stopSystem);
	LUA_METHOD("updateParticleQuads", lua_cocos2d_ParticleSystem_updateParticleQuads);
	LUA_METHOD("updateWithNoTime", lua_cocos2d_ParticleSystem_updateWithNoTime);
	LUA_METHOD("useHSV", lua_cocos2d_ParticleSystem_useHSV);
	LUA_METHOD("create", lua_cocos2d_ParticleSystem_create);
	LUA_METHOD("createCircleShape", lua_cocos2d_ParticleSystem_createCircleShape);
	LUA_METHOD("createConeShape", lua_cocos2d_ParticleSystem_createConeShape);
	LUA_METHOD("createConeTorusShape", lua_cocos2d_ParticleSystem_createConeTorusShape);
	LUA_METHOD("createMaskShape", lua_cocos2d_ParticleSystem_createMaskShape);
	LUA_METHOD("createPointShape", lua_cocos2d_ParticleSystem_createPointShape);
	LUA_METHOD("createRectShape", lua_cocos2d_ParticleSystem_createRectShape);
	LUA_METHOD("createRectTorusShape", lua_cocos2d_ParticleSystem_createRectTorusShape);
	LUA_METHOD("createTorusShape", lua_cocos2d_ParticleSystem_createTorusShape);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSystem_createWithTotalParticles);
	LUA_METHOD("getAllParticleSystems", lua_cocos2d_ParticleSystem_getAllParticleSystems);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int lua_cocos2d_ParticleSystemQuad_setTextureWithRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:setTextureWithRect");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::ParticleSystemQuad::setTextureWithRect)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleSystemQuad_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:create");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cocos2d::ParticleSystemQuad*(*)(cocos2d::ValueMap&)>(&cocos2d::ParticleSystemQuad::create));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cocos2d::ParticleSystemQuad*(*)(std::string_view)>(&cocos2d::ParticleSystemQuad::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleSystemQuad*(*)()>(&cocos2d::ParticleSystemQuad::create));
	LUA_SINVOKE_FOOTER("0,1");
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
		cocos2d::ParticleSystemQuad, "cc.ParticleSystem",
		nullptr, nullptr);
	LUA_METHOD("listenRendererRecreated", lua_cocos2d_ParticleSystemQuad_listenRendererRecreated);
	LUA_METHOD("setDisplayFrame", lua_cocos2d_ParticleSystemQuad_setDisplayFrame);
	LUA_METHOD("setTextureWithRect", lua_cocos2d_ParticleSystemQuad_setTextureWithRect);
	LUA_METHOD("create", lua_cocos2d_ParticleSystemQuad_create);
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
		cocos2d::ParticleFire, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParticleFire_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleFire_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
