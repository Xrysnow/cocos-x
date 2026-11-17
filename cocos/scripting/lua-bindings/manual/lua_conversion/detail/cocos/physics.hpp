#pragma once
#include "../conversion.hpp"
#include "object.hpp"
#include "value_types.hpp"
#include "cocos2d.h"
#include "physics3d/Physics3DObject.h"

namespace lua
{
#if CC_USE_PHYSICS
	LUA_TO_NATIVE_STRUCT3(cc::PhysicsMaterial, density, restitution, friction);

	LUA_TO_LUA_STRUCT3(cc::PhysicsMaterial, density, restitution, friction);

	template<>
	struct to_native<cc::PhysicsContactData> {
		static bool F(lua_State* L, int lo, cc::PhysicsContactData* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::PhysicsContactData v;
			bool ok = luaval_field_to_native(L, lo, "normal", &v.normal, fName);
			if (ok)
			{
				lua_pushliteral(L, "points");
				lua_gettable(L, lo);
				ok = lua_istable(L, -1);
				if (ok)
				{
					const auto count = lua_objlen(L, -1);
					ok = count <= v.POINT_MAX && luaval_to_native_array(L, -1, v.points, count, fName);
					if (ok) v.count = static_cast<int>(count);
				}
				lua_pop(L, 1);
			}
			if (ok) *outValue = v;
			return ok;
		}
	};

	template<>
	struct to_lua<cc::PhysicsContactData> {
		static void F(lua_State* L, const cc::PhysicsContactData& inValue) {
			if (!L) return;
			if (inValue.count < 0 || inValue.count > inValue.POINT_MAX)
			{
				luaL_error(L, "invalid cc::PhysicsContactData count: %d", inValue.count);
				return;
			}
			lua_createtable(L, 0, 3);
			native_to_luaval_field(L, -1, "normal", inValue.normal);
			native_to_luaval_field(L, -1, "POINT_MAX", int(inValue.POINT_MAX));
			lua_pushstring(L, "points");
			native_array_to_luaval(L, inValue.points, inValue.count);
			lua_settable(L, -3);
		}
	};

	template<>
	struct to_native<cc::PhysicsRayCastInfo> {
		static bool F(lua_State* L, int lo, cc::PhysicsRayCastInfo* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cc::PhysicsRayCastInfo v{};
			bool ok = luaval_field_to_native(L, lo, "start", &v.start, fName) &&
				luaval_field_to_native(L, lo, "ended", &v.end, fName) &&
				luaval_field_to_native(L, lo, "contact", &v.contact, fName) &&
				luaval_field_to_native(L, lo, "normal", &v.normal, fName) &&
				luaval_field_to_native(L, lo, "fraction", &v.fraction, fName) &&
				luaval_field_to_native(L, lo, "shape", &v.shape, fName);
			if (ok) *outValue = v;
			return ok;
		}
	};

	template<>
	struct to_lua<cc::PhysicsRayCastInfo> {
		static void F(lua_State* L, const cc::PhysicsRayCastInfo& inValue) {
			if (!L) return;
			lua_createtable(L, 0, 6);
			native_to_luaval_field(L, -1, "start", inValue.start);
			native_to_luaval_field(L, -1, "ended", inValue.end);
			native_to_luaval_field(L, -1, "contact", inValue.contact);
			native_to_luaval_field(L, -1, "normal", inValue.normal);
			native_to_luaval_field(L, -1, "fraction", inValue.fraction);
			native_to_luaval_field(L, -1, "shape", inValue.shape);
		}
	};

#endif

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
	LUA_TO_LUA_STRUCT5(cc::Physics3DCollisionInfo::CollisionPoint,
		localPositionOnA, worldPositionOnA, localPositionOnB, worldPositionOnB, worldNormalOnB);

	LUA_TO_LUA_STRUCT3(cc::Physics3DCollisionInfo, objA, objB, collisionPointList);
#endif
}
