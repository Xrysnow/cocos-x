/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2015 hanxi
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

#ifndef __UIEDITBOXIMPLLINUX_H__
#define __UIEDITBOXIMPLLINUX_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#    include "ui/UIEditBox/UIEditBoxImpl-common.h"

NS_CC_BEGIN

class Label;

namespace ui
{

class EditBox;

class EditBoxImplLinux : public EditBoxImplCommon
{
public:
    /**
     * @js NA
     */
    EditBoxImplLinux(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplLinux();

    virtual bool isEditing() override;
    virtual void createNativeControl(const Rect& frame) override{};
    virtual void setNativeFont(const char* pFontName, int fontSize) override{};
    virtual void setNativeFontColor(const Color4B& color) override{};
    virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) override{};
    virtual void setNativePlaceholderFontColor(const Color4B& color) override{};
    virtual void setNativeInputMode(EditBox::InputMode inputMode) override{};
    virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) override{};
    virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) override{};
    virtual void setNativeTextHorizontalAlignment(cocos2d::TextHAlignment alignment){};
    virtual void setNativeText(const char* pText) override{};
    virtual void setNativePlaceHolder(const char* pText) override{};
    virtual void setNativeVisible(bool visible) override{};
    virtual void updateNativeFrame(const Rect& rect) override{};
    virtual const char* getNativeDefaultFontName() override{};
    virtual void nativeOpenKeyboard() override;
    virtual void nativeCloseKeyboard() override{};
    virtual void setNativeMaxLength(int maxLength) override{};

private:
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) override {}
};

}  // namespace ui

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */

#endif /* __UIEDITBOXIMPLLINUX_H__ */
