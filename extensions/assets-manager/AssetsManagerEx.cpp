/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
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
#include "AssetsManagerEx.h"
#include "CCEventListenerAssetsManagerEx.h"
#include "base/ccUTF8.h"
#include "base/Director.h"

#include <stdio.h>
#include <unordered_set>

#include "AssetVersionStorage.h"
#include "base/AsyncTaskPool.h"

NS_CC_EXT_BEGIN

#define TEMP_FOLDERNAME "_temp"
#define VERSION_FILENAME "version.manifest"
#define TEMP_MANIFEST_FILENAME "project.manifest.temp"
#define MANIFEST_FILENAME "project.manifest"

#define DEFAULT_CONNECTION_TIMEOUT 45

#define SAVE_POINT_INTERVAL 0.1

const std::string AssetsManagerEx::VERSION_ID  = "@version";
const std::string AssetsManagerEx::MANIFEST_ID = "@manifest";

namespace
{
constexpr auto VersionStoreName = ".cocos-assets-ex";
constexpr auto ExtractedDirectory = ".cocos-extracted";

asset_storage::fs::path updateAssetPath(std::string_view name)
{
    auto path = asset_storage::relativeAssetPath(name);
    if (path.empty())
        return {};
    auto first = asset_storage::utf8(*path.begin());
    for (auto& character : first)
    {
        if (character >= 'A' && character <= 'Z')
            character += 'a' - 'A';
    }
    if (first == ExtractedDirectory || first == VERSION_FILENAME ||
        first == TEMP_MANIFEST_FILENAME || first == MANIFEST_FILENAME)
        return {};
    return path;
}

asset_storage::fs::path downloadAssetPath(std::string_view path, std::string_view root)
{
    try
    {
        namespace fs = asset_storage::fs;
        return updateAssetPath(asset_storage::utf8(fs::u8path(path).lexically_relative(fs::u8path(root))));
    }
    catch (const asset_storage::fs::filesystem_error&)
    {
        return {};
    }
}
}

