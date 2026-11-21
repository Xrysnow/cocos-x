#include "WinLegacyInput.h"

#ifndef DIRECTINPUT_VERSION
    #define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstring>
#include <map>

namespace cc::input::detail {
namespace {

constexpr DWORD bufferSize = 256;

struct ComRelease {
    void operator()(IUnknown* value) const { value->Release(); }
};

using DirectInput = std::unique_ptr<IDirectInput8W, ComRelease>;
using DirectDevice = std::unique_ptr<IDirectInputDevice8W, ComRelease>;

struct Control {
    DWORD offset;
    RawKind kind;
    LONG minimum = -32768, maximum = 32767;
    unsigned index = 0;
};

std::uint8_t pov(DWORD value)
{
    if (LOWORD(value) == 0xffff || value >= 36000)
        return 0;
    return winHat(((value + 2250) / 4500) % 8);
}

struct Device : WinInputEndpoint {
    DirectDevice native;
    std::wstring path;
    GUID instance{};
    std::vector<Control> controls;
    std::vector<RawChange> changes;
    bool buffered = false, published = false, needsBaseline = true;

    void apply(const Control& control, DWORD value)
    {
        const auto index = control.index;
        const auto update = [&](auto& current, auto next) {
            if (current != next)
            {
                current = next;
                changes.push_back({control.kind, index, next});
            }
        };
        switch (control.kind)
        {
        case RawKind::Button:
            update(state.buttons[index], static_cast<std::uint8_t>((value & 0x80) != 0));
            break;
        case RawKind::Hat:
            update(state.hats[index], pov(value));
            break;
        case RawKind::Axis:
            update(state.axes[index], normalizeWinAxis(std::bit_cast<LONG>(value), control.minimum, control.maximum));
            break;
        }
    }

    bool sample()
    {
        DIJOYSTATE2 data{};
        if (FAILED(native->GetDeviceState(sizeof(data), &data)))
            return false;
        const auto* bytes = reinterpret_cast<const std::byte*>(&data);
        changes.clear();
        for (const auto& control : controls)
        {
            DWORD value{};
            const auto size = control.kind == RawKind::Button ? sizeof(BYTE) : sizeof(DWORD);
            std::memcpy(&value, bytes + control.offset, size);
            apply(control, value);
        }
        return true;
    }

    void markGap(ReportSink& sink)
    {
        if (!needsBaseline && published)
            sink.desynchronized(key, {GapCause::DriverOverflow, {}});
        needsBaseline = true;
    }

    bool captureBaseline()
    {
        if (buffered)
        {
            DWORD discard = INFINITE;
            const auto status = native->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), nullptr, &discard, 0);
            if (status == DIERR_NOTBUFFERED)
                buffered = false;
            else if (FAILED(status))
                return false;
        }
        return sample();
    }

    void baseline(ReportSink& sink)
    {
        if (!captureBaseline())
            return;
        needsBaseline = false;
        if (published)
            sendBaseline(sink);
        else
        {
            auto endpoint = attachment();
            sink.attached(endpoint.key, std::move(endpoint.descriptor), std::move(endpoint.initial));
            published = true;
        }
    }

    void pollReports(ReportSink& sink)
    {
        auto status = native->Poll();
        if (status == DIERR_INPUTLOST || status == DIERR_NOTACQUIRED)
        {
            markGap(sink);
            if (FAILED(native->Acquire()))
                return;
            status = native->Poll();
        }
        if (FAILED(status))
        {
            markGap(sink);
            return;
        }
        if (needsBaseline)
        {
            baseline(sink);
            return;
        }
        if (!buffered)
        {
            if (!sample())
                markGap(sink);
            else if (!changes.empty())
                sink.report(key, {changes, {}, {}, {}, ++cursor, {}});
            return;
        }

        std::array<DIDEVICEOBJECTDATA, bufferSize> data{};
        auto count = bufferSize;
        status = native->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data.data(), &count, 0);
        if (status == DI_BUFFEROVERFLOW || FAILED(status))
        {
            markGap(sink);
            return;
        }
        const ReportTime time;
        for (const auto& event : std::span(data).first(count))
        {
            const auto control = std::ranges::lower_bound(controls, event.dwOfs, {}, &Control::offset);
            if (control == controls.end() || control->offset != event.dwOfs)
                continue;
            changes.clear();
            apply(*control, event.dwData);
            if (!changes.empty())
                sink.report(key, {changes, {}, {}, {}, ++cursor, time});
        }
    }
};

