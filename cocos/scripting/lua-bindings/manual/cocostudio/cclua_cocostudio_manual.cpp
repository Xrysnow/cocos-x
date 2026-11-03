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
#include "scripting/lua-bindings/manual/cocostudio/cclua_cocostudio_manual.hpp"
#include "scripting/lua-bindings/auto/cclua_studio_auto.hpp"
#include "scripting/lua-bindings/auto/cclua_csloader_auto.hpp"
#include "scripting/lua-bindings/manual/cocostudio/cclua_csloader_manual.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/base/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "CocoStudio.h"
#include "ActionTimeline/CCActionTimelineCache.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/cocostudio/CustomGUIReader.h"

using namespace cocostudio;

class LuaArmatureWrapper : public Ref
{
public:
    LuaArmatureWrapper();
    virtual ~LuaArmatureWrapper();

    virtual void addArmatureFileInfoAsyncCallback(float percent);
};

LuaArmatureWrapper::LuaArmatureWrapper() {}

LuaArmatureWrapper::~LuaArmatureWrapper() {}

void LuaArmatureWrapper::addArmatureFileInfoAsyncCallback(float percent)
{
    int handler =
        ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);

    if (0 != handler)
    {
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FILE_ASYNC,
                                                (void*)&percent);

        BasicScriptData data(this, (void*)&wrapperData);

        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ARMATURE_EVENT, (void*)&data);
    }
}

static int cclua_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc                  = 0;
    ArmatureDataManager* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccs.ArmatureDataManager", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<ArmatureDataManager*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,
                    "invalid 'self' in function 'cclua_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc'\n",
                    NULL);
        return 0;
    }
#endif
    argc = lua_gettop(L) - 1;

    if (2 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) || !toluafix_isfunction(L, 3, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* configFilePath = tolua_tostring(L, 2, "");
        LUA_FUNCTION handler       = (toluafix_ref_function(L, 3, 0));

        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler,
                                                          ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);

        self->addArmatureFileInfoAsync(configFilePath, wrapper,
                                       CC_SCHEDULE_SELECTOR(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));

        return 0;
    }
    else if (4 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err) || !tolua_isstring(L, 3, 0, &tolua_err) ||
            !tolua_isstring(L, 4, 0, &tolua_err) || !toluafix_isfunction(L, 5, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* imagePath      = tolua_tostring(L, 2, "");
        const char* plistPath      = tolua_tostring(L, 3, "");
        const char* configFilePath = tolua_tostring(L, 4, "");

        LUA_FUNCTION handler = (toluafix_ref_function(L, 5, 0));

        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler,
                                                          ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);

        self->addArmatureFileInfoAsync(imagePath, plistPath, configFilePath, wrapper,
                                       CC_SCHEDULE_SELECTOR(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));

        return 0;
    }

    luaL_error(L,
               "'addArmatureFileInfoAsync' function of ArmatureDataManager has wrong number of arguments: %d, was "
               "expecting %d\n",
               argc, 1);

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'addArmatureFileInfoAsync'.", &tolua_err);
#endif
    return 0;
}

static void extendArmatureDataManager(lua_State* L)
{
    lua_pushstring(L, "ccs.ArmatureDataManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "addArmatureFileInfoAsync",
                       cclua_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc);
    }
    lua_pop(L, 1);
}

static int cclua_extension_Bone_setIgnoreMovementBoneData(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc               = 0;
    cocostudio::Bone* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccs.Bone", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocostudio::Bone*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_extension_Bone_setIgnoreMovementBoneData'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if CC_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool ignore = (bool)tolua_toboolean(L, 2, 0);
        self->setIgnoreMovementBoneData(ignore);
        return 0;
    }

    luaL_error(L, "'setIgnoreMovementBoneData' function of Bone  has wrong number of arguments: %d, was expecting %d\n",
               argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'setIgnoreMovementBoneData'.", &tolua_err);
    return 0;
#endif
}