AssetsManagerEx::AssetsManagerEx(std::string_view manifestUrl, std::string_view storagePath) : _manifestUrl(manifestUrl)
{
    // Init variables
    _eventDispatcher    = Director::getInstance()->getEventDispatcher();
    std::string pointer = StringUtils::format("%p", this);
    _eventName          = EventListenerAssetsManagerEx::LISTENER_ID + pointer;
    _fileUtils          = FileUtils::getInstance();

    network::DownloaderHints hints = {static_cast<uint32_t>(_maxConcurrentTask), DEFAULT_CONNECTION_TIMEOUT, ".tmp"};
    _downloader                    = std::shared_ptr<network::Downloader>(new network::Downloader(hints));
    _downloader->onTaskError = std::bind(&AssetsManagerEx::onError, this, std::placeholders::_1, std::placeholders::_2,
                                         std::placeholders::_3, std::placeholders::_4);
    _downloader->onTaskProgress = [this](const network::DownloadTask& task) {
        this->onProgress(task.progressInfo.totalBytesExpected, task.progressInfo.totalBytesReceived, task.requestURL,
                         task.identifier);
    };
    _downloader->onFileTaskSuccess = [this](const network::DownloadTask& task) {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
    setStoragePath(storagePath);
    _tempVersionPath   = _tempStoragePath + VERSION_FILENAME;
    _tempManifestPath  = _tempStoragePath + TEMP_MANIFEST_FILENAME;

    initManifests(manifestUrl);
}

AssetsManagerEx::~AssetsManagerEx()
{
    _downloader->onTaskError       = (nullptr);
    _downloader->onFileTaskSuccess = (nullptr);
    _downloader->onTaskProgress    = (nullptr);
    CC_SAFE_RELEASE(_localManifest);
    // _tempManifest could share a ptr with _remoteManifest or _localManifest
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
    CC_SAFE_RELEASE(_remoteManifest);
}

cc::IntrusivePtr<AssetsManagerEx> AssetsManagerEx::create(std::string_view manifestUrl, std::string_view storagePath)
{
    cc::IntrusivePtr ret{new AssetsManagerEx(manifestUrl, storagePath)};
    return ret;
}

void AssetsManagerEx::initManifests(std::string_view manifestUrl)
{
    _inited = true;
    // Init and load local manifest
    _localManifest = cc::IntrusivePtr{new Manifest()}.detach();
    loadLocalManifest(manifestUrl);

    // Init and load temporary manifest
    _tempManifest = cc::IntrusivePtr{new Manifest()}.detach();
    _tempManifest->parse(_tempManifestPath);
    // Previous update is interrupted
    if (_fileUtils->isFileExist(_tempManifestPath))
    {
        // Manifest parse failed, remove all temp files
        if (!_tempManifest->isLoaded())
        {
            _fileUtils->removeDirectory(_tempStoragePath);
            CC_SAFE_RELEASE(_tempManifest);
            _tempManifest = nullptr;
        }
    }

    // Init remote manifest for future usage
    _remoteManifest = cc::IntrusivePtr{new Manifest()}.detach();

    if (!_inited)
    {
        CC_SAFE_RELEASE(_localManifest);
        CC_SAFE_RELEASE(_tempManifest);
        CC_SAFE_RELEASE(_remoteManifest);
        _localManifest  = nullptr;
        _tempManifest   = nullptr;
        _remoteManifest = nullptr;
    }
}

void AssetsManagerEx::prepareLocalManifest()
{
    // An alias to assets
    _assets = &(_localManifest->getAssets());

    // Add search paths
    _localManifest->prependSearchPaths();
}

void AssetsManagerEx::loadLocalManifest(std::string_view /*manifestUrl*/)
{
    Manifest* cachedManifest = nullptr;
    // Find the cached manifest file
    if (_fileUtils->isFileExist(_cacheManifestPath))
    {
        cachedManifest = cc::IntrusivePtr{new Manifest()}.detach();
        cachedManifest->parse(_cacheManifestPath);
        if (!cachedManifest->isLoaded())
        {
            _fileUtils->removeFile(_cacheManifestPath);
            CC_SAFE_RELEASE(cachedManifest);
            cachedManifest = nullptr;
        }
    }

    // Ensure no search path of cached manifest is used to load this manifest
    std::vector<std::string> searchPaths = _fileUtils->getSearchPaths();
    if (cachedManifest)
    {
        std::vector<std::string> cacheSearchPaths = cachedManifest->getSearchPaths();
        std::vector<std::string> trimmedPaths     = searchPaths;
        for (const auto& path : cacheSearchPaths)
        {
            const auto pos = std::find(trimmedPaths.begin(), trimmedPaths.end(), path);
            if (pos != trimmedPaths.end())
            {
                trimmedPaths.erase(pos);
            }
        }
        _fileUtils->setSearchPaths(trimmedPaths);
    }
    // Load local manifest in app package
    _localManifest->parse(_manifestUrl);
    if (cachedManifest)
    {
        // Restore search paths
        _fileUtils->setSearchPaths(searchPaths);
    }
    if (_localManifest->isLoaded())
    {
        // Compare with cached manifest to determine which one to use
        if (cachedManifest)
        {
            bool localNewer = _localManifest->versionGreater(cachedManifest, _versionCompareHandle);
            if (localNewer)
            {
                if (_activeStoragePath == _storagePath)
                    _fileUtils->removeFile(_cacheManifestPath);
                else
                    _fileUtils->removeFile(_storagePath + VersionStoreName + "/active");
                _activeStoragePath.clear();
                CC_SAFE_RELEASE(cachedManifest);
            }
            else
            {
                CC_SAFE_RELEASE(_localManifest);
                _localManifest = cachedManifest;
            }
        }
        prepareLocalManifest();
    }

    // Fail to load local manifest
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
    }
}

std::string_view AssetsManagerEx::basename(std::string_view path) const
{
    size_t found = path.find_last_of("/\\");

    if (std::string::npos != found)
    {
        return path.substr(0, found);
    }
    else
    {
        return path;
    }
}

