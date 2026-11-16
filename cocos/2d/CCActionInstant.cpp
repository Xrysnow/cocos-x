/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
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

#include "2d/CCActionInstant.h"
#include "2d/CCNode.h"
#include "2d/CCSprite.h"

NS_CC_BEGIN
//
// InstantAction
//
void ActionInstant::startWithTarget(Node* target)
{
    FiniteTimeAction::startWithTarget(target);
    _done = false;
}

bool ActionInstant::isDone() const
{
    return _done;
}

void ActionInstant::step(float /*dt*/)
{
    float updateDt = 1;
    update(updateDt);
}

void ActionInstant::update(float /*time*/)
{
    _done = true;
}

//
// Show
//

cc::IntrusivePtr<Show> Show::create()
{
    cc::IntrusivePtr<Show> ret{new Show()};
    return ret;
}

void Show::update(float time)
{
    ActionInstant::update(time);
    _target->setVisible(true);
}

cc::IntrusivePtr<Action> Show::reverse() const
{
    return Hide::create();
}

cc::IntrusivePtr<Action> Show::clone() const
{
    // no copy constructor
    return Show::create();
}

//
// Hide
//
cc::IntrusivePtr<Hide> Hide::create()
{
    cc::IntrusivePtr<Hide> ret{new Hide()};

    return ret;
}

void Hide::update(float time)
{
    ActionInstant::update(time);
    _target->setVisible(false);
}

cc::IntrusivePtr<Action> Hide::reverse() const
{
    return Show::create();
}

cc::IntrusivePtr<Action> Hide::clone() const
{
    // no copy constructor
    return Hide::create();
}

//
// ToggleVisibility
//
cc::IntrusivePtr<ToggleVisibility> ToggleVisibility::create()
{
    cc::IntrusivePtr<ToggleVisibility> ret{new ToggleVisibility()};
    return ret;
}

void ToggleVisibility::update(float time)
{
    ActionInstant::update(time);
    _target->setVisible(!_target->isVisible());
}

cc::IntrusivePtr<Action> ToggleVisibility::reverse() const
{
    return ToggleVisibility::create();
}

cc::IntrusivePtr<Action> ToggleVisibility::clone() const
{
    // no copy constructor
    return ToggleVisibility::create();
}

//
// Remove Self
//
cc::IntrusivePtr<RemoveSelf> RemoveSelf::create(bool isNeedCleanUp /*= true*/)
{
    cc::IntrusivePtr<RemoveSelf> ret{new RemoveSelf()};

    if (!ret->init(isNeedCleanUp))
        return nullptr;
}

bool RemoveSelf::init(bool isNeedCleanUp)
{
    _isNeedCleanUp = isNeedCleanUp;
    return true;
}

void RemoveSelf::update(float time)
{
    ActionInstant::update(time);
    _target->removeFromParentAndCleanup(_isNeedCleanUp);
}

cc::IntrusivePtr<Action> RemoveSelf::reverse() const
{
    return RemoveSelf::create(_isNeedCleanUp);
}

cc::IntrusivePtr<Action> RemoveSelf::clone() const
{
    // no copy constructor
    return RemoveSelf::create(_isNeedCleanUp);
}

//
// FlipX
//

cc::IntrusivePtr<FlipX> FlipX::create(bool x)
{
    cc::IntrusivePtr<FlipX> ret{new FlipX()};

    if (ret->initWithFlipX(x))
    {
        return ret;
    }

    return nullptr;
}

bool FlipX::initWithFlipX(bool x)
{
    _flipX = x;
    return true;
}

void FlipX::update(float time)
{
    ActionInstant::update(time);
    static_cast<Sprite*>(_target)->setFlippedX(_flipX);
}

cc::IntrusivePtr<Action> FlipX::reverse() const
{
    return FlipX::create(!_flipX);
}

cc::IntrusivePtr<Action> FlipX::clone() const
{
    // no copy constructor
    return FlipX::create(_flipX);
}
//
// FlipY
//

cc::IntrusivePtr<FlipY> FlipY::create(bool y)
{
    cc::IntrusivePtr<FlipY> ret{new FlipY()};

    if (ret->initWithFlipY(y))
    {
        return ret;
    }

    return nullptr;
}

bool FlipY::initWithFlipY(bool y)
{
    _flipY = y;
    return true;
}

void FlipY::update(float time)
{
    ActionInstant::update(time);
    static_cast<Sprite*>(_target)->setFlippedY(_flipY);
}

cc::IntrusivePtr<Action> FlipY::reverse() const
{
    return FlipY::create(!_flipY);
}

cc::IntrusivePtr<Action> FlipY::clone() const
{
    // no copy constructor
    return FlipY::create(_flipY);
}

//
// Place
//

cc::IntrusivePtr<Place> Place::create(const Vec2& pos)
{
    cc::IntrusivePtr<Place> ret{new Place()};

    if (ret->initWithPosition(pos))
    {
        return ret;
    }

    return nullptr;
}

bool Place::initWithPosition(const Vec2& pos)
{
    _position = pos;
    return true;
}

cc::IntrusivePtr<Action> Place::clone() const
{
    // no copy constructor
    return Place::create(_position);
}

cc::IntrusivePtr<Action> Place::reverse() const
{
    // no reverse, just clone
    return this->clone();
}

void Place::update(float time)
{
    ActionInstant::update(time);
    _target->setPosition(_position);
}

//
// CallFunc
//

cc::IntrusivePtr<CallFunc> CallFunc::create(const std::function<void()>& func)
{
    cc::IntrusivePtr<CallFunc> ret{new CallFunc()};

    if (ret->initWithFunction(func))
    {
        return ret;
    }

    return nullptr;
}

bool CallFunc::initWithFunction(const std::function<void()>& func)
{
    _function = func;
    return true;
}

cc::IntrusivePtr<Action> CallFunc::clone() const
{
    // no copy constructor
    cc::IntrusivePtr<CallFunc> a{new CallFunc()};
    if (_function)
        a->initWithFunction(_function);

    return a;
}

cc::IntrusivePtr<Action> CallFunc::reverse() const
{
    // no reverse here, just return a clone
    return this->clone();
}

void CallFunc::update(float time)
{
    ActionInstant::update(time);
    this->execute();
}

void CallFunc::execute()
{
    if (_function)
    {
        _function();
    }
}

//
// CallFuncN
//

cc::IntrusivePtr<CallFuncN> CallFuncN::create(const std::function<void(Node*)>& func)
{
    cc::IntrusivePtr<CallFuncN> ret{new CallFuncN()};

    if (ret->initWithFunction(func))
    {
        return ret;
    }

    return nullptr;
}

void CallFuncN::execute()
{
    if (_functionN)
    {
        _functionN(_target);
    }
}

bool CallFuncN::initWithFunction(const std::function<void(Node*)>& func)
{
    _functionN = func;
    return true;
}

cc::IntrusivePtr<Action> CallFuncN::clone() const
{
    // no copy constructor
    cc::IntrusivePtr<CallFuncN> a{new CallFuncN()};
    if (_functionN)
        a->initWithFunction(_functionN);

    return a;
}

NS_CC_END
