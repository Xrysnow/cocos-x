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

int lua_cocos2d_CallFunc_execute(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.CallFunc", "cc.CallFunc:execute");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::CallFunc::*)()>(&cocos2d::CallFunc::execute));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccCallFunc(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::CallFunc, "CallFunc", "cc.CallFunc",
		cocos2d::CallFunc, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("execute", lua_cocos2d_CallFunc_execute);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_GridAction_getGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:getGrid");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::GridBase*(cocos2d::GridAction::*)()>(&cocos2d::GridAction::getGrid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_GridAction_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.GridAction", "cc.GridAction:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::GridAction::*)(float, const cocos2d::Vec2&)>(&cocos2d::GridAction::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccGridAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::GridAction, "GridAction", "cc.GridAction",
		cocos2d::GridAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getGrid", lua_cocos2d_GridAction_getGrid);
	LUA_METHOD("initWithDuration", lua_cocos2d_GridAction_initWithDuration);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Grid3DAction_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Grid3DAction", "cc.Grid3DAction:getGridRect");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Rect(cocos2d::Grid3DAction::*)()const>(&cocos2d::Grid3DAction::getGridRect));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Grid3DAction, "Grid3DAction", "cc.Grid3DAction",
		cocos2d::Grid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_METHOD("getGridRect", lua_cocos2d_Grid3DAction_getGridRect);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTiledGrid3DAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TiledGrid3DAction, "TiledGrid3DAction", "cc.TiledGrid3DAction",
		cocos2d::TiledGrid3DAction, "cc.GridAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_StopGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.StopGrid", "cc.StopGrid:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::StopGrid*(*)()>(&cocos2d::StopGrid::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccStopGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::StopGrid, "StopGrid", "cc.StopGrid",
		cocos2d::StopGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_StopGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ReuseGrid_initWithTimes(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:initWithTimes");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ReuseGrid::*)(int)>(&cocos2d::ReuseGrid::initWithTimes));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ReuseGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ReuseGrid", "cc.ReuseGrid:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ReuseGrid*(*)(int)>(&cocos2d::ReuseGrid::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccReuseGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ReuseGrid, "ReuseGrid", "cc.ReuseGrid",
		cocos2d::ReuseGrid, "cc.ActionInstant",
		nullptr, nullptr);
	LUA_METHOD("initWithTimes", lua_cocos2d_ReuseGrid_initWithTimes);
	LUA_METHOD("create", lua_cocos2d_ReuseGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Waves3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Waves3D::*)()const>(&cocos2d::Waves3D::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Waves3D::*)()const>(&cocos2d::Waves3D::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Waves3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Waves3D::*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Waves3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Waves3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Waves3D::*)(float)>(&cocos2d::Waves3D::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Waves3D", "cc.Waves3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Waves3D::*)(float)>(&cocos2d::Waves3D::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Waves3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Waves3D", "cc.Waves3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Waves3D*(*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::Waves3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccWaves3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Waves3D, "Waves3D", "cc.Waves3D",
		cocos2d::Waves3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Waves3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Waves3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_Waves3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Waves3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Waves3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_Waves3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipX3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithDuration");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FlipX3D::*)(float)>(&cocos2d::FlipX3D::initWithDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FlipX3D_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:initWithSize");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FlipX3D::*)(const cocos2d::Vec2&, float)>(&cocos2d::FlipX3D::initWithSize)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FlipX3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipX3D", "cc.FlipX3D:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FlipX3D*(*)(float)>(&cocos2d::FlipX3D::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipX3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipX3D, "FlipX3D", "cc.FlipX3D",
		cocos2d::FlipX3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_FlipX3D_initWithDuration);
	LUA_METHOD("initWithSize", lua_cocos2d_FlipX3D_initWithSize);
	LUA_METHOD("create", lua_cocos2d_FlipX3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FlipY3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FlipY3D", "cc.FlipY3D:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FlipY3D*(*)(float)>(&cocos2d::FlipY3D::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFlipY3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FlipY3D, "FlipY3D", "cc.FlipY3D",
		cocos2d::FlipY3D, "cc.FlipX3D",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_FlipY3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Lens3D_getLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getLensEffect");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Lens3D::*)()const>(&cocos2d::Lens3D::getLensEffect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Lens3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Lens3D::*)()const>(&cocos2d::Lens3D::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Lens3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Lens3D::*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, float)>(&cocos2d::Lens3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Lens3D_setConcave(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setConcave");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Lens3D::*)(bool)>(&cocos2d::Lens3D::setConcave));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_setLensEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setLensEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Lens3D::*)(float)>(&cocos2d::Lens3D::setLensEffect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Lens3D", "cc.Lens3D:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Lens3D::*)(const cocos2d::Vec2&)>(&cocos2d::Lens3D::setPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Lens3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Lens3D", "cc.Lens3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Lens3D*(*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, float)>(&cocos2d::Lens3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccLens3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Lens3D, "Lens3D", "cc.Lens3D",
		cocos2d::Lens3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getLensEffect", lua_cocos2d_Lens3D_getLensEffect);
	LUA_METHOD("getPosition", lua_cocos2d_Lens3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Lens3D_initWithDuration);
	LUA_METHOD("setConcave", lua_cocos2d_Lens3D_setConcave);
	LUA_METHOD("setLensEffect", lua_cocos2d_Lens3D_setLensEffect);
	LUA_METHOD("setPosition", lua_cocos2d_Lens3D_setPosition);
	LUA_METHOD("create", lua_cocos2d_Lens3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Ripple3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Ripple3D::*)()const>(&cocos2d::Ripple3D::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Ripple3D::*)()const>(&cocos2d::Ripple3D::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_getPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Ripple3D::*)()const>(&cocos2d::Ripple3D::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ripple3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:initWithDuration");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cocos2d::Ripple3D::*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, float, unsigned int, float)>(&cocos2d::Ripple3D::initWithDuration)));
	LUA_INVOKE_FOOTER("6");
}
int lua_cocos2d_Ripple3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Ripple3D::*)(float)>(&cocos2d::Ripple3D::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Ripple3D::*)(float)>(&cocos2d::Ripple3D::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:setPosition");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Ripple3D::*)(const cocos2d::Vec2&)>(&cocos2d::Ripple3D::setPosition));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Ripple3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Ripple3D", "cc.Ripple3D:create");
	LUA_TRY_INVOKE_R(6, (static_cast<cocos2d::Ripple3D*(*)(float, const cocos2d::Vec2&, const cocos2d::Vec2&, float, unsigned int, float)>(&cocos2d::Ripple3D::create)));
	LUA_SINVOKE_FOOTER("6");
}
int luaReg_Core_ccRipple3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Ripple3D, "Ripple3D", "cc.Ripple3D",
		cocos2d::Ripple3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_Ripple3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_Ripple3D_getAmplitudeRate);
	LUA_METHOD("getPosition", lua_cocos2d_Ripple3D_getPosition);
	LUA_METHOD("initWithDuration", lua_cocos2d_Ripple3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_Ripple3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_Ripple3D_setAmplitudeRate);
	LUA_METHOD("setPosition", lua_cocos2d_Ripple3D_setPosition);
	LUA_METHOD("create", lua_cocos2d_Ripple3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Shaky3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Shaky3D::*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::Shaky3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_Shaky3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Shaky3D", "cc.Shaky3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Shaky3D*(*)(float, const cocos2d::Vec2&, int, bool)>(&cocos2d::Shaky3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccShaky3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Shaky3D, "Shaky3D", "cc.Shaky3D",
		cocos2d::Shaky3D, "cc.Grid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_Shaky3D_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_Shaky3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