std::string AssetsManagerEx::get(std::string_view key) const
{
    auto it = _assets->find(key);
    if (it != _assets->cend())
    {
        const auto& root = _activeStoragePath.empty() ? _storagePath : _activeStoragePath;
        return root + it->second.path;
    }
    else
        return "";
}

const Manifest* AssetsManagerEx::getLocalManifest() const
{
    return _localManifest;
}

const Manifest* AssetsManagerEx::getRemoteManifest() const
{
    return _remoteManifest;
}

std::string_view AssetsManagerEx::getStoragePath() const
{
    return _storagePath;
}

void AssetsManagerEx::setStoragePath(std::string_view storagePath)
{
    _storagePath = storagePath;
    adjustPath(_storagePath);
    _fileUtils->createDirectory(_storagePath);
    const auto current = asset_storage::selectedVersion(asset_storage::fs::u8path(_storagePath) / VersionStoreName);
    _activeStoragePath = current.empty() ? _storagePath : asset_storage::searchPath(current);
    _cacheManifestPath = _activeStoragePath + MANIFEST_FILENAME;

    _tempStoragePath = _storagePath;
    _tempStoragePath.append(TEMP_FOLDERNAME);
    adjustPath(_tempStoragePath);
    _fileUtils->createDirectory(_tempStoragePath);
}

void AssetsManagerEx::adjustPath(std::string& path)
{
    if (!path.empty() && path[path.size() - 1] != '/')
    {
        path.push_back('/');
    }
}

bool AssetsManagerEx::decompress(std::string_view zip)
{
    namespace fs = asset_storage::fs;
    const auto downloads = fs::u8path(_tempStoragePath);
    const auto relative = downloadAssetPath(zip, _tempStoragePath);
    if (relative.empty())
        return false;
    const auto extracted = downloads / ExtractedDirectory / relative;
    std::error_code ec;
    fs::create_directories(extracted.parent_path(), ec);
    if (ec)
        return false;
    fs::remove_all(extracted, ec);
    if (ec)
        return false;
    const auto result = asset_storage::extractDownload(zip, extracted);
    if (!result)
        CCLOG("AssetsManagerEx: cannot extract %.*s (error %d, native %d)", static_cast<int>(zip.size()), zip.data(),
              static_cast<int>(result.error.code), result.error.nativeCode);
    return static_cast<bool>(result);
}

void AssetsManagerEx::decompressDownloadedZip(std::string_view customId, std::string_view storagePath)
{
    struct AsyncData
    {
        std::string customId;
        std::string zipFile;
        bool succeed;
    };

    AsyncData* asyncData = new AsyncData;
    asyncData->customId  = customId;
    asyncData->zipFile   = storagePath;
    asyncData->succeed   = false;

    std::function<void(void*)> decompressFinished = [this](void* param) {
        auto dataInner = reinterpret_cast<AsyncData*>(param);
        if (dataInner->succeed)
        {
            fileSuccess(dataInner->customId, dataInner->zipFile);
        }
        else
        {
            std::string errorMsg = "Unable to decompress file " + dataInner->zipFile;
            // Ensure zip file deletion (if decompress failure cause task thread exit anormally)
            _fileUtils->removeFile(dataInner->zipFile);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS, "", errorMsg);
            fileError(dataInner->customId, errorMsg);
        }
        delete dataInner;
    };
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, std::move(decompressFinished),
                                          (void*)asyncData, [this, asyncData]() {
                                              // Decompress all compressed files
                                              if (decompress(asyncData->zipFile))
                                              {
                                                  asyncData->succeed = true;
                                              }
                                              _fileUtils->removeFile(asyncData->zipFile);
                                          });
}

void AssetsManagerEx::dispatchUpdateEvent(EventAssetsManagerEx::EventCode code,
                                          std::string_view assetId /* = ""*/,
                                          std::string_view message /* = ""*/,
                                          int curle_code /* = CURLE_OK*/,
                                          int curlm_code /* = CURLM_OK*/)
{
    switch (code)
    {
    case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
    case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
    case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
    case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
    case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
    case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
    case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
    case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
        _updateEntry = UpdateEntry::NONE;
        break;
    case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
        break;
    case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
        break;
    case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
        if (_updateEntry == UpdateEntry::CHECK_UPDATE)
        {
            _updateEntry = UpdateEntry::NONE;
        }
        break;
    default:
        break;
    }

    EventAssetsManagerEx event(_eventName, this, code, _percent, _percentByFile, assetId, message, curle_code,
                               curlm_code);
    _eventDispatcher->dispatchEvent(&event);
}

