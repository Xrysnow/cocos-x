#pragma once
#include "io/core/Stream.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace cc::archive
{
using Bytes = std::shared_ptr<const std::vector<uint8_t>>;
struct EntryId {
    uint64_t archive = 0;
    uint64_t index = 0;
    bool operator==(const EntryId&) const = default;
};
enum class EntryType { File, Directory, Link, Other };
struct ZipEntryInfo {
    EntryId id;
    std::string name;
    EntryType type = EntryType::File;
    std::optional<uint64_t> size, compressedSize;
    std::optional<uint32_t> crc;
    std::optional<int64_t> modified;
    std::optional<uint8_t> hostSystem;
    std::optional<uint32_t> externalAttributes;
    std::optional<uint16_t> compression, encryption;
};
struct ZipReadOptions {
    std::string password;
    uint64_t maxArchiveBytes = uint64_t{32} << 30;
    uint64_t maxEntries = 1'000'000;
    uint64_t maxIndexBytes = uint64_t{256} << 20;
    bool checkConsistency = false;
};
enum class EntryAccess { Sequential, Seekable };
struct EntryReadOptions {
    EntryAccess access = EntryAccess::Sequential;
    std::optional<std::string> password;
    uint64_t maxBytes = uint64_t{8} << 30;
    uint64_t maxMemoryBytes = uint64_t{256} << 20;
    std::string temporaryDirectory;
};
enum class WriteIntent { CreateNew, Replace, UpdateExisting };
enum class Compression : uint16_t { Store = 0, Deflate = 8, Bzip2 = 12, Xz = 95, Zstd = 93 };
enum class Encryption : uint16_t { None = 0, Traditional = 1, Aes128 = 0x101, Aes192 = 0x102, Aes256 = 0x103 };
struct EntryWriteOptions {
    Compression compression = Compression::Deflate;
    uint8_t level = 6;
    Encryption encryption = Encryption::None;
    std::string password;
};
struct ZipWriteOptions {
    uint64_t maxStagedBytes = uint64_t{32} << 30;
};
struct ZipCapabilities {
    std::vector<Compression> readCompression, writeCompression;
    std::vector<Encryption> readEncryption, writeEncryption;
};
CC_DLL ZipCapabilities zipCapabilities();
}
