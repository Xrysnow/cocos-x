/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies
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

#ifndef __BASE_CCREF_H__
#define __BASE_CCREF_H__

#include "platform/CCPlatformMacros.h"
#include "base/ccConfig.h"
#include "base/RefCounted.h"
#include <type_traits>

NS_CC_BEGIN
using Ref = cc::RefCounted;
template<class T> using RefPtr = cc::IntrusivePtr<T>;

// Explicit host startup/VM lifetime. These never belong to gfx-only consumers.
CC_DLL void initializeCocosRefServices();
CC_DLL void requireRefHostThread();
CC_DLL bool isRefScriptContext(void* context) noexcept;
// Returns the active context only on its host thread, without touching Lua.
CC_DLL void* getRefScriptContext() noexcept;
using ScriptObjectCleanup = void (*)(void*,Ref*,int) noexcept;
CC_DLL void openCocosScriptContext(void* context, ScriptObjectCleanup cleanup);
CC_DLL void closeCocosScriptContext(void* context) noexcept;

template<class T> class Clonable {
public:
    virtual cc::IntrusivePtr<T> clone() const = 0;
    virtual ~Clonable() = default;
};

class Node;
template<class T> T* transferToAutoreleasePool(cc::IntrusivePtr<T>&& owner) {
    static_assert(std::is_convertible_v<T*,const Ref*>,"Pool transfer requires a public unambiguous RefCounted base");
    if(owner) const_cast<std::remove_const_t<T>*>(owner.get())->autorelease();
    return owner.detach();
}

typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Node*);
typedef void (Ref::*SEL_CallFuncND)(Node*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define CC_CALLFUNC_SELECTOR(_SELECTOR) static_cast<cc::SEL_CallFunc>(&_SELECTOR)
#define CC_CALLFUNCN_SELECTOR(_SELECTOR) static_cast<cc::SEL_CallFuncN>(&_SELECTOR)
#define CC_CALLFUNCND_SELECTOR(_SELECTOR) static_cast<cc::SEL_CallFuncND>(&_SELECTOR)
#define CC_CALLFUNCO_SELECTOR(_SELECTOR) static_cast<cc::SEL_CallFuncO>(&_SELECTOR)
#define CC_MENU_SELECTOR(_SELECTOR) static_cast<cc::SEL_MenuHandler>(&_SELECTOR)
#define CC_SCHEDULE_SELECTOR(_SELECTOR) static_cast<cc::SEL_SCHEDULE>(&_SELECTOR)

NS_CC_END
#endif
