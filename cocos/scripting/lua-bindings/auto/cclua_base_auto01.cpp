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

int lua_cocos2d_Scene_getDefaultCamera(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getDefaultCamera");
	LUA_TRY_INVOKE_R(0, &cocos2d::Scene::getDefaultCamera);
	LUA_INVOKE_FOOTER("0");
}
#if CC_USE_NAVMESH
int lua_cocos2d_Scene_getNavMesh_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getNavMesh");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::NavMesh*(cocos2d::Scene::*)()const>(&cocos2d::Scene::getNavMesh));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
int lua_cocos2d_Scene_getPhysics3DWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysics3DWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Physics3DWorld*(cocos2d::Scene::*)()>(&cocos2d::Scene::getPhysics3DWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS
int lua_cocos2d_Scene_getPhysicsWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::PhysicsWorld*(cocos2d::Scene::*)()const>(&cocos2d::Scene::getPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cocos2d_Scene_initPhysicsWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Scene::*)()>(&cocos2d::Scene::initPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cocos2d_Scene_initWithPhysics_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithPhysics");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Scene::*)()>(&cocos2d::Scene::initWithPhysics));
	LUA_INVOKE_FOOTER("0");
}
#endif
int lua_cocos2d_Scene_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithSize");
	LUA_TRY_INVOKE_R(1, &cocos2d::Scene::initWithSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scene_onProjectionChanged(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:onProjectionChanged");
	LUA_TRY_INVOKE(1, &cocos2d::Scene::onProjectionChanged);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scene_setCameraOrderDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setCameraOrderDirty");
	LUA_TRY_INVOKE(0, &cocos2d::Scene::setCameraOrderDirty);
	LUA_INVOKE_FOOTER("0");
}
#if CC_USE_NAVMESH
int lua_cocos2d_Scene_setNavMesh_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMesh");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(cocos2d::NavMesh*)>(&cocos2d::Scene::setNavMesh));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_NAVMESH
int lua_cocos2d_Scene_setNavMeshDebugCamera_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMeshDebugCamera");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(cocos2d::Camera*)>(&cocos2d::Scene::setNavMeshDebugCamera));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
int lua_cocos2d_Scene_setPhysics3DDebugCamera_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setPhysics3DDebugCamera");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(cocos2d::Camera*)>(&cocos2d::Scene::setPhysics3DDebugCamera));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH
int lua_cocos2d_Scene_stepPhysicsAndNavigation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:stepPhysicsAndNavigation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(float)>(&cocos2d::Scene::stepPhysicsAndNavigation));
	LUA_INVOKE_FOOTER("1");
}
#endif
int lua_cocos2d_Scene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:create");
	LUA_TRY_INVOKE_R(0, &cocos2d::Scene::create);
	LUA_SINVOKE_FOOTER("0");
}
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cocos2d_Scene_createWithPhysics_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithPhysics");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::Scene>(*)()>(&cocos2d::Scene::createWithPhysics));
	LUA_SINVOKE_FOOTER("0");
}
#endif
int lua_cocos2d_Scene_createWithSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithSize");
	LUA_TRY_INVOKE_R(1, &cocos2d::Scene::createWithSize);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Scene, "Scene", "cc.Scene",
		cocos2d::Scene, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getDefaultCamera", lua_cocos2d_Scene_getDefaultCamera);
	#if CC_USE_NAVMESH
LUA_METHOD("getNavMesh", lua_cocos2d_Scene_getNavMesh_1);
#endif
	#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
LUA_METHOD("getPhysics3DWorld", lua_cocos2d_Scene_getPhysics3DWorld_1);
#endif
	#if CC_USE_PHYSICS
