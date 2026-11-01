#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_Core_ccApplication(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Application, "Application", "cc.Application",
		cocos2d::ApplicationProtocol, "cc.ApplicationProtocol",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GLViewImpl_createWithFullScreen(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithFullScreen");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::GLViewImpl*(*)(std::string_view)>(&cocos2d::GLViewImpl::createWithFullScreen));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccGLViewImpl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GLViewImpl, "GLViewImpl", "cc.GLViewImpl",
		cocos2d::GLView, "cc.GLView",
		nullptr, nullptr);
	LUA_METHOD("createWithFullScreen", lua_cocos2d_GLViewImpl_createWithFullScreen);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AnimationCache_addAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimation");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::AnimationCache::*)(cocos2d::Animation*, std::string_view)>(&cocos2d::AnimationCache::addAnimation));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_AnimationCache_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getAnimation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animation*(cocos2d::AnimationCache::*)(std::string_view)>(&cocos2d::AnimationCache::getAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::AnimationCache::*)()>(&cocos2d::AnimationCache::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationCache_removeAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:removeAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationCache::*)(std::string_view)>(&cocos2d::AnimationCache::removeAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationCache_destroyInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:destroyInstance");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocos2d::AnimationCache::destroyInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AnimationCache*(*)()>(&cocos2d::AnimationCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccAnimationCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationCache, "AnimationCache", "cc.AnimationCache",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAnimation", lua_cocos2d_AnimationCache_addAnimation);
	LUA_METHOD("getAnimation", lua_cocos2d_AnimationCache_getAnimation);
	LUA_METHOD("init", lua_cocos2d_AnimationCache_init);
	LUA_METHOD("removeAnimation", lua_cocos2d_AnimationCache_removeAnimation);
	LUA_METHOD("destroyInstance", lua_cocos2d_AnimationCache_destroyInstance);
	LUA_METHOD("getInstance", lua_cocos2d_AnimationCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:addSpriteWithoutQuad");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::SpriteBatchNode*(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int, int)>(&cocos2d::SpriteBatchNode::addSpriteWithoutQuad));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SpriteBatchNode_appendChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:appendChild");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::appendChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_atlasIndexForChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:atlasIndexForChild");
	LUA_TRY_INVOKE_R(2, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int)>(&cocos2d::SpriteBatchNode::atlasIndexForChild));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_highestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:highestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::highestAtlasIndexInChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_increaseAtlasCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:increaseAtlasCapacity");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::increaseAtlasCapacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:lowestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::lowestAtlasIndexInChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_removeSpriteFromAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeSpriteFromAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::removeSpriteFromAtlas));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_reorderBatch(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reorderBatch");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(bool)>(&cocos2d::SpriteBatchNode::reorderBatch));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccSpriteBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteBatchNode, "SpriteBatchNode", "cc.SpriteBatchNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addSpriteWithoutQuad", lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad);
	LUA_METHOD("appendChild", lua_cocos2d_SpriteBatchNode_appendChild);
	LUA_METHOD("atlasIndexForChild", lua_cocos2d_SpriteBatchNode_atlasIndexForChild);
	LUA_METHOD("highestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_highestAtlasIndexInChild);
	LUA_METHOD("increaseAtlasCapacity", lua_cocos2d_SpriteBatchNode_increaseAtlasCapacity);
	LUA_METHOD("lowestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild);
	LUA_METHOD("removeSpriteFromAtlas", lua_cocos2d_SpriteBatchNode_removeSpriteFromAtlas);
	LUA_METHOD("reorderBatch", lua_cocos2d_SpriteBatchNode_reorderBatch);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParallaxNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParallaxNode*(*)()>(&cocos2d::ParallaxNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParallaxNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParallaxNode, "ParallaxNode", "cc.ParallaxNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ParallaxNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXObjectGroup_getGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getGroupName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getGroupName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_setGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setGroupName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(std::string_view)>(&cocos2d::TMXObjectGroup::setGroupName));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXObjectGroup(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXObjectGroup, "TMXObjectGroup", "cc.TMXObjectGroup",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getGroupName", lua_cocos2d_TMXObjectGroup_getGroupName);
	LUA_METHOD("setGroupName", lua_cocos2d_TMXObjectGroup_setGroupName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTMXLayerInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXLayerInfo, "TMXLayerInfo", "cc.TMXLayerInfo",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTMXTilesetInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTilesetInfo, "TMXTilesetInfo", "cc.TMXTilesetInfo",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXMapInfo_getCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getCurrentString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getCurrentString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getExternalTilesetFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getExternalTilesetFileName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getExternalTilesetFileName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getHexSideLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getHexSideLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayerAttribs");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getLayerAttribs));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getOrientation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getOrientation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentElement");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getParentElement));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentGID");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getParentGID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerAxis");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getStaggerAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getStaggerIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTMXFileName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTMXFileName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::initWithTMXFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithXML");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::initWithXML));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TMXMapInfo_isStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:isStoringCharacters");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::isStoringCharacters));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_parseXMLFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::parseXMLFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_parseXMLString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLString");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::parseXMLString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setCurrentString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::setCurrentString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setHexSideLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setHexSideLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayerAttribs");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setLayerAttribs));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentElement");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setParentElement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentGID");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setParentGID));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerAxis");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setStaggerAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setStaggerIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStoringCharacters");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(bool)>(&cocos2d::TMXMapInfo::setStoringCharacters));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTMXFileName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::setTMXFileName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXMapInfo*(*)(std::string_view)>(&cocos2d::TMXMapInfo::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:createWithXML");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TMXMapInfo*(*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::createWithXML));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTMXMapInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXMapInfo, "TMXMapInfo", "cc.TMXMapInfo",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentString", lua_cocos2d_TMXMapInfo_getCurrentString);
	LUA_METHOD("getExternalTilesetFileName", lua_cocos2d_TMXMapInfo_getExternalTilesetFileName);
	LUA_METHOD("getHexSideLength", lua_cocos2d_TMXMapInfo_getHexSideLength);
	LUA_METHOD("getLayerAttribs", lua_cocos2d_TMXMapInfo_getLayerAttribs);
	LUA_METHOD("getOrientation", lua_cocos2d_TMXMapInfo_getOrientation);
	LUA_METHOD("getParentElement", lua_cocos2d_TMXMapInfo_getParentElement);
	LUA_METHOD("getParentGID", lua_cocos2d_TMXMapInfo_getParentGID);
	LUA_METHOD("getStaggerAxis", lua_cocos2d_TMXMapInfo_getStaggerAxis);
	LUA_METHOD("getStaggerIndex", lua_cocos2d_TMXMapInfo_getStaggerIndex);
	LUA_METHOD("getTMXFileName", lua_cocos2d_TMXMapInfo_getTMXFileName);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_TMXMapInfo_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_TMXMapInfo_initWithXML);
	LUA_METHOD("isStoringCharacters", lua_cocos2d_TMXMapInfo_isStoringCharacters);
	LUA_METHOD("parseXMLFile", lua_cocos2d_TMXMapInfo_parseXMLFile);
	LUA_METHOD("parseXMLString", lua_cocos2d_TMXMapInfo_parseXMLString);
	LUA_METHOD("setCurrentString", lua_cocos2d_TMXMapInfo_setCurrentString);
	LUA_METHOD("setHexSideLength", lua_cocos2d_TMXMapInfo_setHexSideLength);
	LUA_METHOD("setLayerAttribs", lua_cocos2d_TMXMapInfo_setLayerAttribs);
	LUA_METHOD("setOrientation", lua_cocos2d_TMXMapInfo_setOrientation);
	LUA_METHOD("setParentElement", lua_cocos2d_TMXMapInfo_setParentElement);
	LUA_METHOD("setParentGID", lua_cocos2d_TMXMapInfo_setParentGID);
	LUA_METHOD("setStaggerAxis", lua_cocos2d_TMXMapInfo_setStaggerAxis);
	LUA_METHOD("setStaggerIndex", lua_cocos2d_TMXMapInfo_setStaggerIndex);
	LUA_METHOD("setStoringCharacters", lua_cocos2d_TMXMapInfo_setStoringCharacters);
	LUA_METHOD("setTMXFileName", lua_cocos2d_TMXMapInfo_setTMXFileName);
	LUA_METHOD("create", lua_cocos2d_TMXMapInfo_create);
	LUA_METHOD("createWithXML", lua_cocos2d_TMXMapInfo_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TileMapAtlas_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:initWithTileFile");
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::TileMapAtlas::*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::initWithTileFile));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TileMapAtlas_releaseMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:releaseMap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TileMapAtlas::*)()>(&cocos2d::TileMapAtlas::releaseMap));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TileMapAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:create");
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::TileMapAtlas*(*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::create));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTileMapAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TileMapAtlas, "TileMapAtlas", "cc.TileMapAtlas",
		cocos2d::AtlasNode, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_METHOD("initWithTileFile", lua_cocos2d_TileMapAtlas_initWithTileFile);
	LUA_METHOD("releaseMap", lua_cocos2d_TileMapAtlas_releaseMap);
	LUA_METHOD("create", lua_cocos2d_TileMapAtlas_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FastTMXLayer_getLayerName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::FastTMXLayer::*)()>(&cocos2d::FastTMXLayer::getLayerName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getLayerOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerOrientation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getLayerOrientation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getTileAnimManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileAnimManager");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TMXTileAnimManager*(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getTileAnimManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getTileSet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileSet");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TMXTilesetInfo*(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getTileSet));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_hasTileAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:hasTileAnimation");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::hasTileAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_initWithTilesetInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:initWithTilesetInfo");
	LUA_TRY_INVOKE_R(3, static_cast<bool(cocos2d::FastTMXLayer::*)(cocos2d::TMXTilesetInfo*, cocos2d::TMXLayerInfo*, cocos2d::TMXMapInfo*)>(&cocos2d::FastTMXLayer::initWithTilesetInfo));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_FastTMXLayer_setLayerName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(std::string_view)>(&cocos2d::FastTMXLayer::setLayerName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setLayerOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(int)>(&cocos2d::FastTMXLayer::setLayerOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setTileSet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setTileSet");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(cocos2d::TMXTilesetInfo*)>(&cocos2d::FastTMXLayer::setTileSet));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setupTiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setupTiles");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::FastTMXLayer::*)()>(&cocos2d::FastTMXLayer::setupTiles));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::FastTMXLayer*(*)(cocos2d::TMXTilesetInfo*, cocos2d::TMXLayerInfo*, cocos2d::TMXMapInfo*)>(&cocos2d::FastTMXLayer::create));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccFastTMXLayer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FastTMXLayer, "FastTMXLayer", "cc.FastTMXLayer",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayerName", lua_cocos2d_FastTMXLayer_getLayerName);
	LUA_METHOD("getLayerOrientation", lua_cocos2d_FastTMXLayer_getLayerOrientation);
	LUA_METHOD("getTileAnimManager", lua_cocos2d_FastTMXLayer_getTileAnimManager);
	LUA_METHOD("getTileSet", lua_cocos2d_FastTMXLayer_getTileSet);
	LUA_METHOD("hasTileAnimation", lua_cocos2d_FastTMXLayer_hasTileAnimation);
	LUA_METHOD("initWithTilesetInfo", lua_cocos2d_FastTMXLayer_initWithTilesetInfo);
	LUA_METHOD("setLayerName", lua_cocos2d_FastTMXLayer_setLayerName);
	LUA_METHOD("setLayerOrientation", lua_cocos2d_FastTMXLayer_setLayerOrientation);
	LUA_METHOD("setTileSet", lua_cocos2d_FastTMXLayer_setTileSet);
	LUA_METHOD("setupTiles", lua_cocos2d_FastTMXLayer_setupTiles);
	LUA_METHOD("create", lua_cocos2d_FastTMXLayer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXTileAnimTask_isRunning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:isRunning");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::TMXTileAnimTask::*)()const>(&cocos2d::TMXTileAnimTask::isRunning));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimTask_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:start");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimTask::*)()>(&cocos2d::TMXTileAnimTask::start));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimTask_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimTask::*)()>(&cocos2d::TMXTileAnimTask::stop));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccTMXTileAnimTask(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTileAnimTask, "TMXTileAnimTask", "cc.TMXTileAnimTask",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("isRunning", lua_cocos2d_TMXTileAnimTask_isRunning);
	LUA_METHOD("start", lua_cocos2d_TMXTileAnimTask_start);
	LUA_METHOD("stop", lua_cocos2d_TMXTileAnimTask_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
