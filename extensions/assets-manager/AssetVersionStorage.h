#pragma once

#include "io/zip/ZipExtract.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>

namespace cc::extension::asset_storage
{
namespace fs = std::filesystem;

inline std::string utf8(const fs::path& path)
{
    auto value = path.generic_u8string();
    return {reinterpret_cast<const char*>(value.data()), value.size()};
}

inline std::string searchPath(const fs::path& path)
{
    auto result = utf8(path);
    if (!result.empty() && result.back() != '/')
        result.push_back('/');
    return result;
}

inline fs::path relativeAssetPath(std::string_view name)
{
    if (name.empty() || name.back() == '/' || name.find_first_of("\\:") != name.npos ||
        name.find('\0') != name.npos)
        return {};
    auto path = fs::u8path(name);
    if (path.has_root_path())
        return {};
    for (const auto& component : path)
    {
        auto text = utf8(component);
        if (text.empty() || text.back() == '.' || text.back() == ' ' ||
            text.find_first_of("<>\"|?*") != text.npos ||
            std::any_of(text.begin(), text.end(), [](unsigned char character) { return character < 32; }))
            return {};
        for (auto& character : text)
        {
            if (character >= 'a' && character <= 'z')
                character -= 'a' - 'A';
        }
        const auto base = std::string_view(text).substr(0, text.find('.'));
        if (base == "CON" || base == "PRN" || base == "AUX" || base == "NUL" ||
            base == "CONIN$" || base == "CONOUT$" ||
            ((base.starts_with("COM") || base.starts_with("LPT")) && base.size() == 4 &&
             base.back() >= '1' && base.back() <= '9'))
            return {};
    }
    return path;
}

inline fs::path selectedVersion(const fs::path& store)
{
    std::ifstream marker(store / "active", std::ios::binary);
    char identifier[96]{};
    marker.getline(identifier, sizeof(identifier));
    const std::string_view name(identifier);
    if (!marker || !name.starts_with("version-") || name.size() == 8 ||
        name.substr(8).find_first_not_of("0123456789-") != name.npos)
        return {};
    const auto path = store / identifier / "content";
    std::error_code ec;
    return fs::is_directory(fs::symlink_status(path, ec)) && !ec ? path : fs::path{};
}

class StagedVersion final
{
public:
    explicit StagedVersion(const fs::path& store) : _store(store)
    {
        if (_store.empty())
            return;
        std::error_code ec;
        fs::create_directories(_store, ec);
        if (ec || !fs::is_directory(fs::symlink_status(_store, ec)) || ec)
            return;
        static std::atomic<uint64_t> sequence{0};
        const auto now = std::chrono::system_clock::now().time_since_epoch().count();
        for (unsigned attempt = 0; attempt < 32; ++attempt)
        {
            const auto name = "version-" + std::to_string(now) + '-' + std::to_string(sequence++);
            const auto path = _store / name;
            if (fs::create_directory(path, ec))
            {
                _path = path;
                break;
            }
            if (ec && ec != std::errc::file_exists)
                break;
        }
    }

    ~StagedVersion()
    {
        if (!_published && !_path.empty())
        {
            std::error_code ignored;
            fs::remove_all(_path, ignored);
        }
    }

    StagedVersion(const StagedVersion&) = delete;
    StagedVersion& operator=(const StagedVersion&) = delete;
    explicit operator bool() const { return !_path.empty(); }
    fs::path content() const { return _path / "content"; }

    bool publish()
    {
        std::error_code ec;
        if (_path.empty() || !fs::is_directory(fs::symlink_status(content(), ec)) || ec)
            return false;
        const auto activation = _path / "activation";
        std::ofstream marker(activation, std::ios::binary | std::ios::trunc);
        marker << utf8(_path.filename()) << '\n';
        marker.close();
        if (!marker)
            return false;
        fs::rename(activation, _store / "active", ec);
        _published = !ec;
        return _published;
    }

private:
    fs::path _store;
    fs::path _path;
    bool _published = false;
};

inline io::Status extractDownload(std::string_view archivePath, const fs::path& destination)
{
    auto reader = archive::ZipReader::openFile(archivePath);
    if (!reader)
        return io::Status::failure(reader.error);
    return archive::extractTree(*reader.value, utf8(destination));
}

inline bool copyAsset(const fs::path& source, const fs::path& destination)
{
    std::error_code ec;
    if (!fs::is_regular_file(fs::symlink_status(source, ec)) || ec)
        return false;
    fs::create_directories(destination.parent_path(), ec);
    return !ec && fs::copy_file(source, destination, fs::copy_options::overwrite_existing, ec) && !ec;
}

inline bool overlayTree(const fs::path& source, const fs::path& destination,
                        const fs::path& excluded = {}, const fs::path& otherExcluded = {})
{
    std::error_code ec;
    if (!fs::is_directory(fs::symlink_status(source, ec)) || ec)
        return false;
    fs::create_directories(destination, ec);
    if (ec)
        return false;

    for (fs::recursive_directory_iterator entry(source, ec), end; !ec && entry != end; entry.increment(ec))
    {
        const auto path = entry->path();
        if (entry.depth() == 0 && (path.filename() == excluded || path.filename() == otherExcluded))
        {
            entry.disable_recursion_pending();
            continue;
        }
        const auto target = destination / path.lexically_relative(source);
        const auto type = entry->symlink_status(ec);
        if (ec)
            return false;
        if (fs::is_directory(type))
            fs::create_directory(target, ec);
        else if (!fs::is_regular_file(type) || !copyAsset(path, target))
            return false;
    }
    return !ec;
}
}
