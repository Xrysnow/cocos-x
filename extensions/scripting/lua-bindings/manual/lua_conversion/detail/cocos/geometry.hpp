#pragma once
#include "../value_userdata.hpp"
#include "3d/CCAABB.h"
#include "3d/CCOBB.h"
#include "3d/CCRay.h"

namespace lua
{
	template<> struct value_type<cocos2d::AABB> : std::true_type {};
	template<> struct value_type<cocos2d::OBB> : std::true_type {};
	template<> struct value_type<cocos2d::Ray> : std::true_type {};
}
