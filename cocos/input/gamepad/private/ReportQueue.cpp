#include "ReportQueue.h"

#include <algorithm>

namespace cc::input::detail {

ReportQueue::ReportQueue(std::size_t reports, std::size_t controls)
    : _reportLimit(reports), _controlLimit(controls)
{
    _records.reserve(reports + controls);
}

void ReportQueue::close()
{
    std::lock_guard lock(_mutex);
    _closed = true;
}

bool ReportQueue::control(RecordData data)
{
    return pushControl(std::move(data), {}, false);
}

void ReportQueue::outputNotice(OutputNotice notice)
{
    // At most one notice per outstanding command. A full control lane must
    // never discard a command's terminal status.
    const ReportTime time;
    std::lock_guard lock(_mutex);
    if (!_closed)
        _overflow.push_back({++_seq, time, std::move(notice)});
}

void ReportQueue::focus(bool active)
{
    const ReportTime time;
    std::lock_guard lock(_mutex);
    if (!_closed)
        _overflow.push_back({++_seq, time, Focus{active}});
}

bool ReportQueue::pushControl(RecordData data, ReportTime time, bool backend)
{
    std::lock_guard lock(_mutex);
    if (_closed)
        return false;
    if (_controls == _controlLimit)
    {
        if (backend)
            loseTopology(time);
        return false;
    }
    _records.push_back({++_seq, time, std::move(data)});
    ++_controls;
    return true;
}

// Producer holds _mutex. Loss is ordered after the last accepted native
// record, and the consumer replaces topology from a fresh enumeration.
void ReportQueue::loseTopology(ReportTime time)
{
    if (!_topologyLoss)
        _topologyLoss = Record{++_seq, time, TopologyLoss{}};
}

void ReportQueue::attached(EndpointKey key, EndpointDescriptor descriptor, RawBaseline baseline)
{
    const auto time = baseline.time;
    std::lock_guard lock(_mutex);
    if (_closed || _topologyLoss || _awaitingTopology)
        return;
    if (_endpoints.contains(key))
        return;
    if (_controls == _controlLimit)
    {
        loseTopology(time);
        return;
    }
    _endpoints.try_emplace(key);
    _records.push_back({++_seq, time, Attach{key, std::move(descriptor), std::move(baseline)}});
    ++_controls;
}

void ReportQueue::report(EndpointKey key, const ReportView& view)
{
    Report report{key, ReportPayload<RawChange, 8>(view.changes), ReportPayload<Contact, 2>(view.contacts),
        ReportPayload<Motion, 2>(view.motion), view.power, view.cursor};
    std::lock_guard lock(_mutex);
    const auto route = _endpoints.find(key);
    if (_closed || _topologyLoss || route == _endpoints.end())
        return;
    auto& progress = route->second;
    if (_reports == _reportLimit || progress.lostThrough != 0)
    {
        const auto cursor = std::max<std::uint64_t>(1, view.cursor);
        progress.lostThrough = std::max(progress.lostThrough, cursor);
        if (!progress.gap)
        {
            // Only the first drop for an epoch marks the stream boundary.
            // Subsequent drops can happen after drain, so the count is unknown.
            if (!progress.awaitingBaseline)
                progress.gap = Record{++_seq, view.time,
                    Desync{key, {GapCause::QueueOverflow, std::nullopt}}};
        }
        return;
    }
    _records.push_back({++_seq, view.time, std::move(report)});
    ++_reports;
}

void ReportQueue::baseline(EndpointKey key, RawBaseline snapshot)
{
    const auto time = snapshot.time;
    std::lock_guard lock(_mutex);
    const auto route = _endpoints.find(key);
    if (_closed || _topologyLoss || route == _endpoints.end())
        return;
    auto& progress = route->second;
    if (snapshot.cursor < progress.lostThrough)
    {
        if (progress.awaitingBaseline && !progress.gap)
            progress.gap = Record{++_seq, time, Desync{key, {GapCause::QueueOverflow, std::nullopt}}};
        return;
    }
    if (_controls == _controlLimit)
    {
        loseTopology(time);
        return;
    }
    if (progress.gap)
    {
        _overflow.push_back(std::move(*progress.gap));
        progress.gap.reset();
    }
    progress.lostThrough = 0;
    progress.awaitingBaseline = false;
    _records.push_back({++_seq, time, Baseline{key, std::move(snapshot)}});
    ++_controls;
}

void ReportQueue::capabilitiesChanged(EndpointKey key, EndpointCapabilities caps)
{
    pushControl(CapabilityUpdate{key, std::move(caps)}, {}, true);
}

void ReportQueue::desynchronized(EndpointKey key, InputGap gap)
{
    pushControl(Desync{key, gap}, {}, true);
}

void ReportQueue::detached(EndpointKey key)
{
    const ReportTime time;
    std::lock_guard lock(_mutex);
    const auto route = _endpoints.find(key);
    if (_closed || _topologyLoss || route == _endpoints.end())
        return;
    if (_controls == _controlLimit)
    {
        loseTopology(time);
        return;
    }
    if (route->second.gap)
        _overflow.push_back(std::move(*route->second.gap));
    _endpoints.erase(route);
    _records.push_back({++_seq, time, Detach{key}});
    ++_controls;
}

void ReportQueue::outputCompleted(EndpointKey key, CommandId id, Error error)
{
    if (id != CommandId{})
        pushControl(NativeCompletion{key, id, error}, {}, true);
}

void ReportQueue::topology(std::vector<AttachedEndpoint> endpoints)
{
    std::map<EndpointKey, EndpointProgress> routes;
    for (const auto& endpoint : endpoints)
        routes.try_emplace(endpoint.key);
    const ReportTime time;
    std::lock_guard lock(_mutex);
    if (_closed || !_awaitingTopology || _topologyLoss)
        return;
    _overflow.push_back({++_seq, time, TopologySnapshot{std::move(endpoints)}});
    _endpoints.swap(routes);
    _awaitingTopology = false;
}

void ReportQueue::drain(ReportBatch& batch)
{
    batch.records.clear();
    batch.records.reserve(_reportLimit + _controlLimit);
    auto& overflow = batch.overflow;
    overflow.clear();
    {
        std::lock_guard lock(_mutex);
        batch.records.swap(_records);
        batch.cutoff = nowNs();
        batch.watermark = _seq;
        _reports = _controls = 0;
        overflow.swap(_overflow);
        for (auto& [key, progress] : _endpoints)
        {
            if (!progress.gap)
                continue;
            overflow.push_back(std::move(*progress.gap));
            progress.gap.reset();
            progress.awaitingBaseline = true;
        }
        if (_topologyLoss)
        {
            overflow.push_back(std::move(*_topologyLoss));
            _topologyLoss.reset();
            _endpoints.clear();
            _awaitingTopology = true;
        }
    }
    if (!overflow.empty())
    {
        for (auto& record : overflow)
            batch.records.push_back(std::move(record));
        std::ranges::sort(batch.records, {}, &Record::seq);
    }
}

} // namespace cc::input::detail
