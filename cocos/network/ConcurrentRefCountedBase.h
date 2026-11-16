#pragma once

#include "gfx/base/RefCounted.h"

namespace cocos2d
{
// Compatibility name only. Network roots explicitly select Atomic and acquire
// the legacy owned-raw first reference; this alias adds no counter or Lua state.
using ConcurrentRefCountedBase = cc::RefCounted;
}  // namespace cocos2d
