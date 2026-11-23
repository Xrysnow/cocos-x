#pragma once

#include "AudioDirectBackend.h"
#include "AudioDirectInput.h"
#include <array>
#include <atomic>
#include <stop_token>

namespace cc::audio::detail {

struct DirectBlock {
    struct Frame {
        std::array<float, 2> sample;
        double position;
    };
    std::array<Frame, outputBlockFrames> frames;
    unsigned count = 0;
};

// Owns the decoder and both sides of the interpolation window on the reader thread.
class DirectRenderer {
public:
    DirectRenderer(const AudioDirectInput& input, unsigned outputRate, const std::atomic<bool>& looping,
        std::stop_token cancellation);
    bool start(std::uint64_t frame);
    bool fill(DirectBlock& block);
    bool finished() const { return !_current; }

private:
    using Samples = std::array<float, 2>;
    bool read(Samples& samples);
    bool readNext();

    const AudioDirectInput& _input;
    const unsigned _outputRate;
    const std::atomic<bool>& _looping;
    const std::stop_token _cancellation;
    IntrusivePtr<AudioDecoder> _decoder;
    std::array<std::uint8_t, AudioDecoder::DEFAULT_BUFFER_SIZE> _buffer;
    size_t _offset = 0;
    size_t _bufferSize = 0;
    unsigned _frameBytes = 0;
    std::uint64_t _readPosition = 0;
    std::uint64_t _position = 0;
    std::uint64_t _nextPosition = 0;
    std::uint64_t _phase = 0;
    Samples _sample{};
    Samples _nextSample{};
    bool _current = false;
    bool _next = false;
    bool _failed = false;
};

} // namespace cc::audio::detail
