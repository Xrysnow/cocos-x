#pragma once
#include "lua_conversion/lua_conversion.hpp"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include <cstring>
#include <cstdio>


// The Studio profile parses only cocostudio, so identically named cocos classes
// cannot become duplicate automatic definitions. Resolve inherited type names
// through the existing runtime registration (cc.Node, cc.Action, cc.Ref, etc.).
int register_all_cc_studio_retained(lua_State* L);

namespace studio_binding
{
template<typename T> struct callback_type : std::false_type {};
template<typename R, typename... Args>
struct callback_type<std::function<R(Args...)>> : std::true_type {};

template<typename Arg>
bool prepare_value(lua_State* L, int index, const char* name)
{
	using T = std::remove_cv_t<std::remove_reference_t<Arg>>;
	if constexpr (std::is_enum_v<T> || std::is_same_v<T, int>) {
		int value;
		if (!luaval_to_int32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_same_v<T, unsigned int>) {
		unsigned int value;
		if (!luaval_to_uint32(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (std::is_floating_point_v<T>) {
		double value;
		if (!luaval_to_number(L, index, &value, name)) return false;
		lua_pushnumber(L, value); lua_replace(L, index);
	} else if constexpr (callback_type<T>::value) {
		return lua_isfunction(L, index);
	}
	return true;
}

template<typename... Args, size_t... Index>
bool prepare_arguments(lua_State* L, const char* name, std::index_sequence<Index...>)
{
	const int first = lua_gettop(L) - int(sizeof...(Args)) + 1;
	return (prepare_value<Args>(L, first + int(Index), name) && ...);
}

template<typename T> struct prepare_signature;
template<typename R, typename... Args>
struct prepare_signature<R(*)(Args...)> {
	static bool run(lua_State* L, const char* name) {
		return prepare_arguments<Args...>(L, name, std::index_sequence_for<Args...>{});
	}
};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...)> : prepare_signature<R(*)(Args...)> {};
template<typename C, typename R, typename... Args>
struct prepare_signature<R(C::*)(Args...) const> : prepare_signature<R(*)(Args...)> {};


template<typename T> const char* parent_name(const char* fallback) {
    const auto* registered=lua::_getClassNameByType<T>();
    return *registered ? registered : fallback;
}
inline bool callback_entry(const char* name) {
    return std::strcmp(name, "ccs.ArmatureAnimation:setMovementEventCallFunc") == 0
        || std::strcmp(name, "ccs.ArmatureAnimation:setFrameEventCallFunc") == 0
        || std::strcmp(name, "ccs.ActionTimeline:setFrameEventCallFunc") == 0;
}
inline const char* native_symbol(const char* name) {
    if (std::strcmp(name, "ccs.ActionFrame:getAction") == 0) return "lua_cc_studio_ActionFrame_getAction";
    if (std::strcmp(name, "ccs.ActionFrame:getEasingType") == 0) return "lua_cc_studio_ActionFrame_getEasingType";
    if (std::strcmp(name, "ccs.ActionFrame:getFrameIndex") == 0) return "lua_cc_studio_ActionFrame_getFrameIndex";
    if (std::strcmp(name, "ccs.ActionFrame:getFrameTime") == 0) return "lua_cc_studio_ActionFrame_getFrameTime";
    if (std::strcmp(name, "ccs.ActionFrame:getFrameType") == 0) return "lua_cc_studio_ActionFrame_getFrameType";
    if (std::strcmp(name, "ccs.ActionFrame:setEasingType") == 0) return "lua_cc_studio_ActionFrame_setEasingType";
    if (std::strcmp(name, "ccs.ActionFrame:setFrameIndex") == 0) return "lua_cc_studio_ActionFrame_setFrameIndex";
    if (std::strcmp(name, "ccs.ActionFrame:setFrameTime") == 0) return "lua_cc_studio_ActionFrame_setFrameTime";
    if (std::strcmp(name, "ccs.ActionFrame:setFrameType") == 0) return "lua_cc_studio_ActionFrame_setFrameType";
    if (std::strcmp(name, "ccs.ActionScaleFrame:getScaleX") == 0) return "lua_cc_studio_ActionScaleFrame_getScaleX";
    if (std::strcmp(name, "ccs.ActionScaleFrame:getScaleY") == 0) return "lua_cc_studio_ActionScaleFrame_getScaleY";
    if (std::strcmp(name, "ccs.ActionScaleFrame:setScaleX") == 0) return "lua_cc_studio_ActionScaleFrame_setScaleX";
    if (std::strcmp(name, "ccs.ActionScaleFrame:setScaleY") == 0) return "lua_cc_studio_ActionScaleFrame_setScaleY";
    if (std::strcmp(name, "ccs.ActionRotationFrame:getRotation") == 0) return "lua_cc_studio_ActionRotationFrame_getRotation";
    if (std::strcmp(name, "ccs.ActionRotationFrame:setRotation") == 0) return "lua_cc_studio_ActionRotationFrame_setRotation";
    if (std::strcmp(name, "ccs.ActionFadeFrame:getOpacity") == 0) return "lua_cc_studio_ActionFadeFrame_getOpacity";
    if (std::strcmp(name, "ccs.ActionFadeFrame:setOpacity") == 0) return "lua_cc_studio_ActionFadeFrame_setOpacity";
    if (std::strcmp(name, "ccs.ActionObject:addActionNode") == 0) return "lua_cc_studio_ActionObject_addActionNode";
    if (std::strcmp(name, "ccs.ActionObject:getCurrentTime") == 0) return "lua_cc_studio_ActionObject_getCurrentTime";
    if (std::strcmp(name, "ccs.ActionObject:getLoop") == 0) return "lua_cc_studio_ActionObject_getLoop";
    if (std::strcmp(name, "ccs.ActionObject:getName") == 0) return "lua_cc_studio_ActionObject_getName";
    if (std::strcmp(name, "ccs.ActionObject:getTotalTime") == 0) return "lua_cc_studio_ActionObject_getTotalTime";
    if (std::strcmp(name, "ccs.ActionObject:getUnitTime") == 0) return "lua_cc_studio_ActionObject_getUnitTime";
    if (std::strcmp(name, "ccs.ActionObject:isPlaying") == 0) return "lua_cc_studio_ActionObject_isPlaying";
    if (std::strcmp(name, "ccs.ActionObject:pause") == 0) return "lua_cc_studio_ActionObject_pause";
    if (std::strcmp(name, "ccs.ActionObject:play") == 0) return "lua_cc_studio_ActionObject_play";
    if (std::strcmp(name, "ccs.ActionObject:removeActionNode") == 0) return "lua_cc_studio_ActionObject_removeActionNode";
    if (std::strcmp(name, "ccs.ActionObject:setCurrentTime") == 0) return "lua_cc_studio_ActionObject_setCurrentTime";
    if (std::strcmp(name, "ccs.ActionObject:setLoop") == 0) return "lua_cc_studio_ActionObject_setLoop";
    if (std::strcmp(name, "ccs.ActionObject:setName") == 0) return "lua_cc_studio_ActionObject_setName";
    if (std::strcmp(name, "ccs.ActionObject:setUnitTime") == 0) return "lua_cc_studio_ActionObject_setUnitTime";
    if (std::strcmp(name, "ccs.ActionObject:simulationActionUpdate") == 0) return "lua_cc_studio_ActionObject_simulationActionUpdate";
    if (std::strcmp(name, "ccs.ActionObject:stop") == 0) return "lua_cc_studio_ActionObject_stop";
    if (std::strcmp(name, "ccs.ActionObject:updateToFrameByTime") == 0) return "lua_cc_studio_ActionObject_updateToFrameByTime";
    if (std::strcmp(name, "ccs.ActionManagerEx:getActionByName") == 0) return "lua_cc_studio_ActionManagerEx_getActionByName";
    if (std::strcmp(name, "ccs.ActionManagerEx:getStudioVersionNumber") == 0) return "lua_cc_studio_ActionManagerEx_getStudioVersionNumber";
    if (std::strcmp(name, "ccs.ActionManagerEx:playActionByName") == 0) return "lua_cc_studio_ActionManagerEx_playActionByName";
    if (std::strcmp(name, "ccs.ActionManagerEx:releaseActions") == 0) return "lua_cc_studio_ActionManagerEx_releaseActions";
    if (std::strcmp(name, "ccs.ActionManagerEx:stopActionByName") == 0) return "lua_cc_studio_ActionManagerEx_stopActionByName";
    if (std::strcmp(name, "ccs.BaseData:create") == 0) return "lua_cc_studio_BaseData_create";
    if (std::strcmp(name, "ccs.DisplayData:copy") == 0) return "lua_cc_studio_DisplayData_copy";
    if (std::strcmp(name, "ccs.DisplayData:create") == 0) return "lua_cc_studio_DisplayData_create";
    if (std::strcmp(name, "ccs.SpriteDisplayData:create") == 0) return "lua_cc_studio_SpriteDisplayData_create";
    if (std::strcmp(name, "ccs.ArmatureDisplayData:create") == 0) return "lua_cc_studio_ArmatureDisplayData_create";
    if (std::strcmp(name, "ccs.ParticleDisplayData:create") == 0) return "lua_cc_studio_ParticleDisplayData_create";
    if (std::strcmp(name, "ccs.BoneData:addDisplayData") == 0) return "lua_cc_studio_BoneData_addDisplayData";
    if (std::strcmp(name, "ccs.BoneData:create") == 0) return "lua_cc_studio_BoneData_create";
    if (std::strcmp(name, "ccs.BoneData:getDisplayData") == 0) return "lua_cc_studio_BoneData_getDisplayData";
    if (std::strcmp(name, "ccs.BoneData:init") == 0) return "lua_cc_studio_BoneData_init";
    if (std::strcmp(name, "ccs.ArmatureData:addBoneData") == 0) return "lua_cc_studio_ArmatureData_addBoneData";
    if (std::strcmp(name, "ccs.ArmatureData:create") == 0) return "lua_cc_studio_ArmatureData_create";
    if (std::strcmp(name, "ccs.ArmatureData:init") == 0) return "lua_cc_studio_ArmatureData_init";
    if (std::strcmp(name, "ccs.FrameData:create") == 0) return "lua_cc_studio_FrameData_create";
    if (std::strcmp(name, "ccs.MovementBoneData:addFrameData") == 0) return "lua_cc_studio_MovementBoneData_addFrameData";
    if (std::strcmp(name, "ccs.MovementBoneData:create") == 0) return "lua_cc_studio_MovementBoneData_create";
    if (std::strcmp(name, "ccs.MovementBoneData:getFrameData") == 0) return "lua_cc_studio_MovementBoneData_getFrameData";
    if (std::strcmp(name, "ccs.MovementBoneData:init") == 0) return "lua_cc_studio_MovementBoneData_init";
    if (std::strcmp(name, "ccs.MovementData:addMovementBoneData") == 0) return "lua_cc_studio_MovementData_addMovementBoneData";
    if (std::strcmp(name, "ccs.MovementData:create") == 0) return "lua_cc_studio_MovementData_create";
    if (std::strcmp(name, "ccs.AnimationData:addMovement") == 0) return "lua_cc_studio_AnimationData_addMovement";
    if (std::strcmp(name, "ccs.AnimationData:create") == 0) return "lua_cc_studio_AnimationData_create";
    if (std::strcmp(name, "ccs.AnimationData:getMovementCount") == 0) return "lua_cc_studio_AnimationData_getMovementCount";
    if (std::strcmp(name, "ccs.ContourData:create") == 0) return "lua_cc_studio_ContourData_create";
    if (std::strcmp(name, "ccs.ContourData:init") == 0) return "lua_cc_studio_ContourData_init";
    if (std::strcmp(name, "ccs.TextureData:addContourData") == 0) return "lua_cc_studio_TextureData_addContourData";
    if (std::strcmp(name, "ccs.TextureData:create") == 0) return "lua_cc_studio_TextureData_create";
    if (std::strcmp(name, "ccs.TextureData:getContourData") == 0) return "lua_cc_studio_TextureData_getContourData";
    if (std::strcmp(name, "ccs.TextureData:init") == 0) return "lua_cc_studio_TextureData_init";
    if (std::strcmp(name, "ccs.Tween:create") == 0) return "lua_cc_studio_Tween_create";
    if (std::strcmp(name, "ccs.Tween:getAnimation") == 0) return "lua_cc_studio_Tween_getAnimation";
    if (std::strcmp(name, "ccs.Tween:gotoAndPause") == 0) return "lua_cc_studio_Tween_gotoAndPause";
    if (std::strcmp(name, "ccs.Tween:gotoAndPlay") == 0) return "lua_cc_studio_Tween_gotoAndPlay";
    if (std::strcmp(name, "ccs.Tween:init") == 0) return "lua_cc_studio_Tween_init";
    if (std::strcmp(name, "ccs.Tween:setAnimation") == 0) return "lua_cc_studio_Tween_setAnimation";
    if (std::strcmp(name, "ccs.DisplayManager:addDisplay") == 0) return "lua_cc_studio_DisplayManager_addDisplay";
    if (std::strcmp(name, "ccs.DisplayManager:changeDisplayWithIndex") == 0) return "lua_cc_studio_DisplayManager_changeDisplayWithIndex";
    if (std::strcmp(name, "ccs.DisplayManager:create") == 0) return "lua_cc_studio_DisplayManager_create";
    if (std::strcmp(name, "ccs.DisplayManager:getCurrentDisplayIndex") == 0) return "lua_cc_studio_DisplayManager_getCurrentDisplayIndex";
    if (std::strcmp(name, "ccs.DisplayManager:getDisplayRenderNode") == 0) return "lua_cc_studio_DisplayManager_getDisplayRenderNode";
    if (std::strcmp(name, "ccs.DisplayManager:getDisplayRenderNodeType") == 0) return "lua_cc_studio_DisplayManager_getDisplayRenderNodeType";
    if (std::strcmp(name, "ccs.DisplayManager:init") == 0) return "lua_cc_studio_DisplayManager_init";
    if (std::strcmp(name, "ccs.DisplayManager:isForceChangeDisplay") == 0) return "lua_cc_studio_DisplayManager_isForceChangeDisplay";
    if (std::strcmp(name, "ccs.DisplayManager:isVisible") == 0) return "lua_cc_studio_DisplayManager_isVisible";
    if (std::strcmp(name, "ccs.DisplayManager:removeDisplay") == 0) return "lua_cc_studio_DisplayManager_removeDisplay";
    if (std::strcmp(name, "ccs.DisplayManager:setForceChangeDisplay") == 0) return "lua_cc_studio_DisplayManager_setForceChangeDisplay";
    if (std::strcmp(name, "ccs.DisplayManager:setVisible") == 0) return "lua_cc_studio_DisplayManager_setVisible";
    if (std::strcmp(name, "ccs.Bone:addChildBone") == 0) return "lua_cc_studio_Bone_addChildBone";
    if (std::strcmp(name, "ccs.Bone:addDisplay") == 0) return "lua_cc_studio_Bone_addDisplay";
    if (std::strcmp(name, "ccs.Bone:changeDisplayWithIndex") == 0) return "lua_cc_studio_Bone_changeDisplayWithIndex";
    if (std::strcmp(name, "ccs.Bone:getArmature") == 0) return "lua_cc_studio_Bone_getArmature";
    if (std::strcmp(name, "ccs.Bone:getBoneData") == 0) return "lua_cc_studio_Bone_getBoneData";
    if (std::strcmp(name, "ccs.Bone:getChildArmature") == 0) return "lua_cc_studio_Bone_getChildArmature";
    if (std::strcmp(name, "ccs.Bone:getColliderDetector") == 0) return "lua_cc_studio_Bone_getColliderDetector";
    if (std::strcmp(name, "ccs.Bone:getDisplayManager") == 0) return "lua_cc_studio_Bone_getDisplayManager";
    if (std::strcmp(name, "ccs.Bone:getDisplayRenderNode") == 0) return "lua_cc_studio_Bone_getDisplayRenderNode";
    if (std::strcmp(name, "ccs.Bone:getDisplayRenderNodeType") == 0) return "lua_cc_studio_Bone_getDisplayRenderNodeType";
    if (std::strcmp(name, "ccs.Bone:getNodeToArmatureTransform") == 0) return "lua_cc_studio_Bone_getNodeToArmatureTransform";
    if (std::strcmp(name, "ccs.Bone:getParentBone") == 0) return "lua_cc_studio_Bone_getParentBone";
    if (std::strcmp(name, "ccs.Bone:getTween") == 0) return "lua_cc_studio_Bone_getTween";
    if (std::strcmp(name, "ccs.Bone:getTweenData") == 0) return "lua_cc_studio_Bone_getTweenData";
    if (std::strcmp(name, "ccs.Bone:getWorldInfo") == 0) return "lua_cc_studio_Bone_getWorldInfo";
    if (std::strcmp(name, "ccs.Bone:isBlendDirty") == 0) return "lua_cc_studio_Bone_isBlendDirty";
    if (std::strcmp(name, "ccs.Bone:isIgnoreMovementBoneData") == 0) return "lua_cc_studio_Bone_isIgnoreMovementBoneData";
    if (std::strcmp(name, "ccs.Bone:isTransformDirty") == 0) return "lua_cc_studio_Bone_isTransformDirty";
    if (std::strcmp(name, "ccs.Bone:removeChildBone") == 0) return "lua_cc_studio_Bone_removeChildBone";
    if (std::strcmp(name, "ccs.Bone:removeDisplay") == 0) return "lua_cc_studio_Bone_removeDisplay";
    if (std::strcmp(name, "ccs.Bone:setArmature") == 0) return "lua_cc_studio_Bone_setArmature";
    if (std::strcmp(name, "ccs.Bone:setBlendDirty") == 0) return "lua_cc_studio_Bone_setBlendDirty";
    if (std::strcmp(name, "ccs.Bone:setBoneData") == 0) return "lua_cc_studio_Bone_setBoneData";
    if (std::strcmp(name, "ccs.Bone:setChildArmature") == 0) return "lua_cc_studio_Bone_setChildArmature";
    if (std::strcmp(name, "ccs.Bone:setParentBone") == 0) return "lua_cc_studio_Bone_setParentBone";
    if (std::strcmp(name, "ccs.Bone:setTransformDirty") == 0) return "lua_cc_studio_Bone_setTransformDirty";
    if (std::strcmp(name, "ccs.Bone:updateZOrder") == 0) return "lua_cc_studio_Bone_updateZOrder";
    if (std::strcmp(name, "ccs.BatchNode:create") == 0) return "lua_cc_studio_BatchNode_create";
    if (std::strcmp(name, "ccs.ArmatureAnimation:create") == 0) return "lua_cc_studio_ArmatureAnimation_create";
    if (std::strcmp(name, "ccs.ArmatureAnimation:getAnimationData") == 0) return "lua_cc_studio_ArmatureAnimation_getAnimationData";
    if (std::strcmp(name, "ccs.ArmatureAnimation:getCurrentMovementID") == 0) return "lua_cc_studio_ArmatureAnimation_getCurrentMovementID";
    if (std::strcmp(name, "ccs.ArmatureAnimation:getMovementCount") == 0) return "lua_cc_studio_ArmatureAnimation_getMovementCount";
    if (std::strcmp(name, "ccs.ArmatureAnimation:getSpeedScale") == 0) return "lua_cc_studio_ArmatureAnimation_getSpeedScale";
    if (std::strcmp(name, "ccs.ArmatureAnimation:gotoAndPause") == 0) return "lua_cc_studio_ArmatureAnimation_gotoAndPause";
    if (std::strcmp(name, "ccs.ArmatureAnimation:gotoAndPlay") == 0) return "lua_cc_studio_ArmatureAnimation_gotoAndPlay";
    if (std::strcmp(name, "ccs.ArmatureAnimation:init") == 0) return "lua_cc_studio_ArmatureAnimation_init";
    if (std::strcmp(name, "ccs.ArmatureAnimation:playWithIndex") == 0) return "lua_cc_studio_ArmatureAnimation_playWithIndex";
    if (std::strcmp(name, "ccs.ArmatureAnimation:setAnimationData") == 0) return "lua_cc_studio_ArmatureAnimation_setAnimationData";
    if (std::strcmp(name, "ccs.ArmatureAnimation:setSpeedScale") == 0) return "lua_cc_studio_ArmatureAnimation_setSpeedScale";
    if (std::strcmp(name, "ccs.ArmatureDataManager:destroyInstance") == 0) return "lua_cc_studio_ArmatureDataManager_destroyInstance";
    if (std::strcmp(name, "ccs.ArmatureDataManager:getInstance") == 0) return "lua_cc_studio_ArmatureDataManager_getInstance";
    if (std::strcmp(name, "ccs.ArmatureDataManager:init") == 0) return "lua_cc_studio_ArmatureDataManager_init";
    if (std::strcmp(name, "ccs.ArmatureDataManager:isAutoLoadSpriteFile") == 0) return "lua_cc_studio_ArmatureDataManager_isAutoLoadSpriteFile";
    if (std::strcmp(name, "ccs.Armature:getAnimation") == 0) return "lua_cc_studio_Armature_getAnimation";
    if (std::strcmp(name, "ccs.Armature:getArmatureData") == 0) return "lua_cc_studio_Armature_getArmatureData";
    if (std::strcmp(name, "ccs.Armature:getArmatureTransformDirty") == 0) return "lua_cc_studio_Armature_getArmatureTransformDirty";
    if (std::strcmp(name, "ccs.Armature:getBatchNode") == 0) return "lua_cc_studio_Armature_getBatchNode";
    if (std::strcmp(name, "ccs.Armature:getBoneAtPoint") == 0) return "lua_cc_studio_Armature_getBoneAtPoint";
    if (std::strcmp(name, "ccs.Armature:getParentBone") == 0) return "lua_cc_studio_Armature_getParentBone";
    if (std::strcmp(name, "ccs.Armature:getVersion") == 0) return "lua_cc_studio_Armature_getVersion";
    if (std::strcmp(name, "ccs.Armature:removeBone") == 0) return "lua_cc_studio_Armature_removeBone";
    if (std::strcmp(name, "ccs.Armature:setAnimation") == 0) return "lua_cc_studio_Armature_setAnimation";
    if (std::strcmp(name, "ccs.Armature:setArmatureData") == 0) return "lua_cc_studio_Armature_setArmatureData";
    if (std::strcmp(name, "ccs.Armature:setBatchNode") == 0) return "lua_cc_studio_Armature_setBatchNode";
    if (std::strcmp(name, "ccs.Armature:setParentBone") == 0) return "lua_cc_studio_Armature_setParentBone";
    if (std::strcmp(name, "ccs.Armature:setVersion") == 0) return "lua_cc_studio_Armature_setVersion";
    if (std::strcmp(name, "ccs.Armature:updateOffsetPoint") == 0) return "lua_cc_studio_Armature_updateOffsetPoint";
    if (std::strcmp(name, "ccs.Skin:getBone") == 0) return "lua_cc_studio_Skin_getBone";
    if (std::strcmp(name, "ccs.Skin:getDisplayName") == 0) return "lua_cc_studio_Skin_getDisplayName";
    if (std::strcmp(name, "ccs.Skin:getNodeToWorldTransformAR") == 0) return "lua_cc_studio_Skin_getNodeToWorldTransformAR";
    if (std::strcmp(name, "ccs.Skin:setBone") == 0) return "lua_cc_studio_Skin_setBone";
    if (std::strcmp(name, "ccs.Skin:updateArmatureTransform") == 0) return "lua_cc_studio_Skin_updateArmatureTransform";
    if (std::strcmp(name, "ccs.ComAttribute:create") == 0) return "lua_cc_studio_ComAttribute_create";
    if (std::strcmp(name, "ccs.ComAttribute:createInstance") == 0) return "lua_cc_studio_ComAttribute_createInstance";
    if (std::strcmp(name, "ccs.ComAudio:create") == 0) return "lua_cc_studio_ComAudio_create";
    if (std::strcmp(name, "ccs.ComAudio:createInstance") == 0) return "lua_cc_studio_ComAudio_createInstance";
    if (std::strcmp(name, "ccs.ComAudio:endToLua") == 0) return "lua_cc_studio_ComAudio_end";
    if (std::strcmp(name, "ccs.ComAudio:getBackgroundMusicVolume") == 0) return "lua_cc_studio_ComAudio_getBackgroundMusicVolume";
    if (std::strcmp(name, "ccs.ComAudio:getEffectsVolume") == 0) return "lua_cc_studio_ComAudio_getEffectsVolume";
    if (std::strcmp(name, "ccs.ComAudio:getFile") == 0) return "lua_cc_studio_ComAudio_getFile";
    if (std::strcmp(name, "ccs.ComAudio:isBackgroundMusicPlaying") == 0) return "lua_cc_studio_ComAudio_isBackgroundMusicPlaying";
    if (std::strcmp(name, "ccs.ComAudio:isLoop") == 0) return "lua_cc_studio_ComAudio_isLoop";
    if (std::strcmp(name, "ccs.ComAudio:pauseAllEffects") == 0) return "lua_cc_studio_ComAudio_pauseAllEffects";
    if (std::strcmp(name, "ccs.ComAudio:pauseBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_pauseBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:pauseEffect") == 0) return "lua_cc_studio_ComAudio_pauseEffect";
    if (std::strcmp(name, "ccs.ComAudio:playBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_playBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:playEffect") == 0) return "lua_cc_studio_ComAudio_playEffect";
    if (std::strcmp(name, "ccs.ComAudio:preloadBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_preloadBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:preloadEffect") == 0) return "lua_cc_studio_ComAudio_preloadEffect";
    if (std::strcmp(name, "ccs.ComAudio:resumeAllEffects") == 0) return "lua_cc_studio_ComAudio_resumeAllEffects";
    if (std::strcmp(name, "ccs.ComAudio:resumeBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_resumeBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:resumeEffect") == 0) return "lua_cc_studio_ComAudio_resumeEffect";
    if (std::strcmp(name, "ccs.ComAudio:rewindBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_rewindBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:setBackgroundMusicVolume") == 0) return "lua_cc_studio_ComAudio_setBackgroundMusicVolume";
    if (std::strcmp(name, "ccs.ComAudio:setEffectsVolume") == 0) return "lua_cc_studio_ComAudio_setEffectsVolume";
    if (std::strcmp(name, "ccs.ComAudio:setFile") == 0) return "lua_cc_studio_ComAudio_setFile";
    if (std::strcmp(name, "ccs.ComAudio:setLoop") == 0) return "lua_cc_studio_ComAudio_setLoop";
    if (std::strcmp(name, "ccs.ComAudio:stopAllEffects") == 0) return "lua_cc_studio_ComAudio_stopAllEffects";
    if (std::strcmp(name, "ccs.ComAudio:stopBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_stopBackgroundMusic";
    if (std::strcmp(name, "ccs.ComAudio:stopEffect") == 0) return "lua_cc_studio_ComAudio_stopEffect";
    if (std::strcmp(name, "ccs.ComAudio:unloadEffect") == 0) return "lua_cc_studio_ComAudio_unloadEffect";
    if (std::strcmp(name, "ccs.ComAudio:willPlayBackgroundMusic") == 0) return "lua_cc_studio_ComAudio_willPlayBackgroundMusic";
    if (std::strcmp(name, "ccs.ComController:create") == 0) return "lua_cc_studio_ComController_create";
    if (std::strcmp(name, "ccs.ComController:createInstance") == 0) return "lua_cc_studio_ComController_createInstance";
    if (std::strcmp(name, "ccs.ComRender:create") == 0) return "lua_cc_studio_ComRender_create";
    if (std::strcmp(name, "ccs.ComRender:createInstance") == 0) return "lua_cc_studio_ComRender_createInstance";
    if (std::strcmp(name, "ccs.ComRender:getNode") == 0) return "lua_cc_studio_ComRender_getNode";
    if (std::strcmp(name, "ccs.ComRender:setNode") == 0) return "lua_cc_studio_ComRender_setNode";
    if (std::strcmp(name, "ccs.GUIReader:destroyInstance") == 0) return "lua_cc_studio_GUIReader_destroyInstance";
    if (std::strcmp(name, "ccs.GUIReader:getFilePath") == 0) return "lua_cc_studio_GUIReader_getFilePath";
    if (std::strcmp(name, "ccs.GUIReader:getInstance") == 0) return "lua_cc_studio_GUIReader_getInstance";
    if (std::strcmp(name, "ccs.GUIReader:getVersionInteger") == 0) return "lua_cc_studio_GUIReader_getVersionInteger";
    if (std::strcmp(name, "ccs.GUIReader:widgetFromBinaryFile") == 0) return "lua_cc_studio_GUIReader_widgetFromBinaryFile";
    if (std::strcmp(name, "ccs.GUIReader:widgetFromJsonFile") == 0) return "lua_cc_studio_GUIReader_widgetFromJsonFile";
    if (std::strcmp(name, "ccs.SceneReader:getAttachComponentType") == 0) return "lua_cc_studio_SceneReader_getAttachComponentType";
    if (std::strcmp(name, "ccs.SceneReader:getInstance") == 0) return "lua_cc_studio_SceneReader_getInstance";
    if (std::strcmp(name, "ccs.SceneReader:getNodeByTag") == 0) return "lua_cc_studio_SceneReader_getNodeByTag";
    if (std::strcmp(name, "ccs.SceneReader:sceneReaderVersion") == 0) return "lua_cc_studio_SceneReader_sceneReaderVersion";
    if (std::strcmp(name, "ccs.ActionTimelineCache:destroyInstance") == 0) return "lua_cc_studio_ActionTimelineCache_destroyInstance";
    if (std::strcmp(name, "ccs.ActionTimelineCache:init") == 0) return "lua_cc_studio_ActionTimelineCache_init";
    if (std::strcmp(name, "ccs.ActionTimelineCache:purge") == 0) return "lua_cc_studio_ActionTimelineCache_purge";
    if (std::strcmp(name, "ccs.Frame:apply") == 0) return "lua_cc_studio_Frame_apply";
    if (std::strcmp(name, "ccs.Frame:clone") == 0) return "lua_cc_studio_Frame_clone";
    if (std::strcmp(name, "ccs.Frame:getFrameIndex") == 0) return "lua_cc_studio_Frame_getFrameIndex";
    if (std::strcmp(name, "ccs.Frame:getNode") == 0) return "lua_cc_studio_Frame_getNode";
    if (std::strcmp(name, "ccs.Frame:getTimeline") == 0) return "lua_cc_studio_Frame_getTimeline";
    if (std::strcmp(name, "ccs.Frame:getTweenType") == 0) return "lua_cc_studio_Frame_getTweenType";
    if (std::strcmp(name, "ccs.Frame:isEnterWhenPassed") == 0) return "lua_cc_studio_Frame_isEnterWhenPassed";
    if (std::strcmp(name, "ccs.Frame:isTween") == 0) return "lua_cc_studio_Frame_isTween";
    if (std::strcmp(name, "ccs.Frame:setFrameIndex") == 0) return "lua_cc_studio_Frame_setFrameIndex";
    if (std::strcmp(name, "ccs.Frame:setNode") == 0) return "lua_cc_studio_Frame_setNode";
    if (std::strcmp(name, "ccs.Frame:setTimeline") == 0) return "lua_cc_studio_Frame_setTimeline";
    if (std::strcmp(name, "ccs.Frame:setTween") == 0) return "lua_cc_studio_Frame_setTween";
    if (std::strcmp(name, "ccs.Frame:setTweenType") == 0) return "lua_cc_studio_Frame_setTweenType";
    if (std::strcmp(name, "ccs.VisibleFrame:create") == 0) return "lua_cc_studio_VisibleFrame_create";
    if (std::strcmp(name, "ccs.VisibleFrame:isVisible") == 0) return "lua_cc_studio_VisibleFrame_isVisible";
    if (std::strcmp(name, "ccs.VisibleFrame:setVisible") == 0) return "lua_cc_studio_VisibleFrame_setVisible";
    if (std::strcmp(name, "ccs.TextureFrame:create") == 0) return "lua_cc_studio_TextureFrame_create";
    if (std::strcmp(name, "ccs.TextureFrame:getTextureName") == 0) return "lua_cc_studio_TextureFrame_getTextureName";
    if (std::strcmp(name, "ccs.RotationFrame:create") == 0) return "lua_cc_studio_RotationFrame_create";
    if (std::strcmp(name, "ccs.RotationFrame:getRotation") == 0) return "lua_cc_studio_RotationFrame_getRotation";
    if (std::strcmp(name, "ccs.RotationFrame:setRotation") == 0) return "lua_cc_studio_RotationFrame_setRotation";
    if (std::strcmp(name, "ccs.SkewFrame:create") == 0) return "lua_cc_studio_SkewFrame_create";
    if (std::strcmp(name, "ccs.SkewFrame:getSkewX") == 0) return "lua_cc_studio_SkewFrame_getSkewX";
    if (std::strcmp(name, "ccs.SkewFrame:getSkewY") == 0) return "lua_cc_studio_SkewFrame_getSkewY";
    if (std::strcmp(name, "ccs.SkewFrame:setSkewX") == 0) return "lua_cc_studio_SkewFrame_setSkewX";
    if (std::strcmp(name, "ccs.SkewFrame:setSkewY") == 0) return "lua_cc_studio_SkewFrame_setSkewY";
    if (std::strcmp(name, "ccs.RotationSkewFrame:create") == 0) return "lua_cc_studio_RotationSkewFrame_create";
    if (std::strcmp(name, "ccs.PositionFrame:create") == 0) return "lua_cc_studio_PositionFrame_create";
    if (std::strcmp(name, "ccs.PositionFrame:getX") == 0) return "lua_cc_studio_PositionFrame_getX";
    if (std::strcmp(name, "ccs.PositionFrame:getY") == 0) return "lua_cc_studio_PositionFrame_getY";
    if (std::strcmp(name, "ccs.PositionFrame:setX") == 0) return "lua_cc_studio_PositionFrame_setX";
    if (std::strcmp(name, "ccs.PositionFrame:setY") == 0) return "lua_cc_studio_PositionFrame_setY";
    if (std::strcmp(name, "ccs.ScaleFrame:create") == 0) return "lua_cc_studio_ScaleFrame_create";
    if (std::strcmp(name, "ccs.ScaleFrame:getScaleX") == 0) return "lua_cc_studio_ScaleFrame_getScaleX";
    if (std::strcmp(name, "ccs.ScaleFrame:getScaleY") == 0) return "lua_cc_studio_ScaleFrame_getScaleY";
    if (std::strcmp(name, "ccs.ScaleFrame:setScale") == 0) return "lua_cc_studio_ScaleFrame_setScale";
    if (std::strcmp(name, "ccs.ScaleFrame:setScaleX") == 0) return "lua_cc_studio_ScaleFrame_setScaleX";
    if (std::strcmp(name, "ccs.ScaleFrame:setScaleY") == 0) return "lua_cc_studio_ScaleFrame_setScaleY";
    if (std::strcmp(name, "ccs.AnchorPointFrame:create") == 0) return "lua_cc_studio_AnchorPointFrame_create";
    if (std::strcmp(name, "ccs.InnerActionFrame:create") == 0) return "lua_cc_studio_InnerActionFrame_create";
    if (std::strcmp(name, "ccs.InnerActionFrame:getEndFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_getEndFrameIndex";
    if (std::strcmp(name, "ccs.InnerActionFrame:getInnerActionType") == 0) return "lua_cc_studio_InnerActionFrame_getInnerActionType";
    if (std::strcmp(name, "ccs.InnerActionFrame:getSingleFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_getSingleFrameIndex";
    if (std::strcmp(name, "ccs.InnerActionFrame:getStartFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_getStartFrameIndex";
    if (std::strcmp(name, "ccs.InnerActionFrame:setEndFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_setEndFrameIndex";
    if (std::strcmp(name, "ccs.InnerActionFrame:setEnterWithName") == 0) return "lua_cc_studio_InnerActionFrame_setEnterWithName";
    if (std::strcmp(name, "ccs.InnerActionFrame:setInnerActionType") == 0) return "lua_cc_studio_InnerActionFrame_setInnerActionType";
    if (std::strcmp(name, "ccs.InnerActionFrame:setSingleFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_setSingleFrameIndex";
    if (std::strcmp(name, "ccs.InnerActionFrame:setStartFrameIndex") == 0) return "lua_cc_studio_InnerActionFrame_setStartFrameIndex";
    if (std::strcmp(name, "ccs.ColorFrame:create") == 0) return "lua_cc_studio_ColorFrame_create";
    if (std::strcmp(name, "ccs.AlphaFrame:create") == 0) return "lua_cc_studio_AlphaFrame_create";
    if (std::strcmp(name, "ccs.AlphaFrame:getAlpha") == 0) return "lua_cc_studio_AlphaFrame_getAlpha";
    if (std::strcmp(name, "ccs.EventFrame:create") == 0) return "lua_cc_studio_EventFrame_create";
    if (std::strcmp(name, "ccs.EventFrame:getEvent") == 0) return "lua_cc_studio_EventFrame_getEvent";
    if (std::strcmp(name, "ccs.EventFrame:init") == 0) return "lua_cc_studio_EventFrame_init";
    if (std::strcmp(name, "ccs.ZOrderFrame:create") == 0) return "lua_cc_studio_ZOrderFrame_create";
    if (std::strcmp(name, "ccs.ZOrderFrame:getZOrder") == 0) return "lua_cc_studio_ZOrderFrame_getZOrder";
    if (std::strcmp(name, "ccs.ZOrderFrame:setZOrder") == 0) return "lua_cc_studio_ZOrderFrame_setZOrder";
    if (std::strcmp(name, "ccs.BlendFuncFrame:create") == 0) return "lua_cc_studio_BlendFuncFrame_create";
    if (std::strcmp(name, "ccs.PlayableFrame:create") == 0) return "lua_cc_studio_PlayableFrame_create";
    if (std::strcmp(name, "ccs.PlayableFrame:getPlayableAct") == 0) return "lua_cc_studio_PlayableFrame_getPlayableAct";
    if (std::strcmp(name, "ccs.PlayableFrame:setPlayableAct") == 0) return "lua_cc_studio_PlayableFrame_setPlayableAct";
    if (std::strcmp(name, "ccs.Timeline:addFrame") == 0) return "lua_cc_studio_Timeline_addFrame";
    if (std::strcmp(name, "ccs.Timeline:clone") == 0) return "lua_cc_studio_Timeline_clone";
    if (std::strcmp(name, "ccs.Timeline:create") == 0) return "lua_cc_studio_Timeline_create";
    if (std::strcmp(name, "ccs.Timeline:getActionTag") == 0) return "lua_cc_studio_Timeline_getActionTag";
    if (std::strcmp(name, "ccs.Timeline:getActionTimeline") == 0) return "lua_cc_studio_Timeline_getActionTimeline";
    if (std::strcmp(name, "ccs.Timeline:getNode") == 0) return "lua_cc_studio_Timeline_getNode";
    if (std::strcmp(name, "ccs.Timeline:gotoFrame") == 0) return "lua_cc_studio_Timeline_gotoFrame";
    if (std::strcmp(name, "ccs.Timeline:insertFrame") == 0) return "lua_cc_studio_Timeline_insertFrame";
    if (std::strcmp(name, "ccs.Timeline:removeFrame") == 0) return "lua_cc_studio_Timeline_removeFrame";
    if (std::strcmp(name, "ccs.Timeline:setActionTag") == 0) return "lua_cc_studio_Timeline_setActionTag";
    if (std::strcmp(name, "ccs.Timeline:setActionTimeline") == 0) return "lua_cc_studio_Timeline_setActionTimeline";
    if (std::strcmp(name, "ccs.Timeline:setNode") == 0) return "lua_cc_studio_Timeline_setNode";
    if (std::strcmp(name, "ccs.Timeline:stepToFrame") == 0) return "lua_cc_studio_Timeline_stepToFrame";
    if (std::strcmp(name, "ccs.ActionTimelineData:create") == 0) return "lua_cc_studio_ActionTimelineData_create";
    if (std::strcmp(name, "ccs.ActionTimelineData:getActionTag") == 0) return "lua_cc_studio_ActionTimelineData_getActionTag";
    if (std::strcmp(name, "ccs.ActionTimelineData:init") == 0) return "lua_cc_studio_ActionTimelineData_init";
    if (std::strcmp(name, "ccs.ActionTimelineData:setActionTag") == 0) return "lua_cc_studio_ActionTimelineData_setActionTag";
    if (std::strcmp(name, "ccs.ActionTimeline:addTimeline") == 0) return "lua_cc_studio_ActionTimeline_addTimeline";
    if (std::strcmp(name, "ccs.ActionTimeline:clearFrameEndCallFuncs") == 0) return "lua_cc_studio_ActionTimeline_clearFrameEndCallFuncs";
    if (std::strcmp(name, "ccs.ActionTimeline:clearFrameEventCallFunc") == 0) return "lua_cc_studio_ActionTimeline_clearFrameEventCallFunc";
    if (std::strcmp(name, "ccs.ActionTimeline:clearLastFrameCallFunc") == 0) return "lua_cc_studio_ActionTimeline_clearLastFrameCallFunc";
    if (std::strcmp(name, "ccs.ActionTimeline:create") == 0) return "lua_cc_studio_ActionTimeline_create";
    if (std::strcmp(name, "ccs.ActionTimeline:getCurrentFrame") == 0) return "lua_cc_studio_ActionTimeline_getCurrentFrame";
    if (std::strcmp(name, "ccs.ActionTimeline:getDuration") == 0) return "lua_cc_studio_ActionTimeline_getDuration";
    if (std::strcmp(name, "ccs.ActionTimeline:getEndFrame") == 0) return "lua_cc_studio_ActionTimeline_getEndFrame";
    if (std::strcmp(name, "ccs.ActionTimeline:getStartFrame") == 0) return "lua_cc_studio_ActionTimeline_getStartFrame";
    if (std::strcmp(name, "ccs.ActionTimeline:getTimeSpeed") == 0) return "lua_cc_studio_ActionTimeline_getTimeSpeed";
    if (std::strcmp(name, "ccs.ActionTimeline:gotoFrameAndPause") == 0) return "lua_cc_studio_ActionTimeline_gotoFrameAndPause";
    if (std::strcmp(name, "ccs.ActionTimeline:gotoFrameAndPlay") == 0) return "lua_cc_studio_ActionTimeline_gotoFrameAndPlay";
    if (std::strcmp(name, "ccs.ActionTimeline:init") == 0) return "lua_cc_studio_ActionTimeline_init";
    if (std::strcmp(name, "ccs.ActionTimeline:isPlaying") == 0) return "lua_cc_studio_ActionTimeline_isPlaying";
    if (std::strcmp(name, "ccs.ActionTimeline:pause") == 0) return "lua_cc_studio_ActionTimeline_pause";
    if (std::strcmp(name, "ccs.ActionTimeline:play") == 0) return "lua_cc_studio_ActionTimeline_play";
    if (std::strcmp(name, "ccs.ActionTimeline:removeAnimationInfo") == 0) return "lua_cc_studio_ActionTimeline_removeAnimationInfo";
    if (std::strcmp(name, "ccs.ActionTimeline:removeFrameEndCallFuncs") == 0) return "lua_cc_studio_ActionTimeline_removeFrameEndCallFuncs";
    if (std::strcmp(name, "ccs.ActionTimeline:removeTimeline") == 0) return "lua_cc_studio_ActionTimeline_removeTimeline";
    if (std::strcmp(name, "ccs.ActionTimeline:resume") == 0) return "lua_cc_studio_ActionTimeline_resume";
    if (std::strcmp(name, "ccs.ActionTimeline:setCurrentFrame") == 0) return "lua_cc_studio_ActionTimeline_setCurrentFrame";
    if (std::strcmp(name, "ccs.ActionTimeline:setDuration") == 0) return "lua_cc_studio_ActionTimeline_setDuration";
    if (std::strcmp(name, "ccs.ActionTimeline:setTimeSpeed") == 0) return "lua_cc_studio_ActionTimeline_setTimeSpeed";
    if (std::strcmp(name, "ccs.ActionTimelineNode:create") == 0) return "lua_cc_studio_ActionTimelineNode_create";
    if (std::strcmp(name, "ccs.ActionTimelineNode:getActionTimeline") == 0) return "lua_cc_studio_ActionTimelineNode_getActionTimeline";
    if (std::strcmp(name, "ccs.ActionTimelineNode:getRoot") == 0) return "lua_cc_studio_ActionTimelineNode_getRoot";
    if (std::strcmp(name, "ccs.ActionTimelineNode:setActionTimeline") == 0) return "lua_cc_studio_ActionTimelineNode_setActionTimeline";
    if (std::strcmp(name, "ccs.ActionTimelineNode:setRoot") == 0) return "lua_cc_studio_ActionTimelineNode_setRoot";
    if (std::strcmp(name, "ccs.BoneNode:addSkin") == 0) return "lua_cc_studio_BoneNode_addSkin";
    if (std::strcmp(name, "ccs.BoneNode:create") == 0) return "lua_cc_studio_BoneNode_create";
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawColor") == 0) return "lua_cc_studio_BoneNode_getDebugDrawColor";
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawLength") == 0) return "lua_cc_studio_BoneNode_getDebugDrawLength";
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawWidth") == 0) return "lua_cc_studio_BoneNode_getDebugDrawWidth";
    if (std::strcmp(name, "ccs.BoneNode:getRootSkeletonNode") == 0) return "lua_cc_studio_BoneNode_getRootSkeletonNode";
    if (std::strcmp(name, "ccs.BoneNode:isDebugDrawEnabled") == 0) return "lua_cc_studio_BoneNode_isDebugDrawEnabled";
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawEnabled") == 0) return "lua_cc_studio_BoneNode_setDebugDrawEnabled";
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawLength") == 0) return "lua_cc_studio_BoneNode_setDebugDrawLength";
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawWidth") == 0) return "lua_cc_studio_BoneNode_setDebugDrawWidth";
    if (std::strcmp(name, "ccs.SkeletonNode:create") == 0) return "lua_cc_studio_SkeletonNode_create";
    if (std::strcmp(name, "ccs.ComExtensionData:create") == 0) return "lua_cc_studio_ComExtensionData_create";
    if (std::strcmp(name, "ccs.ComExtensionData:createInstance") == 0) return "lua_cc_studio_ComExtensionData_createInstance";
    if (std::strcmp(name, "ccs.ComExtensionData:getActionTag") == 0) return "lua_cc_studio_ComExtensionData_getActionTag";
    if (std::strcmp(name, "ccs.ComExtensionData:getCustomProperty") == 0) return "lua_cc_studio_ComExtensionData_getCustomProperty";
    if (std::strcmp(name, "ccs.ComExtensionData:setActionTag") == 0) return "lua_cc_studio_ComExtensionData_setActionTag";
    if (std::strcmp(name, "ccs.ArmatureAnimation:setMovementEventCallFunc") == 0) return "cclua_ArmatureAnimation_setMovementEventCallFunc";
    if (std::strcmp(name, "ccs.ArmatureAnimation:setFrameEventCallFunc") == 0) return "cclua_ArmatureAnimation_setFrameEventCallFunc";
    if (std::strcmp(name, "ccs.ActionTimeline:setFrameEventCallFunc") == 0) return "cclua_ActionTimeline_setFrameEventCallFunc";
    return name;
}
template<typename F>
bool prepare(lua_State* L, const char* name, const F&) {
    if (callback_entry(name)) {
#if CC_DEBUG >= 1
        if (!lua_isfunction(L, 2)) {
            tolua_Error error{}; error.index=2; error.array=0; error.type="[not function]";
            const auto* method=std::strchr(name, ':')+1;
            char message[128]; std::snprintf(message,sizeof(message),"#ferror in function '%s'.",method);
            tolua_error(L,message,&error);
        }
#else
        if (!lua_isfunction(L, 2)) {
            lua_pushcfunction(L, [](lua_State*) -> int { return 0; });
            lua_replace(L, 2);
        }
#endif
    }
    using T=std::decay_t<F>;
    if constexpr (std::is_class_v<T>)
        return prepare_signature<typename lua::function_traits<T>::pointer>::run(L,name);
    else return prepare_signature<T>::run(L,name);
}
inline void check_receiver(lua_State* L,const char* type,const char* name,bool member) {
#if CC_DEBUG >= 1
    tolua_Error error{};
    const bool valid=member ? tolua_isusertype(L,1,type,0,&error) : tolua_isusertable(L,1,type,0,&error);
    char message[256];
    if (!valid) {
        std::snprintf(message,sizeof(message),"#ferror in function '%s'.",
            callback_entry(name) ? std::strchr(name, ':')+1 : native_symbol(name));
        tolua_error(L,message,&error);
    }
    if (member && !tolua_tousertype(L,1,nullptr)) {
        if (callback_entry(name))
            std::snprintf(message,sizeof(message),"invalid 'self' in function '%s'\n",native_symbol(name));
        else std::snprintf(message,sizeof(message),"invalid 'cobj' in function '%s'",native_symbol(name));
        tolua_error(L,message,nullptr);
    }
#else
    (void)L; (void)type; (void)name; (void)member;
#endif
}
inline int fail(lua_State* L,const char* name,int argc,int attempted) {
    if (callback_entry(name)) {
        const auto* method=std::strchr(name, ':')+1;
        const auto* cls=std::strcmp(name,"ccs.ActionTimeline:setFrameEventCallFunc")==0 ? "ActionTimeline" : "ArmatureAnimation";
        return luaL_error(L,"'%s' function of %s has wrong number of arguments: %d, was expecting %d\n",method,cls,argc,1);
    }
    if (std::strcmp(name, "ccs.ActionFrame:getAction") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionFrame:getAction",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionFrame:getEasingType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_getEasingType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getEasingType",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionFrame:getFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_getFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionFrame:getFrameTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_getFrameTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameTime",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionFrame:getFrameType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_getFrameType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:getFrameType",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionFrame:setEasingType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_setEasingType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setEasingType",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionFrame:setFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_setFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionFrame:setFrameTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_setFrameTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameTime",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionFrame:setFrameType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFrame_setFrameType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setFrameType",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionScaleFrame:getScaleX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionScaleFrame_getScaleX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getScaleX",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionScaleFrame:getScaleY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionScaleFrame_getScaleY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getScaleY",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionScaleFrame:setScaleX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionScaleFrame_setScaleX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:setScaleX",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionScaleFrame:setScaleY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionScaleFrame_setScaleY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:setScaleY",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionRotationFrame:getRotation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionRotationFrame_getRotation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:getRotation",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionRotationFrame:setRotation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionRotationFrame_setRotation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:setRotation",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionFadeFrame:getOpacity") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFadeFrame_getOpacity'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:getOpacity",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionFadeFrame:setOpacity") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionFadeFrame_setOpacity'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:setOpacity",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:addActionNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_addActionNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:addActionNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:getCurrentTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_getCurrentTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getCurrentTime",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:getLoop") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_getLoop'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getLoop",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:getName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_getName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getName",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:getTotalTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_getTotalTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getTotalTime",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:getUnitTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_getUnitTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:getUnitTime",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:isPlaying") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_isPlaying'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:isPlaying",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:pause") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_pause'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:pause",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:play") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionObject:play",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:removeActionNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_removeActionNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:removeActionNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:setCurrentTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_setCurrentTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setCurrentTime",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:setLoop") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_setLoop'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setLoop",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:setName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_setName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setName",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:setUnitTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_setUnitTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:setUnitTime",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:simulationActionUpdate") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_simulationActionUpdate'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:simulationActionUpdate",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionObject:stop") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_stop'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:stop",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionObject:updateToFrameByTime") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionObject_updateToFrameByTime'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:updateToFrameByTime",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionManagerEx:getActionByName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionManagerEx_getActionByName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:getActionByName",argc, 2);
    }
    if (std::strcmp(name, "ccs.ActionManagerEx:getStudioVersionNumber") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionManagerEx_getStudioVersionNumber'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:getStudioVersionNumber",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionManagerEx:playActionByName") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionManagerEx:playActionByName",argc, 2);
    }
    if (std::strcmp(name, "ccs.ActionManagerEx:releaseActions") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionManagerEx_releaseActions'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:releaseActions",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionManagerEx:stopActionByName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionManagerEx_stopActionByName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionManagerEx:stopActionByName",argc, 2);
    }
    if (std::strcmp(name, "ccs.BaseData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BaseData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BaseData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayData:copy") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayData_copy'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayData:copy",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.SpriteDisplayData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SpriteDisplayData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SpriteDisplayData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureDisplayData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureDisplayData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDisplayData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ParticleDisplayData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ParticleDisplayData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ParticleDisplayData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneData:addDisplayData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneData_addDisplayData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:addDisplayData",argc, 1);
    }
    if (std::strcmp(name, "ccs.BoneData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BoneData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneData:getDisplayData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneData_getDisplayData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:getDisplayData",argc, 1);
    }
    if (std::strcmp(name, "ccs.BoneData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureData:addBoneData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureData_addBoneData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:addBoneData",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.FrameData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_FrameData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.FrameData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.MovementBoneData:addFrameData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementBoneData_addFrameData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:addFrameData",argc, 1);
    }
    if (std::strcmp(name, "ccs.MovementBoneData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementBoneData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.MovementBoneData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.MovementBoneData:getFrameData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementBoneData_getFrameData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:getFrameData",argc, 1);
    }
    if (std::strcmp(name, "ccs.MovementBoneData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementBoneData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.MovementData:addMovementBoneData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementData_addMovementBoneData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:addMovementBoneData",argc, 1);
    }
    if (std::strcmp(name, "ccs.MovementData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_MovementData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.MovementData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.AnimationData:addMovement") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AnimationData_addMovement'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:addMovement",argc, 1);
    }
    if (std::strcmp(name, "ccs.AnimationData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AnimationData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.AnimationData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.AnimationData:getMovementCount") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AnimationData_getMovementCount'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:getMovementCount",argc, 0);
    }
    if (std::strcmp(name, "ccs.ContourData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ContourData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ContourData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ContourData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ContourData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.TextureData:addContourData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureData_addContourData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:addContourData",argc, 1);
    }
    if (std::strcmp(name, "ccs.TextureData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.TextureData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.TextureData:getContourData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureData_getContourData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:getContourData",argc, 1);
    }
    if (std::strcmp(name, "ccs.TextureData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.Tween:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Tween:create",argc, 1);
    }
    if (std::strcmp(name, "ccs.Tween:getAnimation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_getAnimation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:getAnimation",argc, 0);
    }
    if (std::strcmp(name, "ccs.Tween:gotoAndPause") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_gotoAndPause'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:gotoAndPause",argc, 1);
    }
    if (std::strcmp(name, "ccs.Tween:gotoAndPlay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_gotoAndPlay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:gotoAndPlay",argc, 1);
    }
    if (std::strcmp(name, "ccs.Tween:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:init",argc, 1);
    }
    if (std::strcmp(name, "ccs.Tween:setAnimation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Tween_setAnimation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:setAnimation",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayManager:addDisplay") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.DisplayManager:addDisplay",argc, 2);
    }
    if (std::strcmp(name, "ccs.DisplayManager:changeDisplayWithIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_changeDisplayWithIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:changeDisplayWithIndex",argc, 2);
    }
    if (std::strcmp(name, "ccs.DisplayManager:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayManager:create",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayManager:getCurrentDisplayIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_getCurrentDisplayIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getCurrentDisplayIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayManager:getDisplayRenderNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_getDisplayRenderNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDisplayRenderNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayManager:getDisplayRenderNodeType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_getDisplayRenderNodeType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDisplayRenderNodeType",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayManager:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:init",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayManager:isForceChangeDisplay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_isForceChangeDisplay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:isForceChangeDisplay",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayManager:isVisible") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_isVisible'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:isVisible",argc, 0);
    }
    if (std::strcmp(name, "ccs.DisplayManager:removeDisplay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_removeDisplay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:removeDisplay",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayManager:setForceChangeDisplay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_setForceChangeDisplay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:setForceChangeDisplay",argc, 1);
    }
    if (std::strcmp(name, "ccs.DisplayManager:setVisible") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_DisplayManager_setVisible'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:setVisible",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:addChildBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_addChildBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:addChildBone",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:addDisplay") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.Bone:addDisplay",argc, 2);
    }
    if (std::strcmp(name, "ccs.Bone:changeDisplayWithIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_changeDisplayWithIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:changeDisplayWithIndex",argc, 2);
    }
    if (std::strcmp(name, "ccs.Bone:getArmature") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getArmature'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getArmature",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getBoneData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getBoneData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getBoneData",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getChildArmature") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getChildArmature'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getChildArmature",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getColliderDetector") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getColliderDetector'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getColliderDetector",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getDisplayManager") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getDisplayManager'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayManager",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getDisplayRenderNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getDisplayRenderNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayRenderNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getDisplayRenderNodeType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getDisplayRenderNodeType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getDisplayRenderNodeType",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getNodeToArmatureTransform") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getNodeToArmatureTransform'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getNodeToArmatureTransform",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getParentBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getParentBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getParentBone",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getTween") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getTween'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getTween",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getTweenData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getTweenData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getTweenData",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:getWorldInfo") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_getWorldInfo'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getWorldInfo",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:isBlendDirty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_isBlendDirty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isBlendDirty",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:isIgnoreMovementBoneData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_isIgnoreMovementBoneData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isIgnoreMovementBoneData",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:isTransformDirty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_isTransformDirty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:isTransformDirty",argc, 0);
    }
    if (std::strcmp(name, "ccs.Bone:removeChildBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_removeChildBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeChildBone",argc, 2);
    }
    if (std::strcmp(name, "ccs.Bone:removeDisplay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_removeDisplay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeDisplay",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setArmature") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setArmature'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setArmature",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setBlendDirty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setBlendDirty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setBlendDirty",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setBoneData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setBoneData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setBoneData",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setChildArmature") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setChildArmature'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setChildArmature",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setParentBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setParentBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setParentBone",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:setTransformDirty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_setTransformDirty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setTransformDirty",argc, 1);
    }
    if (std::strcmp(name, "ccs.Bone:updateZOrder") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Bone_updateZOrder'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:updateZOrder",argc, 0);
    }
    if (std::strcmp(name, "ccs.BatchNode:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BatchNode_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BatchNode:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureAnimation:create",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:getAnimationData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_getAnimationData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getAnimationData",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:getCurrentMovementID") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_getCurrentMovementID'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getCurrentMovementID",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:getMovementCount") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_getMovementCount'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getMovementCount",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:getSpeedScale") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_getSpeedScale'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:getSpeedScale",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:gotoAndPause") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_gotoAndPause'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:gotoAndPause",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:gotoAndPlay") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_gotoAndPlay'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:gotoAndPlay",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:init",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:playWithIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:setAnimationData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_setAnimationData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:setAnimationData",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureAnimation:setSpeedScale") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureAnimation_setSpeedScale'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:setSpeedScale",argc, 1);
    }
    if (std::strcmp(name, "ccs.ArmatureDataManager:destroyInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureDataManager_destroyInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDataManager:destroyInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureDataManager:getInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ArmatureDataManager:getInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureDataManager:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureDataManager_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.ArmatureDataManager:isAutoLoadSpriteFile") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ArmatureDataManager_isAutoLoadSpriteFile'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:isAutoLoadSpriteFile",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getAnimation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getAnimation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getAnimation",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getArmatureData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getArmatureData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getArmatureData",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getArmatureTransformDirty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getArmatureTransformDirty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getArmatureTransformDirty",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getBatchNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getBatchNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBatchNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getBoneAtPoint") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getBoneAtPoint'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBoneAtPoint",argc, 2);
    }
    if (std::strcmp(name, "ccs.Armature:getParentBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getParentBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getParentBone",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:getVersion") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_getVersion'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getVersion",argc, 0);
    }
    if (std::strcmp(name, "ccs.Armature:removeBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_removeBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:removeBone",argc, 2);
    }
    if (std::strcmp(name, "ccs.Armature:setAnimation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_setAnimation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setAnimation",argc, 1);
    }
    if (std::strcmp(name, "ccs.Armature:setArmatureData") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_setArmatureData'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setArmatureData",argc, 1);
    }
    if (std::strcmp(name, "ccs.Armature:setBatchNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_setBatchNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setBatchNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.Armature:setParentBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_setParentBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setParentBone",argc, 1);
    }
    if (std::strcmp(name, "ccs.Armature:setVersion") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_setVersion'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setVersion",argc, 1);
    }
    if (std::strcmp(name, "ccs.Armature:updateOffsetPoint") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Armature_updateOffsetPoint'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:updateOffsetPoint",argc, 0);
    }
    if (std::strcmp(name, "ccs.Skin:getBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Skin_getBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getBone",argc, 0);
    }
    if (std::strcmp(name, "ccs.Skin:getDisplayName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Skin_getDisplayName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getDisplayName",argc, 0);
    }
    if (std::strcmp(name, "ccs.Skin:getNodeToWorldTransformAR") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Skin_getNodeToWorldTransformAR'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:getNodeToWorldTransformAR",argc, 0);
    }
    if (std::strcmp(name, "ccs.Skin:setBone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Skin_setBone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:setBone",argc, 1);
    }
    if (std::strcmp(name, "ccs.Skin:updateArmatureTransform") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Skin_updateArmatureTransform'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:updateArmatureTransform",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAttribute:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAttribute_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAttribute:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAttribute:createInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAttribute_createInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAttribute:createInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAudio:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:createInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_createInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComAudio:createInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:endToLua") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_end'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:end",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:getBackgroundMusicVolume") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_getBackgroundMusicVolume'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getBackgroundMusicVolume",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:getEffectsVolume") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_getEffectsVolume'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getEffectsVolume",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:getFile") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_getFile'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:getFile",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:isBackgroundMusicPlaying") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_isBackgroundMusicPlaying'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:isBackgroundMusicPlaying",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:isLoop") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_isLoop'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:isLoop",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:pauseAllEffects") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_pauseAllEffects'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseAllEffects",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:pauseBackgroundMusic") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_pauseBackgroundMusic'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseBackgroundMusic",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:pauseEffect") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_pauseEffect'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:pauseEffect",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:playBackgroundMusic") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:playBackgroundMusic",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:playEffect") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:playEffect",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:preloadBackgroundMusic") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_preloadBackgroundMusic'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:preloadBackgroundMusic",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:preloadEffect") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_preloadEffect'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:preloadEffect",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:resumeAllEffects") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_resumeAllEffects'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeAllEffects",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:resumeBackgroundMusic") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_resumeBackgroundMusic'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeBackgroundMusic",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:resumeEffect") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_resumeEffect'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:resumeEffect",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:rewindBackgroundMusic") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_rewindBackgroundMusic'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:rewindBackgroundMusic",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:setBackgroundMusicVolume") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_setBackgroundMusicVolume'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setBackgroundMusicVolume",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:setEffectsVolume") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_setEffectsVolume'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setEffectsVolume",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:setFile") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_setFile'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setFile",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:setLoop") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_setLoop'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:setLoop",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:stopAllEffects") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_stopAllEffects'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:stopAllEffects",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComAudio:stopBackgroundMusic") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ComAudio:stopBackgroundMusic",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:stopEffect") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_stopEffect'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:stopEffect",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:unloadEffect") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_unloadEffect'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:unloadEffect",argc, 1);
    }
    if (std::strcmp(name, "ccs.ComAudio:willPlayBackgroundMusic") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComAudio_willPlayBackgroundMusic'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:willPlayBackgroundMusic",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComController:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComController_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComController:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComController:createInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComController_createInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComController:createInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComRender:create") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", "ccs.ComRender:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComRender:createInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComRender_createInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComRender:createInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComRender:getNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComRender_getNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComRender:getNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComRender:setNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComRender_setNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComRender:setNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.GUIReader:destroyInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_destroyInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.GUIReader:destroyInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.GUIReader:getFilePath") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_getFilePath'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:getFilePath",argc, 0);
    }
    if (std::strcmp(name, "ccs.GUIReader:getInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_getInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.GUIReader:getInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.GUIReader:getVersionInteger") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_getVersionInteger'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:getVersionInteger",argc, 1);
    }
    if (std::strcmp(name, "ccs.GUIReader:widgetFromBinaryFile") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_widgetFromBinaryFile'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:widgetFromBinaryFile",argc, 1);
    }
    if (std::strcmp(name, "ccs.GUIReader:widgetFromJsonFile") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_GUIReader_widgetFromJsonFile'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:widgetFromJsonFile",argc, 1);
    }
    if (std::strcmp(name, "ccs.SceneReader:getAttachComponentType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SceneReader_getAttachComponentType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:getAttachComponentType",argc, 0);
    }
    if (std::strcmp(name, "ccs.SceneReader:getInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SceneReader_getInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:getInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.SceneReader:getNodeByTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SceneReader_getNodeByTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:getNodeByTag",argc, 1);
    }
    if (std::strcmp(name, "ccs.SceneReader:sceneReaderVersion") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SceneReader_sceneReaderVersion'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:sceneReaderVersion",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineCache:destroyInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineCache_destroyInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:destroyInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineCache:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineCache_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineCache:purge") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineCache_purge'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:purge",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:apply") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_apply'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:apply",argc, 1);
    }
    if (std::strcmp(name, "ccs.Frame:clone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_clone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:clone",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:getFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_getFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getFrameIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:getNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_getNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:getTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_getTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getTimeline",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:getTweenType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_getTweenType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getTweenType",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:isEnterWhenPassed") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_isEnterWhenPassed'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:isEnterWhenPassed",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:isTween") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_isTween'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:isTween",argc, 0);
    }
    if (std::strcmp(name, "ccs.Frame:setFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_setFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setFrameIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.Frame:setNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_setNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.Frame:setTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_setTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setTimeline",argc, 1);
    }
    if (std::strcmp(name, "ccs.Frame:setTween") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_setTween'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setTween",argc, 1);
    }
    if (std::strcmp(name, "ccs.Frame:setTweenType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Frame_setTweenType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setTweenType",argc, 1);
    }
    if (std::strcmp(name, "ccs.VisibleFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_VisibleFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.VisibleFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.VisibleFrame:isVisible") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_VisibleFrame_isVisible'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:isVisible",argc, 0);
    }
    if (std::strcmp(name, "ccs.VisibleFrame:setVisible") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_VisibleFrame_setVisible'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:setVisible",argc, 1);
    }
    if (std::strcmp(name, "ccs.TextureFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.TextureFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.TextureFrame:getTextureName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_TextureFrame_getTextureName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:getTextureName",argc, 0);
    }
    if (std::strcmp(name, "ccs.RotationFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_RotationFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.RotationFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.RotationFrame:getRotation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_RotationFrame_getRotation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:getRotation",argc, 0);
    }
    if (std::strcmp(name, "ccs.RotationFrame:setRotation") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_RotationFrame_setRotation'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:setRotation",argc, 1);
    }
    if (std::strcmp(name, "ccs.SkewFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkewFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SkewFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.SkewFrame:getSkewX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkewFrame_getSkewX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:getSkewX",argc, 0);
    }
    if (std::strcmp(name, "ccs.SkewFrame:getSkewY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkewFrame_getSkewY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:getSkewY",argc, 0);
    }
    if (std::strcmp(name, "ccs.SkewFrame:setSkewX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkewFrame_setSkewX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:setSkewX",argc, 1);
    }
    if (std::strcmp(name, "ccs.SkewFrame:setSkewY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkewFrame_setSkewY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:setSkewY",argc, 1);
    }
    if (std::strcmp(name, "ccs.RotationSkewFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_RotationSkewFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.RotationSkewFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.PositionFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PositionFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.PositionFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.PositionFrame:getX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PositionFrame_getX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getX",argc, 0);
    }
    if (std::strcmp(name, "ccs.PositionFrame:getY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PositionFrame_getY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getY",argc, 0);
    }
    if (std::strcmp(name, "ccs.PositionFrame:setX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PositionFrame_setX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setX",argc, 1);
    }
    if (std::strcmp(name, "ccs.PositionFrame:setY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PositionFrame_setY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setY",argc, 1);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ScaleFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:getScaleX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_getScaleX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:getScaleX",argc, 0);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:getScaleY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_getScaleY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:getScaleY",argc, 0);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:setScale") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_setScale'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScale",argc, 1);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:setScaleX") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_setScaleX'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScaleX",argc, 1);
    }
    if (std::strcmp(name, "ccs.ScaleFrame:setScaleY") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ScaleFrame_setScaleY'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:setScaleY",argc, 1);
    }
    if (std::strcmp(name, "ccs.AnchorPointFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AnchorPointFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.AnchorPointFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.InnerActionFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:getEndFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_getEndFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getEndFrameIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:getInnerActionType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_getInnerActionType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getInnerActionType",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:getSingleFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_getSingleFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getSingleFrameIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:getStartFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_getStartFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:getStartFrameIndex",argc, 0);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:setEndFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_setEndFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setEndFrameIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:setEnterWithName") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_setEnterWithName'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setEnterWithName",argc, 1);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:setInnerActionType") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_setInnerActionType'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setInnerActionType",argc, 1);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:setSingleFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_setSingleFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setSingleFrameIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.InnerActionFrame:setStartFrameIndex") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_InnerActionFrame_setStartFrameIndex'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setStartFrameIndex",argc, 1);
    }
    if (std::strcmp(name, "ccs.ColorFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ColorFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ColorFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.AlphaFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AlphaFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.AlphaFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.AlphaFrame:getAlpha") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_AlphaFrame_getAlpha'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AlphaFrame:getAlpha",argc, 0);
    }
    if (std::strcmp(name, "ccs.EventFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_EventFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.EventFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.EventFrame:getEvent") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_EventFrame_getEvent'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:getEvent",argc, 0);
    }
    if (std::strcmp(name, "ccs.EventFrame:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_EventFrame_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.ZOrderFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ZOrderFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ZOrderFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ZOrderFrame:getZOrder") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ZOrderFrame_getZOrder'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:getZOrder",argc, 0);
    }
    if (std::strcmp(name, "ccs.ZOrderFrame:setZOrder") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ZOrderFrame_setZOrder'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:setZOrder",argc, 1);
    }
    if (std::strcmp(name, "ccs.BlendFuncFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BlendFuncFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.BlendFuncFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.PlayableFrame:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PlayableFrame_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.PlayableFrame:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.PlayableFrame:getPlayableAct") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PlayableFrame_getPlayableAct'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PlayableFrame:getPlayableAct",argc, 0);
    }
    if (std::strcmp(name, "ccs.PlayableFrame:setPlayableAct") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_PlayableFrame_setPlayableAct'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PlayableFrame:setPlayableAct",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:addFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_addFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:addFrame",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:clone") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_clone'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:clone",argc, 0);
    }
    if (std::strcmp(name, "ccs.Timeline:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Timeline:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.Timeline:getActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_getActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getActionTag",argc, 0);
    }
    if (std::strcmp(name, "ccs.Timeline:getActionTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_getActionTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getActionTimeline",argc, 0);
    }
    if (std::strcmp(name, "ccs.Timeline:getNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_getNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.Timeline:gotoFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_gotoFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:gotoFrame",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:insertFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_insertFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:insertFrame",argc, 2);
    }
    if (std::strcmp(name, "ccs.Timeline:removeFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_removeFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:removeFrame",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:setActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_setActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setActionTag",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:setActionTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_setActionTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setActionTimeline",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:setNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_setNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:setNode",argc, 1);
    }
    if (std::strcmp(name, "ccs.Timeline:stepToFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_Timeline_stepToFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:stepToFrame",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimelineData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineData:create",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimelineData:getActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineData_getActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:getActionTag",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineData:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineData_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:init",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimelineData:setActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineData_setActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:setActionTag",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:addTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_addTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:addTimeline",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:clearFrameEndCallFuncs") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_clearFrameEndCallFuncs'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:clearFrameEndCallFuncs",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:clearFrameEventCallFunc") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_clearFrameEventCallFunc'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:clearFrameEventCallFunc",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:clearLastFrameCallFunc") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_clearLastFrameCallFunc'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:clearLastFrameCallFunc",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimeline:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:getCurrentFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_getCurrentFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getCurrentFrame",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:getDuration") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_getDuration'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getDuration",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:getEndFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_getEndFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getEndFrame",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:getStartFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_getStartFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getStartFrame",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:getTimeSpeed") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_getTimeSpeed'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getTimeSpeed",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:gotoFrameAndPause") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_gotoFrameAndPause'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:gotoFrameAndPause",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:gotoFrameAndPlay") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionTimeline:gotoFrameAndPlay",argc, 4);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:init") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_init'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:init",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:isPlaying") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_isPlaying'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:isPlaying",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:pause") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_pause'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:pause",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:play") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_play'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:play",argc, 2);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:removeAnimationInfo") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_removeAnimationInfo'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:removeAnimationInfo",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:removeFrameEndCallFuncs") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_removeFrameEndCallFuncs'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:removeFrameEndCallFuncs",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:removeTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_removeTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:removeTimeline",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:resume") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_resume'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:resume",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:setCurrentFrame") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_setCurrentFrame'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setCurrentFrame",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:setDuration") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_setDuration'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setDuration",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimeline:setTimeSpeed") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimeline_setTimeSpeed'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setTimeSpeed",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimelineNode:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineNode_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineNode:create",argc, 2);
    }
    if (std::strcmp(name, "ccs.ActionTimelineNode:getActionTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineNode_getActionTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:getActionTimeline",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineNode:getRoot") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineNode_getRoot'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:getRoot",argc, 0);
    }
    if (std::strcmp(name, "ccs.ActionTimelineNode:setActionTimeline") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineNode_setActionTimeline'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:setActionTimeline",argc, 1);
    }
    if (std::strcmp(name, "ccs.ActionTimelineNode:setRoot") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ActionTimelineNode_setRoot'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:setRoot",argc, 1);
    }
    if (std::strcmp(name, "ccs.BoneNode:addSkin") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.BoneNode:addSkin",argc, 2);
    }
    if (std::strcmp(name, "ccs.BoneNode:create") == 0) {
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", "ccs.BoneNode:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawColor") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_getDebugDrawColor'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getDebugDrawColor",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawLength") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_getDebugDrawLength'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getDebugDrawLength",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:getDebugDrawWidth") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_getDebugDrawWidth'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getDebugDrawWidth",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:getRootSkeletonNode") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_getRootSkeletonNode'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getRootSkeletonNode",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:isDebugDrawEnabled") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_isDebugDrawEnabled'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:isDebugDrawEnabled",argc, 0);
    }
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawEnabled") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_setDebugDrawEnabled'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:setDebugDrawEnabled",argc, 1);
    }
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawLength") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_setDebugDrawLength'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:setDebugDrawLength",argc, 1);
    }
    if (std::strcmp(name, "ccs.BoneNode:setDebugDrawWidth") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_BoneNode_setDebugDrawWidth'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:setDebugDrawWidth",argc, 1);
    }
    if (std::strcmp(name, "ccs.SkeletonNode:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_SkeletonNode_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SkeletonNode:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComExtensionData:create") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComExtensionData_create'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComExtensionData:create",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComExtensionData:createInstance") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComExtensionData_createInstance'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ComExtensionData:createInstance",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComExtensionData:getActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComExtensionData_getActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComExtensionData:getActionTag",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComExtensionData:getCustomProperty") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComExtensionData_getCustomProperty'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComExtensionData:getCustomProperty",argc, 0);
    }
    if (std::strcmp(name, "ccs.ComExtensionData:setActionTag") == 0) {
        if (attempted != -1) { tolua_error(L, "invalid arguments in function 'lua_cc_studio_ComExtensionData_setActionTag'", nullptr); return 0; }
        return luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComExtensionData:setActionTag",argc, 1);
    }
    return luaL_error(L,"unmapped Studio binding: %s",name);
}
}

