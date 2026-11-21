#pragma once

#include "../drivers/DualSenseReports.h"

namespace cc::input::detail {

class LinuxDualSense {
public:
    static std::unique_ptr<LinuxDualSense> open(const std::string& path, EndpointKey key);
    ~LinuxDualSense();

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
    bool hasTimedOutput() const { return _timed; }

private:
    LinuxDualSense() = default;
    bool write(DualSenseOutput& state);

    int _fd = -1;
    bool _writable = false, _attached = false, _timed = false, _hasOutput = false;
    std::string _association;
    DualSenseTransport _transport{};
    EndpointKey _key{};
    EndpointDescriptor _descriptor;
    RawState _raw;
    std::uint64_t _cursor = 0;
    std::bitset<SensorCount> _sensors;
    DualSenseOutput _output;
    std::optional<DualSenseCalibration> _calibration;
    std::array<std::optional<Contact>, 2> _fingers{};
};

} // namespace cc::input::detail
