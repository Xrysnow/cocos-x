#include "cclua_physics3d_auto.hpp"
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "scripting/lua-bindings/manual/physics3d/cclua_physics3d_compat.hpp"
#include "physics3d/CCPhysics3D.h"

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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DWorld::*)(cocos2d::Physics3DConstraint*, bool)>(&cocos2d::Physics3DWorld::addPhysics3DConstraint));
	LUA_TRY_INVOKE(1, [](cocos2d::Physics3DWorld* obj,cocos2d::Physics3DConstraint* arg0){{return obj->addPhysics3DConstraint(arg0);}});
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
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::Physics3DPointToPointConstraint::*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::init));
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Physics3DPointToPointConstraint::*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::init));
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
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::Physics3DPointToPointConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Physics3DPointToPointConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&)>(&cocos2d::Physics3DPointToPointConstraint::create));
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
#endif
