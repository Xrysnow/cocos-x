#include "haptics/private/Import.h"

namespace cc::haptics::detail
{
void Importer::meta(const Field& root)
{
    fields(root, {"version", "metadata", "signals"});
    auto version = root.member("version");
    fields(version, {"major", "minor", "patch"});
    auto major = version.member("major"), minor = version.member("minor"), patch = version.member("patch");
    for (const auto& part : {major, minor, patch})
    {
        if (!part || !part.json->IsUint())
            part.fail("Expected nonnegative integer version component");
    }
    if (major.json->GetUint() != 1 || minor.json->GetUint() != 0)
        version.fail(
            "Unsupported Meta version " + std::to_string(major.json->GetUint()) + "." +
                std::to_string(minor.json->GetUint()) + "." + std::to_string(patch.json->GetUint()),
            Error::Unsupported,
            "UnsupportedVersion");
    auto metadata = root.member("metadata");
    if (metadata)
    {
        fields(metadata, {"author", "editor", "source", "project", "tags", "description"});
        for (auto key : {"author", "editor", "source", "project", "description"})
        {
            if (auto value = metadata.member(key))
                value.string();
        }
        if (auto tags = metadata.member("tags"))
            for (unsigned i = 0, n = tags.size(); i < n; ++i)
                tags.index(i).string();
    }
    auto signals = root.member("signals");
    fields(signals, {"continuous"});
    auto cont = signals.member("continuous");
    fields(cont, {"envelopes"});
    auto env = cont.member("envelopes");
    fields(env, {"amplitude", "frequency"});
    double amplitudeEnd = 0;
    for (bool amplitude : {true, false})
    {
        const char* key = amplitude ? "amplitude" : "frequency";
        auto curve      = env.member(key);
        if (!amplitude && !curve)
            continue;
        unsigned size = curve.size();
        if (amplitude && size < 2)
            curve.fail("Amplitude requires at least two points");
        auto& dest      = amplitude ? clip.amplitude : clip.frequency;
        double previous = -1;
        for (unsigned i = 0; i < size; ++i)
        {
            auto p = curve.index(i);
            node(p);
            if (amplitude)
                fields(p, {"time", "amplitude", "emphasis"});
            else
                fields(p, {"time", "frequency"});
            auto time      = p.member("time");
            double seconds = time.seconds();
            if (seconds < previous || (!amplitude && seconds > amplitudeEnd))
                time.fail("Invalid curve point order or extent");
            previous     = seconds;
            auto at      = micros(seconds);
            double value = ranged(p.member(key), 0, 1);
            dest.push_back({at, value});
            if (amplitude)
            {
                amplitudeEnd  = seconds;
                auto emphasis = p.member("emphasis");
                if (emphasis)
                {
                    node(emphasis);
                    fields(emphasis, {"amplitude", "frequency"});
                    auto height = emphasis.member("amplitude");
                    double peak = ranged(height, 0, 1);
                    if (peak < value)
                        height.fail("Emphasis is weaker than its parent");
                    clip.pulses.push_back({at, i, peak, ranged(emphasis.member("frequency"), 0, 1)});
                }
            }
        }
    }
    auto start = clip.amplitude.front().at, end = clip.amplitude.back().at;
    if (end <= start)
        env.member("amplitude").fail("Amplitude span must survive microsecond quantization");
    clip.duration = clip.renderEnd = end;
    Layer layer;
    layer.start = start;
    layer.end = layer.tail = end;
    clip.layers.push_back(std::move(layer));
}
}  // namespace cc::haptics::detail