AssetsManagerEx::State AssetsManagerEx::getState() const
{
    return _updateState;
}

void AssetsManagerEx::downloadVersion()
{
    if (_updateState > State::PREDOWNLOAD_VERSION)
        return;

    std::string_view versionUrl = _localManifest->getVersionFileUrl();

    if (!versionUrl.empty())
    {
        _updateState = State::DOWNLOADING_VERSION;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(versionUrl, _tempVersionPath, VERSION_ID);
    }
    // No version file found
    else
    {
        CCLOG("AssetsManagerEx : No version file found, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
}

void AssetsManagerEx::parseVersion()
{
    if (_updateState != State::VERSION_LOADED)
        return;

    _remoteManifest->parseVersion(_tempVersionPath);

    if (!_remoteManifest->isVersionLoaded())
    {
        CCLOG("AssetsManagerEx : Fail to parse version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else
    {
        if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
        {
            _updateState = State::UP_TO_DATE;
            _fileUtils->removeDirectory(_tempStoragePath);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;

            // Wait to update so continue the process
            if (_updateEntry == UpdateEntry::DO_UPDATE)
            {
                // dispatch after checking update entry because event dispatching may modify the update entry
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
                _updateState = State::PREDOWNLOAD_MANIFEST;
                downloadManifest();
            }
            else
            {
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
            }
        }
    }
}

void AssetsManagerEx::downloadManifest()
{
    if (_updateState != State::PREDOWNLOAD_MANIFEST)
        return;

    std::string manifestUrl;
    if (_remoteManifest->isVersionLoaded())
    {
        manifestUrl = _remoteManifest->getManifestFileUrl();
    }
    else
    {
        manifestUrl = _localManifest->getManifestFileUrl();
    }

    if (!manifestUrl.empty())
    {
        _updateState = State::DOWNLOADING_MANIFEST;
        // Download version file asynchronously
        _downloader->createDownloadFileTask(manifestUrl, _tempManifestPath, MANIFEST_ID);
    }
    // No manifest file found
    else
    {
        CCLOG("AssetsManagerEx : No manifest file found, check update failed\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST);
        _updateState = State::UNCHECKED;
    }
}

void AssetsManagerEx::parseManifest()
{
    if (_updateState != State::MANIFEST_LOADED)
        return;

    _remoteManifest->parse(_tempManifestPath);

    if (!_remoteManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : Error parsing manifest file, %s", _tempManifestPath.c_str());
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST);
        _updateState = State::UNCHECKED;
    }
    else
    {
        if (_localManifest->versionGreater(_remoteManifest, _versionCompareHandle))
        {
            _updateState = State::UP_TO_DATE;
            _fileUtils->removeDirectory(_tempStoragePath);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
        }
        else
        {
            _updateState = State::NEED_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);

            if (_updateEntry == UpdateEntry::DO_UPDATE)
            {
                startUpdate();
            }
        }
    }
}

void AssetsManagerEx::startUpdate()
{
    if (_updateState != State::NEED_UPDATE)
        return;

    _updateState = State::UPDATING;
    // Clean up before update
    _failedUnits.clear();
    _downloadUnits.clear();
    _totalWaitToDownload = _totalToDownload = 0;
    _nextSavePoint                          = 0;
    _percent = _percentByFile = _sizeCollected = _totalSize = 0;
    _downloadedSize.clear();
    _totalEnabled = false;

    // Temporary manifest exists, resuming previous download
    if (_tempManifest && _tempManifest->isLoaded() && _tempManifest->versionEquals(_remoteManifest))
    {
        _tempManifest->saveToFile(_tempManifestPath);
        _tempManifest->genResumeAssetsList(&_downloadUnits);
        _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
        if (!batchDownload())
            return;

        std::string msg = StringUtils::format(
            "Resuming from previous unfinished update, %d files remains to be finished.", _totalToDownload);
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "", msg);
    }
    else
    {
        // Temporary manifest exists, but can't be parsed or version doesn't equals remote manifest (out of date)
        if (_tempManifest)
        {
            // Remove all temp files
            _fileUtils->removeDirectory(_tempStoragePath);
            CC_SAFE_RELEASE(_tempManifest);
            // Recreate temp storage path and save remote manifest
            _fileUtils->createDirectory(_tempStoragePath);
            _remoteManifest->saveToFile(_tempManifestPath);
        }

        // Temporary manifest will be used to register the download states of each asset,
        // in this case, it equals remote manifest.
        _tempManifest = _remoteManifest;

        // Check difference between local manifest and remote manifest
        hlookup::string_map<Manifest::AssetDiff> diff_map = _localManifest->genDiff(_remoteManifest);
        if (diff_map.empty())
        {
            updateSucceed();
        }
        else
        {
            // Generate download units for all assets that need to be updated or added
            std::string_view packageUrl = _remoteManifest->getPackageUrl();
            // Save current download manifest information for resuming
            _tempManifest->saveToFile(_tempManifestPath);
            // Preprocessing local files in previous version and creating download folders
            for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
            {
                Manifest::AssetDiff diff = it->second;
                if (diff.type != Manifest::DiffType::DELETED)
                {
                    auto& path = diff.asset.path;
                    DownloadUnit unit;
                    unit.customId = it->first;
                    unit.srcUrl   = packageUrl;
                    unit.srcUrl += path;
                    unit.storagePath = _tempStoragePath + path;
                    unit.size        = diff.asset.size;
                    _downloadUnits.emplace(unit.customId, unit);
                    _tempManifest->setAssetDownloadState(it->first, Manifest::DownloadState::UNSTARTED);
                }
            }
            _totalWaitToDownload = _totalToDownload = (int)_downloadUnits.size();
            if (!batchDownload())
                return;

            std::string msg = StringUtils::format("Start to update %d files from remote package.", _totalToDownload);
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "", msg);
        }
    }
}

void AssetsManagerEx::updateSucceed()
{
    namespace fs = asset_storage::fs;
    const auto downloads = fs::u8path(_tempStoragePath);
    asset_storage::StagedVersion version(_storagePath.empty() ? fs::path{} : fs::u8path(_storagePath) / VersionStoreName);
    const auto assemble = [&] {
        if (_storagePath.empty() || !version)
            return false;
        const auto content = version.content();
        std::error_code ec;
        if (!fs::create_directory(content, ec) || ec)
            return false;

        if (!_activeStoragePath.empty())
        {
            const auto previous = fs::u8path(_activeStoragePath);
            const bool legacy = _activeStoragePath == _storagePath;
            if (!asset_storage::overlayTree(previous, content, legacy ? fs::path(TEMP_FOLDERNAME) : fs::path{},
                                            legacy ? fs::path(VersionStoreName) : fs::path{}))
                return false;
        }

        for (const auto& [id, asset] : _tempManifest->getAssets())
        {
            if (asset.downloadState != Manifest::DownloadState::SUCCESSED)
                continue;
            const auto path = updateAssetPath(asset.path);
            if (path.empty())
                return false;
            if (asset.compressed)
            {
                if (!asset_storage::overlayTree(downloads / ExtractedDirectory / path, content / path.parent_path()))
                    return false;
            }
            else if (!asset_storage::copyAsset(downloads / path, content / path))
                return false;
        }
        return asset_storage::copyAsset(fs::u8path(_tempManifestPath), content / MANIFEST_FILENAME) &&
               version.publish();
    };

    if (!assemble())
    {
        _tempManifest->saveToFile(_tempManifestPath);
        _updateState = State::FAIL_TO_UPDATE;
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FAILED, "", "Unable to install the downloaded version");
        return;
    }

    auto searchPaths = _fileUtils->getSearchPaths();
    if (_localManifest->_manifestRoot == _activeStoragePath)
    {
        for (const auto& old : _localManifest->getSearchPaths())
            searchPaths.erase(std::remove(searchPaths.begin(), searchPaths.end(), old), searchPaths.end());
    }
    _activeStoragePath = asset_storage::searchPath(version.content());
    _cacheManifestPath = _activeStoragePath + MANIFEST_FILENAME;
    _fileUtils->removeDirectory(_tempStoragePath);
    if (_tempManifest != _localManifest && _tempManifest != _remoteManifest)
        CC_SAFE_RELEASE(_tempManifest);
    _tempManifest = nullptr;
    CC_SAFE_RELEASE(_localManifest);
    _localManifest = _remoteManifest;
    _localManifest->setManifestRoot(_activeStoragePath);
    _remoteManifest = nullptr;
    _assets = &_localManifest->getAssets();
    for (const auto& path : _localManifest->getSearchPaths())
    {
        searchPaths.erase(std::remove(searchPaths.begin(), searchPaths.end(), path), searchPaths.end());
        searchPaths.insert(searchPaths.begin(), path);
    }
    _fileUtils->setSearchPaths(searchPaths);
    // 5. Set update state
    _updateState = State::UP_TO_DATE;
    // 6. Notify finished event
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FINISHED);
}

