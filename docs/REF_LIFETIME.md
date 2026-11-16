# Ref lifetime and host adaptation

The CTAD simplification and necessary Windows Debug verification are complete.
See the [CTAD report](../../../../research/refcount-unification_2026-10-31/ctad-report.md)
for evidence, initial failures and fixes, and its cleanup record. Full shared,
Release and cross-platform acceptance were not run in this update; follow-up
checks depend on the remaining Ref, Lua and ownership risks.

`cocos2d::Ref` is a compatibility alias for `cc::RefCounted`. There is one
counter implementation, one vtable identity, and one host service table in the
core. `RefPtr<T>` remains an alias for `cc::IntrusivePtr<T>`.

This changes the C++ ABI. Rebuild the core, static Lua/extension libraries,
applications and external consumers together. Do not mix previous binaries
with these headers. Forward declarations must name `cc::RefCounted`, or include
`base/CCRef.h`; `class cocos2d::Ref` is no longer a valid declaration. Overloads
and specializations cannot distinguish the two names.

## Construction and ownership

The common counter starts at zero. A normal `cc::IntrusivePtr{new T(...)}`
uses class template argument deduction (CTAD) and acquires the first reference.
Local/Atomic policy is immutable; Atomic protects the count, not the object's
methods, the autorelease pool or Lua.

All public, unambiguous RefCounted derivatives use the same adaptation protocol,
regardless of namespace or directory. Default construction needs no eligibility
marker or host-specific token:

```cpp
class Widget : public cocos2d::Ref {
public:
    Widget() = default;
    explicit Widget(cocos2d::RefConstructionToken token) : cocos2d::Ref(token) {}
};
```

The token overload is needed only for types offering policy construction through
`makeRef<T, RefThreading::Atomic>()` / `makeThreadSafeRef<T>()`. It must forward
the token to the common base. The factory verifies actual policy forwarding in
Release as well as Debug. Restricted business constructors remain restricted.

Construction and counting never initialize a pool, VM or script sidecar. Host
services, thread confinement, active VM, registered type and ownership shares
are checked at the actual Lua/pool boundary. The stable object ID is assigned
uniformly; script state is still allocated only when used.

`ConcurrentRefCountedBase` is also a pure alias. HTTP request/response roots
explicitly select Atomic and acquire one reference
in their constructor to retain the existing `new`/owned-raw handoff contract.
Do not acquire a second first reference when adopting these legacy interfaces.
Device objects using `GFXDeviceObject` retain their separate deleter protocol.

## Native creation at the original call site

Use the existing business factory, member or original friend context for new:

```cpp
auto object = cc::IntrusivePtr{new Widget()};
auto optional = cc::IntrusivePtr{new (std::nothrow) Widget()};
```

The complete object is constructed at count zero, then IntrusivePtr establishes
one reference. Arguments are evaluated by the original new expression. It does
not call init(), enter a pool or take ownership of constructor pointer arguments.
Business create factories retain their init() calls and return an empty owner on
failure; local RAII performs the corresponding release.

Private/protected constructors and class allocation functions keep their original
access declarations. Construct them in the original authorized context, without
adding a generic construction friend, factory key or allocation-access probe.
Create remains the business initialization convention; no extra layer enforces
that callers can only use create. CTAD does not change C++ access checking.

Nothrow returns empty only when allocation fails; constructor exceptions still
propagate. Keep native class-specific new/delete, over-alignment and constructor
failure cleanup. Preserve the original new T versus new T() initialization form.
There is no common allocation backend, generic creation wrapper or new lifetime
recorder in the current contract.

Return types, members and declarations without a deducible pointer expression
may still use explicit IntrusivePtr<T>. Existing-pointer wrapping follows its
actual share source: borrowed pointers acquire a share, and adopt_ref is only
for an existing share explicitly handed off. Never adopt a newly zero-count
object or infer ownership by inspecting its current count.

The policy helpers makeRef<T, Policy>() / makeThreadSafeRef<T>() retain their
RefConstructionToken forwarding and policy checks. Their authorized native new
expression establishes the same first share; they do not select a separate
allocator or imply Lua/pool participation. Already simplified redundant default
Ref() base initializers stay omitted; real policy/argument forwarding remains.

