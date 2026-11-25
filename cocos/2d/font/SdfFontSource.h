#pragma once

#include "FontTypes.h"
#include "platform/PlatformMacros.h"
#include <cstdint>
#include <memory>
#include <span>
#include <vector>

namespace cc
{
class Texture2D;
struct SdfGlyphBounds
{
    int left{}, top{}, width{}, height{};
};
struct SdfGlyphView
{
    std::shared_ptr<void> lease;
    Texture2D* texture{};
    float u0{}, v0{}, u1{}, v1{};
};

// Query metrics on the engine thread. Prepare visible glyphs before executing
// the render queue, then keep each returned slot lease with its draw submission.
class CC_DLL SdfFontSource
{
public:
    // rasterPpem is an explicit SDF tier in whole pixels per em (32, 48 or 64).
    // Returns an empty pointer for an unsupported tier or font.
    static std::shared_ptr<SdfFontSource> open(std::span<const uint8_t> data, int rasterPpem);
    ~SdfFontSource();
    int rasterPpem() const;
    int ascentUnits() const;
    int descentUnits() const;
    int unitsPerEm() const;
    uint32_t glyphCount() const;
    uint32_t glyphIndex(char32_t codepoint) const;
    bool advance(uint32_t glyph, float& units) const;
    bool bounds(uint32_t glyph, SdfGlyphBounds& out) const;
    bool bitmap(uint32_t glyph, int ppem26_6, SdfGlyphBounds& out, std::vector<uint8_t>& pixels) const;
    struct Request
    {
        const SdfFontSource* font;
        uint32_t glyph;
    };
    static void prepare(std::span<const Request> glyphs, std::span<SdfGlyphView> views);

private:
    struct Impl;
    explicit SdfFontSource(std::unique_ptr<Impl> impl);
    std::unique_ptr<Impl> _impl;
};
}  // namespace cc
