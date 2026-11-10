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

int lua_cocos2d_MenuItemFont_getFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontNameObj");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::MenuItemFont::*)()const>(&cocos2d::MenuItemFont::getFontNameObj));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_getFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSizeObj");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::MenuItemFont::*)()const>(&cocos2d::MenuItemFont::getFontSizeObj));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:initWithString");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::MenuItemFont::*)(std::string_view, const cocos2d::ccMenuCallback&)>(&cocos2d::MenuItemFont::initWithString)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MenuItemFont_setFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontNameObj");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemFont::*)(std::string_view)>(&cocos2d::MenuItemFont::setFontNameObj));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_setFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSizeObj");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemFont::*)(int)>(&cocos2d::MenuItemFont::setFontSizeObj));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::MenuItemFont*(*)(std::string_view)>(&cocos2d::MenuItemFont::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_getFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(*)()>(&cocos2d::MenuItemFont::getFontName));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_getFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(*)()>(&cocos2d::MenuItemFont::getFontSize));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_setFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontName");
	LUA_TRY_INVOKE(1, static_cast<void(*)(std::string_view)>(&cocos2d::MenuItemFont::setFontName));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_setFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(*)(int)>(&cocos2d::MenuItemFont::setFontSize));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemFont(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemFont, "MenuItemFont", "cc.MenuItemFont",
		cocos2d::MenuItemFont, "cc.MenuItemLabel",
		nullptr, nullptr);
	LUA_METHOD("getFontNameObj", lua_cocos2d_MenuItemFont_getFontNameObj);
	LUA_METHOD("getFontSizeObj", lua_cocos2d_MenuItemFont_getFontSizeObj);
	LUA_METHOD("initWithString", lua_cocos2d_MenuItemFont_initWithString);
	LUA_METHOD("setFontNameObj", lua_cocos2d_MenuItemFont_setFontNameObj);
	LUA_METHOD("setFontSizeObj", lua_cocos2d_MenuItemFont_setFontSizeObj);
	LUA_METHOD("create", lua_cocos2d_MenuItemFont_create_1);
	LUA_METHOD("getFontName", lua_cocos2d_MenuItemFont_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_MenuItemFont_getFontSize);
	LUA_METHOD("setFontName", lua_cocos2d_MenuItemFont_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_MenuItemFont_setFontSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int lua_cocos2d_MenuItemSprite_initWithNormalSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:initWithNormalSprite");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::MenuItemSprite::*)(cocos2d::Node*, cocos2d::Node*, cocos2d::Node*, const cocos2d::ccMenuCallback&)>(&cocos2d::MenuItemSprite::initWithNormalSprite)));
	LUA_INVOKE_FOOTER("4");
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
int lua_cocos2d_MenuItemSprite_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::MenuItemSprite*(*)(cocos2d::Node*, cocos2d::Node*, cocos2d::Node*)>(&cocos2d::MenuItemSprite::create)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Node* arg0,cocos2d::Node* arg1){{return cocos2d::MenuItemSprite::create(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccMenuItemSprite(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemSprite, "MenuItemSprite", "cc.MenuItemSprite",
		cocos2d::MenuItemSprite, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("getDisabledImage", lua_cocos2d_MenuItemSprite_getDisabledImage);
	LUA_METHOD("getNormalImage", lua_cocos2d_MenuItemSprite_getNormalImage);
	LUA_METHOD("getSelectedImage", lua_cocos2d_MenuItemSprite_getSelectedImage);
	LUA_METHOD("initWithNormalSprite", lua_cocos2d_MenuItemSprite_initWithNormalSprite);
	LUA_METHOD("setDisabledImage", lua_cocos2d_MenuItemSprite_setDisabledImage);
	LUA_METHOD("setNormalImage", lua_cocos2d_MenuItemSprite_setNormalImage);
	LUA_METHOD("setSelectedImage", lua_cocos2d_MenuItemSprite_setSelectedImage);
	LUA_METHOD("create", lua_cocos2d_MenuItemSprite_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItemImage_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MenuItemImage::*)()>(&cocos2d::MenuItemImage::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemImage_initWithNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:initWithNormalImage");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::MenuItemImage::*)(std::string_view, std::string_view, std::string_view, const cocos2d::ccMenuCallback&)>(&cocos2d::MenuItemImage::initWithNormalImage)));
	LUA_INVOKE_FOOTER("4");
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
int lua_cocos2d_MenuItemImage_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::MenuItemImage*(*)()>(&cocos2d::MenuItemImage::create));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::MenuItemImage*(*)(std::string_view, std::string_view)>(&cocos2d::MenuItemImage::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::MenuItemImage*(*)(std::string_view, std::string_view, std::string_view)>(&cocos2d::MenuItemImage::create)));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int luaReg_Core_ccMenuItemImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemImage, "MenuItemImage", "cc.MenuItemImage",
		cocos2d::MenuItemImage, "cc.MenuItemSprite",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_MenuItemImage_init_1);
	LUA_METHOD("initWithNormalImage", lua_cocos2d_MenuItemImage_initWithNormalImage);
	LUA_METHOD("setDisabledSpriteFrame", lua_cocos2d_MenuItemImage_setDisabledSpriteFrame);
	LUA_METHOD("setNormalSpriteFrame", lua_cocos2d_MenuItemImage_setNormalSpriteFrame);
	LUA_METHOD("setSelectedSpriteFrame", lua_cocos2d_MenuItemImage_setSelectedSpriteFrame);
	LUA_METHOD("create", lua_cocos2d_MenuItemImage_create_1);
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
int lua_cocos2d_MenuItemToggle_setSubItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:setSubItems");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemToggle::*)(const cocos2d::Vector<cocos2d::MenuItem *>&)>(&cocos2d::MenuItemToggle::setSubItems));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemToggle(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemToggle, "MenuItemToggle", "cc.MenuItemToggle",
		cocos2d::MenuItemToggle, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("addSubItem", lua_cocos2d_MenuItemToggle_addSubItem);
	LUA_METHOD("getSelectedIndex", lua_cocos2d_MenuItemToggle_getSelectedIndex);
	LUA_METHOD("getSelectedItem", lua_cocos2d_MenuItemToggle_getSelectedItem);
	LUA_METHOD("initWithItem", lua_cocos2d_MenuItemToggle_initWithItem);
	LUA_METHOD("setSelectedIndex", lua_cocos2d_MenuItemToggle_setSelectedIndex);
	LUA_METHOD("setSubItems", lua_cocos2d_MenuItemToggle_setSubItems);
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
int lua_cocos2d_Menu_initWithArray(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:initWithArray");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Menu::*)(const cocos2d::Vector<cocos2d::MenuItem *>&)>(&cocos2d::Menu::initWithArray));
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
		cocos2d::Menu, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("alignItemsHorizontally", lua_cocos2d_Menu_alignItemsHorizontally);
	LUA_METHOD("alignItemsHorizontallyWithPadding", lua_cocos2d_Menu_alignItemsHorizontallyWithPadding);
	LUA_METHOD("alignItemsVertically", lua_cocos2d_Menu_alignItemsVertically);
	LUA_METHOD("alignItemsVerticallyWithPadding", lua_cocos2d_Menu_alignItemsVerticallyWithPadding);
	LUA_METHOD("initWithArray", lua_cocos2d_Menu_initWithArray);
	LUA_METHOD("isEnabled", lua_cocos2d_Menu_isEnabled);
	LUA_METHOD("setEnabled", lua_cocos2d_Menu_setEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MotionStreak_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getStroke");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::getStroke));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak::*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak::*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak::initWithFade)));
	LUA_INVOKE_FOOTER("5");
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
int lua_cocos2d_MotionStreak_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(const cocos2d::BlendFunc&)>(&cocos2d::MotionStreak::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_MotionStreak_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(cocos2d::Texture2D*)>(&cocos2d::MotionStreak::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:tintWithColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak::*)(const cocos2d::Color3B&)>(&cocos2d::MotionStreak::tintWithColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak*(*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak*(*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak, "MotionStreak", "cc.MotionStreak",
		cocos2d::MotionStreak, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_MotionStreak_getBlendFunc);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak_getStroke);
	LUA_METHOD("getTexture", lua_cocos2d_MotionStreak_getTexture);
	LUA_METHOD("initWithFade", lua_cocos2d_MotionStreak_initWithFade);
	LUA_METHOD("isFastMode", lua_cocos2d_MotionStreak_isFastMode);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak_reset);
	LUA_METHOD("setBlendFunc", lua_cocos2d_MotionStreak_setBlendFunc);
	LUA_METHOD("setFastMode", lua_cocos2d_MotionStreak_setFastMode);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak_setStroke);
	LUA_METHOD("setTexture", lua_cocos2d_MotionStreak_setTexture);
	LUA_METHOD("tintWithColor", lua_cocos2d_MotionStreak_tintWithColor);
	LUA_METHOD("create", lua_cocos2d_MotionStreak_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_NodeGrid_getGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:getGrid");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::GridBase*(cocos2d::NodeGrid::*)()const>(&cocos2d::NodeGrid::getGrid));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::GridBase*(cocos2d::NodeGrid::*)()>(&cocos2d::NodeGrid::getGrid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_NodeGrid_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:getGridRect");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::NodeGrid::*)()const>(&cocos2d::NodeGrid::getGridRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_NodeGrid_setGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setGrid");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::NodeGrid::*)(cocos2d::GridBase*)>(&cocos2d::NodeGrid::setGrid));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_NodeGrid_setGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setGridRect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::NodeGrid::*)(const cocos2d::Rect&)>(&cocos2d::NodeGrid::setGridRect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_NodeGrid_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::NodeGrid::*)(cocos2d::Node*)>(&cocos2d::NodeGrid::setTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_NodeGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::NodeGrid*(*)(const cocos2d::Rect&)>(&cocos2d::NodeGrid::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::NodeGrid*(*)()>(&cocos2d::NodeGrid::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccNodeGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::NodeGrid, "NodeGrid", "cc.NodeGrid",
		cocos2d::NodeGrid, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getGrid", lua_cocos2d_NodeGrid_getGrid);
	LUA_METHOD("getGridRect", lua_cocos2d_NodeGrid_getGridRect);
	LUA_METHOD("setGrid", lua_cocos2d_NodeGrid_setGrid);
	LUA_METHOD("setGridRect", lua_cocos2d_NodeGrid_setGridRect);
	LUA_METHOD("setTarget", lua_cocos2d_NodeGrid_setTarget);
	LUA_METHOD("create", lua_cocos2d_NodeGrid_create);
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
int lua_cocos2d_ParticleBatchNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::ParticleBatchNode::*)()const>(&cocos2d::ParticleBatchNode::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleBatchNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::ParticleBatchNode::*)()const>(&cocos2d::ParticleBatchNode::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleBatchNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureAtlas*(cocos2d::ParticleBatchNode::*)()const>(&cocos2d::ParticleBatchNode::getTextureAtlas));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ParticleBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ParticleBatchNode::*)(std::string_view, int)>(&cocos2d::ParticleBatchNode::initWithFile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ParticleBatchNode::*)(cocos2d::Texture2D*, int)>(&cocos2d::ParticleBatchNode::initWithTexture)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_insertChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:insertChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::ParticleSystem*, int)>(&cocos2d::ParticleBatchNode::insertChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleBatchNode::*)(bool)>(&cocos2d::ParticleBatchNode::removeAllChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ParticleBatchNode::*)(int, bool)>(&cocos2d::ParticleBatchNode::removeChildAtIndex)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ParticleBatchNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleBatchNode::*)(const cocos2d::BlendFunc&)>(&cocos2d::ParticleBatchNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleBatchNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::Texture2D*)>(&cocos2d::ParticleBatchNode::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleBatchNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::ParticleBatchNode::setTextureAtlas));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParticleBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ParticleBatchNode*(*)(std::string_view, int)>(&cocos2d::ParticleBatchNode::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ParticleBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_ParticleBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParticleBatchNode", "cc.ParticleBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ParticleBatchNode*(*)(cocos2d::Texture2D*, int)>(&cocos2d::ParticleBatchNode::createWithTexture)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::ParticleBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccParticleBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParticleBatchNode, "ParticleBatchNode", "cc.ParticleBatchNode",
		cocos2d::ParticleBatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("disableParticle", lua_cocos2d_ParticleBatchNode_disableParticle);
	LUA_METHOD("getBlendFunc", lua_cocos2d_ParticleBatchNode_getBlendFunc);
	LUA_METHOD("getTexture", lua_cocos2d_ParticleBatchNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cocos2d_ParticleBatchNode_getTextureAtlas);
	LUA_METHOD("initWithFile", lua_cocos2d_ParticleBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cocos2d_ParticleBatchNode_initWithTexture);
	LUA_METHOD("insertChild", lua_cocos2d_ParticleBatchNode_insertChild);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cocos2d_ParticleBatchNode_removeAllChildrenWithCleanup);
	LUA_METHOD("removeChildAtIndex", lua_cocos2d_ParticleBatchNode_removeChildAtIndex);
	LUA_METHOD("setBlendFunc", lua_cocos2d_ParticleBatchNode_setBlendFunc);
	LUA_METHOD("setTexture", lua_cocos2d_ParticleBatchNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cocos2d_ParticleBatchNode_setTextureAtlas);
	LUA_METHOD("create", lua_cocos2d_ParticleBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_ParticleBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteFrameCache_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrame");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::SpriteFrameCache::*)(cocos2d::SpriteFrame*, std::string_view)>(&cocos2d::SpriteFrameCache::addSpriteFrame)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteFrameCache_addSpriteFrameCapInset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrameCapInset");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::SpriteFrameCache::*)(cocos2d::SpriteFrame*, const cocos2d::Rect&, cocos2d::Texture2D*)>(&cocos2d::SpriteFrameCache::addSpriteFrameCapInset)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SpriteFrameCache_addSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:addSpriteFrames");
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view, cocos2d::Texture2D*, uint32_t)>(&cocos2d::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view, std::string_view, uint32_t)>(&cocos2d::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cocos2d::SpriteFrameCache* obj,std::string_view arg0,cocos2d::Texture2D* arg1){{return obj->addSpriteFramesWithFile(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cocos2d::SpriteFrameCache* obj,std::string_view arg0,std::string_view arg1){{return obj->addSpriteFramesWithFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocos2d::SpriteFrameCache::*)(std::string_view, uint32_t)>(&cocos2d::SpriteFrameCache::addSpriteFramesWithFile)));
	LUA_TRY_INVOKE(1, ([](cocos2d::SpriteFrameCache* obj,std::string_view arg0){{return obj->addSpriteFramesWithFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
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
int lua_cocos2d_SpriteFrameCache_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getSpriteFrame");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::SpriteFrame*(cocos2d::SpriteFrameCache::*)(std::string_view)>(&cocos2d::SpriteFrameCache::getSpriteFrameByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrameCache_getSpriteSheetLoader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrameCache", "cc.SpriteFrameCache:getSpriteSheetLoader");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ISpriteSheetLoader*(cocos2d::SpriteFrameCache::*)(uint32_t)>(&cocos2d::SpriteFrameCache::getSpriteSheetLoader));
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
		cocos2d::SpriteFrameCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_SpriteFrameCache_addSpriteFrame);
	LUA_METHOD("addSpriteFrameCapInset", lua_cocos2d_SpriteFrameCache_addSpriteFrameCapInset);
	LUA_METHOD("addSpriteFrames", lua_cocos2d_SpriteFrameCache_addSpriteFrames);
	LUA_METHOD("deregisterSpriteSheetLoader", lua_cocos2d_SpriteFrameCache_deregisterSpriteSheetLoader);
	LUA_METHOD("eraseFrame", lua_cocos2d_SpriteFrameCache_eraseFrame);
	LUA_METHOD("findFrame", lua_cocos2d_SpriteFrameCache_findFrame);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_SpriteFrameCache_getSpriteFrame);
	LUA_METHOD("getSpriteSheetLoader", lua_cocos2d_SpriteFrameCache_getSpriteSheetLoader);
	LUA_METHOD("init", lua_cocos2d_SpriteFrameCache_init);
	LUA_METHOD("isSpriteFramesWithFileLoaded", lua_cocos2d_SpriteFrameCache_isSpriteFramesWithFileLoaded);
	LUA_METHOD("reloadTexture", lua_cocos2d_SpriteFrameCache_reloadTexture);
	LUA_METHOD("removeSpriteFrameByName", lua_cocos2d_SpriteFrameCache_removeSpriteFrameByName);
	LUA_METHOD("removeSpriteFrames", lua_cocos2d_SpriteFrameCache_removeSpriteFrames);
	LUA_METHOD("removeSpriteFramesFromFile", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFile);
	LUA_METHOD("removeSpriteFramesFromFileContent", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromFileContent);
	LUA_METHOD("removeSpriteFramesFromTexture", lua_cocos2d_SpriteFrameCache_removeSpriteFramesFromTexture);
	LUA_METHOD("removeUnusedSpriteFrames", lua_cocos2d_SpriteFrameCache_removeUnusedSpriteFrames);
	LUA_METHOD("getInstance", lua_cocos2d_SpriteFrameCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParticleEmissionMaskCache_bakeEmissionMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:bakeEmissionMask");
	LUA_TRY_INVOKE_OVERLOAD(5, (static_cast<void(cocos2d::ParticleEmissionMaskCache::*)(std::string_view, cocos2d::Image*, float, bool, int)>(&cocos2d::ParticleEmissionMaskCache::bakeEmissionMask)));
	LUA_TRY_INVOKE_OVERLOAD(5, (static_cast<void(cocos2d::ParticleEmissionMaskCache::*)(std::string_view, std::string_view, float, bool, int)>(&cocos2d::ParticleEmissionMaskCache::bakeEmissionMask)));
	LUA_TRY_INVOKE_OVERLOAD(4, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,cocos2d::Image* arg1,float arg2,bool arg3){{return obj->bakeEmissionMask(std::move(arg0),arg1,std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_OVERLOAD(4, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1,float arg2,bool arg3){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_OVERLOAD(3, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,cocos2d::Image* arg1,float arg2){{return obj->bakeEmissionMask(std::move(arg0),arg1,std::move(arg2));}}));
	LUA_TRY_INVOKE_OVERLOAD(3, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1,float arg2){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,cocos2d::Image* arg1){{return obj->bakeEmissionMask(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_OVERLOAD(2, ([](cocos2d::ParticleEmissionMaskCache* obj,std::string_view arg0,std::string_view arg1){{return obj->bakeEmissionMask(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4,5");
}
int lua_cocos2d_ParticleEmissionMaskCache_getEmissionMask_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParticleEmissionMaskCache", "cc.ParticleEmissionMaskCache:getEmissionMask");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<const cocos2d::ParticleEmissionMaskDescriptor&(cocos2d::ParticleEmissionMaskCache::*)(uint32_t)>(&cocos2d::ParticleEmissionMaskCache::getEmissionMask));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<const cocos2d::ParticleEmissionMaskDescriptor&(cocos2d::ParticleEmissionMaskCache::*)(std::string_view)>(&cocos2d::ParticleEmissionMaskCache::getEmissionMask));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ParticleEmissionMaskCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("bakeEmissionMask", lua_cocos2d_ParticleEmissionMaskCache_bakeEmissionMask);
	LUA_METHOD("getEmissionMask", lua_cocos2d_ParticleEmissionMaskCache_getEmissionMask_1);
	LUA_METHOD("removeAllMasks", lua_cocos2d_ParticleEmissionMaskCache_removeAllMasks);
	LUA_METHOD("removeMask", lua_cocos2d_ParticleEmissionMaskCache_removeMask);
	LUA_METHOD("getInstance", lua_cocos2d_ParticleEmissionMaskCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
