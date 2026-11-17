#pragma once

#include "platform/Namespace.h"

#include "base/RefCounted.h"

namespace cc
{
// Compatibility name only. Network roots explicitly select Atomic and acquire
// the legacy owned-raw first reference; this alias adds no counter or Lua state.
using ConcurrentRefCountedBase = cc::RefCounted;
}  // namespace cc
