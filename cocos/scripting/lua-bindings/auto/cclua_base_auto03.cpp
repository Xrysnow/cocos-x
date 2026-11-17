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
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/CCPhysics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#endif

int lua_cc_JumpTiles3D_getAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:getAmplitude");
	LUA_TRY_INVOKE_R(0, &cc::JumpTiles3D::getAmplitude);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_JumpTiles3D_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, &cc::JumpTiles3D::getAmplitudeRate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_JumpTiles3D_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::JumpTiles3D::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_JumpTiles3D_setAmplitude(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:setAmplitude");
	LUA_TRY_INVOKE(1, &cc::JumpTiles3D::setAmplitude);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_JumpTiles3D_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:setAmplitudeRate");
	LUA_TRY_INVOKE(1, &cc::JumpTiles3D::setAmplitudeRate);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_JumpTiles3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTiles3D", "cc.JumpTiles3D:create");
	LUA_TRY_INVOKE_R(4, &cc::JumpTiles3D::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTiles3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::JumpTiles3D, "JumpTiles3D", "cc.JumpTiles3D",
		cc::JumpTiles3D, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitude", lua_cc_JumpTiles3D_getAmplitude);
	LUA_METHOD("getAmplitudeRate", lua_cc_JumpTiles3D_getAmplitudeRate);
	LUA_METHOD("initWithDuration", lua_cc_JumpTiles3D_initWithDuration);
	LUA_METHOD("setAmplitude", lua_cc_JumpTiles3D_setAmplitude);
	LUA_METHOD("setAmplitudeRate", lua_cc_JumpTiles3D_setAmplitudeRate);
	LUA_METHOD("create", lua_cc_JumpTiles3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SplitRows_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SplitRows", "cc.SplitRows:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::SplitRows::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SplitRows_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitRows", "cc.SplitRows:create");
	LUA_TRY_INVOKE_R(2, &cc::SplitRows::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitRows(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SplitRows, "SplitRows", "cc.SplitRows",
		cc::SplitRows, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_SplitRows_initWithDuration);
	LUA_METHOD("create", lua_cc_SplitRows_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SplitCols_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SplitCols", "cc.SplitCols:initWithDuration");
	LUA_TRY_INVOKE_R(2, &cc::SplitCols::initWithDuration);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SplitCols_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SplitCols", "cc.SplitCols:create");
	LUA_TRY_INVOKE_R(2, &cc::SplitCols::create);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSplitCols(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SplitCols, "SplitCols", "cc.SplitCols",
		cc::SplitCols, "cc.TiledGrid3DAction",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_SplitCols_initWithDuration);
	LUA_METHOD("create", lua_cc_SplitCols_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ActionTween_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionTween", "cc.ActionTween:initWithDuration");
	LUA_TRY_INVOKE_R(4, &cc::ActionTween::initWithDuration);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_ActionTween_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionTween", "cc.ActionTween:create");
	LUA_TRY_INVOKE_R(4, &cc::ActionTween::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionTween(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ActionTween, "ActionTween", "cc.ActionTween",
		cc::ActionTween, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cc_ActionTween_initWithDuration);
	LUA_METHOD("create", lua_cc_ActionTween_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_AtlasNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::AtlasNode::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AtlasNode_getQuadsToDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getQuadsToDraw");
	LUA_TRY_INVOKE_R(0, &cc::AtlasNode::getQuadsToDraw);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AtlasNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::AtlasNode::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AtlasNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, &cc::AtlasNode::getTextureAtlas);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AtlasNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTexture");
	LUA_TRY_INVOKE_R(4, &cc::AtlasNode::initWithTexture);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_AtlasNode_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:initWithTileFile");
	LUA_TRY_INVOKE_R(4, &cc::AtlasNode::initWithTileFile);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_AtlasNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::AtlasNode::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AtlasNode_setQuadsToDraw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setQuadsToDraw");
	LUA_TRY_INVOKE(1, &cc::AtlasNode::setQuadsToDraw);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AtlasNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setTexture");
	LUA_TRY_INVOKE(1, &cc::AtlasNode::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AtlasNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, &cc::AtlasNode::setTextureAtlas);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AtlasNode_updateAtlasValues(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:updateAtlasValues");
	LUA_TRY_INVOKE(0, &cc::AtlasNode::updateAtlasValues);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AtlasNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AtlasNode", "cc.AtlasNode:create");
	LUA_TRY_INVOKE_R(4, &cc::AtlasNode::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccAtlasNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AtlasNode, "AtlasNode", "cc.AtlasNode",
		cc::AtlasNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cc_AtlasNode_getBlendFunc);
	LUA_METHOD("getQuadsToDraw", lua_cc_AtlasNode_getQuadsToDraw);
	LUA_METHOD("getTexture", lua_cc_AtlasNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cc_AtlasNode_getTextureAtlas);
	LUA_METHOD("initWithTexture", lua_cc_AtlasNode_initWithTexture);
	LUA_METHOD("initWithTileFile", lua_cc_AtlasNode_initWithTileFile);
	LUA_METHOD("setBlendFunc", lua_cc_AtlasNode_setBlendFunc);
	LUA_METHOD("setQuadsToDraw", lua_cc_AtlasNode_setQuadsToDraw);
	LUA_METHOD("setTexture", lua_cc_AtlasNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cc_AtlasNode_setTextureAtlas);
	LUA_METHOD("updateAtlasValues", lua_cc_AtlasNode_updateAtlasValues);
	LUA_METHOD("create", lua_cc_AtlasNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ClippingNode_getAlphaThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:getAlphaThreshold");
	LUA_TRY_INVOKE_R(0, &cc::ClippingNode::getAlphaThreshold);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingNode_getStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:getStencil");
	LUA_TRY_INVOKE_R(0, &cc::ClippingNode::getStencil);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingNode_hasContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:hasContent");
	LUA_TRY_INVOKE_R(0, &cc::ClippingNode::hasContent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingNode_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::ClippingNode::*)(cc::Node*)>(&cc::ClippingNode::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingNode_isInverted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:isInverted");
	LUA_TRY_INVOKE_R(0, &cc::ClippingNode::isInverted);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingNode_setAlphaThreshold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setAlphaThreshold");
	LUA_TRY_INVOKE(1, &cc::ClippingNode::setAlphaThreshold);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingNode_setInverted(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setInverted");
	LUA_TRY_INVOKE(1, &cc::ClippingNode::setInverted);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingNode_setStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:setStencil");
	LUA_TRY_INVOKE(1, &cc::ClippingNode::setStencil);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ClippingNode", "cc.ClippingNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::ClippingNode>(*)(cc::Node*)>(&cc::ClippingNode::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::ClippingNode>(*)()>(&cc::ClippingNode::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccClippingNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ClippingNode, "ClippingNode", "cc.ClippingNode",
		cc::ClippingNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAlphaThreshold", lua_cc_ClippingNode_getAlphaThreshold);
	LUA_METHOD("getStencil", lua_cc_ClippingNode_getStencil);
	LUA_METHOD("hasContent", lua_cc_ClippingNode_hasContent);
	LUA_METHOD("init", lua_cc_ClippingNode_init_1);
	LUA_METHOD("isInverted", lua_cc_ClippingNode_isInverted);
	LUA_METHOD("setAlphaThreshold", lua_cc_ClippingNode_setAlphaThreshold);
	LUA_METHOD("setInverted", lua_cc_ClippingNode_setInverted);
	LUA_METHOD("setStencil", lua_cc_ClippingNode_setStencil);
	LUA_METHOD("create", lua_cc_ClippingNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ClippingRectangleNode_getClippingRegion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:getClippingRegion");
	LUA_TRY_INVOKE_R(0, &cc::ClippingRectangleNode::getClippingRegion);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingRectangleNode_isClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:isClippingEnabled");
	LUA_TRY_INVOKE_R(0, &cc::ClippingRectangleNode::isClippingEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_ClippingRectangleNode_setClippingEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:setClippingEnabled");
	LUA_TRY_INVOKE(1, &cc::ClippingRectangleNode::setClippingEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingRectangleNode_setClippingRegion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:setClippingRegion");
	LUA_TRY_INVOKE(1, &cc::ClippingRectangleNode::setClippingRegion);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ClippingRectangleNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ClippingRectangleNode", "cc.ClippingRectangleNode:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::ClippingRectangleNode>(*)(const cc::Rect&)>(&cc::ClippingRectangleNode::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::ClippingRectangleNode>(*)()>(&cc::ClippingRectangleNode::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccClippingRectangleNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ClippingRectangleNode, "ClippingRectangleNode", "cc.ClippingRectangleNode",
		cc::ClippingRectangleNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getClippingRegion", lua_cc_ClippingRectangleNode_getClippingRegion);
	LUA_METHOD("isClippingEnabled", lua_cc_ClippingRectangleNode_isClippingEnabled);
	LUA_METHOD("setClippingEnabled", lua_cc_ClippingRectangleNode_setClippingEnabled);
	LUA_METHOD("setClippingRegion", lua_cc_ClippingRectangleNode_setClippingRegion);
	LUA_METHOD("create", lua_cc_ClippingRectangleNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_DrawNode_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:clear");
	LUA_TRY_INVOKE(0, &cc::DrawNode::clear);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DrawNode_drawCircle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCircle");
	LUA_TRY_INVOKE(8, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, float, float, unsigned int, bool, float, float, const cc::Color4B&)>(&cc::DrawNode::drawCircle)));
	LUA_TRY_INVOKE(6, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, float, float, unsigned int, bool, const cc::Color4B&)>(&cc::DrawNode::drawCircle)));
	LUA_INVOKE_FOOTER("6,8");
}
int lua_cc_DrawNode_drawCubicBezier(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawCubicBezier");
	LUA_TRY_INVOKE(6, &cc::DrawNode::drawCubicBezier);
	LUA_INVOKE_FOOTER("6");
}
int lua_cc_DrawNode_drawDot(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawDot");
	LUA_TRY_INVOKE(3, &cc::DrawNode::drawDot);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_DrawNode_drawLine(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawLine");
	LUA_TRY_INVOKE(3, &cc::DrawNode::drawLine);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_DrawNode_drawPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawPoint");
	LUA_TRY_INVOKE(3, &cc::DrawNode::drawPoint);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_DrawNode_drawQuadBezier(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawQuadBezier");
	LUA_TRY_INVOKE(5, &cc::DrawNode::drawQuadBezier);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_DrawNode_drawRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawRect");
	LUA_TRY_INVOKE(5, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, const cc::Vec2&, const cc::Vec2&, const cc::Vec2&, const cc::Color4B&)>(&cc::DrawNode::drawRect)));
	LUA_TRY_INVOKE(3, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, const cc::Vec2&, const cc::Color4B&)>(&cc::DrawNode::drawRect)));
	LUA_INVOKE_FOOTER("3,5");
}
int lua_cc_DrawNode_drawSegment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSegment");
	LUA_TRY_INVOKE(4, &cc::DrawNode::drawSegment);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_DrawNode_drawSolidCircle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSolidCircle");
	LUA_TRY_INVOKE(9, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, float, float, unsigned int, float, float, const cc::Color4B&, float, const cc::Color4B&)>(&cc::DrawNode::drawSolidCircle)));
	LUA_TRY_INVOKE(7, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, float, float, unsigned int, float, float, const cc::Color4B&)>(&cc::DrawNode::drawSolidCircle)));
	LUA_TRY_INVOKE(5, (static_cast<void(cc::DrawNode::*)(const cc::Vec2&, float, float, unsigned int, const cc::Color4B&)>(&cc::DrawNode::drawSolidCircle)));
	LUA_INVOKE_FOOTER("5,7,9");
}
int lua_cc_DrawNode_drawSolidRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawSolidRect");
	LUA_TRY_INVOKE(3, &cc::DrawNode::drawSolidRect);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_DrawNode_drawTriangle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:drawTriangle");
	LUA_TRY_INVOKE(4, &cc::DrawNode::drawTriangle);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_DrawNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::DrawNode::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DrawNode_getLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:getLineWidth");
	LUA_TRY_INVOKE_R(0, &cc::DrawNode::getLineWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DrawNode_isIsolated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:isIsolated");
	LUA_TRY_INVOKE_R(0, &cc::DrawNode::isIsolated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_DrawNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::DrawNode::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_DrawNode_setIsolated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setIsolated");
	LUA_TRY_INVOKE(1, &cc::DrawNode::setIsolated);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_DrawNode_setLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.DrawNode", "cc.DrawNode:setLineWidth");
	LUA_TRY_INVOKE(1, &cc::DrawNode::setLineWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_DrawNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DrawNode", "cc.DrawNode:create");
	LUA_TRY_INVOKE_R(1, &cc::DrawNode::create);
	LUA_TRY_INVOKE_R(0, [](){{return cc::DrawNode::create();}});
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccDrawNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::DrawNode, "DrawNode", "cc.DrawNode",
		cc::DrawNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("clear", lua_cc_DrawNode_clear);
	LUA_METHOD("drawCircle", lua_cc_DrawNode_drawCircle);
	LUA_METHOD("drawCubicBezier", lua_cc_DrawNode_drawCubicBezier);
	LUA_METHOD("drawDot", lua_cc_DrawNode_drawDot);
	LUA_METHOD("drawLine", lua_cc_DrawNode_drawLine);
	LUA_METHOD("drawPoint", lua_cc_DrawNode_drawPoint);
	LUA_METHOD("drawQuadBezier", lua_cc_DrawNode_drawQuadBezier);
	LUA_METHOD("drawRect", lua_cc_DrawNode_drawRect);
	LUA_METHOD("drawSegment", lua_cc_DrawNode_drawSegment);
	LUA_METHOD("drawSolidCircle", lua_cc_DrawNode_drawSolidCircle);
	LUA_METHOD("drawSolidRect", lua_cc_DrawNode_drawSolidRect);
	LUA_METHOD("drawTriangle", lua_cc_DrawNode_drawTriangle);
	LUA_METHOD("getBlendFunc", lua_cc_DrawNode_getBlendFunc);
	LUA_METHOD("getLineWidth", lua_cc_DrawNode_getLineWidth);
	LUA_METHOD("isIsolated", lua_cc_DrawNode_isIsolated);
	LUA_METHOD("setBlendFunc", lua_cc_DrawNode_setBlendFunc);
	LUA_METHOD("setIsolated", lua_cc_DrawNode_setIsolated);
	LUA_METHOD("setLineWidth", lua_cc_DrawNode_setLineWidth);
	LUA_METHOD("create", lua_cc_DrawNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Label_disableEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:disableEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Label::*)(cc::LabelEffect)>(&cc::Label::disableEffect));
	LUA_TRY_INVOKE(0, static_cast<void(cc::Label::*)()>(&cc::Label::disableEffect));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Label_enableBold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableBold");
	LUA_TRY_INVOKE(0, &cc::Label::enableBold);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_enableGlow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableGlow");
	LUA_TRY_INVOKE(1, &cc::Label::enableGlow);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_enableItalics(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableItalics");
	LUA_TRY_INVOKE(0, &cc::Label::enableItalics);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_enableOutline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableOutline");
	LUA_TRY_INVOKE(2, &cc::Label::enableOutline);
	LUA_TRY_INVOKE(1, ([](cc::Label* obj,const cc::Color4B& arg0){{return obj->enableOutline(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Label_enableShadow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableShadow");
	LUA_TRY_INVOKE(3, &cc::Label::enableShadow);
	LUA_TRY_INVOKE(2, ([](cc::Label* obj,const cc::Color4B& arg0,const cc::Vec2& arg1){{return obj->enableShadow(arg0,arg1);}}));
	LUA_TRY_INVOKE(1, ([](cc::Label* obj,const cc::Color4B& arg0){{return obj->enableShadow(arg0);}}));
	LUA_TRY_INVOKE(0, [](cc::Label* obj){{return obj->enableShadow();}});
	LUA_INVOKE_FOOTER("0,1,2,3");
}
int lua_cc_Label_enableStrikethrough(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableStrikethrough");
	LUA_TRY_INVOKE(0, &cc::Label::enableStrikethrough);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_enableUnderline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableUnderline");
	LUA_TRY_INVOKE(0, &cc::Label::enableUnderline);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_enableWrap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableWrap");
	LUA_TRY_INVOKE(1, &cc::Label::enableWrap);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_getAdditionalKerning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getAdditionalKerning");
	LUA_TRY_INVOKE_R(0, &cc::Label::getAdditionalKerning);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getBMFontFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getBMFontFilePath");
	LUA_TRY_INVOKE_R(0, &cc::Label::getBMFontFilePath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getBMFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getBMFontSize");
	LUA_TRY_INVOKE_R(0, &cc::Label::getBMFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::Label::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getDimensions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getDimensions");
	LUA_TRY_INVOKE_R(0, &cc::Label::getDimensions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getEffectColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getEffectColor");
	LUA_TRY_INVOKE_R(0, &cc::Label::getEffectColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getFontAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getFontAtlas");
	LUA_TRY_INVOKE_R(0, &cc::Label::getFontAtlas);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getHeight");
	LUA_TRY_INVOKE_R(0, &cc::Label::getHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, &cc::Label::getHorizontalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getLabelEffectType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLabelEffectType");
	LUA_TRY_INVOKE_R(0, &cc::Label::getLabelEffectType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getLabelType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLabelType");
	LUA_TRY_INVOKE_R(0, &cc::Label::getLabelType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getLetter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLetter");
	LUA_TRY_INVOKE_R(1, &cc::Label::getLetter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_getLineHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLineHeight");
	LUA_TRY_INVOKE_R(0, &cc::Label::getLineHeight);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getLineSpacing(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLineSpacing");
	LUA_TRY_INVOKE_R(0, &cc::Label::getLineSpacing);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getMaxLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getMaxLineWidth");
	LUA_TRY_INVOKE_R(0, &cc::Label::getMaxLineWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getOutlineSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getOutlineSize");
	LUA_TRY_INVOKE_R(0, &cc::Label::getOutlineSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getOverflow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getOverflow");
	LUA_TRY_INVOKE_R(0, &cc::Label::getOverflow);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getRenderingFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getRenderingFontSize");
	LUA_TRY_INVOKE_R(0, &cc::Label::getRenderingFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getShadowBlurRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getShadowBlurRadius");
	LUA_TRY_INVOKE_R(0, &cc::Label::getShadowBlurRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getShadowColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getShadowColor");
	LUA_TRY_INVOKE_R(0, &cc::Label::getShadowColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getShadowOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getShadowOffset");
	LUA_TRY_INVOKE_R(0, &cc::Label::getShadowOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getString");
	LUA_TRY_INVOKE_R(0, &cc::Label::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getStringLength");
	LUA_TRY_INVOKE_R(0, &cc::Label::getStringLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getStringNumLines(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getStringNumLines");
	LUA_TRY_INVOKE_R(0, &cc::Label::getStringNumLines);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getSystemFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getSystemFontName");
	LUA_TRY_INVOKE_R(0, &cc::Label::getSystemFontName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getSystemFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getSystemFontSize");
	LUA_TRY_INVOKE_R(0, &cc::Label::getSystemFontSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getTTFConfig(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getTTFConfig");
	LUA_TRY_INVOKE_R(0, &cc::Label::getTTFConfig);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getTextAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getTextAlignment");
	LUA_TRY_INVOKE_R(0, &cc::Label::getTextAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getTextColor");
	LUA_TRY_INVOKE_R(0, &cc::Label::getTextColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getVerticalAlignment");
	LUA_TRY_INVOKE_R(0, &cc::Label::getVerticalAlignment);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getWidth");
	LUA_TRY_INVOKE_R(0, &cc::Label::getWidth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_initWithTTF(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:initWithTTF");
	LUA_TRY_INVOKE_R(6, (static_cast<bool(cc::Label::*)(std::string_view, std::string_view, float, const cc::Vec2&, cc::TextHAlignment, cc::TextVAlignment)>(&cc::Label::initWithTTF)));
	LUA_TRY_INVOKE_R(5, ([](cc::Label* obj,std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4){{return obj->initWithTTF(std::move(arg0),std::move(arg1),std::move(arg2),arg3,std::move(arg4));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<bool(cc::Label::*)(const cc::TTFConfig&, std::string_view, cc::TextHAlignment, int)>(&cc::Label::initWithTTF)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](cc::Label* obj,std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3){{return obj->initWithTTF(std::move(arg0),std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cc::Label* obj,const cc::TTFConfig& arg0,std::string_view arg1,cc::TextHAlignment arg2){{return obj->initWithTTF(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cc::Label* obj,std::string_view arg0,std::string_view arg1,float arg2){{return obj->initWithTTF(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](cc::Label* obj,const cc::TTFConfig& arg0,std::string_view arg1){{return obj->initWithTTF(arg0,std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3,4,5,6");
}
int lua_cc_Label_isClipMarginEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isClipMarginEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Label::isClipMarginEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_isShadowEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isShadowEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Label::isShadowEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_isWrapEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isWrapEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Label::isWrapEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::Label::removeAllChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_requestSystemFontRefresh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:requestSystemFontRefresh");
	LUA_TRY_INVOKE(0, &cc::Label::requestSystemFontRefresh);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_setAdditionalKerning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setAdditionalKerning");
	LUA_TRY_INVOKE(1, &cc::Label::setAdditionalKerning);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setAlignment");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::Label::*)(cc::TextHAlignment, cc::TextVAlignment)>(&cc::Label::setAlignment)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Label::*)(cc::TextHAlignment)>(&cc::Label::setAlignment));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Label_setBMFontFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setBMFontFilePath");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cc::Label::*)(std::string_view, const cc::Rect&, bool, float)>(&cc::Label::setBMFontFilePath)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cc::Label::*)(std::string_view, std::string_view, float)>(&cc::Label::setBMFontFilePath)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](cc::Label* obj,std::string_view arg0,const cc::Rect& arg1,bool arg2){{return obj->setBMFontFilePath(std::move(arg0),arg1,std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, ([](cc::Label* obj,std::string_view arg0,std::string_view arg1){{return obj->setBMFontFilePath(std::move(arg0),std::move(arg1));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::Label::*)(std::string_view, float)>(&cc::Label::setBMFontFilePath)));
	LUA_TRY_INVOKE_R(1, ([](cc::Label* obj,std::string_view arg0){{return obj->setBMFontFilePath(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2,3,4");
}
int lua_cc_Label_setBMFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setBMFontSize");
	LUA_TRY_INVOKE(1, &cc::Label::setBMFontSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::Label::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setCharMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setCharMap");
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<bool(cc::Label::*)(cc::Texture2D*, int, int, int)>(&cc::Label::setCharMap)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<bool(cc::Label::*)(std::string_view, int, int, int)>(&cc::Label::setCharMap)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Label::*)(std::string_view)>(&cc::Label::setCharMap));
	LUA_INVOKE_FOOTER("1,4");
}
int lua_cc_Label_setClipMarginEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setClipMarginEnabled");
	LUA_TRY_INVOKE(1, &cc::Label::setClipMarginEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setDimensions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setDimensions");
	LUA_TRY_INVOKE(2, &cc::Label::setDimensions);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Label_setHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setHeight");
	LUA_TRY_INVOKE(1, &cc::Label::setHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setHorizontalAlignment");
	LUA_TRY_INVOKE(1, &cc::Label::setHorizontalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setLineBreakWithoutSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineBreakWithoutSpace");
	LUA_TRY_INVOKE(1, &cc::Label::setLineBreakWithoutSpace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setLineHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineHeight");
	LUA_TRY_INVOKE(1, &cc::Label::setLineHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setLineSpacing(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineSpacing");
	LUA_TRY_INVOKE(1, &cc::Label::setLineSpacing);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setMaxLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setMaxLineWidth");
	LUA_TRY_INVOKE(1, &cc::Label::setMaxLineWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setOverflow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setOverflow");
	LUA_TRY_INVOKE(1, &cc::Label::setOverflow);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setString");
	LUA_TRY_INVOKE(1, &cc::Label::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setSystemFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setSystemFontName");
	LUA_TRY_INVOKE(1, &cc::Label::setSystemFontName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setSystemFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setSystemFontSize");
	LUA_TRY_INVOKE(1, &cc::Label::setSystemFontSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setTTFConfig(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setTTFConfig");
	LUA_TRY_INVOKE_R(1, &cc::Label::setTTFConfig);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setTextColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setTextColor");
	LUA_TRY_INVOKE(1, &cc::Label::setTextColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setVerticalAlignment");
	LUA_TRY_INVOKE(1, &cc::Label::setVerticalAlignment);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_setWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setWidth");
	LUA_TRY_INVOKE(1, &cc::Label::setWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Label_updateContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:updateContent");
	LUA_TRY_INVOKE(0, &cc::Label::updateContent);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Label_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:create");
	LUA_TRY_INVOKE_R(0, &cc::Label::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Label_createWithBMFont(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:createWithBMFont");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view, std::string_view, const cc::TextHAlignment&, int, const cc::Rect&, bool)>(&cc::Label::createWithBMFont)));
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view, std::string_view, const cc::TextHAlignment&, int, std::string_view)>(&cc::Label::createWithBMFont)));
	LUA_TRY_INVOKE_R(4, (static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view, std::string_view, const cc::TextHAlignment&, int)>(&cc::Label::createWithBMFont)));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,std::string_view arg1,const cc::TextHAlignment& arg2){{return cc::Label::createWithBMFont(std::move(arg0),std::move(arg1),arg2);}}));
	LUA_TRY_INVOKE_R(2, ([](std::string_view arg0,std::string_view arg1){{return cc::Label::createWithBMFont(std::move(arg0),std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3,4,5,6");
}
int lua_cc_Label_createWithCharMap(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:createWithCharMap");
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cc::IntrusivePtr<cc::Label>(*)(cc::Texture2D*, int, int, int)>(&cc::Label::createWithCharMap)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view, int, int, int)>(&cc::Label::createWithCharMap)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view)>(&cc::Label::createWithCharMap));
	LUA_SINVOKE_FOOTER("1,4");
}
int lua_cc_Label_createWithSystemFont(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:createWithSystemFont");
	LUA_TRY_INVOKE_R(6, &cc::Label::createWithSystemFont);
	LUA_TRY_INVOKE_R(5, ([](std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4){{return cc::Label::createWithSystemFont(std::move(arg0),std::move(arg1),std::move(arg2),arg3,std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3){{return cc::Label::createWithSystemFont(std::move(arg0),std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE_R(3, ([](std::string_view arg0,std::string_view arg1,float arg2){{return cc::Label::createWithSystemFont(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4,5,6");
}
int lua_cc_Label_createWithTTF(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:createWithTTF");
	LUA_TRY_INVOKE_R(6, (static_cast<cc::IntrusivePtr<cc::Label>(*)(std::string_view, std::string_view, float, const cc::Vec2&, cc::TextHAlignment, cc::TextVAlignment)>(&cc::Label::createWithTTF)));
	LUA_TRY_INVOKE_R(5, ([](std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4){{return cc::Label::createWithTTF(std::move(arg0),std::move(arg1),std::move(arg2),arg3,std::move(arg4));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(4, (static_cast<cc::IntrusivePtr<cc::Label>(*)(const cc::TTFConfig&, std::string_view, cc::TextHAlignment, int)>(&cc::Label::createWithTTF)));
	LUA_TRY_INVOKE_R_OVERLOAD(4, ([](std::string_view arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3){{return cc::Label::createWithTTF(std::move(arg0),std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](const cc::TTFConfig& arg0,std::string_view arg1,cc::TextHAlignment arg2){{return cc::Label::createWithTTF(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R_OVERLOAD(3, ([](std::string_view arg0,std::string_view arg1,float arg2){{return cc::Label::createWithTTF(std::move(arg0),std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, ([](const cc::TTFConfig& arg0,std::string_view arg1){{return cc::Label::createWithTTF(arg0,std::move(arg1));}}));
	LUA_SINVOKE_FOOTER("2,3,4,5,6");
}
int luaReg_Core_ccLabel(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Label, "Label", "cc.Label",
		cc::Label, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("disableEffect", lua_cc_Label_disableEffect);
	LUA_METHOD("enableBold", lua_cc_Label_enableBold);
	LUA_METHOD("enableGlow", lua_cc_Label_enableGlow);
	LUA_METHOD("enableItalics", lua_cc_Label_enableItalics);
	LUA_METHOD("enableOutline", lua_cc_Label_enableOutline);
	LUA_METHOD("enableShadow", lua_cc_Label_enableShadow);
	LUA_METHOD("enableStrikethrough", lua_cc_Label_enableStrikethrough);
	LUA_METHOD("enableUnderline", lua_cc_Label_enableUnderline);
	LUA_METHOD("enableWrap", lua_cc_Label_enableWrap);
	LUA_METHOD("getAdditionalKerning", lua_cc_Label_getAdditionalKerning);
	LUA_METHOD("getBMFontFilePath", lua_cc_Label_getBMFontFilePath);
	LUA_METHOD("getBMFontSize", lua_cc_Label_getBMFontSize);
	LUA_METHOD("getBlendFunc", lua_cc_Label_getBlendFunc);
	LUA_METHOD("getDimensions", lua_cc_Label_getDimensions);
	LUA_METHOD("getEffectColor", lua_cc_Label_getEffectColor);
	LUA_METHOD("getFontAtlas", lua_cc_Label_getFontAtlas);
	LUA_METHOD("getHeight", lua_cc_Label_getHeight);
	LUA_METHOD("getHorizontalAlignment", lua_cc_Label_getHorizontalAlignment);
	LUA_METHOD("getLabelEffectType", lua_cc_Label_getLabelEffectType);
	LUA_METHOD("getLabelType", lua_cc_Label_getLabelType);
	LUA_METHOD("getLetter", lua_cc_Label_getLetter);
	LUA_METHOD("getLineHeight", lua_cc_Label_getLineHeight);
	LUA_METHOD("getLineSpacing", lua_cc_Label_getLineSpacing);
	LUA_METHOD("getMaxLineWidth", lua_cc_Label_getMaxLineWidth);
	LUA_METHOD("getOutlineSize", lua_cc_Label_getOutlineSize);
	LUA_METHOD("getOverflow", lua_cc_Label_getOverflow);
	LUA_METHOD("getRenderingFontSize", lua_cc_Label_getRenderingFontSize);
	LUA_METHOD("getShadowBlurRadius", lua_cc_Label_getShadowBlurRadius);
	LUA_METHOD("getShadowColor", lua_cc_Label_getShadowColor);
	LUA_METHOD("getShadowOffset", lua_cc_Label_getShadowOffset);
	LUA_METHOD("getString", lua_cc_Label_getString);
	LUA_METHOD("getStringLength", lua_cc_Label_getStringLength);
	LUA_METHOD("getStringNumLines", lua_cc_Label_getStringNumLines);
	LUA_METHOD("getSystemFontName", lua_cc_Label_getSystemFontName);
	LUA_METHOD("getSystemFontSize", lua_cc_Label_getSystemFontSize);
	LUA_METHOD("getTTFConfig", lua_cc_Label_getTTFConfig);
	LUA_METHOD("getTextAlignment", lua_cc_Label_getTextAlignment);
	LUA_METHOD("getTextColor", lua_cc_Label_getTextColor);
	LUA_METHOD("getVerticalAlignment", lua_cc_Label_getVerticalAlignment);
	LUA_METHOD("getWidth", lua_cc_Label_getWidth);
	LUA_METHOD("initWithTTF", lua_cc_Label_initWithTTF);
	LUA_METHOD("isClipMarginEnabled", lua_cc_Label_isClipMarginEnabled);
	LUA_METHOD("isShadowEnabled", lua_cc_Label_isShadowEnabled);
	LUA_METHOD("isWrapEnabled", lua_cc_Label_isWrapEnabled);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cc_Label_removeAllChildrenWithCleanup);
	LUA_METHOD("requestSystemFontRefresh", lua_cc_Label_requestSystemFontRefresh);
	LUA_METHOD("setAdditionalKerning", lua_cc_Label_setAdditionalKerning);
	LUA_METHOD("setAlignment", lua_cc_Label_setAlignment);
	LUA_METHOD("setBMFontFilePath", lua_cc_Label_setBMFontFilePath);
	LUA_METHOD("setBMFontSize", lua_cc_Label_setBMFontSize);
	LUA_METHOD("setBlendFunc", lua_cc_Label_setBlendFunc);
	LUA_METHOD("setCharMap", lua_cc_Label_setCharMap);
	LUA_METHOD("setClipMarginEnabled", lua_cc_Label_setClipMarginEnabled);
	LUA_METHOD("setDimensions", lua_cc_Label_setDimensions);
	LUA_METHOD("setHeight", lua_cc_Label_setHeight);
	LUA_METHOD("setHorizontalAlignment", lua_cc_Label_setHorizontalAlignment);
	LUA_METHOD("setLineBreakWithoutSpace", lua_cc_Label_setLineBreakWithoutSpace);
	LUA_METHOD("setLineHeight", lua_cc_Label_setLineHeight);
	LUA_METHOD("setLineSpacing", lua_cc_Label_setLineSpacing);
	LUA_METHOD("setMaxLineWidth", lua_cc_Label_setMaxLineWidth);
	LUA_METHOD("setOverflow", lua_cc_Label_setOverflow);
	LUA_METHOD("setString", lua_cc_Label_setString);
	LUA_METHOD("setSystemFontName", lua_cc_Label_setSystemFontName);
	LUA_METHOD("setSystemFontSize", lua_cc_Label_setSystemFontSize);
	LUA_METHOD("setTTFConfig", lua_cc_Label_setTTFConfig);
	LUA_METHOD("setTextColor", lua_cc_Label_setTextColor);
	LUA_METHOD("setVerticalAlignment", lua_cc_Label_setVerticalAlignment);
	LUA_METHOD("setWidth", lua_cc_Label_setWidth);
	LUA_METHOD("updateContent", lua_cc_Label_updateContent);
	LUA_METHOD("create", lua_cc_Label_create);
	LUA_METHOD("createWithBMFont", lua_cc_Label_createWithBMFont);
	LUA_METHOD("createWithCharMap", lua_cc_Label_createWithCharMap);
	LUA_METHOD("createWithSystemFont", lua_cc_Label_createWithSystemFont);
	LUA_METHOD("createWithTTF", lua_cc_Label_createWithTTF);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_LabelAtlas_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LabelAtlas", "cc.LabelAtlas:getString");
	LUA_TRY_INVOKE_R(0, &cc::LabelAtlas::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LabelAtlas_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LabelAtlas", "cc.LabelAtlas:initWithString");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::LabelAtlas::*)(std::string_view, cc::Texture2D*, int, int, int)>(&cc::LabelAtlas::initWithString)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::LabelAtlas::*)(std::string_view, std::string_view, int, int, int)>(&cc::LabelAtlas::initWithString)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::LabelAtlas::*)(std::string_view, std::string_view)>(&cc::LabelAtlas::initWithString)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cc_LabelAtlas_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LabelAtlas", "cc.LabelAtlas:setString");
	LUA_TRY_INVOKE(1, &cc::LabelAtlas::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LabelAtlas__create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.LabelAtlas", "cc.LabelAtlas:_create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::LabelAtlas>(*)(std::string_view, cc::Texture2D*, int, int, int)>(&cc::LabelAtlas::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::LabelAtlas>(*)(std::string_view, std::string_view, int, int, int)>(&cc::LabelAtlas::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::LabelAtlas>(*)(std::string_view, std::string_view)>(&cc::LabelAtlas::create)));
	LUA_SINVOKE_FOOTER("2,5");
}
int luaReg_Core_ccLabelAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::LabelAtlas, "LabelAtlas", "cc.LabelAtlas",
		cc::LabelAtlas, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_METHOD("getString", lua_cc_LabelAtlas_getString);
	LUA_METHOD("initWithString", lua_cc_LabelAtlas_initWithString);
	LUA_METHOD("setString", lua_cc_LabelAtlas_setString);
	LUA_METHOD("_create", lua_cc_LabelAtlas__create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Sprite_getAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getAtlasIndex");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getAtlasIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getBatchNode");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getBatchNode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getCenterRect");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getCenterRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getCenterRectNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getCenterRectNormalized");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getCenterRectNormalized);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getOffsetPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getOffsetPosition");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getOffsetPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getResourceName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getResourceName");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getResourceName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getResourceType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getResourceType");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getResourceType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getSpriteFrame);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getTextureAtlas);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_getTextureRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getTextureRect");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::getTextureRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithFile");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::Sprite::*)(std::string_view, const cc::Rect&)>(&cc::Sprite::initWithFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cc::Sprite::*)(std::string_view, cc::PixelFormat)>(&cc::Sprite::initWithFile)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Sprite::*)(std::string_view)>(&cc::Sprite::initWithFile));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Sprite_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(1, &cc::Sprite::initWithSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_initWithSpriteFrameName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithSpriteFrameName");
	LUA_TRY_INVOKE_R(1, &cc::Sprite::initWithSpriteFrameName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithTexture");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::Sprite::*)(cc::Texture2D*, const cc::Rect&, bool)>(&cc::Sprite::initWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::Sprite::*)(cc::Texture2D*, const cc::Rect&)>(&cc::Sprite::initWithTexture)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Sprite::*)(cc::Texture2D*)>(&cc::Sprite::initWithTexture));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_Sprite_isDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isDirty");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::isDirty);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_isFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFlippedX");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::isFlippedX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_isFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFlippedY");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::isFlippedY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_isFrameDisplayed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFrameDisplayed");
	LUA_TRY_INVOKE_R(1, &cc::Sprite::isFrameDisplayed);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_isStretchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isStretchEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::isStretchEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_isTextureRectRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isTextureRectRotated");
	LUA_TRY_INVOKE_R(0, &cc::Sprite::isTextureRectRotated);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::Sprite::removeAllChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setAtlasIndex");
	LUA_TRY_INVOKE(1, &cc::Sprite::setAtlasIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setBatchNode");
	LUA_TRY_INVOKE(1, &cc::Sprite::setBatchNode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::Sprite::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setCenterRect");
	LUA_TRY_INVOKE(1, &cc::Sprite::setCenterRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setCenterRectNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setCenterRectNormalized");
	LUA_TRY_INVOKE(1, &cc::Sprite::setCenterRectNormalized);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setDirty");
	LUA_TRY_INVOKE(1, &cc::Sprite::setDirty);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setDisplayFrameWithAnimationName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setDisplayFrameWithAnimationName");
	LUA_TRY_INVOKE(2, &cc::Sprite::setDisplayFrameWithAnimationName);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Sprite_setFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setFlippedX");
	LUA_TRY_INVOKE(1, &cc::Sprite::setFlippedX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setFlippedY");
	LUA_TRY_INVOKE(1, &cc::Sprite::setFlippedY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setSpriteFrame");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Sprite::*)(cc::SpriteFrame*)>(&cc::Sprite::setSpriteFrame));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Sprite::*)(std::string_view)>(&cc::Sprite::setSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setStretchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setStretchEnabled");
	LUA_TRY_INVOKE(1, &cc::Sprite::setStretchEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setTexture");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Sprite::*)(cc::Texture2D*)>(&cc::Sprite::setTexture));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Sprite::*)(std::string_view)>(&cc::Sprite::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setTextureAtlas");
	LUA_TRY_INVOKE(1, &cc::Sprite::setTextureAtlas);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_setTextureRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setTextureRect");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::Sprite::*)(const cc::Rect&, bool, const cc::Vec2&)>(&cc::Sprite::setTextureRect)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Sprite::*)(const cc::Rect&)>(&cc::Sprite::setTextureRect));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cc_Sprite_setVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setVertexLayout");
	LUA_TRY_INVOKE(0, &cc::Sprite::setVertexLayout);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Sprite_setVertexRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setVertexRect");
	LUA_TRY_INVOKE(1, &cc::Sprite::setVertexRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Sprite_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Sprite>(*)()>(&cc::Sprite::create));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::Sprite>(*)(std::string_view)>(&cc::Sprite::create));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::Sprite>(*)(std::string_view, const cc::Rect&)>(&cc::Sprite::create)));
	LUA_SINVOKE_FOOTER("0,1,2");
}
int lua_cc_Sprite_createWithSpriteFrame(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:createWithSpriteFrame");
	LUA_TRY_INVOKE_R(1, &cc::Sprite::createWithSpriteFrame);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Sprite_createWithSpriteFrameName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:createWithSpriteFrameName");
	LUA_TRY_INVOKE_R(1, &cc::Sprite::createWithSpriteFrameName);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Sprite_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:createWithTexture");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::Sprite>(*)(cc::Texture2D*, const cc::Rect&, bool)>(&cc::Sprite::createWithTexture)));
	LUA_TRY_INVOKE_R(2, ([](cc::Texture2D* arg0,const cc::Rect& arg1){{return cc::Sprite::createWithTexture(arg0,arg1);}}));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::Sprite>(*)(cc::Texture2D*)>(&cc::Sprite::createWithTexture));
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Core_ccSprite(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Sprite, "Sprite", "cc.Sprite",
		cc::Sprite, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAtlasIndex", lua_cc_Sprite_getAtlasIndex);
	LUA_METHOD("getBatchNode", lua_cc_Sprite_getBatchNode);
	LUA_METHOD("getBlendFunc", lua_cc_Sprite_getBlendFunc);
	LUA_METHOD("getCenterRect", lua_cc_Sprite_getCenterRect);
	LUA_METHOD("getCenterRectNormalized", lua_cc_Sprite_getCenterRectNormalized);
	LUA_METHOD("getOffsetPosition", lua_cc_Sprite_getOffsetPosition);
	LUA_METHOD("getResourceName", lua_cc_Sprite_getResourceName);
	LUA_METHOD("getResourceType", lua_cc_Sprite_getResourceType);
	LUA_METHOD("getSpriteFrame", lua_cc_Sprite_getSpriteFrame);
	LUA_METHOD("getTexture", lua_cc_Sprite_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cc_Sprite_getTextureAtlas);
	LUA_METHOD("getTextureRect", lua_cc_Sprite_getTextureRect);
	LUA_METHOD("initWithFile", lua_cc_Sprite_initWithFile);
	LUA_METHOD("initWithSpriteFrame", lua_cc_Sprite_initWithSpriteFrame);
	LUA_METHOD("initWithSpriteFrameName", lua_cc_Sprite_initWithSpriteFrameName);
	LUA_METHOD("initWithTexture", lua_cc_Sprite_initWithTexture);
	LUA_METHOD("isDirty", lua_cc_Sprite_isDirty);
	LUA_METHOD("isFlippedX", lua_cc_Sprite_isFlippedX);
	LUA_METHOD("isFlippedY", lua_cc_Sprite_isFlippedY);
	LUA_METHOD("isFrameDisplayed", lua_cc_Sprite_isFrameDisplayed);
	LUA_METHOD("isStretchEnabled", lua_cc_Sprite_isStretchEnabled);
	LUA_METHOD("isTextureRectRotated", lua_cc_Sprite_isTextureRectRotated);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cc_Sprite_removeAllChildrenWithCleanup);
	LUA_METHOD("setAtlasIndex", lua_cc_Sprite_setAtlasIndex);
	LUA_METHOD("setBatchNode", lua_cc_Sprite_setBatchNode);
	LUA_METHOD("setBlendFunc", lua_cc_Sprite_setBlendFunc);
	LUA_METHOD("setCenterRect", lua_cc_Sprite_setCenterRect);
	LUA_METHOD("setCenterRectNormalized", lua_cc_Sprite_setCenterRectNormalized);
	LUA_METHOD("setDirty", lua_cc_Sprite_setDirty);
	LUA_METHOD("setDisplayFrameWithAnimationName", lua_cc_Sprite_setDisplayFrameWithAnimationName);
	LUA_METHOD("setFlippedX", lua_cc_Sprite_setFlippedX);
	LUA_METHOD("setFlippedY", lua_cc_Sprite_setFlippedY);
	LUA_METHOD("setSpriteFrame", lua_cc_Sprite_setSpriteFrame);
	LUA_METHOD("setStretchEnabled", lua_cc_Sprite_setStretchEnabled);
	LUA_METHOD("setTexture", lua_cc_Sprite_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cc_Sprite_setTextureAtlas);
	LUA_METHOD("setTextureRect", lua_cc_Sprite_setTextureRect);
	LUA_METHOD("setVertexLayout", lua_cc_Sprite_setVertexLayout);
	LUA_METHOD("setVertexRect", lua_cc_Sprite_setVertexRect);
	LUA_METHOD("create", lua_cc_Sprite_create_1);
	LUA_METHOD("createWithSpriteFrame", lua_cc_Sprite_createWithSpriteFrame);
	LUA_METHOD("createWithSpriteFrameName", lua_cc_Sprite_createWithSpriteFrameName);
	LUA_METHOD("createWithTexture", lua_cc_Sprite_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Layer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Layer", "cc.Layer:create");
	LUA_TRY_INVOKE_R(0, &cc::Layer::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccLayer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Layer, "Layer", "cc.Layer",
		cc::Layer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_Layer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_LayerColor_changeHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeHeight");
	LUA_TRY_INVOKE(1, &cc::LayerColor::changeHeight);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerColor_changeWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeWidth");
	LUA_TRY_INVOKE(1, &cc::LayerColor::changeWidth);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerColor_changeWidthAndHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeWidthAndHeight");
	LUA_TRY_INVOKE(2, &cc::LayerColor::changeWidthAndHeight);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_LayerColor_initWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:initWithColor");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::LayerColor::*)(const cc::Color4B&, float, float)>(&cc::LayerColor::initWithColor)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::LayerColor::*)(const cc::Color4B&)>(&cc::LayerColor::initWithColor));
	LUA_INVOKE_FOOTER("1,3");
}
int lua_cc_LayerColor_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.LayerColor", "cc.LayerColor:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::LayerColor>(*)(const cc::Color4B&, float, float)>(&cc::LayerColor::create)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::LayerColor>(*)(const cc::Color4B&)>(&cc::LayerColor::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::LayerColor>(*)()>(&cc::LayerColor::create));
	LUA_SINVOKE_FOOTER("0,1,3");
}
int luaReg_Core_ccLayerColor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::LayerColor, "LayerColor", "cc.LayerColor",
		cc::LayerColor, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("changeHeight", lua_cc_LayerColor_changeHeight);
	LUA_METHOD("changeWidth", lua_cc_LayerColor_changeWidth);
	LUA_METHOD("changeWidthAndHeight", lua_cc_LayerColor_changeWidthAndHeight);
	LUA_METHOD("initWithColor", lua_cc_LayerColor_initWithColor);
	LUA_METHOD("create", lua_cc_LayerColor_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_LayerGradient_getEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getEndColor");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::getEndColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_getEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getEndOpacity");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::getEndOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_getStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getStartColor");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::getStartColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_getStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getStartOpacity");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::getStartOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_getVector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getVector");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::getVector);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_initWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:initWithColor");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cc::LayerGradient::*)(const cc::Color4B&, const cc::Color4B&, const cc::Vec2&)>(&cc::LayerGradient::initWithColor)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::LayerGradient::*)(const cc::Color4B&, const cc::Color4B&)>(&cc::LayerGradient::initWithColor)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_LayerGradient_isCompressedInterpolation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:isCompressedInterpolation");
	LUA_TRY_INVOKE_R(0, &cc::LayerGradient::isCompressedInterpolation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerGradient_setCompressedInterpolation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setCompressedInterpolation");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setCompressedInterpolation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_setEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setEndColor");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setEndColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_setEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setEndOpacity");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setEndOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_setStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setStartColor");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setStartColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_setStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setStartOpacity");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setStartOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_setVector(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setVector");
	LUA_TRY_INVOKE(1, &cc::LayerGradient::setVector);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerGradient_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::LayerGradient>(*)(const cc::Color4B&, const cc::Color4B&, const cc::Vec2&)>(&cc::LayerGradient::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::LayerGradient>(*)(const cc::Color4B&, const cc::Color4B&)>(&cc::LayerGradient::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::LayerGradient>(*)()>(&cc::LayerGradient::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int luaReg_Core_ccLayerGradient(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::LayerGradient, "LayerGradient", "cc.LayerGradient",
		cc::LayerGradient, "cc.LayerColor",
		nullptr, nullptr);
	LUA_METHOD("getEndColor", lua_cc_LayerGradient_getEndColor);
	LUA_METHOD("getEndOpacity", lua_cc_LayerGradient_getEndOpacity);
	LUA_METHOD("getStartColor", lua_cc_LayerGradient_getStartColor);
	LUA_METHOD("getStartOpacity", lua_cc_LayerGradient_getStartOpacity);
	LUA_METHOD("getVector", lua_cc_LayerGradient_getVector);
	LUA_METHOD("initWithColor", lua_cc_LayerGradient_initWithColor);
	LUA_METHOD("isCompressedInterpolation", lua_cc_LayerGradient_isCompressedInterpolation);
	LUA_METHOD("setCompressedInterpolation", lua_cc_LayerGradient_setCompressedInterpolation);
	LUA_METHOD("setEndColor", lua_cc_LayerGradient_setEndColor);
	LUA_METHOD("setEndOpacity", lua_cc_LayerGradient_setEndOpacity);
	LUA_METHOD("setStartColor", lua_cc_LayerGradient_setStartColor);
	LUA_METHOD("setStartOpacity", lua_cc_LayerGradient_setStartOpacity);
	LUA_METHOD("setVector", lua_cc_LayerGradient_setVector);
	LUA_METHOD("create", lua_cc_LayerGradient_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_LayerRadialGradient_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getCenter");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getCenter);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getEndColor");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getEndColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getEndColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getEndColor3B");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getEndColor3B);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getEndOpacity");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getEndOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getExpand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getExpand");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getExpand);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getRadius");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getRadius);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getStartColor");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getStartColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getStartColor3B(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getStartColor3B");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getStartColor3B);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_getStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getStartOpacity");
	LUA_TRY_INVOKE_R(0, &cc::LayerRadialGradient::getStartOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_LayerRadialGradient_initWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:initWithColor");
	LUA_TRY_INVOKE_R(5, &cc::LayerRadialGradient::initWithColor);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_LayerRadialGradient_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setCenter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setCenter");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setCenter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setEndColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setEndColor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::LayerRadialGradient::*)(const cc::Color4B&)>(&cc::LayerRadialGradient::setEndColor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::LayerRadialGradient::*)(const cc::Color3B&)>(&cc::LayerRadialGradient::setEndColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setEndOpacity");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setEndOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setExpand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setExpand");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setExpand);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setRadius");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setRadius);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setStartColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setStartColor");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::LayerRadialGradient::*)(const cc::Color4B&)>(&cc::LayerRadialGradient::setStartColor));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::LayerRadialGradient::*)(const cc::Color3B&)>(&cc::LayerRadialGradient::setStartColor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_setStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setStartOpacity");
	LUA_TRY_INVOKE(1, &cc::LayerRadialGradient::setStartOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerRadialGradient_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cc::IntrusivePtr<cc::LayerRadialGradient>(*)(const cc::Color4B&, const cc::Color4B&, float, const cc::Vec2&, float)>(&cc::LayerRadialGradient::create)));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::LayerRadialGradient>(*)()>(&cc::LayerRadialGradient::create));
	LUA_SINVOKE_FOOTER("0,5");
}
int luaReg_Core_ccLayerRadialGradient(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::LayerRadialGradient, "LayerRadialGradient", "cc.LayerRadialGradient",
		cc::LayerRadialGradient, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cc_LayerRadialGradient_getBlendFunc);
	LUA_METHOD("getCenter", lua_cc_LayerRadialGradient_getCenter);
	LUA_METHOD("getEndColor", lua_cc_LayerRadialGradient_getEndColor);
	LUA_METHOD("getEndColor3B", lua_cc_LayerRadialGradient_getEndColor3B);
	LUA_METHOD("getEndOpacity", lua_cc_LayerRadialGradient_getEndOpacity);
	LUA_METHOD("getExpand", lua_cc_LayerRadialGradient_getExpand);
	LUA_METHOD("getRadius", lua_cc_LayerRadialGradient_getRadius);
	LUA_METHOD("getStartColor", lua_cc_LayerRadialGradient_getStartColor);
	LUA_METHOD("getStartColor3B", lua_cc_LayerRadialGradient_getStartColor3B);
	LUA_METHOD("getStartOpacity", lua_cc_LayerRadialGradient_getStartOpacity);
	LUA_METHOD("initWithColor", lua_cc_LayerRadialGradient_initWithColor);
	LUA_METHOD("setBlendFunc", lua_cc_LayerRadialGradient_setBlendFunc);
	LUA_METHOD("setCenter", lua_cc_LayerRadialGradient_setCenter);
	LUA_METHOD("setEndColor", lua_cc_LayerRadialGradient_setEndColor);
	LUA_METHOD("setEndOpacity", lua_cc_LayerRadialGradient_setEndOpacity);
	LUA_METHOD("setExpand", lua_cc_LayerRadialGradient_setExpand);
	LUA_METHOD("setRadius", lua_cc_LayerRadialGradient_setRadius);
	LUA_METHOD("setStartColor", lua_cc_LayerRadialGradient_setStartColor);
	LUA_METHOD("setStartOpacity", lua_cc_LayerRadialGradient_setStartOpacity);
	LUA_METHOD("create", lua_cc_LayerRadialGradient_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_LayerMultiplex_addLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:addLayer");
	LUA_TRY_INVOKE(1, &cc::LayerMultiplex::addLayer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerMultiplex_initWithArray(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:initWithArray");
	LUA_TRY_INVOKE_R(1, &cc::LayerMultiplex::initWithArray);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_LayerMultiplex_switchTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:switchTo");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::LayerMultiplex::*)(int, bool)>(&cc::LayerMultiplex::switchTo)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::LayerMultiplex::*)(int)>(&cc::LayerMultiplex::switchTo));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_LayerMultiplex_switchToAndReleaseMe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:switchToAndReleaseMe");
	LUA_TRY_INVOKE(1, &cc::LayerMultiplex::switchToAndReleaseMe);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccLayerMultiplex(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::LayerMultiplex, "LayerMultiplex", "cc.LayerMultiplex",
		cc::LayerMultiplex, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addLayer", lua_cc_LayerMultiplex_addLayer);
	LUA_METHOD("initWithArray", lua_cc_LayerMultiplex_initWithArray);
	LUA_METHOD("switchTo", lua_cc_LayerMultiplex_switchTo);
	LUA_METHOD("switchToAndReleaseMe", lua_cc_LayerMultiplex_switchToAndReleaseMe);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItem_activate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:activate");
	LUA_TRY_INVOKE(0, &cc::MenuItem::activate);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItem_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::MenuItem::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItem_isSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:isSelected");
	LUA_TRY_INVOKE_R(0, &cc::MenuItem::isSelected);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItem_rect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:rect");
	LUA_TRY_INVOKE_R(0, &cc::MenuItem::rect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItem_selected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:selected");
	LUA_TRY_INVOKE(0, &cc::MenuItem::selected);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItem_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:setEnabled");
	LUA_TRY_INVOKE(1, &cc::MenuItem::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItem_unselected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:unselected");
	LUA_TRY_INVOKE(0, &cc::MenuItem::unselected);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccMenuItem(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItem, "MenuItem", "cc.MenuItem",
		cc::MenuItem, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("activate", lua_cc_MenuItem_activate);
	LUA_METHOD("isEnabled", lua_cc_MenuItem_isEnabled);
	LUA_METHOD("isSelected", lua_cc_MenuItem_isSelected);
	LUA_METHOD("rect", lua_cc_MenuItem_rect);
	LUA_METHOD("selected", lua_cc_MenuItem_selected);
	LUA_METHOD("setEnabled", lua_cc_MenuItem_setEnabled);
	LUA_METHOD("unselected", lua_cc_MenuItem_unselected);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemLabel_getDisabledColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:getDisabledColor");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemLabel::getDisabledColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemLabel_getLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:getLabel");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemLabel::getLabel);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemLabel_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:getString");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemLabel::getString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemLabel_initWithLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:initWithLabel");
	LUA_TRY_INVOKE_R(2, &cc::MenuItemLabel::initWithLabel);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_MenuItemLabel_setDisabledColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:setDisabledColor");
	LUA_TRY_INVOKE(1, &cc::MenuItemLabel::setDisabledColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemLabel_setLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:setLabel");
	LUA_TRY_INVOKE(1, &cc::MenuItemLabel::setLabel);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemLabel_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:setString");
	LUA_TRY_INVOKE(1, &cc::MenuItemLabel::setString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemLabel_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::MenuItemLabel>(*)(cc::Node*)>(&cc::MenuItemLabel::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemLabel(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemLabel, "MenuItemLabel", "cc.MenuItemLabel",
		cc::MenuItemLabel, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("getDisabledColor", lua_cc_MenuItemLabel_getDisabledColor);
	LUA_METHOD("getLabel", lua_cc_MenuItemLabel_getLabel);
	LUA_METHOD("getString", lua_cc_MenuItemLabel_getString);
	LUA_METHOD("initWithLabel", lua_cc_MenuItemLabel_initWithLabel);
	LUA_METHOD("setDisabledColor", lua_cc_MenuItemLabel_setDisabledColor);
	LUA_METHOD("setLabel", lua_cc_MenuItemLabel_setLabel);
	LUA_METHOD("setString", lua_cc_MenuItemLabel_setString);
	LUA_METHOD("create", lua_cc_MenuItemLabel_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemAtlasFont_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemAtlasFont", "cc.MenuItemAtlasFont:initWithString");
	LUA_TRY_INVOKE_R(6, &cc::MenuItemAtlasFont::initWithString);
	LUA_INVOKE_FOOTER("6");
}
int luaReg_Core_ccMenuItemAtlasFont(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemAtlasFont, "MenuItemAtlasFont", "cc.MenuItemAtlasFont",
		cc::MenuItemAtlasFont, "cc.MenuItemLabel",
		nullptr, nullptr);
	LUA_METHOD("initWithString", lua_cc_MenuItemAtlasFont_initWithString);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemFont_getFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontNameObj");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemFont::getFontNameObj);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemFont_getFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSizeObj");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemFont::getFontSizeObj);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemFont_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:initWithString");
	LUA_TRY_INVOKE_R(2, &cc::MenuItemFont::initWithString);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_MenuItemFont_setFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontNameObj");
	LUA_TRY_INVOKE(1, &cc::MenuItemFont::setFontNameObj);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemFont_setFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSizeObj");
	LUA_TRY_INVOKE(1, &cc::MenuItemFont::setFontSizeObj);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemFont_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::MenuItemFont>(*)(std::string_view)>(&cc::MenuItemFont::create));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_MenuItemFont_getFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontName");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemFont::getFontName);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_MenuItemFont_getFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSize");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemFont::getFontSize);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_MenuItemFont_setFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontName");
	LUA_TRY_INVOKE(1, &cc::MenuItemFont::setFontName);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_MenuItemFont_setFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSize");
	LUA_TRY_INVOKE(1, &cc::MenuItemFont::setFontSize);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemFont(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemFont, "MenuItemFont", "cc.MenuItemFont",
		cc::MenuItemFont, "cc.MenuItemLabel",
		nullptr, nullptr);
	LUA_METHOD("getFontNameObj", lua_cc_MenuItemFont_getFontNameObj);
	LUA_METHOD("getFontSizeObj", lua_cc_MenuItemFont_getFontSizeObj);
	LUA_METHOD("initWithString", lua_cc_MenuItemFont_initWithString);
	LUA_METHOD("setFontNameObj", lua_cc_MenuItemFont_setFontNameObj);
	LUA_METHOD("setFontSizeObj", lua_cc_MenuItemFont_setFontSizeObj);
	LUA_METHOD("create", lua_cc_MenuItemFont_create_1);
	LUA_METHOD("getFontName", lua_cc_MenuItemFont_getFontName);
	LUA_METHOD("getFontSize", lua_cc_MenuItemFont_getFontSize);
	LUA_METHOD("setFontName", lua_cc_MenuItemFont_setFontName);
	LUA_METHOD("setFontSize", lua_cc_MenuItemFont_setFontSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemSprite_getDisabledImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getDisabledImage");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemSprite::getDisabledImage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemSprite_getNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getNormalImage");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemSprite::getNormalImage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemSprite_getSelectedImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:getSelectedImage");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemSprite::getSelectedImage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemSprite_initWithNormalSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:initWithNormalSprite");
	LUA_TRY_INVOKE_R(4, &cc::MenuItemSprite::initWithNormalSprite);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_MenuItemSprite_setDisabledImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setDisabledImage");
	LUA_TRY_INVOKE(1, &cc::MenuItemSprite::setDisabledImage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemSprite_setNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setNormalImage");
	LUA_TRY_INVOKE(1, &cc::MenuItemSprite::setNormalImage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemSprite_setSelectedImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:setSelectedImage");
	LUA_TRY_INVOKE(1, &cc::MenuItemSprite::setSelectedImage);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemSprite_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemSprite", "cc.MenuItemSprite:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::MenuItemSprite>(*)(cc::Node*, cc::Node*, cc::Node*)>(&cc::MenuItemSprite::create)));
	LUA_TRY_INVOKE_R(2, ([](cc::Node* arg0,cc::Node* arg1){{return cc::MenuItemSprite::create(arg0,arg1);}}));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccMenuItemSprite(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemSprite, "MenuItemSprite", "cc.MenuItemSprite",
		cc::MenuItemSprite, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("getDisabledImage", lua_cc_MenuItemSprite_getDisabledImage);
	LUA_METHOD("getNormalImage", lua_cc_MenuItemSprite_getNormalImage);
	LUA_METHOD("getSelectedImage", lua_cc_MenuItemSprite_getSelectedImage);
	LUA_METHOD("initWithNormalSprite", lua_cc_MenuItemSprite_initWithNormalSprite);
	LUA_METHOD("setDisabledImage", lua_cc_MenuItemSprite_setDisabledImage);
	LUA_METHOD("setNormalImage", lua_cc_MenuItemSprite_setNormalImage);
	LUA_METHOD("setSelectedImage", lua_cc_MenuItemSprite_setSelectedImage);
	LUA_METHOD("create", lua_cc_MenuItemSprite_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemImage_init_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::MenuItemImage::*)()>(&cc::MenuItemImage::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemImage_initWithNormalImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:initWithNormalImage");
	LUA_TRY_INVOKE_R(4, &cc::MenuItemImage::initWithNormalImage);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_MenuItemImage_setDisabledSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setDisabledSpriteFrame");
	LUA_TRY_INVOKE(1, &cc::MenuItemImage::setDisabledSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemImage_setNormalSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setNormalSpriteFrame");
	LUA_TRY_INVOKE(1, &cc::MenuItemImage::setNormalSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemImage_setSelectedSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:setSelectedSpriteFrame");
	LUA_TRY_INVOKE(1, &cc::MenuItemImage::setSelectedSpriteFrame);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemImage_create_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemImage", "cc.MenuItemImage:create");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::MenuItemImage>(*)()>(&cc::MenuItemImage::create));
	LUA_TRY_INVOKE_R(2, (static_cast<cc::IntrusivePtr<cc::MenuItemImage>(*)(std::string_view, std::string_view)>(&cc::MenuItemImage::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cc::IntrusivePtr<cc::MenuItemImage>(*)(std::string_view, std::string_view, std::string_view)>(&cc::MenuItemImage::create)));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int luaReg_Core_ccMenuItemImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemImage, "MenuItemImage", "cc.MenuItemImage",
		cc::MenuItemImage, "cc.MenuItemSprite",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cc_MenuItemImage_init_1);
	LUA_METHOD("initWithNormalImage", lua_cc_MenuItemImage_initWithNormalImage);
	LUA_METHOD("setDisabledSpriteFrame", lua_cc_MenuItemImage_setDisabledSpriteFrame);
	LUA_METHOD("setNormalSpriteFrame", lua_cc_MenuItemImage_setNormalSpriteFrame);
	LUA_METHOD("setSelectedSpriteFrame", lua_cc_MenuItemImage_setSelectedSpriteFrame);
	LUA_METHOD("create", lua_cc_MenuItemImage_create_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MenuItemToggle_addSubItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:addSubItem");
	LUA_TRY_INVOKE(1, &cc::MenuItemToggle::addSubItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemToggle_getSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:getSelectedIndex");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemToggle::getSelectedIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemToggle_getSelectedItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:getSelectedItem");
	LUA_TRY_INVOKE_R(0, &cc::MenuItemToggle::getSelectedItem);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MenuItemToggle_initWithItem(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:initWithItem");
	LUA_TRY_INVOKE_R(1, &cc::MenuItemToggle::initWithItem);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemToggle_setSelectedIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:setSelectedIndex");
	LUA_TRY_INVOKE(1, &cc::MenuItemToggle::setSelectedIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MenuItemToggle_setSubItems(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemToggle", "cc.MenuItemToggle:setSubItems");
	LUA_TRY_INVOKE(1, &cc::MenuItemToggle::setSubItems);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemToggle(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MenuItemToggle, "MenuItemToggle", "cc.MenuItemToggle",
		cc::MenuItemToggle, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("addSubItem", lua_cc_MenuItemToggle_addSubItem);
	LUA_METHOD("getSelectedIndex", lua_cc_MenuItemToggle_getSelectedIndex);
	LUA_METHOD("getSelectedItem", lua_cc_MenuItemToggle_getSelectedItem);
	LUA_METHOD("initWithItem", lua_cc_MenuItemToggle_initWithItem);
	LUA_METHOD("setSelectedIndex", lua_cc_MenuItemToggle_setSelectedIndex);
	LUA_METHOD("setSubItems", lua_cc_MenuItemToggle_setSubItems);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Menu_alignItemsHorizontally(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsHorizontally");
	LUA_TRY_INVOKE(0, &cc::Menu::alignItemsHorizontally);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Menu_alignItemsHorizontallyWithPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsHorizontallyWithPadding");
	LUA_TRY_INVOKE(1, &cc::Menu::alignItemsHorizontallyWithPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Menu_alignItemsVertically(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsVertically");
	LUA_TRY_INVOKE(0, &cc::Menu::alignItemsVertically);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Menu_alignItemsVerticallyWithPadding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:alignItemsVerticallyWithPadding");
	LUA_TRY_INVOKE(1, &cc::Menu::alignItemsVerticallyWithPadding);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Menu_initWithArray(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:initWithArray");
	LUA_TRY_INVOKE_R(1, &cc::Menu::initWithArray);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Menu_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Menu::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Menu_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Menu", "cc.Menu:setEnabled");
	LUA_TRY_INVOKE(1, &cc::Menu::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenu(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Menu, "Menu", "cc.Menu",
		cc::Menu, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("alignItemsHorizontally", lua_cc_Menu_alignItemsHorizontally);
	LUA_METHOD("alignItemsHorizontallyWithPadding", lua_cc_Menu_alignItemsHorizontallyWithPadding);
	LUA_METHOD("alignItemsVertically", lua_cc_Menu_alignItemsVertically);
	LUA_METHOD("alignItemsVerticallyWithPadding", lua_cc_Menu_alignItemsVerticallyWithPadding);
	LUA_METHOD("initWithArray", lua_cc_Menu_initWithArray);
	LUA_METHOD("isEnabled", lua_cc_Menu_isEnabled);
	LUA_METHOD("setEnabled", lua_cc_Menu_setEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MotionStreak_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getStroke");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak::getStroke);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::MotionStreak::*)(float, float, float, const cc::Color3B&, cc::Texture2D*)>(&cc::MotionStreak::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::MotionStreak::*)(float, float, float, const cc::Color3B&, std::string_view)>(&cc::MotionStreak::initWithFade)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_MotionStreak_isFastMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:isFastMode");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak::isFastMode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak::isStartingPositionInitialized);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:reset");
	LUA_TRY_INVOKE(0, &cc::MotionStreak::reset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_setFastMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setFastMode");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::setFastMode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::setStartingPositionInitialized);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setStroke");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::setStroke);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:setTexture");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:tintWithColor");
	LUA_TRY_INVOKE(1, &cc::MotionStreak::tintWithColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak", "cc.MotionStreak:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::MotionStreak>(*)(float, float, float, const cc::Color3B&, cc::Texture2D*)>(&cc::MotionStreak::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::MotionStreak>(*)(float, float, float, const cc::Color3B&, std::string_view)>(&cc::MotionStreak::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MotionStreak, "MotionStreak", "cc.MotionStreak",
		cc::MotionStreak, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cc_MotionStreak_getBlendFunc);
	LUA_METHOD("getStroke", lua_cc_MotionStreak_getStroke);
	LUA_METHOD("getTexture", lua_cc_MotionStreak_getTexture);
	LUA_METHOD("initWithFade", lua_cc_MotionStreak_initWithFade);
	LUA_METHOD("isFastMode", lua_cc_MotionStreak_isFastMode);
	LUA_METHOD("isStartingPositionInitialized", lua_cc_MotionStreak_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cc_MotionStreak_reset);
	LUA_METHOD("setBlendFunc", lua_cc_MotionStreak_setBlendFunc);
	LUA_METHOD("setFastMode", lua_cc_MotionStreak_setFastMode);
	LUA_METHOD("setStartingPositionInitialized", lua_cc_MotionStreak_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cc_MotionStreak_setStroke);
	LUA_METHOD("setTexture", lua_cc_MotionStreak_setTexture);
	LUA_METHOD("tintWithColor", lua_cc_MotionStreak_tintWithColor);
	LUA_METHOD("create", lua_cc_MotionStreak_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_NodeGrid_getGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:getGrid");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::GridBase*(cc::NodeGrid::*)()const>(&cc::NodeGrid::getGrid));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::GridBase*(cc::NodeGrid::*)()>(&cc::NodeGrid::getGrid));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NodeGrid_getGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:getGridRect");
	LUA_TRY_INVOKE_R(0, &cc::NodeGrid::getGridRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_NodeGrid_setGrid(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setGrid");
	LUA_TRY_INVOKE(1, &cc::NodeGrid::setGrid);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NodeGrid_setGridRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setGridRect");
	LUA_TRY_INVOKE(1, &cc::NodeGrid::setGridRect);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NodeGrid_setTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:setTarget");
	LUA_TRY_INVOKE(1, &cc::NodeGrid::setTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_NodeGrid_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.NodeGrid", "cc.NodeGrid:create");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::NodeGrid>(*)(const cc::Rect&)>(&cc::NodeGrid::create));
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::NodeGrid>(*)()>(&cc::NodeGrid::create));
	LUA_SINVOKE_FOOTER("0,1");
}
int luaReg_Core_ccNodeGrid(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::NodeGrid, "NodeGrid", "cc.NodeGrid",
		cc::NodeGrid, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getGrid", lua_cc_NodeGrid_getGrid);
	LUA_METHOD("getGridRect", lua_cc_NodeGrid_getGridRect);
	LUA_METHOD("setGrid", lua_cc_NodeGrid_setGrid);
	LUA_METHOD("setGridRect", lua_cc_NodeGrid_setGridRect);
	LUA_METHOD("setTarget", lua_cc_NodeGrid_setTarget);
	LUA_METHOD("create", lua_cc_NodeGrid_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
