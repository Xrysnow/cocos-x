#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_TMXTileAnimManager_startAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:startAll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimManager::*)()>(&cocos2d::TMXTileAnimManager::startAll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimManager_stopAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:stopAll");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::TMXTileAnimManager::*)()>(&cocos2d::TMXTileAnimManager::stopAll));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TMXTileAnimManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXTileAnimManager*(*)(cocos2d::FastTMXLayer*)>(&cocos2d::TMXTileAnimManager::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTileAnimManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TMXTileAnimManager, "TMXTileAnimManager", "cc.TMXTileAnimManager",
		cocos2d::Ref, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("startAll", lua_cocos2d_TMXTileAnimManager_startAll);
	LUA_METHOD("stopAll", lua_cocos2d_TMXTileAnimManager_stopAll);
	LUA_METHOD("create", lua_cocos2d_TMXTileAnimManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FastTMXTiledMap_getLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayer");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FastTMXLayer*(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getLayer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getLayerCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayerCount");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getLayerCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapOrientation");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapOrientation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getObjectGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroup");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXObjectGroup*(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getObjectGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getResourceFile");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getResourceFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FastTMXTiledMap::*)(std::string_view)>(&cocos2d::FastTMXTiledMap::initWithTMXFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithXML");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::FastTMXTiledMap::*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::initWithXML));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FastTMXTiledMap_setMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(int)>(&cocos2d::FastTMXTiledMap::setMapOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileAnimEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(bool)>(&cocos2d::FastTMXTiledMap::setTileAnimEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FastTMXTiledMap*(*)(std::string_view)>(&cocos2d::FastTMXTiledMap::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:createWithXML");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::FastTMXTiledMap*(*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::createWithXML));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFastTMXTiledMap(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FastTMXTiledMap, "FastTMXTiledMap", "cc.FastTMXTiledMap",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayer", lua_cocos2d_FastTMXTiledMap_getLayer);
	LUA_METHOD("getLayerCount", lua_cocos2d_FastTMXTiledMap_getLayerCount);
	LUA_METHOD("getMapOrientation", lua_cocos2d_FastTMXTiledMap_getMapOrientation);
	LUA_METHOD("getObjectGroup", lua_cocos2d_FastTMXTiledMap_getObjectGroup);
	LUA_METHOD("getResourceFile", lua_cocos2d_FastTMXTiledMap_getResourceFile);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_FastTMXTiledMap_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_FastTMXTiledMap_initWithXML);
	LUA_METHOD("setMapOrientation", lua_cocos2d_FastTMXTiledMap_setMapOrientation);
	LUA_METHOD("setTileAnimEnabled", lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled);
	LUA_METHOD("create", lua_cocos2d_FastTMXTiledMap_create);
	LUA_METHOD("createWithXML", lua_cocos2d_FastTMXTiledMap_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MotionStreak3D_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getStroke");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getStroke));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::isStartingPositionInitialized));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:reset");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MotionStreak3D::*)()>(&cocos2d::MotionStreak3D::reset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(bool)>(&cocos2d::MotionStreak3D::setStartingPositionInitialized));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStroke");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(float)>(&cocos2d::MotionStreak3D::setStroke));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMotionStreak3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak3D, "MotionStreak3D", "cc.MotionStreak3D",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak3D_getStroke);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak3D_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak3D_reset);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak3D_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak3D_setStroke);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ComponentLua_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ComponentLua", "cc.ComponentLua:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ComponentLua*(*)(std::string_view)>(&cocos2d::ComponentLua::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccComponentLua(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ComponentLua, "ComponentLua", "cc.ComponentLua",
		cocos2d::Component, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ComponentLua_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
