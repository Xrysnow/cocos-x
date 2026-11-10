#include "cclua_ui_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"

int lua_cocos2d_ui_PageView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::ui::PageView::ccPageViewCallback&)>(&cocos2d::ui::PageView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_addPage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:addPage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::PageView::addPage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_getCurrentPageIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getCurrentPageIndex");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::ui::PageView::*)()>(&cocos2d::ui::PageView::getCurrentPageIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color3B&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorPositionAsAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorPositionAsAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorPositionAsAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSelectedIndexColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSelectedIndexColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color3B&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSelectedIndexColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSelectedIndexOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSelectedIndexOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSelectedIndexOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSpaceBetweenIndexNodes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSpaceBetweenIndexNodes");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSpaceBetweenIndexNodes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_insertPage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:insertPage");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::PageView::insertPage)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_PageView_removeAllPages(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removeAllPages");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::PageView::*)()>(&cocos2d::ui::PageView::removeAllPages));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_removePage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removePage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::PageView::removePage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_removePageAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removePageAtIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::removePageAtIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_scrollToItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:scrollToItem");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::PageView::*)(ssize_t, float)>(&cocos2d::ui::PageView::scrollToItem)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::scrollToItem));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_PageView_scrollToPage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:scrollToPage");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::PageView::*)(ssize_t, float)>(&cocos2d::ui::PageView::scrollToPage)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::scrollToPage));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_PageView_setAutoScrollStopEpsilon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setAutoScrollStopEpsilon");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setAutoScrollStopEpsilon));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setCurrentPageIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setCurrentPageIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::setCurrentPageIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(bool)>(&cocos2d::ui::PageView::setIndicatorEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::PageView::setIndicatorIndexNodesColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(uint8_t)>(&cocos2d::ui::PageView::setIndicatorIndexNodesOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setIndicatorIndexNodesScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::PageView::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::PageView::setIndicatorIndexNodesTexture)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::PageView* obj,std::string_view arg0){{return obj->setIndicatorIndexNodesTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_PageView_setIndicatorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::PageView::setIndicatorPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorPositionAsAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorPositionAsAnchorPoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::PageView::setIndicatorPositionAsAnchorPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSelectedIndexColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSelectedIndexColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::PageView::setIndicatorSelectedIndexColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSelectedIndexOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSelectedIndexOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(uint8_t)>(&cocos2d::ui::PageView::setIndicatorSelectedIndexOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSpaceBetweenIndexNodes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSpaceBetweenIndexNodes");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setIndicatorSpaceBetweenIndexNodes));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.PageView", "ccui.PageView:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::PageView*(*)()>(&cocos2d::ui::PageView::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.PageView", "ccui.PageView:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::PageView::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiPageView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::PageView, "PageView", "ccui.PageView",
		cocos2d::ui::PageView, "ccui.ListView",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_PageView_addEventListener_1);
	LUA_METHOD("addPage", lua_cocos2d_ui_PageView_addPage);
	LUA_METHOD("getCurrentPageIndex", lua_cocos2d_ui_PageView_getCurrentPageIndex);
	LUA_METHOD("getIndicatorEnabled", lua_cocos2d_ui_PageView_getIndicatorEnabled);
	LUA_METHOD("getIndicatorIndexNodesColor", lua_cocos2d_ui_PageView_getIndicatorIndexNodesColor);
	LUA_METHOD("getIndicatorIndexNodesOpacity", lua_cocos2d_ui_PageView_getIndicatorIndexNodesOpacity);
	LUA_METHOD("getIndicatorIndexNodesScale", lua_cocos2d_ui_PageView_getIndicatorIndexNodesScale);
	LUA_METHOD("getIndicatorPosition", lua_cocos2d_ui_PageView_getIndicatorPosition);
	LUA_METHOD("getIndicatorPositionAsAnchorPoint", lua_cocos2d_ui_PageView_getIndicatorPositionAsAnchorPoint);
	LUA_METHOD("getIndicatorSelectedIndexColor", lua_cocos2d_ui_PageView_getIndicatorSelectedIndexColor);
	LUA_METHOD("getIndicatorSelectedIndexOpacity", lua_cocos2d_ui_PageView_getIndicatorSelectedIndexOpacity);
	LUA_METHOD("getIndicatorSpaceBetweenIndexNodes", lua_cocos2d_ui_PageView_getIndicatorSpaceBetweenIndexNodes);
	LUA_METHOD("insertPage", lua_cocos2d_ui_PageView_insertPage);
	LUA_METHOD("removeAllPages", lua_cocos2d_ui_PageView_removeAllPages);
	LUA_METHOD("removePage", lua_cocos2d_ui_PageView_removePage);
	LUA_METHOD("removePageAtIndex", lua_cocos2d_ui_PageView_removePageAtIndex);
	LUA_METHOD("scrollToItem", lua_cocos2d_ui_PageView_scrollToItem);
	LUA_METHOD("scrollToPage", lua_cocos2d_ui_PageView_scrollToPage);
	LUA_METHOD("setAutoScrollStopEpsilon", lua_cocos2d_ui_PageView_setAutoScrollStopEpsilon);
	LUA_METHOD("setCurrentPageIndex", lua_cocos2d_ui_PageView_setCurrentPageIndex);
	LUA_METHOD("setIndicatorEnabled", lua_cocos2d_ui_PageView_setIndicatorEnabled);
	LUA_METHOD("setIndicatorIndexNodesColor", lua_cocos2d_ui_PageView_setIndicatorIndexNodesColor);
	LUA_METHOD("setIndicatorIndexNodesOpacity", lua_cocos2d_ui_PageView_setIndicatorIndexNodesOpacity);
	LUA_METHOD("setIndicatorIndexNodesScale", lua_cocos2d_ui_PageView_setIndicatorIndexNodesScale);
	LUA_METHOD("setIndicatorIndexNodesTexture", lua_cocos2d_ui_PageView_setIndicatorIndexNodesTexture);
	LUA_METHOD("setIndicatorPosition", lua_cocos2d_ui_PageView_setIndicatorPosition);
	LUA_METHOD("setIndicatorPositionAsAnchorPoint", lua_cocos2d_ui_PageView_setIndicatorPositionAsAnchorPoint);
	LUA_METHOD("setIndicatorSelectedIndexColor", lua_cocos2d_ui_PageView_setIndicatorSelectedIndexColor);
	LUA_METHOD("setIndicatorSelectedIndexOpacity", lua_cocos2d_ui_PageView_setIndicatorSelectedIndexOpacity);
	LUA_METHOD("setIndicatorSpaceBetweenIndexNodes", lua_cocos2d_ui_PageView_setIndicatorSpaceBetweenIndexNodes);
	LUA_METHOD("create", lua_cocos2d_ui_PageView_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_PageView_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Helper_changeLayoutSystemActiveState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:changeLayoutSystemActiveState");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::ui::Helper::changeLayoutSystemActiveState));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_convertBoundingBoxToScreen(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:convertBoundingBoxToScreen");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Rect(*)(cocos2d::Node*)>(&cocos2d::ui::Helper::convertBoundingBoxToScreen));
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
	LUA_TRY_INVOKE_R(3, (static_cast<std::string(*)(std::string_view, std::basic_string<char>::size_type, std::basic_string<char>::size_type)>(&cocos2d::ui::Helper::getSubStringOfUTF8String)));
	LUA_SINVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Helper_restrictCapInsetRect(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:restrictCapInsetRect");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Rect(*)(const cocos2d::Rect&, const cocos2d::Vec2&)>(&cocos2d::ui::Helper::restrictCapInsetRect)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekActionWidgetByActionTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekActionWidgetByActionTag");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::Helper::seekActionWidgetByActionTag)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByName");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, std::string_view)>(&cocos2d::ui::Helper::seekWidgetByName)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByTag");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Widget*(*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::Helper::seekWidgetByTag)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_UI_ccuiHelper(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Helper, "Helper", "ccui.Helper",
		cocos2d::ui::Helper, "",
		nullptr, nullptr);
	LUA_METHOD("changeLayoutSystemActiveState", lua_cocos2d_ui_Helper_changeLayoutSystemActiveState);
	LUA_METHOD("convertBoundingBoxToScreen", lua_cocos2d_ui_Helper_convertBoundingBoxToScreen);
	LUA_METHOD("doLayout", lua_cocos2d_ui_Helper_doLayout);
	LUA_METHOD("getSubStringOfUTF8String", lua_cocos2d_ui_Helper_getSubStringOfUTF8String);
	LUA_METHOD("restrictCapInsetRect", lua_cocos2d_ui_Helper_restrictCapInsetRect);
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
int lua_cocos2d_ui_RichElement_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElement", "ccui.RichElement:init");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::RichElement::*)(int, const cocos2d::Color3B&, uint8_t)>(&cocos2d::ui::RichElement::init)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_RichElement_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElement", "ccui.RichElement:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichElement::*)(const cocos2d::Color3B&)>(&cocos2d::ui::RichElement::setColor));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiRichElement(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElement, "RichElement", "ccui.RichElement",
		cocos2d::ui::RichElement, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("equalType", lua_cocos2d_ui_RichElement_equalType);
	LUA_METHOD("init", lua_cocos2d_ui_RichElement_init);
	LUA_METHOD("setColor", lua_cocos2d_ui_RichElement_setColor);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElementText_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementText", "ccui.RichElementText:init");
	LUA_TRY_INVOKE_R(14, (static_cast<bool(cocos2d::ui::RichElementText::*)(int, const cocos2d::Color3B&, uint8_t, std::string_view, std::string_view, float, uint32_t, std::string_view, const cocos2d::Color3B&, int, const cocos2d::Color3B&, const cocos2d::Vec2&, int, const cocos2d::Color3B&)>(&cocos2d::ui::RichElementText::init)));
	LUA_TRY_INVOKE_R(13, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10,const cocos2d::Vec2& arg11,int arg12){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10,arg11,std::move(arg12));}}));
	LUA_TRY_INVOKE_R(12, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10,const cocos2d::Vec2& arg11){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10,arg11);}}));
	LUA_TRY_INVOKE_R(11, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10);}}));
	LUA_TRY_INVOKE_R(10, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9));}}));
	LUA_TRY_INVOKE_R(9, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8);}}));
	LUA_TRY_INVOKE_R(8, ([](cocos2d::ui::RichElementText* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7));}}));
	LUA_INVOKE_FOOTER("10,11,12,13,14,8,9");
}
int lua_cocos2d_ui_RichElementText_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementText", "ccui.RichElementText:create");
	LUA_TRY_INVOKE_R(14, (static_cast<cocos2d::ui::RichElementText*(*)(int, const cocos2d::Color3B&, uint8_t, std::string_view, std::string_view, float, uint32_t, std::string_view, const cocos2d::Color3B&, int, const cocos2d::Color3B&, const cocos2d::Vec2&, int, const cocos2d::Color3B&)>(&cocos2d::ui::RichElementText::create)));
	LUA_TRY_INVOKE_R(13, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10,const cocos2d::Vec2& arg11,int arg12){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10,arg11,std::move(arg12));}}));
	LUA_TRY_INVOKE_R(12, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10,const cocos2d::Vec2& arg11){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10,arg11);}}));
	LUA_TRY_INVOKE_R(11, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9,const cocos2d::Color3B& arg10){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9),arg10);}}));
	LUA_TRY_INVOKE_R(10, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8,int arg9){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8,std::move(arg9));}}));
	LUA_TRY_INVOKE_R(9, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7,const cocos2d::Color3B& arg8){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7),arg8);}}));
	LUA_TRY_INVOKE_R(8, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6,std::string_view arg7){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6),std::move(arg7));}}));
	LUA_TRY_INVOKE_R(7, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5,uint32_t arg6){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5),std::move(arg6));}}));
	LUA_TRY_INVOKE_R(6, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4,float arg5){{return cocos2d::ui::RichElementText::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5));}}));
	LUA_SINVOKE_FOOTER("10,11,12,13,14,6,7,8,9");
}
int luaReg_UI_ccuiRichElementText(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementText, "RichElementText", "ccui.RichElementText",
		cocos2d::ui::RichElementText, "ccui.RichElement",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ui_RichElementText_init);
	LUA_METHOD("create", lua_cocos2d_ui_RichElementText_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElementImage_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:init");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::ui::RichElementImage::*)(int, const cocos2d::Color3B&, uint8_t, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RichElementImage::init)));
	LUA_TRY_INVOKE_R(5, ([](cocos2d::ui::RichElementImage* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](cocos2d::ui::RichElementImage* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3));}}));
	LUA_INVOKE_FOOTER("4,5,6");
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
int lua_cocos2d_ui_RichElementImage_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::ui::RichElementImage*(*)(int, const cocos2d::Color3B&, uint8_t, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RichElementImage::create)));
	LUA_TRY_INVOKE_R(5, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4){{return cocos2d::ui::RichElementImage::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3){{return cocos2d::ui::RichElementImage::create(std::move(arg0),arg1,std::move(arg2),std::move(arg3));}}));
	LUA_SINVOKE_FOOTER("4,5,6");
}
int luaReg_UI_ccuiRichElementImage(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementImage, "RichElementImage", "ccui.RichElementImage",
		cocos2d::ui::RichElementImage, "ccui.RichElement",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ui_RichElementImage_init);
	LUA_METHOD("setHeight", lua_cocos2d_ui_RichElementImage_setHeight);
	LUA_METHOD("setScale", lua_cocos2d_ui_RichElementImage_setScale);
	LUA_METHOD("setScaleX", lua_cocos2d_ui_RichElementImage_setScaleX);
	LUA_METHOD("setScaleY", lua_cocos2d_ui_RichElementImage_setScaleY);
	LUA_METHOD("setUrl", lua_cocos2d_ui_RichElementImage_setUrl);
	LUA_METHOD("setWidth", lua_cocos2d_ui_RichElementImage_setWidth);
	LUA_METHOD("create", lua_cocos2d_ui_RichElementImage_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElementCustomNode_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementCustomNode", "ccui.RichElementCustomNode:init");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ui::RichElementCustomNode::*)(int, const cocos2d::Color3B&, uint8_t, cocos2d::Node*)>(&cocos2d::ui::RichElementCustomNode::init)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ui_RichElementCustomNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementCustomNode", "ccui.RichElementCustomNode:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ui::RichElementCustomNode*(*)(int, const cocos2d::Color3B&, uint8_t, cocos2d::Node*)>(&cocos2d::ui::RichElementCustomNode::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_UI_ccuiRichElementCustomNode(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementCustomNode, "RichElementCustomNode", "ccui.RichElementCustomNode",
		cocos2d::ui::RichElementCustomNode, "ccui.RichElement",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_ui_RichElementCustomNode_init);
	LUA_METHOD("create", lua_cocos2d_ui_RichElementCustomNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichElementNewLine_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementNewLine", "ccui.RichElementNewLine:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::RichElementNewLine*(*)(int, const cocos2d::Color3B&, uint8_t)>(&cocos2d::ui::RichElementNewLine::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_UI_ccuiRichElementNewLine(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichElementNewLine, "RichElementNewLine", "ccui.RichElementNewLine",
		cocos2d::ui::RichElementNewLine, "ccui.RichElement",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ui_RichElementNewLine_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RichText_color3BWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:color3BWithString");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)(std::string_view)>(&cocos2d::ui::RichText::color3BWithString));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_RichText_getAnchorFontColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorFontColor3B");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorFontColor3B));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getAnchorTextGlowColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextGlowColor3B");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextGlowColor3B));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getAnchorTextOutlineColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextOutlineColor3B");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextOutlineColor3B));
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
int lua_cocos2d_ui_RichText_getAnchorTextShadowColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextShadowColor3B");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextShadowColor3B));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getAnchorTextShadowOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getAnchorTextShadowOffset");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getAnchorTextShadowOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getDefaults(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getDefaults");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ValueMap(cocos2d::ui::RichText::*)()const>(&cocos2d::ui::RichText::getDefaults));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getFontColor");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getFontColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_getFontColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:getFontColor3B");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocos2d::ui::RichText::*)()>(&cocos2d::ui::RichText::getFontColor3B));
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
int lua_cocos2d_ui_RichText_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:initWithXML");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::RichText::*)(std::string_view, const cocos2d::ValueMap&, const cocos2d::ui::RichText::OpenUrlHandler&)>(&cocos2d::ui::RichText::initWithXML)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::ui::RichText* obj,std::string_view arg0,const cocos2d::ValueMap& arg1){{return obj->initWithXML(std::move(arg0),arg1);}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_ui_RichText_insertElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:insertElement");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichElement*, int)>(&cocos2d::ui::RichText::insertElement)));
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
int lua_cocos2d_ui_RichText_removeElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:removeElement");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RichText::*)(cocos2d::ui::RichElement*)>(&cocos2d::ui::RichText::removeElement));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RichText::*)(int)>(&cocos2d::ui::RichText::removeElement));
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
int lua_cocos2d_ui_RichText_setAnchorTextGlow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextGlow");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::RichText::*)(bool, const cocos2d::Color3B&)>(&cocos2d::ui::RichText::setAnchorTextGlow)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::RichText* obj,bool arg0){{return obj->setAnchorTextGlow(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_RichText_setAnchorTextItalic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextItalic");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextItalic));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setAnchorTextOutline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextOutline");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::RichText::*)(bool, const cocos2d::Color3B&, int)>(&cocos2d::ui::RichText::setAnchorTextOutline)));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::RichText* obj,bool arg0,const cocos2d::Color3B& arg1){{return obj->setAnchorTextOutline(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::RichText* obj,bool arg0){{return obj->setAnchorTextOutline(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_ui_RichText_setAnchorTextShadow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextShadow");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ui::RichText::*)(bool, const cocos2d::Color3B&, const cocos2d::Vec2&, int)>(&cocos2d::ui::RichText::setAnchorTextShadow)));
	LUA_TRY_INVOKE(3, ([](cocos2d::ui::RichText* obj,bool arg0,const cocos2d::Color3B& arg1,const cocos2d::Vec2& arg2){{return obj->setAnchorTextShadow(std::move(arg0),arg1,arg2);}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::RichText* obj,bool arg0,const cocos2d::Color3B& arg1){{return obj->setAnchorTextShadow(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::RichText* obj,bool arg0){{return obj->setAnchorTextShadow(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_ui_RichText_setAnchorTextUnderline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setAnchorTextUnderline");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(bool)>(&cocos2d::ui::RichText::setAnchorTextUnderline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_setDefaults(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:setDefaults");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RichText::*)(const cocos2d::ValueMap&)>(&cocos2d::ui::RichText::setDefaults));
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
int lua_cocos2d_ui_RichText_stringWithColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:stringWithColor3B");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::ui::RichText::*)(const cocos2d::Color3B&)>(&cocos2d::ui::RichText::stringWithColor3B));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_stringWithColor4B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichText", "ccui.RichText:stringWithColor4B");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::ui::RichText::*)(const cocos2d::Color4B&)>(&cocos2d::ui::RichText::stringWithColor4B));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichText_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichText", "ccui.RichText:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RichText*(*)()>(&cocos2d::ui::RichText::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RichText_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichText", "ccui.RichText:createWithXML");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::RichText*(*)(std::string_view, const cocos2d::ValueMap&, const cocos2d::ui::RichText::OpenUrlHandler&)>(&cocos2d::ui::RichText::createWithXML)));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,const cocos2d::ValueMap& arg1){{return cocos2d::ui::RichText::createWithXML(std::move(arg0),arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_UI_ccuiRichText(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RichText, "RichText", "ccui.RichText",
		cocos2d::ui::RichText, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("color3BWithString", lua_cocos2d_ui_RichText_color3BWithString);
	LUA_METHOD("formatText", lua_cocos2d_ui_RichText_formatText);
	LUA_METHOD("getAnchorFontColor", lua_cocos2d_ui_RichText_getAnchorFontColor);
	LUA_METHOD("getAnchorFontColor3B", lua_cocos2d_ui_RichText_getAnchorFontColor3B);
	LUA_METHOD("getAnchorTextGlowColor3B", lua_cocos2d_ui_RichText_getAnchorTextGlowColor3B);
	LUA_METHOD("getAnchorTextOutlineColor3B", lua_cocos2d_ui_RichText_getAnchorTextOutlineColor3B);
	LUA_METHOD("getAnchorTextOutlineSize", lua_cocos2d_ui_RichText_getAnchorTextOutlineSize);
	LUA_METHOD("getAnchorTextShadowBlurRadius", lua_cocos2d_ui_RichText_getAnchorTextShadowBlurRadius);
	LUA_METHOD("getAnchorTextShadowColor3B", lua_cocos2d_ui_RichText_getAnchorTextShadowColor3B);
	LUA_METHOD("getAnchorTextShadowOffset", lua_cocos2d_ui_RichText_getAnchorTextShadowOffset);
	LUA_METHOD("getDefaults", lua_cocos2d_ui_RichText_getDefaults);
	LUA_METHOD("getFontColor", lua_cocos2d_ui_RichText_getFontColor);
	LUA_METHOD("getFontColor3B", lua_cocos2d_ui_RichText_getFontColor3B);
	LUA_METHOD("getFontFace", lua_cocos2d_ui_RichText_getFontFace);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_RichText_getFontSize);
	LUA_METHOD("getHorizontalAlignment", lua_cocos2d_ui_RichText_getHorizontalAlignment);
	LUA_METHOD("getWrapMode", lua_cocos2d_ui_RichText_getWrapMode);
	LUA_METHOD("initWithXML", lua_cocos2d_ui_RichText_initWithXML);
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
	LUA_METHOD("removeElement", lua_cocos2d_ui_RichText_removeElement);
	LUA_METHOD("setAnchorFontColor", lua_cocos2d_ui_RichText_setAnchorFontColor);
	LUA_METHOD("setAnchorTextBold", lua_cocos2d_ui_RichText_setAnchorTextBold);
	LUA_METHOD("setAnchorTextDel", lua_cocos2d_ui_RichText_setAnchorTextDel);
	LUA_METHOD("setAnchorTextGlow", lua_cocos2d_ui_RichText_setAnchorTextGlow);
	LUA_METHOD("setAnchorTextItalic", lua_cocos2d_ui_RichText_setAnchorTextItalic);
	LUA_METHOD("setAnchorTextOutline", lua_cocos2d_ui_RichText_setAnchorTextOutline);
	LUA_METHOD("setAnchorTextShadow", lua_cocos2d_ui_RichText_setAnchorTextShadow);
	LUA_METHOD("setAnchorTextUnderline", lua_cocos2d_ui_RichText_setAnchorTextUnderline);
	LUA_METHOD("setDefaults", lua_cocos2d_ui_RichText_setDefaults);
	LUA_METHOD("setFontColor", lua_cocos2d_ui_RichText_setFontColor);
	LUA_METHOD("setFontFace", lua_cocos2d_ui_RichText_setFontFace);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_RichText_setFontSize);
	LUA_METHOD("setHorizontalAlignment", lua_cocos2d_ui_RichText_setHorizontalAlignment);
	LUA_METHOD("setVerticalSpace", lua_cocos2d_ui_RichText_setVerticalSpace);
	LUA_METHOD("setWrapMode", lua_cocos2d_ui_RichText_setWrapMode);
	LUA_METHOD("stringWithColor3B", lua_cocos2d_ui_RichText_stringWithColor3B);
	LUA_METHOD("stringWithColor4B", lua_cocos2d_ui_RichText_stringWithColor4B);
	LUA_METHOD("create", lua_cocos2d_ui_RichText_create);
	LUA_METHOD("createWithXML", lua_cocos2d_ui_RichText_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_HBox_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.HBox", "ccui.HBox:initWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ui::HBox::*)(const cocos2d::Vec2&)>(&cocos2d::ui::HBox::initWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_HBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.HBox", "ccui.HBox:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::HBox*(*)(const cocos2d::Vec2&)>(&cocos2d::ui::HBox::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::HBox*(*)()>(&cocos2d::ui::HBox::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_UI_ccuiHBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::HBox, "HBox", "ccui.HBox",
		cocos2d::ui::HBox, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("initWithSize", lua_cocos2d_ui_HBox_initWithSize);
	LUA_METHOD("create", lua_cocos2d_ui_HBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_VBox_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VBox", "ccui.VBox:initWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ui::VBox::*)(const cocos2d::Vec2&)>(&cocos2d::ui::VBox::initWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.VBox", "ccui.VBox:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::VBox*(*)(const cocos2d::Vec2&)>(&cocos2d::ui::VBox::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::VBox*(*)()>(&cocos2d::ui::VBox::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_UI_ccuiVBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::VBox, "VBox", "ccui.VBox",
		cocos2d::ui::VBox, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("initWithSize", lua_cocos2d_ui_VBox_initWithSize);
	LUA_METHOD("create", lua_cocos2d_ui_VBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RelativeBox_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeBox", "ccui.RelativeBox:initWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ui::RelativeBox::*)(const cocos2d::Vec2&)>(&cocos2d::ui::RelativeBox::initWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RelativeBox", "ccui.RelativeBox:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::RelativeBox*(*)(const cocos2d::Vec2&)>(&cocos2d::ui::RelativeBox::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RelativeBox*(*)()>(&cocos2d::ui::RelativeBox::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_UI_ccuiRelativeBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RelativeBox, "RelativeBox", "ccui.RelativeBox",
		cocos2d::ui::RelativeBox, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("initWithSize", lua_cocos2d_ui_RelativeBox_initWithSize);
	LUA_METHOD("create", lua_cocos2d_ui_RelativeBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Scale9Sprite_copyTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:copyTo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::ui::Scale9Sprite*)const>(&cocos2d::ui::Scale9Sprite::copyTo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_getCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getCapInsets");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getCapInsets));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_ui_Scale9Sprite_getOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getOriginalSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getOriginalSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Scale9Sprite_getPreferredSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:getPreferredSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::Scale9Sprite::*)()const>(&cocos2d::ui::Scale9Sprite::getPreferredSize));
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
int lua_cocos2d_ui_Scale9Sprite_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:init");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::Sprite*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::init)));
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::Sprite*, const cocos2d::Rect&, bool, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::init)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::Sprite*, const cocos2d::Rect&, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::init)));
	LUA_INVOKE_FOOTER("3,4,6");
}
int lua_cocos2d_ui_Scale9Sprite_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:initWithFile");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(std::string_view, const cocos2d::Rect&, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::initWithFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(const cocos2d::Rect&, std::string_view)>(&cocos2d::ui::Scale9Sprite::initWithFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::initWithFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(std::string_view, cocos2d::PixelFormat)>(&cocos2d::ui::Scale9Sprite::initWithFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_ui_Scale9Sprite_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::SpriteFrame*, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::initWithSpriteFrame)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Scale9Sprite_initWithSpriteFrameName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:initWithSpriteFrameName");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::initWithSpriteFrameName)));
	LUA_INVOKE_FOOTER("2");
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
int lua_cocos2d_ui_Scale9Sprite_resizableSpriteWithCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:resizableSpriteWithCapInsets");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Scale9Sprite*(cocos2d::ui::Scale9Sprite::*)(const cocos2d::Rect&)const>(&cocos2d::ui::Scale9Sprite::resizableSpriteWithCapInsets));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setCapInsets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::setCapInsets));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_Scale9Sprite_setPreferredSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setPreferredSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(const cocos2d::Vec2&)>(&cocos2d::ui::Scale9Sprite::setPreferredSize));
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
int lua_cocos2d_ui_Scale9Sprite_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setSpriteFrame");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::SpriteFrame*, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::setSpriteFrame)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Scale9Sprite_setState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:setState");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Scale9Sprite::*)(cocos2d::ui::Scale9Sprite::State)>(&cocos2d::ui::Scale9Sprite::setState));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Scale9Sprite_updateWithSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:updateWithSprite");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::Sprite*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::updateWithSprite)));
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ui::Scale9Sprite::*)(cocos2d::Sprite*, const cocos2d::Rect&, bool, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::updateWithSprite)));
	LUA_INVOKE_FOOTER("4,6");
}
int lua_cocos2d_ui_Scale9Sprite_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ui::Scale9Sprite*(*)(std::string_view, const cocos2d::Rect&, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::ui::Scale9Sprite*(*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::ui::Scale9Sprite*(*)(const cocos2d::Rect&, std::string_view)>(&cocos2d::ui::Scale9Sprite::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Scale9Sprite*(*)(std::string_view)>(&cocos2d::ui::Scale9Sprite::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Scale9Sprite*(*)()>(&cocos2d::ui::Scale9Sprite::create));
	LUA_SINVOKE_FOOTER("0,1,2,3");
}
int lua_cocos2d_ui_Scale9Sprite_createWithSpriteFrame(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:createWithSpriteFrame");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Scale9Sprite*(*)(cocos2d::SpriteFrame*, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::createWithSpriteFrame)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Scale9Sprite*(*)(cocos2d::SpriteFrame*)>(&cocos2d::ui::Scale9Sprite::createWithSpriteFrame));
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Scale9Sprite_createWithSpriteFrameName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Scale9Sprite", "ccui.Scale9Sprite:createWithSpriteFrameName");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ui::Scale9Sprite*(*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::ui::Scale9Sprite::createWithSpriteFrameName)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Scale9Sprite*(*)(std::string_view)>(&cocos2d::ui::Scale9Sprite::createWithSpriteFrameName));
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_UI_ccuiScale9Sprite(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Scale9Sprite, "Scale9Sprite", "ccui.Scale9Sprite",
		cocos2d::ui::Scale9Sprite, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("copyTo", lua_cocos2d_ui_Scale9Sprite_copyTo);
	LUA_METHOD("getCapInsets", lua_cocos2d_ui_Scale9Sprite_getCapInsets);
	LUA_METHOD("getInsetBottom", lua_cocos2d_ui_Scale9Sprite_getInsetBottom);
	LUA_METHOD("getInsetLeft", lua_cocos2d_ui_Scale9Sprite_getInsetLeft);
	LUA_METHOD("getInsetRight", lua_cocos2d_ui_Scale9Sprite_getInsetRight);
	LUA_METHOD("getInsetTop", lua_cocos2d_ui_Scale9Sprite_getInsetTop);
	LUA_METHOD("getOriginalSize", lua_cocos2d_ui_Scale9Sprite_getOriginalSize);
	LUA_METHOD("getPreferredSize", lua_cocos2d_ui_Scale9Sprite_getPreferredSize);
	LUA_METHOD("getRenderingType", lua_cocos2d_ui_Scale9Sprite_getRenderingType);
	LUA_METHOD("getSprite", lua_cocos2d_ui_Scale9Sprite_getSprite);
	LUA_METHOD("getState", lua_cocos2d_ui_Scale9Sprite_getState);
	LUA_METHOD("init", lua_cocos2d_ui_Scale9Sprite_init);
	LUA_METHOD("initWithFile", lua_cocos2d_ui_Scale9Sprite_initWithFile);
	LUA_METHOD("initWithSpriteFrame", lua_cocos2d_ui_Scale9Sprite_initWithSpriteFrame);
	LUA_METHOD("initWithSpriteFrameName", lua_cocos2d_ui_Scale9Sprite_initWithSpriteFrameName);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_Scale9Sprite_isScale9Enabled);
	LUA_METHOD("resetRender", lua_cocos2d_ui_Scale9Sprite_resetRender);
	LUA_METHOD("resizableSpriteWithCapInsets", lua_cocos2d_ui_Scale9Sprite_resizableSpriteWithCapInsets);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_Scale9Sprite_setCapInsets);
	LUA_METHOD("setInsetBottom", lua_cocos2d_ui_Scale9Sprite_setInsetBottom);
	LUA_METHOD("setInsetLeft", lua_cocos2d_ui_Scale9Sprite_setInsetLeft);
	LUA_METHOD("setInsetRight", lua_cocos2d_ui_Scale9Sprite_setInsetRight);
	LUA_METHOD("setInsetTop", lua_cocos2d_ui_Scale9Sprite_setInsetTop);
	LUA_METHOD("setPreferredSize", lua_cocos2d_ui_Scale9Sprite_setPreferredSize);
	LUA_METHOD("setRenderingType", lua_cocos2d_ui_Scale9Sprite_setRenderingType);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_Scale9Sprite_setScale9Enabled);
	LUA_METHOD("setSpriteFrame", lua_cocos2d_ui_Scale9Sprite_setSpriteFrame);
	LUA_METHOD("setState", lua_cocos2d_ui_Scale9Sprite_setState);
	LUA_METHOD("updateWithSprite", lua_cocos2d_ui_Scale9Sprite_updateWithSprite);
	LUA_METHOD("create", lua_cocos2d_ui_Scale9Sprite_create);
	LUA_METHOD("createWithSpriteFrame", lua_cocos2d_ui_Scale9Sprite_createWithSpriteFrame);
	LUA_METHOD("createWithSpriteFrameName", lua_cocos2d_ui_Scale9Sprite_createWithSpriteFrameName);
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
int lua_cocos2d_ui_EditBox_getCapInsetsDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getCapInsetsDisabledRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getCapInsetsDisabledRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getCapInsetsNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getCapInsetsNormalRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getCapInsetsNormalRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getCapInsetsPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getCapInsetsPressedRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getCapInsetsPressedRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_getFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getFontColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getFontColor));
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
int lua_cocos2d_ui_EditBox_getPlaceholderFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:getPlaceholderFontColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::getPlaceholderFontColor));
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
int lua_cocos2d_ui_EditBox_initWithSizeAndBackgroundSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:initWithSizeAndBackgroundSprite");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ui::EditBox::*)(const cocos2d::Size&, cocos2d::ui::Scale9Sprite*, cocos2d::ui::Scale9Sprite*, cocos2d::ui::Scale9Sprite*)>(&cocos2d::ui::EditBox::initWithSizeAndBackgroundSprite)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ui::EditBox::*)(const cocos2d::Size&, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::initWithSizeAndBackgroundSprite)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::ui::EditBox::*)(const cocos2d::Size&, cocos2d::ui::Scale9Sprite*)>(&cocos2d::ui::EditBox::initWithSizeAndBackgroundSprite)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cocos2d::ui::EditBox* obj,const cocos2d::Size& arg0,std::string_view arg1){{return obj->initWithSizeAndBackgroundSprite(arg0,std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ui_EditBox_initWithSizeAndTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:initWithSizeAndTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::ui::EditBox::*)(const cocos2d::Size&, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::initWithSizeAndTexture)));
	LUA_TRY_INVOKE_R(4, ([](cocos2d::ui::EditBox* obj,const cocos2d::Size& arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3){{return obj->initWithSizeAndTexture(arg0,std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::ui::EditBox* obj,const cocos2d::Size& arg0,std::string_view arg1,std::string_view arg2){{return obj->initWithSizeAndTexture(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::ui::EditBox* obj,const cocos2d::Size& arg0,std::string_view arg1){{return obj->initWithSizeAndTexture(arg0,std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4,5");
}
int lua_cocos2d_ui_EditBox_loadTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextureDisabled");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextureDisabled)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTextureDisabled(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextureNormal");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextureNormal)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTextureNormal(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTexturePressed");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTexturePressed)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::EditBox* obj,std::string_view arg0){{return obj->loadTexturePressed(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_EditBox_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:loadTextures");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ui::EditBox::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::loadTextures)));
	LUA_TRY_INVOKE(3, ([](cocos2d::ui::EditBox* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::EditBox* obj,std::string_view arg0,std::string_view arg1){{return obj->loadTextures(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ui_EditBox_openKeyboard(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:openKeyboard");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::EditBox::*)()const>(&cocos2d::ui::EditBox::openKeyboard));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_EditBox_registerScriptEditBoxHandler_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:registerScriptEditBoxHandler");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::ui::EditBox::ScriptEditBoxCallback&)>(&cocos2d::ui::EditBox::setScriptEditBoxCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setCapInsets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Rect&)>(&cocos2d::ui::EditBox::setCapInsets));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setCapInsetsDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setCapInsetsDisabledRenderer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Rect&)>(&cocos2d::ui::EditBox::setCapInsetsDisabledRenderer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setCapInsetsNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setCapInsetsNormalRenderer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Rect&)>(&cocos2d::ui::EditBox::setCapInsetsNormalRenderer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setCapInsetsPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setCapInsetsPressedRenderer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Rect&)>(&cocos2d::ui::EditBox::setCapInsetsPressedRenderer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_EditBox_setFont(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setFont");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::EditBox::*)(const char*, int)>(&cocos2d::ui::EditBox::setFont)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_EditBox_setFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setFontColor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Color4B&)>(&cocos2d::ui::EditBox::setFontColor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Color3B&)>(&cocos2d::ui::EditBox::setFontColor));
	LUA_INVOKE_FOOTER("1");
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::EditBox::*)(const char*, int)>(&cocos2d::ui::EditBox::setPlaceholderFont)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_EditBox_setPlaceholderFontColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:setPlaceholderFontColor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Color4B&)>(&cocos2d::ui::EditBox::setPlaceholderFontColor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::EditBox::*)(const cocos2d::Color3B&)>(&cocos2d::ui::EditBox::setPlaceholderFontColor));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_ui_EditBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.EditBox", "ccui.EditBox:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::ui::EditBox*(*)(const cocos2d::Size&, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](const cocos2d::Size& arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3){{return cocos2d::ui::EditBox::create(arg0,std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cocos2d::ui::EditBox*(*)(const cocos2d::Size&, cocos2d::ui::Scale9Sprite*, cocos2d::ui::Scale9Sprite*, cocos2d::ui::Scale9Sprite*)>(&cocos2d::ui::EditBox::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](const cocos2d::Size& arg0,std::string_view arg1,std::string_view arg2){{return cocos2d::ui::EditBox::create(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<cocos2d::ui::EditBox*(*)(const cocos2d::Size&, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::EditBox::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](const cocos2d::Size& arg0,cocos2d::ui::Scale9Sprite* arg1,cocos2d::ui::Scale9Sprite* arg2){{return cocos2d::ui::EditBox::create(arg0,arg1,arg2);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](const cocos2d::Size& arg0,std::string_view arg1){{return cocos2d::ui::EditBox::create(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](const cocos2d::Size& arg0,cocos2d::ui::Scale9Sprite* arg1){{return cocos2d::ui::EditBox::create(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3,4,5");
}
int luaReg_UI_ccuiEditBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::EditBox, "EditBox", "ccui.EditBox",
		cocos2d::ui::EditBox, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("closeKeyboard", lua_cocos2d_ui_EditBox_closeKeyboard);
	LUA_METHOD("getCapInsetsDisabledRenderer", lua_cocos2d_ui_EditBox_getCapInsetsDisabledRenderer);
	LUA_METHOD("getCapInsetsNormalRenderer", lua_cocos2d_ui_EditBox_getCapInsetsNormalRenderer);
	LUA_METHOD("getCapInsetsPressedRenderer", lua_cocos2d_ui_EditBox_getCapInsetsPressedRenderer);
	LUA_METHOD("getFontColor", lua_cocos2d_ui_EditBox_getFontColor);
	LUA_METHOD("getFontName", lua_cocos2d_ui_EditBox_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_EditBox_getFontSize);
	LUA_METHOD("getInputFlag", lua_cocos2d_ui_EditBox_getInputFlag);
	LUA_METHOD("getInputMode", lua_cocos2d_ui_EditBox_getInputMode);
	LUA_METHOD("getMaxLength", lua_cocos2d_ui_EditBox_getMaxLength);
	LUA_METHOD("getPlaceHolder", lua_cocos2d_ui_EditBox_getPlaceHolder);
	LUA_METHOD("getPlaceholderFontColor", lua_cocos2d_ui_EditBox_getPlaceholderFontColor);
	LUA_METHOD("getPlaceholderFontName", lua_cocos2d_ui_EditBox_getPlaceholderFontName);
	LUA_METHOD("getPlaceholderFontSize", lua_cocos2d_ui_EditBox_getPlaceholderFontSize);
	LUA_METHOD("getReturnType", lua_cocos2d_ui_EditBox_getReturnType);
	LUA_METHOD("getText", lua_cocos2d_ui_EditBox_getText);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_EditBox_getTextHorizontalAlignment);
	LUA_METHOD("initWithSizeAndBackgroundSprite", lua_cocos2d_ui_EditBox_initWithSizeAndBackgroundSprite);
	LUA_METHOD("initWithSizeAndTexture", lua_cocos2d_ui_EditBox_initWithSizeAndTexture);
	LUA_METHOD("loadTextureDisabled", lua_cocos2d_ui_EditBox_loadTextureDisabled);
	LUA_METHOD("loadTextureNormal", lua_cocos2d_ui_EditBox_loadTextureNormal);
	LUA_METHOD("loadTexturePressed", lua_cocos2d_ui_EditBox_loadTexturePressed);
	LUA_METHOD("loadTextures", lua_cocos2d_ui_EditBox_loadTextures);
	LUA_METHOD("openKeyboard", lua_cocos2d_ui_EditBox_openKeyboard);
	LUA_METHOD("registerScriptEditBoxHandler", lua_cocos2d_ui_EditBox_registerScriptEditBoxHandler_1);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_EditBox_setCapInsets);
	LUA_METHOD("setCapInsetsDisabledRenderer", lua_cocos2d_ui_EditBox_setCapInsetsDisabledRenderer);
	LUA_METHOD("setCapInsetsNormalRenderer", lua_cocos2d_ui_EditBox_setCapInsetsNormalRenderer);
	LUA_METHOD("setCapInsetsPressedRenderer", lua_cocos2d_ui_EditBox_setCapInsetsPressedRenderer);
	LUA_METHOD("setFont", lua_cocos2d_ui_EditBox_setFont);
	LUA_METHOD("setFontColor", lua_cocos2d_ui_EditBox_setFontColor);
	LUA_METHOD("setFontName", lua_cocos2d_ui_EditBox_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_ui_EditBox_setFontSize);
	LUA_METHOD("setInputFlag", lua_cocos2d_ui_EditBox_setInputFlag);
	LUA_METHOD("setInputMode", lua_cocos2d_ui_EditBox_setInputMode);
	LUA_METHOD("setMaxLength", lua_cocos2d_ui_EditBox_setMaxLength);
	LUA_METHOD("setPlaceHolder", lua_cocos2d_ui_EditBox_setPlaceHolder);
	LUA_METHOD("setPlaceholderFont", lua_cocos2d_ui_EditBox_setPlaceholderFont);
	LUA_METHOD("setPlaceholderFontColor", lua_cocos2d_ui_EditBox_setPlaceholderFontColor);
	LUA_METHOD("setPlaceholderFontName", lua_cocos2d_ui_EditBox_setPlaceholderFontName);
	LUA_METHOD("setPlaceholderFontSize", lua_cocos2d_ui_EditBox_setPlaceholderFontSize);
	LUA_METHOD("setReturnType", lua_cocos2d_ui_EditBox_setReturnType);
	LUA_METHOD("setText", lua_cocos2d_ui_EditBox_setText);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_EditBox_setTextHorizontalAlignment);
	LUA_METHOD("create", lua_cocos2d_ui_EditBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
