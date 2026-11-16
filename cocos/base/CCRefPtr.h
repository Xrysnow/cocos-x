/****************************************************************************
 Copyright (c) 2014      PlayFirst Inc.
 Copyright (c) 2014-2016 Chukong Technologies Inc.
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

#ifndef __CC_REF_PTR_H__
#define __CC_REF_PTR_H__
/// @cond DO_NOT_SHOW

#include "base/CCRef.h"
#include "base/ccMacros.h"
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace cc {

// RefPtr is the pure alias declared in CCRef.h. Ownership lives in gfx/base/Ptr.h.
using cc::static_pointer_cast;
using cc::dynamic_pointer_cast;

template <class T>
inline cc::IntrusivePtr<T> makeRef(T* ptr)
{
    return cc::IntrusivePtr<T>(ptr);
}

/** Construct an object with an explicit, immutable reference-count policy.
 * Construction starts at zero; the returned IntrusivePtr establishes the first reference.
 * It calls neither init() nor autorelease(); callers perform any initialization
 * while retaining the returned IntrusivePtr. Allocation/constructor exceptions propagate.
 *
 * T must accept RefConstructionToken as its first constructor argument and forward
 * it through its base constructors, for example:
 *
 * class Item : public Ref {
 * public:
 *     Item(RefConstructionToken token, int value) : Ref(token), value(value) {}
 *     int value;
 * };
 * auto item = makeRef<Item, RefThreading::Atomic>(42);
 *
 * Existing classes without such a constructor are intentionally not supported:
 * wrapping an existing pointer cannot change its policy. A private constructor
 * grants friendship to this policy factory. Callers choose the
 * business factory when they also require its init() work.
 * This policy does not make object state, Lua access, autorelease pools, or
 * thread-affine destructors safe to use on arbitrary threads.
 */
template <class T, RefThreading Threading, class... Args>
cc::IntrusivePtr<T> makeRef(Args&&... args)
{
    static_assert(Threading == RefThreading::Local || Threading == RefThreading::Atomic,
                  "Invalid reference-count threading policy");
    static_assert(std::is_convertible_v<T*,RefCounted*>, "T must publicly and unambiguously derive from RefCounted");

    cc::IntrusivePtr result{new T(RefConstructionToken(Threading), std::forward<Args>(args)...)};
    // A constructor can accidentally accept the token but omit forwarding it.
    // Reject that mistake in release builds too, before publishing the object.
    if (static_cast<const RefCounted*>(result.get())->getReferenceThreading() != Threading)
        throw std::logic_error("Ref constructor did not forward its RefConstructionToken");
    return result;
}

} // namespace cc

NS_CC_BEGIN
using cc::makeRef;
using cc::static_pointer_cast;
using cc::dynamic_pointer_cast;
/** A strong reference whose non-null target always uses RefThreading::Atomic.
 * The private IntrusivePtr stores the same intrusive ownership as an ordinary IntrusivePtr;
 * this wrapper adds no counter and never changes an object's policy.
 *
 * Use makeThreadSafeRef<T>(args...) to create an object, or requireThreadSafe(ref)
 * to check an existing IntrusivePtr explicitly. There is no public raw-pointer/adoption
 * constructor, implicit raw-pointer conversion, or mutable access to the IntrusivePtr.
 *
 * Distinct instances can manage references concurrently. Concurrent mutation of
 * the same instance still needs synchronization. Object state, autorelease pools,
 * Lua access and thread-affine destruction retain their own threading rules.
 * @lua NA
 * @js NA
 */
template <class T>
class ThreadSafeRefPtr
{
public:
    ThreadSafeRefPtr() noexcept = default;
    ThreadSafeRefPtr(std::nullptr_t) noexcept {}

    ThreadSafeRefPtr(const ThreadSafeRefPtr&) = default;
    ThreadSafeRefPtr(ThreadSafeRefPtr&&) noexcept = default;

    // Pointer-compatible upcasts and adding const preserve the same Ref subobject.
    template <class U, std::enable_if_t<std::is_convertible<U*, T*>::value, int> = 0>
    ThreadSafeRefPtr(const ThreadSafeRefPtr<U>& other) : _ptr(other.get())
    {}

    template <class U, std::enable_if_t<std::is_convertible<U*, T*>::value, int> = 0>
    ThreadSafeRefPtr(ThreadSafeRefPtr<U>&& other) noexcept : _ptr(std::move(other._ptr))
    {}

    ThreadSafeRefPtr& operator=(ThreadSafeRefPtr other) noexcept
    {
        swap(other);
        return *this;
    }

    template <class U, std::enable_if_t<std::is_convertible<U*, T*>::value, int> = 0>
    ThreadSafeRefPtr& operator=(const ThreadSafeRefPtr<U>& other)
    {
        ThreadSafeRefPtr copy(other);
        swap(copy);
        return *this;
    }

    template <class U, std::enable_if_t<std::is_convertible<U*, T*>::value, int> = 0>
    ThreadSafeRefPtr& operator=(ThreadSafeRefPtr<U>&& other)
    {
        ThreadSafeRefPtr moved(std::move(other));
        swap(moved);
        return *this;
    }

