#include "FontFace.h"
#include "raster/RasterGeometry.h"
#include FT_FONT_FORMATS_H
#include <climits>
#include <cstring>

namespace cc::font
{
int32_t requestedPpem(float points, float scale)
{
    const double value = double(points) * scale * 64;
    return value >= 0.5 && value < INT32_MAX ? int32_t(std::lround(value)) : 0;
}
FontFace::~FontFace()
{
    if (_face)
        FT_Done_Face(_face);
    if (_library)
        FT_Done_FreeType(_library);
}
cc::GlyphStatus FontFace::open(std::span<const uint8_t> data)
{
    if (data.empty())
        return cc::GlyphStatus::UnsupportedFont;
    if (data.size() > LONG_MAX)
        return cc::GlyphStatus::TooLarge;
    if (FT_Init_FreeType(&_library))
        return cc::GlyphStatus::RasterError;
    _bytes = std::make_shared<FontBytes>(data.begin(), data.end());
    if (FT_New_Memory_Face(_library, _bytes->data(), static_cast<FT_Long>(_bytes->size()), 0, &_face))
        return cc::GlyphStatus::UnsupportedFont;
    return detail::validateFace(_face);
}
bool FontFace::setSize(int32_t size)
{
    if (size <= 0)
        return false;
    if (_size == size)
        return true;
    _size = 0;
    if (FT_Set_Char_Size(_face, 0, size, 72, 72))
        return false;
    _size = size;
    return true;
}
FontMetrics FontFace::metrics() const
{
    const auto& m = _face->size->metrics;
    auto ascent = m.ascender, descent = m.descender;
    if (std::strcmp(FT_Get_Font_Format(_face), "TrueType") == 0)
    {
        ascent  = (FT_MulFix(_face->ascender, m.y_scale) + 32) & ~63L;
        descent = (FT_MulFix(_face->descender, m.y_scale) + 32) & ~63L;
    }
    return {ascent / 64.f, descent / 64.f, (ascent - descent) / 64.f};
}
uint32_t FontFace::glyph(char32_t cp) const
{
    if (cp == 0xa0)
        cp = U' ';
    if (auto it = _characters.find(cp); it != _characters.end())
        return it->second;
    if (_characters.size() >= 8192)
        _characters.clear();
    return _characters.emplace(cp, FT_Get_Char_Index(_face, cp)).first->second;
}
FontLetterDefinition FontFace::measure(char32_t cp, float scale)
{
    const auto id  = glyph(cp);
    const auto key = std::make_pair(_size, id);
    auto it        = _measurements.find(key);
    if (it == _measurements.end())
    {
        if (FT_Load_Glyph(_face, id, FT_LOAD_NO_BITMAP | FT_LOAD_NO_AUTOHINT))
            return {};
        const auto& m = _face->glyph->metrics;
        FontLetterDefinition def{};
        def.validDefinition = true;
        def.offsetX         = m.horiBearingX / 64.f;
        def.offsetY         = metrics().ascent - m.horiBearingY / 64.f;
        def.width           = m.width / 64.f;
        def.height          = m.height / 64.f;
        def.xAdvance        = int(_face->glyph->advance.x >> 6);
        if (_measurements.size() >= 8192)
            _measurements.clear();
        it = _measurements.emplace(key, def).first;
    }
    auto def    = it->second;
    def.width  /= scale;
    def.height /= scale;
    return def;
}
int FontFace::kerning(uint32_t a, uint32_t b)
{
    if (!FT_HAS_KERNING(_face))
        return 0;
    const auto key = std::make_tuple(_size, a, b);
    if (auto it = _kernings.find(key); it != _kernings.end())
        return it->second;
    FT_Vector v{};
    const int offset = FT_Get_Kerning(_face, a, b, FT_KERNING_DEFAULT, &v) ? 0 : int(v.x >> 6);
    if (_kernings.size() >= 8192)
        _kernings.clear();
    _kernings.emplace(key, offset);
    return offset;
}
GlyphKey FontFace::key(char32_t cp, cc::FontRasterMode mode, int32_t requested) const
{
    return {_bytes, glyph(cp), mode, selectRasterPpem(mode, requested)};
}
}  // namespace cc::font
