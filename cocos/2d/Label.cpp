/****************************************************************************
 Copyright (c) 2013      Zynga Inc.
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

#include "2d/Label.h"
#include "2d/label/FontLabelState.h"
#include "2d/label/LabelLetter.h"
#include <algorithm>
#include <stddef.h>  // offsetof
#include "base/ccTypes.h"
#include "2d/Font.h"
#include "2d/FontAtlasCache.h"
#include "2d/FontAtlas.h"
#include "2d/Sprite.h"
#include "2d/SpriteBatchNode.h"
#include "2d/DrawNode.h"
#include "2d/Camera.h"
#include "base/ccUTF8.h"
#include "base/Macros.h"
#include "platform/PlatformMacros.h"
#include "platform/FileUtils.h"
#include "renderer/Renderer.h"
#include "renderer/RenderCommand.h"
#include "base/Director.h"
#include "base/EventListenerCustom.h"
#include "base/EventDispatcher.h"
#include "base/EventCustom.h"
#include "base/ccUtils.h"
#include "2d/FontFNT.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/ProgramStateRegistry.h"

NS_CC_BEGIN

namespace
{
void updateBlend(backend::BlendDescriptor& blendDescriptor, BlendFunc blendFunc)
{
    blendDescriptor.blendEnabled = true;
    if (blendFunc == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendDescriptor.sourceRGBBlendFactor        = backend::BlendFactor::SRC_ALPHA;
        blendDescriptor.destinationRGBBlendFactor   = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        blendDescriptor.sourceAlphaBlendFactor      = backend::BlendFactor::SRC_ALPHA;
        blendDescriptor.destinationAlphaBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    }
    else
    {
        blendDescriptor.sourceRGBBlendFactor        = backend::BlendFactor::ONE;
        blendDescriptor.destinationRGBBlendFactor   = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
        blendDescriptor.sourceAlphaBlendFactor      = backend::BlendFactor::ONE;
        blendDescriptor.destinationAlphaBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    }
}
}  // namespace

Label::BatchCommand::BatchCommand()
{
    textCommand.setDrawType(CustomCommand::DrawType::ELEMENT);
    textCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);
    shadowCommand.setDrawType(CustomCommand::DrawType::ELEMENT);
    shadowCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);
    outLineCommand.setDrawType(CustomCommand::DrawType::ELEMENT);
    outLineCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE);
}

Label::BatchCommand::~BatchCommand() = default;

void Label::BatchCommand::setProgramState(backend::ProgramState* programState)
{
    const auto commands = getCommandArray();
    for (std::size_t i = 0; i < commands.size(); ++i)
    {
        cc::IntrusivePtr<backend::ProgramState> state = programState ? programState->clone() : nullptr;
        commands[i]->getPipelineDescriptor().programState = state.get();
        programStates[i] = std::move(state);
    }
}

std::array<CustomCommand*, 3> Label::BatchCommand::getCommandArray()
{
    return std::array<CustomCommand*, 3>{&textCommand, &shadowCommand, &outLineCommand};
}

cc::IntrusivePtr<Label> Label::create()
{
    cc::IntrusivePtr ret{new Label};
    return ret;
}

cc::IntrusivePtr<Label> Label::createWithSystemFont(std::string_view text,
                                   std::string_view font,
                                   float fontSize,
                                   const Vec2& dimensions /* = Vec2::ZERO */,
                                   TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                                   TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    cc::IntrusivePtr ret{new Label(hAlignment, vAlignment)};

    ret->setSystemFontName(font);
    ret->setSystemFontSize(fontSize);
    ret->setDimensions(dimensions.width, dimensions.height);
    ret->setString(text);

    return ret;
}

