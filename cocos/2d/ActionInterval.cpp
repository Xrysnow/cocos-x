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

#include "2d/ActionInterval.h"

#include <stdarg.h>

#include "2d/Sprite.h"
#include "2d/Node.h"
#include "2d/SpriteFrame.h"
#include "2d/ActionInstant.h"
#include "base/Director.h"
#include "base/EventCustom.h"
#include "base/EventDispatcher.h"
#include "platform/StdC.h"
#include "base/ScriptSupport.h"

NS_CC_BEGIN

// Extra action for making a Sequence or Spawn when only adding one action to it.
class ExtraAction : public FiniteTimeAction
{
public:
    static cc::IntrusivePtr<ExtraAction> create();
    virtual cc::IntrusivePtr<Action> clone() const;
    virtual cc::IntrusivePtr<Action> reverse() const;
    virtual void update(float time);
    virtual void step(float dt);
};

cc::IntrusivePtr<ExtraAction> ExtraAction::create()
{
    cc::IntrusivePtr ret{new ExtraAction()};
    return ret;
}

cc::IntrusivePtr<Action> ExtraAction::clone() const
{
    // no copy constructor
    return ExtraAction::create().get();
}

cc::IntrusivePtr<Action> ExtraAction::reverse() const
{
    return ExtraAction::create().get();
}

void ExtraAction::update(float /*time*/) {}

void ExtraAction::step(float /*dt*/) {}

//
// IntervalAction
//

bool ActionInterval::initWithDuration(float d)
{
    _duration = d;

    _elapsed   = 0;
    _firstTick = true;
    _done      = false;

    return true;
}

bool ActionInterval::sendUpdateEventToScript(float dt, Action* actionObject)
{
    return false;
}

bool ActionInterval::isDone() const
{
    return _done;
}

void ActionInterval::step(float dt)
{
    if (_firstTick)
    {
        _firstTick = false;
        _elapsed   = 0;
    }
    else
    {
        _elapsed += dt;
    }

    float updateDt = std::max(0.0f,  // needed for rewind. elapsed could be negative
                              std::min(1.0f, _elapsed / _duration));

    if (sendUpdateEventToScript(updateDt, this))
        return;

    this->update(updateDt);

    _done = _elapsed >= _duration;
}

void ActionInterval::setAmplitudeRate(float /*amp*/)
{
    // Abstract class needs implementation
    CCASSERT(0, "Subclass should implement this method!");
}

float ActionInterval::getAmplitudeRate()
{
    // Abstract class needs implementation
    CCASSERT(0, "Subclass should implement this method!");

    return 0;
}

void ActionInterval::startWithTarget(Node* target)
{
    FiniteTimeAction::startWithTarget(target);
    _elapsed   = 0.0f;
    _firstTick = true;
    _done      = false;
}

//
// Sequence
//

cc::IntrusivePtr<Sequence> Sequence::createWithTwoActions(FiniteTimeAction* actionOne, FiniteTimeAction* actionTwo)
{
    cc::IntrusivePtr sequence{new Sequence()};
    if (sequence->initWithTwoActions(actionOne, actionTwo))
    {
        return sequence;
    }

    return nullptr;
}



cc::IntrusivePtr<Sequence> Sequence::createWithVariableList(FiniteTimeAction* action1, va_list args)
{
    FiniteTimeAction* now;
    cc::IntrusivePtr<FiniteTimeAction> prev{action1};
    bool bOneAction        = true;

    while (action1)
    {
        now = va_arg(args, FiniteTimeAction*);
        if (now)
        {
            prev       = createWithTwoActions(prev, now);
            bOneAction = false;
        }
        else
        {
            // If only one action is added to Sequence, make up a Sequence by adding a simplest finite time action.
            if (bOneAction)
            {
                prev = createWithTwoActions(prev, ExtraAction::create().get());
            }
            break;
        }
    }

    return cc::static_pointer_cast<Sequence>(std::move(prev));
}

cc::IntrusivePtr<Sequence> Sequence::create(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    cc::IntrusivePtr seq{new Sequence};

    if (seq->init(arrayOfActions))
    {
        return seq;
    }

    return nullptr;
}

bool Sequence::init(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    auto count = arrayOfActions.size();
    if (count == 0)
        return false;

    if (count == 1)
        return initWithTwoActions(arrayOfActions.at(0), ExtraAction::create().get());

    // else size > 1
    cc::IntrusivePtr<FiniteTimeAction> prev{arrayOfActions.at(0)};
    for (int i = 1; i < count - 1; ++i)
    {
        prev = createWithTwoActions(prev, arrayOfActions.at(i));
    }

    return initWithTwoActions(prev, arrayOfActions.at(count - 1));
}

bool Sequence::initWithTwoActions(FiniteTimeAction* actionOne, FiniteTimeAction* actionTwo)
{
    CCASSERT(actionOne != nullptr, "actionOne can't be nullptr!");
    CCASSERT(actionTwo != nullptr, "actionTwo can't be nullptr!");
    if (actionOne == nullptr || actionTwo == nullptr)
    {
        log("Sequence::initWithTwoActions error: action is nullptr!!");
        return false;
    }

    float d = actionOne->getDuration() + actionTwo->getDuration();
    ActionInterval::initWithDuration(d);

    _actions[0] = actionOne;
    actionOne->retain();

    _actions[1] = actionTwo;
    actionTwo->retain();

    return true;
}

bool Sequence::isDone() const
{
    // fix issue #17884
    if (dynamic_cast<ActionInstant*>(_actions[1]))
        return (_done && _actions[1]->isDone());
    else
        return _done;
}

cc::IntrusivePtr<Action> Sequence::clone() const
{
    // no copy constructor
    if (_actions[0] && _actions[1])
    {
        return Sequence::createWithTwoActions(cc::static_pointer_cast<FiniteTimeAction>(_actions[0]->clone()).get(),
                                              cc::static_pointer_cast<FiniteTimeAction>(_actions[1]->clone()).get());
    }
    else
    {
        return nullptr;
    }
}

Sequence::Sequence() : _split(0)
{
    _actions[0] = nullptr;
    _actions[1] = nullptr;
}

Sequence::~Sequence()
{
    CC_SAFE_RELEASE(_actions[0]);
    CC_SAFE_RELEASE(_actions[1]);
}

void Sequence::startWithTarget(Node* target)
{
    if (target == nullptr)
    {
        log("Sequence::startWithTarget error: target is nullptr!");
        return;
    }
    if (_actions[0] == nullptr || _actions[1] == nullptr)
    {
        log("Sequence::startWithTarget error: _actions[0] or _actions[1] is nullptr!");
        return;
    }
    if (_duration > FLT_EPSILON)
        // fix #14936 - FLT_EPSILON (instant action) / very fast duration (0.001) leads to wrong split, that leads to
        // call instant action few times
        _split = _actions[0]->getDuration() > FLT_EPSILON ? _actions[0]->getDuration() / _duration : 0;

    ActionInterval::startWithTarget(target);
    _last = -1;
}

void Sequence::stop()
{
    // Issue #1305
    if (_last != -1 && _actions[_last])
    {
        _actions[_last]->stop();
    }

    ActionInterval::stop();
}

