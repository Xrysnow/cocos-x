/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
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
#include "base/CCDirector.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventDispatcher.h"
#include "platform/android/CCGLViewImpl-android.h"

#include <android/log.h>
#include <jni.h>

using namespace cocos2d;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        intptr_t idlong = id;
        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &idlong, &x, &y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        intptr_t idlong = id;
        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &idlong, &x, &y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t idlong[size];
        for(int i = 0; i < size; i++)
            idlong[i] = id[i];

        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesMove(size, idlong, x, y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        intptr_t idlong[size];
        for(int i = 0; i < size; i++)
            idlong[i] = id[i];

        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesCancel(size, idlong, x, y);
    }

    static std::unordered_map<int, cocos2d::EventKeyboard::KeyCode> g_keyCodeMap = {
        { 4, EventKeyboard::KeyCode::KEY_BACK }, // KEY_BACK == KEY_ESCAPE
        // 0-9
        { 7,  static_cast<EventKeyboard::KeyCode>(76) },
        { 8,  static_cast<EventKeyboard::KeyCode>(77) },
        { 9,  static_cast<EventKeyboard::KeyCode>(78) },
        { 10, static_cast<EventKeyboard::KeyCode>(79) },
        { 11, static_cast<EventKeyboard::KeyCode>(80) },
        { 12, static_cast<EventKeyboard::KeyCode>(81) },
        { 13, static_cast<EventKeyboard::KeyCode>(82) },
        { 14, static_cast<EventKeyboard::KeyCode>(83) },
        { 15, static_cast<EventKeyboard::KeyCode>(84) },
        { 16, static_cast<EventKeyboard::KeyCode>(85) },
        //
        //{ 17, KEYCODE_STAR },
        { 18, EventKeyboard::KeyCode::KEY_POUND },
        { 19, EventKeyboard::KeyCode::KEY_DPAD_UP },
        { 20, EventKeyboard::KeyCode::KEY_DPAD_DOWN },
        { 21, EventKeyboard::KeyCode::KEY_DPAD_LEFT },
        { 22, EventKeyboard::KeyCode::KEY_DPAD_RIGHT },
        { 23, EventKeyboard::KeyCode::KEY_DPAD_CENTER },
        //{ 24, KEYCODE_VOLUME_UP },
        //{ 25, KEYCODE_VOLUME_DOWN },
        //{ 26, KEYCODE_POWER },
        //{ 27, KEYCODE_CAMERA },
        //{ 28, KEYCODE_CLEAR },
        // a-z
        { 29, static_cast<EventKeyboard::KeyCode>(124) },
        { 30, static_cast<EventKeyboard::KeyCode>(125) },
        { 31, static_cast<EventKeyboard::KeyCode>(126) },
        { 32, static_cast<EventKeyboard::KeyCode>(127) },
        { 33, static_cast<EventKeyboard::KeyCode>(128) },
        { 34, static_cast<EventKeyboard::KeyCode>(129) },
        { 35, static_cast<EventKeyboard::KeyCode>(130) },
        { 36, static_cast<EventKeyboard::KeyCode>(131) },
        { 37, static_cast<EventKeyboard::KeyCode>(132) },
        { 38, static_cast<EventKeyboard::KeyCode>(133) },
        { 39, static_cast<EventKeyboard::KeyCode>(134) },
        { 40, static_cast<EventKeyboard::KeyCode>(135) },
        { 41, static_cast<EventKeyboard::KeyCode>(136) },
        { 42, static_cast<EventKeyboard::KeyCode>(137) },
        { 43, static_cast<EventKeyboard::KeyCode>(138) },
        { 44, static_cast<EventKeyboard::KeyCode>(139) },
        { 45, static_cast<EventKeyboard::KeyCode>(140) },
        { 46, static_cast<EventKeyboard::KeyCode>(141) },
        { 47, static_cast<EventKeyboard::KeyCode>(142) },
        { 48, static_cast<EventKeyboard::KeyCode>(143) },
        { 49, static_cast<EventKeyboard::KeyCode>(144) },
        { 50, static_cast<EventKeyboard::KeyCode>(145) },
        { 51, static_cast<EventKeyboard::KeyCode>(146) },
        { 52, static_cast<EventKeyboard::KeyCode>(147) },
        { 53, static_cast<EventKeyboard::KeyCode>(148) },
        { 54, static_cast<EventKeyboard::KeyCode>(149) },
        //
        { 55, EventKeyboard::KeyCode::KEY_COMMA },
        { 56, EventKeyboard::KeyCode::KEY_PERIOD },
        // special
        { 57, EventKeyboard::KeyCode::KEY_ALT },
        { 58, EventKeyboard::KeyCode::KEY_ALT },
        { 59, EventKeyboard::KeyCode::KEY_SHIFT },
        { 60, EventKeyboard::KeyCode::KEY_SHIFT },
        { 61, EventKeyboard::KeyCode::KEY_TAB },
        { 62, EventKeyboard::KeyCode::KEY_SPACE },
        //{ 63, KEYCODE_SYM },
        //{ 64, KEYCODE_EXPLORER },
        //{ 65, KEYCODE_ENVELOPE },
        { 66, EventKeyboard::KeyCode::KEY_ENTER },
        { 67, EventKeyboard::KeyCode::KEY_DELETE },
        { 68, EventKeyboard::KeyCode::KEY_GRAVE },
        { 69, EventKeyboard::KeyCode::KEY_MINUS },
        { 70, EventKeyboard::KeyCode::KEY_EQUAL },
        { 71, EventKeyboard::KeyCode::KEY_LEFT_BRACKET },
        { 72, EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
        { 73, EventKeyboard::KeyCode::KEY_BACK_SLASH },
        { 74, EventKeyboard::KeyCode::KEY_SEMICOLON },
        { 75, EventKeyboard::KeyCode::KEY_APOSTROPHE },
        { 76, EventKeyboard::KeyCode::KEY_SLASH },
        { 77, EventKeyboard::KeyCode::KEY_AT },
        //{ 78, KEYCODE_NUM },
        //{ 79, KEYCODE_HEADSETHOOK },
        //{ 80, KEYCODE_FOCUS },
        { 81, EventKeyboard::KeyCode::KEY_PLUS },
        { 82, EventKeyboard::KeyCode::KEY_MENU },
        //{ 83, KEYCODE_NOTIFICATION },
        { 84, EventKeyboard::KeyCode::KEY_SEARCH },
        //{ 85, KEYCODE_MEDIA_PLAY_PAUSE },
        //{ 86, KEYCODE_MEDIA_STOP },
        //{ 87, KEYCODE_MEDIA_NEXT },
        //{ 88, KEYCODE_MEDIA_PREVIOUS },
        //{ 89, KEYCODE_MEDIA_REWIND },
        //{ 90, KEYCODE_MEDIA_FAST_FORWARD },
        //{ 91, KEYCODE_MUTE },
        { 92, EventKeyboard::KeyCode::KEY_PG_UP },
        { 93, EventKeyboard::KeyCode::KEY_PG_DOWN },
        //{ 94, KEYCODE_PICTSYMBOLS },
        //{ 95, KEYCODE_SWITCH_CHARSET },
        //{ 96, KEYCODE_BUTTON_A },
        //{ 97, KEYCODE_BUTTON_B },
        //{ 98, KEYCODE_BUTTON_C },
        //{ 99, KEYCODE_BUTTON_X },
        //{ 100, KEYCODE_BUTTON_Y },
        //{ 101, KEYCODE_BUTTON_Z },
        //{ 102, KEYCODE_BUTTON_L1 },
        //{ 103, KEYCODE_BUTTON_R1 },
        //{ 104, KEYCODE_BUTTON_L2 },
        //{ 105, KEYCODE_BUTTON_R2 },
        //{ 106, KEYCODE_BUTTON_THUMBL },
        //{ 107, KEYCODE_BUTTON_THUMBR },
        //{ 108, KEYCODE_BUTTON_START },
        //{ 109, KEYCODE_BUTTON_SELECT },
        //{ 110, KEYCODE_BUTTON_MODE },
        { 111, EventKeyboard::KeyCode::KEY_ESCAPE },
        //{ 112, KEYCODE_FORWARD_DEL },
        { 113, EventKeyboard::KeyCode::KEY_LEFT_CTRL },
        { 114, EventKeyboard::KeyCode::KEY_RIGHT_CTRL },
        { 115, EventKeyboard::KeyCode::KEY_CAPS_LOCK },
        { 116, EventKeyboard::KeyCode::KEY_SCROLL_LOCK },
        //{ 117, KEYCODE_META_LEFT },
        //{ 118, KEYCODE_META_RIGHT },
        //{ 119, KEYCODE_FUNCTION },
        //{ 120, KEYCODE_SYSRQ },
        { 121, EventKeyboard::KeyCode::KEY_BREAK },
        //{ 122, KEYCODE_MOVE_HOME },
        //{ 123, KEYCODE_MOVE_END },
        { 124, EventKeyboard::KeyCode::KEY_INSERT },
        //{ 125, KEYCODE_FORWARD },
        { 126, EventKeyboard::KeyCode::KEY_PLAY },
        //{ 127, KEYCODE_MEDIA_PAUSE },
        //{ 128, KEYCODE_MEDIA_CLOSE },
        //{ 129, KEYCODE_MEDIA_EJECT },
        //{ 130, KEYCODE_MEDIA_RECORD },
        { 131, EventKeyboard::KeyCode::KEY_F1 },
        { 132, EventKeyboard::KeyCode::KEY_F2 },
        { 133, EventKeyboard::KeyCode::KEY_F3 },
        { 134, EventKeyboard::KeyCode::KEY_F4 },
        { 135, EventKeyboard::KeyCode::KEY_F5 },
        { 136, EventKeyboard::KeyCode::KEY_F6 },
        { 137, EventKeyboard::KeyCode::KEY_F7 },
        { 138, EventKeyboard::KeyCode::KEY_F8 },
        { 139, EventKeyboard::KeyCode::KEY_F9 },
        { 140, EventKeyboard::KeyCode::KEY_F10 },
        { 141, EventKeyboard::KeyCode::KEY_F11 },
        { 142, EventKeyboard::KeyCode::KEY_F12 },
        { 143, EventKeyboard::KeyCode::KEY_NUM_LOCK },
        { 144, EventKeyboard::KeyCode::KEY_0 },
        { 145, EventKeyboard::KeyCode::KEY_1 },
        { 146, EventKeyboard::KeyCode::KEY_2 },
        { 147, EventKeyboard::KeyCode::KEY_3 },
        { 148, EventKeyboard::KeyCode::KEY_4 },
        { 149, EventKeyboard::KeyCode::KEY_5 },
        { 150, EventKeyboard::KeyCode::KEY_6 },
        { 151, EventKeyboard::KeyCode::KEY_7 },
        { 152, EventKeyboard::KeyCode::KEY_8 },
        { 153, EventKeyboard::KeyCode::KEY_9 },
        { 154, EventKeyboard::KeyCode::KEY_KP_DIVIDE },
        { 155, EventKeyboard::KeyCode::KEY_KP_MULTIPLY },
        { 156, EventKeyboard::KeyCode::KEY_KP_MINUS },
        { 157, EventKeyboard::KeyCode::KEY_KP_PLUS },
        //{ 158, KEYCODE_NUMPAD_DOT },
        //{ 159, KEYCODE_NUMPAD_COMMA },
        { 160, EventKeyboard::KeyCode::KEY_KP_ENTER },
        //{ 161, KEYCODE_NUMPAD_EQUALS },
        //{ 162, KEYCODE_NUMPAD_LEFT_PAREN },
        //{ 163, KEYCODE_NUMPAD_RIGHT_PAREN },

        //{ 188, KEYCODE_BUTTON_1 },
        //{ 189, KEYCODE_BUTTON_2 },
        //{ 190, KEYCODE_BUTTON_3 },
        //{ 191, KEYCODE_BUTTON_4 },
        //{ 192, KEYCODE_BUTTON_5 },
        //{ 193, KEYCODE_BUTTON_6 },
        //{ 194, KEYCODE_BUTTON_7 },
        //{ 195, KEYCODE_BUTTON_8 },
        //{ 196, KEYCODE_BUTTON_9 },
        //{ 197, KEYCODE_BUTTON_10 },
        //{ 198, KEYCODE_BUTTON_11 },
        //{ 199, KEYCODE_BUTTON_12 },
        //{ 200, KEYCODE_BUTTON_13 },
        //{ 201, KEYCODE_BUTTON_14 },
        //{ 202, KEYCODE_BUTTON_15 },
        //{ 203, KEYCODE_BUTTON_16 },

        //{ 260, KEYCODE_NAVIGATE_PREVIOUS },
        //{ 261, KEYCODE_NAVIGATE_NEXT },
        //{ 262, KEYCODE_NAVIGATE_IN },
        //{ 263, KEYCODE_NAVIGATE_OUT },
        //{ 264, KEYCODE_STEM_PRIMARY },
        //{ 265, KEYCODE_STEM_1 },
        //{ 266, KEYCODE_STEM_2 },
        //{ 267, KEYCODE_STEM_3 },
        //{ 268, KEYCODE_DPAD_UP_LEFT },
        //{ 269, KEYCODE_DPAD_DOWN_LEFT },
        //{ 270, KEYCODE_DPAD_UP_RIGHT },
        //{ 271, KEYCODE_DPAD_DOWN_RIGHT },
    };
    
    JNIEXPORT jboolean JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyEvent(JNIEnv * env, jobject thiz, jint keyCode, jboolean isPressed) {        
        auto iterKeyCode = g_keyCodeMap.find(keyCode);
        if (iterKeyCode == g_keyCodeMap.end()) {
            return JNI_FALSE;
        }
        
        cocos2d::EventKeyboard::KeyCode cocos2dKey = g_keyCodeMap.at(keyCode);
        cocos2d::EventKeyboard event(cocos2dKey, isPressed);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        return JNI_TRUE;
        
    }}