void AssetsManagerEx::checkUpdate()
{
    if (_updateEntry != UpdateEntry::NONE)
    {
        CCLOGERROR("AssetsManagerEx::checkUpdate, updateEntry isn't NONE");
        return;
    }

    if (!_inited)
    {
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _updateEntry = UpdateEntry::CHECK_UPDATE;

    switch (_updateState)
    {
    case State::UNCHECKED:
    case State::PREDOWNLOAD_VERSION:
    {
        downloadVersion();
    }
    break;
    case State::UP_TO_DATE:
    {
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE);
    }
    break;
    case State::FAIL_TO_UPDATE:
    case State::NEED_UPDATE:
    {
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND);
    }
    break;
    default:
        break;
    }
}

void AssetsManagerEx::update()
{
    if (_updateEntry != UpdateEntry::NONE)
    {
        CCLOGERROR("AssetsManagerEx::update, updateEntry isn't NONE");
        return;
    }

    if (!_inited)
    {
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }
    if (!_localManifest->isLoaded())
    {
        CCLOG("AssetsManagerEx : No local manifest file found error.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    _updateEntry = UpdateEntry::DO_UPDATE;

    switch (_updateState)
    {
    case State::UNCHECKED:
    {
        _updateState = State::PREDOWNLOAD_VERSION;
    }
    case State::PREDOWNLOAD_VERSION:
    {
        downloadVersion();
    }
    break;
    case State::VERSION_LOADED:
    {
        parseVersion();
    }
    break;
    case State::PREDOWNLOAD_MANIFEST:
    {
        downloadManifest();
    }
    break;
    case State::MANIFEST_LOADED:
    {
        parseManifest();
    }
    break;
    case State::FAIL_TO_UPDATE:
    case State::NEED_UPDATE:
    {
        // Manifest not loaded yet
        if (!_remoteManifest->isLoaded())
        {
            _updateState = State::PREDOWNLOAD_MANIFEST;
            downloadManifest();
        }
        else
        {
            startUpdate();
        }
    }
    break;
    case State::UP_TO_DATE:
    case State::UPDATING:
    case State::UNZIPPING:
        _updateEntry = UpdateEntry::NONE;
        break;
    default:
        break;
    }
}

void AssetsManagerEx::updateAssets(const DownloadUnits& assets)
{
    if (!_inited)
    {
        CCLOG("AssetsManagerEx : Manifests uninited.\n");
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST);
        return;
    }

    if (_updateState != State::UPDATING && _localManifest->isLoaded() && _remoteManifest && _remoteManifest->isLoaded())
    {
        _updateState = State::UPDATING;
        _downloadUnits.clear();
        _downloadedSize.clear();
        _percent = _percentByFile = _sizeCollected = _totalSize = 0;
        _totalWaitToDownload = _totalToDownload = (int)assets.size();
        _nextSavePoint                          = 0;
        _totalEnabled                           = false;
        if (_totalToDownload > 0)
        {
            _downloadUnits = assets;
            this->batchDownload();
        }
        else if (_totalToDownload == 0)
        {
            onDownloadUnitsFinished();
        }
    }
}

const DownloadUnits& AssetsManagerEx::getFailedAssets() const
{
    return _failedUnits;
}

void AssetsManagerEx::downloadFailedAssets()
{
    CCLOG("AssetsManagerEx : Start update %lu failed assets.\n", static_cast<unsigned long>(_failedUnits.size()));
    updateAssets(_failedUnits);
}

void AssetsManagerEx::fileError(std::string_view identifier,
                                std::string_view errorStr,
                                int errorCode,
                                int errorCodeInternal)
{
    auto unitIt = _downloadUnits.find(identifier);
    // Found unit and add it to failed units
    if (unitIt != _downloadUnits.end())
    {
        _totalWaitToDownload--;

        DownloadUnit unit = unitIt->second;
        _failedUnits.emplace(unit.customId, unit);
    }
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_UPDATING, identifier, errorStr, errorCode,
                        errorCodeInternal);
    _tempManifest->setAssetDownloadState(identifier, Manifest::DownloadState::UNSTARTED);

    _currConcurrentTask = MAX(0, _currConcurrentTask - 1);
    queueDowload();
}

