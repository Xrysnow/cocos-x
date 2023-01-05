/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2021 Bytedance Inc.

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
#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include "platform/CCPlatformMacros.h"
#include "math/Vec3.h"
#include "jni/jni.hpp"

namespace jni
{
template <>
struct TypeSignature<bool>
{
    constexpr auto operator()() const { return TypeSignature<jboolean>{}(); }
};
template <>
struct TypeSignature<const char*>
{
    constexpr auto operator()() const { return TypeSignature<jni::String>{}(); }
};
template <>
struct TypeSignature<std::string_view>
{
    constexpr auto operator()() const { return TypeSignature<jni::String>{}(); }
};
template <>
struct TypeSignature<std::string>
{
    constexpr auto operator()() const { return TypeSignature<jni::String>{}(); }
};
}  // namespace jni

NS_CC_BEGIN

typedef struct JniMethodInfo_
{
    JNIEnv* env;
    jclass classID;
    jmethodID methodID;
} JniMethodInfo;

class CC_DLL JniHelper
{
public:
    typedef std::unordered_map<JNIEnv*, std::vector<jobject>> LocalRefMapType;

    static void setJavaVM(JavaVM* javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static jobject getActivity();

    static bool setClassLoaderFrom(jobject activityInstance);
    static bool getStaticMethodInfo(JniMethodInfo& methodinfo,
                                    const char* className,
                                    const char* methodName,
                                    const char* paramCode);
    static bool getMethodInfo(JniMethodInfo& methodinfo,
                              const char* className,
                              const char* methodName,
                              const char* paramCode);

    static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;
    static std::function<void()> classloaderCallback;

    /**
    @brief Call of Java static void method
    @if no such method will log error
    */
    template <typename... Ts>
    static void callStaticVoidMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<void(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            t.env->CallStaticVoidMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
    }

    /**
    @brief Call of Java static boolean method
    @return value from Java static boolean method if there are proper JniMethodInfo; otherwise false.
    */
    template <typename... Ts>
    static bool callStaticBooleanMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        jboolean jret = JNI_FALSE;
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jboolean(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            jret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return (jret == JNI_TRUE);
    }

    /**
    @brief Call of Java static int method
    @return value from Java static int method if there are proper JniMethodInfo; otherwise 0.
    */
    template <typename... Ts>
    static int callStaticIntMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        jint ret = 0;
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jint(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            ret = t.env->CallStaticIntMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    /**
    @brief Call of Java static float method
    @return value from Java static float method if there are proper JniMethodInfo; otherwise 0.
    */
    template <typename... Ts>
    static float callStaticFloatMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        jfloat ret = 0.0;
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jfloat(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    /**
    @brief Call of Java static float* method
    @return address of JniMethodInfo if there are proper JniMethodInfo; otherwise nullptr.
    */
    template <typename... Ts>
    static float* callStaticFloatArrayMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        static float ret[32];
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jni::Array<jfloat>(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            jfloatArray array =
                (jfloatArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len <= 32)
            {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                if (elems)
                {
                    memcpy(ret, elems, sizeof(float) * len);
                    t.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
            return &ret[0];
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return nullptr;
    }

    /**
    @brief Call of Java static int* method
    @return address of JniMethodInfo if there are proper JniMethodInfo; otherwise nullptr.
    */
    template <typename... Ts>
    static int* callStaticIntArrayMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        static int ret[32];
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jni::Array<jint>(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            jintArray array =
                (jintArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len <= 32)
            {
                jint* elems = t.env->GetIntArrayElements(array, 0);
                if (elems)
                {
                    memcpy(ret, elems, sizeof(int) * len);
                    t.env->ReleaseIntArrayElements(array, elems, 0);
                };
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
            return &ret[0];
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return nullptr;
    }

    /**
    @brief Call of Java static Vec3 method
    @return JniMethodInfo of Vec3 type if there are proper JniMethodInfo; otherwise Vec3(0, 0, 0).
    */
    template <typename... Ts>
    static Vec3 callStaticVec3Method(const char* className, const char* methodName, Ts&&... xs)
    {
        Vec3 ret;
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jni::Array<jfloat>(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            jfloatArray array =
                (jfloatArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len == 3)
            {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                ret.x         = elems[0];
                ret.y         = elems[1];
                ret.z         = elems[2];
                t.env->ReleaseFloatArrayElements(array, elems, 0);
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    /**
    @brief Call of Java static double method
    @return value from Java static double method if there are proper JniMethodInfo; otherwise 0.
    */
    template <typename... Ts>
    static double callStaticDoubleMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        jdouble ret = 0.0;
        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jdouble(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    /**
    @brief Call of Java static string method
    @return JniMethodInfo of string type if there are proper JniMethodInfo; otherwise empty string.
    */
    template <typename... Ts>
    static std::string callStaticStringMethod(const char* className, const char* methodName, Ts&&... xs)
    {
        std::string ret;

        cocos2d::JniMethodInfo t;
        const char* signature = jni::TypeSignature<jni::String(std::decay_t<Ts>...)>{}();
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature))
        {
            LocalRefMapType localRefs;
            jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            ret          = cocos2d::JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo& methodinfo,
                                                 const char* className,
                                                 const char* methodName,
                                                 const char* paramCode);

    static JavaVM* _psJavaVM;

    static jobject _activity;

    static jstring convert(LocalRefMapType& localRefs, cocos2d::JniMethodInfo& t, const char* x);

    static jstring convert(LocalRefMapType& localRefs, cocos2d::JniMethodInfo& t, std::string_view x);

    static jstring convert(LocalRefMapType& localRefs, cocos2d::JniMethodInfo& t, const std::string& x);

    inline static jint convert(LocalRefMapType&, cocos2d::JniMethodInfo&, int32_t value)
    {
        return static_cast<jint>(value);
    }
    inline static jlong convert(LocalRefMapType&, cocos2d::JniMethodInfo&, int64_t value)
    {
        return static_cast<jlong>(value);
    }
    inline static jfloat convert(LocalRefMapType&, cocos2d::JniMethodInfo&, float value)
    {
        return static_cast<jfloat>(value);
    }
    inline static jdouble convert(LocalRefMapType&, cocos2d::JniMethodInfo&, double value)
    {
        return static_cast<jdouble>(value);
    }
    inline static jboolean convert(LocalRefMapType&, cocos2d::JniMethodInfo&, bool value)
    {
        return static_cast<jboolean>(value);
    }
    inline static jbyte convert(LocalRefMapType&, cocos2d::JniMethodInfo&, int8_t value)
    {
        return static_cast<jbyte>(value);
    }
    inline static jchar convert(LocalRefMapType&, cocos2d::JniMethodInfo&, uint8_t value)
    {
        return static_cast<jchar>(value);
    }
    inline static jshort convert(LocalRefMapType&, cocos2d::JniMethodInfo&, int16_t value)
    {
        return static_cast<jshort>(value);
    }

    template <typename T>
    static T convert(LocalRefMapType& localRefs, cocos2d::JniMethodInfo&, T x)
    {
        return x;
    }

    static void deleteLocalRefs(JNIEnv* env, LocalRefMapType& localRefs);

    static void reportError(const char* className, const char* methodName, const char* signature);
};

NS_CC_END

#endif  // __ANDROID_JNI_HELPER_H__
