#include "cclua_3d_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"

int lua_cc_Animation3D_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation3D", "cc.Animation3D:getDuration");
	LUA_TRY_INVOKE_R(0, &cc::Animation3D::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation3D_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation3D", "cc.Animation3D:initWithFile");
	LUA_TRY_INVOKE_R(2, &cc::Animation3D::initWithFile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Animation3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation3D", "cc.Animation3D:create");
	LUA_TRY_INVOKE_R(2, &cc::Animation3D::create);
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::Animation3D::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccAnimation3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Animation3D, "Animation3D", "cc.Animation3D",
		cc::Animation3D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getDuration", lua_cc_Animation3D_getDuration);
	LUA_METHOD("initWithFile", lua_cc_Animation3D_initWithFile);
	LUA_METHOD("create", lua_cc_Animation3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Animate3D_getOriginInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getOriginInterval");
	LUA_TRY_INVOKE_R(0, &cc::Animate3D::getOriginInterval);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate3D_getQuality(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getQuality");
	LUA_TRY_INVOKE_R(0, &cc::Animate3D::getQuality);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate3D_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getSpeed");
	LUA_TRY_INVOKE_R(0, &cc::Animate3D::getSpeed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate3D_getWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getWeight");
	LUA_TRY_INVOKE_R(0, &cc::Animate3D::getWeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate3D_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:init");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::Animate3D::*)(cc::Animation3D*, float, float)>(&cc::Animate3D::init)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Animate3D::*)(cc::Animation3D*)>(&cc::Animate3D::init));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cc_Animate3D_initWithFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:initWithFrames");
	LUA_TRY_INVOKE_R(4, &cc::Animate3D::initWithFrames);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Animate3D_removeFromMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:removeFromMap");
	LUA_TRY_INVOKE(0, &cc::Animate3D::removeFromMap);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate3D_setKeyFrameUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setKeyFrameUserInfo");
	LUA_TRY_INVOKE(2, &cc::Animate3D::setKeyFrameUserInfo);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Animate3D_setOriginInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setOriginInterval");
	LUA_TRY_INVOKE(1, &cc::Animate3D::setOriginInterval);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate3D_setQuality(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setQuality");
	LUA_TRY_INVOKE(1, &cc::Animate3D::setQuality);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate3D_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setSpeed");
	LUA_TRY_INVOKE(1, &cc::Animate3D::setSpeed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate3D_setWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setWeight");
	LUA_TRY_INVOKE(1, &cc::Animate3D::setWeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::Animate3D>(*)(cc::Animation3D*, float, float)>(&cc::Animate3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::Animate3D>(*)(cc::Animation3D*)>(&cc::Animate3D::create));
	LUA_SINVOKE_FOOTER("1,3");
}
int lua_cc_Animate3D_createWithFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:createWithFrames");
	LUA_TRY_INVOKE_R(4, &cc::Animate3D::createWithFrames);
	LUA_TRY_INVOKE_R(3, ([](cc::Animation3D* arg0,int arg1,int arg2){{return cc::Animate3D::createWithFrames(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int lua_cc_Animate3D_getTransitionTime(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getTransitionTime");
	LUA_TRY_INVOKE_R(0, &cc::Animate3D::getTransitionTime);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Animate3D_setTransitionTime(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setTransitionTime");
	LUA_TRY_INVOKE(1, &cc::Animate3D::setTransitionTime);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccAnimate3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Animate3D, "Animate3D", "cc.Animate3D",
		cc::Animate3D, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getOriginInterval", lua_cc_Animate3D_getOriginInterval);
	LUA_METHOD("getQuality", lua_cc_Animate3D_getQuality);
	LUA_METHOD("getSpeed", lua_cc_Animate3D_getSpeed);
	LUA_METHOD("getWeight", lua_cc_Animate3D_getWeight);
	LUA_METHOD("init", lua_cc_Animate3D_init);
	LUA_METHOD("initWithFrames", lua_cc_Animate3D_initWithFrames);
	LUA_METHOD("removeFromMap", lua_cc_Animate3D_removeFromMap);
	LUA_METHOD("setKeyFrameUserInfo", lua_cc_Animate3D_setKeyFrameUserInfo);
	LUA_METHOD("setOriginInterval", lua_cc_Animate3D_setOriginInterval);
	LUA_METHOD("setQuality", lua_cc_Animate3D_setQuality);
	LUA_METHOD("setSpeed", lua_cc_Animate3D_setSpeed);
	LUA_METHOD("setWeight", lua_cc_Animate3D_setWeight);
	LUA_METHOD("create", lua_cc_Animate3D_create);
	LUA_METHOD("createWithFrames", lua_cc_Animate3D_createWithFrames);
	LUA_METHOD("getTransitionTime", lua_cc_Animate3D_getTransitionTime);
	LUA_METHOD("setTransitionTime", lua_cc_Animate3D_setTransitionTime);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TextureCube_getBackendTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:getBackendTexture");
	LUA_TRY_INVOKE_R(0, &cc::TextureCube::getBackendTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCube_getImagePaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:getImagePaths");
	LUA_TRY_INVOKE_R(0, &cc::TextureCube::getImagePaths);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCube_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:reloadTexture");
	LUA_TRY_INVOKE_R(0, &cc::TextureCube::reloadTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCube_setTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:setTexParameters");
	LUA_TRY_INVOKE(1, &cc::TextureCube::setTexParameters);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCube_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCube", "cc.TextureCube:create");
	LUA_TRY_INVOKE_R(6, &cc::TextureCube::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_ThreeD_ccTextureCube(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TextureCube, "TextureCube", "cc.TextureCube",
		cc::TextureCube, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBackendTexture", lua_cc_TextureCube_getBackendTexture);
	LUA_METHOD("getImagePaths", lua_cc_TextureCube_getImagePaths);
	LUA_METHOD("reloadTexture", lua_cc_TextureCube_reloadTexture);
	LUA_METHOD("setTexParameters", lua_cc_TextureCube_setTexParameters);
	LUA_METHOD("create", lua_cc_TextureCube_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_ThreeD_ccAttachNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AttachNode, "AttachNode", "cc.AttachNode",
		cc::AttachNode, "cc.Node",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_BillBoard_getMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BillBoard", "cc.BillBoard:getMode");
	LUA_TRY_INVOKE_R(0, &cc::BillBoard::getMode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_BillBoard_setMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BillBoard", "cc.BillBoard:setMode");
	LUA_TRY_INVOKE(1, &cc::BillBoard::setMode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_BillBoard_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BillBoard", "cc.BillBoard:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::BillBoard>(*)(std::string_view, const cc::Rect&, cc::BillBoard::Mode)>(&cc::BillBoard::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](std::string_view arg0,const cc::Rect& arg1){{return cc::BillBoard::create(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::BillBoard>(*)(std::string_view, cc::BillBoard::Mode)>(&cc::BillBoard::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(1, [](std::string_view arg0){{return cc::BillBoard::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cc::IntrusivePtr<cc::BillBoard>(*)(cc::BillBoard::Mode)>(&cc::BillBoard::create));
	LUA_TRY_INVOKE_R(0, [](){{return cc::BillBoard::create();}});
	LUA_SINVOKE_FOOTER("0,1,2,3");
}
int lua_cc_BillBoard_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BillBoard", "cc.BillBoard:createWithTexture");
	LUA_TRY_INVOKE_R(2, &cc::BillBoard::createWithTexture);
	LUA_TRY_INVOKE_R(1, [](cc::Texture2D* arg0){{return cc::BillBoard::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccBillBoard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::BillBoard, "BillBoard", "cc.BillBoard",
		cc::BillBoard, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("getMode", lua_cc_BillBoard_getMode);
	LUA_METHOD("setMode", lua_cc_BillBoard_setMode);
	LUA_METHOD("create", lua_cc_BillBoard_create);
	LUA_METHOD("createWithTexture", lua_cc_BillBoard_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Mesh_calculateAABB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:calculateAABB");
	LUA_TRY_INVOKE(0, &cc::Mesh::calculateAABB);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:draw");
	LUA_TRY_INVOKE(8, &cc::Mesh::draw);
	LUA_INVOKE_FOOTER("8");
}
int lua_cc_Mesh_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_getMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMaterial");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getMaterial);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_getMeshVertexAttribCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMeshVertexAttribCount");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getMeshVertexAttribCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_getMeshVertexAttribute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMeshVertexAttribute");
	LUA_TRY_INVOKE_R(1, &cc::Mesh::getMeshVertexAttribute);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getName");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getProgramState");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getProgramState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_getVertexSizeInBytes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getVertexSizeInBytes");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::getVertexSizeInBytes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:isVisible");
	LUA_TRY_INVOKE_R(0, &cc::Mesh::isVisible);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Mesh_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::Mesh::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_setIndexFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setIndexFormat");
	LUA_TRY_INVOKE(1, &cc::Mesh::setIndexFormat);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setMaterial");
	LUA_TRY_INVOKE(1, &cc::Mesh::setMaterial);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setName");
	LUA_TRY_INVOKE(1, &cc::Mesh::setName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_setProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setProgramState");
	LUA_TRY_INVOKE(1, &cc::Mesh::setProgramState);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Mesh_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setVisible");
	LUA_TRY_INVOKE(1, &cc::Mesh::setVisible);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccMesh(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Mesh, "Mesh", "cc.Mesh",
		cc::Mesh, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("calculateAABB", lua_cc_Mesh_calculateAABB);
	LUA_METHOD("draw", lua_cc_Mesh_draw);
	LUA_METHOD("getBlendFunc", lua_cc_Mesh_getBlendFunc);
	LUA_METHOD("getMaterial", lua_cc_Mesh_getMaterial);
	LUA_METHOD("getMeshVertexAttribCount", lua_cc_Mesh_getMeshVertexAttribCount);
	LUA_METHOD("getMeshVertexAttribute", lua_cc_Mesh_getMeshVertexAttribute);
	LUA_METHOD("getName", lua_cc_Mesh_getName);
	LUA_METHOD("getProgramState", lua_cc_Mesh_getProgramState);
	LUA_METHOD("getVertexSizeInBytes", lua_cc_Mesh_getVertexSizeInBytes);
	LUA_METHOD("isVisible", lua_cc_Mesh_isVisible);
	LUA_METHOD("setBlendFunc", lua_cc_Mesh_setBlendFunc);
	LUA_METHOD("setIndexFormat", lua_cc_Mesh_setIndexFormat);
	LUA_METHOD("setMaterial", lua_cc_Mesh_setMaterial);
	LUA_METHOD("setName", lua_cc_Mesh_setName);
	LUA_METHOD("setProgramState", lua_cc_Mesh_setProgramState);
	LUA_METHOD("setVisible", lua_cc_Mesh_setVisible);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Skeleton3D_getBoneCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:getBoneCount");
	LUA_TRY_INVOKE_R(0, &cc::Skeleton3D::getBoneCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Skeleton3D_getRootCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:getRootCount");
	LUA_TRY_INVOKE_R(0, &cc::Skeleton3D::getRootCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Skeleton3D_removeAllBones(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:removeAllBones");
	LUA_TRY_INVOKE(0, &cc::Skeleton3D::removeAllBones);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Skeleton3D_updateBoneMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:updateBoneMatrix");
	LUA_TRY_INVOKE(0, &cc::Skeleton3D::updateBoneMatrix);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccSkeleton3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Skeleton3D, "Skeleton3D", "cc.Skeleton3D",
		cc::Skeleton3D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBoneCount", lua_cc_Skeleton3D_getBoneCount);
	LUA_METHOD("getRootCount", lua_cc_Skeleton3D_getRootCount);
	LUA_METHOD("removeAllBones", lua_cc_Skeleton3D_removeAllBones);
	LUA_METHOD("updateBoneMatrix", lua_cc_Skeleton3D_updateBoneMatrix);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Skybox_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:init");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cc::Skybox::*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cc::Skybox::init)));
	LUA_INVOKE_FOOTER("6");
}
int lua_cc_Skybox_reload(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:reload");
	LUA_TRY_INVOKE(0, &cc::Skybox::reload);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Skybox_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:setTexture");
	LUA_TRY_INVOKE(1, &cc::Skybox::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Skybox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Skybox", "cc.Skybox:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cc::Skybox>(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cc::Skybox::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Skybox>(*)()>(&cc::Skybox::create));
	LUA_SINVOKE_FOOTER("0,6");
}
int luaReg_ThreeD_ccSkybox(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Skybox, "Skybox", "cc.Skybox",
		cc::Skybox, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_Skybox_init_1);
	LUA_METHOD("reload", lua_cc_Skybox_reload);
	LUA_METHOD("setTexture", lua_cc_Skybox_setTexture);
	LUA_METHOD("create", lua_cc_Skybox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MeshRenderer_genMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:genMaterial");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::genMaterial);
	LUA_TRY_INVOKE(0, [](cc::MeshRenderer* obj){{return obj->genMaterial();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_MeshRenderer_getAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getAttachNode");
	LUA_TRY_INVOKE_R(1, &cc::MeshRenderer::getAttachNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_getLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getLightMask");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getLightMask);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_getMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMaterial");
	LUA_TRY_INVOKE_R(1, &cc::MeshRenderer::getMaterial);
	LUA_TRY_INVOKE_R(0, [](const cc::MeshRenderer* obj){{return obj->getMaterial();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_MeshRenderer_getMesh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMesh");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getMesh);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_getMeshByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshByIndex");
	LUA_TRY_INVOKE_R(1, &cc::MeshRenderer::getMeshByIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_getMeshByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshByName");
	LUA_TRY_INVOKE_R(1, &cc::MeshRenderer::getMeshByName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_getMeshCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshCount");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getMeshCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_getMeshes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshes");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getMeshes);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_getSkeleton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getSkeleton");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::getSkeleton);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_isForceDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:isForceDepthWrite");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::isForceDepthWrite);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_isWireframe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:isWireframe");
	LUA_TRY_INVOKE_R(0, &cc::MeshRenderer::isWireframe);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_removeAllAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:removeAllAttachNode");
	LUA_TRY_INVOKE(0, &cc::MeshRenderer::removeAllAttachNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRenderer_removeAttachNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:removeAttachNode");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::removeAttachNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setCullFace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setCullFace");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setCullFace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setCullFaceEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setCullFaceEnabled");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setCullFaceEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setForceDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setForceDepthWrite");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setForceDepthWrite);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setLightMask");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setLightMask);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setMaterial");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::MeshRenderer::*)(cc::Material*, int)>(&cc::MeshRenderer::setMaterial)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::MeshRenderer::*)(cc::Material*)>(&cc::MeshRenderer::setMaterial));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_MeshRenderer_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setTexture");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::MeshRenderer::*)(cc::Texture2D*)>(&cc::MeshRenderer::setTexture));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::MeshRenderer::*)(std::string_view)>(&cc::MeshRenderer::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_setWireframe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setWireframe");
	LUA_TRY_INVOKE(1, &cc::MeshRenderer::setWireframe);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRenderer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::MeshRenderer>(*)(std::string_view, std::string_view)>(&cc::MeshRenderer::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::MeshRenderer>(*)(std::string_view)>(&cc::MeshRenderer::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::MeshRenderer>(*)()>(&cc::MeshRenderer::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int luaReg_ThreeD_ccMeshRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MeshRenderer, "MeshRenderer", "cc.MeshRenderer",
		cc::MeshRenderer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("genMaterial", lua_cc_MeshRenderer_genMaterial);
	LUA_METHOD("getAttachNode", lua_cc_MeshRenderer_getAttachNode);
	LUA_METHOD("getBlendFunc", lua_cc_MeshRenderer_getBlendFunc);
	LUA_METHOD("getLightMask", lua_cc_MeshRenderer_getLightMask);
	LUA_METHOD("getMaterial", lua_cc_MeshRenderer_getMaterial);
	LUA_METHOD("getMesh", lua_cc_MeshRenderer_getMesh);
	LUA_METHOD("getMeshByIndex", lua_cc_MeshRenderer_getMeshByIndex);
	LUA_METHOD("getMeshByName", lua_cc_MeshRenderer_getMeshByName);
	LUA_METHOD("getMeshCount", lua_cc_MeshRenderer_getMeshCount);
	LUA_METHOD("getMeshes", lua_cc_MeshRenderer_getMeshes);
	LUA_METHOD("getSkeleton", lua_cc_MeshRenderer_getSkeleton);
	LUA_METHOD("isForceDepthWrite", lua_cc_MeshRenderer_isForceDepthWrite);
	LUA_METHOD("isWireframe", lua_cc_MeshRenderer_isWireframe);
	LUA_METHOD("removeAllAttachNode", lua_cc_MeshRenderer_removeAllAttachNode);
	LUA_METHOD("removeAttachNode", lua_cc_MeshRenderer_removeAttachNode);
	LUA_METHOD("setBlendFunc", lua_cc_MeshRenderer_setBlendFunc);
	LUA_METHOD("setCullFace", lua_cc_MeshRenderer_setCullFace);
	LUA_METHOD("setCullFaceEnabled", lua_cc_MeshRenderer_setCullFaceEnabled);
	LUA_METHOD("setForceDepthWrite", lua_cc_MeshRenderer_setForceDepthWrite);
	LUA_METHOD("setLightMask", lua_cc_MeshRenderer_setLightMask);
	LUA_METHOD("setMaterial", lua_cc_MeshRenderer_setMaterial);
	LUA_METHOD("setTexture", lua_cc_MeshRenderer_setTexture);
	LUA_METHOD("setWireframe", lua_cc_MeshRenderer_setWireframe);
	LUA_METHOD("create", lua_cc_MeshRenderer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MeshRendererCache_removeAllMeshRenderData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:removeAllMeshRenderData");
	LUA_TRY_INVOKE(0, &cc::MeshRendererCache::removeAllMeshRenderData);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshRendererCache_removeMeshRenderData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:removeMeshRenderData");
	LUA_TRY_INVOKE(1, &cc::MeshRendererCache::removeMeshRenderData);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MeshRendererCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::MeshRendererCache::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccMeshRendererCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MeshRendererCache, "MeshRendererCache", "cc.MeshRendererCache",
		cc::MeshRendererCache, "",
		nullptr, nullptr);
	LUA_METHOD("removeAllMeshRenderData", lua_cc_MeshRendererCache_removeAllMeshRenderData);
	LUA_METHOD("removeMeshRenderData", lua_cc_MeshRendererCache_removeMeshRenderData);
	LUA_METHOD("getInstance", lua_cc_MeshRendererCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MeshMaterial_getMaterialType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:getMaterialType");
	LUA_TRY_INVOKE_R(0, &cc::MeshMaterial::getMaterialType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MeshMaterial_createBuiltInMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createBuiltInMaterial");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::MeshMaterial>(*)(cc::MeshMaterial::MaterialType, bool)>(&cc::MeshMaterial::createBuiltInMaterial)));
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cc::MeshMaterial::createBuiltInMaterial));
	LUA_SINVOKE_FOOTER("0,2");
}
int lua_cc_MeshMaterial_createWithFilename(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createWithFilename");
	LUA_TRY_INVOKE_R(1, &cc::MeshMaterial::createWithFilename);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_MeshMaterial_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:createWithProgramState");
	LUA_TRY_INVOKE_R(1, &cc::MeshMaterial::createWithProgramState);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_MeshMaterial_releaseBuiltInMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:releaseBuiltInMaterial");
	LUA_TRY_INVOKE(0, &cc::MeshMaterial::releaseBuiltInMaterial);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_MeshMaterial_releaseCachedMaterial(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshMaterial", "cc.MeshMaterial:releaseCachedMaterial");
	LUA_TRY_INVOKE(0, &cc::MeshMaterial::releaseCachedMaterial);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccMeshMaterial(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MeshMaterial, "MeshMaterial", "cc.MeshMaterial",
		cc::MeshMaterial, "cc.Material",
		nullptr, nullptr);
	LUA_METHOD("getMaterialType", lua_cc_MeshMaterial_getMaterialType);
	LUA_METHOD("createBuiltInMaterial", lua_cc_MeshMaterial_createBuiltInMaterial);
	LUA_METHOD("createWithFilename", lua_cc_MeshMaterial_createWithFilename);
	LUA_METHOD("createWithProgramState", lua_cc_MeshMaterial_createWithProgramState);
	LUA_METHOD("releaseBuiltInMaterial", lua_cc_MeshMaterial_releaseBuiltInMaterial);
	LUA_METHOD("releaseCachedMaterial", lua_cc_MeshMaterial_releaseCachedMaterial);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Terrain_convertToTerrainSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:convertToTerrainSpace");
	LUA_TRY_INVOKE_R(1, &cc::Terrain::convertToTerrainSpace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_getHeightData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getHeightData");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::getHeightData);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_getImageHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getImageHeight");
	LUA_TRY_INVOKE_R(2, &cc::Terrain::getImageHeight);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Terrain_getIntersectionPoint_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getIntersectionPoint");
	LUA_TRY_INVOKE_R(1, static_cast<cc::Vec3(cc::Terrain::*)(const cc::Ray&)const>(&cc::Terrain::getIntersectionPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_getMaxHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getMaxHeight");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::getMaxHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_getMinHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getMinHeight");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::getMinHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_getNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getNormal");
	LUA_TRY_INVOKE_R(2, &cc::Terrain::getNormal);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Terrain_getTerrainSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getTerrainSize");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::getTerrainSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_initHeightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initHeightMap");
	LUA_TRY_INVOKE_R(1, &cc::Terrain::initHeightMap);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_initProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initProperties");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::initProperties);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_initTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:initTextures");
	LUA_TRY_INVOKE_R(0, &cc::Terrain::initTextures);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_reload(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:reload");
	LUA_TRY_INVOKE(0, &cc::Terrain::reload);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Terrain_resetHeightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:resetHeightMap");
	LUA_TRY_INVOKE(1, &cc::Terrain::resetHeightMap);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setAlphaMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setAlphaMap");
	LUA_TRY_INVOKE(1, &cc::Terrain::setAlphaMap);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setDrawWire(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setDrawWire");
	LUA_TRY_INVOKE(1, &cc::Terrain::setDrawWire);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setIsEnableFrustumCull(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setIsEnableFrustumCull");
	LUA_TRY_INVOKE(1, &cc::Terrain::setIsEnableFrustumCull);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setLODDistance(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLODDistance");
	LUA_TRY_INVOKE(3, &cc::Terrain::setLODDistance);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_Terrain_setLightDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLightDir");
	LUA_TRY_INVOKE(1, &cc::Terrain::setLightDir);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setLightMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLightMap");
	LUA_TRY_INVOKE(1, &cc::Terrain::setLightMap);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setMaxDetailMapAmount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setMaxDetailMapAmount");
	LUA_TRY_INVOKE(1, &cc::Terrain::setMaxDetailMapAmount);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_setSkirtHeightRatio(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setSkirtHeightRatio");
	LUA_TRY_INVOKE(1, &cc::Terrain::setSkirtHeightRatio);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Terrain_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Terrain", "cc.Terrain:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::Terrain>(*)(cc::Terrain::TerrainData&, cc::Terrain::CrackFixedType)>(&cc::Terrain::create)));
	LUA_TRY_INVOKE_R(1, [](cc::Terrain::TerrainData& arg0){{return cc::Terrain::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccTerrain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Terrain, "Terrain", "cc.Terrain",
		cc::Terrain, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("convertToTerrainSpace", lua_cc_Terrain_convertToTerrainSpace);
	LUA_METHOD("getHeightData", lua_cc_Terrain_getHeightData);
	LUA_METHOD("getImageHeight", lua_cc_Terrain_getImageHeight);
	LUA_METHOD("getIntersectionPoint", lua_cc_Terrain_getIntersectionPoint_1);
	LUA_METHOD("getMaxHeight", lua_cc_Terrain_getMaxHeight);
	LUA_METHOD("getMinHeight", lua_cc_Terrain_getMinHeight);
	LUA_METHOD("getNormal", lua_cc_Terrain_getNormal);
	LUA_METHOD("getTerrainSize", lua_cc_Terrain_getTerrainSize);
	LUA_METHOD("initHeightMap", lua_cc_Terrain_initHeightMap);
	LUA_METHOD("initProperties", lua_cc_Terrain_initProperties);
	LUA_METHOD("initTextures", lua_cc_Terrain_initTextures);
	LUA_METHOD("reload", lua_cc_Terrain_reload);
	LUA_METHOD("resetHeightMap", lua_cc_Terrain_resetHeightMap);
	LUA_METHOD("setAlphaMap", lua_cc_Terrain_setAlphaMap);
	LUA_METHOD("setDrawWire", lua_cc_Terrain_setDrawWire);
	LUA_METHOD("setIsEnableFrustumCull", lua_cc_Terrain_setIsEnableFrustumCull);
	LUA_METHOD("setLODDistance", lua_cc_Terrain_setLODDistance);
	LUA_METHOD("setLightDir", lua_cc_Terrain_setLightDir);
	LUA_METHOD("setLightMap", lua_cc_Terrain_setLightMap);
	LUA_METHOD("setMaxDetailMapAmount", lua_cc_Terrain_setMaxDetailMapAmount);
	LUA_METHOD("setSkirtHeightRatio", lua_cc_Terrain_setSkirtHeightRatio);
	LUA_METHOD("create", lua_cc_Terrain_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Bundle3D_getTrianglesList(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:getTrianglesList");
	LUA_TRY_INVOKE_R(1, &cc::Bundle3D::getTrianglesList);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Bundle3D_parseGLDataType(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseGLDataType");
	LUA_TRY_INVOKE_R(2, &cc::Bundle3D::parseGLDataType);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cc_Bundle3D_parseSamplerAddressMode(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseSamplerAddressMode");
	LUA_TRY_INVOKE_R(1, &cc::Bundle3D::parseSamplerAddressMode);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccBundle3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Bundle3D, "Bundle3D", "cc.Bundle3D",
		cc::Bundle3D, "",
		nullptr, nullptr);
	LUA_METHOD("getTrianglesList", lua_cc_Bundle3D_getTrianglesList);
	LUA_METHOD("parseGLDataType", lua_cc_Bundle3D_parseGLDataType);
	LUA_METHOD("parseSamplerAddressMode", lua_cc_Bundle3D_parseSamplerAddressMode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int register_all_cc_3d(lua_State* lua_S)
{
	tolua_open(lua_S);
	luaReg_ThreeD_ccAnimation3D(lua_S);
	luaReg_ThreeD_ccAnimate3D(lua_S);
	luaReg_ThreeD_ccTextureCube(lua_S);
	luaReg_ThreeD_ccAttachNode(lua_S);
	luaReg_ThreeD_ccBillBoard(lua_S);
	luaReg_ThreeD_ccMesh(lua_S);
	luaReg_ThreeD_ccSkeleton3D(lua_S);
	luaReg_ThreeD_ccSkybox(lua_S);
	luaReg_ThreeD_ccMeshRenderer(lua_S);
	luaReg_ThreeD_ccMeshRendererCache(lua_S);
	luaReg_ThreeD_ccMeshMaterial(lua_S);
	luaReg_ThreeD_ccTerrain(lua_S);
	luaReg_ThreeD_ccBundle3D(lua_S);
	return 0;
}
