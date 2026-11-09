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

int lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:addSpriteWithoutQuad");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SpriteBatchNode*(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int, int)>(&cocos2d::SpriteBatchNode::addSpriteWithoutQuad)));
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
	LUA_TRY_INVOKE_R(2, (static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int)>(&cocos2d::SpriteBatchNode::atlasIndexForChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getDescendants(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getDescendants");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<cocos2d::Sprite *>&(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getDescendants));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureAtlas*(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::getTextureAtlas));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_SpriteBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteBatchNode::*)(std::string_view, ssize_t)>(&cocos2d::SpriteBatchNode::initWithFile)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::SpriteBatchNode* obj,std::string_view arg0){{return obj->initWithFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteBatchNode::*)(cocos2d::Texture2D*, ssize_t)>(&cocos2d::SpriteBatchNode::initWithTexture)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::SpriteBatchNode* obj,cocos2d::Texture2D* arg0){{return obj->initWithTexture(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_insertQuadFromSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:insertQuadFromSprite");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, ssize_t)>(&cocos2d::SpriteBatchNode::insertQuadFromSprite)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:lowestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::lowestAtlasIndexInChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_rebuildIndexInOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:rebuildIndexInOrder");
	LUA_TRY_INVOKE_R(2, (static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, ssize_t)>(&cocos2d::SpriteBatchNode::rebuildIndexInOrder)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(bool)>(&cocos2d::SpriteBatchNode::removeAllChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t, bool)>(&cocos2d::SpriteBatchNode::removeChildAtIndex)));
	LUA_INVOKE_FOOTER("2");
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
int lua_cocos2d_SpriteBatchNode_reserveCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reserveCapacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t)>(&cocos2d::SpriteBatchNode::reserveCapacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(const cocos2d::BlendFunc&)>(&cocos2d::SpriteBatchNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Texture2D*)>(&cocos2d::SpriteBatchNode::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::SpriteBatchNode::setTextureAtlas));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteBatchNode*(*)(std::string_view, ssize_t)>(&cocos2d::SpriteBatchNode::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::SpriteBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteBatchNode*(*)(cocos2d::Texture2D*, ssize_t)>(&cocos2d::SpriteBatchNode::createWithTexture)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::SpriteBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccSpriteBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteBatchNode, "SpriteBatchNode", "cc.SpriteBatchNode",
		cocos2d::SpriteBatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addSpriteWithoutQuad", lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad);
	LUA_METHOD("appendChild", lua_cocos2d_SpriteBatchNode_appendChild);
	LUA_METHOD("atlasIndexForChild", lua_cocos2d_SpriteBatchNode_atlasIndexForChild);
	LUA_METHOD("getBlendFunc", lua_cocos2d_SpriteBatchNode_getBlendFunc);
	LUA_METHOD("getDescendants", lua_cocos2d_SpriteBatchNode_getDescendants);
	LUA_METHOD("getTexture", lua_cocos2d_SpriteBatchNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cocos2d_SpriteBatchNode_getTextureAtlas);
	LUA_METHOD("highestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_highestAtlasIndexInChild);
	LUA_METHOD("increaseAtlasCapacity", lua_cocos2d_SpriteBatchNode_increaseAtlasCapacity);
	LUA_METHOD("initWithFile", lua_cocos2d_SpriteBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cocos2d_SpriteBatchNode_initWithTexture);
	LUA_METHOD("insertQuadFromSprite", lua_cocos2d_SpriteBatchNode_insertQuadFromSprite);
	LUA_METHOD("lowestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild);
	LUA_METHOD("rebuildIndexInOrder", lua_cocos2d_SpriteBatchNode_rebuildIndexInOrder);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cocos2d_SpriteBatchNode_removeAllChildrenWithCleanup);
	LUA_METHOD("removeChildAtIndex", lua_cocos2d_SpriteBatchNode_removeChildAtIndex);
	LUA_METHOD("removeSpriteFromAtlas", lua_cocos2d_SpriteBatchNode_removeSpriteFromAtlas);
	LUA_METHOD("reorderBatch", lua_cocos2d_SpriteBatchNode_reorderBatch);
	LUA_METHOD("reserveCapacity", lua_cocos2d_SpriteBatchNode_reserveCapacity);
	LUA_METHOD("setBlendFunc", lua_cocos2d_SpriteBatchNode_setBlendFunc);
	LUA_METHOD("setTexture", lua_cocos2d_SpriteBatchNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cocos2d_SpriteBatchNode_setTextureAtlas);
	LUA_METHOD("create", lua_cocos2d_SpriteBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_SpriteBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParallaxNode_addChild_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:addChild");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ParallaxNode::*)(cocos2d::Node*, int, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::ParallaxNode::addChild)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ParallaxNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParallaxNode::*)(bool)>(&cocos2d::ParallaxNode::removeAllChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParallaxNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addChild", lua_cocos2d_ParallaxNode_addChild_1);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cocos2d_ParallaxNode_removeAllChildrenWithCleanup);
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
int lua_cocos2d_TMXObjectGroup_getObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObject");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueMap(cocos2d::TMXObjectGroup::*)(std::string_view)const>(&cocos2d::TMXObjectGroup::getObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_getObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObjects");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueVector&(cocos2d::TMXObjectGroup::*)()>(&cocos2d::TMXObjectGroup::getObjects));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueVector&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getObjects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getPositionOffset");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getPositionOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXObjectGroup::*)()>(&cocos2d::TMXObjectGroup::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperty");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::TMXObjectGroup::*)(std::string_view)const>(&cocos2d::TMXObjectGroup::getProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setGroupName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(std::string_view)>(&cocos2d::TMXObjectGroup::setGroupName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setObjects");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::ValueVector&)>(&cocos2d::TMXObjectGroup::setObjects));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setPositionOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::Vec2&)>(&cocos2d::TMXObjectGroup::setPositionOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::ValueMap&)>(&cocos2d::TMXObjectGroup::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXObjectGroup(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXObjectGroup, "TMXObjectGroup", "cc.TMXObjectGroup",
		cocos2d::TMXObjectGroup, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getGroupName", lua_cocos2d_TMXObjectGroup_getGroupName);
	LUA_METHOD("getObject", lua_cocos2d_TMXObjectGroup_getObject);
	LUA_METHOD("getObjects", lua_cocos2d_TMXObjectGroup_getObjects);
	LUA_METHOD("getPositionOffset", lua_cocos2d_TMXObjectGroup_getPositionOffset);
	LUA_METHOD("getProperties", lua_cocos2d_TMXObjectGroup_getProperties);
	LUA_METHOD("getProperty", lua_cocos2d_TMXObjectGroup_getProperty);
	LUA_METHOD("setGroupName", lua_cocos2d_TMXObjectGroup_setGroupName);
	LUA_METHOD("setObjects", lua_cocos2d_TMXObjectGroup_setObjects);
	LUA_METHOD("setPositionOffset", lua_cocos2d_TMXObjectGroup_setPositionOffset);
	LUA_METHOD("setProperties", lua_cocos2d_TMXObjectGroup_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXLayerInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:getProperties");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXLayerInfo::*)()>(&cocos2d::TMXLayerInfo::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXLayerInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXLayerInfo::*)(cocos2d::ValueMap)>(&cocos2d::TMXLayerInfo::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXLayerInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXLayerInfo, "TMXLayerInfo", "cc.TMXLayerInfo",
		cocos2d::TMXLayerInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getProperties", lua_cocos2d_TMXLayerInfo_getProperties);
	LUA_METHOD("setProperties", lua_cocos2d_TMXLayerInfo_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXTilesetInfo_getRectForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTilesetInfo", "cc.TMXTilesetInfo:getRectForGID");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Rect(cocos2d::TMXTilesetInfo::*)(uint32_t)>(&cocos2d::TMXTilesetInfo::getRectForGID));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTilesetInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTilesetInfo, "TMXTilesetInfo", "cc.TMXTilesetInfo",
		cocos2d::TMXTilesetInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getRectForGID", lua_cocos2d_TMXTilesetInfo_getRectForGID);
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
int lua_cocos2d_TMXMapInfo_getLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayers");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXLayerInfo *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getLayers));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXLayerInfo *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getLayers));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getMapSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getMapSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getObjectGroups));
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
int lua_cocos2d_TMXMapInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getProperties));
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
int lua_cocos2d_TMXMapInfo_getTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileProperties");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ValueMapIntKey&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getTileProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTileSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTilesets");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXTilesetInfo *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getTilesets));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXTilesetInfo *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTilesets));
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
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::initWithXML)));
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
int lua_cocos2d_TMXMapInfo_setLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayers");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXLayerInfo *>&)>(&cocos2d::TMXMapInfo::setLayers));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setMapSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vec2&)>(&cocos2d::TMXMapInfo::setMapSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setObjectGroups");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)>(&cocos2d::TMXMapInfo::setObjectGroups));
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
int lua_cocos2d_TMXMapInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::ValueMap&)>(&cocos2d::TMXMapInfo::setProperties));
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
int lua_cocos2d_TMXMapInfo_setTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::ValueMapIntKey&)>(&cocos2d::TMXMapInfo::setTileProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vec2&)>(&cocos2d::TMXMapInfo::setTileSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTilesets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXTilesetInfo *>&)>(&cocos2d::TMXMapInfo::setTilesets));
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TMXMapInfo*(*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::createWithXML)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTMXMapInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXMapInfo, "TMXMapInfo", "cc.TMXMapInfo",
		cocos2d::TMXMapInfo, "",
		nullptr, nullptr);
	LUA_METHOD("getCurrentString", lua_cocos2d_TMXMapInfo_getCurrentString);
	LUA_METHOD("getExternalTilesetFileName", lua_cocos2d_TMXMapInfo_getExternalTilesetFileName);
	LUA_METHOD("getHexSideLength", lua_cocos2d_TMXMapInfo_getHexSideLength);
	LUA_METHOD("getLayerAttribs", lua_cocos2d_TMXMapInfo_getLayerAttribs);
	LUA_METHOD("getLayers", lua_cocos2d_TMXMapInfo_getLayers);
	LUA_METHOD("getMapSize", lua_cocos2d_TMXMapInfo_getMapSize);
	LUA_METHOD("getObjectGroups", lua_cocos2d_TMXMapInfo_getObjectGroups);
	LUA_METHOD("getOrientation", lua_cocos2d_TMXMapInfo_getOrientation);
	LUA_METHOD("getParentElement", lua_cocos2d_TMXMapInfo_getParentElement);
	LUA_METHOD("getParentGID", lua_cocos2d_TMXMapInfo_getParentGID);
	LUA_METHOD("getProperties", lua_cocos2d_TMXMapInfo_getProperties);
	LUA_METHOD("getStaggerAxis", lua_cocos2d_TMXMapInfo_getStaggerAxis);
	LUA_METHOD("getStaggerIndex", lua_cocos2d_TMXMapInfo_getStaggerIndex);
	LUA_METHOD("getTMXFileName", lua_cocos2d_TMXMapInfo_getTMXFileName);
	LUA_METHOD("getTileProperties", lua_cocos2d_TMXMapInfo_getTileProperties);
	LUA_METHOD("getTileSize", lua_cocos2d_TMXMapInfo_getTileSize);
	LUA_METHOD("getTilesets", lua_cocos2d_TMXMapInfo_getTilesets);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_TMXMapInfo_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_TMXMapInfo_initWithXML);
	LUA_METHOD("isStoringCharacters", lua_cocos2d_TMXMapInfo_isStoringCharacters);
	LUA_METHOD("parseXMLFile", lua_cocos2d_TMXMapInfo_parseXMLFile);
	LUA_METHOD("parseXMLString", lua_cocos2d_TMXMapInfo_parseXMLString);
	LUA_METHOD("setCurrentString", lua_cocos2d_TMXMapInfo_setCurrentString);
	LUA_METHOD("setHexSideLength", lua_cocos2d_TMXMapInfo_setHexSideLength);
	LUA_METHOD("setLayerAttribs", lua_cocos2d_TMXMapInfo_setLayerAttribs);
	LUA_METHOD("setLayers", lua_cocos2d_TMXMapInfo_setLayers);
	LUA_METHOD("setMapSize", lua_cocos2d_TMXMapInfo_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cocos2d_TMXMapInfo_setObjectGroups);
	LUA_METHOD("setOrientation", lua_cocos2d_TMXMapInfo_setOrientation);
	LUA_METHOD("setParentElement", lua_cocos2d_TMXMapInfo_setParentElement);
	LUA_METHOD("setParentGID", lua_cocos2d_TMXMapInfo_setParentGID);
	LUA_METHOD("setProperties", lua_cocos2d_TMXMapInfo_setProperties);
	LUA_METHOD("setStaggerAxis", lua_cocos2d_TMXMapInfo_setStaggerAxis);
	LUA_METHOD("setStaggerIndex", lua_cocos2d_TMXMapInfo_setStaggerIndex);
	LUA_METHOD("setStoringCharacters", lua_cocos2d_TMXMapInfo_setStoringCharacters);
	LUA_METHOD("setTMXFileName", lua_cocos2d_TMXMapInfo_setTMXFileName);
	LUA_METHOD("setTileProperties", lua_cocos2d_TMXMapInfo_setTileProperties);
	LUA_METHOD("setTileSize", lua_cocos2d_TMXMapInfo_setTileSize);
	LUA_METHOD("setTilesets", lua_cocos2d_TMXMapInfo_setTilesets);
	LUA_METHOD("create", lua_cocos2d_TMXMapInfo_create);
	LUA_METHOD("createWithXML", lua_cocos2d_TMXMapInfo_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TileMapAtlas_getTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:getTileAt");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Color3B(cocos2d::TileMapAtlas::*)(const cocos2d::Vec2&)const>(&cocos2d::TileMapAtlas::getTileAt));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TileMapAtlas_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:initWithTileFile");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TileMapAtlas::*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::initWithTileFile)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TileMapAtlas_releaseMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:releaseMap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TileMapAtlas::*)()>(&cocos2d::TileMapAtlas::releaseMap));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TileMapAtlas_setTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:setTile");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::TileMapAtlas::*)(const cocos2d::Color3B&, const cocos2d::Vec2&)>(&cocos2d::TileMapAtlas::setTile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TileMapAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TileMapAtlas*(*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTileMapAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TileMapAtlas, "TileMapAtlas", "cc.TileMapAtlas",
		cocos2d::TileMapAtlas, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_METHOD("getTileAt", lua_cocos2d_TileMapAtlas_getTileAt);
	LUA_METHOD("initWithTileFile", lua_cocos2d_TileMapAtlas_initWithTileFile);
	LUA_METHOD("releaseMap", lua_cocos2d_TileMapAtlas_releaseMap);
	LUA_METHOD("setTile", lua_cocos2d_TileMapAtlas_setTile);
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
int lua_cocos2d_FastTMXLayer_getLayerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getLayerSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getMapTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getMapTileSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getMapTileSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getPositionAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getPositionAt");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::FastTMXLayer::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::getPositionAt));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::FastTMXLayer::*)()>(&cocos2d::FastTMXLayer::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getProperty");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::FastTMXLayer::*)(std::string_view)const>(&cocos2d::FastTMXLayer::getProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_getTileAnimManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileAnimManager");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TMXTileAnimManager*(cocos2d::FastTMXLayer::*)()const>(&cocos2d::FastTMXLayer::getTileAnimManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXLayer_getTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileAt");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Sprite*(cocos2d::FastTMXLayer::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::getTileAt));
	LUA_INVOKE_FOOTER("1");
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
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::FastTMXLayer::*)(cocos2d::TMXTilesetInfo*, cocos2d::TMXLayerInfo*, cocos2d::TMXMapInfo*)>(&cocos2d::FastTMXLayer::initWithTilesetInfo)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_FastTMXLayer_removeTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:removeTileAt");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::removeTileAt));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_FastTMXLayer_setLayerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::setLayerSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setMapTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setMapTileSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::setMapTileSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(const cocos2d::ValueMap&)>(&cocos2d::FastTMXLayer::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setTileGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setTileGID");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FastTMXLayer::*)(int, const cocos2d::Vec2&, cocos2d::TMXTileFlags)>(&cocos2d::FastTMXLayer::setTileGID)));
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FastTMXLayer::*)(int, const cocos2d::Vec2&)>(&cocos2d::FastTMXLayer::setTileGID)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FastTMXLayer_setTileSet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setTileSet");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXLayer::*)(cocos2d::TMXTilesetInfo*)>(&cocos2d::FastTMXLayer::setTileSet));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXLayer_setupTileSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setupTileSprite");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FastTMXLayer::*)(cocos2d::Sprite*, const cocos2d::Vec2&, uint32_t)>(&cocos2d::FastTMXLayer::setupTileSprite)));
	LUA_INVOKE_FOOTER("3");
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
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::FastTMXLayer*(*)(cocos2d::TMXTilesetInfo*, cocos2d::TMXLayerInfo*, cocos2d::TMXMapInfo*)>(&cocos2d::FastTMXLayer::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccFastTMXLayer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FastTMXLayer, "FastTMXLayer", "cc.FastTMXLayer",
		cocos2d::FastTMXLayer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayerName", lua_cocos2d_FastTMXLayer_getLayerName);
	LUA_METHOD("getLayerOrientation", lua_cocos2d_FastTMXLayer_getLayerOrientation);
	LUA_METHOD("getLayerSize", lua_cocos2d_FastTMXLayer_getLayerSize);
	LUA_METHOD("getMapTileSize", lua_cocos2d_FastTMXLayer_getMapTileSize);
	LUA_METHOD("getPositionAt", lua_cocos2d_FastTMXLayer_getPositionAt);
	LUA_METHOD("getProperties", lua_cocos2d_FastTMXLayer_getProperties);
	LUA_METHOD("getProperty", lua_cocos2d_FastTMXLayer_getProperty);
	LUA_METHOD("getTileAnimManager", lua_cocos2d_FastTMXLayer_getTileAnimManager);
	LUA_METHOD("getTileAt", lua_cocos2d_FastTMXLayer_getTileAt);
	LUA_METHOD("getTileSet", lua_cocos2d_FastTMXLayer_getTileSet);
	LUA_METHOD("hasTileAnimation", lua_cocos2d_FastTMXLayer_hasTileAnimation);
	LUA_METHOD("initWithTilesetInfo", lua_cocos2d_FastTMXLayer_initWithTilesetInfo);
	LUA_METHOD("removeTileAt", lua_cocos2d_FastTMXLayer_removeTileAt);
	LUA_METHOD("setLayerName", lua_cocos2d_FastTMXLayer_setLayerName);
	LUA_METHOD("setLayerOrientation", lua_cocos2d_FastTMXLayer_setLayerOrientation);
	LUA_METHOD("setLayerSize", lua_cocos2d_FastTMXLayer_setLayerSize);
	LUA_METHOD("setMapTileSize", lua_cocos2d_FastTMXLayer_setMapTileSize);
	LUA_METHOD("setProperties", lua_cocos2d_FastTMXLayer_setProperties);
	LUA_METHOD("setTileGID", lua_cocos2d_FastTMXLayer_setTileGID);
	LUA_METHOD("setTileSet", lua_cocos2d_FastTMXLayer_setTileSet);
	LUA_METHOD("setupTileSprite", lua_cocos2d_FastTMXLayer_setupTileSprite);
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
		cocos2d::TMXTileAnimTask, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("isRunning", lua_cocos2d_TMXTileAnimTask_isRunning);
	LUA_METHOD("start", lua_cocos2d_TMXTileAnimTask_start);
	LUA_METHOD("stop", lua_cocos2d_TMXTileAnimTask_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXTileAnimManager_getTasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:getTasks");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::TMXTileAnimTask *>&(cocos2d::TMXTileAnimManager::*)()const>(&cocos2d::TMXTileAnimManager::getTasks));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimManager_startAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:startAll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimManager::*)()>(&cocos2d::TMXTileAnimManager::startAll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimManager_stopAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:stopAll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimManager::*)()>(&cocos2d::TMXTileAnimManager::stopAll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXTileAnimManager*(*)(cocos2d::FastTMXLayer*)>(&cocos2d::TMXTileAnimManager::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTileAnimManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTileAnimManager, "TMXTileAnimManager", "cc.TMXTileAnimManager",
		cocos2d::TMXTileAnimManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getTasks", lua_cocos2d_TMXTileAnimManager_getTasks);
	LUA_METHOD("startAll", lua_cocos2d_TMXTileAnimManager_startAll);
	LUA_METHOD("stopAll", lua_cocos2d_TMXTileAnimManager_stopAll);
	LUA_METHOD("create", lua_cocos2d_TMXTileAnimManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FastTMXTiledMap_getLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayer");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FastTMXLayer*(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getLayer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getLayerCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayerCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getLayerCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapOrientation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapOrientation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getObjectGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroup");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXObjectGroup*(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getObjectGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::FastTMXTiledMap::*)()>(&cocos2d::FastTMXTiledMap::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getObjectGroups));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperties");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::ValueMap&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getPropertiesForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getPropertiesForGID");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(int)const>(&cocos2d::FastTMXTiledMap::getPropertiesForGID));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperty");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getResourceFile");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getResourceFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getTileSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getTileSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FastTMXTiledMap::*)(std::string_view)>(&cocos2d::FastTMXTiledMap::initWithTMXFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithXML");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FastTMXTiledMap::*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::initWithXML)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FastTMXTiledMap_setMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(int)>(&cocos2d::FastTMXTiledMap::setMapOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXTiledMap::setMapSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setObjectGroups");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)>(&cocos2d::FastTMXTiledMap::setObjectGroups));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::ValueMap&)>(&cocos2d::FastTMXTiledMap::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileAnimEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(bool)>(&cocos2d::FastTMXTiledMap::setTileAnimEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXTiledMap::setTileSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FastTMXTiledMap*(*)(std::string_view)>(&cocos2d::FastTMXTiledMap::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:createWithXML");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FastTMXTiledMap*(*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::createWithXML)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFastTMXTiledMap(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FastTMXTiledMap, "FastTMXTiledMap", "cc.FastTMXTiledMap",
		cocos2d::FastTMXTiledMap, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayer", lua_cocos2d_FastTMXTiledMap_getLayer);
	LUA_METHOD("getLayerCount", lua_cocos2d_FastTMXTiledMap_getLayerCount);
	LUA_METHOD("getMapOrientation", lua_cocos2d_FastTMXTiledMap_getMapOrientation);
	LUA_METHOD("getMapSize", lua_cocos2d_FastTMXTiledMap_getMapSize);
	LUA_METHOD("getObjectGroup", lua_cocos2d_FastTMXTiledMap_getObjectGroup);
	LUA_METHOD("getObjectGroups", lua_cocos2d_FastTMXTiledMap_getObjectGroups);
	LUA_METHOD("getProperties", lua_cocos2d_FastTMXTiledMap_getProperties);
	LUA_METHOD("getPropertiesForGID", lua_cocos2d_FastTMXTiledMap_getPropertiesForGID);
	LUA_METHOD("getProperty", lua_cocos2d_FastTMXTiledMap_getProperty);
	LUA_METHOD("getResourceFile", lua_cocos2d_FastTMXTiledMap_getResourceFile);
	LUA_METHOD("getTileSize", lua_cocos2d_FastTMXTiledMap_getTileSize);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_FastTMXTiledMap_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_FastTMXTiledMap_initWithXML);
	LUA_METHOD("setMapOrientation", lua_cocos2d_FastTMXTiledMap_setMapOrientation);
	LUA_METHOD("setMapSize", lua_cocos2d_FastTMXTiledMap_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cocos2d_FastTMXTiledMap_setObjectGroups);
	LUA_METHOD("setProperties", lua_cocos2d_FastTMXTiledMap_setProperties);
	LUA_METHOD("setTileAnimEnabled", lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled);
	LUA_METHOD("setTileSize", lua_cocos2d_FastTMXTiledMap_setTileSize);
	LUA_METHOD("create", lua_cocos2d_FastTMXTiledMap_create);
	LUA_METHOD("createWithXML", lua_cocos2d_FastTMXTiledMap_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MotionStreak3D_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getStroke");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getStroke));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getSweepAxis");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getSweepAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_MotionStreak3D_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::isStartingPositionInitialized));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:reset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MotionStreak3D::*)()>(&cocos2d::MotionStreak3D::reset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::BlendFunc&)>(&cocos2d::MotionStreak3D::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(bool)>(&cocos2d::MotionStreak3D::setStartingPositionInitialized));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStroke");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(float)>(&cocos2d::MotionStreak3D::setStroke));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setSweepAxis");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::Vec3&)>(&cocos2d::MotionStreak3D::setSweepAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:tintWithColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::Color3B&)>(&cocos2d::MotionStreak3D::tintWithColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak3D*(*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak3D*(*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak3D, "MotionStreak3D", "cc.MotionStreak3D",
		cocos2d::MotionStreak3D, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_MotionStreak3D_getBlendFunc);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak3D_getStroke);
	LUA_METHOD("getSweepAxis", lua_cocos2d_MotionStreak3D_getSweepAxis);
	LUA_METHOD("getTexture", lua_cocos2d_MotionStreak3D_getTexture);
	LUA_METHOD("initWithFade", lua_cocos2d_MotionStreak3D_initWithFade);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak3D_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak3D_reset);
	LUA_METHOD("setBlendFunc", lua_cocos2d_MotionStreak3D_setBlendFunc);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak3D_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak3D_setStroke);
	LUA_METHOD("setSweepAxis", lua_cocos2d_MotionStreak3D_setSweepAxis);
	LUA_METHOD("setTexture", lua_cocos2d_MotionStreak3D_setTexture);
	LUA_METHOD("tintWithColor", lua_cocos2d_MotionStreak3D_tintWithColor);
	LUA_METHOD("create", lua_cocos2d_MotionStreak3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
