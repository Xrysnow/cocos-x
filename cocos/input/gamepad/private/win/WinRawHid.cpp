#include "WinSwitchGamepad.h"
#include "WinWgi.h"
#include "WinXboxBluetooth.h"
#include "../PlatformGamepadBackend.h"
#include "../drivers/SonyHidReports.h"

#include <cfgmgr32.h>
#include <hidsdi.h>
#include <hidusage.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <map>
#include <tuple>
#include <type_traits>

namespace cc::input::detail {
namespace {

constexpr std::array<USHORT, 2> gamepadUsages{HID_USAGE_GENERIC_JOYSTICK, HID_USAGE_GENERIC_GAMEPAD};
constexpr UINT errorSize = static_cast<UINT>(-1);

bool gamepadUsage(DWORD page, DWORD usage)
{
    return page == HID_USAGE_PAGE_GENERIC && std::ranges::find(gamepadUsages, usage) != gamepadUsages.end();
}

std::wstring rawDevicePath(HANDLE handle)
{
    UINT size = 0;
    if (GetRawInputDeviceInfoW(handle, RIDI_DEVICENAME, nullptr, &size) == errorSize || size == 0)
        return {};
    std::wstring result(size, L'\0');
    if (GetRawInputDeviceInfoW(handle, RIDI_DEVICENAME, result.data(), &size) == errorSize)
        return {};
    result.resize(std::char_traits<wchar_t>::length(result.c_str()));
    return result;
}

struct Control {
    RawKind kind;
    USHORT dataIndex, page, usage, link;
    UCHAR report;
    LONG minimum = 0, maximum = 1;
    USHORT bits = 1;
    unsigned index = 0;
};

struct FreePreparsedData {
    void operator()(PHIDP_PREPARSED_DATA data) const { HidD_FreePreparsedData(data); }
};


class WinSonyGamepad {
public:
    WinSonyGamepad(const std::wstring& path, const HIDP_CAPS& hid, EndpointDescriptor& descriptor,
                   SonyHidModel model, DualSenseTransport transport, WinHidBus bus)
        : _model(model), _transport(transport), _outputLength(hid.OutputReportByteLength),
          _reports(model, transport), _output(model)
    {
        if (bus != WinHidBus::Unknown)
            descriptor.link = bluetooth() ? Link::Wireless : Link::Wired;
        // Windows pads feature reads to the collection's longest feature report.
        const auto feature = hid.FeatureReportByteLength ? openHid(path, GENERIC_READ, FILE_ATTRIBUTE_NORMAL)
                                                         : HidHandle{};
        bool requestedEnhanced = false;
        std::optional<std::uint16_t> firmware;
        if (feature)
        {
            std::vector<std::uint8_t> buffer(hid.FeatureReportByteLength);
            const auto readFeature = [&](std::uint8_t id, std::size_t length) {
                if (buffer.size() < length)
                    return std::span<const std::uint8_t>{};
                std::ranges::fill(buffer, std::uint8_t{0});
                buffer.front() = id;
                return HidD_GetFeature(feature.get(), buffer.data(), static_cast<ULONG>(buffer.size()))
                    ? std::span<const std::uint8_t>(buffer).first(length) : std::span<const std::uint8_t>{};
            };
            if (isDualShock4())
            {
                const auto usbCalibration = readFeature(0x02, 37);
                if (bluetooth())
                {
                    requestedEnhanced = !usbCalibration.empty();
                    _reports.calibrate(readFeature(0x05, 41));
                }
                else
                    _reports.calibrate(usbCalibration);
            }
            else
            {
                _reports.calibrate(readFeature(0x05, 41));
                firmware = decodeDualSenseFirmware(readFeature(DualSenseFirmwareReportId, 46));
                if (bluetooth())
                    requestedEnhanced = !readFeature(0x09, 20).empty();
            }
        }
        _output.configureRumble(model, transport, firmware);
        const bool writableReport = bluetooth() ? _outputLength >= 78
            : isDualShock4() ? _outputLength >= 32 && _outputLength <= 64
                            : _outputLength >= 48 && _outputLength <= 64;
        if (writableReport)
        {
            _writable = openHid(path, GENERIC_WRITE, FILE_FLAG_OVERLAPPED);
            if (_writable)
                _written.reset(CreateEventW(nullptr, TRUE, FALSE, nullptr));
            if (bluetooth() && _outputLength > 78)
                _outputBuffer.resize(_outputLength);
        }
        if (bus == WinHidBus::Usb && !isDualShock4())
        {
            descriptor.hapticAudio.containerId = sonyUsbHapticContainer(path);
            descriptor.hapticAudio.writable = static_cast<bool>(_written);
            _waveformAvailable = _written && !descriptor.hapticAudio.containerId.empty();
        }
        if (!bluetooth())
            enableCapabilities(descriptor);
        else if (!requestedEnhanced)
            enableEnhancedReports();
    }

    ~WinSonyGamepad() { stopOutput(); }

    bool bluetooth() const { return _transport == DualSenseTransport::Bluetooth; }
    bool receivedFullInput() const { return _firstFullReport.has_value(); }
    bool usesProtocolLayout() const { return _model != SonyHidModel::DualSense; }
    bool decodesControls() const { return usesProtocolLayout() || bluetooth(); }

    void observeSimpleReport(std::uint64_t now)
    {
        if (_written && _enableAttempts < 3 && now >= _nextEnable)
            enableEnhancedReports();
    }

    std::optional<SonyHidInput> decode(std::span<const std::uint8_t> bytes)
    {
        if (!isDualShock4() && bluetooth() && bytes.size() > 78)
            bytes = bytes.first(78); // Discard Windows padding after the protocol CRC.
        return _reports.decode(bytes);
    }

    std::optional<DualSenseControls> simple(std::span<const std::uint8_t> bytes) const { return _reports.simple(bytes); }

    void setSensor(Sensor sensor, bool enabled)
    {
        if ((_reports.hasCalibration() || receivedFullInput()) && (sensor == Sensor::Gyro || sensor == Sensor::Accel))
            _sensors.set(static_cast<unsigned>(sensor), enabled);
    }

    void resetBaseline()
    {
        _fingers = {};
        _refreshPower = true;
    }

    void resetTopology()
    {
        stopOutput();
        resetBaseline();
        _sensors.reset();
    }

