#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>

namespace cc::audio::detail {
// Counts the quantized samples actually offered to the output. One instance
// belongs to a physical pair of grips and survives stream and owner changes.
class GripLimiter {
public:
    struct Checkpoint {
        unsigned first, count;
        std::array<double, 2> sums, detector;
        double gain;
        std::array<std::array<double, 2>, 256> previous;
    };
    Checkpoint checkpoint(unsigned count) const {
        Checkpoint saved{index, count, energy, detector, gain, {}};
        for (unsigned i = 0; i < count; ++i)
            saved.previous[i] = history[(index + i) % window];
        return saved;
    }
    void restore(const Checkpoint& saved) {
        index = saved.first;
        energy = saved.sums;
        detector = saved.detector;
        gain = saved.gain;
        for (unsigned i = 0; i < saved.count; ++i)
            history[(index + i) % window] = saved.previous[i];
    }
    std::array<std::int16_t, 2> process(float left, float right)
    {
        std::array<double, 2> x{left, right};
        double scale = 1;
        double power = 0;
        double targetGain = 1;
        for (unsigned side = 0; side < 2; ++side) {
            energy[side] -= history[index][side];
            if (!std::isfinite(x[side]))
                x[side] = 0;
            const double p = x[side] * x[side];
            power += p;
            // A 3 ms RMS detector backs off sustained drive before the hard window fills.
            detector[side] += (p - detector[side]) / 144.;
            if (detector[side] > .38 * .38)
                targetGain = std::min(targetGain, .38 / std::sqrt(detector[side]));
            if (p > 0) {
                const double allowance = std::clamp(sideEnergy - energy[side], 0., .75 * .75);
                scale = std::min(scale, std::sqrt(allowance / p));
            }
        }
        const double detectedPair = detector[0] + detector[1];
        if (detectedPair > .475 * .475)
            targetGain = std::min(targetGain, .475 / std::sqrt(detectedPair));
        gain = std::min(targetGain, gain + (1. - gain) / 1920.); // 40 ms release.
        scale = std::min(scale, gain);
        if (power > 0) {
            const double allowance = std::clamp(pairEnergy - energy[0] - energy[1], 0., .85 * .85);
            scale = std::min(scale, std::sqrt(allowance / power));
        }
        std::array<std::int16_t, 2> result{};
        for (unsigned side = 0; side < 2; ++side) {
            result[side] = static_cast<std::int16_t>(x[side] * scale * 32767.);
            double value = result[side] / 32767.;
            history[index][side] = value * value;
            energy[side] += value * value;
        }
        index = (index + 1) % window;
        return result;
    }
private:
    static constexpr unsigned window = 4800;
    static constexpr double sideEnergy = .40 * .40 * window;
    static constexpr double pairEnergy = .50 * .50 * window;
    std::array<std::array<double, 2>, window> history{};
    std::array<double, 2> energy{}, detector{};
    double gain = 1;
    unsigned index{};
};
} // namespace cc::audio::detail
