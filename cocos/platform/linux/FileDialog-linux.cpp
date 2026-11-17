#include "platform/FileDialogInternal.h"
#include "platform/desktop/GLViewImpl-desktop.h"

#ifdef CC_DIALOG_X11
#define GLFW_EXPOSE_NATIVE_X11
#endif
#ifdef CC_DIALOG_WAYLAND
#define GLFW_EXPOSE_NATIVE_WAYLAND
#include "xdg-foreign-v2-client.h"
#endif
#include "glfw3native.h"
#include <dbus/dbus.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <thread>

namespace cc::dialog {
namespace {
constexpr auto portal = "org.freedesktop.portal.Desktop";
constexpr auto desktop = "/org/freedesktop/portal/desktop";
constexpr auto chooser = "org.freedesktop.portal.FileChooser";
constexpr auto requestInterface = "org.freedesktop.portal.Request";
constexpr auto requestPrefix = "/org/freedesktop/portal/desktop/request/";
constexpr int methodTimeoutMs = 5000;
constexpr int closeTimeoutMs = 1500;

NativeResult failure(DialogErrorCode code, std::string message, std::string domain = {}, int64_t nativeCode = 0)
{
    NativeResult result;
    result.error = {code, std::move(message), std::move(domain), nativeCode};
    return result;
}

NativeResult cancelled(CancelReason reason)
{
    NativeResult result;
    result.status = DialogStatus::Cancelled;
    result.cancelReason = reason;
    return result;
}

struct BusError {
    DBusError value = DBUS_ERROR_INIT;
    ~BusError() { dbus_error_free(&value); }
};

struct BusDeleter {
    void operator()(DBusConnection* p) const
    {
        dbus_connection_close(p);
        dbus_connection_unref(p);
    }
    void operator()(DBusMessage* p) const { dbus_message_unref(p); }
};
using Connection = std::unique_ptr<DBusConnection, BusDeleter>;
using Message = std::unique_ptr<DBusMessage, BusDeleter>;

NativeResult busFailure(const BusError& error, DialogErrorCode defaultCode, const char* message)
{
    auto code = defaultCode;
    if (dbus_error_has_name(&error.value, DBUS_ERROR_NO_MEMORY)) code = DialogErrorCode::OutOfMemory;
    if (dbus_error_has_name(&error.value, DBUS_ERROR_NO_REPLY) ||
        dbus_error_has_name(&error.value, DBUS_ERROR_TIMEOUT)) code = DialogErrorCode::Timeout;
    if (dbus_error_has_name(&error.value, DBUS_ERROR_ACCESS_DENIED)) code = DialogErrorCode::PermissionDenied;
    if (dbus_error_has_name(&error.value, DBUS_ERROR_SERVICE_UNKNOWN) ||
        dbus_error_has_name(&error.value, DBUS_ERROR_NAME_HAS_NO_OWNER) ||
        dbus_error_has_name(&error.value, DBUS_ERROR_UNKNOWN_METHOD) ||
        dbus_error_has_name(&error.value, DBUS_ERROR_UNKNOWN_INTERFACE) ||
        dbus_error_has_name(&error.value, DBUS_ERROR_DISCONNECTED)) code = DialogErrorCode::Unavailable;
    return failure(code, error.value.message ? error.value.message : message,
                   error.value.name ? error.value.name : "dbus");
}

Message call(DBusConnection* bus, const Message& method, int timeout, BusError& error)
{
    return Message(dbus_connection_send_with_reply_and_block(bus, method.get(), timeout, &error.value));
}

std::optional<std::filesystem::path> fileUri(std::string_view uri)
{
    if (!uri.starts_with("file://")) return {};
    uri.remove_prefix(7);
    if (uri.starts_with("localhost/")) uri.remove_prefix(9);
    if (uri.empty() || uri.front() != '/' || uri.find_first_of("?#") != std::string_view::npos)
        return {};
    auto hex = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return -1;
    };
    std::string path;
    path.reserve(uri.size());
    for (size_t index = 0; index < uri.size(); ++index) {
        auto c = uri[index];
        if (c == '%') {
            if (index + 2 >= uri.size()) return {};
            auto first = hex(uri[index + 1]), second = hex(uri[index + 2]);
            if (first < 0 || second < 0) return {};
            c = static_cast<char>(16 * first + second);
            index += 2;
        }
        if (!c) return {};
        path += c;
    }
    std::filesystem::path result(path);
    for (const auto& component : result)
        if (component == "." || component == "..") return {};
    return result;
}

bool beneath(const std::filesystem::path& path, const std::filesystem::path& root)
{
    if (root.empty()) return false;
    auto mismatch = std::mismatch(root.begin(), root.end(), path.begin(), path.end());
    return mismatch.first == root.end() && mismatch.second != path.end();
}

template<class T>
void append(DBusMessageIter& iter, int type, const T& value)
{
    if (!dbus_message_iter_append_basic(&iter, type, &value)) throw std::bad_alloc{};
}

// Let libdbus discard any unfinished container during exception unwinding.
class Container {
public:
    Container(DBusMessageIter& parent, int type, const char* signature) : _parent(parent)
    {
        if (!dbus_message_iter_open_container(&_parent, type, signature, &iter)) throw std::bad_alloc{};
    }
    ~Container() { dbus_message_iter_abandon_container_if_open(&_parent, &iter); }
    void finish()
    {
        if (!dbus_message_iter_close_container(&_parent, &iter)) throw std::bad_alloc{};
    }
    DBusMessageIter iter = DBUS_MESSAGE_ITER_INIT_CLOSED;
private:
    DBusMessageIter& _parent;
};

template<class Write>
void option(DBusMessageIter& dict, const char* key, const char* signature, Write write)
{
    Container entry(dict, DBUS_TYPE_DICT_ENTRY, nullptr);
    append(entry.iter, DBUS_TYPE_STRING, key);
    Container variant(entry.iter, DBUS_TYPE_VARIANT, signature);
    write(variant.iter);
    variant.finish();
    entry.finish();
}

struct PortalFilter {
    std::string label;
    std::vector<std::pair<dbus_uint32_t, std::string>> rules;
    std::optional<uint32_t> index;
};

std::vector<PortalFilter> makeFilters(const NativeRequest& request)
{
    std::vector<PortalFilter> filters;
    if (request.operation == Operation::Folder) return filters;
    for (uint32_t index = 0; index < request.options.filters.size(); ++index) {
        const auto& source = request.options.filters[index];
        PortalFilter filter{source.label, {}, index};
        for (const auto& extension : source.extensions) {
            std::string pattern = "*.";
            for (auto c : extension) {
                if (c >= 'a' && c <= 'z') {
                    pattern += '[';
                    pattern += c;
                    pattern += static_cast<char>(c - 'a' + 'A');
                    pattern += ']';
                } else {
                    pattern += c;
                }
            }
            filter.rules.emplace_back(0, std::move(pattern));
        }
        for (const auto& mime : source.mimeTypes) filter.rules.emplace_back(1, mime);
        if (!filter.rules.empty()) filters.push_back(std::move(filter));
    }
    if (!filters.empty() && request.options.allowAllFiles)
        filters.push_back({"All files", {{0, "*"}}, {}});
    return filters;
}

bool isSave(Operation operation)
{
    return operation == Operation::SaveTarget || operation == Operation::Export;
}

Message chooserCall(const NativeRequest& request, const std::string& parent, const std::string& token,
                    const std::vector<PortalFilter>& filters, bool initialFolder)
{
    const bool save = isSave(request.operation);
    Message method(dbus_message_new_method_call(portal, desktop, chooser, save ? "SaveFile" : "OpenFile"));
    if (!method) throw std::bad_alloc{};
    DBusMessageIter args;
    dbus_message_iter_init_append(method.get(), &args);
    append(args, DBUS_TYPE_STRING, parent.c_str());
    append(args, DBUS_TYPE_STRING, request.options.title.c_str());
    Container options(args, DBUS_TYPE_ARRAY, "{sv}");
    option(options.iter, "handle_token", "s",
           [&](DBusMessageIter& value) { append(value, DBUS_TYPE_STRING, token.c_str()); });
    if (!save) {
        if (request.operation == Operation::Folder) {
            option(options.iter, "directory", "b",
                   [](DBusMessageIter& value) { append(value, DBUS_TYPE_BOOLEAN, dbus_bool_t{TRUE}); });
        } else if (request.options.allowMultiple) {
            option(options.iter, "multiple", "b",
                   [](DBusMessageIter& value) { append(value, DBUS_TYPE_BOOLEAN, dbus_bool_t{TRUE}); });
        }
    } else if (!request.suggestedName.empty()) {
        option(options.iter, "current_name", "s",
               [&](DBusMessageIter& value) { append(value, DBUS_TYPE_STRING, request.suggestedName.c_str()); });
    }
    if (initialFolder && request.options.initialDirectory) {
        auto hint = request.options.initialDirectory->tryGetLocalPath();
        if (hint && hint->size() < 65536) {
            option(options.iter, "current_folder", "ay", [&](DBusMessageIter& value) {
                Container array(value, DBUS_TYPE_ARRAY, "y");
                auto data = hint->c_str();
                if (!dbus_message_iter_append_fixed_array(&array.iter, DBUS_TYPE_BYTE, &data,
                                                           static_cast<int>(hint->size() + 1)))
                    throw std::bad_alloc{};
                array.finish();
            });
        }
    }
    if (!filters.empty()) {
        option(options.iter, "filters", "a(sa(us))", [&](DBusMessageIter& value) {
            Container list(value, DBUS_TYPE_ARRAY, "(sa(us))");
            for (const auto& filter : filters) {
                Container row(list.iter, DBUS_TYPE_STRUCT, nullptr);
                append(row.iter, DBUS_TYPE_STRING, filter.label.c_str());
                Container rules(row.iter, DBUS_TYPE_ARRAY, "(us)");
                for (const auto& [type, pattern] : filter.rules) {
                    Container rule(rules.iter, DBUS_TYPE_STRUCT, nullptr);
                    append(rule.iter, DBUS_TYPE_UINT32, type);
                    append(rule.iter, DBUS_TYPE_STRING, pattern.c_str());
                    rule.finish();
                }
                rules.finish();
                row.finish();
            }
            list.finish();
        });
    }
    options.finish();
    return method;
}

template<class T>
T value(DBusMessageIter& iter)
{
    T result{};
    dbus_message_iter_get_basic(&iter, &result);
    return result;
}

std::optional<uint32_t> filterIndex(DBusMessageIter& variant, const std::vector<PortalFilter>& filters)
{
    DBusMessageIter rowArgs;
    dbus_message_iter_recurse(&variant, &rowArgs);
    auto label = value<const char*>(rowArgs);
    dbus_message_iter_next(&rowArgs);
    DBusMessageIter rules;
    dbus_message_iter_recurse(&rowArgs, &rules);

    const PortalFilter* match = nullptr;
    for (const auto& filter : filters) {
        if (filter.label != label) continue;
        auto cursor = rules;
        size_t count = 0;
        for (; count < filter.rules.size() && dbus_message_iter_get_arg_type(&cursor) == DBUS_TYPE_STRUCT; ++count) {
            DBusMessageIter ruleArgs;
            dbus_message_iter_recurse(&cursor, &ruleArgs);
            auto type = value<dbus_uint32_t>(ruleArgs);
            dbus_message_iter_next(&ruleArgs);
            auto pattern = value<const char*>(ruleArgs);
            if (filter.rules[count].first != type || filter.rules[count].second != pattern) break;
            dbus_message_iter_next(&cursor);
        }
        if (count != filter.rules.size() || dbus_message_iter_get_arg_type(&cursor) != DBUS_TYPE_INVALID) continue;
        if (match) return {}; // Duplicate filter groups cannot be distinguished in a Portal response.
        match = &filter;
    }
    return match ? match->index : std::nullopt;
}

NativeResult response(DBusMessage* message, const NativeRequest& request, const std::vector<PortalFilter>& filters,
                      const std::filesystem::path& mount)
{
    if (!dbus_message_has_signature(message, "ua{sv}"))
        return failure(DialogErrorCode::InvalidResult, "Invalid file chooser response");
    DBusMessageIter top;
    dbus_message_iter_init(message, &top);
    auto code = value<dbus_uint32_t>(top);
    if (code == 1) return cancelled(CancelReason::User);
    if (code != 0) return failure(DialogErrorCode::BackendError, "File chooser failed", requestInterface, code);
    dbus_message_iter_next(&top);
    DBusMessageIter results;
    dbus_message_iter_recurse(&top, &results);
    const bool save = isSave(request.operation);
    const auto kind = request.operation == Operation::Folder ? DocumentKind::Directory : DocumentKind::File;
    const bool multiple = request.operation == Operation::Open && request.options.allowMultiple;
    NativeResult result;
    size_t count = 0;
    for (; dbus_message_iter_get_arg_type(&results) == DBUS_TYPE_DICT_ENTRY; dbus_message_iter_next(&results)) {
        DBusMessageIter member, variant;
        dbus_message_iter_recurse(&results, &member);
        std::string_view key(value<const char*>(member));
        dbus_message_iter_next(&member);
        dbus_message_iter_recurse(&member, &variant);
        std::unique_ptr<char, decltype(&dbus_free)> signature(dbus_message_iter_get_signature(&variant), dbus_free);
        if (!signature) throw std::bad_alloc{};
        if (key == "current_filter" && std::strcmp(signature.get(), "(sa(us))") == 0) {
            result.selectedFilter = filterIndex(variant, filters);
        } else if (key == "uris" && std::strcmp(signature.get(), "as") == 0) {
            DBusMessageIter uris;
            dbus_message_iter_recurse(&variant, &uris);
            for (; dbus_message_iter_get_arg_type(&uris) == DBUS_TYPE_STRING; dbus_message_iter_next(&uris)) {
                ++count;
                if (!multiple && count != 1)
                    return failure(DialogErrorCode::InvalidResult, "Expected exactly one selected item");
                if (multiple && count > request.options.maxSelectionCount)
                    return failure(DialogErrorCode::LimitExceeded, "Too many files selected");
                auto path = fileUri(value<const char*>(uris));
                if (!path) return failure(DialogErrorCode::InvalidResult, "File chooser returned an invalid file URI");
                auto document = beneath(*path, mount) ? localPortalLocation(*path, kind, save) :
                                save ? localSaveLocation(*path) :
                                kind == DocumentKind::Directory ? localSelectedDirectory(*path) :
                                localDocument(*path, kind);
                if (save) {
                    result.displayName = document.displayName();
                    result.target = std::move(document);
                } else {
                    result.documents.push_back(std::move(document));
                }
            }
        }
    }
    if (!count) return failure(DialogErrorCode::InvalidResult, "File chooser returned no files");
    result.status = DialogStatus::Ok;
    return result;
}

class PortalWorker {
public:
    ~PortalWorker() { shutdown(); }

