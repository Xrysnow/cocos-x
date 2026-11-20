#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/ProtectedNode.h"
#include "base/AsyncTaskPool.h"
#include "scripting/lua-bindings/manual/ComponentLua.h"
#include "renderer/Renderer.h"
#include "renderer/PipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/Physics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/NavMesh.h"
#endif

int lua_cc_GLView_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:endToLua");
	LUA_TRY_INVOKE(0, &cc::GLView::end);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getAllTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getAllTouches");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getAllTouches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getContentScaleFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getDesignResolutionSize");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getDesignResolutionSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameSize");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getFrameSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameZoomFactor");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getFrameZoomFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getResolutionPolicy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getResolutionPolicy");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getResolutionPolicy);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getRetinaFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getRetinaFactor");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getRetinaFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getSafeAreaRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleX");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getScaleX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleY");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getScaleY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScissorRect");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getScissorRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewName");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getViewName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getViewPortRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewPortRect");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getViewPortRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getVisibleOrigin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getVisibleRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleRect");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getVisibleRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleSize");
	LUA_TRY_INVOKE_R(0, &cc::GLView::getVisibleSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_isOpenGLReady(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isOpenGLReady");
	LUA_TRY_INVOKE_R(0, &cc::GLView::isOpenGLReady);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_isRetinaDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isRetinaDisplay");
	LUA_TRY_INVOKE_R(0, &cc::GLView::isRetinaDisplay);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_isScissorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isScissorEnabled");
	LUA_TRY_INVOKE_R(0, &cc::GLView::isScissorEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_pollEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:pollEvents");
	LUA_TRY_INVOKE(0, &cc::GLView::pollEvents);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_renderScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:renderScene");
	LUA_TRY_INVOKE(2, &cc::GLView::renderScene);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_GLView_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setContentScaleFactor");
	LUA_TRY_INVOKE_R(1, &cc::GLView::setContentScaleFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GLView_setCursorVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setCursorVisible");
	LUA_TRY_INVOKE(1, &cc::GLView::setCursorVisible);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GLView_setDefaultIcon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDefaultIcon");
	LUA_TRY_INVOKE(0, &cc::GLView::setDefaultIcon);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_setDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDesignResolutionSize");
	LUA_TRY_INVOKE(3, &cc::GLView::setDesignResolutionSize);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_GLView_setFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameSize");
	LUA_TRY_INVOKE(2, &cc::GLView::setFrameSize);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_GLView_setFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameZoomFactor");
	LUA_TRY_INVOKE(1, &cc::GLView::setFrameZoomFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GLView_setIcon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setIcon");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::GLView::*)(const std::vector<std::string_view>&)const>(&cc::GLView::setIcon));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::GLView::*)(std::string_view)const>(&cc::GLView::setIcon));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GLView_setScissorInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setScissorInPoints");
	LUA_TRY_INVOKE(4, &cc::GLView::setScissorInPoints);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_GLView_setViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewName");
	LUA_TRY_INVOKE(1, &cc::GLView::setViewName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_GLView_setViewPortInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewPortInPoints");
	LUA_TRY_INVOKE(4, &cc::GLView::setViewPortInPoints);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_GLView_swapBuffers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:swapBuffers");
	LUA_TRY_INVOKE(0, &cc::GLView::swapBuffers);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_GLView_windowShouldClose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:windowShouldClose");
	LUA_TRY_INVOKE_R(0, &cc::GLView::windowShouldClose);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGLView(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::GLView, "GLView", "cc.GLView",
		cc::GLView, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("endToLua", lua_cc_GLView_endToLua);
	LUA_METHOD("getAllTouches", lua_cc_GLView_getAllTouches);
	LUA_METHOD("getContentScaleFactor", lua_cc_GLView_getContentScaleFactor);
	LUA_METHOD("getDesignResolutionSize", lua_cc_GLView_getDesignResolutionSize);
	LUA_METHOD("getFrameSize", lua_cc_GLView_getFrameSize);
	LUA_METHOD("getFrameZoomFactor", lua_cc_GLView_getFrameZoomFactor);
	LUA_METHOD("getResolutionPolicy", lua_cc_GLView_getResolutionPolicy);
	LUA_METHOD("getRetinaFactor", lua_cc_GLView_getRetinaFactor);
	LUA_METHOD("getSafeAreaRect", lua_cc_GLView_getSafeAreaRect);
	LUA_METHOD("getScaleX", lua_cc_GLView_getScaleX);
	LUA_METHOD("getScaleY", lua_cc_GLView_getScaleY);
	LUA_METHOD("getScissorRect", lua_cc_GLView_getScissorRect);
	LUA_METHOD("getViewName", lua_cc_GLView_getViewName);
	LUA_METHOD("getViewPortRect", lua_cc_GLView_getViewPortRect);
	LUA_METHOD("getVisibleOrigin", lua_cc_GLView_getVisibleOrigin);
	LUA_METHOD("getVisibleRect", lua_cc_GLView_getVisibleRect);
	LUA_METHOD("getVisibleSize", lua_cc_GLView_getVisibleSize);
	LUA_METHOD("isOpenGLReady", lua_cc_GLView_isOpenGLReady);
	LUA_METHOD("isRetinaDisplay", lua_cc_GLView_isRetinaDisplay);
	LUA_METHOD("isScissorEnabled", lua_cc_GLView_isScissorEnabled);
	LUA_METHOD("pollEvents", lua_cc_GLView_pollEvents);
	LUA_METHOD("renderScene", lua_cc_GLView_renderScene);
	LUA_METHOD("setContentScaleFactor", lua_cc_GLView_setContentScaleFactor);
	LUA_METHOD("setCursorVisible", lua_cc_GLView_setCursorVisible);
	LUA_METHOD("setDefaultIcon", lua_cc_GLView_setDefaultIcon);
	LUA_METHOD("setDesignResolutionSize", lua_cc_GLView_setDesignResolutionSize);
	LUA_METHOD("setFrameSize", lua_cc_GLView_setFrameSize);
	LUA_METHOD("setFrameZoomFactor", lua_cc_GLView_setFrameZoomFactor);

	LUA_METHOD("setIcon", lua_cc_GLView_setIcon);
	LUA_METHOD("setScissorInPoints", lua_cc_GLView_setScissorInPoints);
	LUA_METHOD("setViewName", lua_cc_GLView_setViewName);
	LUA_METHOD("setViewPortInPoints", lua_cc_GLView_setViewPortInPoints);
	LUA_METHOD("swapBuffers", lua_cc_GLView_swapBuffers);
	LUA_METHOD("windowShouldClose", lua_cc_GLView_windowShouldClose);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Director_convertToGL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:convertToGL");
	LUA_TRY_INVOKE_R(1, &cc::Director::convertToGL);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_convertToUI(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:convertToUI");
	LUA_TRY_INVOKE_R(1, &cc::Director::convertToUI);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_drawScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:drawScene");
	LUA_TRY_INVOKE(0, &cc::Director::drawScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:endToLua");
	LUA_TRY_INVOKE(0, &cc::Director::end);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getActionManager");
	LUA_TRY_INVOKE_R(0, &cc::Director::getActionManager);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAnimationInterval");
	LUA_TRY_INVOKE_R(0, &cc::Director::getAnimationInterval);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getAxmolThreadId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAxmolThreadId");
	LUA_TRY_INVOKE_R(0, &cc::Director::getCocos2dThreadId);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getConsole(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getConsole");
	LUA_TRY_INVOKE_R(0, &cc::Director::getConsole);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, &cc::Director::getContentScaleFactor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getDeltaTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getDeltaTime");
	LUA_TRY_INVOKE_R(0, &cc::Director::getDeltaTime);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getEventDispatcher");
	LUA_TRY_INVOKE_R(0, &cc::Director::getEventDispatcher);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getFrameRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getFrameRate");
	LUA_TRY_INVOKE_R(0, &cc::Director::getFrameRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getMatrix");
	LUA_TRY_INVOKE_R(1, &cc::Director::getMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_getNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getNotificationNode");
	LUA_TRY_INVOKE_R(0, &cc::Director::getNotificationNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getOpenGLView");
	LUA_TRY_INVOKE_R(0, &cc::Director::getOpenGLView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRenderer");
	LUA_TRY_INVOKE_R(0, &cc::Director::getRenderer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getRunningScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRunningScene");
	LUA_TRY_INVOKE_R(0, &cc::Director::getRunningScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, &cc::Director::getSafeAreaRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getScheduler");
	LUA_TRY_INVOKE_R(0, &cc::Director::getScheduler);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getSecondsPerFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSecondsPerFrame");
	LUA_TRY_INVOKE_R(0, &cc::Director::getSecondsPerFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getTextureCache(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTextureCache");
	LUA_TRY_INVOKE_R(0, &cc::Director::getTextureCache);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getTotalFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTotalFrames");
	LUA_TRY_INVOKE_R(0, &cc::Director::getTotalFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, &cc::Director::getVisibleOrigin);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleSize");
	LUA_TRY_INVOKE_R(0, &cc::Director::getVisibleSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getWinSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSize");
	LUA_TRY_INVOKE_R(0, &cc::Director::getWinSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getWinSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSizeInPixels");
	LUA_TRY_INVOKE_R(0, &cc::Director::getWinSizeInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getZEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getZEye");
	LUA_TRY_INVOKE_R(0, &cc::Director::getZEye);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:init");
	LUA_TRY_INVOKE_R(0, &cc::Director::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isChildrenIndexerEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isChildrenIndexerEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Director::isChildrenIndexerEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isNextDeltaTimeZero");
	LUA_TRY_INVOKE_R(0, &cc::Director::isNextDeltaTimeZero);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isPaused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isPaused");
	LUA_TRY_INVOKE_R(0, &cc::Director::isPaused);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isSendCleanupToScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isSendCleanupToScene");
	LUA_TRY_INVOKE_R(0, &cc::Director::isSendCleanupToScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isStatsDisplay");
	LUA_TRY_INVOKE_R(0, &cc::Director::isStatsDisplay);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isValid");
	LUA_TRY_INVOKE_R(0, &cc::Director::isValid);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_loadIdentityMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadIdentityMatrix");
	LUA_TRY_INVOKE(1, &cc::Director::loadIdentityMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_loadMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadMatrix");
	LUA_TRY_INVOKE(2, &cc::Director::loadMatrix);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Director_mainLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:mainLoop");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Director::*)(float)>(&cc::Director::mainLoop));
	LUA_TRY_INVOKE(0, static_cast<void(cc::Director::*)()>(&cc::Director::mainLoop));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Director_multiplyMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:multiplyMatrix");
	LUA_TRY_INVOKE(2, &cc::Director::multiplyMatrix);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Director_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pause");
	LUA_TRY_INVOKE(0, &cc::Director::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_popMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popMatrix");
	LUA_TRY_INVOKE(1, &cc::Director::popMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_popScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popScene");
	LUA_TRY_INVOKE(0, &cc::Director::popScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_popToRootScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToRootScene");
	LUA_TRY_INVOKE(0, &cc::Director::popToRootScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_popToSceneStackLevel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToSceneStackLevel");
	LUA_TRY_INVOKE(1, &cc::Director::popToSceneStackLevel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_purgeCachedData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:purgeCachedData");
	LUA_TRY_INVOKE(0, &cc::Director::purgeCachedData);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_pushMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushMatrix");
	LUA_TRY_INVOKE(1, &cc::Director::pushMatrix);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_pushScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushScene");
	LUA_TRY_INVOKE(1, &cc::Director::pushScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_replaceScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:replaceScene");
	LUA_TRY_INVOKE(1, &cc::Director::replaceScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_resetMatrixStack(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resetMatrixStack");
	LUA_TRY_INVOKE(0, &cc::Director::resetMatrixStack);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_restart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:restart");
	LUA_TRY_INVOKE(0, &cc::Director::restart);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resume");
	LUA_TRY_INVOKE(0, &cc::Director::resume);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_runWithScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:runWithScene");
	LUA_TRY_INVOKE(1, &cc::Director::runWithScene);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setActionManager");
	LUA_TRY_INVOKE(1, &cc::Director::setActionManager);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setAnimationInterval");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Director::*)(float)>(&cc::Director::setAnimationInterval));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setChildrenIndexerEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setChildrenIndexerEnabled");
	LUA_TRY_INVOKE(1, &cc::Director::setChildrenIndexerEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setClearColor");
	LUA_TRY_INVOKE(1, &cc::Director::setClearColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setContentScaleFactor");
	LUA_TRY_INVOKE(1, &cc::Director::setContentScaleFactor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setDefaultValues");
	LUA_TRY_INVOKE(0, &cc::Director::setDefaultValues);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_setEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setEventDispatcher");
	LUA_TRY_INVOKE(1, &cc::Director::setEventDispatcher);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setGLDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setGLDefaultValues");
	LUA_TRY_INVOKE(0, &cc::Director::setGLDefaultValues);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_setNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNextDeltaTimeZero");
	LUA_TRY_INVOKE(1, &cc::Director::setNextDeltaTimeZero);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNotificationNode");
	LUA_TRY_INVOKE(1, &cc::Director::setNotificationNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setOpenGLView");
	LUA_TRY_INVOKE(1, &cc::Director::setOpenGLView);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setProjection");
	LUA_TRY_INVOKE(1, &cc::Director::setProjection);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setScheduler");
	LUA_TRY_INVOKE(1, &cc::Director::setScheduler);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setStatsAnchor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsAnchor");
	LUA_TRY_INVOKE(1, &cc::Director::setStatsAnchor);
	LUA_TRY_INVOKE(0, [](cc::Director* obj){{return obj->setStatsAnchor();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Director_setStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsDisplay");
	LUA_TRY_INVOKE(1, &cc::Director::setStatsDisplay);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Director_setViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setViewport");
	LUA_TRY_INVOKE(0, &cc::Director::setViewport);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_startAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:startAnimation");
	LUA_TRY_INVOKE(0, static_cast<void(cc::Director::*)()>(&cc::Director::startAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_stopAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:stopAnimation");
	LUA_TRY_INVOKE(0, &cc::Director::stopAnimation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Director_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Director", "cc.Director:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::Director::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccDirector(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Director, "Director", "cc.Director",
		cc::Director, "",
		nullptr, nullptr);
	LUA_METHOD("convertToGL", lua_cc_Director_convertToGL);
	LUA_METHOD("convertToUI", lua_cc_Director_convertToUI);
	LUA_METHOD("drawScene", lua_cc_Director_drawScene);
	LUA_METHOD("endToLua", lua_cc_Director_endToLua);
	LUA_METHOD("getActionManager", lua_cc_Director_getActionManager);
	LUA_METHOD("getAnimationInterval", lua_cc_Director_getAnimationInterval);
	LUA_METHOD("getAxmolThreadId", lua_cc_Director_getAxmolThreadId);
	LUA_METHOD("getConsole", lua_cc_Director_getConsole);
	LUA_METHOD("getContentScaleFactor", lua_cc_Director_getContentScaleFactor);
	LUA_METHOD("getDeltaTime", lua_cc_Director_getDeltaTime);
	LUA_METHOD("getEventDispatcher", lua_cc_Director_getEventDispatcher);
	LUA_METHOD("getFrameRate", lua_cc_Director_getFrameRate);
	LUA_METHOD("getMatrix", lua_cc_Director_getMatrix);
	LUA_METHOD("getNotificationNode", lua_cc_Director_getNotificationNode);
	LUA_METHOD("getOpenGLView", lua_cc_Director_getOpenGLView);
	LUA_METHOD("getRenderer", lua_cc_Director_getRenderer);
	LUA_METHOD("getRunningScene", lua_cc_Director_getRunningScene);
	LUA_METHOD("getSafeAreaRect", lua_cc_Director_getSafeAreaRect);
	LUA_METHOD("getScheduler", lua_cc_Director_getScheduler);
	LUA_METHOD("getSecondsPerFrame", lua_cc_Director_getSecondsPerFrame);
	LUA_METHOD("getTextureCache", lua_cc_Director_getTextureCache);
	LUA_METHOD("getTotalFrames", lua_cc_Director_getTotalFrames);
	LUA_METHOD("getVisibleOrigin", lua_cc_Director_getVisibleOrigin);
	LUA_METHOD("getVisibleSize", lua_cc_Director_getVisibleSize);
	LUA_METHOD("getWinSize", lua_cc_Director_getWinSize);
	LUA_METHOD("getWinSizeInPixels", lua_cc_Director_getWinSizeInPixels);
	LUA_METHOD("getZEye", lua_cc_Director_getZEye);
	LUA_METHOD("init", lua_cc_Director_init);
	LUA_METHOD("isChildrenIndexerEnabled", lua_cc_Director_isChildrenIndexerEnabled);
	LUA_METHOD("isNextDeltaTimeZero", lua_cc_Director_isNextDeltaTimeZero);
	LUA_METHOD("isPaused", lua_cc_Director_isPaused);
	LUA_METHOD("isSendCleanupToScene", lua_cc_Director_isSendCleanupToScene);
	LUA_METHOD("isStatsDisplay", lua_cc_Director_isStatsDisplay);
	LUA_METHOD("isValid", lua_cc_Director_isValid);
	LUA_METHOD("loadIdentityMatrix", lua_cc_Director_loadIdentityMatrix);
	LUA_METHOD("loadMatrix", lua_cc_Director_loadMatrix);
	LUA_METHOD("mainLoop", lua_cc_Director_mainLoop);
	LUA_METHOD("multiplyMatrix", lua_cc_Director_multiplyMatrix);
	LUA_METHOD("pause", lua_cc_Director_pause);
	LUA_METHOD("popMatrix", lua_cc_Director_popMatrix);
	LUA_METHOD("popScene", lua_cc_Director_popScene);
	LUA_METHOD("popToRootScene", lua_cc_Director_popToRootScene);
	LUA_METHOD("popToSceneStackLevel", lua_cc_Director_popToSceneStackLevel);
	LUA_METHOD("purgeCachedData", lua_cc_Director_purgeCachedData);
	LUA_METHOD("pushMatrix", lua_cc_Director_pushMatrix);
	LUA_METHOD("pushScene", lua_cc_Director_pushScene);
	LUA_METHOD("replaceScene", lua_cc_Director_replaceScene);
	LUA_METHOD("resetMatrixStack", lua_cc_Director_resetMatrixStack);
	LUA_METHOD("restart", lua_cc_Director_restart);
	LUA_METHOD("resume", lua_cc_Director_resume);
	LUA_METHOD("runWithScene", lua_cc_Director_runWithScene);
	LUA_METHOD("setActionManager", lua_cc_Director_setActionManager);
	LUA_METHOD("setAnimationInterval", lua_cc_Director_setAnimationInterval);
	LUA_METHOD("setChildrenIndexerEnabled", lua_cc_Director_setChildrenIndexerEnabled);
	LUA_METHOD("setClearColor", lua_cc_Director_setClearColor);
	LUA_METHOD("setContentScaleFactor", lua_cc_Director_setContentScaleFactor);
	LUA_METHOD("setDefaultValues", lua_cc_Director_setDefaultValues);
	LUA_METHOD("setEventDispatcher", lua_cc_Director_setEventDispatcher);
	LUA_METHOD("setGLDefaultValues", lua_cc_Director_setGLDefaultValues);
	LUA_METHOD("setNextDeltaTimeZero", lua_cc_Director_setNextDeltaTimeZero);
	LUA_METHOD("setNotificationNode", lua_cc_Director_setNotificationNode);
	LUA_METHOD("setOpenGLView", lua_cc_Director_setOpenGLView);
	LUA_METHOD("setProjection", lua_cc_Director_setProjection);
	LUA_METHOD("setScheduler", lua_cc_Director_setScheduler);
	LUA_METHOD("setStatsAnchor", lua_cc_Director_setStatsAnchor);
	LUA_METHOD("setStatsDisplay", lua_cc_Director_setStatsDisplay);
	LUA_METHOD("setViewport", lua_cc_Director_setViewport);
	LUA_METHOD("startAnimation", lua_cc_Director_startAnimation);
	LUA_METHOD("stopAnimation", lua_cc_Director_stopAnimation);
	LUA_METHOD("getInstance", lua_cc_Director_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Timer_cancel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:cancel");
	LUA_TRY_INVOKE(0, &cc::Timer::cancel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Timer_isAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isAborted");
	LUA_TRY_INVOKE_R(0, &cc::Timer::isAborted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Timer_isExhausted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isExhausted");
	LUA_TRY_INVOKE_R(0, &cc::Timer::isExhausted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Timer_setAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setAborted");
	LUA_TRY_INVOKE(0, &cc::Timer::setAborted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Timer_setupTimerWithInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setupTimerWithInterval");
	LUA_TRY_INVOKE(3, &cc::Timer::setupTimerWithInterval);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_Timer_trigger(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:trigger");
	LUA_TRY_INVOKE(1, &cc::Timer::trigger);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Timer_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:update");
	LUA_TRY_INVOKE(1, &cc::Timer::update);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTimer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Timer, "Timer", "cc.Timer",
		cc::Timer, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("cancel", lua_cc_Timer_cancel);
	LUA_METHOD("isAborted", lua_cc_Timer_isAborted);
	LUA_METHOD("isExhausted", lua_cc_Timer_isExhausted);
	LUA_METHOD("setAborted", lua_cc_Timer_setAborted);
	LUA_METHOD("setupTimerWithInterval", lua_cc_Timer_setupTimerWithInterval);
	LUA_METHOD("trigger", lua_cc_Timer_trigger);
	LUA_METHOD("update", lua_cc_Timer_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Scheduler_getTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:getTimeScale");
	LUA_TRY_INVOKE_R(0, &cc::Scheduler::getTimeScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Scheduler_performFunctionInCocosThread(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:performFunctionInCocosThread");
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, &cc::Scheduler::performFunctionInCocosThread);
	}
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Scheduler_removeAllPendingActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:removeAllPendingActions");
	LUA_TRY_INVOKE(0, &cc::Scheduler::removeAllPendingActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Scheduler_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:setTimeScale");
	LUA_TRY_INVOKE(1, &cc::Scheduler::setTimeScale);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccScheduler(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Scheduler, "Scheduler", "cc.Scheduler",
		cc::Scheduler, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getTimeScale", lua_cc_Scheduler_getTimeScale);
	LUA_METHOD("performFunctionInCocosThread", lua_cc_Scheduler_performFunctionInCocosThread);
	LUA_METHOD("removeAllPendingActions", lua_cc_Scheduler_removeAllPendingActions);
	LUA_METHOD("setTimeScale", lua_cc_Scheduler_setTimeScale);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_AsyncTaskPool_stopTasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AsyncTaskPool", "cc.AsyncTaskPool:stopTasks");
	LUA_TRY_INVOKE(1, &cc::AsyncTaskPool::stopTasks);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AsyncTaskPool_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AsyncTaskPool", "cc.AsyncTaskPool:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::AsyncTaskPool::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccAsyncTaskPool(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AsyncTaskPool, "AsyncTaskPool", "cc.AsyncTaskPool",
		cc::AsyncTaskPool, "",
		nullptr, nullptr);
	LUA_METHOD("stopTasks", lua_cc_AsyncTaskPool_stopTasks);
	LUA_METHOD("getInstance", lua_cc_AsyncTaskPool_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Action_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:clone");
	LUA_TRY_INVOKE_R(0, &cc::Action::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_getFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getFlags");
	LUA_TRY_INVOKE_R(0, &cc::Action::getFlags);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_getOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getOriginalTarget");
	LUA_TRY_INVOKE_R(0, &cc::Action::getOriginalTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTag");
	LUA_TRY_INVOKE_R(0, &cc::Action::getTag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_getTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTarget");
	LUA_TRY_INVOKE_R(0, &cc::Action::getTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_isDone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:isDone");
	LUA_TRY_INVOKE_R(0, &cc::Action::isDone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_reverse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:reverse");
	LUA_TRY_INVOKE_R(0, &cc::Action::reverse);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_setFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setFlags");
	LUA_TRY_INVOKE(1, &cc::Action::setFlags);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_setOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setOriginalTarget");
	LUA_TRY_INVOKE(1, &cc::Action::setOriginalTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTag");
	LUA_TRY_INVOKE(1, &cc::Action::setTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTarget");
	LUA_TRY_INVOKE(1, &cc::Action::setTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_startWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:startWithTarget");
	LUA_TRY_INVOKE(1, &cc::Action::startWithTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_step(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:step");
	LUA_TRY_INVOKE(1, &cc::Action::step);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Action_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:stop");
	LUA_TRY_INVOKE(0, &cc::Action::stop);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Action_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:update");
	LUA_TRY_INVOKE(1, &cc::Action::update);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Action, "Action", "cc.Action",
		cc::Action, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cc_Action_clone);
	LUA_METHOD("getFlags", lua_cc_Action_getFlags);
	LUA_METHOD("getOriginalTarget", lua_cc_Action_getOriginalTarget);
	LUA_METHOD("getTag", lua_cc_Action_getTag);
	LUA_METHOD("getTarget", lua_cc_Action_getTarget);
	LUA_METHOD("isDone", lua_cc_Action_isDone);
	LUA_METHOD("reverse", lua_cc_Action_reverse);
	LUA_METHOD("setFlags", lua_cc_Action_setFlags);
	LUA_METHOD("setOriginalTarget", lua_cc_Action_setOriginalTarget);
	LUA_METHOD("setTag", lua_cc_Action_setTag);
	LUA_METHOD("setTarget", lua_cc_Action_setTarget);
	LUA_METHOD("startWithTarget", lua_cc_Action_startWithTarget);
	LUA_METHOD("step", lua_cc_Action_step);
	LUA_METHOD("stop", lua_cc_Action_stop);
	LUA_METHOD("update", lua_cc_Action_update);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FiniteTimeAction_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FiniteTimeAction", "cc.FiniteTimeAction:getDuration");
	LUA_TRY_INVOKE_R(0, &cc::FiniteTimeAction::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FiniteTimeAction_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FiniteTimeAction", "cc.FiniteTimeAction:setDuration");
	LUA_TRY_INVOKE(1, &cc::FiniteTimeAction::setDuration);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccFiniteTimeAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FiniteTimeAction, "FiniteTimeAction", "cc.FiniteTimeAction",
		cc::FiniteTimeAction, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("getDuration", lua_cc_FiniteTimeAction_getDuration);
	LUA_METHOD("setDuration", lua_cc_FiniteTimeAction_setDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Speed_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cc::Speed::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Speed_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getSpeed");
	LUA_TRY_INVOKE_R(0, &cc::Speed::getSpeed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Speed_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:initWithAction");
	LUA_TRY_INVOKE_R(2, &cc::Speed::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Speed_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setInnerAction");
	LUA_TRY_INVOKE(1, &cc::Speed::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Speed_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setSpeed");
	LUA_TRY_INVOKE(1, &cc::Speed::setSpeed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Speed_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Speed", "cc.Speed:create");
	LUA_TRY_INVOKE_R(2, &cc::Speed::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSpeed(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Speed, "Speed", "cc.Speed",
		cc::Speed, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cc_Speed_getInnerAction);
	LUA_METHOD("getSpeed", lua_cc_Speed_getSpeed);
	LUA_METHOD("initWithAction", lua_cc_Speed_initWithAction);
	LUA_METHOD("setInnerAction", lua_cc_Speed_setInnerAction);
	LUA_METHOD("setSpeed", lua_cc_Speed_setSpeed);
	LUA_METHOD("create", lua_cc_Speed_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Follow_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTarget");
	LUA_TRY_INVOKE_R(2, &cc::Follow::initWithTarget);
	LUA_TRY_INVOKE_R(1, ([](cc::Follow* obj,cc::Node* arg0){{return obj->initWithTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Follow_initWithTargetAndOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTargetAndOffset");
	LUA_TRY_INVOKE_R(4, &cc::Follow::initWithTargetAndOffset);
	LUA_TRY_INVOKE_R(3, ([](cc::Follow* obj,cc::Node* arg0,float arg1,float arg2){{return obj->initWithTargetAndOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4");
}
int lua_cc_Follow_isBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:isBoundarySet");
	LUA_TRY_INVOKE_R(0, &cc::Follow::isBoundarySet);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Follow_setBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:setBoundarySet");
	LUA_TRY_INVOKE(1, &cc::Follow::setBoundarySet);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Follow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:create");
	LUA_TRY_INVOKE_R(2, &cc::Follow::create);
	LUA_TRY_INVOKE_R(1, [](cc::Node* arg0){{return cc::Follow::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_Follow_createWithOffset(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:createWithOffset");
	LUA_TRY_INVOKE_R(4, &cc::Follow::createWithOffset);
	LUA_TRY_INVOKE_R(3, ([](cc::Node* arg0,float arg1,float arg2){{return cc::Follow::createWithOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int luaReg_Core_ccFollow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Follow, "Follow", "cc.Follow",
		cc::Follow, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("initWithTarget", lua_cc_Follow_initWithTarget);
	LUA_METHOD("initWithTargetAndOffset", lua_cc_Follow_initWithTargetAndOffset);
	LUA_METHOD("isBoundarySet", lua_cc_Follow_isBoundarySet);
	LUA_METHOD("setBoundarySet", lua_cc_Follow_setBoundarySet);
	LUA_METHOD("create", lua_cc_Follow_create);
	LUA_METHOD("createWithOffset", lua_cc_Follow_createWithOffset);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Image_getBitPerPixel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getBitPerPixel");
	LUA_TRY_INVOKE_R(0, &cc::Image::getBitPerPixel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFilePath");
	LUA_TRY_INVOKE_R(0, &cc::Image::getFilePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getFileType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFileType");
	LUA_TRY_INVOKE_R(0, &cc::Image::getFileType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getHeight");
	LUA_TRY_INVOKE_R(0, &cc::Image::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getNumberOfMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getNumberOfMipmaps");
	LUA_TRY_INVOKE_R(0, &cc::Image::getNumberOfMipmaps);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getPixelFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getPixelFormat");
	LUA_TRY_INVOKE_R(0, &cc::Image::getPixelFormat);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getWidth");
	LUA_TRY_INVOKE_R(0, &cc::Image::getWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_hasAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasAlpha");
	LUA_TRY_INVOKE_R(0, &cc::Image::hasAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_hasPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasPremultipliedAlpha");
	LUA_TRY_INVOKE_R(0, &cc::Image::hasPremultipliedAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_initWithImageFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:initWithImageFile");
	LUA_TRY_INVOKE_R(1, &cc::Image::initWithImageFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Image_isCompressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:isCompressed");
	LUA_TRY_INVOKE_R(0, &cc::Image::isCompressed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_premultiplyAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:premultiplyAlpha");
	LUA_TRY_INVOKE(0, &cc::Image::premultiplyAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_reversePremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:reversePremultipliedAlpha");
	LUA_TRY_INVOKE(0, &cc::Image::reversePremultipliedAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Image_saveToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:saveToFile");
	LUA_TRY_INVOKE_R(2, &cc::Image::saveToFile);
	LUA_TRY_INVOKE_R(1, ([](cc::Image* obj,std::string_view arg0){{return obj->saveToFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Image_isCompressedImageHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:isCompressedImageHavePMA");
	LUA_TRY_INVOKE_R(1, &cc::Image::isCompressedImageHavePMA);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Image_setCompressedImagesHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setCompressedImagesHavePMA");
	LUA_TRY_INVOKE(2, &cc::Image::setCompressedImagesHavePMA);
	LUA_SINVOKE_FOOTER("2");
}
int lua_cc_Image_setPNGPremultipliedAlphaEnabled(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setPNGPremultipliedAlphaEnabled");
	LUA_TRY_INVOKE(1, &cc::Image::setPNGPremultipliedAlphaEnabled);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Image, "Image", "cc.Image",
		cc::Image, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBitPerPixel", lua_cc_Image_getBitPerPixel);
	LUA_METHOD("getFilePath", lua_cc_Image_getFilePath);
	LUA_METHOD("getFileType", lua_cc_Image_getFileType);
	LUA_METHOD("getHeight", lua_cc_Image_getHeight);
	LUA_METHOD("getNumberOfMipmaps", lua_cc_Image_getNumberOfMipmaps);
	LUA_METHOD("getPixelFormat", lua_cc_Image_getPixelFormat);
	LUA_METHOD("getWidth", lua_cc_Image_getWidth);
	LUA_METHOD("hasAlpha", lua_cc_Image_hasAlpha);
	LUA_METHOD("hasPremultipliedAlpha", lua_cc_Image_hasPremultipliedAlpha);
	LUA_METHOD("initWithImageFile", lua_cc_Image_initWithImageFile);
	LUA_METHOD("isCompressed", lua_cc_Image_isCompressed);
	LUA_METHOD("premultiplyAlpha", lua_cc_Image_premultiplyAlpha);
	LUA_METHOD("reversePremultipliedAlpha", lua_cc_Image_reversePremultipliedAlpha);
	LUA_METHOD("saveToFile", lua_cc_Image_saveToFile);
	LUA_METHOD("isCompressedImageHavePMA", lua_cc_Image_isCompressedImageHavePMA);
	LUA_METHOD("setCompressedImagesHavePMA", lua_cc_Image_setCompressedImagesHavePMA);
	LUA_METHOD("setPNGPremultipliedAlphaEnabled", lua_cc_Image_setPNGPremultipliedAlphaEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SpriteFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:clone");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getCenterRect");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getCenterRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffset");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffsetInPixels");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getOffsetInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSize");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getOriginalSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSizeInPixels");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getOriginalSizeInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRect");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRectInPixels");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getRectInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_hasAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::hasAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_hasCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasCenterRect");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::hasCenterRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cc::SpriteFrame::*)(cc::Texture2D*, const cc::Rect&, bool, const cc::Vec2&, const cc::Vec2&)>(&cc::SpriteFrame::initWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::SpriteFrame::*)(cc::Texture2D*, const cc::Rect&)>(&cc::SpriteFrame::initWithTexture)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cc_SpriteFrame_initWithTextureFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTextureFilename");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cc::SpriteFrame::*)(std::string_view, const cc::Rect&, bool, const cc::Vec2&, const cc::Vec2&)>(&cc::SpriteFrame::initWithTextureFilename)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::SpriteFrame::*)(std::string_view, const cc::Rect&)>(&cc::SpriteFrame::initWithTextureFilename)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cc_SpriteFrame_isRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:isRotated");
	LUA_TRY_INVOKE_R(0, &cc::SpriteFrame::isRotated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteFrame_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setAnchorPoint");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setAnchorPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setCenterRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setCenterRectInPixels");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setCenterRectInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffset");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setOffset);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffsetInPixels");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setOffsetInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSize");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setOriginalSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSizeInPixels");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setOriginalSizeInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRect");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRectInPixels");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setRectInPixels);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRotated");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setRotated);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setTexture");
	LUA_TRY_INVOKE(1, &cc::SpriteFrame::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cc::SpriteFrame>(*)(std::string_view, const cc::Rect&, bool, const cc::Vec2&, const cc::Vec2&)>(&cc::SpriteFrame::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::SpriteFrame>(*)(std::string_view, const cc::Rect&)>(&cc::SpriteFrame::create)));
	LUA_SINVOKE_FOOTER("2,5");
}
int lua_cc_SpriteFrame_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:createWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cc::SpriteFrame>(*)(cc::Texture2D*, const cc::Rect&, bool, const cc::Vec2&, const cc::Vec2&)>(&cc::SpriteFrame::createWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::SpriteFrame>(*)(cc::Texture2D*, const cc::Rect&)>(&cc::SpriteFrame::createWithTexture)));
	LUA_SINVOKE_FOOTER("2,5");
}
int luaReg_Core_ccSpriteFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SpriteFrame, "SpriteFrame", "cc.SpriteFrame",
		cc::SpriteFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cc_SpriteFrame_clone);
	LUA_METHOD("getAnchorPoint", lua_cc_SpriteFrame_getAnchorPoint);
	LUA_METHOD("getCenterRect", lua_cc_SpriteFrame_getCenterRect);
	LUA_METHOD("getOffset", lua_cc_SpriteFrame_getOffset);
	LUA_METHOD("getOffsetInPixels", lua_cc_SpriteFrame_getOffsetInPixels);
	LUA_METHOD("getOriginalSize", lua_cc_SpriteFrame_getOriginalSize);
	LUA_METHOD("getOriginalSizeInPixels", lua_cc_SpriteFrame_getOriginalSizeInPixels);
	LUA_METHOD("getRect", lua_cc_SpriteFrame_getRect);
	LUA_METHOD("getRectInPixels", lua_cc_SpriteFrame_getRectInPixels);
	LUA_METHOD("getTexture", lua_cc_SpriteFrame_getTexture);
	LUA_METHOD("hasAnchorPoint", lua_cc_SpriteFrame_hasAnchorPoint);
	LUA_METHOD("hasCenterRect", lua_cc_SpriteFrame_hasCenterRect);
	LUA_METHOD("initWithTexture", lua_cc_SpriteFrame_initWithTexture);
	LUA_METHOD("initWithTextureFilename", lua_cc_SpriteFrame_initWithTextureFilename);
	LUA_METHOD("isRotated", lua_cc_SpriteFrame_isRotated);
	LUA_METHOD("setAnchorPoint", lua_cc_SpriteFrame_setAnchorPoint);
	LUA_METHOD("setCenterRectInPixels", lua_cc_SpriteFrame_setCenterRectInPixels);
	LUA_METHOD("setOffset", lua_cc_SpriteFrame_setOffset);
	LUA_METHOD("setOffsetInPixels", lua_cc_SpriteFrame_setOffsetInPixels);
	LUA_METHOD("setOriginalSize", lua_cc_SpriteFrame_setOriginalSize);
	LUA_METHOD("setOriginalSizeInPixels", lua_cc_SpriteFrame_setOriginalSizeInPixels);
	LUA_METHOD("setRect", lua_cc_SpriteFrame_setRect);
	LUA_METHOD("setRectInPixels", lua_cc_SpriteFrame_setRectInPixels);
	LUA_METHOD("setRotated", lua_cc_SpriteFrame_setRotated);
	LUA_METHOD("setTexture", lua_cc_SpriteFrame_setTexture);
	LUA_METHOD("create", lua_cc_SpriteFrame_create);
	LUA_METHOD("createWithTexture", lua_cc_SpriteFrame_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_AnimationFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:clone");
	LUA_TRY_INVOKE_R(0, &cc::AnimationFrame::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AnimationFrame_getDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getDelayUnits");
	LUA_TRY_INVOKE_R(0, &cc::AnimationFrame::getDelayUnits);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AnimationFrame_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, &cc::AnimationFrame::getSpriteFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AnimationFrame_getUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getUserInfo");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ValueMap&(cc::AnimationFrame::*)()>(&cc::AnimationFrame::getUserInfo));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ValueMap&(cc::AnimationFrame::*)()const>(&cc::AnimationFrame::getUserInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AnimationFrame_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(3, &cc::AnimationFrame::initWithSpriteFrame);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_AnimationFrame_setDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setDelayUnits");
	LUA_TRY_INVOKE(1, &cc::AnimationFrame::setDelayUnits);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationFrame_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setSpriteFrame");
	LUA_TRY_INVOKE(1, &cc::AnimationFrame::setSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationFrame_setUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setUserInfo");
	LUA_TRY_INVOKE(1, &cc::AnimationFrame::setUserInfo);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:create");
	LUA_TRY_INVOKE_R(3, &cc::AnimationFrame::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccAnimationFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AnimationFrame, "AnimationFrame", "cc.AnimationFrame",
		cc::AnimationFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cc_AnimationFrame_clone);
	LUA_METHOD("getDelayUnits", lua_cc_AnimationFrame_getDelayUnits);
	LUA_METHOD("getSpriteFrame", lua_cc_AnimationFrame_getSpriteFrame);
	LUA_METHOD("getUserInfo", lua_cc_AnimationFrame_getUserInfo);
	LUA_METHOD("initWithSpriteFrame", lua_cc_AnimationFrame_initWithSpriteFrame);
	LUA_METHOD("setDelayUnits", lua_cc_AnimationFrame_setDelayUnits);
	LUA_METHOD("setSpriteFrame", lua_cc_AnimationFrame_setSpriteFrame);
	LUA_METHOD("setUserInfo", lua_cc_AnimationFrame_setUserInfo);
	LUA_METHOD("create", lua_cc_AnimationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Animation_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrame");
	LUA_TRY_INVOKE(1, &cc::Animation::addSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_addSpriteFrameWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithFile");
	LUA_TRY_INVOKE(1, &cc::Animation::addSpriteFrameWithFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_addSpriteFrameWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithTexture");
	LUA_TRY_INVOKE(2, &cc::Animation::addSpriteFrameWithTexture);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Animation_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:clone");
	LUA_TRY_INVOKE_R(0, &cc::Animation::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDelayPerUnit");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getDelayPerUnit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDuration");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getDuration);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getFrames");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getFrames);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getLoops");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getLoops);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getRestoreOriginalFrame");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getRestoreOriginalFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_getTotalDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getTotalDelayUnits");
	LUA_TRY_INVOKE_R(0, &cc::Animation::getTotalDelayUnits);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:init");
	LUA_TRY_INVOKE_R(0, &cc::Animation::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animation_initWithAnimationFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithAnimationFrames");
	LUA_TRY_INVOKE_R(3, &cc::Animation::initWithAnimationFrames);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_Animation_initWithSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, &cc::Animation::initWithSpriteFrames);
	LUA_TRY_INVOKE_R(2, ([](cc::Animation* obj,const cc::Vector<cc::SpriteFrame *>& arg0,float arg1){{return obj->initWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cc::Animation* obj,const cc::Vector<cc::SpriteFrame *>& arg0){{return obj->initWithSpriteFrames(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_Animation_setDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setDelayPerUnit");
	LUA_TRY_INVOKE(1, &cc::Animation::setDelayPerUnit);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setFrames");
	LUA_TRY_INVOKE(1, &cc::Animation::setFrames);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_setLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setLoops");
	LUA_TRY_INVOKE(1, &cc::Animation::setLoops);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_setRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setRestoreOriginalFrame");
	LUA_TRY_INVOKE(1, &cc::Animation::setRestoreOriginalFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::Animation>(*)(const cc::Vector<cc::AnimationFrame *>&, float, unsigned int)>(&cc::Animation::create)));
	LUA_TRY_INVOKE_R(2, ([](const cc::Vector<cc::AnimationFrame *>& arg0,float arg1){{return cc::Animation::create(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Animation>(*)()>(&cc::Animation::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cc_Animation_createWithSpriteFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:createWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, &cc::Animation::createWithSpriteFrames);
	LUA_TRY_INVOKE_R(2, ([](const cc::Vector<cc::SpriteFrame *>& arg0,float arg1){{return cc::Animation::createWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](const cc::Vector<cc::SpriteFrame *>& arg0){{return cc::Animation::createWithSpriteFrames(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Core_ccAnimation(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Animation, "Animation", "cc.Animation",
		cc::Animation, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cc_Animation_addSpriteFrame);
	LUA_METHOD("addSpriteFrameWithFile", lua_cc_Animation_addSpriteFrameWithFile);
	LUA_METHOD("addSpriteFrameWithTexture", lua_cc_Animation_addSpriteFrameWithTexture);
	LUA_METHOD("clone", lua_cc_Animation_clone);
	LUA_METHOD("getDelayPerUnit", lua_cc_Animation_getDelayPerUnit);
	LUA_METHOD("getDuration", lua_cc_Animation_getDuration);
	LUA_METHOD("getFrames", lua_cc_Animation_getFrames);
	LUA_METHOD("getLoops", lua_cc_Animation_getLoops);
	LUA_METHOD("getRestoreOriginalFrame", lua_cc_Animation_getRestoreOriginalFrame);
	LUA_METHOD("getTotalDelayUnits", lua_cc_Animation_getTotalDelayUnits);
	LUA_METHOD("init", lua_cc_Animation_init);
	LUA_METHOD("initWithAnimationFrames", lua_cc_Animation_initWithAnimationFrames);
	LUA_METHOD("initWithSpriteFrames", lua_cc_Animation_initWithSpriteFrames);
	LUA_METHOD("setDelayPerUnit", lua_cc_Animation_setDelayPerUnit);
	LUA_METHOD("setFrames", lua_cc_Animation_setFrames);
	LUA_METHOD("setLoops", lua_cc_Animation_setLoops);
	LUA_METHOD("setRestoreOriginalFrame", lua_cc_Animation_setRestoreOriginalFrame);
	LUA_METHOD("create", lua_cc_Animation_create);
	LUA_METHOD("createWithSpriteFrames", lua_cc_Animation_createWithSpriteFrames);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionInterval_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::ActionInterval::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionInterval_getElapsed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getElapsed");
	LUA_TRY_INVOKE_R(0, &cc::ActionInterval::getElapsed);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ActionInterval_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:initWithDuration");
	LUA_TRY_INVOKE_R(1, &cc::ActionInterval::initWithDuration);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ActionInterval_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::ActionInterval::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionInterval(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionInterval, "ActionInterval", "cc.ActionInterval",
		cc::ActionInterval, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitudeRate", lua_cc_ActionInterval_getAmplitudeRate);
	LUA_METHOD("getElapsed", lua_cc_ActionInterval_getElapsed);
	LUA_METHOD("initWithDuration", lua_cc_ActionInterval_initWithDuration);
	LUA_METHOD("setAmplitudeRate", lua_cc_ActionInterval_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Sequence_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:init");
	LUA_TRY_INVOKE_R(1, &cc::Sequence::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sequence_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, &cc::Sequence::initWithTwoActions);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSequence(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Sequence, "Sequence", "cc.Sequence",
		cc::Sequence, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_Sequence_init);
	LUA_METHOD("initWithTwoActions", lua_cc_Sequence_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Repeat_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cc::Repeat::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Repeat_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:initWithAction");
	LUA_TRY_INVOKE_R(2, &cc::Repeat::initWithAction);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Repeat_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:setInnerAction");
	LUA_TRY_INVOKE(1, &cc::Repeat::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Repeat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Repeat", "cc.Repeat:create");
	LUA_TRY_INVOKE_R(2, &cc::Repeat::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccRepeat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Repeat, "Repeat", "cc.Repeat",
		cc::Repeat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cc_Repeat_getInnerAction);
	LUA_METHOD("initWithAction", lua_cc_Repeat_initWithAction);
	LUA_METHOD("setInnerAction", lua_cc_Repeat_setInnerAction);
	LUA_METHOD("create", lua_cc_Repeat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_RepeatForever_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:getInnerAction");
	LUA_TRY_INVOKE_R(0, &cc::RepeatForever::getInnerAction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_RepeatForever_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:initWithAction");
	LUA_TRY_INVOKE_R(1, &cc::RepeatForever::initWithAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RepeatForever_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:setInnerAction");
	LUA_TRY_INVOKE(1, &cc::RepeatForever::setInnerAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_RepeatForever_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:create");
	LUA_TRY_INVOKE_R(1, &cc::RepeatForever::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccRepeatForever(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RepeatForever, "RepeatForever", "cc.RepeatForever",
		cc::RepeatForever, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cc_RepeatForever_getInnerAction);
	LUA_METHOD("initWithAction", lua_cc_RepeatForever_initWithAction);
	LUA_METHOD("setInnerAction", lua_cc_RepeatForever_setInnerAction);
	LUA_METHOD("create", lua_cc_RepeatForever_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Spawn_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:init");
	LUA_TRY_INVOKE_R(1, &cc::Spawn::init);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Spawn_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, &cc::Spawn::initWithTwoActions);
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSpawn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Spawn, "Spawn", "cc.Spawn",
		cc::Spawn, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_Spawn_init);
	LUA_METHOD("initWithTwoActions", lua_cc_Spawn_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_RotateTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateTo", "cc.RotateTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::RotateTo::*)(float, float, float)>(&cc::RotateTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::RotateTo::*)(float, const cc::Vec3&)>(&cc::RotateTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_RotateTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateTo", "cc.RotateTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::RotateTo>(*)(float, float, float)>(&cc::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::RotateTo>(*)(float, const cc::Vec3&)>(&cc::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::RotateTo>(*)(float, float)>(&cc::RotateTo::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RotateTo, "RotateTo", "cc.RotateTo",
		cc::RotateTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_RotateTo_initWithDuration);
	LUA_METHOD("create", lua_cc_RotateTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_RotateBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateBy", "cc.RotateBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::RotateBy::*)(float, float, float)>(&cc::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::RotateBy::*)(float, const cc::Vec3&)>(&cc::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::RotateBy::*)(float, float)>(&cc::RotateBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_RotateBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateBy", "cc.RotateBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::RotateBy>(*)(float, float, float)>(&cc::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::RotateBy>(*)(float, const cc::Vec3&)>(&cc::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::RotateBy>(*)(float, float)>(&cc::RotateBy::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::RotateBy, "RotateBy", "cc.RotateBy",
		cc::RotateBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_RotateBy_initWithDuration);
	LUA_METHOD("create", lua_cc_RotateBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MoveBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveBy", "cc.MoveBy:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::MoveBy::*)(float, const cc::Vec3&)>(&cc::MoveBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::MoveBy::*)(float, const cc::Vec2&)>(&cc::MoveBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_MoveBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveBy", "cc.MoveBy:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::MoveBy>(*)(float, const cc::Vec3&)>(&cc::MoveBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::MoveBy>(*)(float, const cc::Vec2&)>(&cc::MoveBy::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MoveBy, "MoveBy", "cc.MoveBy",
		cc::MoveBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_MoveBy_initWithDuration);
	LUA_METHOD("create", lua_cc_MoveBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MoveTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveTo", "cc.MoveTo:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::MoveTo::*)(float, const cc::Vec3&)>(&cc::MoveTo::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::MoveTo::*)(float, const cc::Vec2&)>(&cc::MoveTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_MoveTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveTo", "cc.MoveTo:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::MoveTo>(*)(float, const cc::Vec3&)>(&cc::MoveTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::IntrusivePtr<cc::MoveTo>(*)(float, const cc::Vec2&)>(&cc::MoveTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MoveTo, "MoveTo", "cc.MoveTo",
		cc::MoveTo, "cc.MoveBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_MoveTo_initWithDuration);
	LUA_METHOD("create", lua_cc_MoveTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SkewTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewTo", "cc.SkewTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::SkewTo::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_SkewTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewTo", "cc.SkewTo:create");
	LUA_TRY_INVOKE_R(3, &cc::SkewTo::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SkewTo, "SkewTo", "cc.SkewTo",
		cc::SkewTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_SkewTo_initWithDuration);
	LUA_METHOD("create", lua_cc_SkewTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SkewBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewBy", "cc.SkewBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, &cc::SkewBy::initWithDuration);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_SkewBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewBy", "cc.SkewBy:create");
	LUA_TRY_INVOKE_R(3, &cc::SkewBy::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SkewBy, "SkewBy", "cc.SkewBy",
		cc::SkewBy, "cc.SkewTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_SkewBy_initWithDuration);
	LUA_METHOD("create", lua_cc_SkewBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_JumpBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpBy", "cc.JumpBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::JumpBy::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_JumpBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpBy", "cc.JumpBy:create");
	LUA_TRY_INVOKE_R(4, &cc::JumpBy::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::JumpBy, "JumpBy", "cc.JumpBy",
		cc::JumpBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_JumpBy_initWithDuration);
	LUA_METHOD("create", lua_cc_JumpBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_JumpTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTo", "cc.JumpTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::JumpTo::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_JumpTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTo", "cc.JumpTo:create");
	LUA_TRY_INVOKE_R(4, &cc::JumpTo::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::JumpTo, "JumpTo", "cc.JumpTo",
		cc::JumpTo, "cc.JumpBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_JumpTo_initWithDuration);
	LUA_METHOD("create", lua_cc_JumpTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_BezierBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierBy", "cc.BezierBy:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::BezierBy::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_BezierBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierBy", "cc.BezierBy:create");
	LUA_TRY_INVOKE_R(2, &cc::BezierBy::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::BezierBy, "BezierBy", "cc.BezierBy",
		cc::BezierBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_BezierBy_initWithDuration);
	LUA_METHOD("create", lua_cc_BezierBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_BezierTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierTo", "cc.BezierTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::BezierTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_BezierTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierTo", "cc.BezierTo:create");
	LUA_TRY_INVOKE_R(2, &cc::BezierTo::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::BezierTo, "BezierTo", "cc.BezierTo",
		cc::BezierTo, "cc.BezierBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_BezierTo_initWithDuration);
	LUA_METHOD("create", lua_cc_BezierTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ScaleTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cc::ScaleTo::*)(float, float, float, float)>(&cc::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::ScaleTo::*)(float, float, float)>(&cc::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::ScaleTo::*)(float, float)>(&cc::ScaleTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cc_ScaleTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::ScaleTo>(*)(float, float, float, float)>(&cc::ScaleTo::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::ScaleTo>(*)(float, float, float)>(&cc::ScaleTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::ScaleTo>(*)(float, float)>(&cc::ScaleTo::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ScaleTo, "ScaleTo", "cc.ScaleTo",
		cc::ScaleTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ScaleTo_initWithDuration);
	LUA_METHOD("create", lua_cc_ScaleTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ScaleBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleBy", "cc.ScaleBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::ScaleBy>(*)(float, float, float, float)>(&cc::ScaleBy::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::ScaleBy>(*)(float, float, float)>(&cc::ScaleBy::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::ScaleBy>(*)(float, float)>(&cc::ScaleBy::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ScaleBy, "ScaleBy", "cc.ScaleBy",
		cc::ScaleBy, "cc.ScaleTo",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_ScaleBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Blink_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Blink", "cc.Blink:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::Blink::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Blink_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Blink", "cc.Blink:create");
	LUA_TRY_INVOKE_R(2, &cc::Blink::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBlink(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Blink, "Blink", "cc.Blink",
		cc::Blink, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_Blink_initWithDuration);
	LUA_METHOD("create", lua_cc_Blink_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeTo", "cc.FadeTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::FadeTo::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FadeTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeTo", "cc.FadeTo:create");
	LUA_TRY_INVOKE_R(2, &cc::FadeTo::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeTo, "FadeTo", "cc.FadeTo",
		cc::FadeTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_FadeTo_initWithDuration);
	LUA_METHOD("create", lua_cc_FadeTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeIn_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeIn", "cc.FadeIn:setReverseAction");
	LUA_TRY_INVOKE(1, &cc::FadeIn::setReverseAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FadeIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeIn", "cc.FadeIn:create");
	LUA_TRY_INVOKE_R(1, &cc::FadeIn::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeIn, "FadeIn", "cc.FadeIn",
		cc::FadeIn, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cc_FadeIn_setReverseAction);
	LUA_METHOD("create", lua_cc_FadeIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FadeOut_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOut", "cc.FadeOut:setReverseAction");
	LUA_TRY_INVOKE(1, &cc::FadeOut::setReverseAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FadeOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOut", "cc.FadeOut:create");
	LUA_TRY_INVOKE_R(1, &cc::FadeOut::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FadeOut, "FadeOut", "cc.FadeOut",
		cc::FadeOut, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cc_FadeOut_setReverseAction);
	LUA_METHOD("create", lua_cc_FadeOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TintTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintTo", "cc.TintTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::TintTo::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_TintTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintTo", "cc.TintTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::TintTo>(*)(float, uint8_t, uint8_t, uint8_t)>(&cc::TintTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::TintTo>(*)(float, const cc::Color3B&)>(&cc::TintTo::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Core_ccTintTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TintTo, "TintTo", "cc.TintTo",
		cc::TintTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_TintTo_initWithDuration);
	LUA_METHOD("create", lua_cc_TintTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TintBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintBy", "cc.TintBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::TintBy::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_TintBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintBy", "cc.TintBy:create");
	LUA_TRY_INVOKE_R(4, &cc::TintBy::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTintBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TintBy, "TintBy", "cc.TintBy",
		cc::TintBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_TintBy_initWithDuration);
	LUA_METHOD("create", lua_cc_TintBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_DelayTime_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DelayTime", "cc.DelayTime:create");
	LUA_TRY_INVOKE_R(1, &cc::DelayTime::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDelayTime(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::DelayTime, "DelayTime", "cc.DelayTime",
		cc::DelayTime, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_DelayTime_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Animate_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getAnimation");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Animation*(cc::Animate::*)()const>(&cc::Animate::getAnimation));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Animation*(cc::Animate::*)()>(&cc::Animate::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate_getCurrentFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getCurrentFrameIndex");
	LUA_TRY_INVOKE_R(0, &cc::Animate::getCurrentFrameIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Animate_initWithAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:initWithAnimation");
	LUA_TRY_INVOKE_R(1, &cc::Animate::initWithAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:setAnimation");
	LUA_TRY_INVOKE(1, &cc::Animate::setAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Animate_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate", "cc.Animate:create");
	LUA_TRY_INVOKE_R(1, &cc::Animate::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAnimate(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Animate, "Animate", "cc.Animate",
		cc::Animate, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cc_Animate_getAnimation);
	LUA_METHOD("getCurrentFrameIndex", lua_cc_Animate_getCurrentFrameIndex);
	LUA_METHOD("initWithAnimation", lua_cc_Animate_initWithAnimation);
	LUA_METHOD("setAnimation", lua_cc_Animate_setAnimation);
	LUA_METHOD("create", lua_cc_Animate_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TargetedAction_getForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:getForcedTarget");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Node*(cc::TargetedAction::*)()const>(&cc::TargetedAction::getForcedTarget));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Node*(cc::TargetedAction::*)()>(&cc::TargetedAction::getForcedTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TargetedAction_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:initWithTarget");
	LUA_TRY_INVOKE_R(2, &cc::TargetedAction::initWithTarget);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TargetedAction_setForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:setForcedTarget");
	LUA_TRY_INVOKE(1, &cc::TargetedAction::setForcedTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TargetedAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:create");
	LUA_TRY_INVOKE_R(2, &cc::TargetedAction::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTargetedAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TargetedAction, "TargetedAction", "cc.TargetedAction",
		cc::TargetedAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getForcedTarget", lua_cc_TargetedAction_getForcedTarget);
	LUA_METHOD("initWithTarget", lua_cc_TargetedAction_initWithTarget);
	LUA_METHOD("setForcedTarget", lua_cc_TargetedAction_setForcedTarget);
	LUA_METHOD("create", lua_cc_TargetedAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionFloat_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:initWithDuration");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, &cc::ActionFloat::initWithDuration);
	}
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_ActionFloat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:create");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, &cc::ActionFloat::create);
	}
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionFloat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionFloat, "ActionFloat", "cc.ActionFloat",
		cc::ActionFloat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ActionFloat_initWithDuration);
	LUA_METHOD("create", lua_cc_ActionFloat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_UserDefault_deleteValueForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:deleteValueForKey");
	LUA_TRY_INVOKE(1, &cc::UserDefault::deleteValueForKey);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_UserDefault_flush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:flush");
	LUA_TRY_INVOKE(0, &cc::UserDefault::flush);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_UserDefault_getBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getBoolForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::UserDefault::*)(const char*, bool)>(&cc::UserDefault::getBoolForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getBoolForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_getDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getDoubleForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<double(cc::UserDefault::*)(const char*, double)>(&cc::UserDefault::getDoubleForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<double(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getDoubleForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_getFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getFloatForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cc::UserDefault::*)(const char*, float)>(&cc::UserDefault::getFloatForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<float(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getFloatForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_getIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getIntegerForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int(cc::UserDefault::*)(const char*, int)>(&cc::UserDefault::getIntegerForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getIntegerForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_getLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getLargeIntForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int64_t(cc::UserDefault::*)(const char*, int64_t)>(&cc::UserDefault::getLargeIntForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getLargeIntForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_getStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getStringForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<std::string_view(cc::UserDefault::*)(const char*, std::string_view)>(&cc::UserDefault::getStringForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<std::string_view(cc::UserDefault::*)(const char*)>(&cc::UserDefault::getStringForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_UserDefault_setBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setBoolForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setBoolForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_setDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setDoubleForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setDoubleForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_setEncryptEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setEncryptEnabled");
	LUA_TRY_INVOKE(3, &cc::UserDefault::setEncryptEnabled);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_UserDefault_setFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setFloatForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setFloatForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_setIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setIntegerForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setIntegerForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_setLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setLargeIntForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setLargeIntForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_setStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setStringForKey");
	LUA_TRY_INVOKE(2, &cc::UserDefault::setStringForKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_UserDefault_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::UserDefault::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccUserDefault(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::UserDefault, "UserDefault", "cc.UserDefault",
		cc::UserDefault, "",
		nullptr, nullptr);
	LUA_METHOD("deleteValueForKey", lua_cc_UserDefault_deleteValueForKey);
	LUA_METHOD("flush", lua_cc_UserDefault_flush);
	LUA_METHOD("getBoolForKey", lua_cc_UserDefault_getBoolForKey);
	LUA_METHOD("getDoubleForKey", lua_cc_UserDefault_getDoubleForKey);
	LUA_METHOD("getFloatForKey", lua_cc_UserDefault_getFloatForKey);
	LUA_METHOD("getIntegerForKey", lua_cc_UserDefault_getIntegerForKey);
	LUA_METHOD("getLargeIntForKey", lua_cc_UserDefault_getLargeIntForKey);
	LUA_METHOD("getStringForKey", lua_cc_UserDefault_getStringForKey);
	LUA_METHOD("setBoolForKey", lua_cc_UserDefault_setBoolForKey);
	LUA_METHOD("setDoubleForKey", lua_cc_UserDefault_setDoubleForKey);
	LUA_METHOD("setEncryptEnabled", lua_cc_UserDefault_setEncryptEnabled);
	LUA_METHOD("setFloatForKey", lua_cc_UserDefault_setFloatForKey);
	LUA_METHOD("setIntegerForKey", lua_cc_UserDefault_setIntegerForKey);
	LUA_METHOD("setLargeIntForKey", lua_cc_UserDefault_setLargeIntForKey);
	LUA_METHOD("setStringForKey", lua_cc_UserDefault_setStringForKey);
	LUA_METHOD("getInstance", lua_cc_UserDefault_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccAppDirectory(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("AppDirectory");
	LUA_ENUM_ENTRY("PersistentData", cc::AppDirectory::PersistentData);
	LUA_ENUM_ENTRY("TransientData", cc::AppDirectory::TransientData);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccDirectoryStatus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("DirectoryStatus");
	LUA_ENUM_ENTRY("Ok", cc::DirectoryStatus::Ok);
	LUA_ENUM_ENTRY("NotInitialized", cc::DirectoryStatus::NotInitialized);
	LUA_ENUM_ENTRY("InvalidArgument", cc::DirectoryStatus::InvalidArgument);
	LUA_ENUM_ENTRY("InUse", cc::DirectoryStatus::InUse);
	LUA_ENUM_ENTRY("Unavailable", cc::DirectoryStatus::Unavailable);
	LUA_ENUM_ENTRY("PermissionDenied", cc::DirectoryStatus::PermissionDenied);
	LUA_ENUM_ENTRY("NotDirectory", cc::DirectoryStatus::NotDirectory);
	LUA_ENUM_ENTRY("IoError", cc::DirectoryStatus::IoError);
	LUA_ENUM_ENTRY("Unsupported", cc::DirectoryStatus::Unsupported);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
