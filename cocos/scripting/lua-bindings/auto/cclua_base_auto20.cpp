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
