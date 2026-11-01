#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"


int luaReg_UI_ccuiRichElementNewLine(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementNewLine, "RichElementNewLine", "ccui.RichElementNewLine",
		cocos2d::ui::RichElement, "ccui.RichElement",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichText_formatText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:formatText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::formatText));
	LUA_TRY_INVOKE(0, [](cocos2d::ui::RichText* obj){{return obj->formatText();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ui_RichText_getAnchorFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorFontColor");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorFontColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getAnchorTextOutlineSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextOutlineSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextOutlineSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getAnchorTextShadowBlurRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextShadowBlurRadius");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextShadowBlurRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getFontColor");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getFontColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getFontFace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getFontFace");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getFontFace));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RichText::HorizontalAlignment(cocos2d::ui::RichText::*)()const>(&cocos2d::ui::RichText::getHorizontalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getWrapMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getWrapMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RichText::WrapMode(cocos2d::ui::RichText::*)()const>(&cocos2d::ui::RichText::getWrapMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_insertElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:insertElement");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichElement*, int)>(&cocos2d::ui::RichText::insertElement));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_RichText_isAnchorTextBoldEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextBoldEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextBoldEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextDelEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextDelEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextDelEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextGlowEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextGlowEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextGlowEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextItalicEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextItalicEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextItalicEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextOutlineEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextOutlineEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextOutlineEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextShadowEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextShadowEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextShadowEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_isAnchorTextUnderlineEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:isAnchorTextUnderlineEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::isAnchorTextUnderlineEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_openUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:openUrl");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(std::string_view)>(&cocos2d::ui::RichText::openUrl));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_pushBackElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:pushBackElement");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichElement*)>(&cocos2d::ui::RichText::pushBackElement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorFontColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(std::string_view)>(&cocos2d::ui::RichText::setAnchorFontColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorTextBold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextBold");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextBold));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorTextDel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextDel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextDel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorTextItalic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextItalic");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextItalic));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorTextUnderline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextUnderline");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextUnderline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setFontColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(std::string_view)>(&cocos2d::ui::RichText::setFontColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setFontFace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setFontFace");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(std::string_view)>(&cocos2d::ui::RichText::setFontFace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(float)>(&cocos2d::ui::RichText::setFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setHorizontalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichText::HorizontalAlignment)>(&cocos2d::ui::RichText::setHorizontalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setVerticalSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setVerticalSpace");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(float)>(&cocos2d::ui::RichText::setVerticalSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setWrapMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setWrapMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichText::WrapMode)>(&cocos2d::ui::RichText::setWrapMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichText", "ccui.RichText:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RichText*(*)()>(&cocos2d::ui::RichText::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRichText(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichText, "RichText", "ccui.RichText",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("formatText", lua_cocos2d_ui_RichText_formatText);
	LUA_METHOD("getAnchorFontColor", lua_cocos2d_ui_RichText_getAnchorFontColor);
	LUA_METHOD("getAnchorTextOutlineSize", lua_cocos2d_ui_RichText_getAnchorTextOutlineSize);
	LUA_METHOD("getAnchorTextShadowBlurRadius", lua_cocos2d_ui_RichText_getAnchorTextShadowBlurRadius);
	LUA_METHOD("getFontColor", lua_cocos2d_ui_RichText_getFontColor);
	LUA_METHOD("getFontFace", lua_cocos2d_ui_RichText_getFontFace);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_RichText_getFontSize);
	LUA_METHOD("getHorizontalAlignment", lua_cocos2d_ui_RichText_getHorizontalAlignment);
	LUA_METHOD("getWrapMode", lua_cocos2d_ui_RichText_getWrapMode);
	LUA_METHOD("insertElement", lua_cocos2d_ui_RichText_insertElement);
	LUA_METHOD("isAnchorTextBoldEnabled", lua_cocos2d_ui_RichText_isAnchorTextBoldEnabled);
	LUA_METHOD("isAnchorTextDelEnabled", lua_cocos2d_ui_RichText_isAnchorTextDelEnabled);
	LUA_METHOD("isAnchorTextGlowEnabled", lua_cocos2d_ui_RichText_isAnchorTextGlowEnabled);
	LUA_METHOD("isAnchorTextItalicEnabled", lua_cocos2d_ui_RichText_isAnchorTextItalicEnabled);
	LUA_METHOD("isAnchorTextOutlineEnabled", lua_cocos2d_ui_RichText_isAnchorTextOutlineEnabled);
	LUA_METHOD("isAnchorTextShadowEnabled", lua_cocos2d_ui_RichText_isAnchorTextShadowEnabled);
	LUA_METHOD("isAnchorTextUnderlineEnabled", lua_cocos2d_ui_RichText_isAnchorTextUnderlineEnabled);
	LUA_METHOD("openUrl", lua_cocos2d_ui_RichText_openUrl);
	LUA_METHOD("pushBackElement", lua_cocos2d_ui_RichText_pushBackElement);
	LUA_METHOD("setAnchorFontColor", lua_cocos2d_ui_RichText_setAnchorFontColor);
	LUA_METHOD("setAnchorTextBold", lua_cocos2d_ui_RichText_setAnchorTextBold);
	LUA_METHOD("setAnchorTextDel", lua_cocos2d_ui_RichText_setAnchorTextDel);
	LUA_METHOD("setAnchorTextItalic", lua_cocos2d_ui_RichText_setAnchorTextItalic);
	LUA_METHOD("setAnchorTextUnderline", lua_cocos2d_ui_RichText_setAnchorTextUnderline);
	LUA_METHOD("setFontColor", lua_cocos2d_ui_RichText_setFontColor);
	LUA_METHOD("setFontFace", lua_cocos2d_ui_RichText_setFontFace);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_RichText_setFontSize);
	LUA_METHOD("setHorizontalAlignment", lua_cocos2d_ui_RichText_setHorizontalAlignment);
	LUA_METHOD("setVerticalSpace", lua_cocos2d_ui_RichText_setVerticalSpace);
	LUA_METHOD("setWrapMode", lua_cocos2d_ui_RichText_setWrapMode);
	LUA_METHOD("create", lua_cocos2d_ui_RichText_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_UI_ccuiHBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::HBox, "HBox", "ccui.HBox",
		cocos2d::ui::Layout, "ccui.Layout",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_UI_ccuiVBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::VBox, "VBox", "ccui.VBox",
		cocos2d::ui::Layout, "ccui.Layout",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_UI_ccuiRelativeBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RelativeBox, "RelativeBox", "ccui.RelativeBox",
		cocos2d::ui::Layout, "ccui.Layout",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
