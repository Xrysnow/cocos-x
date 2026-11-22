#pragma once

#include "WinHidFile.h"
#include "../drivers/SwitchReports.h"

namespace cc::input::detail {

class WinSwitchGamepad {
public:
    WinSwitchGamepad(const std::wstring& path, SwitchModel model, WinHidBus bus, unsigned outputLength);
    ~WinSwitchGamepad();
    bool writable() const { return static_cast<bool>(_written); }
    void decode(WinInputEndpoint& endpoint, std::span<const std::uint8_t> bytes, ReportSink& sink, ReportTime time);
    void setSensor(Sensor sensor, bool enabled);
    void poll();
    Error submit(const OutputCommand& command);
    void stopOutput();
    void resetTopology();

private:
    bool write(const SwitchPacket& packet);
    void finishSetup(std::span<const std::uint8_t> reply);
    void updateCapabilities(WinInputEndpoint& endpoint, ReportSink& sink);
    void pollProtocol(std::uint64_t now);

    HidHandle _writable, _written;
    const SwitchModel _model;
    SwitchReports _reports;
    SwitchOutput _output;
    const bool _usb;
    std::vector<std::uint8_t> _buffer;
    std::bitset<SensorCount> _sensors;
    unsigned _setupStep = 0, _attempts = 0, _imuAttempts = 0;
    std::uint64_t _nextCommand = 0, _nextImu = 0, _nextRumble = 0, _rumbleEnd = 0, _lastFull = 0;
    std::optional<bool> _imuPending, _startedInFullMode;
    bool _imuEnabled = false, _modeRequested = false, _subcommandsReady = false, _vibrationReady = false;
    bool _stopping = false;
    std::uint8_t _lights = 0;
    SwitchMotors _motors = SwitchNeutralRumble;
};

} // namespace cc::input::detail
