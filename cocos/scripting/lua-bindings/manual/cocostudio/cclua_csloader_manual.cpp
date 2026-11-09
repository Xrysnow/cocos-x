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
#include "scripting/lua-bindings/manual/cocostudio/cclua_csloader_manual.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/ActionTimeline/CSLoader.h"

namespace
{
// This parameter is a native precondition, not a second Lua userdata type.
struct CSLoaderSender
{
    cocos2d::ui::Widget* value = nullptr;
};
}

namespace lua
{
template<>
struct binding_argument<CSLoaderSender>
{
    CSLoaderSender value;
    template<bool Checked>
    bool read(lua_State* L, int index)
    {
        return binding_read<cocos2d::ui::Widget*>::template F<Checked>(L, index, &value.value)
            && value.value != nullptr;
    }
    CSLoaderSender get() { return value; }
};
}

static int csloader_bindCallback(lua_State* lua_S)
{
    LUA_INVOKE_HEADER("cc.CSLoader", "cc.CSLoader:bindCallback");
    const auto bind = [](cocos2d::CSLoader* self, std::string_view name, std::string_view type,
                         CSLoaderSender sender, cocos2d::Node* handler) {
        return self->bindCallback(name, type, sender.value, handler);
    };
    LUA_TRY_INVOKE_R(4, bind);
    LUA_INVOKE_FOOTER("4");
}

int register_all_cc_csloader_manual(lua_State* L)
{
    luaL_getmetatable(L, "cc.CSLoader");
    tolua_function(L, "bindCallback", csloader_bindCallback);
    lua_pop(L, 1);
    return 0;
}