void AssetsManagerEx::fileSuccess(std::string_view customId, std::string_view storagePath)
{
    // Set download state to SUCCESSED
    _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::SUCCESSED);

    auto unitIt = _failedUnits.find(customId);
    // Found unit and delete it
    if (unitIt != _failedUnits.end())
    {
        // Remove from failed units list
        _failedUnits.erase(unitIt);
    }

    unitIt = _downloadUnits.find(customId);
    if (unitIt != _downloadUnits.end())
    {
        // Reduce count only when unit found in _downloadUnits
        _totalWaitToDownload--;

        _percent = _percentByFile = 100 * (float)(_totalToDownload - _totalWaitToDownload) / _totalToDownload;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, "");
    }
    // Notify asset updated event
    dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ASSET_UPDATED, customId);

    _currConcurrentTask = MAX(0, _currConcurrentTask - 1);
    queueDowload();
}

void AssetsManagerEx::onError(const network::DownloadTask& task,
                              int errorCode,
                              int errorCodeInternal,
                              std::string_view errorStr)
{
    // Skip version error occurred
    if (task.identifier == VERSION_ID)
    {
        CCLOG("AssetsManagerEx : Fail to download version file, step skipped\n");
        _updateState = State::PREDOWNLOAD_MANIFEST;
        downloadManifest();
    }
    else if (task.identifier == MANIFEST_ID)
    {
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST, task.identifier, errorStr,
                            errorCode, errorCodeInternal);
        _updateState = State::FAIL_TO_UPDATE;
    }
    else
    {
        fileError(task.identifier, errorStr, errorCode, errorCodeInternal);
    }
}

