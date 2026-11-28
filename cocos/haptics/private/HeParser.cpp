#include "Import.h"

namespace cc::haptics::detail
{
namespace
{
Time milliseconds(const Field& f, Time origin = 0)
{
    if (!f || !f.json->IsUint64() || f.json->GetUint64() > std::uint64_t((30 * Second - origin) / 1000))
        f.fail("Expected integer milliseconds within the 30 second clip");
    return origin + static_cast<Time>(f.json->GetUint64()) * 1000;
}

void pattern(Importer& parser, const Field& items, Time origin, bool grouped, unsigned& ordinal)
{
    auto& clip = parser.clip;
    const unsigned count = items.size();
    if (!count) items.fail("Empty HE pattern");
    clip.heFitsPlayer &= count <= 16;
    Time previousEnd = origin;
    for (unsigned i = 0; i < count; ++i, ++ordinal)
    {
        auto item = items.index(i);
        parser.fields(item, {"Event"});
        auto event = item.member("Event");
        auto type = event.member("Type").string();
        if (event.member("EventType")) event.fail("Conflicting HE and AHAP event types");
        auto index = event.member("Index");
        if (grouped || index)
        {
            if (!index) index.fail("An explicit actuator index is required", Error::Unsupported, "UnsupportedActuator");
            if (!index.json->IsInt()) index.fail("Expected integer actuator index");
            if (index.json->GetInt() != 0)
                index.fail("Only actuator index 0 is supported", Error::Unsupported, "UnsupportedActuator");
        }
        const bool continuous = type == "continuous";
        if (!continuous && type != "transient")
        {
            parser.warn(event.member("Type"), "UnknownEvent", "Skipped unsupported HE event type", true);
            continue;
        }
        if (continuous) parser.fields(event, {"Type", "RelativeTime", "Duration", "Index", "Parameters"});
        else parser.fields(event, {"Type", "RelativeTime", "Index", "Parameters"});
        parser.node(event);
        const Time start = milliseconds(event.member("RelativeTime"), origin);
        clip.heFitsPlayer &= start >= previousEnd;
        auto params = event.member("Parameters");
        if (continuous) parser.fields(params, {"Intensity", "Frequency", "Curve"});
        else parser.fields(params, {"Intensity", "Frequency"});
        auto intensity = params.member("Intensity"), frequency = params.member("Frequency");
        const double level = parser.ranged(intensity, 0, 100) / 100;
        const double texture = parser.ranged(frequency, 0, 100) / 100;
        clip.heFitsPlayer &= intensity.json->IsUint() && frequency.json->IsUint();
        if (!continuous)
        {
            clip.pulses.push_back({start, ordinal, level, texture});
            clip.duration = std::max(clip.duration, start);
            // The handset profile currently qualifies authored continuous events only.
            clip.heFitsPlayer = false;
            continue;
        }
        auto duration = event.member("Duration");
        Layer layer;
        layer.start = start;
        layer.end = layer.tail = milliseconds(duration, start);
        if (layer.end == start) duration.fail("Continuous event needs a positive duration");
        previousEnd = layer.end;
        layer.ordinal = ordinal;
        layer.intensity = level;
        layer.sharpness = texture;
        auto curve = params.member("Curve");
        if (!curve) curve.fail("Continuous event without explicit curve", Error::Unsupported, "UnsupportedCurve");
        const unsigned points = curve.size();
        if (points < 2) curve.fail("Expected both curve endpoints");
        clip.heFitsPlayer &= points >= 4 && points <= 16;
        for (unsigned j = 0; j < points; ++j)
        {
            auto p = curve.index(j);
            parser.fields(p, {"Time", "Intensity", "Frequency"});
            parser.node(p);
            auto time = p.member("Time");
            const Time at = milliseconds(time, start);
            if ((j == 0 && at != start) || (j && at <= layer.envelope.back().at) ||
                at > layer.end || (j + 1 == points && at != layer.end))
                time.fail("Curve must increase from zero to Duration");
            auto amplitude = p.member("Intensity");
            if ((j == 0 || j + 1 == points) && amplitude.number() != 0)
                amplitude.fail("HE curve endpoints must have zero intensity");
            layer.envelope.push_back({at, parser.ranged(amplitude, 0, 1)});
            auto offset = p.member("Frequency");
            layer.textureOffset.push_back({at, parser.ranged(offset, -100, 100) / 100});
            clip.heFitsPlayer &= offset.json->IsInt();
        }
        clip.duration = std::max(clip.duration, layer.end);
        clip.layers.push_back(std::move(layer));
    }
}
} // namespace

void Importer::he(const Field& root)
{
    const bool grouped = clip.format == AssetFormat::RichTapHeV2;
    const auto metadata = root.member("Metadata");
    // Metadata is descriptive; reject duplicate version declarations before
    // interpreting the pattern, without treating author annotations as playback fields.
    unsigned versions = 0;
    for (auto it = metadata.json->MemberBegin(); it != metadata.json->MemberEnd(); ++it)
        if (std::string_view(it->name.GetString(), it->name.GetStringLength()) == "Version" && ++versions > 1)
            metadata.member("Version").fail("Duplicate version", Error::InvalidAsset, "DuplicateKey");
    unsigned ordinal = 0;
    if (grouped)
    {
        fields(root, {"Metadata", "PatternList"});
        auto groups = root.member("PatternList");
        const unsigned count = groups.size();
        clip.heFitsPlayer &= count <= 2;
        for (unsigned i = 0; i < count; ++i)
        {
            auto group = groups.index(i);
            fields(group, {"AbsoluteTime", "Pattern"});
            Time origin = milliseconds(group.member("AbsoluteTime"));
            clip.heFitsPlayer &= origin >= clip.duration;
            pattern(*this, group.member("Pattern"), origin, true, ordinal);
        }
    }
    else
    {
        fields(root, {"Metadata", "Pattern"});
        pattern(*this, root.member("Pattern"), 0, false, ordinal);
    }
    if (clip.layers.empty() && clip.pulses.empty())
        root.fail("No supported HE events", Error::Unsupported, "NoHaptics");
    clip.renderEnd = clip.duration;
}
} // namespace cc::haptics::detail
