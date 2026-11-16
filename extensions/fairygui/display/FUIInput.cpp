#include "FUIInput.h"
#include "UIPackage.h"
#include "GTextInput.h"
#include "UIConfig.h"
NS_FGUI_BEGIN
USING_NS_CC;

cc::IntrusivePtr<FUIInput> FUIInput::create()
{
    cc::IntrusivePtr pRet{new FUIInput()};

    auto* texture = UIPackage::getEmptyTexture();
    auto frame = SpriteFrame::createWithTexture(texture, Rect(Vec2::ZERO, texture->getContentSize()));
    auto background = ui::Scale9Sprite::createWithSpriteFrame(frame.get());
    if (pRet->initWithSizeAndBackgroundSprite(Size(100, 100), background.get()))
    {

        pRet->continueInit();
    }
    else
    {
        return nullptr;
    }

    return pRet;
}

FUIInput::FUIInput() :
    _textFormat(new TextFormat()),
    _password(false),
    _keyboardType(0)
{
}

FUIInput::~FUIInput()
{
    delete _textFormat;
}

std::string FUIInput::getText() const
{
    return ui::EditBox::getText();
}

void FUIInput::setText(const std::string & value)
{
    ui::EditBox::setText(value.c_str());
}

void FUIInput::applyTextFormat()
{
    setFontName(UIConfig::getRealFontName(_textFormat->face).c_str());
    setFontSize(_textFormat->fontSize);
    setPlaceholderFontSize(_textFormat->fontSize);
    setFontColor(_textFormat->color);
    //setPlaceholderFontColor(_textFormat->color);
}

bool FUIInput::isSingleLine() const
{
    return getInputMode() == ui::EditBox::InputMode::SINGLE_LINE;
}

void FUIInput::setSingleLine(bool value)
{
    setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
}

void FUIInput::setPassword(bool value)
{
    _password = value;
    setInputFlag(ui::EditBox::InputFlag::PASSWORD);
}

void FUIInput::setKeyboardType(int value)
{
    //if (!_password)
        //setInputMode((ui::EditBox::InputMode)value);
}

void FUIInput::openKeyboard()
{
    EditBox::openKeyboard();
}

void FUIInput::continueInit()
{
    applyTextFormat();

    //disable default behavior
    this->setTouchEnabled(false);
    this->addTouchEventListener(CC_CALLBACK_2(FUIInput::_touchDownAction, this));
}

void FUIInput::_touchDownAction(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType controlEvent)
{
    //do nothing
}

NS_FGUI_END
