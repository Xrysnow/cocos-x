#pragma once
#include "base.hpp"
#include <cmath>
#include <cstring>
#include <string>
#include <string_view>
#include <type_traits>

namespace lua
{
	constexpr auto _ffi_cast_uint64 = R"__(
local ffi = require('ffi')
local store = ffi.new('uint64_t[1]')
local ptr = ffi.cast('uint64_t*', store)
return function(value)
	store[0] = value
    return ptr
end
)__";
	constexpr auto _ffi_cast_int64 = R"__(
local ffi = require('ffi')
local store = ffi.new('int64_t[1]')
local ptr = ffi.cast('int64_t*', store)
return function(value)
	store[0] = value
    return ptr
end
)__";
	// Keep 64-bit integers exact; other numeric cdata can use the number path.
	constexpr auto _ffi_integer_number = R"__(
local ffi = require('ffi')
local istype, tonumber = ffi.istype, tonumber
local signed, unsigned = ffi.typeof('int64_t'), ffi.typeof('uint64_t')
return function(value)
    if istype(signed, value) or istype(unsigned, value) then return nil end
    return tonumber(value)
end
)__";
	constexpr auto _ffi_convert_ptr = R"__(
local ffi = require('ffi')
local C = ffi.C
local _ptr_size = ffi.sizeof('void*')
local _pptr_t = ffi.typeof('void*[1]')
pcall(ffi.cdef, [[void* memcpy(void *p1, void *p2, size_t n);]])
return function(cdata_ptr, userdata)
    C.memcpy(userdata, _pptr_t(cdata_ptr), _ptr_size)
