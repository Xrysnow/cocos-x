#include "platform/FileDialogInternal.h"
#include "platform/GLView.h"

#include <ShObjIdl.h>
#include <ShlObj.h>
#include <climits>
#include <mutex>
#include <thread>

namespace cc::dialog {
namespace {
template<class T>
struct ComRelease {
    void operator()(T* p) const { p->Release(); }
};
template<class T>
using ComPtr = std::unique_ptr<T, ComRelease<T>>;

struct ShellFree {
    void operator()(wchar_t* p) const { CoTaskMemFree(p); }
};

NativeResult failure(DialogErrorCode code, const char* message, HRESULT hr = S_OK)
{
    NativeResult result;
    result.error = {code, message, FAILED(hr) ? "hresult" : "", hr};
    return result;
}

NativeResult comFailure(HRESULT hr, const char* message)
{
    auto code = DialogErrorCode::BackendError;
    if (hr == E_ACCESSDENIED) code = DialogErrorCode::PermissionDenied;
    if (hr == E_OUTOFMEMORY) code = DialogErrorCode::OutOfMemory;
    if (hr == REGDB_E_CLASSNOTREG) code = DialogErrorCode::Unavailable;
    if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) || hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND))
        code = DialogErrorCode::NotFound;
    return failure(code, message, hr);
}

NativeResult cancelled(CancelReason reason)
{
    NativeResult result;
    result.status = DialogStatus::Cancelled;
    result.cancelReason = reason;
    return result;
}

bool wide(const std::string& text, std::wstring& out)
{
    if (text.empty()) {
        out.clear();
        return true;
    }
    if (text.size() > INT_MAX || text.find('\0') != std::string::npos)
        return false;
    auto size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                                    static_cast<int>(text.size()), nullptr, 0);
    if (!size) return false;
    out.resize(size);
    return MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(),
                               static_cast<int>(text.size()), out.data(), size) == size;
}

struct FilterSpecs {
    struct Filter {
        std::wstring label, pattern;
        std::optional<uint32_t> originalIndex;
    };
    std::vector<Filter> filters;
    std::vector<COMDLG_FILTERSPEC> specs;

    bool populate(const OpenFileOptions& options)
    {
        for (uint32_t index = 0; index < options.filters.size(); ++index) {
            const auto& item = options.filters[index];
            if (item.extensions.empty()) continue;
            Filter filter;
            filter.originalIndex = index;
            if (!wide(item.label, filter.label)) return false;
            for (const auto& extension : item.extensions) {
                std::wstring part;
                if (!wide(extension, part)) return false;
                if (!filter.pattern.empty()) filter.pattern += L";";
                filter.pattern += L"*." + part;
            }
            filters.push_back(std::move(filter));
        }
        if (!filters.empty() && options.allowAllFiles)
            filters.push_back({L"All files", L"*.*", {}});
        for (const auto& filter : filters)
            specs.push_back({filter.label.c_str(), filter.pattern.c_str()});
        return true;
    }
};

HRESULT shellPath(IShellItem* item, std::filesystem::path& path)
{
    PWSTR rawPath = nullptr;
    auto hr = item->GetDisplayName(SIGDN_FILESYSPATH, &rawPath);
    std::unique_ptr<wchar_t, ShellFree> allocation(rawPath);
    if (FAILED(hr)) return hr;
    if (!rawPath || !*rawPath) return E_UNEXPECTED;
    path = rawPath;
    return S_OK;
}

