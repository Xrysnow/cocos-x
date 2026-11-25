#include "platform/apple/FileDialog-apple.h"
#include "io/core/FileStream.h"

#include <cerrno>
#include <fcntl.h>
#include <mutex>
#include <sys/stat.h>
#include <unistd.h>
#if TARGET_OS_OSX
    #import <Security/SecTask.h>
#endif

namespace cc::dialog::apple
{
namespace
{
struct CoordinationState
{
    std::mutex mutex;
    NSMutableSet<NSFileCoordinator*>* active = [NSMutableSet new];
    uint64_t sequence = 0;
    uint64_t session = 0;
};

CoordinationState& coordinationState()
{
    // A provider may be finishing on the I/O worker when the host process exits.
    static auto* state = new CoordinationState;
    return *state;
}

uint64_t currentSession()
{
    auto& state = coordinationState();
    std::lock_guard lock(state.mutex);
    return state.session;
}

class Coordination
{
public:
    explicit Coordination(uint64_t session)
    {
        auto& state = coordinationState();
        std::lock_guard lock(state.mutex);
        if (session != 0 && state.session == session)
        {
            _coordinator = [[NSFileCoordinator alloc] initWithFilePresenter:nil];
            [state.active addObject:_coordinator];
        }
    }
    ~Coordination()
    {
        if (_coordinator)
        {
            auto& state = coordinationState();
            std::lock_guard lock(state.mutex);
            [state.active removeObject:_coordinator];
        }
    }
    NSFileCoordinator* get() const { return _coordinator; }
    Coordination(const Coordination&) = delete;
    Coordination& operator=(const Coordination&) = delete;
private:
    NSFileCoordinator* _coordinator = nil;
};

class Scope
{
public:
    explicit Scope(NSURL* url) : _url(url), _active([url startAccessingSecurityScopedResource]) {}
    ~Scope() { if (_active) [_url stopAccessingSecurityScopedResource]; }
    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;
private:
    NSURL* _url;
    bool _active;
};

FileDialogError posixError(const char* message, int code)
{
    auto reason = DialogErrorCode::IoError;
    if (code == EACCES || code == EPERM || code == EROFS)
        reason = DialogErrorCode::PermissionDenied;
    else if (code == ENOENT)
        reason = DialogErrorCode::NotFound;
    return {reason, message, "POSIX", code};
}

FileDialogError cocoaError(NSError* error)
{
    if (!error)
        return {DialogErrorCode::IoError, "Foundation did not return document information"};
    if ([error.domain isEqualToString:NSPOSIXErrorDomain])
        return posixError(error.localizedDescription.UTF8String, static_cast<int>(error.code));
    auto code = DialogErrorCode::IoError;
    if ([error.domain isEqualToString:NSCocoaErrorDomain])
    {
        if (error.code == NSFileReadNoPermissionError || error.code == NSFileWriteNoPermissionError)
            code = DialogErrorCode::PermissionDenied;
        else if (error.code == NSFileNoSuchFileError || error.code == NSFileReadNoSuchFileError)
            code = DialogErrorCode::NotFound;
    }
    return {code, string(error.localizedDescription), string(error.domain), error.code};
}

FileDialogError streamError(const char* message, const io::StreamError& error)
{
    if (error.nativeCode != 0)
        return posixError(message, error.nativeCode);
    return {DialogErrorCode::IoError, message};
}

// Own the descriptor used for the identity check by the coordinated accessor.
class Descriptor final : public cc::FileStream
{
public:
    explicit Descriptor(bool writable) : _writable(writable) {}
    ~Descriptor() override { if (isOpen()) close(); }