    void start()
    {
        std::lock_guard lock(_mutex);
        if (_thread.joinable()) return;
        if (!dbus_threads_init_default()) {
            _version = -1;
            return;
        }
        try {
            _thread = std::thread([this] { run(); });
        } catch (const std::system_error&) {
            _version = -1;
        }
    }

    void submit(NativeRequest request, NativeCallback callback, std::string parent)
    {
        start();
        std::unique_lock lock(_mutex);
        if (!_thread.joinable() || _stopping || _activeId || _pending || _finished) {
            lock.unlock();
            callback(failure(DialogErrorCode::Unavailable, "Could not queue file chooser request"));
            return;
        }
        _pending.emplace(Task{std::move(request), std::move(callback), std::move(parent)});
        _wake.notify_one();
    }

    void cancel(uint64_t id)
    {
        std::lock_guard lock(_mutex);
        if (_activeId == id || (_pending && _pending->request.id == id)) _cancelledId = id;
    }

    struct Completion {
        NativeCallback callback;
        NativeResult result;
    };
    std::optional<Completion> takeCompletion()
    {
        std::lock_guard lock(_mutex);
        auto completion = std::move(_finished);
        _finished.reset();
        return completion;
    }

    int version() const { return _version.load(); }

    void shutdown()
    {
        {
            std::lock_guard lock(_mutex);
            if (!_thread.joinable()) return;
            _stopping = true;
            _wake.notify_one();
        }
        // No operation on this worker uses the window thread or waits for client input.
        _thread.join();
        std::lock_guard lock(_mutex);
        _stopping = false;
        _version = 0;
    }

private:
    struct Task {
        NativeRequest request;
        NativeCallback callback;
        std::string parent;
    };

