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

NS_CC_BEGIN

/**
 * Utility/support macros. Defined to enable RefPtr<T> to contain types like 'const T' because we do not
 * regard retain()/release() as affecting mutability of state.
 */
#define CC_REF_PTR_SAFE_RETAIN(ptr)                                   \
                                                                      \
    do                                                                \
    {                                                                 \
        if (ptr)                                                      \
        {                                                             \
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->retain(); \
        }                                                             \
                                                                      \
    } while (0);

#define CC_REF_PTR_SAFE_RELEASE(ptr)                                   \
                                                                       \
    do                                                                 \
    {                                                                  \
        if (ptr)                                                       \
        {                                                              \
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release(); \
        }                                                              \
                                                                       \
    } while (0);

#define CC_REF_PTR_SAFE_RELEASE_NULL(ptr)                              \
                                                                       \
    do                                                                 \
    {                                                                  \
        if (ptr)                                                       \
        {                                                              \
            const_cast<Ref*>(static_cast<const Ref*>(ptr))->release(); \
            ptr = nullptr;                                             \
        }                                                              \
                                                                       \
    } while (0);

// Tell RefPtr, the object already referenced, no need to retain again
template <typename T>
struct ReferencedObject
{
    T* _ptr;
};

/**
 * Wrapper class which maintains a strong reference to a cocos2dx cocos2d::Ref* type object.
 * Similar in concept to a boost smart pointer.
 *
 * Enables the use of the RAII idiom with Cocos2dx objects and helps automate some of the more
 * mundane tasks of pointer initialization and cleanup.
 *
 * The class itself is modelled on C++ 11 std::shared_ptr, and trys to keep some of the methods
 * and functionality consistent with std::shared_ptr.
 * Reference-count thread safety is determined by the object at construction.
 * Distinct RefPtr instances may manage an Atomic object concurrently; accessing
 * the same RefPtr instance concurrently still requires external synchronization.
 */
template <typename T>
class RefPtr
{
public:
    RefPtr() : _ptr(nullptr) {}

    RefPtr(RefPtr<T>&& other)
    {
        _ptr       = other._ptr;
        other._ptr = nullptr;
    }

    RefPtr(T* ptr) : _ptr(ptr) { CC_REF_PTR_SAFE_RETAIN(_ptr); }

    template <typename _Other>
    RefPtr(ReferencedObject<_Other>&& ptr) : _ptr(ptr._ptr)
    {}

    RefPtr(std::nullptr_t ptr) : _ptr(nullptr) {}

    RefPtr(const RefPtr<T>& other) : _ptr(other._ptr) { CC_REF_PTR_SAFE_RETAIN(_ptr); }

    ~RefPtr() { CC_REF_PTR_SAFE_RELEASE_NULL(_ptr); }

    RefPtr<T>& operator=(const RefPtr<T>& other)
    {
        if (other._ptr != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other._ptr);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
        }

        return *this;
    }

    RefPtr<T>& operator=(RefPtr<T>&& other)
    {
        if (&other != this)
        {
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr       = other._ptr;
            other._ptr = nullptr;
        }

        return *this;
    }

    RefPtr<T>& operator=(T* other)
    {
        if (other != _ptr)
        {
            CC_REF_PTR_SAFE_RETAIN(other);
            CC_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other;
        }

        return *this;
    }

    RefPtr<T>& operator=(std::nullptr_t other)
    {
        CC_REF_PTR_SAFE_RELEASE_NULL(_ptr);
        return *this;
    }

    operator T*() const { return _ptr; }

    T& operator*() const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return *_ptr;
    }

    T* operator->() const
    {
        CCASSERT(_ptr, "Attempt to dereference a null pointer!");
        return _ptr;
    }

    T* get() const { return _ptr; }

    bool operator==(const RefPtr<T>& other) const { return _ptr == other._ptr; }

    bool operator==(const T* other) const { return _ptr == other; }

    bool operator==(typename std::remove_const<T>::type* other) const { return _ptr == other; }

    bool operator==(const std::nullptr_t other) const { return _ptr == other; }

    bool operator!=(const RefPtr<T>& other) const { return _ptr != other._ptr; }

    bool operator!=(const T* other) const { return _ptr != other; }

    bool operator!=(typename std::remove_const<T>::type* other) const { return _ptr != other; }

    bool operator!=(const std::nullptr_t other) const { return _ptr != other; }

    bool operator>(const RefPtr<T>& other) const { return _ptr > other._ptr; }

    bool operator>(const T* other) const { return _ptr > other; }

    bool operator>(typename std::remove_const<T>::type* other) const { return _ptr > other; }

    bool operator<(const RefPtr<T>& other) const { return _ptr < other._ptr; }

    bool operator<(const T* other) const { return _ptr < other; }

    bool operator<(typename std::remove_const<T>::type* other) const { return _ptr < other; }

    bool operator>=(const RefPtr<T>& other) const { return _ptr >= other._ptr; }

    bool operator>=(const T* other) const { return _ptr >= other; }

    bool operator>=(typename std::remove_const<T>::type* other) const { return _ptr >= other; }

    bool operator<=(const RefPtr<T>& other) const { return _ptr <= other._ptr; }

    bool operator<=(const T* other) const { return _ptr <= other; }

    bool operator<=(typename std::remove_const<T>::type* other) const { return _ptr <= other; }

    explicit operator bool() const { return _ptr != nullptr; }

    void reset() { CC_REF_PTR_SAFE_RELEASE_NULL(_ptr); }

    void swap(RefPtr<T>& other)
    {
        if (&other != this)
        {
            T* tmp     = _ptr;
            _ptr       = other._ptr;
            other._ptr = tmp;
        }
    }

    /**
     * This function assigns to this RefPtr<T> but does not increase the reference count of the object pointed to.
     * Useful for assigning an object created through the 'new' operator to a RefPtr<T>. Basically used in scenarios
     * where the RefPtr<T> has the initial ownership of the object.
     *
     * E.G:
     *      RefPtr<cocos2d::Image> image;
     *      image.weakAssign(new cocos2d::Image());
     *
     * Instead of:
     *      RefPtr<cocos2d::Image> image;
     *      image = new cocos2d::Image();
     *      image->release();               // Required because new'd object already has a reference count of '1'.
     */
    void weakAssign(const RefPtr<T>& other)
    {
        CC_REF_PTR_SAFE_RELEASE(_ptr);
        _ptr = other._ptr;
    }

