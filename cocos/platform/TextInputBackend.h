#pragma once

#include "platform/PlatformDefine.h"
#include "platform/TextInputTypes.h"

#include <memory>

namespace cc
{

class TextInputService;
namespace text_input_detail
{
struct Channel;
struct Router;
}

// Capture this value when creating native work. Posting is safe on a platform UI thread.
class CC_DLL TextInputEventSink
{
public:
    TextInputEventSink() = default;
    explicit operator bool() const;
    TextInputWindowId window() const { return _window; }
    TextInputSessionId session() const { return _session; }

    // Async range edits must capture the epoch alongside the snapshot they read.
    std::uint64_t snapshotEpoch() const;
    bool post(TextInputPayload payload, std::uint64_t snapshotEpoch = 0) const;
    bool closed(TextInputCloseReason reason = TextInputCloseReason::requested) const;

private:
    friend class TextInputService;
    friend struct text_input_detail::Router;
    explicit TextInputEventSink(const std::shared_ptr<text_input_detail::Channel>& channel);

    std::weak_ptr<text_input_detail::Channel> _channel;
    TextInputWindowId _window = 0;
    TextInputSessionId _session = 0;
};

struct TextInputActivation
{
    TextInputEventSink sink;
    TextInputOptions options;
    TextInputInitialState initial;
};

class CC_DLL TextInputBackend
{
public:
    virtual ~TextInputBackend() = default;
    virtual TextInputCapabilities capabilities() const = 0;
    virtual TextInputCapabilities nativeEditingCapabilities() const { return {}; }
    virtual TextInputError activate(const TextInputActivation& activation) = 0;
    virtual void setArea(const std::optional<TextInputArea>& area) = 0;
    virtual void geometryChanged(const std::optional<TextInputArea>& area) { setArea(area); }
    virtual void updateSnapshot(const TextInputSnapshot& snapshot) = 0;
    virtual TextInputError requestKeyboard(bool visible) = 0;
    virtual TextInputError cancelComposition() = 0;

    // Stop accepting new edits first. Post any final messages, then close the activation's sink.
    // The backend may complete asynchronously. Its destructor must always release the native hooks.
    virtual void deactivate() = 0;
};

}  // namespace cc
