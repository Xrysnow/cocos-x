#pragma once
#include "haptics/HapticClip.h"
#include "input/gamepad/GamepadTypes.h"
#include <compare>
namespace cc::haptics
{
namespace detail
{
class HapticControl;
}
/** Preset voice pool. */
enum class Track
{
    Normal,  ///< Eight normal voices per target.
    Burst,   ///< Three priority burst voices per target.
};
/** Logical start during cold initialization. */
enum class StartPolicy
{
    Auto,           ///< Align immediate playback with the first writable instant.
    FixedTimeline,  ///< Keep the requested origin, including leading silence.
};
/** Current physical Body writer. */
enum class Owner
{
    Idle,          ///< No writer.
    Preset,        ///< Shared preset mixer.
    LegacyRumble,  ///< Legacy dual-motor state.
    LegacyPcm,     ///< File-backed audio haptics.
    Raw,           ///< Exclusive handset lease.
};
/** Physical output availability. */
enum class Availability
{
    Available,   ///< Accepts compatible starts.
    Stopping,    ///< Waiting for the previous writer to become silent.
    RouteFault,  ///< Stop evidence is missing.
    NotFocused,  ///< Application output is suspended.
};
/** Observable playback lifecycle. */
enum class PlaybackState
{
    Scheduled,  ///< Accepted and awaiting its logical start.
    Active,     ///< Participating in the mixer.
    Completed,  ///< Reached its natural end.
    Stopped,    ///< Cancelled by a stop or lifecycle change.
    Preempted,  ///< Replaced by a higher priority voice or a different owner.
    Dropped,    ///< Voice pool rejected the request.
    Coalesced,  ///< Merged into another voice.
    Failed,     ///< Output could not be completed.
};
/** Cause of playback retirement. */
enum class StopReason
{
    None,          ///< No interruption.
    Requested,     ///< Explicit stop or scope release.
    Priority,      ///< Voice pool priority decision.
    FocusLost,     ///< Window, animation or application lost focus.
    EndpointLost,  ///< Device or selected route changed.
    Replaced,      ///< Another writer took over.
    IdleExpired,   ///< A ready handset lease was idle for two seconds.
};
/** Stop transaction progress. */
enum class OperationState
{
    Pending,    ///< Awaiting evidence.
    Succeeded,  ///< Silence was confirmed.
    Failed,     ///< See the error.
    Cancelled,  ///< Transaction was withdrawn.
};
/** Conditions for acquiring the handset. */
enum class AcquirePolicy
{
    IfIdle,           ///< Require a free target.
    InterruptPreset,  ///< May interrupt a preset through a stop fence.
};
/** Handset lease state. */
enum class RawState
{
    Pending,  ///< Waiting for the previous writer.
    Ready,    ///< Owns the target.
    Closed,   ///< Released or invalidated.
    Failed,   ///< Acquisition failed.
};
/** Opaque connection identity, unique across service lifetimes. */
enum class TargetId : std::uint64_t
{
};
/** Opaque playback identity scoped to one issuing scope. */
class PlaybackId
{
public:
    /** Compare the issuing scope and sequence.
     * @param other Identity to compare.
     * @return Ordering by scope and sequence.
     */
    auto operator<=>(const PlaybackId& other) const = default;

private:
    friend class detail::HapticControl;
    std::uint64_t scope{}, serial{};
};
/** Opaque operation identity scoped to one issuing scope. */
class OperationId
{
public:
    /** Compare the issuing scope and sequence.
     * @param other Identity to compare.
     * @return Ordering by scope and sequence.
     */
    auto operator<=>(const OperationId& other) const = default;

private:
    friend class detail::HapticControl;
    std::uint64_t scope{}, serial{};
};
/** Monotonic instant issued by one service generation. */
class CC_DLL HapticTime
{
public:
    /** Compute a future instant.
     * @param deltaMs Finite nonnegative millisecond offset.
     * @return Instant from the same clock or InvalidArgument on overflow.
     */
    Result<HapticTime> afterMs(double deltaMs) const;

private:
    friend class detail::HapticControl;
    std::uint64_t generation{};
    std::int64_t us{};
};
/** Preset admission settings. */
struct PlayOptions
{
    Track track = Track::Normal;                  ///< Defaults to the normal voice pool.
    std::optional<unsigned> priority;             ///< 0..255; defaults to 64 for Normal and 128 for Burst.
    double gain         = 1;                      ///< Normalized total amplitude, 0..1.
    double pan          = 0;                      ///< Position -1..1; low/high motor layouts fold pan.
    double startAfterMs = 0;                      ///< Delay in milliseconds, up to 5000.
    std::optional<HapticTime> startAt;            ///< Absolute time, exclusive with a nonzero delay.
    StartPolicy startPolicy = StartPolicy::Auto;  ///< Immediate cold-start behavior.
    unsigned iterations     = 1;                  ///< Finite total iterations, 1..65535; Burst requires one.
    std::string mergeKey;                         ///< UTF-8 key up to 64 bytes. Empty disables merging.
};
/** Successful call or a synchronous validation error. */
struct Status
{
    std::optional<ErrorInfo> error;  ///< Missing on success.
};
/** Current route identity. */
struct TargetInfo
{
    TargetId target{};                      ///< Connection-scoped target.
    std::optional<input::DeviceId> device;  ///< Gamepad connection; absent for a handset.
};
/** Snapshot of the selected physical route at query time. */
struct Capabilities
{
    Owner owner               = Owner::Idle;              ///< Writer holding the Body route, including during shutdown.
    Availability availability = Availability::Available;  ///< Readiness for new work.
    bool canInterruptPreset   = false;                    ///< The adapter can confirm a safe stop.
    bool canReleaseRaw        = false;                    ///< The handset can safely relinquish raw ownership.
};
/** Playback record. Times are microseconds on the service clock. */
struct PlaybackSnapshot
{
    PlaybackState state = PlaybackState::Scheduled;  ///< Current scheduling or terminal state.
    StopReason reason   = StopReason::None;          ///< Cause for an interrupted record.
    std::optional<Error> error;                      ///< Asynchronous failure when present.
    bool submitted = false;                          ///< A nonzero motor write received a successful native receipt.
    std::int64_t requestedUs{};                      ///< Request admission time.
    std::optional<std::int64_t> logicalStartUs;      ///< Logical start including leading silence.
    std::optional<std::int64_t> firstSubmitUs;       ///< First acknowledged nonzero native write.
    std::optional<PlaybackId> mergedInto;            ///< Surviving playback for a coalesced request.
};
/** Result of an asynchronous stop. */
struct OperationSnapshot
{
    OperationState state = OperationState::Pending;  ///< Current transaction state.
    std::optional<Error> error;                      ///< Failure or cancellation detail.
    std::optional<std::int64_t> confirmedUs;         ///< Monotonic microseconds when silence was confirmed.
};
/** Handset ownership snapshot. */
struct RawSnapshot
{
    RawState state = RawState::Closed;  ///< Readiness of this lease.
    std::optional<Error> error;         ///< Reason for failed acquisition.
    StopReason reason = StopReason::None; ///< Cause of automatic lease closure.
};
/** Move-only raw handset lease. Destruction revokes only this handle's work. */
class CC_DLL RawSession
{
public:
    /** Transfer ownership.
     * @param other Source handle, left empty.
     */
    RawSession(RawSession&& other) noexcept;
    /** Release current ownership and transfer the source.
     * @param other Source handle, left empty.
     * @return This handle.
     */
    RawSession& operator=(RawSession&& other) noexcept;
    /** Release ownership. */
    ~RawSession();
    /** Inspect the lease without advancing it.
     * @return Current state and any failure.
     */
    RawSnapshot state() const;
    /** Cancel the current effect, or withdraw a pending acquisition.
     * @return Stop ticket for the owning scope, or a handle error.
     */
    Result<OperationId> cancel();
    /** Idempotently revoke this handle. Native stop confirmation may follow asynchronously.
     */
    void close() noexcept;

private:
    friend class detail::HapticControl;
    RawSession(std::weak_ptr<detail::HapticControl> control, std::uint64_t id) : _control(std::move(control)), _id(id)
    {
    }
    std::weak_ptr<detail::HapticControl> _control;
    std::uint64_t _id{};
};
/** Move-only playback scope. Destruction revokes only this handle's work. */
class CC_DLL HapticScope
{
public:
    /** Transfer ownership.
     * @param other Source handle, left empty.
     */
    HapticScope(HapticScope&& other) noexcept;
    /** Release current ownership and transfer the source.
     * @param other Source handle, left empty.
     * @return This handle.
     */
    HapticScope& operator=(HapticScope&& other) noexcept;
    /** Release ownership. */
    ~HapticScope();
    /** Submit a preset for asynchronous playback.
     * @param target Live connection identity.
     * @param clip Immutable clip retained through retirement.
     * @param options Optional timing, track and gain settings.
     * @return Playback record or an admission error.
     */
    Result<PlaybackId> play(TargetId target, const HapticClip& clip, const PlayOptions& options = {});
    /** Read a record, consuming a terminal result once.
     * @param playback Identity issued by this scope.
     * @return Current state or RecordGone after consumption.
     */
    Result<PlaybackSnapshot> readPlayback(PlaybackId playback);
    /** Idempotently cancel one issued playback.
     * @param playback Identity issued by this scope.
     * @return Admission status; the playback record reports retirement.
     */
    Status stop(PlaybackId playback);
    /** Stop the current owner and previously scheduled work.
     * @param target Live physical target.
     * @return Stop ticket completed after backend confirmation.
     */
    Result<OperationId> stopTarget(TargetId target);
    /** Read a stop ticket, consuming terminal results once.
     * @param operation Ticket issued by this scope.
     * @return Current operation state or RecordGone.
     */
    Result<OperationSnapshot> readOperation(OperationId operation);
    /** Acquire an exclusive handset lease.
     * @param target Current handset target.
     * @param policy IfIdle by default; InterruptPreset allows an asynchronous handover.
     * @return Pending or Ready lease, or an admission error.
     */
    Result<RawSession> acquireRaw(TargetId target, AcquirePolicy policy = AcquirePolicy::IfIdle);
    /** Idempotently revoke this handle. Native stop confirmation may follow asynchronously.
     */
    void close() noexcept;

private:
    friend class detail::HapticControl;
    HapticScope(std::weak_ptr<detail::HapticControl> control, std::uint64_t id) : _control(std::move(control)), _id(id)
    {
    }
    std::weak_ptr<detail::HapticControl> _control;
    std::uint64_t _id{};
};
}  // namespace cc::haptics
namespace cc::input::detail
{
class OutputRouter;
}
namespace cc::haptics
{
/** Director-owned service. Scope and lease handles can safely outlive it. */
class CC_DLL HapticService
{
public:
    /** List current preset-capable routes.
     * @return A copy of the connection identities.
     */
    std::vector<TargetInfo> enumerate() const;
    /** Resolve a connected gamepad.
     * @param deviceId Connection ID from the input frame.
     * @return Preset-capable Body target or a route error.
     */
    Result<TargetId> gamepad(input::DeviceId deviceId) const;
    /** Resolve the current handset.
     * @return Handset target or Unsupported.
     */
    Result<TargetId> handset() const;
    /** Read live route and ownership information.
     * @param target Connection identity issued by this service.
     * @return Snapshot or StaleTarget.
     */
    Result<Capabilities> capabilities(TargetId target) const;
    /** Sample the service clock.
     * @return Monotonic time suitable for startAt.
     */
    HapticTime now() const;
    /** Create a separately cancellable playback scope.
     * @return Move-only scope or QueueFull.
     */
    Result<HapticScope> createScope();
    HapticService(const HapticService&)            = delete;
    HapticService& operator=(const HapticService&) = delete;

private:
    friend class input::detail::OutputRouter;
    friend class detail::HapticControl;
    explicit HapticService(std::shared_ptr<detail::HapticControl> control) : _control(std::move(control)) {}
    std::shared_ptr<detail::HapticControl> _control;
};
}  // namespace cc::haptics
