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

int lua_cocos2d_FadeOutUpTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutUpTiles", "cc.FadeOutUpTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeOutUpTiles*(*)(float, const cocos2d::Vec2&)>(&cocos2d::FadeOutUpTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutUpTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutUpTiles, "FadeOutUpTiles", "cc.FadeOutUpTiles",
		cocos2d::FadeOutUpTiles, "cc.FadeOutTRTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_FadeOutUpTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOutDownTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOutDownTiles", "cc.FadeOutDownTiles:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeOutDownTiles*(*)(float, const cocos2d::Vec2&)>(&cocos2d::FadeOutDownTiles::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeOutDownTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOutDownTiles, "FadeOutDownTiles", "cc.FadeOutDownTiles",
		cocos2d::FadeOutDownTiles, "cc.FadeOutUpTiles",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_FadeOutDownTiles_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TurnOffTiles_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::TurnOffTiles::*)(float, const cocos2d::Vec2&, unsigned int)>(&cocos2d::TurnOffTiles::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_TurnOffTiles_turnOffTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:turnOffTile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TurnOffTiles::*)(const cocos2d::Vec2&)>(&cocos2d::TurnOffTiles::turnOffTile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TurnOffTiles_turnOnTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:turnOnTile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TurnOffTiles::*)(const cocos2d::Vec2&)>(&cocos2d::TurnOffTiles::turnOnTile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TurnOffTiles_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TurnOffTiles", "cc.TurnOffTiles:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::TurnOffTiles*(*)(float, const cocos2d::Vec2&, unsigned int)>(&cocos2d::TurnOffTiles::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TurnOffTiles*(*)(float, const cocos2d::Vec2&)>(&cocos2d::TurnOffTiles::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccTurnOffTiles(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TurnOffTiles, "TurnOffTiles", "cc.TurnOffTiles",
		cocos2d::TurnOffTiles, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TurnOffTiles_initWithDuration);
	LUA_METHOD("turnOffTile", lua_cocos2d_TurnOffTiles_turnOffTile);
	LUA_METHOD("turnOnTile", lua_cocos2d_TurnOffTiles_turnOnTile);
	LUA_METHOD("create", lua_cocos2d_TurnOffTiles_create);
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
int lua_cocos2d_WavesTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::WavesTiles3D::*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::WavesTiles3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
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
int lua_cocos2d_WavesTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.WavesTiles3D", "cc.WavesTiles3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::WavesTiles3D*(*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::WavesTiles3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccWavesTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::WavesTiles3D, "WavesTiles3D", "cc.WavesTiles3D",
		cocos2d::WavesTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_WavesTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_WavesTiles3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_WavesTiles3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_WavesTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_WavesTiles3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_WavesTiles3D_create);
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
int lua_cocos2d_JumpTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::JumpTiles3D::*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::JumpTiles3D::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
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
int lua_cocos2d_JumpTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::JumpTiles3D*(*)(float, const cocos2d::Vec2&, unsigned int, float)>(&cocos2d::JumpTiles3D::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpTiles3D, "JumpTiles3D", "cc.JumpTiles3D",
		cocos2d::JumpTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cocos2d_JumpTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_JumpTiles3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpTiles3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cocos2d_JumpTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_JumpTiles3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cocos2d_JumpTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SplitRows_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SplitRows", "cc.SplitRows:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SplitRows::*)(float, unsigned int)>(&cocos2d::SplitRows::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitRows", "cc.SplitRows:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SplitRows*(*)(float, unsigned int)>(&cocos2d::SplitRows::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SplitRows, "SplitRows", "cc.SplitRows",
		cocos2d::SplitRows, "cc.TiledGrid3DAction",
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
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SplitCols::*)(float, unsigned int)>(&cocos2d::SplitCols::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_SplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitCols", "cc.SplitCols:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SplitCols*(*)(float, unsigned int)>(&cocos2d::SplitCols::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SplitCols, "SplitCols", "cc.SplitCols",
		cocos2d::SplitCols, "cc.TiledGrid3DAction",
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
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ActionTween::*)(float, std::string_view, float, float)>(&cocos2d::ActionTween::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ActionTween_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionTween", "cc.ActionTween:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ActionTween*(*)(float, std::string_view, float, float)>(&cocos2d::ActionTween::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionTween(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionTween, "ActionTween", "cc.ActionTween",
		cocos2d::ActionTween, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionTween_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ActionTween_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AtlasNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::AtlasNode::*)()const>(&cocos2d::AtlasNode::getBlendFunc));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_getQuadsToDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getQuadsToDraw");
	LUA_TRY_INVOKE_R(0, static_cast<size_t(cocos2d::AtlasNode::*)()const>(&cocos2d::AtlasNode::getQuadsToDraw));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::AtlasNode::*)()const>(&cocos2d::AtlasNode::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextureAtlas*(cocos2d::AtlasNode::*)()const>(&cocos2d::AtlasNode::getTextureAtlas));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AtlasNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTexture");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::AtlasNode::*)(cocos2d::Texture2D*, int, int, int)>(&cocos2d::AtlasNode::initWithTexture)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_AtlasNode_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTileFile");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::AtlasNode::*)(std::string_view, int, int, int)>(&cocos2d::AtlasNode::initWithTileFile)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_AtlasNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AtlasNode::*)(const cocos2d::BlendFunc&)>(&cocos2d::AtlasNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AtlasNode_setQuadsToDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setQuadsToDraw");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AtlasNode::*)(ssize_t)>(&cocos2d::AtlasNode::setQuadsToDraw));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AtlasNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AtlasNode::*)(cocos2d::Texture2D*)>(&cocos2d::AtlasNode::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AtlasNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AtlasNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::AtlasNode::setTextureAtlas));
	LUA_INVOKE_FOOTER("1");
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
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::AtlasNode*(*)(std::string_view, int, int, int)>(&cocos2d::AtlasNode::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccAtlasNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AtlasNode, "AtlasNode", "cc.AtlasNode",
		cocos2d::AtlasNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cocos2d_AtlasNode_getBlendFunc);
	LUA_METHOD("getQuadsToDraw", lua_cocos2d_AtlasNode_getQuadsToDraw);
	LUA_METHOD("getTexture", lua_cocos2d_AtlasNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cocos2d_AtlasNode_getTextureAtlas);
	LUA_METHOD("initWithTexture", lua_cocos2d_AtlasNode_initWithTexture);
	LUA_METHOD("initWithTileFile", lua_cocos2d_AtlasNode_initWithTileFile);
	LUA_METHOD("setBlendFunc", lua_cocos2d_AtlasNode_setBlendFunc);
	LUA_METHOD("setQuadsToDraw", lua_cocos2d_AtlasNode_setQuadsToDraw);
	LUA_METHOD("setTexture", lua_cocos2d_AtlasNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cocos2d_AtlasNode_setTextureAtlas);
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
int lua_cocos2d_ClippingNode_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ClippingNode::*)(cocos2d::Node*)>(&cocos2d::ClippingNode::init));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::ClippingNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAlphaThreshold", lua_cocos2d_ClippingNode_getAlphaThreshold);
	LUA_METHOD("getStencil", lua_cocos2d_ClippingNode_getStencil);
	LUA_METHOD("hasContent", lua_cocos2d_ClippingNode_hasContent);
	LUA_METHOD("init", lua_cocos2d_ClippingNode_init_1);
	LUA_METHOD("isInverted", lua_cocos2d_ClippingNode_isInverted);
	LUA_METHOD("setAlphaThreshold", lua_cocos2d_ClippingNode_setAlphaThreshold);
	LUA_METHOD("setInverted", lua_cocos2d_ClippingNode_setInverted);
	LUA_METHOD("setStencil", lua_cocos2d_ClippingNode_setStencil);
	LUA_METHOD("create", lua_cocos2d_ClippingNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ClippingRectangleNode_getClippingRegion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:getClippingRegion");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::ClippingRectangleNode::*)()const>(&cocos2d::ClippingRectangleNode::getClippingRegion));
	LUA_INVOKE_FOOTER("0");
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
int lua_cocos2d_ClippingRectangleNode_setClippingRegion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:setClippingRegion");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ClippingRectangleNode::*)(const cocos2d::Rect&)>(&cocos2d::ClippingRectangleNode::setClippingRegion));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ClippingRectangleNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ClippingRectangleNode*(*)(const cocos2d::Rect&)>(&cocos2d::ClippingRectangleNode::create));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ClippingRectangleNode*(*)()>(&cocos2d::ClippingRectangleNode::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccClippingRectangleNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ClippingRectangleNode, "ClippingRectangleNode", "cc.ClippingRectangleNode",
		cocos2d::ClippingRectangleNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getClippingRegion", lua_cocos2d_ClippingRectangleNode_getClippingRegion);
	LUA_METHOD("isClippingEnabled", lua_cocos2d_ClippingRectangleNode_isClippingEnabled);
	LUA_METHOD("setClippingEnabled", lua_cocos2d_ClippingRectangleNode_setClippingEnabled);
	LUA_METHOD("setClippingRegion", lua_cocos2d_ClippingRectangleNode_setClippingRegion);
	LUA_METHOD("create", lua_cocos2d_ClippingRectangleNode_create);
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
int lua_cocos2d_DrawNode_drawCircle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCircle");
	LUA_TRY_INVOKE(8, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, float, unsigned int, bool, float, float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawCircle)));
	LUA_TRY_INVOKE(6, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, float, unsigned int, bool, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawCircle)));
	LUA_INVOKE_FOOTER("6,8");
}
int lua_cocos2d_DrawNode_drawCubicBezier(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCubicBezier");
	LUA_TRY_INVOKE(6, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, unsigned int, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawCubicBezier)));
	LUA_INVOKE_FOOTER("6");
}
int lua_cocos2d_DrawNode_drawDot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawDot");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawDot)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_DrawNode_drawLine(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawLine");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawLine)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_DrawNode_drawPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawPoint");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawPoint)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_DrawNode_drawQuadBezier(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawQuadBezier");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, unsigned int, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawQuadBezier)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cocos2d_DrawNode_drawRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawRect");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawRect)));
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawRect)));
	LUA_INVOKE_FOOTER("3,5");
}
int lua_cocos2d_DrawNode_drawSegment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSegment");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawSegment)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_DrawNode_drawSolidCircle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSolidCircle");
	LUA_TRY_INVOKE(9, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, float, unsigned int, float, float, const cocos2d::Color4B&, float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawSolidCircle)));
	LUA_TRY_INVOKE(7, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, float, unsigned int, float, float, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawSolidCircle)));
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, float, float, unsigned int, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawSolidCircle)));
	LUA_INVOKE_FOOTER("5,7,9");
}
int lua_cocos2d_DrawNode_drawSolidRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSolidRect");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawSolidRect)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_DrawNode_drawTriangle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawTriangle");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::DrawNode::*)(const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Vec2&, const cocos2d::Color4B&)>(&cocos2d::DrawNode::drawTriangle)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_DrawNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::BlendFunc&(cocos2d::DrawNode::*)()const>(&cocos2d::DrawNode::getBlendFunc));
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
int lua_cocos2d_DrawNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setBlendFunc");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::DrawNode::*)(const cocos2d::BlendFunc&)>(&cocos2d::DrawNode::setBlendFunc));
	LUA_INVOKE_FOOTER("1");
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
		cocos2d::DrawNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("clear", lua_cocos2d_DrawNode_clear);
	LUA_METHOD("drawCircle", lua_cocos2d_DrawNode_drawCircle);
	LUA_METHOD("drawCubicBezier", lua_cocos2d_DrawNode_drawCubicBezier);
	LUA_METHOD("drawDot", lua_cocos2d_DrawNode_drawDot);
	LUA_METHOD("drawLine", lua_cocos2d_DrawNode_drawLine);
	LUA_METHOD("drawPoint", lua_cocos2d_DrawNode_drawPoint);
	LUA_METHOD("drawQuadBezier", lua_cocos2d_DrawNode_drawQuadBezier);
	LUA_METHOD("drawRect", lua_cocos2d_DrawNode_drawRect);
	LUA_METHOD("drawSegment", lua_cocos2d_DrawNode_drawSegment);
	LUA_METHOD("drawSolidCircle", lua_cocos2d_DrawNode_drawSolidCircle);
	LUA_METHOD("drawSolidRect", lua_cocos2d_DrawNode_drawSolidRect);
	LUA_METHOD("drawTriangle", lua_cocos2d_DrawNode_drawTriangle);
	LUA_METHOD("getBlendFunc", lua_cocos2d_DrawNode_getBlendFunc);
	LUA_METHOD("getLineWidth", lua_cocos2d_DrawNode_getLineWidth);
	LUA_METHOD("isIsolated", lua_cocos2d_DrawNode_isIsolated);
	LUA_METHOD("setBlendFunc", lua_cocos2d_DrawNode_setBlendFunc);
	LUA_METHOD("setIsolated", lua_cocos2d_DrawNode_setIsolated);
	LUA_METHOD("setLineWidth", lua_cocos2d_DrawNode_setLineWidth);
	LUA_METHOD("create", lua_cocos2d_DrawNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
