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
