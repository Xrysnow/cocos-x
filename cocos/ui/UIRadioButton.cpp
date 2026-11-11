/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)
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

#include "base/CCRefPtr.h"
#include "ui/UIRadioButton.h"

NS_CC_BEGIN

namespace ui
{

IMPLEMENT_CLASS_GUI_INFO(RadioButton)

RadioButton::RadioButton() : _radioButtonEventCallback(nullptr), _group(nullptr) {}

RadioButton::~RadioButton()
{
    _radioButtonEventCallback = nullptr;
    _group                    = nullptr;
}

RadioButton* RadioButton::create()
{
    RadioButton* widget = new RadioButton();
    if (widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

RadioButton* RadioButton::create(std::string_view backGround,
                                 std::string_view backGroundSelected,
                                 std::string_view cross,
                                 std::string_view backGroundDisabled,
                                 std::string_view frontCrossDisabled,
                                 TextureResType texType)
{
    RadioButton* pWidget = new RadioButton();
    if (pWidget->init(backGround, backGroundSelected, cross, backGroundDisabled, frontCrossDisabled, texType))
    {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}

RadioButton* RadioButton::create(std::string_view backGround, std::string_view cross, TextureResType texType)
{
    RadioButton* pWidget = new RadioButton();
    if (pWidget->init(backGround, "", cross, "", "", texType))
    {
        pWidget->autorelease();
        return pWidget;
    }
    CC_SAFE_DELETE(pWidget);
    return nullptr;
}

void RadioButton::dispatchSelectChangedEvent(bool selected)
{
    EventType eventType = (selected ? EventType::SELECTED : EventType::UNSELECTED);
    this->retain();
    if (auto callback = _radioButtonEventCallback)
    {
        callback(this, eventType);
    }

    if (selected && _group != nullptr)
    {
        _group->onChangedRadioButtonSelect(this);
    }
    this->release();
}

void RadioButton::addEventListener(const ccRadioButtonCallback& callback)
{
    _radioButtonEventCallback = callback;
}

void RadioButton::releaseUpEvent()
{
    auto keepAlive = makeRef(this);
    Widget::releaseUpEvent();

    if (!_isSelected)
    {
        setSelected(true);
        dispatchSelectChangedEvent(true);
    }
}

std::string RadioButton::getDescription() const
{
    return "RadioButton";
}

Widget* RadioButton::createCloneInstance()
{
    return RadioButton::create();
}

void RadioButton::copySpecialProperties(Widget* widget)
{
    RadioButton* radioButton = dynamic_cast<RadioButton*>(widget);
    if (radioButton)
    {
        AbstractCheckButton::copySpecialProperties(widget);
        _radioButtonEventCallback = radioButton->_radioButtonEventCallback;
        // A standalone clone is not a member of the source button's group.
        _group                    = nullptr;
    }
}

RadioButtonGroup::RadioButtonGroup()
    : _radioButtonGroupEventCallback(nullptr), _selectedRadioButton(nullptr), _allowedNoSelection(false)
{}

RadioButtonGroup::~RadioButtonGroup()
{
    _radioButtonGroupEventCallback = nullptr;
    _selectedRadioButton           = nullptr;
    for (auto* radioButton : _radioButtons)
    {
        if (radioButton->_group == this)
            radioButton->_group = nullptr;
    }
    _radioButtons.clear();
}

RadioButtonGroup* RadioButtonGroup::create()
{
    RadioButtonGroup* widget = new RadioButtonGroup();
    if (widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void RadioButtonGroup::addEventListener(const ccRadioButtonGroupCallback& callback)
{
    _radioButtonGroupEventCallback = callback;
}

void RadioButtonGroup::addRadioButton(RadioButton* radioButton)
{
    if (radioButton != nullptr)
    {
        CCASSERT(!radioButton->_group, "It already belongs to a group!");
        radioButton->_group = this;
        _radioButtons.pushBack(radioButton);

        if (!_allowedNoSelection && _selectedRadioButton == nullptr)
        {
            setSelectedButtonWithoutEvent(radioButton);
        }
    }
}

void RadioButtonGroup::removeRadioButton(RadioButton* radioButton)
{
    auto keepAlive = makeRef(this);
    ssize_t index = _radioButtons.getIndex(radioButton);
    if (index == CC_INVALID_INDEX)
    {
        CCLOGERROR("The radio button does not belong to this group!");
        return;
    }

    if (radioButton != nullptr)
    {
        auto buttonAlive = makeRef(radioButton);
        radioButton->_group = nullptr;
        // Erase before notifying: the callback may mutate the group again.
        _radioButtons.erase(index);
        if (radioButton == _selectedRadioButton)
        {
            deselect();
        }

        if (!_allowedNoSelection && _selectedRadioButton == nullptr && !_radioButtons.empty())
        {
            setSelectedButtonWithoutEvent(0);
        }
    }
}

void RadioButtonGroup::removeAllRadioButtons()
{
    auto keepAlive = makeRef(this);
    while (!_radioButtons.empty())
    {
        removeRadioButton(_radioButtons.at(0));
    }
}

ssize_t RadioButtonGroup::getNumberOfRadioButtons() const
{
    return _radioButtons.size();
}

RadioButton* RadioButtonGroup::getRadioButtonByIndex(int index) const
{
    if (index >= _radioButtons.size())
    {
        CCLOGERROR("Out of array index! length=%d, requestedIndex=%d", (int)_radioButtons.size(), index);
        return nullptr;
    }
    return _radioButtons.at(index);
}

void RadioButtonGroup::deselect()
{
    auto keepAlive = makeRef(this);
    auto selected = makeRef(_selectedRadioButton);
    // Publish the empty selection before a callback can select/deselect again.
    _selectedRadioButton = nullptr;
    if (selected)
    {
        selected->setSelected(false);
        selected->dispatchSelectChangedEvent(false);
    }
}

int RadioButtonGroup::getSelectedButtonIndex() const
{
    return (int)_radioButtons.getIndex(_selectedRadioButton);
}

void RadioButtonGroup::setSelectedButton(int index)
{
    CCASSERT(index < _radioButtons.size(), "Out of array index!");
    setSelectedButton(_radioButtons.at(index));
}

void RadioButtonGroup::setSelectedButton(RadioButton* radioButton)
{
    auto keepAlive = makeRef(this);
    setSelectedButtonWithoutEvent(radioButton);
    onChangedRadioButtonSelect(_selectedRadioButton);
}

void RadioButtonGroup::setSelectedButtonWithoutEvent(int index)
{
    setSelectedButtonWithoutEvent(_radioButtons.at(index));
}

void RadioButtonGroup::setSelectedButtonWithoutEvent(RadioButton* radioButton)
{
    auto keepAlive = makeRef(this);
    if (!_allowedNoSelection && radioButton == nullptr)
    {
        return;
    }
    if (_selectedRadioButton == radioButton)
    {
        return;
    }
    if (radioButton != nullptr && !_radioButtons.contains(radioButton))
    {
        CCLOGERROR("The radio button does not belong to this group!");
        return;
    }

    auto buttonAlive = makeRef(radioButton);
    deselect();
    // A deselection callback can select another button or remove the requested one.
    if (_selectedRadioButton != nullptr || (radioButton && !_radioButtons.contains(radioButton)))
        return;
    _selectedRadioButton = radioButton;
    if (_selectedRadioButton != nullptr)
    {
        _selectedRadioButton->setSelected(true);
    }
}

std::string RadioButtonGroup::getDescription() const
{
    return "RadioButtonGroup";
}

void RadioButtonGroup::setAllowedNoSelection(bool allowedNoSelection)
{
    _allowedNoSelection = allowedNoSelection;
    if (!_allowedNoSelection && _selectedRadioButton == nullptr)
    {
        if (!_radioButtons.empty())
        {
            setSelectedButton(_radioButtons.at(0));
        }
    }
}

bool RadioButtonGroup::isAllowedNoSelection() const
{
    return _allowedNoSelection;
}

Widget* RadioButtonGroup::createCloneInstance()
{
    return RadioButtonGroup::create();
}

void RadioButtonGroup::copySpecialProperties(Widget* widget)
{
    RadioButtonGroup* radioButtonGroup = dynamic_cast<RadioButtonGroup*>(widget);
    if (radioButtonGroup)
    {
        _radioButtonGroupEventCallback = radioButtonGroup->_radioButtonGroupEventCallback;
        _selectedRadioButton           = radioButtonGroup->_selectedRadioButton;
        _allowedNoSelection            = radioButtonGroup->_allowedNoSelection;

        _radioButtons.clear();
        for (const auto& radioButton : radioButtonGroup->_radioButtons)
        {
            _radioButtons.pushBack(radioButton);
        }
    }
}

void RadioButtonGroup::onChangedRadioButtonSelect(RadioButton* radioButton)
{
    auto keepAlive = makeRef(this);
    auto buttonAlive = makeRef(radioButton);
    if (radioButton && !_radioButtons.contains(radioButton))
        return;
    if (_selectedRadioButton != radioButton)
    {
        deselect();
        if (_selectedRadioButton != nullptr || (radioButton && !_radioButtons.contains(radioButton)))
            return;
        _selectedRadioButton = radioButton;
    }

    this->retain();
    if (auto callback = _radioButtonGroupEventCallback)
    {
        int index = (int)_radioButtons.getIndex(radioButton);
        auto selectedAlive = makeRef(_selectedRadioButton);
        callback(selectedAlive.get(), index, EventType::SELECT_CHANGED);
    }
    this->release();
}

}  // namespace ui

NS_CC_END
