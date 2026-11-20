#include "platform/TextInputService.h"

#include <cmath>

#include "base/ccUTF8.h"
#include "platform/TextInputBackend.h"
#include "platform/TextInputIndex.h"

#include <algorithm>
#include <atomic>
#include <deque>
#include <limits>
#include <mutex>
#include <unordered_map>
#include <utility>

namespace cc
{
namespace
{
std::atomic<std::uint64_t> nextWindowId{1};
std::atomic<std::uint64_t> nextSessionId{1};

bool validRect(const TextInputRect& rect)
{
    return std::isfinite(rect.x) && std::isfinite(rect.y) && std::isfinite(rect.width) && std::isfinite(rect.height) &&
           rect.width >= 0 && rect.height >= 0 && std::isfinite(rect.x + rect.width) &&
           std::isfinite(rect.y + rect.height);
}

bool validArea(const TextInputArea& area)
{
    return validRect(area.caret) && validRect(area.line) && (!area.clip || validRect(*area.clip));
}

bool sameRect(const TextInputRect& a, const TextInputRect& b)
{
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

bool sameArea(const std::optional<TextInputArea>& a, const std::optional<TextInputArea>& b)
{
    if (!a || !b)
        return a.has_value() == b.has_value();
    return a->space == b->space && sameRect(a->caret, b->caret) && sameRect(a->line, b->line) &&
           a->clip.has_value() == b->clip.has_value() && (!a->clip || sameRect(*a->clip, *b->clip));
}

TextInputRect intersection(const TextInputRect& a, const TextInputRect& b)
{
    const auto x = std::max(a.x, b.x);
    const auto y = std::max(a.y, b.y);
    return {x, y, std::max(0.0, std::min(a.x + a.width, b.x + b.width) - x),
            std::max(0.0, std::min(a.y + a.height, b.y + b.height) - y)};
}

bool inRange(std::size_t position, std::size_t origin, std::size_t count)
{
    return position >= origin && position - origin <= count;
}

bool sameSnapshot(const TextInputSnapshot& a, const TextInputSnapshot& b)
{
    return a.revision == b.revision && a.origin == b.origin && a.utf8 == b.utf8 && a.anchor == b.anchor &&
           a.focus == b.focus && a.acknowledgedTransaction == b.acknowledgedTransaction;
}

std::optional<TextInputSnapshot> applyEdit(const TextInputSnapshot& snapshot, const TextInputEdit& edit)
{
    if (snapshot.revision != edit.baseRevision || snapshot.revision == (std::numeric_limits<std::uint64_t>::max)())
        return std::nullopt;

    std::u32string mirror;
    if (!StringUtils::UTF8ToUTF32(snapshot.utf8, mirror))
        return std::nullopt;
    for (const auto& op : edit.operations)
    {
        std::u32string replacement;
        if (op.start > op.end || !inRange(op.start, snapshot.origin, mirror.size()) ||
            !inRange(op.end, snapshot.origin, mirror.size()) || !StringUtils::UTF8ToUTF32(op.utf8, replacement))
            return std::nullopt;
        mirror.replace(op.start - snapshot.origin, op.end - op.start, replacement);
    }
    if (!inRange(edit.selectionAfter.anchor, snapshot.origin, mirror.size()) ||
        !inRange(edit.selectionAfter.focus, snapshot.origin, mirror.size()))
        return std::nullopt;

    TextInputSnapshot predicted;
    predicted.revision = snapshot.revision + 1;
    predicted.origin = snapshot.origin;
    predicted.anchor = edit.selectionAfter.anchor;
    predicted.focus = edit.selectionAfter.focus;
    predicted.acknowledgedTransaction = edit.transactionId;
    if (!StringUtils::UTF32ToUTF8(mirror, predicted.utf8))
        return std::nullopt;
    return predicted;
}

TextInputCommandAction returnCommand(TextInputAction action)
{
    switch (action)
    {
    case TextInputAction::search: return TextInputCommandAction::search;
    case TextInputAction::send: return TextInputCommandAction::send;
    case TextInputAction::next: return TextInputCommandAction::next;
    case TextInputAction::go: return TextInputCommandAction::go;
    case TextInputAction::done:
    case TextInputAction::unspecified: return TextInputCommandAction::done;
    }
    return TextInputCommandAction::done;
}
}  // namespace

namespace text_input_detail
{
struct QueuedEvent
{
    TextInputEvent event;
    std::uint64_t snapshotEpoch;
    bool hasRangeSnapshot;
};

struct Queue
{
    std::atomic<bool> hasEvents{false};
    std::mutex mutex;
    std::deque<QueuedEvent> events;

