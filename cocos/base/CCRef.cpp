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
    : Ref(RefConstructionToken(RefThreading::Local))
{}

Ref::Ref(RefConstructionToken token)
    : cc::RefCounted(token._threading)
#if CC_ENABLE_SCRIPT_BINDING
    , _luaID(0)
    , _rooted(false)
    , _scriptObject(nullptr)
#endif
{
#if CC_ENABLE_SCRIPT_BINDING
    static std::atomic<unsigned int> uObjectCount{0};
    _ID = uObjectCount.fetch_add(1, std::memory_order_relaxed) + 1;
#endif

#if CC_REF_LEAK_DETECTION
    trackRef(this);
#endif
}

Ref::~Ref()
{
#if CC_ENABLE_SCRIPT_BINDING
    // Unbound objects may be destroyed on a worker without touching the script singleton.
    // Lua-bound objects still require destruction on the scripting thread.
    if (_luaID)
    {
        auto* manager = ScriptEngineManager::getInstanceIfExists();
        ScriptEngineProtocol* pEngine = manager ? manager->getScriptEngine() : nullptr;
        if (pEngine != nullptr)
        {
            // if the object is referenced by Lua engine, remove it
            pEngine->removeScriptObjectByObject(this);
        }
    }
#endif  // CC_ENABLE_SCRIPT_BINDING

#if CC_REF_LEAK_DETECTION
    untrackRef(this);
#endif
}

void Ref::retain()
{
    addRef();
}

void Ref::onFinalRelease() noexcept
{
#if defined(CC_DEBUG) && (CC_DEBUG > 0)
    // This hook also runs when the last owner holds a cc::RefCounted*.
    // Atomic owners must never query the thread-confined pool manager.
    if (getReferenceThreading() == RefThreading::Local)
    {
        auto* manager = PoolManager::getInstanceIfExists();
        if (manager && manager->isObjectInPools(this))
            CCASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
    }
#endif
}

Ref* Ref::autorelease()
{
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return getRefCount();
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
