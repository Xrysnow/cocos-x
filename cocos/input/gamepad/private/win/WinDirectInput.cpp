#include "WinLegacyInput.h"

#ifndef DIRECTINPUT_VERSION
    #define DIRECTINPUT_VERSION 0x0800
#endif
#include <dinput.h>
#include <hidusage.h>
#include <objbase.h>

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstring>
#include <condition_variable>
#include <future>
#include <map>
#include <mutex>
#include <thread>
#include <utility>

namespace cc::input::detail {
namespace {

constexpr DWORD bufferSize = 256;
using Clock = std::chrono::steady_clock;
using namespace std::chrono_literals;

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

    void baseline(ReportSink& sink, const auto& attach)
    {
        if (!captureBaseline())
            return;
        if (published)
            sendBaseline(sink);
        else
            published = attach(*this);
        needsBaseline = !published;
    }

    void pollReports(ReportSink& sink, const auto& attach)
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
            baseline(sink, attach);
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
    Impl(ReportSink& target, HANDLE event) : sink(target), wakeWindow(event) {}

    ~Impl()
    {
        if (!worker.joinable())
            return;
        {
            std::lock_guard lock(mutex);
            stopping = true;
        }
        wake.notify_one();
        worker.join();
    }

    void run(HWND window, std::promise<bool>& ready)
    {
        const auto com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        IDirectInput8W* created = nullptr;
        if (SUCCEEDED(com) &&
            SUCCEEDED(DirectInput8Create(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W,
                                        reinterpret_cast<LPVOID*>(&created), nullptr)))
        {
            DirectInput input(created);
            ready.set_value(true);
            service(*input, window);
            devices.clear();
        }
        else
            ready.set_value(false);
        if (SUCCEEDED(com))
            CoUninitialize();
    }

    bool publish(const Device& device)
    {
        auto endpoint = device.attachment();
        std::lock_guard lock(mutex);
        if (!device.path.empty())
        {
            if (rawPaths.contains(device.path))
                return false;
            publishedPaths.insert_or_assign(device.path, device.key);
        }
        sink.attached(endpoint.key, std::move(endpoint.descriptor), std::move(endpoint.initial));
        return true;
    }

    void detach(const Device& device)
    {
        if (!device.published)
            return;
        std::lock_guard lock(mutex);
        if (!device.path.empty())
        {
            const auto found = publishedPaths.find(device.path);
            if (found == publishedPaths.end() || found->second != device.key)
                return; // Raw Input already retired this public endpoint.
            publishedPaths.erase(found);
        }
        sink.detached(device.key);
    }

    void scan(IDirectInput8W& input, HWND window, const HidPaths& rawHidPaths)
    {
        std::vector<DIDEVICEINSTANCEW> list;
        if (FAILED(input.EnumDevices(DI8DEVCLASS_GAMECTRL, collectDevice, &list, DIEDFL_ATTACHEDONLY)))
            return;
        HidPaths present;
        for (const auto& instance : list)
        {
            // DirectInput can enumerate auxiliary HID collections as game controllers.
            if ((instance.dwDevType & DIDEVTYPE_HID) &&
                (instance.wUsagePage == HID_USAGE_PAGE_CONSUMER ||
                 (instance.wUsagePage == HID_USAGE_PAGE_GENERIC && instance.wUsage == HID_USAGE_GENERIC_SYSTEM_CTL)))
                continue;
            IDirectInputDevice8W* created = nullptr;
            if (FAILED(input.CreateDevice(instance.guidInstance, &created, nullptr)))
                continue;
            DirectDevice native(created);
            auto path = devicePath(*native);
            if (rawHidPaths.contains(path) || isXInputMirror(path))
                continue;
            if (path.empty() && (instance.dwDevType & DIDEVTYPE_HID))
                continue; // HID devices without a provable interface could mirror another backend.
            std::array<wchar_t, 40> guid{};
            StringFromGUID2(instance.guidInstance, guid.data(), static_cast<int>(guid.size()));
            const auto identity = path.empty() ? std::wstring(guid.data()) : path;
            if (!present.insert(identity).second)
                continue;
            auto current = devices.find(identity);
            if (current != devices.end() && current->second.instance == instance.guidInstance)
                continue;
            auto opened = configureDevice(std::move(native), window, instance, std::move(path));
            if (!opened)
                continue;
            if (current == devices.end())
            {
                opened->key = {WinDirectInputId, ++nextEndpoint, 1};
                devices.emplace(identity, std::move(*opened));
                continue;
            }
            auto& old = current->second;
            if (old.descriptor.layout.id == opened->descriptor.layout.id)
            {
                old.markGap(sink);
                opened->key = old.key;
                opened->cursor = old.cursor;
                opened->published = old.published;
            }
            else
            {
                detach(old);
                opened->key = {WinDirectInputId, ++nextEndpoint, 1};
            }
            old = std::move(*opened);
        }
        std::erase_if(devices, [&](const auto& entry) {
            if (present.contains(entry.first))
                return false;
            detach(entry.second);
            return true;
        });
    }

