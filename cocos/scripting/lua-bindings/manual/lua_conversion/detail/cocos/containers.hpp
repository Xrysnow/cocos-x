#pragma once
#include "../containers.hpp"
#include "../conversion.hpp"
#include "object.hpp"
#include "cocos2d.h"
#include <functional>
#include <limits>
#include <string>
#include <thread>
#include <utility>

namespace lua
{
	// cocos::Vector requires non-null Ref pointers. Shared Ref conversion allows
	// nil for ordinary pointer arguments, so reject it before native pushBack.
	template<typename T>
	struct to_native<cocos2d::Vector<T>> {
		static bool F(lua_State* L, int lo, cocos2d::Vector<T>* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			const size_t len = lua_objlen(L, lo);
			cocos2d::Vector<T> result;
			for (size_t i = 0; i < len; ++i) {
				T value{};
				lua_pushnumber(L, i + 1);
				lua_gettable(L, lo);
				const bool ok = to_native<T>::F(L, top + 1, &value, fName);
				lua_settop(L, top);
				if (!ok || !value) return false;
				result.pushBack(value);
			}
			*outValue = std::move(result);
			return true;
		}
	};

	LUA_TO_LUA_VECTOR(cocos2d::Vector);

	// StringMap uses transparent hash/equality parameters. Match the complete
	// Map type instead of assuming its default std::hash specialization.
	template<typename K, typename V, typename Hash, typename Equal>
	struct to_lua<cocos2d::Map<K, V, Hash, Equal>> {
		static void F(lua_State* L, const cocos2d::Map<K, V, Hash, Equal>& inValue) {
			if (!L) return;
			lua_createtable(L, 0, static_cast<int>(inValue.size()));
			const int table = lua_gettop(L);
			for (const auto& entry : inValue) {
				native_to_luaval(L, entry.first);
				native_to_luaval(L, entry.second);
				lua_rawset(L, table);
			}
		}
	};

	template<typename T>
	struct to_native<hlookup::string_map<T>> {
		static bool F(lua_State* L, int lo, hlookup::string_map<T>* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			hlookup::string_map<T> result;
			lua_pushnil(L);
			while (lua_next(L, lo) != 0)
			{
				std::string key; T value{};
				if (!_to_native_map_key(L, top + 1, &key, fName) ||
					!to_native<T>::F(L, top + 2, &value, fName))
				{
					lua_settop(L, top);
					return false;
				}
				result[key] = value;
				lua_settop(L, top + 1);
			}
			*outValue = std::move(result);
			return true;
		}
	};

	template<typename T>
	struct to_lua<hlookup::string_map<T>> {
		static void F(lua_State* L, const hlookup::string_map<T>& inValue) {
			if (!L) return;
			lua_createtable(L, 0, (int)inValue.size());
			const int table = lua_gettop(L);
			for (auto&& it : inValue)
			{
				lua_pushlstring(L, it.first.c_str(), it.first.size());
				to_lua<T>::F(L, it.second);
				lua_settable(L, table);
			}
		}
	};