    bool open(std::string_view, Mode) override { errno = ENOTSUP; return false; }
    struct stat openAt(NSURL* url, int flags, FileDialogError& error)
    {
        struct stat info{};
        _fd = ::open(url.fileSystemRepresentation, flags | O_NOFOLLOW | O_NONBLOCK | O_CLOEXEC, 0600);
        if (_fd < 0 || fstat(_fd, &info) < 0)
            error = posixError("Could not open the selected document", errno);
        else if (!S_ISREG(info.st_mode))
            error = {DialogErrorCode::InvalidResult, "The selected item is not a regular file"};
        return info;
    }
    int close() override { return ::close(std::exchange(_fd, -1)); }
    int seek(int64_t offset, int origin) override { return lseek(_fd, offset, origin) < 0 ? -1 : 0; }
    int read(void* buf, unsigned int count) override { return static_cast<int>(::read(_fd, buf, count)); }
    int write(const void* buf, unsigned int count) override { return static_cast<int>(::write(_fd, buf, count)); }
    int64_t tell() override { return lseek(_fd, 0, SEEK_CUR); }
    int64_t size() override { struct stat info{}; return fstat(_fd, &info) == 0 ? info.st_size : -1; }
    bool isOpen() const override { return _fd >= 0; }
    bool isReadable() const noexcept override { return !_writable; }
    bool isWritable() const noexcept override { return _writable; }
    bool canResize() const noexcept override { return _writable; }
    bool canSync() const noexcept override { return _writable; }
    int resize(int64_t length) override { return ftruncate(_fd, length); }
    int sync() override { return fsync(_fd); }
private:
    int _fd = -1;
    bool _writable;
};

bool sameFile(const struct stat& a, const struct stat& b)
{
    return a.st_dev == b.st_dev && a.st_ino == b.st_ino && S_ISREG(b.st_mode);
}

bool sameVersion(const struct stat& a, const struct stat& b)
{
    return sameFile(a, b) && a.st_size == b.st_size &&
           a.st_mtimespec.tv_sec == b.st_mtimespec.tv_sec && a.st_mtimespec.tv_nsec == b.st_mtimespec.tv_nsec &&
           a.st_ctimespec.tv_sec == b.st_ctimespec.tv_sec && a.st_ctimespec.tv_nsec == b.st_ctimespec.tv_nsec;
}

FileDialogError checkDirectory(NSURL* url)
{
    struct stat info{};
    if (lstat(url.fileSystemRepresentation, &info) < 0)
        return posixError("Could not inspect the selected directory", errno);
    if (!S_ISDIR(info.st_mode))
        return {DialogErrorCode::InvalidResult, "The selected item is not a directory"};
    return {};
}

#if TARGET_OS_OSX
bool hasNoAppSandboxEntitlement()
{
    static const bool noAppSandbox = [] {
        SecTaskRef task = SecTaskCreateFromSelf(kCFAllocatorDefault);
        if (!task)
            return false;
        CFErrorRef error = nullptr;
        CFTypeRef value = SecTaskCopyValueForEntitlement(task, CFSTR("com.apple.security.app-sandbox"), &error);
        const bool disabled = !error && (!value || value == kCFBooleanFalse);
        if (value) CFRelease(value);
        if (error) CFRelease(error);
        CFRelease(task);
        return disabled;
    }();
    return noAppSandbox;
}
#endif

class AppleDocument final : public DocumentProvider
{
public:
    AppleDocument(NSURL* url, DocumentKind type, uint64_t session, NSURL* scopeRoot = nil)
        : _url(url), _scopeRoot(scopeRoot), _session(session)
    {
        location = LocationKind::AppleDocument;
        kind = type;
        name = string(url.lastPathComponent);
    }

    NSURL* url() const { return currentSession() == _session ? _url : nil; }

    DocumentAccessHints hints() const override
    {
        return url() ? DocumentProvider::hints() : DocumentAccessHints{};
    }

    std::optional<std::string> localPath(FileDialogError&) const override
    {
#if TARGET_OS_OSX
        if (hasNoAppSandboxEntitlement())
        {
            auto path = string(url().path);
            if (!path.empty())
                return path;
        }
#endif
        return {};
    }

    FileDialogError captureTarget()
    {
        if (!url())
            return {DialogErrorCode::Unavailable, "The document's engine session has ended"};
        Scope access(_url);
        if (lstat(_url.fileSystemRepresentation, &_original) == 0)
        {
            if (!S_ISREG(_original.st_mode))
                return {DialogErrorCode::InvalidResult, "The save target is not a regular file"};
            _existingTarget = true;
        }
        else if (errno != ENOENT)
            return posixError("Could not inspect the selected save target", errno);

        _localTarget = Documents::get(localSaveLocation(_url.fileSystemRepresentation));
        if (!_localTarget)
            return {DialogErrorCode::InvalidResult, "Could not record the selected save target"};
        return {};
    }

    FileDialogError read(const StreamOperation& reader) override
    {
        return coordinate(false, [&](NSURL* url) -> FileDialogError {
            auto fd = std::make_unique<Descriptor>(false);
            FileDialogError error;
            fd->openAt(url, O_RDONLY, error);
            if (error)
                return error;
            auto stream = io::FileStream::fromBackend(std::move(fd));
            if (!stream)
                return streamError("Could not create a document stream", stream.error);
            error = reader(*stream.value);
            const auto status = stream.value->close();
            return !error && !status ? streamError("Could not close the document", status.error) : error;
        });
    }

