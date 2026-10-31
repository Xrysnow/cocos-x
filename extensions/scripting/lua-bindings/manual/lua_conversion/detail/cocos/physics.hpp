#pragma once
#include "../conversion.hpp"
#include "object.hpp"
#include "value_types.hpp"
#include "cocos2d.h"

namespace lua
{
#if CC_USE_PHYSICS
	LUA_TO_NATIVE_STRUCT3(cocos2d::PhysicsMaterial, density, restitution, friction);

	LUA_TO_LUA_STRUCT3(cocos2d::PhysicsMaterial, density, restitution, friction);

	template<>
	struct to_native<cocos2d::PhysicsContactData> {
		static bool F(lua_State* L, int lo, cocos2d::PhysicsContactData* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::PhysicsContactData v;
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
	struct to_lua<cocos2d::PhysicsContactData> {
		static void F(lua_State* L, const cocos2d::PhysicsContactData& inValue) {
			if (!L) return;
			if (inValue.count < 0 || inValue.count > inValue.POINT_MAX)
			{
				luaL_error(L, "invalid cocos2d::PhysicsContactData count: %d", inValue.count);
				return;
			}
			lua_createtable(L, 0, 3);
			native_to_luaval_field(L, -1, "normal", inValue.normal);
			native_to_luaval_field(L, -1, "POINT_MAX", inValue.POINT_MAX);
			lua_pushstring(L, "points");
			native_array_to_luaval(L, inValue.points, inValue.count);
			lua_settable(L, -3);
		}
	};

	template<>
	struct to_native<cocos2d::PhysicsRayCastInfo> {
		static bool F(lua_State* L, int lo, cocos2d::PhysicsRayCastInfo* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::PhysicsRayCastInfo v{};
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
	struct to_lua<cocos2d::PhysicsRayCastInfo> {
		static void F(lua_State* L, const cocos2d::PhysicsRayCastInfo& inValue) {
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
}
