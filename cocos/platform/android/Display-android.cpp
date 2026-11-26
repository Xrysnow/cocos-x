#include "platform/DisplayInternal.h"
#include "platform/android/GLViewImpl-android.h"
#include "platform/android/jni/JniHelper.h"
#include "base/Director.h"
#include <algorithm>
#include <bit>
#include <cmath>

namespace cc::display {
constexpr auto host = "org/cocos/lib/CocosEngine";
std::optional<Keys> enumerate()
{
    auto ids = JniHelper::callStaticIntArrayMethod(host, "displayIds");
    if (ids.empty()) return {};
    Keys keys;
    for (size_t i = 1; i < ids.size(); ++i) keys.push_back(Key(ids[i]) + 1);
    return keys;
}
Key primary() { return 1; } // Display.DEFAULT_DISPLAY is zero.
std::optional<DisplayInfo> read(Key key)
{
    const int id = static_cast<int>(key - 1);
    auto name = JniHelper::callStaticStringMethod(host, "displayName", id);
    auto values = JniHelper::callStaticIntArrayMethod(host, "displayModeInfo", id);
    if (values.size() != 5) return {};
    DisplayInfo info;
    if (!name.empty()) info.name = std::move(name);
    if (values[0] > 0 && values[1] > 0) info.pixelSize = DisplaySize{values[0],values[1]};
    float hz = std::bit_cast<float>(values[2]), scale = std::bit_cast<float>(values[3]);
    if (std::isfinite(hz) && hz > 0) info.refreshRateHz = hz;
    if (std::isfinite(scale) && scale > 0) info.contentScale = DisplayAxisValues{scale,scale};
    if (values[4] > 0) info.logicalDpi = DisplayAxisValues{double(values[4]),double(values[4])};
    return info;
}
}
namespace cc {
std::optional<DisplayInfo> GLViewImpl::getCurrentDisplayInfo() const
{
    if (Director::getInstance()->getOpenGLView() != this) return {};
    auto binding = [] { return JniHelper::callStaticIntArrayMethod(display::host, "currentDisplayBinding"); };
    const auto before = binding();
    if (before.size() != 5 || before[0] < 0) return {};
    auto result = display::snapshot(display::Key(before[0]) + 1);
    const auto after = binding();
    if (!std::equal(before.begin(), before.end(), after.begin(), after.end())) return {};
    return result;
}
}
