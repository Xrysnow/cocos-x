#pragma once

#include "BindingPlan.h"

#include <map>
#include <tuple>

namespace cc::input::detail
{

struct MappingSelection
{
    BindingPlan plan;
    std::string name;
    std::string_view status = "RawOnly";
    std::string exported;
    std::vector<Diagnostic> diagnostics;
    std::optional<MappingSource> source;

    bool operator==(const MappingSelection& other) const noexcept;
};

struct LocalMappingResult
{
    MappingResult result;
    MappingSelection selection;
};

class MappingDatabase
{
public:
    static constexpr std::size_t maxFileSize = 8 * 1024 * 1024;

    explicit MappingDatabase(MappingEnvironment env = {});

    MappingResult add(std::string_view line, MappingSource source);
    ImportReport import(std::string_view utf8, MappingSource source);
    std::uint64_t revision() const noexcept { return revision_; }
    MappingSelection select(const RawLayout& layout, std::string_view name) const;
    LocalMappingResult local(const RawLayout& layout, std::string_view fields, std::string_view name) const;

private:
    using Key = std::tuple<MappingSlot, DeviceGuid, std::optional<std::uint16_t>>;
    struct Entry
    {
        MappingRecord record;
        MappingSource source;
        std::size_t order;
    };

    MappingEnvironment env_;
    std::map<Key, Entry> entries_;
    std::uint64_t revision_ = 0;

    MappingResult install(ParsedMapping parsed, MappingSource source);
    const Entry* findExact(MappingSlot slot, DeviceGuid guid = {},
                           std::optional<std::uint16_t> crc = {}) const;
    const Entry* match(const RawLayout& layout) const;
    MappingSelection compile(const RawLayout& layout, std::string_view name, const MappingRecord& record,
                             MappingSource source, std::string_view status, bool fixupLegacyHidapi) const;
};

} // namespace cc::input::detail