void AssetsManagerEx::onProgress(double total, double downloaded, std::string_view /*url*/, std::string_view customId)
{
    if (customId == VERSION_ID || customId == MANIFEST_ID)
    {
        _percent = 100 * downloaded / total;
        // Notify progression event
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
        return;
    }
    else
    {
        // Calcul total downloaded
        bool found             = false;
        double totalDownloaded = 0;
        for (auto it = _downloadedSize.begin(); it != _downloadedSize.end(); ++it)
        {
            if (it->first == customId)
            {
                it->second = downloaded;
                found      = true;
            }
            totalDownloaded += it->second;
        }
        // Collect information if not registed
        if (!found)
        {
            // Set download state to DOWNLOADING, this will run only once in the download process
            _tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::DOWNLOADING);
            // Register the download size information
            _downloadedSize.emplace(customId, downloaded);
            // Check download unit size existance, if not exist collect size in total size
            if (_downloadUnits[customId].size == 0)
            {
                _totalSize += total;
                _sizeCollected++;
                // All collected, enable total size
                if (_sizeCollected == _totalToDownload)
                {
                    _totalEnabled = true;
                }
            }
        }

        if (_totalEnabled && _updateState == State::UPDATING)
        {
            float currentPercent = 100 * totalDownloaded / _totalSize;
            // Notify at integer level change
            if ((int)currentPercent != (int)_percent)
            {
                _percent = currentPercent;
                // Notify progression event
                dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION, customId);
            }
        }
    }
}

