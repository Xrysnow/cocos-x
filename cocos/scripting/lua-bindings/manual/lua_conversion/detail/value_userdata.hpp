#pragma once
#include "base.hpp"
#include <type_traits>
#include <utility>

namespace lua
{
	// Only an explicit specialization opts a native class into userdata value semantics.
	template<typename T> struct value_type : std::false_type {};
	template<typename T> inline constexpr bool is_value_type_v = value_type<std::remove_cv_t<T>>::value;

	inline const void* _value_owned_key() { static const char key = 0; return &key; }
	inline const void* _value_const_key() { static const char key = 0; return &key; }
	inline const void* _value_owner_key() { static const char key = 0; return &key; }
	inline const void* _value_context_key() { static const char key = 0; return &key; }
	inline const void* _value_context_start_key() { static const char key = 0; return &key; }
	inline const void* _value_context_offset_key() { static const char key = 0; return &key; }

	inline void _value_raw_integer(lua_State* L, int table, const void* key, int value) {
		lua_pushlightuserdata(L, const_cast<void*>(key));
		lua_pushinteger(L, value);
		lua_rawset(L, table);
	}
	inline int _value_raw_integer(lua_State* L, int table, const void* key) {
		lua_pushlightuserdata(L, const_cast<void*>(key));
		lua_rawget(L, table);
		const int value = static_cast<int>(lua_tointeger(L, -1));
		lua_pop(L, 1);
		return value;
	}
	inline int _value_context(lua_State* L) {
		for (int index = lua_gettop(L); index > 0; --index) {
			if (!lua_istable(L, index)) continue;
			lua_pushlightuserdata(L, const_cast<void*>(_value_context_key()));
			lua_rawget(L, index);
			const bool context = lua_toboolean(L, -1) != 0;
			lua_pop(L, 1);
			if (context) return index;
		}
		return 0;
	}
	inline void _begin_value_arguments(lua_State* L, int inputTop, int argumentTop, int count) {
		lua_newtable(L);
		const int frame = lua_gettop(L);
		_value_raw_integer(L, frame, _value_context_key(), 1);
		_value_raw_integer(L, frame, _value_context_start_key(), argumentTop - count + 1);
		_value_raw_integer(L, frame, _value_context_offset_key(), argumentTop - inputTop);
	}
	inline void _record_value_root(lua_State* L, int sourceIndex, int resolvedIndex) {
		const int frame = _value_context(L);
		if (!frame) return;
		const int start = _value_raw_integer(L, frame, _value_context_start_key());
		const int offset = _value_raw_integer(L, frame, _value_context_offset_key());
		if (sourceIndex >= start && sourceIndex < frame) sourceIndex -= offset;
		lua_pushvalue(L, resolvedIndex);
		lua_rawseti(L, frame, sourceIndex);
	}
	inline void _push_value_owner(lua_State* L, int ownerIndex) {
		const int frame = _value_context(L);
		if (frame) {
			lua_rawgeti(L, frame, ownerIndex);
			if (!lua_isnil(L, -1)) return;
			lua_pop(L, 1);
		}
		lua_pushvalue(L, ownerIndex);
	}

	inline bool _value_flag(lua_State* L, int index, const void* key) {
		index = _absolute_index(L, index);
		if (!index || !lua_isuserdata(L, index)) return false;
		lua_getfenv(L, index);
		lua_pushlightuserdata(L, const_cast<void*>(key));
		lua_rawget(L, -2);
		const bool flag = lua_toboolean(L, -1) != 0;
		lua_pop(L, 2);
		return flag;
	}

	template<typename T>
	bool read_value_pointer(lua_State* L, int index, T** out, bool nullable = false) {
		static_assert(is_value_type_v<T>, "value pointer requires an explicitly registered value type");
		if (!L || !out || !(index = _absolute_index(L, index))) return false;
		const int sourceIndex = index;
		// Keep dynamically supplied instances rooted without replacing the Lua wrapper.
		if (lua_istable(L, index)) {
			lua_pushliteral(L, ".c_instance");
			lua_gettable(L, index);
			index = lua_gettop(L);
			if (lua_type(L, index) != LUA_TUSERDATA) return false;
		}
		if (lua_isnil(L, index)) {
			if (!nullable) return false;
			*out = nullptr;
			return true;
		}
		if (!isusertype(L, index, _getClassNameByType<std::remove_cv_t<T>>())) return false;
		if constexpr (!std::is_const_v<T>)
			if (_value_flag(L, index, _value_const_key())) return false;
		auto* value = static_cast<T*>(_tousertype(L, index));
		if (!value) return false;
		_record_value_root(L, sourceIndex, index);
		*out = value;
		return true;
	}

	template<typename T>
	void _push_value_pointer(lua_State* L, T* value, bool owned, int ownerIndex) {
		static_assert(is_value_type_v<T>, "value userdata requires an explicitly registered value type");
		if (!L) return;
		if (!value) { lua_pushnil(L); return; }
		ownerIndex = ownerIndex ? _absolute_index(L, ownerIndex) : 0;
		const auto* name = _getClassNameByType<std::remove_cv_t<T>>();
		lua_getfield(L, LUA_REGISTRYINDEX, name);
		if (!*name || !lua_istable(L, -1))
			luaL_error(L, "unregistered value userdata type");
		// A distinct borrow preserves const and ownership even when another userdata
		// already refers to this address. Keep the pointer-sized tolua representation.
		*static_cast<void**>(lua_newuserdata(L, sizeof(void*))) = const_cast<std::remove_cv_t<T>*>(value);
		lua_pushvalue(L, -2);
		lua_setmetatable(L, -2);
		lua_remove(L, -2);
		lua_newtable(L);
		lua_pushlightuserdata(L, const_cast<void*>(_value_owned_key()));
		lua_pushboolean(L, owned);
		lua_rawset(L, -3);
		lua_pushlightuserdata(L, const_cast<void*>(_value_const_key()));
		lua_pushboolean(L, std::is_const_v<T>);
		lua_rawset(L, -3);
		if (ownerIndex) {
			lua_pushlightuserdata(L, const_cast<void*>(_value_owner_key()));
			_push_value_owner(L, ownerIndex);
			lua_rawset(L, -3);
		}
		lua_setfenv(L, -2);
	}

