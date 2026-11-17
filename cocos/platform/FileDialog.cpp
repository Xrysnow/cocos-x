#include "platform/FileDialogInternal.h"
#include "platform/GLView.h"
#include "base/ccUTF8.h"
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <deque>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace cc::dialog {
#if !CC_ENABLE_FILE_DIALOG
DialogCapabilities nativeCapabilities() { DialogCapabilities c; c.unavailableReason = "Disabled"; return c; }
void presentNative(NativeRequest, NativeCallback callback) {
    NativeResult result; result.error = {DialogErrorCode::Unavailable, "File dialogs disabled"}; callback(std::move(result));
}
void cancelNative(uint64_t) {}
void shutdownNative() {}
#elif CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || defined(__APPLE__)
void startNative();
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
void pumpNative();
#endif
#endif

namespace {
enum class Phase { Pending, Writing, Cancelled, Done };
struct RequestState {
    uint64_t id;
    std::atomic<Phase> phase{Phase::Pending};
    std::atomic<bool> stopping{false};
    std::atomic<int64_t> deadline{0};
    explicit RequestState(uint64_t value) : id(value) {}
    static int64_t now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    void timeLimit(uint32_t seconds) { deadline = seconds ? now() + int64_t(seconds) * 1000 : 0; }
    bool beginWrite() {
        auto expected = Phase::Pending;
        return phase.compare_exchange_strong(expected, Phase::Writing);
    }
};
using State = std::shared_ptr<RequestState>;
AccessJob accessJob(const State& state) {
    return {[state] { return state->stopping || state->phase == Phase::Cancelled; }, [state] { return state->beginWrite(); }};
}
struct Outcome : NativeResult { std::string nextPage; };
using Completion = std::function<void(Outcome)>;
using Task = std::function<void()>;
struct Entry { State state; Completion deliver; };
struct WorkQueue {
    std::mutex mutex;
    std::condition_variable wake;
    std::deque<Task> tasks;
    bool closed = false;
};
struct Session {
    std::unordered_map<uint64_t, Entry> active;
    std::unordered_map<uint64_t, GLView*> parents;
    GLView* view = nullptr;
    uint64_t generation = 0, slot = 0, slotParent = 0;
    Operation slotOperation = Operation::Open;
    IntrusivePtr<GLView> nativeOwner;
    std::mutex mutex;
    std::deque<Task> mailbox;
    std::shared_ptr<WorkQueue> io = std::make_shared<WorkQueue>();
    bool closed = false;
    std::thread worker;
    void post(Task task) {
        std::lock_guard lock(mutex);
        if (!closed) mailbox.push_back(std::move(task));
    }
    bool enqueue(Task task) {
        std::lock_guard lock(io->mutex);
        if (io->closed || io->tasks.size() >= 16) return false;
        if (!worker.joinable()) worker = std::thread([queue = io] {
            for (;;) {
                Task next;
                {
                    std::unique_lock guard(queue->mutex);
                    queue->wake.wait(guard, [&] { return queue->closed || !queue->tasks.empty(); });
                    if (queue->closed) return;
                    next = std::move(queue->tasks.front()); queue->tasks.pop_front();
                }
                next();
            }
        });
        io->tasks.push_back(std::move(task));
        io->wake.notify_one();
        return true;
    }
    void close() {
        std::deque<Task> events, jobs;
        {
            std::lock_guard lock(mutex);
            closed = true;
            events.swap(mailbox);
        }
        {
            std::lock_guard lock(io->mutex);
            io->closed = true;
            jobs.swap(io->tasks);
        }
        io->wake.notify_all();
        if (worker.joinable()) {
#if defined(__APPLE__) || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            // A provider may still need the main loop to finish its cancelled access.
            // The thread owns its queue. Its only route back to this session is weak.
            worker.detach();
#else
            worker.join();
#endif
        }
    }
    ~Session() { close(); }
};
// Accessed on the engine thread. Foreign threads only inspect the atomic running flag.
thread_local std::shared_ptr<Session> current;
std::atomic<bool> running{false};
std::atomic<uint64_t> sequence{0};
std::mutex capsMutex;
DialogCapabilities caps;

Outcome failed(DialogErrorCode code, std::string message) {
    Outcome result; result.error = {code, std::move(message)}; return result;
}
using WeakSession = std::weak_ptr<Session>;
void deliver(Session& session, uint64_t id, Outcome result) {
    auto it = session.active.find(id);
    if (it == session.active.end()) return;
    auto callback = std::move(it->second.deliver);
    session.active.erase(it);
    callback(std::move(result));
}
void finish(const WeakSession& weak, const State& state, Outcome result) {
    auto phase = state->phase.load();
    do {
        if (phase == Phase::Cancelled || phase == Phase::Done) return;
    } while (!state->phase.compare_exchange_weak(phase, Phase::Done));
    if (auto session = weak.lock())
        session->post([weak, id = state->id, result = std::move(result)]() mutable {
            if (auto s = weak.lock()) deliver(*s, id, std::move(result));
        });
}
void releaseSlot(Session& s, uint64_t id) {
    if (s.slot == id) { s.slot = 0; s.slotParent = 0; s.nativeOwner.reset(); }
}
void abort(Session& s, const State& state, bool parentClosed) {
    Outcome result;
    if (parentClosed) result.error = {DialogErrorCode::ParentClosed, "Dialog owner closed"};
    else { result.status = DialogStatus::Cancelled; result.cancelReason = CancelReason::Caller; }
    if (s.slot == state->id) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        if (s.nativeOwner && s.slotOperation == Operation::Export) result.effect = ExternalEffect::PartialPossible;
#endif
        if (s.nativeOwner) cancelNative(state->id);
        else releaseSlot(s, state->id);
    }
    WeakSession weak = current;
    s.post([weak, id = state->id, result = std::move(result)]() mutable {
        if (auto session = weak.lock()) deliver(*session, id, std::move(result));
    });
}

template<class Start>
DialogSubmission submit(Completion completion, Start start) {
    if (!current) {
        const bool wrongThread = running.load();
        CCASSERT(!wrongThread, "Submit file dialog requests on the engine thread");
        return {{}, {wrongThread ? DialogErrorCode::WrongThread : DialogErrorCode::NotInitialized, "File dialog requires the active engine thread"}};
    }
    if (!completion) return {{}, {DialogErrorCode::InvalidArgument, "Missing completion callback"}};
    uint64_t id = ++sequence;
    try {
        auto state = std::make_shared<RequestState>(id);
        current->active.emplace(id, Entry{state, std::move(completion)});
        start(current, state);
        return {DialogRequest(id), {}};
    } catch (const std::bad_alloc&) {
        releaseSlot(*current, id); current->active.erase(id);
        return {{}, {DialogErrorCode::OutOfMemory}};
    } catch (const std::exception& error) {
        releaseSlot(*current, id); current->active.erase(id);
        return {{}, {DialogErrorCode::BackendError, error.what()}};
    }
}

template<class Work>
bool schedule(const std::shared_ptr<Session>& s, const State& state, Work work) {
    WeakSession weak = s;
    return s->enqueue([weak, state, work = std::move(work)]() mutable {
        try {
            if (state->phase == Phase::Pending) work();
        } catch (const std::exception& ex) {
            if (auto active = weak.lock())
                active->post([weak, state] { if (auto s = weak.lock()) releaseSlot(*s, state->id); });
            finish(weak, state, failed(DialogErrorCode::IoError, ex.what()));
        } catch (...) {
            if (auto active = weak.lock())
                active->post([weak, state] { if (auto s = weak.lock()) releaseSlot(*s, state->id); });
            finish(weak, state, failed(DialogErrorCode::BackendError, "Document operation raised an exception"));
        }
    });
}

void received(const std::shared_ptr<Session>& s, const State& state, Operation operation,
              std::shared_ptr<Snapshot> stage, TransferLimits limits, NativeResult native, uint32_t maximum) {
    if (s->slot != state->id || !s->nativeOwner) return;
    releaseSlot(*s, state->id);
    if (state->phase == Phase::Cancelled) return;
    Outcome result;
    static_cast<NativeResult&>(result) = std::move(native);
    if (result.status != DialogStatus::Ok) {
        if (result.status == DialogStatus::Error && !result.error)
            result.error = {DialogErrorCode::BackendError, "Native picker failed"};
        if (result.status == DialogStatus::Cancelled && result.cancelReason == CancelReason::None)
            result.cancelReason = CancelReason::User;
    } else if (operation == Operation::Open || operation == Operation::Folder) {
        const auto kind = operation == Operation::Folder ? DocumentKind::Directory : DocumentKind::File;
        if (result.documents.empty() || std::any_of(result.documents.begin(), result.documents.end(),
                [kind](const auto& d) { return !d || d.kind() != kind; }))
            result = failed(DialogErrorCode::InvalidResult, "Picker returned an empty or invalid selection");
        else if (result.documents.size() > maximum)
            result = failed(DialogErrorCode::LimitExceeded, "Selection exceeds requested count");
    } else if (!result.target && !(operation == Operation::Export && result.effect == ExternalEffect::Committed))
        result = failed(DialogErrorCode::InvalidResult, "Missing save destination");
    else if (operation == Operation::Export && result.effect != ExternalEffect::Committed) {
        WeakSession weak = s;
        state->timeLimit(limits.timeoutSeconds);
        const bool accepted = schedule(s, state, [weak, state, stage, limits, target = result.target] {
            if (!state->beginWrite()) return;
            Outcome written;
            written.error = Documents::get(target)->write({}, [&](io::Stream& out) {
                return copyDocument(stage->document, out, limits, accessJob(state).cancelled);
            }, written.target, written.effect);
            written.status = written.error ? DialogStatus::Error : DialogStatus::Ok;
            written.displayName = written.target ? written.target.displayName() : target.displayName();
            finish(weak, state, std::move(written));
        });
        if (!accepted) finish(s, state, failed(DialogErrorCode::Busy, "Document I/O queue is full"));
        return;
    }
    finish(s, state, std::move(result));
}

void show(const std::shared_ptr<Session>& s, const State& state, NativeRequest request,
          std::shared_ptr<Snapshot> stage, TransferLimits limits) {
    if (s->slot != state->id || state->phase != Phase::Pending) return;
    auto it = s->parents.find(s->slotParent);
    if (it == s->parents.end()) {
        releaseSlot(*s, state->id);
        finish(s, state, failed(DialogErrorCode::ParentClosed, "Dialog owner closed before presentation"));
        return;
    }
    s->nativeOwner = IntrusivePtr<GLView>(it->second);
    request.view = it->second;
    if (stage) request.stagingPath = *stage->document.tryGetLocalPath();
    request.beginExternalWrite = [state] { return state->beginWrite(); };
    const auto op = request.operation;
    const auto max = request.options.allowMultiple ? request.options.maxSelectionCount : 1u;
    WeakSession weak = s;
    try {
        presentNative(std::move(request), [weak, state, op, stage, limits, max](NativeResult result) {
            if (auto s = weak.lock()) s->post([weak, state, op, stage, limits, max, result = std::move(result)]() mutable {
                if (auto s = weak.lock()) received(s, state, op, stage, limits, std::move(result), max);
            });
        });
    } catch (const std::exception& e) {
        releaseSlot(*s, state->id);
        finish(s, state, failed(DialogErrorCode::BackendError, e.what()));
    }
}

bool textValid(const std::string& text) {
    return text.find('\0') == std::string::npos && StringUtils::isLegalUTF8String(text.data(), text.size());
}
bool filterValid(const FileDialogFilter& f) {
    auto field = [](const std::string& v) {
        return !v.empty() && textValid(v) && std::none_of(v.begin(), v.end(), [](unsigned char c) { return c < 32 || c == 127; });
    };
    return textValid(f.label) && std::all_of(f.extensions.begin(), f.extensions.end(), [&](const auto& ext) {
        return field(ext) && ext.front() != '.' && ext.find_first_of("/\\*?[];,:|") == std::string::npos;
    }) && std::all_of(f.mimeTypes.begin(), f.mimeTypes.end(), field) &&
           std::all_of(f.appleTypeIdentifiers.begin(), f.appleTypeIdentifiers.end(), field);
}
DialogSubmission picker(NativeRequest request, DocumentHandle source, TransferLimits limits, Completion cb) {
    return submit(std::move(cb), [&](const std::shared_ptr<Session>& s, const State& state) {
        auto& o = request.options;
        const auto op = request.operation;
        request.id = state->id;
        auto reject = [&](DialogErrorCode code, std::string why) { finish(s, state, failed(code, std::move(why))); };
        auto c = FileDialog::capabilities();
        if (!c.available) return reject(DialogErrorCode::Unavailable, c.unavailableReason);
        if ((op == Operation::SaveTarget && !c.chooseSaveTarget) || (op == Operation::Open && !c.openFiles) ||
            (op == Operation::Folder && !c.pickFolder) || (op == Operation::Export && !c.exportFile) ||
            (o.allowMultiple && !c.multipleFiles)) return reject(DialogErrorCode::UnsupportedFeature, "Picker operation unavailable");
        auto parent = o.parent ? o.parent.generation() : s->generation;
        if (!s->parents.count(parent))
            return reject(DialogErrorCode::ParentClosed, "No current dialog owner");
        if (!textValid(o.title) || (o.initialDirectory && (!*o.initialDirectory || o.initialDirectory->kind() != DocumentKind::Directory)) ||
            !o.maxSelectionCount || !std::all_of(o.filters.begin(), o.filters.end(), filterValid))
            return reject(DialogErrorCode::InvalidArgument, "Invalid picker options");
        if (op == Operation::Export || op == Operation::SaveTarget) {
            if (op == Operation::Export) {
                if (!source || source.kind() != DocumentKind::File || !limits.timeoutSeconds)
                    return reject(DialogErrorCode::InvalidArgument, "Expected a readable export source");
                if (request.suggestedName.empty()) request.suggestedName = source.displayName();
            }
            if (!request.suggestedName.empty()) {
                if (!validName(request.suggestedName)) return reject(DialogErrorCode::InvalidArgument, "Invalid suggested filename");
                if (!o.filters.empty() && !o.filters.front().extensions.empty() && request.suggestedName.find('.') == std::string::npos)
                    request.suggestedName += "." + o.filters.front().extensions.front();
            }
        }
        if (s->slot) return reject(DialogErrorCode::Busy, "Another picker is active");
        s->slot = state->id;
        s->slotParent = parent;
        s->slotOperation = op;
        WeakSession weak = s;
        if (op != Operation::Export) {
            s->post([weak, state, request = std::move(request), limits]() mutable {
                if (auto s = weak.lock()) show(s, state, std::move(request), {}, limits);
            });
        } else {
            state->timeLimit(limits.timeoutSeconds);
            const bool queued = schedule(s, state, [weak, state, source, request = std::move(request), limits]() mutable {
                std::shared_ptr<Snapshot> stage;
                auto error = prepareSnapshot(source, request.suggestedName, limits, accessJob(state), stage);
                state->deadline = 0; // Waiting for the user is unbounded.
                if (auto s = weak.lock()) s->post([weak, state, request = std::move(request), stage, limits, error]() mutable {
                    if (auto s = weak.lock()) {
                        if (error) {
                            releaseSlot(*s, state->id);
                            Outcome failed; failed.error = error; finish(s, state, std::move(failed));
                        } else show(s, state, std::move(request), std::move(stage), limits);
                    }
                });
            });
            if (!queued) {
                releaseSlot(*s, state->id);
                reject(DialogErrorCode::Busy, "Document I/O queue is full");
            }
        }
    });
}
}

