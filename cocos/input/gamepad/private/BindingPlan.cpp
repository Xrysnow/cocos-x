#include "BindingPlan.h"

#include "GamepadBackend.h"

#include <algorithm>

namespace cc::input::detail
{
namespace
{

constexpr auto firstDpad = static_cast<unsigned>(Button::DpadUp);
constexpr auto lastDpad = static_cast<unsigned>(Button::DpadRight);

bool needsHidapiFixup(std::span<const Binding> bindings)
{
    for (const auto& binding : bindings)
        if (!binding.outputAxis && binding.outputIndex >= firstDpad)
            return binding.inputKind == RawKind::Button && binding.inputIndex == binding.outputIndex;
    return false;
}

bool adjustHidapi(Binding& binding)
{
    if (binding.inputKind != RawKind::Button || binding.outputAxis || binding.outputIndex < firstDpad)
        return true;
    if (binding.outputIndex <= lastDpad)
    {
        constexpr std::array<unsigned, 4> mask{1, 4, 8, 2};
        binding.inputKind = RawKind::Hat;
        binding.inputIndex = 0;
        binding.hatMask = mask[binding.outputIndex - firstDpad];
    }
    else
    {
        if (binding.inputIndex < 4)
            return false;
        binding.inputIndex -= 4;
    }
    return true;
}

std::optional<int> rawAxis(const RawState& raw, unsigned index)
{
    if (index >= raw.axes.size() || (!raw.axesKnown.empty() &&
        (index >= raw.axesKnown.size() || !raw.axesKnown[index])))
        return {};
    return raw.axes[index];
}

bool resolveSdlIndex(Binding& binding, const SdlInputIndices& indices)
{
    // Hats use the native indices even when buttons and axes are projected.
    if (binding.inputKind == RawKind::Hat)
        return true;
    const auto index = binding.inputIndex;
    if (binding.inputKind == RawKind::Button && index < indices.buttons.size() && indices.buttons[index])
    {
        binding.inputIndex = *indices.buttons[index];
        return true;
    }
    if (binding.inputKind == RawKind::Axis && index < indices.axes.size() && indices.axes[index])
    {
        binding.inputIndex = indices.axes[index]->index;
        binding.encoding = indices.axes[index]->encoding;
        return true;
    }
    return false;
}

int evaluateBinding(const RawState& raw, const Binding& binding)
{
    const unsigned index = binding.inputIndex;
    switch (binding.inputKind)
    {
    case RawKind::Button:
        return index < raw.buttons.size() && raw.buttons[index] ?
               (binding.outputAxis ? binding.outEnd : 1) : 0;
    case RawKind::Hat:
        return index < raw.hats.size() && (raw.hats[index] & binding.hatMask) ?
               (binding.outputAxis ? binding.outEnd : 1) : 0;
    case RawKind::Axis:
    {
        auto value = rawAxis(raw, index);
        if (!value)
            return 0;
        if (binding.encoding == AxisEncoding::Inverted)
            *value = std::clamp(-*value, -32767, 32767);
        else if (binding.encoding == AxisEncoding::PositiveHalf)
            *value = (*value + 32768) * 32767 / 65535;
        const int start = binding.inStart;
        const int end = binding.inEnd;
        if (*value < std::min(start, end) || *value > std::max(start, end))
            return 0;
        if (!binding.outputAxis)
        {
            const int threshold = start + (end - start) / 2;
            return start < end ? *value >= threshold : *value <= threshold;
        }
        if (start == binding.outStart && end == binding.outEnd)
            return *value;
        const float ratio = static_cast<float>(*value - start) / static_cast<float>(end - start);
        return binding.outStart + static_cast<int>(ratio * static_cast<float>(binding.outEnd - binding.outStart));
    }
    }
    return 0;
}

} // namespace

BindingPlan BindingPlan::compile(const RawLayout& layout, const MappingRecord& record,
                                 std::vector<Diagnostic>& diagnostics, bool legacyHidapi, bool useSdlIndices)
{
    BindingPlan plan;
    plan.face_ = record.face;
    const std::array<unsigned, 3> counts{layout.buttonCount, layout.axisCount, layout.hatCount};
    const std::array<std::span<const std::uint8_t>, 3> present{
        layout.buttonPresent, layout.axisPresent, layout.hatPresent
    };
    const bool fixup = legacyHidapi && needsHidapiFixup(record.bindings);
    for (auto binding : record.bindings)
    {
        const bool valid = (!fixup || adjustHidapi(binding)) &&
            (!useSdlIndices || resolveSdlIndex(binding, *layout.sdlIndices));
        const auto kind = static_cast<unsigned>(binding.inputKind);
        const auto index = binding.inputIndex;
        if (!valid || index >= counts[kind] ||
            (!present[kind].empty() && (index >= present[kind].size() || !present[kind][index])))
        {
            diagnostics.push_back({record.line, binding.column, "BindingUnavailable",
                binding.field() + " is unavailable in raw layout " + layout.id});
            continue;
        }
        if (std::ranges::find(plan.bindings_, binding) != plan.bindings_.end())
            continue;
        const unsigned output = binding.outputAxis ? ButtonCount + binding.outputIndex : binding.outputIndex;
        plan.byInput_[kind][binding.inputIndex].set(output);
        plan.byOutput_[output].push_back(plan.bindings_.size());
        if (binding.outputAxis)
            plan.axes_.set(binding.outputIndex);
        else
            plan.buttons_.set(binding.outputIndex);
        plan.bindings_.push_back(binding);
    }
    return plan;
}

std::string_view BindingPlan::label(Button button) const noexcept
{
    constexpr std::array<std::string_view, 4> abxy{"A", "B", "X", "Y"};
    constexpr std::array<std::string_view, 4> axby{"A", "X", "B", "Y"};
    constexpr std::array<std::string_view, 4> bayx{"B", "A", "Y", "X"};
    constexpr std::array<std::string_view, 4> sony{"Cross", "Circle", "Square", "Triangle"};
    const unsigned index = static_cast<unsigned>(button);
    if (index >= abxy.size())
        return {};
    switch (face_)
    {
    case FaceStyle::Abxy: return abxy[index];
    case FaceStyle::Axby: return axby[index];
    case FaceStyle::Bayx: return bayx[index];
    case FaceStyle::Sony: return sony[index];
    default: return {};
    }
}

void BindingPlan::evaluate(const RawState& raw, LogicalState& state) const noexcept
{
    Outputs outputs;
    outputs.set();
    evaluateOutputs(raw, outputs, state);
}

void BindingPlan::update(const RawState& raw, std::span<const RawChange> changes, LogicalState& state) const noexcept
{
    Outputs outputs;
    for (const auto& change : changes)
    {
        const auto kind = static_cast<unsigned>(change.kind);
        if (kind < byInput_.size())
            if (const auto index = byInput_[kind].find(change.index); index != byInput_[kind].end())
                outputs |= index->second;
    }
    if (outputs.any())
        evaluateOutputs(raw, outputs, state);
}

void BindingPlan::evaluateOutputs(const RawState& raw, const Outputs& outputs, LogicalState& state) const noexcept
{
    for (unsigned output = 0; output < byOutput_.size(); ++output)
    {
        if (!outputs[output])
            continue;
        int value = 0;
        for (const auto entry : byOutput_[output])
        {
            value = evaluateBinding(raw, bindings_[entry]);
            if (value != 0)
                break;
        }
        if (output < ButtonCount)
            state.buttons[output] = value != 0;
        else
            state.axes[output - ButtonCount] = static_cast<std::int16_t>(value);
    }
}

bool BindingPlan::operator==(const BindingPlan& other) const noexcept
{
    return face_ == other.face_ && bindings_ == other.bindings_;
}

} // namespace cc::input::detail
