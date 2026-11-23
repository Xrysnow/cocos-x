#include "SdlMappingParser.h"

#include "platform/PlatformConfig.h"

#include <algorithm>
#include <charconv>
#include <iterator>

namespace cc::input::detail
{
namespace
{

constexpr std::array<std::string_view, ButtonCount> buttonNames{
    "a", "b", "x", "y", "back", "guide", "start", "leftstick", "rightstick", "leftshoulder",
    "rightshoulder", "dpup", "dpdown", "dpleft", "dpright", "misc1", "paddle1", "paddle2",
    "paddle3", "paddle4", "touchpad", "misc2", "misc3", "misc4", "misc5", "misc6"
};
constexpr std::array<std::string_view, AxisCount> axisNames{
    "leftx", "lefty", "rightx", "righty", "lefttrigger", "righttrigger"
};
constexpr std::string_view nintendoLabels = "SDL_GAMECONTROLLER_USE_BUTTON_LABELS";
constexpr std::string_view gameCubeLabels = "SDL_GAMECONTROLLER_USE_GAMECUBE_LABELS";

constexpr int axisMin = -32768;
constexpr int axisMax = 32767;

bool space(char c) noexcept
{
    return c == ' ' || c == '\t';
}

char lower(char c) noexcept
{
    return c >= 'A' && c <= 'Z' ? static_cast<char>(c - 'A' + 'a') : c;
}

bool iequals(std::string_view left, std::string_view right) noexcept
{
    return std::ranges::equal(left, right, {}, lower, lower);
}

template <class Integer>
bool number(std::string_view text, Integer& value, int base = 10)
{
    if (text.empty())
        return false;
    const auto end = text.data() + text.size();
    const auto result = std::from_chars(text.data(), end, value, base);
    return result.ec == std::errc{} && result.ptr == end;
}

// Return the first invalid byte offset, including NUL which cannot be exported in a mapping line.
std::optional<std::size_t> invalidUtf8(std::string_view text)
{
    for (std::size_t i = 0; i < text.size();)
    {
        const auto lead = static_cast<unsigned char>(text[i]);
        if (lead && lead <= 0x7f)
        {
            if (lead == '\n' || lead == '\r')
                return i;
            ++i;
            continue;
        }
        const unsigned remaining = lead >= 0xc2 && lead <= 0xdf ? 1 :
                                   lead >= 0xe0 && lead <= 0xef ? 2 :
                                   lead >= 0xf0 && lead <= 0xf4 ? 3 : 0;
        if (!remaining || remaining >= text.size() - i)
            return i;
        const auto second = static_cast<unsigned char>(text[i + 1]);
        if ((lead == 0xe0 && second < 0xa0) || (lead == 0xed && second >= 0xa0) ||
            (lead == 0xf0 && second < 0x90) || (lead == 0xf4 && second >= 0x90))
            return i + 1;
        for (unsigned j = 1; j <= remaining; ++j)
            if ((static_cast<unsigned char>(text[i + j]) & 0xc0) != 0x80)
                return i + j;
        i += remaining + 1;
    }
    return {};
}

std::string_view next(std::string_view& fields)
{
    const auto separator = fields.find(',');
    const auto field = fields.substr(0, separator);
    fields = separator == fields.npos ? std::string_view{} : fields.substr(separator + 1);
    return field;
}

void diagnostic(ParsedMapping& parsed, std::size_t column, std::string code, std::string message)
{
    parsed.result.diagnostics.push_back({parsed.record.line, column, std::move(code), std::move(message)});
}

bool validateLine(ParsedMapping& parsed, std::string_view line)
{
    if (line.size() > SdlMappingParser::maxLineSize)
    {
        diagnostic(parsed, SdlMappingParser::maxLineSize + 1, "LineTooLong", "Mapping line exceeds 16 KiB");
        return false;
    }
    if (const auto invalid = invalidUtf8(line))
    {
        diagnostic(parsed, *invalid + 1, "InvalidEncoding", "Expected one UTF-8 mapping line");
        return false;
    }
    return true;
}

template <std::size_t N>
std::optional<unsigned> find(std::string_view name, const std::array<std::string_view, N>& names)
{
    for (unsigned i = 0; i < names.size(); ++i)
        if (iequals(name, names[i]))
            return i;
    return {};
}

char takeSign(std::string_view& text)
{
    if (text.empty() || (text.front() != '+' && text.front() != '-'))
        return '\0';
    const char sign = text.front();
    text.remove_prefix(1);
    return sign;
}

void axisRange(char sign, int& start, int& end)
{
    start = sign ? 0 : axisMin;
    end = sign == '-' ? axisMin : axisMax;
}

bool parseInput(Binding& binding, std::string_view input, bool local)
{
    const char sign = takeSign(input);
    if (input.empty())
        return false;
    const char kind = lower(input.front());
    input.remove_prefix(1);
    if (input.empty() || (kind != 'a' && sign))
        return false;
    switch (kind)
    {
    case 'b':
        binding.inputKind = RawKind::Button;
        return number(input, binding.inputIndex);
    case 'a':
    {
        binding.inputKind = RawKind::Axis;
        axisRange(sign, binding.inStart, binding.inEnd);
        if (input.back() == '~')
        {
            std::swap(binding.inStart, binding.inEnd);
            input.remove_suffix(1);
        }
        return number(input, binding.inputIndex);
    }
    case 'h':
    {
        binding.inputKind = RawKind::Hat;
        const auto separator = input.find('.');
        return separator != input.npos && (local || separator == 1) &&
               number(input.substr(0, separator), binding.inputIndex) &&
               number(input.substr(separator + 1), binding.hatMask) &&
               binding.hatMask >= 1 && binding.hatMask <= 15;
    }
    default:
        return false;
    }
}

FaceStyle readFace(std::string_view text)
{
    for (const auto face : {FaceStyle::Abxy, FaceStyle::Axby, FaceStyle::Bayx, FaceStyle::Sony})
        if (iequals(text, faceName(face)))
            return face;
    return FaceStyle::Unspecified;
}

FaceStyle faceForType(std::string_view type)
{
    if (iequals(type, "ps3") || iequals(type, "ps4") || iequals(type, "ps5"))
        return FaceStyle::Sony;
    if (iequals(type, "switchpro") || iequals(type, "joyconleft") || iequals(type, "joyconright") ||
        iequals(type, "joyconpair"))
        return FaceStyle::Bayx;
    if (iequals(type, "gamecube"))
        return FaceStyle::Axby;
    return FaceStyle::Unspecified;
}

bool knownGameCube(DeviceGuid guid)
{
    // Device IDs in SDL 3.4.20's GameCube label list.
    constexpr std::array devices{
        0x00791843u, 0x00791844u, 0x00791846u, 0x057e0337u, 0x057e2073u,
        0x05e30681u, 0x09268888u, 0x0e6f0185u, 0x1a34f705u, 0x20d6a711u
    };
    const auto id = (static_cast<std::uint32_t>(guid.vendor()) << 16) | guid.product();
    return std::ranges::find(devices, id) != devices.end();
}

bool matchConditions(ParsedMapping& parsed, const MappingEnvironment& env, std::size_t hintColumn)
{
    auto& record = parsed.record;
    if (record.minSdk && record.maxSdk && record.minSdk > record.maxSdk)
    {
        diagnostic(parsed, 1, "InvalidSdkRange", "Minimum Android SDK exceeds maximum");
        return false;
    }
    if (SdlMappingParser::canonicalPlatform(env.platform) == "Android" &&
        (record.minSdk || record.maxSdk))
    {
        if (!env.androidSdk)
        {
            diagnostic(parsed, 1, "SdkUnavailable", "Android SDK version is missing from the mapping environment");
            return false;
        }
        const unsigned sdk = *env.androidSdk;
        if ((record.minSdk && sdk < *record.minSdk) || (record.maxSdk && sdk > *record.maxSdk))
        {
            diagnostic(parsed, 1, "SdkOutOfRange", "Android SDK " + std::to_string(sdk) + " is outside the mapping range");
            return false;
        }
    }

    std::string_view condition = record.hint;
    const bool negate = condition.starts_with('!');
    if (negate)
        condition.remove_prefix(1);
    const auto separator = condition.find(':');
    const auto name = condition.substr(0, separator);
    bool defaultValue = false;
    if (separator != condition.npos)
    {
        const auto fallback = condition.substr(separator + 1);
        if (fallback != "=0" && fallback != "=1")
        {
            diagnostic(parsed, hintColumn, "InvalidHint", "Expected hint NAME[:=0 or :=1]");
            return false;
        }
        defaultValue = fallback == "=1";
    }
    if (hintColumn != 0 && (name.empty() || !std::ranges::all_of(name, [](char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
               (c >= '0' && c <= '9') || c == '_';
    })))
    {
        diagnostic(parsed, hintColumn, "InvalidHint", "Expected an ASCII hint name");
        return false;
    }

    const bool gameCube = name == gameCubeLabels || (name.empty() && knownGameCube(record.guid));
    if (gameCube || name == nintendoLabels)
    {
        if (record.face == FaceStyle::Unspecified)
            record.face = gameCube ? FaceStyle::Axby : FaceStyle::Bayx;
        if (!negate)
        {
            constexpr std::array<unsigned, 4> gameCubePositions{0, 2, 1, 3};
            constexpr std::array<unsigned, 4> nintendoPositions{1, 0, 3, 2};
            const auto& positions = gameCube ? gameCubePositions : nintendoPositions;
            for (auto& binding : record.bindings)
                if (!binding.outputAxis && binding.outputIndex < positions.size())
                    binding.outputIndex = positions[binding.outputIndex];
        }
    }
    else if (!name.empty())
    {
        const auto found = env.hints.find(std::string(name));
        const bool enabled = found != env.hints.end() ? found->second : defaultValue;
        if (enabled == negate)
        {
            diagnostic(parsed, hintColumn, "HintSkipped", "Mapping condition is false: " + record.hint);
            parsed.result.change = MappingChange::ConditionSkipped;
            return false;
        }
    }
    if (record.face == FaceStyle::Unspecified)
        record.face = faceForType(record.type);
    return true;
}

void parseFields(ParsedMapping& parsed, std::string_view line, std::string_view fields,
                 const MappingEnvironment& env, bool local)
{
    auto& record = parsed.record;
    std::size_t hintColumn = 0;
    std::size_t bindingCount = 0;
    bool hasFace = false;
    while (!fields.empty())
    {
        const auto field = SdlMappingParser::trim(next(fields));
        if (field.empty())
            continue;
        const auto column = static_cast<std::size_t>(field.data() - line.data()) + 1;
        const auto separator = field.find(':');
        auto key = SdlMappingParser::trim(field.substr(0, separator));
        const auto value = separator == field.npos ? std::string_view{} :
                           SdlMappingParser::trim(field.substr(separator + 1));
        const auto spanColumn = column + (value.empty() ? field.size() :
                                static_cast<std::size_t>(value.data() - field.data()));

        const auto duplicate = [&] {
            diagnostic(parsed, column, "DuplicateMetadata", "Ignored repeated field: " + std::string(key));
        };
        if (iequals(key, "hint"))
        {
            if (hintColumn)
                duplicate();
            else
            {
                record.hint = value;
                hintColumn = spanColumn;
            }
            continue;
        }
        if (iequals(key, "platform") || iequals(key, "type"))
        {
            if (value.empty())
            {
                diagnostic(parsed, column, "InvalidMetadata", "Expected a value for " + std::string(key));
                return;
            }
            auto& item = iequals(key, "platform") ? record.platform : record.type;
            if (item.empty())
                item = value;
            else
                duplicate();
            continue;
        }
        if (iequals(key, "face"))
        {
            if (!hasFace)
            {
                hasFace = true;
                record.face = readFace(value);
                if (record.face == FaceStyle::Unspecified)
                {
                    diagnostic(parsed, spanColumn, "UnknownFace", "Unknown face style: " + std::string(value));
                    record.extraFields.emplace_back(field);
                }
            }
            else
                duplicate();
            continue;
        }
        if (iequals(key, "crc"))
        {
            std::uint16_t crc = 0;
            if (record.crc)
                duplicate();
            else if (value.size() > 4 || !number(value, crc, 16))
            {
                diagnostic(parsed, spanColumn, "InvalidCrc", "Expected a hexadecimal 16-bit CRC");
                return;
            }
            else
                record.crc = crc;
            continue;
        }
        if (iequals(key, "sdk>=") || iequals(key, "sdk<="))
        {
            auto& bound = iequals(key, "sdk>=") ? record.minSdk : record.maxSdk;
            unsigned sdk = 0;
            if (bound)
                duplicate();
            else if (!number(value, sdk))
            {
                diagnostic(parsed, spanColumn, "InvalidSdk", "Expected an unsigned Android SDK version");
                return;
            }
            else
                bound = sdk;
            continue;
        }

        std::string compactKey;
        if (std::ranges::any_of(key, space))
        {
            compactKey.reserve(key.size());
            std::ranges::remove_copy_if(key, std::back_inserter(compactKey), space);
            key = compactKey;
        }
        const char sign = takeSign(key);
        const auto axis = find(key, axisNames);
        const auto button = find(key, buttonNames);
        if (!axis && !button)
        {
            diagnostic(parsed, column, "UnknownField", "Unrecognized mapping field: " + std::string(key));
            record.extraFields.emplace_back(field);
            continue;
        }
        if (++bindingCount > SdlMappingParser::maxBindingCount)
        {
            diagnostic(parsed, column, "TooManyBindings", "Mapping line exceeds 512 bindings");
            return;
        }
        Binding binding;
        if (axis)
        {
            binding.outputAxis = true;
            binding.outputIndex = *axis;
            if (*axis >= static_cast<unsigned>(Axis::LeftTrigger))
            {
                binding.outStart = 0;
                binding.outEnd = axisMax;
            }
            else
                axisRange(sign, binding.outStart, binding.outEnd);
        }
        else
            binding.outputIndex = *button;

        // SDL permits spaces anywhere inside a binding token.
        std::string compactInput;
        compactInput.reserve(value.size());
        std::ranges::remove_copy_if(value, std::back_inserter(compactInput), space);
        binding.column = spanColumn;
        if ((sign && button) || !parseInput(binding, compactInput, local))
        {
            diagnostic(parsed, spanColumn, "InvalidBinding", "Invalid input for " + std::string(key) + ": " + std::string(value));
            return;
        }
        if (std::ranges::find(record.bindings, binding) == record.bindings.end())
            record.bindings.push_back(binding);
    }
    if (record.bindings.empty())
    {
        diagnostic(parsed, 1, "NoBindings", "Mapping contains no recognized bindings");
        return;
    }
    if (const auto crc = record.guid.crc())
    {
        if (record.crc && crc != record.crc)
            diagnostic(parsed, 1, "CrcOverride", "GUID checksum overrides the crc field");
        record.crc = crc;
        record.guid = record.guid.withoutCrc();
    }
    if (matchConditions(parsed, env, hintColumn))
        parsed.result.change = MappingChange::Added;
}

} // namespace

std::string_view targetMappingPlatform() noexcept
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    return "Windows";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    return "Linux";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    return "macOS";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return "iOS";
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return "Android";
#else
    return "Unknown";
#endif
}

