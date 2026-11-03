#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_MenuItemSprite_getDisabledImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getDisabledImage");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::MenuItemSprite::*)()const>(&cocos2d::MenuItemSprite::getDisabledImage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemSprite_getNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getNormalImage");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::MenuItemSprite::*)()const>(&cocos2d::MenuItemSprite::getNormalImage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemSprite_getSelectedImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getSelectedImage");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::MenuItemSprite::*)()const>(&cocos2d::MenuItemSprite::getSelectedImage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemSprite_setDisabledImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setDisabledImage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemSprite::*)(cocos2d::Node*)>(&cocos2d::MenuItemSprite::setDisabledImage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemSprite_setNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setNormalImage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemSprite::*)(cocos2d::Node*)>(&cocos2d::MenuItemSprite::setNormalImage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemSprite_setSelectedImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setSelectedImage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemSprite::*)(cocos2d::Node*)>(&cocos2d::MenuItemSprite::setSelectedImage));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemSprite(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemSprite, "MenuItemSprite", "cc.MenuItemSprite",
		cocos2d::MenuItem, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("getDisabledImage", lua_cocos2d_MenuItemSprite_getDisabledImage);
	LUA_METHOD("getNormalImage", lua_cocos2d_MenuItemSprite_getNormalImage);
	LUA_METHOD("getSelectedImage", lua_cocos2d_MenuItemSprite_getSelectedImage);
	LUA_METHOD("setDisabledImage", lua_cocos2d_MenuItemSprite_setDisabledImage);
	LUA_METHOD("setNormalImage", lua_cocos2d_MenuItemSprite_setNormalImage);
	LUA_METHOD("setSelectedImage", lua_cocos2d_MenuItemSprite_setSelectedImage);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItemImage_setDisabledSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setDisabledSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemImage::*)(cocos2d::SpriteFrame*)>(&cocos2d::MenuItemImage::setDisabledSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemImage_setNormalSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setNormalSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemImage::*)(cocos2d::SpriteFrame*)>(&cocos2d::MenuItemImage::setNormalSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemImage_setSelectedSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setSelectedSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemImage::*)(cocos2d::SpriteFrame*)>(&cocos2d::MenuItemImage::setSelectedSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemImage, "MenuItemImage", "cc.MenuItemImage",
		cocos2d::MenuItemSprite, "cc.MenuItemSprite",
		nullptr, nullptr);
	LUA_METHOD("setDisabledSpriteFrame", lua_cocos2d_MenuItemImage_setDisabledSpriteFrame);
	LUA_METHOD("setNormalSpriteFrame", lua_cocos2d_MenuItemImage_setNormalSpriteFrame);
	LUA_METHOD("setSelectedSpriteFrame", lua_cocos2d_MenuItemImage_setSelectedSpriteFrame);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItemToggle_addSubItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:addSubItem");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemToggle::*)(cocos2d::MenuItem*)>(&cocos2d::MenuItemToggle::addSubItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemToggle_getSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:getSelectedIndex");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::MenuItemToggle::*)()const>(&cocos2d::MenuItemToggle::getSelectedIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemToggle_getSelectedItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:getSelectedItem");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::MenuItem*(cocos2d::MenuItemToggle::*)()>(&cocos2d::MenuItemToggle::getSelectedItem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemToggle_initWithItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:initWithItem");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::MenuItemToggle::*)(cocos2d::MenuItem*)>(&cocos2d::MenuItemToggle::initWithItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemToggle_setSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:setSelectedIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemToggle::*)(unsigned int)>(&cocos2d::MenuItemToggle::setSelectedIndex));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemToggle(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemToggle, "MenuItemToggle", "cc.MenuItemToggle",
		cocos2d::MenuItem, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("addSubItem", lua_cocos2d_MenuItemToggle_addSubItem);
	LUA_METHOD("getSelectedIndex", lua_cocos2d_MenuItemToggle_getSelectedIndex);
	LUA_METHOD("getSelectedItem", lua_cocos2d_MenuItemToggle_getSelectedItem);
	LUA_METHOD("initWithItem", lua_cocos2d_MenuItemToggle_initWithItem);
	LUA_METHOD("setSelectedIndex", lua_cocos2d_MenuItemToggle_setSelectedIndex);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Menu_alignItemsHorizontally(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsHorizontally");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Menu::*)()>(&cocos2d::Menu::alignItemsHorizontally));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Menu_alignItemsHorizontallyWithPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsHorizontallyWithPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Menu::*)(float)>(&cocos2d::Menu::alignItemsHorizontallyWithPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Menu_alignItemsVertically(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsVertically");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Menu::*)()>(&cocos2d::Menu::alignItemsVertically));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Menu_alignItemsVerticallyWithPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsVerticallyWithPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Menu::*)(float)>(&cocos2d::Menu::alignItemsVerticallyWithPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Menu_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Menu::*)()const>(&cocos2d::Menu::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Menu_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Menu::*)(bool)>(&cocos2d::Menu::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenu(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Menu, "Menu", "cc.Menu",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("alignItemsHorizontally", lua_cocos2d_Menu_alignItemsHorizontally);
	LUA_METHOD("alignItemsHorizontallyWithPadding", lua_cocos2d_Menu_alignItemsHorizontallyWithPadding);
	LUA_METHOD("alignItemsVertically", lua_cocos2d_Menu_alignItemsVertically);
	LUA_METHOD("alignItemsVerticallyWithPadding", lua_cocos2d_Menu_alignItemsVerticallyWithPadding);
	LUA_METHOD("isEnabled", lua_cocos2d_Menu_isEnabled);
	LUA_METHOD("setEnabled", lua_cocos2d_Menu_setEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MotionStreak_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getStroke");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::getStroke));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_isFastMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:isFastMode");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::isFastMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::isStartingPositionInitialized));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:reset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MotionStreak::*)()>(&cocos2d::MotionStreak::reset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_setFastMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setFastMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(bool)>(&cocos2d::MotionStreak::setFastMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(bool)>(&cocos2d::MotionStreak::setStartingPositionInitialized));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setStroke");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(float)>(&cocos2d::MotionStreak::setStroke));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMotionStreak(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak, "MotionStreak", "cc.MotionStreak",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak_getStroke);
	LUA_METHOD("isFastMode", lua_cocos2d_MotionStreak_isFastMode);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak_reset);
	LUA_METHOD("setFastMode", lua_cocos2d_MotionStreak_setFastMode);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak_setStroke);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_NodeGrid_setGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setGrid");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::NodeGrid::*)(cocos2d::GridBase*)>(&cocos2d::NodeGrid::setGrid));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_NodeGrid_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::NodeGrid::*)(cocos2d::Node*)>(&cocos2d::NodeGrid::setTarget));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccNodeGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::NodeGrid, "NodeGrid", "cc.NodeGrid",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("setGrid", lua_cocos2d_NodeGrid_setGrid);
	LUA_METHOD("setTarget", lua_cocos2d_NodeGrid_setTarget);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleBatchNode_disableParticle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:disableParticle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleBatchNode::*)(int)>(&cocos2d::ParticleBatchNode::disableParticle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::ParticleBatchNode::*)(std::string_view, int)>(&cocos2d::ParticleBatchNode::initWithFile));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::ParticleBatchNode::*)(cocos2d::Texture2D*, int)>(&cocos2d::ParticleBatchNode::initWithTexture));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_insertChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:insertChild");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::ParticleSystem*, int)>(&cocos2d::ParticleBatchNode::insertChild));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleBatchNode::*)(int, bool)>(&cocos2d::ParticleBatchNode::removeChildAtIndex));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ParticleBatchNode*(*)(std::string_view, int)>(&cocos2d::ParticleBatchNode::create));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ParticleBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_ParticleBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ParticleBatchNode*(*)(cocos2d::Texture2D*, int)>(&cocos2d::ParticleBatchNode::createWithTexture));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::ParticleBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccParticleBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleBatchNode, "ParticleBatchNode", "cc.ParticleBatchNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("disableParticle", lua_cocos2d_ParticleBatchNode_disableParticle);
	LUA_METHOD("initWithFile", lua_cocos2d_ParticleBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cocos2d_ParticleBatchNode_initWithTexture);
	LUA_METHOD("insertChild", lua_cocos2d_ParticleBatchNode_insertChild);
	LUA_METHOD("removeChildAtIndex", lua_cocos2d_ParticleBatchNode_removeChildAtIndex);
	LUA_METHOD("create", lua_cocos2d_ParticleBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_ParticleBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccSpriteSheet(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::SpriteSheet, "SpriteSheet", "cc.SpriteSheet",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteFrameCache_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrame");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::SpriteFrameCache::*)(cocos2d::SpriteFrame*, std::string_view)>(&cocos2d::SpriteFrameCache::addSpriteFrame));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteFrameCache_deregisterSpriteSheetLoader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:deregisterSpriteSheetLoader");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrameCache::*)(uint32_t)>(&cocos2d::SpriteFrameCache::deregisterSpriteSheetLoader));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_eraseFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:eraseFrame");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::eraseFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_findFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:findFrame");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::SpriteFrame*(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::findFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrameCache::*)()>(&cocos2d::SpriteFrameCache::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrameCache_isSpriteFramesWithFileLoaded(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:isSpriteFramesWithFileLoaded");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::SpriteFrameCache::*)(std::string_view)const>(&cocos2d::SpriteFrameCache::isSpriteFramesWithFileLoaded));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:reloadTexture");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::reloadTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_removeSpriteFrameByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFrameByName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::removeSpriteFrameByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_removeSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFrames");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::SpriteFrameCache::*)()>(&cocos2d::SpriteFrameCache::removeSpriteFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromFile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::removeSpriteFramesFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFileContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromFileContent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::removeSpriteFramesFromFileContent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeSpriteFramesFromTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrameCache::*)(cocos2d::Texture2D*)>(&cocos2d::SpriteFrameCache::removeSpriteFramesFromTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_removeUnusedSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:removeUnusedSpriteFrames");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::SpriteFrameCache::*)()>(&cocos2d::SpriteFrameCache::removeUnusedSpriteFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrameCache_destroyInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:destroyInstance");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocos2d::SpriteFrameCache::destroyInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrameCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrameCache*(*)()>(&cocos2d::SpriteFrameCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccSpriteFrameCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteFrameCache, "SpriteFrameCache", "cc.SpriteFrameCache",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_SpriteFrameCache_addSpriteFrame);
	LUA_METHOD("deregisterSpriteSheetLoader", lua_cocos2d_SpriteFrameCache_deregisterSpriteSheetLoader);
	LUA_METHOD("eraseFrame", lua_cocos2d_SpriteFrameCache_eraseFrame);
	LUA_METHOD("findFrame", lua_cocos2d_SpriteFrameCache_findFrame);
	LUA_METHOD("init", lua_cocos2d_SpriteFrameCache_init);
	LUA_METHOD("isSpriteFramesWithFileLoaded", lua_cocos2d_SpriteFrameCache_isSpriteFramesWithFileLoaded);
	LUA_METHOD("reloadTexture", lua_cocos2d_SpriteFrameCache_reloadTexture);
	LUA_METHOD("removeSpriteFrameByName", lua_cocos2d_SpriteFrameCache_removeSpriteFrameByName);
	LUA_METHOD("removeSpriteFrames", lua_cocos2d_SpriteFrameCache_removeSpriteFrames);
	LUA_METHOD("removeSpriteFramesFromFile", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFile);
	LUA_METHOD("removeSpriteFramesFromFileContent", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFileContent);
	LUA_METHOD("removeSpriteFramesFromTexture", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromTexture);
	LUA_METHOD("removeUnusedSpriteFrames", lua_cocos2d_SpriteFrameCache_removeUnusedSpriteFrames);
	LUA_METHOD("destroyInstance", lua_cocos2d_SpriteFrameCache_destroyInstance);
	LUA_METHOD("getInstance", lua_cocos2d_SpriteFrameCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleData_copyParticle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleData", "cc.ParticleData:copyParticle");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleData::*)(int, int)>(&cocos2d::ParticleData::copyParticle));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleData_getMaxCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleData", "cc.ParticleData:getMaxCount");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::ParticleData::*)()>(&cocos2d::ParticleData::getMaxCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleData", "cc.ParticleData:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ParticleData::*)(int)>(&cocos2d::ParticleData::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleData_release(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleData", "cc.ParticleData:release");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleData::*)()>(&cocos2d::ParticleData::release));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccParticleData(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::ParticleData, "ParticleData", "cc.ParticleData",
		nullptr, nullptr);
	LUA_METHOD("copyParticle", lua_cocos2d_ParticleData_copyParticle);
	LUA_METHOD("getMaxCount", lua_cocos2d_ParticleData_getMaxCount);
	LUA_METHOD("init", lua_cocos2d_ParticleData_init);
	LUA_METHOD("release", lua_cocos2d_ParticleData_release);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleEmissionMaskCache_removeAllMasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:removeAllMasks");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ParticleEmissionMaskCache::*)()>(&cocos2d::ParticleEmissionMaskCache::removeAllMasks));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleEmissionMaskCache_removeMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:removeMask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleEmissionMaskCache::*)(std::string_view)>(&cocos2d::ParticleEmissionMaskCache::removeMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleEmissionMaskCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParticleEmissionMaskCache*(*)()>(&cocos2d::ParticleEmissionMaskCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParticleEmissionMaskCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleEmissionMaskCache, "ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("removeAllMasks", lua_cocos2d_ParticleEmissionMaskCache_removeAllMasks);
	LUA_METHOD("removeMask", lua_cocos2d_ParticleEmissionMaskCache_removeMask);
	LUA_METHOD("getInstance", lua_cocos2d_ParticleEmissionMaskCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleSystem_addParticles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:addParticles");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ParticleSystem::*)(int, int, int)>(&cocos2d::ParticleSystem::addParticles));
	LUA_TRY_INVOKE(2, [](cocos2d::ParticleSystem* obj,int arg0,int arg1){{return obj->addParticles(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE(1, [](cocos2d::ParticleSystem* obj,int arg0){{return obj->addParticles(std::move(arg0));}});
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleSystem::*)(float, float)>(&cocos2d::ParticleSystem::resimulate));
	LUA_TRY_INVOKE(1, [](cocos2d::ParticleSystem* obj,float arg0){{return obj->resimulate(std::move(arg0));}});
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
int lua_cocos2d_ParticleSystem_setAnimationIndicesAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:setAnimationIndicesAtlas");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleSystem::*)(unsigned int, cocos2d::ParticleSystem::TexAnimDir)>(&cocos2d::ParticleSystem::setAnimationIndicesAtlas));
	LUA_TRY_INVOKE(1, [](cocos2d::ParticleSystem* obj,unsigned int arg0){{return obj->setAnimationIndicesAtlas(std::move(arg0));}});
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ParticleSystem::*)(float, float)>(&cocos2d::ParticleSystem::simulate));
	LUA_TRY_INVOKE(1, [](cocos2d::ParticleSystem* obj,float arg0){{return obj->simulate(std::move(arg0));}});
	LUA_TRY_INVOKE(0, [](cocos2d::ParticleSystem* obj){{return obj->simulate();}});
	LUA_INVOKE_FOOTER("0,1,2");
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
int lua_cocos2d_ParticleSystem_createWithTotalParticles(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleSystem", "cc.ParticleSystem:createWithTotalParticles");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ParticleSystem*(*)(int)>(&cocos2d::ParticleSystem::createWithTotalParticles));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccParticleSystem(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleSystem, "ParticleSystem", "cc.ParticleSystem",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addParticles", lua_cocos2d_ParticleSystem_addParticles);
	LUA_METHOD("getAngle", lua_cocos2d_ParticleSystem_getAngle);
	LUA_METHOD("getAngleVar", lua_cocos2d_ParticleSystem_getAngleVar);
	LUA_METHOD("getAtlasIndex", lua_cocos2d_ParticleSystem_getAtlasIndex);
	LUA_METHOD("getBatchNode", lua_cocos2d_ParticleSystem_getBatchNode);
	LUA_METHOD("getDuration", lua_cocos2d_ParticleSystem_getDuration);
	LUA_METHOD("getEmissionRate", lua_cocos2d_ParticleSystem_getEmissionRate);
	LUA_METHOD("getEmitterMode", lua_cocos2d_ParticleSystem_getEmitterMode);
	LUA_METHOD("getEndRadius", lua_cocos2d_ParticleSystem_getEndRadius);
	LUA_METHOD("getEndRadiusVar", lua_cocos2d_ParticleSystem_getEndRadiusVar);
	LUA_METHOD("getEndSize", lua_cocos2d_ParticleSystem_getEndSize);
	LUA_METHOD("getEndSizeVar", lua_cocos2d_ParticleSystem_getEndSizeVar);
	LUA_METHOD("getEndSpin", lua_cocos2d_ParticleSystem_getEndSpin);
	LUA_METHOD("getEndSpinVar", lua_cocos2d_ParticleSystem_getEndSpinVar);
	LUA_METHOD("getFixedFPS", lua_cocos2d_ParticleSystem_getFixedFPS);
	LUA_METHOD("getHue", lua_cocos2d_ParticleSystem_getHue);
	LUA_METHOD("getHueVar", lua_cocos2d_ParticleSystem_getHueVar);
	LUA_METHOD("getLife", lua_cocos2d_ParticleSystem_getLife);
	LUA_METHOD("getLifeVar", lua_cocos2d_ParticleSystem_getLifeVar);
	LUA_METHOD("getParticleCount", lua_cocos2d_ParticleSystem_getParticleCount);
	LUA_METHOD("getPositionType", lua_cocos2d_ParticleSystem_getPositionType);
	LUA_METHOD("getRadialAccel", lua_cocos2d_ParticleSystem_getRadialAccel);
	LUA_METHOD("getRadialAccelVar", lua_cocos2d_ParticleSystem_getRadialAccelVar);
	LUA_METHOD("getResourceFile", lua_cocos2d_ParticleSystem_getResourceFile);
	LUA_METHOD("getRotatePerSecond", lua_cocos2d_ParticleSystem_getRotatePerSecond);
	LUA_METHOD("getRotatePerSecondVar", lua_cocos2d_ParticleSystem_getRotatePerSecondVar);
	LUA_METHOD("getRotationIsDir", lua_cocos2d_ParticleSystem_getRotationIsDir);
	LUA_METHOD("getSpawnAngle", lua_cocos2d_ParticleSystem_getSpawnAngle);
	LUA_METHOD("getSpawnAngleVar", lua_cocos2d_ParticleSystem_getSpawnAngleVar);
	LUA_METHOD("getSpawnFadeIn", lua_cocos2d_ParticleSystem_getSpawnFadeIn);
	LUA_METHOD("getSpawnFadeInVar", lua_cocos2d_ParticleSystem_getSpawnFadeInVar);
	LUA_METHOD("getSpawnScaleIn", lua_cocos2d_ParticleSystem_getSpawnScaleIn);
	LUA_METHOD("getSpawnScaleInVar", lua_cocos2d_ParticleSystem_getSpawnScaleInVar);
	LUA_METHOD("getSpeed", lua_cocos2d_ParticleSystem_getSpeed);
	LUA_METHOD("getSpeedVar", lua_cocos2d_ParticleSystem_getSpeedVar);
	LUA_METHOD("getStartRadius", lua_cocos2d_ParticleSystem_getStartRadius);
	LUA_METHOD("getStartRadiusVar", lua_cocos2d_ParticleSystem_getStartRadiusVar);
	LUA_METHOD("getStartSize", lua_cocos2d_ParticleSystem_getStartSize);
	LUA_METHOD("getStartSizeVar", lua_cocos2d_ParticleSystem_getStartSizeVar);
	LUA_METHOD("getStartSpin", lua_cocos2d_ParticleSystem_getStartSpin);
	LUA_METHOD("getStartSpinVar", lua_cocos2d_ParticleSystem_getStartSpinVar);
	LUA_METHOD("getTangentialAccel", lua_cocos2d_ParticleSystem_getTangentialAccel);
	LUA_METHOD("getTangentialAccelVar", lua_cocos2d_ParticleSystem_getTangentialAccelVar);
	LUA_METHOD("getTimeScale", lua_cocos2d_ParticleSystem_getTimeScale);
	LUA_METHOD("getTotalAnimationIndices", lua_cocos2d_ParticleSystem_getTotalAnimationIndices);
	LUA_METHOD("getTotalParticles", lua_cocos2d_ParticleSystem_getTotalParticles);
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
	LUA_METHOD("setAnimationIndicesAtlas", lua_cocos2d_ParticleSystem_setAnimationIndicesAtlas);
	LUA_METHOD("setAnimationReverse", lua_cocos2d_ParticleSystem_setAnimationReverse);
	LUA_METHOD("setAnimationSpeedTimescaleIndependent", lua_cocos2d_ParticleSystem_setAnimationSpeedTimescaleIndependent);
	LUA_METHOD("setAtlasIndex", lua_cocos2d_ParticleSystem_setAtlasIndex);
	LUA_METHOD("setAutoRemoveOnFinish", lua_cocos2d_ParticleSystem_setAutoRemoveOnFinish);
	LUA_METHOD("setBatchNode", lua_cocos2d_ParticleSystem_setBatchNode);
	LUA_METHOD("setBlendAdditive", lua_cocos2d_ParticleSystem_setBlendAdditive);
	LUA_METHOD("setDuration", lua_cocos2d_ParticleSystem_setDuration);
	LUA_METHOD("setEmissionRate", lua_cocos2d_ParticleSystem_setEmissionRate);
	LUA_METHOD("setEmissionShapes", lua_cocos2d_ParticleSystem_setEmissionShapes);
	LUA_METHOD("setEmitterAnimation", lua_cocos2d_ParticleSystem_setEmitterAnimation);
	LUA_METHOD("setEmitterMode", lua_cocos2d_ParticleSystem_setEmitterMode);
	LUA_METHOD("setEndRadius", lua_cocos2d_ParticleSystem_setEndRadius);
	LUA_METHOD("setEndRadiusVar", lua_cocos2d_ParticleSystem_setEndRadiusVar);
	LUA_METHOD("setEndSize", lua_cocos2d_ParticleSystem_setEndSize);
	LUA_METHOD("setEndSizeVar", lua_cocos2d_ParticleSystem_setEndSizeVar);
	LUA_METHOD("setEndSpin", lua_cocos2d_ParticleSystem_setEndSpin);
	LUA_METHOD("setEndSpinVar", lua_cocos2d_ParticleSystem_setEndSpinVar);
	LUA_METHOD("setFixedFPS", lua_cocos2d_ParticleSystem_setFixedFPS);
	LUA_METHOD("setHue", lua_cocos2d_ParticleSystem_setHue);
	LUA_METHOD("setHueVar", lua_cocos2d_ParticleSystem_setHueVar);
	LUA_METHOD("setLife", lua_cocos2d_ParticleSystem_setLife);
	LUA_METHOD("setLifeAnimation", lua_cocos2d_ParticleSystem_setLifeAnimation);
	LUA_METHOD("setLifeVar", lua_cocos2d_ParticleSystem_setLifeVar);
	LUA_METHOD("setLoopAnimation", lua_cocos2d_ParticleSystem_setLoopAnimation);
	LUA_METHOD("setMultiAnimationRandom", lua_cocos2d_ParticleSystem_setMultiAnimationRandom);
	LUA_METHOD("setPositionType", lua_cocos2d_ParticleSystem_setPositionType);
	LUA_METHOD("setRadialAccel", lua_cocos2d_ParticleSystem_setRadialAccel);
	LUA_METHOD("setRadialAccelVar", lua_cocos2d_ParticleSystem_setRadialAccelVar);
	LUA_METHOD("setRotatePerSecond", lua_cocos2d_ParticleSystem_setRotatePerSecond);
	LUA_METHOD("setRotatePerSecondVar", lua_cocos2d_ParticleSystem_setRotatePerSecondVar);
	LUA_METHOD("setRotationIsDir", lua_cocos2d_ParticleSystem_setRotationIsDir);
	LUA_METHOD("setSourcePositionCompatible", lua_cocos2d_ParticleSystem_setSourcePositionCompatible);
	LUA_METHOD("setSpawnAngle", lua_cocos2d_ParticleSystem_setSpawnAngle);
	LUA_METHOD("setSpawnAngleVar", lua_cocos2d_ParticleSystem_setSpawnAngleVar);
	LUA_METHOD("setSpawnFadeIn", lua_cocos2d_ParticleSystem_setSpawnFadeIn);
	LUA_METHOD("setSpawnFadeInVar", lua_cocos2d_ParticleSystem_setSpawnFadeInVar);
	LUA_METHOD("setSpawnScaleIn", lua_cocos2d_ParticleSystem_setSpawnScaleIn);
	LUA_METHOD("setSpawnScaleInVar", lua_cocos2d_ParticleSystem_setSpawnScaleInVar);
	LUA_METHOD("setSpeed", lua_cocos2d_ParticleSystem_setSpeed);
	LUA_METHOD("setSpeedVar", lua_cocos2d_ParticleSystem_setSpeedVar);
	LUA_METHOD("setStartRadius", lua_cocos2d_ParticleSystem_setStartRadius);
	LUA_METHOD("setStartRadiusVar", lua_cocos2d_ParticleSystem_setStartRadiusVar);
	LUA_METHOD("setStartSize", lua_cocos2d_ParticleSystem_setStartSize);
	LUA_METHOD("setStartSizeVar", lua_cocos2d_ParticleSystem_setStartSizeVar);
	LUA_METHOD("setStartSpin", lua_cocos2d_ParticleSystem_setStartSpin);
	LUA_METHOD("setStartSpinVar", lua_cocos2d_ParticleSystem_setStartSpinVar);
	LUA_METHOD("setTangentialAccel", lua_cocos2d_ParticleSystem_setTangentialAccel);
	LUA_METHOD("setTangentialAccelVar", lua_cocos2d_ParticleSystem_setTangentialAccelVar);
	LUA_METHOD("setTimeScale", lua_cocos2d_ParticleSystem_setTimeScale);
	LUA_METHOD("setTotalParticles", lua_cocos2d_ParticleSystem_setTotalParticles);
	LUA_METHOD("simulate", lua_cocos2d_ParticleSystem_simulate);
	LUA_METHOD("stopSystem", lua_cocos2d_ParticleSystem_stopSystem);
	LUA_METHOD("updateParticleQuads", lua_cocos2d_ParticleSystem_updateParticleQuads);
	LUA_METHOD("updateWithNoTime", lua_cocos2d_ParticleSystem_updateWithNoTime);
	LUA_METHOD("useHSV", lua_cocos2d_ParticleSystem_useHSV);
	LUA_METHOD("create", lua_cocos2d_ParticleSystem_create);
	LUA_METHOD("createWithTotalParticles", lua_cocos2d_ParticleSystem_createWithTotalParticles);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
