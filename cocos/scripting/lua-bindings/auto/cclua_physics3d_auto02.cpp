#include "cclua_physics3d_auto.hpp"
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "scripting/lua-bindings/manual/physics3d/cclua_physics3d_compat.hpp"
#include "physics3d/CCPhysics3D.h"

int lua_cocos2d_Physics3DHingeConstraint_enableAngularMotor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:enableAngularMotor");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(bool, float, float)>(&cocos2d::Physics3DHingeConstraint::enableAngularMotor));
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
	LUA_TRY_INVOKE_R(2, static_cast<float(cocos2d::Physics3DHingeConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DHingeConstraint::getHingeAngle));
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DHingeConstraint::setFrames));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DHingeConstraint_setLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DHingeConstraint", "cc.Physics3DHingeConstraint:setLimit");
	LUA_TRY_INVOKE(5, static_cast<void(cocos2d::Physics3DHingeConstraint::*)(float, float, float, float, float)>(&cocos2d::Physics3DHingeConstraint::setLimit));
	LUA_TRY_INVOKE(4, [](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1,float arg2,float arg3){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}});
	LUA_TRY_INVOKE(3, [](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1,float arg2){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2));}});
	LUA_TRY_INVOKE(2, [](cocos2d::Physics3DHingeConstraint* obj,float arg0,float arg1){{return obj->setLimit(std::move(arg0),std::move(arg1));}});
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
	LUA_TRY_INVOKE_R(7, static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&, cocos2d::Vec3&, cocos2d::Vec3&, bool)>(&cocos2d::Physics3DHingeConstraint::create));
	LUA_TRY_INVOKE_R(6, [](cocos2d::Physics3DRigidBody* arg0,cocos2d::Physics3DRigidBody* arg1,const cocos2d::Vec3& arg2,const cocos2d::Vec3& arg3,cocos2d::Vec3& arg4,cocos2d::Vec3& arg5){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2,arg3,arg4,arg5);}});
	LUA_TRY_INVOKE_R(5, static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3DHingeConstraint::create));
	LUA_TRY_INVOKE_R_OVERLOAD(4, [](cocos2d::Physics3DRigidBody* arg0,cocos2d::Physics3DRigidBody* arg1,const cocos2d::Mat4& arg2,const cocos2d::Mat4& arg3){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2,arg3);}});
	LUA_TRY_INVOKE_R_OVERLOAD(4, static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Vec3&, const cocos2d::Vec3&, bool)>(&cocos2d::Physics3DHingeConstraint::create));
	LUA_TRY_INVOKE_R_OVERLOAD(3, [](cocos2d::Physics3DRigidBody* arg0,const cocos2d::Vec3& arg1,const cocos2d::Vec3& arg2){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1,arg2);}});
	LUA_TRY_INVOKE_R_OVERLOAD(3, static_cast<cocos2d::Physics3DHingeConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3DHingeConstraint::create));
	LUA_TRY_INVOKE_R(2, [](cocos2d::Physics3DRigidBody* arg0,const cocos2d::Mat4& arg1){{return cocos2d::Physics3DHingeConstraint::create(arg0,arg1);}});
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DSliderConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DSliderConstraint::setFrames));
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
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Physics3DConeTwistConstraint_GetPointForAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:GetPointForAngle");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Vec3(cocos2d::Physics3DConeTwistConstraint::*)(float, float)const>(&cocos2d::Physics3DConeTwistConstraint::GetPointForAngle));
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::setFrames));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Physics3DConeTwistConstraint_setLimit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Physics3DConeTwistConstraint", "cc.Physics3DConeTwistConstraint:setLimit");
	LUA_TRY_INVOKE(6, static_cast<void(cocos2d::Physics3DConeTwistConstraint::*)(float, float, float, float, float, float)>(&cocos2d::Physics3DConeTwistConstraint::setLimit));
	LUA_TRY_INVOKE(5, [](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2,float arg3,float arg4){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3),std::move(arg4));}});
	LUA_TRY_INVOKE(4, [](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2,float arg3){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}});
	LUA_TRY_INVOKE(3, [](cocos2d::Physics3DConeTwistConstraint* obj,float arg0,float arg1,float arg2){{return obj->setLimit(std::move(arg0),std::move(arg1),std::move(arg2));}});
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
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::Physics3DConeTwistConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::create));
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Physics3DConeTwistConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&)>(&cocos2d::Physics3DConeTwistConstraint::create));
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
	LUA_TRY_INVOKE_R(5, static_cast<cocos2d::Physics3D6DofConstraint*(*)(cocos2d::Physics3DRigidBody*, cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3D6DofConstraint::create));
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::Physics3D6DofConstraint*(*)(cocos2d::Physics3DRigidBody*, const cocos2d::Mat4&, bool)>(&cocos2d::Physics3D6DofConstraint::create));
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
