# Native file dialogs and document access

Use `cc::FileDialog` in C++ or `cc.FileDialog` in Lua to let a user open files, choose a folder, or export a file through the system picker. A selection gives the application a document handle. Keep that handle to read the file or work inside the selected folder. If a library requires a filename, import the selected file into app storage first.

| What the application needs | Operation | What success gives you |
| --- | --- | --- |
| Read one or more user-selected files | `openFiles` | A document handle for each file. C++ can read through `withReadStream`. |
| Give a path to a decoder or reopen a file on the next launch | `importFile` | A new, app-owned file with a local path. |
| Open a project that references sibling assets | `pickFolder`, then `listChildren` | A directory grant and handles for its children. Selecting the project file alone may grant access only to that file. |
| Create a file in a previously selected folder | `exportChild` | A new child. An existing entry with the same name is preserved. |
| Let the user save a copy of finished content | `exportFile` | The outcome of exporting a snapshot of the source. |
| Choose a desktop save location before generating content | `chooseSaveTarget`, then `writeTarget` | A `SaveTarget` for a later write. The file is created or replaced during that write. |

The picker is enabled by default. Set `-DCC_ENABLE_FILE_DIALOG=OFF` to build the public API with an unavailable picker. Once the Director and its view are active, check both `capabilities().available` and the operation flag before enabling a UI command. Some capabilities depend on the running Activity or desktop portal. The public C++ declarations are in [FileDialog.h](../cocos/platform/FileDialog.h) and [Document.h](../cocos/io/core/Document.h).

## Lua filter presets and shortcuts

Install the contents of the engine's Lua `script` directory under `cocos/` on the Lua search path. In both cocos-x and LuaSTG-x, `require("cocos.init")` installs the shortcuts on `cc.FileDialog`. Hosts can also load `require("cocos.cocos2d.FileDialog")` after registering the native bindings. The module returns the same `cc.FileDialog` table. [Lua module](../cocos/scripting/lua-bindings/script/cocos2d/FileDialog.lua)

| Shortcut | Use |
| --- | --- |
| `dialog.openFile(filter, callback)` | Pick one file. Call `dialog.openFile(callback)` to accept any type. |
| `dialog.openMultiple(filter, callback)` | Pick one or more files with the same filter. The callback-only form accepts any type. |
| `dialog.openFolder(callback)` | Pick a directory. Its handle is in `result.documents[1]`. |
| `dialog.exportAs(source, suggestedName, callback)` | Export a document handle under a suggested filename, including its extension. The callback receives the native export result. |

Use a preset such as `dialog.filters.image()` or pass your own single filter table. Each preset returns a fresh table, so you can translate its label or edit its types for one call. The shortcuts return the native request, or `nil, error` on submission failure. Use `openFiles` with an options table for named filter groups, an initial directory, or a custom selection limit.

| Preset | Extensions |
| --- | --- |
| `image()` | png, jpg, jpeg, gif, webp, bmp |
| `audio()` | wav, mp3, ogg, flac, m4a |
| `video()` | mp4, mov, webm |
| `font()` | ttf, otf, ttc |
| `text()` | txt |
| `json()` | json |
| `lua()` | lua |
| `zip()` | zip |

## Open a file for a path-based loader in Lua

Call this function from an engine UI event. It opens the system picker and copies the selection into the app's persistent imports directory. `onPath` receives the path to the completed copy. User cancellation leaves the current document open.

```lua
local dialog = cc.FileDialog

local function importTextFile(onPath, onError)
    local function imported(result)
        if result.status == "error" then
            onError(result.error.message)
        elseif result.status == "ok" then
            local path, err = result.documents[1]:tryGetLocalPath()
            if path then
                onPath(path)
            else
                onError(err and err.message or "Imported file has no local path")
            end
        end
    end

    local picker, err = dialog.openFile(dialog.filters.text(), function(selection)
        if selection.status == "error" then
            onError(selection.error.message)
        elseif selection.status == "ok" then
            local copy, copyError = dialog.importFile(
                selection.documents[1], { maxBytes = 8 * 1024 * 1024 }, imported)
            if not copy then onError(copyError.message) end
        end
    end)
    if not picker then onError(err.message) end
end
```

Both steps can fail at submission or later in the callback. For a scene-owned button, keep the current request, switch it from the picker to the import when copying starts, and cancel it on scene exit. Guard callbacks that touch widgets against the scene having closed. The [runnable Lua example](../templates/Resources/main.lua) shows this handoff and how to prevent a second tap from opening another picker.

