#pragma once
#include "platform/FileReadAdapter.h"
#include "io/zip/ZipReadAdapter.h"

namespace cc
{
class AndroidPackageReadAdapter final : public FileReadAdapter {
public:
    AndroidPackageReadAdapter(std::shared_ptr<ZipReadAdapter> obb, std::vector<std::string> roots);
    std::string_view kind() const noexcept override { return "android-package"; }
    std::span<const std::string> searchPaths() const override { return _roots; }
    io::Result<AdapterPtr> withSearchPaths(const std::vector<std::string>& roots) const override;
    io::Status visitFiles(ReadQuery query, const HitVisitor& emit) const override;
    io::Result<ReadFile> openEntry(const AdapterEntry& entry) const override;
    io::Result<AdapterEntry> findSibling(const AdapterEntry& parent, std::string_view name) const override;
private:
    std::shared_ptr<ZipReadAdapter> _obb;
    std::vector<std::string> _roots;
};
}