    bool cancellationRequested(uint64_t id)
    {
        std::lock_guard lock(_mutex);
        return _stopping || _cancelledId == id;
    }

    FileDialogError probe()
    {
        if (!_bus || !dbus_connection_get_is_connected(_bus.get())) {
            BusError error;
            _bus.reset(dbus_bus_get_private(DBUS_BUS_SESSION, &error.value));
            if (!_bus) return busFailure(error, DialogErrorCode::Unavailable, "No desktop session bus").error;
            dbus_connection_set_exit_on_disconnect(_bus.get(), FALSE);
            // Older portals choose their own request path. Subscribe before sending the
            // chooser method and check the exact path and unique sender once it replies.
            dbus_bus_add_match(_bus.get(),
                "type='signal',sender='org.freedesktop.portal.Desktop',"
                "interface='org.freedesktop.portal.Request',member='Response',"
                "path_namespace='/org/freedesktop/portal/desktop/request'", &error.value);
            if (!dbus_error_is_set(&error.value)) {
                dbus_bus_add_match(_bus.get(),
                    "type='signal',sender='org.freedesktop.DBus',interface='org.freedesktop.DBus',"
                    "member='NameOwnerChanged',arg0='org.freedesktop.portal.Desktop'", &error.value);
            }
            if (dbus_error_is_set(&error.value)) {
                _bus.reset();
                return busFailure(error, DialogErrorCode::Unavailable, "Could not subscribe to file chooser events").error;
            }
        }

        Message get(dbus_message_new_method_call(portal, desktop, DBUS_INTERFACE_PROPERTIES, "Get"));
        if (!get) throw std::bad_alloc{};
        DBusMessageIter args;
        dbus_message_iter_init_append(get.get(), &args);
        append(args, DBUS_TYPE_STRING, chooser);
        const char* property = "version";
        append(args, DBUS_TYPE_STRING, property);
        BusError error;
        const auto reply = call(_bus.get(), get, methodTimeoutMs, error);
        if (!reply) return busFailure(error, DialogErrorCode::Unavailable, "No FileChooser portal").error;
        DBusMessageIter top, variant;
        if (!dbus_message_has_signature(reply.get(), "v") || !dbus_message_iter_init(reply.get(), &top))
            return {DialogErrorCode::Unavailable, "FileChooser portal returned an invalid version"};
        dbus_message_iter_recurse(&top, &variant);
        if (dbus_message_iter_get_arg_type(&variant) != DBUS_TYPE_UINT32)
            return {DialogErrorCode::Unavailable, "FileChooser portal returned an invalid version"};
        auto version = value<dbus_uint32_t>(variant);
        if (!version) return {DialogErrorCode::Unavailable, "No FileChooser portal"};
        const auto sender = dbus_message_get_sender(reply.get());
        if (!sender || *sender != ':') return {DialogErrorCode::Unavailable, "Invalid FileChooser portal owner"};
        _portalOwner = sender;
        _version = static_cast<int>(std::min<dbus_uint32_t>(version, 4));
        return {};
    }

