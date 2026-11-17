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

int lua_cc_RenderTexture_begin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:begin");
	LUA_TRY_INVOKE(0, &cc::RenderTexture::begin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_beginWithClear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:beginWithClear");
	LUA_TRY_INVOKE(6, (static_cast<void(cc::RenderTexture::*)(float, float, float, float, float, int)>(&cc::RenderTexture::beginWithClear)));
	LUA_TRY_INVOKE(5, (static_cast<void(cc::RenderTexture::*)(float, float, float, float, float)>(&cc::RenderTexture::beginWithClear)));
	LUA_TRY_INVOKE(4, (static_cast<void(cc::RenderTexture::*)(float, float, float, float)>(&cc::RenderTexture::beginWithClear)));
	LUA_INVOKE_FOOTER("4,5,6");
}
int lua_cc_RenderTexture_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clear");
	LUA_TRY_INVOKE(4, &cc::RenderTexture::clear);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_RenderTexture_clearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clearDepth");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::clearDepth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_clearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clearStencil");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::clearStencil);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:endToLua");
	LUA_TRY_INVOKE(0, &cc::RenderTexture::end);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearColor");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getClearColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearDepth");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getClearDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getClearFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearFlags");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getClearFlags);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getClearStencil");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getClearStencil);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getSprite");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::getSprite);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_initWithWidthAndHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:initWithWidthAndHeight");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cc::RenderTexture::*)(int, int, cc::backend::PixelFormat, cc::backend::PixelFormat, bool)>(&cc::RenderTexture::initWithWidthAndHeight)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](cc::RenderTexture* obj,int arg0,int arg1,cc::backend::PixelFormat arg2,cc::backend::PixelFormat arg3){{return obj->initWithWidthAndHeight(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<bool(cc::RenderTexture::*)(int, int, cc::backend::PixelFormat, bool)>(&cc::RenderTexture::initWithWidthAndHeight)));
	LUA_TRY_INVOKE_R(3, ([](cc::RenderTexture* obj,int arg0,int arg1,cc::backend::PixelFormat arg2){{return obj->initWithWidthAndHeight(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4,5");
}
int lua_cc_RenderTexture_isAutoDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:isAutoDraw");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::isAutoDraw);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_isSharedRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:isSharedRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::RenderTexture::isSharedRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RenderTexture_newImage_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:newImage");
	if (argc == 2 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(2, (static_cast<void(cc::RenderTexture::*)(std::function<void(cc::IntrusivePtr<cc::Image>)>, bool)>(&cc::RenderTexture::newImage)));
	}
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, ([](cc::RenderTexture* obj,std::function<void(cc::IntrusivePtr<cc::Image>)> arg0){{return obj->newImage(std::move(arg0));}}));
	}
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_RenderTexture_saveToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:saveToFile");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cc::RenderTexture::*)(std::string_view, cc::Image::Format, bool, cc::RenderTexture::SaveFileCallbackType)>(&cc::RenderTexture::saveToFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cc::RenderTexture* obj,std::string_view arg0,cc::Image::Format arg1,bool arg2){{return obj->saveToFile(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cc::RenderTexture::*)(std::string_view, bool, cc::RenderTexture::SaveFileCallbackType)>(&cc::RenderTexture::saveToFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cc::RenderTexture* obj,std::string_view arg0,cc::Image::Format arg1){{return obj->saveToFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cc::RenderTexture* obj,std::string_view arg0,bool arg1){{return obj->saveToFile(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cc::RenderTexture* obj,std::string_view arg0){{return obj->saveToFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cc_RenderTexture_saveToFileAsNonPMA(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:saveToFileAsNonPMA");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cc::RenderTexture::*)(std::string_view, cc::Image::Format, bool, cc::RenderTexture::SaveFileCallbackType)>(&cc::RenderTexture::saveToFileAsNonPMA)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::RenderTexture::*)(std::string_view, bool, cc::RenderTexture::SaveFileCallbackType)>(&cc::RenderTexture::saveToFileAsNonPMA)));
	LUA_TRY_INVOKE_R(2, ([](cc::RenderTexture* obj,std::string_view arg0,bool arg1){{return obj->saveToFileAsNonPMA(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cc::RenderTexture* obj,std::string_view arg0){{return obj->saveToFileAsNonPMA(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cc_RenderTexture_setAutoDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setAutoDraw");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setAutoDraw);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearColor");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setClearColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearDepth");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setClearDepth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setClearFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearFlags");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setClearFlags);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setClearStencil");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setClearStencil);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setKeepMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setKeepMatrix");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setKeepMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setSprite");
	LUA_TRY_INVOKE(1, &cc::RenderTexture::setSprite);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RenderTexture_setVirtualViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setVirtualViewport");
	LUA_TRY_INVOKE(3, &cc::RenderTexture::setVirtualViewport);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_RenderTexture_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cc::RenderTexture>(*)(int, int, cc::backend::PixelFormat, cc::backend::PixelFormat, bool)>(&cc::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cc::IntrusivePtr<cc::RenderTexture>(*)(int, int, cc::backend::PixelFormat, bool)>(&cc::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](int arg0,int arg1,cc::backend::PixelFormat arg2,cc::backend::PixelFormat arg3){{return cc::RenderTexture::create(std::move(arg0),std::move(arg1),std::move(arg2),std::move(arg3));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<cc::IntrusivePtr<cc::RenderTexture>(*)(int, int, bool)>(&cc::RenderTexture::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](int arg0,int arg1,cc::backend::PixelFormat arg2){{return cc::RenderTexture::create(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](int arg0,int arg1){{return cc::RenderTexture::create(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3,4,5");
}
int luaReg_Core_ccRenderTexture(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RenderTexture, "RenderTexture", "cc.RenderTexture",
		cc::RenderTexture, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("begin", lua_cc_RenderTexture_begin);
	LUA_METHOD("beginWithClear", lua_cc_RenderTexture_beginWithClear);
	LUA_METHOD("clear", lua_cc_RenderTexture_clear);
	LUA_METHOD("clearDepth", lua_cc_RenderTexture_clearDepth);
	LUA_METHOD("clearStencil", lua_cc_RenderTexture_clearStencil);
	LUA_METHOD("endToLua", lua_cc_RenderTexture_endToLua);
	LUA_METHOD("getClearColor", lua_cc_RenderTexture_getClearColor);
	LUA_METHOD("getClearDepth", lua_cc_RenderTexture_getClearDepth);
	LUA_METHOD("getClearFlags", lua_cc_RenderTexture_getClearFlags);
	LUA_METHOD("getClearStencil", lua_cc_RenderTexture_getClearStencil);
	LUA_METHOD("getRenderTarget", lua_cc_RenderTexture_getRenderTarget);
	LUA_METHOD("getSprite", lua_cc_RenderTexture_getSprite);
	LUA_METHOD("initWithWidthAndHeight", lua_cc_RenderTexture_initWithWidthAndHeight);
	LUA_METHOD("isAutoDraw", lua_cc_RenderTexture_isAutoDraw);
	LUA_METHOD("isSharedRenderTarget", lua_cc_RenderTexture_isSharedRenderTarget);
	LUA_METHOD("newImage", lua_cc_RenderTexture_newImage_1);
	LUA_METHOD("saveToFile", lua_cc_RenderTexture_saveToFile);
	LUA_METHOD("saveToFileAsNonPMA", lua_cc_RenderTexture_saveToFileAsNonPMA);
	LUA_METHOD("setAutoDraw", lua_cc_RenderTexture_setAutoDraw);
	LUA_METHOD("setClearColor", lua_cc_RenderTexture_setClearColor);
	LUA_METHOD("setClearDepth", lua_cc_RenderTexture_setClearDepth);
	LUA_METHOD("setClearFlags", lua_cc_RenderTexture_setClearFlags);
	LUA_METHOD("setClearStencil", lua_cc_RenderTexture_setClearStencil);
	LUA_METHOD("setKeepMatrix", lua_cc_RenderTexture_setKeepMatrix);
	LUA_METHOD("setSprite", lua_cc_RenderTexture_setSprite);
	LUA_METHOD("setVirtualViewport", lua_cc_RenderTexture_setVirtualViewport);
	LUA_METHOD("create", lua_cc_RenderTexture_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionScene_finish(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:finish");
	LUA_TRY_INVOKE(0, &cc::TransitionScene::finish);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionScene_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:getDuration");
	LUA_TRY_INVOKE_R(0, &cc::TransitionScene::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionScene_getInScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:getInScene");
	LUA_TRY_INVOKE_R(0, &cc::TransitionScene::getInScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionScene_hideOutShowIn(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:hideOutShowIn");
	LUA_TRY_INVOKE(0, &cc::TransitionScene::hideOutShowIn);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionScene_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::TransitionScene::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TransitionScene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionScene::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionScene, "TransitionScene", "cc.TransitionScene",
		cc::TransitionScene, "cc.Scene",
		nullptr, nullptr);
	LUA_METHOD("finish", lua_cc_TransitionScene_finish);
	LUA_METHOD("getDuration", lua_cc_TransitionScene_getDuration);
	LUA_METHOD("getInScene", lua_cc_TransitionScene_getInScene);
	LUA_METHOD("hideOutShowIn", lua_cc_TransitionScene_hideOutShowIn);
	LUA_METHOD("initWithDuration", lua_cc_TransitionScene_initWithDuration);
	LUA_METHOD("create", lua_cc_TransitionScene_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSceneOriented_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSceneOriented", "cc.TransitionSceneOriented:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::TransitionSceneOriented::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_TransitionSceneOriented_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSceneOriented", "cc.TransitionSceneOriented:create");
	LUA_TRY_INVOKE_R(3, &cc::TransitionSceneOriented::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionSceneOriented(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSceneOriented, "TransitionSceneOriented", "cc.TransitionSceneOriented",
		cc::TransitionSceneOriented, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_TransitionSceneOriented_initWithDuration);
	LUA_METHOD("create", lua_cc_TransitionSceneOriented_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionRotoZoom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionRotoZoom", "cc.TransitionRotoZoom:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionRotoZoom::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionRotoZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionRotoZoom, "TransitionRotoZoom", "cc.TransitionRotoZoom",
		cc::TransitionRotoZoom, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionRotoZoom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionJumpZoom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionJumpZoom", "cc.TransitionJumpZoom:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionJumpZoom::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionJumpZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionJumpZoom, "TransitionJumpZoom", "cc.TransitionJumpZoom",
		cc::TransitionJumpZoom, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionJumpZoom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionMoveInL_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:action");
	LUA_TRY_INVOKE_R(0, &cc::TransitionMoveInL::action);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionMoveInL_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionMoveInL::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionMoveInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionMoveInL::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionMoveInL, "TransitionMoveInL", "cc.TransitionMoveInL",
		cc::TransitionMoveInL, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cc_TransitionMoveInL_action);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionMoveInL_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionMoveInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionMoveInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInR", "cc.TransitionMoveInR:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionMoveInR::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionMoveInR, "TransitionMoveInR", "cc.TransitionMoveInR",
		cc::TransitionMoveInR, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionMoveInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionMoveInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInT", "cc.TransitionMoveInT:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionMoveInT::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionMoveInT, "TransitionMoveInT", "cc.TransitionMoveInT",
		cc::TransitionMoveInT, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionMoveInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionMoveInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInB", "cc.TransitionMoveInB:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionMoveInB::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionMoveInB, "TransitionMoveInB", "cc.TransitionMoveInB",
		cc::TransitionMoveInB, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionMoveInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSlideInL_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:action");
	LUA_TRY_INVOKE_R(0, &cc::TransitionSlideInL::action);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionSlideInL_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionSlideInL::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionSlideInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInL", "cc.TransitionSlideInL:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSlideInL::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSlideInL, "TransitionSlideInL", "cc.TransitionSlideInL",
		cc::TransitionSlideInL, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cc_TransitionSlideInL_action);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionSlideInL_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionSlideInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSlideInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInR", "cc.TransitionSlideInR:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSlideInR::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSlideInR, "TransitionSlideInR", "cc.TransitionSlideInR",
		cc::TransitionSlideInR, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionSlideInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSlideInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInB", "cc.TransitionSlideInB:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSlideInB::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSlideInB, "TransitionSlideInB", "cc.TransitionSlideInB",
		cc::TransitionSlideInB, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionSlideInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSlideInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSlideInT", "cc.TransitionSlideInT:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSlideInT::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSlideInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSlideInT, "TransitionSlideInT", "cc.TransitionSlideInT",
		cc::TransitionSlideInT, "cc.TransitionSlideInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionSlideInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionShrinkGrow_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionShrinkGrow::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionShrinkGrow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionShrinkGrow", "cc.TransitionShrinkGrow:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionShrinkGrow::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionShrinkGrow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionShrinkGrow, "TransitionShrinkGrow", "cc.TransitionShrinkGrow",
		cc::TransitionShrinkGrow, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionShrinkGrow_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionShrinkGrow_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipX", "cc.TransitionFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionFlipX>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionFlipX>(*)(float, cc::Scene*)>(&cc::TransitionFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFlipX, "TransitionFlipX", "cc.TransitionFlipX",
		cc::TransitionFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipY", "cc.TransitionFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionFlipY>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionFlipY>(*)(float, cc::Scene*)>(&cc::TransitionFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFlipY, "TransitionFlipY", "cc.TransitionFlipY",
		cc::TransitionFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFlipAngular", "cc.TransitionFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionFlipAngular>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionFlipAngular>(*)(float, cc::Scene*)>(&cc::TransitionFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFlipAngular, "TransitionFlipAngular", "cc.TransitionFlipAngular",
		cc::TransitionFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionZoomFlipX_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipX", "cc.TransitionZoomFlipX:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipX>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionZoomFlipX::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipX>(*)(float, cc::Scene*)>(&cc::TransitionZoomFlipX::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipX(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionZoomFlipX, "TransitionZoomFlipX", "cc.TransitionZoomFlipX",
		cc::TransitionZoomFlipX, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionZoomFlipX_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionZoomFlipY_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipY", "cc.TransitionZoomFlipY:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipY>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionZoomFlipY::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipY>(*)(float, cc::Scene*)>(&cc::TransitionZoomFlipY::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipY(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionZoomFlipY, "TransitionZoomFlipY", "cc.TransitionZoomFlipY",
		cc::TransitionZoomFlipY, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionZoomFlipY_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionZoomFlipAngular_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipAngular>(*)(float, cc::Scene*, cc::TransitionScene::Orientation)>(&cc::TransitionZoomFlipAngular::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionZoomFlipAngular>(*)(float, cc::Scene*)>(&cc::TransitionZoomFlipAngular::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionZoomFlipAngular(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionZoomFlipAngular, "TransitionZoomFlipAngular", "cc.TransitionZoomFlipAngular",
		cc::TransitionZoomFlipAngular, "cc.TransitionSceneOriented",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionZoomFlipAngular_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFade_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::TransitionFade::*)(float, cc::Scene*, const cc::Color3B&)>(&cc::TransitionFade::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::TransitionFade::*)(float, cc::Scene*)>(&cc::TransitionFade::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_TransitionFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFade", "cc.TransitionFade:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TransitionFade>(*)(float, cc::Scene*, const cc::Color3B&)>(&cc::TransitionFade::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TransitionFade>(*)(float, cc::Scene*)>(&cc::TransitionFade::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTransitionFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFade, "TransitionFade", "cc.TransitionFade",
		cc::TransitionFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_TransitionFade_initWithDuration);
	LUA_METHOD("create", lua_cc_TransitionFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionCrossFade_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionCrossFade", "cc.TransitionCrossFade:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionCrossFade::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionCrossFade(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionCrossFade, "TransitionCrossFade", "cc.TransitionCrossFade",
		cc::TransitionCrossFade, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionCrossFade_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionTurnOffTiles_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionTurnOffTiles::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionTurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionTurnOffTiles", "cc.TransitionTurnOffTiles:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionTurnOffTiles::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionTurnOffTiles, "TransitionTurnOffTiles", "cc.TransitionTurnOffTiles",
		cc::TransitionTurnOffTiles, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionTurnOffTiles_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionTurnOffTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSplitCols_action(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:action");
	LUA_TRY_INVOKE_R(0, &cc::TransitionSplitCols::action);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TransitionSplitCols_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionSplitCols::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionSplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitCols", "cc.TransitionSplitCols:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSplitCols::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSplitCols, "TransitionSplitCols", "cc.TransitionSplitCols",
		cc::TransitionSplitCols, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cc_TransitionSplitCols_action);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionSplitCols_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionSplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionSplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSplitRows", "cc.TransitionSplitRows:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionSplitRows::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionSplitRows, "TransitionSplitRows", "cc.TransitionSplitRows",
		cc::TransitionSplitRows, "cc.TransitionSplitCols",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionSplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFadeTR_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:actionWithSize");
	LUA_TRY_INVOKE_R(1, &cc::TransitionFadeTR::actionWithSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionFadeTR_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, &cc::TransitionFadeTR::easeActionWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionFadeTR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeTR", "cc.TransitionFadeTR:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionFadeTR::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeTR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFadeTR, "TransitionFadeTR", "cc.TransitionFadeTR",
		cc::TransitionFadeTR, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cc_TransitionFadeTR_actionWithSize);
	LUA_METHOD("easeActionWithAction", lua_cc_TransitionFadeTR_easeActionWithAction);
	LUA_METHOD("create", lua_cc_TransitionFadeTR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFadeBL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeBL", "cc.TransitionFadeBL:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionFadeBL::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeBL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFadeBL, "TransitionFadeBL", "cc.TransitionFadeBL",
		cc::TransitionFadeBL, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFadeBL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFadeUp_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeUp", "cc.TransitionFadeUp:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionFadeUp::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeUp(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFadeUp, "TransitionFadeUp", "cc.TransitionFadeUp",
		cc::TransitionFadeUp, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFadeUp_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionFadeDown_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionFadeDown", "cc.TransitionFadeDown:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionFadeDown::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionFadeDown(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionFadeDown, "TransitionFadeDown", "cc.TransitionFadeDown",
		cc::TransitionFadeDown, "cc.TransitionFadeTR",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionFadeDown_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionPageTurn_actionWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:actionWithSize");
	LUA_TRY_INVOKE_R(1, &cc::TransitionPageTurn::actionWithSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TransitionPageTurn_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::TransitionPageTurn::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_TransitionPageTurn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionPageTurn", "cc.TransitionPageTurn:create");
	LUA_TRY_INVOKE_R(3, &cc::TransitionPageTurn::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionPageTurn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionPageTurn, "TransitionPageTurn", "cc.TransitionPageTurn",
		cc::TransitionPageTurn, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("actionWithSize", lua_cc_TransitionPageTurn_actionWithSize);
	LUA_METHOD("initWithDuration", lua_cc_TransitionPageTurn_initWithDuration);
	LUA_METHOD("create", lua_cc_TransitionPageTurn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgress_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgress", "cc.TransitionProgress:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgress::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgress(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgress, "TransitionProgress", "cc.TransitionProgress",
		cc::TransitionProgress, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgress_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressRadialCCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressRadialCCW::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressRadialCCW, "TransitionProgressRadialCCW", "cc.TransitionProgressRadialCCW",
		cc::TransitionProgressRadialCCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressRadialCCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressRadialCW_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressRadialCW", "cc.TransitionProgressRadialCW:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressRadialCW::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressRadialCW(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressRadialCW, "TransitionProgressRadialCW", "cc.TransitionProgressRadialCW",
		cc::TransitionProgressRadialCW, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressRadialCW_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressHorizontal_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressHorizontal", "cc.TransitionProgressHorizontal:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressHorizontal::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressHorizontal(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressHorizontal, "TransitionProgressHorizontal", "cc.TransitionProgressHorizontal",
		cc::TransitionProgressHorizontal, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressHorizontal_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressVertical_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressVertical", "cc.TransitionProgressVertical:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressVertical::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressVertical(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressVertical, "TransitionProgressVertical", "cc.TransitionProgressVertical",
		cc::TransitionProgressVertical, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressVertical_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressInOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressInOut", "cc.TransitionProgressInOut:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressInOut::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressInOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressInOut, "TransitionProgressInOut", "cc.TransitionProgressInOut",
		cc::TransitionProgressInOut, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressInOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TransitionProgressOutIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionProgressOutIn", "cc.TransitionProgressOutIn:create");
	LUA_TRY_INVOKE_R(2, &cc::TransitionProgressOutIn::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionProgressOutIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TransitionProgressOutIn, "TransitionProgressOutIn", "cc.TransitionProgressOutIn",
		cc::TransitionProgressOutIn, "cc.TransitionProgress",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TransitionProgressOutIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Camera_apply(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:apply");
	LUA_TRY_INVOKE(0, &cc::Camera::apply);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_applyViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:applyViewport");
	LUA_TRY_INVOKE(0, &cc::Camera::applyViewport);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_applyZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:applyZoom");
	LUA_TRY_INVOKE(0, &cc::Camera::applyZoom);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_clearBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:clearBackground");
	LUA_TRY_INVOKE(0, &cc::Camera::clearBackground);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getBackgroundBrush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getBackgroundBrush");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getBackgroundBrush);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getCameraFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getCameraFlag");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getCameraFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getDepth");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getDepthInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getDepthInView");
	LUA_TRY_INVOKE_R(1, &cc::Camera::getDepthInView);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_getFOV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getFOV");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getFOV);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getFarPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getFarPlane");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getFarPlane);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getNearPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getNearPlane");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getNearPlane);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getProjectionMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getProjectionMatrix");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getProjectionMatrix);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getRenderOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getRenderOrder");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getRenderOrder);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getViewMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getViewMatrix");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getViewMatrix);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getViewProjectionMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getViewProjectionMatrix");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getViewProjectionMatrix);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_getZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:getZoom");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getZoom);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_initDefault(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initDefault");
	LUA_TRY_INVOKE(0, &cc::Camera::initDefault);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_initOrthographic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initOrthographic");
	LUA_TRY_INVOKE_R(4, &cc::Camera::initOrthographic);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Camera_initPerspective(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:initPerspective");
	LUA_TRY_INVOKE_R(4, &cc::Camera::initPerspective);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Camera_isBrushValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isBrushValid");
	LUA_TRY_INVOKE_R(0, &cc::Camera::isBrushValid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_isViewProjectionUpdated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isViewProjectionUpdated");
	LUA_TRY_INVOKE_R(0, &cc::Camera::isViewProjectionUpdated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Camera_isVisibleInFrustum(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:isVisibleInFrustum");
	LUA_TRY_INVOKE_R(1, &cc::Camera::isVisibleInFrustum);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_lookAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:lookAt");
	LUA_TRY_INVOKE(2, &cc::Camera::lookAt);
	LUA_TRY_INVOKE(1, ([](cc::Camera* obj,const cc::Vec3& arg0){{return obj->lookAt(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Camera_project(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:project");
	LUA_TRY_INVOKE_R(1, &cc::Camera::project);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_projectGL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:projectGL");
	LUA_TRY_INVOKE_R(1, &cc::Camera::projectGL);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setAdditionalProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setAdditionalProjection");
	LUA_TRY_INVOKE(1, &cc::Camera::setAdditionalProjection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setBackgroundBrush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setBackgroundBrush");
	LUA_TRY_INVOKE(1, &cc::Camera::setBackgroundBrush);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setCameraFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setCameraFlag");
	LUA_TRY_INVOKE(1, &cc::Camera::setCameraFlag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setDepth");
	LUA_TRY_INVOKE(1, &cc::Camera::setDepth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setFOV(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setFOV");
	LUA_TRY_INVOKE(1, &cc::Camera::setFOV);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setFarPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setFarPlane");
	LUA_TRY_INVOKE(1, &cc::Camera::setFarPlane);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setNearPlane(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setNearPlane");
	LUA_TRY_INVOKE(1, &cc::Camera::setNearPlane);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setScene");
	LUA_TRY_INVOKE(1, &cc::Camera::setScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_setZoom(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Camera", "cc.Camera:setZoom");
	LUA_TRY_INVOKE(1, &cc::Camera::setZoom);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Camera_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:create");
	LUA_TRY_INVOKE_R(0, &cc::Camera::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Camera_createOrthographic(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:createOrthographic");
	LUA_TRY_INVOKE_R(4, &cc::Camera::createOrthographic);
	LUA_SINVOKE_FOOTER("4");
}
int lua_cc_Camera_createPerspective(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:createPerspective");
	LUA_TRY_INVOKE_R(4, &cc::Camera::createPerspective);
	LUA_SINVOKE_FOOTER("4");
}
int lua_cc_Camera_getDefaultCamera(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getDefaultCamera");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getDefaultCamera);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Camera_getDefaultViewport(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getDefaultViewport");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getDefaultViewport);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Camera_getVisitingCamera(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:getVisitingCamera");
	LUA_TRY_INVOKE_R(0, &cc::Camera::getVisitingCamera);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Camera_setDefaultViewport(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Camera", "cc.Camera:setDefaultViewport");
	LUA_TRY_INVOKE(1, &cc::Camera::setDefaultViewport);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccCamera(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Camera, "Camera", "cc.Camera",
		cc::Camera, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("apply", lua_cc_Camera_apply);
	LUA_METHOD("applyViewport", lua_cc_Camera_applyViewport);
	LUA_METHOD("applyZoom", lua_cc_Camera_applyZoom);
	LUA_METHOD("clearBackground", lua_cc_Camera_clearBackground);
	LUA_METHOD("getBackgroundBrush", lua_cc_Camera_getBackgroundBrush);
	LUA_METHOD("getCameraFlag", lua_cc_Camera_getCameraFlag);
	LUA_METHOD("getDepth", lua_cc_Camera_getDepth);
	LUA_METHOD("getDepthInView", lua_cc_Camera_getDepthInView);
	LUA_METHOD("getFOV", lua_cc_Camera_getFOV);
	LUA_METHOD("getFarPlane", lua_cc_Camera_getFarPlane);
	LUA_METHOD("getNearPlane", lua_cc_Camera_getNearPlane);
	LUA_METHOD("getProjectionMatrix", lua_cc_Camera_getProjectionMatrix);
	LUA_METHOD("getRenderOrder", lua_cc_Camera_getRenderOrder);
	LUA_METHOD("getViewMatrix", lua_cc_Camera_getViewMatrix);
	LUA_METHOD("getViewProjectionMatrix", lua_cc_Camera_getViewProjectionMatrix);
	LUA_METHOD("getZoom", lua_cc_Camera_getZoom);
	LUA_METHOD("initDefault", lua_cc_Camera_initDefault);
	LUA_METHOD("initOrthographic", lua_cc_Camera_initOrthographic);
	LUA_METHOD("initPerspective", lua_cc_Camera_initPerspective);
	LUA_METHOD("isBrushValid", lua_cc_Camera_isBrushValid);
	LUA_METHOD("isViewProjectionUpdated", lua_cc_Camera_isViewProjectionUpdated);
	LUA_METHOD("isVisibleInFrustum", lua_cc_Camera_isVisibleInFrustum);
	LUA_METHOD("lookAt", lua_cc_Camera_lookAt);
	LUA_METHOD("project", lua_cc_Camera_project);
	LUA_METHOD("projectGL", lua_cc_Camera_projectGL);
	LUA_METHOD("setAdditionalProjection", lua_cc_Camera_setAdditionalProjection);
	LUA_METHOD("setBackgroundBrush", lua_cc_Camera_setBackgroundBrush);
	LUA_METHOD("setCameraFlag", lua_cc_Camera_setCameraFlag);
	LUA_METHOD("setDepth", lua_cc_Camera_setDepth);
	LUA_METHOD("setFOV", lua_cc_Camera_setFOV);
	LUA_METHOD("setFarPlane", lua_cc_Camera_setFarPlane);
	LUA_METHOD("setNearPlane", lua_cc_Camera_setNearPlane);
	LUA_METHOD("setScene", lua_cc_Camera_setScene);
	LUA_METHOD("setZoom", lua_cc_Camera_setZoom);
	LUA_METHOD("create", lua_cc_Camera_create);
	LUA_METHOD("createOrthographic", lua_cc_Camera_createOrthographic);
	LUA_METHOD("createPerspective", lua_cc_Camera_createPerspective);
	LUA_METHOD("getDefaultCamera", lua_cc_Camera_getDefaultCamera);
	LUA_METHOD("getDefaultViewport", lua_cc_Camera_getDefaultViewport);
	LUA_METHOD("getVisitingCamera", lua_cc_Camera_getVisitingCamera);
	LUA_METHOD("setDefaultViewport", lua_cc_Camera_setDefaultViewport);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CameraBackgroundBrush_drawBackground(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:drawBackground");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundBrush::drawBackground);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundBrush_getBrushType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:getBrushType");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundBrush::getBrushType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundBrush_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:init");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundBrush::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundBrush_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:isValid");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundBrush::isValid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundBrush_createColorBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createColorBrush");
	LUA_TRY_INVOKE_R(2, &cc::CameraBackgroundBrush::createColorBrush);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cc_CameraBackgroundBrush_createDepthBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createDepthBrush");
	LUA_TRY_INVOKE_R(1, &cc::CameraBackgroundBrush::createDepthBrush);
	LUA_TRY_INVOKE_R(0, [](){{return cc::CameraBackgroundBrush::createDepthBrush();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int lua_cc_CameraBackgroundBrush_createNoneBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createNoneBrush");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundBrush::createNoneBrush);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundBrush_createSkyboxBrush(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundBrush", "cc.CameraBackgroundBrush:createSkyboxBrush");
	LUA_TRY_INVOKE_R(6, &cc::CameraBackgroundBrush::createSkyboxBrush);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccCameraBackgroundBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CameraBackgroundBrush, "CameraBackgroundBrush", "cc.CameraBackgroundBrush",
		cc::CameraBackgroundBrush, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("drawBackground", lua_cc_CameraBackgroundBrush_drawBackground);
	LUA_METHOD("getBrushType", lua_cc_CameraBackgroundBrush_getBrushType);
	LUA_METHOD("init", lua_cc_CameraBackgroundBrush_init);
	LUA_METHOD("isValid", lua_cc_CameraBackgroundBrush_isValid);
	LUA_METHOD("createColorBrush", lua_cc_CameraBackgroundBrush_createColorBrush);
	LUA_METHOD("createDepthBrush", lua_cc_CameraBackgroundBrush_createDepthBrush);
	LUA_METHOD("createNoneBrush", lua_cc_CameraBackgroundBrush_createNoneBrush);
	LUA_METHOD("createSkyboxBrush", lua_cc_CameraBackgroundBrush_createSkyboxBrush);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CameraBackgroundDepthBrush_setDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush:setDepth");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundDepthBrush::setDepth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundDepthBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush:create");
	LUA_TRY_INVOKE_R(1, &cc::CameraBackgroundDepthBrush::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccCameraBackgroundDepthBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CameraBackgroundDepthBrush, "CameraBackgroundDepthBrush", "cc.CameraBackgroundDepthBrush",
		cc::CameraBackgroundDepthBrush, "cc.CameraBackgroundBrush",
		nullptr, nullptr);
	LUA_METHOD("setDepth", lua_cc_CameraBackgroundDepthBrush_setDepth);
	LUA_METHOD("create", lua_cc_CameraBackgroundDepthBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CameraBackgroundColorBrush_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush:setColor");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundColorBrush::setColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundColorBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush:create");
	LUA_TRY_INVOKE_R(2, &cc::CameraBackgroundColorBrush::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccCameraBackgroundColorBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CameraBackgroundColorBrush, "CameraBackgroundColorBrush", "cc.CameraBackgroundColorBrush",
		cc::CameraBackgroundColorBrush, "cc.CameraBackgroundDepthBrush",
		nullptr, nullptr);
	LUA_METHOD("setColor", lua_cc_CameraBackgroundColorBrush_setColor);
	LUA_METHOD("create", lua_cc_CameraBackgroundColorBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_CameraBackgroundSkyBoxBrush_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundSkyBoxBrush::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundSkyBoxBrush_isActived(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:isActived");
	LUA_TRY_INVOKE_R(0, &cc::CameraBackgroundSkyBoxBrush::isActived);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_CameraBackgroundSkyBoxBrush_setActived(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setActived");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundSkyBoxBrush::setActived);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundSkyBoxBrush_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setTexture");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundSkyBoxBrush::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundSkyBoxBrush_setTextureValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:setTextureValid");
	LUA_TRY_INVOKE(1, &cc::CameraBackgroundSkyBoxBrush::setTextureValid);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_CameraBackgroundSkyBoxBrush_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cc::CameraBackgroundSkyBoxBrush>(*)(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, std::string_view)>(&cc::CameraBackgroundSkyBoxBrush::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::CameraBackgroundSkyBoxBrush>(*)()>(&cc::CameraBackgroundSkyBoxBrush::create));
	LUA_SINVOKE_FOOTER("0,6");
}
int luaReg_Core_ccCameraBackgroundSkyBoxBrush(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::CameraBackgroundSkyBoxBrush, "CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundSkyBoxBrush",
		cc::CameraBackgroundSkyBoxBrush, "cc.CameraBackgroundBrush",
		nullptr, nullptr);
	LUA_METHOD("getTexture", lua_cc_CameraBackgroundSkyBoxBrush_getTexture);
	LUA_METHOD("isActived", lua_cc_CameraBackgroundSkyBoxBrush_isActived);
	LUA_METHOD("setActived", lua_cc_CameraBackgroundSkyBoxBrush_setActived);
	LUA_METHOD("setTexture", lua_cc_CameraBackgroundSkyBoxBrush_setTexture);
	LUA_METHOD("setTextureValid", lua_cc_CameraBackgroundSkyBoxBrush_setTextureValid);
	LUA_METHOD("create", lua_cc_CameraBackgroundSkyBoxBrush_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_GridBase_afterBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:afterBlit");
	LUA_TRY_INVOKE(0, &cc::GridBase::afterBlit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_afterDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:afterDraw");
	LUA_TRY_INVOKE(1, &cc::GridBase::afterDraw);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_beforeBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:beforeBlit");
	LUA_TRY_INVOKE(0, &cc::GridBase::beforeBlit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_beforeDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:beforeDraw");
	LUA_TRY_INVOKE(0, &cc::GridBase::beforeDraw);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_blit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:blit");
	LUA_TRY_INVOKE(0, &cc::GridBase::blit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_calculateVertexPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:calculateVertexPoints");
	LUA_TRY_INVOKE(0, &cc::GridBase::calculateVertexPoints);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getGridRect");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::getGridRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_getGridSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getGridSize");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::getGridSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_getReuseGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getReuseGrid");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::getReuseGrid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_getStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:getStep");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::getStep);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:initWithSize");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cc::GridBase::*)(const cc::Vec2&, cc::Texture2D*, bool, const cc::Rect&)>(&cc::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::GridBase::*)(const cc::Vec2&, cc::Texture2D*, bool)>(&cc::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::GridBase::*)(const cc::Vec2&, const cc::Rect&)>(&cc::GridBase::initWithSize)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::GridBase::*)(const cc::Vec2&)>(&cc::GridBase::initWithSize));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cc_GridBase_isActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:isActive");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::isActive);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_isTextureFlipped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:isTextureFlipped");
	LUA_TRY_INVOKE_R(0, &cc::GridBase::isTextureFlipped);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_reuse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:reuse");
	LUA_TRY_INVOKE(0, &cc::GridBase::reuse);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_set2DProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:set2DProjection");
	LUA_TRY_INVOKE(0, &cc::GridBase::set2DProjection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GridBase_setActive(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setActive");
	LUA_TRY_INVOKE(1, &cc::GridBase::setActive);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_setGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setGridRect");
	LUA_TRY_INVOKE(1, &cc::GridBase::setGridRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_setGridSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setGridSize");
	LUA_TRY_INVOKE(1, &cc::GridBase::setGridSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_setReuseGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setReuseGrid");
	LUA_TRY_INVOKE(1, &cc::GridBase::setReuseGrid);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_setStep(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setStep");
	LUA_TRY_INVOKE(1, &cc::GridBase::setStep);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GridBase_setTextureFlipped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridBase", "cc.GridBase:setTextureFlipped");
	LUA_TRY_INVOKE(1, &cc::GridBase::setTextureFlipped);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccGridBase(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::GridBase, "GridBase", "cc.GridBase",
		cc::GridBase, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("afterBlit", lua_cc_GridBase_afterBlit);
	LUA_METHOD("afterDraw", lua_cc_GridBase_afterDraw);
	LUA_METHOD("beforeBlit", lua_cc_GridBase_beforeBlit);
	LUA_METHOD("beforeDraw", lua_cc_GridBase_beforeDraw);
	LUA_METHOD("blit", lua_cc_GridBase_blit);
	LUA_METHOD("calculateVertexPoints", lua_cc_GridBase_calculateVertexPoints);
	LUA_METHOD("getGridRect", lua_cc_GridBase_getGridRect);
	LUA_METHOD("getGridSize", lua_cc_GridBase_getGridSize);
	LUA_METHOD("getReuseGrid", lua_cc_GridBase_getReuseGrid);
	LUA_METHOD("getStep", lua_cc_GridBase_getStep);
	LUA_METHOD("initWithSize", lua_cc_GridBase_initWithSize);
	LUA_METHOD("isActive", lua_cc_GridBase_isActive);
	LUA_METHOD("isTextureFlipped", lua_cc_GridBase_isTextureFlipped);
	LUA_METHOD("reuse", lua_cc_GridBase_reuse);
	LUA_METHOD("set2DProjection", lua_cc_GridBase_set2DProjection);
	LUA_METHOD("setActive", lua_cc_GridBase_setActive);
	LUA_METHOD("setGridRect", lua_cc_GridBase_setGridRect);
	LUA_METHOD("setGridSize", lua_cc_GridBase_setGridSize);
	LUA_METHOD("setReuseGrid", lua_cc_GridBase_setReuseGrid);
	LUA_METHOD("setStep", lua_cc_GridBase_setStep);
	LUA_METHOD("setTextureFlipped", lua_cc_GridBase_setTextureFlipped);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Grid3D_getNeedDepthTestForBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3D", "cc.Grid3D:getNeedDepthTestForBlit");
	LUA_TRY_INVOKE_R(0, &cc::Grid3D::getNeedDepthTestForBlit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Grid3D_setNeedDepthTestForBlit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3D", "cc.Grid3D:setNeedDepthTestForBlit");
	LUA_TRY_INVOKE(1, &cc::Grid3D::setNeedDepthTestForBlit);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Grid3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Grid3D", "cc.Grid3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::Grid3D>(*)(const cc::Vec2&, cc::Texture2D*, bool, const cc::Rect&)>(&cc::Grid3D::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::Grid3D>(*)(const cc::Vec2&, cc::Texture2D*, bool)>(&cc::Grid3D::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::Grid3D>(*)(const cc::Vec2&, const cc::Rect&)>(&cc::Grid3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::Grid3D>(*)(const cc::Vec2&)>(&cc::Grid3D::create));
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Core_ccGrid3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Grid3D, "Grid3D", "cc.Grid3D",
		cc::Grid3D, "cc.GridBase",
		nullptr, nullptr);
	LUA_METHOD("getNeedDepthTestForBlit", lua_cc_Grid3D_getNeedDepthTestForBlit);
	LUA_METHOD("setNeedDepthTestForBlit", lua_cc_Grid3D_setNeedDepthTestForBlit);
	LUA_METHOD("create", lua_cc_Grid3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TiledGrid3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TiledGrid3D", "cc.TiledGrid3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::TiledGrid3D>(*)(const cc::Vec2&, cc::Texture2D*, bool, const cc::Rect&)>(&cc::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::TiledGrid3D>(*)(const cc::Vec2&, cc::Texture2D*, bool)>(&cc::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TiledGrid3D>(*)(const cc::Vec2&, const cc::Rect&)>(&cc::TiledGrid3D::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::TiledGrid3D>(*)(const cc::Vec2&)>(&cc::TiledGrid3D::create));
	LUA_SINVOKE_FOOTER("1,2,3,4");
}
int luaReg_Core_ccTiledGrid3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TiledGrid3D, "TiledGrid3D", "cc.TiledGrid3D",
		cc::TiledGrid3D, "cc.GridBase",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_TiledGrid3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_BaseLight_getIntensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getIntensity");
	LUA_TRY_INVOKE_R(0, &cc::BaseLight::getIntensity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_BaseLight_getLightFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getLightFlag");
	LUA_TRY_INVOKE_R(0, &cc::BaseLight::getLightFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_BaseLight_getLightType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:getLightType");
	LUA_TRY_INVOKE_R(0, &cc::BaseLight::getLightType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_BaseLight_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::BaseLight::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_BaseLight_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setEnabled");
	LUA_TRY_INVOKE(1, &cc::BaseLight::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_BaseLight_setIntensity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setIntensity");
	LUA_TRY_INVOKE(1, &cc::BaseLight::setIntensity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_BaseLight_setLightFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BaseLight", "cc.BaseLight:setLightFlag");
	LUA_TRY_INVOKE(1, &cc::BaseLight::setLightFlag);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccBaseLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::BaseLight, "BaseLight", "cc.BaseLight",
		cc::BaseLight, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getIntensity", lua_cc_BaseLight_getIntensity);
	LUA_METHOD("getLightFlag", lua_cc_BaseLight_getLightFlag);
	LUA_METHOD("getLightType", lua_cc_BaseLight_getLightType);
	LUA_METHOD("isEnabled", lua_cc_BaseLight_isEnabled);
	LUA_METHOD("setEnabled", lua_cc_BaseLight_setEnabled);
	LUA_METHOD("setIntensity", lua_cc_BaseLight_setIntensity);
	LUA_METHOD("setLightFlag", lua_cc_BaseLight_setLightFlag);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_DirectionLight_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:getDirection");
	LUA_TRY_INVOKE_R(0, &cc::DirectionLight::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DirectionLight_getDirectionInWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:getDirectionInWorld");
	LUA_TRY_INVOKE_R(0, &cc::DirectionLight::getDirectionInWorld);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DirectionLight_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:setDirection");
	LUA_TRY_INVOKE(1, &cc::DirectionLight::setDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_DirectionLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DirectionLight", "cc.DirectionLight:create");
	LUA_TRY_INVOKE_R(2, &cc::DirectionLight::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccDirectionLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::DirectionLight, "DirectionLight", "cc.DirectionLight",
		cc::DirectionLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getDirection", lua_cc_DirectionLight_getDirection);
	LUA_METHOD("getDirectionInWorld", lua_cc_DirectionLight_getDirectionInWorld);
	LUA_METHOD("setDirection", lua_cc_DirectionLight_setDirection);
	LUA_METHOD("create", lua_cc_DirectionLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_PointLight_getRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PointLight", "cc.PointLight:getRange");
	LUA_TRY_INVOKE_R(0, &cc::PointLight::getRange);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_PointLight_setRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.PointLight", "cc.PointLight:setRange");
	LUA_TRY_INVOKE(1, &cc::PointLight::setRange);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_PointLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.PointLight", "cc.PointLight:create");
	LUA_TRY_INVOKE_R(3, &cc::PointLight::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccPointLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::PointLight, "PointLight", "cc.PointLight",
		cc::PointLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getRange", lua_cc_PointLight_getRange);
	LUA_METHOD("setRange", lua_cc_PointLight_setRange);
	LUA_METHOD("create", lua_cc_PointLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SpotLight_getCosInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getCosInnerAngle");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getCosInnerAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getCosOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getCosOuterAngle");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getCosOuterAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getDirection");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getDirection);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getDirectionInWorld(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getDirectionInWorld");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getDirectionInWorld);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getInnerAngle");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getInnerAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getOuterAngle");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getOuterAngle);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_getRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:getRange");
	LUA_TRY_INVOKE_R(0, &cc::SpotLight::getRange);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpotLight_setDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setDirection");
	LUA_TRY_INVOKE(1, &cc::SpotLight::setDirection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpotLight_setInnerAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setInnerAngle");
	LUA_TRY_INVOKE(1, &cc::SpotLight::setInnerAngle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpotLight_setOuterAngle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setOuterAngle");
	LUA_TRY_INVOKE(1, &cc::SpotLight::setOuterAngle);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpotLight_setRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpotLight", "cc.SpotLight:setRange");
	LUA_TRY_INVOKE(1, &cc::SpotLight::setRange);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpotLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpotLight", "cc.SpotLight:create");
	LUA_TRY_INVOKE_R(6, &cc::SpotLight::create);
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccSpotLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SpotLight, "SpotLight", "cc.SpotLight",
		cc::SpotLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("getCosInnerAngle", lua_cc_SpotLight_getCosInnerAngle);
	LUA_METHOD("getCosOuterAngle", lua_cc_SpotLight_getCosOuterAngle);
	LUA_METHOD("getDirection", lua_cc_SpotLight_getDirection);
	LUA_METHOD("getDirectionInWorld", lua_cc_SpotLight_getDirectionInWorld);
	LUA_METHOD("getInnerAngle", lua_cc_SpotLight_getInnerAngle);
	LUA_METHOD("getOuterAngle", lua_cc_SpotLight_getOuterAngle);
	LUA_METHOD("getRange", lua_cc_SpotLight_getRange);
	LUA_METHOD("setDirection", lua_cc_SpotLight_setDirection);
	LUA_METHOD("setInnerAngle", lua_cc_SpotLight_setInnerAngle);
	LUA_METHOD("setOuterAngle", lua_cc_SpotLight_setOuterAngle);
	LUA_METHOD("setRange", lua_cc_SpotLight_setRange);
	LUA_METHOD("create", lua_cc_SpotLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_AmbientLight_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AmbientLight", "cc.AmbientLight:create");
	LUA_TRY_INVOKE_R(1, &cc::AmbientLight::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAmbientLight(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AmbientLight, "AmbientLight", "cc.AmbientLight",
		cc::AmbientLight, "cc.BaseLight",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_AmbientLight_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_RenderState_bindPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderState", "cc.RenderState:bindPass");
	LUA_TRY_INVOKE(2, &cc::RenderState::bindPass);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_RenderState_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderState", "cc.RenderState:getName");
	LUA_TRY_INVOKE_R(0, &cc::RenderState::getName);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccRenderState(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RenderState, "RenderState", "cc.RenderState",
		cc::RenderState, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("bindPass", lua_cc_RenderState_bindPass);
	LUA_METHOD("getName", lua_cc_RenderState_getName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Technique_addPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:addPass");
	LUA_TRY_INVOKE(1, &cc::Technique::addPass);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Technique_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:clone");
	LUA_TRY_INVOKE_R(0, &cc::Technique::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Technique_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getName");
	LUA_TRY_INVOKE_R(0, &cc::Technique::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Technique_getPassByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPassByIndex");
	LUA_TRY_INVOKE_R(1, &cc::Technique::getPassByIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Technique_getPassCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPassCount");
	LUA_TRY_INVOKE_R(0, &cc::Technique::getPassCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Technique_getPasses(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:getPasses");
	LUA_TRY_INVOKE_R(0, &cc::Technique::getPasses);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Technique_setMaterial(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Technique", "cc.Technique:setMaterial");
	LUA_TRY_INVOKE(1, &cc::Technique::setMaterial);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Technique_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Technique", "cc.Technique:create");
	LUA_TRY_INVOKE_R(1, &cc::Technique::create);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Technique_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Technique", "cc.Technique:createWithProgramState");
	LUA_TRY_INVOKE_R(2, &cc::Technique::createWithProgramState);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTechnique(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Technique, "Technique", "cc.Technique",
		cc::Technique, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addPass", lua_cc_Technique_addPass);
	LUA_METHOD("clone", lua_cc_Technique_clone);
	LUA_METHOD("getName", lua_cc_Technique_getName);
	LUA_METHOD("getPassByIndex", lua_cc_Technique_getPassByIndex);
	LUA_METHOD("getPassCount", lua_cc_Technique_getPassCount);
	LUA_METHOD("getPasses", lua_cc_Technique_getPasses);
	LUA_METHOD("setMaterial", lua_cc_Technique_setMaterial);
	LUA_METHOD("create", lua_cc_Technique_create);
	LUA_METHOD("createWithProgramState", lua_cc_Technique_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Material_addTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:addTechnique");
	LUA_TRY_INVOKE(1, &cc::Material::addTechnique);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:clone");
	LUA_TRY_INVOKE_R(0, &cc::Material::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:draw");
	LUA_TRY_INVOKE(8, &cc::Material::draw);
	LUA_INVOKE_FOOTER("8");
}
int lua_cc_Material_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getName");
	LUA_TRY_INVOKE_R(0, &cc::Material::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_getPrimitiveType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getPrimitiveType");
	LUA_TRY_INVOKE_R(0, &cc::Material::getPrimitiveType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_getRenderState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getRenderState");
	LUA_TRY_INVOKE_R(0, &cc::Material::getRenderState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_getTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechnique");
	LUA_TRY_INVOKE_R(0, &cc::Material::getTechnique);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_getTechniqueByIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueByIndex");
	LUA_TRY_INVOKE_R(1, &cc::Material::getTechniqueByIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_getTechniqueByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueByName");
	LUA_TRY_INVOKE_R(1, &cc::Material::getTechniqueByName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_getTechniqueCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniqueCount");
	LUA_TRY_INVOKE_R(0, &cc::Material::getTechniqueCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_getTechniques(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:getTechniques");
	LUA_TRY_INVOKE_R(0, &cc::Material::getTechniques);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_isForce2DQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:isForce2DQueue");
	LUA_TRY_INVOKE_R(0, &cc::Material::isForce2DQueue);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_isTransparent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:isTransparent");
	LUA_TRY_INVOKE_R(0, &cc::Material::isTransparent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Material_setForce2DQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setForce2DQueue");
	LUA_TRY_INVOKE(1, &cc::Material::setForce2DQueue);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setName");
	LUA_TRY_INVOKE(1, &cc::Material::setName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_setPrimitiveType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setPrimitiveType");
	LUA_TRY_INVOKE(1, &cc::Material::setPrimitiveType);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_setTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setTechnique");
	LUA_TRY_INVOKE(1, &cc::Material::setTechnique);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_setTransparent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Material", "cc.Material:setTransparent");
	LUA_TRY_INVOKE(1, &cc::Material::setTransparent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Material_createWithFilename(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Material", "cc.Material:createWithFilename");
	LUA_TRY_INVOKE_R(1, &cc::Material::createWithFilename);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Material_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Material", "cc.Material:createWithProgramState");
	LUA_TRY_INVOKE_R(1, &cc::Material::createWithProgramState);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMaterial(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Material, "Material", "cc.Material",
		cc::Material, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addTechnique", lua_cc_Material_addTechnique);
	LUA_METHOD("clone", lua_cc_Material_clone);
	LUA_METHOD("draw", lua_cc_Material_draw);
	LUA_METHOD("getName", lua_cc_Material_getName);
	LUA_METHOD("getPrimitiveType", lua_cc_Material_getPrimitiveType);
	LUA_METHOD("getRenderState", lua_cc_Material_getRenderState);
	LUA_METHOD("getTechnique", lua_cc_Material_getTechnique);
	LUA_METHOD("getTechniqueByIndex", lua_cc_Material_getTechniqueByIndex);
	LUA_METHOD("getTechniqueByName", lua_cc_Material_getTechniqueByName);
	LUA_METHOD("getTechniqueCount", lua_cc_Material_getTechniqueCount);
	LUA_METHOD("getTechniques", lua_cc_Material_getTechniques);
	LUA_METHOD("isForce2DQueue", lua_cc_Material_isForce2DQueue);
	LUA_METHOD("isTransparent", lua_cc_Material_isTransparent);
	LUA_METHOD("setForce2DQueue", lua_cc_Material_setForce2DQueue);
	LUA_METHOD("setName", lua_cc_Material_setName);
	LUA_METHOD("setPrimitiveType", lua_cc_Material_setPrimitiveType);
	LUA_METHOD("setTechnique", lua_cc_Material_setTechnique);
	LUA_METHOD("setTransparent", lua_cc_Material_setTransparent);
	LUA_METHOD("createWithFilename", lua_cc_Material_createWithFilename);
	LUA_METHOD("createWithProgramState", lua_cc_Material_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Pass_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:clone");
	LUA_TRY_INVOKE_R(0, &cc::Pass::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Pass_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:draw");
	LUA_TRY_INVOKE(8, &cc::Pass::draw);
	LUA_INVOKE_FOOTER("8");
}
int lua_cc_Pass_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getName");
	LUA_TRY_INVOKE_R(0, &cc::Pass::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Pass_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getProgramState");
	LUA_TRY_INVOKE_R(0, &cc::Pass::getProgramState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Pass_getVertexAttributeBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:getVertexAttributeBinding");
	LUA_TRY_INVOKE_R(0, &cc::Pass::getVertexAttributeBinding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Pass_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setName");
	LUA_TRY_INVOKE(1, &cc::Pass::setName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Pass_setTechnique(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setTechnique");
	LUA_TRY_INVOKE(1, &cc::Pass::setTechnique);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Pass_setUniformNormTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setUniformNormTexture");
	LUA_TRY_INVOKE(2, &cc::Pass::setUniformNormTexture);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Pass_setUniformTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setUniformTexture");
	LUA_TRY_INVOKE(2, &cc::Pass::setUniformTexture);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Pass_setVertexAttribBinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:setVertexAttribBinding");
	LUA_TRY_INVOKE(1, &cc::Pass::setVertexAttribBinding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Pass_updateMVPUniform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Pass", "cc.Pass:updateMVPUniform");
	LUA_TRY_INVOKE(1, &cc::Pass::updateMVPUniform);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Pass_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Pass", "cc.Pass:create");
	LUA_TRY_INVOKE_R(1, &cc::Pass::create);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Pass_createWithProgramState(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Pass", "cc.Pass:createWithProgramState");
	LUA_TRY_INVOKE_R(2, &cc::Pass::createWithProgramState);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccPass(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Pass, "Pass", "cc.Pass",
		cc::Pass, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cc_Pass_clone);
	LUA_METHOD("draw", lua_cc_Pass_draw);
	LUA_METHOD("getName", lua_cc_Pass_getName);
	LUA_METHOD("getProgramState", lua_cc_Pass_getProgramState);
	LUA_METHOD("getVertexAttributeBinding", lua_cc_Pass_getVertexAttributeBinding);
	LUA_METHOD("setName", lua_cc_Pass_setName);
	LUA_METHOD("setTechnique", lua_cc_Pass_setTechnique);
	LUA_METHOD("setUniformNormTexture", lua_cc_Pass_setUniformNormTexture);
	LUA_METHOD("setUniformTexture", lua_cc_Pass_setUniformTexture);
	LUA_METHOD("setVertexAttribBinding", lua_cc_Pass_setVertexAttribBinding);
	LUA_METHOD("updateMVPUniform", lua_cc_Pass_updateMVPUniform);
	LUA_METHOD("create", lua_cc_Pass_create);
	LUA_METHOD("createWithProgramState", lua_cc_Pass_createWithProgramState);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
