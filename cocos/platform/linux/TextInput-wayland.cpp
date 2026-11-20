#include "platform/TextInputBackend.h"
#include "platform/desktop/TextInputGLFW.h"
#include "platform/linux/TextInput-wayland-private.h"

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WAYLAND
#include "glfw3.h"
#include "glfw3native.h"
#include "text-input-unstable-v3-client-protocol.h"

#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstring>
#include <deque>
#include <poll.h>
#include <unordered_map>
#include <utility>

namespace cc
{
namespace
{
using namespace wayland_text_input;
using Clock = std::chrono::steady_clock;
constexpr auto protocolTimeout = std::chrono::milliseconds(250);

class WaylandBackend;

struct Batch
{
    std::string commit;
    std::string preedit;
    std::int32_t begin = -1;
    std::int32_t end = -1;
    std::uint32_t before = 0;
    std::uint32_t after = 0;
    bool composing = false;
};

struct Seat
{
    explicit Seat(wl_display* display, wl_seat* proxy);
    ~Seat();

    void bind(zwp_text_input_manager_v3* manager);
    void unbind();
    void commit(const std::shared_ptr<const Surrounding>& context, std::uint64_t epoch);
    const Surrounding* contextAt(std::uint32_t serial, std::uint64_t epoch) const;
    void retire();
    void detach();
    void poll(Clock::time_point now);

    wl_display* display;
    wl_seat* proxy;
    zwp_text_input_v3* input = nullptr;
    wl_surface* surface = nullptr;
    WaylandBackend* owner = nullptr;
    std::uint32_t serial = 0;
    std::uint32_t first = 0;
    Batch batch;
    bool keyboard = false;
    wl_callback* retirement = nullptr;
    Clock::time_point retirementDeadline{};
    struct Publication
    {
        std::uint32_t serial;
        std::uint64_t epoch;
        std::shared_ptr<const Surrounding> context;
    };
    std::deque<Publication> publications;
};

class Context
{
public:
    explicit Context(wl_display* display) : display(display) {}
    ~Context();

    bool discover();
    bool available() const;
    void poll();

    wl_display* const display;
    std::size_t activeSessions = 0;
    std::unordered_map<wl_surface*, WaylandBackend*> windows;
    std::unordered_map<std::uint32_t, std::unique_ptr<Seat>> seats;

private:
    void removeManager();

