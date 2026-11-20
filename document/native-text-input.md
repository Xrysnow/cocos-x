# Native text input and IME

Use `cc::TextInputService` when an engine-rendered editor needs text from the system input method (IME). The editor owns its document, selection and caret. It sends the caret and line rectangles to the system and receives committed text or edits. The OS and the user's input method control the candidate list, its placement and the on-screen keyboard. [Public API](../cocos/platform/TextInputService.h) · [Options, events and state](../cocos/platform/TextInputTypes.h)

| What you are building | Entry point |
| --- | --- |
| A standard engine-rendered field | Call `beginEditing()` and `endEditing()` on `cc::TextFieldTTF` or `cc::ui::TextField`. In Lua, an existing `ccui.TextField` exposes `field:beginEditing()` and `field:endEditing()`. The widget already forwards its caret and applies input. |
| A platform-native text control | Use `cc::ui::EditBox` and its delegate or Lua editing events. The widget exposes `openKeyboard()` and `closeKeyboard()`. Its native editor owns the text changes. |
| A custom engine-rendered editor | Call `view->getTextInputService().begin(view->getTextInputWindow(), ...)` in C++. Use committed text for simple fields. Opt into range edits when the IME needs the selection or surrounding text. |

## Start a session for a custom field

Call on the engine thread after the view has a registered input window. This single-line search field stores a `cc::TextInputSession` member named `session`. Its three editor methods replace the current selection, handle an editing command and finish editing. The field must own the handle for as long as its callback can use the field.

```cpp
#include "platform/TextInputService.h"
#include <utility>

template<class Editor>
cc::TextInputError beginSearch(cc::TextInputService& input, cc::TextInputWindowId window,
                               Editor& field, cc::TextInputArea area)
{
    cc::TextInputOptions options;
    options.returnAction = cc::TextInputAction::search;
    cc::TextInputInitialState initial;
    initial.area = area;

    auto opened = input.begin(window, options, [&field](const cc::TextInputEvent& event) {
        if (event.session != field.session.id())
            return;
        if (auto* commit = std::get_if<cc::TextInputCommit>(&event.payload))
            field.replaceSelection(commit->text);
        else if (auto* command = std::get_if<cc::TextInputCommand>(&event.payload))
            field.handleCommand(command->action);
        else if (auto* closed = std::get_if<cc::TextInputClosed>(&event.payload))
            field.editingEnded(closed->reason);
    }, initial);

    if (!opened)
        return opened.error;
    field.session = std::move(opened.session);
    return cc::TextInputError::none;
}
```

Pass the service and window ID from the field's own `GLView`. Check the returned error before using the handle. If the field should show a software keyboard, check `session.capabilities().requestKeyboard` and call `session.requestKeyboard(true)`. A successful request can precede the visibility change. For a password field, set `purpose = TextInputPurpose::password`. The service suppresses surrounding text and preedit, disables autocorrection and requests no capitalization. Other purposes, capitalization, autocorrection, multiline input and the return action are hints interpreted by the backend.

Keep the move-only session in the widget. Calling `close()` lets queued final input and then `TextInputClosed` reach the callback. Destroying or overwriting the handle disconnects its callback and requests closure. The close reason is `requested`, `replaced`, `focusLost`, `nativeEnded` or `activationFailed`. A new field in the same window replaces the old target. A session opened in an unfocused window can remain pending until that window gains focus. Read `session.state().active` to distinguish a pending target from an active editor. [Session lifetime and dispatch](../cocos/platform/TextInputService.cpp) · [Built-in field implementation](../cocos/2d/TextFieldTTF.cpp)

## Position the candidate window

Provide `initial.area` when opening the session so the IME can query the insertion point immediately. Set `caret` to the actual insertion rectangle, `line` to the current line and optional `clip` to the visible editor bounds. All three use the same coordinate space.

| `TextInputSpace` | Coordinate system |
| --- | --- |
| `window` (default) | Logical coordinates relative to the top left of the window's content, with Y increasing downwards. Desktop uses window units, UIKit uses view points, and the Android host uses dp. |
| `design` | GLView design coordinates with Y increasing upwards. The registered view transform applies the viewport, scaling and Y flip. For node-local rectangles, `cc::textInputAreaForNode(node, caret, line)` projects the geometry using the node and camera. |

Call `session.setArea(area)` when the caret moves, text wraps or scrolling changes the visible line. The view reapplies geometry on viewport changes. Use finite coordinates and nonnegative sizes. A clipped-out caret or `setArea(std::nullopt)` lets the platform use its default placement. Check `capabilities().anchor` for positioning support. For example, an X11 input method can accept ordinary text while offering no caret positioning. [Node geometry helper](../cocos/2d/TextInputGeometry.h) · [View conversion](../cocos/platform/GLView.cpp)

## Consume editor events

The callback receives a `TextInputEvent` with its window ID, session ID, per-session sequence number and a variant payload. Use one of the two document-writing paths below. An accepted range snapshot switches the session from commits to edit transactions.

| Payload | What the editor does |
| --- | --- |
| `TextInputCommit` | Insert the committed UTF-8 string once, replacing the current selection. One commit can contain multiple characters. |
| `TextInputEdit` | Apply its ordered replacements and selection as one transaction, then acknowledge it during the callback. |
| `TextInputPreedit` | With `observePreedit` enabled and supported, display the provisional text separately from the document. Its optional selection is relative to that preedit string. Clear the preview on `ended` or closure. |
| `TextInputCommand` | Handle navigation, deletion, selection, cancellation and return actions in the editor. A single-line `insertNewline` becomes the configured return action, defaulting to `done`. |
| `TextInputStateChanged` | Read observed `composing`, `imeOpen` and `keyboardVisible` as `yes`, `no` or `unknown`. A missing `occlusion` means unknown. A zero-area rectangle means known clear. Use optional `targetOcclusion` and `animationDuration` (seconds) to animate layout. |
| `TextInputClosed` | Release transient editing UI for this session, including any remaining preedit. |

