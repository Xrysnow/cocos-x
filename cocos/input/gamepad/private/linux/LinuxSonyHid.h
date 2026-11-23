#pragma once

#include "LinuxHidGamepad.h"
#include "../drivers/SonyHidReports.h"

namespace cc::input::detail {

class LinuxSonyHid final : public LinuxHidGamepad {
public:
    static std::unique_ptr<LinuxSonyHid> open(const std::string& path, EndpointKey key);
    ~LinuxSonyHid() override;

    int fd() const override { return _fd; }
    bool attached() const override { return _attached; }
    const std::string& association() const override { return _association; }
    EndpointKey key() const override { return _key; }
    bool read(ReportSink& sink, const std::function<void()>& beforeAttach) override;
    RawBaseline baseline() const override { return {_raw, _cursor, {}}; }
    AttachedEndpoint snapshot() override;
    void setSensor(Sensor sensor, bool enabled) override;
    Error submit(const OutputCommand& command) override;
    Error startWaveform() override;
    void neutral() override;
    void tick(std::uint64_t now, bool active) override;
    bool needsPolling() const override { return _output.hasTimedRumble(); }

private:
    LinuxSonyHid(int fd, bool writable, SonyHidModel model, DualSenseTransport transport, EndpointKey key);
    bool write(SonyHidOutput& state, DualSenseOutputKind kind = DualSenseOutputKind::Effects);

    int _fd;
    bool _writable, _attached = false, _hasOutput = false, _enableRequested = false;
    bool _releaseLights;
    bool _waveformMode = false;
    std::string _association;
    DualSenseTransport _transport;
    EndpointKey _key;
    EndpointDescriptor _descriptor;
    RawState _raw;
    std::uint64_t _cursor = 0;
    std::uint64_t _firstFull = 0, _retryLightsAt = 0;
    std::bitset<SensorCount> _sensors;
    SonyHidReports _reports;
    SonyHidOutput _output;
    std::array<std::optional<Contact>, 2> _fingers{};
};

} // namespace cc::input::detail
