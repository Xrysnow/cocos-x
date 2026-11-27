#pragma once

#include "WinHidFile.h"
#include "../drivers/XboxBluetoothReports.h"

namespace cc::input::detail {

class WinXboxBluetooth {
public:
    WinXboxBluetooth(const std::wstring& path, XboxBluetoothModel model, unsigned outputLength);
    ~WinXboxBluetooth();

    void decode(WinInputEndpoint& device, std::span<const std::uint8_t> packet, ReportSink& sink, ReportTime time);
    Error submit(const OutputCommand& command, const NativeBodyGate& gate = {});
    void stop();
    void poll();

private:
    bool write(const XboxRumbleState& state);

    HidHandle _writer, _event;
    XboxBluetoothReports _reports;
    XboxRumbleState _rumble;
    std::vector<std::uint8_t> _buffer;
    std::uint64_t _probeAt = 0, _retryAt = 0;
    unsigned _probeAttempts = 0;
    bool _seenControls = false, _feedback = false, _stopPending = false;
};

} // namespace cc::input::detail