    ThreadSafeRefPtr& operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }

    T* get() const noexcept { return _ptr.get(); }
    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr.operator->(); }
    explicit operator bool() const noexcept { return get() != nullptr; }

    void reset() noexcept
    {
        // Publish the empty state before releasing the old object.
        ThreadSafeRefPtr empty;
        swap(empty);
    }

    void swap(ThreadSafeRefPtr& other) noexcept { _ptr.swap(other._ptr); }

    /** Explicitly erase the type-level guarantee; the object's policy stays Atomic.
     * Lvalues copy a reference, while rvalues transfer it and become empty.
     */
    cc::IntrusivePtr<T> asRef() const & { return _ptr; }
    cc::IntrusivePtr<T> asRef() && noexcept { return std::move(_ptr); }

private:
    template <class U> friend class ThreadSafeRefPtr;

    static T* checkedPointer(T* ptr)
    {
        // Check before retain(): a Local counter must not be touched by a failed
        // conversion, even when this check runs on a worker thread.
        if (ptr && static_cast<const Ref*>(ptr)->getReferenceThreading() != RefThreading::Atomic)
            throw std::invalid_argument("ThreadSafeRefPtr requires RefThreading::Atomic");
        return ptr;
    }

    explicit ThreadSafeRefPtr(T* ptr) : _ptr(checkedPointer(ptr)) {}

    explicit ThreadSafeRefPtr(cc::IntrusivePtr<T>&& ptr)
    {
        checkedPointer(ptr.get());
        // Validate before consuming the source; failure leaves it unchanged.
        _ptr.swap(ptr);
    }

    cc::IntrusivePtr<T> _ptr;

    static_assert(std::is_convertible_v<T*,const Ref*>,
                  "T must publicly and unambiguously derive from Ref (optionally const)");

    template <class U>
    friend ThreadSafeRefPtr<U> requireThreadSafe(const cc::IntrusivePtr<U>& ptr);
    template <class U>
    friend ThreadSafeRefPtr<U> requireThreadSafe(cc::IntrusivePtr<U>&& ptr);
    template <class U, class V>
    friend ThreadSafeRefPtr<U> static_pointer_cast(const ThreadSafeRefPtr<V>& ptr);
    template <class U, class V>
    friend ThreadSafeRefPtr<U> dynamic_pointer_cast(const ThreadSafeRefPtr<V>& ptr);
};

/** Check an existing strong reference without changing its policy.
 * Null succeeds as an empty wrapper. A Local target throws std::invalid_argument
 * in every build configuration, before acquiring a reference. The source must stay
 * alive and must not be concurrently modified during the call.
 */
template <class T>
ThreadSafeRefPtr<T> requireThreadSafe(const cc::IntrusivePtr<T>& ptr)
{
    return ThreadSafeRefPtr<T>(ptr.get());
}

/** Transfer an existing reference after validation. On failure ptr is unchanged. */
template <class T>
ThreadSafeRefPtr<T> requireThreadSafe(cc::IntrusivePtr<T>&& ptr)
{
    return ThreadSafeRefPtr<T>(std::move(ptr));
}

/** Create an Atomic object and establish its first reference.
 * T must accept and forward RefConstructionToken, just as for makeRef<T, Atomic>.
 * This factory calls neither init() nor autorelease().
 *
 * void submit(ThreadSafeRefPtr<Job> job);
 * auto job = makeThreadSafeRef<Job>(args...);
 * submit(job);
 * // submit(ordinaryRefPtr);                  // rejected at compile time
 * // submit(requireThreadSafe(ordinaryRefPtr)); // explicit runtime policy check
 */
template <class T, class... Args>
ThreadSafeRefPtr<T> makeThreadSafeRef(Args&&... args)
{
    return requireThreadSafe(makeRef<T, RefThreading::Atomic>(std::forward<Args>(args)...));
}

/** Cast while preserving the Atomic guarantee. Validate the target Ref subobject
 * before retaining it, including cross-casts in multiple-inheritance hierarchies.
 * static_pointer_cast requires a valid static cast, just as for ordinary IntrusivePtr.
 */
template <class T, class U>
ThreadSafeRefPtr<T> static_pointer_cast(const ThreadSafeRefPtr<U>& ptr)
{
    return ThreadSafeRefPtr<T>(static_cast<T*>(ptr.get()));
}

/** A failed dynamic cast returns an empty wrapper; a Local target is rejected. */
template <class T, class U>
ThreadSafeRefPtr<T> dynamic_pointer_cast(const ThreadSafeRefPtr<U>& ptr)
{
    return ThreadSafeRefPtr<T>(dynamic_cast<T*>(ptr.get()));
}

template <class T, class U>
bool operator==(const ThreadSafeRefPtr<T>& lhs, const ThreadSafeRefPtr<U>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <class T, class U>
bool operator!=(const ThreadSafeRefPtr<T>& lhs, const ThreadSafeRefPtr<U>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <class T>
bool operator==(const ThreadSafeRefPtr<T>& ptr, std::nullptr_t) noexcept
{
    return !ptr;
}

template <class T>
bool operator==(std::nullptr_t, const ThreadSafeRefPtr<T>& ptr) noexcept
{
    return !ptr;
}

template <class T>
bool operator!=(const ThreadSafeRefPtr<T>& ptr, std::nullptr_t) noexcept
{
    return static_cast<bool>(ptr);
}

template <class T>
bool operator!=(std::nullptr_t, const ThreadSafeRefPtr<T>& ptr) noexcept
{
    return static_cast<bool>(ptr);
}

template <class T>
void swap(ThreadSafeRefPtr<T>& lhs, ThreadSafeRefPtr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

NS_CC_END

/// @endcond
#endif  // __CC_REF_PTR_H__
