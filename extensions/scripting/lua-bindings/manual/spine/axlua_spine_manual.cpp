/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "scripting/lua-bindings/manual/spine/axlua_spine_manual.hpp"
#include "scripting/lua-bindings/auto/axlua_spine_auto.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/base/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "spine/spine.h"
#include "spine/spine-cocos2dx.h"
#include "scripting/lua-bindings/manual/spine/LuaSkeletonAnimation.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

using namespace spine;

static int axlua_CCSkeletonAnimation_createWithFile(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;

#if _CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "sp.SkeletonAnimation", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    if (2 == argc)
    {
#if _CC_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) || !tolua_isstring(L, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* skeletonDataFile = tolua_tostring(L, 2, "");
        const char* atlasFile        = tolua_tostring(L, 3, "");

        auto tolua_ret = LuaSkeletonAnimation::createWithFile(skeletonDataFile, atlasFile);

        int nID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(L, nID, pLuaID, (void*)tolua_ret, "sp.SkeletonAnimation");
        return 1;
    }
    else if (3 == argc)
    {
#if _CC_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) || !tolua_isstring(L, 3, 0, &tolua_err) ||
            !tolua_isnumber(L, 4, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* skeletonDataFile = tolua_tostring(L, 2, "");
        const char* atlasFile        = tolua_tostring(L, 3, "");
        LUA_NUMBER scale             = tolua_tonumber(L, 4, 1);

        auto tolua_ret = LuaSkeletonAnimation::createWithFile(skeletonDataFile, atlasFile, scale);

        int nID     = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(L, nID, pLuaID, (void*)tolua_ret, "sp.SkeletonAnimation");
        return 1;
    }

    luaL_error(L,
               "'createWithFile' function of SkeletonAnimation has wrong number of arguments: %d, was expecting %d\n",
               argc, 2);

#if _CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'createWithFile'.", &tolua_err);
#endif
    return 0;
}

int executeSpineEvent(LuaSkeletonAnimation* skeletonAnimation,
                      int handler,
                      spine::EventType eventType,
                      spine::TrackEntry* entry,
                      spine::Event* event = nullptr)
{
    if (nullptr == skeletonAnimation || 0 == handler)
        return 0;

    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    if (nullptr == stack)
        return 0;

    lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    if (nullptr == L)
        return 0;

    int ret = 0;

    std::string animationName = (entry && entry->getAnimation()) ? entry->getAnimation()->getName().buffer() : "";
    std::string eventTypeName = "";

    switch (eventType)
    {
    case spine::EventType::EventType_Start:
    {
        eventTypeName = "start";
    }
    break;
    case spine::EventType::EventType_Interrupt:
    {
        eventTypeName = "interrupt";
    }
    break;
    case spine::EventType::EventType_End:
    {
        eventTypeName = "end";
    }
    break;
    case spine::EventType::EventType_Dispose:
    {
        eventTypeName = "dispose";
    }
    break;
    case spine::EventType::EventType_Complete:
    {
        eventTypeName = "complete";
    }
    break;
    case spine::EventType::EventType_Event:
    {
        eventTypeName = "event";
    }
    break;

    default:
        break;
    }

    LuaValueDict spineEvent;
    spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("type", LuaValue::stringValue(eventTypeName)));
    spineEvent.insert(spineEvent.end(),
                      LuaValueDict::value_type("trackIndex", LuaValue::intValue(entry->getTrackIndex())));
    spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("animation", LuaValue::stringValue(animationName)));
    spineEvent.insert(spineEvent.end(),
                      LuaValueDict::value_type("loopCount", LuaValue::intValue(std::floor(entry->getTrackTime() /
                                                                                          entry->getAnimationEnd()))));

    if (nullptr != event)
    {
        LuaValueDict eventData;
        eventData.insert(eventData.end(),
                         LuaValueDict::value_type("name", LuaValue::stringValue(event->getData().getName().buffer())));
        eventData.insert(eventData.end(),
                         LuaValueDict::value_type("intValue", LuaValue::intValue(event->getData().getIntValue())));
        eventData.insert(eventData.end(), LuaValueDict::value_type(
                                              "floatValue", LuaValue::floatValue(event->getData().getFloatValue())));
        eventData.insert(
            eventData.end(),
            LuaValueDict::value_type("stringValue", LuaValue::stringValue(event->getData().getStringValue().buffer())));
        spineEvent.insert(spineEvent.end(), LuaValueDict::value_type("eventData", LuaValue::dictValue(eventData)));
    }

    stack->pushLuaValueDict(spineEvent);
    ret = stack->executeFunctionByHandler(handler, 1);
    return ret;
}

