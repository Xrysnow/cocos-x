#include "scripting/lua-bindings/auto/cclua_base_auto.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "scripting/lua-bindings/manual/CCComponentLua.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"


#include "cclua_base_compat.hpp"
namespace core_base_binding
{
struct Error { const char* name; const char* native; const char* format; const char* label; int expected; bool invalid; };
static const Error errors[] = {
        {"cc.Ref:release", "lua_cc_base_Ref_release", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ref:release", 0, true},
        {"cc.Ref:retain", "lua_cc_base_Ref_retain", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ref:retain", 0, true},
        {"cc.Ref:getReferenceCount", "lua_cc_base_Ref_getReferenceCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ref:getReferenceCount", 0, true},
        {"cc.Console:listenOnTCP", "lua_cc_base_Console_listenOnTCP", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:listenOnTCP", 1, true},
        {"cc.Console:delCommand", "lua_cc_base_Console_delCommand", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:delCommand", 1, true},
        {"cc.Console:stop", "lua_cc_base_Console_stop", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:stop", 0, true},
        {"cc.Console:listenOnFileDescriptor", "lua_cc_base_Console_listenOnFileDescriptor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:listenOnFileDescriptor", 1, true},
        {"cc.Console:setBindAddress", "lua_cc_base_Console_setBindAddress", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:setBindAddress", 1, true},
        {"cc.Console:print", "lua_cc_base_Console_print", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:print", 1, true},
        {"cc.Console:isIpv6Server", "lua_cc_base_Console_isIpv6Server", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:isIpv6Server", 0, true},
        {"cc.EventListener:setEnabled", "lua_cc_base_EventListener_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListener:setEnabled", 1, true},
        {"cc.EventListener:isEnabled", "lua_cc_base_EventListener_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListener:isEnabled", 0, true},
        {"cc.EventListener:clone", "lua_cc_base_EventListener_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListener:clone", 0, true},
        {"cc.EventListener:checkAvailable", "lua_cc_base_EventListener_checkAvailable", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListener:checkAvailable", 0, true},
        {"cc.Texture2D:getMaxT", "lua_cc_base_Texture2D_getMaxT", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getMaxT", 0, true},
        {"cc.Texture2D:getStringForFormat", "lua_cc_base_Texture2D_getStringForFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getStringForFormat", 0, true},
        {"cc.Texture2D:initWithImage", "lua_cc_base_Texture2D_initWithImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:initWithImage", 1, false},
        {"cc.Texture2D:getMaxS", "lua_cc_base_Texture2D_getMaxS", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getMaxS", 0, true},
        {"cc.Texture2D:hasPremultipliedAlpha", "lua_cc_base_Texture2D_hasPremultipliedAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:hasPremultipliedAlpha", 0, true},
        {"cc.Texture2D:getPixelsHigh", "lua_cc_base_Texture2D_getPixelsHigh", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getPixelsHigh", 0, true},
        {"cc.Texture2D:getBitsPerPixelForFormat", "lua_cc_base_Texture2D_getBitsPerPixelForFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getBitsPerPixelForFormat", 0, false},
        {"cc.Texture2D:setMaxS", "lua_cc_base_Texture2D_setMaxS", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setMaxS", 1, true},
        {"cc.Texture2D:setMaxT", "lua_cc_base_Texture2D_setMaxT", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setMaxT", 1, true},
        {"cc.Texture2D:getPath", "lua_cc_base_Texture2D_getPath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getPath", 0, true},
        {"cc.Texture2D:isRenderTarget", "lua_cc_base_Texture2D_isRenderTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:isRenderTarget", 0, true},
        {"cc.Texture2D:setAliasTexParameters", "lua_cc_base_Texture2D_setAliasTexParameters", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setAliasTexParameters", 0, true},
        {"cc.Texture2D:setAntiAliasTexParameters", "lua_cc_base_Texture2D_setAntiAliasTexParameters", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setAntiAliasTexParameters", 0, true},
        {"cc.Texture2D:generateMipmap", "lua_cc_base_Texture2D_generateMipmap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:generateMipmap", 0, true},
        {"cc.Texture2D:getPixelFormat", "lua_cc_base_Texture2D_getPixelFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getPixelFormat", 0, true},
        {"cc.Texture2D:setPremultipliedAlpha", "lua_cc_base_Texture2D_setPremultipliedAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setPremultipliedAlpha", 1, true},
        {"cc.Texture2D:getBackendTexture", "lua_cc_base_Texture2D_getBackendTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getBackendTexture", 0, true},
        {"cc.Texture2D:getSamplerFlags", "lua_cc_base_Texture2D_getSamplerFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getSamplerFlags", 0, true},
        {"cc.Texture2D:getPixelsWide", "lua_cc_base_Texture2D_getPixelsWide", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getPixelsWide", 0, true},
        {"cc.Texture2D:hasMipmaps", "lua_cc_base_Texture2D_hasMipmaps", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:hasMipmaps", 0, true},
        {"cc.Texture2D:setRenderTarget", "lua_cc_base_Texture2D_setRenderTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:setRenderTarget", 1, true},
        {"cc.Texture2D:updateWithImage", "lua_cc_base_Texture2D_updateWithImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:updateWithImage", 2, true},
        {"cc.Texture2D:setDefaultAlphaPixelFormat", "lua_cc_base_Texture2D_setDefaultAlphaPixelFormat", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Texture2D:setDefaultAlphaPixelFormat", 1, true},
        {"cc.Texture2D:getDefaultAlphaPixelFormat", "lua_cc_base_Texture2D_getDefaultAlphaPixelFormat", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Texture2D:getDefaultAlphaPixelFormat", 0, true},
        {"cc.Touch:getCurrentForce", "lua_cc_base_Touch_getCurrentForce", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getCurrentForce", 0, true},
        {"cc.Touch:setTouchInfo", "lua_cc_base_Touch_setTouchInfo", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:setTouchInfo", 3, false},
        {"cc.Touch:getMaxForce", "lua_cc_base_Touch_getMaxForce", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getMaxForce", 0, true},
        {"cc.Event:isStopped", "lua_cc_base_Event_isStopped", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Event:isStopped", 0, true},
        {"cc.Event:getType", "lua_cc_base_Event_getType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Event:getType", 0, true},
        {"cc.Event:getCurrentTarget", "lua_cc_base_Event_getCurrentTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Event:getCurrentTarget", 0, true},
        {"cc.Event:stopPropagation", "lua_cc_base_Event_stopPropagation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Event:stopPropagation", 0, true},
        {"cc.EventTouch:getEventCode", "lua_cc_base_EventTouch_getEventCode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventTouch:getEventCode", 0, true},
        {"cc.EventTouch:setEventCode", "lua_cc_base_EventTouch_setEventCode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventTouch:setEventCode", 1, true},
        {"cc.Component:setEnabled", "lua_cc_base_Component_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:setEnabled", 1, true},
        {"cc.Component:onRemove", "lua_cc_base_Component_onRemove", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:onRemove", 0, true},
        {"cc.Component:setName", "lua_cc_base_Component_setName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:setName", 1, true},
        {"cc.Component:isEnabled", "lua_cc_base_Component_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:isEnabled", 0, true},
        {"cc.Component:update", "lua_cc_base_Component_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:update", 1, true},
        {"cc.Component:getOwner", "lua_cc_base_Component_getOwner", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:getOwner", 0, true},
        {"cc.Component:init", "lua_cc_base_Component_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:init", 0, true},
        {"cc.Component:setOwner", "lua_cc_base_Component_setOwner", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:setOwner", 1, true},
        {"cc.Component:getName", "lua_cc_base_Component_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:getName", 0, true},
        {"cc.Component:onAdd", "lua_cc_base_Component_onAdd", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Component:onAdd", 0, true},
        {"cc.Component:create", "lua_cc_base_Component_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Component:create", 0, true},
        {"cc.Node:updateProgramStateTexture", "lua_cc_base_Node_updateProgramStateTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:updateProgramStateTexture", 1, true},
        {"cc.Node:getDescription", "lua_cc_base_Node_getDescription", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getDescription", 0, true},
        {"cc.Node:setRotationSkewY", "lua_cc_base_Node_setRotationSkewY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setRotationSkewY", 1, true},
        {"cc.Node:setOpacityModifyRGB", "lua_cc_base_Node_setOpacityModifyRGB", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOpacityModifyRGB", 1, true},
        {"cc.Node:setCascadeOpacityEnabled", "lua_cc_base_Node_setCascadeOpacityEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setCascadeOpacityEnabled", 1, true},
        {"cc.Node:setActionManager", "lua_cc_base_Node_setActionManager", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setActionManager", 1, true},
        {"cc.Node:isIgnoreAnchorPointForPosition", "lua_cc_base_Node_isIgnoreAnchorPointForPosition", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isIgnoreAnchorPointForPosition", 0, true},
        {"cc.Node:getChildByName", "lua_cc_base_Node_getChildByName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getChildByName", 1, true},
        {"cc.Node:init", "lua_cc_base_Node_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:init", 0, true},
        {"cc.Node:getCameraMask", "lua_cc_base_Node_getCameraMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getCameraMask", 0, true},
        {"cc.Node:setRotation", "lua_cc_base_Node_setRotation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setRotation", 1, true},
        {"cc.Node:setScaleZ", "lua_cc_base_Node_setScaleZ", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setScaleZ", 1, true},
        {"cc.Node:setScaleY", "lua_cc_base_Node_setScaleY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setScaleY", 1, true},
        {"cc.Node:setScaleX", "lua_cc_base_Node_setScaleX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setScaleX", 1, true},
        {"cc.Node:setRotationSkewX", "lua_cc_base_Node_setRotationSkewX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setRotationSkewX", 1, true},
        {"cc.Node:removeAllComponents", "lua_cc_base_Node_removeAllComponents", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:removeAllComponents", 0, true},
        {"cc.Node:_setLocalZOrder", "lua_cc_base_Node__setLocalZOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:_setLocalZOrder", 1, true},
        {"cc.Node:getTag", "lua_cc_base_Node_getTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getTag", 0, true},
        {"cc.Node:initLayer", "lua_cc_base_Node_initLayer", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:initLayer", 0, true},
        {"cc.Node:setProgramStateWithRegistry", "lua_cc_base_Node_setProgramStateWithRegistry", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setProgramStateWithRegistry", 2, true},
        {"cc.Node:removeChild", "lua_cc_base_Node_removeChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:removeChild", 1, true},
        {"cc.Node:getScene", "lua_cc_base_Node_getScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getScene", 0, true},
        {"cc.Node:getEventDispatcher", "lua_cc_base_Node_getEventDispatcher", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getEventDispatcher", 0, true},
        {"cc.Node:setSkewX", "lua_cc_base_Node_setSkewX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setSkewX", 1, true},
        {"cc.Node:setSkewY", "lua_cc_base_Node_setSkewY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setSkewY", 1, true},
        {"cc.Node:stopActionsByFlags", "lua_cc_base_Node_stopActionsByFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:stopActionsByFlags", 1, true},
        {"cc.Node:isCascadeOpacityEnabled", "lua_cc_base_Node_isCascadeOpacityEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isCascadeOpacityEnabled", 0, true},
        {"cc.Node:setParent", "lua_cc_base_Node_setParent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setParent", 1, true},
        {"cc.Node:getName", "lua_cc_base_Node_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getName", 0, true},
        {"cc.Node:resume", "lua_cc_base_Node_resume", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:resume", 0, true},
        {"cc.Node:pause", "lua_cc_base_Node_pause", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:pause", 0, true},
        {"cc.Node:applyMaskOnEnter", "lua_cc_base_Node_applyMaskOnEnter", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:applyMaskOnEnter", 1, true},
        {"cc.Node:isOpacityModifyRGB", "lua_cc_base_Node_isOpacityModifyRGB", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isOpacityModifyRGB", 0, true},
        {"cc.Node:stopActionByTag", "lua_cc_base_Node_stopActionByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:stopActionByTag", 1, true},
        {"cc.Node:reorderChild", "lua_cc_base_Node_reorderChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:reorderChild", 2, true},
        {"cc.Node:setPositionZ", "lua_cc_base_Node_setPositionZ", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPositionZ", 1, true},
        {"cc.Node:setPositionX", "lua_cc_base_Node_setPositionX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPositionX", 1, true},
        {"cc.Node:getNumberOfRunningActions", "lua_cc_base_Node_getNumberOfRunningActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getNumberOfRunningActions", 0, true},
        {"cc.Node:updateTransform", "lua_cc_base_Node_updateTransform", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:updateTransform", 0, true},
        {"cc.Node:isVisible", "lua_cc_base_Node_isVisible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isVisible", 0, true},
        {"cc.Node:getChildrenCount", "lua_cc_base_Node_getChildrenCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getChildrenCount", 0, true},
        {"cc.Node:addComponent", "lua_cc_base_Node_addComponent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:addComponent", 1, true},
        {"cc.Node:runAction", "lua_cc_base_Node_runAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:runAction", 1, true},
        {"cc.Node:getRotation", "lua_cc_base_Node_getRotation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getRotation", 0, true},
        {"cc.Node:removeChildByName", "lua_cc_base_Node_removeChildByName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:removeChildByName", 1, true},
        {"cc.Node:resetChild", "lua_cc_base_Node_resetChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:resetChild", 2, true},
        {"cc.Node:setScheduler", "lua_cc_base_Node_setScheduler", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setScheduler", 1, true},
        {"cc.Node:stopAllActions", "lua_cc_base_Node_stopAllActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:stopAllActions", 0, true},
        {"cc.Node:getSkewX", "lua_cc_base_Node_getSkewX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getSkewX", 0, true},
        {"cc.Node:getSkewY", "lua_cc_base_Node_getSkewY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getSkewY", 0, true},
        {"cc.Node:getActionByTag", "lua_cc_base_Node_getActionByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getActionByTag", 1, true},
        {"cc.Node:setName", "lua_cc_base_Node_setName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setName", 1, true},
        {"cc.Node:update", "lua_cc_base_Node_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:update", 1, true},
        {"cc.Node:getDisplayedOpacity", "lua_cc_base_Node_getDisplayedOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getDisplayedOpacity", 0, true},
        {"cc.Node:getLocalZOrder", "lua_cc_base_Node_getLocalZOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getLocalZOrder", 0, true},
        {"cc.Node:isRunning", "lua_cc_base_Node_isRunning", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isRunning", 0, true},
        {"cc.Node:getPositionZ", "lua_cc_base_Node_getPositionZ", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPositionZ", 0, true},
        {"cc.Node:getPositionY", "lua_cc_base_Node_getPositionY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPositionY", 0, true},
        {"cc.Node:getPositionX", "lua_cc_base_Node_getPositionX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPositionX", 0, true},
        {"cc.Node:removeChildByTag", "lua_cc_base_Node_removeChildByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:removeChildByTag", 1, true},
        {"cc.Node:setPositionY", "lua_cc_base_Node_setPositionY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPositionY", 1, true},
        {"cc.Node:setVisible", "lua_cc_base_Node_setVisible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setVisible", 1, true},
        {"cc.Node:setGlobalZOrder", "lua_cc_base_Node_setGlobalZOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setGlobalZOrder", 1, true},
        {"cc.Node:setScale", "lua_cc_base_Node_setScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setScale", 1, false},
        {"cc.Node:getChildByTag", "lua_cc_base_Node_getChildByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getChildByTag", 1, true},
        {"cc.Node:getScaleZ", "lua_cc_base_Node_getScaleZ", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getScaleZ", 0, true},
        {"cc.Node:getScaleY", "lua_cc_base_Node_getScaleY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getScaleY", 0, true},
        {"cc.Node:getScaleX", "lua_cc_base_Node_getScaleX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getScaleX", 0, true},
        {"cc.Node:setLocalZOrder", "lua_cc_base_Node_setLocalZOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setLocalZOrder", 1, true},
        {"cc.Node:setCascadeColorEnabled", "lua_cc_base_Node_setCascadeColorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setCascadeColorEnabled", 1, true},
        {"cc.Node:cleanup", "lua_cc_base_Node_cleanup", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:cleanup", 0, true},
        {"cc.Node:getComponent", "lua_cc_base_Node_getComponent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getComponent", 1, true},
        {"cc.Node:stopAllActionsByTag", "lua_cc_base_Node_stopAllActionsByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:stopAllActionsByTag", 1, true},
        {"cc.Node:setIgnoreAnchorPointForPosition", "lua_cc_base_Node_setIgnoreAnchorPointForPosition", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setIgnoreAnchorPointForPosition", 1, true},
        {"cc.Node:setEventDispatcher", "lua_cc_base_Node_setEventDispatcher", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setEventDispatcher", 1, true},
        {"cc.Node:getGlobalZOrder", "lua_cc_base_Node_getGlobalZOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getGlobalZOrder", 0, true},
        {"cc.Node:setUserObject", "lua_cc_base_Node_setUserObject", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setUserObject", 1, true},
        {"cc.Node:getNumberOfRunningActionsByTag", "lua_cc_base_Node_getNumberOfRunningActionsByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getNumberOfRunningActionsByTag", 1, true},
        {"cc.Node:sortAllChildren", "lua_cc_base_Node_sortAllChildren", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:sortAllChildren", 0, true},
        {"cc.Node:getProgramState", "lua_cc_base_Node_getProgramState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getProgramState", 0, true},
        {"cc.Node:getScale", "lua_cc_base_Node_getScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getScale", 0, true},
        {"cc.Node:getOpacity", "lua_cc_base_Node_getOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getOpacity", 0, true},
        {"cc.Node:updateOrderOfArrival", "lua_cc_base_Node_updateOrderOfArrival", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:updateOrderOfArrival", 0, true},
        {"cc.Node:getRotationSkewX", "lua_cc_base_Node_getRotationSkewX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getRotationSkewX", 0, true},
        {"cc.Node:getRotationSkewY", "lua_cc_base_Node_getRotationSkewY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getRotationSkewY", 0, true},
        {"cc.Node:setTag", "lua_cc_base_Node_setTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setTag", 1, true},
        {"cc.Node:isCascadeColorEnabled", "lua_cc_base_Node_isCascadeColorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isCascadeColorEnabled", 0, true},
        {"cc.Node:stopAction", "lua_cc_base_Node_stopAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:stopAction", 1, true},
        {"cc.Node:create", "lua_cc_base_Node_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Node:create", 0, true},
        {"cc.Node:getAttachedNodeCount", "lua_cc_base_Node_getAttachedNodeCount", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Node:getAttachedNodeCount", 0, true},
        {"cc.Scene:setCameraOrderDirty", "lua_cc_base_Scene_setCameraOrderDirty", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:setCameraOrderDirty", 0, true},
        {"cc.Scene:onProjectionChanged", "lua_cc_base_Scene_onProjectionChanged", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:onProjectionChanged", 1, true},
        {"cc.Scene:getDefaultCamera", "lua_cc_base_Scene_getDefaultCamera", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:getDefaultCamera", 0, true},
        {"cc.Scene:create", "lua_cc_base_Scene_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Scene:create", 0, true},
        {"cc.GLView:setFrameSize", "lua_cc_base_GLView_setFrameSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setFrameSize", 2, true},
        {"cc.GLView:getScaleY", "lua_cc_base_GLView_getScaleY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getScaleY", 0, true},
        {"cc.GLView:setContentScaleFactor", "lua_cc_base_GLView_setContentScaleFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setContentScaleFactor", 1, true},
        {"cc.GLView:getContentScaleFactor", "lua_cc_base_GLView_getContentScaleFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getContentScaleFactor", 0, true},
        {"cc.GLView:setIMEKeyboardState", "lua_cc_base_GLView_setIMEKeyboardState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setIMEKeyboardState", 1, true},
        {"cc.GLView:setScissorInPoints", "lua_cc_base_GLView_setScissorInPoints", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setScissorInPoints", 4, true},
        {"cc.GLView:getViewName", "lua_cc_base_GLView_getViewName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getViewName", 0, true},
        {"cc.GLView:isOpenGLReady", "lua_cc_base_GLView_isOpenGLReady", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:isOpenGLReady", 0, true},
        {"cc.GLView:setCursorVisible", "lua_cc_base_GLView_setCursorVisible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setCursorVisible", 1, true},
        {"cc.GLView:setDefaultIcon", "lua_cc_base_GLView_setDefaultIcon", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setDefaultIcon", 0, true},
        {"cc.GLView:getScaleX", "lua_cc_base_GLView_getScaleX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getScaleX", 0, true},
        {"cc.GLView:setFrameZoomFactor", "lua_cc_base_GLView_setFrameZoomFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setFrameZoomFactor", 1, true},
        {"cc.GLView:getFrameZoomFactor", "lua_cc_base_GLView_getFrameZoomFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getFrameZoomFactor", 0, true},
        {"cc.GLView:windowShouldClose", "lua_cc_base_GLView_windowShouldClose", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:windowShouldClose", 0, true},
        {"cc.GLView:swapBuffers", "lua_cc_base_GLView_swapBuffers", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:swapBuffers", 0, true},
        {"cc.GLView:setDesignResolutionSize", "lua_cc_base_GLView_setDesignResolutionSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setDesignResolutionSize", 3, true},
        {"cc.GLView:getResolutionPolicy", "lua_cc_base_GLView_getResolutionPolicy", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getResolutionPolicy", 0, true},
        {"cc.GLView:endToLua", "lua_cc_base_GLView_end", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:end", 0, true},
        {"cc.GLView:isRetinaDisplay", "lua_cc_base_GLView_isRetinaDisplay", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:isRetinaDisplay", 0, true},
        {"cc.GLView:renderScene", "lua_cc_base_GLView_renderScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:renderScene", 2, true},
        {"cc.GLView:setViewPortInPoints", "lua_cc_base_GLView_setViewPortInPoints", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setViewPortInPoints", 4, true},
        {"cc.GLView:getRetinaFactor", "lua_cc_base_GLView_getRetinaFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getRetinaFactor", 0, true},
        {"cc.GLView:setViewName", "lua_cc_base_GLView_setViewName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:setViewName", 1, true},
        {"cc.GLView:isScissorEnabled", "lua_cc_base_GLView_isScissorEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:isScissorEnabled", 0, true},
        {"cc.GLView:pollEvents", "lua_cc_base_GLView_pollEvents", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:pollEvents", 0, true},
        {"cc.Director:pause", "lua_cc_base_Director_pause", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:pause", 0, true},
        {"cc.Director:setEventDispatcher", "lua_cc_base_Director_setEventDispatcher", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setEventDispatcher", 1, true},
        {"cc.Director:setContentScaleFactor", "lua_cc_base_Director_setContentScaleFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setContentScaleFactor", 1, true},
        {"cc.Director:getDeltaTime", "lua_cc_base_Director_getDeltaTime", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getDeltaTime", 0, true},
        {"cc.Director:setStatsDisplay", "lua_cc_base_Director_setStatsDisplay", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setStatsDisplay", 1, true},
        {"cc.Director:getContentScaleFactor", "lua_cc_base_Director_getContentScaleFactor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getContentScaleFactor", 0, true},
        {"cc.Director:setGLDefaultValues", "lua_cc_base_Director_setGLDefaultValues", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setGLDefaultValues", 0, true},
        {"cc.Director:setActionManager", "lua_cc_base_Director_setActionManager", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setActionManager", 1, true},
        {"cc.Director:popToRootScene", "lua_cc_base_Director_popToRootScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:popToRootScene", 0, true},
        {"cc.Director:getNotificationNode", "lua_cc_base_Director_getNotificationNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getNotificationNode", 0, true},
        {"cc.Director:getTextureCache", "lua_cc_base_Director_getTextureCache", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getTextureCache", 0, true},
        {"cc.Director:isSendCleanupToScene", "lua_cc_base_Director_isSendCleanupToScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isSendCleanupToScene", 0, true},
        {"cc.Director:mainLoop", "lua_cc_base_Director_mainLoop", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:mainLoop", 0, false},
        {"cc.Director:getFrameRate", "lua_cc_base_Director_getFrameRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getFrameRate", 0, true},
        {"cc.Director:getSecondsPerFrame", "lua_cc_base_Director_getSecondsPerFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getSecondsPerFrame", 0, true},
        {"cc.Director:resetMatrixStack", "lua_cc_base_Director_resetMatrixStack", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:resetMatrixStack", 0, true},
        {"cc.Director:pushMatrix", "lua_cc_base_Director_pushMatrix", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:pushMatrix", 1, true},
        {"cc.Director:setDefaultValues", "lua_cc_base_Director_setDefaultValues", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setDefaultValues", 0, true},
        {"cc.Director:init", "lua_cc_base_Director_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:init", 0, true},
        {"cc.Director:setScheduler", "lua_cc_base_Director_setScheduler", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setScheduler", 1, true},
        {"cc.Director:isValid", "lua_cc_base_Director_isValid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isValid", 0, true},
        {"cc.Director:getOpenGLView", "lua_cc_base_Director_getOpenGLView", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getOpenGLView", 0, true},
        {"cc.Director:getRunningScene", "lua_cc_base_Director_getRunningScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getRunningScene", 0, true},
        {"cc.Director:setViewport", "lua_cc_base_Director_setViewport", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setViewport", 0, true},
        {"cc.Director:stopAnimation", "lua_cc_base_Director_stopAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:stopAnimation", 0, true},
        {"cc.Director:popToSceneStackLevel", "lua_cc_base_Director_popToSceneStackLevel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:popToSceneStackLevel", 1, true},
        {"cc.Director:resume", "lua_cc_base_Director_resume", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:resume", 0, true},
        {"cc.Director:isNextDeltaTimeZero", "lua_cc_base_Director_isNextDeltaTimeZero", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isNextDeltaTimeZero", 0, true},
        {"cc.Director:isChildrenIndexerEnabled", "lua_cc_base_Director_isChildrenIndexerEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isChildrenIndexerEnabled", 0, true},
        {"cc.Director:endToLua", "lua_cc_base_Director_end", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:end", 0, true},
        {"cc.Director:setOpenGLView", "lua_cc_base_Director_setOpenGLView", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setOpenGLView", 1, true},
        {"cc.Director:getTotalFrames", "lua_cc_base_Director_getTotalFrames", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getTotalFrames", 0, true},
        {"cc.Director:runWithScene", "lua_cc_base_Director_runWithScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:runWithScene", 1, true},
        {"cc.Director:setNotificationNode", "lua_cc_base_Director_setNotificationNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setNotificationNode", 1, true},
        {"cc.Director:isStatsDisplay", "lua_cc_base_Director_isStatsDisplay", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isStatsDisplay", 0, true},
        {"cc.Director:setChildrenIndexerEnabled", "lua_cc_base_Director_setChildrenIndexerEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setChildrenIndexerEnabled", 1, true},
        {"cc.Director:drawScene", "lua_cc_base_Director_drawScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:drawScene", 0, true},
        {"cc.Director:restart", "lua_cc_base_Director_restart", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:restart", 0, true},
        {"cc.Director:popScene", "lua_cc_base_Director_popScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:popScene", 0, true},
        {"cc.Director:loadIdentityMatrix", "lua_cc_base_Director_loadIdentityMatrix", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:loadIdentityMatrix", 1, true},
        {"cc.Director:startAnimation", "lua_cc_base_Director_startAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:startAnimation", 0, true},
        {"cc.Director:setProjection", "lua_cc_base_Director_setProjection", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setProjection", 1, true},
        {"cc.Director:getConsole", "lua_cc_base_Director_getConsole", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getConsole", 0, true},
        {"cc.Director:getZEye", "lua_cc_base_Director_getZEye", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getZEye", 0, true},
        {"cc.Director:setNextDeltaTimeZero", "lua_cc_base_Director_setNextDeltaTimeZero", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setNextDeltaTimeZero", 1, true},
        {"cc.Director:popMatrix", "lua_cc_base_Director_popMatrix", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:popMatrix", 1, true},
        {"cc.Director:getScheduler", "lua_cc_base_Director_getScheduler", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getScheduler", 0, true},
        {"cc.Director:pushScene", "lua_cc_base_Director_pushScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:pushScene", 1, true},
        {"cc.Director:setStatsAnchor", "lua_cc_base_Director_setStatsAnchor", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setStatsAnchor", 0, true},
        {"cc.Director:getAnimationInterval", "lua_cc_base_Director_getAnimationInterval", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getAnimationInterval", 0, true},
        {"cc.Director:isPaused", "lua_cc_base_Director_isPaused", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:isPaused", 0, true},
        {"cc.Director:purgeCachedData", "lua_cc_base_Director_purgeCachedData", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:purgeCachedData", 0, true},
        {"cc.Director:getEventDispatcher", "lua_cc_base_Director_getEventDispatcher", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getEventDispatcher", 0, true},
        {"cc.Director:replaceScene", "lua_cc_base_Director_replaceScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:replaceScene", 1, true},
        {"cc.Director:setAnimationInterval", "lua_cc_base_Director_setAnimationInterval", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setAnimationInterval", 1, true},
        {"cc.Director:getActionManager", "lua_cc_base_Director_getActionManager", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getActionManager", 0, true},
        {"cc.Timer:setupTimerWithInterval", "lua_cc_base_Timer_setupTimerWithInterval", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:setupTimerWithInterval", 3, true},
        {"cc.Timer:update", "lua_cc_base_Timer_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:update", 1, true},
        {"cc.Timer:isAborted", "lua_cc_base_Timer_isAborted", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:isAborted", 0, true},
        {"cc.Timer:isExhausted", "lua_cc_base_Timer_isExhausted", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:isExhausted", 0, true},
        {"cc.Timer:trigger", "lua_cc_base_Timer_trigger", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:trigger", 1, true},
        {"cc.Timer:cancel", "lua_cc_base_Timer_cancel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:cancel", 0, true},
        {"cc.Timer:setAborted", "lua_cc_base_Timer_setAborted", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Timer:setAborted", 0, true},
        {"cc.Scheduler:setTimeScale", "lua_cc_base_Scheduler_setTimeScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scheduler:setTimeScale", 1, true},
        {"cc.Scheduler:removeAllPendingActions", "lua_cc_base_Scheduler_removeAllPendingActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scheduler:removeAllPendingActions", 0, true},
        {"cc.Scheduler:getTimeScale", "lua_cc_base_Scheduler_getTimeScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scheduler:getTimeScale", 0, true},
        {"cc.AsyncTaskPool:stopTasks", "lua_cc_base_AsyncTaskPool_stopTasks", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AsyncTaskPool:stopTasks", 1, true},
        {"cc.Action:startWithTarget", "lua_cc_base_Action_startWithTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:startWithTarget", 1, true},
        {"cc.Action:setOriginalTarget", "lua_cc_base_Action_setOriginalTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:setOriginalTarget", 1, true},
        {"cc.Action:clone", "lua_cc_base_Action_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:clone", 0, true},
        {"cc.Action:getOriginalTarget", "lua_cc_base_Action_getOriginalTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:getOriginalTarget", 0, true},
        {"cc.Action:stop", "lua_cc_base_Action_stop", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:stop", 0, true},
        {"cc.Action:update", "lua_cc_base_Action_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:update", 1, true},
        {"cc.Action:getTarget", "lua_cc_base_Action_getTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:getTarget", 0, true},
        {"cc.Action:getFlags", "lua_cc_base_Action_getFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:getFlags", 0, true},
        {"cc.Action:step", "lua_cc_base_Action_step", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:step", 1, true},
        {"cc.Action:setTag", "lua_cc_base_Action_setTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:setTag", 1, true},
        {"cc.Action:setFlags", "lua_cc_base_Action_setFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:setFlags", 1, true},
        {"cc.Action:getTag", "lua_cc_base_Action_getTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:getTag", 0, true},
        {"cc.Action:setTarget", "lua_cc_base_Action_setTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:setTarget", 1, true},
        {"cc.Action:isDone", "lua_cc_base_Action_isDone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:isDone", 0, true},
        {"cc.Action:reverse", "lua_cc_base_Action_reverse", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Action:reverse", 0, true},
        {"cc.FiniteTimeAction:setDuration", "lua_cc_base_FiniteTimeAction_setDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FiniteTimeAction:setDuration", 1, true},
        {"cc.FiniteTimeAction:getDuration", "lua_cc_base_FiniteTimeAction_getDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FiniteTimeAction:getDuration", 0, true},
        {"cc.Speed:setInnerAction", "lua_cc_base_Speed_setInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:setInnerAction", 1, true},
        {"cc.Speed:getSpeed", "lua_cc_base_Speed_getSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:getSpeed", 0, true},
        {"cc.Speed:setSpeed", "lua_cc_base_Speed_setSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:setSpeed", 1, true},
        {"cc.Speed:initWithAction", "lua_cc_base_Speed_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:initWithAction", 2, true},
        {"cc.Speed:getInnerAction", "lua_cc_base_Speed_getInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:getInnerAction", 0, true},
        {"cc.Speed:create", "lua_cc_base_Speed_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Speed:create", 2, true},
        {"cc.Follow:setBoundarySet", "lua_cc_base_Follow_setBoundarySet", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Follow:setBoundarySet", 1, true},
        {"cc.Follow:isBoundarySet", "lua_cc_base_Follow_isBoundarySet", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Follow:isBoundarySet", 0, true},
        {"cc.Image:hasPremultipliedAlpha", "lua_cc_base_Image_hasPremultipliedAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:hasPremultipliedAlpha", 0, true},
        {"cc.Image:reversePremultipliedAlpha", "lua_cc_base_Image_reversePremultipliedAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:reversePremultipliedAlpha", 0, true},
        {"cc.Image:isCompressed", "lua_cc_base_Image_isCompressed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:isCompressed", 0, true},
        {"cc.Image:hasAlpha", "lua_cc_base_Image_hasAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:hasAlpha", 0, true},
        {"cc.Image:getPixelFormat", "lua_cc_base_Image_getPixelFormat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getPixelFormat", 0, true},
        {"cc.Image:getHeight", "lua_cc_base_Image_getHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getHeight", 0, true},
        {"cc.Image:premultiplyAlpha", "lua_cc_base_Image_premultiplyAlpha", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:premultiplyAlpha", 0, true},
        {"cc.Image:initWithImageFile", "lua_cc_base_Image_initWithImageFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:initWithImageFile", 1, true},
        {"cc.Image:getWidth", "lua_cc_base_Image_getWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getWidth", 0, true},
        {"cc.Image:getBitPerPixel", "lua_cc_base_Image_getBitPerPixel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getBitPerPixel", 0, true},
        {"cc.Image:getFileType", "lua_cc_base_Image_getFileType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getFileType", 0, true},
        {"cc.Image:getFilePath", "lua_cc_base_Image_getFilePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getFilePath", 0, true},
        {"cc.Image:getNumberOfMipmaps", "lua_cc_base_Image_getNumberOfMipmaps", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:getNumberOfMipmaps", 0, true},
        {"cc.Image:saveToFile", "lua_cc_base_Image_saveToFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:saveToFile", 1, true},
        {"cc.Image:isCompressedImageHavePMA", "lua_cc_base_Image_isCompressedImageHavePMA", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Image:isCompressedImageHavePMA", 1, true},
        {"cc.Image:setPNGPremultipliedAlphaEnabled", "lua_cc_base_Image_setPNGPremultipliedAlphaEnabled", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Image:setPNGPremultipliedAlphaEnabled", 1, true},
        {"cc.Image:setCompressedImagesHavePMA", "lua_cc_base_Image_setCompressedImagesHavePMA", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Image:setCompressedImagesHavePMA", 2, true},
        {"cc.PolygonInfo:getFilename", "lua_cc_base_PolygonInfo_getFilename", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:getFilename", 0, true},
        {"cc.PolygonInfo:getArea", "lua_cc_base_PolygonInfo_getArea", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:getArea", 0, true},
        {"cc.PolygonInfo:setFilename", "lua_cc_base_PolygonInfo_setFilename", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:setFilename", 1, true},
        {"cc.PolygonInfo:getVertCount", "lua_cc_base_PolygonInfo_getVertCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:getVertCount", 0, true},
        {"cc.PolygonInfo:getTrianglesCount", "lua_cc_base_PolygonInfo_getTrianglesCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:getTrianglesCount", 0, true},
        {"cc.SpriteFrame:setTexture", "lua_cc_base_SpriteFrame_setTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setTexture", 1, true},
        {"cc.SpriteFrame:getTexture", "lua_cc_base_SpriteFrame_getTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getTexture", 0, true},
        {"cc.SpriteFrame:clone", "lua_cc_base_SpriteFrame_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:clone", 0, true},
        {"cc.SpriteFrame:isRotated", "lua_cc_base_SpriteFrame_isRotated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:isRotated", 0, true},
        {"cc.SpriteFrame:hasCenterRect", "lua_cc_base_SpriteFrame_hasCenterRect", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:hasCenterRect", 0, true},
        {"cc.SpriteFrame:setRotated", "lua_cc_base_SpriteFrame_setRotated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setRotated", 1, true},
        {"cc.SpriteFrame:hasAnchorPoint", "lua_cc_base_SpriteFrame_hasAnchorPoint", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:hasAnchorPoint", 0, true},
        {"cc.AnimationFrame:setSpriteFrame", "lua_cc_base_AnimationFrame_setSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:setSpriteFrame", 1, true},
        {"cc.AnimationFrame:setDelayUnits", "lua_cc_base_AnimationFrame_setDelayUnits", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:setDelayUnits", 1, true},
        {"cc.AnimationFrame:clone", "lua_cc_base_AnimationFrame_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:clone", 0, true},
        {"cc.AnimationFrame:getSpriteFrame", "lua_cc_base_AnimationFrame_getSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:getSpriteFrame", 0, true},
        {"cc.AnimationFrame:getDelayUnits", "lua_cc_base_AnimationFrame_getDelayUnits", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:getDelayUnits", 0, true},
        {"cc.Animation:getLoops", "lua_cc_base_Animation_getLoops", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getLoops", 0, true},
        {"cc.Animation:addSpriteFrame", "lua_cc_base_Animation_addSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:addSpriteFrame", 1, true},
        {"cc.Animation:setRestoreOriginalFrame", "lua_cc_base_Animation_setRestoreOriginalFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:setRestoreOriginalFrame", 1, true},
        {"cc.Animation:clone", "lua_cc_base_Animation_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:clone", 0, true},
        {"cc.Animation:getDuration", "lua_cc_base_Animation_getDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getDuration", 0, true},
        {"cc.Animation:init", "lua_cc_base_Animation_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:init", 0, true},
        {"cc.Animation:setLoops", "lua_cc_base_Animation_setLoops", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:setLoops", 1, true},
        {"cc.Animation:setDelayPerUnit", "lua_cc_base_Animation_setDelayPerUnit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:setDelayPerUnit", 1, true},
        {"cc.Animation:addSpriteFrameWithFile", "lua_cc_base_Animation_addSpriteFrameWithFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:addSpriteFrameWithFile", 1, true},
        {"cc.Animation:getTotalDelayUnits", "lua_cc_base_Animation_getTotalDelayUnits", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getTotalDelayUnits", 0, true},
        {"cc.Animation:getDelayPerUnit", "lua_cc_base_Animation_getDelayPerUnit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getDelayPerUnit", 0, true},
        {"cc.Animation:getRestoreOriginalFrame", "lua_cc_base_Animation_getRestoreOriginalFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getRestoreOriginalFrame", 0, true},
        {"cc.ActionInterval:getAmplitudeRate", "lua_cc_base_ActionInterval_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionInterval:getAmplitudeRate", 0, true},
        {"cc.ActionInterval:initWithDuration", "lua_cc_base_ActionInterval_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionInterval:initWithDuration", 1, true},
        {"cc.ActionInterval:setAmplitudeRate", "lua_cc_base_ActionInterval_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionInterval:setAmplitudeRate", 1, true},
        {"cc.ActionInterval:getElapsed", "lua_cc_base_ActionInterval_getElapsed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionInterval:getElapsed", 0, true},
        {"cc.Sequence:initWithTwoActions", "lua_cc_base_Sequence_initWithTwoActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sequence:initWithTwoActions", 2, true},
        {"cc.Repeat:setInnerAction", "lua_cc_base_Repeat_setInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Repeat:setInnerAction", 1, true},
        {"cc.Repeat:initWithAction", "lua_cc_base_Repeat_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Repeat:initWithAction", 2, true},
        {"cc.Repeat:getInnerAction", "lua_cc_base_Repeat_getInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Repeat:getInnerAction", 0, true},
        {"cc.Repeat:create", "lua_cc_base_Repeat_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Repeat:create", 2, true},
        {"cc.RepeatForever:setInnerAction", "lua_cc_base_RepeatForever_setInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RepeatForever:setInnerAction", 1, true},
        {"cc.RepeatForever:initWithAction", "lua_cc_base_RepeatForever_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RepeatForever:initWithAction", 1, true},
        {"cc.RepeatForever:getInnerAction", "lua_cc_base_RepeatForever_getInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RepeatForever:getInnerAction", 0, true},
        {"cc.RepeatForever:create", "lua_cc_base_RepeatForever_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.RepeatForever:create", 1, true},
        {"cc.Spawn:initWithTwoActions", "lua_cc_base_Spawn_initWithTwoActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Spawn:initWithTwoActions", 2, true},
        {"cc.SkewTo:initWithDuration", "lua_cc_base_SkewTo_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SkewTo:initWithDuration", 3, true},
        {"cc.SkewTo:create", "lua_cc_base_SkewTo_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SkewTo:create", 3, true},
        {"cc.SkewBy:initWithDuration", "lua_cc_base_SkewBy_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SkewBy:initWithDuration", 3, true},
        {"cc.SkewBy:create", "lua_cc_base_SkewBy_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SkewBy:create", 3, true},
        {"cc.ScaleTo:initWithDuration", "lua_cc_base_ScaleTo_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScaleTo:initWithDuration", 4, false},
        {"cc.ScaleTo:create", "lua_cc_base_ScaleTo_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.ScaleTo:create", 4, false},
        {"cc.ScaleBy:create", "lua_cc_base_ScaleBy_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.ScaleBy:create", 4, false},
        {"cc.Blink:initWithDuration", "lua_cc_base_Blink_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Blink:initWithDuration", 2, true},
        {"cc.Blink:create", "lua_cc_base_Blink_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Blink:create", 2, true},
        {"cc.FadeIn:setReverseAction", "lua_cc_base_FadeIn_setReverseAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeIn:setReverseAction", 1, true},
        {"cc.FadeIn:create", "lua_cc_base_FadeIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeIn:create", 1, true},
        {"cc.FadeOut:setReverseAction", "lua_cc_base_FadeOut_setReverseAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOut:setReverseAction", 1, true},
        {"cc.FadeOut:create", "lua_cc_base_FadeOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeOut:create", 1, true},
        {"cc.DelayTime:create", "lua_cc_base_DelayTime_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.DelayTime:create", 1, true},
        {"cc.Animate:initWithAnimation", "lua_cc_base_Animate_initWithAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate:initWithAnimation", 1, true},
        {"cc.Animate:getCurrentFrameIndex", "lua_cc_base_Animate_getCurrentFrameIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate:getCurrentFrameIndex", 0, true},
        {"cc.Animate:setAnimation", "lua_cc_base_Animate_setAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate:setAnimation", 1, true},
        {"cc.Animate:create", "lua_cc_base_Animate_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animate:create", 1, true},
        {"cc.TargetedAction:initWithTarget", "lua_cc_base_TargetedAction_initWithTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TargetedAction:initWithTarget", 2, true},
        {"cc.TargetedAction:setForcedTarget", "lua_cc_base_TargetedAction_setForcedTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TargetedAction:setForcedTarget", 1, true},
        {"cc.TargetedAction:create", "lua_cc_base_TargetedAction_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TargetedAction:create", 2, true},
        {"cc.Properties:setVariable", "lua_cc_base_Properties_setVariable", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:setVariable", 2, true},
        {"cc.Properties:getFloat", "lua_cc_base_Properties_getFloat", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getFloat", 0, true},
        {"cc.Properties:getType", "lua_cc_base_Properties_getType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getType", 0, true},
        {"cc.Properties:getString", "lua_cc_base_Properties_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getString", 0, true},
        {"cc.Properties:exists", "lua_cc_base_Properties_exists", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:exists", 1, true},
        {"cc.Properties:setString", "lua_cc_base_Properties_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:setString", 2, true},
        {"cc.Properties:getNextProperty", "lua_cc_base_Properties_getNextProperty", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getNextProperty", 0, true},
        {"cc.Properties:getId", "lua_cc_base_Properties_getId", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getId", 0, true},
        {"cc.Properties:getInt", "lua_cc_base_Properties_getInt", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getInt", 0, true},
        {"cc.Properties:rewind", "lua_cc_base_Properties_rewind", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:rewind", 0, true},
        {"cc.Properties:getBool", "lua_cc_base_Properties_getBool", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getBool", 0, true},
        {"cc.Properties:getVariable", "lua_cc_base_Properties_getVariable", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getVariable", 1, true},
        {"cc.UserDefault:setIntegerForKey", "lua_cc_base_UserDefault_setIntegerForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setIntegerForKey", 2, true},
        {"cc.UserDefault:getFloatForKey", "lua_cc_base_UserDefault_getFloatForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:getFloatForKey", 1, false},
        {"cc.UserDefault:getBoolForKey", "lua_cc_base_UserDefault_getBoolForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:getBoolForKey", 1, false},
        {"cc.UserDefault:flush", "lua_cc_base_UserDefault_flush", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:flush", 0, true},
        {"cc.UserDefault:setDoubleForKey", "lua_cc_base_UserDefault_setDoubleForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setDoubleForKey", 2, true},
        {"cc.UserDefault:setFloatForKey", "lua_cc_base_UserDefault_setFloatForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setFloatForKey", 2, true},
        {"cc.UserDefault:getStringForKey", "lua_cc_base_UserDefault_getStringForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:getStringForKey", 1, false},
        {"cc.UserDefault:setStringForKey", "lua_cc_base_UserDefault_setStringForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setStringForKey", 2, true},
        {"cc.UserDefault:setEncryptEnabled", "lua_cc_base_UserDefault_setEncryptEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setEncryptEnabled", 3, true},
        {"cc.UserDefault:deleteValueForKey", "lua_cc_base_UserDefault_deleteValueForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:deleteValueForKey", 1, true},
        {"cc.UserDefault:getIntegerForKey", "lua_cc_base_UserDefault_getIntegerForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:getIntegerForKey", 1, false},
        {"cc.UserDefault:getDoubleForKey", "lua_cc_base_UserDefault_getDoubleForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:getDoubleForKey", 1, false},
        {"cc.UserDefault:setBoolForKey", "lua_cc_base_UserDefault_setBoolForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setBoolForKey", 2, true},
        {"cc.FileUtils:getNativeWritableAbsolutePath", "lua_cc_base_FileUtils_getNativeWritableAbsolutePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getNativeWritableAbsolutePath", 0, true},
        {"cc.FileUtils:isAbsolutePath", "lua_cc_base_FileUtils_isAbsolutePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:isAbsolutePath", 1, true},
        {"cc.FileUtils:getDefaultResourceRootPath", "lua_cc_base_FileUtils_getDefaultResourceRootPath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getDefaultResourceRootPath", 0, true},
        {"cc.FileUtils:isPopupNotify", "lua_cc_base_FileUtils_isPopupNotify", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:isPopupNotify", 0, true},
        {"cc.FileUtils:isFileExistInternal", "lua_cc_base_FileUtils_isFileExistInternal", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:isFileExistInternal", 1, true},
        {"cc.FileUtils:fullPathForFilename", "lua_cc_base_FileUtils_fullPathForFilename", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:fullPathForFilename", 1, true},
        {"cc.FileUtils:addSearchPath", "lua_cc_base_FileUtils_addSearchPath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:addSearchPath", 1, true},
        {"cc.FileUtils:purgeCachedEntries", "lua_cc_base_FileUtils_purgeCachedEntries", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:purgeCachedEntries", 0, true},
        {"cc.FileUtils:fullPathFromRelativeFile", "lua_cc_base_FileUtils_fullPathFromRelativeFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:fullPathFromRelativeFile", 2, true},
        {"cc.FileUtils:isDirectoryExistInternal", "lua_cc_base_FileUtils_isDirectoryExistInternal", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:isDirectoryExistInternal", 1, true},
        {"cc.FileUtils:getFileExtension", "lua_cc_base_FileUtils_getFileExtension", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getFileExtension", 1, true},
        {"cc.FileUtils:setWritablePath", "lua_cc_base_FileUtils_setWritablePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:setWritablePath", 1, true},
        {"cc.FileUtils:setPopupNotify", "lua_cc_base_FileUtils_setPopupNotify", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:setPopupNotify", 1, true},
        {"cc.FileUtils:setDefaultResourceRootPath", "lua_cc_base_FileUtils_setDefaultResourceRootPath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:setDefaultResourceRootPath", 1, true},
        {"cc.FileUtils:getWritablePath", "lua_cc_base_FileUtils_getWritablePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getWritablePath", 0, true},
        {"cc.FileUtils:isAbsolutePathInternal", "lua_cc_base_FileUtils_isAbsolutePathInternal", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FileUtils:isAbsolutePathInternal", 1, true},
        {"cc.FileUtils:getFileShortName", "lua_cc_base_FileUtils_getFileShortName", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FileUtils:getFileShortName", 1, true},
        {"cc.EventCustom:getEventName", "lua_cc_base_EventCustom_getEventName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventCustom:getEventName", 0, true},
        {"cc.EventDispatcher:pauseEventListenersForTarget", "lua_cc_base_EventDispatcher_pauseEventListenersForTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:pauseEventListenersForTarget", 1, true},
        {"cc.EventDispatcher:addEventListenerWithSceneGraphPriority", "lua_cc_base_EventDispatcher_addEventListenerWithSceneGraphPriority", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:addEventListenerWithSceneGraphPriority", 2, true},
        {"cc.EventDispatcher:setEnabled", "lua_cc_base_EventDispatcher_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:setEnabled", 1, true},
        {"cc.EventDispatcher:addEventListenerWithFixedPriority", "lua_cc_base_EventDispatcher_addEventListenerWithFixedPriority", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:addEventListenerWithFixedPriority", 2, true},
        {"cc.EventDispatcher:removeEventListener", "lua_cc_base_EventDispatcher_removeEventListener", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:removeEventListener", 1, true},
        {"cc.EventDispatcher:resumeEventListenersForTarget", "lua_cc_base_EventDispatcher_resumeEventListenersForTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:resumeEventListenersForTarget", 1, true},
        {"cc.EventDispatcher:removeEventListenersForTarget", "lua_cc_base_EventDispatcher_removeEventListenersForTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:removeEventListenersForTarget", 1, true},
        {"cc.EventDispatcher:setPriority", "lua_cc_base_EventDispatcher_setPriority", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:setPriority", 2, true},
        {"cc.EventDispatcher:dispatchEvent", "lua_cc_base_EventDispatcher_dispatchEvent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:dispatchEvent", 1, true},
        {"cc.EventDispatcher:hasEventListener", "lua_cc_base_EventDispatcher_hasEventListener", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:hasEventListener", 1, true},
        {"cc.EventDispatcher:removeAllEventListeners", "lua_cc_base_EventDispatcher_removeAllEventListeners", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:removeAllEventListeners", 0, true},
        {"cc.EventDispatcher:removeCustomEventListeners", "lua_cc_base_EventDispatcher_removeCustomEventListeners", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:removeCustomEventListeners", 1, true},
        {"cc.EventDispatcher:isEnabled", "lua_cc_base_EventDispatcher_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:isEnabled", 0, true},
        {"cc.EventDispatcher:removeEventListenersForType", "lua_cc_base_EventDispatcher_removeEventListenersForType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:removeEventListenersForType", 1, true},
        {"cc.EventListenerFocus:init", "lua_cc_base_EventListenerFocus_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerFocus:init", 0, true},
        {"cc.EventListenerKeyboard:init", "lua_cc_base_EventListenerKeyboard_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerKeyboard:init", 0, true},
        {"cc.EventMouse:getMouseButton", "lua_cc_base_EventMouse_getMouseButton", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getMouseButton", 0, true},
        {"cc.EventMouse:setScrollData", "lua_cc_base_EventMouse_setScrollData", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:setScrollData", 2, true},
        {"cc.EventMouse:setMouseButton", "lua_cc_base_EventMouse_setMouseButton", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:setMouseButton", 1, true},
        {"cc.EventMouse:getScrollY", "lua_cc_base_EventMouse_getScrollY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getScrollY", 0, true},
        {"cc.EventMouse:getScrollX", "lua_cc_base_EventMouse_getScrollX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getScrollX", 0, true},
        {"cc.EventMouse:getCursorX", "lua_cc_base_EventMouse_getCursorX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getCursorX", 0, true},
        {"cc.EventMouse:getCursorY", "lua_cc_base_EventMouse_getCursorY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getCursorY", 0, true},
        {"cc.EventMouse:setCursorPosition", "lua_cc_base_EventMouse_setCursorPosition", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:setCursorPosition", 2, true},
        {"cc.EventListenerMouse:init", "lua_cc_base_EventListenerMouse_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerMouse:init", 0, true},
        {"cc.EventListenerTouchOneByOne:isSwallowTouches", "lua_cc_base_EventListenerTouchOneByOne_isSwallowTouches", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchOneByOne:isSwallowTouches", 0, true},
        {"cc.EventListenerTouchOneByOne:setSwallowTouches", "lua_cc_base_EventListenerTouchOneByOne_setSwallowTouches", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchOneByOne:setSwallowTouches", 1, true},
        {"cc.EventListenerTouchOneByOne:init", "lua_cc_base_EventListenerTouchOneByOne_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchOneByOne:init", 0, true},
        {"cc.EventListenerTouchAllAtOnce:init", "lua_cc_base_EventListenerTouchAllAtOnce_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchAllAtOnce:init", 0, true},
        {"cc.OrbitCamera:initWithDuration", "lua_cc_base_OrbitCamera_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OrbitCamera:initWithDuration", 7, true},
        {"cc.OrbitCamera:create", "lua_cc_base_OrbitCamera_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.OrbitCamera:create", 7, true},
        {"cc.ActionEase:initWithAction", "lua_cc_base_ActionEase_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionEase:initWithAction", 1, true},
        {"cc.ActionEase:getInnerAction", "lua_cc_base_ActionEase_getInnerAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionEase:getInnerAction", 0, true},
        {"cc.EaseRateAction:setRate", "lua_cc_base_EaseRateAction_setRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseRateAction:setRate", 1, true},
        {"cc.EaseRateAction:initWithAction", "lua_cc_base_EaseRateAction_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseRateAction:initWithAction", 2, true},
        {"cc.EaseRateAction:getRate", "lua_cc_base_EaseRateAction_getRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseRateAction:getRate", 0, true},
        {"cc.EaseRateAction:create", "lua_cc_base_EaseRateAction_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseRateAction:create", 2, true},
        {"cc.EaseExponentialIn:create", "lua_cc_base_EaseExponentialIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseExponentialIn:create", 1, true},
        {"cc.EaseExponentialOut:create", "lua_cc_base_EaseExponentialOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseExponentialOut:create", 1, true},
        {"cc.EaseExponentialInOut:create", "lua_cc_base_EaseExponentialInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseExponentialInOut:create", 1, true},
        {"cc.EaseSineIn:create", "lua_cc_base_EaseSineIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseSineIn:create", 1, true},
        {"cc.EaseSineOut:create", "lua_cc_base_EaseSineOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseSineOut:create", 1, true},
        {"cc.EaseSineInOut:create", "lua_cc_base_EaseSineInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseSineInOut:create", 1, true},
        {"cc.EaseBounceIn:create", "lua_cc_base_EaseBounceIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBounceIn:create", 1, true},
        {"cc.EaseBounceOut:create", "lua_cc_base_EaseBounceOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBounceOut:create", 1, true},
        {"cc.EaseBounceInOut:create", "lua_cc_base_EaseBounceInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBounceInOut:create", 1, true},
        {"cc.EaseBackIn:create", "lua_cc_base_EaseBackIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBackIn:create", 1, true},
        {"cc.EaseBackOut:create", "lua_cc_base_EaseBackOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBackOut:create", 1, true},
        {"cc.EaseBackInOut:create", "lua_cc_base_EaseBackInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBackInOut:create", 1, true},
        {"cc.EaseQuadraticActionIn:create", "lua_cc_base_EaseQuadraticActionIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuadraticActionIn:create", 1, true},
        {"cc.EaseQuadraticActionOut:create", "lua_cc_base_EaseQuadraticActionOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuadraticActionOut:create", 1, true},
        {"cc.EaseQuadraticActionInOut:create", "lua_cc_base_EaseQuadraticActionInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuadraticActionInOut:create", 1, true},
        {"cc.EaseQuarticActionIn:create", "lua_cc_base_EaseQuarticActionIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuarticActionIn:create", 1, true},
        {"cc.EaseQuarticActionOut:create", "lua_cc_base_EaseQuarticActionOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuarticActionOut:create", 1, true},
        {"cc.EaseQuarticActionInOut:create", "lua_cc_base_EaseQuarticActionInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuarticActionInOut:create", 1, true},
        {"cc.EaseQuinticActionIn:create", "lua_cc_base_EaseQuinticActionIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuinticActionIn:create", 1, true},
        {"cc.EaseQuinticActionOut:create", "lua_cc_base_EaseQuinticActionOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuinticActionOut:create", 1, true},
        {"cc.EaseQuinticActionInOut:create", "lua_cc_base_EaseQuinticActionInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseQuinticActionInOut:create", 1, true},
        {"cc.EaseCircleActionIn:create", "lua_cc_base_EaseCircleActionIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCircleActionIn:create", 1, true},
        {"cc.EaseCircleActionOut:create", "lua_cc_base_EaseCircleActionOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCircleActionOut:create", 1, true},
        {"cc.EaseCircleActionInOut:create", "lua_cc_base_EaseCircleActionInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCircleActionInOut:create", 1, true},
        {"cc.EaseCubicActionIn:create", "lua_cc_base_EaseCubicActionIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCubicActionIn:create", 1, true},
        {"cc.EaseCubicActionOut:create", "lua_cc_base_EaseCubicActionOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCubicActionOut:create", 1, true},
        {"cc.EaseCubicActionInOut:create", "lua_cc_base_EaseCubicActionInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseCubicActionInOut:create", 1, true},
        {"cc.EaseIn:create", "lua_cc_base_EaseIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseIn:create", 2, true},
        {"cc.EaseOut:create", "lua_cc_base_EaseOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseOut:create", 2, true},
        {"cc.EaseInOut:create", "lua_cc_base_EaseInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseInOut:create", 2, true},
        {"cc.EaseElastic:setPeriod", "lua_cc_base_EaseElastic_setPeriod", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElastic:setPeriod", 1, true},
        {"cc.EaseElastic:initWithAction", "lua_cc_base_EaseElastic_initWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElastic:initWithAction", 1, true},
        {"cc.EaseElastic:getPeriod", "lua_cc_base_EaseElastic_getPeriod", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElastic:getPeriod", 0, true},
        {"cc.EaseElasticIn:create", "lua_cc_base_EaseElasticIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseElasticIn:create", 1, true},
        {"cc.EaseElasticOut:create", "lua_cc_base_EaseElasticOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseElasticOut:create", 1, true},
        {"cc.EaseElasticInOut:create", "lua_cc_base_EaseElasticInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseElasticInOut:create", 1, true},
        {"cc.EaseBezierAction:setBezierParamer", "lua_cc_base_EaseBezierAction_setBezierParamer", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBezierAction:setBezierParamer", 4, true},
        {"cc.EaseBezierAction:create", "lua_cc_base_EaseBezierAction_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EaseBezierAction:create", 1, true},
        {"cc.Show:create", "lua_cc_base_Show_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Show:create", 0, true},
        {"cc.Hide:create", "lua_cc_base_Hide_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Hide:create", 0, true},
        {"cc.ToggleVisibility:create", "lua_cc_base_ToggleVisibility_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ToggleVisibility:create", 0, true},
        {"cc.RemoveSelf:init", "lua_cc_base_RemoveSelf_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RemoveSelf:init", 1, true},
        {"cc.RemoveSelf:create", "lua_cc_base_RemoveSelf_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.RemoveSelf:create", 0, true},
        {"cc.FlipX:initWithFlipX", "lua_cc_base_FlipX_initWithFlipX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipX:initWithFlipX", 1, true},
        {"cc.FlipX:create", "lua_cc_base_FlipX_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FlipX:create", 1, true},
        {"cc.FlipY:initWithFlipY", "lua_cc_base_FlipY_initWithFlipY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipY:initWithFlipY", 1, true},
        {"cc.FlipY:create", "lua_cc_base_FlipY_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FlipY:create", 1, true},
        {"cc.CallFunc:execute", "lua_cc_base_CallFunc_execute", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CallFunc:execute", 0, true},
        {"cc.GridAction:getGrid", "lua_cc_base_GridAction_getGrid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridAction:getGrid", 0, true},
        {"cc.StopGrid:create", "lua_cc_base_StopGrid_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.StopGrid:create", 0, true},
        {"cc.ReuseGrid:initWithTimes", "lua_cc_base_ReuseGrid_initWithTimes", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ReuseGrid:initWithTimes", 1, true},
        {"cc.ReuseGrid:create", "lua_cc_base_ReuseGrid_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ReuseGrid:create", 1, true},
        {"cc.Waves3D:setAmplitudeRate", "lua_cc_base_Waves3D_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:setAmplitudeRate", 1, true},
        {"cc.Waves3D:getAmplitude", "lua_cc_base_Waves3D_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:getAmplitude", 0, true},
        {"cc.Waves3D:getAmplitudeRate", "lua_cc_base_Waves3D_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:getAmplitudeRate", 0, true},
        {"cc.Waves3D:setAmplitude", "lua_cc_base_Waves3D_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:setAmplitude", 1, true},
        {"cc.FlipX3D:initWithDuration", "lua_cc_base_FlipX3D_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipX3D:initWithDuration", 1, true},
        {"cc.FlipX3D:create", "lua_cc_base_FlipX3D_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FlipX3D:create", 1, true},
        {"cc.FlipY3D:create", "lua_cc_base_FlipY3D_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FlipY3D:create", 1, true},
        {"cc.Lens3D:setConcave", "lua_cc_base_Lens3D_setConcave", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:setConcave", 1, true},
        {"cc.Lens3D:setLensEffect", "lua_cc_base_Lens3D_setLensEffect", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:setLensEffect", 1, true},
        {"cc.Lens3D:getLensEffect", "lua_cc_base_Lens3D_getLensEffect", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:getLensEffect", 0, true},
        {"cc.Ripple3D:setAmplitudeRate", "lua_cc_base_Ripple3D_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:setAmplitudeRate", 1, true},
        {"cc.Ripple3D:getAmplitudeRate", "lua_cc_base_Ripple3D_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:getAmplitudeRate", 0, true},
        {"cc.Ripple3D:setAmplitude", "lua_cc_base_Ripple3D_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:setAmplitude", 1, true},
        {"cc.Ripple3D:getAmplitude", "lua_cc_base_Ripple3D_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:getAmplitude", 0, true},
        {"cc.Liquid:setAmplitudeRate", "lua_cc_base_Liquid_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:setAmplitudeRate", 1, true},
        {"cc.Liquid:getAmplitude", "lua_cc_base_Liquid_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:getAmplitude", 0, true},
        {"cc.Liquid:getAmplitudeRate", "lua_cc_base_Liquid_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:getAmplitudeRate", 0, true},
        {"cc.Liquid:setAmplitude", "lua_cc_base_Liquid_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:setAmplitude", 1, true},
        {"cc.Waves:setAmplitudeRate", "lua_cc_base_Waves_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:setAmplitudeRate", 1, true},
        {"cc.Waves:getAmplitude", "lua_cc_base_Waves_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:getAmplitude", 0, true},
        {"cc.Waves:getAmplitudeRate", "lua_cc_base_Waves_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:getAmplitudeRate", 0, true},
        {"cc.Waves:setAmplitude", "lua_cc_base_Waves_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:setAmplitude", 1, true},
        {"cc.Twirl:setAmplitudeRate", "lua_cc_base_Twirl_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:setAmplitudeRate", 1, true},
        {"cc.Twirl:getAmplitudeRate", "lua_cc_base_Twirl_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:getAmplitudeRate", 0, true},
        {"cc.Twirl:setAmplitude", "lua_cc_base_Twirl_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:setAmplitude", 1, true},
        {"cc.Twirl:getAmplitude", "lua_cc_base_Twirl_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:getAmplitude", 0, true},
        {"cc.ActionManager:getActionByTag", "lua_cc_base_ActionManager_getActionByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:getActionByTag", 2, true},
        {"cc.ActionManager:removeActionByTag", "lua_cc_base_ActionManager_removeActionByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeActionByTag", 2, true},
        {"cc.ActionManager:removeActionsByFlags", "lua_cc_base_ActionManager_removeActionsByFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeActionsByFlags", 2, true},
        {"cc.ActionManager:removeAllActions", "lua_cc_base_ActionManager_removeAllActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeAllActions", 0, true},
        {"cc.ActionManager:addAction", "lua_cc_base_ActionManager_addAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:addAction", 3, true},
        {"cc.ActionManager:resumeTarget", "lua_cc_base_ActionManager_resumeTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:resumeTarget", 1, true},
        {"cc.ActionManager:getNumberOfRunningActions", "lua_cc_base_ActionManager_getNumberOfRunningActions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:getNumberOfRunningActions", 0, true},
        {"cc.ActionManager:pauseTarget", "lua_cc_base_ActionManager_pauseTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:pauseTarget", 1, true},
        {"cc.ActionManager:getNumberOfRunningActionsInTarget", "lua_cc_base_ActionManager_getNumberOfRunningActionsInTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:getNumberOfRunningActionsInTarget", 1, true},
        {"cc.ActionManager:removeAllActionsFromTarget", "lua_cc_base_ActionManager_removeAllActionsFromTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeAllActionsFromTarget", 1, true},
        {"cc.ActionManager:removeAction", "lua_cc_base_ActionManager_removeAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeAction", 1, true},
        {"cc.ActionManager:update", "lua_cc_base_ActionManager_update", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:update", 1, true},
        {"cc.ActionManager:removeAllActionsByTag", "lua_cc_base_ActionManager_removeAllActionsByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:removeAllActionsByTag", 2, true},
        {"cc.ActionManager:getNumberOfRunningActionsInTargetByTag", "lua_cc_base_ActionManager_getNumberOfRunningActionsInTargetByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:getNumberOfRunningActionsInTargetByTag", 2, true},
        {"cc.ProgressTo:initWithDuration", "lua_cc_base_ProgressTo_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTo:initWithDuration", 2, true},
        {"cc.ProgressTo:create", "lua_cc_base_ProgressTo_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ProgressTo:create", 2, true},
        {"cc.ProgressFromTo:initWithDuration", "lua_cc_base_ProgressFromTo_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressFromTo:initWithDuration", 3, true},
        {"cc.ProgressFromTo:create", "lua_cc_base_ProgressFromTo_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ProgressFromTo:create", 3, true},
        {"cc.WavesTiles3D:setAmplitudeRate", "lua_cc_base_WavesTiles3D_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:setAmplitudeRate", 1, true},
        {"cc.WavesTiles3D:getAmplitude", "lua_cc_base_WavesTiles3D_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:getAmplitude", 0, true},
        {"cc.WavesTiles3D:getAmplitudeRate", "lua_cc_base_WavesTiles3D_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:getAmplitudeRate", 0, true},
        {"cc.WavesTiles3D:setAmplitude", "lua_cc_base_WavesTiles3D_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:setAmplitude", 1, true},
        {"cc.JumpTiles3D:setAmplitudeRate", "lua_cc_base_JumpTiles3D_setAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:setAmplitudeRate", 1, true},
        {"cc.JumpTiles3D:getAmplitude", "lua_cc_base_JumpTiles3D_getAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:getAmplitude", 0, true},
        {"cc.JumpTiles3D:getAmplitudeRate", "lua_cc_base_JumpTiles3D_getAmplitudeRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:getAmplitudeRate", 0, true},
        {"cc.JumpTiles3D:setAmplitude", "lua_cc_base_JumpTiles3D_setAmplitude", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:setAmplitude", 1, true},
        {"cc.SplitRows:initWithDuration", "lua_cc_base_SplitRows_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SplitRows:initWithDuration", 2, true},
        {"cc.SplitRows:create", "lua_cc_base_SplitRows_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SplitRows:create", 2, true},
        {"cc.SplitCols:initWithDuration", "lua_cc_base_SplitCols_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SplitCols:initWithDuration", 2, true},
        {"cc.SplitCols:create", "lua_cc_base_SplitCols_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SplitCols:create", 2, true},
        {"cc.ActionTween:initWithDuration", "lua_cc_base_ActionTween_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionTween:initWithDuration", 4, true},
        {"cc.ActionTween:create", "lua_cc_base_ActionTween_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ActionTween:create", 4, true},
        {"cc.AtlasNode:initWithTileFile", "lua_cc_base_AtlasNode_initWithTileFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:initWithTileFile", 4, true},
        {"cc.AtlasNode:updateAtlasValues", "lua_cc_base_AtlasNode_updateAtlasValues", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:updateAtlasValues", 0, true},
        {"cc.AtlasNode:initWithTexture", "lua_cc_base_AtlasNode_initWithTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:initWithTexture", 4, true},
        {"cc.AtlasNode:getQuadsToDraw", "lua_cc_base_AtlasNode_getQuadsToDraw", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:getQuadsToDraw", 0, true},
        {"cc.AtlasNode:create", "lua_cc_base_AtlasNode_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AtlasNode:create", 4, true},
        {"cc.ClippingNode:hasContent", "lua_cc_base_ClippingNode_hasContent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:hasContent", 0, true},
        {"cc.ClippingNode:setInverted", "lua_cc_base_ClippingNode_setInverted", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:setInverted", 1, true},
        {"cc.ClippingNode:setStencil", "lua_cc_base_ClippingNode_setStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:setStencil", 1, true},
        {"cc.ClippingNode:getAlphaThreshold", "lua_cc_base_ClippingNode_getAlphaThreshold", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:getAlphaThreshold", 0, true},
        {"cc.ClippingNode:getStencil", "lua_cc_base_ClippingNode_getStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:getStencil", 0, true},
        {"cc.ClippingNode:setAlphaThreshold", "lua_cc_base_ClippingNode_setAlphaThreshold", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:setAlphaThreshold", 1, true},
        {"cc.ClippingNode:isInverted", "lua_cc_base_ClippingNode_isInverted", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:isInverted", 0, true},
        {"cc.ClippingNode:create", "lua_cc_base_ClippingNode_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.ClippingNode:create", 0, false},
        {"cc.ClippingRectangleNode:isClippingEnabled", "lua_cc_base_ClippingRectangleNode_isClippingEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingRectangleNode:isClippingEnabled", 0, true},
        {"cc.ClippingRectangleNode:setClippingEnabled", "lua_cc_base_ClippingRectangleNode_setClippingEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingRectangleNode:setClippingEnabled", 1, true},
        {"cc.DrawNode:setIsolated", "lua_cc_base_DrawNode_setIsolated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:setIsolated", 1, true},
        {"cc.DrawNode:setLineWidth", "lua_cc_base_DrawNode_setLineWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:setLineWidth", 1, true},
        {"cc.DrawNode:clear", "lua_cc_base_DrawNode_clear", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:clear", 0, true},
        {"cc.DrawNode:getLineWidth", "lua_cc_base_DrawNode_getLineWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:getLineWidth", 0, true},
        {"cc.DrawNode:isIsolated", "lua_cc_base_DrawNode_isIsolated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:isIsolated", 0, true},
        {"cc.DrawNode:create", "lua_cc_base_DrawNode_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.DrawNode:create", 0, true},
        {"cc.Label:isClipMarginEnabled", "lua_cc_base_Label_isClipMarginEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:isClipMarginEnabled", 0, true},
        {"cc.Label:setDimensions", "lua_cc_base_Label_setDimensions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setDimensions", 2, true},
        {"cc.Label:getWidth", "lua_cc_base_Label_getWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getWidth", 0, true},
        {"cc.Label:getHeight", "lua_cc_base_Label_getHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getHeight", 0, true},
        {"cc.Label:disableEffect", "lua_cc_base_Label_disableEffect", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:disableEffect", 0, false},
        {"cc.Label:getLabelType", "lua_cc_base_Label_getLabelType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getLabelType", 0, true},
        {"cc.Label:enableWrap", "lua_cc_base_Label_enableWrap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableWrap", 1, true},
        {"cc.Label:setWidth", "lua_cc_base_Label_setWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setWidth", 1, true},
        {"cc.Label:getAdditionalKerning", "lua_cc_base_Label_getAdditionalKerning", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getAdditionalKerning", 0, true},
        {"cc.Label:getBMFontSize", "lua_cc_base_Label_getBMFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getBMFontSize", 0, true},
        {"cc.Label:getMaxLineWidth", "lua_cc_base_Label_getMaxLineWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getMaxLineWidth", 0, true},
        {"cc.Label:getHorizontalAlignment", "lua_cc_base_Label_getHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getHorizontalAlignment", 0, true},
        {"cc.Label:getLineSpacing", "lua_cc_base_Label_getLineSpacing", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getLineSpacing", 0, true},
        {"cc.Label:setClipMarginEnabled", "lua_cc_base_Label_setClipMarginEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setClipMarginEnabled", 1, true},
        {"cc.Label:setSystemFontName", "lua_cc_base_Label_setSystemFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setSystemFontName", 1, true},
        {"cc.Label:isWrapEnabled", "lua_cc_base_Label_isWrapEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:isWrapEnabled", 0, true},
        {"cc.Label:getOutlineSize", "lua_cc_base_Label_getOutlineSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getOutlineSize", 0, true},
        {"cc.Label:setLineHeight", "lua_cc_base_Label_setLineHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setLineHeight", 1, true},
        {"cc.Label:setSystemFontSize", "lua_cc_base_Label_setSystemFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setSystemFontSize", 1, true},
        {"cc.Label:setOverflow", "lua_cc_base_Label_setOverflow", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setOverflow", 1, true},
        {"cc.Label:enableStrikethrough", "lua_cc_base_Label_enableStrikethrough", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableStrikethrough", 0, true},
        {"cc.Label:updateContent", "lua_cc_base_Label_updateContent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:updateContent", 0, true},
        {"cc.Label:getStringLength", "lua_cc_base_Label_getStringLength", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getStringLength", 0, true},
        {"cc.Label:setLineBreakWithoutSpace", "lua_cc_base_Label_setLineBreakWithoutSpace", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setLineBreakWithoutSpace", 1, true},
        {"cc.Label:getStringNumLines", "lua_cc_base_Label_getStringNumLines", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getStringNumLines", 0, true},
        {"cc.Label:getShadowBlurRadius", "lua_cc_base_Label_getShadowBlurRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getShadowBlurRadius", 0, true},
        {"cc.Label:setMaxLineWidth", "lua_cc_base_Label_setMaxLineWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setMaxLineWidth", 1, true},
        {"cc.Label:getSystemFontName", "lua_cc_base_Label_getSystemFontName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getSystemFontName", 0, true},
        {"cc.Label:setVerticalAlignment", "lua_cc_base_Label_setVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setVerticalAlignment", 1, true},
        {"cc.Label:setLineSpacing", "lua_cc_base_Label_setLineSpacing", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setLineSpacing", 1, true},
        {"cc.Label:getRenderingFontSize", "lua_cc_base_Label_getRenderingFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getRenderingFontSize", 0, true},
        {"cc.Label:getLineHeight", "lua_cc_base_Label_getLineHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getLineHeight", 0, true},
        {"cc.Label:enableItalics", "lua_cc_base_Label_enableItalics", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableItalics", 0, true},
        {"cc.Label:getLetter", "lua_cc_base_Label_getLetter", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getLetter", 1, true},
        {"cc.Label:setHeight", "lua_cc_base_Label_setHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setHeight", 1, true},
        {"cc.Label:isShadowEnabled", "lua_cc_base_Label_isShadowEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:isShadowEnabled", 0, true},
        {"cc.Label:getOverflow", "lua_cc_base_Label_getOverflow", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getOverflow", 0, true},
        {"cc.Label:getVerticalAlignment", "lua_cc_base_Label_getVerticalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getVerticalAlignment", 0, true},
        {"cc.Label:setAdditionalKerning", "lua_cc_base_Label_setAdditionalKerning", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setAdditionalKerning", 1, true},
        {"cc.Label:getSystemFontSize", "lua_cc_base_Label_getSystemFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getSystemFontSize", 0, true},
        {"cc.Label:getTextAlignment", "lua_cc_base_Label_getTextAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getTextAlignment", 0, true},
        {"cc.Label:getBMFontFilePath", "lua_cc_base_Label_getBMFontFilePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getBMFontFilePath", 0, true},
        {"cc.Label:setHorizontalAlignment", "lua_cc_base_Label_setHorizontalAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setHorizontalAlignment", 1, true},
        {"cc.Label:enableBold", "lua_cc_base_Label_enableBold", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableBold", 0, true},
        {"cc.Label:enableUnderline", "lua_cc_base_Label_enableUnderline", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableUnderline", 0, true},
        {"cc.Label:getLabelEffectType", "lua_cc_base_Label_getLabelEffectType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getLabelEffectType", 0, true},
        {"cc.Label:setAlignment", "lua_cc_base_Label_setAlignment", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setAlignment", 1, false},
        {"cc.Label:requestSystemFontRefresh", "lua_cc_base_Label_requestSystemFontRefresh", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:requestSystemFontRefresh", 0, true},
        {"cc.Label:setBMFontSize", "lua_cc_base_Label_setBMFontSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setBMFontSize", 1, true},
        {"cc.Label:create", "lua_cc_base_Label_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Label:create", 0, true},
        {"cc.Sprite:setFlippedY", "lua_cc_base_Sprite_setFlippedY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setFlippedY", 1, true},
        {"cc.Sprite:setFlippedX", "lua_cc_base_Sprite_setFlippedX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setFlippedX", 1, true},
        {"cc.Sprite:getResourceType", "lua_cc_base_Sprite_getResourceType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getResourceType", 0, true},
        {"cc.Sprite:setDisplayFrameWithAnimationName", "lua_cc_base_Sprite_setDisplayFrameWithAnimationName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setDisplayFrameWithAnimationName", 2, true},
        {"cc.Sprite:getBatchNode", "lua_cc_base_Sprite_getBatchNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getBatchNode", 0, true},
        {"cc.Sprite:isStretchEnabled", "lua_cc_base_Sprite_isStretchEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isStretchEnabled", 0, true},
        {"cc.Sprite:initWithSpriteFrameName", "lua_cc_base_Sprite_initWithSpriteFrameName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:initWithSpriteFrameName", 1, true},
        {"cc.Sprite:setStretchEnabled", "lua_cc_base_Sprite_setStretchEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setStretchEnabled", 1, true},
        {"cc.Sprite:isFrameDisplayed", "lua_cc_base_Sprite_isFrameDisplayed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isFrameDisplayed", 1, true},
        {"cc.Sprite:getAtlasIndex", "lua_cc_base_Sprite_getAtlasIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getAtlasIndex", 0, true},
        {"cc.Sprite:setBatchNode", "lua_cc_base_Sprite_setBatchNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setBatchNode", 1, true},
        {"cc.Sprite:getSpriteFrame", "lua_cc_base_Sprite_getSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getSpriteFrame", 0, true},
        {"cc.Sprite:setVertexLayout", "lua_cc_base_Sprite_setVertexLayout", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setVertexLayout", 0, true},
        {"cc.Sprite:getResourceName", "lua_cc_base_Sprite_getResourceName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getResourceName", 0, true},
        {"cc.Sprite:isDirty", "lua_cc_base_Sprite_isDirty", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isDirty", 0, true},
        {"cc.Sprite:setAtlasIndex", "lua_cc_base_Sprite_setAtlasIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setAtlasIndex", 1, true},
        {"cc.Sprite:setDirty", "lua_cc_base_Sprite_setDirty", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setDirty", 1, true},
        {"cc.Sprite:isTextureRectRotated", "lua_cc_base_Sprite_isTextureRectRotated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isTextureRectRotated", 0, true},
        {"cc.Sprite:initWithSpriteFrame", "lua_cc_base_Sprite_initWithSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:initWithSpriteFrame", 1, true},
        {"cc.Sprite:isFlippedX", "lua_cc_base_Sprite_isFlippedX", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isFlippedX", 0, true},
        {"cc.Sprite:isFlippedY", "lua_cc_base_Sprite_isFlippedY", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:isFlippedY", 0, true},
        {"cc.Sprite:createWithSpriteFrameName", "lua_cc_base_Sprite_createWithSpriteFrameName", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Sprite:createWithSpriteFrameName", 1, true},
        {"cc.Sprite:createWithSpriteFrame", "lua_cc_base_Sprite_createWithSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Sprite:createWithSpriteFrame", 1, true},
        {"cc.Layer:create", "lua_cc_base_Layer_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Layer:create", 0, true},
        {"cc.LayerColor:changeWidthAndHeight", "lua_cc_base_LayerColor_changeWidthAndHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerColor:changeWidthAndHeight", 2, true},
        {"cc.LayerColor:changeHeight", "lua_cc_base_LayerColor_changeHeight", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerColor:changeHeight", 1, true},
        {"cc.LayerColor:changeWidth", "lua_cc_base_LayerColor_changeWidth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerColor:changeWidth", 1, true},
        {"cc.LayerGradient:isCompressedInterpolation", "lua_cc_base_LayerGradient_isCompressedInterpolation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:isCompressedInterpolation", 0, true},
        {"cc.LayerGradient:getStartOpacity", "lua_cc_base_LayerGradient_getStartOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:getStartOpacity", 0, true},
        {"cc.LayerGradient:setCompressedInterpolation", "lua_cc_base_LayerGradient_setCompressedInterpolation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setCompressedInterpolation", 1, true},
        {"cc.LayerGradient:getEndOpacity", "lua_cc_base_LayerGradient_getEndOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:getEndOpacity", 0, true},
        {"cc.LayerRadialGradient:getStartOpacity", "lua_cc_base_LayerRadialGradient_getStartOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getStartOpacity", 0, true},
        {"cc.LayerRadialGradient:setExpand", "lua_cc_base_LayerRadialGradient_setExpand", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setExpand", 1, true},
        {"cc.LayerRadialGradient:getEndOpacity", "lua_cc_base_LayerRadialGradient_getEndOpacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getEndOpacity", 0, true},
        {"cc.LayerRadialGradient:setRadius", "lua_cc_base_LayerRadialGradient_setRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setRadius", 1, true},
        {"cc.LayerRadialGradient:getExpand", "lua_cc_base_LayerRadialGradient_getExpand", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getExpand", 0, true},
        {"cc.LayerRadialGradient:getRadius", "lua_cc_base_LayerRadialGradient_getRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getRadius", 0, true},
        {"cc.LayerMultiplex:switchToAndReleaseMe", "lua_cc_base_LayerMultiplex_switchToAndReleaseMe", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerMultiplex:switchToAndReleaseMe", 1, true},
        {"cc.LayerMultiplex:addLayer", "lua_cc_base_LayerMultiplex_addLayer", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerMultiplex:addLayer", 1, true},
        {"cc.LayerMultiplex:switchTo", "lua_cc_base_LayerMultiplex_switchTo", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerMultiplex:switchTo", 1, false},
        {"cc.MenuItem:setEnabled", "lua_cc_base_MenuItem_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:setEnabled", 1, true},
        {"cc.MenuItem:activate", "lua_cc_base_MenuItem_activate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:activate", 0, true},
        {"cc.MenuItem:isEnabled", "lua_cc_base_MenuItem_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:isEnabled", 0, true},
        {"cc.MenuItem:selected", "lua_cc_base_MenuItem_selected", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:selected", 0, true},
        {"cc.MenuItem:isSelected", "lua_cc_base_MenuItem_isSelected", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:isSelected", 0, true},
        {"cc.MenuItem:unselected", "lua_cc_base_MenuItem_unselected", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:unselected", 0, true},
        {"cc.MenuItemLabel:setLabel", "lua_cc_base_MenuItemLabel_setLabel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:setLabel", 1, true},
        {"cc.MenuItemLabel:getString", "lua_cc_base_MenuItemLabel_getString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:getString", 0, true},
        {"cc.MenuItemLabel:setString", "lua_cc_base_MenuItemLabel_setString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:setString", 1, true},
        {"cc.MenuItemLabel:getLabel", "lua_cc_base_MenuItemLabel_getLabel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:getLabel", 0, true},
        {"cc.MenuItemFont:getFontNameObj", "lua_cc_base_MenuItemFont_getFontNameObj", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:getFontNameObj", 0, true},
        {"cc.MenuItemFont:setFontNameObj", "lua_cc_base_MenuItemFont_setFontNameObj", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:setFontNameObj", 1, true},
        {"cc.MenuItemFont:getFontSizeObj", "lua_cc_base_MenuItemFont_getFontSizeObj", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:getFontSizeObj", 0, true},
        {"cc.MenuItemFont:setFontSizeObj", "lua_cc_base_MenuItemFont_setFontSizeObj", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:setFontSizeObj", 1, true},
        {"cc.MenuItemFont:setFontName", "lua_cc_base_MenuItemFont_setFontName", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MenuItemFont:setFontName", 1, true},
        {"cc.MenuItemFont:getFontSize", "lua_cc_base_MenuItemFont_getFontSize", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MenuItemFont:getFontSize", 0, true},
        {"cc.MenuItemFont:getFontName", "lua_cc_base_MenuItemFont_getFontName", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MenuItemFont:getFontName", 0, true},
        {"cc.MenuItemFont:setFontSize", "lua_cc_base_MenuItemFont_setFontSize", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MenuItemFont:setFontSize", 1, true},
        {"cc.MenuItemSprite:setNormalImage", "lua_cc_base_MenuItemSprite_setNormalImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:setNormalImage", 1, true},
        {"cc.MenuItemSprite:setDisabledImage", "lua_cc_base_MenuItemSprite_setDisabledImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:setDisabledImage", 1, true},
        {"cc.MenuItemSprite:setSelectedImage", "lua_cc_base_MenuItemSprite_setSelectedImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:setSelectedImage", 1, true},
        {"cc.MenuItemSprite:getDisabledImage", "lua_cc_base_MenuItemSprite_getDisabledImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:getDisabledImage", 0, true},
        {"cc.MenuItemSprite:getSelectedImage", "lua_cc_base_MenuItemSprite_getSelectedImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:getSelectedImage", 0, true},
        {"cc.MenuItemSprite:getNormalImage", "lua_cc_base_MenuItemSprite_getNormalImage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:getNormalImage", 0, true},
        {"cc.MenuItemImage:setDisabledSpriteFrame", "lua_cc_base_MenuItemImage_setDisabledSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:setDisabledSpriteFrame", 1, true},
        {"cc.MenuItemImage:setSelectedSpriteFrame", "lua_cc_base_MenuItemImage_setSelectedSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:setSelectedSpriteFrame", 1, true},
        {"cc.MenuItemImage:setNormalSpriteFrame", "lua_cc_base_MenuItemImage_setNormalSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:setNormalSpriteFrame", 1, true},
        {"cc.MenuItemToggle:initWithItem", "lua_cc_base_MenuItemToggle_initWithItem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:initWithItem", 1, true},
        {"cc.MenuItemToggle:getSelectedIndex", "lua_cc_base_MenuItemToggle_getSelectedIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:getSelectedIndex", 0, true},
        {"cc.MenuItemToggle:addSubItem", "lua_cc_base_MenuItemToggle_addSubItem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:addSubItem", 1, true},
        {"cc.MenuItemToggle:getSelectedItem", "lua_cc_base_MenuItemToggle_getSelectedItem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:getSelectedItem", 0, true},
        {"cc.MenuItemToggle:setSelectedIndex", "lua_cc_base_MenuItemToggle_setSelectedIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:setSelectedIndex", 1, true},
        {"cc.Menu:setEnabled", "lua_cc_base_Menu_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:setEnabled", 1, true},
        {"cc.Menu:alignItemsVertically", "lua_cc_base_Menu_alignItemsVertically", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:alignItemsVertically", 0, true},
        {"cc.Menu:isEnabled", "lua_cc_base_Menu_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:isEnabled", 0, true},
        {"cc.Menu:alignItemsHorizontally", "lua_cc_base_Menu_alignItemsHorizontally", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:alignItemsHorizontally", 0, true},
        {"cc.Menu:alignItemsHorizontallyWithPadding", "lua_cc_base_Menu_alignItemsHorizontallyWithPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:alignItemsHorizontallyWithPadding", 1, true},
        {"cc.Menu:alignItemsVerticallyWithPadding", "lua_cc_base_Menu_alignItemsVerticallyWithPadding", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:alignItemsVerticallyWithPadding", 1, true},
        {"cc.MotionStreak:reset", "lua_cc_base_MotionStreak_reset", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:reset", 0, true},
        {"cc.MotionStreak:setStartingPositionInitialized", "lua_cc_base_MotionStreak_setStartingPositionInitialized", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:setStartingPositionInitialized", 1, true},
        {"cc.MotionStreak:isStartingPositionInitialized", "lua_cc_base_MotionStreak_isStartingPositionInitialized", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:isStartingPositionInitialized", 0, true},
        {"cc.MotionStreak:isFastMode", "lua_cc_base_MotionStreak_isFastMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:isFastMode", 0, true},
        {"cc.MotionStreak:getStroke", "lua_cc_base_MotionStreak_getStroke", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:getStroke", 0, true},
        {"cc.MotionStreak:setFastMode", "lua_cc_base_MotionStreak_setFastMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:setFastMode", 1, true},
        {"cc.MotionStreak:setStroke", "lua_cc_base_MotionStreak_setStroke", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:setStroke", 1, true},
        {"cc.NodeGrid:setTarget", "lua_cc_base_NodeGrid_setTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NodeGrid:setTarget", 1, true},
        {"cc.NodeGrid:setGrid", "lua_cc_base_NodeGrid_setGrid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NodeGrid:setGrid", 1, true},
        {"cc.ParticleBatchNode:initWithTexture", "lua_cc_base_ParticleBatchNode_initWithTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:initWithTexture", 2, true},
        {"cc.ParticleBatchNode:disableParticle", "lua_cc_base_ParticleBatchNode_disableParticle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:disableParticle", 1, true},
        {"cc.ParticleBatchNode:initWithFile", "lua_cc_base_ParticleBatchNode_initWithFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:initWithFile", 2, true},
        {"cc.ParticleBatchNode:insertChild", "lua_cc_base_ParticleBatchNode_insertChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:insertChild", 2, true},
        {"cc.ParticleBatchNode:removeChildAtIndex", "lua_cc_base_ParticleBatchNode_removeChildAtIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:removeChildAtIndex", 2, true},
        {"cc.ParticleBatchNode:create", "lua_cc_base_ParticleBatchNode_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleBatchNode:create", 1, true},
        {"cc.ParticleBatchNode:createWithTexture", "lua_cc_base_ParticleBatchNode_createWithTexture", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleBatchNode:createWithTexture", 1, true},
        {"cc.SpriteFrameCache:reloadTexture", "lua_cc_base_SpriteFrameCache_reloadTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:reloadTexture", 1, true},
        {"cc.SpriteFrameCache:addSpriteFrame", "lua_cc_base_SpriteFrameCache_addSpriteFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:addSpriteFrame", 2, true},
        {"cc.SpriteFrameCache:findFrame", "lua_cc_base_SpriteFrameCache_findFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:findFrame", 1, true},
        {"cc.SpriteFrameCache:removeSpriteFramesFromFile", "lua_cc_base_SpriteFrameCache_removeSpriteFramesFromFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeSpriteFramesFromFile", 1, true},
        {"cc.SpriteFrameCache:init", "lua_cc_base_SpriteFrameCache_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:init", 0, true},
        {"cc.SpriteFrameCache:removeSpriteFrames", "lua_cc_base_SpriteFrameCache_removeSpriteFrames", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeSpriteFrames", 0, true},
        {"cc.SpriteFrameCache:deregisterSpriteSheetLoader", "lua_cc_base_SpriteFrameCache_deregisterSpriteSheetLoader", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:deregisterSpriteSheetLoader", 1, true},
        {"cc.SpriteFrameCache:removeUnusedSpriteFrames", "lua_cc_base_SpriteFrameCache_removeUnusedSpriteFrames", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeUnusedSpriteFrames", 0, true},
        {"cc.SpriteFrameCache:removeSpriteFramesFromFileContent", "lua_cc_base_SpriteFrameCache_removeSpriteFramesFromFileContent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeSpriteFramesFromFileContent", 1, true},
        {"cc.SpriteFrameCache:removeSpriteFrameByName", "lua_cc_base_SpriteFrameCache_removeSpriteFrameByName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeSpriteFrameByName", 1, true},
        {"cc.SpriteFrameCache:eraseFrame", "lua_cc_base_SpriteFrameCache_eraseFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:eraseFrame", 1, true},
        {"cc.SpriteFrameCache:isSpriteFramesWithFileLoaded", "lua_cc_base_SpriteFrameCache_isSpriteFramesWithFileLoaded", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:isSpriteFramesWithFileLoaded", 1, true},
        {"cc.SpriteFrameCache:removeSpriteFramesFromTexture", "lua_cc_base_SpriteFrameCache_removeSpriteFramesFromTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:removeSpriteFramesFromTexture", 1, true},
        {"cc.SpriteFrameCache:destroyInstance", "lua_cc_base_SpriteFrameCache_destroyInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SpriteFrameCache:destroyInstance", 0, true},
        {"cc.SpriteFrameCache:getInstance", "lua_cc_base_SpriteFrameCache_getInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SpriteFrameCache:getInstance", 0, true},
        {"cc.ParticleData:release", "lua_cc_base_ParticleData_release", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleData:release", 0, true},
        {"cc.ParticleData:getMaxCount", "lua_cc_base_ParticleData_getMaxCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleData:getMaxCount", 0, true},
        {"cc.ParticleData:init", "lua_cc_base_ParticleData_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleData:init", 1, true},
        {"cc.ParticleData:copyParticle", "lua_cc_base_ParticleData_copyParticle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleData:copyParticle", 2, true},
        {"cc.ParticleEmissionMaskCache:removeMask", "lua_cc_base_ParticleEmissionMaskCache_removeMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleEmissionMaskCache:removeMask", 1, true},
        {"cc.ParticleEmissionMaskCache:removeAllMasks", "lua_cc_base_ParticleEmissionMaskCache_removeAllMasks", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleEmissionMaskCache:removeAllMasks", 0, true},
        {"cc.ParticleEmissionMaskCache:getInstance", "lua_cc_base_ParticleEmissionMaskCache_getInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleEmissionMaskCache:getInstance", 0, true},
        {"cc.ParticleSystem:getStartSizeVar", "lua_cc_base_ParticleSystem_getStartSizeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartSizeVar", 0, true},
        {"cc.ParticleSystem:isFull", "lua_cc_base_ParticleSystem_isFull", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isFull", 0, true},
        {"cc.ParticleSystem:getBatchNode", "lua_cc_base_ParticleSystem_getBatchNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getBatchNode", 0, true},
        {"cc.ParticleSystem:getPositionType", "lua_cc_base_ParticleSystem_getPositionType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getPositionType", 0, true},
        {"cc.ParticleSystem:getSpawnAngle", "lua_cc_base_ParticleSystem_getSpawnAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnAngle", 0, true},
        {"cc.ParticleSystem:getEndSpin", "lua_cc_base_ParticleSystem_getEndSpin", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndSpin", 0, true},
        {"cc.ParticleSystem:getSpawnScaleInVar", "lua_cc_base_ParticleSystem_getSpawnScaleInVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnScaleInVar", 0, true},
        {"cc.ParticleSystem:setRotatePerSecondVar", "lua_cc_base_ParticleSystem_setRotatePerSecondVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRotatePerSecondVar", 1, true},
        {"cc.ParticleSystem:setSourcePositionCompatible", "lua_cc_base_ParticleSystem_setSourcePositionCompatible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSourcePositionCompatible", 1, true},
        {"cc.ParticleSystem:getStartSpinVar", "lua_cc_base_ParticleSystem_getStartSpinVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartSpinVar", 0, true},
        {"cc.ParticleSystem:getRadialAccelVar", "lua_cc_base_ParticleSystem_getRadialAccelVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getRadialAccelVar", 0, true},
        {"cc.ParticleSystem:getEndSizeVar", "lua_cc_base_ParticleSystem_getEndSizeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndSizeVar", 0, true},
        {"cc.ParticleSystem:resetAnimationIndices", "lua_cc_base_ParticleSystem_resetAnimationIndices", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resetAnimationIndices", 0, true},
        {"cc.ParticleSystem:setTangentialAccel", "lua_cc_base_ParticleSystem_setTangentialAccel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setTangentialAccel", 1, true},
        {"cc.ParticleSystem:getTotalAnimationIndices", "lua_cc_base_ParticleSystem_getTotalAnimationIndices", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTotalAnimationIndices", 0, true},
        {"cc.ParticleSystem:getRadialAccel", "lua_cc_base_ParticleSystem_getRadialAccel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getRadialAccel", 0, true},
        {"cc.ParticleSystem:getHue", "lua_cc_base_ParticleSystem_getHue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHue", 0, true},
        {"cc.ParticleSystem:setRotatePerSecond", "lua_cc_base_ParticleSystem_setRotatePerSecond", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRotatePerSecond", 1, true},
        {"cc.ParticleSystem:setEndSize", "lua_cc_base_ParticleSystem_setEndSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndSize", 1, true},
        {"cc.ParticleSystem:isAnimationSpeedTimescaleIndependent", "lua_cc_base_ParticleSystem_isAnimationSpeedTimescaleIndependent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isAnimationSpeedTimescaleIndependent", 0, true},
        {"cc.ParticleSystem:resumeEmissions", "lua_cc_base_ParticleSystem_resumeEmissions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resumeEmissions", 0, true},
        {"cc.ParticleSystem:getTangentialAccel", "lua_cc_base_ParticleSystem_getTangentialAccel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTangentialAccel", 0, true},
        {"cc.ParticleSystem:setEndRadius", "lua_cc_base_ParticleSystem_setEndRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndRadius", 1, true},
        {"cc.ParticleSystem:getSpeed", "lua_cc_base_ParticleSystem_getSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpeed", 0, true},
        {"cc.ParticleSystem:pauseEmissions", "lua_cc_base_ParticleSystem_pauseEmissions", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:pauseEmissions", 0, true},
        {"cc.ParticleSystem:getAngle", "lua_cc_base_ParticleSystem_getAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getAngle", 0, true},
        {"cc.ParticleSystem:isLoopAnimated", "lua_cc_base_ParticleSystem_isLoopAnimated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isLoopAnimated", 0, true},
        {"cc.ParticleSystem:setLifeAnimation", "lua_cc_base_ParticleSystem_setLifeAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setLifeAnimation", 1, true},
        {"cc.ParticleSystem:setStartSpin", "lua_cc_base_ParticleSystem_setStartSpin", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartSpin", 1, true},
        {"cc.ParticleSystem:setDuration", "lua_cc_base_ParticleSystem_setDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setDuration", 1, true},
        {"cc.ParticleSystem:initWithTotalParticles", "lua_cc_base_ParticleSystem_initWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:initWithTotalParticles", 1, true},
        {"cc.ParticleSystem:addParticles", "lua_cc_base_ParticleSystem_addParticles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:addParticles", 1, true},
        {"cc.ParticleSystem:setSpawnFadeInVar", "lua_cc_base_ParticleSystem_setSpawnFadeInVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnFadeInVar", 1, true},
        {"cc.ParticleSystem:updateWithNoTime", "lua_cc_base_ParticleSystem_updateWithNoTime", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:updateWithNoTime", 0, true},
        {"cc.ParticleSystem:isBlendAdditive", "lua_cc_base_ParticleSystem_isBlendAdditive", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isBlendAdditive", 0, true},
        {"cc.ParticleSystem:getSpeedVar", "lua_cc_base_ParticleSystem_getSpeedVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpeedVar", 0, true},
        {"cc.ParticleSystem:setPositionType", "lua_cc_base_ParticleSystem_setPositionType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setPositionType", 1, true},
        {"cc.ParticleSystem:stopSystem", "lua_cc_base_ParticleSystem_stopSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:stopSystem", 0, true},
        {"cc.ParticleSystem:setLifeVar", "lua_cc_base_ParticleSystem_setLifeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setLifeVar", 1, true},
        {"cc.ParticleSystem:setHue", "lua_cc_base_ParticleSystem_setHue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHue", 1, true},
        {"cc.ParticleSystem:useHSV", "lua_cc_base_ParticleSystem_useHSV", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:useHSV", 1, true},
        {"cc.ParticleSystem:setEmitterAnimation", "lua_cc_base_ParticleSystem_setEmitterAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmitterAnimation", 1, true},
        {"cc.ParticleSystem:getAtlasIndex", "lua_cc_base_ParticleSystem_getAtlasIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getAtlasIndex", 0, true},
        {"cc.ParticleSystem:getStartSize", "lua_cc_base_ParticleSystem_getStartSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartSize", 0, true},
        {"cc.ParticleSystem:setStartSpinVar", "lua_cc_base_ParticleSystem_setStartSpinVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartSpinVar", 1, true},
        {"cc.ParticleSystem:getHueVar", "lua_cc_base_ParticleSystem_getHueVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHueVar", 0, true},
        {"cc.ParticleSystem:setSpawnAngle", "lua_cc_base_ParticleSystem_setSpawnAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnAngle", 1, true},
        {"cc.ParticleSystem:resetSystem", "lua_cc_base_ParticleSystem_resetSystem", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resetSystem", 0, true},
        {"cc.ParticleSystem:setAtlasIndex", "lua_cc_base_ParticleSystem_setAtlasIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAtlasIndex", 1, true},
        {"cc.ParticleSystem:setTangentialAccelVar", "lua_cc_base_ParticleSystem_setTangentialAccelVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setTangentialAccelVar", 1, true},
        {"cc.ParticleSystem:setEndRadiusVar", "lua_cc_base_ParticleSystem_setEndRadiusVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndRadiusVar", 1, true},
        {"cc.ParticleSystem:getEndRadius", "lua_cc_base_ParticleSystem_getEndRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndRadius", 0, true},
        {"cc.ParticleSystem:isActive", "lua_cc_base_ParticleSystem_isActive", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isActive", 0, true},
        {"cc.ParticleSystem:getTimeScale", "lua_cc_base_ParticleSystem_getTimeScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTimeScale", 0, true},
        {"cc.ParticleSystem:setRadialAccelVar", "lua_cc_base_ParticleSystem_setRadialAccelVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRadialAccelVar", 1, true},
        {"cc.ParticleSystem:setSpawnAngleVar", "lua_cc_base_ParticleSystem_setSpawnAngleVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnAngleVar", 1, true},
        {"cc.ParticleSystem:setStartSize", "lua_cc_base_ParticleSystem_setStartSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartSize", 1, true},
        {"cc.ParticleSystem:setSpeed", "lua_cc_base_ParticleSystem_setSpeed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpeed", 1, true},
        {"cc.ParticleSystem:getStartSpin", "lua_cc_base_ParticleSystem_getStartSpin", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartSpin", 0, true},
        {"cc.ParticleSystem:setAnimationSpeedTimescaleIndependent", "lua_cc_base_ParticleSystem_setAnimationSpeedTimescaleIndependent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAnimationSpeedTimescaleIndependent", 1, true},
        {"cc.ParticleSystem:setStartRadius", "lua_cc_base_ParticleSystem_setStartRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartRadius", 1, true},
        {"cc.ParticleSystem:getResourceFile", "lua_cc_base_ParticleSystem_getResourceFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getResourceFile", 0, true},
        {"cc.ParticleSystem:getRotatePerSecond", "lua_cc_base_ParticleSystem_getRotatePerSecond", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getRotatePerSecond", 0, true},
        {"cc.ParticleSystem:resetEmissionShapes", "lua_cc_base_ParticleSystem_resetEmissionShapes", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resetEmissionShapes", 0, true},
        {"cc.ParticleSystem:setEmitterMode", "lua_cc_base_ParticleSystem_setEmitterMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmitterMode", 1, true},
        {"cc.ParticleSystem:getDuration", "lua_cc_base_ParticleSystem_getDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getDuration", 0, true},
        {"cc.ParticleSystem:isEmitterAnimated", "lua_cc_base_ParticleSystem_isEmitterAnimated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isEmitterAnimated", 0, true},
        {"cc.ParticleSystem:setTimeScale", "lua_cc_base_ParticleSystem_setTimeScale", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setTimeScale", 0, true},
        {"cc.ParticleSystem:updateParticleQuads", "lua_cc_base_ParticleSystem_updateParticleQuads", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:updateParticleQuads", 0, true},
        {"cc.ParticleSystem:getEndSpinVar", "lua_cc_base_ParticleSystem_getEndSpinVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndSpinVar", 0, true},
        {"cc.ParticleSystem:resetAnimationDescriptors", "lua_cc_base_ParticleSystem_resetAnimationDescriptors", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resetAnimationDescriptors", 0, true},
        {"cc.ParticleSystem:setBlendAdditive", "lua_cc_base_ParticleSystem_setBlendAdditive", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setBlendAdditive", 1, true},
        {"cc.ParticleSystem:setLife", "lua_cc_base_ParticleSystem_setLife", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setLife", 1, true},
        {"cc.ParticleSystem:setAngleVar", "lua_cc_base_ParticleSystem_setAngleVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAngleVar", 1, true},
        {"cc.ParticleSystem:setAnimationIndicesAtlas", "lua_cc_base_ParticleSystem_setAnimationIndicesAtlas", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAnimationIndicesAtlas", 0, false},
        {"cc.ParticleSystem:setSpawnFadeIn", "lua_cc_base_ParticleSystem_setSpawnFadeIn", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnFadeIn", 1, true},
        {"cc.ParticleSystem:setRotationIsDir", "lua_cc_base_ParticleSystem_setRotationIsDir", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRotationIsDir", 1, true},
        {"cc.ParticleSystem:setEndSizeVar", "lua_cc_base_ParticleSystem_setEndSizeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndSizeVar", 1, true},
        {"cc.ParticleSystem:isLifeAnimated", "lua_cc_base_ParticleSystem_isLifeAnimated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isLifeAnimated", 0, true},
        {"cc.ParticleSystem:setAngle", "lua_cc_base_ParticleSystem_setAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAngle", 1, true},
        {"cc.ParticleSystem:setBatchNode", "lua_cc_base_ParticleSystem_setBatchNode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setBatchNode", 1, true},
        {"cc.ParticleSystem:getTangentialAccelVar", "lua_cc_base_ParticleSystem_getTangentialAccelVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTangentialAccelVar", 0, true},
        {"cc.ParticleSystem:getEmitterMode", "lua_cc_base_ParticleSystem_getEmitterMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEmitterMode", 0, true},
        {"cc.ParticleSystem:setEndSpinVar", "lua_cc_base_ParticleSystem_setEndSpinVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndSpinVar", 1, true},
        {"cc.ParticleSystem:getSpawnFadeIn", "lua_cc_base_ParticleSystem_getSpawnFadeIn", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnFadeIn", 0, true},
        {"cc.ParticleSystem:getSpawnFadeInVar", "lua_cc_base_ParticleSystem_getSpawnFadeInVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnFadeInVar", 0, true},
        {"cc.ParticleSystem:simulate", "lua_cc_base_ParticleSystem_simulate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:simulate", 0, true},
        {"cc.ParticleSystem:initWithFile", "lua_cc_base_ParticleSystem_initWithFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:initWithFile", 1, true},
        {"cc.ParticleSystem:getAngleVar", "lua_cc_base_ParticleSystem_getAngleVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getAngleVar", 0, true},
        {"cc.ParticleSystem:getRotatePerSecondVar", "lua_cc_base_ParticleSystem_getRotatePerSecondVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getRotatePerSecondVar", 0, true},
        {"cc.ParticleSystem:setHueVar", "lua_cc_base_ParticleSystem_setHueVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHueVar", 1, true},
        {"cc.ParticleSystem:getEndSize", "lua_cc_base_ParticleSystem_getEndSize", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndSize", 0, true},
        {"cc.ParticleSystem:isAnimationReversed", "lua_cc_base_ParticleSystem_isAnimationReversed", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isAnimationReversed", 0, true},
        {"cc.ParticleSystem:getLife", "lua_cc_base_ParticleSystem_getLife", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getLife", 0, true},
        {"cc.ParticleSystem:isPaused", "lua_cc_base_ParticleSystem_isPaused", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isPaused", 0, true},
        {"cc.ParticleSystem:getSpawnScaleIn", "lua_cc_base_ParticleSystem_getSpawnScaleIn", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnScaleIn", 0, true},
        {"cc.ParticleSystem:setFixedFPS", "lua_cc_base_ParticleSystem_setFixedFPS", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setFixedFPS", 0, true},
        {"cc.ParticleSystem:isHSV", "lua_cc_base_ParticleSystem_isHSV", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isHSV", 0, true},
        {"cc.ParticleSystem:setSpeedVar", "lua_cc_base_ParticleSystem_setSpeedVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpeedVar", 1, true},
        {"cc.ParticleSystem:setAutoRemoveOnFinish", "lua_cc_base_ParticleSystem_setAutoRemoveOnFinish", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAutoRemoveOnFinish", 1, true},
        {"cc.ParticleSystem:postStep", "lua_cc_base_ParticleSystem_postStep", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:postStep", 0, true},
        {"cc.ParticleSystem:isEmissionShapes", "lua_cc_base_ParticleSystem_isEmissionShapes", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isEmissionShapes", 0, true},
        {"cc.ParticleSystem:setLoopAnimation", "lua_cc_base_ParticleSystem_setLoopAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setLoopAnimation", 1, true},
        {"cc.ParticleSystem:setEmissionRate", "lua_cc_base_ParticleSystem_setEmissionRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmissionRate", 1, true},
        {"cc.ParticleSystem:getRotationIsDir", "lua_cc_base_ParticleSystem_getRotationIsDir", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getRotationIsDir", 0, true},
        {"cc.ParticleSystem:setSpawnScaleIn", "lua_cc_base_ParticleSystem_setSpawnScaleIn", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnScaleIn", 1, true},
        {"cc.ParticleSystem:getEmissionRate", "lua_cc_base_ParticleSystem_getEmissionRate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEmissionRate", 0, true},
        {"cc.ParticleSystem:setSpawnScaleInVar", "lua_cc_base_ParticleSystem_setSpawnScaleInVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSpawnScaleInVar", 1, true},
        {"cc.ParticleSystem:setEmissionShapes", "lua_cc_base_ParticleSystem_setEmissionShapes", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmissionShapes", 1, true},
        {"cc.ParticleSystem:getLifeVar", "lua_cc_base_ParticleSystem_getLifeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getLifeVar", 0, true},
        {"cc.ParticleSystem:setStartSizeVar", "lua_cc_base_ParticleSystem_setStartSizeVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartSizeVar", 1, true},
        {"cc.ParticleSystem:resimulate", "lua_cc_base_ParticleSystem_resimulate", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:resimulate", 0, true},
        {"cc.ParticleSystem:setMultiAnimationRandom", "lua_cc_base_ParticleSystem_setMultiAnimationRandom", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setMultiAnimationRandom", 0, true},
        {"cc.ParticleSystem:getStartRadius", "lua_cc_base_ParticleSystem_getStartRadius", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartRadius", 0, true},
        {"cc.ParticleSystem:getParticleCount", "lua_cc_base_ParticleSystem_getParticleCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getParticleCount", 0, true},
        {"cc.ParticleSystem:getStartRadiusVar", "lua_cc_base_ParticleSystem_getStartRadiusVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartRadiusVar", 0, true},
        {"cc.ParticleSystem:setEndSpin", "lua_cc_base_ParticleSystem_setEndSpin", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndSpin", 1, true},
        {"cc.ParticleSystem:setRadialAccel", "lua_cc_base_ParticleSystem_setRadialAccel", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRadialAccel", 1, true},
        {"cc.ParticleSystem:setAnimationReverse", "lua_cc_base_ParticleSystem_setAnimationReverse", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setAnimationReverse", 1, true},
        {"cc.ParticleSystem:isAutoRemoveOnFinish", "lua_cc_base_ParticleSystem_isAutoRemoveOnFinish", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isAutoRemoveOnFinish", 0, true},
        {"cc.ParticleSystem:isSourcePositionCompatible", "lua_cc_base_ParticleSystem_isSourcePositionCompatible", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:isSourcePositionCompatible", 0, true},
        {"cc.ParticleSystem:getTotalParticles", "lua_cc_base_ParticleSystem_getTotalParticles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTotalParticles", 0, true},
        {"cc.ParticleSystem:setStartRadiusVar", "lua_cc_base_ParticleSystem_setStartRadiusVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartRadiusVar", 1, true},
        {"cc.ParticleSystem:setTotalParticles", "lua_cc_base_ParticleSystem_setTotalParticles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setTotalParticles", 1, true},
        {"cc.ParticleSystem:getEndRadiusVar", "lua_cc_base_ParticleSystem_getEndRadiusVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndRadiusVar", 0, true},
        {"cc.ParticleSystem:getSpawnAngleVar", "lua_cc_base_ParticleSystem_getSpawnAngleVar", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSpawnAngleVar", 0, true},
        {"cc.ParticleSystem:getFixedFPS", "lua_cc_base_ParticleSystem_getFixedFPS", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getFixedFPS", 0, true},
        {"cc.ParticleSystem:create", "lua_cc_base_ParticleSystem_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:create", 1, true},
        {"cc.ParticleSystem:createWithTotalParticles", "lua_cc_base_ParticleSystem_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createWithTotalParticles", 1, true},
        {"cc.ParticleSystemQuad:setDisplayFrame", "lua_cc_base_ParticleSystemQuad_setDisplayFrame", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemQuad:setDisplayFrame", 1, true},
        {"cc.ParticleSystemQuad:listenRendererRecreated", "lua_cc_base_ParticleSystemQuad_listenRendererRecreated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemQuad:listenRendererRecreated", 1, true},
        {"cc.ParticleSystemQuad:createWithTotalParticles", "lua_cc_base_ParticleSystemQuad_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystemQuad:createWithTotalParticles", 1, true},
        {"cc.ParticleFire:create", "lua_cc_base_ParticleFire_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFire:create", 0, true},
        {"cc.ParticleFire:createWithTotalParticles", "lua_cc_base_ParticleFire_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFire:createWithTotalParticles", 1, true},
        {"cc.ParticleFireworks:create", "lua_cc_base_ParticleFireworks_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFireworks:create", 0, true},
        {"cc.ParticleFireworks:createWithTotalParticles", "lua_cc_base_ParticleFireworks_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFireworks:createWithTotalParticles", 1, true},
        {"cc.ParticleSun:create", "lua_cc_base_ParticleSun_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSun:create", 0, true},
        {"cc.ParticleSun:createWithTotalParticles", "lua_cc_base_ParticleSun_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSun:createWithTotalParticles", 1, true},
        {"cc.ParticleGalaxy:create", "lua_cc_base_ParticleGalaxy_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleGalaxy:create", 0, true},
        {"cc.ParticleGalaxy:createWithTotalParticles", "lua_cc_base_ParticleGalaxy_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleGalaxy:createWithTotalParticles", 1, true},
        {"cc.ParticleFlower:create", "lua_cc_base_ParticleFlower_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFlower:create", 0, true},
        {"cc.ParticleFlower:createWithTotalParticles", "lua_cc_base_ParticleFlower_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleFlower:createWithTotalParticles", 1, true},
        {"cc.ParticleMeteor:create", "lua_cc_base_ParticleMeteor_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleMeteor:create", 0, true},
        {"cc.ParticleMeteor:createWithTotalParticles", "lua_cc_base_ParticleMeteor_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleMeteor:createWithTotalParticles", 1, true},
        {"cc.ParticleSpiral:create", "lua_cc_base_ParticleSpiral_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSpiral:create", 0, true},
        {"cc.ParticleSpiral:createWithTotalParticles", "lua_cc_base_ParticleSpiral_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSpiral:createWithTotalParticles", 1, true},
        {"cc.ParticleExplosion:create", "lua_cc_base_ParticleExplosion_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleExplosion:create", 0, true},
        {"cc.ParticleExplosion:createWithTotalParticles", "lua_cc_base_ParticleExplosion_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleExplosion:createWithTotalParticles", 1, true},
        {"cc.ParticleSmoke:create", "lua_cc_base_ParticleSmoke_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSmoke:create", 0, true},
        {"cc.ParticleSmoke:createWithTotalParticles", "lua_cc_base_ParticleSmoke_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSmoke:createWithTotalParticles", 1, true},
        {"cc.ParticleSnow:create", "lua_cc_base_ParticleSnow_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSnow:create", 0, true},
        {"cc.ParticleSnow:createWithTotalParticles", "lua_cc_base_ParticleSnow_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSnow:createWithTotalParticles", 1, true},
        {"cc.ParticleRain:create", "lua_cc_base_ParticleRain_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleRain:create", 0, true},
        {"cc.ParticleRain:createWithTotalParticles", "lua_cc_base_ParticleRain_createWithTotalParticles", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleRain:createWithTotalParticles", 1, true},
        {"cc.ProgressTimer:initWithSprite", "lua_cc_base_ProgressTimer_initWithSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:initWithSprite", 1, true},
        {"cc.ProgressTimer:isReverseDirection", "lua_cc_base_ProgressTimer_isReverseDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:isReverseDirection", 0, true},
        {"cc.ProgressTimer:getPercentage", "lua_cc_base_ProgressTimer_getPercentage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:getPercentage", 0, true},
        {"cc.ProgressTimer:setSprite", "lua_cc_base_ProgressTimer_setSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setSprite", 1, true},
        {"cc.ProgressTimer:getType", "lua_cc_base_ProgressTimer_getType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:getType", 0, true},
        {"cc.ProgressTimer:getSprite", "lua_cc_base_ProgressTimer_getSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:getSprite", 0, true},
        {"cc.ProgressTimer:setReverseDirection", "lua_cc_base_ProgressTimer_setReverseDirection", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setReverseDirection", 1, true},
        {"cc.ProgressTimer:setPercentage", "lua_cc_base_ProgressTimer_setPercentage", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setPercentage", 1, true},
        {"cc.ProgressTimer:setType", "lua_cc_base_ProgressTimer_setType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setType", 1, true},
        {"cc.ProgressTimer:create", "lua_cc_base_ProgressTimer_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ProgressTimer:create", 1, true},
        {"cc.ProtectedNode:addProtectedChild", "lua_cc_base_ProtectedNode_addProtectedChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:addProtectedChild", 3, false},
        {"cc.ProtectedNode:removeProtectedChildByTag", "lua_cc_base_ProtectedNode_removeProtectedChildByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeProtectedChildByTag", 1, true},
        {"cc.ProtectedNode:reorderProtectedChild", "lua_cc_base_ProtectedNode_reorderProtectedChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:reorderProtectedChild", 2, true},
        {"cc.ProtectedNode:removeAllProtectedChildrenWithCleanup", "lua_cc_base_ProtectedNode_removeAllProtectedChildrenWithCleanup", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup", 1, true},
        {"cc.ProtectedNode:sortAllProtectedChildren", "lua_cc_base_ProtectedNode_sortAllProtectedChildren", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:sortAllProtectedChildren", 0, true},
        {"cc.ProtectedNode:getProtectedChildByTag", "lua_cc_base_ProtectedNode_getProtectedChildByTag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:getProtectedChildByTag", 1, true},
        {"cc.ProtectedNode:removeProtectedChild", "lua_cc_base_ProtectedNode_removeProtectedChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeProtectedChild", 1, true},
        {"cc.ProtectedNode:removeAllProtectedChildren", "lua_cc_base_ProtectedNode_removeAllProtectedChildren", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeAllProtectedChildren", 0, true},
        {"cc.ProtectedNode:create", "lua_cc_base_ProtectedNode_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ProtectedNode:create", 0, true},
        {"cc.RenderTexture:clearStencil", "lua_cc_base_RenderTexture_clearStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:clearStencil", 1, true},
        {"cc.RenderTexture:getClearDepth", "lua_cc_base_RenderTexture_getClearDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getClearDepth", 0, true},
        {"cc.RenderTexture:getClearStencil", "lua_cc_base_RenderTexture_getClearStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getClearStencil", 0, true},
        {"cc.RenderTexture:setClearStencil", "lua_cc_base_RenderTexture_setClearStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setClearStencil", 1, true},
        {"cc.RenderTexture:setSprite", "lua_cc_base_RenderTexture_setSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setSprite", 1, true},
        {"cc.RenderTexture:getSprite", "lua_cc_base_RenderTexture_getSprite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getSprite", 0, true},
        {"cc.RenderTexture:isAutoDraw", "lua_cc_base_RenderTexture_isAutoDraw", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:isAutoDraw", 0, true},
        {"cc.RenderTexture:setKeepMatrix", "lua_cc_base_RenderTexture_setKeepMatrix", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setKeepMatrix", 1, true},
        {"cc.RenderTexture:setClearFlags", "lua_cc_base_RenderTexture_setClearFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setClearFlags", 1, true},
        {"cc.RenderTexture:begin", "lua_cc_base_RenderTexture_begin", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:begin", 0, true},
        {"cc.RenderTexture:setAutoDraw", "lua_cc_base_RenderTexture_setAutoDraw", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setAutoDraw", 1, true},
        {"cc.RenderTexture:endToLua", "lua_cc_base_RenderTexture_end", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:end", 0, true},
        {"cc.RenderTexture:beginWithClear", "lua_cc_base_RenderTexture_beginWithClear", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:beginWithClear", 6, false},
        {"cc.RenderTexture:clearDepth", "lua_cc_base_RenderTexture_clearDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:clearDepth", 1, true},
        {"cc.RenderTexture:clear", "lua_cc_base_RenderTexture_clear", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:clear", 4, true},
        {"cc.RenderTexture:isSharedRenderTarget", "lua_cc_base_RenderTexture_isSharedRenderTarget", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:isSharedRenderTarget", 0, true},
        {"cc.RenderTexture:getClearFlags", "lua_cc_base_RenderTexture_getClearFlags", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getClearFlags", 0, true},
        {"cc.RenderTexture:setClearDepth", "lua_cc_base_RenderTexture_setClearDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setClearDepth", 1, true},
        {"cc.TransitionEaseScene:easeActionWithAction", "lua_cc_base_TransitionEaseScene_easeActionWithAction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionEaseScene:easeActionWithAction", 1, true},
        {"cc.TransitionScene:getInScene", "lua_cc_base_TransitionScene_getInScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:getInScene", 0, true},
        {"cc.TransitionScene:finish", "lua_cc_base_TransitionScene_finish", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:finish", 0, true},
        {"cc.TransitionScene:initWithDuration", "lua_cc_base_TransitionScene_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:initWithDuration", 2, true},
        {"cc.TransitionScene:getDuration", "lua_cc_base_TransitionScene_getDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:getDuration", 0, true},
        {"cc.TransitionScene:hideOutShowIn", "lua_cc_base_TransitionScene_hideOutShowIn", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:hideOutShowIn", 0, true},
        {"cc.TransitionScene:create", "lua_cc_base_TransitionScene_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionScene:create", 2, true},
        {"cc.TransitionSceneOriented:initWithDuration", "lua_cc_base_TransitionSceneOriented_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSceneOriented:initWithDuration", 3, true},
        {"cc.TransitionSceneOriented:create", "lua_cc_base_TransitionSceneOriented_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSceneOriented:create", 3, true},
        {"cc.TransitionRotoZoom:create", "lua_cc_base_TransitionRotoZoom_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionRotoZoom:create", 2, true},
        {"cc.TransitionJumpZoom:create", "lua_cc_base_TransitionJumpZoom_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionJumpZoom:create", 2, true},
        {"cc.TransitionMoveInL:action", "lua_cc_base_TransitionMoveInL_action", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInL:action", 0, true},
        {"cc.TransitionMoveInL:create", "lua_cc_base_TransitionMoveInL_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionMoveInL:create", 2, true},
        {"cc.TransitionMoveInR:create", "lua_cc_base_TransitionMoveInR_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionMoveInR:create", 2, true},
        {"cc.TransitionMoveInT:create", "lua_cc_base_TransitionMoveInT_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionMoveInT:create", 2, true},
        {"cc.TransitionMoveInB:create", "lua_cc_base_TransitionMoveInB_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionMoveInB:create", 2, true},
        {"cc.TransitionSlideInL:action", "lua_cc_base_TransitionSlideInL_action", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInL:action", 0, true},
        {"cc.TransitionSlideInL:create", "lua_cc_base_TransitionSlideInL_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSlideInL:create", 2, true},
        {"cc.TransitionSlideInR:create", "lua_cc_base_TransitionSlideInR_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSlideInR:create", 2, true},
        {"cc.TransitionSlideInB:create", "lua_cc_base_TransitionSlideInB_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSlideInB:create", 2, true},
        {"cc.TransitionSlideInT:create", "lua_cc_base_TransitionSlideInT_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSlideInT:create", 2, true},
        {"cc.TransitionShrinkGrow:create", "lua_cc_base_TransitionShrinkGrow_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionShrinkGrow:create", 2, true},
        {"cc.TransitionFlipX:create", "lua_cc_base_TransitionFlipX_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionFlipX:create", 3, false},
        {"cc.TransitionFlipY:create", "lua_cc_base_TransitionFlipY_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionFlipY:create", 3, false},
        {"cc.TransitionFlipAngular:create", "lua_cc_base_TransitionFlipAngular_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionFlipAngular:create", 3, false},
        {"cc.TransitionZoomFlipX:create", "lua_cc_base_TransitionZoomFlipX_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionZoomFlipX:create", 3, false},
        {"cc.TransitionZoomFlipY:create", "lua_cc_base_TransitionZoomFlipY_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionZoomFlipY:create", 3, false},
        {"cc.TransitionZoomFlipAngular:create", "lua_cc_base_TransitionZoomFlipAngular_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionZoomFlipAngular:create", 3, false},
        {"cc.TransitionCrossFade:create", "lua_cc_base_TransitionCrossFade_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionCrossFade:create", 2, true},
        {"cc.TransitionTurnOffTiles:create", "lua_cc_base_TransitionTurnOffTiles_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionTurnOffTiles:create", 2, true},
        {"cc.TransitionSplitCols:action", "lua_cc_base_TransitionSplitCols_action", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSplitCols:action", 0, true},
        {"cc.TransitionSplitCols:create", "lua_cc_base_TransitionSplitCols_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSplitCols:create", 2, true},
        {"cc.TransitionSplitRows:create", "lua_cc_base_TransitionSplitRows_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionSplitRows:create", 2, true},
        {"cc.TransitionFadeTR:create", "lua_cc_base_TransitionFadeTR_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionFadeTR:create", 2, true},
        {"cc.TransitionFadeBL:create", "lua_cc_base_TransitionFadeBL_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionFadeBL:create", 2, true},
        {"cc.TransitionFadeUp:create", "lua_cc_base_TransitionFadeUp_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionFadeUp:create", 2, true},
        {"cc.TransitionFadeDown:create", "lua_cc_base_TransitionFadeDown_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionFadeDown:create", 2, true},
        {"cc.TransitionPageTurn:initWithDuration", "lua_cc_base_TransitionPageTurn_initWithDuration", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionPageTurn:initWithDuration", 3, true},
        {"cc.TransitionPageTurn:create", "lua_cc_base_TransitionPageTurn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionPageTurn:create", 3, true},
        {"cc.TransitionProgress:create", "lua_cc_base_TransitionProgress_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgress:create", 2, true},
        {"cc.TransitionProgressRadialCCW:create", "lua_cc_base_TransitionProgressRadialCCW_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressRadialCCW:create", 2, true},
        {"cc.TransitionProgressRadialCW:create", "lua_cc_base_TransitionProgressRadialCW_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressRadialCW:create", 2, true},
        {"cc.TransitionProgressHorizontal:create", "lua_cc_base_TransitionProgressHorizontal_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressHorizontal:create", 2, true},
        {"cc.TransitionProgressVertical:create", "lua_cc_base_TransitionProgressVertical_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressVertical:create", 2, true},
        {"cc.TransitionProgressInOut:create", "lua_cc_base_TransitionProgressInOut_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressInOut:create", 2, true},
        {"cc.TransitionProgressOutIn:create", "lua_cc_base_TransitionProgressOutIn_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TransitionProgressOutIn:create", 2, true},
        {"cc.Camera:getDepth", "lua_cc_base_Camera_getDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getDepth", 0, true},
        {"cc.Camera:setBackgroundBrush", "lua_cc_base_Camera_setBackgroundBrush", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setBackgroundBrush", 1, true},
        {"cc.Camera:getZoom", "lua_cc_base_Camera_getZoom", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getZoom", 0, true},
        {"cc.Camera:apply", "lua_cc_base_Camera_apply", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:apply", 0, true},
        {"cc.Camera:getBackgroundBrush", "lua_cc_base_Camera_getBackgroundBrush", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getBackgroundBrush", 0, true},
        {"cc.Camera:setFarPlane", "lua_cc_base_Camera_setFarPlane", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setFarPlane", 1, true},
        {"cc.Camera:isBrushValid", "lua_cc_base_Camera_isBrushValid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:isBrushValid", 0, true},
        {"cc.Camera:applyViewport", "lua_cc_base_Camera_applyViewport", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:applyViewport", 0, true},
        {"cc.Camera:clearBackground", "lua_cc_base_Camera_clearBackground", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:clearBackground", 0, true},
        {"cc.Camera:initDefault", "lua_cc_base_Camera_initDefault", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:initDefault", 0, true},
        {"cc.Camera:setNearPlane", "lua_cc_base_Camera_setNearPlane", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setNearPlane", 1, true},
        {"cc.Camera:applyZoom", "lua_cc_base_Camera_applyZoom", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:applyZoom", 0, true},
        {"cc.Camera:setFOV", "lua_cc_base_Camera_setFOV", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setFOV", 1, true},
        {"cc.Camera:getCameraFlag", "lua_cc_base_Camera_getCameraFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getCameraFlag", 0, true},
        {"cc.Camera:setZoom", "lua_cc_base_Camera_setZoom", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setZoom", 1, true},
        {"cc.Camera:initOrthographic", "lua_cc_base_Camera_initOrthographic", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:initOrthographic", 4, true},
        {"cc.Camera:getRenderOrder", "lua_cc_base_Camera_getRenderOrder", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getRenderOrder", 0, true},
        {"cc.Camera:getFOV", "lua_cc_base_Camera_getFOV", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getFOV", 0, true},
        {"cc.Camera:setScene", "lua_cc_base_Camera_setScene", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setScene", 1, true},
        {"cc.Camera:getNearPlane", "lua_cc_base_Camera_getNearPlane", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getNearPlane", 0, true},
        {"cc.Camera:setCameraFlag", "lua_cc_base_Camera_setCameraFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setCameraFlag", 1, true},
        {"cc.Camera:getFarPlane", "lua_cc_base_Camera_getFarPlane", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getFarPlane", 0, true},
        {"cc.Camera:isViewProjectionUpdated", "lua_cc_base_Camera_isViewProjectionUpdated", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:isViewProjectionUpdated", 0, true},
        {"cc.Camera:initPerspective", "lua_cc_base_Camera_initPerspective", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:initPerspective", 4, true},
        {"cc.Camera:createOrthographic", "lua_cc_base_Camera_createOrthographic", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:createOrthographic", 4, true},
        {"cc.Camera:create", "lua_cc_base_Camera_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:create", 0, true},
        {"cc.Camera:createPerspective", "lua_cc_base_Camera_createPerspective", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:createPerspective", 4, true},
        {"cc.Camera:getDefaultCamera", "lua_cc_base_Camera_getDefaultCamera", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:getDefaultCamera", 0, true},
        {"cc.CameraBackgroundBrush:getBrushType", "lua_cc_base_CameraBackgroundBrush_getBrushType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundBrush:getBrushType", 0, true},
        {"cc.CameraBackgroundBrush:drawBackground", "lua_cc_base_CameraBackgroundBrush_drawBackground", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundBrush:drawBackground", 1, true},
        {"cc.CameraBackgroundBrush:init", "lua_cc_base_CameraBackgroundBrush_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundBrush:init", 0, true},
        {"cc.CameraBackgroundBrush:isValid", "lua_cc_base_CameraBackgroundBrush_isValid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundBrush:isValid", 0, true},
        {"cc.CameraBackgroundBrush:createSkyboxBrush", "lua_cc_base_CameraBackgroundBrush_createSkyboxBrush", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundBrush:createSkyboxBrush", 6, true},
        {"cc.CameraBackgroundBrush:createNoneBrush", "lua_cc_base_CameraBackgroundBrush_createNoneBrush", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundBrush:createNoneBrush", 0, true},
        {"cc.CameraBackgroundBrush:createDepthBrush", "lua_cc_base_CameraBackgroundBrush_createDepthBrush", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundBrush:createDepthBrush", 0, true},
        {"cc.CameraBackgroundDepthBrush:setDepth", "lua_cc_base_CameraBackgroundDepthBrush_setDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundDepthBrush:setDepth", 1, true},
        {"cc.CameraBackgroundDepthBrush:create", "lua_cc_base_CameraBackgroundDepthBrush_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundDepthBrush:create", 1, true},
        {"cc.CameraBackgroundSkyBoxBrush:isActived", "lua_cc_base_CameraBackgroundSkyBoxBrush_isActived", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:isActived", 0, true},
        {"cc.CameraBackgroundSkyBoxBrush:setTextureValid", "lua_cc_base_CameraBackgroundSkyBoxBrush_setTextureValid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:setTextureValid", 1, true},
        {"cc.CameraBackgroundSkyBoxBrush:setActived", "lua_cc_base_CameraBackgroundSkyBoxBrush_setActived", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:setActived", 1, true},
        {"cc.CameraBackgroundSkyBoxBrush:create", "lua_cc_base_CameraBackgroundSkyBoxBrush_create", "%s has wrong number of arguments: %d, was expecting %d", "cc.CameraBackgroundSkyBoxBrush:create", 6, false},
        {"cc.GridBase:calculateVertexPoints", "lua_cc_base_GridBase_calculateVertexPoints", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:calculateVertexPoints", 0, true},
        {"cc.GridBase:reuse", "lua_cc_base_GridBase_reuse", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:reuse", 0, true},
        {"cc.GridBase:beforeDraw", "lua_cc_base_GridBase_beforeDraw", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:beforeDraw", 0, true},
        {"cc.GridBase:isTextureFlipped", "lua_cc_base_GridBase_isTextureFlipped", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:isTextureFlipped", 0, true},
        {"cc.GridBase:afterBlit", "lua_cc_base_GridBase_afterBlit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:afterBlit", 0, true},
        {"cc.GridBase:set2DProjection", "lua_cc_base_GridBase_set2DProjection", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:set2DProjection", 0, true},
        {"cc.GridBase:setTextureFlipped", "lua_cc_base_GridBase_setTextureFlipped", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setTextureFlipped", 1, true},
        {"cc.GridBase:blit", "lua_cc_base_GridBase_blit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:blit", 0, true},
        {"cc.GridBase:setActive", "lua_cc_base_GridBase_setActive", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setActive", 1, true},
        {"cc.GridBase:getReuseGrid", "lua_cc_base_GridBase_getReuseGrid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:getReuseGrid", 0, true},
        {"cc.GridBase:beforeBlit", "lua_cc_base_GridBase_beforeBlit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:beforeBlit", 0, true},
        {"cc.GridBase:setReuseGrid", "lua_cc_base_GridBase_setReuseGrid", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setReuseGrid", 1, true},
        {"cc.GridBase:isActive", "lua_cc_base_GridBase_isActive", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:isActive", 0, true},
        {"cc.GridBase:afterDraw", "lua_cc_base_GridBase_afterDraw", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:afterDraw", 1, true},
        {"cc.Grid3D:getNeedDepthTestForBlit", "lua_cc_base_Grid3D_getNeedDepthTestForBlit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Grid3D:getNeedDepthTestForBlit", 0, true},
        {"cc.Grid3D:setNeedDepthTestForBlit", "lua_cc_base_Grid3D_setNeedDepthTestForBlit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Grid3D:setNeedDepthTestForBlit", 1, true},
        {"cc.BaseLight:setEnabled", "lua_cc_base_BaseLight_setEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:setEnabled", 1, true},
        {"cc.BaseLight:getIntensity", "lua_cc_base_BaseLight_getIntensity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:getIntensity", 0, true},
        {"cc.BaseLight:isEnabled", "lua_cc_base_BaseLight_isEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:isEnabled", 0, true},
        {"cc.BaseLight:getLightType", "lua_cc_base_BaseLight_getLightType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:getLightType", 0, true},
        {"cc.BaseLight:setLightFlag", "lua_cc_base_BaseLight_setLightFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:setLightFlag", 1, true},
        {"cc.BaseLight:setIntensity", "lua_cc_base_BaseLight_setIntensity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:setIntensity", 1, true},
        {"cc.BaseLight:getLightFlag", "lua_cc_base_BaseLight_getLightFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BaseLight:getLightFlag", 0, true},
        {"cc.PointLight:getRange", "lua_cc_base_PointLight_getRange", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PointLight:getRange", 0, true},
        {"cc.PointLight:setRange", "lua_cc_base_PointLight_setRange", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PointLight:setRange", 1, true},
        {"cc.SpotLight:getRange", "lua_cc_base_SpotLight_getRange", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getRange", 0, true},
        {"cc.SpotLight:getCosInnerAngle", "lua_cc_base_SpotLight_getCosInnerAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getCosInnerAngle", 0, true},
        {"cc.SpotLight:getOuterAngle", "lua_cc_base_SpotLight_getOuterAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getOuterAngle", 0, true},
        {"cc.SpotLight:getInnerAngle", "lua_cc_base_SpotLight_getInnerAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getInnerAngle", 0, true},
        {"cc.SpotLight:getCosOuterAngle", "lua_cc_base_SpotLight_getCosOuterAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getCosOuterAngle", 0, true},
        {"cc.SpotLight:setOuterAngle", "lua_cc_base_SpotLight_setOuterAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:setOuterAngle", 1, true},
        {"cc.SpotLight:setInnerAngle", "lua_cc_base_SpotLight_setInnerAngle", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:setInnerAngle", 1, true},
        {"cc.SpotLight:setRange", "lua_cc_base_SpotLight_setRange", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:setRange", 1, true},
        {"cc.RenderState:getName", "lua_cc_base_RenderState_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderState:getName", 0, true},
        {"cc.Technique:getPassCount", "lua_cc_base_Technique_getPassCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:getPassCount", 0, true},
        {"cc.Technique:setMaterial", "lua_cc_base_Technique_setMaterial", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:setMaterial", 1, true},
        {"cc.Technique:clone", "lua_cc_base_Technique_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:clone", 0, true},
        {"cc.Technique:addPass", "lua_cc_base_Technique_addPass", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:addPass", 1, true},
        {"cc.Technique:getName", "lua_cc_base_Technique_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:getName", 0, true},
        {"cc.Technique:createWithProgramState", "lua_cc_base_Technique_createWithProgramState", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Technique:createWithProgramState", 2, true},
        {"cc.Technique:create", "lua_cc_base_Technique_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Technique:create", 1, true},
        {"cc.Material:clone", "lua_cc_base_Material_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:clone", 0, true},
        {"cc.Material:isTransparent", "lua_cc_base_Material_isTransparent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:isTransparent", 0, true},
        {"cc.Material:isForce2DQueue", "lua_cc_base_Material_isForce2DQueue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:isForce2DQueue", 0, true},
        {"cc.Material:getRenderState", "lua_cc_base_Material_getRenderState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getRenderState", 0, true},
        {"cc.Material:setName", "lua_cc_base_Material_setName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:setName", 1, true},
        {"cc.Material:setForce2DQueue", "lua_cc_base_Material_setForce2DQueue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:setForce2DQueue", 1, true},
        {"cc.Material:getName", "lua_cc_base_Material_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getName", 0, true},
        {"cc.Material:getTechniqueCount", "lua_cc_base_Material_getTechniqueCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getTechniqueCount", 0, true},
        {"cc.Material:setTechnique", "lua_cc_base_Material_setTechnique", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:setTechnique", 1, true},
        {"cc.Material:getTechniqueByName", "lua_cc_base_Material_getTechniqueByName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getTechniqueByName", 1, true},
        {"cc.Material:setPrimitiveType", "lua_cc_base_Material_setPrimitiveType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:setPrimitiveType", 1, true},
        {"cc.Material:addTechnique", "lua_cc_base_Material_addTechnique", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:addTechnique", 1, true},
        {"cc.Material:setTransparent", "lua_cc_base_Material_setTransparent", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:setTransparent", 1, true},
        {"cc.Material:getPrimitiveType", "lua_cc_base_Material_getPrimitiveType", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getPrimitiveType", 0, true},
        {"cc.Material:getTechnique", "lua_cc_base_Material_getTechnique", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getTechnique", 0, true},
        {"cc.Material:createWithFilename", "lua_cc_base_Material_createWithFilename", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Material:createWithFilename", 1, true},
        {"cc.Material:createWithProperties", "lua_cc_base_Material_createWithProperties", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Material:createWithProperties", 1, true},
        {"cc.Material:createWithProgramState", "lua_cc_base_Material_createWithProgramState", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Material:createWithProgramState", 1, true},
        {"cc.Pass:setTechnique", "lua_cc_base_Pass_setTechnique", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setTechnique", 1, true},
        {"cc.Pass:setName", "lua_cc_base_Pass_setName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setName", 1, true},
        {"cc.Pass:getName", "lua_cc_base_Pass_getName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:getName", 0, true},
        {"cc.Pass:clone", "lua_cc_base_Pass_clone", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:clone", 0, true},
        {"cc.Pass:setUniformNormTexture", "lua_cc_base_Pass_setUniformNormTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformNormTexture", 2, true},
        {"cc.Pass:getProgramState", "lua_cc_base_Pass_getProgramState", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:getProgramState", 0, true},
        {"cc.Pass:setUniformTexture", "lua_cc_base_Pass_setUniformTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformTexture", 2, true},
        {"cc.Pass:createWithProgramState", "lua_cc_base_Pass_createWithProgramState", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Pass:createWithProgramState", 2, true},
        {"cc.Pass:create", "lua_cc_base_Pass_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Pass:create", 1, true},
        {"cc.Renderer:getWinding", "lua_cc_base_Renderer_getWinding", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getWinding", 0, true},
        {"cc.Renderer:getDrawnVertices", "lua_cc_base_Renderer_getDrawnVertices", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDrawnVertices", 0, true},
        {"cc.Renderer:render", "lua_cc_base_Renderer_render", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:render", 0, true},
        {"cc.Renderer:createRenderQueue", "lua_cc_base_Renderer_createRenderQueue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:createRenderQueue", 0, true},
        {"cc.Renderer:getStencilTest", "lua_cc_base_Renderer_getStencilTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilTest", 0, true},
        {"cc.Renderer:getRenderTargetFlag", "lua_cc_base_Renderer_getRenderTargetFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getRenderTargetFlag", 0, true},
        {"cc.Renderer:getClearFlag", "lua_cc_base_Renderer_getClearFlag", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getClearFlag", 0, true},
        {"cc.Renderer:setViewPort", "lua_cc_base_Renderer_setViewPort", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setViewPort", 4, true},
        {"cc.Renderer:getStencilReadMask", "lua_cc_base_Renderer_getStencilReadMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilReadMask", 0, true},
        {"cc.Renderer:getClearDepth", "lua_cc_base_Renderer_getClearDepth", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getClearDepth", 0, true},
        {"cc.Renderer:setStencilCompareFunction", "lua_cc_base_Renderer_setStencilCompareFunction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setStencilCompareFunction", 3, true},
        {"cc.Renderer:getClearStencil", "lua_cc_base_Renderer_getClearStencil", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getClearStencil", 0, true},
        {"cc.Renderer:setStencilTest", "lua_cc_base_Renderer_setStencilTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setStencilTest", 1, true},
        {"cc.Renderer:getStencilFailureOperation", "lua_cc_base_Renderer_getStencilFailureOperation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilFailureOperation", 0, true},
        {"cc.Renderer:setDepthTest", "lua_cc_base_Renderer_setDepthTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setDepthTest", 1, true},
        {"cc.Renderer:setScissorRect", "lua_cc_base_Renderer_setScissorRect", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setScissorRect", 4, true},
        {"cc.Renderer:getDepthTest", "lua_cc_base_Renderer_getDepthTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDepthTest", 0, true},
        {"cc.Renderer:init", "lua_cc_base_Renderer_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:init", 0, true},
        {"cc.Renderer:setDepthWrite", "lua_cc_base_Renderer_setDepthWrite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setDepthWrite", 1, true},
        {"cc.Renderer:getStencilPassDepthFailureOperation", "lua_cc_base_Renderer_getStencilPassDepthFailureOperation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilPassDepthFailureOperation", 0, true},
        {"cc.Renderer:setCullMode", "lua_cc_base_Renderer_setCullMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setCullMode", 1, true},
        {"cc.Renderer:popGroup", "lua_cc_base_Renderer_popGroup", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:popGroup", 0, true},
        {"cc.Renderer:pushGroup", "lua_cc_base_Renderer_pushGroup", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:pushGroup", 1, true},
        {"cc.Renderer:getScissorTest", "lua_cc_base_Renderer_getScissorTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getScissorTest", 0, true},
        {"cc.Renderer:getStencilWriteMask", "lua_cc_base_Renderer_getStencilWriteMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilWriteMask", 0, true},
        {"cc.Renderer:endRenderPass", "lua_cc_base_Renderer_endRenderPass", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:endRenderPass", 0, true},
        {"cc.Renderer:getDepthWrite", "lua_cc_base_Renderer_getDepthWrite", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDepthWrite", 0, true},
        {"cc.Renderer:getCullMode", "lua_cc_base_Renderer_getCullMode", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getCullMode", 0, true},
        {"cc.Renderer:getStencilCompareFunction", "lua_cc_base_Renderer_getStencilCompareFunction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilCompareFunction", 0, true},
        {"cc.Renderer:setDepthCompareFunction", "lua_cc_base_Renderer_setDepthCompareFunction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setDepthCompareFunction", 1, true},
        {"cc.Renderer:setStencilWriteMask", "lua_cc_base_Renderer_setStencilWriteMask", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setStencilWriteMask", 1, true},
        {"cc.Renderer:getStencilDepthPassOperation", "lua_cc_base_Renderer_getStencilDepthPassOperation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilDepthPassOperation", 0, true},
        {"cc.Renderer:setWinding", "lua_cc_base_Renderer_setWinding", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setWinding", 1, true},
        {"cc.Renderer:getStencilReferenceValue", "lua_cc_base_Renderer_getStencilReferenceValue", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getStencilReferenceValue", 0, true},
        {"cc.Renderer:beginRenderPass", "lua_cc_base_Renderer_beginRenderPass", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:beginRenderPass", 0, true},
        {"cc.Renderer:setScissorTest", "lua_cc_base_Renderer_setScissorTest", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setScissorTest", 1, true},
        {"cc.Renderer:clean", "lua_cc_base_Renderer_clean", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:clean", 0, true},
        {"cc.Renderer:setStencilOperation", "lua_cc_base_Renderer_setStencilOperation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setStencilOperation", 3, true},
        {"cc.Renderer:getDrawnBatches", "lua_cc_base_Renderer_getDrawnBatches", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDrawnBatches", 0, true},
        {"cc.Renderer:clearDrawStats", "lua_cc_base_Renderer_clearDrawStats", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:clearDrawStats", 0, true},
        {"cc.Renderer:getDepthCompareFunction", "lua_cc_base_Renderer_getDepthCompareFunction", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDepthCompareFunction", 0, true},
        {"cc.TextureCache:reloadTexture", "lua_cc_base_TextureCache_reloadTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:reloadTexture", 1, true},
        {"cc.TextureCache:unbindAllImageAsync", "lua_cc_base_TextureCache_unbindAllImageAsync", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:unbindAllImageAsync", 0, true},
        {"cc.TextureCache:removeTextureForKey", "lua_cc_base_TextureCache_removeTextureForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:removeTextureForKey", 1, true},
        {"cc.TextureCache:removeAllTextures", "lua_cc_base_TextureCache_removeAllTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:removeAllTextures", 0, true},
        {"cc.TextureCache:getDescription", "lua_cc_base_TextureCache_getDescription", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:getDescription", 0, true},
        {"cc.TextureCache:getCachedTextureInfo", "lua_cc_base_TextureCache_getCachedTextureInfo", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:getCachedTextureInfo", 0, true},
        {"cc.TextureCache:unbindImageAsync", "lua_cc_base_TextureCache_unbindImageAsync", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:unbindImageAsync", 1, true},
        {"cc.TextureCache:getTextureForKey", "lua_cc_base_TextureCache_getTextureForKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:getTextureForKey", 1, true},
        {"cc.TextureCache:getTextureFilePath", "lua_cc_base_TextureCache_getTextureFilePath", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:getTextureFilePath", 1, true},
        {"cc.TextureCache:renameTextureWithKey", "lua_cc_base_TextureCache_renameTextureWithKey", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:renameTextureWithKey", 2, true},
        {"cc.TextureCache:removeUnusedTextures", "lua_cc_base_TextureCache_removeUnusedTextures", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:removeUnusedTextures", 0, true},
        {"cc.TextureCache:removeTexture", "lua_cc_base_TextureCache_removeTexture", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:removeTexture", 1, true},
        {"cc.TextureCache:waitForQuit", "lua_cc_base_TextureCache_waitForQuit", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:waitForQuit", 0, true},
        {"cc.TextureCache:setETC1AlphaFileSuffix", "lua_cc_base_TextureCache_setETC1AlphaFileSuffix", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TextureCache:setETC1AlphaFileSuffix", 1, true},
        {"cc.TextureCache:getETC1AlphaFileSuffix", "lua_cc_base_TextureCache_getETC1AlphaFileSuffix", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TextureCache:getETC1AlphaFileSuffix", 0, true},
        {"cc.Device:setAccelerometerEnabled", "lua_cc_base_Device_setAccelerometerEnabled", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Device:setAccelerometerEnabled", 1, true},
        {"cc.Device:setAccelerometerInterval", "lua_cc_base_Device_setAccelerometerInterval", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Device:setAccelerometerInterval", 1, true},
        {"cc.Device:setKeepScreenOn", "lua_cc_base_Device_setKeepScreenOn", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Device:setKeepScreenOn", 1, true},
        {"cc.Device:vibrate", "lua_cc_base_Device_vibrate", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Device:vibrate", 1, true},
        {"cc.Device:getDPI", "lua_cc_base_Device_getDPI", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Device:getDPI", 0, true},
        {"cc.GLViewImpl:createWithFullScreen", "lua_cc_base_GLViewImpl_createWithFullScreen", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLViewImpl:createWithFullScreen", 1, true},
        {"cc.AnimationCache:getAnimation", "lua_cc_base_AnimationCache_getAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:getAnimation", 1, true},
        {"cc.AnimationCache:addAnimation", "lua_cc_base_AnimationCache_addAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:addAnimation", 2, true},
        {"cc.AnimationCache:init", "lua_cc_base_AnimationCache_init", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:init", 0, true},
        {"cc.AnimationCache:removeAnimation", "lua_cc_base_AnimationCache_removeAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:removeAnimation", 1, true},
        {"cc.AnimationCache:destroyInstance", "lua_cc_base_AnimationCache_destroyInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AnimationCache:destroyInstance", 0, true},
        {"cc.AnimationCache:getInstance", "lua_cc_base_AnimationCache_getInstance", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AnimationCache:getInstance", 0, true},
        {"cc.SpriteBatchNode:appendChild", "lua_cc_base_SpriteBatchNode_appendChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:appendChild", 1, true},
        {"cc.SpriteBatchNode:reorderBatch", "lua_cc_base_SpriteBatchNode_reorderBatch", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:reorderBatch", 1, true},
        {"cc.SpriteBatchNode:removeSpriteFromAtlas", "lua_cc_base_SpriteBatchNode_removeSpriteFromAtlas", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:removeSpriteFromAtlas", 1, true},
        {"cc.SpriteBatchNode:addSpriteWithoutQuad", "lua_cc_base_SpriteBatchNode_addSpriteWithoutQuad", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:addSpriteWithoutQuad", 3, true},
        {"cc.SpriteBatchNode:atlasIndexForChild", "lua_cc_base_SpriteBatchNode_atlasIndexForChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:atlasIndexForChild", 2, true},
        {"cc.SpriteBatchNode:increaseAtlasCapacity", "lua_cc_base_SpriteBatchNode_increaseAtlasCapacity", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:increaseAtlasCapacity", 0, true},
        {"cc.SpriteBatchNode:lowestAtlasIndexInChild", "lua_cc_base_SpriteBatchNode_lowestAtlasIndexInChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:lowestAtlasIndexInChild", 1, true},
        {"cc.SpriteBatchNode:highestAtlasIndexInChild", "lua_cc_base_SpriteBatchNode_highestAtlasIndexInChild", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:highestAtlasIndexInChild", 1, true},
        {"cc.ParallaxNode:create", "lua_cc_base_ParallaxNode_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParallaxNode:create", 0, true},
        {"cc.TMXObjectGroup:setGroupName", "lua_cc_base_TMXObjectGroup_setGroupName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:setGroupName", 1, true},
        {"cc.TMXObjectGroup:getGroupName", "lua_cc_base_TMXObjectGroup_getGroupName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:getGroupName", 0, true},
        {"cc.TMXMapInfo:setCurrentString", "lua_cc_base_TMXMapInfo_setCurrentString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setCurrentString", 1, true},
        {"cc.TMXMapInfo:getHexSideLength", "lua_cc_base_TMXMapInfo_getHexSideLength", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getHexSideLength", 0, true},
        {"cc.TMXMapInfo:getOrientation", "lua_cc_base_TMXMapInfo_getOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getOrientation", 0, true},
        {"cc.TMXMapInfo:parseXMLFile", "lua_cc_base_TMXMapInfo_parseXMLFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:parseXMLFile", 1, true},
        {"cc.TMXMapInfo:getParentElement", "lua_cc_base_TMXMapInfo_getParentElement", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getParentElement", 0, true},
        {"cc.TMXMapInfo:setTMXFileName", "lua_cc_base_TMXMapInfo_setTMXFileName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setTMXFileName", 1, true},
        {"cc.TMXMapInfo:parseXMLString", "lua_cc_base_TMXMapInfo_parseXMLString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:parseXMLString", 1, true},
        {"cc.TMXMapInfo:getStaggerAxis", "lua_cc_base_TMXMapInfo_getStaggerAxis", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getStaggerAxis", 0, true},
        {"cc.TMXMapInfo:setHexSideLength", "lua_cc_base_TMXMapInfo_setHexSideLength", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setHexSideLength", 1, true},
        {"cc.TMXMapInfo:initWithTMXFile", "lua_cc_base_TMXMapInfo_initWithTMXFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:initWithTMXFile", 1, true},
        {"cc.TMXMapInfo:getParentGID", "lua_cc_base_TMXMapInfo_getParentGID", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getParentGID", 0, true},
        {"cc.TMXMapInfo:setParentElement", "lua_cc_base_TMXMapInfo_setParentElement", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setParentElement", 1, true},
        {"cc.TMXMapInfo:initWithXML", "lua_cc_base_TMXMapInfo_initWithXML", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:initWithXML", 2, true},
        {"cc.TMXMapInfo:setParentGID", "lua_cc_base_TMXMapInfo_setParentGID", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setParentGID", 1, true},
        {"cc.TMXMapInfo:getLayerAttribs", "lua_cc_base_TMXMapInfo_getLayerAttribs", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getLayerAttribs", 0, true},
        {"cc.TMXMapInfo:isStoringCharacters", "lua_cc_base_TMXMapInfo_isStoringCharacters", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:isStoringCharacters", 0, true},
        {"cc.TMXMapInfo:getExternalTilesetFileName", "lua_cc_base_TMXMapInfo_getExternalTilesetFileName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getExternalTilesetFileName", 0, true},
        {"cc.TMXMapInfo:getTMXFileName", "lua_cc_base_TMXMapInfo_getTMXFileName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getTMXFileName", 0, true},
        {"cc.TMXMapInfo:setStaggerIndex", "lua_cc_base_TMXMapInfo_setStaggerIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setStaggerIndex", 1, true},
        {"cc.TMXMapInfo:setOrientation", "lua_cc_base_TMXMapInfo_setOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setOrientation", 1, true},
        {"cc.TMXMapInfo:getCurrentString", "lua_cc_base_TMXMapInfo_getCurrentString", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getCurrentString", 0, true},
        {"cc.TMXMapInfo:setStoringCharacters", "lua_cc_base_TMXMapInfo_setStoringCharacters", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setStoringCharacters", 1, true},
        {"cc.TMXMapInfo:setStaggerAxis", "lua_cc_base_TMXMapInfo_setStaggerAxis", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setStaggerAxis", 1, true},
        {"cc.TMXMapInfo:getStaggerIndex", "lua_cc_base_TMXMapInfo_getStaggerIndex", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getStaggerIndex", 0, true},
        {"cc.TMXMapInfo:setLayerAttribs", "lua_cc_base_TMXMapInfo_setLayerAttribs", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setLayerAttribs", 1, true},
        {"cc.TMXMapInfo:create", "lua_cc_base_TMXMapInfo_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TMXMapInfo:create", 1, true},
        {"cc.TMXMapInfo:createWithXML", "lua_cc_base_TMXMapInfo_createWithXML", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TMXMapInfo:createWithXML", 2, true},
        {"cc.TileMapAtlas:initWithTileFile", "lua_cc_base_TileMapAtlas_initWithTileFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TileMapAtlas:initWithTileFile", 4, true},
        {"cc.TileMapAtlas:releaseMap", "lua_cc_base_TileMapAtlas_releaseMap", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TileMapAtlas:releaseMap", 0, true},
        {"cc.TileMapAtlas:create", "lua_cc_base_TileMapAtlas_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TileMapAtlas:create", 4, true},
        {"cc.FastTMXLayer:setLayerOrientation", "lua_cc_base_FastTMXLayer_setLayerOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setLayerOrientation", 1, true},
        {"cc.FastTMXLayer:initWithTilesetInfo", "lua_cc_base_FastTMXLayer_initWithTilesetInfo", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:initWithTilesetInfo", 3, true},
        {"cc.FastTMXLayer:hasTileAnimation", "lua_cc_base_FastTMXLayer_hasTileAnimation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:hasTileAnimation", 0, true},
        {"cc.FastTMXLayer:getLayerOrientation", "lua_cc_base_FastTMXLayer_getLayerOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getLayerOrientation", 0, true},
        {"cc.FastTMXLayer:setLayerName", "lua_cc_base_FastTMXLayer_setLayerName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setLayerName", 1, true},
        {"cc.FastTMXLayer:setupTiles", "lua_cc_base_FastTMXLayer_setupTiles", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setupTiles", 0, true},
        {"cc.FastTMXLayer:getLayerName", "lua_cc_base_FastTMXLayer_getLayerName", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getLayerName", 0, true},
        {"cc.FastTMXLayer:setTileSet", "lua_cc_base_FastTMXLayer_setTileSet", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setTileSet", 1, true},
        {"cc.FastTMXLayer:getTileSet", "lua_cc_base_FastTMXLayer_getTileSet", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getTileSet", 0, true},
        {"cc.FastTMXLayer:getTileAnimManager", "lua_cc_base_FastTMXLayer_getTileAnimManager", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getTileAnimManager", 0, true},
        {"cc.FastTMXLayer:create", "lua_cc_base_FastTMXLayer_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FastTMXLayer:create", 3, true},
        {"cc.TMXTileAnimTask:start", "lua_cc_base_TMXTileAnimTask_start", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimTask:start", 0, true},
        {"cc.TMXTileAnimTask:stop", "lua_cc_base_TMXTileAnimTask_stop", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimTask:stop", 0, true},
        {"cc.TMXTileAnimTask:isRunning", "lua_cc_base_TMXTileAnimTask_isRunning", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimTask:isRunning", 0, true},
        {"cc.TMXTileAnimManager:startAll", "lua_cc_base_TMXTileAnimManager_startAll", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimManager:startAll", 0, true},
        {"cc.TMXTileAnimManager:stopAll", "lua_cc_base_TMXTileAnimManager_stopAll", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimManager:stopAll", 0, true},
        {"cc.TMXTileAnimManager:create", "lua_cc_base_TMXTileAnimManager_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TMXTileAnimManager:create", 1, true},
        {"cc.FastTMXTiledMap:getObjectGroup", "lua_cc_base_FastTMXTiledMap_getObjectGroup", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getObjectGroup", 1, true},
        {"cc.FastTMXTiledMap:getResourceFile", "lua_cc_base_FastTMXTiledMap_getResourceFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getResourceFile", 0, true},
        {"cc.FastTMXTiledMap:getLayerCount", "lua_cc_base_FastTMXTiledMap_getLayerCount", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getLayerCount", 0, true},
        {"cc.FastTMXTiledMap:initWithTMXFile", "lua_cc_base_FastTMXTiledMap_initWithTMXFile", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:initWithTMXFile", 1, true},
        {"cc.FastTMXTiledMap:setTileAnimEnabled", "lua_cc_base_FastTMXTiledMap_setTileAnimEnabled", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setTileAnimEnabled", 1, true},
        {"cc.FastTMXTiledMap:initWithXML", "lua_cc_base_FastTMXTiledMap_initWithXML", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:initWithXML", 2, true},
        {"cc.FastTMXTiledMap:getLayer", "lua_cc_base_FastTMXTiledMap_getLayer", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getLayer", 1, true},
        {"cc.FastTMXTiledMap:getMapOrientation", "lua_cc_base_FastTMXTiledMap_getMapOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getMapOrientation", 0, true},
        {"cc.FastTMXTiledMap:setMapOrientation", "lua_cc_base_FastTMXTiledMap_setMapOrientation", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setMapOrientation", 1, true},
        {"cc.FastTMXTiledMap:create", "lua_cc_base_FastTMXTiledMap_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FastTMXTiledMap:create", 1, true},
        {"cc.FastTMXTiledMap:createWithXML", "lua_cc_base_FastTMXTiledMap_createWithXML", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FastTMXTiledMap:createWithXML", 2, true},
        {"cc.MotionStreak3D:reset", "lua_cc_base_MotionStreak3D_reset", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:reset", 0, true},
        {"cc.MotionStreak3D:setStartingPositionInitialized", "lua_cc_base_MotionStreak3D_setStartingPositionInitialized", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:setStartingPositionInitialized", 1, true},
        {"cc.MotionStreak3D:isStartingPositionInitialized", "lua_cc_base_MotionStreak3D_isStartingPositionInitialized", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:isStartingPositionInitialized", 0, true},
        {"cc.MotionStreak3D:getStroke", "lua_cc_base_MotionStreak3D_getStroke", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:getStroke", 0, true},
        {"cc.MotionStreak3D:setStroke", "lua_cc_base_MotionStreak3D_setStroke", "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:setStroke", 1, true},
        {"cc.ComponentLua:create", "lua_cc_base_ComponentLua_create", "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ComponentLua:create", 1, true},
};
const char* parent_name(const char* type)
{
    struct Parent { const char* type; const char* parent; };
    static const Parent parents[] = {
        {"cc.Ref", ""},
        {"cc.Console", "cc.Ref"},
        {"cc.EventListener", "cc.Ref"},
        {"cc.EventListenerCustom", "cc.EventListener"},
        {"ccb.ShaderCache", "cc.Ref"},
        {"cc.Texture2D", "cc.Ref"},
        {"cc.Touch", "cc.Ref"},
        {"cc.Event", "cc.Ref"},
        {"cc.EventTouch", "cc.Event"},
        {"cc.EventKeyboard", "cc.Event"},
        {"cc.Component", "cc.Ref"},
        {"cc.Node", "cc.Ref"},
        {"cc.Scene", "cc.Node"},
        {"cc.GLView", "cc.Ref"},
        {"cc.Director", ""},
        {"cc.Timer", "cc.Ref"},
        {"cc.Scheduler", "cc.Ref"},
        {"cc.AsyncTaskPool", ""},
        {"cc.Action", "cc.Ref"},
        {"cc.FiniteTimeAction", "cc.Action"},
        {"cc.Speed", "cc.Action"},
        {"cc.Follow", "cc.Action"},
        {"cc.Image", "cc.Ref"},
        {"cc.PolygonInfo", ""},
        {"cc.AutoPolygon", ""},
        {"cc.SpriteFrame", "cc.Ref"},
        {"cc.AnimationFrame", "cc.Ref"},
        {"cc.Animation", "cc.Ref"},
        {"cc.ActionInterval", "cc.FiniteTimeAction"},
        {"cc.Sequence", "cc.ActionInterval"},
        {"cc.Repeat", "cc.ActionInterval"},
        {"cc.RepeatForever", "cc.ActionInterval"},
        {"cc.Spawn", "cc.ActionInterval"},
        {"cc.RotateTo", "cc.ActionInterval"},
        {"cc.RotateBy", "cc.ActionInterval"},
        {"cc.MoveBy", "cc.ActionInterval"},
        {"cc.MoveTo", "cc.MoveBy"},
        {"cc.SkewTo", "cc.ActionInterval"},
        {"cc.SkewBy", "cc.SkewTo"},
        {"cc.JumpBy", "cc.ActionInterval"},
        {"cc.JumpTo", "cc.JumpBy"},
        {"cc.BezierBy", "cc.ActionInterval"},
        {"cc.BezierTo", "cc.BezierBy"},
        {"cc.ScaleTo", "cc.ActionInterval"},
        {"cc.ScaleBy", "cc.ScaleTo"},
        {"cc.Blink", "cc.ActionInterval"},
        {"cc.FadeTo", "cc.ActionInterval"},
        {"cc.FadeIn", "cc.FadeTo"},
        {"cc.FadeOut", "cc.FadeTo"},
        {"cc.TintTo", "cc.ActionInterval"},
        {"cc.TintBy", "cc.ActionInterval"},
        {"cc.DelayTime", "cc.ActionInterval"},
        {"cc.Animate", "cc.ActionInterval"},
        {"cc.TargetedAction", "cc.ActionInterval"},
        {"cc.ActionFloat", "cc.ActionInterval"},
        {"cc.Properties", ""},
        {"cc.UserDefault", ""},
        {"cc.FileUtils", ""},
        {"cc.EventAcceleration", "cc.Event"},
        {"cc.EventCustom", "cc.Event"},
        {"cc.EventDispatcher", "cc.Ref"},
        {"cc.EventFocus", "cc.Event"},
        {"cc.EventListenerAcceleration", "cc.EventListener"},
        {"cc.EventListenerFocus", "cc.EventListener"},
        {"cc.EventListenerKeyboard", "cc.EventListener"},
        {"cc.EventMouse", "cc.Event"},
        {"cc.EventListenerMouse", "cc.EventListener"},
        {"cc.EventListenerController", "cc.EventListener"},
        {"cc.EventListenerTouchOneByOne", "cc.EventListener"},
        {"cc.EventListenerTouchAllAtOnce", "cc.EventListener"},
        {"cc.EventController", "cc.Event"},
        {"cc.ActionCamera", "cc.ActionInterval"},
        {"cc.OrbitCamera", "cc.ActionCamera"},
        {"cc.CardinalSplineTo", "cc.ActionInterval"},
        {"cc.CardinalSplineBy", "cc.CardinalSplineTo"},
        {"cc.CatmullRomTo", "cc.CardinalSplineTo"},
        {"cc.CatmullRomBy", "cc.CardinalSplineBy"},
        {"cc.ActionEase", "cc.ActionInterval"},
        {"cc.EaseRateAction", "cc.ActionEase"},
        {"cc.EaseExponentialIn", "cc.ActionEase"},
        {"cc.EaseExponentialOut", "cc.ActionEase"},
        {"cc.EaseExponentialInOut", "cc.ActionEase"},
        {"cc.EaseSineIn", "cc.ActionEase"},
        {"cc.EaseSineOut", "cc.ActionEase"},
        {"cc.EaseSineInOut", "cc.ActionEase"},
        {"cc.EaseBounce", "cc.ActionEase"},
        {"cc.EaseBounceIn", "cc.ActionEase"},
        {"cc.EaseBounceOut", "cc.ActionEase"},
        {"cc.EaseBounceInOut", "cc.ActionEase"},
        {"cc.EaseBackIn", "cc.ActionEase"},
        {"cc.EaseBackOut", "cc.ActionEase"},
        {"cc.EaseBackInOut", "cc.ActionEase"},
        {"cc.EaseQuadraticActionIn", "cc.ActionEase"},
        {"cc.EaseQuadraticActionOut", "cc.ActionEase"},
        {"cc.EaseQuadraticActionInOut", "cc.ActionEase"},
        {"cc.EaseQuarticActionIn", "cc.ActionEase"},
        {"cc.EaseQuarticActionOut", "cc.ActionEase"},
        {"cc.EaseQuarticActionInOut", "cc.ActionEase"},
        {"cc.EaseQuinticActionIn", "cc.ActionEase"},
        {"cc.EaseQuinticActionOut", "cc.ActionEase"},
        {"cc.EaseQuinticActionInOut", "cc.ActionEase"},
        {"cc.EaseCircleActionIn", "cc.ActionEase"},
        {"cc.EaseCircleActionOut", "cc.ActionEase"},
        {"cc.EaseCircleActionInOut", "cc.ActionEase"},
        {"cc.EaseCubicActionIn", "cc.ActionEase"},
        {"cc.EaseCubicActionOut", "cc.ActionEase"},
        {"cc.EaseCubicActionInOut", "cc.ActionEase"},
        {"cc.EaseIn", "cc.EaseRateAction"},
        {"cc.EaseOut", "cc.EaseRateAction"},
        {"cc.EaseInOut", "cc.EaseRateAction"},
        {"cc.EaseElastic", "cc.ActionEase"},
        {"cc.EaseElasticIn", "cc.EaseElastic"},
        {"cc.EaseElasticOut", "cc.EaseElastic"},
        {"cc.EaseElasticInOut", "cc.EaseElastic"},
        {"cc.EaseBezierAction", "cc.ActionEase"},
        {"cc.ActionInstant", "cc.FiniteTimeAction"},
        {"cc.Show", "cc.ActionInstant"},
        {"cc.Hide", "cc.ActionInstant"},
        {"cc.ToggleVisibility", "cc.ActionInstant"},
        {"cc.RemoveSelf", "cc.ActionInstant"},
        {"cc.FlipX", "cc.ActionInstant"},
        {"cc.FlipY", "cc.ActionInstant"},
        {"cc.Place", "cc.ActionInstant"},
        {"cc.CallFunc", "cc.ActionInstant"},
        {"cc.GridAction", "cc.ActionInterval"},
        {"cc.Grid3DAction", "cc.GridAction"},
        {"cc.TiledGrid3DAction", "cc.GridAction"},
        {"cc.StopGrid", "cc.ActionInstant"},
        {"cc.ReuseGrid", "cc.ActionInstant"},
        {"cc.Waves3D", "cc.Grid3DAction"},
        {"cc.FlipX3D", "cc.Grid3DAction"},
        {"cc.FlipY3D", "cc.FlipX3D"},
        {"cc.Lens3D", "cc.Grid3DAction"},
        {"cc.Ripple3D", "cc.Grid3DAction"},
        {"cc.Shaky3D", "cc.Grid3DAction"},
        {"cc.Liquid", "cc.Grid3DAction"},
        {"cc.Waves", "cc.Grid3DAction"},
        {"cc.Twirl", "cc.Grid3DAction"},
        {"cc.ActionManager", "cc.Ref"},
        {"cc.PageTurn3D", "cc.Grid3DAction"},
        {"cc.ProgressTo", "cc.ActionInterval"},
        {"cc.ProgressFromTo", "cc.ActionInterval"},
        {"cc.ShakyTiles3D", "cc.TiledGrid3DAction"},
        {"cc.ShatteredTiles3D", "cc.TiledGrid3DAction"},
        {"cc.ShuffleTiles", "cc.TiledGrid3DAction"},
        {"cc.FadeOutTRTiles", "cc.TiledGrid3DAction"},
        {"cc.FadeOutBLTiles", "cc.FadeOutTRTiles"},
        {"cc.FadeOutUpTiles", "cc.FadeOutTRTiles"},
        {"cc.FadeOutDownTiles", "cc.FadeOutUpTiles"},
        {"cc.TurnOffTiles", "cc.TiledGrid3DAction"},
        {"cc.WavesTiles3D", "cc.TiledGrid3DAction"},
        {"cc.JumpTiles3D", "cc.TiledGrid3DAction"},
        {"cc.SplitRows", "cc.TiledGrid3DAction"},
        {"cc.SplitCols", "cc.TiledGrid3DAction"},
        {"cc.ActionTween", "cc.ActionInterval"},
        {"cc.AtlasNode", "cc.Node"},
        {"cc.ClippingNode", "cc.Node"},
        {"cc.ClippingRectangleNode", "cc.Node"},
        {"cc.DrawNode", "cc.Node"},
        {"cc.Label", "cc.Node"},
        {"cc.LabelAtlas", "cc.AtlasNode"},
        {"cc.Sprite", "cc.Node"},
        {"cc.Layer", "cc.Node"},
        {"cc.LayerColor", "cc.Sprite"},
        {"cc.LayerGradient", "cc.LayerColor"},
        {"cc.LayerRadialGradient", "cc.Node"},
        {"cc.LayerMultiplex", "cc.Node"},
        {"cc.MenuItem", "cc.Node"},
        {"cc.MenuItemLabel", "cc.MenuItem"},
        {"cc.MenuItemAtlasFont", "cc.MenuItemLabel"},
        {"cc.MenuItemFont", "cc.MenuItemLabel"},
        {"cc.MenuItemSprite", "cc.MenuItem"},
        {"cc.MenuItemImage", "cc.MenuItemSprite"},
        {"cc.MenuItemToggle", "cc.MenuItem"},
        {"cc.Menu", "cc.Node"},
        {"cc.MotionStreak", "cc.Node"},
        {"cc.NodeGrid", "cc.Node"},
        {"cc.ParticleBatchNode", "cc.Node"},
        {"cc.SpriteSheet", ""},
        {"cc.SpriteFrameCache", "cc.Ref"},
        {"cc.ParticleData", ""},
        {"cc.ParticleEmissionMaskCache", "cc.Ref"},
        {"cc.ParticleSystem", "cc.Node"},
        {"cc.ParticleSystemQuad", "cc.ParticleSystem"},
        {"cc.ParticleFire", "cc.ParticleSystemQuad"},
        {"cc.ParticleFireworks", "cc.ParticleSystemQuad"},
        {"cc.ParticleSun", "cc.ParticleSystemQuad"},
        {"cc.ParticleGalaxy", "cc.ParticleSystemQuad"},
        {"cc.ParticleFlower", "cc.ParticleSystemQuad"},
        {"cc.ParticleMeteor", "cc.ParticleSystemQuad"},
        {"cc.ParticleSpiral", "cc.ParticleSystemQuad"},
        {"cc.ParticleExplosion", "cc.ParticleSystemQuad"},
        {"cc.ParticleSmoke", "cc.ParticleSystemQuad"},
        {"cc.ParticleSnow", "cc.ParticleSystemQuad"},
        {"cc.ParticleRain", "cc.ParticleSystemQuad"},
        {"cc.ProgressTimer", "cc.Node"},
        {"cc.ProtectedNode", "cc.Node"},
        {"cc.RenderTexture", "cc.Node"},
        {"cc.TransitionEaseScene", ""},
        {"cc.TransitionScene", "cc.Scene"},
        {"cc.TransitionSceneOriented", "cc.TransitionScene"},
        {"cc.TransitionRotoZoom", "cc.TransitionScene"},
        {"cc.TransitionJumpZoom", "cc.TransitionScene"},
        {"cc.TransitionMoveInL", "cc.TransitionScene"},
        {"cc.TransitionMoveInR", "cc.TransitionMoveInL"},
        {"cc.TransitionMoveInT", "cc.TransitionMoveInL"},
        {"cc.TransitionMoveInB", "cc.TransitionMoveInL"},
        {"cc.TransitionSlideInL", "cc.TransitionScene"},
        {"cc.TransitionSlideInR", "cc.TransitionSlideInL"},
        {"cc.TransitionSlideInB", "cc.TransitionSlideInL"},
        {"cc.TransitionSlideInT", "cc.TransitionSlideInL"},
        {"cc.TransitionShrinkGrow", "cc.TransitionScene"},
        {"cc.TransitionFlipX", "cc.TransitionSceneOriented"},
        {"cc.TransitionFlipY", "cc.TransitionSceneOriented"},
        {"cc.TransitionFlipAngular", "cc.TransitionSceneOriented"},
        {"cc.TransitionZoomFlipX", "cc.TransitionSceneOriented"},
        {"cc.TransitionZoomFlipY", "cc.TransitionSceneOriented"},
        {"cc.TransitionZoomFlipAngular", "cc.TransitionSceneOriented"},
        {"cc.TransitionFade", "cc.TransitionScene"},
        {"cc.TransitionCrossFade", "cc.TransitionScene"},
        {"cc.TransitionTurnOffTiles", "cc.TransitionScene"},
        {"cc.TransitionSplitCols", "cc.TransitionScene"},
        {"cc.TransitionSplitRows", "cc.TransitionSplitCols"},
        {"cc.TransitionFadeTR", "cc.TransitionScene"},
        {"cc.TransitionFadeBL", "cc.TransitionFadeTR"},
        {"cc.TransitionFadeUp", "cc.TransitionFadeTR"},
        {"cc.TransitionFadeDown", "cc.TransitionFadeTR"},
        {"cc.TransitionPageTurn", "cc.TransitionScene"},
        {"cc.TransitionProgress", "cc.TransitionScene"},
        {"cc.TransitionProgressRadialCCW", "cc.TransitionProgress"},
        {"cc.TransitionProgressRadialCW", "cc.TransitionProgress"},
        {"cc.TransitionProgressHorizontal", "cc.TransitionProgress"},
        {"cc.TransitionProgressVertical", "cc.TransitionProgress"},
        {"cc.TransitionProgressInOut", "cc.TransitionProgress"},
        {"cc.TransitionProgressOutIn", "cc.TransitionProgress"},
        {"cc.Camera", "cc.Node"},
        {"cc.CameraBackgroundBrush", "cc.Ref"},
        {"cc.CameraBackgroundDepthBrush", "cc.CameraBackgroundBrush"},
        {"cc.CameraBackgroundColorBrush", "cc.CameraBackgroundDepthBrush"},
        {"cc.CameraBackgroundSkyBoxBrush", "cc.CameraBackgroundBrush"},
        {"cc.GridBase", "cc.Ref"},
        {"cc.Grid3D", "cc.GridBase"},
        {"cc.TiledGrid3D", "cc.GridBase"},
        {"cc.BaseLight", "cc.Node"},
        {"cc.DirectionLight", "cc.BaseLight"},
        {"cc.PointLight", "cc.BaseLight"},
        {"cc.SpotLight", "cc.BaseLight"},
        {"cc.AmbientLight", "cc.BaseLight"},
        {"cc.RenderState", "cc.Ref"},
        {"cc.Technique", "cc.Ref"},
        {"cc.Material", "cc.Ref"},
        {"cc.Pass", "cc.Ref"},
        {"cc.Renderer", ""},
        {"cc.TextureCache", "cc.Ref"},
        {"cc.Device", ""},
        {"cc.Application", ""},
        {"cc.GLViewImpl", "cc.GLView"},
        {"cc.AnimationCache", "cc.Ref"},
        {"cc.SpriteBatchNode", "cc.Node"},
        {"cc.ParallaxNode", "cc.Node"},
        {"cc.TMXObjectGroup", "cc.Ref"},
        {"cc.TMXLayerInfo", "cc.Ref"},
        {"cc.TMXTilesetInfo", "cc.Ref"},
        {"cc.TMXMapInfo", ""},
        {"cc.TileMapAtlas", "cc.AtlasNode"},
        {"cc.FastTMXLayer", "cc.Node"},
        {"cc.TMXTileAnimTask", "cc.Ref"},
        {"cc.TMXTileAnimManager", "cc.Ref"},
        {"cc.FastTMXTiledMap", "cc.Node"},
        {"cc.MotionStreak3D", "cc.Node"},
        {"cc.ComponentLua", "cc.Component"},
    };
    for (const auto& p : parents) if (std::strcmp(type,p.type)==0) return p.parent;
    return "";
}
const char* native_symbol(const char* name)
{
    for (const auto& e : errors) if (std::strcmp(name,e.name)==0) return e.native;
    return name;
}
void check_receiver(lua_State* L,const char* type,const char* name,bool member)
{
#if CC_DEBUG >= 1
    tolua_Error error{};
    const bool valid=member ? tolua_isusertype(L,1,type,0,&error) : tolua_isusertable(L,1,type,0,&error);
    if (!valid) {
        char text[256]; std::snprintf(text,sizeof(text),"#ferror in function '%s'.",native_symbol(name));
        tolua_error(L,text,&error);
    }
    if (member && !tolua_tousertype(L,1,nullptr)) {
        char text[256]; std::snprintf(text,sizeof(text),"invalid 'cobj' in function '%s'",native_symbol(name));
        tolua_error(L,text,nullptr);
    }
#else
    (void)L; (void)type; (void)name; (void)member;
#endif
}
int fail(lua_State* L,const char* name,int argc,int attempted)
{
    for (const auto& e : errors) if (std::strcmp(name,e.name)==0) {
        if (attempted!=-1 && e.invalid) {
            char text[256]; std::snprintf(text,sizeof(text),"invalid arguments in function '%s'",e.native);
            tolua_error(L,text,nullptr); return 0;
        }
        return luaL_error(L,e.format,e.label,argc,e.expected);
    }
    return luaL_error(L,"unmapped Core binding: %s",name);
}
}

int lua_cc_base_ShaderCache_removeUnusedShader(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ShaderCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ShaderCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ShaderCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ShaderCache_removeUnusedShader'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShaderCache_removeUnusedShader'", nullptr);
            return 0;
        }
        cobj->removeUnusedShader();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ShaderCache:removeUnusedShader",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShaderCache_removeUnusedShader'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShaderCache_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.ShaderCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShaderCache_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::backend::ShaderCache::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.ShaderCache:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShaderCache_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ShaderCache_newVertexShaderModule(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.ShaderCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.ShaderCache:newVertexShaderModule");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShaderCache_newVertexShaderModule'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::backend::ShaderCache::newVertexShaderModule(arg0);
        object_to_luaval<cocos2d::backend::ShaderModule>(tolua_S, "ccb.ShaderModule",(cocos2d::backend::ShaderModule*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.ShaderCache:newVertexShaderModule",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShaderCache_newVertexShaderModule'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ShaderCache_newFragmentShaderModule(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.ShaderCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.ShaderCache:newFragmentShaderModule");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShaderCache_newFragmentShaderModule'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::backend::ShaderCache::newFragmentShaderModule(arg0);
        object_to_luaval<cocos2d::backend::ShaderModule>(tolua_S, "ccb.ShaderModule",(cocos2d::backend::ShaderModule*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.ShaderCache:newFragmentShaderModule",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShaderCache_newFragmentShaderModule'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ShaderCache_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccb.ShaderCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShaderCache_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::backend::ShaderCache::getInstance();
        object_to_luaval<cocos2d::backend::ShaderCache>(tolua_S, "ccb.ShaderCache",(cocos2d::backend::ShaderCache*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccb.ShaderCache:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShaderCache_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_register_cc_base_ShaderCache(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccb.ShaderCache");
    tolua_cclass(tolua_S,"ShaderCache","ccb.ShaderCache","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ShaderCache");
        tolua_function(tolua_S,"removeUnusedShader",lua_cc_base_ShaderCache_removeUnusedShader);
        tolua_function(tolua_S,"destroyInstance", lua_cc_base_ShaderCache_destroyInstance);
        tolua_function(tolua_S,"newVertexShaderModule", lua_cc_base_ShaderCache_newVertexShaderModule);
        tolua_function(tolua_S,"newFragmentShaderModule", lua_cc_base_ShaderCache_newFragmentShaderModule);
        tolua_function(tolua_S,"getInstance", lua_cc_base_ShaderCache_getInstance);
    tolua_endmodule(tolua_S);
    auto typeName = typeid(cocos2d::backend::ShaderCache).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccb.ShaderCache";
    g_typeCast[typeName] = "ccb.ShaderCache";
    return 1;
}

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32

int lua_register_cc_base_EventListenerController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerController");
    tolua_cclass(tolua_S,"EventListenerController","cc.EventListenerController","cc.EventListener",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerController");
    tolua_endmodule(tolua_S);
    auto typeName = typeid(cocos2d::EventListenerController).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "cc.EventListenerController";
    g_typeCast[typeName] = "cc.EventListenerController";
    return 1;
}

#endif

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32

int lua_cc_base_EventController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::EventController::ControllerEventType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:EventController");

            if (!ok) { break; }
            cocos2d::Controller* arg1;
            ok &= luaval_to_object<cocos2d::Controller>(tolua_S, 3, "cc.Controller",&arg1, "cc.EventController:EventController");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.EventController:EventController");

            if (!ok) { break; }
            cobj = new cocos2d::EventController(arg0, arg1, arg2);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventController");
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::EventController::ControllerEventType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:EventController");

            if (!ok) { break; }
            cocos2d::Controller* arg1;
            ok &= luaval_to_object<cocos2d::Controller>(tolua_S, 3, "cc.Controller",&arg1, "cc.EventController:EventController");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventController:EventController");

            if (!ok) { break; }
            cobj = new cocos2d::EventController(arg0, arg1, arg2);
            cobj->autorelease();
            int ID =  (int)cobj->_ID ;
            int* luaID =  &cobj->_luaID ;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventController");
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.EventController:EventController",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_getControllerEventType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_getControllerEventType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_getControllerEventType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getControllerEventType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getControllerEventType",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_getControllerEventType'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_setConnectStatus(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_setConnectStatus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.EventController:setConnectStatus");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_setConnectStatus'", nullptr);
            return 0;
        }
        cobj->setConnectStatus(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:setConnectStatus",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_setConnectStatus'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_isConnected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_isConnected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_isConnected'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isConnected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:isConnected",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_isConnected'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_setKeyCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_setKeyCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventController:setKeyCode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_setKeyCode'", nullptr);
            return 0;
        }
        cobj->setKeyCode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:setKeyCode",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_setKeyCode'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_getController(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_getController'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_getController'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getController();
        object_to_luaval<cocos2d::Controller>(tolua_S, "cc.Controller",(cocos2d::Controller*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getController",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_getController'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventController_getKeyCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventController*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventController_getKeyCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventController_getKeyCode'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getKeyCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventController:getKeyCode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventController_getKeyCode'.",&tolua_err);
#endif

    return 0;
}

int lua_register_cc_base_EventController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventController");
    tolua_cclass(tolua_S,"EventController","cc.EventController","cc.Event",nullptr);

    tolua_beginmodule(tolua_S,"EventController");
        tolua_function(tolua_S,"new",lua_cc_base_EventController_constructor);
        tolua_function(tolua_S,"getControllerEventType",lua_cc_base_EventController_getControllerEventType);
        tolua_function(tolua_S,"setConnectStatus",lua_cc_base_EventController_setConnectStatus);
        tolua_function(tolua_S,"isConnected",lua_cc_base_EventController_isConnected);
        tolua_function(tolua_S,"setKeyCode",lua_cc_base_EventController_setKeyCode);
        tolua_function(tolua_S,"getController",lua_cc_base_EventController_getController);
        tolua_function(tolua_S,"getKeyCode",lua_cc_base_EventController_getKeyCode);
    tolua_endmodule(tolua_S);
    auto typeName = typeid(cocos2d::EventController).name(); // rtti is literal storage
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "cc.EventController";
    g_typeCast[typeName] = "cc.EventController";
    return 1;
}

#endif
int lua_cc_base_Console_setCommandSeparator(lua_State* tolua_S);
int lua_cc_base_EventListenerCustom_constructor(lua_State* tolua_S);
int lua_cc_base_Texture2D_constructor(lua_State* tolua_S);
int lua_cc_base_Texture2D_updateWithMipmaps(lua_State* tolua_S);
int lua_cc_base_Texture2D_initWithString(lua_State* tolua_S);
int lua_cc_base_Texture2D_drawInRect(lua_State* tolua_S);
int lua_cc_base_Texture2D_getContentSize(lua_State* tolua_S);
int lua_cc_base_Texture2D_updateTextureDescriptor(lua_State* tolua_S);
int lua_cc_base_Texture2D_getContentSizeInPixels(lua_State* tolua_S);
int lua_cc_base_Texture2D_drawAtPoint(lua_State* tolua_S);
int lua_cc_base_Texture2D_updateWithSubData(lua_State* tolua_S);
int lua_cc_base_Touch_constructor(lua_State* tolua_S);
int lua_cc_base_Touch_getPreviousLocationInView(lua_State* tolua_S);
int lua_cc_base_Touch_getLocation(lua_State* tolua_S);
int lua_cc_base_Touch_getDelta(lua_State* tolua_S);
int lua_cc_base_Touch_getStartLocationInView(lua_State* tolua_S);
int lua_cc_base_Touch_getStartLocation(lua_State* tolua_S);
int lua_cc_base_Touch_getID(lua_State* tolua_S);
int lua_cc_base_Touch_getLocationInView(lua_State* tolua_S);
int lua_cc_base_Touch_getPreviousLocation(lua_State* tolua_S);
int lua_cc_base_Event_constructor(lua_State* tolua_S);
int lua_cc_base_EventTouch_constructor(lua_State* tolua_S);
int lua_cc_base_EventKeyboard_constructor(lua_State* tolua_S);
int lua_cc_base_Node_constructor(lua_State* tolua_S);
int lua_cc_base_Node_addChild(lua_State* tolua_S);
int lua_cc_base_Node_removeComponent(lua_State* tolua_S);
#if CC_USE_PHYSICS
int lua_cc_base_Node_setPhysicsBody(lua_State* tolua_S);
#endif
int lua_cc_base_Node_getOnExitTransitionDidStartCallback(lua_State* tolua_S);
int lua_cc_base_Node_getChildren(lua_State* tolua_S);
int lua_cc_base_Node_setOnExitCallback(lua_State* tolua_S);
int lua_cc_base_Node_convertToWorldSpaceAR(lua_State* tolua_S);
int lua_cc_base_Node_updateDisplayedOpacity(lua_State* tolua_S);
int lua_cc_base_Node_setCameraMask(lua_State* tolua_S);
int lua_cc_base_Node_getNodeToWorldAffineTransform(lua_State* tolua_S);
int lua_cc_base_Node_getNodeToWorldTransform(lua_State* tolua_S);
int lua_cc_base_Node_getPosition3D(lua_State* tolua_S);
int lua_cc_base_Node_convertToWorldSpace(lua_State* tolua_S);
int lua_cc_base_Node_setOnEnterCallback(lua_State* tolua_S);
int lua_cc_base_Node_setNormalizedPosition(lua_State* tolua_S);
int lua_cc_base_Node_convertTouchToNodeSpace(lua_State* tolua_S);
int lua_cc_base_Node_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_Node_setOnEnterTransitionDidFinishCallback(lua_State* tolua_S);
int lua_cc_base_Node_setProgramState(lua_State* tolua_S);
int lua_cc_base_Node_getNodeToParentAffineTransform(lua_State* tolua_S);
int lua_cc_base_Node_getRotation3D(lua_State* tolua_S);
int lua_cc_base_Node_getNodeToParentTransform(lua_State* tolua_S);
int lua_cc_base_Node_convertTouchToNodeSpaceAR(lua_State* tolua_S);
int lua_cc_base_Node_convertToNodeSpace(lua_State* tolua_S);
int lua_cc_base_Node_setPositionNormalized(lua_State* tolua_S);
int lua_cc_base_Node_setPosition(lua_State* tolua_S);
int lua_cc_base_Node_setRotation3D(lua_State* tolua_S);
int lua_cc_base_Node_setNodeToParentTransform(lua_State* tolua_S);
int lua_cc_base_Node_getAnchorPoint(lua_State* tolua_S);
int lua_cc_base_Node_convertToNodeSpaceAR(lua_State* tolua_S);
int lua_cc_base_Node_visit(lua_State* tolua_S);
#if CC_USE_PHYSICS
int lua_cc_base_Node_getPhysicsBody(lua_State* tolua_S);
#endif
int lua_cc_base_Node_getAnchorPointInPoints(lua_State* tolua_S);
int lua_cc_base_Node_getOnEnterTransitionDidFinishCallback(lua_State* tolua_S);
int lua_cc_base_Node_getDisplayedColor(lua_State* tolua_S);
int lua_cc_base_Node_getScheduler(lua_State* tolua_S);
int lua_cc_base_Node_getParentToNodeAffineTransform(lua_State* tolua_S);
int lua_cc_base_Node_getPositionNormalized(lua_State* tolua_S);
int lua_cc_base_Node_setColor(lua_State* tolua_S);
int lua_cc_base_Node_getParent(lua_State* tolua_S);
int lua_cc_base_Node_hitTest(lua_State* tolua_S);
int lua_cc_base_Node_updateDisplayedColor(lua_State* tolua_S);
int lua_cc_base_Node_getParentToNodeTransform(lua_State* tolua_S);
int lua_cc_base_Node_isScheduled(lua_State* tolua_S);
int lua_cc_base_Node_getWorldPosition(lua_State* tolua_S);
int lua_cc_base_Node_getWorldToNodeAffineTransform(lua_State* tolua_S);
int lua_cc_base_Node_setOpacity(lua_State* tolua_S);
int lua_cc_base_Node_getContentSize(lua_State* tolua_S);
int lua_cc_base_Node_getColor(lua_State* tolua_S);
int lua_cc_base_Node_getBoundingBox(lua_State* tolua_S);
int lua_cc_base_Node_draw(lua_State* tolua_S);
int lua_cc_base_Node_removeFromParentAndCleanup(lua_State* tolua_S);
int lua_cc_base_Node_setPosition3D(lua_State* tolua_S);
int lua_cc_base_Node_getWorldToNodeTransform(lua_State* tolua_S);
int lua_cc_base_Node_getNormalizedPosition(lua_State* tolua_S);
int lua_cc_base_Node_setOnExitTransitionDidStartCallback(lua_State* tolua_S);
int lua_cc_base_Node_getActionManager(lua_State* tolua_S);
int lua_cc_base_Scene_constructor(lua_State* tolua_S);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initWithPhysics(lua_State* tolua_S);
#endif
int lua_cc_base_Scene_render(lua_State* tolua_S);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
int lua_cc_base_Scene_stepPhysicsAndNavigation(lua_State* tolua_S);
#endif
#if CC_USE_PHYSICS
int lua_cc_base_Scene_getPhysicsWorld(lua_State* tolua_S);
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initPhysicsWorld(lua_State* tolua_S);
#endif
int lua_cc_base_Scene_initWithSize(lua_State* tolua_S);
int lua_cc_base_Scene_createWithSize(lua_State* tolua_S);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_createWithPhysics(lua_State* tolua_S);
#endif
int lua_cc_base_GLView_getViewPortRect(lua_State* tolua_S);
int lua_cc_base_GLView_getSafeAreaRect(lua_State* tolua_S);
int lua_cc_base_GLView_getFrameSize(lua_State* tolua_S);
int lua_cc_base_GLView_getVisibleOrigin(lua_State* tolua_S);
int lua_cc_base_GLView_getDesignResolutionSize(lua_State* tolua_S);
int lua_cc_base_GLView_setIcon(lua_State* tolua_S);
int lua_cc_base_GLView_getScissorRect(lua_State* tolua_S);
int lua_cc_base_GLView_getVisibleRect(lua_State* tolua_S);
int lua_cc_base_GLView_getVisibleSize(lua_State* tolua_S);
int lua_cc_base_GLView_setGLContextAttrs(lua_State* tolua_S);
int lua_cc_base_GLView_getGLContextAttrs(lua_State* tolua_S);
int lua_cc_base_Director_getAxmolThreadId(lua_State* tolua_S);
int lua_cc_base_Director_getWinSizeInPixels(lua_State* tolua_S);
int lua_cc_base_Director_getSafeAreaRect(lua_State* tolua_S);
int lua_cc_base_Director_loadMatrix(lua_State* tolua_S);
int lua_cc_base_Director_getWinSize(lua_State* tolua_S);
int lua_cc_base_Director_getVisibleOrigin(lua_State* tolua_S);
int lua_cc_base_Director_convertToUI(lua_State* tolua_S);
int lua_cc_base_Director_getMatrix(lua_State* tolua_S);
int lua_cc_base_Director_setClearColor(lua_State* tolua_S);
int lua_cc_base_Director_convertToGL(lua_State* tolua_S);
int lua_cc_base_Director_getRenderer(lua_State* tolua_S);
int lua_cc_base_Director_multiplyMatrix(lua_State* tolua_S);
int lua_cc_base_Director_getVisibleSize(lua_State* tolua_S);
int lua_cc_base_Director_getInstance(lua_State* tolua_S);
int lua_cc_base_Scheduler_constructor(lua_State* tolua_S);
int lua_cc_base_Scheduler_performFunctionInCocosThread(lua_State* tolua_S);
int lua_cc_base_AsyncTaskPool_constructor(lua_State* tolua_S);
int lua_cc_base_AsyncTaskPool_enqueue(lua_State* tolua_S);
int lua_cc_base_AsyncTaskPool_destroyInstance(lua_State* tolua_S);
int lua_cc_base_AsyncTaskPool_getInstance(lua_State* tolua_S);
int lua_cc_base_Speed_constructor(lua_State* tolua_S);
int lua_cc_base_Follow_constructor(lua_State* tolua_S);
int lua_cc_base_Follow_initWithTarget(lua_State* tolua_S);
int lua_cc_base_Follow_initWithTargetAndOffset(lua_State* tolua_S);
int lua_cc_base_Follow_create(lua_State* tolua_S);
int lua_cc_base_Follow_createWithOffset(lua_State* tolua_S);
int lua_cc_base_Image_constructor(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_constructor(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_getRect(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_setQuads(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_setQuad(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_setTriangles(lua_State* tolua_S);
int lua_cc_base_PolygonInfo_setRect(lua_State* tolua_S);
int lua_cc_base_AutoPolygon_constructor(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_constructor(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setAnchorPoint(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setOffsetInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getOriginalSizeInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setOriginalSize(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getCenterRect(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setRectInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getRect(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setCenterRectInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setOffset(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_initWithTextureFilename(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setRect(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_initWithTexture(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getOriginalSize(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getRectInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getOffset(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_setOriginalSizeInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getAnchorPoint(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_getOffsetInPixels(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_create(lua_State* tolua_S);
int lua_cc_base_SpriteFrame_createWithTexture(lua_State* tolua_S);
int lua_cc_base_AnimationFrame_constructor(lua_State* tolua_S);
int lua_cc_base_AnimationFrame_getUserInfo(lua_State* tolua_S);
int lua_cc_base_AnimationFrame_setUserInfo(lua_State* tolua_S);
int lua_cc_base_AnimationFrame_initWithSpriteFrame(lua_State* tolua_S);
int lua_cc_base_AnimationFrame_create(lua_State* tolua_S);
int lua_cc_base_Animation_constructor(lua_State* tolua_S);
int lua_cc_base_Animation_initWithAnimationFrames(lua_State* tolua_S);
int lua_cc_base_Animation_setFrames(lua_State* tolua_S);
int lua_cc_base_Animation_getFrames(lua_State* tolua_S);
int lua_cc_base_Animation_initWithSpriteFrames(lua_State* tolua_S);
int lua_cc_base_Animation_addSpriteFrameWithTexture(lua_State* tolua_S);
int lua_cc_base_Animation_create(lua_State* tolua_S);
int lua_cc_base_Animation_createWithSpriteFrames(lua_State* tolua_S);
int lua_cc_base_Sequence_constructor(lua_State* tolua_S);
int lua_cc_base_Sequence_init(lua_State* tolua_S);
int lua_cc_base_Repeat_constructor(lua_State* tolua_S);
int lua_cc_base_RepeatForever_constructor(lua_State* tolua_S);
int lua_cc_base_Spawn_constructor(lua_State* tolua_S);
int lua_cc_base_Spawn_init(lua_State* tolua_S);
int lua_cc_base_RotateTo_constructor(lua_State* tolua_S);
int lua_cc_base_RotateTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_RotateTo_create(lua_State* tolua_S);
int lua_cc_base_RotateBy_constructor(lua_State* tolua_S);
int lua_cc_base_RotateBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_RotateBy_create(lua_State* tolua_S);
int lua_cc_base_MoveBy_constructor(lua_State* tolua_S);
int lua_cc_base_MoveBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_MoveBy_create(lua_State* tolua_S);
int lua_cc_base_MoveTo_constructor(lua_State* tolua_S);
int lua_cc_base_MoveTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_MoveTo_create(lua_State* tolua_S);
int lua_cc_base_SkewTo_constructor(lua_State* tolua_S);
int lua_cc_base_SkewBy_constructor(lua_State* tolua_S);
int lua_cc_base_JumpBy_constructor(lua_State* tolua_S);
int lua_cc_base_JumpBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_JumpBy_create(lua_State* tolua_S);
int lua_cc_base_JumpTo_constructor(lua_State* tolua_S);
int lua_cc_base_JumpTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_JumpTo_create(lua_State* tolua_S);
int lua_cc_base_BezierBy_constructor(lua_State* tolua_S);
int lua_cc_base_BezierBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_BezierTo_constructor(lua_State* tolua_S);
int lua_cc_base_BezierTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_ScaleTo_constructor(lua_State* tolua_S);
int lua_cc_base_ScaleBy_constructor(lua_State* tolua_S);
int lua_cc_base_Blink_constructor(lua_State* tolua_S);
int lua_cc_base_FadeTo_constructor(lua_State* tolua_S);
int lua_cc_base_FadeTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_FadeTo_create(lua_State* tolua_S);
int lua_cc_base_FadeIn_constructor(lua_State* tolua_S);
int lua_cc_base_FadeOut_constructor(lua_State* tolua_S);
int lua_cc_base_TintTo_constructor(lua_State* tolua_S);
int lua_cc_base_TintTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_TintTo_create(lua_State* tolua_S);
int lua_cc_base_TintBy_constructor(lua_State* tolua_S);
int lua_cc_base_TintBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_TintBy_create(lua_State* tolua_S);
int lua_cc_base_DelayTime_constructor(lua_State* tolua_S);
int lua_cc_base_Animate_constructor(lua_State* tolua_S);
int lua_cc_base_Animate_getAnimation(lua_State* tolua_S);
int lua_cc_base_TargetedAction_constructor(lua_State* tolua_S);
int lua_cc_base_TargetedAction_getForcedTarget(lua_State* tolua_S);
int lua_cc_base_ActionFloat_constructor(lua_State* tolua_S);
int lua_cc_base_ActionFloat_initWithDuration(lua_State* tolua_S);
int lua_cc_base_ActionFloat_create(lua_State* tolua_S);
int lua_cc_base_Properties_getColor(lua_State* tolua_S);
int lua_cc_base_Properties_getNamespace(lua_State* tolua_S);
int lua_cc_base_Properties_getNextNamespace(lua_State* tolua_S);
int lua_cc_base_Properties_getVec3(lua_State* tolua_S);
int lua_cc_base_Properties_getVec2(lua_State* tolua_S);
int lua_cc_base_Properties_getVec4(lua_State* tolua_S);
int lua_cc_base_Properties_getQuaternionFromAxisAngle(lua_State* tolua_S);
int lua_cc_base_Properties_getPath(lua_State* tolua_S);
int lua_cc_base_Properties_getMat4(lua_State* tolua_S);
int lua_cc_base_Properties_parseColor(lua_State* tolua_S);
int lua_cc_base_Properties_parseVec3(lua_State* tolua_S);
int lua_cc_base_Properties_parseAxisAngle(lua_State* tolua_S);
int lua_cc_base_Properties_parseVec2(lua_State* tolua_S);
int lua_cc_base_Properties_parseVec4(lua_State* tolua_S);
int lua_cc_base_UserDefault_setLargeIntForKey(lua_State* tolua_S);
int lua_cc_base_UserDefault_getLargeIntForKey(lua_State* tolua_S);
int lua_cc_base_UserDefault_destroyInstance(lua_State* tolua_S);
int lua_cc_base_FileUtils_removeFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_listFilesRecursivelyAsync(lua_State* tolua_S);
int lua_cc_base_FileUtils_renameFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_getValueVectorFromFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_getSearchPaths(lua_State* tolua_S);
int lua_cc_base_FileUtils_writeToFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_getOriginalSearchPaths(lua_State* tolua_S);
int lua_cc_base_FileUtils_listFiles(lua_State* tolua_S);
int lua_cc_base_FileUtils_getValueMapFromFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_getFileSize(lua_State* tolua_S);
int lua_cc_base_FileUtils_getValueMapFromData(lua_State* tolua_S);
int lua_cc_base_FileUtils_removeDirectory(lua_State* tolua_S);
int lua_cc_base_FileUtils_setSearchPaths(lua_State* tolua_S);
int lua_cc_base_FileUtils_writeStringToFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_writeValueVectorToFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_isFileExist(lua_State* tolua_S);
int lua_cc_base_FileUtils_writeValueMapToFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_isDirectoryExist(lua_State* tolua_S);
int lua_cc_base_FileUtils_createDirectory(lua_State* tolua_S);
int lua_cc_base_FileUtils_listFilesAsync(lua_State* tolua_S);
int lua_cc_base_FileUtils_listFilesRecursively(lua_State* tolua_S);
int lua_cc_base_FileUtils_writeBinaryToFile(lua_State* tolua_S);
int lua_cc_base_FileUtils_getInstance(lua_State* tolua_S);
int lua_cc_base_FileUtils_destroyInstance(lua_State* tolua_S);
int lua_cc_base_EventCustom_constructor(lua_State* tolua_S);
int lua_cc_base_EventDispatcher_constructor(lua_State* tolua_S);
int lua_cc_base_EventDispatcher_dispatchCustomEvent(lua_State* tolua_S);
int lua_cc_base_EventFocus_constructor(lua_State* tolua_S);
int lua_cc_base_EventListenerAcceleration_constructor(lua_State* tolua_S);
int lua_cc_base_EventListenerAcceleration_init(lua_State* tolua_S);
int lua_cc_base_EventListenerFocus_constructor(lua_State* tolua_S);
int lua_cc_base_EventListenerKeyboard_constructor(lua_State* tolua_S);
int lua_cc_base_EventMouse_constructor(lua_State* tolua_S);
int lua_cc_base_EventMouse_getPreviousLocationInView(lua_State* tolua_S);
int lua_cc_base_EventMouse_getLocation(lua_State* tolua_S);
int lua_cc_base_EventMouse_getPreviousLocation(lua_State* tolua_S);
int lua_cc_base_EventMouse_getDelta(lua_State* tolua_S);
int lua_cc_base_EventMouse_getStartLocationInView(lua_State* tolua_S);
int lua_cc_base_EventMouse_getStartLocation(lua_State* tolua_S);
int lua_cc_base_EventMouse_getLocationInView(lua_State* tolua_S);
int lua_cc_base_EventListenerMouse_constructor(lua_State* tolua_S);
int lua_cc_base_EventListenerTouchOneByOne_constructor(lua_State* tolua_S);
int lua_cc_base_EventListenerTouchAllAtOnce_constructor(lua_State* tolua_S);
int lua_cc_base_ActionCamera_constructor(lua_State* tolua_S);
int lua_cc_base_ActionCamera_setEye(lua_State* tolua_S);
int lua_cc_base_ActionCamera_getEye(lua_State* tolua_S);
int lua_cc_base_ActionCamera_setUp(lua_State* tolua_S);
int lua_cc_base_ActionCamera_getCenter(lua_State* tolua_S);
int lua_cc_base_ActionCamera_setCenter(lua_State* tolua_S);
int lua_cc_base_ActionCamera_getUp(lua_State* tolua_S);
int lua_cc_base_OrbitCamera_constructor(lua_State* tolua_S);
int lua_cc_base_CardinalSplineTo_constructor(lua_State* tolua_S);
int lua_cc_base_CardinalSplineTo_getPoints(lua_State* tolua_S);
int lua_cc_base_CardinalSplineTo_updatePosition(lua_State* tolua_S);
int lua_cc_base_CardinalSplineTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_CardinalSplineBy_constructor(lua_State* tolua_S);
int lua_cc_base_CatmullRomTo_initWithDuration(lua_State* tolua_S);
int lua_cc_base_CatmullRomBy_initWithDuration(lua_State* tolua_S);
int lua_cc_base_EaseExponentialIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseExponentialOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseExponentialInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseSineIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseSineOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseSineInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBounceIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBounceOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBounceInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBackIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBackOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBackInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuadraticActionIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuadraticActionOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuadraticActionInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuarticActionIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuarticActionOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuarticActionInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuinticActionIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuinticActionOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseQuinticActionInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCircleActionIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCircleActionOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCircleActionInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCubicActionIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCubicActionOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseCubicActionInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseElasticIn_constructor(lua_State* tolua_S);
int lua_cc_base_EaseElasticOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseElasticInOut_constructor(lua_State* tolua_S);
int lua_cc_base_EaseBezierAction_constructor(lua_State* tolua_S);
int lua_cc_base_Show_constructor(lua_State* tolua_S);
int lua_cc_base_Hide_constructor(lua_State* tolua_S);
int lua_cc_base_ToggleVisibility_constructor(lua_State* tolua_S);
int lua_cc_base_RemoveSelf_constructor(lua_State* tolua_S);
int lua_cc_base_FlipX_constructor(lua_State* tolua_S);
int lua_cc_base_FlipY_constructor(lua_State* tolua_S);
int lua_cc_base_Place_constructor(lua_State* tolua_S);
int lua_cc_base_Place_initWithPosition(lua_State* tolua_S);
int lua_cc_base_Place_create(lua_State* tolua_S);
int lua_cc_base_CallFunc_constructor(lua_State* tolua_S);
int lua_cc_base_GridAction_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Grid3DAction_getGridRect(lua_State* tolua_S);
int lua_cc_base_StopGrid_constructor(lua_State* tolua_S);
int lua_cc_base_ReuseGrid_constructor(lua_State* tolua_S);
int lua_cc_base_Waves3D_constructor(lua_State* tolua_S);
int lua_cc_base_Waves3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Waves3D_create(lua_State* tolua_S);
int lua_cc_base_FlipX3D_constructor(lua_State* tolua_S);
int lua_cc_base_FlipX3D_initWithSize(lua_State* tolua_S);
int lua_cc_base_FlipY3D_constructor(lua_State* tolua_S);
int lua_cc_base_Lens3D_constructor(lua_State* tolua_S);
int lua_cc_base_Lens3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Lens3D_setPosition(lua_State* tolua_S);
int lua_cc_base_Lens3D_getPosition(lua_State* tolua_S);
int lua_cc_base_Lens3D_create(lua_State* tolua_S);
int lua_cc_base_Ripple3D_constructor(lua_State* tolua_S);
int lua_cc_base_Ripple3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Ripple3D_setPosition(lua_State* tolua_S);
int lua_cc_base_Ripple3D_getPosition(lua_State* tolua_S);
int lua_cc_base_Ripple3D_create(lua_State* tolua_S);
int lua_cc_base_Shaky3D_constructor(lua_State* tolua_S);
int lua_cc_base_Shaky3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Shaky3D_create(lua_State* tolua_S);
int lua_cc_base_Liquid_constructor(lua_State* tolua_S);
int lua_cc_base_Liquid_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Liquid_create(lua_State* tolua_S);
int lua_cc_base_Waves_constructor(lua_State* tolua_S);
int lua_cc_base_Waves_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Waves_create(lua_State* tolua_S);
int lua_cc_base_Twirl_constructor(lua_State* tolua_S);
int lua_cc_base_Twirl_initWithDuration(lua_State* tolua_S);
int lua_cc_base_Twirl_setPosition(lua_State* tolua_S);
int lua_cc_base_Twirl_getPosition(lua_State* tolua_S);
int lua_cc_base_Twirl_create(lua_State* tolua_S);
int lua_cc_base_ActionManager_constructor(lua_State* tolua_S);
int lua_cc_base_ActionManager_resumeTargets(lua_State* tolua_S);
int lua_cc_base_ActionManager_pauseAllRunningActions(lua_State* tolua_S);
int lua_cc_base_PageTurn3D_create(lua_State* tolua_S);
int lua_cc_base_ProgressTo_constructor(lua_State* tolua_S);
int lua_cc_base_ProgressFromTo_constructor(lua_State* tolua_S);
int lua_cc_base_ShakyTiles3D_constructor(lua_State* tolua_S);
int lua_cc_base_ShakyTiles3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_ShakyTiles3D_create(lua_State* tolua_S);
int lua_cc_base_ShatteredTiles3D_constructor(lua_State* tolua_S);
int lua_cc_base_ShatteredTiles3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_ShatteredTiles3D_create(lua_State* tolua_S);
int lua_cc_base_ShuffleTiles_constructor(lua_State* tolua_S);
int lua_cc_base_ShuffleTiles_initWithDuration(lua_State* tolua_S);
int lua_cc_base_ShuffleTiles_getDelta(lua_State* tolua_S);
int lua_cc_base_ShuffleTiles_create(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_constructor(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_turnOnTile(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_turnOffTile(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_transformTile(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_testFunc(lua_State* tolua_S);
int lua_cc_base_FadeOutTRTiles_create(lua_State* tolua_S);
int lua_cc_base_FadeOutBLTiles_constructor(lua_State* tolua_S);
int lua_cc_base_FadeOutBLTiles_create(lua_State* tolua_S);
int lua_cc_base_FadeOutUpTiles_constructor(lua_State* tolua_S);
int lua_cc_base_FadeOutUpTiles_create(lua_State* tolua_S);
int lua_cc_base_FadeOutDownTiles_constructor(lua_State* tolua_S);
int lua_cc_base_FadeOutDownTiles_create(lua_State* tolua_S);
int lua_cc_base_TurnOffTiles_constructor(lua_State* tolua_S);
int lua_cc_base_TurnOffTiles_turnOnTile(lua_State* tolua_S);
int lua_cc_base_TurnOffTiles_turnOffTile(lua_State* tolua_S);
int lua_cc_base_TurnOffTiles_initWithDuration(lua_State* tolua_S);
int lua_cc_base_TurnOffTiles_create(lua_State* tolua_S);
int lua_cc_base_WavesTiles3D_constructor(lua_State* tolua_S);
int lua_cc_base_WavesTiles3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_WavesTiles3D_create(lua_State* tolua_S);
int lua_cc_base_JumpTiles3D_constructor(lua_State* tolua_S);
int lua_cc_base_JumpTiles3D_initWithDuration(lua_State* tolua_S);
int lua_cc_base_JumpTiles3D_create(lua_State* tolua_S);
int lua_cc_base_SplitRows_constructor(lua_State* tolua_S);
int lua_cc_base_SplitCols_constructor(lua_State* tolua_S);
int lua_cc_base_AtlasNode_constructor(lua_State* tolua_S);
int lua_cc_base_AtlasNode_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_AtlasNode_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_AtlasNode_setTextureAtlas(lua_State* tolua_S);
int lua_cc_base_AtlasNode_getTexture(lua_State* tolua_S);
int lua_cc_base_AtlasNode_getTextureAtlas(lua_State* tolua_S);
int lua_cc_base_AtlasNode_setTexture(lua_State* tolua_S);
int lua_cc_base_AtlasNode_setQuadsToDraw(lua_State* tolua_S);
int lua_cc_base_ClippingNode_init(lua_State* tolua_S);
int lua_cc_base_ClippingRectangleNode_getClippingRegion(lua_State* tolua_S);
int lua_cc_base_ClippingRectangleNode_setClippingRegion(lua_State* tolua_S);
int lua_cc_base_ClippingRectangleNode_create(lua_State* tolua_S);
int lua_cc_base_DrawNode_constructor(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawLine(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawRect(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawSolidCircle(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawDot(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawSegment(lua_State* tolua_S);
int lua_cc_base_DrawNode_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawCircle(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawQuadBezier(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawTriangle(lua_State* tolua_S);
int lua_cc_base_DrawNode_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawSolidRect(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawPoint(lua_State* tolua_S);
int lua_cc_base_DrawNode_drawCubicBezier(lua_State* tolua_S);
int lua_cc_base_Label_enableShadow(lua_State* tolua_S);
int lua_cc_base_Label_getString(lua_State* tolua_S);
int lua_cc_base_Label_setTTFConfig(lua_State* tolua_S);
int lua_cc_base_Label_getTextColor(lua_State* tolua_S);
int lua_cc_base_Label_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_Label_getShadowOffset(lua_State* tolua_S);
int lua_cc_base_Label_setString(lua_State* tolua_S);
int lua_cc_base_Label_setBMFontFilePath(lua_State* tolua_S);
int lua_cc_base_Label_initWithTTF(lua_State* tolua_S);
int lua_cc_base_Label_getFontAtlas(lua_State* tolua_S);
int lua_cc_base_Label_enableOutline(lua_State* tolua_S);
int lua_cc_base_Label_getEffectColor(lua_State* tolua_S);
int lua_cc_base_Label_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_Label_setCharMap(lua_State* tolua_S);
int lua_cc_base_Label_getDimensions(lua_State* tolua_S);
int lua_cc_base_Label_getShadowColor(lua_State* tolua_S);
int lua_cc_base_Label_getTTFConfig(lua_State* tolua_S);
int lua_cc_base_Label_setTextColor(lua_State* tolua_S);
int lua_cc_base_Label_enableGlow(lua_State* tolua_S);
int lua_cc_base_Label_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_Label_createWithBMFont(lua_State* tolua_S);
int lua_cc_base_Label_createWithCharMap(lua_State* tolua_S);
int lua_cc_base_Label_createWithSystemFont(lua_State* tolua_S);
int lua_cc_base_LabelAtlas_constructor(lua_State* tolua_S);
int lua_cc_base_LabelAtlas_setString(lua_State* tolua_S);
int lua_cc_base_LabelAtlas_initWithString(lua_State* tolua_S);
int lua_cc_base_LabelAtlas_getString(lua_State* tolua_S);
int lua_cc_base_LabelAtlas_create(lua_State* tolua_S);
int lua_cc_base_Sprite_constructor(lua_State* tolua_S);
int lua_cc_base_Sprite_setSpriteFrame(lua_State* tolua_S);
int lua_cc_base_Sprite_setTexture(lua_State* tolua_S);
int lua_cc_base_Sprite_getTexture(lua_State* tolua_S);
int lua_cc_base_Sprite_getOffsetPosition(lua_State* tolua_S);
int lua_cc_base_Sprite_getCenterRect(lua_State* tolua_S);
int lua_cc_base_Sprite_setCenterRectNormalized(lua_State* tolua_S);
int lua_cc_base_Sprite_setTextureRect(lua_State* tolua_S);
int lua_cc_base_Sprite_setTextureAtlas(lua_State* tolua_S);
int lua_cc_base_Sprite_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_Sprite_setCenterRect(lua_State* tolua_S);
int lua_cc_base_Sprite_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_Sprite_getCenterRectNormalized(lua_State* tolua_S);
int lua_cc_base_Sprite_initWithTexture(lua_State* tolua_S);
int lua_cc_base_Sprite_getTextureRect(lua_State* tolua_S);
int lua_cc_base_Sprite_initWithFile(lua_State* tolua_S);
int lua_cc_base_Sprite_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_Sprite_getTextureAtlas(lua_State* tolua_S);
int lua_cc_base_Sprite_setVertexRect(lua_State* tolua_S);
int lua_cc_base_Sprite_createWithTexture(lua_State* tolua_S);
int lua_cc_base_LayerColor_constructor(lua_State* tolua_S);
int lua_cc_base_LayerColor_initWithColor(lua_State* tolua_S);
int lua_cc_base_LayerColor_create(lua_State* tolua_S);
int lua_cc_base_LayerGradient_constructor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_getStartColor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_setVector(lua_State* tolua_S);
int lua_cc_base_LayerGradient_setStartOpacity(lua_State* tolua_S);
int lua_cc_base_LayerGradient_setEndOpacity(lua_State* tolua_S);
int lua_cc_base_LayerGradient_getVector(lua_State* tolua_S);
int lua_cc_base_LayerGradient_setEndColor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_initWithColor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_getEndColor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_setStartColor(lua_State* tolua_S);
int lua_cc_base_LayerGradient_create(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_constructor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getStartColor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getStartColor3B(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setCenter(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getEndColor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setStartOpacity(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getCenter(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setEndOpacity(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_initWithColor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setEndColor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_getEndColor3B(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setStartColor(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_LayerRadialGradient_create(lua_State* tolua_S);
int lua_cc_base_LayerMultiplex_constructor(lua_State* tolua_S);
int lua_cc_base_LayerMultiplex_initWithArray(lua_State* tolua_S);
int lua_cc_base_MenuItem_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItem_rect(lua_State* tolua_S);
int lua_cc_base_MenuItemLabel_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemLabel_getDisabledColor(lua_State* tolua_S);
int lua_cc_base_MenuItemLabel_initWithLabel(lua_State* tolua_S);
int lua_cc_base_MenuItemLabel_setDisabledColor(lua_State* tolua_S);
int lua_cc_base_MenuItemAtlasFont_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemAtlasFont_initWithString(lua_State* tolua_S);
int lua_cc_base_MenuItemFont_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemFont_initWithString(lua_State* tolua_S);
int lua_cc_base_MenuItemSprite_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemSprite_setEnabled(lua_State* tolua_S);
int lua_cc_base_MenuItemSprite_selected(lua_State* tolua_S);
int lua_cc_base_MenuItemSprite_initWithNormalSprite(lua_State* tolua_S);
int lua_cc_base_MenuItemSprite_unselected(lua_State* tolua_S);
int lua_cc_base_MenuItemImage_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemImage_init(lua_State* tolua_S);
int lua_cc_base_MenuItemImage_initWithNormalImage(lua_State* tolua_S);
int lua_cc_base_MenuItemToggle_constructor(lua_State* tolua_S);
int lua_cc_base_MenuItemToggle_setSubItems(lua_State* tolua_S);
int lua_cc_base_Menu_constructor(lua_State* tolua_S);
int lua_cc_base_Menu_initWithArray(lua_State* tolua_S);
int lua_cc_base_MotionStreak_constructor(lua_State* tolua_S);
int lua_cc_base_MotionStreak_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_MotionStreak_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_MotionStreak_tintWithColor(lua_State* tolua_S);
int lua_cc_base_MotionStreak_getTexture(lua_State* tolua_S);
int lua_cc_base_MotionStreak_setTexture(lua_State* tolua_S);
int lua_cc_base_MotionStreak_initWithFade(lua_State* tolua_S);
int lua_cc_base_MotionStreak_create(lua_State* tolua_S);
int lua_cc_base_NodeGrid_constructor(lua_State* tolua_S);
int lua_cc_base_NodeGrid_setGridRect(lua_State* tolua_S);
int lua_cc_base_NodeGrid_getGrid(lua_State* tolua_S);
int lua_cc_base_NodeGrid_getGridRect(lua_State* tolua_S);
int lua_cc_base_NodeGrid_create(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_setTexture(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_getTexture(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_setTextureAtlas(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_getTextureAtlas(lua_State* tolua_S);
int lua_cc_base_ParticleBatchNode_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_SpriteFrameCache_getSpriteSheetLoader(lua_State* tolua_S);
int lua_cc_base_SpriteFrameCache_addSpriteFramesWithFile(lua_State* tolua_S);
int lua_cc_base_SpriteFrameCache_getSpriteFrameByName(lua_State* tolua_S);
int lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset(lua_State* tolua_S);
int lua_cc_base_ParticleData_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleEmissionMaskCache_bakeEmissionMask(lua_State* tolua_S);
int lua_cc_base_ParticleEmissionMaskCache_getEmissionMask(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setAnimationDescriptor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getTexture(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getStartColor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setPosVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setHSVVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getGravity(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setEndColor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_addAnimationIndex(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setTexture(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getPosVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getSourcePosition(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setEndColorVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setEmissionShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setRectForUndefinedIndices(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getHSVVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getHSV(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setSourcePosition(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_stop(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_start(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_addEmissionShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setStartColor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setGravity(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getEndColorVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getEndColor(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setHSV(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setStartColorVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_initWithDictionary(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getStartColorVar(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createRectTorusShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createTorusShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createConeShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createPointShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createCircleShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createMaskShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createRectShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_getAllParticleSystems(lua_State* tolua_S);
int lua_cc_base_ParticleSystem_createConeTorusShape(lua_State* tolua_S);
int lua_cc_base_ParticleSystemQuad_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSystemQuad_setTextureWithRect(lua_State* tolua_S);
int lua_cc_base_ParticleSystemQuad_create(lua_State* tolua_S);
int lua_cc_base_ParticleFire_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleFireworks_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleFireworks_init(lua_State* tolua_S);
int lua_cc_base_ParticleFireworks_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleSun_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSun_init(lua_State* tolua_S);
int lua_cc_base_ParticleSun_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleGalaxy_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleGalaxy_init(lua_State* tolua_S);
int lua_cc_base_ParticleGalaxy_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleFlower_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleFlower_init(lua_State* tolua_S);
int lua_cc_base_ParticleFlower_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleMeteor_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleMeteor_init(lua_State* tolua_S);
int lua_cc_base_ParticleMeteor_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleSpiral_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSpiral_init(lua_State* tolua_S);
int lua_cc_base_ParticleSpiral_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleExplosion_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleExplosion_init(lua_State* tolua_S);
int lua_cc_base_ParticleExplosion_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleSmoke_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSmoke_init(lua_State* tolua_S);
int lua_cc_base_ParticleSmoke_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleSnow_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleSnow_init(lua_State* tolua_S);
int lua_cc_base_ParticleSnow_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ParticleRain_constructor(lua_State* tolua_S);
int lua_cc_base_ParticleRain_init(lua_State* tolua_S);
int lua_cc_base_ParticleRain_initWithTotalParticles(lua_State* tolua_S);
int lua_cc_base_ProgressTimer_constructor(lua_State* tolua_S);
int lua_cc_base_ProgressTimer_setBarChangeRate(lua_State* tolua_S);
int lua_cc_base_ProgressTimer_setMidpoint(lua_State* tolua_S);
int lua_cc_base_ProgressTimer_getBarChangeRate(lua_State* tolua_S);
int lua_cc_base_ProgressTimer_getMidpoint(lua_State* tolua_S);
int lua_cc_base_ProtectedNode_constructor(lua_State* tolua_S);
int lua_cc_base_ProtectedNode_disableCascadeColor(lua_State* tolua_S);
int lua_cc_base_ProtectedNode_disableCascadeOpacity(lua_State* tolua_S);
int lua_cc_base_RenderTexture_constructor(lua_State* tolua_S);
int lua_cc_base_RenderTexture_setVirtualViewport(lua_State* tolua_S);
int lua_cc_base_RenderTexture_getRenderTarget(lua_State* tolua_S);
int lua_cc_base_RenderTexture_saveToFileAsNonPMA(lua_State* tolua_S);
int lua_cc_base_RenderTexture_saveToFile(lua_State* tolua_S);
int lua_cc_base_RenderTexture_setClearColor(lua_State* tolua_S);
int lua_cc_base_RenderTexture_getClearColor(lua_State* tolua_S);
int lua_cc_base_RenderTexture_initWithWidthAndHeight(lua_State* tolua_S);
int lua_cc_base_RenderTexture_create(lua_State* tolua_S);
int lua_cc_base_TransitionScene_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSceneOriented_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionRotoZoom_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionJumpZoom_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionMoveInL_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionMoveInL_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionMoveInR_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionMoveInT_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionMoveInB_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSlideInL_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSlideInL_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionSlideInR_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSlideInB_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSlideInT_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionShrinkGrow_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionShrinkGrow_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionFlipX_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFlipY_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFlipAngular_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionZoomFlipX_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionZoomFlipY_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionZoomFlipAngular_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFade_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFade_initWithDuration(lua_State* tolua_S);
int lua_cc_base_TransitionFade_create(lua_State* tolua_S);
int lua_cc_base_TransitionCrossFade_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionTurnOffTiles_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionTurnOffTiles_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionSplitCols_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionSplitCols_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionSplitRows_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFadeTR_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFadeTR_easeActionWithAction(lua_State* tolua_S);
int lua_cc_base_TransitionFadeTR_actionWithSize(lua_State* tolua_S);
int lua_cc_base_TransitionFadeBL_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFadeUp_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionFadeDown_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionPageTurn_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionPageTurn_actionWithSize(lua_State* tolua_S);
int lua_cc_base_TransitionProgress_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressRadialCCW_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressRadialCW_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressHorizontal_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressVertical_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressInOut_constructor(lua_State* tolua_S);
int lua_cc_base_TransitionProgressOutIn_constructor(lua_State* tolua_S);
int lua_cc_base_Camera_constructor(lua_State* tolua_S);
int lua_cc_base_Camera_getViewProjectionMatrix(lua_State* tolua_S);
int lua_cc_base_Camera_lookAt(lua_State* tolua_S);
int lua_cc_base_Camera_getProjectionMatrix(lua_State* tolua_S);
int lua_cc_base_Camera_setAdditionalProjection(lua_State* tolua_S);
int lua_cc_base_Camera_isVisibleInFrustum(lua_State* tolua_S);
int lua_cc_base_Camera_setDepth(lua_State* tolua_S);
int lua_cc_base_Camera_projectGL(lua_State* tolua_S);
int lua_cc_base_Camera_getViewMatrix(lua_State* tolua_S);
int lua_cc_base_Camera_project(lua_State* tolua_S);
int lua_cc_base_Camera_getDepthInView(lua_State* tolua_S);
int lua_cc_base_Camera_getVisitingCamera(lua_State* tolua_S);
int lua_cc_base_Camera_getDefaultViewport(lua_State* tolua_S);
int lua_cc_base_Camera_setDefaultViewport(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundBrush_constructor(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundBrush_createColorBrush(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundDepthBrush_constructor(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundColorBrush_constructor(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundColorBrush_setColor(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundColorBrush_create(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundSkyBoxBrush_constructor(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture(lua_State* tolua_S);
int lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture(lua_State* tolua_S);
int lua_cc_base_GridBase_setGridSize(lua_State* tolua_S);
int lua_cc_base_GridBase_setGridRect(lua_State* tolua_S);
int lua_cc_base_GridBase_getGridRect(lua_State* tolua_S);
int lua_cc_base_GridBase_getGridSize(lua_State* tolua_S);
int lua_cc_base_GridBase_getStep(lua_State* tolua_S);
int lua_cc_base_GridBase_setStep(lua_State* tolua_S);
int lua_cc_base_GridBase_initWithSize(lua_State* tolua_S);
int lua_cc_base_Grid3D_constructor(lua_State* tolua_S);
int lua_cc_base_Grid3D_create(lua_State* tolua_S);
int lua_cc_base_TiledGrid3D_create(lua_State* tolua_S);
int lua_cc_base_DirectionLight_constructor(lua_State* tolua_S);
int lua_cc_base_DirectionLight_getDirection(lua_State* tolua_S);
int lua_cc_base_DirectionLight_getDirectionInWorld(lua_State* tolua_S);
int lua_cc_base_DirectionLight_setDirection(lua_State* tolua_S);
int lua_cc_base_DirectionLight_create(lua_State* tolua_S);
int lua_cc_base_PointLight_constructor(lua_State* tolua_S);
int lua_cc_base_PointLight_create(lua_State* tolua_S);
int lua_cc_base_SpotLight_constructor(lua_State* tolua_S);
int lua_cc_base_SpotLight_setDirection(lua_State* tolua_S);
int lua_cc_base_SpotLight_getDirection(lua_State* tolua_S);
int lua_cc_base_SpotLight_getDirectionInWorld(lua_State* tolua_S);
int lua_cc_base_SpotLight_create(lua_State* tolua_S);
int lua_cc_base_AmbientLight_constructor(lua_State* tolua_S);
int lua_cc_base_AmbientLight_create(lua_State* tolua_S);
int lua_cc_base_RenderState_bindPass(lua_State* tolua_S);
int lua_cc_base_Technique_getPasses(lua_State* tolua_S);
int lua_cc_base_Technique_getPassByIndex(lua_State* tolua_S);
int lua_cc_base_Material_draw(lua_State* tolua_S);
int lua_cc_base_Material_getTechniqueByIndex(lua_State* tolua_S);
int lua_cc_base_Material_getTechniques(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformPointLightPosition(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformDirLightDir(lua_State* tolua_S);
int lua_cc_base_Pass_getVertexAttributeBinding(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightOuterAngleCos(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightDir(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformMatrixPalette(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightRangeInverse(lua_State* tolua_S);
int lua_cc_base_Pass_draw(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformPointLightRangeInverse(lua_State* tolua_S);
int lua_cc_base_Pass_updateMVPUniform(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightColor(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformAmbientLigthColor(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformDirLightColor(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightPosition(lua_State* tolua_S);
int lua_cc_base_Pass_setVertexAttribBinding(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformSpotLightInnerAngleCos(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformColor(lua_State* tolua_S);
int lua_cc_base_Pass_setUniformPointLightColor(lua_State* tolua_S);
int lua_cc_base_Renderer_constructor(lua_State* tolua_S);
int lua_cc_base_Renderer_setDepthStencilDesc(lua_State* tolua_S);
int lua_cc_base_Renderer_getViewport(lua_State* tolua_S);
int lua_cc_base_Renderer_addCallbackCommand(lua_State* tolua_S);
int lua_cc_base_Renderer_getRenderTarget(lua_State* tolua_S);
int lua_cc_base_Renderer_addCommand(lua_State* tolua_S);
int lua_cc_base_Renderer_addDrawnVertices(lua_State* tolua_S);
int lua_cc_base_Renderer_getDepthStencilDesc(lua_State* tolua_S);
int lua_cc_base_Renderer_getScissorRect(lua_State* tolua_S);
int lua_cc_base_Renderer_addDrawnBatches(lua_State* tolua_S);
int lua_cc_base_Renderer_nextCallbackCommand(lua_State* tolua_S);
int lua_cc_base_Renderer_checkVisibility(lua_State* tolua_S);
int lua_cc_base_Renderer_getNextGroupCommand(lua_State* tolua_S);
int lua_cc_base_Renderer_getClearColor(lua_State* tolua_S);
int lua_cc_base_Renderer_getOffscreenRenderTarget(lua_State* tolua_S);
int lua_cc_base_Renderer_clear(lua_State* tolua_S);
int lua_cc_base_Renderer_setRenderTarget(lua_State* tolua_S);
int lua_cc_base_Renderer_readPixels(lua_State* tolua_S);
int lua_cc_base_Renderer_getDefaultRenderTarget(lua_State* tolua_S);
int lua_cc_base_TextureCache_constructor(lua_State* tolua_S);
int lua_cc_base_TextureCache_addImage(lua_State* tolua_S);
int lua_cc_base_Application_getTargetPlatform(lua_State* tolua_S);
int lua_cc_base_Application_getCurrentLanguage(lua_State* tolua_S);
int lua_cc_base_Application_getCurrentLanguageCode(lua_State* tolua_S);
int lua_cc_base_Application_openURL(lua_State* tolua_S);
int lua_cc_base_Application_getVersion(lua_State* tolua_S);
int lua_cc_base_Application_setAnimationInterval(lua_State* tolua_S);
int lua_cc_base_Application_getInstance(lua_State* tolua_S);
int lua_cc_base_AnimationCache_constructor(lua_State* tolua_S);
int lua_cc_base_AnimationCache_addAnimationsWithDictionary(lua_State* tolua_S);
int lua_cc_base_AnimationCache_addAnimationsWithFile(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_constructor(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_getTexture(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_setTexture(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_removeChildAtIndex(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_initWithTexture(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_setTextureAtlas(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_reserveCapacity(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_insertQuadFromSprite(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_initWithFile(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_rebuildIndexInOrder(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_getTextureAtlas(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_create(lua_State* tolua_S);
int lua_cc_base_SpriteBatchNode_createWithTexture(lua_State* tolua_S);
int lua_cc_base_ParallaxNode_constructor(lua_State* tolua_S);
int lua_cc_base_ParallaxNode_addChild(lua_State* tolua_S);
int lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_constructor(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_setPositionOffset(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_getProperty(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_getPositionOffset(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_getObject(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_getObjects(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_getProperties(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_setProperties(lua_State* tolua_S);
int lua_cc_base_TMXObjectGroup_setObjects(lua_State* tolua_S);
int lua_cc_base_TMXLayerInfo_constructor(lua_State* tolua_S);
int lua_cc_base_TMXLayerInfo_setProperties(lua_State* tolua_S);
int lua_cc_base_TMXLayerInfo_getProperties(lua_State* tolua_S);
int lua_cc_base_TMXTilesetInfo_constructor(lua_State* tolua_S);
int lua_cc_base_TMXTilesetInfo_getRectForGID(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_constructor(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setTileSize(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setObjectGroups(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setLayers(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getLayers(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getTilesets(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getTileSize(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getTileProperties(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getObjectGroups(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setProperties(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setTileProperties(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setMapSize(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getMapSize(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_setTilesets(lua_State* tolua_S);
int lua_cc_base_TMXMapInfo_getProperties(lua_State* tolua_S);
int lua_cc_base_TileMapAtlas_constructor(lua_State* tolua_S);
int lua_cc_base_TileMapAtlas_getTileAt(lua_State* tolua_S);
int lua_cc_base_TileMapAtlas_setTile(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_constructor(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getAnimTileCoord(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getPositionAt(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getLayerSize(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_setMapTileSize(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_setProperties(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_removeTileAt(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getProperties(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_setupTileSprite(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_setTileGID(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getMapTileSize(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getProperty(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_setLayerSize(lua_State* tolua_S);
int lua_cc_base_FastTMXLayer_getTileAt(lua_State* tolua_S);
int lua_cc_base_TMXTileAnimTask_constructor(lua_State* tolua_S);
int lua_cc_base_TMXTileAnimTask_create(lua_State* tolua_S);
int lua_cc_base_TMXTileAnimManager_constructor(lua_State* tolua_S);
int lua_cc_base_TMXTileAnimManager_getTasks(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_constructor(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_setObjectGroups(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getProperty(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_setMapSize(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getObjectGroups(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getTileSize(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getMapSize(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getProperties(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_getPropertiesForGID(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_setTileSize(lua_State* tolua_S);
int lua_cc_base_FastTMXTiledMap_setProperties(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_constructor(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_setTexture(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_getTexture(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_tintWithColor(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_getSweepAxis(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_setBlendFunc(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_getBlendFunc(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_initWithFade(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_setSweepAxis(lua_State* tolua_S);
int lua_cc_base_MotionStreak3D_create(lua_State* tolua_S);
int lua_cc_base_ComponentLua_constructor(lua_State* tolua_S);
int lua_cc_base_ComponentLua_getScriptObject(lua_State* tolua_S);
int lua_cc_base_ComponentLua_update(lua_State* tolua_S);

int lua_cc_base_GLViewImpl_createWithRect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLViewImpl",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::Rect arg1;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.GLViewImpl:createWithRect");
        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.GLViewImpl:createWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLViewImpl_createWithRect'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::GLViewImpl::createWithRect(arg0, arg1);
        object_to_luaval<cocos2d::GLViewImpl>(tolua_S, "cc.GLViewImpl",(cocos2d::GLViewImpl*)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::Rect arg1;
        double arg2;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.GLViewImpl:createWithRect");
        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.GLViewImpl:createWithRect");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.GLViewImpl:createWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLViewImpl_createWithRect'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::GLViewImpl::createWithRect(arg0, arg1, arg2);
        object_to_luaval<cocos2d::GLViewImpl>(tolua_S, "cc.GLViewImpl",(cocos2d::GLViewImpl*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLViewImpl:createWithRect",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLViewImpl_createWithRect'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_GLViewImpl_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLViewImpl",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.GLViewImpl:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLViewImpl_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::GLViewImpl::create(arg0);
        object_to_luaval<cocos2d::GLViewImpl>(tolua_S, "cc.GLViewImpl",(cocos2d::GLViewImpl*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLViewImpl:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLViewImpl_create'.",&tolua_err);
#endif
    return 0;
}

int register_all_cc_base_retained(lua_State* L)
{
    tolua_module(L,"cc",0); tolua_beginmodule(L,"cc");
    lua_register_cc_base_ShaderCache(L);

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    lua_register_cc_base_EventListenerController(L);

#endif

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    lua_register_cc_base_EventController(L);

#endif
    tolua_endmodule(L);
    luaL_getmetatable(L,"cc.Console");
    if (lua_istable(L,-1)) {
        tolua_function(L,"setCommandSeparator",lua_cc_base_Console_setCommandSeparator);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerCustom");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerCustom_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Texture2D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Texture2D_constructor);
        tolua_function(L,"updateWithMipmaps",lua_cc_base_Texture2D_updateWithMipmaps);
        tolua_function(L,"initWithString",lua_cc_base_Texture2D_initWithString);
        tolua_function(L,"drawInRect",lua_cc_base_Texture2D_drawInRect);
        tolua_function(L,"getContentSize",lua_cc_base_Texture2D_getContentSize);
        tolua_function(L,"updateTextureDescriptor",lua_cc_base_Texture2D_updateTextureDescriptor);
        tolua_function(L,"getContentSizeInPixels",lua_cc_base_Texture2D_getContentSizeInPixels);
        tolua_function(L,"drawAtPoint",lua_cc_base_Texture2D_drawAtPoint);
        tolua_function(L,"updateWithSubData",lua_cc_base_Texture2D_updateWithSubData);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Touch");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Touch_constructor);
        tolua_function(L,"getPreviousLocationInView",lua_cc_base_Touch_getPreviousLocationInView);
        tolua_function(L,"getLocation",lua_cc_base_Touch_getLocation);
        tolua_function(L,"getDelta",lua_cc_base_Touch_getDelta);
        tolua_function(L,"getStartLocationInView",lua_cc_base_Touch_getStartLocationInView);
        tolua_function(L,"getStartLocation",lua_cc_base_Touch_getStartLocation);
        tolua_function(L,"getId",lua_cc_base_Touch_getID);
        tolua_function(L,"getLocationInView",lua_cc_base_Touch_getLocationInView);
        tolua_function(L,"getPreviousLocation",lua_cc_base_Touch_getPreviousLocation);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Event");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Event_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventTouch");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventTouch_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventKeyboard");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventKeyboard_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Node");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Node_constructor);
        tolua_function(L,"addChild",lua_cc_base_Node_addChild);
        tolua_function(L,"removeComponent",lua_cc_base_Node_removeComponent);
#if CC_USE_PHYSICS
        tolua_function(L,"setPhysicsBody",lua_cc_base_Node_setPhysicsBody);
#endif
        tolua_function(L,"getOnExitTransitionDidStartCallback",lua_cc_base_Node_getOnExitTransitionDidStartCallback);
        tolua_function(L,"getChildren",lua_cc_base_Node_getChildren);
        tolua_function(L,"setOnExitCallback",lua_cc_base_Node_setOnExitCallback);
        tolua_function(L,"convertToWorldSpaceAR",lua_cc_base_Node_convertToWorldSpaceAR);
        tolua_function(L,"updateDisplayedOpacity",lua_cc_base_Node_updateDisplayedOpacity);
        tolua_function(L,"setCameraMask",lua_cc_base_Node_setCameraMask);
        tolua_function(L,"getNodeToWorldAffineTransform",lua_cc_base_Node_getNodeToWorldAffineTransform);
        tolua_function(L,"getNodeToWorldTransform",lua_cc_base_Node_getNodeToWorldTransform);
        tolua_function(L,"getPosition3D",lua_cc_base_Node_getPosition3D);
        tolua_function(L,"convertToWorldSpace",lua_cc_base_Node_convertToWorldSpace);
        tolua_function(L,"setOnEnterCallback",lua_cc_base_Node_setOnEnterCallback);
        tolua_function(L,"setNormalizedPosition",lua_cc_base_Node_setNormalizedPosition);
        tolua_function(L,"convertTouchToNodeSpace",lua_cc_base_Node_convertTouchToNodeSpace);
        tolua_function(L,"removeAllChildren",lua_cc_base_Node_removeAllChildrenWithCleanup);
        tolua_function(L,"setOnEnterTransitionDidFinishCallback",lua_cc_base_Node_setOnEnterTransitionDidFinishCallback);
        tolua_function(L,"setProgramState",lua_cc_base_Node_setProgramState);
        tolua_function(L,"getNodeToParentAffineTransform",lua_cc_base_Node_getNodeToParentAffineTransform);
        tolua_function(L,"getRotation3D",lua_cc_base_Node_getRotation3D);
        tolua_function(L,"getNodeToParentTransform",lua_cc_base_Node_getNodeToParentTransform);
        tolua_function(L,"convertTouchToNodeSpaceAR",lua_cc_base_Node_convertTouchToNodeSpaceAR);
        tolua_function(L,"convertToNodeSpace",lua_cc_base_Node_convertToNodeSpace);
        tolua_function(L,"setPositionNormalized",lua_cc_base_Node_setPositionNormalized);
        tolua_function(L,"setPosition",lua_cc_base_Node_setPosition);
        tolua_function(L,"setRotation3D",lua_cc_base_Node_setRotation3D);
        tolua_function(L,"setNodeToParentTransform",lua_cc_base_Node_setNodeToParentTransform);
        tolua_function(L,"getAnchorPoint",lua_cc_base_Node_getAnchorPoint);
        tolua_function(L,"convertToNodeSpaceAR",lua_cc_base_Node_convertToNodeSpaceAR);
        tolua_function(L,"visit",lua_cc_base_Node_visit);
#if CC_USE_PHYSICS
        tolua_function(L,"getPhysicsBody",lua_cc_base_Node_getPhysicsBody);
#endif
        tolua_function(L,"getAnchorPointInPoints",lua_cc_base_Node_getAnchorPointInPoints);
        tolua_function(L,"getOnEnterTransitionDidFinishCallback",lua_cc_base_Node_getOnEnterTransitionDidFinishCallback);
        tolua_function(L,"getDisplayedColor",lua_cc_base_Node_getDisplayedColor);
        tolua_function(L,"getScheduler",lua_cc_base_Node_getScheduler);
        tolua_function(L,"getParentToNodeAffineTransform",lua_cc_base_Node_getParentToNodeAffineTransform);
        tolua_function(L,"getPositionNormalized",lua_cc_base_Node_getPositionNormalized);
        tolua_function(L,"setColor",lua_cc_base_Node_setColor);
        tolua_function(L,"getParent",lua_cc_base_Node_getParent);
        tolua_function(L,"hitTest",lua_cc_base_Node_hitTest);
        tolua_function(L,"updateDisplayedColor",lua_cc_base_Node_updateDisplayedColor);
        tolua_function(L,"getParentToNodeTransform",lua_cc_base_Node_getParentToNodeTransform);
        tolua_function(L,"isScheduled",lua_cc_base_Node_isScheduled);
        tolua_function(L,"getWorldPosition",lua_cc_base_Node_getWorldPosition);
        tolua_function(L,"getWorldToNodeAffineTransform",lua_cc_base_Node_getWorldToNodeAffineTransform);
        tolua_function(L,"setOpacity",lua_cc_base_Node_setOpacity);
        tolua_function(L,"getContentSize",lua_cc_base_Node_getContentSize);
        tolua_function(L,"getColor",lua_cc_base_Node_getColor);
        tolua_function(L,"getBoundingBox",lua_cc_base_Node_getBoundingBox);
        tolua_function(L,"draw",lua_cc_base_Node_draw);
        tolua_function(L,"removeFromParent",lua_cc_base_Node_removeFromParentAndCleanup);
        tolua_function(L,"setPosition3D",lua_cc_base_Node_setPosition3D);
        tolua_function(L,"getWorldToNodeTransform",lua_cc_base_Node_getWorldToNodeTransform);
        tolua_function(L,"getNormalizedPosition",lua_cc_base_Node_getNormalizedPosition);
        tolua_function(L,"setOnExitTransitionDidStartCallback",lua_cc_base_Node_setOnExitTransitionDidStartCallback);
        tolua_function(L,"getActionManager",lua_cc_base_Node_getActionManager);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Scene");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Scene_constructor);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L,"initWithPhysics",lua_cc_base_Scene_initWithPhysics);
#endif
        tolua_function(L,"render",lua_cc_base_Scene_render);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
        tolua_function(L,"stepPhysicsAndNavigation",lua_cc_base_Scene_stepPhysicsAndNavigation);
#endif
#if CC_USE_PHYSICS
        tolua_function(L,"getPhysicsWorld",lua_cc_base_Scene_getPhysicsWorld);
#endif
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L,"initPhysicsWorld",lua_cc_base_Scene_initPhysicsWorld);
#endif
        tolua_function(L,"initWithSize",lua_cc_base_Scene_initWithSize);
        tolua_function(L,"createWithSize",lua_cc_base_Scene_createWithSize);
#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
        tolua_function(L,"createWithPhysics",lua_cc_base_Scene_createWithPhysics);
#endif
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.GLView");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getViewPortRect",lua_cc_base_GLView_getViewPortRect);
        tolua_function(L,"getSafeAreaRect",lua_cc_base_GLView_getSafeAreaRect);
        tolua_function(L,"getFrameSize",lua_cc_base_GLView_getFrameSize);
        tolua_function(L,"getVisibleOrigin",lua_cc_base_GLView_getVisibleOrigin);
        tolua_function(L,"getDesignResolutionSize",lua_cc_base_GLView_getDesignResolutionSize);
        tolua_function(L,"setIcon",lua_cc_base_GLView_setIcon);
        tolua_function(L,"getScissorRect",lua_cc_base_GLView_getScissorRect);
        tolua_function(L,"getVisibleRect",lua_cc_base_GLView_getVisibleRect);
        tolua_function(L,"getVisibleSize",lua_cc_base_GLView_getVisibleSize);
        tolua_function(L,"setGLContextAttrs",lua_cc_base_GLView_setGLContextAttrs);
        tolua_function(L,"getGLContextAttrs",lua_cc_base_GLView_getGLContextAttrs);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Director");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getAxmolThreadId",lua_cc_base_Director_getAxmolThreadId);
        tolua_function(L,"getWinSizeInPixels",lua_cc_base_Director_getWinSizeInPixels);
        tolua_function(L,"getSafeAreaRect",lua_cc_base_Director_getSafeAreaRect);
        tolua_function(L,"loadMatrix",lua_cc_base_Director_loadMatrix);
        tolua_function(L,"getWinSize",lua_cc_base_Director_getWinSize);
        tolua_function(L,"getVisibleOrigin",lua_cc_base_Director_getVisibleOrigin);
        tolua_function(L,"convertToUI",lua_cc_base_Director_convertToUI);
        tolua_function(L,"getMatrix",lua_cc_base_Director_getMatrix);
        tolua_function(L,"setClearColor",lua_cc_base_Director_setClearColor);
        tolua_function(L,"convertToGL",lua_cc_base_Director_convertToGL);
        tolua_function(L,"getRenderer",lua_cc_base_Director_getRenderer);
        tolua_function(L,"multiplyMatrix",lua_cc_base_Director_multiplyMatrix);
        tolua_function(L,"getVisibleSize",lua_cc_base_Director_getVisibleSize);
        tolua_function(L,"getInstance",lua_cc_base_Director_getInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Scheduler");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Scheduler_constructor);
        tolua_function(L,"performFunctionInCocosThread",lua_cc_base_Scheduler_performFunctionInCocosThread);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AsyncTaskPool");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AsyncTaskPool_constructor);
        tolua_function(L,"enqueue",lua_cc_base_AsyncTaskPool_enqueue);
        tolua_function(L,"destroyInstance",lua_cc_base_AsyncTaskPool_destroyInstance);
        tolua_function(L,"getInstance",lua_cc_base_AsyncTaskPool_getInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Speed");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Speed_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Follow");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Follow_constructor);
        tolua_function(L,"initWithTarget",lua_cc_base_Follow_initWithTarget);
        tolua_function(L,"initWithTargetAndOffset",lua_cc_base_Follow_initWithTargetAndOffset);
        tolua_function(L,"create",lua_cc_base_Follow_create);
        tolua_function(L,"createWithOffset",lua_cc_base_Follow_createWithOffset);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Image");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Image_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.PolygonInfo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_PolygonInfo_constructor);
        tolua_function(L,"getRect",lua_cc_base_PolygonInfo_getRect);
        tolua_function(L,"setQuads",lua_cc_base_PolygonInfo_setQuads);
        tolua_function(L,"setQuad",lua_cc_base_PolygonInfo_setQuad);
        tolua_function(L,"setTriangles",lua_cc_base_PolygonInfo_setTriangles);
        tolua_function(L,"setRect",lua_cc_base_PolygonInfo_setRect);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AutoPolygon");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AutoPolygon_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SpriteFrame");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SpriteFrame_constructor);
        tolua_function(L,"setAnchorPoint",lua_cc_base_SpriteFrame_setAnchorPoint);
        tolua_function(L,"setOffsetInPixels",lua_cc_base_SpriteFrame_setOffsetInPixels);
        tolua_function(L,"getOriginalSizeInPixels",lua_cc_base_SpriteFrame_getOriginalSizeInPixels);
        tolua_function(L,"setOriginalSize",lua_cc_base_SpriteFrame_setOriginalSize);
        tolua_function(L,"getCenterRect",lua_cc_base_SpriteFrame_getCenterRect);
        tolua_function(L,"setRectInPixels",lua_cc_base_SpriteFrame_setRectInPixels);
        tolua_function(L,"getRect",lua_cc_base_SpriteFrame_getRect);
        tolua_function(L,"setCenterRectInPixels",lua_cc_base_SpriteFrame_setCenterRectInPixels);
        tolua_function(L,"setOffset",lua_cc_base_SpriteFrame_setOffset);
        tolua_function(L,"initWithTextureFilename",lua_cc_base_SpriteFrame_initWithTextureFilename);
        tolua_function(L,"setRect",lua_cc_base_SpriteFrame_setRect);
        tolua_function(L,"initWithTexture",lua_cc_base_SpriteFrame_initWithTexture);
        tolua_function(L,"getOriginalSize",lua_cc_base_SpriteFrame_getOriginalSize);
        tolua_function(L,"getRectInPixels",lua_cc_base_SpriteFrame_getRectInPixels);
        tolua_function(L,"getOffset",lua_cc_base_SpriteFrame_getOffset);
        tolua_function(L,"setOriginalSizeInPixels",lua_cc_base_SpriteFrame_setOriginalSizeInPixels);
        tolua_function(L,"getAnchorPoint",lua_cc_base_SpriteFrame_getAnchorPoint);
        tolua_function(L,"getOffsetInPixels",lua_cc_base_SpriteFrame_getOffsetInPixels);
        tolua_function(L,"create",lua_cc_base_SpriteFrame_create);
        tolua_function(L,"createWithTexture",lua_cc_base_SpriteFrame_createWithTexture);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AnimationFrame");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AnimationFrame_constructor);
        tolua_function(L,"getUserInfo",lua_cc_base_AnimationFrame_getUserInfo);
        tolua_function(L,"setUserInfo",lua_cc_base_AnimationFrame_setUserInfo);
        tolua_function(L,"initWithSpriteFrame",lua_cc_base_AnimationFrame_initWithSpriteFrame);
        tolua_function(L,"create",lua_cc_base_AnimationFrame_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Animation");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Animation_constructor);
        tolua_function(L,"initWithAnimationFrames",lua_cc_base_Animation_initWithAnimationFrames);
        tolua_function(L,"setFrames",lua_cc_base_Animation_setFrames);
        tolua_function(L,"getFrames",lua_cc_base_Animation_getFrames);
        tolua_function(L,"initWithSpriteFrames",lua_cc_base_Animation_initWithSpriteFrames);
        tolua_function(L,"addSpriteFrameWithTexture",lua_cc_base_Animation_addSpriteFrameWithTexture);
        tolua_function(L,"create",lua_cc_base_Animation_create);
        tolua_function(L,"createWithSpriteFrames",lua_cc_base_Animation_createWithSpriteFrames);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Sequence");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Sequence_constructor);
        tolua_function(L,"init",lua_cc_base_Sequence_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Repeat");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Repeat_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RepeatForever");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_RepeatForever_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Spawn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Spawn_constructor);
        tolua_function(L,"init",lua_cc_base_Spawn_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RotateTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_RotateTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_RotateTo_initWithDuration);
        tolua_function(L,"create",lua_cc_base_RotateTo_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RotateBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_RotateBy_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_RotateBy_initWithDuration);
        tolua_function(L,"create",lua_cc_base_RotateBy_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MoveBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MoveBy_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_MoveBy_initWithDuration);
        tolua_function(L,"create",lua_cc_base_MoveBy_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MoveTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MoveTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_MoveTo_initWithDuration);
        tolua_function(L,"create",lua_cc_base_MoveTo_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SkewTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SkewTo_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SkewBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SkewBy_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.JumpBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_JumpBy_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_JumpBy_initWithDuration);
        tolua_function(L,"create",lua_cc_base_JumpBy_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.JumpTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_JumpTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_JumpTo_initWithDuration);
        tolua_function(L,"create",lua_cc_base_JumpTo_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.BezierBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_BezierBy_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_BezierBy_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.BezierTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_BezierTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_BezierTo_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ScaleTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ScaleTo_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ScaleBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ScaleBy_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Blink");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Blink_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_FadeTo_initWithDuration);
        tolua_function(L,"create",lua_cc_base_FadeTo_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TintTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TintTo_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_TintTo_initWithDuration);
        tolua_function(L,"create",lua_cc_base_TintTo_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TintBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TintBy_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_TintBy_initWithDuration);
        tolua_function(L,"create",lua_cc_base_TintBy_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.DelayTime");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_DelayTime_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Animate");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Animate_constructor);
        tolua_function(L,"getAnimation",lua_cc_base_Animate_getAnimation);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TargetedAction");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TargetedAction_constructor);
        tolua_function(L,"getForcedTarget",lua_cc_base_TargetedAction_getForcedTarget);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ActionFloat");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ActionFloat_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_ActionFloat_initWithDuration);
        tolua_function(L,"create",lua_cc_base_ActionFloat_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Properties");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getColor",lua_cc_base_Properties_getColor);
        tolua_function(L,"getNamespace",lua_cc_base_Properties_getNamespace);
        tolua_function(L,"getNextNamespace",lua_cc_base_Properties_getNextNamespace);
        tolua_function(L,"getVec3",lua_cc_base_Properties_getVec3);
        tolua_function(L,"getVec2",lua_cc_base_Properties_getVec2);
        tolua_function(L,"getVec4",lua_cc_base_Properties_getVec4);
        tolua_function(L,"getQuaternionFromAxisAngle",lua_cc_base_Properties_getQuaternionFromAxisAngle);
        tolua_function(L,"getPath",lua_cc_base_Properties_getPath);
        tolua_function(L,"getMat4",lua_cc_base_Properties_getMat4);
        tolua_function(L,"parseColor",lua_cc_base_Properties_parseColor);
        tolua_function(L,"parseVec3",lua_cc_base_Properties_parseVec3);
        tolua_function(L,"parseAxisAngle",lua_cc_base_Properties_parseAxisAngle);
        tolua_function(L,"parseVec2",lua_cc_base_Properties_parseVec2);
        tolua_function(L,"parseVec4",lua_cc_base_Properties_parseVec4);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.UserDefault");
    if (lua_istable(L,-1)) {
        tolua_function(L,"setLargeIntForKey",lua_cc_base_UserDefault_setLargeIntForKey);
        tolua_function(L,"getLargeIntForKey",lua_cc_base_UserDefault_getLargeIntForKey);
        tolua_function(L,"destroyInstance",lua_cc_base_UserDefault_destroyInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FileUtils");
    if (lua_istable(L,-1)) {
        tolua_function(L,"removeFile",lua_cc_base_FileUtils_removeFile);
        tolua_function(L,"listFilesRecursivelyAsync",lua_cc_base_FileUtils_listFilesRecursivelyAsync);
        tolua_function(L,"renameFile",lua_cc_base_FileUtils_renameFile);
        tolua_function(L,"getValueVectorFromFile",lua_cc_base_FileUtils_getValueVectorFromFile);
        tolua_function(L,"getSearchPaths",lua_cc_base_FileUtils_getSearchPaths);
        tolua_function(L,"writeToFile",lua_cc_base_FileUtils_writeToFile);
        tolua_function(L,"getOriginalSearchPaths",lua_cc_base_FileUtils_getOriginalSearchPaths);
        tolua_function(L,"listFiles",lua_cc_base_FileUtils_listFiles);
        tolua_function(L,"getValueMapFromFile",lua_cc_base_FileUtils_getValueMapFromFile);
        tolua_function(L,"getFileSize",lua_cc_base_FileUtils_getFileSize);
        tolua_function(L,"getValueMapFromData",lua_cc_base_FileUtils_getValueMapFromData);
        tolua_function(L,"removeDirectory",lua_cc_base_FileUtils_removeDirectory);
        tolua_function(L,"setSearchPaths",lua_cc_base_FileUtils_setSearchPaths);
        tolua_function(L,"writeStringToFile",lua_cc_base_FileUtils_writeStringToFile);
        tolua_function(L,"writeValueVectorToFile",lua_cc_base_FileUtils_writeValueVectorToFile);
        tolua_function(L,"isFileExist",lua_cc_base_FileUtils_isFileExist);
        tolua_function(L,"writeValueMapToFile",lua_cc_base_FileUtils_writeValueMapToFile);
        tolua_function(L,"isDirectoryExist",lua_cc_base_FileUtils_isDirectoryExist);
        tolua_function(L,"createDirectory",lua_cc_base_FileUtils_createDirectory);
        tolua_function(L,"listFilesAsync",lua_cc_base_FileUtils_listFilesAsync);
        tolua_function(L,"listFilesRecursively",lua_cc_base_FileUtils_listFilesRecursively);
        tolua_function(L,"writeBinaryToFile",lua_cc_base_FileUtils_writeBinaryToFile);
        tolua_function(L,"getInstance",lua_cc_base_FileUtils_getInstance);
        tolua_function(L,"destroyInstance",lua_cc_base_FileUtils_destroyInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventCustom");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventCustom_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventDispatcher");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventDispatcher_constructor);
        tolua_function(L,"dispatchCustomEvent",lua_cc_base_EventDispatcher_dispatchCustomEvent);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventFocus");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventFocus_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerAcceleration");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerAcceleration_constructor);
        tolua_function(L,"init",lua_cc_base_EventListenerAcceleration_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerFocus");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerFocus_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerKeyboard");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerKeyboard_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventMouse");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventMouse_constructor);
        tolua_function(L,"getPreviousLocationInView",lua_cc_base_EventMouse_getPreviousLocationInView);
        tolua_function(L,"getLocation",lua_cc_base_EventMouse_getLocation);
        tolua_function(L,"getPreviousLocation",lua_cc_base_EventMouse_getPreviousLocation);
        tolua_function(L,"getDelta",lua_cc_base_EventMouse_getDelta);
        tolua_function(L,"getStartLocationInView",lua_cc_base_EventMouse_getStartLocationInView);
        tolua_function(L,"getStartLocation",lua_cc_base_EventMouse_getStartLocation);
        tolua_function(L,"getLocationInView",lua_cc_base_EventMouse_getLocationInView);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerMouse");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerMouse_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerTouchOneByOne");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerTouchOneByOne_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EventListenerTouchAllAtOnce");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EventListenerTouchAllAtOnce_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ActionCamera");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ActionCamera_constructor);
        tolua_function(L,"setEye",lua_cc_base_ActionCamera_setEye);
        tolua_function(L,"getEye",lua_cc_base_ActionCamera_getEye);
        tolua_function(L,"setUp",lua_cc_base_ActionCamera_setUp);
        tolua_function(L,"getCenter",lua_cc_base_ActionCamera_getCenter);
        tolua_function(L,"setCenter",lua_cc_base_ActionCamera_setCenter);
        tolua_function(L,"getUp",lua_cc_base_ActionCamera_getUp);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.OrbitCamera");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_OrbitCamera_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CardinalSplineTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CardinalSplineTo_constructor);
        tolua_function(L,"getPoints",lua_cc_base_CardinalSplineTo_getPoints);
        tolua_function(L,"updatePosition",lua_cc_base_CardinalSplineTo_updatePosition);
        tolua_function(L,"initWithDuration",lua_cc_base_CardinalSplineTo_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CardinalSplineBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CardinalSplineBy_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CatmullRomTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"initWithDuration",lua_cc_base_CatmullRomTo_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CatmullRomBy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"initWithDuration",lua_cc_base_CatmullRomBy_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseExponentialIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseExponentialIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseExponentialOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseExponentialOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseExponentialInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseExponentialInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseSineIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseSineIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseSineOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseSineOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseSineInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseSineInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBounceIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBounceIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBounceOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBounceOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBounceInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBounceInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBackIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBackIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBackOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBackOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBackInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBackInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuadraticActionIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuadraticActionIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuadraticActionOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuadraticActionOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuadraticActionInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuadraticActionInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuarticActionIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuarticActionIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuarticActionOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuarticActionOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuarticActionInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuarticActionInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuinticActionIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuinticActionIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuinticActionOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuinticActionOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseQuinticActionInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseQuinticActionInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCircleActionIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCircleActionIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCircleActionOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCircleActionOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCircleActionInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCircleActionInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCubicActionIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCubicActionIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCubicActionOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCubicActionOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseCubicActionInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseCubicActionInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseElasticIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseElasticIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseElasticOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseElasticOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseElasticInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseElasticInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.EaseBezierAction");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_EaseBezierAction_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Show");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Show_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Hide");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Hide_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ToggleVisibility");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ToggleVisibility_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RemoveSelf");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_RemoveSelf_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FlipX");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FlipX_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FlipY");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FlipY_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Place");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Place_constructor);
        tolua_function(L,"initWithPosition",lua_cc_base_Place_initWithPosition);
        tolua_function(L,"create",lua_cc_base_Place_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CallFunc");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CallFunc_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.GridAction");
    if (lua_istable(L,-1)) {
        tolua_function(L,"initWithDuration",lua_cc_base_GridAction_initWithDuration);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Grid3DAction");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getGridRect",lua_cc_base_Grid3DAction_getGridRect);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.StopGrid");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_StopGrid_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ReuseGrid");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ReuseGrid_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Waves3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Waves3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Waves3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_Waves3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FlipX3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FlipX3D_constructor);
        tolua_function(L,"initWithSize",lua_cc_base_FlipX3D_initWithSize);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FlipY3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FlipY3D_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Lens3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Lens3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Lens3D_initWithDuration);
        tolua_function(L,"setPosition",lua_cc_base_Lens3D_setPosition);
        tolua_function(L,"getPosition",lua_cc_base_Lens3D_getPosition);
        tolua_function(L,"create",lua_cc_base_Lens3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Ripple3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Ripple3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Ripple3D_initWithDuration);
        tolua_function(L,"setPosition",lua_cc_base_Ripple3D_setPosition);
        tolua_function(L,"getPosition",lua_cc_base_Ripple3D_getPosition);
        tolua_function(L,"create",lua_cc_base_Ripple3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Shaky3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Shaky3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Shaky3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_Shaky3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Liquid");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Liquid_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Liquid_initWithDuration);
        tolua_function(L,"create",lua_cc_base_Liquid_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Waves");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Waves_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Waves_initWithDuration);
        tolua_function(L,"create",lua_cc_base_Waves_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Twirl");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Twirl_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_Twirl_initWithDuration);
        tolua_function(L,"setPosition",lua_cc_base_Twirl_setPosition);
        tolua_function(L,"getPosition",lua_cc_base_Twirl_getPosition);
        tolua_function(L,"create",lua_cc_base_Twirl_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ActionManager");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ActionManager_constructor);
        tolua_function(L,"resumeTargets",lua_cc_base_ActionManager_resumeTargets);
        tolua_function(L,"pauseAllRunningActions",lua_cc_base_ActionManager_pauseAllRunningActions);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.PageTurn3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"create",lua_cc_base_PageTurn3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ProgressTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ProgressTo_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ProgressFromTo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ProgressFromTo_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ShakyTiles3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ShakyTiles3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_ShakyTiles3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_ShakyTiles3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ShatteredTiles3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ShatteredTiles3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_ShatteredTiles3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_ShatteredTiles3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ShuffleTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ShuffleTiles_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_ShuffleTiles_initWithDuration);
        tolua_function(L,"getDelta",lua_cc_base_ShuffleTiles_getDelta);
        tolua_function(L,"create",lua_cc_base_ShuffleTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeOutTRTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeOutTRTiles_constructor);
        tolua_function(L,"turnOnTile",lua_cc_base_FadeOutTRTiles_turnOnTile);
        tolua_function(L,"turnOffTile",lua_cc_base_FadeOutTRTiles_turnOffTile);
        tolua_function(L,"transformTile",lua_cc_base_FadeOutTRTiles_transformTile);
        tolua_function(L,"testFunc",lua_cc_base_FadeOutTRTiles_testFunc);
        tolua_function(L,"create",lua_cc_base_FadeOutTRTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeOutBLTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeOutBLTiles_constructor);
        tolua_function(L,"create",lua_cc_base_FadeOutBLTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeOutUpTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeOutUpTiles_constructor);
        tolua_function(L,"create",lua_cc_base_FadeOutUpTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FadeOutDownTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FadeOutDownTiles_constructor);
        tolua_function(L,"create",lua_cc_base_FadeOutDownTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TurnOffTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TurnOffTiles_constructor);
        tolua_function(L,"turnOnTile",lua_cc_base_TurnOffTiles_turnOnTile);
        tolua_function(L,"turnOffTile",lua_cc_base_TurnOffTiles_turnOffTile);
        tolua_function(L,"initWithDuration",lua_cc_base_TurnOffTiles_initWithDuration);
        tolua_function(L,"create",lua_cc_base_TurnOffTiles_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.WavesTiles3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_WavesTiles3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_WavesTiles3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_WavesTiles3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.JumpTiles3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_JumpTiles3D_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_JumpTiles3D_initWithDuration);
        tolua_function(L,"create",lua_cc_base_JumpTiles3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SplitRows");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SplitRows_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SplitCols");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SplitCols_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AtlasNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AtlasNode_constructor);
        tolua_function(L,"getBlendFunc",lua_cc_base_AtlasNode_getBlendFunc);
        tolua_function(L,"setBlendFunc",lua_cc_base_AtlasNode_setBlendFunc);
        tolua_function(L,"setTextureAtlas",lua_cc_base_AtlasNode_setTextureAtlas);
        tolua_function(L,"getTexture",lua_cc_base_AtlasNode_getTexture);
        tolua_function(L,"getTextureAtlas",lua_cc_base_AtlasNode_getTextureAtlas);
        tolua_function(L,"setTexture",lua_cc_base_AtlasNode_setTexture);
        tolua_function(L,"setQuadsToDraw",lua_cc_base_AtlasNode_setQuadsToDraw);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ClippingNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"init",lua_cc_base_ClippingNode_init);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ClippingRectangleNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getClippingRegion",lua_cc_base_ClippingRectangleNode_getClippingRegion);
        tolua_function(L,"setClippingRegion",lua_cc_base_ClippingRectangleNode_setClippingRegion);
        tolua_function(L,"create",lua_cc_base_ClippingRectangleNode_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.DrawNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_DrawNode_constructor);
        tolua_function(L,"drawLine",lua_cc_base_DrawNode_drawLine);
        tolua_function(L,"drawRect",lua_cc_base_DrawNode_drawRect);
        tolua_function(L,"drawSolidCircle",lua_cc_base_DrawNode_drawSolidCircle);
        tolua_function(L,"drawDot",lua_cc_base_DrawNode_drawDot);
        tolua_function(L,"drawSegment",lua_cc_base_DrawNode_drawSegment);
        tolua_function(L,"getBlendFunc",lua_cc_base_DrawNode_getBlendFunc);
        tolua_function(L,"drawCircle",lua_cc_base_DrawNode_drawCircle);
        tolua_function(L,"drawQuadBezier",lua_cc_base_DrawNode_drawQuadBezier);
        tolua_function(L,"drawTriangle",lua_cc_base_DrawNode_drawTriangle);
        tolua_function(L,"setBlendFunc",lua_cc_base_DrawNode_setBlendFunc);
        tolua_function(L,"drawSolidRect",lua_cc_base_DrawNode_drawSolidRect);
        tolua_function(L,"drawPoint",lua_cc_base_DrawNode_drawPoint);
        tolua_function(L,"drawCubicBezier",lua_cc_base_DrawNode_drawCubicBezier);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Label");
    if (lua_istable(L,-1)) {
        tolua_function(L,"enableShadow",lua_cc_base_Label_enableShadow);
        tolua_function(L,"getString",lua_cc_base_Label_getString);
        tolua_function(L,"setTTFConfig",lua_cc_base_Label_setTTFConfig);
        tolua_function(L,"getTextColor",lua_cc_base_Label_getTextColor);
        tolua_function(L,"getBlendFunc",lua_cc_base_Label_getBlendFunc);
        tolua_function(L,"getShadowOffset",lua_cc_base_Label_getShadowOffset);
        tolua_function(L,"setString",lua_cc_base_Label_setString);
        tolua_function(L,"setBMFontFilePath",lua_cc_base_Label_setBMFontFilePath);
        tolua_function(L,"initWithTTF",lua_cc_base_Label_initWithTTF);
        tolua_function(L,"getFontAtlas",lua_cc_base_Label_getFontAtlas);
        tolua_function(L,"enableOutline",lua_cc_base_Label_enableOutline);
        tolua_function(L,"getEffectColor",lua_cc_base_Label_getEffectColor);
        tolua_function(L,"removeAllChildrenWithCleanup",lua_cc_base_Label_removeAllChildrenWithCleanup);
        tolua_function(L,"setCharMap",lua_cc_base_Label_setCharMap);
        tolua_function(L,"getDimensions",lua_cc_base_Label_getDimensions);
        tolua_function(L,"getShadowColor",lua_cc_base_Label_getShadowColor);
        tolua_function(L,"getTTFConfig",lua_cc_base_Label_getTTFConfig);
        tolua_function(L,"setTextColor",lua_cc_base_Label_setTextColor);
        tolua_function(L,"enableGlow",lua_cc_base_Label_enableGlow);
        tolua_function(L,"setBlendFunc",lua_cc_base_Label_setBlendFunc);
        tolua_function(L,"createWithBMFont",lua_cc_base_Label_createWithBMFont);
        tolua_function(L,"createWithCharMap",lua_cc_base_Label_createWithCharMap);
        tolua_function(L,"createWithSystemFont",lua_cc_base_Label_createWithSystemFont);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.LabelAtlas");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_LabelAtlas_constructor);
        tolua_function(L,"setString",lua_cc_base_LabelAtlas_setString);
        tolua_function(L,"initWithString",lua_cc_base_LabelAtlas_initWithString);
        tolua_function(L,"getString",lua_cc_base_LabelAtlas_getString);
        tolua_function(L,"_create",lua_cc_base_LabelAtlas_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Sprite");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Sprite_constructor);
        tolua_function(L,"setSpriteFrame",lua_cc_base_Sprite_setSpriteFrame);
        tolua_function(L,"setTexture",lua_cc_base_Sprite_setTexture);
        tolua_function(L,"getTexture",lua_cc_base_Sprite_getTexture);
        tolua_function(L,"getOffsetPosition",lua_cc_base_Sprite_getOffsetPosition);
        tolua_function(L,"getCenterRect",lua_cc_base_Sprite_getCenterRect);
        tolua_function(L,"setCenterRectNormalized",lua_cc_base_Sprite_setCenterRectNormalized);
        tolua_function(L,"setTextureRect",lua_cc_base_Sprite_setTextureRect);
        tolua_function(L,"setTextureAtlas",lua_cc_base_Sprite_setTextureAtlas);
        tolua_function(L,"getBlendFunc",lua_cc_base_Sprite_getBlendFunc);
        tolua_function(L,"setCenterRect",lua_cc_base_Sprite_setCenterRect);
        tolua_function(L,"removeAllChildrenWithCleanup",lua_cc_base_Sprite_removeAllChildrenWithCleanup);
        tolua_function(L,"getCenterRectNormalized",lua_cc_base_Sprite_getCenterRectNormalized);
        tolua_function(L,"initWithTexture",lua_cc_base_Sprite_initWithTexture);
        tolua_function(L,"getTextureRect",lua_cc_base_Sprite_getTextureRect);
        tolua_function(L,"initWithFile",lua_cc_base_Sprite_initWithFile);
        tolua_function(L,"setBlendFunc",lua_cc_base_Sprite_setBlendFunc);
        tolua_function(L,"getTextureAtlas",lua_cc_base_Sprite_getTextureAtlas);
        tolua_function(L,"setVertexRect",lua_cc_base_Sprite_setVertexRect);
        tolua_function(L,"createWithTexture",lua_cc_base_Sprite_createWithTexture);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.LayerColor");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_LayerColor_constructor);
        tolua_function(L,"initWithColor",lua_cc_base_LayerColor_initWithColor);
        tolua_function(L,"create",lua_cc_base_LayerColor_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.LayerGradient");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_LayerGradient_constructor);
        tolua_function(L,"getStartColor",lua_cc_base_LayerGradient_getStartColor);
        tolua_function(L,"setVector",lua_cc_base_LayerGradient_setVector);
        tolua_function(L,"setStartOpacity",lua_cc_base_LayerGradient_setStartOpacity);
        tolua_function(L,"setEndOpacity",lua_cc_base_LayerGradient_setEndOpacity);
        tolua_function(L,"getVector",lua_cc_base_LayerGradient_getVector);
        tolua_function(L,"setEndColor",lua_cc_base_LayerGradient_setEndColor);
        tolua_function(L,"initWithColor",lua_cc_base_LayerGradient_initWithColor);
        tolua_function(L,"getEndColor",lua_cc_base_LayerGradient_getEndColor);
        tolua_function(L,"setStartColor",lua_cc_base_LayerGradient_setStartColor);
        tolua_function(L,"create",lua_cc_base_LayerGradient_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.LayerRadialGradient");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_LayerRadialGradient_constructor);
        tolua_function(L,"getStartColor",lua_cc_base_LayerRadialGradient_getStartColor);
        tolua_function(L,"getBlendFunc",lua_cc_base_LayerRadialGradient_getBlendFunc);
        tolua_function(L,"getStartColor3B",lua_cc_base_LayerRadialGradient_getStartColor3B);
        tolua_function(L,"setCenter",lua_cc_base_LayerRadialGradient_setCenter);
        tolua_function(L,"getEndColor",lua_cc_base_LayerRadialGradient_getEndColor);
        tolua_function(L,"setStartOpacity",lua_cc_base_LayerRadialGradient_setStartOpacity);
        tolua_function(L,"getCenter",lua_cc_base_LayerRadialGradient_getCenter);
        tolua_function(L,"setEndOpacity",lua_cc_base_LayerRadialGradient_setEndOpacity);
        tolua_function(L,"initWithColor",lua_cc_base_LayerRadialGradient_initWithColor);
        tolua_function(L,"setEndColor",lua_cc_base_LayerRadialGradient_setEndColor);
        tolua_function(L,"getEndColor3B",lua_cc_base_LayerRadialGradient_getEndColor3B);
        tolua_function(L,"setStartColor",lua_cc_base_LayerRadialGradient_setStartColor);
        tolua_function(L,"setBlendFunc",lua_cc_base_LayerRadialGradient_setBlendFunc);
        tolua_function(L,"create",lua_cc_base_LayerRadialGradient_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.LayerMultiplex");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_LayerMultiplex_constructor);
        tolua_function(L,"initWithArray",lua_cc_base_LayerMultiplex_initWithArray);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItem");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItem_constructor);
        tolua_function(L,"rect",lua_cc_base_MenuItem_rect);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemLabel");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemLabel_constructor);
        tolua_function(L,"getDisabledColor",lua_cc_base_MenuItemLabel_getDisabledColor);
        tolua_function(L,"initWithLabel",lua_cc_base_MenuItemLabel_initWithLabel);
        tolua_function(L,"setDisabledColor",lua_cc_base_MenuItemLabel_setDisabledColor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemAtlasFont");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemAtlasFont_constructor);
        tolua_function(L,"initWithString",lua_cc_base_MenuItemAtlasFont_initWithString);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemFont");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemFont_constructor);
        tolua_function(L,"initWithString",lua_cc_base_MenuItemFont_initWithString);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemSprite");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemSprite_constructor);
        tolua_function(L,"setEnabled",lua_cc_base_MenuItemSprite_setEnabled);
        tolua_function(L,"selected",lua_cc_base_MenuItemSprite_selected);
        tolua_function(L,"initWithNormalSprite",lua_cc_base_MenuItemSprite_initWithNormalSprite);
        tolua_function(L,"unselected",lua_cc_base_MenuItemSprite_unselected);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemImage");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemImage_constructor);
        tolua_function(L,"init",lua_cc_base_MenuItemImage_init);
        tolua_function(L,"initWithNormalImage",lua_cc_base_MenuItemImage_initWithNormalImage);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MenuItemToggle");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MenuItemToggle_constructor);
        tolua_function(L,"setSubItems",lua_cc_base_MenuItemToggle_setSubItems);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Menu");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Menu_constructor);
        tolua_function(L,"initWithArray",lua_cc_base_Menu_initWithArray);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MotionStreak");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MotionStreak_constructor);
        tolua_function(L,"getBlendFunc",lua_cc_base_MotionStreak_getBlendFunc);
        tolua_function(L,"setBlendFunc",lua_cc_base_MotionStreak_setBlendFunc);
        tolua_function(L,"tintWithColor",lua_cc_base_MotionStreak_tintWithColor);
        tolua_function(L,"getTexture",lua_cc_base_MotionStreak_getTexture);
        tolua_function(L,"setTexture",lua_cc_base_MotionStreak_setTexture);
        tolua_function(L,"initWithFade",lua_cc_base_MotionStreak_initWithFade);
        tolua_function(L,"create",lua_cc_base_MotionStreak_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.NodeGrid");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_NodeGrid_constructor);
        tolua_function(L,"setGridRect",lua_cc_base_NodeGrid_setGridRect);
        tolua_function(L,"getGrid",lua_cc_base_NodeGrid_getGrid);
        tolua_function(L,"getGridRect",lua_cc_base_NodeGrid_getGridRect);
        tolua_function(L,"create",lua_cc_base_NodeGrid_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleBatchNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleBatchNode_constructor);
        tolua_function(L,"setTexture",lua_cc_base_ParticleBatchNode_setTexture);
        tolua_function(L,"getTexture",lua_cc_base_ParticleBatchNode_getTexture);
        tolua_function(L,"setTextureAtlas",lua_cc_base_ParticleBatchNode_setTextureAtlas);
        tolua_function(L,"setBlendFunc",lua_cc_base_ParticleBatchNode_setBlendFunc);
        tolua_function(L,"removeAllChildrenWithCleanup",lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup);
        tolua_function(L,"getTextureAtlas",lua_cc_base_ParticleBatchNode_getTextureAtlas);
        tolua_function(L,"getBlendFunc",lua_cc_base_ParticleBatchNode_getBlendFunc);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SpriteFrameCache");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getSpriteSheetLoader",lua_cc_base_SpriteFrameCache_getSpriteSheetLoader);
        tolua_function(L,"addSpriteFrames",lua_cc_base_SpriteFrameCache_addSpriteFramesWithFile);
        tolua_function(L,"getSpriteFrame",lua_cc_base_SpriteFrameCache_getSpriteFrameByName);
        tolua_function(L,"addSpriteFrameCapInset",lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleData");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleData_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleEmissionMaskCache");
    if (lua_istable(L,-1)) {
        tolua_function(L,"bakeEmissionMask",lua_cc_base_ParticleEmissionMaskCache_bakeEmissionMask);
        tolua_function(L,"getEmissionMask",lua_cc_base_ParticleEmissionMaskCache_getEmissionMask);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSystem");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSystem_constructor);
        tolua_function(L,"setAnimationDescriptor",lua_cc_base_ParticleSystem_setAnimationDescriptor);
        tolua_function(L,"getTexture",lua_cc_base_ParticleSystem_getTexture);
        tolua_function(L,"getStartColor",lua_cc_base_ParticleSystem_getStartColor);
        tolua_function(L,"setPosVar",lua_cc_base_ParticleSystem_setPosVar);
        tolua_function(L,"setHSVVar",lua_cc_base_ParticleSystem_setHSVVar);
        tolua_function(L,"getGravity",lua_cc_base_ParticleSystem_getGravity);
        tolua_function(L,"setEndColor",lua_cc_base_ParticleSystem_setEndColor);
        tolua_function(L,"addAnimationIndex",lua_cc_base_ParticleSystem_addAnimationIndex);
        tolua_function(L,"setTexture",lua_cc_base_ParticleSystem_setTexture);
        tolua_function(L,"getPosVar",lua_cc_base_ParticleSystem_getPosVar);
        tolua_function(L,"getSourcePosition",lua_cc_base_ParticleSystem_getSourcePosition);
        tolua_function(L,"setEndColorVar",lua_cc_base_ParticleSystem_setEndColorVar);
        tolua_function(L,"setEmissionShape",lua_cc_base_ParticleSystem_setEmissionShape);
        tolua_function(L,"setRectForUndefinedIndices",lua_cc_base_ParticleSystem_setRectForUndefinedIndices);
        tolua_function(L,"getHSVVar",lua_cc_base_ParticleSystem_getHSVVar);
        tolua_function(L,"getHSV",lua_cc_base_ParticleSystem_getHSV);
        tolua_function(L,"setSourcePosition",lua_cc_base_ParticleSystem_setSourcePosition);
        tolua_function(L,"stop",lua_cc_base_ParticleSystem_stop);
        tolua_function(L,"start",lua_cc_base_ParticleSystem_start);
        tolua_function(L,"addEmissionShape",lua_cc_base_ParticleSystem_addEmissionShape);
        tolua_function(L,"setStartColor",lua_cc_base_ParticleSystem_setStartColor);
        tolua_function(L,"setGravity",lua_cc_base_ParticleSystem_setGravity);
        tolua_function(L,"getEndColorVar",lua_cc_base_ParticleSystem_getEndColorVar);
        tolua_function(L,"getEndColor",lua_cc_base_ParticleSystem_getEndColor);
        tolua_function(L,"setMultiAnimationRandomSpecific",lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific);
        tolua_function(L,"setHSV",lua_cc_base_ParticleSystem_setHSV);
        tolua_function(L,"getBlendFunc",lua_cc_base_ParticleSystem_getBlendFunc);
        tolua_function(L,"setStartColorVar",lua_cc_base_ParticleSystem_setStartColorVar);
        tolua_function(L,"initWithDictionary",lua_cc_base_ParticleSystem_initWithDictionary);
        tolua_function(L,"setBlendFunc",lua_cc_base_ParticleSystem_setBlendFunc);
        tolua_function(L,"getStartColorVar",lua_cc_base_ParticleSystem_getStartColorVar);
        tolua_function(L,"createRectTorusShape",lua_cc_base_ParticleSystem_createRectTorusShape);
        tolua_function(L,"createTorusShape",lua_cc_base_ParticleSystem_createTorusShape);
        tolua_function(L,"createConeShape",lua_cc_base_ParticleSystem_createConeShape);
        tolua_function(L,"createPointShape",lua_cc_base_ParticleSystem_createPointShape);
        tolua_function(L,"createCircleShape",lua_cc_base_ParticleSystem_createCircleShape);
        tolua_function(L,"createMaskShape",lua_cc_base_ParticleSystem_createMaskShape);
        tolua_function(L,"createRectShape",lua_cc_base_ParticleSystem_createRectShape);
        tolua_function(L,"getAllParticleSystems",lua_cc_base_ParticleSystem_getAllParticleSystems);
        tolua_function(L,"createConeTorusShape",lua_cc_base_ParticleSystem_createConeTorusShape);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSystemQuad");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSystemQuad_constructor);
        tolua_function(L,"setTextureWithRect",lua_cc_base_ParticleSystemQuad_setTextureWithRect);
        tolua_function(L,"create",lua_cc_base_ParticleSystemQuad_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleFire");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleFire_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleFireworks");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleFireworks_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleFireworks_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleFireworks_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSun");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSun_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleSun_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleSun_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleGalaxy");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleGalaxy_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleGalaxy_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleGalaxy_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleFlower");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleFlower_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleFlower_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleFlower_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleMeteor");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleMeteor_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleMeteor_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleMeteor_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSpiral");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSpiral_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleSpiral_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleSpiral_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleExplosion");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleExplosion_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleExplosion_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleExplosion_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSmoke");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSmoke_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleSmoke_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleSmoke_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleSnow");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleSnow_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleSnow_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleSnow_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParticleRain");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParticleRain_constructor);
        tolua_function(L,"init",lua_cc_base_ParticleRain_init);
        tolua_function(L,"initWithTotalParticles",lua_cc_base_ParticleRain_initWithTotalParticles);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ProgressTimer");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ProgressTimer_constructor);
        tolua_function(L,"setBarChangeRate",lua_cc_base_ProgressTimer_setBarChangeRate);
        tolua_function(L,"setMidpoint",lua_cc_base_ProgressTimer_setMidpoint);
        tolua_function(L,"getBarChangeRate",lua_cc_base_ProgressTimer_getBarChangeRate);
        tolua_function(L,"getMidpoint",lua_cc_base_ProgressTimer_getMidpoint);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ProtectedNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ProtectedNode_constructor);
        tolua_function(L,"disableCascadeColor",lua_cc_base_ProtectedNode_disableCascadeColor);
        tolua_function(L,"disableCascadeOpacity",lua_cc_base_ProtectedNode_disableCascadeOpacity);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RenderTexture");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_RenderTexture_constructor);
        tolua_function(L,"setVirtualViewport",lua_cc_base_RenderTexture_setVirtualViewport);
        tolua_function(L,"getRenderTarget",lua_cc_base_RenderTexture_getRenderTarget);
        tolua_function(L,"saveToFileAsNonPMA",lua_cc_base_RenderTexture_saveToFileAsNonPMA);
        tolua_function(L,"saveToFile",lua_cc_base_RenderTexture_saveToFile);
        tolua_function(L,"setClearColor",lua_cc_base_RenderTexture_setClearColor);
        tolua_function(L,"getClearColor",lua_cc_base_RenderTexture_getClearColor);
        tolua_function(L,"initWithWidthAndHeight",lua_cc_base_RenderTexture_initWithWidthAndHeight);
        tolua_function(L,"create",lua_cc_base_RenderTexture_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionScene");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionScene_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSceneOriented");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSceneOriented_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionRotoZoom");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionRotoZoom_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionJumpZoom");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionJumpZoom_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionMoveInL");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionMoveInL_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionMoveInL_easeActionWithAction);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionMoveInR");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionMoveInR_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionMoveInT");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionMoveInT_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionMoveInB");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionMoveInB_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSlideInL");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSlideInL_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionSlideInL_easeActionWithAction);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSlideInR");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSlideInR_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSlideInB");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSlideInB_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSlideInT");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSlideInT_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionShrinkGrow");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionShrinkGrow_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionShrinkGrow_easeActionWithAction);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFlipX");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFlipX_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFlipY");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFlipY_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFlipAngular");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFlipAngular_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionZoomFlipX");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionZoomFlipX_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionZoomFlipY");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionZoomFlipY_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionZoomFlipAngular");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionZoomFlipAngular_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFade");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFade_constructor);
        tolua_function(L,"initWithDuration",lua_cc_base_TransitionFade_initWithDuration);
        tolua_function(L,"create",lua_cc_base_TransitionFade_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionCrossFade");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionCrossFade_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionTurnOffTiles");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionTurnOffTiles_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionTurnOffTiles_easeActionWithAction);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSplitCols");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSplitCols_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionSplitCols_easeActionWithAction);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionSplitRows");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionSplitRows_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFadeTR");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFadeTR_constructor);
        tolua_function(L,"easeActionWithAction",lua_cc_base_TransitionFadeTR_easeActionWithAction);
        tolua_function(L,"actionWithSize",lua_cc_base_TransitionFadeTR_actionWithSize);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFadeBL");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFadeBL_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFadeUp");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFadeUp_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionFadeDown");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionFadeDown_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionPageTurn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionPageTurn_constructor);
        tolua_function(L,"actionWithSize",lua_cc_base_TransitionPageTurn_actionWithSize);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgress");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgress_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressRadialCCW");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressRadialCCW_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressRadialCW");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressRadialCW_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressHorizontal");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressHorizontal_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressVertical");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressVertical_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressInOut");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressInOut_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TransitionProgressOutIn");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TransitionProgressOutIn_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Camera");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Camera_constructor);
        tolua_function(L,"getViewProjectionMatrix",lua_cc_base_Camera_getViewProjectionMatrix);
        tolua_function(L,"lookAt",lua_cc_base_Camera_lookAt);
        tolua_function(L,"getProjectionMatrix",lua_cc_base_Camera_getProjectionMatrix);
        tolua_function(L,"setAdditionalProjection",lua_cc_base_Camera_setAdditionalProjection);
        tolua_function(L,"isVisibleInFrustum",lua_cc_base_Camera_isVisibleInFrustum);
        tolua_function(L,"setDepth",lua_cc_base_Camera_setDepth);
        tolua_function(L,"projectGL",lua_cc_base_Camera_projectGL);
        tolua_function(L,"getViewMatrix",lua_cc_base_Camera_getViewMatrix);
        tolua_function(L,"project",lua_cc_base_Camera_project);
        tolua_function(L,"getDepthInView",lua_cc_base_Camera_getDepthInView);
        tolua_function(L,"getVisitingCamera",lua_cc_base_Camera_getVisitingCamera);
        tolua_function(L,"getDefaultViewport",lua_cc_base_Camera_getDefaultViewport);
        tolua_function(L,"setDefaultViewport",lua_cc_base_Camera_setDefaultViewport);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CameraBackgroundBrush");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CameraBackgroundBrush_constructor);
        tolua_function(L,"createColorBrush",lua_cc_base_CameraBackgroundBrush_createColorBrush);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CameraBackgroundDepthBrush");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CameraBackgroundDepthBrush_constructor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CameraBackgroundColorBrush");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CameraBackgroundColorBrush_constructor);
        tolua_function(L,"setColor",lua_cc_base_CameraBackgroundColorBrush_setColor);
        tolua_function(L,"create",lua_cc_base_CameraBackgroundColorBrush_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.CameraBackgroundSkyBoxBrush");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_CameraBackgroundSkyBoxBrush_constructor);
        tolua_function(L,"setTexture",lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture);
        tolua_function(L,"getTexture",lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.GridBase");
    if (lua_istable(L,-1)) {
        tolua_function(L,"setGridSize",lua_cc_base_GridBase_setGridSize);
        tolua_function(L,"setGridRect",lua_cc_base_GridBase_setGridRect);
        tolua_function(L,"getGridRect",lua_cc_base_GridBase_getGridRect);
        tolua_function(L,"getGridSize",lua_cc_base_GridBase_getGridSize);
        tolua_function(L,"getStep",lua_cc_base_GridBase_getStep);
        tolua_function(L,"setStep",lua_cc_base_GridBase_setStep);
        tolua_function(L,"initWithSize",lua_cc_base_GridBase_initWithSize);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Grid3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Grid3D_constructor);
        tolua_function(L,"create",lua_cc_base_Grid3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TiledGrid3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"create",lua_cc_base_TiledGrid3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.DirectionLight");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_DirectionLight_constructor);
        tolua_function(L,"getDirection",lua_cc_base_DirectionLight_getDirection);
        tolua_function(L,"getDirectionInWorld",lua_cc_base_DirectionLight_getDirectionInWorld);
        tolua_function(L,"setDirection",lua_cc_base_DirectionLight_setDirection);
        tolua_function(L,"create",lua_cc_base_DirectionLight_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.PointLight");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_PointLight_constructor);
        tolua_function(L,"create",lua_cc_base_PointLight_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SpotLight");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SpotLight_constructor);
        tolua_function(L,"setDirection",lua_cc_base_SpotLight_setDirection);
        tolua_function(L,"getDirection",lua_cc_base_SpotLight_getDirection);
        tolua_function(L,"getDirectionInWorld",lua_cc_base_SpotLight_getDirectionInWorld);
        tolua_function(L,"create",lua_cc_base_SpotLight_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AmbientLight");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AmbientLight_constructor);
        tolua_function(L,"create",lua_cc_base_AmbientLight_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.RenderState");
    if (lua_istable(L,-1)) {
        tolua_function(L,"bindPass",lua_cc_base_RenderState_bindPass);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Technique");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getPasses",lua_cc_base_Technique_getPasses);
        tolua_function(L,"getPassByIndex",lua_cc_base_Technique_getPassByIndex);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Material");
    if (lua_istable(L,-1)) {
        tolua_function(L,"draw",lua_cc_base_Material_draw);
        tolua_function(L,"getTechniqueByIndex",lua_cc_base_Material_getTechniqueByIndex);
        tolua_function(L,"getTechniques",lua_cc_base_Material_getTechniques);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Pass");
    if (lua_istable(L,-1)) {
        tolua_function(L,"setUniformPointLightPosition",lua_cc_base_Pass_setUniformPointLightPosition);
        tolua_function(L,"setUniformDirLightDir",lua_cc_base_Pass_setUniformDirLightDir);
        tolua_function(L,"getVertexAttributeBinding",lua_cc_base_Pass_getVertexAttributeBinding);
        tolua_function(L,"setUniformSpotLightOuterAngleCos",lua_cc_base_Pass_setUniformSpotLightOuterAngleCos);
        tolua_function(L,"setUniformSpotLightDir",lua_cc_base_Pass_setUniformSpotLightDir);
        tolua_function(L,"setUniformMatrixPalette",lua_cc_base_Pass_setUniformMatrixPalette);
        tolua_function(L,"setUniformSpotLightRangeInverse",lua_cc_base_Pass_setUniformSpotLightRangeInverse);
        tolua_function(L,"draw",lua_cc_base_Pass_draw);
        tolua_function(L,"setUniformPointLightRangeInverse",lua_cc_base_Pass_setUniformPointLightRangeInverse);
        tolua_function(L,"updateMVPUniform",lua_cc_base_Pass_updateMVPUniform);
        tolua_function(L,"setUniformSpotLightColor",lua_cc_base_Pass_setUniformSpotLightColor);
        tolua_function(L,"setUniformAmbientLigthColor",lua_cc_base_Pass_setUniformAmbientLigthColor);
        tolua_function(L,"setUniformDirLightColor",lua_cc_base_Pass_setUniformDirLightColor);
        tolua_function(L,"setUniformSpotLightPosition",lua_cc_base_Pass_setUniformSpotLightPosition);
        tolua_function(L,"setVertexAttribBinding",lua_cc_base_Pass_setVertexAttribBinding);
        tolua_function(L,"setUniformSpotLightInnerAngleCos",lua_cc_base_Pass_setUniformSpotLightInnerAngleCos);
        tolua_function(L,"setUniformColor",lua_cc_base_Pass_setUniformColor);
        tolua_function(L,"setUniformPointLightColor",lua_cc_base_Pass_setUniformPointLightColor);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Renderer");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_Renderer_constructor);
        tolua_function(L,"setDepthStencilDesc",lua_cc_base_Renderer_setDepthStencilDesc);
        tolua_function(L,"getViewport",lua_cc_base_Renderer_getViewport);
        tolua_function(L,"addCallbackCommand",lua_cc_base_Renderer_addCallbackCommand);
        tolua_function(L,"getRenderTarget",lua_cc_base_Renderer_getRenderTarget);
        tolua_function(L,"addCommand",lua_cc_base_Renderer_addCommand);
        tolua_function(L,"addDrawnVertices",lua_cc_base_Renderer_addDrawnVertices);
        tolua_function(L,"getDepthStencilDesc",lua_cc_base_Renderer_getDepthStencilDesc);
        tolua_function(L,"getScissorRect",lua_cc_base_Renderer_getScissorRect);
        tolua_function(L,"addDrawnBatches",lua_cc_base_Renderer_addDrawnBatches);
        tolua_function(L,"nextCallbackCommand",lua_cc_base_Renderer_nextCallbackCommand);
        tolua_function(L,"checkVisibility",lua_cc_base_Renderer_checkVisibility);
        tolua_function(L,"getNextGroupCommand",lua_cc_base_Renderer_getNextGroupCommand);
        tolua_function(L,"getClearColor",lua_cc_base_Renderer_getClearColor);
        tolua_function(L,"getOffscreenRenderTarget",lua_cc_base_Renderer_getOffscreenRenderTarget);
        tolua_function(L,"clear",lua_cc_base_Renderer_clear);
        tolua_function(L,"setRenderTarget",lua_cc_base_Renderer_setRenderTarget);
        tolua_function(L,"readPixels",lua_cc_base_Renderer_readPixels);
        tolua_function(L,"getDefaultRenderTarget",lua_cc_base_Renderer_getDefaultRenderTarget);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TextureCache");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TextureCache_constructor);
        tolua_function(L,"addImage",lua_cc_base_TextureCache_addImage);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.Application");
    if (lua_istable(L,-1)) {
        tolua_function(L,"getTargetPlatform",lua_cc_base_Application_getTargetPlatform);
        tolua_function(L,"getCurrentLanguage",lua_cc_base_Application_getCurrentLanguage);
        tolua_function(L,"getCurrentLanguageCode",lua_cc_base_Application_getCurrentLanguageCode);
        tolua_function(L,"openURL",lua_cc_base_Application_openURL);
        tolua_function(L,"getVersion",lua_cc_base_Application_getVersion);
        tolua_function(L,"setAnimationInterval",lua_cc_base_Application_setAnimationInterval);
        tolua_function(L,"getInstance",lua_cc_base_Application_getInstance);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.AnimationCache");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_AnimationCache_constructor);
        tolua_function(L,"addAnimationsWithDictionary",lua_cc_base_AnimationCache_addAnimationsWithDictionary);
        tolua_function(L,"addAnimations",lua_cc_base_AnimationCache_addAnimationsWithFile);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.SpriteBatchNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_SpriteBatchNode_constructor);
        tolua_function(L,"getTexture",lua_cc_base_SpriteBatchNode_getTexture);
        tolua_function(L,"setTexture",lua_cc_base_SpriteBatchNode_setTexture);
        tolua_function(L,"removeChildAtIndex",lua_cc_base_SpriteBatchNode_removeChildAtIndex);
        tolua_function(L,"getBlendFunc",lua_cc_base_SpriteBatchNode_getBlendFunc);
        tolua_function(L,"initWithTexture",lua_cc_base_SpriteBatchNode_initWithTexture);
        tolua_function(L,"setTextureAtlas",lua_cc_base_SpriteBatchNode_setTextureAtlas);
        tolua_function(L,"reserveCapacity",lua_cc_base_SpriteBatchNode_reserveCapacity);
        tolua_function(L,"removeAllChildrenWithCleanup",lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup);
        tolua_function(L,"insertQuadFromSprite",lua_cc_base_SpriteBatchNode_insertQuadFromSprite);
        tolua_function(L,"initWithFile",lua_cc_base_SpriteBatchNode_initWithFile);
        tolua_function(L,"setBlendFunc",lua_cc_base_SpriteBatchNode_setBlendFunc);
        tolua_function(L,"rebuildIndexInOrder",lua_cc_base_SpriteBatchNode_rebuildIndexInOrder);
        tolua_function(L,"getTextureAtlas",lua_cc_base_SpriteBatchNode_getTextureAtlas);
        tolua_function(L,"create",lua_cc_base_SpriteBatchNode_create);
        tolua_function(L,"createWithTexture",lua_cc_base_SpriteBatchNode_createWithTexture);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ParallaxNode");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ParallaxNode_constructor);
        tolua_function(L,"addChild",lua_cc_base_ParallaxNode_addChild);
        tolua_function(L,"removeAllChildrenWithCleanup",lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXObjectGroup");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXObjectGroup_constructor);
        tolua_function(L,"setPositionOffset",lua_cc_base_TMXObjectGroup_setPositionOffset);
        tolua_function(L,"getProperty",lua_cc_base_TMXObjectGroup_getProperty);
        tolua_function(L,"getPositionOffset",lua_cc_base_TMXObjectGroup_getPositionOffset);
        tolua_function(L,"getObject",lua_cc_base_TMXObjectGroup_getObject);
        tolua_function(L,"getObjects",lua_cc_base_TMXObjectGroup_getObjects);
        tolua_function(L,"getProperties",lua_cc_base_TMXObjectGroup_getProperties);
        tolua_function(L,"setProperties",lua_cc_base_TMXObjectGroup_setProperties);
        tolua_function(L,"setObjects",lua_cc_base_TMXObjectGroup_setObjects);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXLayerInfo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXLayerInfo_constructor);
        tolua_function(L,"setProperties",lua_cc_base_TMXLayerInfo_setProperties);
        tolua_function(L,"getProperties",lua_cc_base_TMXLayerInfo_getProperties);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXTilesetInfo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXTilesetInfo_constructor);
        tolua_function(L,"getRectForGID",lua_cc_base_TMXTilesetInfo_getRectForGID);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXMapInfo");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXMapInfo_constructor);
        tolua_function(L,"setTileSize",lua_cc_base_TMXMapInfo_setTileSize);
        tolua_function(L,"setObjectGroups",lua_cc_base_TMXMapInfo_setObjectGroups);
        tolua_function(L,"setLayers",lua_cc_base_TMXMapInfo_setLayers);
        tolua_function(L,"getLayers",lua_cc_base_TMXMapInfo_getLayers);
        tolua_function(L,"getTilesets",lua_cc_base_TMXMapInfo_getTilesets);
        tolua_function(L,"getTileSize",lua_cc_base_TMXMapInfo_getTileSize);
        tolua_function(L,"getTileProperties",lua_cc_base_TMXMapInfo_getTileProperties);
        tolua_function(L,"getObjectGroups",lua_cc_base_TMXMapInfo_getObjectGroups);
        tolua_function(L,"setProperties",lua_cc_base_TMXMapInfo_setProperties);
        tolua_function(L,"setTileProperties",lua_cc_base_TMXMapInfo_setTileProperties);
        tolua_function(L,"setMapSize",lua_cc_base_TMXMapInfo_setMapSize);
        tolua_function(L,"getMapSize",lua_cc_base_TMXMapInfo_getMapSize);
        tolua_function(L,"setTilesets",lua_cc_base_TMXMapInfo_setTilesets);
        tolua_function(L,"getProperties",lua_cc_base_TMXMapInfo_getProperties);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TileMapAtlas");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TileMapAtlas_constructor);
        tolua_function(L,"getTileAt",lua_cc_base_TileMapAtlas_getTileAt);
        tolua_function(L,"setTile",lua_cc_base_TileMapAtlas_setTile);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FastTMXLayer");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FastTMXLayer_constructor);
        tolua_function(L,"getAnimTileCoord",lua_cc_base_FastTMXLayer_getAnimTileCoord);
        tolua_function(L,"getPositionAt",lua_cc_base_FastTMXLayer_getPositionAt);
        tolua_function(L,"getLayerSize",lua_cc_base_FastTMXLayer_getLayerSize);
        tolua_function(L,"setMapTileSize",lua_cc_base_FastTMXLayer_setMapTileSize);
        tolua_function(L,"setProperties",lua_cc_base_FastTMXLayer_setProperties);
        tolua_function(L,"removeTileAt",lua_cc_base_FastTMXLayer_removeTileAt);
        tolua_function(L,"getProperties",lua_cc_base_FastTMXLayer_getProperties);
        tolua_function(L,"setupTileSprite",lua_cc_base_FastTMXLayer_setupTileSprite);
        tolua_function(L,"setTileGID",lua_cc_base_FastTMXLayer_setTileGID);
        tolua_function(L,"getMapTileSize",lua_cc_base_FastTMXLayer_getMapTileSize);
        tolua_function(L,"getProperty",lua_cc_base_FastTMXLayer_getProperty);
        tolua_function(L,"setLayerSize",lua_cc_base_FastTMXLayer_setLayerSize);
        tolua_function(L,"getTileAt",lua_cc_base_FastTMXLayer_getTileAt);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXTileAnimTask");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXTileAnimTask_constructor);
        tolua_function(L,"create",lua_cc_base_TMXTileAnimTask_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.TMXTileAnimManager");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_TMXTileAnimManager_constructor);
        tolua_function(L,"getTasks",lua_cc_base_TMXTileAnimManager_getTasks);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.FastTMXTiledMap");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_FastTMXTiledMap_constructor);
        tolua_function(L,"setObjectGroups",lua_cc_base_FastTMXTiledMap_setObjectGroups);
        tolua_function(L,"getProperty",lua_cc_base_FastTMXTiledMap_getProperty);
        tolua_function(L,"setMapSize",lua_cc_base_FastTMXTiledMap_setMapSize);
        tolua_function(L,"getObjectGroups",lua_cc_base_FastTMXTiledMap_getObjectGroups);
        tolua_function(L,"getTileSize",lua_cc_base_FastTMXTiledMap_getTileSize);
        tolua_function(L,"getMapSize",lua_cc_base_FastTMXTiledMap_getMapSize);
        tolua_function(L,"getProperties",lua_cc_base_FastTMXTiledMap_getProperties);
        tolua_function(L,"getPropertiesForGID",lua_cc_base_FastTMXTiledMap_getPropertiesForGID);
        tolua_function(L,"setTileSize",lua_cc_base_FastTMXTiledMap_setTileSize);
        tolua_function(L,"setProperties",lua_cc_base_FastTMXTiledMap_setProperties);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.MotionStreak3D");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_MotionStreak3D_constructor);
        tolua_function(L,"setTexture",lua_cc_base_MotionStreak3D_setTexture);
        tolua_function(L,"getTexture",lua_cc_base_MotionStreak3D_getTexture);
        tolua_function(L,"tintWithColor",lua_cc_base_MotionStreak3D_tintWithColor);
        tolua_function(L,"getSweepAxis",lua_cc_base_MotionStreak3D_getSweepAxis);
        tolua_function(L,"setBlendFunc",lua_cc_base_MotionStreak3D_setBlendFunc);
        tolua_function(L,"getBlendFunc",lua_cc_base_MotionStreak3D_getBlendFunc);
        tolua_function(L,"initWithFade",lua_cc_base_MotionStreak3D_initWithFade);
        tolua_function(L,"setSweepAxis",lua_cc_base_MotionStreak3D_setSweepAxis);
        tolua_function(L,"create",lua_cc_base_MotionStreak3D_create);
    }
    lua_pop(L,1);
    luaL_getmetatable(L,"cc.ComponentLua");
    if (lua_istable(L,-1)) {
        tolua_function(L,"new",lua_cc_base_ComponentLua_constructor);
        tolua_function(L,"getScriptObject",lua_cc_base_ComponentLua_getScriptObject);
        tolua_function(L,"update",lua_cc_base_ComponentLua_update);
    }
    lua_pop(L,1);
    return 0;
}