#undef LUA_CLS_DEF_BASE
#define LUA_CLS_DEF_BASE(T_, TType_, TName_, BT_, BName_, Ctor_, Dtor_) \
    const char* typeName=(TName_); \
    const char* castName=(TType_); \
    using current_type=T_; \
    tolua_usertype(lua_S,(TName_)); \
    tolua_cclass(lua_S,(TType_),(TName_),studio_binding::parent_name<BT_>(BName_),(Dtor_)); \
    tolua_beginmodule(lua_S,(TType_));
#undef LUA_INVOKE_HEADER
#define LUA_INVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	studio_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, true); \
	const auto* studio_self = tolua_tousertype(lua_S, 1, nullptr); \
	(void)studio_self; \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = true; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_SINVOKE_HEADER
#define LUA_SINVOKE_HEADER(CName_, FName_) \
	constexpr auto LUA_OBJ_TYPE = CName_; \
	constexpr auto LUA_FNAME = FName_; \
	studio_binding::check_receiver(lua_S, LUA_OBJ_TYPE, LUA_FNAME, false); \
	const int argc = lua_gettop(lua_S) - 1; \
	constexpr bool binding_member_self = false; \
	int arg_cur = -1; \
	bool ok = false;

#undef LUA_TRY_INVOKE
#define LUA_TRY_INVOKE(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto studio_fn = (Fn_); \
		arg_cur = 0; \
		if (studio_binding::prepare(lua_S, LUA_FNAME, studio_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, studio_fn, &native_results); \
			if (ok) { lua_settop(lua_S, 1); return 1; } \
		} \
	}

