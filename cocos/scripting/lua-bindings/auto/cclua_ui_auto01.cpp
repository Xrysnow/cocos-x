#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_Button_getRendererClicked(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererClicked");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite*(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getRendererClicked));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getRendererDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererDisabled");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite*(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getRendererDisabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getRendererNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererNormal");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite*(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getRendererNormal));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getTitleFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getTitleFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleLabel");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label*(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getTitleLabel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label*(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getTitleRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleText");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getTitleText));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getZoomScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::getZoomScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Button::*)()const>(&cocos2d::ui::Button::isScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_loadTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextureDisabled");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTextureDisabled));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTextureDisabled(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextureNormal");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTextureNormal));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTextureNormal(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTexturePressed");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTexturePressed));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTexturePressed(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextures");
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::ui::Button::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTextures));
	LUA_TRY_INVOKE(3, [](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE(2, [](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1){{return obj->loadTextures(std::move(arg0),std::move(arg1));}});
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ui_Button_resetDisabledRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetDisabledRender");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Button::*)()>(&cocos2d::ui::Button::resetDisabledRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_resetNormalRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetNormalRender");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Button::*)()>(&cocos2d::ui::Button::resetNormalRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_resetPressedRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetPressedRender");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Button::*)()>(&cocos2d::ui::Button::resetPressedRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_setPressedActionEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setPressedActionEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(bool)>(&cocos2d::ui::Button::setPressedActionEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(bool)>(&cocos2d::ui::Button::setScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleAlignment");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Button::*)(cocos2d::TextHAlignment, cocos2d::TextVAlignment)>(&cocos2d::ui::Button::setTitleAlignment));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::Button::setTitleAlignment));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_setTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(std::string_view)>(&cocos2d::ui::Button::setTitleFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(float)>(&cocos2d::ui::Button::setTitleFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleLabel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(cocos2d::Label*)>(&cocos2d::ui::Button::setTitleLabel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(std::string_view)>(&cocos2d::ui::Button::setTitleText));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setZoomScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(float)>(&cocos2d::ui::Button::setZoomScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Button", "ccui.Button:create");
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::ui::Button*(*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::create));
	LUA_TRY_INVOKE_R(3, [](std::string_view arg0,std::string_view arg1,std::string_view arg2){{return cocos2d::ui::Button::create(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE_R(2, [](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::Button::create(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::Button::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Button*(*)()>(&cocos2d::ui::Button::create));
	LUA_SINVOKE_FOOTER("0,1,2,3,4");
}
int lua_cocos2d_ui_Button_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Button", "ccui.Button:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Button::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Button, "Button", "ccui.Button",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getRendererClicked", lua_cocos2d_ui_Button_getRendererClicked);
	LUA_METHOD("getRendererDisabled", lua_cocos2d_ui_Button_getRendererDisabled);
	LUA_METHOD("getRendererNormal", lua_cocos2d_ui_Button_getRendererNormal);
	LUA_METHOD("getTitleFontName", lua_cocos2d_ui_Button_getTitleFontName);
	LUA_METHOD("getTitleFontSize", lua_cocos2d_ui_Button_getTitleFontSize);
	LUA_METHOD("getTitleLabel", lua_cocos2d_ui_Button_getTitleLabel);
	LUA_METHOD("getTitleRenderer", lua_cocos2d_ui_Button_getTitleRenderer);
	LUA_METHOD("getTitleText", lua_cocos2d_ui_Button_getTitleText);
	LUA_METHOD("getZoomScale", lua_cocos2d_ui_Button_getZoomScale);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_Button_isScale9Enabled);
	LUA_METHOD("loadTextureDisabled", lua_cocos2d_ui_Button_loadTextureDisabled);
	LUA_METHOD("loadTextureNormal", lua_cocos2d_ui_Button_loadTextureNormal);
	LUA_METHOD("loadTexturePressed", lua_cocos2d_ui_Button_loadTexturePressed);
	LUA_METHOD("loadTextures", lua_cocos2d_ui_Button_loadTextures);
	LUA_METHOD("resetDisabledRender", lua_cocos2d_ui_Button_resetDisabledRender);
	LUA_METHOD("resetNormalRender", lua_cocos2d_ui_Button_resetNormalRender);
	LUA_METHOD("resetPressedRender", lua_cocos2d_ui_Button_resetPressedRender);
	LUA_METHOD("setPressedActionEnabled", lua_cocos2d_ui_Button_setPressedActionEnabled);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_Button_setScale9Enabled);
	LUA_METHOD("setTitleAlignment", lua_cocos2d_ui_Button_setTitleAlignment);
	LUA_METHOD("setTitleFontName", lua_cocos2d_ui_Button_setTitleFontName);
	LUA_METHOD("setTitleFontSize", lua_cocos2d_ui_Button_setTitleFontSize);
	LUA_METHOD("setTitleLabel", lua_cocos2d_ui_Button_setTitleLabel);
	LUA_METHOD("setTitleText", lua_cocos2d_ui_Button_setTitleText);
	LUA_METHOD("setZoomScale", lua_cocos2d_ui_Button_setZoomScale);
	LUA_METHOD("create", lua_cocos2d_ui_Button_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_Button_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackground");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getRendererBackground));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackgroundDisabled");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getRendererBackgroundDisabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackgroundSelected");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getRendererBackgroundSelected));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCross(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererFrontCross");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getRendererFrontCross));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCrossDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererFrontCrossDisabled");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getRendererFrontCrossDisabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getZoomScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::getZoomScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_isSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:isSelected");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::AbstractCheckButton::*)()const>(&cocos2d::ui::AbstractCheckButton::isSelected));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGround(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGround");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGround));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGround(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGroundDisabled");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGroundDisabled));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGroundDisabled(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGroundSelected");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGroundSelected));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGroundSelected(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCross(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureFrontCross");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureFrontCross));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureFrontCross(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCrossDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureFrontCrossDisabled");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureFrontCrossDisabled));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureFrontCrossDisabled(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextures");
	LUA_TRY_INVOKE(6, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextures));
	LUA_TRY_INVOKE(5, [](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}});
	LUA_INVOKE_FOOTER("5,6");
}
int lua_cocos2d_ui_AbstractCheckButton_setSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:setSelected");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(bool)>(&cocos2d::ui::AbstractCheckButton::setSelected));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_AbstractCheckButton_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:setZoomScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::AbstractCheckButton::*)(float)>(&cocos2d::ui::AbstractCheckButton::setZoomScale));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiAbstractCheckButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::AbstractCheckButton, "AbstractCheckButton", "ccui.AbstractCheckButton",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getRendererBackground", lua_cocos2d_ui_AbstractCheckButton_getRendererBackground);
	LUA_METHOD("getRendererBackgroundDisabled", lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundDisabled);
	LUA_METHOD("getRendererBackgroundSelected", lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundSelected);
	LUA_METHOD("getRendererFrontCross", lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCross);
	LUA_METHOD("getRendererFrontCrossDisabled", lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCrossDisabled);
	LUA_METHOD("getZoomScale", lua_cocos2d_ui_AbstractCheckButton_getZoomScale);
	LUA_METHOD("isSelected", lua_cocos2d_ui_AbstractCheckButton_isSelected);
	LUA_METHOD("loadTextureBackGround", lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGround);
	LUA_METHOD("loadTextureBackGroundDisabled", lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundDisabled);
	LUA_METHOD("loadTextureBackGroundSelected", lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundSelected);
	LUA_METHOD("loadTextureFrontCross", lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCross);
	LUA_METHOD("loadTextureFrontCrossDisabled", lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCrossDisabled);
	LUA_METHOD("loadTextures", lua_cocos2d_ui_AbstractCheckButton_loadTextures);
	LUA_METHOD("setSelected", lua_cocos2d_ui_AbstractCheckButton_setSelected);
	LUA_METHOD("setZoomScale", lua_cocos2d_ui_AbstractCheckButton_setZoomScale);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_CheckBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.CheckBox", "ccui.CheckBox:create");
	LUA_TRY_INVOKE_R(6, static_cast<cocos2d::ui::CheckBox*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::CheckBox::create));
	LUA_TRY_INVOKE_R(5, [](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return cocos2d::ui::CheckBox::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}});
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ui::CheckBox*(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::CheckBox::create));
	LUA_TRY_INVOKE_R(2, [](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::CheckBox::create(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::CheckBox*(*)()>(&cocos2d::ui::CheckBox::create));
	LUA_SINVOKE_FOOTER("0,2,3,5,6");
}
int lua_cocos2d_ui_CheckBox_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.CheckBox", "ccui.CheckBox:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::CheckBox::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiCheckBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::CheckBox, "CheckBox", "ccui.CheckBox",
		cocos2d::ui::AbstractCheckButton, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ui_CheckBox_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_CheckBox_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RadioButton_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButton", "ccui.RadioButton:create");
	LUA_TRY_INVOKE_R(6, static_cast<cocos2d::ui::RadioButton*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RadioButton::create));
	LUA_TRY_INVOKE_R(5, [](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return cocos2d::ui::RadioButton::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}});
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ui::RadioButton*(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RadioButton::create));
	LUA_TRY_INVOKE_R(2, [](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::RadioButton::create(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RadioButton*(*)()>(&cocos2d::ui::RadioButton::create));
	LUA_SINVOKE_FOOTER("0,2,3,5,6");
}
int lua_cocos2d_ui_RadioButton_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButton", "ccui.RadioButton:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::RadioButton::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRadioButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RadioButton, "RadioButton", "ccui.RadioButton",
		cocos2d::ui::AbstractCheckButton, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ui_RadioButton_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_RadioButton_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RadioButtonGroup_addRadioButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:addRadioButton");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(cocos2d::ui::RadioButton*)>(&cocos2d::ui::RadioButtonGroup::addRadioButton));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_getNumberOfRadioButtons(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getNumberOfRadioButtons");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::RadioButtonGroup::*)()const>(&cocos2d::ui::RadioButtonGroup::getNumberOfRadioButtons));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_getRadioButtonByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getRadioButtonByIndex");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::RadioButton*(cocos2d::ui::RadioButtonGroup::*)(int)const>(&cocos2d::ui::RadioButtonGroup::getRadioButtonByIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_getSelectedButtonIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getSelectedButtonIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::RadioButtonGroup::*)()const>(&cocos2d::ui::RadioButtonGroup::getSelectedButtonIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_isAllowedNoSelection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:isAllowedNoSelection");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RadioButtonGroup::*)()const>(&cocos2d::ui::RadioButtonGroup::isAllowedNoSelection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_removeAllRadioButtons(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:removeAllRadioButtons");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::RadioButtonGroup::*)()>(&cocos2d::ui::RadioButtonGroup::removeAllRadioButtons));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_removeRadioButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:removeRadioButton");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(cocos2d::ui::RadioButton*)>(&cocos2d::ui::RadioButtonGroup::removeRadioButton));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_setAllowedNoSelection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:setAllowedNoSelection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(bool)>(&cocos2d::ui::RadioButtonGroup::setAllowedNoSelection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RadioButtonGroup*(*)()>(&cocos2d::ui::RadioButtonGroup::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRadioButtonGroup(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RadioButtonGroup, "RadioButtonGroup", "ccui.RadioButtonGroup",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("addRadioButton", lua_cocos2d_ui_RadioButtonGroup_addRadioButton);
	LUA_METHOD("getNumberOfRadioButtons", lua_cocos2d_ui_RadioButtonGroup_getNumberOfRadioButtons);
	LUA_METHOD("getRadioButtonByIndex", lua_cocos2d_ui_RadioButtonGroup_getRadioButtonByIndex);
	LUA_METHOD("getSelectedButtonIndex", lua_cocos2d_ui_RadioButtonGroup_getSelectedButtonIndex);
	LUA_METHOD("isAllowedNoSelection", lua_cocos2d_ui_RadioButtonGroup_isAllowedNoSelection);
	LUA_METHOD("removeAllRadioButtons", lua_cocos2d_ui_RadioButtonGroup_removeAllRadioButtons);
	LUA_METHOD("removeRadioButton", lua_cocos2d_ui_RadioButtonGroup_removeRadioButton);
	LUA_METHOD("setAllowedNoSelection", lua_cocos2d_ui_RadioButtonGroup_setAllowedNoSelection);
	LUA_METHOD("create", lua_cocos2d_ui_RadioButtonGroup_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
