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
the original object. By-value inputs require copying; they never move from the
Lua-owned object. Rvalue-reference inputs require an explicit adapter.

A non-reference native result of a registered value type becomes owned userdata.
Mutable results prefer construction from an rvalue, including move-only values;
copy-only types with an explicitly deleted move constructor fall back to copying.
Const results keep const-qualified construction and do not move through a cast.
Output does not require a default constructor. `T&` and `const T&` results remain
borrowed, with their existing constness and owner rules. Rvalue-reference results
keep the existing non-consuming conversion and require an explicit adapter in
generated bindings.

`native_to_luaval` and its field helpers preserve the supplied value category.
Lvalues copy through the registered value converter; mutable rvalues may move.
Converters that only accept a mutable lvalue retain their existing calling path.
Container output and Lua callback argument output keep their existing element
and argument copying behavior.

Lua-to-native sequence and map conversion may move its own local element, key
and mapped-value temporaries, with copy-only fallbacks. Vector conversion reserves
its final size before insertion. Reading a value userdata still copies from it;
failed sequence or map conversion leaves the destination unchanged. Pair and
tuple conversion retain their existing partial-update failure behavior.

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

## Base data tables

Base value conversions use native field names and the existing scalar rules
(including numeric enum values). Failed input conversion leaves the destination
unchanged.

- `HSV`: `h`, `s`, `v`, `a`.
- `ccBezierConfig`: `controlPoint_1`, `controlPoint_2`, `endPosition`, each a Vec2.
  Input also accepts the three-element `{control1, control2, end}` array used by
  `BezierBy:create` and `BezierTo:create`; output uses the named fields.
- `EmissionShape`: `type`, `x`, `y`, `innerWidth`, `innerHeight`, `outerWidth`,
  `outerHeight`, `innerRadius`, `outerRadius`, `coneOffset`, `coneAngle`, `edgeBias`,
  `fourccId`. All fields are required on input. The `ParticleSystem:create*Shape`
  helpers return complete tables that can be edited and passed directly to
  `setEmissionShape` or `addEmissionShape`.
- `ParticleEmissionMaskDescriptor`: `size` (Vec2), `points` (an array of Vec2).
  Output copies the cache data before allocating Lua tables, so the returned
  snapshot stays independent of cache changes.
- `Viewport`: `x`, `y`, `w`, `h`; `ScissorRect`: `x`, `y`, `width`, `height`.

Rendering descriptors accept partial tables: omitted or nil fields retain their
native defaults; supplied fields must convert successfully. Output includes all
fields, including nested descriptor tables.

- `TextureDescriptor`: `textureType`, `textureFormat`, `textureUsage`, `width`,
  `height`, `depth`, `samplerDescriptor`. The nested sampler uses the existing
  `minFilter`, `magFilter`, `sAddressMode`, `tAddressMode` conversion, including
  its legacy `wrapS`/`wrapT` input aliases.
- `StencilDescriptor`: `stencilFailureOperation`, `depthFailureOperation`,
  `depthStencilPassOperation`, `stencilCompareFunction`, `readMask`, `writeMask`.
- `DepthStencilDescriptor`: `depthCompareFunction`, `backFaceStencil`,
  `frontFaceStencil`, `flags`.

Implementation: [value_types.hpp](detail/cocos/value_types.hpp),
[particle_types.hpp](detail/cocos/particle_types.hpp), and
[render_types.hpp](detail/cocos/render_types.hpp). `GLContextAttrs` remains
outside these conversions.

## Value userdata ownership

Only an explicit `value_type<T>` specialization opts a native class into userdata
value semantics. Borrowed values get distinct userdata even when another
userdata already refers to the same native address, preserving each borrow's
constness and ownership. The userdata keeps tolua's pointer-sized representation.

Tolua's default collector keys ownership by native address. Since a borrowed
value can share an owned value's address, value types instead collect according
to each userdata's ownership flag. Only the owning userdata deletes the native
value.

Value conversion prepares a rooted userdata with a null pointer, metatable and
ownership flags before constructing the native copy or move. Publishing the
constructed pointer makes no further Lua calls. A C++ construction exception
restores the converter's stack and leaves an empty userdata safe for collection;
field helpers also remove their temporary key when C++ conversion throws.

`push_value_owned`, including a converted `own_value` marker, adopts a raw pointer
exactly once. It protects Lua registration, deletes the adopted pointer if
registration fails, and propagates the Lua error; a null Lua state deletes it.
After successful adoption, ordinary GC deletes it once. `owned_value` itself is
a transfer marker, so an unpushed marker does not manage the allocation.

This is a local registration guarantee, not general C++ unwinding across Lua
errors. Lua errors can still skip native caller locals, including an invocation's
by-value result while userdata setup is running. Constructors, custom converters
and callers remain responsible for their Lua-error lifetimes. Scripts, hooks and
registry mutation follow the trusted-script contract described below.

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
