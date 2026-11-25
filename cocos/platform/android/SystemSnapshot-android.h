#pragma once

#include "base/ccUTF8.h"
#include "platform/SystemInfoInternal.h"
#include "platform/android/jni/JniHelper.h"

#include <charconv>
#include <optional>
#include <string_view>

namespace cc::system_info::android
{
template <typename T>
std::optional<T> number(std::string_view value, int base = 10)
{
    if (value.empty())
        return {};
    T result;
    const auto end = value.data() + value.size();
    const auto parsed = std::from_chars(value.data(), end, result, base);
    if (parsed.ec != std::errc{} || parsed.ptr != end)
        return {};
    return result;
}

inline std::string string(JNIEnv* env, jobject value)
{
    if (!value)
        return {};
    const auto str = static_cast<jstring>(value);
    const jsize length = env->GetStringLength(str);
    const jchar* chars = env->GetStringChars(str, nullptr);
    if (!chars)
        return {};
    const std::u16string utf16(chars, chars + length);
    env->ReleaseStringChars(str, chars);
    std::string utf8;
    StringUtils::UTF16ToUTF8(utf16, utf8);
    return utf8;
}

// JNI methods return key/value pairs. A colon suffix marks a field status,
// and the empty key denotes a failure of the entire platform query.
template <typename... Args>
ValueMap snapshot(const char* cls, const char* method, const char* signature, Args... args)
{
    if (!JniHelper::getJavaVM() || !JniHelper::classloader)
        return failure("pending", method);
    auto* env = JniHelper::getEnv();
    if (!env)
        return failure("platformError", method);
    if (env->PushLocalFrame(8) != JNI_OK)
    {
        env->ExceptionClear();
        return failure("platformError", method);
    }
    struct LocalFrame
    {
        JNIEnv* env;
        ~LocalFrame() { env->PopLocalFrame(nullptr); }
    } frame{env};

    JniMethodInfo info;
    if (!JniHelper::getStaticMethodInfo(info, cls, method, signature))
        return failure("platformError", method);
    const auto pairs = static_cast<jobjectArray>(env->CallStaticObjectMethod(info.classID, info.methodID, args...));
    if (env->ExceptionCheck() || !pairs)
    {
        env->ExceptionClear();
        return failure("platformError", method);
    }
    const jsize count = env->GetArrayLength(pairs);
    if (count % 2 != 0)
        return failure("parseError", method);

    ValueMap result;
    for (jsize i = 0; i < count; i += 2)
    {
        const auto keyRef = env->GetObjectArrayElement(pairs, i);
        const auto valueRef = env->GetObjectArrayElement(pairs, i + 1);
        auto key = string(env, keyRef);
        auto value = string(env, valueRef);
        env->DeleteLocalRef(keyRef);
        env->DeleteLocalRef(valueRef);
        if (env->ExceptionCheck())
        {
            env->ExceptionClear();
            return failure("platformError", method);
        }
        if (value.empty())
            continue;
        if (key.empty())
            return failure(value.c_str(), method);
        if (key.back() == ':')
        {
            key.pop_back();
            missing(result, key.c_str(), value.c_str());
        }
        else
            result.emplace(std::move(key), Value(std::move(value)));
    }
    return result;
}

inline ValueMap snapshot(const char* cls, const char* method)
{
    return snapshot(cls, method, "()[Ljava/lang/String;");
}

template <typename T>
std::optional<T> takeNumber(ValueMap& values, const char* field)
{
    const auto item = values.find(field);
    if (item == values.end())
        return {};
    const auto result = number<T>(item->second.asString());
    values.erase(item);
    return result;
}
} // namespace cc::system_info::android
