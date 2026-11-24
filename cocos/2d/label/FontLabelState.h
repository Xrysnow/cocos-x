#pragma once
#include "2d/font/internal/FontService.h"
namespace cc
{
struct FontLabelState
{
    std::shared_ptr<font::FontFace> face;
    int32_t ppem{};
    float scale{1};
    float layoutSize{};
    FontMetrics metrics;
    std::vector<font::GlyphKey> keys;
    GlyphTicket visible, warmup;
    std::map<int, Vec2> anchors;
    bool layoutOnly{};
};
}  // namespace cc
