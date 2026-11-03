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
#include "scripting/lua-bindings/manual/extension/cclua_extension_manual.h"
#include "scripting/lua-bindings/auto/cclua_extension_auto.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "assets-manager/AssetsManager.h"
#include "assets-manager/AssetsManagerEx.h"
#include "assets-manager/Manifest.h"
#include "assets-manager/CCEventAssetsManagerEx.h"
#include "assets-manager/CCEventListenerAssetsManagerEx.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/base/LuaScriptHandlerMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LuaAssetsManagerDelegateProtocol : public Ref, public AssetsManagerDelegateProtocol
{
public:
    virtual ~LuaAssetsManagerDelegateProtocol() {}

    virtual void onProgress(int percent) override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(
            (void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData(percent);
            BasicScriptData data((void*)this, &eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS, (void*)&data);
        }
    }

    virtual void onSuccess() override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(
            (void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData;
            BasicScriptData data((void*)this, &eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS, (void*)&data);
        }
    }

    virtual void onError(AssetsManager::ErrorCode errorCode) override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(
            (void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData((int)errorCode);
            BasicScriptData data((void*)this, &eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR, (void*)&data);
        }
    }
};

static int cclua_AssetsManager_setDelegate(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc            = 0;
    AssetsManager* self = nullptr;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.AssetsManager", 0, &tolua_err))
        goto tolua_lerror;
#endif

    self = (AssetsManager*)tolua_tousertype(L, 1, 0);

#if CC_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L, "invalid 'self' in function 'cclua_AssetsManager_setDelegate'\n", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(L) - 1;

    if (2 == argc)
    {
#if CC_DEBUG >= 1
        if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err) || !tolua_isnumber(L, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaAssetsManagerDelegateProtocol* delegate =
            dynamic_cast<LuaAssetsManagerDelegateProtocol*>(self->getDelegate());
        if (nullptr == delegate)
        {
            delegate = new LuaAssetsManagerDelegateProtocol();
            self->setUserObject(delegate);
            self->setDelegate(delegate);
            delegate->release();
        }

        LUA_FUNCTION handler                      = toluafix_ref_function(L, 2, 0);
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)(
            (int)tolua_tonumber(L, 3, 0) + (int)ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS);

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)delegate, handler, handlerType);
        return 0;
    }

    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.AssetsManager:setDelegate", argc, 2);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'cclua_AssetsManager_setDelegate'.", &tolua_err);
    return 0;
#endif
}

static void extendAssetsManager(lua_State* L)
{
    lua_pushstring(L, "cc.AssetsManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "setDelegate", cclua_AssetsManager_setDelegate);
    }
    lua_pop(L, 1);
}

static void extendManifest(lua_State* L)
{
    lua_pushstring(L, "cc.Manifest");
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pop(L, 1);
}

int cclua_extension_ParticleSystem3D_getParticlePool(lua_State* tolua_S)
{
    int argc                        = 0;
    cocos2d::ParticleSystem3D* cobj = nullptr;
    bool ok                         = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.ParticleSystem3D", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem3D*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_extension_ParticleSystem3D_getParticlePool'",
                    nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if (!ok)
        {
            tolua_error(tolua_S,
                        "invalid arguments in function 'cclua_extension_ParticleSystem3D_getParticlePool'",
                        nullptr);
            return 0;
        }
        const cocos2d::ParticlePool& ret = cobj->getParticlePool();
        tolua_pushusertype(tolua_S, (void*)&ret, "cc.ParticlePool");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",
               "cc.ParticleSystem3D:getParticlePool", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_extension_ParticleSystem3D_getParticlePool'.", &tolua_err);
#endif

    return 0;
}

static void extendParticleSystem3D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ParticleSystem3D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "getParticlePool", cclua_extension_ParticleSystem3D_getParticlePool);
    }
    lua_pop(tolua_S, 1);
}

