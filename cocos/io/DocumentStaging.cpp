#include "platform/FileDialogInternal.h"
#include "platform/AppDirectories.h"
#include <algorithm>
#include <array>
#if defined(_WIN32)
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#endif

namespace cc::dialog {
namespace fs = std::filesystem;
namespace {
constexpr char prefix[] = "cocos-file-dialog-v1\n";
constexpr char manifest[] = ".owner";
class Lease {
public:
    bool open(const fs::path& path, bool create) {
#if defined(_WIN32)
        _file = CreateFileW(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                            create ? CREATE_NEW : OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
        return _file != INVALID_HANDLE_VALUE;
#else
        _fd = ::open(path.c_str(), O_RDWR | O_NOFOLLOW | O_CLOEXEC | (create ? O_CREAT | O_EXCL : 0), 0600);
        return _fd >= 0 && flock(_fd, LOCK_EX | LOCK_NB) == 0;
#endif
    }
    bool record(const std::string& name) {
        auto data = prefix + name;
#if defined(_WIN32)
        DWORD written = 0;
        return WriteFile(_file, data.data(), static_cast<DWORD>(data.size()), &written, nullptr) &&
               written == data.size() && FlushFileBuffers(_file);
#else
        return ::write(_fd, data.data(), data.size()) == static_cast<ssize_t>(data.size()) && fsync(_fd) == 0;
#endif
    }
    std::string recordedName() {
        std::array<char, 4096> data{};
#if defined(_WIN32)
        DWORD count = 0;
        if (!ReadFile(_file, data.data(), static_cast<DWORD>(data.size()), &count, nullptr)) return {};
#else
        auto count = ::read(_fd, data.data(), data.size());
        if (count < 0) return {};
#endif
        if (size_t(count) == data.size()) return {};
        std::string text(data.data(), count);
        if (text.compare(0, sizeof(prefix)-1, prefix) != 0) return {};
        auto name = text.substr(sizeof(prefix)-1);
        return validName(name) ? name : std::string{};
    }
    ~Lease() {
#if defined(_WIN32)
        if (_file != INVALID_HANDLE_VALUE) CloseHandle(_file);
#else
        if (_fd >= 0) ::close(_fd);
#endif
    }
private:
#if defined(_WIN32)
    HANDLE _file = INVALID_HANDLE_VALUE;
#else
    int _fd = -1;
#endif
};
void recover(const fs::path& root) {
    std::error_code ec;
    for (fs::directory_iterator it(root, ec), end; !ec && it != end; it.increment(ec)) {
        auto dir = it->path();
        if (!fs::is_directory(it->symlink_status(ec))) continue;
        auto name = dir.filename().string();
        if (name.empty() || name.find_first_not_of("0123456789-") != std::string::npos) continue;
        std::error_code ignored;
        if (!fs::is_regular_file(fs::symlink_status(dir / manifest, ignored))) continue;
        {
            Lease abandoned;
            if (!abandoned.open(dir / manifest, false)) continue;
            auto recorded = abandoned.recordedName();
            if (recorded.empty()) continue;
            auto payload = dir / "content";
            if (fs::is_directory(fs::symlink_status(payload, ignored))) {
                fs::remove(payload / fs::u8path(recorded), ignored);
                if (!fs::remove(payload, ignored)) continue;
            }
        }
        fs::remove(dir / manifest, ignored);
        fs::remove(dir, ignored);
    }
}
}
FileDialogError prepareSnapshot(DocumentHandle source, const std::string& name, TransferLimits limits,
                                const AccessJob& job, std::shared_ptr<Snapshot>& out) {
    if (!validName(name)) return {DialogErrorCode::InvalidArgument, "Invalid snapshot name"};
    auto root = cc::detail::ensureAppDirectory(AppDirectory::TransientData, "file-dialog");
    if (root.status != DirectoryStatus::Ok)
        return {DialogErrorCode::IoError, "Cannot create staging root", root.nativeDomain, root.nativeCode};
    auto parent = fs::u8path(root.path);
    thread_local fs::path checked;
    if (checked != parent) { recover(parent); checked = parent; }
    auto stage = std::make_shared<Snapshot>();
    const auto dir = parent / uniqueName();
    std::error_code ec;
    if (!fs::create_directory(dir, ec))
        return {DialogErrorCode::IoError, "Cannot reserve staging directory", ec.category().name(), ec.value()};
    stage->directory = dir;
    auto lease = std::make_shared<Lease>();
    if (!lease->open(dir / manifest, true)) return {DialogErrorCode::IoError, "Cannot reserve staging manifest"};
    stage->lease = lease;
    if (!lease->record(name) || !fs::create_directory(dir / "content", ec))
        return {DialogErrorCode::IoError, "Cannot initialize staging manifest"};
    stage->path = dir / "content" / fs::u8path(name);
    auto error = writeSnapshotFile(stage->path, [&](io::Stream& stream) {
        return copyDocument(source, stream, limits, job.cancelled);
    });
    if (!error) {
        stage->document = localDocument(stage->path, DocumentKind::File);
        out = std::move(stage);
    }
    return error;
}
Snapshot::~Snapshot() {
    std::error_code ec;
    if (directory.empty()) return;
    if (!path.empty()) fs::remove(path, ec);
    fs::remove(directory / "content", ec);
    if (lease) {
        lease.reset();
        fs::remove(directory / manifest, ec);
    }
    fs::remove(directory, ec);
}
}