    void publish(WinInputEndpoint& endpoint, const std::optional<SonyHidInput>& sample,
                 std::span<const RawChange> changes,
                 ReportSink& sink, ReportTime time)
    {
        std::vector<Contact> contacts;
        std::array<Motion, 2> motion{};
        unsigned motionCount = 0;
        std::optional<Power> power;
        if (sample)
        {
            if (!_firstFullReport)
            {
                _firstFullReport = time.receivedNs;
                if (bluetooth() || isDualShock4())
                {
                    enableCapabilities(endpoint.descriptor);
                    sink.capabilitiesChanged(endpoint.key, endpoint.descriptor.capabilities);
                }
            }
            // DualSense Bluetooth plays a connection animation before it releases its lights.
            if (bluetooth() && !isDualShock4())
                _canReleaseLights |= sample->sensorTicks >= 10200000;
            if (sample->hasTouchSample)
            {
                contacts = dualSenseTouchChanges(_fingers, sample->fingers);
                _fingers = sample->fingers;
            }
            for (const auto& value : sample->motion)
                if (_sensors.test(static_cast<unsigned>(value.sensor)))
                    motion[motionCount++] = value;
            auto& current = endpoint.descriptor.power;
            if (_refreshPower || current.state != sample->power.state || current.percent != sample->power.percent)
            {
                current = sample->power;
                power = current;
                _refreshPower = false;
            }
        }
        if (!changes.empty() || !contacts.empty() || motionCount || power)
            sink.report(endpoint.key, {changes, contacts, std::span(motion).first(motionCount), power,
                                       ++endpoint.cursor, time});
    }

    Error submit(const OutputCommand& command, const NativeBodyGate& gate)
    {
        if (!_written || (bluetooth() && !receivedFullInput()))
            return Error::Unsupported;
        const auto* stop = std::get_if<Stop>(&command);
        const bool stopAll = stop && stop->channel == Channel::All;
        const bool stopBody = stop && stop->channel == Channel::Body;
        if (_resetOutput && !stopAll && !stopBody)
            return Error::Busy;
        auto next = _output;
        const auto now = nowNs();
        if (std::holds_alternative<Rumble>(command) || stopAll || stopBody)
            next.setHapticsMode(false);
        const bool allNeutral = stopAll || _resetOutput;
        if (!next.apply(allNeutral ? OutputCommand{Stop{}} : command, now, gate))
            return bodyGateOpen(gate) ? Error::Unsupported : Error::Busy;
        if (!write(next))
            return Error::BackendFailure;
        _output = next;
        _hasOutput = !allNeutral && (_hasOutput || !stop);
        _resetOutput = false;
        return Error::None;
    }

    void stopOutput()
    {
        if (_hasOutput)
        {
            auto neutral = _output;
            neutral.setHapticsMode(false);
            neutral.apply(Stop{}, nowNs());
            if (write(neutral))
            {
                _output = neutral;
                _hasOutput = false;
            }
        }
        _resetOutput = _hasOutput;
    }

    Error startWaveform()
    {
        if (!_waveformAvailable)
            return Error::Unsupported;
        if (_resetOutput)
            return Error::Busy;
        auto next = _output;
        next.expire(nowNs());
        if (!next.setHapticsMode(true) || !write(next))
            return Error::BackendFailure;
        _output = next;
        _hasOutput = true;
        return Error::None;
    }


    bool needsPolling() const
    {
        return _resetOutput || _output.hasTimedRumble() ||
            (_written && bluetooth() && !isDualShock4() && _firstFullReport && !_lightsReleased);
    }

    void pollOutput()
    {
        if (_resetOutput)
        {
            stopOutput();
            return;
        }
        if (_output.hasTimedRumble())
        {
            auto next = _output;
            if (next.expire(nowNs()) && write(next))
                _output = next;
        }
        if (_written && bluetooth() && !isDualShock4() && !_lightsReleased && _firstFullReport)
        {
            const auto now = nowNs();
            if (now >= _nextLightAttempt && (_canReleaseLights || now - *_firstFullReport >= 3400000000ull))
            {
                _nextLightAttempt = now + 250000000;
                if (write(_output, DualSenseOutputKind::ReleaseBluetoothLights))
                {
                    auto next = _output;
                    next.expire(nowNs());
                    _lightsReleased = !_hasOutput || write(next);
                    if (_lightsReleased)
                        _output = next;
                }
            }
        }
    }

private:
    bool isDualShock4() const { return _model == SonyHidModel::DualShock4; }

    void enableCapabilities(EndpointDescriptor& descriptor) const
    {
        auto& caps = descriptor.capabilities;
        if (!isDualShock4() || receivedFullInput())
            caps.fingersPerPad = {2};
        // Full DS4 and Bluetooth reports permit nominal conversion if calibration is unavailable.
        if (_reports.hasCalibration() || (receivedFullInput() && (bluetooth() || isDualShock4())))
        {
            caps.sensors.set(static_cast<unsigned>(Sensor::Gyro));
            caps.sensors.set(static_cast<unsigned>(Sensor::Accel));
        }
        if (!_written)
            return;
        for (auto feature : {Feature::BodyRumble, Feature::RgbLed})
            caps.features.set(static_cast<unsigned>(feature));
        caps.acknowledgedBodyStop = true;
        if (isDualShock4())
            return;
        for (auto feature : {Feature::PlayerLights, Feature::AdaptiveLeft, Feature::AdaptiveRight})
            caps.features.set(static_cast<unsigned>(feature));
        caps.playerLightMask = 31;
        caps.triggerLimits = {TriggerLimits{true, true, 1, 255}, TriggerLimits{true, true, 1, 255}};
    }

    bool enableEnhancedReports()
    {
        if (!_written)
            return false;
        ++_enableAttempts;
        _nextEnable = nowNs() + 500000000;
        return write(_output, DualSenseOutputKind::EnableBluetooth);
    }

    bool write(SonyHidOutput& output, DualSenseOutputKind kind = DualSenseOutputKind::Effects)
    {
        auto report = output.encode(_transport, _outputLength, kind);
        if (report.empty())
            return false;
        if (!_outputBuffer.empty())
        {
            std::ranges::copy(report, _outputBuffer.begin());
            report = _outputBuffer;
        }
        return writeHid(_writable.get(), _written.get(), report);
    }

