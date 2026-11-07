#pragma once
#include "io/Stream.h"
#include <chrono>
#include <memory>
#include <string>
#include <string_view>
#include <thread>

namespace cocos2d::io
{
struct HttpStreamOptions
{
    // The receive queue and curl's requested transfer buffer are separate.
    // receiveCapacity must hold at least curl's maximum body callback block
    // (16 KiB in the bundled curl); transferBufferSize permits 1 KiB..10 MiB.
    size_t receiveCapacity = 64 * 1024;
    size_t transferBufferSize = 16 * 1024;
    size_t maxHeaderBytes = 64 * 1024;
    int64_t connectTimeoutMs = 10000;
    // Zero disables the whole-transfer deadline, which otherwise includes pause.
    int64_t totalTimeoutMs = 0;
    long maxRedirects = 5;
    // Empty uses curl's configured trust store. Verification is always enabled.
    std::string caFile;
};

struct HttpStreamSnapshot
{
    long httpStatus = 0;
    std::optional<int64_t> knownLength;
    // Unique body bytes accepted into this stream's queue, excluding redirects.
    uint64_t receivedBytes = 0;
    size_t queuedBytes = 0;
    size_t peakQueuedBytes = 0;
    size_t receiveCapacity = 0;
    bool paused = false;
    bool transferComplete = false;
    StreamError error{};
};

// Read-only, nonseekable HTTP(S) GET input. open starts a dedicated worker and
// returns before the response arrives; transport failures are read/snapshot errors.
// I/O sequences still use StreamLock. cancel, close, waitReadable and snapshot
// may run concurrently; the worker never acquires the external Stream lock.
class CC_DLL HttpStream final : public Stream
{
public:
    explicit HttpStream(RefConstructionToken token);
    ~HttpStream() override;

    static Result<ThreadSafeRefPtr<HttpStream>> open(
        std::string_view url, const HttpStreamOptions& options = {});

    Capability capabilities() const noexcept override;
    bool isOpen() const noexcept override;
    IoResult read(void* destination, size_t length) override;
    Result<int64_t> tell() const override;
    Result<std::optional<int64_t>> size() const override;
    Status seek(SeekOrigin origin, int64_t offset) override;
    Status close() override;

    // Zero polls; a positive duration waits. Readiness includes successful EOF.
    // Terminal failure is returned after queued data has been consumed.
    Status waitReadable(std::chrono::milliseconds timeout);
    // Stops production, retains queued data, and wakes all waiting readers.
    void cancel() noexcept;
    HttpStreamSnapshot snapshot() const;

private:
    struct State;
    static void run(State* state) noexcept;
    std::unique_ptr<State> _state;
    std::thread _worker;
    std::mutex _closeMutex;
};
}