    std::optional<QueuedEvent> pop()
    {
        std::lock_guard lock(mutex);
        if (events.empty())
            return std::nullopt;
        auto event = std::move(events.front());
        events.pop_front();
        hasEvents.store(!events.empty());
        return event;
    }
};

struct Channel
{
    Channel(TextInputWindowId windowId, TextInputSessionId sessionId, const std::shared_ptr<Queue>& queue)
        : window(windowId), session(sessionId), queue(queue)
    {}

    const TextInputWindowId window;
    const TextInputSessionId session;
    const std::weak_ptr<Queue> queue;
    std::atomic<bool> accepting{true};
    std::atomic<std::uint64_t> snapshotEpoch{1};
    std::atomic<bool> hasRangeSnapshot{false};

    // Protected by Queue::mutex, which also serializes all source messages and the close marker.
    std::optional<TextInputCloseReason> requestedReason;
    std::uint64_t nextSequence = 1;
};

struct Session
{
    std::shared_ptr<Channel> channel;
    std::shared_ptr<TextInputService::Callback> callback;
    TextInputOptions options;
    TextInputInitialState initial;
    TextInputCapabilities capabilities;
    TextInputState state;
    std::optional<TextInputSnapshot> predicted;
    std::optional<bool> keyboardRequest;
    std::uint64_t lastTransaction = 0;
    TextInputError activationError = TextInputError::none;
    bool native = false;
    bool closing = false;
    bool deactivationStarted = false;
};

struct Window
{
    TextInputWindowId id;
    std::unique_ptr<TextInputBackend> backend;
    TextInputService::CoordinateTransform transform;
    std::shared_ptr<Session> target;
    std::shared_ptr<Session> occupant;
    std::deque<std::shared_ptr<Session>> pendingClosures;
    bool registered = true;
    bool updatingBackend = false;
};

std::optional<TextInputArea> resolveArea(const Window& window, const std::optional<TextInputArea>& area)
{
    if (!area)
        return std::nullopt;
    auto result = area;
    if (area->space == TextInputSpace::design)
        result = window.transform ? window.transform(*area) : std::nullopt;
    if (!result || result->space != TextInputSpace::window || !validArea(*result))
        return std::nullopt;
    if (const auto& clip = result->clip)
    {
        const auto& caret = result->caret;
        if (clip->width == 0 || clip->height == 0 || caret.x >= clip->x + clip->width ||
            caret.y >= clip->y + clip->height || caret.x + caret.width < clip->x || caret.y + caret.height <= clip->y)
            return std::nullopt;
        result->caret = intersection(caret, *clip);
        result->line = intersection(result->line, *clip);
    }
    return result;
}

bool open(const std::shared_ptr<Session>& session)
{
    return session && !session->closing && session->channel->accepting.load();
}

struct Router
{
    std::shared_ptr<Queue> queue = std::make_shared<Queue>();
    std::unordered_map<TextInputWindowId, std::shared_ptr<Window>> windows;
    std::unordered_map<TextInputSessionId, std::shared_ptr<Session>> sessions;
    std::shared_ptr<TextInputService::FocusChangedCallback> focusCallback;
    TextInputWindowId focusedWindow = 0;
    TextInputWindowId nativeFocusedWindow = 0;
    TextInputWindowId occupiedWindow = 0;
    bool dispatching = false;
    bool shuttingDown = false;
    bool resetting = false;

    std::atomic<std::uint64_t> focusEpoch{0};
    std::atomic<TextInputWindowId> focusWindow{0};
    std::atomic<TextInputSessionId> focusSession{0};
    std::atomic<bool> focusNative{false};

