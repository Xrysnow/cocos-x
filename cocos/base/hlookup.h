// Heterogeneous lookup support on c++17 with robin_hash
// C++20 demo: Heterogeneous lookup for unordered containers (transparent hashing)
// https://en.cppreference.com/w/cpp/container/unordered_map/find
#pragma once
#include "base/StringHash.h"
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "robin-map/include/tsl/robin_map.h"
#include "robin-map/include/tsl/robin_set.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace hlookup
{
template <typename _Valty>
using stl_string_map = std::map<std::string, _Valty, std::less<>>;
using stl_string_set = std::set<std::string, std::less<>>;

template <typename _Valty>
using string_map = tsl::robin_map<std::string, _Valty, string_hash, equal_to>;
using string_set = tsl::robin_set<std::string, string_hash, equal_to>;

template <typename _Cont, typename _Valty>
inline auto set_item(_Cont& cont, std::string_view k, _Valty&& v)
{
    typename _Cont::iterator it = cont.find(k);
    if (it != cont.end())
        it->second = std::forward<_Valty>(v);
    else
        it = cont.emplace(k, std::forward<_Valty>(v)).first;
    return it;
}

constexpr auto empty_sv = ""sv;

}  // namespace hlookup
