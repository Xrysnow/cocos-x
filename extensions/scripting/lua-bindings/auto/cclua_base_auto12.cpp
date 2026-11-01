#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"


int luaReg_Core_ccFadeOutUpTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutUpTiles, "FadeOutUpTiles", "cc.FadeOutUpTiles",
		cocos2d::FadeOutTRTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccFadeOutDownTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutDownTiles, "FadeOutDownTiles", "cc.FadeOutDownTiles",
		cocos2d::FadeOutUpTiles, "cc.FadeOutUpTiles",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TurnOffTiles, "TurnOffTiles", "cc.TurnOffTiles",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_WavesTiles3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::WavesTiles3D::*)()const>(&cocos2d::WavesTiles3D::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_WavesTiles3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::WavesTiles3D::*)()const>(&cocos2d::WavesTiles3D::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_WavesTiles3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::WavesTiles3D::*)(float)>(&cocos2d::WavesTiles3D::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_WavesTiles3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::WavesTiles3D::*)(float)>(&cocos2d::WavesTiles3D::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccWavesTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::WavesTiles3D, "WavesTiles3D", "cc.WavesTiles3D",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_WavesTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_WavesTiles3D_getAmplitudeRate);
	LUA_METHOD("setAmplitude", lua_cocos2d_WavesTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_WavesTiles3D_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpTiles3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::JumpTiles3D::*)()const>(&cocos2d::JumpTiles3D::getAmplitude));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_JumpTiles3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::JumpTiles3D::*)()const>(&cocos2d::JumpTiles3D::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_JumpTiles3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:setAmplitude");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::JumpTiles3D::*)(float)>(&cocos2d::JumpTiles3D::setAmplitude));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_JumpTiles3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::JumpTiles3D::*)(float)>(&cocos2d::JumpTiles3D::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccJumpTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpTiles3D, "JumpTiles3D", "cc.JumpTiles3D",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_JumpTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_JumpTiles3D_getAmplitudeRate);
	LUA_METHOD("setAmplitude", lua_cocos2d_JumpTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_JumpTiles3D_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SplitRows_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SplitRows", "cc.SplitRows:initWithDuration");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::SplitRows::*)(float, unsigned int)>(&cocos2d::SplitRows::initWithDuration));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitRows", "cc.SplitRows:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::SplitRows*(*)(float, unsigned int)>(&cocos2d::SplitRows::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SplitRows, "SplitRows", "cc.SplitRows",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SplitRows_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SplitCols_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SplitCols", "cc.SplitCols:initWithDuration");
	LUA_TRY_INVOKE_R(2, static_cast<bool(cocos2d::SplitCols::*)(float, unsigned int)>(&cocos2d::SplitCols::initWithDuration));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitCols", "cc.SplitCols:create");
	LUA_TRY_INVOKE_R(2, static_cast<cocos2d::SplitCols*(*)(float, unsigned int)>(&cocos2d::SplitCols::create));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SplitCols, "SplitCols", "cc.SplitCols",
		cocos2d::TiledGrid3DAction, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SplitCols_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionTween_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionTween", "cc.ActionTween:initWithDuration");
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::ActionTween::*)(float, std::string_view, float, float)>(&cocos2d::ActionTween::initWithDuration));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ActionTween_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionTween", "cc.ActionTween:create");
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::ActionTween*(*)(float, std::string_view, float, float)>(&cocos2d::ActionTween::create));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionTween(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionTween, "ActionTween", "cc.ActionTween",
		cocos2d::ActionInterval, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionTween_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ActionTween_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AtlasNode_getQuadsToDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getQuadsToDraw");
	LUA_TRY_INVOKE_R(0, static_cast<size_t(cocos2d::AtlasNode::*)()const>(&cocos2d::AtlasNode::getQuadsToDraw));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTexture");
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::AtlasNode::*)(cocos2d::Texture2D*, int, int, int)>(&cocos2d::AtlasNode::initWithTexture));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_AtlasNode_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTileFile");
	LUA_TRY_INVOKE_R(4, static_cast<bool(cocos2d::AtlasNode::*)(std::string_view, int, int, int)>(&cocos2d::AtlasNode::initWithTileFile));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_AtlasNode_updateAtlasValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:updateAtlasValues");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::AtlasNode::*)()>(&cocos2d::AtlasNode::updateAtlasValues));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:create");
	LUA_TRY_INVOKE_R(4, static_cast<cocos2d::AtlasNode*(*)(std::string_view, int, int, int)>(&cocos2d::AtlasNode::create));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccAtlasNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AtlasNode, "AtlasNode", "cc.AtlasNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getQuadsToDraw", lua_cocos2d_AtlasNode_getQuadsToDraw);
	LUA_METHOD("initWithTexture", lua_cocos2d_AtlasNode_initWithTexture);
	LUA_METHOD("initWithTileFile", lua_cocos2d_AtlasNode_initWithTileFile);
	LUA_METHOD("updateAtlasValues", lua_cocos2d_AtlasNode_updateAtlasValues);
	LUA_METHOD("create", lua_cocos2d_AtlasNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ClippingNode_getAlphaThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:getAlphaThreshold");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ClippingNode::*)()const>(&cocos2d::ClippingNode::getAlphaThreshold));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ClippingNode_getStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:getStencil");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::ClippingNode::*)()const>(&cocos2d::ClippingNode::getStencil));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ClippingNode_hasContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:hasContent");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ClippingNode::*)()const>(&cocos2d::ClippingNode::hasContent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ClippingNode_isInverted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:isInverted");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ClippingNode::*)()const>(&cocos2d::ClippingNode::isInverted));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ClippingNode_setAlphaThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setAlphaThreshold");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ClippingNode::*)(float)>(&cocos2d::ClippingNode::setAlphaThreshold));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ClippingNode_setInverted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setInverted");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ClippingNode::*)(bool)>(&cocos2d::ClippingNode::setInverted));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ClippingNode_setStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setStencil");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ClippingNode::*)(cocos2d::Node*)>(&cocos2d::ClippingNode::setStencil));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ClippingNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ClippingNode*(*)(cocos2d::Node*)>(&cocos2d::ClippingNode::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ClippingNode*(*)()>(&cocos2d::ClippingNode::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccClippingNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ClippingNode, "ClippingNode", "cc.ClippingNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAlphaThreshold", lua_cocos2d_ClippingNode_getAlphaThreshold);
	LUA_METHOD("getStencil", lua_cocos2d_ClippingNode_getStencil);
	LUA_METHOD("hasContent", lua_cocos2d_ClippingNode_hasContent);
	LUA_METHOD("isInverted", lua_cocos2d_ClippingNode_isInverted);
	LUA_METHOD("setAlphaThreshold", lua_cocos2d_ClippingNode_setAlphaThreshold);
	LUA_METHOD("setInverted", lua_cocos2d_ClippingNode_setInverted);
	LUA_METHOD("setStencil", lua_cocos2d_ClippingNode_setStencil);
	LUA_METHOD("create", lua_cocos2d_ClippingNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ClippingRectangleNode_isClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:isClippingEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ClippingRectangleNode::*)()const>(&cocos2d::ClippingRectangleNode::isClippingEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ClippingRectangleNode_setClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:setClippingEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ClippingRectangleNode::*)(bool)>(&cocos2d::ClippingRectangleNode::setClippingEnabled));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccClippingRectangleNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ClippingRectangleNode, "ClippingRectangleNode", "cc.ClippingRectangleNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("isClippingEnabled", lua_cocos2d_ClippingRectangleNode_isClippingEnabled);
	LUA_METHOD("setClippingEnabled", lua_cocos2d_ClippingRectangleNode_setClippingEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_DrawNode_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:clear");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::DrawNode::*)()>(&cocos2d::DrawNode::clear));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_DrawNode_getLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:getLineWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::DrawNode::*)()>(&cocos2d::DrawNode::getLineWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_DrawNode_isIsolated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:isIsolated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::DrawNode::*)()const>(&cocos2d::DrawNode::isIsolated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_DrawNode_setIsolated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setIsolated");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::DrawNode::*)(bool)>(&cocos2d::DrawNode::setIsolated));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_DrawNode_setLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setLineWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::DrawNode::*)(float)>(&cocos2d::DrawNode::setLineWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_DrawNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DrawNode", "cc.DrawNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::DrawNode*(*)(float)>(&cocos2d::DrawNode::create));
	LUA_TRY_INVOKE_R(0, [](){{return cocos2d::DrawNode::create();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccDrawNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DrawNode, "DrawNode", "cc.DrawNode",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("clear", lua_cocos2d_DrawNode_clear);
	LUA_METHOD("getLineWidth", lua_cocos2d_DrawNode_getLineWidth);
	LUA_METHOD("isIsolated", lua_cocos2d_DrawNode_isIsolated);
	LUA_METHOD("setIsolated", lua_cocos2d_DrawNode_setIsolated);
	LUA_METHOD("setLineWidth", lua_cocos2d_DrawNode_setLineWidth);
	LUA_METHOD("create", lua_cocos2d_DrawNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