void startSession() {
    if (current) return;
    current = std::make_shared<Session>(); running = true;
#if CC_ENABLE_FILE_DIALOG && (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || defined(__APPLE__))
    startNative();
#endif
    std::lock_guard lock(capsMutex);
    caps = nativeCapabilities();
}
void forgetView(GLView* view) {
    if (!current || !view) return;
    auto p = std::find_if(current->parents.begin(), current->parents.end(),
                          [view](const auto& entry) { return entry.second == view; });
    if (p == current->parents.end()) return;
    bool isOwner = current->slotParent == p->first;
    current->parents.erase(p);
    if (current->view == view) { current->view = nullptr; current->generation = 0; }
    auto it = current->active.find(current->slot);
    bool boundToView = true;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // A SAF activity outlives the rendering surface that launched it.
    boundToView = !current->nativeOwner;
#endif
    if (isOwner && boundToView && it != current->active.end()) {
        auto expected = Phase::Pending;
        if (it->second.state->phase.compare_exchange_strong(expected, Phase::Cancelled))
            abort(*current, it->second.state, true);
    }
}
void setView(GLView* view) {
    if (!current || current->view == view) return;
    forgetView(current->view);
    current->view = view;
    current->generation = DialogParent::registerView(view).generation();
}
void pump() {
    auto s = current;
    if (!s) return;
    const auto now = RequestState::now();
    for (const auto& [id, entry] : s->active) {
        auto& state = entry.state;
        const auto deadline = state->deadline.load();
        if (!deadline || deadline > now) continue;
        // A provider can block inside one native read/write. Report that timeout
        // even while the call unwinds, without claiming that an external write rolled back.
        auto phase = state->phase.load();
        while (phase == Phase::Pending || phase == Phase::Writing) {
            if (!state->phase.compare_exchange_weak(phase, Phase::Done)) continue;
            state->stopping = true;
            if (s->slot == id && !s->nativeOwner) releaseSlot(*s, id);
            auto r = failed(DialogErrorCode::Timeout, "Document provider timed out");
            if (phase == Phase::Writing) r.effect = ExternalEffect::Unknown;
            WeakSession weak = s;
            s->post([weak, id, r = std::move(r)]() mutable {
                if (auto session = weak.lock()) deliver(*session, id, std::move(r));
            });
            break;
        }
    }
#if CC_ENABLE_FILE_DIALOG && CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    pumpNative();
    { std::lock_guard lock(capsMutex); caps = nativeCapabilities(); }
#endif
    std::deque<Task> pending;
    { std::lock_guard lock(s->mutex); pending.swap(s->mailbox); }
    for (auto& task : pending) {
        if (current != s) break;
        try {
            task();
        } catch (const std::exception& e) {
            CCLOGERROR("File dialog callback: %s", e.what());
        } catch (...) {
            CCLOGERROR("File dialog callback raised an exception");
        }
    }
}
void stopSession() {
    auto s = std::move(current);
    if (!s) return;
    running = false;
    for (auto& [id, entry] : s->active) {
        entry.state->stopping = true;
        auto expected = Phase::Pending;
        entry.state->phase.compare_exchange_strong(expected, Phase::Cancelled);
    }
    shutdownNative();
    s->close();
    s->active.clear(); s->nativeOwner.reset();
    std::lock_guard lock(capsMutex); caps = {};
}

