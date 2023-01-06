/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "2d/CCSpriteFrameCache.h"

#include <vector>

#include "2d/CCSprite.h"
#include "2d/CCAutoPolygon.h"
#include "2d/CCPlistSpriteSheetLoader.h"
#include "platform/CCFileUtils.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCTexture2D.h"
#include "base/CCNinePatchImageParser.h"

using namespace std;

NS_CC_BEGIN

static SpriteFrameCache* _sharedSpriteFrameCache = nullptr;

SpriteFrameCache* SpriteFrameCache::getInstance()
{
    if (!_sharedSpriteFrameCache)
    {
        _sharedSpriteFrameCache = new SpriteFrameCache();
        _sharedSpriteFrameCache->init();
    }

    return _sharedSpriteFrameCache;
}

void SpriteFrameCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedSpriteFrameCache);
}

bool SpriteFrameCache::init()
{
    _spriteFrames.reserve(20);
    clear();

    registerSpriteSheetLoader(std::make_shared<PlistSpriteSheetLoader>());

    return true;
}

SpriteFrameCache::~SpriteFrameCache() {}

void SpriteFrameCache::addSpriteFramesWithFile(std::string_view spriteSheetFileName,
                                               std::string_view textureFileName,
                                               uint32_t spriteSheetFormat)
{
    auto* loader = getSpriteSheetLoader(spriteSheetFormat);
    if (loader)
    {
        loader->load(spriteSheetFileName, textureFileName, *this);
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(std::string_view spriteSheetFileName,
                                               Texture2D* texture,
                                               uint32_t spriteSheetFormat)
{
    auto* loader = getSpriteSheetLoader(spriteSheetFormat);
    if (loader)
    {
        loader->load(spriteSheetFileName, texture, *this);
    }
}

void SpriteFrameCache::addSpriteFramesWithFile(std::string_view spriteSheetFileName, uint32_t spriteSheetFormat)
{
    auto* loader = getSpriteSheetLoader(spriteSheetFormat);
    if (loader)
    {
        loader->load(spriteSheetFileName, *this);
    }
}

void SpriteFrameCache::addSpriteFramesWithFileContent(const Data& content,
                                                      Texture2D* texture,
                                                      uint32_t spriteSheetFormat)
{
    auto* loader = getSpriteSheetLoader(spriteSheetFormat);
    if (loader)
    {
        loader->load(content, texture, *this);
    }
}

bool SpriteFrameCache::isSpriteFramesWithFileLoaded(std::string_view plist) const
{
    return isSpriteSheetInUse(plist) && isPlistFull(plist);
}

void SpriteFrameCache::addSpriteFrame(SpriteFrame* frame, std::string_view frameName)
{
    CCASSERT(frame, "frame should not be nil");

    const std::string name = "by#addSpriteFrame()";
    auto&& itr             = _spriteSheets.find(name);
    if (itr != _spriteSheets.end())
    {
        insertFrame(itr->second, frameName, frame);
    }
    else
    {
        auto spriteSheet  = std::make_shared<SpriteSheet>();
        spriteSheet->path = name;
        insertFrame(spriteSheet, frameName, frame);
    }
}

void SpriteFrameCache::removeSpriteFrames()
{
    clear();
}

void SpriteFrameCache::removeUnusedSpriteFrames()
{
    auto removed = false;
    std::vector<std::string_view> toRemoveFrames;

    const auto& frames = getSpriteFrames();
    for (auto&& iter : frames)
    {
        auto* spriteFrame = iter.second;
        if (spriteFrame->getReferenceCount() == 1)
        {
            toRemoveFrames.emplace_back(iter.first);
            spriteFrame->getTexture()->removeSpriteFrameCapInset(spriteFrame);
            CCLOG("cocos2d: SpriteFrameCache: removing unused frame: %s", iter.first.c_str());
            removed = true;
        }
    }

    if (removed)
    {
        eraseFrames(toRemoveFrames);
    }
}

void SpriteFrameCache::removeSpriteFrameByName(std::string_view name)
{
    // explicit nil handling
    if (name.empty())
        return;

    eraseFrame(name);
}

void SpriteFrameCache::removeSpriteFramesFromFile(std::string_view atlasPath)
{
    // const auto fullPath = FileUtils::getInstance()->fullPathForFilename(plist);
    // auto dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    // if (dict.empty())
    //{
    //     CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFile: create dict by %s fail.",plist.c_str());
    //     return;
    // }
    // removeSpriteFramesFromDictionary(dict);

    // remove it from the cache
    removeSpriteSheet(atlasPath);
}

void SpriteFrameCache::removeSpriteFramesFromFileContent(std::string_view plist_content)
{
    auto dict =
        FileUtils::getInstance()->getValueMapFromData(plist_content.data(), static_cast<int>(plist_content.size()));
    if (dict.empty())
    {
        CCLOG("cocos2d:SpriteFrameCache:removeSpriteFramesFromFileContent: create dict by fail.");
        return;
    }
    removeSpriteFramesFromDictionary(dict);
}

void SpriteFrameCache::removeSpriteFramesFromDictionary(ValueMap& dictionary)
{
    if (dictionary["frames"].getType() != cocos2d::Value::Type::MAP)
        return;

    const auto& framesDict = dictionary["frames"].asValueMap();
    std::vector<std::string_view> keysToRemove;

    for (const auto& iter : framesDict)
    {
        if (findFrame(iter.first))
        {
            keysToRemove.emplace_back(iter.first);
        }
    }

    eraseFrames(keysToRemove);
}

void SpriteFrameCache::removeSpriteFramesFromTexture(Texture2D* texture)
{
    std::vector<std::string_view> keysToRemove;

    for (auto&& iter : getSpriteFrames())
    {
        auto key    = iter.first;
        auto* frame = findFrame(key);
        if (frame && (frame->getTexture() == texture))
        {
            keysToRemove.emplace_back(key);
        }
    }

    eraseFrames(keysToRemove);
}

SpriteFrame* SpriteFrameCache::getSpriteFrameByName(std::string_view name)
{
    auto* frame = findFrame(name);
    if (!frame)
    {
        CCLOG("cocos2d: SpriteFrameCache: Frame '%s' isn't found", name.data());
    }
    return frame;
}

bool SpriteFrameCache::reloadTexture(std::string_view spriteSheetFileName)
{
    CCASSERT(!spriteSheetFileName.empty(), "plist filename should not be nullptr");

    const auto spriteSheetItr = _spriteSheets.find(spriteSheetFileName);
    if (spriteSheetItr == _spriteSheets.end())
    {
        return false;  // Sprite sheet wasn't loaded, so don't reload it
    }

    const auto format = spriteSheetItr->second->format;

    if (isSpriteSheetInUse(spriteSheetFileName))
    {
        removeSpriteSheet(
            spriteSheetFileName);  // we've removed the associated entry, so spriteSheetItr is no longer valid
    }
    else
    {
        // If one plist hasn't be loaded, we don't load it here.
        return false;
    }

    auto* loader = getSpriteSheetLoader(format);
    if (loader)
    {
        loader->reload(spriteSheetFileName, *this);
    }
    return true;
}

void SpriteFrameCache::insertFrame(const std::shared_ptr<SpriteSheet>& spriteSheet,
                                   std::string_view frameName,
                                   SpriteFrame* spriteFrame)
{
    spriteSheet->frames.emplace(frameName);
    _spriteFrames.insert(frameName, spriteFrame);  // add SpriteFrame
    _spriteSheets[spriteSheet->path] = spriteSheet;
    hlookup::set_item(_spriteFrameToSpriteSheetMap, frameName,
                      spriteSheet);  // _spriteFrameToSpriteSheetMap[frameName] = spriteSheet;  // insert
                                     // index frameName->plist
}

bool SpriteFrameCache::eraseFrame(std::string_view frameName)
{
    // drop SpriteFrame
    const auto itFrame = _spriteFrameToSpriteSheetMap.find(frameName);
    bool hint = itFrame != _spriteFrameToSpriteSheetMap.end();
    if (hint)
    {
        auto& spriteSheet = itFrame->second;
        spriteSheet->full = false;
        spriteSheet->frames.erase(frameName);

        if (spriteSheet->frames.empty())
        {
            _spriteSheets.erase(spriteSheet->path);
        }

        _spriteFrameToSpriteSheetMap.erase(itFrame);  // update index frame->plist

        // erase all sprite sheets if all frames are erased
        // if (_spriteFrameToSpriteSheetMap.empty())
        //{
        //    _spriteSheets.clear();
        //}
    }
    _spriteFrames.erase(frameName);
    return hint;
}

bool SpriteFrameCache::eraseFrames(const std::vector<std::string_view>& frames)
{
    auto ret = false;
    for (const auto& frame : frames)
    {
        ret |= eraseFrame(frame);
    }

    return ret;
}

bool SpriteFrameCache::removeSpriteSheet(std::string_view spriteSheetFileName)
{
    auto it = _spriteSheets.find(spriteSheetFileName);
    if (it == _spriteSheets.end())
        return false;

    auto& frames = it->second->frames;
    for (const auto& f : frames)
    {
        // !!do not!! call `_spriteFrames.erase(f);` to erase SpriteFrame
        // only erase index here
        _spriteFrames.erase(f);
        _spriteFrameToSpriteSheetMap.erase(f);  // erase plist frame frameName->plist
    }
    _spriteSheets.erase(spriteSheetFileName);  // update index plist->[frameNames]

    return true;
}

void SpriteFrameCache::clear()
{
    _spriteSheets.clear();
    _spriteFrameToSpriteSheetMap.clear();
    _spriteFrames.clear();
}

bool SpriteFrameCache::hasFrame(std::string_view frame) const
{
    return _spriteFrameToSpriteSheetMap.find(frame) != _spriteFrameToSpriteSheetMap.end();
}

bool SpriteFrameCache::isSpriteSheetInUse(std::string_view spriteSheetFileName) const
{
    const auto spriteSheetItr = _spriteSheets.find(spriteSheetFileName);
    return spriteSheetItr != _spriteSheets.end() && !spriteSheetItr->second->frames.empty();
}

SpriteFrame* SpriteFrameCache::findFrame(std::string_view frame)
{
    return _spriteFrames.at(frame);
}

void SpriteFrameCache::addSpriteFrameCapInset(SpriteFrame* spriteFrame, const Rect& capInsets, Texture2D* texture)
{
    texture->addSpriteFrameCapInset(spriteFrame, capInsets);
}

StringMap<SpriteFrame*>& SpriteFrameCache::getSpriteFrames()
{
    return _spriteFrames;
}

void SpriteFrameCache::registerSpriteSheetLoader(std::shared_ptr<ISpriteSheetLoader> loader)
{
    auto format = loader->getFormat();

    if (_spriteSheetLoaders.find(format) != _spriteSheetLoaders.end())
    {
        return;
    }

    _spriteSheetLoaders.emplace(format, std::move(loader));
}

void SpriteFrameCache::deregisterSpriteSheetLoader(uint32_t spriteSheetFormat)
{
    auto&& itr = _spriteSheetLoaders.find(spriteSheetFormat);
    if (itr != _spriteSheetLoaders.end())
    {
        _spriteSheetLoaders.erase(itr);
    }
}

ISpriteSheetLoader* SpriteFrameCache::getSpriteSheetLoader(uint32_t spriteSheetFormat)
{
    auto&& itr = _spriteSheetLoaders.find(spriteSheetFormat);
    if (itr != _spriteSheetLoaders.end())
    {
        return itr->second.get();
    }

    return nullptr;
}

NS_CC_END
