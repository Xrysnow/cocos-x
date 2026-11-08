/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2021-2022 Bytedance Inc.

 https://axmolengine.github.io/

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
#include "platform/win32/CCFileUtils-win32.h"
#include "platform/CCCommon.h"
#include "base/ccUTF8.h"
#include <Shlobj.h>
#include <cstdlib>
#include <memory>
#include <regex>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "ntcvt/ntcvt.hpp"

#define DECLARE_GUARD (void)0  // std::lock_guard<std::recursive_mutex> mutexGuard(_mutex)

NS_CC_BEGIN

#define CC_MAX_PATH 512

// The root path of resources, the character encoding is UTF-8.
// UTF-8 is the only encoding supported by axmol API by default.
static std::string s_workingDir;
static std::string s_exeDir;

static bool utf16PathToUtf8(std::wstring_view path, std::string& text)
{
    if (!StringUtils::UTF16ToUTF8(
            std::u16string_view{reinterpret_cast<const char16_t*>(path.data()), path.size()}, text))
        return false;
    std::replace(text.begin(), text.end(), '\\', '/');
    return true;
}

// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
static std::string convertPathFormatToUnixStyle(const std::string_view& path)
{
    std::string ret{path};
    int len = ret.length();
    std::replace(ret.begin(), ret.end(), '\\', '/');
    return ret;
}

static std::string convertPathFormatToWinStyle(const std::string_view& path)
{
    std::string ret{path};
    int len = ret.length();
    std::replace(ret.begin(), ret.end(), '/', '\\');
    return ret;
}

static bool queryExecutablePath(std::wstring& path)
{
    std::vector<WCHAR> buffer(512);
    for (;;)
    {
        const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (!length)
            return false;
        if (length < buffer.size())
        {
            path.assign(buffer.data(), length);
            return true;
        }
        if (buffer.size() >= 32768)
            return false;
        buffer.resize(std::min<size_t>(buffer.size() * 2, 32768));
    }
}

static bool _checkWorkingPath()
{
    if (s_workingDir.empty())
    {
        std::vector<WCHAR> buffer(512);
        for (;;)
        {
            const DWORD length = GetCurrentDirectoryW(static_cast<DWORD>(buffer.size()), buffer.data());
            if (!length)
                return false;
            if (length < buffer.size())
            {
                if (!utf16PathToUtf8(std::wstring_view{buffer.data(), length}, s_workingDir))
                    return false;
                if (s_workingDir.back() != '/')
                    s_workingDir += '/';
                break;
            }
            buffer.resize(length);
        }
    }
    return true;
}