    wl_registry* _registry = nullptr;
    zwp_text_input_manager_v3* _manager = nullptr;
    std::uint32_t _managerName = 0;
};

std::weak_ptr<Context> connection;
std::unordered_map<GLFWwindow*, WaylandBackend*> glfwWindows;

template <typename Proxy>
void setQueue(Proxy* proxy, wl_event_queue* queue)
{
    if (proxy)
        wl_proxy_set_queue(reinterpret_cast<wl_proxy*>(proxy), queue);
}

// Initial registry discovery never dispatches GLFW's queue. Later events go through GLFW's normal pump.
void discoverPending(wl_display* display, wl_event_queue* queue, bool& completed)
{
    const auto deadline = Clock::now() + protocolTimeout;
    while (!completed && Clock::now() < deadline)
    {
        if (wl_display_dispatch_queue_pending(display, queue) < 0 || completed)
            break;
        if (wl_display_prepare_read_queue(display, queue) != 0)
            continue;

        pollfd fd{wl_display_get_fd(display), POLLIN, 0};
        if (wl_display_flush(display) < 0)
        {
            if (errno != EAGAIN)
            {
                wl_display_cancel_read(display);
                break;
            }
            fd.events |= POLLOUT;
        }
        const auto remaining = std::chrono::ceil<std::chrono::milliseconds>(deadline - Clock::now()).count();
        const int ready = ::poll(&fd, 1, static_cast<int>(std::max(remaining, decltype(remaining){0})));
        if (ready > 0 && (fd.revents & POLLIN))
        {
            if (wl_display_read_events(display) < 0)
                break;
        }
        else
        {
            wl_display_cancel_read(display);
            if (ready == 0 || (ready < 0 && errno != EINTR) || (fd.revents & (POLLERR | POLLHUP | POLLNVAL)))
                break;
        }
    }
}

std::uint32_t purpose(TextInputPurpose value)
{
    switch (value)
    {
    case TextInputPurpose::name: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_NAME;
    case TextInputPurpose::email: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_EMAIL;
    case TextInputPurpose::url: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_URL;
    case TextInputPurpose::phone: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_PHONE;
    case TextInputPurpose::number: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_DIGITS;
    case TextInputPurpose::decimal: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_NUMBER;
    case TextInputPurpose::password: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_PASSWORD;
    case TextInputPurpose::text: return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_NORMAL;
    }
    return ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_NORMAL;
}

std::uint32_t hints(const TextInputOptions& options)
{
    if (options.purpose == TextInputPurpose::password)
        return ZWP_TEXT_INPUT_V3_CONTENT_HINT_HIDDEN_TEXT | ZWP_TEXT_INPUT_V3_CONTENT_HINT_SENSITIVE_DATA;
    std::uint32_t result = ZWP_TEXT_INPUT_V3_CONTENT_HINT_NONE;
    if (options.multiline)
        result |= ZWP_TEXT_INPUT_V3_CONTENT_HINT_MULTILINE;
    if (options.autocorrect.value_or(false))
        result |= ZWP_TEXT_INPUT_V3_CONTENT_HINT_COMPLETION | ZWP_TEXT_INPUT_V3_CONTENT_HINT_SPELLCHECK;
    switch (options.capitalization)
    {
    case TextInputCapitalization::sentences: result |= ZWP_TEXT_INPUT_V3_CONTENT_HINT_AUTO_CAPITALIZATION; break;
    case TextInputCapitalization::words: result |= ZWP_TEXT_INPUT_V3_CONTENT_HINT_TITLECASE; break;
    case TextInputCapitalization::characters: result |= ZWP_TEXT_INPUT_V3_CONTENT_HINT_UPPERCASE; break;
    default: break;
    }
    return result;
}

std::int32_t protocolInt(double value)
{
    constexpr auto min = (std::numeric_limits<std::int32_t>::min)();
    constexpr auto max = (std::numeric_limits<std::int32_t>::max)();
    return static_cast<std::int32_t>(std::clamp(value, static_cast<double>(min), static_cast<double>(max)));
}

class WaylandBackend final : public TextInputBackend
{
public:
    WaylandBackend(std::shared_ptr<Context> context, GLFWwindow* window, wl_surface* surface)
        : _context(std::move(context)), _window(window), _surface(surface)
    {
        _context->windows.emplace(_surface, this);
        glfwWindows.emplace(_window, this);
    }

    ~WaylandBackend() override
    {
        glfwWindows.erase(_window);
        _context->windows.erase(_surface);
        if (_seat)
        {
            _seat->retire();
            if (_seat)
                _seat->detach();
        }
        stopPolling();
    }

    TextInputCapabilities capabilities() const override
    {
        TextInputCapabilities result;
        result.anchor = result.observePreedit = result.rangeEdit = _context->available();
        return result;
    }

    TextInputError activate(const TextInputActivation& activation) override
    {
        _sink = activation.sink;
        _polling = true;
        ++_context->activeSessions;
        _options = activation.options;
        _area = activation.initial.area;
        _confirmed = _options.rangeEdit && !password() ? activation.initial.snapshot : std::nullopt;
        _mirror = _confirmed;
        _snapshotEpoch = _sink.snapshotEpoch();
        _nextTransaction = 1;
        _causes.clear();
        attach();
        return TextInputError::none;
    }

    void setArea(const std::optional<TextInputArea>& area) override
    {
        _area = area;
        _areaDirty = true;
    }

    void updateSnapshot(const TextInputSnapshot& snapshot) override
    {
        if (!_options.rangeEdit || password())
            return;
        const auto epoch = _sink.snapshotEpoch();
        bool fromIme = false;
        if (epoch != _snapshotEpoch || !_mirror)
        {
            _snapshotEpoch = epoch;
            _mirror = snapshot;
            _causes.clear();
            _firstSnapshotSerial.reset();
            endPreedit();
        }
        else if (snapshot.acknowledgedTransaction)
        {
            const auto transaction = *snapshot.acknowledgedTransaction;
            while (!_causes.empty() && _causes.front().first < transaction)
                _causes.pop_front();
            if (!_causes.empty() && _causes.front().first == transaction)
            {
                fromIme = _causes.front().second;
                _causes.pop_front();
            }
        }
        _confirmed = snapshot;
        _contextDirty = true;
        _inputMethodChange = fromIme;
        publish(false);
    }

