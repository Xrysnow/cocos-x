#include "cclua_base_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_base_compat.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"

int lua_cocos2d_Label_disableEffect(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:disableEffect");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(cocos2d::LabelEffect)>(&cocos2d::Label::disableEffect));
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::disableEffect));
	LUA_INVOKE_FOOTER("0,1");
}
int lua_cocos2d_Label_enableBold(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableBold");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::enableBold));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_enableItalics(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableItalics");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::enableItalics));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_enableStrikethrough(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableStrikethrough");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::enableStrikethrough));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_enableUnderline(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableUnderline");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::enableUnderline));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_enableWrap(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:enableWrap");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(bool)>(&cocos2d::Label::enableWrap));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_getAdditionalKerning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getAdditionalKerning");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getAdditionalKerning));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getBMFontFilePath(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getBMFontFilePath");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Label::*)()const>(&cocos2d::Label::getBMFontFilePath));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getBMFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getBMFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getBMFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getHorizontalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextHAlignment(cocos2d::Label::*)()const>(&cocos2d::Label::getHorizontalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getLabelEffectType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLabelEffectType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::LabelEffect(cocos2d::Label::*)()const>(&cocos2d::Label::getLabelEffectType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getLabelType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLabelType");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label::LabelType(cocos2d::Label::*)()const>(&cocos2d::Label::getLabelType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getLetter(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLetter");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Sprite*(cocos2d::Label::*)(int)>(&cocos2d::Label::getLetter));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_getLineHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLineHeight");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getLineHeight));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getLineSpacing(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getLineSpacing");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getLineSpacing));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getMaxLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getMaxLineWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()>(&cocos2d::Label::getMaxLineWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getOutlineSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getOutlineSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getOutlineSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getOverflow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getOverflow");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label::Overflow(cocos2d::Label::*)()const>(&cocos2d::Label::getOverflow));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getRenderingFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getRenderingFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getRenderingFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getShadowBlurRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getShadowBlurRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getShadowBlurRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getStringLength(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getStringLength");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Label::*)()>(&cocos2d::Label::getStringLength));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getStringNumLines(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getStringNumLines");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Label::*)()>(&cocos2d::Label::getStringNumLines));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getSystemFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getSystemFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Label::*)()const>(&cocos2d::Label::getSystemFontName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getSystemFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getSystemFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getSystemFontSize));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getTextAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getTextAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextHAlignment(cocos2d::Label::*)()const>(&cocos2d::Label::getTextAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getVerticalAlignment");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::TextVAlignment(cocos2d::Label::*)()const>(&cocos2d::Label::getVerticalAlignment));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_getWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:getWidth");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::Label::*)()const>(&cocos2d::Label::getWidth));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_isClipMarginEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isClipMarginEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Label::*)()const>(&cocos2d::Label::isClipMarginEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_isShadowEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isShadowEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Label::*)()const>(&cocos2d::Label::isShadowEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_isWrapEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:isWrapEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Label::*)()const>(&cocos2d::Label::isWrapEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_requestSystemFontRefresh(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:requestSystemFontRefresh");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::requestSystemFontRefresh));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_setAdditionalKerning(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setAdditionalKerning");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setAdditionalKerning));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setAlignment");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Label::*)(cocos2d::TextHAlignment, cocos2d::TextVAlignment)>(&cocos2d::Label::setAlignment));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(cocos2d::TextHAlignment)>(&cocos2d::Label::setAlignment));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_Label_setBMFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setBMFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setBMFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setClipMarginEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setClipMarginEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(bool)>(&cocos2d::Label::setClipMarginEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setDimensions(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setDimensions");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Label::*)(float, float)>(&cocos2d::Label::setDimensions));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Label_setHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setHorizontalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setHorizontalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(cocos2d::TextHAlignment)>(&cocos2d::Label::setHorizontalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setLineBreakWithoutSpace(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineBreakWithoutSpace");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(bool)>(&cocos2d::Label::setLineBreakWithoutSpace));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setLineHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setLineHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setLineSpacing(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setLineSpacing");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setLineSpacing));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setMaxLineWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setMaxLineWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setMaxLineWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setOverflow(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setOverflow");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(cocos2d::Label::Overflow)>(&cocos2d::Label::setOverflow));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setSystemFontName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setSystemFontName");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(std::string_view)>(&cocos2d::Label::setSystemFontName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setSystemFontSize(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setSystemFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setSystemFontSize));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setVerticalAlignment(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setVerticalAlignment");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(cocos2d::TextVAlignment)>(&cocos2d::Label::setVerticalAlignment));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_setWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:setWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Label::*)(float)>(&cocos2d::Label::setWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Label_updateContent(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Label", "cc.Label:updateContent");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Label::*)()>(&cocos2d::Label::updateContent));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Label_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Label", "cc.Label:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Label*(*)()>(&cocos2d::Label::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccLabel(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Label, "Label", "cc.Label",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("disableEffect", lua_cocos2d_Label_disableEffect);
	LUA_METHOD("enableBold", lua_cocos2d_Label_enableBold);
	LUA_METHOD("enableItalics", lua_cocos2d_Label_enableItalics);
	LUA_METHOD("enableStrikethrough", lua_cocos2d_Label_enableStrikethrough);
	LUA_METHOD("enableUnderline", lua_cocos2d_Label_enableUnderline);
	LUA_METHOD("enableWrap", lua_cocos2d_Label_enableWrap);
	LUA_METHOD("getAdditionalKerning", lua_cocos2d_Label_getAdditionalKerning);
	LUA_METHOD("getBMFontFilePath", lua_cocos2d_Label_getBMFontFilePath);
	LUA_METHOD("getBMFontSize", lua_cocos2d_Label_getBMFontSize);
	LUA_METHOD("getHeight", lua_cocos2d_Label_getHeight);
	LUA_METHOD("getHorizontalAlignment", lua_cocos2d_Label_getHorizontalAlignment);
	LUA_METHOD("getLabelEffectType", lua_cocos2d_Label_getLabelEffectType);
	LUA_METHOD("getLabelType", lua_cocos2d_Label_getLabelType);
	LUA_METHOD("getLetter", lua_cocos2d_Label_getLetter);
	LUA_METHOD("getLineHeight", lua_cocos2d_Label_getLineHeight);
	LUA_METHOD("getLineSpacing", lua_cocos2d_Label_getLineSpacing);
	LUA_METHOD("getMaxLineWidth", lua_cocos2d_Label_getMaxLineWidth);
	LUA_METHOD("getOutlineSize", lua_cocos2d_Label_getOutlineSize);
	LUA_METHOD("getOverflow", lua_cocos2d_Label_getOverflow);
	LUA_METHOD("getRenderingFontSize", lua_cocos2d_Label_getRenderingFontSize);
	LUA_METHOD("getShadowBlurRadius", lua_cocos2d_Label_getShadowBlurRadius);
	LUA_METHOD("getStringLength", lua_cocos2d_Label_getStringLength);
	LUA_METHOD("getStringNumLines", lua_cocos2d_Label_getStringNumLines);
	LUA_METHOD("getSystemFontName", lua_cocos2d_Label_getSystemFontName);
	LUA_METHOD("getSystemFontSize", lua_cocos2d_Label_getSystemFontSize);
	LUA_METHOD("getTextAlignment", lua_cocos2d_Label_getTextAlignment);
	LUA_METHOD("getVerticalAlignment", lua_cocos2d_Label_getVerticalAlignment);
	LUA_METHOD("getWidth", lua_cocos2d_Label_getWidth);
	LUA_METHOD("isClipMarginEnabled", lua_cocos2d_Label_isClipMarginEnabled);
	LUA_METHOD("isShadowEnabled", lua_cocos2d_Label_isShadowEnabled);
	LUA_METHOD("isWrapEnabled", lua_cocos2d_Label_isWrapEnabled);
	LUA_METHOD("requestSystemFontRefresh", lua_cocos2d_Label_requestSystemFontRefresh);
	LUA_METHOD("setAdditionalKerning", lua_cocos2d_Label_setAdditionalKerning);
	LUA_METHOD("setAlignment", lua_cocos2d_Label_setAlignment);
	LUA_METHOD("setBMFontSize", lua_cocos2d_Label_setBMFontSize);
	LUA_METHOD("setClipMarginEnabled", lua_cocos2d_Label_setClipMarginEnabled);
	LUA_METHOD("setDimensions", lua_cocos2d_Label_setDimensions);
	LUA_METHOD("setHeight", lua_cocos2d_Label_setHeight);
	LUA_METHOD("setHorizontalAlignment", lua_cocos2d_Label_setHorizontalAlignment);
	LUA_METHOD("setLineBreakWithoutSpace", lua_cocos2d_Label_setLineBreakWithoutSpace);
	LUA_METHOD("setLineHeight", lua_cocos2d_Label_setLineHeight);
	LUA_METHOD("setLineSpacing", lua_cocos2d_Label_setLineSpacing);
	LUA_METHOD("setMaxLineWidth", lua_cocos2d_Label_setMaxLineWidth);
	LUA_METHOD("setOverflow", lua_cocos2d_Label_setOverflow);
	LUA_METHOD("setSystemFontName", lua_cocos2d_Label_setSystemFontName);
	LUA_METHOD("setSystemFontSize", lua_cocos2d_Label_setSystemFontSize);
	LUA_METHOD("setVerticalAlignment", lua_cocos2d_Label_setVerticalAlignment);
	LUA_METHOD("setWidth", lua_cocos2d_Label_setWidth);
	LUA_METHOD("updateContent", lua_cocos2d_Label_updateContent);
	LUA_METHOD("create", lua_cocos2d_Label_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccLabelAtlas(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::LabelAtlas, "LabelAtlas", "cc.LabelAtlas",
		cocos2d::AtlasNode, "cc.AtlasNode",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Sprite_getAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getAtlasIndex");
	LUA_TRY_INVOKE_R(0, static_cast<unsigned int(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::getAtlasIndex));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_getBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getBatchNode");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteBatchNode*(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::getBatchNode));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_getResourceName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getResourceName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::getResourceName));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_getResourceType(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getResourceType");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::getResourceType));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_getSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:getSpriteFrame");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::SpriteFrame*(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::getSpriteFrame));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_initWithSpriteFrame(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithSpriteFrame");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Sprite::*)(cocos2d::SpriteFrame*)>(&cocos2d::Sprite::initWithSpriteFrame));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_initWithSpriteFrameName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:initWithSpriteFrameName");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Sprite::*)(std::string_view)>(&cocos2d::Sprite::initWithSpriteFrameName));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_isDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isDirty");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::isDirty));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_isFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFlippedX");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::isFlippedX));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_isFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFlippedY");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::isFlippedY));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_isFrameDisplayed(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isFrameDisplayed");
	LUA_TRY_INVOKE_R(1, static_cast<bool(cocos2d::Sprite::*)(cocos2d::SpriteFrame*)const>(&cocos2d::Sprite::isFrameDisplayed));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_isStretchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isStretchEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::isStretchEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_isTextureRectRotated(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:isTextureRectRotated");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::Sprite::*)()const>(&cocos2d::Sprite::isTextureRectRotated));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_setAtlasIndex(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setAtlasIndex");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(unsigned int)>(&cocos2d::Sprite::setAtlasIndex));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setBatchNode(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setBatchNode");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(cocos2d::SpriteBatchNode*)>(&cocos2d::Sprite::setBatchNode));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setDirty(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setDirty");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(bool)>(&cocos2d::Sprite::setDirty));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setDisplayFrameWithAnimationName(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setDisplayFrameWithAnimationName");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::Sprite::*)(std::string_view, unsigned int)>(&cocos2d::Sprite::setDisplayFrameWithAnimationName));
	LUA_INVOKE_FOOTER("2");
}
int lua_cocos2d_Sprite_setFlippedX(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setFlippedX");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(bool)>(&cocos2d::Sprite::setFlippedX));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setFlippedY(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setFlippedY");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(bool)>(&cocos2d::Sprite::setFlippedY));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setStretchEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setStretchEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::Sprite::*)(bool)>(&cocos2d::Sprite::setStretchEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_setVertexLayout(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.Sprite", "cc.Sprite:setVertexLayout");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::Sprite::*)()>(&cocos2d::Sprite::setVertexLayout));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_Sprite_createWithSpriteFrame(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:createWithSpriteFrame");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Sprite*(*)(cocos2d::SpriteFrame*)>(&cocos2d::Sprite::createWithSpriteFrame));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_Sprite_createWithSpriteFrameName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Sprite", "cc.Sprite:createWithSpriteFrameName");
	LUA_TRY_INVOKE_R(1, static_cast<cocos2d::Sprite*(*)(std::string_view)>(&cocos2d::Sprite::createWithSpriteFrameName));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccSprite(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Sprite, "Sprite", "cc.Sprite",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getAtlasIndex", lua_cocos2d_Sprite_getAtlasIndex);
	LUA_METHOD("getBatchNode", lua_cocos2d_Sprite_getBatchNode);
	LUA_METHOD("getResourceName", lua_cocos2d_Sprite_getResourceName);
	LUA_METHOD("getResourceType", lua_cocos2d_Sprite_getResourceType);
	LUA_METHOD("getSpriteFrame", lua_cocos2d_Sprite_getSpriteFrame);
	LUA_METHOD("initWithSpriteFrame", lua_cocos2d_Sprite_initWithSpriteFrame);
	LUA_METHOD("initWithSpriteFrameName", lua_cocos2d_Sprite_initWithSpriteFrameName);
	LUA_METHOD("isDirty", lua_cocos2d_Sprite_isDirty);
	LUA_METHOD("isFlippedX", lua_cocos2d_Sprite_isFlippedX);
	LUA_METHOD("isFlippedY", lua_cocos2d_Sprite_isFlippedY);
	LUA_METHOD("isFrameDisplayed", lua_cocos2d_Sprite_isFrameDisplayed);
	LUA_METHOD("isStretchEnabled", lua_cocos2d_Sprite_isStretchEnabled);
	LUA_METHOD("isTextureRectRotated", lua_cocos2d_Sprite_isTextureRectRotated);
	LUA_METHOD("setAtlasIndex", lua_cocos2d_Sprite_setAtlasIndex);
	LUA_METHOD("setBatchNode", lua_cocos2d_Sprite_setBatchNode);
	LUA_METHOD("setDirty", lua_cocos2d_Sprite_setDirty);
	LUA_METHOD("setDisplayFrameWithAnimationName", lua_cocos2d_Sprite_setDisplayFrameWithAnimationName);
	LUA_METHOD("setFlippedX", lua_cocos2d_Sprite_setFlippedX);
	LUA_METHOD("setFlippedY", lua_cocos2d_Sprite_setFlippedY);
	LUA_METHOD("setStretchEnabled", lua_cocos2d_Sprite_setStretchEnabled);
	LUA_METHOD("setVertexLayout", lua_cocos2d_Sprite_setVertexLayout);
	LUA_METHOD("createWithSpriteFrame", lua_cocos2d_Sprite_createWithSpriteFrame);
	LUA_METHOD("createWithSpriteFrameName", lua_cocos2d_Sprite_createWithSpriteFrameName);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_Layer_create(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.Layer", "cc.Layer:create");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Layer*(*)()>(&cocos2d::Layer::create));
	LUA_SINVOKE_FOOTER("0");
}
int luaReg_Core_ccLayer(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::Layer, "Layer", "cc.Layer",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("create", lua_cocos2d_Layer_create);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_LayerColor_changeHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeHeight");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerColor::*)(float)>(&cocos2d::LayerColor::changeHeight));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_LayerColor_changeWidth(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeWidth");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerColor::*)(float)>(&cocos2d::LayerColor::changeWidth));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_LayerColor_changeWidthAndHeight(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerColor", "cc.LayerColor:changeWidthAndHeight");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::LayerColor::*)(float, float)>(&cocos2d::LayerColor::changeWidthAndHeight));
	LUA_INVOKE_FOOTER("2");
}
int luaReg_Core_ccLayerColor(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::LayerColor, "LayerColor", "cc.LayerColor",
		cocos2d::Sprite, "cc.Sprite",
		nullptr, nullptr);
	LUA_METHOD("changeHeight", lua_cocos2d_LayerColor_changeHeight);
	LUA_METHOD("changeWidth", lua_cocos2d_LayerColor_changeWidth);
	LUA_METHOD("changeWidthAndHeight", lua_cocos2d_LayerColor_changeWidthAndHeight);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_LayerGradient_getEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getEndOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::LayerGradient::*)()const>(&cocos2d::LayerGradient::getEndOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerGradient_getStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:getStartOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::LayerGradient::*)()const>(&cocos2d::LayerGradient::getStartOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerGradient_isCompressedInterpolation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:isCompressedInterpolation");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::LayerGradient::*)()const>(&cocos2d::LayerGradient::isCompressedInterpolation));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerGradient_setCompressedInterpolation(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerGradient", "cc.LayerGradient:setCompressedInterpolation");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerGradient::*)(bool)>(&cocos2d::LayerGradient::setCompressedInterpolation));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccLayerGradient(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::LayerGradient, "LayerGradient", "cc.LayerGradient",
		cocos2d::LayerColor, "cc.LayerColor",
		nullptr, nullptr);
	LUA_METHOD("getEndOpacity", lua_cocos2d_LayerGradient_getEndOpacity);
	LUA_METHOD("getStartOpacity", lua_cocos2d_LayerGradient_getStartOpacity);
	LUA_METHOD("isCompressedInterpolation", lua_cocos2d_LayerGradient_isCompressedInterpolation);
	LUA_METHOD("setCompressedInterpolation", lua_cocos2d_LayerGradient_setCompressedInterpolation);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_LayerRadialGradient_getEndOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getEndOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::LayerRadialGradient::*)()const>(&cocos2d::LayerRadialGradient::getEndOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerRadialGradient_getExpand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getExpand");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::LayerRadialGradient::*)()const>(&cocos2d::LayerRadialGradient::getExpand));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerRadialGradient_getRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getRadius");
	LUA_TRY_INVOKE_R(0, static_cast<float(cocos2d::LayerRadialGradient::*)()const>(&cocos2d::LayerRadialGradient::getRadius));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerRadialGradient_getStartOpacity(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:getStartOpacity");
	LUA_TRY_INVOKE_R(0, static_cast<uint8_t(cocos2d::LayerRadialGradient::*)()const>(&cocos2d::LayerRadialGradient::getStartOpacity));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_LayerRadialGradient_setExpand(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setExpand");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerRadialGradient::*)(float)>(&cocos2d::LayerRadialGradient::setExpand));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_LayerRadialGradient_setRadius(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerRadialGradient", "cc.LayerRadialGradient:setRadius");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerRadialGradient::*)(float)>(&cocos2d::LayerRadialGradient::setRadius));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccLayerRadialGradient(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::LayerRadialGradient, "LayerRadialGradient", "cc.LayerRadialGradient",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("getEndOpacity", lua_cocos2d_LayerRadialGradient_getEndOpacity);
	LUA_METHOD("getExpand", lua_cocos2d_LayerRadialGradient_getExpand);
	LUA_METHOD("getRadius", lua_cocos2d_LayerRadialGradient_getRadius);
	LUA_METHOD("getStartOpacity", lua_cocos2d_LayerRadialGradient_getStartOpacity);
	LUA_METHOD("setExpand", lua_cocos2d_LayerRadialGradient_setExpand);
	LUA_METHOD("setRadius", lua_cocos2d_LayerRadialGradient_setRadius);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_LayerMultiplex_addLayer(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:addLayer");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerMultiplex::*)(cocos2d::Node*)>(&cocos2d::LayerMultiplex::addLayer));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_LayerMultiplex_switchTo(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:switchTo");
	LUA_TRY_INVOKE(2, static_cast<void(cocos2d::LayerMultiplex::*)(int, bool)>(&cocos2d::LayerMultiplex::switchTo));
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerMultiplex::*)(int)>(&cocos2d::LayerMultiplex::switchTo));
	LUA_INVOKE_FOOTER("1,2");
}
int lua_cocos2d_LayerMultiplex_switchToAndReleaseMe(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.LayerMultiplex", "cc.LayerMultiplex:switchToAndReleaseMe");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::LayerMultiplex::*)(int)>(&cocos2d::LayerMultiplex::switchToAndReleaseMe));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccLayerMultiplex(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::LayerMultiplex, "LayerMultiplex", "cc.LayerMultiplex",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("addLayer", lua_cocos2d_LayerMultiplex_addLayer);
	LUA_METHOD("switchTo", lua_cocos2d_LayerMultiplex_switchTo);
	LUA_METHOD("switchToAndReleaseMe", lua_cocos2d_LayerMultiplex_switchToAndReleaseMe);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItem_activate(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:activate");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MenuItem::*)()>(&cocos2d::MenuItem::activate));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItem_isEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:isEnabled");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MenuItem::*)()const>(&cocos2d::MenuItem::isEnabled));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItem_isSelected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:isSelected");
	LUA_TRY_INVOKE_R(0, static_cast<bool(cocos2d::MenuItem::*)()const>(&cocos2d::MenuItem::isSelected));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItem_selected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:selected");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MenuItem::*)()>(&cocos2d::MenuItem::selected));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItem_setEnabled(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:setEnabled");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItem::*)(bool)>(&cocos2d::MenuItem::setEnabled));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItem_unselected(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItem", "cc.MenuItem:unselected");
	LUA_TRY_INVOKE(0, static_cast<void(cocos2d::MenuItem::*)()>(&cocos2d::MenuItem::unselected));
	LUA_INVOKE_FOOTER("0");
}
int luaReg_Core_ccMenuItem(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItem, "MenuItem", "cc.MenuItem",
		cocos2d::Node, "cc.Node",
		nullptr, nullptr);
	LUA_METHOD("activate", lua_cocos2d_MenuItem_activate);
	LUA_METHOD("isEnabled", lua_cocos2d_MenuItem_isEnabled);
	LUA_METHOD("isSelected", lua_cocos2d_MenuItem_isSelected);
	LUA_METHOD("selected", lua_cocos2d_MenuItem_selected);
	LUA_METHOD("setEnabled", lua_cocos2d_MenuItem_setEnabled);
	LUA_METHOD("unselected", lua_cocos2d_MenuItem_unselected);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItemLabel_getLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:getLabel");
	LUA_TRY_INVOKE_R(0, static_cast<cocos2d::Node*(cocos2d::MenuItemLabel::*)()const>(&cocos2d::MenuItemLabel::getLabel));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemLabel_getString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:getString");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::MenuItemLabel::*)()const>(&cocos2d::MenuItemLabel::getString));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemLabel_setLabel(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:setLabel");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemLabel::*)(cocos2d::Node*)>(&cocos2d::MenuItemLabel::setLabel));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemLabel_setString(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemLabel", "cc.MenuItemLabel:setString");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemLabel::*)(std::string_view)>(&cocos2d::MenuItemLabel::setString));
	LUA_INVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemLabel(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemLabel, "MenuItemLabel", "cc.MenuItemLabel",
		cocos2d::MenuItem, "cc.MenuItem",
		nullptr, nullptr);
	LUA_METHOD("getLabel", lua_cocos2d_MenuItemLabel_getLabel);
	LUA_METHOD("getString", lua_cocos2d_MenuItemLabel_getString);
	LUA_METHOD("setLabel", lua_cocos2d_MenuItemLabel_setLabel);
	LUA_METHOD("setString", lua_cocos2d_MenuItemLabel_setString);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}

