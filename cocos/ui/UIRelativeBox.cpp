/****************************************************************************
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

#include "ui/UIRelativeBox.h"

NS_CC_BEGIN

namespace ui
{

RelativeBox::RelativeBox() {}

RelativeBox::~RelativeBox() {}

cc::IntrusivePtr<RelativeBox> RelativeBox::create()
{
    cc::IntrusivePtr<RelativeBox> widget{new RelativeBox()};
    if (widget->init())
    {
        return widget;
    }
    return nullptr;
}

cc::IntrusivePtr<RelativeBox> RelativeBox::create(const Vec2& size)
{
    cc::IntrusivePtr<RelativeBox> widget{new RelativeBox()};
    if (widget->initWithSize(size))
    {
        return widget;
    }
    return nullptr;
}

bool RelativeBox::init()
{
    if (Layout::init())
    {
        setLayoutType(Layout::Type::RELATIVE);
        return true;
    }
    return false;
}

bool RelativeBox::initWithSize(const Vec2& size)
{
    if (init())
    {
        setContentSize(size);
        return true;
    }
    return false;
}

}  // namespace ui

NS_CC_END