void AssetsManagerEx::onSuccess(std::string_view /*srcUrl*/, std::string_view storagePath, std::string_view customId)
{
    if (customId == VERSION_ID)
    {
        _updateState = State::VERSION_LOADED;
        parseVersion();
    }
    else if (customId == MANIFEST_ID)
    {
        _updateState = State::MANIFEST_LOADED;
        parseManifest();
    }
    else
    {
        bool ok      = true;
        auto& assets = _remoteManifest->getAssets();
        auto assetIt = assets.find(customId);
        if (assetIt != assets.end())
        {
            Manifest::Asset asset = assetIt->second;
            if (_verifyCallback != nullptr)
            {
                ok = _verifyCallback(storagePath, asset);
            }
        }

        if (ok)
        {
            bool compressed = assetIt != assets.end() ? assetIt->second.compressed : false;
            if (compressed)
            {
                decompressDownloadedZip(customId, storagePath);
            }
            else
            {
                fileSuccess(customId, storagePath);
            }
        }
        else
        {
            fileError(customId, "Asset file verification failed after downloaded");
        }
    }
}

void AssetsManagerEx::destroyDownloadedVersion()
{
    _fileUtils->removeDirectory(_storagePath);
    _fileUtils->removeDirectory(_tempStoragePath);
}

bool AssetsManagerEx::batchDownload()
{
    _queue.clear();
    std::unordered_set<std::string> destinations;
    for (const auto& iter : _downloadUnits)
    {
        const DownloadUnit& unit = iter.second;
        const auto path = downloadAssetPath(unit.storagePath, _tempStoragePath);
        auto key = asset_storage::utf8(path);
        for (auto& character : key)
        {
            if (character >= 'A' && character <= 'Z')
                character += 'a' - 'A';
        }
        if (path.empty() || !destinations.emplace(std::move(key)).second)
        {
            _queue.clear();
            _updateState = State::FAIL_TO_UPDATE;
            dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FAILED, unit.customId, "Invalid asset destination");
            return false;
        }
        if (unit.size > 0)
        {
            _totalSize += unit.size;
            _sizeCollected++;
        }

        _queue.emplace_back(iter.first);
    }
    // All collected, enable total size
    if (_sizeCollected == _totalToDownload)
    {
        _totalEnabled = true;
    }

    queueDowload();
    return true;
}

void AssetsManagerEx::queueDowload()
{
    if (_totalWaitToDownload == 0)
    {
        this->onDownloadUnitsFinished();
        return;
    }

    while (_currConcurrentTask < _maxConcurrentTask && !_queue.empty())
    {
        std::string key = _queue.back();
        _queue.pop_back();

        _currConcurrentTask++;
        DownloadUnit& unit = _downloadUnits[key];
        _fileUtils->createDirectory(basename(unit.storagePath));
        _downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);

        _tempManifest->setAssetDownloadState(key, Manifest::DownloadState::DOWNLOADING);
    }
    if (_percentByFile / 100 > _nextSavePoint)
    {
        // Save current download manifest information for resuming
        _tempManifest->saveToFile(_tempManifestPath);
        _nextSavePoint += SAVE_POINT_INTERVAL;
    }
}

void AssetsManagerEx::onDownloadUnitsFinished()
{
    // Finished with error check
    if (!_failedUnits.empty())
    {
        // Save current download manifest information for resuming
        _tempManifest->saveToFile(_tempManifestPath);

        _updateState = State::FAIL_TO_UPDATE;
        dispatchUpdateEvent(EventAssetsManagerEx::EventCode::UPDATE_FAILED);
    }
    else if (_updateState == State::UPDATING)
    {
        updateSucceed();
    }
}


NS_CC_EXT_END
