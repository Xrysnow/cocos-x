#pragma once

#include "io/core/Stream.h"
#include "io/zip/codecs/CompressionTypes.h"
#include <array>

namespace cc::compression
{
using CczKey = std::array<uint32_t, 4>;

struct CczHeader
{
    bool encrypted = false;
    uint16_t version = 0;
    uint16_t compression = 0;
    uint32_t reserved = 0;
    // For CCZp, this field is encrypted and is available only during decoding.
    std::optional<uint32_t> plainSize;
};

struct CczReadOptions
{
    DecodeLimits limits;
    std::optional<CczKey> key;
};

struct CczWriteOptions
{
    int level = -1;
};

CC_DLL bool hasCczSignature(std::span<const uint8_t> prefix);
CC_DLL io::Result<CczHeader> inspectCcz(std::span<const uint8_t> prefix);
CC_DLL io::Status decodeCcz(io::Stream& input, io::Stream& output, const CczReadOptions& options = {});
CC_DLL io::Result<DecodedBuffer> decodeCcz(std::span<const uint8_t> input, const CczReadOptions& options = {});
CC_DLL io::Status encodeCcz(io::Stream& input, uint64_t plainSize, io::Stream& output,
                            const CczWriteOptions& options = {});
}
