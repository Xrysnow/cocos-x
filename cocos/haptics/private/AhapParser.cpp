#include "haptics/private/Import.h"

namespace cc::haptics::detail
{
namespace
{
constexpr std::array<std::string_view, Count> controlIds{
    "HapticIntensityControl",
    "HapticSharpnessControl",
    "HapticAttackTimeControl",
    "HapticDecayTimeControl",
    "HapticReleaseTimeControl"};

void readEvent(Importer& parser, const Field& f, unsigned ordinal)
{
    auto type       = f.member("EventType").string();
    bool continuous = type == "HapticContinuous";
    if (!continuous && type != "HapticTransient")
    {
        parser.warn(
            f,
            type.starts_with("Audio") ? "SkippedAudio" : "UnknownEvent",
            "Skipped event: " + std::string(type),
            true);
        return;
    }
    parser.fields(f, {"EventType", "Time", "EventDuration", "EventParameters"});
    parser.node(f);
    auto time    = f.member("Time");
    double start = time.seconds();
    Layer layer;
    layer.start   = micros(start);
    layer.ordinal = ordinal;
    auto duration = f.member("EventDuration");
    if (continuous || duration)
    {
        double seconds = duration.seconds();
        if (start + seconds > 30)
            duration.fail("Event extends past 30 seconds");
        layer.end = layer.tail = micros(start + seconds);
        if (continuous && layer.end <= layer.start)
            duration.fail("Continuous event needs a positive microsecond span");
    }
    auto params = f.member("EventParameters");
    if (params)
        for (unsigned i = 0, n = params.size(); i < n; ++i)
        {
            auto p = params.index(i);
            parser.fields(p, {"ParameterID", "ParameterValue"});
            auto id                       = p.member("ParameterID").string();
            std::optional<double>* target = nullptr;
            if (id == "HapticIntensity")
                target = &layer.intensity;
            else if (id == "HapticSharpness")
                target = &layer.sharpness;
            else if (continuous && id == "AttackTime")
                target = &layer.attack;
            else if (continuous && id == "DecayTime")
                target = &layer.decay;
            else if (continuous && id == "ReleaseTime")
                target = &layer.release;
            else if (continuous && id == "Sustained")
                target = &layer.sustained;
            if (!target)
            {
                parser.warn(
                    p.member("ParameterID"),
                    "UnknownParameter",
                    "Unsupported event parameter: " + std::string(id),
                    true);
                continue;
            }
            if (target->has_value())
                p.member("ParameterID").fail("Duplicate event parameter");
            *target = parser.ranged(p.member("ParameterValue"), 0, 1);
        }
    if (!layer.intensity || !layer.sharpness)
        parser.warn(
            f, "PortableDefault", "Portable rendering uses intensity 1 or sharpness 0.5 for omitted parameters");
    auto& clip = parser.clip;
    if (continuous)
    {
        clip.duration = std::max(clip.duration, layer.end);
        clip.layers.push_back(std::move(layer));
    }
    else
    {
        clip.duration = std::max(clip.duration, layer.start);
        clip.pulses.push_back({layer.start, ordinal, layer.intensity, layer.sharpness});
    }
}

void readControl(Importer& parser, const Field& f, bool curve)
{
    auto id    = f.member("ParameterID").string();
    auto match = std::find(controlIds.begin(), controlIds.end(), id);
    if (match == controlIds.end())
    {
        parser.warn(
            f,
            id.starts_with("Audio") ? "SkippedAudio" : "UnknownParameter",
            "Skipped dynamic parameter: " + std::string(id),
            true);
        return;
    }
    if (curve)
        parser.fields(f, {"ParameterID", "Time", "ParameterCurveControlPoints"});
    else
        parser.fields(f, {"ParameterID", "Time", "ParameterValue"});
    auto axis   = static_cast<Control>(match - controlIds.begin());
    double base = f.member("Time").seconds();
    Command cmd;
    parser.node(f);
    auto append = [&](const Field& point, double offset) {
        if (base + offset > 30)
            point.member("Time").fail("Control extends past 30 seconds");
        cmd.points.push_back(
            {micros(base + offset), parser.ranged(point.member("ParameterValue"), axis == Intensity ? 0 : -1, 1)});
    };
    if (curve)
    {
        auto points = f.member("ParameterCurveControlPoints");
        if (!points.size())
            points.fail("Empty control curve");
        double previous = -1;
        for (unsigned i = 0; i < points.size(); ++i)
        {
            auto p = points.index(i);
            parser.node(p);
            parser.fields(p, {"Time", "ParameterValue"});
            double offset = p.member("Time").seconds();
            if (offset < previous)
                p.member("Time").fail("Decreasing curve offset");
            previous = offset;
            append(p, offset);
        }
    }
    else
        append(f, 0);
    cmd.at = cmd.points.front().at;
    parser.clip.controls[axis].push_back(std::move(cmd));
}

// Each control breakpoint changes the slope of the unfinished phase. The level
// at takeover is carried forward, so a late change cannot restart an attack.
Time ramp(
    Importer& parser,
    Layer& layer,
    Control axis,
    double base,
    const std::vector<Time>& breaks,
    Time start,
    Time limit,
    double level,
    double goal,
    const Field& field)
{
    auto put = [&](Time at, double value) {
        if (!layer.envelope.empty() && layer.envelope.back().at == at && layer.envelope.back().value == value)
            return;
        parser.node(field);
        layer.envelope.push_back({at, value});
    };
    put(start, level);
    auto next = std::upper_bound(breaks.begin(), breaks.end(), start);
    Time t    = start;
    while (t < limit)
    {
        Time duration  = std::llround(100000 * std::clamp(base + parser.clip.control(axis, t), 0., 1.));
        Time remaining = std::llround(duration * std::abs(goal - level));
        Time end       = std::min(limit, t + remaining);
        if (next != breaks.end() && *next < end)
            end = *next++;
        if (end == t + remaining)
        {
            put(end, goal);
            return end;
        }
        level = std::lerp(level, goal, double(end - t) / double(remaining));
        put(end, level);
        t = end;
    }
    return limit;
}

void compileEnvelopes(Importer& parser, const Field& pattern)
{
    auto& clip = parser.clip;
    std::array<std::vector<Time>, Count> breaks;
    for (unsigned axis = 0; axis < Count; ++axis)
    {
        auto& list = clip.controls[axis];
        std::stable_sort(list.begin(), list.end(), [](auto& a, auto& b) { return a.at < b.at; });
        // Discard superseded knots from the breakpoint index.
        for (size_t i = 0; i < list.size(); ++i)
        {
            auto end = i + 1 == list.size() ? 31 * Second : list[i + 1].at;
            for (auto p : list[i].points)
                if (p.at < end)
                    breaks[axis].push_back(p.at);
        }
    }
    clip.renderEnd = clip.duration;
    for (auto& layer : clip.layers)
    {
        auto f = pattern.index(layer.ordinal).member("Event");
        if (!layer.attack && !layer.decay && !layer.release && !layer.sustained && breaks[Attack].empty() &&
            breaks[Decay].empty() && breaks[Release].empty())
            continue;
        parser.warn(f, "EnvelopeApproximation", "Portable envelope uses a 100 ms reference time scale");
        Time peak =
            ramp(parser, layer, Attack, layer.attack.value_or(0), breaks[Attack], layer.start, layer.end, 0, 1, f);
        if (layer.sustained.value_or(1) < .5)
            ramp(
                parser,
                layer,
                Decay,
                layer.decay.value_or(0),
                breaks[Decay],
                peak,
                layer.end,
                layer.envelope.back().value,
                0,
                f);
        else
        {
            double finalLevel = layer.envelope.back().value;
            layer.tail        = ramp(
                parser,
                layer,
                Release,
                layer.release.value_or(0),
                breaks[Release],
                layer.end,
                layer.end + 100000,
                finalLevel,
                0,
                f);
        }
        clip.renderEnd = std::max(clip.renderEnd, layer.tail);
    }
}
}  // namespace
void Importer::apple(const Field& root)
{
    fields(root, {"Version", "Pattern", "Metadata"});
    auto version = root.member("Version");
    if (!version)
    {
        clip.nativeEligible = false;
        warn(version, "MissingVersion", "Assuming AHAP version 1");
    }
    else if (version.number() != 1)
        version.fail(
            "Unsupported AHAP version " + std::to_string(version.number()), Error::Unsupported, "UnsupportedVersion");
    auto pattern = root.member("Pattern");
    if (!pattern.size())
        pattern.fail("Empty pattern");
    for (unsigned i = 0; i < pattern.size(); ++i)
    {
        auto item = pattern.index(i);
        fields(item, {"Event", "Parameter", "ParameterCurve"});
        auto event = item.member("Event"), parameter = item.member("Parameter"), curve = item.member("ParameterCurve");
        unsigned kinds = unsigned(bool(event)) + unsigned(bool(parameter)) + unsigned(bool(curve));
        if (kinds > 1 || (!kinds && item.json->ObjectEmpty()))
            item.fail("Expected one pattern item");
        if (event)
            readEvent(*this, event, i);
        else if (parameter || curve)
            readControl(*this, curve ? curve : parameter, bool(curve));
    }
    if (clip.layers.empty() && clip.pulses.empty())
        pattern.fail("No supported haptic events", Error::Unsupported, "NoHaptics");
    compileEnvelopes(*this, pattern);
}
}  // namespace cc::haptics::detail