int tolua_Cocos2d_CCSkeletonAnimation_registerSpineEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "sp.SkeletonAnimation", 0, &tolua_err) ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) || !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S, 4, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        LuaSkeletonAnimation* self = (LuaSkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);
        if (NULL != self)
        {
            int handler                = (toluafix_ref_function(tolua_S, 2, 0));
            spine::EventType eventType = static_cast<spine::EventType>((int)tolua_tonumber(tolua_S, 3, 0));

            switch (eventType)
            {
            case spine::EventType::EventType_Start:
            {
                self->setStartListener(
                    [=](spine::TrackEntry* entry) { executeSpineEvent(self, handler, eventType, entry); });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_START);
            }
            break;
            case spine::EventType::EventType_Interrupt:
            {
                self->setInterruptListener(
                    [=](spine::TrackEntry* entry) { executeSpineEvent(self, handler, eventType, entry); });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_INTERRUPT);
            }
            break;
            case spine::EventType::EventType_End:
            {
                self->setEndListener(
                    [=](spine::TrackEntry* entry) { executeSpineEvent(self, handler, eventType, entry); });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_END);
            }
            break;
            case spine::EventType::EventType_Dispose:
            {
                self->setDisposeListener(
                    [=](spine::TrackEntry* entry) { executeSpineEvent(self, handler, eventType, entry); });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_DISPOSE);
            }
            break;
            case spine::EventType::EventType_Complete:
            {
                self->setCompleteListener(
                    [=](spine::TrackEntry* entry) { executeSpineEvent(self, handler, eventType, entry); });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_COMPLETE);
            }
            break;
            case spine::EventType::EventType_Event:
            {
                self->setEventListener([=](spine::TrackEntry* entry, spine::Event* event) {
                    executeSpineEvent(self, handler, eventType, entry, event);
                });
                ScriptHandlerMgr::getInstance()->addObjectHandler(
                    (void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_EVENT);
            }
            break;
            default:
                break;
            }
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'registerSpineEventHandler'.", &tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_CCSkeletonAnimation_unregisterSpineEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "sp.SkeletonAnimation", 0, &tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err) || !tolua_isnoobj(tolua_S, 3, &tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        LuaSkeletonAnimation* self = (LuaSkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);
        if (NULL != self)
        {
            spine::EventType eventType = static_cast<spine::EventType>((int)tolua_tonumber(tolua_S, 2, 0));
            ScriptHandlerMgr::HandlerType handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_START;
            switch (eventType)
            {
            case spine::EventType::EventType_Start:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_START;
                self->setStartListener(nullptr);
                break;
            case spine::EventType::EventType_Interrupt:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_INTERRUPT;
                break;
            case spine::EventType::EventType_End:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_END;
                self->setEndListener(nullptr);
                break;
            case spine::EventType::EventType_Dispose:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_DISPOSE;
                break;
            case spine::EventType::EventType_Complete:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_COMPLETE;
                self->setCompleteListener(nullptr);
                break;
            case spine::EventType::EventType_Event:
                handlerType = ScriptHandlerMgr::HandlerType::EVENT_SPINE_ANIMATION_EVENT;
                self->setEventListener(nullptr);
                break;

            default:
                break;
            }
            ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'unregisterScriptHandler'.", &tolua_err);
    return 0;
#endif
}

