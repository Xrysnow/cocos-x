#include "cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_compat.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"

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
		cocostudio::timeline::Frame, "ccs.Frame",
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
		cocostudio::timeline::SkewFrame, "ccs.SkewFrame",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocostudio_timeline_RotationSkewFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
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
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getX", lua_cocostudio_timeline_PositionFrame_getX);
	LUA_METHOD("getY", lua_cocostudio_timeline_PositionFrame_getY);
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
		cocostudio::timeline::Frame, "ccs.Frame",
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
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
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
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getEndFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getEndFrameIndex);
	LUA_METHOD("getInnerActionType", lua_cocostudio_timeline_InnerActionFrame_getInnerActionType);
	LUA_METHOD("getSingleFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getSingleFrameIndex);
	LUA_METHOD("getStartFrameIndex", lua_cocostudio_timeline_InnerActionFrame_getStartFrameIndex);
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
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
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
		cocostudio::timeline::Frame, "ccs.Frame",
		nullptr, nullptr);
	LUA_METHOD("getAlpha", lua_cocostudio_timeline_AlphaFrame_getAlpha);
	LUA_METHOD("create", lua_cocostudio_timeline_AlphaFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