    bool portalDisconnected(DBusMessage* message, const char* peer)
    {
        const char *name = nullptr, *previous = nullptr, *next = nullptr;
        return dbus_message_is_signal(message, DBUS_INTERFACE_DBUS, "NameOwnerChanged") &&
               dbus_message_has_sender(message, DBUS_SERVICE_DBUS) &&
               dbus_message_get_args(message, nullptr, DBUS_TYPE_STRING, &name, DBUS_TYPE_STRING, &previous,
                                     DBUS_TYPE_STRING, &next, DBUS_TYPE_INVALID) &&
               std::strcmp(name, portal) == 0 && std::strcmp(previous, peer) == 0;
    }

    void close(const char* sender, const char* path)
    {
        if (!sender || !dbus_connection_get_is_connected(_bus.get())) return;
        Message method(dbus_message_new_method_call(sender, path, requestInterface, "Close"));
        if (method) {
            BusError error;
            if (!call(_bus.get(), method, closeTimeoutMs, error)) {
                _bus.reset();
                _version = -1;
            }
        }
    }

    NativeResult choose(const Task& task)
    {
        const auto& request = task.request;
        if (cancellationRequested(request.id)) return cancelled(CancelReason::Caller);
        if (_version <= 0 || !_bus || !dbus_connection_get_is_connected(_bus.get())) {
            auto error = probe();
            if (error) {
                _version = -1;
                NativeResult result;
                result.error = std::move(error);
                return result;
            }
        }
        if (request.operation == Operation::Folder && _version < 3)
            return failure(DialogErrorCode::UnsupportedFeature, "Choosing directories requires FileChooser version 3");
        const auto filters = makeFilters(request);
        const auto token = "cocos_" + std::to_string(request.id);
        std::string sender = dbus_bus_get_unique_name(_bus.get()) + 1;
        std::replace(sender.begin(), sender.end(), '.', '_');
        const auto expected = requestPrefix + sender + '/' + token;
        const auto method = chooserCall(request, task.parent, token, filters, isSave(request.operation) || _version >= 4);
        if (cancellationRequested(request.id)) return cancelled(CancelReason::Caller);
        BusError error;
        const auto reply = call(_bus.get(), method, methodTimeoutMs, error);
        if (!reply) {
            // A method timeout may leave a request on the server. The private
            // connection's disappearance lets the portal discard any outstanding UI.
            _bus.reset();
            _version = -1;
            return busFailure(error, DialogErrorCode::BackendError, "File chooser method failed");
        }
        const auto peer = dbus_message_get_sender(reply.get());
        const char* path = nullptr;
        if (!dbus_message_get_args(reply.get(), nullptr, DBUS_TYPE_OBJECT_PATH, &path, DBUS_TYPE_INVALID) ||
            !std::string_view(path).starts_with(requestPrefix) || !peer || *peer != ':') {
            close(peer, expected.c_str());
            return failure(DialogErrorCode::InvalidResult, "File chooser returned an invalid request handle");
        }
        while (!cancellationRequested(request.id)) {
            if (!dbus_connection_read_write(_bus.get(), 25)) break;
            while (Message message{dbus_connection_pop_message(_bus.get())}) {
                if (dbus_message_is_signal(message.get(), requestInterface, "Response") &&
                    dbus_message_has_path(message.get(), path) && dbus_message_has_sender(message.get(), peer)) {
                    return response(message.get(), request, filters, _documentMount);
                }
                if (portalDisconnected(message.get(), peer)) {
                    _version = -1;
                    return failure(DialogErrorCode::Unavailable, "FileChooser portal disconnected");
                }
            }
        }
        if (cancellationRequested(request.id)) {
            close(peer, path);
            return cancelled(CancelReason::Caller);
        }
        _version = -1;
        return failure(DialogErrorCode::Unavailable, "Desktop session bus disconnected");
    }

