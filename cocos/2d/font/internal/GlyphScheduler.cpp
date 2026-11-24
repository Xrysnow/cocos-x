#include "GlyphScheduler.h"
#include "GlyphUpload.h"
#include <algorithm>

namespace cc::font
{
// Credits follow the packed pixels through the completion queue and the renderer
// upload prefix. The renderer can outlive the scheduler during Director shutdown.
struct GlyphScheduler::Budget
{
    std::mutex mutex;
    std::condition_variable changed;
    size_t used{}, limit{32u << 20};
    bool stopping{};
    struct Reservation
    {
        std::shared_ptr<Budget> account;
        size_t bytes{};
        ~Reservation()
        {
            {
                std::lock_guard lock(account->mutex);
                account->used -= bytes;
            }
            account->changed.notify_all();
        }
    };
};
GlyphScheduler::GlyphScheduler() : _budget(std::make_shared<Budget>())
{
}
GlyphScheduler::~GlyphScheduler()
{
    {
        std::lock_guard lock(_mutex);
        for (auto& w : _workers)
            w.quit->store(true);
        for (auto& flag : _active)
            flag->store(true);
    }
    {
        std::lock_guard lock(_budget->mutex);
        _budget->stopping = true;
    }
    _budget->changed.notify_all();
    _changed.notify_all();
    for (auto& w : _workers)
        w.thread.join();
}

bool GlyphScheduler::configure(const FontCacheConfig& config)
{
    const auto n = config.workerCount;
    if (n == 0)
        return false;
    std::unique_lock lock(_mutex);
    const size_t old = _workers.size();
    std::unique_lock credits(_budget->mutex);
    if (_budget->used > config.maxStagingBytes || _jobs.size() + _running + _results.size() > config.maxPendingGlyphs ||
        (old != n && (!_jobs.empty() || _running)))
        return false;
    size_t target = n;
    try
    {
        _workers.reserve(n);
        while (_workers.size() < n)
        {
            auto quit = std::make_shared<std::atomic_bool>(false);
            _workers.push_back({quit, std::thread(&GlyphScheduler::run, this, quit)});
        }
    }
    catch (const std::exception&)
    {
        target = old;
    }
    while (_workers.size() > target)
    {
        auto worker = std::move(_workers.back());
        _workers.pop_back();
        worker.quit->store(true);
        lock.unlock();
        _changed.notify_all();
        worker.thread.join();
        lock.lock();
    }
    if (_workers.size() != n)
        return false;
    _budget->limit = config.maxStagingBytes;
    credits.unlock();
    _budget->changed.notify_all();
    return true;
}
bool GlyphScheduler::submit(const std::shared_ptr<Demand>& demand, Priority p, size_t limit)
{
    {
        std::lock_guard lock(_mutex);
        if (_jobs.size() + _running + _results.size() >= limit)
        {
            std::erase_if(_jobs, [](auto& job) { return job.demand.expired(); });
            std::erase_if(_results, [](const auto& r) { return r.demand.expired(); });
            if (_jobs.size() + _running + _results.size() >= limit)
                return false;
        }
        _jobs.push_back({demand, demand->key, p, std::chrono::steady_clock::now(), demand->cancelled});
    }
    _changed.notify_all();
    return true;
}
void GlyphScheduler::promote(const Demand& demand, Priority p)
{
    std::lock_guard lock(_mutex);
    for (auto& job : _jobs)
        if (job.key == demand.key)
            job.priority = std::min(job.priority, p);
}
void GlyphScheduler::stats(FontCacheStats& s) const
{
    std::lock_guard lock(_mutex);
    s.queuedGlyphs  = uint32_t(_jobs.size());
    s.runningGlyphs = _running;
    std::lock_guard credits(_budget->mutex);
    s.stagingBytes = _budget->used;
}
bool GlyphScheduler::take(Result& out, bool wait, size_t maxBytes)
{
    std::unique_lock lock(_mutex);
    if (wait)
        _changed.wait(lock, [&] { return !_results.empty() || (!_running && _jobs.empty()); });
    if (_results.empty() || _results.front().raster.image.pixels.size() > maxBytes)
        return false;
    out = std::move(_results.front());
    _results.pop_front();
    lock.unlock();
    _changed.notify_all();
    return true;
}
void GlyphScheduler::run(std::shared_ptr<std::atomic_bool> quit)
{
    RasterContext context;
    BitmapRasterizer bitmap;
    SdfRasterizer sdf;
    MsdfRasterizer msdf;
    for (;;)
    {
        std::unique_lock lock(_mutex);
        _changed.wait(lock, [&] { return quit->load() || !_jobs.empty(); });
        if (quit->load())
            return;
        const auto it = std::min_element(_jobs.begin(), _jobs.end(), [](const Job& a, const Job& b) {
            // Bound starvation even when a foreground stream never empties.
            auto deadline = [](const Job& j) { return j.queued + std::chrono::milliseconds(100 * int(j.priority)); };
            return deadline(a) < deadline(b);
        });
        auto job      = std::move(*it);
        _jobs.erase(it);
        if (job.demand.expired())
        {
            _changed.notify_all();
            continue;
        }
        ++_running;
        _active.push_back(job.cancel);
        lock.unlock();
        const GlyphRasterizer* raster = &bitmap;
        if (job.key.mode == FontRasterMode::Sdf)
            raster = &sdf;
        if (job.key.mode == FontRasterMode::Msdf)
            raster = &msdf;
        auto result = raster->rasterize(context, {job.key.bytes, job.key.glyph, job.key.ppem, job.cancel.get()});
        std::shared_ptr<Budget::Reservation> reservation;
        if (result.status == GlyphStatus::Ready && !result.image.pixels.empty())
        {
            try
            {
                prepareUpload(result.image);
                const size_t bytes = result.image.pixels.size();
                std::unique_lock credits(_budget->mutex);
                _budget->changed.wait(credits, [&] {
                    return _budget->stopping || bytes > _budget->limit || _budget->used <= _budget->limit - bytes;
                });
                if (bytes > _budget->limit || quit->load())
                    result = {GlyphStatus::TooLarge};
                else
                {
                    reservation           = std::make_shared<Budget::Reservation>();
                    reservation->account  = _budget;
                    reservation->bytes    = bytes;
                    _budget->used        += bytes;
                }
            }
            catch (const std::bad_alloc&)
            {
                result = {GlyphStatus::TooLarge};
            }
        }
        lock.lock();
        --_running;
        std::erase(_active, job.cancel);
        if (quit->load())
            return;
        if (!job.demand.expired())
        {
            _results.push_back({std::move(job.demand), std::move(result), std::move(reservation)});
        }
        lock.unlock();
        _changed.notify_all();
    }
}
}  // namespace cc::font