    FileDialogError children(size_t maximum, std::vector<DocumentHandle>& out) override
    {
        return coordinate(false, [&](NSURL* url) -> FileDialogError {
            if (auto error = checkDirectory(url))
                return error;
            NSArray* keys = @[NSURLIsDirectoryKey, NSURLIsRegularFileKey, NSURLIsSymbolicLinkKey];
            __block NSError* enumerationError = nil;
            auto* iterator = [[NSFileManager defaultManager] enumeratorAtURL:url includingPropertiesForKeys:keys
                options:NSDirectoryEnumerationSkipsSubdirectoryDescendants
                errorHandler:^BOOL(NSURL*, NSError* error) { enumerationError = error; return NO; }];
            if (!iterator)
                return {DialogErrorCode::IoError, "Could not enumerate the selected directory"};
            size_t visited = 0;
            for (NSURL* item in iterator)
            {
                if (++visited > maximum)
                    return {DialogErrorCode::LimitExceeded, "The selected directory exceeds the scan limit"};
                NSError* error = nil;
                NSDictionary* info = [item resourceValuesForKeys:keys error:&error];
                if (!info)
                    return cocoaError(error);
                if ([info[NSURLIsSymbolicLinkKey] boolValue])
                    continue;
                const bool isDirectory = [info[NSURLIsDirectoryKey] boolValue];
                if (isDirectory || [info[NSURLIsRegularFileKey] boolValue])
                    out.push_back(Documents::wrap(std::make_shared<AppleDocument>(item,
                        isDirectory ? DocumentKind::Directory : DocumentKind::File, _session, _scopeRoot ?: _url)));
            }
            return enumerationError ? cocoaError(enumerationError) : FileDialogError{};
        });
    }

    FileDialogError write(const std::string& childName, const StreamOperation& writer,
                          DocumentHandle& actual, ExternalEffect& effect) override
    {
        return coordinate(true, [&](NSURL* url) -> FileDialogError {
            if (!childName.empty())
            {
                if (!validName(childName))
                    return {DialogErrorCode::InvalidArgument, "Invalid child name"};
                if (auto error = checkDirectory(url))
                    return error;
                auto directory = Documents::get(localDocument(url.fileSystemRepresentation, DocumentKind::Directory));
                DocumentHandle ignored;
                auto error = directory->write(childName, writer, ignored, effect);
                if (!error)
                    actual = Documents::wrap(std::make_shared<AppleDocument>(
                        [url URLByAppendingPathComponent:string(childName) isDirectory:NO],
                        DocumentKind::File, _session, _scopeRoot ?: _url));
                return error;
            }
            if (!_localTarget || ![url.path isEqualToString:_url.path])
                return changedTarget();
            struct stat current{};
            if (lstat(url.fileSystemRepresentation, &current) == 0)
            {
                if (!_existingTarget || !sameVersion(_original, current))
                    return changedTarget();
            }
            else if (errno != ENOENT)
                return posixError("Could not inspect the selected save target", errno);
            else if (_existingTarget)
                return changedTarget();

            bool writerCalled = false;
            DocumentHandle ignored;
            auto error = _localTarget->write({}, [&](io::Stream& stream) {
                writerCalled = true;
                auto outcome = writer(stream);
                if (!outcome && _existingTarget)
                {
                    struct stat currentVersion{};
                    if (lstat(url.fileSystemRepresentation, &currentVersion) < 0 ||
                        !sameVersion(_original, currentVersion))
                        return changedTarget();
                }
                return outcome;
            }, ignored, effect);
            // Powerbox can grant a file without granting the directory used for atomic staging.
            const bool scopedPathOnly = error.code == DialogErrorCode::PermissionDenied ||
                (error.nativeDomain == "generic" && error.nativeCode == EPERM);
            if (scopedPathOnly && !writerCalled && effect == ExternalEffect::None)
                error = writeAuthorizedPath(url, writer, effect);
            if (!error)
                actual = Documents::wrap(std::make_shared<AppleDocument>(_url, DocumentKind::File, _session));
            return error;
        });
    }

private:
    static FileDialogError changedTarget()
    {
        return {DialogErrorCode::InvalidResult, "The selected save target changed. Choose it again to confirm replacement."};
    }

