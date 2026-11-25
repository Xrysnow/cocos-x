/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2020 C4games Ltd.
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

#include "renderer/TextureCache.h"

#include <errno.h>
#include <stack>
#include <cctype>
#include <list>

#include "renderer/Texture2D.h"
#include "base/Macros.h"
#include "platform/PlatformMacros.h"
#include "base/ccUTF8.h"
#include "base/Director.h"
#include "base/Scheduler.h"
#include "platform/FileUtils.h"
#include "base/ccUtils.h"
#include "base/NinePatchImageParser.h"
#include "renderer/backend/Device.h"

using namespace std;

NS_CC_BEGIN

namespace
{
std::string textureKey(const FileHit& hit)
{
    if (hit.name() == "physical" && hit.entry().nativePath)
        return *hit.entry().nativePath;
    return std::string(1, '\0') + std::to_string(hit.adapterId()) + ':' + hit.entry().entryKey;
}

std::string textureKeyForPath(std::string_view path)
{
    const auto hit = FileUtils::getInstance()->findFile(path);
    return hit ? textureKey(hit.value) : std::string{};
}

bool readAlpha(const FileHit& parent, std::string_view suffix, Image& image)
{
    if (suffix.empty())
        return false;
    auto key = std::string_view(parent.entry().entryKey);
    if (parent.kind() == "android-package" && (key.starts_with("apk:") || key.starts_with("obb:")))
        key.remove_prefix(4);
    const auto filename = std::string(key.substr(key.find_last_of("/\\") + 1));
    const auto alpha = FileUtils::getInstance()->findSibling(parent, filename + std::string(suffix));
    return alpha && image.initWithImageHit(alpha.value);
}
}

std::string TextureCache::s_etc1AlphaFileSuffix = "@alpha";

// implementation TextureCache

void TextureCache::setETC1AlphaFileSuffix(std::string_view suffix)
{
    s_etc1AlphaFileSuffix = suffix;
}

std::string TextureCache::getETC1AlphaFileSuffix()
{
    return s_etc1AlphaFileSuffix;
}

TextureCache::TextureCache() : _loadingThread(nullptr), _needQuit(false), _asyncRefCount(0) {}

std::string TextureCache::getDescription() const
{
    return StringUtils::format("<TextureCache | Number of textures = %d>", static_cast<int>(_textures.size()));
}

struct TextureCache::AsyncStruct
{
public:
    AsyncStruct(FileHit source, const std::function<void(Texture2D*)>& f, std::string_view callbackName)
        : hit(std::move(source))
        , key(textureKey(hit))
        , callback(f)
        , callbackKey(callbackName)
        , alphaSuffix(TextureCache::getETC1AlphaFileSuffix())
        , pixelFormat(Texture2D::getDefaultAlphaPixelFormat())
        , loadSuccess(false)
    {}

    FileHit hit;
    std::string key;
    std::function<void(Texture2D*)> callback;
    std::string callbackKey;
    std::string alphaSuffix;
    Image image;
    Image imageAlpha;
    backend::PixelFormat pixelFormat;
    bool loadSuccess;
};

TextureCache::~TextureCache()
{
    CCLOGINFO("deallocing TextureCache: %p", this);
    waitForQuit();
    // An independently owned cache can be destroyed with pending responses.
    // Remove its selector before freeing the queued records and target object.
    if (_asyncRefCount != 0)
        Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack),
                                                            this);
    // The queues alias these records. Destroy captures on the main thread only
    // at cache destruction; public waitForQuit must preserve pending delivery.
    for (auto* pending : _asyncStructQueue)
        delete pending;
    _asyncStructQueue.clear();
    _requestQueue.clear();
    _responseQueue.clear();
    for (auto&& texture : _textures)
        texture.second->release();
    CC_SAFE_DELETE(_loadingThread);
}

