#include "platform/android/AndroidPackageReadAdapter.h"
#include "platform/android/FileUtils-android.h"
#include "platform/PosixFileStream.h"
#include "io/zip/detail/ZipSource.h"
namespace cc
{
using io::ErrorCode;
using io::Result;
namespace {
Result<AdapterEntry> apkEntry(std::string key, std::optional<size_t> index) {
    auto* manager = FileUtilsAndroid::getAssetManager();
    if (!manager) return Result<AdapterEntry>::failure({ErrorCode::NotFound});
    auto* asset = AAssetManager_open(manager, key.c_str(), AASSET_MODE_UNKNOWN);
    if (!asset) return Result<AdapterEntry>::failure({ErrorCode::NotFound});
    auto size = AAsset_getLength64(asset);
    AAsset_close(asset);
    return Result<AdapterEntry>::success({index, "apk:" + key, "APK", {}, size});
}
}
AndroidPackageReadAdapter::AndroidPackageReadAdapter(std::shared_ptr<ZipReadAdapter> obb, std::vector<std::string> roots)
    : _obb(std::move(obb)), _roots(std::move(roots)) {}
Result<AdapterPtr> AndroidPackageReadAdapter::withSearchPaths(const std::vector<std::string>& roots) const {
    std::vector<std::string> paths;
    for (auto& root : roots) {
        if (root.empty() || root == "." || root == "./") paths.emplace_back();
        else {
            auto clean = archive::detail::cleanName(root, true);
            if (!clean) return Result<AdapterPtr>::failure(clean.error);
            paths.push_back(std::move(clean.value));
        }
    }
    return Result<AdapterPtr>::success(std::make_shared<AndroidPackageReadAdapter>(_obb, std::move(paths)));
}
io::Status AndroidPackageReadAdapter::visitFiles(ReadQuery q, const HitVisitor& emit) const {
    if (q.kind == PathKind::NativeAbsolute) return io::Status::success();
    bool direct = q.kind == PathKind::AndroidAsset;
    for (size_t i = 0; i < (direct ? 1 : _roots.size()); ++i) {
        auto key = archive::detail::cleanName((direct ? std::string{} : _roots[i]) + std::string(q.name));
        if (!key) continue;
        std::optional<size_t> index = direct ? std::nullopt : std::optional<size_t>(i);
        bool stop = false;
        if (_obb) {
            auto status = _obb->visitFiles({PathKind::Logical, key.value}, [&](AdapterEntry entry) {
                entry.entryKey = "obb:" + entry.entryKey;
                entry.rootIndex = index;
                stop = emit(entry) == Visit::Stop;
                return stop ? Visit::Stop : Visit::Next;
            });
            if (!status || stop) return status;
        }
        auto apk = apkEntry(key.value, index);
        if (apk && emit(apk.value) == Visit::Stop) break;
    }
    return io::Status::success();
}
Result<ReadFile> AndroidPackageReadAdapter::openEntry(const AdapterEntry& entry) const {
    auto key = entry;
    if (key.entryKey.starts_with("obb:") && _obb) {
        key.entryKey.erase(0, 4);
        return _obb->openEntry(key);
    }
    if (!key.entryKey.starts_with("apk:")) return Result<ReadFile>::failure({ErrorCode::InvalidArgument});
    auto stream = std::make_unique<PosixFileStream>();
    if (!stream->openAsset(FileUtilsAndroid::getAssetManager(), key.entryKey.c_str() + 4))
        return Result<ReadFile>::failure({ErrorCode::NotFound});
    return Result<ReadFile>::success(std::move(stream));
}
Result<AdapterEntry> AndroidPackageReadAdapter::findSibling(const AdapterEntry& parent, std::string_view name) const {
    if (name.empty() || name.front() == '/') return Result<AdapterEntry>::failure({ErrorCode::InvalidArgument});
    auto key = parent;
    key.entryKey.erase(0, 4);
    if (parent.entryKey.starts_with("obb:") && _obb) {
        auto found = _obb->findSibling(key, name);
        if (found) found.value.entryKey = "obb:" + found.value.entryKey;
        return found;
    }
    auto clean = archive::detail::cleanName(key.entryKey.substr(0, key.entryKey.rfind('/') + 1) + std::string(name));
    return clean ? apkEntry(std::move(clean.value), parent.rootIndex) : Result<AdapterEntry>::failure(clean.error);
}
}
