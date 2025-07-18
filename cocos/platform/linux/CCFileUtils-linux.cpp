/****************************************************************************
Copyright (c) 2011      Laschweinski
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
#include "platform/linux/CCFileUtils-linux.h"
#include "platform/linux/CCApplication-linux.h"
#include "platform/CCCommon.h"
#include "base/ccMacros.h"
#include "base/ccUTF8.h"
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>
#include <cerrno>

using namespace std;

#define DECLARE_GUARD (void)0  // std::lock_guard<std::recursive_mutex> mutexGuard(_mutex)

NS_CC_BEGIN

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsLinux();
        if (!s_sharedFileUtils->init())
        {
            delete s_sharedFileUtils;
            s_sharedFileUtils = nullptr;
            CCLOG("ERROR: Could not init CCFileUtilsLinux");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsLinux::FileUtilsLinux() {}

bool FileUtilsLinux::init()
{
    DECLARE_GUARD;
    // get application path
    char fullpath[256] = {0};
    ssize_t length     = readlink("/proc/self/exe", fullpath, sizeof(fullpath) - 1);

    if (length <= 0)
    {
        return false;
    }

    fullpath[length]    = '\0';
    std::string appPath = fullpath;
    _defaultResRootPath = appPath.substr(0, appPath.find_last_of('/') + 1);
    _defaultResRootPath += CC_PC_RESOURCES_DIR;

    // Set writable path to $XDG_CONFIG_HOME or ~/.config/<app name>/ if $XDG_CONFIG_HOME not exists.
    const char* xdg_config_path = getenv("XDG_CONFIG_HOME");
    std::string xdgConfigPath;
    if (xdg_config_path == NULL)
    {
        xdgConfigPath = getenv("HOME");
        xdgConfigPath += "/.config";
    }
    else
    {
        xdgConfigPath = xdg_config_path;
    }
    _writablePath = xdgConfigPath;
    _writablePath += appPath.substr(appPath.find_last_of('/'));
    _writablePath += "/";

    return FileUtils::init();
}

string FileUtilsLinux::getWritablePath() const
{
    DECLARE_GUARD;
    return getNativeWritableAbsolutePath();
}

std::string FileUtilsLinux::getNativeWritableAbsolutePath() const
{
    struct stat st;
    stat(_writablePath.c_str(), &st);
    if (!S_ISDIR(st.st_mode))
    {
        mkdir(_writablePath.c_str(), 0744);
    }

    return _writablePath;
}

void FileUtilsLinux::setWritablePath(std::string_view writablePath)
{
    DECLARE_GUARD;
    struct stat st;
    stat(writablePath.data(), &st);
    if (!S_ISDIR(st.st_mode) || access(writablePath.data(), W_OK) != 0)
        return;
    _writablePath = writablePath;
}

bool FileUtilsLinux::isFileExistInternal(std::string_view path) const
{
    struct stat sts;
    return (stat(path.data(), &sts) == 0) && S_ISREG(sts.st_mode);
}

NS_CC_END