void Sequence::update(float t)
{
    int found   = 0;
    float new_t = 0.0f;

    if (t < _split)
    {
        // action[0]
        found = 0;
        if (_split != 0)
            new_t = t / _split;
        else
            new_t = 1;
    }
    else
    {
        // action[1]
        found = 1;
        if (_split == 1)
            new_t = 1;
        else
            new_t = (t - _split) / (1 - _split);
    }

    if (found == 1)
    {
        if (_last == -1)
        {
            // action[0] was skipped, execute it.
            _actions[0]->startWithTarget(_target);
            if (!(sendUpdateEventToScript(1.0f, _actions[0])))
                _actions[0]->update(1.0f);
            _actions[0]->stop();
        }
        else if (_last == 0)
        {
            // switching to action 1. stop action 0.
            if (!(sendUpdateEventToScript(1.0f, _actions[0])))
                _actions[0]->update(1.0f);
            _actions[0]->stop();
        }
    }
    else if (found == 0 && _last == 1)
    {
        // Reverse mode ?
        // FIXME: Bug. this case doesn't contemplate when _last==-1, found=0 and in "reverse mode"
        // since it will require a hack to know if an action is on reverse mode or not.
        // "step" should be overridden, and the "reverseMode" value propagated to inner Sequences.
        if (!(sendUpdateEventToScript(0, _actions[1])))
            _actions[1]->update(0);
        _actions[1]->stop();
    }
    // Last action found and it is done.
    if (found == _last && _actions[found]->isDone())
    {
        return;
    }

    // Last action found and it is done
    if (found != _last)
    {
        _actions[found]->startWithTarget(_target);
    }
    if (!(sendUpdateEventToScript(new_t, _actions[found])))
        _actions[found]->update(new_t);
    _last = found;
}

cc::IntrusivePtr<Action> Sequence::reverse() const
{
    if (_actions[0] && _actions[1])
        return Sequence::createWithTwoActions(cc::static_pointer_cast<FiniteTimeAction>(_actions[1]->reverse()).get(), cc::static_pointer_cast<FiniteTimeAction>(_actions[0]->reverse()).get());
    else
        return nullptr;
}

//
// Repeat
//

cc::IntrusivePtr<Repeat> Repeat::create(FiniteTimeAction* action, unsigned int times)
{
    cc::IntrusivePtr repeat{new Repeat()};
    if (repeat->initWithAction(action, times))
    {
        return repeat;
    }

    return nullptr;
}

bool Repeat::initWithAction(FiniteTimeAction* action, unsigned int times)
{
    if (action && ActionInterval::initWithDuration(action->getDuration() * times))
    {
        _times       = times;
        _innerAction = action;
        action->retain();

        _actionInstant = dynamic_cast<ActionInstant*>(action) ? true : false;
        // an instant action needs to be executed one time less in the update method since it uses startWithTarget to
        // execute the action
        //  minggo: instant action doesn't execute action in Repeat::startWithTarget(), so comment it.
        //        if (_actionInstant)
        //        {
        //            _times -=1;
        //        }
        _total = 0;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> Repeat::clone() const
{
    // no copy constructor
    return Repeat::create(cc::static_pointer_cast<FiniteTimeAction>(_innerAction->clone()).get(), _times);
}

Repeat::~Repeat()
{
    CC_SAFE_RELEASE(_innerAction);
}

void Repeat::startWithTarget(Node* target)
{
    _total  = 0;
    _nextDt = _innerAction->getDuration() / _duration;
    ActionInterval::startWithTarget(target);
    _innerAction->startWithTarget(target);
}

void Repeat::stop()
{
    _innerAction->stop();
    ActionInterval::stop();
}

// issue #80. Instead of hooking step:, hook update: since it can be called by any
// container action like Repeat, Sequence, Ease, etc..
void Repeat::update(float dt)
{
    if (dt >= _nextDt)
    {
        while (dt >= _nextDt && _total < _times)
        {
            if (!(sendUpdateEventToScript(1.0f, _innerAction)))
                _innerAction->update(1.0f);
            _total++;

            _innerAction->stop();
            _innerAction->startWithTarget(_target);
            _nextDt = _innerAction->getDuration() / _duration * (_total + 1);
        }

        // fix for issue #1288, incorrect end value of repeat
        if (std::abs(dt - 1.0f) < FLT_EPSILON && _total < _times)
        {
            if (!(sendUpdateEventToScript(1.0f, _innerAction)))
                _innerAction->update(1.0f);

            _total++;
        }

        // don't set an instant action back or update it, it has no use because it has no duration
        if (!_actionInstant)
        {
            if (_total == _times)
            {
                // minggo: inner action update is invoked above, don't have to invoke it here
                //                if (!(sendUpdateEventToScript(1, _innerAction)))
                //                    _innerAction->update(1);
                _innerAction->stop();
            }
            else
            {
                // issue #390 prevent jerk, use right update
                if (!(sendUpdateEventToScript(dt - (_nextDt - _innerAction->getDuration() / _duration), _innerAction)))
                    _innerAction->update(dt - (_nextDt - _innerAction->getDuration() / _duration));
            }
        }
    }
    else
    {
        if (!(sendUpdateEventToScript(fmodf(dt * _times, 1.0f), _innerAction)))
            _innerAction->update(fmodf(dt * _times, 1.0f));
    }
}

bool Repeat::isDone() const
{
    return _total == _times;
}

cc::IntrusivePtr<Action> Repeat::reverse() const
{
    return Repeat::create(cc::static_pointer_cast<FiniteTimeAction>(_innerAction->reverse()).get(), _times);
}

//
// RepeatForever
//
RepeatForever::~RepeatForever()
{
    CC_SAFE_RELEASE(_innerAction);
}

cc::IntrusivePtr<RepeatForever> RepeatForever::create(ActionInterval* action)
{
    cc::IntrusivePtr ret{new RepeatForever()};
    if (ret->initWithAction(action))
    {
        return ret;
    }

    return nullptr;
}

bool RepeatForever::initWithAction(ActionInterval* action)
{
    CCASSERT(action != nullptr, "action can't be nullptr!");
    if (action == nullptr)
    {
        log("RepeatForever::initWithAction error:action is nullptr!");
        return false;
    }

    action->retain();
    _innerAction = action;

    return true;
}

cc::IntrusivePtr<Action> RepeatForever::clone() const
{
    // no copy constructor
    return RepeatForever::create(cc::static_pointer_cast<ActionInterval>(_innerAction->clone()).get());
}

void RepeatForever::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _innerAction->startWithTarget(target);
}

void RepeatForever::step(float dt)
{
    _innerAction->step(dt);
    // only action interval should prevent jerk, issue #17808
    if (_innerAction->isDone() && _innerAction->getDuration() > 0)
    {
        float diff = _innerAction->getElapsed() - _innerAction->getDuration();
        if (diff > _innerAction->getDuration())
            diff = fmodf(diff, _innerAction->getDuration());
        _innerAction->startWithTarget(_target);
        // to prevent jerk. cocos2d-iphone issue #390, 1247
        _innerAction->step(0.0f);
        _innerAction->step(diff);
    }
}

bool RepeatForever::isDone() const
{
    return false;
}

cc::IntrusivePtr<Action> RepeatForever::reverse() const
{
    return RepeatForever::create(cc::static_pointer_cast<ActionInterval>(_innerAction->reverse()).get());
}

//
// Spawn
//



cc::IntrusivePtr<Spawn> Spawn::createWithVariableList(FiniteTimeAction* action1, va_list args)
{
    FiniteTimeAction* now;
    cc::IntrusivePtr<FiniteTimeAction> prev{action1};
    bool oneAction         = true;

    while (action1)
    {
        now = va_arg(args, FiniteTimeAction*);
        if (now)
        {
            prev      = createWithTwoActions(prev, now);
            oneAction = false;
        }
        else
        {
            // If only one action is added to Spawn, make up a Spawn by adding a simplest finite time action.
            if (oneAction)
            {
                prev = createWithTwoActions(prev, ExtraAction::create().get());
            }
            break;
        }
    }

    return cc::static_pointer_cast<Spawn>(std::move(prev));
}

cc::IntrusivePtr<Spawn> Spawn::create(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    cc::IntrusivePtr ret{new Spawn};

    if (ret->init(arrayOfActions))
    {
        return ret;
    }

    return nullptr;
}

cc::IntrusivePtr<Spawn> Spawn::createWithTwoActions(FiniteTimeAction* action1, FiniteTimeAction* action2)
{
    cc::IntrusivePtr spawn{new Spawn()};
    if (spawn->initWithTwoActions(action1, action2))
    {
        return spawn;
    }

    return nullptr;
}

bool Spawn::init(const Vector<FiniteTimeAction*>& arrayOfActions)
{
    auto count = arrayOfActions.size();

    if (count == 0)
        return false;

    if (count == 1)
        return initWithTwoActions(arrayOfActions.at(0), ExtraAction::create().get());

    // else count > 1
    cc::IntrusivePtr<FiniteTimeAction> prev{arrayOfActions.at(0)};
    for (int i = 1; i < count - 1; ++i)
    {
        prev = createWithTwoActions(prev, arrayOfActions.at(i));
    }

    return initWithTwoActions(prev, arrayOfActions.at(count - 1));
}

bool Spawn::initWithTwoActions(FiniteTimeAction* action1, FiniteTimeAction* action2)
{
    CCASSERT(action1 != nullptr, "action1 can't be nullptr!");
    CCASSERT(action2 != nullptr, "action2 can't be nullptr!");
    if (action1 == nullptr || action2 == nullptr)
    {
        log("Spawn::initWithTwoActions error: action is nullptr!");
        return false;
    }

    bool ret = false;

    float d1 = action1->getDuration();
    float d2 = action2->getDuration();

    if (ActionInterval::initWithDuration(MAX(d1, d2)))
    {
        _one = action1;
        _two = action2;
        _one->retain();
        _two->retain();

        if (d1 > d2)
        {
            _two->release();
            _two = Sequence::createWithTwoActions(action2, DelayTime::create(d1 - d2).get()).detach();
        }
        else if (d1 < d2)
        {
            _one->release();
            _one = Sequence::createWithTwoActions(action1, DelayTime::create(d2 - d1).get()).detach();
        }

        ret = true;
    }

    return ret;
}

cc::IntrusivePtr<Action> Spawn::clone() const
{
    // no copy constructor
    if (_one && _two)
        return Spawn::createWithTwoActions(cc::static_pointer_cast<FiniteTimeAction>(_one->clone()).get(), cc::static_pointer_cast<FiniteTimeAction>(_two->clone()).get());
    else
        return nullptr;
}

Spawn::Spawn() : _one(nullptr), _two(nullptr) {}

Spawn::~Spawn()
{
    CC_SAFE_RELEASE(_one);
    CC_SAFE_RELEASE(_two);
}

void Spawn::startWithTarget(Node* target)
{
    if (target == nullptr)
    {
        log("Spawn::startWithTarget error: target is nullptr!");
        return;
    }
    if (_one == nullptr || _two == nullptr)
    {
        log("Spawn::startWithTarget error: _one or _two is nullptr!");
        return;
    }

    ActionInterval::startWithTarget(target);
    _one->startWithTarget(target);
    _two->startWithTarget(target);
}

void Spawn::stop()
{
    if (_one)
        _one->stop();

    if (_two)
        _two->stop();

    ActionInterval::stop();
}

void Spawn::update(float time)
{
    if (_one)
    {
        if (!(sendUpdateEventToScript(time, _one)))
            _one->update(time);
    }
    if (_two)
    {
        if (!(sendUpdateEventToScript(time, _two)))
            _two->update(time);
    }
}

cc::IntrusivePtr<Action> Spawn::reverse() const
{
    if (_one && _two)
        return Spawn::createWithTwoActions(cc::static_pointer_cast<FiniteTimeAction>(_one->reverse()).get(), cc::static_pointer_cast<FiniteTimeAction>(_two->reverse()).get());

    return nullptr;
}

//
// RotateTo
//

cc::IntrusivePtr<RotateTo> RotateTo::create(float duration, float dstAngle)
{
    cc::IntrusivePtr rotateTo{new RotateTo()};
    if (rotateTo->initWithDuration(duration, dstAngle, dstAngle))
    {
        return rotateTo;
    }

    return nullptr;
}

cc::IntrusivePtr<RotateTo> RotateTo::create(float duration, float dstAngleX, float dstAngleY)
{
    cc::IntrusivePtr rotateTo{new RotateTo()};
    if (rotateTo->initWithDuration(duration, dstAngleX, dstAngleY))
    {
        return rotateTo;
    }

    return nullptr;
}

cc::IntrusivePtr<RotateTo> RotateTo::create(float duration, const Vec3& dstAngle3D)
{
    cc::IntrusivePtr rotateTo{new RotateTo()};
    if (rotateTo->initWithDuration(duration, dstAngle3D))
    {
        return rotateTo;
    }

    return nullptr;
}

RotateTo::RotateTo() : _is3D(false) {}

bool RotateTo::initWithDuration(float duration, float dstAngleX, float dstAngleY)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _dstAngle.x = dstAngleX;
        _dstAngle.y = dstAngleY;

        return true;
    }

    return false;
}

