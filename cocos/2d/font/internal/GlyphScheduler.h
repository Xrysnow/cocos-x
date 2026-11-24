#pragma once
#include "FontFace.h"
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>

namespace cc::font
{
enum class Priority
{
    Sync,
    Visible,
    Prefetch
};
struct Demand
{
    explicit Demand(GlyphKey k) : key(std::move(k)) {}
    GlyphKey key;
    Priority priority{Priority::Prefetch};
    std::shared_ptr<std::atomic_bool> cancelled = std::make_shared<std::atomic_bool>(false);
    std::shared_ptr<const GlyphStatus> publication;
    cc::GlyphStatus status{cc::GlyphStatus::Pending};  // engine thread only
};
class GlyphScheduler
{
public:
    struct Result
    {
        std::weak_ptr<Demand> demand;
        RasterResult raster;
        std::shared_ptr<void> staging;
    };
    GlyphScheduler();
    ~GlyphScheduler();
    bool configure(const FontCacheConfig& config);
    bool submit(const std::shared_ptr<Demand>& demand, Priority priority, size_t limit);
    void promote(const Demand& demand, Priority priority);
    bool take(Result& out, bool wait, size_t maxBytes = SIZE_MAX);
    void stats(FontCacheStats&) const;

private:
    struct Job
    {
        std::weak_ptr<Demand> demand;
        GlyphKey key;
        Priority priority;
        std::chrono::steady_clock::time_point queued;
        std::shared_ptr<std::atomic_bool> cancel;
    };
    void run(std::shared_ptr<std::atomic_bool> quit);
    mutable std::mutex _mutex;
    std::condition_variable _changed;
    std::deque<Job> _jobs;
    std::deque<Result> _results;
    struct Budget;
    std::shared_ptr<Budget> _budget;
    uint32_t _running{};
    std::vector<std::shared_ptr<std::atomic_bool>> _active;
    struct Worker
    {
        std::shared_ptr<std::atomic_bool> quit;
        std::thread thread;
    };
    std::vector<Worker> _workers;
};
}  // namespace cc::font
