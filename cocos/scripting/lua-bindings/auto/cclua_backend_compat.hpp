#pragma once
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include <cstring>
#include <cstdio>


// Preserve this module's legacy checked conversions independently of Release's
// global binding setting. Numeric strings and nil booleans remain accepted;
namespace core_backend_binding
{
template<typename Arg>
bool prepare_value(lua_State* L, int index, const char* name)
{
	using T = std::remove_cv_t<std::remove_reference_t<Arg>>;
	if constexpr (std::is_enum_v<T> || std::is_same_v<T, int>) {
		int value;
		if (!luaval_to_int32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_same_v<T, unsigned int>) {
		unsigned int value;
		if (!luaval_to_uint32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_floating_point_v<T>) {
		double value;
		if (!luaval_to_number(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	
	}
	return true;
}

template<typename... Args, size_t... Index>
bool prepare_arguments(lua_State* L, const char* name, std::index_sequence<Index...>)
{
	const int first = lua_gettop(L) - int(sizeof...(Args)) + 1;
	return (prepare_value<Args>(L, first + int(Index), name) && ...);
}

template<typename T> struct prepare_signature;
template<typename R, typename... Args>
struct prepare_signature<R(*)(Args...)> {
	static bool run(lua_State* L, const char* name) {
		return prepare_arguments<Args...>(L, name, std::index_sequence_for<Args...>{});
	}
};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...)> : prepare_signature<R(*)(Args...)> {};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...) const> : prepare_signature<R(*)(Args...)> {};

template<typename F>
bool prepare(lua_State* L, const char* name, const F&)
{
	using T = std::decay_t<F>;
	if constexpr (std::is_class_v<T>)
		return prepare_signature<typename lua::function_traits<T>::pointer>::run(L, name);
	else
		return prepare_signature<T>::run(L, name);
}


const char* parent_name(const char* type);
void check_receiver(lua_State* L, const char* type, const char* name, bool member);
int fail(lua_State* L, const char* name, int argc, int attempted);
}
int register_all_cc_backend_retained(lua_State* L);
#undef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	core_backend_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, true); \
	const auto* core_self = tolua_tousertype(lua_S, 1, nullptr); \
	(void)core_self; \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = true; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	core_backend_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, false); \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = false; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto core_fn = (Fn_); \
		arg_cur = 0; \
		if (core_backend_binding::prepare(lua_S, LUA_FNAME, core_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, core_fn, &native_results); \
			if (ok) { lua_settop(lua_S, 1); return 1; } \
		} \
	}

#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto core_fn = (Fn_); \
		arg_cur = 0; \
		if (core_backend_binding::prepare(lua_S, LUA_FNAME, core_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, core_fn, &native_results); \
			if (ok) { return native_results; } \
		} \
	}

#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    return core_backend_binding::fail(lua_S, LUA_FNAME, argc, arg_cur);
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)

#undef LUA_TRY_INVOKE_OVERLOAD
#define LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE(ARGC_, Fn_)
#undef LUA_TRY_INVOKE_R_OVERLOAD
#define LUA_TRY_INVOKE_R_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE_R(ARGC_, Fn_)

// Core is the first tolua module installed by LuaStack. Its former aggregate
// initialized tolua before registering Ref; preserve that standalone contract.
// tolua_open is state-local and idempotent, including fresh external states.
#undef LUA_ENTRY
#define LUA_ENTRY(S_) tolua_open(lua_S); tolua_module(lua_S,(S_),0); tolua_beginmodule(lua_S,(S_));

// Preserve the exact legacy single Lua parent, including intentionally empty
// roots (Director/FileUtils/etc.) and inherited native classes outside Core.
#undef LUA_CLS_DEF
#define LUA_CLS_DEF(T_, TType_, TName_, Ctor_, Dtor_) \
    const char* typeName=(TName_); \
    const char* castName=(TType_); \
    using current_type=T_; \
    tolua_usertype(lua_S,(TName_)); \
    tolua_cclass(lua_S,(TType_),(TName_),core_backend_binding::parent_name(TName_),nullptr); \
    tolua_beginmodule(lua_S,(TType_));
#undef LUA_CLS_DEF_BASE
#define LUA_CLS_DEF_BASE(T_, TType_, TName_, BT_, BName_, Ctor_, Dtor_) \
    LUA_CLS_DEF(T_, TType_, TName_, Ctor_, Dtor_)
