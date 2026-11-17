#pragma once
#include "../value_userdata.hpp"
#include "3d/AABB.h"
#include "3d/OBB.h"
#include "3d/Ray.h"

namespace lua
{
	template<> struct value_type<cc::AABB> : std::true_type {};
	template<> struct value_type<cc::OBB> : std::true_type {};
	template<> struct value_type<cc::Ray> : std::true_type {};
}
