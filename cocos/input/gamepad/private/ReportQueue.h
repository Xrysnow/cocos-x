#pragma once

#include "GamepadBackend.h"

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <utility>

namespace cc::input::detail {

class MappingDatabase;
struct MappingSelection;

using Attach = AttachedEndpoint;
template<class T, std::size_t InlineCapacity>
class ReportPayload {
public:
    explicit ReportPayload(std::span<const T> values) : _size(values.size())
    {
        if (_size <= InlineCapacity)
            std::ranges::copy(values, _smallStorage.begin());
        else
            _extended.emplace(values.begin(), values.end());
    }

    std::span<const T> view() const
    {
        if (_size <= InlineCapacity)
            return {_smallStorage.data(), _size};
        return *_extended;
    }
    auto begin() const { return view().begin(); }
    auto end() const { return view().end(); }

private:
    std::array<T, InlineCapacity> _smallStorage{};
    std::optional<std::vector<T>> _extended;
    std::size_t _size;
};

struct Report {
    EndpointKey key;
    ReportPayload<RawChange, 8> changes;
    ReportPayload<Contact, 2> contacts;
    ReportPayload<Motion, 2> motion;
    std::optional<Power> power;
    std::uint64_t cursor;
};
struct Baseline { EndpointKey key; RawBaseline snapshot; };
struct CapabilityUpdate { EndpointKey key; EndpointCapabilities capabilities; };
struct HapticCapabilityUpdate { DeviceId device; std::optional<EndpointKey> owner; };
struct Desync { EndpointKey key; InputGap gap; };
struct Detach { EndpointKey key; };
struct Focus { bool active; };
struct MappingFence { std::shared_ptr<const MappingDatabase> database; };
struct LocalFence { DeviceId id; std::string layout; std::shared_ptr<const MappingSelection> selection; };
struct PlayerFence { DeviceId id; std::optional<unsigned> slot; };
struct NativeCompletion { EndpointKey key; CommandId id; Error error; };
struct OutputNotice { DeviceId device; OutputDone done; };
struct TopologyLoss {};
struct TopologySnapshot { std::vector<AttachedEndpoint> endpoints; };

using RecordData = std::variant<Attach, Report, Baseline, CapabilityUpdate, HapticCapabilityUpdate, Desync, Detach,
    Focus, MappingFence, LocalFence, PlayerFence, NativeCompletion, OutputNotice, TopologyLoss,
    TopologySnapshot>;

struct Record {
    std::uint64_t seq;
    ReportTime time;
    RecordData data;
};

struct ReportBatch {
    std::vector<Record> records;
    std::vector<Record> overflow;
    std::uint64_t cutoff = 0, watermark = 0;
};

class ReportQueue final : public ReportSink {
public:
    ReportQueue(std::size_t reports, std::size_t controls);
    void close();
    bool control(RecordData);
    void outputNotice(OutputNotice);
    void hapticCapability(HapticCapabilityUpdate);
    void focus(bool);
    void drain(ReportBatch&);

    void attached(EndpointKey, EndpointDescriptor, RawBaseline) override;
    void report(EndpointKey, const ReportView&) override;
    void baseline(EndpointKey, RawBaseline) override;
    void capabilitiesChanged(EndpointKey, EndpointCapabilities) override;
    void desynchronized(EndpointKey, InputGap) override;
    void detached(EndpointKey) override;
    void topology(std::vector<AttachedEndpoint>) override;
    void outputCompleted(EndpointKey, CommandId, Error) override;

private:
    struct EndpointProgress {
        std::uint64_t lostThrough = 0;
        std::optional<Record> gap;
        bool awaitingBaseline = false;
    };

    bool pushControl(RecordData, ReportTime, bool backend);
    void loseTopology(ReportTime);

    std::mutex _mutex;
    std::vector<Record> _records;
    std::vector<Record> _overflow;
    std::map<EndpointKey, EndpointProgress> _endpoints;
    std::optional<Record> _topologyLoss;
    std::uint64_t _seq = 0;
    std::size_t _reportLimit, _controlLimit;
    std::size_t _reports = 0, _controls = 0;
    bool _closed = false;
    bool _awaitingTopology = false;
};

} // namespace cc::input::detail
