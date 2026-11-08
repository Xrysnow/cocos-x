#pragma once

#include "base/filesystem.h"
#include <string_view>
#include <stdexcept>
#include <system_error>

namespace cocos2d::detail
{
// Writer-side preparation only. FileUtils path queries must never call this.
inline bool ensureNativeDirectory(std::string_view directory)
{
    if (directory.empty() || directory.find('\0') != std::string_view::npos)
        return false;
    try
    {
        const auto path = stdfs::u8path(directory.begin(), directory.end());
        std::error_code error;
        stdfs::create_directories(path, error);
        if (error)
            return false;
        return stdfs::is_directory(path, error) && !error;
    }
    catch (const std::system_error&)
    {
        // Includes filesystem_error from UTF-8/native path conversion.
        return false;
    }
    catch (const std::range_error&)
    {
        return false;
    }
}

inline bool ensureNativeParentDirectory(std::string_view filename)
{
    if (filename.empty() || filename.find('\0') != std::string_view::npos)
        return false;
    try
    {
        const auto parent = stdfs::u8path(filename.begin(), filename.end()).parent_path();
        if (parent.empty())
            return true;
        std::error_code error;
        stdfs::create_directories(parent, error);
        if (error)
            return false;
        return stdfs::is_directory(parent, error) && !error;
    }
    catch (const std::system_error&)
    {
        return false;
    }
    catch (const std::range_error&)
    {
        return false;
    }
}
} // namespace cocos2d::detail
