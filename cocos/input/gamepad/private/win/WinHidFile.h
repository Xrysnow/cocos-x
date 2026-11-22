#pragma once

#include "WinLegacyInput.h"

namespace cc::input::detail {

struct CloseHidHandle {
    void operator()(HANDLE handle) const { CloseHandle(handle); }
};

using HidHandle = std::unique_ptr<void, CloseHidHandle>;

inline HidHandle openHid(const std::wstring& path, DWORD access, DWORD flags)
{
    const auto handle = CreateFileW(path.c_str(), access, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                    OPEN_EXISTING, flags, nullptr);
    return HidHandle(handle != INVALID_HANDLE_VALUE ? handle : nullptr);
}

inline bool writeHid(HANDLE file, HANDLE event, std::span<const std::uint8_t> report)
{
    OVERLAPPED operation{};
    operation.hEvent = event;
    ResetEvent(event);
    DWORD count{};
    if (!WriteFile(file, report.data(), static_cast<DWORD>(report.size()), &count, &operation))
    {
        if (GetLastError() != ERROR_IO_PENDING)
            return false;
        const bool ready = WaitForSingleObject(event, 25) == WAIT_OBJECT_0;
        if (!ready)
            CancelIoEx(file, &operation);
        // A completed transfer can win the race with cancellation.
        if (!GetOverlappedResult(file, &operation, &count, ready ? FALSE : TRUE))
            return false;
    }
    return count == report.size();
}

} // namespace cc::input::detail