    FileDialogError writeAuthorizedPath(NSURL* url, const StreamOperation& writer, ExternalEffect& effect)
    {
        auto fd = std::make_unique<Descriptor>(true);
        FileDialogError error;
        const int flags = O_WRONLY | (_existingTarget ? 0 : O_CREAT | O_EXCL);
        const auto original = fd->openAt(url, flags, error);
        if (error)
            return error;
        if (_existingTarget && !sameVersion(_original, original))
            return changedTarget();
        if (!_existingTarget)
            effect = ExternalEffect::PartialPossible;
        auto stream = io::FileStream::fromBackend(std::move(fd), {io::FileAccess::Write});
        if (stream)
        {
            effect = ExternalEffect::PartialPossible;
            if (auto status = stream.value->resize(0); !status)
                error = streamError("Could not truncate the save target", status.error);
            else
                error = writer(*stream.value);
            if (auto status = stream.value->sync(); !status && !error)
                error = streamError("Could not synchronize the save target", status.error);
            if (auto status = stream.value->close(); !status && !error)
                error = streamError("Could not close the save target", status.error);
        }
        else
            error = streamError("Could not create a document stream", stream.error);

        struct stat after{};
        const auto path = url.fileSystemRepresentation;
        const bool stillSelected = lstat(path, &after) == 0 && sameFile(original, after);
        if (!error && !stillSelected)
            error = changedTarget();
        // Without an atomic compare-and-unlink, a concurrent replacement could
        // turn cleanup into deleting someone else's file.
        if (!error)
            effect = ExternalEffect::Committed;
        return error;
    }

    FileDialogError coordinate(bool writing, const std::function<FileDialogError(NSURL*)>& operation)
    {
        @autoreleasepool
        {
            Coordination coordination(_session);
            auto* coordinator = coordination.get();
            if (!coordinator)
                return {DialogErrorCode::Unavailable, "The document's engine session has ended"};
            Scope root(_scopeRoot);
            Scope item(_url);
            NSError* error = nil;
            __block FileDialogError result{DialogErrorCode::IoError, "The file coordinator did not grant access"};
            auto accessor = ^(NSURL* url) {
                if (_scopeRoot)
                {
                    NSString* rootPath = _scopeRoot.URLByResolvingSymlinksInPath.path;
                    NSString* prefix = [rootPath hasSuffix:@"/"] ? rootPath : [rootPath stringByAppendingString:@"/"];
                    NSString* parent = url.URLByDeletingLastPathComponent.URLByResolvingSymlinksInPath.path;
                    if (!prefix || (![parent isEqualToString:rootPath] && ![parent hasPrefix:prefix]))
                    {
                        result = {DialogErrorCode::PermissionDenied, "The document escaped its selected directory"};
                        return;
                    }
                }
                result = operation(url);
            };
            if (writing)
                [coordinator coordinateWritingItemAtURL:_url options:0 error:&error byAccessor:accessor];
            else
                [coordinator coordinateReadingItemAtURL:_url options:0 error:&error byAccessor:accessor];
            return error ? cocoaError(error) : result;
        }
    }

    NSURL* _url;
    NSURL* _scopeRoot;
    uint64_t _session;
    std::shared_ptr<DocumentProvider> _localTarget;
    struct stat _original{};
    bool _existingTarget = false;
};
}

void stopCoordinating()
{
    NSArray<NSFileCoordinator*>* active;
    {
        auto& state = coordinationState();
        std::lock_guard lock(state.mutex);
        state.session = 0;
        active = state.active.allObjects;
    }
    if (active.count)
        dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
            for (NSFileCoordinator* coordinator in active)
                [coordinator cancel];
        });
}

NSString* string(const std::string& value)
{
    return [[NSString alloc] initWithBytes:value.data() length:value.size() encoding:NSUTF8StringEncoding];
}

std::string string(NSString* value)
{
    const char* bytes = value.UTF8String;
    return bytes ? bytes : "";
}

NSURL* directoryURL(const std::optional<DocumentHandle>& directory)
{
    if (!directory)
        return nil;
    if (auto provider = std::dynamic_pointer_cast<AppleDocument>(Documents::get(*directory)))
        return provider->url();
    auto path = directory->tryGetLocalPath();
    return path ? [NSURL fileURLWithFileSystemRepresentation:path->c_str() isDirectory:YES relativeToURL:nil] : nil;
}

