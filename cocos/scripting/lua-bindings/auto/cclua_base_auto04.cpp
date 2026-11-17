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

int lua_cc_ParticleBatchNode_disableParticle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:disableParticle");
	LUA_TRY_INVOKE(1, &cc::ParticleBatchNode::disableParticle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleBatchNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::ParticleBatchNode::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleBatchNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::ParticleBatchNode::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleBatchNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, &cc::ParticleBatchNode::getTextureAtlas);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, &cc::ParticleBatchNode::initWithFile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, &cc::ParticleBatchNode::initWithTexture);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleBatchNode_insertChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:insertChild");
	LUA_TRY_INVOKE(2, &cc::ParticleBatchNode::insertChild);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleBatchNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::ParticleBatchNode::removeAllChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, &cc::ParticleBatchNode::removeChildAtIndex);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleBatchNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::ParticleBatchNode::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleBatchNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setTexture");
	LUA_TRY_INVOKE(1, &cc::ParticleBatchNode::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleBatchNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, &cc::ParticleBatchNode::setTextureAtlas);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:create");
	LUA_TRY_INVOKE_R(2, &cc::ParticleBatchNode::create);
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::ParticleBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_ParticleBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, &cc::ParticleBatchNode::createWithTexture);
	LUA_TRY_INVOKE_R(1, [](cc::Texture2D* arg0){{return cc::ParticleBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccParticleBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleBatchNode, "ParticleBatchNode", "cc.ParticleBatchNode",
		cc::ParticleBatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("disableParticle", lua_cc_ParticleBatchNode_disableParticle);
	LUA_METHOD("getBlendFunc", lua_cc_ParticleBatchNode_getBlendFunc);
	LUA_METHOD("getTexture", lua_cc_ParticleBatchNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cc_ParticleBatchNode_getTextureAtlas);
	LUA_METHOD("initWithFile", lua_cc_ParticleBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cc_ParticleBatchNode_initWithTexture);
	LUA_METHOD("insertChild", lua_cc_ParticleBatchNode_insertChild);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cc_ParticleBatchNode_removeAllChildrenWithCleanup);
	LUA_METHOD("removeChildAtIndex", lua_cc_ParticleBatchNode_removeChildAtIndex);
	LUA_METHOD("setBlendFunc", lua_cc_ParticleBatchNode_setBlendFunc);
	LUA_METHOD("setTexture", lua_cc_ParticleBatchNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cc_ParticleBatchNode_setTextureAtlas);
	LUA_METHOD("create", lua_cc_ParticleBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cc_ParticleBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SpriteFrameCache_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrame");
	LUA_TRY_INVOKE(2, &cc::SpriteFrameCache::addSpriteFrame);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SpriteFrameCache_addSpriteFrameCapInset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrameCapInset");
	LUA_TRY_INVOKE(3, &cc::SpriteFrameCache::addSpriteFrameCapInset);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_SpriteFrameCache_addSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrames");
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cc::SpriteFrameCache::*)(std::string_view, cc::Texture2D*, uint32_t)>(&cc::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cc::SpriteFrameCache::*)(std::string_view, std::string_view, uint32_t)>(&cc::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cc::SpriteFrameCache* obj,std::string_view arg0,cc::Texture2D* arg1){{return obj->addSpriteFramesWithFile(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cc::SpriteFrameCache* obj,std::string_view arg0,std::string_view arg1){{return obj->addSpriteFramesWithFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cc::SpriteFrameCache::*)(std::string_view, uint32_t)>(&cc::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE(1, ([](cc::SpriteFrameCache* obj,std::string_view arg0){{return obj->addSpriteFramesWithFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_SpriteFrameCache_deregisterSpriteSheetLoader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:deregisterSpriteSheetLoader");
	LUA_TRY_INVOKE(1, &cc::SpriteFrameCache::deregisterSpriteSheetLoader);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_eraseFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:eraseFrame");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::eraseFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_findFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:findFrame");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::findFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getSpriteFrame");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::getSpriteFrameByName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_getSpriteSheetLoader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getSpriteSheetLoader");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::getSpriteSheetLoader);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:init");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrameCache::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrameCache_isSpriteFramesWithFileLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:isSpriteFramesWithFileLoaded");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::isSpriteFramesWithFileLoaded);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:reloadTexture");
	LUA_TRY_INVOKE_R(1, &cc::SpriteFrameCache::reloadTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_removeSpriteFrameByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFrameByName");
	LUA_TRY_INVOKE(1, &cc::SpriteFrameCache::removeSpriteFrameByName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_removeSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFrames");
	LUA_TRY_INVOKE(0, &cc::SpriteFrameCache::removeSpriteFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrameCache_removeSpriteFramesFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromFile");
	LUA_TRY_INVOKE(1, &cc::SpriteFrameCache::removeSpriteFramesFromFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_removeSpriteFramesFromFileContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromFileContent");
	LUA_TRY_INVOKE(1, &cc::SpriteFrameCache::removeSpriteFramesFromFileContent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_removeSpriteFramesFromTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromTexture");
	LUA_TRY_INVOKE(1, &cc::SpriteFrameCache::removeSpriteFramesFromTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrameCache_removeUnusedSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeUnusedSpriteFrames");
	LUA_TRY_INVOKE(0, &cc::SpriteFrameCache::removeUnusedSpriteFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrameCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrameCache::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccSpriteFrameCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SpriteFrameCache, "SpriteFrameCache", "cc.SpriteFrameCache",
		cc::SpriteFrameCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cc_SpriteFrameCache_addSpriteFrame);
	LUA_METHOD("addSpriteFrameCapInset", lua_cc_SpriteFrameCache_addSpriteFrameCapInset);
	LUA_METHOD("addSpriteFrames", lua_cc_SpriteFrameCache_addSpriteFrames);
	LUA_METHOD("deregisterSpriteSheetLoader", lua_cc_SpriteFrameCache_deregisterSpriteSheetLoader);
	LUA_METHOD("eraseFrame", lua_cc_SpriteFrameCache_eraseFrame);
	LUA_METHOD("findFrame", lua_cc_SpriteFrameCache_findFrame);
	LUA_METHOD("getSpriteFrame", lua_cc_SpriteFrameCache_getSpriteFrame);
	LUA_METHOD("getSpriteSheetLoader", lua_cc_SpriteFrameCache_getSpriteSheetLoader);
	LUA_METHOD("init", lua_cc_SpriteFrameCache_init);
	LUA_METHOD("isSpriteFramesWithFileLoaded", lua_cc_SpriteFrameCache_isSpriteFramesWithFileLoaded);
	LUA_METHOD("reloadTexture", lua_cc_SpriteFrameCache_reloadTexture);
	LUA_METHOD("removeSpriteFrameByName", lua_cc_SpriteFrameCache_removeSpriteFrameByName);
	LUA_METHOD("removeSpriteFrames", lua_cc_SpriteFrameCache_removeSpriteFrames);
	LUA_METHOD("removeSpriteFramesFromFile", lua_cc_SpriteFrameCache_removeSpriteFramesFromFile);
	LUA_METHOD("removeSpriteFramesFromFileContent", lua_cc_SpriteFrameCache_removeSpriteFramesFromFileContent);
	LUA_METHOD("removeSpriteFramesFromTexture", lua_cc_SpriteFrameCache_removeSpriteFramesFromTexture);
	LUA_METHOD("removeUnusedSpriteFrames", lua_cc_SpriteFrameCache_removeUnusedSpriteFrames);
	LUA_METHOD("getInstance", lua_cc_SpriteFrameCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleEmissionMaskCache_bakeEmissionMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:bakeEmissionMask");
	LUA_TRY_INVOKE_OVERLOAD(5, (static_cast<void(cc::ParticleEmissionMaskCache::*)(std::string_view, cc::Image*, float, bool, int)>(&cc::ParticleEmissionMaskCache::bakeEmissionMask)));
	LUA_TRY_INVOKE_OVERLOAD(5, (static_cast<void(cc::ParticleEmissionMaskCache::*)(std::string_view, std::string_view, float, bool, int)>(&cc::ParticleEmissionMaskCache::bakeEmissionMask)));
	LUA_TRY_INVOKE_OVERLOAD(4, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,cc::Image* arg1,float arg2,bool arg3){{return obj->bakeEmissionMask(std::move(arg0),arg1,std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_OVERLOAD(4, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1,float arg2,bool arg3){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_OVERLOAD(3, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,cc::Image* arg1,float arg2){{return obj->bakeEmissionMask(std::move(arg0),arg1,std::move(arg2));}}));
	LUA_TRY_INVOKE_OVERLOAD(3, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1,float arg2){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,cc::Image* arg1){{return obj->bakeEmissionMask(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cc::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4,5");
}
int lua_cc_ParticleEmissionMaskCache_getEmissionMask_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:getEmissionMask");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<const cc::ParticleEmissionMaskDescriptor&(cc::ParticleEmissionMaskCache::*)(uint32_t)>(&cc::ParticleEmissionMaskCache::getEmissionMask));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<const cc::ParticleEmissionMaskDescriptor&(cc::ParticleEmissionMaskCache::*)(std::string_view)>(&cc::ParticleEmissionMaskCache::getEmissionMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleEmissionMaskCache_removeAllMasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:removeAllMasks");
	LUA_TRY_INVOKE(0, &cc::ParticleEmissionMaskCache::removeAllMasks);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleEmissionMaskCache_removeMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:removeMask");
	LUA_TRY_INVOKE(1, &cc::ParticleEmissionMaskCache::removeMask);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleEmissionMaskCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::ParticleEmissionMaskCache::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParticleEmissionMaskCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleEmissionMaskCache, "ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache",
		cc::ParticleEmissionMaskCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("bakeEmissionMask", lua_cc_ParticleEmissionMaskCache_bakeEmissionMask);
	LUA_METHOD("getEmissionMask", lua_cc_ParticleEmissionMaskCache_getEmissionMask_1);
	LUA_METHOD("removeAllMasks", lua_cc_ParticleEmissionMaskCache_removeAllMasks);
	LUA_METHOD("removeMask", lua_cc_ParticleEmissionMaskCache_removeMask);
	LUA_METHOD("getInstance", lua_cc_ParticleEmissionMaskCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSystem_addAnimationIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addAnimationIndex");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::ParticleSystem::*)(unsigned short, cc::Rect, bool)>(&cc::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cc::ParticleSystem* obj,unsigned short arg0,cc::Rect arg1){{return obj->addAnimationIndex(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::ParticleSystem::*)(unsigned short, cc::SpriteFrame*)>(&cc::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::ParticleSystem::*)(unsigned short, std::string_view)>(&cc::ParticleSystem::addAnimationIndex)));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cc::ParticleSystem::*)(cc::SpriteFrame*)>(&cc::ParticleSystem::addAnimationIndex));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cc::ParticleSystem::*)(std::string_view)>(&cc::ParticleSystem::addAnimationIndex));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_ParticleSystem_addEmissionShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addEmissionShape");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::addEmissionShape);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_addParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addParticles");
	LUA_TRY_INVOKE(3, &cc::ParticleSystem::addParticles);
	LUA_TRY_INVOKE(2, ([](cc::ParticleSystem* obj,int arg0,int arg1){{return obj->addParticles(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cc::ParticleSystem* obj,int arg0){{return obj->addParticles(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_ParticleSystem_getAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAngle");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAngleVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getAngleVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAtlasIndex");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getAtlasIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getBatchNode");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getBatchNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getDuration");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEmissionRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEmissionRate");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEmissionRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEmitterMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEmitterMode");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEmitterMode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndColor");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndColorVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndColorVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndRadius");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndRadiusVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndRadiusVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSize");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSizeVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndSizeVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSpin");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndSpin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getEndSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getEndSpinVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getEndSpinVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getFixedFPS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getFixedFPS");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getFixedFPS);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getGravity");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getGravity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHSV");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getHSV);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getHSVVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHSVVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getHSVVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getHue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHue");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getHue);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getHueVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getHueVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getHueVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getLife(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getLife");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getLife);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getLifeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getLifeVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getLifeVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getParticleCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getParticleCount");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getParticleCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getPosVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getPosVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getPosVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getPositionType");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getPositionType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getRadialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRadialAccel");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getRadialAccel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getRadialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRadialAccelVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getRadialAccelVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getResourceFile");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getResourceFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getRotatePerSecond(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotatePerSecond");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getRotatePerSecond);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getRotatePerSecondVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotatePerSecondVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getRotatePerSecondVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getRotationIsDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getRotationIsDir");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getRotationIsDir);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSourcePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSourcePosition");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSourcePosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnAngle");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnAngleVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnAngleVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnFadeIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnFadeIn");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnFadeIn);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnFadeInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnFadeInVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnFadeInVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnScaleIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnScaleIn");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnScaleIn);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpawnScaleInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpawnScaleInVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpawnScaleInVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpeed");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpeed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getSpeedVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getSpeedVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getSpeedVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartColor");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartColorVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartColorVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartRadius");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartRadiusVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartRadiusVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSize");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSizeVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartSizeVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSpin");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartSpin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getStartSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getStartSpinVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getStartSpinVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTangentialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTangentialAccel");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTangentialAccel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTangentialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTangentialAccelVar");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTangentialAccelVar);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTimeScale");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTimeScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTotalAnimationIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTotalAnimationIndices");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTotalAnimationIndices);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_getTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getTotalParticles");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getTotalParticles);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_initWithDictionary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithDictionary");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::ParticleSystem::*)(const cc::ValueMap&, std::string_view)>(&cc::ParticleSystem::initWithDictionary)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleSystem::*)(const cc::ValueMap&)>(&cc::ParticleSystem::initWithDictionary));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_ParticleSystem_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithFile");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystem::initWithFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_initWithTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystem::initWithTotalParticles);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_isActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isActive");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isActive);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isAnimationReversed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAnimationReversed");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isAnimationReversed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isAnimationSpeedTimescaleIndependent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAnimationSpeedTimescaleIndependent");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isAnimationSpeedTimescaleIndependent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isAutoRemoveOnFinish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isAutoRemoveOnFinish");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isAutoRemoveOnFinish);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isBlendAdditive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isBlendAdditive");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isBlendAdditive);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isEmissionShapes");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isEmissionShapes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isEmitterAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isEmitterAnimated");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isEmitterAnimated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isFull(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isFull");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isFull);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isHSV");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isHSV);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isLifeAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isLifeAnimated");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isLifeAnimated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isLoopAnimated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isLoopAnimated");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isLoopAnimated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isPaused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isPaused");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isPaused);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_isSourcePositionCompatible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:isSourcePositionCompatible");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::isSourcePositionCompatible);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_pauseEmissions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:pauseEmissions");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::pauseEmissions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_postStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:postStep");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::postStep);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_resetAnimationDescriptors(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetAnimationDescriptors");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::resetAnimationDescriptors);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_resetAnimationIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetAnimationIndices");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::resetAnimationIndices);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_resetEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetEmissionShapes");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::resetEmissionShapes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_resetSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resetSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::resetSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_resimulate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resimulate");
	LUA_TRY_INVOKE(2, &cc::ParticleSystem::resimulate);
	LUA_TRY_INVOKE(1, ([](cc::ParticleSystem* obj,float arg0){{return obj->resimulate(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, [](cc::ParticleSystem* obj){{return obj->resimulate();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cc_ParticleSystem_resumeEmissions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:resumeEmissions");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::resumeEmissions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_setAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAngle");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAngle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAngleVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAngleVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setAnimationDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationDescriptor");
	LUA_TRY_INVOKE(5, (static_cast<void(cc::ParticleSystem::*)(unsigned short, float, float, const std::vector<unsigned short>&, bool)>(&cc::ParticleSystem::setAnimationDescriptor)));
	LUA_TRY_INVOKE(4, ([](cc::ParticleSystem* obj,unsigned short arg0,float arg1,float arg2,const std::vector<unsigned short>& arg3){{return obj->setAnimationDescriptor(std::move(arg0),std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE(2, (static_cast<void(cc::ParticleSystem::*)(const std::vector<unsigned short>&, bool)>(&cc::ParticleSystem::setAnimationDescriptor)));
	LUA_TRY_INVOKE(1, ([](cc::ParticleSystem* obj,const std::vector<unsigned short>& arg0){{return obj->setAnimationDescriptor(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,4,5");
}
int lua_cc_ParticleSystem_setAnimationIndicesAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationIndicesAtlas");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::ParticleSystem::*)(unsigned int, cc::ParticleSystem::TexAnimDir)>(&cc::ParticleSystem::setAnimationIndicesAtlas)));
	LUA_TRY_INVOKE(1, ([](cc::ParticleSystem* obj,unsigned int arg0){{return obj->setAnimationIndicesAtlas(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, static_cast<void(cc::ParticleSystem::*)()>(&cc::ParticleSystem::setAnimationIndicesAtlas));
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cc_ParticleSystem_setAnimationReverse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationReverse");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAnimationReverse);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setAnimationSpeedTimescaleIndependent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationSpeedTimescaleIndependent");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAnimationSpeedTimescaleIndependent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAtlasIndex");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAtlasIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setAutoRemoveOnFinish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAutoRemoveOnFinish");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setAutoRemoveOnFinish);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBatchNode");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setBatchNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setBlendAdditive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBlendAdditive");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setBlendAdditive);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setDuration");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEmissionRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionRate");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEmissionRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEmissionShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionShape");
	LUA_TRY_INVOKE(2, &cc::ParticleSystem::setEmissionShape);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleSystem_setEmissionShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmissionShapes");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEmissionShapes);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEmitterAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmitterAnimation");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEmitterAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEmitterMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEmitterMode");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEmitterMode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndColor");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndColorVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndColorVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndRadius");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndRadius);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndRadiusVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndRadiusVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSize");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSizeVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndSizeVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSpin");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndSpin);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setEndSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setEndSpinVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setEndSpinVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setFixedFPS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setFixedFPS");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setFixedFPS);
	LUA_TRY_INVOKE(0, [](cc::ParticleSystem* obj){{return obj->setFixedFPS();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_ParticleSystem_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setGravity");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setGravity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHSV");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setHSV);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setHSVVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHSVVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setHSVVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setHue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHue");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setHue);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setHueVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setHueVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setHueVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setLife(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLife");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setLife);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setLifeAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLifeAnimation");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setLifeAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setLifeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLifeVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setLifeVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setLoopAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setLoopAnimation");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setLoopAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setMultiAnimationRandom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setMultiAnimationRandom");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::setMultiAnimationRandom);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_setMultiAnimationRandomSpecific(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setMultiAnimationRandomSpecific");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setMultiAnimationRandomSpecific);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setPosVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setPosVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setPosVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setPositionType");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setPositionType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRadialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRadialAccel");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRadialAccel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRadialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRadialAccelVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRadialAccelVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRectForUndefinedIndices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRectForUndefinedIndices");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRectForUndefinedIndices);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRotatePerSecond(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotatePerSecond");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRotatePerSecond);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRotatePerSecondVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotatePerSecondVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRotatePerSecondVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setRotationIsDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setRotationIsDir");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setRotationIsDir);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSourcePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSourcePosition");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSourcePosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSourcePositionCompatible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSourcePositionCompatible");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSourcePositionCompatible);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnAngle");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnAngle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnAngleVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnAngleVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnAngleVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnFadeIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnFadeIn");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnFadeIn);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnFadeInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnFadeInVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnFadeInVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnScaleIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnScaleIn");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnScaleIn);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpawnScaleInVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpawnScaleInVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpawnScaleInVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpeed");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpeed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setSpeedVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setSpeedVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setSpeedVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartColor");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartColorVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartColorVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartColorVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartRadius");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartRadius);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartRadiusVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartRadiusVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartRadiusVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSize");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartSizeVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSizeVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartSizeVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartSpin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSpin");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartSpin);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setStartSpinVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setStartSpinVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setStartSpinVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setTangentialAccel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTangentialAccel");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setTangentialAccel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setTangentialAccelVar(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTangentialAccelVar");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setTangentialAccelVar);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTexture");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTimeScale");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setTimeScale);
	LUA_TRY_INVOKE(0, [](cc::ParticleSystem* obj){{return obj->setTimeScale();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_ParticleSystem_setTotalParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setTotalParticles");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::setTotalParticles);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_simulate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:simulate");
	LUA_TRY_INVOKE(2, &cc::ParticleSystem::simulate);
	LUA_TRY_INVOKE(1, ([](cc::ParticleSystem* obj,float arg0){{return obj->simulate(std::move(arg0));}}));
	LUA_TRY_INVOKE(0, [](cc::ParticleSystem* obj){{return obj->simulate();}});
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cc_ParticleSystem_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:start");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::start);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:stop");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::stop);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_stopSystem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:stopSystem");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::stopSystem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_updateParticleQuads(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:updateParticleQuads");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::updateParticleQuads);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_updateWithNoTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:updateWithNoTime");
	LUA_TRY_INVOKE(0, &cc::ParticleSystem::updateWithNoTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSystem_useHSV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:useHSV");
	LUA_TRY_INVOKE(1, &cc::ParticleSystem::useHSV);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:create");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystem::create);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_createCircleShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createCircleShape");
	LUA_TRY_INVOKE_R(3, &cc::ParticleSystem::createCircleShape);
	LUA_TRY_INVOKE_R(2, ([](cc::Vec2 arg0,float arg1){{return cc::ParticleSystem::createCircleShape(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_cc_ParticleSystem_createConeShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createConeShape");
	LUA_TRY_INVOKE_R(5, &cc::ParticleSystem::createConeShape);
	LUA_TRY_INVOKE_R(4, ([](cc::Vec2 arg0,float arg1,float arg2,float arg3){{return cc::ParticleSystem::createConeShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_SINVOKE_FOOTER("4,5");
}
int lua_cc_ParticleSystem_createConeTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createConeTorusShape");
	LUA_TRY_INVOKE_R(6, &cc::ParticleSystem::createConeTorusShape);
	LUA_TRY_INVOKE_R(5, ([](cc::Vec2 arg0,float arg1,float arg2,float arg3,float arg4){{return cc::ParticleSystem::createConeTorusShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_SINVOKE_FOOTER("5,6");
}
int lua_cc_ParticleSystem_createMaskShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createMaskShape");
	LUA_TRY_INVOKE_R(5, &cc::ParticleSystem::createMaskShape);
	LUA_TRY_INVOKE_R(4, ([](std::string_view arg0,cc::Vec2 arg1,cc::Vec2 arg2,cc::Vec2 arg3){{return cc::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,cc::Vec2 arg1,cc::Vec2 arg2){{return cc::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,cc::Vec2 arg1){{return cc::ParticleSystem::createMaskShape(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::ParticleSystem::createMaskShape(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2,3,4,5");
}
int lua_cc_ParticleSystem_createPointShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createPointShape");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystem::createPointShape);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_createRectShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createRectShape");
	LUA_TRY_INVOKE_R(2, &cc::ParticleSystem::createRectShape);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cc_ParticleSystem_createRectTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createRectTorusShape");
	LUA_TRY_INVOKE_R(3, &cc::ParticleSystem::createRectTorusShape);
	LUA_SINVOKE_FOOTER("3");
}
int lua_cc_ParticleSystem_createTorusShape(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createTorusShape");
	LUA_TRY_INVOKE_R(4, &cc::ParticleSystem::createTorusShape);
	LUA_TRY_INVOKE_R(3, ([](cc::Vec2 arg0,float arg1,float arg2){{return cc::ParticleSystem::createTorusShape(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int lua_cc_ParticleSystem_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystem::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_ParticleSystem_getAllParticleSystems(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:getAllParticleSystems");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSystem::getAllParticleSystems);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParticleSystem(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSystem, "ParticleSystem", "cc.ParticleSystem",
		cc::ParticleSystem, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addAnimationIndex", lua_cc_ParticleSystem_addAnimationIndex);
	LUA_METHOD("addEmissionShape", lua_cc_ParticleSystem_addEmissionShape);
	LUA_METHOD("addParticles", lua_cc_ParticleSystem_addParticles);
	LUA_METHOD("getAngle", lua_cc_ParticleSystem_getAngle);
	LUA_METHOD("getAngleVar", lua_cc_ParticleSystem_getAngleVar);
	LUA_METHOD("getAtlasIndex", lua_cc_ParticleSystem_getAtlasIndex);
	LUA_METHOD("getBatchNode", lua_cc_ParticleSystem_getBatchNode);
	LUA_METHOD("getBlendFunc", lua_cc_ParticleSystem_getBlendFunc);
	LUA_METHOD("getDuration", lua_cc_ParticleSystem_getDuration);
	LUA_METHOD("getEmissionRate", lua_cc_ParticleSystem_getEmissionRate);
	LUA_METHOD("getEmitterMode", lua_cc_ParticleSystem_getEmitterMode);
	LUA_METHOD("getEndColor", lua_cc_ParticleSystem_getEndColor);
	LUA_METHOD("getEndColorVar", lua_cc_ParticleSystem_getEndColorVar);
	LUA_METHOD("getEndRadius", lua_cc_ParticleSystem_getEndRadius);
	LUA_METHOD("getEndRadiusVar", lua_cc_ParticleSystem_getEndRadiusVar);
	LUA_METHOD("getEndSize", lua_cc_ParticleSystem_getEndSize);
	LUA_METHOD("getEndSizeVar", lua_cc_ParticleSystem_getEndSizeVar);
	LUA_METHOD("getEndSpin", lua_cc_ParticleSystem_getEndSpin);
	LUA_METHOD("getEndSpinVar", lua_cc_ParticleSystem_getEndSpinVar);
	LUA_METHOD("getFixedFPS", lua_cc_ParticleSystem_getFixedFPS);
	LUA_METHOD("getGravity", lua_cc_ParticleSystem_getGravity);
	LUA_METHOD("getHSV", lua_cc_ParticleSystem_getHSV);
	LUA_METHOD("getHSVVar", lua_cc_ParticleSystem_getHSVVar);
	LUA_METHOD("getHue", lua_cc_ParticleSystem_getHue);
	LUA_METHOD("getHueVar", lua_cc_ParticleSystem_getHueVar);
	LUA_METHOD("getLife", lua_cc_ParticleSystem_getLife);
	LUA_METHOD("getLifeVar", lua_cc_ParticleSystem_getLifeVar);
	LUA_METHOD("getParticleCount", lua_cc_ParticleSystem_getParticleCount);
	LUA_METHOD("getPosVar", lua_cc_ParticleSystem_getPosVar);
	LUA_METHOD("getPositionType", lua_cc_ParticleSystem_getPositionType);
	LUA_METHOD("getRadialAccel", lua_cc_ParticleSystem_getRadialAccel);
	LUA_METHOD("getRadialAccelVar", lua_cc_ParticleSystem_getRadialAccelVar);
	LUA_METHOD("getResourceFile", lua_cc_ParticleSystem_getResourceFile);
	LUA_METHOD("getRotatePerSecond", lua_cc_ParticleSystem_getRotatePerSecond);
	LUA_METHOD("getRotatePerSecondVar", lua_cc_ParticleSystem_getRotatePerSecondVar);
	LUA_METHOD("getRotationIsDir", lua_cc_ParticleSystem_getRotationIsDir);
	LUA_METHOD("getSourcePosition", lua_cc_ParticleSystem_getSourcePosition);
	LUA_METHOD("getSpawnAngle", lua_cc_ParticleSystem_getSpawnAngle);
	LUA_METHOD("getSpawnAngleVar", lua_cc_ParticleSystem_getSpawnAngleVar);
	LUA_METHOD("getSpawnFadeIn", lua_cc_ParticleSystem_getSpawnFadeIn);
	LUA_METHOD("getSpawnFadeInVar", lua_cc_ParticleSystem_getSpawnFadeInVar);
	LUA_METHOD("getSpawnScaleIn", lua_cc_ParticleSystem_getSpawnScaleIn);
	LUA_METHOD("getSpawnScaleInVar", lua_cc_ParticleSystem_getSpawnScaleInVar);
	LUA_METHOD("getSpeed", lua_cc_ParticleSystem_getSpeed);
	LUA_METHOD("getSpeedVar", lua_cc_ParticleSystem_getSpeedVar);
	LUA_METHOD("getStartColor", lua_cc_ParticleSystem_getStartColor);
	LUA_METHOD("getStartColorVar", lua_cc_ParticleSystem_getStartColorVar);
	LUA_METHOD("getStartRadius", lua_cc_ParticleSystem_getStartRadius);
	LUA_METHOD("getStartRadiusVar", lua_cc_ParticleSystem_getStartRadiusVar);
	LUA_METHOD("getStartSize", lua_cc_ParticleSystem_getStartSize);
	LUA_METHOD("getStartSizeVar", lua_cc_ParticleSystem_getStartSizeVar);
	LUA_METHOD("getStartSpin", lua_cc_ParticleSystem_getStartSpin);
	LUA_METHOD("getStartSpinVar", lua_cc_ParticleSystem_getStartSpinVar);
	LUA_METHOD("getTangentialAccel", lua_cc_ParticleSystem_getTangentialAccel);
	LUA_METHOD("getTangentialAccelVar", lua_cc_ParticleSystem_getTangentialAccelVar);
	LUA_METHOD("getTexture", lua_cc_ParticleSystem_getTexture);
	LUA_METHOD("getTimeScale", lua_cc_ParticleSystem_getTimeScale);
	LUA_METHOD("getTotalAnimationIndices", lua_cc_ParticleSystem_getTotalAnimationIndices);
	LUA_METHOD("getTotalParticles", lua_cc_ParticleSystem_getTotalParticles);
	LUA_METHOD("initWithDictionary", lua_cc_ParticleSystem_initWithDictionary);
	LUA_METHOD("initWithFile", lua_cc_ParticleSystem_initWithFile);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleSystem_initWithTotalParticles);
	LUA_METHOD("isActive", lua_cc_ParticleSystem_isActive);
	LUA_METHOD("isAnimationReversed", lua_cc_ParticleSystem_isAnimationReversed);
	LUA_METHOD("isAnimationSpeedTimescaleIndependent", lua_cc_ParticleSystem_isAnimationSpeedTimescaleIndependent);
	LUA_METHOD("isAutoRemoveOnFinish", lua_cc_ParticleSystem_isAutoRemoveOnFinish);
	LUA_METHOD("isBlendAdditive", lua_cc_ParticleSystem_isBlendAdditive);
	LUA_METHOD("isEmissionShapes", lua_cc_ParticleSystem_isEmissionShapes);
	LUA_METHOD("isEmitterAnimated", lua_cc_ParticleSystem_isEmitterAnimated);
	LUA_METHOD("isFull", lua_cc_ParticleSystem_isFull);
	LUA_METHOD("isHSV", lua_cc_ParticleSystem_isHSV);
	LUA_METHOD("isLifeAnimated", lua_cc_ParticleSystem_isLifeAnimated);
	LUA_METHOD("isLoopAnimated", lua_cc_ParticleSystem_isLoopAnimated);
	LUA_METHOD("isPaused", lua_cc_ParticleSystem_isPaused);
	LUA_METHOD("isSourcePositionCompatible", lua_cc_ParticleSystem_isSourcePositionCompatible);
	LUA_METHOD("pauseEmissions", lua_cc_ParticleSystem_pauseEmissions);
	LUA_METHOD("postStep", lua_cc_ParticleSystem_postStep);
	LUA_METHOD("resetAnimationDescriptors", lua_cc_ParticleSystem_resetAnimationDescriptors);
	LUA_METHOD("resetAnimationIndices", lua_cc_ParticleSystem_resetAnimationIndices);
	LUA_METHOD("resetEmissionShapes", lua_cc_ParticleSystem_resetEmissionShapes);
	LUA_METHOD("resetSystem", lua_cc_ParticleSystem_resetSystem);
	LUA_METHOD("resimulate", lua_cc_ParticleSystem_resimulate);
	LUA_METHOD("resumeEmissions", lua_cc_ParticleSystem_resumeEmissions);
	LUA_METHOD("setAngle", lua_cc_ParticleSystem_setAngle);
	LUA_METHOD("setAngleVar", lua_cc_ParticleSystem_setAngleVar);
	LUA_METHOD("setAnimationDescriptor", lua_cc_ParticleSystem_setAnimationDescriptor);
	LUA_METHOD("setAnimationIndicesAtlas", lua_cc_ParticleSystem_setAnimationIndicesAtlas);
	LUA_METHOD("setAnimationReverse", lua_cc_ParticleSystem_setAnimationReverse);
	LUA_METHOD("setAnimationSpeedTimescaleIndependent", lua_cc_ParticleSystem_setAnimationSpeedTimescaleIndependent);
	LUA_METHOD("setAtlasIndex", lua_cc_ParticleSystem_setAtlasIndex);
	LUA_METHOD("setAutoRemoveOnFinish", lua_cc_ParticleSystem_setAutoRemoveOnFinish);
	LUA_METHOD("setBatchNode", lua_cc_ParticleSystem_setBatchNode);
	LUA_METHOD("setBlendAdditive", lua_cc_ParticleSystem_setBlendAdditive);
	LUA_METHOD("setBlendFunc", lua_cc_ParticleSystem_setBlendFunc);
	LUA_METHOD("setDuration", lua_cc_ParticleSystem_setDuration);
	LUA_METHOD("setEmissionRate", lua_cc_ParticleSystem_setEmissionRate);
	LUA_METHOD("setEmissionShape", lua_cc_ParticleSystem_setEmissionShape);
	LUA_METHOD("setEmissionShapes", lua_cc_ParticleSystem_setEmissionShapes);
	LUA_METHOD("setEmitterAnimation", lua_cc_ParticleSystem_setEmitterAnimation);
	LUA_METHOD("setEmitterMode", lua_cc_ParticleSystem_setEmitterMode);
	LUA_METHOD("setEndColor", lua_cc_ParticleSystem_setEndColor);
	LUA_METHOD("setEndColorVar", lua_cc_ParticleSystem_setEndColorVar);
	LUA_METHOD("setEndRadius", lua_cc_ParticleSystem_setEndRadius);
	LUA_METHOD("setEndRadiusVar", lua_cc_ParticleSystem_setEndRadiusVar);
	LUA_METHOD("setEndSize", lua_cc_ParticleSystem_setEndSize);
	LUA_METHOD("setEndSizeVar", lua_cc_ParticleSystem_setEndSizeVar);
	LUA_METHOD("setEndSpin", lua_cc_ParticleSystem_setEndSpin);
	LUA_METHOD("setEndSpinVar", lua_cc_ParticleSystem_setEndSpinVar);
	LUA_METHOD("setFixedFPS", lua_cc_ParticleSystem_setFixedFPS);
	LUA_METHOD("setGravity", lua_cc_ParticleSystem_setGravity);
	LUA_METHOD("setHSV", lua_cc_ParticleSystem_setHSV);
	LUA_METHOD("setHSVVar", lua_cc_ParticleSystem_setHSVVar);
	LUA_METHOD("setHue", lua_cc_ParticleSystem_setHue);
	LUA_METHOD("setHueVar", lua_cc_ParticleSystem_setHueVar);
	LUA_METHOD("setLife", lua_cc_ParticleSystem_setLife);
	LUA_METHOD("setLifeAnimation", lua_cc_ParticleSystem_setLifeAnimation);
	LUA_METHOD("setLifeVar", lua_cc_ParticleSystem_setLifeVar);
	LUA_METHOD("setLoopAnimation", lua_cc_ParticleSystem_setLoopAnimation);
	LUA_METHOD("setMultiAnimationRandom", lua_cc_ParticleSystem_setMultiAnimationRandom);
	LUA_METHOD("setMultiAnimationRandomSpecific", lua_cc_ParticleSystem_setMultiAnimationRandomSpecific);
	LUA_METHOD("setPosVar", lua_cc_ParticleSystem_setPosVar);
	LUA_METHOD("setPositionType", lua_cc_ParticleSystem_setPositionType);
	LUA_METHOD("setRadialAccel", lua_cc_ParticleSystem_setRadialAccel);
	LUA_METHOD("setRadialAccelVar", lua_cc_ParticleSystem_setRadialAccelVar);
	LUA_METHOD("setRectForUndefinedIndices", lua_cc_ParticleSystem_setRectForUndefinedIndices);
	LUA_METHOD("setRotatePerSecond", lua_cc_ParticleSystem_setRotatePerSecond);
	LUA_METHOD("setRotatePerSecondVar", lua_cc_ParticleSystem_setRotatePerSecondVar);
	LUA_METHOD("setRotationIsDir", lua_cc_ParticleSystem_setRotationIsDir);
	LUA_METHOD("setSourcePosition", lua_cc_ParticleSystem_setSourcePosition);
	LUA_METHOD("setSourcePositionCompatible", lua_cc_ParticleSystem_setSourcePositionCompatible);
	LUA_METHOD("setSpawnAngle", lua_cc_ParticleSystem_setSpawnAngle);
	LUA_METHOD("setSpawnAngleVar", lua_cc_ParticleSystem_setSpawnAngleVar);
	LUA_METHOD("setSpawnFadeIn", lua_cc_ParticleSystem_setSpawnFadeIn);
	LUA_METHOD("setSpawnFadeInVar", lua_cc_ParticleSystem_setSpawnFadeInVar);
	LUA_METHOD("setSpawnScaleIn", lua_cc_ParticleSystem_setSpawnScaleIn);
	LUA_METHOD("setSpawnScaleInVar", lua_cc_ParticleSystem_setSpawnScaleInVar);
	LUA_METHOD("setSpeed", lua_cc_ParticleSystem_setSpeed);
	LUA_METHOD("setSpeedVar", lua_cc_ParticleSystem_setSpeedVar);
	LUA_METHOD("setStartColor", lua_cc_ParticleSystem_setStartColor);
	LUA_METHOD("setStartColorVar", lua_cc_ParticleSystem_setStartColorVar);
	LUA_METHOD("setStartRadius", lua_cc_ParticleSystem_setStartRadius);
	LUA_METHOD("setStartRadiusVar", lua_cc_ParticleSystem_setStartRadiusVar);
	LUA_METHOD("setStartSize", lua_cc_ParticleSystem_setStartSize);
	LUA_METHOD("setStartSizeVar", lua_cc_ParticleSystem_setStartSizeVar);
	LUA_METHOD("setStartSpin", lua_cc_ParticleSystem_setStartSpin);
	LUA_METHOD("setStartSpinVar", lua_cc_ParticleSystem_setStartSpinVar);
	LUA_METHOD("setTangentialAccel", lua_cc_ParticleSystem_setTangentialAccel);
	LUA_METHOD("setTangentialAccelVar", lua_cc_ParticleSystem_setTangentialAccelVar);
	LUA_METHOD("setTexture", lua_cc_ParticleSystem_setTexture);
	LUA_METHOD("setTimeScale", lua_cc_ParticleSystem_setTimeScale);
	LUA_METHOD("setTotalParticles", lua_cc_ParticleSystem_setTotalParticles);
	LUA_METHOD("simulate", lua_cc_ParticleSystem_simulate);
	LUA_METHOD("start", lua_cc_ParticleSystem_start);
	LUA_METHOD("stop", lua_cc_ParticleSystem_stop);
	LUA_METHOD("stopSystem", lua_cc_ParticleSystem_stopSystem);
	LUA_METHOD("updateParticleQuads", lua_cc_ParticleSystem_updateParticleQuads);
	LUA_METHOD("updateWithNoTime", lua_cc_ParticleSystem_updateWithNoTime);
	LUA_METHOD("useHSV", lua_cc_ParticleSystem_useHSV);
	LUA_METHOD("create", lua_cc_ParticleSystem_create);
	LUA_METHOD("createCircleShape", lua_cc_ParticleSystem_createCircleShape);
	LUA_METHOD("createConeShape", lua_cc_ParticleSystem_createConeShape);
	LUA_METHOD("createConeTorusShape", lua_cc_ParticleSystem_createConeTorusShape);
	LUA_METHOD("createMaskShape", lua_cc_ParticleSystem_createMaskShape);
	LUA_METHOD("createPointShape", lua_cc_ParticleSystem_createPointShape);
	LUA_METHOD("createRectShape", lua_cc_ParticleSystem_createRectShape);
	LUA_METHOD("createRectTorusShape", lua_cc_ParticleSystem_createRectTorusShape);
	LUA_METHOD("createTorusShape", lua_cc_ParticleSystem_createTorusShape);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSystem_createWithTotalParticles);
	LUA_METHOD("getAllParticleSystems", lua_cc_ParticleSystem_getAllParticleSystems);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSystemQuad_listenRendererRecreated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:listenRendererRecreated");
	LUA_TRY_INVOKE(1, &cc::ParticleSystemQuad::listenRendererRecreated);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystemQuad_setDisplayFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:setDisplayFrame");
	LUA_TRY_INVOKE(1, &cc::ParticleSystemQuad::setDisplayFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSystemQuad_setTextureWithRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:setTextureWithRect");
	LUA_TRY_INVOKE(2, &cc::ParticleSystemQuad::setTextureWithRect);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ParticleSystemQuad_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:create");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cc::IntrusivePtr<cc::ParticleSystemQuad>(*)(cc::ValueMap&)>(&cc::ParticleSystemQuad::create));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cc::IntrusivePtr<cc::ParticleSystemQuad>(*)(std::string_view)>(&cc::ParticleSystemQuad::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::ParticleSystemQuad>(*)()>(&cc::ParticleSystemQuad::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int lua_cc_ParticleSystemQuad_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystemQuad", "cc.ParticleSystemQuad:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSystemQuad::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSystemQuad(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSystemQuad, "ParticleSystemQuad", "cc.ParticleSystemQuad",
		cc::ParticleSystemQuad, "cc.ParticleSystem",
		nullptr, nullptr);
	LUA_METHOD("listenRendererRecreated", lua_cc_ParticleSystemQuad_listenRendererRecreated);
	LUA_METHOD("setDisplayFrame", lua_cc_ParticleSystemQuad_setDisplayFrame);
	LUA_METHOD("setTextureWithRect", lua_cc_ParticleSystemQuad_setTextureWithRect);
	LUA_METHOD("create", lua_cc_ParticleSystemQuad_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSystemQuad_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleFire_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFire", "cc.ParticleFire:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleFire::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleFire_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFire", "cc.ParticleFire:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleFire::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFire(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleFire, "ParticleFire", "cc.ParticleFire",
		cc::ParticleFire, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_ParticleFire_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleFire_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleFireworks_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleFireworks::*)()>(&cc::ParticleFireworks::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleFireworks_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleFireworks::*)(int)>(&cc::ParticleFireworks::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleFireworks_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleFireworks::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleFireworks_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFireworks", "cc.ParticleFireworks:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleFireworks::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFireworks(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleFireworks, "ParticleFireworks", "cc.ParticleFireworks",
		cc::ParticleFireworks, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleFireworks_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleFireworks_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleFireworks_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleFireworks_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSun_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleSun::*)()>(&cc::ParticleSun::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSun_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleSun::*)(int)>(&cc::ParticleSun::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSun_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSun::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleSun_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSun", "cc.ParticleSun:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSun::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSun(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSun, "ParticleSun", "cc.ParticleSun",
		cc::ParticleSun, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleSun_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleSun_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleSun_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSun_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleGalaxy_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleGalaxy::*)()>(&cc::ParticleGalaxy::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleGalaxy_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleGalaxy::*)(int)>(&cc::ParticleGalaxy::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleGalaxy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleGalaxy::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleGalaxy_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleGalaxy", "cc.ParticleGalaxy:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleGalaxy::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleGalaxy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleGalaxy, "ParticleGalaxy", "cc.ParticleGalaxy",
		cc::ParticleGalaxy, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleGalaxy_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleGalaxy_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleGalaxy_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleGalaxy_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleFlower_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleFlower::*)()>(&cc::ParticleFlower::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleFlower_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleFlower::*)(int)>(&cc::ParticleFlower::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleFlower_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleFlower::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleFlower_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleFlower", "cc.ParticleFlower:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleFlower::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleFlower(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleFlower, "ParticleFlower", "cc.ParticleFlower",
		cc::ParticleFlower, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleFlower_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleFlower_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleFlower_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleFlower_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleMeteor_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleMeteor::*)()>(&cc::ParticleMeteor::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleMeteor_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleMeteor::*)(int)>(&cc::ParticleMeteor::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleMeteor_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleMeteor::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleMeteor_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleMeteor", "cc.ParticleMeteor:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleMeteor::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleMeteor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleMeteor, "ParticleMeteor", "cc.ParticleMeteor",
		cc::ParticleMeteor, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleMeteor_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleMeteor_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleMeteor_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleMeteor_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSpiral_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleSpiral::*)()>(&cc::ParticleSpiral::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSpiral_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleSpiral::*)(int)>(&cc::ParticleSpiral::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSpiral_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSpiral::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleSpiral_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSpiral", "cc.ParticleSpiral:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSpiral::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSpiral(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSpiral, "ParticleSpiral", "cc.ParticleSpiral",
		cc::ParticleSpiral, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleSpiral_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleSpiral_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleSpiral_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSpiral_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleExplosion_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleExplosion::*)()>(&cc::ParticleExplosion::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleExplosion_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleExplosion::*)(int)>(&cc::ParticleExplosion::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleExplosion_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleExplosion::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleExplosion_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleExplosion", "cc.ParticleExplosion:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleExplosion::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleExplosion(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleExplosion, "ParticleExplosion", "cc.ParticleExplosion",
		cc::ParticleExplosion, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleExplosion_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleExplosion_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleExplosion_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleExplosion_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSmoke_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleSmoke::*)()>(&cc::ParticleSmoke::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSmoke_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleSmoke::*)(int)>(&cc::ParticleSmoke::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSmoke_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSmoke::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleSmoke_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSmoke", "cc.ParticleSmoke:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSmoke::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSmoke(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSmoke, "ParticleSmoke", "cc.ParticleSmoke",
		cc::ParticleSmoke, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleSmoke_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleSmoke_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleSmoke_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSmoke_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleSnow_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleSnow::*)()>(&cc::ParticleSnow::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleSnow_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleSnow::*)(int)>(&cc::ParticleSnow::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleSnow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleSnow::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleSnow_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSnow", "cc.ParticleSnow:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleSnow::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSnow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleSnow, "ParticleSnow", "cc.ParticleSnow",
		cc::ParticleSnow, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleSnow_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleSnow_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleSnow_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleSnow_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParticleRain_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ParticleRain::*)()>(&cc::ParticleRain::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ParticleRain_initWithTotalParticles_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:initWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ParticleRain::*)(int)>(&cc::ParticleRain::initWithTotalParticles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParticleRain_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:create");
	LUA_TRY_INVOKE_R(0, &cc::ParticleRain::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_ParticleRain_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleRain", "cc.ParticleRain:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, &cc::ParticleRain::createWithTotalParticles);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleRain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParticleRain, "ParticleRain", "cc.ParticleRain",
		cc::ParticleRain, "cc.ParticleSystemQuad",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_ParticleRain_init_1);
	LUA_METHOD("initWithTotalParticles", lua_cc_ParticleRain_initWithTotalParticles_1);
	LUA_METHOD("create", lua_cc_ParticleRain_create);
	LUA_METHOD("createWithTotalParticles", lua_cc_ParticleRain_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ProgressTimer_getBarChangeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getBarChangeRate");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::getBarChangeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_getMidpoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getMidpoint");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::getMidpoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_getPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getPercentage");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::getPercentage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getSprite");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::getSprite);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getType");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::getType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_initWithSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:initWithSprite");
	LUA_TRY_INVOKE_R(1, &cc::ProgressTimer::initWithSprite);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_isReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:isReverseDirection");
	LUA_TRY_INVOKE_R(0, &cc::ProgressTimer::isReverseDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProgressTimer_setBarChangeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setBarChangeRate");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setBarChangeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_setMidpoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setMidpoint");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setMidpoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_setPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setPercentage");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setPercentage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_setReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setReverseDirection");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setReverseDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_setSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setSprite");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setSprite);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_setType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setType");
	LUA_TRY_INVOKE(1, &cc::ProgressTimer::setType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProgressTimer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:create");
	LUA_TRY_INVOKE_R(1, &cc::ProgressTimer::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccProgressTimer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ProgressTimer, "ProgressTimer", "cc.ProgressTimer",
		cc::ProgressTimer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBarChangeRate", lua_cc_ProgressTimer_getBarChangeRate);
	LUA_METHOD("getMidpoint", lua_cc_ProgressTimer_getMidpoint);
	LUA_METHOD("getPercentage", lua_cc_ProgressTimer_getPercentage);
	LUA_METHOD("getSprite", lua_cc_ProgressTimer_getSprite);
	LUA_METHOD("getType", lua_cc_ProgressTimer_getType);
	LUA_METHOD("initWithSprite", lua_cc_ProgressTimer_initWithSprite);
	LUA_METHOD("isReverseDirection", lua_cc_ProgressTimer_isReverseDirection);
	LUA_METHOD("setBarChangeRate", lua_cc_ProgressTimer_setBarChangeRate);
	LUA_METHOD("setMidpoint", lua_cc_ProgressTimer_setMidpoint);
	LUA_METHOD("setPercentage", lua_cc_ProgressTimer_setPercentage);
	LUA_METHOD("setReverseDirection", lua_cc_ProgressTimer_setReverseDirection);
	LUA_METHOD("setSprite", lua_cc_ProgressTimer_setSprite);
	LUA_METHOD("setType", lua_cc_ProgressTimer_setType);
	LUA_METHOD("create", lua_cc_ProgressTimer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ProtectedNode_addProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:addProtectedChild");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::ProtectedNode::*)(cc::Node*, int, int)>(&cc::ProtectedNode::addProtectedChild)));
	LUA_TRY_INVOKE(2, (static_cast<void(cc::ProtectedNode::*)(cc::Node*, int)>(&cc::ProtectedNode::addProtectedChild)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::ProtectedNode::*)(cc::Node*)>(&cc::ProtectedNode::addProtectedChild));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_ProtectedNode_disableCascadeColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:disableCascadeColor");
	LUA_TRY_INVOKE(0, &cc::ProtectedNode::disableCascadeColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProtectedNode_disableCascadeOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:disableCascadeOpacity");
	LUA_TRY_INVOKE(0, &cc::ProtectedNode::disableCascadeOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProtectedNode_getProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:getProtectedChildByTag");
	LUA_TRY_INVOKE_R(1, &cc::ProtectedNode::getProtectedChildByTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProtectedNode_removeAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildren");
	LUA_TRY_INVOKE(0, &cc::ProtectedNode::removeAllProtectedChildren);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProtectedNode_removeAllProtectedChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::ProtectedNode::removeAllProtectedChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ProtectedNode_removeProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChild");
	LUA_TRY_INVOKE(2, &cc::ProtectedNode::removeProtectedChild);
	LUA_TRY_INVOKE(1, ([](cc::ProtectedNode* obj,cc::Node* arg0){{return obj->removeProtectedChild(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_ProtectedNode_removeProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChildByTag");
	LUA_TRY_INVOKE(2, &cc::ProtectedNode::removeProtectedChildByTag);
	LUA_TRY_INVOKE(1, ([](cc::ProtectedNode* obj,int arg0){{return obj->removeProtectedChildByTag(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_ProtectedNode_reorderProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:reorderProtectedChild");
	LUA_TRY_INVOKE(2, &cc::ProtectedNode::reorderProtectedChild);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_ProtectedNode_sortAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:sortAllProtectedChildren");
	LUA_TRY_INVOKE(0, &cc::ProtectedNode::sortAllProtectedChildren);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ProtectedNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:create");
	LUA_TRY_INVOKE_R(0, &cc::ProtectedNode::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccProtectedNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ProtectedNode, "ProtectedNode", "cc.ProtectedNode",
		cc::ProtectedNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addProtectedChild", lua_cc_ProtectedNode_addProtectedChild);
	LUA_METHOD("disableCascadeColor", lua_cc_ProtectedNode_disableCascadeColor);
	LUA_METHOD("disableCascadeOpacity", lua_cc_ProtectedNode_disableCascadeOpacity);
	LUA_METHOD("getProtectedChildByTag", lua_cc_ProtectedNode_getProtectedChildByTag);
	LUA_METHOD("removeAllProtectedChildren", lua_cc_ProtectedNode_removeAllProtectedChildren);
	LUA_METHOD("removeAllProtectedChildrenWithCleanup", lua_cc_ProtectedNode_removeAllProtectedChildrenWithCleanup);
	LUA_METHOD("removeProtectedChild", lua_cc_ProtectedNode_removeProtectedChild);
	LUA_METHOD("removeProtectedChildByTag", lua_cc_ProtectedNode_removeProtectedChildByTag);
	LUA_METHOD("reorderProtectedChild", lua_cc_ProtectedNode_reorderProtectedChild);
	LUA_METHOD("sortAllProtectedChildren", lua_cc_ProtectedNode_sortAllProtectedChildren);
	LUA_METHOD("create", lua_cc_ProtectedNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
