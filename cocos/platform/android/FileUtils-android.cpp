/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md)

https://axmol.dev/

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
#include "platform/android/FileUtils-android.h"
#include "platform/Common.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos_lib_CocosEngine.h"
#include "platform/android/AndroidPackageReadAdapter.h"
#include <set>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string_view>

#define LOG_TAG "FileUtils-android.cpp"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#define ASSETS_FOLDER_NAME "assets/"
#define ASSETS_FOLDER_NAME_LENGTH 7

// #define CC_USE_ANDROID_EXTERNAL_FILES_DIR 1

NS_CC_BEGIN

static jobject s_assetmanager_hold = nullptr;
static std::mutex s_writablePathMutex;
static std::string s_defaultWritablePath;
AAssetManager* FileUtilsAndroid::assetmanager = nullptr;

void FileUtilsAndroid::setAssetManagerFromJava(jobject a)
{
    auto env = JniHelper::getEnv();
    if (!s_assetmanager_hold)
        s_assetmanager_hold = env->NewGlobalRef(a);
    /*
    Note: that the caller is responsible for obtaining and holding a VM reference to the jobject to 
        prevent its being garbage collected while the native object is in use.
    refer: https://developer.android.com/ndk/reference/group/asset#aassetmanager_fromjava
    */
    auto aassetMgr = AAssetManager_fromJava(env, s_assetmanager_hold);
    if (nullptr == aassetMgr)
    {
        LOGD("setassetmanager : received unexpected nullptr parameter");
        return;
    }

    cc::FileUtilsAndroid::assetmanager = aassetMgr;
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

FileUtilsAndroid::~FileUtilsAndroid() = default;

bool FileUtilsAndroid::init()
{
    _defaultResRootPath = ASSETS_FOLDER_NAME;
    if (!FileUtils::init()) return false;
    std::shared_ptr<ZipReadAdapter> obb;
    std::string path(getApkPath());
    if (path.find("/obb/") != std::string::npos) {
        auto reader = archive::ZipReader::openFile(path);
        if (reader) {
            ZipMountOptions options;
            options.entry.temporaryDirectory = getWritablePath();
            auto adapter = ZipReadAdapter::create(reader.value, {""}, options);
            if (adapter) {
                _obb = std::move(reader.value);
                obb = std::move(adapter.value);
            } else CCLOGERROR("Cannot mount Android expansion archive (%d): %s", int(adapter.error.code), path.c_str());
        } else CCLOGERROR("Cannot open Android expansion archive (%d): %s", int(reader.error.code), path.c_str());
    }
    auto registered = registerReadAdapter("android-package",
        std::make_shared<AndroidPackageReadAdapter>(std::move(obb), std::vector<std::string>{""}), -10.f);
    if (!registered) return false;
    _packageId = registered.value;
    return true;
}

bool FileUtilsAndroid::isFileExistInternal(std::string_view strFilePath) const
{
    return static_cast<bool>(findPlatformFile(strFilePath));
}

bool FileUtilsAndroid::isDirectoryExistInternal(std::string_view dirPath) const
{
    if (dirPath.empty() || dirPath.find('\0') != dirPath.npos) return false;
    if (dirPath.front() == '/') {
        struct stat st;
        return ::stat(std::string(dirPath).c_str(), &st) == 0 && S_ISDIR(st.st_mode);
    }
    if (dirPath.starts_with("assets/")) dirPath.remove_prefix(7);
    while (dirPath.ends_with('/')) dirPath.remove_suffix(1);
    std::string name(dirPath);
    if (_obb) {
        auto prefix = name.empty() ? name : name + "/";
        for (const auto& entry : _obb->entries()) if (entry.name.starts_with(prefix)) return true;
    }
    if (!assetmanager) return false;
    auto* dir = AAssetManager_openDir(assetmanager, name.c_str());
    if (!dir) return false;
    bool found = AAssetDir_getNextFileName(dir) != nullptr;
    AAssetDir_close(dir);
    return found;
}

bool FileUtilsAndroid::isAbsolutePath(std::string_view strPath) const
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos.hellocpp/cache/path/path/file.png, or
    // /sdcard/path/path/file.png. So these two situations need to be checked on Android.
    return !strPath.empty() && (strPath[0] == '/' || strPath.starts_with("assets/"));
}

std::vector<std::string> FileUtilsAndroid::listFiles(std::string_view dirPath) const
{
    if (dirPath.starts_with('/')) return FileUtils::listFiles(dirPath);
    if (dirPath.starts_with("assets/")) dirPath.remove_prefix(7);
    while (dirPath.ends_with('/')) dirPath.remove_suffix(1);
    std::string dir(dirPath);
    if (_obb) {
        std::set<std::string> names;
        auto prefix = dir.empty() ? dir : dir + "/";
        for (auto& entry : _obb->entries()) {
            if (!entry.name.starts_with(prefix) || entry.name.size() == prefix.size()) continue;
            auto next = entry.name.find('/', prefix.size());
            names.insert(entry.name.substr(0, next == std::string::npos ? next : next + 1));
        }
        if (!names.empty()) return {names.begin(), names.end()};
    }
    if (!assetmanager) return {};
    return JniHelper::callStaticStringArrayMethod("org/cocos/lib/CocosEngine", "getAssetsList", dir);
}

bool FileUtilsAndroid::usesExternalWritablePath()
{
#ifdef CC_USE_ANDROID_EXTERNAL_FILES_DIR
    return true;
#else
    return false;
#endif
}

void FileUtilsAndroid::setDefaultWritablePathFromJava(std::string path)
{
    std::lock_guard<std::mutex> guard(s_writablePathMutex);
    s_defaultWritablePath = std::move(path);
}

bool FileUtilsAndroid::queryDefaultWritablePath(std::string& path) const
{
    std::lock_guard<std::mutex> guard(s_writablePathMutex);
    path = s_defaultWritablePath;
    return !path.empty();
}

NS_CC_END