static int axlua_spine_SkeletonAnimation_addAnimation(lua_State* tolua_S)
{
    int argc                       = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok                        = true;

#if _CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if _CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "sp.SkeletonAnimation", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);

#if _CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'axlua_spine_SkeletonAnimation_addAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 3)
    {
        int arg0;
        const char* arg1;
        bool arg2;

        ok &= luaval_to_int32(tolua_S, 2, (int*)&arg0, "sp.SkeletonAnimation:addAnimation");

        std::string arg1_tmp;
        ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "sp.SkeletonAnimation:addAnimation");
        arg1 = arg1_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 4, &arg2, "sp.SkeletonAnimation:addAnimation");
        if (!ok)
            return 0;
        cobj->addAnimation(arg0, arg1, arg2);

        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4)
    {
        int arg0;
        const char* arg1;
        bool arg2;
        double arg3;

        ok &= luaval_to_int32(tolua_S, 2, (int*)&arg0, "sp.SkeletonAnimation:addAnimation");

        std::string arg1_tmp;
        ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "sp.SkeletonAnimation:addAnimation");
        arg1 = arg1_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 4, &arg2, "sp.SkeletonAnimation:addAnimation");

        ok &= luaval_to_number(tolua_S, 5, &arg3, "sp.SkeletonAnimation:addAnimation");
        if (!ok)
            return 0;

        cobj->addAnimation(arg0, arg1, arg2, arg3);

        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "addAnimation", argc, 3);
    return 0;

#if _CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'axlua_spine_SkeletonAnimation_addAnimation'.", &tolua_err);
#endif

    return 0;
}

static int axlua_spine_SkeletonAnimation_setAnimation(lua_State* tolua_S)
{
    int argc                       = 0;
    spine::SkeletonAnimation* cobj = nullptr;
    bool ok                        = true;

#if _CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if _CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "sp.SkeletonAnimation", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);

#if _CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'axlua_spine_SkeletonAnimation_setAnimation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 3)
    {
        int arg0;
        const char* arg1;
        bool arg2;

        ok &= luaval_to_int32(tolua_S, 2, (int*)&arg0, "sp.SkeletonAnimation:setAnimation");

        std::string arg1_tmp;
        ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "sp.SkeletonAnimation:setAnimation");
        arg1 = arg1_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 4, &arg2, "sp.SkeletonAnimation:setAnimation");
        if (!ok)
            return 0;

        cobj->setAnimation(arg0, arg1, arg2);

        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "setAnimation", argc, 3);
    return 0;

#if _CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'axlua_spine_SkeletonAnimation_setAnimation'.", &tolua_err);
#endif

    return 0;
}


static int axlua_spine_SkeletonAnimation_getBoundingBox(lua_State* tolua_S)
{
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);

#if _CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'axlua_spine_SkeletonAnimation_getBoundingBox'", nullptr);
        return 0;
    }
#endif
    Rect rect = cobj->getBoundingBox();
    // return a table
    lua_newtable(tolua_S);
    lua_pushstring(tolua_S, "x");
    lua_pushnumber(tolua_S, rect.origin.x);
    lua_rawset(tolua_S, -3);
    lua_pushstring(tolua_S, "y");
    lua_pushnumber(tolua_S, rect.origin.y);
    lua_rawset(tolua_S, -3);
    lua_pushstring(tolua_S, "width");
    lua_pushnumber(tolua_S, rect.size.width);
    lua_rawset(tolua_S, -3);
    lua_pushstring(tolua_S, "height");
    lua_pushnumber(tolua_S, rect.size.height);
    lua_rawset(tolua_S, -3);
    return 1;
}