    TextInputError requestKeyboard(bool) override { return TextInputError::unsupported; }
    TextInputError cancelComposition() override { return TextInputError::unsupported; }

    void deactivate() override
    {
        if (_closing)
            return;
        _closing = true;
        if (_seat)
            _seat->retire();
        else
            finish();
    }

    void attach()
    {
        if (!_sink || _seat || _closing)
            return;
        std::uint32_t selected = 0;
        for (const auto& entry : _context->seats)
        {
            Seat& seat = *entry.second;
            if (seat.input && seat.surface == _surface && !seat.owner &&
                (!_seat || (seat.keyboard != _seat->keyboard ? seat.keyboard : entry.first < selected)))
            {
                _seat = &seat;
                selected = entry.first;
            }
        }
        if (_seat)
        {
            _seat->owner = this;
            _seat->first = _seat->serial + 1;
            _firstSnapshotSerial.reset();
            _inputMethodChange = false;
            publish(true);
        }
    }

    void lostSeat()
    {
        _seat = nullptr;
        _published.reset();
        _deferState = false;
        _sentArea = false;
        endPreedit();
        if (_closing)
            finish();
    }

    bool acceptCharacter(unsigned int codepoint)
    {
        if (!_sink)
            return false;
        if (_closing)
            return true;
        if (!_mirror)
            return false;

        const auto text = TextInputIndex::encode(static_cast<char32_t>(codepoint));
        if (text)
            applyEdit(nullptr, 0, 0, *text, false);
        return true;
    }

    void readPreedit(Batch& batch, const char* text, std::int32_t begin, std::int32_t end) const
    {
        if (password())
            return;
        batch.composing = text && *text;
        batch.preedit = _options.observePreedit && text ? text : "";
        batch.begin = begin;
        batch.end = end;
    }

    void done(Batch batch, std::uint32_t serial)
    {
        if (!_seat || !_sink || !inActivation(serial, _seat->first, _seat->serial))
            return;

        // Serial inequality within this activation delays state publication, never plain committed text.
        _deferState = serial != _seat->serial;

        // External selection/document changes invalidate even a pure commit based on the old caret.
        // Mismatched serials within the current snapshot epoch still describe this editor state.
        if (_mirror && (!_firstSnapshotSerial || !inActivation(serial, *_firstSnapshotSerial, _seat->serial)))
        {
            publish(false);
            return;
        }

        const bool changesText = batch.before || batch.after || !batch.commit.empty();
        if (_composing && (!batch.composing || changesText))
            endPreedit();
        if (changesText)
        {
            if (_mirror)
            {
                if (!applyEdit(_seat->contextAt(serial, _snapshotEpoch), batch.before, batch.after, batch.commit, true))
                {
                    _contextDirty = true;
                    _inputMethodChange = false;
                }
            }
            else if (!batch.before && !batch.after && !batch.commit.empty())
            {
                TextInputGLFW::detail::postCommit(_window, _sink, TextInputCommit{std::move(batch.commit)});
            }
        }
        if (batch.composing && (!batch.preedit.empty() || !_options.observePreedit))
        {
            const bool beginning = !_composing;
            _composing = true;
            if (_options.observePreedit)
            {
                const auto selection = preeditSelection(batch.preedit, batch.begin, batch.end);
                _sink.post(TextInputPreedit{std::move(batch.preedit), selection,
                                           beginning ? TextInputPreeditPhase::began : TextInputPreeditPhase::updated});
            }
            else if (beginning)
            {
                _sink.post(TextInputStateChanged{compositionState(TextInputKnowledge::yes)});
            }
        }
        publish(false);
    }

    void poll()
    {
        attach();
        publish(false);
    }

private:
    bool password() const { return _options.purpose == TextInputPurpose::password; }

    static TextInputState compositionState(TextInputKnowledge value)
    {
        TextInputState state;
        state.composing = value;
        return state;
    }

    void endPreedit()
    {
        if (!std::exchange(_composing, false))
            return;
        if (_options.observePreedit)
            _sink.post(TextInputPreedit{{}, {}, TextInputPreeditPhase::ended});
        else
            _sink.post(TextInputStateChanged{compositionState(TextInputKnowledge::no)});
    }

    void finish()
    {
        endPreedit();
        _sink.closed();
        _sink = {};
        _confirmed.reset();
        _mirror.reset();
        _causes.clear();
        _closing = false;
        stopPolling();
    }

