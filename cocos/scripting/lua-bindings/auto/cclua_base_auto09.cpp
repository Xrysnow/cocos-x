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
int lua_cocos2d_FastTMXTiledMap_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getObjectGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroup");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::TMXObjectGroup*(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getObjectGroup));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::FastTMXTiledMap::*)()>(&cocos2d::FastTMXTiledMap::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getObjectGroups));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperties");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::ValueMap&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getPropertiesForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getPropertiesForGID");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(int)const>(&cocos2d::FastTMXTiledMap::getPropertiesForGID));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperty");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(std::string_view)const>(&cocos2d::FastTMXTiledMap::getProperty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getResourceFile");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getResourceFile));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FastTMXTiledMap_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getTileSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getTileSize));
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
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FastTMXTiledMap::*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::initWithXML)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FastTMXTiledMap_setMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapOrientation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(int)>(&cocos2d::FastTMXTiledMap::setMapOrientation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXTiledMap::setMapSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setObjectGroups");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)>(&cocos2d::FastTMXTiledMap::setObjectGroups));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setProperties");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::ValueMap&)>(&cocos2d::FastTMXTiledMap::setProperties));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileAnimEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(bool)>(&cocos2d::FastTMXTiledMap::setTileAnimEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FastTMXTiledMap_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vec2&)>(&cocos2d::FastTMXTiledMap::setTileSize));
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
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FastTMXTiledMap*(*)(std::string_view, std::string_view)>(&cocos2d::FastTMXTiledMap::createWithXML)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFastTMXTiledMap(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FastTMXTiledMap, "FastTMXTiledMap", "cc.FastTMXTiledMap",
		cocos2d::FastTMXTiledMap, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayer", lua_cocos2d_FastTMXTiledMap_getLayer);
	LUA_METHOD("getLayerCount", lua_cocos2d_FastTMXTiledMap_getLayerCount);
	LUA_METHOD("getMapOrientation", lua_cocos2d_FastTMXTiledMap_getMapOrientation);
	LUA_METHOD("getMapSize", lua_cocos2d_FastTMXTiledMap_getMapSize);
	LUA_METHOD("getObjectGroup", lua_cocos2d_FastTMXTiledMap_getObjectGroup);
	LUA_METHOD("getObjectGroups", lua_cocos2d_FastTMXTiledMap_getObjectGroups);
	LUA_METHOD("getProperties", lua_cocos2d_FastTMXTiledMap_getProperties);
	LUA_METHOD("getPropertiesForGID", lua_cocos2d_FastTMXTiledMap_getPropertiesForGID);
	LUA_METHOD("getProperty", lua_cocos2d_FastTMXTiledMap_getProperty);
	LUA_METHOD("getResourceFile", lua_cocos2d_FastTMXTiledMap_getResourceFile);
	LUA_METHOD("getTileSize", lua_cocos2d_FastTMXTiledMap_getTileSize);
	LUA_METHOD("initWithTMXFile", lua_cocos2d_FastTMXTiledMap_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cocos2d_FastTMXTiledMap_initWithXML);
	LUA_METHOD("setMapOrientation", lua_cocos2d_FastTMXTiledMap_setMapOrientation);
	LUA_METHOD("setMapSize", lua_cocos2d_FastTMXTiledMap_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cocos2d_FastTMXTiledMap_setObjectGroups);
	LUA_METHOD("setProperties", lua_cocos2d_FastTMXTiledMap_setProperties);
	LUA_METHOD("setTileAnimEnabled", lua_cocos2d_FastTMXTiledMap_setTileAnimEnabled);
	LUA_METHOD("setTileSize", lua_cocos2d_FastTMXTiledMap_setTileSize);
	LUA_METHOD("create", lua_cocos2d_FastTMXTiledMap_create);
	LUA_METHOD("createWithXML", lua_cocos2d_FastTMXTiledMap_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MotionStreak3D_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getStroke");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getStroke));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getSweepAxis");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec3&(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getSweepAxis));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::MotionStreak3D::*)()const>(&cocos2d::MotionStreak3D::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MotionStreak3D_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cocos2d::MotionStreak3D::*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::initWithFade)));
	LUA_INVOKE_FOOTER("5");
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
int lua_cocos2d_MotionStreak3D_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::BlendFunc&)>(&cocos2d::MotionStreak3D::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
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
int lua_cocos2d_MotionStreak3D_setSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setSweepAxis");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::Vec3&)>(&cocos2d::MotionStreak3D::setSweepAxis));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:tintWithColor");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MotionStreak3D::*)(const cocos2d::Color3B&)>(&cocos2d::MotionStreak3D::tintWithColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MotionStreak3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak3D*(*)(float, float, float, const cocos2d::Color3B&, cocos2d::Texture2D*)>(&cocos2d::MotionStreak3D::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cocos2d::MotionStreak3D*(*)(float, float, float, const cocos2d::Color3B&, std::string_view)>(&cocos2d::MotionStreak3D::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MotionStreak3D, "MotionStreak3D", "cc.MotionStreak3D",
		cocos2d::MotionStreak3D, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_MotionStreak3D_getBlendFunc);
	LUA_METHOD("getStroke", lua_cocos2d_MotionStreak3D_getStroke);
	LUA_METHOD("getSweepAxis", lua_cocos2d_MotionStreak3D_getSweepAxis);
	LUA_METHOD("getTexture", lua_cocos2d_MotionStreak3D_getTexture);
	LUA_METHOD("initWithFade", lua_cocos2d_MotionStreak3D_initWithFade);
	LUA_METHOD("isStartingPositionInitialized", lua_cocos2d_MotionStreak3D_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cocos2d_MotionStreak3D_reset);
	LUA_METHOD("setBlendFunc", lua_cocos2d_MotionStreak3D_setBlendFunc);
	LUA_METHOD("setStartingPositionInitialized", lua_cocos2d_MotionStreak3D_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cocos2d_MotionStreak3D_setStroke);
	LUA_METHOD("setSweepAxis", lua_cocos2d_MotionStreak3D_setSweepAxis);
	LUA_METHOD("setTexture", lua_cocos2d_MotionStreak3D_setTexture);
	LUA_METHOD("tintWithColor", lua_cocos2d_MotionStreak3D_tintWithColor);
	LUA_METHOD("create", lua_cocos2d_MotionStreak3D_create);
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
		cocos2d::ComponentLua, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ComponentLua_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
