#include "MappingDatabase.h"

#include "../GamepadBackend.h"

#include <algorithm>
#include <iterator>
#include <new>

namespace cc::input::detail
{
namespace
{

bool isModification(MappingChange change)
{
    return change == MappingChange::Added || change == MappingChange::Replaced;
}

void appendDiagnostics(std::vector<Diagnostic>& to, std::vector<Diagnostic>& from)
{
    to.insert(to.end(), std::make_move_iterator(from.begin()), std::make_move_iterator(from.end()));
}

void count(ImportReport& total, MappingResult result)
{
    switch (result.change)
    {
    case MappingChange::Added: ++total.added; break;
    case MappingChange::Replaced: ++total.replaced; break;
    case MappingChange::Unchanged: ++total.unchanged; break;
    case MappingChange::Shadowed:
    case MappingChange::ConditionSkipped: ++total.skipped; break;
    case MappingChange::Error: ++total.failed; break;
    }
    appendDiagnostics(total.diagnostics, result.diagnostics);
}

std::string safeName(std::string_view name)
{
    std::string result(name);
    for (auto& c : result)
        if (c == ',' || c == '\n' || c == '\r' || c == '\0')
            c = ' ';
    return result.empty() ? "*" : result;
}

std::string exportLine(const DeviceGuid& guid, std::string_view name, std::string_view platform,
                       const MappingRecord& record, std::span<const Binding> bindings, FaceStyle face)
{
    std::string result = guid.str();
    result += ',';
    result += safeName(name);
    result += ',';
    for (const auto& binding : bindings)
    {
        // Multi-digit hat indices only belong to layout-local bindings.
        if (binding.inputKind == RawKind::Hat && binding.inputIndex > 9)
            return {};
        result += binding.field();
        result += ',';
    }
    if (!record.type.empty())
        result += "type:" + record.type + ',';
    if (face != FaceStyle::Unspecified)
    {
        result += "face:";
        result += faceName(face);
        result += ',';
    }
    for (const auto& field : record.extraFields)
        result += field + ',';
    result += "platform:";
    result += platform;
    result += ',';
    return result;
}

bool sameDiagnostic(const Diagnostic& lhs, const Diagnostic& rhs)
{
    return lhs.code == rhs.code && lhs.message == rhs.message;
}

} // namespace

bool MappingSelection::operator==(const MappingSelection& other) const noexcept
{
    return plan == other.plan && name == other.name && status == other.status &&
           exported == other.exported && std::ranges::equal(diagnostics, other.diagnostics, sameDiagnostic);
}

MappingDatabase::MappingDatabase(MappingEnvironment env) : env_(std::move(env))
{
    env_.platform = SdlMappingParser::canonicalPlatform(env_.platform);
}

MappingResult MappingDatabase::install(ParsedMapping parsed, MappingSource source)
{
    auto& [result, record] = parsed;
    if (result.change != MappingChange::Added)
        return std::move(result);
    const Key key{record.slot, record.guid, record.slot == MappingSlot::Guid ? record.crc : std::nullopt};
    const auto existing = entries_.find(key);
    if (existing == entries_.end())
    {
        entries_.emplace(key, Entry{std::move(record), source, entries_.size()});
        return std::move(result);
    }

    auto& entry = existing->second;
    if (source < entry.source)
    {
        result.change = MappingChange::Shadowed;
        result.diagnostics.push_back({record.line, 1, "LowerPriority", "A higher-priority mapping already owns this key"});
    }
    else if (entry.record.sameContent(record))
    {
        entry.source = source;
        result.change = MappingChange::Unchanged;
    }
    else
    {
        entry = {std::move(record), source, entry.order};
        result.change = MappingChange::Replaced;
    }
    return std::move(result);
}

MappingResult MappingDatabase::add(std::string_view line, MappingSource source)
{
    try
    {
        auto result = install(SdlMappingParser::parse(line, env_), source);
        if (isModification(result.change))
            ++revision_;
        return result;
    }
    catch (const std::bad_alloc&)
    {
        return {MappingChange::Error, {{1, 1, "OutOfMemory", "Could not store mapping"}}};
    }
}

ImportReport MappingDatabase::import(std::string_view utf8, MappingSource source)
{
    if (utf8.size() > maxFileSize)
    {
        ImportReport result;
        result.batchError = Error::InvalidArgument;
        result.diagnostics.push_back({1, 1, "FileTooLong", "Mapping database exceeds 8 MiB"});
        return result;
    }
    try
    {
        if (utf8.starts_with("\xef\xbb\xbf"))
            utf8.remove_prefix(3);
        MappingDatabase pending(*this);
        ImportReport result;
        for (std::size_t lineNumber = 1; !utf8.empty(); ++lineNumber)
        {
            const auto end = utf8.find('\n');
            auto line = utf8.substr(0, end);
            utf8 = end == utf8.npos ? std::string_view{} : utf8.substr(end + 1);
            if (line.ends_with('\r'))
                line.remove_suffix(1);
            const auto content = SdlMappingParser::trim(line);
            if (content.empty() || content.starts_with('#'))
                continue;
            if (line.size() > SdlMappingParser::maxLineSize)
            {
                count(result, SdlMappingParser::parse(line, env_, lineNumber).result);
                continue;
            }
            const auto platform = SdlMappingParser::platformField(line);
            if (platform.empty())
            {
                count(result, {MappingChange::ConditionSkipped,
                    {{lineNumber, 1, "MissingPlatform", "Batch mapping has no platform"}}});
                continue;
            }
            const auto rowPlatform = SdlMappingParser::canonicalPlatform(platform);
            // Both Apple targets use the same GameController profile layout.
            const bool sharedMfi = env_.platform == "macOS" && rowPlatform == "iOS" && content.size() > 32 &&
                content[28] == '6' && (content[29] == 'd' || content[29] == 'D') && content[32] == ',';
            if (rowPlatform != env_.platform && !sharedMfi)
            {
                count(result, {MappingChange::ConditionSkipped,
                    {{lineNumber, static_cast<std::size_t>(platform.data() - line.data()) + 1,
                      "OtherPlatform", "Mapping targets " + std::string(platform) + " on " + env_.platform}}});
                continue;
            }
            count(result, pending.install(SdlMappingParser::parse(line, env_, lineNumber), source));
        }
        entries_.swap(pending.entries_);
        if (result.added || result.replaced)
            ++revision_;
        return result;
    }
    catch (const std::bad_alloc&)
    {
        ImportReport result;
        result.batchError = Error::BackendFailure;
        return result;
    }
}

const MappingDatabase::Entry* MappingDatabase::findExact(MappingSlot slot, DeviceGuid guid,
                                                        std::optional<std::uint16_t> crc) const
{
    const auto found = entries_.find({slot, guid, crc});
    return found == entries_.end() ? nullptr : &found->second;
}

const MappingDatabase::Entry* MappingDatabase::match(const RawLayout& layout) const
{
    if (!layout.guid)
        return nullptr;
    const auto crc = layout.guid->crc();
    const auto guid = layout.guid->withoutCrc();
    if (const auto* entry = findExact(MappingSlot::Guid, guid, crc))
        return entry;
    if (const auto* entry = findExact(MappingSlot::Guid, guid))
        return entry;
    if (!layout.usesVersion || !guid.usesVersion())
        return nullptr;

    const auto anyVersion = guid.withoutVersion();
    const Entry* exact = nullptr;
    const Entry* generic = nullptr;
    for (const auto& [key, entry] : entries_)
    {
        const auto& [slot, candidateGuid, candidateCrc] = key;
        if (slot != MappingSlot::Guid || candidateGuid.withoutVersion() != anyVersion)
            continue;
        if (candidateCrc == crc && (!exact || entry.order < exact->order))
            exact = &entry;
        if (!candidateCrc && (!generic || entry.order < generic->order))
            generic = &entry;
    }
    return exact ? exact : generic;
}

MappingSelection MappingDatabase::compile(const RawLayout& layout, std::string_view name,
                                          const MappingRecord& record, MappingSource source,
                                          std::string_view status, bool fixupLegacyHidapi) const
{
    MappingSelection selection;
    const bool projected = layout.sdlIndices && status == "Matched" && record.slot == MappingSlot::Guid;
    selection.plan = BindingPlan::compile(layout, record, selection.diagnostics, fixupLegacyHidapi, projected);
    if (selection.plan.empty() || (projected && !selection.diagnostics.empty()))
    {
        selection.plan = {};
        selection.status = "LayoutUnavailable";
        return selection;
    }
    selection.name = record.name.empty() || record.name == "*" ? name : std::string_view(record.name);
    selection.status = status;
    selection.source = source;
    if (layout.guid && selection.status != "Local" && (!layout.sdlIndices || projected))
        selection.exported = exportLine(*layout.guid, selection.name, env_.platform, record,
            projected ? std::span<const Binding>(record.bindings) : selection.plan.bindings(), selection.plan.face());
    return selection;
}

MappingSelection MappingDatabase::select(const RawLayout& layout, std::string_view name) const
{
    MappingSelection unavailable;
    const auto tryEntry = [&](const Entry& entry) {
        auto selection = compile(layout, name, entry.record, entry.source, "Matched", layout.legacyHidapi);
        if (selection.plan.empty())
        {
            unavailable.status = selection.status;
            appendDiagnostics(unavailable.diagnostics, selection.diagnostics);
        }
        return selection;
    };
    if (const auto* entry = match(layout))
    {
        auto selected = tryEntry(*entry);
        if (!selected.plan.empty())
            return selected;
    }
    else if (layout.guid && layout.guid->vendor() && layout.guid->product())
    {
        // Matching these values is useful for a diagnostic only. A different
        // driver signature does not promise the same raw indices.
        for (const auto& [key, candidate] : entries_)
            if (candidate.record.slot == MappingSlot::Guid &&
                candidate.record.guid.vendor() == layout.guid->vendor() &&
                candidate.record.guid.product() == layout.guid->product() &&
                candidate.record.guid.bytes[14] != layout.guid->bytes[14])
            {
                unavailable.status = "LayoutUnavailable";
                unavailable.diagnostics.push_back({candidate.record.line, 1, "LayoutUnavailable",
                    "Mapping targets a different driver layout than " + layout.id});
                break;
            }
    }
    if (layout.xinput)
        if (const auto* entry = findExact(MappingSlot::XInput))
        {
            auto selected = tryEntry(*entry);
            if (!selected.plan.empty())
                return selected;
        }
    if (!layout.builtInMapping.empty())
    {
        auto parsed = SdlMappingParser::parseFields(layout.builtInMapping, env_);
        if (parsed.result.change == MappingChange::Added)
        {
            auto selected = compile(layout, name, parsed.record, MappingSource::BuiltIn, "Automatic", false);
            if (!selected.plan.empty())
            {
                appendDiagnostics(selected.diagnostics, unavailable.diagnostics);
                return selected;
            }
            appendDiagnostics(unavailable.diagnostics, selected.diagnostics);
        }
        unavailable.status = "LayoutUnavailable";
        appendDiagnostics(unavailable.diagnostics, parsed.result.diagnostics);
    }
    if (const auto* entry = findExact(MappingSlot::Default))
    {
        auto selected = tryEntry(*entry);
        if (!selected.plan.empty())
        {
            appendDiagnostics(selected.diagnostics, unavailable.diagnostics);
            return selected;
        }
    }
    return unavailable;
}

LocalMappingResult MappingDatabase::local(const RawLayout& layout, std::string_view fields,
                                          std::string_view name) const
{
    if (SdlMappingParser::trim(fields).empty())
        return {{MappingChange::Unchanged, {}}, select(layout, name)};
    auto parsed = SdlMappingParser::parseFields(fields, env_);
    if (parsed.result.change != MappingChange::Added)
        return {std::move(parsed.result), {}};
    auto selection = compile(layout, name, parsed.record, MappingSource::User, "Local", false);
    if (!selection.diagnostics.empty())
        parsed.result.change = MappingChange::Error;
    appendDiagnostics(parsed.result.diagnostics, selection.diagnostics);
    return {std::move(parsed.result), std::move(selection)};
}

} // namespace cc::input::detail