    std::shared_ptr<Window> findWindow(TextInputWindowId id) const
    {
        const auto found = windows.find(id);
        return found == windows.end() ? nullptr : found->second;
    }

    std::shared_ptr<Session> findSession(TextInputSessionId id) const
    {
        const auto found = sessions.find(id);
        return found == sessions.end() ? nullptr : found->second;
    }

    TextInputFocus focus() const
    {
        for (;;)
        {
            const auto epoch = focusEpoch.load();
            if (epoch % 2 != 0)
                continue;
            const TextInputFocus result{focusWindow.load(), focusSession.load(), focusNative.load()};
            if (focusEpoch.load() == epoch)
                return result;
        }
    }

    void publishFocus()
    {
        const auto window = findWindow(nativeFocusedWindow ? nativeFocusedWindow : focusedWindow);
        TextInputFocus next;
        if (window && open(window->target))
            next = {window->id, window->target->channel->session, window->target->native};
        if (focusSession.load() == next.session)
            return;

        ++focusEpoch;
        focusWindow.store(next.window);
        focusSession.store(next.session);
        focusNative.store(next.native);
        ++focusEpoch;
        if (const auto callback = focusCallback)
            (*callback)(next);
    }

    void drive(const std::shared_ptr<Window>& window)
    {
        if (!window->registered || window->updatingBackend)
            return;

        window->updatingBackend = true;
        while (window->registered)
        {
            if (const auto occupant = window->occupant)
            {
                if (occupant->closing && !occupant->deactivationStarted && occupant->channel->accepting.load())
                {
                    occupant->deactivationStarted = true;
                    if (occupant->native)
                        TextInputEventSink(occupant->channel).closed();
                    else
                        window->backend->deactivate();
                }
                if (occupant->channel->accepting.load())
                    break;

                occupant->state.active = false;
                if (window->target == occupant)
                {
                    window->target.reset();
                    if (occupant->native && nativeFocusedWindow == window->id)
                        nativeFocusedWindow = 0;
                }
                window->occupant.reset();
                if (occupiedWindow == window->id)
                    occupiedWindow = 0;
            }

            for (const auto& closing : window->pendingClosures)
                TextInputEventSink(closing->channel).closed();
            window->pendingClosures.clear();
            const auto session = window->target;
            const auto desiredWindow = nativeFocusedWindow ? nativeFocusedWindow : focusedWindow;
            if (resetting || occupiedWindow || !open(session) || !window->registered || window->id != desiredWindow)
                break;
            occupiedWindow = window->id;
            window->occupant = session;
            session->state.active = true;
            if (session->native)
                break;

            auto initial = session->initial;
            initial.area = resolveArea(*window, initial.area);
            const TextInputEventSink sink(session->channel);
            session->activationError = window->backend->activate({sink, session->options, std::move(initial)});
            if (session->activationError != TextInputError::none)
                sink.closed(TextInputCloseReason::activationFailed);
            else if (window->registered && open(session) && session->keyboardRequest)
            {
                const auto visible = *std::exchange(session->keyboardRequest, std::nullopt);
                window->backend->requestKeyboard(visible);
            }
        }
        window->updatingBackend = false;
        publishFocus();
    }

    void driveFocused()
    {
        if (const auto window = findWindow(nativeFocusedWindow ? nativeFocusedWindow : focusedWindow))
            drive(window);
    }

    void close(std::shared_ptr<Session> session, TextInputCloseReason reason)
    {
        if (!session || session->closing)
            return;
        session->closing = true;
        session->state.active = false;
        {
            std::lock_guard lock(queue->mutex);
            session->channel->requestedReason = reason;
        }

        const auto window = findWindow(session->channel->window);
        if (!window)
            return;
        if (window->target == session)
        {
            window->target.reset();
            if (session->native && nativeFocusedWindow == window->id)
                nativeFocusedWindow = 0;
        }
        publishFocus();
        if (!window->registered)
            return;

        if (window->occupant != session)
        {
            if (window->occupant && window->occupant->channel->accepting.load())
                window->pendingClosures.emplace_back(session);
            else
                TextInputEventSink(session->channel).closed(reason);
        }
        drive(window);
        driveFocused();
    }

