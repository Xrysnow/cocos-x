#include "cclua_ui_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_compat.hpp"
#include "ui/CocosGUI.h"

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
int lua_cocos2d_ui_ListView_removeLastItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ListView", "ccui.ListView:removeLastItem");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeLastItem));
	LUA_INVOKE_FOOTER("0");
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
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::ui::ListView::*)(float, float, float, float)>(&cocos2d::ui::ListView::setPadding));
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
		cocos2d::ui::ScrollView, "ccui.ScrollView",
		nullptr, nullptr);
	LUA_METHOD("getBottomPadding", lua_cocos2d_ui_ListView_getBottomPadding);
	LUA_METHOD("getBottommostItemInCurrentView", lua_cocos2d_ui_ListView_getBottommostItemInCurrentView);
	LUA_METHOD("getCenterItemInCurrentView", lua_cocos2d_ui_ListView_getCenterItemInCurrentView);
	LUA_METHOD("getCurSelectedIndex", lua_cocos2d_ui_ListView_getCurSelectedIndex);
	LUA_METHOD("getIndex", lua_cocos2d_ui_ListView_getIndex);
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
	LUA_METHOD("pushBackCustomItem", lua_cocos2d_ui_ListView_pushBackCustomItem);
	LUA_METHOD("pushBackDefaultItem", lua_cocos2d_ui_ListView_pushBackDefaultItem);
	LUA_METHOD("removeAllItems", lua_cocos2d_ui_ListView_removeAllItems);
	LUA_METHOD("removeLastItem", lua_cocos2d_ui_ListView_removeLastItem);
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadBarTexture));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadBarTexture(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadProgressBarTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadProgressBarTexture");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadProgressBarTexture));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadProgressBarTexture(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextureDisabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextureDisabled");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextureDisabled));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextureDisabled(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextureNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextureNormal");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextureNormal));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextureNormal(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTexturePressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTexturePressed");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTexturePressed));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTexturePressed(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ui_Slider_loadSlidBallTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.Slider", "ccui.Slider:loadSlidBallTextures");
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::ui::Slider::*)(std::string_view, std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::loadSlidBallTextures));
	LUA_TRY_INVOKE(3, [](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1,std::string_view arg2){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE(2, [](cocos2d::ui::Slider* obj,std::string_view arg0,std::string_view arg1){{return obj->loadSlidBallTextures(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE(1, [](cocos2d::ui::Slider* obj,std::string_view arg0){{return obj->loadSlidBallTextures(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2,3,4");
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
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ui::Slider*(*)(std::string_view, std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::Slider::create));
	LUA_TRY_INVOKE_R(2, [](std::string_view arg0,std::string_view arg1){{return cocos2d::ui::Slider::create(std::move(arg0),std::move(arg1));}});
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
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("getMaxPercent", lua_cocos2d_ui_Slider_getMaxPercent);
	LUA_METHOD("getPercent", lua_cocos2d_ui_Slider_getPercent);
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
int lua_cocos2d_ui_TextField_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::TextField::*)(std::string_view)>(&cocos2d::ui::TextField::setString));
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
int lua_cocos2d_ui_TextField_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.TextField", "ccui.TextField:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::ui::TextField*(*)(std::string_view, std::string_view, int)>(&cocos2d::ui::TextField::create));
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
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("attachWithIME", lua_cocos2d_ui_TextField_attachWithIME);
	LUA_METHOD("detachWithIME", lua_cocos2d_ui_TextField_detachWithIME);
	LUA_METHOD("didNotSelectSelf", lua_cocos2d_ui_TextField_didNotSelectSelf);
	LUA_METHOD("getAttachWithIME", lua_cocos2d_ui_TextField_getAttachWithIME);
	LUA_METHOD("getDeleteBackward", lua_cocos2d_ui_TextField_getDeleteBackward);
	LUA_METHOD("getDetachWithIME", lua_cocos2d_ui_TextField_getDetachWithIME);
	LUA_METHOD("getFontName", lua_cocos2d_ui_TextField_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_ui_TextField_getFontSize);
	LUA_METHOD("getInsertText", lua_cocos2d_ui_TextField_getInsertText);
	LUA_METHOD("getMaxLength", lua_cocos2d_ui_TextField_getMaxLength);
	LUA_METHOD("getPasswordStyleText", lua_cocos2d_ui_TextField_getPasswordStyleText);
	LUA_METHOD("getPlaceHolder", lua_cocos2d_ui_TextField_getPlaceHolder);
	LUA_METHOD("getString", lua_cocos2d_ui_TextField_getString);
	LUA_METHOD("getStringLength", lua_cocos2d_ui_TextField_getStringLength);
	LUA_METHOD("getTextHorizontalAlignment", lua_cocos2d_ui_TextField_getTextHorizontalAlignment);
	LUA_METHOD("getTextVerticalAlignment", lua_cocos2d_ui_TextField_getTextVerticalAlignment);
	LUA_METHOD("isMaxLengthEnabled", lua_cocos2d_ui_TextField_isMaxLengthEnabled);
	LUA_METHOD("isPasswordEnabled", lua_cocos2d_ui_TextField_isPasswordEnabled);
	LUA_METHOD("setAttachWithIME", lua_cocos2d_ui_TextField_setAttachWithIME);
	LUA_METHOD("setCursorEnabled", lua_cocos2d_ui_TextField_setCursorEnabled);
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
	LUA_METHOD("setString", lua_cocos2d_ui_TextField_setString);
	LUA_METHOD("setTextHorizontalAlignment", lua_cocos2d_ui_TextField_setTextHorizontalAlignment);
	LUA_METHOD("setTextVerticalAlignment", lua_cocos2d_ui_TextField_setTextVerticalAlignment);
	LUA_METHOD("setTouchAreaEnabled", lua_cocos2d_ui_TextField_setTouchAreaEnabled);
	LUA_METHOD("create", lua_cocos2d_ui_TextField_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_TextField_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
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
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::ui::TextBMFont*(*)(std::string_view, std::string_view)>(&cocos2d::ui::TextBMFont::create));
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
		cocos2d::ui::Widget, "ccui.Widget",
		nullptr, nullptr);
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*, int)>(&cocos2d::ui::PageView::insertPage));
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
int lua_cocos2d_ui_PageView_setAutoScrollStopEpsilon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setAutoScrollStopEpsilon");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setAutoScrollStopEpsilon));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_PageView_setIndicatorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.PageView", "ccui.PageView:setIndicatorEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::PageView::*)(bool)>(&cocos2d::ui::PageView::setIndicatorEnabled));
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ui::PageView::*)(std::string_view, cocos2d::ui::Widget::TextureResType)>(&cocos2d::ui::PageView::setIndicatorIndexNodesTexture));
	LUA_TRY_INVOKE(1, [](cocos2d::ui::PageView* obj,std::string_view arg0){{return obj->setIndicatorIndexNodesTexture(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
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
		cocos2d::ui::ListView, "ccui.ListView",
		nullptr, nullptr);
	LUA_METHOD("addPage", lua_cocos2d_ui_PageView_addPage);
	LUA_METHOD("getCurrentPageIndex", lua_cocos2d_ui_PageView_getCurrentPageIndex);
	LUA_METHOD("getIndicatorEnabled", lua_cocos2d_ui_PageView_getIndicatorEnabled);
	LUA_METHOD("getIndicatorIndexNodesOpacity", lua_cocos2d_ui_PageView_getIndicatorIndexNodesOpacity);
	LUA_METHOD("getIndicatorIndexNodesScale", lua_cocos2d_ui_PageView_getIndicatorIndexNodesScale);
	LUA_METHOD("getIndicatorSelectedIndexOpacity", lua_cocos2d_ui_PageView_getIndicatorSelectedIndexOpacity);
	LUA_METHOD("getIndicatorSpaceBetweenIndexNodes", lua_cocos2d_ui_PageView_getIndicatorSpaceBetweenIndexNodes);
	LUA_METHOD("insertPage", lua_cocos2d_ui_PageView_insertPage);
	LUA_METHOD("removeAllPages", lua_cocos2d_ui_PageView_removeAllPages);
	LUA_METHOD("removePage", lua_cocos2d_ui_PageView_removePage);
	LUA_METHOD("setAutoScrollStopEpsilon", lua_cocos2d_ui_PageView_setAutoScrollStopEpsilon);
	LUA_METHOD("setIndicatorEnabled", lua_cocos2d_ui_PageView_setIndicatorEnabled);
	LUA_METHOD("setIndicatorIndexNodesOpacity", lua_cocos2d_ui_PageView_setIndicatorIndexNodesOpacity);
	LUA_METHOD("setIndicatorIndexNodesScale", lua_cocos2d_ui_PageView_setIndicatorIndexNodesScale);
	LUA_METHOD("setIndicatorIndexNodesTexture", lua_cocos2d_ui_PageView_setIndicatorIndexNodesTexture);
	LUA_METHOD("setIndicatorSelectedIndexOpacity", lua_cocos2d_ui_PageView_setIndicatorSelectedIndexOpacity);
	LUA_METHOD("setIndicatorSpaceBetweenIndexNodes", lua_cocos2d_ui_PageView_setIndicatorSpaceBetweenIndexNodes);
	LUA_METHOD("create", lua_cocos2d_ui_PageView_create);
	LUA_METHOD("createInstance", lua_cocos2d_ui_PageView_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
