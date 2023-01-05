/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2020 C4games Ltd

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
#include "platform/android/CCFileUtils-android.h"
#include "platform/CCCommon.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#include "base/ZipUtils.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "yasio/cxx17/string_view.hpp"

#define LOG_TAG "CCFileUtils-android.cpp"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define ASSETS_FOLDER_NAME "assets/"
#define ASSETS_FOLDER_NAME_LENGTH 7

using namespace std;

#define DECLARE_GUARD (void)0  // std::lock_guard<std::recursive_mutex> mutexGuard(_mutex)

NS_CC_BEGIN

AAssetManager* FileUtilsAndroid::assetmanager = nullptr;
ZipFile* FileUtilsAndroid::obbfile            = nullptr;

void FileUtilsAndroid::setassetmanager(AAssetManager* a)
{
    if (nullptr == a)
    {
        LOGD("setassetmanager : received unexpected nullptr parameter");
        return;
    }

    cocos2d::FileUtilsAndroid::assetmanager = a;
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsAndroid();
        if (!s_sharedFileUtils->init())
        {
            delete s_sharedFileUtils;
            s_sharedFileUtils = nullptr;
            CCLOG("ERROR: Could not init CCFileUtilsAndroid");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsAndroid::FileUtilsAndroid() {}

FileUtilsAndroid::~FileUtilsAndroid()
{
    if (obbfile)
    {
        delete obbfile;
        obbfile = nullptr;
    }
}

bool FileUtilsAndroid::init()
{
    DECLARE_GUARD;

    _defaultResRootPath = ASSETS_FOLDER_NAME;

    std::string assetsPath(getApkPath());
    if (assetsPath.find("/obb/") != std::string::npos)
    {
        obbfile = new ZipFile(assetsPath);
    }

    return FileUtils::init();
}

bool FileUtilsAndroid::isFileExistInternal(std::string_view strFilePath) const
{

    DECLARE_GUARD;

    if (strFilePath.empty())
    {
        return false;
    }

    bool bFound = false;

    // Check whether file exists in apk.
    if (strFilePath[0] != '/')
    {
        const char* s = strFilePath.data();

        // Found "assets/" at the beginning of the path and we don't want it
        if (strFilePath.find(_defaultResRootPath) == 0)
            s += _defaultResRootPath.length();

        if (obbfile && obbfile->fileExists(s))
        {
            bFound = true;
        }
        else if (FileUtilsAndroid::assetmanager)
        {
            AAsset* aa = AAssetManager_open(FileUtilsAndroid::assetmanager, s, AASSET_MODE_UNKNOWN);
            if (aa)
            {
                bFound = true;
                AAsset_close(aa);
            }
            else
            {
                // CCLOG("[AssetManager] ... in APK %s, found = false!", strFilePath.c_str());
            }
        }
    }
    else
    {
        struct stat st;
        if (::stat(strFilePath.data(), &st) == 0)
            bFound = S_ISREG(st.st_mode);
    }
    return bFound;
}

bool FileUtilsAndroid::isDirectoryExistInternal(std::string_view dirPath) const
{
    if (dirPath.empty())
    {
        return false;
    }

    std::string_view path;
    std::string dirPathCopy;
    if (dirPath[dirPath.length() - 1] == '/')
    {
        dirPathCopy.assign(dirPath.data(), dirPath.length() - 1);
        path = dirPathCopy;
    }
    else
        path = dirPath;

    const char* s = path.data();

    // find absolute path in flash memory
    if (s[0] == '/')
    {
        CCLOG("find in flash memory dirPath(%s)", s);
        struct stat st;
        if (stat(s, &st) == 0)
        {
            return S_ISDIR(st.st_mode);
        }
    }
    else
    {

        // find it in apk's assets dir
        // Found "assets/" at the beginning of the path and we don't want it
        CCLOG("find in apk dirPath(%s)", s);
        if (dirPath.find(ASSETS_FOLDER_NAME) == 0)
        {
            s += ASSETS_FOLDER_NAME_LENGTH;
        }

        if (FileUtilsAndroid::assetmanager)
        {
            AAssetDir* aa = AAssetManager_openDir(FileUtilsAndroid::assetmanager, s);
            if (aa && AAssetDir_getNextFileName(aa))
            {
                AAssetDir_close(aa);
                return true;
            }
        }
    }

    return false;
}

bool FileUtilsAndroid::isAbsolutePath(std::string_view strPath) const
{
    DECLARE_GUARD;
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    return (strPath[0] == '/' || strPath.find(_defaultResRootPath) == 0);
}

int64_t FileUtilsAndroid::getFileSize(std::string_view filepath) const
{
    DECLARE_GUARD;
    int64_t size = FileUtils::getFileSize(filepath);
    if (size != -1)
    {
        return size;
    }

    if (FileUtilsAndroid::assetmanager)
    {
        std::string_view path;
        std::string relativePath;
        if (cxx20::starts_with(filepath, _defaultResRootPath))
        {
            path = relativePath = filepath.substr(_defaultResRootPath.size());
        }
        else
            path = filepath;

        AAsset* asset = AAssetManager_open(FileUtilsAndroid::assetmanager, path.data(), AASSET_MODE_UNKNOWN);
        if (asset)
        {
            size = AAsset_getLength(asset);
            AAsset_close(asset);
        }
    }

    return size;
}

std::vector<std::string> FileUtilsAndroid::listFiles(std::string_view dirPath) const
{

    if (!dirPath.empty() && dirPath[0] == '/')
        return FileUtils::listFiles(dirPath);

    std::vector<std::string> fileList;
    string fullPath = fullPathForDirectory(dirPath);

    static const std::string apkprefix("assets/");
    std::string relativePath;
    size_t position = fullPath.find(apkprefix);
    if (0 == position)
    {
        // "assets/" is at the beginning of the path and we don't want it
        relativePath += fullPath.substr(apkprefix.size());
    }
    else
    {
        relativePath = fullPath;
    }

    if (obbfile)
        return obbfile->listFiles(relativePath);

    if (nullptr == assetmanager)
    {
        LOGD("... FileUtilsAndroid::assetmanager is nullptr");
        return fileList;
    }

    if (relativePath[relativePath.length() - 1] == '/')
    {
        relativePath.erase(relativePath.length() - 1);
    }

    auto* dir = AAssetManager_openDir(assetmanager, relativePath.c_str());
    if (nullptr == dir)
    {
        LOGD("... FileUtilsAndroid::failed to open dir %s", relativePath.c_str());
        AAssetDir_close(dir);
        return fileList;
    }
    const char* tmpDir = nullptr;
    while ((tmpDir = AAssetDir_getNextFileName(dir)) != nullptr)
    {
        string filepath(tmpDir);
        if (isDirectoryExistInternal(filepath))
            filepath += "/";
        fileList.emplace_back(fullPath + filepath);
    }
    AAssetDir_close(dir);
    return fileList;
}

FileUtils::Status FileUtilsAndroid::getContents(std::string_view filename, ResizableBuffer* buffer) const
{
    static const std::string apkprefix("assets/");
    if (filename.empty())
        return FileUtils::Status::NotExists;

    auto fullPath = fullPathForFilename(filename);

    if (fullPath[0] == '/')
        return FileUtils::getContents(fullPath, buffer);

    std::string relativePath;
    size_t position = fullPath.find(apkprefix);
    if (0 == position)
    {
        // "assets/" is at the beginning of the path and we don't want it
        relativePath += fullPath.substr(apkprefix.size());
    }
    else
    {
        relativePath = fullPath;
    }

    if (obbfile)
    {
        if (obbfile->getFileData(relativePath, buffer))
            return FileUtils::Status::OK;
    }

    if (nullptr == assetmanager)
    {
        LOGD("... FileUtilsAndroid::assetmanager is nullptr");
        return FileUtils::Status::NotInitialized;
    }

    AAsset* asset = AAssetManager_open(assetmanager, relativePath.c_str(), AASSET_MODE_UNKNOWN);
    if (nullptr == asset)
    {
        LOGD("AAssetManager_open %s failed", relativePath.c_str());
        return FileUtils::Status::OpenFailed;
    }

    auto size = AAsset_getLength(asset);
    buffer->resize(size);

    int readsize = AAsset_read(asset, buffer->buffer(), size);
    AAsset_close(asset);

    if (readsize < size)
    {
        if (readsize >= 0)
            buffer->resize(readsize);
        return FileUtils::Status::ReadFailed;
    }

    return FileUtils::Status::OK;
}

std::string FileUtilsAndroid::getWritablePath() const
{
    return getNativeWritableAbsolutePath();
}

std::string FileUtilsAndroid::getNativeWritableAbsolutePath() const
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    std::string path = JniHelper::callStaticStringMethod("org.cocos2dx.lib.Cocos2dxHelper", "getCocos2dxWritablePath");
    if (!path.empty())
        path.append("/");

    return path;
}

NS_CC_END
