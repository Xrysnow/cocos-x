#include "WinLegacyInput.h"
#include "../drivers/DualSenseReports.h"

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

struct CloseHidHandle {
    void operator()(HANDLE handle) const { CloseHandle(handle); }
};

using HidHandle = std::unique_ptr<void, CloseHidHandle>;

HidHandle openHid(std::wstring_view path, DWORD access, DWORD flags)
{
    const std::wstring terminated(path);
    const auto handle = CreateFileW(terminated.c_str(), access, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                   OPEN_EXISTING, flags, nullptr);
    return HidHandle(handle != INVALID_HANDLE_VALUE ? handle : nullptr);
}

class WinDualSense {
public:
    WinDualSense(const std::wstring& path, const HIDP_CAPS& hid, EndpointDescriptor& descriptor)
        : _outputLength(hid.OutputReportByteLength)
    {
        descriptor.link = Link::Wired;
        auto& caps = descriptor.capabilities;
        caps.fingersPerPad = {2};
        // Windows pads feature reads to the collection's longest feature report.
        constexpr std::size_t calibrationLength = 41;
        if (hid.FeatureReportByteLength >= calibrationLength)
            if (const auto feature = openHid(path, GENERIC_READ, FILE_ATTRIBUTE_NORMAL))
            {
                std::vector<std::uint8_t> buffer(hid.FeatureReportByteLength);
                buffer.front() = 0x05;
                if (HidD_GetFeature(feature.get(), buffer.data(), static_cast<ULONG>(buffer.size())))
                    _calibration = decodeDualSenseCalibration(DualSenseTransport::Usb,
                                                              std::span(buffer).first(calibrationLength));
            }
        if (_calibration)
        {
            caps.sensors.set(static_cast<unsigned>(Sensor::Gyro));
            caps.sensors.set(static_cast<unsigned>(Sensor::Accel));
        }
        if (_output.encode(DualSenseTransport::Usb, _outputLength).empty())
            return;
        _writable = openHid(path, GENERIC_WRITE, FILE_FLAG_OVERLAPPED);
        if (_writable)
            _written.reset(CreateEventW(nullptr, TRUE, FALSE, nullptr));
        if (!_written)
            return;
        for (auto feature : {Feature::BodyRumble, Feature::RgbLed, Feature::PlayerLights,
                             Feature::AdaptiveLeft, Feature::AdaptiveRight})
            caps.features.set(static_cast<unsigned>(feature));
        caps.playerLightMask = 31;
        caps.triggerLimits = {TriggerLimits{true, true, 1, 255}, TriggerLimits{true, true, 1, 255}};
    }

    ~WinDualSense() { stopOutput(); }

