#include "cclua_base_auto.hpp"
#include "lua_conversion/lua_conversion.hpp"
#include "cocos2d.h"
#include "2d/ProtectedNode.h"
#include "base/AsyncTaskPool.h"
#include "scripting/lua-bindings/manual/ComponentLua.h"
#include "renderer/Renderer.h"
#include "renderer/PipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "renderer/backend/ShaderCache.h"
#include "renderer/backend/Buffer.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "physics3d/Physics3DWorld.h"
#endif
#if CC_USE_NAVMESH
#include "navmesh/NavMesh.h"
#endif

int lua_cc_Renderer_addCallbackCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addCallbackCommand");
	if (argc == 2 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(2, &cc::Renderer::addCallbackCommand);
	}
	if (argc == 1 && !ok && lua_isnil(lua_S, 2)) { arg_cur = 1; } else {
	LUA_TRY_INVOKE(1, ([](cc::Renderer* obj,std::function<void()> arg0){{return obj->addCallbackCommand(std::move(arg0));}}));
	}
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Renderer_addCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addCommand");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::Renderer::*)(cc::RenderCommand*, int)>(&cc::Renderer::addCommand)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Renderer::*)(cc::RenderCommand*)>(&cc::Renderer::addCommand));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Renderer_addDrawnBatches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addDrawnBatches");
	LUA_TRY_INVOKE(1, &cc::Renderer::addDrawnBatches);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_addDrawnVertices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:addDrawnVertices");
	LUA_TRY_INVOKE(1, &cc::Renderer::addDrawnVertices);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_beginRenderPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:beginRenderPass");
	LUA_TRY_INVOKE(0, &cc::Renderer::beginRenderPass);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_checkVisibility(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:checkVisibility");
	LUA_TRY_INVOKE_R(2, &cc::Renderer::checkVisibility);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Renderer_clean(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clean");
	LUA_TRY_INVOKE(0, &cc::Renderer::clean);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_clear(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clear");
	LUA_TRY_INVOKE(5, &cc::Renderer::clear);
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_Renderer_clearDrawStats(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:clearDrawStats");
	LUA_TRY_INVOKE(0, &cc::Renderer::clearDrawStats);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_createRenderQueue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:createRenderQueue");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::createRenderQueue);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_endRenderPass(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:endRenderPass");
	LUA_TRY_INVOKE(0, &cc::Renderer::endRenderPass);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getClearColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearColor");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getClearColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getClearDepth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearDepth");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getClearDepth);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getClearFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearFlag");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getClearFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getClearStencil(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getClearStencil");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getClearStencil);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getCullMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getCullMode");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getCullMode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDefaultRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDefaultRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDefaultRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDepthCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthCompareFunction");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDepthCompareFunction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDepthStencilDesc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthStencilDesc");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDepthStencilDesc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDepthTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthTest");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDepthTest);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDepthWrite");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDepthWrite);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDrawnBatches(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDrawnBatches");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDrawnBatches);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getDrawnVertices(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getDrawnVertices");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getDrawnVertices);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getNextGroupCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getNextGroupCommand");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getNextGroupCommand);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getOffscreenRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getOffscreenRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getOffscreenRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getRenderTargetFlag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getRenderTargetFlag");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getRenderTargetFlag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getScissorRect");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getScissorRect);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getScissorTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getScissorTest");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getScissorTest);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilCompareFunction");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilCompareFunction);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilDepthPassOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilDepthPassOperation");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilDepthPassOperation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilFailureOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilFailureOperation");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilFailureOperation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilPassDepthFailureOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilPassDepthFailureOperation");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilPassDepthFailureOperation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilReadMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilReadMask");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilReadMask);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilReferenceValue(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilReferenceValue");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilReferenceValue);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilTest");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilTest);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getStencilWriteMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getStencilWriteMask");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getStencilWriteMask);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getViewport(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getViewport");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getViewport);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_getWinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:getWinding");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::getWinding);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:init");
	LUA_TRY_INVOKE(0, &cc::Renderer::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_nextCallbackCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:nextCallbackCommand");
	LUA_TRY_INVOKE_R(0, &cc::Renderer::nextCallbackCommand);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_popGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:popGroup");
	LUA_TRY_INVOKE(0, &cc::Renderer::popGroup);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_pushGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:pushGroup");
	LUA_TRY_INVOKE(1, &cc::Renderer::pushGroup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_render(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:render");
	LUA_TRY_INVOKE(0, &cc::Renderer::render);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Renderer_setCullMode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setCullMode");
	LUA_TRY_INVOKE(1, &cc::Renderer::setCullMode);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setDepthCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthCompareFunction");
	LUA_TRY_INVOKE(1, &cc::Renderer::setDepthCompareFunction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setDepthStencilDesc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthStencilDesc");
	LUA_TRY_INVOKE(1, &cc::Renderer::setDepthStencilDesc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setDepthTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthTest");
	LUA_TRY_INVOKE(1, &cc::Renderer::setDepthTest);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setDepthWrite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setDepthWrite");
	LUA_TRY_INVOKE(1, &cc::Renderer::setDepthWrite);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setRenderTarget");
	LUA_TRY_INVOKE(1, &cc::Renderer::setRenderTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setScissorRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setScissorRect");
	LUA_TRY_INVOKE(4, &cc::Renderer::setScissorRect);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Renderer_setScissorTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setScissorTest");
	LUA_TRY_INVOKE(1, &cc::Renderer::setScissorTest);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setStencilCompareFunction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilCompareFunction");
	LUA_TRY_INVOKE(3, &cc::Renderer::setStencilCompareFunction);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_Renderer_setStencilOperation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilOperation");
	LUA_TRY_INVOKE(3, &cc::Renderer::setStencilOperation);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_Renderer_setStencilTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilTest");
	LUA_TRY_INVOKE(1, &cc::Renderer::setStencilTest);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setStencilWriteMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setStencilWriteMask");
	LUA_TRY_INVOKE(1, &cc::Renderer::setStencilWriteMask);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Renderer_setViewPort(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setViewPort");
	LUA_TRY_INVOKE(4, &cc::Renderer::setViewPort);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_Renderer_setWinding(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Renderer", "cc.Renderer:setWinding");
	LUA_TRY_INVOKE(1, &cc::Renderer::setWinding);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccRenderer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Renderer, "Renderer", "cc.Renderer",
		cc::Renderer, "",
		nullptr, nullptr);
	LUA_METHOD("addCallbackCommand", lua_cc_Renderer_addCallbackCommand);
	LUA_METHOD("addCommand", lua_cc_Renderer_addCommand);
	LUA_METHOD("addDrawnBatches", lua_cc_Renderer_addDrawnBatches);
	LUA_METHOD("addDrawnVertices", lua_cc_Renderer_addDrawnVertices);
	LUA_METHOD("beginRenderPass", lua_cc_Renderer_beginRenderPass);
	LUA_METHOD("checkVisibility", lua_cc_Renderer_checkVisibility);
	LUA_METHOD("clean", lua_cc_Renderer_clean);
	LUA_METHOD("clear", lua_cc_Renderer_clear);
	LUA_METHOD("clearDrawStats", lua_cc_Renderer_clearDrawStats);
	LUA_METHOD("createRenderQueue", lua_cc_Renderer_createRenderQueue);
	LUA_METHOD("endRenderPass", lua_cc_Renderer_endRenderPass);
	LUA_METHOD("getClearColor", lua_cc_Renderer_getClearColor);
	LUA_METHOD("getClearDepth", lua_cc_Renderer_getClearDepth);
	LUA_METHOD("getClearFlag", lua_cc_Renderer_getClearFlag);
	LUA_METHOD("getClearStencil", lua_cc_Renderer_getClearStencil);
	LUA_METHOD("getCullMode", lua_cc_Renderer_getCullMode);
	LUA_METHOD("getDefaultRenderTarget", lua_cc_Renderer_getDefaultRenderTarget);
	LUA_METHOD("getDepthCompareFunction", lua_cc_Renderer_getDepthCompareFunction);
	LUA_METHOD("getDepthStencilDesc", lua_cc_Renderer_getDepthStencilDesc);
	LUA_METHOD("getDepthTest", lua_cc_Renderer_getDepthTest);
	LUA_METHOD("getDepthWrite", lua_cc_Renderer_getDepthWrite);
	LUA_METHOD("getDrawnBatches", lua_cc_Renderer_getDrawnBatches);
	LUA_METHOD("getDrawnVertices", lua_cc_Renderer_getDrawnVertices);
	LUA_METHOD("getNextGroupCommand", lua_cc_Renderer_getNextGroupCommand);
	LUA_METHOD("getOffscreenRenderTarget", lua_cc_Renderer_getOffscreenRenderTarget);
	LUA_METHOD("getRenderTarget", lua_cc_Renderer_getRenderTarget);
	LUA_METHOD("getRenderTargetFlag", lua_cc_Renderer_getRenderTargetFlag);
	LUA_METHOD("getScissorRect", lua_cc_Renderer_getScissorRect);
	LUA_METHOD("getScissorTest", lua_cc_Renderer_getScissorTest);
	LUA_METHOD("getStencilCompareFunction", lua_cc_Renderer_getStencilCompareFunction);
	LUA_METHOD("getStencilDepthPassOperation", lua_cc_Renderer_getStencilDepthPassOperation);
	LUA_METHOD("getStencilFailureOperation", lua_cc_Renderer_getStencilFailureOperation);
	LUA_METHOD("getStencilPassDepthFailureOperation", lua_cc_Renderer_getStencilPassDepthFailureOperation);
	LUA_METHOD("getStencilReadMask", lua_cc_Renderer_getStencilReadMask);
	LUA_METHOD("getStencilReferenceValue", lua_cc_Renderer_getStencilReferenceValue);
	LUA_METHOD("getStencilTest", lua_cc_Renderer_getStencilTest);
	LUA_METHOD("getStencilWriteMask", lua_cc_Renderer_getStencilWriteMask);
	LUA_METHOD("getViewport", lua_cc_Renderer_getViewport);
	LUA_METHOD("getWinding", lua_cc_Renderer_getWinding);
	LUA_METHOD("init", lua_cc_Renderer_init);
	LUA_METHOD("nextCallbackCommand", lua_cc_Renderer_nextCallbackCommand);
	LUA_METHOD("popGroup", lua_cc_Renderer_popGroup);
	LUA_METHOD("pushGroup", lua_cc_Renderer_pushGroup);
	LUA_METHOD("render", lua_cc_Renderer_render);
	LUA_METHOD("setCullMode", lua_cc_Renderer_setCullMode);
	LUA_METHOD("setDepthCompareFunction", lua_cc_Renderer_setDepthCompareFunction);
	LUA_METHOD("setDepthStencilDesc", lua_cc_Renderer_setDepthStencilDesc);
	LUA_METHOD("setDepthTest", lua_cc_Renderer_setDepthTest);
	LUA_METHOD("setDepthWrite", lua_cc_Renderer_setDepthWrite);
	LUA_METHOD("setRenderTarget", lua_cc_Renderer_setRenderTarget);
	LUA_METHOD("setScissorRect", lua_cc_Renderer_setScissorRect);
	LUA_METHOD("setScissorTest", lua_cc_Renderer_setScissorTest);
	LUA_METHOD("setStencilCompareFunction", lua_cc_Renderer_setStencilCompareFunction);
	LUA_METHOD("setStencilOperation", lua_cc_Renderer_setStencilOperation);
	LUA_METHOD("setStencilTest", lua_cc_Renderer_setStencilTest);
	LUA_METHOD("setStencilWriteMask", lua_cc_Renderer_setStencilWriteMask);
	LUA_METHOD("setViewPort", lua_cc_Renderer_setViewPort);
	LUA_METHOD("setWinding", lua_cc_Renderer_setWinding);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TextureCache_addImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:addImage");
	LUA_TRY_INVOKE_R(3, (static_cast<cc::Texture2D*(cc::TextureCache::*)(cc::Image*, std::string_view, cc::PixelFormat)>(&cc::TextureCache::addImage)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::Texture2D*(cc::TextureCache::*)(cc::Image*, std::string_view)>(&cc::TextureCache::addImage)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cc::Texture2D*(cc::TextureCache::*)(std::string_view, cc::PixelFormat)>(&cc::TextureCache::addImage)));
	LUA_TRY_INVOKE_R(1, static_cast<cc::Texture2D*(cc::TextureCache::*)(std::string_view)>(&cc::TextureCache::addImage));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_TextureCache_addImageAsync_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:addImageAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::TextureCache::*)(std::string_view, const std::function<void(cc::Texture2D*)>&)>(&cc::TextureCache::addImageAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TextureCache_getCachedTextureInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getCachedTextureInfo");
	LUA_TRY_INVOKE_R(0, &cc::TextureCache::getCachedTextureInfo);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_getDescription(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getDescription");
	LUA_TRY_INVOKE_R(0, &cc::TextureCache::getDescription);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_getTextureFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getTextureFilePath");
	LUA_TRY_INVOKE_R(1, &cc::TextureCache::getTextureFilePath);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_getTextureForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getTextureForKey");
	LUA_TRY_INVOKE_R(1, &cc::TextureCache::getTextureForKey);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_reloadTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:reloadTexture");
	LUA_TRY_INVOKE_R(1, &cc::TextureCache::reloadTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_removeAllTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeAllTextures");
	LUA_TRY_INVOKE(0, &cc::TextureCache::removeAllTextures);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_removeTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeTexture");
	LUA_TRY_INVOKE(1, &cc::TextureCache::removeTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_removeTextureForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeTextureForKey");
	LUA_TRY_INVOKE(1, &cc::TextureCache::removeTextureForKey);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_removeUnusedTextures(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:removeUnusedTextures");
	LUA_TRY_INVOKE(0, &cc::TextureCache::removeUnusedTextures);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_renameTextureWithKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:renameTextureWithKey");
	LUA_TRY_INVOKE(2, &cc::TextureCache::renameTextureWithKey);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TextureCache_unbindAllImageAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:unbindAllImageAsync");
	LUA_TRY_INVOKE(0, &cc::TextureCache::unbindAllImageAsync);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_unbindImageAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:unbindImageAsync");
	LUA_TRY_INVOKE(1, &cc::TextureCache::unbindImageAsync);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TextureCache_waitForQuit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TextureCache", "cc.TextureCache:waitForQuit");
	LUA_TRY_INVOKE(0, &cc::TextureCache::waitForQuit);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TextureCache_getETC1AlphaFileSuffix(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCache", "cc.TextureCache:getETC1AlphaFileSuffix");
	LUA_TRY_INVOKE_R(0, &cc::TextureCache::getETC1AlphaFileSuffix);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_TextureCache_setETC1AlphaFileSuffix(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TextureCache", "cc.TextureCache:setETC1AlphaFileSuffix");
	LUA_TRY_INVOKE(1, &cc::TextureCache::setETC1AlphaFileSuffix);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTextureCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TextureCache, "TextureCache", "cc.TextureCache",
		cc::TextureCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addImage", lua_cc_TextureCache_addImage);
	LUA_METHOD("addImageAsync", lua_cc_TextureCache_addImageAsync_1);
	LUA_METHOD("getCachedTextureInfo", lua_cc_TextureCache_getCachedTextureInfo);
	LUA_METHOD("getDescription", lua_cc_TextureCache_getDescription);
	LUA_METHOD("getTextureFilePath", lua_cc_TextureCache_getTextureFilePath);
	LUA_METHOD("getTextureForKey", lua_cc_TextureCache_getTextureForKey);
	LUA_METHOD("reloadTexture", lua_cc_TextureCache_reloadTexture);
	LUA_METHOD("removeAllTextures", lua_cc_TextureCache_removeAllTextures);
	LUA_METHOD("removeTexture", lua_cc_TextureCache_removeTexture);
	LUA_METHOD("removeTextureForKey", lua_cc_TextureCache_removeTextureForKey);
	LUA_METHOD("removeUnusedTextures", lua_cc_TextureCache_removeUnusedTextures);
	LUA_METHOD("renameTextureWithKey", lua_cc_TextureCache_renameTextureWithKey);
	LUA_METHOD("unbindAllImageAsync", lua_cc_TextureCache_unbindAllImageAsync);
	LUA_METHOD("unbindImageAsync", lua_cc_TextureCache_unbindImageAsync);
	LUA_METHOD("waitForQuit", lua_cc_TextureCache_waitForQuit);
	LUA_METHOD("getETC1AlphaFileSuffix", lua_cc_TextureCache_getETC1AlphaFileSuffix);
	LUA_METHOD("setETC1AlphaFileSuffix", lua_cc_TextureCache_setETC1AlphaFileSuffix);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Device_getDPI(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:getDPI");
	LUA_TRY_INVOKE_R(0, &cc::Device::getDPI);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Device_setAccelerometerEnabled(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setAccelerometerEnabled");
	LUA_TRY_INVOKE(1, &cc::Device::setAccelerometerEnabled);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Device_setAccelerometerInterval(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setAccelerometerInterval");
	LUA_TRY_INVOKE(1, &cc::Device::setAccelerometerInterval);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Device_setKeepScreenOn(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:setKeepScreenOn");
	LUA_TRY_INVOKE(1, &cc::Device::setKeepScreenOn);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Device_vibrate(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Device", "cc.Device:vibrate");
	LUA_TRY_INVOKE(1, &cc::Device::vibrate);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDevice(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Device, "Device", "cc.Device",
		cc::Device, "",
		nullptr, nullptr);
	LUA_METHOD("getDPI", lua_cc_Device_getDPI);
	LUA_METHOD("setAccelerometerEnabled", lua_cc_Device_setAccelerometerEnabled);
	LUA_METHOD("setAccelerometerInterval", lua_cc_Device_setAccelerometerInterval);
	LUA_METHOD("setKeepScreenOn", lua_cc_Device_setKeepScreenOn);
	LUA_METHOD("vibrate", lua_cc_Device_vibrate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Application_getCurrentLanguage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getCurrentLanguage");
	LUA_TRY_INVOKE_R(0, &cc::Application::getCurrentLanguage);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Application_getCurrentLanguageCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getCurrentLanguageCode");
	LUA_TRY_INVOKE_R(0, &cc::Application::getCurrentLanguageCode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Application_getTargetPlatform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getTargetPlatform");
	LUA_TRY_INVOKE_R(0, &cc::Application::getTargetPlatform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Application_getVersion(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:getVersion");
	LUA_TRY_INVOKE_R(0, &cc::Application::getVersion);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Application_openURL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:openURL");
	LUA_TRY_INVOKE_R(1, &cc::Application::openURL);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Application_setAnimationInterval(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Application", "cc.Application:setAnimationInterval");
	LUA_TRY_INVOKE(1, &cc::Application::setAnimationInterval);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Application_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Application", "cc.Application:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::Application::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccApplication(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Application, "Application", "cc.Application",
		cc::Application, "",
		nullptr, nullptr);
	LUA_METHOD("getCurrentLanguage", lua_cc_Application_getCurrentLanguage);
	LUA_METHOD("getCurrentLanguageCode", lua_cc_Application_getCurrentLanguageCode);
	LUA_METHOD("getTargetPlatform", lua_cc_Application_getTargetPlatform);
	LUA_METHOD("getVersion", lua_cc_Application_getVersion);
	LUA_METHOD("openURL", lua_cc_Application_openURL);
	LUA_METHOD("setAnimationInterval", lua_cc_Application_setAnimationInterval);
	LUA_METHOD("getInstance", lua_cc_Application_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_GLViewImpl_createWithFullScreen_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.GLViewImpl", "cc.GLViewImpl:createWithFullScreen");
	LUA_TRY_INVOKE_R(1, static_cast<cc::IntrusivePtr<cc::GLViewImpl>(*)(std::string_view)>(&cc::GLViewImpl::createWithFullScreen));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccGLViewImpl(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::GLViewImpl, "GLViewImpl", "cc.GLViewImpl",
		cc::GLViewImpl, "cc.GLView",
		nullptr, nullptr);
	LUA_METHOD("createWithFullScreen", lua_cc_GLViewImpl_createWithFullScreen_1);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_AnimationCache_addAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimation");
	LUA_TRY_INVOKE(2, &cc::AnimationCache::addAnimation);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_AnimationCache_addAnimations(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimations");
	LUA_TRY_INVOKE(1, &cc::AnimationCache::addAnimationsWithFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationCache_addAnimationsWithDictionary(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:addAnimationsWithDictionary");
	LUA_TRY_INVOKE(2, &cc::AnimationCache::addAnimationsWithDictionary);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_AnimationCache_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getAnimation");
	LUA_TRY_INVOKE_R(1, &cc::AnimationCache::getAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationCache_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:init");
	LUA_TRY_INVOKE_R(0, &cc::AnimationCache::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_AnimationCache_removeAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:removeAnimation");
	LUA_TRY_INVOKE(1, &cc::AnimationCache::removeAnimation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_AnimationCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationCache", "cc.AnimationCache:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::AnimationCache::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccAnimationCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::AnimationCache, "AnimationCache", "cc.AnimationCache",
		cc::AnimationCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addAnimation", lua_cc_AnimationCache_addAnimation);
	LUA_METHOD("addAnimations", lua_cc_AnimationCache_addAnimations);
	LUA_METHOD("addAnimationsWithDictionary", lua_cc_AnimationCache_addAnimationsWithDictionary);
	LUA_METHOD("getAnimation", lua_cc_AnimationCache_getAnimation);
	LUA_METHOD("init", lua_cc_AnimationCache_init);
	LUA_METHOD("removeAnimation", lua_cc_AnimationCache_removeAnimation);
	LUA_METHOD("getInstance", lua_cc_AnimationCache_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_SpriteBatchNode_addSpriteWithoutQuad(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:addSpriteWithoutQuad");
	LUA_TRY_INVOKE_R(3, &cc::SpriteBatchNode::addSpriteWithoutQuad);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_SpriteBatchNode_appendChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:appendChild");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::appendChild);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_atlasIndexForChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:atlasIndexForChild");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::atlasIndexForChild);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SpriteBatchNode_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::SpriteBatchNode::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteBatchNode_getDescendants(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getDescendants");
	LUA_TRY_INVOKE_R(0, &cc::SpriteBatchNode::getDescendants);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteBatchNode_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::SpriteBatchNode::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteBatchNode_getTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:getTextureAtlas");
	LUA_TRY_INVOKE_R(0, &cc::SpriteBatchNode::getTextureAtlas);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteBatchNode_highestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:highestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, &cc::SpriteBatchNode::highestAtlasIndexInChild);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_increaseAtlasCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:increaseAtlasCapacity");
	LUA_TRY_INVOKE(0, &cc::SpriteBatchNode::increaseAtlasCapacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_SpriteBatchNode_initWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithFile");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::initWithFile);
	LUA_TRY_INVOKE_R(1, ([](cc::SpriteBatchNode* obj,std::string_view arg0){{return obj->initWithFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_SpriteBatchNode_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:initWithTexture");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::initWithTexture);
	LUA_TRY_INVOKE_R(1, ([](cc::SpriteBatchNode* obj,cc::Texture2D* arg0){{return obj->initWithTexture(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_SpriteBatchNode_insertQuadFromSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:insertQuadFromSprite");
	LUA_TRY_INVOKE(2, &cc::SpriteBatchNode::insertQuadFromSprite);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SpriteBatchNode_lowestAtlasIndexInChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:lowestAtlasIndexInChild");
	LUA_TRY_INVOKE_R(1, &cc::SpriteBatchNode::lowestAtlasIndexInChild);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_rebuildIndexInOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:rebuildIndexInOrder");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::rebuildIndexInOrder);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SpriteBatchNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::removeAllChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_removeChildAtIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeChildAtIndex");
	LUA_TRY_INVOKE(2, &cc::SpriteBatchNode::removeChildAtIndex);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_SpriteBatchNode_removeSpriteFromAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:removeSpriteFromAtlas");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::removeSpriteFromAtlas);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_reorderBatch(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reorderBatch");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::reorderBatch);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_reserveCapacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:reserveCapacity");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::reserveCapacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTexture");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_setTextureAtlas(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:setTextureAtlas");
	LUA_TRY_INVOKE(1, &cc::SpriteBatchNode::setTextureAtlas);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_SpriteBatchNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:create");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::create);
	LUA_TRY_INVOKE_R(1, [](std::string_view arg0){{return cc::SpriteBatchNode::create(std::move(arg0));}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cc_SpriteBatchNode_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteBatchNode", "cc.SpriteBatchNode:createWithTexture");
	LUA_TRY_INVOKE_R(2, &cc::SpriteBatchNode::createWithTexture);
	LUA_TRY_INVOKE_R(1, [](cc::Texture2D* arg0){{return cc::SpriteBatchNode::createWithTexture(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int luaReg_Core_ccSpriteBatchNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::SpriteBatchNode, "SpriteBatchNode", "cc.SpriteBatchNode",
		cc::SpriteBatchNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addSpriteWithoutQuad", lua_cc_SpriteBatchNode_addSpriteWithoutQuad);
	LUA_METHOD("appendChild", lua_cc_SpriteBatchNode_appendChild);
	LUA_METHOD("atlasIndexForChild", lua_cc_SpriteBatchNode_atlasIndexForChild);
	LUA_METHOD("getBlendFunc", lua_cc_SpriteBatchNode_getBlendFunc);
	LUA_METHOD("getDescendants", lua_cc_SpriteBatchNode_getDescendants);
	LUA_METHOD("getTexture", lua_cc_SpriteBatchNode_getTexture);
	LUA_METHOD("getTextureAtlas", lua_cc_SpriteBatchNode_getTextureAtlas);
	LUA_METHOD("highestAtlasIndexInChild", lua_cc_SpriteBatchNode_highestAtlasIndexInChild);
	LUA_METHOD("increaseAtlasCapacity", lua_cc_SpriteBatchNode_increaseAtlasCapacity);
	LUA_METHOD("initWithFile", lua_cc_SpriteBatchNode_initWithFile);
	LUA_METHOD("initWithTexture", lua_cc_SpriteBatchNode_initWithTexture);
	LUA_METHOD("insertQuadFromSprite", lua_cc_SpriteBatchNode_insertQuadFromSprite);
	LUA_METHOD("lowestAtlasIndexInChild", lua_cc_SpriteBatchNode_lowestAtlasIndexInChild);
	LUA_METHOD("rebuildIndexInOrder", lua_cc_SpriteBatchNode_rebuildIndexInOrder);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cc_SpriteBatchNode_removeAllChildrenWithCleanup);
	LUA_METHOD("removeChildAtIndex", lua_cc_SpriteBatchNode_removeChildAtIndex);
	LUA_METHOD("removeSpriteFromAtlas", lua_cc_SpriteBatchNode_removeSpriteFromAtlas);
	LUA_METHOD("reorderBatch", lua_cc_SpriteBatchNode_reorderBatch);
	LUA_METHOD("reserveCapacity", lua_cc_SpriteBatchNode_reserveCapacity);
	LUA_METHOD("setBlendFunc", lua_cc_SpriteBatchNode_setBlendFunc);
	LUA_METHOD("setTexture", lua_cc_SpriteBatchNode_setTexture);
	LUA_METHOD("setTextureAtlas", lua_cc_SpriteBatchNode_setTextureAtlas);
	LUA_METHOD("create", lua_cc_SpriteBatchNode_create);
	LUA_METHOD("createWithTexture", lua_cc_SpriteBatchNode_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ParallaxNode_addChild_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:addChild");
	LUA_TRY_INVOKE(4, (static_cast<void(cc::ParallaxNode::*)(cc::IntrusivePtr<cc::Node>, int, const cc::Vec2&, const cc::Vec2&)>(&cc::ParallaxNode::addChild)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_ParallaxNode_removeAllChildrenWithCleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:removeAllChildrenWithCleanup");
	LUA_TRY_INVOKE(1, &cc::ParallaxNode::removeAllChildrenWithCleanup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_ParallaxNode_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ParallaxNode", "cc.ParallaxNode:create");
	LUA_TRY_INVOKE_R(0, &cc::ParallaxNode::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccParallaxNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ParallaxNode, "ParallaxNode", "cc.ParallaxNode",
		cc::ParallaxNode, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addChild", lua_cc_ParallaxNode_addChild_1);
	LUA_METHOD("removeAllChildrenWithCleanup", lua_cc_ParallaxNode_removeAllChildrenWithCleanup);
	LUA_METHOD("create", lua_cc_ParallaxNode_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXObjectGroup_getGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getGroupName");
	LUA_TRY_INVOKE_R(0, &cc::TMXObjectGroup::getGroupName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXObjectGroup_getObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObject");
	LUA_TRY_INVOKE_R(1, &cc::TMXObjectGroup::getObject);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXObjectGroup_getObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getObjects");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ValueVector&(cc::TMXObjectGroup::*)()>(&cc::TMXObjectGroup::getObjects));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ValueVector&(cc::TMXObjectGroup::*)()const>(&cc::TMXObjectGroup::getObjects));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXObjectGroup_getPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getPositionOffset");
	LUA_TRY_INVOKE_R(0, &cc::TMXObjectGroup::getPositionOffset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXObjectGroup_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ValueMap&(cc::TMXObjectGroup::*)()>(&cc::TMXObjectGroup::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ValueMap&(cc::TMXObjectGroup::*)()const>(&cc::TMXObjectGroup::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXObjectGroup_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:getProperty");
	LUA_TRY_INVOKE_R(1, &cc::TMXObjectGroup::getProperty);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXObjectGroup_setGroupName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setGroupName");
	LUA_TRY_INVOKE(1, &cc::TMXObjectGroup::setGroupName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXObjectGroup_setObjects(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setObjects");
	LUA_TRY_INVOKE(1, &cc::TMXObjectGroup::setObjects);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXObjectGroup_setPositionOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setPositionOffset");
	LUA_TRY_INVOKE(1, &cc::TMXObjectGroup::setPositionOffset);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXObjectGroup_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXObjectGroup", "cc.TMXObjectGroup:setProperties");
	LUA_TRY_INVOKE(1, &cc::TMXObjectGroup::setProperties);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXObjectGroup(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXObjectGroup, "TMXObjectGroup", "cc.TMXObjectGroup",
		cc::TMXObjectGroup, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getGroupName", lua_cc_TMXObjectGroup_getGroupName);
	LUA_METHOD("getObject", lua_cc_TMXObjectGroup_getObject);
	LUA_METHOD("getObjects", lua_cc_TMXObjectGroup_getObjects);
	LUA_METHOD("getPositionOffset", lua_cc_TMXObjectGroup_getPositionOffset);
	LUA_METHOD("getProperties", lua_cc_TMXObjectGroup_getProperties);
	LUA_METHOD("getProperty", lua_cc_TMXObjectGroup_getProperty);
	LUA_METHOD("setGroupName", lua_cc_TMXObjectGroup_setGroupName);
	LUA_METHOD("setObjects", lua_cc_TMXObjectGroup_setObjects);
	LUA_METHOD("setPositionOffset", lua_cc_TMXObjectGroup_setPositionOffset);
	LUA_METHOD("setProperties", lua_cc_TMXObjectGroup_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXLayerInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:getProperties");
	LUA_TRY_INVOKE_R(0, &cc::TMXLayerInfo::getProperties);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXLayerInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXLayerInfo", "cc.TMXLayerInfo:setProperties");
	LUA_TRY_INVOKE(1, &cc::TMXLayerInfo::setProperties);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXLayerInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXLayerInfo, "TMXLayerInfo", "cc.TMXLayerInfo",
		cc::TMXLayerInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getProperties", lua_cc_TMXLayerInfo_getProperties);
	LUA_METHOD("setProperties", lua_cc_TMXLayerInfo_setProperties);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXTilesetInfo_getRectForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTilesetInfo", "cc.TMXTilesetInfo:getRectForGID");
	LUA_TRY_INVOKE_R(1, &cc::TMXTilesetInfo::getRectForGID);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTilesetInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXTilesetInfo, "TMXTilesetInfo", "cc.TMXTilesetInfo",
		cc::TMXTilesetInfo, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getRectForGID", lua_cc_TMXTilesetInfo_getRectForGID);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXMapInfo_getCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getCurrentString");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getCurrentString);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getExternalTilesetFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getExternalTilesetFileName");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getExternalTilesetFileName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getHexSideLength");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getHexSideLength);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayerAttribs");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getLayerAttribs);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getLayers");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Vector<cc::TMXLayerInfo *>&(cc::TMXMapInfo::*)()>(&cc::TMXMapInfo::getLayers));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Vector<cc::TMXLayerInfo *>&(cc::TMXMapInfo::*)()const>(&cc::TMXMapInfo::getLayers));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getMapSize");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getMapSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Vector<cc::TMXObjectGroup *>&(cc::TMXMapInfo::*)()>(&cc::TMXMapInfo::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Vector<cc::TMXObjectGroup *>&(cc::TMXMapInfo::*)()const>(&cc::TMXMapInfo::getObjectGroups));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getOrientation");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getOrientation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentElement");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getParentElement);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getParentGID");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getParentGID);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ValueMap&(cc::TMXMapInfo::*)()>(&cc::TMXMapInfo::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ValueMap&(cc::TMXMapInfo::*)()const>(&cc::TMXMapInfo::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerAxis");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getStaggerAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getStaggerIndex");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getStaggerIndex);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTMXFileName");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getTMXFileName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileProperties");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getTileProperties);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTileSize");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::getTileSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_getTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:getTilesets");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Vector<cc::TMXTilesetInfo *>&(cc::TMXMapInfo::*)()>(&cc::TMXMapInfo::getTilesets));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Vector<cc::TMXTilesetInfo *>&(cc::TMXMapInfo::*)()const>(&cc::TMXMapInfo::getTilesets));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, &cc::TMXMapInfo::initWithTMXFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:initWithXML");
	LUA_TRY_INVOKE_R(2, &cc::TMXMapInfo::initWithXML);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TMXMapInfo_isStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:isStoringCharacters");
	LUA_TRY_INVOKE_R(0, &cc::TMXMapInfo::isStoringCharacters);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXMapInfo_parseXMLFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLFile");
	LUA_TRY_INVOKE_R(1, &cc::TMXMapInfo::parseXMLFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_parseXMLString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:parseXMLString");
	LUA_TRY_INVOKE_R(1, &cc::TMXMapInfo::parseXMLString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setCurrentString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setCurrentString");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setCurrentString);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setHexSideLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setHexSideLength");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setHexSideLength);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setLayerAttribs(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayerAttribs");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setLayerAttribs);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setLayers(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setLayers");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setLayers);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setMapSize");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setMapSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setObjectGroups");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setObjectGroups);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setOrientation");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setOrientation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setParentElement(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentElement");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setParentElement);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setParentGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setParentGID");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setParentGID);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setProperties");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setProperties);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setStaggerAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerAxis");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setStaggerAxis);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setStaggerIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStaggerIndex");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setStaggerIndex);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setStoringCharacters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setStoringCharacters");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setStoringCharacters);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setTMXFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTMXFileName");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setTMXFileName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setTileProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileProperties");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setTileProperties);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTileSize");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setTileSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_setTilesets(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:setTilesets");
	LUA_TRY_INVOKE(1, &cc::TMXMapInfo::setTilesets);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:create");
	LUA_TRY_INVOKE_R(1, &cc::TMXMapInfo::create);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_TMXMapInfo_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXMapInfo", "cc.TMXMapInfo:createWithXML");
	LUA_TRY_INVOKE_R(2, &cc::TMXMapInfo::createWithXML);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTMXMapInfo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXMapInfo, "TMXMapInfo", "cc.TMXMapInfo",
		cc::TMXMapInfo, "",
		nullptr, nullptr);
	LUA_METHOD("getCurrentString", lua_cc_TMXMapInfo_getCurrentString);
	LUA_METHOD("getExternalTilesetFileName", lua_cc_TMXMapInfo_getExternalTilesetFileName);
	LUA_METHOD("getHexSideLength", lua_cc_TMXMapInfo_getHexSideLength);
	LUA_METHOD("getLayerAttribs", lua_cc_TMXMapInfo_getLayerAttribs);
	LUA_METHOD("getLayers", lua_cc_TMXMapInfo_getLayers);
	LUA_METHOD("getMapSize", lua_cc_TMXMapInfo_getMapSize);
	LUA_METHOD("getObjectGroups", lua_cc_TMXMapInfo_getObjectGroups);
	LUA_METHOD("getOrientation", lua_cc_TMXMapInfo_getOrientation);
	LUA_METHOD("getParentElement", lua_cc_TMXMapInfo_getParentElement);
	LUA_METHOD("getParentGID", lua_cc_TMXMapInfo_getParentGID);
	LUA_METHOD("getProperties", lua_cc_TMXMapInfo_getProperties);
	LUA_METHOD("getStaggerAxis", lua_cc_TMXMapInfo_getStaggerAxis);
	LUA_METHOD("getStaggerIndex", lua_cc_TMXMapInfo_getStaggerIndex);
	LUA_METHOD("getTMXFileName", lua_cc_TMXMapInfo_getTMXFileName);
	LUA_METHOD("getTileProperties", lua_cc_TMXMapInfo_getTileProperties);
	LUA_METHOD("getTileSize", lua_cc_TMXMapInfo_getTileSize);
	LUA_METHOD("getTilesets", lua_cc_TMXMapInfo_getTilesets);
	LUA_METHOD("initWithTMXFile", lua_cc_TMXMapInfo_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cc_TMXMapInfo_initWithXML);
	LUA_METHOD("isStoringCharacters", lua_cc_TMXMapInfo_isStoringCharacters);
	LUA_METHOD("parseXMLFile", lua_cc_TMXMapInfo_parseXMLFile);
	LUA_METHOD("parseXMLString", lua_cc_TMXMapInfo_parseXMLString);
	LUA_METHOD("setCurrentString", lua_cc_TMXMapInfo_setCurrentString);
	LUA_METHOD("setHexSideLength", lua_cc_TMXMapInfo_setHexSideLength);
	LUA_METHOD("setLayerAttribs", lua_cc_TMXMapInfo_setLayerAttribs);
	LUA_METHOD("setLayers", lua_cc_TMXMapInfo_setLayers);
	LUA_METHOD("setMapSize", lua_cc_TMXMapInfo_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cc_TMXMapInfo_setObjectGroups);
	LUA_METHOD("setOrientation", lua_cc_TMXMapInfo_setOrientation);
	LUA_METHOD("setParentElement", lua_cc_TMXMapInfo_setParentElement);
	LUA_METHOD("setParentGID", lua_cc_TMXMapInfo_setParentGID);
	LUA_METHOD("setProperties", lua_cc_TMXMapInfo_setProperties);
	LUA_METHOD("setStaggerAxis", lua_cc_TMXMapInfo_setStaggerAxis);
	LUA_METHOD("setStaggerIndex", lua_cc_TMXMapInfo_setStaggerIndex);
	LUA_METHOD("setStoringCharacters", lua_cc_TMXMapInfo_setStoringCharacters);
	LUA_METHOD("setTMXFileName", lua_cc_TMXMapInfo_setTMXFileName);
	LUA_METHOD("setTileProperties", lua_cc_TMXMapInfo_setTileProperties);
	LUA_METHOD("setTileSize", lua_cc_TMXMapInfo_setTileSize);
	LUA_METHOD("setTilesets", lua_cc_TMXMapInfo_setTilesets);
	LUA_METHOD("create", lua_cc_TMXMapInfo_create);
	LUA_METHOD("createWithXML", lua_cc_TMXMapInfo_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TileMapAtlas_getTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:getTileAt");
	LUA_TRY_INVOKE_R(1, &cc::TileMapAtlas::getTileAt);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_TileMapAtlas_initWithTileFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:initWithTileFile");
	LUA_TRY_INVOKE_R(4, &cc::TileMapAtlas::initWithTileFile);
	LUA_INVOKE_FOOTER("4");
}
int lua_cc_TileMapAtlas_releaseMap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:releaseMap");
	LUA_TRY_INVOKE(0, &cc::TileMapAtlas::releaseMap);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TileMapAtlas_setTile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:setTile");
	LUA_TRY_INVOKE(2, &cc::TileMapAtlas::setTile);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_TileMapAtlas_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TileMapAtlas", "cc.TileMapAtlas:create");
	LUA_TRY_INVOKE_R(4, &cc::TileMapAtlas::create);
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTileMapAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TileMapAtlas, "TileMapAtlas", "cc.TileMapAtlas",
		cc::TileMapAtlas, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_METHOD("getTileAt", lua_cc_TileMapAtlas_getTileAt);
	LUA_METHOD("initWithTileFile", lua_cc_TileMapAtlas_initWithTileFile);
	LUA_METHOD("releaseMap", lua_cc_TileMapAtlas_releaseMap);
	LUA_METHOD("setTile", lua_cc_TileMapAtlas_setTile);
	LUA_METHOD("create", lua_cc_TileMapAtlas_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FastTMXLayer_getLayerName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerName");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getLayerName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getLayerOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerOrientation");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getLayerOrientation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getLayerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getLayerSize");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getLayerSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getMapTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getMapTileSize");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getMapTileSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getPositionAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getPositionAt");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXLayer::getPositionAt);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getProperties");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ValueMap&(cc::FastTMXLayer::*)()>(&cc::FastTMXLayer::getProperties));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ValueMap&(cc::FastTMXLayer::*)()const>(&cc::FastTMXLayer::getProperties));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getProperty");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXLayer::getProperty);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_getTileAnimManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileAnimManager");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getTileAnimManager);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_getTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileAt");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXLayer::getTileAt);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_getTileSet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:getTileSet");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::getTileSet);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_hasTileAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:hasTileAnimation");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXLayer::hasTileAnimation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_initWithTilesetInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:initWithTilesetInfo");
	LUA_TRY_INVOKE_R(3, &cc::FastTMXLayer::initWithTilesetInfo);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_FastTMXLayer_removeTileAt(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:removeTileAt");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::removeTileAt);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setLayerName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerName");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setLayerName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setLayerOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerOrientation");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setLayerOrientation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setLayerSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setLayerSize");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setLayerSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setMapTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setMapTileSize");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setMapTileSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setProperties");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setProperties);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setTileGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setTileGID");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::FastTMXLayer::*)(int, const cc::Vec2&, cc::TMXTileFlags)>(&cc::FastTMXLayer::setTileGID)));
	LUA_TRY_INVOKE(2, (static_cast<void(cc::FastTMXLayer::*)(int, const cc::Vec2&)>(&cc::FastTMXLayer::setTileGID)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_FastTMXLayer_setTileSet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setTileSet");
	LUA_TRY_INVOKE(1, &cc::FastTMXLayer::setTileSet);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXLayer_setupTileSprite(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setupTileSprite");
	LUA_TRY_INVOKE(3, &cc::FastTMXLayer::setupTileSprite);
	LUA_INVOKE_FOOTER("3");
}
int lua_cc_FastTMXLayer_setupTiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:setupTiles");
	LUA_TRY_INVOKE(0, &cc::FastTMXLayer::setupTiles);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXLayer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXLayer", "cc.FastTMXLayer:create");
	LUA_TRY_INVOKE_R(3, &cc::FastTMXLayer::create);
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccFastTMXLayer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FastTMXLayer, "FastTMXLayer", "cc.FastTMXLayer",
		cc::FastTMXLayer, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayerName", lua_cc_FastTMXLayer_getLayerName);
	LUA_METHOD("getLayerOrientation", lua_cc_FastTMXLayer_getLayerOrientation);
	LUA_METHOD("getLayerSize", lua_cc_FastTMXLayer_getLayerSize);
	LUA_METHOD("getMapTileSize", lua_cc_FastTMXLayer_getMapTileSize);
	LUA_METHOD("getPositionAt", lua_cc_FastTMXLayer_getPositionAt);
	LUA_METHOD("getProperties", lua_cc_FastTMXLayer_getProperties);
	LUA_METHOD("getProperty", lua_cc_FastTMXLayer_getProperty);
	LUA_METHOD("getTileAnimManager", lua_cc_FastTMXLayer_getTileAnimManager);
	LUA_METHOD("getTileAt", lua_cc_FastTMXLayer_getTileAt);
	LUA_METHOD("getTileSet", lua_cc_FastTMXLayer_getTileSet);
	LUA_METHOD("hasTileAnimation", lua_cc_FastTMXLayer_hasTileAnimation);
	LUA_METHOD("initWithTilesetInfo", lua_cc_FastTMXLayer_initWithTilesetInfo);
	LUA_METHOD("removeTileAt", lua_cc_FastTMXLayer_removeTileAt);
	LUA_METHOD("setLayerName", lua_cc_FastTMXLayer_setLayerName);
	LUA_METHOD("setLayerOrientation", lua_cc_FastTMXLayer_setLayerOrientation);
	LUA_METHOD("setLayerSize", lua_cc_FastTMXLayer_setLayerSize);
	LUA_METHOD("setMapTileSize", lua_cc_FastTMXLayer_setMapTileSize);
	LUA_METHOD("setProperties", lua_cc_FastTMXLayer_setProperties);
	LUA_METHOD("setTileGID", lua_cc_FastTMXLayer_setTileGID);
	LUA_METHOD("setTileSet", lua_cc_FastTMXLayer_setTileSet);
	LUA_METHOD("setupTileSprite", lua_cc_FastTMXLayer_setupTileSprite);
	LUA_METHOD("setupTiles", lua_cc_FastTMXLayer_setupTiles);
	LUA_METHOD("create", lua_cc_FastTMXLayer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXTileAnimTask_isRunning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:isRunning");
	LUA_TRY_INVOKE_R(0, &cc::TMXTileAnimTask::isRunning);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXTileAnimTask_start(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:start");
	LUA_TRY_INVOKE(0, &cc::TMXTileAnimTask::start);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXTileAnimTask_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimTask", "cc.TMXTileAnimTask:stop");
	LUA_TRY_INVOKE(0, &cc::TMXTileAnimTask::stop);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccTMXTileAnimTask(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXTileAnimTask, "TMXTileAnimTask", "cc.TMXTileAnimTask",
		cc::TMXTileAnimTask, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("isRunning", lua_cc_TMXTileAnimTask_isRunning);
	LUA_METHOD("start", lua_cc_TMXTileAnimTask_start);
	LUA_METHOD("stop", lua_cc_TMXTileAnimTask_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_TMXTileAnimManager_getTasks(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:getTasks");
	LUA_TRY_INVOKE_R(0, &cc::TMXTileAnimManager::getTasks);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXTileAnimManager_startAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:startAll");
	LUA_TRY_INVOKE(0, &cc::TMXTileAnimManager::startAll);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXTileAnimManager_stopAll(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:stopAll");
	LUA_TRY_INVOKE(0, &cc::TMXTileAnimManager::stopAll);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_TMXTileAnimManager_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TMXTileAnimManager", "cc.TMXTileAnimManager:create");
	LUA_TRY_INVOKE_R(1, &cc::TMXTileAnimManager::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTMXTileAnimManager(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::TMXTileAnimManager, "TMXTileAnimManager", "cc.TMXTileAnimManager",
		cc::TMXTileAnimManager, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getTasks", lua_cc_TMXTileAnimManager_getTasks);
	LUA_METHOD("startAll", lua_cc_TMXTileAnimManager_startAll);
	LUA_METHOD("stopAll", lua_cc_TMXTileAnimManager_stopAll);
	LUA_METHOD("create", lua_cc_TMXTileAnimManager_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_FastTMXTiledMap_getLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayer");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::getLayer);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_getLayerCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getLayerCount");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getLayerCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapOrientation");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getMapOrientation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getMapSize");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getMapSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getObjectGroup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroup");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::getObjectGroup);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_getObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getObjectGroups");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Vector<cc::TMXObjectGroup *>&(cc::FastTMXTiledMap::*)()>(&cc::FastTMXTiledMap::getObjectGroups));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Vector<cc::TMXObjectGroup *>&(cc::FastTMXTiledMap::*)()const>(&cc::FastTMXTiledMap::getObjectGroups));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperties");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getProperties);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getPropertiesForGID(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getPropertiesForGID");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::getPropertiesForGID);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_getProperty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getProperty");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::getProperty);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_getResourceFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getResourceFile");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getResourceFile);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_getTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:getTileSize");
	LUA_TRY_INVOKE_R(0, &cc::FastTMXTiledMap::getTileSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_FastTMXTiledMap_initWithTMXFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithTMXFile");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::initWithTMXFile);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_initWithXML(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:initWithXML");
	LUA_TRY_INVOKE_R(2, &cc::FastTMXTiledMap::initWithXML);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_FastTMXTiledMap_setMapOrientation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapOrientation");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setMapOrientation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_setMapSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setMapSize");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setMapSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_setObjectGroups(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setObjectGroups");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setObjectGroups);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_setProperties(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setProperties");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setProperties);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_setTileAnimEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileAnimEnabled");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setTileAnimEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_setTileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:setTileSize");
	LUA_TRY_INVOKE(1, &cc::FastTMXTiledMap::setTileSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:create");
	LUA_TRY_INVOKE_R(1, &cc::FastTMXTiledMap::create);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_FastTMXTiledMap_createWithXML(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FastTMXTiledMap", "cc.FastTMXTiledMap:createWithXML");
	LUA_TRY_INVOKE_R(2, &cc::FastTMXTiledMap::createWithXML);
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFastTMXTiledMap(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::FastTMXTiledMap, "FastTMXTiledMap", "cc.FastTMXTiledMap",
		cc::FastTMXTiledMap, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getLayer", lua_cc_FastTMXTiledMap_getLayer);
	LUA_METHOD("getLayerCount", lua_cc_FastTMXTiledMap_getLayerCount);
	LUA_METHOD("getMapOrientation", lua_cc_FastTMXTiledMap_getMapOrientation);
	LUA_METHOD("getMapSize", lua_cc_FastTMXTiledMap_getMapSize);
	LUA_METHOD("getObjectGroup", lua_cc_FastTMXTiledMap_getObjectGroup);
	LUA_METHOD("getObjectGroups", lua_cc_FastTMXTiledMap_getObjectGroups);
	LUA_METHOD("getProperties", lua_cc_FastTMXTiledMap_getProperties);
	LUA_METHOD("getPropertiesForGID", lua_cc_FastTMXTiledMap_getPropertiesForGID);
	LUA_METHOD("getProperty", lua_cc_FastTMXTiledMap_getProperty);
	LUA_METHOD("getResourceFile", lua_cc_FastTMXTiledMap_getResourceFile);
	LUA_METHOD("getTileSize", lua_cc_FastTMXTiledMap_getTileSize);
	LUA_METHOD("initWithTMXFile", lua_cc_FastTMXTiledMap_initWithTMXFile);
	LUA_METHOD("initWithXML", lua_cc_FastTMXTiledMap_initWithXML);
	LUA_METHOD("setMapOrientation", lua_cc_FastTMXTiledMap_setMapOrientation);
	LUA_METHOD("setMapSize", lua_cc_FastTMXTiledMap_setMapSize);
	LUA_METHOD("setObjectGroups", lua_cc_FastTMXTiledMap_setObjectGroups);
	LUA_METHOD("setProperties", lua_cc_FastTMXTiledMap_setProperties);
	LUA_METHOD("setTileAnimEnabled", lua_cc_FastTMXTiledMap_setTileAnimEnabled);
	LUA_METHOD("setTileSize", lua_cc_FastTMXTiledMap_setTileSize);
	LUA_METHOD("create", lua_cc_FastTMXTiledMap_create);
	LUA_METHOD("createWithXML", lua_cc_FastTMXTiledMap_createWithXML);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_MotionStreak3D_getBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getBlendFunc");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak3D::getBlendFunc);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_getStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getStroke");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak3D::getStroke);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_getSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getSweepAxis");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak3D::getSweepAxis);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:getTexture");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak3D::getTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_initWithFade(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:initWithFade");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::MotionStreak3D::*)(float, float, float, const cc::Color3B&, cc::Texture2D*)>(&cc::MotionStreak3D::initWithFade)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<bool(cc::MotionStreak3D::*)(float, float, float, const cc::Color3B&, std::string_view)>(&cc::MotionStreak3D::initWithFade)));
	LUA_INVOKE_FOOTER("5");
}
int lua_cc_MotionStreak3D_isStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:isStartingPositionInitialized");
	LUA_TRY_INVOKE_R(0, &cc::MotionStreak3D::isStartingPositionInitialized);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_reset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:reset");
	LUA_TRY_INVOKE(0, &cc::MotionStreak3D::reset);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_MotionStreak3D_setBlendFunc(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setBlendFunc");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::setBlendFunc);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_setStartingPositionInitialized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStartingPositionInitialized");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::setStartingPositionInitialized);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_setStroke(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setStroke");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::setStroke);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_setSweepAxis(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setSweepAxis");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::setSweepAxis);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:setTexture");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::setTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_tintWithColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:tintWithColor");
	LUA_TRY_INVOKE(1, &cc::MotionStreak3D::tintWithColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_MotionStreak3D_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MotionStreak3D", "cc.MotionStreak3D:create");
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::MotionStreak3D>(*)(float, float, float, const cc::Color3B&, cc::Texture2D*)>(&cc::MotionStreak3D::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(5, (static_cast<cc::IntrusivePtr<cc::MotionStreak3D>(*)(float, float, float, const cc::Color3B&, std::string_view)>(&cc::MotionStreak3D::create)));
	LUA_SINVOKE_FOOTER("5");
}
int luaReg_Core_ccMotionStreak3D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::MotionStreak3D, "MotionStreak3D", "cc.MotionStreak3D",
		cc::MotionStreak3D, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getBlendFunc", lua_cc_MotionStreak3D_getBlendFunc);
	LUA_METHOD("getStroke", lua_cc_MotionStreak3D_getStroke);
	LUA_METHOD("getSweepAxis", lua_cc_MotionStreak3D_getSweepAxis);
	LUA_METHOD("getTexture", lua_cc_MotionStreak3D_getTexture);
	LUA_METHOD("initWithFade", lua_cc_MotionStreak3D_initWithFade);
	LUA_METHOD("isStartingPositionInitialized", lua_cc_MotionStreak3D_isStartingPositionInitialized);
	LUA_METHOD("reset", lua_cc_MotionStreak3D_reset);
	LUA_METHOD("setBlendFunc", lua_cc_MotionStreak3D_setBlendFunc);
	LUA_METHOD("setStartingPositionInitialized", lua_cc_MotionStreak3D_setStartingPositionInitialized);
	LUA_METHOD("setStroke", lua_cc_MotionStreak3D_setStroke);
	LUA_METHOD("setSweepAxis", lua_cc_MotionStreak3D_setSweepAxis);
	LUA_METHOD("setTexture", lua_cc_MotionStreak3D_setTexture);
	LUA_METHOD("tintWithColor", lua_cc_MotionStreak3D_tintWithColor);
	LUA_METHOD("create", lua_cc_MotionStreak3D_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_ComponentLua_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ComponentLua", "cc.ComponentLua:create");
	LUA_TRY_INVOKE_R(1, &cc::ComponentLua::create);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccComponentLua(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::ComponentLua, "ComponentLua", "cc.ComponentLua",
		cc::ComponentLua, "cc.Component",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_ComponentLua_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