NativeResult readSelection(IFileDialog* dialog, IFileOpenDialog* open, const NativeRequest& request,
                           const FilterSpecs& filters)
{
    NativeResult result;
    UINT index = 0;
    if (!filters.specs.empty() && SUCCEEDED(dialog->GetFileTypeIndex(&index)) &&
        index && index <= filters.filters.size())
        result.selectedFilter = filters.filters[index - 1].originalIndex;
    if (open && request.operation == Operation::Open && request.options.allowMultiple) {
        IShellItemArray* raw = nullptr;
        auto hr = open->GetResults(&raw);
        ComPtr<IShellItemArray> selection(raw);
        if (FAILED(hr)) return comFailure(hr, "Could not read dialog selection");
        DWORD count = 0;
        hr = selection->GetCount(&count);
        if (FAILED(hr)) return comFailure(hr, "Could not count selected files");
        if (count == 0) return failure(DialogErrorCode::InvalidResult, "No files selected");
        if (count > request.options.maxSelectionCount)
            return failure(DialogErrorCode::LimitExceeded, "Too many files selected");
        result.documents.reserve(count);
        for (DWORD i = 0; i < count; ++i) {
            IShellItem* rawItem = nullptr;
            hr = selection->GetItemAt(i, &rawItem);
            ComPtr<IShellItem> item(rawItem);
            if (FAILED(hr)) return comFailure(hr, "Could not read selected file");
            std::filesystem::path path;
            hr = shellPath(item.get(), path);
            if (FAILED(hr)) return failure(DialogErrorCode::InvalidResult, "Selected item has no file path", hr);
            result.documents.push_back(localDocument(path, DocumentKind::File));
            if (!result.documents.back())
                return failure(DialogErrorCode::InvalidResult, "Selected file path is invalid");
        }
    } else {
        IShellItem* raw = nullptr;
        auto hr = dialog->GetResult(&raw);
        ComPtr<IShellItem> selected(raw);
        if (FAILED(hr)) return comFailure(hr, "Could not read dialog selection");
        std::filesystem::path path;
        hr = shellPath(selected.get(), path);
        if (FAILED(hr)) return failure(DialogErrorCode::InvalidResult, "Selected item has no file path", hr);
        if (open) {
            result.documents.push_back(request.operation == Operation::Folder ? localSelectedDirectory(path) :
                                       localDocument(path, DocumentKind::File));
            if (!result.documents.back())
                return failure(DialogErrorCode::InvalidResult, "Selected item path is invalid");
        } else {
            result.target = localSaveLocation(path);
            if (!result.target)
                return failure(DialogErrorCode::IoError, "Could not inspect the selected save target");
            result.displayName = result.target.displayName();
        }
    }
    result.status = DialogStatus::Ok;
    return result;
}

constexpr UINT wake = WM_APP + 1;
constexpr UINT_PTR cancelTimer = 1;

HWND dialogWindow(IFileDialog& dialog)
{
    IOleWindow* raw = nullptr;
    if (FAILED(dialog.QueryInterface(IID_PPV_ARGS(&raw)))) return nullptr;
    ComPtr<IOleWindow> window(raw);
    HWND handle = nullptr;
    if (FAILED(window->GetWindow(&handle)) || !handle) return nullptr;
    return GetAncestor(handle, GA_ROOT);
}

