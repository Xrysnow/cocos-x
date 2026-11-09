#pragma once
#include "containers.hpp"
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace lua
{
	template<typename T>
	bool luaval_to_native(lua_State* L, int lo, T* outValue, const char* fName = "") {
		return to_native<T>::F(L, lo, outValue, fName);
	}

	template<typename T>
	bool luaval_field_to_native(lua_State* L, int lo, const char* field, T* outValue, const char* fName = "") {
		if (!field) return false;
		LUA_CHECK_TO_NATIVE;
		lua_pushstring(L, field);
		lua_gettable(L, lo);
		const bool ret = to_native<T>::F(L, -1, outValue, fName);
		lua_pop(L, 1);
		return ret;
	}

	template<typename T>
	bool luaval_field_to_native(lua_State* L, int lo, const std::string& field, T* outValue, const char* fName = "") {
		LUA_CHECK_TO_NATIVE;
		lua_pushlstring(L, field.c_str(), field.size());
		lua_gettable(L, lo);
		const bool ret = to_native<T>::F(L, -1, outValue, fName);
		lua_pop(L, 1);
		return ret;
	}

	template<typename T>
	bool luaval_field_to_native(lua_State* L, int lo, int field, T* outValue, const char* fName = "") {
		LUA_CHECK_TO_NATIVE;
		lua_pushinteger(L, field);
		lua_gettable(L, lo);
		const bool ret = to_native<T>::F(L, -1, outValue, fName);
		lua_pop(L, 1);
		return ret;
	}

	template<typename T>
	bool luaval_to_native_array(lua_State* L, int lo, T* outValue, size_t size, const char* fName = "") {
		LUA_CHECK_TO_NATIVE;
		std::vector<T> value;
		if(!to_native<std::vector<T>>::F(L, lo, &value, fName))
			return false;
		if (value.size() != size) return false;
		for (size_t i = 0; i < size; ++i) {
			if constexpr (std::is_same_v<T, bool>)
				outValue[i] = value[i]; // vector<bool> exposes a proxy temporary.
			else
				outValue[i] = _move_local_assignment(value[i]);
		}
		return true;
	}

	template<typename T>
	bool luaval_to_native_array_inplace(lua_State* L, int lo, T* outValue, size_t size, const char* fName = "") {
		LUA_CHECK_TO_NATIVE;
		if (!lua_istable(L, lo)) return false;
		const size_t len = lua_objlen(L, lo);
		if (len != size) return false;
		bool ok = true;
		for (int i = 0; i < size; ++i)
		{
			lua_pushnumber(L, i + 1);
			lua_gettable(L, lo);
			ok &= to_native<T>::F(L, top + 1, outValue + i, fName);
			lua_pop(L, 1);
			if(!ok)
				break;
		}
		return ok;
	}

	template<typename T, class Enable = void>
	struct _can_forward_to_lua : std::false_type {};
	template<typename T>
	struct _can_forward_to_lua<T, std::void_t<decltype(
		to_lua<std::remove_cv_t<std::remove_reference_t<T>>>::F(
			std::declval<lua_State*>(), std::declval<T>()))>> : std::true_type {};

	template<typename T>
	void native_to_luaval(lua_State* L, T&& inValue) {
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
		if constexpr (_can_forward_to_lua<T&&>::value)
			to_lua<type>::F(L, std::forward<T>(inValue));
		else
			// Preserve converters that only accept a named, mutable lvalue.
			to_lua<type>::F(L, inValue);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, const char* field, T&& inValue) {
		if (!field) return;
		if (!L || !(lo = _absolute_index(L, lo))) return;
		const int top = lua_gettop(L);
		lua_pushstring(L, field);
		try {
			native_to_luaval(L, std::forward<T>(inValue));
		} catch (...) {
			lua_settop(L, top);
			throw;
		}
		lua_settable(L, lo);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, const std::string& field, T&& inValue) {
		if (!L || !(lo = _absolute_index(L, lo))) return;
		const int top = lua_gettop(L);
		lua_pushlstring(L, field.c_str(), field.size());
		try {
			native_to_luaval(L, std::forward<T>(inValue));
		} catch (...) {
			lua_settop(L, top);
			throw;
		}
		lua_settable(L, lo);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, int field, T&& inValue) {
		if (!L || !(lo = _absolute_index(L, lo))) return;
		const int top = lua_gettop(L);
		lua_pushinteger(L, field);
		try {
			native_to_luaval(L, std::forward<T>(inValue));
		} catch (...) {
			lua_settop(L, top);
			throw;
		}
		lua_settable(L, lo);
	}

	template<typename T>
	void native_array_to_luaval(lua_State* L, const T* inValue, size_t size) {
		lua_createtable(L, (int)size, 0);
		for (size_t i = 0; i < size; ++i) {
			lua_pushinteger(L, i + 1);
			to_lua<T>::F(L, inValue[i]);
			lua_settable(L, -3);
		}
	}
}