    void stopPolling()
    {
        if (std::exchange(_polling, false))
            --_context->activeSessions;
    }

    bool applyEdit(const Surrounding* published, std::uint32_t before, std::uint32_t after,
                   std::string_view commit, bool fromIme)
    {
        auto plan = planEdit(*_mirror, published, before, after, commit, _nextTransaction);
        if (!plan || !_sink.post(std::move(plan->edit), _snapshotEpoch))
            return false;
        _mirror = std::move(plan->predicted);
        _causes.emplace_back(_nextTransaction++, fromIme);
        return true;
    }

    void publish(bool start)
    {
        if (!_seat || _closing || _deferState ||
            (!start && !_areaDirty && !_contextDirty))
            return;

        std::shared_ptr<const Surrounding> next = _published;
        if (start || _contextDirty)
        {
            next.reset();
            if (_confirmed)
                if (auto clipped = surrounding(*_confirmed))
                    next = std::make_shared<Surrounding>(std::move(*clipped));
        }

        auto* input = _seat->input;
        const bool reset = start || static_cast<bool>(next) != static_cast<bool>(_published);
        if (reset)
        {
            // An enable starts a fresh advertised context. A missing context stays unset.
            zwp_text_input_v3_enable(input);
            zwp_text_input_v3_set_content_type(input, hints(_options), purpose(_options.purpose));
            _sentArea = false;
        }
        if ((reset || _contextDirty) && next)
        {
            zwp_text_input_v3_set_surrounding_text(input, next->text.c_str(), next->cursorByte, next->anchorByte);
            zwp_text_input_v3_set_text_change_cause(input, _inputMethodChange ? ZWP_TEXT_INPUT_V3_CHANGE_CAUSE_INPUT_METHOD
                                                                           : ZWP_TEXT_INPUT_V3_CHANGE_CAUSE_OTHER);
        }
        if ((reset || _areaDirty) && _area)
        {
            const auto& caret = _area->caret;
            const auto x = std::floor(caret.x);
            const auto y = std::floor(caret.y);
            zwp_text_input_v3_set_cursor_rectangle(input, protocolInt(x), protocolInt(y),
                protocolInt(std::ceil(caret.x + caret.width) - x), protocolInt(std::ceil(caret.y + caret.height) - y));
            _sentArea = true;
        }
        else if (_areaDirty && _sentArea)
        {
            zwp_text_input_v3_set_cursor_rectangle(input, 0, 0, 0, 0);
            _sentArea = false;
        }
        _published = std::move(next);
        _areaDirty = _contextDirty = false;
        _seat->commit(_published, _snapshotEpoch);
        if (_mirror && !_firstSnapshotSerial)
            _firstSnapshotSerial = _seat->serial;
        wl_display_flush(_context->display);
    }

