/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
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

#include "base/IMEDispatcher.h"
#include "base/Director.h"
#include "base/EventType.h"
#include "base/EventCustom.h"
#include "base/EventDispatcher.h"
#include "platform/Application.h"
#include "platform/FileUtils.h"
#include <jni.h>

#include "base/ccUTF8.h"

using namespace cc;

extern "C" {

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeRender(JNIEnv*, jclass)
{
    cc::Director::getInstance()->mainLoop();
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeOnPause(JNIEnv*, jclass)
{
    if (Director::getInstance()->getOpenGLView())
    {
        Application::getInstance()->applicationDidEnterBackground();
        cc::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
        cc::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
    }
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeOnResume(JNIEnv*, jclass)
{
    if (Director::getInstance()->getOpenGLView())
    {
        Application::getInstance()->applicationWillEnterForeground();
        cc::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        cc::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
    }
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeInsertText(JNIEnv* env, jclass, jstring text)
{
    std::string strValue = cc::StringUtils::getStringUTFCharsJNI(env, text);
    const char* pszText  = strValue.c_str();
    cc::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeDeleteBackward(JNIEnv*, jclass, jint numChars)
{
    // Java counts Unicode code points, matching the native delegates' deletion unit.
    for (jint i = 0; i < numChars; ++i)
        cc::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
}

JNIEXPORT void JNICALL Java_org_cocos_lib_CocosRenderer_nativeIMEClosed(JNIEnv*, jclass)
{
    cc::IMEKeyboardNotificationInfo info{};
    cc::IMEDispatcher::sharedDispatcher()->dispatchKeyboardDidHide(info);
}

JNIEXPORT jstring JNICALL Java_org_cocos_lib_CocosRenderer_nativeGetContentText(JNIEnv* env, jclass)
{
    auto pszText = cc::IMEDispatcher::sharedDispatcher()->getContentText();
    return cc::StringUtils::newStringUTFJNI(env, pszText);
}
}