/**
 The addImageAsync logic follow the steps:
 - find the image has been add or not, if not add an AsyncStruct to _requestQueue  (GL thread)
 - get AsyncStruct from _requestQueue, load res and fill image data to AsyncStruct.image, then add AsyncStruct to
 _responseQueue (Load thread)
 - on schedule callback, get AsyncStruct from _responseQueue, convert image to texture, then delete AsyncStruct (GL
 thread)

 the Critical Area include these members:
 - _requestQueue: locked by _requestMutex
 - _responseQueue: locked by _responseMutex

 the object's life time:
 - AsyncStruct: construct and destruct in GL thread
 - image data: new in Load thread, delete in GL thread(by Image instance)

 Note:
 - all AsyncStruct referenced in _asyncStructQueue, for unbind function use.

 How to deal add image many times?
 - At first, this situation is abnormal, we only ensure the logic is correct.
 - If the image has been loaded, the after load image call will return immediately.
 - If the image request is in queue already, there will be more than one request in queue,
 - In addImageAsyncCallback, will deduplicate the request to ensure only create one texture.

 Does process all response in addImageAsyncCallback consume more time?
 - Convert image to texture faster than load image from disk, so this isn't a
 problem.

 Call unbindImageAsync(path) to prevent the call to the callback when the
 texture is loaded.
 */
void TextureCache::addImageAsync(std::string_view path, const std::function<void(Texture2D*)>& callback)
{
    addImageAsync(path, callback, path);
}

/**
 The addImageAsync logic follow the steps:
 - find the image has been add or not, if not add an AsyncStruct to _requestQueue  (GL thread)
 - get AsyncStruct from _requestQueue, load res and fill image data to AsyncStruct.image, then add AsyncStruct to
 _responseQueue (Load thread)
 - on schedule callback, get AsyncStruct from _responseQueue, convert image to texture, then delete AsyncStruct (GL
 thread)

 the Critical Area include these members:
 - _requestQueue: locked by _requestMutex
 - _responseQueue: locked by _responseMutex

 the object's life time:
 - AsyncStruct: construct and destruct in GL thread
 - image data: new in Load thread, delete in GL thread(by Image instance)

 Note:
 - all AsyncStruct referenced in _asyncStructQueue, for unbind function use.

 How to deal add image many times?
 - At first, this situation is abnormal, we only ensure the logic is correct.
 - If the image has been loaded, the after load image call will return immediately.
 - If the image request is in queue already, there will be more than one request in queue,
 - In addImageAsyncCallback, will deduplicate the request to ensure only create one texture.

 Does process all response in addImageAsyncCallback consume more time?
 - Convert image to texture faster than load image from disk, so this isn't a
 problem.

 The callbackKey allows to unbind the callback in cases where the loading of
 path is requested by several sources simultaneously. Each source can then
 unbind the callback independently as needed whilst a call to
 unbindImageAsync(path) would be ambiguous.
 */
void TextureCache::addImageAsync(std::string_view path,
                                 const std::function<void(Texture2D*)>& callback,
                                 std::string_view callbackKey)
{
    auto hit = FileUtils::getInstance()->findFile(path);
    if (!hit)
    {
        if (callback)
            callback(nullptr);
        return;
    }
    if (const auto cached = _textures.find(textureKey(hit.value)); cached != _textures.end())
    {
        if (callback)
            callback(cached->second);
        return;
    }

    // lazy init
    if (_loadingThread == nullptr)
    {
        // create a new thread to load images
        _needQuit      = false;
        _loadingThread = new std::thread(&TextureCache::loadImage, this);
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack),
                                                          this, 0, false);
    }

    ++_asyncRefCount;

    // generate async struct
    AsyncStruct* data = new AsyncStruct(std::move(hit.value), callback, callbackKey);

    // add async struct into queue
    _asyncStructQueue.emplace_back(data);
    std::unique_lock<std::mutex> ul(_requestMutex);
    _requestQueue.emplace_back(data);
    _sleepCondition.notify_one();
}

void TextureCache::unbindImageAsync(std::string_view callbackKey)
{
    if (_asyncStructQueue.empty())
    {
        return;
    }

    for (auto&& asyncStruct : _asyncStructQueue)
    {
        if (asyncStruct->callbackKey == callbackKey)
        {
            asyncStruct->callback = nullptr;
        }
    }
}

void TextureCache::unbindAllImageAsync()
{
    if (_asyncStructQueue.empty())
    {
        return;
    }
    for (auto&& asyncStruct : _asyncStructQueue)
    {
        asyncStruct->callback = nullptr;
    }
}

