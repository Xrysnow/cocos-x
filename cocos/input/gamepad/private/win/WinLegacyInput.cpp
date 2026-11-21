#include "WinLegacyInput.h"

#include <cfgmgr32.h>
#include <objbase.h>
#include <initguid.h>
#include <devpkey.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <future>
#include <mutex>
#include <thread>
#include <utility>

namespace cc::input::detail {
namespace {

using namespace std::chrono_literals;
using Clock = std::chrono::steady_clock;

std::wstring lowerAscii(std::wstring_view text)
{
    std::wstring result(text);
    for (auto& c : result)
        if (c >= L'A' && c <= L'Z')
            c += L'a' - L'A';
    return result;
}

bool hasXInputMarker(std::wstring_view id)
{
    return id.find(L"&ig_") != std::wstring_view::npos ||
           id.starts_with(L"xusb\\") || id.starts_with(L"xinput\\");
}

bool hasXInputProperty(DEVINST node, const DEVPROPKEY& key)
{
    std::array<wchar_t, 2048> property{};
    ULONG size = sizeof(property) - sizeof(wchar_t);
    DEVPROPTYPE type{};
    if (CM_Get_DevNode_PropertyW(node, &key, &type, reinterpret_cast<PBYTE>(property.data()), &size, 0)
        != CR_SUCCESS)
        return false;
    if (type != DEVPROP_TYPE_STRING && type != DEVPROP_TYPE_STRING_LIST)
        return false;
    for (const auto* value = property.data(); *value; value += std::char_traits<wchar_t>::length(value) + 1)
    {
        const auto id = lowerAscii(value);
        if (hasXInputMarker(id) || id == L"xinputhid" || id == L"xusb21" || id == L"xusb22")
            return true;
    }
    return false;
}

class WinLegacyInput final : public GamepadBackend {
public:
    explicit WinLegacyInput(WinLegacyPaths paths) : _paths(paths) {}
    ~WinLegacyInput() override { stop(); }

    Error start(ReportSink& sink) override
    {
        if (_worker.joinable())
            return Error::Busy;
        _wake = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        if (!_wake)
            return Error::BackendFailure;
        std::promise<Error> ready;
        auto status = ready.get_future();
        try
        {
            _worker = std::thread([this, &sink, ready = std::move(ready)]() mutable {
                run(sink, ready);
            });
        }
        catch (const std::system_error&)
        {
            stop();
            return Error::BackendFailure;
        }
        const auto result = status.get();
        if (result != Error::None)
            stop();
        return result;
    }

    void stop() noexcept override
    {
        if (_worker.joinable())
        {
            {
                std::lock_guard lock(_mutex);
                _quit = true;
            }
            SetEvent(_wake);
            _worker.join();
        }
        if (_wake)
            CloseHandle(std::exchange(_wake, nullptr));
        _quit = false;
        _topology = false;
        _baselines.clear();
    }

    void setActive(bool) override {}

    void requestBaseline(EndpointKey key) override
    {
        {
            std::lock_guard lock(_mutex);
            _baselines.insert(key);
        }
        SetEvent(_wake);
    }

    void requestTopology() override
    {
        {
            std::lock_guard lock(_mutex);
            _topology = true;
        }
        SetEvent(_wake);
    }

    Error submit(EndpointKey, const NativeCommand&) override { return Error::Unsupported; }

private:
    static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM kind, LPARAM param)
    {
        if (message == WM_NCCREATE)
        {
            const auto* creation = reinterpret_cast<const CREATESTRUCTW*>(param);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(creation->lpCreateParams));
        }
        auto* self = reinterpret_cast<WinLegacyInput*>(GetWindowLongPtrW(window, GWLP_USERDATA));
        if (self)
        {
            if (message == WM_INPUT && self->_raw)
                self->_raw->read(reinterpret_cast<HRAWINPUT>(param));
            else if (message == WM_INPUT_DEVICE_CHANGE || message == WM_DEVICECHANGE)
            {
                if (message == WM_INPUT_DEVICE_CHANGE && kind == GIDC_REMOVAL && self->_raw)
                    self->_raw->remove(reinterpret_cast<HANDLE>(param));
                self->_rescan = true;
            }
        }
        return DefWindowProcW(window, message, kind, param);
    }

    void run(ReportSink& sink, std::promise<Error>& ready)
    {
        const auto com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        const HINSTANCE module = GetModuleHandleW(nullptr);
        // Use a separate class per backend instance so creation and teardown
        // cannot disturb another instance's private window.
        const std::wstring name = L"CocosGamepadInput" + std::to_wstring(reinterpret_cast<std::uintptr_t>(this));
        WNDCLASSW windowClass{};
        windowClass.lpfnWndProc = windowProc;
        windowClass.hInstance = module;
        windowClass.lpszClassName = name.c_str();
        if (RegisterClassW(&windowClass))
        {
            if (const HWND window = CreateWindowExW(0, name.c_str(), L"", WS_POPUP, 0, 0, 0, 0,
                                                    nullptr, nullptr, module, this))
            {
                runWindow(sink, ready, window);
                DestroyWindow(window);
            }
            else
                ready.set_value(Error::BackendFailure);
            UnregisterClassW(name.c_str(), module);
        }
        else
            ready.set_value(Error::BackendFailure);
        if (SUCCEEDED(com))
            CoUninitialize();
    }

