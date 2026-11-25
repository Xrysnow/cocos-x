#pragma once
#include "io/zip/ZipReader.h"
#include <functional>
namespace cc::archive
{
struct ExtractOptions {
    EntryReadOptions entry;
    uint64_t maxTotalBytes = uint64_t{8} << 30;
    uint64_t maxEntries = 100'000;
    std::function<bool()> cancelled;
};
CC_DLL io::Status extractEntry(const ZipReader&, EntryId, io::Stream&, const ExtractOptions& = {});
CC_DLL io::Status extractTree(const ZipReader&, std::string_view newDirectory, const ExtractOptions& = {});
}
