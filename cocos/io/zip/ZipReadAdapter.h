#pragma once
#include "platform/FileReadAdapter.h"
#include "io/zip/ZipReader.h"

namespace cc
{
struct ZipMountOptions {
    archive::EntryReadOptions entry;
    uint64_t maxCacheBytes = uint64_t{512} << 20;
};
class CC_DLL ZipReadAdapter final : public FileReadAdapter {
public:
    static io::Result<std::shared_ptr<ZipReadAdapter>> create(std::shared_ptr<archive::ZipReader> reader,
        const std::vector<std::string>& roots = {""}, const ZipMountOptions& options = {});
    std::string_view kind() const noexcept override { return "zip"; }
    std::span<const std::string> searchPaths() const override { return _roots; }
    io::Result<AdapterPtr> withSearchPaths(const std::vector<std::string>& roots) const override;
    io::Status visitFiles(ReadQuery query, const HitVisitor& emit) const override;
    io::Result<ReadFile> openEntry(const AdapterEntry& entry) const override;
    io::Result<AdapterEntry> findSibling(const AdapterEntry& parent, std::string_view name) const override;
    const archive::ZipEntryInfo* entryInfo(std::string_view name) const;
    bool containsEntry(std::string_view name) const;
    io::Result<archive::Bytes> readBytes(std::string_view entryKey) const;
    bool isCached(std::string_view entryKey) const;
    bool removeCached(std::string_view entryKey) const;
    void clearCache() const;
    std::vector<std::string> cachedEntryNames() const;
    size_t cachedBytes() const;
    struct State;
private:
    ZipReadAdapter(std::shared_ptr<State>, std::vector<std::string>);
    io::Result<AdapterEntry> locate(std::string_view key, std::optional<size_t> root) const;
    std::shared_ptr<State> _state;
    std::vector<std::string> _roots;
};
}
