/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

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

#pragma once

#include "platform/Namespace.h"

#include "RefCountedExport.h"
#include "Ptr.h"
#include <atomic>
#include <cstdint>

#ifndef CC_REF_LEAK_DETECTION
#define CC_REF_LEAK_DETECTION 0
#endif

namespace cc {

// The counting policy is immutable; host adaptation is checked at its boundary.
enum class RefThreading { Local, Atomic };

class RefCounted;
template<class T, RefThreading Threading, class... Args>
IntrusivePtr<T> makeRef(Args&&... args);

class RefConstructionToken final {
public:
    RefConstructionToken(const RefConstructionToken&) noexcept = default;
private:
    explicit constexpr RefConstructionToken(RefThreading threading) noexcept : _threading(threading) {}
    const RefThreading _threading;
    friend class RefCounted;
    template<class T, RefThreading Threading, class... Args>
    friend IntrusivePtr<T> makeRef(Args&&... args);
};

// Opaque to ordinary counting. Allocated only when host adaptation needs it.
// The definition never depends on CC_ENABLE_SCRIPT_BINDING or a Lua header.
struct RefScriptIdentity {
    int luaID = 0;
    bool rooted = false;
    void* scriptObject = nullptr;
    std::uint64_t vmEpoch = 0;
};

struct RefServices {
    void (*enqueue)(RefCounted&);
    void (*finalRelease)(RefCounted&) noexcept;
    RefScriptIdentity& (*identity)(RefCounted&, RefScriptIdentity*&);
    void (*destroyIdentity)(RefCounted&, RefScriptIdentity&) noexcept;
    // A host may also have live non-Ref clients (for example a raw Lua VM).
    bool (*canRemove)() noexcept = nullptr;
};

// One implementation in the common core, including shared consumers.
CC_REF_API void installRefServices(const RefServices* services);
// Requires host quiescence: no concurrent constructors or calls into the core.
// Refuses removal while any object can still call the service code.
CC_REF_API bool removeRefServices(const RefServices* services) noexcept;
CC_REF_API const RefServices* getRefServices() noexcept;
CC_REF_API unsigned long long liveRefCountedObjects() noexcept;

class CC_REF_API RefCounted {
public:
    RefCounted(const RefCounted&) = delete;
    RefCounted(RefCounted&&) = delete;
    RefCounted& operator=(const RefCounted&) = delete;
    RefCounted& operator=(RefCounted&&) = delete;
    virtual ~RefCounted();

    void addRef() noexcept;
    void retain() { addRef(); }
    void release();
    unsigned int getRefCount() const;
    unsigned int getReferenceCount() const { return getRefCount(); }
    RefThreading getReferenceThreading() const noexcept { return _threading; }

    /** @lua NA */
    unsigned int getScriptObjectID() const;
    /** @lua NA */
    RefScriptIdentity& getScriptIdentity();
    /** @lua NA */
    const RefScriptIdentity* getScriptIdentityIfExists() const noexcept { return _scriptIdentity; }
    /** @lua NA */
    RefCounted* autorelease();

protected:
    // Neither constructor initializes a pool, VM or script identity.
    explicit RefCounted(RefThreading threading = RefThreading::Local);
    explicit RefCounted(RefConstructionToken token);
    // Compatibility extension hook; host checks/cleanup cannot be bypassed by it.
    virtual void onFinalRelease() noexcept {}

private:
    const RefThreading _threading;
    const unsigned int _scriptObjectID;
    union Counter {
        explicit Counter(unsigned int count) : local(count) {}
        ~Counter() {}
        unsigned int local;
        std::atomic<unsigned int> atomic;
    } _counter;
    RefScriptIdentity* _scriptIdentity = nullptr;

    template<class T, RefThreading Threading, class... Args>
    friend IntrusivePtr<T> makeRef(Args&&... args);
#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};

using SCHEDULE_CB = void (RefCounted::*)(float);
#define CC_SCHEDULE_CALLBACK(cb) static_cast<cc::SCHEDULE_CB>(&cb)

} // namespace cc
