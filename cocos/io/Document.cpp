#include "platform/FileDialogInternal.h"
#include "base/ccUTF8.h"
#include "io/FileStream.h"
#include "platform/PosixFileStream.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cerrno>
#include <random>
#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/stat.h>
#if defined(__APPLE__)
#include <stdio.h>
#endif
#if defined(__ANDROID__)
#include <array>
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif
#endif

namespace fs = std::filesystem;
namespace cc::dialog {
namespace {
fs::path osPath(const fs::path& path)
{
#if defined(_WIN32)
    if (path.native().size() >= 248 && path.is_absolute()) {
        auto wide = fs::path(path).lexically_normal().make_preferred().native();
        if (wide.starts_with(LR"(\\?\)") || wide.starts_with(LR"(\\.\)")) return wide;
        if (wide.starts_with(LR"(\\)")) return LR"(\\?\UNC\)" + wide.substr(2);
        return LR"(\\?\)" + wide;
    }
#endif
    return path;
}

std::string bytes(const fs::path& path)
{
    const auto value = path.u8string();
    return {value.begin(), value.end()};
}

FileDialogError filesystemError(std::error_code ec, std::string action)
{
    auto code = DialogErrorCode::IoError;
    if (ec == std::errc::permission_denied) code = DialogErrorCode::PermissionDenied;
    if (ec == std::errc::no_such_file_or_directory) code = DialogErrorCode::NotFound;
    return {code, std::move(action) + ": " + ec.message(), ec.category().name(), ec.value()};
}

struct FileStamp {
    uint64_t device = 0, id = 0, modified = 0, size = 0;
    bool exists = false;
    bool operator==(const FileStamp&) const = default;
};

FileDialogError inspect(const fs::path& path, FileStamp& stamp, DocumentKind kind = DocumentKind::File)
{
    const bool directory = kind == DocumentKind::Directory;
    auto typeError = [&] {
        return FileDialogError{DialogErrorCode::InvalidArgument,
                               directory ? "Expected a regular directory" : "Expected a regular file"};
    };
#if defined(_WIN32)
    HANDLE h = CreateFileW(osPath(path).c_str(), FILE_READ_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        auto e = GetLastError();
        if (e == ERROR_FILE_NOT_FOUND || e == ERROR_PATH_NOT_FOUND) return {};
        return filesystemError({static_cast<int>(e), std::system_category()}, "Inspect document");
    }
    BY_HANDLE_FILE_INFORMATION st{};
    const bool ok = GetFileInformationByHandle(h, &st) != FALSE;
    const auto error = GetLastError();
    CloseHandle(h);
    if (!ok) return filesystemError({static_cast<int>(error), std::system_category()}, "Inspect file identity");
    if ((st.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) ||
        bool(st.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != directory)
        return typeError();
    auto combine = [](DWORD high, DWORD low) { return (uint64_t(high) << 32) | low; };
    stamp = {st.dwVolumeSerialNumber, combine(st.nFileIndexHigh, st.nFileIndexLow),
             combine(st.ftLastWriteTime.dwHighDateTime, st.ftLastWriteTime.dwLowDateTime),
             combine(st.nFileSizeHigh, st.nFileSizeLow), true};
#else
    struct stat st{};
    if (::lstat(path.c_str(), &st) != 0) {
        if (errno == ENOENT) return {};
        return filesystemError({errno, std::generic_category()}, "Inspect document");
    }
    if (directory ? !S_ISDIR(st.st_mode) : !S_ISREG(st.st_mode)) return typeError();
#if defined(__APPLE__)
    const auto time = st.st_mtimespec;
#else
    const auto time = st.st_mtim;
#endif
    stamp = {static_cast<uint64_t>(st.st_dev), static_cast<uint64_t>(st.st_ino),
             uint64_t(time.tv_sec) * 1000000000 + time.tv_nsec, uint64_t(st.st_size), true};
#endif
    return {};
}

bool sameIdentity(const FileStamp& first, const FileStamp& second)
{
    return first.device == second.device && first.id == second.id;
}

FileDialogError inspectDirectory(const fs::path& path, FileStamp& stamp, const FileStamp* expected = nullptr)
{
    if (auto error = inspect(path, stamp, DocumentKind::Directory)) return error;
    if (!stamp.exists) return {DialogErrorCode::NotFound, "Directory no longer exists"};
    if (expected && !sameIdentity(stamp, *expected)) return {DialogErrorCode::IoError, "Directory was replaced"};
    return {};
}

auto openPhysical(const fs::path& path, io::FileOpenOptions options)
{
    using Result = io::Result<ThreadSafeRefPtr<io::FileStream>>;
    auto backend = std::make_unique<PosixFileStream>();
    FileStream::Mode mode;
    if (!FileStream::encodeOpenOptions(options, mode) || !backend->open(bytes(osPath(path)), mode))
        return Result::failure({io::ErrorCode::IoError, errno, io::ErrorDomain::Errno});
    return io::FileStream::fromBackend(std::move(backend), options);
}

struct OwnedFile {
    fs::path path;
    ~OwnedFile() { if (!path.empty()) { std::error_code ignored; fs::remove(path, ignored); } }
};

FileDialogError writeAndClose(io::Stream& stream, const StreamOperation& writer)
{
    auto error = writer(stream);
    if (!error) {
        auto sync = stream.sync();
        if (!sync) error = filesystemError({sync.error.nativeCode, std::generic_category()}, "Sync written file");
    }
    auto closed = stream.close();
    if (!closed && !error) error = filesystemError({closed.error.nativeCode, std::generic_category()}, "Close written file");
    return error;
}

#if defined(__ANDROID__)
struct ScopedDescriptor {
    int value;
    ~ScopedDescriptor() { if (value >= 0) ::close(value); }
    int close() { return ::close(std::exchange(value, -1)); }
};

struct AndroidCreatedFile {
    int directory;
    const fs::path& name;
    struct stat identity;
    ExternalEffect& effect;
    bool keep = false;

    bool ownsCurrent() const {
        struct stat current{};
        return ::fstatat(directory, name.c_str(), &current, AT_SYMLINK_NOFOLLOW) == 0 &&
               current.st_dev == identity.st_dev && current.st_ino == identity.st_ino;
    }
    ~AndroidCreatedFile() {
        if (keep) return;
        struct stat current{};
        if (::fstatat(directory, name.c_str(), &current, AT_SYMLINK_NOFOLLOW) != 0) {
            if (errno == ENOENT) effect = ExternalEffect::None;
            return;
        }
        if (current.st_dev == identity.st_dev && current.st_ino == identity.st_ino &&
            ::unlinkat(directory, name.c_str(), 0) == 0)
            effect = ExternalEffect::None;
    }
};

FileDialogError copyAndroidFile(int source, int destination, uint64_t remaining)
{
    std::array<char, 64 * 1024> buffer;
    while (remaining) {
        const size_t capacity = std::min<uint64_t>(remaining, buffer.size());
        const auto count = TEMP_FAILURE_RETRY(::read(source, buffer.data(), capacity));
        if (count < 0) return filesystemError({errno, std::generic_category()}, "Read staged file");
        if (count == 0) return {DialogErrorCode::IoError, "Staged file ended before the recorded size"};
        for (ssize_t written = 0; written < count;) {
            const auto added = TEMP_FAILURE_RETRY(::write(destination, buffer.data() + written, count - written));
            if (added < 0) return filesystemError({errno, std::generic_category()}, "Write new file");
            if (added == 0) return {DialogErrorCode::IoError, "Write made no progress"};
            written += added;
        }
        remaining -= count;
    }
    return {};
}

FileDialogError publishLegacyAndroidFile(const fs::path& staged, const fs::path& target,
                                        const FileStamp& expectedDirectory, ExternalEffect& effect)
{
    // Pre-renameat2 Android kernels can also deny links. Install through an
    // exclusive descriptor bound to the same directory. The destination can
    // be observed during copying on these kernels.
    ScopedDescriptor directory{::open(target.parent_path().c_str(), O_RDONLY | O_DIRECTORY | O_NOFOLLOW | O_CLOEXEC)};
    if (directory.value < 0) return filesystemError({errno, std::generic_category()}, "Open destination directory");
    struct stat parentInfo{};
    if (::fstat(directory.value, &parentInfo) != 0)
        return filesystemError({errno, std::generic_category()}, "Inspect destination directory");
    if (expectedDirectory.exists && (expectedDirectory.device != uint64_t(parentInfo.st_dev) ||
                                     expectedDirectory.id != uint64_t(parentInfo.st_ino)))
        return {DialogErrorCode::IoError, "Destination directory was replaced"};

    const auto stagedName = staged.filename();
    ScopedDescriptor source{::openat(directory.value, stagedName.c_str(), O_RDONLY | O_NOFOLLOW | O_CLOEXEC)};
    if (source.value < 0) return filesystemError({errno, std::generic_category()}, "Open staged file");
    struct stat sourceInfo{};
    if (::fstat(source.value, &sourceInfo) != 0)
        return filesystemError({errno, std::generic_category()}, "Inspect staged file");
    if (!S_ISREG(sourceInfo.st_mode) || sourceInfo.st_size < 0)
        return {DialogErrorCode::IoError, "Staged file is not a regular file"};

    const auto name = target.filename();
    ScopedDescriptor destination{::openat(directory.value, name.c_str(),
            O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, S_IRUSR | S_IWUSR)};
    if (destination.value < 0) return filesystemError({errno, std::generic_category()}, "Create new file");
    effect = ExternalEffect::PartialPossible;
    struct stat identity{};
    if (::fstat(destination.value, &identity) != 0)
        return filesystemError({errno, std::generic_category()}, "Inspect new file");
    AndroidCreatedFile created{directory.value, name, identity, effect};
    auto error = copyAndroidFile(source.value, destination.value, sourceInfo.st_size);
    if (!error && TEMP_FAILURE_RETRY(::fsync(destination.value)) != 0)
        error = filesystemError({errno, std::generic_category()}, "Sync new file");
    if (destination.close() != 0 && !error)
        error = filesystemError({errno, std::generic_category()}, "Close new file");
    if (source.close() != 0 && !error)
        error = filesystemError({errno, std::generic_category()}, "Close staged file");

    if (error) return error;
    if (!created.ownsCurrent()) return {DialogErrorCode::IoError, "New file no longer exists at the destination"};
    created.keep = true;
    return {};
}
#endif

class LocalDocument final : public DocumentProvider {
public:
    LocalDocument(fs::path path, DocumentKind type, bool save, bool portal = false,
                  bool captureDirectory = false, std::optional<FileStamp> parent = {})
        : _path(std::move(path)), _save(save), _portal(portal), _parent(std::move(parent)) {
        kind = type;
        name = bytes(_path.filename());
        if (!StringUtils::isLegalUTF8String(name.data(), name.size())) name = "document";
        if (_save) _inspectError = inspect(_path, _initial);
        if (captureDirectory) _inspectError = inspectDirectory(_path, _initial);
    }

    std::optional<std::string> localPath(FileDialogError& error) const override {
        auto value = bytes(_path);
        if (StringUtils::isLegalUTF8String(value.data(), value.size())) return value;
        error = {DialogErrorCode::EncodingError, "Local filename cannot be represented in UTF-8"};
        return {};
    }

    FileDialogError read(const StreamOperation& reader) override {
        if (kind != DocumentKind::File) return {DialogErrorCode::InvalidArgument, "Cannot read a directory as a file"};
        if (auto error = verifyParent()) return error;
        FileStamp stamp;
        if (auto error = inspect(_path, stamp)) return error;
        if (!stamp.exists) return {DialogErrorCode::NotFound, "Document no longer exists"};
        auto stream = openPhysical(_path, {});
        if (!stream) return filesystemError({stream.error.nativeCode, std::generic_category()}, "Open document");
        auto error = reader(*stream.value);
        auto closed = stream.value->close();
        if (!error && !closed) return filesystemError({closed.error.nativeCode, std::generic_category()}, "Close document");
        return error;
    }

    FileDialogError children(size_t maximum, std::vector<DocumentHandle>& out) override {
        if (kind != DocumentKind::Directory) return {DialogErrorCode::InvalidArgument, "Expected a directory"};
        if (_inspectError) return _inspectError;
        if (auto error = verifyParent()) return error;
        FileStamp directory;
        if (auto error = inspectDirectory(_path, directory, _initial.exists ? &_initial : nullptr)) return error;
        std::error_code ec;
        fs::directory_iterator it(osPath(_path), ec), end;
        while (!ec && it != end) {
            auto type = it->symlink_status(ec);
            if (ec) break;
            if (fs::is_regular_file(type) || fs::is_directory(type)) {
                if (out.size() >= maximum) return {DialogErrorCode::LimitExceeded, "Directory enumeration limit exceeded"};
                auto childKind = fs::is_directory(type) ? DocumentKind::Directory : DocumentKind::File;
                out.push_back(Documents::wrap(std::make_shared<LocalDocument>(_path / it->path().filename(), childKind,
                    false, _portal, childKind == DocumentKind::Directory, directory)));
            }
            it.increment(ec);
        }
        if (ec) return filesystemError(ec, "List directory");
        FileStamp current;
        return inspectDirectory(_path, current, &directory);
    }

    FileDialogError write(const std::string& child, const StreamOperation& writer,
                          DocumentHandle& actual, ExternalEffect& effect) override {
        if (child.empty() ? !_save : (kind != DocumentKind::Directory || !validName(child)))
            return {DialogErrorCode::InvalidArgument, "Expected a selected target or a single child name"};
        if (_inspectError) return _inspectError;
        if (auto error = verifyParent()) return error;
        FileStamp directory;
        if (!child.empty()) {
            if (auto error = inspectDirectory(_path, directory, _initial.exists ? &_initial : nullptr)) return error;
        }
        const auto path = child.empty() ? _path : _path / fs::u8path(child);
        FileStamp expected = child.empty() ? _initial : FileStamp{};
        auto verify = [&]() -> FileDialogError {
            FileStamp current;
            if (!child.empty()) {
                if (auto error = inspectDirectory(_path, current, &directory)) return error;
                current = {};
            }
            if (auto error = inspect(path, current)) return error;
            if (current != expected) return {DialogErrorCode::IoError, "Save target changed or already exists"};
            return {};
        };
        if (auto error = verify()) return error;

        if (_portal) {
            // A Documents Portal grant may only permit opening this exact file.
            // Preserve exclusive child creation and avoid temporary siblings.
            auto destination = Documents::wrap(std::make_shared<LocalDocument>(path, DocumentKind::File, false, true));
            auto creation = expected.exists ? io::FileCreation::OpenExisting : io::FileCreation::CreateNew;
            auto stream = openPhysical(path, {io::FileAccess::Write, creation});
            if (!stream) return filesystemError({stream.error.nativeCode, std::generic_category()}, "Open portal save target");
            if (expected.exists) {
                if (auto changed = verify()) return changed;
                effect = ExternalEffect::PartialPossible;
                auto truncated = stream.value->resize(0);
                if (!truncated) return filesystemError({truncated.error.nativeCode, std::generic_category()}, "Truncate portal save target");
            } else {
                effect = ExternalEffect::PartialPossible;
            }
            if (auto error = writeAndClose(*stream.value, writer)) return error;
            effect = ExternalEffect::Committed;
            actual = std::move(destination);
            return {};
        }

        auto tempPath = path.parent_path() / (".cocos-dialog-" + uniqueName());
        auto stream = openPhysical(tempPath, {io::FileAccess::Write, io::FileCreation::CreateNew});
        if (!stream) return filesystemError({stream.error.nativeCode, std::generic_category()}, "Create sibling temporary file");
        OwnedFile temporary{osPath(tempPath)};
        if (auto error = writeAndClose(*stream.value, writer)) return error;
        if (auto changed = verify()) return changed;
        auto committed = localDocument(path, DocumentKind::File);
#if defined(_WIN32)
        auto targetName = osPath(path), temporaryName = osPath(tempPath);
        BOOL ok = expected.exists ? ReplaceFileW(targetName.c_str(), temporaryName.c_str(), nullptr, 0, nullptr, nullptr)
                                  : MoveFileExW(temporaryName.c_str(), targetName.c_str(), MOVEFILE_WRITE_THROUGH);
        if (!ok) {
            auto nativeError = GetLastError();
            if (expected.exists && (nativeError == ERROR_UNABLE_TO_MOVE_REPLACEMENT ||
                                    nativeError == ERROR_UNABLE_TO_MOVE_REPLACEMENT_2))
                effect = ExternalEffect::PartialPossible;
            return filesystemError({static_cast<int>(nativeError), std::system_category()}, "Commit save target");
        }
        temporary.path.clear();
#else
        std::error_code ec;
        if (expected.exists) fs::rename(tempPath, path, ec);
#if defined(__APPLE__)
        else if (::renamex_np(tempPath.c_str(), path.c_str(), RENAME_EXCL) == 0)
            temporary.path.clear();
        else ec.assign(errno, std::generic_category());
#elif defined(__ANDROID__)
        else {
            // Android's app sandbox can deny hard links even within private storage.
            // The kernel operation is available before the public bionic wrapper.
            if (::syscall(SYS_renameat2, AT_FDCWD, tempPath.c_str(), AT_FDCWD, path.c_str(), RENAME_NOREPLACE) != 0) {
                const int error = errno;
                if (error != ENOSYS && error != EINVAL && error != EOPNOTSUPP)
                    return filesystemError({error, std::generic_category()}, "Commit save target");
                if (auto fallback = publishLegacyAndroidFile(tempPath, path, directory, effect)) return fallback;
            } else {
                temporary.path.clear();
            }
        }
#else
        else fs::create_hard_link(tempPath, path, ec);
#endif
        if (ec) return filesystemError(ec, "Commit save target");
        if (expected.exists) temporary.path.clear();
#endif
        effect = ExternalEffect::Committed;
        actual = std::move(committed);
        return {};
    }
private:
    FileDialogError verifyParent() const {
        if (!_parent) return {};
        FileStamp parent;
        return inspectDirectory(_path.parent_path(), parent, &*_parent);
    }
    fs::path _path;
    bool _save, _portal;
    std::optional<FileStamp> _parent;
    FileStamp _initial;
    FileDialogError _inspectError;
};
}

std::string uniqueName()
{
    static std::atomic<uint64_t> serial{0};
    static const uint64_t salt = (uint64_t(std::random_device{}()) << 32) ^ std::random_device{}();
    return std::to_string(salt) + "-" + std::to_string(++serial);
}

bool validName(const std::string& s)
{
#ifdef _WIN32
    if (s.empty() || s.back() == '.' || s.back() == ' ' || s.find_first_of("<>\"|?*") != std::string::npos) return false;
    auto stem = s.substr(0, s.find('.'));
    std::transform(stem.begin(), stem.end(), stem.begin(), [](unsigned char c) { return (c >= 'a' && c <= 'z') ? c - 32 : c; });
    if (stem == "CON" || stem == "NUL" || stem == "PRN" || stem == "AUX" || stem == "CONIN$" || stem == "CONOUT$" ||
        (stem.size() == 4 && (stem.substr(0,3) == "COM" || stem.substr(0,3) == "LPT") && stem[3] >= '0' && stem[3] <= '9')) return false;
#endif
    return !s.empty() && s != "." && s != ".." &&
           s.find_first_of("/\\:") == std::string::npos &&
           std::none_of(s.begin(), s.end(), [](unsigned char c) { return c < 32 || c == 127; }) &&
           StringUtils::isLegalUTF8String(s.data(), s.size());
}
FileDialogError writeSnapshotFile(const fs::path& path, const StreamOperation& writer) {
    auto stream = openPhysical(path, {io::FileAccess::Write, io::FileCreation::CreateNew});
    if (!stream) return filesystemError({stream.error.nativeCode, std::generic_category()}, "Create snapshot");
    auto error = writer(*stream.value);
    auto closed = stream.value->close();
    if (!closed && !error) error = filesystemError({closed.error.nativeCode, std::generic_category()}, "Close snapshot");
    return error;
}
DocumentHandle localSaveLocation(const fs::path& p) {
    return Documents::wrap(std::make_shared<LocalDocument>(p, DocumentKind::File, true));
}
DocumentHandle localDocument(const fs::path& p, DocumentKind k) {
    return Documents::wrap(std::make_shared<LocalDocument>(p, k, false));
}
DocumentHandle localSelectedDirectory(const fs::path& path) {
    return Documents::wrap(std::make_shared<LocalDocument>(path, DocumentKind::Directory, false, false, true));
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
DocumentHandle localPortalLocation(const fs::path& path, DocumentKind kind, bool save) {
    return Documents::wrap(std::make_shared<LocalDocument>(path, kind, save, true, kind == DocumentKind::Directory));
}
#endif
FileDialogError DocumentProvider::children(size_t, std::vector<DocumentHandle>&) {
    return {DialogErrorCode::UnsupportedFeature, "Directory enumeration unavailable"};
}
FileDialogError DocumentProvider::write(const std::string&, const StreamOperation&, DocumentHandle&, ExternalEffect&) {
    return {DialogErrorCode::UnsupportedFeature, "Document is not writable"};
}
}

namespace cc {
DocumentKind DocumentHandle::kind() const { return _provider ? _provider->kind : DocumentKind::File; }
LocationKind DocumentHandle::locationKind() const { return _provider ? _provider->location : LocationKind::LocalFile; }
std::string DocumentHandle::displayName() const { return _provider ? _provider->name : std::string{}; }
std::string DocumentHandle::mimeType() const { return _provider ? _provider->mime : std::string{}; }
std::optional<uint64_t> DocumentHandle::size() const { return _provider ? _provider->length : std::nullopt; }
DocumentAccessHints DocumentHandle::accessHints() const { return _provider ? _provider->hints() : DocumentAccessHints{}; }
std::optional<std::string> DocumentHandle::tryGetLocalPath(FileDialogError& error) const {
    error = {};
    return _provider ? _provider->localPath(error) : std::nullopt;
}
std::optional<std::string> DocumentHandle::tryGetLocalPath() const {
    FileDialogError error;
    return tryGetLocalPath(error);
}
std::optional<std::string> SaveTarget::tryGetLocalPath() const { return _target.tryGetLocalPath(); }
std::optional<std::string> SaveTarget::tryGetLocalPath(FileDialogError& error) const { return _target.tryGetLocalPath(error); }
std::string DocumentHandle::legacyAndroidUri() const { return _provider ? _provider->legacyAndroidUri() : std::string{}; }
DocumentHandle DocumentAccess::fromLocalPath(std::string path, DocumentKind kind) {
    if (path.empty() || path.find('\0') != std::string::npos || !StringUtils::isLegalUTF8String(path.data(), path.size())) return {};
    auto p = fs::u8path(path);
    return p.is_absolute() ? dialog::localDocument(p, kind) : DocumentHandle{};
}
}