HWND ownedPrompt(IFileDialog& dialog)
{
    struct Prompts { HWND dialog, prompt = nullptr; } prompts{dialogWindow(dialog)};
    if (!prompts.dialog) return nullptr;
    EnumThreadWindows(GetCurrentThreadId(), [](HWND window, LPARAM context) -> BOOL {
        if (!IsWindowVisible(window) || !IsWindowEnabled(window)) return TRUE;
        wchar_t type[16]{};
        GetClassNameW(window, type, _countof(type));
        if (std::wstring_view(type) != L"#32770") return TRUE;
        auto& prompts = *reinterpret_cast<Prompts*>(context);
        for (auto owner = GetWindow(window, GW_OWNER); owner; owner = GetWindow(owner, GW_OWNER)) {
            if (owner == prompts.dialog) {
                prompts.prompt = window;
                return FALSE;
            }
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(&prompts));
    return prompts.prompt;
}

// A standard native message box gives the STA a cancellable No command even
// while the shell is waiting in its nested overwrite confirmation loop.
class ConfirmOverwrite final : public IFileDialogEvents {
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID id, void** out) override
    {
        if (!out) return E_POINTER;
        if (id == IID_IUnknown || id == IID_IFileDialogEvents) {
            *out = static_cast<IFileDialogEvents*>(this);
            AddRef();
            return S_OK;
        }
        *out = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() override { return InterlockedIncrement(&_references); }
    ULONG STDMETHODCALLTYPE Release() override
    {
        const auto count = InterlockedDecrement(&_references);
        if (!count) delete this;
        return count;
    }
    HRESULT STDMETHODCALLTYPE OnFileOk(IFileDialog*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnFolderChanging(IFileDialog*, IShellItem*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnFolderChange(IFileDialog*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnSelectionChange(IFileDialog*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE* response) override
    {
        *response = FDESVR_DEFAULT;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnTypeChange(IFileDialog*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnOverwrite(IFileDialog* dialog, IShellItem*, FDE_OVERWRITE_RESPONSE* response) override
    {
        auto owner = dialogWindow(*dialog);
        auto choice = owner ? MessageBoxW(owner, L"A file with that name already exists. Replace it?",
                                          L"Replace existing file", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) : IDNO;
        *response = choice == IDYES ? FDEOR_ACCEPT : FDEOR_REFUSE;
        return S_OK;
    }
private:
    LONG _references = 1;
};

struct Advice {
    IFileDialog* dialog = nullptr;
    DWORD cookie = 0;
    ~Advice() { if (dialog) dialog->Unadvise(cookie); }
};

class DialogThread {
public:
    void submit(NativeRequest request, NativeCallback callback, HWND owner)
    {
        std::unique_lock lock(_mutex);
        if (_stopping || _pending || _activeId) {
            lock.unlock();
            callback(failure(DialogErrorCode::Busy, "Another Windows file dialog is active"));
            return;
        }
        _pending.emplace(Command{std::move(request), std::move(callback), owner});
        if (!_worker.joinable()) {
            try {
                _worker = std::thread([this] { run(); });
            } catch (const std::system_error&) {
                reject(lock, failure(DialogErrorCode::Unavailable, "Could not start file dialog STA"));
            }
        } else if (_startupError != S_OK) {
            reject(lock, comFailure(_startupError, "Could not initialize file dialog STA"));
        } else if (_control && !PostMessageW(_control, wake, 0, 0)) {
            auto hr = HRESULT_FROM_WIN32(GetLastError());
            reject(lock, comFailure(hr, "Could not post file dialog request"));
        }
    }

    void cancel(uint64_t id)
    {
        std::lock_guard lock(_mutex);
        if ((_pending && _pending->request.id == id) || _activeId == id) {
            _cancelledId = id;
            if (_control) SendNotifyMessageW(_control, wake, 0, 0);
        }
    }

    void shutdown()
    {
        {
            std::lock_guard lock(_mutex);
            if (!_worker.joinable() || _stopping) return;
            _stopping = true;
            if (_control) SendNotifyMessageW(_control, wake, 0, 0);
        }
        // The dialog may send WM_ENABLE to its GLFW owner during dismissal.
        // Dispatch sent messages without taking application messages out of GLFW's queue.
        auto workerHandle = _worker.native_handle();
        for (;;) {
            const auto ready = MsgWaitForMultipleObjectsEx(1, &workerHandle, 100, QS_SENDMESSAGE, MWMO_INPUTAVAILABLE);
            if (ready == WAIT_OBJECT_0 + 1) {
                MSG message;
                PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE | PM_QS_SENDMESSAGE);
            } else if (ready == WAIT_TIMEOUT) {
                std::lock_guard lock(_mutex);
                if (_control && _activeId) SendNotifyMessageW(_control, wake, 0, 0);
            } else {
                break;
            }
        }
        _worker.join();
        std::lock_guard lock(_mutex);
        _stopping = false;
        _startupError = S_OK;
    }

private:
    struct Command {
        NativeRequest request;
        NativeCallback callback;
        HWND owner;
    };

    void reject(std::unique_lock<std::mutex>& lock, NativeResult result)
    {
        if (!_pending) return;
        auto callback = std::move(_pending->callback);
        _pending.reset();
        lock.unlock();
        callback(std::move(result));
    }

    bool cancellationRequested(uint64_t id)
    {
        std::lock_guard lock(_mutex);
        return _stopping || _cancelledId == id;
    }

    NativeResult display(const Command& command)
    {
        const auto& request = command.request;
        if (!IsWindow(command.owner))
            return failure(DialogErrorCode::ParentClosed, "The dialog owner was closed");

        ComPtr<IFileOpenDialog> open;
        ComPtr<IFileSaveDialog> save;
        HRESULT hr;
        if (request.operation == Operation::Open || request.operation == Operation::Folder) {
            IFileOpenDialog* raw = nullptr;
            hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&raw));
            open.reset(raw);
        } else {
            IFileSaveDialog* raw = nullptr;
            hr = CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&raw));
            save.reset(raw);
        }
        if (FAILED(hr)) return comFailure(hr, "Could not create system file dialog");
        IFileDialog* dialog = open ? static_cast<IFileDialog*>(open.get()) : save.get();
        FILEOPENDIALOGOPTIONS options = 0;
        if (FAILED(hr = dialog->GetOptions(&options)))
            return comFailure(hr, "Could not read dialog settings");
        options |= FOS_FORCEFILESYSTEM | FOS_NOCHANGEDIR | FOS_PATHMUSTEXIST;
        if (open) options |= FOS_FILEMUSTEXIST;
        if (save) options |= FOS_OVERWRITEPROMPT;
        if (request.operation == Operation::Folder) options |= FOS_PICKFOLDERS;
        if (request.operation == Operation::Open && request.options.allowMultiple) options |= FOS_ALLOWMULTISELECT;
        if (FAILED(hr = dialog->SetOptions(options)))
            return comFailure(hr, "Could not set dialog options");

        std::wstring title, name;
        if (!wide(request.options.title, title) || !wide(request.suggestedName, name))
            return failure(DialogErrorCode::EncodingError, "Dialog title or file name is not valid UTF-8");
        if (!title.empty() && FAILED(hr = dialog->SetTitle(title.c_str())))
            return comFailure(hr, "Could not set dialog title");
        if (!name.empty() && FAILED(hr = dialog->SetFileName(name.c_str())))
            return comFailure(hr, "Could not set suggested file name");

        FilterSpecs filters;
        if (request.operation != Operation::Folder) {
            if (!filters.populate(request.options))
                return failure(DialogErrorCode::EncodingError, "Dialog filter is not valid UTF-8");
            if (!filters.specs.empty() &&
                FAILED(hr = dialog->SetFileTypes(static_cast<UINT>(filters.specs.size()), filters.specs.data())))
                return comFailure(hr, "Could not set dialog filters");
        }

        if (request.options.initialDirectory) {
            auto path = request.options.initialDirectory->tryGetLocalPath();
            std::wstring folder;
            if (path && wide(*path, folder)) {
                IShellItem* raw = nullptr;
                hr = SHCreateItemFromParsingName(folder.c_str(), nullptr, IID_PPV_ARGS(&raw));
                ComPtr<IShellItem> item(raw);
                if (SUCCEEDED(hr)) dialog->SetFolder(item.get());
            }
        }

        Advice advice;
        if (save) {
            ComPtr<IFileDialogEvents> confirmation(new ConfirmOverwrite);
            hr = dialog->Advise(confirmation.get(), &advice.cookie);
            if (FAILED(hr)) return comFailure(hr, "Could not register overwrite confirmation");
            advice.dialog = dialog;
        }
        if (cancellationRequested(request.id)) return cancelled(CancelReason::Caller);
        _dialog = dialog;
        hr = dialog->Show(command.owner);
        _dialog = nullptr;
        if (cancellationRequested(request.id)) return cancelled(CancelReason::Caller);
        if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED)) return cancelled(CancelReason::User);
        if (FAILED(hr)) return comFailure(hr, "System file dialog failed");
        return readSelection(dialog, open.get(), request, filters);
    }

    void dispatch()
    {
        std::unique_lock lock(_mutex);
        if (_activeId) {
            const bool close = _stopping || _activeId == _cancelledId;
            lock.unlock();
            // System overwrite and error prompts have nested modal loops. End
            // those owned windows before ending the file dialog's outer loop.
            if (close && _dialog && !_dismissing) {
                _dismissing = true;
                if (auto prompt = ownedPrompt(*_dialog)) {
                    if (auto no = GetDlgItem(prompt, IDNO))
                        PostMessageW(no, BM_CLICK, 0, 0);
                    else
                        PostMessageW(prompt, WM_CLOSE, 0, 0);
                } else {
                    _dialog->Close(HRESULT_FROM_WIN32(ERROR_CANCELLED));
                    if (auto window = dialogWindow(*_dialog); window && IsWindowVisible(window)) {
                        // Close can return before the shell finishes restoring
                        // the outer modal loop after a nested prompt.
                        PostMessageW(window, WM_COMMAND, IDCANCEL, 0);
                    }
                }
                _dismissing = false;
            }
            return;
        }
        if (!_pending) {
            if (_stopping) PostQuitMessage(0);
            return;
        }
        auto command = std::move(*_pending);
        _pending.reset();
        _activeId = command.request.id;
        const bool skip = _stopping || _activeId == _cancelledId;
        lock.unlock();

        NativeResult result;
        if (skip) {
            result = cancelled(CancelReason::Caller);
        } else {
            try {
                result = display(command);
            } catch (const std::bad_alloc&) {
                result.error.code = DialogErrorCode::OutOfMemory;
            } catch (const std::filesystem::filesystem_error&) {
                result = failure(DialogErrorCode::IoError, "Could not use the selected file path");
            }
        }
        lock.lock();
        _activeId = 0;
        _cancelledId = 0;
        if (_stopping) PostQuitMessage(0);
        lock.unlock();
        command.callback(std::move(result));
    }

    static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM w, LPARAM l)
    {
        if (message == WM_NCCREATE) {
            auto create = reinterpret_cast<const CREATESTRUCTW*>(l);
            SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
        }
        auto self = reinterpret_cast<DialogThread*>(GetWindowLongPtrW(window, GWLP_USERDATA));
        if (self && (message == wake || (message == WM_TIMER && w == cancelTimer))) {
            self->dispatch();
            return 0;
        }
        return DefWindowProcW(window, message, w, l);
    }

    void run()
    {
        auto initialize = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(initialize)) {
            std::unique_lock lock(_mutex);
            _startupError = initialize;
            reject(lock, comFailure(_startupError, "Could not initialize file dialog COM apartment"));
            return;
        }

        WNDCLASSEXW type{};
        type.cbSize = sizeof(type);
        type.lpfnWndProc = windowProc;
        type.hInstance = GetModuleHandleW(nullptr);
        type.lpszClassName = L"cocos-x.FileDialog.STA";
        const auto atom = RegisterClassExW(&type);
        const auto window = atom ? CreateWindowExW(0, MAKEINTATOM(atom), L"", 0, 0, 0, 0, 0,
                                                   HWND_MESSAGE, nullptr, type.hInstance, this) : nullptr;
        if (window && SetTimer(window, cancelTimer, 100, nullptr)) {
            {
                std::lock_guard lock(_mutex);
                _control = window;
            }
            dispatch();
            MSG message;
            while (GetMessageW(&message, nullptr, 0, 0) > 0) {
                TranslateMessage(&message);
                DispatchMessageW(&message);
            }
            KillTimer(window, cancelTimer);
        } else {
            std::unique_lock lock(_mutex);
            _startupError = HRESULT_FROM_WIN32(GetLastError());
            if (SUCCEEDED(_startupError)) _startupError = E_FAIL;
            reject(lock, comFailure(_startupError, "Could not create file dialog message window"));
        }
        {
            std::lock_guard lock(_mutex);
            _control = nullptr;
        }
        if (window) DestroyWindow(window);
        if (atom) UnregisterClassW(MAKEINTATOM(atom), type.hInstance);
        CoUninitialize();
    }

    std::mutex _mutex;
    std::thread _worker;
    std::optional<Command> _pending;
    HWND _control = nullptr;
    HRESULT _startupError = S_OK;
    uint64_t _activeId = 0, _cancelledId = 0;
    bool _stopping = false;
    IFileDialog* _dialog = nullptr; // Accessed only during dispatch in the STA.
    bool _dismissing = false;
};

DialogThread worker;
} // namespace

DialogCapabilities nativeCapabilities()
{
    DialogCapabilities caps;
    caps.backend = "win32";
    caps.available = caps.openFiles = caps.multipleFiles = caps.pickFolder = true;
    caps.exportFile = caps.chooseSaveTarget = caps.initialDirectoryHint = true;
    caps.selectedFilter = caps.physicalDismiss = true;
    return caps;
}

void presentNative(NativeRequest request, NativeCallback callback)
{
    auto owner = request.view && request.view->isOpenGLReady() ? request.view->getWin32Window() : nullptr;
    if (!owner || !IsWindow(owner)) {
        callback(failure(DialogErrorCode::ParentClosed, "The dialog owner was closed"));
        return;
    }
    worker.submit(std::move(request), std::move(callback), owner);
}

void cancelNative(uint64_t id) { worker.cancel(id); }
void shutdownNative() { worker.shutdown(); }
} // namespace cc::dialog
