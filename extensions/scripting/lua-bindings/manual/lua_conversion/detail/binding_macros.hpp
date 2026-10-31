#pragma once
#include "conversion.hpp"
#include "invoke.hpp"
#include "cocos/object.hpp"

#ifndef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_)\
	constexpr auto LUA_OBJ_TYPE = CName_;\
	constexpr auto LUA_FNAME = FName_;\
	if (CC_LUA_BINDING_CHECKS && lua_isnil(lua_S, 1))\
		return luaL_error(lua_S, "invalid class object in '%s'", LUA_FNAME);\
	const int binding_arg_top = lua_gettop(lua_S);\
	const int argc = binding_arg_top - 1;\
	int binding_self = 0;\
	constexpr bool binding_member_self = true;\
	int arg_cur = -1;\
	bool ok = false;
#endif // !LUA_INVOKE_HEADER

#ifndef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_)\
	constexpr auto LUA_FNAME = FName_;\
	const int binding_arg_top = lua_gettop(lua_S);\
	const int argc = binding_arg_top - 1;\
	int binding_self = -1;\
	constexpr bool binding_member_self = false;\
	int arg_cur = -1;\
	bool ok = false;
#endif // !LUA_SINVOKE_HEADER

#ifndef LUA_GINVOKE_HEADER
#define LUA_GINVOKE_HEADER(CName_, FName_)\
	constexpr auto LUA_FNAME = FName_;\
	const int binding_arg_top = lua_gettop(lua_S);\
	const int argc = binding_arg_top;\
	int binding_self = -1;\
	constexpr bool binding_member_self = false;\
	int arg_cur = -1;\
	bool ok = false;
#endif // !LUA_GINVOKE_HEADER

#ifndef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		ok = lua::invoke_binding<false, binding_member_self>(lua_S, arg_cur, (Fn_), native_results);\
		if (ok) {\
			lua_settop(lua_S, 1);\
			return 1;\
		}\
	}
#endif // !LUA_TRY_INVOKE

#ifndef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		ok = lua::invoke_binding<false, binding_member_self>(lua_S, arg_cur, (Fn_), native_results);\
		if (ok) return native_results;\
	}
#endif // !LUA_TRY_INVOKE_R

#ifndef LUA_TRY_CTOR
#define LUA_TRY_CTOR(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		ok = lua::invoke_binding<false, binding_member_self>(lua_S, arg_cur, (Fn_), native_results);\
		if (ok) {\
			tolua_register_gc(lua_S, lua_gettop(lua_S));\
			return native_results;\
		}\
	}
#endif // !LUA_TRY_CTOR

#ifndef LUA_TRY_INVOKE_OVERLOAD
#define LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		if (!lua::_prepare_binding_receiver(lua_S, binding_self)) { arg_cur = 0; }\
		else ok = lua::invoke_binding<true, binding_member_self>(lua_S, arg_cur, (Fn_), native_results, binding_arg_top);\
		if (ok) {\
			if (binding_self > 0) { lua_pushvalue(lua_S, binding_self); lua_replace(lua_S, 1); }\
			lua_settop(lua_S, 1); return 1;\
		}\
	}
#endif // !LUA_TRY_INVOKE_OVERLOAD

#ifndef LUA_TRY_INVOKE_R_OVERLOAD
#define LUA_TRY_INVOKE_R_OVERLOAD(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		if (!lua::_prepare_binding_receiver(lua_S, binding_self)) { arg_cur = 0; }\
		else ok = lua::invoke_binding<true, binding_member_self>(lua_S, arg_cur, (Fn_), native_results, binding_arg_top);\
		if (ok) return native_results;\
	}
#endif // !LUA_TRY_INVOKE_R_OVERLOAD

#ifndef LUA_TRY_CTOR_OVERLOAD
#define LUA_TRY_CTOR_OVERLOAD(ARGC_, Fn_)\
	if (argc == (ARGC_) && !ok) {\
		int native_results = 0;\
		if (!lua::_prepare_binding_receiver(lua_S, binding_self)) { arg_cur = 0; }\
		else ok = lua::invoke_binding<true, binding_member_self>(lua_S, arg_cur, (Fn_), native_results, binding_arg_top);\
		if (ok) { tolua_register_gc(lua_S, lua_gettop(lua_S)); return native_results; }\
	}
#endif // !LUA_TRY_CTOR_OVERLOAD

#ifndef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_)\
	if (arg_cur == -1)\
		return luaL_error(lua_S, "wrong number of arguments in '%s': %d, expects %s", LUA_FNAME, argc, Expected_);\
	else if (arg_cur == 0)\
		return luaL_error(lua_S, "invalid class object in '%s'", LUA_FNAME);\
	return luaL_error(lua_S, "invalid argument #%d in '%s'", arg_cur, LUA_FNAME);