void TextureCache::loadImage()
{
    AsyncStruct* asyncStruct = nullptr;
    while (true)
    {
        std::unique_lock<std::mutex> ul(_requestMutex);
        if (_needQuit)
            break;
        // pop an AsyncStruct from request queue
        if (_requestQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _requestQueue.front();
            _requestQueue.pop_front();
        }

        if (nullptr == asyncStruct)
        {
            if (_needQuit)
            {
                break;
            }
            _sleepCondition.wait(ul);
            continue;
        }
        ul.unlock();

        // load image
        asyncStruct->loadSuccess = asyncStruct->image.initWithImageHit(asyncStruct->hit);

        // ETC1 ALPHA supports.
        if (asyncStruct->loadSuccess && asyncStruct->image.getFileType() == Image::Format::ETC1)
            readAlpha(asyncStruct->hit, asyncStruct->alphaSuffix, asyncStruct->imageAlpha);
        // push the asyncStruct to response queue
        _responseMutex.lock();
        _responseQueue.emplace_back(asyncStruct);
        _responseMutex.unlock();
    }
}

void TextureCache::addImageAsyncCallBack(float /*dt*/)
{
    Texture2D* texture       = nullptr;
    AsyncStruct* asyncStruct = nullptr;
    while (true)
    {
        // pop an AsyncStruct from response queue
        _responseMutex.lock();
        if (_responseQueue.empty())
        {
            asyncStruct = nullptr;
        }
        else
        {
            asyncStruct = _responseQueue.front();
            _responseQueue.pop_front();

            // the asyncStruct's sequence order in _asyncStructQueue must equal to the order in _responseQueue
            CC_ASSERT(asyncStruct == _asyncStructQueue.front());
            _asyncStructQueue.pop_front();
        }
        _responseMutex.unlock();

        if (nullptr == asyncStruct)
        {
            break;
        }

        // check the image has been convert to texture or not
        auto it = _textures.find(asyncStruct->key);
        if (it != _textures.end())
        {
            texture = it->second;
        }
        else
        {
            // convert image to texture
            if (asyncStruct->loadSuccess)
            {
                Image* image = &(asyncStruct->image);
                // generate texture in render thread
                cc::IntrusivePtr newTexture{new Texture2D()};

                if (newTexture->initWithImage(image, asyncStruct->pixelFormat))
                {
                    this->parseNinePatchImage(image, newTexture.get(), asyncStruct->hit.entry().entryKey);
#if CC_ENABLE_CACHE_TEXTURE_DATA
                    VolatileTextureMgr::addImageTexture(newTexture.get(), asyncStruct->hit);
#endif
                    _textures.emplace(asyncStruct->key, newTexture.get());

                    if (asyncStruct->imageAlpha.getFileType() == Image::Format::ETC1)
                        newTexture->updateWithImage(&asyncStruct->imageAlpha, asyncStruct->pixelFormat, 1);
                    texture = newTexture.detach();
                }
                else
                    texture = nullptr;
            }
            else
            {
                texture = nullptr;
                CCLOG("cocos2d: failed to call TextureCache::addImageAsync(%s)", asyncStruct->hit.entry().entryKey.c_str());
            }
        }

        // call callback function
        if (asyncStruct->callback)
        {
            (asyncStruct->callback)(texture);
        }

        // release the asyncStruct
        delete asyncStruct;
        --_asyncRefCount;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(TextureCache::addImageAsyncCallBack),
                                                            this);
    }
}

Texture2D* TextureCache::addImage(std::string_view path)
{
    return addImage(path, Texture2D::getDefaultAlphaPixelFormat());
}

Texture2D* TextureCache::addImage(const FileHit& hit)
{
    return addImage(hit, Texture2D::getDefaultAlphaPixelFormat());
}

Texture2D* TextureCache::addImage(const FileHit& hit, PixelFormat format)
{
    if (!hit.adapterId())
        return nullptr;
    const auto key = textureKey(hit);
    const auto cached = _textures.find(key);
    if (cached != _textures.end())
        return cached->second;

    cc::IntrusivePtr image{new Image()};
    if (!image->initWithImageHit(hit))
        return nullptr;
    cc::IntrusivePtr texture{new Texture2D()};
    if (!texture->initWithImage(image, format))
    {
        CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", hit.entry().entryKey.c_str());
        return nullptr;
    }
    if (image->getFileType() == Image::Format::ETC1)
    {
        Image alpha;
        if (readAlpha(hit, s_etc1AlphaFileSuffix, alpha))
            texture->updateWithImage(&alpha, format, 1);
    }
    parseNinePatchImage(image, texture, hit.entry().entryKey);
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::addImageTexture(texture.get(), hit);
#endif
    _textures.emplace(key, texture.get());
    return texture.detach();
}

