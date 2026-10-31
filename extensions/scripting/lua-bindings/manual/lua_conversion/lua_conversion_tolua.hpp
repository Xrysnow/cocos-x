#pragma once
#include "platform/CCPlatformMacros.h"
#include "tolua++.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include <array>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Follow cocos' debug policy unless checks are explicitly overridden.
#ifndef CC_LUA_BINDING_CHECKS
#if CC_DEBUG > 0
#define CC_LUA_BINDING_CHECKS 1
#else
#define CC_LUA_BINDING_CHECKS 0
#endif
#endif

extern std::unordered_map<uintptr_t, const char*> g_luaType;
extern std::unordered_map<std::string, const char*> g_typeCast;

namespace lua
{
	constexpr int LUA_TPROTO = LUA_TTHREAD + 1;
    constexpr int LUA_TCDATA = LUA_TTHREAD + 2;
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

    template<typename T>
    const char* _getClassNameByType()
    {
		using key_type = decltype(g_luaType)::key_type;
		using type = std::conditional_t<std::is_integral_v<key_type>, key_type, const char*>;
		const auto key = reinterpret_cast<type>(typeid(T).name());
        const auto it = g_luaType.find(key);
        if (it != g_luaType.end())
            return it->second;
        return "";
    }

    template<typename T>
    std::string getClassNameByType()
    {
        return _getClassNameByType<T>();
    }

    template<typename T>
    void registerLuaType(const char* luaType, const char* castType)
    {
		using key_type = decltype(g_luaType)::key_type;
		using type = std::conditional_t<std::is_integral_v<key_type>, key_type, const char*>;
		const auto key = reinterpret_cast<type>(typeid(T).name());
        g_luaType[key] = luaType;
        g_typeCast[castType] = luaType;
    }

