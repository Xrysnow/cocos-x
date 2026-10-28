#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioCommon.h"
#include <string>
#include <vector>

NS_CC_BEGIN
	class CC_DLL AudioALSupport
	{
		static void init();
	public:

		static std::string getReadableInfo();

		static std::string getDeviceName();
		static std::string getCaptureDeviceName();
		static std::vector<std::string> getDeviceNames();
		static std::vector<std::string> getCaptureDeviceNames();

		static ALenum getBufferFormat(const std::string& name);
		static bool hasALEXT(const std::string& name);
		static bool hasALCEXT(const std::string& name);
		static void refresh();
	};
NS_CC_END
