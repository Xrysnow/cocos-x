#pragma once
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include <cstring>
#include <cstdio>


// Preserve this module's legacy checked conversions independently of Release's
// global binding setting. Numeric strings and nil booleans remain accepted;
namespace ui_binding
{
template<typename Arg>
bool prepare_value(lua_State* L, int index, const char* name)
{
	using T = std::remove_cv_t<std::remove_reference_t<Arg>>;
	if constexpr (std::is_enum_v<T> || std::is_same_v<T, int>) {
		int value;
		if (!luaval_to_int32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr ((std::is_integral_v<T> && std::is_unsigned_v<T> && !std::is_same_v<T, bool>)) {
		unsigned int value;
		if (!luaval_to_uint32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_floating_point_v<T>) {
		double value;
		if (!luaval_to_number(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	
	}
	return true;
}

template<typename... Args, size_t... Index>
bool prepare_arguments(lua_State* L, const char* name, std::index_sequence<Index...>)
{
	const int first = lua_gettop(L) - int(sizeof...(Args)) + 1;
	return (prepare_value<Args>(L, first + int(Index), name) && ...);
}

template<typename T> struct prepare_signature;
template<typename R, typename... Args>
struct prepare_signature<R(*)(Args...)> {
	static bool run(lua_State* L, const char* name) {
		return prepare_arguments<Args...>(L, name, std::index_sequence_for<Args...>{});
	}
};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...)> : prepare_signature<R(*)(Args...)> {};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...) const> : prepare_signature<R(*)(Args...)> {};

template<typename F>
bool prepare(lua_State* L, const char* name, const F&)
{
	using T = std::decay_t<F>;
	if constexpr (std::is_class_v<T>)
		return prepare_signature<typename lua::function_traits<T>::pointer>::run(L, name);
	else
		return prepare_signature<T>::run(L, name);
}

inline void check_receiver(lua_State* L, const char* type, const char* name, bool member)
{
#if CC_DEBUG >= 1
    tolua_Error error{};
    const bool valid = member ? tolua_isusertype(L, 1, type, 0, &error)
                              : tolua_isusertable(L, 1, type, 0, &error);
    char native[192];
    std::snprintf(native, sizeof(native), "lua_cc_ui_%s", name + 5);
    for (char* p = native; *p; ++p) if (*p == ':') *p = '_';
    if (!valid) {
        char message[256];
        std::snprintf(message, sizeof(message), "#ferror in function '%s'.", native);
        tolua_error(L, message, &error);
    }
    if (member && !tolua_tousertype(L, 1, nullptr)) {
        char message[256];
        std::snprintf(message, sizeof(message), "invalid 'cobj' in function '%s'", native);
        tolua_error(L, message, nullptr);
    }
#else
    (void)L; (void)type; (void)name; (void)member;
#endif
}
inline int fail(lua_State* L, const char* name, int argc, int attempted)
{
    struct Error { const char* name; const char* native; const char* format; const char* label; int expected; };
    static const Error errors[] = {
        {"ccui.LayoutParameter:clone", "lua_cc_ui_LayoutParameter_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutParameter:clone", 0},
        {"ccui.LayoutParameter:getLayoutType", "lua_cc_ui_LayoutParameter_getLayoutType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutParameter:getLayoutType", 0},
        {"ccui.LayoutParameter:createCloneInstance", "lua_cc_ui_LayoutParameter_createCloneInstance", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutParameter:createCloneInstance", 0},
        {"ccui.LayoutParameter:copyProperties", "lua_cc_ui_LayoutParameter_copyProperties", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutParameter:copyProperties", 1},
        {"ccui.LayoutParameter:create", "lua_cc_ui_LayoutParameter_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.LayoutParameter:create", 0},
        {"ccui.LinearLayoutParameter:setGravity", "lua_cc_ui_LinearLayoutParameter_setGravity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LinearLayoutParameter:setGravity", 1},
        {"ccui.LinearLayoutParameter:getGravity", "lua_cc_ui_LinearLayoutParameter_getGravity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LinearLayoutParameter:getGravity", 0},
        {"ccui.LinearLayoutParameter:create", "lua_cc_ui_LinearLayoutParameter_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.LinearLayoutParameter:create", 0},
        {"ccui.RelativeLayoutParameter:setAlign", "lua_cc_ui_RelativeLayoutParameter_setAlign", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:setAlign", 1},
        {"ccui.RelativeLayoutParameter:setRelativeToWidgetName", "lua_cc_ui_RelativeLayoutParameter_setRelativeToWidgetName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:setRelativeToWidgetName", 1},
        {"ccui.RelativeLayoutParameter:getRelativeName", "lua_cc_ui_RelativeLayoutParameter_getRelativeName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:getRelativeName", 0},
        {"ccui.RelativeLayoutParameter:getRelativeToWidgetName", "lua_cc_ui_RelativeLayoutParameter_getRelativeToWidgetName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:getRelativeToWidgetName", 0},
        {"ccui.RelativeLayoutParameter:setRelativeName", "lua_cc_ui_RelativeLayoutParameter_setRelativeName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:setRelativeName", 1},
        {"ccui.RelativeLayoutParameter:getAlign", "lua_cc_ui_RelativeLayoutParameter_getAlign", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:getAlign", 0},
        {"ccui.RelativeLayoutParameter:create", "lua_cc_ui_RelativeLayoutParameter_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RelativeLayoutParameter:create", 0},
        {"ccui.Widget:setLayoutComponentEnabled", "lua_cc_ui_Widget_setLayoutComponentEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setLayoutComponentEnabled", 1},
        {"ccui.Widget:getLeftBoundary", "lua_cc_ui_Widget_getLeftBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLeftBoundary", 0},
        {"ccui.Widget:setFlippedX", "lua_cc_ui_Widget_setFlippedX", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFlippedX", 1},
        {"ccui.Widget:setCallbackName", "lua_cc_ui_Widget_setCallbackName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setCallbackName", 1},
        {"ccui.Widget:getVirtualRenderer", "lua_cc_ui_Widget_getVirtualRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getVirtualRenderer", 0},
        {"ccui.Widget:setPropagateTouchEvents", "lua_cc_ui_Widget_setPropagateTouchEvents", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPropagateTouchEvents", 1},
        {"ccui.Widget:isUnifySizeEnabled", "lua_cc_ui_Widget_isUnifySizeEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isUnifySizeEnabled", 0},
        {"ccui.Widget:setSwallowTouches", "lua_cc_ui_Widget_setSwallowTouches", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSwallowTouches", 1},
        {"ccui.Widget:setHighlighted", "lua_cc_ui_Widget_setHighlighted", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setHighlighted", 1},
        {"ccui.Widget:setPositionType", "lua_cc_ui_Widget_setPositionType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPositionType", 1},
        {"ccui.Widget:isIgnoreContentAdaptWithSize", "lua_cc_ui_Widget_isIgnoreContentAdaptWithSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isIgnoreContentAdaptWithSize", 0},
        {"ccui.Widget:isHighlighted", "lua_cc_ui_Widget_isHighlighted", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isHighlighted", 0},
        {"ccui.Widget:getPositionType", "lua_cc_ui_Widget_getPositionType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getPositionType", 0},
        {"ccui.Widget:getTopBoundary", "lua_cc_ui_Widget_getTopBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTopBoundary", 0},
        {"ccui.Widget:ignoreContentAdaptWithSize", "lua_cc_ui_Widget_ignoreContentAdaptWithSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:ignoreContentAdaptWithSize", 1},
        {"ccui.Widget:findNextFocusedWidget", "lua_cc_ui_Widget_findNextFocusedWidget", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:findNextFocusedWidget", 2},
        {"ccui.Widget:isEnabled", "lua_cc_ui_Widget_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isEnabled", 0},
        {"ccui.Widget:isFocused", "lua_cc_ui_Widget_isFocused", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFocused", 0},
        {"ccui.Widget:isTouchEnabled", "lua_cc_ui_Widget_isTouchEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isTouchEnabled", 0},
        {"ccui.Widget:getCallbackName", "lua_cc_ui_Widget_getCallbackName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCallbackName", 0},
        {"ccui.Widget:getActionTag", "lua_cc_ui_Widget_getActionTag", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getActionTag", 0},
        {"ccui.Widget:requestFocus", "lua_cc_ui_Widget_requestFocus", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:requestFocus", 0},
        {"ccui.Widget:isFocusEnabled", "lua_cc_ui_Widget_isFocusEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFocusEnabled", 0},
        {"ccui.Widget:setFocused", "lua_cc_ui_Widget_setFocused", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFocused", 1},
        {"ccui.Widget:setActionTag", "lua_cc_ui_Widget_setActionTag", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setActionTag", 1},
        {"ccui.Widget:setTouchEnabled", "lua_cc_ui_Widget_setTouchEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setTouchEnabled", 1},
        {"ccui.Widget:setFlippedY", "lua_cc_ui_Widget_setFlippedY", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFlippedY", 1},
        {"ccui.Widget:setEnabled", "lua_cc_ui_Widget_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setEnabled", 1},
        {"ccui.Widget:getRightBoundary", "lua_cc_ui_Widget_getRightBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getRightBoundary", 0},
        {"ccui.Widget:setBrightStyle", "lua_cc_ui_Widget_setBrightStyle", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setBrightStyle", 1},
        {"ccui.Widget:setLayoutParameter", "lua_cc_ui_Widget_setLayoutParameter", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setLayoutParameter", 1},
        {"ccui.Widget:clone", "lua_cc_ui_Widget_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:clone", 0},
        {"ccui.Widget:setFocusEnabled", "lua_cc_ui_Widget_setFocusEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFocusEnabled", 1},
        {"ccui.Widget:getBottomBoundary", "lua_cc_ui_Widget_getBottomBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getBottomBoundary", 0},
        {"ccui.Widget:isBright", "lua_cc_ui_Widget_isBright", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isBright", 0},
        {"ccui.Widget:dispatchFocusEvent", "lua_cc_ui_Widget_dispatchFocusEvent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:dispatchFocusEvent", 2},
        {"ccui.Widget:setUnifySizeEnabled", "lua_cc_ui_Widget_setUnifySizeEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setUnifySizeEnabled", 1},
        {"ccui.Widget:isPropagateTouchEvents", "lua_cc_ui_Widget_isPropagateTouchEvents", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isPropagateTouchEvents", 0},
        {"ccui.Widget:isLayoutComponentEnabled", "lua_cc_ui_Widget_isLayoutComponentEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isLayoutComponentEnabled", 0},
        {"ccui.Widget:onFocusChange", "lua_cc_ui_Widget_onFocusChange", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:onFocusChange", 2},
        {"ccui.Widget:getSizeType", "lua_cc_ui_Widget_getSizeType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getSizeType", 0},
        {"ccui.Widget:getCallbackType", "lua_cc_ui_Widget_getCallbackType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCallbackType", 0},
        {"ccui.Widget:propagateTouchEvent", "lua_cc_ui_Widget_propagateTouchEvent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:propagateTouchEvent", 3},
        {"ccui.Widget:isFlippedX", "lua_cc_ui_Widget_isFlippedX", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFlippedX", 0},
        {"ccui.Widget:isFlippedY", "lua_cc_ui_Widget_isFlippedY", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFlippedY", 0},
        {"ccui.Widget:setSizeType", "lua_cc_ui_Widget_setSizeType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSizeType", 1},
        {"ccui.Widget:interceptTouchEvent", "lua_cc_ui_Widget_interceptTouchEvent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:interceptTouchEvent", 3},
        {"ccui.Widget:setBright", "lua_cc_ui_Widget_setBright", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setBright", 1},
        {"ccui.Widget:setCallbackType", "lua_cc_ui_Widget_setCallbackType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setCallbackType", 1},
        {"ccui.Widget:isSwallowTouches", "lua_cc_ui_Widget_isSwallowTouches", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isSwallowTouches", 0},
        {"ccui.Widget:enableDpadNavigation", "lua_cc_ui_Widget_enableDpadNavigation", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Widget:enableDpadNavigation", 1},
        {"ccui.Widget:getCurrentFocusedWidget", "lua_cc_ui_Widget_getCurrentFocusedWidget", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Widget:getCurrentFocusedWidget", 0},
        {"ccui.Widget:create", "lua_cc_ui_Widget_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Widget:create", 0},
        {"ccui.Layout:setClippingType", "lua_cc_ui_Layout_setClippingType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setClippingType", 1},
        {"ccui.Layout:setBackGroundColorType", "lua_cc_ui_Layout_setBackGroundColorType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundColorType", 1},
        {"ccui.Layout:setLoopFocus", "lua_cc_ui_Layout_setLoopFocus", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setLoopFocus", 1},
        {"ccui.Layout:getClippingType", "lua_cc_ui_Layout_getClippingType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getClippingType", 0},
        {"ccui.Layout:isLoopFocus", "lua_cc_ui_Layout_isLoopFocus", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:isLoopFocus", 0},
        {"ccui.Layout:removeBackGroundImage", "lua_cc_ui_Layout_removeBackGroundImage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:removeBackGroundImage", 0},
        {"ccui.Layout:getBackGroundColorOpacity", "lua_cc_ui_Layout_getBackGroundColorOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundColorOpacity", 0},
        {"ccui.Layout:isClippingEnabled", "lua_cc_ui_Layout_isClippingEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:isClippingEnabled", 0},
        {"ccui.Layout:setBackGroundImageOpacity", "lua_cc_ui_Layout_setBackGroundImageOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundImageOpacity", 1},
        {"ccui.Layout:setBackGroundImage", "lua_cc_ui_Layout_setBackGroundImage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundImage", 1},
        {"ccui.Layout:requestDoLayout", "lua_cc_ui_Layout_requestDoLayout", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:requestDoLayout", 0},
        {"ccui.Layout:setClippingEnabled", "lua_cc_ui_Layout_setClippingEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setClippingEnabled", 1},
        {"ccui.Layout:isBackGroundImageScale9Enabled", "lua_cc_ui_Layout_isBackGroundImageScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:isBackGroundImageScale9Enabled", 0},
        {"ccui.Layout:getBackGroundColorType", "lua_cc_ui_Layout_getBackGroundColorType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundColorType", 0},
        {"ccui.Layout:setBackGroundColorOpacity", "lua_cc_ui_Layout_setBackGroundColorOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundColorOpacity", 1},
        {"ccui.Layout:getBackGroundImageOpacity", "lua_cc_ui_Layout_getBackGroundImageOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundImageOpacity", 0},
        {"ccui.Layout:isPassFocusToChild", "lua_cc_ui_Layout_isPassFocusToChild", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:isPassFocusToChild", 0},
        {"ccui.Layout:forceDoLayout", "lua_cc_ui_Layout_forceDoLayout", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:forceDoLayout", 0},
        {"ccui.Layout:getLayoutType", "lua_cc_ui_Layout_getLayoutType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getLayoutType", 0},
        {"ccui.Layout:setPassFocusToChild", "lua_cc_ui_Layout_setPassFocusToChild", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setPassFocusToChild", 1},
        {"ccui.Layout:setBackGroundImageScale9Enabled", "lua_cc_ui_Layout_setBackGroundImageScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundImageScale9Enabled", 1},
        {"ccui.Layout:setLayoutType", "lua_cc_ui_Layout_setLayoutType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setLayoutType", 1},
        {"ccui.Layout:create", "lua_cc_ui_Layout_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Layout:create", 0},
        {"ccui.Layout:createInstance", "lua_cc_ui_Layout_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Layout:createInstance", 0},
        {"ccui.Button:getTitleText", "lua_cc_ui_Button_getTitleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleText", 0},
        {"ccui.Button:setTitleLabel", "lua_cc_ui_Button_setTitleLabel", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleLabel", 1},
        {"ccui.Button:setTitleFontSize", "lua_cc_ui_Button_setTitleFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleFontSize", 1},
        {"ccui.Button:resetPressedRender", "lua_cc_ui_Button_resetPressedRender", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:resetPressedRender", 0},
        {"ccui.Button:setScale9Enabled", "lua_cc_ui_Button_setScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setScale9Enabled", 1},
        {"ccui.Button:resetDisabledRender", "lua_cc_ui_Button_resetDisabledRender", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:resetDisabledRender", 0},
        {"ccui.Button:getTitleRenderer", "lua_cc_ui_Button_getTitleRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleRenderer", 0},
        {"ccui.Button:getRendererClicked", "lua_cc_ui_Button_getRendererClicked", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getRendererClicked", 0},
        {"ccui.Button:getZoomScale", "lua_cc_ui_Button_getZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getZoomScale", 0},
        {"ccui.Button:resetNormalRender", "lua_cc_ui_Button_resetNormalRender", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:resetNormalRender", 0},
        {"ccui.Button:getRendererDisabled", "lua_cc_ui_Button_getRendererDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getRendererDisabled", 0},
        {"ccui.Button:loadTextureDisabled", "lua_cc_ui_Button_loadTextureDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:loadTextureDisabled", 1},
        {"ccui.Button:setTitleText", "lua_cc_ui_Button_setTitleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleText", 1},
        {"ccui.Button:loadTexturePressed", "lua_cc_ui_Button_loadTexturePressed", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:loadTexturePressed", 1},
        {"ccui.Button:setTitleFontName", "lua_cc_ui_Button_setTitleFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleFontName", 1},
        {"ccui.Button:setTitleAlignment", "lua_cc_ui_Button_setTitleAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleAlignment", 1},
        {"ccui.Button:loadTextures", "lua_cc_ui_Button_loadTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:loadTextures", 2},
        {"ccui.Button:isScale9Enabled", "lua_cc_ui_Button_isScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:isScale9Enabled", 0},
        {"ccui.Button:loadTextureNormal", "lua_cc_ui_Button_loadTextureNormal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:loadTextureNormal", 1},
        {"ccui.Button:getTitleLabel", "lua_cc_ui_Button_getTitleLabel", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleLabel", 0},
        {"ccui.Button:getTitleFontSize", "lua_cc_ui_Button_getTitleFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleFontSize", 0},
        {"ccui.Button:getRendererNormal", "lua_cc_ui_Button_getRendererNormal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getRendererNormal", 0},
        {"ccui.Button:getTitleFontName", "lua_cc_ui_Button_getTitleFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleFontName", 0},
        {"ccui.Button:setPressedActionEnabled", "lua_cc_ui_Button_setPressedActionEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setPressedActionEnabled", 1},
        {"ccui.Button:setZoomScale", "lua_cc_ui_Button_setZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setZoomScale", 1},
        {"ccui.Button:create", "lua_cc_ui_Button_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.Button:create", 0},
        {"ccui.Button:createInstance", "lua_cc_ui_Button_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Button:createInstance", 0},
        {"ccui.AbstractCheckButton:loadTextureBackGroundSelected", "lua_cc_ui_AbstractCheckButton_loadTextureBackGroundSelected", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextureBackGroundSelected", 1},
        {"ccui.AbstractCheckButton:loadTextureBackGroundDisabled", "lua_cc_ui_AbstractCheckButton_loadTextureBackGroundDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextureBackGroundDisabled", 1},
        {"ccui.AbstractCheckButton:setSelected", "lua_cc_ui_AbstractCheckButton_setSelected", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:setSelected", 1},
        {"ccui.AbstractCheckButton:getRendererFrontCrossDisabled", "lua_cc_ui_AbstractCheckButton_getRendererFrontCrossDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getRendererFrontCrossDisabled", 0},
        {"ccui.AbstractCheckButton:getRendererBackground", "lua_cc_ui_AbstractCheckButton_getRendererBackground", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getRendererBackground", 0},
        {"ccui.AbstractCheckButton:loadTextureFrontCross", "lua_cc_ui_AbstractCheckButton_loadTextureFrontCross", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextureFrontCross", 1},
        {"ccui.AbstractCheckButton:getRendererBackgroundDisabled", "lua_cc_ui_AbstractCheckButton_getRendererBackgroundDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getRendererBackgroundDisabled", 0},
        {"ccui.AbstractCheckButton:isSelected", "lua_cc_ui_AbstractCheckButton_isSelected", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:isSelected", 0},
        {"ccui.AbstractCheckButton:loadTextures", "lua_cc_ui_AbstractCheckButton_loadTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextures", 5},
        {"ccui.AbstractCheckButton:getZoomScale", "lua_cc_ui_AbstractCheckButton_getZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getZoomScale", 0},
        {"ccui.AbstractCheckButton:getRendererFrontCross", "lua_cc_ui_AbstractCheckButton_getRendererFrontCross", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getRendererFrontCross", 0},
        {"ccui.AbstractCheckButton:getRendererBackgroundSelected", "lua_cc_ui_AbstractCheckButton_getRendererBackgroundSelected", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getRendererBackgroundSelected", 0},
        {"ccui.AbstractCheckButton:loadTextureBackGround", "lua_cc_ui_AbstractCheckButton_loadTextureBackGround", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextureBackGround", 1},
        {"ccui.AbstractCheckButton:setZoomScale", "lua_cc_ui_AbstractCheckButton_setZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:setZoomScale", 1},
        {"ccui.AbstractCheckButton:loadTextureFrontCrossDisabled", "lua_cc_ui_AbstractCheckButton_loadTextureFrontCrossDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:loadTextureFrontCrossDisabled", 1},
        {"ccui.CheckBox:create", "lua_cc_ui_CheckBox_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.CheckBox:create", 2},
        {"ccui.CheckBox:createInstance", "lua_cc_ui_CheckBox_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.CheckBox:createInstance", 0},
        {"ccui.RadioButton:create", "lua_cc_ui_RadioButton_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.RadioButton:create", 2},
        {"ccui.RadioButton:createInstance", "lua_cc_ui_RadioButton_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RadioButton:createInstance", 0},
        {"ccui.RadioButtonGroup:removeRadioButton", "lua_cc_ui_RadioButtonGroup_removeRadioButton", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:removeRadioButton", 1},
        {"ccui.RadioButtonGroup:isAllowedNoSelection", "lua_cc_ui_RadioButtonGroup_isAllowedNoSelection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:isAllowedNoSelection", 0},
        {"ccui.RadioButtonGroup:getSelectedButtonIndex", "lua_cc_ui_RadioButtonGroup_getSelectedButtonIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:getSelectedButtonIndex", 0},
        {"ccui.RadioButtonGroup:setAllowedNoSelection", "lua_cc_ui_RadioButtonGroup_setAllowedNoSelection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:setAllowedNoSelection", 1},
        {"ccui.RadioButtonGroup:removeAllRadioButtons", "lua_cc_ui_RadioButtonGroup_removeAllRadioButtons", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:removeAllRadioButtons", 0},
        {"ccui.RadioButtonGroup:getRadioButtonByIndex", "lua_cc_ui_RadioButtonGroup_getRadioButtonByIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:getRadioButtonByIndex", 1},
        {"ccui.RadioButtonGroup:getNumberOfRadioButtons", "lua_cc_ui_RadioButtonGroup_getNumberOfRadioButtons", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:getNumberOfRadioButtons", 0},
        {"ccui.RadioButtonGroup:addRadioButton", "lua_cc_ui_RadioButtonGroup_addRadioButton", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:addRadioButton", 1},
        {"ccui.RadioButtonGroup:create", "lua_cc_ui_RadioButtonGroup_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RadioButtonGroup:create", 0},
        {"ccui.ImageView:loadTexture", "lua_cc_ui_ImageView_loadTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:loadTexture", 1},
        {"ccui.ImageView:setScale9Enabled", "lua_cc_ui_ImageView_setScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:setScale9Enabled", 1},
        {"ccui.ImageView:isScale9Enabled", "lua_cc_ui_ImageView_isScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:isScale9Enabled", 0},
        {"ccui.ImageView:create", "lua_cc_ui_ImageView_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.ImageView:create", 0},
        {"ccui.ImageView:createInstance", "lua_cc_ui_ImageView_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.ImageView:createInstance", 0},
        {"ccui.Text:getFontSize", "lua_cc_ui_Text_getFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getFontSize", 0},
        {"ccui.Text:getString", "lua_cc_ui_Text_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getString", 0},
        {"ccui.Text:disableEffect", "lua_cc_ui_Text_disableEffect", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:disableEffect", 0},
        {"ccui.Text:getLabelEffectType", "lua_cc_ui_Text_getLabelEffectType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getLabelEffectType", 0},
        {"ccui.Text:setTextVerticalAlignment", "lua_cc_ui_Text_setTextVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setTextVerticalAlignment", 1},
        {"ccui.Text:setFontName", "lua_cc_ui_Text_setFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setFontName", 1},
        {"ccui.Text:setTouchScaleChangeEnabled", "lua_cc_ui_Text_setTouchScaleChangeEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setTouchScaleChangeEnabled", 1},
        {"ccui.Text:setString", "lua_cc_ui_Text_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setString", 1},
        {"ccui.Text:getOutlineSize", "lua_cc_ui_Text_getOutlineSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getOutlineSize", 0},
        {"ccui.Text:getShadowBlurRadius", "lua_cc_ui_Text_getShadowBlurRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getShadowBlurRadius", 0},
        {"ccui.Text:isTouchScaleChangeEnabled", "lua_cc_ui_Text_isTouchScaleChangeEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:isTouchScaleChangeEnabled", 0},
        {"ccui.Text:getFontName", "lua_cc_ui_Text_getFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getFontName", 0},
        {"ccui.Text:getStringLength", "lua_cc_ui_Text_getStringLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getStringLength", 0},
        {"ccui.Text:getType", "lua_cc_ui_Text_getType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getType", 0},
        {"ccui.Text:getTextHorizontalAlignment", "lua_cc_ui_Text_getTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getTextHorizontalAlignment", 0},
        {"ccui.Text:isShadowEnabled", "lua_cc_ui_Text_isShadowEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:isShadowEnabled", 0},
        {"ccui.Text:setFontSize", "lua_cc_ui_Text_setFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setFontSize", 1},
        {"ccui.Text:getLetter", "lua_cc_ui_Text_getLetter", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getLetter", 1},
        {"ccui.Text:getTextVerticalAlignment", "lua_cc_ui_Text_getTextVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getTextVerticalAlignment", 0},
        {"ccui.Text:setTextHorizontalAlignment", "lua_cc_ui_Text_setTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setTextHorizontalAlignment", 1},
        {"ccui.Text:create", "lua_cc_ui_Text_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.Text:create", 0},
        {"ccui.Text:createInstance", "lua_cc_ui_Text_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Text:createInstance", 0},
        {"ccui.TextAtlas:getStringLength", "lua_cc_ui_TextAtlas_getStringLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:getStringLength", 0},
        {"ccui.TextAtlas:getString", "lua_cc_ui_TextAtlas_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:getString", 0},
        {"ccui.TextAtlas:setString", "lua_cc_ui_TextAtlas_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:setString", 1},
        {"ccui.TextAtlas:setProperty", "lua_cc_ui_TextAtlas_setProperty", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:setProperty", 5},
        {"ccui.TextAtlas:create", "lua_cc_ui_TextAtlas_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.TextAtlas:create", 0},
        {"ccui.TextAtlas:createInstance", "lua_cc_ui_TextAtlas_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.TextAtlas:createInstance", 0},
        {"ccui.LoadingBar:setPercent", "lua_cc_ui_LoadingBar_setPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:setPercent", 1},
        {"ccui.LoadingBar:loadTexture", "lua_cc_ui_LoadingBar_loadTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:loadTexture", 1},
        {"ccui.LoadingBar:setDirection", "lua_cc_ui_LoadingBar_setDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:setDirection", 1},
        {"ccui.LoadingBar:setScale9Enabled", "lua_cc_ui_LoadingBar_setScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:setScale9Enabled", 1},
        {"ccui.LoadingBar:getDirection", "lua_cc_ui_LoadingBar_getDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:getDirection", 0},
        {"ccui.LoadingBar:isScale9Enabled", "lua_cc_ui_LoadingBar_isScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:isScale9Enabled", 0},
        {"ccui.LoadingBar:getPercent", "lua_cc_ui_LoadingBar_getPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:getPercent", 0},
        {"ccui.LoadingBar:createInstance", "lua_cc_ui_LoadingBar_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.LoadingBar:createInstance", 0},
        {"ccui.ScrollView:scrollToTop", "lua_cc_ui_ScrollView_scrollToTop", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToTop", 2},
        {"ccui.ScrollView:scrollToPercentHorizontal", "lua_cc_ui_ScrollView_scrollToPercentHorizontal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToPercentHorizontal", 3},
        {"ccui.ScrollView:setScrollBarOpacity", "lua_cc_ui_ScrollView_setScrollBarOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarOpacity", 1},
        {"ccui.ScrollView:setScrollBarEnabled", "lua_cc_ui_ScrollView_setScrollBarEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarEnabled", 1},
        {"ccui.ScrollView:isInertiaScrollEnabled", "lua_cc_ui_ScrollView_isInertiaScrollEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isInertiaScrollEnabled", 0},
        {"ccui.ScrollView:scrollToBottom", "lua_cc_ui_ScrollView_scrollToBottom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToBottom", 2},
        {"ccui.ScrollView:getDirection", "lua_cc_ui_ScrollView_getDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getDirection", 0},
        {"ccui.ScrollView:scrollToBottomLeft", "lua_cc_ui_ScrollView_scrollToBottomLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToBottomLeft", 2},
        {"ccui.ScrollView:getInnerContainer", "lua_cc_ui_ScrollView_getInnerContainer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getInnerContainer", 0},
        {"ccui.ScrollView:jumpToBottom", "lua_cc_ui_ScrollView_jumpToBottom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToBottom", 0},
        {"ccui.ScrollView:setDirection", "lua_cc_ui_ScrollView_setDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setDirection", 1},
        {"ccui.ScrollView:scrollToTopLeft", "lua_cc_ui_ScrollView_scrollToTopLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToTopLeft", 2},
        {"ccui.ScrollView:jumpToTopRight", "lua_cc_ui_ScrollView_jumpToTopRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToTopRight", 0},
        {"ccui.ScrollView:jumpToTop", "lua_cc_ui_ScrollView_jumpToTop", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToTop", 0},
        {"ccui.ScrollView:getScrolledPercentVertical", "lua_cc_ui_ScrollView_getScrolledPercentVertical", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrolledPercentVertical", 0},
        {"ccui.ScrollView:isBounceEnabled", "lua_cc_ui_ScrollView_isBounceEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isBounceEnabled", 0},
        {"ccui.ScrollView:jumpToPercentVertical", "lua_cc_ui_ScrollView_jumpToPercentVertical", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToPercentVertical", 1},
        {"ccui.ScrollView:setScrollBarAutoHideTime", "lua_cc_ui_ScrollView_setScrollBarAutoHideTime", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarAutoHideTime", 1},
        {"ccui.ScrollView:stopScroll", "lua_cc_ui_ScrollView_stopScroll", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:stopScroll", 0},
        {"ccui.ScrollView:setInertiaScrollEnabled", "lua_cc_ui_ScrollView_setInertiaScrollEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setInertiaScrollEnabled", 1},
        {"ccui.ScrollView:setScrollBarAutoHideEnabled", "lua_cc_ui_ScrollView_setScrollBarAutoHideEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarAutoHideEnabled", 1},
        {"ccui.ScrollView:jumpToTopLeft", "lua_cc_ui_ScrollView_jumpToTopLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToTopLeft", 0},
        {"ccui.ScrollView:isScrollBarEnabled", "lua_cc_ui_ScrollView_isScrollBarEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isScrollBarEnabled", 0},
        {"ccui.ScrollView:isAutoScrolling", "lua_cc_ui_ScrollView_isAutoScrolling", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isAutoScrolling", 0},
        {"ccui.ScrollView:jumpToBottomRight", "lua_cc_ui_ScrollView_jumpToBottomRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToBottomRight", 0},
        {"ccui.ScrollView:setTouchTotalTimeThreshold", "lua_cc_ui_ScrollView_setTouchTotalTimeThreshold", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setTouchTotalTimeThreshold", 1},
        {"ccui.ScrollView:getTouchTotalTimeThreshold", "lua_cc_ui_ScrollView_getTouchTotalTimeThreshold", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getTouchTotalTimeThreshold", 0},
        {"ccui.ScrollView:getScrolledPercentHorizontal", "lua_cc_ui_ScrollView_getScrolledPercentHorizontal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrolledPercentHorizontal", 0},
        {"ccui.ScrollView:setBounceEnabled", "lua_cc_ui_ScrollView_setBounceEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setBounceEnabled", 1},
        {"ccui.ScrollView:stopAutoScroll", "lua_cc_ui_ScrollView_stopAutoScroll", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:stopAutoScroll", 0},
        {"ccui.ScrollView:scrollToTopRight", "lua_cc_ui_ScrollView_scrollToTopRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToTopRight", 2},
        {"ccui.ScrollView:isScrolling", "lua_cc_ui_ScrollView_isScrolling", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isScrolling", 0},
        {"ccui.ScrollView:scrollToLeft", "lua_cc_ui_ScrollView_scrollToLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToLeft", 2},
        {"ccui.ScrollView:stopOverallScroll", "lua_cc_ui_ScrollView_stopOverallScroll", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:stopOverallScroll", 0},
        {"ccui.ScrollView:scrollToPercentVertical", "lua_cc_ui_ScrollView_scrollToPercentVertical", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToPercentVertical", 3},
        {"ccui.ScrollView:setScrollBarWidth", "lua_cc_ui_ScrollView_setScrollBarWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarWidth", 1},
        {"ccui.ScrollView:getScrollBarOpacity", "lua_cc_ui_ScrollView_getScrollBarOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarOpacity", 0},
        {"ccui.ScrollView:scrollToBottomRight", "lua_cc_ui_ScrollView_scrollToBottomRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToBottomRight", 2},
        {"ccui.ScrollView:getScrollBarAutoHideTime", "lua_cc_ui_ScrollView_getScrollBarAutoHideTime", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarAutoHideTime", 0},
        {"ccui.ScrollView:jumpToLeft", "lua_cc_ui_ScrollView_jumpToLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToLeft", 0},
        {"ccui.ScrollView:scrollToRight", "lua_cc_ui_ScrollView_scrollToRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToRight", 2},
        {"ccui.ScrollView:getScrollBarWidth", "lua_cc_ui_ScrollView_getScrollBarWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarWidth", 0},
        {"ccui.ScrollView:isScrollBarAutoHideEnabled", "lua_cc_ui_ScrollView_isScrollBarAutoHideEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:isScrollBarAutoHideEnabled", 0},
        {"ccui.ScrollView:jumpToBottomLeft", "lua_cc_ui_ScrollView_jumpToBottomLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToBottomLeft", 0},
        {"ccui.ScrollView:jumpToRight", "lua_cc_ui_ScrollView_jumpToRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToRight", 0},
        {"ccui.ScrollView:jumpToPercentHorizontal", "lua_cc_ui_ScrollView_jumpToPercentHorizontal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToPercentHorizontal", 1},
        {"ccui.ScrollView:create", "lua_cc_ui_ScrollView_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.ScrollView:create", 0},
        {"ccui.ScrollView:createInstance", "lua_cc_ui_ScrollView_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.ScrollView:createInstance", 0},
        {"ccui.ListView:setGravity", "lua_cc_ui_ListView_setGravity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setGravity", 1},
        {"ccui.ListView:removeLastItem", "lua_cc_ui_ListView_removeLastItem", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:removeLastItem", 0},
        {"ccui.ListView:getLeftPadding", "lua_cc_ui_ListView_getLeftPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getLeftPadding", 0},
        {"ccui.ListView:getCenterItemInCurrentView", "lua_cc_ui_ListView_getCenterItemInCurrentView", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getCenterItemInCurrentView", 0},
        {"ccui.ListView:getCurSelectedIndex", "lua_cc_ui_ListView_getCurSelectedIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getCurSelectedIndex", 0},
        {"ccui.ListView:getScrollDuration", "lua_cc_ui_ListView_getScrollDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getScrollDuration", 0},
        {"ccui.ListView:getMagneticAllowedOutOfBoundary", "lua_cc_ui_ListView_getMagneticAllowedOutOfBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getMagneticAllowedOutOfBoundary", 0},
        {"ccui.ListView:getItemsMargin", "lua_cc_ui_ListView_getItemsMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getItemsMargin", 0},
        {"ccui.ListView:setTopPadding", "lua_cc_ui_ListView_setTopPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setTopPadding", 1},
        {"ccui.ListView:getIndex", "lua_cc_ui_ListView_getIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getIndex", 1},
        {"ccui.ListView:pushBackCustomItem", "lua_cc_ui_ListView_pushBackCustomItem", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:pushBackCustomItem", 1},
        {"ccui.ListView:setCurSelectedIndex", "lua_cc_ui_ListView_setCurSelectedIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setCurSelectedIndex", 1},
        {"ccui.ListView:setMagneticType", "lua_cc_ui_ListView_setMagneticType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setMagneticType", 1},
        {"ccui.ListView:setMagneticAllowedOutOfBoundary", "lua_cc_ui_ListView_setMagneticAllowedOutOfBoundary", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setMagneticAllowedOutOfBoundary", 1},
        {"ccui.ListView:getTopmostItemInCurrentView", "lua_cc_ui_ListView_getTopmostItemInCurrentView", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getTopmostItemInCurrentView", 0},
        {"ccui.ListView:setPadding", "lua_cc_ui_ListView_setPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setPadding", 4},
        {"ccui.ListView:removeAllItems", "lua_cc_ui_ListView_removeAllItems", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:removeAllItems", 0},
        {"ccui.ListView:getRightPadding", "lua_cc_ui_ListView_getRightPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getRightPadding", 0},
        {"ccui.ListView:getBottommostItemInCurrentView", "lua_cc_ui_ListView_getBottommostItemInCurrentView", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getBottommostItemInCurrentView", 0},
        {"ccui.ListView:getLeftmostItemInCurrentView", "lua_cc_ui_ListView_getLeftmostItemInCurrentView", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getLeftmostItemInCurrentView", 0},
        {"ccui.ListView:setItemsMargin", "lua_cc_ui_ListView_setItemsMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setItemsMargin", 1},
        {"ccui.ListView:getMagneticType", "lua_cc_ui_ListView_getMagneticType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getMagneticType", 0},
        {"ccui.ListView:getTopPadding", "lua_cc_ui_ListView_getTopPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getTopPadding", 0},
        {"ccui.ListView:pushBackDefaultItem", "lua_cc_ui_ListView_pushBackDefaultItem", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:pushBackDefaultItem", 0},
        {"ccui.ListView:setLeftPadding", "lua_cc_ui_ListView_setLeftPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setLeftPadding", 1},
        {"ccui.ListView:setBottomPadding", "lua_cc_ui_ListView_setBottomPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setBottomPadding", 1},
        {"ccui.ListView:setScrollDuration", "lua_cc_ui_ListView_setScrollDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setScrollDuration", 1},
        {"ccui.ListView:getRightmostItemInCurrentView", "lua_cc_ui_ListView_getRightmostItemInCurrentView", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getRightmostItemInCurrentView", 0},
        {"ccui.ListView:setRightPadding", "lua_cc_ui_ListView_setRightPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setRightPadding", 1},
        {"ccui.ListView:setItemModel", "lua_cc_ui_ListView_setItemModel", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:setItemModel", 1},
        {"ccui.ListView:getBottomPadding", "lua_cc_ui_ListView_getBottomPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getBottomPadding", 0},
        {"ccui.ListView:create", "lua_cc_ui_ListView_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.ListView:create", 0},
        {"ccui.ListView:createInstance", "lua_cc_ui_ListView_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.ListView:createInstance", 0},
        {"ccui.Slider:setPercent", "lua_cc_ui_Slider_setPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setPercent", 1},
        {"ccui.Slider:getMaxPercent", "lua_cc_ui_Slider_getMaxPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getMaxPercent", 0},
        {"ccui.Slider:loadSlidBallTextureNormal", "lua_cc_ui_Slider_loadSlidBallTextureNormal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadSlidBallTextureNormal", 1},
        {"ccui.Slider:loadProgressBarTexture", "lua_cc_ui_Slider_loadProgressBarTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadProgressBarTexture", 1},
        {"ccui.Slider:getSlidBallDisabledRenderer", "lua_cc_ui_Slider_getSlidBallDisabledRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getSlidBallDisabledRenderer", 0},
        {"ccui.Slider:setScale9Enabled", "lua_cc_ui_Slider_setScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setScale9Enabled", 1},
        {"ccui.Slider:getZoomScale", "lua_cc_ui_Slider_getZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getZoomScale", 0},
        {"ccui.Slider:loadSlidBallTextures", "lua_cc_ui_Slider_loadSlidBallTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadSlidBallTextures", 1},
        {"ccui.Slider:getSlidBallRenderer", "lua_cc_ui_Slider_getSlidBallRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getSlidBallRenderer", 0},
        {"ccui.Slider:setMaxPercent", "lua_cc_ui_Slider_setMaxPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setMaxPercent", 1},
        {"ccui.Slider:loadBarTexture", "lua_cc_ui_Slider_loadBarTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadBarTexture", 1},
        {"ccui.Slider:updateVisualSlider", "lua_cc_ui_Slider_updateVisualSlider", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:updateVisualSlider", 0},
        {"ccui.Slider:getSlidBallPressedRenderer", "lua_cc_ui_Slider_getSlidBallPressedRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getSlidBallPressedRenderer", 0},
        {"ccui.Slider:loadSlidBallTexturePressed", "lua_cc_ui_Slider_loadSlidBallTexturePressed", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadSlidBallTexturePressed", 1},
        {"ccui.Slider:isScale9Enabled", "lua_cc_ui_Slider_isScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:isScale9Enabled", 0},
        {"ccui.Slider:getPercent", "lua_cc_ui_Slider_getPercent", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getPercent", 0},
        {"ccui.Slider:loadSlidBallTextureDisabled", "lua_cc_ui_Slider_loadSlidBallTextureDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:loadSlidBallTextureDisabled", 1},
        {"ccui.Slider:getSlidBallNormalRenderer", "lua_cc_ui_Slider_getSlidBallNormalRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getSlidBallNormalRenderer", 0},
        {"ccui.Slider:setZoomScale", "lua_cc_ui_Slider_setZoomScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setZoomScale", 1},
        {"ccui.Slider:create", "lua_cc_ui_Slider_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.Slider:create", 0},
        {"ccui.Slider:createInstance", "lua_cc_ui_Slider_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Slider:createInstance", 0},
        {"ccui.TextField:setAttachWithIME", "lua_cc_ui_TextField_setAttachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setAttachWithIME", 1},
        {"ccui.TextField:getFontSize", "lua_cc_ui_TextField_getFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getFontSize", 0},
        {"ccui.TextField:getString", "lua_cc_ui_TextField_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getString", 0},
        {"ccui.TextField:setPasswordStyleText", "lua_cc_ui_TextField_setPasswordStyleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPasswordStyleText", 1},
        {"ccui.TextField:getDeleteBackward", "lua_cc_ui_TextField_getDeleteBackward", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getDeleteBackward", 0},
        {"ccui.TextField:detachWithIME", "lua_cc_ui_TextField_detachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:detachWithIME", 0},
        {"ccui.TextField:getPlaceHolder", "lua_cc_ui_TextField_getPlaceHolder", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPlaceHolder", 0},
        {"ccui.TextField:getAttachWithIME", "lua_cc_ui_TextField_getAttachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getAttachWithIME", 0},
        {"ccui.TextField:setFontName", "lua_cc_ui_TextField_setFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setFontName", 1},
        {"ccui.TextField:getInsertText", "lua_cc_ui_TextField_getInsertText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getInsertText", 0},
        {"ccui.TextField:setInsertText", "lua_cc_ui_TextField_setInsertText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setInsertText", 1},
        {"ccui.TextField:setString", "lua_cc_ui_TextField_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setString", 1},
        {"ccui.TextField:getDetachWithIME", "lua_cc_ui_TextField_getDetachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getDetachWithIME", 0},
        {"ccui.TextField:setTextVerticalAlignment", "lua_cc_ui_TextField_setTextVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextVerticalAlignment", 1},
        {"ccui.TextField:didNotSelectSelf", "lua_cc_ui_TextField_didNotSelectSelf", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:didNotSelectSelf", 0},
        {"ccui.TextField:getFontName", "lua_cc_ui_TextField_getFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getFontName", 0},
        {"ccui.TextField:attachWithIME", "lua_cc_ui_TextField_attachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:attachWithIME", 0},
        {"ccui.TextField:getStringLength", "lua_cc_ui_TextField_getStringLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getStringLength", 0},
        {"ccui.TextField:setPasswordEnabled", "lua_cc_ui_TextField_setPasswordEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPasswordEnabled", 1},
        {"ccui.TextField:getPasswordStyleText", "lua_cc_ui_TextField_getPasswordStyleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPasswordStyleText", 0},
        {"ccui.TextField:setMaxLengthEnabled", "lua_cc_ui_TextField_setMaxLengthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setMaxLengthEnabled", 1},
        {"ccui.TextField:isPasswordEnabled", "lua_cc_ui_TextField_isPasswordEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:isPasswordEnabled", 0},
        {"ccui.TextField:setDeleteBackward", "lua_cc_ui_TextField_setDeleteBackward", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setDeleteBackward", 1},
        {"ccui.TextField:setCursorPosition", "lua_cc_ui_TextField_setCursorPosition", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setCursorPosition", 1},
        {"ccui.TextField:getTextHorizontalAlignment", "lua_cc_ui_TextField_getTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getTextHorizontalAlignment", 0},
        {"ccui.TextField:setFontSize", "lua_cc_ui_TextField_setFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setFontSize", 1},
        {"ccui.TextField:setPlaceHolder", "lua_cc_ui_TextField_setPlaceHolder", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPlaceHolder", 1},
        {"ccui.TextField:setTextHorizontalAlignment", "lua_cc_ui_TextField_setTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextHorizontalAlignment", 1},
        {"ccui.TextField:getMaxLength", "lua_cc_ui_TextField_getMaxLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getMaxLength", 0},
        {"ccui.TextField:isMaxLengthEnabled", "lua_cc_ui_TextField_isMaxLengthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:isMaxLengthEnabled", 0},
        {"ccui.TextField:setDetachWithIME", "lua_cc_ui_TextField_setDetachWithIME", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setDetachWithIME", 1},
        {"ccui.TextField:getTextVerticalAlignment", "lua_cc_ui_TextField_getTextVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getTextVerticalAlignment", 0},
        {"ccui.TextField:setTouchAreaEnabled", "lua_cc_ui_TextField_setTouchAreaEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTouchAreaEnabled", 1},
        {"ccui.TextField:setMaxLength", "lua_cc_ui_TextField_setMaxLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setMaxLength", 1},
        {"ccui.TextField:setCursorEnabled", "lua_cc_ui_TextField_setCursorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setCursorEnabled", 1},
        {"ccui.TextField:create", "lua_cc_ui_TextField_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.TextField:create", 0},
        {"ccui.TextField:createInstance", "lua_cc_ui_TextField_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.TextField:createInstance", 0},
        {"ccui.TextBMFont:getStringLength", "lua_cc_ui_TextBMFont_getStringLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:getStringLength", 0},
        {"ccui.TextBMFont:getString", "lua_cc_ui_TextBMFont_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:getString", 0},
        {"ccui.TextBMFont:setString", "lua_cc_ui_TextBMFont_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:setString", 1},
        {"ccui.TextBMFont:setFntFile", "lua_cc_ui_TextBMFont_setFntFile", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:setFntFile", 1},
        {"ccui.TextBMFont:resetRender", "lua_cc_ui_TextBMFont_resetRender", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:resetRender", 0},
        {"ccui.TextBMFont:create", "lua_cc_ui_TextBMFont_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.TextBMFont:create", 0},
        {"ccui.TextBMFont:createInstance", "lua_cc_ui_TextBMFont_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.TextBMFont:createInstance", 0},
        {"ccui.PageView:setIndicatorSpaceBetweenIndexNodes", "lua_cc_ui_PageView_setIndicatorSpaceBetweenIndexNodes", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorSpaceBetweenIndexNodes", 1},
        {"ccui.PageView:insertPage", "lua_cc_ui_PageView_insertPage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:insertPage", 2},
        {"ccui.PageView:setIndicatorIndexNodesOpacity", "lua_cc_ui_PageView_setIndicatorIndexNodesOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorIndexNodesOpacity", 1},
        {"ccui.PageView:setIndicatorSelectedIndexOpacity", "lua_cc_ui_PageView_setIndicatorSelectedIndexOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorSelectedIndexOpacity", 1},
        {"ccui.PageView:removeAllPages", "lua_cc_ui_PageView_removeAllPages", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:removeAllPages", 0},
        {"ccui.PageView:setAutoScrollStopEpsilon", "lua_cc_ui_PageView_setAutoScrollStopEpsilon", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setAutoScrollStopEpsilon", 1},
        {"ccui.PageView:setIndicatorIndexNodesScale", "lua_cc_ui_PageView_setIndicatorIndexNodesScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorIndexNodesScale", 1},
        {"ccui.PageView:setIndicatorEnabled", "lua_cc_ui_PageView_setIndicatorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorEnabled", 1},
        {"ccui.PageView:getIndicatorIndexNodesScale", "lua_cc_ui_PageView_getIndicatorIndexNodesScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorIndexNodesScale", 0},
        {"ccui.PageView:getIndicatorSelectedIndexOpacity", "lua_cc_ui_PageView_getIndicatorSelectedIndexOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorSelectedIndexOpacity", 0},
        {"ccui.PageView:getIndicatorIndexNodesOpacity", "lua_cc_ui_PageView_getIndicatorIndexNodesOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorIndexNodesOpacity", 0},
        {"ccui.PageView:getCurrentPageIndex", "lua_cc_ui_PageView_getCurrentPageIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getCurrentPageIndex", 0},
        {"ccui.PageView:removePage", "lua_cc_ui_PageView_removePage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:removePage", 1},
        {"ccui.PageView:setIndicatorIndexNodesTexture", "lua_cc_ui_PageView_setIndicatorIndexNodesTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorIndexNodesTexture", 1},
        {"ccui.PageView:getIndicatorEnabled", "lua_cc_ui_PageView_getIndicatorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorEnabled", 0},
        {"ccui.PageView:getIndicatorSpaceBetweenIndexNodes", "lua_cc_ui_PageView_getIndicatorSpaceBetweenIndexNodes", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorSpaceBetweenIndexNodes", 0},
        {"ccui.PageView:addPage", "lua_cc_ui_PageView_addPage", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:addPage", 1},
        {"ccui.PageView:create", "lua_cc_ui_PageView_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.PageView:create", 0},
        {"ccui.PageView:createInstance", "lua_cc_ui_PageView_createInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.PageView:createInstance", 0},
        {"ccui.Helper:getSubStringOfUTF8String", "lua_cc_ui_Helper_getSubStringOfUTF8String", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:getSubStringOfUTF8String", 3},
        {"ccui.Helper:changeLayoutSystemActiveState", "lua_cc_ui_Helper_changeLayoutSystemActiveState", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:changeLayoutSystemActiveState", 1},
        {"ccui.Helper:seekActionWidgetByActionTag", "lua_cc_ui_Helper_seekActionWidgetByActionTag", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:seekActionWidgetByActionTag", 2},
        {"ccui.Helper:seekWidgetByName", "lua_cc_ui_Helper_seekWidgetByName", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:seekWidgetByName", 2},
        {"ccui.Helper:seekWidgetByTag", "lua_cc_ui_Helper_seekWidgetByTag", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:seekWidgetByTag", 2},
        {"ccui.Helper:doLayout", "lua_cc_ui_Helper_doLayout", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:doLayout", 1},
        {"ccui.RichElement:equalType", "lua_cc_ui_RichElement_equalType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:equalType", 1},
        {"ccui.RichElementImage:setHeight", "lua_cc_ui_RichElementImage_setHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setHeight", 1},
        {"ccui.RichElementImage:setScaleY", "lua_cc_ui_RichElementImage_setScaleY", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setScaleY", 1},
        {"ccui.RichElementImage:setScaleX", "lua_cc_ui_RichElementImage_setScaleX", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setScaleX", 1},
        {"ccui.RichElementImage:setUrl", "lua_cc_ui_RichElementImage_setUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setUrl", 1},
        {"ccui.RichElementImage:setScale", "lua_cc_ui_RichElementImage_setScale", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setScale", 1},
        {"ccui.RichElementImage:setWidth", "lua_cc_ui_RichElementImage_setWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:setWidth", 1},
        {"ccui.RichText:insertElement", "lua_cc_ui_RichText_insertElement", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:insertElement", 2},
        {"ccui.RichText:getFontSize", "lua_cc_ui_RichText_getFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getFontSize", 0},
        {"ccui.RichText:pushBackElement", "lua_cc_ui_RichText_pushBackElement", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:pushBackElement", 1},
        {"ccui.RichText:setAnchorTextBold", "lua_cc_ui_RichText_setAnchorTextBold", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextBold", 1},
        {"ccui.RichText:getAnchorFontColor", "lua_cc_ui_RichText_getAnchorFontColor", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorFontColor", 0},
        {"ccui.RichText:getAnchorTextShadowBlurRadius", "lua_cc_ui_RichText_getAnchorTextShadowBlurRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextShadowBlurRadius", 0},
        {"ccui.RichText:isAnchorTextItalicEnabled", "lua_cc_ui_RichText_isAnchorTextItalicEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextItalicEnabled", 0},
        {"ccui.RichText:setAnchorFontColor", "lua_cc_ui_RichText_setAnchorFontColor", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorFontColor", 1},
        {"ccui.RichText:setFontFace", "lua_cc_ui_RichText_setFontFace", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setFontFace", 1},
        {"ccui.RichText:getHorizontalAlignment", "lua_cc_ui_RichText_getHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getHorizontalAlignment", 0},
        {"ccui.RichText:setHorizontalAlignment", "lua_cc_ui_RichText_setHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setHorizontalAlignment", 1},
        {"ccui.RichText:setAnchorTextDel", "lua_cc_ui_RichText_setAnchorTextDel", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextDel", 1},
        {"ccui.RichText:formatText", "lua_cc_ui_RichText_formatText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:formatText", 0},
        {"ccui.RichText:openUrl", "lua_cc_ui_RichText_openUrl", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:openUrl", 1},
        {"ccui.RichText:getFontFace", "lua_cc_ui_RichText_getFontFace", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getFontFace", 0},
        {"ccui.RichText:setFontColor", "lua_cc_ui_RichText_setFontColor", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setFontColor", 1},
        {"ccui.RichText:isAnchorTextGlowEnabled", "lua_cc_ui_RichText_isAnchorTextGlowEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextGlowEnabled", 0},
        {"ccui.RichText:isAnchorTextUnderlineEnabled", "lua_cc_ui_RichText_isAnchorTextUnderlineEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextUnderlineEnabled", 0},
        {"ccui.RichText:getFontColor", "lua_cc_ui_RichText_getFontColor", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getFontColor", 0},
        {"ccui.RichText:isAnchorTextShadowEnabled", "lua_cc_ui_RichText_isAnchorTextShadowEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextShadowEnabled", 0},
        {"ccui.RichText:getAnchorTextOutlineSize", "lua_cc_ui_RichText_getAnchorTextOutlineSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextOutlineSize", 0},
        {"ccui.RichText:setVerticalSpace", "lua_cc_ui_RichText_setVerticalSpace", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setVerticalSpace", 1},
        {"ccui.RichText:isAnchorTextDelEnabled", "lua_cc_ui_RichText_isAnchorTextDelEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextDelEnabled", 0},
        {"ccui.RichText:setWrapMode", "lua_cc_ui_RichText_setWrapMode", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setWrapMode", 1},
        {"ccui.RichText:setFontSize", "lua_cc_ui_RichText_setFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setFontSize", 1},
        {"ccui.RichText:setAnchorTextItalic", "lua_cc_ui_RichText_setAnchorTextItalic", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextItalic", 1},
        {"ccui.RichText:isAnchorTextBoldEnabled", "lua_cc_ui_RichText_isAnchorTextBoldEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextBoldEnabled", 0},
        {"ccui.RichText:isAnchorTextOutlineEnabled", "lua_cc_ui_RichText_isAnchorTextOutlineEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:isAnchorTextOutlineEnabled", 0},
        {"ccui.RichText:getWrapMode", "lua_cc_ui_RichText_getWrapMode", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getWrapMode", 0},
        {"ccui.RichText:setAnchorTextUnderline", "lua_cc_ui_RichText_setAnchorTextUnderline", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextUnderline", 1},
        {"ccui.RichText:create", "lua_cc_ui_RichText_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichText:create", 0},
        {"ccui.Scale9Sprite:setState", "lua_cc_ui_Scale9Sprite_setState", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setState", 1},
        {"ccui.Scale9Sprite:setInsetBottom", "lua_cc_ui_Scale9Sprite_setInsetBottom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetBottom", 1},
        {"ccui.Scale9Sprite:getSprite", "lua_cc_ui_Scale9Sprite_getSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getSprite", 0},
        {"ccui.Scale9Sprite:setInsetTop", "lua_cc_ui_Scale9Sprite_setInsetTop", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetTop", 1},
        {"ccui.Scale9Sprite:setRenderingType", "lua_cc_ui_Scale9Sprite_setRenderingType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setRenderingType", 1},
        {"ccui.Scale9Sprite:copyTo", "lua_cc_ui_Scale9Sprite_copyTo", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:copyTo", 1},
        {"ccui.Scale9Sprite:getState", "lua_cc_ui_Scale9Sprite_getState", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getState", 0},
        {"ccui.Scale9Sprite:getInsetBottom", "lua_cc_ui_Scale9Sprite_getInsetBottom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetBottom", 0},
        {"ccui.Scale9Sprite:setScale9Enabled", "lua_cc_ui_Scale9Sprite_setScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setScale9Enabled", 1},
        {"ccui.Scale9Sprite:isScale9Enabled", "lua_cc_ui_Scale9Sprite_isScale9Enabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:isScale9Enabled", 0},
        {"ccui.Scale9Sprite:resetRender", "lua_cc_ui_Scale9Sprite_resetRender", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:resetRender", 0},
        {"ccui.Scale9Sprite:getRenderingType", "lua_cc_ui_Scale9Sprite_getRenderingType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getRenderingType", 0},
        {"ccui.Scale9Sprite:getInsetRight", "lua_cc_ui_Scale9Sprite_getInsetRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetRight", 0},
        {"ccui.Scale9Sprite:getInsetTop", "lua_cc_ui_Scale9Sprite_getInsetTop", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetTop", 0},
        {"ccui.Scale9Sprite:setInsetLeft", "lua_cc_ui_Scale9Sprite_setInsetLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetLeft", 1},
        {"ccui.Scale9Sprite:getInsetLeft", "lua_cc_ui_Scale9Sprite_getInsetLeft", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetLeft", 0},
        {"ccui.Scale9Sprite:setInsetRight", "lua_cc_ui_Scale9Sprite_setInsetRight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetRight", 1},
        {"ccui.EditBox:getFontSize", "lua_cc_ui_EditBox_getFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getFontSize", 0},
        {"ccui.EditBox:setMaxLength", "lua_cc_ui_EditBox_setMaxLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setMaxLength", 1},
        {"ccui.EditBox:openKeyboard", "lua_cc_ui_EditBox_openKeyboard", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:openKeyboard", 0},
        {"ccui.EditBox:setFontSize", "lua_cc_ui_EditBox_setFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFontSize", 1},
        {"ccui.EditBox:getText", "lua_cc_ui_EditBox_getText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getText", 0},
        {"ccui.EditBox:getInputMode", "lua_cc_ui_EditBox_getInputMode", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getInputMode", 0},
        {"ccui.EditBox:getPlaceholderFontName", "lua_cc_ui_EditBox_getPlaceholderFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getPlaceholderFontName", 0},
        {"ccui.EditBox:setPlaceholderFontName", "lua_cc_ui_EditBox_setPlaceholderFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFontName", 1},
        {"ccui.EditBox:getPlaceholderFontSize", "lua_cc_ui_EditBox_getPlaceholderFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getPlaceholderFontSize", 0},
        {"ccui.EditBox:getPlaceHolder", "lua_cc_ui_EditBox_getPlaceHolder", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getPlaceHolder", 0},
        {"ccui.EditBox:setFontName", "lua_cc_ui_EditBox_setFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFontName", 1},
        {"ccui.EditBox:setPlaceholderFontSize", "lua_cc_ui_EditBox_setPlaceholderFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFontSize", 1},
        {"ccui.EditBox:loadTextureDisabled", "lua_cc_ui_EditBox_loadTextureDisabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:loadTextureDisabled", 1},
        {"ccui.EditBox:setInputMode", "lua_cc_ui_EditBox_setInputMode", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setInputMode", 1},
        {"ccui.EditBox:getReturnType", "lua_cc_ui_EditBox_getReturnType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getReturnType", 0},
        {"ccui.EditBox:getFontName", "lua_cc_ui_EditBox_getFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getFontName", 0},
        {"ccui.EditBox:closeKeyboard", "lua_cc_ui_EditBox_closeKeyboard", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:closeKeyboard", 0},
        {"ccui.EditBox:loadTexturePressed", "lua_cc_ui_EditBox_loadTexturePressed", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:loadTexturePressed", 1},
        {"ccui.EditBox:getInputFlag", "lua_cc_ui_EditBox_getInputFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getInputFlag", 0},
        {"ccui.EditBox:getTextHorizontalAlignment", "lua_cc_ui_EditBox_getTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getTextHorizontalAlignment", 0},
        {"ccui.EditBox:getScriptEditBoxHandler", "lua_cc_ui_EditBox_getScriptEditBoxHandler", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getScriptEditBoxHandler", 0},
        {"ccui.EditBox:loadTextures", "lua_cc_ui_EditBox_loadTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:loadTextures", 2},
        {"ccui.EditBox:setPlaceHolder", "lua_cc_ui_EditBox_setPlaceHolder", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceHolder", 1},
        {"ccui.EditBox:setInputFlag", "lua_cc_ui_EditBox_setInputFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setInputFlag", 1},
        {"ccui.EditBox:setReturnType", "lua_cc_ui_EditBox_setReturnType", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setReturnType", 1},
        {"ccui.EditBox:loadTextureNormal", "lua_cc_ui_EditBox_loadTextureNormal", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:loadTextureNormal", 1},
        {"ccui.EditBox:getMaxLength", "lua_cc_ui_EditBox_getMaxLength", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getMaxLength", 0},
        {"ccui.EditBox:setText", "lua_cc_ui_EditBox_setText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setText", 1},
        {"ccui.EditBox:setPlaceholderFont", "lua_cc_ui_EditBox_setPlaceholderFont", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFont", 2},
        {"ccui.EditBox:setFont", "lua_cc_ui_EditBox_setFont", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFont", 2},
        {"ccui.EditBox:setTextHorizontalAlignment", "lua_cc_ui_EditBox_setTextHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setTextHorizontalAlignment", 1},
        {"ccui.LayoutComponent:setStretchWidthEnabled", "lua_cc_ui_LayoutComponent_setStretchWidthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setStretchWidthEnabled", 1},
        {"ccui.LayoutComponent:setPercentWidth", "lua_cc_ui_LayoutComponent_setPercentWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentWidth", 1},
        {"ccui.LayoutComponent:setPositionPercentXEnabled", "lua_cc_ui_LayoutComponent_setPositionPercentXEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPositionPercentXEnabled", 1},
        {"ccui.LayoutComponent:setStretchHeightEnabled", "lua_cc_ui_LayoutComponent_setStretchHeightEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setStretchHeightEnabled", 1},
        {"ccui.LayoutComponent:setActiveEnabled", "lua_cc_ui_LayoutComponent_setActiveEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setActiveEnabled", 1},
        {"ccui.LayoutComponent:getRightMargin", "lua_cc_ui_LayoutComponent_getRightMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getRightMargin", 0},
        {"ccui.LayoutComponent:refreshLayout", "lua_cc_ui_LayoutComponent_refreshLayout", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:refreshLayout", 0},
        {"ccui.LayoutComponent:isPercentWidthEnabled", "lua_cc_ui_LayoutComponent_isPercentWidthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isPercentWidthEnabled", 0},
        {"ccui.LayoutComponent:setVerticalEdge", "lua_cc_ui_LayoutComponent_setVerticalEdge", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setVerticalEdge", 1},
        {"ccui.LayoutComponent:getTopMargin", "lua_cc_ui_LayoutComponent_getTopMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getTopMargin", 0},
        {"ccui.LayoutComponent:setSizeWidth", "lua_cc_ui_LayoutComponent_setSizeWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setSizeWidth", 1},
        {"ccui.LayoutComponent:getVerticalEdge", "lua_cc_ui_LayoutComponent_getVerticalEdge", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getVerticalEdge", 0},
        {"ccui.LayoutComponent:setPercentWidthEnabled", "lua_cc_ui_LayoutComponent_setPercentWidthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentWidthEnabled", 1},
        {"ccui.LayoutComponent:isStretchWidthEnabled", "lua_cc_ui_LayoutComponent_isStretchWidthEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isStretchWidthEnabled", 0},
        {"ccui.LayoutComponent:setLeftMargin", "lua_cc_ui_LayoutComponent_setLeftMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setLeftMargin", 1},
        {"ccui.LayoutComponent:getSizeWidth", "lua_cc_ui_LayoutComponent_getSizeWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getSizeWidth", 0},
        {"ccui.LayoutComponent:setPositionPercentYEnabled", "lua_cc_ui_LayoutComponent_setPositionPercentYEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPositionPercentYEnabled", 1},
        {"ccui.LayoutComponent:getSizeHeight", "lua_cc_ui_LayoutComponent_getSizeHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getSizeHeight", 0},
        {"ccui.LayoutComponent:getPositionPercentY", "lua_cc_ui_LayoutComponent_getPositionPercentY", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPositionPercentY", 0},
        {"ccui.LayoutComponent:getPositionPercentX", "lua_cc_ui_LayoutComponent_getPositionPercentX", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPositionPercentX", 0},
        {"ccui.LayoutComponent:setTopMargin", "lua_cc_ui_LayoutComponent_setTopMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setTopMargin", 1},
        {"ccui.LayoutComponent:getPercentHeight", "lua_cc_ui_LayoutComponent_getPercentHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPercentHeight", 0},
        {"ccui.LayoutComponent:getUsingPercentContentSize", "lua_cc_ui_LayoutComponent_getUsingPercentContentSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getUsingPercentContentSize", 0},
        {"ccui.LayoutComponent:setPositionPercentY", "lua_cc_ui_LayoutComponent_setPositionPercentY", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPositionPercentY", 1},
        {"ccui.LayoutComponent:setPositionPercentX", "lua_cc_ui_LayoutComponent_setPositionPercentX", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPositionPercentX", 1},
        {"ccui.LayoutComponent:setRightMargin", "lua_cc_ui_LayoutComponent_setRightMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setRightMargin", 1},
        {"ccui.LayoutComponent:isPositionPercentYEnabled", "lua_cc_ui_LayoutComponent_isPositionPercentYEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isPositionPercentYEnabled", 0},
        {"ccui.LayoutComponent:setPercentHeight", "lua_cc_ui_LayoutComponent_setPercentHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentHeight", 1},
        {"ccui.LayoutComponent:setPercentOnlyEnabled", "lua_cc_ui_LayoutComponent_setPercentOnlyEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentOnlyEnabled", 1},
        {"ccui.LayoutComponent:setHorizontalEdge", "lua_cc_ui_LayoutComponent_setHorizontalEdge", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setHorizontalEdge", 1},
        {"ccui.LayoutComponent:setUsingPercentContentSize", "lua_cc_ui_LayoutComponent_setUsingPercentContentSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setUsingPercentContentSize", 1},
        {"ccui.LayoutComponent:getLeftMargin", "lua_cc_ui_LayoutComponent_getLeftMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getLeftMargin", 0},
        {"ccui.LayoutComponent:setSizeHeight", "lua_cc_ui_LayoutComponent_setSizeHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setSizeHeight", 1},
        {"ccui.LayoutComponent:isPositionPercentXEnabled", "lua_cc_ui_LayoutComponent_isPositionPercentXEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isPositionPercentXEnabled", 0},
        {"ccui.LayoutComponent:getBottomMargin", "lua_cc_ui_LayoutComponent_getBottomMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getBottomMargin", 0},
        {"ccui.LayoutComponent:setPercentHeightEnabled", "lua_cc_ui_LayoutComponent_setPercentHeightEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentHeightEnabled", 1},
        {"ccui.LayoutComponent:isPercentHeightEnabled", "lua_cc_ui_LayoutComponent_isPercentHeightEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isPercentHeightEnabled", 0},
        {"ccui.LayoutComponent:getPercentWidth", "lua_cc_ui_LayoutComponent_getPercentWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPercentWidth", 0},
        {"ccui.LayoutComponent:getHorizontalEdge", "lua_cc_ui_LayoutComponent_getHorizontalEdge", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getHorizontalEdge", 0},
        {"ccui.LayoutComponent:isStretchHeightEnabled", "lua_cc_ui_LayoutComponent_isStretchHeightEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:isStretchHeightEnabled", 0},
        {"ccui.LayoutComponent:setBottomMargin", "lua_cc_ui_LayoutComponent_setBottomMargin", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setBottomMargin", 1},
        {"ccui.LayoutComponent:create", "lua_cc_ui_LayoutComponent_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.LayoutComponent:create", 0},
        {"ccui.LayoutComponent:bindLayoutComponent", "lua_cc_ui_LayoutComponent_bindLayoutComponent", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.LayoutComponent:bindLayoutComponent", 1},
        {"ccui.TabHeader:getIndexInTabControl", "lua_cc_ui_TabHeader_getIndexInTabControl", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getIndexInTabControl", 0},
        {"ccui.TabHeader:getTitleText", "lua_cc_ui_TabHeader_getTitleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getTitleText", 0},
        {"ccui.TabHeader:setTitleFontSize", "lua_cc_ui_TabHeader_setTitleFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:setTitleFontSize", 1},
        {"ccui.TabHeader:setTitleFontName", "lua_cc_ui_TabHeader_setTitleFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:setTitleFontName", 1},
        {"ccui.TabHeader:getTitleFontSize", "lua_cc_ui_TabHeader_getTitleFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getTitleFontSize", 0},
        {"ccui.TabHeader:getTitleFontName", "lua_cc_ui_TabHeader_getTitleFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getTitleFontName", 0},
        {"ccui.TabHeader:getTitleRenderer", "lua_cc_ui_TabHeader_getTitleRenderer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getTitleRenderer", 0},
        {"ccui.TabHeader:setTitleText", "lua_cc_ui_TabHeader_setTitleText", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:setTitleText", 1},
        {"ccui.TabHeader:create", "lua_cc_ui_TabHeader_create", "%s has wrong number of arguments: %d, was expecting %d", "ccui.TabHeader:create", 6},
        {"ccui.TabControl:setHeaderWidth", "lua_cc_ui_TabControl_setHeaderWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:setHeaderWidth", 1},
        {"ccui.TabControl:removeTab", "lua_cc_ui_TabControl_removeTab", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:removeTab", 1},
        {"ccui.TabControl:getTabCount", "lua_cc_ui_TabControl_getTabCount", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getTabCount", 0},
        {"ccui.TabControl:getHeaderDockPlace", "lua_cc_ui_TabControl_getHeaderDockPlace", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getHeaderDockPlace", 0},
        {"ccui.TabControl:getSelectedTabIndex", "lua_cc_ui_TabControl_getSelectedTabIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getSelectedTabIndex", 0},
        {"ccui.TabControl:insertTab", "lua_cc_ui_TabControl_insertTab", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:insertTab", 3},
        {"ccui.TabControl:ignoreHeadersTextureSize", "lua_cc_ui_TabControl_ignoreHeadersTextureSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:ignoreHeadersTextureSize", 1},
        {"ccui.TabControl:getHeaderWidth", "lua_cc_ui_TabControl_getHeaderWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getHeaderWidth", 0},
        {"ccui.TabControl:setHeaderDockPlace", "lua_cc_ui_TabControl_setHeaderDockPlace", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:setHeaderDockPlace", 1},
        {"ccui.TabControl:getTabHeader", "lua_cc_ui_TabControl_getTabHeader", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getTabHeader", 1},
        {"ccui.TabControl:isIgnoreHeadersTextureSize", "lua_cc_ui_TabControl_isIgnoreHeadersTextureSize", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:isIgnoreHeadersTextureSize", 0},
        {"ccui.TabControl:setHeaderSelectedZoom", "lua_cc_ui_TabControl_setHeaderSelectedZoom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:setHeaderSelectedZoom", 1},
        {"ccui.TabControl:setHeaderHeight", "lua_cc_ui_TabControl_setHeaderHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:setHeaderHeight", 1},
        {"ccui.TabControl:indexOfTabHeader", "lua_cc_ui_TabControl_indexOfTabHeader", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:indexOfTabHeader", 1},
        {"ccui.TabControl:getTabContainer", "lua_cc_ui_TabControl_getTabContainer", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getTabContainer", 1},
        {"ccui.TabControl:getHeaderSelectedZoom", "lua_cc_ui_TabControl_getHeaderSelectedZoom", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getHeaderSelectedZoom", 0},
        {"ccui.TabControl:getHeaderHeight", "lua_cc_ui_TabControl_getHeaderHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:getHeaderHeight", 0},
        {"ccui.TabControl:create", "lua_cc_ui_TabControl_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.TabControl:create", 0},
    };
    for (const auto& e : errors) if (std::strcmp(name, e.name) == 0) {
        if (attempted != -1) {
            char text[256];
            std::snprintf(text, sizeof(text), "invalid arguments in function '%s'", e.native);
            tolua_error(L, text, nullptr);
            return 0;
        }
        return luaL_error(L, e.format, e.label, argc, e.expected);
    }
    return luaL_error(L, "unmapped UI binding: %s", name);
}
}
#undef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	ui_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, true); \
	const auto* ui_self = tolua_tousertype(lua_S, 1, nullptr); \
	(void)ui_self; \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = true; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	ui_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, false); \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = false; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto ui_fn = (Fn_); \
		arg_cur = 0; \
		if (ui_binding::prepare(lua_S, LUA_FNAME, ui_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, ui_fn, &native_results); \
			if (ok) { lua_settop(lua_S, 1); return 1; } \
		} \
	}

#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto ui_fn = (Fn_); \
		arg_cur = 0; \
		if (ui_binding::prepare(lua_S, LUA_FNAME, ui_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, ui_fn, &native_results); \
			if (ok) { return native_results; } \
		} \
	}

#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    return ui_binding::fail(lua_S, LUA_FNAME, argc, arg_cur);
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)

// All same-arity legacy groups remain in retained adapters. Keep these aliases
// checked and normalized as well if later audited groups use the suffix.
#undef LUA_TRY_INVOKE_OVERLOAD
#define LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE(ARGC_, Fn_)
#undef LUA_TRY_INVOKE_R_OVERLOAD
#define LUA_TRY_INVOKE_R_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE_R(ARGC_, Fn_)