    void unregisterWindow(TextInputWindowId id)
    {
        const auto window = findWindow(id);
        if (!window)
            return;
        window->registered = false;
        windows.erase(id);
        if (focusedWindow == id)
            focusedWindow = 0;
        if (nativeFocusedWindow == id)
            nativeFocusedWindow = 0;
        if (occupiedWindow == id)
            occupiedWindow = 0;

        // Destroy callbacks after iterating because capture destructors may release other sessions.
        std::vector<std::shared_ptr<Session>> removed;
        for (auto it = sessions.begin(); it != sessions.end();)
        {
            if (it->second->channel->window != id)
            {
                ++it;
                continue;
            }
            removed.push_back(it->second);
            it = sessions.erase(it);
        }

        bool deactivate = false;
        {
            std::lock_guard lock(queue->mutex);
            deactivate = window->occupant && window->occupant->channel->accepting.load() &&
                         !window->occupant->deactivationStarted && !window->occupant->native && !window->updatingBackend;
            for (const auto& session : removed)
                session->channel->accepting.store(false);
        }
        for (const auto& session : removed)
            session->callback.reset();
        if (deactivate)
            window->backend->deactivate();
        publishFocus();
        if (!shuttingDown)
            driveFocused();
    }

    void sendSnapshot(const std::shared_ptr<Session>& session)
    {
        const auto window = findWindow(session->channel->window);
        if (window && window->occupant == session && session->channel->accepting.load() && session->initial.snapshot)
            window->backend->updateSnapshot(*session->initial.snapshot);
    }

    void resync(const std::shared_ptr<Session>& session)
    {
        ++session->channel->snapshotEpoch;
        sendSnapshot(session);
    }

