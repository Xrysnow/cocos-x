#include "2d/Label.h"
#include "FontLabelState.h"
#include "LabelLetter.h"
#include "base/Director.h"
#include "base/ccUTF8.h"
#include "renderer/Renderer.h"

namespace cc
{
namespace
{
bool control(char32_t cp)
{
    return cp == U'\n' || cp == U'\r' || cp == U'\b';
}
std::vector<font::GlyphKey> keysFor(const FontLabelState& state, FontRasterMode mode, std::u32string_view text)
{
    std::vector<font::GlyphKey> out;
    out.reserve(text.size());
    for (char32_t cp : text)
        if (!control(cp))
            out.push_back(state.face->key(cp, mode, state.ppem));
    return out;
}
}  // namespace
cc::IntrusivePtr<Label> Label::createWithFont(const FontConfig& config, std::string_view text, FontRasterMode mode)
{
    if (mode != FontRasterMode::Bitmap && mode != FontRasterMode::Sdf && mode != FontRasterMode::Msdf)
        return {};
    cc::IntrusivePtr label{new Label(mode)};
    if (!label->setFontConfig(config))
        return {};
    label->setString(text);
    return label;
}
bool Label::setFontConfig(const FontConfig& config)
{
    auto legacy         = _fontConfig;
    legacy.fontFilePath = config.name;
    legacy.fontSize     = config.size;
    return setTTFConfig(legacy);
}
bool Label::setTTFConfigInternal(const TTFConfig& config)
{
    const float scale = CC_CONTENT_SCALE_FACTOR();
    const int ppem    = font::requestedPpem(config.fontSize, scale);
    if (!ppem || (_rasterMode == FontRasterMode::Bitmap && config.outlineSize > 0))
        return false;
    auto& service = *_director->getFontRendering()._service;
    GlyphStatus status;
    auto face = service.face(config.fontFilePath, status);
    if (!face || !face->setSize(ppem))
        return false;
    auto state        = std::make_unique<FontLabelState>();
    state->face       = std::move(face);
    state->ppem       = ppem;
    state->layoutSize = config.fontSize;
    state->scale      = scale;
    state->metrics    = state->face->metrics();
    cc::IntrusivePtr view{new FontAtlas(nullptr)};
    view->_name = config.fontFilePath;
    view->setLineHeight(state->metrics.lineHeight);
    if (_fileState)
        state->anchors = std::move(_fileState->anchors);
    _currentLabelType = LabelType::TTF;
    setFontAtlas(view.get(), _rasterMode != FontRasterMode::Bitmap, true);
    _fileState                       = std::move(state);
    _fontConfig                      = config;
    _fontConfig.distanceFieldEnabled = _rasterMode != FontRasterMode::Bitmap;
    _outlineSize                     = float(config.outlineSize);
    _currLabelEffect                 = config.outlineSize > 0 ? LabelEffect::OUTLINE : LabelEffect::NORMAL;
    updateShaderProgram();
    if (config.italics)
        enableItalics();
    if (config.bold)
        enableBold();
    if (config.underline)
        enableUnderline();
    if (config.strikethrough)
        enableStrikethrough();
    if (config.glyphs == GlyphCollection::CUSTOM)
        _fileState->warmup = prefetchGlyphs(config.customGlyphs);
    else if (config.glyphs == GlyphCollection::NEHE || config.glyphs == GlyphCollection::ASCII)
    {
        std::u32string chars;
        for (char32_t c = 32; c <= 126; ++c)
            chars.push_back(c);
        if (config.glyphs == GlyphCollection::ASCII)
            for (char32_t c = 161; c <= 254; ++c)
                chars.push_back(c);
        _fileState->warmup = service.submit(keysFor(*_fileState, _rasterMode, chars), font::Priority::Prefetch);
    }
    return true;
}
GlyphTicket Label::prefetchGlyphs(std::string_view text) const
{
    if (!_fileState || _currentLabelType != LabelType::TTF)
        return font::FontService::failure(GlyphStatus::NotFileFont);
    std::u32string utf32;
    if (!text.empty() && !StringUtils::UTF8ToUTF32(text, utf32))
        return font::FontService::failure(GlyphStatus::InvalidInput);
    return _director->getFontRendering()._service->submit(
        keysFor(*_fileState, _rasterMode, utf32), font::Priority::Prefetch);
}
bool Label::getFontMetrics(FontMetrics& out) const
{
    if (!_fileState || _currentLabelType != LabelType::TTF)
        return false;
    out             = _fileState->metrics;
    out.ascent     /= _fileState->scale;
    out.descent    /= _fileState->scale;
    out.lineHeight /= _fileState->scale;
    return true;
}
bool Label::alignFileText()
{
    auto& state   = *_fileState;
    state.visible = {};
    state.keys.clear();
    auto& face               = *state.face;
    const float oldHeight    = state.metrics.lineHeight;
    const float customHeight = _lineHeight == oldHeight ? 0.f : _lineHeight;
    state.scale              = CC_CONTENT_SCALE_FACTOR();
    float size               = _originalFontSize > 0 ? _originalFontSize : _fontConfig.fontSize;
    std::set<char32_t> unique(_utf32Text.begin(), _utf32Text.end());
    for (;;)
    {
        state.ppem = font::requestedPpem(size, state.scale);
        if (!face.setSize(state.ppem))
            return false;
        state.metrics    = face.metrics();
        state.layoutSize = size;
        _lineHeight      = customHeight > 0 ? customHeight * (size / _fontConfig.fontSize) : state.metrics.lineHeight;
        _fontAtlas->setLineHeight(_lineHeight);
        _fontAtlas->_letterDefinitions.clear();
        for (auto cp : unique)
            if (!control(cp))
                _fontAtlas->addLetterDefinition(cp, face.measure(cp, state.scale));
        delete[] _horizontalKernings;
        _horizontalKernings = nullptr;
        if (!_utf32Text.empty())
        {
            _horizontalKernings = new int[_utf32Text.size()]{};
            for (size_t i = 1; i < _utf32Text.size(); ++i)
                _horizontalKernings[i] = face.kerning(face.glyph(_utf32Text[i - 1]), face.glyph(_utf32Text[i]));
        }
        _lengthOfString    = 0;
        _textDesiredHeight = 0;
        _linesWidth.clear();
        if (_utf32Text.empty())
        {
            _numberOfLines = 0;
            setContentSize(Vec2::ZERO);
            break;
        }
        if (_maxLineWidth > 0 && !_lineBreakWithoutSpaces)
            multilineTextWrapByWord();
        else
            multilineTextWrapByChar();
        computeAlignmentOffset();
        if (_overflow != Overflow::SHRINK || size <= 1 || (!isVerticalClamp() && !isHorizontalClamp()))
            break;
        size = std::max(1.f, size - 1);
    }
    for (auto it = _letters.begin(); it != _letters.end();)
    {
        if (it->first >= _lengthOfString || !_lettersInfo[it->first].valid)
        {
            state.anchors.erase(it->first);
            Node::removeChild(it->second, true);
            it = _letters.erase(it);
        }
        else
        {
            positionFileLetter(it->first, it->second);
            ++it;
        }
    }
    state.keys = keysFor(state, _rasterMode, _utf32Text);
    if (!state.layoutOnly)
    {
        auto& service = *_director->getFontRendering()._service;
        state.visible = service.submit(state.keys, font::Priority::Visible);
        if (_glyphPolicy == GlyphRenderPolicy::Synchronous)
            service.prepare(*_director->getRenderer(), state.keys);
    }
    return true;
}
GlyphStatus Label::prepareGlyphsNow()
{
    if (!_fileState || _currentLabelType != LabelType::TTF)
        return GlyphStatus::NotFileFont;
    if (_contentDirty)
        updateContent();
    return _director->getFontRendering()._service->prepare(*_director->getRenderer(), _fileState->keys);
}
bool Label::measureText(std::string_view text, Size& out) const
{
    if (!_fileState || _currentLabelType != LabelType::TTF)
        return false;
    cc::IntrusivePtr scratch{new Label(_rasterMode, _hAlignment, _vAlignment)};
    // Each layout has its own metrics view, including during SHRINK.
    auto config   = _fontConfig;
    config.glyphs = GlyphCollection::DYNAMIC;
    if (!scratch->setTTFConfig(config))
        return false;
    scratch->_fileState->layoutOnly  = true;
    scratch->_labelWidth             = _labelWidth;
    scratch->_labelHeight            = _labelHeight;
    scratch->_maxLineWidth           = _maxLineWidth;
    scratch->_overflow               = _overflow;
    scratch->_enableWrap             = _enableWrap;
    scratch->_lineBreakWithoutSpaces = _lineBreakWithoutSpaces;
    scratch->_lineHeight             = _lineHeight;
    scratch->_lineSpacing            = _lineSpacing;
    scratch->_additionalKerning      = _additionalKerning;
    if (!text.empty() && !StringUtils::UTF8ToUTF32(text, scratch->_utf32Text))
        return false;
    if (!scratch->alignFileText())
        return false;
    out = scratch->_contentSize;
    return true;
}
void Label::positionFileLetter(int index, Sprite* sprite)
{
    const auto& info = _lettersInfo[index];
    const auto& def  = _fontAtlas->_letterDefinitions.at(info.utf32Char);
    Vec2 anchor{
        info.positionX + _linesOffsetX[info.lineIndex] + def.width / 2,
        info.positionY + _letterOffsetY - def.height / 2};
    auto [it, fresh] = _fileState->anchors.try_emplace(index, anchor);
    auto pos         = fresh ? anchor : sprite->getPosition() + anchor - it->second;
    sprite->setContentSize({def.width, def.height});
    sprite->setPosition(pos);
    it->second = anchor;
}
Sprite* Label::fileLetter(int index)
{
    if (index < 0 || index >= _lengthOfString || !_lettersInfo[index].valid)
        return nullptr;
    const auto& info = _lettersInfo[index];
    const auto& def  = _fontAtlas->_letterDefinitions.at(info.utf32Char);
    if (def.width <= 0 || def.height <= 0)
        return nullptr;
    const auto key = _fileState->face->key(info.utf32Char, _rasterMode, _fileState->ppem);
    auto slot      = _director->getFontRendering()._service->resolve(key);
    auto it        = _letters.find(index);
    if (it != _letters.end())
    {
        if (slot && slot->page)
            static_cast<LabelLetter*>(it->second)->bind(slot, {def.width, def.height});
        return it->second;
    }
    auto letter = LabelLetter::create();
    if (!letter)
        return nullptr;
    addChild(letter);
    _letters.emplace(index, letter.get());
    if (slot && slot->page)
        letter->bind(slot, {def.width, def.height});
    positionFileLetter(index, letter.get());
    return letter.get();
}
}  // namespace cc