### Range edits and surrounding text

Set `options.rangeEdit = true` and supply an initial `TextInputSnapshot` if the first native query should see the selection. Check `session.capabilities().rangeEdit` after opening and keep the commit handler for backends that provide basic text input. A snapshot can describe the whole document or a slice containing both selection endpoints.

- `utf8` is the slice text. `origin` is the zero-based index of its first **Unicode scalar** in the full document. `anchor`, `focus` and edit endpoints are absolute scalar positions. Preserve selection direction. A supplementary character such as 😀 counts as one scalar, four UTF-8 bytes and two UTF-16 code units. Use `cc::TextInputIndex` to convert offsets at string boundaries. [Index conversion](../cocos/platform/TextInputIndex.h)
- Check `baseRevision` against your document revision. Apply each half-open replacement `[start, end)` **in order** to a temporary model. Each operation addresses the result of the preceding one. Apply `selectionAfter` to the result and publish the whole change atomically.
- Before returning from the callback, call `session.updateState(snapshot)` with the resulting text and selection, the same slice origin, revision `baseRevision + 1` and `acknowledgedTransaction = transactionId`. If the editor rejects or changes the proposed result, send its authoritative snapshot instead. The service resynchronizes the backend when the expected acknowledgement is missing or different. Also publish a fresh revision after an application-side edit or selection change.

For example, take revision 7 with `origin = 40`, text `A😀B` and selection `{41, 42}`. Replacing `[41, 42)` with `中文` gives `A中文B`. Deleting `[43, 44)` in the same transaction then removes the `B`. For a final caret at 43 and transaction ID 12, the acknowledgement has revision 8, origin 40, text `A中文`, anchor and focus 43, and `acknowledgedTransaction = 12`.

## Event timing and host integration

Native callbacks enqueue input for their original session. Desktop `GLViewImpl::pollEvents()` first polls GLFW and then delegates to `GLView::pollEvents()` to drain text events. The Director polls the view before its scheduled update. The default drain handles up to 128 events or about 2 ms per call and finishes the current callback before checking the time budget. Keep editor callbacks short. Gameplay can keep sampling physical keys through its existing path and use `hasTextFocus()` or `focus()` to decide when to suppress shortcuts. [Desktop event pump](../cocos/platform/desktop/GLViewImpl-desktop.cpp) · [Director update order](../cocos/base/Director.cpp)

The standard views register and unregister their native window. A custom host must keep the native window alive through `unregisterWindow()`, forward focus and geometry changes, and drain the service on the engine thread. For an OS text control, `beginNativeEditing()` reserves text focus while the control delivers edits through its own delegate. This prevents duplicate insertion. A custom backend captures its activation's `TextInputEventSink` when scheduling native work and can post through it on a platform UI thread. For asynchronous range edits, capture the snapshot epoch when reading the snapshot. Post final input before closing the sink. [Backend contract](../cocos/platform/TextInputBackend.h) · [Native EditBox integration](../cocos/ui/UIEditBox/UIEditBoxImpl-common.cpp)

## Platform support

Use the session's negotiated capabilities. `observePreedit` and `rangeEdit` require both an editor opt-in and backend support. The `reconversion` flag additionally requires range editing. Check `keyboardVisibility` and `keyboardOcclusion` independently when adjusting layout. If `cancelComposition` is available, `session.cancelComposition()` discards the current composition while keeping the field open. Use `session.requestKeyboard(false)` to request that the keyboard hide. Unsupported operations return `TextInputError::unsupported`. [Session API and error names](../cocos/platform/TextInputService.h)

| Backend | Native integration and limits |
| --- | --- |
| Windows | IMM32 supports candidate positioning, observable composition, cancellation and reconversion when an input context is available. Reconversion and document-feed requests use the editor's surrounding-text snapshot. [Windows backend](../cocos/platform/win32/TextInput-win32.cpp) |
| macOS | An AppKit `NSTextInputClient` provides the candidate rectangle, marked text, range edits and composition cancellation. The responder belongs to the focused window. [AppKit backend](../cocos/platform/mac/TextInput-mac.mm) |
| Android | The host's editor and `InputConnection` bridge provide commits, preedit, range edits, caret updates, keyboard requests and cancellation. Keyboard visibility and occlusion use IME insets on API 30 and later. [Android backend](../cocos/platform/android/TextInput-android.cpp) · [Java host](../cocos/platform/android/java/src/org/cocos/lib/CocosGLSurfaceView.java) |
| iOS | UIKit's `UITextInput` responder provides marked text, replacements, caret geometry, keyboard requests and composition cancellation. Keyboard notifications can include a destination rectangle and animation duration. [UIKit backend](../cocos/platform/ios/TextInput-ios.mm) |
| Linux, X11 or Xwayland | GLFW delivers committed characters. Precise positioning additionally requires a working XIM positioned input context. Query `anchor` at runtime. This backend offers commit and command editing. [X11 backend](../cocos/platform/linux/TextInput-x11.cpp) |
| Linux, native Wayland | A compositor with `text-input-v3` and a usable seat can receive the cursor rectangle and surrounding text, and deliver preedit, commits and surrounding deletion in a `done` batch. The backend limits the surrounding slice to 4,000 UTF-8 bytes. Without the protocol, basic GLFW character input remains available. A Wayland build needs `wayland-client`, `wayland-scanner` and the v3 XML from `wayland-protocols`. [Wayland backend](../cocos/platform/linux/TextInput-wayland.cpp) · [Build dependencies](../cocos/platform/linux/TextInput-deps.cmake) |
