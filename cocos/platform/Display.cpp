#include "platform/DisplayInternal.h"
#include <algorithm>
#include <unordered_map>

namespace cc::display {
namespace {
std::unordered_map<Key, DisplayId> ids;
std::uint64_t serial = 0;
}

void endSession() { ids.clear(); }

std::optional<DisplayInfo> snapshot(Key key)
{
    if (!key) return {};
    auto result = read(key);
    if (result) {
        auto [it, inserted] = ids.try_emplace(key);
        if (inserted) it->second = DisplayId{++serial};
        result->id = it->second;
    }
    return result;
}

Key keyForId(DisplayId id)
{
    for (const auto& [key, value] : ids)
        if (value == id) return key;
    return 0;
}
}

namespace cc {
std::optional<std::vector<DisplayInfo>> Display::getAllDisplayInfo()
{
    auto keys = display::enumerate();
    if (!keys) return {};
    std::erase_if(display::ids, [&](const auto& pair) {
        return std::find(keys->begin(), keys->end(), pair.first) == keys->end();
    });
    std::vector<DisplayInfo> result;
    for (auto key : *keys) {
        auto info = display::snapshot(key);
        if (!info) return {};
        result.emplace_back(std::move(*info));
    }
    return result;
}

std::optional<DisplayInfo> Display::getDisplayInfo(DisplayId id)
{
    return display::snapshot(display::keyForId(id));
}

std::optional<DisplayInfo> Display::getPrimaryDisplayInfo()
{
    return display::snapshot(display::primary());
}
}
