#pragma once
#include "containers.hpp"
#include <cstddef>
#include <string>
#include <type_traits>
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
		for (size_t i = 0; i < size; ++i)
			outValue[i] = value[i];
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

	template<typename T>
	void native_to_luaval(lua_State* L, T&& inValue) {
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
		to_lua<type>::F(L, inValue);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, const char* field, T&& inValue) {
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
		if (!field) return;
		if (!L || !(lo = _absolute_index(L, lo))) return;
		lua_pushstring(L, field);
		to_lua<type>::F(L, inValue);
		lua_settable(L, lo);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, const std::string& field, T&& inValue) {
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
		if (!L || !(lo = _absolute_index(L, lo))) return;
		lua_pushlstring(L, field.c_str(), field.size());
		to_lua<type>::F(L, inValue);
		lua_settable(L, lo);
	}

	template<typename T>
	void native_to_luaval_field(lua_State* L, int lo, int field, T&& inValue) {
		using type = std::remove_cv_t<std::remove_reference_t<T>>;
		if (!L || !(lo = _absolute_index(L, lo))) return;
		lua_pushinteger(L, field);
		to_lua<type>::F(L, inValue);
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