cc::IntrusivePtr<Label> Label::createWithTTF(std::string_view text,
                            std::string_view fontFile,
                            float fontSize,
                            const Vec2& dimensions /* = Vec2::ZERO */,
                            TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
                            TextVAlignment vAlignment /* = TextVAlignment::TOP */)
{
    cc::IntrusivePtr ret{new Label(hAlignment, vAlignment)};

    if (ret->initWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment))
    {
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithTTF(const TTFConfig& ttfConfig,
                            std::string_view text,
                            TextHAlignment hAlignment /* = TextHAlignment::CENTER */,
                            int maxLineWidth /* = 0 */)
{
    const auto mode = ttfConfig.outlineSize > 0 || ttfConfig.distanceFieldEnabled ? FontRasterMode::Sdf : FontRasterMode::Bitmap;
    cc::IntrusivePtr ret{new Label(mode, hAlignment)};

    if (ret->initWithTTF(ttfConfig, text, hAlignment, maxLineWidth))
    {
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithBMFont(std::string_view bmfontPath,
                               std::string_view text,
                               const TextHAlignment& hAlignment,
                               int maxLineWidth)
{
    cc::IntrusivePtr ret{new Label(hAlignment)};

    if (ret->setBMFontFilePath(bmfontPath))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithBMFont(std::string_view bmfontPath,
                               std::string_view text,
                               const TextHAlignment& hAlignment,
                               int maxLineWidth,
                               const Rect& imageRect,
                               bool imageRotated)
{
    cc::IntrusivePtr ret{new Label(hAlignment)};

    if (ret->setBMFontFilePath(bmfontPath, imageRect, imageRotated))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithBMFont(std::string_view bmfontPath,
                               std::string_view text,
                               const TextHAlignment& hAlignment,
                               int maxLineWidth,
                               std::string_view subTextureKey)
{
    cc::IntrusivePtr ret{new Label(hAlignment)};

    if (ret->setBMFontFilePath(bmfontPath, subTextureKey))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->setString(text);
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithBMFont(std::string_view bmfontPath,
                               std::string_view text,
                               const TextHAlignment& hAlignment,
                               int maxLineWidth,
                               const Vec2& imageOffset)
{
    return createWithBMFont(bmfontPath, text, hAlignment, maxLineWidth, Rect(imageOffset.x, imageOffset.y, 0, 0),
                            false);
}

cc::IntrusivePtr<Label> Label::createWithCharMap(std::string_view plistFile)
{
    cc::IntrusivePtr ret{new Label()};

    if (ret->setCharMap(plistFile))
    {
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    cc::IntrusivePtr ret{new Label()};

    if (ret->setCharMap(texture, itemWidth, itemHeight, startCharMap))
    {
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Label> Label::createWithCharMap(std::string_view charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    cc::IntrusivePtr ret{new Label()};

    if (ret->setCharMap(charMapFile, itemWidth, itemHeight, startCharMap))
    {
        return ret;
    }

    return nullptr;
}

bool Label::setCharMap(std::string_view plistFile)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(plistFile);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::initWithTTF(std::string_view text,
                        std::string_view fontFilePath,
                        float fontSize,
                        const Vec2& dimensions,
                        TextHAlignment /*hAlignment*/,
                        TextVAlignment /*vAlignment*/)
{
    if (!setTTFConfig(TTFConfig(fontFilePath, fontSize))) return false;
    setDimensions(dimensions.width, dimensions.height);
    setString(text);
    return true;
}

bool Label::initWithTTF(const TTFConfig& ttfConfig,
                        std::string_view text,
                        TextHAlignment /*hAlignment*/,
                        int maxLineWidth)
{
    if (setTTFConfig(ttfConfig))
    {
        setMaxLineWidth(maxLineWidth);
        setString(text);
        return true;
    }
    return false;
}

bool Label::setCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(texture, itemWidth, itemHeight, startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setCharMap(std::string_view charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
    auto newAtlas = FontAtlasCache::getFontAtlasCharMap(charMapFile, itemWidth, itemHeight, startCharMap);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    _currentLabelType = LabelType::CHARMAP;
    setFontAtlas(newAtlas);

    return true;
}

Label::Label(TextHAlignment hAlignment /* = TextHAlignment::LEFT */,
             TextVAlignment vAlignment /* = TextVAlignment::TOP */)
    : Label(FontRasterMode::Bitmap, hAlignment, vAlignment)
{}

Label::Label(FontRasterMode mode, TextHAlignment hAlignment, TextVAlignment vAlignment)
    : _rasterMode(mode)
    , _textSprite(nullptr)
    , _shadowNode(nullptr)
    , _fontAtlas(nullptr)
    , _reusedLetter(nullptr)
    , _horizontalKernings(nullptr)
    , _boldEnabled(false)
    , _underlineNode(nullptr)
    , _strikethroughEnabled(false)
{
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    reset();
    _hAlignment = hAlignment;
    _vAlignment = vAlignment;

#if CC_LABEL_DEBUG_DRAW
    auto debugDrawNodeOwner = DrawNode::create();
        _debugDrawNode = debugDrawNodeOwner.get();
    addChild(_debugDrawNode);
#endif

}

Label::~Label()
{
    delete[] _horizontalKernings;

    if (_fontAtlas)
    {
        Node::removeAllChildrenWithCleanup(true);
        _reusedLetter.reset();
        _batchNodes.clear();
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }
    _batchCommands.clear();

    _textSprite.reset();
    _shadowNode.reset();
}

void Label::reset()
{
    _fileState.reset();
    _textSprite.reset();
    _shadowNode.reset();
    Node::removeAllChildrenWithCleanup(true);
    _reusedLetter.reset();
    _letters.clear();
    _batchNodes.clear();
    _batchCommands.clear();
    _lettersInfo.clear();
    if (_fontAtlas)
    {
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
        _fontAtlas = nullptr;
    }

    _currentLabelType = LabelType::STRING_TEXTURE;
    _currLabelEffect  = LabelEffect::NORMAL;
    _contentDirty     = false;
    _numberOfLines    = 0;
    _lengthOfString   = 0;
    _utf32Text.clear();
    _utf8Text.clear();

    TTFConfig temp;
    _fontConfig  = temp;
    _outlineSize = 0.f;

    _bmFontPath      = "";
    _bmSubTextureKey = "";
    _bmRect          = Rect::ZERO;
    _bmRotated       = false;

    _systemFontDirty = false;
    _systemFont      = "Helvetica";
    _systemFontSize  = CC_DEFAULT_FONT_LABEL_SIZE;

    if (_horizontalKernings)
    {
        delete[] _horizontalKernings;
        _horizontalKernings = nullptr;
    }
    _additionalKerning      = 0.f;
    _lineHeight             = 0.f;
    _lineSpacing            = 0.f;
    _maxLineWidth           = 0.f;
    _labelDimensions.width  = 0.f;
    _labelDimensions.height = 0.f;
    _labelWidth             = 0.f;
    _labelHeight            = 0.f;
    _lineBreakWithoutSpaces = false;
    _hAlignment             = TextHAlignment::LEFT;
    _vAlignment             = TextVAlignment::TOP;

    _effectColorF = Color4F::BLACK;
    _textColor    = Color4B::WHITE;
    _textColorF   = Color4F::WHITE;
    setColor(Color3B::WHITE);

    _shadowDirty      = false;
    _shadowEnabled    = false;
    _shadowBlurRadius = 0.f;

    _uniformEffectColor = -1;
    _uniformEffectType  = -1;
    _uniformTextColor   = -1;

    _useDistanceField   = false;
    _useA8Shader        = false;
    _clipEnabled        = false;
    _blendFuncDirty     = false;
    _blendFunc          = BlendFunc::ALPHA_PREMULTIPLIED;
    _isOpacityModifyRGB = false;
    _insideBounds       = true;
    _enableWrap         = true;
    _bmFontSize         = -1;
    _bmfontScale        = 1.0f;
    _overflow           = Overflow::NONE;
    _originalFontSize   = 0.0f;
    _boldEnabled        = false;
    if (_underlineNode)
    {
        removeChild(_underlineNode);
        _underlineNode = nullptr;
    }
    _strikethroughEnabled = false;
    setRotationSkewX(0);  // reverse italics
}

//  ETC1 ALPHA supports, for LabelType::BMFONT & LabelType::CHARMAP
static Texture2D* _getTexture(Label* label)
{
    auto fontAtlas     = label->getFontAtlas();
    Texture2D* texture = nullptr;
    if (fontAtlas != nullptr)
    {
        auto textures = fontAtlas->getTextures();
        if (!textures.empty())
        {
            texture = textures.begin()->second;
        }
    }
    return texture;
}

void Label::setVertexLayout()
{
    _programState->validateSharedVertexLayout(VertexLayoutHelper::setupSprite);
}

bool Label::setProgramState(cc::IntrusivePtr<backend::ProgramState> state)
{
    if (_programState.get() == state.get())
        return false;

    _quadCommand.getPipelineDescriptor().programState = state.get();
    const bool installed = Node::setProgramState(std::move(state));
    if (installed)
    {
        updateUniformLocations();
        setVertexLayout();
    }

    for (auto&& batch : _batchCommands)
    {
        updateBatchCommand(batch);
    }

    return installed;
}

void Label::updateShaderProgram()
{
    uint32_t programType = backend::ProgramType::POSITION_TEXTURE_COLOR;
    if (_currentLabelType == LabelType::TTF && _fileState)
        programType = backend::ProgramType::FONT_GLYPH;
    else if (_currentLabelType == LabelType::BMFONT || _currentLabelType == LabelType::CHARMAP)
    {
        auto texture = _getTexture(this);
        if (texture)
        {
            programType =
                backend::ProgramStateRegistry::getInstance()->getProgramType(programType, texture->getSamplerFlags());
        }
    }
    else
    {
        switch (_currLabelEffect)
        {
        case cc::LabelEffect::NORMAL:
            if (_useDistanceField)
            {
                programType = backend::ProgramType::LABEL_DISTANCE_NORMAL;
            }
            else if (_useA8Shader)
            {
                programType = backend::ProgramType::LABEL_NORMAL;
            }
            else
            {
                auto texture = _getTexture(this);
                if (texture)
                {
                    programType = backend::ProgramStateRegistry::getInstance()->getProgramType(
                        programType, texture->getSamplerFlags());
                }
            }
            break;
        case cc::LabelEffect::OUTLINE:
        {
            programType = backend::ProgramType::LABLE_OUTLINE;
        }
        break;
        case cc::LabelEffect::GLOW:
            if (_useDistanceField)
            {
                programType = backend::ProgramType::LABLE_DISTANCEFIELD_GLOW;
            }
            break;
        default:
            return;
        }
    }

    auto* program = backend::Program::getBuiltinProgram(programType);
    setProgramState(cc::IntrusivePtr{new backend::ProgramState(program)});
}

void Label::updateBatchCommand(Label::BatchCommand& batch)
{
    batch.setProgramState(_programState.get());
}

void Label::updateUniformLocations()
{
    _mvpMatrixLocation   = _programState->getUniformLocation(backend::Uniform::MVP_MATRIX);
    _textureLocation     = _programState->getUniformLocation(backend::Uniform::TEXTURE);
    _textColorLocation   = _programState->getUniformLocation(backend::Uniform::TEXT_COLOR);
    _effectColorLocation = _programState->getUniformLocation(backend::Uniform::EFFECT_COLOR);
    _effectTypeLocation  = _programState->getUniformLocation(backend::Uniform::EFFECT_TYPE);
}

void Label::setFontAtlas(FontAtlas* atlas, bool distanceFieldEnabled /* = false */, bool useA8Shader /* = false */)
{
    if (atlas)
    {
        _systemFontDirty = false;
    }

    if (atlas == _fontAtlas)
        return;

    CC_SAFE_RETAIN(atlas);
    if (_fontAtlas)
    {
        _batchNodes.clear();
        FontAtlasCache::releaseFontAtlas(_fontAtlas);
    }
    _fontAtlas = atlas;
    _fileState.reset();

    if (_reusedLetter == nullptr)
    {
        _reusedLetter = Sprite::create();
        _reusedLetter->setOpacityModifyRGB(_isOpacityModifyRGB);
        _reusedLetter->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    }

    if (_fontAtlas)
    {
        _lineHeight      = _fontAtlas->getLineHeight();
        _contentDirty    = true;
        _systemFontDirty = false;
    }
    _useDistanceField = distanceFieldEnabled;
    _useA8Shader      = useA8Shader;

    if (_currentLabelType != LabelType::TTF)
    {
        _currLabelEffect = LabelEffect::NORMAL;
        updateShaderProgram();
    }
}

bool Label::setTTFConfig(const TTFConfig& ttfConfig)
{
    if (!setTTFConfigInternal(ttfConfig)) return false;
    _originalFontSize = ttfConfig.fontSize;
    return true;
}

bool Label::setBMFontFilePath(std::string_view bmfontFilePath, float fontSize)
{
    FontAtlas* newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    // assign the default fontSize
    if (std::abs(fontSize) < FLT_EPSILON)
    {
        FontFNT* bmFont = (FontFNT*)newAtlas->getFont();
        if (bmFont)
        {
            float originalFontSize = bmFont->getOriginalFontSize();
            _bmFontSize            = originalFontSize / CC_CONTENT_SCALE_FACTOR();
        }
    }

    if (fontSize > 0.0f)
    {
        _bmFontSize = fontSize;
    }

    _bmFontPath = bmfontFilePath;

    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setBMFontData(const FileHit& source, std::string_view data)
{
    const auto font = FontFNT::createFromData(source, data);
    if (!font)
        return false;
    cc::IntrusivePtr<FontAtlas> atlas{font->newFontAtlas(), cc::adopt_ref};
    if (!atlas)
        return false;
    _bmFontSize = font->getOriginalFontSize() / CC_CONTENT_SCALE_FACTOR();
    _bmFontPath = source.entry().entryKey;
    _bmSubTextureKey.clear();
    _bmRect = Rect::ZERO;
    _bmRotated = false;
    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(atlas);
    return true;
}

bool Label::copyBMFontFrom(const Label& source)
{
    if (source._currentLabelType != LabelType::BMFONT || !source._fontAtlas)
        return false;
    _bmFontPath = source._bmFontPath;
    _bmSubTextureKey = source._bmSubTextureKey;
    _bmRect = source._bmRect;
    _bmRotated = source._bmRotated;
    _bmFontSize = source._bmFontSize;
    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(source._fontAtlas);
    return true;
}

bool Label::setBMFontFilePath(std::string_view bmfontFilePath, const Rect& imageRect, bool imageRotated, float fontSize)
{
    FontAtlas* newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath, imageRect, imageRotated);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    // assign the default fontSize
    if (std::abs(fontSize) < FLT_EPSILON)
    {
        FontFNT* bmFont = (FontFNT*)newAtlas->getFont();
        if (bmFont)
        {
            float originalFontSize = bmFont->getOriginalFontSize();
            _bmFontSize            = originalFontSize / CC_CONTENT_SCALE_FACTOR();
        }
    }

    if (fontSize > 0.0f)
    {
        _bmFontSize = fontSize;
    }

    _bmFontPath = bmfontFilePath;
    _bmRect     = imageRect;
    _bmRotated  = imageRotated;

    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setBMFontFilePath(std::string_view bmfontFilePath, std::string_view subTextureKey, float fontSize)
{
    FontAtlas* newAtlas = FontAtlasCache::getFontAtlasFNT(bmfontFilePath, subTextureKey);

    if (!newAtlas)
    {
        reset();
        return false;
    }

    // assign the default fontSize
    if (std::abs(fontSize) < FLT_EPSILON)
    {
        FontFNT* bmFont = (FontFNT*)newAtlas->getFont();
        if (bmFont)
        {
            float originalFontSize = bmFont->getOriginalFontSize();
            _bmFontSize            = originalFontSize / CC_CONTENT_SCALE_FACTOR();
        }
    }

    if (fontSize > 0.0f)
    {
        _bmFontSize = fontSize;
    }

    _bmFontPath      = bmfontFilePath;
    _bmSubTextureKey = subTextureKey;

    _currentLabelType = LabelType::BMFONT;
    setFontAtlas(newAtlas);

    return true;
}

bool Label::setBMFontFilePath(std::string_view bmfontFilePath, const Vec2& imageOffset, float fontSize)
{
    return setBMFontFilePath(bmfontFilePath, Rect(imageOffset.x, imageOffset.y, 0, 0), false);
}

void Label::setString(std::string_view text)
{
    if (text.compare(_utf8Text))
    {
        if (_fileState)
            _fileState->visible = {};
        _utf8Text     = text;
        _contentDirty = true;

        std::u32string utf32String;
        if (StringUtils::UTF8ToUTF32(_utf8Text, utf32String))
        {
            _utf32Text = utf32String;
        }
    }
}

void Label::setAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment)
{
    if (hAlignment != _hAlignment || vAlignment != _vAlignment)
    {
        _hAlignment = hAlignment;
        _vAlignment = vAlignment;

        _contentDirty = true;
    }
}

void Label::setMaxLineWidth(float maxLineWidth)
{
    if (_labelWidth == 0 && _maxLineWidth != maxLineWidth)
    {
        _maxLineWidth = maxLineWidth;
        _contentDirty = true;
    }
}

void Label::setDimensions(float width, float height)
{
    if (_overflow == Overflow::RESIZE_HEIGHT)
    {
        height = 0;
    }
    if (height != _labelHeight || width != _labelWidth)
    {
        _labelWidth             = width;
        _labelHeight            = height;
        _labelDimensions.width  = width;
        _labelDimensions.height = height;

        _maxLineWidth = width;
        _contentDirty = true;

        if (_overflow == Overflow::SHRINK)
        {
            if (_originalFontSize > 0)
            {
                this->restoreFontSize();
            }
        }
    }
}

void Label::restoreFontSize()
{
    if (_currentLabelType == LabelType::TTF)
    {
        auto ttfConfig     = this->getTTFConfig();
        ttfConfig.fontSize = _originalFontSize;
        this->setTTFConfigInternal(ttfConfig);
    }
    else if (_currentLabelType == LabelType::BMFONT)
    {
        this->setBMFontSizeInternal(_originalFontSize);
    }
    else if (_currentLabelType == LabelType::STRING_TEXTURE)
    {
        this->setSystemFontSize(_originalFontSize);
    }
}

void Label::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
    if (breakWithoutSpace != _lineBreakWithoutSpaces)
    {
        _lineBreakWithoutSpaces = breakWithoutSpace;
        _contentDirty           = true;
    }
}

void Label::updateLabelLetters()
{
    if (!_letters.empty())
    {
        Rect uvRect;
        LabelLetter* letterSprite;
        int letterIndex;

        for (auto it = _letters.begin(); it != _letters.end();)
        {
            letterIndex  = it->first;
            letterSprite = (LabelLetter*)it->second;

            if (letterIndex >= _lengthOfString)
            {
                Node::removeChild(letterSprite, true);
                it = _letters.erase(it);
            }
            else
            {
                auto& letterInfo = _lettersInfo[letterIndex];
                if (letterInfo.valid)
                {
                    auto& letterDef    = _fontAtlas->_letterDefinitions[letterInfo.utf32Char];
                    uvRect.size.height = letterDef.height;
                    uvRect.size.width  = letterDef.width;
                    uvRect.origin.x    = letterDef.U;
                    uvRect.origin.y    = letterDef.V;

                    auto batchNode = _batchNodes.at(letterDef.textureID);
                    letterSprite->setTextureAtlas(batchNode->getTextureAtlas());
                    letterSprite->setTexture(_fontAtlas->getTexture(letterDef.textureID));
                    if (letterDef.width <= 0.f || letterDef.height <= 0.f)
                    {
                        letterSprite->setTextureAtlas(nullptr);
                    }
                    else
                    {
                        letterSprite->setTextureRect(uvRect, letterDef.rotated, uvRect.size);
                        letterSprite->setTextureAtlas(_batchNodes.at(letterDef.textureID)->getTextureAtlas());
                        letterSprite->setAtlasIndex(_lettersInfo[letterIndex].atlasIndex);
                    }

                    auto px = letterInfo.positionX + letterDef.width / 2 + _linesOffsetX[letterInfo.lineIndex];
                    auto py = letterInfo.positionY - letterDef.height / 2 + _letterOffsetY;
                    letterSprite->setPosition(px, py);
                }
                else
                {
                    letterSprite->setTextureAtlas(nullptr);
                }
                this->updateLetterSpriteScale(letterSprite);
                ++it;
            }
        }
    }
}

bool Label::alignText()
{
    if (_fileState)
        return alignFileText();
    if (_fontAtlas == nullptr || _utf32Text.empty())
    {
        setContentSize(Vec2::ZERO);
        return true;
    }

    bool ret = true;
    do
    {
        auto& textures = _fontAtlas->getTextures();
        auto size      = textures.size();
        if (size > static_cast<size_t>(_batchNodes.size()))
        {
            for (auto index = static_cast<unsigned int>(_batchNodes.size()); index < size; ++index)
            {
                auto batchNode = SpriteBatchNode::createWithTexture(textures.at(index));
                if (batchNode)
                {
                    _isOpacityModifyRGB = batchNode->getTexture()->hasPremultipliedAlpha();
                    _blendFunc          = batchNode->getBlendFunc();
                    batchNode->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                    batchNode->setPosition(Vec2::ZERO);
                    _batchNodes.pushBack(batchNode);
                }
            }
        }
        if (_batchNodes.empty())
        {
            return true;
        }
        // optimize for one-texture-only scenario
        // if multiple textures, then we should count how many chars
        // are per texture
        if (_batchNodes.size() == 1)
            _batchNodes.at(0)->reserveCapacity(_utf32Text.size());

        _reusedLetter->setBatchNode(_batchNodes.at(0));

        _lengthOfString    = 0;
        _textDesiredHeight = 0.f;
        _linesWidth.clear();
        if (_maxLineWidth > 0.f && !_lineBreakWithoutSpaces)
        {
            multilineTextWrapByWord();
        }
        else
        {
            multilineTextWrapByChar();
        }
        computeAlignmentOffset();

        if (_overflow == Overflow::SHRINK)
        {
            float fontSize = this->getRenderingFontSize();

            if (fontSize > 0 && isVerticalClamp())
            {
                this->shrinkLabelToContentSize(CC_CALLBACK_0(Label::isVerticalClamp, this));
            }
        }

        if (!updateQuads())
        {
            ret = false;
            if (_overflow == Overflow::SHRINK)
            {
                this->shrinkLabelToContentSize(CC_CALLBACK_0(Label::isHorizontalClamp, this));
            }
            break;
        }

        updateLabelLetters();

        updateColor();
    } while (0);

    return ret;
}

bool Label::computeHorizontalKernings(const std::u32string& stringToRender)
{
    if (_horizontalKernings)
    {
        delete[] _horizontalKernings;
        _horizontalKernings = nullptr;
    }

    int letterCount     = 0;
    _horizontalKernings = _fontAtlas->getFont()->getHorizontalKerningForTextUTF32(stringToRender, letterCount);

    if (!_horizontalKernings)
        return false;
    else
        return true;
}

bool Label::isHorizontalClamped(float letterPositionX, int lineIndex)
{
    auto wordWidth       = this->_linesWidth[lineIndex];
    bool letterOverClamp = (letterPositionX > _contentSize.width || letterPositionX < 0);
    if (!_enableWrap)
    {
        return letterOverClamp;
    }
    else
    {
        return (wordWidth > this->_contentSize.width && letterOverClamp);
    }
}

bool Label::updateQuads()
{
    bool ret = true;
    for (auto&& batchNode : _batchNodes)
    {
        batchNode->getTextureAtlas()->removeAllQuads();
    }

    for (int ctr = 0; ctr < _lengthOfString; ++ctr)
    {
        if (_lettersInfo[ctr].valid)
        {
            auto& letterDef = _fontAtlas->_letterDefinitions[_lettersInfo[ctr].utf32Char];

            _reusedRect.size.height = letterDef.height;
            _reusedRect.size.width  = letterDef.width;
            _reusedRect.origin.x    = letterDef.U;
            _reusedRect.origin.y    = letterDef.V;

            auto py = _lettersInfo[ctr].positionY + _letterOffsetY;
            if (_labelHeight > 0.f)
            {
                if (py > _tailoredTopY)
                {
                    auto clipTop = py - _tailoredTopY;
                    _reusedRect.origin.y += clipTop;
                    _reusedRect.size.height -= clipTop;
                    py -= clipTop;
                }
                if (py - letterDef.height * _bmfontScale < _tailoredBottomY)
                {
                    _reusedRect.size.height = (py < _tailoredBottomY) ? 0.f : (py - _tailoredBottomY);
                }
            }

            auto lineIndex = _lettersInfo[ctr].lineIndex;
            auto px = _lettersInfo[ctr].positionX + letterDef.width / 2 * _bmfontScale + _linesOffsetX[lineIndex];

            if (_labelWidth > 0.f)
            {
                if (this->isHorizontalClamped(px, lineIndex))
                {
                    if (_overflow == Overflow::CLAMP)
                    {
                        _reusedRect.size.width = 0;
                    }
                    else if (_overflow == Overflow::SHRINK)
                    {
                        if (_contentSize.width > letterDef.width)
                        {
                            ret = false;
                            break;
                        }
                        else
                        {
                            _reusedRect.size.width = 0;
                        }
                    }
                }
            }

            if (_reusedRect.size.height > 0.f && _reusedRect.size.width > 0.f)
            {
                _reusedLetter->setTextureRect(_reusedRect, letterDef.rotated, _reusedRect.size);
                float letterPositionX = _lettersInfo[ctr].positionX + _linesOffsetX[_lettersInfo[ctr].lineIndex];
                _reusedLetter->setPosition(letterPositionX, py);
                auto index = static_cast<int>(_batchNodes.at(letterDef.textureID)->getTextureAtlas()->getTotalQuads());
                _lettersInfo[ctr].atlasIndex = index;

                this->updateLetterSpriteScale(_reusedLetter);

                _batchNodes.at(letterDef.textureID)->insertQuadFromSprite(_reusedLetter, index);
            }
        }
    }

    return ret;
}

void Label::setBMFontSizeInternal(float fontSize)
{
    if (_currentLabelType == LabelType::BMFONT && _fontAtlas)
    {
        const auto font = static_cast<const FontFNT*>(_fontAtlas->getFont());
        if (std::abs(fontSize) < FLT_EPSILON && font)
            _bmFontSize = font->getOriginalFontSize() / CC_CONTENT_SCALE_FACTOR();
        else if (fontSize > 0)
            _bmFontSize = fontSize;
        _contentDirty = true;
    }
}

void Label::scaleFontSize(float fontSize)
{
    bool shouldUpdateContent = true;
    if (_currentLabelType == LabelType::TTF)
    {
        auto ttfConfig     = this->getTTFConfig();
        ttfConfig.fontSize = fontSize;
        this->setTTFConfigInternal(ttfConfig);
    }
    else if (_currentLabelType == LabelType::BMFONT)
    {
        if (std::abs(fontSize) < FLT_EPSILON)
        {
            fontSize            = 0.1f;
            shouldUpdateContent = false;
        }
        this->setBMFontSizeInternal(fontSize);
    }
    else if (_currentLabelType == LabelType::STRING_TEXTURE)
    {
        this->setSystemFontSize(fontSize);
    }

    if (shouldUpdateContent)
    {
        this->updateContent();
    }
}

void Label::enableGlow(const Color4B& glowColor)
{
    if (_currentLabelType == LabelType::TTF)
    {
        _currLabelEffect = LabelEffect::GLOW;
        _effectColorF.r  = glowColor.r / 255.0f;
        _effectColorF.g  = glowColor.g / 255.0f;
        _effectColorF.b  = glowColor.b / 255.0f;
        _effectColorF.a  = glowColor.a / 255.0f;
        updateShaderProgram();
    }
}

void Label::enableOutline(const Color4B& outlineColor, int outlineSize /* = -1 */)
{
    CCASSERT(_currentLabelType == LabelType::STRING_TEXTURE || _currentLabelType == LabelType::TTF,
             "Only supported system font and TTF!");

    if (_currentLabelType == LabelType::TTF)
    {
        if (_rasterMode == FontRasterMode::Bitmap) return;
        const int width = outlineSize > 0 ? outlineSize : _fontConfig.outlineSize;
        if (width <= 0) return;
        _fontConfig.outlineSize = width;
        _outlineSize = static_cast<float>(width);
        _effectColorF = Color4F(outlineColor);
        _currLabelEffect = LabelEffect::OUTLINE;
        return;
    }
    if (outlineSize > 0 || _currLabelEffect == LabelEffect::OUTLINE)
    {
        if (_effectColorF != outlineColor || _outlineSize != outlineSize)
        {
            _effectColorF.r  = outlineColor.r / 255.f;
            _effectColorF.g  = outlineColor.g / 255.f;
            _effectColorF.b  = outlineColor.b / 255.f;
            _effectColorF.a  = outlineColor.a / 255.f;
            _currLabelEffect = LabelEffect::OUTLINE;
            _contentDirty    = true;
        }
        _outlineSize = outlineSize;
    }
}

void Label::enableShadow(const Color4B& shadowColor /* = Color4B::BLACK */,
                         const Vec2& offset /* = Vec2(2 ,-2)*/,
                         int /* blurRadius = 0 */)
{
    _shadowEnabled = true;
    _shadowDirty   = true;

    _shadowOffset.width  = offset.width;
    _shadowOffset.height = offset.height;
    // TODO: support blur for shadow

    _shadowColor3B.r = shadowColor.r;
    _shadowColor3B.g = shadowColor.g;
    _shadowColor3B.b = shadowColor.b;
    _shadowOpacity   = shadowColor.a;

    if (!_systemFontDirty && !_contentDirty && _textSprite)
    {
        auto fontDef = _getFontDefinition();
        if (_shadowNode)
        {
            if (shadowColor != _shadowColor4F)
            {
                _shadowNode.reset();
                _shadowNode = nullptr;
                createShadowSpriteForSystemFont(fontDef);
            }
            else
            {
                _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);
            }
        }
        else
        {
            createShadowSpriteForSystemFont(fontDef);
        }
    }

    _shadowColor4F.r = shadowColor.r / 255.0f;
    _shadowColor4F.g = shadowColor.g / 255.0f;
    _shadowColor4F.b = shadowColor.b / 255.0f;
    _shadowColor4F.a = shadowColor.a / 255.0f;

    if (_currentLabelType == LabelType::BMFONT || _currentLabelType == LabelType::CHARMAP)
    {
        updateShaderProgram();
    }
}

void Label::enableItalics()
{
    setRotationSkewX(12);
}

void Label::enableBold()
{
    if (!_boldEnabled)
    {
        // bold is implemented with outline
        enableShadow(Color4B::WHITE, Vec2(0.9f, 0), 0);
        // add one to kerning
        setAdditionalKerning(_additionalKerning + 1);
        _boldEnabled = true;
    }
}

void Label::enableUnderline()
{
    // remove it, just in case to prevent adding two or more
    if (!_underlineNode)
    {
        auto underlineNodeOwner = DrawNode::create();
        _underlineNode = underlineNodeOwner.get();
        _underlineNode->setGlobalZOrder(getGlobalZOrder());
        addChild(_underlineNode, 100000);
        _contentDirty = true;
    }
}

void Label::enableStrikethrough()
{
    if (!_strikethroughEnabled)
    {
        enableUnderline();
        _strikethroughEnabled = true;
    }
}

void Label::disableEffect()
{
    disableEffect(LabelEffect::ALL);
}

void Label::disableEffect(LabelEffect effect)
{
    switch (effect)
    {
    case cc::LabelEffect::NORMAL:
        break;
    case cc::LabelEffect::OUTLINE:
        if (_currLabelEffect == LabelEffect::OUTLINE)
        {
            if (_currentLabelType == LabelType::TTF)
            {
                _fontConfig.outlineSize = 0;
                _outlineSize=0;
            }
            _currLabelEffect = LabelEffect::NORMAL;
            _contentDirty    = true;
        }
        break;
    case cc::LabelEffect::SHADOW:
        if (_shadowEnabled)
        {
            _shadowEnabled = false;
            _shadowNode.reset();
            updateShaderProgram();
        }
        break;
    case cc::LabelEffect::GLOW:
        if (_currLabelEffect == LabelEffect::GLOW)
        {
            _currLabelEffect = LabelEffect::NORMAL;
            updateShaderProgram();
        }
        break;
    case cc::LabelEffect::ITALICS:
        setRotationSkewX(0);
        break;
    case cc::LabelEffect::BOLD:
        if (_boldEnabled)
        {
            _boldEnabled = false;
            _additionalKerning -= 1;
            disableEffect(LabelEffect::SHADOW);
        }
        break;
    case cc::LabelEffect::UNDERLINE:
        if (_underlineNode)
        {
            removeChild(_underlineNode);
            _underlineNode = nullptr;
        }
        break;
    case cc::LabelEffect::STRIKETHROUGH:
        _strikethroughEnabled = false;
        // since it is based on underline, disable it as well
        disableEffect(LabelEffect::UNDERLINE);
        break;
    case LabelEffect::ALL:
    {
        disableEffect(LabelEffect::SHADOW);
        disableEffect(LabelEffect::GLOW);
        disableEffect(LabelEffect::OUTLINE);
        disableEffect(LabelEffect::ITALICS);
        disableEffect(LabelEffect::BOLD);
        disableEffect(LabelEffect::UNDERLINE);
        disableEffect(LabelEffect::STRIKETHROUGH);
    }
    break;
    default:
        break;
    }
}

void Label::createSpriteForSystemFont(const FontDefinition& fontDef)
{
    _currentLabelType = LabelType::STRING_TEXTURE;

    cc::IntrusivePtr texture{new Texture2D};
    texture->initWithString(_utf8Text.c_str(), fontDef);

    _textSprite = Sprite::createWithTexture(texture.get());
    // set camera mask using label's camera mask, because _textSprite may be null when setting camera mask to label
    _textSprite->setCameraMask(getCameraMask());
    _textSprite->setGlobalZOrder(getGlobalZOrder());
    _textSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->setContentSize(_textSprite->getContentSize());
    if (_blendFuncDirty)
    {
        _textSprite->setBlendFunc(_blendFunc);
    }

    _textSprite->updateDisplayedColor(_displayedColor);
    _textSprite->updateDisplayedOpacity(_displayedOpacity);
}

void Label::createShadowSpriteForSystemFont(const FontDefinition& fontDef)
{
    if (!fontDef._stroke._strokeEnabled && fontDef._fontFillColor == _shadowColor3B &&
        (fontDef._fontAlpha == _shadowOpacity))
    {
        _shadowNode = Sprite::createWithTexture(_textSprite->getTexture());
    }
    else
    {
        FontDefinition shadowFontDefinition   = fontDef;
        shadowFontDefinition._fontFillColor.r = _shadowColor3B.r;
        shadowFontDefinition._fontFillColor.g = _shadowColor3B.g;
        shadowFontDefinition._fontFillColor.b = _shadowColor3B.b;
        shadowFontDefinition._fontAlpha       = _shadowOpacity;

        shadowFontDefinition._stroke._strokeColor = shadowFontDefinition._fontFillColor;
        shadowFontDefinition._stroke._strokeAlpha = shadowFontDefinition._fontAlpha;

        cc::IntrusivePtr texture{new Texture2D};
        texture->initWithString(_utf8Text.c_str(), shadowFontDefinition);
        _shadowNode = Sprite::createWithTexture(texture.get());
    }

    if (_shadowNode)
    {
        if (_blendFuncDirty)
        {
            _shadowNode->setBlendFunc(_blendFunc);
        }
        _shadowNode->setCameraMask(getCameraMask());
        _shadowNode->setGlobalZOrder(getGlobalZOrder());
        _shadowNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        _shadowNode->setPosition(_shadowOffset.width, _shadowOffset.height);

        _shadowNode->updateDisplayedColor(_displayedColor);
        _shadowNode->updateDisplayedOpacity(_displayedOpacity);
    }
}

void Label::setCameraMask(unsigned short mask, bool applyChildren)
{
    Node::setCameraMask(mask, applyChildren);

    if (_textSprite)
    {
        _textSprite->setCameraMask(mask, applyChildren);
    }
    if (_shadowNode)
    {
        _shadowNode->setCameraMask(mask, applyChildren);
    }
}

void Label::updateContent()
{
    if (_systemFontDirty)
    {
        if (_fontAtlas)
        {
            _batchNodes.clear();
            _batchCommands.clear();
            _reusedLetter.reset();
            FontAtlasCache::releaseFontAtlas(_fontAtlas);
            _fontAtlas = nullptr;
            _fileState.reset();
        }

        _systemFontDirty = false;
    }

    _textSprite.reset();
    _shadowNode.reset();
    bool updateFinished = true;

    if (_fontAtlas)
    {
        std::u32string utf32String;
        if (StringUtils::UTF8ToUTF32(_utf8Text, utf32String))
        {
            _utf32Text = utf32String;
        }

        if (!_fileState) computeHorizontalKernings(_utf32Text);
        updateFinished = alignText();
    }
    else
    {
        auto fontDef = _getFontDefinition();
        createSpriteForSystemFont(fontDef);
        if (_shadowEnabled)
        {
            createShadowSpriteForSystemFont(fontDef);
        }
    }

    if (_underlineNode)
    {
        _underlineNode->clear();

        if (_numberOfLines)
        {
            // This is the logic for TTF fonts
            const float charheight = (_textDesiredHeight / _numberOfLines);
            _underlineNode->setLineWidth(charheight / 6);

            // atlas font
            for (int i = 0; i < _numberOfLines; ++i)
            {
                float offsety = 0;
                if (_strikethroughEnabled)
                    offsety += charheight / 2;
                // FIXME: Might not work with different vertical alignments
                float y = (_numberOfLines - i - 1) * charheight + offsety;

                // Github issue #15214. Uses _displayedColor instead of _textColor for the underline.
                // This is to have the same behavior of SystemFonts.
                _underlineNode->drawLine(Vec2(_linesOffsetX[i], y), Vec2(_linesWidth[i] + _linesOffsetX[i], y),
                                         Color4F(_displayedColor));
            }
        }
        else if (_textSprite)
        {
            // ...and is the logic for System fonts
            float y               = 0;
            const auto spriteSize = _textSprite->getContentSize();
            _underlineNode->setLineWidth(spriteSize.height / 6);

            if (_strikethroughEnabled)
                // FIXME: system fonts don't report the height of the font correctly. only the size of the texture,
                // which is POT
                y += spriteSize.height / 2;
            // FIXME: Might not work with different vertical alignments
            _underlineNode->drawLine(Vec2(0.0f, y), Vec2(spriteSize.width, y),
                                     Color4F(_textSprite->getDisplayedColor()));
        }
    }

    if (updateFinished)
    {
        _contentDirty = false;
    }

#if CC_LABEL_DEBUG_DRAW
    _debugDrawNode->clear();
    Vec2 vertices[4] = {Vec2::ZERO, Vec2(_contentSize.width, 0.0f), Vec2(_contentSize.width, _contentSize.height),
                        Vec2(0.0f, _contentSize.height)};
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F::WHITE);
#endif
}

void Label::setBMFontSize(float fontSize)
{
    this->setBMFontSizeInternal(fontSize);
    _originalFontSize = fontSize;
}

float Label::getBMFontSize() const
{
    return _bmFontSize;
}

void Label::updateBuffer(TextureAtlas* textureAtlas, CustomCommand& customCommand)
{
    const auto totalQuads = textureAtlas->getTotalQuads();
    const auto totalVertex = totalQuads * 4;
    const auto totalIndex = totalQuads * 6;
    if (totalVertex > customCommand.getVertexCapacity())
    {
        customCommand.createVertexBuffer(sizeof(V3F_C4B_T2F), totalVertex, CustomCommand::BufferUsage::DYNAMIC);
        customCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, totalIndex, CustomCommand::BufferUsage::DYNAMIC);
    }
    customCommand.updateVertexBuffer(textureAtlas->getQuads(), totalVertex * sizeof(V3F_C4B_T2F));
    customCommand.updateIndexBuffer(textureAtlas->getIndices(), totalIndex * sizeof(unsigned short));
    customCommand.setIndexDrawInfo(0, totalIndex);
}

void Label::updateEffectUniforms(BatchCommand& batch,
                                 TextureAtlas* textureAtlas,
                                 Renderer* renderer,
                                 const Mat4& transform)
{
    updateBuffer(textureAtlas, batch.textCommand);

    auto& matrixProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    if (_shadowEnabled)
    {
        updateBuffer(textureAtlas, batch.shadowCommand);
        auto shadowMatrix = matrixProjection * _shadowTransform;
        batch.shadowCommand.getPipelineDescriptor().programState->setUniform(_mvpMatrixLocation, shadowMatrix.m,
                                                                             sizeof(shadowMatrix.m));

        Color3B oldColor   = _realColor;
        uint8_t oldOPacity = _displayedOpacity;
        _displayedOpacity  = _shadowColor4F.a * (oldOPacity / 255.0f) * 255;
        setColor(Color3B(_shadowColor4F));
        batch.shadowCommand.updateVertexBuffer(
            textureAtlas->getQuads(), (unsigned int)(textureAtlas->getTotalQuads() * sizeof(V3F_C4B_T2F_Quad)));
        batch.shadowCommand.init(_globalZOrder);
        renderer->addCommand(&batch.shadowCommand);

        _displayedOpacity = oldOPacity;
        setColor(oldColor);
    }

    batch.textCommand.init(_globalZOrder);
    renderer->addCommand(&batch.textCommand);
}

void Label::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    if (_fileState && _currentLabelType == LabelType::TTF)
    {
        drawFileText(renderer, transform, flags);
        return;
    }
    if (!_programState || _batchNodes.empty() || _lengthOfString <= 0)
    {
        return;
    }
    // Don't do calculate the culling if the transform was not updated
    bool transformUpdated = flags & FLAGS_TRANSFORM_DIRTY;
#if CC_USE_CULLING
    auto visitingCamera = Camera::getVisitingCamera();
    auto defaultCamera  = Camera::getDefaultCamera();
    if (visitingCamera == defaultCamera)
    {
        _insideBounds = (transformUpdated || visitingCamera->isViewProjectionUpdated())
                            ? renderer->checkVisibility(transform, _contentSize)
                            : _insideBounds;
    }
    else
    {
        _insideBounds = renderer->checkVisibility(transform, _contentSize);
    }

    if (_insideBounds)
#endif
    {
        cc::Mat4 matrixProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
        if (!_shadowEnabled && (_currentLabelType == LabelType::BMFONT || _currentLabelType == LabelType::CHARMAP))
        {
            updateBlendState();
            for (auto&& it : _letters)
            {
                it.second->updateTransform();
            }
            // ETC1 ALPHA supports for BMFONT & CHARMAP
            auto textureAtlas = _batchNodes.at(0)->getTextureAtlas();
            if (!textureAtlas->getTotalQuads())
                return;

            auto texture       = textureAtlas->getTexture();
            auto& pipelineQuad = _quadCommand.getPipelineDescriptor();
            pipelineQuad.programState->setUniform(_mvpMatrixLocation, matrixProjection.m, sizeof(matrixProjection.m));
            pipelineQuad.programState->setTexture(texture->getBackendTexture());
            _quadCommand.init(_globalZOrder, texture, _blendFunc, textureAtlas->getQuads(),
                              textureAtlas->getTotalQuads(), transform, flags);
            renderer->addCommand(&_quadCommand);
        }
        else
        {
            cc::Mat4 matrixMVP = matrixProjection * transform;

            for (auto&& it : _letters)
            {
                it.second->updateTransform();
            }
            int i = 0;

            if (_batchCommands.size() != _batchNodes.size())
            {
            	// clear before resize since CCCustomCommand is not copyable
                _batchCommands.clear();
                _batchCommands.resize(_batchNodes.size());
                for (auto& batch : _batchCommands)
                    updateBatchCommand(batch);
            }

            updateBlendState();

            for (auto&& batchNode : _batchNodes)
            {
                auto textureAtlas = batchNode->getTextureAtlas();
                if (!textureAtlas->getTotalQuads())
                    continue;

                auto& batch = _batchCommands[i++];
                for (auto&& command : batch.getCommandArray())
                {
                    auto* programState = command->getPipelineDescriptor().programState;
                    Vec4 textColor(_textColorF.r, _textColorF.g, _textColorF.b, _textColorF.a);
                    programState->setUniform(_textColorLocation, &textColor, sizeof(Vec4));
                    programState->setTexture(textureAtlas->getTexture()->getBackendTexture());
                }
                batch.textCommand.getPipelineDescriptor().programState->setUniform(_mvpMatrixLocation, matrixMVP.m,
                                                                                   sizeof(matrixMVP.m));
                batch.outLineCommand.getPipelineDescriptor().programState->setUniform(_mvpMatrixLocation, matrixMVP.m,
                                                                                      sizeof(matrixMVP.m));
                updateEffectUniforms(batch, textureAtlas, renderer, transform);
            }
        }
    }
}

void Label::updateBlendState()
{
    setOpacityModifyRGB(_blendFunc != BlendFunc::ALPHA_NON_PREMULTIPLIED);
    for (auto&& batch : _batchCommands)
    {
        for (auto&& command : batch.getCommandArray())
        {
            auto& blendDescriptor = command->getPipelineDescriptor().blendDescriptor;
            updateBlend(blendDescriptor, _blendFunc);
        }
    }
    updateBlend(_quadCommand.getPipelineDescriptor().blendDescriptor, _blendFunc);
}

void Label::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    if (!_visible || (_utf8Text.empty() && _children.empty()))
    {
        return;
    }

    if (_fileState && _fileState->scale!=CC_CONTENT_SCALE_FACTOR()) _contentDirty=true;
    if (_systemFontDirty || _contentDirty)
    {
        // Label overflow shrink fix #566
        if (!_fileState && _overflow == Overflow::SHRINK && this->getRenderingFontSize() < _originalFontSize)
            rescaleWithOriginalFontSize();
     
        updateContent();
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    if (!_utf8Text.empty() && _shadowEnabled && (_shadowDirty || (flags & FLAGS_DIRTY_MASK)))
    {
        _position.x += _shadowOffset.width;
        _position.y += _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowTransform = transform(parentTransform);

        _position.x -= _shadowOffset.width;
        _position.y -= _shadowOffset.height;
        _transformDirty = _inverseDirty = true;

        _shadowDirty = false;
    }

    bool visibleByCamera = isVisitableByVisitingCamera();
    if (_children.empty() && !_textSprite && !visibleByCamera)
    {
        return;
    }

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    if (!_children.empty())
    {
        sortAllChildren();

        int i = 0;
        // draw children zOrder < 0
        for (auto size = _children.size(); i < size; ++i)
        {
            auto node = _children.at(i);

            if (node && node->getLocalZOrder() < 0)
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }

        this->drawSelf(visibleByCamera, renderer, flags);

        for (auto it = _children.cbegin() + i, itCend = _children.cend(); it != itCend; ++it)
        {
            (*it)->visit(renderer, _modelViewTransform, flags);
        }
    }
    else
    {
        this->drawSelf(visibleByCamera, renderer, flags);
    }

    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Label::drawSelf(bool visibleByCamera, Renderer* renderer, uint32_t flags)
{
    if (_textSprite)
    {
        if (_shadowNode)
        {
            _shadowNode->visit(renderer, _modelViewTransform, flags);
        }
        _textSprite->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera && !_utf8Text.empty())
    {
        draw(renderer, _modelViewTransform, flags);
    }
}

void Label::setSystemFontName(std::string_view systemFont)
{
    if (systemFont != _systemFont)
    {
        _systemFont       = systemFont;
        _currentLabelType = LabelType::STRING_TEXTURE;
        _systemFontDirty  = true;
    }
}

void Label::setSystemFontSize(float fontSize)
{
    if (_systemFontSize != fontSize)
    {
        _systemFontSize   = fontSize;
        _originalFontSize = fontSize;
        _currentLabelType = LabelType::STRING_TEXTURE;
        _systemFontDirty  = true;
    }
}

///// PROTOCOL STUFF
Sprite* Label::getLetter(int letterIndex)
{
    cc::IntrusivePtr<Sprite> letter;
    do
    {
        if (_systemFontDirty || _currentLabelType == LabelType::STRING_TEXTURE)
        {
            break;
        }

        auto contentDirty = _contentDirty;
        if (contentDirty)
        {
            updateContent();
        }

        if (_fileState) return fileLetter(letterIndex);
        if (_textSprite == nullptr && letterIndex >= 0 && letterIndex < _lengthOfString)
        {
            const auto& letterInfo = _lettersInfo[letterIndex];
            if (!letterInfo.valid || letterInfo.atlasIndex < 0)
            {
                break;
            }

            if (_letters.find(letterIndex) != _letters.end())
            {
                letter = _letters[letterIndex];
            }

            if (letter == nullptr)
            {
                auto& letterDef = _fontAtlas->_letterDefinitions[letterInfo.utf32Char];
                auto textureID  = letterDef.textureID;
                Rect uvRect;
                uvRect.size.height = letterDef.height;
                uvRect.size.width  = letterDef.width;
                uvRect.origin.x    = letterDef.U;
                uvRect.origin.y    = letterDef.V;

                if (letterDef.width <= 0.f || letterDef.height <= 0.f)
                {
                    letter = LabelLetter::create();
                }
                else
                {
                    this->updateBMFontScale();
                    letter =
                        LabelLetter::createWithTexture(_fontAtlas->getTexture(textureID), uvRect, letterDef.rotated);
                    letter->setTextureAtlas(_batchNodes.at(textureID)->getTextureAtlas());
                    letter->setAtlasIndex(letterInfo.atlasIndex);
                    auto px = letterInfo.positionX + _bmfontScale * uvRect.size.width / 2 +
                              _linesOffsetX[letterInfo.lineIndex];
                    auto py = letterInfo.positionY - _bmfontScale * uvRect.size.height / 2 + _letterOffsetY;
                    letter->setPosition(px, py);
                    letter->setOpacity(_realOpacity);
                    this->updateLetterSpriteScale(letter);
                }

                addChild(letter);
                _letters[letterIndex] = letter;
            }
        }
    } while (false);

    return letter.get();
}

void Label::setLineHeight(float height)
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");

    if (_lineHeight != height)
    {
        _lineHeight   = height;
        _contentDirty = true;
    }
}

float Label::getLineHeight() const
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");
    return _textSprite ? 0.0f : _lineHeight * _bmfontScale;
}

void Label::setLineSpacing(float height)
{
    if (_lineSpacing != height)
    {
        _lineSpacing  = height;
        _contentDirty = true;
    }
}

float Label::getLineSpacing() const
{
    return _lineSpacing;
}

void Label::setAdditionalKerning(float space)
{

    if (_currentLabelType != LabelType::STRING_TEXTURE)
    {
        if (_additionalKerning != space)
        {
            _additionalKerning = space;
            _contentDirty      = true;
        }
    }
    else
        CCLOG("Label::setAdditionalKerning not supported on LabelType::STRING_TEXTURE");
}

float Label::getAdditionalKerning() const
{
    CCASSERT(_currentLabelType != LabelType::STRING_TEXTURE, "Not supported system font!");

    return _additionalKerning;
}

void Label::computeStringNumLines()
{
    int quantityOfLines = 1;

    if (_utf32Text.empty())
    {
        _numberOfLines = 0;
        return;
    }

    // count number of lines
    size_t stringLen = _utf32Text.length();
    for (size_t i = 0; i < stringLen - 1; ++i)
    {
        if (_utf32Text[i] == StringUtils::UnicodeCharacters::NewLine)
        {
            quantityOfLines++;
        }
    }

    _numberOfLines = quantityOfLines;
}

int Label::getStringNumLines()
{
    if (_contentDirty)
    {
        updateContent();
    }

    if (_currentLabelType == LabelType::STRING_TEXTURE)
    {
        computeStringNumLines();
    }

    return _numberOfLines;
}

int Label::getStringLength()
{
    _lengthOfString = static_cast<int>(_utf32Text.length());
    return _lengthOfString;
}

// RGBA protocol
void Label::setOpacityModifyRGB(bool isOpacityModifyRGB)
{
    if (isOpacityModifyRGB != _isOpacityModifyRGB)
    {
        _isOpacityModifyRGB = isOpacityModifyRGB;
        updateColor();
    }
}

void Label::updateDisplayedColor(const Color3B& parentColor)
{
    Node::updateDisplayedColor(parentColor);

    if (_textSprite)
    {
        _textSprite->updateDisplayedColor(_displayedColor);
    }

    if (_shadowNode)
    {
        _shadowNode->updateDisplayedColor(_displayedColor);
    }

    if (_underlineNode)
    {
        // FIXME: _underlineNode is not a sprite/label. It is a DrawNode
        // and updating its color doesn't work. it must be re-drawn,
        // which makes it super expensive to change update it frequently
        // Correct solution is to update the DrawNode directly since we know it is
        // a line. Returning a pointer to the line is an option
        _contentDirty = true;
    }

    for (auto&& it : _letters)
    {
        it.second->updateDisplayedColor(_displayedColor);
    }
}

void Label::updateDisplayedOpacity(uint8_t parentOpacity)
{
    Node::updateDisplayedOpacity(parentOpacity);

    if (_textSprite)
    {
        _textSprite->updateDisplayedOpacity(_displayedOpacity);
        if (_shadowNode)
        {
            _shadowNode->updateDisplayedOpacity(_displayedOpacity);
        }
    }

    for (auto&& it : _letters)
    {
        it.second->updateDisplayedOpacity(_displayedOpacity);
    }
}

// FIXME: it is not clear what is the difference between setTextColor() and setColor()
// if setTextColor() only changes the text and nothing but the text (no glow, no outline, not underline)
// that's fine but it should be documented
void Label::setTextColor(const Color4B& color)
{
    CCASSERT(_currentLabelType == LabelType::TTF || _currentLabelType == LabelType::STRING_TEXTURE,
             "Only supported system font and ttf!");

    if (_currentLabelType == LabelType::STRING_TEXTURE && _textColor != color)
    {
        _contentDirty = true;
    }

    _textColor    = color;
    _textColorF.r = _textColor.r / 255.0f;
    _textColorF.g = _textColor.g / 255.0f;
    _textColorF.b = _textColor.b / 255.0f;
    _textColorF.a = _textColor.a / 255.0f;
}

void Label::updateColor()
{
    if (_batchNodes.empty())
    {
        return;
    }

    Color4B color4(_displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity);

    // special opacity for premultiplied textures
    if (_isOpacityModifyRGB)
    {
        color4.r *= _displayedOpacity / 255.0f;
        color4.g *= _displayedOpacity / 255.0f;
        color4.b *= _displayedOpacity / 255.0f;
    }

    cc::TextureAtlas* textureAtlas;
    V3F_C4B_T2F_Quad* quads;
    for (auto&& batchNode : _batchNodes)
    {
        textureAtlas = batchNode->getTextureAtlas();
        quads        = textureAtlas->getQuads();
        auto count   = textureAtlas->getTotalQuads();

        for (int index = 0; index < count; ++index)
        {
            quads[index].bl.colors = color4;
            quads[index].br.colors = color4;
            quads[index].tl.colors = color4;
            quads[index].tr.colors = color4;
            textureAtlas->updateQuad(&quads[index], index);
        }
    }
}

std::string Label::getDescription() const
{
    char tmp[50];
    snprintf(tmp, sizeof(tmp), "<Label | Tag = %d, Label = >", _tag);
    std::string ret = tmp;
    ret += _utf8Text;

    return ret;
}

const Vec2& Label::getContentSize() const
{
    if (_systemFontDirty || _contentDirty)
    {
        if (_fileState) _fileState->layoutOnly=true;
        const_cast<Label*>(this)->updateContent();
        if (_fileState) _fileState->layoutOnly=false;
    }
    return _contentSize;
}

Rect Label::getBoundingBox() const
{
    const_cast<Label*>(this)->getContentSize();

    return Node::getBoundingBox();
}

void Label::setBlendFunc(const BlendFunc& blendFunc)
{
    _blendFunc      = blendFunc;
    _blendFuncDirty = true;
    if (_textSprite)
    {
        _textSprite->setBlendFunc(blendFunc);
        if (_shadowNode)
        {
            _shadowNode->setBlendFunc(blendFunc);
        }
    }
}

void Label::removeAllChildrenWithCleanup(bool cleanup)
{
    Node::removeAllChildrenWithCleanup(cleanup);
    _letters.clear();
}

void Label::removeChild(Node* child, bool cleanup /* = true */)
{
    Node::removeChild(child, cleanup);
    for (auto&& it : _letters)
    {
        if (it.second == child)
        {
            _letters.erase(it.first);
            break;
        }
    }
}

FontDefinition Label::_getFontDefinition() const
{
    FontDefinition systemFontDef;

    std::string fontName = _systemFont;
    if (_fontAtlas && !_fontAtlas->getFontName().empty())
        fontName = _fontAtlas->getFontName();

    systemFontDef._fontName              = fontName;
    systemFontDef._fontSize              = _systemFontSize;
    systemFontDef._alignment             = _hAlignment;
    systemFontDef._vertAlignment         = _vAlignment;
    systemFontDef._dimensions.width      = _labelWidth == 0.f ? _maxLineWidth : _labelWidth;
    systemFontDef._dimensions.height     = _labelHeight;
    systemFontDef._fontFillColor.r       = _textColor.r;
    systemFontDef._fontFillColor.g       = _textColor.g;
    systemFontDef._fontFillColor.b       = _textColor.b;
    systemFontDef._fontAlpha             = _textColor.a;
    systemFontDef._shadow._shadowEnabled = false;
    systemFontDef._enableWrap            = _enableWrap;
    systemFontDef._overflow              = (int)_overflow;

    if (_currLabelEffect == LabelEffect::OUTLINE && _outlineSize > 0.f)
    {
        systemFontDef._stroke._strokeEnabled = true;
        systemFontDef._stroke._strokeSize    = _outlineSize;
        systemFontDef._stroke._strokeColor.r = _effectColorF.r * 255;
        systemFontDef._stroke._strokeColor.g = _effectColorF.g * 255;
        systemFontDef._stroke._strokeColor.b = _effectColorF.b * 255;
        systemFontDef._stroke._strokeAlpha   = _effectColorF.a * 255;
    }
    else
    {
        systemFontDef._stroke._strokeEnabled = false;
    }

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID) && (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    if (systemFontDef._stroke._strokeEnabled)
    {
        CCLOGERROR("Stroke Currently only supported on iOS and Android!");
    }
    systemFontDef._stroke._strokeEnabled = false;
#endif

    return systemFontDef;
}

void Label::setGlobalZOrder(float globalZOrder)
{
    Node::setGlobalZOrder(globalZOrder);
    if (_textSprite)
    {
        _textSprite->setGlobalZOrder(globalZOrder);
        if (_shadowNode)
        {
            _shadowNode->setGlobalZOrder(globalZOrder);
        }
    }

    if (_underlineNode)
    {
        _underlineNode->setGlobalZOrder(globalZOrder);
    }

#if CC_LABEL_DEBUG_DRAW
    _debugDrawNode->setGlobalZOrder(globalZOrder);
#endif
}

float Label::getRenderingFontSize() const
{
    float fontSize;
    if (_currentLabelType == LabelType::BMFONT)
    {
        fontSize = _bmFontSize;
    }
    else if (_currentLabelType == LabelType::TTF)
    {
        fontSize = _fileState ? _fileState->layoutSize : this->getTTFConfig().fontSize;
    }
    else if (_currentLabelType == LabelType::STRING_TEXTURE)
    {
        fontSize = _systemFontSize;
    }
    else
    {  // FIXME: find a way to calculate char map font size
        fontSize = this->getLineHeight();
    }
    return fontSize;
}

void Label::enableWrap(bool enable)
{
    if (enable == _enableWrap || _overflow == Overflow::RESIZE_HEIGHT)
    {
        return;
    }

    this->_enableWrap = enable;

    this->rescaleWithOriginalFontSize();

    _contentDirty = true;
}

bool Label::isWrapEnabled() const
{
    return this->_enableWrap;
}

void Label::setOverflow(Overflow overflow)
{
    if (_overflow == overflow)
    {
        return;
    }

    if (_currentLabelType == LabelType::CHARMAP)
    {
        if (overflow == Overflow::SHRINK)
        {
            return;
        }
    }

    if (overflow == Overflow::RESIZE_HEIGHT)
    {
        this->setDimensions(_labelDimensions.width, 0);
        this->enableWrap(true);
    }
    _overflow = overflow;

    this->rescaleWithOriginalFontSize();

    _contentDirty = true;
}

void Label::rescaleWithOriginalFontSize()
{
    auto renderingFontSize = this->getRenderingFontSize();
    if (_originalFontSize - renderingFontSize >= 1)
    {
        this->scaleFontSize(_originalFontSize);
    }
}

Label::Overflow Label::getOverflow() const
{
    return _overflow;
}

void Label::updateLetterSpriteScale(Sprite* sprite)
{
    if (_currentLabelType == LabelType::BMFONT && _bmFontSize > 0)
    {
        sprite->setScale(_bmfontScale);
    }
    else
    {
        if (std::abs(_bmFontSize) < FLT_EPSILON)
        {
            sprite->setScale(0);
        }
        else
        {
            sprite->setScale(1.0);
        }
    }
}

NS_CC_END