#undef LUA_TRY_INVOKE_R
#define LUA_TRY_INVOKE_R(ARGC_, Fn_) \
	if (argc == (ARGC_)) { \
		auto studio_fn = (Fn_); \
		arg_cur = 0; \
		if (studio_binding::prepare(lua_S, LUA_FNAME, studio_fn)) { \
			int native_results = 0; \
			ok = lua::_invoke_native<true, true, false, binding_member_self>( \
				lua_S, arg_cur, studio_fn, &native_results); \
			if (ok) { return native_results; } \
		} \
	}

#undef LUA_INVOKE_FOOTER
#define LUA_INVOKE_FOOTER(Expected_) \
    return studio_binding::fail(lua_S, LUA_FNAME, argc, arg_cur);
#undef LUA_SINVOKE_FOOTER
#define LUA_SINVOKE_FOOTER(Expected_) LUA_INVOKE_FOOTER(Expected_)

#undef LUA_TRY_INVOKE_OVERLOAD
#define LUA_TRY_INVOKE_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE(ARGC_, Fn_)
#undef LUA_TRY_INVOKE_R_OVERLOAD
#define LUA_TRY_INVOKE_R_OVERLOAD(ARGC_, Fn_) LUA_TRY_INVOKE_R(ARGC_, Fn_)
