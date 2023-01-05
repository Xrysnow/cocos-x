/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021-2022 Bytedance Inc.

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
#include "scripting/lua-bindings/manual/ui/axlua_video_manual.hpp"

#include "ui/UIVideoPlayer/UIVideoPlayer.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

static int axlua_video_VideoPlayer_addEventListener(lua_State* L)
{

    int argc                       = 0;
    cocos2d::ui::VideoPlayer* self = nullptr;

#    if _CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "axui.VideoPlayer", 0, &tolua_err))
        goto tolua_lerror;
#    endif

    self = static_cast<cocos2d::ui::VideoPlayer*>(tolua_tousertype(L, 1, 0));

#    if _CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'axlua_Widget_addTouchEventListener'\n", nullptr);
        return 0;
    }
#    endif

    argc = lua_gettop(L) - 1;

    if (argc == 1)
    {
#    if _CC_DEBUG >= 1
        if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#    endif

        LUA_FUNCTION handler = (toluafix_ref_function(L, 2, 0));

        self->addEventListener([=](cocos2d::Ref* ref, cocos2d::ui::VideoPlayer::EventType eventType) {
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

            stack->pushObject(ref, "cc.Ref");
            stack->pushInt((int)eventType);

            stack->executeFunctionByHandler(handler, 2);
        });

        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "axui.VideoPlayer:addEventListener",
               argc, 0);
    return 0;
#    if _CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'axlua_VideoPlayer_addEventListener'.", &tolua_err);
#    endif
    return 0;
}

static void extendVideoPlayer(lua_State* L)
{
    lua_pushstring(L, "axui.VideoPlayer");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "addEventListener", axlua_video_VideoPlayer_addEventListener);
    }
    lua_pop(L, 1);
}

int register_all_ax_video_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendVideoPlayer(L);

    return 0;
}
