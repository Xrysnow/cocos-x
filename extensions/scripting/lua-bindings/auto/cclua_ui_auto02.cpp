#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_ImageView_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::isScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ImageView_loadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:loadTexture");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ImageView::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::ImageView::loadTexture));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::ImageView* obj,std::string_view arg0){{return obj->loadTexture(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_ImageView_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:setScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ImageView::*)(bool)>(&cocos2d::ui::ImageView::setScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ImageView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ImageView", "ccui.ImageView:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::ImageView*(*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::ImageView::create));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::ImageView::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::ImageView*(*)()>(&cocos2d::ui::ImageView::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_ui_ImageView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ImageView", "ccui.ImageView:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ImageView::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiImageView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ImageView, "ImageView", "ccui.ImageView",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_ImageView_isScale9Enabled);
	LUA_METHOD("loadTexture", lua_cocos2d_ui_ImageView_loadTexture);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_ImageView_setScale9Enabled);
	LUA_METHOD("create", lua_cocos2d_ui_ImageView_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_ImageView_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Text_disableEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:disableEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(cocos2d::LabelEffect)>(&cocos2d::ui::Text::disableEffect));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::disableEffect));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ui_Text_getFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getLabelEffectType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getLabelEffectType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::LabelEffect(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getLabelEffectType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getLetter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getLetter");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Sprite*(cocos2d::ui::Text::*)(int)>(&cocos2d::ui::Text::getLetter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_getOutlineSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getOutlineSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getOutlineSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getShadowBlurRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowBlurRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowBlurRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getStringLength");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getStringLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextHAlignment(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextVerticalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextVAlignment(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextVerticalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Text::Type(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_isShadowEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:isShadowEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::isShadowEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_isTouchScaleChangeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:isTouchScaleChangeEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::isTouchScaleChangeEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_setFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(std::string_view)>(&cocos2d::ui::Text::setFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(float)>(&cocos2d::ui::Text::setFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(std::string_view)>(&cocos2d::ui::Text::setString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextHorizontalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::Text::setTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextVerticalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(cocos2d::TextVAlignment)>(&cocos2d::ui::Text::setTextVerticalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTouchScaleChangeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTouchScaleChangeEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(bool)>(&cocos2d::ui::Text::setTouchScaleChangeEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Text", "ccui.Text:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ui::Text*(*)(std::string_view, std::string_view, float)>(&cocos2d::ui::Text::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Text*(*)()>(&cocos2d::ui::Text::create));
	LUA_SINVOKE_FOOTER("0,3");
}
int lua_cocos2d_ui_Text_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Text", "ccui.Text:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Text::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiText(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Text, "Text", "ccui.Text",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("disableEffect", lua_cocos2d_ui_Text_disableEffect);
	LUA_METHOD("getFontName", lua_cocos2d_ui_Text_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_Text_getFontSize);
	LUA_METHOD("getLabelEffectType", lua_cocos2d_ui_Text_getLabelEffectType);
	LUA_METHOD("getLetter", lua_cocos2d_ui_Text_getLetter);
	LUA_METHOD("getOutlineSize", lua_cocos2d_ui_Text_getOutlineSize);
	LUA_METHOD("getShadowBlurRadius", lua_cocos2d_ui_Text_getShadowBlurRadius);
	LUA_METHOD("getString", lua_cocos2d_ui_Text_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_Text_getStringLength);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_Text_getTextHorizontalAlignment);
	LUA_METHOD("getTextVerticalAlignment", lua_cocos2d_ui_Text_getTextVerticalAlignment);
	LUA_METHOD("getType", lua_cocos2d_ui_Text_getType);
	LUA_METHOD("isShadowEnabled", lua_cocos2d_ui_Text_isShadowEnabled);
	LUA_METHOD("isTouchScaleChangeEnabled", lua_cocos2d_ui_Text_isTouchScaleChangeEnabled);
	LUA_METHOD("setFontName", lua_cocos2d_ui_Text_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_Text_setFontSize);
	LUA_METHOD("setString", lua_cocos2d_ui_Text_setString);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_Text_setTextHorizontalAlignment);
	LUA_METHOD("setTextVerticalAlignment", lua_cocos2d_ui_Text_setTextVerticalAlignment);
	LUA_METHOD("setTouchScaleChangeEnabled", lua_cocos2d_ui_Text_setTouchScaleChangeEnabled);
	LUA_METHOD("create", lua_cocos2d_ui_Text_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_Text_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TextAtlas_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getStringLength");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getStringLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_setProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:setProperty");
	LUA_TRY_INVOKE(5, static_cast<void(cocos2d::ui::TextAtlas::*)(std::string_view, std::string_view, int, int, std::string_view)>(&cocos2d::ui::TextAtlas::setProperty));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_ui_TextAtlas_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextAtlas::*)(std::string_view)>(&cocos2d::ui::TextAtlas::setString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:create");
	LUA_TRY_INVOKE_R(5, static_cast<cocos2d::ui::TextAtlas*(*)(std::string_view, std::string_view, int, int, std::string_view)>(&cocos2d::ui::TextAtlas::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TextAtlas*(*)()>(&cocos2d::ui::TextAtlas::create));
	LUA_SINVOKE_FOOTER("0,5");
}
int lua_cocos2d_ui_TextAtlas_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextAtlas::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiTextAtlas(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TextAtlas, "TextAtlas", "ccui.TextAtlas",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getString", lua_cocos2d_ui_TextAtlas_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_TextAtlas_getStringLength);
	LUA_METHOD("setProperty", lua_cocos2d_ui_TextAtlas_setProperty);
	LUA_METHOD("setString", lua_cocos2d_ui_TextAtlas_setString);
	LUA_METHOD("create", lua_cocos2d_ui_TextAtlas_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_TextAtlas_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_LoadingBar_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getDirection");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LoadingBar::Direction(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getPercent");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getPercent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::isScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_loadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:loadTexture");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::LoadingBar::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::LoadingBar::loadTexture));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::LoadingBar* obj,std::string_view arg0){{return obj->loadTexture(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_LoadingBar_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LoadingBar::*)(cocos2d::ui::LoadingBar::Direction)>(&cocos2d::ui::LoadingBar::setDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_setPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setPercent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LoadingBar::*)(float)>(&cocos2d::ui::LoadingBar::setPercent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LoadingBar::*)(bool)>(&cocos2d::ui::LoadingBar::setScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::LoadingBar::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLoadingBar(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LoadingBar, "LoadingBar", "ccui.LoadingBar",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getDirection", lua_cocos2d_ui_LoadingBar_getDirection);
	LUA_METHOD("getPercent", lua_cocos2d_ui_LoadingBar_getPercent);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_LoadingBar_isScale9Enabled);
	LUA_METHOD("loadTexture", lua_cocos2d_ui_LoadingBar_loadTexture);
	LUA_METHOD("setDirection", lua_cocos2d_ui_LoadingBar_setDirection);
	LUA_METHOD("setPercent", lua_cocos2d_ui_LoadingBar_setPercent);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_LoadingBar_setScale9Enabled);
	LUA_METHOD("createInstance", lua_cocos2d_ui_LoadingBar_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_ScrollView_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getDirection");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::ScrollView::Direction(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getInnerContainer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Layout*(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarAutoHideTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarAutoHideTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarAutoHideTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentHorizontal");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentHorizontal));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentVertical");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentVertical));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getTouchTotalTimeThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getTouchTotalTimeThreshold");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getTouchTotalTimeThreshold));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isAutoScrolling(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isAutoScrolling");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isAutoScrolling));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isBounceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isBounceEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isBounceEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isInertiaScrollEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isInertiaScrollEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isInertiaScrollEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrollBarAutoHideEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrollBarAutoHideEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrollBarAutoHideEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrollBarEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrollBarEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrollBarEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrolling(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrolling");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrolling));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottom");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottomLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottomLeft");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottomLeft));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottomRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottomRight");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottomRight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToLeft");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToLeft));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentHorizontal");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::jumpToPercentHorizontal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_jumpToPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentVertical");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::jumpToPercentVertical));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_jumpToRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToRight");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToRight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTopLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTopLeft");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTopLeft));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTopRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTopRight");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTopRight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_scrollToBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottom");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottom));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomLeft");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottomLeft));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomRight");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottomRight));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToLeft");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToLeft));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentHorizontal");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ui::ScrollView::*)(float, float, bool)>(&cocos2d::ui::ScrollView::scrollToPercentHorizontal));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentVertical");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ui::ScrollView::*)(float, float, bool)>(&cocos2d::ui::ScrollView::scrollToPercentVertical));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToRight");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToRight));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTop");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTop));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopLeft");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTopLeft));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopRight");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTopRight));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_setBounceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setBounceEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setBounceEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::ui::ScrollView::Direction)>(&cocos2d::ui::ScrollView::setDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setInertiaScrollEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInertiaScrollEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setInertiaScrollEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarAutoHideEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarAutoHideEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setScrollBarAutoHideEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarAutoHideTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarAutoHideTime");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setScrollBarAutoHideTime));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setScrollBarEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(uint8_t)>(&cocos2d::ui::ScrollView::setScrollBarOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setScrollBarWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setTouchTotalTimeThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setTouchTotalTimeThreshold");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setTouchTotalTimeThreshold));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_stopAutoScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopAutoScroll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopAutoScroll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_stopOverallScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopOverallScroll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopOverallScroll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_stopScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopScroll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopScroll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::ScrollView*(*)()>(&cocos2d::ui::ScrollView::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ScrollView::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiScrollView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ScrollView, "ScrollView", "ccui.ScrollView",
		cocos2d::ui::Layout, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("getDirection", lua_cocos2d_ui_ScrollView_getDirection);
	LUA_METHOD("getInnerContainer", lua_cocos2d_ui_ScrollView_getInnerContainer);
	LUA_METHOD("getScrollBarAutoHideTime", lua_cocos2d_ui_ScrollView_getScrollBarAutoHideTime);
	LUA_METHOD("getScrollBarOpacity", lua_cocos2d_ui_ScrollView_getScrollBarOpacity);
	LUA_METHOD("getScrollBarWidth", lua_cocos2d_ui_ScrollView_getScrollBarWidth);
	LUA_METHOD("getScrolledPercentHorizontal", lua_cocos2d_ui_ScrollView_getScrolledPercentHorizontal);
	LUA_METHOD("getScrolledPercentVertical", lua_cocos2d_ui_ScrollView_getScrolledPercentVertical);
	LUA_METHOD("getTouchTotalTimeThreshold", lua_cocos2d_ui_ScrollView_getTouchTotalTimeThreshold);
	LUA_METHOD("isAutoScrolling", lua_cocos2d_ui_ScrollView_isAutoScrolling);
	LUA_METHOD("isBounceEnabled", lua_cocos2d_ui_ScrollView_isBounceEnabled);
	LUA_METHOD("isInertiaScrollEnabled", lua_cocos2d_ui_ScrollView_isInertiaScrollEnabled);
	LUA_METHOD("isScrollBarAutoHideEnabled", lua_cocos2d_ui_ScrollView_isScrollBarAutoHideEnabled);
	LUA_METHOD("isScrollBarEnabled", lua_cocos2d_ui_ScrollView_isScrollBarEnabled);
	LUA_METHOD("isScrolling", lua_cocos2d_ui_ScrollView_isScrolling);
	LUA_METHOD("jumpToBottom", lua_cocos2d_ui_ScrollView_jumpToBottom);
	LUA_METHOD("jumpToBottomLeft", lua_cocos2d_ui_ScrollView_jumpToBottomLeft);
	LUA_METHOD("jumpToBottomRight", lua_cocos2d_ui_ScrollView_jumpToBottomRight);
	LUA_METHOD("jumpToLeft", lua_cocos2d_ui_ScrollView_jumpToLeft);
	LUA_METHOD("jumpToPercentHorizontal", lua_cocos2d_ui_ScrollView_jumpToPercentHorizontal);
	LUA_METHOD("jumpToPercentVertical", lua_cocos2d_ui_ScrollView_jumpToPercentVertical);
	LUA_METHOD("jumpToRight", lua_cocos2d_ui_ScrollView_jumpToRight);
	LUA_METHOD("jumpToTop", lua_cocos2d_ui_ScrollView_jumpToTop);
	LUA_METHOD("jumpToTopLeft", lua_cocos2d_ui_ScrollView_jumpToTopLeft);
	LUA_METHOD("jumpToTopRight", lua_cocos2d_ui_ScrollView_jumpToTopRight);
	LUA_METHOD("scrollToBottom", lua_cocos2d_ui_ScrollView_scrollToBottom);
	LUA_METHOD("scrollToBottomLeft", lua_cocos2d_ui_ScrollView_scrollToBottomLeft);
	LUA_METHOD("scrollToBottomRight", lua_cocos2d_ui_ScrollView_scrollToBottomRight);
	LUA_METHOD("scrollToLeft", lua_cocos2d_ui_ScrollView_scrollToLeft);
	LUA_METHOD("scrollToPercentHorizontal", lua_cocos2d_ui_ScrollView_scrollToPercentHorizontal);
	LUA_METHOD("scrollToPercentVertical", lua_cocos2d_ui_ScrollView_scrollToPercentVertical);
	LUA_METHOD("scrollToRight", lua_cocos2d_ui_ScrollView_scrollToRight);
	LUA_METHOD("scrollToTop", lua_cocos2d_ui_ScrollView_scrollToTop);
	LUA_METHOD("scrollToTopLeft", lua_cocos2d_ui_ScrollView_scrollToTopLeft);
	LUA_METHOD("scrollToTopRight", lua_cocos2d_ui_ScrollView_scrollToTopRight);
	LUA_METHOD("setBounceEnabled", lua_cocos2d_ui_ScrollView_setBounceEnabled);
	LUA_METHOD("setDirection", lua_cocos2d_ui_ScrollView_setDirection);
	LUA_METHOD("setInertiaScrollEnabled", lua_cocos2d_ui_ScrollView_setInertiaScrollEnabled);
	LUA_METHOD("setScrollBarAutoHideEnabled", lua_cocos2d_ui_ScrollView_setScrollBarAutoHideEnabled);
	LUA_METHOD("setScrollBarAutoHideTime", lua_cocos2d_ui_ScrollView_setScrollBarAutoHideTime);
	LUA_METHOD("setScrollBarEnabled", lua_cocos2d_ui_ScrollView_setScrollBarEnabled);
	LUA_METHOD("setScrollBarOpacity", lua_cocos2d_ui_ScrollView_setScrollBarOpacity);
	LUA_METHOD("setScrollBarWidth", lua_cocos2d_ui_ScrollView_setScrollBarWidth);
	LUA_METHOD("setTouchTotalTimeThreshold", lua_cocos2d_ui_ScrollView_setTouchTotalTimeThreshold);
	LUA_METHOD("stopAutoScroll", lua_cocos2d_ui_ScrollView_stopAutoScroll);
	LUA_METHOD("stopOverallScroll", lua_cocos2d_ui_ScrollView_stopOverallScroll);
	LUA_METHOD("stopScroll", lua_cocos2d_ui_ScrollView_stopScroll);
	LUA_METHOD("create", lua_cocos2d_ui_ScrollView_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_ScrollView_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
