# Lua conversion

Include `lua_conversion.hpp` for cocos conversions, or
`lua_conversion_tolua.hpp` for the common tolua conversion layer. This document
collects conversion contracts and lifetime notes; headers keep local implementation
invariants next to the code they constrain.

## Arguments and invocation

The public `to_native` conversion stays checked. Binding invocation may skip
checks according to `CC_LUA_BINDING_CHECKS`, except during overload resolution;
automatic fields always use checked conversion.

Unregistered value types use temporary conversion storage. Classes explicitly
registered through `value_type<T>` instead refer to the original, rooted userdata:
a by-value native signature makes the C++ copy, while a reference signature keeps
the original object.

Invocation keeps inputs and dynamically resolved `.c_instance` objects rooted
through native execution, result conversion and argument destruction. Resolving
an instance does not replace the original Lua wrapper in the binding path, so
void setters can return the original Lua self. Overload attempts isolate input
slots that converters may replace. Explicit borrowed returns use the resolved
value-owner snapshots held on the invocation stack.

`invoke_native` replaces trailing arguments with converted results and preserves
the stack prefix. `invoke_binding` keeps inputs for the binding macros to handle
returns, including setters that return self.

Implementation: [invoke.hpp](detail/invoke.hpp) and
[object.hpp](detail/cocos/object.hpp).

## Value userdata ownership

Only an explicit `value_type<T>` specialization opts a native class into userdata
value semantics. Borrowed values get distinct userdata even when another
userdata already refers to the same native address, preserving each borrow's
constness and ownership. The userdata keeps tolua's pointer-sized representation.

Tolua's default collector keys ownership by native address. Since a borrowed
value can share an owned value's address, value types instead collect according
to each userdata's ownership flag. Only the owning userdata deletes the native
value.

Implementation: [value_userdata.hpp](detail/value_userdata.hpp).

## Owned Lua callbacks

`luaval_to_owned_callback` converts a Lua function to `std::function` without
handler or alias registration. C++ copies and temporary call anchors share one
registration; clearing one copy leaves the others valid. Conversion failure
preserves the destination. The call anchor also keeps a callback alive if it
replaces itself during invocation.

Callback arguments and results exclude `std::function`, including functions
nested in supported containers. Payload converters run in an empty environment
and must handle Lua-error cleanup and borrowed lifetimes. Cached bridge closures
access globals and the registry explicitly; their empty environments avoid
retaining the first caller's sandbox or coroutine.

The Lua VM and its coroutines share a registry lifetime sentinel. Callback
invocation requires the owning thread and a live VM. The mutex protects release
bookkeeping, not the Lua VM. Last-reference release on another thread queues
cleanup without allocation or Lua access; the next owner-thread registration or
call drains it, or VM close discards it.

### Error handling and protected frames

C++ ownership stays outside protected Lua frames. Each acquired registry root
is recorded immediately so partial registration can be cleaned up. Callback
registration uses a protected preflight because `lua_cpcall` cannot see the
caller's input slot. The preflight grows the physical stack beyond `top + 4`;
the subsequent `lua_checkstack(L, 4)` only updates the caller's C API limit and
cannot allocate in Lua 5.1/LuaJIT.

Initial bridge-closure allocation runs in a protected frame. Debug callback
setup remains protected regardless of installed hooks. The Release fast path
falls back to protected setup for cache misses or pending cleanup. A stack
capacity limit is an ordinary failure; allocation failure while growing the
stack in the Release fast path is outside the recovery contract.

### Script trust and reentrancy

All builds trust scripts, hooks, finalizers and error reporters. Bridge frames
may be observed, but private calls or replay, and mutation of frames,
environments or the registry, are unguarded: they may repeat callbacks or corrupt
registration. Use public APIs for invocation; recursion is supported.

Implementation: [callback_from_lua.hpp](detail/callback_from_lua.hpp) and
[callback_state.hpp](detail/callback_state.hpp).

## RefPtr conversion

`cocos2d::RefPtr<T>` uses the same Lua userdata, inheritance checks and identity
cache as `T*`. There is no Lua RefPtr class. Include `lua_conversion.hpp` as for
other cocos conversions.

```cpp
void setTexture(cocos2d::RefPtr<cocos2d::Texture2D> texture);
bool acceptsTexture(const cocos2d::RefPtr<cocos2d::Texture2D>& texture);
cocos2d::RefPtr<cocos2d::Texture2D> getTexture();
```

- Lua `nil` converts to an empty RefPtr, and an empty RefPtr returns `nil`.
- A valid userdata (including a derived type or a `.c_instance` wrapper) is
  retained by the converted parameter. Failed conversion leaves the destination
  unchanged. Object validation remains enabled with `CC_LUA_BINDING_CHECKS=0`.
- By-value and const lvalue-reference parameters are supported. Mutable
  lvalue-reference and rvalue-reference parameters require an explicit adapter;
  Lua has no smart-pointer slot to update or move from.
- Nonempty output adds one independent retain/autorelease pair before pushing
  the existing object userdata. This keeps sole-owner temporary results alive
  until the current autorelease pool drains. The source RefPtr is not consumed.
  Repeated returns and objects already in an autorelease pool are balanced.
- Returning a const reference to a RefPtr uses the same output policy. Pointee
  constness follows the existing `const T*` binding convention; it does not
  create a read-only Lua object.
- This does not give Lua variables persistent native ownership. Objects needed
  after pool cleanup still require an engine owner or an explicit retain.
  Conversion runs on the scripting thread with the normal autorelease pool.

Bindings whose overloads differ only between `T*` and `RefPtr<T>` have the same
Lua representation; use an explicit adapter or expose only one overload.
