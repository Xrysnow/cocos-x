#include "platform/FileUtils.h"
#include "platform/PhysicalReadAdapter.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <unordered_set>

namespace cc
{
using io::Result;
using io::ErrorCode;
namespace {
std::atomic<AdapterId> nextAdapterId{};
bool validName(std::string_view name) { return !name.empty() && name.find('\0') == name.npos; }
}
void FileUtils::publishMounts(Mounts mounts)
{
    std::sort(mounts.begin(), mounts.end(), [](const auto& a, const auto& b) {
        return a.priority != b.priority ? a.priority > b.priority : a.id > b.id;
    });
    _mounts = std::make_shared<const Mounts>(std::move(mounts));
}
Result<AdapterId> FileUtils::registerReadAdapter(std::string name, AdapterPtr adapter, float priority)
{
    return replaceReadAdapter(0, std::move(name), std::move(adapter), priority);
}
Result<AdapterId> FileUtils::replaceReadAdapter(AdapterId id, std::string name, AdapterPtr adapter, float priority)
{
    using Output = Result<AdapterId>;
    if (!validName(name) || !adapter || !std::isfinite(priority)) return Output::failure({ErrorCode::InvalidArgument});
    // Keep the previous adapters alive until after releasing the registry lock.
    std::shared_ptr<const Mounts> previous;
    std::lock_guard lock(_mutex);
    previous = _mounts;
    Mounts next = *previous;
    if (id && (id == _physicalId || id == _packageId)) return Output::failure({ErrorCode::PermissionDenied});
    if (id && !std::erase_if(next, [id](const auto& m){ return m.id == id; }))
        return Output::failure({ErrorCode::NotFound});
    if (std::any_of(next.begin(), next.end(), [&](const auto& m) { return m.name == name; }))
        return Output::failure({ErrorCode::AlreadyExists});
    auto newId = ++nextAdapterId;
    next.push_back({newId, std::move(name), std::move(adapter), priority});
    publishMounts(std::move(next));
    return Output::success(newId);
}
io::Status FileUtils::unregisterReadAdapter(AdapterId id)
{
    // Keep the previous adapters alive until after releasing the registry lock.
    std::shared_ptr<const Mounts> previous;
    std::lock_guard lock(_mutex);
    previous = _mounts;
    Mounts next = *previous;
    if (!std::erase_if(next, [id](const auto& m){ return m.id == id; })) return io::Status::failure({ErrorCode::NotFound});
    publishMounts(std::move(next));
    if (id == _physicalId || id == _packageId) {
        if (id == _physicalId) _physicalId = 0;
        if (id == _packageId) _packageId = 0;
        syncDirectoryRoots();
    }
    return io::Status::success();
}
io::Status FileUtils::setAdapterPriority(AdapterId id, float priority)
{
    if (!std::isfinite(priority)) return io::Status::failure({ErrorCode::InvalidArgument});
    std::lock_guard lock(_mutex);
    Mounts next = *_mounts;
    for (auto& m : next) if (m.id == id) {
        m.priority = priority;
        publishMounts(std::move(next));
        if (id == _physicalId || id == _packageId) syncDirectoryRoots();
        return io::Status::success();
    }
    return io::Status::failure({ErrorCode::NotFound});
}
io::Status FileUtils::setAdapterSearchPaths(AdapterId id, const std::vector<std::string>& roots)
{
    return updateAdapterSearchPaths(id, [&](const FileReadAdapter& adapter) {
        return adapter.withSearchPaths(roots);
    });
}
io::Status FileUtils::updateAdapterSearchPaths(AdapterId id,
    const std::function<io::Result<AdapterPtr>(const FileReadAdapter&)>& update)
{
    for (;;) {
        AdapterPtr original;
        {
            std::lock_guard lock(_mutex);
            auto mount = std::find_if(_mounts->begin(), _mounts->end(), [id](const auto& m) { return m.id == id; });
            if (mount == _mounts->end()) return io::Status::failure({ErrorCode::NotFound});
            original = mount->adapter;
        }
        auto updated = update(*original);
        if (!updated || !updated.value)
            return io::Status::failure(updated ? io::StreamError{ErrorCode::InvalidBackend} : updated.error);

        std::lock_guard lock(_mutex);
        Mounts next = *_mounts;
        auto mount = std::find_if(next.begin(), next.end(), [id](const auto& m) { return m.id == id; });
        if (mount == next.end()) return io::Status::failure({ErrorCode::NotFound});
        if (mount->adapter != original) continue;
        mount->adapter = std::move(updated.value);
        publishMounts(std::move(next));
        if (id == _physicalId || id == _packageId) syncDirectoryRoots();
        return io::Status::success();
    }
}
io::Status FileUtils::addAdapterSearchPath(AdapterId id, std::string root, bool front)
{
    return updateAdapterSearchPaths(id, [&](const FileReadAdapter& adapter) {
        auto view = adapter.searchPaths();
        std::vector<std::string> roots(view.begin(), view.end());
        roots.insert(front ? roots.begin() : roots.end(), root);
        return adapter.withSearchPaths(roots);
    });
}
std::vector<AdapterInfo> FileUtils::getReadAdapters() const
{
    std::shared_ptr<const Mounts> snapshot;
    { std::lock_guard lock(_mutex); snapshot = _mounts; }
    std::vector<AdapterInfo> result;
    for (auto& m : *snapshot) {
        auto roots = m.adapter->searchPaths();
        result.push_back({m.id, m.name, std::string(m.adapter->kind()), m.priority, {roots.begin(), roots.end()}});
    }
    return result;
}
io::Status FileUtils::visitHits(std::string_view path, AdapterId only, bool platformOnly,
                            const std::function<Visit(FileHit)>& visitor) const
{
    if (!validName(path)) return io::Status::failure({ErrorCode::InvalidArgument});
    PathKind kind = PathKind::Logical;
    std::string normalized;
#ifdef _WIN32
    normalized.assign(path);
    std::replace(normalized.begin(), normalized.end(), '\\', '/');
    path = normalized;
    if (path.size() >= 2 && path[1] == ':' && (path.size() == 2 || path[2] != '/'))
        return io::Status::failure({ErrorCode::InvalidArgument});
#endif
    if (isAbsolutePathInternal(path)) kind = PathKind::NativeAbsolute;
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    if (path.starts_with("assets/")) { kind = PathKind::AndroidAsset; path.remove_prefix(7); }
#endif
    if (path.empty() || path.ends_with('/')) return io::Status::success();
    AdapterId physical, package;
    std::shared_ptr<const Mounts> snapshot;
    { std::lock_guard lock(_mutex); snapshot = _mounts; physical = _physicalId; package = _packageId; }
    for (auto& m : *snapshot) {
        if ((only && m.id != only) || (platformOnly && m.id != physical && m.id != package) ||
            (kind == PathKind::NativeAbsolute && m.id != physical) ||
            (kind == PathKind::AndroidAsset && m.id != package)) continue;
        bool stop = false, invalid = false;
        std::unordered_set<std::string> seen;
        auto status = m.adapter->visitFiles({kind, path}, [&](const AdapterEntry& entry) {
            if (stop) return Visit::Stop;
            if (entry.rootIndex && *entry.rootIndex >= m.adapter->searchPaths().size()) {
                invalid = stop = true;
                return Visit::Stop;
            }
            if (!seen.insert(entry.entryKey).second) return Visit::Next;
            FileHit hit;
            hit._adapter = m.adapter;
            hit._entry = entry;
            hit._id = m.id;
            hit._name = m.name;
            hit._priority = m.priority;
            stop = visitor(std::move(hit)) == Visit::Stop;
            return stop ? Visit::Stop : Visit::Next;
        });
        if (invalid) return io::Status::failure({ErrorCode::InvalidBackend});
        if (!status) return status;
        if (stop) break;
    }
    return io::Status::success();
}
Result<FileHit> FileUtils::firstHit(std::string_view path, AdapterId only, bool platformOnly) const
{
    auto result = Result<FileHit>::failure({ErrorCode::NotFound});
    auto status = visitHits(path, only, platformOnly, [&](FileHit hit) {
        result = Result<FileHit>::success(std::move(hit));
        return Visit::Stop;
    });
    return status ? result : Result<FileHit>::failure(status.error);
}
Result<FileHit> FileUtils::findFile(std::string_view path) const { return firstHit(path, 0, false); }
Result<FileHit> FileUtils::findFileIn(AdapterId id, std::string_view path) const {
    return id ? firstHit(path, id, false) : Result<FileHit>::failure({ErrorCode::InvalidArgument});
}
Result<FileHit> FileUtils::findPlatformFile(std::string_view path) const { return firstHit(path, 0, true); }
Result<std::vector<FileHit>> FileUtils::findAllFiles(std::string_view path) const {
    std::vector<FileHit> hits;
    auto status = visitHits(path, 0, false, [&](FileHit hit) { hits.push_back(std::move(hit)); return Visit::Next; });
    return status ? Result<std::vector<FileHit>>::success(std::move(hits)) : Result<std::vector<FileHit>>::failure(status.error);
}
Result<FileHit> FileUtils::findSibling(const FileHit& parent, std::string_view name) const {
    if (!parent._adapter || !validName(name) || isAbsolutePathInternal(name)) return Result<FileHit>::failure({ErrorCode::InvalidArgument});
    auto entry = parent._adapter->findSibling(parent._entry, name);
    if (!entry) return Result<FileHit>::failure(entry.error);
    if (entry.value.rootIndex && *entry.value.rootIndex >= parent._adapter->searchPaths().size())
        return Result<FileHit>::failure({ErrorCode::InvalidBackend});
    auto hit = parent;
    hit._entry = std::move(entry.value);
    return Result<FileHit>::success(std::move(hit));
}
Result<ReadFile> FileUtils::openRead(const FileHit& hit) {
    return hit._adapter ? hit._adapter->openEntry(hit._entry) : Result<ReadFile>::failure({ErrorCode::InvalidArgument});
}
Result<int64_t> FileUtils::fileSize(const FileHit& hit) {
    if (hit._entry.sizeHint) return Result<int64_t>::success(*hit._entry.sizeHint);
    auto file = openRead(hit);
    if (!file) return Result<int64_t>::failure(file.error);
    auto length = file.value->size();
    return length >= 0 ? Result<int64_t>::success(length) : Result<int64_t>::failure({ErrorCode::IoError});
}

void FileUtils::refreshPhysicalAdapter()
{
    std::lock_guard lock(_mutex);
    Mounts next = *_mounts;
    for (auto& m : next) if (m.id == _physicalId) {
        auto current = m.adapter->searchPaths();
        m.adapter = std::make_shared<PhysicalReadAdapter>(
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            "",
#else
            _defaultResRootPath,
#endif
            std::vector<std::string>(current.begin(), current.end()), physicalLookup());
        publishMounts(std::move(next));
        return;
    }
}
void FileUtils::syncPlatformRoots()
{
    // Called with _mutex held, after a legacy path-list change.
    std::vector<std::string> disk, package;
    for (auto& root : _searchPathArray) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        if (!isAbsolutePathInternal(root)) {
            package.push_back(root.starts_with("assets/") ? root.substr(7) : root);
            continue;
        }
#else
        if (!_defaultResRootPath.empty() && !isAbsolutePathInternal(_defaultResRootPath) &&
            root.starts_with(_defaultResRootPath)) {
            disk.push_back(root.substr(_defaultResRootPath.size()));
            continue;
        }
#endif
        disk.push_back(root);
    }
    Mounts next = *_mounts;
    for (auto& m : next) if (m.id == _physicalId || m.id == _packageId) {
        auto updated = m.adapter->withSearchPaths(m.id == _physicalId ? disk : package);
        if (!updated) return;
        m.adapter = std::move(updated.value);
    }
    publishMounts(std::move(next));
}
void FileUtils::syncDirectoryRoots()
{
    _searchPathArray.clear();
    _originalSearchPaths.clear();
    _fullPathCacheDir.clear();
    for (auto& m : *_mounts) if (m.id == _physicalId || m.id == _packageId) {
        for (auto root : m.adapter->searchPaths()) {
            if (m.id == _packageId) root = "assets/" + root;
            _originalSearchPaths.push_back(root);
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
            if (!isAbsolutePathInternal(root)) root = _defaultResRootPath + root;
#endif
            if (!root.empty() && root.back() != '/') root += '/';
            _searchPathArray.push_back(std::move(root));
        }
    }
}
}
