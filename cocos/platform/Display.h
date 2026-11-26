#pragma once

#include "platform/PlatformDefine.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace cc {

enum class DisplayId : std::uint64_t {};
enum class DisplayCoordinateSpace { ScreenLocal, Desktop };

struct DisplaySize {
    std::int32_t width, height;
};

struct DisplayRect {
    std::int32_t x, y, width, height;
};

struct DisplayAxisValues {
    double x, y;
};

struct DisplayInfo {
    DisplayId id{};
    DisplayCoordinateSpace coordinateSpace = DisplayCoordinateSpace::ScreenLocal;
    std::optional<std::string> name;
    std::optional<DisplayRect> geometry;
    std::optional<DisplayRect> availableGeometry;
    std::optional<DisplaySize> pixelSize;
    std::optional<DisplaySize> physicalSizeMm;
    std::optional<DisplayAxisValues> contentScale;
    std::optional<double> devicePixelRatio;
    std::optional<DisplayAxisValues> logicalDpi;
    std::optional<DisplayAxisValues> physicalDpi;
    std::optional<double> refreshRateHz;
};

class CC_DLL Display final {
public:
    Display() = delete;

    static std::optional<std::vector<DisplayInfo>> getAllDisplayInfo();
    static std::optional<DisplayInfo> getPrimaryDisplayInfo();
    static std::optional<DisplayInfo> getDisplayInfo(DisplayId id);
};

} // namespace cc
