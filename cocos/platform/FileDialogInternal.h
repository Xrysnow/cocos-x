#pragma once

#include "platform/FileDialog.h"
#include <filesystem>

namespace cc::dialog {
// Methods run on the single bounded I/O worker. Coordinate scope and stream lifetime
// across the entire reader/writer call. Identifiers remain private to their provider.
using StreamOperation = std::function<FileDialogError(io::Stream&)>;
class DocumentProvider {
public:
    virtual ~DocumentProvider() = default;
    DocumentKind kind = DocumentKind::File;
    LocationKind location = LocationKind::LocalFile;
    std::string name, mime;
    std::optional<uint64_t> length;
    virtual DocumentAccessHints hints() const {
        return {kind == DocumentKind::File, kind == DocumentKind::Directory, kind == DocumentKind::Directory};
    }
    virtual std::optional<std::string> localPath(FileDialogError&) const { return {}; }
    virtual std::string legacyAndroidUri() const { return {}; }
    virtual FileDialogError read(const StreamOperation&) = 0;
    // Enumerate immediate children. Fail if there are more than maximum, never truncate.
    virtual FileDialogError children(size_t maximum, std::vector<DocumentHandle>& out);
    // Empty childName writes the selected target, otherwise create a new child exclusively.
    virtual FileDialogError write(const std::string& childName, const StreamOperation&,
                                  DocumentHandle& actual, ExternalEffect& effect);
};
struct Documents {
    static DocumentHandle wrap(std::shared_ptr<DocumentProvider> provider) {
        DocumentHandle h; h._provider = std::move(provider); return h;
    }
    static std::shared_ptr<DocumentProvider> get(const DocumentHandle& h) { return h._provider; }
    static SaveTarget target(DocumentHandle h) { SaveTarget t; t._target = std::move(h); return t; }
    static DocumentHandle get(const SaveTarget& t) { return t._target; }
};
// Called on receipt of a desktop save selection. Records the identity of any existing target.
DocumentHandle localSaveLocation(const std::filesystem::path&);
DocumentHandle localDocument(const std::filesystem::path&, DocumentKind);
DocumentHandle localSelectedDirectory(const std::filesystem::path&);
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
DocumentHandle localPortalLocation(const std::filesystem::path&, DocumentKind, bool save);
#endif
enum class Operation { Open, Folder, SaveTarget, Export };
struct NativeRequest {
    uint64_t id = 0;
    Operation operation = Operation::Open;
    GLView* view = nullptr; // valid on engine thread during presentNative only; capture the native owner here
    OpenFileOptions options;
    std::string suggestedName, stagingPath;
    // iOS calls this immediately before handing staged content to UIKit.
    std::function<bool()> beginExternalWrite;
};
struct NativeResult : SelectionResult {
    // For SaveTarget and desktop/Android Export, return the selected writable location here.
    DocumentHandle target;
    // iOS can report completion of the system copy directly.
    ExternalEffect effect = ExternalEffect::None;
    std::string displayName;
};
using NativeCallback = std::function<void(NativeResult)>;
// Called on the engine thread. Callback may run on any thread, exactly once after native UI ends.
// Logical cancel keeps the physical slot until this callback, including Android late results.
DialogCapabilities nativeCapabilities();
void presentNative(NativeRequest, NativeCallback);
void cancelNative(uint64_t);
void shutdownNative();

void startSession();
void setView(GLView*);
void forgetView(GLView*);
void pump();
void stopSession();
bool validName(const std::string&);
std::string uniqueName();
struct AccessJob {
    std::function<bool()> cancelled;
    std::function<bool()> beginWrite;
};
using AccessWork = std::function<DocumentResult(const AccessJob&)>;
struct Snapshot {
    std::filesystem::path directory, path;
    DocumentHandle document;
    std::shared_ptr<void> lease;
    ~Snapshot();
};
FileDialogError writeSnapshotFile(const std::filesystem::path&, const StreamOperation&);
FileDialogError prepareSnapshot(DocumentHandle, const std::string&, TransferLimits, const AccessJob&,
                                std::shared_ptr<Snapshot>&);
DialogSubmission submitAccess(AccessWork, DocumentCallback, uint32_t timeoutSeconds = 0);
FileDialogError copyDocument(DocumentHandle, io::Stream&, TransferLimits, const std::function<bool()>&);
}
