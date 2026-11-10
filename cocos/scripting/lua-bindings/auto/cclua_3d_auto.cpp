#include "cclua_3d_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"

int lua_cocos2d_Animation3D_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation3D", "cc.Animation3D:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation3D::*)()const>(&cocos2d::Animation3D::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation3D_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation3D", "cc.Animation3D:initWithFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Animation3D::*)(std::string_view, std::string_view)>(&cocos2d::Animation3D::initWithFile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animation3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation3D", "cc.Animation3D:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Animation3D*(*)(std::string_view, std::string_view)>(&cocos2d::Animation3D::create)));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::Animation3D::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccAnimation3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation3D, "Animation3D", "cc.Animation3D",
		cocos2d::Animation3D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getDuration", lua_cocos2d_Animation3D_getDuration);
	LUA_METHOD("initWithFile", lua_cocos2d_Animation3D_initWithFile);
	LUA_METHOD("create", lua_cocos2d_Animation3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animate3D_getOriginInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getOriginInterval");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animate3D::*)()const>(&cocos2d::Animate3D::getOriginInterval));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_getQuality(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getQuality");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Animate3DQuality(cocos2d::Animate3D::*)()const>(&cocos2d::Animate3D::getQuality));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animate3D::*)()const>(&cocos2d::Animate3D::getSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_getWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getWeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animate3D::*)()const>(&cocos2d::Animate3D::getWeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:init");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*, float, float)>(&cocos2d::Animate3D::init)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*)>(&cocos2d::Animate3D::init));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cocos2d_Animate3D_initWithFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:initWithFrames");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*, int, int, float)>(&cocos2d::Animate3D::initWithFrames)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Animate3D_removeFromMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:removeFromMap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Animate3D::*)()>(&cocos2d::Animate3D::removeFromMap));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_setKeyFrameUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setKeyFrameUserInfo");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Animate3D::*)(int, const cocos2d::ValueMap&)>(&cocos2d::Animate3D::setKeyFrameUserInfo)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animate3D_setOriginInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setOriginInterval");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate3D::*)(float)>(&cocos2d::Animate3D::setOriginInterval));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate3D_setQuality(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setQuality");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate3D::*)(cocos2d::Animate3DQuality)>(&cocos2d::Animate3D::setQuality));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate3D_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate3D::*)(float)>(&cocos2d::Animate3D::setSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate3D_setWeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setWeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate3D::*)(float)>(&cocos2d::Animate3D::setWeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*, float, float)>(&cocos2d::Animate3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*)>(&cocos2d::Animate3D::create));
	LUA_SINVOKE_FOOTER("1,3");
}
int lua_cocos2d_Animate3D_createWithFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:createWithFrames");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*, int, int, float)>(&cocos2d::Animate3D::createWithFrames)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Animation3D* arg0,int arg1,int arg2){{return cocos2d::Animate3D::createWithFrames(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int lua_cocos2d_Animate3D_getTransitionTime(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:getTransitionTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(*)()>(&cocos2d::Animate3D::getTransitionTime));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Animate3D_setTransitionTime(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:setTransitionTime");
	LUA_TRY_INVOKE(1, static_cast<void(*)(float)>(&cocos2d::Animate3D::setTransitionTime));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccAnimate3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animate3D, "Animate3D", "cc.Animate3D",
		cocos2d::Animate3D, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getOriginInterval", lua_cocos2d_Animate3D_getOriginInterval);
	LUA_METHOD("getQuality", lua_cocos2d_Animate3D_getQuality);
	LUA_METHOD("getSpeed", lua_cocos2d_Animate3D_getSpeed);
	LUA_METHOD("getWeight", lua_cocos2d_Animate3D_getWeight);
	LUA_METHOD("init", lua_cocos2d_Animate3D_init);
	LUA_METHOD("initWithFrames", lua_cocos2d_Animate3D_initWithFrames);
	LUA_METHOD("removeFromMap", lua_cocos2d_Animate3D_removeFromMap);
	LUA_METHOD("setKeyFrameUserInfo", lua_cocos2d_Animate3D_setKeyFrameUserInfo);
	LUA_METHOD("setOriginInterval", lua_cocos2d_Animate3D_setOriginInterval);
	LUA_METHOD("setQuality", lua_cocos2d_Animate3D_setQuality);
	LUA_METHOD("setSpeed", lua_cocos2d_Animate3D_setSpeed);
	LUA_METHOD("setWeight", lua_cocos2d_Animate3D_setWeight);
	LUA_METHOD("create", lua_cocos2d_Animate3D_create);
	LUA_METHOD("createWithFrames", lua_cocos2d_Animate3D_createWithFrames);
	LUA_METHOD("getTransitionTime", lua_cocos2d_Animate3D_getTransitionTime);
	LUA_METHOD("setTransitionTime", lua_cocos2d_Animate3D_setTransitionTime);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TextureCube_getBackendTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:getBackendTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::TextureBackend*(cocos2d::TextureCube::*)()>(&cocos2d::TextureCube::getBackendTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCube_getImagePaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:getImagePaths");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<std::string>&(cocos2d::TextureCube::*)()const>(&cocos2d::TextureCube::getImagePaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCube_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:reloadTexture");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::TextureCube::*)()>(&cocos2d::TextureCube::reloadTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCube_setTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:setTexParameters");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TextureCube::*)(const cocos2d::Texture2D::TexParams&)>(&cocos2d::TextureCube::setTexParameters));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TextureCube_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCube", "cc.TextureCube:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::TextureCube*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::TextureCube::create)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_ThreeD_ccTextureCube(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TextureCube, "TextureCube", "cc.TextureCube",
		cocos2d::TextureCube, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBackendTexture", lua_cocos2d_TextureCube_getBackendTexture);
	LUA_METHOD("getImagePaths", lua_cocos2d_TextureCube_getImagePaths);
	LUA_METHOD("reloadTexture", lua_cocos2d_TextureCube_reloadTexture);
	LUA_METHOD("setTexParameters", lua_cocos2d_TextureCube_setTexParameters);
	LUA_METHOD("create", lua_cocos2d_TextureCube_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_ThreeD_ccAttachNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AttachNode, "AttachNode", "cc.AttachNode",
		cocos2d::AttachNode, "cc.Node",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int lua_cocos2d_BillBoard_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BillBoard", "cc.BillBoard:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::BillBoard*(*)(std::string_view, const cocos2d::Rect&, cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](std::string_view arg0,const cocos2d::Rect& arg1){{return cocos2d::BillBoard::create(std::move(arg0),arg1);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::BillBoard*(*)(std::string_view, cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(1, [](std::string_view arg0){{return cocos2d::BillBoard::create(std::move(arg0));}});
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<cocos2d::BillBoard*(*)(cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::create));
	LUA_TRY_INVOKE_R(0, [](){{return cocos2d::BillBoard::create();}});
	LUA_SINVOKE_FOOTER("0,1,2,3");
}
int lua_cocos2d_BillBoard_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BillBoard", "cc.BillBoard:createWithTexture");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::BillBoard*(*)(cocos2d::Texture2D*, cocos2d::BillBoard::Mode)>(&cocos2d::BillBoard::createWithTexture)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Texture2D* arg0){{return cocos2d::BillBoard::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccBillBoard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BillBoard, "BillBoard", "cc.BillBoard",
		cocos2d::BillBoard, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("getMode", lua_cocos2d_BillBoard_getMode);
	LUA_METHOD("setMode", lua_cocos2d_BillBoard_setMode);
	LUA_METHOD("create", lua_cocos2d_BillBoard_create);
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
int lua_cocos2d_Mesh_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:draw");
	LUA_TRY_INVOKE(8, (static_cast<void(cocos2d::Mesh::*)(cocos2d::Renderer*, float, const cocos2d::Mat4&, uint32_t, unsigned int, const cocos2d::Vec4&, bool, bool)>(&cocos2d::Mesh::draw)));
	LUA_INVOKE_FOOTER("8");
}
int lua_cocos2d_Mesh_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMaterial");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Material*(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getMaterial));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getMeshVertexAttribCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMeshVertexAttribCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getMeshVertexAttribCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getMeshVertexAttribute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getMeshVertexAttribute");
	LUA_TRY_INVOKE_R(1, static_cast<const cocos2d::MeshVertexAttrib&(cocos2d::Mesh::*)(int)>(&cocos2d::Mesh::getMeshVertexAttribute));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Mesh_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:getProgramState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::ProgramState*(cocos2d::Mesh::*)()const>(&cocos2d::Mesh::getProgramState));
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
int lua_cocos2d_Mesh_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(const cocos2d::BlendFunc&)>(&cocos2d::Mesh::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_setIndexFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setIndexFormat");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(cocos2d::CustomCommand::IndexFormat)>(&cocos2d::Mesh::setIndexFormat));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Mesh_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Mesh", "cc.Mesh:setMaterial");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Mesh::*)(cocos2d::Material*)>(&cocos2d::Mesh::setMaterial));
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
		cocos2d::Mesh, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("calculateAABB", lua_cocos2d_Mesh_calculateAABB);
	LUA_METHOD("draw", lua_cocos2d_Mesh_draw);
	LUA_METHOD("getBlendFunc", lua_cocos2d_Mesh_getBlendFunc);
	LUA_METHOD("getMaterial", lua_cocos2d_Mesh_getMaterial);
	LUA_METHOD("getMeshVertexAttribCount", lua_cocos2d_Mesh_getMeshVertexAttribCount);
	LUA_METHOD("getMeshVertexAttribute", lua_cocos2d_Mesh_getMeshVertexAttribute);
	LUA_METHOD("getName", lua_cocos2d_Mesh_getName);
	LUA_METHOD("getProgramState", lua_cocos2d_Mesh_getProgramState);
	LUA_METHOD("getVertexSizeInBytes", lua_cocos2d_Mesh_getVertexSizeInBytes);
	LUA_METHOD("isVisible", lua_cocos2d_Mesh_isVisible);
	LUA_METHOD("setBlendFunc", lua_cocos2d_Mesh_setBlendFunc);
	LUA_METHOD("setIndexFormat", lua_cocos2d_Mesh_setIndexFormat);
	LUA_METHOD("setMaterial", lua_cocos2d_Mesh_setMaterial);
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
		cocos2d::Skeleton3D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBoneCount", lua_cocos2d_Skeleton3D_getBoneCount);
	LUA_METHOD("getRootCount", lua_cocos2d_Skeleton3D_getRootCount);
	LUA_METHOD("removeAllBones", lua_cocos2d_Skeleton3D_removeAllBones);
	LUA_METHOD("updateBoneMatrix", lua_cocos2d_Skeleton3D_updateBoneMatrix);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Skybox_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Skybox", "cc.Skybox:init");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::Skybox::*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::Skybox::init)));
	LUA_INVOKE_FOOTER("6");
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
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::Skybox*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::Skybox::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Skybox*(*)()>(&cocos2d::Skybox::create));
	LUA_SINVOKE_FOOTER("0,6");
}
int luaReg_ThreeD_ccSkybox(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Skybox, "Skybox", "cc.Skybox",
		cocos2d::Skybox, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Skybox_init_1);
	LUA_METHOD("reload", lua_cocos2d_Skybox_reload);
	LUA_METHOD("setTexture", lua_cocos2d_Skybox_setTexture);
	LUA_METHOD("create", lua_cocos2d_Skybox_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
int lua_cocos2d_MeshRenderer_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getLightMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getLightMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getLightMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMaterial");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Material*(cocos2d::MeshRenderer::*)(int)const>(&cocos2d::MeshRenderer::getMaterial));
	LUA_TRY_INVOKE_R(0, [](const cocos2d::MeshRenderer* obj){{return obj->getMaterial();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_MeshRenderer_getMesh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMesh");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mesh*(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getMesh));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getMeshByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshByIndex");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Mesh*(cocos2d::MeshRenderer::*)(int)const>(&cocos2d::MeshRenderer::getMeshByIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_getMeshByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshByName");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Mesh*(cocos2d::MeshRenderer::*)(std::string_view)const>(&cocos2d::MeshRenderer::getMeshByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_getMeshCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getMeshCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getMeshes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getMeshes");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::Mesh *>&(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getMeshes));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MeshRenderer_getSkeleton(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:getSkeleton");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Skeleton3D*(cocos2d::MeshRenderer::*)()const>(&cocos2d::MeshRenderer::getSkeleton));
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
int lua_cocos2d_MeshRenderer_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(const cocos2d::BlendFunc&)>(&cocos2d::MeshRenderer::setBlendFunc));
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
int lua_cocos2d_MeshRenderer_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setMaterial");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::MeshRenderer::*)(cocos2d::Material*, int)>(&cocos2d::MeshRenderer::setMaterial)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(cocos2d::Material*)>(&cocos2d::MeshRenderer::setMaterial));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_MeshRenderer_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setTexture");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::MeshRenderer::*)(cocos2d::Texture2D*)>(&cocos2d::MeshRenderer::setTexture));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::MeshRenderer::*)(std::string_view)>(&cocos2d::MeshRenderer::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_setWireframe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:setWireframe");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MeshRenderer::*)(bool)>(&cocos2d::MeshRenderer::setWireframe));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MeshRenderer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshRenderer", "cc.MeshRenderer:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::MeshRenderer*(*)(std::string_view, std::string_view)>(&cocos2d::MeshRenderer::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::MeshRenderer*(*)(std::string_view)>(&cocos2d::MeshRenderer::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::MeshRenderer*(*)()>(&cocos2d::MeshRenderer::create));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int luaReg_ThreeD_ccMeshRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MeshRenderer, "MeshRenderer", "cc.MeshRenderer",
		cocos2d::MeshRenderer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("genMaterial", lua_cocos2d_MeshRenderer_genMaterial);
	LUA_METHOD("getAttachNode", lua_cocos2d_MeshRenderer_getAttachNode);
	LUA_METHOD("getBlendFunc", lua_cocos2d_MeshRenderer_getBlendFunc);
	LUA_METHOD("getLightMask", lua_cocos2d_MeshRenderer_getLightMask);
	LUA_METHOD("getMaterial", lua_cocos2d_MeshRenderer_getMaterial);
	LUA_METHOD("getMesh", lua_cocos2d_MeshRenderer_getMesh);
	LUA_METHOD("getMeshByIndex", lua_cocos2d_MeshRenderer_getMeshByIndex);
	LUA_METHOD("getMeshByName", lua_cocos2d_MeshRenderer_getMeshByName);
	LUA_METHOD("getMeshCount", lua_cocos2d_MeshRenderer_getMeshCount);
	LUA_METHOD("getMeshes", lua_cocos2d_MeshRenderer_getMeshes);
	LUA_METHOD("getSkeleton", lua_cocos2d_MeshRenderer_getSkeleton);
	LUA_METHOD("isForceDepthWrite", lua_cocos2d_MeshRenderer_isForceDepthWrite);
	LUA_METHOD("isWireframe", lua_cocos2d_MeshRenderer_isWireframe);
	LUA_METHOD("removeAllAttachNode", lua_cocos2d_MeshRenderer_removeAllAttachNode);
	LUA_METHOD("removeAttachNode", lua_cocos2d_MeshRenderer_removeAttachNode);
	LUA_METHOD("setBlendFunc", lua_cocos2d_MeshRenderer_setBlendFunc);
	LUA_METHOD("setCullFace", lua_cocos2d_MeshRenderer_setCullFace);
	LUA_METHOD("setCullFaceEnabled", lua_cocos2d_MeshRenderer_setCullFaceEnabled);
	LUA_METHOD("setForceDepthWrite", lua_cocos2d_MeshRenderer_setForceDepthWrite);
	LUA_METHOD("setLightMask", lua_cocos2d_MeshRenderer_setLightMask);
	LUA_METHOD("setMaterial", lua_cocos2d_MeshRenderer_setMaterial);
	LUA_METHOD("setTexture", lua_cocos2d_MeshRenderer_setTexture);
	LUA_METHOD("setWireframe", lua_cocos2d_MeshRenderer_setWireframe);
	LUA_METHOD("create", lua_cocos2d_MeshRenderer_create);
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
int lua_cocos2d_MeshRendererCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MeshRendererCache", "cc.MeshRendererCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::MeshRendererCache*(*)()>(&cocos2d::MeshRendererCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_ThreeD_ccMeshRendererCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MeshRendererCache, "MeshRendererCache", "cc.MeshRendererCache",
		cocos2d::MeshRendererCache, "",
		nullptr, nullptr);
	LUA_METHOD("removeAllMeshRenderData", lua_cocos2d_MeshRendererCache_removeAllMeshRenderData);
	LUA_METHOD("removeMeshRenderData", lua_cocos2d_MeshRendererCache_removeMeshRenderData);
	LUA_METHOD("getInstance", lua_cocos2d_MeshRendererCache_getInstance);
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::MeshMaterial*(*)(cocos2d::MeshMaterial::MaterialType, bool)>(&cocos2d::MeshMaterial::createBuiltInMaterial)));
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
		cocos2d::MeshMaterial, "cc.Material",
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
int lua_cocos2d_Terrain_convertToTerrainSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:convertToTerrainSpace");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Terrain::*)(const cocos2d::Vec2&)const>(&cocos2d::Terrain::convertToTerrainSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Terrain_getHeightData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getHeightData");
	LUA_TRY_INVOKE_R(0, static_cast<std::vector<float>(cocos2d::Terrain::*)()const>(&cocos2d::Terrain::getHeightData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Terrain_getImageHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getImageHeight");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocos2d::Terrain::*)(int, int)const>(&cocos2d::Terrain::getImageHeight)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Terrain_getIntersectionPoint_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getIntersectionPoint");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec3(cocos2d::Terrain::*)(const cocos2d::Ray&)const>(&cocos2d::Terrain::getIntersectionPoint));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_Terrain_getNormal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getNormal");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Vec3(cocos2d::Terrain::*)(int, int)const>(&cocos2d::Terrain::getNormal)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Terrain_getTerrainSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:getTerrainSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Terrain::*)()const>(&cocos2d::Terrain::getTerrainSize));
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
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Terrain::*)(float, float, float)>(&cocos2d::Terrain::setLODDistance)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Terrain_setLightDir(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Terrain", "cc.Terrain:setLightDir");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Terrain::*)(const cocos2d::Vec3&)>(&cocos2d::Terrain::setLightDir));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_Terrain_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Terrain", "cc.Terrain:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Terrain*(*)(cocos2d::Terrain::TerrainData&, cocos2d::Terrain::CrackFixedType)>(&cocos2d::Terrain::create)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Terrain::TerrainData& arg0){{return cocos2d::Terrain::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccTerrain(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Terrain, "Terrain", "cc.Terrain",
		cocos2d::Terrain, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("convertToTerrainSpace", lua_cocos2d_Terrain_convertToTerrainSpace);
	LUA_METHOD("getHeightData", lua_cocos2d_Terrain_getHeightData);
	LUA_METHOD("getImageHeight", lua_cocos2d_Terrain_getImageHeight);
	LUA_METHOD("getIntersectionPoint", lua_cocos2d_Terrain_getIntersectionPoint_1);
	LUA_METHOD("getMaxHeight", lua_cocos2d_Terrain_getMaxHeight);
	LUA_METHOD("getMinHeight", lua_cocos2d_Terrain_getMinHeight);
	LUA_METHOD("getNormal", lua_cocos2d_Terrain_getNormal);
	LUA_METHOD("getTerrainSize", lua_cocos2d_Terrain_getTerrainSize);
	LUA_METHOD("initHeightMap", lua_cocos2d_Terrain_initHeightMap);
	LUA_METHOD("initProperties", lua_cocos2d_Terrain_initProperties);
	LUA_METHOD("initTextures", lua_cocos2d_Terrain_initTextures);
	LUA_METHOD("reload", lua_cocos2d_Terrain_reload);
	LUA_METHOD("resetHeightMap", lua_cocos2d_Terrain_resetHeightMap);
	LUA_METHOD("setAlphaMap", lua_cocos2d_Terrain_setAlphaMap);
	LUA_METHOD("setDrawWire", lua_cocos2d_Terrain_setDrawWire);
	LUA_METHOD("setIsEnableFrustumCull", lua_cocos2d_Terrain_setIsEnableFrustumCull);
	LUA_METHOD("setLODDistance", lua_cocos2d_Terrain_setLODDistance);
	LUA_METHOD("setLightDir", lua_cocos2d_Terrain_setLightDir);
	LUA_METHOD("setLightMap", lua_cocos2d_Terrain_setLightMap);
	LUA_METHOD("setMaxDetailMapAmount", lua_cocos2d_Terrain_setMaxDetailMapAmount);
	LUA_METHOD("setSkirtHeightRatio", lua_cocos2d_Terrain_setSkirtHeightRatio);
	LUA_METHOD("create", lua_cocos2d_Terrain_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Bundle3D_getTrianglesList(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:getTrianglesList");
	LUA_TRY_INVOKE_R(1, static_cast<std::vector<cocos2d::Vec3>(*)(std::string_view)>(&cocos2d::Bundle3D::getTrianglesList));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Bundle3D_parseGLDataType(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseGLDataType");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::backend::VertexFormat(*)(std::string_view, int)>(&cocos2d::Bundle3D::parseGLDataType)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Bundle3D_parseSamplerAddressMode(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Bundle3D", "cc.Bundle3D:parseSamplerAddressMode");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::SamplerAddressMode(*)(std::string_view)>(&cocos2d::Bundle3D::parseSamplerAddressMode));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_ThreeD_ccBundle3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Bundle3D, "Bundle3D", "cc.Bundle3D",
		cocos2d::Bundle3D, "",
		nullptr, nullptr);
	LUA_METHOD("getTrianglesList", lua_cocos2d_Bundle3D_getTrianglesList);
	LUA_METHOD("parseGLDataType", lua_cocos2d_Bundle3D_parseGLDataType);
	LUA_METHOD("parseSamplerAddressMode", lua_cocos2d_Bundle3D_parseSamplerAddressMode);
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
