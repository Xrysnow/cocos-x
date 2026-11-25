/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "AssetsManager.h"

#include <thread>

#include "base/Director.h"
#include "base/Scheduler.h"
#include "base/UserDefault.h"
#include "network/Downloader.h"
#include "platform/FileUtils.h"

#include "AssetVersionStorage.h"

NS_CC_EXT_BEGIN

using namespace std;
USING_NS_CC;
using namespace cc::network;

#define KEY_OF_VERSION "current-version-code"
#define KEY_OF_DOWNLOADED_VERSION "downloaded-version-code"
#define TEMP_PACKAGE_FILE_NAME "cocos2dx-update-temp-package.zip"

AssetsManager::AssetsManager(const char* packageUrl /* =nullptr */,
                             const char* versionFileUrl /* =nullptr */,
                             const char* storagePath /* =nullptr */)
    : _storagePath(storagePath ? storagePath : "")
    , _version("")
    , _packageUrl(packageUrl ? packageUrl : "")
    , _versionFileUrl(versionFileUrl ? versionFileUrl : "")
    , _downloadedVersion("")
    , _downloader(new Downloader())
    , _connectionTimeout(0)
    , _delegate(nullptr)
    , _isDownloading(false)
    , _shouldDeleteDelegateWhenExit(false)
{
    checkStoragePath();
    // convert downloader error code to AssetsManager::ErrorCode
    _downloader->onTaskError = [this](const DownloadTask& /*task*/, int errorCode, int /*errorCodeInternal*/,
                                      std::string_view /*errorStr*/) {
        _isDownloading = false;

        if (nullptr == _delegate)
        {
            return;
        }
        auto err = (DownloadTask::ERROR_OPEN_FILE_FAILED == errorCode) ? ErrorCode::CREATE_FILE : ErrorCode::NETWORK;
        _delegate->onError(err);
    };

    // progress callback
    _downloader->onTaskProgress = [this](const DownloadTask& task) {
        if (FileUtils::getInstance()->getFileExtension(task.requestURL) != ".zip")
        {
            // get version progress don't report
            return;
        }

        if (nullptr == _delegate)
        {
            return;
        }

        int percent = task.progressInfo.totalBytesExpected
                          ? int(task.progressInfo.totalBytesReceived * 100 / task.progressInfo.totalBytesExpected)
                          : 0;
        _delegate->onProgress(percent);
        CCLOG("downloading... %d%%", percent);
    };

    // get version from version file when get data success
    _downloader->onDataTaskSuccess = [this](const DownloadTask& /*task*/, std::vector<unsigned char>& data) {
        // store version info to member _version
        const char* p = (char*)data.data();
        _version.insert(_version.end(), p, p + data.size());

        if (getVersion() == _version)
        {
            if (_delegate)
            {
                _delegate->onError(ErrorCode::NO_NEW_VERSION);
            }
            CCLOG("there is not new version");
            // Set resource search path.
            setSearchPath();
            _isDownloading = false;
            return;
        }

        // start download new version assets
        // 1. Urls of package and version should be valid;
        // 2. Package should be a zip file.
        if (_versionFileUrl.empty() || _packageUrl.empty() ||
            FileUtils::getInstance()->getFileExtension(_packageUrl) != ".zip")
        {
            CCLOG("no version file url, or no package url, or the package is not a zip file");
            _isDownloading = false;
            return;
        }

        // Is package already downloaded?
        _downloadedVersion = UserDefault::getInstance()->getStringForKey(keyOfDownloadedVersion().c_str());
        if (_downloadedVersion == _version)
        {
            downloadAndUncompress();
            return;
        }

        // start download;
        const string outFileName = _storagePath + TEMP_PACKAGE_FILE_NAME;
        _downloader->createDownloadFileTask(_packageUrl, outFileName);
    };

    // after download package, do uncompress operation
    _downloader->onFileTaskSuccess = [this](const DownloadTask& /*task*/) { downloadAndUncompress(); };
}

AssetsManager::~AssetsManager()
{
    if (_shouldDeleteDelegateWhenExit)
    {
        delete _delegate;
    }
    CC_SAFE_DELETE(_downloader);
}

void AssetsManager::checkStoragePath()
{
    if (!_storagePath.empty() && _storagePath[_storagePath.size() - 1] != '/')
    {
        _storagePath.push_back('/');
    }
}

// Multiple key names
static std::string keyWithHash(const char* prefix, std::string_view url)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "%s%zd", prefix, std::hash<std::string_view>()(url));
    return buf;
}

// hashed version
std::string AssetsManager::keyOfVersion() const
{
    return keyWithHash(KEY_OF_VERSION, _packageUrl);
}

// hashed version
std::string AssetsManager::keyOfDownloadedVersion() const
{
    return keyWithHash(KEY_OF_DOWNLOADED_VERSION, _packageUrl);
}

bool AssetsManager::checkUpdate()
{
    if (_versionFileUrl.empty() || _isDownloading)
        return false;

    // Clear _version before assign new value.
    _version.clear();
    _isDownloading = true;
    _downloader->createDownloadDataTask(_versionFileUrl);
    return true;
}