    using Snapshot = std::vector<std::pair<std::wstring, AttachedEndpoint>>;

    void prepareSnapshot()
    {
        Snapshot endpoints;
        for (auto& [identity, device] : devices)
        {
            ++device.key.generation;
            device.published = device.captureBaseline();
            {
                std::lock_guard lock(mutex);
                if (!device.path.empty())
                {
                    if (rawPaths.contains(device.path))
                        device.published = false;
                    if (device.published)
                        publishedPaths.insert_or_assign(device.path, device.key);
                    else
                        publishedPaths.erase(device.path);
                }
            }
            device.needsBaseline = !device.published;
            if (device.published)
                endpoints.emplace_back(device.path, device.attachment());
        }
        std::unique_lock lock(mutex);
        pendingSnapshot = std::move(endpoints);
        awaitingPublication = true;
        SetEvent(wakeWindow);
        // Let Raw Input keep collecting while DirectInput is scanning. Once
        // ready, hold reports from the new DirectInput generation until the
        // window thread publishes the complete topology.
        wake.wait(lock, [this] { return stopping || !awaitingPublication; });
    }

    void service(IDirectInput8W& input, HWND window)
    {
        auto nextPoll = Clock::now();
        for (;;)
        {
            HidPaths rawHidPaths;
            std::set<EndpointKey> baselines, retire;
            bool rescan, topology, ownershipChanged;
            {
                std::unique_lock lock(mutex);
                const auto work = [this] {
                    return stopping || refreshRequested || pathsChanged || !baselineRequests.empty();
                };
                if (devices.empty())
                    wake.wait(lock, work);
                else
                    wake.wait_until(lock, nextPoll, work);
                if (stopping)
                    break;
                rescan = std::exchange(refreshRequested, false);
                topology = std::exchange(snapshotRequested, false);
                ownershipChanged = std::exchange(pathsChanged, false);
                if (rescan || ownershipChanged)
                    rawHidPaths = rawPaths;
                baselines.swap(baselineRequests);
                retire.swap(retired);
            }
            if (ownershipChanged)
                std::erase_if(devices, [&](const auto& entry) {
                    const auto& device = entry.second;
                    if (!rawHidPaths.contains(device.path) && !retire.contains(device.key))
                        return false;
                    detach(device);
                    return true;
                });
            if (rescan)
                scan(input, window, rawHidPaths);
            if (topology)
            {
                prepareSnapshot();
                continue;
            }
            for (auto& [identity, device] : devices)
                if (baselines.contains(device.key))
                    device.needsBaseline = true;
            const auto now = Clock::now();
            if (now >= nextPoll)
            {
                for (auto& [identity, device] : devices)
                    device.pollReports(sink, [this](const Device& entry) { return publish(entry); });
                nextPoll = now + 4ms;
            }
        }
    }