Texture2D* TextureCache::addImage(std::string_view path, PixelFormat format)
{
    const auto hit = FileUtils::getInstance()->findFile(path);
    return hit ? addImage(hit.value, format) : nullptr;
}

void TextureCache::parseNinePatchImage(cc::Image* image, cc::Texture2D* texture, std::string_view path)
{
    if (NinePatchImageParser::isNinePatchImage(path))
    {
        Rect frameRect = Rect(0, 0, image->getWidth(), image->getHeight());
        NinePatchImageParser parser(image, frameRect, false);
        texture->addSpriteFrameCapInset(nullptr, parser.parseCapInset());
    }
}

Texture2D* TextureCache::addImage(Image* image, std::string_view key)
{
    return addImage(image, key, Texture2D::getDefaultAlphaPixelFormat());
}

Texture2D* TextureCache::addImage(Image* image, std::string_view key, PixelFormat format)
{
    CCASSERT(image != nullptr, "TextureCache: image MUST not be nil");
    CCASSERT(image->getData() != nullptr, "TextureCache: image MUST not be nil");

    Texture2D* texture = nullptr;

    do
    {
        auto it = _textures.find(key);
        if (it != _textures.end())
        {
            texture = it->second;
            break;
        }

        cc::IntrusivePtr owner{new Texture2D()};
        if (owner->initWithImage(image, format))
        {
            // The map owns exactly this share; emplace may allocate/throw.
            _textures.emplace(key, owner.get());
            texture = owner.detach();
        }
        else
        {
            CCLOG("cocos2d: initWithImage failed!");
        }

    } while (0);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::addImage(texture, image);
#endif

    return texture;
}

bool TextureCache::reloadTexture(std::string_view fileName)
{
    const auto hit = FileUtils::getInstance()->findFile(fileName);
    return hit && reloadTexture(hit.value);
}

Texture2D* TextureCache::reloadTexture(const FileHit& hit)
{
    const auto cached = _textures.find(textureKey(hit));
    if (cached == _textures.end())
        return addImage(hit);
    auto texture = cached->second;
    Image image;
    if (!image.initWithImageHit(hit) || !texture->initWithImage(&image))
        return nullptr;
    if (image.getFileType() == Image::Format::ETC1)
    {
        Image alpha;
        if (readAlpha(hit, s_etc1AlphaFileSuffix, alpha))
            texture->updateWithImage(&alpha, texture->getPixelFormat(), 1);
    }
    return texture;
}

// TextureCache - Remove

void TextureCache::removeAllTextures()
{
    for (auto&& texture : _textures)
    {
        texture.second->release();
    }
    _textures.clear();
}

