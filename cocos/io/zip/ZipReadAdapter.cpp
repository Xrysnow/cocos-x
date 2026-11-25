#include "io/zip/ZipReadAdapter.h"
#include "io/zip/detail/ZipSource.h"
#include "io/core/MemoryStream.h"
#include <algorithm>
#include <condition_variable>
#include <unordered_map>
#include <unordered_set>
namespace cc
{
using io::Result;
using io::ErrorCode;
using archive::detail::cleanName;
struct ZipReadAdapter::State {
    std::shared_ptr<archive::ZipReader> reader;
    std::unordered_map<std::string, archive::EntryId> entries;
    std::unordered_map<std::string, std::optional<archive::EntryId>> directories;
    struct CacheSlot {
        std::condition_variable ready;
        archive::Bytes bytes;
        io::StreamError error{};
        bool complete = false;
    };
    ZipMountOptions options;
    uint64_t cachedSize = 0, loadingSize = 0;
    std::mutex mutex;
    std::unordered_map<std::string, std::shared_ptr<CacheSlot>> cached;
};
namespace {
class CachedEntryOwner final : public Ref {
public:
    CachedEntryOwner(RefConstructionToken token, archive::Bytes bytes) : Ref(token), bytes(std::move(bytes)) {}
    const archive::Bytes bytes;
};
Result<std::string> lookupName(std::string_view raw, bool directory = false)
{
    std::string name(raw);
    std::replace(name.begin(), name.end(), '\\', '/');
    return cleanName(name, directory);
}

Result<std::vector<std::string>> zipRoots(const std::vector<std::string>& input)
{
    std::vector<std::string> roots;
    for (auto& root : input) {
        if (root.empty() || root == "." || root == "./") roots.emplace_back();
        else {
            auto name = cleanName(root, true);
            if (!name) return Result<std::vector<std::string>>::failure(name.error);
            roots.push_back(std::move(name.value));
        }
    }
    return Result<std::vector<std::string>>::success(std::move(roots));
}
}
ZipReadAdapter::ZipReadAdapter(std::shared_ptr<State> state, std::vector<std::string> roots)
    : _state(std::move(state)), _roots(std::move(roots)) {}

Result<std::shared_ptr<ZipReadAdapter>> ZipReadAdapter::create(std::shared_ptr<archive::ZipReader> reader,
                                                              const std::vector<std::string>& roots, const ZipMountOptions& options)
{
    using Output = Result<std::shared_ptr<ZipReadAdapter>>;
    if (!reader) return Output::failure({ErrorCode::InvalidArgument});
    auto paths = zipRoots(roots);
    if (!paths) return Output::failure(paths.error);
    auto state = std::make_shared<State>();
    state->reader = std::move(reader);
    state->options = options;
    state->options.entry.access = archive::EntryAccess::Seekable;
    if (state->options.entry.temporaryDirectory.empty()) {
        std::error_code ec;
        auto temp = std::filesystem::temp_directory_path(ec);
        if (!ec) state->options.entry.temporaryDirectory = archive::detail::utf8(temp);
    }
    std::unordered_set<std::string> explicitNames;
    for (auto& entry : state->reader->entries()) {
        bool dir = entry.type == archive::EntryType::Directory;
        if (!dir && entry.type != archive::EntryType::File) return Output::failure({ErrorCode::NotSupported});
        auto clean = cleanName(entry.name, dir);
        if (!clean) return Output::failure(clean.error);
        auto& key = clean.value;
        if (dir) key.pop_back();
        if (!explicitNames.emplace(key).second || (!dir && state->directories.contains(key)))
            return Output::failure({ErrorCode::AmbiguousEntry});
        for (size_t i = key.find('/'); i != key.npos; i = key.find('/', i + 1)) {
            auto parent = key.substr(0, i);
            if (state->entries.contains(parent)) return Output::failure({ErrorCode::AmbiguousEntry});
            state->directories.try_emplace(std::move(parent));
        }
        if (dir) state->directories.insert_or_assign(key, entry.id);
        else state->entries.emplace(key, entry.id);
    }
    return Output::success(std::shared_ptr<ZipReadAdapter>(new ZipReadAdapter(std::move(state), std::move(paths.value))));
}
Result<AdapterPtr> ZipReadAdapter::withSearchPaths(const std::vector<std::string>& roots) const {
    auto paths = zipRoots(roots);
    if (!paths) return Result<AdapterPtr>::failure(paths.error);
    return Result<AdapterPtr>::success(AdapterPtr(new ZipReadAdapter(_state, std::move(paths.value))));
}
Result<AdapterEntry> ZipReadAdapter::locate(std::string_view raw, std::optional<size_t> root) const {
    auto clean = lookupName(raw);
    if (!clean) return Result<AdapterEntry>::failure(clean.error);
    auto it = _state->entries.find(clean.value);
    if (it == _state->entries.end()) return Result<AdapterEntry>::failure({ErrorCode::NotFound});
    auto& meta = _state->reader->entries()[it->second.index];
    AdapterEntry entry{root, it->first, _state->reader->sourceName(), {}, {}};
    if (meta.size && *meta.size <= INT64_MAX) entry.sizeHint = static_cast<int64_t>(*meta.size);
    return Result<AdapterEntry>::success(std::move(entry));
}
io::Status ZipReadAdapter::visitFiles(ReadQuery q, const HitVisitor& emit) const {
    if (q.kind != PathKind::Logical) return io::Status::success();
    for (size_t i = 0; i < _roots.size(); ++i) {
        auto hit = locate(_roots[i] + std::string(q.name), i);
        if (hit && emit(hit.value) == Visit::Stop) break;
        if (!hit && hit.error.code != ErrorCode::NotFound && hit.error.code != ErrorCode::InvalidArgument)
            return io::Status::failure(hit.error);
    }
    return io::Status::success();
}
Result<AdapterEntry> ZipReadAdapter::findSibling(const AdapterEntry& parent, std::string_view name) const {
    if (name.empty() || name.starts_with('/') || name.starts_with('\\'))
        return Result<AdapterEntry>::failure({ErrorCode::InvalidArgument});
    auto dir = parent.entryKey.substr(0, parent.entryKey.rfind('/') + 1);
    return locate(dir.append(name), parent.rootIndex);
}
Result<ReadFile> ZipReadAdapter::openEntry(const AdapterEntry& entry) const {
    auto it = _state->entries.find(entry.entryKey);
    if (it == _state->entries.end()) return Result<ReadFile>::failure({ErrorCode::NotFound});
    archive::Bytes cached;
    {
        std::lock_guard lock(_state->mutex);
        auto slot = _state->cached.find(it->first);
        if (slot != _state->cached.end()) cached = slot->second->bytes;
    }
    if (cached) {
        auto owner = makeThreadSafeRef<CachedEntryOwner>(cached);
        auto stream = io::MemoryStream::borrow(cached->data(), cached->size(), std::move(owner));
        return stream ? readFileFromStream(std::move(stream.value)) : Result<ReadFile>::failure(stream.error);
    }
    auto stream = _state->reader->openEntry(it->second, _state->options.entry);
    return stream ? readFileFromStream(std::move(stream.value)) : Result<ReadFile>::failure(stream.error);
}
const archive::ZipEntryInfo* ZipReadAdapter::entryInfo(std::string_view name) const {
    if (const auto file = lookupName(name)) {
        if (const auto found = _state->entries.find(file.value); found != _state->entries.end())
            return &_state->reader->entries()[found->second.index];
    }
    if (auto dir = lookupName(name, true)) {
        dir.value.pop_back();
        if (const auto found = _state->directories.find(dir.value); found != _state->directories.end() && found->second)
            return &_state->reader->entries()[found->second->index];
    }
    return nullptr;
}
bool ZipReadAdapter::containsEntry(std::string_view name) const {
    if (const auto file = lookupName(name); file && _state->entries.contains(file.value))
        return true;
    auto dir = lookupName(name, true);
    if (!dir)
        return false;
    dir.value.pop_back();
    return _state->directories.contains(dir.value);
}
Result<archive::Bytes> ZipReadAdapter::readBytes(std::string_view name) const {
    const auto key = lookupName(name);
    if (!key) return Result<archive::Bytes>::failure(key.error);
    auto it = _state->entries.find(key.value);
    if (it == _state->entries.end()) return Result<archive::Bytes>::failure({ErrorCode::NotFound});
    using Output = Result<archive::Bytes>;
    auto size = _state->reader->entries()[it->second.index].size;
    if (!size) return Output::failure({ErrorCode::NotSupported});
    std::unique_lock lock(_state->mutex);
    auto existing = _state->cached.find(it->first);
    if (existing != _state->cached.end()) {
        auto slot = existing->second;
        slot->ready.wait(lock, [&] { return slot->complete; });
        return slot->bytes ? Output::success(slot->bytes) : Output::failure(slot->error);
    }
    if (*size > _state->options.maxCacheBytes - _state->cachedSize - _state->loadingSize)
        return Output::failure({ErrorCode::LimitExceeded});
    auto slot = std::make_shared<State::CacheSlot>();
    _state->cached.emplace(it->first, slot);
    _state->loadingSize += *size;
    lock.unlock();
    auto bytes = _state->reader->readEntry(it->second, _state->options.entry);
    lock.lock();
    _state->loadingSize -= *size;
    slot->bytes = bytes.value;
    slot->error = bytes.error;
    slot->complete = true;
    auto current = _state->cached.find(it->first);
    if (current != _state->cached.end() && current->second == slot) {
        if (bytes) _state->cachedSize += *size;
        else _state->cached.erase(current);
    }
    lock.unlock();
    slot->ready.notify_all();
    return bytes;
}
bool ZipReadAdapter::removeCached(std::string_view name) const {
    const auto key = lookupName(name);
    if (!key) return false;
    std::lock_guard lock(_state->mutex);
    auto it = _state->cached.find(key.value);
    if (it == _state->cached.end()) return false;
    bool loaded = !!it->second->bytes;
    if (loaded) _state->cachedSize -= it->second->bytes->size();
    _state->cached.erase(it);
    return loaded;
}
void ZipReadAdapter::clearCache() const {
    std::lock_guard lock(_state->mutex);
    _state->cached.clear();
    _state->cachedSize = 0;
}
bool ZipReadAdapter::isCached(std::string_view name) const {
    const auto key = lookupName(name);
    if (!key) return false;
    std::lock_guard lock(_state->mutex);
    auto it = _state->cached.find(key.value);
    return it != _state->cached.end() && it->second->bytes;
}
std::vector<std::string> ZipReadAdapter::cachedEntryNames() const {
    std::lock_guard lock(_state->mutex);
    std::vector<std::string> out;
    for (auto& [name, slot] : _state->cached) if (slot->bytes) out.push_back(name);
    return out;
}
size_t ZipReadAdapter::cachedBytes() const {
    std::lock_guard lock(_state->mutex);
    return static_cast<size_t>(_state->cachedSize);
}
}
