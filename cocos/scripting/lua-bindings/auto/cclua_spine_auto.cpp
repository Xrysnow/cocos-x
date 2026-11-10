#include "cclua_spine_auto.hpp"
#include "base/ccConfig.h"
#ifdef CC_USE_SPINE
#include "lua_conversion/lua_conversion.hpp"
#include "spine/spine-cocos2dx.h"

int lua_spine_SkeletonRenderer_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getBoundingBox(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getBoundingBox");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getBoundingBox));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getDebugBonesEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getDebugBonesEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getDebugBonesEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getDebugBoundingRectEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getDebugBoundingRectEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getDebugBoundingRectEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getDebugMeshesEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getDebugMeshesEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getDebugMeshesEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getDebugSlotsEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getDebugSlotsEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getDebugSlotsEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_getTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:getTimeScale");
	LUA_TRY_INVOKE_R(0, static_cast<float(spine::SkeletonRenderer::*)()const>(&spine::SkeletonRenderer::getTimeScale));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_isTwoColorTint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:isTwoColorTint");
	LUA_TRY_INVOKE_R(0, static_cast<bool(spine::SkeletonRenderer::*)()>(&spine::SkeletonRenderer::isTwoColorTint));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_setAttachment_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setAttachment");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(spine::SkeletonRenderer::*)(const std::string&, const std::string&)>(&spine::SkeletonRenderer::setAttachment)));
	LUA_INVOKE_FOOTER("2");
}
int lua_spine_SkeletonRenderer_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(const cocos2d::BlendFunc&)>(&spine::SkeletonRenderer::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setBonesToSetupPose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setBonesToSetupPose");
	LUA_TRY_INVOKE(0, static_cast<void(spine::SkeletonRenderer::*)()>(&spine::SkeletonRenderer::setBonesToSetupPose));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_setDebugBonesEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setDebugBonesEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(bool)>(&spine::SkeletonRenderer::setDebugBonesEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setDebugBoundingRectEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setDebugBoundingRectEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(bool)>(&spine::SkeletonRenderer::setDebugBoundingRectEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setDebugMeshesEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setDebugMeshesEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(bool)>(&spine::SkeletonRenderer::setDebugMeshesEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setDebugSlotsEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setDebugSlotsEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(bool)>(&spine::SkeletonRenderer::setDebugSlotsEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setSkin_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setSkin");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(const std::string&)>(&spine::SkeletonRenderer::setSkin));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setSlotsRange(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setSlotsRange");
	LUA_TRY_INVOKE(2, (static_cast<void(spine::SkeletonRenderer::*)(int, int)>(&spine::SkeletonRenderer::setSlotsRange)));
	LUA_INVOKE_FOOTER("2");
}
int lua_spine_SkeletonRenderer_setSlotsToSetupPose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setSlotsToSetupPose");
	LUA_TRY_INVOKE(0, static_cast<void(spine::SkeletonRenderer::*)()>(&spine::SkeletonRenderer::setSlotsToSetupPose));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_setTimeScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setTimeScale");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(float)>(&spine::SkeletonRenderer::setTimeScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_setToSetupPose(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setToSetupPose");
	LUA_TRY_INVOKE(0, static_cast<void(spine::SkeletonRenderer::*)()>(&spine::SkeletonRenderer::setToSetupPose));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonRenderer_setTwoColorTint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:setTwoColorTint");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonRenderer::*)(bool)>(&spine::SkeletonRenderer::setTwoColorTint));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonRenderer_createWithFile_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("sp.SkeletonRenderer", "sp.SkeletonRenderer:createWithFile");
	LUA_TRY_INVOKE_R(3, (static_cast<spine::SkeletonRenderer*(*)(const std::string&, const std::string&, float)>(&spine::SkeletonRenderer::createWithFile)));
	LUA_TRY_INVOKE_R(2, ([](const std::string& arg0,const std::string& arg1){{return spine::SkeletonRenderer::createWithFile(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Spine_spSkeletonRenderer(lua_State* lua_S)
{
	LUA_ENTRY("sp");
	LUA_CLS_DEF_BASE(spine::SkeletonRenderer, "SkeletonRenderer", "sp.SkeletonRenderer",
		spine::SkeletonRenderer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_spine_SkeletonRenderer_getBlendFunc);
	LUA_METHOD("getBoundingBox", lua_spine_SkeletonRenderer_getBoundingBox);
	LUA_METHOD("getDebugBonesEnabled", lua_spine_SkeletonRenderer_getDebugBonesEnabled);
	LUA_METHOD("getDebugBoundingRectEnabled", lua_spine_SkeletonRenderer_getDebugBoundingRectEnabled);
	LUA_METHOD("getDebugMeshesEnabled", lua_spine_SkeletonRenderer_getDebugMeshesEnabled);
	LUA_METHOD("getDebugSlotsEnabled", lua_spine_SkeletonRenderer_getDebugSlotsEnabled);
	LUA_METHOD("getTimeScale", lua_spine_SkeletonRenderer_getTimeScale);
	LUA_METHOD("isTwoColorTint", lua_spine_SkeletonRenderer_isTwoColorTint);
	LUA_METHOD("setAttachment", lua_spine_SkeletonRenderer_setAttachment_1);
	LUA_METHOD("setBlendFunc", lua_spine_SkeletonRenderer_setBlendFunc);
	LUA_METHOD("setBonesToSetupPose", lua_spine_SkeletonRenderer_setBonesToSetupPose);
	LUA_METHOD("setDebugBonesEnabled", lua_spine_SkeletonRenderer_setDebugBonesEnabled);
	LUA_METHOD("setDebugBoundingRectEnabled", lua_spine_SkeletonRenderer_setDebugBoundingRectEnabled);
	LUA_METHOD("setDebugMeshesEnabled", lua_spine_SkeletonRenderer_setDebugMeshesEnabled);
	LUA_METHOD("setDebugSlotsEnabled", lua_spine_SkeletonRenderer_setDebugSlotsEnabled);
	LUA_METHOD("setSkin", lua_spine_SkeletonRenderer_setSkin_1);
	LUA_METHOD("setSlotsRange", lua_spine_SkeletonRenderer_setSlotsRange);
	LUA_METHOD("setSlotsToSetupPose", lua_spine_SkeletonRenderer_setSlotsToSetupPose);
	LUA_METHOD("setTimeScale", lua_spine_SkeletonRenderer_setTimeScale);
	LUA_METHOD("setToSetupPose", lua_spine_SkeletonRenderer_setToSetupPose);
	LUA_METHOD("setTwoColorTint", lua_spine_SkeletonRenderer_setTwoColorTint);
	LUA_METHOD("createWithFile", lua_spine_SkeletonRenderer_createWithFile_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_spine_SkeletonAnimation_clearTrack(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:clearTrack");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonAnimation::*)(int)>(&spine::SkeletonAnimation::clearTrack));
	LUA_TRY_INVOKE(0, [](spine::SkeletonAnimation* obj){{return obj->clearTrack();}});
	LUA_INVOKE_FOOTER("0,1");
}
int lua_spine_SkeletonAnimation_clearTracks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:clearTracks");
	LUA_TRY_INVOKE(0, static_cast<void(spine::SkeletonAnimation::*)()>(&spine::SkeletonAnimation::clearTracks));
	LUA_INVOKE_FOOTER("0");
}
int lua_spine_SkeletonAnimation_setEmptyAnimations(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setEmptyAnimations");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonAnimation::*)(float)>(&spine::SkeletonAnimation::setEmptyAnimations));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonAnimation_setMix(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setMix");
	LUA_TRY_INVOKE(3, (static_cast<void(spine::SkeletonAnimation::*)(const std::string&, const std::string&, float)>(&spine::SkeletonAnimation::setMix)));
	LUA_INVOKE_FOOTER("3");
}
int lua_spine_SkeletonAnimation_setPostUpdateWorldTransformsListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setPostUpdateWorldTransformsListener");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonAnimation::*)(const spine::UpdateWorldTransformsListener&)>(&spine::SkeletonAnimation::setPostUpdateWorldTransformsListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonAnimation_setPreUpdateWorldTransformsListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setPreUpdateWorldTransformsListener");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonAnimation::*)(const spine::UpdateWorldTransformsListener&)>(&spine::SkeletonAnimation::setPreUpdateWorldTransformsListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonAnimation_setUpdateOnlyIfVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:setUpdateOnlyIfVisible");
	LUA_TRY_INVOKE(1, static_cast<void(spine::SkeletonAnimation::*)(bool)>(&spine::SkeletonAnimation::setUpdateOnlyIfVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_spine_SkeletonAnimation_createWithBinaryFile_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:createWithBinaryFile");
	LUA_TRY_INVOKE_R(3, (static_cast<spine::SkeletonAnimation*(*)(const std::string&, const std::string&, float)>(&spine::SkeletonAnimation::createWithBinaryFile)));
	LUA_TRY_INVOKE_R(2, ([](const std::string& arg0,const std::string& arg1){{return spine::SkeletonAnimation::createWithBinaryFile(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int lua_spine_SkeletonAnimation_createWithJsonFile_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("sp.SkeletonAnimation", "sp.SkeletonAnimation:createWithJsonFile");
	LUA_TRY_INVOKE_R(3, (static_cast<spine::SkeletonAnimation*(*)(const std::string&, const std::string&, float)>(&spine::SkeletonAnimation::createWithJsonFile)));
	LUA_TRY_INVOKE_R(2, ([](const std::string& arg0,const std::string& arg1){{return spine::SkeletonAnimation::createWithJsonFile(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Spine_spSkeletonAnimation(lua_State* lua_S)
{
	LUA_ENTRY("sp");
	LUA_CLS_DEF_BASE(spine::SkeletonAnimation, "SkeletonAnimation", "sp.SkeletonAnimation",
		spine::SkeletonAnimation, "sp.SkeletonRenderer",
		nullptr, nullptr);
	LUA_METHOD("clearTrack", lua_spine_SkeletonAnimation_clearTrack);
	LUA_METHOD("clearTracks", lua_spine_SkeletonAnimation_clearTracks);
	LUA_METHOD("setEmptyAnimations", lua_spine_SkeletonAnimation_setEmptyAnimations);
	LUA_METHOD("setMix", lua_spine_SkeletonAnimation_setMix);
	LUA_METHOD("setPostUpdateWorldTransformsListener", lua_spine_SkeletonAnimation_setPostUpdateWorldTransformsListener);
	LUA_METHOD("setPreUpdateWorldTransformsListener", lua_spine_SkeletonAnimation_setPreUpdateWorldTransformsListener);
	LUA_METHOD("setUpdateOnlyIfVisible", lua_spine_SkeletonAnimation_setUpdateOnlyIfVisible);
	LUA_METHOD("createWithBinaryFile", lua_spine_SkeletonAnimation_createWithBinaryFile_1);
	LUA_METHOD("createWithJsonFile", lua_spine_SkeletonAnimation_createWithJsonFile_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_spine(lua_State* lua_S)
{
#include "base/ccConfig.h"
#ifdef CC_USE_SPINE
	tolua_open(lua_S);
	luaReg_Spine_spSkeletonRenderer(lua_S);
	luaReg_Spine_spSkeletonAnimation(lua_S);
	return 0;
#else
	return 0;
#endif
}