std::string_view SdlMappingParser::trim(std::string_view value) noexcept
{
    while (!value.empty() && space(value.front()))
        value.remove_prefix(1);
    while (!value.empty() && space(value.back()))
        value.remove_suffix(1);
    return value;
}

std::string_view SdlMappingParser::canonicalPlatform(std::string_view platform) noexcept
{
    platform = trim(platform);
    if (iequals(platform, "Mac OS X"))
        return "macOS";
    for (const std::string_view known : {"Windows", "Linux", "macOS", "iOS", "Android"})
        if (iequals(platform, known))
            return known;
    return platform;
}

std::string_view SdlMappingParser::platformField(std::string_view line)
{
    next(line);
    next(line);
    while (!line.empty())
    {
        const auto field = trim(next(line));
        const auto separator = field.find(':');
        if (separator != field.npos && iequals(trim(field.substr(0, separator)), "platform"))
            return trim(field.substr(separator + 1));
    }
    return {};
}

ParsedMapping SdlMappingParser::parse(std::string_view line, const MappingEnvironment& env,
                                      std::size_t lineNumber)
{
    ParsedMapping parsed;
    parsed.result.change = MappingChange::Error;
    parsed.record.line = lineNumber;
    if (!validateLine(parsed, line))
        return parsed;
    auto fields = line;
    const auto guidText = trim(next(fields));
    const auto name = next(fields);
    if (name.empty() || fields.empty())
    {
        diagnostic(parsed, 1, "MissingHeader", "Expected GUID, name and binding fields");
        return parsed;
    }
    if (iequals(guidText, "xinput"))
        parsed.record.slot = MappingSlot::XInput;
    else if (iequals(guidText, "default"))
        parsed.record.slot = MappingSlot::Default;
    else if (const auto guid = DeviceGuid::parse(guidText))
        parsed.record.guid = guid->migrateLegacy(canonicalPlatform(env.platform));
    else
    {
        diagnostic(parsed, 1, "InvalidGuid", "Expected a 32-digit hexadecimal GUID, xinput or default");
        return parsed;
    }
    parsed.record.original = line;
    parsed.record.name = name;
    detail::parseFields(parsed, line, fields, env, false);
    return parsed;
}