DialogSubmission submitAccess(AccessWork work, DocumentCallback cb, uint32_t timeoutSeconds) {
    if (!cb) return {{}, {DialogErrorCode::InvalidArgument, "Missing document callback"}};
    return submit([cb = std::move(cb)](Outcome r) {
        cb({r.status, r.cancelReason, std::move(r.error), std::move(r.documents), std::move(r.nextPage), r.effect});
    }, [&](const std::shared_ptr<Session>& s, const State& state) {
        WeakSession weak = s;
        state->timeLimit(timeoutSeconds);
        if (!schedule(s, state, [weak, state, work = std::move(work)] {
            auto r = work(accessJob(state));
            Outcome out;
            out.status = r.status; out.cancelReason = r.cancelReason; out.documents = std::move(r.documents);
            out.error = std::move(r.error); out.nextPage = std::move(r.nextPage); out.effect = r.effect;
            finish(weak, state, std::move(out));
        })) finish(s, state, failed(DialogErrorCode::Busy, "Document I/O queue is full"));
    });
}
}

namespace cc {
using namespace dialog;
DialogParent DialogParent::current() {
    DialogParent p;
    if (dialog::current && dialog::current->view) p._generation = dialog::current->generation;
    return p;
}
DialogParent DialogParent::registerView(GLView* view) {
    DialogParent p;
    if (!view || !dialog::current) return p;
    auto& parents = dialog::current->parents;
    for (auto [token, owner] : parents)
        if (owner == view) { p._generation = token; return p; }
    p._generation = ++sequence;
    parents.emplace(p._generation, view);
    return p;
}
void DialogParent::invalidate() const {
    if (!dialog::current) return;
    auto it = dialog::current->parents.find(_generation);
    if (it != dialog::current->parents.end()) forgetView(it->second);
}
CancelResult DialogRequest::cancel() const {
    if (!current) {
        CCASSERT(!running.load(), "Cancel file dialog requests on the engine thread");
        return CancelResult::AlreadyFinished;
    }
    auto it = current->active.find(_id);
    if (it == current->active.end()) return CancelResult::AlreadyFinished;
    auto state = it->second.state;
    auto phase = Phase::Pending;
    if (!state->phase.compare_exchange_strong(phase, Phase::Cancelled))
        return phase == Phase::Writing ? CancelResult::TooLate : CancelResult::AlreadyFinished;
    abort(*current, state, false);
    return CancelResult::Accepted;
}
DialogCapabilities FileDialog::capabilities() {
    std::lock_guard lock(capsMutex); return caps;
}
DialogSubmission FileDialog::openFiles(OpenFileOptions options, std::function<void(SelectionResult)> cb) {
    NativeRequest request; request.options = std::move(options);
    return picker(std::move(request), {}, {}, std::move(cb));
}
DialogSubmission FileDialog::pickFolder(FolderOptions o, std::function<void(SelectionResult)> cb) {
    NativeRequest request; request.operation = Operation::Folder;
    request.options.parent = o.parent; request.options.title = std::move(o.title); request.options.initialDirectory = std::move(o.initialDirectory);
    return picker(std::move(request), {}, {}, std::move(cb));
}
DialogSubmission FileDialog::chooseSaveTarget(SaveTargetOptions o, std::function<void(SaveTargetResult)> cb) {
    if (!cb) return {{}, {DialogErrorCode::InvalidArgument, "Missing completion callback"}};
    NativeRequest request; request.operation = Operation::SaveTarget;
    request.suggestedName = std::move(o.suggestedName); request.options = std::move(o);
    return picker(std::move(request), {}, {}, [cb = std::move(cb)](Outcome r) {
        cb({r.status, r.cancelReason, Documents::target(std::move(r.target)), r.selectedFilter, std::move(r.error)});
    });
}
DialogSubmission FileDialog::exportFile(ExportFileOptions o, DocumentHandle source, std::function<void(ExportResult)> cb) {
    if (!cb) return {{}, {DialogErrorCode::InvalidArgument, "Missing completion callback"}};
    NativeRequest request; request.operation = Operation::Export;
    request.options.title = std::move(o.title); request.options.parent = o.parent;
    request.options.initialDirectory = std::move(o.initialDirectory); request.suggestedName = std::move(o.suggestedName);
    request.options.filters.push_back(std::move(o.contentType)); request.options.allowAllFiles = false;
    return picker(std::move(request), std::move(source), o.limits, [cb = std::move(cb)](Outcome r) {
        ExportResult result{r.status, r.cancelReason, r.effect, {}, std::move(r.displayName), std::move(r.error)};
        if (r.target) result.destination = std::move(r.target);
        cb(std::move(result));
    });
}
}
