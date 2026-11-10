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
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#endif

int lua_cocos2d_RenderTexture_begin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:begin");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::RenderTexture::*)()>(&cocos2d::RenderTexture::begin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_beginWithClear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:beginWithClear");
	LUA_TRY_INVOKE(6, (static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float, float, int)>(&cocos2d::RenderTexture::beginWithClear)));
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float, float)>(&cocos2d::RenderTexture::beginWithClear)));
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float)>(&cocos2d::RenderTexture::beginWithClear)));
	LUA_INVOKE_FOOTER("4,5,6");
}
int lua_cocos2d_RenderTexture_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clear");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float)>(&cocos2d::RenderTexture::clear)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_RenderTexture_clearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clearDepth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(float)>(&cocos2d::RenderTexture::clearDepth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_clearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clearStencil");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(int)>(&cocos2d::RenderTexture::clearStencil));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:endToLua");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::RenderTexture::*)()>(&cocos2d::RenderTexture::end));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color4F&(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getClearColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearDepth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getClearDepth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getClearFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearFlags");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ClearFlag(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getClearFlags));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearStencil");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getClearStencil));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::RenderTarget*(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getSprite");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getSprite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_initWithWidthAndHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:initWithWidthAndHeight");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::RenderTexture::*)(int, int, cocos2d::backend::PixelFormat, cocos2d::backend::PixelFormat, bool)>(&cocos2d::RenderTexture::initWithWidthAndHeight)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](cocos2d::RenderTexture* obj,int arg0,int arg1,cocos2d::backend::PixelFormat arg2,cocos2d::backend::PixelFormat arg3){{return obj->initWithWidthAndHeight(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<bool(cocos2d::RenderTexture::*)(int, int, cocos2d::backend::PixelFormat, bool)>(&cocos2d::RenderTexture::initWithWidthAndHeight)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::RenderTexture* obj,int arg0,int arg1,cocos2d::backend::PixelFormat arg2){{return obj->initWithWidthAndHeight(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4,5");
}
int lua_cocos2d_RenderTexture_isAutoDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:isAutoDraw");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::isAutoDraw));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_isSharedRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:isSharedRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::isSharedRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_newImage_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:newImage");
	if (argc == 2 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::RenderTexture::*)(std::function<void(cocos2d::RefPtr<cocos2d::Image>)>, bool)>(&cocos2d::RenderTexture::newImage)));
	}
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, ([](cocos2d::RenderTexture* obj,std::function<void(cocos2d::RefPtr<cocos2d::Image>)> arg0){{return obj->newImage(std::move(arg0));}}));
	}
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_RenderTexture_saveToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:saveToFile");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::RenderTexture::*)(std::string_view, cocos2d::Image::Format, bool, cocos2d::RenderTexture::SaveFileCallbackType)>(&cocos2d::RenderTexture::saveToFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cocos2d::RenderTexture* obj,std::string_view arg0,cocos2d::Image::Format arg1,bool arg2){{return obj->saveToFile(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cocos2d::RenderTexture::*)(std::string_view, bool, cocos2d::RenderTexture::SaveFileCallbackType)>(&cocos2d::RenderTexture::saveToFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cocos2d::RenderTexture* obj,std::string_view arg0,cocos2d::Image::Format arg1){{return obj->saveToFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cocos2d::RenderTexture* obj,std::string_view arg0,bool arg1){{return obj->saveToFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::RenderTexture* obj,std::string_view arg0){{return obj->saveToFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_RenderTexture_saveToFileAsNonPMA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:saveToFileAsNonPMA");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::RenderTexture::*)(std::string_view, cocos2d::Image::Format, bool, cocos2d::RenderTexture::SaveFileCallbackType)>(&cocos2d::RenderTexture::saveToFileAsNonPMA)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RenderTexture::*)(std::string_view, bool, cocos2d::RenderTexture::SaveFileCallbackType)>(&cocos2d::RenderTexture::saveToFileAsNonPMA)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::RenderTexture* obj,std::string_view arg0,bool arg1){{return obj->saveToFileAsNonPMA(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::RenderTexture* obj,std::string_view arg0){{return obj->saveToFileAsNonPMA(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_RenderTexture_setAutoDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setAutoDraw");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(bool)>(&cocos2d::RenderTexture::setAutoDraw));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(const cocos2d::Color4F&)>(&cocos2d::RenderTexture::setClearColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearDepth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(float)>(&cocos2d::RenderTexture::setClearDepth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setClearFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearFlags");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(cocos2d::ClearFlag)>(&cocos2d::RenderTexture::setClearFlags));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearStencil");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(int)>(&cocos2d::RenderTexture::setClearStencil));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setKeepMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setKeepMatrix");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(bool)>(&cocos2d::RenderTexture::setKeepMatrix));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setSprite");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(cocos2d::Sprite*)>(&cocos2d::RenderTexture::setSprite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RenderTexture_setVirtualViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setVirtualViewport");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::RenderTexture::*)(const cocos2d::Vec2&, const cocos2d::Rect&, const cocos2d::Rect&)>(&cocos2d::RenderTexture::setVirtualViewport)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_RenderTexture_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::RenderTexture*(*)(int, int, cocos2d::backend::PixelFormat, cocos2d::backend::PixelFormat, bool)>(&cocos2d::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cocos2d::RenderTexture*(*)(int, int, cocos2d::backend::PixelFormat, bool)>(&cocos2d::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](int arg0,int arg1,cocos2d::backend::PixelFormat arg2,cocos2d::backend::PixelFormat arg3){{return cocos2d::RenderTexture::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<cocos2d::RenderTexture*(*)(int, int, bool)>(&cocos2d::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](int arg0,int arg1,cocos2d::backend::PixelFormat arg2){{return cocos2d::RenderTexture::create(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](int arg0,int arg1){{return cocos2d::RenderTexture::create(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3,4,5");
}
int luaReg_Core_ccRenderTexture(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RenderTexture, "RenderTexture", "cc.RenderTexture",
		cocos2d::RenderTexture, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("begin", lua_cocos2d_RenderTexture_begin);
	LUA_METHOD("beginWithClear", lua_cocos2d_RenderTexture_beginWithClear);
	LUA_METHOD("clear", lua_cocos2d_RenderTexture_clear);
	LUA_METHOD("clearDepth", lua_cocos2d_RenderTexture_clearDepth);
	LUA_METHOD("clearStencil", lua_cocos2d_RenderTexture_clearStencil);
	LUA_METHOD("endToLua", lua_cocos2d_RenderTexture_endToLua);
	LUA_METHOD("getClearColor", lua_cocos2d_RenderTexture_getClearColor);
	LUA_METHOD("getClearDepth", lua_cocos2d_RenderTexture_getClearDepth);
	LUA_METHOD("getClearFlags", lua_cocos2d_RenderTexture_getClearFlags);
	LUA_METHOD("getClearStencil", lua_cocos2d_RenderTexture_getClearStencil);
	LUA_METHOD("getRenderTarget", lua_cocos2d_RenderTexture_getRenderTarget);
	LUA_METHOD("getSprite", lua_cocos2d_RenderTexture_getSprite);
	LUA_METHOD("initWithWidthAndHeight", lua_cocos2d_RenderTexture_initWithWidthAndHeight);
	LUA_METHOD("isAutoDraw", lua_cocos2d_RenderTexture_isAutoDraw);
	LUA_METHOD("isSharedRenderTarget", lua_cocos2d_RenderTexture_isSharedRenderTarget);
	LUA_METHOD("newImage", lua_cocos2d_RenderTexture_newImage_1);
	LUA_METHOD("saveToFile", lua_cocos2d_RenderTexture_saveToFile);
	LUA_METHOD("saveToFileAsNonPMA", lua_cocos2d_RenderTexture_saveToFileAsNonPMA);
	LUA_METHOD("setAutoDraw", lua_cocos2d_RenderTexture_setAutoDraw);
	LUA_METHOD("setClearColor", lua_cocos2d_RenderTexture_setClearColor);
	LUA_METHOD("setClearDepth", lua_cocos2d_RenderTexture_setClearDepth);
	LUA_METHOD("setClearFlags", lua_cocos2d_RenderTexture_setClearFlags);
	LUA_METHOD("setClearStencil", lua_cocos2d_RenderTexture_setClearStencil);
	LUA_METHOD("setKeepMatrix", lua_cocos2d_RenderTexture_setKeepMatrix);
	LUA_METHOD("setSprite", lua_cocos2d_RenderTexture_setSprite);
	LUA_METHOD("setVirtualViewport", lua_cocos2d_RenderTexture_setVirtualViewport);
	LUA_METHOD("create", lua_cocos2d_RenderTexture_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionScene_finish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:finish");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TransitionScene::*)()>(&cocos2d::TransitionScene::finish));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionScene_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::TransitionScene::*)()const>(&cocos2d::TransitionScene::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionScene_getInScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:getInScene");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scene*(cocos2d::TransitionScene::*)()const>(&cocos2d::TransitionScene::getInScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionScene_hideOutShowIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:hideOutShowIn");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TransitionScene::*)()>(&cocos2d::TransitionScene::hideOutShowIn));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionScene_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TransitionScene::*)(float, cocos2d::Scene*)>(&cocos2d::TransitionScene::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TransitionScene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionScene*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionScene::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionScene, "TransitionScene", "cc.TransitionScene",
		cocos2d::TransitionScene, "cc.Scene",
		nullptr, nullptr);
	LUA_METHOD("finish", lua_cocos2d_TransitionScene_finish);
	LUA_METHOD("getDuration", lua_cocos2d_TransitionScene_getDuration);
	LUA_METHOD("getInScene", lua_cocos2d_TransitionScene_getInScene);
	LUA_METHOD("hideOutShowIn", lua_cocos2d_TransitionScene_hideOutShowIn);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionScene_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionScene_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSceneOriented_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSceneOriented", "cc.TransitionSceneOriented:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TransitionSceneOriented::*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionSceneOriented::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TransitionSceneOriented_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSceneOriented", "cc.TransitionSceneOriented:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionSceneOriented*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionSceneOriented::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionSceneOriented(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSceneOriented, "TransitionSceneOriented", "cc.TransitionSceneOriented",
		cocos2d::TransitionSceneOriented, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionSceneOriented_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionSceneOriented_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionRotoZoom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionRotoZoom", "cc.TransitionRotoZoom:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionRotoZoom*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionRotoZoom::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionRotoZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionRotoZoom, "TransitionRotoZoom", "cc.TransitionRotoZoom",
		cocos2d::TransitionRotoZoom, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionRotoZoom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionJumpZoom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionJumpZoom", "cc.TransitionJumpZoom:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionJumpZoom*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionJumpZoom::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionJumpZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionJumpZoom, "TransitionJumpZoom", "cc.TransitionJumpZoom",
		cocos2d::TransitionJumpZoom, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionJumpZoom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInL_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:action");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionMoveInL::*)()>(&cocos2d::TransitionMoveInL::action));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionMoveInL_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionMoveInL::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionMoveInL::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionMoveInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionMoveInL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInL::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInL, "TransitionMoveInL", "cc.TransitionMoveInL",
		cocos2d::TransitionMoveInL, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionMoveInL_action);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionMoveInL_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInR", "cc.TransitionMoveInR:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionMoveInR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInR::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInR, "TransitionMoveInR", "cc.TransitionMoveInR",
		cocos2d::TransitionMoveInR, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInT", "cc.TransitionMoveInT:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionMoveInT*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInT::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInT, "TransitionMoveInT", "cc.TransitionMoveInT",
		cocos2d::TransitionMoveInT, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInB", "cc.TransitionMoveInB:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionMoveInB*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInB::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInB, "TransitionMoveInB", "cc.TransitionMoveInB",
		cocos2d::TransitionMoveInB, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInL_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:action");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSlideInL::*)()>(&cocos2d::TransitionSlideInL::action));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionSlideInL_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSlideInL::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionSlideInL::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionSlideInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSlideInL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInL::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInL, "TransitionSlideInL", "cc.TransitionSlideInL",
		cocos2d::TransitionSlideInL, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionSlideInL_action);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionSlideInL_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInR", "cc.TransitionSlideInR:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSlideInR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInR::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInR, "TransitionSlideInR", "cc.TransitionSlideInR",
		cocos2d::TransitionSlideInR, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInB", "cc.TransitionSlideInB:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSlideInB*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInB::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInB, "TransitionSlideInB", "cc.TransitionSlideInB",
		cocos2d::TransitionSlideInB, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSlideInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInT", "cc.TransitionSlideInT:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSlideInT*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSlideInT::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSlideInT, "TransitionSlideInT", "cc.TransitionSlideInT",
		cocos2d::TransitionSlideInT, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSlideInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionShrinkGrow_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionShrinkGrow::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionShrinkGrow::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionShrinkGrow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionShrinkGrow*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionShrinkGrow::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionShrinkGrow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionShrinkGrow, "TransitionShrinkGrow", "cc.TransitionShrinkGrow",
		cocos2d::TransitionShrinkGrow, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionShrinkGrow_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionShrinkGrow_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipX", "cc.TransitionFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipX, "TransitionFlipX", "cc.TransitionFlipX",
		cocos2d::TransitionFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipY", "cc.TransitionFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipY, "TransitionFlipY", "cc.TransitionFlipY",
		cocos2d::TransitionFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipAngular", "cc.TransitionFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFlipAngular, "TransitionFlipAngular", "cc.TransitionFlipAngular",
		cocos2d::TransitionFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipX", "cc.TransitionZoomFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipX*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipX, "TransitionZoomFlipX", "cc.TransitionZoomFlipX",
		cocos2d::TransitionZoomFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipY", "cc.TransitionZoomFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipY*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipY, "TransitionZoomFlipY", "cc.TransitionZoomFlipY",
		cocos2d::TransitionZoomFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionZoomFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionZoomFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionZoomFlipAngular*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionZoomFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionZoomFlipAngular, "TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular",
		cocos2d::TransitionZoomFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionZoomFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFade_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TransitionFade::*)(float, cocos2d::Scene*, const cocos2d::Color3B&)>(&cocos2d::TransitionFade::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TransitionFade::*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFade::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_TransitionFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionFade*(*)(float, cocos2d::Scene*, const cocos2d::Color3B&)>(&cocos2d::TransitionFade::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFade*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFade::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFade, "TransitionFade", "cc.TransitionFade",
		cocos2d::TransitionFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionFade_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionCrossFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionCrossFade", "cc.TransitionCrossFade:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionCrossFade*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionCrossFade::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionCrossFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionCrossFade, "TransitionCrossFade", "cc.TransitionCrossFade",
		cocos2d::TransitionCrossFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionCrossFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionTurnOffTiles_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionTurnOffTiles::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionTurnOffTiles::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionTurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionTurnOffTiles*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionTurnOffTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionTurnOffTiles, "TransitionTurnOffTiles", "cc.TransitionTurnOffTiles",
		cocos2d::TransitionTurnOffTiles, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionTurnOffTiles_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionTurnOffTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSplitCols_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:action");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSplitCols::*)()>(&cocos2d::TransitionSplitCols::action));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TransitionSplitCols_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionSplitCols::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionSplitCols::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionSplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSplitCols*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitCols::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitCols, "TransitionSplitCols", "cc.TransitionSplitCols",
		cocos2d::TransitionSplitCols, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionSplitCols_action);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionSplitCols_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionSplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitRows", "cc.TransitionSplitRows:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionSplitRows*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionSplitRows::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSplitRows, "TransitionSplitRows", "cc.TransitionSplitRows",
		cocos2d::TransitionSplitRows, "cc.TransitionSplitCols",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionSplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeTR_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:actionWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionFadeTR::*)(const cocos2d::Vec2&)>(&cocos2d::TransitionFadeTR::actionWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionFadeTR_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionFadeTR::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionFadeTR::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionFadeTR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeTR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeTR::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeTR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeTR, "TransitionFadeTR", "cc.TransitionFadeTR",
		cocos2d::TransitionFadeTR, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cocos2d_TransitionFadeTR_actionWithSize);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionFadeTR_easeActionWithAction);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeTR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeBL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeBL", "cc.TransitionFadeBL:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeBL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeBL::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeBL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeBL, "TransitionFadeBL", "cc.TransitionFadeBL",
		cocos2d::TransitionFadeBL, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeBL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeUp_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeUp", "cc.TransitionFadeUp:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeUp*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeUp::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeUp(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeUp, "TransitionFadeUp", "cc.TransitionFadeUp",
		cocos2d::TransitionFadeUp, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeUp_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionFadeDown_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeDown", "cc.TransitionFadeDown:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionFadeDown*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionFadeDown::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeDown(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionFadeDown, "TransitionFadeDown", "cc.TransitionFadeDown",
		cocos2d::TransitionFadeDown, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionFadeDown_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionPageTurn_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:actionWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionPageTurn::*)(const cocos2d::Vec2&)>(&cocos2d::TransitionPageTurn::actionWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TransitionPageTurn_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TransitionPageTurn::*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TransitionPageTurn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TransitionPageTurn*(*)(float, cocos2d::Scene*, bool)>(&cocos2d::TransitionPageTurn::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionPageTurn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionPageTurn, "TransitionPageTurn", "cc.TransitionPageTurn",
		cocos2d::TransitionPageTurn, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cocos2d_TransitionPageTurn_actionWithSize);
	LUA_METHOD("initWithDuration", lua_cocos2d_TransitionPageTurn_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TransitionPageTurn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgress_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgress", "cc.TransitionProgress:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgress*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgress::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgress(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgress, "TransitionProgress", "cc.TransitionProgress",
		cocos2d::TransitionProgress, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgress_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressRadialCCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCCW::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCCW, "TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW",
		cocos2d::TransitionProgressRadialCCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressRadialCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCW", "cc.TransitionProgressRadialCW:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressRadialCW*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressRadialCW::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressRadialCW, "TransitionProgressRadialCW", "cc.TransitionProgressRadialCW",
		cocos2d::TransitionProgressRadialCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressRadialCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressHorizontal_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressHorizontal", "cc.TransitionProgressHorizontal:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressHorizontal*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressHorizontal::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressHorizontal(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressHorizontal, "TransitionProgressHorizontal", "cc.TransitionProgressHorizontal",
		cocos2d::TransitionProgressHorizontal, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressHorizontal_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressVertical_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressVertical", "cc.TransitionProgressVertical:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressVertical*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressVertical::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressVertical(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressVertical, "TransitionProgressVertical", "cc.TransitionProgressVertical",
		cocos2d::TransitionProgressVertical, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressVertical_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressInOut", "cc.TransitionProgressInOut:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressInOut*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressInOut::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressInOut, "TransitionProgressInOut", "cc.TransitionProgressInOut",
		cocos2d::TransitionProgressInOut, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionProgressOutIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressOutIn", "cc.TransitionProgressOutIn:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TransitionProgressOutIn*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionProgressOutIn::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressOutIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionProgressOutIn, "TransitionProgressOutIn", "cc.TransitionProgressOutIn",
		cocos2d::TransitionProgressOutIn, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionProgressOutIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Camera_apply(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:apply");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Camera::*)()>(&cocos2d::Camera::apply));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_applyViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:applyViewport");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Camera::*)()>(&cocos2d::Camera::applyViewport));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_applyZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:applyZoom");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Camera::*)()>(&cocos2d::Camera::applyZoom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_clearBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:clearBackground");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Camera::*)()>(&cocos2d::Camera::clearBackground));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getBackgroundBrush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getBackgroundBrush");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CameraBackgroundBrush*(cocos2d::Camera::*)()const>(&cocos2d::Camera::getBackgroundBrush));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getCameraFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getCameraFlag");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CameraFlag(cocos2d::Camera::*)()const>(&cocos2d::Camera::getCameraFlag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getDepth");
	LUA_TRY_INVOKE_R(0, static_cast<int8_t(cocos2d::Camera::*)()const>(&cocos2d::Camera::getDepth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getDepthInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getDepthInView");
	LUA_TRY_INVOKE_R(1, static_cast<float(cocos2d::Camera::*)(const cocos2d::Mat4&)const>(&cocos2d::Camera::getDepthInView));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_getFOV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getFOV");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Camera::*)()const>(&cocos2d::Camera::getFOV));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getFarPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getFarPlane");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Camera::*)()const>(&cocos2d::Camera::getFarPlane));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getNearPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getNearPlane");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Camera::*)()const>(&cocos2d::Camera::getNearPlane));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getProjectionMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getProjectionMatrix");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Mat4&(cocos2d::Camera::*)()const>(&cocos2d::Camera::getProjectionMatrix));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getRenderOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getRenderOrder");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Camera::*)()const>(&cocos2d::Camera::getRenderOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getViewMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getViewMatrix");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Mat4&(cocos2d::Camera::*)()const>(&cocos2d::Camera::getViewMatrix));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getViewProjectionMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getViewProjectionMatrix");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Mat4&(cocos2d::Camera::*)()const>(&cocos2d::Camera::getViewProjectionMatrix));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getZoom");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Camera::*)()const>(&cocos2d::Camera::getZoom));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_initDefault(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initDefault");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Camera::*)()>(&cocos2d::Camera::initDefault));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_initOrthographic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initOrthographic");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Camera::*)(float, float, float, float)>(&cocos2d::Camera::initOrthographic)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Camera_initPerspective(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initPerspective");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Camera::*)(float, float, float, float)>(&cocos2d::Camera::initPerspective)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Camera_isBrushValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isBrushValid");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Camera::*)()>(&cocos2d::Camera::isBrushValid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_isViewProjectionUpdated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isViewProjectionUpdated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Camera::*)()const>(&cocos2d::Camera::isViewProjectionUpdated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_isVisibleInFrustum(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isVisibleInFrustum");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Camera::*)(const cocos2d::AABB*)const>(&cocos2d::Camera::isVisibleInFrustum));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_lookAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:lookAt");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Camera::*)(const cocos2d::Vec3&, const cocos2d::Vec3&)>(&cocos2d::Camera::lookAt)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Camera* obj,const cocos2d::Vec3& arg0){{return obj->lookAt(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Camera_project(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:project");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Camera::*)(const cocos2d::Vec3&)const>(&cocos2d::Camera::project));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_projectGL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:projectGL");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Camera::*)(const cocos2d::Vec3&)const>(&cocos2d::Camera::projectGL));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setAdditionalProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setAdditionalProjection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(const cocos2d::Mat4&)>(&cocos2d::Camera::setAdditionalProjection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setBackgroundBrush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setBackgroundBrush");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(cocos2d::CameraBackgroundBrush*)>(&cocos2d::Camera::setBackgroundBrush));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setCameraFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setCameraFlag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(cocos2d::CameraFlag)>(&cocos2d::Camera::setCameraFlag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setDepth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(int8_t)>(&cocos2d::Camera::setDepth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setFOV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setFOV");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(float)>(&cocos2d::Camera::setFOV));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setFarPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setFarPlane");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(float)>(&cocos2d::Camera::setFarPlane));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setNearPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setNearPlane");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(float)>(&cocos2d::Camera::setNearPlane));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setScene");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(cocos2d::Scene*)>(&cocos2d::Camera::setScene));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_setZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setZoom");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Camera::*)(float)>(&cocos2d::Camera::setZoom));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Camera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Camera*(*)()>(&cocos2d::Camera::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_createOrthographic(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:createOrthographic");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Camera*(*)(float, float, float, float)>(&cocos2d::Camera::createOrthographic)));
	LUA_SINVOKE_FOOTER("4");
}
int lua_cocos2d_Camera_createPerspective(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:createPerspective");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Camera*(*)(float, float, float, float)>(&cocos2d::Camera::createPerspective)));
	LUA_SINVOKE_FOOTER("4");
}
int lua_cocos2d_Camera_getDefaultCamera(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getDefaultCamera");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Camera*(*)()>(&cocos2d::Camera::getDefaultCamera));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getDefaultViewport(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getDefaultViewport");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Viewport&(*)()>(&cocos2d::Camera::getDefaultViewport));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_getVisitingCamera(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getVisitingCamera");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Camera*(*)()>(&cocos2d::Camera::getVisitingCamera));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Camera_setDefaultViewport(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:setDefaultViewport");
	LUA_TRY_INVOKE(1, static_cast<void(*)(const cocos2d::Viewport&)>(&cocos2d::Camera::setDefaultViewport));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Camera, "Camera", "cc.Camera",
		cocos2d::Camera, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("apply", lua_cocos2d_Camera_apply);
	LUA_METHOD("applyViewport", lua_cocos2d_Camera_applyViewport);
	LUA_METHOD("applyZoom", lua_cocos2d_Camera_applyZoom);
	LUA_METHOD("clearBackground", lua_cocos2d_Camera_clearBackground);
	LUA_METHOD("getBackgroundBrush", lua_cocos2d_Camera_getBackgroundBrush);
	LUA_METHOD("getCameraFlag", lua_cocos2d_Camera_getCameraFlag);
	LUA_METHOD("getDepth", lua_cocos2d_Camera_getDepth);
	LUA_METHOD("getDepthInView", lua_cocos2d_Camera_getDepthInView);
	LUA_METHOD("getFOV", lua_cocos2d_Camera_getFOV);
	LUA_METHOD("getFarPlane", lua_cocos2d_Camera_getFarPlane);
	LUA_METHOD("getNearPlane", lua_cocos2d_Camera_getNearPlane);
	LUA_METHOD("getProjectionMatrix", lua_cocos2d_Camera_getProjectionMatrix);
	LUA_METHOD("getRenderOrder", lua_cocos2d_Camera_getRenderOrder);
	LUA_METHOD("getViewMatrix", lua_cocos2d_Camera_getViewMatrix);
	LUA_METHOD("getViewProjectionMatrix", lua_cocos2d_Camera_getViewProjectionMatrix);
	LUA_METHOD("getZoom", lua_cocos2d_Camera_getZoom);
	LUA_METHOD("initDefault", lua_cocos2d_Camera_initDefault);
	LUA_METHOD("initOrthographic", lua_cocos2d_Camera_initOrthographic);
	LUA_METHOD("initPerspective", lua_cocos2d_Camera_initPerspective);
	LUA_METHOD("isBrushValid", lua_cocos2d_Camera_isBrushValid);
	LUA_METHOD("isViewProjectionUpdated", lua_cocos2d_Camera_isViewProjectionUpdated);
	LUA_METHOD("isVisibleInFrustum", lua_cocos2d_Camera_isVisibleInFrustum);
	LUA_METHOD("lookAt", lua_cocos2d_Camera_lookAt);
	LUA_METHOD("project", lua_cocos2d_Camera_project);
	LUA_METHOD("projectGL", lua_cocos2d_Camera_projectGL);
	LUA_METHOD("setAdditionalProjection", lua_cocos2d_Camera_setAdditionalProjection);
	LUA_METHOD("setBackgroundBrush", lua_cocos2d_Camera_setBackgroundBrush);
	LUA_METHOD("setCameraFlag", lua_cocos2d_Camera_setCameraFlag);
	LUA_METHOD("setDepth", lua_cocos2d_Camera_setDepth);
	LUA_METHOD("setFOV", lua_cocos2d_Camera_setFOV);
	LUA_METHOD("setFarPlane", lua_cocos2d_Camera_setFarPlane);
	LUA_METHOD("setNearPlane", lua_cocos2d_Camera_setNearPlane);
	LUA_METHOD("setScene", lua_cocos2d_Camera_setScene);
	LUA_METHOD("setZoom", lua_cocos2d_Camera_setZoom);
	LUA_METHOD("create", lua_cocos2d_Camera_create);
	LUA_METHOD("createOrthographic", lua_cocos2d_Camera_createOrthographic);
	LUA_METHOD("createPerspective", lua_cocos2d_Camera_createPerspective);
	LUA_METHOD("getDefaultCamera", lua_cocos2d_Camera_getDefaultCamera);
	LUA_METHOD("getDefaultViewport", lua_cocos2d_Camera_getDefaultViewport);
	LUA_METHOD("getVisitingCamera", lua_cocos2d_Camera_getVisitingCamera);
	LUA_METHOD("setDefaultViewport", lua_cocos2d_Camera_setDefaultViewport);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CameraBackgroundBrush_drawBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:drawBackground");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundBrush::*)(cocos2d::Camera*)>(&cocos2d::CameraBackgroundBrush::drawBackground));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundBrush_getBrushType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:getBrushType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CameraBackgroundBrush::BrushType(cocos2d::CameraBackgroundBrush::*)()const>(&cocos2d::CameraBackgroundBrush::getBrushType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundBrush_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::CameraBackgroundBrush::*)()>(&cocos2d::CameraBackgroundBrush::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundBrush_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:isValid");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::CameraBackgroundBrush::*)()>(&cocos2d::CameraBackgroundBrush::isValid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundBrush_createColorBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createColorBrush");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::CameraBackgroundColorBrush*(*)(const cocos2d::Color4F&, float)>(&cocos2d::CameraBackgroundBrush::createColorBrush)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_CameraBackgroundBrush_createDepthBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createDepthBrush");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::CameraBackgroundDepthBrush*(*)(float)>(&cocos2d::CameraBackgroundBrush::createDepthBrush));
	LUA_TRY_INVOKE_R(0, [](){{return cocos2d::CameraBackgroundBrush::createDepthBrush();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int lua_cocos2d_CameraBackgroundBrush_createNoneBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createNoneBrush");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CameraBackgroundBrush*(*)()>(&cocos2d::CameraBackgroundBrush::createNoneBrush));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundBrush_createSkyboxBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createSkyboxBrush");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::CameraBackgroundSkyBoxBrush*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::CameraBackgroundBrush::createSkyboxBrush)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccCameraBackgroundBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CameraBackgroundBrush, "CameraBackgroundBrush", "cc.CameraBackgroundBrush",
		cocos2d::CameraBackgroundBrush, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("drawBackground", lua_cocos2d_CameraBackgroundBrush_drawBackground);
	LUA_METHOD("getBrushType", lua_cocos2d_CameraBackgroundBrush_getBrushType);
	LUA_METHOD("init", lua_cocos2d_CameraBackgroundBrush_init);
	LUA_METHOD("isValid", lua_cocos2d_CameraBackgroundBrush_isValid);
	LUA_METHOD("createColorBrush", lua_cocos2d_CameraBackgroundBrush_createColorBrush);
	LUA_METHOD("createDepthBrush", lua_cocos2d_CameraBackgroundBrush_createDepthBrush);
	LUA_METHOD("createNoneBrush", lua_cocos2d_CameraBackgroundBrush_createNoneBrush);
	LUA_METHOD("createSkyboxBrush", lua_cocos2d_CameraBackgroundBrush_createSkyboxBrush);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CameraBackgroundDepthBrush_setDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush:setDepth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundDepthBrush::*)(float)>(&cocos2d::CameraBackgroundDepthBrush::setDepth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundDepthBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::CameraBackgroundDepthBrush*(*)(float)>(&cocos2d::CameraBackgroundDepthBrush::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccCameraBackgroundDepthBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CameraBackgroundDepthBrush, "CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush",
		cocos2d::CameraBackgroundDepthBrush, "cc.CameraBackgroundBrush",
		nullptr, nullptr);
	LUA_METHOD("setDepth", lua_cocos2d_CameraBackgroundDepthBrush_setDepth);
	LUA_METHOD("create", lua_cocos2d_CameraBackgroundDepthBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CameraBackgroundColorBrush_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundColorBrush::*)(const cocos2d::Color4F&)>(&cocos2d::CameraBackgroundColorBrush::setColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundColorBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::CameraBackgroundColorBrush*(*)(const cocos2d::Color4F&, float)>(&cocos2d::CameraBackgroundColorBrush::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccCameraBackgroundColorBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CameraBackgroundColorBrush, "CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush",
		cocos2d::CameraBackgroundColorBrush, "cc.CameraBackgroundDepthBrush",
		nullptr, nullptr);
	LUA_METHOD("setColor", lua_cocos2d_CameraBackgroundColorBrush_setColor);
	LUA_METHOD("create", lua_cocos2d_CameraBackgroundColorBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureCube*(cocos2d::CameraBackgroundSkyBoxBrush::*)()const>(&cocos2d::CameraBackgroundSkyBoxBrush::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_isActived(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:isActived");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::CameraBackgroundSkyBoxBrush::*)()const>(&cocos2d::CameraBackgroundSkyBoxBrush::isActived));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_setActived(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setActived");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundSkyBoxBrush::*)(bool)>(&cocos2d::CameraBackgroundSkyBoxBrush::setActived));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundSkyBoxBrush::*)(cocos2d::TextureCube*)>(&cocos2d::CameraBackgroundSkyBoxBrush::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_setTextureValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setTextureValid");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::CameraBackgroundSkyBoxBrush::*)(bool)>(&cocos2d::CameraBackgroundSkyBoxBrush::setTextureValid));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_CameraBackgroundSkyBoxBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::CameraBackgroundSkyBoxBrush*(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cocos2d::CameraBackgroundSkyBoxBrush::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::CameraBackgroundSkyBoxBrush*(*)()>(&cocos2d::CameraBackgroundSkyBoxBrush::create));
	LUA_SINVOKE_FOOTER("0,6");
}
int luaReg_Core_ccCameraBackgroundSkyBoxBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CameraBackgroundSkyBoxBrush, "CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush",
		cocos2d::CameraBackgroundSkyBoxBrush, "cc.CameraBackgroundBrush",
		nullptr, nullptr);
	LUA_METHOD("getTexture", lua_cocos2d_CameraBackgroundSkyBoxBrush_getTexture);
	LUA_METHOD("isActived", lua_cocos2d_CameraBackgroundSkyBoxBrush_isActived);
	LUA_METHOD("setActived", lua_cocos2d_CameraBackgroundSkyBoxBrush_setActived);
	LUA_METHOD("setTexture", lua_cocos2d_CameraBackgroundSkyBoxBrush_setTexture);
	LUA_METHOD("setTextureValid", lua_cocos2d_CameraBackgroundSkyBoxBrush_setTextureValid);
	LUA_METHOD("create", lua_cocos2d_CameraBackgroundSkyBoxBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GridBase_afterBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:afterBlit");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::afterBlit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_afterDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:afterDraw");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(cocos2d::Node*)>(&cocos2d::GridBase::afterDraw));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_beforeBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:beforeBlit");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::beforeBlit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_beforeDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:beforeDraw");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::beforeDraw));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_blit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:blit");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::blit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_calculateVertexPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:calculateVertexPoints");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::calculateVertexPoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getGridRect");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::getGridRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_getGridSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getGridSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::getGridSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_getReuseGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getReuseGrid");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::getReuseGrid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_getStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getStep");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::getStep));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:initWithSize");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::GridBase::*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool, const cocos2d::Rect&)>(&cocos2d::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::GridBase::*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool)>(&cocos2d::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::GridBase::*)(const cocos2d::Vec2&, const cocos2d::Rect&)>(&cocos2d::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::GridBase::*)(const cocos2d::Vec2&)>(&cocos2d::GridBase::initWithSize));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocos2d_GridBase_isActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:isActive");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::isActive));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_isTextureFlipped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:isTextureFlipped");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GridBase::*)()const>(&cocos2d::GridBase::isTextureFlipped));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_reuse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:reuse");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::reuse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_set2DProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:set2DProjection");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GridBase::*)()>(&cocos2d::GridBase::set2DProjection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridBase_setActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setActive");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(bool)>(&cocos2d::GridBase::setActive));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_setGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setGridRect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(const cocos2d::Rect&)>(&cocos2d::GridBase::setGridRect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_setGridSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setGridSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(const cocos2d::Vec2&)>(&cocos2d::GridBase::setGridSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_setReuseGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setReuseGrid");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(int)>(&cocos2d::GridBase::setReuseGrid));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_setStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setStep");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(const cocos2d::Vec2&)>(&cocos2d::GridBase::setStep));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GridBase_setTextureFlipped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setTextureFlipped");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GridBase::*)(bool)>(&cocos2d::GridBase::setTextureFlipped));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccGridBase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GridBase, "GridBase", "cc.GridBase",
		cocos2d::GridBase, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("afterBlit", lua_cocos2d_GridBase_afterBlit);
	LUA_METHOD("afterDraw", lua_cocos2d_GridBase_afterDraw);
	LUA_METHOD("beforeBlit", lua_cocos2d_GridBase_beforeBlit);
	LUA_METHOD("beforeDraw", lua_cocos2d_GridBase_beforeDraw);
	LUA_METHOD("blit", lua_cocos2d_GridBase_blit);
	LUA_METHOD("calculateVertexPoints", lua_cocos2d_GridBase_calculateVertexPoints);
	LUA_METHOD("getGridRect", lua_cocos2d_GridBase_getGridRect);
	LUA_METHOD("getGridSize", lua_cocos2d_GridBase_getGridSize);
	LUA_METHOD("getReuseGrid", lua_cocos2d_GridBase_getReuseGrid);
	LUA_METHOD("getStep", lua_cocos2d_GridBase_getStep);
	LUA_METHOD("initWithSize", lua_cocos2d_GridBase_initWithSize);
	LUA_METHOD("isActive", lua_cocos2d_GridBase_isActive);
	LUA_METHOD("isTextureFlipped", lua_cocos2d_GridBase_isTextureFlipped);
	LUA_METHOD("reuse", lua_cocos2d_GridBase_reuse);
	LUA_METHOD("set2DProjection", lua_cocos2d_GridBase_set2DProjection);
	LUA_METHOD("setActive", lua_cocos2d_GridBase_setActive);
	LUA_METHOD("setGridRect", lua_cocos2d_GridBase_setGridRect);
	LUA_METHOD("setGridSize", lua_cocos2d_GridBase_setGridSize);
	LUA_METHOD("setReuseGrid", lua_cocos2d_GridBase_setReuseGrid);
	LUA_METHOD("setStep", lua_cocos2d_GridBase_setStep);
	LUA_METHOD("setTextureFlipped", lua_cocos2d_GridBase_setTextureFlipped);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Grid3D_getNeedDepthTestForBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3D", "cc.Grid3D:getNeedDepthTestForBlit");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Grid3D::*)()const>(&cocos2d::Grid3D::getNeedDepthTestForBlit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Grid3D_setNeedDepthTestForBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3D", "cc.Grid3D:setNeedDepthTestForBlit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Grid3D::*)(bool)>(&cocos2d::Grid3D::setNeedDepthTestForBlit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Grid3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Grid3D", "cc.Grid3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Grid3D*(*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool, const cocos2d::Rect&)>(&cocos2d::Grid3D::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Grid3D*(*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool)>(&cocos2d::Grid3D::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Grid3D*(*)(const cocos2d::Vec2&, const cocos2d::Rect&)>(&cocos2d::Grid3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Grid3D*(*)(const cocos2d::Vec2&)>(&cocos2d::Grid3D::create));
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Core_ccGrid3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Grid3D, "Grid3D", "cc.Grid3D",
		cocos2d::Grid3D, "cc.GridBase",
		nullptr, nullptr);
	LUA_METHOD("getNeedDepthTestForBlit", lua_cocos2d_Grid3D_getNeedDepthTestForBlit);
	LUA_METHOD("setNeedDepthTestForBlit", lua_cocos2d_Grid3D_setNeedDepthTestForBlit);
	LUA_METHOD("create", lua_cocos2d_Grid3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TiledGrid3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TiledGrid3D", "cc.TiledGrid3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TiledGrid3D*(*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool, const cocos2d::Rect&)>(&cocos2d::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TiledGrid3D*(*)(const cocos2d::Vec2&, cocos2d::Texture2D*, bool)>(&cocos2d::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TiledGrid3D*(*)(const cocos2d::Vec2&, const cocos2d::Rect&)>(&cocos2d::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TiledGrid3D*(*)(const cocos2d::Vec2&)>(&cocos2d::TiledGrid3D::create));
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Core_ccTiledGrid3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TiledGrid3D, "TiledGrid3D", "cc.TiledGrid3D",
		cocos2d::TiledGrid3D, "cc.GridBase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TiledGrid3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
