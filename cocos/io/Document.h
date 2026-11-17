#pragma once

#include "io/Stream.h"
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace cc {
enum class DialogStatus { Ok, Cancelled, Error };
enum class CancelReason { None, User, Caller };
enum class CancelResult { Accepted, TooLate, AlreadyFinished };
enum class DialogErrorCode {
    None, InvalidArgument, WrongThread, NotInitialized, Busy, Unavailable, UnsupportedFeature,
    ParentClosed, PermissionDenied, NotFound, InvalidResult, EncodingError, IoError,
    LimitExceeded, Timeout, OutOfMemory, BackendError
};
enum class DocumentKind { File, Directory };
enum class LocationKind { LocalFile, AndroidDocument, AppleDocument };
// Operations this handle can attempt. Providers may still refuse or revoke access.
struct DocumentAccessHints {
    bool read = false, listChildren = false, createChild = false;
};
enum class ExternalEffect { None, Committed, PartialPossible, Unknown };
struct FileDialogError {
    DialogErrorCode code = DialogErrorCode::None;
    std::string message, nativeDomain;
    int64_t nativeCode = 0;
    explicit operator bool() const { return code != DialogErrorCode::None; }
};
namespace dialog { class DocumentProvider; struct Documents; }
class CC_DLL DocumentHandle {
public:
    DocumentHandle() = default;
    explicit operator bool() const { return bool(_provider); }
    DocumentKind kind() const;
    LocationKind locationKind() const;
    std::string displayName() const;
    std::string mimeType() const;
    std::optional<uint64_t> size() const;
    DocumentAccessHints accessHints() const;
    std::optional<std::string> tryGetLocalPath() const;
    std::optional<std::string> tryGetLocalPath(FileDialogError& error) const;
    // Compatibility metadata. The URI alone does not retain the Android grant.
    std::string legacyAndroidUri() const;
private:
    friend struct dialog::Documents;
    std::shared_ptr<dialog::DocumentProvider> _provider;
};
class CC_DLL SaveTarget {
public:
    explicit operator bool() const { return bool(_target); }
    std::optional<std::string> tryGetLocalPath() const;
    std::optional<std::string> tryGetLocalPath(FileDialogError& error) const;
private:
    friend struct dialog::Documents;
    DocumentHandle _target;
};
class CC_DLL DialogRequest {
public:
    explicit DialogRequest(uint64_t id = 0) : _id(id) {}
    CancelResult cancel() const;
private:
    uint64_t _id;
};
struct DialogSubmission {
    std::optional<DialogRequest> request;
    FileDialogError error;
};
struct TransferLimits {
    uint64_t maxBytes = 512ull * 1024 * 1024;
    uint32_t timeoutSeconds = 300;
};
struct DocumentResult {
    DialogStatus status = DialogStatus::Error;
    CancelReason cancelReason = CancelReason::None;
    FileDialogError error;
    std::vector<DocumentHandle> documents;
    std::string nextPage;
    ExternalEffect effect = ExternalEffect::None;
};
using DocumentCallback = std::function<void(DocumentResult)>;
using DocumentReader = std::function<FileDialogError(io::Stream&)>;
class CC_DLL DocumentAccess {
public:
    static DocumentHandle fromLocalPath(std::string absolutePath, DocumentKind kind = DocumentKind::File);
    static DialogSubmission withReadStream(DocumentHandle, DocumentReader, DocumentCallback);
    // Empty destination selects a new file in the application's persistent imports directory.
    static DialogSubmission importFile(DocumentHandle, std::string destination, TransferLimits, DocumentCallback);
    static DialogSubmission listChildren(DocumentHandle, std::string pageToken, uint32_t limit, DocumentCallback);
    static DialogSubmission exportChild(DocumentHandle directory, std::string name, DocumentHandle source,
                                       TransferLimits, DocumentCallback);
    static DialogSubmission writeTarget(SaveTarget, DocumentHandle source, TransferLimits, DocumentCallback);
};
}