ParsedMapping SdlMappingParser::parseFields(std::string_view fields, const MappingEnvironment& env)
{
    ParsedMapping parsed;
    parsed.result.change = MappingChange::Error;
    if (validateLine(parsed, fields))
    {
        parsed.record.original = fields;
        detail::parseFields(parsed, fields, fields, env, true);
    }
    return parsed;
}

std::string_view faceName(FaceStyle face) noexcept
{
    switch (face)
    {
    case FaceStyle::Abxy: return "abxy";
    case FaceStyle::Axby: return "axby";
    case FaceStyle::Bayx: return "bayx";
    case FaceStyle::Sony: return "sony";
    default: return {};
    }
}

bool Binding::operator==(const Binding& other) const noexcept
{
    return inputKind == other.inputKind && inputIndex == other.inputIndex && hatMask == other.hatMask &&
           inStart == other.inStart && inEnd == other.inEnd && outputAxis == other.outputAxis &&
           outputIndex == other.outputIndex && outStart == other.outStart && outEnd == other.outEnd && encoding == other.encoding;
}

std::string Binding::field() const
{
    std::string text;
    if (outputAxis)
    {
        if (outStart == 0 && outputIndex < static_cast<unsigned>(Axis::LeftTrigger))
            text += outEnd == axisMin ? '-' : '+';
        text += axisNames[outputIndex];
    }
    else
        text += buttonNames[outputIndex];
    text += ':';
    if (inputKind == RawKind::Axis)
    {
        if (inStart == 0 || inEnd == 0)
            text += std::min(inStart, inEnd) == axisMin ? '-' : '+';
        text += 'a';
        text += std::to_string(inputIndex);
        const bool inverted = inEnd == 0 || (inStart == axisMax && inEnd == axisMin);
        if (inverted)
            text += '~';
    }
    else
    {
        text += inputKind == RawKind::Hat ? 'h' : 'b';
        text += std::to_string(inputIndex);
        if (inputKind == RawKind::Hat)
        {
            text += '.';
            text += std::to_string(hatMask);
        }
    }
    return text;
}

bool MappingRecord::sameContent(const MappingRecord& other) const noexcept
{
    return slot == other.slot && guid == other.guid && crc == other.crc && name == other.name &&
           platform == other.platform && type == other.type && hint == other.hint &&
           minSdk == other.minSdk && maxSdk == other.maxSdk && face == other.face &&
           bindings == other.bindings && extraFields == other.extraFields;
}

} // namespace cc::input::detail
