#pragma once
#include "HapticMixer.h"
#include "audio/output/RealtimeHaptics.h"
#include <map>
#include <numbers>
#include <cmath>
#include <tuple>

namespace cc::haptics::detail {
// The output worker owns the oscillator phases and native-device sample cursor.
// The controller supplies only immutable, already budgeted mix intervals.
class GripSynth {
    struct Oscillator {
        std::uint64_t start{}, end{};
        double phase{}, hz{};
    };
    using Voice = std::tuple<Id, unsigned, unsigned>;
    struct Impulse { Id id; std::uint64_t at; unsigned frames; Channels gain; };
    std::map<Voice, Oscillator> tones;
    std::vector<Impulse> pulses;
    std::optional<std::uint64_t> cursor;
    std::array<double, 2> previousInput{}, previousOutput{};
public:
    audio::detail::GripBlock render(std::uint64_t first, Time begin, const std::vector<Entry>& entries,
                                    const std::vector<Id>& active) {
        audio::detail::GripBlock out{};
        std::array<std::array<bool, 2>, 256> driven{};
        if (cursor && *cursor != first) {
            pulses.clear();
            previousInput = {};
            previousOutput = {};
        }
        std::erase_if(pulses, [&](const Impulse& p) { return std::find(active.begin(), active.end(), p.id) == active.end(); });
        constexpr double tau = 2 * std::numbers::pi;
        auto offset = [begin](Time at) { return unsigned(std::clamp<Time>(((at-begin)*48000 + Second-1)/Second, 0, 256)); };
        for (const auto& e : entries) {
            const double hz = 55. * std::pow(4., std::clamp(e.texture, 0., 1.));
            const unsigned from = offset(e.at), to = offset(e.validUntil);
            if (e.pulse) {
                const auto width = std::min(1u + unsigned(std::lround(48000. / hz)), toWidth(e));
                if (width >= 3) pulses.push_back({e.key.playback, first + from, width, e.amplitude});
                continue;
            }
            if (from >= to) continue;
            const auto key = Voice{e.key.playback, e.key.ordinal, e.key.iteration};
            auto [it, fresh] = tones.try_emplace(key);
            auto& tone = it->second;
            if (fresh && e.key.iteration) {
                const auto prev = tones.find({e.key.playback,e.key.ordinal,e.key.iteration-1});
                if (prev != tones.end() && prev->second.end <= first+from) tone = prev->second;
            }
            if (!tone.end) tone.start = first + from;
            if (tone.end && first+from > tone.end)
                tone.phase = std::remainder(tone.phase + tau * tone.hz * double(first + from - tone.end) / 48000., tau);
            for (unsigned i=from; i<to; ++i) {
                const auto attack = std::min(1., double(first + i - tone.start) / 144.);
                const double wave = attack * std::sin(tone.phase);
                for (unsigned side = 0; side < 2; ++side) {
                    out[i][side] += float(wave * e.amplitude[side]);
                    driven[i][side] |= e.amplitude[side] != 0;
                }
                tone.phase += tau * hz / 48000.;
            }
            tone.phase = std::remainder(tone.phase, tau);
            tone.hz = hz;
            tone.end = first + to;
        }
        for (const auto& pulse : pulses) {
            auto start = std::max(first, pulse.at);
            auto stop = std::min(first + out.size(), pulse.at + pulse.frames);
            for (auto i=start; i<stop; ++i) {
                double t = double(i-pulse.at)/(pulse.frames-1);
                double window = std::sin(std::numbers::pi*t);
                double sample = window*window*std::sin(tau*t);
                for (unsigned side = 0; side < 2; ++side) {
                    out[i-first][side] += float(sample * pulse.gain[side]);
                    driven[i-first][side] |= pulse.gain[side] != 0;
                }
            }
        }
        // A 15 Hz DC blocker operates only on authored excitation. At a hard rest
        // reset both states, so a previous owner or the opposite grip cannot leak a tail.
        static const double pole = std::exp(-tau * 15. / 48000.);
        for (unsigned i = 0; i < out.size(); ++i) {
            for (unsigned side = 0; side < 2; ++side) {
                if (!driven[i][side]) {
                    previousInput[side] = previousOutput[side] = 0;
                    continue;
                }
                const double input = out[i][side];
                previousOutput[side] = input - previousInput[side] + pole * previousOutput[side];
                previousInput[side] = input;
                out[i][side] = static_cast<float>(previousOutput[side]);
            }
        }
        cursor = first + out.size();
        std::erase_if(pulses, [&](auto& p){return p.at+p.frames <= *cursor;});
        std::erase_if(tones, [&](auto& p){return p.second.end < first;});
        return out;
    }
private:
    static unsigned toWidth(const Entry& e) {
        return unsigned(std::max<Time>(0,(e.validUntil-e.at)*48000/Second));
    }
};
} // namespace cc::haptics::detail
