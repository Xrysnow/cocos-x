#pragma once

#include "../../FontTypes.h"
#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>

namespace cc::font
{
using cc::FontRasterMode;
using cc::GlyphStatus;
enum class RasterEncoding
{
    Coverage,
    Sdf,
    Msdf
};
using FontBytes = std::vector<uint8_t>;

// Sizes use FreeType's 26.6 pixels per em. Zero denotes an invalid request.
int32_t selectRasterPpem(FontRasterMode mode, int32_t requestedPpem26_6) noexcept;

struct RasterRequest
{
    std::shared_ptr<const FontBytes> font;
    uint32_t glyphId;
    int32_t rasterPpem26_6;
    const std::atomic_bool* cancelled{};  // Borrowed for the duration of rasterize().
};

struct GlyphImage
{
    RasterEncoding encoding{};
    uint32_t width{}, height{}, rowBytes{};
    int32_t leftPx{}, topPx{};  // Baseline origin, Y up. Pixel rows run top to bottom.
    float distanceRangePx{};    // Full encoded range, in generated pixels.
    std::vector<uint8_t> pixels;
};

struct RasterResult
{
    GlyphStatus status;
    GlyphImage image{};
};

// One context per worker. Holds the most recently opened face and its backing bytes.
class RasterContext
{
public:
    RasterContext();
    ~RasterContext();
    RasterContext(const RasterContext&)            = delete;
    RasterContext& operator=(const RasterContext&) = delete;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
    friend class GlyphRasterizer;
};

class GlyphRasterizer
{
public:
    virtual ~GlyphRasterizer()                                                 = default;
    virtual RasterResult rasterize(RasterContext&, const RasterRequest&) const = 0;

protected:
    static RasterResult render(RasterContext&, const RasterRequest&, FontRasterMode, bool boundsOnly = false);
};

class BitmapRasterizer final : public GlyphRasterizer
{
public:
    RasterResult rasterize(RasterContext&, const RasterRequest&) const override;
};
class SdfRasterizer final : public GlyphRasterizer
{
public:
    static RasterResult measure(RasterContext& ctx, const RasterRequest& req)
    {
        return render(ctx, req, FontRasterMode::Sdf, true);
    }
    RasterResult rasterize(RasterContext&, const RasterRequest&) const override;
};
class MsdfRasterizer final : public GlyphRasterizer
{
public:
    RasterResult rasterize(RasterContext&, const RasterRequest&) const override;
};
}  // namespace cc::font
