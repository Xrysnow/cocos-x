#pragma once
#include "../base.hpp"
#include "../invoke.hpp"
#include "cocos2d.h"
#include <string>
#include <type_traits>
#include <typeinfo>
#include <stdexcept>

namespace lua
{
	inline void ref_type_to_luaval(lua_State* L, cc::Ref* ref, const char* typeID)
    {
        if (!cc::isRefScriptContext(L))
            throw std::logic_error("Ref conversion requires the active Lua context and its host thread");
        if (ref)
        {
            const char* typeName = typeID ? typeID : typeid(*ref).name();
			using key_type = decltype(g_luaType)::key_type;
			using type = std::conditional_t<std::is_integral_v<key_type>, key_type, const char*>;
            const auto key = reinterpret_cast<type>(typeName);
            const auto iter = g_luaType.find(key);
            std::string luatype = "cc.Ref";
            if (g_luaType.end() != iter)
				luatype = iter->second;
            toluafix_pushusertype_ccobject(
                L, (int)ref->getScriptObjectID(), &ref->getScriptIdentity().luaID, (void*)ref, luatype.c_str());
        }
        else
        {
            lua_pushnil(L);
        }
    }

	template<typename T>
	struct to_native<T*, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		using binding_pointer = void;
		static bool F(lua_State* L, int lo, T** outValue, const char* fName = "") {
			if (!outValue || !cc::isRefScriptContext(L))
				return false;
			LUA_CHECK_TO_NATIVE;
			if (lo < 0 && lo > LUA_REGISTRYINDEX) {
				lo = top + lo + 1;
				if (lo <= 0) return false;
			}
			if (lo == 0) return false;
			if(lua_isnil(L, lo)) {
				*outValue = nullptr;
				return true;
			}
			const auto* className = _getClassNameByType<T>();
			if (!*className || !isusertype(L, lo, className))
				return false;
			// Ref userdata stores the canonical base address. Recover the complete
			// T address, including non-first or virtual public Ref bases.
			const auto p = dynamic_cast<T*>(static_cast<cc::Ref*>(*static_cast<void**>(lua_touserdata(L, lo))));
			if (!p)
				return false;
			*outValue = p;
			return true;
		}
	};

	template<typename T>
	struct to_lua<T*, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		static void F(lua_State* L, T* inValue) {
			if (!L) return;
			ref_type_to_luaval(L, const_cast<cc::RefCounted*>(static_cast<const cc::RefCounted*>(inValue)), typeid(T).name());
		}
	};

	template<typename T>
	struct to_native<T*, std::enable_if_t<!std::is_base_of_v<cc::RefCounted, T> && !is_value_type_v<T>>> {
		using binding_pointer = void;
		static bool F(lua_State* L, int lo, T** outValue, const char* fName = "") {
			if (!L || !outValue)
				return false;
			LUA_CHECK_TO_NATIVE;
			if (lo < 0 && lo > LUA_REGISTRYINDEX) {
				lo = top + lo + 1;
				if (lo <= 0) return false;
			}
			if (lo == 0) return false;
			if(lua_isnil(L, lo)) {
				*outValue = nullptr;
				return true;
			}
			const auto* className = _getClassNameByType<T>();
			if (!*className || !isusertype(L, lo, className))
				return false;
			auto p = static_cast<T*>(*static_cast<void**>(lua_touserdata(L, lo)));
			if (!p)
				return false;
			*outValue = p;
			return true;
		}
	};

	template<typename T>
	struct to_lua<T*, std::enable_if_t<!std::is_base_of_v<cc::RefCounted, T> && !is_value_type_v<T>>> {
		static void F(lua_State* L, T* inValue) {
			if (!L) return;
			if(!inValue) { lua_pushnil(L); return; }
			const auto className = getClassNameByType<T>();
			if(className.empty()) { lua_pushnil(L); return; }
			lua_getfield(L, LUA_REGISTRYINDEX, className.c_str());
			if (lua_isnil(L, -1)) // leave nil on stack
				return;
			tolua_pushusertype(L, (void*)inValue, className.c_str());
			lua_remove(L, -2);
		}
	};

	// Preserve wrappers for setter returns; root __index-created instances
	// through native execution, result conversion and argument destruction.
	template<typename T>
	struct binding_read<T*, std::void_t<typename to_native<T*>::binding_pointer>> {
		template<bool Checked>
		static bool F(lua_State* L, int lo, T** outValue) {
			if constexpr (std::is_convertible_v<T*, const cc::RefCounted*>)
				if (!outValue || !cc::isRefScriptContext(L)) return false;
			if (lua_istable(L, lo)) {
				lua_pushliteral(L, ".c_instance");
				lua_gettable(L, lo);
				lo = lua_gettop(L);
			}
			// Ref userdata must retain its registration/canonical-address checks
			// even when optional argument validation is disabled.
			if constexpr (Checked || std::is_convertible_v<T*, const cc::RefCounted*>)
				return to_native<T*>::F(L, lo, outValue);
			else {
				if (lua_isnil(L, lo)) *outValue = nullptr;
				else *outValue = static_cast<T*>(*static_cast<void**>(lua_touserdata(L, lo)));
				return true;
			}
		}
	};

	template<typename T>
	struct binding_argument<T&, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		T* value = nullptr;
		template<bool Checked> bool read(lua_State* L, int index) {
			return binding_read<T*>::template F<Checked>(L, index, &value) && value;
		}
		T& get() const { return *value; }
	};

	// Transparent RefPtr ownership and conversion contract: see ../../README.md (RefPtr conversion).
	template<typename T>
	struct to_native<cc::IntrusivePtr<T>, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		static bool F(lua_State* L, int lo, cc::IntrusivePtr<T>* outValue, const char* fName = "") {
			if (!L || !outValue) return false;
			T* value = nullptr;
			if (!to_native<T*>::F(L, lo, &value, fName)) return false;
			*outValue = value;
			return true;
		}
	};

	template<typename T>
	struct to_lua<cc::IntrusivePtr<T>, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		static void F(lua_State* L, cc::IntrusivePtr<T>&& inValue) {
			if (!L) return;
			if (!cc::isRefScriptContext(L))
				throw std::logic_error("Ref conversion requires the active Lua context and its host thread");
			// Owned factory results transfer their share before Lua can raise an
			// allocation error. L0 userdata borrows it until the pool is cleared.
			auto* value = cc::transferToAutoreleasePool(std::move(inValue));
			to_lua<T*>::F(L, value);
		}
		static void F(lua_State* L, const cc::IntrusivePtr<T>& inValue) {
			if (!L) return;
			if (!cc::isRefScriptContext(L))
				throw std::logic_error("Ref conversion requires the active Lua context and its host thread");
			auto* value = inValue.get();
			if (value) {
				auto* ref = const_cast<cc::Ref*>(static_cast<const cc::Ref*>(value));
				// Queue first: allocation failure must not strand an extra retain.
				ref->autorelease();
				ref->retain();
			}
			to_lua<T*>::F(L, value);
		}
	};

	template<typename T>
	struct binding_read<cc::IntrusivePtr<T>, std::enable_if_t<std::is_convertible_v<T*, const cc::RefCounted*>>> {
		template<bool Checked>
		static bool F(lua_State* L, int lo, cc::IntrusivePtr<T>* outValue) {
			if (!outValue || !cc::isRefScriptContext(L)) return false;
			LUA_CHECK_TO_NATIVE;
			const bool wrapper = lua_istable(L, lo);
			T* value = nullptr;
			// Keep a resolved .c_instance on the invocation stack, without replacing
			// the wrapper. Retaining arbitrary userdata is unsafe even with checks off.
			if (!binding_read<T*>::template F<true>(L, lo, &value) || (wrapper && !value))
				return false;
			*outValue = value;
			return true;
		}
	};

	template<typename T> struct is_ref_ptr : std::false_type {};
	template<typename T> struct is_ref_ptr<cc::IntrusivePtr<T>> : std::bool_constant<std::is_convertible_v<T*, const cc::RefCounted*>> {};

	template<typename Targ>
	struct binding_argument<Targ, std::enable_if_t<is_ref_ptr<std::remove_cv_t<std::remove_reference_t<Targ>>>::value>> {
		static_assert(!std::is_lvalue_reference_v<Targ> || std::is_const_v<std::remove_reference_t<Targ>>,
			"mutable RefPtr reference parameters require an explicit adapter; Lua has no ownership slot to update");
		static_assert(!std::is_rvalue_reference_v<Targ>,
			"RefPtr rvalue reference parameters require an explicit adapter; use a by-value parameter");
		using T = std::remove_cv_t<std::remove_reference_t<Targ>>;
		T value{};
		template<bool Checked> bool read(lua_State* L, int index) {
			return binding_read<T>::template F<Checked>(L, index, &value);
		}
		decltype(auto) get() { return std::forward<Targ>(value); }
	};
}