For multiple selection, set `allowMultiple = true` and iterate over `result.documents`. `maxSelectionCount` defaults to 256. An oversized selection fails with `LimitExceeded`. Use extension strings such as `"txt"` without a leading dot or wildcard. Filters guide the picker. Validate file contents in the decoder. When a backend reports `selectedFilter`, the index starts at zero in C++ and one in Lua.

## Export an existing file in C++

Finish writing and close the source before calling this function on the engine thread. Pass an absolute UTF-8 path to an app-readable file. The returned request lets the owner cancel the export while it is pending.

```cpp
#include "platform/FileDialog.h"
#include <cstdio>

std::optional<cc::DialogRequest> exportReplay(const std::string& finishedReplayPath)
{
    auto source = cc::DocumentAccess::fromLocalPath(finishedReplayPath);
    if (!source) {
        std::fputs("Invalid replay path\n", stderr);
        return {};
    }

    cc::ExportFileOptions options;
    options.suggestedName = "session.replay";
    options.contentType.extensions = {"replay"};
    auto submission = cc::FileDialog::exportFile(options, source, [](cc::ExportResult result) {
        if (result.effect == cc::ExternalEffect::PartialPossible ||
            result.effect == cc::ExternalEffect::Unknown) {
            std::fputs("Check the destination before retrying the export.\n", stderr);
        }
        if (result.status == cc::DialogStatus::Error) {
            std::fprintf(stderr, "Export failed: %s\n", result.error.message.c_str());
        } else if (result.status == cc::DialogStatus::Ok) {
            std::puts("Export completed.");
        }
    });
    if (!submission.request) {
        std::fprintf(stderr, "Could not start export: %s\n", submission.error.message.c_str());
    }
    return submission.request;
}
```

The service copies the source into an app-owned temporary file before showing the picker. Snapshot creation is asynchronous. If you generated the source specifically for export, keep it readable and unchanged until the completion callback, then discard it if appropriate. The system receives stable bytes even on iOS where Files takes over the copy. Use a single filename in `suggestedName`. `ExportResult::destination` is optional. The display name can be empty when the provider returns only the destination folder.

**To preserve an existing file on iOS, enter an unused filename in Save As.** On iPhone and iPad simulators running iOS 27.2, choosing **Keep Both** in the local Files provider replaced the existing file and reported `Committed`. Entering a different name preserved the original and produced a byte-identical export. This behavior was reproduced with the local simulator provider.

## Document handles, paths and directory grants

- A `DocumentHandle` retains its provider and can be copied beyond the selection callback. `kind()`, `displayName()`, `size()` and `accessHints()` describe it. In Lua these fields come from `document:info()`. Size can be unknown. Check the actual result of every read, listing or write because a provider can revoke access.
- `tryGetLocalPath()` returns an absolute UTF-8 path when ordinary file APIs can use it. An empty optional or Lua `nil` is normal for an Android document URI or a security-scoped Apple URL. The overload taking a `FileDialogError&` and Lua's second return value distinguish encoding failure. Persist an imported copy if you need access across launches. An Android URI string or a display name alone carries no grant.
- C++ callers can use `DocumentAccess::withReadStream(document, reader, completion)` to avoid copying. The reader runs on the I/O worker while the provider grant is active. Use the borrowed `io::Stream&` only inside the reader, handle short reads and unknown length, and return a `FileDialogError` on failure or `{}` on success. Update the scene in the engine-thread completion. Lua exposes the import operation for readers that need a local file.
- Start `listChildren` with an empty page token. Pass the returned `nextPage` once with the **same directory handle** to continue. Stop when C++ returns an empty token or Lua omits it. Valid page sizes are 1–1024. The current implementation snapshots up to 8192 entries and retains up to eight unfinished listings. Restart from the first page if a token expires. Use child handles to descend into subdirectories.
- Omitting the import destination creates a new file under persistent app storage. An explicit destination must be an absolute filename in a writable directory. Imports and `exportChild` create new files exclusively. A desktop `SaveTarget` can represent a confirmed replacement. Another process can change that location before the write. Use `writeTarget` to apply the captured overwrite decision and handle a change detected during the write.

## Request lifetime, cancellation and write outcomes

Submit and cancel on the engine thread. With the default parent, the service binds the request to the Director's current `GLView` at submission. A C++ host with a second window can use `DialogParent::registerView(view)`, set `options.parent`, and call `invalidate()` before closing that window.

