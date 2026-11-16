/****************************************************************************
Copyright (C) 2010      Lam Pham
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "2d/CCActionProgressTimer.h"
#include "2d/CCProgressTimer.h"

NS_CC_BEGIN

#define kProgressTimerCast ProgressTimer*

// implementation of ProgressTo

cc::IntrusivePtr<ProgressTo> ProgressTo::create(float duration, float percent)
{
    cc::IntrusivePtr progressTo{new ProgressTo()};
    if (progressTo->initWithDuration(duration, percent))
    {
        return progressTo;
    }

    return nullptr;
}

bool ProgressTo::initWithDuration(float duration, float percent)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = percent;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> ProgressTo::clone() const
{
    // no copy constructor
    return ProgressTo::create(_duration, _to);
}

cc::IntrusivePtr<Action> ProgressTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in ProgressTo");
    return nullptr;
}

void ProgressTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _from = ((kProgressTimerCast)(target))->getPercentage();
}

void ProgressTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

// implementation of ProgressFromTo

cc::IntrusivePtr<ProgressFromTo> ProgressFromTo::create(float duration, float fromPercentage, float toPercentage)
{
    cc::IntrusivePtr progressFromTo{new ProgressFromTo()};
    if (progressFromTo->initWithDuration(duration, fromPercentage, toPercentage))
    {
        return progressFromTo;
    }

    return nullptr;
}

bool ProgressFromTo::initWithDuration(float duration, float fromPercentage, float toPercentage)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to   = toPercentage;
        _from = fromPercentage;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> ProgressFromTo::clone() const
{
    // no copy constructor
    return ProgressFromTo::create(_duration, _from, _to);
}

cc::IntrusivePtr<Action> ProgressFromTo::reverse() const
{
    return ProgressFromTo::create(_duration, _to, _from);
}

void ProgressFromTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
}

void ProgressFromTo::update(float time)
{
    ((kProgressTimerCast)(_target))->setPercentage(_from + (_to - _from) * time);
}

NS_CC_END
