#include "cclua_ui_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"

int lua_cocos2d_ui_LayoutComponent_getAnchorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getAnchorPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Point&(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getAnchorPosition));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_ui_LayoutComponent_getPercentContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPercentContentSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPercentContentSize));
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
int lua_cocos2d_ui_LayoutComponent_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Point&(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getPosition));
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
int lua_cocos2d_ui_LayoutComponent_getSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:getSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::ui::LayoutComponent::*)()const>(&cocos2d::ui::LayoutComponent::getSize));
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
int lua_cocos2d_ui_LayoutComponent_setAnchorPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setAnchorPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(const cocos2d::Point&)>(&cocos2d::ui::LayoutComponent::setAnchorPosition));
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
int lua_cocos2d_ui_LayoutComponent_setPercentContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPercentContentSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(const cocos2d::Vec2&)>(&cocos2d::ui::LayoutComponent::setPercentContentSize));
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
int lua_cocos2d_ui_LayoutComponent_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(const cocos2d::Point&)>(&cocos2d::ui::LayoutComponent::setPosition));
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
int lua_cocos2d_ui_LayoutComponent_setSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.LayoutComponent", "ccui.LayoutComponent:setSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::LayoutComponent::*)(const cocos2d::Vec2&)>(&cocos2d::ui::LayoutComponent::setSize));
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
		cocos2d::ui::LayoutComponent, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getAnchorPosition", lua_cocos2d_ui_LayoutComponent_getAnchorPosition);
	LUA_METHOD("getBottomMargin", lua_cocos2d_ui_LayoutComponent_getBottomMargin);
	LUA_METHOD("getHorizontalEdge", lua_cocos2d_ui_LayoutComponent_getHorizontalEdge);
	LUA_METHOD("getLeftMargin", lua_cocos2d_ui_LayoutComponent_getLeftMargin);
	LUA_METHOD("getPercentContentSize", lua_cocos2d_ui_LayoutComponent_getPercentContentSize);
	LUA_METHOD("getPercentHeight", lua_cocos2d_ui_LayoutComponent_getPercentHeight);
	LUA_METHOD("getPercentWidth", lua_cocos2d_ui_LayoutComponent_getPercentWidth);
	LUA_METHOD("getPosition", lua_cocos2d_ui_LayoutComponent_getPosition);
	LUA_METHOD("getPositionPercentX", lua_cocos2d_ui_LayoutComponent_getPositionPercentX);
	LUA_METHOD("getPositionPercentY", lua_cocos2d_ui_LayoutComponent_getPositionPercentY);
	LUA_METHOD("getRightMargin", lua_cocos2d_ui_LayoutComponent_getRightMargin);
	LUA_METHOD("getSize", lua_cocos2d_ui_LayoutComponent_getSize);
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
	LUA_METHOD("setAnchorPosition", lua_cocos2d_ui_LayoutComponent_setAnchorPosition);
	LUA_METHOD("setBottomMargin", lua_cocos2d_ui_LayoutComponent_setBottomMargin);
	LUA_METHOD("setHorizontalEdge", lua_cocos2d_ui_LayoutComponent_setHorizontalEdge);
	LUA_METHOD("setLeftMargin", lua_cocos2d_ui_LayoutComponent_setLeftMargin);
	LUA_METHOD("setPercentContentSize", lua_cocos2d_ui_LayoutComponent_setPercentContentSize);
	LUA_METHOD("setPercentHeight", lua_cocos2d_ui_LayoutComponent_setPercentHeight);
	LUA_METHOD("setPercentHeightEnabled", lua_cocos2d_ui_LayoutComponent_setPercentHeightEnabled);
	LUA_METHOD("setPercentOnlyEnabled", lua_cocos2d_ui_LayoutComponent_setPercentOnlyEnabled);
	LUA_METHOD("setPercentWidth", lua_cocos2d_ui_LayoutComponent_setPercentWidth);
	LUA_METHOD("setPercentWidthEnabled", lua_cocos2d_ui_LayoutComponent_setPercentWidthEnabled);
	LUA_METHOD("setPosition", lua_cocos2d_ui_LayoutComponent_setPosition);
	LUA_METHOD("setPositionPercentX", lua_cocos2d_ui_LayoutComponent_setPositionPercentX);
	LUA_METHOD("setPositionPercentXEnabled", lua_cocos2d_ui_LayoutComponent_setPositionPercentXEnabled);
	LUA_METHOD("setPositionPercentY", lua_cocos2d_ui_LayoutComponent_setPositionPercentY);
	LUA_METHOD("setPositionPercentYEnabled", lua_cocos2d_ui_LayoutComponent_setPositionPercentYEnabled);
	LUA_METHOD("setRightMargin", lua_cocos2d_ui_LayoutComponent_setRightMargin);
	LUA_METHOD("setSize", lua_cocos2d_ui_LayoutComponent_setSize);
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
int lua_cocos2d_ui_TabHeader_getTitleColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:getTitleColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4B&(cocos2d::ui::TabHeader::*)()const>(&cocos2d::ui::TabHeader::getTitleColor));
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
int lua_cocos2d_ui_TabHeader_setTitleColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabHeader", "ccui.TabHeader:setTitleColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabHeader::*)(const cocos2d::Color4B&)>(&cocos2d::ui::TabHeader::setTitleColor));
	LUA_INVOKE_FOOTER("1");
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
	LUA_TRY_INVOKE_R(7, (static_cast<cocos2d::ui::TabHeader*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::TabHeader::create)));
	LUA_TRY_INVOKE_R(6, ([](std::string_view arg0,std::string_view arg1,std::string_view arg2,std::string_view arg3,std::string_view arg4,std::string_view arg5){{return cocos2d::ui::TabHeader::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4),std::move(arg5));}}));
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ui::TabHeader*(*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::TabHeader::create)));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,std::string_view arg1,std::string_view arg2){{return cocos2d::ui::TabHeader::create(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::TabHeader*(*)()>(&cocos2d::ui::TabHeader::create));
	LUA_SINVOKE_FOOTER("0,3,4,6,7");
}
int luaReg_UI_ccuiTabHeader(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::TabHeader, "TabHeader", "ccui.TabHeader",
		cocos2d::ui::TabHeader, "ccui.AbstractCheckButton",
		nullptr, nullptr);
	LUA_METHOD("getIndexInTabControl", lua_cocos2d_ui_TabHeader_getIndexInTabControl);
	LUA_METHOD("getTitleColor", lua_cocos2d_ui_TabHeader_getTitleColor);
	LUA_METHOD("getTitleFontName", lua_cocos2d_ui_TabHeader_getTitleFontName);
	LUA_METHOD("getTitleFontSize", lua_cocos2d_ui_TabHeader_getTitleFontSize);
	LUA_METHOD("getTitleRenderer", lua_cocos2d_ui_TabHeader_getTitleRenderer);
	LUA_METHOD("getTitleText", lua_cocos2d_ui_TabHeader_getTitleText);
	LUA_METHOD("setTitleColor", lua_cocos2d_ui_TabHeader_setTitleColor);
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
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::ui::TabControl::*)(int, cocos2d::ui::TabHeader*, cocos2d::ui::Layout*)>(&cocos2d::ui::TabControl::insertTab)));
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
int lua_cocos2d_ui_TabControl_setSelectTab(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setSelectTab");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::TabControl::*)(cocos2d::ui::TabHeader*)>(&cocos2d::ui::TabControl::setSelectTab));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::ui::TabControl::*)(int)>(&cocos2d::ui::TabControl::setSelectTab));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_TabControl_setTabChangedEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TabControl", "ccui.TabControl:setTabChangedEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TabControl::*)(const cocos2d::ui::TabControl::ccTabControlCallback&)>(&cocos2d::ui::TabControl::setTabChangedEventListener));
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
		cocos2d::ui::TabControl, "ccui.Widget",
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
	LUA_METHOD("setSelectTab", lua_cocos2d_ui_TabControl_setSelectTab);
	LUA_METHOD("setTabChangedEventListener", lua_cocos2d_ui_TabControl_setTabChangedEventListener);
	LUA_METHOD("create", lua_cocos2d_ui_TabControl_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
