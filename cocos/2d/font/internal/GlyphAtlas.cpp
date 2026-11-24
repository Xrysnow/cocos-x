#include "GlyphAtlas.h"
#include "renderer/Renderer.h"
#include <algorithm>
#include <cstring>

namespace cc::font
{
bool AtlasPage::allocate(int w, int h, AtlasRect& out)
{
    auto best = free.end();
    for (auto it = free.begin(); it != free.end(); ++it)
        if (it->w >= w && it->h >= h && (best == free.end() || it->w * it->h < best->w * best->h))
            best = it;
    if (best == free.end())
        return false;
    const auto rect = *best;
    free.erase(best);
    out = {rect.x, rect.y, w, h};
    if (rect.w > w)
        free.push_back({rect.x + w, rect.y, rect.w - w, h});
    if (rect.h > h)
        free.push_back({rect.x, rect.y + h, rect.w, rect.h - h});
    ++used;
    return true;
}
void AtlasPage::release(AtlasRect rect)
{
    --used;
    if (!used)
    {
        free = {{0, 0, 2048, 2048}};
        return;
    }
    for (size_t i = 0; i < free.size();)
    {
        const auto r = free[i];
        if (r.y == rect.y && r.h == rect.h && (r.x + r.w == rect.x || rect.x + rect.w == r.x))
        {
            rect.x  = std::min(rect.x, r.x);
            rect.w += r.w;
        }
        else if (r.x == rect.x && r.w == rect.w && (r.y + r.h == rect.y || rect.y + rect.h == r.y))
        {
            rect.y  = std::min(rect.y, r.y);
            rect.h += r.h;
        }
        else
        {
            ++i;
            continue;
        }
        free.erase(free.begin() + i);
        i = 0;
    }
    free.push_back(rect);
}
GlyphAtlas::Entries::iterator GlyphAtlas::evict(Entries::iterator it)
{
    if (it->second->page)
        it->second->page->release(it->second->rect);
    ++_evictions;
    return _entries.erase(it);
}
GlyphAtlas::Lease GlyphAtlas::find(const GlyphKey& key)
{
    auto it = _entries.find(key);
    if (it == _entries.end() || *it->second->publication == cc::GlyphStatus::UploadError)
        return {};
    it->second->lastUse = std::chrono::steady_clock::now();
    return it->second;
}
void GlyphAtlas::retireEmpty(Renderer& renderer)
{
    std::erase_if(_pages, [&](auto& p) {
        if (p->used)
            return false;
        const size_t bytes = (p->rgba ? 4u : 1u) * 2048 * 2048;
        ++_retirement->count;
        _retirement->bytes += bytes;
        renderer.retireTexture(std::move(p->texture), [r = _retirement, bytes] {
            --r->count;
            r->bytes -= bytes;
        });
        return true;
    });
}
void GlyphAtlas::collect(Renderer& renderer, std::chrono::milliseconds ttl)
{
    auto now = std::chrono::steady_clock::now();
    for (auto it = _entries.begin(); it != _entries.end();)
        if (it->second.use_count() == 1 &&
            (*it->second->publication == cc::GlyphStatus::UploadError ||
             std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second->lastUse) >= ttl))
            it = evict(it);
        else
            ++it;
    retireEmpty(renderer);
}
bool GlyphAtlas::reduceTo(Renderer& renderer, size_t limit)
{
    if (_pages.size() + _retirement->count <= limit)
        return true;
    // A page can be retired only when every live slot is unleased.
    std::map<AtlasPage*, std::chrono::steady_clock::time_point> cold;
    for (auto& page : _pages)
        cold.emplace(page.get(), std::chrono::steady_clock::time_point{});
    for (auto& [key, slot] : _entries)
    {
        auto page = cold.find(slot->page.get());
        if (page == cold.end())
            continue;
        if (slot.use_count() > 1)
            cold.erase(page);
        else
            page->second = std::max(page->second, slot->lastUse);
    }
    const size_t needed = _pages.size() > limit ? _pages.size() - limit : 0;
    if (cold.size() < needed)
        return false;
    for (size_t n = 0; n < needed; ++n)
    {
        const auto chosen =
            std::min_element(cold.begin(), cold.end(), [](auto& a, auto& b) { return a.second < b.second; });
        for (auto it = _entries.begin(); it != _entries.end();)
            if (it->second->page.get() == chosen->first)
                it = evict(it);
            else
                ++it;
        cold.erase(chosen);
    }
    retireEmpty(renderer);
    return _pages.size() + _retirement->count <= limit;
}
void GlyphAtlas::invalidate()
{
    _entries.clear();
    _pages.clear();
}
void GlyphAtlas::stats(FontCacheStats& s) const
{
    s.livePages      = uint32_t(_pages.size());
    s.retiringPages  = _retirement->count;
    s.evictions      = _evictions;
    s.capacityMisses = _misses;
    s.textureBytes   = _retirement->bytes;
    for (const auto& p : _pages)
        s.textureBytes += (p->rgba ? 4u : 1u) * 2048 * 2048;
}
cc::GlyphStatus GlyphAtlas::publish(
    Renderer& renderer,
    const GlyphKey& key,
    GlyphImage&& image,
    const FontCacheConfig& config,
    std::shared_ptr<void> staging)
{
    using Status = cc::GlyphStatus;
    if (find(key))
        return Status::Ready;
    if (auto it = _entries.find(key); it != _entries.end())
    {
        if (it->second.use_count() > 1)
            return Status::Busy;
        evict(it);
    }
    auto slot = std::make_shared<GlyphSlot>();
    if (!image.width || !image.height)
    {
        _entries.emplace(key, slot);
        return Status::Ready;
    }
    if (!renderer.isFrameActive() || renderer.isRendering())
        return Status::DeviceUnavailable;
    const int w = int(image.width) + 2, h = int(image.height) + 2;
    if (w > 2048 || h > 2048)
        return Status::TooLarge;
    const bool rgba = image.encoding == RasterEncoding::Msdf;
    auto allocate   = [&] {
        for (auto& p : _pages)
            if (p->rgba == rgba && p->allocate(w, h, slot->rect))
            {
                slot->page = p;
                return true;
            }
        return false;
    };
    while (!allocate())
    {
        if (_pages.size() + _retirement->count < config.maxPages)
        {
            auto page  = std::make_shared<AtlasPage>();
            page->rgba = rgba;
            backend::TextureDescriptor desc;
            desc.width = desc.height = 2048;
            desc.textureFormat       = rgba ? backend::PixelFormat::RGBA8 : backend::PixelFormat::A8;
            desc.samplerDescriptor   = {
                backend::SamplerFilter::LINEAR,
                backend::SamplerFilter::LINEAR,
                backend::SamplerAddressMode::CLAMP_TO_EDGE,
                backend::SamplerAddressMode::CLAMP_TO_EDGE};
            page->texture = cc::IntrusivePtr{new Texture2D()};
            if (!page->texture->updateTextureDescriptor(desc))
                return Status::UploadError;
            page->texture->setMaxS(1);
            page->texture->setMaxT(1);
            _pages.push_back(std::move(page));
            continue;
        }
        auto oldest = _entries.end();
        for (auto it = _entries.begin(); it != _entries.end(); ++it)
            if (it->second.use_count() == 1 && it->second->page &&
                (oldest == _entries.end() || it->second->lastUse < oldest->second->lastUse))
                oldest = it;
        if (oldest == _entries.end())
        {
            retireEmpty(renderer);
            ++_misses;
            return Status::CacheFull;
        }
        evict(oldest);
        // Changing page format also passes through the native retirement budget.
        if (std::any_of(_pages.begin(), _pages.end(), [&](auto& p) { return !p->used && p->rgba != rgba; }))
            retireEmpty(renderer);
    }
    slot->left          = image.leftPx;
    slot->top           = image.topPx;
    slot->range         = image.distanceRangePx;
    *slot->publication  = Status::Pending;
    const bool accepted = renderer.queueTextureUpload(
        slot->page->texture->getBackendTexture(),
        slot->rect.x,
        slot->rect.y,
        w,
        h,
        std::move(image.pixels),
        slot,
        [published = slot->publication, staging = std::move(staging)](bool ok) {
            *published = ok ? Status::Ready : Status::UploadError;
        });
    if (!accepted)
    {
        slot->page->release(slot->rect);
        return Status::UploadError;
    }
    _entries.emplace(key, std::move(slot));
    return Status::Ready;
}
}  // namespace cc::font
