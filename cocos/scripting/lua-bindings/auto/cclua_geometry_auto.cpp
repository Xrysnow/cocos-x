#include "cclua_geometry_auto.hpp"
#include "scripting/lua-bindings/manual/3d/cclua_geometry_compat.hpp"
#include "3d/CCAABB.h"
#include "3d/CCOBB.h"
#include "3d/CCRay.h"

static_assert(lua::value_type<cocos2d::AABB>::value, "ValueTypes requires a shared runtime trait for cocos2d::AABB");
static_assert(lua::value_type<cocos2d::OBB>::value, "ValueTypes requires a shared runtime trait for cocos2d::OBB");
static_assert(lua::value_type<cocos2d::Ray>::value, "ValueTypes requires a shared runtime trait for cocos2d::Ray");
int lua_cocos2d_AABB_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AABB", "cc.AABB:new");
	LUA_TRY_INVOKE_R(2, [](const cocos2d::Vec3& arg0,const cocos2d::Vec3& arg1){{return lua::own_value(new cocos2d::AABB(arg0,arg1));}});
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cocos2d::AABB());}});
	LUA_SINVOKE_FOOTER("0,2");
}
// Impl No Dtor
int lua_cocos2d_AABB_containPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:containPoint");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::AABB::*)(const cocos2d::Vec3&)const>(&cocos2d::AABB::containPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AABB_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getCenter");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::AABB::*)()const>(&cocos2d::AABB::getCenter));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AABB_getMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getMax");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::AABB::*)()const>(&cocos2d::AABB::getMax));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AABB_getMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:getMin");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::AABB::*)()const>(&cocos2d::AABB::getMin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AABB_isEmpty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:isEmpty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::AABB::*)()const>(&cocos2d::AABB::isEmpty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AABB_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:reset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::AABB::*)()>(&cocos2d::AABB::reset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AABB_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:set");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::AABB::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::AABB::set));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_AABB_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AABB", "cc.AABB:transform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AABB::*)(const cocos2d::Mat4&)>(&cocos2d::AABB::transform));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccAABB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::AABB, "AABB", "cc.AABB",
		lua_cocos2d_AABB_new, lua::value_collect<cocos2d::AABB>);
	LUA_METHOD("new", lua_cocos2d_AABB_new);
	LUA_METHOD("containPoint", lua_cocos2d_AABB_containPoint);
	LUA_METHOD("getCenter", lua_cocos2d_AABB_getCenter);
	LUA_METHOD("getMax", lua_cocos2d_AABB_getMax);
	LUA_METHOD("getMin", lua_cocos2d_AABB_getMin);
	LUA_METHOD("isEmpty", lua_cocos2d_AABB_isEmpty);
	LUA_METHOD("reset", lua_cocos2d_AABB_reset);
	LUA_METHOD("set", lua_cocos2d_AABB_set);
	LUA_METHOD("transform", lua_cocos2d_AABB_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cocos2d::AABB>(lua_S, "cc.AABB");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_OBB_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.OBB", "cc.OBB:new");
	LUA_TRY_INVOKE_R(1, [](const cocos2d::AABB& arg0){{return lua::own_value(new cocos2d::OBB(arg0));}});
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cocos2d::OBB());}});
	LUA_SINVOKE_FOOTER("0,1");
}
// Impl No Dtor
int lua_cocos2d_OBB_containPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:containPoint");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::OBB::*)(const cocos2d::Vec3&)const>(&cocos2d::OBB::containPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_OBB_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getCenter");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::OBB::*)()const>(&cocos2d::OBB::getCenter));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_getExtents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getExtents");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::OBB::*)()const>(&cocos2d::OBB::getExtents));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_getXAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getXAxis");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::OBB::*)()const>(&cocos2d::OBB::getXAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_getYAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getYAxis");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::OBB::*)()const>(&cocos2d::OBB::getYAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_getZAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:getZAxis");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::OBB::*)()const>(&cocos2d::OBB::getZAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_intersects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:intersects");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::OBB::*)(const cocos2d::OBB&)const>(&cocos2d::OBB::intersects));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_OBB_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:reset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::OBB::*)()>(&cocos2d::OBB::reset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_OBB_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:set");
	LUA_TRY_INVOKE(5, static_cast<void(cocos2d::OBB::*)(const cocos2d::Vec3&, const cocos2d::Vec3&, const cocos2d::Vec3&, const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::OBB::set));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_OBB_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.OBB", "cc.OBB:transform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::OBB::*)(const cocos2d::Mat4&)>(&cocos2d::OBB::transform));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccOBB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::OBB, "OBB", "cc.OBB",
		lua_cocos2d_OBB_new, lua::value_collect<cocos2d::OBB>);
	LUA_METHOD("new", lua_cocos2d_OBB_new);
	LUA_METHOD("containPoint", lua_cocos2d_OBB_containPoint);
	LUA_METHOD("getCenter", lua_cocos2d_OBB_getCenter);
	LUA_METHOD("getExtents", lua_cocos2d_OBB_getExtents);
	LUA_METHOD("getXAxis", lua_cocos2d_OBB_getXAxis);
	LUA_METHOD("getYAxis", lua_cocos2d_OBB_getYAxis);
	LUA_METHOD("getZAxis", lua_cocos2d_OBB_getZAxis);
	LUA_METHOD("intersects", lua_cocos2d_OBB_intersects);
	LUA_METHOD("reset", lua_cocos2d_OBB_reset);
	LUA_METHOD("set", lua_cocos2d_OBB_set);
	LUA_METHOD("transform", lua_cocos2d_OBB_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cocos2d::OBB>(lua_S, "cc.OBB");
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Ray_new(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Ray", "cc.Ray:new");
	LUA_TRY_INVOKE_R(2, [](const cocos2d::Vec3& arg0,const cocos2d::Vec3& arg1){{return lua::own_value(new cocos2d::Ray(arg0,arg1));}});
	LUA_TRY_INVOKE_R(0, [](){{return lua::own_value(new cocos2d::Ray());}});
	LUA_SINVOKE_FOOTER("0,2");
}
// Impl No Dtor
int lua_cocos2d_Ray_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:getDirection");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::Ray::*)()const>(&cocos2d::Ray::getDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ray_getOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:getOrigin");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::Ray::*)()const>(&cocos2d::Ray::getOrigin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ray_set(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:set");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Ray::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Ray::set));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Ray_transform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ray", "cc.Ray:transform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Ray::*)(const cocos2d::Mat4&)>(&cocos2d::Ray::transform));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Geometry_ccRay(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::Ray, "Ray", "cc.Ray",
		lua_cocos2d_Ray_new, lua::value_collect<cocos2d::Ray>);
	LUA_METHOD("new", lua_cocos2d_Ray_new);
	LUA_METHOD("getDirection", lua_cocos2d_Ray_getDirection);
	LUA_METHOD("getOrigin", lua_cocos2d_Ray_getOrigin);
	LUA_METHOD("set", lua_cocos2d_Ray_set);
	LUA_METHOD("transform", lua_cocos2d_Ray_transform);
	LUA_CLS_END();
	lua::register_value_metatable<cocos2d::Ray>(lua_S, "cc.Ray");
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
