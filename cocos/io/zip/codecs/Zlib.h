#pragma once

#include "io/core/Stream.h"
#include "io/zip/codecs/CompressionTypes.h"

namespace cc::compression
{
CC_DLL bool hasZlibHeader(std::span<const uint8_t> prefix);
CC_DLL io::Status decodeZlib(io::Stream& input, io::Stream& output, const DecodeLimits& limits = {});
CC_DLL io::Result<DecodedBuffer> decodeZlib(std::span<const uint8_t> input, const DecodeLimits& limits = {});
}