bool RotateTo::initWithDuration(float duration, const Vec3& dstAngle3D)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _dstAngle = dstAngle3D;
        _is3D     = true;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> RotateTo::clone() const
{
    // no copy constructor
    cc::IntrusivePtr a{new RotateTo()};
    if (_is3D)
        a->initWithDuration(_duration, _dstAngle);
    else
        a->initWithDuration(_duration, _dstAngle.x, _dstAngle.y);
    return a;
}

void RotateTo::calculateAngles(float& startAngle, float& diffAngle, float dstAngle)
{
    if (startAngle > 0)
    {
        startAngle = fmodf(startAngle, 360.0f);
    }
    else
    {
        startAngle = fmodf(startAngle, -360.0f);
    }

    diffAngle = dstAngle - startAngle;
    if (diffAngle > 180)
    {
        diffAngle -= 360;
    }
    if (diffAngle < -180)
    {
        diffAngle += 360;
    }
}

void RotateTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);

    if (_is3D)
    {
        _startAngle = _target->getRotation3D();
    }
    else
    {
        _startAngle.x = _target->getRotationSkewX();
        _startAngle.y = _target->getRotationSkewY();
    }

    calculateAngles(_startAngle.x, _diffAngle.x, _dstAngle.x);
    calculateAngles(_startAngle.y, _diffAngle.y, _dstAngle.y);
    calculateAngles(_startAngle.z, _diffAngle.z, _dstAngle.z);
}

void RotateTo::update(float time)
{
    if (_target)
    {
        if (_is3D)
        {
            _target->setRotation3D(Vec3(_startAngle.x + _diffAngle.x * time, _startAngle.y + _diffAngle.y * time,
                                        _startAngle.z + _diffAngle.z * time));
        }
        else
        {
#if CC_USE_PHYSICS
            if (_startAngle.x == _startAngle.y && _diffAngle.x == _diffAngle.y)
            {
                _target->setRotation(_startAngle.x + _diffAngle.x * time);
            }
            else
            {
                _target->setRotationSkewX(_startAngle.x + _diffAngle.x * time);
                _target->setRotationSkewY(_startAngle.y + _diffAngle.y * time);
            }
#else
            _target->setRotationSkewX(_startAngle.x + _diffAngle.x * time);
            _target->setRotationSkewY(_startAngle.y + _diffAngle.y * time);
#endif  // CC_USE_PHYSICS
        }
    }
}

cc::IntrusivePtr<Action> RotateTo::reverse() const
{
    CCASSERT(false, "RotateTo doesn't support the 'reverse' method");
    return nullptr;
}

//
// RotateBy
//

cc::IntrusivePtr<RotateBy> RotateBy::create(float duration, float deltaAngle)
{
    cc::IntrusivePtr rotateBy{new RotateBy()};
    if (rotateBy->initWithDuration(duration, deltaAngle))
    {
        return rotateBy;
    }

    return nullptr;
}

cc::IntrusivePtr<RotateBy> RotateBy::create(float duration, float deltaAngleX, float deltaAngleY)
{
    cc::IntrusivePtr rotateBy{new RotateBy()};
    if (rotateBy->initWithDuration(duration, deltaAngleX, deltaAngleY))
    {
        return rotateBy;
    }

    return nullptr;
}

cc::IntrusivePtr<RotateBy> RotateBy::create(float duration, const Vec3& deltaAngle3D)
{
    cc::IntrusivePtr rotateBy{new RotateBy()};
    if (rotateBy->initWithDuration(duration, deltaAngle3D))
    {
        return rotateBy;
    }

    return nullptr;
}