An immediate rejection returns an empty `DialogSubmission::request` and an error, or `nil, error` in Lua. An accepted request delivers one terminal callback on a later engine frame while the engine session and callback context remain alive. Check the callback even when submission succeeded. Picker availability, a busy window and many option errors are reported there. Dropping the request handle leaves the operation running. Session shutdown discards late callbacks.

| Result of `request.cancel()` in C++ | What the caller should do |
| --- | --- |
| `Accepted` | Expect a caller-cancelled result. The native UI may still be closing. A second picker can report `Busy` until the first exits. |
| `TooLate` | The operation has entered its write or system handoff phase. Wait for its actual outcome. On iOS the user can still cancel in Files. |
| `AlreadyFinished` | The request has already reached a terminal state or its session has ended. |

Lua uses `request:cancel()` and returns `"accepted"`, `"tooLate"` or `"alreadyFinished"`. For writes, inspect both `status` and `effect`. `None` means no reported external effect. `Committed` means the system or provider accepted the write. Cloud synchronization can finish later. With `PartialPossible` or `Unknown`, inspect the destination before retrying. For diagnostics, log the structured error's `code`, `message`, `nativeDomain` and `nativeCode`.

## How the service fits into the engine

The Director starts the session, registers its view and drains native completions once per frame. A session owns one native picker slot and a bounded serial I/O queue. Platform backends handle presentation and user decisions. Document providers handle reading, listing and writing under the platform's permissions. This keeps a blocking provider read off the render thread and lets a callback start another document operation. A full queue reports `Busy`. [Session and dispatch](../cocos/platform/FileDialog.cpp) · [Document providers](../cocos/io/core/Document.cpp) · [Transfer implementation](../cocos/io/core/DocumentTransfer.cpp)

On Apple platforms the provider opens the security scope and coordinates access with `NSFileCoordinator` around the actual I/O. On Android the provider uses the Storage Access Framework URI grant and can receive a pipe with no seek support. Keeping those details inside the provider lets the same caller read local files, sandboxed files and streamed documents. [Apple provider](../cocos/io/core/Document-apple.mm) · [Android provider](../cocos/platform/android/jni/FileDialog-android.cpp)

Transfers default to 512 MiB and a 300-second I/O timeout. Waiting for the user in the picker has no transfer deadline. Set `maxBytes` and `timeoutSeconds` in `TransferLimits` to suit the format. Lua takes these under `options.limits` for `exportFile` and directly on the options table for `importFile`, `exportChild` and `writeTarget`. A native provider call can outlive a reported timeout. The export keeps its staged snapshot until the backend releases it. The service uses leases to recover abandoned snapshot files. [Snapshot management](../cocos/io/core/DocumentStaging.cpp)

## Platform integration and tested scope

| Platform | Host requirements and observed behavior |
| --- | --- |
| Windows | The Common Item Dialog runs on a dedicated COM STA and uses the engine window as its owner. x64 Debug coverage includes multi-select, UNC paths, long-path I/O, overwrite confirmation and focus recovery. |
| macOS | AppKit presents a sheet on the engine window. A sandboxed host needs `com.apple.security.files.user-selected.read-only` for opening or `com.apple.security.files.user-selected.read-write` for exporting. Use document access for external grants. File selection and byte transfers were exercised both with and without App Sandbox. |
| Android | The Storage Access Framework grants access through the picker without a broad storage permission. Custom Activities must preserve the `CocosActivity` result and lifecycle hooks. Initial-directory hints require API 26+. The system picker can remain open after caller cancellation. API 24 emulator and API 31 device tests included real document operations. On the tested API 24 filesystem, an exclusive import preserves existing files, but another reader can see the new file while it is being copied. |
| iOS | An enabled picker requires an iOS 14+ deployment target and an active foreground `UIWindowScene` for the engine view. iOS 27.2 iPhone and iPad simulators exercised Files selection, directory grants, exports, cancellation and foreground recovery. Physical devices, iCloud and third-party cloud providers remain unverified. See the **Keep Both** result above. |
| Linux | Build with libdbus-1. At runtime the picker requires a session bus, XDG Desktop Portal and a FileChooser backend. Portal v3 enables folder selection and v4 adds initial-directory hints. Capability probing is asynchronous. A Wayland parent needs xdg-foreign v2, and the engine's current Linux rendering path uses X11. Linux runtime acceptance is pending. |

For host build commands and signing examples, see the [platform template guide](../templates/README.md). The [Lua binding implementation](../cocos/scripting/lua-bindings/manual/cclua_file_dialog.cpp) lists the exported functions and result fields.
