#pragma once
#include "platform/FileReadAdapter.h"

namespace cc
{
class CC_DLL PhysicalReadAdapter final : public FileReadAdapter {
public:
    using Lookup = std::function<std::string(std::string_view)>;
    PhysicalReadAdapter(std::string base, std::vector<std::string> roots, Lookup lookup = {});
    std::string_view kind() const noexcept override { return "physical"; }
    std::span<const std::string> searchPaths() const override { return _roots; }
    io::Result<AdapterPtr> withSearchPaths(const std::vector<std::string>& roots) const override;
    io::Status visitFiles(ReadQuery query, const HitVisitor& emit) const override;
    io::Result<ReadFile> openEntry(const AdapterEntry& entry) const override;
    io::Result<AdapterEntry> findSibling(const AdapterEntry& entry, std::string_view name) const override;
private:
    io::Result<AdapterEntry> probe(std::string path, std::optional<size_t> root) const;
    std::string _base;
    std::vector<std::string> _roots;
    Lookup _lookup;
};
}