    void deliver(QueuedEvent item)
    {
        auto& event = item.event;
        const auto session = findSession(event.session);
        if (!session)
            return;

        if (std::holds_alternative<TextInputClosed>(event.payload))
        {
            session->closing = true;
            session->state.active = false;
            if (const auto window = findWindow(event.window))
                drive(window);
            driveFocused();
            const auto callback = std::move(session->callback);
            sessions.erase(event.session);
            if (callback && !shuttingDown && findWindow(event.window))
                (*callback)(event);
            return;
        }

        const auto callback = session->callback;
        if (!callback)
            return;

        if (const auto* commit = std::get_if<TextInputCommit>(&event.payload))
        {
            if (session->native || item.hasRangeSnapshot ||
                !StringUtils::isLegalUTF8String(commit->text.data(), commit->text.size()))
                return;
        }
        else if (const auto* edit = std::get_if<TextInputEdit>(&event.payload))
        {
            if (!session->capabilities.rangeEdit || !session->initial.snapshot ||
                item.snapshotEpoch != session->channel->snapshotEpoch.load() || edit->transactionId <= session->lastTransaction)
                return;

            session->lastTransaction = edit->transactionId;
            session->predicted = applyEdit(*session->initial.snapshot, *edit);
            if (!session->predicted)
            {
                resync(session);
                return;
            }
        }
        else if (const auto* preedit = std::get_if<TextInputPreedit>(&event.payload))
        {
            if (!session->capabilities.observePreedit)
                return;
            const auto count = TextInputIndex(preedit->text).scalarCount();
            if (!count || (preedit->selection &&
                           (preedit->selection->anchor > count.offset || preedit->selection->focus > count.offset)))
                return;
            session->state.composing = preedit->phase == TextInputPreeditPhase::ended ? TextInputKnowledge::no
                                                                                     : TextInputKnowledge::yes;
        }
        else if (auto* command = std::get_if<TextInputCommand>(&event.payload))
        {
            if (session->native)
                return;
            if (command->action == TextInputCommandAction::insertNewline && !session->options.multiline)
                command->action = returnCommand(session->options.returnAction);
        }
        else if (auto* changed = std::get_if<TextInputStateChanged>(&event.payload))
        {
            changed->state.active = session->state.active;
            if (!session->capabilities.keyboardVisibility)
                changed->state.keyboardVisible = TextInputKnowledge::unknown;
            if (!session->capabilities.keyboardOcclusion || (changed->state.occlusion && !validRect(*changed->state.occlusion)))
                changed->state.occlusion.reset();
            if (!session->capabilities.keyboardOcclusion || (changed->targetOcclusion && !validRect(*changed->targetOcclusion)))
                changed->targetOcclusion.reset();
            if (changed->animationDuration && (!std::isfinite(*changed->animationDuration) || *changed->animationDuration < 0))
                changed->animationDuration.reset();
            if (session->options.purpose == TextInputPurpose::password)
                changed->state.composing = TextInputKnowledge::unknown;
            session->state = changed->state;
        }

        (*callback)(event);
        if (session->predicted && findSession(event.session) && session->callback)
        {
            session->predicted.reset();
            resync(session);
        }
    }
};
}  // namespace text_input_detail

using namespace text_input_detail;

TextInputEventSink::TextInputEventSink(const std::shared_ptr<Channel>& channel)
    : _channel(channel), _window(channel->window), _session(channel->session)
{}

TextInputEventSink::operator bool() const
{
    const auto channel = _channel.lock();
    return channel && channel->accepting.load();
}

std::uint64_t TextInputEventSink::snapshotEpoch() const
{
    const auto channel = _channel.lock();
    return channel ? channel->snapshotEpoch.load() : 0;
}

bool TextInputEventSink::post(TextInputPayload payload, std::uint64_t snapshotEpoch) const
{
    const auto channel = _channel.lock();
    if (!channel || !channel->accepting.load())
        return false;
    const auto queue = channel->queue.lock();
    if (!queue)
        return false;

    std::lock_guard lock(queue->mutex);
    if (!channel->accepting.load())
        return false;
    if (auto* close = std::get_if<TextInputClosed>(&payload))
    {
        if (channel->requestedReason)
            close->reason = *channel->requestedReason;
        channel->accepting.store(false);
    }
    if (!snapshotEpoch)
        snapshotEpoch = channel->snapshotEpoch.load();
    queue->events.push_back({{_window, _session, channel->nextSequence++, std::move(payload)}, snapshotEpoch,
                             channel->hasRangeSnapshot.load()});
    queue->hasEvents.store(true);
    return true;
}

bool TextInputEventSink::closed(TextInputCloseReason reason) const
{
    return post(TextInputClosed{reason});
}

const char* textInputErrorName(TextInputError error)
{
    switch (error)
    {
    case TextInputError::none: return "none";
    case TextInputError::invalidWindow: return "invalidWindow";
    case TextInputError::invalidArgument: return "invalidArgument";
    case TextInputError::invalidArea: return "invalidArea";
    case TextInputError::invalidSnapshot: return "invalidSnapshot";
    case TextInputError::staleSnapshot: return "staleSnapshot";
    case TextInputError::staleSession: return "staleSession";
    case TextInputError::unsupported: return "unsupported";
    case TextInputError::activationFailed: return "activationFailed";
    }
    return "unknown";
}

TextInputSession::TextInputSession(const std::shared_ptr<Router>& router, TextInputWindowId window, TextInputSessionId id)
    : _router(router), _window(window), _id(id)
{}

TextInputSession::~TextInputSession()
{
    release();
}

TextInputSession::TextInputSession(TextInputSession&& other) noexcept
    : _router(std::move(other._router)), _window(std::exchange(other._window, 0)), _id(std::exchange(other._id, 0)),
      _closed(std::exchange(other._closed, false))
{}

TextInputSession& TextInputSession::operator=(TextInputSession&& other) noexcept
{
    if (this != &other)
    {
        release();
        _router = std::move(other._router);
        _window = std::exchange(other._window, 0);
        _id = std::exchange(other._id, 0);
        _closed = std::exchange(other._closed, false);
    }
    return *this;
}

void TextInputSession::release()
{
    if (const auto router = _router.lock())
    {
        if (const auto session = router->findSession(_id))
        {
            session->callback.reset();
            router->close(session, TextInputCloseReason::requested);
        }
    }
}

TextInputSession::operator bool() const
{
    const auto router = _router.lock();
    return router && open(router->findSession(_id));
}

TextInputError TextInputSession::setArea(std::optional<TextInputArea> area)
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    if (!open(session))
        return TextInputError::staleSession;
    const auto window = router->findWindow(_window);
    if (session->native)
        return TextInputError::unsupported;
    const bool active = window->occupant == session;
    const auto hasAnchor = [&] {
        return active ? window->backend->capabilities().anchor : session->capabilities.anchor;
    };
    if (area && (!validArea(*area) || (area->space == TextInputSpace::design && !window->transform)))
        return hasAnchor() ? TextInputError::invalidArea : TextInputError::unsupported;
    if (!sameArea(area, session->initial.area))
    {
        // Retain the latest requested area if the native transport disconnects or has
        // yet to negotiate positioning, so recovery uses the current caret.
        session->initial.area = std::move(area);
        if (active)
            window->backend->setArea(resolveArea(*window, session->initial.area));
    }
    return hasAnchor() ? TextInputError::none : TextInputError::unsupported;
}

TextInputError TextInputSession::updateState(TextInputSnapshot snapshot)
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    // A terminally ordered edit can still require acknowledgement during close.
    if (!open(session) && !(session && session->predicted))
        return TextInputError::staleSession;
    if (!session->capabilities.rangeEdit)
        return TextInputError::unsupported;
    const auto count = TextInputIndex(snapshot.utf8).scalarCount();
    if (!count || count.offset > (std::numeric_limits<std::size_t>::max)() - snapshot.origin ||
        !inRange(snapshot.anchor, snapshot.origin, count.offset) || !inRange(snapshot.focus, snapshot.origin, count.offset))
        return TextInputError::invalidSnapshot;

