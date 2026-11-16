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
#include <atomic>
#include "gfx/base/Ptr.h"
#include "gfx/base/RefCounted.h"

#define CC_REF_LEAK_DETECTION 0

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

class Ref;

/** Reference-count policy, fixed for the entire lifetime of an object.
 * Atomic protects reference counting only, not object state or autorelease pools.
 * @lua NA
 * @js NA
 */
using RefThreading = cc::RefThreading;

template <class T>
using RefPtr = cc::IntrusivePtr<T>;

template <class T, RefThreading Threading, class... Args>
cc::IntrusivePtr<T> makeRef(Args&&... args);

/** Construction-only policy token supplied by makeRef<T, Threading>().
 * Opt-in constructors must forward this token to their Ref base constructor.
 * @lua NA
 * @js NA
 */
class RefConstructionToken final
{
public:
    RefConstructionToken(const RefConstructionToken&) noexcept = default;

private:
    explicit constexpr RefConstructionToken(RefThreading threading) noexcept : _threading(threading) {}

    const RefThreading _threading;

    friend class Ref;
    template <class T, RefThreading Threading, class... Args>
    friend cc::IntrusivePtr<T> makeRef(Args&&... args);
};

/**
 * Interface that defines how to clone an Ref.
 * @lua NA
 * @js NA
 */
template <class T>
class Clonable
{
public:
    /** Returns a copy of the Ref. */
    virtual cc::IntrusivePtr<T> clone() const = 0;

    /**
     * @js NA
     * @lua NA
     */
    virtual ~Clonable(){};
};

/**
 * Ref is used for reference count management. If a class inherits from Ref,
 * then it is easy to be shared in different places.
 * @js NA
 */
class CC_DLL Ref : public cc::RefCounted
{
public:
    Ref(const Ref&) = delete;
    Ref(Ref&&) = delete;
    Ref& operator=(const Ref&) = delete;
    Ref& operator=(Ref&&) = delete;

    /**
     * Retains the ownership.
     *
     * This increases the Ref's reference count.
     * The caller must already have a live reference; this cannot revive an object.
     * Concurrent calls are supported only for the Atomic policy.
     *
     * @see release, autorelease
     * @js NA
     */
    void retain();

    /** Unified intrusive-pointer protocol; retains one existing live reference.
     * @lua NA
     * @js NA
     */
    using cc::RefCounted::addRef;

    /**
     * Releases the ownership immediately.
     *
     * This decrements the Ref's reference count.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @see retain, autorelease
     * @js NA
     */
    // Keep the legacy pointer-to-member type used by Lua bindings. Both entry
    // points run the same counter algorithm and virtual final-release hook.
    void release() { cc::RefCounted::release(); }

    /**
     * Releases the ownership sometime soon automatically.
     *
     * This decrements the Ref's reference count at the end of current
     * autorelease pool block.
     *
     * If the reference count reaches 0 after the decrement, this Ref is
     * destructed.
     *
     * @returns The Ref itself.
     *
     * @see AutoreleasePool, retain, release
     * @js NA
     * @lua NA
     */
    Ref* autorelease();

    /**
     * Returns the Ref's current reference count.
     * For Atomic objects this is a snapshot, not an exclusivity or lifetime test.
     *
     * @returns The Ref's reference count.
     * @js NA
     */
    unsigned int getReferenceCount() const;

    /** Returns the immutable reference-count policy.
     * @lua NA
     * @js NA
     */
    using cc::RefCounted::getReferenceThreading;

protected:
    /**
     * Constructor
     *
     * The Ref's reference count is 0 after construction.
     * Immediately establish ownership with cc::IntrusivePtr<T>{new T(...)}.
     * Stack and embedded values stay unowned and are destroyed naturally.
     * Existing default construction always selects the Local policy.
     * @js NA
     */
    Ref();

    /** Opt in to a policy selected by makeRef<T, Threading>().
     * Every constructor in a participating inheritance chain must forward token.
     * @lua NA
     * @js NA
     */
    explicit Ref(RefConstructionToken token);

    void onFinalRelease() noexcept override;

public:
    /**
     * Destructor
     *
     * @js NA
     * @lua NA
     */
    virtual ~Ref();

private:
    template <class T, RefThreading Threading, class... Args>
    friend cc::IntrusivePtr<T> makeRef(Args&&... args);

#if CC_ENABLE_SCRIPT_BINDING
public:
    /// object id, ScriptSupport need public _ID
    unsigned int _ID;
    /// Lua reference id
    int _luaID;
    /**
     When true, it means that the object was already rooted.
     */
    bool _rooted;
    /// scriptObject, support for swift
    void* _scriptObject;

#endif

    // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

class Node;

/** Transfer exactly one owned share. Keep the owner intact if enqueue throws. */
template <class T>
T* transferToAutoreleasePool(cc::IntrusivePtr<T>&& owner)
{
    static_assert(std::is_convertible<T*, const Ref*>::value, "Only cocos Ref objects use this pool");
    if (owner)
        const_cast<std::remove_const_t<T>*>(owner.get())->autorelease();
    return owner.detach();
}

typedef void (Ref::*SEL_CallFunc)();
typedef void (Ref::*SEL_CallFuncN)(Node*);
typedef void (Ref::*SEL_CallFuncND)(Node*, void*);
typedef void (Ref::*SEL_CallFuncO)(Ref*);
typedef void (Ref::*SEL_MenuHandler)(Ref*);
typedef void (Ref::*SEL_SCHEDULE)(float);

#define CC_CALLFUNC_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFunc>(&_SELECTOR)
#define CC_CALLFUNCN_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncN>(&_SELECTOR)
#define CC_CALLFUNCND_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncND>(&_SELECTOR)
#define CC_CALLFUNCO_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_CallFuncO>(&_SELECTOR)
#define CC_MENU_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_MenuHandler>(&_SELECTOR)
#define CC_SCHEDULE_SELECTOR(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)

NS_CC_END
// end of base group
/** @} */

#endif  // __BASE_CCREF_H__
