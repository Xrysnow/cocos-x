#include "platform/SystemInfoInternal.h"

#include <filesystem>
#include <system_error>

namespace cc {
namespace system_info {

void missing(ValueMap& data, const char* field, const char* reason) {
    auto [it, inserted] = data.try_emplace("missing", ValueMap{});
    it->second.asValueMap()[field] = reason;
}

ValueMap failure(const char* code, const char* context, int64_t nativeCode) {
    ValueMap result;
    result["ok"] = false;
    result["error"] = code;
    result["context"] = context;
    result["nativeCode"] = nativeCode;
    return result;
}

ValueMap finish(ValueMap data, std::initializer_list<const char*> fields) {
    if (data.contains("error")) return data;
    data["ok"] = true;
    auto [it, inserted] = data.try_emplace("missing", ValueMap{});
    auto& reasons = it->second.asValueMap();
    for (const auto field : fields) {
        if (!data.contains(field) && !reasons.contains(field)) reasons[field] = "unknown";
    }
    return data;
}
} // namespace system_info

ValueMap SystemInfo::getComputer(bool identifiers) {
    auto result = system_info::readComputer(identifiers);
    if (!identifiers && !result.contains("error")) {
        for (const auto key : {"serialNumber", "uuid"}) {
            result.erase(key);
            system_info::missing(result, key, "withheld");
        }
    }
    return system_info::finish(std::move(result), {"vendor", "model", "family", "version", "sku",
                                                   "chassis", "serialNumber", "uuid", "socModel"});
}

ValueMap SystemInfo::getCpu() {
    return system_info::finish(system_info::readCpu(), {"vendor", "model", "physicalCores", "logicalCores",
                                                         "packages", "clusters", "cores", "flags"});
}

ValueMap SystemInfo::getOs() {
    return system_info::finish(system_info::readOs(), {"family", "name", "version", "marketingName",
                                                        "build", "kernel", "architecture", "bits", "source"});
}

ValueMap SystemInfo::getMemoryUsage() {
    return system_info::finish(system_info::readMemory(), {"total", "free", "available"});
}

ValueMap SystemInfo::getUptime() {
    return system_info::finish(system_info::readUptime(), {"seconds", "bootTime"});
}

ValueMap SystemInfo::getDiskSpace(std::string_view path) {
    namespace fs = std::filesystem;
    if (path.empty() || path.find('\0') != path.npos || path.find("://") != path.npos)
        return system_info::failure("invalidArgument", "native filesystem path required");
    std::error_code ec;
    fs::space_info space{};
    try {
        auto target = fs::u8path(path);
        const auto status = fs::status(target, ec);
        if (!ec && !fs::exists(status)) ec = std::make_error_code(std::errc::no_such_file_or_directory);
        if (!ec && !fs::is_directory(status)) {
            target = fs::canonical(target, ec).parent_path();
        }
        if (!ec) space = fs::space(target, ec);
    } catch (const fs::filesystem_error& e) {
        ec = e.code();
    }
    if (ec) {
        const auto code = ec == std::errc::no_such_file_or_directory ? "notFound"
                        : ec == std::errc::permission_denied ? "permissionDenied" : "ioError";
        return system_info::failure(code, "filesystem space", ec.value());
    }
    ValueMap result;
    result["capacity"] = static_cast<uint64_t>(space.capacity);
    result["free"] = static_cast<uint64_t>(space.free);
    result["available"] = static_cast<uint64_t>(space.available);
    return system_info::finish(std::move(result), {});
}

} // namespace cc
