//////////////////////////////////////////////////////////////////////////////////////////
// A multi-platform support c++11 library with focus on asynchronous socket I/O for any 
// client application.
//////////////////////////////////////////////////////////////////////////////////////////
/*
The MIT License (MIT)

Copyright (c) 2012-2023 HALX99

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "yasio_cclua.hpp"
#include "base/SimpleTimer.h"
#include "sol/sol.hpp"

namespace lyasio
{
namespace stimer
{
YASIO_LUA_API void clear() { cocos2d::stimer::killAll(false); }
}
}

extern "C" YASIO_LUA_API int luaopen_yasio_cclua(lua_State* L)
{
    int n = luaopen_yasio(L);
    sol::stack_table yasio(L, -1);
    yasio.set_function("delay", [](float delay, cocos2d::stimer::vcallback_t cb) {
        return cocos2d::stimer::delay(delay, std::move(cb), false);
    });
    yasio.set_function("loop", [](unsigned int n, float interval, cocos2d::stimer::vcallback_t cb) {
        return cocos2d::stimer::loop(n, interval, std::move(cb), false);
    });
    yasio.set_function("kill", [](cocos2d::stimer::TIMER_ID id) { cocos2d::stimer::kill(id, false); });
    return n;
}
