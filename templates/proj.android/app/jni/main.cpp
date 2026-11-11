#include "AppDelegate.h"
#include <jni.h>
#include <memory>

namespace
{
std::unique_ptr<AppDelegate> app;
}

void cocos_android_app_init(JNIEnv*)
{
    app = std::make_unique<AppDelegate>();
}
