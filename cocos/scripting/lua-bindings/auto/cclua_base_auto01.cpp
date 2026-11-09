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

int lua_cocos2d_Node__setLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:_setLocalZOrder");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(std::int32_t)>(&cocos2d::Node::_setLocalZOrder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_addChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:addChild");
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, int, std::string_view)>(&cocos2d::Node::addChild)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, int, int)>(&cocos2d::Node::addChild)));
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, int)>(&cocos2d::Node::addChild)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Node*)>(&cocos2d::Node::addChild));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_Node_addComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:addComponent");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Node::*)(cocos2d::Component*)>(&cocos2d::Node::addComponent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_applyMaskOnEnter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:applyMaskOnEnter");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::applyMaskOnEnter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_cleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:cleanup");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::cleanup));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_convertToNodeSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToNodeSpace");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(const cocos2d::Vec2&)const>(&cocos2d::Node::convertToNodeSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_convertToNodeSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToNodeSpaceAR");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(const cocos2d::Vec2&)const>(&cocos2d::Node::convertToNodeSpaceAR));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_convertToWorldSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToWorldSpace");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(const cocos2d::Vec2&)const>(&cocos2d::Node::convertToWorldSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_convertToWorldSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToWorldSpaceAR");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(const cocos2d::Vec2&)const>(&cocos2d::Node::convertToWorldSpaceAR));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_convertTouchToNodeSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertTouchToNodeSpace");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(cocos2d::Touch*)const>(&cocos2d::Node::convertTouchToNodeSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_convertTouchToNodeSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertTouchToNodeSpaceAR");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Node::*)(cocos2d::Touch*)const>(&cocos2d::Node::convertTouchToNodeSpaceAR));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:draw");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Node::*)(cocos2d::Renderer*, const cocos2d::Mat4&, uint32_t)>(&cocos2d::Node::draw)));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::draw));
	LUA_INVOKE_FOOTER("0,3");
}
int lua_cocos2d_Node_enumerateChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:enumerateChildren");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(std::string_view, std::function<bool(cocos2d::Node*)>)const>(&cocos2d::Node::enumerateChildren)));
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Node_getActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getActionByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Action*(cocos2d::Node::*)(int)>(&cocos2d::Node::getActionByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_getActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getActionManager");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ActionManager*(cocos2d::Node::*)()const>(&cocos2d::Node::getActionManager));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ActionManager*(cocos2d::Node::*)()>(&cocos2d::Node::getActionManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getAnchorPointInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getAnchorPointInPoints");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getAnchorPointInPoints));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getBoundingBox(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getBoundingBox");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::Node::*)()const>(&cocos2d::Node::getBoundingBox));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getCameraMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getCameraMask");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned short(cocos2d::Node::*)()const>(&cocos2d::Node::getCameraMask));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getChildByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildByName");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::Node::*)(std::string_view)const>(&cocos2d::Node::getChildByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_getChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::Node::*)(int)const>(&cocos2d::Node::getChildByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_getChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildren");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::Node *>&(cocos2d::Node::*)()const>(&cocos2d::Node::getChildren));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::Node *>&(cocos2d::Node::*)()>(&cocos2d::Node::getChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getChildrenCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildrenCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Node::*)()const>(&cocos2d::Node::getChildrenCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color3B&(cocos2d::Node::*)()const>(&cocos2d::Node::getColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getComponent");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Component*(cocos2d::Node::*)(std::string_view)>(&cocos2d::Node::getComponent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_getContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getContentSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getContentSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getDescription(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDescription");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Node::*)()const>(&cocos2d::Node::getDescription));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getDisplayedColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDisplayedColor");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Color3B&(cocos2d::Node::*)()const>(&cocos2d::Node::getDisplayedColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getDisplayedOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDisplayedOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::Node::*)()const>(&cocos2d::Node::getDisplayedOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getEventDispatcher");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventDispatcher*(cocos2d::Node::*)()const>(&cocos2d::Node::getEventDispatcher));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getGlobalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getGlobalZOrder");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getGlobalZOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getLocalZOrder");
	LUA_TRY_INVOKE_R(0, static_cast<std::int32_t(cocos2d::Node::*)()const>(&cocos2d::Node::getLocalZOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Node::*)()const>(&cocos2d::Node::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getNodeToParentAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToParentAffineTransform");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::AffineTransform(cocos2d::Node::*)(cocos2d::Node*)const>(&cocos2d::Node::getNodeToParentAffineTransform));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AffineTransform(cocos2d::Node::*)()const>(&cocos2d::Node::getNodeToParentAffineTransform));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Node_getNodeToParentTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToParentTransform");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Mat4(cocos2d::Node::*)(cocos2d::Node*)const>(&cocos2d::Node::getNodeToParentTransform));
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Mat4&(cocos2d::Node::*)()const>(&cocos2d::Node::getNodeToParentTransform));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Node_getNodeToWorldAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToWorldAffineTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AffineTransform(cocos2d::Node::*)()const>(&cocos2d::Node::getNodeToWorldAffineTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getNodeToWorldTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToWorldTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Node::*)()const>(&cocos2d::Node::getNodeToWorldTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getNormalizedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNormalizedPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getNormalizedPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getNumberOfRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNumberOfRunningActions");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocos2d::Node::*)()const>(&cocos2d::Node::getNumberOfRunningActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getNumberOfRunningActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNumberOfRunningActionsByTag");
	LUA_TRY_INVOKE_R(1, static_cast<ssize_t(cocos2d::Node::*)(int)const>(&cocos2d::Node::getNumberOfRunningActionsByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_getOnEnterTransitionDidFinishCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOnEnterTransitionDidFinishCallback");
	LUA_TRY_INVOKE_R(0, static_cast<const std::function<void()>&(cocos2d::Node::*)()const>(&cocos2d::Node::getOnEnterTransitionDidFinishCallback));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getOnExitTransitionDidStartCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOnExitTransitionDidStartCallback");
	LUA_TRY_INVOKE_R(0, static_cast<const std::function<void()>&(cocos2d::Node::*)()const>(&cocos2d::Node::getOnExitTransitionDidStartCallback));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::Node::*)()const>(&cocos2d::Node::getOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getParent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParent");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Node*(cocos2d::Node::*)()const>(&cocos2d::Node::getParent));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Node*(cocos2d::Node::*)()>(&cocos2d::Node::getParent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getParentToNodeAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParentToNodeAffineTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AffineTransform(cocos2d::Node::*)()const>(&cocos2d::Node::getParentToNodeAffineTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getParentToNodeTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParentToNodeTransform");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Mat4&(cocos2d::Node::*)()const>(&cocos2d::Node::getParentToNodeTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPosition_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPosition3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPosition3D");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Node::*)()const>(&cocos2d::Node::getPosition3D));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPositionNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionNormalized");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Node::*)()const>(&cocos2d::Node::getPositionNormalized));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPositionX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getPositionX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPositionY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getPositionY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getPositionZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionZ");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getPositionZ));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getProgramState");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::ProgramState*(cocos2d::Node::*)()const>(&cocos2d::Node::getProgramState));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotation");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getRotation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getRotation3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotation3D");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec3(cocos2d::Node::*)()const>(&cocos2d::Node::getRotation3D));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getRotationSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotationSkewX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getRotationSkewX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getRotationSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotationSkewY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getRotationSkewY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getScaleX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getScaleY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScaleZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleZ");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getScaleZ));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScene");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scene*(cocos2d::Node::*)()const>(&cocos2d::Node::getScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScheduler");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Scheduler*(cocos2d::Node::*)()const>(&cocos2d::Node::getScheduler));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Scheduler*(cocos2d::Node::*)()>(&cocos2d::Node::getScheduler));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getSkewX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getSkewX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getSkewY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Node::*)()const>(&cocos2d::Node::getSkewY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Node::*)()const>(&cocos2d::Node::getTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getWorldPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldPosition");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Node::*)()const>(&cocos2d::Node::getWorldPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getWorldToNodeAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldToNodeAffineTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AffineTransform(cocos2d::Node::*)()const>(&cocos2d::Node::getWorldToNodeAffineTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getWorldToNodeTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldToNodeTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocos2d::Node::*)()const>(&cocos2d::Node::getWorldToNodeTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_hitTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:hitTest");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Node::*)(const cocos2d::Vec2&)const>(&cocos2d::Node::hitTest));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()>(&cocos2d::Node::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_initLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:initLayer");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()>(&cocos2d::Node::initLayer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isCascadeColorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isCascadeColorEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isCascadeColorEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isCascadeOpacityEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isCascadeOpacityEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isCascadeOpacityEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isIgnoreAnchorPointForPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isIgnoreAnchorPointForPosition");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isIgnoreAnchorPointForPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isOpacityModifyRGB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isOpacityModifyRGB");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isOpacityModifyRGB));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isRunning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isRunning");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isRunning));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_isScheduled_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isScheduled");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Node::*)(std::string_view)const>(&cocos2d::Node::isScheduled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isVisible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Node::*)()const>(&cocos2d::Node::isVisible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:pause");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::pause));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_removeAllComponents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeAllComponents");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::removeAllComponents));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_removeChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, bool)>(&cocos2d::Node::removeChild)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Node* obj,cocos2d::Node* arg0){{return obj->removeChild(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_removeChildByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChildByName");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(std::string_view, bool)>(&cocos2d::Node::removeChildByName)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Node* obj,std::string_view arg0){{return obj->removeChildByName(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_removeChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChildByTag");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(int, bool)>(&cocos2d::Node::removeChildByTag)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Node* obj,int arg0){{return obj->removeChildByTag(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_removeComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeComponent");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cocos2d::Node::*)(cocos2d::Component*)>(&cocos2d::Node::removeComponent));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cocos2d::Node::*)(std::string_view)>(&cocos2d::Node::removeComponent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_reorderChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:reorderChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, int)>(&cocos2d::Node::reorderChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Node_resetChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:resetChild");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(cocos2d::Node*, bool)>(&cocos2d::Node::resetChild)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Node_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:resume");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::resume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_runAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:runAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Action*(cocos2d::Node::*)(cocos2d::Action*)>(&cocos2d::Node::runAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setActionManager");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::ActionManager*)>(&cocos2d::Node::setActionManager));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setAdditionalTransform_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setAdditionalTransform");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Node::*)(const cocos2d::AffineTransform&)>(&cocos2d::Node::setAdditionalTransform));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Mat4&)>(&cocos2d::Node::setAdditionalTransform));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setAnchorPoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec2&)>(&cocos2d::Node::setAnchorPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setCameraMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCameraMask");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(unsigned short, bool)>(&cocos2d::Node::setCameraMask)));
	LUA_TRY_INVOKE(1, ([](cocos2d::Node* obj,unsigned short arg0){{return obj->setCameraMask(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_setCascadeColorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCascadeColorEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::setCascadeColorEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setCascadeOpacityEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCascadeOpacityEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::setCascadeOpacityEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Color3B&)>(&cocos2d::Node::setColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setContentSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec2&)>(&cocos2d::Node::setContentSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setEventDispatcher");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::EventDispatcher*)>(&cocos2d::Node::setEventDispatcher));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setGlobalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setGlobalZOrder");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setGlobalZOrder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setIgnoreAnchorPointForPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setIgnoreAnchorPointForPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::setIgnoreAnchorPointForPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setLocalZOrder");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(std::int32_t)>(&cocos2d::Node::setLocalZOrder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(std::string_view)>(&cocos2d::Node::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setNodeToParentTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setNodeToParentTransform");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Mat4&)>(&cocos2d::Node::setNodeToParentTransform));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setNormalizedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setNormalizedPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec2&)>(&cocos2d::Node::setNormalizedPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOnEnterCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnEnterCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const std::function<void()>&)>(&cocos2d::Node::setOnEnterCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOnEnterTransitionDidFinishCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnEnterTransitionDidFinishCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const std::function<void()>&)>(&cocos2d::Node::setOnEnterTransitionDidFinishCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOnExitCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnExitCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const std::function<void()>&)>(&cocos2d::Node::setOnExitCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOnExitTransitionDidStartCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnExitTransitionDidStartCallback");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const std::function<void()>&)>(&cocos2d::Node::setOnExitTransitionDidStartCallback));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(uint8_t)>(&cocos2d::Node::setOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setOpacityModifyRGB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOpacityModifyRGB");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::setOpacityModifyRGB));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setParent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setParent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Node*)>(&cocos2d::Node::setParent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPosition");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(float, float)>(&cocos2d::Node::setPosition)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec2&)>(&cocos2d::Node::setPosition));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_setPosition3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPosition3D");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec3&)>(&cocos2d::Node::setPosition3D));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setPositionNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionNormalized");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec2&)>(&cocos2d::Node::setPositionNormalized));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setPositionX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setPositionX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setPositionY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setPositionY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setPositionZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionZ");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setPositionZ));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setProgramState");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Node::*)(cocos2d::backend::ProgramState*, bool)>(&cocos2d::Node::setProgramState)));
	LUA_TRY_INVOKE_R_OVERLOAD(1, ([](cocos2d::Node* obj,cocos2d::backend::ProgramState* arg0){{return obj->setProgramState(arg0);}}));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocos2d::Node::*)(uint32_t)>(&cocos2d::Node::setProgramState));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_setProgramStateWithRegistry(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setProgramStateWithRegistry");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(uint32_t, cocos2d::Texture2D*)>(&cocos2d::Node::setProgramStateWithRegistry)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Node_setRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setRotation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setRotation3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotation3D");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Vec3&)>(&cocos2d::Node::setRotation3D));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setRotationQuat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationQuat");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Quaternion&)>(&cocos2d::Node::setRotationQuat));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setRotationSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationSkewX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setRotationSkewX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setRotationSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationSkewY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setRotationSkewY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScale");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Node::*)(float, float)>(&cocos2d::Node::setScale)));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setScale));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Node_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setScaleX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setScaleY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setScaleZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleZ");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setScaleZ));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScheduler");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Scheduler*)>(&cocos2d::Node::setScheduler));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setSkewX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setSkewX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setSkewY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::setSkewY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(int)>(&cocos2d::Node::setTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setUserObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setUserObject");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Ref*)>(&cocos2d::Node::setUserObject));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(bool)>(&cocos2d::Node::setVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_sortAllChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:sortAllChildren");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::sortAllChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_stopAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Action*)>(&cocos2d::Node::stopAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_stopActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopActionByTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(int)>(&cocos2d::Node::stopActionByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_stopActionsByFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopActionsByFlags");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(unsigned int)>(&cocos2d::Node::stopActionsByFlags));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_stopAllActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAllActions");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::stopAllActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_stopAllActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAllActionsByTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(int)>(&cocos2d::Node::stopAllActionsByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:update");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(float)>(&cocos2d::Node::update));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_updateDisplayedColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateDisplayedColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(const cocos2d::Color3B&)>(&cocos2d::Node::updateDisplayedColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_updateDisplayedOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateDisplayedOpacity");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(uint8_t)>(&cocos2d::Node::updateDisplayedOpacity));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_updateOrderOfArrival(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateOrderOfArrival");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::updateOrderOfArrival));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_updateProgramStateTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateProgramStateTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Node::*)(cocos2d::Texture2D*)>(&cocos2d::Node::updateProgramStateTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Node_updateTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateTransform");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::updateTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Node_visit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:visit");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Node::*)(cocos2d::Renderer*, const cocos2d::Mat4&, uint32_t)>(&cocos2d::Node::visit)));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Node::*)()>(&cocos2d::Node::visit));
	LUA_INVOKE_FOOTER("0,3");
}
int lua_cocos2d_Node_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Node", "cc.Node:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(*)()>(&cocos2d::Node::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Node_getAttachedNodeCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Node", "cc.Node:getAttachedNodeCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(*)()>(&cocos2d::Node::getAttachedNodeCount));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Node, "Node", "cc.Node",
		cocos2d::Node, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("_setLocalZOrder", lua_cocos2d_Node__setLocalZOrder);
	LUA_METHOD("addChild", lua_cocos2d_Node_addChild);
	LUA_METHOD("addComponent", lua_cocos2d_Node_addComponent);
	LUA_METHOD("applyMaskOnEnter", lua_cocos2d_Node_applyMaskOnEnter);
	LUA_METHOD("cleanup", lua_cocos2d_Node_cleanup);
	LUA_METHOD("convertToNodeSpace", lua_cocos2d_Node_convertToNodeSpace);
	LUA_METHOD("convertToNodeSpaceAR", lua_cocos2d_Node_convertToNodeSpaceAR);
	LUA_METHOD("convertToWorldSpace", lua_cocos2d_Node_convertToWorldSpace);
	LUA_METHOD("convertToWorldSpaceAR", lua_cocos2d_Node_convertToWorldSpaceAR);
	LUA_METHOD("convertTouchToNodeSpace", lua_cocos2d_Node_convertTouchToNodeSpace);
	LUA_METHOD("convertTouchToNodeSpaceAR", lua_cocos2d_Node_convertTouchToNodeSpaceAR);
	LUA_METHOD("draw", lua_cocos2d_Node_draw);
	LUA_METHOD("enumerateChildren", lua_cocos2d_Node_enumerateChildren);
	LUA_METHOD("getActionByTag", lua_cocos2d_Node_getActionByTag);
	LUA_METHOD("getActionManager", lua_cocos2d_Node_getActionManager);
	LUA_METHOD("getAnchorPoint", lua_cocos2d_Node_getAnchorPoint);
	LUA_METHOD("getAnchorPointInPoints", lua_cocos2d_Node_getAnchorPointInPoints);
	LUA_METHOD("getBoundingBox", lua_cocos2d_Node_getBoundingBox);
	LUA_METHOD("getCameraMask", lua_cocos2d_Node_getCameraMask);
	LUA_METHOD("getChildByName", lua_cocos2d_Node_getChildByName);
	LUA_METHOD("getChildByTag", lua_cocos2d_Node_getChildByTag);
	LUA_METHOD("getChildren", lua_cocos2d_Node_getChildren);
	LUA_METHOD("getChildrenCount", lua_cocos2d_Node_getChildrenCount);
	LUA_METHOD("getColor", lua_cocos2d_Node_getColor);
	LUA_METHOD("getComponent", lua_cocos2d_Node_getComponent);
	LUA_METHOD("getContentSize", lua_cocos2d_Node_getContentSize);
	LUA_METHOD("getDescription", lua_cocos2d_Node_getDescription);
	LUA_METHOD("getDisplayedColor", lua_cocos2d_Node_getDisplayedColor);
	LUA_METHOD("getDisplayedOpacity", lua_cocos2d_Node_getDisplayedOpacity);
	LUA_METHOD("getEventDispatcher", lua_cocos2d_Node_getEventDispatcher);
	LUA_METHOD("getGlobalZOrder", lua_cocos2d_Node_getGlobalZOrder);
	LUA_METHOD("getLocalZOrder", lua_cocos2d_Node_getLocalZOrder);
	LUA_METHOD("getName", lua_cocos2d_Node_getName);
	LUA_METHOD("getNodeToParentAffineTransform", lua_cocos2d_Node_getNodeToParentAffineTransform);
	LUA_METHOD("getNodeToParentTransform", lua_cocos2d_Node_getNodeToParentTransform);
	LUA_METHOD("getNodeToWorldAffineTransform", lua_cocos2d_Node_getNodeToWorldAffineTransform);
	LUA_METHOD("getNodeToWorldTransform", lua_cocos2d_Node_getNodeToWorldTransform);
	LUA_METHOD("getNormalizedPosition", lua_cocos2d_Node_getNormalizedPosition);
	LUA_METHOD("getNumberOfRunningActions", lua_cocos2d_Node_getNumberOfRunningActions);
	LUA_METHOD("getNumberOfRunningActionsByTag", lua_cocos2d_Node_getNumberOfRunningActionsByTag);
	LUA_METHOD("getOnEnterTransitionDidFinishCallback", lua_cocos2d_Node_getOnEnterTransitionDidFinishCallback);
	LUA_METHOD("getOnExitTransitionDidStartCallback", lua_cocos2d_Node_getOnExitTransitionDidStartCallback);
	LUA_METHOD("getOpacity", lua_cocos2d_Node_getOpacity);
	LUA_METHOD("getParent", lua_cocos2d_Node_getParent);
	LUA_METHOD("getParentToNodeAffineTransform", lua_cocos2d_Node_getParentToNodeAffineTransform);
	LUA_METHOD("getParentToNodeTransform", lua_cocos2d_Node_getParentToNodeTransform);
	LUA_METHOD("getPosition", lua_cocos2d_Node_getPosition_1);
	LUA_METHOD("getPosition3D", lua_cocos2d_Node_getPosition3D);
	LUA_METHOD("getPositionNormalized", lua_cocos2d_Node_getPositionNormalized);
	LUA_METHOD("getPositionX", lua_cocos2d_Node_getPositionX);
	LUA_METHOD("getPositionY", lua_cocos2d_Node_getPositionY);
	LUA_METHOD("getPositionZ", lua_cocos2d_Node_getPositionZ);
	LUA_METHOD("getProgramState", lua_cocos2d_Node_getProgramState);
	LUA_METHOD("getRotation", lua_cocos2d_Node_getRotation);
	LUA_METHOD("getRotation3D", lua_cocos2d_Node_getRotation3D);
	LUA_METHOD("getRotationSkewX", lua_cocos2d_Node_getRotationSkewX);
	LUA_METHOD("getRotationSkewY", lua_cocos2d_Node_getRotationSkewY);
	LUA_METHOD("getScale", lua_cocos2d_Node_getScale);
	LUA_METHOD("getScaleX", lua_cocos2d_Node_getScaleX);
	LUA_METHOD("getScaleY", lua_cocos2d_Node_getScaleY);
	LUA_METHOD("getScaleZ", lua_cocos2d_Node_getScaleZ);
	LUA_METHOD("getScene", lua_cocos2d_Node_getScene);
	LUA_METHOD("getScheduler", lua_cocos2d_Node_getScheduler);
	LUA_METHOD("getSkewX", lua_cocos2d_Node_getSkewX);
	LUA_METHOD("getSkewY", lua_cocos2d_Node_getSkewY);
	LUA_METHOD("getTag", lua_cocos2d_Node_getTag);
	LUA_METHOD("getWorldPosition", lua_cocos2d_Node_getWorldPosition);
	LUA_METHOD("getWorldToNodeAffineTransform", lua_cocos2d_Node_getWorldToNodeAffineTransform);
	LUA_METHOD("getWorldToNodeTransform", lua_cocos2d_Node_getWorldToNodeTransform);
	LUA_METHOD("hitTest", lua_cocos2d_Node_hitTest);
	LUA_METHOD("init", lua_cocos2d_Node_init);
	LUA_METHOD("initLayer", lua_cocos2d_Node_initLayer);
	LUA_METHOD("isCascadeColorEnabled", lua_cocos2d_Node_isCascadeColorEnabled);
	LUA_METHOD("isCascadeOpacityEnabled", lua_cocos2d_Node_isCascadeOpacityEnabled);
	LUA_METHOD("isIgnoreAnchorPointForPosition", lua_cocos2d_Node_isIgnoreAnchorPointForPosition);
	LUA_METHOD("isOpacityModifyRGB", lua_cocos2d_Node_isOpacityModifyRGB);
	LUA_METHOD("isRunning", lua_cocos2d_Node_isRunning);
	LUA_METHOD("isScheduled", lua_cocos2d_Node_isScheduled_1);
	LUA_METHOD("isVisible", lua_cocos2d_Node_isVisible);
	LUA_METHOD("pause", lua_cocos2d_Node_pause);
	LUA_METHOD("removeAllComponents", lua_cocos2d_Node_removeAllComponents);
	LUA_METHOD("removeChild", lua_cocos2d_Node_removeChild);
	LUA_METHOD("removeChildByName", lua_cocos2d_Node_removeChildByName);
	LUA_METHOD("removeChildByTag", lua_cocos2d_Node_removeChildByTag);
	LUA_METHOD("removeComponent", lua_cocos2d_Node_removeComponent);
	LUA_METHOD("reorderChild", lua_cocos2d_Node_reorderChild);
	LUA_METHOD("resetChild", lua_cocos2d_Node_resetChild);
	LUA_METHOD("resume", lua_cocos2d_Node_resume);
	LUA_METHOD("runAction", lua_cocos2d_Node_runAction);
	LUA_METHOD("setActionManager", lua_cocos2d_Node_setActionManager);
	LUA_METHOD("setAdditionalTransform", lua_cocos2d_Node_setAdditionalTransform_1);
	LUA_METHOD("setAnchorPoint", lua_cocos2d_Node_setAnchorPoint);
	LUA_METHOD("setCameraMask", lua_cocos2d_Node_setCameraMask);
	LUA_METHOD("setCascadeColorEnabled", lua_cocos2d_Node_setCascadeColorEnabled);
	LUA_METHOD("setCascadeOpacityEnabled", lua_cocos2d_Node_setCascadeOpacityEnabled);
	LUA_METHOD("setColor", lua_cocos2d_Node_setColor);
	LUA_METHOD("setContentSize", lua_cocos2d_Node_setContentSize);
	LUA_METHOD("setEventDispatcher", lua_cocos2d_Node_setEventDispatcher);
	LUA_METHOD("setGlobalZOrder", lua_cocos2d_Node_setGlobalZOrder);
	LUA_METHOD("setIgnoreAnchorPointForPosition", lua_cocos2d_Node_setIgnoreAnchorPointForPosition);
	LUA_METHOD("setLocalZOrder", lua_cocos2d_Node_setLocalZOrder);
	LUA_METHOD("setName", lua_cocos2d_Node_setName);
	LUA_METHOD("setNodeToParentTransform", lua_cocos2d_Node_setNodeToParentTransform);
	LUA_METHOD("setNormalizedPosition", lua_cocos2d_Node_setNormalizedPosition);
	LUA_METHOD("setOnEnterCallback", lua_cocos2d_Node_setOnEnterCallback);
	LUA_METHOD("setOnEnterTransitionDidFinishCallback", lua_cocos2d_Node_setOnEnterTransitionDidFinishCallback);
	LUA_METHOD("setOnExitCallback", lua_cocos2d_Node_setOnExitCallback);
	LUA_METHOD("setOnExitTransitionDidStartCallback", lua_cocos2d_Node_setOnExitTransitionDidStartCallback);
	LUA_METHOD("setOpacity", lua_cocos2d_Node_setOpacity);
	LUA_METHOD("setOpacityModifyRGB", lua_cocos2d_Node_setOpacityModifyRGB);
	LUA_METHOD("setParent", lua_cocos2d_Node_setParent);
	LUA_METHOD("setPosition", lua_cocos2d_Node_setPosition);
	LUA_METHOD("setPosition3D", lua_cocos2d_Node_setPosition3D);
	LUA_METHOD("setPositionNormalized", lua_cocos2d_Node_setPositionNormalized);
	LUA_METHOD("setPositionX", lua_cocos2d_Node_setPositionX);
	LUA_METHOD("setPositionY", lua_cocos2d_Node_setPositionY);
	LUA_METHOD("setPositionZ", lua_cocos2d_Node_setPositionZ);
	LUA_METHOD("setProgramState", lua_cocos2d_Node_setProgramState);
	LUA_METHOD("setProgramStateWithRegistry", lua_cocos2d_Node_setProgramStateWithRegistry);
	LUA_METHOD("setRotation", lua_cocos2d_Node_setRotation);
	LUA_METHOD("setRotation3D", lua_cocos2d_Node_setRotation3D);
	LUA_METHOD("setRotationQuat", lua_cocos2d_Node_setRotationQuat);
	LUA_METHOD("setRotationSkewX", lua_cocos2d_Node_setRotationSkewX);
	LUA_METHOD("setRotationSkewY", lua_cocos2d_Node_setRotationSkewY);
	LUA_METHOD("setScale", lua_cocos2d_Node_setScale);
	LUA_METHOD("setScaleX", lua_cocos2d_Node_setScaleX);
	LUA_METHOD("setScaleY", lua_cocos2d_Node_setScaleY);
	LUA_METHOD("setScaleZ", lua_cocos2d_Node_setScaleZ);
	LUA_METHOD("setScheduler", lua_cocos2d_Node_setScheduler);
	LUA_METHOD("setSkewX", lua_cocos2d_Node_setSkewX);
	LUA_METHOD("setSkewY", lua_cocos2d_Node_setSkewY);
	LUA_METHOD("setTag", lua_cocos2d_Node_setTag);
	LUA_METHOD("setUserObject", lua_cocos2d_Node_setUserObject);
	LUA_METHOD("setVisible", lua_cocos2d_Node_setVisible);
	LUA_METHOD("sortAllChildren", lua_cocos2d_Node_sortAllChildren);
	LUA_METHOD("stopAction", lua_cocos2d_Node_stopAction);
	LUA_METHOD("stopActionByTag", lua_cocos2d_Node_stopActionByTag);
	LUA_METHOD("stopActionsByFlags", lua_cocos2d_Node_stopActionsByFlags);
	LUA_METHOD("stopAllActions", lua_cocos2d_Node_stopAllActions);
	LUA_METHOD("stopAllActionsByTag", lua_cocos2d_Node_stopAllActionsByTag);
	LUA_METHOD("update", lua_cocos2d_Node_update);
	LUA_METHOD("updateDisplayedColor", lua_cocos2d_Node_updateDisplayedColor);
	LUA_METHOD("updateDisplayedOpacity", lua_cocos2d_Node_updateDisplayedOpacity);
	LUA_METHOD("updateOrderOfArrival", lua_cocos2d_Node_updateOrderOfArrival);
	LUA_METHOD("updateProgramStateTexture", lua_cocos2d_Node_updateProgramStateTexture);
	LUA_METHOD("updateTransform", lua_cocos2d_Node_updateTransform);
	LUA_METHOD("visit", lua_cocos2d_Node_visit);
	LUA_METHOD("create", lua_cocos2d_Node_create);
	LUA_METHOD("getAttachedNodeCount", lua_cocos2d_Node_getAttachedNodeCount);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Scene_getDefaultCamera(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getDefaultCamera");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Camera*(cocos2d::Scene::*)()const>(&cocos2d::Scene::getDefaultCamera));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scene_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Scene::*)(const cocos2d::Vec2&)>(&cocos2d::Scene::initWithSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scene_onProjectionChanged(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:onProjectionChanged");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scene::*)(cocos2d::EventCustom*)>(&cocos2d::Scene::onProjectionChanged));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scene_setCameraOrderDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setCameraOrderDirty");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Scene::*)()>(&cocos2d::Scene::setCameraOrderDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scene*(*)()>(&cocos2d::Scene::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Scene_createWithSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithSize");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Scene*(*)(const cocos2d::Vec2&)>(&cocos2d::Scene::createWithSize));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Scene, "Scene", "cc.Scene",
		cocos2d::Scene, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getDefaultCamera", lua_cocos2d_Scene_getDefaultCamera);
	LUA_METHOD("initWithSize", lua_cocos2d_Scene_initWithSize);
	LUA_METHOD("onProjectionChanged", lua_cocos2d_Scene_onProjectionChanged);
	LUA_METHOD("setCameraOrderDirty", lua_cocos2d_Scene_setCameraOrderDirty);
	LUA_METHOD("create", lua_cocos2d_Scene_create);
	LUA_METHOD("createWithSize", lua_cocos2d_Scene_createWithSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GLView_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:endToLua");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GLView::*)()>(&cocos2d::GLView::end));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getAllTouches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getAllTouches");
	LUA_TRY_INVOKE_R(0, static_cast<std::vector<cocos2d::Touch *>(cocos2d::GLView::*)()const>(&cocos2d::GLView::getAllTouches));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::GLView::*)()const>(&cocos2d::GLView::getContentScaleFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getDesignResolutionSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::GLView::*)()const>(&cocos2d::GLView::getDesignResolutionSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::GLView::*)()const>(&cocos2d::GLView::getFrameSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getFrameZoomFactor");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::GLView::*)()const>(&cocos2d::GLView::getFrameZoomFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getResolutionPolicy(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getResolutionPolicy");
	LUA_TRY_INVOKE_R(0, static_cast<ResolutionPolicy(cocos2d::GLView::*)()const>(&cocos2d::GLView::getResolutionPolicy));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getRetinaFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getRetinaFactor");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::GLView::*)()const>(&cocos2d::GLView::getRetinaFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::GLView::*)()const>(&cocos2d::GLView::getSafeAreaRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::GLView::*)()const>(&cocos2d::GLView::getScaleX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScaleY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::GLView::*)()const>(&cocos2d::GLView::getScaleY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getScissorRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::GLView::*)()const>(&cocos2d::GLView::getScissorRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::GLView::*)()const>(&cocos2d::GLView::getViewName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getViewPortRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getViewPortRect");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::GLView::*)()const>(&cocos2d::GLView::getViewPortRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::GLView::*)()const>(&cocos2d::GLView::getVisibleOrigin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::GLView::*)()const>(&cocos2d::GLView::getVisibleRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:getVisibleSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::GLView::*)()const>(&cocos2d::GLView::getVisibleSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isOpenGLReady(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isOpenGLReady");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GLView::*)()>(&cocos2d::GLView::isOpenGLReady));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isRetinaDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isRetinaDisplay");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GLView::*)()const>(&cocos2d::GLView::isRetinaDisplay));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_isScissorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:isScissorEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GLView::*)()>(&cocos2d::GLView::isScissorEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_pollEvents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:pollEvents");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GLView::*)()>(&cocos2d::GLView::pollEvents));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_renderScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:renderScene");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::GLView::*)(cocos2d::Scene*, cocos2d::Renderer*)>(&cocos2d::GLView::renderScene)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_GLView_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setContentScaleFactor");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::GLView::*)(float)>(&cocos2d::GLView::setContentScaleFactor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setCursorVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setCursorVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GLView::*)(bool)>(&cocos2d::GLView::setCursorVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setDefaultIcon(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDefaultIcon");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GLView::*)()const>(&cocos2d::GLView::setDefaultIcon));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_setDesignResolutionSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setDesignResolutionSize");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::GLView::*)(float, float, ResolutionPolicy)>(&cocos2d::GLView::setDesignResolutionSize)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_GLView_setFrameSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameSize");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::GLView::*)(float, float)>(&cocos2d::GLView::setFrameSize)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_GLView_setFrameZoomFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setFrameZoomFactor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GLView::*)(float)>(&cocos2d::GLView::setFrameZoomFactor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setIMEKeyboardState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setIMEKeyboardState");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GLView::*)(bool)>(&cocos2d::GLView::setIMEKeyboardState));
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
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::GLView::*)(float, float, float, float)>(&cocos2d::GLView::setScissorInPoints)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_GLView_setViewName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::GLView::*)(std::string_view)>(&cocos2d::GLView::setViewName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_GLView_setViewPortInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:setViewPortInPoints");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::GLView::*)(float, float, float, float)>(&cocos2d::GLView::setViewPortInPoints)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_GLView_swapBuffers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:swapBuffers");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::GLView::*)()>(&cocos2d::GLView::swapBuffers));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GLView_windowShouldClose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GLView", "cc.GLView:windowShouldClose");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::GLView::*)()>(&cocos2d::GLView::windowShouldClose));
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
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Director::*)(const cocos2d::Vec2&)>(&cocos2d::Director::convertToGL));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_convertToUI(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:convertToUI");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Vec2(cocos2d::Director::*)(const cocos2d::Vec2&)>(&cocos2d::Director::convertToUI));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_drawScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:drawScene");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::drawScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:endToLua");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::end));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getActionManager");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionManager*(cocos2d::Director::*)()const>(&cocos2d::Director::getActionManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAnimationInterval");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()>(&cocos2d::Director::getAnimationInterval));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getAxmolThreadId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getAxmolThreadId");
	LUA_TRY_INVOKE_R(0, static_cast<const std::thread::id&(cocos2d::Director::*)()const>(&cocos2d::Director::getCocos2dThreadId));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getConsole(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getConsole");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Console*(cocos2d::Director::*)()const>(&cocos2d::Director::getConsole));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getContentScaleFactor");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()const>(&cocos2d::Director::getContentScaleFactor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getDeltaTime(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getDeltaTime");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()const>(&cocos2d::Director::getDeltaTime));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getEventDispatcher");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventDispatcher*(cocos2d::Director::*)()const>(&cocos2d::Director::getEventDispatcher));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getFrameRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getFrameRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()const>(&cocos2d::Director::getFrameRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getMatrix");
	LUA_TRY_INVOKE_R(1, static_cast<const cocos2d::Mat4&(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE)const>(&cocos2d::Director::getMatrix));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_getNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getNotificationNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::Director::*)()const>(&cocos2d::Director::getNotificationNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getOpenGLView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::GLView*(cocos2d::Director::*)()>(&cocos2d::Director::getOpenGLView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getRenderer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRenderer");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Renderer*(cocos2d::Director::*)()const>(&cocos2d::Director::getRenderer));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getRunningScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getRunningScene");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scene*(cocos2d::Director::*)()>(&cocos2d::Director::getRunningScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getSafeAreaRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSafeAreaRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::Director::*)()const>(&cocos2d::Director::getSafeAreaRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getScheduler");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Scheduler*(cocos2d::Director::*)()const>(&cocos2d::Director::getScheduler));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getSecondsPerFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getSecondsPerFrame");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()>(&cocos2d::Director::getSecondsPerFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getTextureCache(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTextureCache");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureCache*(cocos2d::Director::*)()const>(&cocos2d::Director::getTextureCache));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getTotalFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getTotalFrames");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Director::*)()>(&cocos2d::Director::getTotalFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getVisibleOrigin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleOrigin");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Director::*)()const>(&cocos2d::Director::getVisibleOrigin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getVisibleSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getVisibleSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Director::*)()const>(&cocos2d::Director::getVisibleSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getWinSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Director::*)()const>(&cocos2d::Director::getWinSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getWinSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getWinSizeInPixels");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Director::*)()const>(&cocos2d::Director::getWinSizeInPixels));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getZEye(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:getZEye");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Director::*)()const>(&cocos2d::Director::getZEye));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()>(&cocos2d::Director::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isChildrenIndexerEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isChildrenIndexerEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()const>(&cocos2d::Director::isChildrenIndexerEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isNextDeltaTimeZero");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()>(&cocos2d::Director::isNextDeltaTimeZero));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isPaused(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isPaused");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()>(&cocos2d::Director::isPaused));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isSendCleanupToScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isSendCleanupToScene");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()>(&cocos2d::Director::isSendCleanupToScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isStatsDisplay");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()>(&cocos2d::Director::isStatsDisplay));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_isValid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:isValid");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Director::*)()const>(&cocos2d::Director::isValid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_loadIdentityMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadIdentityMatrix");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE)>(&cocos2d::Director::loadIdentityMatrix));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_loadMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:loadMatrix");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE, const cocos2d::Mat4&)>(&cocos2d::Director::loadMatrix)));
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
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE, const cocos2d::Mat4&)>(&cocos2d::Director::multiplyMatrix)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Director_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pause");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::pause));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popMatrix");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE)>(&cocos2d::Director::popMatrix));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_popScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popScene");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::popScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popToRootScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToRootScene");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::popToRootScene));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_popToSceneStackLevel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:popToSceneStackLevel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(int)>(&cocos2d::Director::popToSceneStackLevel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_purgeCachedData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:purgeCachedData");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::purgeCachedData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_pushMatrix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushMatrix");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::MATRIX_STACK_TYPE)>(&cocos2d::Director::pushMatrix));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_pushScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:pushScene");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Scene*)>(&cocos2d::Director::pushScene));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_replaceScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:replaceScene");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Scene*)>(&cocos2d::Director::replaceScene));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_resetMatrixStack(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resetMatrixStack");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::resetMatrixStack));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_restart(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:restart");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::restart));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:resume");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::resume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_runWithScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:runWithScene");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Scene*)>(&cocos2d::Director::runWithScene));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setActionManager");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::ActionManager*)>(&cocos2d::Director::setActionManager));
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
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(bool)>(&cocos2d::Director::setChildrenIndexerEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setClearColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(const cocos2d::Color4F&)>(&cocos2d::Director::setClearColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setContentScaleFactor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setContentScaleFactor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(float)>(&cocos2d::Director::setContentScaleFactor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setDefaultValues");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::setDefaultValues));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_setEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setEventDispatcher");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::EventDispatcher*)>(&cocos2d::Director::setEventDispatcher));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setGLDefaultValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setGLDefaultValues");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::setGLDefaultValues));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_setNextDeltaTimeZero(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNextDeltaTimeZero");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(bool)>(&cocos2d::Director::setNextDeltaTimeZero));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setNotificationNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setNotificationNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Node*)>(&cocos2d::Director::setNotificationNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setOpenGLView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setOpenGLView");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::GLView*)>(&cocos2d::Director::setOpenGLView));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setProjection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setProjection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Director::Projection)>(&cocos2d::Director::setProjection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setScheduler");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::Scheduler*)>(&cocos2d::Director::setScheduler));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setStatsAnchor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsAnchor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(cocos2d::AnchorPreset)>(&cocos2d::Director::setStatsAnchor));
	LUA_TRY_INVOKE(0, [](cocos2d::Director* obj){{return obj->setStatsAnchor();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Director_setStatsDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setStatsDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Director::*)(bool)>(&cocos2d::Director::setStatsDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Director_setViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Director", "cc.Director:setViewport");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::setViewport));
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
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Director::*)()>(&cocos2d::Director::stopAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Director_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Director", "cc.Director:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Director*(*)()>(&cocos2d::Director::getInstance));
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
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Timer::*)()>(&cocos2d::Timer::cancel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_isAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isAborted");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Timer::*)()const>(&cocos2d::Timer::isAborted));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_isExhausted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:isExhausted");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Timer::*)()const>(&cocos2d::Timer::isExhausted));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_setAborted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setAborted");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Timer::*)()>(&cocos2d::Timer::setAborted));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Timer_setupTimerWithInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:setupTimerWithInterval");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Timer::*)(float, unsigned int, float)>(&cocos2d::Timer::setupTimerWithInterval)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Timer_trigger(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:trigger");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Timer::*)(float)>(&cocos2d::Timer::trigger));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Timer_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Timer", "cc.Timer:update");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Timer::*)(float)>(&cocos2d::Timer::update));
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
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Scheduler::*)()>(&cocos2d::Scheduler::getTimeScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scheduler_performFunctionInCocosThread(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:performFunctionInCocosThread");
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scheduler::*)(std::function<void()>)>(&cocos2d::Scheduler::performFunctionInCocosThread));
	}
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Scheduler_removeAllPendingActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:removeAllPendingActions");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Scheduler::*)()>(&cocos2d::Scheduler::removeAllPendingActions));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Scheduler_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scheduler", "cc.Scheduler:setTimeScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Scheduler::*)(float)>(&cocos2d::Scheduler::setTimeScale));
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
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AsyncTaskPool::*)(cocos2d::AsyncTaskPool::TaskType)>(&cocos2d::AsyncTaskPool::stopTasks));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AsyncTaskPool_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AsyncTaskPool", "cc.AsyncTaskPool:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AsyncTaskPool*(*)()>(&cocos2d::AsyncTaskPool::getInstance));
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
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Action*(cocos2d::Action::*)()const>(&cocos2d::Action::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getFlags");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Action::*)()const>(&cocos2d::Action::getFlags));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getOriginalTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::Action::*)()const>(&cocos2d::Action::getOriginalTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Action::*)()const>(&cocos2d::Action::getTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_getTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:getTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::Action::*)()const>(&cocos2d::Action::getTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_isDone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:isDone");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Action::*)()const>(&cocos2d::Action::isDone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_reverse(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:reverse");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Action*(cocos2d::Action::*)()const>(&cocos2d::Action::reverse));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_setFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setFlags");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(unsigned int)>(&cocos2d::Action::setFlags));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setOriginalTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setOriginalTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(cocos2d::Node*)>(&cocos2d::Action::setOriginalTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(int)>(&cocos2d::Action::setTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:setTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(cocos2d::Node*)>(&cocos2d::Action::setTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_startWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:startWithTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(cocos2d::Node*)>(&cocos2d::Action::startWithTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_step(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:step");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(float)>(&cocos2d::Action::step));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Action_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Action::*)()>(&cocos2d::Action::stop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Action_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Action", "cc.Action:update");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Action::*)(float)>(&cocos2d::Action::update));
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
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::FiniteTimeAction::*)()const>(&cocos2d::FiniteTimeAction::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FiniteTimeAction_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FiniteTimeAction", "cc.FiniteTimeAction:setDuration");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FiniteTimeAction::*)(float)>(&cocos2d::FiniteTimeAction::setDuration));
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
