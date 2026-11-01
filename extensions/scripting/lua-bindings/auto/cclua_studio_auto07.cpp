#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_timeline_BoneNode_addSkin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:addSkin");
	LUA_TRY_INVOKE(3, static_cast<void(cocostudio::timeline::BoneNode::*)(cocostudio::timeline::SkinNode*, bool, bool)>(&cocostudio::timeline::BoneNode::addSkin));
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::timeline::BoneNode::*)(cocostudio::timeline::SkinNode*, bool)>(&cocostudio::timeline::BoneNode::addSkin));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_timeline_BoneNode_getDebugDrawColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getDebugDrawColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color4F(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getDebugDrawColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getDebugDrawLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getDebugDrawLength");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getDebugDrawLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getDebugDrawWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getDebugDrawWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getDebugDrawWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getRootSkeletonNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getRootSkeletonNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::SkeletonNode*(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getRootSkeletonNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_isDebugDrawEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:isDebugDrawEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::isDebugDrawEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_setDebugDrawEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:setDebugDrawEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BoneNode::*)(bool)>(&cocostudio::timeline::BoneNode::setDebugDrawEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_BoneNode_setDebugDrawLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:setDebugDrawLength");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BoneNode::*)(float)>(&cocostudio::timeline::BoneNode::setDebugDrawLength));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_BoneNode_setDebugDrawWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:setDebugDrawWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BoneNode::*)(float)>(&cocostudio::timeline::BoneNode::setDebugDrawWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_BoneNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::BoneNode*(*)(int)>(&cocostudio::timeline::BoneNode::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::BoneNode*(*)()>(&cocostudio::timeline::BoneNode::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Studio_ccsBoneNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::BoneNode, "BoneNode", "ccs.BoneNode",
		cocos2d::Node, "ccs.cocos2d.Node",
		nullptr, nullptr);
	LUA_METHOD("addSkin", lua_cocostudio_timeline_BoneNode_addSkin);
	LUA_METHOD("getDebugDrawColor", lua_cocostudio_timeline_BoneNode_getDebugDrawColor);
	LUA_METHOD("getDebugDrawLength", lua_cocostudio_timeline_BoneNode_getDebugDrawLength);
	LUA_METHOD("getDebugDrawWidth", lua_cocostudio_timeline_BoneNode_getDebugDrawWidth);
	LUA_METHOD("getRootSkeletonNode", lua_cocostudio_timeline_BoneNode_getRootSkeletonNode);
	LUA_METHOD("isDebugDrawEnabled", lua_cocostudio_timeline_BoneNode_isDebugDrawEnabled);
	LUA_METHOD("setDebugDrawEnabled", lua_cocostudio_timeline_BoneNode_setDebugDrawEnabled);
	LUA_METHOD("setDebugDrawLength", lua_cocostudio_timeline_BoneNode_setDebugDrawLength);
	LUA_METHOD("setDebugDrawWidth", lua_cocostudio_timeline_BoneNode_setDebugDrawWidth);
	LUA_METHOD("create", lua_cocostudio_timeline_BoneNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_SkeletonNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SkeletonNode", "ccs.SkeletonNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::SkeletonNode*(*)()>(&cocostudio::timeline::SkeletonNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSkeletonNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::SkeletonNode, "SkeletonNode", "ccs.SkeletonNode",
		cocostudio::timeline::BoneNode, "ccs.BoneNode",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_timeline_SkeletonNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ComExtensionData_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::ComExtensionData::*)()const>(&cocostudio::ComExtensionData::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_getCustomProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:getCustomProperty");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::ComExtensionData::*)()const>(&cocostudio::ComExtensionData::getCustomProperty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComExtensionData::*)(int)>(&cocostudio::ComExtensionData::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComExtensionData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComExtensionData*(*)()>(&cocostudio::ComExtensionData::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComExtensionData_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComExtensionData::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComExtensionData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComExtensionData, "ComExtensionData", "ccs.ComExtensionData",
		cocos2d::Component, "ccs.cocos2d.Component",
		nullptr, nullptr);
	LUA_METHOD("getActionTag", lua_cocostudio_ComExtensionData_getActionTag);
	LUA_METHOD("getCustomProperty", lua_cocostudio_ComExtensionData_getCustomProperty);
	LUA_METHOD("setActionTag", lua_cocostudio_ComExtensionData_setActionTag);
	LUA_METHOD("create", lua_cocostudio_ComExtensionData_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComExtensionData_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
