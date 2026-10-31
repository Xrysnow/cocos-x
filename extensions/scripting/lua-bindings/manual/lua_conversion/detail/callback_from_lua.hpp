#pragma once
#include "conversion.hpp"
#include "callback_state.hpp"
#include <array>
#include <functional>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace lua
{
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

	// Payloads exclude std::function, including in supported containers.
	// Converters run in an empty environment and must handle Lua-error cleanup
	// and borrowed lifetimes.
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

	template<typename F>
	struct _owned_callback_call : _owned_callback_call_base {
		F* invoke;
		_owned_callback_call* previous;
		inline static thread_local _owned_callback_call* active = nullptr;
		inline static char report_key, run_key;
		_owned_callback_call(_callback_reference* ref, F* function)
			: _owned_callback_call_base(ref), invoke(function), previous(active) {
			active = this;
		}
		_owned_callback_call(const _owned_callback_call&) = delete;
		_owned_callback_call& operator=(const _owned_callback_call&) = delete;
		~_owned_callback_call() { active = previous; }
		static int report(lua_State* L) {
			return _owned_callback_call_base::report(L, active);
		}
		static int run(lua_State* L) {
			auto* c = active;
			if (!c || c->L != L) {
				return luaL_error(L, "expired Lua callback invocation");
			}
			// No Lua arguments: TLS supplies the context and restores nested calls/reporters.
			(*c->invoke)(L);
			c->completed = true;
			return 0;
		}
		static int enter(lua_State* L) {
			return _owned_callback_call_base::enter(L, active, report, &report_key, run, &run_key);
		}
		static bool try_call_fast(lua_State* L, int top) {
			return _owned_callback_call_base::try_call_fast(L, top, active, &report_key, &run_key);
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

	// No handler/alias registration; clearing one C++ copy leaves others valid.
	// Failure preserves *out.
	// All builds trust scripts, hooks, finalizers and reporters. Bridge frames may
	// be observed, but private calls/replay or frame/environment/registry mutation
	// are unguarded and may repeat callbacks or corrupt registration. Use public
	// APIs for invocation; recursion is supported.
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

	template<typename R, typename... Targs>
	struct to_native<std::function<R(Targs...)>> {
		static bool F(lua_State* L, int lo, std::function<R(Targs...)>* outValue, const char* fName = "") {
			return luaval_to_owned_callback(L, lo, outValue, fName);
		}
	};
}
