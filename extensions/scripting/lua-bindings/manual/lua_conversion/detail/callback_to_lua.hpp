#pragma once
#include "invoke.hpp"
#include <functional>
#include <new>

namespace lua
{
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
				p->value = nullptr; // Prevent double destruction on reentrant __gc.
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
			// Construct after Lua allocations; a throwing constructor leaves inert userdata.
			p->value = new (p->storage) type(inValue);
		}
	};
}
