#pragma once
#include "base.hpp"
#include "scalar.hpp"
#include "conversion.hpp"
#include "callback_from_lua.hpp"
#include <cmath>
#include <functional>
#include <limits>
#include <type_traits>
#include <utility>

namespace lua
{
	// Automatic fields always use checked conversion.
	template<typename T>
	bool luaval_to_binding_value(lua_State* L, int index, T* out, const char* name = "") {
		return luaval_to_native(L, index, out, name);
	}
	template<typename R, typename... Args>
	bool luaval_to_binding_value(lua_State* L, int index, std::function<R(Args...)>* out,
		const char* name = "") {
		return luaval_to_owned_callback(L, index, out, name);
	}

	// Public to_native stays checked; bindings may skip checks except during overload resolution.
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
				// Use an exclusive bound: double rounds int64/uint64 max() up, allowing overflow.
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
				// Keep a local owner: the callback may destroy or replace the stored function.
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

	// Replace trailing arguments with converted results, preserving the prefix.
	// Inputs stay rooted through result conversion and argument destruction.
	template<typename T>
	bool invoke_native(lua_State* L, int& argCur, T callable) {
		return _invoke_native<bool(CC_LUA_BINDING_CHECKS), false, false>(L, argCur, std::move(callable));
	}

	// Resolve a wrapper once across same-arity overloads; retain it for void setters.
	// original: 0 = unresolved, -1 = no wrapper, -2 = invalid, >0 = saved wrapper slot.
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

	// Keep inputs to avoid stack shifts and let void setters return the original Lua self.
	template<bool Overload = false, bool RequireSelf = false, typename T>
	bool invoke_binding(lua_State* L, int& argCur, T callable, int& results, int inputTop = -1) {
		return _invoke_native<Overload || bool(CC_LUA_BINDING_CHECKS), true, Overload, RequireSelf>(L, argCur, std::move(callable), &results, inputTop);
	}
}
