#pragma once
#include "raster/GlyphRasterizer.h"

namespace cc::font
{
// Converts an owning CPU image into one tightly packed, guarded GPU transfer.
// The bearings and dimensions continue to describe the unguarded glyph.
void prepareUpload(GlyphImage&);
}  // namespace cc::font
