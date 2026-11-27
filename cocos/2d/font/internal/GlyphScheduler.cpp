#include "GlyphScheduler.h"
#include "GlyphUpload.h"
#include <algorithm>
#include <iterator>
#include <list>

namespace cc::font
{
// Credits follow the packed pixels through the completion queue and the renderer
// upload prefix. The renderer can outlive the scheduler during Director shutdown.
struct GlyphScheduler::Budget
{
    std::mutex mutex;
    size_t used{}, limit{32u << 20};
    bool stopping{};

    enum class WaitState
    {
        Pending,
        Granted,
        Rejected
    };
    struct Waiter
    {
        size_t bytes;
        unsigned bypasses{};
        WaitState state{WaitState::Pending};
        std::condition_variable ready;
    };
    static constexpr unsigned maxBypasses = 8;
    std::list<Waiter*> waiters;

    // All queue and credit changes use mutex. Notifying under it keeps the
    // worker's stack-allocated waiter alive through the notification.
    void finishWaiter(std::list<Waiter*>::iterator position, WaitState state)
    {
        auto& waiter = **position;
        waiters.erase(position);
        waiter.state = state;
        waiter.ready.notify_one();
    }

    void grantWaiters()
    {
        while (!waiters.empty())
        {
            const size_t free = limit - used;
            auto selected = waiters.begin();
            auto& oldest = **selected;
            if (oldest.bytes > free)
            {
                // Accumulate credit for the oldest request after bounded bypass.
                if (oldest.bypasses == maxBypasses)
                    return;
                selected = std::find_if(std::next(selected), waiters.end(),
                                        [free](const Waiter* waiter) { return waiter->bytes <= free; });
                if (selected == waiters.end())
                    return;
                ++oldest.bypasses;
            }
            used += (*selected)->bytes;
            finishWaiter(selected, WaitState::Granted);
        }
    }

    bool acquire(std::unique_lock<std::mutex>& lock, size_t bytes)
    {
        if (stopping || bytes > limit)
            return false;
        // Any previously admissible waiter was granted on the last release or resize.
        if (bytes <= limit - used && (waiters.empty() || waiters.front()->bypasses < maxBypasses))
        {
            if (!waiters.empty())
                ++waiters.front()->bypasses;
            used += bytes;
            return true;
        }
        Waiter waiter{bytes};
        waiters.push_back(&waiter);
        waiter.ready.wait(lock, [&] { return waiter.state != WaitState::Pending; });
        return waiter.state == WaitState::Granted;
    }

    void release(size_t bytes)
    {
        std::lock_guard lock(mutex);
        used -= bytes;
        grantWaiters();
    }

    void resize(size_t bytes)  // mutex held
    {
        limit = bytes;
        for (auto it = waiters.begin(); it != waiters.end();)
        {
            const auto current = it++;
            if ((*current)->bytes > limit)
                finishWaiter(current, WaitState::Rejected);
        }
        grantWaiters();
    }

    void stop()
    {
        std::lock_guard lock(mutex);
        stopping = true;
        while (!waiters.empty())
            finishWaiter(waiters.begin(), WaitState::Rejected);
    }

    struct Reservation
    {
        std::shared_ptr<Budget> account;
        size_t bytes{};
        ~Reservation()
        {
            if (bytes)
                account->release(bytes);
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
    _budget->stop();
    _workAvailable.notify_all();
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
        _workAvailable.notify_all();
        worker.thread.join();
        lock.lock();
    }
    if (_workers.size() != n)
        return false;
    _budget->resize(config.maxStagingBytes);
    return true;
}
bool GlyphScheduler::submit(const std::shared_ptr<Demand>& demand, Priority p, size_t limit)
{
    {
        std::unique_lock lock(_mutex);
        if (_jobs.size() + _running + _results.size() >= limit)
        {
            std::erase_if(_jobs, [](auto& job) { return job.demand.expired(); });
            std::erase_if(_results, [](const auto& r) { return r.demand.expired(); });
            if (_jobs.size() + _running + _results.size() >= limit)
            {
                const bool drained = idle();
                lock.unlock();
                if (drained)
                    _resultsChanged.notify_all();
                return false;
            }
        }
        _jobs.insert(_jobs.end(), {demand, demand->key, p, std::chrono::steady_clock::now(), _nextSequence++,
                                   demand->cancelled});
    }
    _workAvailable.notify_one();
    return true;
}
void GlyphScheduler::promote(const Demand& demand, Priority p)
{
    std::lock_guard lock(_mutex);
    for (auto it = _jobs.begin(); it != _jobs.end();)
    {
        const auto current = it++;
        if (current->key == demand.key && p < current->priority)
        {
            // The deadline only moves earlier, ahead of the remaining scan.
            auto job = _jobs.extract(current);
            job.value().priority = p;
            _jobs.insert(std::move(job));
        }
    }
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
        _resultsChanged.wait(lock, [&] { return !_results.empty() || idle(); });
    if (_results.empty() || _results.front().raster.image.pixels.size() > maxBytes)
        return false;
    auto result = std::move(_results.front());
    _results.pop_front();
    lock.unlock();
    out = std::move(result);
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
        _workAvailable.wait(lock, [&] { return quit->load() || !_jobs.empty(); });
        if (quit->load())
            return;
        auto job = std::move(_jobs.extract(_jobs.begin()).value());
        if (job.demand.expired())
        {
            const bool drained = idle();
            lock.unlock();
            if (drained)
                _resultsChanged.notify_all();
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
                auto credit = std::make_shared<Budget::Reservation>();
                credit->account = _budget;
                if (_budget->acquire(credits, bytes))
                    credit->bytes = bytes;
                credits.unlock();
                if (credit->bytes && !quit->load())
                    reservation = std::move(credit);
                else
                    result = {GlyphStatus::TooLarge};
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
        const bool wasEmpty = _results.empty();
        if (!job.demand.expired())
            _results.push_back({std::move(job.demand), std::move(result), std::move(reservation)});
        // A waiting consumer may proceed on the first result or when work drains.
        const bool wakeConsumer = (wasEmpty && !_results.empty()) || idle();
        lock.unlock();
        if (wakeConsumer)
            _resultsChanged.notify_all();
    }
}
}  // namespace cc::font
