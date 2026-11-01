#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_Scale9Sprite_copyTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:copyTo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::ui::Scale9Sprite*)const>(&cocos2d::ui::Scale9Sprite::copyTo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_getInsetBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getInsetBottom");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getInsetBottom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getInsetLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getInsetLeft");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getInsetLeft));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getInsetRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getInsetRight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getInsetRight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getInsetTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getInsetTop");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getInsetTop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getRenderingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getRenderingType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite::RenderingType(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getRenderingType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getSprite");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::Scale9Sprite::*)()>(&cocos2d::ui::Scale9Sprite::getSprite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite::State(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::isScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_resetRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:resetRender");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Scale9Sprite::*)()>(&cocos2d::ui::Scale9Sprite::resetRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_setInsetBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setInsetBottom");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(float)>(&cocos2d::ui::Scale9Sprite::setInsetBottom));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setInsetLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setInsetLeft");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(float)>(&cocos2d::ui::Scale9Sprite::setInsetLeft));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setInsetRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setInsetRight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(float)>(&cocos2d::ui::Scale9Sprite::setInsetRight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setInsetTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setInsetTop");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(float)>(&cocos2d::ui::Scale9Sprite::setInsetTop));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setRenderingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setRenderingType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::ui::Scale9Sprite::RenderingType)>(&cocos2d::ui::Scale9Sprite::setRenderingType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(bool)>(&cocos2d::ui::Scale9Sprite::setScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setState");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::ui::Scale9Sprite::State)>(&cocos2d::ui::Scale9Sprite::setState));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiScale9Sprite(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Scale9Sprite, "Scale9Sprite", "ccui.Scale9Sprite",
		cocos2d::Sprite, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("copyTo", lua_cocos2d_ui_Scale9Sprite_copyTo);
	LUA_METHOD("getInsetBottom", lua_cocos2d_ui_Scale9Sprite_getInsetBottom);
	LUA_METHOD("getInsetLeft", lua_cocos2d_ui_Scale9Sprite_getInsetLeft);
	LUA_METHOD("getInsetRight", lua_cocos2d_ui_Scale9Sprite_getInsetRight);
	LUA_METHOD("getInsetTop", lua_cocos2d_ui_Scale9Sprite_getInsetTop);
	LUA_METHOD("getRenderingType", lua_cocos2d_ui_Scale9Sprite_getRenderingType);
	LUA_METHOD("getSprite", lua_cocos2d_ui_Scale9Sprite_getSprite);
	LUA_METHOD("getState", lua_cocos2d_ui_Scale9Sprite_getState);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_Scale9Sprite_isScale9Enabled);
	LUA_METHOD("resetRender", lua_cocos2d_ui_Scale9Sprite_resetRender);
	LUA_METHOD("setInsetBottom", lua_cocos2d_ui_Scale9Sprite_setInsetBottom);
	LUA_METHOD("setInsetLeft", lua_cocos2d_ui_Scale9Sprite_setInsetLeft);
	LUA_METHOD("setInsetRight", lua_cocos2d_ui_Scale9Sprite_setInsetRight);
	LUA_METHOD("setInsetTop", lua_cocos2d_ui_Scale9Sprite_setInsetTop);
	LUA_METHOD("setRenderingType", lua_cocos2d_ui_Scale9Sprite_setRenderingType);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_Scale9Sprite_setScale9Enabled);
	LUA_METHOD("setState", lua_cocos2d_ui_Scale9Sprite_setState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_EditBox_closeKeyboard(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:closeKeyboard");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::closeKeyboard));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getFontName");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getInputFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getInputFlag");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::EditBox::InputFlag(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getInputFlag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getInputMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getInputMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::EditBox::InputMode(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getInputMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getMaxLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::EditBox::*)()>(&cocos2d::ui::EditBox::getMaxLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getPlaceHolder");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getPlaceHolder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getPlaceholderFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getPlaceholderFontName");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getPlaceholderFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getPlaceholderFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getPlaceholderFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getPlaceholderFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getReturnType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getReturnType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::EditBox::KeyboardReturnType(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getReturnType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getScriptEditBoxHandler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getScriptEditBoxHandler");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::EditBox::*)()>(&cocos2d::ui::EditBox::getScriptEditBoxHandler));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getText");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getText));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getTextHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextHAlignment(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_loadTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextureDisabled");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextureDisabled));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTextureDisabled(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextureNormal");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextureNormal));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTextureNormal(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTexturePressed");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTexturePressed));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTexturePressed(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextures");
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextures));
	LUA_TRY_INVOKE(3, [](cocos2d::ui::EditBox* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE(2, [](cocos2d::ui::EditBox* obj,std::string_view arg0,std::string_view arg1){{return obj->loadTextures(std::move(arg0),std::move(arg1));}});
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ui_EditBox_openKeyboard(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:openKeyboard");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::openKeyboard));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_setFont(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setFont");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::EditBox::*)(const char*, int)>(&cocos2d::ui::EditBox::setFont));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_EditBox_setFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const char*)>(&cocos2d::ui::EditBox::setFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(int)>(&cocos2d::ui::EditBox::setFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setInputFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setInputFlag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(cocos2d::ui::EditBox::InputFlag)>(&cocos2d::ui::EditBox::setInputFlag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setInputMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setInputMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(cocos2d::ui::EditBox::InputMode)>(&cocos2d::ui::EditBox::setInputMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setMaxLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(int)>(&cocos2d::ui::EditBox::setMaxLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setPlaceHolder");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const char*)>(&cocos2d::ui::EditBox::setPlaceHolder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setPlaceholderFont(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setPlaceholderFont");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::EditBox::*)(const char*, int)>(&cocos2d::ui::EditBox::setPlaceholderFont));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_EditBox_setPlaceholderFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setPlaceholderFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const char*)>(&cocos2d::ui::EditBox::setPlaceholderFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setPlaceholderFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setPlaceholderFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(int)>(&cocos2d::ui::EditBox::setPlaceholderFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setReturnType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setReturnType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(cocos2d::ui::EditBox::KeyboardReturnType)>(&cocos2d::ui::EditBox::setReturnType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const char*)>(&cocos2d::ui::EditBox::setText));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setTextHorizontalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::EditBox::setTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiEditBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::EditBox, "EditBox", "ccui.EditBox",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("closeKeyboard", lua_cocos2d_ui_EditBox_closeKeyboard);
	LUA_METHOD("getFontName", lua_cocos2d_ui_EditBox_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_EditBox_getFontSize);
	LUA_METHOD("getInputFlag", lua_cocos2d_ui_EditBox_getInputFlag);
	LUA_METHOD("getInputMode", lua_cocos2d_ui_EditBox_getInputMode);
	LUA_METHOD("getMaxLength", lua_cocos2d_ui_EditBox_getMaxLength);
	LUA_METHOD("getPlaceHolder", lua_cocos2d_ui_EditBox_getPlaceHolder);
	LUA_METHOD("getPlaceholderFontName", lua_cocos2d_ui_EditBox_getPlaceholderFontName);
	LUA_METHOD("getPlaceholderFontSize", lua_cocos2d_ui_EditBox_getPlaceholderFontSize);
	LUA_METHOD("getReturnType", lua_cocos2d_ui_EditBox_getReturnType);
	LUA_METHOD("getScriptEditBoxHandler", lua_cocos2d_ui_EditBox_getScriptEditBoxHandler);
	LUA_METHOD("getText", lua_cocos2d_ui_EditBox_getText);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_EditBox_getTextHorizontalAlignment);
	LUA_METHOD("loadTextureDisabled", lua_cocos2d_ui_EditBox_loadTextureDisabled);
	LUA_METHOD("loadTextureNormal", lua_cocos2d_ui_EditBox_loadTextureNormal);
	LUA_METHOD("loadTexturePressed", lua_cocos2d_ui_EditBox_loadTexturePressed);
	LUA_METHOD("loadTextures", lua_cocos2d_ui_EditBox_loadTextures);
	LUA_METHOD("openKeyboard", lua_cocos2d_ui_EditBox_openKeyboard);
	LUA_METHOD("setFont", lua_cocos2d_ui_EditBox_setFont);
	LUA_METHOD("setFontName", lua_cocos2d_ui_EditBox_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_EditBox_setFontSize);
	LUA_METHOD("setInputFlag", lua_cocos2d_ui_EditBox_setInputFlag);
	LUA_METHOD("setInputMode", lua_cocos2d_ui_EditBox_setInputMode);
	LUA_METHOD("setMaxLength", lua_cocos2d_ui_EditBox_setMaxLength);
	LUA_METHOD("setPlaceHolder", lua_cocos2d_ui_EditBox_setPlaceHolder);
	LUA_METHOD("setPlaceholderFont", lua_cocos2d_ui_EditBox_setPlaceholderFont);
	LUA_METHOD("setPlaceholderFontName", lua_cocos2d_ui_EditBox_setPlaceholderFontName);
	LUA_METHOD("setPlaceholderFontSize", lua_cocos2d_ui_EditBox_setPlaceholderFontSize);
	LUA_METHOD("setReturnType", lua_cocos2d_ui_EditBox_setReturnType);
	LUA_METHOD("setText", lua_cocos2d_ui_EditBox_setText);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_EditBox_setTextHorizontalAlignment);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_LayoutComponent_getBottomMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getBottomMargin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getBottomMargin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getHorizontalEdge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getHorizontalEdge");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutComponent::HorizontalEdge(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getHorizontalEdge));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getLeftMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getLeftMargin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getLeftMargin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getPercentHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPercentHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPercentHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getPercentWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPercentWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPercentWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getPositionPercentX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPositionPercentX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPositionPercentX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getPositionPercentY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPositionPercentY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPositionPercentY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getRightMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getRightMargin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getRightMargin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getSizeHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getSizeHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getSizeHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getSizeWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getSizeWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getSizeWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getTopMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getTopMargin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getTopMargin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getUsingPercentContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getUsingPercentContentSize");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getUsingPercentContentSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_getVerticalEdge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getVerticalEdge");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutComponent::VerticalEdge(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getVerticalEdge));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isPercentHeightEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isPercentHeightEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isPercentHeightEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isPercentWidthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isPercentWidthEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isPercentWidthEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isPositionPercentXEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isPositionPercentXEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isPositionPercentXEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isPositionPercentYEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isPositionPercentYEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isPositionPercentYEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isStretchHeightEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isStretchHeightEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isStretchHeightEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_isStretchWidthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:isStretchWidthEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::isStretchWidthEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_refreshLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:refreshLayout");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::LayoutComponent::*)()>(&cocos2d::ui::LayoutComponent::refreshLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutComponent_setActiveEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setActiveEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setActiveEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setBottomMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setBottomMargin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setBottomMargin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setHorizontalEdge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setHorizontalEdge");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(cocos2d::ui::LayoutComponent::HorizontalEdge)>(&cocos2d::ui::LayoutComponent::setHorizontalEdge));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setLeftMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setLeftMargin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setLeftMargin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPercentHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setPercentHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPercentHeightEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentHeightEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setPercentHeightEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPercentOnlyEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentOnlyEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setPercentOnlyEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPercentWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setPercentWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPercentWidthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentWidthEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setPercentWidthEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPositionPercentX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPositionPercentX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setPositionPercentX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPositionPercentXEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPositionPercentXEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setPositionPercentXEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPositionPercentY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPositionPercentY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setPositionPercentY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setPositionPercentYEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPositionPercentYEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setPositionPercentYEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setRightMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setRightMargin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setRightMargin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setSizeHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setSizeHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setSizeHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setSizeWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setSizeWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setSizeWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setStretchHeightEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setStretchHeightEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setStretchHeightEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setStretchWidthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setStretchWidthEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setStretchWidthEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setTopMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setTopMargin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(float)>(&cocos2d::ui::LayoutComponent::setTopMargin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setUsingPercentContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setUsingPercentContentSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(bool)>(&cocos2d::ui::LayoutComponent::setUsingPercentContentSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_setVerticalEdge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setVerticalEdge");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(cocos2d::ui::LayoutComponent::VerticalEdge)>(&cocos2d::ui::LayoutComponent::setVerticalEdge));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_bindLayoutComponent(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:bindLayoutComponent");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::LayoutComponent*(*)(cocos2d::Node*)>(&cocos2d::ui::LayoutComponent::bindLayoutComponent));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutComponent_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutComponent*(*)()>(&cocos2d::ui::LayoutComponent::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLayoutComponent(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LayoutComponent, "LayoutComponent", "ccui.LayoutComponent",
		cocos2d::Component, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getBottomMargin", lua_cocos2d_ui_LayoutComponent_getBottomMargin);
	LUA_METHOD("getHorizontalEdge", lua_cocos2d_ui_LayoutComponent_getHorizontalEdge);
	LUA_METHOD("getLeftMargin", lua_cocos2d_ui_LayoutComponent_getLeftMargin);
	LUA_METHOD("getPercentHeight", lua_cocos2d_ui_LayoutComponent_getPercentHeight);
	LUA_METHOD("getPercentWidth", lua_cocos2d_ui_LayoutComponent_getPercentWidth);
	LUA_METHOD("getPositionPercentX", lua_cocos2d_ui_LayoutComponent_getPositionPercentX);
	LUA_METHOD("getPositionPercentY", lua_cocos2d_ui_LayoutComponent_getPositionPercentY);
	LUA_METHOD("getRightMargin", lua_cocos2d_ui_LayoutComponent_getRightMargin);
	LUA_METHOD("getSizeHeight", lua_cocos2d_ui_LayoutComponent_getSizeHeight);
	LUA_METHOD("getSizeWidth", lua_cocos2d_ui_LayoutComponent_getSizeWidth);
	LUA_METHOD("getTopMargin", lua_cocos2d_ui_LayoutComponent_getTopMargin);
	LUA_METHOD("getUsingPercentContentSize", lua_cocos2d_ui_LayoutComponent_getUsingPercentContentSize);
	LUA_METHOD("getVerticalEdge", lua_cocos2d_ui_LayoutComponent_getVerticalEdge);
	LUA_METHOD("isPercentHeightEnabled", lua_cocos2d_ui_LayoutComponent_isPercentHeightEnabled);
	LUA_METHOD("isPercentWidthEnabled", lua_cocos2d_ui_LayoutComponent_isPercentWidthEnabled);
	LUA_METHOD("isPositionPercentXEnabled", lua_cocos2d_ui_LayoutComponent_isPositionPercentXEnabled);
	LUA_METHOD("isPositionPercentYEnabled", lua_cocos2d_ui_LayoutComponent_isPositionPercentYEnabled);
	LUA_METHOD("isStretchHeightEnabled", lua_cocos2d_ui_LayoutComponent_isStretchHeightEnabled);
	LUA_METHOD("isStretchWidthEnabled", lua_cocos2d_ui_LayoutComponent_isStretchWidthEnabled);
	LUA_METHOD("refreshLayout", lua_cocos2d_ui_LayoutComponent_refreshLayout);
	LUA_METHOD("setActiveEnabled", lua_cocos2d_ui_LayoutComponent_setActiveEnabled);
	LUA_METHOD("setBottomMargin", lua_cocos2d_ui_LayoutComponent_setBottomMargin);
	LUA_METHOD("setHorizontalEdge", lua_cocos2d_ui_LayoutComponent_setHorizontalEdge);
	LUA_METHOD("setLeftMargin", lua_cocos2d_ui_LayoutComponent_setLeftMargin);
	LUA_METHOD("setPercentHeight", lua_cocos2d_ui_LayoutComponent_setPercentHeight);
	LUA_METHOD("setPercentHeightEnabled", lua_cocos2d_ui_LayoutComponent_setPercentHeightEnabled);
	LUA_METHOD("setPercentOnlyEnabled", lua_cocos2d_ui_LayoutComponent_setPercentOnlyEnabled);
	LUA_METHOD("setPercentWidth", lua_cocos2d_ui_LayoutComponent_setPercentWidth);
	LUA_METHOD("setPercentWidthEnabled", lua_cocos2d_ui_LayoutComponent_setPercentWidthEnabled);
	LUA_METHOD("setPositionPercentX", lua_cocos2d_ui_LayoutComponent_setPositionPercentX);
	LUA_METHOD("setPositionPercentXEnabled", lua_cocos2d_ui_LayoutComponent_setPositionPercentXEnabled);
	LUA_METHOD("setPositionPercentY", lua_cocos2d_ui_LayoutComponent_setPositionPercentY);
	LUA_METHOD("setPositionPercentYEnabled", lua_cocos2d_ui_LayoutComponent_setPositionPercentYEnabled);
	LUA_METHOD("setRightMargin", lua_cocos2d_ui_LayoutComponent_setRightMargin);
	LUA_METHOD("setSizeHeight", lua_cocos2d_ui_LayoutComponent_setSizeHeight);
	LUA_METHOD("setSizeWidth", lua_cocos2d_ui_LayoutComponent_setSizeWidth);
	LUA_METHOD("setStretchHeightEnabled", lua_cocos2d_ui_LayoutComponent_setStretchHeightEnabled);
	LUA_METHOD("setStretchWidthEnabled", lua_cocos2d_ui_LayoutComponent_setStretchWidthEnabled);
	LUA_METHOD("setTopMargin", lua_cocos2d_ui_LayoutComponent_setTopMargin);
	LUA_METHOD("setUsingPercentContentSize", lua_cocos2d_ui_LayoutComponent_setUsingPercentContentSize);
	LUA_METHOD("setVerticalEdge", lua_cocos2d_ui_LayoutComponent_setVerticalEdge);
	LUA_METHOD("bindLayoutComponent", lua_cocos2d_ui_LayoutComponent_bindLayoutComponent);
	LUA_METHOD("create", lua_cocos2d_ui_LayoutComponent_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TabHeader_getIndexInTabControl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getIndexInTabControl");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getIndexInTabControl));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabHeader_getTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getTitleFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getTitleFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabHeader_getTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getTitleFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getTitleFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabHeader_getTitleRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getTitleRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label*(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getTitleRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabHeader_getTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getTitleText");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getTitleText));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabHeader_setTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:setTitleFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabHeader::*)(std::string_view)>(&cocos2d::ui::TabHeader::setTitleFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabHeader_setTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:setTitleFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabHeader::*)(float)>(&cocos2d::ui::TabHeader::setTitleFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabHeader_setTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:setTitleText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabHeader::*)(std::string_view)>(&cocos2d::ui::TabHeader::setTitleText));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabHeader_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:create");
	LUA_TRY_INVOKE_R(7, static_cast<cocos2d::ui::TabHeader*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::TabHeader::create));
	LUA_TRY_INVOKE_R(6, [](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4,std::string_view arg5){{return cocos2d::ui::TabHeader::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5));}});
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::ui::TabHeader*(*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::TabHeader::create));
	LUA_TRY_INVOKE_R(3, [](std::string_view arg0,std::string_view arg1,std::string_view arg2){{return cocos2d::ui::TabHeader::create(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TabHeader*(*)()>(&cocos2d::ui::TabHeader::create));
	LUA_SINVOKE_FOOTER("0,3,4,6,7");
}
int luaReg_UI_ccuiTabHeader(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TabHeader, "TabHeader", "ccui.TabHeader",
		cocos2d::ui::AbstractCheckButton, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("getIndexInTabControl", lua_cocos2d_ui_TabHeader_getIndexInTabControl);
	LUA_METHOD("getTitleFontName", lua_cocos2d_ui_TabHeader_getTitleFontName);
	LUA_METHOD("getTitleFontSize", lua_cocos2d_ui_TabHeader_getTitleFontSize);
	LUA_METHOD("getTitleRenderer", lua_cocos2d_ui_TabHeader_getTitleRenderer);
	LUA_METHOD("getTitleText", lua_cocos2d_ui_TabHeader_getTitleText);
	LUA_METHOD("setTitleFontName", lua_cocos2d_ui_TabHeader_setTitleFontName);
	LUA_METHOD("setTitleFontSize", lua_cocos2d_ui_TabHeader_setTitleFontSize);
	LUA_METHOD("setTitleText", lua_cocos2d_ui_TabHeader_setTitleText);
	LUA_METHOD("create", lua_cocos2d_ui_TabHeader_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TabControl_getHeaderDockPlace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getHeaderDockPlace");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TabControl::Dock(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getHeaderDockPlace));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getHeaderHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getHeaderHeight");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getHeaderHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getHeaderSelectedZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getHeaderSelectedZoom");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getHeaderSelectedZoom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getHeaderWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getHeaderWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getHeaderWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getSelectedTabIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getSelectedTabIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getSelectedTabIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getTabContainer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getTabContainer");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Layout*(cocos2d::ui::TabControl::*)(int)const>(&cocos2d::ui::TabControl::getTabContainer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_getTabCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getTabCount");
	LUA_TRY_INVOKE_R(0, static_cast<size_t(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::getTabCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_getTabHeader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:getTabHeader");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::TabHeader*(cocos2d::ui::TabControl::*)(int)const>(&cocos2d::ui::TabControl::getTabHeader));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_ignoreHeadersTextureSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:ignoreHeadersTextureSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(bool)>(&cocos2d::ui::TabControl::ignoreHeadersTextureSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_indexOfTabHeader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:indexOfTabHeader");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::ui::TabControl::*)(const cocos2d::ui::TabHeader*)const>(&cocos2d::ui::TabControl::indexOfTabHeader));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_insertTab(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:insertTab");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ui::TabControl::*)(int, cocos2d::ui::TabHeader*, cocos2d::ui::Layout*)>(&cocos2d::ui::TabControl::insertTab));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_TabControl_isIgnoreHeadersTextureSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:isIgnoreHeadersTextureSize");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TabControl::*)()const>(&cocos2d::ui::TabControl::isIgnoreHeadersTextureSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TabControl_removeTab(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:removeTab");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(int)>(&cocos2d::ui::TabControl::removeTab));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_setHeaderDockPlace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setHeaderDockPlace");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(cocos2d::ui::TabControl::Dock)>(&cocos2d::ui::TabControl::setHeaderDockPlace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_setHeaderHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setHeaderHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(float)>(&cocos2d::ui::TabControl::setHeaderHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_setHeaderSelectedZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setHeaderSelectedZoom");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(float)>(&cocos2d::ui::TabControl::setHeaderSelectedZoom));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_setHeaderWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setHeaderWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(float)>(&cocos2d::ui::TabControl::setHeaderWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TabControl", "ccui.TabControl:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TabControl*(*)()>(&cocos2d::ui::TabControl::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiTabControl(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TabControl, "TabControl", "ccui.TabControl",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getHeaderDockPlace", lua_cocos2d_ui_TabControl_getHeaderDockPlace);
	LUA_METHOD("getHeaderHeight", lua_cocos2d_ui_TabControl_getHeaderHeight);
	LUA_METHOD("getHeaderSelectedZoom", lua_cocos2d_ui_TabControl_getHeaderSelectedZoom);
	LUA_METHOD("getHeaderWidth", lua_cocos2d_ui_TabControl_getHeaderWidth);
	LUA_METHOD("getSelectedTabIndex", lua_cocos2d_ui_TabControl_getSelectedTabIndex);
	LUA_METHOD("getTabContainer", lua_cocos2d_ui_TabControl_getTabContainer);
	LUA_METHOD("getTabCount", lua_cocos2d_ui_TabControl_getTabCount);
	LUA_METHOD("getTabHeader", lua_cocos2d_ui_TabControl_getTabHeader);
	LUA_METHOD("ignoreHeadersTextureSize", lua_cocos2d_ui_TabControl_ignoreHeadersTextureSize);
	LUA_METHOD("indexOfTabHeader", lua_cocos2d_ui_TabControl_indexOfTabHeader);
	LUA_METHOD("insertTab", lua_cocos2d_ui_TabControl_insertTab);
	LUA_METHOD("isIgnoreHeadersTextureSize", lua_cocos2d_ui_TabControl_isIgnoreHeadersTextureSize);
	LUA_METHOD("removeTab", lua_cocos2d_ui_TabControl_removeTab);
	LUA_METHOD("setHeaderDockPlace", lua_cocos2d_ui_TabControl_setHeaderDockPlace);
	LUA_METHOD("setHeaderHeight", lua_cocos2d_ui_TabControl_setHeaderHeight);
	LUA_METHOD("setHeaderSelectedZoom", lua_cocos2d_ui_TabControl_setHeaderSelectedZoom);
	LUA_METHOD("setHeaderWidth", lua_cocos2d_ui_TabControl_setHeaderWidth);
	LUA_METHOD("create", lua_cocos2d_ui_TabControl_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
