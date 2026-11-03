#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_ProgressTimer_getPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getPercentage");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getPercentage));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getSprite");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getSprite));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:getType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ProgressTimer::Type(cocos2d::ProgressTimer::*)()const>(&cocos2d::ProgressTimer::getType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_initWithSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:initWithSprite");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ProgressTimer::*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::initWithSprite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_isReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:isReverseDirection");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ProgressTimer::*)()>(&cocos2d::ProgressTimer::isReverseDirection));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProgressTimer_setPercentage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setPercentage");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(float)>(&cocos2d::ProgressTimer::setPercentage));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setReverseDirection(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setReverseDirection");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(bool)>(&cocos2d::ProgressTimer::setReverseDirection));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setSprite");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::setSprite));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_setType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:setType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProgressTimer::*)(cocos2d::ProgressTimer::Type)>(&cocos2d::ProgressTimer::setType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProgressTimer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProgressTimer", "cc.ProgressTimer:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ProgressTimer*(*)(cocos2d::Sprite*)>(&cocos2d::ProgressTimer::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccProgressTimer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProgressTimer, "ProgressTimer", "cc.ProgressTimer",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getPercentage", lua_cocos2d_ProgressTimer_getPercentage);
	LUA_METHOD("getSprite", lua_cocos2d_ProgressTimer_getSprite);
	LUA_METHOD("getType", lua_cocos2d_ProgressTimer_getType);
	LUA_METHOD("initWithSprite", lua_cocos2d_ProgressTimer_initWithSprite);
	LUA_METHOD("isReverseDirection", lua_cocos2d_ProgressTimer_isReverseDirection);
	LUA_METHOD("setPercentage", lua_cocos2d_ProgressTimer_setPercentage);
	LUA_METHOD("setReverseDirection", lua_cocos2d_ProgressTimer_setReverseDirection);
	LUA_METHOD("setSprite", lua_cocos2d_ProgressTimer_setSprite);
	LUA_METHOD("setType", lua_cocos2d_ProgressTimer_setType);
	LUA_METHOD("create", lua_cocos2d_ProgressTimer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ProtectedNode_addProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:addProtectedChild");
	LUA_TRY_INVOKE(3, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int, int)>(&cocos2d::ProtectedNode::addProtectedChild));
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int)>(&cocos2d::ProtectedNode::addProtectedChild));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*)>(&cocos2d::ProtectedNode::addProtectedChild));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_ProtectedNode_getProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:getProtectedChildByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocos2d::ProtectedNode::*)(int)>(&cocos2d::ProtectedNode::getProtectedChildByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProtectedNode_removeAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildren");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::removeAllProtectedChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_removeAllProtectedChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ProtectedNode::*)(bool)>(&cocos2d::ProtectedNode::removeAllProtectedChildrenWithCleanup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ProtectedNode_removeProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChild");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, bool)>(&cocos2d::ProtectedNode::removeProtectedChild));
	LUA_TRY_INVOKE(1, [](cocos2d::ProtectedNode* obj,cocos2d::Node* arg0){{return obj->removeProtectedChild(arg0);}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ProtectedNode_removeProtectedChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:removeProtectedChildByTag");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ProtectedNode::*)(int, bool)>(&cocos2d::ProtectedNode::removeProtectedChildByTag));
	LUA_TRY_INVOKE(1, [](cocos2d::ProtectedNode* obj,int arg0){{return obj->removeProtectedChildByTag(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_ProtectedNode_reorderProtectedChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:reorderProtectedChild");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::ProtectedNode::*)(cocos2d::Node*, int)>(&cocos2d::ProtectedNode::reorderProtectedChild));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_ProtectedNode_sortAllProtectedChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:sortAllProtectedChildren");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ProtectedNode::*)()>(&cocos2d::ProtectedNode::sortAllProtectedChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ProtectedNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ProtectedNode", "cc.ProtectedNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ProtectedNode*(*)()>(&cocos2d::ProtectedNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccProtectedNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ProtectedNode, "ProtectedNode", "cc.ProtectedNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addProtectedChild", lua_cocos2d_ProtectedNode_addProtectedChild);
	LUA_METHOD("getProtectedChildByTag", lua_cocos2d_ProtectedNode_getProtectedChildByTag);
	LUA_METHOD("removeAllProtectedChildren", lua_cocos2d_ProtectedNode_removeAllProtectedChildren);
	LUA_METHOD("removeAllProtectedChildrenWithCleanup", lua_cocos2d_ProtectedNode_removeAllProtectedChildrenWithCleanup);
	LUA_METHOD("removeProtectedChild", lua_cocos2d_ProtectedNode_removeProtectedChild);
	LUA_METHOD("removeProtectedChildByTag", lua_cocos2d_ProtectedNode_removeProtectedChildByTag);
	LUA_METHOD("reorderProtectedChild", lua_cocos2d_ProtectedNode_reorderProtectedChild);
	LUA_METHOD("sortAllProtectedChildren", lua_cocos2d_ProtectedNode_sortAllProtectedChildren);
	LUA_METHOD("create", lua_cocos2d_ProtectedNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RenderTexture_begin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:begin");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::RenderTexture::*)()>(&cocos2d::RenderTexture::begin));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RenderTexture_beginWithClear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:beginWithClear");
	LUA_TRY_INVOKE(6, static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float, float, int)>(&cocos2d::RenderTexture::beginWithClear));
	LUA_TRY_INVOKE(5, static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float, float)>(&cocos2d::RenderTexture::beginWithClear));
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float)>(&cocos2d::RenderTexture::beginWithClear));
	LUA_INVOKE_FOOTER("4,5,6");
}
int lua_cocos2d_RenderTexture_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:clear");
	LUA_TRY_INVOKE(4, static_cast<void(cocos2d::RenderTexture::*)(float, float, float, float)>(&cocos2d::RenderTexture::clear));
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
int lua_cocos2d_RenderTexture_getSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:getSprite");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Sprite*(cocos2d::RenderTexture::*)()const>(&cocos2d::RenderTexture::getSprite));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_RenderTexture_setAutoDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RenderTexture", "cc.RenderTexture:setAutoDraw");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RenderTexture::*)(bool)>(&cocos2d::RenderTexture::setAutoDraw));
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
int luaReg_Core_ccRenderTexture(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RenderTexture, "RenderTexture", "cc.RenderTexture",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("begin", lua_cocos2d_RenderTexture_begin);
	LUA_METHOD("beginWithClear", lua_cocos2d_RenderTexture_beginWithClear);
	LUA_METHOD("clear", lua_cocos2d_RenderTexture_clear);
	LUA_METHOD("clearDepth", lua_cocos2d_RenderTexture_clearDepth);
	LUA_METHOD("clearStencil", lua_cocos2d_RenderTexture_clearStencil);
	LUA_METHOD("endToLua", lua_cocos2d_RenderTexture_endToLua);
	LUA_METHOD("getClearDepth", lua_cocos2d_RenderTexture_getClearDepth);
	LUA_METHOD("getClearFlags", lua_cocos2d_RenderTexture_getClearFlags);
	LUA_METHOD("getClearStencil", lua_cocos2d_RenderTexture_getClearStencil);
	LUA_METHOD("getSprite", lua_cocos2d_RenderTexture_getSprite);
	LUA_METHOD("isAutoDraw", lua_cocos2d_RenderTexture_isAutoDraw);
	LUA_METHOD("isSharedRenderTarget", lua_cocos2d_RenderTexture_isSharedRenderTarget);
	LUA_METHOD("setAutoDraw", lua_cocos2d_RenderTexture_setAutoDraw);
	LUA_METHOD("setClearDepth", lua_cocos2d_RenderTexture_setClearDepth);
	LUA_METHOD("setClearFlags", lua_cocos2d_RenderTexture_setClearFlags);
	LUA_METHOD("setClearStencil", lua_cocos2d_RenderTexture_setClearStencil);
	LUA_METHOD("setKeepMatrix", lua_cocos2d_RenderTexture_setKeepMatrix);
	LUA_METHOD("setSprite", lua_cocos2d_RenderTexture_setSprite);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionEaseScene_easeActionWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TransitionEaseScene", "cc.TransitionEaseScene:easeActionWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ActionInterval*(cocos2d::TransitionEaseScene::*)(cocos2d::ActionInterval*)>(&cocos2d::TransitionEaseScene::easeActionWithAction));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTransitionEaseScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cocos2d::TransitionEaseScene, "TransitionEaseScene", "cc.TransitionEaseScene",
		nullptr, nullptr);
	LUA_METHOD("easeActionWithAction", lua_cocos2d_TransitionEaseScene_easeActionWithAction);
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
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::TransitionScene::*)(float, cocos2d::Scene*)>(&cocos2d::TransitionScene::initWithDuration));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TransitionScene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionScene", "cc.TransitionScene:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionScene*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionScene::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionScene, "TransitionScene", "cc.TransitionScene",
		cocos2d::Scene, "cc.Scene",
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
	LUA_TRY_INVOKE_R(3, static_cast<bool(cocos2d::TransitionSceneOriented::*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionSceneOriented::initWithDuration));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TransitionSceneOriented_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionSceneOriented", "cc.TransitionSceneOriented:create");
	LUA_TRY_INVOKE_R(3, static_cast<cocos2d::TransitionSceneOriented*(*)(float, cocos2d::Scene*, cocos2d::TransitionScene::Orientation)>(&cocos2d::TransitionSceneOriented::create));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccTransitionSceneOriented(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionSceneOriented, "TransitionSceneOriented", "cc.TransitionSceneOriented",
		cocos2d::TransitionScene, "cc.TransitionScene",
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
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionRotoZoom*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionRotoZoom::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionRotoZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionRotoZoom, "TransitionRotoZoom", "cc.TransitionRotoZoom",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionRotoZoom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionJumpZoom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionJumpZoom", "cc.TransitionJumpZoom:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionJumpZoom*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionJumpZoom::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionJumpZoom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionJumpZoom, "TransitionJumpZoom", "cc.TransitionJumpZoom",
		cocos2d::TransitionScene, "cc.TransitionScene",
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
int lua_cocos2d_TransitionMoveInL_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInL", "cc.TransitionMoveInL:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionMoveInL*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInL::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInL(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInL, "TransitionMoveInL", "cc.TransitionMoveInL",
		cocos2d::TransitionScene, "cc.TransitionScene",
		nullptr, nullptr);
	LUA_METHOD("action", lua_cocos2d_TransitionMoveInL_action);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInL_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInR_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInR", "cc.TransitionMoveInR:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionMoveInR*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInR::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInR(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInR, "TransitionMoveInR", "cc.TransitionMoveInR",
		cocos2d::TransitionMoveInL, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInR_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInT_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInT", "cc.TransitionMoveInT:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionMoveInT*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInT::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInT(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInT, "TransitionMoveInT", "cc.TransitionMoveInT",
		cocos2d::TransitionMoveInL, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInT_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TransitionMoveInB_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TransitionMoveInB", "cc.TransitionMoveInB:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::TransitionMoveInB*(*)(float, cocos2d::Scene*)>(&cocos2d::TransitionMoveInB::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTransitionMoveInB(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TransitionMoveInB, "TransitionMoveInB", "cc.TransitionMoveInB",
		cocos2d::TransitionMoveInL, "cc.TransitionMoveInL",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_TransitionMoveInB_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
