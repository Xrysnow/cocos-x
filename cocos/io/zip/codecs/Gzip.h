#pragma once

#include "io/core/Stream.h"
#include "io/zip/codecs/CompressionTypes.h"
#include <memory>
#include <string>

namespace cc::compression
{
struct GzipWriteOptions
{
    int level = -1;
    std::string originalName;
    uint32_t modificationTime = 0;
};

// The caller retains control of the stream cursor and closes the underlying stream.
class CC_DLL GzipReader final
{
public:
    using Ptr = std::unique_ptr<GzipReader>;
    static io::Result<Ptr> open(io::StreamPtr input, const DecodeLimits& limits = {});
    ~GzipReader();

    io::IoResult read(void* destination, size_t capacity);
    // Consume the remaining members, then validate EOF.
    io::Status finish();

private:
    struct Impl;
    explicit GzipReader(std::unique_ptr<Impl> impl);
    std::unique_ptr<Impl> _impl;
};

class CC_DLL GzipWriter final
{
public:
    using Ptr = std::unique_ptr<GzipWriter>;
    static io::Result<Ptr> begin(io::StreamPtr output, const GzipWriteOptions& options = {});
    ~GzipWriter();

    io::IoResult write(const void* source, size_t size);
    // Write the final DEFLATE data and gzip trailer. Repeated calls report the same status.
    io::Status finish();

private:
    struct Impl;
    explicit GzipWriter(std::unique_ptr<Impl> impl);
    std::unique_ptr<Impl> _impl;
};

CC_DLL bool hasGzipSignature(std::span<const uint8_t> prefix);
CC_DLL io::Status decodeGzip(io::Stream& input, io::Stream& output, const DecodeLimits& limits = {});
CC_DLL io::Result<DecodedBuffer> decodeGzip(std::span<const uint8_t> input, const DecodeLimits& limits = {});
}
