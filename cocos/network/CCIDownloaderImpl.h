/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

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

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "base/CCConsole.h"

// #define CC_DOWNLOADER_DEBUG
#if defined(CC_DOWNLOADER_DEBUG) || defined(_DEBUG)
    #define DLLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)
#else
    #define DLLOG(...) \
        do             \
        {              \
        } while (0)
#endif

NS_CC_BEGIN

namespace network
{
class DownloadTask;

class CC_DLL IDownloadTask
{
public:
    virtual ~IDownloadTask() {}
    virtual void cancel() {}
};

class IDownloaderImpl
{
public:
    virtual ~IDownloaderImpl() {}

    std::function<void(const DownloadTask& task,
                       std::function<int64_t(void* buffer, int64_t len)>& transferDataToBuffer)>
        onTaskProgress;

    std::function<void(const DownloadTask& task,
                       int errorCode,
                       int errorCodeInternal,
                       std::string_view errorStr,
                       std::vector<unsigned char>& data)>
        onTaskFinish;

    virtual void startTask(std::shared_ptr<DownloadTask>& task) = 0;
};

}  // namespace network
NS_CC_END  // namespace cocos2d
