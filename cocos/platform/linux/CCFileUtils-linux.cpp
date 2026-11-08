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
#include <cstring>
#include <cstdlib>

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

static bool queryExecutablePath(std::string& path)
{
    std::vector<char> buffer(256);
    for (;;)
    {
        const ssize_t length = readlink("/proc/self/exe", buffer.data(), buffer.size());
        if (length <= 0)
            return false;
        if (static_cast<size_t>(length) < buffer.size())
        {
            path.assign(buffer.data(), static_cast<size_t>(length));
            return path.find_last_of('/') != std::string::npos;
        }
        if (buffer.size() > buffer.max_size() / 2)
            return false;
        buffer.resize(buffer.size() * 2);
    }
}

bool FileUtilsLinux::init()
{
    DECLARE_GUARD;
    std::string appPath;
    if (!queryExecutablePath(appPath))
        return false;
    _defaultResRootPath = appPath.substr(0, appPath.find_last_of('/') + 1);
    _defaultResRootPath += CC_PC_RESOURCES_DIR;
    return FileUtils::init();
}

bool FileUtilsLinux::queryDefaultWritablePath(std::string& path) const
{
    const auto validRoot = [](const char* value) {
        return value && value[0] == '/' && StringUtils::isLegalUTF8String(value, strlen(value));
    };
    // Keep the legacy configuration-directory layout; invalid/empty XDG values are ignored.
    const char* xdg = getenv("XDG_CONFIG_HOME");
    if (validRoot(xdg))
        path = xdg;
    else
    {
        const char* home = getenv("HOME");
        if (!validRoot(home))
            return false;
        path = home;
        path += "/.config";
    }
    std::string executable;
    if (!queryExecutablePath(executable))
        return false;
    path += executable.substr(executable.find_last_of('/'));
    return true;
}

bool FileUtilsLinux::isFileExistInternal(std::string_view path) const
{
    struct stat sts;
    return (stat(path.data(), &sts) == 0) && S_ISREG(sts.st_mode);
}

NS_CC_END
