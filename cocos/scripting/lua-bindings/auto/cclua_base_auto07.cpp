#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"

int lua_cocos2d_BaseLight_getIntensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getIntensity");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::BaseLight::*)()const>(&cocos2d::BaseLight::getIntensity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_BaseLight_getLightFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getLightFlag");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::LightFlag(cocos2d::BaseLight::*)()const>(&cocos2d::BaseLight::getLightFlag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_BaseLight_getLightType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getLightType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::LightType(cocos2d::BaseLight::*)()const>(&cocos2d::BaseLight::getLightType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_BaseLight_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::BaseLight::*)()const>(&cocos2d::BaseLight::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_BaseLight_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::BaseLight::*)(bool)>(&cocos2d::BaseLight::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_BaseLight_setIntensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setIntensity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::BaseLight::*)(float)>(&cocos2d::BaseLight::setIntensity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_BaseLight_setLightFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setLightFlag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::BaseLight::*)(cocos2d::LightFlag)>(&cocos2d::BaseLight::setLightFlag));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccBaseLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BaseLight, "BaseLight", "cc.BaseLight",
		cocos2d::BaseLight, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getIntensity", lua_cocos2d_BaseLight_getIntensity);
	LUA_METHOD("getLightFlag", lua_cocos2d_BaseLight_getLightFlag);
	LUA_METHOD("getLightType", lua_cocos2d_BaseLight_getLightType);
	LUA_METHOD("isEnabled", lua_cocos2d_BaseLight_isEnabled);
	LUA_METHOD("setEnabled", lua_cocos2d_BaseLight_setEnabled);
	LUA_METHOD("setIntensity", lua_cocos2d_BaseLight_setIntensity);
	LUA_METHOD("setLightFlag", lua_cocos2d_BaseLight_setLightFlag);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_DirectionLight_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:getDirection");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::DirectionLight::*)()const>(&cocos2d::DirectionLight::getDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_DirectionLight_getDirectionInWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:getDirectionInWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::DirectionLight::*)()const>(&cocos2d::DirectionLight::getDirectionInWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_DirectionLight_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:setDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::DirectionLight::*)(const cocos2d::Vec3&)>(&cocos2d::DirectionLight::setDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_DirectionLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::DirectionLight*(*)(const cocos2d::Vec3&, const cocos2d::Color3B&)>(&cocos2d::DirectionLight::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccDirectionLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DirectionLight, "DirectionLight", "cc.DirectionLight",
		cocos2d::DirectionLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getDirection", lua_cocos2d_DirectionLight_getDirection);
	LUA_METHOD("getDirectionInWorld", lua_cocos2d_DirectionLight_getDirectionInWorld);
	LUA_METHOD("setDirection", lua_cocos2d_DirectionLight_setDirection);
	LUA_METHOD("create", lua_cocos2d_DirectionLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_PointLight_getRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PointLight", "cc.PointLight:getRange");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::PointLight::*)()const>(&cocos2d::PointLight::getRange));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_PointLight_setRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PointLight", "cc.PointLight:setRange");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::PointLight::*)(float)>(&cocos2d::PointLight::setRange));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_PointLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PointLight", "cc.PointLight:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::PointLight*(*)(const cocos2d::Vec3&, const cocos2d::Color3B&, float)>(&cocos2d::PointLight::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccPointLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PointLight, "PointLight", "cc.PointLight",
		cocos2d::PointLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getRange", lua_cocos2d_PointLight_getRange);
	LUA_METHOD("setRange", lua_cocos2d_PointLight_setRange);
	LUA_METHOD("create", lua_cocos2d_PointLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpotLight_getCosInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getCosInnerAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getCosInnerAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getCosOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getCosOuterAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getCosOuterAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getDirection");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getDirectionInWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getDirectionInWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getDirectionInWorld));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getInnerAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getInnerAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getOuterAngle");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getOuterAngle));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_getRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getRange");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::SpotLight::*)()const>(&cocos2d::SpotLight::getRange));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpotLight_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpotLight::*)(const cocos2d::Vec3&)>(&cocos2d::SpotLight::setDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpotLight_setInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setInnerAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpotLight::*)(float)>(&cocos2d::SpotLight::setInnerAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpotLight_setOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setOuterAngle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpotLight::*)(float)>(&cocos2d::SpotLight::setOuterAngle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpotLight_setRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setRange");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpotLight::*)(float)>(&cocos2d::SpotLight::setRange));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpotLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpotLight", "cc.SpotLight:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::SpotLight*(*)(const cocos2d::Vec3&, const cocos2d::Vec3&, const cocos2d::Color3B&, float, float, float)>(&cocos2d::SpotLight::create)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccSpotLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpotLight, "SpotLight", "cc.SpotLight",
		cocos2d::SpotLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getCosInnerAngle", lua_cocos2d_SpotLight_getCosInnerAngle);
	LUA_METHOD("getCosOuterAngle", lua_cocos2d_SpotLight_getCosOuterAngle);
	LUA_METHOD("getDirection", lua_cocos2d_SpotLight_getDirection);
	LUA_METHOD("getDirectionInWorld", lua_cocos2d_SpotLight_getDirectionInWorld);
	LUA_METHOD("getInnerAngle", lua_cocos2d_SpotLight_getInnerAngle);
	LUA_METHOD("getOuterAngle", lua_cocos2d_SpotLight_getOuterAngle);
	LUA_METHOD("getRange", lua_cocos2d_SpotLight_getRange);
	LUA_METHOD("setDirection", lua_cocos2d_SpotLight_setDirection);
	LUA_METHOD("setInnerAngle", lua_cocos2d_SpotLight_setInnerAngle);
	LUA_METHOD("setOuterAngle", lua_cocos2d_SpotLight_setOuterAngle);
	LUA_METHOD("setRange", lua_cocos2d_SpotLight_setRange);
	LUA_METHOD("create", lua_cocos2d_SpotLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AmbientLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AmbientLight", "cc.AmbientLight:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::AmbientLight*(*)(const cocos2d::Color3B&)>(&cocos2d::AmbientLight::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAmbientLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AmbientLight, "AmbientLight", "cc.AmbientLight",
		cocos2d::AmbientLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_AmbientLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RenderState_bindPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderState", "cc.RenderState:bindPass");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::RenderState::*)(cocos2d::Pass*, cocos2d::MeshCommand*)>(&cocos2d::RenderState::bindPass)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_RenderState_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderState", "cc.RenderState:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::RenderState::*)()const>(&cocos2d::RenderState::getName));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccRenderState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RenderState, "RenderState", "cc.RenderState",
		cocos2d::RenderState, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("bindPass", lua_cocos2d_RenderState_bindPass);
	LUA_METHOD("getName", lua_cocos2d_RenderState_getName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Technique_addPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:addPass");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Technique::*)(cocos2d::Pass*)>(&cocos2d::Technique::addPass));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Technique_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Technique*(cocos2d::Technique::*)()const>(&cocos2d::Technique::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Technique_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Technique::*)()const>(&cocos2d::Technique::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Technique_getPassByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPassByIndex");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Pass*(cocos2d::Technique::*)(ssize_t)const>(&cocos2d::Technique::getPassByIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Technique_getPassCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPassCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Technique::*)()const>(&cocos2d::Technique::getPassCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Technique_getPasses(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPasses");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::Pass *>&(cocos2d::Technique::*)()const>(&cocos2d::Technique::getPasses));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Technique_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:setMaterial");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Technique::*)(cocos2d::Material*)>(&cocos2d::Technique::setMaterial));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Technique_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Technique", "cc.Technique:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Technique*(*)(cocos2d::Material*)>(&cocos2d::Technique::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Technique_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Technique", "cc.Technique:createWithProgramState");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Technique*(*)(cocos2d::Material*, cocos2d::backend::ProgramState*)>(&cocos2d::Technique::createWithProgramState)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTechnique(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Technique, "Technique", "cc.Technique",
		cocos2d::Technique, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addPass", lua_cocos2d_Technique_addPass);
	LUA_METHOD("clone", lua_cocos2d_Technique_clone);
	LUA_METHOD("getName", lua_cocos2d_Technique_getName);
	LUA_METHOD("getPassByIndex", lua_cocos2d_Technique_getPassByIndex);
	LUA_METHOD("getPassCount", lua_cocos2d_Technique_getPassCount);
	LUA_METHOD("getPasses", lua_cocos2d_Technique_getPasses);
	LUA_METHOD("setMaterial", lua_cocos2d_Technique_setMaterial);
	LUA_METHOD("create", lua_cocos2d_Technique_create);
	LUA_METHOD("createWithProgramState", lua_cocos2d_Technique_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Material_addTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:addTechnique");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(cocos2d::Technique*)>(&cocos2d::Material::addTechnique));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Material*(cocos2d::Material::*)()const>(&cocos2d::Material::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:draw");
	LUA_TRY_INVOKE(8, (static_cast<void(cocos2d::Material::*)(cocos2d::MeshCommand*, float, cocos2d::backend::Buffer*, cocos2d::backend::Buffer*, cocos2d::CustomCommand::PrimitiveType, cocos2d::CustomCommand::IndexFormat, unsigned int, const cocos2d::Mat4&)>(&cocos2d::Material::draw)));
	LUA_INVOKE_FOOTER("8");
}
int lua_cocos2d_Material_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Material::*)()const>(&cocos2d::Material::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_getPrimitiveType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getPrimitiveType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::PrimitiveType(cocos2d::Material::*)()const>(&cocos2d::Material::getPrimitiveType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_getRenderState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getRenderState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::RenderState*(cocos2d::Material::*)()>(&cocos2d::Material::getRenderState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_getTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechnique");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Technique*(cocos2d::Material::*)()const>(&cocos2d::Material::getTechnique));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_getTechniqueByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueByIndex");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Technique*(cocos2d::Material::*)(ssize_t)>(&cocos2d::Material::getTechniqueByIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_getTechniqueByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueByName");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Technique*(cocos2d::Material::*)(std::string_view)>(&cocos2d::Material::getTechniqueByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_getTechniqueCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Material::*)()const>(&cocos2d::Material::getTechniqueCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_getTechniques(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniques");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::Technique *>&(cocos2d::Material::*)()const>(&cocos2d::Material::getTechniques));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_isForce2DQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:isForce2DQueue");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Material::*)()const>(&cocos2d::Material::isForce2DQueue));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_isTransparent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:isTransparent");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Material::*)()const>(&cocos2d::Material::isTransparent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Material_setForce2DQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setForce2DQueue");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(bool)>(&cocos2d::Material::setForce2DQueue));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(std::string_view)>(&cocos2d::Material::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_setPrimitiveType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setPrimitiveType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(cocos2d::backend::PrimitiveType)>(&cocos2d::Material::setPrimitiveType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_setTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setTechnique");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(std::string_view)>(&cocos2d::Material::setTechnique));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_setTransparent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setTransparent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Material::*)(bool)>(&cocos2d::Material::setTransparent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Material_createWithFilename(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Material", "cc.Material:createWithFilename");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Material*(*)(std::string_view)>(&cocos2d::Material::createWithFilename));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Material_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Material", "cc.Material:createWithProgramState");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Material*(*)(cocos2d::backend::ProgramState*)>(&cocos2d::Material::createWithProgramState));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMaterial(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Material, "Material", "cc.Material",
		cocos2d::Material, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addTechnique", lua_cocos2d_Material_addTechnique);
	LUA_METHOD("clone", lua_cocos2d_Material_clone);
	LUA_METHOD("draw", lua_cocos2d_Material_draw);
	LUA_METHOD("getName", lua_cocos2d_Material_getName);
	LUA_METHOD("getPrimitiveType", lua_cocos2d_Material_getPrimitiveType);
	LUA_METHOD("getRenderState", lua_cocos2d_Material_getRenderState);
	LUA_METHOD("getTechnique", lua_cocos2d_Material_getTechnique);
	LUA_METHOD("getTechniqueByIndex", lua_cocos2d_Material_getTechniqueByIndex);
	LUA_METHOD("getTechniqueByName", lua_cocos2d_Material_getTechniqueByName);
	LUA_METHOD("getTechniqueCount", lua_cocos2d_Material_getTechniqueCount);
	LUA_METHOD("getTechniques", lua_cocos2d_Material_getTechniques);
	LUA_METHOD("isForce2DQueue", lua_cocos2d_Material_isForce2DQueue);
	LUA_METHOD("isTransparent", lua_cocos2d_Material_isTransparent);
	LUA_METHOD("setForce2DQueue", lua_cocos2d_Material_setForce2DQueue);
	LUA_METHOD("setName", lua_cocos2d_Material_setName);
	LUA_METHOD("setPrimitiveType", lua_cocos2d_Material_setPrimitiveType);
	LUA_METHOD("setTechnique", lua_cocos2d_Material_setTechnique);
	LUA_METHOD("setTransparent", lua_cocos2d_Material_setTransparent);
	LUA_METHOD("createWithFilename", lua_cocos2d_Material_createWithFilename);
	LUA_METHOD("createWithProgramState", lua_cocos2d_Material_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Pass_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Pass*(cocos2d::Pass::*)()const>(&cocos2d::Pass::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Pass_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:draw");
	LUA_TRY_INVOKE(8, (static_cast<void(cocos2d::Pass::*)(cocos2d::MeshCommand*, float, cocos2d::backend::Buffer*, cocos2d::backend::Buffer*, cocos2d::CustomCommand::PrimitiveType, cocos2d::MeshCommand::IndexFormat, unsigned int, const cocos2d::Mat4&)>(&cocos2d::Pass::draw)));
	LUA_INVOKE_FOOTER("8");
}
int lua_cocos2d_Pass_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Pass::*)()const>(&cocos2d::Pass::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Pass_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getProgramState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::ProgramState*(cocos2d::Pass::*)()const>(&cocos2d::Pass::getProgramState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Pass_getVertexAttributeBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getVertexAttributeBinding");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::VertexAttribBinding*(cocos2d::Pass::*)()const>(&cocos2d::Pass::getVertexAttributeBinding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Pass_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Pass::*)(std::string_view)>(&cocos2d::Pass::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Pass_setTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setTechnique");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Pass::*)(cocos2d::Technique*)>(&cocos2d::Pass::setTechnique));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Pass_setUniformNormTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setUniformNormTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Pass::*)(uint32_t, cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformNormTexture)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Pass_setUniformTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setUniformTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Pass::*)(uint32_t, cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformTexture)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Pass_setVertexAttribBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setVertexAttribBinding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Pass::*)(cocos2d::VertexAttribBinding*)>(&cocos2d::Pass::setVertexAttribBinding));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Pass_updateMVPUniform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:updateMVPUniform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Pass::*)(const cocos2d::Mat4&)>(&cocos2d::Pass::updateMVPUniform));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Pass_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Pass", "cc.Pass:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Pass*(*)(cocos2d::Technique*)>(&cocos2d::Pass::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Pass_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Pass", "cc.Pass:createWithProgramState");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Pass*(*)(cocos2d::Technique*, cocos2d::backend::ProgramState*)>(&cocos2d::Pass::createWithProgramState)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccPass(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Pass, "Pass", "cc.Pass",
		cocos2d::Pass, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_Pass_clone);
	LUA_METHOD("draw", lua_cocos2d_Pass_draw);
	LUA_METHOD("getName", lua_cocos2d_Pass_getName);
	LUA_METHOD("getProgramState", lua_cocos2d_Pass_getProgramState);
	LUA_METHOD("getVertexAttributeBinding", lua_cocos2d_Pass_getVertexAttributeBinding);
	LUA_METHOD("setName", lua_cocos2d_Pass_setName);
	LUA_METHOD("setTechnique", lua_cocos2d_Pass_setTechnique);
	LUA_METHOD("setUniformNormTexture", lua_cocos2d_Pass_setUniformNormTexture);
	LUA_METHOD("setUniformTexture", lua_cocos2d_Pass_setUniformTexture);
	LUA_METHOD("setVertexAttribBinding", lua_cocos2d_Pass_setVertexAttribBinding);
	LUA_METHOD("updateMVPUniform", lua_cocos2d_Pass_updateMVPUniform);
	LUA_METHOD("create", lua_cocos2d_Pass_create);
	LUA_METHOD("createWithProgramState", lua_cocos2d_Pass_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Renderer_addCallbackCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addCallbackCommand");
	if (argc == 2 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Renderer::*)(std::function<void()>, float)>(&cocos2d::Renderer::addCallbackCommand)));
	}
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, ([](cocos2d::Renderer* obj,std::function<void()> arg0){{return obj->addCallbackCommand(std::move(arg0));}}));
	}
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Renderer_addCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addCommand");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Renderer::*)(cocos2d::RenderCommand*, int)>(&cocos2d::Renderer::addCommand)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(cocos2d::RenderCommand*)>(&cocos2d::Renderer::addCommand));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Renderer_addDrawnBatches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addDrawnBatches");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(ssize_t)>(&cocos2d::Renderer::addDrawnBatches));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_addDrawnVertices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addDrawnVertices");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(ssize_t)>(&cocos2d::Renderer::addDrawnVertices));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_beginRenderPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:beginRenderPass");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::beginRenderPass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_checkVisibility(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:checkVisibility");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Renderer::*)(const cocos2d::Mat4&, const cocos2d::Vec2&)>(&cocos2d::Renderer::checkVisibility)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Renderer_clean(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clean");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::clean));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clear");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::Renderer::*)(cocos2d::ClearFlag, const cocos2d::Color4F&, float, unsigned int, float)>(&cocos2d::Renderer::clear)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_Renderer_clearDrawStats(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clearDrawStats");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::clearDrawStats));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_createRenderQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:createRenderQueue");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Renderer::*)()>(&cocos2d::Renderer::createRenderQueue));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_endRenderPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:endRenderPass");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::endRenderPass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearDepth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearDepth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getClearFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearFlag");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ClearFlag(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearFlag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearStencil");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearStencil));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getCullMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getCullMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CullMode(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getCullMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDefaultRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDefaultRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::RenderTarget*(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDefaultRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDepthCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthCompareFunction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::CompareFunction(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthCompareFunction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDepthTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthTest");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthTest));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthWrite");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthWrite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDrawnBatches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDrawnBatches");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDrawnBatches));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getDrawnVertices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDrawnVertices");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDrawnVertices));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getNextGroupCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getNextGroupCommand");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::GroupCommand*(cocos2d::Renderer::*)()>(&cocos2d::Renderer::getNextGroupCommand));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getOffscreenRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getOffscreenRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::RenderTarget*(cocos2d::Renderer::*)()>(&cocos2d::Renderer::getOffscreenRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::RenderTarget*(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getRenderTargetFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getRenderTargetFlag");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::RenderTargetFlag(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getRenderTargetFlag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getScissorTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getScissorTest");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getScissorTest));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilCompareFunction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::CompareFunction(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilCompareFunction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilDepthPassOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilDepthPassOperation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilDepthPassOperation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilFailureOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilFailureOperation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilFailureOperation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilPassDepthFailureOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilPassDepthFailureOperation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilPassDepthFailureOperation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilReadMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilReadMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilReadMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilReferenceValue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilReferenceValue");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilReferenceValue));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilTest");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilTest));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getStencilWriteMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilWriteMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilWriteMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_getWinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getWinding");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Winding(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getWinding));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_nextCallbackCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:nextCallbackCommand");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CallbackCommand*(cocos2d::Renderer::*)()>(&cocos2d::Renderer::nextCallbackCommand));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_popGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:popGroup");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::popGroup));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_pushGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:pushGroup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(int)>(&cocos2d::Renderer::pushGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_render(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:render");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::render));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_setCullMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setCullMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(cocos2d::CullMode)>(&cocos2d::Renderer::setCullMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setDepthCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthCompareFunction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::CompareFunction)>(&cocos2d::Renderer::setDepthCompareFunction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setDepthTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthTest");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setDepthTest));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthWrite");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setDepthWrite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setRenderTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::RenderTarget*)>(&cocos2d::Renderer::setRenderTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setScissorRect");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::Renderer::*)(float, float, float, float)>(&cocos2d::Renderer::setScissorRect)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Renderer_setScissorTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setScissorTest");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setScissorTest));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setStencilCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilCompareFunction");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::CompareFunction, unsigned int, unsigned int)>(&cocos2d::Renderer::setStencilCompareFunction)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Renderer_setStencilOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilOperation");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::StencilOperation, cocos2d::backend::StencilOperation, cocos2d::backend::StencilOperation)>(&cocos2d::Renderer::setStencilOperation)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Renderer_setStencilTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilTest");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setStencilTest));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setStencilWriteMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilWriteMask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(unsigned int)>(&cocos2d::Renderer::setStencilWriteMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Renderer_setViewPort(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setViewPort");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::Renderer::*)(int, int, unsigned int, unsigned int)>(&cocos2d::Renderer::setViewPort)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Renderer_setWinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setWinding");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Renderer::*)(cocos2d::Winding)>(&cocos2d::Renderer::setWinding));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Renderer, "Renderer", "cc.Renderer",
		cocos2d::Renderer, "",
		nullptr, nullptr);
	LUA_METHOD("addCallbackCommand", lua_cocos2d_Renderer_addCallbackCommand);
	LUA_METHOD("addCommand", lua_cocos2d_Renderer_addCommand);
	LUA_METHOD("addDrawnBatches", lua_cocos2d_Renderer_addDrawnBatches);
	LUA_METHOD("addDrawnVertices", lua_cocos2d_Renderer_addDrawnVertices);
	LUA_METHOD("beginRenderPass", lua_cocos2d_Renderer_beginRenderPass);
	LUA_METHOD("checkVisibility", lua_cocos2d_Renderer_checkVisibility);
	LUA_METHOD("clean", lua_cocos2d_Renderer_clean);
	LUA_METHOD("clear", lua_cocos2d_Renderer_clear);
	LUA_METHOD("clearDrawStats", lua_cocos2d_Renderer_clearDrawStats);
	LUA_METHOD("createRenderQueue", lua_cocos2d_Renderer_createRenderQueue);
	LUA_METHOD("endRenderPass", lua_cocos2d_Renderer_endRenderPass);
	LUA_METHOD("getClearColor", lua_cocos2d_Renderer_getClearColor);
	LUA_METHOD("getClearDepth", lua_cocos2d_Renderer_getClearDepth);
	LUA_METHOD("getClearFlag", lua_cocos2d_Renderer_getClearFlag);
	LUA_METHOD("getClearStencil", lua_cocos2d_Renderer_getClearStencil);
	LUA_METHOD("getCullMode", lua_cocos2d_Renderer_getCullMode);
	LUA_METHOD("getDefaultRenderTarget", lua_cocos2d_Renderer_getDefaultRenderTarget);
	LUA_METHOD("getDepthCompareFunction", lua_cocos2d_Renderer_getDepthCompareFunction);
	LUA_METHOD("getDepthTest", lua_cocos2d_Renderer_getDepthTest);
	LUA_METHOD("getDepthWrite", lua_cocos2d_Renderer_getDepthWrite);
	LUA_METHOD("getDrawnBatches", lua_cocos2d_Renderer_getDrawnBatches);
	LUA_METHOD("getDrawnVertices", lua_cocos2d_Renderer_getDrawnVertices);
	LUA_METHOD("getNextGroupCommand", lua_cocos2d_Renderer_getNextGroupCommand);
	LUA_METHOD("getOffscreenRenderTarget", lua_cocos2d_Renderer_getOffscreenRenderTarget);
	LUA_METHOD("getRenderTarget", lua_cocos2d_Renderer_getRenderTarget);
	LUA_METHOD("getRenderTargetFlag", lua_cocos2d_Renderer_getRenderTargetFlag);
	LUA_METHOD("getScissorTest", lua_cocos2d_Renderer_getScissorTest);
	LUA_METHOD("getStencilCompareFunction", lua_cocos2d_Renderer_getStencilCompareFunction);
	LUA_METHOD("getStencilDepthPassOperation", lua_cocos2d_Renderer_getStencilDepthPassOperation);
	LUA_METHOD("getStencilFailureOperation", lua_cocos2d_Renderer_getStencilFailureOperation);
	LUA_METHOD("getStencilPassDepthFailureOperation", lua_cocos2d_Renderer_getStencilPassDepthFailureOperation);
	LUA_METHOD("getStencilReadMask", lua_cocos2d_Renderer_getStencilReadMask);
	LUA_METHOD("getStencilReferenceValue", lua_cocos2d_Renderer_getStencilReferenceValue);
	LUA_METHOD("getStencilTest", lua_cocos2d_Renderer_getStencilTest);
	LUA_METHOD("getStencilWriteMask", lua_cocos2d_Renderer_getStencilWriteMask);
	LUA_METHOD("getWinding", lua_cocos2d_Renderer_getWinding);
	LUA_METHOD("init", lua_cocos2d_Renderer_init);
	LUA_METHOD("nextCallbackCommand", lua_cocos2d_Renderer_nextCallbackCommand);
	LUA_METHOD("popGroup", lua_cocos2d_Renderer_popGroup);
	LUA_METHOD("pushGroup", lua_cocos2d_Renderer_pushGroup);
	LUA_METHOD("render", lua_cocos2d_Renderer_render);
	LUA_METHOD("setCullMode", lua_cocos2d_Renderer_setCullMode);
	LUA_METHOD("setDepthCompareFunction", lua_cocos2d_Renderer_setDepthCompareFunction);
	LUA_METHOD("setDepthTest", lua_cocos2d_Renderer_setDepthTest);
	LUA_METHOD("setDepthWrite", lua_cocos2d_Renderer_setDepthWrite);
	LUA_METHOD("setRenderTarget", lua_cocos2d_Renderer_setRenderTarget);
	LUA_METHOD("setScissorRect", lua_cocos2d_Renderer_setScissorRect);
	LUA_METHOD("setScissorTest", lua_cocos2d_Renderer_setScissorTest);
	LUA_METHOD("setStencilCompareFunction", lua_cocos2d_Renderer_setStencilCompareFunction);
	LUA_METHOD("setStencilOperation", lua_cocos2d_Renderer_setStencilOperation);
	LUA_METHOD("setStencilTest", lua_cocos2d_Renderer_setStencilTest);
	LUA_METHOD("setStencilWriteMask", lua_cocos2d_Renderer_setStencilWriteMask);
	LUA_METHOD("setViewPort", lua_cocos2d_Renderer_setViewPort);
	LUA_METHOD("setWinding", lua_cocos2d_Renderer_setWinding);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TextureCache_addImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:addImage");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(cocos2d::Image*, std::string_view, cocos2d::PixelFormat)>(&cocos2d::TextureCache::addImage)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(cocos2d::Image*, std::string_view)>(&cocos2d::TextureCache::addImage)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(std::string_view, cocos2d::PixelFormat)>(&cocos2d::TextureCache::addImage)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(std::string_view)>(&cocos2d::TextureCache::addImage));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_TextureCache_addImageAsync_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:addImageAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::TextureCache::*)(std::string_view, const std::function<void(cocos2d::Texture2D*)>&)>(&cocos2d::TextureCache::addImageAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TextureCache_getCachedTextureInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getCachedTextureInfo");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::TextureCache::*)()const>(&cocos2d::TextureCache::getCachedTextureInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_getDescription(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getDescription");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::TextureCache::*)()const>(&cocos2d::TextureCache::getDescription));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_getTextureFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getTextureFilePath");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::TextureCache::*)(cocos2d::Texture2D*)const>(&cocos2d::TextureCache::getTextureFilePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_getTextureForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getTextureForKey");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(std::string_view)const>(&cocos2d::TextureCache::getTextureForKey));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:reloadTexture");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TextureCache::*)(std::string_view)>(&cocos2d::TextureCache::reloadTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_removeAllTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeAllTextures");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::removeAllTextures));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_removeTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TextureCache::*)(cocos2d::Texture2D*)>(&cocos2d::TextureCache::removeTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_removeTextureForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeTextureForKey");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TextureCache::*)(std::string_view)>(&cocos2d::TextureCache::removeTextureForKey));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_removeUnusedTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeUnusedTextures");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::removeUnusedTextures));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_renameTextureWithKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:renameTextureWithKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::TextureCache::*)(std::string_view, std::string_view)>(&cocos2d::TextureCache::renameTextureWithKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TextureCache_unbindAllImageAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:unbindAllImageAsync");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::unbindAllImageAsync));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_unbindImageAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:unbindImageAsync");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TextureCache::*)(std::string_view)>(&cocos2d::TextureCache::unbindImageAsync));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCache_waitForQuit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:waitForQuit");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::waitForQuit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_getETC1AlphaFileSuffix(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getETC1AlphaFileSuffix");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(*)()>(&cocos2d::TextureCache::getETC1AlphaFileSuffix));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCache_setETC1AlphaFileSuffix(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCache", "cc.TextureCache:setETC1AlphaFileSuffix");
	LUA_TRY_INVOKE(1, static_cast<void(*)(std::string_view)>(&cocos2d::TextureCache::setETC1AlphaFileSuffix));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTextureCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TextureCache, "TextureCache", "cc.TextureCache",
		cocos2d::TextureCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addImage", lua_cocos2d_TextureCache_addImage);
	LUA_METHOD("addImageAsync", lua_cocos2d_TextureCache_addImageAsync_1);
	LUA_METHOD("getCachedTextureInfo", lua_cocos2d_TextureCache_getCachedTextureInfo);
	LUA_METHOD("getDescription", lua_cocos2d_TextureCache_getDescription);
	LUA_METHOD("getTextureFilePath", lua_cocos2d_TextureCache_getTextureFilePath);
	LUA_METHOD("getTextureForKey", lua_cocos2d_TextureCache_getTextureForKey);
	LUA_METHOD("reloadTexture", lua_cocos2d_TextureCache_reloadTexture);
	LUA_METHOD("removeAllTextures", lua_cocos2d_TextureCache_removeAllTextures);
	LUA_METHOD("removeTexture", lua_cocos2d_TextureCache_removeTexture);
	LUA_METHOD("removeTextureForKey", lua_cocos2d_TextureCache_removeTextureForKey);
	LUA_METHOD("removeUnusedTextures", lua_cocos2d_TextureCache_removeUnusedTextures);
	LUA_METHOD("renameTextureWithKey", lua_cocos2d_TextureCache_renameTextureWithKey);
	LUA_METHOD("unbindAllImageAsync", lua_cocos2d_TextureCache_unbindAllImageAsync);
	LUA_METHOD("unbindImageAsync", lua_cocos2d_TextureCache_unbindImageAsync);
	LUA_METHOD("waitForQuit", lua_cocos2d_TextureCache_waitForQuit);
	LUA_METHOD("getETC1AlphaFileSuffix", lua_cocos2d_TextureCache_getETC1AlphaFileSuffix);
	LUA_METHOD("setETC1AlphaFileSuffix", lua_cocos2d_TextureCache_setETC1AlphaFileSuffix);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Device_getDPI(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:getDPI");
	LUA_TRY_INVOKE_R(0, static_cast<int(*)()>(&cocos2d::Device::getDPI));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Device_setAccelerometerEnabled(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setAccelerometerEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::Device::setAccelerometerEnabled));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Device_setAccelerometerInterval(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setAccelerometerInterval");
	LUA_TRY_INVOKE(1, static_cast<void(*)(float)>(&cocos2d::Device::setAccelerometerInterval));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Device_setKeepScreenOn(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setKeepScreenOn");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::Device::setKeepScreenOn));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Device_vibrate(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:vibrate");
	LUA_TRY_INVOKE(1, static_cast<void(*)(float)>(&cocos2d::Device::vibrate));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDevice(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Device, "Device", "cc.Device",
		cocos2d::Device, "",
		nullptr, nullptr);
	LUA_METHOD("getDPI", lua_cocos2d_Device_getDPI);
	LUA_METHOD("setAccelerometerEnabled", lua_cocos2d_Device_setAccelerometerEnabled);
	LUA_METHOD("setAccelerometerInterval", lua_cocos2d_Device_setAccelerometerInterval);
	LUA_METHOD("setKeepScreenOn", lua_cocos2d_Device_setKeepScreenOn);
	LUA_METHOD("vibrate", lua_cocos2d_Device_vibrate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Application_getCurrentLanguage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getCurrentLanguage");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::LanguageType(cocos2d::Application::*)()>(&cocos2d::Application::getCurrentLanguage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Application_getCurrentLanguageCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getCurrentLanguageCode");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::Application::*)()>(&cocos2d::Application::getCurrentLanguageCode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Application_getTargetPlatform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getTargetPlatform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ApplicationProtocol::Platform(cocos2d::Application::*)()>(&cocos2d::Application::getTargetPlatform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Application_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getVersion");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Application::*)()>(&cocos2d::Application::getVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Application_openURL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:openURL");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Application::*)(std::string_view)>(&cocos2d::Application::openURL));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Application_setAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:setAnimationInterval");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Application::*)(float)>(&cocos2d::Application::setAnimationInterval));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Application_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Application", "cc.Application:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Application*(*)()>(&cocos2d::Application::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccApplication(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Application, "Application", "cc.Application",
		cocos2d::Application, "",
		nullptr, nullptr);
	LUA_METHOD("getCurrentLanguage", lua_cocos2d_Application_getCurrentLanguage);
	LUA_METHOD("getCurrentLanguageCode", lua_cocos2d_Application_getCurrentLanguageCode);
	LUA_METHOD("getTargetPlatform", lua_cocos2d_Application_getTargetPlatform);
	LUA_METHOD("getVersion", lua_cocos2d_Application_getVersion);
	LUA_METHOD("openURL", lua_cocos2d_Application_openURL);
	LUA_METHOD("setAnimationInterval", lua_cocos2d_Application_setAnimationInterval);
	LUA_METHOD("getInstance", lua_cocos2d_Application_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GLViewImpl_createWithFullScreen(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithFullScreen");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::GLViewImpl*(*)(std::string_view)>(&cocos2d::GLViewImpl::createWithFullScreen));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccGLViewImpl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GLViewImpl, "GLViewImpl", "cc.GLViewImpl",
		cocos2d::GLViewImpl, "cc.GLView",
		nullptr, nullptr);
	LUA_METHOD("createWithFullScreen", lua_cocos2d_GLViewImpl_createWithFullScreen);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AnimationCache_addAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimation");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::AnimationCache::*)(cocos2d::Animation*, std::string_view)>(&cocos2d::AnimationCache::addAnimation)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_AnimationCache_addAnimations(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimations");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationCache::*)(std::string_view)>(&cocos2d::AnimationCache::addAnimationsWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationCache_addAnimationsWithDictionary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimationsWithDictionary");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::AnimationCache::*)(const cocos2d::ValueMap&, std::string_view)>(&cocos2d::AnimationCache::addAnimationsWithDictionary)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_AnimationCache_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getAnimation");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animation*(cocos2d::AnimationCache::*)(std::string_view)>(&cocos2d::AnimationCache::getAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::AnimationCache::*)()>(&cocos2d::AnimationCache::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationCache_removeAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:removeAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationCache::*)(std::string_view)>(&cocos2d::AnimationCache::removeAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AnimationCache*(*)()>(&cocos2d::AnimationCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccAnimationCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationCache, "AnimationCache", "cc.AnimationCache",
		cocos2d::AnimationCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAnimation", lua_cocos2d_AnimationCache_addAnimation);
	LUA_METHOD("addAnimations", lua_cocos2d_AnimationCache_addAnimations);
	LUA_METHOD("addAnimationsWithDictionary", lua_cocos2d_AnimationCache_addAnimationsWithDictionary);
	LUA_METHOD("getAnimation", lua_cocos2d_AnimationCache_getAnimation);
	LUA_METHOD("init", lua_cocos2d_AnimationCache_init);
	LUA_METHOD("removeAnimation", lua_cocos2d_AnimationCache_removeAnimation);
	LUA_METHOD("getInstance", lua_cocos2d_AnimationCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:addSpriteWithoutQuad");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SpriteBatchNode*(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int, int)>(&cocos2d::SpriteBatchNode::addSpriteWithoutQuad)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SpriteBatchNode_appendChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:appendChild");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::appendChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_atlasIndexForChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:atlasIndexForChild");
	LUA_TRY_INVOKE_R(2, (static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, int)>(&cocos2d::SpriteBatchNode::atlasIndexForChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getDescendants(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getDescendants");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<cocos2d::Sprite *>&(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getDescendants));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureAtlas*(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::getTextureAtlas));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_highestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:highestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::highestAtlasIndexInChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_increaseAtlasCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:increaseAtlasCapacity");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::increaseAtlasCapacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteBatchNode::*)(std::string_view, ssize_t)>(&cocos2d::SpriteBatchNode::initWithFile)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::SpriteBatchNode* obj,std::string_view arg0){{return obj->initWithFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteBatchNode::*)(cocos2d::Texture2D*, ssize_t)>(&cocos2d::SpriteBatchNode::initWithTexture)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::SpriteBatchNode* obj,cocos2d::Texture2D* arg0){{return obj->initWithTexture(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_insertQuadFromSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:insertQuadFromSprite");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, ssize_t)>(&cocos2d::SpriteBatchNode::insertQuadFromSprite)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:lowestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::lowestAtlasIndexInChild));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_rebuildIndexInOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:rebuildIndexInOrder");
	LUA_TRY_INVOKE_R(2, (static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*, ssize_t)>(&cocos2d::SpriteBatchNode::rebuildIndexInOrder)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(bool)>(&cocos2d::SpriteBatchNode::removeAllChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t, bool)>(&cocos2d::SpriteBatchNode::removeChildAtIndex)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SpriteBatchNode_removeSpriteFromAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeSpriteFromAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::removeSpriteFromAtlas));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_reorderBatch(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reorderBatch");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(bool)>(&cocos2d::SpriteBatchNode::reorderBatch));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_reserveCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reserveCapacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t)>(&cocos2d::SpriteBatchNode::reserveCapacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(const cocos2d::BlendFunc&)>(&cocos2d::SpriteBatchNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Texture2D*)>(&cocos2d::SpriteBatchNode::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::SpriteBatchNode::setTextureAtlas));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteBatchNode*(*)(std::string_view, ssize_t)>(&cocos2d::SpriteBatchNode::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::SpriteBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_SpriteBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteBatchNode*(*)(cocos2d::Texture2D*, ssize_t)>(&cocos2d::SpriteBatchNode::createWithTexture)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::SpriteBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccSpriteBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteBatchNode, "SpriteBatchNode", "cc.SpriteBatchNode",
		cocos2d::SpriteBatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addSpriteWithoutQuad", lua_cocos2d_SpriteBatchNode_addSpriteWithoutQuad);
	LUA_METHOD("appendChild", lua_cocos2d_SpriteBatchNode_appendChild);
	LUA_METHOD("atlasIndexForChild", lua_cocos2d_SpriteBatchNode_atlasIndexForChild);
	LUA_METHOD("getBlendFunc", lua_cocos2d_SpriteBatchNode_getBlendFunc);
	LUA_METHOD("getDescendants", lua_cocos2d_SpriteBatchNode_getDescendants);
	LUA_METHOD("getTexture", lua_cocos2d_SpriteBatchNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cocos2d_SpriteBatchNode_getTextureAtlas);
	LUA_METHOD("highestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_highestAtlasIndexInChild);
	LUA_METHOD("increaseAtlasCapacity", lua_cocos2d_SpriteBatchNode_increaseAtlasCapacity);
	LUA_METHOD("initWithFile", lua_cocos2d_SpriteBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cocos2d_SpriteBatchNode_initWithTexture);
	LUA_METHOD("insertQuadFromSprite", lua_cocos2d_SpriteBatchNode_insertQuadFromSprite);
	LUA_METHOD("lowestAtlasIndexInChild", lua_cocos2d_SpriteBatchNode_lowestAtlasIndexInChild);
	LUA_METHOD("rebuildIndexInOrder", lua_cocos2d_SpriteBatchNode_rebuildIndexInOrder);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cocos2d_SpriteBatchNode_removeAllChildrenWithCleanup);
	LUA_METHOD("removeChildAtIndex", lua_cocos2d_SpriteBatchNode_removeChildAtIndex);
	LUA_METHOD("removeSpriteFromAtlas", lua_cocos2d_SpriteBatchNode_removeSpriteFromAtlas);
	LUA_METHOD("reorderBatch", lua_cocos2d_SpriteBatchNode_reorderBatch);
	LUA_METHOD("reserveCapacity", lua_cocos2d_SpriteBatchNode_reserveCapacity);
	LUA_METHOD("setBlendFunc", lua_cocos2d_SpriteBatchNode_setBlendFunc);
	LUA_METHOD("setTexture", lua_cocos2d_SpriteBatchNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cocos2d_SpriteBatchNode_setTextureAtlas);
	LUA_METHOD("create", lua_cocos2d_SpriteBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_SpriteBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ParallaxNode_addChild_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:addChild");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::ParallaxNode::*)(cocos2d::Node*, int, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::ParallaxNode::addChild)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ParallaxNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ParallaxNode::*)(bool)>(&cocos2d::ParallaxNode::removeAllChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ParallaxNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ParallaxNode*(*)()>(&cocos2d::ParallaxNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParallaxNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ParallaxNode, "ParallaxNode", "cc.ParallaxNode",
		cocos2d::ParallaxNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addChild", lua_cocos2d_ParallaxNode_addChild_1);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cocos2d_ParallaxNode_removeAllChildrenWithCleanup);
	LUA_METHOD("create", lua_cocos2d_ParallaxNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXObjectGroup_getGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getGroupName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getGroupName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObject");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueMap(cocos2d::TMXObjectGroup::*)(std::string_view)const>(&cocos2d::TMXObjectGroup::getObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_getObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObjects");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueVector&(cocos2d::TMXObjectGroup::*)()>(&cocos2d::TMXObjectGroup::getObjects));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueVector&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getObjects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getPositionOffset");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getPositionOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXObjectGroup::*)()>(&cocos2d::TMXObjectGroup::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::TMXObjectGroup::*)()const>(&cocos2d::TMXObjectGroup::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXObjectGroup_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperty");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::TMXObjectGroup::*)(std::string_view)const>(&cocos2d::TMXObjectGroup::getProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setGroupName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(std::string_view)>(&cocos2d::TMXObjectGroup::setGroupName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setObjects");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::ValueVector&)>(&cocos2d::TMXObjectGroup::setObjects));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setPositionOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::Vec2&)>(&cocos2d::TMXObjectGroup::setPositionOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXObjectGroup_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXObjectGroup::*)(const cocos2d::ValueMap&)>(&cocos2d::TMXObjectGroup::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXObjectGroup(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXObjectGroup, "TMXObjectGroup", "cc.TMXObjectGroup",
		cocos2d::TMXObjectGroup, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getGroupName", lua_cocos2d_TMXObjectGroup_getGroupName);
	LUA_METHOD("getObject", lua_cocos2d_TMXObjectGroup_getObject);
	LUA_METHOD("getObjects", lua_cocos2d_TMXObjectGroup_getObjects);
	LUA_METHOD("getPositionOffset", lua_cocos2d_TMXObjectGroup_getPositionOffset);
	LUA_METHOD("getProperties", lua_cocos2d_TMXObjectGroup_getProperties);
	LUA_METHOD("getProperty", lua_cocos2d_TMXObjectGroup_getProperty);
	LUA_METHOD("setGroupName", lua_cocos2d_TMXObjectGroup_setGroupName);
	LUA_METHOD("setObjects", lua_cocos2d_TMXObjectGroup_setObjects);
	LUA_METHOD("setPositionOffset", lua_cocos2d_TMXObjectGroup_setPositionOffset);
	LUA_METHOD("setProperties", lua_cocos2d_TMXObjectGroup_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXLayerInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:getProperties");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXLayerInfo::*)()>(&cocos2d::TMXLayerInfo::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXLayerInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXLayerInfo::*)(cocos2d::ValueMap)>(&cocos2d::TMXLayerInfo::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXLayerInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXLayerInfo, "TMXLayerInfo", "cc.TMXLayerInfo",
		cocos2d::TMXLayerInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getProperties", lua_cocos2d_TMXLayerInfo_getProperties);
	LUA_METHOD("setProperties", lua_cocos2d_TMXLayerInfo_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXTilesetInfo_getRectForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTilesetInfo", "cc.TMXTilesetInfo:getRectForGID");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Rect(cocos2d::TMXTilesetInfo::*)(uint32_t)>(&cocos2d::TMXTilesetInfo::getRectForGID));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTilesetInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTilesetInfo, "TMXTilesetInfo", "cc.TMXTilesetInfo",
		cocos2d::TMXTilesetInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getRectForGID", lua_cocos2d_TMXTilesetInfo_getRectForGID);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TMXMapInfo_getCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getCurrentString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getCurrentString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getExternalTilesetFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getExternalTilesetFileName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getExternalTilesetFileName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getHexSideLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getHexSideLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayerAttribs");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getLayerAttribs));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayers");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXLayerInfo *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getLayers));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXLayerInfo *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getLayers));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getMapSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getMapSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getObjectGroups));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getOrientation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getOrientation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentElement");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getParentElement));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentGID");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getParentGID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerAxis");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getStaggerAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getStaggerIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTMXFileName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTMXFileName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileProperties");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ValueMapIntKey&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getTileProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTileSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_getTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTilesets");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXTilesetInfo *>&(cocos2d::TMXMapInfo::*)()>(&cocos2d::TMXMapInfo::getTilesets));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXTilesetInfo *>&(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::getTilesets));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::initWithTMXFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithXML");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::initWithXML)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TMXMapInfo_isStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:isStoringCharacters");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::TMXMapInfo::*)()const>(&cocos2d::TMXMapInfo::isStoringCharacters));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXMapInfo_parseXMLFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::parseXMLFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_parseXMLString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLString");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::parseXMLString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setCurrentString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::setCurrentString));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setHexSideLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setHexSideLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayerAttribs");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setLayerAttribs));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayers");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXLayerInfo *>&)>(&cocos2d::TMXMapInfo::setLayers));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setMapSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vec2&)>(&cocos2d::TMXMapInfo::setMapSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setObjectGroups");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)>(&cocos2d::TMXMapInfo::setObjectGroups));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentElement");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setParentElement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentGID");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setParentGID));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::ValueMap&)>(&cocos2d::TMXMapInfo::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerAxis");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setStaggerAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(int)>(&cocos2d::TMXMapInfo::setStaggerIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStoringCharacters");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(bool)>(&cocos2d::TMXMapInfo::setStoringCharacters));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTMXFileName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(std::string_view)>(&cocos2d::TMXMapInfo::setTMXFileName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::ValueMapIntKey&)>(&cocos2d::TMXMapInfo::setTileProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vec2&)>(&cocos2d::TMXMapInfo::setTileSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_setTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTilesets");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TMXMapInfo::*)(const cocos2d::Vector<cocos2d::TMXTilesetInfo *>&)>(&cocos2d::TMXMapInfo::setTilesets));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXMapInfo*(*)(std::string_view)>(&cocos2d::TMXMapInfo::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_TMXMapInfo_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:createWithXML");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TMXMapInfo*(*)(std::string_view, std::string_view)>(&cocos2d::TMXMapInfo::createWithXML)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTMXMapInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXMapInfo, "TMXMapInfo", "cc.TMXMapInfo",
		cocos2d::TMXMapInfo, "",
		nullptr, nullptr);
	LUA_METHOD("getCurrentString", lua_cocos2d_TMXMapInfo_getCurrentString);
	LUA_METHOD("getExternalTilesetFileName", lua_cocos2d_TMXMapInfo_getExternalTilesetFileName);
	LUA_METHOD("getHexSideLength", lua_cocos2d_TMXMapInfo_getHexSideLength);
	LUA_METHOD("getLayerAttribs", lua_cocos2d_TMXMapInfo_getLayerAttribs);
	LUA_METHOD("getLayers", lua_cocos2d_TMXMapInfo_getLayers);
	LUA_METHOD("getMapSize", lua_cocos2d_TMXMapInfo_getMapSize);
	LUA_METHOD("getObjectGroups", lua_cocos2d_TMXMapInfo_getObjectGroups);
	LUA_METHOD("getOrientation", lua_cocos2d_TMXMapInfo_getOrientation);
	LUA_METHOD("getParentElement", lua_cocos2d_TMXMapInfo_getParentElement);
	LUA_METHOD("getParentGID", lua_cocos2d_TMXMapInfo_getParentGID);
	LUA_METHOD("getProperties", lua_cocos2d_TMXMapInfo_getProperties);
	LUA_METHOD("getStaggerAxis", lua_cocos2d_TMXMapInfo_getStaggerAxis);
	LUA_METHOD("getStaggerIndex", lua_cocos2d_TMXMapInfo_getStaggerIndex);
	LUA_METHOD("getTMXFileName", lua_cocos2d_TMXMapInfo_getTMXFileName);
	LUA_METHOD("getTileProperties", lua_cocos2d_TMXMapInfo_getTileProperties);
	LUA_METHOD("getTileSize", lua_cocos2d_TMXMapInfo_getTileSize);
	LUA_METHOD("getTilesets", lua_cocos2d_TMXMapInfo_getTilesets);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_TMXMapInfo_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_TMXMapInfo_initWithXML);
	LUA_METHOD("isStoringCharacters", lua_cocos2d_TMXMapInfo_isStoringCharacters);
	LUA_METHOD("parseXMLFile", lua_cocos2d_TMXMapInfo_parseXMLFile);
	LUA_METHOD("parseXMLString", lua_cocos2d_TMXMapInfo_parseXMLString);
	LUA_METHOD("setCurrentString", lua_cocos2d_TMXMapInfo_setCurrentString);
	LUA_METHOD("setHexSideLength", lua_cocos2d_TMXMapInfo_setHexSideLength);
	LUA_METHOD("setLayerAttribs", lua_cocos2d_TMXMapInfo_setLayerAttribs);
	LUA_METHOD("setLayers", lua_cocos2d_TMXMapInfo_setLayers);
	LUA_METHOD("setMapSize", lua_cocos2d_TMXMapInfo_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cocos2d_TMXMapInfo_setObjectGroups);
	LUA_METHOD("setOrientation", lua_cocos2d_TMXMapInfo_setOrientation);
	LUA_METHOD("setParentElement", lua_cocos2d_TMXMapInfo_setParentElement);
	LUA_METHOD("setParentGID", lua_cocos2d_TMXMapInfo_setParentGID);
	LUA_METHOD("setProperties", lua_cocos2d_TMXMapInfo_setProperties);
	LUA_METHOD("setStaggerAxis", lua_cocos2d_TMXMapInfo_setStaggerAxis);
	LUA_METHOD("setStaggerIndex", lua_cocos2d_TMXMapInfo_setStaggerIndex);
	LUA_METHOD("setStoringCharacters", lua_cocos2d_TMXMapInfo_setStoringCharacters);
	LUA_METHOD("setTMXFileName", lua_cocos2d_TMXMapInfo_setTMXFileName);
	LUA_METHOD("setTileProperties", lua_cocos2d_TMXMapInfo_setTileProperties);
	LUA_METHOD("setTileSize", lua_cocos2d_TMXMapInfo_setTileSize);
	LUA_METHOD("setTilesets", lua_cocos2d_TMXMapInfo_setTilesets);
	LUA_METHOD("create", lua_cocos2d_TMXMapInfo_create);
	LUA_METHOD("createWithXML", lua_cocos2d_TMXMapInfo_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TileMapAtlas_getTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:getTileAt");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Color3B(cocos2d::TileMapAtlas::*)(const cocos2d::Vec2&)const>(&cocos2d::TileMapAtlas::getTileAt));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TileMapAtlas_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:initWithTileFile");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TileMapAtlas::*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::initWithTileFile)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TileMapAtlas_releaseMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:releaseMap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TileMapAtlas::*)()>(&cocos2d::TileMapAtlas::releaseMap));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TileMapAtlas_setTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:setTile");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::TileMapAtlas::*)(const cocos2d::Color3B&, const cocos2d::Vec2&)>(&cocos2d::TileMapAtlas::setTile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TileMapAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TileMapAtlas*(*)(std::string_view, std::string_view, int, int)>(&cocos2d::TileMapAtlas::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTileMapAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TileMapAtlas, "TileMapAtlas", "cc.TileMapAtlas",
		cocos2d::TileMapAtlas, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_METHOD("getTileAt", lua_cocos2d_TileMapAtlas_getTileAt);
	LUA_METHOD("initWithTileFile", lua_cocos2d_TileMapAtlas_initWithTileFile);
	LUA_METHOD("releaseMap", lua_cocos2d_TileMapAtlas_releaseMap);
	LUA_METHOD("setTile", lua_cocos2d_TileMapAtlas_setTile);
	LUA_METHOD("create", lua_cocos2d_TileMapAtlas_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
