/****************************************************************************
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
#include "base/Log.h"
#include "base/Random.h"
#include "base/RefCounted.h"
#include <cstddef>
#include <functional>
#include <iterator>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cc {

// One owned reference per non-null mapped pointer. All public iterators borrow
// read-only slots. Hash/equality and key operations must not reenter the map.
// @lua NA
template <class K, class V, class Hash = std::hash<K>, class Equal = std::equal_to<K>>
class RefMap {
    static_assert(std::is_pointer_v<V>, "RefMap requires a raw pointer mapped type");
    static_assert(std::is_nothrow_swappable_v<Hash> && std::is_nothrow_swappable_v<Equal>,
                  "RefMap requires non-throwing hash/equality swap");
    template <class U>
    using Compatible = std::enable_if_t<std::is_convertible_v<U *, V>, int>;

public:
    using storage_type = std::unordered_map<K, V, Hash, Equal>;
    using key_type = K;
    using mapped_type = V;
    using size_type = std::ptrdiff_t;
    using iterator = typename storage_type::const_iterator;
    using const_iterator = iterator;

    RefMap() { checkType(); }
    explicit RefMap(size_type capacity, const Hash &hash = Hash{}, const Equal &equal = Equal{})
    : _data(0, hash, equal) { checkType(); reserve(capacity); }
    RefMap(const RefMap &other) : _data(other._data) { retainAll(); }
    // An empty standard unordered_map may allocate; do not promise noexcept.
    RefMap(RefMap &&other) : RefMap() { swap(other); }
    ~RefMap() {
        // No allocation during teardown, including when a callback adds entries.
        while (!empty()) erase(begin());
    }
    RefMap &operator=(const RefMap &other) {
        if (this != &other) RefMap(other).swap(*this);
        return *this;
    }
    RefMap &operator=(RefMap &&other) {
        if (this != &other) RefMap(std::move(other)).swap(*this);
        return *this;
    }
    void swap(RefMap &other) noexcept { _data.swap(other._data); }

    iterator begin() const noexcept { return _data.cbegin(); }
    iterator end() const noexcept { return _data.cend(); }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }
    const storage_type &get() const noexcept { return _data; }
    size_type size() const noexcept { return static_cast<size_type>(_data.size()); }
    bool empty() const noexcept { return _data.empty(); }
    void reserve(size_type capacity) {
        CC_ASSERT(capacity >= 0);
        _data.reserve(static_cast<size_t>(capacity));
    }

    template <class Key> iterator find(const Key &key) const { return lookup(_data, key); }
    template <class Key> V at(const Key &key) const {
        auto it = find(key);
        return it == end() ? nullptr : it->second;
    }
    template <class Key> bool contains(const Key &key) const { return find(key) != end(); }

    // insert preserves the legacy overwrite semantics. Existing keys stay put.
    template <class Key> void insert(Key &&key, V object) {
        CC_ASSERT_NOT_NULL(object);
        assign(std::forward<Key>(key), object, [&] { object->addRef(); });
    }
    template <class Key, class U, Compatible<U> = 0>
    void insert(Key &&key, const IntrusivePtr<U> &object) {
        insert(std::forward<Key>(key), object.get());
    }
    template <class Key, class U, Compatible<U> = 0>
    void insert(Key &&key, IntrusivePtr<U> &&object) {
        CC_ASSERT_NOT_NULL(object.get());
        assign(std::forward<Key>(key), object.get(), [&] { object.detach(); });
    }
    template <class Key, class U, class Ops,
              std::enable_if_t<!std::is_same_v<Ops, IntrusiveRefOps>, int> = 0>
    void insert(Key &&, const IntrusivePtr<U, Ops> &) = delete;

    // No successor iterator: final release may erase it or trigger a rehash.
    void erase(const_iterator position) {
        CC_ASSERT(position != end());
        auto removed = _data.extract(position);
        removed.mapped()->release();
    }
    template <class Key> size_t erase(const Key &key) {
        auto it = find(key);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }
    template <class Key> void erase(const std::vector<Key> &keys) {
        // Views may point into this map or objects released by an earlier key.
        std::vector<K> ownedKeys;
        ownedKeys.reserve(keys.size());
        for (const auto &key : keys) ownedKeys.emplace_back(key);
        for (const auto &key : ownedKeys) erase(key);
    }
    void clear() {
        if (empty()) return;
        // Use the potentially-throwing sized constructor: MSVC's Debug vector
        // default constructor is noexcept but allocates an iterator proxy.
        std::vector<typename storage_type::node_type> removed(_data.size());
        for (auto &node : removed) node = _data.extract(_data.cbegin());
        // Callbacks observe all original entries removed; new entries survive.
        for (auto &node : removed) node.mapped()->release();
    }

    std::vector<K> keys() const {
        std::vector<K> result;
        result.reserve(_data.size());
        for (const auto &entry : _data) result.push_back(entry.first);
        return result;
    }
    std::vector<K> keys(V object) const {
        std::vector<K> result;
        for (const auto &entry : _data)
            if (entry.second == object) result.push_back(entry.first);
        return result;
    }
    template <class U, class Ops, Compatible<U> = 0>
    std::vector<K> keys(const IntrusivePtr<U, Ops> &object) const { return keys(object.get()); }
    V getRandomObject() const {
        if (empty()) return nullptr;
        auto it = begin();
        std::advance(it, RandomHelper::randomInt<size_type>(0, size() - 1));
        return it->second;
    }

private:
    static void checkType() {
        static_assert(std::is_convertible_v<V, RefCounted *>, "RefMap requires public RefCounted pointers");
    }
    void retainAll() {
        checkType();
        for (const auto &entry : _data) entry.second->addRef();
    }
    template <class Data, class Key> static auto lookup(Data &data, const Key &key) {
        if constexpr (requires { data.find(key); }) return data.find(key);
        else return data.find(K(key));
    }
    template <class Key, class Acquire> void assign(Key &&key, V object, Acquire acquire) {
        auto it = lookup(_data, key);
        if (it == _data.end()) {
            // Construct an owning key only for a new entry. The owner is untouched
            // until key/hash/equality/allocation work has succeeded.
            auto result = _data.try_emplace(K(std::forward<Key>(key)), object);
            it = result.first;
            if (result.second) { acquire(); return; }
        }
        acquire();
        V old = std::exchange(it->second, object);
        old->release(); // Published replacement; do not touch iterators afterward.
    }
    storage_type _data;
};

template <class K, class V, class H, class E>
void swap(RefMap<K, V, H, E> &a, RefMap<K, V, H, E> &b) noexcept { a.swap(b); }

} // namespace cc