LUA_METHOD("getPhysicsWorld", lua_cocos2d_Scene_getPhysicsWorld_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("initPhysicsWorld", lua_cocos2d_Scene_initPhysicsWorld_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("initWithPhysics", lua_cocos2d_Scene_initWithPhysics_1);
#endif
	LUA_METHOD("initWithSize", lua_cocos2d_Scene_initWithSize);
	LUA_METHOD("onProjectionChanged", lua_cocos2d_Scene_onProjectionChanged);
	LUA_METHOD("setCameraOrderDirty", lua_cocos2d_Scene_setCameraOrderDirty);
	#if CC_USE_NAVMESH
LUA_METHOD("setNavMesh", lua_cocos2d_Scene_setNavMesh_1);
#endif
	#if CC_USE_NAVMESH
LUA_METHOD("setNavMeshDebugCamera", lua_cocos2d_Scene_setNavMeshDebugCamera_1);
#endif
	#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
LUA_METHOD("setPhysics3DDebugCamera", lua_cocos2d_Scene_setPhysics3DDebugCamera_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH
LUA_METHOD("stepPhysicsAndNavigation", lua_cocos2d_Scene_stepPhysicsAndNavigation_1);
#endif
	LUA_METHOD("create", lua_cocos2d_Scene_create);
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("createWithPhysics", lua_cocos2d_Scene_createWithPhysics_1);
#endif
	LUA_METHOD("createWithSize", lua_cocos2d_Scene_createWithSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GLView_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:endToLua");
	LUA_TRY_INVOKE(0, &cocos2d::GLView::end);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getAllTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getAllTouches");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getAllTouches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getContentScaleFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getDesignResolutionSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getDesignResolutionSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getFrameSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameZoomFactor");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getFrameZoomFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getResolutionPolicy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getResolutionPolicy");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getResolutionPolicy);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getRetinaFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getRetinaFactor");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getRetinaFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getSafeAreaRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleX");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getScaleX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleY");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getScaleY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScissorRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getScissorRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewName");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getViewName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getViewPortRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewPortRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getViewPortRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getVisibleOrigin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getVisibleRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::getVisibleSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isOpenGLReady(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isOpenGLReady");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::isOpenGLReady);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isRetinaDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isRetinaDisplay");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::isRetinaDisplay);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isScissorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isScissorEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::isScissorEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_pollEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:pollEvents");
	LUA_TRY_INVOKE(0, &cocos2d::GLView::pollEvents);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_renderScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:renderScene");
	LUA_TRY_INVOKE(2, &cocos2d::GLView::renderScene);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_GLView_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setContentScaleFactor");
	LUA_TRY_INVOKE_R(1, &cocos2d::GLView::setContentScaleFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setCursorVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setCursorVisible");
	LUA_TRY_INVOKE(1, &cocos2d::GLView::setCursorVisible);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setDefaultIcon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDefaultIcon");
	LUA_TRY_INVOKE(0, &cocos2d::GLView::setDefaultIcon);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_setDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDesignResolutionSize");
	LUA_TRY_INVOKE(3, &cocos2d::GLView::setDesignResolutionSize);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_GLView_setFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameSize");
	LUA_TRY_INVOKE(2, &cocos2d::GLView::setFrameSize);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_GLView_setFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameZoomFactor");
	LUA_TRY_INVOKE(1, &cocos2d::GLView::setFrameZoomFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setIMEKeyboardState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setIMEKeyboardState");
	LUA_TRY_INVOKE(1, &cocos2d::GLView::setIMEKeyboardState);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setIcon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setIcon");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::GLView::*)(const std::vector<std::string_view>&)const>(&cocos2d::GLView::setIcon));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::GLView::*)(std::string_view)const>(&cocos2d::GLView::setIcon));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setScissorInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setScissorInPoints");
	LUA_TRY_INVOKE(4, &cocos2d::GLView::setScissorInPoints);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_GLView_setViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewName");
	LUA_TRY_INVOKE(1, &cocos2d::GLView::setViewName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setViewPortInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewPortInPoints");
	LUA_TRY_INVOKE(4, &cocos2d::GLView::setViewPortInPoints);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_GLView_swapBuffers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:swapBuffers");
	LUA_TRY_INVOKE(0, &cocos2d::GLView::swapBuffers);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_windowShouldClose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:windowShouldClose");
	LUA_TRY_INVOKE_R(0, &cocos2d::GLView::windowShouldClose);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGLView(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GLView, "GLView", "cc.GLView",
		cocos2d::GLView, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("endToLua", lua_cocos2d_GLView_endToLua);
	LUA_METHOD("getAllTouches", lua_cocos2d_GLView_getAllTouches);
	LUA_METHOD("getContentScaleFactor", lua_cocos2d_GLView_getContentScaleFactor);
	LUA_METHOD("getDesignResolutionSize", lua_cocos2d_GLView_getDesignResolutionSize);
	LUA_METHOD("getFrameSize", lua_cocos2d_GLView_getFrameSize);
	LUA_METHOD("getFrameZoomFactor", lua_cocos2d_GLView_getFrameZoomFactor);
	LUA_METHOD("getResolutionPolicy", lua_cocos2d_GLView_getResolutionPolicy);
	LUA_METHOD("getRetinaFactor", lua_cocos2d_GLView_getRetinaFactor);
	LUA_METHOD("getSafeAreaRect", lua_cocos2d_GLView_getSafeAreaRect);
	LUA_METHOD("getScaleX", lua_cocos2d_GLView_getScaleX);
	LUA_METHOD("getScaleY", lua_cocos2d_GLView_getScaleY);
	LUA_METHOD("getScissorRect", lua_cocos2d_GLView_getScissorRect);
	LUA_METHOD("getViewName", lua_cocos2d_GLView_getViewName);
	LUA_METHOD("getViewPortRect", lua_cocos2d_GLView_getViewPortRect);
	LUA_METHOD("getVisibleOrigin", lua_cocos2d_GLView_getVisibleOrigin);
	LUA_METHOD("getVisibleRect", lua_cocos2d_GLView_getVisibleRect);
	LUA_METHOD("getVisibleSize", lua_cocos2d_GLView_getVisibleSize);
	LUA_METHOD("isOpenGLReady", lua_cocos2d_GLView_isOpenGLReady);
	LUA_METHOD("isRetinaDisplay", lua_cocos2d_GLView_isRetinaDisplay);
	LUA_METHOD("isScissorEnabled", lua_cocos2d_GLView_isScissorEnabled);
	LUA_METHOD("pollEvents", lua_cocos2d_GLView_pollEvents);
	LUA_METHOD("renderScene", lua_cocos2d_GLView_renderScene);
	LUA_METHOD("setContentScaleFactor", lua_cocos2d_GLView_setContentScaleFactor);
	LUA_METHOD("setCursorVisible", lua_cocos2d_GLView_setCursorVisible);
	LUA_METHOD("setDefaultIcon", lua_cocos2d_GLView_setDefaultIcon);
	LUA_METHOD("setDesignResolutionSize", lua_cocos2d_GLView_setDesignResolutionSize);
	LUA_METHOD("setFrameSize", lua_cocos2d_GLView_setFrameSize);
	LUA_METHOD("setFrameZoomFactor", lua_cocos2d_GLView_setFrameZoomFactor);
	LUA_METHOD("setIMEKeyboardState", lua_cocos2d_GLView_setIMEKeyboardState);
	LUA_METHOD("setIcon", lua_cocos2d_GLView_setIcon);
	LUA_METHOD("setScissorInPoints", lua_cocos2d_GLView_setScissorInPoints);
	LUA_METHOD("setViewName", lua_cocos2d_GLView_setViewName);
	LUA_METHOD("setViewPortInPoints", lua_cocos2d_GLView_setViewPortInPoints);
	LUA_METHOD("swapBuffers", lua_cocos2d_GLView_swapBuffers);
	LUA_METHOD("windowShouldClose", lua_cocos2d_GLView_windowShouldClose);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Director_convertToGL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:convertToGL");
	LUA_TRY_INVOKE_R(1, &cocos2d::Director::convertToGL);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_convertToUI(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:convertToUI");
	LUA_TRY_INVOKE_R(1, &cocos2d::Director::convertToUI);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_drawScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:drawScene");
	LUA_TRY_INVOKE(0, &cocos2d::Director::drawScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:endToLua");
	LUA_TRY_INVOKE(0, &cocos2d::Director::end);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getActionManager");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getActionManager);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAnimationInterval");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getAnimationInterval);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getAxmolThreadId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAxmolThreadId");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getCocos2dThreadId);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getConsole(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getConsole");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getConsole);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getContentScaleFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getDeltaTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getDeltaTime");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getDeltaTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getEventDispatcher");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getEventDispatcher);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getFrameRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getFrameRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getFrameRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getMatrix");
	LUA_TRY_INVOKE_R(1, &cocos2d::Director::getMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_getNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getNotificationNode");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getNotificationNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getOpenGLView");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getOpenGLView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRenderer");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getRunningScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRunningScene");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getRunningScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getSafeAreaRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getScheduler");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getScheduler);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getSecondsPerFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSecondsPerFrame");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getSecondsPerFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getTextureCache(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTextureCache");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getTextureCache);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getTotalFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTotalFrames");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getTotalFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getVisibleOrigin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getVisibleSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getWinSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getWinSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getWinSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSizeInPixels");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getWinSizeInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getZEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getZEye");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getZEye);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isChildrenIndexerEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isChildrenIndexerEnabled");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isChildrenIndexerEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isNextDeltaTimeZero");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isNextDeltaTimeZero);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isPaused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isPaused");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isPaused);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isSendCleanupToScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isSendCleanupToScene");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isSendCleanupToScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isStatsDisplay");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isStatsDisplay);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isValid");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::isValid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_loadIdentityMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadIdentityMatrix");
	LUA_TRY_INVOKE(1, &cocos2d::Director::loadIdentityMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_loadMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadMatrix");
	LUA_TRY_INVOKE(2, &cocos2d::Director::loadMatrix);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Director_mainLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:mainLoop");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(float)>(&cocos2d::Director::mainLoop));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::mainLoop));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Director_multiplyMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:multiplyMatrix");
	LUA_TRY_INVOKE(2, &cocos2d::Director::multiplyMatrix);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Director_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pause");
	LUA_TRY_INVOKE(0, &cocos2d::Director::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popMatrix");
	LUA_TRY_INVOKE(1, &cocos2d::Director::popMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_popScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popScene");
	LUA_TRY_INVOKE(0, &cocos2d::Director::popScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popToRootScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToRootScene");
	LUA_TRY_INVOKE(0, &cocos2d::Director::popToRootScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popToSceneStackLevel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToSceneStackLevel");
	LUA_TRY_INVOKE(1, &cocos2d::Director::popToSceneStackLevel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_purgeCachedData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:purgeCachedData");
	LUA_TRY_INVOKE(0, &cocos2d::Director::purgeCachedData);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_pushMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushMatrix");
	LUA_TRY_INVOKE(1, &cocos2d::Director::pushMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_pushScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushScene");
	LUA_TRY_INVOKE(1, &cocos2d::Director::pushScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_replaceScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:replaceScene");
	LUA_TRY_INVOKE(1, &cocos2d::Director::replaceScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_resetMatrixStack(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resetMatrixStack");
	LUA_TRY_INVOKE(0, &cocos2d::Director::resetMatrixStack);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_restart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:restart");
	LUA_TRY_INVOKE(0, &cocos2d::Director::restart);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resume");
	LUA_TRY_INVOKE(0, &cocos2d::Director::resume);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_runWithScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:runWithScene");
	LUA_TRY_INVOKE(1, &cocos2d::Director::runWithScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setActionManager");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setActionManager);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setAnimationInterval");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(float)>(&cocos2d::Director::setAnimationInterval));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setChildrenIndexerEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setChildrenIndexerEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setChildrenIndexerEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setClearColor");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setClearColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setContentScaleFactor");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setContentScaleFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setDefaultValues");
	LUA_TRY_INVOKE(0, &cocos2d::Director::setDefaultValues);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_setEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setEventDispatcher");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setEventDispatcher);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setGLDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setGLDefaultValues");
	LUA_TRY_INVOKE(0, &cocos2d::Director::setGLDefaultValues);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_setNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNextDeltaTimeZero");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setNextDeltaTimeZero);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNotificationNode");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setNotificationNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setOpenGLView");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setOpenGLView);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setProjection");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setProjection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setScheduler");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setScheduler);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setStatsAnchor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsAnchor");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setStatsAnchor);
	LUA_TRY_INVOKE(0, [](cocos2d::Director* obj){{return obj->setStatsAnchor();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Director_setStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsDisplay");
	LUA_TRY_INVOKE(1, &cocos2d::Director::setStatsDisplay);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setViewport");
	LUA_TRY_INVOKE(0, &cocos2d::Director::setViewport);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_startAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:startAnimation");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::startAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_stopAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:stopAnimation");
	LUA_TRY_INVOKE(0, &cocos2d::Director::stopAnimation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Director", "cc.Director:getInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::Director::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccDirector(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Director, "Director", "cc.Director",
		cocos2d::Director, "",
		nullptr, nullptr);
	LUA_METHOD("convertToGL", lua_cocos2d_Director_convertToGL);
	LUA_METHOD("convertToUI", lua_cocos2d_Director_convertToUI);
	LUA_METHOD("drawScene", lua_cocos2d_Director_drawScene);
	LUA_METHOD("endToLua", lua_cocos2d_Director_endToLua);
	LUA_METHOD("getActionManager", lua_cocos2d_Director_getActionManager);
	LUA_METHOD("getAnimationInterval", lua_cocos2d_Director_getAnimationInterval);
	LUA_METHOD("getAxmolThreadId", lua_cocos2d_Director_getAxmolThreadId);
	LUA_METHOD("getConsole", lua_cocos2d_Director_getConsole);
	LUA_METHOD("getContentScaleFactor", lua_cocos2d_Director_getContentScaleFactor);
	LUA_METHOD("getDeltaTime", lua_cocos2d_Director_getDeltaTime);
	LUA_METHOD("getEventDispatcher", lua_cocos2d_Director_getEventDispatcher);
	LUA_METHOD("getFrameRate", lua_cocos2d_Director_getFrameRate);
	LUA_METHOD("getMatrix", lua_cocos2d_Director_getMatrix);
	LUA_METHOD("getNotificationNode", lua_cocos2d_Director_getNotificationNode);
	LUA_METHOD("getOpenGLView", lua_cocos2d_Director_getOpenGLView);
	LUA_METHOD("getRenderer", lua_cocos2d_Director_getRenderer);
	LUA_METHOD("getRunningScene", lua_cocos2d_Director_getRunningScene);
	LUA_METHOD("getSafeAreaRect", lua_cocos2d_Director_getSafeAreaRect);
	LUA_METHOD("getScheduler", lua_cocos2d_Director_getScheduler);
	LUA_METHOD("getSecondsPerFrame", lua_cocos2d_Director_getSecondsPerFrame);
	LUA_METHOD("getTextureCache", lua_cocos2d_Director_getTextureCache);
	LUA_METHOD("getTotalFrames", lua_cocos2d_Director_getTotalFrames);
	LUA_METHOD("getVisibleOrigin", lua_cocos2d_Director_getVisibleOrigin);
	LUA_METHOD("getVisibleSize", lua_cocos2d_Director_getVisibleSize);
	LUA_METHOD("getWinSize", lua_cocos2d_Director_getWinSize);
	LUA_METHOD("getWinSizeInPixels", lua_cocos2d_Director_getWinSizeInPixels);
	LUA_METHOD("getZEye", lua_cocos2d_Director_getZEye);
	LUA_METHOD("init", lua_cocos2d_Director_init);
	LUA_METHOD("isChildrenIndexerEnabled", lua_cocos2d_Director_isChildrenIndexerEnabled);
	LUA_METHOD("isNextDeltaTimeZero", lua_cocos2d_Director_isNextDeltaTimeZero);
	LUA_METHOD("isPaused", lua_cocos2d_Director_isPaused);
	LUA_METHOD("isSendCleanupToScene", lua_cocos2d_Director_isSendCleanupToScene);
	LUA_METHOD("isStatsDisplay", lua_cocos2d_Director_isStatsDisplay);
	LUA_METHOD("isValid", lua_cocos2d_Director_isValid);
	LUA_METHOD("loadIdentityMatrix", lua_cocos2d_Director_loadIdentityMatrix);
	LUA_METHOD("loadMatrix", lua_cocos2d_Director_loadMatrix);
	LUA_METHOD("mainLoop", lua_cocos2d_Director_mainLoop);
	LUA_METHOD("multiplyMatrix", lua_cocos2d_Director_multiplyMatrix);
	LUA_METHOD("pause", lua_cocos2d_Director_pause);
	LUA_METHOD("popMatrix", lua_cocos2d_Director_popMatrix);
	LUA_METHOD("popScene", lua_cocos2d_Director_popScene);
	LUA_METHOD("popToRootScene", lua_cocos2d_Director_popToRootScene);
	LUA_METHOD("popToSceneStackLevel", lua_cocos2d_Director_popToSceneStackLevel);
	LUA_METHOD("purgeCachedData", lua_cocos2d_Director_purgeCachedData);
	LUA_METHOD("pushMatrix", lua_cocos2d_Director_pushMatrix);
	LUA_METHOD("pushScene", lua_cocos2d_Director_pushScene);
	LUA_METHOD("replaceScene", lua_cocos2d_Director_replaceScene);
	LUA_METHOD("resetMatrixStack", lua_cocos2d_Director_resetMatrixStack);
	LUA_METHOD("restart", lua_cocos2d_Director_restart);
	LUA_METHOD("resume", lua_cocos2d_Director_resume);
	LUA_METHOD("runWithScene", lua_cocos2d_Director_runWithScene);
	LUA_METHOD("setActionManager", lua_cocos2d_Director_setActionManager);
	LUA_METHOD("setAnimationInterval", lua_cocos2d_Director_setAnimationInterval);
	LUA_METHOD("setChildrenIndexerEnabled", lua_cocos2d_Director_setChildrenIndexerEnabled);
	LUA_METHOD("setClearColor", lua_cocos2d_Director_setClearColor);
	LUA_METHOD("setContentScaleFactor", lua_cocos2d_Director_setContentScaleFactor);
	LUA_METHOD("setDefaultValues", lua_cocos2d_Director_setDefaultValues);
	LUA_METHOD("setEventDispatcher", lua_cocos2d_Director_setEventDispatcher);
	LUA_METHOD("setGLDefaultValues", lua_cocos2d_Director_setGLDefaultValues);
	LUA_METHOD("setNextDeltaTimeZero", lua_cocos2d_Director_setNextDeltaTimeZero);
	LUA_METHOD("setNotificationNode", lua_cocos2d_Director_setNotificationNode);
	LUA_METHOD("setOpenGLView", lua_cocos2d_Director_setOpenGLView);
	LUA_METHOD("setProjection", lua_cocos2d_Director_setProjection);
	LUA_METHOD("setScheduler", lua_cocos2d_Director_setScheduler);
	LUA_METHOD("setStatsAnchor", lua_cocos2d_Director_setStatsAnchor);
	LUA_METHOD("setStatsDisplay", lua_cocos2d_Director_setStatsDisplay);
	LUA_METHOD("setViewport", lua_cocos2d_Director_setViewport);
	LUA_METHOD("startAnimation", lua_cocos2d_Director_startAnimation);
	LUA_METHOD("stopAnimation", lua_cocos2d_Director_stopAnimation);
	LUA_METHOD("getInstance", lua_cocos2d_Director_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Timer_cancel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:cancel");
	LUA_TRY_INVOKE(0, &cocos2d::Timer::cancel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_isAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isAborted");
	LUA_TRY_INVOKE_R(0, &cocos2d::Timer::isAborted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_isExhausted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isExhausted");
	LUA_TRY_INVOKE_R(0, &cocos2d::Timer::isExhausted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_setAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setAborted");
	LUA_TRY_INVOKE(0, &cocos2d::Timer::setAborted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_setupTimerWithInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setupTimerWithInterval");
	LUA_TRY_INVOKE(3, &cocos2d::Timer::setupTimerWithInterval);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Timer_trigger(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:trigger");
	LUA_TRY_INVOKE(1, &cocos2d::Timer::trigger);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Timer_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:update");
	LUA_TRY_INVOKE(1, &cocos2d::Timer::update);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTimer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Timer, "Timer", "cc.Timer",
		cocos2d::Timer, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("cancel", lua_cocos2d_Timer_cancel);
	LUA_METHOD("isAborted", lua_cocos2d_Timer_isAborted);
	LUA_METHOD("isExhausted", lua_cocos2d_Timer_isExhausted);
	LUA_METHOD("setAborted", lua_cocos2d_Timer_setAborted);
	LUA_METHOD("setupTimerWithInterval", lua_cocos2d_Timer_setupTimerWithInterval);
	LUA_METHOD("trigger", lua_cocos2d_Timer_trigger);
	LUA_METHOD("update", lua_cocos2d_Timer_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Scheduler_getTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:getTimeScale");
	LUA_TRY_INVOKE_R(0, &cocos2d::Scheduler::getTimeScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scheduler_performFunctionInCocosThread(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:performFunctionInCocosThread");
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, &cocos2d::Scheduler::performFunctionInCocosThread);
	}
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scheduler_removeAllPendingActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:removeAllPendingActions");
	LUA_TRY_INVOKE(0, &cocos2d::Scheduler::removeAllPendingActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scheduler_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:setTimeScale");
	LUA_TRY_INVOKE(1, &cocos2d::Scheduler::setTimeScale);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccScheduler(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Scheduler, "Scheduler", "cc.Scheduler",
		cocos2d::Scheduler, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getTimeScale", lua_cocos2d_Scheduler_getTimeScale);
	LUA_METHOD("performFunctionInCocosThread", lua_cocos2d_Scheduler_performFunctionInCocosThread);
	LUA_METHOD("removeAllPendingActions", lua_cocos2d_Scheduler_removeAllPendingActions);
	LUA_METHOD("setTimeScale", lua_cocos2d_Scheduler_setTimeScale);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AsyncTaskPool_stopTasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AsyncTaskPool", "cc.AsyncTaskPool:stopTasks");
	LUA_TRY_INVOKE(1, &cocos2d::AsyncTaskPool::stopTasks);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AsyncTaskPool_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AsyncTaskPool", "cc.AsyncTaskPool:getInstance");
	LUA_TRY_INVOKE_R(0, &cocos2d::AsyncTaskPool::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccAsyncTaskPool(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AsyncTaskPool, "AsyncTaskPool", "cc.AsyncTaskPool",
		cocos2d::AsyncTaskPool, "",
		nullptr, nullptr);
	LUA_METHOD("stopTasks", lua_cocos2d_AsyncTaskPool_stopTasks);
	LUA_METHOD("getInstance", lua_cocos2d_AsyncTaskPool_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Action_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getFlags");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::getFlags);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getOriginalTarget");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::getOriginalTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTag");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::getTag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTarget");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::getTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_isDone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:isDone");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::isDone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_reverse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:reverse");
	LUA_TRY_INVOKE_R(0, &cocos2d::Action::reverse);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_setFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setFlags");
	LUA_TRY_INVOKE(1, &cocos2d::Action::setFlags);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setOriginalTarget");
	LUA_TRY_INVOKE(1, &cocos2d::Action::setOriginalTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTag");
	LUA_TRY_INVOKE(1, &cocos2d::Action::setTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTarget");
	LUA_TRY_INVOKE(1, &cocos2d::Action::setTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_startWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:startWithTarget");
	LUA_TRY_INVOKE(1, &cocos2d::Action::startWithTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_step(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:step");
	LUA_TRY_INVOKE(1, &cocos2d::Action::step);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:stop");
	LUA_TRY_INVOKE(0, &cocos2d::Action::stop);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:update");
	LUA_TRY_INVOKE(1, &cocos2d::Action::update);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Action, "Action", "cc.Action",
		cocos2d::Action, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_Action_clone);
	LUA_METHOD("getFlags", lua_cocos2d_Action_getFlags);
	LUA_METHOD("getOriginalTarget", lua_cocos2d_Action_getOriginalTarget);
	LUA_METHOD("getTag", lua_cocos2d_Action_getTag);
	LUA_METHOD("getTarget", lua_cocos2d_Action_getTarget);
	LUA_METHOD("isDone", lua_cocos2d_Action_isDone);
	LUA_METHOD("reverse", lua_cocos2d_Action_reverse);
	LUA_METHOD("setFlags", lua_cocos2d_Action_setFlags);
	LUA_METHOD("setOriginalTarget", lua_cocos2d_Action_setOriginalTarget);
	LUA_METHOD("setTag", lua_cocos2d_Action_setTag);
	LUA_METHOD("setTarget", lua_cocos2d_Action_setTarget);
	LUA_METHOD("startWithTarget", lua_cocos2d_Action_startWithTarget);
	LUA_METHOD("step", lua_cocos2d_Action_step);
	LUA_METHOD("stop", lua_cocos2d_Action_stop);
	LUA_METHOD("update", lua_cocos2d_Action_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FiniteTimeAction_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FiniteTimeAction", "cc.FiniteTimeAction:getDuration");
	LUA_TRY_INVOKE_R(0, &cocos2d::FiniteTimeAction::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FiniteTimeAction_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FiniteTimeAction", "cc.FiniteTimeAction:setDuration");
	LUA_TRY_INVOKE(1, &cocos2d::FiniteTimeAction::setDuration);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccFiniteTimeAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FiniteTimeAction, "FiniteTimeAction", "cc.FiniteTimeAction",
		cocos2d::FiniteTimeAction, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("getDuration", lua_cocos2d_FiniteTimeAction_getDuration);
	LUA_METHOD("setDuration", lua_cocos2d_FiniteTimeAction_setDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Speed_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cocos2d::Speed::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Speed_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getSpeed");
	LUA_TRY_INVOKE_R(0, &cocos2d::Speed::getSpeed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Speed_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:initWithAction");
	LUA_TRY_INVOKE_R(2, &cocos2d::Speed::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Speed_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setInnerAction");
	LUA_TRY_INVOKE(1, &cocos2d::Speed::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Speed_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setSpeed");
	LUA_TRY_INVOKE(1, &cocos2d::Speed::setSpeed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Speed_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Speed", "cc.Speed:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::Speed::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSpeed(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Speed, "Speed", "cc.Speed",
		cocos2d::Speed, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_Speed_getInnerAction);
	LUA_METHOD("getSpeed", lua_cocos2d_Speed_getSpeed);
	LUA_METHOD("initWithAction", lua_cocos2d_Speed_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_Speed_setInnerAction);
	LUA_METHOD("setSpeed", lua_cocos2d_Speed_setSpeed);
	LUA_METHOD("create", lua_cocos2d_Speed_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Follow_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTarget");
	LUA_TRY_INVOKE_R(2, &cocos2d::Follow::initWithTarget);
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Follow* obj,cocos2d::Node* arg0){{return obj->initWithTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Follow_initWithTargetAndOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTargetAndOffset");
	LUA_TRY_INVOKE_R(4, &cocos2d::Follow::initWithTargetAndOffset);
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Follow* obj,cocos2d::Node* arg0,float arg1,float arg2){{return obj->initWithTargetAndOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4");
}
int lua_cocos2d_Follow_isBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:isBoundarySet");
	LUA_TRY_INVOKE_R(0, &cocos2d::Follow::isBoundarySet);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Follow_setBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:setBoundarySet");
	LUA_TRY_INVOKE(1, &cocos2d::Follow::setBoundarySet);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Follow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::Follow::create);
	LUA_TRY_INVOKE_R(1, [](cocos2d::Node* arg0){{return cocos2d::Follow::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_Follow_createWithOffset(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:createWithOffset");
	LUA_TRY_INVOKE_R(4, &cocos2d::Follow::createWithOffset);
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Node* arg0,float arg1,float arg2){{return cocos2d::Follow::createWithOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int luaReg_Core_ccFollow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Follow, "Follow", "cc.Follow",
		cocos2d::Follow, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("initWithTarget", lua_cocos2d_Follow_initWithTarget);
	LUA_METHOD("initWithTargetAndOffset", lua_cocos2d_Follow_initWithTargetAndOffset);
	LUA_METHOD("isBoundarySet", lua_cocos2d_Follow_isBoundarySet);
	LUA_METHOD("setBoundarySet", lua_cocos2d_Follow_setBoundarySet);
	LUA_METHOD("create", lua_cocos2d_Follow_create);
	LUA_METHOD("createWithOffset", lua_cocos2d_Follow_createWithOffset);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Image_getBitPerPixel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getBitPerPixel");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getBitPerPixel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFilePath");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getFilePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getFileType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFileType");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getFileType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getHeight");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getNumberOfMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getNumberOfMipmaps");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getNumberOfMipmaps);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getPixelFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getPixelFormat");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getPixelFormat);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getWidth");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::getWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_hasAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasAlpha");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::hasAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_hasPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasPremultipliedAlpha");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::hasPremultipliedAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_initWithImageFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:initWithImageFile");
	LUA_TRY_INVOKE_R(1, &cocos2d::Image::initWithImageFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Image_isCompressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:isCompressed");
	LUA_TRY_INVOKE_R(0, &cocos2d::Image::isCompressed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_premultiplyAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:premultiplyAlpha");
	LUA_TRY_INVOKE(0, &cocos2d::Image::premultiplyAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_reversePremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:reversePremultipliedAlpha");
	LUA_TRY_INVOKE(0, &cocos2d::Image::reversePremultipliedAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_saveToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:saveToFile");
	LUA_TRY_INVOKE_R(2, &cocos2d::Image::saveToFile);
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Image* obj,std::string_view arg0){{return obj->saveToFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Image_isCompressedImageHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:isCompressedImageHavePMA");
	LUA_TRY_INVOKE_R(1, &cocos2d::Image::isCompressedImageHavePMA);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Image_setCompressedImagesHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setCompressedImagesHavePMA");
	LUA_TRY_INVOKE(2, &cocos2d::Image::setCompressedImagesHavePMA);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Image_setPNGPremultipliedAlphaEnabled(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setPNGPremultipliedAlphaEnabled");
	LUA_TRY_INVOKE(1, &cocos2d::Image::setPNGPremultipliedAlphaEnabled);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Image, "Image", "cc.Image",
		cocos2d::Image, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBitPerPixel", lua_cocos2d_Image_getBitPerPixel);
	LUA_METHOD("getFilePath", lua_cocos2d_Image_getFilePath);
	LUA_METHOD("getFileType", lua_cocos2d_Image_getFileType);
	LUA_METHOD("getHeight", lua_cocos2d_Image_getHeight);
	LUA_METHOD("getNumberOfMipmaps", lua_cocos2d_Image_getNumberOfMipmaps);
	LUA_METHOD("getPixelFormat", lua_cocos2d_Image_getPixelFormat);
	LUA_METHOD("getWidth", lua_cocos2d_Image_getWidth);
	LUA_METHOD("hasAlpha", lua_cocos2d_Image_hasAlpha);
	LUA_METHOD("hasPremultipliedAlpha", lua_cocos2d_Image_hasPremultipliedAlpha);
	LUA_METHOD("initWithImageFile", lua_cocos2d_Image_initWithImageFile);
	LUA_METHOD("isCompressed", lua_cocos2d_Image_isCompressed);
	LUA_METHOD("premultiplyAlpha", lua_cocos2d_Image_premultiplyAlpha);
	LUA_METHOD("reversePremultipliedAlpha", lua_cocos2d_Image_reversePremultipliedAlpha);
	LUA_METHOD("saveToFile", lua_cocos2d_Image_saveToFile);
	LUA_METHOD("isCompressedImageHavePMA", lua_cocos2d_Image_isCompressedImageHavePMA);
	LUA_METHOD("setCompressedImagesHavePMA", lua_cocos2d_Image_setCompressedImagesHavePMA);
	LUA_METHOD("setPNGPremultipliedAlphaEnabled", lua_cocos2d_Image_setPNGPremultipliedAlphaEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getCenterRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getCenterRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffset");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffsetInPixels");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getOffsetInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSize");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getOriginalSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSizeInPixels");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getOriginalSizeInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRectInPixels");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getRectInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getTexture");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::hasAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasCenterRect");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::hasCenterRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::initWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::initWithTexture)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_initWithTextureFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTextureFilename");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::SpriteFrame::*)(std::string_view, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::initWithTextureFilename)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteFrame::*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::initWithTextureFilename)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_isRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:isRotated");
	LUA_TRY_INVOKE_R(0, &cocos2d::SpriteFrame::isRotated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setAnchorPoint");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setAnchorPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setCenterRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setCenterRectInPixels");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setCenterRectInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffset");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setOffset);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffsetInPixels");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setOffsetInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSize");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setOriginalSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSizeInPixels");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setOriginalSizeInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRect");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRectInPixels");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setRectInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRotated");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setRotated);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setTexture");
	LUA_TRY_INVOKE(1, &cocos2d::SpriteFrame::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cocos2d::SpriteFrame>(*)(std::string_view, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::SpriteFrame>(*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::create)));
	LUA_SINVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:createWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cocos2d::SpriteFrame>(*)(cocos2d::Texture2D*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::createWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::SpriteFrame>(*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::createWithTexture)));
	LUA_SINVOKE_FOOTER("2,5");
}
int luaReg_Core_ccSpriteFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteFrame, "SpriteFrame", "cc.SpriteFrame",
		cocos2d::SpriteFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_SpriteFrame_clone);
	LUA_METHOD("getAnchorPoint", lua_cocos2d_SpriteFrame_getAnchorPoint);
	LUA_METHOD("getCenterRect", lua_cocos2d_SpriteFrame_getCenterRect);
	LUA_METHOD("getOffset", lua_cocos2d_SpriteFrame_getOffset);
	LUA_METHOD("getOffsetInPixels", lua_cocos2d_SpriteFrame_getOffsetInPixels);
	LUA_METHOD("getOriginalSize", lua_cocos2d_SpriteFrame_getOriginalSize);
	LUA_METHOD("getOriginalSizeInPixels", lua_cocos2d_SpriteFrame_getOriginalSizeInPixels);
	LUA_METHOD("getRect", lua_cocos2d_SpriteFrame_getRect);
	LUA_METHOD("getRectInPixels", lua_cocos2d_SpriteFrame_getRectInPixels);
	LUA_METHOD("getTexture", lua_cocos2d_SpriteFrame_getTexture);
	LUA_METHOD("hasAnchorPoint", lua_cocos2d_SpriteFrame_hasAnchorPoint);
	LUA_METHOD("hasCenterRect", lua_cocos2d_SpriteFrame_hasCenterRect);
	LUA_METHOD("initWithTexture", lua_cocos2d_SpriteFrame_initWithTexture);
	LUA_METHOD("initWithTextureFilename", lua_cocos2d_SpriteFrame_initWithTextureFilename);
	LUA_METHOD("isRotated", lua_cocos2d_SpriteFrame_isRotated);
	LUA_METHOD("setAnchorPoint", lua_cocos2d_SpriteFrame_setAnchorPoint);
	LUA_METHOD("setCenterRectInPixels", lua_cocos2d_SpriteFrame_setCenterRectInPixels);
	LUA_METHOD("setOffset", lua_cocos2d_SpriteFrame_setOffset);
	LUA_METHOD("setOffsetInPixels", lua_cocos2d_SpriteFrame_setOffsetInPixels);
	LUA_METHOD("setOriginalSize", lua_cocos2d_SpriteFrame_setOriginalSize);
	LUA_METHOD("setOriginalSizeInPixels", lua_cocos2d_SpriteFrame_setOriginalSizeInPixels);
	LUA_METHOD("setRect", lua_cocos2d_SpriteFrame_setRect);
	LUA_METHOD("setRectInPixels", lua_cocos2d_SpriteFrame_setRectInPixels);
	LUA_METHOD("setRotated", lua_cocos2d_SpriteFrame_setRotated);
	LUA_METHOD("setTexture", lua_cocos2d_SpriteFrame_setTexture);
	LUA_METHOD("create", lua_cocos2d_SpriteFrame_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_SpriteFrame_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AnimationFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::AnimationFrame::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getDelayUnits");
	LUA_TRY_INVOKE_R(0, &cocos2d::AnimationFrame::getDelayUnits);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, &cocos2d::AnimationFrame::getSpriteFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getUserInfo");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(3, &cocos2d::AnimationFrame::initWithSpriteFrame);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_AnimationFrame_setDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setDelayUnits");
	LUA_TRY_INVOKE(1, &cocos2d::AnimationFrame::setDelayUnits);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setSpriteFrame");
	LUA_TRY_INVOKE(1, &cocos2d::AnimationFrame::setSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setUserInfo");
	LUA_TRY_INVOKE(1, &cocos2d::AnimationFrame::setUserInfo);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:create");
	LUA_TRY_INVOKE_R(3, &cocos2d::AnimationFrame::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccAnimationFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationFrame, "AnimationFrame", "cc.AnimationFrame",
		cocos2d::AnimationFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_AnimationFrame_clone);
	LUA_METHOD("getDelayUnits", lua_cocos2d_AnimationFrame_getDelayUnits);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_AnimationFrame_getSpriteFrame);
	LUA_METHOD("getUserInfo", lua_cocos2d_AnimationFrame_getUserInfo);
	LUA_METHOD("initWithSpriteFrame", lua_cocos2d_AnimationFrame_initWithSpriteFrame);
	LUA_METHOD("setDelayUnits", lua_cocos2d_AnimationFrame_setDelayUnits);
	LUA_METHOD("setSpriteFrame", lua_cocos2d_AnimationFrame_setSpriteFrame);
	LUA_METHOD("setUserInfo", lua_cocos2d_AnimationFrame_setUserInfo);
	LUA_METHOD("create", lua_cocos2d_AnimationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animation_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrame");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::addSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithFile");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::addSpriteFrameWithFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithTexture");
	LUA_TRY_INVOKE(2, &cocos2d::Animation::addSpriteFrameWithTexture);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animation_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:clone");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDelayPerUnit");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getDelayPerUnit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDuration");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getFrames");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getLoops");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getLoops);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getRestoreOriginalFrame");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getRestoreOriginalFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getTotalDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getTotalDelayUnits");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::getTotalDelayUnits);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:init");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animation::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_initWithAnimationFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithAnimationFrames");
	LUA_TRY_INVOKE_R(3, &cocos2d::Animation::initWithAnimationFrames);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Animation_initWithSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, &cocos2d::Animation::initWithSpriteFrames);
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return obj->initWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return obj->initWithSpriteFrames(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_Animation_setDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setDelayPerUnit");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::setDelayPerUnit);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setFrames");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::setFrames);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setLoops");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::setLoops);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setRestoreOriginalFrame");
	LUA_TRY_INVOKE(1, &cocos2d::Animation::setRestoreOriginalFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::Animation>(*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&, float, unsigned int)>(&cocos2d::Animation::create)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::AnimationFrame *>& arg0,float arg1){{return cocos2d::Animation::create(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cocos2d::Animation>(*)()>(&cocos2d::Animation::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cocos2d_Animation_createWithSpriteFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:createWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, &cocos2d::Animation::createWithSpriteFrames);
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return cocos2d::Animation::createWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return cocos2d::Animation::createWithSpriteFrames(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Core_ccAnimation(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation, "Animation", "cc.Animation",
		cocos2d::Animation, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_Animation_addSpriteFrame);
	LUA_METHOD("addSpriteFrameWithFile", lua_cocos2d_Animation_addSpriteFrameWithFile);
	LUA_METHOD("addSpriteFrameWithTexture", lua_cocos2d_Animation_addSpriteFrameWithTexture);
	LUA_METHOD("clone", lua_cocos2d_Animation_clone);
	LUA_METHOD("getDelayPerUnit", lua_cocos2d_Animation_getDelayPerUnit);
	LUA_METHOD("getDuration", lua_cocos2d_Animation_getDuration);
	LUA_METHOD("getFrames", lua_cocos2d_Animation_getFrames);
	LUA_METHOD("getLoops", lua_cocos2d_Animation_getLoops);
	LUA_METHOD("getRestoreOriginalFrame", lua_cocos2d_Animation_getRestoreOriginalFrame);
	LUA_METHOD("getTotalDelayUnits", lua_cocos2d_Animation_getTotalDelayUnits);
	LUA_METHOD("init", lua_cocos2d_Animation_init);
	LUA_METHOD("initWithAnimationFrames", lua_cocos2d_Animation_initWithAnimationFrames);
	LUA_METHOD("initWithSpriteFrames", lua_cocos2d_Animation_initWithSpriteFrames);
	LUA_METHOD("setDelayPerUnit", lua_cocos2d_Animation_setDelayPerUnit);
	LUA_METHOD("setFrames", lua_cocos2d_Animation_setFrames);
	LUA_METHOD("setLoops", lua_cocos2d_Animation_setLoops);
	LUA_METHOD("setRestoreOriginalFrame", lua_cocos2d_Animation_setRestoreOriginalFrame);
	LUA_METHOD("create", lua_cocos2d_Animation_create);
	LUA_METHOD("createWithSpriteFrames", lua_cocos2d_Animation_createWithSpriteFrames);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionInterval_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionInterval::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_getElapsed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getElapsed");
	LUA_TRY_INVOKE_R(0, &cocos2d::ActionInterval::getElapsed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:initWithDuration");
	LUA_TRY_INVOKE_R(1, &cocos2d::ActionInterval::initWithDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionInterval_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cocos2d::ActionInterval::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionInterval(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionInterval, "ActionInterval", "cc.ActionInterval",
		cocos2d::ActionInterval, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_ActionInterval_getAmplitudeRate);
	LUA_METHOD("getElapsed", lua_cocos2d_ActionInterval_getElapsed);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionInterval_initWithDuration);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_ActionInterval_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Sequence_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:init");
	LUA_TRY_INVOKE_R(1, &cocos2d::Sequence::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sequence_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, &cocos2d::Sequence::initWithTwoActions);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSequence(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Sequence, "Sequence", "cc.Sequence",
		cocos2d::Sequence, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Sequence_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Sequence_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Repeat_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cocos2d::Repeat::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Repeat_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:initWithAction");
	LUA_TRY_INVOKE_R(2, &cocos2d::Repeat::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Repeat_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:setInnerAction");
	LUA_TRY_INVOKE(1, &cocos2d::Repeat::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Repeat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Repeat", "cc.Repeat:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::Repeat::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccRepeat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Repeat, "Repeat", "cc.Repeat",
		cocos2d::Repeat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_Repeat_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_Repeat_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_Repeat_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_Repeat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RepeatForever_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cocos2d::RepeatForever::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RepeatForever_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:initWithAction");
	LUA_TRY_INVOKE_R(1, &cocos2d::RepeatForever::initWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:setInnerAction");
	LUA_TRY_INVOKE(1, &cocos2d::RepeatForever::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::RepeatForever::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccRepeatForever(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RepeatForever, "RepeatForever", "cc.RepeatForever",
		cocos2d::RepeatForever, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_RepeatForever_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_RepeatForever_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_RepeatForever_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_RepeatForever_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Spawn_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:init");
	LUA_TRY_INVOKE_R(1, &cocos2d::Spawn::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Spawn_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, &cocos2d::Spawn::initWithTwoActions);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSpawn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Spawn, "Spawn", "cc.Spawn",
		cocos2d::Spawn, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Spawn_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Spawn_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateTo", "cc.RotateTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateTo::*)(float, float, float)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::RotateTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateTo", "cc.RotateTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::RotateTo>(*)(float, float, float)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::RotateTo>(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::RotateTo>(*)(float, float)>(&cocos2d::RotateTo::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateTo, "RotateTo", "cc.RotateTo",
		cocos2d::RotateTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateBy", "cc.RotateBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateBy::*)(float, float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateBy", "cc.RotateBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::RotateBy>(*)(float, float, float)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::RotateBy>(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::RotateBy>(*)(float, float)>(&cocos2d::RotateBy::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateBy, "RotateBy", "cc.RotateBy",
		cocos2d::RotateBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveBy", "cc.MoveBy:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveBy", "cc.MoveBy:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::MoveBy>(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::MoveBy>(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveBy, "MoveBy", "cc.MoveBy",
		cocos2d::MoveBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveTo", "cc.MoveTo:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveTo", "cc.MoveTo:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::MoveTo>(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cocos2d::MoveTo>(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveTo, "MoveTo", "cc.MoveTo",
		cocos2d::MoveTo, "cc.MoveBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SkewTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewTo", "cc.SkewTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cocos2d::SkewTo::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewTo", "cc.SkewTo:create");
	LUA_TRY_INVOKE_R(3, &cocos2d::SkewTo::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewTo, "SkewTo", "cc.SkewTo",
		cocos2d::SkewTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SkewBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewBy", "cc.SkewBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cocos2d::SkewBy::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewBy", "cc.SkewBy:create");
	LUA_TRY_INVOKE_R(3, &cocos2d::SkewBy::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewBy, "SkewBy", "cc.SkewBy",
		cocos2d::SkewBy, "cc.SkewTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpBy", "cc.JumpBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::JumpBy::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpBy", "cc.JumpBy:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::JumpBy::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpBy, "JumpBy", "cc.JumpBy",
		cocos2d::JumpBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTo", "cc.JumpTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::JumpTo::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTo", "cc.JumpTo:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::JumpTo::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpTo, "JumpTo", "cc.JumpTo",
		cocos2d::JumpTo, "cc.JumpBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_BezierBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierBy", "cc.BezierBy:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::BezierBy::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_BezierBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierBy", "cc.BezierBy:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::BezierBy::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierBy, "BezierBy", "cc.BezierBy",
		cocos2d::BezierBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_BezierBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_BezierBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_BezierTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierTo", "cc.BezierTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::BezierTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_BezierTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierTo", "cc.BezierTo:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::BezierTo::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierTo, "BezierTo", "cc.BezierTo",
		cocos2d::BezierTo, "cc.BezierBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_BezierTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_BezierTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ScaleTo::*)(float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ScaleTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cocos2d::ScaleTo>(*)(float, float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ScaleTo>(*)(float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::ScaleTo>(*)(float, float)>(&cocos2d::ScaleTo::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleTo, "ScaleTo", "cc.ScaleTo",
		cocos2d::ScaleTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ScaleTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ScaleTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleBy", "cc.ScaleBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cocos2d::ScaleBy>(*)(float, float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cocos2d::ScaleBy>(*)(float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::ScaleBy>(*)(float, float)>(&cocos2d::ScaleBy::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleBy, "ScaleBy", "cc.ScaleBy",
		cocos2d::ScaleBy, "cc.ScaleTo",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ScaleBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Blink_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Blink", "cc.Blink:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::Blink::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Blink_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Blink", "cc.Blink:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::Blink::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBlink(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Blink, "Blink", "cc.Blink",
		cocos2d::Blink, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_Blink_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_Blink_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeTo", "cc.FadeTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cocos2d::FadeTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FadeTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeTo", "cc.FadeTo:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::FadeTo::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeTo, "FadeTo", "cc.FadeTo",
		cocos2d::FadeTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_FadeTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_FadeTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeIn_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeIn", "cc.FadeIn:setReverseAction");
	LUA_TRY_INVOKE(1, &cocos2d::FadeIn::setReverseAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeIn", "cc.FadeIn:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FadeIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeIn, "FadeIn", "cc.FadeIn",
		cocos2d::FadeIn, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeIn_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOut_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOut", "cc.FadeOut:setReverseAction");
	LUA_TRY_INVOKE(1, &cocos2d::FadeOut::setReverseAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOut", "cc.FadeOut:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::FadeOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOut, "FadeOut", "cc.FadeOut",
		cocos2d::FadeOut, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeOut_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TintTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintTo", "cc.TintTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::TintTo::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintTo", "cc.TintTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cocos2d::TintTo>(*)(float, uint8_t, uint8_t, uint8_t)>(&cocos2d::TintTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cocos2d::TintTo>(*)(float, const cocos2d::Color3B&)>(&cocos2d::TintTo::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Core_ccTintTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintTo, "TintTo", "cc.TintTo",
		cocos2d::TintTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TintBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintBy", "cc.TintBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cocos2d::TintBy::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintBy", "cc.TintBy:create");
	LUA_TRY_INVOKE_R(4, &cocos2d::TintBy::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTintBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintBy, "TintBy", "cc.TintBy",
		cocos2d::TintBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_DelayTime_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DelayTime", "cc.DelayTime:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::DelayTime::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDelayTime(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DelayTime, "DelayTime", "cc.DelayTime",
		cocos2d::DelayTime, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_DelayTime_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animate_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getAnimation");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Animation*(cocos2d::Animate::*)()const>(&cocos2d::Animate::getAnimation));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Animation*(cocos2d::Animate::*)()>(&cocos2d::Animate::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate_getCurrentFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getCurrentFrameIndex");
	LUA_TRY_INVOKE_R(0, &cocos2d::Animate::getCurrentFrameIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate_initWithAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:initWithAnimation");
	LUA_TRY_INVOKE_R(1, &cocos2d::Animate::initWithAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:setAnimation");
	LUA_TRY_INVOKE(1, &cocos2d::Animate::setAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate", "cc.Animate:create");
	LUA_TRY_INVOKE_R(1, &cocos2d::Animate::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAnimate(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animate, "Animate", "cc.Animate",
		cocos2d::Animate, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocos2d_Animate_getAnimation);
	LUA_METHOD("getCurrentFrameIndex", lua_cocos2d_Animate_getCurrentFrameIndex);
	LUA_METHOD("initWithAnimation", lua_cocos2d_Animate_initWithAnimation);
	LUA_METHOD("setAnimation", lua_cocos2d_Animate_setAnimation);
	LUA_METHOD("create", lua_cocos2d_Animate_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TargetedAction_getForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:getForcedTarget");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Node*(cocos2d::TargetedAction::*)()const>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Node*(cocos2d::TargetedAction::*)()>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TargetedAction_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:initWithTarget");
	LUA_TRY_INVOKE_R(2, &cocos2d::TargetedAction::initWithTarget);
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TargetedAction_setForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:setForcedTarget");
	LUA_TRY_INVOKE(1, &cocos2d::TargetedAction::setForcedTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TargetedAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:create");
	LUA_TRY_INVOKE_R(2, &cocos2d::TargetedAction::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTargetedAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TargetedAction, "TargetedAction", "cc.TargetedAction",
		cocos2d::TargetedAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getForcedTarget", lua_cocos2d_TargetedAction_getForcedTarget);
	LUA_METHOD("initWithTarget", lua_cocos2d_TargetedAction_initWithTarget);
	LUA_METHOD("setForcedTarget", lua_cocos2d_TargetedAction_setForcedTarget);
	LUA_METHOD("create", lua_cocos2d_TargetedAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
