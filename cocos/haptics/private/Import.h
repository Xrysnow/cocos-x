#pragma once
#include "haptics/private/ClipData.h"
#include "rapidjson/document-wrapper.h"
#include <algorithm>
#include <cmath>
#include <initializer_list>

namespace cc::haptics::detail
{
constexpr size_t ByteLimit = 1 << 20;
Result<ImportResult> failure(Error code, std::string message, std::string path = "$");
Result<ImportResult> compile(std::string_view bytes, const ImportOptions& options, AssetFormat extension);
struct Failure
{
    Diagnostic diagnostic;
    Error error;
};
struct Field
{
    const rapidjson::Value* json;
    std::string path;

    [[noreturn]] void fail(
        std::string message, Error error = Error::InvalidAsset, std::string code = "InvalidField") const
    {
        throw Failure{{path, std::move(code), std::move(message)}, error};
    }
    explicit operator bool() const { return json != nullptr; }
    Field member(std::string_view key) const;
    Field index(unsigned i) const { return {&(*json)[i], path + "[" + std::to_string(i) + "]"}; }
    unsigned size() const
    {
        if (!json || !json->IsArray())
            fail("Expected array");
        return json->Size();
    }
    std::string_view string() const
    {
        if (!json || !json->IsString())
            fail("Expected string");
        return {json->GetString(), json->GetStringLength()};
    }
    double number() const
    {
        if (!json || !json->IsNumber() || !std::isfinite(json->GetDouble()))
            fail("Expected finite number");
        return json->GetDouble();
    }
    double seconds() const
    {
        double v = number();
        if (v < 0 || v > 30)
            fail("Time outside 0..30 seconds");
        return v;
    }
    void object() const
    {
        if (!json || !json->IsObject())
            fail("Expected object");
    }
};
inline Time micros(double seconds)
{
    return static_cast<Time>(std::llround(seconds * Second));
}

struct Importer
{
    ClipData& clip;
    std::vector<Diagnostic>& warnings;
    void node(const Field& field, unsigned count = 1)
    {
        if (count > MaxNodes - clip.nodes)
            field.fail("Timeline exceeds 4096 nodes");
        clip.nodes += count;
    }
    void warn(const Field& field, std::string code, std::string message, bool loss = false);
    void fields(const Field& object, std::initializer_list<std::string_view> known);
    double ranged(const Field& field, double lo, double hi);
    void meta(const Field& root);
    void apple(const Field& root);
};
}  // namespace cc::haptics::detail