    void discoverMount()
    {
        if (const auto runtime = std::getenv("XDG_RUNTIME_DIR"))
            _documentMount = std::filesystem::path(runtime) / "doc";
        if (!_bus) return;
        Message method(dbus_message_new_method_call("org.freedesktop.portal.Documents",
            "/org/freedesktop/portal/documents", "org.freedesktop.portal.Documents", "GetMountPoint"));
        if (!method) return;
        BusError error;
        auto reply = call(_bus.get(), method, closeTimeoutMs, error);
        if (reply && dbus_message_has_signature(reply.get(), "ay")) {
            DBusMessageIter top, bytes;
            dbus_message_iter_init(reply.get(), &top);
            dbus_message_iter_recurse(&top, &bytes);
            const char* path = nullptr;
            int size = 0;
            dbus_message_iter_get_fixed_array(&bytes, &path, &size);
            if (path && size > 1 && path[0] == '/' && path[size - 1] == '\0' &&
                !std::memchr(path, '\0', size - 1))
                _documentMount = path;
        }
        if (!_documentMount.has_filename()) _documentMount = _documentMount.parent_path();
    }

    void refresh()
    {
        try {
            if (_version > 0) {
                if (!_bus || !dbus_connection_read_write(_bus.get(), 0)) {
                    _version = -1;
                } else {
                    while (Message message{dbus_connection_pop_message(_bus.get())})
                        if (portalDisconnected(message.get(), _portalOwner.c_str())) _version = -1;
                }
            }
            if (_version <= 0) {
                if (probe()) _version = -1;
                else discoverMount();
            }
        } catch (const std::bad_alloc&) {
            _version = -1;
        }
    }

