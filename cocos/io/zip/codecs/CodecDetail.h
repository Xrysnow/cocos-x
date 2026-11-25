#pragma once

#include "io/core/MemoryStream.h"
#include "io/zip/codecs/CompressionTypes.h"
#include <algorithm>
#include <array>
#include <zlib.h>

namespace cc::compression::detail
{
constexpr size_t ChunkSize = 32 * 1024;
enum class Format { Zlib, Gzip };

io::StreamError transferError(const io::IoResult& result);
io::IoResult readChunk(io::Stream& input, void* destination, size_t capacity);
io::StreamError checkStreams(io::Stream& input, io::Stream& output);

class InflateReader final
{
public:
    InflateReader(io::Stream& input, Format format, const DecodeLimits& limits);
    ~InflateReader();
    io::StreamError error() const { return _error; }
    io::IoResult read(void* destination, size_t capacity);

private:
    io::Stream& _input;
    Format _format;
    DecodeLimits _limits;
    z_stream _stream{};
    gz_header _gzipHeader{};
    std::array<uint8_t, ChunkSize> _buffer;
    size_t _position = 0;
    size_t _end = 0;
    size_t _headerBytes = 0;
    uint64_t _inputBytes = 0;
    uint64_t _outputBytes = 0;
    uint64_t _memberBytes = 0;
    uint64_t _members = 0;
    io::StreamError _error;
    bool _initialized = false;
    bool _sourceEnded = false;
    bool _memberEnded = false;

    int beginMember();
    bool fill();
};

class DeflateWriter final
{
public:
    DeflateWriter(io::Stream& output, Format format, int level, gz_header* header = nullptr);
    ~DeflateWriter();
    io::StreamError error() const { return _error; }
    io::IoResult write(const void* source, size_t size);
    io::Status finish();

private:
    io::Stream& _output;
    z_stream _stream{};
    std::array<uint8_t, ChunkSize> _buffer;
    io::StreamError _error;
    bool _initialized = false;
    bool _finished = false;

    int step(int flush);
};

io::Status decode(io::Stream& input, io::Stream& output, Format format, const DecodeLimits& limits,
                  uint64_t* written = nullptr);

template<class Decoder>
io::Result<DecodedBuffer> decodeBuffer(std::span<const uint8_t> input, const DecodeLimits& limits, Decoder decoder)
{
    if (input.size() > limits.maxInputBytes)
        return {{}, {io::ErrorCode::LimitExceeded}};
    auto source = io::MemoryStream::borrow(input.data(), input.size());
    if (!source)
        return {{}, source.error};
    const auto capacity = static_cast<size_t>(std::min<uint64_t>(limits.maxOutputBytes, io::MemoryBuffer::MaxSize));
    auto destination = io::MemoryStream::create(0, capacity);
    if (!destination)
        return {{}, destination.error};
    if (auto status = decoder(*source.value, *destination.value); !status)
        return {{}, status.error};
    return destination.value->freeze();
}
}