static bool _checkExePath()
{
    if (s_exeDir.empty())
    {
        std::wstring executable;
        if (!queryExecutablePath(executable))
            return false;
        const auto separator = executable.find_last_of(L"\\/");
        if (separator == std::wstring::npos)
            return false;
        if (!utf16PathToUtf8(std::wstring_view{executable}.substr(0, separator + 1), s_exeDir))
            return false;
    }
    return true;
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsWin32();
        if (!s_sharedFileUtils->init())
        {
            delete s_sharedFileUtils;
            s_sharedFileUtils = nullptr;
            CCLOG("ERROR: Could not init CCFileUtilsWin32");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsWin32::FileUtilsWin32() {}

bool FileUtilsWin32::init()
{
    if (!_checkWorkingPath() || !_checkExePath())
        return false;

    bool startedFromSelfLocation = s_workingDir == s_exeDir;
    if (!startedFromSelfLocation || !isDirectoryExistInternal(CC_PC_RESOURCES_DIR))
        _defaultResRootPath = s_workingDir;
    else
    {
        _defaultResRootPath.reserve(s_exeDir.size() + CC_PC_RESOURCES_DIR_LEN);
        _defaultResRootPath.append(s_exeDir).append(CC_PC_RESOURCES_DIR, CC_PC_RESOURCES_DIR_LEN);
    }

    bool bRet = FileUtils::init();

    // make sure any path relative to exe dir can be found when app working directory location not exe path
    if (!startedFromSelfLocation)
        addSearchPath(s_exeDir);

    return bRet;
}

bool FileUtilsWin32::isDirectoryExistInternal(std::string_view dirPath) const
{
    uint32_t fAttrib = GetFileAttributesW(ntcvt::from_chars(dirPath).c_str());
    return (fAttrib != INVALID_FILE_ATTRIBUTES && (fAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileUtilsWin32::isFileExistInternal(std::string_view strFilePath) const
{
    DWORD attr = GetFileAttributesW(ntcvt::from_chars(strFilePath).c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

FileUtils::Status FileUtilsWin32::getContents(std::string_view filename, ResizableBuffer* buffer) const
{
    if (filename.empty())
        return FileUtils::Status::NotExists;

    // read the file from hardware
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);

    HANDLE fileHandle = ::CreateFileW(ntcvt::from_chars(fullPath).c_str(), GENERIC_READ,
                                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
    if (fileHandle == INVALID_HANDLE_VALUE)
        return FileUtils::Status::OpenFailed;

    // ResizableBuffer::resize can throw; never leak the handle on that path.
    struct CloseFile
    {
        HANDLE handle;
        ~CloseFile() { ::CloseHandle(handle); }
    } closeFile{fileHandle};
    DWORD hi = 0;
    auto size = ::GetFileSize(fileHandle, &hi);
    if (size == INVALID_FILE_SIZE && ::GetLastError() != NO_ERROR)
        return FileUtils::Status::ObtainSizeFailed;
    if (hi > 0)
    {
        return FileUtils::Status::TooLarge;
    }
    // don't read file content if it is empty
    if (size == 0)
    {
        buffer->resize(0);
        return FileUtils::Status::OK;
    }

    buffer->resize(size);
    DWORD sizeRead = 0;
    BOOL successed = ::ReadFile(fileHandle, buffer->buffer(), size, &sizeRead, nullptr);

    if (!successed || sizeRead != size)
    {
        CCLOG("Get data from file(%s) failed, error code is %s", filename.data(),
              std::to_string(::GetLastError()).data());
        buffer->resize(sizeRead);
        return FileUtils::Status::ReadFailed;
    }
    return FileUtils::Status::OK;
}

std::string FileUtilsWin32::getPathForFilename(std::string_view filename,
                                               std::string_view searchPath) const
{
    std::string unixFileName            = convertPathFormatToUnixStyle(filename);
    std::string unixSearchPath          = convertPathFormatToUnixStyle(searchPath);

    return FileUtils::getPathForFilename(unixFileName, unixSearchPath);
}

std::string FileUtilsWin32::getFullPathForFilenameWithinDirectory(std::string_view strDirectory,
                                                                  std::string_view strFilename) const
{
    std::string unixDirectory = convertPathFormatToUnixStyle(strDirectory);
    std::string unixFilename  = convertPathFormatToUnixStyle(strFilename);

    return FileUtils::getFullPathForFilenameWithinDirectory(unixDirectory, unixFilename);
}

int64_t FileUtilsWin32::getFileSize(std::string_view filepath) const
{
    if (filepath.empty())
        return -1;
    WIN32_FILE_ATTRIBUTE_DATA attrs = {0};
    if (GetFileAttributesExW(ntcvt::from_chars(filepath).c_str(), GetFileExInfoStandard, &attrs) &&
        !(attrs.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        return static_cast<long long>(attrs.nFileSizeHigh) << 32 | static_cast<unsigned long long>(attrs.nFileSizeLow);
    return -1;
}

bool FileUtilsWin32::queryDefaultWritablePath(std::string& path) const
{
    std::wstring executable;
    if (!queryExecutablePath(executable))
        return false;
    const auto separator = executable.find_last_of(L"\\/");
    if (separator == std::wstring::npos)
        return false;
    PWSTR appData = nullptr;
    const HRESULT status = SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DONT_VERIFY, nullptr, &appData);
    const std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> appDataOwner(appData, &CoTaskMemFree);
    std::wstring directory;
    if (SUCCEEDED(status) && appData && *appData)
    {
        directory = appData;
        if (directory.back() != L'\\' && directory.back() != L'/')
            directory += L'\\';
        auto name = executable.substr(separator + 1);
        const auto extension = name.find_last_of(L'.');
        if (extension != std::wstring::npos)
            name.resize(extension);
        directory += name;
    }
    else
        directory = executable.substr(0, separator + 1); // Preserve the legacy query-failure fallback.
    return utf16PathToUtf8(directory, path) && !path.empty();
}

std::string FileUtilsWin32::getSuitableFOpen(std::string_view path)
{
    return ntcvt::from_chars(ntcvt::from_chars(path), CP_ACP);
}

bool FileUtilsWin32::renameFile(std::string_view oldfullpath, std::string_view newfullpath) const
{
    CCASSERT(!oldfullpath.empty(), "Invalid path");
    CCASSERT(!newfullpath.empty(), "Invalid path");

    std::wstring _wNew = ntcvt::from_chars(newfullpath);
    std::wstring _wOld = ntcvt::from_chars(oldfullpath);

    if (FileUtils::getInstance()->isFileExist(newfullpath))
    {
        if (!DeleteFile(_wNew.c_str()))
        {
            CCLOGERROR("Fail to delete file %s !Error code is 0x%x", newfullpath.data(), GetLastError());
        }
    }

    if (MoveFileW(_wOld.c_str(), _wNew.c_str()))
    {
        return true;
    }
    else
    {
        CCLOGERROR("Fail to rename file %s to %s !Error code is 0x%x", oldfullpath.data(), newfullpath.data(),
                   GetLastError());
        return false;
    }
}

bool FileUtilsWin32::renameFile(std::string_view path, std::string_view oldname, std::string_view name) const
{
    CCASSERT(!path.empty(), "Invalid path");
    std::string oldPath{path};
    oldPath += oldname;
    std::string newPath{path};
    newPath += name;

    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");

    return renameFile(_old, _new);
}

bool FileUtilsWin32::createDirectory(std::string_view dirPath) const
{
    CCASSERT(!dirPath.empty(), "Invalid path");

    if (isDirectoryExist(dirPath))
        return true;

    std::wstring path = ntcvt::from_chars(dirPath);

    // Split the path
    size_t start = 0;
    size_t found = path.find_first_of(L"/\\", start);
    std::wstring subpath;
    std::vector<std::wstring> dirs;

    if (found != std::wstring::npos)
    {
        while (true)
        {
            subpath = path.substr(start, found - start + 1);
            if (!subpath.empty())
                dirs.emplace_back(subpath);
            start = found + 1;
            found = path.find_first_of(L"/\\", start);
            if (found == std::wstring::npos)
            {
                if (start < path.length())
                {
                    dirs.emplace_back(path.substr(start));
                }
                break;
            }
        }
    }

    if ((GetFileAttributesW(path.c_str())) == INVALID_FILE_ATTRIBUTES)
    {
        subpath = L"";
        for (unsigned int i = 0, size = dirs.size(); i < size; ++i)
        {
            subpath += dirs[i];

            std::string utf8Path = ntcvt::from_chars(subpath);
            if (!isDirectoryExist(utf8Path))
            {
                BOOL ret = CreateDirectoryW(subpath.c_str(), NULL);
                if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
                {
                    CCLOGERROR("Fail create directory %s !Error code is 0x%x", utf8Path.c_str(), GetLastError());
                    return false;
                }
            }
        }
    }
    return true;
}

bool FileUtilsWin32::removeFile(std::string_view filepath) const
{
    std::string win32path = convertPathFormatToWinStyle(filepath);

    if (DeleteFileW(ntcvt::from_chars(win32path).c_str()))
    {
        return true;
    }
    else
    {
        CCLOGERROR("Fail remove file %s !Error code is 0x%x", filepath.data(), GetLastError());
        return false;
    }
}

bool FileUtilsWin32::removeDirectory(std::string_view dirPath) const
{
    std::string dirPathCopy{dirPath};
    if (!dirPath.empty() && dirPath[dirPath.length() - 1] != '/' && dirPath[dirPath.length() - 1] != '\\')
    {
        dirPathCopy.push_back('/');
    }
    std::wstring wpath = ntcvt::from_chars(dirPathCopy);
    std::wstring files = wpath + L"*.*";
    WIN32_FIND_DATA wfd;
    HANDLE search = FindFirstFileEx(files.c_str(), FindExInfoStandard, &wfd, FindExSearchNameMatch, NULL, 0);
    bool ret      = true;
    if (search != INVALID_HANDLE_VALUE)
    {
        BOOL find = true;
        while (find)
        {
            // Need check string . and .. for delete folders and files begin name.
            std::wstring fileName = wfd.cFileName;
            if (fileName != L"." && fileName != L"..")
            {
                std::wstring temp = wpath + wfd.cFileName;
                if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    temp += '/';
                    ret = ret && this->removeDirectory(ntcvt::from_chars(temp));
                }
                else
                {
                    SetFileAttributesW(temp.c_str(), FILE_ATTRIBUTE_NORMAL);
                    ret = ret && DeleteFileW(temp.c_str());
                }
            }
            find = FindNextFile(search, &wfd);
        }
        FindClose(search);
    }
    if (ret && RemoveDirectoryW(wpath.c_str()))
    {
        return true;
    }
    return false;
}

NS_CC_END