RotateBy::RotateBy() : _is3D(false) {}

bool RotateBy::initWithDuration(float duration, float deltaAngle)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _deltaAngle.x = _deltaAngle.y = deltaAngle;
        return true;
    }

    return false;
}

bool RotateBy::initWithDuration(float duration, float deltaAngleX, float deltaAngleY)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _deltaAngle.x = deltaAngleX;
        _deltaAngle.y = deltaAngleY;
        return true;
    }

    return false;
}

bool RotateBy::initWithDuration(float duration, const Vec3& deltaAngle3D)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _deltaAngle = deltaAngle3D;
        _is3D       = true;
        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> RotateBy::clone() const
{
    // no copy constructor
    cc::IntrusivePtr a{new RotateBy()};
    if (_is3D)
        a->initWithDuration(_duration, _deltaAngle);
    else
        a->initWithDuration(_duration, _deltaAngle.x, _deltaAngle.y);
    return a;
}

void RotateBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    if (_is3D)
    {
        _startAngle = target->getRotation3D();
    }
    else
    {
        _startAngle.x = target->getRotationSkewX();
        _startAngle.y = target->getRotationSkewY();
    }
}

void RotateBy::update(float time)
{
    // FIXME: shall I add % 360
    if (_target)
    {
        if (_is3D)
        {
            Vec3 v;
            v.x = _startAngle.x + _deltaAngle.x * time;
            v.y = _startAngle.y + _deltaAngle.y * time;
            v.z = _startAngle.z + _deltaAngle.z * time;
            _target->setRotation3D(v);
        }
        else
        {
#if CC_USE_PHYSICS
            if (_startAngle.x == _startAngle.y && _deltaAngle.x == _deltaAngle.y)
            {
                _target->setRotation(_startAngle.x + _deltaAngle.x * time);
            }
            else
            {
                _target->setRotationSkewX(_startAngle.x + _deltaAngle.x * time);
                _target->setRotationSkewY(_startAngle.y + _deltaAngle.y * time);
            }
#else
            _target->setRotationSkewX(_startAngle.x + _deltaAngle.x * time);
            _target->setRotationSkewY(_startAngle.y + _deltaAngle.y * time);
#endif  // CC_USE_PHYSICS
        }
    }
}

cc::IntrusivePtr<Action> RotateBy::reverse() const
{
    if (_is3D)
    {
        Vec3 v;
        v.x = -_deltaAngle.x;
        v.y = -_deltaAngle.y;
        v.z = -_deltaAngle.z;
        return RotateBy::create(_duration, v);
    }
    else
    {
        return RotateBy::create(_duration, -_deltaAngle.x, -_deltaAngle.y);
    }
}

//
// MoveBy
//

cc::IntrusivePtr<MoveBy> MoveBy::create(float duration, const Vec2& deltaPosition)
{
    return MoveBy::create(duration, Vec3(deltaPosition.x, deltaPosition.y, 0));
}

cc::IntrusivePtr<MoveBy> MoveBy::create(float duration, const Vec3& deltaPosition)
{
    cc::IntrusivePtr ret{new MoveBy()};

    if (ret->initWithDuration(duration, deltaPosition))
    {
        return ret;
    }

    return nullptr;
}

bool MoveBy::initWithDuration(float duration, const Vec2& deltaPosition)
{
    return MoveBy::initWithDuration(duration, Vec3(deltaPosition.x, deltaPosition.y, 0));
}

bool MoveBy::initWithDuration(float duration, const Vec3& deltaPosition)
{
    bool ret = false;

    if (ActionInterval::initWithDuration(duration))
    {
        _positionDelta = deltaPosition;
        _is3D          = true;
        ret            = true;
    }

    return ret;
}

cc::IntrusivePtr<Action> MoveBy::clone() const
{
    // no copy constructor
    return MoveBy::create(_duration, _positionDelta);
}

void MoveBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition3D();
}

cc::IntrusivePtr<Action> MoveBy::reverse() const
{
    return MoveBy::create(_duration, -_positionDelta);
}

void MoveBy::update(float t)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec3 currentPos = _target->getPosition3D();
        Vec3 diff       = currentPos - _previousPosition;
        _startPosition  = _startPosition + diff;
        Vec3 newPos     = _startPosition + (_positionDelta * t);
        _target->setPosition3D(newPos);
        _previousPosition = newPos;
#else
        _target->setPosition3D(_startPosition + _positionDelta * t);
#endif  // CC_ENABLE_STACKABLE_ACTIONS
    }
}

//
// MoveTo
//

cc::IntrusivePtr<MoveTo> MoveTo::create(float duration, const Vec2& position)
{
    return MoveTo::create(duration, Vec3(position.x, position.y, 0));
}

cc::IntrusivePtr<MoveTo> MoveTo::create(float duration, const Vec3& position)
{
    cc::IntrusivePtr ret{new MoveTo()};

    if (ret->initWithDuration(duration, position))
    {
        return ret;
    }

    return nullptr;
}

bool MoveTo::initWithDuration(float duration, const Vec2& position)
{
    return initWithDuration(duration, Vec3(position.x, position.y, 0));
}

bool MoveTo::initWithDuration(float duration, const Vec3& position)
{
    bool ret = false;

    if (ActionInterval::initWithDuration(duration))
    {
        _endPosition = position;
        ret          = true;
    }

    return ret;
}

cc::IntrusivePtr<Action> MoveTo::clone() const
{
    // no copy constructor
    return MoveTo::create(_duration, _endPosition);
}

void MoveTo::startWithTarget(Node* target)
{
    MoveBy::startWithTarget(target);
    _positionDelta = _endPosition - target->getPosition3D();
}

cc::IntrusivePtr<Action> MoveTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in MoveTo");
    return nullptr;
}

//
// SkewTo
//
cc::IntrusivePtr<SkewTo> SkewTo::create(float t, float sx, float sy)
{
    cc::IntrusivePtr skewTo{new SkewTo()};
    if (skewTo->initWithDuration(t, sx, sy))
    {
        return skewTo;
    }

    return nullptr;
}

bool SkewTo::initWithDuration(float t, float sx, float sy)
{
    bool bRet = false;

    if (ActionInterval::initWithDuration(t))
    {
        _endSkewX = sx;
        _endSkewY = sy;

        bRet = true;
    }

    return bRet;
}

cc::IntrusivePtr<Action> SkewTo::clone() const
{
    // no copy constructor
    return SkewTo::create(_duration, _endSkewX, _endSkewY);
}

cc::IntrusivePtr<Action> SkewTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in SkewTo");
    return nullptr;
}

void SkewTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);

    _startSkewX = target->getSkewX();

    if (_startSkewX > 0)
    {
        _startSkewX = fmodf(_startSkewX, 180.f);
    }
    else
    {
        _startSkewX = fmodf(_startSkewX, -180.f);
    }

    _deltaX = _endSkewX - _startSkewX;

    if (_deltaX > 180)
    {
        _deltaX -= 360;
    }
    if (_deltaX < -180)
    {
        _deltaX += 360;
    }

    _startSkewY = target->getSkewY();

    if (_startSkewY > 0)
    {
        _startSkewY = fmodf(_startSkewY, 360.f);
    }
    else
    {
        _startSkewY = fmodf(_startSkewY, -360.f);
    }

    _deltaY = _endSkewY - _startSkewY;

    if (_deltaY > 180)
    {
        _deltaY -= 360;
    }
    if (_deltaY < -180)
    {
        _deltaY += 360;
    }
}

void SkewTo::update(float t)
{
    _target->setSkewX(_startSkewX + _deltaX * t);
    _target->setSkewY(_startSkewY + _deltaY * t);
}

SkewTo::SkewTo()
    : _skewX(0.0)
    , _skewY(0.0)
    , _startSkewX(0.0)
    , _startSkewY(0.0)
    , _endSkewX(0.0)
    , _endSkewY(0.0)
    , _deltaX(0.0)
    , _deltaY(0.0)
{}