static int cclua_extension_Bone_getIgnoreMovementBoneData(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc               = 0;
    cocostudio::Bone* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccs.Bone", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = static_cast<cocostudio::Bone*>(tolua_tousertype(L, 1, 0));

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_extension_Bone_getIgnoreMovementBoneData'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (0 == argc)
    {
        tolua_pushboolean(L, self->getIgnoreMovementBoneData());
        return 1;
    }

    luaL_error(L, "'getIgnoreMovementBoneData' function of Bone  has wrong number of arguments: %d, was expecting %d\n",
               argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'getIgnoreMovementBoneData'.", &tolua_err);
    return 0;
#endif
}

static void extendBone(lua_State* L)
{
    lua_pushstring(L, "ccs.Bone");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "setIgnoreMovementBoneData", cclua_extension_Bone_setIgnoreMovementBoneData);
        tolua_function(L, "getIgnoreMovementBoneData", cclua_extension_Bone_getIgnoreMovementBoneData);
    }
    lua_pop(L, 1);
}

int cclua_studio_ActionTimelineCache_getInstance(lua_State* L)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(L, 1, "ccs.ActionTimelineCache", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    if (argc == 0)
    {
        if (!ok)
            return 0;
        cocostudio::timeline::ActionTimelineCache* ret = cocostudio::timeline::ActionTimelineCache::getInstance();
        tolua_pushusertype(L, (void*)ret, "ccs.ActionTimelineCache");
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:getInstance",
               argc, 0);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_studio_ActionTimelineCache_getInstance'.", &tolua_err);
#endif
    return 0;
}

static void extendActionTimelineCache(lua_State* L)
{
    lua_pushstring(L, "ccs.ActionTimelineCache");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "getInstance", cclua_studio_ActionTimelineCache_getInstance);
    }
    lua_pop(L, 1);
}

int cclua_CustomGUIReader_create(lua_State* L)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(L, 1, "ccs.CustomGUIReader", 0, &tolua_err))
        goto tolua_lerror;
#endif

    argc = lua_gettop(L) - 1;

    do
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(L, 2, &arg0, "ccs.CustomGUIReader:create");
            if (!ok)
            {
                break;
            }
#if CC_DEBUG >= 1
            if (!toluafix_isfunction(L, 3, "LUA_FUNCTION", 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            LUA_FUNCTION arg1 = toluafix_ref_function(L, 3, 0);
#if CC_DEBUG >= 1
            if (!toluafix_isfunction(L, 4, "LUA_FUNCTION", 0, &tolua_err))
            {
                goto tolua_lerror;
            }
#endif
            LUA_FUNCTION arg2 = toluafix_ref_function(L, 4, 0);

            cocostudio::CustomGUIReader* ret = cocostudio::CustomGUIReader::create(arg0, arg1, arg2);
            object_to_luaval<cocostudio::CustomGUIReader>(L, "ccs.CustomGUIReader", (cocostudio::CustomGUIReader*)ret);
            return 1;
        }
    } while (0);
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d", "ccs.CustomGUIReader:create", argc, 1);
    return 0;
#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_CustomGUIReader_create'.", &tolua_err);
#endif
    return 0;
}

int register_all_cc_coco_studio_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendArmatureDataManager(L);
    extendBone(L);
    extendActionTimelineCache(L);

    return 0;
}

int lua_register_cc_coco_studio_CustomGUIReader(lua_State* L)
{
    tolua_module(L, "ccs", 0);
    tolua_beginmodule(L, "ccs");

    tolua_usertype(L, "ccs.CustomGUIReader");
    tolua_cclass(L, "CustomGUIReader", "ccs.CustomGUIReader", "cc.Ref", nullptr);

    tolua_beginmodule(L, "CustomGUIReader");
    tolua_function(L, "create", cclua_CustomGUIReader_create);
    tolua_endmodule(L);
    auto typeName                                    = typeid(cocostudio::CustomGUIReader).name();
    g_luaType[reinterpret_cast<uintptr_t>(typeName)] = "ccs.CustomGUIReader";
    g_typeCast[typeName]                             = "ccs.CustomGUIReader";

    tolua_endmodule(L);
    return 1;
}

int register_cocostudio_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L, -1))  // stack:...,_G,
    {
        register_all_cc_studio(L);
        register_all_cc_csloader(L);
        register_all_cc_coco_studio_manual(L);
        register_all_cc_csloader_manual(L);
        lua_register_cc_coco_studio_CustomGUIReader(L);
    }
    lua_pop(L, 1);
    return 1;
}
