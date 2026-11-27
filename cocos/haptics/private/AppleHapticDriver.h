#pragma once
#import <CoreHaptics/CoreHaptics.h>
#include "MobileHaptics.h"

namespace cc::haptics::detail
{
// The output worker exclusively owns the engine returned by this factory.
std::unique_ptr<MobileDriver> makeAppleHapticDriver(
    std::function<CHHapticEngine*()> factory, std::function<void()> interrupted = {});
}  // namespace cc::haptics::detail
