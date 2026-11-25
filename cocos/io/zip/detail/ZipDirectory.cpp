#include "io/zip/detail/ZipSource.h"
#include <algorithm>
#include <array>

namespace cc::archive::detail
{
namespace {
// Fields in ZIP and ZIP64 are unsigned, unaligned and little endian.
uint64_t field(const uint8_t* p, unsigned width)
{
    uint64_t value = 0;
    for (unsigned i = 0; i < width; ++i) value |= uint64_t(p[i]) << (8 * i);
    return value;
}

class DirectoryInput {
public:
    explicit DirectoryInput(zip_source_t* source) : _source(source) {}
    bool read(uint64_t offset, uint8_t* out, size_t length) {
        if (offset > INT64_MAX || zip_source_seek(_source, static_cast<int64_t>(offset), SEEK_SET) < 0)
            return false;
        while (length) {
            auto n = zip_source_read(_source, out, length);
            if (n <= 0 || uint64_t(n) > length) return false;
            length -= static_cast<size_t>(n);
            out += n;
        }
        return true;
    }
    Status check(uint64_t length, const ZipReadOptions& limits, bool& strict) {
        constexpr size_t endBytes = 22, locatorBytes = 20;
        std::vector<uint8_t> tail(static_cast<size_t>(std::min<uint64_t>(length, UINT16_MAX + endBytes + locatorBytes)));
        if (tail.size() < endBytes || !read(length - tail.size(), tail.data(), tail.size()))
            return Status::failure({ErrorCode::CorruptData});
        size_t i = tail.size() - endBytes;
        for (;;) {
            if (field(tail.data() + i, 4) == 0x06054b50) {
                if (field(tail.data() + i + 20, 2) == tail.size() - i - endBytes) break;
                // A signature inside the comment must not select another directory.
                strict = true;
            }
            if (!i) return Status::failure({ErrorCode::UnsupportedFormat});
            --i;
        }
        const uint8_t* end = tail.data() + i;
        uint64_t bound = length - tail.size() + i;
        uint64_t count = field(end + 10, 2), bytes = field(end + 12, 4), offset = field(end + 16, 4);
        bool zip64 = i >= locatorBytes && field(end - locatorBytes, 4) == 0x07064b50;
        if (zip64) {
            auto* locator = end - locatorBytes;
            if (field(locator + 4, 4) != 0 || field(locator + 16, 4) != 1)
                return Status::failure({ErrorCode::UnsupportedFormat});
            uint64_t zip64Offset = field(locator + 8, 8);
            std::array<uint8_t, 56> record{};
            if (zip64Offset > bound - locatorBytes || bound - locatorBytes - zip64Offset < record.size() ||
                !read(zip64Offset, record.data(), record.size()) || field(record.data(), 4) != 0x06064b50 ||
                field(record.data() + 4, 8) != bound - locatorBytes - zip64Offset - 12)
                return Status::failure({ErrorCode::CorruptData});
            const auto* p = record.data();
            if (field(p + 16, 4) || field(p + 20, 4) || field(p + 24, 8) != field(p + 32, 8))
                return Status::failure({ErrorCode::UnsupportedFormat});
            bound = zip64Offset;
            count = field(p + 32, 8);
            bytes = field(p + 40, 8);
            offset = field(p + 48, 8);
        } else if (field(end + 4, 2) || field(end + 6, 2) || field(end + 8, 2) != count) {
            return Status::failure({ErrorCode::UnsupportedFormat});
        }
        if (offset > bound || bytes > bound - offset || count > bytes / 46)
            return Status::failure({ErrorCode::CorruptData});
        auto maxCount = std::min(limits.maxEntries, limits.maxIndexBytes / sizeof(ZipEntryInfo));
        if (count > maxCount || bytes > limits.maxIndexBytes) return Status::failure({ErrorCode::LimitExceeded});
        // Classic ZIP permits a wrapped 16-bit count. Walk the actual records before
        // libzip allocates its directory and reject invalid lengths or excess entries.
        const uint64_t stop = offset + bytes;
        uint64_t actual = 0, windowStart = 0, windowEnd = 0;
        std::array<uint8_t, 8192> window;
        while (offset < stop) {
            if (stop - offset < 46) return Status::failure({ErrorCode::CorruptData});
            if (windowEnd < offset + 46) {
                auto length = static_cast<size_t>(std::min<uint64_t>(window.size(), stop - offset));
                if (!read(offset, window.data(), length)) return Status::failure({ErrorCode::CorruptData});
                windowStart = offset;
                windowEnd = offset + length;
            }
            const auto* header = window.data() + (offset - windowStart);
            if (field(header, 4) != 0x02014b50) return Status::failure({ErrorCode::CorruptData});
            auto record = 46 + field(header + 28, 2) + field(header + 30, 2) + field(header + 32, 2);
            if (record > stop - offset) return Status::failure({ErrorCode::CorruptData});
            if (++actual > maxCount) return Status::failure({ErrorCode::LimitExceeded});
            offset += record;
        }
        if ((zip64 ? actual : actual & UINT16_MAX) != count) return Status::failure({ErrorCode::CorruptData});
        return Status::success();
    }
private:
    zip_source_t* _source;
};
}
Status checkDirectory(zip_source_t* source, uint64_t length, const ZipReadOptions& limits, bool& strict)
{
    if (zip_source_open(source) != 0)
        return Status::failure(zipError(zip_error_code_zip(zip_source_error(source))));
    struct Close { zip_source_t* source; ~Close() { zip_source_close(source); } } close{source};
    return DirectoryInput(source).check(length, limits, strict);
}
}
