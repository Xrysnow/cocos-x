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
- `ManifestAsset`: output-only snapshot of `md5`, `path`, `compressed`, `size`,
  `downloadState`; the native asset is copied before Lua table allocation.
  This conversion lives in [assets_manager.hpp](detail/cocos/assets_manager.hpp)
  and is available through the shared conversion header.
- `Viewport`: `x`, `y`, `w`, `h`; `ScissorRect`: `x`, `y`, `width`, `height`.

Rendering descriptors accept partial tables: omitted or nil fields retain their
native defaults; supplied fields must convert successfully. Output includes all
fields, including nested descriptor tables.

- `TextureDescriptor`: `textureType`, `textureFormat`, `textureUsage`, `width`,
  `height`, `depth`, `samplerDescriptor`. The nested sampler uses the canonical
  `minFilter`, `magFilter`, `sAddressMode`, `tAddressMode` record below.
- `StencilDescriptor`: `stencilFailureOperation`, `depthFailureOperation`,
  `depthStencilPassOperation`, `stencilCompareFunction`, `readMask`, `writeMask`.
- `DepthStencilDescriptor`: `depthCompareFunction`, `backFaceStencil`,
  `frontFaceStencil`, `flags`.

Implementation: [value_types.hpp](detail/cocos/value_types.hpp),
[particle_types.hpp](detail/cocos/particle_types.hpp), and
[render_types.hpp](detail/cocos/render_types.hpp). `GLContextAttrs` remains
outside these conversions.

## Canonical sampler and navigation records

`SamplerDescriptor` and its native alias `Texture2D::TexParams` use one shared
plain-table conversion. Only `minFilter`, `magFilter`, `sAddressMode` and
`tAddressMode` are accepted. Missing/nil fields keep the native LINEAR filters
and CLAMP_TO_EDGE address modes. Supplied values must match declared native enum
values, including DONT_CARE. Unknown keys (including wrapS/wrapT), fractional or
unknown enum values fail. Texture2D's generated setter takes one such table;
TextureCube and TextureBackend use the same conversion.

`NavMeshAgentParam` is a partial table with exactly the ten native field names.
Missing/nil fields preserve the native constructor defaults: radius=0.6,
height=2, maxAcceleration=8, maxSpeed=3.5, collisionQueryRange=7.2,
pathOptimizationRange=18, separationWeight=2, updateFlags=27,
obstacleAvoidanceType=3, queryFilterType=0. An overridden radius does not alter
other omitted fields. Floats must be finite and fit float; radius, acceleration,
speed and separation are nonnegative; height and the two ranges are positive.
The three byte fields require integral values; updateFlags may contain only
Detour's five defined bits, avoidance index is 0..7 and query filter is 0..15.

Both inputs read raw own fields without metamethods, reject unknown/non-string
keys and publish the converted value only on complete success. Numeric fields
use shared scalar input conversion (so numeric strings remain accepted), then
apply these schema constraints. Input tables and conversion destinations remain
unchanged on failure. The reusable implementation is in
[record.hpp](detail/record.hpp), [value_types.hpp](detail/cocos/value_types.hpp)
and [navmesh.hpp](detail/cocos/navmesh.hpp).

`OffMeshLinkData` has an output-only shared conversion to a fresh table with
independent `startPosition` and `endPosition` Vec3 tables. No userdata identity or
borrowed lifetime is attached to the snapshot. Navigation conversions and native
headers are guarded by CC_USE_NAVMESH. The old module compatibility macros and
local descriptor/output converters have been removed. NavMesh now installs only
generated bindings: there are no manual new factories or NavMeshAgent
getUserData/setUserData adapters. The module aggregator registers the generated
module directly under the existing feature gate.

## Geometry bridges

`cc.AABB:getCorners()` and `cc.OBB:getCorners()` take no arguments and return
`std::array<Vec3, 8>` through the shared conversion: one Lua array containing
exactly eight independent Vec3 tables, in native corner order.

`cc.AABB:updateMinMax(points)` takes a `std::vector<Vec3>` (one Lua array),
updates the existing box and returns no Lua values. There is no separate count
argument. An empty input preserves the box's bounds. Input points are not
modified.

These adapters use shared invocation and `LUA_INVOKE_FOOTER`; Geometry's
generated methods also use the shared default footer. `cc.Ray:intersects` is
not registered. Native C++ geometry APIs and value ownership are unchanged.

## Physics3D generated invocation

Physics3D generated wrappers include the shared conversion header directly.
Receiver handling, scalar/enum/Vec3/Mat4 conversion, overload isolation, void
self returns and invocation errors use the common binding implementation and
CC_LUA_BINDING_CHECKS policy. There are no module-local macro overrides or
argument-rewriting prepasses.

Collision callbacks use shared owned-callback conversion: function installs or
replaces the callable, nil clears it, and other values are rejected in both
check modes. Clearing releases the Lua capture when the last native copy is
released. Native signatures, feature guards and retained registration order
continue to define the module's public surface.

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
