#include "io/HttpStream.h"
#include "curl/curl.h"
#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <limits>
#include <new>
#include <stdexcept>
#include <system_error>

namespace cocos2d::io
{
namespace
{
constexpr int PollIntervalMs = 50;

StreamError curlError(CURLcode code)
{
    ErrorCode error = ErrorCode::IoError;
    switch (code)
    {
    case CURLE_OPERATION_TIMEDOUT: error = ErrorCode::Timeout; break;
    case CURLE_OUT_OF_MEMORY: error = ErrorCode::OutOfMemory; break;
    case CURLE_URL_MALFORMAT: error = ErrorCode::InvalidArgument; break;
    case CURLE_UNSUPPORTED_PROTOCOL: error = ErrorCode::NotSupported; break;
    default: break;
    }
    return {error, static_cast<int>(code), ErrorDomain::Curl};
}

// Existing cocos curl users do not share an explicit global lifecycle. Retain
// this initialization until process exit instead of cleaning up beneath them.
CURLcode initializeCurl()
{
    static std::once_flag flag;
    static CURLcode result = CURLE_FAILED_INIT;
    std::call_once(flag, [] { result = curl_global_init(CURL_GLOBAL_DEFAULT); });
    return result;
}

bool equalsAscii(std::string_view left, std::string_view right) noexcept
{
    if (left.size() != right.size())
        return false;
    for (size_t i = 0; i < left.size(); ++i)
    {
        const auto c = left[i];
        if ((c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c) != right[i])
            return false;
    }
    return true;
}

std::string_view trim(std::string_view value) noexcept
{
    while (!value.empty() && (value.front() == ' ' || value.front() == '\t'))
        value.remove_prefix(1);
    while (!value.empty() && (value.back() == ' ' || value.back() == '\t' ||
                              value.back() == '\r' || value.back() == '\n'))
        value.remove_suffix(1);
    return value;
}

bool parseLength(std::string_view value, int64_t& result) noexcept
{
    // RFC Content-Length permits a list only when every value is identical.
    bool found = false;
    do
    {
        const auto comma = value.find(',');
        auto item = trim(value.substr(0, comma));
        if (item.empty())
            return false;
        int64_t number = 0;
        for (const char c : item)
        {
            if (c < '0' || c > '9' ||
                number > (std::numeric_limits<int64_t>::max() - (c - '0')) / 10)
                return false;
            number = number * 10 + (c - '0');
        }
        if (found && number != result)
            return false;
        result = number;
        found = true;
        if (comma == std::string_view::npos)
            return true;
        value.remove_prefix(comma + 1);
    } while (true);
}

bool validUrl(const std::string& url, bool& https)
{
    CURLU* parsed = curl_url();
    if (!parsed)
        throw std::bad_alloc();
    const auto result = curl_url_set(parsed, CURLUPART_URL, url.c_str(), 0);
    if (result == CURLUE_OUT_OF_MEMORY)
    {
        curl_url_cleanup(parsed);
        throw std::bad_alloc();
    }
    char* scheme = nullptr;
    char* host = nullptr;
    char* user = nullptr;
    char* password = nullptr;
    const bool valid = result == CURLUE_OK &&
        curl_url_get(parsed, CURLUPART_SCHEME, &scheme, 0) == CURLUE_OK &&
        curl_url_get(parsed, CURLUPART_HOST, &host, 0) == CURLUE_OK && host && *host &&
        (equalsAscii(scheme, "http") || equalsAscii(scheme, "https")) &&
        curl_url_get(parsed, CURLUPART_USER, &user, 0) == CURLUE_NO_USER &&
        curl_url_get(parsed, CURLUPART_PASSWORD, &password, 0) == CURLUE_NO_PASSWORD;
    https = valid && equalsAscii(scheme, "https");
    curl_free(scheme);
    curl_free(host);
    curl_free(user);
    curl_free(password);
    curl_url_cleanup(parsed);
    return valid;
}

IoResult stoppedResult(StreamError error, size_t transferred)
{
    if (error.code == ErrorCode::Cancelled)
        return {transferred, IoStatus::Cancelled, {}};
    if (error.code == ErrorCode::Timeout)
        return {transferred, IoStatus::Timeout, {}};
    return IoResult::failure(error, transferred);
}
}

struct HttpStream::State
{
    mutable std::mutex mutex;
    std::condition_variable changed;
    bool closed = true;
    bool cancelRequested = false;
    bool complete = false;
    StreamError error{};
    std::vector<uint8_t> queue;
    size_t head = 0;
    size_t queued = 0;
    size_t peak = 0;
    int64_t position = 0;
    uint64_t received = 0;
    bool paused = false;
    size_t pauseBytes = 0;
    long httpStatus = 0;
    std::optional<int64_t> knownLength;
    HttpStreamOptions options;
    std::string url;
    bool https = false;
    std::chrono::steady_clock::time_point started;