	template<>
	struct to_native<hlookup::string_set> {
		static bool F(lua_State* L, int lo, hlookup::string_set* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_istable(L, lo)) return false;
			const size_t len = lua_objlen(L, lo);
			hlookup::string_set result;
			for (size_t i = 0; i < len; i++) {
				std::string value;
				lua_pushnumber(L, i + 1);
				lua_gettable(L, lo);
				const bool ok = to_native<std::string>::F(L, top + 1, &value, fName);
				lua_settop(L, top);
				if (!ok) return false;
				result.insert(value);
			}
			*outValue = std::move(result);
			return true;
		}
	};

	template<>
	struct to_lua<hlookup::string_set> {
		static void F(lua_State* L, const hlookup::string_set& inValue) {
			if (!L) return;
			lua_createtable(L, (int)inValue.size(), 0);
			const int table = lua_gettop(L);
			int i = 1;
			for (auto&& it : inValue)
			{
				lua_pushlstring(L, it.c_str(), it.size());
				lua_rawseti(L, table, i);
				++i;
			}
		}
	};

	template<>
	struct to_native<cocos2d::Value> {
		static bool F(lua_State* L, int lo, cocos2d::Value* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const void* ancestors[64]{};
			cocos2d::Value result;
			const bool ok = read(L, lo, result, ancestors, 0);
			lua_settop(L, top);
			if (ok) *outValue = std::move(result);
			return ok;
		}

	private:
		// Value is a data snapshot: inspect raw entries, never call metamethods.
		// The ancestor path rejects cycles while allowing shared sibling tables.
		static bool read(lua_State* L, int index, cocos2d::Value& result,
			const void** ancestors, size_t depth) {
			switch (lua_type(L, index)) {
			case LUA_TNIL:
				result = cocos2d::Value::Null;
				return true;
			case LUA_TBOOLEAN:
				result = cocos2d::Value(lua_toboolean(L, index) != 0);
				return true;
			case LUA_TNUMBER:
				result = cocos2d::Value(lua_tonumber(L, index));
				return true;
			case LUA_TSTRING: {
				size_t size = 0;
				const auto* text = lua_tolstring(L, index, &size);
				result = cocos2d::Value(std::string_view(text, size));
				return true;
			}
			case LUA_TTABLE: {
				if (depth == 64 || !lua_checkstack(L, 4)) return false;
				const auto* identity = lua_topointer(L, index);
				for (size_t i = 0; i < depth; ++i)
					if (ancestors[i] == identity) return false;
				ancestors[depth] = identity;
				const int top = lua_gettop(L);
				const bool ok = read_table(L, index, result, ancestors, depth + 1);
				lua_settop(L, top);
				return ok;
			}
			default:
				return false;
			}
		}

		static bool read_table(lua_State* L, int index, cocos2d::Value& result,
			const void** ancestors, size_t depth) {
			size_t numeric = 0, strings = 0;
			lua_Number maximum = 0;
			lua_pushnil(L);
			while (lua_next(L, index)) {
				if (lua_type(L, -2) == LUA_TSTRING) {
					++strings;
				} else if (lua_type(L, -2) == LUA_TNUMBER) {
					const auto key = lua_tonumber(L, -2);
					if (!(key >= 1 && key <= std::numeric_limits<int>::max()) ||
						key != static_cast<int>(key)) return false;
					++numeric;
					if (key > maximum) maximum = key;
				} else return false;
				lua_pop(L, 1);
			}
			// Positive integral keys must be exactly 1..N, without string fields.
			if (numeric && (strings || maximum != numeric)) return false;
			if (numeric) {
				cocos2d::ValueVector values;
				values.reserve(numeric);
				for (size_t i = 0; i < numeric; ++i) {
					lua_rawgeti(L, index, static_cast<int>(i + 1));
					cocos2d::Value value;
					if (!read(L, lua_gettop(L), value, ancestors, depth)) return false;
					values.emplace_back(std::move(value));
					lua_pop(L, 1);
				}
				result = cocos2d::Value(std::move(values));
			} else {
				// An empty table consistently represents an empty string dictionary.
				cocos2d::ValueMap values;
				lua_pushnil(L);
				while (lua_next(L, index)) {
					size_t size = 0;
					const auto* key = lua_tolstring(L, -2, &size);
					cocos2d::Value value;
					if (!read(L, lua_gettop(L), value, ancestors, depth)) return false;
					values[std::string(key, size)] = std::move(value);
					lua_pop(L, 1);
				}
				result = cocos2d::Value(std::move(values));
			}
			return true;
		}
	};

	template<>
	struct to_lua<cocos2d::Value> {
		static void F(lua_State* L, const cocos2d::Value& inValue) {
			if (!L) return;
			luaL_checkstack(L, 4, "Value result stack overflow");
			switch (inValue.getTypeFamily())
			{
			case cocos2d::Value::Type::NONE:
				lua_pushnil(L);
				break;
			case cocos2d::Value::Type::BOOLEAN:
				lua_pushboolean(L, inValue.asBool());
				break;
			case cocos2d::Value::Type::FLOAT:
			case cocos2d::Value::Type::DOUBLE:
				lua_pushnumber(L, inValue.asDouble());
				break;
			case cocos2d::Value::Type::INTEGER:
				lua_pushinteger(L, inValue.asInt64());
				break;
			case cocos2d::Value::Type::STRING:
				native_to_luaval(L, inValue.asStringRef());
				break;
			case cocos2d::Value::Type::VECTOR:
				native_to_luaval(L, inValue.asValueVector());
				break;
			case cocos2d::Value::Type::MAP:
				native_to_luaval(L, inValue.asValueMap());
				break;
			case cocos2d::Value::Type::INT_KEY_MAP:
				native_to_luaval(L, inValue.asIntKeyMap());
				break;
			default:
				luaL_error(L, "unsupported cocos2d::Value type: %d", static_cast<int>(inValue.getType()));
				break;
			}
		}
	};

	template<>
	struct to_lua<std::thread::id> {
		static void F(lua_State* L, const std::thread::id& inValue) {
			if (!L) return;
			lua_pushinteger(L, std::hash<std::thread::id>{}(inValue));
		}
	};
}
