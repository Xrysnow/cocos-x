#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_MovementBoneData_addFrameData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:addFrameData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::MovementBoneData::*)(cocostudio::FrameData*)>(&cocostudio::MovementBoneData::addFrameData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementBoneData_getFrameData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:getFrameData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::FrameData*(cocostudio::MovementBoneData::*)(int)>(&cocostudio::MovementBoneData::getFrameData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementBoneData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::MovementBoneData::*)()>(&cocostudio::MovementBoneData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_MovementBoneData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.MovementBoneData", "ccs.MovementBoneData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::MovementBoneData*(*)()>(&cocostudio::MovementBoneData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsMovementBoneData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::MovementBoneData, "MovementBoneData", "ccs.MovementBoneData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addFrameData", lua_cocostudio_MovementBoneData_addFrameData);
	LUA_METHOD("getFrameData", lua_cocostudio_MovementBoneData_getFrameData);
	LUA_METHOD("init", lua_cocostudio_MovementBoneData_init);
	LUA_METHOD("create", lua_cocostudio_MovementBoneData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_MovementData_addMovementBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.MovementData", "ccs.MovementData:addMovementBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::MovementData::*)(cocostudio::MovementBoneData*)>(&cocostudio::MovementData::addMovementBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_MovementData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.MovementData", "ccs.MovementData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::MovementData*(*)()>(&cocostudio::MovementData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsMovementData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::MovementData, "MovementData", "ccs.MovementData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addMovementBoneData", lua_cocostudio_MovementData_addMovementBoneData);
	LUA_METHOD("create", lua_cocostudio_MovementData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_AnimationData_addMovement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:addMovement");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::AnimationData::*)(cocostudio::MovementData*)>(&cocostudio::AnimationData::addMovement));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_AnimationData_getMovementCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:getMovementCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocostudio::AnimationData::*)()>(&cocostudio::AnimationData::getMovementCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_AnimationData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.AnimationData", "ccs.AnimationData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::AnimationData*(*)()>(&cocostudio::AnimationData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsAnimationData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::AnimationData, "AnimationData", "ccs.AnimationData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addMovement", lua_cocostudio_AnimationData_addMovement);
	LUA_METHOD("getMovementCount", lua_cocostudio_AnimationData_getMovementCount);
	LUA_METHOD("create", lua_cocostudio_AnimationData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ContourData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ContourData", "ccs.ContourData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ContourData::*)()>(&cocostudio::ContourData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ContourData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ContourData", "ccs.ContourData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ContourData*(*)()>(&cocostudio::ContourData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsContourData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ContourData, "ContourData", "ccs.ContourData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocostudio_ContourData_init);
	LUA_METHOD("create", lua_cocostudio_ContourData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_TextureData_addContourData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:addContourData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::TextureData::*)(cocostudio::ContourData*)>(&cocostudio::TextureData::addContourData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_TextureData_getContourData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:getContourData");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::ContourData*(cocostudio::TextureData::*)(int)>(&cocostudio::TextureData::getContourData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_TextureData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureData", "ccs.TextureData:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::TextureData::*)()>(&cocostudio::TextureData::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_TextureData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.TextureData", "ccs.TextureData:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::TextureData*(*)()>(&cocostudio::TextureData::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsTextureData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::TextureData, "TextureData", "ccs.TextureData",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addContourData", lua_cocostudio_TextureData_addContourData);
	LUA_METHOD("getContourData", lua_cocostudio_TextureData_getContourData);
	LUA_METHOD("init", lua_cocostudio_TextureData_init);
	LUA_METHOD("create", lua_cocostudio_TextureData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Tween_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:getAnimation");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureAnimation*(cocostudio::Tween::*)()const>(&cocostudio::Tween::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Tween_gotoAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:gotoAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(int)>(&cocostudio::Tween::gotoAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_gotoAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:gotoAndPlay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(int)>(&cocostudio::Tween::gotoAndPlay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::Tween::*)(cocostudio::Bone*)>(&cocostudio::Tween::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Tween", "ccs.Tween:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Tween::*)(cocostudio::ArmatureAnimation*)>(&cocostudio::Tween::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Tween_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Tween", "ccs.Tween:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::Tween*(*)(cocostudio::Bone*)>(&cocostudio::Tween::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsTween(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Tween, "Tween", "ccs.Tween",
		cocostudio::ProcessBase, "ccs.ProcessBase",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocostudio_Tween_getAnimation);
	LUA_METHOD("gotoAndPause", lua_cocostudio_Tween_gotoAndPause);
	LUA_METHOD("gotoAndPlay", lua_cocostudio_Tween_gotoAndPlay);
	LUA_METHOD("init", lua_cocostudio_Tween_init);
	LUA_METHOD("setAnimation", lua_cocostudio_Tween_setAnimation);
	LUA_METHOD("create", lua_cocostudio_Tween_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_DisplayManager_addDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:addDisplay");
	LUA_TRY_INVOKE_OVERLOAD(2, static_cast<void(cocostudio::DisplayManager::*)(cocos2d::Node*, int)>(&cocostudio::DisplayManager::addDisplay));
	LUA_TRY_INVOKE_OVERLOAD(2, static_cast<void(cocostudio::DisplayManager::*)(cocostudio::DisplayData*, int)>(&cocostudio::DisplayManager::addDisplay));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_DisplayManager_changeDisplayWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:changeDisplayWithIndex");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::DisplayManager::*)(int, bool)>(&cocostudio::DisplayManager::changeDisplayWithIndex));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_DisplayManager_getCurrentDisplayIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getCurrentDisplayIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getCurrentDisplayIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getDisplayRenderNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getDisplayRenderNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getDisplayRenderNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_getDisplayRenderNodeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:getDisplayRenderNodeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayType(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::getDisplayRenderNodeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::DisplayManager::*)(cocostudio::Bone*)>(&cocostudio::DisplayManager::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_isForceChangeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:isForceChangeDisplay");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::isForceChangeDisplay));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:isVisible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::DisplayManager::*)()const>(&cocostudio::DisplayManager::isVisible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_DisplayManager_removeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:removeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(int)>(&cocostudio::DisplayManager::removeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_setForceChangeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:setForceChangeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(bool)>(&cocostudio::DisplayManager::setForceChangeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:setVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::DisplayManager::*)(bool)>(&cocostudio::DisplayManager::setVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_DisplayManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.DisplayManager", "ccs.DisplayManager:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::DisplayManager*(*)(cocostudio::Bone*)>(&cocostudio::DisplayManager::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsDisplayManager(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::DisplayManager, "DisplayManager", "ccs.DisplayManager",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("addDisplay", lua_cocostudio_DisplayManager_addDisplay);
	LUA_METHOD("changeDisplayWithIndex", lua_cocostudio_DisplayManager_changeDisplayWithIndex);
	LUA_METHOD("getCurrentDisplayIndex", lua_cocostudio_DisplayManager_getCurrentDisplayIndex);
	LUA_METHOD("getDisplayRenderNode", lua_cocostudio_DisplayManager_getDisplayRenderNode);
	LUA_METHOD("getDisplayRenderNodeType", lua_cocostudio_DisplayManager_getDisplayRenderNodeType);
	LUA_METHOD("init", lua_cocostudio_DisplayManager_init);
	LUA_METHOD("isForceChangeDisplay", lua_cocostudio_DisplayManager_isForceChangeDisplay);
	LUA_METHOD("isVisible", lua_cocostudio_DisplayManager_isVisible);
	LUA_METHOD("removeDisplay", lua_cocostudio_DisplayManager_removeDisplay);
	LUA_METHOD("setForceChangeDisplay", lua_cocostudio_DisplayManager_setForceChangeDisplay);
	LUA_METHOD("setVisible", lua_cocostudio_DisplayManager_setVisible);
	LUA_METHOD("create", lua_cocostudio_DisplayManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Bone_addChildBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:addChildBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*)>(&cocostudio::Bone::addChildBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_addDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:addDisplay");
	LUA_TRY_INVOKE_OVERLOAD(2, static_cast<void(cocostudio::Bone::*)(cocos2d::Node*, int)>(&cocostudio::Bone::addDisplay));
	LUA_TRY_INVOKE_OVERLOAD(2, static_cast<void(cocostudio::Bone::*)(cocostudio::DisplayData*, int)>(&cocostudio::Bone::addDisplay));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_changeDisplayWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:changeDisplayWithIndex");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::Bone::*)(int, bool)>(&cocostudio::Bone::changeDisplayWithIndex));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_getArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getArmature");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Armature*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getArmature));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getBoneData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BoneData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getBoneData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getChildArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getChildArmature");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Armature*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getChildArmature));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getColliderDetector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getColliderDetector");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ColliderDetector*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getColliderDetector));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayManager");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayManager*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getDisplayManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayRenderNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayRenderNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::Bone::*)()>(&cocostudio::Bone::getDisplayRenderNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getDisplayRenderNodeType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getDisplayRenderNodeType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::DisplayType(cocostudio::Bone::*)()>(&cocostudio::Bone::getDisplayRenderNodeType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getNodeToArmatureTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getNodeToArmatureTransform");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocostudio::Bone::*)()const>(&cocostudio::Bone::getNodeToArmatureTransform));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getParentBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Bone::*)()>(&cocostudio::Bone::getParentBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getTween(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getTween");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Tween*(cocostudio::Bone::*)()>(&cocostudio::Bone::getTween));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getTweenData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getTweenData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::FrameData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getTweenData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_getWorldInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:getWorldInfo");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BaseData*(cocostudio::Bone::*)()const>(&cocostudio::Bone::getWorldInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_isBlendDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isBlendDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()>(&cocostudio::Bone::isBlendDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_isIgnoreMovementBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isIgnoreMovementBoneData");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()const>(&cocostudio::Bone::isIgnoreMovementBoneData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_isTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:isTransformDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Bone::*)()>(&cocostudio::Bone::isTransformDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Bone_removeChildBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:removeChildBone");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*, bool)>(&cocostudio::Bone::removeChildBone));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Bone_removeDisplay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:removeDisplay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(int)>(&cocostudio::Bone::removeDisplay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setArmature");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Armature*)>(&cocostudio::Bone::setArmature));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setBlendDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setBlendDirty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::setBlendDirty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setBoneData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setBoneData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::BoneData*)>(&cocostudio::Bone::setBoneData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setChildArmature(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setChildArmature");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Armature*)>(&cocostudio::Bone::setChildArmature));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setParentBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(cocostudio::Bone*)>(&cocostudio::Bone::setParentBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_setTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:setTransformDirty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Bone::*)(bool)>(&cocostudio::Bone::setTransformDirty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Bone_updateZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Bone", "ccs.Bone:updateZOrder");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Bone::*)()>(&cocostudio::Bone::updateZOrder));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBone(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Bone, "Bone", "ccs.Bone",
		cocos2d::Node, "ccs.cocos2d.Node",
		nullptr, nullptr);
	LUA_METHOD("addChildBone", lua_cocostudio_Bone_addChildBone);
	LUA_METHOD("addDisplay", lua_cocostudio_Bone_addDisplay);
	LUA_METHOD("changeDisplayWithIndex", lua_cocostudio_Bone_changeDisplayWithIndex);
	LUA_METHOD("getArmature", lua_cocostudio_Bone_getArmature);
	LUA_METHOD("getBoneData", lua_cocostudio_Bone_getBoneData);
	LUA_METHOD("getChildArmature", lua_cocostudio_Bone_getChildArmature);
	LUA_METHOD("getColliderDetector", lua_cocostudio_Bone_getColliderDetector);
	LUA_METHOD("getDisplayManager", lua_cocostudio_Bone_getDisplayManager);
	LUA_METHOD("getDisplayRenderNode", lua_cocostudio_Bone_getDisplayRenderNode);
	LUA_METHOD("getDisplayRenderNodeType", lua_cocostudio_Bone_getDisplayRenderNodeType);
	LUA_METHOD("getNodeToArmatureTransform", lua_cocostudio_Bone_getNodeToArmatureTransform);
	LUA_METHOD("getParentBone", lua_cocostudio_Bone_getParentBone);
	LUA_METHOD("getTween", lua_cocostudio_Bone_getTween);
	LUA_METHOD("getTweenData", lua_cocostudio_Bone_getTweenData);
	LUA_METHOD("getWorldInfo", lua_cocostudio_Bone_getWorldInfo);
	LUA_METHOD("isBlendDirty", lua_cocostudio_Bone_isBlendDirty);
	LUA_METHOD("isIgnoreMovementBoneData", lua_cocostudio_Bone_isIgnoreMovementBoneData);
	LUA_METHOD("isTransformDirty", lua_cocostudio_Bone_isTransformDirty);
	LUA_METHOD("removeChildBone", lua_cocostudio_Bone_removeChildBone);
	LUA_METHOD("removeDisplay", lua_cocostudio_Bone_removeDisplay);
	LUA_METHOD("setArmature", lua_cocostudio_Bone_setArmature);
	LUA_METHOD("setBlendDirty", lua_cocostudio_Bone_setBlendDirty);
	LUA_METHOD("setBoneData", lua_cocostudio_Bone_setBoneData);
	LUA_METHOD("setChildArmature", lua_cocostudio_Bone_setChildArmature);
	LUA_METHOD("setParentBone", lua_cocostudio_Bone_setParentBone);
	LUA_METHOD("setTransformDirty", lua_cocostudio_Bone_setTransformDirty);
	LUA_METHOD("updateZOrder", lua_cocostudio_Bone_updateZOrder);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
