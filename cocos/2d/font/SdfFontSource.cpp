#include "SdfFontSource.h"
#include "internal/FontService.h"
#include "base/Director.h"
#include "renderer/Renderer.h"
#include FT_TRUETYPE_TABLES_H

namespace cc
{
struct SdfFontSource::Impl
{
    std::shared_ptr<font::FontFace> face;
    font::RasterContext context;
    int32_t ppem26_6{};
    int ascent{}, descent{};
};
SdfFontSource::SdfFontSource(std::unique_ptr<Impl> impl) : _impl(std::move(impl)) {}
SdfFontSource::~SdfFontSource() = default;

std::shared_ptr<SdfFontSource> SdfFontSource::open(std::span<const uint8_t> data, int rasterPpem)
{
    if (rasterPpem <= 0 || rasterPpem > INT32_MAX / 64)
        return {};
    const int32_t ppem26_6 = rasterPpem * 64;
    if (font::selectRasterPpem(FontRasterMode::Sdf, ppem26_6) != ppem26_6)
        return {};
    GlyphStatus status;
    auto face = FontRendering::getInstance()._service->face(data, status);
    if (!face)
        return {};
    auto* header = static_cast<const TT_HoriHeader*>(FT_Get_Sfnt_Table(face->nativeFace(), ft_sfnt_hhea));
    if (!header || header->Ascender <= header->Descender || !face->nativeFace()->units_per_EM)
        return {};
    auto impl = std::make_unique<Impl>();
    impl->ppem26_6 = ppem26_6;
    impl->ascent = header->Ascender;
    impl->descent = header->Descender;
    impl->face = std::move(face);
    return std::shared_ptr<SdfFontSource>(new SdfFontSource(std::move(impl)));
}
int SdfFontSource::rasterPpem() const { return _impl->ppem26_6 / 64; }
int SdfFontSource::ascentUnits() const { return _impl->ascent; }
int SdfFontSource::descentUnits() const { return _impl->descent; }
int SdfFontSource::unitsPerEm() const { return _impl->face->nativeFace()->units_per_EM; }
uint32_t SdfFontSource::glyphCount() const { return uint32_t(_impl->face->nativeFace()->num_glyphs); }
uint32_t SdfFontSource::glyphIndex(char32_t cp) const { return FT_Get_Char_Index(_impl->face->nativeFace(), cp); }
bool SdfFontSource::advance(uint32_t glyph, float& units) const
{
    auto face = _impl->face->nativeFace();
    if (FT_Load_Glyph(face, glyph, FT_LOAD_NO_SCALE | FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP))
        return false;
    units = float(face->glyph->metrics.horiAdvance);
    return true;
}
static SdfGlyphBounds boundsOf(const font::GlyphImage& image)
{
    return {image.leftPx, image.topPx, int(image.width), int(image.height)};
}
bool SdfFontSource::bounds(uint32_t glyph, SdfGlyphBounds& out) const
{
    auto result = font::SdfRasterizer::measure(_impl->context, {_impl->face->bytes(), glyph, _impl->ppem26_6});
    out = boundsOf(result.image);
    return result.status == GlyphStatus::Ready;
}
bool SdfFontSource::bitmap(uint32_t glyph, int ppem, SdfGlyphBounds& out, std::vector<uint8_t>& pixels) const
{
    auto result = font::BitmapRasterizer().rasterize(_impl->context, {_impl->face->bytes(), glyph, ppem});
    out = boundsOf(result.image);
    pixels = std::move(result.image.pixels);
    return result.status == GlyphStatus::Ready;
}
void SdfFontSource::prepare(std::span<const Request> glyphs, std::span<SdfGlyphView> views)
{
    auto& service = *FontRendering::getInstance()._service;
    auto& renderer = *Director::getInstance()->getRenderer();
    std::fill(views.begin(), views.end(), SdfGlyphView{});
    if (glyphs.size() != views.size() || !renderer.isFrameActive() || renderer.isRendering())
        return;
    const auto key = [](const Request& request) {
        const auto& source = *request.font->_impl;
        return font::GlyphKey{source.face->bytes(), request.glyph, FontRasterMode::Sdf, source.ppem26_6};
    };
    std::vector<font::GlyphAtlas::Lease> pins(glyphs.size());
    std::vector<font::GlyphKey> missing;
    for (size_t i = 0; i < glyphs.size(); ++i)
    {
        pins[i] = service.lookupRequest(key(glyphs[i]));
        if (!pins[i] || *pins[i]->publication != GlyphStatus::Ready)
            missing.push_back(key(glyphs[i]));
    }
    if (!missing.empty())
        service.prepare(renderer, missing, true);
    for (size_t i = 0; i < glyphs.size(); ++i)
    {
        auto slot = pins[i] ? std::move(pins[i]) : service.resolve(key(glyphs[i]));
        if (!slot || *slot->publication != GlyphStatus::Ready || !slot->page)
            continue;
        auto* texture = slot->page->texture.get();
        const float w = float(texture->getPixelsWide()), h = float(texture->getPixelsHigh());
        const auto r = slot->rect;
        views[i] = {std::move(slot), texture, (r.x + 1) / w, (r.y + 1) / h,
                    (r.x + r.w - 1) / w, (r.y + r.h - 1) / h};
    }
}
}  // namespace cc