DIPROPDWORD deviceProperty(DWORD value = 0)
{
    return {{sizeof(DIPROPDWORD), sizeof(DIPROPHEADER), 0, DIPH_DEVICE}, value};
}

void collectControl(Device& device, DWORD offset, RawKind kind)
{
    // EnumObjects returns format-independent offsets on some HID minidrivers.
    // Resolve the installed DIJOYSTATE2 slots through DIPH_BYOFFSET instead.
    DIDEVICEOBJECTINSTANCEW object{};
    object.dwSize = sizeof(object);
    if (FAILED(device.native->GetObjectInfo(&object, offset, DIPH_BYOFFSET)))
        return;
    if (kind == RawKind::Axis)
    {
        if ((DIDFT_GETTYPE(object.dwType) & DIDFT_ABSAXIS) == 0)
            return;
        DIPROPRANGE range{{sizeof(DIPROPRANGE), sizeof(DIPROPHEADER), object.dwType, DIPH_BYID}, -32768, 32767};
        if (FAILED(device.native->SetProperty(DIPROP_RANGE, &range.diph)) &&
            FAILED(device.native->GetProperty(DIPROP_RANGE, &range.diph)))
            return;
        if (range.lMin >= range.lMax || range.lMin == DIPROPRANGE_NOMIN || range.lMax == DIPROPRANGE_NOMAX)
            return;
        DIPROPDWORD deadZone{{sizeof(DIPROPDWORD), sizeof(DIPROPHEADER), object.dwType, DIPH_BYID}, 0};
        device.native->SetProperty(DIPROP_DEADZONE, &deadZone.diph);
        device.controls.push_back({offset, kind, range.lMin, range.lMax});
    }
    else
        device.controls.push_back({offset, kind});
}

BOOL CALLBACK collectDevice(const DIDEVICEINSTANCEW* instance, void* context)
{
    static_cast<std::vector<DIDEVICEINSTANCEW>*>(context)->push_back(*instance);
    return DIENUM_CONTINUE;
}

std::wstring devicePath(IDirectInputDevice8W& device)
{
    DIPROPGUIDANDPATH path{};
    path.diph = {sizeof(path), sizeof(DIPROPHEADER), 0, DIPH_DEVICE};
    return SUCCEEDED(device.GetProperty(DIPROP_GUIDANDPATH, &path.diph)) ? normalizeHidPath(path.wszPath)
                                                                       : std::wstring{};
}

