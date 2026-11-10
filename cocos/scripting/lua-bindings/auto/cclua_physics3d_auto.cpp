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
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Physics3DShape::*)(float, float)>(&cocos2d::Physics3DShape::initCapsule)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_initCylinder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:initCylinder");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Physics3DShape::*)(float, float)>(&cocos2d::Physics3DShape::initCylinder)));
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Physics3DShape*(*)(float, float)>(&cocos2d::Physics3DShape::createCapsule)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DShape_createCylinder(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DShape", "cc.Physics3DShape:createCylinder");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Physics3DShape*(*)(float, float)>(&cocos2d::Physics3DShape::createCylinder)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyForce)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DRigidBody_applyImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DRigidBody", "cc.Physics3DRigidBody:applyImpulse");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DRigidBody::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::applyImpulse)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DRigidBody::*)(float, float)>(&cocos2d::Physics3DRigidBody::setDamping)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DRigidBody::*)(float, const cocos2d::Vec3&)>(&cocos2d::Physics3DRigidBody::setMassProps)));
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
int lua_cocos2d_Physics3DComponent_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DComponent", "cc.Physics3DComponent:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DComponent*(*)()>(&cocos2d::Physics3DComponent::create));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Physics3DComponent*(*)(cocos2d::Physics3DObject*, const cocos2d::Vec3&, const cocos2d::Quaternion&)>(&cocos2d::Physics3DComponent::create)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Physics3DObject* arg0,const cocos2d::Vec3& arg1){{return cocos2d::Physics3DComponent::create(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Physics3DObject* arg0){{return cocos2d::Physics3DComponent::create(arg0);}});
	LUA_SINVOKE_FOOTER("0,1,2,3");
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
	LUA_METHOD("create", lua_cocos2d_Physics3DComponent_create_1);
	LUA_METHOD("getPhysics3DComponentName", lua_cocos2d_Physics3DComponent_getPhysics3DComponentName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PhysicsMeshRenderer_getPhysicsObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsMeshRenderer", "cc.PhysicsMeshRenderer:getPhysicsObj");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DObject*(cocos2d::PhysicsMeshRenderer::*)()const>(&cocos2d::PhysicsMeshRenderer::getPhysicsObj));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsMeshRenderer_setSyncFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsMeshRenderer", "cc.PhysicsMeshRenderer:setSyncFlag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PhysicsMeshRenderer::*)(cocos2d::Physics3DComponent::PhysicsSyncFlag)>(&cocos2d::PhysicsMeshRenderer::setSyncFlag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PhysicsMeshRenderer_syncNodeToPhysics(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsMeshRenderer", "cc.PhysicsMeshRenderer:syncNodeToPhysics");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsMeshRenderer::*)()>(&cocos2d::PhysicsMeshRenderer::syncNodeToPhysics));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PhysicsMeshRenderer_syncPhysicsToNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PhysicsMeshRenderer", "cc.PhysicsMeshRenderer:syncPhysicsToNode");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::PhysicsMeshRenderer::*)()>(&cocos2d::PhysicsMeshRenderer::syncPhysicsToNode));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Physics3D_ccPhysicsMeshRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PhysicsMeshRenderer, "PhysicsMeshRenderer", "cc.PhysicsMeshRenderer",
		cocos2d::MeshRenderer, "cc.MeshRenderer",
		nullptr, nullptr);
	LUA_METHOD("getPhysicsObj", lua_cocos2d_PhysicsMeshRenderer_getPhysicsObj);
	LUA_METHOD("setSyncFlag", lua_cocos2d_PhysicsMeshRenderer_setSyncFlag);
	LUA_METHOD("syncNodeToPhysics", lua_cocos2d_PhysicsMeshRenderer_syncNodeToPhysics);
	LUA_METHOD("syncPhysicsToNode", lua_cocos2d_PhysicsMeshRenderer_syncPhysicsToNode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DWorld_addPhysics3DConstraint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:addPhysics3DConstraint");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Physics3DConstraint*, bool)>(&cocos2d::Physics3DWorld::addPhysics3DConstraint)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Physics3DWorld* obj,cocos2d::Physics3DConstraint* arg0){{return obj->addPhysics3DConstraint(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Physics3DWorld_addPhysics3DObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:addPhysics3DObject");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Physics3DObject*)>(&cocos2d::Physics3DWorld::addPhysics3DObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_collisionChecking(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:collisionChecking");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DWorld::*)()>(&cocos2d::Physics3DWorld::collisionChecking));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_debugDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:debugDraw");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Renderer*)>(&cocos2d::Physics3DWorld::debugDraw));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_getGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:getGravity");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DWorld::*)()const>(&cocos2d::Physics3DWorld::getGravity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_isDebugDrawEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:isDebugDrawEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DWorld::*)()const>(&cocos2d::Physics3DWorld::isDebugDrawEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_needCollisionChecking(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:needCollisionChecking");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DWorld::*)()>(&cocos2d::Physics3DWorld::needCollisionChecking));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_removeAllPhysics3DConstraints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:removeAllPhysics3DConstraints");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DWorld::*)()>(&cocos2d::Physics3DWorld::removeAllPhysics3DConstraints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_removeAllPhysics3DObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:removeAllPhysics3DObjects");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DWorld::*)()>(&cocos2d::Physics3DWorld::removeAllPhysics3DObjects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_removePhysics3DConstraint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:removePhysics3DConstraint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Physics3DConstraint*)>(&cocos2d::Physics3DWorld::removePhysics3DConstraint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_removePhysics3DObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:removePhysics3DObject");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Physics3DObject*)>(&cocos2d::Physics3DWorld::removePhysics3DObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_setDebugDrawEnable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:setDebugDrawEnable");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(bool)>(&cocos2d::Physics3DWorld::setDebugDrawEnable));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_setGhostPairCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:setGhostPairCallback");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Physics3DWorld::*)()>(&cocos2d::Physics3DWorld::setGhostPairCallback));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DWorld_setGravity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:setGravity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DWorld::setGravity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DWorld_stepSimulate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DWorld", "cc.Physics3DWorld:stepSimulate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DWorld::*)(float)>(&cocos2d::Physics3DWorld::stepSimulate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics3D_ccPhysics3DWorld(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DWorld, "Physics3DWorld", "cc.Physics3DWorld",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addPhysics3DConstraint", lua_cocos2d_Physics3DWorld_addPhysics3DConstraint);
	LUA_METHOD("addPhysics3DObject", lua_cocos2d_Physics3DWorld_addPhysics3DObject);
	LUA_METHOD("collisionChecking", lua_cocos2d_Physics3DWorld_collisionChecking);
	LUA_METHOD("debugDraw", lua_cocos2d_Physics3DWorld_debugDraw);
	LUA_METHOD("getGravity", lua_cocos2d_Physics3DWorld_getGravity);
	LUA_METHOD("isDebugDrawEnabled", lua_cocos2d_Physics3DWorld_isDebugDrawEnabled);
	LUA_METHOD("needCollisionChecking", lua_cocos2d_Physics3DWorld_needCollisionChecking);
	LUA_METHOD("removeAllPhysics3DConstraints", lua_cocos2d_Physics3DWorld_removeAllPhysics3DConstraints);
	LUA_METHOD("removeAllPhysics3DObjects", lua_cocos2d_Physics3DWorld_removeAllPhysics3DObjects);
	LUA_METHOD("removePhysics3DConstraint", lua_cocos2d_Physics3DWorld_removePhysics3DConstraint);
	LUA_METHOD("removePhysics3DObject", lua_cocos2d_Physics3DWorld_removePhysics3DObject);
	LUA_METHOD("setDebugDrawEnable", lua_cocos2d_Physics3DWorld_setDebugDrawEnable);
	LUA_METHOD("setGhostPairCallback", lua_cocos2d_Physics3DWorld_setGhostPairCallback);
	LUA_METHOD("setGravity", lua_cocos2d_Physics3DWorld_setGravity);
	LUA_METHOD("stepSimulate", lua_cocos2d_Physics3DWorld_stepSimulate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DConstraint_getBodyA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:getBodyA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DRigidBody*(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::getBodyA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_getBodyB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:getBodyB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DRigidBody*(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::getBodyB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_getBreakingImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:getBreakingImpulse");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::getBreakingImpulse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_getConstraintType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:getConstraintType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DConstraint::ConstraintType(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::getConstraintType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_getOverrideNumSolverIterations(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:getOverrideNumSolverIterations");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::getOverrideNumSolverIterations));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DConstraint::*)()const>(&cocos2d::Physics3DConstraint::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConstraint_setBreakingImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:setBreakingImpulse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConstraint::*)(float)>(&cocos2d::Physics3DConstraint::setBreakingImpulse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConstraint_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConstraint::*)(bool)>(&cocos2d::Physics3DConstraint::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConstraint_setOverrideNumSolverIterations(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConstraint", "cc.Physics3DConstraint:setOverrideNumSolverIterations");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConstraint::*)(int)>(&cocos2d::Physics3DConstraint::setOverrideNumSolverIterations));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Physics3D_ccPhysics3DConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DConstraint, "Physics3DConstraint", "cc.Physics3DConstraint",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBodyA", lua_cocos2d_Physics3DConstraint_getBodyA);
	LUA_METHOD("getBodyB", lua_cocos2d_Physics3DConstraint_getBodyB);
	LUA_METHOD("getBreakingImpulse", lua_cocos2d_Physics3DConstraint_getBreakingImpulse);
	LUA_METHOD("getConstraintType", lua_cocos2d_Physics3DConstraint_getConstraintType);
	LUA_METHOD("getOverrideNumSolverIterations", lua_cocos2d_Physics3DConstraint_getOverrideNumSolverIterations);
	LUA_METHOD("isEnabled", lua_cocos2d_Physics3DConstraint_isEnabled);
	LUA_METHOD("setBreakingImpulse", lua_cocos2d_Physics3DConstraint_setBreakingImpulse);
	LUA_METHOD("setEnabled", lua_cocos2d_Physics3DConstraint_setEnabled);
	LUA_METHOD("setOverrideNumSolverIterations", lua_cocos2d_Physics3DConstraint_setOverrideNumSolverIterations);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DPointToPointConstraint_getPivotPointInA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:getPivotPointInA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DPointToPointConstraint::*)()const>(&cocos2d::Physics3DPointToPointConstraint::getPivotPointInA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DPointToPointConstraint_getPivotPointInB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:getPivotPointInB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3DPointToPointConstraint::*)()const>(&cocos2d::Physics3DPointToPointConstraint::getPivotPointInB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DPointToPointConstraint_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:init");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Physics3DPointToPointConstraint::*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::init)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Physics3DPointToPointConstraint::*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::init)));
	LUA_INVOKE_FOOTER("2,4");
}
int lua_cocos2d_Physics3DPointToPointConstraint_setPivotPointInA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:setPivotPointInA");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DPointToPointConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::setPivotPointInA));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DPointToPointConstraint_setPivotPointInB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:setPivotPointInB");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DPointToPointConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::setPivotPointInB));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DPointToPointConstraint_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Physics3DPointToPointConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Physics3DPointToPointConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Physics3D_ccPhysics3DPointToPointConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DPointToPointConstraint, "Physics3DPointToPointConstraint", "cc.Physics3DPointToPointConstraint",
		cocos2d::Physics3DConstraint, "cc.Physics3DConstraint",
		nullptr, nullptr);
	LUA_METHOD("getPivotPointInA", lua_cocos2d_Physics3DPointToPointConstraint_getPivotPointInA);
	LUA_METHOD("getPivotPointInB", lua_cocos2d_Physics3DPointToPointConstraint_getPivotPointInB);
	LUA_METHOD("init", lua_cocos2d_Physics3DPointToPointConstraint_init);
	LUA_METHOD("setPivotPointInA", lua_cocos2d_Physics3DPointToPointConstraint_setPivotPointInA);
	LUA_METHOD("setPivotPointInB", lua_cocos2d_Physics3DPointToPointConstraint_setPivotPointInB);
	LUA_METHOD("create", lua_cocos2d_Physics3DPointToPointConstraint_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DHingeConstraint_enableAngularMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:enableAngularMotor");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Physics3DHingeConstraint::*)(bool, float, float)>(&cocos2d::Physics3DHingeConstraint::enableAngularMotor)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Physics3DHingeConstraint_enableMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:enableMotor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(bool)>(&cocos2d::Physics3DHingeConstraint::enableMotor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DHingeConstraint_getAFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getAFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getAFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getAngularOnly(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getAngularOnly");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getAngularOnly));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getBFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getBFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getBFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getEnableAngularMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getEnableAngularMotor");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getEnableAngularMotor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getFrameOffsetA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getFrameOffsetA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getFrameOffsetA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getFrameOffsetB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getFrameOffsetB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getFrameOffsetB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getHingeAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getHingeAngle");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocos2d::Physics3DHingeConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DHingeConstraint::getHingeAngle)));
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getHingeAngle));
	LUA_INVOKE_FOOTER("0,2");
}
int lua_cocos2d_Physics3DHingeConstraint_getLowerLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getLowerLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getLowerLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getMaxMotorImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getMaxMotorImpulse");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getMaxMotorImpulse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getMotorTargetVelosity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getMotorTargetVelosity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getMotorTargetVelosity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getUpperLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getUpperLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getUpperLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_getUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:getUseFrameOffset");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DHingeConstraint::*)()const>(&cocos2d::Physics3DHingeConstraint::getUseFrameOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DHingeConstraint_setAngularOnly(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setAngularOnly");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(bool)>(&cocos2d::Physics3DHingeConstraint::setAngularOnly));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DHingeConstraint_setAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setAxis");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3DHingeConstraint::setAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DHingeConstraint_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setFrames");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DHingeConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DHingeConstraint::setFrames)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DHingeConstraint_setLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setLimit");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::Physics3DHingeConstraint::*)(float, float, float, float, float)>(&cocos2d::Physics3DHingeConstraint::setLimit)));
	LUA_TRY_INVOKE(4, ([](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1,float arg2,float arg3){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE(3, ([](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1,float arg2){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE(2, ([](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1){{return obj->setLimit(std::move(arg0),std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4,5");
}
int lua_cocos2d_Physics3DHingeConstraint_setMaxMotorImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setMaxMotorImpulse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(float)>(&cocos2d::Physics3DHingeConstraint::setMaxMotorImpulse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DHingeConstraint_setUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setUseFrameOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(bool)>(&cocos2d::Physics3DHingeConstraint::setUseFrameOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DHingeConstraint_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:create");
	LUA_TRY_INVOKE_R(7, (static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&, cocos2d::Vec3&, cocos2d::Vec3&, bool)>(&cocos2d::Physics3DHingeConstraint::create)));
	LUA_TRY_INVOKE_R(6, ([](cocos2d::Physics3DRigidBody* arg0,cocos2d::Physics3DRigidBody* arg1,const cocos2d::Vec3& arg2,const cocos2d::Vec3& arg3,cocos2d::Vec3& arg4,cocos2d::Vec3& arg5){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2,arg3,arg4,arg5);}}));
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3DHingeConstraint::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](cocos2d::Physics3DRigidBody* arg0,cocos2d::Physics3DRigidBody* arg1,const cocos2d::Mat4& arg2,const cocos2d::Mat4& arg3){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2,arg3);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&, bool)>(&cocos2d::Physics3DHingeConstraint::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cocos2d::Physics3DRigidBody* arg0,const cocos2d::Vec3& arg1,const cocos2d::Vec3& arg2){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3DHingeConstraint::create)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Physics3DRigidBody* arg0,const cocos2d::Mat4& arg1){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3,4,5,6,7");
}
int luaReg_Physics3D_ccPhysics3DHingeConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DHingeConstraint, "Physics3DHingeConstraint", "cc.Physics3DHingeConstraint",
		cocos2d::Physics3DConstraint, "cc.Physics3DConstraint",
		nullptr, nullptr);
	LUA_METHOD("enableAngularMotor", lua_cocos2d_Physics3DHingeConstraint_enableAngularMotor);
	LUA_METHOD("enableMotor", lua_cocos2d_Physics3DHingeConstraint_enableMotor);
	LUA_METHOD("getAFrame", lua_cocos2d_Physics3DHingeConstraint_getAFrame);
	LUA_METHOD("getAngularOnly", lua_cocos2d_Physics3DHingeConstraint_getAngularOnly);
	LUA_METHOD("getBFrame", lua_cocos2d_Physics3DHingeConstraint_getBFrame);
	LUA_METHOD("getEnableAngularMotor", lua_cocos2d_Physics3DHingeConstraint_getEnableAngularMotor);
	LUA_METHOD("getFrameOffsetA", lua_cocos2d_Physics3DHingeConstraint_getFrameOffsetA);
	LUA_METHOD("getFrameOffsetB", lua_cocos2d_Physics3DHingeConstraint_getFrameOffsetB);
	LUA_METHOD("getHingeAngle", lua_cocos2d_Physics3DHingeConstraint_getHingeAngle);
	LUA_METHOD("getLowerLimit", lua_cocos2d_Physics3DHingeConstraint_getLowerLimit);
	LUA_METHOD("getMaxMotorImpulse", lua_cocos2d_Physics3DHingeConstraint_getMaxMotorImpulse);
	LUA_METHOD("getMotorTargetVelosity", lua_cocos2d_Physics3DHingeConstraint_getMotorTargetVelosity);
	LUA_METHOD("getUpperLimit", lua_cocos2d_Physics3DHingeConstraint_getUpperLimit);
	LUA_METHOD("getUseFrameOffset", lua_cocos2d_Physics3DHingeConstraint_getUseFrameOffset);
	LUA_METHOD("setAngularOnly", lua_cocos2d_Physics3DHingeConstraint_setAngularOnly);
	LUA_METHOD("setAxis", lua_cocos2d_Physics3DHingeConstraint_setAxis);
	LUA_METHOD("setFrames", lua_cocos2d_Physics3DHingeConstraint_setFrames);
	LUA_METHOD("setLimit", lua_cocos2d_Physics3DHingeConstraint_setLimit);
	LUA_METHOD("setMaxMotorImpulse", lua_cocos2d_Physics3DHingeConstraint_setMaxMotorImpulse);
	LUA_METHOD("setUseFrameOffset", lua_cocos2d_Physics3DHingeConstraint_setUseFrameOffset);
	LUA_METHOD("create", lua_cocos2d_Physics3DHingeConstraint_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DSliderConstraint_getAngularPos(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getAngularPos");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getAngularPos));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingDirAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingDirAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingDirLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingDirLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingLimAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingLimAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingLimLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingLimLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingOrthoAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingOrthoAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getDampingOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getDampingOrthoLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getDampingOrthoLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getFrameOffsetA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getFrameOffsetA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getFrameOffsetA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getFrameOffsetB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getFrameOffsetB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getFrameOffsetB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getLinearPos(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getLinearPos");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getLinearPos));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getLowerAngLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getLowerAngLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getLowerAngLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getLowerLinLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getLowerLinLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getLowerLinLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getMaxAngMotorForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getMaxAngMotorForce");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getMaxAngMotorForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getMaxLinMotorForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getMaxLinMotorForce");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getMaxLinMotorForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getPoweredAngMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getPoweredAngMotor");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getPoweredAngMotor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getPoweredLinMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getPoweredLinMotor");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getPoweredLinMotor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionDirAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionDirAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionDirLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionDirLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionLimAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionLimAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionLimLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionLimLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionOrthoAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionOrthoAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getRestitutionOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getRestitutionOrthoLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getRestitutionOrthoLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessDirAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessDirAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessDirLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessDirLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessLimAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessLimAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessLimLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessLimLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessOrthoAng");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessOrthoAng));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getSoftnessOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getSoftnessOrthoLin");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getSoftnessOrthoLin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getTargetAngMotorVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getTargetAngMotorVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getTargetAngMotorVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getTargetLinMotorVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getTargetLinMotorVelocity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getTargetLinMotorVelocity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getUpperAngLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getUpperAngLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getUpperAngLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getUpperLinLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getUpperLinLimit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getUpperLinLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getUseFrameOffset");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getUseFrameOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_getUseLinearReferenceFrameA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:getUseLinearReferenceFrameA");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3DSliderConstraint::*)()const>(&cocos2d::Physics3DSliderConstraint::getUseLinearReferenceFrameA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingDirAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingDirAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingDirLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingDirLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingLimAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingLimAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingLimLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingLimLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingOrthoAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingOrthoAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setDampingOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setDampingOrthoLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setDampingOrthoLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setFrames");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DSliderConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DSliderConstraint::setFrames)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DSliderConstraint_setLowerAngLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setLowerAngLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setLowerAngLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setLowerLinLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setLowerLinLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setLowerLinLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setMaxAngMotorForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setMaxAngMotorForce");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setMaxAngMotorForce));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setMaxLinMotorForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setMaxLinMotorForce");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setMaxLinMotorForce));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setPoweredAngMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setPoweredAngMotor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(bool)>(&cocos2d::Physics3DSliderConstraint::setPoweredAngMotor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setPoweredLinMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setPoweredLinMotor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(bool)>(&cocos2d::Physics3DSliderConstraint::setPoweredLinMotor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionDirAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionDirAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionDirLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionDirLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionLimAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionLimAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionLimLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionLimLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionOrthoAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionOrthoAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setRestitutionOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setRestitutionOrthoLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setRestitutionOrthoLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessDirAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessDirAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessDirAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessDirLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessDirLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessDirLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessLimAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessLimAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessLimAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessLimLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessLimLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessLimLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessOrthoAng(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessOrthoAng");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessOrthoAng));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setSoftnessOrthoLin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setSoftnessOrthoLin");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setSoftnessOrthoLin));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setTargetAngMotorVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setTargetAngMotorVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setTargetAngMotorVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setTargetLinMotorVelocity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setTargetLinMotorVelocity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setTargetLinMotorVelocity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setUpperAngLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setUpperAngLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setUpperAngLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setUpperLinLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setUpperLinLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(float)>(&cocos2d::Physics3DSliderConstraint::setUpperLinLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_setUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:setUseFrameOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(bool)>(&cocos2d::Physics3DSliderConstraint::setUseFrameOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DSliderConstraint_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DSliderConstraint", "cc.Physics3DSliderConstraint:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::Physics3DSliderConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3DSliderConstraint::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Physics3D_ccPhysics3DSliderConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DSliderConstraint, "Physics3DSliderConstraint", "cc.Physics3DSliderConstraint",
		cocos2d::Physics3DConstraint, "cc.Physics3DConstraint",
		nullptr, nullptr);
	LUA_METHOD("getAngularPos", lua_cocos2d_Physics3DSliderConstraint_getAngularPos);
	LUA_METHOD("getDampingDirAng", lua_cocos2d_Physics3DSliderConstraint_getDampingDirAng);
	LUA_METHOD("getDampingDirLin", lua_cocos2d_Physics3DSliderConstraint_getDampingDirLin);
	LUA_METHOD("getDampingLimAng", lua_cocos2d_Physics3DSliderConstraint_getDampingLimAng);
	LUA_METHOD("getDampingLimLin", lua_cocos2d_Physics3DSliderConstraint_getDampingLimLin);
	LUA_METHOD("getDampingOrthoAng", lua_cocos2d_Physics3DSliderConstraint_getDampingOrthoAng);
	LUA_METHOD("getDampingOrthoLin", lua_cocos2d_Physics3DSliderConstraint_getDampingOrthoLin);
	LUA_METHOD("getFrameOffsetA", lua_cocos2d_Physics3DSliderConstraint_getFrameOffsetA);
	LUA_METHOD("getFrameOffsetB", lua_cocos2d_Physics3DSliderConstraint_getFrameOffsetB);
	LUA_METHOD("getLinearPos", lua_cocos2d_Physics3DSliderConstraint_getLinearPos);
	LUA_METHOD("getLowerAngLimit", lua_cocos2d_Physics3DSliderConstraint_getLowerAngLimit);
	LUA_METHOD("getLowerLinLimit", lua_cocos2d_Physics3DSliderConstraint_getLowerLinLimit);
	LUA_METHOD("getMaxAngMotorForce", lua_cocos2d_Physics3DSliderConstraint_getMaxAngMotorForce);
	LUA_METHOD("getMaxLinMotorForce", lua_cocos2d_Physics3DSliderConstraint_getMaxLinMotorForce);
	LUA_METHOD("getPoweredAngMotor", lua_cocos2d_Physics3DSliderConstraint_getPoweredAngMotor);
	LUA_METHOD("getPoweredLinMotor", lua_cocos2d_Physics3DSliderConstraint_getPoweredLinMotor);
	LUA_METHOD("getRestitutionDirAng", lua_cocos2d_Physics3DSliderConstraint_getRestitutionDirAng);
	LUA_METHOD("getRestitutionDirLin", lua_cocos2d_Physics3DSliderConstraint_getRestitutionDirLin);
	LUA_METHOD("getRestitutionLimAng", lua_cocos2d_Physics3DSliderConstraint_getRestitutionLimAng);
	LUA_METHOD("getRestitutionLimLin", lua_cocos2d_Physics3DSliderConstraint_getRestitutionLimLin);
	LUA_METHOD("getRestitutionOrthoAng", lua_cocos2d_Physics3DSliderConstraint_getRestitutionOrthoAng);
	LUA_METHOD("getRestitutionOrthoLin", lua_cocos2d_Physics3DSliderConstraint_getRestitutionOrthoLin);
	LUA_METHOD("getSoftnessDirAng", lua_cocos2d_Physics3DSliderConstraint_getSoftnessDirAng);
	LUA_METHOD("getSoftnessDirLin", lua_cocos2d_Physics3DSliderConstraint_getSoftnessDirLin);
	LUA_METHOD("getSoftnessLimAng", lua_cocos2d_Physics3DSliderConstraint_getSoftnessLimAng);
	LUA_METHOD("getSoftnessLimLin", lua_cocos2d_Physics3DSliderConstraint_getSoftnessLimLin);
	LUA_METHOD("getSoftnessOrthoAng", lua_cocos2d_Physics3DSliderConstraint_getSoftnessOrthoAng);
	LUA_METHOD("getSoftnessOrthoLin", lua_cocos2d_Physics3DSliderConstraint_getSoftnessOrthoLin);
	LUA_METHOD("getTargetAngMotorVelocity", lua_cocos2d_Physics3DSliderConstraint_getTargetAngMotorVelocity);
	LUA_METHOD("getTargetLinMotorVelocity", lua_cocos2d_Physics3DSliderConstraint_getTargetLinMotorVelocity);
	LUA_METHOD("getUpperAngLimit", lua_cocos2d_Physics3DSliderConstraint_getUpperAngLimit);
	LUA_METHOD("getUpperLinLimit", lua_cocos2d_Physics3DSliderConstraint_getUpperLinLimit);
	LUA_METHOD("getUseFrameOffset", lua_cocos2d_Physics3DSliderConstraint_getUseFrameOffset);
	LUA_METHOD("getUseLinearReferenceFrameA", lua_cocos2d_Physics3DSliderConstraint_getUseLinearReferenceFrameA);
	LUA_METHOD("setDampingDirAng", lua_cocos2d_Physics3DSliderConstraint_setDampingDirAng);
	LUA_METHOD("setDampingDirLin", lua_cocos2d_Physics3DSliderConstraint_setDampingDirLin);
	LUA_METHOD("setDampingLimAng", lua_cocos2d_Physics3DSliderConstraint_setDampingLimAng);
	LUA_METHOD("setDampingLimLin", lua_cocos2d_Physics3DSliderConstraint_setDampingLimLin);
	LUA_METHOD("setDampingOrthoAng", lua_cocos2d_Physics3DSliderConstraint_setDampingOrthoAng);
	LUA_METHOD("setDampingOrthoLin", lua_cocos2d_Physics3DSliderConstraint_setDampingOrthoLin);
	LUA_METHOD("setFrames", lua_cocos2d_Physics3DSliderConstraint_setFrames);
	LUA_METHOD("setLowerAngLimit", lua_cocos2d_Physics3DSliderConstraint_setLowerAngLimit);
	LUA_METHOD("setLowerLinLimit", lua_cocos2d_Physics3DSliderConstraint_setLowerLinLimit);
	LUA_METHOD("setMaxAngMotorForce", lua_cocos2d_Physics3DSliderConstraint_setMaxAngMotorForce);
	LUA_METHOD("setMaxLinMotorForce", lua_cocos2d_Physics3DSliderConstraint_setMaxLinMotorForce);
	LUA_METHOD("setPoweredAngMotor", lua_cocos2d_Physics3DSliderConstraint_setPoweredAngMotor);
	LUA_METHOD("setPoweredLinMotor", lua_cocos2d_Physics3DSliderConstraint_setPoweredLinMotor);
	LUA_METHOD("setRestitutionDirAng", lua_cocos2d_Physics3DSliderConstraint_setRestitutionDirAng);
	LUA_METHOD("setRestitutionDirLin", lua_cocos2d_Physics3DSliderConstraint_setRestitutionDirLin);
	LUA_METHOD("setRestitutionLimAng", lua_cocos2d_Physics3DSliderConstraint_setRestitutionLimAng);
	LUA_METHOD("setRestitutionLimLin", lua_cocos2d_Physics3DSliderConstraint_setRestitutionLimLin);
	LUA_METHOD("setRestitutionOrthoAng", lua_cocos2d_Physics3DSliderConstraint_setRestitutionOrthoAng);
	LUA_METHOD("setRestitutionOrthoLin", lua_cocos2d_Physics3DSliderConstraint_setRestitutionOrthoLin);
	LUA_METHOD("setSoftnessDirAng", lua_cocos2d_Physics3DSliderConstraint_setSoftnessDirAng);
	LUA_METHOD("setSoftnessDirLin", lua_cocos2d_Physics3DSliderConstraint_setSoftnessDirLin);
	LUA_METHOD("setSoftnessLimAng", lua_cocos2d_Physics3DSliderConstraint_setSoftnessLimAng);
	LUA_METHOD("setSoftnessLimLin", lua_cocos2d_Physics3DSliderConstraint_setSoftnessLimLin);
	LUA_METHOD("setSoftnessOrthoAng", lua_cocos2d_Physics3DSliderConstraint_setSoftnessOrthoAng);
	LUA_METHOD("setSoftnessOrthoLin", lua_cocos2d_Physics3DSliderConstraint_setSoftnessOrthoLin);
	LUA_METHOD("setTargetAngMotorVelocity", lua_cocos2d_Physics3DSliderConstraint_setTargetAngMotorVelocity);
	LUA_METHOD("setTargetLinMotorVelocity", lua_cocos2d_Physics3DSliderConstraint_setTargetLinMotorVelocity);
	LUA_METHOD("setUpperAngLimit", lua_cocos2d_Physics3DSliderConstraint_setUpperAngLimit);
	LUA_METHOD("setUpperLinLimit", lua_cocos2d_Physics3DSliderConstraint_setUpperLinLimit);
	LUA_METHOD("setUseFrameOffset", lua_cocos2d_Physics3DSliderConstraint_setUseFrameOffset);
	LUA_METHOD("create", lua_cocos2d_Physics3DSliderConstraint_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DConeTwistConstraint_GetPointForAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:GetPointForAngle");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Vec3(cocos2d::Physics3DConeTwistConstraint::*)(float, float)const>(&cocos2d::Physics3DConeTwistConstraint::GetPointForAngle)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DConeTwistConstraint_enableMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:enableMotor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(bool)>(&cocos2d::Physics3DConeTwistConstraint::enableMotor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getAFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getAFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getAFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getBFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getBFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getBFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getFixThresh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getFixThresh");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getFixThresh));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getFrameOffsetA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getFrameOffsetA");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getFrameOffsetA));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getFrameOffsetB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getFrameOffsetB");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getFrameOffsetB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getSwingSpan1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getSwingSpan1");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getSwingSpan1));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getSwingSpan2(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getSwingSpan2");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getSwingSpan2));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getTwistAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getTwistAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getTwistAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_getTwistSpan(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:getTwistSpan");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Physics3DConeTwistConstraint::*)()const>(&cocos2d::Physics3DConeTwistConstraint::getTwistSpan));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setDamping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setDamping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float)>(&cocos2d::Physics3DConeTwistConstraint::setDamping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setFixThresh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setFixThresh");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float)>(&cocos2d::Physics3DConeTwistConstraint::setFixThresh));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setFrames");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::setFrames)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setLimit");
	LUA_TRY_INVOKE(6, (static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float, float, float, float, float, float)>(&cocos2d::Physics3DConeTwistConstraint::setLimit)));
	LUA_TRY_INVOKE(5, ([](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2,float arg3,float arg4){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}}));
	LUA_TRY_INVOKE(4, ([](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2,float arg3){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE(3, ([](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4,5,6");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setMaxMotorImpulse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setMaxMotorImpulse");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float)>(&cocos2d::Physics3DConeTwistConstraint::setMaxMotorImpulse));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setMaxMotorImpulseNormalized");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float)>(&cocos2d::Physics3DConeTwistConstraint::setMaxMotorImpulseNormalized));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3DConeTwistConstraint_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Physics3DConeTwistConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Physics3DConeTwistConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Physics3D_ccPhysics3DConeTwistConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3DConeTwistConstraint, "Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint",
		cocos2d::Physics3DConstraint, "cc.Physics3DConstraint",
		nullptr, nullptr);
	LUA_METHOD("GetPointForAngle", lua_cocos2d_Physics3DConeTwistConstraint_GetPointForAngle);
	LUA_METHOD("enableMotor", lua_cocos2d_Physics3DConeTwistConstraint_enableMotor);
	LUA_METHOD("getAFrame", lua_cocos2d_Physics3DConeTwistConstraint_getAFrame);
	LUA_METHOD("getBFrame", lua_cocos2d_Physics3DConeTwistConstraint_getBFrame);
	LUA_METHOD("getFixThresh", lua_cocos2d_Physics3DConeTwistConstraint_getFixThresh);
	LUA_METHOD("getFrameOffsetA", lua_cocos2d_Physics3DConeTwistConstraint_getFrameOffsetA);
	LUA_METHOD("getFrameOffsetB", lua_cocos2d_Physics3DConeTwistConstraint_getFrameOffsetB);
	LUA_METHOD("getSwingSpan1", lua_cocos2d_Physics3DConeTwistConstraint_getSwingSpan1);
	LUA_METHOD("getSwingSpan2", lua_cocos2d_Physics3DConeTwistConstraint_getSwingSpan2);
	LUA_METHOD("getTwistAngle", lua_cocos2d_Physics3DConeTwistConstraint_getTwistAngle);
	LUA_METHOD("getTwistSpan", lua_cocos2d_Physics3DConeTwistConstraint_getTwistSpan);
	LUA_METHOD("setDamping", lua_cocos2d_Physics3DConeTwistConstraint_setDamping);
	LUA_METHOD("setFixThresh", lua_cocos2d_Physics3DConeTwistConstraint_setFixThresh);
	LUA_METHOD("setFrames", lua_cocos2d_Physics3DConeTwistConstraint_setFrames);
	LUA_METHOD("setLimit", lua_cocos2d_Physics3DConeTwistConstraint_setLimit);
	LUA_METHOD("setMaxMotorImpulse", lua_cocos2d_Physics3DConeTwistConstraint_setMaxMotorImpulse);
	LUA_METHOD("setMaxMotorImpulseNormalized", lua_cocos2d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized);
	LUA_METHOD("create", lua_cocos2d_Physics3DConeTwistConstraint_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3D6DofConstraint_getAngularLowerLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:getAngularLowerLimit");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3D6DofConstraint::*)()const>(&cocos2d::Physics3D6DofConstraint::getAngularLowerLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3D6DofConstraint_getAngularUpperLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:getAngularUpperLimit");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3D6DofConstraint::*)()const>(&cocos2d::Physics3D6DofConstraint::getAngularUpperLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3D6DofConstraint_getLinearLowerLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:getLinearLowerLimit");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3D6DofConstraint::*)()const>(&cocos2d::Physics3D6DofConstraint::getLinearLowerLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3D6DofConstraint_getLinearUpperLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:getLinearUpperLimit");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Physics3D6DofConstraint::*)()const>(&cocos2d::Physics3D6DofConstraint::getLinearUpperLimit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3D6DofConstraint_getUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:getUseFrameOffset");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Physics3D6DofConstraint::*)()const>(&cocos2d::Physics3D6DofConstraint::getUseFrameOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Physics3D6DofConstraint_isLimited(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:isLimited");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Physics3D6DofConstraint::*)(int)const>(&cocos2d::Physics3D6DofConstraint::isLimited));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_setAngularLowerLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:setAngularLowerLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3D6DofConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3D6DofConstraint::setAngularLowerLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_setAngularUpperLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:setAngularUpperLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3D6DofConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3D6DofConstraint::setAngularUpperLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_setLinearLowerLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:setLinearLowerLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3D6DofConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3D6DofConstraint::setLinearLowerLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_setLinearUpperLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:setLinearUpperLimit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3D6DofConstraint::*)(const cocos2d::Vec3&)>(&cocos2d::Physics3D6DofConstraint::setLinearUpperLimit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_setUseFrameOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:setUseFrameOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Physics3D6DofConstraint::*)(bool)const>(&cocos2d::Physics3D6DofConstraint::setUseFrameOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Physics3D6DofConstraint_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Physics3D6DofConstraint", "cc.Physics3D6DofConstraint:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::Physics3D6DofConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3D6DofConstraint::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Physics3D6DofConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3D6DofConstraint::create)));
	LUA_SINVOKE_FOOTER("3,5");
}
int luaReg_Physics3D_ccPhysics3D6DofConstraint(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Physics3D6DofConstraint, "Physics3D6DofConstraint", "cc.Physics3D6DofConstraint",
		cocos2d::Physics3DConstraint, "cc.Physics3DConstraint",
		nullptr, nullptr);
	LUA_METHOD("getAngularLowerLimit", lua_cocos2d_Physics3D6DofConstraint_getAngularLowerLimit);
	LUA_METHOD("getAngularUpperLimit", lua_cocos2d_Physics3D6DofConstraint_getAngularUpperLimit);
	LUA_METHOD("getLinearLowerLimit", lua_cocos2d_Physics3D6DofConstraint_getLinearLowerLimit);
	LUA_METHOD("getLinearUpperLimit", lua_cocos2d_Physics3D6DofConstraint_getLinearUpperLimit);
	LUA_METHOD("getUseFrameOffset", lua_cocos2d_Physics3D6DofConstraint_getUseFrameOffset);
	LUA_METHOD("isLimited", lua_cocos2d_Physics3D6DofConstraint_isLimited);
	LUA_METHOD("setAngularLowerLimit", lua_cocos2d_Physics3D6DofConstraint_setAngularLowerLimit);
	LUA_METHOD("setAngularUpperLimit", lua_cocos2d_Physics3D6DofConstraint_setAngularUpperLimit);
	LUA_METHOD("setLinearLowerLimit", lua_cocos2d_Physics3D6DofConstraint_setLinearLowerLimit);
	LUA_METHOD("setLinearUpperLimit", lua_cocos2d_Physics3D6DofConstraint_setLinearUpperLimit);
	LUA_METHOD("setUseFrameOffset", lua_cocos2d_Physics3D6DofConstraint_setUseFrameOffset);
	LUA_METHOD("create", lua_cocos2d_Physics3D6DofConstraint_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_physics3d_retained(lua_State* lua_S);

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
