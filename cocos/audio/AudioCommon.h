#pragma once
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformConfig.h"
#include <functional>
#include <string>

NS_CC_BEGIN
namespace AudioInternal
{
	CC_DLL std::string string_format(const char* format, ...);
	CC_DLL void logging(const char* format, ...);
	CC_DLL const char* getErrorString(int errorCode);
	CC_DLL bool requestRecordAudioPermission();
}
NS_CC_END

#define AINFO(_str, ...) cocos2d::AudioInternal::logging("[AINFO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AWARN(_str,...) cocos2d::AudioInternal::logging("[AWARN] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)
#define AERRO(_str, ...) cocos2d::AudioInternal::logging("[AERRO] [%s] " _str, __FUNCTION__, ##__VA_ARGS__)

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
//#include "AL/efx.h"
//#include "AL/efx-presets.h"
