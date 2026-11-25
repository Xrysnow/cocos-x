#include "io/zip/ZipWriter.h"
#include "io/zip/detail/ZipSource.h"
#include "io/core/FileStream.h"
#include "platform/PosixFileStream.h"
#include <algorithm>
#include <array>
#include <set>

namespace cc::archive
{
using namespace detail;
namespace {
Status archiveFailure(zip_t* handle) { return Status::failure(zipError(zip_error_code_zip(zip_get_error(handle)))); }

Status validOptions(const EntryWriteOptions& opts)
{
    if (opts.level > 9 || opts.password.find('\0') != opts.password.npos)
        return Status::failure({ErrorCode::InvalidArgument});
    if (!zip_compression_method_supported(static_cast<int>(opts.compression), 1) ||
        !zip_encryption_method_supported(static_cast<uint16_t>(opts.encryption), 1))
        return Status::failure({ErrorCode::NotSupported});
    if (opts.encryption != Encryption::None && opts.password.empty())
        return Status::failure({ErrorCode::CredentialsRequired});
    return Status::success();
}
Result<std::string> writeName(std::string_view name)
{
    auto clean = cleanName(name, name.ends_with('/'));
    if (!clean || clean.value != name || name.size() > UINT16_MAX)
        return Result<std::string>::failure({ErrorCode::InvalidArgument});
    return clean;
}
}
struct ZipWriter::State {
    std::shared_ptr<FileLease> lease;
    std::shared_ptr<TemporaryDirectory> temp;
    fs::path archive;
    zip_t* handle = nullptr;
    WriteIntent intent;
    std::vector<Bytes> retained;
    uint64_t budget{}, staged{}, serial{};
    bool poisoned = false;
    ~State() { if (handle) zip_discard(handle); }
    bool writable() const { return handle && !poisoned; }
    std::set<std::string, std::less<>> names;

