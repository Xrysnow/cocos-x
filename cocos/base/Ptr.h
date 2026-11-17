/****************************************************************************
 Copyright (c) 2021-2023 Xiamen Yaji Software Co., Ltd.

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

#include "platform/CCNamespace.h"

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

namespace cc {

struct retain_ref_t { explicit constexpr retain_ref_t() = default; };
struct adopt_ref_t { explicit constexpr adopt_ref_t() = default; };
inline constexpr retain_ref_t retain_ref{};
inline constexpr adopt_ref_t adopt_ref{};

// Const handles restrict object access, not ownership bookkeeping. The object
// itself must permit reference-count mutation (as with the legacy RefPtr).
struct IntrusiveRefOps {
    template <class T> static void addRef(T *ptr) {
        const_cast<std::remove_const_t<T> *>(ptr)->addRef();
    }
    template <class T> static void release(T *ptr) {
        const_cast<std::remove_const_t<T> *>(ptr)->release();
    }
};

// One reference per non-null handle. Raw pointers retain by default; adopt_ref
// consumes an existing owned reference, never a borrow or a pool's reference.
// Concurrent access to the same handle needs external synchronization even when
// the pointee uses an atomic counter. RefOps adds no counter/control block.
template <class T, class RefOps = IntrusiveRefOps>
class IntrusivePtr {
public:
    using element_type = T;

    constexpr IntrusivePtr() noexcept = default;
    constexpr IntrusivePtr(std::nullptr_t) noexcept {}
    IntrusivePtr(T *ptr) : _ptr(ptr) { // NOLINT: legacy API
        if (_ptr) RefOps::addRef(_ptr);
    }
    IntrusivePtr(T *ptr, retain_ref_t) : _ptr(ptr) {
        if (_ptr) RefOps::addRef(_ptr);
    }
    IntrusivePtr(T *ptr, adopt_ref_t) noexcept : _ptr(ptr) {}
    IntrusivePtr(const IntrusivePtr &other) : _ptr(other._ptr) {
        if (_ptr) RefOps::addRef(_ptr);
    }
    IntrusivePtr(IntrusivePtr &&other) noexcept : _ptr(other._ptr) { other._ptr = nullptr; }

    template <class U, std::enable_if_t<std::is_convertible<U *, T *>::value, int> = 0>
    IntrusivePtr(const IntrusivePtr<U, RefOps> &other) : _ptr(other._ptr) {
        if (_ptr) RefOps::addRef(_ptr);
    }
    template <class U, std::enable_if_t<std::is_convertible<U *, T *>::value, int> = 0>
    IntrusivePtr(IntrusivePtr<U, RefOps> &&other) noexcept : _ptr(other._ptr) { other._ptr = nullptr; }

    ~IntrusivePtr() {
        T *old = _ptr;
        _ptr = nullptr;
        if (old) RefOps::release(old);
    }

    T *get() const noexcept { return _ptr; }
    // Borrow only from a named owner. Temporary ownership must be explicit.
    operator T *() const & noexcept { return _ptr; } // NOLINT: legacy lvalue API
    operator T *() && = delete;
    operator T *() const && = delete;
    explicit operator bool() const & noexcept { return _ptr != nullptr; }
    explicit operator bool() && noexcept { return _ptr != nullptr; }
    explicit operator bool() const && noexcept { return _ptr != nullptr; }
    T &operator*() const { return *_ptr; }
    T *operator->() const noexcept { return _ptr; }

    IntrusivePtr &operator=(const IntrusivePtr &other) {
        reset(other.get());
        return *this;
    }
    IntrusivePtr &operator=(IntrusivePtr &&other) noexcept {
        IntrusivePtr(std::move(other)).swap(*this);
        return *this;
    }
    template <class U, std::enable_if_t<std::is_convertible<U *, T *>::value, int> = 0>
    IntrusivePtr &operator=(const IntrusivePtr<U, RefOps> &other) {
        reset(other.get());
        return *this;
    }
    template <class U, std::enable_if_t<std::is_convertible<U *, T *>::value, int> = 0>
    IntrusivePtr &operator=(IntrusivePtr<U, RefOps> &&other) noexcept {
        IntrusivePtr(std::move(other)).swap(*this);
        return *this;
    }
    IntrusivePtr &operator=(T *ptr) { reset(ptr); return *this; }
    IntrusivePtr &operator=(std::nullptr_t) noexcept { reset(); return *this; }

    // Transfer one owned reference to the caller without releasing it.
    T *detach() noexcept {
        T *old = _ptr;
        _ptr = nullptr;
        return old;
    }
    void reset() noexcept {
        T *old = _ptr;
        _ptr = nullptr; // Publish null before a destructor can reenter.
        if (old) RefOps::release(old);
    }
    void reset(T *ptr) { reset(ptr, retain_ref); }
    void reset(T *ptr, retain_ref_t) {
        if (ptr == _ptr) return;
        if (ptr) RefOps::addRef(ptr); // Keep the replacement alive first.
        T *old = _ptr;
        _ptr = ptr;
        if (old) RefOps::release(old);
    }
    void reset(T *ptr, adopt_ref_t) noexcept {
        // Even for the same address the caller must supply a separate share.
        T *old = _ptr;
        _ptr = ptr;
        if (old) RefOps::release(old);
    }
    void swap(IntrusivePtr &other) noexcept { std::swap(_ptr, other._ptr); }
    // Legacy owned-raw exchange: *ptr must own one reference (or be null).
    void swap(T **ptr) noexcept { std::swap(_ptr, *ptr); }

private:
    template <class U, class Ops> friend class IntrusivePtr;
    T *_ptr{nullptr};
};

template <class T, class Ops>
void swap(IntrusivePtr<T, Ops> &lhs, IntrusivePtr<T, Ops> &rhs) noexcept { lhs.swap(rhs); }

template <class T, class U, class Ops, class OtherOps>
bool operator==(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return lhs.get() == rhs.get();
}
template <class T, class U, class Ops>
bool operator==(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return lhs.get() == rhs;
}
template <class T, class U, class Ops>
bool operator==(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return lhs == rhs.get();
}
template <class T, class Ops>
bool operator==(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return ptr.get() == nullptr;
}
template <class T, class Ops>
bool operator==(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return nullptr == ptr.get();
}

template <class T, class U, class Ops, class OtherOps>
bool operator!=(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return !(lhs.get() == rhs.get());
}
template <class T, class U, class Ops>
bool operator!=(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return !(lhs.get() == rhs);
}
template <class T, class U, class Ops>
bool operator!=(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return !(lhs == rhs.get());
}
template <class T, class Ops>
bool operator!=(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return !(ptr.get() == nullptr);
}
template <class T, class Ops>
bool operator!=(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return !(nullptr == ptr.get());
}

template <class T, class U, class Ops, class OtherOps>
bool operator<(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(lhs.get(), rhs.get());
}
template <class T, class U, class Ops>
bool operator<(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(lhs.get(), rhs);
}
template <class T, class U, class Ops>
bool operator<(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(lhs, rhs.get());
}
template <class T, class Ops>
bool operator<(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return std::less<T *>{}(ptr.get(), nullptr);
}
template <class T, class Ops>
bool operator<(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return std::less<T *>{}(nullptr, ptr.get());
}

template <class T, class U, class Ops, class OtherOps>
bool operator>(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(rhs.get(), lhs.get());
}
template <class T, class U, class Ops>
bool operator>(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(rhs, lhs.get());
}
template <class T, class U, class Ops>
bool operator>(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return std::less<std::common_type_t<T *, U *>>{}(rhs.get(), lhs);
}
template <class T, class Ops>
bool operator>(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return std::less<T *>{}(nullptr, ptr.get());
}
template <class T, class Ops>
bool operator>(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return std::less<T *>{}(ptr.get(), nullptr);
}

template <class T, class U, class Ops, class OtherOps>
bool operator<=(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(rhs.get(), lhs.get());
}
template <class T, class U, class Ops>
bool operator<=(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(rhs, lhs.get());
}
template <class T, class U, class Ops>
bool operator<=(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(rhs.get(), lhs);
}
template <class T, class Ops>
bool operator<=(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return !std::less<T *>{}(nullptr, ptr.get());
}
template <class T, class Ops>
bool operator<=(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return !std::less<T *>{}(ptr.get(), nullptr);
}

template <class T, class U, class Ops, class OtherOps>
bool operator>=(const IntrusivePtr<T, Ops> &lhs, const IntrusivePtr<U, OtherOps> &rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(lhs.get(), rhs.get());
}
template <class T, class U, class Ops>
bool operator>=(const IntrusivePtr<T, Ops> &lhs, U *rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(lhs.get(), rhs);
}
template <class T, class U, class Ops>
bool operator>=(T *lhs, const IntrusivePtr<U, Ops> &rhs) noexcept {
    return !std::less<std::common_type_t<T *, U *>>{}(lhs, rhs.get());
}
template <class T, class Ops>
bool operator>=(const IntrusivePtr<T, Ops> &ptr, std::nullptr_t) noexcept {
    return !std::less<T *>{}(ptr.get(), nullptr);
}
template <class T, class Ops>
bool operator>=(std::nullptr_t, const IntrusivePtr<T, Ops> &ptr) noexcept {
    return !std::less<T *>{}(nullptr, ptr.get());
}

template <class T, class U, class Ops>
IntrusivePtr<T, Ops> static_pointer_cast(const IntrusivePtr<U, Ops> &ptr) {
    return IntrusivePtr<T, Ops>(static_cast<T *>(ptr.get()), retain_ref);
}
template <class T, class U, class Ops>
IntrusivePtr<T, Ops> static_pointer_cast(IntrusivePtr<U, Ops> &&ptr) noexcept {
    return IntrusivePtr<T, Ops>(static_cast<T *>(ptr.detach()), adopt_ref);
}
template <class T, class U, class Ops>
IntrusivePtr<T, Ops> dynamic_pointer_cast(const IntrusivePtr<U, Ops> &ptr) {
    return IntrusivePtr<T, Ops>(dynamic_cast<T *>(ptr.get()), retain_ref);
}
template <class T, class U, class Ops>
IntrusivePtr<T, Ops> dynamic_pointer_cast(IntrusivePtr<U, Ops> &&ptr) noexcept {
    auto *value = dynamic_cast<T *>(ptr.get());
    if (value) ptr.detach(); // Failure leaves the source unchanged.
    return IntrusivePtr<T, Ops>(value, adopt_ref);
}

} // namespace cc

namespace std {
template <class T, class Ops>
struct hash<cc::IntrusivePtr<T, Ops>> {
    size_t operator()(const cc::IntrusivePtr<T, Ops> &value) const noexcept {
        return hash<T *>{}(value.get());
    }
};
} // namespace std
