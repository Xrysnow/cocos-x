#pragma once
#include "io/core/Stream.h"
#include "platform/FileStream.h"
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <vector>

namespace cc
{
using AdapterId = uint64_t;
class FileReadAdapter;
using AdapterPtr = std::shared_ptr<const FileReadAdapter>;
using ReadFile = std::unique_ptr<FileStream>;
CC_DLL io::Result<ReadFile> readFileFromStream(io::StreamPtr stream);
enum class PathKind { Logical, NativeAbsolute, AndroidAsset };
struct ReadQuery { PathKind kind; std::string_view name; };
struct AdapterEntry {
    std::optional<size_t> rootIndex;
    std::string entryKey;
    std::string source;
    std::optional<std::string> nativePath;
    std::optional<int64_t> sizeHint;
};
enum class Visit { Next, Stop };
using HitVisitor = std::function<Visit(const AdapterEntry&)>;
class CC_DLL FileReadAdapter {
public:
    virtual ~FileReadAdapter() = default;
    virtual std::string_view kind() const noexcept = 0;
    virtual std::span<const std::string> searchPaths() const = 0;
    virtual io::Result<AdapterPtr> withSearchPaths(const std::vector<std::string>& roots) const = 0;
    virtual io::Status visitFiles(ReadQuery query, const HitVisitor& emit) const = 0;
    virtual io::Result<ReadFile> openEntry(const AdapterEntry& entry) const = 0;
    virtual io::Result<AdapterEntry> findSibling(const AdapterEntry&, std::string_view) const {
        return io::Result<AdapterEntry>::failure({io::ErrorCode::NotSupported});
    }
};
struct AdapterInfo {
    AdapterId id{};
    std::string name, kind;
    float priority{};
    std::vector<std::string> roots;
};
class CC_DLL FileHit {
public:
    AdapterId adapterId() const noexcept { return _id; }
    std::string_view kind() const noexcept { return _adapter ? _adapter->kind() : std::string_view{}; }
    const std::string& name() const noexcept { return _name; }
    float priority() const noexcept { return _priority; }
    const AdapterEntry& entry() const noexcept { return _entry; }
    const AdapterPtr& adapter() const noexcept { return _adapter; }
    std::string_view root() const noexcept {
        return _adapter && _entry.rootIndex ? _adapter->searchPaths()[*_entry.rootIndex] : std::string_view{};
    }
private:
    friend class FileUtils;
    AdapterId _id{};
    AdapterPtr _adapter;
    AdapterEntry _entry;
    std::string _name;
    float _priority{};
};
}
