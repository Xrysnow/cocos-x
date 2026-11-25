#pragma once

#include "io/core/Document.h"

namespace cc {
class GLView;
class CC_DLL DialogParent {
public:
    static DialogParent current();
    // Engine thread. A host owning another GLView invalidates its token before closing the window.
    static DialogParent registerView(GLView*);
    void invalidate() const;
    explicit operator bool() const { return _generation != 0; }
    uint64_t generation() const { return _generation; }
private:
    uint64_t _generation = 0;
};
struct FileDialogFilter {
    std::string label;
    std::vector<std::string> extensions, mimeTypes, appleTypeIdentifiers;
};
struct OpenFileOptions {
    DialogParent parent;
    std::string title;
    std::vector<FileDialogFilter> filters;
    std::optional<DocumentHandle> initialDirectory;
    bool allowMultiple = false;
    bool allowAllFiles = true;
    uint32_t maxSelectionCount = 256;
};
struct FolderOptions {
    DialogParent parent;
    std::string title;
    std::optional<DocumentHandle> initialDirectory;
};
struct ExportFileOptions : FolderOptions {
    std::string suggestedName;
    FileDialogFilter contentType;
    TransferLimits limits;
};
struct SaveTargetOptions : OpenFileOptions {
    std::string suggestedName;
};
struct SelectionResult {
    DialogStatus status = DialogStatus::Error;
    CancelReason cancelReason = CancelReason::None;
    std::vector<DocumentHandle> documents;
    std::optional<uint32_t> selectedFilter;
    FileDialogError error;
};
struct ExportResult {
    DialogStatus status = DialogStatus::Error;
    CancelReason cancelReason = CancelReason::None;
    ExternalEffect effect = ExternalEffect::None;
    std::optional<DocumentHandle> destination;
    std::string displayName;
    FileDialogError error;
};
struct SaveTargetResult {
    DialogStatus status = DialogStatus::Error;
    CancelReason cancelReason = CancelReason::None;
    SaveTarget target;
    std::optional<uint32_t> selectedFilter;
    FileDialogError error;
};
struct DialogCapabilities {
    std::string backend, unavailableReason;
    bool available = false, openFiles = false, multipleFiles = false, pickFolder = false,
         exportFile = false, chooseSaveTarget = false, initialDirectoryHint = false,
         selectedFilter = false, physicalDismiss = false;
};
class CC_DLL FileDialog {
public:
    static DialogCapabilities capabilities();
    static DialogSubmission openFiles(OpenFileOptions, std::function<void(SelectionResult)>);
    static DialogSubmission pickFolder(FolderOptions, std::function<void(SelectionResult)>);
    static DialogSubmission chooseSaveTarget(SaveTargetOptions, std::function<void(SaveTargetResult)>);
    static DialogSubmission exportFile(ExportFileOptions, DocumentHandle, std::function<void(ExportResult)>);
};
}