    void setSensor(Sensor sensor, bool enabled)
    {
        if (_calibration && (sensor == Sensor::Gyro || sensor == Sensor::Accel))
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

    void publish(WinInputEndpoint& endpoint, std::span<const char> packet, std::span<const RawChange> changes,
                 ReportSink& sink, ReportTime time)
    {
        const auto bytes = std::span(reinterpret_cast<const std::uint8_t*>(packet.data()), packet.size());
        const auto sample = decodeDualSenseInput(DualSenseTransport::Usb, bytes, _calibration);
        std::vector<Contact> contacts;
        std::array<Motion, 2> motion{};
        unsigned motionCount = 0;
        std::optional<Power> power;
        if (sample)
        {
            contacts = dualSenseTouchChanges(_fingers, sample->fingers);
            _fingers = sample->fingers;
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

    Error submit(const OutputCommand& command)
    {
        if (!_written)
            return Error::Unsupported;
        const auto* stop = std::get_if<Stop>(&command);
        const bool stopAll = stop && stop->channel == Channel::All;
        if (_resetOutput && !stopAll)
            return Error::Busy;
        auto next = _output;
        if (!next.apply(command, nowNs()))
            return Error::Unsupported;
        if (!write(next))
            return Error::BackendFailure;
        _output = next;
        _hasOutput = !stopAll && (_hasOutput || !stop);
        _resetOutput = false;
        return Error::None;
    }

    void stopOutput()
    {
        if (_hasOutput)
        {
            DualSenseOutput neutral;
            if (write(neutral))
            {
                _output = neutral;
                _hasOutput = false;
            }
        }
        _resetOutput = _hasOutput;
    }

    bool needsPolling() const { return _resetOutput || _output.hasTimedRumble(); }

    void pollOutput()
    {
        if (_resetOutput)
            stopOutput();
        else if (_output.hasTimedRumble())
        {
            auto next = _output;
            if (next.expire(nowNs()) && write(next))
                _output = next;
        }
    }

private:
    bool write(DualSenseOutput& output)
    {
        const auto report = output.encode(DualSenseTransport::Usb, _outputLength);
        OVERLAPPED operation{};
        operation.hEvent = _written.get();
        ResetEvent(operation.hEvent);
        DWORD count{};
        if (!WriteFile(_writable.get(), report.data(), static_cast<DWORD>(report.size()), &count, &operation))
        {
            if (GetLastError() != ERROR_IO_PENDING)
                return false;
            // A stalled write must not hold up input polling or a focus-loss stop.
            const bool ready = WaitForSingleObject(operation.hEvent, 25) == WAIT_OBJECT_0;
            if (!ready)
                CancelIoEx(_writable.get(), &operation);
            // A completed transfer can win the race with cancellation.
            if (!GetOverlappedResult(_writable.get(), &operation, &count, ready ? FALSE : TRUE))
                return false;
        }
        return count == report.size();
    }

    HidHandle _writable, _written;
    unsigned _outputLength;
    DualSenseOutput _output;
    std::optional<DualSenseCalibration> _calibration;
    std::array<std::optional<Contact>, 2> _fingers{};
    std::bitset<SensorCount> _sensors;
    bool _refreshPower = true, _hasOutput = false, _resetOutput = false;
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
    std::unique_ptr<WinDualSense> dualSense;

    PHIDP_PREPARSED_DATA parser()
    {
        return nativePreparsed ? nativePreparsed.get() : reinterpret_cast<PHIDP_PREPARSED_DATA>(preparsed.data());
    }

    void decode(std::span<const char> packet, ReportSink& sink, ReportTime time)
    {
        if (packet.empty() || packet.size() > buffer.size())
            return;
        const auto report = static_cast<unsigned char>(packet.front());
        if (!reportIds[report])
            return;
        const auto input = packet;
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
        if (dualSense)
            dualSense->publish(*this, input, changes, sink, time);
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
                if (!ReadFile(file, input.data(), static_cast<DWORD>(input.size()), &size, &operation))
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

void describe(Device& device, std::uint16_t vendor, std::uint16_t product, std::uint16_t version, HANDLE file)
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
    if (vendor && product)
        if (auto indices = directInputIndices(device.controls))
        {
            auto& layout = descriptor.layout;
            layout.guid = DeviceGuid::make(3, vendor, product, 0, manufacturer, name);
            if (indices->buttons.size() != layout.buttonCount || indices->axes.size() != layout.axisCount)
                layout.sdlIndices = std::move(indices);
        }
    if (vendor == 0x054c && product == 0x0ce6 && device.buffer.size() == 64 && device.reportIds[0x01] &&
        isUsbHidDevice(device.path))
    {
        HIDP_CAPS hid{};
        if (HidP_GetCaps(device.parser(), &hid) == HIDP_STATUS_SUCCESS)
            device.dualSense = std::make_unique<WinDualSense>(device.path, hid, descriptor);
    }
}

bool initialize(Device& device)
{
    HIDP_CAPS caps{};
    if (HidP_GetCaps(device.parser(), &caps) != HIDP_STATUS_SUCCESS ||
        !gamepadUsage(caps.UsagePage, caps.Usage) || caps.InputReportByteLength == 0)
        return false;
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
    device.buffer.resize(caps.InputReportByteLength);
    device.changes.reserve(device.controls.size());
    device.state.buttons.resize(layout.buttonCount);
    device.state.axes.resize(layout.axisCount);
    device.state.axesKnown.resize(layout.axisCount);
    device.state.hats.resize(layout.hatCount);
    return true;
}

std::optional<Device> openDevice(HANDLE handle)
{
    RID_DEVICE_INFO info{};
    info.cbSize = sizeof(info);
    UINT size = sizeof(info);
    if (GetRawInputDeviceInfoW(handle, RIDI_DEVICEINFO, &info, &size) == errorSize ||
        info.dwType != RIM_TYPEHID || !gamepadUsage(info.hid.usUsagePage, info.hid.usUsage))
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
    if (GetRawInputDeviceInfoW(handle, RIDI_PREPARSEDDATA, device.preparsed.data(), &size) == errorSize ||
        !initialize(device))
        return {};
    const auto file = CreateFileW(path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    describe(device, static_cast<std::uint16_t>(info.hid.dwVendorId), static_cast<std::uint16_t>(info.hid.dwProductId),
             static_cast<std::uint16_t>(info.hid.dwVersionNumber), file);
    if (file != INVALID_HANDLE_VALUE)
        CloseHandle(file);
    return device;
}

std::unique_ptr<DirectHidDevice> openInterface(const std::wstring& path)
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
    if (!initialize(*device))
        return {};
    device->path = path;
    HIDD_ATTRIBUTES attributes{};
    attributes.Size = sizeof(attributes);
    if (HidD_GetAttributes(device->file, &attributes))
        describe(*device, attributes.VendorID, attributes.ProductID, attributes.VersionNumber, device->file);
    else
        device->descriptor.name = "HID Gamepad";
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

struct WinRawHid::Impl {
    Impl(ReportSink& target, WinDirectInput* fallback) : sink(target), direct(fallback) {}

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
        auto device = openDevice(handle);
        if (device)
            if (const auto old = interfaces.find(device->path); old != interfaces.end())
                removeInterface(old, true);
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
            if (auto device = openInterface(path))
            {
                paths.insert(path);
                auto& added = interfaces.emplace(path, std::move(device)).first->second;
                publish(*added);
            }
        }
    }

    ReportSink& sink;
    WinDirectInput* direct;
    HWND window = nullptr;
    std::uint64_t nextEndpoint = 0;
    std::map<HANDLE, Device> devices;
    std::map<std::wstring, std::unique_ptr<DirectHidDevice>> interfaces;
    std::set<HANDLE> ignored;
    HidPaths paths;
    std::vector<std::uint64_t> input;
};

WinRawHid::WinRawHid(ReportSink& sink, WinDirectInput* direct) : _impl(std::make_unique<Impl>(sink, direct)) {}

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
        if (device.dualSense)
            device.dualSense->pollOutput();
    for (auto it = _impl->interfaces.begin(); it != _impl->interfaces.end();)
    {
        if (it->second->pollReports(_impl->sink))
        {
            if (it->second->dualSense)
                it->second->dualSense->pollOutput();
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
        if (device->dualSense)
            device->dualSense->resetBaseline();
        device->sendBaseline(_impl->sink);
    }
}

void WinRawHid::snapshot(std::vector<AttachedEndpoint>& endpoints)
{
    for (auto& [handle, device] : _impl->devices)
    {
        if (device.dualSense)
            device.dualSense->resetTopology();
        ++device.key.generation;
        endpoints.push_back(device.attachment());
    }
    for (auto& [path, device] : _impl->interfaces)
    {
        if (device->dualSense)
            device->dualSense->resetTopology();
        ++device->key.generation;
        endpoints.push_back(device->attachment());
    }
}

void WinRawHid::setSensor(EndpointKey key, Sensor sensor, bool enabled)
{
    if (const auto device = _impl->find(key); device && device->dualSense)
        device->dualSense->setSensor(sensor, enabled);
}

Error WinRawHid::submit(EndpointKey key, const OutputCommand& command)
{
    const auto device = _impl->find(key);
    if (!device)
        return Error::Disconnected;
    return device->dualSense ? device->dualSense->submit(command) : Error::Unsupported;
}

void WinRawHid::stopOutputs()
{
    for (auto& [handle, device] : _impl->devices)
        if (device.dualSense)
            device.dualSense->stopOutput();
    for (auto& [path, device] : _impl->interfaces)
        if (device->dualSense)
            device->dualSense->stopOutput();
}

bool WinRawHid::needsPolling() const
{
    return !_impl->interfaces.empty() || std::ranges::any_of(_impl->devices, [](const auto& item) {
        return item.second.dualSense && item.second.dualSense->needsPolling();
    });
}

} // namespace cc::input::detail
