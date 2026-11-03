#include "cclua_ui_events_auto.hpp"
#include "scripting/lua-bindings/manual/ui/cclua_ui_events_compat.hpp"
#include "ui/CocosGUI.h"

int lua_cocos2d_ui_ScrollView_addEventListener_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.ScrollView", "ccui.ScrollView:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::ui::ScrollView::ccScrollViewCallback&)>(&cocos2d::ui::ScrollView::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_UIEvents_ccuiScrollView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ScrollView, "ScrollView", "ccui.ScrollView",
		cocos2d::ui::Layout, "ccui.Layout",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_ScrollView_addEventListener_1);
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
int luaReg_UIEvents_ccuiListView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::ListView, "ListView", "ccui.ListView",
		cocos2d::ui::ScrollView, "ccui.ScrollView",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_ListView_addEventListener_1);
	LUA_METHOD("addScrollViewEventListener", lua_cocos2d_ui_ListView_addScrollViewEventListener_1);
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
int luaReg_UIEvents_ccuiPageView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::PageView, "PageView", "ccui.PageView",
		cocos2d::ui::ListView, "ccui.ListView",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_PageView_addEventListener_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int register_all_cc_ui_events(lua_State* lua_S)
{
	luaReg_UIEvents_ccuiScrollView(lua_S);
	luaReg_UIEvents_ccuiListView(lua_S);
	luaReg_UIEvents_ccuiPageView(lua_S);
	return 0;
}