void AssetsManager::downloadAndUncompress()
{
    std::thread([this, owner = cc::IntrusivePtr{this}]() mutable {
        const bool installed = uncompress();
        Director::getInstance()->getScheduler()->performFunctionInCocosThread(
            [this, owner = std::move(owner), installed] {
                auto* defaults = UserDefault::getInstance();
                if (installed)
                    defaults->setStringForKey(keyOfVersion().c_str(), _version);
                defaults->setStringForKey(keyOfDownloadedVersion().c_str(), "");
                defaults->flush();

                if (installed)
                    setSearchPath();
                const auto package = _storagePath + TEMP_PACKAGE_FILE_NAME;
                FileUtils::getInstance()->removeFile(package);

                _isDownloading = false;
                if (_delegate && installed)
                    _delegate->onSuccess();
                else if (_delegate)
                    _delegate->onError(ErrorCode::UNCOMPRESS);
            });
    }).detach();
}

void AssetsManager::update()
{
    // all operation in checkUpdate, nothing need to do
    // keep this function for compatibility
}

bool AssetsManager::uncompress()
{
    if (_storagePath.empty())
        return false;
    const auto store = asset_storage::fs::u8path(_storagePath) / (".cocos-assets-" + keyOfVersion());
    asset_storage::StagedVersion version(store);
    if (!version)
        return false;
    const auto path = _storagePath + TEMP_PACKAGE_FILE_NAME;
    const auto result = asset_storage::extractDownload(path, version.content());
    if (!result)
    {
        CCLOG("AssetsManager: cannot extract %s (error %d, native %d)", path.c_str(),
              static_cast<int>(result.error.code), result.error.nativeCode);
        return false;
    }
    return version.publish();
}

void AssetsManager::setSearchPath()
{
    if (_storagePath.empty())
        return;
    const auto store = asset_storage::fs::u8path(_storagePath) / (".cocos-assets-" + keyOfVersion());
    const auto version = asset_storage::selectedVersion(store);
    auto next = version.empty() ? _storagePath : asset_storage::searchPath(version);
    auto searchPaths = FileUtils::getInstance()->getSearchPaths();
    searchPaths.erase(std::remove(searchPaths.begin(), searchPaths.end(), _installedSearchPath), searchPaths.end());
    searchPaths.erase(std::remove(searchPaths.begin(), searchPaths.end(), next), searchPaths.end());
    searchPaths.insert(searchPaths.begin(), next);
    _installedSearchPath = std::move(next);
    FileUtils::getInstance()->setSearchPaths(searchPaths);
}

const char* AssetsManager::getPackageUrl() const
{
    return _packageUrl.c_str();
}

void AssetsManager::setPackageUrl(const char* packageUrl)
{
    _packageUrl = packageUrl;
}

const char* AssetsManager::getStoragePath() const
{
    return _storagePath.c_str();
}

void AssetsManager::setStoragePath(const char* storagePath)
{
    _storagePath = storagePath;
    checkStoragePath();
}

const char* AssetsManager::getVersionFileUrl() const
{
    return _versionFileUrl.c_str();
}

void AssetsManager::setVersionFileUrl(const char* versionFileUrl)
{
    _versionFileUrl = versionFileUrl;
}

std::string_view AssetsManager::getVersion()
{
    return UserDefault::getInstance()->getStringForKey(keyOfVersion().data());
}

void AssetsManager::deleteVersion()
{
    UserDefault::getInstance()->setStringForKey(keyOfVersion().c_str(), "");
}

void AssetsManager::setDelegate(AssetsManagerDelegateProtocol* delegate)
{
    _delegate = delegate;
}

void AssetsManager::setConnectionTimeout(unsigned int timeout)
{
    _connectionTimeout = timeout;
}

unsigned int AssetsManager::getConnectionTimeout()
{
    return _connectionTimeout;
}

cc::IntrusivePtr<AssetsManager> AssetsManager::create(const char* packageUrl,
                                     const char* versionFileUrl,
                                     const char* storagePath,
                                     ErrorCallback errorCallback,
                                     ProgressCallback progressCallback,
                                     SuccessCallback successCallback)
{
    class DelegateProtocolImpl : public AssetsManagerDelegateProtocol
    {
    public:
        DelegateProtocolImpl(ErrorCallback& aErrorCallback,
                             ProgressCallback& aProgressCallback,
                             SuccessCallback& aSuccessCallback)
            : errorCallback(aErrorCallback), progressCallback(aProgressCallback), successCallback(aSuccessCallback)
        {}

        virtual void onError(AssetsManager::ErrorCode errorCode) { errorCallback(int(errorCode)); }
        virtual void onProgress(int percent) { progressCallback(percent); }
        virtual void onSuccess() { successCallback(); }

    private:
        ErrorCallback errorCallback;
        ProgressCallback progressCallback;
        SuccessCallback successCallback;
    };

    cc::IntrusivePtr manager{new AssetsManager(packageUrl, versionFileUrl, storagePath)};
    auto* delegate = new DelegateProtocolImpl(errorCallback, progressCallback, successCallback);
    manager->setDelegate(delegate);
    manager->_shouldDeleteDelegateWhenExit = true;
    return manager;
}



NS_CC_EXT_END
