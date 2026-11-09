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
