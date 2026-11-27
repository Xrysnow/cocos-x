#include "haptics/private/Import.h"
#include <unordered_set>

namespace cc::haptics::detail
{
Field Field::member(std::string_view key) const
{
    object();
    auto it = json->FindMember(rapidjson::StringRef(key.data(), static_cast<rapidjson::SizeType>(key.size())));
    return {it == json->MemberEnd() ? nullptr : &it->value, path + "." + std::string(key)};
}

void Importer::warn(const Field& f, std::string code, std::string message, bool loss)
{
    if (loss && clip.policy == ImportPolicy::Strict)
        f.fail(std::move(message), Error::InvalidAsset, std::move(code));
    warnings.push_back({f.path, std::move(code), std::move(message)});
}
void Importer::fields(const Field& f, std::initializer_list<std::string_view> known)
{
    f.object();
    std::unordered_set<std::string_view> seen;
    for (auto it = f.json->MemberBegin(); it != f.json->MemberEnd(); ++it)
    {
        std::string_view key(it->name.GetString(), it->name.GetStringLength());
        bool recognized = std::find(known.begin(), known.end(), key) != known.end();
        if (recognized && !seen.insert(key).second)
            f.member(key).fail("Duplicate field", Error::InvalidAsset, "DuplicateKey");
        if (!recognized && clip.format == AssetFormat::AppleAhap)
        {
            // Reference the current value directly. A lookup here would scan a large object for every unknown key.
            warn({&it->value, f.path + "." + std::string(key)}, "UnknownField", "Unknown AHAP playback field", true);
        }
    }
}
double Importer::ranged(const Field& f, double lo, double hi)
{
    double v = f.number();
    if (v < lo || v > hi)
    {
        if (clip.format == AssetFormat::MetaHaptic)
            f.fail("Parameter out of range");
        warn(f, "Clamped", "Parameter outside supported range", true);
    }
    return std::clamp(v, lo, hi);
}
double interpolate(const Curve& curve, Time at, double fallback)
{
    if (curve.empty())
        return fallback;
    auto right = std::upper_bound(curve.begin(), curve.end(), at, [](Time t, const Point& p) { return t < p.at; });
    if (right == curve.begin())
        return right->value;
    const auto& left = right[-1];
    if (right == curve.end())
        return left.value;
    return std::lerp(left.value, right->value, double(at - left.at) / double(right->at - left.at));
}
double ClipData::control(Control id, Time at) const
{
    const auto& commands = controls[id];
    auto next =
        std::upper_bound(commands.begin(), commands.end(), at, [](Time t, const Command& c) { return t < c.at; });
    return next == commands.begin() ? (id == Intensity ? 1.0 : 0.0) : interpolate(next[-1].points, at, 0);
}
Sample ClipData::sample(const Layer& l, Time at) const
{
    if (at < l.start || at >= l.tail)
        return {};
    if (format == AssetFormat::MetaHaptic)
        return {interpolate(amplitude, at, 0), interpolate(frequency, at, .5)};
    return {
        l.intensity.value_or(1) * control(Intensity, at) * interpolate(l.envelope, at, 1),
        std::clamp(l.sharpness.value_or(.5) + control(Sharpness, at), 0., 1.)};
}
Sample ClipData::sample(const Pulse& p) const
{
    return {p.intensity.value_or(1) * control(Intensity, p.at), p.sharpness.value_or(.5)};
}
}  // namespace cc::haptics::detail

