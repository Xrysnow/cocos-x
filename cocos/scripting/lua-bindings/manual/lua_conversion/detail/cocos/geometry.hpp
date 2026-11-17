#pragma once
#include "../value_userdata.hpp"
#include "3d/CCAABB.h"
#include "3d/CCOBB.h"
#include "3d/CCRay.h"

namespace lua
{
	template<> struct value_type<cc::AABB> : std::true_type {};
	template<> struct value_type<cc::OBB> : std::true_type {};
	template<> struct value_type<cc::Ray> : std::true_type {};
}
