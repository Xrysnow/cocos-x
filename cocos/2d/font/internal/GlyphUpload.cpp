#include "GlyphUpload.h"
#include <cstring>

namespace cc::font
{
void prepareUpload(GlyphImage& image)
{
    if (!image.width || !image.height)
        return;
    const int w = int(image.width) + 2, h = int(image.height) + 2;
    const bool rgba     = image.encoding == RasterEncoding::Msdf;
    const size_t stride = size_t(w) * (rgba ? 4 : 1);
    std::vector<uint8_t> bytes(stride * h);
    for (uint32_t y = 0; y < image.height; ++y)
    {
        auto* dst = bytes.data() + (y + 1) * stride + (rgba ? 4 : 1);
        auto* src = image.pixels.data() + size_t(y) * image.rowBytes;
        if (!rgba)
            std::memcpy(dst, src, image.width);
        else
            for (uint32_t x = 0; x < image.width; ++x)
            {
                std::memcpy(dst + 4 * x, src + 3 * x, 3);
                dst[4 * x + 3] = 255;
            }
    }
    if (image.encoding != RasterEncoding::Coverage)
    {
        const size_t channels = rgba ? 4 : 1;
        for (int y = 1; y < h - 1; ++y)
        {
            auto* row = bytes.data() + y * stride;
            std::memcpy(row, row + channels, channels);
            std::memcpy(row + (w - 1) * channels, row + (w - 2) * channels, channels);
        }
        std::memcpy(bytes.data(), bytes.data() + stride, stride);
        std::memcpy(bytes.data() + (h - 1) * stride, bytes.data() + (h - 2) * stride, stride);
    }
    image.pixels   = std::move(bytes);
    image.rowBytes = static_cast<uint32_t>(stride);
}
}  // namespace cc::font
