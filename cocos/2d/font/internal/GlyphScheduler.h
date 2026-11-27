#pragma once
#include "FontFace.h"
#include <condition_variable>
#include <deque>
#include <mutex>
#include <set>
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
        uint64_t sequence;
        std::shared_ptr<std::atomic_bool> cancel;

        // A queued background job can age past newer foreground jobs.
        auto deadline() const { return queued + std::chrono::milliseconds(100 * int(priority)); }
    };
    struct EarlierJob
    {
        bool operator()(const Job& a, const Job& b) const
        {
            return std::pair(a.deadline(), a.sequence) < std::pair(b.deadline(), b.sequence);
        }
    };
    void run(std::shared_ptr<std::atomic_bool> quit);
    bool idle() const { return _jobs.empty() && _running == 0; }  // _mutex held
    mutable std::mutex _mutex;
    std::condition_variable _workAvailable;
    std::condition_variable _resultsChanged;
    std::set<Job, EarlierJob> _jobs;
    uint64_t _nextSequence{};
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