//
// SkewBy
//
cc::IntrusivePtr<SkewBy> SkewBy::create(float t, float sx, float sy)
{
    cc::IntrusivePtr skewBy{new SkewBy()};
    if (skewBy->initWithDuration(t, sx, sy))
    {
        return skewBy;
    }

    return nullptr;
}

cc::IntrusivePtr<Action> SkewBy::clone() const
{
    // no copy constructor
    return SkewBy::create(_duration, _skewX, _skewY);
}

bool SkewBy::initWithDuration(float t, float deltaSkewX, float deltaSkewY)
{
    bool ret = false;

    if (SkewTo::initWithDuration(t, deltaSkewX, deltaSkewY))
    {
        _skewX = deltaSkewX;
        _skewY = deltaSkewY;

        ret = true;
    }

    return ret;
}

void SkewBy::startWithTarget(Node* target)
{
    SkewTo::startWithTarget(target);
    _deltaX   = _skewX;
    _deltaY   = _skewY;
    _endSkewX = _startSkewX + _deltaX;
    _endSkewY = _startSkewY + _deltaY;
}

cc::IntrusivePtr<Action> SkewBy::reverse() const
{
    return SkewBy::create(_duration, -_skewX, -_skewY);
}

cc::IntrusivePtr<ResizeTo> ResizeTo::create(float duration, const Vec2& final_size)
{
    cc::IntrusivePtr ret{new ResizeTo()};

    if (!(ret->initWithDuration(duration, final_size)))
    {
        return nullptr;

    }

    return ret;
}

cc::IntrusivePtr<Action> ResizeTo::clone() const
{
    // no copy constructor
    cc::IntrusivePtr a{new ResizeTo()};
    a->initWithDuration(_duration, _finalSize);
    return a;
}

void ResizeTo::startWithTarget(cc::Node* target)
{
    ActionInterval::startWithTarget(target);
    _initialSize = target->getContentSize();
    _sizeDelta   = _finalSize - _initialSize;
}

void ResizeTo::update(float time)
{
    if (_target)
    {
        auto new_size = _initialSize + (_sizeDelta * time);
        _target->setContentSize(new_size);
    }
}

bool ResizeTo::initWithDuration(float duration, const Vec2& final_size)
{
    if (cc::ActionInterval::initWithDuration(duration))
    {
        _finalSize = final_size;
        return true;
    }

    return false;
}

//
// ResizeBy
//

cc::IntrusivePtr<ResizeBy> ResizeBy::create(float duration, const Vec2& deltaSize)
{
    cc::IntrusivePtr ret{new ResizeBy()};

    if (!(ret->initWithDuration(duration, deltaSize)))
    {
        return nullptr;

    }

    return ret;
}

cc::IntrusivePtr<Action> ResizeBy::clone() const
{
    // no copy constructor
    cc::IntrusivePtr a{new ResizeBy()};
    a->initWithDuration(_duration, _sizeDelta);
    return a;
}

void ResizeBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _previousSize = _startSize = target->getContentSize();
}

cc::IntrusivePtr<Action> ResizeBy::reverse() const
{
    Vec2 newSize(-_sizeDelta.width, -_sizeDelta.height);
    return ResizeBy::create(_duration, newSize);
}

void ResizeBy::update(float t)
{
    if (_target)
    {
        _target->setContentSize(_startSize + (_sizeDelta * t));
    }
}

bool ResizeBy::initWithDuration(float duration, const Vec2& deltaSize)
{
    bool ret = false;

    if (ActionInterval::initWithDuration(duration))
    {
        _sizeDelta = deltaSize;
        ret        = true;
    }

    return ret;
}

//
// JumpBy
//

cc::IntrusivePtr<JumpBy> JumpBy::create(float duration, const Vec2& position, float height, int jumps)
{
    cc::IntrusivePtr jumpBy{new JumpBy()};
    if (jumpBy->initWithDuration(duration, position, height, jumps))
    {
        return jumpBy;
    }

    return nullptr;
}

