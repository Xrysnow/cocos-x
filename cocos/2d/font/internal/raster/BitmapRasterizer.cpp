#include "RasterGeometry.h"
#include FT_BBOX_H
#include <cstring>

namespace cc::font::detail
{
RasterResult copyBitmap(const FT_Bitmap& source, int left, int top)
{
    GlyphImage image;
    image.encoding = RasterEncoding::Coverage;
    if (!source.width || !source.rows)
        return {GlyphStatus::Ready, std::move(image)};
    if (source.width > maxImageSide || source.rows > maxImageSide)
        return {GlyphStatus::TooLarge};
    const bool mono = source.pixel_mode == FT_PIXEL_MODE_MONO;
    if (!source.buffer || (!mono && (source.pixel_mode != FT_PIXEL_MODE_GRAY || source.num_grays < 2)))
        return {GlyphStatus::RasterError};
    const auto stride = std::abs(int64_t(source.pitch));
    if (stride < (mono ? (source.width + 7) / 8 : source.width) || stride * (source.rows - 1) > PTRDIFF_MAX)
        return {GlyphStatus::RasterError};
    image.width = image.rowBytes = source.width;
    image.height                 = source.rows;
    image.leftPx                 = left;
    image.topPx                  = top;
    image.pixels.resize(size_t(source.width) * source.rows);
    for (unsigned y = 0; y < source.rows; ++y)
    {
        const auto* row = source.buffer + (source.pitch < 0 ? source.rows - 1 - y : y) * stride;
        auto* out       = image.pixels.data() + size_t(y) * source.width;
        if (mono)
            for (unsigned x = 0; x < source.width; ++x)
                out[x] = (row[x / 8] & (0x80u >> (x % 8))) ? 255 : 0;
        else if (source.num_grays == 256)
            std::memcpy(out, row, source.width);
        else
            for (unsigned x = 0; x < source.width; ++x)
                out[x] = static_cast<uint8_t>(
                    std::min(255u, (255u * row[x] + (source.num_grays - 1) / 2) / (source.num_grays - 1)));
    }
    return {GlyphStatus::Ready, std::move(image)};
}

RasterResult rasterBitmap(FT_GlyphSlot slot, const RasterRequest& req)
{
    FT_BBox box;
    if (FT_Outline_Get_BBox(&slot->outline, &box))
        return {GlyphStatus::RasterError};
    if (std::ceil(box.xMax / 64.) - std::floor(box.xMin / 64.) > maxImageSide ||
        std::ceil(box.yMax / 64.) - std::floor(box.yMin / 64.) > maxImageSide)
        return {GlyphStatus::TooLarge};
    if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL))
        return {GlyphStatus::RasterError};
    if (stopped(req))
        return {GlyphStatus::Cancelled};
    return copyBitmap(slot->bitmap, slot->bitmap_left, slot->bitmap_top);
}
}  // namespace cc::font::detail
