#pragma once

#include "LinuxHidGamepad.h"
#include "../drivers/SwitchReports.h"

namespace cc::input::detail {

class LinuxSwitchHid final : public LinuxHidGamepad {
public:
    static std::unique_ptr<LinuxSwitchHid> open(const std::string& path, EndpointKey key);

    // Takes ownership of an already opened nonblocking report stream.
    LinuxSwitchHid(int fd, EndpointKey key, SwitchModel model, EndpointDescriptor descriptor, bool kernelManaged);
    ~LinuxSwitchHid() override;

    int fd() const override { return _fd; }
    bool attached() const override { return _attached; }
    const std::string& association() const override { return _descriptor.physicalAssociation; }
    EndpointKey key() const override { return _key; }
    bool read(ReportSink& sink, const std::function<void()>& beforeAttach) override;
    RawBaseline baseline() const override { return {_raw, _cursor, _lastInput}; }
    AttachedEndpoint snapshot() override;
    void setSensor(Sensor sensor, bool enabled) override;
    Error submit(const OutputCommand& command, const NativeBodyGate& gate = {}) override;
    void neutral() override;
    void tick(std::uint64_t now, bool active) override;
    bool needsPolling() const override;

private:
    bool write(const SwitchPacket& packet) const;
    void receive(std::span<const std::uint8_t> packet, ReportSink& sink,
                 const std::function<void()>& beforeAttach, ReportTime time);
    void configure(std::uint64_t now);
    void restoreReportMode();
    void updateImu(std::uint64_t now);
    bool bodyActive(std::uint64_t now) const { return _rumbleEnd > now && bodyGateOpen(_bodyGate); }

    int _fd;
    EndpointKey _key;
    EndpointDescriptor _descriptor;
    const SwitchModel _model;
    const bool _usb, _kernelManaged;
    SwitchReports _reports;
    SwitchOutput _output;
    RawState _raw;
    ReportTime _lastInput{};
    std::uint64_t _cursor = 0;
    bool _attached = false, _active = true, _vibrationReady = false;
    std::optional<bool> _startedInFullMode;
    bool _modeRequested = false;
    unsigned _setupStep, _setupAttempts = 0;
    std::uint64_t _setupAt = 0, _lastFull = 0, _attachBy = 0;
    std::bitset<SensorCount> _sensors;
    bool _imuTarget = false, _imuWritten = false;
    unsigned _imuAttemptsLeft = 0;
    std::uint64_t _imuAt = 0;
    SwitchMotors _motors = SwitchNeutralRumble;
    NativeBodyGate _bodyGate;
    std::uint8_t _lights = 0;
    bool _stopPending = false;
    std::uint64_t _rumbleEnd = 0, _rumbleAt = 0, _stopAt = 0;
};

} // namespace cc::input::detail