    HidHandle _writable, _written;
    SonyHidModel _model;
    DualSenseTransport _transport;
    unsigned _outputLength;
    std::vector<std::uint8_t> _outputBuffer;
    SonyHidReports _reports;
    SonyHidOutput _output;
    bool _waveformAvailable = false;
    std::array<std::optional<Contact>, 2> _fingers{};
    std::bitset<SensorCount> _sensors;
    bool _refreshPower = true, _hasOutput = false, _resetOutput = false;
    std::optional<std::uint64_t> _firstFullReport;
    std::uint64_t _nextEnable = 0, _nextLightAttempt = 0;
    unsigned _enableAttempts = 0;
    bool _canReleaseLights = false, _lightsReleased = false;
};

std::int64_t logicalValue(const Control& control, ULONG value)
{
    const auto range = std::uint64_t{1} << control.bits;
    const auto masked = value & (range - 1);
    const auto signedValue = static_cast<std::int64_t>(masked);
    return control.minimum < 0 && masked >= range / 2 ? signedValue - static_cast<std::int64_t>(range)
                                                     : signedValue;
}

std::string layoutId(std::span<const Control> controls)
{
    std::uint64_t hash = 14695981039346656037ull;
    for (const auto& control : controls)
    {
        for (auto field : {static_cast<unsigned>(control.kind), static_cast<unsigned>(control.page),
                           static_cast<unsigned>(control.usage), static_cast<unsigned>(control.link),
                           static_cast<unsigned>(control.dataIndex), static_cast<unsigned>(control.report),
                           static_cast<unsigned>(control.bits), static_cast<unsigned>(control.minimum),
                           static_cast<unsigned>(control.maximum)})
            hash = (hash ^ field) * 1099511628211ull;
    }
    return "win-raw-hid-v1/" + std::to_string(hash);
}

struct Device : WinInputEndpoint {
    std::wstring path;
    std::vector<ULONG> preparsed;
    std::unique_ptr<std::remove_pointer_t<PHIDP_PREPARSED_DATA>, FreePreparsedData> nativePreparsed;
    std::vector<Control> controls;
    std::vector<HIDP_DATA> data;
    std::vector<ULONG> values;
    std::vector<std::uint8_t> valuePresent;
    std::vector<char> buffer;
    std::vector<RawChange> changes;
    std::bitset<256> seenReports;
    std::bitset<256> reportIds;
    std::unique_ptr<WinSonyGamepad> sony;
    std::unique_ptr<WinSwitchGamepad> nintendo;
    std::unique_ptr<WinXboxBluetooth> xbox;

    PHIDP_PREPARSED_DATA parser()
    {
        return nativePreparsed ? nativePreparsed.get() : reinterpret_cast<PHIDP_PREPARSED_DATA>(preparsed.data());
    }

    void decodeSony(std::span<const std::uint8_t> bytes, ReportSink& sink, ReportTime time)
    {
        const auto full = sony->decode(bytes);
        const auto simple = !full && !sony->receivedFullInput() ? sony->simple(bytes) : std::nullopt;
        const DualSenseControls* sample = full ? &*full : simple ? &*simple : nullptr;
        if (!sample)
            return;
        // Preserve the existing DirectInput layout for the standard DualSense over Bluetooth.
        constexpr std::array<unsigned, 15> buttons{2, 0, 1, 3, 9, 10, 13, 14, 4, 6, 7, 8, 5, 11, 12};
        constexpr std::array<unsigned, 6> axes{0, 1, 2, 4, 5, 3};
        const bool nativeLayout = sony->usesProtocolLayout();
        changes.clear();
        const auto update = [&](RawKind kind, unsigned index, auto& old, auto value) {
            if (old != value)
            {
                old = value;
                changes.push_back({kind, index, value});
            }
        };
        for (unsigned i = 0; i < state.buttons.size(); ++i)
            update(RawKind::Button, i, state.buttons[i], sample->buttons[nativeLayout ? i : buttons[i]]);
        for (unsigned i = 0; i < axes.size(); ++i)
        {
            update(RawKind::Axis, i, state.axes[i], sample->axes[nativeLayout ? i : axes[i]]);
            state.axesKnown[i] = 1;
        }
        update(RawKind::Hat, 0, state.hats[0], sample->hat);
        const bool first = seenReports.none();
        seenReports.set(bytes.front());
        if (first)
        {
            sendBaseline(sink, time);
            changes.clear();
        }
        sony->publish(*this, full, changes, sink, time);
        if (simple)
            sony->observeSimpleReport(time.receivedNs);
    }

    void decode(std::span<const char> packet, ReportSink& sink, ReportTime time)
    {
        if (packet.empty() || packet.size() > buffer.size())
            return;
        const auto bytes = std::span(reinterpret_cast<const std::uint8_t*>(packet.data()), packet.size());
        if (xbox)
        {
            xbox->decode(*this, bytes, sink, time);
            return;
        }
        if (nintendo)
        {
            nintendo->decode(*this, bytes, sink, time);
            return;
        }
        if (sony && sony->decodesControls())
        {
            decodeSony(bytes, sink, time);
            return;
        }
        const auto report = static_cast<unsigned char>(packet.front());
        if (!reportIds[report])
            return;
        if (packet.size() < buffer.size())
        {
            std::ranges::fill(buffer, '\0');
            std::ranges::copy(packet, buffer.begin());
            packet = buffer;
        }
        auto count = static_cast<ULONG>(data.size());
        if (HidP_GetData(HidP_Input, data.data(), &count, parser(), const_cast<char*>(packet.data()),
                         static_cast<ULONG>(packet.size())) != HIDP_STATUS_SUCCESS)
            return;

        const bool first = !seenReports[report];
        seenReports.set(report);
        std::ranges::fill(valuePresent, std::uint8_t{0});
        for (const auto& entry : std::span(data).first(count))
        {
            if (entry.DataIndex >= values.size())
                continue;
            values[entry.DataIndex] = entry.RawValue;
            valuePresent[entry.DataIndex] = 1;
        }
        changes.clear();
        for (const auto& control : controls)
        {
            if (control.report != report)
                continue;
            const auto index = control.index;
            const bool present = valuePresent[control.dataIndex] != 0;
            const auto apply = [&](auto& current, auto value) {
                if (current != value)
                {
                    current = value;
                    changes.push_back({control.kind, index, value});
                }
            };
            if (control.kind == RawKind::Button)
                apply(state.buttons[index], static_cast<std::uint8_t>(present && values[control.dataIndex] != 0));
            else if (present)
            {
                const auto value = logicalValue(control, values[control.dataIndex]);
                if (control.kind == RawKind::Axis)
                {
                    apply(state.axes[index], normalizeWinAxis(value, control.minimum, control.maximum));
                    state.axesKnown[index] = 1;
                }
                else
                {
                    auto hat = std::uint8_t{0};
                    if (value >= control.minimum && value <= control.maximum)
                    {
                        const auto positions = static_cast<std::int64_t>(control.maximum) - control.minimum + 1;
                        const auto offset = value - control.minimum;
                        hat = winHat(static_cast<unsigned>((offset * 8 + positions / 2) / positions % 8));
                    }
                    apply(state.hats[index], hat);
                }
            }
        }
        if (first)
        {
            sendBaseline(sink, time);
            changes.clear();
        }
        if (sony)
            sony->publish(*this, sony->decode(bytes), changes, sink, time);
        else if (!changes.empty())
            sink.report(key, {changes, {}, {}, {}, ++cursor, time});
    }
};

struct DirectHidDevice : Device {
    ~DirectHidDevice()
    {
        if (file == INVALID_HANDLE_VALUE)
            return;
        if (pending)
        {
            CancelIoEx(file, &operation);
            DWORD ignored{};
            GetOverlappedResult(file, &operation, &ignored, TRUE);
        }
        CloseHandle(file);
    }

