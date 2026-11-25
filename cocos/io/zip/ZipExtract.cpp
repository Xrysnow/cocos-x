#include "io/zip/ZipExtract.h"
#include "io/zip/detail/ZipSource.h"
#include "io/core/FileStream.h"
#include "platform/PosixFileStream.h"
#include <array>
#include <unordered_set>

namespace cc::archive
{
using namespace detail;
Status extractEntry(const ZipReader& reader, EntryId id, io::Stream& output, const ExtractOptions& options)
{
    auto opts = options.entry;
    opts.access = EntryAccess::Sequential;
    opts.maxBytes = std::min(opts.maxBytes, options.maxTotalBytes);
    auto input = reader.openEntry(id, opts);
    if (!input) return Status::failure(input.error);
    std::array<uint8_t, 64 * 1024> block;
    for (;;) {
        if (options.cancelled && options.cancelled()) return Status::failure({ErrorCode::Cancelled});
        auto r = input.value->read(block.data(), block.size());
        if (!r && r.status != io::IoStatus::EndOfStream) return Status::failure(r.error);
        if (r.transferred) {
            auto written = output.writeAll(block.data(), r.transferred);
            if (!written) return Status::failure(written.error ? written.error : StreamError{ErrorCode::IoError});
        }
        if (r.status == io::IoStatus::EndOfStream) return input.value->close();
        if (!r.transferred) return Status::failure({ErrorCode::NoProgress});
    }
}

Status extractTree(const ZipReader& reader, std::string_view target, const ExtractOptions& options)
{
    if (target.empty() || target.find('\0') != target.npos) return Status::failure({ErrorCode::InvalidArgument});
    if (reader.entries().size() > options.maxEntries) return Status::failure({ErrorCode::LimitExceeded});
    std::error_code ec;
    auto destination = fs::absolute(fs::u8path(target), ec);
    if (ec) return Status::failure(fileError(ec));
    if (fs::exists(destination, ec)) return Status::failure({ErrorCode::AlreadyExists});
    if (ec) return Status::failure(fileError(ec));
    auto temp = TemporaryDirectory::create(destination.parent_path());
    if (!temp) return Status::failure(temp.error);
    const auto root = temp.value->path / "contents";
    if (!fs::create_directory(root, ec)) return Status::failure(fileError(ec));
    uint64_t remaining = options.maxTotalBytes;
    std::unordered_set<std::string> entries, directories;
    for (const auto& info : reader.entries()) {
        if (options.cancelled && options.cancelled()) return Status::failure({ErrorCode::Cancelled});
        const bool dir = info.type == EntryType::Directory;
        if (!dir && info.type != EntryType::File) return Status::failure({ErrorCode::NotSupported});
        auto clean = cleanName(info.name, dir);
        if (!clean || clean.value != info.name || !entries.emplace(info.name).second)
            return Status::failure({ErrorCode::InvalidArgument});
        auto path = root;
        std::string key;
        std::string_view rest(info.name);
        while (!rest.empty()) {
            auto end = rest.find('/');
            auto part = rest.substr(0, end);
            if (!portableComponent(part)) return Status::failure({ErrorCode::InvalidArgument});
            path /= fs::u8path(part);
            if (end == rest.npos) break;
            key += part;
            key += '/';
            if (directories.insert(key).second && !fs::create_directory(path, ec))
                return Status::failure(ec ? fileError(ec) : StreamError{ErrorCode::AmbiguousEntry});
            rest.remove_prefix(end + 1);
        }
        if (dir) continue;
        if (!info.size || *info.size > remaining) return Status::failure({ErrorCode::LimitExceeded});
        auto backend = std::make_unique<PosixFileStream>();
        FileStream::Mode mode;
        FileStream::encodeOpenOptions({FileStream::Access::Write, FileStream::Creation::CreateNew, false}, mode);
        if (!backend->open(utf8(path), mode)) return Status::failure(fileError({errno, std::generic_category()}));
        auto out = io::FileStream::fromBackend(std::move(backend), {FileStream::Access::Write, FileStream::Creation::CreateNew, false});
        if (!out) return Status::failure(out.error);
        auto entryOptions = options;
        entryOptions.maxTotalBytes = remaining;
        auto done = extractEntry(reader, info.id, *out.value, entryOptions);
        if (!done) return done;
        auto length = out.value->tell();
        if (!length) return Status::failure(length.error);
        if (static_cast<uint64_t>(length.value) != *info.size) return Status::failure({ErrorCode::CorruptData});
        done = out.value->close();
        if (!done) return done;
        remaining -= *info.size;
    }
    return publish(root, destination, false);
}
}