#endif // !LUA_INVOKE_FOOTER

#ifndef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_)\
	if (arg_cur == -1)\
		return luaL_error(lua_S, "wrong number of arguments in '%s': %d, expects %s", LUA_FNAME, argc, Expected_);\
	return luaL_error(lua_S, "invalid argument #%d in '%s'", arg_cur, LUA_FNAME);
#endif // !LUA_SINVOKE_FOOTER

#ifndef LUA_GINVOKE_FOOTER
#define LUA_GINVOKE_FOOTER(Expected_) LUA_SINVOKE_FOOTER(Expected_)
#endif // !LUA_GINVOKE_FOOTER

#ifndef LUA_ENTRY
#define LUA_ENTRY(S_) tolua_module(lua_S, (S_), 0); tolua_beginmodule(lua_S, (S_));
#endif // !LUA_ENTRY

#ifndef LUA_ENTRY_END
#define LUA_ENTRY_END(N_) lua_pop(lua_S, (N_));
#endif // !LUA_ENTRY_END

#ifndef LUA_CLS_DEF
#define LUA_CLS_DEF(T_, TType_, TName_, Ctor_, Dtor_)\
	const char* typeName = (TName_);\
	const char* castName = (TType_);\
	using current_type = T_;\
	tolua_usertype(lua_S, (TName_));\
	tolua_cclass(lua_S, (TType_), (TName_), "", (Dtor_));\
	tolua_beginmodule(lua_S, (TType_));
#endif // !LUA_CLS_DEF

#ifndef LUA_CLS_DEF_BASE
#define LUA_CLS_DEF_BASE(T_, TType_, TName_, BT_, BName_, Ctor_, Dtor_)\
	const char* typeName = (TName_);\
	const char* castName = (TType_);\
	using current_type = T_;\
	tolua_usertype(lua_S, (TName_));\
	tolua_cclass(lua_S, (TType_), (TName_), (BName_), (Dtor_));\
	tolua_beginmodule(lua_S, (TType_));
#endif // !LUA_CLS_DEF_BASE

#ifndef LUA_METHOD
#define LUA_METHOD(Name_, Fn_)\
	tolua_function(lua_S, (Name_), Fn_);
#endif // !LUA_METHOD

#ifndef LUA_CLS_END
#define LUA_CLS_END()\
	tolua_endmodule(lua_S);\
	lua::registerLuaType<current_type>(typeName, castName);
#endif // !LUA_CLS_END

#ifndef LUA_TO_COBJ
#define LUA_TO_COBJ(T_, IDX_)\
	(T_)tolua_tousertype(lua_S, (IDX_), nullptr);
#endif // !LUA_TO_COBJ

#ifndef LUA_PUSH_NATIVE
#define LUA_PUSH_NATIVE(V_)\
	lua::native_to_luaval(lua_S, V_);
#endif // !LUA_PUSH_NATIVE

#ifndef LUA_NATIVE_SETTER
#define LUA_NATIVE_SETTER(V_, IDX_)\
	if (!lua::luaval_to_binding_value(lua_S, (IDX_), &(V_), LUA_FNAME))\
		return luaL_error(lua_S, "invalid value for '%s'", LUA_FNAME);
#endif // !LUA_NATIVE_SETTER

#ifndef LUA_CUR_FNAME
#define LUA_CUR_FNAME(FName_)\
	constexpr auto LUA_FNAME = FName_;
#endif // !LUA_CUR_FNAME

#ifndef LUA_FIELD
#define LUA_FIELD(Name_, Getter_, Setter_)\
	tolua_variable(lua_S, (Name_), (Getter_), (Setter_));
#endif // !LUA_FIELD

#ifndef LUA_SFIELD
#define LUA_SFIELD(Name_, Getter_, Setter_)\
	tolua_variable(lua_S, (Name_), (Getter_), (Setter_));
#endif // !LUA_SFIELD

#ifndef LUA_CONSTANT
#define LUA_CONSTANT(Name_, V_)\
	tolua_constant(lua_S, (Name_), (lua_Number)(V_));
#endif // !LUA_CONSTANT

#ifndef LUA_ENUM_DEF
#define LUA_ENUM_DEF(Name_)\
	tolua_module(lua_S, (Name_), 0);\
	tolua_beginmodule(lua_S, (Name_));
#endif // !LUA_ENUM_DEF

#ifndef LUA_ENUM_ENTRY
#define LUA_ENUM_ENTRY(Name_, V_)\
	tolua_constant(lua_S, (Name_), (lua_Number)(V_));
#endif // !LUA_ENUM_ENTRY

#ifndef LUA_ENUM_END
#define LUA_ENUM_END()\
	tolua_endmodule(lua_S);
#endif // !LUA_ENUM_END
