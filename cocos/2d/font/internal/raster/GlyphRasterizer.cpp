#include "RasterGeometry.h"
#include FT_BBOX_H
#include FT_TRUETYPE_TABLES_H
#include <climits>
#include <new>

namespace cc::font
{
int32_t selectRasterPpem(FontRasterMode mode, int32_t requested) noexcept
{
    if (requested <= 0)
        return 0;
    switch (mode)
    {
    case FontRasterMode::Bitmap:
        return requested;
    case FontRasterMode::Sdf:
    case FontRasterMode::Msdf:
        return (requested <= 32 * 64 ? 32 : requested <= 48 * 64 ? 48 : 64) * 64;
    }
    return 0;
}

static bool hasTable(FT_Face face, FT_ULong tag)
{
    FT_ULong length = 0;
    return FT_Load_Sfnt_Table(face, tag, 0, nullptr, &length) == 0 && length != 0;
}

GlyphStatus detail::validateFace(FT_Face face)
{
    if (FT_HAS_COLOR(face))
        return GlyphStatus::UnsupportedColorFont;
    for (FT_ULong tag :
         {FT_MAKE_TAG('C', 'O', 'L', 'R'),
          FT_MAKE_TAG('C', 'P', 'A', 'L'),
          FT_MAKE_TAG('s', 'b', 'i', 'x'),
          FT_MAKE_TAG('S', 'V', 'G', ' '),
          FT_MAKE_TAG('C', 'B', 'D', 'T'),
          FT_MAKE_TAG('C', 'B', 'L', 'C')})
        if (hasTable(face, tag))
            return GlyphStatus::UnsupportedColorFont;
    if (!FT_IS_SFNT(face) || !FT_IS_SCALABLE(face) || FT_Select_Charmap(face, FT_ENCODING_UNICODE))
        return GlyphStatus::UnsupportedFont;
    if (!(hasTable(face, FT_MAKE_TAG('g', 'l', 'y', 'f')) || hasTable(face, FT_MAKE_TAG('C', 'F', 'F', ' ')) ||
          hasTable(face, FT_MAKE_TAG('C', 'F', 'F', '2'))))
        return GlyphStatus::UnsupportedFont;
    return GlyphStatus::Ready;
}

struct RasterContext::Impl
{
    FT_Library library{};
    FT_Face face{};
    std::shared_ptr<const FontBytes> bytes;
    int32_t size{};

    ~Impl()
    {
        if (face)
            FT_Done_Face(face);
        if (library)
            FT_Done_FreeType(library);
    }
    GlyphStatus open(const std::shared_ptr<const FontBytes>& font)
    {
        if (font == bytes)
            return GlyphStatus::Ready;
        if (!library && FT_Init_FreeType(&library))
            return GlyphStatus::RasterError;
        FT_Face next{};
        if (FT_New_Memory_Face(library, font->data(), static_cast<FT_Long>(font->size()), 0, &next))
            return GlyphStatus::UnsupportedFont;
        auto status = detail::validateFace(next);
        if (status != GlyphStatus::Ready)
        {
            FT_Done_Face(next);
            return status;
        }
        if (face)
            FT_Done_Face(face);
        face  = next;
        bytes = font;
        size  = 0;
        return status;
    }
};

RasterContext::RasterContext() : _impl(std::make_unique<Impl>())
{
}
RasterContext::~RasterContext() = default;

RasterResult GlyphRasterizer::render(RasterContext& context, const RasterRequest& req, FontRasterMode mode, bool boundsOnly)
{
    if (detail::stopped(req))
        return {GlyphStatus::Cancelled};
    if (!req.font || req.font->empty() || req.font->size() > LONG_MAX || req.rasterPpem26_6 <= 0 ||
        selectRasterPpem(mode, req.rasterPpem26_6) != req.rasterPpem26_6)
        return {GlyphStatus::InvalidInput};
    auto& worker = *context._impl;
    auto status  = worker.open(req.font);
    if (status != GlyphStatus::Ready)
        return {status};
    if (req.glyphId >= static_cast<uint32_t>(worker.face->num_glyphs))
        return {GlyphStatus::InvalidInput};
    if (worker.size != req.rasterPpem26_6)
    {
        worker.size = 0;
        if (FT_Set_Char_Size(worker.face, 0, req.rasterPpem26_6, 72, 72))
            return {GlyphStatus::TooLarge};
        worker.size = req.rasterPpem26_6;
    }
    FT_Int32 flags = FT_LOAD_NO_BITMAP | FT_LOAD_NO_AUTOHINT;
    if (mode != FontRasterMode::Bitmap)
        flags |= FT_LOAD_NO_HINTING;
    if (FT_Load_Glyph(worker.face, req.glyphId, flags))
        return {GlyphStatus::RasterError};
    auto slot = worker.face->glyph;
    if (slot->format != FT_GLYPH_FORMAT_OUTLINE)
        return {GlyphStatus::UnsupportedFont};
    try
    {
        if (mode == FontRasterMode::Bitmap)
            return detail::rasterBitmap(slot, req);
        return detail::rasterField(slot, req, mode == FontRasterMode::Msdf, boundsOnly);
    }
    catch (const std::bad_alloc&)
    {
        return {GlyphStatus::TooLarge};
    }
}

RasterResult BitmapRasterizer::rasterize(RasterContext& ctx, const RasterRequest& req) const
{
    return render(ctx, req, FontRasterMode::Bitmap);
}
RasterResult SdfRasterizer::rasterize(RasterContext& ctx, const RasterRequest& req) const
{
    return render(ctx, req, FontRasterMode::Sdf);
}
RasterResult MsdfRasterizer::rasterize(RasterContext& ctx, const RasterRequest& req) const
{
    return render(ctx, req, FontRasterMode::Msdf);
}
}  // namespace cc::font
