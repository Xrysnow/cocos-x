#include "cclua_physics_auto.hpp"
#include "base/ccConfig.h"
#if CC_USE_PHYSICS
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"

int lua_cocos2d_PhysicsShape_calculateDefaultMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:calculateDefaultMoment");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()>(&cocos2d::PhysicsShape::calculateDefaultMoment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_containsPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:containsPoint");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::PhysicsShape::*)(const cocos2d::Vec2&)const>(&cocos2d::PhysicsShape::containsPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_getArea(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getArea");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getArea));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getBody(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getBody");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsBody*(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getBody));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getCategoryBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getCategoryBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getCategoryBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getCenter");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsShape::*)()>(&cocos2d::PhysicsShape::getCenter));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getCollisionBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getCollisionBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getCollisionBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getContactTestBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getContactTestBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getContactTestBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getDensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getDensity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getDensity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getFriction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getFriction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getGroup");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShape::*)()>(&cocos2d::PhysicsShape::getGroup));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getMass");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getMass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getMaterial");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::PhysicsMaterial&(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getMaterial));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getMoment");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getMoment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getOffset");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsShape::*)()>(&cocos2d::PhysicsShape::getOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getRestitution");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getRestitution));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:getType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsShape::Type(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::getType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_isSensor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:isSensor");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsShape::*)()const>(&cocos2d::PhysicsShape::isSensor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShape_setCategoryBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setCategoryBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(int)>(&cocos2d::PhysicsShape::setCategoryBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setCollisionBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setCollisionBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(int)>(&cocos2d::PhysicsShape::setCollisionBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setContactTestBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setContactTestBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(int)>(&cocos2d::PhysicsShape::setContactTestBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setDensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setDensity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(float)>(&cocos2d::PhysicsShape::setDensity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setFriction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(float)>(&cocos2d::PhysicsShape::setFriction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setGroup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(int)>(&cocos2d::PhysicsShape::setGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setMass");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(float)>(&cocos2d::PhysicsShape::setMass));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setMaterial");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(const cocos2d::PhysicsMaterial&)>(&cocos2d::PhysicsShape::setMaterial));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setMoment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(float)>(&cocos2d::PhysicsShape::setMoment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setRestitution");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(float)>(&cocos2d::PhysicsShape::setRestitution));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setSensor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setSensor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(bool)>(&cocos2d::PhysicsShape::setSensor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShape_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShape", "cc.PhysicsShape:setTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsShape::*)(int)>(&cocos2d::PhysicsShape::setTag));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics_ccPhysicsShape(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShape, "PhysicsShape", "cc.PhysicsShape",
		cocos2d::PhysicsShape, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("calculateDefaultMoment", lua_cocos2d_PhysicsShape_calculateDefaultMoment);
	LUA_METHOD("containsPoint", lua_cocos2d_PhysicsShape_containsPoint);
	LUA_METHOD("getArea", lua_cocos2d_PhysicsShape_getArea);
	LUA_METHOD("getBody", lua_cocos2d_PhysicsShape_getBody);
	LUA_METHOD("getCategoryBitmask", lua_cocos2d_PhysicsShape_getCategoryBitmask);
	LUA_METHOD("getCenter", lua_cocos2d_PhysicsShape_getCenter);
	LUA_METHOD("getCollisionBitmask", lua_cocos2d_PhysicsShape_getCollisionBitmask);
	LUA_METHOD("getContactTestBitmask", lua_cocos2d_PhysicsShape_getContactTestBitmask);
	LUA_METHOD("getDensity", lua_cocos2d_PhysicsShape_getDensity);
	LUA_METHOD("getFriction", lua_cocos2d_PhysicsShape_getFriction);
	LUA_METHOD("getGroup", lua_cocos2d_PhysicsShape_getGroup);
	LUA_METHOD("getMass", lua_cocos2d_PhysicsShape_getMass);
	LUA_METHOD("getMaterial", lua_cocos2d_PhysicsShape_getMaterial);
	LUA_METHOD("getMoment", lua_cocos2d_PhysicsShape_getMoment);
	LUA_METHOD("getOffset", lua_cocos2d_PhysicsShape_getOffset);
	LUA_METHOD("getRestitution", lua_cocos2d_PhysicsShape_getRestitution);
	LUA_METHOD("getTag", lua_cocos2d_PhysicsShape_getTag);
	LUA_METHOD("getType", lua_cocos2d_PhysicsShape_getType);
	LUA_METHOD("isSensor", lua_cocos2d_PhysicsShape_isSensor);
	LUA_METHOD("setCategoryBitmask", lua_cocos2d_PhysicsShape_setCategoryBitmask);
	LUA_METHOD("setCollisionBitmask", lua_cocos2d_PhysicsShape_setCollisionBitmask);
	LUA_METHOD("setContactTestBitmask", lua_cocos2d_PhysicsShape_setContactTestBitmask);
	LUA_METHOD("setDensity", lua_cocos2d_PhysicsShape_setDensity);
	LUA_METHOD("setFriction", lua_cocos2d_PhysicsShape_setFriction);
	LUA_METHOD("setGroup", lua_cocos2d_PhysicsShape_setGroup);
	LUA_METHOD("setMass", lua_cocos2d_PhysicsShape_setMass);
	LUA_METHOD("setMaterial", lua_cocos2d_PhysicsShape_setMaterial);
	LUA_METHOD("setMoment", lua_cocos2d_PhysicsShape_setMoment);
	LUA_METHOD("setRestitution", lua_cocos2d_PhysicsShape_setRestitution);
	LUA_METHOD("setSensor", lua_cocos2d_PhysicsShape_setSensor);
	LUA_METHOD("setTag", lua_cocos2d_PhysicsShape_setTag);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeCircle_getRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeCircle", "cc.PhysicsShapeCircle:getRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsShapeCircle::*)()const>(&cocos2d::PhysicsShapeCircle::getRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShapeCircle_calculateArea(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeCircle", "cc.PhysicsShapeCircle:calculateArea");
	LUA_TRY_INVOKE_R(1, static_cast<float(*)(float)>(&cocos2d::PhysicsShapeCircle::calculateArea));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShapeCircle_calculateMoment(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeCircle", "cc.PhysicsShapeCircle:calculateMoment");
	LUA_TRY_INVOKE_R(3, (static_cast<float(*)(float, float, const cocos2d::Vec2&)>(&cocos2d::PhysicsShapeCircle::calculateMoment)));
	LUA_TRY_INVOKE_R(2, ([](float arg0,float arg1){{return cocos2d::PhysicsShapeCircle::calculateMoment(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_cocos2d_PhysicsShapeCircle_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeCircle", "cc.PhysicsShapeCircle:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsShapeCircle*(*)(float, const cocos2d::PhysicsMaterial&, const cocos2d::Vec2&)>(&cocos2d::PhysicsShapeCircle::create)));
	LUA_TRY_INVOKE_R(2, ([](float arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsShapeCircle::create(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_R(1, [](float arg0){{return cocos2d::PhysicsShapeCircle::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Physics_ccPhysicsShapeCircle(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeCircle, "PhysicsShapeCircle", "cc.PhysicsShapeCircle",
		cocos2d::PhysicsShapeCircle, "cc.PhysicsShape",
		nullptr, nullptr);
	LUA_METHOD("getRadius", lua_cocos2d_PhysicsShapeCircle_getRadius);
	LUA_METHOD("calculateArea", lua_cocos2d_PhysicsShapeCircle_calculateArea);
	LUA_METHOD("calculateMoment", lua_cocos2d_PhysicsShapeCircle_calculateMoment);
	LUA_METHOD("create", lua_cocos2d_PhysicsShapeCircle_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapePolygon_getPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:getPoint");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::PhysicsShapePolygon::*)(int)const>(&cocos2d::PhysicsShapePolygon::getPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsShapePolygon_getPointsCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapePolygon", "cc.PhysicsShapePolygon:getPointsCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShapePolygon::*)()const>(&cocos2d::PhysicsShapePolygon::getPointsCount));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics_ccPhysicsShapePolygon(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapePolygon, "PhysicsShapePolygon", "cc.PhysicsShapePolygon",
		cocos2d::PhysicsShapePolygon, "cc.PhysicsShape",
		nullptr, nullptr);
	LUA_METHOD("getPoint", lua_cocos2d_PhysicsShapePolygon_getPoint);
	LUA_METHOD("getPointsCount", lua_cocos2d_PhysicsShapePolygon_getPointsCount);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeBox_getSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeBox", "cc.PhysicsShapeBox:getSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsShapeBox::*)()const>(&cocos2d::PhysicsShapeBox::getSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShapeBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeBox", "cc.PhysicsShapeBox:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsShapeBox*(*)(const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, const cocos2d::Vec2&, float)>(&cocos2d::PhysicsShapeBox::create)));
	LUA_TRY_INVOKE_R(3, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1,const cocos2d::Vec2& arg2){{return cocos2d::PhysicsShapeBox::create(arg0,arg1,arg2);}}));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsShapeBox::create(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vec2& arg0){{return cocos2d::PhysicsShapeBox::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Physics_ccPhysicsShapeBox(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeBox, "PhysicsShapeBox", "cc.PhysicsShapeBox",
		cocos2d::PhysicsShapeBox, "cc.PhysicsShapePolygon",
		nullptr, nullptr);
	LUA_METHOD("getSize", lua_cocos2d_PhysicsShapeBox_getSize);
	LUA_METHOD("create", lua_cocos2d_PhysicsShapeBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeEdgeSegment_getPointA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeEdgeSegment", "cc.PhysicsShapeEdgeSegment:getPointA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsShapeEdgeSegment::*)()const>(&cocos2d::PhysicsShapeEdgeSegment::getPointA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShapeEdgeSegment_getPointB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeEdgeSegment", "cc.PhysicsShapeEdgeSegment:getPointB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsShapeEdgeSegment::*)()const>(&cocos2d::PhysicsShapeEdgeSegment::getPointB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsShapeEdgeSegment_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeEdgeSegment", "cc.PhysicsShapeEdgeSegment:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsShapeEdgeSegment*(*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, float)>(&cocos2d::PhysicsShapeEdgeSegment::create)));
	LUA_TRY_INVOKE_R(3, ([](const cocos2d::Vec2& arg0,const cocos2d::Vec2& arg1,const cocos2d::PhysicsMaterial& arg2){{return cocos2d::PhysicsShapeEdgeSegment::create(arg0,arg1,arg2);}}));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::Vec2& arg1){{return cocos2d::PhysicsShapeEdgeSegment::create(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Physics_ccPhysicsShapeEdgeSegment(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeEdgeSegment, "PhysicsShapeEdgeSegment", "cc.PhysicsShapeEdgeSegment",
		cocos2d::PhysicsShapeEdgeSegment, "cc.PhysicsShape",
		nullptr, nullptr);
	LUA_METHOD("getPointA", lua_cocos2d_PhysicsShapeEdgeSegment_getPointA);
	LUA_METHOD("getPointB", lua_cocos2d_PhysicsShapeEdgeSegment_getPointB);
	LUA_METHOD("create", lua_cocos2d_PhysicsShapeEdgeSegment_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeEdgePolygon_getPointsCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeEdgePolygon", "cc.PhysicsShapeEdgePolygon:getPointsCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShapeEdgePolygon::*)()const>(&cocos2d::PhysicsShapeEdgePolygon::getPointsCount));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics_ccPhysicsShapeEdgePolygon(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeEdgePolygon, "PhysicsShapeEdgePolygon", "cc.PhysicsShapeEdgePolygon",
		cocos2d::PhysicsShapeEdgePolygon, "cc.PhysicsShape",
		nullptr, nullptr);
	LUA_METHOD("getPointsCount", lua_cocos2d_PhysicsShapeEdgePolygon_getPointsCount);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeEdgeBox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsShapeEdgeBox", "cc.PhysicsShapeEdgeBox:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsShapeEdgeBox*(*)(const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, float, const cocos2d::Vec2&)>(&cocos2d::PhysicsShapeEdgeBox::create)));
	LUA_TRY_INVOKE_R(3, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1,float arg2){{return cocos2d::PhysicsShapeEdgeBox::create(arg0,arg1,std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsShapeEdgeBox::create(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vec2& arg0){{return cocos2d::PhysicsShapeEdgeBox::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Physics_ccPhysicsShapeEdgeBox(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeEdgeBox, "PhysicsShapeEdgeBox", "cc.PhysicsShapeEdgeBox",
		cocos2d::PhysicsShapeEdgeBox, "cc.PhysicsShapeEdgePolygon",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_PhysicsShapeEdgeBox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsShapeEdgeChain_getPointsCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsShapeEdgeChain", "cc.PhysicsShapeEdgeChain:getPointsCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsShapeEdgeChain::*)()const>(&cocos2d::PhysicsShapeEdgeChain::getPointsCount));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics_ccPhysicsShapeEdgeChain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsShapeEdgeChain, "PhysicsShapeEdgeChain", "cc.PhysicsShapeEdgeChain",
		cocos2d::PhysicsShapeEdgeChain, "cc.PhysicsShape",
		nullptr, nullptr);
	LUA_METHOD("getPointsCount", lua_cocos2d_PhysicsShapeEdgeChain_getPointsCount);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsBody_addMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:addMass");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::addMass));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_addMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:addMoment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::addMoment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_addShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:addShape");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsBody::*)(cocos2d::PhysicsShape*, bool)>(&cocos2d::PhysicsBody::addShape)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::PhysicsBody* obj,cocos2d::PhysicsShape* arg0){{return obj->addShape(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_PhysicsBody_applyForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:applyForce");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::applyForce)));
	LUA_TRY_INVOKE(1, ([](cocos2d::PhysicsBody* obj,const cocos2d::Vec2& arg0){{return obj->applyForce(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_PhysicsBody_applyImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:applyImpulse");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::applyImpulse)));
	LUA_TRY_INVOKE(1, ([](cocos2d::PhysicsBody* obj,const cocos2d::Vec2& arg0){{return obj->applyImpulse(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_PhysicsBody_applyTorque(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:applyTorque");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::applyTorque));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_getAngularDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getAngularDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getAngularDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getAngularVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getAngularVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::getAngularVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getAngularVelocityLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getAngularVelocityLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::getAngularVelocityLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getCategoryBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getCategoryBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getCategoryBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getCollisionBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getCollisionBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getCollisionBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getContactTestBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getContactTestBitmask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getContactTestBitmask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getFirstShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getFirstShape");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getFirstShape));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getGroup");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getGroup));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getJoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getJoints");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<cocos2d::PhysicsJoint *>&(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getJoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getLinearDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getLinearDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getLinearDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getMass");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getMass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getMoment");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getMoment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getPositionOffset");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getPositionOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getRotation");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::getRotation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getRotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getRotationOffset");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getRotationOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getShape");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsBody::*)(int)const>(&cocos2d::PhysicsBody::getShape));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_getShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getShapes");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::PhysicsShape *>&(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getShapes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::getVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getVelocityAtLocalPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getVelocityAtLocalPoint");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::getVelocityAtLocalPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_getVelocityAtWorldPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getVelocityAtWorldPoint");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::getVelocityAtWorldPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_getVelocityLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getVelocityLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::getVelocityLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_getWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:getWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsWorld*(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::getWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_isDynamic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:isDynamic");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::isDynamic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_isGravityEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:isGravityEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::isGravityEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_isResting(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:isResting");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::isResting));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_isRotationEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:isRotationEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsBody::*)()const>(&cocos2d::PhysicsBody::isRotationEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_local2World(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:local2World");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::local2World));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_removeAllShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:removeAllShapes");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(bool)>(&cocos2d::PhysicsBody::removeAllShapes));
	LUA_TRY_INVOKE(0, [](cocos2d::PhysicsBody* obj){{return obj->removeAllShapes();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_PhysicsBody_removeFromWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:removeFromWorld");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::removeFromWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_removeShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:removeShape");
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocos2d::PhysicsBody::*)(int, bool)>(&cocos2d::PhysicsBody::removeShape)));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocos2d::PhysicsBody::*)(cocos2d::PhysicsShape*, bool)>(&cocos2d::PhysicsBody::removeShape)));
	LUA_TRY_INVOKE_OVERLOAD(1, ([](cocos2d::PhysicsBody* obj,int arg0){{return obj->removeShape(std::move(arg0));}}));
	LUA_TRY_INVOKE_OVERLOAD(1, ([](cocos2d::PhysicsBody* obj,cocos2d::PhysicsShape* arg0){{return obj->removeShape(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_PhysicsBody_resetForces(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:resetForces");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsBody::*)()>(&cocos2d::PhysicsBody::resetForces));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsBody_setAngularDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setAngularDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setAngularDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setAngularVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setAngularVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setAngularVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setAngularVelocityLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setAngularVelocityLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setAngularVelocityLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setCategoryBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setCategoryBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(int)>(&cocos2d::PhysicsBody::setCategoryBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setCollisionBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setCollisionBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(int)>(&cocos2d::PhysicsBody::setCollisionBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setContactTestBitmask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setContactTestBitmask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(int)>(&cocos2d::PhysicsBody::setContactTestBitmask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setDynamic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setDynamic");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(bool)>(&cocos2d::PhysicsBody::setDynamic));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setGravityEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setGravityEnable");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(bool)>(&cocos2d::PhysicsBody::setGravityEnable));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setGroup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(int)>(&cocos2d::PhysicsBody::setGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setLinearDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setLinearDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setLinearDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setMass");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setMass));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setMoment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setMoment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setMoment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setPositionOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::setPositionOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setResting(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setResting");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(bool)const>(&cocos2d::PhysicsBody::setResting));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setRotationEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setRotationEnable");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(bool)>(&cocos2d::PhysicsBody::setRotationEnable));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setRotationOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setRotationOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setRotationOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(int)>(&cocos2d::PhysicsBody::setTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::setVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_setVelocityLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:setVelocityLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsBody::*)(float)>(&cocos2d::PhysicsBody::setVelocityLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_world2Local(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:world2Local");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::PhysicsBody::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::world2Local));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsBody_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::PhysicsBody*(*)(float, float)>(&cocos2d::PhysicsBody::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::PhysicsBody*(*)(float)>(&cocos2d::PhysicsBody::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsBody*(*)()>(&cocos2d::PhysicsBody::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int lua_cocos2d_PhysicsBody_createBox(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createBox");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsBody*(*)(const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::createBox)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsBody::createBox(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vec2& arg0){{return cocos2d::PhysicsBody::createBox(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_PhysicsBody_createCircle(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createCircle");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsBody*(*)(float, const cocos2d::PhysicsMaterial&, const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::createCircle)));
	LUA_TRY_INVOKE_R(2, ([](float arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsBody::createCircle(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_R(1, [](float arg0){{return cocos2d::PhysicsBody::createCircle(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_PhysicsBody_createEdgeBox(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createEdgeBox");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsBody*(*)(const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, float, const cocos2d::Vec2&)>(&cocos2d::PhysicsBody::createEdgeBox)));
	LUA_TRY_INVOKE_R(3, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1,float arg2){{return cocos2d::PhysicsBody::createEdgeBox(arg0,arg1,std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::PhysicsMaterial& arg1){{return cocos2d::PhysicsBody::createEdgeBox(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vec2& arg0){{return cocos2d::PhysicsBody::createEdgeBox(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_PhysicsBody_createEdgeSegment(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsBody", "cc.PhysicsBody:createEdgeSegment");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsBody*(*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::PhysicsMaterial&, float)>(&cocos2d::PhysicsBody::createEdgeSegment)));
	LUA_TRY_INVOKE_R(3, ([](const cocos2d::Vec2& arg0,const cocos2d::Vec2& arg1,const cocos2d::PhysicsMaterial& arg2){{return cocos2d::PhysicsBody::createEdgeSegment(arg0,arg1,arg2);}}));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vec2& arg0,const cocos2d::Vec2& arg1){{return cocos2d::PhysicsBody::createEdgeSegment(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Physics_ccPhysicsBody(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsBody, "PhysicsBody", "cc.PhysicsBody",
		cocos2d::PhysicsBody, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("addMass", lua_cocos2d_PhysicsBody_addMass);
	LUA_METHOD("addMoment", lua_cocos2d_PhysicsBody_addMoment);
	LUA_METHOD("addShape", lua_cocos2d_PhysicsBody_addShape);
	LUA_METHOD("applyForce", lua_cocos2d_PhysicsBody_applyForce);
	LUA_METHOD("applyImpulse", lua_cocos2d_PhysicsBody_applyImpulse);
	LUA_METHOD("applyTorque", lua_cocos2d_PhysicsBody_applyTorque);
	LUA_METHOD("getAngularDamping", lua_cocos2d_PhysicsBody_getAngularDamping);
	LUA_METHOD("getAngularVelocity", lua_cocos2d_PhysicsBody_getAngularVelocity);
	LUA_METHOD("getAngularVelocityLimit", lua_cocos2d_PhysicsBody_getAngularVelocityLimit);
	LUA_METHOD("getCategoryBitmask", lua_cocos2d_PhysicsBody_getCategoryBitmask);
	LUA_METHOD("getCollisionBitmask", lua_cocos2d_PhysicsBody_getCollisionBitmask);
	LUA_METHOD("getContactTestBitmask", lua_cocos2d_PhysicsBody_getContactTestBitmask);
	LUA_METHOD("getFirstShape", lua_cocos2d_PhysicsBody_getFirstShape);
	LUA_METHOD("getGroup", lua_cocos2d_PhysicsBody_getGroup);
	LUA_METHOD("getJoints", lua_cocos2d_PhysicsBody_getJoints);
	LUA_METHOD("getLinearDamping", lua_cocos2d_PhysicsBody_getLinearDamping);
	LUA_METHOD("getMass", lua_cocos2d_PhysicsBody_getMass);
	LUA_METHOD("getMoment", lua_cocos2d_PhysicsBody_getMoment);
	LUA_METHOD("getNode", lua_cocos2d_PhysicsBody_getNode);
	LUA_METHOD("getPosition", lua_cocos2d_PhysicsBody_getPosition);
	LUA_METHOD("getPositionOffset", lua_cocos2d_PhysicsBody_getPositionOffset);
	LUA_METHOD("getRotation", lua_cocos2d_PhysicsBody_getRotation);
	LUA_METHOD("getRotationOffset", lua_cocos2d_PhysicsBody_getRotationOffset);
	LUA_METHOD("getShape", lua_cocos2d_PhysicsBody_getShape);
	LUA_METHOD("getShapes", lua_cocos2d_PhysicsBody_getShapes);
	LUA_METHOD("getTag", lua_cocos2d_PhysicsBody_getTag);
	LUA_METHOD("getVelocity", lua_cocos2d_PhysicsBody_getVelocity);
	LUA_METHOD("getVelocityAtLocalPoint", lua_cocos2d_PhysicsBody_getVelocityAtLocalPoint);
	LUA_METHOD("getVelocityAtWorldPoint", lua_cocos2d_PhysicsBody_getVelocityAtWorldPoint);
	LUA_METHOD("getVelocityLimit", lua_cocos2d_PhysicsBody_getVelocityLimit);
	LUA_METHOD("getWorld", lua_cocos2d_PhysicsBody_getWorld);
	LUA_METHOD("isDynamic", lua_cocos2d_PhysicsBody_isDynamic);
	LUA_METHOD("isGravityEnabled", lua_cocos2d_PhysicsBody_isGravityEnabled);
	LUA_METHOD("isResting", lua_cocos2d_PhysicsBody_isResting);
	LUA_METHOD("isRotationEnabled", lua_cocos2d_PhysicsBody_isRotationEnabled);
	LUA_METHOD("local2World", lua_cocos2d_PhysicsBody_local2World);
	LUA_METHOD("removeAllShapes", lua_cocos2d_PhysicsBody_removeAllShapes);
	LUA_METHOD("removeFromWorld", lua_cocos2d_PhysicsBody_removeFromWorld);
	LUA_METHOD("removeShape", lua_cocos2d_PhysicsBody_removeShape);
	LUA_METHOD("resetForces", lua_cocos2d_PhysicsBody_resetForces);
	LUA_METHOD("setAngularDamping", lua_cocos2d_PhysicsBody_setAngularDamping);
	LUA_METHOD("setAngularVelocity", lua_cocos2d_PhysicsBody_setAngularVelocity);
	LUA_METHOD("setAngularVelocityLimit", lua_cocos2d_PhysicsBody_setAngularVelocityLimit);
	LUA_METHOD("setCategoryBitmask", lua_cocos2d_PhysicsBody_setCategoryBitmask);
	LUA_METHOD("setCollisionBitmask", lua_cocos2d_PhysicsBody_setCollisionBitmask);
	LUA_METHOD("setContactTestBitmask", lua_cocos2d_PhysicsBody_setContactTestBitmask);
	LUA_METHOD("setDynamic", lua_cocos2d_PhysicsBody_setDynamic);
	LUA_METHOD("setGravityEnable", lua_cocos2d_PhysicsBody_setGravityEnable);
	LUA_METHOD("setGroup", lua_cocos2d_PhysicsBody_setGroup);
	LUA_METHOD("setLinearDamping", lua_cocos2d_PhysicsBody_setLinearDamping);
	LUA_METHOD("setMass", lua_cocos2d_PhysicsBody_setMass);
	LUA_METHOD("setMoment", lua_cocos2d_PhysicsBody_setMoment);
	LUA_METHOD("setPositionOffset", lua_cocos2d_PhysicsBody_setPositionOffset);
	LUA_METHOD("setResting", lua_cocos2d_PhysicsBody_setResting);
	LUA_METHOD("setRotationEnable", lua_cocos2d_PhysicsBody_setRotationEnable);
	LUA_METHOD("setRotationOffset", lua_cocos2d_PhysicsBody_setRotationOffset);
	LUA_METHOD("setTag", lua_cocos2d_PhysicsBody_setTag);
	LUA_METHOD("setVelocity", lua_cocos2d_PhysicsBody_setVelocity);
	LUA_METHOD("setVelocityLimit", lua_cocos2d_PhysicsBody_setVelocityLimit);
	LUA_METHOD("world2Local", lua_cocos2d_PhysicsBody_world2Local);
	LUA_METHOD("create", lua_cocos2d_PhysicsBody_create);
	LUA_METHOD("createBox", lua_cocos2d_PhysicsBody_createBox);
	LUA_METHOD("createCircle", lua_cocos2d_PhysicsBody_createCircle);
	LUA_METHOD("createEdgeBox", lua_cocos2d_PhysicsBody_createEdgeBox);
	LUA_METHOD("createEdgeSegment", lua_cocos2d_PhysicsBody_createEdgeSegment);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsContact_getEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContact", "cc.PhysicsContact:getEventCode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsContact::EventCode(cocos2d::PhysicsContact::*)()const>(&cocos2d::PhysicsContact::getEventCode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContact_getShapeA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContact", "cc.PhysicsContact:getShapeA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsContact::*)()const>(&cocos2d::PhysicsContact::getShapeA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContact_getShapeB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContact", "cc.PhysicsContact:getShapeB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsContact::*)()const>(&cocos2d::PhysicsContact::getShapeB));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics_ccPhysicsContact(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsContact, "PhysicsContact", "cc.PhysicsContact",
		cocos2d::PhysicsContact, "cc.EventCustom",
		nullptr, nullptr);
	LUA_METHOD("getEventCode", lua_cocos2d_PhysicsContact_getEventCode);
	LUA_METHOD("getShapeA", lua_cocos2d_PhysicsContact_getShapeA);
	LUA_METHOD("getShapeB", lua_cocos2d_PhysicsContact_getShapeB);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsContactPreSolve_getFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:getFriction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsContactPreSolve::*)()const>(&cocos2d::PhysicsContactPreSolve::getFriction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPreSolve_getRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:getRestitution");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsContactPreSolve::*)()const>(&cocos2d::PhysicsContactPreSolve::getRestitution));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPreSolve_getSurfaceVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:getSurfaceVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsContactPreSolve::*)()const>(&cocos2d::PhysicsContactPreSolve::getSurfaceVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPreSolve_ignore(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:ignore");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsContactPreSolve::*)()>(&cocos2d::PhysicsContactPreSolve::ignore));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPreSolve_setFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:setFriction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsContactPreSolve::*)(float)>(&cocos2d::PhysicsContactPreSolve::setFriction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsContactPreSolve_setRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:setRestitution");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsContactPreSolve::*)(float)>(&cocos2d::PhysicsContactPreSolve::setRestitution));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsContactPreSolve_setSurfaceVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPreSolve", "cc.PhysicsContactPreSolve:setSurfaceVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsContactPreSolve::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsContactPreSolve::setSurfaceVelocity));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics_ccPhysicsContactPreSolve(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsContactPreSolve, "PhysicsContactPreSolve", "cc.PhysicsContactPreSolve",
		cocos2d::PhysicsContactPreSolve, "",
		nullptr, nullptr);
	LUA_METHOD("getFriction", lua_cocos2d_PhysicsContactPreSolve_getFriction);
	LUA_METHOD("getRestitution", lua_cocos2d_PhysicsContactPreSolve_getRestitution);
	LUA_METHOD("getSurfaceVelocity", lua_cocos2d_PhysicsContactPreSolve_getSurfaceVelocity);
	LUA_METHOD("ignore", lua_cocos2d_PhysicsContactPreSolve_ignore);
	LUA_METHOD("setFriction", lua_cocos2d_PhysicsContactPreSolve_setFriction);
	LUA_METHOD("setRestitution", lua_cocos2d_PhysicsContactPreSolve_setRestitution);
	LUA_METHOD("setSurfaceVelocity", lua_cocos2d_PhysicsContactPreSolve_setSurfaceVelocity);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsContactPostSolve_getFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPostSolve", "cc.PhysicsContactPostSolve:getFriction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsContactPostSolve::*)()const>(&cocos2d::PhysicsContactPostSolve::getFriction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPostSolve_getRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPostSolve", "cc.PhysicsContactPostSolve:getRestitution");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsContactPostSolve::*)()const>(&cocos2d::PhysicsContactPostSolve::getRestitution));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsContactPostSolve_getSurfaceVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsContactPostSolve", "cc.PhysicsContactPostSolve:getSurfaceVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsContactPostSolve::*)()const>(&cocos2d::PhysicsContactPostSolve::getSurfaceVelocity));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics_ccPhysicsContactPostSolve(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsContactPostSolve, "PhysicsContactPostSolve", "cc.PhysicsContactPostSolve",
		cocos2d::PhysicsContactPostSolve, "",
		nullptr, nullptr);
	LUA_METHOD("getFriction", lua_cocos2d_PhysicsContactPostSolve_getFriction);
	LUA_METHOD("getRestitution", lua_cocos2d_PhysicsContactPostSolve_getRestitution);
	LUA_METHOD("getSurfaceVelocity", lua_cocos2d_PhysicsContactPostSolve_getSurfaceVelocity);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerPhysicsContact_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerPhysicsContact", "cc.EventListenerPhysicsContact:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventListenerPhysicsContact*(*)()>(&cocos2d::EventListenerPhysicsContact::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Physics_ccEventListenerPhysicsContact(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerPhysicsContact, "EventListenerPhysicsContact", "cc.EventListenerPhysicsContact",
		cocos2d::EventListenerPhysicsContact, "cc.EventListenerCustom",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EventListenerPhysicsContact_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerPhysicsContactWithBodies_hitTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerPhysicsContactWithBodies", "cc.EventListenerPhysicsContactWithBodies:hitTest");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::EventListenerPhysicsContactWithBodies::*)(cocos2d::PhysicsShape*, cocos2d::PhysicsShape*)>(&cocos2d::EventListenerPhysicsContactWithBodies::hitTest)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventListenerPhysicsContactWithBodies_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerPhysicsContactWithBodies", "cc.EventListenerPhysicsContactWithBodies:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EventListenerPhysicsContactWithBodies*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*)>(&cocos2d::EventListenerPhysicsContactWithBodies::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Physics_ccEventListenerPhysicsContactWithBodies(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerPhysicsContactWithBodies, "EventListenerPhysicsContactWithBodies", "cc.EventListenerPhysicsContactWithBodies",
		cocos2d::EventListenerPhysicsContactWithBodies, "cc.EventListenerPhysicsContact",
		nullptr, nullptr);
	LUA_METHOD("hitTest", lua_cocos2d_EventListenerPhysicsContactWithBodies_hitTest);
	LUA_METHOD("create", lua_cocos2d_EventListenerPhysicsContactWithBodies_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerPhysicsContactWithShapes_hitTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerPhysicsContactWithShapes", "cc.EventListenerPhysicsContactWithShapes:hitTest");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::EventListenerPhysicsContactWithShapes::*)(cocos2d::PhysicsShape*, cocos2d::PhysicsShape*)>(&cocos2d::EventListenerPhysicsContactWithShapes::hitTest)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventListenerPhysicsContactWithShapes_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerPhysicsContactWithShapes", "cc.EventListenerPhysicsContactWithShapes:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EventListenerPhysicsContactWithShapes*(*)(cocos2d::PhysicsShape*, cocos2d::PhysicsShape*)>(&cocos2d::EventListenerPhysicsContactWithShapes::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Physics_ccEventListenerPhysicsContactWithShapes(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerPhysicsContactWithShapes, "EventListenerPhysicsContactWithShapes", "cc.EventListenerPhysicsContactWithShapes",
		cocos2d::EventListenerPhysicsContactWithShapes, "cc.EventListenerPhysicsContact",
		nullptr, nullptr);
	LUA_METHOD("hitTest", lua_cocos2d_EventListenerPhysicsContactWithShapes_hitTest);
	LUA_METHOD("create", lua_cocos2d_EventListenerPhysicsContactWithShapes_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerPhysicsContactWithGroup_hitTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerPhysicsContactWithGroup", "cc.EventListenerPhysicsContactWithGroup:hitTest");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::EventListenerPhysicsContactWithGroup::*)(cocos2d::PhysicsShape*, cocos2d::PhysicsShape*)>(&cocos2d::EventListenerPhysicsContactWithGroup::hitTest)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventListenerPhysicsContactWithGroup_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerPhysicsContactWithGroup", "cc.EventListenerPhysicsContactWithGroup:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::EventListenerPhysicsContactWithGroup*(*)(int)>(&cocos2d::EventListenerPhysicsContactWithGroup::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Physics_ccEventListenerPhysicsContactWithGroup(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerPhysicsContactWithGroup, "EventListenerPhysicsContactWithGroup", "cc.EventListenerPhysicsContactWithGroup",
		cocos2d::EventListenerPhysicsContactWithGroup, "cc.EventListenerPhysicsContact",
		nullptr, nullptr);
	LUA_METHOD("hitTest", lua_cocos2d_EventListenerPhysicsContactWithGroup_hitTest);
	LUA_METHOD("create", lua_cocos2d_EventListenerPhysicsContactWithGroup_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJoint_getBodyA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:getBodyA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsBody*(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::getBodyA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_getBodyB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:getBodyB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsBody*(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::getBodyB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_getMaxForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:getMaxForce");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::getMaxForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:getTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::getTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_getWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:getWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsWorld*(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::getWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_isCollisionEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:isCollisionEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::isCollisionEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsJoint::*)()const>(&cocos2d::PhysicsJoint::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_removeFormWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:removeFormWorld");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsJoint::*)()>(&cocos2d::PhysicsJoint::removeFormWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJoint_setCollisionEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:setCollisionEnable");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJoint::*)(bool)>(&cocos2d::PhysicsJoint::setCollisionEnable));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJoint_setEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:setEnable");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJoint::*)(bool)>(&cocos2d::PhysicsJoint::setEnable));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJoint_setMaxForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:setMaxForce");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJoint::*)(float)>(&cocos2d::PhysicsJoint::setMaxForce));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJoint_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJoint", "cc.PhysicsJoint:setTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJoint::*)(int)>(&cocos2d::PhysicsJoint::setTag));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics_ccPhysicsJoint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJoint, "PhysicsJoint", "cc.PhysicsJoint",
		cocos2d::PhysicsJoint, "",
		nullptr, nullptr);
	LUA_METHOD("getBodyA", lua_cocos2d_PhysicsJoint_getBodyA);
	LUA_METHOD("getBodyB", lua_cocos2d_PhysicsJoint_getBodyB);
	LUA_METHOD("getMaxForce", lua_cocos2d_PhysicsJoint_getMaxForce);
	LUA_METHOD("getTag", lua_cocos2d_PhysicsJoint_getTag);
	LUA_METHOD("getWorld", lua_cocos2d_PhysicsJoint_getWorld);
	LUA_METHOD("isCollisionEnabled", lua_cocos2d_PhysicsJoint_isCollisionEnabled);
	LUA_METHOD("isEnabled", lua_cocos2d_PhysicsJoint_isEnabled);
	LUA_METHOD("removeFormWorld", lua_cocos2d_PhysicsJoint_removeFormWorld);
	LUA_METHOD("setCollisionEnable", lua_cocos2d_PhysicsJoint_setCollisionEnable);
	LUA_METHOD("setEnable", lua_cocos2d_PhysicsJoint_setEnable);
	LUA_METHOD("setMaxForce", lua_cocos2d_PhysicsJoint_setMaxForce);
	LUA_METHOD("setTag", lua_cocos2d_PhysicsJoint_setTag);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointFixed_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointFixed", "cc.PhysicsJointFixed:construct");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsJointFixed*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointFixed::construct)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Physics_ccPhysicsJointFixed(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointFixed, "PhysicsJointFixed", "cc.PhysicsJointFixed",
		cocos2d::PhysicsJointFixed, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointFixed_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointLimit_getAnchr1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:getAnchr1");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointLimit::*)()const>(&cocos2d::PhysicsJointLimit::getAnchr1));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointLimit_getAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:getAnchr2");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointLimit::*)()const>(&cocos2d::PhysicsJointLimit::getAnchr2));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointLimit_getMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:getMax");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointLimit::*)()const>(&cocos2d::PhysicsJointLimit::getMax));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointLimit_getMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:getMin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointLimit::*)()const>(&cocos2d::PhysicsJointLimit::getMin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointLimit_setAnchr1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:setAnchr1");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointLimit::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointLimit::setAnchr1));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointLimit_setAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:setAnchr2");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointLimit::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointLimit::setAnchr2));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointLimit_setMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:setMax");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointLimit::*)(float)>(&cocos2d::PhysicsJointLimit::setMax));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointLimit_setMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:setMin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointLimit::*)(float)>(&cocos2d::PhysicsJointLimit::setMin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointLimit_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointLimit", "cc.PhysicsJointLimit:construct");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::PhysicsJointLimit*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&, float, float)>(&cocos2d::PhysicsJointLimit::construct)));
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointLimit*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointLimit::construct)));
	LUA_SINVOKE_FOOTER("4,6");
}
int luaReg_Physics_ccPhysicsJointLimit(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointLimit, "PhysicsJointLimit", "cc.PhysicsJointLimit",
		cocos2d::PhysicsJointLimit, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getAnchr1", lua_cocos2d_PhysicsJointLimit_getAnchr1);
	LUA_METHOD("getAnchr2", lua_cocos2d_PhysicsJointLimit_getAnchr2);
	LUA_METHOD("getMax", lua_cocos2d_PhysicsJointLimit_getMax);
	LUA_METHOD("getMin", lua_cocos2d_PhysicsJointLimit_getMin);
	LUA_METHOD("setAnchr1", lua_cocos2d_PhysicsJointLimit_setAnchr1);
	LUA_METHOD("setAnchr2", lua_cocos2d_PhysicsJointLimit_setAnchr2);
	LUA_METHOD("setMax", lua_cocos2d_PhysicsJointLimit_setMax);
	LUA_METHOD("setMin", lua_cocos2d_PhysicsJointLimit_setMin);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointLimit_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointPin_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointPin", "cc.PhysicsJointPin:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointPin*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointPin::construct)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsJointPin*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointPin::construct)));
	LUA_SINVOKE_FOOTER("3,4");
}
int luaReg_Physics_ccPhysicsJointPin(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointPin, "PhysicsJointPin", "cc.PhysicsJointPin",
		cocos2d::PhysicsJointPin, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointPin_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointDistance_getDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointDistance", "cc.PhysicsJointDistance:getDistance");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointDistance::*)()const>(&cocos2d::PhysicsJointDistance::getDistance));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointDistance_setDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointDistance", "cc.PhysicsJointDistance:setDistance");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointDistance::*)(float)>(&cocos2d::PhysicsJointDistance::setDistance));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointDistance_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointDistance", "cc.PhysicsJointDistance:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointDistance*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointDistance::construct)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Physics_ccPhysicsJointDistance(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointDistance, "PhysicsJointDistance", "cc.PhysicsJointDistance",
		cocos2d::PhysicsJointDistance, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getDistance", lua_cocos2d_PhysicsJointDistance_getDistance);
	LUA_METHOD("setDistance", lua_cocos2d_PhysicsJointDistance_setDistance);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointDistance_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointSpring_getAnchr1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:getAnchr1");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointSpring::*)()const>(&cocos2d::PhysicsJointSpring::getAnchr1));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointSpring_getAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:getAnchr2");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointSpring::*)()const>(&cocos2d::PhysicsJointSpring::getAnchr2));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointSpring_getDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:getDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointSpring::*)()const>(&cocos2d::PhysicsJointSpring::getDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointSpring_getRestLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:getRestLength");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointSpring::*)()const>(&cocos2d::PhysicsJointSpring::getRestLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointSpring_getStiffness(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:getStiffness");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointSpring::*)()const>(&cocos2d::PhysicsJointSpring::getStiffness));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointSpring_setAnchr1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:setAnchr1");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointSpring::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointSpring::setAnchr1));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointSpring_setAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:setAnchr2");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointSpring::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointSpring::setAnchr2));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointSpring_setDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:setDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointSpring::*)(float)>(&cocos2d::PhysicsJointSpring::setDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointSpring_setRestLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:setRestLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointSpring::*)(float)>(&cocos2d::PhysicsJointSpring::setRestLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointSpring_setStiffness(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:setStiffness");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointSpring::*)(float)>(&cocos2d::PhysicsJointSpring::setStiffness));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointSpring_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointSpring", "cc.PhysicsJointSpring:construct");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::PhysicsJointSpring*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&, float, float)>(&cocos2d::PhysicsJointSpring::construct)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Physics_ccPhysicsJointSpring(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointSpring, "PhysicsJointSpring", "cc.PhysicsJointSpring",
		cocos2d::PhysicsJointSpring, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getAnchr1", lua_cocos2d_PhysicsJointSpring_getAnchr1);
	LUA_METHOD("getAnchr2", lua_cocos2d_PhysicsJointSpring_getAnchr2);
	LUA_METHOD("getDamping", lua_cocos2d_PhysicsJointSpring_getDamping);
	LUA_METHOD("getRestLength", lua_cocos2d_PhysicsJointSpring_getRestLength);
	LUA_METHOD("getStiffness", lua_cocos2d_PhysicsJointSpring_getStiffness);
	LUA_METHOD("setAnchr1", lua_cocos2d_PhysicsJointSpring_setAnchr1);
	LUA_METHOD("setAnchr2", lua_cocos2d_PhysicsJointSpring_setAnchr2);
	LUA_METHOD("setDamping", lua_cocos2d_PhysicsJointSpring_setDamping);
	LUA_METHOD("setRestLength", lua_cocos2d_PhysicsJointSpring_setRestLength);
	LUA_METHOD("setStiffness", lua_cocos2d_PhysicsJointSpring_setStiffness);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointSpring_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointGroove_getAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:getAnchr2");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointGroove::*)()const>(&cocos2d::PhysicsJointGroove::getAnchr2));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointGroove_getGrooveA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:getGrooveA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointGroove::*)()const>(&cocos2d::PhysicsJointGroove::getGrooveA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointGroove_getGrooveB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:getGrooveB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsJointGroove::*)()const>(&cocos2d::PhysicsJointGroove::getGrooveB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointGroove_setAnchr2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:setAnchr2");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointGroove::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointGroove::setAnchr2));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointGroove_setGrooveA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:setGrooveA");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointGroove::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointGroove::setGrooveA));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointGroove_setGrooveB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:setGrooveB");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointGroove::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsJointGroove::setGrooveB));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointGroove_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointGroove", "cc.PhysicsJointGroove:construct");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::PhysicsJointGroove*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::PhysicsJointGroove::construct)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Physics_ccPhysicsJointGroove(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointGroove, "PhysicsJointGroove", "cc.PhysicsJointGroove",
		cocos2d::PhysicsJointGroove, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getAnchr2", lua_cocos2d_PhysicsJointGroove_getAnchr2);
	LUA_METHOD("getGrooveA", lua_cocos2d_PhysicsJointGroove_getGrooveA);
	LUA_METHOD("getGrooveB", lua_cocos2d_PhysicsJointGroove_getGrooveB);
	LUA_METHOD("setAnchr2", lua_cocos2d_PhysicsJointGroove_setAnchr2);
	LUA_METHOD("setGrooveA", lua_cocos2d_PhysicsJointGroove_setGrooveA);
	LUA_METHOD("setGrooveB", lua_cocos2d_PhysicsJointGroove_setGrooveB);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointGroove_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointRotarySpring_getDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:getDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRotarySpring::*)()const>(&cocos2d::PhysicsJointRotarySpring::getDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRotarySpring_getRestAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:getRestAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRotarySpring::*)()const>(&cocos2d::PhysicsJointRotarySpring::getRestAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRotarySpring_getStiffness(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:getStiffness");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRotarySpring::*)()const>(&cocos2d::PhysicsJointRotarySpring::getStiffness));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRotarySpring_setDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:setDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRotarySpring::*)(float)>(&cocos2d::PhysicsJointRotarySpring::setDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRotarySpring_setRestAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:setRestAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRotarySpring::*)(float)>(&cocos2d::PhysicsJointRotarySpring::setRestAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRotarySpring_setStiffness(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:setStiffness");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRotarySpring::*)(float)>(&cocos2d::PhysicsJointRotarySpring::setStiffness));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRotarySpring_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointRotarySpring*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, float, float)>(&cocos2d::PhysicsJointRotarySpring::construct)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Physics_ccPhysicsJointRotarySpring(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointRotarySpring, "PhysicsJointRotarySpring", "cc.PhysicsJointRotarySpring",
		cocos2d::PhysicsJointRotarySpring, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getDamping", lua_cocos2d_PhysicsJointRotarySpring_getDamping);
	LUA_METHOD("getRestAngle", lua_cocos2d_PhysicsJointRotarySpring_getRestAngle);
	LUA_METHOD("getStiffness", lua_cocos2d_PhysicsJointRotarySpring_getStiffness);
	LUA_METHOD("setDamping", lua_cocos2d_PhysicsJointRotarySpring_setDamping);
	LUA_METHOD("setRestAngle", lua_cocos2d_PhysicsJointRotarySpring_setRestAngle);
	LUA_METHOD("setStiffness", lua_cocos2d_PhysicsJointRotarySpring_setStiffness);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointRotarySpring_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointRotaryLimit_getMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit:getMax");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRotaryLimit::*)()const>(&cocos2d::PhysicsJointRotaryLimit::getMax));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRotaryLimit_getMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit:getMin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRotaryLimit::*)()const>(&cocos2d::PhysicsJointRotaryLimit::getMin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRotaryLimit_setMax(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit:setMax");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRotaryLimit::*)(float)>(&cocos2d::PhysicsJointRotaryLimit::setMax));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRotaryLimit_setMin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit:setMin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRotaryLimit::*)(float)>(&cocos2d::PhysicsJointRotaryLimit::setMin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRotaryLimit_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointRotaryLimit*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, float, float)>(&cocos2d::PhysicsJointRotaryLimit::construct)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::PhysicsJointRotaryLimit*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*)>(&cocos2d::PhysicsJointRotaryLimit::construct)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Physics_ccPhysicsJointRotaryLimit(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointRotaryLimit, "PhysicsJointRotaryLimit", "cc.PhysicsJointRotaryLimit",
		cocos2d::PhysicsJointRotaryLimit, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getMax", lua_cocos2d_PhysicsJointRotaryLimit_getMax);
	LUA_METHOD("getMin", lua_cocos2d_PhysicsJointRotaryLimit_getMin);
	LUA_METHOD("setMax", lua_cocos2d_PhysicsJointRotaryLimit_setMax);
	LUA_METHOD("setMin", lua_cocos2d_PhysicsJointRotaryLimit_setMin);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointRotaryLimit_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointRatchet_getAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:getAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRatchet::*)()const>(&cocos2d::PhysicsJointRatchet::getAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRatchet_getPhase(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:getPhase");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRatchet::*)()const>(&cocos2d::PhysicsJointRatchet::getPhase));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRatchet_getRatchet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:getRatchet");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointRatchet::*)()const>(&cocos2d::PhysicsJointRatchet::getRatchet));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointRatchet_setAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:setAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRatchet::*)(float)>(&cocos2d::PhysicsJointRatchet::setAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRatchet_setPhase(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:setPhase");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRatchet::*)(float)>(&cocos2d::PhysicsJointRatchet::setPhase));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRatchet_setRatchet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:setRatchet");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointRatchet::*)(float)>(&cocos2d::PhysicsJointRatchet::setRatchet));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointRatchet_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointRatchet", "cc.PhysicsJointRatchet:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointRatchet*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, float, float)>(&cocos2d::PhysicsJointRatchet::construct)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Physics_ccPhysicsJointRatchet(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointRatchet, "PhysicsJointRatchet", "cc.PhysicsJointRatchet",
		cocos2d::PhysicsJointRatchet, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getAngle", lua_cocos2d_PhysicsJointRatchet_getAngle);
	LUA_METHOD("getPhase", lua_cocos2d_PhysicsJointRatchet_getPhase);
	LUA_METHOD("getRatchet", lua_cocos2d_PhysicsJointRatchet_getRatchet);
	LUA_METHOD("setAngle", lua_cocos2d_PhysicsJointRatchet_setAngle);
	LUA_METHOD("setPhase", lua_cocos2d_PhysicsJointRatchet_setPhase);
	LUA_METHOD("setRatchet", lua_cocos2d_PhysicsJointRatchet_setRatchet);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointRatchet_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointGear_getPhase(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGear", "cc.PhysicsJointGear:getPhase");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointGear::*)()const>(&cocos2d::PhysicsJointGear::getPhase));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointGear_getRatio(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGear", "cc.PhysicsJointGear:getRatio");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointGear::*)()const>(&cocos2d::PhysicsJointGear::getRatio));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointGear_setPhase(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGear", "cc.PhysicsJointGear:setPhase");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointGear::*)(float)>(&cocos2d::PhysicsJointGear::setPhase));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointGear_setRatio(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointGear", "cc.PhysicsJointGear:setRatio");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointGear::*)(float)>(&cocos2d::PhysicsJointGear::setRatio));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointGear_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointGear", "cc.PhysicsJointGear:construct");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::PhysicsJointGear*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, float, float)>(&cocos2d::PhysicsJointGear::construct)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Physics_ccPhysicsJointGear(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointGear, "PhysicsJointGear", "cc.PhysicsJointGear",
		cocos2d::PhysicsJointGear, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getPhase", lua_cocos2d_PhysicsJointGear_getPhase);
	LUA_METHOD("getRatio", lua_cocos2d_PhysicsJointGear_getRatio);
	LUA_METHOD("setPhase", lua_cocos2d_PhysicsJointGear_setPhase);
	LUA_METHOD("setRatio", lua_cocos2d_PhysicsJointGear_setRatio);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointGear_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsJointMotor_getRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointMotor", "cc.PhysicsJointMotor:getRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsJointMotor::*)()const>(&cocos2d::PhysicsJointMotor::getRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsJointMotor_setRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsJointMotor", "cc.PhysicsJointMotor:setRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsJointMotor::*)(float)>(&cocos2d::PhysicsJointMotor::setRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsJointMotor_construct(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PhysicsJointMotor", "cc.PhysicsJointMotor:construct");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PhysicsJointMotor*(*)(cocos2d::PhysicsBody*, cocos2d::PhysicsBody*, float)>(&cocos2d::PhysicsJointMotor::construct)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Physics_ccPhysicsJointMotor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsJointMotor, "PhysicsJointMotor", "cc.PhysicsJointMotor",
		cocos2d::PhysicsJointMotor, "cc.PhysicsJoint",
		nullptr, nullptr);
	LUA_METHOD("getRate", lua_cocos2d_PhysicsJointMotor_getRate);
	LUA_METHOD("setRate", lua_cocos2d_PhysicsJointMotor_setRate);
	LUA_METHOD("construct", lua_cocos2d_PhysicsJointMotor_construct);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsWorld_addJoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:addJoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(cocos2d::PhysicsJoint*)>(&cocos2d::PhysicsWorld::addJoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_getAllBodies(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getAllBodies");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::PhysicsBody *>&(cocos2d::PhysicsWorld::*)()const>(&cocos2d::PhysicsWorld::getAllBodies));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getBody(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getBody");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::PhysicsBody*(cocos2d::PhysicsWorld::*)(int)const>(&cocos2d::PhysicsWorld::getBody));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_getDebugDrawMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getDebugDrawMask");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsWorld::*)()>(&cocos2d::PhysicsWorld::getDebugDrawMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getFixedUpdateRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getFixedUpdateRate");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsWorld::*)()const>(&cocos2d::PhysicsWorld::getFixedUpdateRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getGravity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::PhysicsWorld::*)()const>(&cocos2d::PhysicsWorld::getGravity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getShape(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getShape");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::PhysicsShape*(cocos2d::PhysicsWorld::*)(const cocos2d::Vec2&)const>(&cocos2d::PhysicsWorld::getShape));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_getShapes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getShapes");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vector<cocos2d::PhysicsShape *>(cocos2d::PhysicsWorld::*)(const cocos2d::Vec2&)const>(&cocos2d::PhysicsWorld::getShapes));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PhysicsWorld::*)()>(&cocos2d::PhysicsWorld::getSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getSubsteps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getSubsteps");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsWorld::*)()const>(&cocos2d::PhysicsWorld::getSubsteps));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_getUpdateRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:getUpdateRate");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::PhysicsWorld::*)()>(&cocos2d::PhysicsWorld::getUpdateRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_isAutoStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:isAutoStep");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::PhysicsWorld::*)()>(&cocos2d::PhysicsWorld::isAutoStep));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_removeAllBodies(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:removeAllBodies");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsWorld::*)()>(&cocos2d::PhysicsWorld::removeAllBodies));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsWorld_removeAllJoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:removeAllJoints");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(bool)>(&cocos2d::PhysicsWorld::removeAllJoints));
	LUA_TRY_INVOKE(0, [](cocos2d::PhysicsWorld* obj){{return obj->removeAllJoints();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_PhysicsWorld_removeBody(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:removeBody");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::PhysicsWorld::*)(int)>(&cocos2d::PhysicsWorld::removeBody));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::PhysicsWorld::*)(cocos2d::PhysicsBody*)>(&cocos2d::PhysicsWorld::removeBody));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_removeJoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:removeJoint");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::PhysicsWorld::*)(cocos2d::PhysicsJoint*, bool)>(&cocos2d::PhysicsWorld::removeJoint)));
	LUA_TRY_INVOKE(1, ([](cocos2d::PhysicsWorld* obj,cocos2d::PhysicsJoint* arg0){{return obj->removeJoint(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_PhysicsWorld_setAutoStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setAutoStep");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(bool)>(&cocos2d::PhysicsWorld::setAutoStep));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setDebugDrawMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setDebugDrawMask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(int)>(&cocos2d::PhysicsWorld::setDebugDrawMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setFixedUpdateRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setFixedUpdateRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(int)>(&cocos2d::PhysicsWorld::setFixedUpdateRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(const cocos2d::Vec2&)>(&cocos2d::PhysicsWorld::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setPostUpdateCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setPostUpdateCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(const std::function<void()>&)>(&cocos2d::PhysicsWorld::setPostUpdateCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setPreUpdateCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setPreUpdateCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(const std::function<void()>&)>(&cocos2d::PhysicsWorld::setPreUpdateCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(float)>(&cocos2d::PhysicsWorld::setSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setSubsteps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setSubsteps");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(int)>(&cocos2d::PhysicsWorld::setSubsteps));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_setUpdateRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:setUpdateRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(int)>(&cocos2d::PhysicsWorld::setUpdateRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsWorld_step(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsWorld", "cc.PhysicsWorld:step");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsWorld::*)(float)>(&cocos2d::PhysicsWorld::step));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics_ccPhysicsWorld(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsWorld, "PhysicsWorld", "cc.PhysicsWorld",
		cocos2d::PhysicsWorld, "",
		nullptr, nullptr);
	LUA_METHOD("addJoint", lua_cocos2d_PhysicsWorld_addJoint);
	LUA_METHOD("getAllBodies", lua_cocos2d_PhysicsWorld_getAllBodies);
	LUA_METHOD("getBody", lua_cocos2d_PhysicsWorld_getBody);
	LUA_METHOD("getDebugDrawMask", lua_cocos2d_PhysicsWorld_getDebugDrawMask);
	LUA_METHOD("getFixedUpdateRate", lua_cocos2d_PhysicsWorld_getFixedUpdateRate);
	LUA_METHOD("getGravity", lua_cocos2d_PhysicsWorld_getGravity);
	LUA_METHOD("getShape", lua_cocos2d_PhysicsWorld_getShape);
	LUA_METHOD("getShapes", lua_cocos2d_PhysicsWorld_getShapes);
	LUA_METHOD("getSpeed", lua_cocos2d_PhysicsWorld_getSpeed);
	LUA_METHOD("getSubsteps", lua_cocos2d_PhysicsWorld_getSubsteps);
	LUA_METHOD("getUpdateRate", lua_cocos2d_PhysicsWorld_getUpdateRate);
	LUA_METHOD("isAutoStep", lua_cocos2d_PhysicsWorld_isAutoStep);
	LUA_METHOD("removeAllBodies", lua_cocos2d_PhysicsWorld_removeAllBodies);
	LUA_METHOD("removeAllJoints", lua_cocos2d_PhysicsWorld_removeAllJoints);
	LUA_METHOD("removeBody", lua_cocos2d_PhysicsWorld_removeBody);
	LUA_METHOD("removeJoint", lua_cocos2d_PhysicsWorld_removeJoint);
	LUA_METHOD("setAutoStep", lua_cocos2d_PhysicsWorld_setAutoStep);
	LUA_METHOD("setDebugDrawMask", lua_cocos2d_PhysicsWorld_setDebugDrawMask);
	LUA_METHOD("setFixedUpdateRate", lua_cocos2d_PhysicsWorld_setFixedUpdateRate);
	LUA_METHOD("setGravity", lua_cocos2d_PhysicsWorld_setGravity);
	LUA_METHOD("setPostUpdateCallback", lua_cocos2d_PhysicsWorld_setPostUpdateCallback);
	LUA_METHOD("setPreUpdateCallback", lua_cocos2d_PhysicsWorld_setPreUpdateCallback);
	LUA_METHOD("setSpeed", lua_cocos2d_PhysicsWorld_setSpeed);
	LUA_METHOD("setSubsteps", lua_cocos2d_PhysicsWorld_setSubsteps);
	LUA_METHOD("setUpdateRate", lua_cocos2d_PhysicsWorld_setUpdateRate);
	LUA_METHOD("step", lua_cocos2d_PhysicsWorld_step);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_physics(lua_State* lua_S)
{
#include "base/ccConfig.h"
#if CC_USE_PHYSICS
	tolua_open(lua_S);
	luaReg_Physics_ccPhysicsShape(lua_S);
	luaReg_Physics_ccPhysicsShapeCircle(lua_S);
	luaReg_Physics_ccPhysicsShapePolygon(lua_S);
	luaReg_Physics_ccPhysicsShapeBox(lua_S);
	luaReg_Physics_ccPhysicsShapeEdgeSegment(lua_S);
	luaReg_Physics_ccPhysicsShapeEdgePolygon(lua_S);
	luaReg_Physics_ccPhysicsShapeEdgeBox(lua_S);
	luaReg_Physics_ccPhysicsShapeEdgeChain(lua_S);
	luaReg_Physics_ccPhysicsBody(lua_S);
	luaReg_Physics_ccPhysicsContact(lua_S);
	luaReg_Physics_ccPhysicsContactPreSolve(lua_S);
	luaReg_Physics_ccPhysicsContactPostSolve(lua_S);
	luaReg_Physics_ccEventListenerPhysicsContact(lua_S);
	luaReg_Physics_ccEventListenerPhysicsContactWithBodies(lua_S);
	luaReg_Physics_ccEventListenerPhysicsContactWithShapes(lua_S);
	luaReg_Physics_ccEventListenerPhysicsContactWithGroup(lua_S);
	luaReg_Physics_ccPhysicsJoint(lua_S);
	luaReg_Physics_ccPhysicsJointFixed(lua_S);
	luaReg_Physics_ccPhysicsJointLimit(lua_S);
	luaReg_Physics_ccPhysicsJointPin(lua_S);
	luaReg_Physics_ccPhysicsJointDistance(lua_S);
	luaReg_Physics_ccPhysicsJointSpring(lua_S);
	luaReg_Physics_ccPhysicsJointGroove(lua_S);
	luaReg_Physics_ccPhysicsJointRotarySpring(lua_S);
	luaReg_Physics_ccPhysicsJointRotaryLimit(lua_S);
	luaReg_Physics_ccPhysicsJointRatchet(lua_S);
	luaReg_Physics_ccPhysicsJointGear(lua_S);
	luaReg_Physics_ccPhysicsJointMotor(lua_S);
	luaReg_Physics_ccPhysicsWorld(lua_S);
	return 0;
#else
	return 0;
#endif
}
