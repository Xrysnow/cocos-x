#pragma once

#include "platform/PlatformMacros.h"
#include "FontTypes.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace cc
{
struct FontConfig
{
    std::string name;
    float size{12};
};
struct FontMetrics
{
    float ascent{}, descent{}, lineHeight{};
};
struct FontCacheConfig
{
    uint32_t maxPages{4};
    std::chrono::milliseconds glyphIdleTime{30000};
    uint32_t workerCount{2}, maxPendingGlyphs{4096};
    size_t maxStagingBytes{32u << 20}, uploadBytesPerFrame{2u << 20};
};
struct FontCacheStats
{
    uint32_t livePages{}, retiringPages{}, queuedGlyphs{}, runningGlyphs{};
    size_t textureBytes{}, stagingBytes{};
    uint64_t cacheHits{}, deduplicatedRequests{}, evictions{}, capacityMisses{};
};
struct FontUploadStats
{
    uint64_t glyphs{}, bytes{}; // Successfully encoded glyph rectangles, including guard texels.
};
struct GlyphProgress
{
    GlyphStatus status{GlyphStatus::Ready};
    uint32_t total{}, ready{}, failed{};
};

namespace font
{
class FontService;
}
class CC_DLL GlyphTicket
{
public:
    GlyphTicket() = default;
    GlyphProgress poll() const;
    void cancel();

private:
    struct State;
    std::shared_ptr<State> _state;
    friend class font::FontService;
};

class CC_DLL FontRendering
{
public:
    static FontRendering& getInstance();
    GlyphStatus inspectFont(std::string_view name) const;
    FontCacheConfig getConfig() const;
    GlyphStatus configure(const FontCacheConfig&);
    GlyphStatus setWorkerCount(uint32_t count);
    FontCacheStats getStats() const;
    FontUploadStats getUploadStats() const;
    void trim();

private:
    FontRendering();
    ~FontRendering();
    std::unique_ptr<font::FontService> _service;
    friend class Director;
    friend class Label;
    friend class SdfFontSource;
};
}  // namespace cc
