#pragma once

#include "input/gamepad/GamepadFrame.h"
#include "input/gamepad/GamepadMapping.h"
#include "DeviceGuid.h"

#include <unordered_map>

namespace cc::input::detail
{

std::string_view targetMappingPlatform() noexcept;

struct MappingEnvironment
{
    std::string platform{targetMappingPlatform()};
    std::optional<unsigned> androidSdk;
    std::unordered_map<std::string, bool> hints;
};

enum class MappingSlot { Guid, XInput, Default };
enum class FaceStyle { Unspecified, Abxy, Axby, Bayx, Sony };
enum class AxisEncoding { Signed, Inverted, PositiveHalf };

struct Binding
{
    RawKind inputKind = RawKind::Button;
    unsigned inputIndex = 0;
    unsigned hatMask = 0;
    int inStart = 0;
    int inEnd = 0;
    bool outputAxis = false;
    unsigned outputIndex = 0;
    int outStart = 0;
    int outEnd = 0;
    std::size_t column = 0;
    AxisEncoding encoding = AxisEncoding::Signed;

    bool operator==(const Binding& other) const noexcept;
    std::string field() const;
};

struct MappingRecord
{
    MappingSlot slot = MappingSlot::Guid;
    DeviceGuid guid;
    std::optional<std::uint16_t> crc;
    std::string original;
    std::string name;
    std::string platform;
    std::string type;
    std::string hint;
    std::optional<unsigned> minSdk;
    std::optional<unsigned> maxSdk;
    FaceStyle face = FaceStyle::Unspecified;
    std::vector<Binding> bindings;
    std::vector<std::string> extraFields;
    std::size_t line = 1;

    bool sameContent(const MappingRecord& other) const noexcept;
};

struct ParsedMapping
{
    MappingResult result;
    MappingRecord record;
};

class SdlMappingParser
{
public:
    static constexpr std::size_t maxLineSize = 16 * 1024;
    static constexpr std::size_t maxBindingCount = 512;

    static ParsedMapping parse(std::string_view line, const MappingEnvironment& env,
                               std::size_t lineNumber = 1);
    static ParsedMapping parseFields(std::string_view fields, const MappingEnvironment& env);
    static std::string_view platformField(std::string_view line);
    static std::string_view canonicalPlatform(std::string_view platform) noexcept;
    static std::string_view trim(std::string_view value) noexcept;
};

std::string_view faceName(FaceStyle face) noexcept;

} // namespace cc::input::detail
