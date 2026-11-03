#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_Helper_changeLayoutSystemActiveState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:changeLayoutSystemActiveState");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::ui::Helper::changeLayoutSystemActiveState));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_doLayout(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:doLayout");
	LUA_TRY_INVOKE(1, static_cast<void(*)(cocos2d::Node*)>(&cocos2d::ui::Helper::doLayout));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_getSubStringOfUTF8String(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:getSubStringOfUTF8String");
	LUA_TRY_INVOKE_R(3, static_cast<std::string(*)(std::string_view, std::basic_string<char>::size_type, std::basic_string<char>::size_type)>(&cocos2d::ui::Helper::getSubStringOfUTF8String));
	LUA_SINVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Helper_seekActionWidgetByActionTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekActionWidgetByActionTag");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::Helper::seekActionWidgetByActionTag));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByName");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, std::string_view)>(&cocos2d::ui::Helper::seekWidgetByName));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByTag");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::Helper::seekWidgetByTag));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_UI_ccuiHelper(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF(cocos2d::ui::Helper, "Helper", "ccui.Helper",
		nullptr, nullptr);
	LUA_METHOD("changeLayoutSystemActiveState", lua_cocos2d_ui_Helper_changeLayoutSystemActiveState);
	LUA_METHOD("doLayout", lua_cocos2d_ui_Helper_doLayout);
	LUA_METHOD("getSubStringOfUTF8String", lua_cocos2d_ui_Helper_getSubStringOfUTF8String);
	LUA_METHOD("seekActionWidgetByActionTag", lua_cocos2d_ui_Helper_seekActionWidgetByActionTag);
	LUA_METHOD("seekWidgetByName", lua_cocos2d_ui_Helper_seekWidgetByName);
	LUA_METHOD("seekWidgetByTag", lua_cocos2d_ui_Helper_seekWidgetByTag);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElement_equalType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElement", "ccui.RichElement:equalType");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ui::RichElement::*)(cocos2d::ui::RichElement::Type)>(&cocos2d::ui::RichElement::equalType));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiRichElement(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElement, "RichElement", "ccui.RichElement",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("equalType", lua_cocos2d_ui_RichElement_equalType);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_UI_ccuiRichElementText(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementText, "RichElementText", "ccui.RichElementText",
		cocos2d::ui::RichElement, "ccui.RichElement",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElementImage_setHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(int)>(&cocos2d::ui::RichElementImage::setHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(float)>(&cocos2d::ui::RichElementImage::setScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScaleX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(float)>(&cocos2d::ui::RichElementImage::setScaleX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScaleY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(float)>(&cocos2d::ui::RichElementImage::setScaleY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setUrl");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(std::string_view)>(&cocos2d::ui::RichElementImage::setUrl));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElementImage::*)(int)>(&cocos2d::ui::RichElementImage::setWidth));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiRichElementImage(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementImage, "RichElementImage", "ccui.RichElementImage",
		cocos2d::ui::RichElement, "ccui.RichElement",
		nullptr, nullptr);
	LUA_METHOD("setHeight", lua_cocos2d_ui_RichElementImage_setHeight);
	LUA_METHOD("setScale", lua_cocos2d_ui_RichElementImage_setScale);
	LUA_METHOD("setScaleX", lua_cocos2d_ui_RichElementImage_setScaleX);
	LUA_METHOD("setScaleY", lua_cocos2d_ui_RichElementImage_setScaleY);
	LUA_METHOD("setUrl", lua_cocos2d_ui_RichElementImage_setUrl);
	LUA_METHOD("setWidth", lua_cocos2d_ui_RichElementImage_setWidth);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_UI_ccuiRichElementCustomNode(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementCustomNode, "RichElementCustomNode", "ccui.RichElementCustomNode",
		cocos2d::ui::RichElement, "ccui.RichElement",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
