#include "cclua_ui_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"

int lua_cocos2d_ui_ScrollView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::ui::ScrollView::ccScrollViewCallback&)>(&cocos2d::ui::ScrollView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getDirection");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getInnerContainer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getInnerContainer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getInnerContainerPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainerPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getInnerContainerPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getInnerContainerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getInnerContainerSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getInnerContainerSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarAutoHideTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarAutoHideTime");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarAutoHideTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarOpacity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarPositionFromCornerForHorizontal");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForHorizontal);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarPositionFromCornerForVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarPositionFromCornerForVertical");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForVertical);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrollBarWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrollBarWidth");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrollBarWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentBothDirection");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrolledPercentBothDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentHorizontal");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrolledPercentHorizontal);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getScrolledPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getScrolledPercentVertical");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getScrolledPercentVertical);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_getTouchTotalTimeThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:getTouchTotalTimeThreshold");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::getTouchTotalTimeThreshold);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isAutoScrolling(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isAutoScrolling");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isAutoScrolling);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isBounceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isBounceEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isBounceEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isInertiaScrollEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isInertiaScrollEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isInertiaScrollEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrollBarAutoHideEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrollBarAutoHideEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isScrollBarAutoHideEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrollBarEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrollBarEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isScrollBarEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_isScrolling(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:isScrolling");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::isScrolling);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottom");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToBottom);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottomLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottomLeft");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToBottomLeft);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToBottomRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToBottomRight");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToBottomRight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToLeft");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToLeft);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentBothDirection");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::jumpToPercentBothDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_jumpToPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentHorizontal");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::jumpToPercentHorizontal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_jumpToPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToPercentVertical");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::jumpToPercentVertical);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_jumpToRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToRight");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToRight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTop");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToTop);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTopLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTopLeft");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToTopLeft);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_jumpToTopRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:jumpToTopRight");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::jumpToTopRight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_scrollToBottom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottom");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToBottom);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomLeft");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToBottomLeft);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToBottomRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToBottomRight");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToBottomRight);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToLeft");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToLeft);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentBothDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentBothDirection");
	LUA_TRY_INVOKE(3, &cocos2d::ui::ScrollView::scrollToPercentBothDirection);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentHorizontal");
	LUA_TRY_INVOKE(3, &cocos2d::ui::ScrollView::scrollToPercentHorizontal);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToPercentVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToPercentVertical");
	LUA_TRY_INVOKE(3, &cocos2d::ui::ScrollView::scrollToPercentVertical);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ScrollView_scrollToRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToRight");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToRight);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTop");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToTop);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopLeft(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopLeft");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToTopLeft);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_scrollToTopRight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:scrollToTopRight");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ScrollView::scrollToTopRight);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ScrollView_setBounceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setBounceEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setBounceEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setDirection");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setInertiaScrollEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInertiaScrollEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setInertiaScrollEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setInnerContainerPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInnerContainerPosition");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setInnerContainerPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setInnerContainerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setInnerContainerSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setInnerContainerSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarAutoHideEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarAutoHideEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarAutoHideEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarAutoHideTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarAutoHideTime");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarAutoHideTime);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarOpacity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCorner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCorner");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarPositionFromCorner);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCornerForHorizontal");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForHorizontal);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarPositionFromCornerForVertical(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarPositionFromCornerForVertical");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForVertical);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setScrollBarWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setScrollBarWidth");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setScrollBarWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_setTouchTotalTimeThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:setTouchTotalTimeThreshold");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ScrollView::setTouchTotalTimeThreshold);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ScrollView_stopAutoScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopAutoScroll");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::stopAutoScroll);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_stopOverallScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopOverallScroll");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::stopOverallScroll);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_stopScroll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:stopScroll");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ScrollView::stopScroll);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ScrollView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ScrollView::createInstance);
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
	LUA_TRY_INVOKE(0, &cocos2d::ui::ListView::doLayout);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getBottomPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getBottomPadding");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getBottomPadding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getBottommostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getBottommostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getBottommostItemInCurrentView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getCenterItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getCenterItemInCurrentView");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getCenterItemInCurrentView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getClosestItemToPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getClosestItemToPosition");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::ListView::getClosestItemToPosition);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_getClosestItemToPositionInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getClosestItemToPositionInCurrentView");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::ListView::getClosestItemToPositionInCurrentView);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_getCurSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getCurSelectedIndex");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getCurSelectedIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getIndex");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::ListView::getIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_getItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItem");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::ListView::getItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_getItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItems");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getItems);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getItemsMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getItemsMargin");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getItemsMargin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getLeftPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getLeftPadding");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getLeftPadding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getLeftmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getLeftmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getLeftmostItemInCurrentView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getMagneticAllowedOutOfBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getMagneticAllowedOutOfBoundary");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getMagneticAllowedOutOfBoundary);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getMagneticType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getMagneticType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getMagneticType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getRightPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getRightPadding");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getRightPadding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getRightmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getRightmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getRightmostItemInCurrentView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getScrollDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getScrollDuration");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getScrollDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getTopPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getTopPadding");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getTopPadding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_getTopmostItemInCurrentView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:getTopmostItemInCurrentView");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::getTopmostItemInCurrentView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_insertCustomItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:insertCustomItem");
	LUA_TRY_INVOKE(2, &cocos2d::ui::ListView::insertCustomItem);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_ListView_insertDefaultItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:insertDefaultItem");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::insertDefaultItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_jumpToItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:jumpToItem");
	LUA_TRY_INVOKE(3, &cocos2d::ui::ListView::jumpToItem);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_ListView_pushBackCustomItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:pushBackCustomItem");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::pushBackCustomItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_pushBackDefaultItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:pushBackDefaultItem");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ListView::pushBackDefaultItem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_removeAllItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeAllItems");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ListView::removeAllItems);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_removeItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeItem");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::removeItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_removeLastItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeLastItem");
	LUA_TRY_INVOKE(0, &cocos2d::ui::ListView::removeLastItem);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setBottomPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setCurSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setCurSelectedIndex");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setCurSelectedIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setGravity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setGravity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setItemModel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setItemModel");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setItemModel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setItemsMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setItemsMargin");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setItemsMargin);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setLeftPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setLeftPadding");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setLeftPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setMagneticAllowedOutOfBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setMagneticAllowedOutOfBoundary");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setMagneticAllowedOutOfBoundary);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setMagneticType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setMagneticType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setMagneticType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setPadding");
	LUA_TRY_INVOKE(4, &cocos2d::ui::ListView::setPadding);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ui_ListView_setRightPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setRightPadding");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setRightPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setScrollDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setScrollDuration");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setScrollDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_setTopPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:setTopPadding");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ListView::setTopPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ListView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ListView", "ccui.ListView:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ListView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ListView", "ccui.ListView:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ListView::createInstance);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::addEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_getBackFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBackFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getBackFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallDisabledFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallDisabledFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getBallDisabledFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallNormalFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallNormalFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getBallNormalFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getBallPressedFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getBallPressedFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getBallPressedFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getCapInsetsBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getCapInsetsBarRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getCapInsetsBarRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getCapInsetsProgressBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getCapInsetsProgressBarRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getCapInsetsProgressBarRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getMaxPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getMaxPercent");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getMaxPercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getPercent");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getPercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getProgressBarFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getProgressBarFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getProgressBarFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallDisabledRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getSlidBallDisabledRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallNormalRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getSlidBallNormalRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallPressedRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getSlidBallPressedRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getSlidBallRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getSlidBallRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getSlidBallRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:getZoomScale");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::getZoomScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::isScale9Enabled);
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
	LUA_TRY_INVOKE(4, &cocos2d::ui::Slider::loadSlidBallTextures);
	LUA_TRY_INVOKE(3, ([](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextures(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_ui_Slider_setCapInsetProgressBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsetProgressBarRenderer");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setCapInsetProgressBarRenderer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsets");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setCapInsets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setCapInsetsBarRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setCapInsetsBarRenderer");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setCapInsetsBarRenderer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setMaxPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setMaxPercent");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setMaxPercent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setPercent");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setPercent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setScale9Enabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setScale9Enabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:setZoomScale");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Slider::setZoomScale);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Slider_updateVisualSlider(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:updateVisualSlider");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Slider::updateVisualSlider);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Slider_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Slider", "ccui.Slider:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::Slider>(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::create)));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::Slider::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::Slider>(*)()>(&cocos2d::ui::Slider::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cocos2d_ui_Slider_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Slider", "ccui.Slider:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Slider::createInstance);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::addEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_attachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:attachWithIME");
	LUA_TRY_INVOKE(0, &cocos2d::ui::TextField::attachWithIME);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_detachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:detachWithIME");
	LUA_TRY_INVOKE(0, &cocos2d::ui::TextField::detachWithIME);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_didNotSelectSelf(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:didNotSelectSelf");
	LUA_TRY_INVOKE(0, &cocos2d::ui::TextField::didNotSelectSelf);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getAttachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getAttachWithIME");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getAttachWithIME);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getAutoRenderSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getAutoRenderSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getAutoRenderSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getDeleteBackward(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getDeleteBackward");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getDeleteBackward);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getDetachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getDetachWithIME");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getDetachWithIME);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getFontName");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getFontName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getFontSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getInsertText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getInsertText");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getInsertText);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getMaxLength");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getMaxLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPasswordStyleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPasswordStyleText");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getPasswordStyleText);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPlaceHolder");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getPlaceHolder);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getPlaceHolderColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getPlaceHolderColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getPlaceHolderColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getString");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getStringLength");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getStringLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getTextColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getTextHorizontalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTextVerticalAlignment");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getTextVerticalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_getTouchSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:getTouchSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::getTouchSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_isMaxLengthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:isMaxLengthEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::isMaxLengthEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_isPasswordEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:isPasswordEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::isPasswordEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextField_setAttachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setAttachWithIME");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setAttachWithIME);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setCursorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setCursorEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setCursorFromPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorFromPoint");
	LUA_TRY_INVOKE(2, &cocos2d::ui::TextField::setCursorFromPoint);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_TextField_setCursorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorPosition");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setCursorPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setDeleteBackward(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setDeleteBackward");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setDeleteBackward);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setDetachWithIME(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setDetachWithIME");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setDetachWithIME);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setFontName");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setFontName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setFontSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setFontSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setInsertText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setInsertText");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setInsertText);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setMaxLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setMaxLength");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setMaxLength);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setMaxLengthEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setMaxLengthEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setMaxLengthEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPasswordEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPasswordEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setPasswordEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPasswordStyleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPasswordStyleText");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setPasswordStyleText);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setPlaceHolder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setPlaceHolder");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setPlaceHolder);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextAreaSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTextAreaSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTextColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextHorizontalAlignment");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTextHorizontalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTextVerticalAlignment");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTextVerticalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTouchAreaEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTouchAreaEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTouchAreaEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_setTouchSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setTouchSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextField::setTouchSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextField_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextField", "ccui.TextField:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::TextField>(*)(std::string_view, std::string_view, int)>(&cocos2d::ui::TextField::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::TextField>(*)()>(&cocos2d::ui::TextField::create));
	LUA_SINVOKE_FOOTER("0,3");
}
int lua_cocos2d_ui_TextField_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextField", "ccui.TextField:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextField::createInstance);
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
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextBMFont::getRenderFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:getString");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextBMFont::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:getStringLength");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextBMFont::getStringLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_resetRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:resetRender");
	LUA_TRY_INVOKE(0, &cocos2d::ui::TextBMFont::resetRender);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextBMFont_setFntFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:setFntFile");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextBMFont::setFntFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextBMFont_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:setString");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextBMFont::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextBMFont_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::ui::TextBMFont>(*)(std::string_view, std::string_view)>(&cocos2d::ui::TextBMFont::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::TextBMFont>(*)()>(&cocos2d::ui::TextBMFont::create));
	LUA_SINVOKE_FOOTER("0,2");
}
int lua_cocos2d_ui_TextBMFont_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextBMFont", "ccui.TextBMFont:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextBMFont::createInstance);
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
int lua_cocos2d_ui_PageView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::ui::PageView::ccPageViewCallback&)>(&cocos2d::ui::PageView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_addPage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:addPage");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::addPage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_getCurrentPageIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getCurrentPageIndex");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getCurrentPageIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorIndexNodesColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesOpacity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorIndexNodesOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorIndexNodesScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorIndexNodesScale");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorIndexNodesScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorPositionAsAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorPositionAsAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorPositionAsAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSelectedIndexColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSelectedIndexColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorSelectedIndexColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSelectedIndexOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSelectedIndexOpacity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorSelectedIndexOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_getIndicatorSpaceBetweenIndexNodes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:getIndicatorSpaceBetweenIndexNodes");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::getIndicatorSpaceBetweenIndexNodes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_insertPage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:insertPage");
	LUA_TRY_INVOKE(2, &cocos2d::ui::PageView::insertPage);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_PageView_removeAllPages(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removeAllPages");
	LUA_TRY_INVOKE(0, &cocos2d::ui::PageView::removeAllPages);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_removePage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removePage");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::removePage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_removePageAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:removePageAtIndex");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::removePageAtIndex);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setAutoScrollStopEpsilon);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setCurrentPageIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setCurrentPageIndex");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setCurrentPageIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorIndexNodesColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesOpacity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorIndexNodesOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesScale");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorIndexNodesScale);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorIndexNodesTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorIndexNodesTexture");
	LUA_TRY_INVOKE(2, &cocos2d::ui::PageView::setIndicatorIndexNodesTexture);
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::PageView* obj,std::string_view arg0){{return obj->setIndicatorIndexNodesTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_PageView_setIndicatorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorPosition");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorPositionAsAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorPositionAsAnchorPoint");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorPositionAsAnchorPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSelectedIndexColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSelectedIndexColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorSelectedIndexColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSelectedIndexOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSelectedIndexOpacity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorSelectedIndexOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorSpaceBetweenIndexNodes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorSpaceBetweenIndexNodes");
	LUA_TRY_INVOKE(1, &cocos2d::ui::PageView::setIndicatorSpaceBetweenIndexNodes);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.PageView", "ccui.PageView:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_PageView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.PageView", "ccui.PageView:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::PageView::createInstance);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::Helper::changeLayoutSystemActiveState);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_convertBoundingBoxToScreen(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:convertBoundingBoxToScreen");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::Helper::convertBoundingBoxToScreen);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_doLayout(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:doLayout");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Helper::doLayout);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Helper_getSubStringOfUTF8String(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:getSubStringOfUTF8String");
	LUA_TRY_INVOKE_R(3, &cocos2d::ui::Helper::getSubStringOfUTF8String);
	LUA_SINVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Helper_restrictCapInsetRect(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:restrictCapInsetRect");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::Helper::restrictCapInsetRect);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekActionWidgetByActionTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekActionWidgetByActionTag");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::Helper::seekActionWidgetByActionTag);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByName");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::Helper::seekWidgetByName);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Helper_seekWidgetByTag(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Helper", "ccui.Helper:seekWidgetByTag");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::Helper::seekWidgetByTag);
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
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::RichElement::equalType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElement_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElement", "ccui.RichElement:init");
	LUA_TRY_INVOKE_R(3, &cocos2d::ui::RichElement::init);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_RichElement_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElement", "ccui.RichElement:setColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElement::setColor);
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
	LUA_TRY_INVOKE_R(14, &cocos2d::ui::RichElementText::init);
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
	LUA_TRY_INVOKE_R(14, &cocos2d::ui::RichElementText::create);
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
	LUA_TRY_INVOKE_R(6, &cocos2d::ui::RichElementImage::init);
	LUA_TRY_INVOKE_R(5, ([](cocos2d::ui::RichElementImage* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3,std::string_view arg4){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](cocos2d::ui::RichElementImage* obj,int arg0,const cocos2d::Color3B& arg1,uint8_t arg2,std::string_view arg3){{return obj->init(std::move(arg0),arg1,std::move(arg2),std::move(arg3));}}));
	LUA_INVOKE_FOOTER("4,5,6");
}
int lua_cocos2d_ui_RichElementImage_setHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setHeight");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScale");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setScale);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScaleX");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setScaleX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setScaleY");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setScaleY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setUrl(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setUrl");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setUrl);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_setWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:setWidth");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RichElementImage::setWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RichElementImage_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementImage", "ccui.RichElementImage:create");
	LUA_TRY_INVOKE_R(6, &cocos2d::ui::RichElementImage::create);
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
	LUA_TRY_INVOKE_R(4, &cocos2d::ui::RichElementCustomNode::init);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ui_RichElementCustomNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RichElementCustomNode", "ccui.RichElementCustomNode:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::ui::RichElementCustomNode::create);
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
	LUA_TRY_INVOKE_R(3, &cocos2d::ui::RichElementNewLine::create);
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