    // Header-parser state is private to the worker; shared metadata above is
    // published only for a final response. Count all redirect/1xx/trailer bytes.
    size_t headerBytes = 0;
    long blockStatus = 0;
    bool inHeaders = false;
    bool acceptBody = false;
    bool haveLength = false;
    int64_t blockLength = 0;
    bool transferEncoding = false;
    bool contentRange = false;
    bool currentHttps = false;
    bool redirectHttps = false;

    void fail(StreamError value)
    {
        if (!error)
            error = value;
        changed.notify_all();
    }

    static size_t bodyCallback(char* bytes, size_t size, size_t count, void* context) noexcept
    {
        auto& state = *static_cast<State*>(context);
        try
        {
            std::lock_guard<std::mutex> guard(state.mutex);
            if (size && count > std::numeric_limits<size_t>::max() / size)
            {
                state.fail({ErrorCode::Overflow});
                return CURL_WRITEFUNC_ERROR;
            }
            const size_t length = size * count;
            if (state.closed || state.cancelRequested || state.error)
                return CURL_WRITEFUNC_ERROR;
            // Followed redirects and informational responses cannot contribute
            // bytes or metadata to the resource exposed by this stream.
            if (!state.acceptBody)
                return length;
            if (length > state.queue.size())
            {
                state.fail({ErrorCode::LimitExceeded});
                return CURL_WRITEFUNC_ERROR;
            }
            if (length > state.queue.size() - state.queued)
            {
                state.paused = true;
                state.pauseBytes = length;
                state.changed.notify_all();
                return CURL_WRITEFUNC_PAUSE;
            }
            if (length > static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) - state.received)
            {
                state.fail({ErrorCode::Overflow});
                return CURL_WRITEFUNC_ERROR;
            }
            if (length)
            {
                const size_t tail = (state.head + state.queued) % state.queue.size();
                const size_t first = std::min(length, state.queue.size() - tail);
                std::memcpy(state.queue.data() + tail, bytes, first);
                std::memcpy(state.queue.data(), bytes + first, length - first);
                state.queued += length;
                state.received += length;
                state.peak = std::max(state.peak, state.queued);
                state.changed.notify_all();
            }
            return length;
        }
        catch (...) { return CURL_WRITEFUNC_ERROR; }
    }

