#pragma once
#include "value_types.hpp"
#include "2d/CCParticleSystem.h"

namespace lua
{
	template<>
	struct to_native<cocos2d::EmissionShape> {
		static bool F(lua_State* L, int lo, cocos2d::EmissionShape* outValue, const char* fName = "") {
			LUA_CHECK_TO_NATIVE;
			if (!is_indexable(L, lo)) return false;
			cocos2d::EmissionShape value{};
			const bool ok = luaval_field_to_native(L, lo, "type", &value.type, fName) &&
				luaval_field_to_native(L, lo, "x", &value.x, fName) &&
				luaval_field_to_native(L, lo, "y", &value.y, fName) &&
				luaval_field_to_native(L, lo, "innerWidth", &value.innerWidth, fName) &&
				luaval_field_to_native(L, lo, "innerHeight", &value.innerHeight, fName) &&
				luaval_field_to_native(L, lo, "outerWidth", &value.outerWidth, fName) &&
				luaval_field_to_native(L, lo, "outerHeight", &value.outerHeight, fName) &&
				luaval_field_to_native(L, lo, "innerRadius", &value.innerRadius, fName) &&
				luaval_field_to_native(L, lo, "outerRadius", &value.outerRadius, fName) &&
				luaval_field_to_native(L, lo, "coneOffset", &value.coneOffset, fName) &&
				luaval_field_to_native(L, lo, "coneAngle", &value.coneAngle, fName) &&
				luaval_field_to_native(L, lo, "edgeBias", &value.edgeBias, fName) &&
				luaval_field_to_native(L, lo, "fourccId", &value.fourccId, fName);
			if (ok) *outValue = value;
			return ok;
		}
	};

	template<>
	struct to_lua<cocos2d::EmissionShape> {
		static void F(lua_State* L, const cocos2d::EmissionShape& inValue) {
			if (!L) return;
			const auto value = inValue;
			lua_createtable(L, 0, 13);
			native_to_luaval_field(L, -1, "type", value.type);
			native_to_luaval_field(L, -1, "x", value.x);
			native_to_luaval_field(L, -1, "y", value.y);
			native_to_luaval_field(L, -1, "innerWidth", value.innerWidth);
			native_to_luaval_field(L, -1, "innerHeight", value.innerHeight);
			native_to_luaval_field(L, -1, "outerWidth", value.outerWidth);
			native_to_luaval_field(L, -1, "outerHeight", value.outerHeight);
			native_to_luaval_field(L, -1, "innerRadius", value.innerRadius);
			native_to_luaval_field(L, -1, "outerRadius", value.outerRadius);
			native_to_luaval_field(L, -1, "coneOffset", value.coneOffset);
			native_to_luaval_field(L, -1, "coneAngle", value.coneAngle);
			native_to_luaval_field(L, -1, "edgeBias", value.edgeBias);
			native_to_luaval_field(L, -1, "fourccId", value.fourccId);
		}
	};

	LUA_TO_NATIVE_STRUCT2(cocos2d::ParticleEmissionMaskDescriptor, size, points);

	template<>
	struct to_lua<cocos2d::ParticleEmissionMaskDescriptor> {
		static void F(lua_State* L, const cocos2d::ParticleEmissionMaskDescriptor& inValue) {
			if (!L) return;
			// The cache can be cleared by Lua GC during table allocation.
			const auto value = inValue;
			lua_createtable(L, 0, 2);
			native_to_luaval_field(L, -1, "size", value.size);
			native_to_luaval_field(L, -1, "points", value.points);
		}
	};
}