void TextureCache::removeUnusedTextures()
{
    for (auto it = _textures.cbegin(); it != _textures.cend(); /* nothing */)
    {
        Texture2D* tex = it->second;
        if (tex->getReferenceCount() == 1)
        {
            CCLOG("cocos2d: TextureCache: removing unused texture: %s", tex->getPath().c_str());

            tex->release();
            it = _textures.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void TextureCache::removeTexture(Texture2D* texture)
{
    if (!texture)
    {
        return;
    }

    for (auto it = _textures.cbegin(); it != _textures.cend(); /* nothing */)
    {
        if (it->second == texture)
        {
            it->second->release();
            it = _textures.erase(it);
            break;
        }
        else
            ++it;
    }
}

void TextureCache::removeTextureForKey(std::string_view textureKeyName)
{
    auto it = _textures.find(textureKeyName);

    if (it == _textures.end())
    {
        const auto key = textureKeyForPath(textureKeyName);
        if (!key.empty())
            it = _textures.find(key);
    }

    if (it != _textures.end())
    {
        it->second->release();
        _textures.erase(it);
    }
}

Texture2D* TextureCache::getTextureForKey(std::string_view textureKeyName) const
{
    auto it = _textures.find(textureKeyName);

    if (it == _textures.end())
    {
        const auto key = textureKeyForPath(textureKeyName);
        if (!key.empty())
            it = _textures.find(key);
    }

    if (it != _textures.end())
        return it->second;
    return nullptr;
}

std::string TextureCache::getTextureFilePath(cc::Texture2D* texture) const
{
    for (auto&& item : _textures)
    {
        if (item.second == texture)
        {
            return !item.first.empty() && item.first[0] == '\0' ? texture->getPath() : item.first;
        }
    }
    return "";
}

void TextureCache::waitForQuit()
{
    // notify sub thread to quick
    std::unique_lock<std::mutex> ul(_requestMutex);
    _needQuit = true;
    _sleepCondition.notify_one();
    ul.unlock();
    if (_loadingThread && _loadingThread->joinable())
        _loadingThread->join();

}

std::string TextureCache::getCachedTextureInfo() const
{
    std::string buffer;
    char buftmp[4096];

    unsigned int count      = 0;
    unsigned int totalBytes = 0;

    for (auto&& texture : _textures)
    {

        memset(buftmp, 0, sizeof(buftmp));

        Texture2D* tex   = texture.second;
        unsigned int bpp = tex->getBitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        auto bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        const auto name = !texture.first.empty() && texture.first[0] == '\0' ? tex->getPath() : texture.first;
        snprintf(buftmp, sizeof(buftmp) - 1, "\"%s\" rc=%d id=%p %d x %d @ %d bpp => %d KB\n", name.c_str(),
                 (int32_t)tex->getReferenceCount(), tex->getBackendTexture(), (int32_t)tex->getPixelsWide(),
                 (int32_t)tex->getPixelsHigh(), (int32_t)bpp, (int32_t)bytes / 1024);

        buffer += buftmp;
    }

    snprintf(buftmp, sizeof(buftmp) - 1, "TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)\n",
             (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f * 1024.0f));
    buffer += buftmp;

    return buffer;
}

void TextureCache::renameTextureWithKey(std::string_view srcName, std::string_view dstName)
{
    auto it = _textures.find(srcName);

    if (it == _textures.end())
    {
        const auto key = textureKeyForPath(srcName);
        if (!key.empty())
            it = _textures.find(key);
    }

    if (it != _textures.end())
    {
        const auto hit = FileUtils::getInstance()->findFile(dstName);
        if (!hit)
            return;
        auto key = textureKey(hit.value);
        if (const auto match = _textures.find(key); match != _textures.end() && match != it)
            return;
        auto texture = it->second;
        const auto oldKey = it->first;
        Image image;
        if (image.initWithImageHit(hit.value) && texture->initWithImage(&image))
        {
#if CC_ENABLE_CACHE_TEXTURE_DATA
            VolatileTextureMgr::addImageTexture(texture, hit.value);
#endif
            if (key != oldKey)
            {
                _textures.emplace(std::move(key), texture);
                _textures.erase(oldKey);
            }
        }
    }
}

#if CC_ENABLE_CACHE_TEXTURE_DATA

std::list<VolatileTexture*> VolatileTextureMgr::_textures;
bool VolatileTextureMgr::_isReloading = false;

VolatileTexture::VolatileTexture(Texture2D* t)
    : _texture(t)
    , _uiImage(nullptr)
    , _cashedImageType(kInvalid)
    , _textureData(nullptr)
    , _pixelFormat(backend::PixelFormat::RGBA8)
    , _fileName("")
    , _text("")
{}

VolatileTexture::~VolatileTexture()
{
    CC_SAFE_RELEASE(_uiImage);
}

void VolatileTextureMgr::addImageTexture(Texture2D* tt, std::string_view imageFileName)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture* vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageFile;
    vt->_fileName        = imageFileName;
    vt->_fileHit.reset();
    vt->_pixelFormat     = tt->getPixelFormat();
}

void VolatileTextureMgr::addImageTexture(Texture2D* texture, const FileHit& hit)
{
    if (_isReloading)
        return;
    auto* entry = findVolotileTexture(texture);
    entry->_fileHit = std::make_shared<FileHit>(hit);
    entry->_cashedImageType = VolatileTexture::kImageFile;
    entry->_fileName.clear();
    entry->_pixelFormat = texture->getPixelFormat();
}

void VolatileTextureMgr::addImage(Texture2D* tt, Image* image)
{
    if (tt == nullptr || image == nullptr)
        return;

    VolatileTexture* vt = findVolotileTexture(tt);
    image->retain();
    vt->_uiImage         = image;
    vt->_cashedImageType = VolatileTexture::kImage;
    vt->_pixelFormat     = tt->getPixelFormat();
}

VolatileTexture* VolatileTextureMgr::findVolotileTexture(Texture2D* tt)
{
    VolatileTexture* vt = nullptr;
    for (const auto& texture : _textures)
    {
        VolatileTexture* v = texture;
        if (v->_texture == tt)
        {
            vt = v;
            break;
        }
    }

    if (!vt)
    {
        vt = new VolatileTexture(tt);
        _textures.emplace_back(vt);
    }

    return vt;
}

void VolatileTextureMgr::addDataTexture(Texture2D* tt,
                                        void* data,
                                        int dataLen,
                                        backend::PixelFormat pixelFormat,
                                        const Vec2& contentSize)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture* vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageData;
    vt->_textureData     = data;
    vt->_dataLen         = dataLen;
    vt->_pixelFormat     = pixelFormat;
    vt->_textureSize     = contentSize;
}

void VolatileTextureMgr::addStringTexture(Texture2D* tt, const char* text, const FontDefinition& fontDefinition)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture* vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kString;
    vt->_text            = text;
    vt->_fontDefinition  = fontDefinition;
}

