#include "io/zip/detail/ZipSource.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#if defined(__linux__)
#include <sys/syscall.h>
#include <fcntl.h>
#elif defined(__APPLE__)
#include <stdio.h>
#endif
#endif

namespace cc::archive::detail
{
StreamError zipError(int code)
{
    ErrorCode error = ErrorCode::IoError;
    switch (code) {
    case ZIP_ER_NOENT: error = ErrorCode::NotFound; break;
    case ZIP_ER_EXISTS: error = ErrorCode::AlreadyExists; break;
    case ZIP_ER_MEMORY: error = ErrorCode::OutOfMemory; break;
    case ZIP_ER_NOPASSWD: error = ErrorCode::CredentialsRequired; break;
    case ZIP_ER_WRONGPASSWD: case ZIP_ER_RDONLY: error = ErrorCode::PermissionDenied; break;
    case ZIP_ER_INVAL: error = ErrorCode::InvalidArgument; break;
    case ZIP_ER_CRC: case ZIP_ER_INCONS: case ZIP_ER_EOF: case ZIP_ER_COMPRESSED_DATA:
    case ZIP_ER_DATA_LENGTH: error = ErrorCode::CorruptData; break;
    case ZIP_ER_NOZIP: case ZIP_ER_MULTIDISK: case ZIP_ER_COMPNOTSUPP:
    case ZIP_ER_ENCRNOTSUPP: error = ErrorCode::UnsupportedFormat; break;
    case ZIP_ER_CANCELLED: error = ErrorCode::Cancelled; break;
    }
    return {error, code, io::ErrorDomain::Libzip};
}

StreamError fileError(std::error_code error)
{
    auto code = ErrorCode::IoError;
    if (error == std::errc::no_such_file_or_directory) code = ErrorCode::NotFound;
    else if (error == std::errc::file_exists) code = ErrorCode::AlreadyExists;
    else if (error == std::errc::permission_denied) code = ErrorCode::PermissionDenied;
    else if (error == std::errc::no_space_on_device) code = ErrorCode::NoSpace;
#ifdef _WIN32
    if (error.category() == std::system_category())
        return {code, error.value(), io::ErrorDomain::Win32};
#endif
    return {code, error.value(), io::ErrorDomain::Errno};
}

std::string utf8(const fs::path& path)
{
    auto bytes = path.generic_u8string();
    return {reinterpret_cast<const char*>(bytes.data()), bytes.size()};
}

Result<std::string> cleanName(std::string_view name, bool directory)
{
    using Output = Result<std::string>;
    if (name.empty() || name.starts_with('/') || name.find_first_of("\\:") != name.npos ||
        name.find('\0') != name.npos || (!directory && name.ends_with('/')))
        return Output::failure({ErrorCode::InvalidArgument});
    std::string result;
    while (!name.empty()) {
        auto end = name.find('/');
        auto part = name.substr(0, end);
        if (part == "..") {
            if (result.empty()) return Output::failure({ErrorCode::InvalidArgument});
            auto pos = result.rfind('/');
            result.resize(pos == result.npos ? 0 : pos);
        } else if (!part.empty() && part != ".") {
            if (!result.empty()) result += '/';
            result += part;
        }
        if (end == name.npos) break;
        name.remove_prefix(end + 1);
    }
    if (result.empty()) return Output::failure({ErrorCode::InvalidArgument});
    if (directory) result += '/';
    return Output::success(std::move(result));
}

bool portableComponent(std::string_view name)
{
    if (name.empty() || name.back() == '.' || name.back() == ' ' ||
        name.find_first_of("<>:\"/\\|?*") != name.npos) return false;
    for (unsigned char c : name) if (c < 32) return false;
    auto stem = std::string(name.substr(0, name.find('.')));
    for (char& c : stem) if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
    if (stem == "CON" || stem == "NUL" || stem == "AUX" || stem == "PRN" ||
        stem == "CONIN$" || stem == "CONOUT$") return false;
    return !(stem.size() == 4 && (stem.starts_with("COM") || stem.starts_with("LPT")) &&
             stem[3] >= '0' && stem[3] <= '9');
}

Result<std::shared_ptr<FileLease>> acquire(std::string_view name, bool writer)
{
    using Output = Result<std::shared_ptr<FileLease>>;
    if (name.empty() || name.find('\0') != name.npos)
        return Output::failure({ErrorCode::InvalidArgument});
    std::error_code ec;
    auto absolute = fs::absolute(fs::u8path(name), ec);
    if (ec) return Output::failure(fileError(ec));
    auto path = fs::weakly_canonical(absolute, ec);
    if (ec) return Output::failure(fileError(ec));
    static std::mutex mutex;
    static std::vector<std::weak_ptr<FileLease>> active;
    std::lock_guard lock(mutex);
    std::erase_if(active, [](const auto& item) { return item.expired(); });
    for (auto& weak : active) {
        auto lease = weak.lock();
        if (!lease || (!writer && !lease->writer)) continue;
        if (lease->path == path || fs::equivalent(path, lease->path, ec))
            return Output::failure({ErrorCode::Busy});
#ifdef _WIN32
        if (CompareStringOrdinal(path.c_str(), -1, lease->path.c_str(), -1, TRUE) == CSTR_EQUAL)
            return Output::failure({ErrorCode::Busy});
#endif
    }
    auto lease = std::make_shared<FileLease>(FileLease{std::move(path), writer});
    active.push_back(lease);
    return Output::success(std::move(lease));
}

TemporaryDirectory::~TemporaryDirectory()
{
    if (!path.empty()) {
        std::error_code ignored;
        fs::remove_all(path, ignored);
    }
}

Result<std::shared_ptr<TemporaryDirectory>> TemporaryDirectory::create(const fs::path& parent)
{
    static std::atomic<uint64_t> next{};
    auto temp = std::make_shared<TemporaryDirectory>();
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    for (unsigned attempt = 0; attempt < 128; ++attempt) {
        auto candidate = parent / (".cocos-zip-" + std::to_string(stamp) + "-" + std::to_string(++next));
        std::error_code ec;
#ifdef _WIN32
        const bool created = fs::create_directory(candidate, ec);
#else
        const bool created = ::mkdir(candidate.c_str(), 0700) == 0;
        if (!created) ec = {errno, std::generic_category()};
#endif
        if (created) {
            temp->path = std::move(candidate);
            return Result<std::shared_ptr<TemporaryDirectory>>::success(std::move(temp));
        }
        if (ec && ec != std::errc::file_exists)
            return Result<std::shared_ptr<TemporaryDirectory>>::failure(fileError(ec));
    }
    return Result<std::shared_ptr<TemporaryDirectory>>::failure({ErrorCode::AlreadyExists});
}

Status publish(const fs::path& source, const fs::path& destination, bool replace)
{
#ifdef _WIN32
    if (MoveFileExW(source.c_str(), destination.c_str(), replace ? MOVEFILE_REPLACE_EXISTING : 0))
        return Status::success();
    return Status::failure(fileError({static_cast<int>(GetLastError()), std::system_category()}));
#else
    if (replace) {
        if (::rename(source.c_str(), destination.c_str()) == 0) return Status::success();
    } else {
#if defined(__linux__) && defined(SYS_renameat2)
        if (::syscall(SYS_renameat2, AT_FDCWD, source.c_str(), AT_FDCWD, destination.c_str(), 1u) == 0)
            return Status::success();
#elif defined(__APPLE__)
        if (::renamex_np(source.c_str(), destination.c_str(), RENAME_EXCL) == 0) return Status::success();
#else
        return Status::failure({ErrorCode::NotSupported});
#endif
    }
    return Status::failure(fileError({errno, std::generic_category()}));
#endif
}

namespace {
struct StreamSource {
    io::StreamPtr stream;
    uint64_t length;
    zip_error_t error;
    StreamSource(io::StreamPtr s, uint64_t n) : stream(std::move(s)), length(n) { zip_error_init(&error); }
    ~StreamSource() { zip_error_fini(&error); }
};
zip_int64_t sourceCall(void* user, void* data, zip_uint64_t length, zip_source_cmd_t cmd)
{
    auto& s = *static_cast<StreamSource*>(user);
    switch (cmd) {
    case ZIP_SOURCE_OPEN:
        if (s.stream->seek(io::SeekOrigin::Begin, 0)) return 0;
        break;
    case ZIP_SOURCE_READ: {
        auto r = s.stream->read(data, static_cast<size_t>(std::min<uint64_t>(length, SIZE_MAX)));
        if (r || r.status == io::IoStatus::EndOfStream) return r.transferred;
        zip_error_set(&s.error, ZIP_ER_READ, 0);
        return -1;
    }
    case ZIP_SOURCE_TELL: {
        auto position = s.stream->tell();
        if (position) return position.value;
        break;
    }
    case ZIP_SOURCE_SEEK: {
        auto* args = ZIP_SOURCE_GET_ARGS(zip_source_args_seek_t, data, length, &s.error);
        if (!args) return -1;
        if (args->whence != SEEK_SET && args->whence != SEEK_CUR && args->whence != SEEK_END) {
            zip_error_set(&s.error, ZIP_ER_INVAL, 0);
            return -1;
        }
        auto origin = args->whence == SEEK_SET ? io::SeekOrigin::Begin :
                      args->whence == SEEK_CUR ? io::SeekOrigin::Current : io::SeekOrigin::End;
        if (s.stream->seek(origin, args->offset)) return 0;
        break;
    }
    case ZIP_SOURCE_STAT: {
        if (length < sizeof(zip_stat_t)) return -1;
        auto* stat = static_cast<zip_stat_t*>(data);
        zip_stat_init(stat);
        stat->valid = ZIP_STAT_SIZE;
        stat->size = s.length;
        return sizeof(*stat);
    }
    case ZIP_SOURCE_ERROR: return zip_error_to_data(&s.error, data, length);
    case ZIP_SOURCE_SUPPORTS: return ZIP_SOURCE_SUPPORTS_SEEKABLE;
    case ZIP_SOURCE_CLOSE: return 0;
    case ZIP_SOURCE_FREE: delete &s; return 0;
    default: zip_error_set(&s.error, ZIP_ER_OPNOTSUPP, 0); return -1;
    }
    zip_error_set(&s.error, ZIP_ER_SEEK, 0);
    return -1;
}
}
zip_source_t* streamSource(io::StreamPtr input, uint64_t length, zip_error_t* error)
{
    auto context = std::make_unique<StreamSource>(std::move(input), length);
    auto* source = zip_source_function_create(sourceCall, context.get(), error);
    if (source) context.release();
    return source;
}
}
