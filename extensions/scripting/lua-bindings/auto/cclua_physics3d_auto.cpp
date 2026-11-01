#include "cclua_physics3d_auto.hpp"
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "scripting/lua-bindings/manual/physics3d/cclua_physics3d_compat.hpp"
#include "physics3d/CCPhysics3D.h"

int lua_cocos2d_Physics3DShape_getShapeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:getShapeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DShape::ShapeType(cocos2d::Physics3DShape::*)()const>(&cocos2d::Physics3DShape::getShapeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DShape_initBox(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:initBox");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Physics3DShape::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DShape::initBox));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DShape_initCapsule(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:initCapsule");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Physics3DShape::*)(float, float)>(&cocos2d::Physics3DShape::initCapsule));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_initCylinder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:initCylinder");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Physics3DShape::*)(float, float)>(&cocos2d::Physics3DShape::initCylinder));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_initSphere(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:initSphere");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Physics3DShape::*)(float)>(&cocos2d::Physics3DShape::initSphere));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DShape_createBox(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:createBox");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Physics3DShape*(*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DShape::createBox));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DShape_createCapsule(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:createCapsule");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Physics3DShape*(*)(float, float)>(&cocos2d::Physics3DShape::createCapsule));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_createCylinder(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:createCylinder");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Physics3DShape*(*)(float, float)>(&cocos2d::Physics3DShape::createCylinder));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_createSphere(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:createSphere");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Physics3DShape*(*)(float)>(&cocos2d::Physics3DShape::createSphere));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Physics3D_ccPhysics3DShape(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DShape, "Physics3DShape", "cc.Physics3DShape",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getShapeType", lua_cocos2d_Physics3DShape_getShapeType);
	LUA_METHOD("initBox", lua_cocos2d_Physics3DShape_initBox);
	LUA_METHOD("initCapsule", lua_cocos2d_Physics3DShape_initCapsule);
	LUA_METHOD("initCylinder", lua_cocos2d_Physics3DShape_initCylinder);
	LUA_METHOD("initSphere", lua_cocos2d_Physics3DShape_initSphere);
	LUA_METHOD("createBox", lua_cocos2d_Physics3DShape_createBox);
	LUA_METHOD("createCapsule", lua_cocos2d_Physics3DShape_createCapsule);
	LUA_METHOD("createCylinder", lua_cocos2d_Physics3DShape_createCylinder);
	LUA_METHOD("createSphere", lua_cocos2d_Physics3DShape_createSphere);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DObject_getMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:getMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Physics3DObject::*)()const>(&cocos2d::Physics3DObject::getMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DObject_getObjType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:getObjType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DObject::PhysicsObjType(cocos2d::Physics3DObject::*)()const>(&cocos2d::Physics3DObject::getObjType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DObject_getPhysicsWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:getPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DWorld*(cocos2d::Physics3DObject::*)()const>(&cocos2d::Physics3DObject::getPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DObject_getWorldTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:getWorldTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DObject::*)()const>(&cocos2d::Physics3DObject::getWorldTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DObject_needCollisionCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:needCollisionCallback");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DObject::*)()>(&cocos2d::Physics3DObject::needCollisionCallback));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DObject_setCollisionCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:setCollisionCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DObject::*)(const cocos2d::Physics3DObject::CollisionCallbackFunc&)>(&cocos2d::Physics3DObject::setCollisionCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DObject_setMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:setMask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DObject::*)(unsigned int)>(&cocos2d::Physics3DObject::setMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DObject_setPhysicsWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DObject", "cc.Physics3DObject:setPhysicsWorld");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DObject::*)(cocos2d::Physics3DWorld*)>(&cocos2d::Physics3DObject::setPhysicsWorld));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics3D_ccPhysics3DObject(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DObject, "Physics3DObject", "cc.Physics3DObject",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getMask", lua_cocos2d_Physics3DObject_getMask);
	LUA_METHOD("getObjType", lua_cocos2d_Physics3DObject_getObjType);
	LUA_METHOD("getPhysicsWorld", lua_cocos2d_Physics3DObject_getPhysicsWorld);
	LUA_METHOD("getWorldTransform", lua_cocos2d_Physics3DObject_getWorldTransform);
	LUA_METHOD("needCollisionCallback", lua_cocos2d_Physics3DObject_needCollisionCallback);
	LUA_METHOD("setCollisionCallback", lua_cocos2d_Physics3DObject_setCollisionCallback);
	LUA_METHOD("setMask", lua_cocos2d_Physics3DObject_setMask);
	LUA_METHOD("setPhysicsWorld", lua_cocos2d_Physics3DObject_setPhysicsWorld);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DRigidBody_addConstraint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:addConstraint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(cocos2d::Physics3DConstraint*)>(&cocos2d::Physics3DRigidBody::addConstraint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_applyCentralForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyCentralForce");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyCentralForce));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_applyCentralImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyCentralImpulse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyCentralImpulse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_applyDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::applyDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_applyForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyForce");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyForce));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DRigidBody_applyImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyImpulse");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyImpulse));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DRigidBody_applyTorque(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyTorque");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyTorque));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_applyTorqueImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyTorqueImpulse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyTorqueImpulse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_getAngularDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getAngularDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getAngularDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getAngularFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getAngularFactor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getAngularFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getAngularVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getAngularVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getAngularVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getCcdMotionThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getCcdMotionThreshold");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getCcdMotionThreshold));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getCcdSweptSphereRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getCcdSweptSphereRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getCcdSweptSphereRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getCenterOfMassTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getCenterOfMassTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getCenterOfMassTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getConstraint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getConstraint");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Physics3DConstraint*(cocos2d::Physics3DRigidBody::*)(unsigned int)const>(&cocos2d::Physics3DRigidBody::getConstraint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_getConstraintCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getConstraintCount");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getConstraintCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getFriction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getFriction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getGravity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getGravity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getHitFraction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getHitFraction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getHitFraction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getInvInertiaDiagLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getInvInertiaDiagLocal");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getInvInertiaDiagLocal));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getInvMass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getInvMass");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getInvMass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getLinearDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getLinearDamping");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getLinearDamping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getLinearFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getLinearFactor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getLinearFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getLinearVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getLinearVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getLinearVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getRestitution");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getRestitution));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getRollingFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getRollingFriction");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getRollingFriction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getTotalForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getTotalForce");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getTotalForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_getTotalTorque(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:getTotalTorque");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::getTotalTorque));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_isKinematic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:isKinematic");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DRigidBody::*)()const>(&cocos2d::Physics3DRigidBody::isKinematic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DRigidBody_removeConstraint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:removeConstraint");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(unsigned int)>(&cocos2d::Physics3DRigidBody::removeConstraint));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(cocos2d::Physics3DConstraint*)>(&cocos2d::Physics3DRigidBody::removeConstraint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setActive");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(bool)>(&cocos2d::Physics3DRigidBody::setActive));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setAngularFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setAngularFactor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setAngularFactor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setAngularFactor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setAngularVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setAngularVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setAngularVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setCcdMotionThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setCcdMotionThreshold");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setCcdMotionThreshold));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setCcdSweptSphereRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setCcdSweptSphereRadius");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setCcdSweptSphereRadius));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setCenterOfMassTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setCenterOfMassTransform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Mat4&)>(&cocos2d::Physics3DRigidBody::setCenterOfMassTransform));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setDamping");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DRigidBody::*)(float, float)>(&cocos2d::Physics3DRigidBody::setDamping));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DRigidBody_setFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setFriction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setFriction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setHitFraction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setHitFraction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setHitFraction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setInvInertiaDiagLocal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setInvInertiaDiagLocal");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setInvInertiaDiagLocal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setKinematic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setKinematic");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(bool)>(&cocos2d::Physics3DRigidBody::setKinematic));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setLinearFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setLinearFactor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setLinearFactor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setLinearVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setLinearVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setLinearVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setMassProps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setMassProps");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DRigidBody::*)(float, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setMassProps));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DRigidBody_setRestitution(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setRestitution");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setRestitution));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DRigidBody_setRollingFriction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:setRollingFriction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DRigidBody::*)(float)>(&cocos2d::Physics3DRigidBody::setRollingFriction));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics3D_ccPhysics3DRigidBody(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DRigidBody, "Physics3DRigidBody", "cc.Physics3DRigidBody",
		cocos2d::Physics3DObject, "cc.Physics3DObject",
		nullptr, nullptr);
	LUA_METHOD("addConstraint", lua_cocos2d_Physics3DRigidBody_addConstraint);
	LUA_METHOD("applyCentralForce", lua_cocos2d_Physics3DRigidBody_applyCentralForce);
	LUA_METHOD("applyCentralImpulse", lua_cocos2d_Physics3DRigidBody_applyCentralImpulse);
	LUA_METHOD("applyDamping", lua_cocos2d_Physics3DRigidBody_applyDamping);
	LUA_METHOD("applyForce", lua_cocos2d_Physics3DRigidBody_applyForce);
	LUA_METHOD("applyImpulse", lua_cocos2d_Physics3DRigidBody_applyImpulse);
	LUA_METHOD("applyTorque", lua_cocos2d_Physics3DRigidBody_applyTorque);
	LUA_METHOD("applyTorqueImpulse", lua_cocos2d_Physics3DRigidBody_applyTorqueImpulse);
	LUA_METHOD("getAngularDamping", lua_cocos2d_Physics3DRigidBody_getAngularDamping);
	LUA_METHOD("getAngularFactor", lua_cocos2d_Physics3DRigidBody_getAngularFactor);
	LUA_METHOD("getAngularVelocity", lua_cocos2d_Physics3DRigidBody_getAngularVelocity);
	LUA_METHOD("getCcdMotionThreshold", lua_cocos2d_Physics3DRigidBody_getCcdMotionThreshold);
	LUA_METHOD("getCcdSweptSphereRadius", lua_cocos2d_Physics3DRigidBody_getCcdSweptSphereRadius);
	LUA_METHOD("getCenterOfMassTransform", lua_cocos2d_Physics3DRigidBody_getCenterOfMassTransform);
	LUA_METHOD("getConstraint", lua_cocos2d_Physics3DRigidBody_getConstraint);
	LUA_METHOD("getConstraintCount", lua_cocos2d_Physics3DRigidBody_getConstraintCount);
	LUA_METHOD("getFriction", lua_cocos2d_Physics3DRigidBody_getFriction);
	LUA_METHOD("getGravity", lua_cocos2d_Physics3DRigidBody_getGravity);
	LUA_METHOD("getHitFraction", lua_cocos2d_Physics3DRigidBody_getHitFraction);
	LUA_METHOD("getInvInertiaDiagLocal", lua_cocos2d_Physics3DRigidBody_getInvInertiaDiagLocal);
	LUA_METHOD("getInvMass", lua_cocos2d_Physics3DRigidBody_getInvMass);
	LUA_METHOD("getLinearDamping", lua_cocos2d_Physics3DRigidBody_getLinearDamping);
	LUA_METHOD("getLinearFactor", lua_cocos2d_Physics3DRigidBody_getLinearFactor);
	LUA_METHOD("getLinearVelocity", lua_cocos2d_Physics3DRigidBody_getLinearVelocity);
	LUA_METHOD("getRestitution", lua_cocos2d_Physics3DRigidBody_getRestitution);
	LUA_METHOD("getRollingFriction", lua_cocos2d_Physics3DRigidBody_getRollingFriction);
	LUA_METHOD("getTotalForce", lua_cocos2d_Physics3DRigidBody_getTotalForce);
	LUA_METHOD("getTotalTorque", lua_cocos2d_Physics3DRigidBody_getTotalTorque);
	LUA_METHOD("isKinematic", lua_cocos2d_Physics3DRigidBody_isKinematic);
	LUA_METHOD("removeConstraint", lua_cocos2d_Physics3DRigidBody_removeConstraint);
	LUA_METHOD("setActive", lua_cocos2d_Physics3DRigidBody_setActive);
	LUA_METHOD("setAngularFactor", lua_cocos2d_Physics3DRigidBody_setAngularFactor);
	LUA_METHOD("setAngularVelocity", lua_cocos2d_Physics3DRigidBody_setAngularVelocity);
	LUA_METHOD("setCcdMotionThreshold", lua_cocos2d_Physics3DRigidBody_setCcdMotionThreshold);
	LUA_METHOD("setCcdSweptSphereRadius", lua_cocos2d_Physics3DRigidBody_setCcdSweptSphereRadius);
	LUA_METHOD("setCenterOfMassTransform", lua_cocos2d_Physics3DRigidBody_setCenterOfMassTransform);
	LUA_METHOD("setDamping", lua_cocos2d_Physics3DRigidBody_setDamping);
	LUA_METHOD("setFriction", lua_cocos2d_Physics3DRigidBody_setFriction);
	LUA_METHOD("setGravity", lua_cocos2d_Physics3DRigidBody_setGravity);
	LUA_METHOD("setHitFraction", lua_cocos2d_Physics3DRigidBody_setHitFraction);
	LUA_METHOD("setInvInertiaDiagLocal", lua_cocos2d_Physics3DRigidBody_setInvInertiaDiagLocal);
	LUA_METHOD("setKinematic", lua_cocos2d_Physics3DRigidBody_setKinematic);
	LUA_METHOD("setLinearFactor", lua_cocos2d_Physics3DRigidBody_setLinearFactor);
	LUA_METHOD("setLinearVelocity", lua_cocos2d_Physics3DRigidBody_setLinearVelocity);
	LUA_METHOD("setMassProps", lua_cocos2d_Physics3DRigidBody_setMassProps);
	LUA_METHOD("setRestitution", lua_cocos2d_Physics3DRigidBody_setRestitution);
	LUA_METHOD("setRollingFriction", lua_cocos2d_Physics3DRigidBody_setRollingFriction);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DComponent_addToPhysicsWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:addToPhysicsWorld");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DComponent::*)(cocos2d::Physics3DWorld*)>(&cocos2d::Physics3DComponent::addToPhysicsWorld));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DComponent_getPhysics3DObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:getPhysics3DObject");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DObject*(cocos2d::Physics3DComponent::*)()const>(&cocos2d::Physics3DComponent::getPhysics3DObject));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DComponent_setPhysics3DObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:setPhysics3DObject");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DComponent::*)(cocos2d::Physics3DObject*)>(&cocos2d::Physics3DComponent::setPhysics3DObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DComponent_setSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:setSyncFlag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DComponent::*)(cocos2d::Physics3DComponent::PhysicsSyncFlag)>(&cocos2d::Physics3DComponent::setSyncFlag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DComponent_syncNodeToPhysics(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:syncNodeToPhysics");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DComponent::*)()>(&cocos2d::Physics3DComponent::syncNodeToPhysics));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DComponent_syncPhysicsToNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:syncPhysicsToNode");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DComponent::*)()>(&cocos2d::Physics3DComponent::syncPhysicsToNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DComponent_getPhysics3DComponentName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:getPhysics3DComponentName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string&(*)()>(&cocos2d::Physics3DComponent::getPhysics3DComponentName));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Physics3D_ccPhysics3DComponent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DComponent, "Physics3DComponent", "cc.Physics3DComponent",
		cocos2d::Component, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("addToPhysicsWorld", lua_cocos2d_Physics3DComponent_addToPhysicsWorld);
	LUA_METHOD("getPhysics3DObject", lua_cocos2d_Physics3DComponent_getPhysics3DObject);
	LUA_METHOD("setPhysics3DObject", lua_cocos2d_Physics3DComponent_setPhysics3DObject);
	LUA_METHOD("setSyncFlag", lua_cocos2d_Physics3DComponent_setSyncFlag);
	LUA_METHOD("syncNodeToPhysics", lua_cocos2d_Physics3DComponent_syncNodeToPhysics);
	LUA_METHOD("syncPhysicsToNode", lua_cocos2d_Physics3DComponent_syncPhysicsToNode);
	LUA_METHOD("getPhysics3DComponentName", lua_cocos2d_Physics3DComponent_getPhysics3DComponentName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
extern int luaReg_Physics3D_ccPhysics3DShape(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DObject(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DRigidBody(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DComponent(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysicsMeshRenderer(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DWorld(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DConstraint(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DPointToPointConstraint(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DHingeConstraint(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DSliderConstraint(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3DConeTwistConstraint(lua_State* lua_S);
extern int luaReg_Physics3D_ccPhysics3D6DofConstraint(lua_State* lua_S);
#endif

int register_all_cc_physics3d(lua_State* lua_S)
{
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
	luaReg_Physics3D_ccPhysics3DShape(lua_S);
	luaReg_Physics3D_ccPhysics3DObject(lua_S);
	luaReg_Physics3D_ccPhysics3DRigidBody(lua_S);
	luaReg_Physics3D_ccPhysics3DComponent(lua_S);
	luaReg_Physics3D_ccPhysicsMeshRenderer(lua_S);
	luaReg_Physics3D_ccPhysics3DWorld(lua_S);
	luaReg_Physics3D_ccPhysics3DConstraint(lua_S);
	luaReg_Physics3D_ccPhysics3DPointToPointConstraint(lua_S);
	luaReg_Physics3D_ccPhysics3DHingeConstraint(lua_S);
	luaReg_Physics3D_ccPhysics3DSliderConstraint(lua_S);
	luaReg_Physics3D_ccPhysics3DConeTwistConstraint(lua_S);
	luaReg_Physics3D_ccPhysics3D6DofConstraint(lua_S);
	return register_all_cc_physics3d_retained(lua_S);
#else
	return 0;
#endif
}