	template<typename T>
	void push_value_owned(lua_State* L, T* value) {
		static_assert(!std::is_const_v<T>, "owned value must be mutable");
		_push_value_pointer(L, value, true, 0);
	}
	template<typename T>
	void push_value_borrowed(lua_State* L, T* value, int ownerIndex = 0) {
		_push_value_pointer(L, value, false, ownerIndex);
	}

	template<typename T>
	int value_collect(lua_State* L) {
		static_assert(is_value_type_v<T>, "value collector requires an explicitly registered type");
		if (!L || lua_type(L, 1) != LUA_TUSERDATA || lua_objlen(L, 1) != sizeof(void*)) return 0;
		if (!isusertype(L, 1, _getClassNameByType<std::remove_cv_t<T>>())) return 0;
		if (!_value_flag(L, 1, _value_owned_key())) return 0;
		auto** slot = static_cast<void**>(lua_touserdata(L, 1));
		auto* value = static_cast<std::remove_cv_t<T>*>(*slot);
		*slot = nullptr;
		delete value;
		return 0;
	}

	template<typename T>
	void register_value_metatable(lua_State* L, const char* name) {
		static_assert(is_value_type_v<T>, "value metatable requires an explicitly registered type");
		lua_getfield(L, LUA_REGISTRYINDEX, name);
		if (!lua_istable(L, -1)) luaL_error(L, "missing metatable for value type '%s'", name);
		// tolua's default collector keys ownership by native address. A borrow can
		// share that address, so value types collect by userdata ownership instead.
		lua_pushcfunction(L, value_collect<T>);
		lua_setfield(L, -2, "__gc");
		lua_pushcfunction(L, value_collect<T>);
		lua_setfield(L, -2, ".collector");
		lua_pop(L, 1);
	}

	template<typename T> struct owned_value { T* pointer; };
	template<typename T> owned_value<T> own_value(T* value) { return {value}; }
	template<typename T> struct borrowed_value { T* pointer; int owner; bool nullable; };
	template<typename T> borrowed_value<T> borrow_value(T* value, int owner = 0, bool nullable = true) {
		return {value, owner, nullable};
	}
	template<typename T> borrowed_value<T> borrow_value(T& value, int owner = 0, bool nullable = false) {
		return {&value, owner, nullable};
	}

	template<typename T, bool Nullable>
	struct value_pointer {
		T* pointer = nullptr;
		T* get() const { return pointer; }
		operator T*() const { return pointer; }
	};
	template<typename T> struct _value_pointer_argument : std::false_type {};
	template<typename T, bool Nullable> struct _value_pointer_argument<value_pointer<T, Nullable>> : std::true_type {};
	template<typename T> inline constexpr bool is_value_argument_v =
		is_value_type_v<std::remove_reference_t<T>> ||
		(std::is_pointer_v<std::remove_reference_t<T>> && is_value_type_v<std::remove_pointer_t<std::remove_reference_t<T>>>) ||
		_value_pointer_argument<std::remove_cv_t<std::remove_reference_t<T>>>::value;
	template<typename T, bool Nullable>
	struct to_native<value_pointer<T, Nullable>> {
		static bool F(lua_State* L, int index, value_pointer<T, Nullable>* out, const char* = "") {
			return out && read_value_pointer(L, index, &out->pointer, Nullable);
		}
	};
	template<typename T>
	struct to_native<T, std::enable_if_t<is_value_type_v<T>>> {
		static bool F(lua_State* L, int index, T* out, const char* = "") {
			const T* source = nullptr;
			if (!out || !read_value_pointer(L, index, &source)) return false;
			*out = *source;
			return true;
		}
	};
	template<typename T>
	struct to_native<T*, std::enable_if_t<is_value_type_v<T>>> {
		static bool F(lua_State* L, int index, T** out, const char* = "") {
			return read_value_pointer(L, index, out, true);
		}
	};
	template<typename T>
	struct to_lua<T, std::enable_if_t<is_value_type_v<T>>> {
		static void F(lua_State* L, const T& value) { push_value_owned(L, new T(value)); }
	};
	template<typename T>
	struct to_lua<T*, std::enable_if_t<is_value_type_v<T>>> {
		static void F(lua_State* L, T* value) { push_value_borrowed(L, value); }
	};
	template<typename T> struct to_lua<owned_value<T>> {
		static void F(lua_State* L, const owned_value<T>& value) { push_value_owned(L, value.pointer); }
	};
	template<typename T> struct to_lua<borrowed_value<T>> {
		static void F(lua_State* L, const borrowed_value<T>& value) {
			if (!value.pointer && !value.nullable) luaL_error(L, "native value borrow returned null");
			push_value_borrowed(L, value.pointer, value.owner);
		}
	};
}
