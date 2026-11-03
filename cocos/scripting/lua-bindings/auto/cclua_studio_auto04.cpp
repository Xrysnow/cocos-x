#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

int lua_cocostudio_ComRender_getNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComRender", "ccs.ComRender:getNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::ComRender::*)()>(&cocostudio::ComRender::getNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComRender_setNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComRender", "ccs.ComRender:setNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComRender::*)(cocos2d::Node*)>(&cocostudio::ComRender::setNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_ComRender_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComRender", "ccs.ComRender:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocostudio::ComRender*(*)(cocos2d::Node*, const char*)>(&cocostudio::ComRender::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::ComRender*(*)()>(&cocostudio::ComRender::create));
	LUA_SINVOKE_FOOTER("0,2");
}
int lua_cocostudio_ComRender_createInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ComRender", "ccs.ComRender:createInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Ref*(*)()>(&cocostudio::ComRender::createInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsComRender(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::ComRender, "ComRender", "ccs.ComRender",
		cocos2d::Component, "ccs.cocos2d.Component",
		nullptr, nullptr);
	LUA_METHOD("getNode", lua_cocostudio_ComRender_getNode);
	LUA_METHOD("setNode", lua_cocostudio_ComRender_setNode);
	LUA_METHOD("create", lua_cocostudio_ComRender_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComRender_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_GUIReader_getFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:getFilePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::GUIReader::*)()const>(&cocostudio::GUIReader::getFilePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_GUIReader_getVersionInteger(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:getVersionInteger");
	LUA_TRY_INVOKE_R(1, static_cast<int(cocostudio::GUIReader::*)(const char*)>(&cocostudio::GUIReader::getVersionInteger));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_GUIReader_widgetFromBinaryFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:widgetFromBinaryFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Widget*(cocostudio::GUIReader::*)(const char*)>(&cocostudio::GUIReader::widgetFromBinaryFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_GUIReader_widgetFromJsonFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:widgetFromJsonFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ui::Widget*(cocostudio::GUIReader::*)(const char*)>(&cocostudio::GUIReader::widgetFromJsonFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_GUIReader_destroyInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:destroyInstance");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocostudio::GUIReader::destroyInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_GUIReader_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::GUIReader*(*)()>(&cocostudio::GUIReader::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsGUIReader(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::GUIReader, "GUIReader", "ccs.GUIReader",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("getFilePath", lua_cocostudio_GUIReader_getFilePath);
	LUA_METHOD("getVersionInteger", lua_cocostudio_GUIReader_getVersionInteger);
	LUA_METHOD("widgetFromBinaryFile", lua_cocostudio_GUIReader_widgetFromBinaryFile);
	LUA_METHOD("widgetFromJsonFile", lua_cocostudio_GUIReader_widgetFromJsonFile);
	LUA_METHOD("destroyInstance", lua_cocostudio_GUIReader_destroyInstance);
	LUA_METHOD("getInstance", lua_cocostudio_GUIReader_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_SceneReader_getAttachComponentType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SceneReader", "ccs.SceneReader:getAttachComponentType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::SceneReader::AttachComponentType(cocostudio::SceneReader::*)()>(&cocostudio::SceneReader::getAttachComponentType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_SceneReader_getNodeByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SceneReader", "ccs.SceneReader:getNodeByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Node*(cocostudio::SceneReader::*)(int)>(&cocostudio::SceneReader::getNodeByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_SceneReader_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SceneReader", "ccs.SceneReader:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::SceneReader*(*)()>(&cocostudio::SceneReader::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocostudio_SceneReader_sceneReaderVersion(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SceneReader", "ccs.SceneReader:sceneReaderVersion");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(*)()>(&cocostudio::SceneReader::sceneReaderVersion));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSceneReader(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF(cocostudio::SceneReader, "SceneReader", "ccs.SceneReader",
		nullptr, nullptr);
	LUA_METHOD("getAttachComponentType", lua_cocostudio_SceneReader_getAttachComponentType);
	LUA_METHOD("getNodeByTag", lua_cocostudio_SceneReader_getNodeByTag);
	LUA_METHOD("getInstance", lua_cocostudio_SceneReader_getInstance);
	LUA_METHOD("sceneReaderVersion", lua_cocostudio_SceneReader_sceneReaderVersion);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimelineCache::*)()>(&cocostudio::timeline::ActionTimelineCache::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineCache_purge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:purge");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimelineCache::*)()>(&cocostudio::timeline::ActionTimelineCache::purge));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineCache_destroyInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:destroyInstance");
	LUA_TRY_INVOKE(0, static_cast<void(*)()>(&cocostudio::timeline::ActionTimelineCache::destroyInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsActionTimelineCache(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF(cocostudio::timeline::ActionTimelineCache, "ActionTimelineCache", "ccs.ActionTimelineCache",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimelineCache_init);
	LUA_METHOD("purge", lua_cocostudio_timeline_ActionTimelineCache_purge);
	LUA_METHOD("destroyInstance", lua_cocostudio_timeline_ActionTimelineCache_destroyInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_Frame_apply(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:apply");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(float)>(&cocostudio::timeline::Frame::apply));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Frame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Frame*(cocostudio::timeline::Frame::*)()>(&cocostudio::timeline::Frame::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_getFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:getFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::getFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_getNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:getNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::getNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_getTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:getTimeline");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Timeline*(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::getTimeline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_getTweenType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:getTweenType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::tweenfunc::TweenType(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::getTweenType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_isEnterWhenPassed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:isEnterWhenPassed");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::Frame::*)()>(&cocostudio::timeline::Frame::isEnterWhenPassed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_isTween(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:isTween");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::isTween));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Frame_setFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setFrameIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(unsigned int)>(&cocostudio::timeline::Frame::setFrameIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Frame_setNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(cocos2d::Node*)>(&cocostudio::timeline::Frame::setNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Frame_setTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(cocostudio::timeline::Timeline*)>(&cocostudio::timeline::Frame::setTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Frame_setTween(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setTween");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(bool)>(&cocostudio::timeline::Frame::setTween));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Frame_setTweenType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setTweenType");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(const cocos2d::tweenfunc::TweenType&)>(&cocostudio::timeline::Frame::setTweenType));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Studio_ccsFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::Frame, "Frame", "ccs.Frame",
		cocos2d::Ref, "ccs.cocos2d.Ref",
		nullptr, nullptr);
	LUA_METHOD("apply", lua_cocostudio_timeline_Frame_apply);
	LUA_METHOD("clone", lua_cocostudio_timeline_Frame_clone);
	LUA_METHOD("getFrameIndex", lua_cocostudio_timeline_Frame_getFrameIndex);
	LUA_METHOD("getNode", lua_cocostudio_timeline_Frame_getNode);
	LUA_METHOD("getTimeline", lua_cocostudio_timeline_Frame_getTimeline);
	LUA_METHOD("getTweenType", lua_cocostudio_timeline_Frame_getTweenType);
	LUA_METHOD("isEnterWhenPassed", lua_cocostudio_timeline_Frame_isEnterWhenPassed);
	LUA_METHOD("isTween", lua_cocostudio_timeline_Frame_isTween);
	LUA_METHOD("setFrameIndex", lua_cocostudio_timeline_Frame_setFrameIndex);
	LUA_METHOD("setNode", lua_cocostudio_timeline_Frame_setNode);
	LUA_METHOD("setTimeline", lua_cocostudio_timeline_Frame_setTimeline);
	LUA_METHOD("setTween", lua_cocostudio_timeline_Frame_setTween);
	LUA_METHOD("setTweenType", lua_cocostudio_timeline_Frame_setTweenType);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_VisibleFrame_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.VisibleFrame", "ccs.VisibleFrame:isVisible");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::VisibleFrame::*)()const>(&cocostudio::timeline::VisibleFrame::isVisible));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_VisibleFrame_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.VisibleFrame", "ccs.VisibleFrame:setVisible");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::VisibleFrame::*)(bool)>(&cocostudio::timeline::VisibleFrame::setVisible));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_VisibleFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.VisibleFrame", "ccs.VisibleFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::VisibleFrame*(*)()>(&cocostudio::timeline::VisibleFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsVisibleFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::VisibleFrame, "VisibleFrame", "ccs.VisibleFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("isVisible", lua_cocostudio_timeline_VisibleFrame_isVisible);
	LUA_METHOD("setVisible", lua_cocostudio_timeline_VisibleFrame_setVisible);
	LUA_METHOD("create", lua_cocostudio_timeline_VisibleFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_TextureFrame_getTextureName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureFrame", "ccs.TextureFrame:getTextureName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::timeline::TextureFrame::*)()const>(&cocostudio::timeline::TextureFrame::getTextureName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_TextureFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.TextureFrame", "ccs.TextureFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::TextureFrame*(*)()>(&cocostudio::timeline::TextureFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsTextureFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::TextureFrame, "TextureFrame", "ccs.TextureFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getTextureName", lua_cocostudio_timeline_TextureFrame_getTextureName);
	LUA_METHOD("create", lua_cocostudio_timeline_TextureFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_RotationFrame_getRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.RotationFrame", "ccs.RotationFrame:getRotation");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::RotationFrame::*)()const>(&cocostudio::timeline::RotationFrame::getRotation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_RotationFrame_setRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.RotationFrame", "ccs.RotationFrame:setRotation");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::RotationFrame::*)(float)>(&cocostudio::timeline::RotationFrame::setRotation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_RotationFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.RotationFrame", "ccs.RotationFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::RotationFrame*(*)()>(&cocostudio::timeline::RotationFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsRotationFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::RotationFrame, "RotationFrame", "ccs.RotationFrame",
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getRotation", lua_cocostudio_timeline_RotationFrame_getRotation);
	LUA_METHOD("setRotation", lua_cocostudio_timeline_RotationFrame_setRotation);
	LUA_METHOD("create", lua_cocostudio_timeline_RotationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