private:
    T* _ptr;

    // NOTE: We can ensure T is derived from cocos2d::Ref at compile time here.
    static_assert(std::is_base_of<Ref, typename std::remove_const<T>::type>::value, "T must be derived from Ref");
};

template <class T>
inline RefPtr<T> makeRef(T* ptr)
{
    return RefPtr<T>(ptr);
}

/** Construct an object with an explicit, immutable reference-count policy.
 * Unlike makeRef(T*), this overload adopts the initial reference (count == 1).
 * It calls neither init() nor autorelease(); callers perform any initialization
 * while retaining the returned RefPtr. Allocation/constructor exceptions propagate.
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
 * can grant friendship to this factory template, as Ref itself does.
 * This policy does not make object state, Lua access, autorelease pools, or
 * thread-affine destructors safe to use on arbitrary threads.
 */
template <class T, RefThreading Threading, class... Args>
RefPtr<T> makeRef(Args&&... args)
{
    static_assert(Threading == RefThreading::Local || Threading == RefThreading::Atomic,
                  "Invalid reference-count threading policy");
    static_assert(std::is_convertible<T*, Ref*>::value, "T must publicly and unambiguously derive from Ref");

    RefPtr<T> result(ReferencedObject<T>{new T(RefConstructionToken(Threading), std::forward<Args>(args)...)});
    // A constructor can accidentally accept the token but omit forwarding it.
    // Reject that mistake in release builds too, before publishing the object.
    if (static_cast<const Ref*>(result.get())->getReferenceThreading() != Threading)
        throw std::logic_error("Ref constructor did not forward its RefConstructionToken");
    return result;
}

template <class T>
inline bool operator<(const RefPtr<T>& r, std::nullptr_t)
{
    return std::less<T*>()(r.get(), nullptr);
}

template <class T>
inline bool operator<(std::nullptr_t, const RefPtr<T>& r)
{
    return std::less<T*>()(nullptr, r.get());
}

template <class T>
inline bool operator>(const RefPtr<T>& r, std::nullptr_t)
{
    return nullptr < r;
}

template <class T>
inline bool operator>(std::nullptr_t, const RefPtr<T>& r)
{
    return r < nullptr;
}

template <class T>
inline bool operator<=(const RefPtr<T>& r, std::nullptr_t)
{
    return !(nullptr < r);
}

template <class T>
inline bool operator<=(std::nullptr_t, const RefPtr<T>& r)
{
    return !(r < nullptr);
}

template <class T>
inline bool operator>=(const RefPtr<T>& r, std::nullptr_t)
{
    return !(r < nullptr);
}

template <class T>
inline bool operator>=(std::nullptr_t, const RefPtr<T>& r)
{
    return !(nullptr < r);
}

/**
 * Cast between RefPtr types statically.
 */
template <class T, class U>
RefPtr<T> static_pointer_cast(const RefPtr<U>& r)
{
    return RefPtr<T>(static_cast<T*>(r.get()));
}

/**
 * Cast between RefPtr types dynamically.
 */
template <class T, class U>
RefPtr<T> dynamic_pointer_cast(const RefPtr<U>& r)
{
    return RefPtr<T>(dynamic_cast<T*>(r.get()));
}

/**
 * Done with these macros.
 */
#undef CC_REF_PTR_SAFE_RETAIN
#undef CC_REF_PTR_SAFE_RELEASE
#undef CC_REF_PTR_SAFE_RELEASE_NULL

NS_CC_END

/// @endcond
#endif  // __CC_REF_PTR_H__