    Status available(const std::string& name, bool replace = false) const {
        if (names.contains(name))
            return replace ? Status::success() : Status::failure({ErrorCode::AlreadyExists});
        if (replace) return Status::failure({ErrorCode::NotFound});
        for (auto i = name.find('/'); i != name.npos; i = name.find('/', i + 1))
            if (names.contains(std::string_view(name).substr(0, i)))
                return Status::failure({ErrorCode::AmbiguousEntry});
        if (name.back() != '/') {
            const auto prefix = name + '/';
            auto next = names.lower_bound(prefix);
            if (next != names.end() && next->starts_with(prefix))
                return Status::failure({ErrorCode::AmbiguousEntry});
        }
        return Status::success();
    }
    Status options(zip_int64_t id, const EntryWriteOptions& opts) {
        if (zip_set_file_compression(handle, id, static_cast<int>(opts.compression), opts.level) < 0 ||
            zip_file_set_encryption(handle, id, static_cast<uint16_t>(opts.encryption),
                                    opts.password.empty() ? nullptr : opts.password.c_str()) < 0) {
            poisoned = true;
            return archiveFailure(handle);
        }
        return Status::success();
    }
    Status attach(const std::string& name, zip_source_t* source, bool replace, const EntryWriteOptions& opts) {
        if (!source) return archiveFailure(handle);
        zip_int64_t id;
        if (replace) {
            id = zip_name_locate(handle, name.c_str(), 0);
            if (id >= 0 && zip_file_replace(handle, id, source, 0) < 0) id = -1;
        } else {
            id = zip_file_add(handle, name.c_str(), source, ZIP_FL_ENC_UTF_8);
        }
        if (id < 0) {
            zip_source_free(source);
            return archiveFailure(handle);
        }
        names.insert(name);
        return options(id, opts);
    }
};
ZipWriter::ZipWriter(std::unique_ptr<State> state) : _state(std::move(state)) {}
ZipWriter::~ZipWriter() = default;
Result<ZipWriter::Ptr> ZipWriter::begin(std::string_view path, WriteIntent intent, const ZipWriteOptions& opts)
{
    using Output = Result<Ptr>;
    auto lease = acquire(path, true);
    if (!lease) return Output::failure(lease.error);
    auto state = std::make_unique<State>();
    state->intent = intent;
    state->lease = std::move(lease.value);
    state->budget = opts.maxStagedBytes;
    auto& target = state->lease->path;
    std::error_code ec;
    const bool exists = fs::exists(target, ec);
    if (ec) return Output::failure(fileError(ec));
    if (exists && intent == WriteIntent::CreateNew) return Output::failure({ErrorCode::AlreadyExists});
    if (!exists && intent == WriteIntent::UpdateExisting) return Output::failure({ErrorCode::NotFound});
    if (exists && !fs::is_regular_file(target, ec)) return Output::failure({ErrorCode::InvalidArgument});
    auto temp = TemporaryDirectory::create(target.parent_path());
    if (!temp) return Output::failure(temp.error);
    state->temp = std::move(temp.value);
    state->archive = state->temp->path / "archive.zip";
    int flags = ZIP_CREATE | ZIP_EXCL;
    if (intent == WriteIntent::UpdateExisting) {
        auto size = fs::file_size(target, ec);
        if (ec) return Output::failure(fileError(ec));
        if (size > state->budget) return Output::failure({ErrorCode::LimitExceeded});
        if (!fs::copy_file(target, state->archive, ec)) return Output::failure(fileError(ec));
        state->staged = size;
        flags = 0;
    }
    int error = 0;
    state->handle = zip_open(utf8(state->archive).c_str(), flags, &error);
    if (!state->handle) return Output::failure(zipError(error));
    if (zip_set_archive_flag(state->handle, ZIP_AFL_CREATE_OR_KEEP_FILE_FOR_EMPTY_ARCHIVE, 1) < 0)
        return Output::failure(archiveFailure(state->handle).error);
    const auto count = zip_get_num_entries(state->handle, 0);
    if (count < 0) return Output::failure(archiveFailure(state->handle).error);
    for (zip_int64_t i = 0; i < count; ++i) {
        auto name = zip_get_name(state->handle, i, 0);
        if (!name || !writeName(name)) return Output::failure({ErrorCode::InvalidArgument});
        auto valid = state->available(name);
        if (!valid) return Output::failure(valid.error);
        state->names.insert(name);
    }
    return Output::success(Ptr(new ZipWriter(std::move(state))));
}
Status ZipWriter::putBytes(std::string_view name, Bytes bytes, bool replace, const EntryWriteOptions& opts)
{
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto clean = writeName(name);
    if (!clean || name.ends_with('/') || !bytes) return Status::failure({ErrorCode::InvalidArgument});
    auto valid = validOptions(opts);
    if (!valid) return valid;
    auto available = _state->available(clean.value, replace);
    if (!available) return available;
    if (bytes->size() > _state->budget - _state->staged) return Status::failure({ErrorCode::LimitExceeded});
    _state->retained.push_back(bytes);
    auto* source = zip_source_buffer(_state->handle, bytes->data(), bytes->size(), 0);
    auto result = _state->attach(clean.value, source, replace, opts);
    if (result || _state->poisoned) _state->staged += bytes->size();
    else _state->retained.pop_back();
    return result;
}
Status ZipWriter::add(std::string_view name, Bytes bytes, const EntryWriteOptions& opts) {
    return putBytes(name, std::move(bytes), false, opts);
}
Status ZipWriter::replace(std::string_view name, Bytes bytes, const EntryWriteOptions& opts) {
    return putBytes(name, std::move(bytes), true, opts);
}
Status ZipWriter::addFile(std::string_view name, std::string_view path, const EntryWriteOptions& opts)
{
    if (path.empty() || path.find('\0') != path.npos) return Status::failure({ErrorCode::InvalidArgument});
    auto file = std::make_unique<PosixFileStream>();
    if (!file->open(path, FileStream::Mode::READ)) return Status::failure(fileError({errno, std::generic_category()}));
    auto input = io::FileStream::fromBackend(std::move(file));
    return input ? addStream(name, *input.value, opts) : Status::failure(input.error);
}
Status ZipWriter::addStream(std::string_view name, io::Stream& input, const EntryWriteOptions& opts)
{
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto clean = writeName(name);
    if (!clean || name.ends_with('/')) return Status::failure({ErrorCode::InvalidArgument});
    auto valid = validOptions(opts);
    if (!valid) return valid;
    auto available = _state->available(clean.value);
    if (!available) return available;
    struct Spool {
        fs::path path;
        bool retained = false;
        ~Spool() { if (!retained) { std::error_code ec; fs::remove(path, ec); } }
    } spool{_state->temp->path / std::to_string(++_state->serial)};
    const auto path = utf8(spool.path);
    uint64_t written = 0;
    PosixFileStream out;
    if (!out.open(path, FileStream::Mode::WRITE)) return Status::failure(fileError({errno, std::generic_category()}));
    std::array<uint8_t, 64 * 1024> block;
    for (;;) {
        auto r = input.read(block.data(), block.size());
        if (!r && r.status != io::IoStatus::EndOfStream)
            return Status::failure(r.error ? r.error : StreamError{ErrorCode::IoError});
        if (r.transferred > block.size()) return Status::failure({ErrorCode::InvalidBackend});
        if (r.transferred > _state->budget - _state->staged - written) return Status::failure({ErrorCode::LimitExceeded});
        if (out.write(block.data(), static_cast<unsigned>(r.transferred)) != static_cast<int>(r.transferred))
            return Status::failure({ErrorCode::IoError});
        written += r.transferred;
        if (r.status == io::IoStatus::EndOfStream) break;
        if (!r.transferred) return Status::failure({ErrorCode::NoProgress});
    }
    if (out.close() < 0) return Status::failure({ErrorCode::IoError});
    auto status = _state->attach(clean.value, zip_source_file(_state->handle, path.c_str(), 0, ZIP_LENGTH_TO_END), false, opts);
    if (status || _state->poisoned) {
        spool.retained = true;
        _state->staged += written;
    }
    return status;
}
Status ZipWriter::addDirectory(std::string_view name)
{
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto clean = writeName(name);
    if (!clean || !name.ends_with('/')) return Status::failure({ErrorCode::InvalidArgument});
    auto available = _state->available(clean.value);
    if (!available) return available;
    if (zip_dir_add(_state->handle, clean.value.c_str(), ZIP_FL_ENC_UTF_8) < 0) return archiveFailure(_state->handle);
    _state->names.insert(clean.value);
    return Status::success();
}
namespace {
Result<zip_int64_t> editable(zip_t* handle, std::string_view name)
{
    auto clean = writeName(name);
    if (!clean) return Result<zip_int64_t>::failure(clean.error);
    const auto id = zip_name_locate(handle, clean.value.c_str(), 0);
    if (id < 0) return Result<zip_int64_t>::failure(archiveFailure(handle).error);
    if (name.ends_with('/')) {
        const auto n = zip_get_num_entries(handle, 0);
        for (zip_int64_t i = 0; i < n; ++i) {
            auto other = zip_get_name(handle, i, 0);
            if (i != id && other && std::string_view(other).starts_with(name))
                return Result<zip_int64_t>::failure({ErrorCode::Busy});
        }
    }
    return Result<zip_int64_t>::success(id);
}
}
Status ZipWriter::rename(std::string_view from, std::string_view to) {
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto name = writeName(to);
    if (!name || from.ends_with('/') != to.ends_with('/')) return Status::failure({ErrorCode::InvalidArgument});
    auto id = editable(_state->handle, from);
    if (!id) return Status::failure(id.error);
    if (from == to) return Status::success();
    auto available = _state->available(name.value);
    if (!available) return available;
    if (zip_file_rename(_state->handle, id.value, name.value.c_str(), ZIP_FL_ENC_UTF_8) != 0)
        return archiveFailure(_state->handle);
    _state->names.erase(std::string(from));
    _state->names.insert(name.value);
    return Status::success();
}
Status ZipWriter::remove(std::string_view name) {
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto id = editable(_state->handle, name);
    if (!id) return Status::failure(id.error);
    if (zip_delete(_state->handle, id.value) != 0) return archiveFailure(_state->handle);
    _state->names.erase(std::string(name));
    return Status::success();
}
Status ZipWriter::setArchiveComment(std::string_view comment) {
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    if (comment.size() > UINT16_MAX) return Status::failure({ErrorCode::Overflow});
    return zip_set_archive_comment(_state->handle, comment.data(), static_cast<uint16_t>(comment.size())) == 0 ?
        Status::success() : archiveFailure(_state->handle);
}
Status ZipWriter::setEntryComment(std::string_view name, std::string_view comment) {
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    if (comment.size() > UINT16_MAX || !writeName(name)) return Status::failure({ErrorCode::InvalidArgument});
    auto id = zip_name_locate(_state->handle, std::string(name).c_str(), 0);
    if (id < 0) return archiveFailure(_state->handle);
    return zip_file_set_comment(_state->handle, id, comment.data(), static_cast<uint16_t>(comment.size()), ZIP_FL_ENC_UTF_8) == 0 ?
        Status::success() : archiveFailure(_state->handle);
}
Status ZipWriter::setEntryOptions(std::string_view name, const EntryWriteOptions& opts) {
    if (!_state || !_state->writable()) return Status::failure({ErrorCode::Closed});
    auto valid = validOptions(opts);
    if (!valid) return valid;
    auto id = editable(_state->handle, name);
    return id ? _state->options(id.value, opts) : Status::failure(id.error);
}
Status ZipWriter::commit()
{
    if (!_state || _state->poisoned) return Status::failure({ErrorCode::Closed});
    if (_state->handle) {
        if (zip_close(_state->handle) < 0) return archiveFailure(_state->handle);
        _state->handle = nullptr;
    }
    auto status = publish(_state->archive, _state->lease->path, _state->intent != WriteIntent::CreateNew);
    if (status) _state.reset();
    return status;
}
void ZipWriter::discard() noexcept { _state.reset(); }

ZipCapabilities zipCapabilities()
{
    ZipCapabilities result;
    for (auto method : {Compression::Store, Compression::Deflate, Compression::Bzip2, Compression::Xz, Compression::Zstd}) {
        if (zip_compression_method_supported(static_cast<int>(method), 0)) result.readCompression.push_back(method);
        if (zip_compression_method_supported(static_cast<int>(method), 1)) result.writeCompression.push_back(method);
    }
    for (auto method : {Encryption::None, Encryption::Traditional, Encryption::Aes128, Encryption::Aes192, Encryption::Aes256}) {
        if (zip_encryption_method_supported(static_cast<uint16_t>(method), 0)) result.readEncryption.push_back(method);
        if (zip_encryption_method_supported(static_cast<uint16_t>(method), 1)) result.writeEncryption.push_back(method);
    }
    return result;
}
}