int cclua_extension_ParticlePool_getActiveDataList(lua_State* tolua_S)
{
    int argc                    = 0;
    cocos2d::ParticlePool* cobj = nullptr;
    bool ok                     = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "cc.ParticlePool", 0, &tolua_err))
        goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticlePool*)tolua_tousertype(tolua_S, 1, 0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S, "invalid 'cobj' in function 'cclua_extension_ParticlePool_getActiveDataList'",
                    nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (argc == 0)
    {
        if (!ok)
        {
            tolua_error(tolua_S,
                        "invalid arguments in function 'cclua_extension_ParticlePool_getActiveDataList'",
                        nullptr);
            return 0;
        }
        const ParticlePool::PoolList& ret = cobj->getActiveDataList();

        lua_newtable(tolua_S);
        if (ret.empty())
            return 1;

        int index = 1;
        for (const auto& obj : ret)
        {
            if (nullptr == obj)
                continue;

            lua_pushnumber(tolua_S, (lua_Number)index);
            tolua_pushusertype(tolua_S, (void*)&ret, "cc.ParticlePool");
            lua_rawset(tolua_S, -3);
            ++index;
        }

        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",
               "cc.ParticlePool:getActiveParticleList", argc, 0);
    return 0;

#if CC_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'cclua_extension_ParticlePool_getActiveParticleList'.",
                &tolua_err);
#endif

    return 0;
}

static void extendParticlePool(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ParticlePool");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        tolua_function(tolua_S, "getActiveDataList", cclua_extension_ParticlePool_getActiveDataList);
    }
    lua_pop(tolua_S, 1);
}


// Legacy constructors, unsupported callback stubs and special conversions.
static int lua_cc_extension_AssetsManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 1)
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 2)
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 3)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:AssetsManager"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:AssetsManager",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_AssetsManager_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_AssetsManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        std::function<void (int)> arg3;
        std::function<void (int)> arg4;
        std::function<void ()> arg5;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:create"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:create"); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:create"); arg2 = arg2_tmp.c_str();
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManager_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::extension::AssetsManager::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::extension::AssetsManager>(tolua_S, "cc.AssetsManager",(cocos2d::extension::AssetsManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManager:create",argc, 6);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_AssetsManager_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cc_extension_EventAssetsManagerEx_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 4)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 5)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;
        double arg4;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 6)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;
        double arg4;
        std::string_view arg5;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 7,&arg5, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 7)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;
        double arg4;
        std::string_view arg5;
        std::string_view arg6;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 7,&arg5, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 8,&arg6, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 8)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;
        double arg4;
        std::string_view arg5;
        std::string_view arg6;
        int arg7;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 7,&arg5, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 8,&arg6, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    if (argc == 9)
    {
        std::string_view arg0;
        cocos2d::extension::AssetsManagerEx* arg1;
        cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
        double arg3;
        double arg4;
        std::string_view arg5;
        std::string_view arg6;
        int arg7;
        int arg8;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_object<cocos2d::extension::AssetsManagerEx>(tolua_S, 3, "cc.AssetsManagerEx",&arg1, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 7,&arg5, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 8,&arg6, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "cc.EventAssetsManagerEx:EventAssetsManagerEx");

        ok &= luaval_to_int32(tolua_S, 10,(int *)&arg8, "cc.EventAssetsManagerEx:EventAssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventAssetsManagerEx");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventAssetsManagerEx:EventAssetsManagerEx",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_EventAssetsManagerEx_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_AssetsManagerEx_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.AssetsManagerEx:AssetsManagerEx");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.AssetsManagerEx:AssetsManagerEx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManagerEx(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManagerEx");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:AssetsManagerEx",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_AssetsManagerEx_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_AssetsManagerEx_setVerifyCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_AssetsManagerEx_setVerifyCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::function<bool (std::string_view, cocos2d::extension::ManifestAsset)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManagerEx_setVerifyCallback'", nullptr);
            return 0;
        }
        cobj->setVerifyCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:setVerifyCallback",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_AssetsManagerEx_setVerifyCallback'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_AssetsManagerEx_setVersionCompareHandle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_AssetsManagerEx_setVersionCompareHandle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::function<int (std::string_view, std::string_view)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_AssetsManagerEx_setVersionCompareHandle'", nullptr);
            return 0;
        }
        cobj->setVersionCompareHandle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:setVersionCompareHandle",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_AssetsManagerEx_setVersionCompareHandle'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_EventListenerAssetsManagerEx_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventListenerAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventListenerAssetsManagerEx_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::EventListenerAssetsManagerEx();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerAssetsManagerEx");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerAssetsManagerEx:EventListenerAssetsManagerEx",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_EventListenerAssetsManagerEx_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_EventListenerAssetsManagerEx_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::EventListenerAssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventListenerAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::EventListenerAssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_EventListenerAssetsManagerEx_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        const cocos2d::extension::AssetsManagerEx* arg0;
        std::function<void (cocos2d::extension::EventAssetsManagerEx *)> arg1;

        ok &= luaval_to_object<const cocos2d::extension::AssetsManagerEx>(tolua_S, 2, "cc.AssetsManagerEx",&arg0, "cc.EventListenerAssetsManagerEx:init");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_EventListenerAssetsManagerEx_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerAssetsManagerEx:init",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_EventListenerAssetsManagerEx_init'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_ParticleSystem3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_ParticleSystem3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSystem3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSystem3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:ParticleSystem3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_ParticleSystem3D_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_ParticleSystem3D_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_ParticleSystem3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_ParticleSystem3D_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_ParticleSystem3D_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_ParticleSystem3D_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_ParticleSystem3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.ParticleSystem3D:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_ParticleSystem3D_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_ParticleSystem3D_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_PUParticleSystem3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PUParticleSystem3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_PUParticleSystem3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::PUParticleSystem3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.PUParticleSystem3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:PUParticleSystem3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_PUParticleSystem3D_constructor'.",&tolua_err);