bool JumpBy::initWithDuration(float duration, const Vec2& position, float height, int jumps)
{
    CCASSERT(jumps >= 0, "Number of jumps must be >= 0");
    if (jumps < 0)
    {
        log("JumpBy::initWithDuration error: Number of jumps must be >= 0");
        return false;
    }

    if (ActionInterval::initWithDuration(duration) && jumps >= 0)
    {
        _delta  = position;
        _height = height;
        _jumps  = jumps;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> JumpBy::clone() const
{
    // no copy constructor
    return JumpBy::create(_duration, _delta, _height, _jumps);
}

void JumpBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _previousPos = _startPosition = target->getPosition();
}

void JumpBy::update(float t)
{
    // parabolic jump (since v0.8.2)
    if (_target)
    {
        float frac = fmodf(t * _jumps, 1.0f);
        float y    = _height * 4 * frac * (1 - frac);
        y += _delta.y * t;

        float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();

        Vec2 diff      = currentPos - _previousPos;
        _startPosition = diff + _startPosition;

        Vec2 newPos = _startPosition + Vec2(x, y);
        _target->setPosition(newPos);

        _previousPos = newPos;
#else
        _target->setPosition(_startPosition + Vec2(x, y));
#endif  // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

cc::IntrusivePtr<Action> JumpBy::reverse() const
{
    return JumpBy::create(_duration, Vec2(-_delta.x, -_delta.y), _height, _jumps);
}

//
// JumpTo
//

cc::IntrusivePtr<JumpTo> JumpTo::create(float duration, const Vec2& position, float height, int jumps)
{
    cc::IntrusivePtr jumpTo{new JumpTo()};
    if (jumpTo->initWithDuration(duration, position, height, jumps))
    {
        return jumpTo;
    }

    return nullptr;
}

bool JumpTo::initWithDuration(float duration, const Vec2& position, float height, int jumps)
{
    CCASSERT(jumps >= 0, "Number of jumps must be >= 0");
    if (jumps < 0)
    {
        log("JumpTo::initWithDuration error:Number of jumps must be >= 0");
        return false;
    }

    if (ActionInterval::initWithDuration(duration) && jumps >= 0)
    {
        _endPosition = position;
        _height      = height;
        _jumps       = jumps;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> JumpTo::clone() const
{
    // no copy constructor
    return JumpTo::create(_duration, _endPosition, _height, _jumps);
}

cc::IntrusivePtr<Action> JumpTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in JumpTo");
    return nullptr;
}

void JumpTo::startWithTarget(Node* target)
{
    JumpBy::startWithTarget(target);
    _delta.set(_endPosition.x - _startPosition.x, _endPosition.y - _startPosition.y);
}

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1
// Expands to ...
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
static inline float bezierat(float a, float b, float c, float d, float t)
{
    return (powf(1 - t, 3) * a + 3 * t * (powf(1 - t, 2)) * b + 3 * powf(t, 2) * (1 - t) * c + powf(t, 3) * d);
}

//
// BezierBy
//

cc::IntrusivePtr<BezierBy> BezierBy::create(float t, const ccBezierConfig& c)
{
    cc::IntrusivePtr bezierBy{new BezierBy()};
    if (bezierBy->initWithDuration(t, c))
    {
        return bezierBy;
    }

    return nullptr;
}

bool BezierBy::initWithDuration(float t, const ccBezierConfig& c)
{
    if (ActionInterval::initWithDuration(t))
    {
        _config = c;
        return true;
    }

    return false;
}

void BezierBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _previousPosition = _startPosition = target->getPosition();
}

cc::IntrusivePtr<Action> BezierBy::clone() const
{
    // no copy constructor
    return BezierBy::create(_duration, _config);
}

void BezierBy::update(float time)
{
    if (_target)
    {
        float xa = 0;
        float xb = _config.controlPoint_1.x;
        float xc = _config.controlPoint_2.x;
        float xd = _config.endPosition.x;

        float ya = 0;
        float yb = _config.controlPoint_1.y;
        float yc = _config.controlPoint_2.y;
        float yd = _config.endPosition.y;

        float x = bezierat(xa, xb, xc, xd, time);
        float y = bezierat(ya, yb, yc, yd, time);

#if CC_ENABLE_STACKABLE_ACTIONS
        Vec2 currentPos = _target->getPosition();
        Vec2 diff       = currentPos - _previousPosition;
        _startPosition  = _startPosition + diff;

        Vec2 newPos = _startPosition + Vec2(x, y);
        _target->setPosition(newPos);

        _previousPosition = newPos;
#else
        _target->setPosition(_startPosition + Vec2(x, y));
#endif  // !CC_ENABLE_STACKABLE_ACTIONS
    }
}

cc::IntrusivePtr<Action> BezierBy::reverse() const
{
    ccBezierConfig r;

    r.endPosition    = -_config.endPosition;
    r.controlPoint_1 = _config.controlPoint_2 + (-_config.endPosition);
    r.controlPoint_2 = _config.controlPoint_1 + (-_config.endPosition);

    cc::IntrusivePtr<BezierBy> action = BezierBy::create(_duration, r);
    return action;
}

//
// BezierTo
//

cc::IntrusivePtr<BezierTo> BezierTo::create(float t, const ccBezierConfig& c)
{
    cc::IntrusivePtr bezierTo{new BezierTo()};
    if (bezierTo->initWithDuration(t, c))
    {
        return bezierTo;
    }

    return nullptr;
}

bool BezierTo::initWithDuration(float t, const ccBezierConfig& c)
{
    if (ActionInterval::initWithDuration(t))
    {
        _toConfig = c;
        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> BezierTo::clone() const
{
    // no copy constructor
    return BezierTo::create(_duration, _toConfig);
}

void BezierTo::startWithTarget(Node* target)
{
    BezierBy::startWithTarget(target);
    _config.controlPoint_1 = _toConfig.controlPoint_1 - _startPosition;
    _config.controlPoint_2 = _toConfig.controlPoint_2 - _startPosition;
    _config.endPosition    = _toConfig.endPosition - _startPosition;
}

cc::IntrusivePtr<Action> BezierTo::reverse() const
{
    CCASSERT(false, "CCBezierTo doesn't support the 'reverse' method");
    return nullptr;
}

//
// ScaleTo
//
cc::IntrusivePtr<ScaleTo> ScaleTo::create(float duration, float s)
{
    cc::IntrusivePtr scaleTo{new ScaleTo()};
    if (scaleTo->initWithDuration(duration, s))
    {
        return scaleTo;
    }

    return nullptr;
}

cc::IntrusivePtr<ScaleTo> ScaleTo::create(float duration, float sx, float sy)
{
    cc::IntrusivePtr scaleTo{new ScaleTo()};
    if (scaleTo->initWithDuration(duration, sx, sy))
    {
        return scaleTo;
    }

    return nullptr;
}

cc::IntrusivePtr<ScaleTo> ScaleTo::create(float duration, float sx, float sy, float sz)
{
    cc::IntrusivePtr scaleTo{new ScaleTo()};
    if (scaleTo->initWithDuration(duration, sx, sy, sz))
    {
        return scaleTo;
    }

    return nullptr;
}

bool ScaleTo::initWithDuration(float duration, float s)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = s;
        _endScaleY = s;
        _endScaleZ = s;

        return true;
    }

    return false;
}

bool ScaleTo::initWithDuration(float duration, float sx, float sy)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = sx;
        _endScaleY = sy;
        _endScaleZ = 1.f;

        return true;
    }

    return false;
}

bool ScaleTo::initWithDuration(float duration, float sx, float sy, float sz)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _endScaleX = sx;
        _endScaleY = sy;
        _endScaleZ = sz;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> ScaleTo::clone() const
{
    // no copy constructor
    return ScaleTo::create(_duration, _endScaleX, _endScaleY, _endScaleZ);
}

cc::IntrusivePtr<Action> ScaleTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in ScaleTo");
    return nullptr;
}

void ScaleTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _startScaleX = target->getScaleX();
    _startScaleY = target->getScaleY();
    _startScaleZ = target->getScaleZ();
    _deltaX      = _endScaleX - _startScaleX;
    _deltaY      = _endScaleY - _startScaleY;
    _deltaZ      = _endScaleZ - _startScaleZ;
}

void ScaleTo::update(float time)
{
    if (_target)
    {
        _target->setScaleX(_startScaleX + _deltaX * time);
        _target->setScaleY(_startScaleY + _deltaY * time);
        _target->setScaleZ(_startScaleZ + _deltaZ * time);
    }
}

//
// ScaleBy
//

cc::IntrusivePtr<ScaleBy> ScaleBy::create(float duration, float s)
{
    cc::IntrusivePtr scaleBy{new ScaleBy()};
    if (scaleBy->initWithDuration(duration, s))
    {
        return scaleBy;
    }

    return nullptr;
}

cc::IntrusivePtr<ScaleBy> ScaleBy::create(float duration, float sx, float sy)
{
    cc::IntrusivePtr scaleBy{new ScaleBy()};
    if (scaleBy->initWithDuration(duration, sx, sy, 1.f))
    {
        return scaleBy;
    }

    return nullptr;
}

cc::IntrusivePtr<ScaleBy> ScaleBy::create(float duration, float sx, float sy, float sz)
{
    cc::IntrusivePtr scaleBy{new ScaleBy()};
    if (scaleBy->initWithDuration(duration, sx, sy, sz))
    {
        return scaleBy;
    }

    return nullptr;
}

cc::IntrusivePtr<Action> ScaleBy::clone() const
{
    // no copy constructor
    return ScaleBy::create(_duration, _endScaleX, _endScaleY, _endScaleZ);
}

void ScaleBy::startWithTarget(Node* target)
{
    ScaleTo::startWithTarget(target);
    _deltaX = _startScaleX * _endScaleX - _startScaleX;
    _deltaY = _startScaleY * _endScaleY - _startScaleY;
    _deltaZ = _startScaleZ * _endScaleZ - _startScaleZ;
}

cc::IntrusivePtr<Action> ScaleBy::reverse() const
{
    return ScaleBy::create(_duration, 1 / _endScaleX, 1 / _endScaleY, 1 / _endScaleZ);
}

//
// Blink
//

cc::IntrusivePtr<Blink> Blink::create(float duration, int blinks)
{
    cc::IntrusivePtr blink{new Blink()};
    if (blink->initWithDuration(duration, blinks))
    {
        return blink;
    }

    return nullptr;
}

bool Blink::initWithDuration(float duration, int blinks)
{
    CCASSERT(blinks >= 0, "blinks should be >= 0");
    if (blinks < 0)
    {
        log("Blink::initWithDuration error:blinks should be >= 0");
        return false;
    }

    if (ActionInterval::initWithDuration(duration) && blinks >= 0)
    {
        _times = blinks;
        return true;
    }

    return false;
}

void Blink::stop()
{
    if (nullptr != _target)
        _target->setVisible(_originalState);
    ActionInterval::stop();
}

void Blink::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _originalState = target->isVisible();
}

cc::IntrusivePtr<Action> Blink::clone() const
{
    // no copy constructor
    return Blink::create(_duration, _times);
}

void Blink::update(float time)
{
    if (_target && !isDone())
    {
        float slice = 1.0f / _times;
        float m     = fmodf(time, slice);
        _target->setVisible(m > slice / 2 ? true : false);
    }
}

cc::IntrusivePtr<Action> Blink::reverse() const
{
    return Blink::create(_duration, _times);
}

//
// FadeIn
//

cc::IntrusivePtr<FadeIn> FadeIn::create(float d)
{
    cc::IntrusivePtr action{new FadeIn()};
    if (action->initWithDuration(d, 255))
    {
        return action;
    }

    return nullptr;
}

cc::IntrusivePtr<Action> FadeIn::clone() const
{
    // no copy constructor
    return FadeIn::create(_duration);
}

