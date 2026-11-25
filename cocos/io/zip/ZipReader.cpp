#include "io/zip/ZipReader.h"
#include "io/zip/detail/ZipSource.h"
#include "io/core/FileStream.h"
#include "io/core/MemoryStream.h"
#include "platform/PosixFileStream.h"
#include <array>
#include <atomic>
#include <limits>
#include <unordered_map>

namespace cc::archive
{
using namespace detail;
struct ZipReader::State {
    zip_t* handle = nullptr;
    std::mutex mutex;
    std::shared_ptr<FileLease> lease;
    Bytes bytes;
    std::string name, password;
    uint64_t identity{};
    std::vector<ZipEntryInfo> entries;
    std::unordered_map<std::string, size_t> names;
    ~State() { if (handle) zip_discard(handle); }
};
namespace {
using ReaderResult = Result<ZipReader::Ptr>;
struct ZipError {
    zip_error_t error;
    ZipError() { zip_error_init(&error); }
    ~ZipError() { zip_error_fini(&error); }
    StreamError result() const { return zipError(zip_error_code_zip(&error)); }
};
Status openSource(ZipReader::State& state, zip_source_t* source, const ZipReadOptions& options, uint64_t length, ZipError& error)
{
    if (!source) return Status::failure(error.result());
    std::unique_ptr<zip_source_t, decltype(&zip_source_free)> owner(source, zip_source_free);
    bool strict = options.checkConsistency;
    if (options.password.find('\0') != options.password.npos) return Status::failure({ErrorCode::InvalidArgument});
    auto checked = checkDirectory(source, length, options, strict);
    if (!checked) return checked;
    state.handle = zip_open_from_source(source, ZIP_RDONLY | (strict ? ZIP_CHECKCONS : 0), &error.error);
    if (state.handle) { owner.release(); return Status::success(); }
    return Status::failure(error.result());
}

class EntryStream final : public io::Stream {
public:
    EntryStream(RefConstructionToken token, std::shared_ptr<ZipReader::State> state,
        zip_file_t* file, int64_t size, bool seekable)
        : Stream(token), _state(std::move(state)), _file(file), _size(size), _seekable(seekable) {}
    ~EntryStream() override { close(); }
    io::Capability capabilities() const noexcept override {
        if (!_file) return io::Capability::None;
        return _seekable ? io::Capability::Read | io::Capability::Seek : io::Capability::Read;
    }
    bool isOpen() const noexcept override { return _file != nullptr; }
    io::IoResult read(void* output, size_t length) override {
        if (!_file) return io::IoResult::failure({ErrorCode::Closed});
        if (!length) return io::IoResult::success(0);
        if (!output) return io::IoResult::failure({ErrorCode::InvalidArgument});
        std::lock_guard lock(_state->mutex);
        // Even at the advertised end, read through EOF to validate the trailer.
        uint8_t tail{};
        const bool atEnd = _position == _size;
        auto count = zip_fread(_file, atEnd ? &tail : output, atEnd ? 1 :
            std::min<uint64_t>(length, _size - _position));
        if (count < 0) return io::IoResult::failure(zipError(zip_error_code_zip(zip_file_get_error(_file))));
        if (atEnd && count == 0) return {0, io::IoStatus::EndOfStream, {}};
        if (atEnd || !count) return io::IoResult::failure({ErrorCode::CorruptData});
        _position += count;
        return io::IoResult::success(static_cast<size_t>(count));
    }
    Result<int64_t> tell() const override {
        return _file ? Result<int64_t>::success(_position) : Result<int64_t>::failure({ErrorCode::Closed});
    }
    Result<std::optional<int64_t>> size() const override {
        return _file ? Result<std::optional<int64_t>>::success(_size) :
                       Result<std::optional<int64_t>>::failure({ErrorCode::Closed});
    }
    Status seek(io::SeekOrigin origin, int64_t offset) override {
        if (!_file) return Status::failure({ErrorCode::Closed});
        if (!_seekable) return Status::failure({ErrorCode::NotSupported});
        auto target = io::detail::seekTarget(origin, offset, _position, _size, false);
        if (!target) return Status::failure(target.error);
        std::lock_guard lock(_state->mutex);
        if (zip_fseek(_file, target.value, SEEK_SET) < 0)
            return Status::failure(zipError(zip_error_code_zip(zip_file_get_error(_file))));
        _position = target.value;
        return Status::success();
    }
    Status close() override {
        if (_file) {
            auto state = std::move(_state);
            std::lock_guard lock(state->mutex);
            int code = zip_fclose(std::exchange(_file, nullptr));
            if (code) _closeResult = Status::failure(zipError(code));
        }
        return _closeResult;
    }
private:
    std::shared_ptr<ZipReader::State> _state;
    zip_file_t* _file;
    int64_t _position = 0, _size;
    bool _seekable;
    Status _closeResult{};
};
class TempReadFile final : public PosixFileStream {
public:
    std::shared_ptr<TemporaryDirectory> directory;
    ~TempReadFile() override { if (isOpen()) close(); }
};
Status drain(io::Stream& stream, cc::FileStream* file)
{
    std::array<uint8_t, 64 * 1024> buffer;
    for (;;) {
        auto r = stream.read(buffer.data(), buffer.size());
        if (!r && r.status != io::IoStatus::EndOfStream) return Status::failure(r.error);
        if (file) {
            size_t offset = 0;
            while (offset < r.transferred) {
                int n = file->write(buffer.data() + offset, static_cast<unsigned>(r.transferred - offset));
                if (n <= 0) return Status::failure({ErrorCode::IoError});
                offset += static_cast<size_t>(n);
            }
        }
        if (r.status == io::IoStatus::EndOfStream) return stream.close();
        if (!r.transferred) return Status::failure({ErrorCode::NoProgress});
    }
}
}

ReaderResult ZipReader::openFile(std::string_view path, const ZipReadOptions& options)
{
    auto lease = acquire(path, false);
    if (!lease) return ReaderResult::failure(lease.error);
    auto state = std::make_shared<State>();
    state->lease = std::move(lease.value);
    state->name = utf8(state->lease->path);
    std::error_code ec;
    auto length = fs::file_size(state->lease->path, ec);
    if (ec) return ReaderResult::failure(fileError(ec));
    if (length > options.maxArchiveBytes) return ReaderResult::failure({ErrorCode::LimitExceeded});
    ZipError error;
#ifdef _WIN32
    auto* source = zip_source_win32w_create(state->lease->path.c_str(), 0, ZIP_LENGTH_TO_END, &error.error);
#else
    auto* source = zip_source_file_create(state->lease->path.c_str(), 0, ZIP_LENGTH_TO_END, &error.error);
#endif
    auto status = openSource(*state, source, options, length, error);
    return status ? index(std::move(state), options) : ReaderResult::failure(status.error);
}
ReaderResult ZipReader::openBuffer(Bytes bytes, const ZipReadOptions& options)
{
    if (!bytes || bytes->empty()) return ReaderResult::failure({ErrorCode::CorruptData});
    if (bytes->size() > options.maxArchiveBytes) return ReaderResult::failure({ErrorCode::LimitExceeded});
    auto state = std::make_shared<State>();
    state->bytes = std::move(bytes);
    state->name = "<memory>";
    ZipError error;
    auto* source = zip_source_buffer_create(state->bytes->data(), state->bytes->size(), 0, &error.error);
    auto status = openSource(*state, source, options, state->bytes->size(), error);
    return status ? index(std::move(state), options) : ReaderResult::failure(status.error);
}
ReaderResult ZipReader::openStream(io::StreamPtr stream, const ZipReadOptions& options)
{
    if (!stream || !io::hasCapability(stream->capabilities(), io::Capability::Read | io::Capability::Seek))
        return ReaderResult::failure({ErrorCode::NotSupported});
    auto size = stream->size();
    if (!size) return ReaderResult::failure(size.error);
    if (!size.value || *size.value < 0) return ReaderResult::failure({ErrorCode::NotSupported});
    if (static_cast<uint64_t>(*size.value) > options.maxArchiveBytes) return ReaderResult::failure({ErrorCode::LimitExceeded});
    auto state = std::make_shared<State>();
    state->name = "<stream>";
    ZipError error;
    auto status = openSource(*state, streamSource(std::move(stream), *size.value, &error.error), options, *size.value, error);
    return status ? index(std::move(state), options) : ReaderResult::failure(status.error);
}

ReaderResult ZipReader::index(std::shared_ptr<State> state, const ZipReadOptions& options) try
{
    static std::atomic<uint64_t> identity{};
    state->identity = ++identity;
    state->password = options.password;
    auto count = zip_get_num_entries(state->handle, 0);
    if (count < 0) return ReaderResult::failure(zipError(zip_error_code_zip(zip_get_error(state->handle))));
    if (static_cast<uint64_t>(count) > options.maxEntries ||
        static_cast<uint64_t>(count) > options.maxIndexBytes / sizeof(ZipEntryInfo))
        return ReaderResult::failure({ErrorCode::LimitExceeded});
    state->entries.reserve(static_cast<size_t>(count));
    uint64_t nameBudget = options.maxIndexBytes - static_cast<uint64_t>(count) * sizeof(ZipEntryInfo);
    for (zip_int64_t i = 0; i < count; ++i) {
        zip_stat_t stat;
        zip_stat_init(&stat);
        if (zip_stat_index(state->handle, i, 0, &stat) < 0 || !(stat.valid & ZIP_STAT_NAME))
            return ReaderResult::failure({ErrorCode::CorruptData});
        ZipEntryInfo info;
        auto name = std::string_view(stat.name);
        if (name.size() > nameBudget / 2) return ReaderResult::failure({ErrorCode::LimitExceeded});
        nameBudget -= name.size() * 2;
        info.name = name;
        info.id = {state->identity, static_cast<uint64_t>(i)};
        if (stat.valid & ZIP_STAT_SIZE) info.size = stat.size;
        if (stat.valid & ZIP_STAT_COMP_SIZE) info.compressedSize = stat.comp_size;
        if (stat.valid & ZIP_STAT_CRC) info.crc = stat.crc;
        if (stat.valid & ZIP_STAT_MTIME) info.modified = stat.mtime;
        if (stat.valid & ZIP_STAT_COMP_METHOD) info.compression = stat.comp_method;
        if (stat.valid & ZIP_STAT_ENCRYPTION_METHOD) info.encryption = stat.encryption_method;
        info.type = name.ends_with('/') ? EntryType::Directory : EntryType::File;
        zip_uint8_t os;
        zip_uint32_t attr;
        if (zip_file_get_external_attributes(state->handle, i, 0, &os, &attr) == 0) {
            info.hostSystem = os;
            info.externalAttributes = attr;
        }
        if (info.hostSystem == ZIP_OPSYS_UNIX) {
            switch ((attr >> 16) & 0170000) {
            case 0: case 0100000: break;
            case 0040000: info.type = EntryType::Directory; break;
            case 0120000: info.type = EntryType::Link; break;
            default: info.type = EntryType::Other;
            }
        }
        auto [it, inserted] = state->names.emplace(info.name, static_cast<size_t>(i));
        if (!inserted) it->second = SIZE_MAX;
        state->entries.push_back(std::move(info));
    }
    return ReaderResult::success(Ptr(new ZipReader(std::move(state))));
}
catch (const std::bad_alloc&) { return ReaderResult::failure({ErrorCode::OutOfMemory}); }

std::span<const ZipEntryInfo> ZipReader::entries() const { return _state->entries; }
const std::string& ZipReader::sourceName() const { return _state->name; }
Result<EntryId> ZipReader::find(std::string_view name) const
{
    auto it = _state->names.find(std::string(name));
    if (it == _state->names.end()) return Result<EntryId>::failure({ErrorCode::NotFound});
    if (it->second == SIZE_MAX) return Result<EntryId>::failure({ErrorCode::AmbiguousEntry});
    return Result<EntryId>::success(_state->entries[it->second].id);
}

Result<io::StreamPtr> ZipReader::openEntry(EntryId id, const EntryReadOptions& options) const
{
    using Output = Result<io::StreamPtr>;
    if (id.archive != _state->identity || id.index >= _state->entries.size())
        return Output::failure({ErrorCode::InvalidArgument});
    const auto& entry = _state->entries[static_cast<size_t>(id.index)];
    if (entry.type != EntryType::File || !entry.size) return Output::failure({ErrorCode::NotSupported});
    if (*entry.size > options.maxBytes || *entry.size > INT64_MAX) return Output::failure({ErrorCode::LimitExceeded});
    const auto& pass = options.password ? *options.password : _state->password;
    if (pass.find('\0') != pass.npos) return Output::failure({ErrorCode::InvalidArgument});
    io::StreamPtr stream;
    {
        std::lock_guard lock(_state->mutex);
        auto* file = zip_fopen_index_encrypted(_state->handle, id.index, 0, pass.empty() ? nullptr : pass.c_str());
        if (!file) return Output::failure(zipError(zip_error_code_zip(zip_get_error(_state->handle))));
        try {
            stream = makeThreadSafeRef<EntryStream>(_state, file, static_cast<int64_t>(*entry.size),
                                                     zip_file_is_seekable(file) == 1);
        } catch (const std::bad_alloc&) {
            zip_fclose(file);
            return Output::failure({ErrorCode::OutOfMemory});
        }
    }
    if (options.access == EntryAccess::Sequential || io::hasCapability(stream->capabilities(), io::Capability::Seek))
        return Output::success(std::move(stream));
    if (*entry.size <= options.maxMemoryBytes && *entry.size <= SIZE_MAX) {
        auto data = stream->readAll(static_cast<size_t>(*entry.size));
        if (!data) return Output::failure(data.error);
        auto done = drain(*stream, nullptr);
        if (!done) return Output::failure(done.error);
        auto memory = io::MemoryStream::move(std::move(data.value), false);
        return memory ? Output::success(std::move(memory.value)) : Output::failure(memory.error);
    }
    if (options.temporaryDirectory.empty()) return Output::failure({ErrorCode::LimitExceeded});
    auto temp = TemporaryDirectory::create(fs::u8path(options.temporaryDirectory));
    if (!temp) return Output::failure(temp.error);
    const auto path = utf8(temp.value->path / "entry");
    PosixFileStream out;
    if (!out.open(path, FileStream::Mode::WRITE)) return Output::failure(fileError({errno, std::generic_category()}));
    auto status = drain(*stream, &out);
    if (!status) return Output::failure(status.error);
    if (out.close() != 0) return Output::failure({ErrorCode::IoError});
    auto file = std::make_unique<TempReadFile>();
    file->directory = std::move(temp.value);
    if (!file->open(path, FileStream::Mode::READ)) return Output::failure({ErrorCode::IoError});
    auto result = io::FileStream::fromBackend(std::move(file));
    return result ? Output::success(std::move(result.value)) : Output::failure(result.error);
}

Result<Bytes> ZipReader::readEntry(EntryId id, const EntryReadOptions& options) const try
{
    auto sequential = options;
    sequential.access = EntryAccess::Sequential;
    sequential.maxBytes = std::min(options.maxBytes, options.maxMemoryBytes);
    auto stream = openEntry(id, sequential);
    if (!stream) return Result<Bytes>::failure(stream.error);
    auto bytes = stream.value->readAll(static_cast<size_t>(std::min<uint64_t>(sequential.maxBytes, SIZE_MAX)));
    if (!bytes) return Result<Bytes>::failure(bytes.error);
    auto status = drain(*stream.value, nullptr);
    if (!status) return Result<Bytes>::failure(status.error);
    return Result<Bytes>::success(std::make_shared<const std::vector<uint8_t>>(std::move(bytes.value)));
}
catch (const std::bad_alloc&) { return Result<Bytes>::failure({ErrorCode::OutOfMemory}); }

Status ZipReader::verify(EntryId id, const EntryReadOptions& options) const
{
    auto sequential = options;
    sequential.access = EntryAccess::Sequential;
    auto stream = openEntry(id, sequential);
    return stream ? drain(*stream.value, nullptr) : Status::failure(stream.error);
}
}
