#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_LayoutParameter_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutParameter*(cocos2d::ui::LayoutParameter::*)()>(&cocos2d::ui::LayoutParameter::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_copyProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:copyProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutParameter::*)(cocos2d::ui::LayoutParameter*)>(&cocos2d::ui::LayoutParameter::copyProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LayoutParameter_createCloneInstance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:createCloneInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutParameter*(cocos2d::ui::LayoutParameter::*)()>(&cocos2d::ui::LayoutParameter::createCloneInstance));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_getLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:getLayoutType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutParameter::Type(cocos2d::ui::LayoutParameter::*)()const>(&cocos2d::ui::LayoutParameter::getLayoutType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LayoutParameter", "ccui.LayoutParameter:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LayoutParameter*(*)()>(&cocos2d::ui::LayoutParameter::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LayoutParameter, "LayoutParameter", "ccui.LayoutParameter",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_ui_LayoutParameter_clone);
	LUA_METHOD("copyProperties", lua_cocos2d_ui_LayoutParameter_copyProperties);
	LUA_METHOD("createCloneInstance", lua_cocos2d_ui_LayoutParameter_createCloneInstance);
	LUA_METHOD("getLayoutType", lua_cocos2d_ui_LayoutParameter_getLayoutType);
	LUA_METHOD("create", lua_cocos2d_ui_LayoutParameter_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ui_LinearLayoutParameter_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:getGravity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LinearLayoutParameter::LinearGravity(cocos2d::ui::LinearLayoutParameter::*)()const>(&cocos2d::ui::LinearLayoutParameter::getGravity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_LinearLayoutParameter_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LinearLayoutParameter::*)(cocos2d::ui::LinearLayoutParameter::LinearGravity)>(&cocos2d::ui::LinearLayoutParameter::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_LinearLayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.LinearLayoutParameter", "ccui.LinearLayoutParameter:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::LinearLayoutParameter*(*)()>(&cocos2d::ui::LinearLayoutParameter::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLinearLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::LinearLayoutParameter, "LinearLayoutParameter", "ccui.LinearLayoutParameter",
		cocos2d::ui::LayoutParameter, "ccui.LayoutParameter",
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
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RelativeLayoutParameter::RelativeAlign(cocos2d::ui::RelativeLayoutParameter::*)()const>(&cocos2d::ui::RelativeLayoutParameter::getAlign));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_getRelativeName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:getRelativeName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::RelativeLayoutParameter::*)()const>(&cocos2d::ui::RelativeLayoutParameter::getRelativeName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_getRelativeToWidgetName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:getRelativeToWidgetName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::RelativeLayoutParameter::*)()const>(&cocos2d::ui::RelativeLayoutParameter::getRelativeToWidgetName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setAlign(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setAlign");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RelativeLayoutParameter::*)(cocos2d::ui::RelativeLayoutParameter::RelativeAlign)>(&cocos2d::ui::RelativeLayoutParameter::setAlign));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setRelativeName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setRelativeName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RelativeLayoutParameter::*)(std::string_view)>(&cocos2d::ui::RelativeLayoutParameter::setRelativeName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_setRelativeToWidgetName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:setRelativeToWidgetName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::RelativeLayoutParameter::*)(std::string_view)>(&cocos2d::ui::RelativeLayoutParameter::setRelativeToWidgetName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_RelativeLayoutParameter_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.RelativeLayoutParameter", "ccui.RelativeLayoutParameter:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::RelativeLayoutParameter*(*)()>(&cocos2d::ui::RelativeLayoutParameter::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiRelativeLayoutParameter(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::RelativeLayoutParameter, "RelativeLayoutParameter", "ccui.RelativeLayoutParameter",
		cocos2d::ui::LayoutParameter, "ccui.LayoutParameter",
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
int lua_cocos2d_ui_Widget_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(cocos2d::ui::Widget::*)()>(&cocos2d::ui::Widget::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_dispatchFocusEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:dispatchFocusEvent");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget*, cocos2d::ui::Widget*)>(&cocos2d::ui::Widget::dispatchFocusEvent));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_findNextFocusedWidget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:findNextFocusedWidget");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::Widget*(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::FocusDirection, cocos2d::ui::Widget*)>(&cocos2d::ui::Widget::findNextFocusedWidget));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getBottomBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getBottomBoundary");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getBottomBoundary));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getCallbackName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getCallbackName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getCallbackName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getCallbackType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getCallbackType");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getCallbackType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getLeftBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getLeftBoundary");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getLeftBoundary));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getPositionType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget::PositionType(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getPositionType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getRightBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getRightBoundary");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getRightBoundary));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getSizeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getSizeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget::SizeType(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getSizeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getTopBoundary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getTopBoundary");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::getTopBoundary));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_getVirtualRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:getVirtualRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::ui::Widget::*)()>(&cocos2d::ui::Widget::getVirtualRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_ignoreContentAdaptWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:ignoreContentAdaptWithSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::ignoreContentAdaptWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_interceptTouchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:interceptTouchEvent");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::TouchEventType, cocos2d::ui::Widget*, cocos2d::Touch*)>(&cocos2d::ui::Widget::interceptTouchEvent));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Widget_isBright(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isBright");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isBright));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFlippedX");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isFlippedX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFlippedY");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isFlippedY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFocusEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFocusEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isFocusEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isFocused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isFocused");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isFocused));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isHighlighted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isHighlighted");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isHighlighted));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isIgnoreContentAdaptWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isIgnoreContentAdaptWithSize");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isIgnoreContentAdaptWithSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isLayoutComponentEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isLayoutComponentEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isLayoutComponentEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isPropagateTouchEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isPropagateTouchEvents");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isPropagateTouchEvents));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isSwallowTouches");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isSwallowTouches));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isTouchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isTouchEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isTouchEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_isUnifySizeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:isUnifySizeEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Widget::*)()const>(&cocos2d::ui::Widget::isUnifySizeEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_onFocusChange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:onFocusChange");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget*, cocos2d::ui::Widget*)>(&cocos2d::ui::Widget::onFocusChange));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ui_Widget_propagateTouchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:propagateTouchEvent");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::TouchEventType, cocos2d::ui::Widget*, cocos2d::Touch*)>(&cocos2d::ui::Widget::propagateTouchEvent));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_ui_Widget_requestFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:requestFocus");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Widget::*)()>(&cocos2d::ui::Widget::requestFocus));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(int)>(&cocos2d::ui::Widget::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setBright(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setBright");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setBright));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setBrightStyle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setBrightStyle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::BrightStyle)>(&cocos2d::ui::Widget::setBrightStyle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setCallbackName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setCallbackName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(std::string_view)>(&cocos2d::ui::Widget::setCallbackName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setCallbackType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setCallbackType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(std::string_view)>(&cocos2d::ui::Widget::setCallbackType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFlippedX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setFlippedX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFlippedY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setFlippedY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFocusEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFocusEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setFocusEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setFocused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setFocused");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setFocused));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setHighlighted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setHighlighted");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setHighlighted));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setLayoutComponentEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setLayoutComponentEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setLayoutComponentEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setLayoutParameter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setLayoutParameter");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::LayoutParameter*)>(&cocos2d::ui::Widget::setLayoutParameter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setPositionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setPositionType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::PositionType)>(&cocos2d::ui::Widget::setPositionType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setPropagateTouchEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setPropagateTouchEvents");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setPropagateTouchEvents));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setSizeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setSizeType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(cocos2d::ui::Widget::SizeType)>(&cocos2d::ui::Widget::setSizeType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setSwallowTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setSwallowTouches");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setSwallowTouches));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setTouchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setTouchEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setTouchEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_setUnifySizeEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:setUnifySizeEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Widget::*)(bool)>(&cocos2d::ui::Widget::setUnifySizeEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(*)()>(&cocos2d::ui::Widget::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Widget_enableDpadNavigation(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:enableDpadNavigation");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::ui::Widget::enableDpadNavigation));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Widget_getCurrentFocusedWidget(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Widget", "ccui.Widget:getCurrentFocusedWidget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Widget*(*)()>(&cocos2d::ui::Widget::getCurrentFocusedWidget));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiWidget(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Widget, "Widget", "ccui.Widget",
		cocos2d::ProtectedNode, "cc.ProtectedNode",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_ui_Widget_clone);
	LUA_METHOD("dispatchFocusEvent", lua_cocos2d_ui_Widget_dispatchFocusEvent);
	LUA_METHOD("findNextFocusedWidget", lua_cocos2d_ui_Widget_findNextFocusedWidget);
	LUA_METHOD("getActionTag", lua_cocos2d_ui_Widget_getActionTag);
	LUA_METHOD("getBottomBoundary", lua_cocos2d_ui_Widget_getBottomBoundary);
	LUA_METHOD("getCallbackName", lua_cocos2d_ui_Widget_getCallbackName);
	LUA_METHOD("getCallbackType", lua_cocos2d_ui_Widget_getCallbackType);
	LUA_METHOD("getLeftBoundary", lua_cocos2d_ui_Widget_getLeftBoundary);
	LUA_METHOD("getPositionType", lua_cocos2d_ui_Widget_getPositionType);
	LUA_METHOD("getRightBoundary", lua_cocos2d_ui_Widget_getRightBoundary);
	LUA_METHOD("getSizeType", lua_cocos2d_ui_Widget_getSizeType);
	LUA_METHOD("getTopBoundary", lua_cocos2d_ui_Widget_getTopBoundary);
	LUA_METHOD("getVirtualRenderer", lua_cocos2d_ui_Widget_getVirtualRenderer);
	LUA_METHOD("ignoreContentAdaptWithSize", lua_cocos2d_ui_Widget_ignoreContentAdaptWithSize);
	LUA_METHOD("interceptTouchEvent", lua_cocos2d_ui_Widget_interceptTouchEvent);
	LUA_METHOD("isBright", lua_cocos2d_ui_Widget_isBright);
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
	LUA_METHOD("setCallbackName", lua_cocos2d_ui_Widget_setCallbackName);
	LUA_METHOD("setCallbackType", lua_cocos2d_ui_Widget_setCallbackType);
	LUA_METHOD("setEnabled", lua_cocos2d_ui_Widget_setEnabled);
	LUA_METHOD("setFlippedX", lua_cocos2d_ui_Widget_setFlippedX);
	LUA_METHOD("setFlippedY", lua_cocos2d_ui_Widget_setFlippedY);
	LUA_METHOD("setFocusEnabled", lua_cocos2d_ui_Widget_setFocusEnabled);
	LUA_METHOD("setFocused", lua_cocos2d_ui_Widget_setFocused);
	LUA_METHOD("setHighlighted", lua_cocos2d_ui_Widget_setHighlighted);
	LUA_METHOD("setLayoutComponentEnabled", lua_cocos2d_ui_Widget_setLayoutComponentEnabled);
	LUA_METHOD("setLayoutParameter", lua_cocos2d_ui_Widget_setLayoutParameter);
	LUA_METHOD("setPositionType", lua_cocos2d_ui_Widget_setPositionType);
	LUA_METHOD("setPropagateTouchEvents", lua_cocos2d_ui_Widget_setPropagateTouchEvents);
	LUA_METHOD("setSizeType", lua_cocos2d_ui_Widget_setSizeType);
	LUA_METHOD("setSwallowTouches", lua_cocos2d_ui_Widget_setSwallowTouches);
	LUA_METHOD("setTouchEnabled", lua_cocos2d_ui_Widget_setTouchEnabled);
	LUA_METHOD("setUnifySizeEnabled", lua_cocos2d_ui_Widget_setUnifySizeEnabled);
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
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Layout::*)()>(&cocos2d::ui::Layout::forceDoLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColorOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColorOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::getBackGroundColorOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundColorType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundColorType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Layout::BackGroundColorType(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::getBackGroundColorType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getBackGroundImageOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getBackGroundImageOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::getBackGroundImageOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getClippingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getClippingType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Layout::ClippingType(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::getClippingType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_getLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:getLayoutType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Layout::Type(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::getLayoutType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isBackGroundImageScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isBackGroundImageScale9Enabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::isBackGroundImageScale9Enabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isClippingEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::isClippingEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isLoopFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isLoopFocus");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::isLoopFocus));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_isPassFocusToChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:isPassFocusToChild");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::Layout::*)()const>(&cocos2d::ui::Layout::isPassFocusToChild));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_removeBackGroundImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:removeBackGroundImage");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Layout::*)()>(&cocos2d::ui::Layout::removeBackGroundImage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_requestDoLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:requestDoLayout");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::Layout::*)()>(&cocos2d::ui::Layout::requestDoLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_setBackGroundColorOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColorOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(uint8_t)>(&cocos2d::ui::Layout::setBackGroundColorOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundColorType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundColorType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(cocos2d::ui::Layout::BackGroundColorType)>(&cocos2d::ui::Layout::setBackGroundColorType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImage");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Layout::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Layout::setBackGroundImage));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Layout* obj,std::string_view arg0){{return obj->setBackGroundImage(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Layout_setBackGroundImageOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(uint8_t)>(&cocos2d::ui::Layout::setBackGroundImageOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setBackGroundImageScale9Enabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setBackGroundImageScale9Enabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(bool)>(&cocos2d::ui::Layout::setBackGroundImageScale9Enabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setClippingEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(bool)>(&cocos2d::ui::Layout::setClippingEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setClippingType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setClippingType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(cocos2d::ui::Layout::ClippingType)>(&cocos2d::ui::Layout::setClippingType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setLayoutType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setLayoutType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(cocos2d::ui::Layout::Type)>(&cocos2d::ui::Layout::setLayoutType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setLoopFocus(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setLoopFocus");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(bool)>(&cocos2d::ui::Layout::setLoopFocus));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_setPassFocusToChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Layout", "ccui.Layout:setPassFocusToChild");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::Layout::*)(bool)>(&cocos2d::ui::Layout::setPassFocusToChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_Layout_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Layout", "ccui.Layout:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::Layout*(*)()>(&cocos2d::ui::Layout::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_ui_Layout_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.Layout", "ccui.Layout:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Layout::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_UI_ccuiLayout(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::Layout, "Layout", "ccui.Layout",
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("forceDoLayout", lua_cocos2d_ui_Layout_forceDoLayout);
	LUA_METHOD("getBackGroundColorOpacity", lua_cocos2d_ui_Layout_getBackGroundColorOpacity);
	LUA_METHOD("getBackGroundColorType", lua_cocos2d_ui_Layout_getBackGroundColorType);
	LUA_METHOD("getBackGroundImageOpacity", lua_cocos2d_ui_Layout_getBackGroundImageOpacity);
	LUA_METHOD("getClippingType", lua_cocos2d_ui_Layout_getClippingType);
	LUA_METHOD("getLayoutType", lua_cocos2d_ui_Layout_getLayoutType);
	LUA_METHOD("isBackGroundImageScale9Enabled", lua_cocos2d_ui_Layout_isBackGroundImageScale9Enabled);
	LUA_METHOD("isClippingEnabled", lua_cocos2d_ui_Layout_isClippingEnabled);
	LUA_METHOD("isLoopFocus", lua_cocos2d_ui_Layout_isLoopFocus);
	LUA_METHOD("isPassFocusToChild", lua_cocos2d_ui_Layout_isPassFocusToChild);
	LUA_METHOD("removeBackGroundImage", lua_cocos2d_ui_Layout_removeBackGroundImage);
	LUA_METHOD("requestDoLayout", lua_cocos2d_ui_Layout_requestDoLayout);
	LUA_METHOD("setBackGroundColorOpacity", lua_cocos2d_ui_Layout_setBackGroundColorOpacity);
	LUA_METHOD("setBackGroundColorType", lua_cocos2d_ui_Layout_setBackGroundColorType);
	LUA_METHOD("setBackGroundImage", lua_cocos2d_ui_Layout_setBackGroundImage);
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
