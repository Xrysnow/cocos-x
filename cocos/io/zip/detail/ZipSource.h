#pragma once
#include "io/zip/ZipTypes.h"
#include <filesystem>
#include <mutex>
#include <zip.h>

namespace cc::archive::detail
{
namespace fs = std::filesystem;
using io::ErrorCode;
using io::Result;
using io::Status;
using io::StreamError;
StreamError zipError(int code);
StreamError fileError(std::error_code error);
Result<std::string> cleanName(std::string_view name, bool directory = false);
bool portableComponent(std::string_view name);
std::string utf8(const fs::path& path);
struct FileLease {
    fs::path path;
    bool writer;
};
Result<std::shared_ptr<FileLease>> acquire(std::string_view name, bool writer);
struct TemporaryDirectory {
    fs::path path;
    ~TemporaryDirectory();
    static Result<std::shared_ptr<TemporaryDirectory>> create(const fs::path& parent);
};
Status publish(const fs::path& source, const fs::path& destination, bool replace);
Status checkDirectory(zip_source_t* source, uint64_t length, const ZipReadOptions& limits, bool& strict);
zip_source_t* streamSource(io::StreamPtr input, uint64_t length, zip_error_t* error);
}
