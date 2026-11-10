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

int lua_cocos2d_Speed_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::Speed::*)()const>(&cocos2d::Speed::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Speed_getSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:getSpeed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Speed::*)()const>(&cocos2d::Speed::getSpeed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Speed_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:initWithAction");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Speed::*)(cocos2d::ActionInterval*, float)>(&cocos2d::Speed::initWithAction)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Speed_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setInnerAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Speed::*)(cocos2d::ActionInterval*)>(&cocos2d::Speed::setInnerAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Speed_setSpeed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Speed", "cc.Speed:setSpeed");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Speed::*)(float)>(&cocos2d::Speed::setSpeed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Speed_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Speed", "cc.Speed:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Speed*(*)(cocos2d::ActionInterval*, float)>(&cocos2d::Speed::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccSpeed(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Speed, "Speed", "cc.Speed",
		cocos2d::Speed, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_Speed_getInnerAction);
	LUA_METHOD("getSpeed", lua_cocos2d_Speed_getSpeed);
	LUA_METHOD("initWithAction", lua_cocos2d_Speed_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_Speed_setInnerAction);
	LUA_METHOD("setSpeed", lua_cocos2d_Speed_setSpeed);
	LUA_METHOD("create", lua_cocos2d_Speed_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Follow_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTarget");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Follow::*)(cocos2d::Node*, const cocos2d::Rect&)>(&cocos2d::Follow::initWithTarget)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Follow* obj,cocos2d::Node* arg0){{return obj->initWithTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Follow_initWithTargetAndOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:initWithTargetAndOffset");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::Follow::*)(cocos2d::Node*, float, float, const cocos2d::Rect&)>(&cocos2d::Follow::initWithTargetAndOffset)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Follow* obj,cocos2d::Node* arg0,float arg1,float arg2){{return obj->initWithTargetAndOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_INVOKE_FOOTER("3,4");
}
int lua_cocos2d_Follow_isBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:isBoundarySet");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Follow::*)()const>(&cocos2d::Follow::isBoundarySet));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Follow_setBoundarySet(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Follow", "cc.Follow:setBoundarySet");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Follow::*)(bool)>(&cocos2d::Follow::setBoundarySet));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Follow_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Follow*(*)(cocos2d::Node*, const cocos2d::Rect&)>(&cocos2d::Follow::create)));
	LUA_TRY_INVOKE_R(1, [](cocos2d::Node* arg0){{return cocos2d::Follow::create(arg0);}});
	LUA_SINVOKE_FOOTER("1,2");
}
int lua_cocos2d_Follow_createWithOffset(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Follow", "cc.Follow:createWithOffset");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::Follow*(*)(cocos2d::Node*, float, float, const cocos2d::Rect&)>(&cocos2d::Follow::createWithOffset)));
	LUA_TRY_INVOKE_R(3, ([](cocos2d::Node* arg0,float arg1,float arg2){{return cocos2d::Follow::createWithOffset(arg0,std::move(arg1),std::move(arg2));}}));
	LUA_SINVOKE_FOOTER("3,4");
}
int luaReg_Core_ccFollow(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Follow, "Follow", "cc.Follow",
		cocos2d::Follow, "cc.Action",
		nullptr, nullptr);
	LUA_METHOD("initWithTarget", lua_cocos2d_Follow_initWithTarget);
	LUA_METHOD("initWithTargetAndOffset", lua_cocos2d_Follow_initWithTargetAndOffset);
	LUA_METHOD("isBoundarySet", lua_cocos2d_Follow_isBoundarySet);
	LUA_METHOD("setBoundarySet", lua_cocos2d_Follow_setBoundarySet);
	LUA_METHOD("create", lua_cocos2d_Follow_create);
	LUA_METHOD("createWithOffset", lua_cocos2d_Follow_createWithOffset);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Image_getBitPerPixel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getBitPerPixel");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Image::*)()>(&cocos2d::Image::getBitPerPixel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFilePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::Image::*)()const>(&cocos2d::Image::getFilePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getFileType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getFileType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Image::Format(cocos2d::Image::*)()>(&cocos2d::Image::getFileType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getHeight");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Image::*)()>(&cocos2d::Image::getHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getNumberOfMipmaps(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getNumberOfMipmaps");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Image::*)()>(&cocos2d::Image::getNumberOfMipmaps));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getPixelFormat(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getPixelFormat");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::backend::PixelFormat(cocos2d::Image::*)()>(&cocos2d::Image::getPixelFormat));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:getWidth");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Image::*)()>(&cocos2d::Image::getWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_hasAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasAlpha");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Image::*)()>(&cocos2d::Image::hasAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_hasPremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:hasPremultipliedAlpha");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Image::*)()>(&cocos2d::Image::hasPremultipliedAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_initWithImageFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:initWithImageFile");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Image::*)(std::string_view)>(&cocos2d::Image::initWithImageFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Image_isCompressed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:isCompressed");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Image::*)()>(&cocos2d::Image::isCompressed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_premultiplyAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:premultiplyAlpha");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Image::*)()>(&cocos2d::Image::premultiplyAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_reversePremultipliedAlpha(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:reversePremultipliedAlpha");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Image::*)()>(&cocos2d::Image::reversePremultipliedAlpha));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Image_saveToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Image", "cc.Image:saveToFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Image::*)(std::string_view, bool)>(&cocos2d::Image::saveToFile)));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Image* obj,std::string_view arg0){{return obj->saveToFile(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Image_isCompressedImageHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:isCompressedImageHavePMA");
	LUA_TRY_INVOKE_R(1, static_cast<bool(*)(uint32_t)>(&cocos2d::Image::isCompressedImageHavePMA));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Image_setCompressedImagesHavePMA(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setCompressedImagesHavePMA");
	LUA_TRY_INVOKE(2, (static_cast<void(*)(uint32_t, bool)>(&cocos2d::Image::setCompressedImagesHavePMA)));
	LUA_SINVOKE_FOOTER("2");
}
int lua_cocos2d_Image_setPNGPremultipliedAlphaEnabled(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Image", "cc.Image:setPNGPremultipliedAlphaEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(*)(bool)>(&cocos2d::Image::setPNGPremultipliedAlphaEnabled));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccImage(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Image, "Image", "cc.Image",
		cocos2d::Image, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("getBitPerPixel", lua_cocos2d_Image_getBitPerPixel);
	LUA_METHOD("getFilePath", lua_cocos2d_Image_getFilePath);
	LUA_METHOD("getFileType", lua_cocos2d_Image_getFileType);
	LUA_METHOD("getHeight", lua_cocos2d_Image_getHeight);
	LUA_METHOD("getNumberOfMipmaps", lua_cocos2d_Image_getNumberOfMipmaps);
	LUA_METHOD("getPixelFormat", lua_cocos2d_Image_getPixelFormat);
	LUA_METHOD("getWidth", lua_cocos2d_Image_getWidth);
	LUA_METHOD("hasAlpha", lua_cocos2d_Image_hasAlpha);
	LUA_METHOD("hasPremultipliedAlpha", lua_cocos2d_Image_hasPremultipliedAlpha);
	LUA_METHOD("initWithImageFile", lua_cocos2d_Image_initWithImageFile);
	LUA_METHOD("isCompressed", lua_cocos2d_Image_isCompressed);
	LUA_METHOD("premultiplyAlpha", lua_cocos2d_Image_premultiplyAlpha);
	LUA_METHOD("reversePremultipliedAlpha", lua_cocos2d_Image_reversePremultipliedAlpha);
	LUA_METHOD("saveToFile", lua_cocos2d_Image_saveToFile);
	LUA_METHOD("isCompressedImageHavePMA", lua_cocos2d_Image_isCompressedImageHavePMA);
	LUA_METHOD("setCompressedImagesHavePMA", lua_cocos2d_Image_setCompressedImagesHavePMA);
	LUA_METHOD("setPNGPremultipliedAlphaEnabled", lua_cocos2d_Image_setPNGPremultipliedAlphaEnabled);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SpriteFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrame*(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getCenterRect");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getCenterRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffset");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getOffset));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOffsetInPixels");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getOffsetInPixels));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSize");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getOriginalSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getOriginalSizeInPixels");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vec2&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getOriginalSizeInPixels));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRect");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getRectInPixels");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Rect&(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::getRectInPixels));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_getTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:getTexture");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Texture2D*(cocos2d::SpriteFrame::*)()>(&cocos2d::SpriteFrame::getTexture));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasAnchorPoint");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::hasAnchorPoint));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_hasCenterRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:hasCenterRect");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::hasCenterRect));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_initWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::initWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::initWithTexture)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_initWithTextureFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:initWithTextureFilename");
	LUA_TRY_INVOKE_R(5, (static_cast<bool(cocos2d::SpriteFrame::*)(std::string_view, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::initWithTextureFilename)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::SpriteFrame::*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::initWithTextureFilename)));
	LUA_INVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_isRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:isRotated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::SpriteFrame::*)()const>(&cocos2d::SpriteFrame::isRotated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_SpriteFrame_setAnchorPoint(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setAnchorPoint");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::setAnchorPoint));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setCenterRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setCenterRectInPixels");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Rect&)>(&cocos2d::SpriteFrame::setCenterRectInPixels));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOffset(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffset");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::setOffset));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOffsetInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOffsetInPixels");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::setOffsetInPixels));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOriginalSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::setOriginalSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setOriginalSizeInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setOriginalSizeInPixels");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::setOriginalSizeInPixels));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Rect&)>(&cocos2d::SpriteFrame::setRect));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRectInPixels(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRectInPixels");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(const cocos2d::Rect&)>(&cocos2d::SpriteFrame::setRectInPixels));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setRotated");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(bool)>(&cocos2d::SpriteFrame::setRotated));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_setTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:setTexture");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::SpriteFrame::*)(cocos2d::Texture2D*)>(&cocos2d::SpriteFrame::setTexture));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_SpriteFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:create");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::SpriteFrame*(*)(std::string_view, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteFrame*(*)(std::string_view, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::create)));
	LUA_SINVOKE_FOOTER("2,5");
}
int lua_cocos2d_SpriteFrame_createWithTexture(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SpriteFrame", "cc.SpriteFrame:createWithTexture");
	LUA_TRY_INVOKE_R(5, (static_cast<cocos2d::SpriteFrame*(*)(cocos2d::Texture2D*, const cocos2d::Rect&, bool, const cocos2d::Vec2&, const cocos2d::Vec2&)>(&cocos2d::SpriteFrame::createWithTexture)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::SpriteFrame*(*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::SpriteFrame::createWithTexture)));
	LUA_SINVOKE_FOOTER("2,5");
}
int luaReg_Core_ccSpriteFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SpriteFrame, "SpriteFrame", "cc.SpriteFrame",
		cocos2d::SpriteFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_SpriteFrame_clone);
	LUA_METHOD("getAnchorPoint", lua_cocos2d_SpriteFrame_getAnchorPoint);
	LUA_METHOD("getCenterRect", lua_cocos2d_SpriteFrame_getCenterRect);
	LUA_METHOD("getOffset", lua_cocos2d_SpriteFrame_getOffset);
	LUA_METHOD("getOffsetInPixels", lua_cocos2d_SpriteFrame_getOffsetInPixels);
	LUA_METHOD("getOriginalSize", lua_cocos2d_SpriteFrame_getOriginalSize);
	LUA_METHOD("getOriginalSizeInPixels", lua_cocos2d_SpriteFrame_getOriginalSizeInPixels);
	LUA_METHOD("getRect", lua_cocos2d_SpriteFrame_getRect);
	LUA_METHOD("getRectInPixels", lua_cocos2d_SpriteFrame_getRectInPixels);
	LUA_METHOD("getTexture", lua_cocos2d_SpriteFrame_getTexture);
	LUA_METHOD("hasAnchorPoint", lua_cocos2d_SpriteFrame_hasAnchorPoint);
	LUA_METHOD("hasCenterRect", lua_cocos2d_SpriteFrame_hasCenterRect);
	LUA_METHOD("initWithTexture", lua_cocos2d_SpriteFrame_initWithTexture);
	LUA_METHOD("initWithTextureFilename", lua_cocos2d_SpriteFrame_initWithTextureFilename);
	LUA_METHOD("isRotated", lua_cocos2d_SpriteFrame_isRotated);
	LUA_METHOD("setAnchorPoint", lua_cocos2d_SpriteFrame_setAnchorPoint);
	LUA_METHOD("setCenterRectInPixels", lua_cocos2d_SpriteFrame_setCenterRectInPixels);
	LUA_METHOD("setOffset", lua_cocos2d_SpriteFrame_setOffset);
	LUA_METHOD("setOffsetInPixels", lua_cocos2d_SpriteFrame_setOffsetInPixels);
	LUA_METHOD("setOriginalSize", lua_cocos2d_SpriteFrame_setOriginalSize);
	LUA_METHOD("setOriginalSizeInPixels", lua_cocos2d_SpriteFrame_setOriginalSizeInPixels);
	LUA_METHOD("setRect", lua_cocos2d_SpriteFrame_setRect);
	LUA_METHOD("setRectInPixels", lua_cocos2d_SpriteFrame_setRectInPixels);
	LUA_METHOD("setRotated", lua_cocos2d_SpriteFrame_setRotated);
	LUA_METHOD("setTexture", lua_cocos2d_SpriteFrame_setTexture);
	LUA_METHOD("create", lua_cocos2d_SpriteFrame_create);
	LUA_METHOD("createWithTexture", lua_cocos2d_SpriteFrame_createWithTexture);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_AnimationFrame_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::AnimationFrame*(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getDelayUnits");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getDelayUnits));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrame*(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getSpriteFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_getUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:getUserInfo");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::ValueMap&(cocos2d::AnimationFrame::*)()const>(&cocos2d::AnimationFrame::getUserInfo));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_AnimationFrame_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::AnimationFrame::*)(cocos2d::SpriteFrame*, float, const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::initWithSpriteFrame)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_AnimationFrame_setDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setDelayUnits");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(float)>(&cocos2d::AnimationFrame::setDelayUnits));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(cocos2d::SpriteFrame*)>(&cocos2d::AnimationFrame::setSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_setUserInfo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:setUserInfo");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::AnimationFrame::*)(const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::setUserInfo));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_AnimationFrame_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.AnimationFrame", "cc.AnimationFrame:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::AnimationFrame*(*)(cocos2d::SpriteFrame*, float, const cocos2d::ValueMap&)>(&cocos2d::AnimationFrame::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccAnimationFrame(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::AnimationFrame, "AnimationFrame", "cc.AnimationFrame",
		cocos2d::AnimationFrame, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("clone", lua_cocos2d_AnimationFrame_clone);
	LUA_METHOD("getDelayUnits", lua_cocos2d_AnimationFrame_getDelayUnits);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_AnimationFrame_getSpriteFrame);
	LUA_METHOD("getUserInfo", lua_cocos2d_AnimationFrame_getUserInfo);
	LUA_METHOD("initWithSpriteFrame", lua_cocos2d_AnimationFrame_initWithSpriteFrame);
	LUA_METHOD("setDelayUnits", lua_cocos2d_AnimationFrame_setDelayUnits);
	LUA_METHOD("setSpriteFrame", lua_cocos2d_AnimationFrame_setSpriteFrame);
	LUA_METHOD("setUserInfo", lua_cocos2d_AnimationFrame_setUserInfo);
	LUA_METHOD("create", lua_cocos2d_AnimationFrame_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animation_addSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(cocos2d::SpriteFrame*)>(&cocos2d::Animation::addSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithFile");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(std::string_view)>(&cocos2d::Animation::addSpriteFrameWithFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_addSpriteFrameWithTexture(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:addSpriteFrameWithTexture");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::Animation::*)(cocos2d::Texture2D*, const cocos2d::Rect&)>(&cocos2d::Animation::addSpriteFrameWithTexture)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Animation_clone(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:clone");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Animation*(cocos2d::Animation::*)()const>(&cocos2d::Animation::clone));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDelayPerUnit");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getDelayPerUnit));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getDuration");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getDuration));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getFrames");
	LUA_TRY_INVOKE_R(0, static_cast<const cocos2d::Vector<cocos2d::AnimationFrame *>&(cocos2d::Animation::*)()const>(&cocos2d::Animation::getFrames));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getLoops");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Animation::*)()const>(&cocos2d::Animation::getLoops));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getRestoreOriginalFrame");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Animation::*)()const>(&cocos2d::Animation::getRestoreOriginalFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_getTotalDelayUnits(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:getTotalDelayUnits");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Animation::*)()const>(&cocos2d::Animation::getTotalDelayUnits));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Animation::*)()>(&cocos2d::Animation::init));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animation_initWithAnimationFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithAnimationFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&, float, unsigned int)>(&cocos2d::Animation::initWithAnimationFrames)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_Animation_initWithSpriteFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:initWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::SpriteFrame *>&, float, unsigned int)>(&cocos2d::Animation::initWithSpriteFrames)));
	LUA_TRY_INVOKE_R(2, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return obj->initWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, ([](cocos2d::Animation* obj,const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return obj->initWithSpriteFrames(arg0);}}));
	LUA_INVOKE_FOOTER("1,2,3");
}
int lua_cocos2d_Animation_setDelayPerUnit(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setDelayPerUnit");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(float)>(&cocos2d::Animation::setDelayPerUnit));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setFrames(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setFrames");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&)>(&cocos2d::Animation::setFrames));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setLoops(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setLoops");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(unsigned int)>(&cocos2d::Animation::setLoops));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_setRestoreOriginalFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animation", "cc.Animation:setRestoreOriginalFrame");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animation::*)(bool)>(&cocos2d::Animation::setRestoreOriginalFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animation_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Animation*(*)(const cocos2d::Vector<cocos2d::AnimationFrame *>&, float, unsigned int)>(&cocos2d::Animation::create)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::AnimationFrame *>& arg0,float arg1){{return cocos2d::Animation::create(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Animation*(*)()>(&cocos2d::Animation::create));
	LUA_SINVOKE_FOOTER("0,2,3");
}
int lua_cocos2d_Animation_createWithSpriteFrames(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animation", "cc.Animation:createWithSpriteFrames");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::Animation*(*)(const cocos2d::Vector<cocos2d::SpriteFrame *>&, float, unsigned int)>(&cocos2d::Animation::createWithSpriteFrames)));
	LUA_TRY_INVOKE_R(2, ([](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0,float arg1){{return cocos2d::Animation::createWithSpriteFrames(arg0,std::move(arg1));}}));
	LUA_TRY_INVOKE_R(1, [](const cocos2d::Vector<cocos2d::SpriteFrame *>& arg0){{return cocos2d::Animation::createWithSpriteFrames(arg0);}});
	LUA_SINVOKE_FOOTER("1,2,3");
}
int luaReg_Core_ccAnimation(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animation, "Animation", "cc.Animation",
		cocos2d::Animation, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addSpriteFrame", lua_cocos2d_Animation_addSpriteFrame);
	LUA_METHOD("addSpriteFrameWithFile", lua_cocos2d_Animation_addSpriteFrameWithFile);
	LUA_METHOD("addSpriteFrameWithTexture", lua_cocos2d_Animation_addSpriteFrameWithTexture);
	LUA_METHOD("clone", lua_cocos2d_Animation_clone);
	LUA_METHOD("getDelayPerUnit", lua_cocos2d_Animation_getDelayPerUnit);
	LUA_METHOD("getDuration", lua_cocos2d_Animation_getDuration);
	LUA_METHOD("getFrames", lua_cocos2d_Animation_getFrames);
	LUA_METHOD("getLoops", lua_cocos2d_Animation_getLoops);
	LUA_METHOD("getRestoreOriginalFrame", lua_cocos2d_Animation_getRestoreOriginalFrame);
	LUA_METHOD("getTotalDelayUnits", lua_cocos2d_Animation_getTotalDelayUnits);
	LUA_METHOD("init", lua_cocos2d_Animation_init);
	LUA_METHOD("initWithAnimationFrames", lua_cocos2d_Animation_initWithAnimationFrames);
	LUA_METHOD("initWithSpriteFrames", lua_cocos2d_Animation_initWithSpriteFrames);
	LUA_METHOD("setDelayPerUnit", lua_cocos2d_Animation_setDelayPerUnit);
	LUA_METHOD("setFrames", lua_cocos2d_Animation_setFrames);
	LUA_METHOD("setLoops", lua_cocos2d_Animation_setLoops);
	LUA_METHOD("setRestoreOriginalFrame", lua_cocos2d_Animation_setRestoreOriginalFrame);
	LUA_METHOD("create", lua_cocos2d_Animation_create);
	LUA_METHOD("createWithSpriteFrames", lua_cocos2d_Animation_createWithSpriteFrames);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionInterval_getAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getAmplitudeRate");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ActionInterval::*)()>(&cocos2d::ActionInterval::getAmplitudeRate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_getElapsed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:getElapsed");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::ActionInterval::*)()>(&cocos2d::ActionInterval::getElapsed));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_ActionInterval_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:initWithDuration");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::ActionInterval::*)(float)>(&cocos2d::ActionInterval::initWithDuration));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_ActionInterval_setAmplitudeRate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionInterval", "cc.ActionInterval:setAmplitudeRate");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::ActionInterval::*)(float)>(&cocos2d::ActionInterval::setAmplitudeRate));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccActionInterval(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionInterval, "ActionInterval", "cc.ActionInterval",
		cocos2d::ActionInterval, "cc.FiniteTimeAction",
		nullptr, nullptr);
	LUA_METHOD("getAmplitudeRate", lua_cocos2d_ActionInterval_getAmplitudeRate);
	LUA_METHOD("getElapsed", lua_cocos2d_ActionInterval_getElapsed);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionInterval_initWithDuration);
	LUA_METHOD("setAmplitudeRate", lua_cocos2d_ActionInterval_setAmplitudeRate);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Sequence_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Sequence::*)(const cocos2d::Vector<cocos2d::FiniteTimeAction *>&)>(&cocos2d::Sequence::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sequence_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sequence", "cc.Sequence:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Sequence::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Sequence::initWithTwoActions)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSequence(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Sequence, "Sequence", "cc.Sequence",
		cocos2d::Sequence, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Sequence_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Sequence_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Repeat_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::FiniteTimeAction*(cocos2d::Repeat::*)()>(&cocos2d::Repeat::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Repeat_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:initWithAction");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Repeat::*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::initWithAction)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Repeat_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Repeat", "cc.Repeat:setInnerAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Repeat::*)(cocos2d::FiniteTimeAction*)>(&cocos2d::Repeat::setInnerAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Repeat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Repeat", "cc.Repeat:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Repeat*(*)(cocos2d::FiniteTimeAction*, unsigned int)>(&cocos2d::Repeat::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccRepeat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Repeat, "Repeat", "cc.Repeat",
		cocos2d::Repeat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_Repeat_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_Repeat_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_Repeat_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_Repeat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RepeatForever_getInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:getInnerAction");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::ActionInterval*(cocos2d::RepeatForever::*)()>(&cocos2d::RepeatForever::getInnerAction));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_RepeatForever_initWithAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:initWithAction");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::RepeatForever::*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::initWithAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_setInnerAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:setInnerAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::RepeatForever::*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::setInnerAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_RepeatForever_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RepeatForever", "cc.RepeatForever:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::RepeatForever*(*)(cocos2d::ActionInterval*)>(&cocos2d::RepeatForever::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccRepeatForever(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RepeatForever, "RepeatForever", "cc.RepeatForever",
		cocos2d::RepeatForever, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getInnerAction", lua_cocos2d_RepeatForever_getInnerAction);
	LUA_METHOD("initWithAction", lua_cocos2d_RepeatForever_initWithAction);
	LUA_METHOD("setInnerAction", lua_cocos2d_RepeatForever_setInnerAction);
	LUA_METHOD("create", lua_cocos2d_RepeatForever_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Spawn_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:init");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Spawn::*)(const cocos2d::Vector<cocos2d::FiniteTimeAction *>&)>(&cocos2d::Spawn::init));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Spawn_initWithTwoActions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Spawn", "cc.Spawn:initWithTwoActions");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Spawn::*)(cocos2d::FiniteTimeAction*, cocos2d::FiniteTimeAction*)>(&cocos2d::Spawn::initWithTwoActions)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccSpawn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Spawn, "Spawn", "cc.Spawn",
		cocos2d::Spawn, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_Spawn_init);
	LUA_METHOD("initWithTwoActions", lua_cocos2d_Spawn_initWithTwoActions);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateTo", "cc.RotateTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateTo::*)(float, float, float)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::RotateTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateTo", "cc.RotateTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::RotateTo*(*)(float, float, float)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateTo*(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateTo*(*)(float, float)>(&cocos2d::RotateTo::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateTo, "RotateTo", "cc.RotateTo",
		cocos2d::RotateTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_RotateBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.RotateBy", "cc.RotateBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::RotateBy::*)(float, float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::RotateBy::*)(float, float)>(&cocos2d::RotateBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_RotateBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.RotateBy", "cc.RotateBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::RotateBy*(*)(float, float, float)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateBy*(*)(float, const cocos2d::Vec3&)>(&cocos2d::RotateBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::RotateBy*(*)(float, float)>(&cocos2d::RotateBy::create)));
	LUA_SINVOKE_FOOTER("2,3");
}
int luaReg_Core_ccRotateBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::RotateBy, "RotateBy", "cc.RotateBy",
		cocos2d::RotateBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_RotateBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_RotateBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveBy", "cc.MoveBy:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveBy::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveBy", "cc.MoveBy:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveBy*(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveBy::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveBy*(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveBy::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveBy, "MoveBy", "cc.MoveBy",
		cocos2d::MoveBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MoveTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MoveTo", "cc.MoveTo:initWithDuration");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<bool(cocos2d::MoveTo::*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_MoveTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MoveTo", "cc.MoveTo:create");
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveTo*(*)(float, const cocos2d::Vec3&)>(&cocos2d::MoveTo::create)));
	LUA_TRY_INVOKE_R_OVERLOAD(2, (static_cast<cocos2d::MoveTo*(*)(float, const cocos2d::Vec2&)>(&cocos2d::MoveTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccMoveTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MoveTo, "MoveTo", "cc.MoveTo",
		cocos2d::MoveTo, "cc.MoveBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_MoveTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_MoveTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SkewTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewTo", "cc.SkewTo:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::SkewTo::*)(float, float, float)>(&cocos2d::SkewTo::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewTo", "cc.SkewTo:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SkewTo*(*)(float, float, float)>(&cocos2d::SkewTo::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewTo, "SkewTo", "cc.SkewTo",
		cocos2d::SkewTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_SkewBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.SkewBy", "cc.SkewBy:initWithDuration");
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::SkewBy::*)(float, float, float)>(&cocos2d::SkewBy::initWithDuration)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_SkewBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.SkewBy", "cc.SkewBy:create");
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::SkewBy*(*)(float, float, float)>(&cocos2d::SkewBy::create)));
	LUA_SINVOKE_FOOTER("3");
}
int luaReg_Core_ccSkewBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::SkewBy, "SkewBy", "cc.SkewBy",
		cocos2d::SkewBy, "cc.SkewTo",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_SkewBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_SkewBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpBy", "cc.JumpBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::JumpBy::*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpBy::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpBy", "cc.JumpBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::JumpBy*(*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpBy::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpBy, "JumpBy", "cc.JumpBy",
		cocos2d::JumpBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_JumpTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.JumpTo", "cc.JumpTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::JumpTo::*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpTo::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_JumpTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.JumpTo", "cc.JumpTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::JumpTo*(*)(float, const cocos2d::Vec2&, float, int)>(&cocos2d::JumpTo::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccJumpTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::JumpTo, "JumpTo", "cc.JumpTo",
		cocos2d::JumpTo, "cc.JumpBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_JumpTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_JumpTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_BezierBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierBy", "cc.BezierBy:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::BezierBy::*)(float, const cocos2d::ccBezierConfig&)>(&cocos2d::BezierBy::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_BezierBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierBy", "cc.BezierBy:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::BezierBy*(*)(float, const cocos2d::ccBezierConfig&)>(&cocos2d::BezierBy::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierBy, "BezierBy", "cc.BezierBy",
		cocos2d::BezierBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_BezierBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_BezierBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_BezierTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.BezierTo", "cc.BezierTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::BezierTo::*)(float, const cocos2d::ccBezierConfig&)>(&cocos2d::BezierTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_BezierTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.BezierTo", "cc.BezierTo:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::BezierTo*(*)(float, const cocos2d::ccBezierConfig&)>(&cocos2d::BezierTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBezierTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::BezierTo, "BezierTo", "cc.BezierTo",
		cocos2d::BezierTo, "cc.BezierBy",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_BezierTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_BezierTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(3, (static_cast<bool(cocos2d::ScaleTo::*)(float, float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::ScaleTo::*)(float, float)>(&cocos2d::ScaleTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_ScaleTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleTo", "cc.ScaleTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ScaleTo*(*)(float, float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ScaleTo*(*)(float, float, float)>(&cocos2d::ScaleTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ScaleTo*(*)(float, float)>(&cocos2d::ScaleTo::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleTo, "ScaleTo", "cc.ScaleTo",
		cocos2d::ScaleTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ScaleTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ScaleTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ScaleBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ScaleBy", "cc.ScaleBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ScaleBy*(*)(float, float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(3, (static_cast<cocos2d::ScaleBy*(*)(float, float, float)>(&cocos2d::ScaleBy::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ScaleBy*(*)(float, float)>(&cocos2d::ScaleBy::create)));
	LUA_SINVOKE_FOOTER("2,3,4");
}
int luaReg_Core_ccScaleBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ScaleBy, "ScaleBy", "cc.ScaleBy",
		cocos2d::ScaleBy, "cc.ScaleTo",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_ScaleBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Blink_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Blink", "cc.Blink:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::Blink::*)(float, int)>(&cocos2d::Blink::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Blink_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Blink", "cc.Blink:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::Blink*(*)(float, int)>(&cocos2d::Blink::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccBlink(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Blink, "Blink", "cc.Blink",
		cocos2d::Blink, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_Blink_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_Blink_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeTo", "cc.FadeTo:initWithDuration");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FadeTo::*)(float, uint8_t)>(&cocos2d::FadeTo::initWithDuration)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FadeTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeTo", "cc.FadeTo:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::FadeTo*(*)(float, uint8_t)>(&cocos2d::FadeTo::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccFadeTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeTo, "FadeTo", "cc.FadeTo",
		cocos2d::FadeTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_FadeTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_FadeTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeIn_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeIn", "cc.FadeIn:setReverseAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeIn::*)(cocos2d::FadeTo*)>(&cocos2d::FadeIn::setReverseAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeIn_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeIn", "cc.FadeIn:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FadeIn*(*)(float)>(&cocos2d::FadeIn::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeIn(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeIn, "FadeIn", "cc.FadeIn",
		cocos2d::FadeIn, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeIn_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeIn_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FadeOut_setReverseAction(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FadeOut", "cc.FadeOut:setReverseAction");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FadeOut::*)(cocos2d::FadeTo*)>(&cocos2d::FadeOut::setReverseAction));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FadeOut_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FadeOut", "cc.FadeOut:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::FadeOut*(*)(float)>(&cocos2d::FadeOut::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFadeOut(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FadeOut, "FadeOut", "cc.FadeOut",
		cocos2d::FadeOut, "cc.FadeTo",
		nullptr, nullptr);
	LUA_METHOD("setReverseAction", lua_cocos2d_FadeOut_setReverseAction);
	LUA_METHOD("create", lua_cocos2d_FadeOut_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TintTo_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintTo", "cc.TintTo:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TintTo::*)(float, uint8_t, uint8_t, uint8_t)>(&cocos2d::TintTo::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintTo_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintTo", "cc.TintTo:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TintTo*(*)(float, uint8_t, uint8_t, uint8_t)>(&cocos2d::TintTo::create)));
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TintTo*(*)(float, const cocos2d::Color3B&)>(&cocos2d::TintTo::create)));
	LUA_SINVOKE_FOOTER("2,4");
}
int luaReg_Core_ccTintTo(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintTo, "TintTo", "cc.TintTo",
		cocos2d::TintTo, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintTo_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintTo_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TintBy_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TintBy", "cc.TintBy:initWithDuration");
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::TintBy::*)(float, int16_t, int16_t, int16_t)>(&cocos2d::TintBy::initWithDuration)));
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_TintBy_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TintBy", "cc.TintBy:create");
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::TintBy*(*)(float, int16_t, int16_t, int16_t)>(&cocos2d::TintBy::create)));
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccTintBy(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TintBy, "TintBy", "cc.TintBy",
		cocos2d::TintBy, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_TintBy_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_TintBy_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_DelayTime_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.DelayTime", "cc.DelayTime:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::DelayTime*(*)(float)>(&cocos2d::DelayTime::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccDelayTime(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::DelayTime, "DelayTime", "cc.DelayTime",
		cocos2d::DelayTime, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_DelayTime_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Animate_getAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getAnimation");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Animation*(cocos2d::Animate::*)()const>(&cocos2d::Animate::getAnimation));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Animation*(cocos2d::Animate::*)()>(&cocos2d::Animate::getAnimation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate_getCurrentFrameIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:getCurrentFrameIndex");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Animate::*)()>(&cocos2d::Animate::getCurrentFrameIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Animate_initWithAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:initWithAnimation");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Animate::*)(cocos2d::Animation*)>(&cocos2d::Animate::initWithAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_setAnimation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Animate", "cc.Animate:setAnimation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Animate::*)(cocos2d::Animation*)>(&cocos2d::Animate::setAnimation));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Animate_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Animate", "cc.Animate:create");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Animate*(*)(cocos2d::Animation*)>(&cocos2d::Animate::create));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccAnimate(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Animate, "Animate", "cc.Animate",
		cocos2d::Animate, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getAnimation", lua_cocos2d_Animate_getAnimation);
	LUA_METHOD("getCurrentFrameIndex", lua_cocos2d_Animate_getCurrentFrameIndex);
	LUA_METHOD("initWithAnimation", lua_cocos2d_Animate_initWithAnimation);
	LUA_METHOD("setAnimation", lua_cocos2d_Animate_setAnimation);
	LUA_METHOD("create", lua_cocos2d_Animate_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_TargetedAction_getForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:getForcedTarget");
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<const cocos2d::Node*(cocos2d::TargetedAction::*)()const>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_TRY_INVOKE_R_OVERLOAD(0, static_cast<cocos2d::Node*(cocos2d::TargetedAction::*)()>(&cocos2d::TargetedAction::getForcedTarget));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_TargetedAction_initWithTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:initWithTarget");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::TargetedAction::*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::initWithTarget)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_TargetedAction_setForcedTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:setForcedTarget");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::TargetedAction::*)(cocos2d::Node*)>(&cocos2d::TargetedAction::setForcedTarget));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_TargetedAction_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.TargetedAction", "cc.TargetedAction:create");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::TargetedAction*(*)(cocos2d::Node*, cocos2d::FiniteTimeAction*)>(&cocos2d::TargetedAction::create)));
	LUA_SINVOKE_FOOTER("2");
}
int luaReg_Core_ccTargetedAction(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::TargetedAction, "TargetedAction", "cc.TargetedAction",
		cocos2d::TargetedAction, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("getForcedTarget", lua_cocos2d_TargetedAction_getForcedTarget);
	LUA_METHOD("initWithTarget", lua_cocos2d_TargetedAction_initWithTarget);
	LUA_METHOD("setForcedTarget", lua_cocos2d_TargetedAction_setForcedTarget);
	LUA_METHOD("create", lua_cocos2d_TargetedAction_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_ActionFloat_initWithDuration(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:initWithDuration");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, (static_cast<bool(cocos2d::ActionFloat::*)(float, float, float, cocos2d::ActionFloat::ActionFloatCallback)>(&cocos2d::ActionFloat::initWithDuration)));
	}
	LUA_INVOKE_FOOTER("4");
}
int lua_cocos2d_ActionFloat_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.ActionFloat", "cc.ActionFloat:create");
	if (argc == 4 && !ok && lua_isnil(lua_S, 5)) { arg_cur = 4; } else {
	LUA_TRY_INVOKE_R(4, (static_cast<cocos2d::ActionFloat*(*)(float, float, float, cocos2d::ActionFloat::ActionFloatCallback)>(&cocos2d::ActionFloat::create)));
	}
	LUA_SINVOKE_FOOTER("4");
}
int luaReg_Core_ccActionFloat(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::ActionFloat, "ActionFloat", "cc.ActionFloat",
		cocos2d::ActionFloat, "cc.ActionInterval",
		nullptr, nullptr);
	LUA_METHOD("initWithDuration", lua_cocos2d_ActionFloat_initWithDuration);
	LUA_METHOD("create", lua_cocos2d_ActionFloat_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_UserDefault_deleteValueForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:deleteValueForKey");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::deleteValueForKey));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_UserDefault_flush(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:flush");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::UserDefault::*)()>(&cocos2d::UserDefault::flush));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_UserDefault_getBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getBoolForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::getBoolForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getBoolForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getDoubleForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<double(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::getDoubleForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<double(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getDoubleForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getFloatForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<float(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::getFloatForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<float(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getFloatForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getIntegerForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::getIntegerForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getIntegerForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getLargeIntForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<int64_t(cocos2d::UserDefault::*)(const char*, int64_t)>(&cocos2d::UserDefault::getLargeIntForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getLargeIntForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_getStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getStringForKey");
	LUA_TRY_INVOKE_R(2, (static_cast<std::string_view(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::getStringForKey)));
	LUA_TRY_INVOKE_R(1, static_cast<std::string_view(cocos2d::UserDefault::*)(const char*)>(&cocos2d::UserDefault::getStringForKey));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_UserDefault_setBoolForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setBoolForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, bool)>(&cocos2d::UserDefault::setBoolForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setDoubleForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setDoubleForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, double)>(&cocos2d::UserDefault::setDoubleForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setEncryptEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setEncryptEnabled");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::UserDefault::*)(bool, std::string_view, std::string_view)>(&cocos2d::UserDefault::setEncryptEnabled)));
	LUA_INVOKE_FOOTER("3");
}
int lua_cocos2d_UserDefault_setFloatForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setFloatForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, float)>(&cocos2d::UserDefault::setFloatForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setIntegerForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setIntegerForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, int)>(&cocos2d::UserDefault::setIntegerForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setLargeIntForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setLargeIntForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, int64_t)>(&cocos2d::UserDefault::setLargeIntForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_setStringForKey(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.UserDefault", "cc.UserDefault:setStringForKey");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::UserDefault::*)(const char*, std::string_view)>(&cocos2d::UserDefault::setStringForKey)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_UserDefault_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.UserDefault", "cc.UserDefault:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::UserDefault*(*)()>(&cocos2d::UserDefault::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccUserDefault(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::UserDefault, "UserDefault", "cc.UserDefault",
		cocos2d::UserDefault, "",
		nullptr, nullptr);
	LUA_METHOD("deleteValueForKey", lua_cocos2d_UserDefault_deleteValueForKey);
	LUA_METHOD("flush", lua_cocos2d_UserDefault_flush);
	LUA_METHOD("getBoolForKey", lua_cocos2d_UserDefault_getBoolForKey);
	LUA_METHOD("getDoubleForKey", lua_cocos2d_UserDefault_getDoubleForKey);
	LUA_METHOD("getFloatForKey", lua_cocos2d_UserDefault_getFloatForKey);
	LUA_METHOD("getIntegerForKey", lua_cocos2d_UserDefault_getIntegerForKey);
	LUA_METHOD("getLargeIntForKey", lua_cocos2d_UserDefault_getLargeIntForKey);
	LUA_METHOD("getStringForKey", lua_cocos2d_UserDefault_getStringForKey);
	LUA_METHOD("setBoolForKey", lua_cocos2d_UserDefault_setBoolForKey);
	LUA_METHOD("setDoubleForKey", lua_cocos2d_UserDefault_setDoubleForKey);
	LUA_METHOD("setEncryptEnabled", lua_cocos2d_UserDefault_setEncryptEnabled);
	LUA_METHOD("setFloatForKey", lua_cocos2d_UserDefault_setFloatForKey);
	LUA_METHOD("setIntegerForKey", lua_cocos2d_UserDefault_setIntegerForKey);
	LUA_METHOD("setLargeIntForKey", lua_cocos2d_UserDefault_setLargeIntForKey);
	LUA_METHOD("setStringForKey", lua_cocos2d_UserDefault_setStringForKey);
	LUA_METHOD("getInstance", lua_cocos2d_UserDefault_getInstance);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccAppDirectory(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("AppDirectory");
	LUA_ENUM_ENTRY("PersistentData", cocos2d::AppDirectory::PersistentData);
	LUA_ENUM_ENTRY("TransientData", cocos2d::AppDirectory::TransientData);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int luaReg_Core_ccDirectoryStatus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_ENUM_DEF("DirectoryStatus");
	LUA_ENUM_ENTRY("Ok", cocos2d::DirectoryStatus::Ok);
	LUA_ENUM_ENTRY("NotInitialized", cocos2d::DirectoryStatus::NotInitialized);
	LUA_ENUM_ENTRY("InvalidArgument", cocos2d::DirectoryStatus::InvalidArgument);
	LUA_ENUM_ENTRY("InUse", cocos2d::DirectoryStatus::InUse);
	LUA_ENUM_ENTRY("Unavailable", cocos2d::DirectoryStatus::Unavailable);
	LUA_ENUM_ENTRY("PermissionDenied", cocos2d::DirectoryStatus::PermissionDenied);
	LUA_ENUM_ENTRY("NotDirectory", cocos2d::DirectoryStatus::NotDirectory);
	LUA_ENUM_ENTRY("IoError", cocos2d::DirectoryStatus::IoError);
	LUA_ENUM_ENTRY("Unsupported", cocos2d::DirectoryStatus::Unsupported);
	LUA_ENUM_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_FileUtils_addSearchPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:addSearchPath");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, const bool)>(&cocos2d::FileUtils::addSearchPath)));
	LUA_TRY_INVOKE(1, ([](cocos2d::FileUtils* obj,std::string_view arg0){{return obj->addSearchPath(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_createDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:createDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::createDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::createDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_ensureAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:ensureAppDirectory");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::DirectoryResult(cocos2d::FileUtils::*)(cocos2d::AppDirectory, std::string_view)const>(&cocos2d::FileUtils::ensureAppDirectory)));
	LUA_TRY_INVOKE_R(1, ([](const cocos2d::FileUtils* obj,cocos2d::AppDirectory arg0){{return obj->ensureAppDirectory(std::move(arg0));}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_fullPathForFilename(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathForFilename");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::fullPathForFilename));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_fullPathFromRelativeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:fullPathFromRelativeFile");
	LUA_TRY_INVOKE_R(2, (static_cast<std::string(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::fullPathFromRelativeFile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getDefaultResourceRootPath");
	LUA_TRY_INVOKE_R(0, static_cast<const std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getDefaultResourceRootPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getFileExtension(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileExtension");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getFileExtension));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getFileSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileSize");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(int64_t)>)const>(&cocos2d::FileUtils::getFileSize)));
	LUA_TRY_INVOKE_R(1, static_cast<int64_t(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getFileSize));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_getNativeWritableAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getNativeWritableAbsolutePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getNativeWritableAbsolutePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getOriginalSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getOriginalSearchPaths");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<std::string>(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getOriginalSearchPaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getPersistentDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getPersistentDataPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getPersistentDataPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSearchPaths");
	LUA_TRY_INVOKE_R(0, static_cast<const std::vector<std::string>(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getSearchPaths));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getStringFromFile_1(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getStringFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getStringFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getSuitableFOpen(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getSuitableFOpen");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::getSuitableFOpen));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getTransientDataPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getTransientDataPath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getTransientDataPath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_getValueMapFromData(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromData");
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::ValueMap(cocos2d::FileUtils::*)(const char*, int)const>(&cocos2d::FileUtils::getValueMapFromData)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_getValueMapFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueMapFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueMap(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getValueMapFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getValueVectorFromFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getValueVectorFromFile");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::ValueVector(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::getValueVectorFromFile));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getWritablePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::getWritablePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_isAbsolutePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePath");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isAbsolutePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isDirectoryExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::isDirectoryExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isDirectoryExist));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_isDirectoryExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isDirectoryExistInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isDirectoryExistInternal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isFileExist(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExist");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::isFileExist)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isFileExist));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_isFileExistInternal(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isFileExistInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::isFileExistInternal));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_isPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isPopupNotify");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::FileUtils::*)()const>(&cocos2d::FileUtils::isPopupNotify));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_listFiles(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFiles");
	LUA_TRY_INVOKE_R(1, static_cast<std::vector<std::string>(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::listFiles));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_listFilesAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(std::vector<std::string>)>)const>(&cocos2d::FileUtils::listFilesAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_listFilesRecursivelyAsync(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:listFilesRecursivelyAsync");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(std::vector<std::string>)>)const>(&cocos2d::FileUtils::listFilesRecursivelyAsync)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_purgeCachedEntries(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:purgeCachedEntries");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::FileUtils::*)()>(&cocos2d::FileUtils::purgeCachedEntries));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_queryAppDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:queryAppDirectory");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::DirectoryResult(cocos2d::FileUtils::*)(cocos2d::AppDirectory)const>(&cocos2d::FileUtils::queryAppDirectory));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_removeDirectory(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeDirectory");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::removeDirectory)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::removeDirectory));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_removeFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:removeFile");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::removeFile)));
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)const>(&cocos2d::FileUtils::removeFile));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_FileUtils_renameFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:renameFile");
	LUA_TRY_INVOKE(4, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_OVERLOAD(3, (static_cast<void(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R_OVERLOAD(3, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view, std::string_view)const>(&cocos2d::FileUtils::renameFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::renameFile)));
	LUA_INVOKE_FOOTER("2,3,4");
}
int lua_cocos2d_FileUtils_setDefaultResourceRootPath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setDefaultResourceRootPath");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::setDefaultResourceRootPath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setPopupNotify(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setPopupNotify");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(bool)>(&cocos2d::FileUtils::setPopupNotify));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setSearchPaths(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setSearchPaths");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::FileUtils::*)(const std::vector<std::string>&)>(&cocos2d::FileUtils::setSearchPaths));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_setWritablePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:setWritablePath");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::FileUtils::*)(std::string_view)>(&cocos2d::FileUtils::setWritablePath));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_writeStringToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeStringToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(std::string, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeStringToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(std::string_view, std::string_view)const>(&cocos2d::FileUtils::writeStringToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_writeToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeToFile");
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueMap&, std::string_view)const>(&cocos2d::FileUtils::writeToFile)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_FileUtils_writeValueMapToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueMapToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(cocos2d::ValueMap, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeValueMapToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueMap&, std::string_view)const>(&cocos2d::FileUtils::writeValueMapToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_writeValueVectorToFile(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.FileUtils", "cc.FileUtils:writeValueVectorToFile");
	LUA_TRY_INVOKE(3, (static_cast<void(cocos2d::FileUtils::*)(cocos2d::ValueVector, std::string_view, std::function<void(bool)>)const>(&cocos2d::FileUtils::writeValueVectorToFile)));
	LUA_TRY_INVOKE_R(2, (static_cast<bool(cocos2d::FileUtils::*)(const cocos2d::ValueVector&, std::string_view)const>(&cocos2d::FileUtils::writeValueVectorToFile)));
	LUA_INVOKE_FOOTER("2,3");
}
int lua_cocos2d_FileUtils_getFileShortName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getFileShortName");
	LUA_TRY_INVOKE_R(1, static_cast<std::string(*)(std::string_view)>(&cocos2d::FileUtils::getFileShortName));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_FileUtils_getInstance(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:getInstance");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::FileUtils*(*)()>(&cocos2d::FileUtils::getInstance));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_FileUtils_isAbsolutePathInternal(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.FileUtils", "cc.FileUtils:isAbsolutePathInternal");
	LUA_TRY_INVOKE_R(1, static_cast<bool(*)(std::string_view)>(&cocos2d::FileUtils::isAbsolutePathInternal));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccFileUtils(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::FileUtils, "FileUtils", "cc.FileUtils",
		cocos2d::FileUtils, "",
		nullptr, nullptr);
	LUA_METHOD("addSearchPath", lua_cocos2d_FileUtils_addSearchPath);
	LUA_METHOD("createDirectory", lua_cocos2d_FileUtils_createDirectory);
	LUA_METHOD("ensureAppDirectory", lua_cocos2d_FileUtils_ensureAppDirectory);
	LUA_METHOD("fullPathForFilename", lua_cocos2d_FileUtils_fullPathForFilename);
	LUA_METHOD("fullPathFromRelativeFile", lua_cocos2d_FileUtils_fullPathFromRelativeFile);
	LUA_METHOD("getDefaultResourceRootPath", lua_cocos2d_FileUtils_getDefaultResourceRootPath);
	LUA_METHOD("getFileExtension", lua_cocos2d_FileUtils_getFileExtension);
	LUA_METHOD("getFileSize", lua_cocos2d_FileUtils_getFileSize);
	LUA_METHOD("getNativeWritableAbsolutePath", lua_cocos2d_FileUtils_getNativeWritableAbsolutePath);
	LUA_METHOD("getOriginalSearchPaths", lua_cocos2d_FileUtils_getOriginalSearchPaths);
	LUA_METHOD("getPersistentDataPath", lua_cocos2d_FileUtils_getPersistentDataPath);
	LUA_METHOD("getSearchPaths", lua_cocos2d_FileUtils_getSearchPaths);
	LUA_METHOD("getStringFromFile", lua_cocos2d_FileUtils_getStringFromFile_1);
	LUA_METHOD("getSuitableFOpen", lua_cocos2d_FileUtils_getSuitableFOpen);
	LUA_METHOD("getTransientDataPath", lua_cocos2d_FileUtils_getTransientDataPath);
	LUA_METHOD("getValueMapFromData", lua_cocos2d_FileUtils_getValueMapFromData);
	LUA_METHOD("getValueMapFromFile", lua_cocos2d_FileUtils_getValueMapFromFile);
	LUA_METHOD("getValueVectorFromFile", lua_cocos2d_FileUtils_getValueVectorFromFile);
	LUA_METHOD("getWritablePath", lua_cocos2d_FileUtils_getWritablePath);
	LUA_METHOD("isAbsolutePath", lua_cocos2d_FileUtils_isAbsolutePath);
	LUA_METHOD("isDirectoryExist", lua_cocos2d_FileUtils_isDirectoryExist);
	LUA_METHOD("isDirectoryExistInternal", lua_cocos2d_FileUtils_isDirectoryExistInternal);
	LUA_METHOD("isFileExist", lua_cocos2d_FileUtils_isFileExist);
	LUA_METHOD("isFileExistInternal", lua_cocos2d_FileUtils_isFileExistInternal);
	LUA_METHOD("isPopupNotify", lua_cocos2d_FileUtils_isPopupNotify);
	LUA_METHOD("listFiles", lua_cocos2d_FileUtils_listFiles);
	LUA_METHOD("listFilesAsync", lua_cocos2d_FileUtils_listFilesAsync);
	LUA_METHOD("listFilesRecursivelyAsync", lua_cocos2d_FileUtils_listFilesRecursivelyAsync);
	LUA_METHOD("purgeCachedEntries", lua_cocos2d_FileUtils_purgeCachedEntries);
	LUA_METHOD("queryAppDirectory", lua_cocos2d_FileUtils_queryAppDirectory);
	LUA_METHOD("removeDirectory", lua_cocos2d_FileUtils_removeDirectory);
	LUA_METHOD("removeFile", lua_cocos2d_FileUtils_removeFile);
	LUA_METHOD("renameFile", lua_cocos2d_FileUtils_renameFile);
	LUA_METHOD("setDefaultResourceRootPath", lua_cocos2d_FileUtils_setDefaultResourceRootPath);
	LUA_METHOD("setPopupNotify", lua_cocos2d_FileUtils_setPopupNotify);
	LUA_METHOD("setSearchPaths", lua_cocos2d_FileUtils_setSearchPaths);
	LUA_METHOD("setWritablePath", lua_cocos2d_FileUtils_setWritablePath);
	LUA_METHOD("writeStringToFile", lua_cocos2d_FileUtils_writeStringToFile);
	LUA_METHOD("writeToFile", lua_cocos2d_FileUtils_writeToFile);
	LUA_METHOD("writeValueMapToFile", lua_cocos2d_FileUtils_writeValueMapToFile);
	LUA_METHOD("writeValueVectorToFile", lua_cocos2d_FileUtils_writeValueVectorToFile);
	LUA_METHOD("getFileShortName", lua_cocos2d_FileUtils_getFileShortName);
	LUA_METHOD("getInstance", lua_cocos2d_FileUtils_getInstance);
	LUA_METHOD("isAbsolutePathInternal", lua_cocos2d_FileUtils_isAbsolutePathInternal);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventAcceleration, "EventAcceleration", "cc.EventAcceleration",
		cocos2d::EventAcceleration, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventCustom_getEventName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventCustom", "cc.EventCustom:getEventName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::EventCustom::*)()const>(&cocos2d::EventCustom::getEventName));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventCustom(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventCustom, "EventCustom", "cc.EventCustom",
		cocos2d::EventCustom, "cc.Event",
		nullptr, nullptr);
	LUA_METHOD("getEventName", lua_cocos2d_EventCustom_getEventName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventDispatcher_addCustomEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addCustomEventListener");
	if (argc == 2 && !ok && lua_isnil(lua_S, 3)) { arg_cur = 2; } else {
	LUA_TRY_INVOKE_R(2, (static_cast<cocos2d::EventListenerCustom*(cocos2d::EventDispatcher::*)(std::string_view, const std::function<void(cocos2d::EventCustom*)>&)>(&cocos2d::EventDispatcher::addCustomEventListener)));
	}
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithFixedPriority");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::addEventListenerWithFixedPriority)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, cocos2d::Node*)>(&cocos2d::EventDispatcher::addEventListenerWithSceneGraphPriority)));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_EventDispatcher_dispatchEvent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:dispatchEvent");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Event*)>(&cocos2d::EventDispatcher::dispatchEvent));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_hasEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:hasEventListener");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::EventDispatcher::*)(std::string_view)const>(&cocos2d::EventDispatcher::hasEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventDispatcher::*)()const>(&cocos2d::EventDispatcher::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_pauseEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:pauseEventListenersForTarget");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::pauseEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->pauseEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeAllEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeAllEventListeners");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::EventDispatcher::*)()>(&cocos2d::EventDispatcher::removeAllEventListeners));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_EventDispatcher_removeCustomEventListeners(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeCustomEventListeners");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(std::string_view)>(&cocos2d::EventDispatcher::removeCustomEventListeners));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListener(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListener");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*)>(&cocos2d::EventDispatcher::removeEventListener));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForTarget");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::removeEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->removeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_removeEventListenersForType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:removeEventListenersForType");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener::Type)>(&cocos2d::EventDispatcher::removeEventListenersForType));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_resumeEventListenersForTarget(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:resumeEventListenersForTarget");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::Node*, bool)>(&cocos2d::EventDispatcher::resumeEventListenersForTarget)));
	LUA_TRY_INVOKE(1, ([](cocos2d::EventDispatcher* obj,cocos2d::Node* arg0){{return obj->resumeEventListenersForTarget(arg0);}}));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_EventDispatcher_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::EventDispatcher::*)(bool)>(&cocos2d::EventDispatcher::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_EventDispatcher_setPriority(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventDispatcher", "cc.EventDispatcher:setPriority");
	LUA_TRY_INVOKE(2, (static_cast<void(cocos2d::EventDispatcher::*)(cocos2d::EventListener*, int)>(&cocos2d::EventDispatcher::setPriority)));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccEventDispatcher(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventDispatcher, "EventDispatcher", "cc.EventDispatcher",
		cocos2d::EventDispatcher, "cc.Ref",
		nullptr, nullptr);
	LUA_METHOD("addCustomEventListener", lua_cocos2d_EventDispatcher_addCustomEventListener);
	LUA_METHOD("addEventListenerWithFixedPriority", lua_cocos2d_EventDispatcher_addEventListenerWithFixedPriority);
	LUA_METHOD("addEventListenerWithSceneGraphPriority", lua_cocos2d_EventDispatcher_addEventListenerWithSceneGraphPriority);
	LUA_METHOD("dispatchEvent", lua_cocos2d_EventDispatcher_dispatchEvent);
	LUA_METHOD("hasEventListener", lua_cocos2d_EventDispatcher_hasEventListener);
	LUA_METHOD("isEnabled", lua_cocos2d_EventDispatcher_isEnabled);
	LUA_METHOD("pauseEventListenersForTarget", lua_cocos2d_EventDispatcher_pauseEventListenersForTarget);
	LUA_METHOD("removeAllEventListeners", lua_cocos2d_EventDispatcher_removeAllEventListeners);
	LUA_METHOD("removeCustomEventListeners", lua_cocos2d_EventDispatcher_removeCustomEventListeners);
	LUA_METHOD("removeEventListener", lua_cocos2d_EventDispatcher_removeEventListener);
	LUA_METHOD("removeEventListenersForTarget", lua_cocos2d_EventDispatcher_removeEventListenersForTarget);
	LUA_METHOD("removeEventListenersForType", lua_cocos2d_EventDispatcher_removeEventListenersForType);
	LUA_METHOD("resumeEventListenersForTarget", lua_cocos2d_EventDispatcher_resumeEventListenersForTarget);
	LUA_METHOD("setEnabled", lua_cocos2d_EventDispatcher_setEnabled);
	LUA_METHOD("setPriority", lua_cocos2d_EventDispatcher_setPriority);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccEventFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventFocus, "EventFocus", "cc.EventFocus",
		cocos2d::EventFocus, "cc.Event",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerAcceleration_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerAcceleration", "cc.EventListenerAcceleration:init");
	LUA_TRY_INVOKE_R(1, (static_cast<bool(cocos2d::EventListenerAcceleration::*)(const std::function<void(cocos2d::Acceleration*, cocos2d::Event*)>&)>(&cocos2d::EventListenerAcceleration::init)));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccEventListenerAcceleration(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerAcceleration, "EventListenerAcceleration", "cc.EventListenerAcceleration",
		cocos2d::EventListenerAcceleration, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerAcceleration_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_EventListenerFocus_init(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.EventListenerFocus", "cc.EventListenerFocus:init");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::EventListenerFocus::*)()>(&cocos2d::EventListenerFocus::init));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccEventListenerFocus(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::EventListenerFocus, "EventListenerFocus", "cc.EventListenerFocus",
		cocos2d::EventListenerFocus, "cc.EventListener",
		nullptr, nullptr);
	LUA_METHOD("init", lua_cocos2d_EventListenerFocus_init);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
