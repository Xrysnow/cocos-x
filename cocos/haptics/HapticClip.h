#pragma once

#include "platform/PlatformDefine.h"
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cc::haptics
{

/** Input representation of a haptic preset. */
enum class AssetFormat
{
    /** Infer from filename and root structure (default for import). */
    Auto,
    /** Meta Studio 1.0.x amplitude and frequency envelopes. */
    MetaHaptic,
    /** Apple Haptic and Audio Pattern version 1. */
    AppleAhap,
    /** RichTap HE version 1, with one event pattern. */
    RichTapHeV1,
    /** RichTap HE version 2, with absolute-time pattern groups. */
    RichTapHeV2
};

/** Treatment of lossy preset features. */
enum class ImportPolicy
{
    /** Clamp or skip recognized losses with field diagnostics (default). */
    Compatible,
    /** Reject unsupported playback fields, dropped content and out-of-range values. */
    Strict
};

/** Machine-readable cause of an unsuccessful request. */
enum class Error
{
    InvalidAsset,     ///< Malformed, inconsistent or oversized input.
    Unsupported,      ///< Unknown format version or no supported haptic content.
    InvalidArgument,  ///< Invalid request options, path or playback bounds.
    IoError,          ///< Resource could not be opened or read.
    QueueFull,        ///< No pending request slot is available.
    Busy,             ///< Another writer or stop transaction owns the target.
    NotFocused,       ///< Application output is suspended.
    StaleTarget,      ///< Target connection has retired.
    Unavailable,      ///< Safe output cannot currently be proved.
    NotFound,         ///< Handle was never issued by this scope.
    RecordGone,       ///< Terminal record was consumed or evicted.
    TimedOut,         ///< Expected native evidence did not arrive in time.
    BackendFailure,   ///< Native output failed.
    Cancelled,        ///< The pending transaction was withdrawn.
    PermissionDenied, ///< The platform denied permission to use the actuator.
    Disabled          ///< Output is disabled or its global strength is zero.
};

/** Field-level import observation. */
struct Diagnostic
{
    std::string path;     ///< JSON path of the affected field, rooted at $.
    std::string code;     ///< Stable diagnostic name.
    std::string message;  ///< Human-readable detail including the offending version when applicable.
};

/** Failed operation and diagnostics collected up to the failing field. */
struct ErrorInfo
{
    Error code;                           ///< Primary error category.
    std::vector<Diagnostic> diagnostics;  ///< Ordered observations, with the failure last.
};

/** Synchronous result. Exactly one of value and error is populated. */
template <class T>
struct Result
{
    std::optional<T> value;          ///< Successful return value.
    std::optional<ErrorInfo> error;  ///< Failure with field-level diagnostics.
};

/** Optional preset import settings. */
struct ImportOptions
{
    AssetFormat format  = AssetFormat::Auto;         ///< Default infers the input format.
    ImportPolicy policy = ImportPolicy::Compatible;  ///< Default permits documented portable approximations.
};

namespace detail
{
struct ClipData;
struct ClipAccess;
}  // namespace detail
struct ImportResult;

/** Immutable, copyable handle. Copies share the timeline independently of the input bytes. */
class CC_DLL HapticClip
{
public:
    /** Share the source's compiled timeline.
     * @param other Valid clip handle whose storage is shared.
     */
    HapticClip(const HapticClip& other) = default;
    /** Share another timeline, releasing the previous reference.
     * @param other Valid clip handle, including this handle.
     * @return This handle, now referring to the source timeline.
     */
    HapticClip& operator=(const HapticClip& other) = default;
    /** Release this reference. Other handles and active voices keep the timeline alive. */
    ~HapticClip() = default;
    /** Read a complete .haptic, .ahap or .he preset synchronously through the engine resource system.
     * @param path Nonempty resource path. A recognized extension must match the content.
     * @param options Optional format and import policy, compatible by default.
     * @return Imported clip and diagnostics, or a resource access, format or validation error.
     */
    static Result<ImportResult> load(std::string_view path, const ImportOptions& options = {});
    /** Compile Meta, AHAP or HE from length-delimited UTF-8 bytes. Embedded NUL bytes are invalid.
     * @param bytes Complete JSON document of at most 1 MiB, borrowed only during this call.
     * @param options Optional format and import policy, compatible by default.
     * @return Imported clip and diagnostics, or a field-specific validation error.
     */
    static Result<ImportResult> parse(std::string_view bytes, const ImportOptions& options = {});
    /** Query content length before the rendering tail.
     * @return Milliseconds, possibly fractional or zero for an instant at the origin.
     */
    double durationMs() const;
    /** Identify the parsed document.
     * @return Concrete input format.
     */
    AssetFormat format() const;
    /** Query import behavior.
     * @return Policy used to compile this clip.
     */
    ImportPolicy importPolicy() const;

private:
    friend struct detail::ClipAccess;
    explicit HapticClip(std::shared_ptr<const detail::ClipData> data) : _data(std::move(data)) {}
    std::shared_ptr<const detail::ClipData> _data;
};

/** Successful import and its recoverable observations. */
struct ImportResult
{
    HapticClip clip;                      ///< Owns the immutable compiled timeline.
    std::vector<Diagnostic> diagnostics;  ///< Ordered warnings and portable rendering approximations.
};
}  // namespace cc::haptics
