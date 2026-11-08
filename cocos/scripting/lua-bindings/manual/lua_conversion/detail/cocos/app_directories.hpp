#pragma once
#include "../conversion.hpp"
#include "platform/CCAppDirectories.h"

namespace lua
{
	// A result is a detached diagnostic table, not a native service object.
	LUA_TO_LUA_STRUCT4(cocos2d::DirectoryResult, status, path, nativeDomain, nativeCode);
}
