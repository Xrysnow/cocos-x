/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "ActionTimeline/CCTimeLine.h"
#include "ActionTimeline/CCActionTimeline.h"
#include "base/CCRefPtr.h"

USING_NS_CC;

NS_TIMELINE_BEGIN

Timeline* Timeline::create()
{
    Timeline* ret = new Timeline();
    ret->autorelease();
    return ret;
}

Timeline::Timeline()
    : _currentKeyFrame(nullptr)
    , _currentKeyFrameIndex(0)
    , _fromIndex(0)
    , _toIndex(0)
    , _betweenDuration(0)
    , _actionTag(0)
    , _ActionTimeline(nullptr)
    , _node(nullptr)
{}

Timeline::~Timeline()
{
    for (auto frame : _frames)
    {
        if (frame->getTimeline() == this)
            frame->setTimeline(nullptr);
    }
}

void Timeline::gotoFrame(int frameIndex)
{
    if (_frames.size() == 0)
        return;

    RefPtr<Timeline> keepTimeline(this);
    RefPtr<ActionTimeline> keepAction(_ActionTimeline);
    RefPtr<Node> keepNode(_node);
    const auto version = ++_stateVersion;
    binarySearchKeyFrame(frameIndex);
    if (version == _stateVersion)
        apply(frameIndex);
}

void Timeline::stepToFrame(int frameIndex)
{
    if (_frames.size() == 0)
        return;

    RefPtr<Timeline> keepTimeline(this);
    RefPtr<ActionTimeline> keepAction(_ActionTimeline);
    RefPtr<Node> keepNode(_node);
    const auto version = ++_stateVersion;
    if (_needsKeyFrameSearch)
        binarySearchKeyFrame(frameIndex);
    else
        updateCurrentKeyFrame(frameIndex);
    if (version == _stateVersion)
        apply(frameIndex);
}

Timeline* Timeline::clone()
{
    Timeline* timeline   = Timeline::create();
    timeline->_actionTag = _actionTag;

    for (auto&& frame : _frames)
    {
        Frame* newFrame = frame->clone();
        timeline->addFrame(newFrame);
    }

    return timeline;
}

void Timeline::addFrame(Frame* frame)
{
    _frames.pushBack(frame);
    frame->setTimeline(this);
    if (_node)
        frame->setNode(_node);
    invalidateCurrentKeyFrame();
}

void Timeline::insertFrame(Frame* frame, int index)
{
    _frames.insert(index, frame);
    frame->setTimeline(this);
    if (_node)
        frame->setNode(_node);
    invalidateCurrentKeyFrame();
}

void Timeline::removeFrame(Frame* frame)
{
    if (!_frames.contains(frame))
        return;
    // Clear back-pointers while the owning vector still retains the frame.
    if (frame->getTimeline() == this)
        frame->setTimeline(nullptr);
    invalidateCurrentKeyFrame();
    _frames.eraseObject(frame);
}

void Timeline::invalidateCurrentKeyFrame()
{
    ++_stateVersion;
    _needsKeyFrameSearch = _needsKeyFrameSearch || _currentKeyFrame != nullptr;
    _currentKeyFrame = nullptr;
    _currentKeyFrameIndex = _fromIndex = _toIndex = _betweenDuration = 0;
}

void Timeline::setActionTimeline(ActionTimeline* action)
{
    ++_stateVersion;
    _ActionTimeline = action;
    if (!action)
        setNode(nullptr);
}

void Timeline::setNode(Node* node)
{
    ++_stateVersion;
    _node = node;
    for (auto&& frame : _frames)
    {
        frame->setNode(node);
    }
}

Node* Timeline::getNode() const
{
    return _node;
}

void Timeline::apply(unsigned int frameIndex)
{
    RefPtr<Frame> frame(_currentKeyFrame);
    RefPtr<Node> keepNode(frame ? frame->getNode() : nullptr);
    if (frame)
    {
        float currentPercent =
            _betweenDuration == 0 ? 0 : (frameIndex - _currentKeyFrameIndex) / (float)_betweenDuration;
        frame->apply(currentPercent);
    }
}