void FadeIn::setReverseAction(cc::FadeTo* ac)
{
    _reverseAction = ac;
}

cc::IntrusivePtr<Action> FadeIn::reverse() const
{
    auto action = FadeOut::create(_duration);
    action->setReverseAction(const_cast<FadeIn*>(this));
    return action;
}

void FadeIn::startWithTarget(cc::Node* target)
{
    ActionInterval::startWithTarget(target);

    if (nullptr != _reverseAction)
        this->_toOpacity = this->_reverseAction->_fromOpacity;
    else
        _toOpacity = 255;

    if (target)
        _fromOpacity = target->getOpacity();
}

//
// FadeOut
//

cc::IntrusivePtr<FadeOut> FadeOut::create(float d)
{
    cc::IntrusivePtr action{new FadeOut()};
    if (action->initWithDuration(d, 0))
    {
        return action;
    }

    return nullptr;
}

cc::IntrusivePtr<Action> FadeOut::clone() const
{
    // no copy constructor
    return FadeOut::create(_duration);
}

void FadeOut::startWithTarget(cc::Node* target)
{
    ActionInterval::startWithTarget(target);

    if (nullptr != _reverseAction)
        _toOpacity = _reverseAction->_fromOpacity;
    else
        _toOpacity = 0;

    if (target)
        _fromOpacity = target->getOpacity();
}

void FadeOut::setReverseAction(cc::FadeTo* ac)
{
    _reverseAction = ac;
}

cc::IntrusivePtr<Action> FadeOut::reverse() const
{
    auto action = FadeIn::create(_duration);
    action->setReverseAction(const_cast<FadeOut*>(this));
    return action;
}

//
// FadeTo
//

cc::IntrusivePtr<FadeTo> FadeTo::create(float duration, uint8_t opacity)
{
    cc::IntrusivePtr fadeTo{new FadeTo()};
    if (fadeTo->initWithDuration(duration, opacity))
    {
        return fadeTo;
    }

    return nullptr;
}

bool FadeTo::initWithDuration(float duration, uint8_t opacity)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _toOpacity = opacity;
        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> FadeTo::clone() const
{
    // no copy constructor
    return FadeTo::create(_duration, _toOpacity);
}

cc::IntrusivePtr<Action> FadeTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in FadeTo");
    return nullptr;
}

void FadeTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);

    if (target)
    {
        _fromOpacity = target->getOpacity();
    }
}

void FadeTo::update(float time)
{
    if (_target)
    {
        _target->setOpacity((uint8_t)(_fromOpacity + (_toOpacity - _fromOpacity) * time));
    }
}

//
// TintTo
//
cc::IntrusivePtr<TintTo> TintTo::create(float duration, uint8_t red, uint8_t green, uint8_t blue)
{
    cc::IntrusivePtr tintTo{new TintTo()};
    if (tintTo->initWithDuration(duration, red, green, blue))
    {
        return tintTo;
    }

    return nullptr;
}

cc::IntrusivePtr<TintTo> TintTo::create(float duration, const Color3B& color)
{
    return create(duration, color.r, color.g, color.b);
}

bool TintTo::initWithDuration(float duration, uint8_t red, uint8_t green, uint8_t blue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _to = Color3B(red, green, blue);
        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> TintTo::clone() const
{
    // no copy constructor
    return TintTo::create(_duration, _to.r, _to.g, _to.b);
}

cc::IntrusivePtr<Action> TintTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in TintTo");
    return nullptr;
}

void TintTo::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    if (_target)
    {
        _from = _target->getColor();
    }
}

void TintTo::update(float time)
{
    if (_target)
    {
        _target->setColor(Color3B(uint8_t(_from.r + (_to.r - _from.r) * time),
                                  (uint8_t)(_from.g + (_to.g - _from.g) * time),
                                  (uint8_t)(_from.b + (_to.b - _from.b) * time)));
    }
}

//
// TintBy
//

cc::IntrusivePtr<TintBy> TintBy::create(float duration, int16_t deltaRed, int16_t deltaGreen, int16_t deltaBlue)
{
    cc::IntrusivePtr tintBy{new TintBy()};
    if (tintBy->initWithDuration(duration, deltaRed, deltaGreen, deltaBlue))
    {
        return tintBy;
    }

    return nullptr;
}

bool TintBy::initWithDuration(float duration, int16_t deltaRed, int16_t deltaGreen, int16_t deltaBlue)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _deltaR = deltaRed;
        _deltaG = deltaGreen;
        _deltaB = deltaBlue;

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> TintBy::clone() const
{
    // no copy constructor
    return TintBy::create(_duration, _deltaR, _deltaG, _deltaB);
}

void TintBy::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);

    if (target)
    {
        Color3B color = target->getColor();
        _fromR        = color.r;
        _fromG        = color.g;
        _fromB        = color.b;
    }
}

void TintBy::update(float time)
{
    if (_target)
    {
        _target->setColor(Color3B((uint8_t)(_fromR + _deltaR * time), (uint8_t)(_fromG + _deltaG * time),
                                  (uint8_t)(_fromB + _deltaB * time)));
    }
}

cc::IntrusivePtr<Action> TintBy::reverse() const
{
    return TintBy::create(_duration, -_deltaR, -_deltaG, -_deltaB);
}

//
// DelayTime
//
cc::IntrusivePtr<DelayTime> DelayTime::create(float d)
{
    cc::IntrusivePtr action{new DelayTime()};
    if (action->initWithDuration(d))
    {
        return action;
    }

    return nullptr;
}

cc::IntrusivePtr<Action> DelayTime::clone() const
{
    // no copy constructor
    return DelayTime::create(_duration);
}

void DelayTime::update(float /*time*/)
{
    return;
}

cc::IntrusivePtr<Action> DelayTime::reverse() const
{
    return DelayTime::create(_duration);
}

//
// ReverseTime
//

cc::IntrusivePtr<ReverseTime> ReverseTime::create(FiniteTimeAction* action)
{
    // casting to prevent warnings
    cc::IntrusivePtr reverseTime{new ReverseTime()};
    if (reverseTime->initWithAction(cc::static_pointer_cast<FiniteTimeAction>(action->clone()).get()))
    {
        return reverseTime;
    }

    return nullptr;
}

bool ReverseTime::initWithAction(FiniteTimeAction* action)
{
    CCASSERT(action != nullptr, "action can't be nullptr!");
    CCASSERT(action != _other, "action doesn't equal to _other!");
    if (action == nullptr || action == _other)
    {
        log("ReverseTime::initWithAction error: action is null or action equal to _other");
        return false;
    }

    if (ActionInterval::initWithDuration(action->getDuration()))
    {
        // Don't leak if action is reused
        CC_SAFE_RELEASE(_other);

        _other = action;
        action->retain();

        return true;
    }

    return false;
}

cc::IntrusivePtr<Action> ReverseTime::clone() const
{
    // no copy constructor
    return ReverseTime::create(cc::static_pointer_cast<FiniteTimeAction>(_other->clone()).get());
}

ReverseTime::ReverseTime() : _other(nullptr) {}

ReverseTime::~ReverseTime()
{
    CC_SAFE_RELEASE(_other);
}

void ReverseTime::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _other->startWithTarget(target);
}

void ReverseTime::stop()
{
    _other->stop();
    ActionInterval::stop();
}

void ReverseTime::update(float time)
{
    if (_other)
    {
        if (!(sendUpdateEventToScript(1 - time, _other)))
            _other->update(1 - time);
    }
}

cc::IntrusivePtr<Action> ReverseTime::reverse() const
{
    return _other->clone();
}

//
// Animate
//
cc::IntrusivePtr<Animate> Animate::create(Animation* animation)
{
    cc::IntrusivePtr animate{new Animate()};
    if (animate->initWithAnimation(animation))
    {
        return animate;
    }

    return nullptr;
}

Animate::Animate() {}

Animate::~Animate()
{
    CC_SAFE_RELEASE(_animation);
    CC_SAFE_RELEASE(_origFrame);
    CC_SAFE_DELETE(_splitTimes);
    CC_SAFE_RELEASE(_frameDisplayedEvent);
}

