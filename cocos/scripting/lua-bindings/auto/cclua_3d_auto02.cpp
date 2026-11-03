#include "cclua_3d_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_3d_compat.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"

int lua_cocos2d_MeshRenderer_genMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:genMaterial");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(bool)>(&cocos2d::MeshRenderer::genMaterial));
	LUA_TRY_INVOKE(0, [](cocos2d::MeshRenderer* obj){{return obj->genMaterial();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_MeshRenderer_getAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getAttachNode");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::AttachNode*(cocos2d::MeshRenderer::*)(std::string_view)>(&cocos2d::MeshRenderer::getAttachNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_getLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getLightMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getLightMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getMeshByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshByIndex");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Mesh*(cocos2d::MeshRenderer::*)(int)const>(&cocos2d::MeshRenderer::getMeshByIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_getMeshCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getMeshCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_isForceDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:isForceDepthWrite");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::isForceDepthWrite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_isWireframe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:isWireframe");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::isWireframe));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_removeAllAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:removeAllAttachNode");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MeshRenderer::*)()>(&cocos2d::MeshRenderer::removeAllAttachNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_removeAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:removeAttachNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(std::string_view)>(&cocos2d::MeshRenderer::removeAttachNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setCullFace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setCullFace");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(cocos2d::CullFaceSide)>(&cocos2d::MeshRenderer::setCullFace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setCullFaceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setCullFaceEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(bool)>(&cocos2d::MeshRenderer::setCullFaceEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setForceDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setForceDepthWrite");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(bool)>(&cocos2d::MeshRenderer::setForceDepthWrite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setLightMask");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(unsigned int)>(&cocos2d::MeshRenderer::setLightMask));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setWireframe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setWireframe");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(bool)>(&cocos2d::MeshRenderer::setWireframe));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccMeshRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MeshRenderer, "MeshRenderer", "cc.MeshRenderer",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("genMaterial", lua_cocos2d_MeshRenderer_genMaterial);
	LUA_METHOD("getAttachNode", lua_cocos2d_MeshRenderer_getAttachNode);
	LUA_METHOD("getLightMask", lua_cocos2d_MeshRenderer_getLightMask);
	LUA_METHOD("getMeshByIndex", lua_cocos2d_MeshRenderer_getMeshByIndex);
	LUA_METHOD("getMeshCount", lua_cocos2d_MeshRenderer_getMeshCount);
	LUA_METHOD("isForceDepthWrite", lua_cocos2d_MeshRenderer_isForceDepthWrite);
	LUA_METHOD("isWireframe", lua_cocos2d_MeshRenderer_isWireframe);
	LUA_METHOD("removeAllAttachNode", lua_cocos2d_MeshRenderer_removeAllAttachNode);
	LUA_METHOD("removeAttachNode", lua_cocos2d_MeshRenderer_removeAttachNode);
	LUA_METHOD("setCullFace", lua_cocos2d_MeshRenderer_setCullFace);
	LUA_METHOD("setCullFaceEnabled", lua_cocos2d_MeshRenderer_setCullFaceEnabled);
	LUA_METHOD("setForceDepthWrite", lua_cocos2d_MeshRenderer_setForceDepthWrite);
	LUA_METHOD("setLightMask", lua_cocos2d_MeshRenderer_setLightMask);
	LUA_METHOD("setWireframe", lua_cocos2d_MeshRenderer_setWireframe);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MeshRendererCache_removeAllMeshRenderData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:removeAllMeshRenderData");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MeshRendererCache::*)()>(&cocos2d::MeshRendererCache::removeAllMeshRenderData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRendererCache_removeMeshRenderData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:removeMeshRenderData");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRendererCache::*)(std::string_view)>(&cocos2d::MeshRendererCache::removeMeshRenderData));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccMeshRendererCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::MeshRendererCache, "MeshRendererCache", "cc.MeshRendererCache",
		nullptr, nullptr);
	LUA_METHOD("removeAllMeshRenderData", lua_cocos2d_MeshRendererCache_removeAllMeshRenderData);
	LUA_METHOD("removeMeshRenderData", lua_cocos2d_MeshRendererCache_removeMeshRenderData);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MeshMaterial_getMaterialType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:getMaterialType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::MeshMaterial::MaterialType(cocos2d::MeshMaterial::*)()const>(&cocos2d::MeshMaterial::getMaterialType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshMaterial_createBuiltInMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createBuiltInMaterial");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::MeshMaterial*(*)(cocos2d::MeshMaterial::MaterialType, bool)>(&cocos2d::MeshMaterial::createBuiltInMaterial));
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocos2d::MeshMaterial::createBuiltInMaterial));
	LUA_SINVOKE_FOOTER("0,2");
}
int lua_cocos2d_MeshMaterial_createWithFilename(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createWithFilename");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::MeshMaterial*(*)(std::string_view)>(&cocos2d::MeshMaterial::createWithFilename));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_MeshMaterial_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createWithProgramState");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::MeshMaterial*(*)(cocos2d::backend::ProgramState*)>(&cocos2d::MeshMaterial::createWithProgramState));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_MeshMaterial_releaseBuiltInMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:releaseBuiltInMaterial");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocos2d::MeshMaterial::releaseBuiltInMaterial));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_MeshMaterial_releaseCachedMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:releaseCachedMaterial");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocos2d::MeshMaterial::releaseCachedMaterial));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccMeshMaterial(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MeshMaterial, "MeshMaterial", "cc.MeshMaterial",
		cocos2d::Material, "cc.Material",
		nullptr, nullptr);
	LUA_METHOD("getMaterialType", lua_cocos2d_MeshMaterial_getMaterialType);
	LUA_METHOD("createBuiltInMaterial", lua_cocos2d_MeshMaterial_createBuiltInMaterial);
	LUA_METHOD("createWithFilename", lua_cocos2d_MeshMaterial_createWithFilename);
	LUA_METHOD("createWithProgramState", lua_cocos2d_MeshMaterial_createWithProgramState);
	LUA_METHOD("releaseBuiltInMaterial", lua_cocos2d_MeshMaterial_releaseBuiltInMaterial);
	LUA_METHOD("releaseCachedMaterial", lua_cocos2d_MeshMaterial_releaseCachedMaterial);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Terrain_getImageHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getImageHeight");
	LUA_TRY_INVOKE_R(2, static_cast<float(cocos2d::Terrain::*)(int, int)const>(&cocos2d::Terrain::getImageHeight));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Terrain_getMaxHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getMaxHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Terrain::*)()>(&cocos2d::Terrain::getMaxHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_getMinHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getMinHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Terrain::*)()>(&cocos2d::Terrain::getMinHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_initHeightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initHeightMap");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Terrain::*)(std::string_view)>(&cocos2d::Terrain::initHeightMap));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_initProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initProperties");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Terrain::*)()>(&cocos2d::Terrain::initProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_initTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initTextures");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Terrain::*)()>(&cocos2d::Terrain::initTextures));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_reload(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:reload");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Terrain::*)()>(&cocos2d::Terrain::reload));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_resetHeightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:resetHeightMap");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(std::string_view)>(&cocos2d::Terrain::resetHeightMap));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setAlphaMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setAlphaMap");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(cocos2d::Texture2D*)>(&cocos2d::Terrain::setAlphaMap));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setDrawWire(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setDrawWire");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(bool)>(&cocos2d::Terrain::setDrawWire));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setIsEnableFrustumCull(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setIsEnableFrustumCull");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(bool)>(&cocos2d::Terrain::setIsEnableFrustumCull));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setLODDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLODDistance");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::Terrain::*)(float, float, float)>(&cocos2d::Terrain::setLODDistance));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Terrain_setLightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLightMap");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(std::string_view)>(&cocos2d::Terrain::setLightMap));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setMaxDetailMapAmount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setMaxDetailMapAmount");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(int)>(&cocos2d::Terrain::setMaxDetailMapAmount));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_setSkirtHeightRatio(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setSkirtHeightRatio");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(float)>(&cocos2d::Terrain::setSkirtHeightRatio));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccTerrain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Terrain, "Terrain", "cc.Terrain",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getImageHeight", lua_cocos2d_Terrain_getImageHeight);
	LUA_METHOD("getMaxHeight", lua_cocos2d_Terrain_getMaxHeight);
	LUA_METHOD("getMinHeight", lua_cocos2d_Terrain_getMinHeight);
	LUA_METHOD("initHeightMap", lua_cocos2d_Terrain_initHeightMap);
	LUA_METHOD("initProperties", lua_cocos2d_Terrain_initProperties);
	LUA_METHOD("initTextures", lua_cocos2d_Terrain_initTextures);
	LUA_METHOD("reload", lua_cocos2d_Terrain_reload);
	LUA_METHOD("resetHeightMap", lua_cocos2d_Terrain_resetHeightMap);
	LUA_METHOD("setAlphaMap", lua_cocos2d_Terrain_setAlphaMap);
	LUA_METHOD("setDrawWire", lua_cocos2d_Terrain_setDrawWire);
	LUA_METHOD("setIsEnableFrustumCull", lua_cocos2d_Terrain_setIsEnableFrustumCull);
	LUA_METHOD("setLODDistance", lua_cocos2d_Terrain_setLODDistance);
	LUA_METHOD("setLightMap", lua_cocos2d_Terrain_setLightMap);
	LUA_METHOD("setMaxDetailMapAmount", lua_cocos2d_Terrain_setMaxDetailMapAmount);
	LUA_METHOD("setSkirtHeightRatio", lua_cocos2d_Terrain_setSkirtHeightRatio);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
