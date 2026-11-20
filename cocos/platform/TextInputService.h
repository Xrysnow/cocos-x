#pragma once

#include "platform/PlatformDefine.h"
#include "platform/TextInputTypes.h"

#include <chrono>
#include <functional>
#include <memory>

namespace cc
{

class TextInputBackend;
class TextInputEventSink;
namespace text_input_detail
{
struct Router;
}

CC_DLL const char* textInputErrorName(TextInputError error);

// Session and service operations are confined to the engine thread, aside from focus queries.
class CC_DLL TextInputSession
{
public:
    TextInputSession() = default;
    ~TextInputSession();
    TextInputSession(TextInputSession&& other) noexcept;
    TextInputSession& operator=(TextInputSession&& other) noexcept;

    TextInputSession(const TextInputSession&) = delete;
    TextInputSession& operator=(const TextInputSession&) = delete;

    explicit operator bool() const;
    TextInputWindowId window() const { return _window; }
    TextInputSessionId id() const { return _id; }

    TextInputError setArea(std::optional<TextInputArea> area);
    TextInputError updateState(TextInputSnapshot snapshot);
    TextInputCapabilities capabilities() const;
    TextInputState state() const;
    TextInputError requestKeyboard(bool visible);
    TextInputError cancelComposition();
    TextInputError close();

private:
    friend class TextInputService;
    TextInputSession(const std::shared_ptr<text_input_detail::Router>& router,
                     TextInputWindowId window,
                     TextInputSessionId id);
    void release();

    std::weak_ptr<text_input_detail::Router> _router;
    TextInputWindowId _window = 0;
    TextInputSessionId _id = 0;
    bool _closed = false;
};

struct TextInputBeginResult
{
    TextInputSession session;
    TextInputError error = TextInputError::none;
    explicit operator bool() const { return error == TextInputError::none; }
};

class CC_DLL TextInputService
{
public:
    using Callback = std::function<void(const TextInputEvent&)>;
    using FocusChangedCallback = std::function<void(TextInputFocus)>;
    using CoordinateTransform = std::function<std::optional<TextInputArea>(const TextInputArea&)>;

    TextInputService();
    ~TextInputService();
    TextInputService(const TextInputService&) = delete;
    TextInputService& operator=(const TextInputService&) = delete;

    TextInputBeginResult begin(TextInputWindowId window,
                               TextInputOptions options,
                               Callback onEvent,
                               TextInputInitialState initial = {});
    TextInputBeginResult beginNativeEditing(TextInputWindowId window,
                                            Callback onEvent,
                                            TextInputCapabilities capabilities = {});

    // The native window must remain valid until unregisterWindow returns.
    TextInputWindowId registerWindow(std::unique_ptr<TextInputBackend> backend,
                                      bool focused,
                                      CoordinateTransform transform = {});
    void unregisterWindow(TextInputWindowId window);
    void setWindowFocused(TextInputWindowId window, bool focused);
    void geometryChanged(TextInputWindowId window);
    void reset();

    TextInputEventSink sinkForWindow(TextInputWindowId window, bool includeNative = false) const;
    bool hasTextFocus() const;
    TextInputFocus focus() const;
    void setFocusChangedCallback(FocusChangedCallback callback);

    // Each queued event is indivisible. A callback may close or destroy a session or window.
    std::size_t dispatchPending(std::size_t maxEvents = 128,
                                std::chrono::microseconds budget = std::chrono::milliseconds(2));

private:
    TextInputBeginResult beginEditing(TextInputWindowId window,
                                      TextInputOptions options,
                                      Callback onEvent,
                                      TextInputInitialState initial,
                                      std::optional<TextInputCapabilities> nativeCapabilities);

    std::shared_ptr<text_input_detail::Router> _router;
};

}  // namespace cc