    void run()
    {
        refresh();
        for (;;) {
            std::unique_lock lock(_mutex);
            if (!_wake.wait_for(lock, std::chrono::seconds(2), [&] { return _pending || _stopping; })) {
                lock.unlock();
                refresh();
                continue;
            }
            if (!_pending && _stopping) break;
            auto task = std::move(*_pending);
            _pending.reset();
            _activeId = task.request.id;
            lock.unlock();
            NativeResult result;
            try {
                result = choose(task);
            } catch (const std::bad_alloc&) {
                _bus.reset();
                _version = -1;
                result.error.code = DialogErrorCode::OutOfMemory;
            } catch (const std::filesystem::filesystem_error&) {
                result = failure(DialogErrorCode::IoError, "Could not inspect the selected file location");
            }
            lock.lock();
            _finished.emplace(Completion{std::move(task.callback), std::move(result)});
            _activeId = _cancelledId = 0;
        }
        _bus.reset();
        _documentMount.clear();
    }

    std::atomic<int> _version{0}; // 0 probing, -1 unavailable, otherwise interface version
    Connection _bus;
    std::string _portalOwner;
    std::filesystem::path _documentMount;
    std::mutex _mutex;
    std::condition_variable _wake;
    std::thread _thread;
    std::optional<Task> _pending;
    std::optional<Completion> _finished;
    uint64_t _activeId = 0, _cancelledId = 0;
    bool _stopping = false;
};

PortalWorker worker;

#ifdef CC_DIALOG_WAYLAND
// These proxies use GLFW's default event queue. Only the owner thread handles
// them, with GLFW retaining responsibility for polling and reading the display.
struct WaylandParent {
    GLFWwindow* window = nullptr;
    wl_display* display = nullptr;
    wl_surface* surface = nullptr;
    wl_registry* registry = nullptr;
    wl_callback* sync = nullptr;
    zxdg_exporter_v2* exporter = nullptr;
    zxdg_exported_v2* exported = nullptr;
    uint32_t global = 0;
    bool registryReady = false, gotHandle = false, allocationFailed = false;
    std::string handle;
    std::chrono::steady_clock::time_point deadline;
    NativeRequest request;
    NativeCallback callback;

