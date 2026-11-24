#pragma once
#include "../FontRendering.h"
#include "raster/GlyphRasterizer.h"
#include "2d/FontAtlas.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

namespace cc::font
{
struct GlyphKey
{
    std::shared_ptr<const FontBytes> bytes;
    uint32_t glyph{};
    FontRasterMode mode{};
    int32_t ppem{};
    auto operator<=>(const GlyphKey&) const = default;
};

// Its FreeType face belongs only to the engine thread. Workers receive only bytes.
class FontFace
{
public:
    ~FontFace();
    cc::GlyphStatus open(std::string_view name);
    bool setSize(int32_t size);
    FontMetrics metrics() const;
    uint32_t glyph(char32_t cp) const;
    FontLetterDefinition measure(char32_t cp, float contentScale);
    int kerning(uint32_t first, uint32_t second);
    bool sourceIdle() const { return _bytes.use_count() == 1; }
    GlyphKey key(char32_t cp, cc::FontRasterMode mode, int32_t requested) const;

private:
    FT_Library _library{};
    FT_Face _face{};
    std::shared_ptr<const FontBytes> _bytes;
    int32_t _size{};
    std::map<std::pair<int32_t, uint32_t>, FontLetterDefinition> _measurements;
    std::map<std::tuple<int32_t, uint32_t, uint32_t>, int> _kernings;
    mutable std::map<char32_t, uint32_t> _characters;
};
int32_t requestedPpem(float points, float scale);
}  // namespace cc::font
