#pragma once
#include "GlyphScheduler.h"

namespace cc
{
class Renderer;
}
namespace cc::font
{
struct AtlasRect
{
    int x{}, y{}, w{}, h{};
};
struct AtlasPage
{
    cc::IntrusivePtr<Texture2D> texture;
    bool rgba{};
    std::vector<AtlasRect> free{{0, 0, 2048, 2048}};
    size_t used{};
    bool allocate(int w, int h, AtlasRect&);
    void release(AtlasRect);
};
struct GlyphSlot
{
    std::shared_ptr<AtlasPage> page;
    AtlasRect rect;  // includes the one-texel guard
    int left{}, top{};
    float range{};
    std::vector<std::weak_ptr<std::function<void()>>> bindings;
    ~GlyphSlot()
    {
        for (auto& b : bindings)
            if (auto callback = b.lock())
                (*callback)();
    }
    std::shared_ptr<GlyphStatus> publication = std::make_shared<GlyphStatus>(GlyphStatus::Ready);
    std::chrono::steady_clock::time_point lastUse{std::chrono::steady_clock::now()};
};

class GlyphAtlas
{
public:
    using Lease = std::shared_ptr<GlyphSlot>;
    Lease find(const GlyphKey&);
    cc::GlyphStatus publish(
        Renderer&, const GlyphKey&, GlyphImage&&, const FontCacheConfig&, std::shared_ptr<void> staging);
    void collect(Renderer&, std::chrono::milliseconds ttl);
    void stats(FontCacheStats&) const;
    FontUploadStats uploads() const { return _account->uploads; }
    bool reduceTo(Renderer&, size_t pages);
    void invalidate();

private:
    using Entries = std::map<GlyphKey, Lease>;
    Entries _entries;
    std::vector<std::shared_ptr<AtlasPage>> _pages;
    struct Accounting
    {
        uint32_t retiringPages{};
        size_t retiringBytes{};
        FontUploadStats uploads;
    };
    std::shared_ptr<Accounting> _account = std::make_shared<Accounting>();
    uint64_t _evictions{}, _misses{};
    Entries::iterator evict(Entries::iterator);
    void retireEmpty(Renderer&);
};
}  // namespace cc::font