    ~WaylandParent()
    {
        if (exported) zxdg_exported_v2_destroy(exported);
        if (exporter) zxdg_exporter_v2_destroy(exporter);
        if (sync) wl_callback_destroy(sync);
        if (registry) wl_registry_destroy(registry);
        if (display) wl_display_flush(display);
    }

    static void globalAdded(void* data, wl_registry*, uint32_t name, const char* interface, uint32_t version)
    {
        if (version && std::strcmp(interface, zxdg_exporter_v2_interface.name) == 0)
            static_cast<WaylandParent*>(data)->global = name;
    }
    static void globalRemoved(void* data, wl_registry*, uint32_t name)
    {
        auto& parent = *static_cast<WaylandParent*>(data);
        if (parent.global == name) parent.global = 0;
    }
    static void synced(void* data, wl_callback* callback, uint32_t)
    {
        auto& parent = *static_cast<WaylandParent*>(data);
        wl_callback_destroy(callback);
        parent.sync = nullptr;
        parent.registryReady = true;
    }
    static void receivedHandle(void* data, zxdg_exported_v2*, const char* handle)
    {
        auto& parent = *static_cast<WaylandParent*>(data);
        try {
            if (handle && *handle) parent.handle = std::string("wayland:") + handle;
        } catch (const std::bad_alloc&) {
            parent.allocationFailed = true;
        }
        parent.gotHandle = true;
    }

    bool discover(GLFWwindow* owner)
    {
        window = owner;
        display = glfwGetWaylandDisplay();
        surface = glfwGetWaylandWindow(window);
        if (!display || !surface) return false;
        if (glfwGetWindowAttrib(window, GLFW_VISIBLE) != GLFW_TRUE ||
            glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_TRUE)
            return false;
        static constexpr wl_registry_listener registryListener{globalAdded, globalRemoved};
        static constexpr wl_callback_listener syncListener{synced};
        registry = wl_display_get_registry(display);
        if (!registry || wl_registry_add_listener(registry, &registryListener, this) != 0) return false;
        sync = wl_display_sync(display);
        if (!sync || wl_callback_add_listener(sync, &syncListener, this) != 0) return false;
        deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        wl_display_flush(display);
        return true;
    }

    bool exportSurface()
    {
        if (glfwGetWaylandWindow(window) != surface || glfwGetWindowAttrib(window, GLFW_VISIBLE) != GLFW_TRUE)
            return false;
        static constexpr zxdg_exported_v2_listener listener{receivedHandle};
        exporter = static_cast<zxdg_exporter_v2*>(wl_registry_bind(registry, global, &zxdg_exporter_v2_interface, 1));
        if (!exporter) return false;
        exported = zxdg_exporter_v2_export_toplevel(exporter, surface);
        if (!exported || zxdg_exported_v2_add_listener(exported, &listener, this) != 0) return false;
        wl_display_flush(display);
        return true;
    }
};

std::unique_ptr<WaylandParent> wayland;

void failWayland(NativeResult result)
{
    auto callback = std::move(wayland->callback);
    wayland.reset();
    callback(std::move(result));
}
#endif
} // namespace

