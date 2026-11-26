#pragma once
#include "platform/Display.h"

namespace cc::display {
using Key = std::uintptr_t;
using Keys = std::vector<Key>;
// Keys belong to the active platform session. Zero denotes no output.
std::optional<Keys> enumerate();
std::optional<DisplayInfo> read(Key key);
Key primary();
std::optional<DisplayInfo> snapshot(Key key);
Key keyForId(DisplayId id);
void endSession();
}