static int axlua_spine_SkeletonAnimation_findBone(lua_State* tolua_S)
{
    int argc                       = 0;
    spine::SkeletonAnimation* cobj = nullptr;

#if _CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "sp.SkeletonAnimation", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (spine::SkeletonAnimation*)tolua_tousertype(tolua_S, 1, 0);

#if _CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'axlua_spine_SkeletonAnimation_findBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 1)
    {
        const char* arg0 = lua_tostring(tolua_S, 2);
        if (!arg0)
        {
            tolua_error(tolua_S, "sp.SkeletonAnimation:findBone arg 1 must string", nullptr);
            return 0;
        }

        auto bone = cobj->findBone(arg0);

        lua_newtable(tolua_S);

        if (NULL != bone)
        {
            lua_pushstring(tolua_S, "x");
            lua_pushnumber(tolua_S, bone->getX());
            lua_rawset(tolua_S, -3); /* bone.x */

            lua_pushstring(tolua_S, "y");
            lua_pushnumber(tolua_S, bone->getY());
            lua_rawset(tolua_S, -3); /* bone.y */

            lua_pushstring(tolua_S, "rotation");
            lua_pushnumber(tolua_S, bone->getRotation());
            lua_rawset(tolua_S, -3); /* bone.rotation */

            lua_pushstring(tolua_S, "scaleX");
            lua_pushnumber(tolua_S, bone->getScaleX());
            lua_rawset(tolua_S, -3); /* bone.scaleX */
            lua_pushstring(tolua_S, "scaleY");
            lua_pushnumber(tolua_S, bone->getScaleY());
            lua_rawset(tolua_S, -3); /* bone.scaleY */

            lua_pushstring(tolua_S, "worldX");
            lua_pushnumber(tolua_S, bone->getWorldX());
            lua_rawset(tolua_S, -3); /* bone.worldX */
            lua_pushstring(tolua_S, "worldY");
            lua_pushnumber(tolua_S, bone->getWorldY());
            lua_rawset(tolua_S, -3); /* bone.worldY */
        }
        return 1;
    }
    luaL_error(tolua_S, "findBone has wrong number of arguments: %d, was expecting %d \n", argc, 1);
    return 0;

#if _CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'axlua_spine_SkeletonAnimation_findBone'.", &tolua_err);
#endif

    return 0;
}

static void extendCCSkeletonAnimation(lua_State* L)
{
    lua_pushstring(L, "sp.SkeletonAnimation");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "create", axlua_CCSkeletonAnimation_createWithFile);
        tolua_function(L, "registerSpineEventHandler", tolua_Cocos2d_CCSkeletonAnimation_registerSpineEventHandler00);
        tolua_function(L, "unregisterSpineEventHandler",
                       tolua_Cocos2d_CCSkeletonAnimation_unregisterSpineEventHandler00);
        tolua_function(L, "addAnimation", axlua_spine_SkeletonAnimation_addAnimation);
        tolua_function(L, "setAnimation", axlua_spine_SkeletonAnimation_setAnimation);
        tolua_function(L, "findBone", axlua_spine_SkeletonAnimation_findBone);
        tolua_function(L, "getBoundingBox", axlua_spine_SkeletonAnimation_getBoundingBox);
    }
    lua_pop(L, 1);

    /*Because sp.SkeletonAnimation:create creat a LuaSkeletonAnimation object,so we need use LuaSkeletonAnimation
     * typename for g_luaType*/
    auto typeName                                    = typeid(LuaSkeletonAnimation).name();
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "sp.SkeletonAnimation";
    g_typeCast[typeName]                             = "sp.SkeletonAnimation";
}

int register_all_ax_spine_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendCCSkeletonAnimation(L);

    return 0;
}

int register_spine_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1))  // stack:...,_G,
    {
        register_all_ax_spine(L);
        register_all_ax_spine_manual(L);
    }
    lua_pop(L, 1);

    return 1;
}
