#include "platform/PhysicalReadAdapter.h"
#include "platform/PosixFileStream.h"
#include <filesystem>

namespace cc
{
namespace fs = std::filesystem;
namespace {
std::string pathText(const fs::path& path) {
#ifdef _WIN32
    auto native = fs::path(path).make_preferred();
    const auto& spelling = native.native();
    auto bytes = spelling.starts_with(LR"(\\?\)") || spelling.starts_with(LR"(\\.\)")
        ? native.u8string() : native.generic_u8string();
#else
    auto bytes = path.generic_u8string();
#endif
    return {reinterpret_cast<const char*>(bytes.data()), bytes.size()};
}
io::StreamError pathError(std::error_code ec) {
    auto code = io::ErrorCode::IoError;
    if (ec == std::errc::permission_denied) code = io::ErrorCode::PermissionDenied;
    if (ec == std::errc::no_such_file_or_directory || ec == std::errc::not_a_directory) code = io::ErrorCode::NotFound;
    return {code, ec.value()};
}
}
PhysicalReadAdapter::PhysicalReadAdapter(std::string base, std::vector<std::string> roots, Lookup lookup)
    : _base(std::move(base)), _roots(std::move(roots)), _lookup(std::move(lookup)) {}
io::Result<AdapterPtr> PhysicalReadAdapter::withSearchPaths(const std::vector<std::string>& roots) const {
    for (const auto& root : roots)
        if (root.find('\0') != root.npos) return io::Result<AdapterPtr>::failure({io::ErrorCode::InvalidArgument});
    return io::Result<AdapterPtr>::success(std::make_shared<PhysicalReadAdapter>(_base, roots, _lookup));
}
io::Result<AdapterEntry> PhysicalReadAdapter::probe(std::string name, std::optional<size_t> root) const try {
    using Output = io::Result<AdapterEntry>;
    auto path = fs::u8path(name);
    if (_lookup && !path.has_root_directory()) {
        auto resolved = _lookup(name);
        if (resolved.empty()) return Output::failure({io::ErrorCode::NotFound});
        path = fs::u8path(resolved);
    }
    std::error_code ec;
    path = fs::absolute(path, ec);
    if (ec) return Output::failure(pathError(ec));
    if (!fs::is_regular_file(path, ec)) return Output::failure(ec ? pathError(ec) : io::StreamError{io::ErrorCode::NotFound});
    auto actual = pathText(path);
    auto canonical = fs::canonical(path, ec);
    if (ec) return Output::failure(pathError(ec));
    return Output::success({root, pathText(canonical), "filesystem", std::move(actual), {}});
}
catch (const fs::filesystem_error& error) { return io::Result<AdapterEntry>::failure(pathError(error.code())); }

io::Status PhysicalReadAdapter::visitFiles(ReadQuery q, const HitVisitor& emit) const try {
    if (q.kind == PathKind::AndroidAsset) return io::Status::success();
    const bool direct = q.kind == PathKind::NativeAbsolute;
    for (size_t i = 0; i < (direct ? 1 : _roots.size()); ++i) {
        auto name = fs::u8path(q.name);
        if (!direct) name = fs::u8path(_base) / fs::u8path(_roots[i]) / name;
        auto entry = probe(pathText(name), direct ? std::nullopt : std::optional<size_t>(i));
        if (entry && emit(entry.value) == Visit::Stop) break;
        if (!entry && entry.error.code != io::ErrorCode::NotFound) return io::Status::failure(entry.error);
    }
    return io::Status::success();
}
catch (const fs::filesystem_error& error) { return io::Status::failure(pathError(error.code())); }

io::Result<ReadFile> PhysicalReadAdapter::openEntry(const AdapterEntry& entry) const {
    auto stream = std::make_unique<PosixFileStream>();
    if (!entry.nativePath) return io::Result<ReadFile>::failure({io::ErrorCode::InvalidArgument});
    if (!stream->open(*entry.nativePath, FileStream::Mode::READ))
        return io::Result<ReadFile>::failure(pathError({errno, std::generic_category()}));
    return io::Result<ReadFile>::success(std::move(stream));
}
io::Result<AdapterEntry> PhysicalReadAdapter::findSibling(const AdapterEntry& entry, std::string_view name) const {
    if (!entry.nativePath || fs::u8path(name).has_root_path()) return io::Result<AdapterEntry>::failure({io::ErrorCode::InvalidArgument});
    return probe(pathText(fs::u8path(*entry.nativePath).parent_path() / fs::u8path(name)), entry.rootIndex);
}
}