    const auto& previous = session->initial.snapshot;
    if (previous && snapshot.revision < previous->revision)
        return TextInputError::staleSnapshot;
    if (previous && sameSnapshot(snapshot, *previous) && !session->predicted)
        return TextInputError::none;

    const auto expected = session->predicted && sameSnapshot(snapshot, *session->predicted);
    session->predicted.reset();
    session->initial.snapshot = std::move(snapshot);
    session->channel->hasRangeSnapshot.store(true);
    if (expected)
        router->sendSnapshot(session);
    else
        router->resync(session);
    return TextInputError::none;
}

TextInputCapabilities TextInputSession::capabilities() const
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    if (!open(session))
        return {};
    auto capabilities = session->capabilities;
    const auto window = router->findWindow(_window);
    if (!session->native && window->occupant == session)
        capabilities.anchor = window->backend->capabilities().anchor;
    return capabilities;
}

TextInputState TextInputSession::state() const
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    return open(session) ? session->state : TextInputState{};
}

TextInputError TextInputSession::requestKeyboard(bool visible)
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    if (!open(session))
        return TextInputError::staleSession;
    if (!session->capabilities.requestKeyboard)
        return TextInputError::unsupported;
    const auto window = router->findWindow(_window);
    if (window->occupant == session)
        return window->backend->requestKeyboard(visible);
    session->keyboardRequest = visible;
    return TextInputError::none;
}

TextInputError TextInputSession::cancelComposition()
{
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    if (!open(session))
        return TextInputError::staleSession;
    if (!session->capabilities.cancelComposition)
        return TextInputError::unsupported;
    const auto window = router->findWindow(_window);
    return window->occupant == session ? window->backend->cancelComposition() : TextInputError::none;
}

TextInputError TextInputSession::close()
{
    if (_closed)
        return TextInputError::none;
    const auto router = _router.lock();
    const auto session = router ? router->findSession(_id) : nullptr;
    if (!session)
        return TextInputError::staleSession;
    _closed = true;
    router->close(session, TextInputCloseReason::requested);
    return TextInputError::none;
}

TextInputService::TextInputService() : _router(std::make_shared<Router>()) {}

TextInputService::~TextInputService()
{
    _router->shuttingDown = true;
    _router->focusCallback.reset();
    while (!_router->windows.empty())
        _router->unregisterWindow(_router->windows.begin()->first);
}

TextInputBeginResult TextInputService::begin(TextInputWindowId window,
                                           TextInputOptions options,
                                           Callback onEvent,
                                           TextInputInitialState initial)
{
    return beginEditing(window, std::move(options), std::move(onEvent), std::move(initial), std::nullopt);
}

