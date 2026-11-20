//
// Copyright (c) 2014-2022 @HALX99 - All Rights Reserved
//
#ifndef _UITEXTFIELD_CPP_H_
#define _UITEXTFIELD_CPP_H_
#include "UITextFieldEx.h"
#include "2d/TextInputGeometry.h"
#include "platform/TextInputIndex.h"
#include "platform/GLView.h"

#include "base/Director.h"

/// cocos2d singleton objects
#define CCDIRECTOR cc::Director::getInstance()
#define CCRUNONGL CCDIRECTOR->getScheduler()->performFunctionInCocosThread
#define CCEVENTMGR CCDIRECTOR->getEventDispatcher()
#define CCSCHTASKS CCDIRECTOR->getScheduler()
#define CCACTIONMGR CCDIRECTOR->getActionManager()
#define CCFILEUTILS cc::FileUtils::getInstance()
#define CCAUDIO cc::SimpleAudioEngine::getInstance()
#define CCAPP cc::CCApplication::getInstance()

NS_CC_BEGIN

#ifdef _WIN32
    #define nxbeep(t) MessageBeep(t)
#else
    #define nxbeep(t)
#endif

static cc::IntrusivePtr<Label> createLabel(std::string_view text,
                          std::string_view font,
                          float fontSize,
                          const Vec2& dimensions    = Vec2::ZERO,
                          TextHAlignment hAlignment = TextHAlignment::LEFT,
                          TextVAlignment vAlignment = TextVAlignment::TOP)
{
    if (FileUtils::getInstance()->isFileExist(font))
    {
        return Label::createWithTTF(text, font, fontSize, dimensions, hAlignment, vAlignment);
    }
    else
    {
        return Label::createWithSystemFont(text, font, fontSize, dimensions, hAlignment, vAlignment);
    }
}

static bool engine_inj_checkVisibility(Node* theNode)
{
    // CC_ASSERT(theNode != NULL);
    bool visible = false;
    for (Node* ptr = theNode; (ptr != nullptr && (visible = ptr->isVisible())); ptr = ptr->getParent())
        ;
    return visible;
}

static bool engine_inj_containsTouchPoint(cc::Node* target, cc::Touch* touch)
{
    assert(target != nullptr);

    cc::Point pt = target->convertTouchToNodeSpace(touch);

    const Vec2& size = target->getContentSize();

    cc::Rect rc(0, 0, size.width, size.height);

    bool contains = (rc.containsPoint(pt));

    // CCLOG("check %#x coordinate:(%f, %f), contains:%d", target, pt.x, pt.y, contains);
    return contains;
}

static bool engine_inj_containsPoint(cc::Node* target, const cc::Vec2& worldPoint)
{
    cc::Point pt = target->convertToNodeSpace(worldPoint);

    const Vec2& size = target->getContentSize();

    cc::Rect rc(0, 0, size.width, size.height);

    bool contains = (rc.containsPoint(pt));

    // CCLOG("check %#x coordinate:(%f, %f), contains:%d", target, pt.x, pt.y, contains);
    return contains;
}

static uint32_t engine_inj_c4b2dw(const Color4B& value)
{
    auto rvalue = (uint32_t)value.a << 24 | (uint32_t)value.b << 16 | (uint32_t)value.g << 8 | (uint32_t)value.r;
    return rvalue;
}

static cc::IntrusivePtr<Sprite> engine_inj_create_lump(const Color4B& color, int height, int width)
{
    unsigned int* pixels((unsigned int*)malloc(height * width * sizeof(unsigned int)));

    // Fill Pixels
    uint32_t* ptr           = pixels;
    const Color4B fillColor = Color4B::WHITE;
    for (int i = 0; i < height * width; ++i)
    {
        ptr[i] = engine_inj_c4b2dw(fillColor);  // 0xffffffff;
    }

    // create cursor by pixels
    cc::IntrusivePtr texture{new Texture2D()};

    texture->initWithData(pixels, height * width * sizeof(unsigned int), backend::PixelFormat::RGBA8, width, height);

    auto cursor = Sprite::createWithTexture(texture.get());

    cursor->setColor(Color3B(color));
    cursor->setOpacity(color.a);


    free(pixels);

    return cursor;
}

