#include "io/zip/codecs/Zlib.h"
#include "io/zip/codecs/CodecDetail.h"
#include <limits>

namespace cc::compression
{
namespace detail
{
namespace
{
using io::Capability;
using io::ErrorCode;
using io::IoResult;
using io::IoStatus;
using io::Status;
using io::StreamError;

StreamError zlibError(int code, ErrorCode fallback)
{
    switch (code)
    {
    case Z_MEM_ERROR: fallback = ErrorCode::OutOfMemory; break;
    case Z_VERSION_ERROR:
    case Z_NEED_DICT: fallback = ErrorCode::UnsupportedFormat; break;
    default: break;
    }
    return {fallback, code, io::ErrorDomain::Zlib};
}

int windowBits(Format format)
{
    return format == Format::Gzip ? MAX_WBITS + 16 : MAX_WBITS;
}
}

StreamError transferError(const IoResult& result)
{
    switch (result.status)
    {
    case IoStatus::WouldBlock: return {ErrorCode::WouldBlock};
    case IoStatus::Cancelled: return {ErrorCode::Cancelled};
    case IoStatus::Timeout: return {ErrorCode::Timeout};
    case IoStatus::Error: return result.error ? result.error : StreamError{ErrorCode::InvalidBackend};
    default: return {ErrorCode::InvalidBackend};
    }
}

IoResult readChunk(io::Stream& input, void* destination, size_t capacity)
{
    const auto result = input.read(destination, capacity);
    if (result.transferred > capacity || (result.status == IoStatus::EndOfStream && result.transferred == capacity) ||
        (result.status != IoStatus::Error && result.error))
        return IoResult::failure({ErrorCode::InvalidBackend});
    if (result.status == IoStatus::Ok && !result.transferred)
        return IoResult::failure({ErrorCode::NoProgress});
    return result;
}

StreamError checkStreams(io::Stream& input, io::Stream& output)
{
    if (input.cursorIdentity() == output.cursorIdentity())
        return {ErrorCode::InvalidArgument};
    if (!input.isOpen() || !output.isOpen())
        return {ErrorCode::Closed};
    if (!io::hasCapability(input.capabilities(), Capability::Read) ||
        !io::hasCapability(output.capabilities(), Capability::Write))
        return {ErrorCode::NotSupported};
    return {};
}

InflateReader::InflateReader(io::Stream& input, Format format, const DecodeLimits& limits)
    : _input(input), _format(format), _limits(limits)
{
    if (!input.isOpen())
        _error = {ErrorCode::Closed};
    else if (!io::hasCapability(input.capabilities(), Capability::Read))
        _error = {ErrorCode::NotSupported};
    else if (!_limits.maxMembers)
        _error = {ErrorCode::LimitExceeded};
    if (_error)
        return;

    const int code = inflateInit2(&_stream, windowBits(format));
    _initialized = code == Z_OK;
    if (!_initialized)
        _error = zlibError(code, ErrorCode::IoError);
    else if (const int header = beginMember(); header != Z_OK)
        _error = zlibError(header, ErrorCode::IoError);
}

InflateReader::~InflateReader()
{
    if (_initialized)
        inflateEnd(&_stream);
}

int InflateReader::beginMember()
{
    _memberEnded = false;
    _memberBytes = 0;
    _headerBytes = 0;
    _gzipHeader = {};
    return _format == Format::Gzip ? inflateGetHeader(&_stream, &_gzipHeader) : Z_OK;
}

bool InflateReader::fill()
{
    if (_position != _end || _sourceEnded)
        return true;

    const auto remaining = _limits.maxInputBytes - _inputBytes;
    const auto requested = remaining < _buffer.size() ? static_cast<size_t>(remaining) + 1 : _buffer.size();
    const auto input = readChunk(_input, _buffer.data(), requested);
    if (input.status != IoStatus::Ok && input.status != IoStatus::EndOfStream)
        _error = transferError(input);
    else if (input.transferred > remaining)
        _error = {ErrorCode::LimitExceeded};
    if (_error)
        return false;
    _position = 0;
    _end = input.transferred;
    _inputBytes += _end;
    _sourceEnded = input.status == IoStatus::EndOfStream;
    return true;
}

IoResult InflateReader::read(void* destination, size_t capacity)
{
    if (_error)
        return IoResult::failure(_error);
    if (capacity && !destination)
        return IoResult::failure({ErrorCode::InvalidArgument});

    size_t transferred = 0;
    while (transferred < capacity && fill())
    {
        if (_memberEnded)
        {
            if (_position == _end)
                return {transferred, IoStatus::EndOfStream, {}};
            if (_format == Format::Zlib)
            {
                _error = zlibError(Z_DATA_ERROR, ErrorCode::CorruptData);
                break;
            }
            if (_members == _limits.maxMembers)
            {
                _error = {ErrorCode::LimitExceeded};
                break;
            }
            int code = inflateReset(&_stream);
            if (code == Z_OK)
                code = beginMember();
            if (code != Z_OK)
            {
                _error = zlibError(code, ErrorCode::IoError);
                break;
            }
        }

        const bool readingHeader = _format == Format::Gzip && !_gzipHeader.done;
        auto available = _end - _position;
        if (readingHeader)
        {
            if (_headerBytes == _limits.maxGzipHeaderBytes)
            {
                _error = {ErrorCode::LimitExceeded};
                break;
            }
            available = std::min(available, _limits.maxGzipHeaderBytes - _headerBytes);
        }

        const auto outputRemaining = std::min(_limits.maxOutputBytes - _outputBytes,
                                              _limits.maxMemberBytes - _memberBytes);
        const auto requested = std::min<uint64_t>(capacity - transferred, std::numeric_limits<uInt>::max());
        const auto outputSize = static_cast<uInt>(std::min(requested, outputRemaining));
        uint8_t overflowByte = 0;
        _stream.next_in = _buffer.data() + _position;
        _stream.avail_in = static_cast<uInt>(available);
        _stream.next_out = outputSize ? static_cast<uint8_t*>(destination) + transferred : &overflowByte;
        _stream.avail_out = outputSize ? outputSize : 1;

        // Z_BLOCK returns just after the wrapper header. Bound bytes passed to
        // zlib until then, including unbounded FNAME and FCOMMENT fields.
        const int code = inflate(&_stream, readingHeader ? Z_BLOCK : Z_NO_FLUSH);
        const auto consumed = available - _stream.avail_in;
        const auto produced = (outputSize ? outputSize : 1) - _stream.avail_out;
        _position += consumed;
        if (readingHeader)
            _headerBytes += consumed;
        if (produced > outputSize)
        {
            _error = {ErrorCode::LimitExceeded};
            break;
        }
        transferred += produced;
        _outputBytes += produced;
        _memberBytes += produced;

        if (code == Z_STREAM_END)
        {
            ++_members;
            _memberEnded = true;
        }
        else if (code != Z_OK || (!consumed && !produced))
        {
            _error = zlibError(code == Z_OK ? Z_DATA_ERROR : code, ErrorCode::CorruptData);
            break;
        }
    }
    return _error ? IoResult::failure(_error, transferred) : IoResult::success(transferred);
}

DeflateWriter::DeflateWriter(io::Stream& output, Format format, int level, gz_header* header) : _output(output)
{
    if (!output.isOpen())
        _error = {ErrorCode::Closed};
    else if (!io::hasCapability(output.capabilities(), Capability::Write))
        _error = {ErrorCode::NotSupported};
    else if (level < Z_DEFAULT_COMPRESSION || level > Z_BEST_COMPRESSION)
        _error = {ErrorCode::InvalidArgument};
    if (_error)
        return;
    const int code = deflateInit2(&_stream, level, Z_DEFLATED, windowBits(format), 8, Z_DEFAULT_STRATEGY);
    _initialized = code == Z_OK;
    if (!_initialized)
        _error = zlibError(code, ErrorCode::IoError);
    else if (header)
    {
        if (const int result = deflateSetHeader(&_stream, header); result != Z_OK)
            _error = zlibError(result, ErrorCode::IoError);
    }
}

DeflateWriter::~DeflateWriter()
{
    if (_initialized)
        deflateEnd(&_stream);
}

int DeflateWriter::step(int flush)
{
    _stream.next_out = _buffer.data();
    _stream.avail_out = static_cast<uInt>(_buffer.size());
    const int code = deflate(&_stream, flush);
    if (code != Z_OK && code != Z_STREAM_END)
        _error = zlibError(code, ErrorCode::IoError);
    else if (const auto produced = _buffer.size() - _stream.avail_out)
    {
        const auto write = _output.writeAll(_buffer.data(), produced);
        if (!write)
            _error = transferError(write);
    }
    return code;
}

IoResult DeflateWriter::write(const void* source, size_t size)
{
    if (_error)
        return IoResult::failure(_error);
    if (_finished)
        return IoResult::failure({ErrorCode::Closed});
    if (size && !source)
        return IoResult::failure({ErrorCode::InvalidArgument});

    size_t consumed = 0;
    while (consumed < size && !_error)
    {
        const auto offered = static_cast<uInt>(std::min<size_t>(size - consumed, std::numeric_limits<uInt>::max()));
        _stream.next_in = const_cast<uint8_t*>(static_cast<const uint8_t*>(source) + consumed);
        _stream.avail_in = offered;
        while (_stream.avail_in && !_error)
            step(Z_NO_FLUSH);
        consumed += offered - _stream.avail_in;
    }
    return _error ? IoResult::failure(_error, consumed) : IoResult::success(consumed);
}

Status DeflateWriter::finish()
{
    if (!_finished && !_error)
    {
        _stream.avail_in = 0;
        while (step(Z_FINISH) == Z_OK && !_error)
        {}
        if (!_error)
            _error = _output.flush().error;
    }
    _finished = true;
    return _error ? Status::failure(_error) : Status::success();
}

Status decode(io::Stream& input, io::Stream& output, Format format, const DecodeLimits& limits, uint64_t* written)
{
    if (auto error = checkStreams(input, output))
        return Status::failure(error);
    InflateReader reader(input, format, limits);
    std::array<uint8_t, ChunkSize> buffer;
    uint64_t total = 0;
    for (;;)
    {
        const auto result = reader.read(buffer.data(), buffer.size());
        if (result.status != IoStatus::Ok && result.status != IoStatus::EndOfStream)
            return Status::failure(transferError(result));
        if (result.transferred)
        {
            const auto write = output.writeAll(buffer.data(), result.transferred);
            if (!write)
                return Status::failure(transferError(write));
            total += result.transferred;
        }
        if (result.status == IoStatus::EndOfStream)
        {
            if (written)
                *written = total;
            return output.flush();
        }
    }
}
}

bool hasZlibHeader(std::span<const uint8_t> prefix)
{
    return prefix.size() >= 2 && (prefix[0] & 0x0f) == 8 && (prefix[0] >> 4) <= 7 &&
           (static_cast<unsigned>(prefix[0]) * 256 + prefix[1]) % 31 == 0;
}

io::Status decodeZlib(io::Stream& input, io::Stream& output, const DecodeLimits& limits)
{
    return detail::decode(input, output, detail::Format::Zlib, limits);
}

io::Result<DecodedBuffer> decodeZlib(std::span<const uint8_t> input, const DecodeLimits& limits)
{
    return detail::decodeBuffer(input, limits, [&limits](io::Stream& source, io::Stream& destination) {
        return decodeZlib(source, destination, limits);
    });
}
}