bool Animate::initWithAnimation(Animation* animation)
{
    CCASSERT(animation != nullptr, "Animate: argument Animation must be non-nullptr");
    if (animation == nullptr)
    {
        log("Animate::initWithAnimation: argument Animation must be non-nullptr");
        return false;
    }

    float singleDuration = animation->getDuration();

    if (ActionInterval::initWithDuration(singleDuration * animation->getLoops()))
    {
        _nextFrame = 0;
        setAnimation(animation);
        _origFrame     = nullptr;
        _executedLoops = 0;

        _splitTimes->reserve(animation->getFrames().size());

        float accumUnitsOfTime   = 0;
        float newUnitOfTimeValue = singleDuration / animation->getTotalDelayUnits();

        auto& frames = animation->getFrames();

        for (auto&& frame : frames)
        {
            float value = (accumUnitsOfTime * newUnitOfTimeValue) / singleDuration;
            accumUnitsOfTime += frame->getDelayUnits();
            _splitTimes->emplace_back(value);
        }
        return true;
    }
    return false;
}

void Animate::setAnimation(cc::Animation* animation)
{
    if (_animation != animation)
    {
        CC_SAFE_RETAIN(animation);
        CC_SAFE_RELEASE(_animation);
        _animation = animation;
    }
}

cc::IntrusivePtr<Action> Animate::clone() const
{
    // no copy constructor
    return Animate::create(_animation->clone().get());
}

void Animate::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    Sprite* sprite = static_cast<Sprite*>(target);

    CC_SAFE_RELEASE(_origFrame);

    if (_animation->getRestoreOriginalFrame())
    {
        _origFrame = sprite->getSpriteFrame().detach();
    }
    _nextFrame     = 0;
    _executedLoops = 0;
}

void Animate::stop()
{
    if (_animation->getRestoreOriginalFrame() && _target)
    {
        auto blend = static_cast<Sprite*>(_target)->getBlendFunc();
        static_cast<Sprite*>(_target)->setSpriteFrame(_origFrame);
        static_cast<Sprite*>(_target)->setBlendFunc(blend);
    }

    ActionInterval::stop();
}

void Animate::update(float t)
{
    // if t==1, ignore. Animation should finish with t==1
    if (t < 1.0f)
    {
        t *= _animation->getLoops();

        // new loop?  If so, reset frame counter
        unsigned int loopNumber = (unsigned int)t;
        if (loopNumber > _executedLoops)
        {
            _nextFrame = 0;
            _executedLoops++;
        }

        // new t for animations
        t = fmodf(t, 1.0f);
    }

    auto& frames                = _animation->getFrames();
    auto numberOfFrames         = frames.size();
    SpriteFrame* frameToDisplay = nullptr;

    for (int i = _nextFrame; i < numberOfFrames; i++)
    {
        float splitTime = _splitTimes->at(i);

        if (splitTime <= t)
        {
            auto blend            = static_cast<Sprite*>(_target)->getBlendFunc();
            _currFrameIndex       = i;
            AnimationFrame* frame = frames.at(_currFrameIndex);
            frameToDisplay        = frame->getSpriteFrame();
            static_cast<Sprite*>(_target)->setSpriteFrame(frameToDisplay);
            static_cast<Sprite*>(_target)->setBlendFunc(blend);

            const ValueMap& dict = frame->getUserInfo();
            if (!dict.empty())
            {
                if (_frameDisplayedEvent == nullptr)
                    _frameDisplayedEvent = cc::IntrusivePtr{new EventCustom(AnimationFrameDisplayedNotification)}.detach();

                _frameDisplayedEventInfo.target   = _target;
                _frameDisplayedEventInfo.userInfo = &dict;
                _frameDisplayedEvent->setUserData(&_frameDisplayedEventInfo);
                Director::getInstance()->getEventDispatcher()->dispatchEvent(_frameDisplayedEvent);
            }
            _nextFrame = i + 1;
        }
        // Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
        else
        {
            break;
        }
    }
}

cc::IntrusivePtr<Action> Animate::reverse() const
{
    auto& oldArray = _animation->getFrames();
    Vector<AnimationFrame*> newArray(oldArray.size());

    if (!oldArray.empty())
    {
        for (auto iter = oldArray.crbegin(), iterCrend = oldArray.crend(); iter != iterCrend; ++iter)
        {
            AnimationFrame* animFrame = *iter;
            if (!animFrame)
            {
                break;
            }

            newArray.pushBack(animFrame->clone());
        }
    }

    cc::IntrusivePtr<Animation> newAnim = Animation::create(newArray, _animation->getDelayPerUnit(), _animation->getLoops());
    newAnim->setRestoreOriginalFrame(_animation->getRestoreOriginalFrame());
    return Animate::create(newAnim);
}

// TargetedAction

TargetedAction::TargetedAction() : _action(nullptr), _forcedTarget(nullptr) {}

TargetedAction::~TargetedAction()
{
    CC_SAFE_RELEASE(_forcedTarget);
    CC_SAFE_RELEASE(_action);
}

cc::IntrusivePtr<TargetedAction> TargetedAction::create(Node* target, FiniteTimeAction* action)
{
    cc::IntrusivePtr p{new TargetedAction()};
    if (p->initWithTarget(target, action))
    {
        return p;
    }

    return nullptr;
}

bool TargetedAction::initWithTarget(Node* target, FiniteTimeAction* action)
{
    if (ActionInterval::initWithDuration(action->getDuration()))
    {
        CC_SAFE_RETAIN(target);
        _forcedTarget = target;
        CC_SAFE_RETAIN(action);
        _action = action;
        return true;
    }
    return false;
}

cc::IntrusivePtr<Action> TargetedAction::clone() const
{
    // no copy constructor
    // win32 : use the _other's copy object.
    return TargetedAction::create(_forcedTarget, cc::static_pointer_cast<FiniteTimeAction>(_action->clone()).get());
}

cc::IntrusivePtr<Action> TargetedAction::reverse() const
{
    // just reverse the internal action
    cc::IntrusivePtr a{new TargetedAction()};
    a->initWithTarget(_forcedTarget, cc::static_pointer_cast<FiniteTimeAction>(_action->reverse()).get());
    return a;
}

void TargetedAction::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _action->startWithTarget(_forcedTarget);
}

void TargetedAction::stop()
{
    _action->stop();
}

void TargetedAction::update(float time)
{
    if (!(sendUpdateEventToScript(time, _action)))
        _action->update(time);
}

void TargetedAction::setForcedTarget(Node* forcedTarget)
{
    if (_forcedTarget != forcedTarget)
    {
        CC_SAFE_RETAIN(forcedTarget);
        CC_SAFE_RELEASE(_forcedTarget);
        _forcedTarget = forcedTarget;
    }
}

// ActionFloat

cc::IntrusivePtr<ActionFloat> ActionFloat::create(float duration, float from, float to, ActionFloatCallback callback)
{
    cc::IntrusivePtr ref{new ActionFloat()};
    if (ref->initWithDuration(duration, from, to, callback))
    {
        return ref;
    }

    return nullptr;
}

bool ActionFloat::initWithDuration(float duration, float from, float to, ActionFloatCallback callback)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _from     = from;
        _to       = to;
        _callback = callback;
        return true;
    }
    return false;
}

cc::IntrusivePtr<Action> ActionFloat::clone() const
{
    return ActionFloat::create(_duration, _from, _to, _callback);
}

void ActionFloat::startWithTarget(Node* target)
{
    ActionInterval::startWithTarget(target);
    _delta = _to - _from;
}

void ActionFloat::update(float delta)
{
    float value = _to - _delta * (1 - delta);

    if (_callback)
    {
        // report back value to caller
        _callback(value);
    }
}

cc::IntrusivePtr<Action> ActionFloat::reverse() const
{
    return ActionFloat::create(_duration, _to, _from, _callback);
}

NS_CC_END