    bool pollReports(ReportSink& sink)
    {
        for (unsigned i = 0; i < 64; ++i)
        {
            DWORD size{};
            if (pending)
            {
                if (!GetOverlappedResult(file, &operation, &size, FALSE))
                {
                    if (GetLastError() == ERROR_IO_INCOMPLETE)
                        return true;
                    pending = false;
                    return false;
                }
                pending = false;
            }
            else
            {
                operation = {};
                if (!::ReadFile(file, input.data(), static_cast<DWORD>(input.size()), &size, &operation))
                {
                    pending = GetLastError() == ERROR_IO_PENDING;
                    return pending;
                }
            }
            if (size == 0 || size > input.size())
                return false;
            decode(std::span(input).first(size), sink, {});
        }
        return true;
    }

    HANDLE file = INVALID_HANDLE_VALUE;
    OVERLAPPED operation{};
    std::vector<char> input;
    bool pending = false;
};

void addButtons(Device& device, USHORT count)
{
    if (count == 0)
        return;
    std::vector<HIDP_BUTTON_CAPS> caps(count);
    if (HidP_GetButtonCaps(HidP_Input, caps.data(), &count, device.parser()) != HIDP_STATUS_SUCCESS)
        return;
    for (const auto& cap : std::span(caps).first(count))
    {
        if (cap.IsAlias)
            continue;
        const auto first = cap.IsRange ? cap.Range.DataIndexMin : cap.NotRange.DataIndex;
        const auto last = cap.IsRange ? cap.Range.DataIndexMax : first;
        const auto usage = cap.IsRange ? cap.Range.UsageMin : cap.NotRange.Usage;
        for (unsigned index = first; index <= last; ++index)
            device.controls.push_back({RawKind::Button, static_cast<USHORT>(index), cap.UsagePage,
                static_cast<USHORT>(usage + index - first), cap.LinkCollection, cap.ReportID});
    }
}

void addValues(Device& device, USHORT count)
{
    if (count == 0)
        return;
    std::vector<HIDP_VALUE_CAPS> caps(count);
    if (HidP_GetValueCaps(HidP_Input, caps.data(), &count, device.parser()) != HIDP_STATUS_SUCCESS)
        return;
    for (const auto& cap : std::span(caps).first(count))
    {
        if (cap.IsAlias || !cap.IsAbsolute || cap.BitSize == 0 || cap.BitSize > 32 || cap.LogicalMin >= cap.LogicalMax)
            continue;
        if (!cap.IsRange && cap.ReportCount > 1)
            continue; // HidP_GetData does not return usage value arrays.
        const auto first = cap.IsRange ? cap.Range.DataIndexMin : cap.NotRange.DataIndex;
        const auto last = cap.IsRange ? cap.Range.DataIndexMax : first;
        const auto minimum = cap.IsRange ? cap.Range.UsageMin : cap.NotRange.Usage;
        for (unsigned index = first; index <= last; ++index)
        {
            const auto usage = static_cast<USHORT>(minimum + index - first);
            const bool hat = cap.UsagePage == HID_USAGE_PAGE_GENERIC && usage == HID_USAGE_GENERIC_HATSWITCH;
            device.controls.push_back({hat ? RawKind::Hat : RawKind::Axis, static_cast<USHORT>(index),
                cap.UsagePage, usage, cap.LinkCollection, cap.ReportID, cap.LogicalMin, cap.LogicalMax, cap.BitSize});
        }
    }
}

std::optional<SdlInputIndices> directInputIndices(std::span<const Control> controls)
{
    // Keep vendor-defined controls in the raw layout. DirectInput mappings use
    // the standard joystick slots, with no gaps in the buttons or aliases.
    SdlInputIndices indices;
    unsigned lastAxis = 0;
    bool hasHat = false;
    for (const auto& control : controls)
    {
        if (control.page >= HID_USAGE_PAGE_VENDOR_DEFINED_BEGIN)
            continue;
        switch (control.kind)
        {
        case RawKind::Button:
            if (control.page != HID_USAGE_PAGE_BUTTON || control.usage != indices.buttons.size() + 1)
                return {};
            indices.buttons.emplace_back(control.index);
            break;
        case RawKind::Axis:
            if (control.page != HID_USAGE_PAGE_GENERIC || control.usage < HID_USAGE_GENERIC_X ||
                control.usage > HID_USAGE_GENERIC_SLIDER || control.usage <= lastAxis)
                return {};
            lastAxis = control.usage;
            indices.axes.emplace_back(SdlAxisIndex{control.index, AxisEncoding::Signed});
            break;
        case RawKind::Hat:
            if (hasHat)
                return {};
            hasHat = true;
            break;
        }
    }
    if (indices.buttons.empty())
        return {};
    return indices;
}

void describe(Device& device, std::uint16_t vendor, std::uint16_t product, std::uint16_t version, HANDLE file,
              std::optional<SonyHidModel> model, bool bluetooth)
{
    auto& descriptor = device.descriptor;
    descriptor.vendor = vendor;
    descriptor.product = product;
    descriptor.version = version;
    descriptor.name = "HID Gamepad";
    std::string manufacturer, name;
    if (file != INVALID_HANDLE_VALUE)
    {
        std::array<wchar_t, 128> text{};
        if (HidD_GetProductString(file, text.data(), sizeof(text)) && text[0])
            descriptor.name = name = winUtf8(text.data());
        text.fill(L'\0');
        if (HidD_GetManufacturerString(file, text.data(), sizeof(text)) && text[0])
            manufacturer = winUtf8(text.data());
        text.fill(L'\0');
        if (HidD_GetSerialNumberString(file, text.data(), sizeof(text)) && text[0])
            descriptor.serial = winUtf8(text.data());
    }
    if (model && name.empty())
        descriptor.name = sonyHidName(*model);
    if (model && *model != SonyHidModel::DualSense)
    {
        // This layout uses the SDL HIDAPI indices, independently of DirectInput.
        descriptor.layout.guid = DeviceGuid::make(bluetooth ? 5 : 3, vendor, product, version, manufacturer, name, 'h');
        descriptor.layout.legacyHidapi = true;
        return;
    }
    if (bluetooth)
    {
        // The Windows database identifies Sony's DirectInput layout with a USB-style GUID.
        descriptor.layout.guid = DeviceGuid::make(3, vendor, product, 0, manufacturer, name);
    }
    else if (vendor && product)
        if (auto indices = directInputIndices(device.controls))
        {
            auto& layout = descriptor.layout;
            layout.guid = DeviceGuid::make(3, vendor, product, 0, manufacturer, name);
            if (indices->buttons.size() != layout.buttonCount || indices->axes.size() != layout.axisCount)
                layout.sdlIndices = std::move(indices);
        }
}

bool initializeGenericLayout(Device& device, const HIDP_CAPS& caps)
{
    addButtons(device, caps.NumberInputButtonCaps);
    addValues(device, caps.NumberInputValueCaps);
    if (device.controls.empty())
        return false;

    std::ranges::sort(device.controls, {}, [](const Control& item) {
        return std::tuple{item.kind, item.page, item.usage, item.link, item.report, item.dataIndex};
    });
    auto& layout = device.descriptor.layout;
    layout.id = layoutId(device.controls);
    const std::array counts{&layout.buttonCount, &layout.axisCount, &layout.hatCount};
    for (auto& control : device.controls)
    {
        control.index = (*counts[static_cast<unsigned>(control.kind)])++;
        device.reportIds.set(control.report);
    }
    const auto dataFields = std::ranges::max(device.controls, {}, &Control::dataIndex).dataIndex + 1u;
    device.values.resize(dataFields);
    device.valuePresent.resize(dataFields);
    device.data.resize(HidP_MaxDataListLength(HidP_Input, device.parser()));
    device.changes.reserve(device.controls.size());
    return true;
}

void initializeXboxBluetooth(Device& device, const HIDP_CAPS& caps, std::uint16_t vendor,
                             std::uint16_t product, std::uint16_t version, HANDLE file)
{
    const auto model = xboxBluetoothModel(vendor, product);
    if (!model || hidBus(device.path) != WinHidBus::Bluetooth)
        return;
    const auto minimumInput = *model == XboxBluetoothModel::OneS ? 16 : 17;
    if (caps.InputReportByteLength < minimumInput || caps.InputReportByteLength > 64)
        return;
    const auto hasReport = [&device](HIDP_REPORT_TYPE type, UCHAR id, USHORT length) {
        std::vector<char> report(length);
        return HidP_InitializeReportForID(type, id, device.parser(), report.data(), length) == HIDP_STATUS_SUCCESS;
    };
    if (!hasReport(HidP_Input, 0x01, caps.InputReportByteLength))
        return;
    const auto outputLength = caps.OutputReportByteLength;
    const bool writable = outputLength >= XboxBluetoothOutputSize && outputLength <= 64 &&
        hasReport(HidP_Output, 0x03, outputLength);
    auto& descriptor = device.descriptor;
    auto& layout = descriptor.layout;
    describe(device, vendor, product, version, file, {}, false);
    descriptor.name = xboxBluetoothName(*model);
    descriptor.controllerType = GamepadType::XboxCompatible;
    descriptor.link = Link::Wireless;
    layout.id = "win-xbox-bluetooth-v1";
    layout.guid = DeviceGuid::make(5, vendor, product, version, {}, descriptor.name, 'h');
    configureXboxBluetoothLayout(layout, *model);
    if (*model == XboxBluetoothModel::Elite2 && caps.InputReportByteLength != 20 &&
        caps.InputReportByteLength != 39 && caps.InputReportByteLength != 55)
        std::ranges::fill(std::span(layout.buttonPresent).subspan(static_cast<unsigned>(Button::RightPaddle1)),
                          std::uint8_t{0});
    device.xbox = std::make_unique<WinXboxBluetooth>(device.path, *model, writable ? outputLength : 0);
}

bool initialize(Device& device, std::uint16_t vendor, std::uint16_t product, std::uint16_t version, HANDLE file,
                bool directHid = false)
{
    HIDP_CAPS caps{};
    if (HidP_GetCaps(device.parser(), &caps) != HIDP_STATUS_SUCCESS || caps.InputReportByteLength == 0)
        return false;
    const auto nintendo = directHid ? switchModel(vendor, product) : std::nullopt;
    const bool generic = gamepadUsage(caps.UsagePage, caps.Usage);
    if (!generic && !(nintendo && caps.UsagePage == HID_USAGE_PAGE_GENERIC && caps.Usage == 0x08))
        return false;
    auto model = sonyHidModel(vendor, product);
    const auto bus = model ? hidBus(device.path) : WinHidBus::Unknown;
    const bool bluetooth = bus == WinHidBus::Bluetooth && caps.InputReportByteLength >= 78;
    auto& descriptor = device.descriptor;
    auto& layout = descriptor.layout;
    if (nintendo && caps.InputReportByteLength >= 49)
    {
        const auto transport = hidBus(device.path);
        auto native = std::make_unique<WinSwitchGamepad>(device.path, *nintendo, transport, caps.OutputReportByteLength);
        if (native->writable())
        {
            const bool wireless = transport == WinHidBus::Bluetooth;
            describe(device, vendor, product, version, file, {}, false);
            descriptor.name = switchName(*nintendo);
            descriptor.controllerType = switchGamepadType(*nintendo);
            descriptor.link = wireless ? Link::Wireless : Link::Wired;
            layout.id = wireless ? "win-switch-bluetooth-v1" : "win-switch-usb-v1";
            layout.id += *nintendo == SwitchModel::Pro ? "/pro" :
                         *nintendo == SwitchModel::JoyConLeft ? "/left" : "/right";
            layout.guid = DeviceGuid::make(wireless ? 5 : 3, vendor, product, version, {}, descriptor.name,
                                           'h', static_cast<std::uint8_t>(*nintendo));
            layout.legacyHidapi = true;
            configureSwitchLayout(layout, *nintendo);
            device.nintendo = std::move(native);
        }
    }
    if (!device.nintendo && !generic)
        return false;
    if (directHid && generic)
        initializeXboxBluetooth(device, caps, vendor, product, version, file);
    if (!device.nintendo && !device.xbox && !bluetooth)
    {
        if (!initializeGenericLayout(device, caps))
            return false;
        // ViGEm DS4 presents the USB report layout on a software bus. Other
        // known Sony gamepads require a matching native bus and report shape.
        if (model && (caps.InputReportByteLength != 64 || !device.reportIds[0x01] ||
                      (bus != WinHidBus::Usb && !(bus == WinHidBus::Unknown && *model == SonyHidModel::DualShock4))))
            model.reset();
    }
    if (model && *model != SonyHidModel::DualSense)
    {
        layout.id = *model == SonyHidModel::DualShock4 ? "win-dualshock4" : "win-dualsense-edge";
        layout.id += bluetooth ? "-bluetooth-v1" : "-usb-v1";
        configureSonyHidLayout(layout, *model);
        device.changes.reserve(layout.buttonCount + layout.axisCount + layout.hatCount);
    }
    else if (bluetooth)
    {
        layout.id = "win-dualsense-bluetooth-v1";
        layout.buttonCount = DualSenseBaseButtonCount;
        layout.axisCount = 6;
        layout.hatCount = 1;
        device.changes.reserve(layout.buttonCount + layout.axisCount + layout.hatCount);
    }

    if (!device.nintendo && !device.xbox)
        describe(device, vendor, product, version, file, model, bluetooth);
    device.buffer.resize(caps.InputReportByteLength);
    device.state.buttons.resize(layout.buttonCount);
    device.state.axes.resize(layout.axisCount);
    device.state.axesKnown.resize(layout.axisCount);
    device.state.hats.resize(layout.hatCount);
    if (model)
    {
        device.sony = std::make_unique<WinSonyGamepad>(device.path, caps, descriptor, *model,
            bluetooth ? DualSenseTransport::Bluetooth : DualSenseTransport::Usb, bus);
        descriptor.controllerType = sonyGamepadType(*model);
    }
    return true;
}

std::optional<Device> openDevice(HANDLE handle, bool xboxOwnedByWgi)
{
    RID_DEVICE_INFO info{};
    info.cbSize = sizeof(info);
    UINT size = sizeof(info);
    if (GetRawInputDeviceInfoW(handle, RIDI_DEVICEINFO, &info, &size) == errorSize ||
        info.dwType != RIM_TYPEHID || !gamepadUsage(info.hid.usUsagePage, info.hid.usUsage) ||
        (xboxOwnedByWgi && isWinWgiXboxProduct(info.hid.dwVendorId, info.hid.dwProductId)))
        return {};
    const auto path = rawDevicePath(handle);
    Device device;
    device.path = normalizeHidPath(path);
    if (device.path.empty() || isXInputMirror(device.path))
        return {};
    size = 0;
    if (GetRawInputDeviceInfoW(handle, RIDI_PREPARSEDDATA, nullptr, &size) == errorSize || size == 0)
        return {};
    device.preparsed.resize((size + sizeof(ULONG) - 1) / sizeof(ULONG));
    if (GetRawInputDeviceInfoW(handle, RIDI_PREPARSEDDATA, device.preparsed.data(), &size) == errorSize)
        return {};
    const auto file = openHid(path, 0, FILE_ATTRIBUTE_NORMAL);
    if (!initialize(device, static_cast<std::uint16_t>(info.hid.dwVendorId),
                    static_cast<std::uint16_t>(info.hid.dwProductId),
                    static_cast<std::uint16_t>(info.hid.dwVersionNumber), file ? file.get() : INVALID_HANDLE_VALUE))
        return {};
    return device;
}

std::unique_ptr<DirectHidDevice> openInterface(const std::wstring& path, bool xboxOwnedByWgi)
{
    if (isXInputMirror(path))
        return {};
    auto device = std::make_unique<DirectHidDevice>();
    device->file = CreateFileW(path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (device->file == INVALID_HANDLE_VALUE)
        return {};
    PHIDP_PREPARSED_DATA data = nullptr;
    if (!HidD_GetPreparsedData(device->file, &data))
        return {};
    device->nativePreparsed.reset(data);
    device->path = path;
    HIDD_ATTRIBUTES attributes{};
    attributes.Size = sizeof(attributes);
    const bool identified = HidD_GetAttributes(device->file, &attributes) != FALSE;
    if (identified && xboxOwnedByWgi && isWinWgiXboxProduct(attributes.VendorID, attributes.ProductID))
        return {};
    if (!initialize(*device, attributes.VendorID, attributes.ProductID, attributes.VersionNumber,
                    identified ? device->file : INVALID_HANDLE_VALUE, true))
        return {};
    if (!identified)
    {
        device->descriptor.vendor.reset();
        device->descriptor.product.reset();
        device->descriptor.version.reset();
    }
    device->input.resize(device->buffer.size());
    CloseHandle(device->file);
    device->file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                               OPEN_EXISTING, FILE_FLAG_OVERLAPPED, nullptr);
    if (device->file == INVALID_HANDLE_VALUE)
        return {};
    return device;
}

std::optional<HidPaths> hidInterfaces()
{
    GUID type{};
    HidD_GetHidGuid(&type);
    for (unsigned attempt = 0; attempt < 3; ++attempt)
    {
        ULONG count = 0;
        if (CM_Get_Device_Interface_List_SizeW(&count, &type, nullptr, CM_GET_DEVICE_INTERFACE_LIST_PRESENT)
            != CR_SUCCESS)
            return {};
        if (count == 0)
            return HidPaths{};
        std::vector<wchar_t> paths(count);
        const auto result = CM_Get_Device_Interface_ListW(&type, nullptr, paths.data(), count,
                                                         CM_GET_DEVICE_INTERFACE_LIST_PRESENT);
        if (result == CR_SUCCESS)
        {
            HidPaths present;
            for (auto path = paths.data(); *path; path += std::char_traits<wchar_t>::length(path) + 1)
                present.insert(normalizeHidPath(path));
            return present;
        }
        if (result != CR_BUFFER_SMALL)
            break;
    }
    return {};
}

std::optional<std::vector<RAWINPUTDEVICELIST>> rawDevices()
{
    for (unsigned attempt = 0; attempt < 3; ++attempt)
    {
        UINT count = 0;
        if (GetRawInputDeviceList(nullptr, &count, sizeof(RAWINPUTDEVICELIST)) == errorSize)
            return {};
        if (count == 0)
            return std::vector<RAWINPUTDEVICELIST>{};
        std::vector<RAWINPUTDEVICELIST> list(count);
        const auto size = GetRawInputDeviceList(list.data(), &count, sizeof(RAWINPUTDEVICELIST));
        if (size != errorSize)
        {
            list.resize(size);
            return list;
        }
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            break;
    }
    return {};
}

std::optional<std::vector<RAWINPUTDEVICE>> registeredDevices()
{
    UINT count = 0;
    if (GetRegisteredRawInputDevices(nullptr, &count, sizeof(RAWINPUTDEVICE)) == errorSize &&
        GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        return {};
    std::vector<RAWINPUTDEVICE> registered(count);
    if (count)
    {
        const auto written = GetRegisteredRawInputDevices(registered.data(), &count, sizeof(RAWINPUTDEVICE));
        if (written == errorSize)
            return {};
        registered.resize(written);
    }
    return registered;
}

} // namespace


std::vector<HapticAudioIdentity> connectedHapticAudioIdentities()
{
    std::set<std::string> containers;
    if (const auto paths = hidInterfaces())
        for (const auto& path : *paths)
            if (auto id = sonyUsbHapticContainer(path); !id.empty())
                containers.insert(std::move(id));

    std::vector<HapticAudioIdentity> result;
    result.reserve(containers.size());
    for (const auto& id : containers)
        result.push_back({id, {}, false});
    return result;
}

struct WinRawHid::Impl {
    Impl(ReportSink& target, WinDirectInput* fallback, bool xboxInWgi)
        : sink(target), direct(fallback), xboxOwnedByWgi(xboxInWgi) {}

