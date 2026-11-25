#include "SystemSnapshot-android.h"

namespace cc::system_info
{
namespace
{
constexpr auto networkClass = "org/cocos/lib/CocosSystemNetwork";

void setNetworkEvents(const char* method)
{
    if (!JniHelper::getJavaVM() || !JniHelper::classloader)
        return;
    JniMethodInfo info;
    if (!JniHelper::getStaticMethodInfo(info, networkClass, method, "()V"))
        return;
    info.env->CallStaticVoidMethod(info.classID, info.methodID);
    info.env->ExceptionClear();
    info.env->DeleteLocalRef(info.classID);
}
} // namespace

ValueMap readNetwork()
{
    auto result = android::snapshot(networkClass, "read");
    for (const char* key : {"isMetered", "isVpn"})
    {
        const auto item = result.find(key);
        if (item != result.end())
            item->second = Value(item->second.asString() == "true");
    }
    return result;
}

void startNetworkEvents()
{
    setNetworkEvents("startEvents");
}

void stopNetworkEvents()
{
    setNetworkEvents("stopEvents");
}
} // namespace cc::system_info

extern "C" JNIEXPORT void JNICALL Java_org_cocos_lib_CocosSystemNetwork_networkChanged(JNIEnv*, jclass)
{
    cc::system_info::networkChanged();
}