void Timeline::binarySearchKeyFrame(unsigned int frameIndex)
{
    _needsKeyFrameSearch = false;
    Frame* from = nullptr;
    Frame* to   = nullptr;

    long length         = _frames.size();
    bool needEnterFrame = false;

    do
    {
        if (frameIndex < _frames.at(0)->getFrameIndex())
        {
            if (_currentKeyFrameIndex >= _frames.at(0)->getFrameIndex())
                needEnterFrame = true;

            _fromIndex = 0;
            _toIndex   = 0;

            from = to             = _frames.at(0);
            _currentKeyFrameIndex = 0;
            _betweenDuration      = _frames.at(0)->getFrameIndex();
            break;
        }
        else if (frameIndex >= _frames.at(length - 1)->getFrameIndex())
        {
            _fromIndex = (int)(length - 1);
            _toIndex   = 0;

            from = to = _frames.at(length - 1);
            if (from->isEnterWhenPassed())
                needEnterFrame = true;

            _currentKeyFrameIndex = _frames.at(length - 1)->getFrameIndex();
            _betweenDuration      = 0;
            break;
        }

        long target = -1;
        long low = 0, high = length - 1, mid = 0;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (frameIndex >= _frames.at(mid)->getFrameIndex() && frameIndex < _frames.at(mid + 1)->getFrameIndex())
            {
                target = mid;
                break;
            }
            if (_frames.at(mid)->getFrameIndex() > frameIndex)
                high = mid - 1;
            else
                low = mid + 1;
        }

        _fromIndex = (int)target;

        if (length > 1)
            _toIndex = (int)(target + 1);
        else
            _toIndex = (int)target;

        from = _frames.at(_fromIndex);
        to   = _frames.at(_toIndex);

        if (target == 0 && _currentKeyFrameIndex < from->getFrameIndex())
            needEnterFrame = true;

        _currentKeyFrameIndex = from->getFrameIndex();
        _betweenDuration      = to->getFrameIndex() - from->getFrameIndex();
    } while (0);

    if (needEnterFrame || _currentKeyFrame != from)
    {
        _currentKeyFrame = from;
        RefPtr<Frame> keepFrom(from);
        RefPtr<Frame> keepTo(to);
        _currentKeyFrame->onEnter(to, frameIndex);
    }
}

void Timeline::updateCurrentKeyFrame(unsigned int frameIndex)
{
    const auto version = _stateVersion;
    //! If play to current frame's front or back, then find current frame again
    if (frameIndex < _currentKeyFrameIndex || frameIndex >= _currentKeyFrameIndex + _betweenDuration)
    {
        Frame* from = nullptr;
        Frame* to   = nullptr;

        do
        {
            long length = _frames.size();

            if (frameIndex < _frames.at(0)->getFrameIndex())
            {
                from = to             = _frames.at(0);
                _currentKeyFrameIndex = 0;
                _betweenDuration      = _frames.at(0)->getFrameIndex();
                break;
            }
            else if (frameIndex >= _frames.at(length - 1)->getFrameIndex())
            {
                unsigned int lastFrameIndex = _frames.at(length - 1)->getFrameIndex();
                if (_currentKeyFrameIndex >= lastFrameIndex)
                    return;
                frameIndex = lastFrameIndex;
            }

            do
            {
                _fromIndex            = _toIndex;
                from                  = _frames.at(_fromIndex);
                _currentKeyFrameIndex = from->getFrameIndex();

                _toIndex = _fromIndex + 1;
                if ((ssize_t)_toIndex >= length)
                {
                    _toIndex = 0;
                }

                to = _frames.at(_toIndex);

                if (frameIndex == from->getFrameIndex())
                    break;
                if (frameIndex > from->getFrameIndex() && frameIndex < to->getFrameIndex())
                    break;
                if (from->isEnterWhenPassed())
                {
                    RefPtr<Frame> keepFrom(from);
                    RefPtr<Frame> keepTo(to);
                    from->onEnter(to, from->getFrameIndex());
                    if (version != _stateVersion)
                        return;
                }
            } while (true);

            if (_fromIndex == length - 1)
                to = from;

            _betweenDuration = to->getFrameIndex() - from->getFrameIndex();

        } while (0);

        _currentKeyFrame = from;
        RefPtr<Frame> keepFrom(from);
        RefPtr<Frame> keepTo(to);
        _currentKeyFrame->onEnter(to, frameIndex);
    }
}

NS_TIMELINE_END
