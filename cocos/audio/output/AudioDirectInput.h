#pragma once

#include "audio/AudioDecoder.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <stop_token>
#include <vector>

namespace cc
{
class AudioSource;

struct AudioDirectInput
{
    int channels = 0;
    int sampleRate = 0;
    int bitDepth = 0;
    std::optional<uint64_t> totalFrames;
    bool seekable = false;
    std::shared_ptr<const std::vector<uint8_t>> pcm;
    std::function<IntrusivePtr<AudioDecoder>(std::stop_token)> openDecoder;
};

// Snapshot on the engine thread. The reader is constructed and used on the worker.
AudioDirectInput captureAudioDirectInput(const AudioSource& source);
}
