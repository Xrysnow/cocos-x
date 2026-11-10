#include "cclua_studio_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

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
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::ComAudio::*)(const char*, bool)>(&cocostudio::ComAudio::playBackgroundMusic)));
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComAudio::*)(const char*)>(&cocostudio::ComAudio::playBackgroundMusic));
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::playBackgroundMusic));
	LUA_INVOKE_FOOTER("0,1,2");
}
int lua_cocostudio_ComAudio_playEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:playEffect");
	LUA_TRY_INVOKE_R(2, (static_cast<unsigned int(cocostudio::ComAudio::*)(const char*, bool)>(&cocostudio::ComAudio::playEffect)));
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
int lua_cocostudio_ComAudio_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:start");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::start));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_ComAudio_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComAudio", "ccs.ComAudio:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::ComAudio::*)()>(&cocostudio::ComAudio::stop));
	LUA_INVOKE_FOOTER("0");
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
		cocostudio::ComAudio, "cc.Component",
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
	LUA_METHOD("start", lua_cocostudio_ComAudio_start);
	LUA_METHOD("stop", lua_cocostudio_ComAudio_stop);
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
		cocostudio::ComController, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_ComController_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComController_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::ComRender*(*)(cocos2d::Node*, const char*)>(&cocostudio::ComRender::create)));
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
		cocostudio::ComRender, "cc.Component",
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
int lua_cocostudio_GUIReader_setFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.GUIReader", "ccs.GUIReader:setFilePath");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::GUIReader::*)(std::string_view)>(&cocostudio::GUIReader::setFilePath));
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
		cocostudio::GUIReader, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getFilePath", lua_cocostudio_GUIReader_getFilePath);
	LUA_METHOD("getVersionInteger", lua_cocostudio_GUIReader_getVersionInteger);
	LUA_METHOD("setFilePath", lua_cocostudio_GUIReader_setFilePath);
	LUA_METHOD("widgetFromBinaryFile", lua_cocostudio_GUIReader_widgetFromBinaryFile);
	LUA_METHOD("widgetFromJsonFile", lua_cocostudio_GUIReader_widgetFromJsonFile);
	LUA_METHOD("getInstance", lua_cocostudio_GUIReader_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_SceneReader_createNodeWithSceneFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SceneReader", "ccs.SceneReader:createNodeWithSceneFile");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Node*(cocostudio::SceneReader::*)(std::string_view, cocostudio::SceneReader::AttachComponentType)>(&cocostudio::SceneReader::createNodeWithSceneFile)));
	LUA_TRY_INVOKE_R(1, ([](cocostudio::SceneReader* obj,std::string_view arg0){{return obj->createNodeWithSceneFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
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
	LUA_CLS_DEF_BASE(cocostudio::SceneReader, "SceneReader", "ccs.SceneReader",
		cocostudio::SceneReader, "",
		nullptr, nullptr);
	LUA_METHOD("createNodeWithSceneFile", lua_cocostudio_SceneReader_createNodeWithSceneFile);
	LUA_METHOD("getAttachComponentType", lua_cocostudio_SceneReader_getAttachComponentType);
	LUA_METHOD("getNodeByTag", lua_cocostudio_SceneReader_getNodeByTag);
	LUA_METHOD("getInstance", lua_cocostudio_SceneReader_getInstance);
	LUA_METHOD("sceneReaderVersion", lua_cocostudio_SceneReader_sceneReaderVersion);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineCache_createActionFromContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:createActionFromContent");
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view, std::string_view)>(&cocostudio::timeline::ActionTimelineCache::createActionFromContent)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimelineCache_createActionFromJson(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:createActionFromJson");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::createActionFromJson));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_createActionWithFlatBuffersFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:createActionWithFlatBuffersFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::createActionWithFlatBuffersFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_createActionWithFlatBuffersForSimulator(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:createActionWithFlatBuffersForSimulator");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::createActionWithFlatBuffersForSimulator));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimelineCache::*)()>(&cocostudio::timeline::ActionTimelineCache::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:loadAnimationActionWithContent");
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view, std::string_view)>(&cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithContent)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:loadAnimationActionWithFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:loadAnimationActionWithFlatBuffersFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::loadAnimationActionWithFlatBuffersFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_purge(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:purge");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimelineCache::*)()>(&cocostudio::timeline::ActionTimelineCache::purge));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineCache_removeAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:removeAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineCache::*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::removeAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_createAction(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:createAction");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimeline*(*)(std::string_view)>(&cocostudio::timeline::ActionTimelineCache::createAction));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineCache", "ccs.ActionTimelineCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimelineCache*(*)()>(&cocostudio::timeline::ActionTimelineCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsActionTimelineCache(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimelineCache, "ActionTimelineCache", "ccs.ActionTimelineCache",
		cocostudio::timeline::ActionTimelineCache, "",
		nullptr, nullptr);
	LUA_METHOD("createActionFromContent", lua_cocostudio_timeline_ActionTimelineCache_createActionFromContent);
	LUA_METHOD("createActionFromJson", lua_cocostudio_timeline_ActionTimelineCache_createActionFromJson);
	LUA_METHOD("createActionWithFlatBuffersFile", lua_cocostudio_timeline_ActionTimelineCache_createActionWithFlatBuffersFile);
	LUA_METHOD("createActionWithFlatBuffersForSimulator", lua_cocostudio_timeline_ActionTimelineCache_createActionWithFlatBuffersForSimulator);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimelineCache_init);
	LUA_METHOD("loadAnimationActionWithContent", lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithContent);
	LUA_METHOD("loadAnimationActionWithFile", lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithFile);
	LUA_METHOD("loadAnimationActionWithFlatBuffersFile", lua_cocostudio_timeline_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile);
	LUA_METHOD("purge", lua_cocostudio_timeline_ActionTimelineCache_purge);
	LUA_METHOD("removeAction", lua_cocostudio_timeline_ActionTimelineCache_removeAction);
	LUA_METHOD("createAction", lua_cocostudio_timeline_ActionTimelineCache_createAction);
	LUA_METHOD("getInstance", lua_cocostudio_timeline_ActionTimelineCache_getInstance);
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
int lua_cocostudio_timeline_Frame_getEasingParams(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:getEasingParams");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<float>&(cocostudio::timeline::Frame::*)()const>(&cocostudio::timeline::Frame::getEasingParams));
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
int lua_cocostudio_timeline_Frame_setEasingParams(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Frame", "ccs.Frame:setEasingParams");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Frame::*)(const std::vector<float>&)>(&cocostudio::timeline::Frame::setEasingParams));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::timeline::Frame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("apply", lua_cocostudio_timeline_Frame_apply);
	LUA_METHOD("clone", lua_cocostudio_timeline_Frame_clone);
	LUA_METHOD("getEasingParams", lua_cocostudio_timeline_Frame_getEasingParams);
	LUA_METHOD("getFrameIndex", lua_cocostudio_timeline_Frame_getFrameIndex);
	LUA_METHOD("getNode", lua_cocostudio_timeline_Frame_getNode);
	LUA_METHOD("getTimeline", lua_cocostudio_timeline_Frame_getTimeline);
	LUA_METHOD("getTweenType", lua_cocostudio_timeline_Frame_getTweenType);
	LUA_METHOD("isEnterWhenPassed", lua_cocostudio_timeline_Frame_isEnterWhenPassed);
	LUA_METHOD("isTween", lua_cocostudio_timeline_Frame_isTween);
	LUA_METHOD("setEasingParams", lua_cocostudio_timeline_Frame_setEasingParams);
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
		cocostudio::timeline::VisibleFrame, "ccs.Frame",
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
int lua_cocostudio_timeline_TextureFrame_setTextureName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.TextureFrame", "ccs.TextureFrame:setTextureName");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::TextureFrame::*)(std::string_view)>(&cocostudio::timeline::TextureFrame::setTextureName));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::timeline::TextureFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getTextureName", lua_cocostudio_timeline_TextureFrame_getTextureName);
	LUA_METHOD("setTextureName", lua_cocostudio_timeline_TextureFrame_setTextureName);
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
		cocostudio::timeline::RotationFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getRotation", lua_cocostudio_timeline_RotationFrame_getRotation);
	LUA_METHOD("setRotation", lua_cocostudio_timeline_RotationFrame_setRotation);
	LUA_METHOD("create", lua_cocostudio_timeline_RotationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_SkewFrame_getSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkewFrame", "ccs.SkewFrame:getSkewX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::SkewFrame::*)()const>(&cocostudio::timeline::SkewFrame::getSkewX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_SkewFrame_getSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkewFrame", "ccs.SkewFrame:getSkewY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::SkewFrame::*)()const>(&cocostudio::timeline::SkewFrame::getSkewY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_SkewFrame_setSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkewFrame", "ccs.SkewFrame:setSkewX");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::SkewFrame::*)(float)>(&cocostudio::timeline::SkewFrame::setSkewX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_SkewFrame_setSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkewFrame", "ccs.SkewFrame:setSkewY");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::SkewFrame::*)(float)>(&cocostudio::timeline::SkewFrame::setSkewY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_SkewFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.SkewFrame", "ccs.SkewFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::SkewFrame*(*)()>(&cocostudio::timeline::SkewFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsSkewFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::SkewFrame, "SkewFrame", "ccs.SkewFrame",
		cocostudio::timeline::SkewFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getSkewX", lua_cocostudio_timeline_SkewFrame_getSkewX);
	LUA_METHOD("getSkewY", lua_cocostudio_timeline_SkewFrame_getSkewY);
	LUA_METHOD("setSkewX", lua_cocostudio_timeline_SkewFrame_setSkewX);
	LUA_METHOD("setSkewY", lua_cocostudio_timeline_SkewFrame_setSkewY);
	LUA_METHOD("create", lua_cocostudio_timeline_SkewFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_RotationSkewFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.RotationSkewFrame", "ccs.RotationSkewFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::RotationSkewFrame*(*)()>(&cocostudio::timeline::RotationSkewFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsRotationSkewFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::RotationSkewFrame, "RotationSkewFrame", "ccs.RotationSkewFrame",
		cocostudio::timeline::RotationSkewFrame, "ccs.SkewFrame",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_timeline_RotationSkewFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_PositionFrame_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Point(cocostudio::timeline::PositionFrame::*)()const>(&cocostudio::timeline::PositionFrame::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_PositionFrame_getX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:getX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::PositionFrame::*)()const>(&cocostudio::timeline::PositionFrame::getX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_PositionFrame_getY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:getY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::PositionFrame::*)()const>(&cocostudio::timeline::PositionFrame::getY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_PositionFrame_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::PositionFrame::*)(const cocos2d::Point&)>(&cocostudio::timeline::PositionFrame::setPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_PositionFrame_setX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:setX");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::PositionFrame::*)(float)>(&cocostudio::timeline::PositionFrame::setX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_PositionFrame_setY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:setY");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::PositionFrame::*)(float)>(&cocostudio::timeline::PositionFrame::setY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_PositionFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.PositionFrame", "ccs.PositionFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::PositionFrame*(*)()>(&cocostudio::timeline::PositionFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsPositionFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::PositionFrame, "PositionFrame", "ccs.PositionFrame",
		cocostudio::timeline::PositionFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getPosition", lua_cocostudio_timeline_PositionFrame_getPosition);
	LUA_METHOD("getX", lua_cocostudio_timeline_PositionFrame_getX);
	LUA_METHOD("getY", lua_cocostudio_timeline_PositionFrame_getY);
	LUA_METHOD("setPosition", lua_cocostudio_timeline_PositionFrame_setPosition);
	LUA_METHOD("setX", lua_cocostudio_timeline_PositionFrame_setX);
	LUA_METHOD("setY", lua_cocostudio_timeline_PositionFrame_setY);
	LUA_METHOD("create", lua_cocostudio_timeline_PositionFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ScaleFrame_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:getScaleX");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::ScaleFrame::*)()const>(&cocostudio::timeline::ScaleFrame::getScaleX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ScaleFrame_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:getScaleY");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::ScaleFrame::*)()const>(&cocostudio::timeline::ScaleFrame::getScaleY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ScaleFrame_setScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:setScale");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ScaleFrame::*)(float)>(&cocostudio::timeline::ScaleFrame::setScale));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ScaleFrame_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:setScaleX");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ScaleFrame::*)(float)>(&cocostudio::timeline::ScaleFrame::setScaleX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ScaleFrame_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:setScaleY");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ScaleFrame::*)(float)>(&cocostudio::timeline::ScaleFrame::setScaleY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ScaleFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ScaleFrame", "ccs.ScaleFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ScaleFrame*(*)()>(&cocostudio::timeline::ScaleFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsScaleFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ScaleFrame, "ScaleFrame", "ccs.ScaleFrame",
		cocostudio::timeline::ScaleFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getScaleX", lua_cocostudio_timeline_ScaleFrame_getScaleX);
	LUA_METHOD("getScaleY", lua_cocostudio_timeline_ScaleFrame_getScaleY);
	LUA_METHOD("setScale", lua_cocostudio_timeline_ScaleFrame_setScale);
	LUA_METHOD("setScaleX", lua_cocostudio_timeline_ScaleFrame_setScaleX);
	LUA_METHOD("setScaleY", lua_cocostudio_timeline_ScaleFrame_setScaleY);
	LUA_METHOD("create", lua_cocostudio_timeline_ScaleFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_AnchorPointFrame_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnchorPointFrame", "ccs.AnchorPointFrame:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Point(cocostudio::timeline::AnchorPointFrame::*)()const>(&cocostudio::timeline::AnchorPointFrame::getAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_AnchorPointFrame_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AnchorPointFrame", "ccs.AnchorPointFrame:setAnchorPoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::AnchorPointFrame::*)(const cocos2d::Point&)>(&cocostudio::timeline::AnchorPointFrame::setAnchorPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_AnchorPointFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.AnchorPointFrame", "ccs.AnchorPointFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::AnchorPointFrame*(*)()>(&cocostudio::timeline::AnchorPointFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsAnchorPointFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::AnchorPointFrame, "AnchorPointFrame", "ccs.AnchorPointFrame",
		cocostudio::timeline::AnchorPointFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getAnchorPoint", lua_cocostudio_timeline_AnchorPointFrame_getAnchorPoint);
	LUA_METHOD("setAnchorPoint", lua_cocostudio_timeline_AnchorPointFrame_setAnchorPoint);
	LUA_METHOD("create", lua_cocostudio_timeline_AnchorPointFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_InnerActionFrame_getEndFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:getEndFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::InnerActionFrame::*)()const>(&cocostudio::timeline::InnerActionFrame::getEndFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_InnerActionFrame_getInnerActionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:getInnerActionType");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::InnerActionType(cocostudio::timeline::InnerActionFrame::*)()const>(&cocostudio::timeline::InnerActionFrame::getInnerActionType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_InnerActionFrame_getSingleFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:getSingleFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::InnerActionFrame::*)()const>(&cocostudio::timeline::InnerActionFrame::getSingleFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_InnerActionFrame_getStartFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:getStartFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::InnerActionFrame::*)()const>(&cocostudio::timeline::InnerActionFrame::getStartFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_InnerActionFrame_setAnimationName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setAnimationName");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(std::string_view)>(&cocostudio::timeline::InnerActionFrame::setAnimationName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_setEndFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setEndFrameIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(int)>(&cocostudio::timeline::InnerActionFrame::setEndFrameIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_setEnterWithName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setEnterWithName");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(bool)>(&cocostudio::timeline::InnerActionFrame::setEnterWithName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_setInnerActionType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setInnerActionType");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(cocostudio::timeline::InnerActionType)>(&cocostudio::timeline::InnerActionFrame::setInnerActionType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_setSingleFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setSingleFrameIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(int)>(&cocostudio::timeline::InnerActionFrame::setSingleFrameIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_setStartFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:setStartFrameIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::InnerActionFrame::*)(int)>(&cocostudio::timeline::InnerActionFrame::setStartFrameIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_InnerActionFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.InnerActionFrame", "ccs.InnerActionFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::InnerActionFrame*(*)()>(&cocostudio::timeline::InnerActionFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsInnerActionFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::InnerActionFrame, "InnerActionFrame", "ccs.InnerActionFrame",
		cocostudio::timeline::InnerActionFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getEndFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getEndFrameIndex);
	LUA_METHOD("getInnerActionType", lua_cocostudio_timeline_InnerActionFrame_getInnerActionType);
	LUA_METHOD("getSingleFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getSingleFrameIndex);
	LUA_METHOD("getStartFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getStartFrameIndex);
	LUA_METHOD("setAnimationName", lua_cocostudio_timeline_InnerActionFrame_setAnimationName);
	LUA_METHOD("setEndFrameIndex", lua_cocostudio_timeline_InnerActionFrame_setEndFrameIndex);
	LUA_METHOD("setEnterWithName", lua_cocostudio_timeline_InnerActionFrame_setEnterWithName);
	LUA_METHOD("setInnerActionType", lua_cocostudio_timeline_InnerActionFrame_setInnerActionType);
	LUA_METHOD("setSingleFrameIndex", lua_cocostudio_timeline_InnerActionFrame_setSingleFrameIndex);
	LUA_METHOD("setStartFrameIndex", lua_cocostudio_timeline_InnerActionFrame_setStartFrameIndex);
	LUA_METHOD("create", lua_cocostudio_timeline_InnerActionFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ColorFrame_getColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ColorFrame", "ccs.ColorFrame:getColor");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Color3B(cocostudio::timeline::ColorFrame::*)()const>(&cocostudio::timeline::ColorFrame::getColor));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ColorFrame_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ColorFrame", "ccs.ColorFrame:setColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ColorFrame::*)(const cocos2d::Color3B&)>(&cocostudio::timeline::ColorFrame::setColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ColorFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ColorFrame", "ccs.ColorFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ColorFrame*(*)()>(&cocostudio::timeline::ColorFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsColorFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ColorFrame, "ColorFrame", "ccs.ColorFrame",
		cocostudio::timeline::ColorFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getColor", lua_cocostudio_timeline_ColorFrame_getColor);
	LUA_METHOD("setColor", lua_cocostudio_timeline_ColorFrame_setColor);
	LUA_METHOD("create", lua_cocostudio_timeline_ColorFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_AlphaFrame_getAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AlphaFrame", "ccs.AlphaFrame:getAlpha");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocostudio::timeline::AlphaFrame::*)()const>(&cocostudio::timeline::AlphaFrame::getAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_AlphaFrame_setAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.AlphaFrame", "ccs.AlphaFrame:setAlpha");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::AlphaFrame::*)(uint8_t)>(&cocostudio::timeline::AlphaFrame::setAlpha));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_AlphaFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.AlphaFrame", "ccs.AlphaFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::AlphaFrame*(*)()>(&cocostudio::timeline::AlphaFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsAlphaFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::AlphaFrame, "AlphaFrame", "ccs.AlphaFrame",
		cocostudio::timeline::AlphaFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getAlpha", lua_cocostudio_timeline_AlphaFrame_getAlpha);
	LUA_METHOD("setAlpha", lua_cocostudio_timeline_AlphaFrame_setAlpha);
	LUA_METHOD("create", lua_cocostudio_timeline_AlphaFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_EventFrame_getEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:getEvent");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocostudio::timeline::EventFrame::*)()const>(&cocostudio::timeline::EventFrame::getEvent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_EventFrame_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:init");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::EventFrame::*)()>(&cocostudio::timeline::EventFrame::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_EventFrame_setEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:setEvent");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::EventFrame::*)(std::string_view)>(&cocostudio::timeline::EventFrame::setEvent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_EventFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.EventFrame", "ccs.EventFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::EventFrame*(*)()>(&cocostudio::timeline::EventFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsEventFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::EventFrame, "EventFrame", "ccs.EventFrame",
		cocostudio::timeline::EventFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getEvent", lua_cocostudio_timeline_EventFrame_getEvent);
	LUA_METHOD("init", lua_cocostudio_timeline_EventFrame_init);
	LUA_METHOD("setEvent", lua_cocostudio_timeline_EventFrame_setEvent);
	LUA_METHOD("create", lua_cocostudio_timeline_EventFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ZOrderFrame_getZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:getZOrder");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ZOrderFrame::*)()const>(&cocostudio::timeline::ZOrderFrame::getZOrder));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ZOrderFrame_setZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:setZOrder");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ZOrderFrame::*)(int)>(&cocostudio::timeline::ZOrderFrame::setZOrder));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ZOrderFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ZOrderFrame", "ccs.ZOrderFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ZOrderFrame*(*)()>(&cocostudio::timeline::ZOrderFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsZOrderFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ZOrderFrame, "ZOrderFrame", "ccs.ZOrderFrame",
		cocostudio::timeline::ZOrderFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getZOrder", lua_cocostudio_timeline_ZOrderFrame_getZOrder);
	LUA_METHOD("setZOrder", lua_cocostudio_timeline_ZOrderFrame_setZOrder);
	LUA_METHOD("create", lua_cocostudio_timeline_ZOrderFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_BlendFuncFrame_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BlendFuncFrame", "ccs.BlendFuncFrame:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::BlendFunc(cocostudio::timeline::BlendFuncFrame::*)()const>(&cocostudio::timeline::BlendFuncFrame::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BlendFuncFrame_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BlendFuncFrame", "ccs.BlendFuncFrame:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BlendFuncFrame::*)(cocos2d::BlendFunc)>(&cocostudio::timeline::BlendFuncFrame::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_BlendFuncFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.BlendFuncFrame", "ccs.BlendFuncFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::BlendFuncFrame*(*)()>(&cocostudio::timeline::BlendFuncFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsBlendFuncFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::BlendFuncFrame, "BlendFuncFrame", "ccs.BlendFuncFrame",
		cocostudio::timeline::BlendFuncFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocostudio_timeline_BlendFuncFrame_getBlendFunc);
	LUA_METHOD("setBlendFunc", lua_cocostudio_timeline_BlendFuncFrame_setBlendFunc);
	LUA_METHOD("create", lua_cocostudio_timeline_BlendFuncFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_PlayableFrame_getPlayableAct(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:getPlayableAct");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocostudio::timeline::PlayableFrame::*)()const>(&cocostudio::timeline::PlayableFrame::getPlayableAct));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_PlayableFrame_setPlayableAct(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:setPlayableAct");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::PlayableFrame::*)(std::string)>(&cocostudio::timeline::PlayableFrame::setPlayableAct));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_PlayableFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.PlayableFrame", "ccs.PlayableFrame:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::PlayableFrame*(*)()>(&cocostudio::timeline::PlayableFrame::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsPlayableFrame(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::PlayableFrame, "PlayableFrame", "ccs.PlayableFrame",
		cocostudio::timeline::PlayableFrame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getPlayableAct", lua_cocostudio_timeline_PlayableFrame_getPlayableAct);
	LUA_METHOD("setPlayableAct", lua_cocostudio_timeline_PlayableFrame_setPlayableAct);
	LUA_METHOD("create", lua_cocostudio_timeline_PlayableFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_Timeline_addFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:addFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*)>(&cocostudio::timeline::Timeline::addFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Timeline*(cocostudio::timeline::Timeline::*)()>(&cocostudio::timeline::Timeline::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getActionTimeline");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getActionTimeline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getFrames");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocostudio::timeline::Frame *>&(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_getNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:getNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::timeline::Timeline::*)()const>(&cocostudio::timeline::Timeline::getNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_Timeline_gotoFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:gotoFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::gotoFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_insertFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:insertFrame");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*, int)>(&cocostudio::timeline::Timeline::insertFrame)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_Timeline_removeFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:removeFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::Frame*)>(&cocostudio::timeline::Timeline::removeFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setActionTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::Timeline::setActionTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_setNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:setNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(cocos2d::Node*)>(&cocostudio::timeline::Timeline::setNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_stepToFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.Timeline", "ccs.Timeline:stepToFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::Timeline::*)(int)>(&cocostudio::timeline::Timeline::stepToFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_Timeline_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.Timeline", "ccs.Timeline:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::Timeline*(*)()>(&cocostudio::timeline::Timeline::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsTimeline(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::Timeline, "Timeline", "ccs.Timeline",
		cocostudio::timeline::Timeline, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addFrame", lua_cocostudio_timeline_Timeline_addFrame);
	LUA_METHOD("clone", lua_cocostudio_timeline_Timeline_clone);
	LUA_METHOD("getActionTag", lua_cocostudio_timeline_Timeline_getActionTag);
	LUA_METHOD("getActionTimeline", lua_cocostudio_timeline_Timeline_getActionTimeline);
	LUA_METHOD("getFrames", lua_cocostudio_timeline_Timeline_getFrames);
	LUA_METHOD("getNode", lua_cocostudio_timeline_Timeline_getNode);
	LUA_METHOD("gotoFrame", lua_cocostudio_timeline_Timeline_gotoFrame);
	LUA_METHOD("insertFrame", lua_cocostudio_timeline_Timeline_insertFrame);
	LUA_METHOD("removeFrame", lua_cocostudio_timeline_Timeline_removeFrame);
	LUA_METHOD("setActionTag", lua_cocostudio_timeline_Timeline_setActionTag);
	LUA_METHOD("setActionTimeline", lua_cocostudio_timeline_Timeline_setActionTimeline);
	LUA_METHOD("setNode", lua_cocostudio_timeline_Timeline_setNode);
	LUA_METHOD("stepToFrame", lua_cocostudio_timeline_Timeline_stepToFrame);
	LUA_METHOD("create", lua_cocostudio_timeline_Timeline_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineData_getActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:getActionTag");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimelineData::*)()const>(&cocostudio::timeline::ActionTimelineData::getActionTag));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineData_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::timeline::ActionTimelineData::*)(int)>(&cocostudio::timeline::ActionTimelineData::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineData_setActionTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:setActionTag");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineData::*)(int)>(&cocostudio::timeline::ActionTimelineData::setActionTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineData_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineData", "ccs.ActionTimelineData:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::ActionTimelineData*(*)(int)>(&cocostudio::timeline::ActionTimelineData::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Studio_ccsActionTimelineData(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimelineData, "ActionTimelineData", "ccs.ActionTimelineData",
		cocostudio::timeline::ActionTimelineData, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getActionTag", lua_cocostudio_timeline_ActionTimelineData_getActionTag);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimelineData_init);
	LUA_METHOD("setActionTag", lua_cocostudio_timeline_ActionTimelineData_setActionTag);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimelineData_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimeline_IsAnimationInfoExists(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:IsAnimationInfoExists");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocostudio::timeline::ActionTimeline::*)(std::string_view)>(&cocostudio::timeline::ActionTimeline::IsAnimationInfoExists));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_addFrameEndCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:addFrameEndCallFunc");
	if (argc == 3 && !ok && lua_isnil(lua_S, 4)) { arg_cur = 3; } else {
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, std::string_view, std::function<void()>)>(&cocostudio::timeline::ActionTimeline::addFrameEndCallFunc)));
	}
	LUA_INVOKE_FOOTER("3");
}
int lua_cocostudio_timeline_ActionTimeline_addTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:addTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(cocostudio::timeline::Timeline*)>(&cocostudio::timeline::ActionTimeline::addTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_clearFrameEndCallFuncs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearFrameEndCallFuncs");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearFrameEndCallFuncs));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_clearFrameEventCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearFrameEventCallFunc");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearFrameEventCallFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_clearLastFrameCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:clearLastFrameCallFunc");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::clearLastFrameCallFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getCurrentFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getCurrentFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getCurrentFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getEndFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getEndFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getEndFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getStartFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getStartFrame");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getStartFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getTimeSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getTimeSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getTimeSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_getTimelines(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:getTimelines");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocostudio::timeline::Timeline *>&(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::getTimelines));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:gotoFrameAndPause");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPause));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPlay(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:gotoFrameAndPlay");
	LUA_TRY_INVOKE(4, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, int, int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay)));
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay)));
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, bool)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay)));
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::gotoFrameAndPlay));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cocostudio_timeline_ActionTimeline_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_isPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:isPlaying");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::ActionTimeline::*)()const>(&cocostudio::timeline::ActionTimeline::isPlaying));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:pause");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::pause));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:play");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::string, bool)>(&cocostudio::timeline::ActionTimeline::play)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimeline_removeAnimationInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeAnimationInfo");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::string)>(&cocostudio::timeline::ActionTimeline::removeAnimationInfo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeFrameEndCallFunc");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(int, std::string_view)>(&cocostudio::timeline::ActionTimeline::removeFrameEndCallFunc)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFuncs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeFrameEndCallFuncs");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::removeFrameEndCallFuncs));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_removeTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:removeTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(cocostudio::timeline::Timeline*)>(&cocostudio::timeline::ActionTimeline::removeTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:resume");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::resume));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_setAnimationEndCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setAnimationEndCallFunc");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::ActionTimeline::*)(const std::string, std::function<void()>)>(&cocostudio::timeline::ActionTimeline::setAnimationEndCallFunc)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimeline_setCurrentFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setCurrentFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::setCurrentFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setDuration");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(int)>(&cocostudio::timeline::ActionTimeline::setDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setFrameEventCallFunc_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setFrameEventCallFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::function<void(cocostudio::timeline::Frame*)>)>(&cocostudio::timeline::ActionTimeline::setFrameEventCallFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setLastFrameCallFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setLastFrameCallFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(std::function<void()>)>(&cocostudio::timeline::ActionTimeline::setLastFrameCallFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_setTimeSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:setTimeSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimeline::*)(float)>(&cocostudio::timeline::ActionTimeline::setTimeSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimeline_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:start");
	LUA_TRY_INVOKE(0, static_cast<void(cocostudio::timeline::ActionTimeline::*)()>(&cocostudio::timeline::ActionTimeline::start));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimeline_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimeline", "ccs.ActionTimeline:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(*)()>(&cocostudio::timeline::ActionTimeline::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Studio_ccsActionTimeline(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimeline, "ActionTimeline", "ccs.ActionTimeline",
		cocostudio::timeline::ActionTimeline, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("IsAnimationInfoExists", lua_cocostudio_timeline_ActionTimeline_IsAnimationInfoExists);
	LUA_METHOD("addFrameEndCallFunc", lua_cocostudio_timeline_ActionTimeline_addFrameEndCallFunc);
	LUA_METHOD("addTimeline", lua_cocostudio_timeline_ActionTimeline_addTimeline);
	LUA_METHOD("clearFrameEndCallFuncs", lua_cocostudio_timeline_ActionTimeline_clearFrameEndCallFuncs);
	LUA_METHOD("clearFrameEventCallFunc", lua_cocostudio_timeline_ActionTimeline_clearFrameEventCallFunc);
	LUA_METHOD("clearLastFrameCallFunc", lua_cocostudio_timeline_ActionTimeline_clearLastFrameCallFunc);
	LUA_METHOD("getCurrentFrame", lua_cocostudio_timeline_ActionTimeline_getCurrentFrame);
	LUA_METHOD("getDuration", lua_cocostudio_timeline_ActionTimeline_getDuration);
	LUA_METHOD("getEndFrame", lua_cocostudio_timeline_ActionTimeline_getEndFrame);
	LUA_METHOD("getStartFrame", lua_cocostudio_timeline_ActionTimeline_getStartFrame);
	LUA_METHOD("getTimeSpeed", lua_cocostudio_timeline_ActionTimeline_getTimeSpeed);
	LUA_METHOD("getTimelines", lua_cocostudio_timeline_ActionTimeline_getTimelines);
	LUA_METHOD("gotoFrameAndPause", lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPause);
	LUA_METHOD("gotoFrameAndPlay", lua_cocostudio_timeline_ActionTimeline_gotoFrameAndPlay);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimeline_init);
	LUA_METHOD("isPlaying", lua_cocostudio_timeline_ActionTimeline_isPlaying);
	LUA_METHOD("pause", lua_cocostudio_timeline_ActionTimeline_pause);
	LUA_METHOD("play", lua_cocostudio_timeline_ActionTimeline_play);
	LUA_METHOD("removeAnimationInfo", lua_cocostudio_timeline_ActionTimeline_removeAnimationInfo);
	LUA_METHOD("removeFrameEndCallFunc", lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFunc);
	LUA_METHOD("removeFrameEndCallFuncs", lua_cocostudio_timeline_ActionTimeline_removeFrameEndCallFuncs);
	LUA_METHOD("removeTimeline", lua_cocostudio_timeline_ActionTimeline_removeTimeline);
	LUA_METHOD("resume", lua_cocostudio_timeline_ActionTimeline_resume);
	LUA_METHOD("setAnimationEndCallFunc", lua_cocostudio_timeline_ActionTimeline_setAnimationEndCallFunc);
	LUA_METHOD("setCurrentFrame", lua_cocostudio_timeline_ActionTimeline_setCurrentFrame);
	LUA_METHOD("setDuration", lua_cocostudio_timeline_ActionTimeline_setDuration);
	LUA_METHOD("setFrameEventCallFunc", lua_cocostudio_timeline_ActionTimeline_setFrameEventCallFunc_1);
	LUA_METHOD("setLastFrameCallFunc", lua_cocostudio_timeline_ActionTimeline_setLastFrameCallFunc);
	LUA_METHOD("setTimeSpeed", lua_cocostudio_timeline_ActionTimeline_setTimeSpeed);
	LUA_METHOD("start", lua_cocostudio_timeline_ActionTimeline_start);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimeline_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_ActionTimelineNode_getActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:getActionTimeline");
	LUA_TRY_INVOKE_R(0, static_cast<cocostudio::timeline::ActionTimeline*(cocostudio::timeline::ActionTimelineNode::*)()>(&cocostudio::timeline::ActionTimelineNode::getActionTimeline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineNode_getRoot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:getRoot");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocostudio::timeline::ActionTimelineNode::*)()>(&cocostudio::timeline::ActionTimelineNode::getRoot));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_ActionTimelineNode_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:init");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocostudio::timeline::ActionTimelineNode::*)(cocos2d::Node*, cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::ActionTimelineNode::init)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_ActionTimelineNode_setActionTimeline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:setActionTimeline");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineNode::*)(cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::ActionTimelineNode::setActionTimeline));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineNode_setRoot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:setRoot");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::ActionTimelineNode::*)(cocos2d::Node*)>(&cocostudio::timeline::ActionTimelineNode::setRoot));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_ActionTimelineNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccs.ActionTimelineNode", "ccs.ActionTimelineNode:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocostudio::timeline::ActionTimelineNode*(*)(cocos2d::Node*, cocostudio::timeline::ActionTimeline*)>(&cocostudio::timeline::ActionTimelineNode::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Studio_ccsActionTimelineNode(lua_State* lua_S)
{
	LUA_ENTRY("ccs");
	LUA_CLS_DEF_BASE(cocostudio::timeline::ActionTimelineNode, "ActionTimelineNode", "ccs.ActionTimelineNode",
		cocostudio::timeline::ActionTimelineNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getActionTimeline", lua_cocostudio_timeline_ActionTimelineNode_getActionTimeline);
	LUA_METHOD("getRoot", lua_cocostudio_timeline_ActionTimelineNode_getRoot);
	LUA_METHOD("init", lua_cocostudio_timeline_ActionTimelineNode_init_1);
	LUA_METHOD("setActionTimeline", lua_cocostudio_timeline_ActionTimelineNode_setActionTimeline);
	LUA_METHOD("setRoot", lua_cocostudio_timeline_ActionTimelineNode_setRoot);
	LUA_METHOD("create", lua_cocostudio_timeline_ActionTimelineNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_BoneNode_addSkin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:addSkin");
	LUA_TRY_INVOKE(3, (static_cast<void(cocostudio::timeline::BoneNode::*)(cocostudio::timeline::SkinNode*, bool, bool)>(&cocostudio::timeline::BoneNode::addSkin)));
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::BoneNode::*)(cocostudio::timeline::SkinNode*, bool)>(&cocostudio::timeline::BoneNode::addSkin)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocostudio_timeline_BoneNode_displaySkin(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:displaySkin");
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::timeline::BoneNode::*)(std::string_view, bool)>(&cocostudio::timeline::BoneNode::displaySkin)));
	LUA_TRY_INVOKE_OVERLOAD(2, (static_cast<void(cocostudio::timeline::BoneNode::*)(cocostudio::timeline::SkinNode*, bool)>(&cocostudio::timeline::BoneNode::displaySkin)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_BoneNode_getAllSubBones(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getAllSubBones");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocostudio::timeline::BoneNode *>(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getAllSubBones));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getAllSubSkins(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getAllSubSkins");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocos2d::Node *>(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getAllSubSkins));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getChildBones(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getChildBones");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocostudio::timeline::BoneNode *>&(cocostudio::timeline::BoneNode::*)()>(&cocostudio::timeline::BoneNode::getChildBones));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocostudio::timeline::BoneNode *>&(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getChildBones));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocostudio_timeline_BoneNode_getSkins(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getSkins");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::Node *>&(cocostudio::timeline::BoneNode::*)()>(&cocostudio::timeline::BoneNode::getSkins));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::Node *>&(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getSkins));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getVisibleSkins(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getVisibleSkins");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vector<cocos2d::Node *>(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getVisibleSkins));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_getVisibleSkinsRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:getVisibleSkinsRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::getVisibleSkinsRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_isDebugDrawEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:isDebugDrawEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocostudio::timeline::BoneNode::*)()const>(&cocostudio::timeline::BoneNode::isDebugDrawEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_BoneNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BoneNode::*)(const cocos2d::BlendFunc&)>(&cocostudio::timeline::BoneNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_BoneNode_setDebugDrawColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.BoneNode", "ccs.BoneNode:setDebugDrawColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::timeline::BoneNode::*)(const cocos2d::Color4F&)>(&cocostudio::timeline::BoneNode::setDebugDrawColor));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::timeline::BoneNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addSkin", lua_cocostudio_timeline_BoneNode_addSkin);
	LUA_METHOD("displaySkin", lua_cocostudio_timeline_BoneNode_displaySkin);
	LUA_METHOD("getAllSubBones", lua_cocostudio_timeline_BoneNode_getAllSubBones);
	LUA_METHOD("getAllSubSkins", lua_cocostudio_timeline_BoneNode_getAllSubSkins);
	LUA_METHOD("getBlendFunc", lua_cocostudio_timeline_BoneNode_getBlendFunc);
	LUA_METHOD("getChildBones", lua_cocostudio_timeline_BoneNode_getChildBones);
	LUA_METHOD("getDebugDrawColor", lua_cocostudio_timeline_BoneNode_getDebugDrawColor);
	LUA_METHOD("getDebugDrawLength", lua_cocostudio_timeline_BoneNode_getDebugDrawLength);
	LUA_METHOD("getDebugDrawWidth", lua_cocostudio_timeline_BoneNode_getDebugDrawWidth);
	LUA_METHOD("getRootSkeletonNode", lua_cocostudio_timeline_BoneNode_getRootSkeletonNode);
	LUA_METHOD("getSkins", lua_cocostudio_timeline_BoneNode_getSkins);
	LUA_METHOD("getVisibleSkins", lua_cocostudio_timeline_BoneNode_getVisibleSkins);
	LUA_METHOD("getVisibleSkinsRect", lua_cocostudio_timeline_BoneNode_getVisibleSkinsRect);
	LUA_METHOD("isDebugDrawEnabled", lua_cocostudio_timeline_BoneNode_isDebugDrawEnabled);
	LUA_METHOD("setBlendFunc", lua_cocostudio_timeline_BoneNode_setBlendFunc);
	LUA_METHOD("setDebugDrawColor", lua_cocostudio_timeline_BoneNode_setDebugDrawColor);
	LUA_METHOD("setDebugDrawEnabled", lua_cocostudio_timeline_BoneNode_setDebugDrawEnabled);
	LUA_METHOD("setDebugDrawLength", lua_cocostudio_timeline_BoneNode_setDebugDrawLength);
	LUA_METHOD("setDebugDrawWidth", lua_cocostudio_timeline_BoneNode_setDebugDrawWidth);
	LUA_METHOD("create", lua_cocostudio_timeline_BoneNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocostudio_timeline_SkeletonNode_addSkinGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkeletonNode", "ccs.SkeletonNode:addSkinGroup");
	LUA_TRY_INVOKE(2, (static_cast<void(cocostudio::timeline::SkeletonNode::*)(std::string, tsl::robin_map<std::string, std::string, hlookup::string_hash, hlookup::equal_to>)>(&cocostudio::timeline::SkeletonNode::addSkinGroup)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocostudio_timeline_SkeletonNode_changeSkins(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkeletonNode", "ccs.SkeletonNode:changeSkins");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cocostudio::timeline::SkeletonNode::*)(std::string_view)>(&cocostudio::timeline::SkeletonNode::changeSkins));
	LUA_TRY_INVOKE_OVERLOAD(1, (static_cast<void(cocostudio::timeline::SkeletonNode::*)(const tsl::robin_map<std::string, std::string, hlookup::string_hash, hlookup::equal_to>&)>(&cocostudio::timeline::SkeletonNode::changeSkins)));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocostudio_timeline_SkeletonNode_getAllSubBonesMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkeletonNode", "ccs.SkeletonNode:getAllSubBonesMap");
	LUA_TRY_INVOKE_R(0, (static_cast<const cocos2d::Map<std::string, cocostudio::timeline::BoneNode *, hlookup::string_hash, hlookup::equal_to>&(cocostudio::timeline::SkeletonNode::*)()const>(&cocostudio::timeline::SkeletonNode::getAllSubBonesMap)));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocostudio_timeline_SkeletonNode_getBoneNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.SkeletonNode", "ccs.SkeletonNode:getBoneNode");
	LUA_TRY_INVOKE_R(1, static_cast<cocostudio::timeline::BoneNode*(cocostudio::timeline::SkeletonNode::*)(std::string_view)>(&cocostudio::timeline::SkeletonNode::getBoneNode));
	LUA_INVOKE_FOOTER("1");
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
		cocostudio::timeline::SkeletonNode, "ccs.BoneNode",
		nullptr, nullptr);
	LUA_METHOD("addSkinGroup", lua_cocostudio_timeline_SkeletonNode_addSkinGroup);
	LUA_METHOD("changeSkins", lua_cocostudio_timeline_SkeletonNode_changeSkins);
	LUA_METHOD("getAllSubBonesMap", lua_cocostudio_timeline_SkeletonNode_getAllSubBonesMap);
	LUA_METHOD("getBoneNode", lua_cocostudio_timeline_SkeletonNode_getBoneNode);
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
int lua_cocostudio_ComExtensionData_setCustomProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccs.ComExtensionData", "ccs.ComExtensionData:setCustomProperty");
	LUA_TRY_INVOKE(1, static_cast<void(cocostudio::ComExtensionData::*)(std::string_view)>(&cocostudio::ComExtensionData::setCustomProperty));
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
		cocostudio::ComExtensionData, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("getActionTag", lua_cocostudio_ComExtensionData_getActionTag);
	LUA_METHOD("getCustomProperty", lua_cocostudio_ComExtensionData_getCustomProperty);
	LUA_METHOD("setActionTag", lua_cocostudio_ComExtensionData_setActionTag);
	LUA_METHOD("setCustomProperty", lua_cocostudio_ComExtensionData_setCustomProperty);
	LUA_METHOD("create", lua_cocostudio_ComExtensionData_create);
	LUA_METHOD("createInstance", lua_cocostudio_ComExtensionData_createInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
