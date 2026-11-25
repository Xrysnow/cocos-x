/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd
Copyright (c) 2020 C4games Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "io/zip/codecs/Ccz.h"
#include "io/zip/codecs/CodecDetail.h"
#include <limits>
#include <new>
#include <stdexcept>

namespace cc::compression
{
namespace
{
using io::ErrorCode;
using io::IoStatus;
using io::Status;

constexpr size_t HeaderSize = 16;

io::StreamError cczError(ErrorCode code)
{
    return {code, 0, io::ErrorDomain::Ccz};
}

uint16_t readBig16(const uint8_t* bytes)
{
    return static_cast<uint16_t>((uint16_t{bytes[0]} << 8) | bytes[1]);
}

uint32_t readBig32(const uint8_t* bytes)
{
    return (uint32_t{bytes[0]} << 24) | (uint32_t{bytes[1]} << 16) | (uint32_t{bytes[2]} << 8) | bytes[3];
}

uint32_t readLittle32(const uint8_t* bytes)
{
    return bytes[0] | (uint32_t{bytes[1]} << 8) | (uint32_t{bytes[2]} << 16) | (uint32_t{bytes[3]} << 24);
}

void writeLittle32(uint8_t* bytes, uint32_t word)
{
    for (size_t i = 0; i < 4; ++i)
        bytes[i] = static_cast<uint8_t>(word >> (i * 8));
}

using ExpandedKey = std::array<uint32_t, 1024>;

ExpandedKey expandKey(const CczKey& key)
{
    ExpandedKey words{};
    uint32_t previous = 0;
    uint32_t sum = 0;
    for (int round = 0; round < 6; ++round)
    {
        sum += 0x9e3779b9u;
        const auto part = (sum >> 2) & 3;
        for (size_t i = 0; i < words.size(); ++i)
        {
            const auto next = words[(i + 1) % words.size()];
            const auto mix = ((previous >> 5 ^ next << 2) + (next >> 3 ^ previous << 4)) ^
                             ((sum ^ next) + (key[(i & 3) ^ part] ^ previous));
            words[i] += mix;
            previous = words[i];
        }
    }
    return words;
}

Status decodePayload(io::Stream& input, io::Stream& output, uint32_t plainSize, DecodeLimits limits)
{
    if (plainSize > limits.maxOutputBytes || plainSize > limits.maxMemberBytes)
        return Status::failure(cczError(ErrorCode::LimitExceeded));

    // Reject an inflated size that differs from the format's length field.
    limits.maxOutputBytes = plainSize;
    uint64_t written = 0;
    const auto status = detail::decode(input, output, detail::Format::Zlib, limits, &written);
    if (!status)
        return status;
    return written == plainSize ? Status::success() : Status::failure(cczError(ErrorCode::CorruptData));
}

Status decodeEncrypted(io::Stream& input, io::Stream& output, std::array<uint8_t, HeaderSize>& prefix,
                       const CczHeader& header, const CczReadOptions& options)
{
    if (!options.key)
        return Status::failure(cczError(ErrorCode::CredentialsRequired));
    const auto key = expandKey(*options.key);
    writeLittle32(prefix.data() + 12, readLittle32(prefix.data() + 12) ^ key[0]);
    const auto plainSize = readBig32(prefix.data() + 12);
    if (plainSize > options.limits.maxOutputBytes || plainSize > options.limits.maxMemberBytes)
        return Status::failure(cczError(ErrorCode::LimitExceeded));

    try
    {
        std::vector<uint8_t> bytes(prefix.begin() + 12, prefix.end());
        std::array<uint8_t, detail::ChunkSize> buffer;
        auto remaining = options.limits.maxInputBytes - HeaderSize;
        for (;;)
        {
            const auto requested = remaining < buffer.size() ? static_cast<size_t>(remaining) + 1 : buffer.size();
            const auto read = detail::readChunk(input, buffer.data(), requested);
            if (read.status != IoStatus::Ok && read.status != IoStatus::EndOfStream)
                return Status::failure(detail::transferError(read));
            if (read.transferred > remaining)
                return Status::failure(cczError(ErrorCode::LimitExceeded));
            remaining -= read.transferred;
            bytes.insert(bytes.end(), buffer.begin(), buffer.begin() + read.transferred);
            if (read.status == IoStatus::EndOfStream)
                break;
        }

        // Legacy CCZp XORs little-endian words, starting at the length field.
        // Every word in the first 512 is transformed, then every 64th word.
        const auto wordCount = bytes.size() / 4;
        uint32_t checksum = readLittle32(bytes.data());
        size_t keyIndex = 1;
        for (size_t i = 1; i < wordCount; i += i < 512 ? 1 : 64)
        {
            auto* destination = bytes.data() + i * 4;
            const auto decoded = readLittle32(destination) ^ key[keyIndex++ % key.size()];
            writeLittle32(destination, decoded);
            if (i < 128)
                checksum ^= decoded;
        }
        if (checksum != header.reserved)
            return Status::failure(cczError(ErrorCode::CorruptData));

        auto source = io::MemoryStream::borrow(bytes.data() + 4, bytes.size() - 4);
        if (!source)
            return Status::failure(source.error);
        return decodePayload(*source.value, output, plainSize, options.limits);
    }
    catch (const std::bad_alloc&)
    {
        return Status::failure(cczError(ErrorCode::OutOfMemory));
    }
    catch (const std::length_error&)
    {
        return Status::failure(cczError(ErrorCode::LimitExceeded));
    }
}
}

bool hasCczSignature(std::span<const uint8_t> prefix)
{
    return prefix.size() >= 4 && prefix[0] == 'C' && prefix[1] == 'C' && prefix[2] == 'Z' &&
           (prefix[3] == '!' || prefix[3] == 'p');
}

io::Result<CczHeader> inspectCcz(std::span<const uint8_t> prefix)
{
    if (prefix.size() < HeaderSize || !hasCczSignature(prefix))
        return {{}, cczError(ErrorCode::CorruptData)};
    CczHeader header;
    header.encrypted = prefix[3] == 'p';
    header.compression = readBig16(prefix.data() + 4);
    header.version = readBig16(prefix.data() + 6);
    header.reserved = readBig32(prefix.data() + 8);
    if (header.compression != 0 || header.version > (header.encrypted ? 0 : 2))
        return {{}, cczError(ErrorCode::UnsupportedFormat)};
    if (!header.encrypted)
        header.plainSize = readBig32(prefix.data() + 12);
    return io::Result<CczHeader>::success(header);
}

Status decodeCcz(io::Stream& input, io::Stream& output, const CczReadOptions& options)
{
    if (auto error = detail::checkStreams(input, output))
        return Status::failure(error);
    if (options.limits.maxInputBytes < HeaderSize)
        return Status::failure(cczError(ErrorCode::LimitExceeded));
    std::array<uint8_t, HeaderSize> prefix;
    const auto read = input.readExact(prefix.data(), prefix.size());
    if (read.status == IoStatus::EndOfStream)
        return Status::failure(cczError(ErrorCode::CorruptData));
    if (!read)
        return Status::failure(detail::transferError(read));
    auto header = inspectCcz(prefix);
    if (!header)
        return Status::failure(header.error);
    if (header.value.encrypted)
        return decodeEncrypted(input, output, prefix, header.value, options);

    auto limits = options.limits;
    limits.maxInputBytes -= HeaderSize;
    return decodePayload(input, output, *header.value.plainSize, limits);
}

io::Result<DecodedBuffer> decodeCcz(std::span<const uint8_t> input, const CczReadOptions& options)
{
    return detail::decodeBuffer(input, options.limits, [&options](io::Stream& source, io::Stream& destination) {
        return decodeCcz(source, destination, options);
    });
}

Status encodeCcz(io::Stream& input, uint64_t plainSize, io::Stream& output, const CczWriteOptions& options)
{
    if (auto error = detail::checkStreams(input, output))
        return Status::failure(error);
    if (plainSize > std::numeric_limits<uint32_t>::max())
        return Status::failure(cczError(ErrorCode::LimitExceeded));
    detail::DeflateWriter writer(output, detail::Format::Zlib, options.level);
    if (auto error = writer.error())
        return Status::failure(error);

    std::array<uint8_t, HeaderSize> header{'C', 'C', 'Z', '!', 0, 0, 0, 2};
    for (size_t i = 0; i < 4; ++i)
        header[HeaderSize - 1 - i] = static_cast<uint8_t>(plainSize >> (i * 8));
    if (const auto write = output.writeAll(header.data(), header.size()); !write)
        return Status::failure(detail::transferError(write));

    std::array<uint8_t, detail::ChunkSize> buffer;
    uint64_t remaining = plainSize;
    while (remaining)
    {
        const auto read = detail::readChunk(input, buffer.data(), static_cast<size_t>(std::min<uint64_t>(remaining, buffer.size())));
        if (read.status == IoStatus::EndOfStream)
            return Status::failure(cczError(ErrorCode::CorruptData));
        if (!read)
            return Status::failure(detail::transferError(read));
        if (const auto write = writer.write(buffer.data(), read.transferred); !write)
            return Status::failure(detail::transferError(write));
        remaining -= read.transferred;
    }
    const auto end = detail::readChunk(input, buffer.data(), 1);
    if (end.status == IoStatus::Ok)
        return Status::failure(cczError(ErrorCode::CorruptData));
    if (end.status != IoStatus::EndOfStream)
        return Status::failure(detail::transferError(end));
    return writer.finish();
}
}
