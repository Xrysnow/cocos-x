#include "cclua_webview_auto.hpp"
#include "base/ccConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && defined(CC_ENABLE_MSEDGE_WEBVIEW2) && CC_ENABLE_MSEDGE_WEBVIEW2)
#include "lua_conversion/lua_conversion.hpp"
#include "ui/UIWebView/UIWebView.h"

int lua_cc_ui_WebView_canGoBack_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:canGoBack");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ui::WebView::*)()>(&cc::ui::WebView::canGoBack));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_canGoForward_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:canGoForward");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::ui::WebView::*)()>(&cc::ui::WebView::canGoForward));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_evaluateJS_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:evaluateJS");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(std::string_view)>(&cc::ui::WebView::evaluateJS));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_getOpacityWebView_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:getOpacityWebView");
	LUA_TRY_INVOKE_R(0, static_cast<float(cc::ui::WebView::*)()const>(&cc::ui::WebView::getOpacityWebView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_goBack_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:goBack");
	LUA_TRY_INVOKE(0, static_cast<void(cc::ui::WebView::*)()>(&cc::ui::WebView::goBack));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_goForward_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:goForward");
	LUA_TRY_INVOKE(0, static_cast<void(cc::ui::WebView::*)()>(&cc::ui::WebView::goForward));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_loadFile_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:loadFile");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(std::string_view)>(&cc::ui::WebView::loadFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_loadHTMLString_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:loadHTMLString");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::ui::WebView::*)(std::string_view, std::string_view)>(&cc::ui::WebView::loadHTMLString)));
	LUA_TRY_INVOKE(1, ([](cc::ui::WebView* obj,std::string_view arg0){{return obj->loadHTMLString(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_ui_WebView_loadURL_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:loadURL");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(std::string_view)>(&cc::ui::WebView::loadURL));
	LUA_TRY_INVOKE(2, (static_cast<void(cc::ui::WebView::*)(std::string_view, bool)>(&cc::ui::WebView::loadURL)));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_ui_WebView_reload_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:reload");
	LUA_TRY_INVOKE(0, static_cast<void(cc::ui::WebView::*)()>(&cc::ui::WebView::reload));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_setBackgroundTransparent_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setBackgroundTransparent");
	LUA_TRY_INVOKE(0, static_cast<void(cc::ui::WebView::*)()>(&cc::ui::WebView::setBackgroundTransparent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_setBounces_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setBounces");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(bool)>(&cc::ui::WebView::setBounces));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setJavascriptInterfaceScheme_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setJavascriptInterfaceScheme");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(std::string_view)>(&cc::ui::WebView::setJavascriptInterfaceScheme));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setOnDidFailLoading_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setOnDidFailLoading");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(const cc::ui::WebView::ccWebViewCallback&)>(&cc::ui::WebView::setOnDidFailLoading));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setOnDidFinishLoading_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setOnDidFinishLoading");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(const cc::ui::WebView::ccWebViewCallback&)>(&cc::ui::WebView::setOnDidFinishLoading));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setOnShouldStartLoading_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setOnShouldStartLoading");
	LUA_TRY_INVOKE(1, (static_cast<void(cc::ui::WebView::*)(const std::function<bool(cc::ui::WebView*, std::string_view)>&)>(&cc::ui::WebView::setOnShouldStartLoading)));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setOpacityWebView_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setOpacityWebView");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(float)>(&cc::ui::WebView::setOpacityWebView));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_setScalesPageToFit_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:setScalesPageToFit");
	LUA_TRY_INVOKE(1, static_cast<void(cc::ui::WebView::*)(const bool)>(&cc::ui::WebView::setScalesPageToFit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ui_WebView_stopLoading_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.WebView", "ccui.WebView:stopLoading");
	LUA_TRY_INVOKE(0, static_cast<void(cc::ui::WebView::*)()>(&cc::ui::WebView::stopLoading));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ui_WebView_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.WebView", "ccui.WebView:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::ui::WebView>(*)()>(&cc::ui::WebView::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_cc_webview_ccuiWebView(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cc::ui::WebView, "WebView", "ccui.WebView",
		cc::ui::WebView, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("canGoBack", lua_cc_ui_WebView_canGoBack_1);
	LUA_METHOD("canGoForward", lua_cc_ui_WebView_canGoForward_1);
	LUA_METHOD("evaluateJS", lua_cc_ui_WebView_evaluateJS_1);
	LUA_METHOD("getOpacityWebView", lua_cc_ui_WebView_getOpacityWebView_1);
	LUA_METHOD("goBack", lua_cc_ui_WebView_goBack_1);
	LUA_METHOD("goForward", lua_cc_ui_WebView_goForward_1);
	LUA_METHOD("loadFile", lua_cc_ui_WebView_loadFile_1);
	LUA_METHOD("loadHTMLString", lua_cc_ui_WebView_loadHTMLString_1);
	LUA_METHOD("loadURL", lua_cc_ui_WebView_loadURL_1);
	LUA_METHOD("reload", lua_cc_ui_WebView_reload_1);
	LUA_METHOD("setBackgroundTransparent", lua_cc_ui_WebView_setBackgroundTransparent_1);
	LUA_METHOD("setBounces", lua_cc_ui_WebView_setBounces_1);
	LUA_METHOD("setJavascriptInterfaceScheme", lua_cc_ui_WebView_setJavascriptInterfaceScheme_1);
	LUA_METHOD("setOnDidFailLoading", lua_cc_ui_WebView_setOnDidFailLoading_1);
	LUA_METHOD("setOnDidFinishLoading", lua_cc_ui_WebView_setOnDidFinishLoading_1);
	LUA_METHOD("setOnShouldStartLoading", lua_cc_ui_WebView_setOnShouldStartLoading_1);
	LUA_METHOD("setOpacityWebView", lua_cc_ui_WebView_setOpacityWebView_1);
	LUA_METHOD("setScalesPageToFit", lua_cc_ui_WebView_setScalesPageToFit_1);
	LUA_METHOD("stopLoading", lua_cc_ui_WebView_stopLoading_1);
	LUA_METHOD("create", lua_cc_ui_WebView_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_webview(lua_State* lua_S)
{
#include "base/ccConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && defined(CC_ENABLE_MSEDGE_WEBVIEW2) && CC_ENABLE_MSEDGE_WEBVIEW2)
	tolua_open(lua_S);
	luaReg_cc_webview_ccuiWebView(lua_S);
	return 0;
#else
	return 0;
#endif
}
