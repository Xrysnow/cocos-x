#pragma once
#include "../containers.hpp"
#include "../conversion.hpp"
#include "object.hpp"
#include "cocos2d.h"
#include <functional>
#include <string>
#include <thread>
#include <utility>

namespace lua
{
	LUA_TO_NATIVE_VECTOR(cocos2d::Vector, pushBack);

	LUA_TO_LUA_VECTOR(cocos2d::Vector);

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
			const auto type = lua_type(L, lo);
			bool ok = false;
			if (is_indexable(L, lo))
			{
				lua_pushnumber(L, 1);
				lua_gettable(L, lo);
				if (lua_isnil(L, -1)) // A missing first element selects map conversion.
				{
					lua_pop(L, 1);
					cocos2d::ValueMap dictVal;
					if ((ok = luaval_to_native(L, lo, &dictVal, fName)))
						*outValue = cocos2d::Value(dictVal);
				}
				else
				{
					lua_pop(L, 1);
					cocos2d::ValueVector arrVal;
					if ((ok = luaval_to_native(L, lo, &arrVal, fName)))
						*outValue = cocos2d::Value(arrVal);
				}
			}
			else if (type == LUA_TSTRING)
			{
				std::string stringValue;
				if ((ok = luaval_to_native(L, lo, &stringValue, fName)))
					*outValue = cocos2d::Value(stringValue);
			}
			else if (type == LUA_TBOOLEAN)
			{
				bool boolVal = false;
				if ((ok = luaval_to_native(L, lo, &boolVal, fName)))
					*outValue = cocos2d::Value(boolVal);
			}
			else if (type == LUA_TNUMBER)
			{
				double doubleVal = 0;
				if ((ok = luaval_to_native(L, lo, &doubleVal, fName)))
					*outValue = cocos2d::Value(doubleVal);
			}
			else if (type == LUA_TNIL)
			{
				*outValue = cocos2d::Value::Null;
				ok = true;
			}
			return ok;
		}
	};

	template<>
	struct to_lua<cocos2d::Value> {
		static void F(lua_State* L, const cocos2d::Value& inValue) {
			if (!L) return;
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