    std::shared_ptr<Context> _context;
    GLFWwindow* _window;
    wl_surface* _surface;
    Seat* _seat = nullptr;
    TextInputEventSink _sink;
    TextInputOptions _options;
    std::optional<TextInputArea> _area;
    std::optional<TextInputSnapshot> _confirmed;
    std::optional<TextInputSnapshot> _mirror;
    std::shared_ptr<const Surrounding> _published;
    std::deque<std::pair<std::uint64_t, bool>> _causes;
    std::uint64_t _snapshotEpoch = 0;
    std::uint64_t _nextTransaction = 1;
    std::optional<std::uint32_t> _firstSnapshotSerial;
    bool _deferState = false;
    bool _areaDirty = false;
    bool _contextDirty = false;
    bool _sentArea = false;
    bool _inputMethodChange = false;
    bool _composing = false;
    bool _closing = false;
    bool _polling = false;
};

Seat::Seat(wl_display* display, wl_seat* proxy) : display(display), proxy(proxy)
{
    static constexpr wl_seat_listener listener{
        [](void* data, wl_seat*, std::uint32_t capabilities) {
            static_cast<Seat*>(data)->keyboard = (capabilities & WL_SEAT_CAPABILITY_KEYBOARD) != 0;
        },
        [](void*, wl_seat*, const char*) {},
    };
    wl_seat_add_listener(proxy, &listener, this);
}

Seat::~Seat()
{
    unbind();
    wl_seat_destroy(proxy);
}

void Seat::bind(zwp_text_input_manager_v3* manager)
{
    static const auto listener = [] {
        zwp_text_input_v3_listener callbacks{};
        callbacks.enter = [](void* data, zwp_text_input_v3*, wl_surface* surface) {
            auto& seat = *static_cast<Seat*>(data);
            if (seat.surface != surface)
                seat.detach();
            seat.surface = surface;
        };
        callbacks.leave = [](void* data, zwp_text_input_v3*, wl_surface*) {
            auto& seat = *static_cast<Seat*>(data);
            seat.surface = nullptr;
            seat.detach();
        };
        callbacks.preedit_string = [](void* data, zwp_text_input_v3*, const char* text, std::int32_t begin, std::int32_t end) {
            auto& seat = *static_cast<Seat*>(data);
            if (seat.owner)
                seat.owner->readPreedit(seat.batch, text, begin, end);
        };
        callbacks.commit_string = [](void* data, zwp_text_input_v3*, const char* text) {
            auto& seat = *static_cast<Seat*>(data);
            if (seat.owner)
                seat.batch.commit = text ? text : "";
        };
        callbacks.delete_surrounding_text = [](void* data, zwp_text_input_v3*, std::uint32_t before, std::uint32_t after) {
            auto& seat = *static_cast<Seat*>(data);
            if (seat.owner)
            {
                seat.batch.before = before;
                seat.batch.after = after;
            }
        };
        callbacks.done = [](void* data, zwp_text_input_v3*, std::uint32_t serial) {
            auto& seat = *static_cast<Seat*>(data);
            auto batch = std::exchange(seat.batch, {});
            if (seat.owner)
                seat.owner->done(std::move(batch), serial);
        };
        return callbacks;
    }();
    input = zwp_text_input_manager_v3_get_text_input(manager, proxy);
    if (input && zwp_text_input_v3_add_listener(input, &listener, this) != 0)
        unbind();
}

void Seat::unbind()
{
    surface = nullptr;
    detach();
    if (input)
        zwp_text_input_v3_destroy(std::exchange(input, nullptr));
    serial = first = 0;
}

void Seat::commit(const std::shared_ptr<const Surrounding>& context, std::uint64_t epoch)
{
    ++serial;
    zwp_text_input_v3_commit(input);
    publications.push_back({serial, epoch, context});
    if (publications.size() > 64)
        publications.pop_front();
}

const Surrounding* Seat::contextAt(std::uint32_t serial, std::uint64_t epoch) const
{
    const auto entry = std::find_if(publications.rbegin(), publications.rend(),
                                    [serial](const auto& value) { return value.serial == serial; });
    return entry == publications.rend() || entry->epoch != epoch ? nullptr : entry->context.get();
}

void Seat::retire()
{
    if (retirement)
        return;
    if (!input || !surface || wl_display_get_error(display))
    {
        detach();
        return;
    }

    zwp_text_input_v3_disable(input);
    if (publications.empty())
        commit(nullptr, 0);
    else
    {
        const Publication previous = publications.back();
        commit(previous.context, previous.epoch);
    }
    static constexpr wl_callback_listener listener{[](void* data, wl_callback*, std::uint32_t) {
        static_cast<Seat*>(data)->detach();
    }};
    retirement = wl_display_sync(display);
    retirementDeadline = Clock::now() + protocolTimeout;
    if (!retirement || wl_callback_add_listener(retirement, &listener, this) != 0)
        detach();
    wl_display_flush(display);
}

void Seat::detach()
{
    if (retirement)
        wl_callback_destroy(std::exchange(retirement, nullptr));
    batch = {};
    publications.clear();
    if (auto* backend = std::exchange(owner, nullptr))
        backend->lostSeat();
}

void Seat::poll(Clock::time_point now)
{
    if (retirement && now >= retirementDeadline)
        detach();
}

Context::~Context()
{
    removeManager();
    seats.clear();
    if (_registry)
        wl_registry_destroy(_registry);
    wl_display_flush(display);
}

bool Context::discover()
{
    static constexpr wl_registry_listener listener{
        [](void* data, wl_registry* registry, std::uint32_t name, const char* interface, std::uint32_t version) {
            auto& context = *static_cast<Context*>(data);
            if (!version)
                return;
            if (std::strcmp(interface, zwp_text_input_manager_v3_interface.name) == 0 && !context._manager)
            {
                context._manager = static_cast<zwp_text_input_manager_v3*>(
                    wl_registry_bind(registry, name, &zwp_text_input_manager_v3_interface, 1));
                if (context._manager)
                {
                    context._managerName = name;
                    for (const auto& entry : context.seats)
                        entry.second->bind(context._manager);
                }
            }
            else if (std::strcmp(interface, wl_seat_interface.name) == 0)
            {
                auto* proxy = static_cast<wl_seat*>(wl_registry_bind(registry, name, &wl_seat_interface, 1));
                if (!proxy)
                    return;
                auto seat = std::make_unique<Seat>(context.display, proxy);
                if (context._manager)
                    seat->bind(context._manager);
                context.seats.emplace(name, std::move(seat));
            }
        },
        [](void* data, wl_registry*, std::uint32_t name) {
            auto& context = *static_cast<Context*>(data);
            if (name == context._managerName)
                context.removeManager();
            else
                context.seats.erase(name);
        },
    };
    auto* queue = wl_display_create_queue(display);
    auto* wrapper = queue ? static_cast<wl_display*>(wl_proxy_create_wrapper(display)) : nullptr;
    if (wrapper)
        setQueue(wrapper, queue);
    _registry = wl_display_get_registry(wrapper ? wrapper : display);
    if (!_registry || wl_registry_add_listener(_registry, &listener, this) != 0)
    {
        if (wrapper)
            wl_proxy_wrapper_destroy(wrapper);
        if (queue)
        {
            setQueue(_registry, nullptr);
            wl_event_queue_destroy(queue);
        }
        return false;
    }
    if (wrapper)
    {
        bool completed = false;
        auto* sync = wl_display_sync(wrapper);
        static constexpr wl_callback_listener syncListener{[](void* data, wl_callback*, std::uint32_t) {
            *static_cast<bool*>(data) = true;
        }};
        if (sync && wl_callback_add_listener(sync, &syncListener, &completed) == 0)
            discoverPending(display, queue, completed);
        if (sync)
            wl_callback_destroy(sync);
        wl_proxy_wrapper_destroy(wrapper);

        setQueue(_registry, nullptr);
        setQueue(_manager, nullptr);
        for (const auto& entry : seats)
        {
            setQueue(entry.second->proxy, nullptr);
            setQueue(entry.second->input, nullptr);
        }
        // Events already queued before moving the proxies still belong to the discovery queue.
        wl_display_dispatch_queue_pending(display, queue);
    }
    if (queue)
        wl_event_queue_destroy(queue);
    wl_display_flush(display);
    return wl_display_get_error(display) == 0;
}

bool Context::available() const
{
    return _manager && !wl_display_get_error(display) &&
           std::any_of(seats.begin(), seats.end(), [](const auto& entry) { return entry.second->input; });
}

void Context::poll()
{
    if (activeSessions == 0)
        return;
    if (wl_display_get_error(display))
    {
        removeManager();
        return;
    }
    const auto now = Clock::now();
    for (const auto& entry : seats)
        entry.second->poll(now);
    for (const auto& entry : windows)
        entry.second->poll();
}

void Context::removeManager()
{
    if (!_manager)
        return;
    for (const auto& entry : seats)
        entry.second->unbind();
    zwp_text_input_manager_v3_destroy(std::exchange(_manager, nullptr));
    _managerName = 0;
}
}  // namespace

std::unique_ptr<TextInputBackend> createWaylandTextInputBackend(GLFWwindow* window)
{
    if (!window || glfwGetPlatform() != GLFW_PLATFORM_WAYLAND || glfwWindows.count(window))
        return {};
    auto* display = glfwGetWaylandDisplay();
    auto* surface = glfwGetWaylandWindow(window);
    if (!display || !surface)
        return {};

    auto context = connection.lock();
    if (!context || context->display != display)
    {
        context = std::make_shared<Context>(display);
        if (!context->discover())
            return {};
        connection = context;
    }
    return std::make_unique<WaylandBackend>(std::move(context), window, surface);
}

bool handleWaylandTextCharacter(GLFWwindow* window, unsigned int codepoint)
{
    const auto backend = glfwWindows.find(window);
    return backend != glfwWindows.end() && backend->second->acceptCharacter(codepoint);
}

void pollWaylandTextInput()
{
    // GLFW owns the read side and dispatches our proxies on its default event queue.
    if (const auto context = connection.lock())
        context->poll();
}

}  // namespace cc
