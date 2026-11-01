#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_BatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BatchNode", "ccs.BatchNode:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BatchNode*(*)()>(&cocostudio::BatchNode::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::BatchNode, "BatchNode", "ccs.BatchNode",
		cocos2d::Node, "ccs.cocos2d.Node",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_BatchNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureAnimation_getAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getAnimationData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::AnimationData*(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getAnimationData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getCurrentMovementID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getCurrentMovementID");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getCurrentMovementID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getMovementCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getMovementCount");
	LUA_TRY_INVOKE_R(0, static_cast<ssize_t(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getMovementCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_getSpeedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:getSpeedScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ArmatureAnimation::*)()const>(&cocostudio::ArmatureAnimation::getSpeedScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureAnimation_gotoAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:gotoAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(int)>(&cocostudio::ArmatureAnimation::gotoAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_gotoAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:gotoAndPlay");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(int)>(&cocostudio::ArmatureAnimation::gotoAndPlay));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::ArmatureAnimation::*)(cocostudio::Armature*)>(&cocostudio::ArmatureAnimation::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_playWithIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:playWithIndex");
	LUA_TRY_INVOKE(3, static_cast<void(cocostudio::ArmatureAnimation::*)(int, int, int)>(&cocostudio::ArmatureAnimation::playWithIndex));
	LUA_TRY_INVOKE(2, [](cocostudio::ArmatureAnimation* obj,int arg0,int arg1){{return obj->playWithIndex(std::move(arg0),std::move(arg1));}});
	LUA_TRY_INVOKE(1, [](cocostudio::ArmatureAnimation* obj,int arg0){{return obj->playWithIndex(std::move(arg0));}});
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocostudio_ArmatureAnimation_setAnimationData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setAnimationData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(cocostudio::AnimationData*)>(&cocostudio::ArmatureAnimation::setAnimationData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setFrameEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setFrameEventCallFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(std::function<void (cocostudio::Bone *, std::string_view, int, int)>)>(&cocostudio::ArmatureAnimation::setFrameEventCallFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setMovementEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setMovementEventCallFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(std::function<void (cocostudio::Armature *, cocostudio::MovementEventType, std::string_view)>)>(&cocostudio::ArmatureAnimation::setMovementEventCallFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_setSpeedScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:setSpeedScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ArmatureAnimation::*)(float)>(&cocostudio::ArmatureAnimation::setSpeedScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ArmatureAnimation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureAnimation", "ccs.ArmatureAnimation:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::ArmatureAnimation*(*)(cocostudio::Armature*)>(&cocostudio::ArmatureAnimation::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsArmatureAnimation(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureAnimation, "ArmatureAnimation", "ccs.ArmatureAnimation",
		cocostudio::ProcessBase, "ccs.ProcessBase",
		nullptr, nullptr);
	LUA_METHOD("getAnimationData", lua_cocostudio_ArmatureAnimation_getAnimationData);
	LUA_METHOD("getCurrentMovementID", lua_cocostudio_ArmatureAnimation_getCurrentMovementID);
	LUA_METHOD("getMovementCount", lua_cocostudio_ArmatureAnimation_getMovementCount);
	LUA_METHOD("getSpeedScale", lua_cocostudio_ArmatureAnimation_getSpeedScale);
	LUA_METHOD("gotoAndPause", lua_cocostudio_ArmatureAnimation_gotoAndPause);
	LUA_METHOD("gotoAndPlay", lua_cocostudio_ArmatureAnimation_gotoAndPlay);
	LUA_METHOD("init", lua_cocostudio_ArmatureAnimation_init);
	LUA_METHOD("playWithIndex", lua_cocostudio_ArmatureAnimation_playWithIndex);
	LUA_METHOD("setAnimationData", lua_cocostudio_ArmatureAnimation_setAnimationData);
	LUA_METHOD("setFrameEventCallFunc", lua_cocostudio_ArmatureAnimation_setFrameEventCallFunc_1);
	LUA_METHOD("setMovementEventCallFunc", lua_cocostudio_ArmatureAnimation_setMovementEventCallFunc_1);
	LUA_METHOD("setSpeedScale", lua_cocostudio_ArmatureAnimation_setSpeedScale);
	LUA_METHOD("create", lua_cocostudio_ArmatureAnimation_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ArmatureDataManager_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureDataManager::*)()>(&cocostudio::ArmatureDataManager::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_isAutoLoadSpriteFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:isAutoLoadSpriteFile");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ArmatureDataManager::*)()>(&cocostudio::ArmatureDataManager::isAutoLoadSpriteFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_destroyInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:destroyInstance");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocostudio::ArmatureDataManager::destroyInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ArmatureDataManager_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ArmatureDataManager", "ccs.ArmatureDataManager:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureDataManager*(*)()>(&cocostudio::ArmatureDataManager::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmatureDataManager(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ArmatureDataManager, "ArmatureDataManager", "ccs.ArmatureDataManager",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocostudio_ArmatureDataManager_init);
	LUA_METHOD("isAutoLoadSpriteFile", lua_cocostudio_ArmatureDataManager_isAutoLoadSpriteFile);
	LUA_METHOD("destroyInstance", lua_cocostudio_ArmatureDataManager_destroyInstance);
	LUA_METHOD("getInstance", lua_cocostudio_ArmatureDataManager_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Armature_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getAnimation");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureAnimation*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getArmatureData");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ArmatureData*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getArmatureData));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getArmatureTransformDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getArmatureTransformDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::Armature::*)()const>(&cocostudio::Armature::getArmatureTransformDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBatchNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::BatchNode*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getBatchNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getBoneAtPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getBoneAtPoint");
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::Bone*(cocostudio::Armature::*)(float, float)const>(&cocostudio::Armature::getBoneAtPoint));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_getParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getParentBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Armature::*)()const>(&cocostudio::Armature::getParentBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:getVersion");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::Armature::*)()const>(&cocostudio::Armature::getVersion));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Armature_removeBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:removeBone");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*, bool)>(&cocostudio::Armature::removeBone));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_Armature_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::ArmatureAnimation*)>(&cocostudio::Armature::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setArmatureData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setArmatureData");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::ArmatureData*)>(&cocostudio::Armature::setArmatureData));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setBatchNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::BatchNode*)>(&cocostudio::Armature::setBatchNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setParentBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setParentBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(cocostudio::Bone*)>(&cocostudio::Armature::setParentBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_setVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:setVersion");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Armature::*)(float)>(&cocostudio::Armature::setVersion));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Armature_updateOffsetPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Armature", "ccs.Armature:updateOffsetPoint");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Armature::*)()>(&cocostudio::Armature::updateOffsetPoint));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Studio_ccsArmature(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Armature, "Armature", "ccs.Armature",
		cocos2d::Node, "ccs.cocos2d.Node",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocostudio_Armature_getAnimation);
	LUA_METHOD("getArmatureData", lua_cocostudio_Armature_getArmatureData);
	LUA_METHOD("getArmatureTransformDirty", lua_cocostudio_Armature_getArmatureTransformDirty);
	LUA_METHOD("getBatchNode", lua_cocostudio_Armature_getBatchNode);
	LUA_METHOD("getBoneAtPoint", lua_cocostudio_Armature_getBoneAtPoint);
	LUA_METHOD("getParentBone", lua_cocostudio_Armature_getParentBone);
	LUA_METHOD("getVersion", lua_cocostudio_Armature_getVersion);
	LUA_METHOD("removeBone", lua_cocostudio_Armature_removeBone);
	LUA_METHOD("setAnimation", lua_cocostudio_Armature_setAnimation);
	LUA_METHOD("setArmatureData", lua_cocostudio_Armature_setArmatureData);
	LUA_METHOD("setBatchNode", lua_cocostudio_Armature_setBatchNode);
	LUA_METHOD("setParentBone", lua_cocostudio_Armature_setParentBone);
	LUA_METHOD("setVersion", lua_cocostudio_Armature_setVersion);
	LUA_METHOD("updateOffsetPoint", lua_cocostudio_Armature_updateOffsetPoint);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_Skin_getBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getBone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::Bone*(cocostudio::Skin::*)()const>(&cocostudio::Skin::getBone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_getDisplayName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getDisplayName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::Skin::*)()const>(&cocostudio::Skin::getDisplayName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_getNodeToWorldTransformAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:getNodeToWorldTransformAR");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Mat4(cocostudio::Skin::*)()const>(&cocostudio::Skin::getNodeToWorldTransformAR));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_Skin_setBone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:setBone");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::Skin::*)(cocostudio::Bone*)>(&cocostudio::Skin::setBone));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_Skin_updateArmatureTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Skin", "ccs.Skin:updateArmatureTransform");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::Skin::*)()>(&cocostudio::Skin::updateArmatureTransform));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSkin(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::Skin, "Skin", "ccs.Skin",
		cocos2d::Sprite, "ccs.cocos2d.Sprite",
		nullptr, nullptr);
	LUA_METHOD("getBone", lua_cocostudio_Skin_getBone);
	LUA_METHOD("getDisplayName", lua_cocostudio_Skin_getDisplayName);
	LUA_METHOD("getNodeToWorldTransformAR", lua_cocostudio_Skin_getNodeToWorldTransformAR);
	LUA_METHOD("setBone", lua_cocostudio_Skin_setBone);
	LUA_METHOD("updateArmatureTransform", lua_cocostudio_Skin_updateArmatureTransform);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ComAttribute_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComAttribute*(*)()>(&cocostudio::ComAttribute::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComAttribute_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAttribute", "ccs.ComAttribute:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComAttribute::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComAttribute(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComAttribute, "ComAttribute", "ccs.ComAttribute",
		cocos2d::Component, "ccs.cocos2d.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ComAttribute_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComAttribute_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ComAudio_endToLua(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:endToLua");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::end));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_getBackgroundMusicVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:getBackgroundMusicVolume");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::getBackgroundMusicVolume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_getEffectsVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:getEffectsVolume");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::getEffectsVolume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_getFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:getFile");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::getFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_isBackgroundMusicPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:isBackgroundMusicPlaying");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::isBackgroundMusicPlaying));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_isLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:isLoop");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::isLoop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_pauseAllEffects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:pauseAllEffects");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::pauseAllEffects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_pauseBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:pauseBackgroundMusic");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::pauseBackgroundMusic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_pauseEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:pauseEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(unsigned int)>(&cocostudio::ComAudio::pauseEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_playBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:playBackgroundMusic");
	LUA_TRY_INVOKE(2, static_cast<void(cocostudio::ComAudio::*)(const char*, bool)>(&cocostudio::ComAudio::playBackgroundMusic));
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::playBackgroundMusic));
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::playBackgroundMusic));
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocostudio_ComAudio_playEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:playEffect");
	LUA_TRY_INVOKE_R(2, static_cast<unsigned int(cocostudio::ComAudio::*)(const char*, bool)>(&cocostudio::ComAudio::playEffect));
	LUA_TRY_INVOKE_R(1, static_cast<unsigned int(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::playEffect));
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::playEffect));
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocostudio_ComAudio_preloadBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:preloadBackgroundMusic");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::preloadBackgroundMusic));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_preloadEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:preloadEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::preloadEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_resumeAllEffects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:resumeAllEffects");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::resumeAllEffects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_resumeBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:resumeBackgroundMusic");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::resumeBackgroundMusic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_resumeEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:resumeEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(unsigned int)>(&cocostudio::ComAudio::resumeEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_rewindBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:rewindBackgroundMusic");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::rewindBackgroundMusic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_setBackgroundMusicVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:setBackgroundMusicVolume");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(float)>(&cocostudio::ComAudio::setBackgroundMusicVolume));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_setEffectsVolume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:setEffectsVolume");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(float)>(&cocostudio::ComAudio::setEffectsVolume));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_setFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:setFile");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::setFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_setLoop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:setLoop");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(bool)>(&cocostudio::ComAudio::setLoop));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_stopAllEffects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:stopAllEffects");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::stopAllEffects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_stopBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:stopBackgroundMusic");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(bool)>(&cocostudio::ComAudio::stopBackgroundMusic));
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::stopBackgroundMusic));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocostudio_ComAudio_stopEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:stopEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(unsigned int)>(&cocostudio::ComAudio::stopEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_unloadEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:unloadEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::unloadEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComAudio_willPlayBackgroundMusic(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:willPlayBackgroundMusic");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::willPlayBackgroundMusic));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComAudio*(*)()>(&cocostudio::ComAudio::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComAudio::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComAudio(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComAudio, "ComAudio", "ccs.ComAudio",
		cocos2d::Component, "ccs.cocos2d.Component",
		nullptr, nullptr);
	LUA_METHOD("endToLua", lua_cocostudio_ComAudio_endToLua);
	LUA_METHOD("getBackgroundMusicVolume", lua_cocostudio_ComAudio_getBackgroundMusicVolume);
	LUA_METHOD("getEffectsVolume", lua_cocostudio_ComAudio_getEffectsVolume);
	LUA_METHOD("getFile", lua_cocostudio_ComAudio_getFile);
	LUA_METHOD("isBackgroundMusicPlaying", lua_cocostudio_ComAudio_isBackgroundMusicPlaying);
	LUA_METHOD("isLoop", lua_cocostudio_ComAudio_isLoop);
	LUA_METHOD("pauseAllEffects", lua_cocostudio_ComAudio_pauseAllEffects);
	LUA_METHOD("pauseBackgroundMusic", lua_cocostudio_ComAudio_pauseBackgroundMusic);
	LUA_METHOD("pauseEffect", lua_cocostudio_ComAudio_pauseEffect);
	LUA_METHOD("playBackgroundMusic", lua_cocostudio_ComAudio_playBackgroundMusic);
	LUA_METHOD("playEffect", lua_cocostudio_ComAudio_playEffect);
	LUA_METHOD("preloadBackgroundMusic", lua_cocostudio_ComAudio_preloadBackgroundMusic);
	LUA_METHOD("preloadEffect", lua_cocostudio_ComAudio_preloadEffect);
	LUA_METHOD("resumeAllEffects", lua_cocostudio_ComAudio_resumeAllEffects);
	LUA_METHOD("resumeBackgroundMusic", lua_cocostudio_ComAudio_resumeBackgroundMusic);
	LUA_METHOD("resumeEffect", lua_cocostudio_ComAudio_resumeEffect);
	LUA_METHOD("rewindBackgroundMusic", lua_cocostudio_ComAudio_rewindBackgroundMusic);
	LUA_METHOD("setBackgroundMusicVolume", lua_cocostudio_ComAudio_setBackgroundMusicVolume);
	LUA_METHOD("setEffectsVolume", lua_cocostudio_ComAudio_setEffectsVolume);
	LUA_METHOD("setFile", lua_cocostudio_ComAudio_setFile);
	LUA_METHOD("setLoop", lua_cocostudio_ComAudio_setLoop);
	LUA_METHOD("stopAllEffects", lua_cocostudio_ComAudio_stopAllEffects);
	LUA_METHOD("stopBackgroundMusic", lua_cocostudio_ComAudio_stopBackgroundMusic);
	LUA_METHOD("stopEffect", lua_cocostudio_ComAudio_stopEffect);
	LUA_METHOD("unloadEffect", lua_cocostudio_ComAudio_unloadEffect);
	LUA_METHOD("willPlayBackgroundMusic", lua_cocostudio_ComAudio_willPlayBackgroundMusic);
	LUA_METHOD("create", lua_cocostudio_ComAudio_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComAudio_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_ComController_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComController", "ccs.ComController:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComController*(*)()>(&cocostudio::ComController::create));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_ComController_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComController", "ccs.ComController:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComController::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComController(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComController, "ComController", "ccs.ComController",
		cocos2d::Component, "ccs.cocos2d.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ComController_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComController_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