    static size_t headerCallback(char* bytes, size_t size, size_t count, void* context) noexcept
    {
        auto& state = *static_cast<State*>(context);
        try
        {
            std::lock_guard<std::mutex> guard(state.mutex);
            if (size && count > std::numeric_limits<size_t>::max() / size)
            {
                state.fail({ErrorCode::Overflow});
                return CURL_WRITEFUNC_ERROR;
            }
            const size_t length = size * count;
            if (state.closed || state.cancelRequested || state.error)
                return CURL_WRITEFUNC_ERROR;
            if (length > state.options.maxHeaderBytes - state.headerBytes)
            {
                state.fail({ErrorCode::LimitExceeded});
                return CURL_WRITEFUNC_ERROR;
            }
            state.headerBytes += length;
            std::string_view line(bytes, length);
            if (line.substr(0, 5) == "HTTP/")
            {
                if (state.received)
                {
                    state.fail({ErrorCode::InvalidBackend});
                    return CURL_WRITEFUNC_ERROR;
                }
                const auto space = line.find(' ');
                if (space == std::string_view::npos || line.size() < space + 4 ||
                    line[space + 1] < '1' || line[space + 1] > '9' ||
                    line[space + 2] < '0' || line[space + 2] > '9' ||
                    line[space + 3] < '0' || line[space + 3] > '9' ||
                    (line.size() > space + 4 && line[space + 4] != ' ' &&
                     line[space + 4] != '\r' && line[space + 4] != '\n'))
                {
                    state.fail({ErrorCode::InvalidBackend});
                    return CURL_WRITEFUNC_ERROR;
                }
                state.blockStatus = (line[space + 1] - '0') * 100 +
                                    (line[space + 2] - '0') * 10 + line[space + 3] - '0';
                state.inHeaders = true;
                state.acceptBody = false;
                state.haveLength = false;
                state.transferEncoding = false;
                state.contentRange = false;
                state.redirectHttps = state.currentHttps;
                state.knownLength.reset();
                return length;
            }
            // Trailers are still bounded, but cannot replace response metadata.
            if (!state.inHeaders)
                return length;
            line = trim(line);
            if (line.empty())
            {
                state.inHeaders = false;
                const long status = state.blockStatus;
                if (status >= 100 && status < 200)
                    return length;
                if (status >= 300 && status < 400)
                {
                    state.currentHttps = state.redirectHttps;
                    return length;
                }
                state.httpStatus = status;
                if (status < 200 || status >= 300)
                {
                    state.fail({ErrorCode::IoError, static_cast<int>(status), ErrorDomain::Http});
                    return CURL_WRITEFUNC_ERROR;
                }
                if (status == 206 || state.contentRange)
                {
                    state.fail({ErrorCode::NotSupported, static_cast<int>(status), ErrorDomain::Http});
                    return CURL_WRITEFUNC_ERROR;
                }
                if (state.haveLength && !state.transferEncoding)
                    state.knownLength = state.blockLength;
                state.acceptBody = true;
                state.changed.notify_all();
                return length;
            }
            const auto colon = line.find(':');
            if (colon == std::string_view::npos)
            {
                state.fail({ErrorCode::InvalidBackend});
                return CURL_WRITEFUNC_ERROR;
            }
            const auto name = line.substr(0, colon);
            const auto value = trim(line.substr(colon + 1));
            if (equalsAscii(name, "content-length"))
            {
                int64_t parsed = 0;
                if (!parseLength(value, parsed) ||
                    (state.haveLength && parsed != state.blockLength))
                {
                    state.fail({ErrorCode::InvalidBackend, static_cast<int>(state.blockStatus), ErrorDomain::Http});
                    return CURL_WRITEFUNC_ERROR;
                }
                state.haveLength = true;
                state.blockLength = parsed;
            }
            else if (equalsAscii(name, "transfer-encoding"))
                state.transferEncoding = true;
            else if (equalsAscii(name, "content-range"))
                state.contentRange = true;
            else if (equalsAscii(name, "location") &&
                     state.blockStatus >= 300 && state.blockStatus < 400)
            {
                const auto schemeEnd = value.find(':');
                if (schemeEnd != std::string_view::npos)
                {
                    const auto scheme = value.substr(0, schemeEnd);
                    if (equalsAscii(scheme, "http") && state.currentHttps)
                    {
                        state.fail({ErrorCode::NotSupported, static_cast<int>(state.blockStatus), ErrorDomain::Http});
                        return CURL_WRITEFUNC_ERROR;
                    }
                    if (equalsAscii(scheme, "https"))
                        state.redirectHttps = true;
                }
            }
            return length;
        }
        catch (...) { return CURL_WRITEFUNC_ERROR; }
    }
};

HttpStream::HttpStream(RefConstructionToken token)
    : Stream(token), _state(std::make_unique<State>())
{}

HttpStream::~HttpStream() { close(); }