std::optional<Device> configureDevice(DirectDevice native, HWND window, const DIDEVICEINSTANCEW& instance,
                                      std::wstring path)
{
    Device device;
    device.native = std::move(native);
    device.path = std::move(path);
    device.instance = instance.guidInstance;
    auto* opened = device.native.get();
    if (FAILED(opened->SetDataFormat(&c_dfDIJoystick2)) ||
        FAILED(opened->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
        return {};
    constexpr DWORD firstButton = offsetof(DIJOYSTATE2, rgbButtons);
    constexpr DWORD firstHat = offsetof(DIJOYSTATE2, rgdwPOV);
    for (DWORD axis = 0; axis < firstHat; axis += sizeof(LONG))
        collectControl(device, axis, RawKind::Axis);
    for (DWORD hat = firstHat; hat < firstButton; hat += sizeof(DWORD))
        collectControl(device, hat, RawKind::Hat);
    for (DWORD button = firstButton; button < firstButton + 128; ++button)
        collectControl(device, button, RawKind::Button);
    if (device.controls.empty())
        return {};

    auto& descriptor = device.descriptor;
    descriptor.name = winUtf8(instance.tszProductName);
    if (descriptor.name.empty())
        descriptor.name = "DirectInput Gamepad";
    auto ids = deviceProperty();
    if (SUCCEEDED(opened->GetProperty(DIPROP_VIDPID, &ids.diph)))
    {
        descriptor.vendor = LOWORD(ids.dwData);
        descriptor.product = HIWORD(ids.dwData);
    }
    auto& layout = descriptor.layout;
    if ((instance.dwDevType & DIDEVTYPE_HID) && descriptor.vendor && descriptor.product)
    {
        const auto vendor = *descriptor.vendor;
        const auto product = *descriptor.product;
        layout.guid = DeviceGuid::make(vendor && product ? 3 : 5, vendor, product, 0, {}, descriptor.name);
    }
    layout.id = "win-directinput8-v1";
    const std::array counts{&layout.buttonCount, &layout.axisCount, &layout.hatCount};
    for (auto& control : device.controls)
    {
        control.index = (*counts[static_cast<unsigned>(control.kind)])++;
        layout.id += "/" + std::to_string(control.offset);
    }
    device.state.buttons.resize(layout.buttonCount);
    device.state.axes.resize(layout.axisCount);
    device.state.hats.resize(layout.hatCount);
    device.changes.reserve(device.controls.size());
    auto size = deviceProperty(bufferSize);
    const auto buffered = opened->SetProperty(DIPROP_BUFFERSIZE, &size.diph);
    device.buffered = SUCCEEDED(buffered) && buffered != DI_POLLEDDEVICE;
    opened->Acquire();
    return device;
}

} // namespace

struct WinDirectInput::Impl {
    explicit Impl(ReportSink& target) : sink(target) {}

    ReportSink& sink;
    DirectInput input;
    HWND window = nullptr;
    std::uint64_t nextEndpoint = 0;
    std::map<std::wstring, Device> devices;
};

WinDirectInput::WinDirectInput(ReportSink& sink) : _impl(std::make_unique<Impl>(sink)) {}
WinDirectInput::~WinDirectInput() = default;

bool WinDirectInput::start(HWND window)
{
    IDirectInput8W* input = nullptr;
    if (FAILED(DirectInput8Create(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W,
                                  reinterpret_cast<LPVOID*>(&input), nullptr)))
        return false;
    _impl->input.reset(input);
    _impl->window = window;
    return true;
}

void WinDirectInput::refresh(const HidPaths& rawHidPaths)
{
    std::vector<DIDEVICEINSTANCEW> list;
    if (FAILED(_impl->input->EnumDevices(DI8DEVCLASS_GAMECTRL, collectDevice, &list, DIEDFL_ATTACHEDONLY)))
        return;
    HidPaths present;
    for (const auto& instance : list)
    {
        IDirectInputDevice8W* created = nullptr;
        if (FAILED(_impl->input->CreateDevice(instance.guidInstance, &created, nullptr)))
            continue;
        DirectDevice native(created);
        auto path = devicePath(*native);
        if (isXInputMirror(path) || rawHidPaths.contains(path))
            continue;
        if (path.empty() && (instance.dwDevType & DIDEVTYPE_HID))
            continue; // HID devices without a provable interface could mirror another backend.
        std::array<wchar_t, 40> guid{};
        StringFromGUID2(instance.guidInstance, guid.data(), static_cast<int>(guid.size()));
        const auto identity = path.empty() ? std::wstring(guid.data()) : path;
        if (!present.insert(identity).second)
            continue;
        auto current = _impl->devices.find(identity);
        if (current != _impl->devices.end() && current->second.instance == instance.guidInstance)
            continue;
        auto opened = configureDevice(std::move(native), _impl->window, instance, std::move(path));
        if (!opened)
            continue;
        if (current == _impl->devices.end())
        {
            opened->key = {WinDirectInputId, ++_impl->nextEndpoint, 1};
            _impl->devices.emplace(identity, std::move(*opened));
            continue;
        }
        auto& old = current->second;
        if (old.descriptor.layout.id == opened->descriptor.layout.id)
        {
            old.markGap(_impl->sink);
            opened->key = old.key;
            opened->cursor = old.cursor;
            opened->published = old.published;
        }
        else
        {
            if (old.published)
                _impl->sink.detached(old.key);
            opened->key = {WinDirectInputId, ++_impl->nextEndpoint, 1};
        }
        old = std::move(*opened);
    }
    std::erase_if(_impl->devices, [&](const auto& entry) {
        const auto& [id, device] = entry;
        if (present.contains(id))
            return false;
        if (device.published)
            _impl->sink.detached(device.key);
        return true;
    });
}

void WinDirectInput::pollReports()
{
    for (auto& [id, device] : _impl->devices)
        device.pollReports(_impl->sink);
}

void WinDirectInput::dropMirror(std::wstring_view path)
{
    std::erase_if(_impl->devices, [&](const auto& entry) {
        const auto& device = entry.second;
        if (device.path != path)
            return false;
        if (device.published)
            _impl->sink.detached(device.key);
        return true;
    });
}

void WinDirectInput::requestBaseline(EndpointKey key)
{
    for (auto& [id, device] : _impl->devices)
        if (device.key == key)
            device.needsBaseline = true;
}

void WinDirectInput::snapshot(std::vector<AttachedEndpoint>& endpoints)
{
    for (auto& [id, device] : _impl->devices)
    {
        ++device.key.generation;
        device.published = device.captureBaseline();
        device.needsBaseline = !device.published;
        if (device.published)
            endpoints.push_back(device.attachment());
    }
}

bool WinDirectInput::hasDevices() const { return !_impl->devices.empty(); }

} // namespace cc::input::detail