TextInputBeginResult TextInputService::beginNativeEditing(TextInputWindowId window,
                                                        Callback onEvent,
                                                        TextInputCapabilities capabilities)
{
    return beginEditing(window, {}, std::move(onEvent), {}, capabilities);
}

TextInputBeginResult TextInputService::beginEditing(TextInputWindowId id,
                                                  TextInputOptions options,
                                                  Callback onEvent,
                                                  TextInputInitialState initial,
                                                  std::optional<TextInputCapabilities> nativeCapabilities)
{
    const auto router = _router;
    const auto window = router->findWindow(id);
    if (!window || router->shuttingDown || router->resetting)
        return {{}, TextInputError::invalidWindow};
    if (!onEvent && !nativeCapabilities)
        return {{}, TextInputError::invalidArgument};
    if (initial.area && (!validArea(*initial.area) || (initial.area->space == TextInputSpace::design && !window->transform)))
        return {{}, TextInputError::invalidArea};

    const auto session = std::make_shared<Session>();
    session->native = nativeCapabilities.has_value();
    if (session->native)
    {
        const auto backendCapabilities = window->backend ? window->backend->nativeEditingCapabilities()
                                                         : TextInputCapabilities{};
        session->capabilities.keyboardVisibility = nativeCapabilities->keyboardVisibility || backendCapabilities.keyboardVisibility;
        session->capabilities.keyboardOcclusion = nativeCapabilities->keyboardOcclusion || backendCapabilities.keyboardOcclusion;
    }
    else
    {
        if (!window->backend)
            return {{}, TextInputError::unsupported};
        session->capabilities = window->backend->capabilities();
        if (options.purpose == TextInputPurpose::password)
        {
            options.rangeEdit = false;
            options.observePreedit = false;
            options.autocorrect = false;
            options.capitalization = TextInputCapitalization::none;
        }
        session->capabilities.observePreedit &= options.observePreedit;
        session->capabilities.rangeEdit &= options.rangeEdit;
        session->capabilities.reconversion &= session->capabilities.rangeEdit;
        options.observePreedit = session->capabilities.observePreedit;
        options.rangeEdit = session->capabilities.rangeEdit;
    }
    if (!session->capabilities.rangeEdit)
        initial.snapshot.reset();
    if (initial.snapshot)
    {
        const auto& snapshot = *initial.snapshot;
        const auto count = TextInputIndex(snapshot.utf8).scalarCount();
        if (!count || count.offset > (std::numeric_limits<std::size_t>::max)() - snapshot.origin ||
            !inRange(snapshot.anchor, snapshot.origin, count.offset) || !inRange(snapshot.focus, snapshot.origin, count.offset))
            return {{}, TextInputError::invalidSnapshot};
    }

    const auto sessionId = nextSessionId.fetch_add(1, std::memory_order_relaxed);
    session->channel = std::make_shared<Channel>(id, sessionId, router->queue);
    session->channel->hasRangeSnapshot.store(initial.snapshot.has_value());
    if (onEvent)
        session->callback = std::make_shared<Callback>(std::move(onEvent));
    session->options = std::move(options);
    session->initial = std::move(initial);
    router->sessions.emplace(sessionId, session);

    const auto previousNativeWindow = router->findWindow(router->nativeFocusedWindow);
    const auto previousNative = previousNativeWindow ? previousNativeWindow->target : nullptr;
    const auto occupiedWindow = router->findWindow(router->occupiedWindow);
    const auto previousOccupant = occupiedWindow ? occupiedWindow->occupant : nullptr;
    const auto previous = std::exchange(window->target, session);
    if (session->native)
        router->nativeFocusedWindow = id;
    else if (id == router->nativeFocusedWindow || id == router->focusedWindow)
        router->nativeFocusedWindow = 0;
    router->publishFocus();
    if (previousNative && previousNativeWindow != window && (session->native || id == router->focusedWindow))
        router->close(previousNative, TextInputCloseReason::replaced);
    if (previousOccupant && occupiedWindow != window && (session->native || id == router->focusedWindow))
        router->close(previousOccupant, TextInputCloseReason::replaced);
    router->close(previous, TextInputCloseReason::replaced);
    router->drive(window);
    if (session->activationError != TextInputError::none)
    {
        session->callback.reset();
        router->sessions.erase(sessionId);
        return {{}, session->activationError};
    }
    if (!window->registered)
        return {{}, TextInputError::invalidWindow};
    return {TextInputSession(router, id, sessionId), TextInputError::none};
}

