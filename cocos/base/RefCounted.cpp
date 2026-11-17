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

#include "base/RefCounted.h"
#include "Log.h"
#include <new>
#include <stdexcept>
#include <mutex>
#include <vector>
#include <algorithm>

namespace cc {
namespace {
std::atomic<const RefServices*> services{nullptr};
std::atomic<unsigned long long> liveObjects{0};
std::atomic<unsigned int> scriptSequence{0};
#if CC_REF_LEAK_DETECTION
std::mutex leakMutex;
std::vector<RefCounted*> leakObjects;
#endif
}

void installRefServices(const RefServices* value) {
    if (!value || !value->enqueue || !value->finalRelease || !value->identity || !value->destroyIdentity)
        throw std::invalid_argument("Incomplete Ref host service table");
    const RefServices* expected = nullptr;
    if (!services.compare_exchange_strong(expected,value,std::memory_order_acq_rel,std::memory_order_acquire) && expected != value)
        throw std::logic_error("Ref host services already installed by another core");
}
bool removeRefServices(const RefServices* value) noexcept {
    if(!value) return false;
    if(services.load(std::memory_order_acquire) != value) return false;
    if (liveObjects.load(std::memory_order_acquire) != 0) return false;
    if(value->canRemove && !value->canRemove()) return false;
    return services.compare_exchange_strong(value,nullptr,std::memory_order_acq_rel);
}
const RefServices* getRefServices() noexcept { return services.load(std::memory_order_acquire); }
unsigned long long liveRefCountedObjects() noexcept { return liveObjects.load(std::memory_order_acquire); }

RefCounted::RefCounted(RefConstructionToken token) : RefCounted(token._threading) {}
RefCounted::RefCounted(RefThreading threading)
: _threading(threading),
  _scriptObjectID(scriptSequence.fetch_add(1,std::memory_order_relaxed)+1), _counter(0) {
    if (_threading == RefThreading::Atomic) new (&_counter.atomic) std::atomic<unsigned int>(0);
#if CC_REF_LEAK_DETECTION
    std::lock_guard<std::mutex> lock(leakMutex);
    leakObjects.push_back(this);
#endif
    liveObjects.fetch_add(1,std::memory_order_relaxed);
}
RefCounted::~RefCounted() {
    if (_scriptIdentity) {
        // Host code is retained until objects finish; a VM may already be closed.
        if (const auto* host=getRefServices()) host->destroyIdentity(*this,*_scriptIdentity);
        delete _scriptIdentity;
    }
#if CC_REF_LEAK_DETECTION
    std::lock_guard<std::mutex> lock(leakMutex);
    auto it=std::find(leakObjects.begin(),leakObjects.end(),this);
    if(it!=leakObjects.end()) leakObjects.erase(it);
#endif
    liveObjects.fetch_sub(1,std::memory_order_release);
}
void RefCounted::addRef() noexcept {
    if (_threading == RefThreading::Atomic) _counter.atomic.fetch_add(1,std::memory_order_relaxed);
    else ++_counter.local;
}

void RefCounted::release() {
    const auto previous = _threading == RefThreading::Atomic
        ? _counter.atomic.fetch_sub(1,std::memory_order_acq_rel) : _counter.local--;
    if (previous == 0) {
        CC_LOG_ERROR("RefCounted::release: invalid reference count in %s",typeid(*this).name());
        CC_ASSERT_GT(previous,0);
        if (_threading == RefThreading::Atomic) _counter.atomic.fetch_add(1,std::memory_order_relaxed);
        else ++_counter.local;
        return;
    }

    if (previous == 1) {
        if (_threading == RefThreading::Local)
            if(const auto* host=getRefServices()) host->finalRelease(*this);
        onFinalRelease();
        delete this;
    }
}

unsigned int RefCounted::getRefCount() const {
    return _threading == RefThreading::Atomic ? _counter.atomic.load(std::memory_order_relaxed) : _counter.local;
}
unsigned int RefCounted::getScriptObjectID() const {
    return _scriptObjectID;
}
RefScriptIdentity& RefCounted::getScriptIdentity() {
    const auto* host=getRefServices();
    if (!host) throw std::logic_error("Cocos Ref services are not initialized");
    return host->identity(*this,_scriptIdentity);
}
RefCounted* RefCounted::autorelease() {
    const auto* host=getRefServices();
    if (!host) throw std::logic_error("Cocos Ref pool services are not initialized");
    host->enqueue(*this);
    return this;
}
#if CC_REF_LEAK_DETECTION
void RefCounted::printLeaks() {
    std::lock_guard<std::mutex> lock(leakMutex);
    for(auto* object:leakObjects)
        CC_LOG_INFO("[memory] LEAK: %s count %u",typeid(*object).name(),object->getRefCount());
    if(leakObjects.empty()) CC_LOG_INFO("[memory] All Ref objects successfully cleaned up (no leaks detected).");
}
#endif
} // namespace cc
