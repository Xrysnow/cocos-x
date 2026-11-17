/****************************************************************************
 Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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

#include "platform/CCNamespace.h"
#include "base/Log.h"
#include "base/Random.h"
#include "base/RefCounted.h"
#include "base/std/container/vector.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <utility>

namespace cc {

// One owned reference per non-null raw-pointer slot. Accessors and iterators
// borrow objects but never allow replacing a slot. Mutate through this class.
// Like std::vector, concurrent access and comparator reentry need caller care.
// @lua NA
template <class T>
class RefVector {
    static_assert(std::is_pointer<T>::value, "RefVector requires a raw pointer element type");
    template <class U>
    using Compatible = std::enable_if_t<std::is_convertible<U *, T>::value, int>;

public:
    using value_type = T;
    using size_type = std::ptrdiff_t;
    using iterator = typename ccstd::vector<T>::const_iterator;
    using const_iterator = iterator;
    using reverse_iterator = typename ccstd::vector<T>::const_reverse_iterator;
    using const_reverse_iterator = reverse_iterator;

    RefVector() { checkType(); }
    explicit RefVector(size_type capacity) : RefVector() { reserve(capacity); }
    RefVector(std::initializer_list<T> list) : _data(list) { retainAll(); }
    RefVector(const RefVector &other) : _data(other._data) { retainAll(); }
    explicit RefVector(const ccstd::vector<T> &other) : _data(other) { retainAll(); }
    RefVector(RefVector &&other) noexcept : RefVector() { _data.swap(other._data); }
    // A raw vector owns no references, even when its storage is moved.
    explicit RefVector(ccstd::vector<T> &&other) noexcept : _data(std::move(other)) { retainAll(); }
    ~RefVector() {
        // A final-release callback may append another owned object.
        while (!empty()) clear();
    }

    RefVector &operator=(const RefVector &other) {
        if (this != &other) RefVector(other).swap(*this);
        return *this;
    }
    RefVector &operator=(RefVector &&other) noexcept {
        if (this != &other) RefVector(std::move(other)).swap(*this);
        return *this;
    }
    RefVector &operator=(const ccstd::vector<T> &other) {
        RefVector(other).swap(*this);
        return *this;
    }
    RefVector &operator=(ccstd::vector<T> &&other) noexcept {
        RefVector(std::move(other)).swap(*this);
        return *this;
    }
    RefVector &operator=(std::initializer_list<T> list) {
        RefVector(list).swap(*this);
        return *this;
    }

    iterator begin() const noexcept { return _data.cbegin(); }
    iterator end() const noexcept { return _data.cend(); }
    const_iterator cbegin() const noexcept { return _data.cbegin(); }
    const_iterator cend() const noexcept { return _data.cend(); }
    reverse_iterator rbegin() const noexcept { return _data.crbegin(); }
    reverse_iterator rend() const noexcept { return _data.crend(); }
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }
    const_reverse_iterator crend() const noexcept { return _data.crend(); }
    const ccstd::vector<T> &get() const noexcept { return _data; }

    T &operator[](size_type) = delete;
    const T &operator[](size_type) const = delete;
    T at(size_type index) const {
        checkIndex(index);
        return _data[index];
    }
    T front() const { CC_ASSERT(!empty()); return _data.front(); }
    T back() const { CC_ASSERT(!empty()); return _data.back(); }
    T getRandomObject() const {
        if (empty()) return nullptr;
        return _data[RandomHelper::randomInt<size_type>(0, size() - 1)];
    }

    void reserve(size_type capacity) {
        CC_ASSERT(capacity >= 0);
        _data.reserve(static_cast<size_t>(capacity));
    }
    size_type capacity() const noexcept { return static_cast<size_type>(_data.capacity()); }
    size_type size() const noexcept { return static_cast<size_type>(_data.size()); }
    bool empty() const noexcept { return _data.empty(); }
    size_type max_size() const noexcept { return static_cast<size_type>(_data.max_size()); }
    size_type maxSize() const noexcept { return max_size(); }
    void shrinkToFit() { _data.shrink_to_fit(); }

    // Missing objects use the legacy Vector sentinel, -1.
    size_type getIndex(T object) const {
        auto it = find(object);
        return it == end() ? -1 : it - begin();
    }
    iterator find(T object) const { return std::find(begin(), end(), object); }
    bool contains(T object) const { return find(object) != end(); }
    bool equals(const RefVector &other) const { return _data == other._data; }
    template <class U, class Ops, Compatible<U> = 0>
    size_type getIndex(const IntrusivePtr<U, Ops> &object) const { return getIndex(object.get()); }
    template <class U, class Ops, Compatible<U> = 0>
    iterator find(const IntrusivePtr<U, Ops> &object) const { return find(object.get()); }
    template <class U, class Ops, Compatible<U> = 0>
    bool contains(const IntrusivePtr<U, Ops> &object) const { return contains(object.get()); }

    void pushBack(T object) {
        CC_ASSERT_NOT_NULL(object);
        _data.push_back(object); // Allocation may fail before acquiring the share.
        object->addRef();
    }
    template <class U, Compatible<U> = 0>
    void pushBack(const IntrusivePtr<U> &object) { pushBack(object.get()); }
    template <class U, Compatible<U> = 0>
    void pushBack(IntrusivePtr<U> &&object) {
        CC_ASSERT_NOT_NULL(object.get());
        _data.push_back(object.get());
        object.detach(); // Commit ownership only after insertion succeeds.
    }
    void pushBack(const RefVector &other) {
        const auto count = other.size();
        if (count == 0) return;
        if (this == &other) {
            // Snapshot iterators before growing would be invalidated by reserve.
            RefVector copy(other);
            pushBack(copy);
            return;
        }
        _data.insert(_data.end(), other.begin(), other.end());
        for (T object : other) object->addRef();
    }

    void insert(size_type index, T object) {
        CC_ASSERT(index >= 0 && index <= size());
        CC_ASSERT_NOT_NULL(object);
        _data.insert(_data.begin() + index, object);
        object->addRef();
    }
    template <class U, Compatible<U> = 0>
    void insert(size_type index, const IntrusivePtr<U> &object) { insert(index, object.get()); }
    template <class U, Compatible<U> = 0>
    void insert(size_type index, IntrusivePtr<U> &&object) {
        CC_ASSERT(index >= 0 && index <= size());
        CC_ASSERT_NOT_NULL(object.get());
        _data.insert(_data.begin() + index, object.get());
        object.detach();
    }
    void replace(size_type index, T object) {
        checkIndex(index);
        CC_ASSERT_NOT_NULL(object);
        object->addRef(); // Also protects replacing the sole reference with itself.
        T old = std::exchange(_data[index], object);
        old->release();
    }
    template <class U, Compatible<U> = 0>
    void replace(size_type index, const IntrusivePtr<U> &object) { replace(index, object.get()); }
    template <class U, Compatible<U> = 0>
    void replace(size_type index, IntrusivePtr<U> &&object) {
        checkIndex(index);
        CC_ASSERT_NOT_NULL(object.get());
        T old = std::exchange(_data[index], object.get());
        object.detach();
        old->release();
    }
    // A different ownership policy cannot silently transfer into this container.
    template <class U, class Ops, std::enable_if_t<!std::is_same<Ops, IntrusiveRefOps>::value, int> = 0>
    void pushBack(const IntrusivePtr<U, Ops> &) = delete;
    template <class U, class Ops, std::enable_if_t<!std::is_same<Ops, IntrusiveRefOps>::value, int> = 0>
    void insert(size_type, const IntrusivePtr<U, Ops> &) = delete;
    template <class U, class Ops, std::enable_if_t<!std::is_same<Ops, IntrusiveRefOps>::value, int> = 0>
    void replace(size_type, const IntrusivePtr<U, Ops> &) = delete;

    void popBack() {
        CC_ASSERT(!empty());
        T old = _data.back();
        _data.pop_back();
        old->release();
    }
    void eraseObject(T object, bool removeAll = false) {
        CC_ASSERT_NOT_NULL(object);
        if (!removeAll) {
            auto it = find(object);
            if (it != end()) erase(it);
            return;
        }
        auto first = std::remove(_data.begin(), _data.end(), object);
        auto count = _data.end() - first;
        _data.erase(first, _data.end());
        // Detach every matching slot before the last release can reenter.
        while (count-- > 0) object->release();
    }
    template <class U, class Ops, Compatible<U> = 0>
    void eraseObject(const IntrusivePtr<U, Ops> &object, bool removeAll = false) {
        eraseObject(object.get(), removeAll);
    }
    iterator erase(iterator position) {
        const auto index = position - begin();
        checkIndex(index);
        T old = *position;
        _data.erase(position);
        old->release();
        return begin() + std::min(index, size());
    }
    iterator erase(iterator first, iterator last) {
        const auto index = first - begin();
        CC_ASSERT(index >= 0 && first <= last && last <= end());
        // Allocate before mutation; the detached slots retain their existing shares.
        ccstd::vector<T> removed(first, last);
        _data.erase(first, last);
        for (T object : removed) object->release();
        return begin() + std::min(index, size());
    }
    iterator erase(size_type index) { checkIndex(index); return erase(begin() + index); }
    void clear() {
        ccstd::vector<T> removed;
        removed.swap(_data);
        for (T object : removed) object->release();
        removed.clear();
        // Preserve capacity unless a callback populated the container again.
        if (_data.empty()) _data.swap(removed);
    }

    void swap(RefVector &other) noexcept { _data.swap(other._data); }
    void swap(size_type index1, size_type index2) {
        checkIndex(index1);
        checkIndex(index2);
        std::swap(_data[index1], _data[index2]);
    }
    void swap(T object1, T object2) { swap(getIndex(object1), getIndex(object2)); }
    template <class U, class Ops, class V, class OtherOps, Compatible<U> = 0, Compatible<V> = 0>
    void swap(const IntrusivePtr<U, Ops> &a, const IntrusivePtr<V, OtherOps> &b) { swap(a.get(), b.get()); }
    template <class U, class Ops, Compatible<U> = 0>
    void swap(const IntrusivePtr<U, Ops> &a, T b) { swap(a.get(), b); }
    template <class U, class Ops, Compatible<U> = 0>
    void swap(T a, const IntrusivePtr<U, Ops> &b) { swap(a, b.get()); }
    void reverse() { std::reverse(_data.begin(), _data.end()); }

    // Comparators must not mutate this container. A throwing comparator operates
    // on a borrowed snapshot so a partially sorted permutation cannot lose shares.
    template <class Compare = std::less<T>>
    void sort(Compare compare = Compare{}) {
        reorder(compare, [](auto &data, auto comp) { std::sort(data.begin(), data.end(), comp); });
    }
    template <class Compare = std::less<T>>
    void stableSort(Compare compare = Compare{}) {
        reorder(compare, [](auto &data, auto comp) { std::stable_sort(data.begin(), data.end(), comp); });
    }

private:
    static void checkType() {
        static_assert(std::is_convertible<T, RefCounted *>::value, "RefVector requires public RefCounted pointers");
    }
    void checkIndex(size_type index) const { CC_ASSERT(index >= 0 && index < size()); }
    void retainAll() {
        checkType();
        for (T object : _data) {
            CC_ASSERT_NOT_NULL(object);
            object->addRef();
        }
    }
    template <class Compare, class Sort>
    void reorder(Compare &compare, Sort sort) {
        if constexpr (std::is_nothrow_invocable_r<bool, Compare &, T, T>::value &&
                      std::is_nothrow_copy_constructible<Compare>::value &&
                      std::is_nothrow_move_constructible<Compare>::value) {
            sort(_data, compare);
        } else {
            auto sorted = _data;
            sort(sorted, compare);
            _data.swap(sorted);
        }
    }
    ccstd::vector<T> _data;
};

template <class T>
void swap(RefVector<T> &a, RefVector<T> &b) noexcept { a.swap(b); }

} // namespace cc
