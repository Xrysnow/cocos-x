#include "cclua_ui_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"

int lua_cocos2d_ui_Text_disableEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:disableEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(cocos2d::LabelEffect)>(&cocos2d::ui::Text::disableEffect));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::disableEffect));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ui_Text_enableGlow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableGlow");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B&)>(&cocos2d::ui::Text::enableGlow));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_enableOutline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableOutline");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B&, int)>(&cocos2d::ui::Text::enableOutline)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){{return obj->enableOutline(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Text_enableShadow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableShadow");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B&, const cocos2d::Vec2&, int)>(&cocos2d::ui::Text::enableShadow)));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0,const cocos2d::Vec2& arg1){{return obj->enableShadow(arg0,arg1);}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){{return obj->enableShadow(arg0);}}));
	LUA_TRY_INVOKE(0, [](cocos2d::ui::Text* obj){{return obj->enableShadow();}});
	LUA_INVOKE_FOOTER("0,1,2,3");
}
int lua_cocos2d_ui_Text_getAutoRenderSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getAutoRenderSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::getAutoRenderSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getEffectColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getEffectColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color4B(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getEffectColor));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_ui_Text_getShadowColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color4B(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getShadowOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowOffset");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowOffset));
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
int lua_cocos2d_ui_Text_getTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextAreaSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextAreaSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextColor));
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
int lua_cocos2d_ui_Text_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:init");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::Text::*)(std::string_view, std::string_view, float)>(&cocos2d::ui::Text::init)));
	LUA_INVOKE_FOOTER("3");
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
int lua_cocos2d_ui_Text_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(const cocos2d::BlendFunc&)>(&cocos2d::ui::Text::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_Text_setTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextAreaSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Vec2&)>(&cocos2d::ui::Text::setTextAreaSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B)>(&cocos2d::ui::Text::setTextColor));
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
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::Text*(*)(std::string_view, std::string_view, float)>(&cocos2d::ui::Text::create)));
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
		cocos2d::ui::Text, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("disableEffect", lua_cocos2d_ui_Text_disableEffect);
	LUA_METHOD("enableGlow", lua_cocos2d_ui_Text_enableGlow);
	LUA_METHOD("enableOutline", lua_cocos2d_ui_Text_enableOutline);
	LUA_METHOD("enableShadow", lua_cocos2d_ui_Text_enableShadow);
	LUA_METHOD("getAutoRenderSize", lua_cocos2d_ui_Text_getAutoRenderSize);
	LUA_METHOD("getBlendFunc", lua_cocos2d_ui_Text_getBlendFunc);
	LUA_METHOD("getEffectColor", lua_cocos2d_ui_Text_getEffectColor);
	LUA_METHOD("getFontName", lua_cocos2d_ui_Text_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_Text_getFontSize);
	LUA_METHOD("getLabelEffectType", lua_cocos2d_ui_Text_getLabelEffectType);
	LUA_METHOD("getLetter", lua_cocos2d_ui_Text_getLetter);
	LUA_METHOD("getOutlineSize", lua_cocos2d_ui_Text_getOutlineSize);
	LUA_METHOD("getShadowBlurRadius", lua_cocos2d_ui_Text_getShadowBlurRadius);
	LUA_METHOD("getShadowColor", lua_cocos2d_ui_Text_getShadowColor);
	LUA_METHOD("getShadowOffset", lua_cocos2d_ui_Text_getShadowOffset);
	LUA_METHOD("getString", lua_cocos2d_ui_Text_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_Text_getStringLength);
	LUA_METHOD("getTextAreaSize", lua_cocos2d_ui_Text_getTextAreaSize);
	LUA_METHOD("getTextColor", lua_cocos2d_ui_Text_getTextColor);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_Text_getTextHorizontalAlignment);
	LUA_METHOD("getTextVerticalAlignment", lua_cocos2d_ui_Text_getTextVerticalAlignment);
	LUA_METHOD("getType", lua_cocos2d_ui_Text_getType);
	LUA_METHOD("init", lua_cocos2d_ui_Text_init);
	LUA_METHOD("isShadowEnabled", lua_cocos2d_ui_Text_isShadowEnabled);
	LUA_METHOD("isTouchScaleChangeEnabled", lua_cocos2d_ui_Text_isTouchScaleChangeEnabled);
	LUA_METHOD("setBlendFunc", lua_cocos2d_ui_Text_setBlendFunc);
	LUA_METHOD("setFontName", lua_cocos2d_ui_Text_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_Text_setFontSize);
	LUA_METHOD("setString", lua_cocos2d_ui_Text_setString);
	LUA_METHOD("setTextAreaSize", lua_cocos2d_ui_Text_setTextAreaSize);
	LUA_METHOD("setTextColor", lua_cocos2d_ui_Text_setTextColor);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_Text_setTextHorizontalAlignment);
	LUA_METHOD("setTextVerticalAlignment", lua_cocos2d_ui_Text_setTextVerticalAlignment);
	LUA_METHOD("setTouchScaleChangeEnabled", lua_cocos2d_ui_Text_setTouchScaleChangeEnabled);
	LUA_METHOD("create", lua_cocos2d_ui_Text_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_Text_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TextAtlas_adaptRenderers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:adaptRenderers");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::TextAtlas::*)()>(&cocos2d::ui::TextAtlas::adaptRenderers));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getRenderFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::TextAtlas::*)()>(&cocos2d::ui::TextAtlas::getRenderFile));
	LUA_INVOKE_FOOTER("0");
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
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::ui::TextAtlas::*)(std::string_view, std::string_view, int, int, std::string_view)>(&cocos2d::ui::TextAtlas::setProperty)));
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
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::ui::TextAtlas*(*)(std::string_view, std::string_view, int, int, std::string_view)>(&cocos2d::ui::TextAtlas::create)));
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
		cocos2d::ui::TextAtlas, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("adaptRenderers", lua_cocos2d_ui_TextAtlas_adaptRenderers);
	LUA_METHOD("getRenderFile", lua_cocos2d_ui_TextAtlas_getRenderFile);
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
int lua_cocos2d_ui_LoadingBar_getCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getCapInsets");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getCapInsets));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_ui_LoadingBar_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getRenderFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::LoadingBar::*)()>(&cocos2d::ui::LoadingBar::getRenderFile));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::LoadingBar::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::LoadingBar::loadTexture)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::LoadingBar* obj,std::string_view arg0){{return obj->loadTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_LoadingBar_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setCapInsets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LoadingBar::*)(const cocos2d::Rect&)>(&cocos2d::ui::LoadingBar::setCapInsets));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_LoadingBar_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::LoadingBar*(*)(std::string_view, cocos2d::ui::Widget::TextureResType, float)>(&cocos2d::ui::LoadingBar::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](std::string_view arg0,cocos2d::ui::Widget::TextureResType arg1){{return cocos2d::ui::LoadingBar::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::ui::LoadingBar*(*)(std::string_view, float)>(&cocos2d::ui::LoadingBar::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::LoadingBar::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LoadingBar*(*)()>(&cocos2d::ui::LoadingBar::create));
	LUA_SINVOKE_FOOTER("0,1,2,3");
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
		cocos2d::ui::LoadingBar, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getCapInsets", lua_cocos2d_ui_LoadingBar_getCapInsets);
	LUA_METHOD("getDirection", lua_cocos2d_ui_LoadingBar_getDirection);
	LUA_METHOD("getPercent", lua_cocos2d_ui_LoadingBar_getPercent);
	LUA_METHOD("getRenderFile", lua_cocos2d_ui_LoadingBar_getRenderFile);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_LoadingBar_isScale9Enabled);
	LUA_METHOD("loadTexture", lua_cocos2d_ui_LoadingBar_loadTexture);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_LoadingBar_setCapInsets);
	LUA_METHOD("setDirection", lua_cocos2d_ui_LoadingBar_setDirection);
	LUA_METHOD("setPercent", lua_cocos2d_ui_LoadingBar_setPercent);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_LoadingBar_setScale9Enabled);
	LUA_METHOD("create", lua_cocos2d_ui_LoadingBar_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_LoadingBar_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_ScrollView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::ui::ScrollView::ccScrollViewCallback&)>(&cocos2d::ui::ScrollView::addEventListener));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_ScrollView_getInnerContainerPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainerPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainerPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getInnerContainerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainerSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainerSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarAutoHideTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarAutoHideTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarAutoHideTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color3B&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarPositionFromCornerForHorizontal");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForHorizontal));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarPositionFromCornerForVertical");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForVertical));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentBothDirection");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentBothDirection));
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
int lua_cocos2d_ui_ScrollView_jumpToPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentBothDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::jumpToPercentBothDirection));
	LUA_INVOKE_FOOTER("1");
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottom)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomLeft");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottomLeft)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomRight");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToBottomRight)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToLeft");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToLeft)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentBothDirection");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&, float, bool)>(&cocos2d::ui::ScrollView::scrollToPercentBothDirection)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentHorizontal");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::ScrollView::*)(float, float, bool)>(&cocos2d::ui::ScrollView::scrollToPercentHorizontal)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentVertical");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::ScrollView::*)(float, float, bool)>(&cocos2d::ui::ScrollView::scrollToPercentVertical)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToRight");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToRight)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTop");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTop)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopLeft");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTopLeft)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopRight");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ScrollView::*)(float, bool)>(&cocos2d::ui::ScrollView::scrollToTopRight)));
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
int lua_cocos2d_ui_ScrollView_setInnerContainerPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInnerContainerPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setInnerContainerPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setInnerContainerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInnerContainerSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setInnerContainerSize));
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
int lua_cocos2d_ui_ScrollView_setScrollBarColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::ScrollView::setScrollBarColor));
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
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCorner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCorner");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCorner));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCornerForHorizontal");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForHorizontal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCornerForVertical");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForVertical));
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
		cocos2d::ui::ScrollView, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_ScrollView_addEventListener_1);
	LUA_METHOD("getDirection", lua_cocos2d_ui_ScrollView_getDirection);
	LUA_METHOD("getInnerContainer", lua_cocos2d_ui_ScrollView_getInnerContainer);
	LUA_METHOD("getInnerContainerPosition", lua_cocos2d_ui_ScrollView_getInnerContainerPosition);
	LUA_METHOD("getInnerContainerSize", lua_cocos2d_ui_ScrollView_getInnerContainerSize);
	LUA_METHOD("getScrollBarAutoHideTime", lua_cocos2d_ui_ScrollView_getScrollBarAutoHideTime);
	LUA_METHOD("getScrollBarColor", lua_cocos2d_ui_ScrollView_getScrollBarColor);
	LUA_METHOD("getScrollBarOpacity", lua_cocos2d_ui_ScrollView_getScrollBarOpacity);
	LUA_METHOD("getScrollBarPositionFromCornerForHorizontal", lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal);
	LUA_METHOD("getScrollBarPositionFromCornerForVertical", lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForVertical);
	LUA_METHOD("getScrollBarWidth", lua_cocos2d_ui_ScrollView_getScrollBarWidth);
	LUA_METHOD("getScrolledPercentBothDirection", lua_cocos2d_ui_ScrollView_getScrolledPercentBothDirection);
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
	LUA_METHOD("jumpToPercentBothDirection", lua_cocos2d_ui_ScrollView_jumpToPercentBothDirection);
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
	LUA_METHOD("scrollToPercentBothDirection", lua_cocos2d_ui_ScrollView_scrollToPercentBothDirection);
	LUA_METHOD("scrollToPercentHorizontal", lua_cocos2d_ui_ScrollView_scrollToPercentHorizontal);
	LUA_METHOD("scrollToPercentVertical", lua_cocos2d_ui_ScrollView_scrollToPercentVertical);
	LUA_METHOD("scrollToRight", lua_cocos2d_ui_ScrollView_scrollToRight);
	LUA_METHOD("scrollToTop", lua_cocos2d_ui_ScrollView_scrollToTop);
	LUA_METHOD("scrollToTopLeft", lua_cocos2d_ui_ScrollView_scrollToTopLeft);
	LUA_METHOD("scrollToTopRight", lua_cocos2d_ui_ScrollView_scrollToTopRight);
	LUA_METHOD("setBounceEnabled", lua_cocos2d_ui_ScrollView_setBounceEnabled);
	LUA_METHOD("setDirection", lua_cocos2d_ui_ScrollView_setDirection);
	LUA_METHOD("setInertiaScrollEnabled", lua_cocos2d_ui_ScrollView_setInertiaScrollEnabled);
	LUA_METHOD("setInnerContainerPosition", lua_cocos2d_ui_ScrollView_setInnerContainerPosition);
	LUA_METHOD("setInnerContainerSize", lua_cocos2d_ui_ScrollView_setInnerContainerSize);
	LUA_METHOD("setScrollBarAutoHideEnabled", lua_cocos2d_ui_ScrollView_setScrollBarAutoHideEnabled);
	LUA_METHOD("setScrollBarAutoHideTime", lua_cocos2d_ui_ScrollView_setScrollBarAutoHideTime);
	LUA_METHOD("setScrollBarColor", lua_cocos2d_ui_ScrollView_setScrollBarColor);
	LUA_METHOD("setScrollBarEnabled", lua_cocos2d_ui_ScrollView_setScrollBarEnabled);
	LUA_METHOD("setScrollBarOpacity", lua_cocos2d_ui_ScrollView_setScrollBarOpacity);
	LUA_METHOD("setScrollBarPositionFromCorner", lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCorner);
	LUA_METHOD("setScrollBarPositionFromCornerForHorizontal", lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal);
	LUA_METHOD("setScrollBarPositionFromCornerForVertical", lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForVertical);
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
int lua_cocos2d_ui_ListView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(const cocos2d::ui::ListView::ccListViewCallback&)>(&cocos2d::ui::ListView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_addScrollViewEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:addScrollViewEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(const cocos2d::ui::ScrollView::ccScrollViewCallback&)>(&cocos2d::ui::ListView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_doLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:doLayout");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::doLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getBottomPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getBottomPadding");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getBottomPadding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getBottommostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getBottommostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getBottommostItemInCurrentView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getCenterItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getCenterItemInCurrentView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getCenterItemInCurrentView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getClosestItemToPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getClosestItemToPosition");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(const cocos2d::Vec2&, const cocos2d::Vec2&)const>(&cocos2d::ui::ListView::getClosestItemToPosition)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_getClosestItemToPositionInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getClosestItemToPositionInCurrentView");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(const cocos2d::Vec2&, const cocos2d::Vec2&)const>(&cocos2d::ui::ListView::getClosestItemToPositionInCurrentView)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_getCurSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getCurSelectedIndex");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getCurSelectedIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getIndex");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)const>(&cocos2d::ui::ListView::getIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_getItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItem");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(ssize_t)const>(&cocos2d::ui::ListView::getItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_getItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItems");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocos2d::ui::Widget *>&(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::getItems));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getItemsMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItemsMargin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getItemsMargin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getLeftPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getLeftPadding");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getLeftPadding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getLeftmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getLeftmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getLeftmostItemInCurrentView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getMagneticAllowedOutOfBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getMagneticAllowedOutOfBoundary");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getMagneticAllowedOutOfBoundary));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getMagneticType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getMagneticType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::ListView::MagneticType(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getMagneticType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getRightPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getRightPadding");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getRightPadding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getRightmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getRightmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getRightmostItemInCurrentView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getScrollDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getScrollDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getScrollDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getTopPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getTopPadding");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getTopPadding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getTopmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getTopmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getTopmostItemInCurrentView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_insertCustomItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:insertCustomItem");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*, ssize_t)>(&cocos2d::ui::ListView::insertCustomItem)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_insertDefaultItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:insertDefaultItem");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(ssize_t)>(&cocos2d::ui::ListView::insertDefaultItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_jumpToItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:jumpToItem");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::ListView::*)(ssize_t, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::ui::ListView::jumpToItem)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ListView_pushBackCustomItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:pushBackCustomItem");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::ListView::pushBackCustomItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_pushBackDefaultItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:pushBackDefaultItem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::pushBackDefaultItem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_removeAllItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeAllItems");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeAllItems));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_removeItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeItem");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(ssize_t)>(&cocos2d::ui::ListView::removeItem));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_removeLastItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeLastItem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeLastItem));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_scrollToItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:scrollToItem");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ui::ListView::*)(ssize_t, const cocos2d::Vec2&, const cocos2d::Vec2&, float)>(&cocos2d::ui::ListView::scrollToItem)));
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::ListView::*)(ssize_t, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::ui::ListView::scrollToItem)));
	LUA_INVOKE_FOOTER("3,4");
}
int lua_cocos2d_ui_ListView_setBottomPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setBottomPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setBottomPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setCurSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setCurSelectedIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(int)>(&cocos2d::ui::ListView::setCurSelectedIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::ListView::Gravity)>(&cocos2d::ui::ListView::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setItemModel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setItemModel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::ListView::setItemModel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setItemsMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setItemsMargin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setItemsMargin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setLeftPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setLeftPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setLeftPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setMagneticAllowedOutOfBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setMagneticAllowedOutOfBoundary");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(bool)>(&cocos2d::ui::ListView::setMagneticAllowedOutOfBoundary));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setMagneticType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setMagneticType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::ListView::MagneticType)>(&cocos2d::ui::ListView::setMagneticType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setPadding");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ui::ListView::*)(float, float, float, float)>(&cocos2d::ui::ListView::setPadding)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ui_ListView_setRightPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setRightPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setRightPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setScrollDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setScrollDuration");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setScrollDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setTopPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setTopPadding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setTopPadding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ListView", "ccui.ListView:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::ListView*(*)()>(&cocos2d::ui::ListView::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ListView", "ccui.ListView:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ListView::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiListView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ListView, "ListView", "ccui.ListView",
		cocos2d::ui::ListView, "ccui.ScrollView",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_ListView_addEventListener_1);
	LUA_METHOD("addScrollViewEventListener", lua_cocos2d_ui_ListView_addScrollViewEventListener_1);
	LUA_METHOD("doLayout", lua_cocos2d_ui_ListView_doLayout);
	LUA_METHOD("getBottomPadding", lua_cocos2d_ui_ListView_getBottomPadding);
	LUA_METHOD("getBottommostItemInCurrentView", lua_cocos2d_ui_ListView_getBottommostItemInCurrentView);
	LUA_METHOD("getCenterItemInCurrentView", lua_cocos2d_ui_ListView_getCenterItemInCurrentView);
	LUA_METHOD("getClosestItemToPosition", lua_cocos2d_ui_ListView_getClosestItemToPosition);
	LUA_METHOD("getClosestItemToPositionInCurrentView", lua_cocos2d_ui_ListView_getClosestItemToPositionInCurrentView);
	LUA_METHOD("getCurSelectedIndex", lua_cocos2d_ui_ListView_getCurSelectedIndex);
	LUA_METHOD("getIndex", lua_cocos2d_ui_ListView_getIndex);
	LUA_METHOD("getItem", lua_cocos2d_ui_ListView_getItem);
	LUA_METHOD("getItems", lua_cocos2d_ui_ListView_getItems);
	LUA_METHOD("getItemsMargin", lua_cocos2d_ui_ListView_getItemsMargin);
	LUA_METHOD("getLeftPadding", lua_cocos2d_ui_ListView_getLeftPadding);
	LUA_METHOD("getLeftmostItemInCurrentView", lua_cocos2d_ui_ListView_getLeftmostItemInCurrentView);
	LUA_METHOD("getMagneticAllowedOutOfBoundary", lua_cocos2d_ui_ListView_getMagneticAllowedOutOfBoundary);
	LUA_METHOD("getMagneticType", lua_cocos2d_ui_ListView_getMagneticType);
	LUA_METHOD("getRightPadding", lua_cocos2d_ui_ListView_getRightPadding);
	LUA_METHOD("getRightmostItemInCurrentView", lua_cocos2d_ui_ListView_getRightmostItemInCurrentView);
	LUA_METHOD("getScrollDuration", lua_cocos2d_ui_ListView_getScrollDuration);
	LUA_METHOD("getTopPadding", lua_cocos2d_ui_ListView_getTopPadding);
	LUA_METHOD("getTopmostItemInCurrentView", lua_cocos2d_ui_ListView_getTopmostItemInCurrentView);
	LUA_METHOD("insertCustomItem", lua_cocos2d_ui_ListView_insertCustomItem);
	LUA_METHOD("insertDefaultItem", lua_cocos2d_ui_ListView_insertDefaultItem);
	LUA_METHOD("jumpToItem", lua_cocos2d_ui_ListView_jumpToItem);
	LUA_METHOD("pushBackCustomItem", lua_cocos2d_ui_ListView_pushBackCustomItem);
	LUA_METHOD("pushBackDefaultItem", lua_cocos2d_ui_ListView_pushBackDefaultItem);
	LUA_METHOD("removeAllItems", lua_cocos2d_ui_ListView_removeAllItems);
	LUA_METHOD("removeItem", lua_cocos2d_ui_ListView_removeItem);
	LUA_METHOD("removeLastItem", lua_cocos2d_ui_ListView_removeLastItem);
	LUA_METHOD("scrollToItem", lua_cocos2d_ui_ListView_scrollToItem);
	LUA_METHOD("setBottomPadding", lua_cocos2d_ui_ListView_setBottomPadding);
	LUA_METHOD("setCurSelectedIndex", lua_cocos2d_ui_ListView_setCurSelectedIndex);
	LUA_METHOD("setGravity", lua_cocos2d_ui_ListView_setGravity);
	LUA_METHOD("setItemModel", lua_cocos2d_ui_ListView_setItemModel);
	LUA_METHOD("setItemsMargin", lua_cocos2d_ui_ListView_setItemsMargin);
	LUA_METHOD("setLeftPadding", lua_cocos2d_ui_ListView_setLeftPadding);
	LUA_METHOD("setMagneticAllowedOutOfBoundary", lua_cocos2d_ui_ListView_setMagneticAllowedOutOfBoundary);
	LUA_METHOD("setMagneticType", lua_cocos2d_ui_ListView_setMagneticType);
	LUA_METHOD("setPadding", lua_cocos2d_ui_ListView_setPadding);
	LUA_METHOD("setRightPadding", lua_cocos2d_ui_ListView_setRightPadding);
	LUA_METHOD("setScrollDuration", lua_cocos2d_ui_ListView_setScrollDuration);
	LUA_METHOD("setTopPadding", lua_cocos2d_ui_ListView_setTopPadding);
	LUA_METHOD("create", lua_cocos2d_ui_ListView_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_ListView_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Slider_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::ui::Slider::ccSliderCallback&)>(&cocos2d::ui::Slider::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_getBackFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBackFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBackFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallDisabledFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallDisabledFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallDisabledFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallNormalFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallNormalFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallNormalFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallPressedFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallPressedFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallPressedFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getCapInsetsBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getCapInsetsBarRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getCapInsetsBarRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getCapInsetsProgressBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getCapInsetsProgressBarRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getCapInsetsProgressBarRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getMaxPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getMaxPercent");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getMaxPercent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getPercent");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getPercent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getProgressBarFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getProgressBarFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getProgressBarFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallDisabledRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallDisabledRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallNormalRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallNormalRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallPressedRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallPressedRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getZoomScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getZoomScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::isScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_loadBarTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadBarTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadBarTexture)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadBarTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadProgressBarTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadProgressBarTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadProgressBarTexture)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadProgressBarTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextureDisabled");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextureDisabled)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextureDisabled(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextureNormal");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextureNormal)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextureNormal(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTexturePressed");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTexturePressed)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTexturePressed(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextures");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ui::Slider::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextures)));
	LUA_TRY_INVOKE(3, ([](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextures(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_ui_Slider_setCapInsetProgressBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsetProgressBarRenderer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsetProgressBarRenderer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsets));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setCapInsetsBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsetsBarRenderer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsetsBarRenderer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setMaxPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setMaxPercent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(int)>(&cocos2d::ui::Slider::setMaxPercent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setPercent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(int)>(&cocos2d::ui::Slider::setPercent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(bool)>(&cocos2d::ui::Slider::setScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setZoomScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Slider::*)(float)>(&cocos2d::ui::Slider::setZoomScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_updateVisualSlider(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:updateVisualSlider");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::updateVisualSlider));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Slider", "ccui.Slider:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::Slider*(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::create)));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::Slider::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Slider*(*)()>(&cocos2d::ui::Slider::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cocos2d_ui_Slider_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Slider", "ccui.Slider:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Slider::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiSlider(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Slider, "Slider", "ccui.Slider",
		cocos2d::ui::Slider, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_Slider_addEventListener);
	LUA_METHOD("getBackFile", lua_cocos2d_ui_Slider_getBackFile);
	LUA_METHOD("getBallDisabledFile", lua_cocos2d_ui_Slider_getBallDisabledFile);
	LUA_METHOD("getBallNormalFile", lua_cocos2d_ui_Slider_getBallNormalFile);
	LUA_METHOD("getBallPressedFile", lua_cocos2d_ui_Slider_getBallPressedFile);
	LUA_METHOD("getCapInsetsBarRenderer", lua_cocos2d_ui_Slider_getCapInsetsBarRenderer);
	LUA_METHOD("getCapInsetsProgressBarRenderer", lua_cocos2d_ui_Slider_getCapInsetsProgressBarRenderer);
	LUA_METHOD("getMaxPercent", lua_cocos2d_ui_Slider_getMaxPercent);
	LUA_METHOD("getPercent", lua_cocos2d_ui_Slider_getPercent);
	LUA_METHOD("getProgressBarFile", lua_cocos2d_ui_Slider_getProgressBarFile);
	LUA_METHOD("getSlidBallDisabledRenderer", lua_cocos2d_ui_Slider_getSlidBallDisabledRenderer);
	LUA_METHOD("getSlidBallNormalRenderer", lua_cocos2d_ui_Slider_getSlidBallNormalRenderer);
	LUA_METHOD("getSlidBallPressedRenderer", lua_cocos2d_ui_Slider_getSlidBallPressedRenderer);
	LUA_METHOD("getSlidBallRenderer", lua_cocos2d_ui_Slider_getSlidBallRenderer);
	LUA_METHOD("getZoomScale", lua_cocos2d_ui_Slider_getZoomScale);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_Slider_isScale9Enabled);
	LUA_METHOD("loadBarTexture", lua_cocos2d_ui_Slider_loadBarTexture);
	LUA_METHOD("loadProgressBarTexture", lua_cocos2d_ui_Slider_loadProgressBarTexture);
	LUA_METHOD("loadSlidBallTextureDisabled", lua_cocos2d_ui_Slider_loadSlidBallTextureDisabled);
	LUA_METHOD("loadSlidBallTextureNormal", lua_cocos2d_ui_Slider_loadSlidBallTextureNormal);
	LUA_METHOD("loadSlidBallTexturePressed", lua_cocos2d_ui_Slider_loadSlidBallTexturePressed);
	LUA_METHOD("loadSlidBallTextures", lua_cocos2d_ui_Slider_loadSlidBallTextures);
	LUA_METHOD("setCapInsetProgressBarRenderer", lua_cocos2d_ui_Slider_setCapInsetProgressBarRenderer);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_Slider_setCapInsets);
	LUA_METHOD("setCapInsetsBarRenderer", lua_cocos2d_ui_Slider_setCapInsetsBarRenderer);
	LUA_METHOD("setMaxPercent", lua_cocos2d_ui_Slider_setMaxPercent);
	LUA_METHOD("setPercent", lua_cocos2d_ui_Slider_setPercent);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_Slider_setScale9Enabled);
	LUA_METHOD("setZoomScale", lua_cocos2d_ui_Slider_setZoomScale);
	LUA_METHOD("updateVisualSlider", lua_cocos2d_ui_Slider_updateVisualSlider);
	LUA_METHOD("create", lua_cocos2d_ui_Slider_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_Slider_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TextField_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::ui::TextField::ccTextFieldCallback&)>(&cocos2d::ui::TextField::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_attachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:attachWithIME");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::attachWithIME));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_detachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:detachWithIME");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::detachWithIME));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_didNotSelectSelf(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:didNotSelectSelf");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::didNotSelectSelf));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getAttachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getAttachWithIME");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getAttachWithIME));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getAutoRenderSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getAutoRenderSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::getAutoRenderSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getDeleteBackward(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getDeleteBackward");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getDeleteBackward));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getDetachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getDetachWithIME");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getDetachWithIME));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getInsertText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getInsertText");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getInsertText));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getMaxLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getMaxLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPasswordStyleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPasswordStyleText");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPasswordStyleText));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPlaceHolder");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPlaceHolder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPlaceHolderColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPlaceHolderColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPlaceHolderColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getStringLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getStringLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextHAlignment(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextVerticalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextVAlignment(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextVerticalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTouchSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTouchSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTouchSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_isMaxLengthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:isMaxLengthEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::isMaxLengthEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_isPasswordEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:isPasswordEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::isPasswordEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_setAttachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setAttachWithIME");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setAttachWithIME));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setCursorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setCursorEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setCursorFromPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorFromPoint");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Vec2&, const cocos2d::Camera*)>(&cocos2d::ui::TextField::setCursorFromPoint)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_TextField_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::size_t)>(&cocos2d::ui::TextField::setCursorPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setDeleteBackward(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setDeleteBackward");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setDeleteBackward));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setDetachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setDetachWithIME");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setDetachWithIME));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::string_view)>(&cocos2d::ui::TextField::setFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(int)>(&cocos2d::ui::TextField::setFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setInsertText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setInsertText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setInsertText));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setMaxLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(int)>(&cocos2d::ui::TextField::setMaxLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setMaxLengthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setMaxLengthEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setMaxLengthEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPasswordEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPasswordEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setPasswordEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPasswordStyleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPasswordStyleText");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::string_view)>(&cocos2d::ui::TextField::setPasswordStyleText));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPlaceHolder");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::string_view)>(&cocos2d::ui::TextField::setPlaceHolder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPlaceHolderColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPlaceHolderColor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color4B&)>(&cocos2d::ui::TextField::setPlaceHolderColor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color3B&)>(&cocos2d::ui::TextField::setPlaceHolderColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::string_view)>(&cocos2d::ui::TextField::setString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextAreaSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Vec2&)>(&cocos2d::ui::TextField::setTextAreaSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color4B&)>(&cocos2d::ui::TextField::setTextColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextHorizontalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::TextField::setTextHorizontalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextVerticalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(cocos2d::TextVAlignment)>(&cocos2d::ui::TextField::setTextVerticalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTouchAreaEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTouchAreaEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setTouchAreaEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTouchSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTouchSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Vec2&)>(&cocos2d::ui::TextField::setTouchSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextField", "ccui.TextField:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::TextField*(*)(std::string_view, std::string_view, int)>(&cocos2d::ui::TextField::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TextField*(*)()>(&cocos2d::ui::TextField::create));
	LUA_SINVOKE_FOOTER("0,3");
}
int lua_cocos2d_ui_TextField_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextField", "ccui.TextField:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextField::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiTextField(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TextField, "TextField", "ccui.TextField",
		cocos2d::ui::TextField, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_TextField_addEventListener);
	LUA_METHOD("attachWithIME", lua_cocos2d_ui_TextField_attachWithIME);
	LUA_METHOD("detachWithIME", lua_cocos2d_ui_TextField_detachWithIME);
	LUA_METHOD("didNotSelectSelf", lua_cocos2d_ui_TextField_didNotSelectSelf);
	LUA_METHOD("getAttachWithIME", lua_cocos2d_ui_TextField_getAttachWithIME);
	LUA_METHOD("getAutoRenderSize", lua_cocos2d_ui_TextField_getAutoRenderSize);
	LUA_METHOD("getDeleteBackward", lua_cocos2d_ui_TextField_getDeleteBackward);
	LUA_METHOD("getDetachWithIME", lua_cocos2d_ui_TextField_getDetachWithIME);
	LUA_METHOD("getFontName", lua_cocos2d_ui_TextField_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_TextField_getFontSize);
	LUA_METHOD("getInsertText", lua_cocos2d_ui_TextField_getInsertText);
	LUA_METHOD("getMaxLength", lua_cocos2d_ui_TextField_getMaxLength);
	LUA_METHOD("getPasswordStyleText", lua_cocos2d_ui_TextField_getPasswordStyleText);
	LUA_METHOD("getPlaceHolder", lua_cocos2d_ui_TextField_getPlaceHolder);
	LUA_METHOD("getPlaceHolderColor", lua_cocos2d_ui_TextField_getPlaceHolderColor);
	LUA_METHOD("getString", lua_cocos2d_ui_TextField_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_TextField_getStringLength);
	LUA_METHOD("getTextColor", lua_cocos2d_ui_TextField_getTextColor);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_TextField_getTextHorizontalAlignment);
	LUA_METHOD("getTextVerticalAlignment", lua_cocos2d_ui_TextField_getTextVerticalAlignment);
	LUA_METHOD("getTouchSize", lua_cocos2d_ui_TextField_getTouchSize);
	LUA_METHOD("isMaxLengthEnabled", lua_cocos2d_ui_TextField_isMaxLengthEnabled);
	LUA_METHOD("isPasswordEnabled", lua_cocos2d_ui_TextField_isPasswordEnabled);
	LUA_METHOD("setAttachWithIME", lua_cocos2d_ui_TextField_setAttachWithIME);
	LUA_METHOD("setCursorEnabled", lua_cocos2d_ui_TextField_setCursorEnabled);
	LUA_METHOD("setCursorFromPoint", lua_cocos2d_ui_TextField_setCursorFromPoint);
	LUA_METHOD("setCursorPosition", lua_cocos2d_ui_TextField_setCursorPosition);
	LUA_METHOD("setDeleteBackward", lua_cocos2d_ui_TextField_setDeleteBackward);
	LUA_METHOD("setDetachWithIME", lua_cocos2d_ui_TextField_setDetachWithIME);
	LUA_METHOD("setFontName", lua_cocos2d_ui_TextField_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_TextField_setFontSize);
	LUA_METHOD("setInsertText", lua_cocos2d_ui_TextField_setInsertText);
	LUA_METHOD("setMaxLength", lua_cocos2d_ui_TextField_setMaxLength);
	LUA_METHOD("setMaxLengthEnabled", lua_cocos2d_ui_TextField_setMaxLengthEnabled);
	LUA_METHOD("setPasswordEnabled", lua_cocos2d_ui_TextField_setPasswordEnabled);
	LUA_METHOD("setPasswordStyleText", lua_cocos2d_ui_TextField_setPasswordStyleText);
	LUA_METHOD("setPlaceHolder", lua_cocos2d_ui_TextField_setPlaceHolder);
	LUA_METHOD("setPlaceHolderColor", lua_cocos2d_ui_TextField_setPlaceHolderColor);
	LUA_METHOD("setString", lua_cocos2d_ui_TextField_setString);
	LUA_METHOD("setTextAreaSize", lua_cocos2d_ui_TextField_setTextAreaSize);
	LUA_METHOD("setTextColor", lua_cocos2d_ui_TextField_setTextColor);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_TextField_setTextHorizontalAlignment);
	LUA_METHOD("setTextVerticalAlignment", lua_cocos2d_ui_TextField_setTextVerticalAlignment);
	LUA_METHOD("setTouchAreaEnabled", lua_cocos2d_ui_TextField_setTouchAreaEnabled);
	LUA_METHOD("setTouchSize", lua_cocos2d_ui_TextField_setTouchSize);
	LUA_METHOD("create", lua_cocos2d_ui_TextField_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_TextField_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_TextBMFont_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:getRenderFile");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ResourceData(cocos2d::ui::TextBMFont::*)()>(&cocos2d::ui::TextBMFont::getRenderFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:getString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:getStringLength");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getStringLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_resetRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:resetRender");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::TextBMFont::*)()>(&cocos2d::ui::TextBMFont::resetRender));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_setFntFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:setFntFile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextBMFont::*)(std::string_view)>(&cocos2d::ui::TextBMFont::setFntFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextBMFont_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextBMFont::*)(std::string_view)>(&cocos2d::ui::TextBMFont::setString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextBMFont_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::TextBMFont*(*)(std::string_view, std::string_view)>(&cocos2d::ui::TextBMFont::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TextBMFont*(*)()>(&cocos2d::ui::TextBMFont::create));
	LUA_SINVOKE_FOOTER("0,2");
}
int lua_cocos2d_ui_TextBMFont_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextBMFont::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiTextBMFont(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TextBMFont, "TextBMFont", "ccui.TextBMFont",
		cocos2d::ui::TextBMFont, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getRenderFile", lua_cocos2d_ui_TextBMFont_getRenderFile);
	LUA_METHOD("getString", lua_cocos2d_ui_TextBMFont_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_TextBMFont_getStringLength);
	LUA_METHOD("resetRender", lua_cocos2d_ui_TextBMFont_resetRender);
	LUA_METHOD("setFntFile", lua_cocos2d_ui_TextBMFont_setFntFile);
	LUA_METHOD("setString", lua_cocos2d_ui_TextBMFont_setString);
	LUA_METHOD("create", lua_cocos2d_ui_TextBMFont_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_TextBMFont_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
