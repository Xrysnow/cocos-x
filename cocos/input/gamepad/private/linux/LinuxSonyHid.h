#pragma once

#include "../drivers/SonyHidReports.h"

namespace cc::input::detail {

class LinuxSonyHid {
public:
    static std::unique_ptr<LinuxSonyHid> open(const std::string& path, EndpointKey key);
    ~LinuxSonyHid();

    int fd() const { return _fd; }
    bool attached() const { return _attached; }
    const std::string& association() const { return _association; }
    EndpointKey key() const { return _key; }
    bool read(ReportSink& sink);
    RawBaseline baseline() const { return {_raw, _cursor, {}}; }
    AttachedEndpoint snapshot();
    void setSensor(Sensor sensor, bool enabled);
    Error submit(const OutputCommand& command);
    void neutral();
    void expire(std::uint64_t now);
    bool hasTimedOutput() const { return _output.hasTimedRumble(); }

private:
    LinuxSonyHid(int fd, bool writable, SonyHidModel model, DualSenseTransport transport, EndpointKey key);
    bool write(SonyHidOutput& state, DualSenseOutputKind kind = DualSenseOutputKind::Effects);

    int _fd;
    bool _writable, _attached = false, _hasOutput = false, _enableRequested = false;
    bool _releaseLights;
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