namespace cc::haptics::detail
{

Result<ImportResult> failure(Error code, std::string message, std::string path)
{
    return {{}, ErrorInfo{code, {{std::move(path), "ImportError", std::move(message)}}}};
}
Result<ImportResult> compile(std::string_view bytes, const ImportOptions& options, AssetFormat extension)
{
    if (bytes.empty() || bytes.size() > ByteLimit || bytes.find('\0') != bytes.npos)
        return failure(Error::InvalidAsset, "Expected 1..1048576 bytes of UTF-8 JSON without raw NUL");
    if ((options.policy != ImportPolicy::Compatible && options.policy != ImportPolicy::Strict) ||
        (options.format != AssetFormat::Auto && options.format != AssetFormat::AppleAhap &&
         options.format != AssetFormat::MetaHaptic))
        return failure(Error::InvalidArgument, "Unknown import setting");
    // Protect the JSON reader itself before allocating or descending into a nested container.
    int depth   = 0;
    bool quoted = false, escaped = false;
    for (char c : bytes)
    {
        if (quoted)
        {
            if (escaped)
                escaped = false;
            else if (c == '\\')
                escaped = true;
            else if (c == '"')
                quoted = false;
        }
        else if (c == '"')
            quoted = true;
        else if (c == '{' || c == '[')
        {
            if (++depth > 32)
                return failure(Error::InvalidAsset, "JSON exceeds 32 container levels");
        }
        else if (c == '}' || c == ']')
            --depth;
        if (depth < 0)
            return failure(Error::InvalidAsset, "Unmatched closing bracket");
    }
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseValidateEncodingFlag | rapidjson::kParseFullPrecisionFlag>(bytes.data(), bytes.size());
    if (doc.HasParseError())
        return failure(Error::InvalidAsset, "Invalid JSON or UTF-8 at byte " + std::to_string(doc.GetErrorOffset()));
    std::vector<Diagnostic> diagnostics;
    try
    {
        Field root{&doc, "$"};
        bool meta  = bool(root.member("version")) || bool(root.member("signals"));
        bool apple = bool(root.member("Version")) || bool(root.member("Pattern"));
        if (meta == apple)
            root.fail("Expected one unambiguous preset root");
        auto data    = std::make_shared<ClipData>();
        data->format = apple ? AssetFormat::AppleAhap : AssetFormat::MetaHaptic;
        if ((extension != AssetFormat::Auto && extension != data->format) ||
            (options.format != AssetFormat::Auto && options.format != data->format))
            root.fail("Preset format mismatch");
        data->policy = options.policy;
        Importer importer{*data, diagnostics};
        if (apple)
            importer.apple(root);
        else
            importer.meta(root);
        std::stable_sort(data->pulses.begin(), data->pulses.end(), [](auto& a, auto& b) { return a.at < b.at; });
        auto& boundaries = data->boundaries;
        auto addCurve    = [&](const Curve& curve) {
            for (const auto& p : curve)
                boundaries.push_back(p.at);
        };
        addCurve(data->amplitude);
        addCurve(data->frequency);
        for (auto& l : data->layers)
        {
            boundaries.insert(boundaries.end(), {l.start, l.end, l.tail});
            addCurve(l.envelope);
        }
        for (auto& list : data->controls)
            for (auto& command : list)
                addCurve(command.points);
        for (auto& p : data->pulses)
            boundaries.push_back(p.at);
        std::sort(boundaries.begin(), boundaries.end());
        boundaries.erase(std::unique(boundaries.begin(), boundaries.end()), boundaries.end());
        return {ImportResult{ClipAccess::make(std::move(data)), std::move(diagnostics)}, {}};
    }
    catch (Failure& f)
    {
        diagnostics.push_back(std::move(f.diagnostic));
        return {{}, ErrorInfo{f.error, std::move(diagnostics)}};
    }
}
}  // namespace cc::haptics::detail
namespace cc::haptics {
using namespace detail;
Result<ImportResult> HapticClip::parse(std::string_view bytes, const ImportOptions& options)
{
    return compile(bytes, options, AssetFormat::Auto);
}
double HapticClip::durationMs() const
{
    return double(_data->duration) / 1000;
}
AssetFormat HapticClip::format() const
{
    return _data->format;
}
ImportPolicy HapticClip::importPolicy() const
{
    return _data->policy;
}
}  // namespace cc::haptics