#define LUA_TO_NATIVE_STRUCT2(T, Field1, Field2) \
	template<>\
	struct to_native<T> {\
		static bool F(lua_State* L, int lo, T* outValue, const char* fName = "") {\
			LUA_CHECK_TO_NATIVE;\
			if (!is_indexable(L, lo)) return false;\
			T v;\
			bool ok = luaval_field_to_native(L, lo, #Field1, &v.Field1, fName) &&\
				luaval_field_to_native(L, lo, #Field2, &v.Field2, fName);\
			if (ok) *outValue = v;\
			return ok;\
		}\
	};

#define LUA_TO_NATIVE_STRUCT3(T, Field1, Field2, Field3) \
	template<>\
	struct to_native<T> {\
		static bool F(lua_State* L, int lo, T* outValue, const char* fName = "") {\
			LUA_CHECK_TO_NATIVE;\
			if (!is_indexable(L, lo)) return false;\
			T v;\
			bool ok = luaval_field_to_native(L, lo, #Field1, &v.Field1, fName) &&\
				luaval_field_to_native(L, lo, #Field2, &v.Field2, fName) &&\
				luaval_field_to_native(L, lo, #Field3, &v.Field3, fName);\
			if (ok) *outValue = v;\
			return ok;\
		}\
	};

#define LUA_TO_NATIVE_STRUCT4(T, Field1, Field2, Field3, Field4) \
	template<>\
	struct to_native<T> {\
		static bool F(lua_State* L, int lo, T* outValue, const char* fName = "") {\
			LUA_CHECK_TO_NATIVE;\
			if (!is_indexable(L, lo)) return false;\
			T v;\
			bool ok = luaval_field_to_native(L, lo, #Field1, &v.Field1, fName) &&\
				luaval_field_to_native(L, lo, #Field2, &v.Field2, fName) &&\
				luaval_field_to_native(L, lo, #Field3, &v.Field3, fName) &&\
				luaval_field_to_native(L, lo, #Field4, &v.Field4, fName);\
			if (ok) *outValue = v;\
			return ok;\
		}\
	};

#define LUA_TO_LUA_STRUCT2(T, Field1, Field2) \
	template<>\
	struct to_lua<T> {\
		static void F(lua_State* L, const T& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 2);\
			native_to_luaval_field(L, -1, #Field1, inValue.Field1);\
			native_to_luaval_field(L, -1, #Field2, inValue.Field2);\
		}\
	};

#define LUA_TO_LUA_STRUCT3(T, Field1, Field2, Field3) \
	template<>\
	struct to_lua<T> {\
		static void F(lua_State* L, const T& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 3);\
			native_to_luaval_field(L, -1, #Field1, inValue.Field1);\
			native_to_luaval_field(L, -1, #Field2, inValue.Field2);\
			native_to_luaval_field(L, -1, #Field3, inValue.Field3);\
		}\
	};

#define LUA_TO_LUA_STRUCT4(T, Field1, Field2, Field3, Field4) \
	template<>\
	struct to_lua<T> {\
		static void F(lua_State* L, const T& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 4);\
			native_to_luaval_field(L, -1, #Field1, inValue.Field1);\
			native_to_luaval_field(L, -1, #Field2, inValue.Field2);\
			native_to_luaval_field(L, -1, #Field3, inValue.Field3);\
			native_to_luaval_field(L, -1, #Field4, inValue.Field4);\
		}\
	};

#define LUA_TO_LUA_STRUCT5(T, Field1, Field2, Field3, Field4, Field5) \
	template<>\
	struct to_lua<T> {\
		static void F(lua_State* L, const T& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 5);\
			native_to_luaval_field(L, -1, #Field1, inValue.Field1);\
			native_to_luaval_field(L, -1, #Field2, inValue.Field2);\
			native_to_luaval_field(L, -1, #Field3, inValue.Field3);\
			native_to_luaval_field(L, -1, #Field4, inValue.Field4);\
			native_to_luaval_field(L, -1, #Field5, inValue.Field5);\
		}\
	};

#define LUA_TO_LUA_STRUCT6(T, Field1, Field2, Field3, Field4, Field5, Field6) \
	template<>\
	struct to_lua<T> {\
		static void F(lua_State* L, const T& inValue) {\
			if (!L) return;\
			lua_createtable(L, 0, 6);\
			native_to_luaval_field(L, -1, #Field1, inValue.Field1);\
			native_to_luaval_field(L, -1, #Field2, inValue.Field2);\
			native_to_luaval_field(L, -1, #Field3, inValue.Field3);\
			native_to_luaval_field(L, -1, #Field4, inValue.Field4);\
			native_to_luaval_field(L, -1, #Field5, inValue.Field5);\
			native_to_luaval_field(L, -1, #Field6, inValue.Field6);\
		}\
	};
