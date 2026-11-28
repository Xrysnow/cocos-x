#pragma once
#include "haptics/HapticClip.h"
#include <array>
#include <cstdint>

namespace cc::haptics::detail
{
using Time                  = std::int64_t;  // Absolute or clip-local microseconds, as indicated.
constexpr Time Second       = 1000000;
constexpr unsigned MaxNodes = 4096;
struct Point
{
    Time at;
    double value;
};
using Curve = std::vector<Point>;
enum Control
{
    Intensity,
    Sharpness,
    Attack,
    Decay,
    Release,
    Count
};
struct Command
{
    Time at;
    Curve points;
};
struct Sample
{
    double amplitude, texture;
};
struct Layer
{
    Time start{}, end{}, tail{};
    unsigned ordinal{};
    std::optional<double> intensity, sharpness, attack, decay, release, sustained;
    Curve textureOffset;  // HE frequency offset, interpolated before saturation.
    Curve envelope;  // Compiled AHAP envelope including release.
};
struct Pulse
{
    Time at{};
    unsigned ordinal{};
    std::optional<double> intensity, sharpness;
};
struct ClipData
{
    AssetFormat format{};
    ImportPolicy policy{};
    std::string sourceJson; // Original UTF-8 document, shared with active players through the clip.
    bool nativeEligible{};  // Lossless source semantics and supported document shape.
    bool heFitsPlayer{true}; // Firmware limits apply only to original submission.
    Time duration{}, renderEnd{};
    unsigned nodes{};
    Curve amplitude, frequency;
    std::vector<Layer> layers;
    std::vector<Pulse> pulses;
    std::vector<Time> boundaries;  // Sorted, distinct source knots including release boundaries.
    std::array<std::vector<Command>, Count> controls;
    double control(Control id, Time at) const;
    Sample sample(const Layer& layer, Time at) const;
    Sample sample(const Pulse& pulse) const;
};
struct ClipAccess
{
    static const ClipData& get(const HapticClip& clip) { return *clip._data; }
    static HapticClip make(std::shared_ptr<const ClipData> data) { return HapticClip(std::move(data)); }
};
double interpolate(const Curve& curve, Time at, double fallback);
}  // namespace cc::haptics::detail
