#include "cclua_3d_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_3d_compat.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"

int lua_cocos2d_BillBoard_getMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BillBoard", "cc.BillBoard:getMode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::BillBoard::Mode(cocos2d::BillBoard::*)()const>(&cocos2d::BillBoard::getMode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_BillBoard_setMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BillBoard", "cc.BillBoard:setMode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::BillBoard::*)(cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::setMode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_BillBoard_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BillBoard", "cc.BillBoard:createWithTexture");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::BillBoard*(*)(cocos2d::Texture2D*, cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::createWithTexture));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::BillBoard::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccBillBoard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BillBoard, "BillBoard", "cc.BillBoard",
		cocos2d::Sprite, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("getMode", lua_cocos2d_BillBoard_getMode);
	LUA_METHOD("setMode", lua_cocos2d_BillBoard_setMode);
	LUA_METHOD("createWithTexture", lua_cocos2d_BillBoard_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Mesh_calculateAABB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:calculateAABB");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Mesh::*)()>(&cocos2d::Mesh::calculateAABB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getMeshVertexAttribCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMeshVertexAttribCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getMeshVertexAttribCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getVertexSizeInBytes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getVertexSizeInBytes");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getVertexSizeInBytes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:isVisible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::isVisible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_setIndexFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setIndexFormat");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(cocos2d::CustomCommand::IndexFormat)>(&cocos2d::Mesh::setIndexFormat));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(std::string_view)>(&cocos2d::Mesh::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_setProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setProgramState");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(cocos2d::backend::ProgramState*)>(&cocos2d::Mesh::setProgramState));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(bool)>(&cocos2d::Mesh::setVisible));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccMesh(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Mesh, "Mesh", "cc.Mesh",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("calculateAABB", lua_cocos2d_Mesh_calculateAABB);
	LUA_METHOD("getMeshVertexAttribCount", lua_cocos2d_Mesh_getMeshVertexAttribCount);
	LUA_METHOD("getName", lua_cocos2d_Mesh_getName);
	LUA_METHOD("getVertexSizeInBytes", lua_cocos2d_Mesh_getVertexSizeInBytes);
	LUA_METHOD("isVisible", lua_cocos2d_Mesh_isVisible);
	LUA_METHOD("setIndexFormat", lua_cocos2d_Mesh_setIndexFormat);
	LUA_METHOD("setName", lua_cocos2d_Mesh_setName);
	LUA_METHOD("setProgramState", lua_cocos2d_Mesh_setProgramState);
	LUA_METHOD("setVisible", lua_cocos2d_Mesh_setVisible);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Skeleton3D_getBoneCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:getBoneCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Skeleton3D::*)()const>(&cocos2d::Skeleton3D::getBoneCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Skeleton3D_getRootCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:getRootCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Skeleton3D::*)()const>(&cocos2d::Skeleton3D::getRootCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Skeleton3D_removeAllBones(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:removeAllBones");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Skeleton3D::*)()>(&cocos2d::Skeleton3D::removeAllBones));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Skeleton3D_updateBoneMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skeleton3D", "cc.Skeleton3D:updateBoneMatrix");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Skeleton3D::*)()>(&cocos2d::Skeleton3D::updateBoneMatrix));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccSkeleton3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Skeleton3D, "Skeleton3D", "cc.Skeleton3D",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBoneCount", lua_cocos2d_Skeleton3D_getBoneCount);
	LUA_METHOD("getRootCount", lua_cocos2d_Skeleton3D_getRootCount);
	LUA_METHOD("removeAllBones", lua_cocos2d_Skeleton3D_removeAllBones);
	LUA_METHOD("updateBoneMatrix", lua_cocos2d_Skeleton3D_updateBoneMatrix);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Skybox_reload(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:reload");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Skybox::*)()>(&cocos2d::Skybox::reload));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Skybox_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Skybox::*)(cocos2d::TextureCube*)>(&cocos2d::Skybox::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Skybox_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Skybox", "cc.Skybox:create");
	LUA_TRY_INVOKE_R(6, static_cast<cocos2d::Skybox*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::Skybox::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Skybox*(*)()>(&cocos2d::Skybox::create));
	LUA_SINVOKE_FOOTER("0,6");
}
int luaReg_ThreeD_ccSkybox(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Skybox, "Skybox", "cc.Skybox",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("reload", lua_cocos2d_Skybox_reload);
	LUA_METHOD("setTexture", lua_cocos2d_Skybox_setTexture);
	LUA_METHOD("create", lua_cocos2d_Skybox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
