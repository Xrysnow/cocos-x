#include "cclua_video_platform_auto.hpp"
#include "base/ccConfig.h"
#if CC_ENABLE_VIDEO_PLATFORM && (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)))
#include "lua_conversion/lua_conversion.hpp"
#include "ui/UIVideoPlayer/UIVideoPlayer.h"

int lua_cocos2d_ui_VideoPlayer_addEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:addEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(const cocos2d::ui::VideoPlayer::ccVideoPlayerCallback&)>(&cocos2d::ui::VideoPlayer::addEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_getFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:getFileName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::getFileName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_getURL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:getURL");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::getURL));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_isFullScreenEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:isFullScreenEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::isFullScreenEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_isKeepAspectRatioEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:isKeepAspectRatioEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::isKeepAspectRatioEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_isLooping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:isLooping");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::isLooping));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_isPlaying(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:isPlaying");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::isPlaying));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_isUserInputEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:isUserInputEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::ui::VideoPlayer::*)()const>(&cocos2d::ui::VideoPlayer::isUserInputEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_play(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:play");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::VideoPlayer::*)()>(&cocos2d::ui::VideoPlayer::play));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_seekTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:seekTo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(float)>(&cocos2d::ui::VideoPlayer::seekTo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setFileName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setFileName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(std::string_view)>(&cocos2d::ui::VideoPlayer::setFileName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setFullScreenEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setFullScreenEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(bool)>(&cocos2d::ui::VideoPlayer::setFullScreenEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setKeepAspectRatioEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setKeepAspectRatioEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(bool)>(&cocos2d::ui::VideoPlayer::setKeepAspectRatioEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setLooping(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setLooping");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(bool)>(&cocos2d::ui::VideoPlayer::setLooping));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setPlayRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setPlayRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(float)>(&cocos2d::ui::VideoPlayer::setPlayRate));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setStyle(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setStyle");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(cocos2d::ui::VideoPlayer::StyleType)>(&cocos2d::ui::VideoPlayer::setStyle));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setURL(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setURL");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(std::string_view)>(&cocos2d::ui::VideoPlayer::setURL));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_setUserInputEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:setUserInputEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ui::VideoPlayer::*)(bool)>(&cocos2d::ui::VideoPlayer::setUserInputEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ui_VideoPlayer_stop(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:stop");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::ui::VideoPlayer::*)()>(&cocos2d::ui::VideoPlayer::stop));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ui_VideoPlayer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("ccui.VideoPlayer", "ccui.VideoPlayer:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ui::VideoPlayer*(*)()>(&cocos2d::ui::VideoPlayer::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_cc_video_platform_ccuiVideoPlayer(lua_State* lua_S)
{
	LUA_ENTRY("ccui");
	LUA_CLS_DEF_BASE(cocos2d::ui::VideoPlayer, "VideoPlayer", "ccui.VideoPlayer",
		cocos2d::ui::VideoPlayer, "ccui.Widget",
		nullptr, nullptr);
	LUA_METHOD("addEventListener", lua_cocos2d_ui_VideoPlayer_addEventListener);
	LUA_METHOD("getFileName", lua_cocos2d_ui_VideoPlayer_getFileName);
	LUA_METHOD("getURL", lua_cocos2d_ui_VideoPlayer_getURL);
	LUA_METHOD("isFullScreenEnabled", lua_cocos2d_ui_VideoPlayer_isFullScreenEnabled);
	LUA_METHOD("isKeepAspectRatioEnabled", lua_cocos2d_ui_VideoPlayer_isKeepAspectRatioEnabled);
	LUA_METHOD("isLooping", lua_cocos2d_ui_VideoPlayer_isLooping);
	LUA_METHOD("isPlaying", lua_cocos2d_ui_VideoPlayer_isPlaying);
	LUA_METHOD("isUserInputEnabled", lua_cocos2d_ui_VideoPlayer_isUserInputEnabled);
	LUA_METHOD("play", lua_cocos2d_ui_VideoPlayer_play);
	LUA_METHOD("seekTo", lua_cocos2d_ui_VideoPlayer_seekTo);
	LUA_METHOD("setFileName", lua_cocos2d_ui_VideoPlayer_setFileName);
	LUA_METHOD("setFullScreenEnabled", lua_cocos2d_ui_VideoPlayer_setFullScreenEnabled);
	LUA_METHOD("setKeepAspectRatioEnabled", lua_cocos2d_ui_VideoPlayer_setKeepAspectRatioEnabled);
	LUA_METHOD("setLooping", lua_cocos2d_ui_VideoPlayer_setLooping);
	LUA_METHOD("setPlayRate", lua_cocos2d_ui_VideoPlayer_setPlayRate);
	LUA_METHOD("setStyle", lua_cocos2d_ui_VideoPlayer_setStyle);
	LUA_METHOD("setURL", lua_cocos2d_ui_VideoPlayer_setURL);
	LUA_METHOD("setUserInputEnabled", lua_cocos2d_ui_VideoPlayer_setUserInputEnabled);
	LUA_METHOD("stop", lua_cocos2d_ui_VideoPlayer_stop);
	LUA_METHOD("create", lua_cocos2d_ui_VideoPlayer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
#endif

int register_all_cc_video_platform(lua_State* lua_S)
{
#include "base/ccConfig.h"
#if CC_ENABLE_VIDEO_PLATFORM && (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)))
	tolua_open(lua_S);
	luaReg_cc_video_platform_ccuiVideoPlayer(lua_S);
	return 0;
#else
	return 0;
#endif
}
