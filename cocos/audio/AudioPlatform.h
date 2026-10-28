#pragma once
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformConfig.h"
#include <string>

NS_CC_BEGIN
namespace AudioInternal
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    bool initializeAudioSession(std::string& error);
    void shutdownAudioSession();
#else
    inline bool initializeAudioSession(std::string&) { return true; }
    inline void shutdownAudioSession() {}
#endif
}
NS_CC_END