#endif

    return 0;
}
static int lua_cc_extension_PUParticleSystem3D_rotationOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PUParticleSystem3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PUParticleSystem3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PUParticleSystem3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_extension_PUParticleSystem3D_rotationOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.PUParticleSystem3D:rotationOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_extension_PUParticleSystem3D_rotationOffset'", nullptr);
            return 0;
        }
        cobj->rotationOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PUParticleSystem3D:rotationOffset",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_extension_PUParticleSystem3D_rotationOffset'.",&tolua_err);
#endif

    return 0;
}

static void extendRetainedExtension(lua_State* L)
{
    luaL_getmetatable(L, "cc.AssetsManager");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_AssetsManager_constructor);
        tolua_function(L, "create", lua_cc_extension_AssetsManager_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "cc.EventAssetsManagerEx");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_EventAssetsManagerEx_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "cc.AssetsManagerEx");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_AssetsManagerEx_constructor);
        tolua_function(L, "setVerifyCallback", lua_cc_extension_AssetsManagerEx_setVerifyCallback);
        tolua_function(L, "setVersionCompareHandle", lua_cc_extension_AssetsManagerEx_setVersionCompareHandle);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "cc.EventListenerAssetsManagerEx");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_EventListenerAssetsManagerEx_constructor);
        tolua_function(L, "init", lua_cc_extension_EventListenerAssetsManagerEx_init);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "cc.ParticleSystem3D");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_ParticleSystem3D_constructor);
        tolua_function(L, "getBlendFunc", lua_cc_extension_ParticleSystem3D_getBlendFunc);
        tolua_function(L, "setBlendFunc", lua_cc_extension_ParticleSystem3D_setBlendFunc);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "cc.PUParticleSystem3D");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_extension_PUParticleSystem3D_constructor);
        tolua_function(L, "rotationOffset", lua_cc_extension_PUParticleSystem3D_rotationOffset);
    }
    lua_pop(L, 1);
}

int register_all_cc_extension_manual(lua_State* tolua_S)
{
    extendRetainedExtension(tolua_S);
    extendAssetsManager(tolua_S);
    extendManifest(tolua_S);
    extendParticleSystem3D(tolua_S);
    extendParticlePool(tolua_S);
    return 0;
}

int register_extension_module(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S, -1))  // stack:...,_G,
    {
        register_all_cc_extension(tolua_S);
        register_all_cc_extension_manual(tolua_S);
    }
    lua_pop(tolua_S, 1);
    return 1;
}