    void runWindow(ReportSink& sink, std::promise<Error>& ready, HWND window)
    {
        if (_paths != WinLegacyPaths::RawHid)
        {
            _direct = std::make_unique<WinDirectInput>(sink);
            if (!_direct->start(window))
                _direct.reset();
        }
        if (_paths != WinLegacyPaths::DirectInput)
        {
            _raw = std::make_unique<WinRawHid>(sink, _direct.get());
            if (!_raw->start(window))
                _raw.reset();
        }
        if (!_raw && !_direct)
        {
            ready.set_value(Error::Unsupported);
            return;
        }
        ready.set_value(Error::None);
        HidPaths empty;
        auto lastScan = Clock::time_point{};
        auto nextPoll = Clock::time_point{};
        for (;;)
        {
            std::set<EndpointKey> baselines;
            bool topology;
            {
                std::lock_guard lock(_mutex);
                if (_quit)
                    break;
                topology = std::exchange(_topology, false);
                _baselines.swap(baselines);
            }
            const auto now = Clock::now();
            if (topology || _rescan || now - lastScan >= 1s)
            {
                _rescan = false;
                lastScan = now;
                if (_raw)
                    _raw->refresh();
                if (_direct)
                    _direct->refresh(_raw ? _raw->paths() : empty);
            }
            if (topology)
            {
                std::vector<AttachedEndpoint> endpoints;
                if (_raw)
                    _raw->snapshot(endpoints);
                if (_direct)
                    _direct->snapshot(endpoints);
                sink.topology(std::move(endpoints));
            }
            for (const auto& key : baselines)
            {
                if (key.backend == WinRawHidId && _raw)
                    _raw->requestBaseline(key);
                if (key.backend == WinDirectInputId && _direct)
                    _direct->requestBaseline(key);
            }
            if (_direct && now >= nextPoll)
            {
                _direct->pollReports();
                nextPoll = now + 4ms;
            }
            if (_raw)
                _raw->pollReports();
            const bool polling = (_direct && _direct->hasDevices()) || (_raw && _raw->hasPendingReads());
            const DWORD timeout = polling ? 4 : 1000;
            MsgWaitForMultipleObjectsEx(1, &_wake, timeout, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
            // Bound one visit so a busy HID cannot starve DI or shutdown.
            MSG message{};
            for (unsigned i = 0; i < 128 && PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE); ++i)
                DispatchMessageW(&message);
        }
        _raw.reset();
        _direct.reset();
    }

    WinLegacyPaths _paths;
    HANDLE _wake = nullptr;
    std::thread _worker;
    std::mutex _mutex;
    std::set<EndpointKey> _baselines;
    bool _quit = false, _topology = false;
    bool _rescan = true;
    std::unique_ptr<WinRawHid> _raw;
    std::unique_ptr<WinDirectInput> _direct;
};

} // namespace

std::wstring normalizeHidPath(std::wstring_view path)
{
    auto normalized = lowerAscii(path);
    if (normalized.starts_with(L"\\\\.\\"))
        normalized[2] = L'?';
    return normalized;
}

bool isXInputMirror(std::wstring_view path)
{
    if (hasXInputMarker(path))
        return true;
    if (path.empty())
        return false;
    std::wstring terminated(path);
    std::array<wchar_t, MAX_DEVICE_ID_LEN> instance{};
    ULONG size = sizeof(instance) - sizeof(wchar_t);
    DEVPROPTYPE type{};
    if (CM_Get_Device_Interface_PropertyW(terminated.c_str(), &DEVPKEY_Device_InstanceId, &type,
            reinterpret_cast<PBYTE>(instance.data()), &size, 0) != CR_SUCCESS)
        return false;
    DEVINST node{};
    if (CM_Locate_DevNodeW(&node, instance.data(), CM_LOCATE_DEVNODE_NORMAL) != CR_SUCCESS)
        return false;
    return hasXInputMarker(lowerAscii(instance.data())) ||
           hasXInputProperty(node, DEVPKEY_Device_HardwareIds) ||
           hasXInputProperty(node, DEVPKEY_Device_CompatibleIds) ||
           hasXInputProperty(node, DEVPKEY_Device_Service) ||
           hasXInputProperty(node, DEVPKEY_Device_UpperFilters);
}

std::string winUtf8(std::wstring_view value)
{
    if (value.empty())
        return {};
    const auto length = static_cast<int>(value.size());
    const int size = WideCharToMultiByte(CP_UTF8, 0, value.data(), length, nullptr, 0, nullptr, nullptr);
    std::string utf8(static_cast<std::size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, value.data(), length, utf8.data(), size, nullptr, nullptr);
    return utf8;
}

std::int16_t normalizeWinAxis(std::int64_t value, std::int64_t min, std::int64_t max)
{
    if (min >= max)
        return 0;
    return static_cast<std::int16_t>((std::clamp(value, min, max) - min) * 65535 / (max - min) - 32768);
}

std::uint8_t winHat(unsigned position)
{
    constexpr std::array<std::uint8_t, 8> hats{1, 3, 2, 6, 4, 12, 8, 9};
    return position < hats.size() ? hats[position] : 0;
}

std::unique_ptr<GamepadBackend> makeWinLegacyInput(WinLegacyPaths paths)
{
    return std::make_unique<WinLegacyInput>(paths);
}

} // namespace cc::input::detail
