#pragma once

#include "platform/CCPlatformMacros.h"
#include <cstdint>
#include <string>
#include <string_view>

NS_CC_BEGIN

/** Retention requirements for application-owned physical directories. */
enum class AppDirectory
{
    PersistentData,
    TransientData
};

enum class DirectoryStatus
{
    Ok,
    NotInitialized,
    InvalidArgument,
    InUse,
    Unavailable,
    PermissionDenied,
    NotDirectory,
    IoError,
    Unsupported
};

struct CC_DLL DirectoryResult
{
    DirectoryStatus status = DirectoryStatus::Unavailable;
    std::string path;          ///< Nonempty only on success; UTF-8, absolute, ending in '/'.
    std::string nativeDomain;  ///< For example win32, hresult, errno, cocoa or jni.
    std::int64_t nativeCode = 0;
};

struct CC_DLL AppDirectoryConfig
{
    /**
     * Uses the host's CC_APP_DIRECTORY_DEFAULT_ID build setting, or the generic
     * org.cocos2d.application fallback. Every product should supply its own stable ID.
     */
    AppDirectoryConfig();
    /** 1-200 ASCII lowercase letters/digits/'-'/'_', in nonempty dot-separated components; no device names. */
    std::string appId;
    /**
     * Empty uses the platform default; otherwise the final absolute root, with no
     * '.'/'..' or empty interior components. A trailing separator is normalized.
     * Windows permits drive-absolute and ordinary UNC paths, excluding devices.
     * POSIX paths use '/' and exclude backslashes and implementation-defined '//'.
     * The roots must not overlap; lexical checks cannot identify every filesystem alias.
     */
    std::string persistentDataOverride;
    std::string transientDataOverride;
};

// Shared process-lifetime service behind FileUtils' nonvirtual forwarding API.
// Kept independent of resource delegates, Director and FileUtils destruction.
namespace detail
{
CC_DLL DirectoryStatus configureAppDirectories(const AppDirectoryConfig& config);
CC_DLL DirectoryResult queryAppDirectory(AppDirectory kind);
CC_DLL DirectoryResult ensureAppDirectory(AppDirectory kind, std::string_view relativeSubdirectory);
}

NS_CC_END