    Device* find(EndpointKey key)
    {
        for (auto& [handle, device] : devices)
            if (device.key == key)
                return &device;
        for (auto& [path, device] : interfaces)
            if (device->key == key)
                return device.get();
        return nullptr;
    }

    void publish(Device& device)
    {
        device.key = {WinRawHidId, ++nextEndpoint, 1};
        auto endpoint = device.attachment();
        if (direct)
            direct->attachRaw(device.path, std::move(endpoint));
        else
            sink.attached(endpoint.key, std::move(endpoint.descriptor), std::move(endpoint.initial));
    }

    void detach(const Device& device, bool keepPath = false)
    {
        if (direct)
            direct->detachRaw(device.path, device.key, keepPath);
        else
            sink.detached(device.key);
    }

    auto removeInterface(std::map<std::wstring, std::unique_ptr<DirectHidDevice>>::iterator device,
                         bool keepPath = false)
    {
        detach(*device->second, keepPath);
        paths.erase(device->first);
        return interfaces.erase(device);
    }

    Device* attach(HANDLE handle)
    {
        if (const auto existing = devices.find(handle); existing != devices.end())
            return &existing->second;
        if (ignored.contains(handle))
            return nullptr;
        auto device = openDevice(handle, xboxOwnedByWgi);
        if (device)
        {
            if (const auto old = interfaces.find(device->path); old != interfaces.end())
            {
                if (old->second->nintendo || old->second->xbox)
                {
                    ignored.insert(handle);
                    return nullptr;
                }
                removeInterface(old, true);
            }
            const auto& descriptor = device->descriptor;
            // Use direct overlapped reads for reply reports outside the standard HID controls.
            const auto vendor = descriptor.vendor.value_or(0), product = descriptor.product.value_or(0);
            if (switchModel(vendor, product) || xboxBluetoothModel(vendor, product))
            {
                auto native = openInterface(device->path, xboxOwnedByWgi);
                if (native && (native->nintendo || native->xbox) && paths.insert(device->path).second)
                {
                    auto& added = interfaces.emplace(device->path, std::move(native)).first->second;
                    publish(*added);
                    ignored.insert(handle);
                    return nullptr;
                }
            }
        }
        if (!device || !paths.insert(device->path).second)
        {
            ignored.insert(handle);
            return nullptr;
        }
        auto& added = devices.emplace(handle, std::move(*device)).first->second;
        publish(added);
        return &added;
    }

