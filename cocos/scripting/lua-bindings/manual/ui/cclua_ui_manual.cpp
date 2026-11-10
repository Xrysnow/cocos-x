/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "scripting/lua-bindings/manual/ui/cclua_ui_manual.hpp"
#include "scripting/lua-bindings/auto/cclua_ui_auto.hpp"
#include "scripting/lua-bindings/manual/ui/cclua_ui_values.hpp"
#include "scripting/lua-bindings/manual/lua_conversion/detail/binding_macros.hpp"
#include "base/CCEventListenerFocus.h"
#include "ui/CocosGUI.h"
#if CC_ENABLE_VIDEO_PLATFORM
#include "scripting/lua-bindings/auto/cclua_video_platform_auto.hpp"
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && defined(CC_ENABLE_MSEDGE_WEBVIEW2) && CC_ENABLE_MSEDGE_WEBVIEW2)
#include "scripting/lua-bindings/auto/cclua_webview_auto.hpp"
#endif

namespace ui_binding
{
struct HitTestOutput
{
    lua_State* state = nullptr;
    int index = 0;
    void write(const cocos2d::Vec3& value) const
    {
        lua::native_to_luaval_field(state, index, "x", value.x);
        lua::native_to_luaval_field(state, index, "y", value.y);
        lua::native_to_luaval_field(state, index, "z", value.z);
    }
};
}

namespace lua
{
template<> struct to_native<ui_binding::HitTestOutput>
{
    static bool F(lua_State* L, int index, ui_binding::HitTestOutput* output, const char* = "")
    {
        // This is an output carrier, so its initial fields need not exist.
        if (!L || !output || !lua_istable(L, index)) return false;
        *output = {L, _absolute_index(L, index)};
        return true;
    }
};
}

namespace
{
int widgetHitTest(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccui.Widget", "ccui.Widget:hitTest");
    const auto plain = [](const cocos2d::ui::Widget* self, const cocos2d::Vec2& point,
                          const cocos2d::Camera* camera) { return self->hitTest(point, camera, nullptr); };
    const auto output = [](const cocos2d::ui::Widget* self, const cocos2d::Vec2& point,
                           const cocos2d::Camera* camera, ui_binding::HitTestOutput out) {
        cocos2d::Vec3 intersection;
        const bool hit = self->hitTest(point, camera, &intersection);
        out.write(intersection);
        return hit;
    };
    LUA_TRY_INVOKE_R(2, plain);
    LUA_TRY_INVOKE_R(3, output);
    LUA_INVOKE_FOOTER("2,3");
}

int textFieldSetCursorChar(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccui.TextField", "ccui.TextField:setCursorChar");
    const auto narrow = [](cocos2d::ui::TextField* self, int value) {
        self->setCursorChar(static_cast<char>(value));
    };
    LUA_TRY_INVOKE(1, narrow);
    LUA_INVOKE_FOOTER("1");
}

int editBoxUnregister(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccui.EditBox", "ccui.EditBox:unregisterScriptEditBoxHandler");
    const auto clear = [](cocos2d::ui::EditBox* self) { self->setScriptEditBoxCallback(nullptr); };
    LUA_TRY_INVOKE(0, clear);
    LUA_INVOKE_FOOTER("0");
}

int focusRegister(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:registerScriptHandler");
    const auto assign = [](cocos2d::EventListenerFocus* self,
                           std::function<void(cocos2d::ui::Widget*, cocos2d::ui::Widget*)> callback) {
        self->onFocusChanged = std::move(callback);
    };
    LUA_TRY_INVOKE(1, assign);
    LUA_INVOKE_FOOTER("1");
}

void extend(lua_State* L, const char* name, const luaL_Reg* methods)
{
    lua_getfield(L, LUA_REGISTRYINDEX, name);
    if (lua_istable(L, -1))
        for (const luaL_Reg* method = methods; method->name; ++method)
            tolua_function(L, method->name, method->func);
    lua_pop(L, 1);
}
}

int register_all_cc_ui_manual(lua_State* L)
{
    const luaL_Reg widget[] = {{"hitTest", widgetHitTest}, {nullptr, nullptr}};
    const luaL_Reg field[] = {{"setCursorChar", textFieldSetCursorChar}, {nullptr, nullptr}};
    const luaL_Reg edit[] = {{"unregisterScriptEditBoxHandler", editBoxUnregister}, {nullptr, nullptr}};
    const luaL_Reg focus[] = {{"registerScriptHandler", focusRegister}, {nullptr, nullptr}};
    extend(L, "ccui.Widget", widget);
    extend(L, "ccui.TextField", field);
    extend(L, "ccui.EditBox", edit);
    // Core is the only owner of the Focus class, parent and collector.
    extend(L, "cc.EventListenerFocus", focus);
    return 0;
}

int register_ui_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1))  // stack:...,_G,
    {
        register_all_cc_ui(L);
        register_all_cc_ui_manual(L);
#if CC_ENABLE_VIDEO_PLATFORM
        register_all_cc_video_platform(L);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && defined(CC_ENABLE_MSEDGE_WEBVIEW2) && CC_ENABLE_MSEDGE_WEBVIEW2)
        register_all_cc_webview(L);
#endif
    }
    lua_pop(L, 1);

    return 1;
}