DocumentHandle document(NSURL* url, DocumentKind kind)
{
    const auto session = currentSession();
    if (!session || !url.isFileURL || !url.fileSystemRepresentation || url.lastPathComponent.length == 0)
        return {};
    return Documents::wrap(std::make_shared<AppleDocument>(url, kind, session));
}

DocumentHandle saveLocation(NSURL* url, FileDialogError& error)
{
    if (!url.isFileURL || !url.fileSystemRepresentation || url.lastPathComponent.length == 0)
    {
        error = {DialogErrorCode::InvalidResult, "The save panel did not return a valid file URL"};
        return {};
    }
    const auto session = currentSession();
    if (!session)
    {
        error = {DialogErrorCode::Unavailable, "The document's engine session has ended"};
        return {};
    }
    auto provider = std::make_shared<AppleDocument>(url, DocumentKind::File, session);
    error = provider->captureTarget();
    return error ? DocumentHandle{} : Documents::wrap(std::move(provider));
}

ContentTypes contentTypes(const OpenFileOptions& options)
{
    if (options.filters.empty() || options.allowAllFiles)
        return {@[], false};

    NSMutableOrderedSet<UTType*>* types = [NSMutableOrderedSet orderedSet];
    for (const auto& filter : options.filters)
    {
        NSMutableOrderedSet<UTType*>* explicitTypes = [NSMutableOrderedSet orderedSet];
        for (const auto& identifier : filter.appleTypeIdentifiers)
            if (UTType* type = [UTType typeWithIdentifier:string(identifier)]; type && !type.dynamic)
                [explicitTypes addObject:type];
        for (const auto& mime : filter.mimeTypes)
            if (UTType* type = [UTType typeWithMIMEType:string(mime)]; type && !type.dynamic)
                [explicitTypes addObject:type];
        [types unionOrderedSet:explicitTypes];

        for (const auto& extension : filter.extensions)
        {
            UTType* type = [UTType typeWithFilenameExtension:string(extension)];
            if (type && !type.dynamic && extension.find('.') == std::string::npos)
                [types addObject:type];
            else if (explicitTypes.count == 0)
                return {@[], true};
        }
    }
    return {types.array, false};
}

NativeResult selection(NSArray<NSURL*>* urls, const NativeRequest& request, bool validateExtensions)
{
    NativeResult result;
    const auto kind = request.operation == Operation::Folder ? DocumentKind::Directory : DocumentKind::File;
    const auto limit = request.options.allowMultiple && kind == DocumentKind::File ? request.options.maxSelectionCount : 1;
    if (urls.count == 0 || urls.count > limit)
    {
        result.error = {urls.count > limit ? DialogErrorCode::LimitExceeded : DialogErrorCode::InvalidResult,
                        "The picker returned an unexpected number of selected documents"};
        return result;
    }
    for (NSURL* url in urls)
    {
        auto selected = document(url, kind);
        if (!selected || (kind == DocumentKind::File && url.hasDirectoryPath))
        {
            result.documents.clear();
            result.error = {DialogErrorCode::InvalidResult, "The picker returned an invalid document URL"};
            return result;
        }
        if (validateExtensions && kind == DocumentKind::File)
        {
            const auto actual = [UTType typeWithFilenameExtension:url.pathExtension];
            bool matches = false;
            for (const auto& filter : request.options.filters)
            {
                for (const auto& extension : filter.extensions)
                    matches |= [url.lastPathComponent.lowercaseString hasSuffix:string("." + extension).lowercaseString];
                for (const auto& identifier : filter.appleTypeIdentifiers)
                    if (UTType* type = [UTType typeWithIdentifier:string(identifier)])
                        matches |= [actual conformsToType:type];
                for (const auto& mime : filter.mimeTypes)
                    if (UTType* type = [UTType typeWithMIMEType:string(mime)])
                        matches |= [actual conformsToType:type];
            }
            if (!matches)
            {
                result.documents.clear();
                result.error = {DialogErrorCode::InvalidResult, "The selected file does not match the requested types"};
                return result;
            }
        }
        result.documents.push_back(std::move(selected));
    }
    result.status = DialogStatus::Ok;
    return result;
}
}

namespace cc::dialog
{
void startNative()
{
    auto& state = apple::coordinationState();
    std::lock_guard lock(state.mutex);
    state.session = ++state.sequence;
}
}