int luaReg_Core_ccMenuItemAtlasFont(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemAtlasFont, "MenuItemAtlasFont", "cc.MenuItemAtlasFont",
		cocos2d::MenuItemLabel, "cc.MenuItemLabel",
		nullptr, nullptr);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
int lua_cocos2d_MenuItemFont_getFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontNameObj");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(cocos2d::MenuItemFont::*)()const>(&cocos2d::MenuItemFont::getFontNameObj));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_getFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSizeObj");
	LUA_TRY_INVOKE_R(0, static_cast<int(cocos2d::MenuItemFont::*)()const>(&cocos2d::MenuItemFont::getFontSizeObj));
	LUA_INVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_setFontNameObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontNameObj");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemFont::*)(std::string_view)>(&cocos2d::MenuItemFont::setFontNameObj));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_setFontSizeObj(lua_State* lua_S)
{
	LUA_INVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSizeObj");
	LUA_TRY_INVOKE(1, static_cast<void(cocos2d::MenuItemFont::*)(int)>(&cocos2d::MenuItemFont::setFontSizeObj));
	LUA_INVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_getFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontName");
	LUA_TRY_INVOKE_R(0, static_cast<std::string_view(*)()>(&cocos2d::MenuItemFont::getFontName));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_getFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:getFontSize");
	LUA_TRY_INVOKE_R(0, static_cast<int(*)()>(&cocos2d::MenuItemFont::getFontSize));
	LUA_SINVOKE_FOOTER("0");
}
int lua_cocos2d_MenuItemFont_setFontName(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontName");
	LUA_TRY_INVOKE(1, static_cast<void(*)(std::string_view)>(&cocos2d::MenuItemFont::setFontName));
	LUA_SINVOKE_FOOTER("1");
}
int lua_cocos2d_MenuItemFont_setFontSize(lua_State* lua_S)
{
	LUA_SINVOKE_HEADER("cc.MenuItemFont", "cc.MenuItemFont:setFontSize");
	LUA_TRY_INVOKE(1, static_cast<void(*)(int)>(&cocos2d::MenuItemFont::setFontSize));
	LUA_SINVOKE_FOOTER("1");
}
int luaReg_Core_ccMenuItemFont(lua_State* lua_S)
{
	LUA_ENTRY("cc");
	LUA_CLS_DEF_BASE(cocos2d::MenuItemFont, "MenuItemFont", "cc.MenuItemFont",
		cocos2d::MenuItemLabel, "cc.MenuItemLabel",
		nullptr, nullptr);
	LUA_METHOD("getFontNameObj", lua_cocos2d_MenuItemFont_getFontNameObj);
	LUA_METHOD("getFontSizeObj", lua_cocos2d_MenuItemFont_getFontSizeObj);
	LUA_METHOD("setFontNameObj", lua_cocos2d_MenuItemFont_setFontNameObj);
	LUA_METHOD("setFontSizeObj", lua_cocos2d_MenuItemFont_setFontSizeObj);
	LUA_METHOD("getFontName", lua_cocos2d_MenuItemFont_getFontName);
	LUA_METHOD("getFontSize", lua_cocos2d_MenuItemFont_getFontSize);
	LUA_METHOD("setFontName", lua_cocos2d_MenuItemFont_setFontName);
	LUA_METHOD("setFontSize", lua_cocos2d_MenuItemFont_setFontSize);
	LUA_CLS_END();
	LUA_ENTRY_END(1);
	return 0;
}
