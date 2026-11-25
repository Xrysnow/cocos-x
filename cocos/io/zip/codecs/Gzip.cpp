#include "io/zip/codecs/Gzip.h"
#include "io/zip/codecs/CodecDetail.h"
#include <new>

namespace cc::compression
{
namespace
{
gz_header makeHeader(const GzipWriteOptions& options, std::string& name)
{
    gz_header header{};
    header.time = options.modificationTime;
    header.os = 255;
    if (!name.empty())
        header.name = reinterpret_cast<Bytef*>(name.data());
    return header;
}
}

struct GzipReader::Impl
{
    Impl(io::StreamPtr stream, const DecodeLimits& limits)
        : input(std::move(stream)), reader(*input, detail::Format::Gzip, limits)
    {}

    io::StreamPtr input;
    detail::InflateReader reader;
};

GzipReader::GzipReader(std::unique_ptr<Impl> impl) : _impl(std::move(impl)) {}
GzipReader::~GzipReader() = default;

io::Result<GzipReader::Ptr> GzipReader::open(io::StreamPtr input, const DecodeLimits& limits)
{
    if (!input)
        return {{}, {io::ErrorCode::InvalidArgument}};
    try
    {
        auto impl = std::make_unique<Impl>(std::move(input), limits);
        if (auto error = impl->reader.error())
            return {{}, error};
        return io::Result<Ptr>::success(Ptr(new GzipReader(std::move(impl))));
    }
    catch (const std::bad_alloc&)
    {
        return {{}, {io::ErrorCode::OutOfMemory}};
    }
}

io::IoResult GzipReader::read(void* destination, size_t capacity)
{
    return _impl->reader.read(destination, capacity);
}

io::Status GzipReader::finish()
{
    std::array<uint8_t, detail::ChunkSize> buffer;
    for (;;)
    {
        const auto result = read(buffer.data(), buffer.size());
        if (result.status == io::IoStatus::EndOfStream)
            return io::Status::success();
        if (!result)
            return io::Status::failure(detail::transferError(result));
    }
}

struct GzipWriter::Impl
{
    Impl(io::StreamPtr stream, const GzipWriteOptions& options)
        : output(std::move(stream)), name(options.originalName), header(makeHeader(options, name)),
          writer(*output, detail::Format::Gzip, options.level, &header)
    {}

    io::StreamPtr output;
    std::string name;
    gz_header header;
    detail::DeflateWriter writer;
};

GzipWriter::GzipWriter(std::unique_ptr<Impl> impl) : _impl(std::move(impl)) {}
GzipWriter::~GzipWriter() = default;

io::Result<GzipWriter::Ptr> GzipWriter::begin(io::StreamPtr output, const GzipWriteOptions& options)
{
    if (!output || options.originalName.find('\0') != std::string::npos)
        return {{}, {io::ErrorCode::InvalidArgument}};
    if (options.originalName.size() > DecodeLimits{}.maxGzipHeaderBytes - 11)
        return {{}, {io::ErrorCode::LimitExceeded}};
    try
    {
        auto impl = std::make_unique<Impl>(std::move(output), options);
        if (auto error = impl->writer.error())
            return {{}, error};
        return io::Result<Ptr>::success(Ptr(new GzipWriter(std::move(impl))));
    }
    catch (const std::bad_alloc&)
    {
        return {{}, {io::ErrorCode::OutOfMemory}};
    }
}

io::IoResult GzipWriter::write(const void* source, size_t size)
{
    return _impl->writer.write(source, size);
}

io::Status GzipWriter::finish()
{
    return _impl->writer.finish();
}

bool hasGzipSignature(std::span<const uint8_t> prefix)
{
    return prefix.size() >= 2 && prefix[0] == 0x1f && prefix[1] == 0x8b;
}

io::Status decodeGzip(io::Stream& input, io::Stream& output, const DecodeLimits& limits)
{
    return detail::decode(input, output, detail::Format::Gzip, limits);
}

io::Result<DecodedBuffer> decodeGzip(std::span<const uint8_t> input, const DecodeLimits& limits)
{
    return detail::decodeBuffer(input, limits, [&limits](io::Stream& source, io::Stream& destination) {
        return decodeGzip(source, destination, limits);
    });
}
}