Result<ThreadSafeRefPtr<HttpStream>> HttpStream::open(std::string_view url, const HttpStreamOptions& options)
{
    using Output = Result<ThreadSafeRefPtr<HttpStream>>;
    if (url.empty() || url.find('\0') != std::string_view::npos ||
        options.caFile.find('\0') != std::string::npos ||
        options.receiveCapacity < CURL_MAX_WRITE_SIZE ||
        options.receiveCapacity > static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) ||
        options.transferBufferSize < 1024 || options.transferBufferSize > CURL_MAX_READ_SIZE ||
        !options.maxHeaderBytes || options.connectTimeoutMs < 0 || options.totalTimeoutMs < 0 ||
        options.connectTimeoutMs > std::numeric_limits<long>::max() ||
        options.totalTimeoutMs > std::numeric_limits<long>::max() || options.maxRedirects < 0)
        return Output::failure({ErrorCode::InvalidArgument});
    try
    {
        const auto initialized = initializeCurl();
        if (initialized != CURLE_OK)
            return Output::failure(curlError(initialized));
        std::string target(url);
        bool https = false;
        // An explicit scheme avoids curl's hostname-based protocol guessing.
        const auto colon = target.find(':');
        if (colon == std::string::npos ||
            (!equalsAscii(std::string_view(target).substr(0, colon), "http") &&
             !equalsAscii(std::string_view(target).substr(0, colon), "https")) ||
            !validUrl(target, https))
            return Output::failure({ErrorCode::InvalidArgument});
        auto stream = makeThreadSafeRef<HttpStream>();
        auto& state = *stream->_state;
        state.queue.resize(options.receiveCapacity);
        state.options = options;
        state.url = std::move(target);
        state.https = https;
        state.currentHttps = https;
        state.started = std::chrono::steady_clock::now();
        state.closed = false;
        // The worker owns no Ref. Destruction can safely request stop and join
        // from any client thread, without an ownership cycle or self-join.
        stream->_worker = std::thread(&HttpStream::run, &state);
        return Output::success(std::move(stream));
    }
    catch (const std::bad_alloc&) { return Output::failure({ErrorCode::OutOfMemory}); }
    catch (const std::length_error&) { return Output::failure({ErrorCode::Overflow}); }
    catch (const std::system_error&) { return Output::failure({ErrorCode::IoError}); }
}

Capability HttpStream::capabilities() const noexcept
{
    return isOpen() ? Capability::Read : Capability::None;
}

bool HttpStream::isOpen() const noexcept
{
    std::lock_guard<std::mutex> guard(_state->mutex);
    return !_state->closed;
}

IoResult HttpStream::read(void* destination, size_t length)
{
    auto& state = *_state;
    std::lock_guard<std::mutex> guard(state.mutex);
    if (state.closed)
        return IoResult::failure({ErrorCode::Closed});
    if (!length)
        return IoResult::success(0);
    if (!destination)
        return IoResult::failure({ErrorCode::InvalidArgument});
    const size_t transferred = std::min(length, state.queued);
    if (transferred)
    {
        const size_t first = std::min(transferred, state.queue.size() - state.head);
        std::memcpy(destination, state.queue.data() + state.head, first);
        std::memcpy(static_cast<uint8_t*>(destination) + first, state.queue.data(), transferred - first);
        state.head = (state.head + transferred) % state.queue.size();
        state.queued -= transferred;
        state.position += static_cast<int64_t>(transferred);
        state.changed.notify_all();
    }
    // Satisfying the whole request is always Ok, even at the final byte.
    if (transferred == length)
        return IoResult::success(transferred);
    if (state.error)
        return stoppedResult(state.error, transferred);
    if (state.complete)
        return {transferred, IoStatus::EndOfStream, {}};
    return {transferred, IoStatus::WouldBlock, {}};
}

Result<int64_t> HttpStream::tell() const
{
    std::lock_guard<std::mutex> guard(_state->mutex);
    return _state->closed ? Result<int64_t>::failure({ErrorCode::Closed}) :
                           Result<int64_t>::success(_state->position);
}

Result<std::optional<int64_t>> HttpStream::size() const
{
    std::lock_guard<std::mutex> guard(_state->mutex);
    return _state->closed ? Result<std::optional<int64_t>>::failure({ErrorCode::Closed}) :
                           Result<std::optional<int64_t>>::success(_state->knownLength);
}

Status HttpStream::seek(SeekOrigin, int64_t)
{
    return Status::failure({isOpen() ? ErrorCode::NotSupported : ErrorCode::Closed});
}

Status HttpStream::waitReadable(std::chrono::milliseconds timeout)
{
    auto& state = *_state;
    std::unique_lock<std::mutex> guard(state.mutex);
    if (state.closed)
        return Status::failure({ErrorCode::Closed});
    if (timeout.count() < 0)
        return Status::failure({ErrorCode::InvalidArgument});
    const auto ready = [&] { return state.closed || state.queued || state.error || state.complete; };
    if (!ready())
    {
        if (!timeout.count())
            return Status::failure({ErrorCode::WouldBlock});
        // Avoid chrono duration conversion/addition overflow for a caller's
        // milliseconds::max(). Bounded waits remain interruptible by close/cancel.
        const auto started = std::chrono::steady_clock::now();
        while (!ready())
        {
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - started);
            if (elapsed >= timeout)
                return Status::failure({ErrorCode::Timeout});
            const auto slice = std::min(timeout - elapsed, std::chrono::milliseconds(60000));
            state.changed.wait_for(guard, slice, ready);
        }
    }
    if (state.closed)
        return Status::failure({ErrorCode::Closed});
    if (state.queued)
        return Status::success();
    return state.error ? Status::failure(state.error) : Status::success();
}

