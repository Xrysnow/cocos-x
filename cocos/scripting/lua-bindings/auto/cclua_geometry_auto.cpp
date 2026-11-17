#include "cclua_geometry_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "3d/AABB.h"
#include "3d/OBB.h"
#include "3d/Ray.h"

static_assert(lua::value_type<cc::AABB>::value, "ValueTypes requires a shared runtime trait for cc::AABB");
static_assert(lua::value_type<cc::OBB>::value, "ValueTypes requires a shared runtime trait for cc::OBB");
static_assert(lua::value_type<cc::Ray>::value, "ValueTypes requires a shared runtime trait for cc::Ray");
int lua_cc_AABB_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AABB", "cc.AABB:new");
	LUA_TRY_INVOKE_R(2, ([](const cc::Vec3& arg0,const cc::Vec3& arg1){{return lua::own_value(new cc::AABB(arg0,arg1));}}));
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cc::AABB());}});
	LUA_SINVOKE_FOOTER("0,2");
}
// Impl No Dtor
int lua_cc_AABB_containPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:containPoint");
	LUA_TRY_INVOKE_R(1, &cc::AABB::containPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AABB_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getCenter");
	LUA_TRY_INVOKE_R(0, &cc::AABB::getCenter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AABB_getMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getMax");
	LUA_TRY_INVOKE_R(0, &cc::AABB::getMax);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AABB_getMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getMin");
	LUA_TRY_INVOKE_R(0, &cc::AABB::getMin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AABB_isEmpty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:isEmpty");
	LUA_TRY_INVOKE_R(0, &cc::AABB::isEmpty);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AABB_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:reset");
	LUA_TRY_INVOKE(0, &cc::AABB::reset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AABB_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:set");
	LUA_TRY_INVOKE(2, &cc::AABB::set);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_AABB_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:transform");
	LUA_TRY_INVOKE(1, &cc::AABB::transform);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccAABB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cc::AABB, "AABB", "cc.AABB",
		lua_cc_AABB_new, lua::value_collect<cc::AABB>);
	LUA_METHOD("new", lua_cc_AABB_new);
	LUA_METHOD("containPoint", lua_cc_AABB_containPoint);
	LUA_METHOD("getCenter", lua_cc_AABB_getCenter);
	LUA_METHOD("getMax", lua_cc_AABB_getMax);
	LUA_METHOD("getMin", lua_cc_AABB_getMin);
	LUA_METHOD("isEmpty", lua_cc_AABB_isEmpty);
	LUA_METHOD("reset", lua_cc_AABB_reset);
	LUA_METHOD("set", lua_cc_AABB_set);
	LUA_METHOD("transform", lua_cc_AABB_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cc::AABB>(lua_S, "cc.AABB");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_OBB_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OBB", "cc.OBB:new");
	LUA_TRY_INVOKE_R(1, [](const cc::AABB& arg0){{return lua::own_value(new cc::OBB(arg0));}});
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cc::OBB());}});
	LUA_SINVOKE_FOOTER("0,1");
}
// Impl No Dtor
int lua_cc_OBB_containPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:containPoint");
	LUA_TRY_INVOKE_R(1, &cc::OBB::containPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_OBB_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getCenter");
	LUA_TRY_INVOKE_R(0, &cc::OBB::getCenter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_getExtents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getExtents");
	LUA_TRY_INVOKE_R(0, &cc::OBB::getExtents);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_getXAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getXAxis");
	LUA_TRY_INVOKE_R(0, &cc::OBB::getXAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_getYAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getYAxis");
	LUA_TRY_INVOKE_R(0, &cc::OBB::getYAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_getZAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getZAxis");
	LUA_TRY_INVOKE_R(0, &cc::OBB::getZAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_intersects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:intersects");
	LUA_TRY_INVOKE_R(1, &cc::OBB::intersects);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_OBB_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:reset");
	LUA_TRY_INVOKE(0, &cc::OBB::reset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_OBB_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:set");
	LUA_TRY_INVOKE(5, &cc::OBB::set);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_OBB_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:transform");
	LUA_TRY_INVOKE(1, &cc::OBB::transform);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccOBB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cc::OBB, "OBB", "cc.OBB",
		lua_cc_OBB_new, lua::value_collect<cc::OBB>);
	LUA_METHOD("new", lua_cc_OBB_new);
	LUA_METHOD("containPoint", lua_cc_OBB_containPoint);
	LUA_METHOD("getCenter", lua_cc_OBB_getCenter);
	LUA_METHOD("getExtents", lua_cc_OBB_getExtents);
	LUA_METHOD("getXAxis", lua_cc_OBB_getXAxis);
	LUA_METHOD("getYAxis", lua_cc_OBB_getYAxis);
	LUA_METHOD("getZAxis", lua_cc_OBB_getZAxis);
	LUA_METHOD("intersects", lua_cc_OBB_intersects);
	LUA_METHOD("reset", lua_cc_OBB_reset);
	LUA_METHOD("set", lua_cc_OBB_set);
	LUA_METHOD("transform", lua_cc_OBB_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cc::OBB>(lua_S, "cc.OBB");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Ray_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Ray", "cc.Ray:new");
	LUA_TRY_INVOKE_R(2, ([](const cc::Vec3& arg0,const cc::Vec3& arg1){{return lua::own_value(new cc::Ray(arg0,arg1));}}));
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cc::Ray());}});
	LUA_SINVOKE_FOOTER("0,2");
}
// Impl No Dtor
int lua_cc_Ray_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:getDirection");
	LUA_TRY_INVOKE_R(0, &cc::Ray::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ray_getOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:getOrigin");
	LUA_TRY_INVOKE_R(0, &cc::Ray::getOrigin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ray_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:set");
	LUA_TRY_INVOKE(2, &cc::Ray::set);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Ray_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:transform");
	LUA_TRY_INVOKE(1, &cc::Ray::transform);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccRay(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cc::Ray, "Ray", "cc.Ray",
		lua_cc_Ray_new, lua::value_collect<cc::Ray>);
	LUA_METHOD("new", lua_cc_Ray_new);
	LUA_METHOD("getDirection", lua_cc_Ray_getDirection);
	LUA_METHOD("getOrigin", lua_cc_Ray_getOrigin);
	LUA_METHOD("set", lua_cc_Ray_set);
	LUA_METHOD("transform", lua_cc_Ray_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cc::Ray>(lua_S, "cc.Ray");
	LUA_ENTRY_END(1);
	return 0;
}

int register_all_cc_geometry(lua_State* lua_S)
{
	luaReg_Geometry_ccAABB(lua_S);
	luaReg_Geometry_ccOBB(lua_S);
	luaReg_Geometry_ccRay(lua_S);
	return 0;
}