    void refreshInterfaces()
    {
        const auto current = hidInterfaces();
        if (!current)
            return;
        for (auto it = interfaces.begin(); it != interfaces.end();)
        {
            if (current->contains(it->first))
                ++it;
            else
                it = removeInterface(it);
        }
        for (const auto& path : *current)
        {
            if (paths.contains(path))
                continue;
            if (auto device = openInterface(path, xboxOwnedByWgi))
            {
                paths.insert(path);
                auto& added = interfaces.emplace(path, std::move(device)).first->second;
                publish(*added);
            }
        }
    }


    ReportSink& sink;
    WinDirectInput* direct;
    bool xboxOwnedByWgi;
    HWND window = nullptr;
    std::uint64_t nextEndpoint = 0;
    std::map<HANDLE, Device> devices;
    std::map<std::wstring, std::unique_ptr<DirectHidDevice>> interfaces;
    std::set<HANDLE> ignored;
    HidPaths paths;
    std::vector<std::uint64_t> input;
};

WinRawHid::WinRawHid(ReportSink& sink, WinDirectInput* direct, bool xboxOwnedByWgi)
    : _impl(std::make_unique<Impl>(sink, direct, xboxOwnedByWgi)) {}

WinRawHid::~WinRawHid()
{
    if (!_impl->window)
        return;
    auto registrations = registeredDevices();
    if (!registrations)
        return;
    std::erase_if(*registrations, [this](const auto& reg) {
        return reg.hwndTarget != _impl->window || !gamepadUsage(reg.usUsagePage, reg.usUsage);
    });
    for (auto& reg : *registrations)
    {
        reg.dwFlags = RIDEV_REMOVE;
        reg.hwndTarget = nullptr;
    }
    if (!registrations->empty())
        RegisterRawInputDevices(registrations->data(), static_cast<UINT>(registrations->size()), sizeof(RAWINPUTDEVICE));
}

bool WinRawHid::start(HWND window)
{
    auto existing = registeredDevices();
    if (!existing || std::ranges::any_of(*existing, [](const auto& reg) {
        return gamepadUsage(reg.usUsagePage, reg.usUsage);
    }))
        return false;
    std::array<RAWINPUTDEVICE, gamepadUsages.size()> registrations{};
    for (unsigned i = 0; i < registrations.size(); ++i)
        registrations[i] = {HID_USAGE_PAGE_GENERIC, gamepadUsages[i], RIDEV_INPUTSINK | RIDEV_DEVNOTIFY, window};
    if (!RegisterRawInputDevices(registrations.data(), static_cast<UINT>(registrations.size()), sizeof(RAWINPUTDEVICE)))
        return false;
    _impl->window = window;
    return true;
}

void WinRawHid::refresh()
{
    if (const auto list = rawDevices())
    {
        std::set<HANDLE> present;
        for (const auto& device : *list)
            if (device.dwType == RIM_TYPEHID)
                present.insert(device.hDevice);
        // Retry transient preparsed-data failures during enumeration.
        _impl->ignored.clear();
        for (auto it = _impl->devices.begin(); it != _impl->devices.end();)
        {
            const auto handle = (it++)->first;
            if (!present.contains(handle))
                remove(handle);
        }
        for (const auto handle : present)
            _impl->attach(handle);
    }
    _impl->refreshInterfaces();
}

void WinRawHid::read(HRAWINPUT handle)
{
    UINT size = 0;
    if (GetRawInputData(handle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == errorSize)
        return;
    constexpr auto dataOffset = offsetof(RAWINPUT, data) + offsetof(RAWHID, bRawData);
    if (size < dataOffset)
        return;
    _impl->input.resize((size + sizeof(std::uint64_t) - 1) / sizeof(std::uint64_t));
    const auto written = GetRawInputData(handle, RID_INPUT, _impl->input.data(), &size, sizeof(RAWINPUTHEADER));
    if (written == errorSize || written < dataOffset)
        return;
    const auto& input = *reinterpret_cast<const RAWINPUT*>(_impl->input.data());
    if (input.header.dwType != RIM_TYPEHID)
        return;
    const auto& hid = input.data.hid;
    if (hid.dwSizeHid == 0 || hid.dwCount > (written - dataOffset) / hid.dwSizeHid)
        return;
    const auto* packet = reinterpret_cast<const char*>(_impl->input.data()) + dataOffset;
    if (auto* device = _impl->attach(input.header.hDevice))
    {
        const ReportTime time;
        for (DWORD i = 0; i < hid.dwCount; ++i)
        {
            device->decode({packet, hid.dwSizeHid}, _impl->sink, time);
            packet += hid.dwSizeHid;
        }
    }
}

void WinRawHid::remove(HANDLE handle)
{
    _impl->ignored.erase(handle);
    const auto item = _impl->devices.find(handle);
    if (item == _impl->devices.end())
        return;
    _impl->detach(item->second);
    _impl->paths.erase(item->second.path);
    _impl->devices.erase(item);
}

void WinRawHid::pollReports()
{
    for (auto& [handle, device] : _impl->devices)
        if (device.sony)
            device.sony->pollOutput();
    for (auto it = _impl->interfaces.begin(); it != _impl->interfaces.end();)
    {
        if (it->second->pollReports(_impl->sink))
        {
            if (it->second->sony)
                it->second->sony->pollOutput();
            if (it->second->nintendo)
                it->second->nintendo->poll();
            if (it->second->xbox)
                it->second->xbox->poll();
            ++it;
        }
        else
            it = _impl->removeInterface(it);
    }
}

void WinRawHid::requestBaseline(EndpointKey key)
{
    if (const auto device = _impl->find(key))
    {
        if (device->sony)
            device->sony->resetBaseline();
        device->sendBaseline(_impl->sink);
    }
}

void WinRawHid::snapshot(std::vector<AttachedEndpoint>& endpoints)
{
    for (auto& [handle, device] : _impl->devices)
    {
        if (device.sony)
            device.sony->resetTopology();
        ++device.key.generation;
        endpoints.push_back(device.attachment());
    }
    for (auto& [path, device] : _impl->interfaces)
    {
        if (device->sony)
            device->sony->resetTopology();
        if (device->nintendo)
            device->nintendo->resetTopology();
        if (device->xbox)
            device->xbox->stop();
        ++device->key.generation;
        endpoints.push_back(device->attachment());
    }
}

void WinRawHid::setSensor(EndpointKey key, Sensor sensor, bool enabled)
{
    if (const auto device = _impl->find(key))
    {
        if (device->sony)
            device->sony->setSensor(sensor, enabled);
        if (device->nintendo)
            device->nintendo->setSensor(sensor, enabled);
    }
}

Error WinRawHid::submit(EndpointKey key, const NativeCommand& request)
{
    const auto device = _impl->find(key);
    if (!device)
        return Error::Disconnected;
    const auto command = request.commandAt(nowNs());
    if (device->xbox)
        return device->xbox->submit(command, request.bodyGate);
    if (device->nintendo)
        return device->nintendo->submit(command, request.bodyGate);
    return device->sony ? device->sony->submit(command, request.bodyGate) : Error::Unsupported;
}

Error WinRawHid::startWaveform(EndpointKey key)
{
    const auto* device = _impl->find(key);
    if (!device)
        return Error::Disconnected;
    return device->sony ? device->sony->startWaveform() : Error::Unsupported;
}

void WinRawHid::stopOutputs()
{
    for (auto& [handle, device] : _impl->devices)
        if (device.sony)
            device.sony->stopOutput();
    for (auto& [path, device] : _impl->interfaces)
    {
        if (device->sony)
            device->sony->stopOutput();
        if (device->nintendo)
            device->nintendo->stopOutput();
        if (device->xbox)
            device->xbox->stop();
    }
}

bool WinRawHid::needsPolling() const
{
    return !_impl->interfaces.empty() || std::ranges::any_of(_impl->devices, [](const auto& item) {
        return item.second.sony && item.second.sony->needsPolling();
    });
}

} // namespace cc::input::detail
