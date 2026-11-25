/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "2d/FontAtlasCache.h"

#include "base/Director.h"
#include "2d/FontFNT.h"
#include "2d/FontAtlas.h"
#include "2d/FontCharMap.h"
#include "2d/Label.h"
#include "platform/FileUtils.h"

NS_CC_BEGIN

hlookup::string_map<FontAtlas*> FontAtlasCache::_atlasMap;
#define ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE 255

namespace
{
std::string bitmapAtlasKey(const FileHit& hit, const Rect& rect, bool rotated)
{
    char prefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(prefix, sizeof(prefix), "%.2f %.2f %.2f %.2f %d ", rect.origin.x, rect.origin.y,
             rect.size.width, rect.size.height, static_cast<int>(rotated));
    return prefix + std::to_string(hit.adapterId()) + ':' + hit.entry().entryKey;
}
}

void FontAtlasCache::purgeCachedData()
{
    auto atlasMapCopy = _atlasMap;
    for (auto&& atlas : atlasMapCopy)
    {
        atlas.second->release();
    }
    _atlasMap.clear();
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(std::string_view fontFileName)
{
    return getFontAtlasFNT(fontFileName, Rect::ZERO, false);
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(std::string_view fontFileName, std::string_view subTextureKey)
{
    const auto hit = FileUtils::getInstance()->findFile(fontFileName);
    if (!hit)
        return nullptr;
    auto atlasName = std::to_string(subTextureKey.size()) + ':' + std::string(subTextureKey) + ' ' +
        std::to_string(hit.value.adapterId()) + ':' + hit.value.entry().entryKey;

    const auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        const auto font = FontFNT::create(hit.value, subTextureKey);

        if (font)
        {
            const auto tempAtlas = font->newFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(std::string_view fontFileName, const Rect& imageRect, bool imageRotated)
{
    const auto hit = FileUtils::getInstance()->findFile(fontFileName);
    if (!hit)
        return nullptr;
    const auto atlasName = bitmapAtlasKey(hit.value, imageRect, imageRotated);

    const auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        const auto font = FontFNT::create(hit.value, imageRect, imageRotated);

        if (font)
        {
            const auto tempAtlas = font->newFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasFNT(std::string_view fontFileName, const Vec2& imageOffset)
{
    return getFontAtlasFNT(fontFileName, Rect(imageOffset.x, imageOffset.y, 0, 0), false);
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(std::string_view plistFile)
{
    std::string_view atlasName = plistFile;

    auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        auto font = FontCharMap::create(plistFile);

        if (font)
        {
            auto tempAtlas = font->newFontAtlas();
            if (tempAtlas)
            {
                hlookup::set_item(_atlasMap, atlasName, tempAtlas);  // _atlasMap[atlasName] = tempAtlas;
                return tempAtlas;
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    char key[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(key, sizeof(key), "name:%p_%d_%d_%d", texture->getBackendTexture(), itemWidth, itemHeight, startCharMap);
    std::string atlasName = key;

    auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        auto font = FontCharMap::create(texture, itemWidth, itemHeight, startCharMap);

        if (font)
        {
            auto tempAtlas = font->newFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

FontAtlas* FontAtlasCache::getFontAtlasCharMap(std::string_view charMapFile,
                                               int itemWidth,
                                               int itemHeight,
                                               int startCharMap)
{
    char keyPrefix[ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE];
    snprintf(keyPrefix, ATLAS_MAP_KEY_PREFIX_BUFFER_SIZE, "%d %d %d ", itemWidth, itemHeight, startCharMap);
    std::string atlasName(keyPrefix);
    atlasName += charMapFile;

    auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        auto font = FontCharMap::create(charMapFile, itemWidth, itemHeight, startCharMap);

        if (font)
        {
            auto tempAtlas = font->newFontAtlas();
            if (tempAtlas)
            {
                _atlasMap[atlasName] = tempAtlas;
                return _atlasMap[atlasName];
            }
        }
    }
    else
        return it->second;

    return nullptr;
}

bool FontAtlasCache::releaseFontAtlas(FontAtlas* atlas)
{
    if (nullptr != atlas)
    {
        if (atlas->getReferenceCount() == 1)
        {
            for (auto&& item : _atlasMap)
            {
                if (item.second == atlas)
                {
                    _atlasMap.erase(item.first);
                    break;
                }
            }
        }
        atlas->release();
        return true;
    }

    return false;
}

void FontAtlasCache::reloadFontAtlasFNT(std::string_view fontFileName, const Rect& imageRect, bool imageRotated)
{
    const auto hit = FileUtils::getInstance()->findFile(fontFileName);
    if (!hit)
        return;
    const auto atlasName = bitmapAtlasKey(hit.value, imageRect, imageRotated);

    auto it = _atlasMap.find(atlasName);
    if (it != _atlasMap.end())
    {
        CC_SAFE_RELEASE_NULL(it->second);
        _atlasMap.erase(it);
    }
    FontFNT::reloadBMFontResource(hit.value);
    auto font = FontFNT::create(hit.value, imageRect, imageRotated);
    if (font)
    {
        auto tempAtlas = font->newFontAtlas();
        if (tempAtlas)
        {
            _atlasMap[atlasName] = tempAtlas;
        }
    }
}

void FontAtlasCache::reloadFontAtlasFNT(std::string_view fontFileName, const Vec2& imageOffset)
{
    reloadFontAtlasFNT(fontFileName, Rect(imageOffset.x, imageOffset.y, 0, 0), false);
}

NS_CC_END