end
)__";

    // Success leaves one function on the stack; failure leaves the stack unchanged.
    inline bool _try_get_internal_helper(lua_State* L, const char* key, const char* def)
    {
		const int top = lua_gettop(L);
		lua_pushstring(L, key);
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			if (luaL_loadstring(L, def) != 0 || lua_pcall(L, 0, 1, 0) != 0)
			{
				lua_settop(L, top);
				return false;
			}
			if (lua_isfunction(L, -1))
			{
				lua_pushstring(L, key);
				lua_pushvalue(L, -2);
				lua_rawset(L, LUA_REGISTRYINDEX);
			}
		}
		if (lua_isfunction(L, -1))
			return true;
		lua_settop(L, top);
		return false;
    }

	inline bool luaval_to_cptr(lua_State* L, int lo, void** outValue)
	{
		if (!L || !outValue) return false;
		lo = _absolute_index(L, lo);
		if (!lo)
		{
			*outValue = nullptr;
			return false;
		}
		const int top = lua_gettop(L);
		void* ret = nullptr;
		bool ok = _try_get_internal_helper(L, "ffi.convert_ptr", _ffi_convert_ptr);
		if (ok)
		{
			lua_pushvalue(L, lo);
			lua_pushlightuserdata(L, &ret);
			ok = lua_pcall(L, 2, 0, 0) == 0;
		}
		lua_settop(L, top);
		*outValue = ok ? ret : nullptr;
		return ok;
	}

	// Truncate, then wrap modulo 2^64 without an out-of-range floating cast.
	inline uint64_t _integer_bits_from_number(lua_Number value)
	{
		if (!std::isfinite(value)) return 0;
		const auto magnitude = static_cast<uint64_t>(
			std::fmod(std::trunc(std::fabs(value)), 0x1p64));
		return value < 0 ? uint64_t(0) - magnitude : magnitude;
	}

	// outValue must hold one 64-bit value, matching the legacy FFI helpers.
	inline bool _luaval_to_integer_cdata(lua_State* L, int lo, void* outValue,
		const char* key, const char* def)
	{
		const int top = lua_gettop(L);
		// Handle floating-to-integer overflow here; legacy FFI behavior is platform-specific.
		bool ok = _try_get_internal_helper(L, "ffi.integer_number", _ffi_integer_number);
		if (ok)
		{
			lua_pushvalue(L, lo);
			ok = lua_pcall(L, 1, 1, 0) == 0;
			if (ok && lua_type(L, -1) == LUA_TNUMBER)
			{
				const auto bits = _integer_bits_from_number(lua_tonumber(L, -1));
				std::memcpy(outValue, &bits, sizeof(bits));
				lua_settop(L, top);
				return true;
			}
			ok = ok && lua_isnil(L, -1);
		}
		lua_settop(L, top);
		if (!ok) return false;
		ok = _try_get_internal_helper(L, key, def);
		if (ok)
		{
			lua_pushvalue(L, lo);
			ok = lua_pcall(L, 1, 1, 0) == 0;
			if (ok)
			{
				void* ret = nullptr;
				ok = luaval_to_cptr(L, -1, &ret) && ret != nullptr;
				if (ok)
					std::memcpy(outValue, ret, sizeof(uint64_t));
			}
		}
		lua_settop(L, top);
		return ok;
	}

	template<typename T, typename Enable = std::enable_if_t<std::is_same_v<T, int64_t> || std::is_same_v<T, uint64_t>, T>>
	bool _luaval_to_integer(lua_State* L, int lo,
		T* outValue,
		size_t targetSize, const char* funcName)
	{
		if (nullptr == L || nullptr == outValue ||
			(targetSize != 1 && targetSize != 2 && targetSize != 4 && targetSize != 8))
			return false;
		lo = _absolute_index(L, lo);
		if (!lo) return false;
		constexpr bool isint64 = std::is_same_v<T, int64_t>;
		const auto type = lua_type(L, lo);
		uint64_t bits;
		if (type == LUA_TCDATA)
		{
			if (!_luaval_to_integer_cdata(L, lo, &bits,
				isint64 ? "ffi.cast_int64" : "ffi.cast_uint64",
				isint64 ? _ffi_cast_int64 : _ffi_cast_uint64)) return false;
		}
		else if (type == LUA_TNUMBER)
			bits = _integer_bits_from_number(lua_tonumber(L, lo));
		else
			return false;
		const uint64_t mask = UINT64_MAX >> ((8 - targetSize) * 8);
		bits &= mask;
		if constexpr (isint64)
			// Complement fits int64_t whenever the target sign bit is set.
			*outValue = bits > (mask >> 1)
				? -static_cast<int64_t>(mask ^ bits) - 1 : static_cast<int64_t>(bits);
		else
			*outValue = bits;
		return true;
	}

	inline bool luaval_to_int(lua_State* L, int lo, int64_t* outValue, size_t targetSize, const char* funcName)
    {
		return _luaval_to_integer<int64_t>(L, lo, outValue, targetSize, funcName);
    }

	inline bool luaval_to_uint(lua_State* L, int lo, uint64_t* outValue, size_t targetSize, const char* funcName)
    {
		return _luaval_to_integer<uint64_t>(L, lo, outValue, targetSize, funcName);
    }

#define TO_NATIVE_SIGNED(_T) template<>\
	struct to_native<_T> {\
		static bool F(lua_State* L, int lo, _T* outValue, const char* funcName = ""){\
			if (!outValue) return false;\
			int64_t i; bool ret = luaval_to_int(L, lo, &i, sizeof(_T), funcName);\
			if (ret) *outValue = (_T)(i); return ret; } }
#define TO_NATIVE_UNSIGNED(_T) template<>\
	struct to_native<_T> {\
		static bool F(lua_State* L, int lo, _T* outValue, const char* funcName = ""){\
			if (!outValue) return false;\
			uint64_t i; bool ret = luaval_to_uint(L, lo, &i, sizeof(_T), funcName);\
			if (ret) *outValue = (_T)(i); return ret; } }

	TO_NATIVE_SIGNED(int8_t);
	TO_NATIVE_SIGNED(int16_t);
	TO_NATIVE_SIGNED(int32_t);
	TO_NATIVE_SIGNED(int64_t);
	TO_NATIVE_UNSIGNED(uint8_t);
	TO_NATIVE_UNSIGNED(uint16_t);
	TO_NATIVE_UNSIGNED(uint32_t);
	TO_NATIVE_UNSIGNED(uint64_t);

