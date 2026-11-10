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
#include "scripting/lua-bindings/manual/cocostudio/cclua_cocostudio_manual.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_csloader_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/CocoStudio.h"

namespace studio_binding {
struct AnimationSnapshot {
    std::string name;
    int startIndex = 0;
    int endIndex = 0;
};
struct AnimationResult {
    bool present = false;
    AnimationSnapshot value;
};
}

namespace lua {
LUA_TO_NATIVE_STRUCT3(studio_binding::AnimationSnapshot, name, startIndex, endIndex);
LUA_TO_LUA_STRUCT3(studio_binding::AnimationSnapshot, name, startIndex, endIndex);
template<> struct to_lua<studio_binding::AnimationResult> {
    static void F(lua_State* L, const studio_binding::AnimationResult& result) {
        if (result.present) native_to_luaval(L, result.value);
        else lua_pushnil(L);
    }
};
}

static int studio_addAnimationInfo(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:addAnimationInfo");
    const auto add = [](cocostudio::timeline::ActionTimeline* self, const studio_binding::AnimationSnapshot& value) {
        self->addAnimationInfo(cocostudio::timeline::AnimationInfo(value.name, value.startIndex, value.endIndex));
    };
    LUA_TRY_INVOKE(1, add);
    LUA_INVOKE_FOOTER("1");
}

static int studio_getAnimationInfo(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getAnimationInfo");
    const auto get = [](cocostudio::timeline::ActionTimeline* self, std::string_view name) {
        studio_binding::AnimationResult result;
        if (self->IsAnimationInfoExists(name)) {
            const auto& info = self->getAnimationInfo(name);
            result = {true, {info.name, info.startIndex, info.endIndex}};
        }
        return result;
    };
    LUA_TRY_INVOKE_R(1, get);
    LUA_INVOKE_FOOTER("1");
}

int register_all_cc_coco_studio_manual(lua_State* L)
{
    luaL_getmetatable(L, "ccs.ActionTimeline");
    tolua_function(L, "addAnimationInfo", studio_addAnimationInfo);
    tolua_function(L, "getAnimationInfo", studio_getAnimationInfo);
    lua_pop(L, 1);
    return 0;
}

int register_cocostudio_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1)) {
        register_all_cc_studio(L);
        register_all_cc_csloader(L);
        register_all_cc_coco_studio_manual(L);
    }
    lua_pop(L, 1);
    return 1;
}
