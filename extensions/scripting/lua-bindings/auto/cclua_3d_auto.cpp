#include "cclua_3d_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_3d_compat.hpp"
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
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::Animation3D::*)(std::string_view, std::string_view)>(&cocos2d::Animation3D::initWithFile));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animation3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation3D", "cc.Animation3D:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::Animation3D*(*)(std::string_view, std::string_view)>(&cocos2d::Animation3D::create));
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cocos2d::Animation3D::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_ThreeD_ccAnimation3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation3D, "Animation3D", "cc.Animation3D",
		cocos2d::Ref, "cc.Ref",
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
	LUA_TRY_INVOKE_R(3, static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*, float, float)>(&cocos2d::Animate3D::init));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*)>(&cocos2d::Animate3D::init));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cocos2d_Animate3D_initWithFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:initWithFrames");
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::Animate3D::*)(cocos2d::Animation3D*, int, int, float)>(&cocos2d::Animate3D::initWithFrames));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Animate3D_removeFromMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate3D", "cc.Animate3D:removeFromMap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Animate3D::*)()>(&cocos2d::Animate3D::removeFromMap));
	LUA_INVOKE_FOOTER("0");
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
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*, float, float)>(&cocos2d::Animate3D::create));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*)>(&cocos2d::Animate3D::create));
	LUA_SINVOKE_FOOTER("1,3");
}
int lua_cocos2d_Animate3D_createWithFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate3D", "cc.Animate3D:createWithFrames");
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::Animate3D*(*)(cocos2d::Animation3D*, int, int, float)>(&cocos2d::Animate3D::createWithFrames));
	LUA_TRY_INVOKE_R(3, [](cocos2d::Animation3D* arg0,int arg1,int arg2){{return cocos2d::Animate3D::createWithFrames(arg0,std::move(arg1),std::move(arg2));}});
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
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getOriginInterval", lua_cocos2d_Animate3D_getOriginInterval);
	LUA_METHOD("getQuality", lua_cocos2d_Animate3D_getQuality);
	LUA_METHOD("getSpeed", lua_cocos2d_Animate3D_getSpeed);
	LUA_METHOD("getWeight", lua_cocos2d_Animate3D_getWeight);
	LUA_METHOD("init", lua_cocos2d_Animate3D_init);
	LUA_METHOD("initWithFrames", lua_cocos2d_Animate3D_initWithFrames);
	LUA_METHOD("removeFromMap", lua_cocos2d_Animate3D_removeFromMap);
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
int lua_cocos2d_TextureCube_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCube", "cc.TextureCube:reloadTexture");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::TextureCube::*)()>(&cocos2d::TextureCube::reloadTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TextureCube_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCube", "cc.TextureCube:create");
	LUA_TRY_INVOKE_R(6, static_cast<cocos2d::TextureCube*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::TextureCube::create));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_ThreeD_ccTextureCube(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TextureCube, "TextureCube", "cc.TextureCube",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBackendTexture", lua_cocos2d_TextureCube_getBackendTexture);
	LUA_METHOD("reloadTexture", lua_cocos2d_TextureCube_reloadTexture);
	LUA_METHOD("create", lua_cocos2d_TextureCube_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_ThreeD_ccAttachNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AttachNode, "AttachNode", "cc.AttachNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
extern int luaReg_ThreeD_ccAnimation3D(lua_State* lua_S);
extern int luaReg_ThreeD_ccAnimate3D(lua_State* lua_S);
extern int luaReg_ThreeD_ccTextureCube(lua_State* lua_S);
extern int luaReg_ThreeD_ccAttachNode(lua_State* lua_S);
extern int luaReg_ThreeD_ccBillBoard(lua_State* lua_S);
extern int luaReg_ThreeD_ccMesh(lua_State* lua_S);
extern int luaReg_ThreeD_ccSkeleton3D(lua_State* lua_S);
extern int luaReg_ThreeD_ccSkybox(lua_State* lua_S);
extern int luaReg_ThreeD_ccMeshRenderer(lua_State* lua_S);
extern int luaReg_ThreeD_ccMeshRendererCache(lua_State* lua_S);
extern int luaReg_ThreeD_ccMeshMaterial(lua_State* lua_S);
extern int luaReg_ThreeD_ccTerrain(lua_State* lua_S);
extern int luaReg_ThreeD_ccBundle3D(lua_State* lua_S);

int register_all_cc_3d(lua_State* lua_S)
{
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
	return register_all_cc_3d_retained(lua_S);
}