#undef TO_NATIVE_SIGNED
#undef TO_NATIVE_UNSIGNED

	// Cover long/unsigned long when fixed-width aliases omit them on LP64/LLP64.
	template<typename T>
	struct to_native<T, std::enable_if_t<(std::is_same_v<T, long> ||
		std::is_same_v<T, unsigned long>) && (sizeof(T) <= sizeof(uint64_t))>> {
		static bool F(lua_State* L, int lo, T* outValue, const char* funcName = "") {
			if (!outValue) return false;
			using type = std::conditional_t<std::is_signed_v<T>, int64_t, uint64_t>;
			type value;
			bool ok;
			if constexpr (std::is_signed_v<T>)
				ok = luaval_to_int(L, lo, &value, sizeof(T), funcName);
			else
				ok = luaval_to_uint(L, lo, &value, sizeof(T), funcName);
			if (ok) *outValue = static_cast<T>(value);
			return ok;
		}
	};

	template<typename T>
	struct to_native<T, std::enable_if_t<std::is_enum_v<T>>> {
		static bool F(lua_State* L, int lo, T* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			using type = std::underlying_type_t<T>;
			type value;
			auto ok = to_native<type>::F(L, lo, &value, fName);
			if (ok) *outValue = (T)value;
			return ok;
		}
	};

	template<>
	struct to_native<bool> {
		static bool F(lua_State* L, int lo, bool* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const auto ok = lua_isnil(L, lo) || lua_isboolean(L, lo);
			if (ok) *outValue = (bool)lua_toboolean(L, lo);
			return ok;
		}
	};

	template<>
	struct to_native<float> {
		static bool F(lua_State* L, int lo, float* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const auto ok = lua_isnumber(L, lo);
			if (ok) *outValue = (float)lua_tonumber(L, lo);
			return ok;
		}
	};

	template<>
	struct to_native<double> {
		static bool F(lua_State* L, int lo, double* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			const auto ok = lua_isnumber(L, lo);
			if (ok) *outValue = lua_tonumber(L, lo);
			return ok;
		}
	};

	template<>
	struct to_native<const char*> {
		static bool F(lua_State* L, int lo, const char** outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_isstring(L, lo))
				return false;
			*outValue = lua_tolstring(L, lo, nullptr);
			return true;
		}
	};

	template<>
	struct to_native<std::string> {
		static bool F(lua_State* L, int lo, std::string* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_isstring(L, lo))
				return false;
			size_t size;
			const auto str = lua_tolstring(L, lo, &size);
			outValue->assign(str, size);
			return true;
		}
	};

#ifdef __cpp_lib_string_view
	template<>
	struct to_native<std::string_view> {
		static bool F(lua_State* L, int lo, std::string_view* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!lua_isstring(L, lo))
				return false;
			size_t size;
			const auto str = lua_tolstring(L, lo, &size);
			*outValue = { str,size };
			return true;
		}
	};
#endif

	template<>
	struct to_lua<bool> {
		static void F(lua_State* L, bool inValue) {
			if (!L) return;
			lua_pushboolean(L, inValue);
		}
	};

	template<typename T>
	struct to_lua<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
		static void F(lua_State* L, T inValue) {
			if (!L) return;
			lua_pushnumber(L, (lua_Number)inValue);
		}
	};

	template<typename T>
	struct to_lua<T, std::enable_if_t<std::is_enum_v<T>>> {
		static void F(lua_State* L, T inValue) {
			if (!L) return;
			using type = std::underlying_type_t<T>;
			lua_pushnumber(L, (lua_Number)(type)inValue);
		}
	};

	template<>
	struct to_lua<const char*> {
		static void F(lua_State* L, const char* inValue) {
			if (!L) return;
			lua_pushstring(L, inValue);
		}
	};

	template<>
	struct to_lua<std::string> {
		static void F(lua_State* L, const std::string& inValue) {
			if (!L) return;
			lua_pushlstring(L, inValue.c_str(), inValue.size());
		}
	};

#ifdef __cpp_lib_string_view
	template<>
	struct to_lua<std::string_view> {
		static void F(lua_State* L, const std::string_view& inValue) {
			if (!L) return;
			lua_pushlstring(L, inValue.data(), inValue.size());
		}
	};
#endif
}
