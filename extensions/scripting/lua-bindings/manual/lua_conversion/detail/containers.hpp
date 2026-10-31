#pragma once
#include "scalar.hpp"
#include <array>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace lua
{
	template<typename K>
	bool _to_native_map_key(lua_State* L, int lo, K* outValue, const char* fName) {
		// String keys are strict; ordinary string arguments keep their coercion rules.
		if constexpr (std::is_same_v<K, std::string> || std::is_same_v<K, const char*>
#ifdef __cpp_lib_string_view
			|| std::is_same_v<K, std::string_view>
#endif
			) {
			if (lua_type(L, lo) != LUA_TSTRING) return false;
		}
		const auto top = lua_gettop(L);
		// Convert a copy: slot replacement (e.g. lua_tolstring) would invalidate lua_next's key.
		lua_pushvalue(L, lo);
		const bool ok = to_native<K>::F(L, top + 1, outValue, fName);
		lua_settop(L, top);
		return ok;
	}

#define LUA_TO_NATIVE_VECTOR(_Ty, _Setter) template<typename T>\
	struct to_native<_Ty<T>> {\
		static bool F(lua_State* L, int lo, _Ty<T>* outValue, const char* fName = "") {\
			LUA_CHECK_TO_NATIVE;\
			if (!lua_istable(L, lo))\
				return false;\
			const size_t len = lua_objlen(L, lo);\
			_Ty<T> result;\
			for (size_t i = 0; i < len; i++) {\
				T value{};\
				lua_pushnumber(L, i + 1);\
				lua_gettable(L, lo);\
				const bool ok = to_native<T>::F(L, top + 1, &value, fName);\
				lua_settop(L, top);\
				if (!ok) return false;\
				result._Setter(value);\
			}\
			*outValue = std::move(result);\
			return true; } };

#define LUA_TO_NATIVE_MAP(_Ty, _Setter) template<typename K, typename V>\
	struct to_native<_Ty<K, V>> {\
		static bool F(lua_State* L, int lo, _Ty<K, V>* outValue, const char* fName = "") {\
			LUA_CHECK_TO_NATIVE;\
			if (!lua_istable(L, lo)) return false;\
			_Ty<K, V> result;\
			lua_pushnil(L);\
			while (lua_next(L, lo) != 0) {\
				K key{}; V value{};\
				if (!_to_native_map_key(L, top + 1, &key, fName) ||\
					!to_native<V>::F(L, top + 2, &value, fName)) {\
					lua_settop(L, top);\
					return false;\
				}\
				result _Setter;\
				lua_settop(L, top + 1);\
			}\
			*outValue = std::move(result);\
			return true; } };

#define LUA_TO_LUA_VECTOR(_Ty) template<typename T>\
	struct to_lua<_Ty<T>> {\
		static void F(lua_State* L, const _Ty<T>& inValue) {\
			if (!L) return;\
			lua_createtable(L, (int)inValue.size(), 0);\
			int index = 1;\
			for (auto& value : inValue) {\
				lua_pushnumber(L, (lua_Number)index);\
				to_lua<T>::F(L, value);\
				lua_rawset(L, -3);\
				++index;\
			} } };

#define LUA_TO_LUA_MAP(_Ty) template<typename K, typename V>\
	struct to_lua<_Ty<K, V>> {\
		static void F(lua_State* L, const _Ty<K, V>& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 0);\
			for (auto& it : inValue) {\
				to_lua<K>::F(L, it.first);\
				to_lua<V>::F(L, it.second);\
				lua_rawset(L, -3);\
			} } };

	template<typename T, size_t Size>
	struct to_native<std::array<T, Size>> {
		static bool F(lua_State* L, int lo, std::array<T, Size>* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			if (lua_objlen(L, lo) != Size) return false;
			std::array<T, Size> result{};
			for (size_t i = 0; i < Size; i++) {
				lua_pushnumber(L, i + 1);
				lua_gettable(L, lo);
				const bool ok = to_native<T>::F(L, top + 1, &result[i], fName);
				lua_settop(L, top);
				if (!ok) return false;
			}
			*outValue = std::move(result);
			return true;
		}
	};

	template<typename T1, typename T2>
	struct to_native<std::pair<T1, T2>> {
		static bool F(lua_State* L, int lo, std::pair<T1, T2>* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const auto type = lua_type(L, lo);
			if (!(type == LUA_TTABLE || type == LUA_TUSERDATA || type == LUA_TCDATA))
				return false;
			T1 value1; T2 value2;
			bool ok = true;
			lua_pushnumber(L, 1);
			lua_gettable(L, lo);
			ok &= to_native<T1>::F(L, top + 1, &value1, fName);
			lua_pop(L, 1);
			if (ok)
				outValue->first = value1;
			else
				return false;
			lua_pushnumber(L, 2);
			lua_gettable(L, lo);
			ok &= to_native<T2>::F(L, top + 1, &value2, fName);
			lua_pop(L, 1);
			if (ok)
				outValue->second = value2;
			return ok;
		}
	};

	template<size_t Index, typename ...Targs>
	struct _to_native_tuple_helper {
		static bool F(lua_State* L, int idx, std::tuple<Targs...>* outValue, const char* fName) {
			using type = std::tuple_element_t<Index - 1, std::tuple<Targs...>>;
			lua_pushnumber(L, Index);
			lua_gettable(L, idx);
			const auto ok = to_native<type>::F(L, lua_gettop(L), &std::get<Index - 1>(*outValue), fName);
			lua_pop(L, 1);
			if (!ok) return false;
			return _to_native_tuple_helper<Index - 1, Targs...>::F(L, idx, outValue, fName);
		}
	};

	template<typename ...Targs>
	struct _to_native_tuple_helper<0, Targs...> {
		static bool F(lua_State* L, int idx, std::tuple<Targs...>* outValue, const char* fName) {
			return true;
		}
	};

	template<typename... Types>
	struct to_native<std::tuple<Types...>> {
		using tuple_type = std::tuple<Types...>;
		static bool F(lua_State* L, int lo, tuple_type* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const auto type = lua_type(L, lo);
			if (!(type == LUA_TTABLE || type == LUA_TUSERDATA || type == LUA_TCDATA))
				return false;
			constexpr size_t size = std::tuple_size_v<tuple_type>;
			return _to_native_tuple_helper<size, Types...>::F(L, lo, outValue, fName);
		}
	};

	template<size_t Size>
	struct to_native<std::bitset<Size>> {
		static bool F(lua_State* L, int lo, std::bitset<Size>* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			if (lua_objlen(L, lo) != Size) return false;
			std::bitset<Size> result;
			for (size_t i = 0; i < Size; i++) {
				bool value = false;
				lua_pushnumber(L, i + 1);
				lua_gettable(L, lo);
				const bool ok = to_native<bool>::F(L, top + 1, &value, fName);
				lua_settop(L, top);
				if (!ok) return false;
				result.set(i, value);
			}
			*outValue = result;
			return true;
		}
	};

	LUA_TO_NATIVE_VECTOR(std::vector, push_back);
	LUA_TO_NATIVE_VECTOR(std::deque, push_back);
	LUA_TO_NATIVE_VECTOR(std::list, push_back);
	LUA_TO_NATIVE_VECTOR(std::set, insert);
	LUA_TO_NATIVE_VECTOR(std::multiset, insert);
	LUA_TO_NATIVE_VECTOR(std::unordered_set, insert);
	LUA_TO_NATIVE_VECTOR(std::unordered_multiset, insert);
	LUA_TO_NATIVE_VECTOR(std::stack, push);
	LUA_TO_NATIVE_VECTOR(std::queue, push);
	LUA_TO_NATIVE_VECTOR(std::priority_queue, push);

	LUA_TO_NATIVE_MAP(std::map, [key] = value);
	LUA_TO_NATIVE_MAP(std::unordered_map, [key] = value);

	template<typename T, size_t Size>
	struct to_lua<std::array<T, Size>> {
		static void F(lua_State* L, const std::array<T, Size>& inValue) {
			if (!L) return;
			lua_createtable(L, (int)inValue.size(), 0);
			int index = 1;
			for (auto& value : inValue) {
				lua_pushnumber(L, (lua_Number)index);
				to_lua<T>::F(L, value);
				lua_rawset(L, -3);
				++index;
			}
		}
	};

	template<typename T1, typename T2>
	struct to_lua<std::pair<T1, T2>> {
		static void F(lua_State* L, const std::pair<T1, T2>& inValue) {
			if (!L) return;
			lua_createtable(L, 2, 0);
			lua_pushnumber(L, 1);
			to_lua<T1>::F(L, inValue.first);
			lua_settable(L, -3);
			lua_pushnumber(L, 2);
			to_lua<T2>::F(L, inValue.second);
			lua_settable(L, -3);
		}
	};

	template<size_t Index, typename... Targs>
	struct _to_lua_tuple_helper {
		static void F(lua_State* L, int idx, const std::tuple<Targs...>& inValue) {
			using type = std::tuple_element_t<Index - 1, std::tuple<Targs...>>;
			lua_pushnumber(L, Index);
			to_lua<type>::F(L, std::get<Index - 1>(inValue));
			lua_settable(L, idx);
			_to_lua_tuple_helper<Index - 1, Targs...>::F(L, idx, inValue);
		}
	};

	template<typename... Targs>
	struct _to_lua_tuple_helper<0, Targs...> {
		static void F(lua_State* L, int idx, const std::tuple<Targs...>& inValue) {
		}
	};

	template<typename... Types>
	struct to_lua<std::tuple<Types...>> {
		using tuple_type = std::tuple<Types...>;
		static void F(lua_State* L, const tuple_type& inValue) {
			if (!L) return;
			constexpr size_t size = std::tuple_size_v<tuple_type>;
			lua_createtable(L, (int)size, 0);
			_to_lua_tuple_helper<size, Types...>::F(L, lua_gettop(L), inValue);
		}
	};

	template<size_t Size>
	struct to_lua<std::bitset<Size>> {
		static void F(lua_State* L, const std::bitset<Size>& inValue) {
			if (!L) return;
			lua_createtable(L, (int)inValue.size(), 0);
			for (size_t i = 0; i < Size; ++i) {
				lua_pushnumber(L, (lua_Number)(i + 1));
				to_lua<bool>::F(L, inValue.test(i));
				lua_rawset(L, -3);
			}
		}
	};

	LUA_TO_LUA_VECTOR(std::vector);
	LUA_TO_LUA_VECTOR(std::deque);
	LUA_TO_LUA_VECTOR(std::list);
	LUA_TO_LUA_VECTOR(std::set);
	LUA_TO_LUA_VECTOR(std::multiset);
	LUA_TO_LUA_VECTOR(std::unordered_set);
	LUA_TO_LUA_VECTOR(std::unordered_multiset);

	LUA_TO_LUA_MAP(std::map);
	LUA_TO_LUA_MAP(std::unordered_map);
}