Gfx raw-zero virtual factories keep their raw-zero contract and original new
expressions. Their callers either establish the first share or use the existing
native destroy/delete protocol. Do not introduce a first share merely to detach
it into a raw-zero API. Constructor-owned HTTP shares, Device singleton chains,
unique/shared/native owners, arrays, placement storage and stack/embedded values
retain their actual ownership protocols. Do not turn every new expression into
an IntrusivePtr construction.

The earlier unified creation backend and added four-event lifetime diagnostics
have been removed. Their historical reports remain evidence of the earlier
direction, not current features or validation requirements. Existing leak
checks remain independent; this change does not redesign release or deletion.

## Pool and script services

The low-level implementation includes no cocos pool or Lua headers and links
without either subsystem. The host explicitly installs services at
`PoolManager::getInstance()` or `toluafix_open()`. The normal Director starts the
pool before Lua results or explicit owners are handed to it. `autorelease()`
never creates or reopens a pool; missing/closed services, wrong host threads and
invalid reference shares throw. `transferToAutoreleasePool` enqueues successfully
before detaching its owner, preserving ownership on failure.

Lua conversion checks the active VM, registered type and live canonical Ref
address even with optional binding checks disabled. Independent Lua classes
such as Director need not inherit cc.Ref. Coroutines of the active VM share its
registry identity and remain supported. Other VMs and worker threads are rejected
before ownership transfer; the registry identity comparison does not allocate or
change the Lua stack. Existing cc.Ref fallback and L0 borrowing remain unchanged.

All script identity/pool access runs on the host thread. A script-bound object's
destruction also requires that thread while its VM is active. An unbound Atomic
object may be released on a worker without accessing Lua or pool state.

Script state is allocated lazily as a stable sidecar. Object layout does not
depend on `CC_ENABLE_SCRIPT_BINDING`. Replace direct field access as follows:

| Previous field | Accessor |
| --- | --- |
| `_ID` | `getScriptObjectID()` |
| `_luaID` | `getScriptIdentity().luaID` |
| `_rooted` | `getScriptIdentity().rooted` |
| `_scriptObject` | `getScriptIdentity().scriptObject` |

`getScriptIdentityIfExists()` observes the sidecar without allocating it. These
accessors are internal C++ host interfaces, not new Lua methods. The sidecar
remains available during derived destruction; the common base then invalidates
the Lua mapping. Natural destruction and failed construction follow this same
cleanup path. The low-level destructor never constructs a VM or manager.

LuaStack closes its context before `lua_close`. Raw VMs opened by `toluafix_open`
also have a registry lifetime guard; embedders should explicitly call
`closeCocosScriptContext(L)` before closing the VM. Reopening advances an epoch,
so old mappings cannot target a new VM. Only one cocos VM may be active per core.
Late object destruction after context closure skips script callbacks.

Service tables and their code must outlive every object and host client using
them. Removal requires host quiescence (no concurrent construction/service use),
no live common objects and no active script context. Do not unload a DLL with
live objects or keep a service pointer after unloading its provider.

## Existing ownership corrections

Removing the creation abstraction must preserve the ownership corrections made
while auditing its callers:

- An inner Action retained by AccelAmplitude is released by its destructor; it
  must not be directly deleted while another owner still holds it.
- ProgramManager, ShaderCache and ProgramStateRegistry return their owned first
  share on init failure, matching normal singleton cleanup. RenderMode owners
  and Live2D RenderTarget cleanup likewise release the share they own.
- Spine's shared_ptr control block for ProgramState returns its one intrusive
  share through a release deleter; it must not directly delete the shared Ref.
- PUEmitter clone results detach only at setters verified to consume ownership
  without retaining; borrowed or retaining calls keep get(). Native-owned PU
  members retain their existing deletion protocol.
- VideoPlayerEventQueue uses its native shared_ptr/enable_shared_from_this
  control block. It does not gain an intrusive share merely because it is an
  engine helper.

These are ownership pairings, not new allocation or tracing policies. Preserve
business initialization and shutdown timing when changing a creation expression.