void HttpStream::cancel() noexcept
{
    std::lock_guard<std::mutex> guard(_state->mutex);
    if (!_state->closed && !_state->complete)
    {
        _state->cancelRequested = true;
        _state->fail({ErrorCode::Cancelled});
    }
}

Status HttpStream::close()
{
    std::lock_guard<std::mutex> closing(_closeMutex);
    {
        std::lock_guard<std::mutex> guard(_state->mutex);
        _state->closed = true;
        _state->cancelRequested = true;
        _state->changed.notify_all();
    }
    if (_worker.joinable())
        _worker.join();
    {
        std::lock_guard<std::mutex> guard(_state->mutex);
        std::vector<uint8_t>().swap(_state->queue);
        _state->head = 0;
        _state->queued = 0;
        _state->paused = false;
        _state->complete = true;
    }
    return Status::success();
}

HttpStreamSnapshot HttpStream::snapshot() const
{
    std::lock_guard<std::mutex> guard(_state->mutex);
    return {_state->httpStatus, _state->knownLength, _state->received, _state->queued,
            _state->peak, _state->options.receiveCapacity, _state->paused,
            _state->complete, _state->error};
}

void HttpStream::run(State* state) noexcept
{
    CURL* easy = nullptr;
    CURLM* multi = nullptr;
    bool added = false;
    StreamError result{};
    long finalStatus = 0;
    try
    {
        easy = curl_easy_init();
        multi = curl_multi_init();
        if (!easy || !multi)
            result = {ErrorCode::OutOfMemory};
        if (!result)
        {
            // Check every option: a build lacking a required curl feature must
            // fail explicitly rather than weaken the request's guarantees.
            const auto set = [&](CURLoption option, auto value)
            {
                if (!result)
                {
                    const auto code = curl_easy_setopt(easy, option, value);
                    if (code != CURLE_OK)
                        result = curlError(code);
                }
            };
            set(CURLOPT_URL, state->url.c_str());
            set(CURLOPT_HTTPGET, 1L);
            set(CURLOPT_NOSIGNAL, 1L);
            set(CURLOPT_PROTOCOLS_STR, "http,https");
            set(CURLOPT_REDIR_PROTOCOLS_STR, state->https ? "https" : "http,https");
            set(CURLOPT_FOLLOWLOCATION, 1L);
            set(CURLOPT_MAXREDIRS, state->options.maxRedirects);
            set(CURLOPT_SSL_VERIFYPEER, 1L);
            set(CURLOPT_SSL_VERIFYHOST, 2L);
            if (!state->options.caFile.empty())
            {
                set(CURLOPT_SSL_OPTIONS, 0L);
                set(CURLOPT_CAINFO, state->options.caFile.c_str());
                set(CURLOPT_CAPATH, static_cast<const char*>(nullptr));
            }
#if defined(_WIN32)
            else
                set(CURLOPT_SSL_OPTIONS, static_cast<long>(CURLSSLOPT_NATIVE_CA));
#endif
            set(CURLOPT_CONNECTTIMEOUT_MS, static_cast<long>(state->options.connectTimeoutMs));
            set(CURLOPT_TIMEOUT_MS, static_cast<long>(state->options.totalTimeoutMs));
            set(CURLOPT_BUFFERSIZE, static_cast<long>(state->options.transferBufferSize));
            set(CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
            set(CURLOPT_HTTP_CONTENT_DECODING, 0L);
            set(CURLOPT_SUPPRESS_CONNECT_HEADERS, 1L);
            set(CURLOPT_WRITEFUNCTION, &State::bodyCallback);
            set(CURLOPT_WRITEDATA, state);
            set(CURLOPT_HEADERFUNCTION, &State::headerCallback);
            set(CURLOPT_HEADERDATA, state);
        }
        if (!result)
        {
            const auto code = curl_multi_add_handle(multi, easy);
            if (code != CURLM_OK)
                result = {ErrorCode::IoError, static_cast<int>(code), ErrorDomain::CurlMulti};
            else
                added = true;
        }
        bool finished = false;
        while (!result && !finished)
        {
            bool resume = false;
            {
                std::lock_guard<std::mutex> guard(state->mutex);
                if (state->closed || state->cancelRequested || state->error)
                    break;
                if (state->options.totalTimeoutMs &&
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - state->started).count() >= state->options.totalTimeoutMs)
                {
                    result = curlError(CURLE_OPERATION_TIMEDOUT);
                    break;
                }
                if (state->paused && state->queue.size() - state->queued >= state->pauseBytes)
                {
                    state->paused = false;
                    state->pauseBytes = 0;
                    resume = true;
                }
            }
            if (resume)
            {
                // Unpause can synchronously re-enter the body callback. No state
                // mutex is held, and only this worker ever touches the handle.
                const auto code = curl_easy_pause(easy, CURLPAUSE_CONT);
                if (code != CURLE_OK)
                {
                    result = curlError(code);
                    break;
                }
            }
            int running = 0;
            auto code = curl_multi_perform(multi, &running);
            if (code != CURLM_OK)
            {
                result = {ErrorCode::IoError, static_cast<int>(code), ErrorDomain::CurlMulti};
                break;
            }
            int remaining = 0;
            while (const auto message = curl_multi_info_read(multi, &remaining))
            {
                if (message->msg == CURLMSG_DONE && message->easy_handle == easy)
                {
                    finished = true;
                    if (message->data.result != CURLE_OK)
                        result = curlError(message->data.result);
                }
            }
            if (finished)
                break;
            if (!running)
            {
                result = {ErrorCode::InvalidBackend};
                break;
            }
            {
                std::unique_lock<std::mutex> guard(state->mutex);
                if (state->closed || state->cancelRequested || state->error)
                    break;
                if (state->paused)
                {
                    state->changed.wait_for(guard, std::chrono::milliseconds(PollIntervalMs), [&]
                    {
                        return state->closed || state->cancelRequested || state->error ||
                            state->queue.size() - state->queued >= state->pauseBytes;
                    });
                    continue;
                }
            }
            int descriptors = 0;
            code = curl_multi_poll(multi, nullptr, 0, PollIntervalMs, &descriptors);
            if (code != CURLM_OK)
                result = {ErrorCode::IoError, static_cast<int>(code), ErrorDomain::CurlMulti};
        }
        if (easy)
        {
            const auto code = curl_easy_getinfo(easy, CURLINFO_RESPONSE_CODE, &finalStatus);
            if (!result && code != CURLE_OK)
                result = curlError(code);
        }
    }
    catch (const std::bad_alloc&) { result = {ErrorCode::OutOfMemory}; }
    catch (...) { result = {ErrorCode::IoError}; }
    {
        // Resolver cleanup may wait for an OS call even after curl has timed
        // out. Publish the already known failure before beginning that cleanup.
        std::lock_guard<std::mutex> guard(state->mutex);
        if (!state->closed && result)
            state->fail(result);
    }
    if (added)
    {
        const auto code = curl_multi_remove_handle(multi, easy);
        if (!result && code != CURLM_OK)
            result = {ErrorCode::IoError, static_cast<int>(code), ErrorDomain::CurlMulti};
    }
    if (easy)
        curl_easy_cleanup(easy);
    if (multi)
    {
        const auto code = curl_multi_cleanup(multi);
        if (!result && code != CURLM_OK)
            result = {ErrorCode::IoError, static_cast<int>(code), ErrorDomain::CurlMulti};
    }
    {
        std::lock_guard<std::mutex> guard(state->mutex);
        if (!state->httpStatus)
            state->httpStatus = finalStatus;
        if (!state->closed && !state->error)
        {
            if (result)
                state->fail(result);
            else if (finalStatus < 200 || finalStatus >= 300 || !state->acceptBody)
                state->fail({ErrorCode::IoError, static_cast<int>(finalStatus), ErrorDomain::Http});
            else if (state->knownLength && static_cast<uint64_t>(*state->knownLength) != state->received)
                state->fail({ErrorCode::InvalidBackend, static_cast<int>(finalStatus), ErrorDomain::Http});
            else if (!state->knownLength)
                state->knownLength = static_cast<int64_t>(state->received);
        }
        state->paused = false;
        state->complete = true;
        state->changed.notify_all();
    }
}
}