namespace ui
{

static void internalSetLableFont(Label* l, std::string_view fontName, float fontSize)
{
    if (FileUtils::getInstance()->isFileExist(fontName))
    {
        TTFConfig config    = l->getTTFConfig();
        config.fontFilePath = fontName;
        config.fontSize     = fontSize;
        l->setTTFConfig(config);
    }
    else
    {
        l->setSystemFontName(fontName);
        l->requestSystemFontRefresh();
        l->setSystemFontSize(fontSize);
    }
}

static float internalCalcStringWidth(std::string_view s, std::string_view fontName, float fontSize)
{
    auto label = createLabel(std::string{s}, fontName, fontSize);
    return label->getContentSize().width;
}

static std::string internalUTF8MoveLeft(std::string_view utf8Text, int length /* default utf8Text.length() */)
{
    if (!utf8Text.empty() && length > 0)
    {

        // get the delete byte number
        int deleteLen = 1;  // default, erase 1 byte

        while (length >= deleteLen && 0x80 == (0xC0 & utf8Text.at(length - deleteLen)))
        {
            ++deleteLen;
        }

        return std::string{utf8Text.data(), static_cast<size_t>(length - deleteLen)};
    }
    else
    {
        return std::string{utf8Text};
    }
}

static std::string internalUTF8MoveRight(std::string_view utf8Text, int length /* default utf8Text.length() */)
{
    if (!utf8Text.empty() && length >= 0)
    {

        // get the delete byte number
        size_t addLen = 1;  // default, erase 1 byte

        while ((length + addLen) < utf8Text.size() && 0x80 == (0xC0 & utf8Text.at(length + addLen)))
        {
            ++addLen;
        }

        return std::string{utf8Text.data(), static_cast<size_t>(length + addLen)};
    }
    else
    {
        return std::string{utf8Text};
    }
}

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////
TextFieldEx::TextFieldEx()
    : editable(true)
    , renderLabel(nullptr)
    , charCount(0)
    , inputText("")
    , placeHolder("")
    , colorText(Color4B::WHITE)
    , colorSpaceHolder(Color4B::GRAY)
    , secureTextEntry(false)
    , cursor(nullptr)
    , enabled(true)
    , touchListener(nullptr)
    , onTextModify(nullptr)
    , onOpenIME(nullptr)
    , onCloseIME(nullptr)
    , charLimit(std::numeric_limits<int>::max())
    , systemFontUsed(false)
    , fontSize(24)
    , insertPosUtf8(0)
    , insertPos(0)
    , cursorPos(0)
    , touchCursorControlEnabled(true)
    , cursorVisible(false)
    , _continuousTouchDelayTimerID(nullptr)
    , _continuousTouchDelayTime(0.6)
{}

TextFieldEx::~TextFieldEx()
{
    if (this->touchListener != nullptr)
        CCEVENTMGR->removeEventListener(this->touchListener);
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////
cc::IntrusivePtr<TextFieldEx> TextFieldEx::create(std::string_view placeholder,
                                 std::string_view fontName,
                                 float fontSize,
                                 float cursorWidth,
                                 const Color4B& cursorColor)
{
    cc::IntrusivePtr ret{new TextFieldEx()};
    if (ret && ret->initWithPlaceHolder("", fontName, fontSize, cursorWidth, cursorColor))
    {

        if (placeholder.size() > 0)
        {
            ret->setPlaceholderText(placeholder);
        }
        return ret;
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////
bool TextFieldEx::initWithPlaceHolder(std::string_view placeholder,
                                      std::string_view fontName,
                                      float fontSize,
                                      float cursorWidth,
                                      const Color4B& cursorColor)
{
    this->placeHolder = placeholder;

    auto labelOwner =
        createLabel(placeholder, fontName, fontSize, Vec2::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    this->renderLabel = labelOwner.get();
    this->renderLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    this->addChild(this->renderLabel);

    CCRUNONGL([this] { renderLabel->setPosition(Point(0, this->getContentSize().height / 2)); });

    __initCursor(fontSize, cursorWidth, cursorColor);

    this->fontName       = fontName;
    this->fontSize       = fontSize;
    this->systemFontUsed = !FileUtils::getInstance()->isFileExist(fontName);

    return true;
}

std::string_view TextFieldEx::getTextFontName() const
{
    return this->fontName;
}

void TextFieldEx::setTextFontName(std::string_view fontName)
{
    if (FileUtils::getInstance()->isFileExist(fontName))
    {
        TTFConfig config    = renderLabel->getTTFConfig();
        config.fontFilePath = fontName;
        config.fontSize     = this->fontSize;
        renderLabel->setTTFConfig(config);
        systemFontUsed = false;
        _fontType      = 1;
    }
    else
    {
        renderLabel->setSystemFontName(fontName);
        if (!systemFontUsed)
        {
            renderLabel->requestSystemFontRefresh();
        }
        renderLabel->setSystemFontSize(this->fontSize);
        systemFontUsed = true;
        _fontType      = 0;
    }
    this->fontName = fontName;

    using namespace std::string_view_literals;
    this->asteriskWidth = internalCalcStringWidth("*"sv, this->fontName, this->fontSize);
}

void TextFieldEx::setTextFontSize(float size)
{
    if (this->systemFontUsed)
    {
        renderLabel->setSystemFontSize(size);
    }
    else
    {
        TTFConfig config = renderLabel->getTTFConfig();
        config.fontSize  = size;
        renderLabel->setTTFConfig(config);
    }

    this->fontSize = size;

    using namespace std::string_view_literals;
    this->asteriskWidth = internalCalcStringWidth("*"sv, this->fontName, this->fontSize);
}

float TextFieldEx::getTextFontSize() const
{
    return this->fontSize;
}

void TextFieldEx::enableIME(Node* control)
{
    if (touchListener != nullptr)
    {
        return;
    }
    auto touchOwner = EventListenerTouchOneByOne::create();
    touchListener = touchOwner.get();

    if (control == nullptr)
        control = this;

    touchListener->onTouchBegan = [=](Touch* touch, Event*) {
        bool focus = (engine_inj_checkVisibility(this) && this->editable && this->enabled &&
                      engine_inj_containsTouchPoint(control, touch));

        if (this->_continuousTouchDelayTimerID != nullptr)
        {
            stimer::kill(this->_continuousTouchDelayTimerID);
            this->_continuousTouchDelayTimerID = nullptr;
        }

        if (focus && this->cursorVisible)
        {
            auto worldPoint = touch->getLocation();
            if (this->_continuousTouchCallback)
            {
                this->_continuousTouchDelayTimerID = stimer::delay(
                    this->_continuousTouchDelayTime, [=]() { this->_continuousTouchCallback(worldPoint); });
            }
        }
        return true;
    };
    touchListener->onTouchEnded = [control, this](Touch* touch, Event* e) {
        if (this->_continuousTouchDelayTimerID != nullptr)
        {
            stimer::kill(this->_continuousTouchDelayTimerID);
            this->_continuousTouchDelayTimerID = nullptr;
        }

        bool focus = (engine_inj_checkVisibility(this) && this->editable && this->enabled &&
                      engine_inj_containsTouchPoint(control, touch));

        if (focus)
        {
            if (!this->cursorVisible)
                beginEditing();
            if (this->touchCursorControlEnabled)
            {
                auto renderLabelPoint = renderLabel->convertToNodeSpace(touch->getLocation());
                __moveCursorTo(renderLabelPoint.x);
            }
        }
        else
        {
            endEditing();
        }
    };

    CCEVENTMGR->addEventListenerWithSceneGraphPriority(touchListener, this);


}

void TextFieldEx::disableIME(void)
{
    CCEVENTMGR->removeEventListener(touchListener);

    touchListener = nullptr;
    endEditing();
}

Label* TextFieldEx::getRenderLabel()
{
    return this->renderLabel;
}

//////////////////////////////////////////////////////////////////////////
// Editing focus
//////////////////////////////////////////////////////////////////////////

void TextFieldEx::beginEditing()
{
    auto view = _director->getOpenGLView();
    if (!view || !view->getTextInputWindow() || _inputSession.state().active)
        return;
    TextInputOptions options;
    options.purpose = secureTextEntry ? TextInputPurpose::password : TextInputPurpose::text;
    auto result = view->getTextInputService().begin(view->getTextInputWindow(), options,
        [this](const TextInputEvent& event) { receiveTextInput(event); }, {inputArea(), {}});
    if (!result)
        return;
    _inputSession = std::move(result.session);
    __updateCursorPosition();
    __showCursor();
    _inputSession.requestKeyboard(true);
    if (onOpenIME)
        onOpenIME();
}

void TextFieldEx::endEditing()
{
    _inputSession.close();
}

void TextFieldEx::receiveTextInput(const TextInputEvent& event)
{
    auto keepAlive = cc::IntrusivePtr{this};
    if (event.session != _inputSession.id())
        return;
    if (auto text = std::get_if<TextInputCommit>(&event.payload))
        insertText(text->text.c_str(), text->text.size());
    else if (auto cmd = std::get_if<TextInputCommand>(&event.payload))
    {
        switch (cmd->action)
        {
        case TextInputCommandAction::backspace: deleteBackward(); break;
        case TextInputCommandAction::deleteForward: handleDeleteKeyEvent(); break;
        case TextInputCommandAction::left: __moveCursor(-1); break;
        case TextInputCommandAction::right: __moveCursor(1); break;
        case TextInputCommandAction::cancel:
        case TextInputCommandAction::insertNewline:
        case TextInputCommandAction::done: endEditing(); break;
        default: break;
        }
    }
    else if (std::holds_alternative<TextInputClosed>(event.payload))
    {
        _inputSession = {};
        __hideCursor();
        if (onCloseIME)
            onCloseIME();
    }
}

std::optional<TextInputArea> TextFieldEx::inputArea()
{
    if (!cursor)
        return {};
    const auto caret = cursor->getBoundingBox();
    return textInputAreaForNode(*this, caret, Rect(0, caret.origin.y,
        std::max(1.0f, getContentSize().width), caret.size.height));
}

void TextFieldEx::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t flags)
{
    Node::visit(renderer, parentTransform, flags);
    if (_inputSession.id() && cursorVisible && isVisible())
        _inputSession.setArea(inputArea());
}

void TextFieldEx::onExit()
{
    if (_inputSession.id())
    {
        _inputSession = {};
        __hideCursor();
    }
    Node::onExit();
}


void TextFieldEx::insertText(const char* text, size_t len)
{
    if (!editable || !enabled)
        return;

    const std::string_view input(text, len);
    const auto newline = input.find('\n');
    const auto prefix = input.substr(0, newline);
    const TextInputIndex incoming(prefix);
    const auto count = incoming.scalarCount();
    if (!count)
        return;
    const auto capacity = charLimit ? charLimit - std::min(charLimit, charCount) : count.offset;
    const auto accepted = std::min(capacity, count.offset);
    if (accepted)
    {
        const auto nextCursor = static_cast<size_t>(insertPosUtf8) + accepted;
        std::string updated = inputText;
        updated.insert(static_cast<size_t>(insertPos), prefix.substr(0, incoming.utf8FromScalar(accepted).offset));
        setString(updated);
        setCursorAtScalar(nextCursor);
        if (onTextModify)
            onTextModify();
    }
    if (newline != input.npos)
        endEditing();
}

void TextFieldEx::deleteBackward()
{
    if (!this->editable || !this->enabled || 0 == this->charCount)
    {
        nxbeep(0);
        return;
    }

    size_t len = inputText.length();
    if (0 == len || insertPos == 0)
    {
        nxbeep(0);
        // there is no string
        // __updateCursorPosition();
        return;
    }

    // get the delete byte number
    size_t deleteLen = 1;  // default, erase 1 byte

    while (0x80 == (0xC0 & inputText.at(insertPos - deleteLen)))
    {
        ++deleteLen;
    }

    // if (_delegate && _delegate->onTextFieldDeleteBackward(this, _inputText.c_str() + len - deleteLen,
    // static_cast<int>(deleteLen)))
    //{
    //     // delegate doesn't wan't to delete backwards
    //     return;
    // }

    // if all text deleted, show placeholder string
    if (len <= deleteLen)
    {
        __moveCursor(-1);

        this->inputText.clear();
        this->charCount = 0;
        this->renderLabel->setTextColor(colorSpaceHolder);
        this->renderLabel->setString(placeHolder);

        // __updateCursorPosition();

        // this->contentDirty = true;

        if (this->onTextModify)
            this->onTextModify();
        return;
    }

    // set new input text
    std::string text = inputText;  // (inputText.c_str(), len - deleteLen);
    text.erase(insertPos - deleteLen, deleteLen);

    __moveCursor(-1);

    this->setString(text);

    //__updateCursorPosition();
    // __moveCursor(-1);

    if (this->onTextModify)
        this->onTextModify();
}

void TextFieldEx::handleDeleteKeyEvent()
{
    if (!this->editable || !this->enabled || 0 == this->charCount)
    {
        nxbeep(0);
        return;
    }

    size_t len = inputText.length();
    if (0 == len || insertPosUtf8 == this->charCount)
    {
        nxbeep(0);
        // there is no string
        // __updateCursorPosition();
        return;
    }

    // get the delete byte number
    size_t deleteLen = 1;  // default, erase 1 byte

    while ((inputText.length() > insertPos + deleteLen) && 0x80 == (0xC0 & inputText.at(insertPos + deleteLen)))
    {
        ++deleteLen;
    }

    // if (_delegate && _delegate->onTextFieldDeleteBackward(this, _inputText.c_str() + len - deleteLen,
    // static_cast<int>(deleteLen)))
    //{
    //     // delegate doesn't wan't to delete backwards
    //     return;
    // }

    // if all text deleted, show placeholder string
    if (len <= deleteLen)
    {
        this->inputText.clear();
        this->charCount = 0;
        this->renderLabel->setTextColor(colorSpaceHolder);
        this->renderLabel->setString(placeHolder);

        __updateCursorPosition();

        // this->contentDirty = true;

        if (this->onTextModify)
            this->onTextModify();
        return;
    }

    // set new input text
    std::string text = inputText;  // (inputText.c_str(), len - deleteLen);
    text.erase(insertPos, deleteLen);

    // __moveCursor(-1);

    this->setString(text);

    if (this->onTextModify)
        this->onTextModify();
}


void TextFieldEx::setTextColor(const Color4B& color)
{
    colorText = color;
    if (!this->inputText.empty())
        this->renderLabel->setTextColor(colorText);
}

const Color4B& TextFieldEx::getTextColor(void) const
{
    return colorText;
}

void TextFieldEx::setCursorColor(const Color3B& color)
{
    this->cursor->setColor(color);
}

const Color3B& TextFieldEx::getCursorColor(void) const
{
    return this->cursor->getColor();
}

const Color4B& TextFieldEx::getPlaceholderColor() const
{
    return colorSpaceHolder;
}

void TextFieldEx::setPlaceholderColor(const Color4B& color)
{
    colorSpaceHolder = color;
    if (this->inputText.empty())
        this->renderLabel->setTextColor(color);
}

//////////////////////////////////////////////////////////////////////////
// properties
//////////////////////////////////////////////////////////////////////////

// input text property
void TextFieldEx::setString(std::string_view text)
{
    const TextInputIndex index(text);
    const auto count = index.scalarCount();
    if (!count)
        return;
    const auto oldCursor = static_cast<size_t>(insertPosUtf8);
    const auto newCursor = oldCursor == charCount ? count.offset : std::min(oldCursor, count.offset);
    inputText = text;
    charCount = count.offset;
    if (inputText.empty())
    {
        renderLabel->setTextColor(colorSpaceHolder);
        renderLabel->setString(placeHolder);
    }
    else
    {
        renderLabel->setTextColor(colorText);
        if (secureTextEntry)
        {
            std::string masked;
            for (size_t i = 0; i < charCount; ++i)
                masked.append("\xe2\x80\xa2");
            renderLabel->setString(masked);
        }
        else
            renderLabel->setString(inputText);
    }
    setCursorAtScalar(newCursor);
}

void TextFieldEx::setCursorAtScalar(size_t position)
{
    const bool atEnd = position == charCount;
    insertPosUtf8 = static_cast<int>(position);
    insertPos = static_cast<int>(atEnd ? inputText.size() : TextInputIndex(inputText).utf8FromScalar(position).offset);
    cursorPos = secureTextEntry ? static_cast<int>(position * 3) : insertPos;
    if (cursor)
    {
        const auto visible = renderLabel->getString().substr(0, cursorPos);
        const float x = position == 0 ? 0 : (atEnd ? renderLabel->getContentSize().width :
                                             internalCalcStringWidth(visible, fontName, fontSize));
        cursor->setPosition(Point(x, getContentSize().height / 2));
    }
}

void TextFieldEx::updateContentSize(void)
{
    this->setContentSize(renderLabel->getContentSize());
}

std::string_view TextFieldEx::getString() const
{
    return inputText;
}

// place holder text property
void TextFieldEx::setPlaceholderText(std::string_view text)
{
    placeHolder = text;
    if (inputText.empty())
    {
        renderLabel->setTextColor(colorSpaceHolder);
        renderLabel->setString(placeHolder);
    }
}

std::string_view TextFieldEx::getPlaceholderText() const
{
    return placeHolder;
}

// secureTextEntry
void TextFieldEx::setPasswordEnabled(bool value)
{
    if (secureTextEntry != value)
    {
        secureTextEntry = value;
        this->setString(this->getString());
        __updateCursorPosition();
    }
}

bool TextFieldEx::isPasswordEnabled() const
{
    return secureTextEntry;
}

const Vec2& TextFieldEx::getContentSize() const
{
    // const_cast<TextFieldEx*>(this)->setContentSize(renderLabel->getContentSize());
    return Node::getContentSize();
}

void TextFieldEx::setEnabled(bool bEnabled)
{
    if (this->enabled != bEnabled)
    {
        if (!bEnabled)
        {
            this->endEditing();
        }
        this->enabled = bEnabled;
    }
}

bool TextFieldEx::isEnabled(void) const
{
    return this->enabled;
}

int TextFieldEx::getFontType() const
{
    return _fontType;
}

void TextFieldEx::__initCursor(int height, int width, const Color4B& color)
{
    auto cursorOwner = engine_inj_create_lump(Color4B(color), height, width);
    this->cursor = cursorOwner.get();

    this->addChild(this->cursor);

    this->cursor->setPosition(Point(0, this->getContentSize().height / 2));
    // nodes_layout::setNodeLB(this->cursor, cc::Point::ZERO);

    /*CCAction* blink = CCRepeatForever::create(
        (CCActionInterval *)CCSequence::create(CCFadeOut::create(0.25f),
        CCFadeIn::create(0.25f),
        NULL));*/

    __hideCursor();

    __updateCursorPosition();
}

void TextFieldEx::__showCursor(void)
{
    if (this->cursor)
    {
        this->cursorVisible = true;
        this->cursor->setVisible(true);
        this->cursor->runAction(RepeatForever::create(Blink::create(1, 1).get()).get());
    }
}

void TextFieldEx::__hideCursor(void)
{
    if (this->cursor)
    {
        this->cursor->setVisible(false);
        this->cursorVisible = false;
        this->cursor->stopAllActions();
    }
}

void TextFieldEx::__updateCursorPosition(void)
{
    if (this->cursor && this->insertPosUtf8 == this->charCount)
    {
        if (0 == this->getCharCount())
        {
            this->cursor->setPosition(Point(0, this->getContentSize().height / 2));
        }
        else
        {
            this->cursor->setPosition(Point(renderLabel->getContentSize().width, this->getContentSize().height / 2));
        }
    }
}

void TextFieldEx::__moveCursor(int direction)
{
    /*bool checkSupport = this->renderLabel->getLetter(0) != nullptr;
    if (!checkSupport)
    {
        MessageBeep(MB_ICONHAND);
        return;
    }*/

    auto newOffset = this->insertPosUtf8 + direction;

    if (newOffset > 0 && newOffset <= this->charCount)
    {

        std::string_view displayText;
        if (!secureTextEntry)
            displayText = this->getString();
        else if (!this->inputText.empty())
            displayText = renderLabel->getString();

        if (direction < 0)
        {
            this->insertPos = static_cast<int>(internalUTF8MoveLeft(this->inputText, this->insertPos).size());

            auto s = internalUTF8MoveLeft(displayText, this->cursorPos);

            auto width = internalCalcStringWidth(s, this->fontName, this->fontSize);
            this->cursor->setPosition(Point(width, this->getContentSize().height / 2));
            this->cursorPos = static_cast<int>(s.length());
        }
        else
        {
            this->insertPos = static_cast<int>(internalUTF8MoveRight(this->inputText, this->insertPos).size());

            auto s     = internalUTF8MoveRight(displayText, this->cursorPos);
            auto width = internalCalcStringWidth(s, this->fontName, this->fontSize);
            this->cursor->setPosition(Point(width, this->getContentSize().height / 2));
            this->cursorPos = static_cast<int>(s.length());
        }

        this->insertPosUtf8 = newOffset;
    }
    else if (newOffset == 0)
    {
        this->cursor->setPosition(Point(0, this->getContentSize().height / 2));
        this->insertPosUtf8 = newOffset;
        this->insertPos     = 0;
        this->cursorPos     = 0;
    }
    else
    {
        // MessageBeep(0);
    }
}

void TextFieldEx::__moveCursorTo(float x)
{  // test
    // normalized x
    float normalizedX = 0;

    std::string_view displayText;
    if (!secureTextEntry)
    {
        displayText = this->inputText;
    }
    else
    {
        if (!this->inputText.empty())
        {
            displayText = renderLabel->getString();
        }
    }

    int length = static_cast<int>(displayText.length());
    int n      = static_cast<int>(this->charCount);  // UTF8 char counter

    int insertWhere     = 0;
    int insertWhereUtf8 = 0;
    while (length > 0)
    {
        auto checkX = internalCalcStringWidth(displayText, this->fontName, this->fontSize);
        if (x >= checkX)
        {
            insertWhere     = length;
            insertWhereUtf8 = n;
            normalizedX     = checkX;
            break;
        }

        // clamp backward
        size_t backwardLen = 1;  // default, erase 1 byte
        while (0x80 == (0xC0 & displayText.at(displayText.length() - backwardLen)))
        {
            ++backwardLen;
        }

        --n;
        displayText.remove_suffix(backwardLen);

        length -= backwardLen;
    }

    this->insertPos     = !this->secureTextEntry ? insertWhere : insertWhereUtf8;
    this->cursorPos     = insertWhere;
    this->insertPosUtf8 = insertWhereUtf8;
    this->cursor->setPosition(Point(normalizedX, this->getContentSize().height / 2));
}
};  // namespace ui

NS_CC_END

#endif
