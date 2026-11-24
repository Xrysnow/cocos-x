/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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

#ifndef _CCFontAtlas_h_
#define _CCFontAtlas_h_

/// @cond DO_NOT_SHOW

#include <string>
#include <unordered_map>

#include "platform/PlatformMacros.h"
#include "base/Ref.h"
#include "platform/StdC.h"  // ssize_t on windows
#include "renderer/Texture2D.h"

NS_CC_BEGIN

class Font;
struct FontLetterDefinition
{
    float U;
    float V;
    float width;
    float height;
    float offsetX;
    float offsetY;
    int textureID;
    bool validDefinition;
    int xAdvance;
    bool rotated;
};

class CC_DLL FontAtlas : public Ref
{
public:
    /**
     * @js ctor
     */
    FontAtlas(Font* theFont);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FontAtlas();

    void addLetterDefinition(char32_t utf32Char, const FontLetterDefinition& letterDefinition);
    bool getLetterDefinitionForChar(char32_t utf32Char, FontLetterDefinition& letterDefinition);


    const std::unordered_map<unsigned int, Texture2D*>& getTextures() const { return _atlasTextures; }


    void setTexture(unsigned int slot, Texture2D* texture);
    Texture2D* getTexture(int slot);

    float getLineHeight() const { return _lineHeight; }
    void setLineHeight(float newHeight);

    std::string_view getFontName() const;

    const Font* getFont() const { return _font; }

    /** sets font texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     - GL_TEXTURE_MAG_FILTER = GL_LINEAR
     */
    void setAntiAliasTexParameters();

    /** sets font texture parameters:
    - GL_TEXTURE_MIN_FILTER = GL_NEAREST
    - GL_TEXTURE_MAG_FILTER = GL_NEAREST
    */
    void setAliasTexParameters();

protected:
    /**
     * Scale each font letter by scaleFactor.
     *
     * @param scaleFactor A float scale factor for scaling font letter info.
     */
    void scaleFontLetterDefinition(float scaleFactor);

    void releaseTextures();

    std::unordered_map<unsigned int, Texture2D*> _atlasTextures;
    std::unordered_map<char32_t, FontLetterDefinition> _letterDefinitions;
    float _lineHeight           = 0.f;
    Font* _font                 = nullptr;
    std::string _name;
    bool _antialiasEnabled = true;

    friend class Label;
};

NS_CC_END

/// @endcond
#endif /* defined(__cocos2d_libs__CCFontAtlas__) */