TextInputWindowId TextInputService::registerWindow(std::unique_ptr<TextInputBackend> backend,
                                                 bool focused,
                                                 CoordinateTransform transform)
{
    if (_router->shuttingDown)
        return 0;
    const auto id = nextWindowId.fetch_add(1, std::memory_order_relaxed);
    auto window = std::make_shared<Window>();
    window->id = id;
    window->backend = std::move(backend);
    window->transform = std::move(transform);
    _router->windows.emplace(id, std::move(window));
    if (focused)
        setWindowFocused(id, true);
    return id;
}

void TextInputService::unregisterWindow(TextInputWindowId window)
{
    const auto router = _router;
    router->unregisterWindow(window);
}

void TextInputService::setWindowFocused(TextInputWindowId id, bool focused)
{
    const auto router = _router;
    const auto window = router->findWindow(id);
    if (!window || (router->focusedWindow == id) == focused)
        return;

    const auto previous = router->findWindow(router->focusedWindow);
    router->focusedWindow = focused ? id : 0;
    if (previous && previous->target && !previous->target->native)
        router->close(previous->target, TextInputCloseReason::focusLost);
    router->drive(window);
}

void TextInputService::geometryChanged(TextInputWindowId id)
{
    const auto window = _router->findWindow(id);
    if (window && open(window->occupant) && !window->occupant->native &&
        (window->occupant->initial.area || window->occupant->capabilities.anchor))
        window->backend->geometryChanged(resolveArea(*window, window->occupant->initial.area));
}

void TextInputService::reset()
{
    const auto router = _router;
    if (router->resetting)
        return;
    router->resetting = true;
    std::vector<std::shared_ptr<Session>> sessions;
    for (const auto& entry : router->sessions)
        sessions.push_back(entry.second);
    for (const auto& session : sessions)
        session->callback.reset();
    for (const auto& session : sessions)
        router->close(session, TextInputCloseReason::requested);
    router->resetting = false;
}

TextInputEventSink TextInputService::sinkForWindow(TextInputWindowId id, bool includeNative) const
{
    const auto window = _router->findWindow(id);
    if (!window || !window->occupant)
        return {};
    if (window->occupant->native && !includeNative)
        return {};
    if (window->occupant->native || window->id == _router->focusedWindow ||
        (window->updatingBackend && window->occupant->closing))
        return TextInputEventSink(window->occupant->channel);
    return {};
}

bool TextInputService::hasTextFocus() const
{
    return _router->focusSession.load(std::memory_order_relaxed) != 0;
}

TextInputFocus TextInputService::focus() const
{
    return _router->focus();
}

void TextInputService::setFocusChangedCallback(FocusChangedCallback callback)
{
    const auto router = _router;
    if (callback)
    {
        const auto receiver = std::make_shared<FocusChangedCallback>(std::move(callback));
        router->focusCallback = receiver;
        (*receiver)(router->focus());
    }
    else
    {
        router->focusCallback.reset();
    }
}

std::size_t TextInputService::dispatchPending(std::size_t maxEvents, std::chrono::microseconds budget)
{
    const auto router = _router;
    if (router->dispatching || !router->queue->hasEvents.load(std::memory_order_relaxed) || maxEvents == 0)
        return 0;
    router->dispatching = true;
    struct DispatchGuard
    {
        bool& active;
        ~DispatchGuard() { active = false; }
    } guard{router->dispatching};

    const auto started = std::chrono::steady_clock::now();
    std::size_t processed = 0;
    while (processed < maxEvents && !router->shuttingDown)
    {
        auto event = router->queue->pop();
        if (!event)
            break;
        router->deliver(std::move(*event));
        ++processed;
        if (std::chrono::steady_clock::now() - started >= budget)
            break;
    }
    return processed;
}

}  // namespace cc
