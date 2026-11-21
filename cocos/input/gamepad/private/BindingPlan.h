#pragma once

#include "SdlMappingParser.h"

#include <bitset>

namespace cc::input::detail
{

struct RawState;
struct RawLayout;

struct LogicalState
{
    std::bitset<ButtonCount> buttons;
    std::array<std::int16_t, AxisCount> axes{};
};

class BindingPlan
{
public:
    static BindingPlan compile(const RawLayout& layout, const MappingRecord& record,
                               std::vector<Diagnostic>& diagnostics, bool legacyHidapi = false);

    const std::bitset<ButtonCount>& buttons() const noexcept { return buttons_; }
    const std::bitset<AxisCount>& axes() const noexcept { return axes_; }
    std::span<const Binding> bindings() const noexcept { return bindings_; }
    std::string_view label(Button button) const noexcept;
    bool empty() const noexcept { return bindings_.empty(); }
    FaceStyle face() const noexcept { return face_; }

    void evaluate(const RawState& raw, LogicalState& state) const noexcept;
    void update(const RawState& raw, std::span<const RawChange> changes, LogicalState& state) const noexcept;
    bool operator==(const BindingPlan& other) const noexcept;

private:
    using Outputs = std::bitset<ButtonCount + AxisCount>;
    std::vector<Binding> bindings_;
    std::array<std::vector<std::size_t>, ButtonCount + AxisCount> byOutput_;
    std::array<std::unordered_map<unsigned, Outputs>, 3> byInput_;
    std::bitset<ButtonCount> buttons_;
    std::bitset<AxisCount> axes_;
    FaceStyle face_ = FaceStyle::Unspecified;

    void evaluateOutputs(const RawState& raw, const Outputs& outputs, LogicalState& state) const noexcept;
};

} // namespace cc::input::detail
