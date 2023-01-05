/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "CCSpriteFrameCacheHelper.h"
#include "platform/CCFileUtils.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSpriteFrameCache.h"

USING_NS_CC;

namespace cocostudio
{

SpriteFrameCacheHelper* SpriteFrameCacheHelper::_spriteFrameCacheHelper = nullptr;

SpriteFrameCacheHelper* SpriteFrameCacheHelper::getInstance()
{
    if (!_spriteFrameCacheHelper)
    {
        _spriteFrameCacheHelper = new SpriteFrameCacheHelper();
    }

    return _spriteFrameCacheHelper;
}

void SpriteFrameCacheHelper::purge()
{
    delete _spriteFrameCacheHelper;
    _spriteFrameCacheHelper = nullptr;
}

void SpriteFrameCacheHelper::retainSpriteFrames(std::string_view plistPath)
{
    auto it = _usingSpriteFrames.find(plistPath);
    if (it != _usingSpriteFrames.end())
        return;

    std::string fullPath   = FileUtils::getInstance()->fullPathForFilename(plistPath);
    ValueMap dict          = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    auto spriteFramesCache = SpriteFrameCache::getInstance();
    ValueMap& framesDict   = dict["frames"].asValueMap();

    std::vector<SpriteFrame*> vec;
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        auto& spriteFrameName    = iter->first;

        SpriteFrame* spriteFrame = spriteFramesCache->findFrame(spriteFrameName);
        CCASSERT(spriteFrame, "spriteframe is null!");

        vec.emplace_back(spriteFrame);
        CC_SAFE_RETAIN(spriteFrame);
    }
    _usingSpriteFrames[plistPath] = std::move(vec);
}

void SpriteFrameCacheHelper::releaseSpriteFrames(std::string_view plistPath)
{
    auto it = _usingSpriteFrames.find(plistPath);
    if (it == _usingSpriteFrames.end())
        return;

    auto& vec    = it->second;
    auto itFrame = vec.begin();
    while (itFrame != vec.end())
    {
        CC_SAFE_RELEASE(*itFrame);
        ++itFrame;
    }
    vec.clear();
    _usingSpriteFrames.erase(it);
}

void SpriteFrameCacheHelper::removeSpriteFrameFromFile(std::string_view plistPath)
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistPath);
    releaseSpriteFrames(plistPath);
}

void SpriteFrameCacheHelper::addSpriteFrameFromFile(std::string_view plistPath, std::string_view imagePath)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, imagePath);
    retainSpriteFrames(plistPath);
}

SpriteFrameCacheHelper::SpriteFrameCacheHelper() {}

SpriteFrameCacheHelper::~SpriteFrameCacheHelper()
{
    auto i = _usingSpriteFrames.begin();
    while (i != _usingSpriteFrames.end())
    {
        auto j = i++;
        removeSpriteFrameFromFile(j->first);
    }
}

}  // namespace cocostudio
