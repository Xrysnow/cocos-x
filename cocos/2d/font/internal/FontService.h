#pragma once
#include "GlyphAtlas.h"
#include <set>

namespace cc::font
{
class FontService
{
public:
    FontService();
    ~FontService();
    FontCacheConfig config;
    std::shared_ptr<FontFace> face(std::string_view name, cc::GlyphStatus& status);
    std::shared_ptr<FontFace> face(std::span<const uint8_t> data, cc::GlyphStatus& status);
    GlyphTicket submit(const std::vector<GlyphKey>&, Priority);
    static GlyphTicket failure(cc::GlyphStatus);
    cc::GlyphStatus prepare(Renderer&, const std::vector<GlyphKey>&, bool allowPartial = false);
    GlyphAtlas::Lease resolve(const GlyphKey& key) { return _atlas.find(key); }
    GlyphAtlas::Lease lookupRequest(const GlyphKey& key)
    {
        auto slot = _atlas.find(key);
        if (slot && *slot->publication == GlyphStatus::Ready)
            ++_hits;
        return slot;
    }
    void frame(Renderer&, bool canDraw);
    void trim(Renderer&);
    void finishFrame() { _framePins.clear(); }
    void invalidate();
    cc::GlyphStatus configure(const FontCacheConfig&);
    FontCacheStats stats() const;
    FontUploadStats uploadStats() const { return _atlas.uploads(); }

private:
    std::set<GlyphAtlas::Lease> _framePins;
    GlyphAtlas _atlas;
    GlyphScheduler _scheduler;
    std::map<std::string, std::shared_ptr<FontFace>, std::less<>> _faces;
    std::vector<std::weak_ptr<FontFace>> _memoryFaces;
    std::map<GlyphKey, std::shared_ptr<Demand>> _pending;
    std::map<GlyphKey, std::weak_ptr<Demand>> _deferred;
    struct Failure
    {
        GlyphStatus status;
        std::chrono::steady_clock::time_point retry;
    };
    std::map<GlyphKey, Failure> _failures;
    uint64_t _hits{}, _dedup{};
    bool enqueue(const std::shared_ptr<Demand>&, Priority);
    void dispatchDeferred();
    void publish(Renderer&, GlyphScheduler::Result&);
    void prune();
};
}  // namespace cc::font
