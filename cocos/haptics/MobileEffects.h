#pragma once
#include <cstdint>
#include <vector>

namespace cc::haptics
{
/** Native family used by a mobile route. */
enum class MobilePlatform
{
    None,     ///< Desktop or a route without a mobile backend.
    Android,  ///< Android Vibrator on a handset or input device.
    Apple     ///< Core Haptics on a handset or controller locality.
};
/** Android predefined effects, following the platform IDs. */
enum class AndroidEffect
{
    Click,          ///< Android EFFECT_CLICK.
    DoubleClick,    ///< Android EFFECT_DOUBLE_CLICK.
    Tick,           ///< Android EFFECT_TICK.
    HeavyClick = 5  ///< Android EFFECT_HEAVY_CLICK.
};
/** Finite Android pulse; -1 selects the device's default amplitude. */
struct AndroidOneShot
{
    unsigned durationMs{};  ///< 1..1000 milliseconds.
    int amplitude = -1;     ///< 1..255 or -1 for default.
};
/** One segment of an Android finite waveform. */
struct AndroidStep
{
    unsigned durationMs{};  ///< Positive duration in milliseconds.
    int amplitude{};        ///< 0..255, or -1 for the device default.
};
/** Up to 128 steps, lasting at most 1000 ms in total. */
struct AndroidWaveform
{
    std::vector<AndroidStep> steps;  ///< Adjacent on/off or amplitude steps in playback order.
};
/** One Android composition primitive. */
struct AndroidPrimitive
{
    unsigned id{};       ///< Android primitive ID.
    float scale = 1;     ///< 0..1.
    unsigned delayMs{};  ///< Delay after the previous primitive, in milliseconds.
};
/** Up to 16 ordered primitives whose durations the device can report. */
struct AndroidComposition
{
    std::vector<AndroidPrimitive> steps;  ///< Primitives and inter-primitive delays in playback order.
};
/** One Android envelope transition. */
struct AndroidControlPoint
{
    unsigned durationMs{};  ///< Transition length, in milliseconds.
    float amplitude{};      ///< Normalized amplitude or perceptual intensity.
    float texture{};        ///< Sharpness in 0..1 or a positive frequency in Hz.
};
/** A finite envelope whose last amplitude is zero. */
struct AndroidEnvelope
{
    bool frequency = false;                   ///< True selects amplitude/Hz, false selects intensity/sharpness.
    std::vector<AndroidControlPoint> points;  ///< Ordered transitions within one second.
};
/** One Core Haptics event relative to pattern start. */
struct AppleEvent
{
    double time{};           ///< Start in seconds.
    double duration{};       ///< Zero for a transient, positive for a continuous event.
    float intensity = 1;     ///< Normalized intensity in 0..1.
    float sharpness = 0.5f;  ///< Normalized sharpness in 0..1.
};
/** Dynamic Core Haptics control. */
enum class AppleControl
{
    Intensity,  ///< Multiplies the base event intensity.
    Sharpness   ///< Applies a signed offset to the base sharpness.
};
/** A dynamic value at an offset from the pattern start. */
struct AppleParameter
{
    AppleControl control{};  ///< Intensity multiplier or sharpness offset.
    double time{};           ///< Seconds after start.
    float value{};           ///< Intensity in 0..1, sharpness offset in -1..1.
};
/** Ordered parameters for an existing player. */
struct AppleParameters
{
    std::vector<AppleParameter> parameters;  ///< At most 128 values ordered by time in the current pattern.
};
/** One point relative to a curve's start. */
struct AppleCurvePoint
{
    double time{};  ///< Seconds from the beginning of this curve.
    float value{};  ///< Normalized intensity or signed sharpness offset.
};
/** A native parameter curve containing at most sixteen points. */
struct AppleParameterCurve
{
    AppleControl control{};               ///< Parameter being controlled.
    double time{};                        ///< Curve start in seconds after pattern start.
    std::vector<AppleCurvePoint> points;  ///< Strictly increasing offsets in seconds.
};
/** Finite Apple pattern, total duration at most five seconds. */
struct ApplePattern
{
    std::vector<AppleEvent> events;           ///< Ordered events.
    std::vector<AppleParameter> parameters;   ///< Optional initial dynamic parameters.
    std::vector<AppleParameterCurve> curves;  ///< Optional initial curves.
};
/** Opaque player identity unique across leases. */
enum class RawPlayerId : std::uint64_t
{
};
}  // namespace cc::haptics
