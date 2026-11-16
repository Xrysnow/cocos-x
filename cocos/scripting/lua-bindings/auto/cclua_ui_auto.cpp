#include "cclua_ui_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"

int lua_cocos2d_ui_LayoutParameter_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LayoutParameter::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_copyProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:copyProperties");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LayoutParameter::copyProperties);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutParameter_createCloneInstance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:createCloneInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LayoutParameter::createCloneInstance);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_getLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:getLayoutType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LayoutParameter::getLayoutType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_getMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:getMargin");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LayoutParameter::getMargin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_setMargin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:setMargin");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LayoutParameter::setMargin);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LayoutParameter::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LayoutParameter, "LayoutParameter", "ccui.LayoutParameter",
		cocos2d::ui::LayoutParameter, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_ui_LayoutParameter_clone);
	LUA_METHOD("copyProperties", lua_cocos2d_ui_LayoutParameter_copyProperties);
	LUA_METHOD("createCloneInstance", lua_cocos2d_ui_LayoutParameter_createCloneInstance);
	LUA_METHOD("getLayoutType", lua_cocos2d_ui_LayoutParameter_getLayoutType);
	LUA_METHOD("getMargin", lua_cocos2d_ui_LayoutParameter_getMargin);
	LUA_METHOD("setMargin", lua_cocos2d_ui_LayoutParameter_setMargin);
	LUA_METHOD("create", lua_cocos2d_ui_LayoutParameter_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_LinearLayoutParameter_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:getGravity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LinearLayoutParameter::getGravity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LinearLayoutParameter_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:setGravity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LinearLayoutParameter::setGravity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LinearLayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LinearLayoutParameter::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLinearLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LinearLayoutParameter, "LinearLayoutParameter", "ccui.LinearLayoutParameter",
		cocos2d::ui::LinearLayoutParameter, "ccui.LayoutParameter",
		nullptr, nullptr);
	LUA_METHOD("getGravity", lua_cocos2d_ui_LinearLayoutParameter_getGravity);
	LUA_METHOD("setGravity", lua_cocos2d_ui_LinearLayoutParameter_setGravity);
	LUA_METHOD("create", lua_cocos2d_ui_LinearLayoutParameter_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RelativeLayoutParameter_getAlign(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:getAlign");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RelativeLayoutParameter::getAlign);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_getRelativeName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:getRelativeName");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RelativeLayoutParameter::getRelativeName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_getRelativeToWidgetName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:getRelativeToWidgetName");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RelativeLayoutParameter::getRelativeToWidgetName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setAlign(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setAlign");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RelativeLayoutParameter::setAlign);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setRelativeName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setRelativeName");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RelativeLayoutParameter::setRelativeName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setRelativeToWidgetName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setRelativeToWidgetName");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RelativeLayoutParameter::setRelativeToWidgetName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RelativeLayoutParameter::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRelativeLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RelativeLayoutParameter, "RelativeLayoutParameter", "ccui.RelativeLayoutParameter",
		cocos2d::ui::RelativeLayoutParameter, "ccui.LayoutParameter",
		nullptr, nullptr);
	LUA_METHOD("getAlign", lua_cocos2d_ui_RelativeLayoutParameter_getAlign);
	LUA_METHOD("getRelativeName", lua_cocos2d_ui_RelativeLayoutParameter_getRelativeName);
	LUA_METHOD("getRelativeToWidgetName", lua_cocos2d_ui_RelativeLayoutParameter_getRelativeToWidgetName);
	LUA_METHOD("setAlign", lua_cocos2d_ui_RelativeLayoutParameter_setAlign);
	LUA_METHOD("setRelativeName", lua_cocos2d_ui_RelativeLayoutParameter_setRelativeName);
	LUA_METHOD("setRelativeToWidgetName", lua_cocos2d_ui_RelativeLayoutParameter_setRelativeToWidgetName);
	LUA_METHOD("create", lua_cocos2d_ui_RelativeLayoutParameter_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Widget_addClickEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:addClickEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::addClickEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_addTouchEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:addTouchEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::addTouchEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_dispatchFocusEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:dispatchFocusEvent");
	LUA_TRY_INVOKE(2, &cocos2d::ui::Widget::dispatchFocusEvent);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_findNextFocusedWidget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:findNextFocusedWidget");
	LUA_TRY_INVOKE_R(2, &cocos2d::ui::Widget::findNextFocusedWidget);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getActionTag");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getActionTag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getBottomBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getBottomBoundary");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getBottomBoundary);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getCustomSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getCustomSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getCustomSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getLayoutParameter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getLayoutParameter");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getLayoutParameter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getLayoutSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getLayoutSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getLayoutSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getLeftBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getLeftBoundary");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getLeftBoundary);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getPositionPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getPositionPercent");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getPositionPercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getPositionType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getPositionType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getRightBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getRightBoundary");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getRightBoundary);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getSizePercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getSizePercent");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getSizePercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getSizeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getSizeType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getSizeType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getTopBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getTopBoundary");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getTopBoundary);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getTouchBeganPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getTouchBeganPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getTouchBeganPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getTouchEndPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getTouchEndPosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getTouchEndPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getTouchMovePosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getTouchMovePosition");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getTouchMovePosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getVirtualRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getVirtualRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getVirtualRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getVirtualRendererSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getVirtualRendererSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getVirtualRendererSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_ignoreContentAdaptWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:ignoreContentAdaptWithSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::ignoreContentAdaptWithSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_interceptTouchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:interceptTouchEvent");
	LUA_TRY_INVOKE(3, &cocos2d::ui::Widget::interceptTouchEvent);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Widget_isBright(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isBright");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isBright);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isClippingParentContainsPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isClippingParentContainsPoint");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::Widget::isClippingParentContainsPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFlippedX");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isFlippedX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFlippedY");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isFlippedY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFocusEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFocusEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isFocusEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFocused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFocused");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isFocused);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isHighlighted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isHighlighted");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isHighlighted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isIgnoreContentAdaptWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isIgnoreContentAdaptWithSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isIgnoreContentAdaptWithSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isLayoutComponentEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isLayoutComponentEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isLayoutComponentEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isPropagateTouchEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isPropagateTouchEvents");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isPropagateTouchEvents);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isSwallowTouches");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isSwallowTouches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isTouchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isTouchEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isTouchEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isUnifySizeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isUnifySizeEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::isUnifySizeEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_onFocusChange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:onFocusChange");
	LUA_TRY_INVOKE(2, &cocos2d::ui::Widget::onFocusChange);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_propagateTouchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:propagateTouchEvent");
	LUA_TRY_INVOKE(3, &cocos2d::ui::Widget::propagateTouchEvent);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Widget_requestFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:requestFocus");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Widget::requestFocus);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setActionTag");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setActionTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setBright(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setBright");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setBright);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setBrightStyle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setBrightStyle");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setBrightStyle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFlippedX");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setFlippedX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFlippedY");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setFlippedY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFocusEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFocusEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setFocusEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFocused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFocused");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setFocused);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setHighlighted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setHighlighted");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setHighlighted);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setLayoutComponentEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setLayoutComponentEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setLayoutComponentEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setLayoutParameter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setLayoutParameter");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setLayoutParameter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setPositionPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setPositionPercent");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setPositionPercent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setPositionType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setPositionType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setPropagateTouchEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setPropagateTouchEvents");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setPropagateTouchEvents);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setSizePercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setSizePercent");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setSizePercent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setSizeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setSizeType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setSizeType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setSwallowTouches");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setSwallowTouches);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setTouchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setTouchEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setTouchEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setUnifySizeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setUnifySizeEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::setUnifySizeEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_updateSizeAndPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:updateSizeAndPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(const cocos2d::Vec2&)>(&cocos2d::ui::Widget::updateSizeAndPosition));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Widget::*)()>(&cocos2d::ui::Widget::updateSizeAndPosition));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_ui_Widget_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_enableDpadNavigation(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:enableDpadNavigation");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Widget::enableDpadNavigation);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_getCurrentFocusedWidget(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:getCurrentFocusedWidget");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Widget::getCurrentFocusedWidget);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiWidget(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Widget, "Widget", "ccui.Widget",
		cocos2d::ui::Widget, "cc.ProtectedNode",
		nullptr, nullptr);
	LUA_METHOD("addClickEventListener", lua_cocos2d_ui_Widget_addClickEventListener);
	LUA_METHOD("addTouchEventListener", lua_cocos2d_ui_Widget_addTouchEventListener);
	LUA_METHOD("clone", lua_cocos2d_ui_Widget_clone);
	LUA_METHOD("dispatchFocusEvent", lua_cocos2d_ui_Widget_dispatchFocusEvent);
	LUA_METHOD("findNextFocusedWidget", lua_cocos2d_ui_Widget_findNextFocusedWidget);
	LUA_METHOD("getActionTag", lua_cocos2d_ui_Widget_getActionTag);
	LUA_METHOD("getBottomBoundary", lua_cocos2d_ui_Widget_getBottomBoundary);
	LUA_METHOD("getCustomSize", lua_cocos2d_ui_Widget_getCustomSize);
	LUA_METHOD("getLayoutParameter", lua_cocos2d_ui_Widget_getLayoutParameter);
	LUA_METHOD("getLayoutSize", lua_cocos2d_ui_Widget_getLayoutSize);
	LUA_METHOD("getLeftBoundary", lua_cocos2d_ui_Widget_getLeftBoundary);
	LUA_METHOD("getPositionPercent", lua_cocos2d_ui_Widget_getPositionPercent);
	LUA_METHOD("getPositionType", lua_cocos2d_ui_Widget_getPositionType);
	LUA_METHOD("getRightBoundary", lua_cocos2d_ui_Widget_getRightBoundary);
	LUA_METHOD("getSizePercent", lua_cocos2d_ui_Widget_getSizePercent);
	LUA_METHOD("getSizeType", lua_cocos2d_ui_Widget_getSizeType);
	LUA_METHOD("getTopBoundary", lua_cocos2d_ui_Widget_getTopBoundary);
	LUA_METHOD("getTouchBeganPosition", lua_cocos2d_ui_Widget_getTouchBeganPosition);
	LUA_METHOD("getTouchEndPosition", lua_cocos2d_ui_Widget_getTouchEndPosition);
	LUA_METHOD("getTouchMovePosition", lua_cocos2d_ui_Widget_getTouchMovePosition);
	LUA_METHOD("getVirtualRenderer", lua_cocos2d_ui_Widget_getVirtualRenderer);
	LUA_METHOD("getVirtualRendererSize", lua_cocos2d_ui_Widget_getVirtualRendererSize);
	LUA_METHOD("ignoreContentAdaptWithSize", lua_cocos2d_ui_Widget_ignoreContentAdaptWithSize);
	LUA_METHOD("interceptTouchEvent", lua_cocos2d_ui_Widget_interceptTouchEvent);
	LUA_METHOD("isBright", lua_cocos2d_ui_Widget_isBright);
	LUA_METHOD("isClippingParentContainsPoint", lua_cocos2d_ui_Widget_isClippingParentContainsPoint);
	LUA_METHOD("isEnabled", lua_cocos2d_ui_Widget_isEnabled);
	LUA_METHOD("isFlippedX", lua_cocos2d_ui_Widget_isFlippedX);
	LUA_METHOD("isFlippedY", lua_cocos2d_ui_Widget_isFlippedY);
	LUA_METHOD("isFocusEnabled", lua_cocos2d_ui_Widget_isFocusEnabled);
	LUA_METHOD("isFocused", lua_cocos2d_ui_Widget_isFocused);
	LUA_METHOD("isHighlighted", lua_cocos2d_ui_Widget_isHighlighted);
	LUA_METHOD("isIgnoreContentAdaptWithSize", lua_cocos2d_ui_Widget_isIgnoreContentAdaptWithSize);
	LUA_METHOD("isLayoutComponentEnabled", lua_cocos2d_ui_Widget_isLayoutComponentEnabled);
	LUA_METHOD("isPropagateTouchEvents", lua_cocos2d_ui_Widget_isPropagateTouchEvents);
	LUA_METHOD("isSwallowTouches", lua_cocos2d_ui_Widget_isSwallowTouches);
	LUA_METHOD("isTouchEnabled", lua_cocos2d_ui_Widget_isTouchEnabled);
	LUA_METHOD("isUnifySizeEnabled", lua_cocos2d_ui_Widget_isUnifySizeEnabled);
	LUA_METHOD("onFocusChange", lua_cocos2d_ui_Widget_onFocusChange);
	LUA_METHOD("propagateTouchEvent", lua_cocos2d_ui_Widget_propagateTouchEvent);
	LUA_METHOD("requestFocus", lua_cocos2d_ui_Widget_requestFocus);
	LUA_METHOD("setActionTag", lua_cocos2d_ui_Widget_setActionTag);
	LUA_METHOD("setBright", lua_cocos2d_ui_Widget_setBright);
	LUA_METHOD("setBrightStyle", lua_cocos2d_ui_Widget_setBrightStyle);
	LUA_METHOD("setEnabled", lua_cocos2d_ui_Widget_setEnabled);
	LUA_METHOD("setFlippedX", lua_cocos2d_ui_Widget_setFlippedX);
	LUA_METHOD("setFlippedY", lua_cocos2d_ui_Widget_setFlippedY);
	LUA_METHOD("setFocusEnabled", lua_cocos2d_ui_Widget_setFocusEnabled);
	LUA_METHOD("setFocused", lua_cocos2d_ui_Widget_setFocused);
	LUA_METHOD("setHighlighted", lua_cocos2d_ui_Widget_setHighlighted);
	LUA_METHOD("setLayoutComponentEnabled", lua_cocos2d_ui_Widget_setLayoutComponentEnabled);
	LUA_METHOD("setLayoutParameter", lua_cocos2d_ui_Widget_setLayoutParameter);
	LUA_METHOD("setPositionPercent", lua_cocos2d_ui_Widget_setPositionPercent);
	LUA_METHOD("setPositionType", lua_cocos2d_ui_Widget_setPositionType);
	LUA_METHOD("setPropagateTouchEvents", lua_cocos2d_ui_Widget_setPropagateTouchEvents);
	LUA_METHOD("setSizePercent", lua_cocos2d_ui_Widget_setSizePercent);
	LUA_METHOD("setSizeType", lua_cocos2d_ui_Widget_setSizeType);
	LUA_METHOD("setSwallowTouches", lua_cocos2d_ui_Widget_setSwallowTouches);
	LUA_METHOD("setTouchEnabled", lua_cocos2d_ui_Widget_setTouchEnabled);
	LUA_METHOD("setUnifySizeEnabled", lua_cocos2d_ui_Widget_setUnifySizeEnabled);
	LUA_METHOD("updateSizeAndPosition", lua_cocos2d_ui_Widget_updateSizeAndPosition);
	LUA_METHOD("create", lua_cocos2d_ui_Widget_create);
	LUA_METHOD("enableDpadNavigation", lua_cocos2d_ui_Widget_enableDpadNavigation);
	LUA_METHOD("getCurrentFocusedWidget", lua_cocos2d_ui_Widget_getCurrentFocusedWidget);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Layout_forceDoLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:forceDoLayout");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Layout::forceDoLayout);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColorOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColorOpacity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundColorOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColorType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColorType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundColorType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColorVector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColorVector");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundColorVector);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundEndColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundEndColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundImageCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundImageCapInsets");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundImageCapInsets);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundImageColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundImageColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundImageColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundImageOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundImageOpacity");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundImageOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundImageTextureSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundImageTextureSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundImageTextureSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundStartColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getBackGroundStartColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getClippingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getClippingType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getClippingType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getLayoutType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getLayoutType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getRenderFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::getRenderFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isBackGroundImageScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isBackGroundImageScale9Enabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::isBackGroundImageScale9Enabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isClippingEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::isClippingEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isLoopFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isLoopFocus");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::isLoopFocus);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isPassFocusToChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isPassFocusToChild");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::isPassFocusToChild);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_removeBackGroundImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:removeBackGroundImage");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Layout::removeBackGroundImage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_requestDoLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:requestDoLayout");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Layout::requestDoLayout);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_setBackGroundColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColor");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Layout::*)(const cocos2d::Color3B&, const cocos2d::Color3B&)>(&cocos2d::ui::Layout::setBackGroundColor)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(const cocos2d::Color3B&)>(&cocos2d::ui::Layout::setBackGroundColor));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Layout_setBackGroundColorOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColorOpacity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundColorOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundColorType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColorType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundColorType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundColorVector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColorVector");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundColorVector);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImage");
	LUA_TRY_INVOKE(2, &cocos2d::ui::Layout::setBackGroundImage);
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Layout* obj,std::string_view arg0){{return obj->setBackGroundImage(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Layout_setBackGroundImageCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageCapInsets");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundImageCapInsets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImageColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundImageColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImageOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageOpacity");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundImageOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImageScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageScale9Enabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setBackGroundImageScale9Enabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setClippingEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setClippingEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setClippingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setClippingType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setClippingType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setLayoutType");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setLayoutType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setLoopFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setLoopFocus");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setLoopFocus);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setPassFocusToChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setPassFocusToChild");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Layout::setPassFocusToChild);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Layout", "ccui.Layout:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Layout", "ccui.Layout:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Layout::createInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLayout(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Layout, "Layout", "ccui.Layout",
		cocos2d::ui::Layout, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("forceDoLayout", lua_cocos2d_ui_Layout_forceDoLayout);
	LUA_METHOD("getBackGroundColor", lua_cocos2d_ui_Layout_getBackGroundColor);
	LUA_METHOD("getBackGroundColorOpacity", lua_cocos2d_ui_Layout_getBackGroundColorOpacity);
	LUA_METHOD("getBackGroundColorType", lua_cocos2d_ui_Layout_getBackGroundColorType);
	LUA_METHOD("getBackGroundColorVector", lua_cocos2d_ui_Layout_getBackGroundColorVector);
	LUA_METHOD("getBackGroundEndColor", lua_cocos2d_ui_Layout_getBackGroundEndColor);
	LUA_METHOD("getBackGroundImageCapInsets", lua_cocos2d_ui_Layout_getBackGroundImageCapInsets);
	LUA_METHOD("getBackGroundImageColor", lua_cocos2d_ui_Layout_getBackGroundImageColor);
	LUA_METHOD("getBackGroundImageOpacity", lua_cocos2d_ui_Layout_getBackGroundImageOpacity);
	LUA_METHOD("getBackGroundImageTextureSize", lua_cocos2d_ui_Layout_getBackGroundImageTextureSize);
	LUA_METHOD("getBackGroundStartColor", lua_cocos2d_ui_Layout_getBackGroundStartColor);
	LUA_METHOD("getClippingType", lua_cocos2d_ui_Layout_getClippingType);
	LUA_METHOD("getLayoutType", lua_cocos2d_ui_Layout_getLayoutType);
	LUA_METHOD("getRenderFile", lua_cocos2d_ui_Layout_getRenderFile);
	LUA_METHOD("isBackGroundImageScale9Enabled", lua_cocos2d_ui_Layout_isBackGroundImageScale9Enabled);
	LUA_METHOD("isClippingEnabled", lua_cocos2d_ui_Layout_isClippingEnabled);
	LUA_METHOD("isLoopFocus", lua_cocos2d_ui_Layout_isLoopFocus);
	LUA_METHOD("isPassFocusToChild", lua_cocos2d_ui_Layout_isPassFocusToChild);
	LUA_METHOD("removeBackGroundImage", lua_cocos2d_ui_Layout_removeBackGroundImage);
	LUA_METHOD("requestDoLayout", lua_cocos2d_ui_Layout_requestDoLayout);
	LUA_METHOD("setBackGroundColor", lua_cocos2d_ui_Layout_setBackGroundColor);
	LUA_METHOD("setBackGroundColorOpacity", lua_cocos2d_ui_Layout_setBackGroundColorOpacity);
	LUA_METHOD("setBackGroundColorType", lua_cocos2d_ui_Layout_setBackGroundColorType);
	LUA_METHOD("setBackGroundColorVector", lua_cocos2d_ui_Layout_setBackGroundColorVector);
	LUA_METHOD("setBackGroundImage", lua_cocos2d_ui_Layout_setBackGroundImage);
	LUA_METHOD("setBackGroundImageCapInsets", lua_cocos2d_ui_Layout_setBackGroundImageCapInsets);
	LUA_METHOD("setBackGroundImageColor", lua_cocos2d_ui_Layout_setBackGroundImageColor);
	LUA_METHOD("setBackGroundImageOpacity", lua_cocos2d_ui_Layout_setBackGroundImageOpacity);
	LUA_METHOD("setBackGroundImageScale9Enabled", lua_cocos2d_ui_Layout_setBackGroundImageScale9Enabled);
	LUA_METHOD("setClippingEnabled", lua_cocos2d_ui_Layout_setClippingEnabled);
	LUA_METHOD("setClippingType", lua_cocos2d_ui_Layout_setClippingType);
	LUA_METHOD("setLayoutType", lua_cocos2d_ui_Layout_setLayoutType);
	LUA_METHOD("setLoopFocus", lua_cocos2d_ui_Layout_setLoopFocus);
	LUA_METHOD("setPassFocusToChild", lua_cocos2d_ui_Layout_setPassFocusToChild);
	LUA_METHOD("create", lua_cocos2d_ui_Layout_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_Layout_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_Button_getCapInsetsDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getCapInsetsDisabledRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getCapInsetsDisabledRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getCapInsetsNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getCapInsetsNormalRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getCapInsetsNormalRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getCapInsetsPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getCapInsetsPressedRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getCapInsetsPressedRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getDisabledFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getDisabledFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getDisabledFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getNormalFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getNormalFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getNormalFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getNormalTextureSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getNormalTextureSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getNormalTextureSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getPressedFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getPressedFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getPressedFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getRendererClicked(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererClicked");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getRendererClicked);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getRendererDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererDisabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getRendererDisabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getRendererNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getRendererNormal");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getRendererNormal);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleFontName");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleFontName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleFontSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleLabel");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleLabel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getTitleText");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getTitleText);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:getZoomScale");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::getZoomScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:init");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ui::Button::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::init)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->init(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1){{return obj->init(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->init(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_ui_Button_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::isScale9Enabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_loadTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextureDisabled");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTextureDisabled)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTextureDisabled(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextureNormal");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTextureNormal)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTextureNormal(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTexturePressed");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Button::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::loadTexturePressed)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Button* obj,std::string_view arg0){{return obj->loadTexturePressed(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:loadTextures");
	LUA_TRY_INVOKE(4, &cocos2d::ui::Button::loadTextures);
	LUA_TRY_INVOKE(3, ([](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::Button* obj,std::string_view arg0,std::string_view arg1){{return obj->loadTextures(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ui_Button_resetDisabledRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetDisabledRender");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Button::resetDisabledRender);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_resetNormalRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetNormalRender");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Button::resetNormalRender);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_resetPressedRender(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:resetPressedRender");
	LUA_TRY_INVOKE(0, &cocos2d::ui::Button::resetPressedRender);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Button_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setCapInsets");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setCapInsets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setCapInsetsDisabledRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setCapInsetsDisabledRenderer");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setCapInsetsDisabledRenderer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setCapInsetsNormalRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setCapInsetsNormalRenderer");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setCapInsetsNormalRenderer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setCapInsetsPressedRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setCapInsetsPressedRenderer");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setCapInsetsPressedRenderer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setPressedActionEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setPressedActionEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setPressedActionEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setScale9Enabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setScale9Enabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleAlignment");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::Button::*)(cocos2d::TextHAlignment, cocos2d::TextVAlignment)>(&cocos2d::ui::Button::setTitleAlignment)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Button::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::Button::setTitleAlignment));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Button_setTitleColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setTitleColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleFontName");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setTitleFontName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleFontSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setTitleFontSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleLabel");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setTitleLabel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setTitleText(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setTitleText");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setTitleText);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Button", "ccui.Button:setZoomScale");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Button::setZoomScale);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Button_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Button", "ccui.Button:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cocos2d::ui::Button>(*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Button::create)));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,std::string_view arg1,std::string_view arg2){{return cocos2d::ui::Button::create(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::Button::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::Button::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::Button>(*)()>(&cocos2d::ui::Button::create));
	LUA_SINVOKE_FOOTER("0,1,2,3,4");
}
int lua_cocos2d_ui_Button_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Button", "ccui.Button:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Button::createInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Button, "Button", "ccui.Button",
		cocos2d::ui::Button, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getCapInsetsDisabledRenderer", lua_cocos2d_ui_Button_getCapInsetsDisabledRenderer);
	LUA_METHOD("getCapInsetsNormalRenderer", lua_cocos2d_ui_Button_getCapInsetsNormalRenderer);
	LUA_METHOD("getCapInsetsPressedRenderer", lua_cocos2d_ui_Button_getCapInsetsPressedRenderer);
	LUA_METHOD("getDisabledFile", lua_cocos2d_ui_Button_getDisabledFile);
	LUA_METHOD("getNormalFile", lua_cocos2d_ui_Button_getNormalFile);
	LUA_METHOD("getNormalTextureSize", lua_cocos2d_ui_Button_getNormalTextureSize);
	LUA_METHOD("getPressedFile", lua_cocos2d_ui_Button_getPressedFile);
	LUA_METHOD("getRendererClicked", lua_cocos2d_ui_Button_getRendererClicked);
	LUA_METHOD("getRendererDisabled", lua_cocos2d_ui_Button_getRendererDisabled);
	LUA_METHOD("getRendererNormal", lua_cocos2d_ui_Button_getRendererNormal);
	LUA_METHOD("getTitleColor", lua_cocos2d_ui_Button_getTitleColor);
	LUA_METHOD("getTitleFontName", lua_cocos2d_ui_Button_getTitleFontName);
	LUA_METHOD("getTitleFontSize", lua_cocos2d_ui_Button_getTitleFontSize);
	LUA_METHOD("getTitleLabel", lua_cocos2d_ui_Button_getTitleLabel);
	LUA_METHOD("getTitleRenderer", lua_cocos2d_ui_Button_getTitleRenderer);
	LUA_METHOD("getTitleText", lua_cocos2d_ui_Button_getTitleText);
	LUA_METHOD("getZoomScale", lua_cocos2d_ui_Button_getZoomScale);
	LUA_METHOD("init", lua_cocos2d_ui_Button_init);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_Button_isScale9Enabled);
	LUA_METHOD("loadTextureDisabled", lua_cocos2d_ui_Button_loadTextureDisabled);
	LUA_METHOD("loadTextureNormal", lua_cocos2d_ui_Button_loadTextureNormal);
	LUA_METHOD("loadTexturePressed", lua_cocos2d_ui_Button_loadTexturePressed);
	LUA_METHOD("loadTextures", lua_cocos2d_ui_Button_loadTextures);
	LUA_METHOD("resetDisabledRender", lua_cocos2d_ui_Button_resetDisabledRender);
	LUA_METHOD("resetNormalRender", lua_cocos2d_ui_Button_resetNormalRender);
	LUA_METHOD("resetPressedRender", lua_cocos2d_ui_Button_resetPressedRender);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_Button_setCapInsets);
	LUA_METHOD("setCapInsetsDisabledRenderer", lua_cocos2d_ui_Button_setCapInsetsDisabledRenderer);
	LUA_METHOD("setCapInsetsNormalRenderer", lua_cocos2d_ui_Button_setCapInsetsNormalRenderer);
	LUA_METHOD("setCapInsetsPressedRenderer", lua_cocos2d_ui_Button_setCapInsetsPressedRenderer);
	LUA_METHOD("setPressedActionEnabled", lua_cocos2d_ui_Button_setPressedActionEnabled);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_Button_setScale9Enabled);
	LUA_METHOD("setTitleAlignment", lua_cocos2d_ui_Button_setTitleAlignment);
	LUA_METHOD("setTitleColor", lua_cocos2d_ui_Button_setTitleColor);
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
int lua_cocos2d_ui_AbstractCheckButton_getBackDisabledFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getBackDisabledFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getBackDisabledFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getBackNormalFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getBackNormalFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getBackNormalFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getBackPressedFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getBackPressedFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getBackPressedFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getCrossDisabledFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getCrossDisabledFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getCrossDisabledFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getCrossNormalFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getCrossNormalFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getCrossNormalFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackground");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getRendererBackground);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackgroundDisabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getRendererBackgroundDisabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererBackgroundSelected");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getRendererBackgroundSelected);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCross(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererFrontCross");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getRendererFrontCross);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCrossDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getRendererFrontCrossDisabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getRendererFrontCrossDisabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_getZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:getZoomScale");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::getZoomScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:init");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::ui::AbstractCheckButton::*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::init)));
	LUA_TRY_INVOKE_R(5, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return obj->init(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_INVOKE_FOOTER("5,6");
}
int lua_cocos2d_ui_AbstractCheckButton_isSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:isSelected");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::AbstractCheckButton::isSelected);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGround(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGround");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGround)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGround(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGroundDisabled");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGroundDisabled)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGroundDisabled(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureBackGroundSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureBackGroundSelected");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureBackGroundSelected)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureBackGroundSelected(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCross(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureFrontCross");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureFrontCross)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureFrontCross(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextureFrontCrossDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextureFrontCrossDisabled");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::AbstractCheckButton::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::AbstractCheckButton::loadTextureFrontCrossDisabled)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0){{return obj->loadTextureFrontCrossDisabled(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_AbstractCheckButton_loadTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:loadTextures");
	LUA_TRY_INVOKE(6, &cocos2d::ui::AbstractCheckButton::loadTextures);
	LUA_TRY_INVOKE(5, ([](cocos2d::ui::AbstractCheckButton* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return obj->loadTextures(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_INVOKE_FOOTER("5,6");
}
int lua_cocos2d_ui_AbstractCheckButton_setSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:setSelected");
	LUA_TRY_INVOKE(1, &cocos2d::ui::AbstractCheckButton::setSelected);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_AbstractCheckButton_setZoomScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.AbstractCheckButton", "ccui.AbstractCheckButton:setZoomScale");
	LUA_TRY_INVOKE(1, &cocos2d::ui::AbstractCheckButton::setZoomScale);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UI_ccuiAbstractCheckButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::AbstractCheckButton, "AbstractCheckButton", "ccui.AbstractCheckButton",
		cocos2d::ui::AbstractCheckButton, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getBackDisabledFile", lua_cocos2d_ui_AbstractCheckButton_getBackDisabledFile);
	LUA_METHOD("getBackNormalFile", lua_cocos2d_ui_AbstractCheckButton_getBackNormalFile);
	LUA_METHOD("getBackPressedFile", lua_cocos2d_ui_AbstractCheckButton_getBackPressedFile);
	LUA_METHOD("getCrossDisabledFile", lua_cocos2d_ui_AbstractCheckButton_getCrossDisabledFile);
	LUA_METHOD("getCrossNormalFile", lua_cocos2d_ui_AbstractCheckButton_getCrossNormalFile);
	LUA_METHOD("getRendererBackground", lua_cocos2d_ui_AbstractCheckButton_getRendererBackground);
	LUA_METHOD("getRendererBackgroundDisabled", lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundDisabled);
	LUA_METHOD("getRendererBackgroundSelected", lua_cocos2d_ui_AbstractCheckButton_getRendererBackgroundSelected);
	LUA_METHOD("getRendererFrontCross", lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCross);
	LUA_METHOD("getRendererFrontCrossDisabled", lua_cocos2d_ui_AbstractCheckButton_getRendererFrontCrossDisabled);
	LUA_METHOD("getZoomScale", lua_cocos2d_ui_AbstractCheckButton_getZoomScale);
	LUA_METHOD("init", lua_cocos2d_ui_AbstractCheckButton_init);
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
int lua_cocos2d_ui_CheckBox_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.CheckBox", "ccui.CheckBox:addEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::ui::CheckBox::addEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_CheckBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.CheckBox", "ccui.CheckBox:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cocos2d::ui::CheckBox>(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::CheckBox::create)));
	LUA_TRY_INVOKE_R(5, ([](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return cocos2d::ui::CheckBox::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::CheckBox>(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::CheckBox::create)));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::CheckBox::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::CheckBox>(*)()>(&cocos2d::ui::CheckBox::create));
	LUA_SINVOKE_FOOTER("0,2,3,5,6");
}
int lua_cocos2d_ui_CheckBox_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.CheckBox", "ccui.CheckBox:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::CheckBox::createInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiCheckBox(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::CheckBox, "CheckBox", "ccui.CheckBox",
		cocos2d::ui::CheckBox, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_CheckBox_addEventListener);
	LUA_METHOD("create", lua_cocos2d_ui_CheckBox_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_CheckBox_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RadioButton_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButton", "ccui.RadioButton:addEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RadioButton::addEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButton_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButton", "ccui.RadioButton:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cocos2d::ui::RadioButton>(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RadioButton::create)));
	LUA_TRY_INVOKE_R(5, ([](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4){{return cocos2d::ui::RadioButton::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::RadioButton>(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::RadioButton::create)));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::RadioButton::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::RadioButton>(*)()>(&cocos2d::ui::RadioButton::create));
	LUA_SINVOKE_FOOTER("0,2,3,5,6");
}
int lua_cocos2d_ui_RadioButton_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButton", "ccui.RadioButton:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RadioButton::createInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRadioButton(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RadioButton, "RadioButton", "ccui.RadioButton",
		cocos2d::ui::RadioButton, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_RadioButton_addEventListener);
	LUA_METHOD("create", lua_cocos2d_ui_RadioButton_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_RadioButton_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_RadioButtonGroup_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:addEventListener");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RadioButtonGroup::addEventListener);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_addRadioButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:addRadioButton");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RadioButtonGroup::addRadioButton);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_getNumberOfRadioButtons(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getNumberOfRadioButtons");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RadioButtonGroup::getNumberOfRadioButtons);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_getRadioButtonByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getRadioButtonByIndex");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::RadioButtonGroup::getRadioButtonByIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_getSelectedButtonIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:getSelectedButtonIndex");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RadioButtonGroup::getSelectedButtonIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_isAllowedNoSelection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:isAllowedNoSelection");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RadioButtonGroup::isAllowedNoSelection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_removeAllRadioButtons(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:removeAllRadioButtons");
	LUA_TRY_INVOKE(0, &cocos2d::ui::RadioButtonGroup::removeAllRadioButtons);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RadioButtonGroup_removeRadioButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:removeRadioButton");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RadioButtonGroup::removeRadioButton);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_setAllowedNoSelection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:setAllowedNoSelection");
	LUA_TRY_INVOKE(1, &cocos2d::ui::RadioButtonGroup::setAllowedNoSelection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_setSelectedButton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:setSelectedButton");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(cocos2d::ui::RadioButton*)>(&cocos2d::ui::RadioButtonGroup::setSelectedButton));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(int)>(&cocos2d::ui::RadioButtonGroup::setSelectedButton));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_setSelectedButtonWithoutEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:setSelectedButtonWithoutEvent");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(cocos2d::ui::RadioButton*)>(&cocos2d::ui::RadioButtonGroup::setSelectedButtonWithoutEvent));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::RadioButtonGroup::*)(int)>(&cocos2d::ui::RadioButtonGroup::setSelectedButtonWithoutEvent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RadioButtonGroup_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RadioButtonGroup", "ccui.RadioButtonGroup:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::RadioButtonGroup::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRadioButtonGroup(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RadioButtonGroup, "RadioButtonGroup", "ccui.RadioButtonGroup",
		cocos2d::ui::RadioButtonGroup, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_RadioButtonGroup_addEventListener);
	LUA_METHOD("addRadioButton", lua_cocos2d_ui_RadioButtonGroup_addRadioButton);
	LUA_METHOD("getNumberOfRadioButtons", lua_cocos2d_ui_RadioButtonGroup_getNumberOfRadioButtons);
	LUA_METHOD("getRadioButtonByIndex", lua_cocos2d_ui_RadioButtonGroup_getRadioButtonByIndex);
	LUA_METHOD("getSelectedButtonIndex", lua_cocos2d_ui_RadioButtonGroup_getSelectedButtonIndex);
	LUA_METHOD("isAllowedNoSelection", lua_cocos2d_ui_RadioButtonGroup_isAllowedNoSelection);
	LUA_METHOD("removeAllRadioButtons", lua_cocos2d_ui_RadioButtonGroup_removeAllRadioButtons);
	LUA_METHOD("removeRadioButton", lua_cocos2d_ui_RadioButtonGroup_removeRadioButton);
	LUA_METHOD("setAllowedNoSelection", lua_cocos2d_ui_RadioButtonGroup_setAllowedNoSelection);
	LUA_METHOD("setSelectedButton", lua_cocos2d_ui_RadioButtonGroup_setSelectedButton);
	LUA_METHOD("setSelectedButtonWithoutEvent", lua_cocos2d_ui_RadioButtonGroup_setSelectedButtonWithoutEvent);
	LUA_METHOD("create", lua_cocos2d_ui_RadioButtonGroup_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_ImageView_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ImageView::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ImageView_getCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:getCapInsets");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ImageView::getCapInsets);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ImageView_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:getRenderFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ImageView::getRenderFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ImageView_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:init");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ui::ImageView::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::ImageView::init)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::ui::ImageView* obj,std::string_view arg0){{return obj->init(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_ImageView_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ImageView::isScale9Enabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_ImageView_loadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:loadTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::ui::ImageView::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::ImageView::loadTexture)));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::ImageView* obj,std::string_view arg0){{return obj->loadTexture(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_ImageView_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:setBlendFunc");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ImageView::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ImageView_setCapInsets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:setCapInsets");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ImageView::setCapInsets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ImageView_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:setScale9Enabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ImageView::setScale9Enabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ImageView_setTextureRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ImageView", "ccui.ImageView:setTextureRect");
	LUA_TRY_INVOKE(1, &cocos2d::ui::ImageView::setTextureRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_ImageView_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ImageView", "ccui.ImageView:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::ui::ImageView>(*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::ImageView::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::ImageView::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::ImageView>(*)()>(&cocos2d::ui::ImageView::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_ui_ImageView_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.ImageView", "ccui.ImageView:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::ImageView::createInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiImageView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ImageView, "ImageView", "ccui.ImageView",
		cocos2d::ui::ImageView, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_ui_ImageView_getBlendFunc);
	LUA_METHOD("getCapInsets", lua_cocos2d_ui_ImageView_getCapInsets);
	LUA_METHOD("getRenderFile", lua_cocos2d_ui_ImageView_getRenderFile);
	LUA_METHOD("init", lua_cocos2d_ui_ImageView_init);
	LUA_METHOD("isScale9Enabled", lua_cocos2d_ui_ImageView_isScale9Enabled);
	LUA_METHOD("loadTexture", lua_cocos2d_ui_ImageView_loadTexture);
	LUA_METHOD("setBlendFunc", lua_cocos2d_ui_ImageView_setBlendFunc);
	LUA_METHOD("setCapInsets", lua_cocos2d_ui_ImageView_setCapInsets);
	LUA_METHOD("setScale9Enabled", lua_cocos2d_ui_ImageView_setScale9Enabled);
	LUA_METHOD("setTextureRect", lua_cocos2d_ui_ImageView_setTextureRect);
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
int lua_cocos2d_ui_Text_enableGlow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableGlow");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::enableGlow);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_enableOutline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableOutline");
	LUA_TRY_INVOKE(2, &cocos2d::ui::Text::enableOutline);
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){{return obj->enableOutline(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Text_enableShadow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:enableShadow");
	LUA_TRY_INVOKE(3, &cocos2d::ui::Text::enableShadow);
	LUA_TRY_INVOKE(2, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0,const cocos2d::Vec2& arg1){{return obj->enableShadow(arg0,arg1);}}));
	LUA_TRY_INVOKE(1, ([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){{return obj->enableShadow(arg0);}}));
	LUA_TRY_INVOKE(0, [](cocos2d::ui::Text* obj){{return obj->enableShadow();}});
	LUA_INVOKE_FOOTER("0,1,2,3");
}
int lua_cocos2d_ui_Text_getAutoRenderSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getAutoRenderSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getAutoRenderSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getEffectColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getEffectColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getEffectColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getFontName");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getFontName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getFontSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getLabelEffectType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getLabelEffectType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getLabelEffectType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getLetter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getLetter");
	LUA_TRY_INVOKE_R(1, &cocos2d::ui::Text::getLetter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_getOutlineSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getOutlineSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getOutlineSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getShadowBlurRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowBlurRadius");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getShadowBlurRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getShadowColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getShadowColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getShadowOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getShadowOffset");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getShadowOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getString");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getStringLength");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getStringLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextAreaSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getTextAreaSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextColor");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getTextColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getTextHorizontalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getTextVerticalAlignment");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getTextVerticalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:getType");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::getType);
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
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::isShadowEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_isTouchScaleChangeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:isTouchScaleChangeEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::isTouchScaleChangeEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Text_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setBlendFunc");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setFontName");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setFontName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setFontSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setFontSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setString");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextAreaSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextAreaSize");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setTextAreaSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextColor");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setTextColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextHorizontalAlignment");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setTextHorizontalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTextVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTextVerticalAlignment");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setTextVerticalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_setTouchScaleChangeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Text", "ccui.Text:setTouchScaleChangeEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::Text::setTouchScaleChangeEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Text_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Text", "ccui.Text:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::Text>(*)(std::string_view, std::string_view, float)>(&cocos2d::ui::Text::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::Text>(*)()>(&cocos2d::ui::Text::create));
	LUA_SINVOKE_FOOTER("0,3");
}
int lua_cocos2d_ui_Text_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Text", "ccui.Text:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::Text::createInstance);
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
	LUA_TRY_INVOKE(0, &cocos2d::ui::TextAtlas::adaptRenderers);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getRenderFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextAtlas::getRenderFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getString");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextAtlas::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:getStringLength");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextAtlas::getStringLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_TextAtlas_setProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:setProperty");
	LUA_TRY_INVOKE(5, &cocos2d::ui::TextAtlas::setProperty);
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_ui_TextAtlas_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:setString");
	LUA_TRY_INVOKE(1, &cocos2d::ui::TextAtlas::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TextAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cocos2d::ui::TextAtlas>(*)(std::string_view, std::string_view, int, int, std::string_view)>(&cocos2d::ui::TextAtlas::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::TextAtlas>(*)()>(&cocos2d::ui::TextAtlas::create));
	LUA_SINVOKE_FOOTER("0,5");
}
int lua_cocos2d_ui_TextAtlas_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextAtlas", "ccui.TextAtlas:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::TextAtlas::createInstance);
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
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::getCapInsets);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getDirection");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_getPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getPercent");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::getPercent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_getRenderFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:getRenderFile");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::getRenderFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LoadingBar_isScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:isScale9Enabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::isScale9Enabled);
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
	LUA_TRY_INVOKE(1, &cocos2d::ui::LoadingBar::setCapInsets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setDirection");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LoadingBar::setDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_setPercent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setPercent");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LoadingBar::setPercent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_setScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:setScale9Enabled");
	LUA_TRY_INVOKE(1, &cocos2d::ui::LoadingBar::setScale9Enabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LoadingBar_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ui::LoadingBar>(*)(std::string_view, cocos2d::ui::Widget::TextureResType, float)>(&cocos2d::ui::LoadingBar::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](std::string_view arg0,cocos2d::ui::Widget::TextureResType arg1){{return cocos2d::ui::LoadingBar::create(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::ui::LoadingBar>(*)(std::string_view, float)>(&cocos2d::ui::LoadingBar::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::ui::LoadingBar::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::ui::LoadingBar>(*)()>(&cocos2d::ui::LoadingBar::create));
	LUA_SINVOKE_FOOTER("0,1,2,3");
}
int lua_cocos2d_ui_LoadingBar_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LoadingBar", "ccui.LoadingBar:createInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::ui::LoadingBar::createInstance);
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
extern int luaReg_UI_ccuiLayoutParameter(lua_State* lua_S);
extern int luaReg_UI_ccuiLinearLayoutParameter(lua_State* lua_S);
extern int luaReg_UI_ccuiRelativeLayoutParameter(lua_State* lua_S);
extern int luaReg_UI_ccuiWidget(lua_State* lua_S);
extern int luaReg_UI_ccuiLayout(lua_State* lua_S);
extern int luaReg_UI_ccuiButton(lua_State* lua_S);
extern int luaReg_UI_ccuiAbstractCheckButton(lua_State* lua_S);
extern int luaReg_UI_ccuiCheckBox(lua_State* lua_S);
extern int luaReg_UI_ccuiRadioButton(lua_State* lua_S);
extern int luaReg_UI_ccuiRadioButtonGroup(lua_State* lua_S);
extern int luaReg_UI_ccuiImageView(lua_State* lua_S);
extern int luaReg_UI_ccuiText(lua_State* lua_S);
extern int luaReg_UI_ccuiTextAtlas(lua_State* lua_S);
extern int luaReg_UI_ccuiLoadingBar(lua_State* lua_S);
extern int luaReg_UI_ccuiScrollView(lua_State* lua_S);
extern int luaReg_UI_ccuiListView(lua_State* lua_S);
extern int luaReg_UI_ccuiSlider(lua_State* lua_S);
extern int luaReg_UI_ccuiTextField(lua_State* lua_S);
extern int luaReg_UI_ccuiTextBMFont(lua_State* lua_S);
extern int luaReg_UI_ccuiPageView(lua_State* lua_S);
extern int luaReg_UI_ccuiHelper(lua_State* lua_S);
extern int luaReg_UI_ccuiRichElement(lua_State* lua_S);
extern int luaReg_UI_ccuiRichElementText(lua_State* lua_S);
extern int luaReg_UI_ccuiRichElementImage(lua_State* lua_S);
extern int luaReg_UI_ccuiRichElementCustomNode(lua_State* lua_S);
extern int luaReg_UI_ccuiRichElementNewLine(lua_State* lua_S);
extern int luaReg_UI_ccuiRichText(lua_State* lua_S);
extern int luaReg_UI_ccuiHBox(lua_State* lua_S);
extern int luaReg_UI_ccuiVBox(lua_State* lua_S);
extern int luaReg_UI_ccuiRelativeBox(lua_State* lua_S);
extern int luaReg_UI_ccuiScale9Sprite(lua_State* lua_S);
extern int luaReg_UI_ccuiEditBox(lua_State* lua_S);
extern int luaReg_UI_ccuiLayoutComponent(lua_State* lua_S);
extern int luaReg_UI_ccuiTabHeader(lua_State* lua_S);
extern int luaReg_UI_ccuiTabControl(lua_State* lua_S);

int register_all_cc_ui(lua_State* lua_S)
{
	luaReg_UI_ccuiLayoutParameter(lua_S);
	luaReg_UI_ccuiLinearLayoutParameter(lua_S);
	luaReg_UI_ccuiRelativeLayoutParameter(lua_S);
	luaReg_UI_ccuiWidget(lua_S);
	luaReg_UI_ccuiLayout(lua_S);
	luaReg_UI_ccuiButton(lua_S);
	luaReg_UI_ccuiAbstractCheckButton(lua_S);
	luaReg_UI_ccuiCheckBox(lua_S);
	luaReg_UI_ccuiRadioButton(lua_S);
	luaReg_UI_ccuiRadioButtonGroup(lua_S);
	luaReg_UI_ccuiImageView(lua_S);
	luaReg_UI_ccuiText(lua_S);
	luaReg_UI_ccuiTextAtlas(lua_S);
	luaReg_UI_ccuiLoadingBar(lua_S);
	luaReg_UI_ccuiScrollView(lua_S);
	luaReg_UI_ccuiListView(lua_S);
	luaReg_UI_ccuiSlider(lua_S);
	luaReg_UI_ccuiTextField(lua_S);
	luaReg_UI_ccuiTextBMFont(lua_S);
	luaReg_UI_ccuiPageView(lua_S);
	luaReg_UI_ccuiHelper(lua_S);
	luaReg_UI_ccuiRichElement(lua_S);
	luaReg_UI_ccuiRichElementText(lua_S);
	luaReg_UI_ccuiRichElementImage(lua_S);
	luaReg_UI_ccuiRichElementCustomNode(lua_S);
	luaReg_UI_ccuiRichElementNewLine(lua_S);
	luaReg_UI_ccuiRichText(lua_S);
	luaReg_UI_ccuiHBox(lua_S);
	luaReg_UI_ccuiVBox(lua_S);
	luaReg_UI_ccuiRelativeBox(lua_S);
	luaReg_UI_ccuiScale9Sprite(lua_S);
	luaReg_UI_ccuiEditBox(lua_S);
	luaReg_UI_ccuiLayoutComponent(lua_S);
	luaReg_UI_ccuiTabHeader(lua_S);
	luaReg_UI_ccuiTabControl(lua_S);
	return 0;
}
