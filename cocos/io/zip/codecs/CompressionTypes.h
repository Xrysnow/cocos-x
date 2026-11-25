#pragma once

#include "io/core/MemoryBuffer.h"
#include <span>

namespace cc::compression
{
using DecodedBuffer = ThreadSafeRefPtr<const io::MemoryBuffer>;

struct DecodeLimits
{
    uint64_t maxOutputBytes = uint64_t{256} << 20;
    uint64_t maxMemberBytes = uint64_t{256} << 20;
    uint64_t maxInputBytes = uint64_t{512} << 20;
    uint64_t maxMembers = 4096;
    size_t maxGzipHeaderBytes = 256 * 1024;
};
}