    inline int push_table_instance(lua_State* L, int lo)
    {
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return 0;
        }
        if (lua_istable(L, lo)) {
            lua_pushstring(L, ".c_instance");
            lua_gettable(L, lo);
            if (lua_type(L, -1) == LUA_TUSERDATA) {
                lua_replace(L, lo);
                return 1;
            }
            lua_pop(L, 1);
            return 0;
        }
        return 0;
    }

    inline int isusertype(lua_State* L, int lo, const char* type)
    {
        if (!L || !type || !*type)
            return 0;
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return 0;
        }
        if (lo == 0 || lo > lua_gettop(L))
            return 0;
        if (lua_type(L, lo) != LUA_TUSERDATA) {
            if (!push_table_instance(L, lo)) {
                return 0;
            }
        }
        if (lua_objlen(L, lo) != sizeof(void*))
            return 0;
        if (lua_getmetatable(L, lo))        /* if metatable? */
        {
            lua_rawget(L, LUA_REGISTRYINDEX);  /* get registry[mt] */
            const char *tn = lua_tostring(L, -1);
            const int r = tn && (strcmp(tn, type) == 0);
            lua_pop(L, 1);
            if (r)
                return 1;
            else
            {
                /* check if it is a specialized class */
                lua_pushstring(L, "tolua_super");
                lua_rawget(L, LUA_REGISTRYINDEX); /* get super */
                if (!lua_istable(L, -1)) {
                    lua_pop(L, 1);
                    return 0;
                }
                lua_getmetatable(L, lo);
                lua_rawget(L, -2);                /* get super[mt] */
                if (lua_istable(L, -1))
                {
                    lua_pushstring(L, type);
                    lua_rawget(L, -2);                /* get super[mt][type] */
                    const int b = lua_toboolean(L, -1);
                    lua_pop(L, 3);
                    if (b)
                        return 1;
                }
                else
                    lua_pop(L, 2);
            }
        }
        return 0;
    }

    inline void* _tousertype(lua_State* L, int lo)
    {
        if (!L)
            return nullptr;
        if (lo < 0 && lo > LUA_REGISTRYINDEX) {
            lo = lua_gettop(L) + lo + 1;
            if (lo <= 0)
                return nullptr;
        }
        if (lo == 0 || lo > lua_gettop(L))
            return nullptr;
        if (lua_type(L, lo) != LUA_TUSERDATA) {
            if (!push_table_instance(L, lo))
                return nullptr;
        }
        if (lua_objlen(L, lo) != sizeof(void*))
            return nullptr;
        const auto u = lua_touserdata(L, lo);
        return u ? *(void**)u : nullptr;
    }

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

	inline bool is_indexable(lua_State* L, int lo)
	{
		const auto t = lua_type(L, lo);
		return t == LUA_TTABLE || t == LUA_TUSERDATA || t == LUA_TCDATA;
	}

	////////////////////////////////////////////////////////////////////////////////

	// fix stack indices and keep pseudo-indices, 0 means invalid
	inline int _absolute_index(lua_State* L, int lo) {
		if (!L) return 0;
		if (lo <= LUA_REGISTRYINDEX) return lo;
		const int top = lua_gettop(L);
		if (lo < 0) lo += top + 1;
		return lo > 0 && lo <= top ? lo : 0;
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

	// Both legacy integer helpers return storage for exactly one 64-bit value.
	inline bool _luaval_to_integer_cdata(lua_State* L, int lo, void* outValue,
		const char* key, const char* def)
	{
		const int top = lua_gettop(L);
		// FFI floating-to-integer overflow is platform-specific. Extract those
		// numbers first, without changing the legacy pre-registered helpers.
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

	////////////////////////////////////////////////////////////////////////////////

	inline int luafunction_to_handler(lua_State* L, int lo, const char* fName)
	{
		const int index = _absolute_index(L, lo);
		if (!index) return 0;
		const int handler = toluafix_ref_function(L, index, 0);
		if (handler == 0)
			return 0;
		std::string key;
		if (fName) key = fName;
		if (!key.empty()) {
			key += "::" + std::to_string(lo);
			lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
			lua_rawget(L, LUA_REGISTRYINDEX); // ... t
			lua_pushlstring(L, key.c_str(), key.size()); // ... t k
			// Names are lookup aliases, not ownership or replacement keys.
			lua_pushinteger(L, handler); // ... t k v
			lua_settable(L, -3); // ... t
			lua_pop(L, 1);
		}
		return handler;
	}

	inline int query_luafunction_handler(lua_State* L, int lo, const char* fName)
    {
		std::string key;
		if (fName) key = fName;
		if (!key.empty()) {
			int value = 0;
			key += "::" + std::to_string(lo);
			lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
			lua_rawget(L, LUA_REGISTRYINDEX); // ... t
			lua_pushlstring(L, key.c_str(), key.size()); // ... t k
			lua_rawget(L, -2); // ... t v
			if (lua_isnumber(L, -1))
				value = (int)lua_tointeger(L, -1);
			lua_pop(L, 2);
			return value;
		}
		return 0;
    }

	inline void handler_to_luafunction(lua_State* L, int handler)
    {
		if (handler != 0)
			toluafix_get_function_by_refid(L, handler);
		else
			lua_pushnil(L);
    }

	// Lua-owned storage for the state lifetime sentinel.
	template<typename T>
	struct _callback_userdata {
		using value_type = std::shared_ptr<T>;
		value_type* value;
		alignas(value_type) unsigned char storage[sizeof(value_type)];
		static void* key() { static char k; return &k; }
		// Keep the userdata rooted during reset: destroying its value may enter Lua.
		static void reset(_callback_userdata* p) {
			if (p->value) {
				auto* value = p->value;
				// Invalidate first so reentrant __gc cannot destroy the value twice.
				p->value = nullptr;
				value->~value_type();
			}
		}
		static int collect(lua_State* L) {
			if (lua_type(L, 1) != LUA_TUSERDATA || lua_objlen(L, 1) != sizeof(_callback_userdata)
				|| !lua_getmetatable(L, 1)) return 0;
			lua_pushlightuserdata(L, key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			const bool matches = lua_rawequal(L, -1, -2) != 0;
			lua_pop(L, 2);
			if (matches) reset(static_cast<_callback_userdata*>(lua_touserdata(L, 1)));
			return 0;
		}
		static _callback_userdata* push(lua_State* L, const value_type& value) {
			lua_pushlightuserdata(L, key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				lua_createtable(L, 0, 1);
				lua_pushcfunction(L, collect);
				lua_setfield(L, -2, "__gc");
				// Allocation can run a finalizer which publishes this metatable.
				// Reuse that canonical identity instead of invalidating its userdata.
				lua_pushlightuserdata(L, key());
				lua_rawget(L, LUA_REGISTRYINDEX);
				if (!lua_isnil(L, -1)) {
					lua_replace(L, -2);
				} else {
					lua_pop(L, 1);
					lua_pushlightuserdata(L, key());
					lua_pushvalue(L, -2);
					lua_rawset(L, LUA_REGISTRYINDEX);
				}
			}
			auto* p = new (lua_newuserdata(L, sizeof(_callback_userdata))) _callback_userdata{};
			lua_insert(L, -2);
			lua_setmetatable(L, -2);
			p->value = new (p->storage) value_type(value);
			return p;
		}
	};

	struct _callback_reference;
	// The mutex protects cross-thread release bookkeeping, not the Lua VM.
	struct _callback_state {
		const std::thread::id thread = std::this_thread::get_id();
		std::mutex mutex;
		// Common reads avoid the mutex; queue writers still serialize with close().
		std::atomic<bool> alive{ true };
		std::atomic<_callback_reference*> pending{ nullptr };
		bool callable() const {
			return thread == std::this_thread::get_id() && alive.load(std::memory_order_acquire);
		}
		void drain(lua_State* L);
		void close();
	};

	// One registration, shared by C++ copies and temporary call anchors.
	struct _callback_reference {
		std::shared_ptr<_callback_state> state;
		lua_State* L;
		// Own the diagnostic name; the caller's fName may be temporary.
		std::string name;
		std::string key;
		enum class kind { handler, direct };
		kind ownership = kind::handler;
		int direct_ref = LUA_NOREF;
		int handler = 0;
		int thread_ref = LUA_NOREF;
		_callback_reference* next = nullptr;
		void unref(lua_State* current) {
			if (ownership == kind::direct) {
				luaL_unref(current, LUA_REGISTRYINDEX, direct_ref);
			} else if (handler) {
				toluafix_remove_function_by_refid(current, handler);
				if (!key.empty()) {
					lua_pushstring(current, TOLUA_REFID_FUNCTION_MAPPING);
					lua_rawget(current, LUA_REGISTRYINDEX);
					lua_pushlstring(current, key.data(), key.size());
					lua_rawget(current, -2);
					// An older callback must not remove a newer callback's alias.
					const bool matches = lua_isnumber(current, -1)
						&& lua_tointeger(current, -1) == handler;
					lua_pop(current, 1);
					if (matches) {
						lua_pushlstring(current, key.data(), key.size());
						lua_pushnil(current);
						lua_rawset(current, -3);
					}
					lua_pop(current, 1);
				}
			}
			// Last: current may itself be the coroutine kept alive by this ref.
			luaL_unref(current, LUA_REGISTRYINDEX, thread_ref);
		}
		static void release(_callback_reference* p) {
			if (!p->state) { delete p; return; }
			bool active;
			{
				std::lock_guard<std::mutex> lock(p->state->mutex);
				active = p->state->alive.load(std::memory_order_relaxed);
				if (active && p->state->thread != std::this_thread::get_id()) {
					// Never access Lua from a worker. No allocation in this deleter.
					// Drain on the next owner-thread registration/call, or discard on close.
					p->next = p->state->pending.load(std::memory_order_relaxed);
					p->state->pending.store(p, std::memory_order_release);
					return;
				}
			}
			if (active) p->unref(p->L);
			delete p;
		}
	};

	inline void _callback_state::drain(lua_State* L) {
		if (!pending.load(std::memory_order_acquire)) return;
		_callback_reference* list;
		{
			std::lock_guard<std::mutex> lock(mutex);
			list = pending.exchange(nullptr, std::memory_order_relaxed);
		}
		// Unref outside the lock: Lua GC can reenter callback destruction.
		while (list) {
			auto* p = list;
			list = p->next;
			p->unref(L);
			delete p;
		}
	}
	inline void _callback_state::close() {
		_callback_reference* list;
		{
			std::lock_guard<std::mutex> lock(mutex);
			alive.store(false, std::memory_order_release);
			list = pending.exchange(nullptr, std::memory_order_relaxed);
		}
		while (list) {
			auto* p = list;
			list = p->next;
			delete p; // lua_close owns the registry; do not use Lua here.
		}
	}
	// Only the registry owns this sentinel; its finalizer marks surviving refs closed.
	struct _callback_lifetime {
		std::shared_ptr<_callback_state> state = std::make_shared<_callback_state>();
		~_callback_lifetime() { state->close(); }
	};
	inline void* _callback_state_key() { static char key; return &key; }
	// Leaves the canonical sentinel on the stack, including if allocation
	// reentered registration and published one while our candidate was built.
	inline void _push_callback_lifetime(lua_State* L, const std::shared_ptr<_callback_lifetime>& lifetime) {
		using holder = _callback_userdata<_callback_lifetime>;
		auto* candidate = holder::push(L, lifetime);
		lua_pushlightuserdata(L, _callback_state_key());
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (!lua_isnil(L, -1)) {
			holder::reset(candidate);
			lua_remove(L, -2);
		} else {
			lua_pop(L, 1);
			lua_pushlightuserdata(L, _callback_state_key());
			lua_pushvalue(L, -2);
			lua_rawset(L, LUA_REGISTRYINDEX);
		}
	}
	// Coroutines share the registry and therefore the same lifetime sentinel.
	inline std::shared_ptr<_callback_state> _get_callback_state(lua_State* L) {
		using holder = _callback_userdata<_callback_lifetime>;
		lua_pushlightuserdata(L, _callback_state_key());
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			_push_callback_lifetime(L, std::make_shared<_callback_lifetime>());
		}
		auto* p = static_cast<holder*>(lua_touserdata(L, -1));
		auto state = p->value ? (*p->value)->state : nullptr;
		lua_pop(L, 1);
		if (state && state->callable()) state->drain(L);
		return state;
	}
	inline std::shared_ptr<_callback_reference> _own_luafunction(lua_State* L, int lo, const char* name) {
		const int index = _absolute_index(L, lo);
		if (!index || !lua_isfunction(L, index)) return nullptr;
		auto state = _get_callback_state(L);
		if (!state || !state->callable()) return nullptr;
		auto ref = std::shared_ptr<_callback_reference>(new _callback_reference{
			state, L, name ? name : "", "" }, _callback_reference::release);
		if (!ref->name.empty()) ref->key = ref->name + "::" + std::to_string(lo);
		// Pin the originating coroutine while native code holds the callback.
		lua_pushthread(L);
		ref->thread_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		ref->handler = luafunction_to_handler(L, lo, name);
		return ref->handler ? ref : nullptr;
	}

    ////////////////////////////////////////////////////////////////////////////////

	template<typename T, class Enable = void> struct to_native {};
	template<typename T, class Enable = void> struct owned_callback_push;
	template<typename T, class Enable = void> struct owned_callback_read;

#define LUA_CHECK_TO_NATIVE\
	const auto top = L ? lua_gettop(L) : 0;\
	do {\
		if (nullptr == L || nullptr == outValue || !(lo = ::lua::_absolute_index(L, lo)))\
			return false;\
	} while (false)

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
		// A converter may replace its slot (e.g. lua_tolstring on a number).
		// Never expose lua_next's live iteration key to such a conversion.
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

	// Fixed-width aliases may omit long and unsigned long on LP64/LLP64.
	// Existing explicit specializations keep priority over this fallback.
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

	////////////////////////////////////////////////////////////////////////////////

	template<typename T, class Enable = void> struct to_lua {};

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

	template<size_t Index, typename Targ = void, typename... Targs>
	struct _to_lua_function_helper {
		static void F(lua_State* L, Targ&& arg, Targs&&... args) {
			native_to_luaval(L, arg);
			_to_lua_function_helper<Index - 1, Targs...>::F(L, std::forward<Targs>(args)...);
		}
	};

	template<>
	struct _to_lua_function_helper<0> {
		static void F(lua_State* L) {
		}
	};

	// Do not invoke tostring/metamethods outside a protected Lua frame.
	inline const char* _callback_error_text(lua_State* L, int index) {
		return lua_type(L, index) == LUA_TSTRING ? lua_tostring(L, index)
			: lua_typename(L, lua_type(L, index));
	}
	inline void _callback_log_error(lua_State* L, const char* name) {
		std::fprintf(stderr, "[LUA ERROR] callback (%s): %s\n", name, _callback_error_text(L, -1));
	}
	inline int _callback_report_error(lua_State* L, const char* name) {
		lua_pushfstring(L, "[LUA ERROR] callback (%s): %s",
			name, _callback_error_text(L, 1));
		// Match LuaStack's reporting hook, but protect the reporter too. Its return
		// value is irrelevant (the application's hook does not return a string).
		lua_pushliteral(L, "__G__TRACKBACK__");
		lua_rawget(L, LUA_GLOBALSINDEX);
		if (lua_isfunction(L, -1)) {
			lua_pushvalue(L, 2);
			if (lua_pcall(L, 1, 0, 0) != 0) {
				std::fprintf(stderr, "%s\n[LUA ERROR] callback reporter: %s\n",
					lua_tostring(L, 2), _callback_error_text(L, -1));
			}
		} else {
			std::fprintf(stderr, "%s\n", lua_tostring(L, 2));
		}
		lua_pushvalue(L, 2);
		return 1;
	}

	template<typename F>
	struct _callback_call {
		_callback_reference* callback;
		F* invoke;
		bool completed = false;
		bool entered = false;
		_callback_call* previous;
		// One non-owning activation per signature/thread. The C++ guard stays
		// outside both protected Lua frames and restores nested invocations.
		inline static thread_local _callback_call* active = nullptr;
		_callback_call(_callback_reference* ref, F* function)
			: callback(ref), invoke(function), previous(active) { active = this; }
		_callback_call(const _callback_call&) = delete;
		_callback_call& operator=(const _callback_call&) = delete;
		~_callback_call() { active = previous; }
		static _callback_call* context(lua_State* L) {
			return lua_type(L, 1) == LUA_TLIGHTUSERDATA
				&& lua_touserdata(L, 1) == active ? active : nullptr;
		}
		static void push_cached(lua_State* L, lua_CFunction function, void* key) {
			// Shared per VM/signature, with no callback owner or C++ frame in
			// upvalues. Callers keep initial allocation inside a protected frame.
			lua_pushlightuserdata(L, key);
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				lua_pushcfunction(L, function);
				// The reporter uses explicit globals and needs no caller env.
				// Avoid keeping the first caller's sandbox/coroutine env alive.
				lua_newtable(L);
				lua_setfenv(L, -2);
				lua_pushlightuserdata(L, key);
				lua_pushvalue(L, -2);
				lua_rawset(L, LUA_REGISTRYINDEX);
			}
		}
		static int report(lua_State* L) {
			auto* context = active;
			if (!context) return luaL_error(L, "expired Lua callback error handler");
			return _callback_report_error(L, context->callback->name.c_str());
		}
		static int run(lua_State* L) {
			auto* context = static_cast<_callback_call*>(lua_touserdata(L, lua_upvalueindex(1)));
			if (!context || context != active || context->entered)
				return luaL_error(L, "expired Lua callback invocation");
			context->entered = true;
			// A retained trampoline must not retain this C++ frame. A fresh
			// execution closure also preserves its caller's Lua environment.
			lua_pushnil(L);
			lua_replace(L, lua_upvalueindex(1));
			(*context->invoke)(L);
			context->completed = true;
			return 0;
		}
		static int enter(lua_State* L) {
			auto* context = _callback_call::context(L);
			if (!context || context->entered) return luaL_error(L, "expired Lua callback setup");
			lua_settop(L, 0);
			context->callback->state->drain(L);
			static char report_key;
			push_cached(L, report, &report_key);
			lua_pushlightuserdata(L, context);
			lua_pushcclosure(L, run, 1);
			const int status = lua_pcall(L, 0, 0, 1);
			if (status != 0) {
				context->completed = false;
				if (status != LUA_ERRRUN)
					_callback_log_error(L, context->callback->name.c_str());
			}
			return 0;
		}
	};

	template<typename F>
	bool _call_luafunction(const std::shared_ptr<_callback_reference>& ref, F&& invoke) {
		// All C++ owners live outside both protected frames, including when the
		// callback clears its own slot or the reporting hook triggers GC/reentry.
		auto keep = ref;
		if (!keep->state->callable()) return false;
		auto* L = keep->L;
		const int top = lua_gettop(L);
		_callback_call<F> context{ keep.get(), &invoke };
		// cpcall also protects frame setup, argument conversion and result conversion.
		if (lua_cpcall(L, _callback_call<F>::enter, &context) != 0) {
			context.completed = false;
			_callback_log_error(L, keep->name.c_str());
		}
		lua_settop(L, top);
		return context.completed;
	}


	// Existing converters run in the bridge's fixed empty environment. Only
	// std::function payloads are excluded, including inside supported containers.
	// Converters remain responsible for Lua-error cleanup and borrowed lifetimes.
	template<typename T> struct _callback_has_function;
	template<typename T>
	using _callback_value = std::remove_cv_t<std::remove_reference_t<T>>;
	template<typename T> struct _callback_has_function : std::false_type {};
	template<typename R, typename... Args>
	struct _callback_has_function<std::function<R(Args...)>> : std::true_type {};
	template<template<typename...> class C, typename... Types>
	struct _callback_has_function<C<Types...>>
		: std::disjunction<_callback_has_function<_callback_value<Types>>...> {};
	template<typename T, size_t Size>
	struct _callback_has_function<std::array<T, Size>> : _callback_has_function<_callback_value<T>> {};
	template<typename T>
	struct _callback_has_function<T*> : _callback_has_function<_callback_value<T>> {};

	template<typename T, class Enable>
	struct owned_callback_push : std::bool_constant<!_callback_has_function<_callback_value<T>>::value> {};
	template<typename T, class Enable>
	struct owned_callback_read : std::bool_constant<!_callback_has_function<_callback_value<T>>::value> {};

	// Everything that owns C++ storage lives outside the protected Lua frame.
	// Successful Lua roots are recorded immediately, including partial creation.
	// Trusted debug hooks may observe these frames; private entry points are not
	// authenticated against direct calls or replay.
	struct _owned_callback_registration {
		std::shared_ptr<_callback_reference> ref;
		std::shared_ptr<_callback_lifetime> lifetime;
		bool completed = false;
		bool permitted = false;
		bool needs_lifetime = false;
		_owned_callback_registration* previous;
		inline static thread_local _owned_callback_registration* active = nullptr;
		_owned_callback_registration(lua_State* L, const char* name)
			: ref(new _callback_reference{ nullptr, L, name ? name : "", "" }, _callback_reference::release),
			previous(active) {
			ref->ownership = _callback_reference::kind::direct;
			active = this;
		}
		~_owned_callback_registration() { active = previous; }
		_owned_callback_registration(const _owned_callback_registration&) = delete;
		_owned_callback_registration& operator=(const _owned_callback_registration&) = delete;
		static void* finish_key() { static char key; return &key; }
		static int finish(lua_State* L) {
			auto* c = active;
			if (!c || !c->permitted || c->ref->L != L
				|| lua_type(L, 1) != LUA_TFUNCTION)
				return luaL_error(L, "expired Lua callback registration");
			c->permitted = false;
			lua_pushvalue(L, 1);
			c->ref->direct_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			c->completed = true;
			return 0;
		}
		static int enter(lua_State* L) {
			auto* c = active;
			if (!c || c->ref->L != L)
				return luaL_error(L, "expired Lua callback registration");
			lua_settop(L, 0);
			luaL_checkstack(L, 12, "Lua callback registration stack overflow");
			// Neutralize this fresh setup closure too: newly created sentinel
			// userdata/metatable closures must not root the registering sandbox.
			lua_newtable(L);
			lua_replace(L, LUA_ENVIRONINDEX);
			using holder = _callback_userdata<_callback_lifetime>;
			// Use the same VM sentinel as the compatibility path.
			lua_pushlightuserdata(L, _callback_state_key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				// Allocate C++ ownership outside Lua's C error frames. On a cold
				// VM the caller supplies it and retries the protected setup.
				if (!c->lifetime) { c->needs_lifetime = true; return 0; }
				_push_callback_lifetime(L, c->lifetime);
			}
			auto* p = static_cast<holder*>(lua_touserdata(L, -1));
			c->ref->state = p->value ? (*p->value)->state : nullptr;
			lua_pop(L, 1);
			if (!c->ref->state || !c->ref->state->callable()) return 0;
			c->ref->state->drain(L);
			// Reserve the luaL_unref free-list slot before acquiring roots. Final
			// release only overwrites existing registry slots, even during OOM.
			lua_rawgeti(L, LUA_REGISTRYINDEX, 0);
			const bool missing_freelist = lua_isnil(L, -1);
			lua_pop(L, 1);
			if (missing_freelist) {
				lua_pushinteger(L, 0);
				lua_rawseti(L, LUA_REGISTRYINDEX, 0);
			}
			lua_pushthread(L);
			c->ref->thread_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			_callback_call<void>::push_cached(L, finish, finish_key());
			c->permitted = true;
			return 0;
		}
	};

	inline std::shared_ptr<_callback_reference> _own_direct_luafunction(lua_State* L, int index, const char* name) {
		_owned_callback_registration c(L, name);
		const int top = lua_gettop(L);
		int status = lua_cpcall(L, _owned_callback_registration::enter, nullptr);
		if (status == 0 && c.needs_lifetime) {
			c.lifetime = std::make_shared<_callback_lifetime>();
			c.needs_lifetime = false;
			status = lua_cpcall(L, _owned_callback_registration::enter, nullptr);
		}
		if (status != 0 || !c.permitted) {
			lua_settop(L, top);
			return nullptr;
		}
		// cpcall cannot see the caller's input slot. Its protected preflight has
		// already grown the physical stack beyond top+4; checkstack here only
		// updates the caller's C API limit and cannot allocate in Lua 5.1/LuaJIT.
		if (!lua_checkstack(L, 4)) return nullptr;
		lua_pushlightuserdata(L, _owned_callback_registration::finish_key());
		lua_rawget(L, LUA_REGISTRYINDEX);
		lua_pushvalue(L, index);
		status = lua_pcall(L, 1, 0, 0);
		c.permitted = false;
		lua_settop(L, top);
		return status == 0 && c.completed ? std::move(c.ref) : nullptr;
	}

	template<typename F>
	struct _owned_callback_call {
		_callback_reference* callback;
		F* invoke;
		lua_State* L;
		bool completed = false;
		_owned_callback_call* previous;
		inline static thread_local _owned_callback_call* active = nullptr;
		inline static char report_key, run_key;
		_owned_callback_call(_callback_reference* ref, F* function)
			: callback(ref), invoke(function), L(ref->L), previous(active) {
			active = this;
		}
		_owned_callback_call(const _owned_callback_call&) = delete;
		_owned_callback_call& operator=(const _owned_callback_call&) = delete;
		~_owned_callback_call() { active = previous; }
		static int report(lua_State* L) {
			auto* c = active;
			if (!c || c->L != L)
				return luaL_error(L, "expired Lua callback error handler");
			return _callback_report_error(L, c->callback->name.c_str());
		}
		static int run(lua_State* L) {
			auto* c = active;
			if (!c || c->L != L) {
				return luaL_error(L, "expired Lua callback invocation");
			}
			// Enter with zero Lua arguments. The context comes from TLS;
			// its previous link still restores legitimate nested calls and reporters.
			(*c->invoke)(L);
			c->completed = true;
			return 0;
		}
		static int enter(lua_State* L) {
			auto* context = active;
			if (!context || context->L != L) {
				return luaL_error(L, "expired Lua callback setup");
			}
			lua_settop(L, 0);
			luaL_checkstack(L, 8, "Lua callback setup stack overflow");
			context->callback->state->drain(L);
			_callback_call<F>::push_cached(L, report, &report_key);
			_callback_call<F>::push_cached(L, run, &run_key);
			const int status = lua_pcall(L, 0, 0, 1);
			if (status != 0) {
				context->completed = false;
				if (status != LUA_ERRRUN) _callback_log_error(L, context->callback->name.c_str());
			}
			return 0;
		}
		// Return false only when the original protected setup is still needed.
		// Cache misses and pending cleanup remain cold, protected operations.
		static bool try_call_fast(lua_State* L, int top) {
			auto* context = active;
			if (!context || context->L != L)
				return false;
			if (context->callback->state->pending.load(std::memory_order_acquire))
				return false;
			// A capacity limit is an ordinary failure. Allocation failure while
			// growing this stack is outside the Release recovery contract.
			if (!lua_checkstack(L, 8)) {
				std::fprintf(stderr, "[LUA ERROR] callback (%s): Lua callback setup stack overflow\n",
					context->callback->name.c_str());
				return true;
			}
			lua_pushlightuserdata(L, &report_key);
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) { lua_settop(L, top); return false; }
			lua_pushlightuserdata(L, &run_key);
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) { lua_settop(L, top); return false; }
			// There is no setup C frame: preserve the caller's entire prefix.
			const int status = lua_pcall(L, 0, 0, top + 1);
			if (status != 0) {
				context->completed = false;
				if (status != LUA_ERRRUN) _callback_log_error(L, context->callback->name.c_str());
			}
			return true;
		}
	};

	template<typename F>
	bool _call_owned_luafunction(const std::shared_ptr<_callback_reference>& ref, F&& invoke) {
		auto keep = ref;
		if (!keep->state->callable()) return false;
		auto* L = keep->L;
		const int top = lua_gettop(L);
		_owned_callback_call<F> context{ keep.get(), &invoke };
		bool handled = false;
		// Keep Debug setup protected, independently of whether hooks are installed.
		if constexpr (CC_DEBUG <= 0)
			handled = _owned_callback_call<F>::try_call_fast(L, top);
		if (!handled) {
			if (lua_cpcall(L, _owned_callback_call<F>::enter, nullptr) != 0) {
				context.completed = false;
				_callback_log_error(L, keep->name.c_str());
			}
		}
		lua_settop(L, top);
		return context.completed;
	}

	// Independent ownership: no handler/alias, and clearing one C++ copy does
	// not cancel others. The name is diagnostic only. Failure preserves *out.
	// All builds trust scripts, debug hooks, finalizers and reporters. Observing
	// bridge frames is supported; calling/replaying private bridge functions or
	// changing their frames/environments/registry entries is unsupported and is
	// not defended, and can repeat callbacks or corrupt registration state.
	// Trigger callbacks through public APIs; normal recursion works.
	template<typename R, typename... Args>
	bool luaval_to_owned_callback(lua_State* L, int index, std::function<R(Args...)>* out,
		const char* diagnostic_name = "") {
		static_assert((owned_callback_push<std::remove_cv_t<std::remove_reference_t<Args>>>::value && ...),
			"owned Lua callback: std::function arguments are not supported");
		static_assert(owned_callback_read<R>::value,
			"owned Lua callback: std::function results are not supported");
		index = _absolute_index(L, index);
		if (!out || !index) return false;
		if (lua_isnil(L, index)) { *out = nullptr; return true; }
		if (!lua_isfunction(L, index)) return false;
		try {
			auto ref = _own_direct_luafunction(L, index, diagnostic_name);
			if (!ref) return false;
			std::function<R(Args...)> result = [ref = std::move(ref)](Args... args) -> R {
				// The anchor inside _call_owned_luafunction survives self-replacement.
				auto* callback = ref.get();
				if constexpr (std::is_void_v<R>) {
					_call_owned_luafunction(ref, [&](lua_State* L) {
						lua_rawgeti(L, LUA_REGISTRYINDEX, callback->direct_ref);
						if (!lua_isfunction(L, -1)) return;
						luaL_checkstack(L, sizeof...(Args), "Lua callback argument stack overflow");
						_to_lua_function_helper<sizeof...(Args), Args...>::F(L, std::forward<Args>(args)...);
						lua_call(L, sizeof...(Args), 0);
					});
				} else {
					R ret{};
					const bool ok = _call_owned_luafunction(ref, [&](lua_State* L) {
						lua_rawgeti(L, LUA_REGISTRYINDEX, callback->direct_ref);
						if (!lua_isfunction(L, -1)) return;
						luaL_checkstack(L, sizeof...(Args), "Lua callback argument stack overflow");
						_to_lua_function_helper<sizeof...(Args), Args...>::F(L, std::forward<Args>(args)...);
						lua_call(L, sizeof...(Args), 1);
						if (!luaval_to_native(L, -1, &ret, callback->name.c_str()))
							luaL_error(L, "invalid return value in handler (%s)", callback->name.c_str());
					});
					return ok ? std::move(ret) : R{};
				}
			};
			*out = std::move(result);
			return true;
		} catch (const std::bad_alloc&) {
			return false;
		}
	}

	// All callback reads, including explicit luaval_to_native calls, use owned
	// references. std::function arguments/results are excluded, also when nested
	// inside supported containers; other registered converters remain available.
	template<typename R, typename... Targs>
	struct to_native<std::function<R(Targs...)>> {
		static bool F(lua_State* L, int lo, std::function<R(Targs...)>* outValue, const char* fName = "") {
			return luaval_to_owned_callback(L, lo, outValue, fName);
		}
	};

	////////////////////////////////////////////////////////////////////////////////

	// Automatic fields keep checked value conversion and share the owned callback
	// path with public luaval_to_native.
	template<typename T>
	bool luaval_to_binding_value(lua_State* L, int index, T* out, const char* name = "") {
		return luaval_to_native(L, index, out, name);
	}
	template<typename R, typename... Args>
	bool luaval_to_binding_value(lua_State* L, int index, std::function<R(Args...)>* out,
		const char* name = "") {
		return luaval_to_owned_callback(L, index, out, name);
	}

	// Binding reads are separate from to_native's public checked conversion
	// contract. Overload resolution always requests Checked=true.
	template<typename T, class Enable = void>
	struct binding_read {
		template<bool Checked>
		static bool F(lua_State* L, int lo, T* outValue) {
			if constexpr (Checked)
				return to_native<T>::F(L, lo, outValue);
			else if constexpr (std::is_same_v<T, bool>) {
				*outValue = lua_toboolean(L, lo) != 0;
				return true;
			} else if constexpr (std::is_floating_point_v<T>) {
				*outValue = static_cast<T>(lua_tonumber(L, lo));
				return true;
			} else if constexpr (std::is_integral_v<T>) {
				if (lua_type(L, lo) == LUA_TCDATA)
					return to_native<T>::F(L, lo, outValue);
				const auto value = lua_tonumber(L, lo);
				// The upper bound is exclusive: max() is rounded upwards for
				// int64/uint64 in a double and must never permit an overflowing cast.
				const auto upper = std::ldexp(lua_Number(1), std::numeric_limits<T>::digits);
				const auto lower = std::is_signed_v<T> ? -upper : lua_Number(0);
				if (value >= lower && value < upper) {
					*outValue = static_cast<T>(value);
					return true;
				}
				constexpr uint64_t mask = UINT64_MAX >> ((8 - sizeof(T)) * 8);
				const auto bits = _integer_bits_from_number(value) & mask;
				if constexpr (std::is_signed_v<T>)
					*outValue = static_cast<T>(bits > (mask >> 1)
						? -static_cast<int64_t>(mask ^ bits) - 1 : static_cast<int64_t>(bits));
				else
					*outValue = static_cast<T>(bits);
				return true;
			} else if constexpr (std::is_enum_v<T>) {
				std::underlying_type_t<T> value;
				const bool ok = binding_read<decltype(value)>::template F<false>(L, lo, &value);
				if (ok) *outValue = static_cast<T>(value);
				return ok;
			} else if constexpr (std::is_same_v<T, const char*>) {
				*outValue = lua_tolstring(L, lo, nullptr);
				return true;
			} else if constexpr (std::is_same_v<T, std::string>
#ifdef __cpp_lib_string_view
				|| std::is_same_v<T, std::string_view>
#endif
				) {
				size_t size;
				const auto* value = lua_tolstring(L, lo, &size);
				*outValue = T(value, size);
				return true;
			} else
				return to_native<T>::F(L, lo, outValue);
		}
	};

	template<typename R, typename... Args>
	struct binding_read<std::function<R(Args...)>> {
		template<bool Checked>
		static bool F(lua_State* L, int index, std::function<R(Args...)>* out) {
			return luaval_to_owned_callback(L, index, out);
		}
	};

	template<size_t Index, bool Checked, bool RequireSelf, typename Callable, typename Targ = void, typename... Targs>
	struct _invoke_helper {
		template<typename... Fargs>
		static bool F(lua_State* L, int argTop, int& argCur, int& results, Callable& callable, Fargs&&... args) {
			++argCur;
			using T = std::remove_cv_t<std::remove_reference_t<Targ>>;
			T arg{};
			if (!binding_read<T>::template F<Checked>(L, argTop + 1 - Index, &arg))
				return false;
			if constexpr (Checked && (RequireSelf || std::is_member_function_pointer_v<Callable>) && sizeof...(Fargs) == 0) {
				if constexpr (std::is_pointer_v<T>) {
					if (!arg) return false;
				}
			}
			static_assert(Index > 0);
			return _invoke_helper<Index - 1, Checked, RequireSelf, Callable, Targs...>::template F<Fargs..., Targ>(L, argTop, argCur, results, callable, std::forward<Fargs>(args)..., std::forward<Targ>(arg));
		}
	};

	template<bool Checked, bool RequireSelf, typename Callable>
	struct _invoke_helper<0, Checked, RequireSelf, Callable> {
		template<typename... Fargs>
		static bool F(lua_State* L, int argTop, int& argCur, int& results, Callable& callable, Fargs&&... args) {
			const int top = lua_gettop(L);
			if constexpr (std::is_same_v<std::invoke_result_t<Callable&, Fargs...>, void>) {
				std::invoke(callable, std::forward<Fargs>(args)...);
#if CC_LUA_BINDING_CHECKS
				if (lua_gettop(L) != top)
					luaL_error(L, "native invocation changed Lua stack (expected %d, got %d)", top, lua_gettop(L));
#endif
				results = 0;
			} else {
				decltype(auto) value = std::invoke(callable, std::forward<Fargs>(args)...);
#if CC_LUA_BINDING_CHECKS
				if (lua_gettop(L) != top)
					luaL_error(L, "native invocation changed Lua stack (expected %d, got %d)", top, lua_gettop(L));
#endif
				native_to_luaval(L, value);
				results = lua_gettop(L) - top;
#if CC_LUA_BINDING_CHECKS
				if (results < 0)
					luaL_error(L, "native result conversion removed Lua inputs");
#endif
			}
			return true;
		}
	};

	template<typename... Targs>
	struct _invoke_arguments {
		template<bool Checked, bool KeepInputs, bool Overload, bool RequireSelf, typename Callable>
		static bool F(lua_State* L, Callable& callable, int& argCur, int firstArg, int* outResults, int inputTop) {
			constexpr int nargs = sizeof...(Targs);
			const int top = lua_gettop(L);
			if (inputTop < 0) inputTop = top;
			if (inputTop < nargs) return false;
			argCur = RequireSelf ? -1 : firstArg;
			int argTop = inputTop;
			if constexpr (Overload) {
				// Isolate slot-replacing converters from subsequent candidates.
				luaL_checkstack(L, nargs, "overload argument stack overflow");
				for (int i = inputTop - nargs + 1; i <= inputTop; ++i) lua_pushvalue(L, i);
				argTop = lua_gettop(L);
			}
			int results = 0;
			const bool ok = _invoke_helper<nargs, Checked, RequireSelf, Callable, Targs...>::F(L, argTop, argCur, results, callable);
			if (!ok) {
				lua_settop(L, top);
				return false;
			}
			if (outResults) *outResults = results;
			if constexpr (!KeepInputs) {
				// Argument destructors have run before releasing input roots.
				const int prefix = top - nargs;
				const int firstResult = lua_gettop(L) - results + 1;
				for (int i = 0; i < results; ++i) {
					lua_pushvalue(L, firstResult + i);
					lua_replace(L, prefix + i + 1);
				}
				lua_settop(L, prefix + results);
			}
			return true;
		}
	};

	template<typename T> struct invoke {};

	template<typename R, typename... Targs>
	struct invoke<std::function<R(Targs...)>> {
		using callable_t = std::function<R(Targs...)>;
		template<bool Checked = bool(CC_LUA_BINDING_CHECKS), bool KeepInputs = false, bool Overload = false, bool RequireSelf = false, typename Callable>
		static bool F(lua_State* L, Callable&& callable, int& argCur, int* outResults = nullptr, int inputTop = -1) {
			if constexpr (std::is_same_v<std::decay_t<Callable>, callable_t>) {
				// A stored function may destroy its owner from inside a callback.
				// Keep its historical value semantics and an owning call-local copy.
				callable_t owned(std::forward<Callable>(callable));
				return _invoke_arguments<Targs...>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, owned, argCur, 0, outResults, inputTop);
			} else
				return _invoke_arguments<Targs...>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, callable, argCur, 0, outResults, inputTop);
		}
	};

	template<typename R, typename... Targs>
	struct invoke<R(*)(Targs...)> : invoke<std::function<R(Targs...)>> {
		using callable_t = R(*)(Targs...);
	};

	template<typename C, typename R, typename... Targs>
	struct invoke<R(C::*)(Targs...)> {
		using callable_t = R(C::*)(Targs...);
		template<bool Checked = bool(CC_LUA_BINDING_CHECKS), bool KeepInputs = false, bool Overload = false, bool RequireSelf = false, typename Callable>
		static bool F(lua_State* L, Callable&& callable, int& argCur, int* outResults = nullptr, int inputTop = -1) {
			return _invoke_arguments<C*, Targs...>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, callable, argCur, -1, outResults, inputTop);
		}
	};

	template<typename C, typename R, typename... Targs>
	struct invoke<R(C::*)(Targs...) const> {
		using callable_t = R(C::*)(Targs...) const;
		template<bool Checked = bool(CC_LUA_BINDING_CHECKS), bool KeepInputs = false, bool Overload = false, bool RequireSelf = false, typename Callable>
		static bool F(lua_State* L, Callable&& callable, int& argCur, int* outResults = nullptr, int inputTop = -1) {
			return _invoke_arguments<const C*, Targs...>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, callable, argCur, -1, outResults, inputTop);
		}
	};

	template <typename Function>
	struct function_traits : public function_traits<decltype(&Function::operator())> {};

	template <typename ClassType, typename ReturnType, typename... Args>
	struct function_traits<ReturnType(ClassType::*)(Args...) const> {
		typedef ReturnType(*pointer)(Args...);
		typedef std::function<ReturnType(Args...)> function;
	};

	template <typename ClassType, typename ReturnType, typename... Args>
	struct function_traits<ReturnType(ClassType::*)(Args...)>
		: function_traits<ReturnType(ClassType::*)(Args...) const> {};

	template<bool Checked, bool KeepInputs, bool Overload, bool RequireSelf = false, typename T>
	bool _invoke_native(lua_State* L, int& argCur, T&& callable, int* outResults = nullptr, int inputTop = -1) {
		using type = std::decay_t<T>;
		if constexpr (std::is_class_v<type>)
			return invoke<typename function_traits<type>::function>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, std::forward<T>(callable), argCur, outResults, inputTop);
		else
			return invoke<type>::template F<Checked, KeepInputs, Overload, RequireSelf>(L, std::forward<T>(callable), argCur, outResults, inputTop);
	}

	// Direct calls consume their trailing arguments, preserve the prefix, and
	// append exactly the converter's results. Native code sees all inputs until
	// result conversion and argument destruction have completed.
	template<typename T>
	bool invoke_native(lua_State* L, int& argCur, T callable) {
		return _invoke_native<bool(CC_LUA_BINDING_CHECKS), false, false>(L, argCur, std::move(callable));
	}

	// Expand a dynamic receiver once across same-arity overload attempts. The
	// extra root retains the original wrapper for void setters; ordinary userdata
	// never needs a copy. Negative values mean no wrapper or invalid wrapper.
	inline bool _prepare_binding_receiver(lua_State* L, int& original) {
		if (original != 0) return original != -2;
		if (!lua_istable(L, 1)) { original = -1; return true; }
		lua_pushvalue(L, 1);
		original = lua_gettop(L);
		if (push_table_instance(L, 1)) return true;
		lua_pop(L, 1);
		original = -2;
		return false;
	}

	// Bindings return topmost results; retaining inputs avoids shifting stack
	// slots and lets void setters return the original Lua self directly.
	template<bool Overload = false, bool RequireSelf = false, typename T>
	bool invoke_binding(lua_State* L, int& argCur, T callable, int& results, int inputTop = -1) {
		return _invoke_native<Overload || bool(CC_LUA_BINDING_CHECKS), true, Overload, RequireSelf>(L, argCur, std::move(callable), &results, inputTop);
	}

	template<typename R, typename... Targs>
	struct to_lua<std::function<R(Targs...)>> {
		using type = std::function<R(Targs...)>;
	private:
		struct userdata {
			type* value;
			alignas(type) unsigned char storage[sizeof(type)];
		};
		static void* metatable_key() {
			static char key;
			return &key;
		}
		static userdata* get(lua_State* L) {
			if (lua_type(L, 1) != LUA_TUSERDATA || lua_objlen(L, 1) != sizeof(userdata)
				|| !lua_getmetatable(L, 1))
				return nullptr;
			lua_pushlightuserdata(L, metatable_key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			const bool matches = lua_rawequal(L, -1, -2) != 0;
			lua_pop(L, 2);
			return matches ? static_cast<userdata*>(lua_touserdata(L, 1)) : nullptr;
		}
		static int collect(lua_State* L) {
			auto* p = get(L);
			if (p && p->value) {
				auto* value = p->value;
				p->value = nullptr; // invalidate before destruction, fix reentrant __gc
				value->~type();
			}
			return 0;
		}
		static int call(lua_State* L) {
			auto* p = get(L);
			if (!p)
				return luaL_error(L, "invalid std::function object");
			if (!p->value)
				return luaL_error(L, "expired std::function object");
			if (!*p->value)
				return 0;
			if (lua_gettop(L) < 1 + static_cast<int>(sizeof...(Targs)))
				return luaL_error(L, "not enough arguments for std::function");
			int cur = 0;
			const int prefix = lua_gettop(L) - static_cast<int>(sizeof...(Targs));
			if (!invoke_native(L, cur, *p->value))
				return luaL_error(L, "invalid parameter %d", cur);
			return lua_gettop(L) - prefix;
		}
	public:
		static void F(lua_State* L, const type& inValue) {
			if (!L) return;
			lua_pushlightuserdata(L, metatable_key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				lua_createtable(L, 0, 2);
				lua_pushcfunction(L, call);
				lua_setfield(L, -2, "__call");
				lua_pushcfunction(L, collect);
				lua_setfield(L, -2, "__gc");
				lua_pushlightuserdata(L, metatable_key());
				lua_pushvalue(L, -2);
				lua_rawset(L, LUA_REGISTRYINDEX);
			}
			auto* p = new (lua_newuserdata(L, sizeof(userdata))) userdata{};
			lua_insert(L, -2);
			lua_setmetatable(L, -2);
			// construct after all lua allocations so an exception here leaves an inert userdata
			p->value = new (p->storage) type(inValue);
		}
	};
}

////////////////////////////////////////////////////////////////////////////////

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
