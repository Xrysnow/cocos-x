#pragma once
#include "base.hpp"
#include <atomic>
#include <cstdio>
#include <memory>
#include <mutex>
#include <new>
#include <string>
#include <thread>
#include <utility>

namespace lua
{
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
				// Allocation may publish a metatable through a reentrant finalizer.
				// Reuse it so existing userdata retain their identity.
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
		// The caller's name may be temporary.
		std::string name;
		int direct_ref = LUA_NOREF;
		int thread_ref = LUA_NOREF;
		_callback_reference* next = nullptr;
		void unref(lua_State* current) {
			luaL_unref(current, LUA_REGISTRYINDEX, direct_ref);
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
					// Queue without allocation or Lua access; drain on the next owner-thread
					// registration/call, or discard on close.
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
	// Coroutines share the registry and therefore the same lifetime sentinel.
	inline void* _callback_state_key() { static char key; return &key; }
	// Leaves the shared sentinel on the stack, reusing any published by reentrant allocation.
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
		// Protect LuaStack's reporting hook; it need not return an error string.
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

	inline void _push_cached_callback(lua_State* L, lua_CFunction function, void* key) {
		// Shared per VM/key, without owning callbacks or C++ frames.
		// Initial allocation must run in a protected frame.
		lua_pushlightuserdata(L, key);
		lua_rawget(L, LUA_REGISTRYINDEX);
		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			lua_pushcfunction(L, function);
			// An empty environment avoids retaining the first caller's sandbox/coroutine.
			// Bridge code accesses globals and the registry explicitly.
			lua_newtable(L);
			lua_setfenv(L, -2);
			lua_pushlightuserdata(L, key);
			lua_pushvalue(L, -2);
			lua_rawset(L, LUA_REGISTRYINDEX);
		}
	}

	// Keep C++ ownership outside protected Lua frames; record each acquired root
	// immediately so partial registration can be cleaned up.
	struct _owned_callback_registration {
		std::shared_ptr<_callback_reference> ref;
		std::shared_ptr<_callback_lifetime> lifetime;
		bool completed = false;
		bool permitted = false;
		bool needs_lifetime = false;
		_owned_callback_registration* previous;
		inline static thread_local _owned_callback_registration* active = nullptr;
		_owned_callback_registration(lua_State* L, const char* name)
			: ref(new _callback_reference{ nullptr, L, name ? name : "" }, _callback_reference::release),
			previous(active) {
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
			// Sentinel userdata and closures must not retain the registering sandbox.
			lua_newtable(L);
			lua_replace(L, LUA_ENVIRONINDEX);
			using holder = _callback_userdata<_callback_lifetime>;
			lua_pushlightuserdata(L, _callback_state_key());
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				// The caller allocates C++ ownership outside Lua error frames, then retries.
				if (!c->lifetime) { c->needs_lifetime = true; return 0; }
				_push_callback_lifetime(L, c->lifetime);
			}
			auto* p = static_cast<holder*>(lua_touserdata(L, -1));
			c->ref->state = p->value ? (*p->value)->state : nullptr;
			lua_pop(L, 1);
			if (!c->ref->state || !c->ref->state->callable()) return 0;
			c->ref->state->drain(L);
			// Reserve luaL_unref's free-list slot so final release needs no allocation, even on OOM.
			lua_rawgeti(L, LUA_REGISTRYINDEX, 0);
			const bool missing_freelist = lua_isnil(L, -1);
			lua_pop(L, 1);
			if (missing_freelist) {
				lua_pushinteger(L, 0);
				lua_rawseti(L, LUA_REGISTRYINDEX, 0);
			}
			lua_pushthread(L);
			c->ref->thread_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			_push_cached_callback(L, finish, finish_key());
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

	// Share non-template dispatch code; TLS activation and cache keys remain per signature.
	struct _owned_callback_call_base {
		_callback_reference* callback;
		lua_State* L;
		bool completed = false;
		explicit _owned_callback_call_base(_callback_reference* ref)
			: callback(ref), L(ref->L) {}
		static int report(lua_State* L, _owned_callback_call_base* context) {
			if (!context || context->L != L)
				return luaL_error(L, "expired Lua callback error handler");
			return _callback_report_error(L, context->callback->name.c_str());
		}
		static int enter(lua_State* L, _owned_callback_call_base* context,
			lua_CFunction reporter, void* report_key, lua_CFunction runner, void* run_key) {
			if (!context || context->L != L) {
				return luaL_error(L, "expired Lua callback setup");
			}
			lua_settop(L, 0);
			luaL_checkstack(L, 8, "Lua callback setup stack overflow");
			context->callback->state->drain(L);
			_push_cached_callback(L, reporter, report_key);
			_push_cached_callback(L, runner, run_key);
			const int status = lua_pcall(L, 0, 0, 1);
			if (status != 0) {
				context->completed = false;
				if (status != LUA_ERRRUN) _callback_log_error(L, context->callback->name.c_str());
			}
			return 0;
		}
		// false requests protected setup for cache misses or pending cleanup;
		// true means handled, not necessarily successful.
		static bool try_call_fast(lua_State* L, int top, _owned_callback_call_base* context,
			void* report_key, void* run_key) {
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
			lua_pushlightuserdata(L, report_key);
			lua_rawget(L, LUA_REGISTRYINDEX);
			if (lua_isnil(L, -1)) { lua_settop(L, top); return false; }
			lua_pushlightuserdata(L, run_key);
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
}
