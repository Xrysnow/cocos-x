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

#include "base/CCRef.h"
#include "base/CCAutoreleasePool.h"
#include "base/ccMacros.h"
#include "base/CCScriptSupport.h"

#if CC_REF_LEAK_DETECTION
    #include <algorithm>  // std::find
    #include <thread>
    #include <mutex>
    #include <vector>
#endif

NS_CC_BEGIN

#if CC_REF_LEAK_DETECTION
static void trackRef(Ref* ref);
static void untrackRef(Ref* ref);
#endif

Ref::Ref()
    : _referenceCount(1)  // when the Ref is created, the reference count of it is 1
#if CC_ENABLE_SCRIPT_BINDING
    , _luaID(0)
    , _scriptObject(nullptr)
    , _rooted(false)
#endif
{
#if CC_ENABLE_SCRIPT_BINDING
    static unsigned int uObjectCount = 0;
    _ID                              = ++uObjectCount;
#endif

#if CC_REF_LEAK_DETECTION
    trackRef(this);
#endif
}

Ref::~Ref()
{
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* pEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (pEngine != nullptr && _luaID)
    {
        // if the object is referenced by Lua engine, remove it
        pEngine->removeScriptObjectByObject(this);
    }
#endif  // CC_ENABLE_SCRIPT_BINDING

#if CC_REF_LEAK_DETECTION
    if (_referenceCount != 0)
        untrackRef(this);
#endif
}

void Ref::retain()
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    ++_referenceCount;
}

void Ref::release()
{
#if defined(CC_DEBUG) && (CC_DEBUG > 0)
    if (_referenceCount <= 0)
    {
        print("Ref::release: invalid reference count in %s, got %d", typeid(*this).name(), _referenceCount);
        CCASSERT(false, "reference count should be greater than 0");
    }
#endif
    --_referenceCount;

    if (_referenceCount == 0)
    {
#if defined(CC_DEBUG) && (CC_DEBUG > 0)
        auto poolManager = PoolManager::getInstance();
        if (!poolManager->getCurrentPool()->isClearing() && poolManager->isObjectInPools(this))
        {
            // Trigger an assert if the reference count is 0 but the Ref is still in autorelease pool.
            // This happens when 'autorelease/release' were not used in pairs with 'new/retain'.
            //
            // Wrong usage (1):
            //
            // auto obj = Node::create();   // Ref = 1, but it's an autorelease Ref which means it was in the
            // autorelease pool. obj->autorelease();   // Wrong: If you wish to invoke autorelease several times, you
            // should retain `obj` first.
            //
            // Wrong usage (2):
            //
            // auto obj = Node::create();
            // obj->release();   // Wrong: obj is an autorelease Ref, it will be released when clearing current pool.
            //
            // Correct usage (1):
            //
            // auto obj = Node::create();
            //                     |-   new Node();     // `new` is the pair of the `autorelease` of next line
            //                     |-   autorelease();  // The pair of `new Node`.
            //
            // obj->retain();
            // obj->autorelease();  // This `autorelease` is the pair of `retain` of previous line.
            //
            // Correct usage (2):
            //
            // auto obj = Node::create();
            // obj->retain();
            // obj->release();   // This `release` is the pair of `retain` of previous line.
            CCASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
        }
#endif

#if CC_REF_LEAK_DETECTION
        untrackRef(this);
#endif
        delete this;
    }
}

Ref* Ref::autorelease()
{
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

#if CC_REF_LEAK_DETECTION

static std::vector<Ref*> __refAllocationList;
static std::mutex __refMutex;

void Ref::printLeaks()
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    // Dump Ref object memory leaks
    if (__refAllocationList.empty())
    {
        log("[memory] All Ref objects successfully cleaned up (no leaks detected).\n");
    }
    else
    {
        log("[memory] WARNING: %d Ref objects still active in memory.\n", (int)__refAllocationList.size());

        for (const auto& ref : __refAllocationList)
        {
            CC_ASSERT(ref);
            const char* type = typeid(*ref).name();
            log("[memory] LEAK: Ref object '%s' still active with reference count %d.\n", (type ? type : ""),
                ref->getReferenceCount());
        }
    }
}

static void trackRef(Ref* ref)
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    CCASSERT(ref, "Invalid parameter, ref should not be null!");

    // Create memory allocation record.
    __refAllocationList.emplace_back(ref);
}

static void untrackRef(Ref* ref)
{
    std::lock_guard<std::mutex> refLockGuard(__refMutex);
    auto iter = std::find(__refAllocationList.begin(), __refAllocationList.end(), ref);
    if (iter == __refAllocationList.end())
    {
        log("[memory] CORRUPTION: Attempting to free (%s) with invalid ref tracking record.\n", typeid(*ref).name());
        return;
    }

    __refAllocationList.erase(iter);
}

#endif  // #if CC_REF_LEAK_DETECTION

NS_CC_END
