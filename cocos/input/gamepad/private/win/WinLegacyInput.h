#pragma once

#include "../GamepadBackend.h"

#include <Windows.h>

#include <memory>
#include <set>
#include <string_view>

namespace cc::input::detail {

inline constexpr std::uint64_t WinXInputId = 1;
inline constexpr std::uint64_t WinRawHidId = 2;
inline constexpr std::uint64_t WinDirectInputId = 3;

using HidPaths = std::set<std::wstring, std::less<>>;

std::wstring normalizeHidPath(std::wstring_view path);
bool isXInputMirror(std::wstring_view normalizedPath);
std::string winUtf8(std::wstring_view value);
std::int16_t normalizeWinAxis(std::int64_t value, std::int64_t min, std::int64_t max);
std::uint8_t winHat(unsigned position);

struct WinInputEndpoint {
    EndpointKey key{};
    EndpointDescriptor descriptor;
    RawState state;
    std::uint64_t cursor = 0;

    AttachedEndpoint attachment(ReportTime time = {}) const
    {
        return {key, descriptor, {state, cursor, time}};
    }

    void sendBaseline(ReportSink& sink, ReportTime time = {})
    {
        sink.baseline(key, {state, ++cursor, time});
    }
};

class WinDirectInput;

class WinRawHid {
public:
    WinRawHid(ReportSink& sink, WinDirectInput* direct);
    ~WinRawHid();

    bool start(HWND window);
    void refresh();
    void read(HRAWINPUT input);
    void pollReports();
    void remove(HANDLE handle);
    void requestBaseline(EndpointKey key);
    void snapshot(std::vector<AttachedEndpoint>& endpoints);
    const HidPaths& paths() const;
    bool hasPendingReads() const;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class WinDirectInput {
public:
    explicit WinDirectInput(ReportSink& sink);
    ~WinDirectInput();

    bool start(HWND window);
    void refresh(const HidPaths& rawHidPaths);
    void dropMirror(std::wstring_view path);
    void pollReports();
    void requestBaseline(EndpointKey key);
    void snapshot(std::vector<AttachedEndpoint>& endpoints);
    bool hasDevices() const;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

enum class WinLegacyPaths { RawHid, DirectInput, Both };
std::unique_ptr<GamepadBackend> makeWinLegacyInput(WinLegacyPaths paths);

} // namespace cc::input::detail
