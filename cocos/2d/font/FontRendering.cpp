#include "FontRendering.h"
#include "internal/FontService.h"
#include "base/Director.h"
#include "renderer/Renderer.h"

namespace cc
{
struct GlyphTicket::State
{
    std::vector<std::shared_ptr<font::Demand>> demands;
    GlyphStatus status{GlyphStatus::Ready};
    uint32_t cancelledCount{};
};
GlyphProgress GlyphTicket::poll() const
{
    if (!_state)
        return {};
    GlyphProgress p{_state->status, uint32_t(_state->demands.size()) + _state->cancelledCount};
    for (const auto& d : _state->demands)
    {
        const auto status = d->publication ? *d->publication : d->status;
        if (status == GlyphStatus::Ready)
            ++p.ready;
        else if (status != GlyphStatus::Pending)
        {
            if (!p.failed)
                p.status = status;
            ++p.failed;
        }
    }
    if (!p.failed && p.status == GlyphStatus::Ready && p.ready != p.total)
        p.status = GlyphStatus::Pending;
    return p;
}
void GlyphTicket::cancel()
{
    if (_state && poll().status == GlyphStatus::Pending)
    {
        _state->cancelledCount = uint32_t(_state->demands.size());
        _state->demands.clear();
        _state->status = GlyphStatus::Cancelled;
    }
}

FontRendering::FontRendering() : _service(std::make_unique<font::FontService>())
{
}
FontRendering::~FontRendering() = default;
FontRendering& FontRendering::getInstance()
{
    return Director::getInstance()->getFontRendering();
}
GlyphStatus FontRendering::inspectFont(std::string_view name) const
{
    GlyphStatus status;
    _service->face(name, status);
    return status;
}
FontCacheConfig FontRendering::getConfig() const
{
    return _service->config;
}
GlyphStatus FontRendering::configure(const FontCacheConfig& c)
{
    return _service->configure(c);
}
GlyphStatus FontRendering::setWorkerCount(uint32_t n)
{
    auto c        = getConfig();
    c.workerCount = n;
    return configure(c);
}
FontCacheStats FontRendering::getStats() const
{
    return _service->stats();
}
void FontRendering::trim()
{
    _service->trim(*Director::getInstance()->getRenderer());
}

namespace font
{
using Status = cc::GlyphStatus;
FontService::FontService()
{
    if (!_scheduler.configure(config))
        config.workerCount = 0;
}
FontService::~FontService()
{
    invalidate();
}
void FontService::invalidate()
{
    for (auto& [key, d] : _pending)
    {
        d->cancelled->store(true);
        d->status = Status::Cancelled;
    }
    for (auto& [key, w] : _deferred)
        if (auto d = w.lock())
            d->status = Status::Cancelled;
    _deferred.clear();
    _failures.clear();
    _pending.clear();
    _framePins.clear();
    _atlas.invalidate();
}
std::shared_ptr<FontFace> FontService::face(std::string_view name, Status& status)
{
    status = Status::Ready;
    if (auto it = _faces.find(name); it != _faces.end())
        return it->second;
    auto face = std::make_shared<FontFace>();
    status    = face->open(name);
    if (status != Status::Ready)
        return {};
    if (_faces.size() >= 32)
        std::erase_if(
            _faces, [](const auto& item) { return item.second.use_count() == 1 && item.second->sourceIdle(); });
    _faces.emplace(name, face);
    return face;
}
FontCacheStats FontService::stats() const
{
    FontCacheStats stats;
    _scheduler.stats(stats);
    _atlas.stats(stats);
    stats.cacheHits            = _hits;
    stats.deduplicatedRequests = _dedup;
    return stats;
}
Status FontService::configure(const FontCacheConfig& c)
{
    if (!c.maxPages || !c.workerCount || !c.maxPendingGlyphs || !c.maxStagingBytes || !c.uploadBytesPerFrame ||
        c.glyphIdleTime.count() < 0)
        return Status::InvalidInput;
    const auto s = stats();
    if (((s.queuedGlyphs || s.runningGlyphs) && c.workerCount != config.workerCount) ||
        s.stagingBytes > c.maxStagingBytes || s.queuedGlyphs + s.runningGlyphs > c.maxPendingGlyphs)
        return Status::Busy;
    if (s.livePages + s.retiringPages > c.maxPages &&
        !_atlas.reduceTo(*Director::getInstance()->getRenderer(), c.maxPages))
        return Status::Busy;
    if (!_scheduler.configure(c))
        return Status::Busy;
    _failures.clear();
    config = c;
    return Status::Ready;
}
void FontService::prune()
{
    std::erase_if(_deferred, [](const auto& p) { return p.second.expired(); });
    std::erase_if(_pending, [](auto& p) {
        if (p.second.use_count() > 1)
            return false;
        p.second->cancelled->store(true);
        return true;
    });
}
bool FontService::enqueue(const std::shared_ptr<Demand>& d, Priority p)
{
    const size_t limit = config.maxPendingGlyphs - (p == Priority::Prefetch ? config.maxPendingGlyphs / 8 : 0);
    if (_pending.size() >= limit || !_scheduler.submit(d, p, limit))
        return false;
    _pending[d->key] = d;
    return true;
}
void FontService::dispatchDeferred()
{
    for (auto it = _deferred.begin(); it != _deferred.end();)
    {
        auto d = it->second.lock();
        if (!d || enqueue(d, d->priority))
            it = _deferred.erase(it);
        else
            ++it;
    }
}
GlyphTicket FontService::failure(Status status)
{
    GlyphTicket ticket;
    ticket._state         = std::make_shared<GlyphTicket::State>();
    ticket._state->status = status;
    return ticket;
}
GlyphTicket FontService::submit(const std::vector<GlyphKey>& keys, Priority priority)
{
    auto ticket = failure(Status::Ready);
    std::set<GlyphKey> seen;
    if (priority == Priority::Prefetch && keys.size() > config.maxPendingGlyphs)
    {
        for (auto& key : keys)
            if (seen.insert(key).second && seen.size() > config.maxPendingGlyphs)
                return failure(Status::Busy);
        seen.clear();
    }
    for (const auto& key : keys)
    {
        if (!seen.insert(key).second)
            continue;
        auto& d = ticket._state->demands.emplace_back();
        if (auto slot = _atlas.find(key))
        {
            ++_hits;
            d              = std::make_shared<Demand>(key);
            d->status      = Status::Ready;
            d->publication = slot->publication;
            continue;
        }
        auto it = _pending.find(key);
        if (it != _pending.end())
        {
            d = it->second;
            ++_dedup;
            _scheduler.promote(*d, priority);
            continue;
        }
        if (auto it = _deferred.find(key); it != _deferred.end() && (d = it->second.lock()))
        {
            ++_dedup;
            d->priority = std::min(priority, d->priority);
            if (priority != Priority::Prefetch && enqueue(d, priority))
                _deferred.erase(it);
            continue;
        }
        d           = std::make_shared<Demand>(key);
        d->priority = priority;
        if (auto it = _failures.find(key); it != _failures.end())
        {
            const auto forever = std::chrono::steady_clock::time_point::max();
            if (it->second.retry == forever ||
                (priority != Priority::Sync && std::chrono::steady_clock::now() < it->second.retry))
            {
                d->status = it->second.status;
                continue;
            }
            _failures.erase(it);
        }
        if (_pending.size() >= config.maxPendingGlyphs || _deferred.size() >= config.maxPendingGlyphs)
            prune();
        if (config.workerCount && enqueue(d, priority))
            continue;
        if (config.workerCount && priority == Priority::Prefetch && _deferred.size() < config.maxPendingGlyphs)
            _deferred[key] = d;
        else
            d->status = Status::Busy;
    }
    return ticket;
}
void FontService::publish(Renderer& renderer, GlyphScheduler::Result& r)
{
    auto demand = r.demand.lock();
    if (!demand || demand->status != Status::Pending)
        return;
    demand->status = r.raster.status;
    if (demand->status == Status::Ready)
        demand->status = _atlas.publish(renderer, demand->key, std::move(r.raster.image), config, std::move(r.staging));
    if (demand->status == Status::Ready)
        demand->publication = _atlas.find(demand->key)->publication;
    else if (demand->status != Status::Cancelled)
    {
        const bool permanent = demand->status == Status::TooLarge || demand->status == Status::InvalidInput ||
                               demand->status == Status::UnsupportedFont ||
                               demand->status == Status::UnsupportedColorFont;
        if (_failures.size() >= config.maxPendingGlyphs)
            _failures.erase(_failures.begin());
        _failures[demand->key] = {
            demand->status,
            permanent ? std::chrono::steady_clock::time_point::max()
                      : std::chrono::steady_clock::now() + std::chrono::milliseconds(100)};
    }
    _pending.erase(demand->key);
}
void FontService::frame(Renderer& renderer, bool canDraw)
{
    _atlas.collect(renderer, config.glyphIdleTime);
    prune();
    dispatchDeferred();
    if (!canDraw)
        return;
    size_t bytes = 0;
    GlyphScheduler::Result r;
    while (bytes < config.uploadBytesPerFrame &&
           _scheduler.take(r, false, bytes ? config.uploadBytesPerFrame - bytes : SIZE_MAX))
    {
        bytes += r.raster.image.pixels.size();
        publish(renderer, r);
    }
}
void FontService::trim(Renderer& renderer)
{
    _atlas.collect(renderer, std::chrono::milliseconds(0));
    prune();
}
Status FontService::prepare(Renderer& renderer, const std::vector<GlyphKey>& keys)
{
    std::set<GlyphAtlas::Lease> pins;
    if (keys.empty())
        return Status::Ready;
    if (renderer.isRendering())
        return Status::Busy;
    if (!renderer.isFrameActive())
        return Status::DeviceUnavailable;
    auto ticket = submit(keys, Priority::Sync);
    for (auto& d : ticket._state->demands)
        if (d->status == Status::Ready)
            pins.insert(_atlas.find(d->key));
    GlyphScheduler::Result result;
    const auto& demands = ticket._state->demands;
    auto waiting        = demands.begin();
    while ((waiting = std::find_if(waiting, demands.end(), [](const auto& d) { return d->status != Status::Ready; })) !=
               demands.end() &&
           (*waiting)->status == Status::Pending)
    {
        if (!_scheduler.take(result, false))
        {
            if (!renderer.flushTextureUploads())
                return Status::UploadError;
            if (!_scheduler.take(result, true))
                break;
        }
        publish(renderer, result);
        result = {};
        dispatchDeferred();
    }
    auto status = waiting == demands.end() ? Status::Ready : (*waiting)->status;
    if (status == Status::Ready)
        for (auto& d : ticket._state->demands)
        {
            auto slot = _atlas.find(d->key);
            if (!slot)
            {
                pins.clear();
                return Status::CacheFull;
            }
            pins.insert(std::move(slot));
        }
    if (status == Status::Ready)
    {
        // A synchronous caller can capture the Label immediately. Finish encoding
        // its last upload batch here and report any transfer failure to that caller.
        if (ticket.poll().status == Status::Pending)
            renderer.flushTextureUploads();
        status = ticket.poll().status;
        if (status == Status::Ready)
            _framePins.merge(pins);
    }
    return status == Status::Pending ? Status::Busy : status;
}
}  // namespace font
}  // namespace cc
