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

int lua_cc_Ref_getReferenceCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:getReferenceCount");
	LUA_TRY_INVOKE_R(0, &cc::Ref::getReferenceCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ref_release(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:release");
	LUA_TRY_INVOKE(0, &cc::Ref::release);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Ref_retain(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:retain");
	LUA_TRY_INVOKE(0, &cc::Ref::retain);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccRef(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Ref, "Ref", "cc.Ref",
		cc::Ref, "",
		nullptr, nullptr);
	LUA_METHOD("getReferenceCount", lua_cc_Ref_getReferenceCount);
	LUA_METHOD("release", lua_cc_Ref_release);
	LUA_METHOD("retain", lua_cc_Ref_retain);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Console_delCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:delCommand");
	LUA_TRY_INVOKE(1, &cc::Console::delCommand);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_isIpv6Server(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:isIpv6Server");
	LUA_TRY_INVOKE_R(0, &cc::Console::isIpv6Server);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Console_listenOnFileDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:listenOnFileDescriptor");
	LUA_TRY_INVOKE_R(1, &cc::Console::listenOnFileDescriptor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_listenOnTCP(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:listenOnTCP");
	LUA_TRY_INVOKE_R(1, &cc::Console::listenOnTCP);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_print(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:print");
	LUA_TRY_INVOKE(1, &cc::Console::print);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_setBindAddress(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:setBindAddress");
	LUA_TRY_INVOKE(1, &cc::Console::setBindAddress);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_setCommandSeparator(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:setCommandSeparator");
	LUA_TRY_INVOKE(1, &cc::Console::setCommandSeparator);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Console_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:stop");
	LUA_TRY_INVOKE(0, &cc::Console::stop);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccConsole(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Console, "Console", "cc.Console",
		cc::Console, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("delCommand", lua_cc_Console_delCommand);
	LUA_METHOD("isIpv6Server", lua_cc_Console_isIpv6Server);
	LUA_METHOD("listenOnFileDescriptor", lua_cc_Console_listenOnFileDescriptor);
	LUA_METHOD("listenOnTCP", lua_cc_Console_listenOnTCP);
	LUA_METHOD("print", lua_cc_Console_print);
	LUA_METHOD("setBindAddress", lua_cc_Console_setBindAddress);
	LUA_METHOD("setCommandSeparator", lua_cc_Console_setCommandSeparator);
	LUA_METHOD("stop", lua_cc_Console_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListener_checkAvailable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:checkAvailable");
	LUA_TRY_INVOKE_R(0, &cc::EventListener::checkAvailable);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListener_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:clone");
	LUA_TRY_INVOKE_R(0, &cc::EventListener::clone);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListener_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::EventListener::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventListener_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:setEnabled");
	LUA_TRY_INVOKE(1, &cc::EventListener::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListener(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListener, "EventListener", "cc.EventListener",
		cc::EventListener, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("checkAvailable", lua_cc_EventListener_checkAvailable);
	LUA_METHOD("clone", lua_cc_EventListener_clone);
	LUA_METHOD("isEnabled", lua_cc_EventListener_isEnabled);
	LUA_METHOD("setEnabled", lua_cc_EventListener_setEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventListenerCustom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerCustom", "cc.EventListenerCustom:create");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, &cc::EventListenerCustom::create);
	}
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEventListenerCustom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventListenerCustom, "EventListenerCustom", "cc.EventListenerCustom",
		cc::EventListenerCustom, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cc_EventListenerCustom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_backend_ShaderCache_removeUnusedShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:removeUnusedShader");
	LUA_TRY_INVOKE(0, &cc::backend::ShaderCache::removeUnusedShader);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_backend_ShaderCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:getInstance");
	LUA_TRY_INVOKE_R(0, &cc::backend::ShaderCache::getInstance);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_backend_ShaderCache_newFragmentShaderModule(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:newFragmentShaderModule");
	LUA_TRY_INVOKE_R(1, &cc::backend::ShaderCache::newFragmentShaderModule);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_backend_ShaderCache_newVertexShaderModule(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:newVertexShaderModule");
	LUA_TRY_INVOKE_R(1, &cc::backend::ShaderCache::newVertexShaderModule);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccShaderCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::backend::ShaderCache, "ShaderCache", "ccb.ShaderCache",
		cc::backend::ShaderCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("removeUnusedShader", lua_cc_backend_ShaderCache_removeUnusedShader);
	LUA_METHOD("getInstance", lua_cc_backend_ShaderCache_getInstance);
	LUA_METHOD("newFragmentShaderModule", lua_cc_backend_ShaderCache_newFragmentShaderModule);
	LUA_METHOD("newVertexShaderModule", lua_cc_backend_ShaderCache_newVertexShaderModule);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Texture2D_drawAtPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:drawAtPoint");
	LUA_TRY_INVOKE(2, &cc::Texture2D::drawAtPoint);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Texture2D_drawInRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:drawInRect");
	LUA_TRY_INVOKE(2, &cc::Texture2D::drawInRect);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Texture2D_generateMipmap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:generateMipmap");
	LUA_TRY_INVOKE(0, &cc::Texture2D::generateMipmap);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getBackendTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getBackendTexture");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getBackendTexture);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getBitsPerPixelForFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getBitsPerPixelForFormat");
	LUA_TRY_INVOKE_R(1, static_cast<unsigned int(cc::Texture2D::*)(cc::backend::PixelFormat)const>(&cc::Texture2D::getBitsPerPixelForFormat));
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cc::Texture2D::*)()const>(&cc::Texture2D::getBitsPerPixelForFormat));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Texture2D_getContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getContentSize");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getContentSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getContentSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getContentSizeInPixels");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getContentSizeInPixels);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getMaxS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getMaxS");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getMaxS);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getMaxT(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getMaxT");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getMaxT);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPath");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getPath);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getPixelFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelFormat");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getPixelFormat);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getPixelsHigh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelsHigh");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getPixelsHigh);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getPixelsWide(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelsWide");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getPixelsWide);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getSamplerFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getSamplerFlags");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getSamplerFlags);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_getStringForFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getStringForFormat");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getStringForFormat);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_hasMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:hasMipmaps");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::hasMipmaps);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_hasPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:hasPremultipliedAlpha");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::hasPremultipliedAlpha);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_initWithImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:initWithImage");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::Texture2D::*)(cc::Image*, cc::backend::PixelFormat)>(&cc::Texture2D::initWithImage)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Texture2D::*)(cc::Image*)>(&cc::Texture2D::initWithImage));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Texture2D_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:initWithString");
	LUA_TRY_INVOKE_R(8, (static_cast<bool(cc::Texture2D::*)(const char*, std::string_view, float, const cc::Vec2&, cc::TextHAlignment, cc::TextVAlignment, bool, int)>(&cc::Texture2D::initWithString)));
	LUA_TRY_INVOKE_R(7, ([](cc::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4,cc::TextVAlignment arg5,bool arg6){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4),std::move(arg5),std::move(arg6));}}));
	LUA_TRY_INVOKE_R(6, ([](cc::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4,cc::TextVAlignment arg5){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4),std::move(arg5));}}));
	LUA_TRY_INVOKE_R(5, ([](cc::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3,cc::TextHAlignment arg4){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](cc::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cc::Vec2& arg3){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE_R(3, ([](cc::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cc::Texture2D::*)(const char*, const cc::FontDefinition&)>(&cc::Texture2D::initWithString)));
	LUA_INVOKE_FOOTER("2,3,4,5,6,7,8");
}
int lua_cc_Texture2D_isRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:isRenderTarget");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::isRenderTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_setAliasTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setAliasTexParameters");
	LUA_TRY_INVOKE(0, &cc::Texture2D::setAliasTexParameters);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_setAntiAliasTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setAntiAliasTexParameters");
	LUA_TRY_INVOKE(0, &cc::Texture2D::setAntiAliasTexParameters);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Texture2D_setMaxS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setMaxS");
	LUA_TRY_INVOKE(1, &cc::Texture2D::setMaxS);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Texture2D_setMaxT(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setMaxT");
	LUA_TRY_INVOKE(1, &cc::Texture2D::setMaxT);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Texture2D_setPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setPremultipliedAlpha");
	LUA_TRY_INVOKE(1, &cc::Texture2D::setPremultipliedAlpha);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Texture2D_setRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setRenderTarget");
	LUA_TRY_INVOKE(1, &cc::Texture2D::setRenderTarget);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Texture2D_setTexParameters_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setTexParameters");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Texture2D::*)(const cc::Texture2D::TexParams&)>(&cc::Texture2D::setTexParameters));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Texture2D_updateTextureDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:updateTextureDescriptor");
	LUA_TRY_INVOKE_R(2, &cc::Texture2D::updateTextureDescriptor);
	LUA_TRY_INVOKE_R(1, ([](cc::Texture2D* obj,const cc::backend::TextureDescriptor& arg0){{return obj->updateTextureDescriptor(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Texture2D_updateWithImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:updateWithImage");
	LUA_TRY_INVOKE_R(3, &cc::Texture2D::updateWithImage);
	LUA_TRY_INVOKE_R(2, ([](cc::Texture2D* obj,cc::Image* arg0,cc::backend::PixelFormat arg1){{return obj->updateWithImage(arg0,std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cc_Texture2D_getDefaultAlphaPixelFormat(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getDefaultAlphaPixelFormat");
	LUA_TRY_INVOKE_R(0, &cc::Texture2D::getDefaultAlphaPixelFormat);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Texture2D_setDefaultAlphaPixelFormat(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setDefaultAlphaPixelFormat");
	LUA_TRY_INVOKE(1, &cc::Texture2D::setDefaultAlphaPixelFormat);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTexture2D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Texture2D, "Texture2D", "cc.Texture2D",
		cc::Texture2D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("drawAtPoint", lua_cc_Texture2D_drawAtPoint);
	LUA_METHOD("drawInRect", lua_cc_Texture2D_drawInRect);
	LUA_METHOD("generateMipmap", lua_cc_Texture2D_generateMipmap);
	LUA_METHOD("getBackendTexture", lua_cc_Texture2D_getBackendTexture);
	LUA_METHOD("getBitsPerPixelForFormat", lua_cc_Texture2D_getBitsPerPixelForFormat);
	LUA_METHOD("getContentSize", lua_cc_Texture2D_getContentSize);
	LUA_METHOD("getContentSizeInPixels", lua_cc_Texture2D_getContentSizeInPixels);
	LUA_METHOD("getMaxS", lua_cc_Texture2D_getMaxS);
	LUA_METHOD("getMaxT", lua_cc_Texture2D_getMaxT);
	LUA_METHOD("getPath", lua_cc_Texture2D_getPath);
	LUA_METHOD("getPixelFormat", lua_cc_Texture2D_getPixelFormat);
	LUA_METHOD("getPixelsHigh", lua_cc_Texture2D_getPixelsHigh);
	LUA_METHOD("getPixelsWide", lua_cc_Texture2D_getPixelsWide);
	LUA_METHOD("getSamplerFlags", lua_cc_Texture2D_getSamplerFlags);
	LUA_METHOD("getStringForFormat", lua_cc_Texture2D_getStringForFormat);
	LUA_METHOD("hasMipmaps", lua_cc_Texture2D_hasMipmaps);
	LUA_METHOD("hasPremultipliedAlpha", lua_cc_Texture2D_hasPremultipliedAlpha);
	LUA_METHOD("initWithImage", lua_cc_Texture2D_initWithImage);
	LUA_METHOD("initWithString", lua_cc_Texture2D_initWithString);
	LUA_METHOD("isRenderTarget", lua_cc_Texture2D_isRenderTarget);
	LUA_METHOD("setAliasTexParameters", lua_cc_Texture2D_setAliasTexParameters);
	LUA_METHOD("setAntiAliasTexParameters", lua_cc_Texture2D_setAntiAliasTexParameters);
	LUA_METHOD("setMaxS", lua_cc_Texture2D_setMaxS);
	LUA_METHOD("setMaxT", lua_cc_Texture2D_setMaxT);
	LUA_METHOD("setPremultipliedAlpha", lua_cc_Texture2D_setPremultipliedAlpha);
	LUA_METHOD("setRenderTarget", lua_cc_Texture2D_setRenderTarget);
	LUA_METHOD("setTexParameters", lua_cc_Texture2D_setTexParameters_1);
	LUA_METHOD("updateTextureDescriptor", lua_cc_Texture2D_updateTextureDescriptor);
	LUA_METHOD("updateWithImage", lua_cc_Texture2D_updateWithImage);
	LUA_METHOD("getDefaultAlphaPixelFormat", lua_cc_Texture2D_getDefaultAlphaPixelFormat);
	LUA_METHOD("setDefaultAlphaPixelFormat", lua_cc_Texture2D_setDefaultAlphaPixelFormat);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Touch_getCurrentForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getCurrentForce");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getCurrentForce);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getDelta");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getDelta);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getId");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getID);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getLocation");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getMaxForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getMaxForce");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getMaxForce);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getPreviousLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getPreviousLocation");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getPreviousLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getPreviousLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getPreviousLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getPreviousLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getStartLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getStartLocation");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getStartLocation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_getStartLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getStartLocationInView");
	LUA_TRY_INVOKE_R(0, &cc::Touch::getStartLocationInView);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Touch_setTouchInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:setTouchInfo");
	LUA_TRY_INVOKE(5, (static_cast<void(cc::Touch::*)(int, float, float, float, float)>(&cc::Touch::setTouchInfo)));
	LUA_TRY_INVOKE(3, (static_cast<void(cc::Touch::*)(int, float, float)>(&cc::Touch::setTouchInfo)));
	LUA_INVOKE_FOOTER("3,5");
}
int luaReg_Core_ccTouch(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Touch, "Touch", "cc.Touch",
		cc::Touch, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentForce", lua_cc_Touch_getCurrentForce);
	LUA_METHOD("getDelta", lua_cc_Touch_getDelta);
	LUA_METHOD("getId", lua_cc_Touch_getId);
	LUA_METHOD("getLocation", lua_cc_Touch_getLocation);
	LUA_METHOD("getLocationInView", lua_cc_Touch_getLocationInView);
	LUA_METHOD("getMaxForce", lua_cc_Touch_getMaxForce);
	LUA_METHOD("getPreviousLocation", lua_cc_Touch_getPreviousLocation);
	LUA_METHOD("getPreviousLocationInView", lua_cc_Touch_getPreviousLocationInView);
	LUA_METHOD("getStartLocation", lua_cc_Touch_getStartLocation);
	LUA_METHOD("getStartLocationInView", lua_cc_Touch_getStartLocationInView);
	LUA_METHOD("setTouchInfo", lua_cc_Touch_setTouchInfo);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Event_getCurrentTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:getCurrentTarget");
	LUA_TRY_INVOKE_R(0, &cc::Event::getCurrentTarget);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Event_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:getType");
	LUA_TRY_INVOKE_R(0, &cc::Event::getType);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Event_isStopped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:isStopped");
	LUA_TRY_INVOKE_R(0, &cc::Event::isStopped);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Event_stopPropagation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:stopPropagation");
	LUA_TRY_INVOKE(0, &cc::Event::stopPropagation);
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEvent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Event, "Event", "cc.Event",
		cc::Event, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentTarget", lua_cc_Event_getCurrentTarget);
	LUA_METHOD("getType", lua_cc_Event_getType);
	LUA_METHOD("isStopped", lua_cc_Event_isStopped);
	LUA_METHOD("stopPropagation", lua_cc_Event_stopPropagation);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_EventTouch_getEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventTouch", "cc.EventTouch:getEventCode");
	LUA_TRY_INVOKE_R(0, &cc::EventTouch::getEventCode);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_EventTouch_setEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventTouch", "cc.EventTouch:setEventCode");
	LUA_TRY_INVOKE(1, &cc::EventTouch::setEventCode);
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventTouch(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventTouch, "EventTouch", "cc.EventTouch",
		cc::EventTouch, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventCode", lua_cc_EventTouch_getEventCode);
	LUA_METHOD("setEventCode", lua_cc_EventTouch_setEventCode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventKeyboard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::EventKeyboard, "EventKeyboard", "cc.EventKeyboard",
		cc::EventKeyboard, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Component_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:getName");
	LUA_TRY_INVOKE_R(0, &cc::Component::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_getOwner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:getOwner");
	LUA_TRY_INVOKE_R(0, &cc::Component::getOwner);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:init");
	LUA_TRY_INVOKE_R(0, &cc::Component::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:isEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Component::isEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_onAdd(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:onAdd");
	LUA_TRY_INVOKE(0, &cc::Component::onAdd);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_onRemove(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:onRemove");
	LUA_TRY_INVOKE(0, &cc::Component::onRemove);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Component_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setEnabled");
	LUA_TRY_INVOKE(1, &cc::Component::setEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Component_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setName");
	LUA_TRY_INVOKE(1, &cc::Component::setName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Component_setOwner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setOwner");
	LUA_TRY_INVOKE(1, &cc::Component::setOwner);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Component_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:update");
	LUA_TRY_INVOKE(1, &cc::Component::update);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Component_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Component", "cc.Component:create");
	LUA_TRY_INVOKE_R(0, &cc::Component::create);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccComponent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Component, "Component", "cc.Component",
		cc::Component, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getName", lua_cc_Component_getName);
	LUA_METHOD("getOwner", lua_cc_Component_getOwner);
	LUA_METHOD("init", lua_cc_Component_init);
	LUA_METHOD("isEnabled", lua_cc_Component_isEnabled);
	LUA_METHOD("onAdd", lua_cc_Component_onAdd);
	LUA_METHOD("onRemove", lua_cc_Component_onRemove);
	LUA_METHOD("setEnabled", lua_cc_Component_setEnabled);
	LUA_METHOD("setName", lua_cc_Component_setName);
	LUA_METHOD("setOwner", lua_cc_Component_setOwner);
	LUA_METHOD("update", lua_cc_Component_update);
	LUA_METHOD("create", lua_cc_Component_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Node__setLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:_setLocalZOrder");
	LUA_TRY_INVOKE(1, &cc::Node::_setLocalZOrder);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_addChild_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:addChild");
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cc::Node::*)(cc::IntrusivePtr<cc::Node>, int, int)>(&cc::Node::addChild)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cc::Node::*)(cc::IntrusivePtr<cc::Node>, int, std::string_view)>(&cc::Node::addChild)));
	LUA_TRY_INVOKE(2, (static_cast<void(cc::Node::*)(cc::IntrusivePtr<cc::Node>, int)>(&cc::Node::addChild)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(cc::IntrusivePtr<cc::Node>)>(&cc::Node::addChild));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cc_Node_addComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:addComponent");
	LUA_TRY_INVOKE_R(1, &cc::Node::addComponent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_applyMaskOnEnter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:applyMaskOnEnter");
	LUA_TRY_INVOKE(1, &cc::Node::applyMaskOnEnter);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_cleanup(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:cleanup");
	LUA_TRY_INVOKE(0, &cc::Node::cleanup);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_convertToNodeSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToNodeSpace");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertToNodeSpace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_convertToNodeSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToNodeSpaceAR");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertToNodeSpaceAR);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_convertToWorldSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToWorldSpace");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertToWorldSpace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_convertToWorldSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertToWorldSpaceAR");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertToWorldSpaceAR);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_convertTouchToNodeSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertTouchToNodeSpace");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertTouchToNodeSpace);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_convertTouchToNodeSpaceAR(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:convertTouchToNodeSpaceAR");
	LUA_TRY_INVOKE_R(1, &cc::Node::convertTouchToNodeSpaceAR);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_draw(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:draw");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::Node::*)(cc::Renderer*, const cc::Mat4&, uint32_t)>(&cc::Node::draw)));
	LUA_TRY_INVOKE(0, static_cast<void(cc::Node::*)()>(&cc::Node::draw));
	LUA_INVOKE_FOOTER("0,3");
}
int lua_cc_Node_enumerateChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:enumerateChildren");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE(2, &cc::Node::enumerateChildren);
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Node_getActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getActionByTag");
	LUA_TRY_INVOKE_R(1, &cc::Node::getActionByTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_getActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getActionManager");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::ActionManager*(cc::Node::*)()const>(&cc::Node::getActionManager));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::ActionManager*(cc::Node::*)()>(&cc::Node::getActionManager));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, &cc::Node::getAnchorPoint);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getAnchorPointInPoints(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getAnchorPointInPoints");
	LUA_TRY_INVOKE_R(0, &cc::Node::getAnchorPointInPoints);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getBoundingBox(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getBoundingBox");
	LUA_TRY_INVOKE_R(0, &cc::Node::getBoundingBox);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getCameraMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getCameraMask");
	LUA_TRY_INVOKE_R(0, &cc::Node::getCameraMask);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getChildByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildByName");
	LUA_TRY_INVOKE_R(1, static_cast<cc::Node*(cc::Node::*)(std::string_view)const>(&cc::Node::getChildByName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_getChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildByTag");
	LUA_TRY_INVOKE_R(1, static_cast<cc::Node*(cc::Node::*)(int)const>(&cc::Node::getChildByTag));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_getChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildren");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Vector<cc::Node *>&(cc::Node::*)()const>(&cc::Node::getChildren));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Vector<cc::Node *>&(cc::Node::*)()>(&cc::Node::getChildren));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getChildrenCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getChildrenCount");
	LUA_TRY_INVOKE_R(0, &cc::Node::getChildrenCount);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getColor");
	LUA_TRY_INVOKE_R(0, &cc::Node::getColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getComponent");
	LUA_TRY_INVOKE_R(1, &cc::Node::getComponent);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_getContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getContentSize");
	LUA_TRY_INVOKE_R(0, &cc::Node::getContentSize);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getDescription(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDescription");
	LUA_TRY_INVOKE_R(0, &cc::Node::getDescription);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getDisplayedColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDisplayedColor");
	LUA_TRY_INVOKE_R(0, &cc::Node::getDisplayedColor);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getDisplayedOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getDisplayedOpacity");
	LUA_TRY_INVOKE_R(0, &cc::Node::getDisplayedOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getEventDispatcher");
	LUA_TRY_INVOKE_R(0, &cc::Node::getEventDispatcher);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getGlobalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getGlobalZOrder");
	LUA_TRY_INVOKE_R(0, &cc::Node::getGlobalZOrder);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getLocalZOrder");
	LUA_TRY_INVOKE_R(0, &cc::Node::getLocalZOrder);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getName");
	LUA_TRY_INVOKE_R(0, &cc::Node::getName);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getNodeToParentAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToParentAffineTransform");
	LUA_TRY_INVOKE_R(1, static_cast<cc::AffineTransform(cc::Node::*)(cc::Node*)const>(&cc::Node::getNodeToParentAffineTransform));
	LUA_TRY_INVOKE_R(0, static_cast<cc::AffineTransform(cc::Node::*)()const>(&cc::Node::getNodeToParentAffineTransform));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Node_getNodeToParentTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToParentTransform");
	LUA_TRY_INVOKE_R(1, static_cast<cc::Mat4(cc::Node::*)(cc::Node*)const>(&cc::Node::getNodeToParentTransform));
	LUA_TRY_INVOKE_R(0, static_cast<const cc::Mat4&(cc::Node::*)()const>(&cc::Node::getNodeToParentTransform));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cc_Node_getNodeToWorldAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToWorldAffineTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getNodeToWorldAffineTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getNodeToWorldTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNodeToWorldTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getNodeToWorldTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getNormalizedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNormalizedPosition");
	LUA_TRY_INVOKE_R(0, &cc::Node::getNormalizedPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getNumberOfRunningActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNumberOfRunningActions");
	LUA_TRY_INVOKE_R(0, &cc::Node::getNumberOfRunningActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getNumberOfRunningActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getNumberOfRunningActionsByTag");
	LUA_TRY_INVOKE_R(1, &cc::Node::getNumberOfRunningActionsByTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_getOnEnterTransitionDidFinishCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOnEnterTransitionDidFinishCallback");
	LUA_TRY_INVOKE_R(0, &cc::Node::getOnEnterTransitionDidFinishCallback);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getOnExitTransitionDidStartCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOnExitTransitionDidStartCallback");
	LUA_TRY_INVOKE_R(0, &cc::Node::getOnExitTransitionDidStartCallback);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getOpacity");
	LUA_TRY_INVOKE_R(0, &cc::Node::getOpacity);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getParent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParent");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Node*(cc::Node::*)()const>(&cc::Node::getParent));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Node*(cc::Node::*)()>(&cc::Node::getParent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getParentToNodeAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParentToNodeAffineTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getParentToNodeAffineTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getParentToNodeTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getParentToNodeTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getParentToNodeTransform);
	LUA_INVOKE_FOOTER("0");
}
#if CC_USE_PHYSICS
int lua_cc_Node_getPhysicsBody_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPhysicsBody");
	LUA_TRY_INVOKE_R(0, static_cast<cc::PhysicsBody*(cc::Node::*)()const>(&cc::Node::getPhysicsBody));
	LUA_INVOKE_FOOTER("0");
}
#endif
int lua_cc_Node_getPosition_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPosition");
	LUA_TRY_INVOKE_R(0, static_cast<const cc::Vec2&(cc::Node::*)()const>(&cc::Node::getPosition));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getPosition3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPosition3D");
	LUA_TRY_INVOKE_R(0, &cc::Node::getPosition3D);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getPositionNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionNormalized");
	LUA_TRY_INVOKE_R(0, &cc::Node::getPositionNormalized);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getPositionX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionX");
	LUA_TRY_INVOKE_R(0, &cc::Node::getPositionX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getPositionY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionY");
	LUA_TRY_INVOKE_R(0, &cc::Node::getPositionY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getPositionZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getPositionZ");
	LUA_TRY_INVOKE_R(0, &cc::Node::getPositionZ);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getProgramState");
	LUA_TRY_INVOKE_R(0, &cc::Node::getProgramState);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotation");
	LUA_TRY_INVOKE_R(0, &cc::Node::getRotation);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getRotation3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotation3D");
	LUA_TRY_INVOKE_R(0, &cc::Node::getRotation3D);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getRotationSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotationSkewX");
	LUA_TRY_INVOKE_R(0, &cc::Node::getRotationSkewX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getRotationSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getRotationSkewY");
	LUA_TRY_INVOKE_R(0, &cc::Node::getRotationSkewY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScale");
	LUA_TRY_INVOKE_R(0, &cc::Node::getScale);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleX");
	LUA_TRY_INVOKE_R(0, &cc::Node::getScaleX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleY");
	LUA_TRY_INVOKE_R(0, &cc::Node::getScaleY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScaleZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScaleZ");
	LUA_TRY_INVOKE_R(0, &cc::Node::getScaleZ);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScene(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScene");
	LUA_TRY_INVOKE_R(0, &cc::Node::getScene);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getScheduler");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cc::Scheduler*(cc::Node::*)()const>(&cc::Node::getScheduler));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cc::Scheduler*(cc::Node::*)()>(&cc::Node::getScheduler));
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getSkewX");
	LUA_TRY_INVOKE_R(0, &cc::Node::getSkewX);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getSkewY");
	LUA_TRY_INVOKE_R(0, &cc::Node::getSkewY);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getTag");
	LUA_TRY_INVOKE_R(0, &cc::Node::getTag);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getWorldPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldPosition");
	LUA_TRY_INVOKE_R(0, &cc::Node::getWorldPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getWorldToNodeAffineTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldToNodeAffineTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getWorldToNodeAffineTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_getWorldToNodeTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:getWorldToNodeTransform");
	LUA_TRY_INVOKE_R(0, &cc::Node::getWorldToNodeTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_hitTest(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:hitTest");
	LUA_TRY_INVOKE_R(1, &cc::Node::hitTest);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:init");
	LUA_TRY_INVOKE_R(0, &cc::Node::init);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_initLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:initLayer");
	LUA_TRY_INVOKE_R(0, &cc::Node::initLayer);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isCascadeColorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isCascadeColorEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Node::isCascadeColorEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isCascadeOpacityEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isCascadeOpacityEnabled");
	LUA_TRY_INVOKE_R(0, &cc::Node::isCascadeOpacityEnabled);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isIgnoreAnchorPointForPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isIgnoreAnchorPointForPosition");
	LUA_TRY_INVOKE_R(0, &cc::Node::isIgnoreAnchorPointForPosition);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isOpacityModifyRGB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isOpacityModifyRGB");
	LUA_TRY_INVOKE_R(0, &cc::Node::isOpacityModifyRGB);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isRunning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isRunning");
	LUA_TRY_INVOKE_R(0, &cc::Node::isRunning);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_isScheduled_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isScheduled");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cc::Node::*)(std::string_view)const>(&cc::Node::isScheduled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_isVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:isVisible");
	LUA_TRY_INVOKE_R(0, &cc::Node::isVisible);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_pause(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:pause");
	LUA_TRY_INVOKE(0, &cc::Node::pause);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_removeAllComponents(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeAllComponents");
	LUA_TRY_INVOKE(0, &cc::Node::removeAllComponents);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_removeChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChild");
	LUA_TRY_INVOKE(2, &cc::Node::removeChild);
	LUA_TRY_INVOKE(1, ([](cc::Node* obj,cc::Node* arg0){{return obj->removeChild(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_removeChildByName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChildByName");
	LUA_TRY_INVOKE(2, &cc::Node::removeChildByName);
	LUA_TRY_INVOKE(1, ([](cc::Node* obj,std::string_view arg0){{return obj->removeChildByName(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_removeChildByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeChildByTag");
	LUA_TRY_INVOKE(2, &cc::Node::removeChildByTag);
	LUA_TRY_INVOKE(1, ([](cc::Node* obj,int arg0){{return obj->removeChildByTag(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_removeComponent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:removeComponent");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cc::Node::*)(cc::Component*)>(&cc::Node::removeComponent));
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cc::Node::*)(std::string_view)>(&cc::Node::removeComponent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_reorderChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:reorderChild");
	LUA_TRY_INVOKE(2, &cc::Node::reorderChild);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Node_resetChild(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:resetChild");
	LUA_TRY_INVOKE(2, &cc::Node::resetChild);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Node_resume(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:resume");
	LUA_TRY_INVOKE(0, &cc::Node::resume);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_runAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:runAction");
	LUA_TRY_INVOKE_R(1, &cc::Node::runAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setActionManager(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setActionManager");
	LUA_TRY_INVOKE(1, &cc::Node::setActionManager);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setAdditionalTransform_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setAdditionalTransform");
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Node::*)(const cc::AffineTransform&)>(&cc::Node::setAdditionalTransform));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Node::*)(const cc::Mat4&)>(&cc::Node::setAdditionalTransform));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setAnchorPoint");
	LUA_TRY_INVOKE(1, &cc::Node::setAnchorPoint);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setCameraMask(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCameraMask");
	LUA_TRY_INVOKE(2, &cc::Node::setCameraMask);
	LUA_TRY_INVOKE(1, ([](cc::Node* obj,unsigned short arg0){{return obj->setCameraMask(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_setCascadeColorEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCascadeColorEnabled");
	LUA_TRY_INVOKE(1, &cc::Node::setCascadeColorEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setCascadeOpacityEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setCascadeOpacityEnabled");
	LUA_TRY_INVOKE(1, &cc::Node::setCascadeOpacityEnabled);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setColor");
	LUA_TRY_INVOKE(1, &cc::Node::setColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setContentSize");
	LUA_TRY_INVOKE(1, &cc::Node::setContentSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setEventDispatcher(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setEventDispatcher");
	LUA_TRY_INVOKE(1, &cc::Node::setEventDispatcher);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setGlobalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setGlobalZOrder");
	LUA_TRY_INVOKE(1, &cc::Node::setGlobalZOrder);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setIgnoreAnchorPointForPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setIgnoreAnchorPointForPosition");
	LUA_TRY_INVOKE(1, &cc::Node::setIgnoreAnchorPointForPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setLocalZOrder(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setLocalZOrder");
	LUA_TRY_INVOKE(1, &cc::Node::setLocalZOrder);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setName");
	LUA_TRY_INVOKE(1, &cc::Node::setName);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setNodeToParentTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setNodeToParentTransform");
	LUA_TRY_INVOKE(1, &cc::Node::setNodeToParentTransform);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setNormalizedPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setNormalizedPosition");
	LUA_TRY_INVOKE(1, &cc::Node::setNormalizedPosition);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOnEnterCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnEnterCallback");
	LUA_TRY_INVOKE(1, &cc::Node::setOnEnterCallback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOnEnterTransitionDidFinishCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnEnterTransitionDidFinishCallback");
	LUA_TRY_INVOKE(1, &cc::Node::setOnEnterTransitionDidFinishCallback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOnExitCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnExitCallback");
	LUA_TRY_INVOKE(1, &cc::Node::setOnExitCallback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOnExitTransitionDidStartCallback(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOnExitTransitionDidStartCallback");
	LUA_TRY_INVOKE(1, &cc::Node::setOnExitTransitionDidStartCallback);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOpacity");
	LUA_TRY_INVOKE(1, &cc::Node::setOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setOpacityModifyRGB(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setOpacityModifyRGB");
	LUA_TRY_INVOKE(1, &cc::Node::setOpacityModifyRGB);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setParent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setParent");
	LUA_TRY_INVOKE(1, &cc::Node::setParent);
	LUA_INVOKE_FOOTER("1");
}
#if CC_USE_PHYSICS
int lua_cc_Node_setPhysicsBody_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPhysicsBody");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(cc::PhysicsBody*)>(&cc::Node::setPhysicsBody));
	LUA_INVOKE_FOOTER("1");
}
#endif
int lua_cc_Node_setPosition(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPosition");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::Node::*)(float, float)>(&cc::Node::setPosition)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(const cc::Vec2&)>(&cc::Node::setPosition));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_setPosition3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPosition3D");
	LUA_TRY_INVOKE(1, &cc::Node::setPosition3D);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setPositionNormalized(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionNormalized");
	LUA_TRY_INVOKE(1, &cc::Node::setPositionNormalized);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setPositionX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionX");
	LUA_TRY_INVOKE(1, &cc::Node::setPositionX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setPositionY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionY");
	LUA_TRY_INVOKE(1, &cc::Node::setPositionY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setPositionZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setPositionZ");
	LUA_TRY_INVOKE(1, &cc::Node::setPositionZ);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setProgramState(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setProgramState");
	LUA_TRY_INVOKE_R_OVERLOAD(1, static_cast<bool(cc::Node::*)(cc::IntrusivePtr<cc::backend::ProgramState>)>(&cc::Node::setProgramState));
	LUA_TRY_INVOKE_OVERLOAD(1, static_cast<void(cc::Node::*)(uint32_t)>(&cc::Node::setProgramState));
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setProgramStateWithRegistry(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setProgramStateWithRegistry");
	LUA_TRY_INVOKE(2, &cc::Node::setProgramStateWithRegistry);
	LUA_INVOKE_FOOTER("2");
}
int lua_cc_Node_setRotation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotation");
	LUA_TRY_INVOKE(1, &cc::Node::setRotation);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setRotation3D(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotation3D");
	LUA_TRY_INVOKE(1, &cc::Node::setRotation3D);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setRotationQuat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationQuat");
	LUA_TRY_INVOKE(1, &cc::Node::setRotationQuat);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setRotationSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationSkewX");
	LUA_TRY_INVOKE(1, &cc::Node::setRotationSkewX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setRotationSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setRotationSkewY");
	LUA_TRY_INVOKE(1, &cc::Node::setRotationSkewY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setScale(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScale");
	LUA_TRY_INVOKE(2, (static_cast<void(cc::Node::*)(float, float)>(&cc::Node::setScale)));
	LUA_TRY_INVOKE(1, static_cast<void(cc::Node::*)(float)>(&cc::Node::setScale));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cc_Node_setScaleX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleX");
	LUA_TRY_INVOKE(1, &cc::Node::setScaleX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setScaleY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleY");
	LUA_TRY_INVOKE(1, &cc::Node::setScaleY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setScaleZ(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScaleZ");
	LUA_TRY_INVOKE(1, &cc::Node::setScaleZ);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setScheduler(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setScheduler");
	LUA_TRY_INVOKE(1, &cc::Node::setScheduler);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setSkewX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setSkewX");
	LUA_TRY_INVOKE(1, &cc::Node::setSkewX);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setSkewY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setSkewY");
	LUA_TRY_INVOKE(1, &cc::Node::setSkewY);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setTag");
	LUA_TRY_INVOKE(1, &cc::Node::setTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setUserObject(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setUserObject");
	LUA_TRY_INVOKE(1, &cc::Node::setUserObject);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_setVisible(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:setVisible");
	LUA_TRY_INVOKE(1, &cc::Node::setVisible);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_sortAllChildren(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:sortAllChildren");
	LUA_TRY_INVOKE(0, &cc::Node::sortAllChildren);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_stopAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAction");
	LUA_TRY_INVOKE(1, &cc::Node::stopAction);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_stopActionByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopActionByTag");
	LUA_TRY_INVOKE(1, &cc::Node::stopActionByTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_stopActionsByFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopActionsByFlags");
	LUA_TRY_INVOKE(1, &cc::Node::stopActionsByFlags);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_stopAllActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAllActions");
	LUA_TRY_INVOKE(0, &cc::Node::stopAllActions);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_stopAllActionsByTag(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:stopAllActionsByTag");
	LUA_TRY_INVOKE(1, &cc::Node::stopAllActionsByTag);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:update");
	LUA_TRY_INVOKE(1, &cc::Node::update);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_updateDisplayedColor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateDisplayedColor");
	LUA_TRY_INVOKE(1, &cc::Node::updateDisplayedColor);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_updateDisplayedOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateDisplayedOpacity");
	LUA_TRY_INVOKE(1, &cc::Node::updateDisplayedOpacity);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_updateOrderOfArrival(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateOrderOfArrival");
	LUA_TRY_INVOKE(0, &cc::Node::updateOrderOfArrival);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_updateProgramStateTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateProgramStateTexture");
	LUA_TRY_INVOKE(1, &cc::Node::updateProgramStateTexture);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Node_updateTransform(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:updateTransform");
	LUA_TRY_INVOKE(0, &cc::Node::updateTransform);
	LUA_INVOKE_FOOTER("0");
}
int lua_cc_Node_visit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Node", "cc.Node:visit");
	LUA_TRY_INVOKE(3, (static_cast<void(cc::Node::*)(cc::Renderer*, const cc::Mat4&, uint32_t)>(&cc::Node::visit)));
	LUA_TRY_INVOKE(0, static_cast<void(cc::Node::*)()>(&cc::Node::visit));
	LUA_INVOKE_FOOTER("0,3");
}
int lua_cc_Node_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Node", "cc.Node:create");
	LUA_TRY_INVOKE_R(0, &cc::Node::create);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Node_getAttachedNodeCount(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Node", "cc.Node:getAttachedNodeCount");
	LUA_TRY_INVOKE_R(0, &cc::Node::getAttachedNodeCount);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccNode(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Node, "Node", "cc.Node",
		cc::Node, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("_setLocalZOrder", lua_cc_Node__setLocalZOrder);
	LUA_METHOD("addChild", lua_cc_Node_addChild_1);
	LUA_METHOD("addComponent", lua_cc_Node_addComponent);
	LUA_METHOD("applyMaskOnEnter", lua_cc_Node_applyMaskOnEnter);
	LUA_METHOD("cleanup", lua_cc_Node_cleanup);
	LUA_METHOD("convertToNodeSpace", lua_cc_Node_convertToNodeSpace);
	LUA_METHOD("convertToNodeSpaceAR", lua_cc_Node_convertToNodeSpaceAR);
	LUA_METHOD("convertToWorldSpace", lua_cc_Node_convertToWorldSpace);
	LUA_METHOD("convertToWorldSpaceAR", lua_cc_Node_convertToWorldSpaceAR);
	LUA_METHOD("convertTouchToNodeSpace", lua_cc_Node_convertTouchToNodeSpace);
	LUA_METHOD("convertTouchToNodeSpaceAR", lua_cc_Node_convertTouchToNodeSpaceAR);
	LUA_METHOD("draw", lua_cc_Node_draw);
	LUA_METHOD("enumerateChildren", lua_cc_Node_enumerateChildren);
	LUA_METHOD("getActionByTag", lua_cc_Node_getActionByTag);
	LUA_METHOD("getActionManager", lua_cc_Node_getActionManager);
	LUA_METHOD("getAnchorPoint", lua_cc_Node_getAnchorPoint);
	LUA_METHOD("getAnchorPointInPoints", lua_cc_Node_getAnchorPointInPoints);
	LUA_METHOD("getBoundingBox", lua_cc_Node_getBoundingBox);
	LUA_METHOD("getCameraMask", lua_cc_Node_getCameraMask);
	LUA_METHOD("getChildByName", lua_cc_Node_getChildByName);
	LUA_METHOD("getChildByTag", lua_cc_Node_getChildByTag);
	LUA_METHOD("getChildren", lua_cc_Node_getChildren);
	LUA_METHOD("getChildrenCount", lua_cc_Node_getChildrenCount);
	LUA_METHOD("getColor", lua_cc_Node_getColor);
	LUA_METHOD("getComponent", lua_cc_Node_getComponent);
	LUA_METHOD("getContentSize", lua_cc_Node_getContentSize);
	LUA_METHOD("getDescription", lua_cc_Node_getDescription);
	LUA_METHOD("getDisplayedColor", lua_cc_Node_getDisplayedColor);
	LUA_METHOD("getDisplayedOpacity", lua_cc_Node_getDisplayedOpacity);
	LUA_METHOD("getEventDispatcher", lua_cc_Node_getEventDispatcher);
	LUA_METHOD("getGlobalZOrder", lua_cc_Node_getGlobalZOrder);
	LUA_METHOD("getLocalZOrder", lua_cc_Node_getLocalZOrder);
	LUA_METHOD("getName", lua_cc_Node_getName);
	LUA_METHOD("getNodeToParentAffineTransform", lua_cc_Node_getNodeToParentAffineTransform);
	LUA_METHOD("getNodeToParentTransform", lua_cc_Node_getNodeToParentTransform);
	LUA_METHOD("getNodeToWorldAffineTransform", lua_cc_Node_getNodeToWorldAffineTransform);
	LUA_METHOD("getNodeToWorldTransform", lua_cc_Node_getNodeToWorldTransform);
	LUA_METHOD("getNormalizedPosition", lua_cc_Node_getNormalizedPosition);
	LUA_METHOD("getNumberOfRunningActions", lua_cc_Node_getNumberOfRunningActions);
	LUA_METHOD("getNumberOfRunningActionsByTag", lua_cc_Node_getNumberOfRunningActionsByTag);
	LUA_METHOD("getOnEnterTransitionDidFinishCallback", lua_cc_Node_getOnEnterTransitionDidFinishCallback);
	LUA_METHOD("getOnExitTransitionDidStartCallback", lua_cc_Node_getOnExitTransitionDidStartCallback);
	LUA_METHOD("getOpacity", lua_cc_Node_getOpacity);
	LUA_METHOD("getParent", lua_cc_Node_getParent);
	LUA_METHOD("getParentToNodeAffineTransform", lua_cc_Node_getParentToNodeAffineTransform);
	LUA_METHOD("getParentToNodeTransform", lua_cc_Node_getParentToNodeTransform);
	#if CC_USE_PHYSICS
LUA_METHOD("getPhysicsBody", lua_cc_Node_getPhysicsBody_1);
#endif
	LUA_METHOD("getPosition", lua_cc_Node_getPosition_1);
	LUA_METHOD("getPosition3D", lua_cc_Node_getPosition3D);
	LUA_METHOD("getPositionNormalized", lua_cc_Node_getPositionNormalized);
	LUA_METHOD("getPositionX", lua_cc_Node_getPositionX);
	LUA_METHOD("getPositionY", lua_cc_Node_getPositionY);
	LUA_METHOD("getPositionZ", lua_cc_Node_getPositionZ);
	LUA_METHOD("getProgramState", lua_cc_Node_getProgramState);
	LUA_METHOD("getRotation", lua_cc_Node_getRotation);
	LUA_METHOD("getRotation3D", lua_cc_Node_getRotation3D);
	LUA_METHOD("getRotationSkewX", lua_cc_Node_getRotationSkewX);
	LUA_METHOD("getRotationSkewY", lua_cc_Node_getRotationSkewY);
	LUA_METHOD("getScale", lua_cc_Node_getScale);
	LUA_METHOD("getScaleX", lua_cc_Node_getScaleX);
	LUA_METHOD("getScaleY", lua_cc_Node_getScaleY);
	LUA_METHOD("getScaleZ", lua_cc_Node_getScaleZ);
	LUA_METHOD("getScene", lua_cc_Node_getScene);
	LUA_METHOD("getScheduler", lua_cc_Node_getScheduler);
	LUA_METHOD("getSkewX", lua_cc_Node_getSkewX);
	LUA_METHOD("getSkewY", lua_cc_Node_getSkewY);
	LUA_METHOD("getTag", lua_cc_Node_getTag);
	LUA_METHOD("getWorldPosition", lua_cc_Node_getWorldPosition);
	LUA_METHOD("getWorldToNodeAffineTransform", lua_cc_Node_getWorldToNodeAffineTransform);
	LUA_METHOD("getWorldToNodeTransform", lua_cc_Node_getWorldToNodeTransform);
	LUA_METHOD("hitTest", lua_cc_Node_hitTest);
	LUA_METHOD("init", lua_cc_Node_init);
	LUA_METHOD("initLayer", lua_cc_Node_initLayer);
	LUA_METHOD("isCascadeColorEnabled", lua_cc_Node_isCascadeColorEnabled);
	LUA_METHOD("isCascadeOpacityEnabled", lua_cc_Node_isCascadeOpacityEnabled);
	LUA_METHOD("isIgnoreAnchorPointForPosition", lua_cc_Node_isIgnoreAnchorPointForPosition);
	LUA_METHOD("isOpacityModifyRGB", lua_cc_Node_isOpacityModifyRGB);
	LUA_METHOD("isRunning", lua_cc_Node_isRunning);
	LUA_METHOD("isScheduled", lua_cc_Node_isScheduled_1);
	LUA_METHOD("isVisible", lua_cc_Node_isVisible);
	LUA_METHOD("pause", lua_cc_Node_pause);
	LUA_METHOD("removeAllComponents", lua_cc_Node_removeAllComponents);
	LUA_METHOD("removeChild", lua_cc_Node_removeChild);
	LUA_METHOD("removeChildByName", lua_cc_Node_removeChildByName);
	LUA_METHOD("removeChildByTag", lua_cc_Node_removeChildByTag);
	LUA_METHOD("removeComponent", lua_cc_Node_removeComponent);
	LUA_METHOD("reorderChild", lua_cc_Node_reorderChild);
	LUA_METHOD("resetChild", lua_cc_Node_resetChild);
	LUA_METHOD("resume", lua_cc_Node_resume);
	LUA_METHOD("runAction", lua_cc_Node_runAction);
	LUA_METHOD("setActionManager", lua_cc_Node_setActionManager);
	LUA_METHOD("setAdditionalTransform", lua_cc_Node_setAdditionalTransform_1);
	LUA_METHOD("setAnchorPoint", lua_cc_Node_setAnchorPoint);
	LUA_METHOD("setCameraMask", lua_cc_Node_setCameraMask);
	LUA_METHOD("setCascadeColorEnabled", lua_cc_Node_setCascadeColorEnabled);
	LUA_METHOD("setCascadeOpacityEnabled", lua_cc_Node_setCascadeOpacityEnabled);
	LUA_METHOD("setColor", lua_cc_Node_setColor);
	LUA_METHOD("setContentSize", lua_cc_Node_setContentSize);
	LUA_METHOD("setEventDispatcher", lua_cc_Node_setEventDispatcher);
	LUA_METHOD("setGlobalZOrder", lua_cc_Node_setGlobalZOrder);
	LUA_METHOD("setIgnoreAnchorPointForPosition", lua_cc_Node_setIgnoreAnchorPointForPosition);
	LUA_METHOD("setLocalZOrder", lua_cc_Node_setLocalZOrder);
	LUA_METHOD("setName", lua_cc_Node_setName);
	LUA_METHOD("setNodeToParentTransform", lua_cc_Node_setNodeToParentTransform);
	LUA_METHOD("setNormalizedPosition", lua_cc_Node_setNormalizedPosition);
	LUA_METHOD("setOnEnterCallback", lua_cc_Node_setOnEnterCallback);
	LUA_METHOD("setOnEnterTransitionDidFinishCallback", lua_cc_Node_setOnEnterTransitionDidFinishCallback);
	LUA_METHOD("setOnExitCallback", lua_cc_Node_setOnExitCallback);
	LUA_METHOD("setOnExitTransitionDidStartCallback", lua_cc_Node_setOnExitTransitionDidStartCallback);
	LUA_METHOD("setOpacity", lua_cc_Node_setOpacity);
	LUA_METHOD("setOpacityModifyRGB", lua_cc_Node_setOpacityModifyRGB);
	LUA_METHOD("setParent", lua_cc_Node_setParent);
	#if CC_USE_PHYSICS
LUA_METHOD("setPhysicsBody", lua_cc_Node_setPhysicsBody_1);
#endif
	LUA_METHOD("setPosition", lua_cc_Node_setPosition);
	LUA_METHOD("setPosition3D", lua_cc_Node_setPosition3D);
	LUA_METHOD("setPositionNormalized", lua_cc_Node_setPositionNormalized);
	LUA_METHOD("setPositionX", lua_cc_Node_setPositionX);
	LUA_METHOD("setPositionY", lua_cc_Node_setPositionY);
	LUA_METHOD("setPositionZ", lua_cc_Node_setPositionZ);
	LUA_METHOD("setProgramState", lua_cc_Node_setProgramState);
	LUA_METHOD("setProgramStateWithRegistry", lua_cc_Node_setProgramStateWithRegistry);
	LUA_METHOD("setRotation", lua_cc_Node_setRotation);
	LUA_METHOD("setRotation3D", lua_cc_Node_setRotation3D);
	LUA_METHOD("setRotationQuat", lua_cc_Node_setRotationQuat);
	LUA_METHOD("setRotationSkewX", lua_cc_Node_setRotationSkewX);
	LUA_METHOD("setRotationSkewY", lua_cc_Node_setRotationSkewY);
	LUA_METHOD("setScale", lua_cc_Node_setScale);
	LUA_METHOD("setScaleX", lua_cc_Node_setScaleX);
	LUA_METHOD("setScaleY", lua_cc_Node_setScaleY);
	LUA_METHOD("setScaleZ", lua_cc_Node_setScaleZ);
	LUA_METHOD("setScheduler", lua_cc_Node_setScheduler);
	LUA_METHOD("setSkewX", lua_cc_Node_setSkewX);
	LUA_METHOD("setSkewY", lua_cc_Node_setSkewY);
	LUA_METHOD("setTag", lua_cc_Node_setTag);
	LUA_METHOD("setUserObject", lua_cc_Node_setUserObject);
	LUA_METHOD("setVisible", lua_cc_Node_setVisible);
	LUA_METHOD("sortAllChildren", lua_cc_Node_sortAllChildren);
	LUA_METHOD("stopAction", lua_cc_Node_stopAction);
	LUA_METHOD("stopActionByTag", lua_cc_Node_stopActionByTag);
	LUA_METHOD("stopActionsByFlags", lua_cc_Node_stopActionsByFlags);
	LUA_METHOD("stopAllActions", lua_cc_Node_stopAllActions);
	LUA_METHOD("stopAllActionsByTag", lua_cc_Node_stopAllActionsByTag);
	LUA_METHOD("update", lua_cc_Node_update);
	LUA_METHOD("updateDisplayedColor", lua_cc_Node_updateDisplayedColor);
	LUA_METHOD("updateDisplayedOpacity", lua_cc_Node_updateDisplayedOpacity);
	LUA_METHOD("updateOrderOfArrival", lua_cc_Node_updateOrderOfArrival);
	LUA_METHOD("updateProgramStateTexture", lua_cc_Node_updateProgramStateTexture);
	LUA_METHOD("updateTransform", lua_cc_Node_updateTransform);
	LUA_METHOD("visit", lua_cc_Node_visit);
	LUA_METHOD("create", lua_cc_Node_create);
	LUA_METHOD("getAttachedNodeCount", lua_cc_Node_getAttachedNodeCount);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cc_Scene_getDefaultCamera(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getDefaultCamera");
	LUA_TRY_INVOKE_R(0, &cc::Scene::getDefaultCamera);
	LUA_INVOKE_FOOTER("0");
}
#if CC_USE_NAVMESH
int lua_cc_Scene_getNavMesh_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getNavMesh");
	LUA_TRY_INVOKE_R(0, static_cast<cc::NavMesh*(cc::Scene::*)()const>(&cc::Scene::getNavMesh));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
int lua_cc_Scene_getPhysics3DWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysics3DWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cc::Physics3DWorld*(cc::Scene::*)()>(&cc::Scene::getPhysics3DWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS
int lua_cc_Scene_getPhysicsWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:getPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<cc::PhysicsWorld*(cc::Scene::*)()const>(&cc::Scene::getPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cc_Scene_initPhysicsWorld_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initPhysicsWorld");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::Scene::*)()>(&cc::Scene::initPhysicsWorld));
	LUA_INVOKE_FOOTER("0");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cc_Scene_initWithPhysics_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithPhysics");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cc::Scene::*)()>(&cc::Scene::initWithPhysics));
	LUA_INVOKE_FOOTER("0");
}
#endif
int lua_cc_Scene_initWithSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:initWithSize");
	LUA_TRY_INVOKE_R(1, &cc::Scene::initWithSize);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Scene_onProjectionChanged(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:onProjectionChanged");
	LUA_TRY_INVOKE(1, &cc::Scene::onProjectionChanged);
	LUA_INVOKE_FOOTER("1");
}
int lua_cc_Scene_setCameraOrderDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setCameraOrderDirty");
	LUA_TRY_INVOKE(0, &cc::Scene::setCameraOrderDirty);
	LUA_INVOKE_FOOTER("0");
}
#if CC_USE_NAVMESH
int lua_cc_Scene_setNavMesh_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMesh");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Scene::*)(cc::NavMesh*)>(&cc::Scene::setNavMesh));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_NAVMESH
int lua_cc_Scene_setNavMeshDebugCamera_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setNavMeshDebugCamera");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Scene::*)(cc::Camera*)>(&cc::Scene::setNavMeshDebugCamera));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
int lua_cc_Scene_setPhysics3DDebugCamera_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:setPhysics3DDebugCamera");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Scene::*)(cc::Camera*)>(&cc::Scene::setPhysics3DDebugCamera));
	LUA_INVOKE_FOOTER("1");
}
#endif
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH
int lua_cc_Scene_stepPhysicsAndNavigation_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Scene", "cc.Scene:stepPhysicsAndNavigation");
	LUA_TRY_INVOKE(1, static_cast<void(cc::Scene::*)(float)>(&cc::Scene::stepPhysicsAndNavigation));
	LUA_INVOKE_FOOTER("1");
}
#endif
int lua_cc_Scene_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:create");
	LUA_TRY_INVOKE_R(0, &cc::Scene::create);
	LUA_SINVOKE_FOOTER("0");
}
#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
int lua_cc_Scene_createWithPhysics_1(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithPhysics");
	LUA_TRY_INVOKE_R(0, static_cast<cc::IntrusivePtr<cc::Scene>(*)()>(&cc::Scene::createWithPhysics));
	LUA_SINVOKE_FOOTER("0");
}
#endif
int lua_cc_Scene_createWithSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Scene", "cc.Scene:createWithSize");
	LUA_TRY_INVOKE_R(1, &cc::Scene::createWithSize);
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccScene(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cc::Scene, "Scene", "cc.Scene",
		cc::Scene, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getDefaultCamera", lua_cc_Scene_getDefaultCamera);
	#if CC_USE_NAVMESH
LUA_METHOD("getNavMesh", lua_cc_Scene_getNavMesh_1);
#endif
	#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
LUA_METHOD("getPhysics3DWorld", lua_cc_Scene_getPhysics3DWorld_1);
#endif
	#if CC_USE_PHYSICS
LUA_METHOD("getPhysicsWorld", lua_cc_Scene_getPhysicsWorld_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("initPhysicsWorld", lua_cc_Scene_initPhysicsWorld_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("initWithPhysics", lua_cc_Scene_initWithPhysics_1);
#endif
	LUA_METHOD("initWithSize", lua_cc_Scene_initWithSize);
	LUA_METHOD("onProjectionChanged", lua_cc_Scene_onProjectionChanged);
	LUA_METHOD("setCameraOrderDirty", lua_cc_Scene_setCameraOrderDirty);
	#if CC_USE_NAVMESH
LUA_METHOD("setNavMesh", lua_cc_Scene_setNavMesh_1);
#endif
	#if CC_USE_NAVMESH
LUA_METHOD("setNavMeshDebugCamera", lua_cc_Scene_setNavMeshDebugCamera_1);
#endif
	#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
LUA_METHOD("setPhysics3DDebugCamera", lua_cc_Scene_setPhysics3DDebugCamera_1);
#endif
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH
LUA_METHOD("stepPhysicsAndNavigation", lua_cc_Scene_stepPhysicsAndNavigation_1);
#endif
	LUA_METHOD("create", lua_cc_Scene_create);
	#if CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION)
LUA_METHOD("createWithPhysics", lua_cc_Scene_createWithPhysics_1);
#endif
	LUA_METHOD("createWithSize", lua_cc_Scene_createWithSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
extern int luaReg_Core_ccRef(lua_State* lua_S);
extern int luaReg_Core_ccConsole(lua_State* lua_S);
extern int luaReg_Core_ccEventListener(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerCustom(lua_State* lua_S);
extern int luaReg_Core_ccShaderCache(lua_State* lua_S);
extern int luaReg_Core_ccTexture2D(lua_State* lua_S);
extern int luaReg_Core_ccTouch(lua_State* lua_S);
extern int luaReg_Core_ccEvent(lua_State* lua_S);
extern int luaReg_Core_ccEventTouch(lua_State* lua_S);
extern int luaReg_Core_ccEventKeyboard(lua_State* lua_S);
extern int luaReg_Core_ccComponent(lua_State* lua_S);
extern int luaReg_Core_ccNode(lua_State* lua_S);
extern int luaReg_Core_ccScene(lua_State* lua_S);
int lua_cc_Display_getAllDisplayInfo(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Display", "cc.Display:getAllDisplayInfo");
	LUA_TRY_INVOKE_R(0, &cc::Display::getAllDisplayInfo);
	LUA_SINVOKE_FOOTER("0");
}
int lua_cc_Display_getDisplayInfo(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Display", "cc.Display:getDisplayInfo");
	LUA_TRY_INVOKE_R(1, &cc::Display::getDisplayInfo);
	LUA_SINVOKE_FOOTER("1");
}
int lua_cc_Display_getPrimaryDisplayInfo(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Display", "cc.Display:getPrimaryDisplayInfo");
	LUA_TRY_INVOKE_R(0, &cc::Display::getPrimaryDisplayInfo);
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccDisplay(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF(cc::Display, "Display", "cc.Display",
		nullptr, nullptr);
	LUA_METHOD("getAllDisplayInfo", lua_cc_Display_getAllDisplayInfo);
	LUA_METHOD("getDisplayInfo", lua_cc_Display_getDisplayInfo);
	LUA_METHOD("getPrimaryDisplayInfo", lua_cc_Display_getPrimaryDisplayInfo);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

extern int luaReg_Core_ccGLView(lua_State* lua_S);
extern int luaReg_Core_ccDirector(lua_State* lua_S);
extern int luaReg_Core_ccTimer(lua_State* lua_S);
extern int luaReg_Core_ccScheduler(lua_State* lua_S);
extern int luaReg_Core_ccAsyncTaskPool(lua_State* lua_S);
extern int luaReg_Core_ccAction(lua_State* lua_S);
extern int luaReg_Core_ccFiniteTimeAction(lua_State* lua_S);
extern int luaReg_Core_ccSpeed(lua_State* lua_S);
extern int luaReg_Core_ccFollow(lua_State* lua_S);
extern int luaReg_Core_ccImage(lua_State* lua_S);
extern int luaReg_Core_ccSpriteFrame(lua_State* lua_S);
extern int luaReg_Core_ccAnimationFrame(lua_State* lua_S);
extern int luaReg_Core_ccAnimation(lua_State* lua_S);
extern int luaReg_Core_ccActionInterval(lua_State* lua_S);
extern int luaReg_Core_ccSequence(lua_State* lua_S);
extern int luaReg_Core_ccRepeat(lua_State* lua_S);
extern int luaReg_Core_ccRepeatForever(lua_State* lua_S);
extern int luaReg_Core_ccSpawn(lua_State* lua_S);
extern int luaReg_Core_ccRotateTo(lua_State* lua_S);
extern int luaReg_Core_ccRotateBy(lua_State* lua_S);
extern int luaReg_Core_ccMoveBy(lua_State* lua_S);
extern int luaReg_Core_ccMoveTo(lua_State* lua_S);
extern int luaReg_Core_ccSkewTo(lua_State* lua_S);
extern int luaReg_Core_ccSkewBy(lua_State* lua_S);
extern int luaReg_Core_ccJumpBy(lua_State* lua_S);
extern int luaReg_Core_ccJumpTo(lua_State* lua_S);
extern int luaReg_Core_ccBezierBy(lua_State* lua_S);
extern int luaReg_Core_ccBezierTo(lua_State* lua_S);
extern int luaReg_Core_ccScaleTo(lua_State* lua_S);
extern int luaReg_Core_ccScaleBy(lua_State* lua_S);
extern int luaReg_Core_ccBlink(lua_State* lua_S);
extern int luaReg_Core_ccFadeTo(lua_State* lua_S);
extern int luaReg_Core_ccFadeIn(lua_State* lua_S);
extern int luaReg_Core_ccFadeOut(lua_State* lua_S);
extern int luaReg_Core_ccTintTo(lua_State* lua_S);
extern int luaReg_Core_ccTintBy(lua_State* lua_S);
extern int luaReg_Core_ccDelayTime(lua_State* lua_S);
extern int luaReg_Core_ccAnimate(lua_State* lua_S);
extern int luaReg_Core_ccTargetedAction(lua_State* lua_S);
extern int luaReg_Core_ccActionFloat(lua_State* lua_S);
extern int luaReg_Core_ccUserDefault(lua_State* lua_S);
extern int luaReg_Core_ccAppDirectory(lua_State* lua_S);
extern int luaReg_Core_ccDirectoryStatus(lua_State* lua_S);
extern int luaReg_Core_ccFileUtils(lua_State* lua_S);
extern int luaReg_Core_ccEventAcceleration(lua_State* lua_S);
extern int luaReg_Core_ccEventCustom(lua_State* lua_S);
extern int luaReg_Core_ccEventDispatcher(lua_State* lua_S);
extern int luaReg_Core_ccEventFocus(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerFocus(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerKeyboard(lua_State* lua_S);
extern int luaReg_Core_ccEventMouse(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerMouse(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerTouchOneByOne(lua_State* lua_S);
extern int luaReg_Core_ccEventListenerTouchAllAtOnce(lua_State* lua_S);
extern int luaReg_Core_ccActionCamera(lua_State* lua_S);
extern int luaReg_Core_ccOrbitCamera(lua_State* lua_S);
extern int luaReg_Core_ccCardinalSplineTo(lua_State* lua_S);
extern int luaReg_Core_ccCardinalSplineBy(lua_State* lua_S);
extern int luaReg_Core_ccCatmullRomTo(lua_State* lua_S);
extern int luaReg_Core_ccCatmullRomBy(lua_State* lua_S);
extern int luaReg_Core_ccActionEase(lua_State* lua_S);
extern int luaReg_Core_ccEaseRateAction(lua_State* lua_S);
extern int luaReg_Core_ccEaseExponentialIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseExponentialOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseExponentialInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseSineIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseSineOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseSineInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseBounce(lua_State* lua_S);
extern int luaReg_Core_ccEaseBounceIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseBounceOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseBounceInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseBackIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseBackOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseBackInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuadraticActionIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuadraticActionOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuadraticActionInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuarticActionIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuarticActionOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuarticActionInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuinticActionIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuinticActionOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseQuinticActionInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseCircleActionIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseCircleActionOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseCircleActionInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseCubicActionIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseCubicActionOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseCubicActionInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseElastic(lua_State* lua_S);
extern int luaReg_Core_ccEaseElasticIn(lua_State* lua_S);
extern int luaReg_Core_ccEaseElasticOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseElasticInOut(lua_State* lua_S);
extern int luaReg_Core_ccEaseBezierAction(lua_State* lua_S);
extern int luaReg_Core_ccActionInstant(lua_State* lua_S);
extern int luaReg_Core_ccShow(lua_State* lua_S);
extern int luaReg_Core_ccHide(lua_State* lua_S);
extern int luaReg_Core_ccToggleVisibility(lua_State* lua_S);
extern int luaReg_Core_ccRemoveSelf(lua_State* lua_S);
extern int luaReg_Core_ccFlipX(lua_State* lua_S);
extern int luaReg_Core_ccFlipY(lua_State* lua_S);
extern int luaReg_Core_ccPlace(lua_State* lua_S);
extern int luaReg_Core_ccCallFunc(lua_State* lua_S);
extern int luaReg_Core_ccGridAction(lua_State* lua_S);
extern int luaReg_Core_ccGrid3DAction(lua_State* lua_S);
extern int luaReg_Core_ccTiledGrid3DAction(lua_State* lua_S);
extern int luaReg_Core_ccStopGrid(lua_State* lua_S);
extern int luaReg_Core_ccReuseGrid(lua_State* lua_S);
extern int luaReg_Core_ccWaves3D(lua_State* lua_S);
extern int luaReg_Core_ccFlipX3D(lua_State* lua_S);
extern int luaReg_Core_ccFlipY3D(lua_State* lua_S);
extern int luaReg_Core_ccLens3D(lua_State* lua_S);
extern int luaReg_Core_ccRipple3D(lua_State* lua_S);
extern int luaReg_Core_ccShaky3D(lua_State* lua_S);
extern int luaReg_Core_ccLiquid(lua_State* lua_S);
extern int luaReg_Core_ccWaves(lua_State* lua_S);
extern int luaReg_Core_ccTwirl(lua_State* lua_S);
extern int luaReg_Core_ccActionManager(lua_State* lua_S);
extern int luaReg_Core_ccPageTurn3D(lua_State* lua_S);
extern int luaReg_Core_ccProgressTo(lua_State* lua_S);
extern int luaReg_Core_ccProgressFromTo(lua_State* lua_S);
extern int luaReg_Core_ccShakyTiles3D(lua_State* lua_S);
extern int luaReg_Core_ccShatteredTiles3D(lua_State* lua_S);
extern int luaReg_Core_ccShuffleTiles(lua_State* lua_S);
extern int luaReg_Core_ccFadeOutTRTiles(lua_State* lua_S);
extern int luaReg_Core_ccFadeOutBLTiles(lua_State* lua_S);
extern int luaReg_Core_ccFadeOutUpTiles(lua_State* lua_S);
extern int luaReg_Core_ccFadeOutDownTiles(lua_State* lua_S);
extern int luaReg_Core_ccTurnOffTiles(lua_State* lua_S);
extern int luaReg_Core_ccWavesTiles3D(lua_State* lua_S);
extern int luaReg_Core_ccJumpTiles3D(lua_State* lua_S);
extern int luaReg_Core_ccSplitRows(lua_State* lua_S);
extern int luaReg_Core_ccSplitCols(lua_State* lua_S);
extern int luaReg_Core_ccActionTween(lua_State* lua_S);
extern int luaReg_Core_ccAtlasNode(lua_State* lua_S);
extern int luaReg_Core_ccClippingNode(lua_State* lua_S);
extern int luaReg_Core_ccClippingRectangleNode(lua_State* lua_S);
extern int luaReg_Core_ccDrawNode(lua_State* lua_S);
extern int luaReg_Core_ccFontAtlas(lua_State* lua_S);
extern int luaReg_Core_ccFontRasterMode(lua_State* lua_S);
extern int luaReg_Core_ccGlyphRenderPolicy(lua_State* lua_S);
extern int luaReg_Core_ccGlyphStatus(lua_State* lua_S);
extern int luaReg_Core_ccGlyphTicket(lua_State* lua_S);
extern int luaReg_Core_ccLabel(lua_State* lua_S);
extern int luaReg_Core_ccLabelAtlas(lua_State* lua_S);
extern int luaReg_Core_ccSprite(lua_State* lua_S);
extern int luaReg_Core_ccLayer(lua_State* lua_S);
extern int luaReg_Core_ccLayerColor(lua_State* lua_S);
extern int luaReg_Core_ccLayerGradient(lua_State* lua_S);
extern int luaReg_Core_ccLayerRadialGradient(lua_State* lua_S);
extern int luaReg_Core_ccLayerMultiplex(lua_State* lua_S);
extern int luaReg_Core_ccMenuItem(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemLabel(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemAtlasFont(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemFont(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemSprite(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemImage(lua_State* lua_S);
extern int luaReg_Core_ccMenuItemToggle(lua_State* lua_S);
extern int luaReg_Core_ccMenu(lua_State* lua_S);
extern int luaReg_Core_ccMotionStreak(lua_State* lua_S);
extern int luaReg_Core_ccNodeGrid(lua_State* lua_S);
extern int luaReg_Core_ccParticleBatchNode(lua_State* lua_S);
extern int luaReg_Core_ccSpriteFrameCache(lua_State* lua_S);
extern int luaReg_Core_ccParticleEmissionMaskCache(lua_State* lua_S);
extern int luaReg_Core_ccParticleSystem(lua_State* lua_S);
extern int luaReg_Core_ccParticleSystemQuad(lua_State* lua_S);
extern int luaReg_Core_ccParticleFire(lua_State* lua_S);
extern int luaReg_Core_ccParticleFireworks(lua_State* lua_S);
extern int luaReg_Core_ccParticleSun(lua_State* lua_S);
extern int luaReg_Core_ccParticleGalaxy(lua_State* lua_S);
extern int luaReg_Core_ccParticleFlower(lua_State* lua_S);
extern int luaReg_Core_ccParticleMeteor(lua_State* lua_S);
extern int luaReg_Core_ccParticleSpiral(lua_State* lua_S);
extern int luaReg_Core_ccParticleExplosion(lua_State* lua_S);
extern int luaReg_Core_ccParticleSmoke(lua_State* lua_S);
extern int luaReg_Core_ccParticleSnow(lua_State* lua_S);
extern int luaReg_Core_ccParticleRain(lua_State* lua_S);
extern int luaReg_Core_ccProgressTimer(lua_State* lua_S);
extern int luaReg_Core_ccProtectedNode(lua_State* lua_S);
extern int luaReg_Core_ccRenderTexture(lua_State* lua_S);
extern int luaReg_Core_ccTransitionScene(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSceneOriented(lua_State* lua_S);
extern int luaReg_Core_ccTransitionRotoZoom(lua_State* lua_S);
extern int luaReg_Core_ccTransitionJumpZoom(lua_State* lua_S);
extern int luaReg_Core_ccTransitionMoveInL(lua_State* lua_S);
extern int luaReg_Core_ccTransitionMoveInR(lua_State* lua_S);
extern int luaReg_Core_ccTransitionMoveInT(lua_State* lua_S);
extern int luaReg_Core_ccTransitionMoveInB(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSlideInL(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSlideInR(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSlideInB(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSlideInT(lua_State* lua_S);
extern int luaReg_Core_ccTransitionShrinkGrow(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFlipX(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFlipY(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFlipAngular(lua_State* lua_S);
extern int luaReg_Core_ccTransitionZoomFlipX(lua_State* lua_S);
extern int luaReg_Core_ccTransitionZoomFlipY(lua_State* lua_S);
extern int luaReg_Core_ccTransitionZoomFlipAngular(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFade(lua_State* lua_S);
extern int luaReg_Core_ccTransitionCrossFade(lua_State* lua_S);
extern int luaReg_Core_ccTransitionTurnOffTiles(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSplitCols(lua_State* lua_S);
extern int luaReg_Core_ccTransitionSplitRows(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFadeTR(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFadeBL(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFadeUp(lua_State* lua_S);
extern int luaReg_Core_ccTransitionFadeDown(lua_State* lua_S);
extern int luaReg_Core_ccTransitionPageTurn(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgress(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressRadialCCW(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressRadialCW(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressHorizontal(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressVertical(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressInOut(lua_State* lua_S);
extern int luaReg_Core_ccTransitionProgressOutIn(lua_State* lua_S);
extern int luaReg_Core_ccCamera(lua_State* lua_S);
extern int luaReg_Core_ccCameraBackgroundBrush(lua_State* lua_S);
extern int luaReg_Core_ccCameraBackgroundDepthBrush(lua_State* lua_S);
extern int luaReg_Core_ccCameraBackgroundColorBrush(lua_State* lua_S);
extern int luaReg_Core_ccCameraBackgroundSkyBoxBrush(lua_State* lua_S);
extern int luaReg_Core_ccGridBase(lua_State* lua_S);
extern int luaReg_Core_ccGrid3D(lua_State* lua_S);
extern int luaReg_Core_ccTiledGrid3D(lua_State* lua_S);
extern int luaReg_Core_ccBaseLight(lua_State* lua_S);
extern int luaReg_Core_ccDirectionLight(lua_State* lua_S);
extern int luaReg_Core_ccPointLight(lua_State* lua_S);
extern int luaReg_Core_ccSpotLight(lua_State* lua_S);
extern int luaReg_Core_ccAmbientLight(lua_State* lua_S);
extern int luaReg_Core_ccRenderState(lua_State* lua_S);
extern int luaReg_Core_ccTechnique(lua_State* lua_S);
extern int luaReg_Core_ccMaterial(lua_State* lua_S);
extern int luaReg_Core_ccPass(lua_State* lua_S);
extern int luaReg_Core_ccRenderer(lua_State* lua_S);
extern int luaReg_Core_ccTextureCache(lua_State* lua_S);
extern int luaReg_Core_ccDevice(lua_State* lua_S);
extern int luaReg_Core_ccApplication(lua_State* lua_S);
extern int luaReg_Core_ccGLViewImpl(lua_State* lua_S);
extern int luaReg_Core_ccAnimationCache(lua_State* lua_S);
extern int luaReg_Core_ccSpriteBatchNode(lua_State* lua_S);
extern int luaReg_Core_ccParallaxNode(lua_State* lua_S);
extern int luaReg_Core_ccTMXObjectGroup(lua_State* lua_S);
extern int luaReg_Core_ccTMXLayerInfo(lua_State* lua_S);
extern int luaReg_Core_ccTMXTilesetInfo(lua_State* lua_S);
extern int luaReg_Core_ccTMXMapInfo(lua_State* lua_S);
extern int luaReg_Core_ccTileMapAtlas(lua_State* lua_S);
extern int luaReg_Core_ccFastTMXLayer(lua_State* lua_S);
extern int luaReg_Core_ccTMXTileAnimTask(lua_State* lua_S);
extern int luaReg_Core_ccTMXTileAnimManager(lua_State* lua_S);
extern int luaReg_Core_ccFastTMXTiledMap(lua_State* lua_S);
extern int luaReg_Core_ccMotionStreak3D(lua_State* lua_S);
extern int luaReg_Core_ccComponentLua(lua_State* lua_S);

int register_all_cc_base_retained(lua_State* lua_S);

int register_all_cc_base(lua_State* lua_S)
{
	tolua_open(lua_S);
	luaReg_Core_ccRef(lua_S);
	luaReg_Core_ccConsole(lua_S);
	luaReg_Core_ccEventListener(lua_S);
	luaReg_Core_ccEventListenerCustom(lua_S);
	luaReg_Core_ccShaderCache(lua_S);
	luaReg_Core_ccTexture2D(lua_S);
	luaReg_Core_ccTouch(lua_S);
	luaReg_Core_ccEvent(lua_S);
	luaReg_Core_ccEventTouch(lua_S);
	luaReg_Core_ccEventKeyboard(lua_S);
	luaReg_Core_ccComponent(lua_S);
	luaReg_Core_ccNode(lua_S);
	luaReg_Core_ccScene(lua_S);
	luaReg_Core_ccDisplay(lua_S);
	luaReg_Core_ccGLView(lua_S);
	luaReg_Core_ccDirector(lua_S);
	luaReg_Core_ccTimer(lua_S);
	luaReg_Core_ccScheduler(lua_S);
	luaReg_Core_ccAsyncTaskPool(lua_S);
	luaReg_Core_ccAction(lua_S);
	luaReg_Core_ccFiniteTimeAction(lua_S);
	luaReg_Core_ccSpeed(lua_S);
	luaReg_Core_ccFollow(lua_S);
	luaReg_Core_ccImage(lua_S);
	luaReg_Core_ccSpriteFrame(lua_S);
	luaReg_Core_ccAnimationFrame(lua_S);
	luaReg_Core_ccAnimation(lua_S);
	luaReg_Core_ccActionInterval(lua_S);
	luaReg_Core_ccSequence(lua_S);
	luaReg_Core_ccRepeat(lua_S);
	luaReg_Core_ccRepeatForever(lua_S);
	luaReg_Core_ccSpawn(lua_S);
	luaReg_Core_ccRotateTo(lua_S);
	luaReg_Core_ccRotateBy(lua_S);
	luaReg_Core_ccMoveBy(lua_S);
	luaReg_Core_ccMoveTo(lua_S);
	luaReg_Core_ccSkewTo(lua_S);
	luaReg_Core_ccSkewBy(lua_S);
	luaReg_Core_ccJumpBy(lua_S);
	luaReg_Core_ccJumpTo(lua_S);
	luaReg_Core_ccBezierBy(lua_S);
	luaReg_Core_ccBezierTo(lua_S);
	luaReg_Core_ccScaleTo(lua_S);
	luaReg_Core_ccScaleBy(lua_S);
	luaReg_Core_ccBlink(lua_S);
	luaReg_Core_ccFadeTo(lua_S);
	luaReg_Core_ccFadeIn(lua_S);
	luaReg_Core_ccFadeOut(lua_S);
	luaReg_Core_ccTintTo(lua_S);
	luaReg_Core_ccTintBy(lua_S);
	luaReg_Core_ccDelayTime(lua_S);
	luaReg_Core_ccAnimate(lua_S);
	luaReg_Core_ccTargetedAction(lua_S);
	luaReg_Core_ccActionFloat(lua_S);
	luaReg_Core_ccUserDefault(lua_S);
	luaReg_Core_ccAppDirectory(lua_S);
	luaReg_Core_ccDirectoryStatus(lua_S);
	luaReg_Core_ccFileUtils(lua_S);
	luaReg_Core_ccEventAcceleration(lua_S);
	luaReg_Core_ccEventCustom(lua_S);
	luaReg_Core_ccEventDispatcher(lua_S);
	luaReg_Core_ccEventFocus(lua_S);
	luaReg_Core_ccEventListenerAcceleration(lua_S);
	luaReg_Core_ccEventListenerFocus(lua_S);
	luaReg_Core_ccEventListenerKeyboard(lua_S);
	luaReg_Core_ccEventMouse(lua_S);
	luaReg_Core_ccEventListenerMouse(lua_S);
	luaReg_Core_ccEventListenerTouchOneByOne(lua_S);
	luaReg_Core_ccEventListenerTouchAllAtOnce(lua_S);
	luaReg_Core_ccActionCamera(lua_S);
	luaReg_Core_ccOrbitCamera(lua_S);
	luaReg_Core_ccCardinalSplineTo(lua_S);
	luaReg_Core_ccCardinalSplineBy(lua_S);
	luaReg_Core_ccCatmullRomTo(lua_S);
	luaReg_Core_ccCatmullRomBy(lua_S);
	luaReg_Core_ccActionEase(lua_S);
	luaReg_Core_ccEaseRateAction(lua_S);
	luaReg_Core_ccEaseExponentialIn(lua_S);
	luaReg_Core_ccEaseExponentialOut(lua_S);
	luaReg_Core_ccEaseExponentialInOut(lua_S);
	luaReg_Core_ccEaseSineIn(lua_S);
	luaReg_Core_ccEaseSineOut(lua_S);
	luaReg_Core_ccEaseSineInOut(lua_S);
	luaReg_Core_ccEaseBounce(lua_S);
	luaReg_Core_ccEaseBounceIn(lua_S);
	luaReg_Core_ccEaseBounceOut(lua_S);
	luaReg_Core_ccEaseBounceInOut(lua_S);
	luaReg_Core_ccEaseBackIn(lua_S);
	luaReg_Core_ccEaseBackOut(lua_S);
	luaReg_Core_ccEaseBackInOut(lua_S);
	luaReg_Core_ccEaseQuadraticActionIn(lua_S);
	luaReg_Core_ccEaseQuadraticActionOut(lua_S);
	luaReg_Core_ccEaseQuadraticActionInOut(lua_S);
	luaReg_Core_ccEaseQuarticActionIn(lua_S);
	luaReg_Core_ccEaseQuarticActionOut(lua_S);
	luaReg_Core_ccEaseQuarticActionInOut(lua_S);
	luaReg_Core_ccEaseQuinticActionIn(lua_S);
	luaReg_Core_ccEaseQuinticActionOut(lua_S);
	luaReg_Core_ccEaseQuinticActionInOut(lua_S);
	luaReg_Core_ccEaseCircleActionIn(lua_S);
	luaReg_Core_ccEaseCircleActionOut(lua_S);
	luaReg_Core_ccEaseCircleActionInOut(lua_S);
	luaReg_Core_ccEaseCubicActionIn(lua_S);
	luaReg_Core_ccEaseCubicActionOut(lua_S);
	luaReg_Core_ccEaseCubicActionInOut(lua_S);
	luaReg_Core_ccEaseIn(lua_S);
	luaReg_Core_ccEaseOut(lua_S);
	luaReg_Core_ccEaseInOut(lua_S);
	luaReg_Core_ccEaseElastic(lua_S);
	luaReg_Core_ccEaseElasticIn(lua_S);
	luaReg_Core_ccEaseElasticOut(lua_S);
	luaReg_Core_ccEaseElasticInOut(lua_S);
	luaReg_Core_ccEaseBezierAction(lua_S);
	luaReg_Core_ccActionInstant(lua_S);
	luaReg_Core_ccShow(lua_S);
	luaReg_Core_ccHide(lua_S);
	luaReg_Core_ccToggleVisibility(lua_S);
	luaReg_Core_ccRemoveSelf(lua_S);
	luaReg_Core_ccFlipX(lua_S);
	luaReg_Core_ccFlipY(lua_S);
	luaReg_Core_ccPlace(lua_S);
	luaReg_Core_ccCallFunc(lua_S);
	luaReg_Core_ccGridAction(lua_S);
	luaReg_Core_ccGrid3DAction(lua_S);
	luaReg_Core_ccTiledGrid3DAction(lua_S);
	luaReg_Core_ccStopGrid(lua_S);
	luaReg_Core_ccReuseGrid(lua_S);
	luaReg_Core_ccWaves3D(lua_S);
	luaReg_Core_ccFlipX3D(lua_S);
	luaReg_Core_ccFlipY3D(lua_S);
	luaReg_Core_ccLens3D(lua_S);
	luaReg_Core_ccRipple3D(lua_S);
	luaReg_Core_ccShaky3D(lua_S);
	luaReg_Core_ccLiquid(lua_S);
	luaReg_Core_ccWaves(lua_S);
	luaReg_Core_ccTwirl(lua_S);
	luaReg_Core_ccActionManager(lua_S);
	luaReg_Core_ccPageTurn3D(lua_S);
	luaReg_Core_ccProgressTo(lua_S);
	luaReg_Core_ccProgressFromTo(lua_S);
	luaReg_Core_ccShakyTiles3D(lua_S);
	luaReg_Core_ccShatteredTiles3D(lua_S);
	luaReg_Core_ccShuffleTiles(lua_S);
	luaReg_Core_ccFadeOutTRTiles(lua_S);
	luaReg_Core_ccFadeOutBLTiles(lua_S);
	luaReg_Core_ccFadeOutUpTiles(lua_S);
	luaReg_Core_ccFadeOutDownTiles(lua_S);
	luaReg_Core_ccTurnOffTiles(lua_S);
	luaReg_Core_ccWavesTiles3D(lua_S);
	luaReg_Core_ccJumpTiles3D(lua_S);
	luaReg_Core_ccSplitRows(lua_S);
	luaReg_Core_ccSplitCols(lua_S);
	luaReg_Core_ccActionTween(lua_S);
	luaReg_Core_ccAtlasNode(lua_S);
	luaReg_Core_ccClippingNode(lua_S);
	luaReg_Core_ccClippingRectangleNode(lua_S);
	luaReg_Core_ccDrawNode(lua_S);
	luaReg_Core_ccFontAtlas(lua_S);
	luaReg_Core_ccFontRasterMode(lua_S);
	luaReg_Core_ccGlyphRenderPolicy(lua_S);
	luaReg_Core_ccGlyphStatus(lua_S);
	luaReg_Core_ccGlyphTicket(lua_S);
	luaReg_Core_ccLabel(lua_S);
	luaReg_Core_ccLabelAtlas(lua_S);
	luaReg_Core_ccSprite(lua_S);
	luaReg_Core_ccLayer(lua_S);
	luaReg_Core_ccLayerColor(lua_S);
	luaReg_Core_ccLayerGradient(lua_S);
	luaReg_Core_ccLayerRadialGradient(lua_S);
	luaReg_Core_ccLayerMultiplex(lua_S);
	luaReg_Core_ccMenuItem(lua_S);
	luaReg_Core_ccMenuItemLabel(lua_S);
	luaReg_Core_ccMenuItemAtlasFont(lua_S);
	luaReg_Core_ccMenuItemFont(lua_S);
	luaReg_Core_ccMenuItemSprite(lua_S);
	luaReg_Core_ccMenuItemImage(lua_S);
	luaReg_Core_ccMenuItemToggle(lua_S);
	luaReg_Core_ccMenu(lua_S);
	luaReg_Core_ccMotionStreak(lua_S);
	luaReg_Core_ccNodeGrid(lua_S);
	luaReg_Core_ccParticleBatchNode(lua_S);
	luaReg_Core_ccSpriteFrameCache(lua_S);
	luaReg_Core_ccParticleEmissionMaskCache(lua_S);
	luaReg_Core_ccParticleSystem(lua_S);
	luaReg_Core_ccParticleSystemQuad(lua_S);
	luaReg_Core_ccParticleFire(lua_S);
	luaReg_Core_ccParticleFireworks(lua_S);
	luaReg_Core_ccParticleSun(lua_S);
	luaReg_Core_ccParticleGalaxy(lua_S);
	luaReg_Core_ccParticleFlower(lua_S);
	luaReg_Core_ccParticleMeteor(lua_S);
	luaReg_Core_ccParticleSpiral(lua_S);
	luaReg_Core_ccParticleExplosion(lua_S);
	luaReg_Core_ccParticleSmoke(lua_S);
	luaReg_Core_ccParticleSnow(lua_S);
	luaReg_Core_ccParticleRain(lua_S);
	luaReg_Core_ccProgressTimer(lua_S);
	luaReg_Core_ccProtectedNode(lua_S);
	luaReg_Core_ccRenderTexture(lua_S);
	luaReg_Core_ccTransitionScene(lua_S);
	luaReg_Core_ccTransitionSceneOriented(lua_S);
	luaReg_Core_ccTransitionRotoZoom(lua_S);
	luaReg_Core_ccTransitionJumpZoom(lua_S);
	luaReg_Core_ccTransitionMoveInL(lua_S);
	luaReg_Core_ccTransitionMoveInR(lua_S);
	luaReg_Core_ccTransitionMoveInT(lua_S);
	luaReg_Core_ccTransitionMoveInB(lua_S);
	luaReg_Core_ccTransitionSlideInL(lua_S);
	luaReg_Core_ccTransitionSlideInR(lua_S);
	luaReg_Core_ccTransitionSlideInB(lua_S);
	luaReg_Core_ccTransitionSlideInT(lua_S);
	luaReg_Core_ccTransitionShrinkGrow(lua_S);
	luaReg_Core_ccTransitionFlipX(lua_S);
	luaReg_Core_ccTransitionFlipY(lua_S);
	luaReg_Core_ccTransitionFlipAngular(lua_S);
	luaReg_Core_ccTransitionZoomFlipX(lua_S);
	luaReg_Core_ccTransitionZoomFlipY(lua_S);
	luaReg_Core_ccTransitionZoomFlipAngular(lua_S);
	luaReg_Core_ccTransitionFade(lua_S);
	luaReg_Core_ccTransitionCrossFade(lua_S);
	luaReg_Core_ccTransitionTurnOffTiles(lua_S);
	luaReg_Core_ccTransitionSplitCols(lua_S);
	luaReg_Core_ccTransitionSplitRows(lua_S);
	luaReg_Core_ccTransitionFadeTR(lua_S);
	luaReg_Core_ccTransitionFadeBL(lua_S);
	luaReg_Core_ccTransitionFadeUp(lua_S);
	luaReg_Core_ccTransitionFadeDown(lua_S);
	luaReg_Core_ccTransitionPageTurn(lua_S);
	luaReg_Core_ccTransitionProgress(lua_S);
	luaReg_Core_ccTransitionProgressRadialCCW(lua_S);
	luaReg_Core_ccTransitionProgressRadialCW(lua_S);
	luaReg_Core_ccTransitionProgressHorizontal(lua_S);
	luaReg_Core_ccTransitionProgressVertical(lua_S);
	luaReg_Core_ccTransitionProgressInOut(lua_S);
	luaReg_Core_ccTransitionProgressOutIn(lua_S);
	luaReg_Core_ccCamera(lua_S);
	luaReg_Core_ccCameraBackgroundBrush(lua_S);
	luaReg_Core_ccCameraBackgroundDepthBrush(lua_S);
	luaReg_Core_ccCameraBackgroundColorBrush(lua_S);
	luaReg_Core_ccCameraBackgroundSkyBoxBrush(lua_S);
	luaReg_Core_ccGridBase(lua_S);
	luaReg_Core_ccGrid3D(lua_S);
	luaReg_Core_ccTiledGrid3D(lua_S);
	luaReg_Core_ccBaseLight(lua_S);
	luaReg_Core_ccDirectionLight(lua_S);
	luaReg_Core_ccPointLight(lua_S);
	luaReg_Core_ccSpotLight(lua_S);
	luaReg_Core_ccAmbientLight(lua_S);
	luaReg_Core_ccRenderState(lua_S);
	luaReg_Core_ccTechnique(lua_S);
	luaReg_Core_ccMaterial(lua_S);
	luaReg_Core_ccPass(lua_S);
	luaReg_Core_ccRenderer(lua_S);
	luaReg_Core_ccTextureCache(lua_S);
	luaReg_Core_ccDevice(lua_S);
	luaReg_Core_ccApplication(lua_S);
	luaReg_Core_ccGLViewImpl(lua_S);
	luaReg_Core_ccAnimationCache(lua_S);
	luaReg_Core_ccSpriteBatchNode(lua_S);
	luaReg_Core_ccParallaxNode(lua_S);
	luaReg_Core_ccTMXObjectGroup(lua_S);
	luaReg_Core_ccTMXLayerInfo(lua_S);
	luaReg_Core_ccTMXTilesetInfo(lua_S);
	luaReg_Core_ccTMXMapInfo(lua_S);
	luaReg_Core_ccTileMapAtlas(lua_S);
	luaReg_Core_ccFastTMXLayer(lua_S);
	luaReg_Core_ccTMXTileAnimTask(lua_S);
	luaReg_Core_ccTMXTileAnimManager(lua_S);
	luaReg_Core_ccFastTMXTiledMap(lua_S);
	luaReg_Core_ccMotionStreak3D(lua_S);
	luaReg_Core_ccComponentLua(lua_S);
	return register_all_cc_base_retained(lua_S);
}
