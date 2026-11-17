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
#include "base/Macros.h"
#include <atomic>
#include <mutex>
#include <thread>
#include <stdexcept>
#include <cstdio>
#include <exception>

NS_CC_BEGIN
namespace {
struct HostState {
    std::thread::id thread;
    std::atomic<void*> context{nullptr};
    std::atomic<ScriptObjectCleanup> cleanup{nullptr};
    std::atomic<std::uint64_t> epoch{0};
};
HostState& state() { static HostState value; return value; }
void requireHostThread() {
    if(state().thread != std::this_thread::get_id())
        throw std::logic_error("Cocos script identity/pool access requires its host thread");
}
void enqueue(cc::RefCounted& ref) {
    requireHostThread();
    auto* manager=PoolManager::getInstanceIfExists();
    auto* pool=manager ? manager->getCurrentPoolIfExists() : nullptr;
    if(!pool) throw std::logic_error("Cocos autorelease pool is not initialized or has closed");
    pool->addObject(&ref);
}
void finalRelease(cc::RefCounted& ref) noexcept {
#if defined(CC_DEBUG) && CC_DEBUG > 0
    // A serially owned Local object may be worker-local; host pools are not.
    if(state().thread != std::this_thread::get_id()) return;
    auto* manager=PoolManager::getInstanceIfExists();
    if(manager && manager->isObjectInPools(&ref))
        CCASSERT(false,"The reference shouldn't be 0 because it is still in autorelease pool.");
#endif
}
cc::RefScriptIdentity& identity(cc::RefCounted&, cc::RefScriptIdentity*& slot) {
    requireHostThread();
    if(!slot) slot=new cc::RefScriptIdentity;
    auto& host=state();
    if(slot->vmEpoch != host.epoch) {
        slot->luaID=0;
        slot->rooted=false;
        slot->vmEpoch=host.epoch;
    }
    return *slot;
}
void destroyIdentity(cc::RefCounted& ref, cc::RefScriptIdentity& script) noexcept {
    if(!script.luaID) return;
    auto& host=state();
    if(script.vmEpoch != host.epoch || !host.context) return;
    if(host.thread != std::this_thread::get_id()) {
        std::fputs("Cocos Lua-bound object destroyed outside scripting thread\n",stderr);
        std::terminate();
    }
    const int id=script.luaID;
    script.luaID=0;
    const auto context=host.context.load(std::memory_order_acquire);
    const auto cleanup=host.cleanup.load(std::memory_order_acquire);
    if(cleanup) cleanup(context,&ref,id);
}
bool canRemove() noexcept { return state().context.load(std::memory_order_acquire)==nullptr; }
const cc::RefServices services{enqueue,finalRelease,identity,destroyIdentity,canRemove};
}
void initializeCocosRefServices() {
    // Initialization is explicit and thread-confined, like PoolManager and Lua.
    if(!cc::getRefServices()) state().thread=std::this_thread::get_id();
    cc::installRefServices(&services);
    requireHostThread();
}
void requireRefHostThread() {
    if (!cc::getRefServices()) throw std::logic_error("Ref host services are not initialized");
    requireHostThread();
}
bool isRefScriptContext(void* context) noexcept {
    return context && getRefScriptContext()==context;
}
void* getRefScriptContext() noexcept {
    const auto& host=state();
    return host.thread==std::this_thread::get_id() ? host.context.load(std::memory_order_acquire) : nullptr;
}
void openCocosScriptContext(void* context, ScriptObjectCleanup cleanup) {
    if(!context || !cleanup) throw std::invalid_argument("Script context and cleanup callback are required");
    initializeCocosRefServices();
    requireHostThread();
    auto& host=state();
    if(host.context && host.context != context)
        throw std::logic_error("Only one cocos script context can be active per core");
    if(host.context != context) ++host.epoch;
    host.context=context;
    host.cleanup=cleanup;
}
void closeCocosScriptContext(void* context) noexcept {
    if(!context) return;
    auto& host=state();
    if(host.context == context) {
        if(host.thread != std::this_thread::get_id()) std::terminate();
        host.context=nullptr;
        host.cleanup=nullptr;
        ++host.epoch;
    }
}
NS_CC_END
