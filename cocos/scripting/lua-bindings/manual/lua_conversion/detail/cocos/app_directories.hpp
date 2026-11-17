#pragma once
#include "../conversion.hpp"
#include "platform/AppDirectories.h"

namespace lua
{
	// A result is a detached diagnostic table, not a native service object.
	LUA_TO_LUA_STRUCT4(cc::DirectoryResult, status, path, nativeDomain, nativeCode);
}