void VolatileTextureMgr::removeTexture(Texture2D* t)
{
    for (auto&& item : _textures)
    {
        VolatileTexture* vt = item;
        if (vt->_texture == t)
        {
            _textures.remove(vt);
            delete vt;
            break;
        }
    }
}

void VolatileTextureMgr::reloadAllTextures()
{
    _isReloading = true;
    CCLOG("reload all texture");

    for (auto&& texture : _textures)
    {
        VolatileTexture* vt = texture;

        switch (vt->_cashedImageType)
        {
        case VolatileTexture::kImageFile:
        {
            if (vt->_fileHit)
            {
                Image image;
                if (image.initWithImageHit(*vt->_fileHit) && vt->_texture->initWithImage(&image, vt->_pixelFormat) &&
                    image.getFileType() == Image::Format::ETC1)
                {
                    Image alpha;
                    if (readAlpha(*vt->_fileHit, TextureCache::getETC1AlphaFileSuffix(), alpha))
                        vt->_texture->updateWithImage(&alpha, vt->_pixelFormat, 1);
                }
                break;
            }
            reloadTexture(vt->_texture, vt->_fileName, vt->_pixelFormat);

            // etc1 support check whether alpha texture exists & load it
            Image image;
            if (image.initWithImageFile(vt->_fileName + TextureCache::getETC1AlphaFileSuffix()))
            {
                vt->_texture->updateWithImage(&image, vt->_pixelFormat, 1);
            }
        }
        break;
        case VolatileTexture::kImageData:
        {
            vt->_texture->initWithData(vt->_textureData, vt->_dataLen, vt->_pixelFormat, vt->_textureSize.width,
                                       vt->_textureSize.height);
        }
        break;
        case VolatileTexture::kString:
        {
            vt->_texture->initWithString(vt->_text.c_str(), vt->_fontDefinition);
        }
        break;
        case VolatileTexture::kImage:
        {
            vt->_texture->initWithImage(vt->_uiImage, vt->_pixelFormat);
        }
        break;
        default:
            break;
        }
    }

    _isReloading = false;
}

void VolatileTextureMgr::reloadTexture(Texture2D* texture, std::string_view filename, backend::PixelFormat pixelFormat)
{
    if (!texture)
        return;

    cc::IntrusivePtr image{new Image()};
    Data data    = FileUtils::getInstance()->getDataFromFile(filename);

    if (image->initWithImageData(data.getBytes(), data.getSize()))
        texture->initWithImage(image.get(), pixelFormat);

}

#endif  // CC_ENABLE_CACHE_TEXTURE_DATA

NS_CC_END
