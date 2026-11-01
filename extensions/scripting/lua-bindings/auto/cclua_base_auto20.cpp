#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

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
		cocos2d::Node, "cc.Node",
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

int luaReg_Core_ccDirectionLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DirectionLight, "DirectionLight", "cc.DirectionLight",
		cocos2d::BaseLight, "cc.BaseLight",
		nullptr, nullptr);
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
int luaReg_Core_ccPointLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::PointLight, "PointLight", "cc.PointLight",
		cocos2d::BaseLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getRange", lua_cocos2d_PointLight_getRange);
	LUA_METHOD("setRange", lua_cocos2d_PointLight_setRange);
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
int luaReg_Core_ccSpotLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpotLight, "SpotLight", "cc.SpotLight",
		cocos2d::BaseLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getCosInnerAngle", lua_cocos2d_SpotLight_getCosInnerAngle);
	LUA_METHOD("getCosOuterAngle", lua_cocos2d_SpotLight_getCosOuterAngle);
	LUA_METHOD("getInnerAngle", lua_cocos2d_SpotLight_getInnerAngle);
	LUA_METHOD("getOuterAngle", lua_cocos2d_SpotLight_getOuterAngle);
	LUA_METHOD("getRange", lua_cocos2d_SpotLight_getRange);
	LUA_METHOD("setInnerAngle", lua_cocos2d_SpotLight_setInnerAngle);
	LUA_METHOD("setOuterAngle", lua_cocos2d_SpotLight_setOuterAngle);
	LUA_METHOD("setRange", lua_cocos2d_SpotLight_setRange);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccAmbientLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AmbientLight, "AmbientLight", "cc.AmbientLight",
		cocos2d::BaseLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
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
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
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
int lua_cocos2d_Technique_getPassCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPassCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Technique::*)()const>(&cocos2d::Technique::getPassCount));
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
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Technique*(*)(cocos2d::Material*, cocos2d::backend::ProgramState*)>(&cocos2d::Technique::createWithProgramState));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTechnique(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Technique, "Technique", "cc.Technique",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addPass", lua_cocos2d_Technique_addPass);
	LUA_METHOD("clone", lua_cocos2d_Technique_clone);
	LUA_METHOD("getName", lua_cocos2d_Technique_getName);
	LUA_METHOD("getPassCount", lua_cocos2d_Technique_getPassCount);
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
int lua_cocos2d_Material_createWithProperties(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Material", "cc.Material:createWithProperties");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Material*(*)(cocos2d::Properties*)>(&cocos2d::Material::createWithProperties));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMaterial(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Material, "Material", "cc.Material",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addTechnique", lua_cocos2d_Material_addTechnique);
	LUA_METHOD("clone", lua_cocos2d_Material_clone);
	LUA_METHOD("getName", lua_cocos2d_Material_getName);
	LUA_METHOD("getPrimitiveType", lua_cocos2d_Material_getPrimitiveType);
	LUA_METHOD("getRenderState", lua_cocos2d_Material_getRenderState);
	LUA_METHOD("getTechnique", lua_cocos2d_Material_getTechnique);
	LUA_METHOD("getTechniqueByName", lua_cocos2d_Material_getTechniqueByName);
	LUA_METHOD("getTechniqueCount", lua_cocos2d_Material_getTechniqueCount);
	LUA_METHOD("isForce2DQueue", lua_cocos2d_Material_isForce2DQueue);
	LUA_METHOD("isTransparent", lua_cocos2d_Material_isTransparent);
	LUA_METHOD("setForce2DQueue", lua_cocos2d_Material_setForce2DQueue);
	LUA_METHOD("setName", lua_cocos2d_Material_setName);
	LUA_METHOD("setPrimitiveType", lua_cocos2d_Material_setPrimitiveType);
	LUA_METHOD("setTechnique", lua_cocos2d_Material_setTechnique);
	LUA_METHOD("setTransparent", lua_cocos2d_Material_setTransparent);
	LUA_METHOD("createWithFilename", lua_cocos2d_Material_createWithFilename);
	LUA_METHOD("createWithProgramState", lua_cocos2d_Material_createWithProgramState);
	LUA_METHOD("createWithProperties", lua_cocos2d_Material_createWithProperties);
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Pass::*)(uint32_t, cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformNormTexture));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Pass_setUniformTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setUniformTexture");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Pass::*)(uint32_t, cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformTexture));
	LUA_INVOKE_FOOTER("2");
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
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Pass*(*)(cocos2d::Technique*, cocos2d::backend::ProgramState*)>(&cocos2d::Pass::createWithProgramState));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccPass(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Pass, "Pass", "cc.Pass",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_Pass_clone);
	LUA_METHOD("getName", lua_cocos2d_Pass_getName);
	LUA_METHOD("getProgramState", lua_cocos2d_Pass_getProgramState);
	LUA_METHOD("setName", lua_cocos2d_Pass_setName);
	LUA_METHOD("setTechnique", lua_cocos2d_Pass_setTechnique);
	LUA_METHOD("setUniformNormTexture", lua_cocos2d_Pass_setUniformNormTexture);
	LUA_METHOD("setUniformTexture", lua_cocos2d_Pass_setUniformTexture);
	LUA_METHOD("create", lua_cocos2d_Pass_create);
	LUA_METHOD("createWithProgramState", lua_cocos2d_Pass_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Renderer_beginRenderPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:beginRenderPass");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::beginRenderPass));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Renderer_clean(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clean");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::clean));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_Renderer_setScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setScissorRect");
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::Renderer::*)(float, float, float, float)>(&cocos2d::Renderer::setScissorRect));
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
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::CompareFunction, unsigned int, unsigned int)>(&cocos2d::Renderer::setStencilCompareFunction));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Renderer_setStencilOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilOperation");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::StencilOperation, cocos2d::backend::StencilOperation, cocos2d::backend::StencilOperation)>(&cocos2d::Renderer::setStencilOperation));
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
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::Renderer::*)(int, int, unsigned int, unsigned int)>(&cocos2d::Renderer::setViewPort));
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
	LUA_CLS_DEF(cocos2d::Renderer, "Renderer", "cc.Renderer",
		nullptr, nullptr);
	LUA_METHOD("beginRenderPass", lua_cocos2d_Renderer_beginRenderPass);
	LUA_METHOD("clean", lua_cocos2d_Renderer_clean);
	LUA_METHOD("clearDrawStats", lua_cocos2d_Renderer_clearDrawStats);
	LUA_METHOD("createRenderQueue", lua_cocos2d_Renderer_createRenderQueue);
	LUA_METHOD("endRenderPass", lua_cocos2d_Renderer_endRenderPass);
	LUA_METHOD("getClearDepth", lua_cocos2d_Renderer_getClearDepth);
	LUA_METHOD("getClearFlag", lua_cocos2d_Renderer_getClearFlag);
	LUA_METHOD("getClearStencil", lua_cocos2d_Renderer_getClearStencil);
	LUA_METHOD("getCullMode", lua_cocos2d_Renderer_getCullMode);
	LUA_METHOD("getDepthCompareFunction", lua_cocos2d_Renderer_getDepthCompareFunction);
	LUA_METHOD("getDepthTest", lua_cocos2d_Renderer_getDepthTest);
	LUA_METHOD("getDepthWrite", lua_cocos2d_Renderer_getDepthWrite);
	LUA_METHOD("getDrawnBatches", lua_cocos2d_Renderer_getDrawnBatches);
	LUA_METHOD("getDrawnVertices", lua_cocos2d_Renderer_getDrawnVertices);
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
	LUA_METHOD("popGroup", lua_cocos2d_Renderer_popGroup);
	LUA_METHOD("pushGroup", lua_cocos2d_Renderer_pushGroup);
	LUA_METHOD("render", lua_cocos2d_Renderer_render);
	LUA_METHOD("setCullMode", lua_cocos2d_Renderer_setCullMode);
	LUA_METHOD("setDepthCompareFunction", lua_cocos2d_Renderer_setDepthCompareFunction);
	LUA_METHOD("setDepthTest", lua_cocos2d_Renderer_setDepthTest);
	LUA_METHOD("setDepthWrite", lua_cocos2d_Renderer_setDepthWrite);
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
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::TextureCache::*)(std::string_view, std::string_view)>(&cocos2d::TextureCache::renameTextureWithKey));
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
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
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
	LUA_CLS_DEF(cocos2d::Device, "Device", "cc.Device",
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
