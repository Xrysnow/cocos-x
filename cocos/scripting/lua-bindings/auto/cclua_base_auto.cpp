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

int lua_cocos2d_Ref_getReferenceCount(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:getReferenceCount");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Ref::*)()const>(&cocos2d::Ref::getReferenceCount));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ref_release(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:release");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Ref::*)()>(&cocos2d::Ref::release));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Ref_retain(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Ref", "cc.Ref:retain");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Ref::*)()>(&cocos2d::Ref::retain));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccRef(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Ref, "Ref", "cc.Ref",
		cocos2d::Ref, "",
		nullptr, nullptr);
	LUA_METHOD("getReferenceCount", lua_cocos2d_Ref_getReferenceCount);
	LUA_METHOD("release", lua_cocos2d_Ref_release);
	LUA_METHOD("retain", lua_cocos2d_Ref_retain);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Console_delCommand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:delCommand");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Console::*)(std::string_view)>(&cocos2d::Console::delCommand));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_isIpv6Server(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:isIpv6Server");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Console::*)()const>(&cocos2d::Console::isIpv6Server));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Console_listenOnFileDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:listenOnFileDescriptor");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Console::*)(int)>(&cocos2d::Console::listenOnFileDescriptor));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_listenOnTCP(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:listenOnTCP");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Console::*)(int)>(&cocos2d::Console::listenOnTCP));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_print(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:print");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Console::*)(const char*)>(&cocos2d::Console::print));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_setBindAddress(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:setBindAddress");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Console::*)(std::string_view)>(&cocos2d::Console::setBindAddress));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_setCommandSeparator(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:setCommandSeparator");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Console::*)(char)>(&cocos2d::Console::setCommandSeparator));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Console_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Console", "cc.Console:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Console::*)()>(&cocos2d::Console::stop));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccConsole(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Console, "Console", "cc.Console",
		cocos2d::Console, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("delCommand", lua_cocos2d_Console_delCommand);
	LUA_METHOD("isIpv6Server", lua_cocos2d_Console_isIpv6Server);
	LUA_METHOD("listenOnFileDescriptor", lua_cocos2d_Console_listenOnFileDescriptor);
	LUA_METHOD("listenOnTCP", lua_cocos2d_Console_listenOnTCP);
	LUA_METHOD("print", lua_cocos2d_Console_print);
	LUA_METHOD("setBindAddress", lua_cocos2d_Console_setBindAddress);
	LUA_METHOD("setCommandSeparator", lua_cocos2d_Console_setCommandSeparator);
	LUA_METHOD("stop", lua_cocos2d_Console_stop);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListener_checkAvailable(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:checkAvailable");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListener::*)()>(&cocos2d::EventListener::checkAvailable));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListener_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventListener*(cocos2d::EventListener::*)()>(&cocos2d::EventListener::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListener_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListener::*)()const>(&cocos2d::EventListener::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventListener_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListener", "cc.EventListener:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventListener::*)(bool)>(&cocos2d::EventListener::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListener(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListener, "EventListener", "cc.EventListener",
		cocos2d::EventListener, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("checkAvailable", lua_cocos2d_EventListener_checkAvailable);
	LUA_METHOD("clone", lua_cocos2d_EventListener_clone);
	LUA_METHOD("isEnabled", lua_cocos2d_EventListener_isEnabled);
	LUA_METHOD("setEnabled", lua_cocos2d_EventListener_setEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerCustom_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.EventListenerCustom", "cc.EventListenerCustom:create");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EventListenerCustom*(*)(std::string_view, const std::function<void(cocos2d::EventCustom*)>&)>(&cocos2d::EventListenerCustom::create)));
	}
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccEventListenerCustom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerCustom, "EventListenerCustom", "cc.EventListenerCustom",
		cocos2d::EventListenerCustom, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_EventListenerCustom_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_backend_ShaderCache_removeUnusedShader(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:removeUnusedShader");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::backend::ShaderCache::*)()>(&cocos2d::backend::ShaderCache::removeUnusedShader));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_backend_ShaderCache_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::ShaderCache*(*)()>(&cocos2d::backend::ShaderCache::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_backend_ShaderCache_newFragmentShaderModule(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:newFragmentShaderModule");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::ShaderModule*(*)(std::string_view)>(&cocos2d::backend::ShaderCache::newFragmentShaderModule));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_backend_ShaderCache_newVertexShaderModule(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ShaderCache", "cc.ShaderCache:newVertexShaderModule");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::backend::ShaderModule*(*)(std::string_view)>(&cocos2d::backend::ShaderCache::newVertexShaderModule));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccShaderCache(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::backend::ShaderCache, "ShaderCache", "ccb.ShaderCache",
		cocos2d::backend::ShaderCache, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("removeUnusedShader", lua_cocos2d_backend_ShaderCache_removeUnusedShader);
	LUA_METHOD("getInstance", lua_cocos2d_backend_ShaderCache_getInstance);
	LUA_METHOD("newFragmentShaderModule", lua_cocos2d_backend_ShaderCache_newFragmentShaderModule);
	LUA_METHOD("newVertexShaderModule", lua_cocos2d_backend_ShaderCache_newVertexShaderModule);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Texture2D_drawAtPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:drawAtPoint");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Texture2D::*)(const cocos2d::Vec2&, float)>(&cocos2d::Texture2D::drawAtPoint)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Texture2D_drawInRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:drawInRect");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Texture2D::*)(const cocos2d::Rect&, float)>(&cocos2d::Texture2D::drawInRect)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Texture2D_generateMipmap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:generateMipmap");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Texture2D::*)()>(&cocos2d::Texture2D::generateMipmap));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getBackendTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getBackendTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::TextureBackend*(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getBackendTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getBitsPerPixelForFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getBitsPerPixelForFormat");
	LUA_TRY_INVOKE_R(1, static_cast<unsigned int(cocos2d::Texture2D::*)(cocos2d::backend::PixelFormat)const>(&cocos2d::Texture2D::getBitsPerPixelForFormat));
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getBitsPerPixelForFormat));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Texture2D_getContentSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getContentSize");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getContentSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getContentSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getContentSizeInPixels");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::Texture2D::*)()>(&cocos2d::Texture2D::getContentSizeInPixels));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getMaxS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getMaxS");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getMaxS));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getMaxT(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getMaxT");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getMaxT));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getPixelFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelFormat");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::PixelFormat(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getPixelFormat));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getPixelsHigh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelsHigh");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getPixelsHigh));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getPixelsWide(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getPixelsWide");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getPixelsWide));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getSamplerFlags(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getSamplerFlags");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getSamplerFlags));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_getStringForFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getStringForFormat");
	LUA_TRY_INVOKE_R(0, static_cast<const char*(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::getStringForFormat));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_hasMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:hasMipmaps");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::hasMipmaps));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_hasPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:hasPremultipliedAlpha");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::hasPremultipliedAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_initWithImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:initWithImage");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Texture2D::*)(cocos2d::Image*, cocos2d::backend::PixelFormat)>(&cocos2d::Texture2D::initWithImage)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Texture2D::*)(cocos2d::Image*)>(&cocos2d::Texture2D::initWithImage));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Texture2D_initWithString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:initWithString");
	LUA_TRY_INVOKE_R(8, (static_cast<bool(cocos2d::Texture2D::*)(const char*, std::string_view, float, const cocos2d::Vec2&, cocos2d::TextHAlignment, cocos2d::TextVAlignment, bool, int)>(&cocos2d::Texture2D::initWithString)));
	LUA_TRY_INVOKE_R(7, ([](cocos2d::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cocos2d::Vec2& arg3,cocos2d::TextHAlignment arg4,cocos2d::TextVAlignment arg5,bool arg6){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4),std::move(arg5),std::move(arg6));}}));
	LUA_TRY_INVOKE_R(6, ([](cocos2d::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cocos2d::Vec2& arg3,cocos2d::TextHAlignment arg4,cocos2d::TextVAlignment arg5){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4),std::move(arg5));}}));
	LUA_TRY_INVOKE_R(5, ([](cocos2d::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cocos2d::Vec2& arg3,cocos2d::TextHAlignment arg4){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3,std::move(arg4));}}));
	LUA_TRY_INVOKE_R(4, ([](cocos2d::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2,const cocos2d::Vec2& arg3){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2),arg3);}}));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Texture2D* obj,const char* arg0,std::string_view arg1,float arg2){{return obj->initWithString(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Texture2D::*)(const char*, const cocos2d::FontDefinition&)>(&cocos2d::Texture2D::initWithString)));
	LUA_INVOKE_FOOTER("2,3,4,5,6,7,8");
}
int lua_cocos2d_Texture2D_isRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:isRenderTarget");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Texture2D::*)()const>(&cocos2d::Texture2D::isRenderTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_setAliasTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setAliasTexParameters");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Texture2D::*)()>(&cocos2d::Texture2D::setAliasTexParameters));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_setAntiAliasTexParameters(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setAntiAliasTexParameters");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Texture2D::*)()>(&cocos2d::Texture2D::setAntiAliasTexParameters));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_setMaxS(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setMaxS");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Texture2D::*)(float)>(&cocos2d::Texture2D::setMaxS));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Texture2D_setMaxT(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setMaxT");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Texture2D::*)(float)>(&cocos2d::Texture2D::setMaxT));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Texture2D_setPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setPremultipliedAlpha");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Texture2D::*)(bool)>(&cocos2d::Texture2D::setPremultipliedAlpha));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Texture2D_setRenderTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setRenderTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Texture2D::*)(bool)>(&cocos2d::Texture2D::setRenderTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Texture2D_updateTextureDescriptor(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:updateTextureDescriptor");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Texture2D::*)(const cocos2d::backend::TextureDescriptor&, bool)>(&cocos2d::Texture2D::updateTextureDescriptor)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Texture2D* obj,const cocos2d::backend::TextureDescriptor& arg0){{return obj->updateTextureDescriptor(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Texture2D_updateWithImage(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Texture2D", "cc.Texture2D:updateWithImage");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Texture2D::*)(cocos2d::Image*, cocos2d::backend::PixelFormat, int)>(&cocos2d::Texture2D::updateWithImage)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Texture2D* obj,cocos2d::Image* arg0,cocos2d::backend::PixelFormat arg1){{return obj->updateWithImage(arg0,std::move(arg1));}}));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_Texture2D_getDefaultAlphaPixelFormat(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Texture2D", "cc.Texture2D:getDefaultAlphaPixelFormat");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::PixelFormat(*)()>(&cocos2d::Texture2D::getDefaultAlphaPixelFormat));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_Texture2D_setDefaultAlphaPixelFormat(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Texture2D", "cc.Texture2D:setDefaultAlphaPixelFormat");
	LUA_TRY_INVOKE(1, static_cast<void(*)(cocos2d::backend::PixelFormat)>(&cocos2d::Texture2D::setDefaultAlphaPixelFormat));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccTexture2D(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Texture2D, "Texture2D", "cc.Texture2D",
		cocos2d::Texture2D, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("drawAtPoint", lua_cocos2d_Texture2D_drawAtPoint);
	LUA_METHOD("drawInRect", lua_cocos2d_Texture2D_drawInRect);
	LUA_METHOD("generateMipmap", lua_cocos2d_Texture2D_generateMipmap);
	LUA_METHOD("getBackendTexture", lua_cocos2d_Texture2D_getBackendTexture);
	LUA_METHOD("getBitsPerPixelForFormat", lua_cocos2d_Texture2D_getBitsPerPixelForFormat);
	LUA_METHOD("getContentSize", lua_cocos2d_Texture2D_getContentSize);
	LUA_METHOD("getContentSizeInPixels", lua_cocos2d_Texture2D_getContentSizeInPixels);
	LUA_METHOD("getMaxS", lua_cocos2d_Texture2D_getMaxS);
	LUA_METHOD("getMaxT", lua_cocos2d_Texture2D_getMaxT);
	LUA_METHOD("getPath", lua_cocos2d_Texture2D_getPath);
	LUA_METHOD("getPixelFormat", lua_cocos2d_Texture2D_getPixelFormat);
	LUA_METHOD("getPixelsHigh", lua_cocos2d_Texture2D_getPixelsHigh);
	LUA_METHOD("getPixelsWide", lua_cocos2d_Texture2D_getPixelsWide);
	LUA_METHOD("getSamplerFlags", lua_cocos2d_Texture2D_getSamplerFlags);
	LUA_METHOD("getStringForFormat", lua_cocos2d_Texture2D_getStringForFormat);
	LUA_METHOD("hasMipmaps", lua_cocos2d_Texture2D_hasMipmaps);
	LUA_METHOD("hasPremultipliedAlpha", lua_cocos2d_Texture2D_hasPremultipliedAlpha);
	LUA_METHOD("initWithImage", lua_cocos2d_Texture2D_initWithImage);
	LUA_METHOD("initWithString", lua_cocos2d_Texture2D_initWithString);
	LUA_METHOD("isRenderTarget", lua_cocos2d_Texture2D_isRenderTarget);
	LUA_METHOD("setAliasTexParameters", lua_cocos2d_Texture2D_setAliasTexParameters);
	LUA_METHOD("setAntiAliasTexParameters", lua_cocos2d_Texture2D_setAntiAliasTexParameters);
	LUA_METHOD("setMaxS", lua_cocos2d_Texture2D_setMaxS);
	LUA_METHOD("setMaxT", lua_cocos2d_Texture2D_setMaxT);
	LUA_METHOD("setPremultipliedAlpha", lua_cocos2d_Texture2D_setPremultipliedAlpha);
	LUA_METHOD("setRenderTarget", lua_cocos2d_Texture2D_setRenderTarget);
	LUA_METHOD("updateTextureDescriptor", lua_cocos2d_Texture2D_updateTextureDescriptor);
	LUA_METHOD("updateWithImage", lua_cocos2d_Texture2D_updateWithImage);
	LUA_METHOD("getDefaultAlphaPixelFormat", lua_cocos2d_Texture2D_getDefaultAlphaPixelFormat);
	LUA_METHOD("setDefaultAlphaPixelFormat", lua_cocos2d_Texture2D_setDefaultAlphaPixelFormat);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Touch_getCurrentForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getCurrentForce");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Touch::*)()const>(&cocos2d::Touch::getCurrentForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getDelta(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getDelta");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getDelta));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getId(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getId");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Touch::*)()const>(&cocos2d::Touch::getID));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getMaxForce(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getMaxForce");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Touch::*)()const>(&cocos2d::Touch::getMaxForce));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getPreviousLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getPreviousLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getPreviousLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getPreviousLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getPreviousLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getPreviousLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getStartLocation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getStartLocation");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getStartLocation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_getStartLocationInView(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:getStartLocationInView");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Vec2(cocos2d::Touch::*)()const>(&cocos2d::Touch::getStartLocationInView));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Touch_setTouchInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Touch", "cc.Touch:setTouchInfo");
	LUA_TRY_INVOKE(5, (static_cast<void(cocos2d::Touch::*)(int, float, float, float, float)>(&cocos2d::Touch::setTouchInfo)));
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::Touch::*)(int, float, float)>(&cocos2d::Touch::setTouchInfo)));
	LUA_INVOKE_FOOTER("3,5");
}
int luaReg_Core_ccTouch(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Touch, "Touch", "cc.Touch",
		cocos2d::Touch, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentForce", lua_cocos2d_Touch_getCurrentForce);
	LUA_METHOD("getDelta", lua_cocos2d_Touch_getDelta);
	LUA_METHOD("getId", lua_cocos2d_Touch_getId);
	LUA_METHOD("getLocation", lua_cocos2d_Touch_getLocation);
	LUA_METHOD("getLocationInView", lua_cocos2d_Touch_getLocationInView);
	LUA_METHOD("getMaxForce", lua_cocos2d_Touch_getMaxForce);
	LUA_METHOD("getPreviousLocation", lua_cocos2d_Touch_getPreviousLocation);
	LUA_METHOD("getPreviousLocationInView", lua_cocos2d_Touch_getPreviousLocationInView);
	LUA_METHOD("getStartLocation", lua_cocos2d_Touch_getStartLocation);
	LUA_METHOD("getStartLocationInView", lua_cocos2d_Touch_getStartLocationInView);
	LUA_METHOD("setTouchInfo", lua_cocos2d_Touch_setTouchInfo);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Event_getCurrentTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:getCurrentTarget");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::Event::*)()>(&cocos2d::Event::getCurrentTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Event_getType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:getType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Event::Type(cocos2d::Event::*)()const>(&cocos2d::Event::getType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Event_isStopped(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:isStopped");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Event::*)()const>(&cocos2d::Event::isStopped));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Event_stopPropagation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Event", "cc.Event:stopPropagation");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Event::*)()>(&cocos2d::Event::stopPropagation));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEvent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Event, "Event", "cc.Event",
		cocos2d::Event, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getCurrentTarget", lua_cocos2d_Event_getCurrentTarget);
	LUA_METHOD("getType", lua_cocos2d_Event_getType);
	LUA_METHOD("isStopped", lua_cocos2d_Event_isStopped);
	LUA_METHOD("stopPropagation", lua_cocos2d_Event_stopPropagation);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventTouch_getEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventTouch", "cc.EventTouch:getEventCode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::EventTouch::EventCode(cocos2d::EventTouch::*)()const>(&cocos2d::EventTouch::getEventCode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventTouch_setEventCode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventTouch", "cc.EventTouch:setEventCode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventTouch::*)(cocos2d::EventTouch::EventCode)>(&cocos2d::EventTouch::setEventCode));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventTouch(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventTouch, "EventTouch", "cc.EventTouch",
		cocos2d::EventTouch, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventCode", lua_cocos2d_EventTouch_getEventCode);
	LUA_METHOD("setEventCode", lua_cocos2d_EventTouch_setEventCode);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventKeyboard(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventKeyboard, "EventKeyboard", "cc.EventKeyboard",
		cocos2d::EventKeyboard, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Component_getName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:getName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Component::*)()const>(&cocos2d::Component::getName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_getOwner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:getOwner");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::Component::*)()const>(&cocos2d::Component::getOwner));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Component::*)()>(&cocos2d::Component::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Component::*)()const>(&cocos2d::Component::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_onAdd(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:onAdd");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Component::*)()>(&cocos2d::Component::onAdd));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_onRemove(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:onRemove");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Component::*)()>(&cocos2d::Component::onRemove));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Component_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Component::*)(bool)>(&cocos2d::Component::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Component_setName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Component::*)(std::string_view)>(&cocos2d::Component::setName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Component_setOwner(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:setOwner");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Component::*)(cocos2d::Node*)>(&cocos2d::Component::setOwner));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Component_update(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Component", "cc.Component:update");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Component::*)(float)>(&cocos2d::Component::update));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Component_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Component", "cc.Component:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Component*(*)()>(&cocos2d::Component::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccComponent(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Component, "Component", "cc.Component",
		cocos2d::Component, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getName", lua_cocos2d_Component_getName);
	LUA_METHOD("getOwner", lua_cocos2d_Component_getOwner);
	LUA_METHOD("init", lua_cocos2d_Component_init);
	LUA_METHOD("isEnabled", lua_cocos2d_Component_isEnabled);
	LUA_METHOD("onAdd", lua_cocos2d_Component_onAdd);
	LUA_METHOD("onRemove", lua_cocos2d_Component_onRemove);
	LUA_METHOD("setEnabled", lua_cocos2d_Component_setEnabled);
	LUA_METHOD("setName", lua_cocos2d_Component_setName);
	LUA_METHOD("setOwner", lua_cocos2d_Component_setOwner);
	LUA_METHOD("update", lua_cocos2d_Component_update);
	LUA_METHOD("create", lua_cocos2d_Component_create);
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
