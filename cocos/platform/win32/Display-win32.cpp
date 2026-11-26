#include "platform/DisplayInternal.h"
#include "platform/desktop/GLViewImpl-desktop.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"
#include <shellscalingapi.h>
#include <string_view>
#pragma comment(lib, "Shcore.lib")

namespace cc::display {
namespace {
std::string utf8(std::wstring_view s)
{
    int n = WideCharToMultiByte(CP_UTF8, 0, s.data(), int(s.size()), nullptr, 0, nullptr, nullptr);
    std::string result(n, 0);
    if (n) WideCharToMultiByte(CP_UTF8, 0, s.data(), int(s.size()), result.data(), n, nullptr, nullptr);
    return result;
}
DisplayRect rect(const RECT& r) { return {r.left, r.top, r.right - r.left, r.bottom - r.top}; }
BOOL CALLBACK collect(HMONITOR monitor, HDC, LPRECT, LPARAM data)
{
    MONITORINFOEXW info{};
    info.cbSize = sizeof(info);
    if (!GetMonitorInfoW(monitor, &info)) return FALSE;
    DISPLAY_DEVICEW device{};
    device.cb = sizeof(device);
    for (DWORD index = 0; EnumDisplayDevicesW(nullptr, index, &device, 0); ++index) {
        if (!_wcsicmp(device.DeviceName, info.szDevice) && (device.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER))
            return TRUE;
    }
    reinterpret_cast<Keys*>(data)->push_back(reinterpret_cast<Key>(monitor));
    return TRUE;
}
void targetMode(const wchar_t* source, DisplayInfo& info)
{
    UINT32 paths = 0, modes = 0;
    if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &paths, &modes) != ERROR_SUCCESS) return;
    std::vector<DISPLAYCONFIG_PATH_INFO> path(paths);
    std::vector<DISPLAYCONFIG_MODE_INFO> mode(modes);
    if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &paths, path.data(), &modes, mode.data(), nullptr) != ERROR_SUCCESS) return;
    const DISPLAYCONFIG_PATH_TARGET_INFO* target = nullptr;
    for (UINT32 i = 0; i < paths; ++i) {
        const auto& src = path[i].sourceInfo;
        DISPLAYCONFIG_SOURCE_DEVICE_NAME name{};
        name.header = {DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME, sizeof(name), src.adapterId, src.id};
        if (DisplayConfigGetDeviceInfo(&name.header) || _wcsicmp(source, name.viewGdiDeviceName)) continue;
        if (target) return; // Multiple targets mirror this logical source.
        target = &path[i].targetInfo;
    }
    if (!target) return;
    auto rate = target->refreshRate;
    if (rate.Numerator && rate.Denominator) info.refreshRateHz = double(rate.Numerator) / rate.Denominator;
    DISPLAYCONFIG_TARGET_DEVICE_NAME name{};
    name.header = {DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME, sizeof(name), target->adapterId, target->id};
    if (!DisplayConfigGetDeviceInfo(&name.header) && name.monitorFriendlyDeviceName[0])
        info.name = utf8(name.monitorFriendlyDeviceName);
}
}
std::optional<Keys> enumerate()
{
    Keys keys;
    if (!EnumDisplayMonitors(nullptr, nullptr, collect, reinterpret_cast<LPARAM>(&keys))) return {};
    return keys;
}
Key primary() { return reinterpret_cast<Key>(MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY)); }
std::optional<DisplayInfo> read(Key key)
{
    auto monitor = reinterpret_cast<HMONITOR>(key);
    MONITORINFOEXW data{};
    data.cbSize = sizeof(data);
    if (!GetMonitorInfoW(monitor, &data)) return {};
    DisplayInfo info;
    info.coordinateSpace = DisplayCoordinateSpace::Desktop;
    info.geometry = rect(data.rcMonitor);
    info.availableGeometry = rect(data.rcWork);
    info.name = utf8(data.szDevice);
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    if (EnumDisplaySettingsExW(data.szDevice, ENUM_CURRENT_SETTINGS, &mode, 0)) {
        if (mode.dmPelsWidth && mode.dmPelsHeight && mode.dmPelsWidth <= INT32_MAX && mode.dmPelsHeight <= INT32_MAX)
            info.pixelSize = DisplaySize{int(mode.dmPelsWidth), int(mode.dmPelsHeight)};
        if (mode.dmDisplayFrequency > 1) info.refreshRateHz = mode.dmDisplayFrequency;
    }
    targetMode(data.szDevice, info);
    // Older Windows releases do not export the per-thread awareness APIs.
    static auto context = reinterpret_cast<decltype(&GetThreadDpiAwarenessContext)>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "GetThreadDpiAwarenessContext"));
    static auto awareness = reinterpret_cast<decltype(&GetAwarenessFromDpiAwarenessContext)>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "GetAwarenessFromDpiAwarenessContext"));
    const bool perMonitorAware = context && awareness && awareness(context()) == DPI_AWARENESS_PER_MONITOR_AWARE;
    UINT dpiX = 0, dpiY = 0;
    if (perMonitorAware) info.devicePixelRatio = 1.0;
    if (perMonitorAware && SUCCEEDED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) && dpiX && dpiY) {
        info.logicalDpi = DisplayAxisValues{double(dpiX), double(dpiY)};
        info.contentScale = DisplayAxisValues{dpiX / 96.0, dpiY / 96.0};
    } else {
        DEVICE_SCALE_FACTOR scale;
        if (SUCCEEDED(GetScaleFactorForMonitor(monitor, &scale)) && scale > 0) {
            const double factor = double(scale) / 100;
            info.contentScale = DisplayAxisValues{factor, factor};
        }
    }
    return info;
}
}

namespace cc {
std::optional<DisplayInfo> GLViewImpl::getCurrentDisplayInfo() const
{
    if (!_mainWindow) return {};
    HWND window = glfwGetWin32Window(_mainWindow);
    return window ? display::snapshot(reinterpret_cast<display::Key>(MonitorFromWindow(window, MONITOR_DEFAULTTONULL))) : std::nullopt;
}

GLFWmonitor* GLViewImpl::resolveDisplayMonitor(DisplayId id)
{
    auto key = display::keyForId(id);
    MONITORINFOEXW data{};
    data.cbSize = sizeof(data);
    if (!key || !GetMonitorInfoW(reinterpret_cast<HMONITOR>(key), &data)) return nullptr;
    auto source = display::utf8(data.szDevice);
    int count = 0;
    auto list = glfwGetMonitors(&count);
    GLFWmonitor* result = nullptr;
    for (int i = 0; i < count; ++i) {
        auto adapter = glfwGetWin32Adapter(list[i]);
        if (!adapter || source != adapter) continue;
        if (result) return nullptr;
        result = list[i];
    }
    return result;
}
}