    ReportSink& sink;
    HANDLE wakeWindow;
    std::thread worker;
    std::mutex mutex;
    std::condition_variable wake;
    // Only publication and path ownership use this mutex. DirectInput COM
    // calls and device destruction always run outside it on the worker.
    HidPaths rawPaths;
    std::map<std::wstring, EndpointKey> publishedPaths;
    std::set<EndpointKey> baselineRequests, retired;
    std::optional<Snapshot> pendingSnapshot;
    bool stopping = false, refreshRequested = false, pathsChanged = false;
    bool snapshotRequested = false, awaitingPublication = false;
    std::uint64_t nextEndpoint = 0;
    std::map<std::wstring, Device> devices;
};

WinDirectInput::WinDirectInput(ReportSink& sink, HANDLE wakeWindow)
    : _impl(std::make_unique<Impl>(sink, wakeWindow)) {}
WinDirectInput::~WinDirectInput() = default;

bool WinDirectInput::start(HWND window)
{
    std::promise<bool> ready;
    auto running = ready.get_future();
    try
    {
        _impl->worker = std::thread([this, window, ready = std::move(ready)]() mutable {
            _impl->run(window, ready);
        });
    }
    catch (const std::system_error&)
    {
        return false;
    }
    return running.get();
}

void WinDirectInput::refresh()
{
    {
        std::lock_guard lock(_impl->mutex);
        _impl->refreshRequested = true;
    }
    _impl->wake.notify_one();
}

void WinDirectInput::requestBaseline(EndpointKey key)
{
    {
        std::lock_guard lock(_impl->mutex);
        _impl->baselineRequests.insert(key);
    }
    _impl->wake.notify_one();
}

void WinDirectInput::requestSnapshot()
{
    {
        std::lock_guard lock(_impl->mutex);
        _impl->refreshRequested = true;
        _impl->snapshotRequested = true;
    }
    _impl->wake.notify_one();
}

std::optional<std::vector<AttachedEndpoint>> WinDirectInput::takeSnapshot()
{
    std::lock_guard lock(_impl->mutex);
    auto pending = std::exchange(_impl->pendingSnapshot, std::nullopt);
    if (!pending)
        return {};
    std::vector<AttachedEndpoint> endpoints;
    endpoints.reserve(pending->size());
    for (auto& [path, endpoint] : *pending)
    {
        const auto found = _impl->publishedPaths.find(path);
        if (path.empty() || (found != _impl->publishedPaths.end() && found->second == endpoint.key))
            endpoints.push_back(std::move(endpoint));
    }
    return endpoints;
}

void WinDirectInput::finishSnapshot()
{
    {
        std::lock_guard lock(_impl->mutex);
        _impl->awaitingPublication = false;
    }
    _impl->wake.notify_one();
}

void WinDirectInput::attachRaw(const std::wstring& path, AttachedEndpoint endpoint)
{
    {
        std::lock_guard lock(_impl->mutex);
        const auto found = _impl->publishedPaths.find(path);
        if (found != _impl->publishedPaths.end())
        {
            _impl->retired.insert(found->second);
            _impl->sink.detached(found->second);
            _impl->publishedPaths.erase(found);
        }
        _impl->pathsChanged |= _impl->rawPaths.insert(path).second;
        _impl->sink.attached(endpoint.key, std::move(endpoint.descriptor), std::move(endpoint.initial));
    }
    _impl->wake.notify_one();
}

void WinDirectInput::detachRaw(const std::wstring& path, EndpointKey key, bool keepPath)
{
    {
        std::lock_guard lock(_impl->mutex);
        _impl->sink.detached(key);
        if (!keepPath)
            _impl->refreshRequested |= _impl->rawPaths.erase(path) != 0;
    }
    _impl->wake.notify_one();
}

} // namespace cc::input::detail