DialogCapabilities nativeCapabilities()
{
    DialogCapabilities caps;
    caps.backend = "portal";
    auto version = worker.version();
    caps.available = version > 0;
    if (!caps.available) {
        caps.unavailableReason = version == 0 ? "Probing the desktop portal" : "FileChooser portal unavailable";
        return caps;
    }
    caps.openFiles = caps.multipleFiles = caps.chooseSaveTarget = caps.exportFile = true;
    caps.pickFolder = version >= 3;
    caps.initialDirectoryHint = version >= 4;
    caps.selectedFilter = caps.physicalDismiss = true;
    return caps;
}

void startNative()
{
    worker.start();
}

void presentNative(NativeRequest request, NativeCallback callback)
{
    auto view = dynamic_cast<GLViewImpl*>(request.view);
    auto window = view ? view->getWindow() : nullptr;
    if (!window) {
        callback(failure(DialogErrorCode::ParentClosed, "The dialog owner was closed"));
        return;
    }
    auto utf8 = [](const std::string& value) {
        return value.find('\0') == std::string::npos && dbus_validate_utf8(value.c_str(), nullptr);
    };
    if (!utf8(request.options.title) || !utf8(request.suggestedName)) {
        callback(failure(DialogErrorCode::EncodingError, "Dialog title or file name is not valid UTF-8"));
        return;
    }
    for (const auto& filter : request.options.filters) {
        if (!utf8(filter.label) || !std::all_of(filter.extensions.begin(), filter.extensions.end(), utf8) ||
            !std::all_of(filter.mimeTypes.begin(), filter.mimeTypes.end(), utf8)) {
            callback(failure(DialogErrorCode::EncodingError, "Dialog filter is not valid UTF-8"));
            return;
        }
    }
    request.view = nullptr;
#ifdef CC_DIALOG_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11) {
        auto xid = glfwGetX11Window(window);
        if (!xid) {
            callback(failure(DialogErrorCode::ParentClosed, "The X11 dialog owner was closed"));
            return;
        }
        char parent[32];
        std::snprintf(parent, sizeof(parent), "x11:%lx", xid);
        worker.submit(std::move(request), std::move(callback), parent);
        return;
    }
#endif
#ifdef CC_DIALOG_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) {
        auto pending = std::make_unique<WaylandParent>();
        if (!pending->discover(window)) {
            callback(failure(DialogErrorCode::Unavailable, "Could not discover the Wayland dialog owner"));
            return;
        }
        pending->request = std::move(request);
        pending->callback = std::move(callback);
        wayland = std::move(pending);
        return;
    }
#endif
    callback(failure(DialogErrorCode::UnsupportedFeature, "Unsupported GLFW window backend for the desktop portal"));
}

void pumpNative()
{
    if (auto completion = worker.takeCompletion()) {
        completion->callback(std::move(completion->result));
    }
#ifdef CC_DIALOG_WAYLAND
    if (!wayland || !wayland->callback) return;
    if (std::chrono::steady_clock::now() >= wayland->deadline) {
        failWayland(failure(DialogErrorCode::Timeout, "Timed out exporting the Wayland dialog owner"));
    } else if (wayland->registryReady && !wayland->exported) {
        if (!wayland->global)
            failWayland(failure(DialogErrorCode::UnsupportedFeature, "The compositor lacks xdg-foreign v2"));
        else if (!wayland->exportSurface())
            failWayland(failure(DialogErrorCode::Unavailable, "Could not export the Wayland dialog owner"));
    } else if (wayland->gotHandle) {
        if (wayland->handle.empty()) {
            failWayland(failure(wayland->allocationFailed ? DialogErrorCode::OutOfMemory : DialogErrorCode::InvalidResult,
                                "Compositor returned no Wayland parent handle"));
            return;
        }
        auto command = std::move(wayland->request);
        auto callback = std::move(wayland->callback);
        auto parent = std::move(wayland->handle);
        worker.submit(std::move(command),
            [callback = std::move(callback)](NativeResult result) mutable {
                wayland.reset();
                callback(std::move(result));
            }, std::move(parent));
    }
#endif
}

void cancelNative(uint64_t id)
{
#ifdef CC_DIALOG_WAYLAND
    if (wayland && wayland->request.id == id && wayland->callback) {
        failWayland(cancelled(CancelReason::Caller));
        return;
    }
#endif
    worker.cancel(id);
}

void shutdownNative()
{
    worker.shutdown();
#ifdef CC_DIALOG_WAYLAND
    if (wayland && wayland->callback) failWayland(cancelled(CancelReason::Caller));
    wayland.reset();
#endif
    if (auto completion = worker.takeCompletion())
        completion->callback(std::move(completion->result));
}
} // namespace cc::dialog
