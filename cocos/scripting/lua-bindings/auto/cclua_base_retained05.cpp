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

int lua_cc_base_ParticleSystem_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.ParticleSystem:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getStartColorVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getStartColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getStartColorVar'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartColorVar();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartColorVar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getStartColorVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_createRectTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Size arg1;
        cocos2d::Size arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createRectTorusShape");
        ok &= luaval_to_size(tolua_S, 3, &arg1, "cc.ParticleSystem:createRectTorusShape");
        ok &= luaval_to_size(tolua_S, 4, &arg2, "cc.ParticleSystem:createRectTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createRectTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createRectTorusShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createRectTorusShape",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createRectTorusShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createTorusShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createTorusShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createTorusShape",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createTorusShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createConeShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 5)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createConeShape",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createConeShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createPointShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createPointShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createPointShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createPointShape(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createPointShape",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createPointShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createCircleShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createCircleShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createCircleShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createCircleShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createCircleShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createCircleShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createCircleShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createCircleShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createCircleShape",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createCircleShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createMaskShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 4)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 5)
    {
        std::string_view arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        double arg4;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.ParticleSystem:createMaskShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createMaskShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createMaskShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createMaskShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createMaskShape",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createMaskShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createRectShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Size arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createRectShape");
        ok &= luaval_to_size(tolua_S, 3, &arg1, "cc.ParticleSystem:createRectShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createRectShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createRectShape(arg0, arg1);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createRectShape",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createRectShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_getAllParticleSystems(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getAllParticleSystems'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::getAllParticleSystems();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:getAllParticleSystems",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getAllParticleSystems'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystem_createConeTorusShape(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    if (argc == 6)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        double arg5;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.ParticleSystem:createConeTorusShape");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.ParticleSystem:createConeTorusShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_createConeTorusShape'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ParticleSystem::createConeTorusShape(arg0, arg1, arg2, arg3, arg4, arg5);
        #pragma warning NO CONVERSION FROM NATIVE FOR EmissionShape;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystem:createConeTorusShape",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_createConeTorusShape'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleSystemQuad_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemQuad* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystemQuad_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSystemQuad();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSystemQuad");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemQuad:ParticleSystemQuad",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystemQuad_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystemQuad_setTextureWithRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemQuad* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemQuad",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemQuad*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystemQuad_setTextureWithRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Texture2D* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.ParticleSystemQuad:setTextureWithRect");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.ParticleSystemQuad:setTextureWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystemQuad_setTextureWithRect'", nullptr);
            return 0;
        }
        cobj->setTextureWithRect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemQuad:setTextureWithRect",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystemQuad_setTextureWithRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystemQuad_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystemQuad",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystemQuad:create");
            if (!ok) { break; }
            cocos2d::ParticleSystemQuad* ret = cocos2d::ParticleSystemQuad::create(arg0);
            object_to_luaval<cocos2d::ParticleSystemQuad>(tolua_S, "cc.ParticleSystemQuad",(cocos2d::ParticleSystemQuad*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::ParticleSystemQuad* ret = cocos2d::ParticleSystemQuad::create();
            object_to_luaval<cocos2d::ParticleSystemQuad>(tolua_S, "cc.ParticleSystemQuad",(cocos2d::ParticleSystemQuad*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.ParticleSystemQuad:create");
            if (!ok) { break; }
            cocos2d::ParticleSystemQuad* ret = cocos2d::ParticleSystemQuad::create(arg0);
            object_to_luaval<cocos2d::ParticleSystemQuad>(tolua_S, "cc.ParticleSystemQuad",(cocos2d::ParticleSystemQuad*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.ParticleSystemQuad:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystemQuad_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleFire_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFire* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFire_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleFire();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleFire");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFire:ParticleFire",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFire_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFireworks_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFireworks* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFireworks_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleFireworks();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleFireworks");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFireworks:ParticleFireworks",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFireworks_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFireworks_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFireworks* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleFireworks",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleFireworks*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleFireworks_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFireworks_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFireworks:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFireworks_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFireworks_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFireworks* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleFireworks",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleFireworks*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleFireworks_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleFireworks:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFireworks_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFireworks:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFireworks_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSun_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSun* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSun_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSun();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSun");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSun:ParticleSun",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSun_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSun_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSun* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSun",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSun*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSun_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSun_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSun:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSun_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSun_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSun* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSun",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSun*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSun_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSun:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSun_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSun:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSun_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleGalaxy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleGalaxy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleGalaxy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleGalaxy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleGalaxy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleGalaxy:ParticleGalaxy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleGalaxy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleGalaxy_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleGalaxy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleGalaxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleGalaxy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleGalaxy_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleGalaxy_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleGalaxy:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleGalaxy_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleGalaxy_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleGalaxy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleGalaxy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleGalaxy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleGalaxy_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleGalaxy:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleGalaxy_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleGalaxy:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleGalaxy_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFlower_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFlower* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFlower_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleFlower();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleFlower");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFlower:ParticleFlower",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFlower_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFlower_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFlower* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleFlower",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleFlower*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleFlower_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFlower_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFlower:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFlower_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleFlower_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleFlower* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleFlower",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleFlower*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleFlower_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleFlower:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleFlower_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleFlower:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleFlower_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleMeteor_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleMeteor* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleMeteor_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleMeteor();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleMeteor");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleMeteor:ParticleMeteor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleMeteor_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleMeteor_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleMeteor* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleMeteor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleMeteor*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleMeteor_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleMeteor_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleMeteor:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleMeteor_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleMeteor_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleMeteor* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleMeteor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleMeteor*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleMeteor_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleMeteor:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleMeteor_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleMeteor:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleMeteor_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSpiral_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSpiral* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSpiral_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSpiral();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSpiral");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSpiral:ParticleSpiral",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSpiral_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSpiral_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSpiral* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSpiral",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSpiral*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSpiral_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSpiral_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSpiral:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSpiral_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSpiral_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSpiral* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSpiral",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSpiral*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSpiral_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSpiral:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSpiral_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSpiral:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSpiral_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleExplosion_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleExplosion* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleExplosion_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleExplosion();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleExplosion");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleExplosion:ParticleExplosion",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleExplosion_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleExplosion_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleExplosion* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleExplosion",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleExplosion*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleExplosion_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleExplosion_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleExplosion:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleExplosion_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleExplosion_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleExplosion* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleExplosion",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleExplosion*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleExplosion_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleExplosion:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleExplosion_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleExplosion:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleExplosion_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSmoke_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSmoke* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSmoke_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSmoke();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSmoke");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSmoke:ParticleSmoke",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSmoke_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSmoke_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSmoke* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSmoke",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSmoke*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSmoke_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSmoke_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSmoke:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSmoke_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSmoke_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSmoke* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSmoke",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSmoke*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSmoke_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSmoke:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSmoke_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSmoke:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSmoke_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSnow_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSnow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSnow_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSnow();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSnow");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSnow:ParticleSnow",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSnow_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSnow_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSnow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSnow",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSnow*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSnow_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSnow_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSnow:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSnow_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSnow_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSnow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSnow",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSnow*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSnow_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSnow:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSnow_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSnow:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSnow_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleRain_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleRain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleRain_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleRain();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleRain");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleRain:ParticleRain",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleRain_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleRain_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleRain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleRain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleRain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleRain_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleRain_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleRain:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleRain_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleRain_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleRain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleRain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleRain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleRain_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleRain:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleRain_initWithTotalParticles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleRain:initWithTotalParticles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleRain_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressTimer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTimer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTimer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ProgressTimer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ProgressTimer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:ProgressTimer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTimer_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressTimer_setBarChangeRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTimer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProgressTimer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProgressTimer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProgressTimer_setBarChangeRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ProgressTimer:setBarChangeRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTimer_setBarChangeRate'", nullptr);
            return 0;
        }
        cobj->setBarChangeRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setBarChangeRate",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTimer_setBarChangeRate'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressTimer_setMidpoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTimer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProgressTimer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProgressTimer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProgressTimer_setMidpoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ProgressTimer:setMidpoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTimer_setMidpoint'", nullptr);
            return 0;
        }
        cobj->setMidpoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:setMidpoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTimer_setMidpoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressTimer_getBarChangeRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTimer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProgressTimer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProgressTimer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProgressTimer_getBarChangeRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTimer_getBarChangeRate'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBarChangeRate();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:getBarChangeRate",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTimer_getBarChangeRate'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressTimer_getMidpoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTimer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProgressTimer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProgressTimer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProgressTimer_getMidpoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTimer_getMidpoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMidpoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTimer:getMidpoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTimer_getMidpoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProtectedNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProtectedNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ProtectedNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ProtectedNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:ProtectedNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProtectedNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProtectedNode_disableCascadeColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProtectedNode_disableCascadeColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProtectedNode_disableCascadeColor'", nullptr);
            return 0;
        }
        cobj->disableCascadeColor();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:disableCascadeColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProtectedNode_disableCascadeColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProtectedNode_disableCascadeOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ProtectedNode_disableCascadeOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProtectedNode_disableCascadeOpacity'", nullptr);
            return 0;
        }
        cobj->disableCascadeOpacity();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:disableCascadeOpacity",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProtectedNode_disableCascadeOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderTexture_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::RenderTexture();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RenderTexture");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:RenderTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_setVirtualViewport(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_setVirtualViewport'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Rect arg1;
        cocos2d::Rect arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.RenderTexture:setVirtualViewport");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.RenderTexture:setVirtualViewport");

        ok &= luaval_to_rect(tolua_S, 4, &arg2, "cc.RenderTexture:setVirtualViewport");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderTexture_setVirtualViewport'", nullptr);
            return 0;
        }
        cobj->setVirtualViewport(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setVirtualViewport",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_setVirtualViewport'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_getRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_getRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderTexture_getRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderTarget();
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getRenderTarget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_getRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_saveToFileAsNonPMA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_saveToFileAsNonPMA'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            cocos2d::Image::Format arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            std::function<void (cocos2d::RenderTexture *, std::string_view)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            bool ret = cobj->saveToFileAsNonPMA(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            bool ret = cobj->saveToFileAsNonPMA(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            bool ret = cobj->saveToFileAsNonPMA(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.RenderTexture:saveToFileAsNonPMA");

            if (!ok) { break; }
            std::function<void (cocos2d::RenderTexture *, std::string_view)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            bool ret = cobj->saveToFileAsNonPMA(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.RenderTexture:saveToFileAsNonPMA",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_saveToFileAsNonPMA'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_saveToFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_saveToFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            cocos2d::Image::Format arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            cocos2d::Image::Format arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            cocos2d::Image::Format arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            std::function<void (cocos2d::RenderTexture *, std::string_view)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.RenderTexture:saveToFile");

            if (!ok) { break; }
            std::function<void (cocos2d::RenderTexture *, std::string_view)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            bool ret = cobj->saveToFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.RenderTexture:saveToFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_saveToFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_setClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_setClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.RenderTexture:setClearColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderTexture_setClearColor'", nullptr);
            return 0;
        }
        cobj->setClearColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:setClearColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_setClearColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_getClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_getClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderTexture_getClearColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getClearColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderTexture:getClearColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_getClearColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_initWithWidthAndHeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderTexture* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::RenderTexture*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderTexture_initWithWidthAndHeight'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool ret = cobj->initWithWidthAndHeight(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool ret = cobj->initWithWidthAndHeight(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool ret = cobj->initWithWidthAndHeight(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.RenderTexture:initWithWidthAndHeight");

            if (!ok) { break; }
            bool ret = cobj->initWithWidthAndHeight(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.RenderTexture:initWithWidthAndHeight",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_initWithWidthAndHeight'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RenderTexture_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.RenderTexture",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:create");
            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.RenderTexture:create");
            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.RenderTexture:create");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.RenderTexture:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.RenderTexture:create");
            if (!ok) { break; }
            cocos2d::RenderTexture* ret = cocos2d::RenderTexture::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::RenderTexture>(tolua_S, "cc.RenderTexture",(cocos2d::RenderTexture*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.RenderTexture:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderTexture_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TransitionScene_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionScene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionScene_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionScene();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionScene");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionScene:TransitionScene",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionScene_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSceneOriented_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSceneOriented* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSceneOriented_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSceneOriented();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSceneOriented");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSceneOriented:TransitionSceneOriented",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSceneOriented_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionRotoZoom_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionRotoZoom* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionRotoZoom_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionRotoZoom();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionRotoZoom");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionRotoZoom:TransitionRotoZoom",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionRotoZoom_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionJumpZoom_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionJumpZoom* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionJumpZoom_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionJumpZoom();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionJumpZoom");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionJumpZoom:TransitionJumpZoom",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionJumpZoom_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionMoveInL_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionMoveInL* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionMoveInL_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionMoveInL();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionMoveInL");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInL:TransitionMoveInL",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionMoveInL_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionMoveInL_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionMoveInL* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionMoveInL",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionMoveInL*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionMoveInL_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionMoveInL:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionMoveInL_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInL:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionMoveInL_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionMoveInR_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionMoveInR* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionMoveInR_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionMoveInR();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionMoveInR");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInR:TransitionMoveInR",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionMoveInR_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionMoveInT_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionMoveInT* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionMoveInT_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionMoveInT();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionMoveInT");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInT:TransitionMoveInT",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionMoveInT_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionMoveInB_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionMoveInB* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionMoveInB_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionMoveInB();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionMoveInB");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionMoveInB:TransitionMoveInB",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionMoveInB_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSlideInL_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSlideInL* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSlideInL_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSlideInL();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSlideInL");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInL:TransitionSlideInL",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSlideInL_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSlideInL_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSlideInL* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionSlideInL",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionSlideInL*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionSlideInL_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionSlideInL:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSlideInL_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInL:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSlideInL_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSlideInR_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSlideInR* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSlideInR_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSlideInR();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSlideInR");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInR:TransitionSlideInR",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSlideInR_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSlideInB_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSlideInB* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSlideInB_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSlideInB();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSlideInB");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInB:TransitionSlideInB",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSlideInB_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSlideInT_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSlideInT* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSlideInT_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSlideInT();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSlideInT");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSlideInT:TransitionSlideInT",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSlideInT_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionShrinkGrow_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionShrinkGrow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionShrinkGrow_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionShrinkGrow();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionShrinkGrow");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionShrinkGrow:TransitionShrinkGrow",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionShrinkGrow_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionShrinkGrow_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionShrinkGrow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionShrinkGrow",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionShrinkGrow*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionShrinkGrow_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionShrinkGrow:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionShrinkGrow_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionShrinkGrow:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionShrinkGrow_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFlipX_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFlipX* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFlipX_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFlipX();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFlipX");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFlipX:TransitionFlipX",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFlipX_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFlipY_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFlipY* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFlipY_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFlipY();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFlipY");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFlipY:TransitionFlipY",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFlipY_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFlipAngular_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFlipAngular* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFlipAngular_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFlipAngular();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFlipAngular");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFlipAngular:TransitionFlipAngular",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFlipAngular_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionZoomFlipX_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionZoomFlipX* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionZoomFlipX_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionZoomFlipX();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionZoomFlipX");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionZoomFlipX:TransitionZoomFlipX",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionZoomFlipX_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionZoomFlipY_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionZoomFlipY* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionZoomFlipY_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionZoomFlipY();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionZoomFlipY");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionZoomFlipY:TransitionZoomFlipY",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionZoomFlipY_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionZoomFlipAngular_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionZoomFlipAngular* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionZoomFlipAngular_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionZoomFlipAngular();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionZoomFlipAngular");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionZoomFlipAngular:TransitionZoomFlipAngular",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionZoomFlipAngular_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFade_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFade* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFade_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFade();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFade");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFade:TransitionFade",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFade_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFade_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFade* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionFade",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TransitionFade*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionFade_initWithDuration'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TransitionFade:initWithDuration");

            if (!ok) { break; }
            cocos2d::Scene* arg1;
            ok &= luaval_to_object<cocos2d::Scene>(tolua_S, 3, "cc.Scene",&arg1, "cc.TransitionFade:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TransitionFade:initWithDuration");

            if (!ok) { break; }
            cocos2d::Scene* arg1;
            ok &= luaval_to_object<cocos2d::Scene>(tolua_S, 3, "cc.Scene",&arg1, "cc.TransitionFade:initWithDuration");

            if (!ok) { break; }
            cocos2d::Color3B arg2;
            ok &= luaval_to_color3b(tolua_S, 4, &arg2, "cc.TransitionFade:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TransitionFade:initWithDuration",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFade_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFade_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TransitionFade",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TransitionFade:create");
            if (!ok) { break; }
            cocos2d::Scene* arg1;
            ok &= luaval_to_object<cocos2d::Scene>(tolua_S, 3, "cc.Scene",&arg1, "cc.TransitionFade:create");
            if (!ok) { break; }
            cocos2d::TransitionFade* ret = cocos2d::TransitionFade::create(arg0, arg1);
            object_to_luaval<cocos2d::TransitionFade>(tolua_S, "cc.TransitionFade",(cocos2d::TransitionFade*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TransitionFade:create");
            if (!ok) { break; }
            cocos2d::Scene* arg1;
            ok &= luaval_to_object<cocos2d::Scene>(tolua_S, 3, "cc.Scene",&arg1, "cc.TransitionFade:create");
            if (!ok) { break; }
            cocos2d::Color3B arg2;
            ok &= luaval_to_color3b(tolua_S, 4, &arg2, "cc.TransitionFade:create");
            if (!ok) { break; }
            cocos2d::TransitionFade* ret = cocos2d::TransitionFade::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::TransitionFade>(tolua_S, "cc.TransitionFade",(cocos2d::TransitionFade*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.TransitionFade:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFade_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TransitionCrossFade_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionCrossFade* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionCrossFade_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionCrossFade();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionCrossFade");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionCrossFade:TransitionCrossFade",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionCrossFade_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionTurnOffTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionTurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionTurnOffTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionTurnOffTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionTurnOffTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionTurnOffTiles:TransitionTurnOffTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionTurnOffTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionTurnOffTiles_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionTurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionTurnOffTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionTurnOffTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionTurnOffTiles_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionTurnOffTiles:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionTurnOffTiles_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionTurnOffTiles:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionTurnOffTiles_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSplitCols_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSplitCols* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSplitCols_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSplitCols();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSplitCols");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSplitCols:TransitionSplitCols",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSplitCols_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSplitCols_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSplitCols* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionSplitCols",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionSplitCols*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionSplitCols_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionSplitCols:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSplitCols_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSplitCols:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSplitCols_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionSplitRows_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionSplitRows* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionSplitRows_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionSplitRows();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionSplitRows");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionSplitRows:TransitionSplitRows",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionSplitRows_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeTR_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeTR* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeTR_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFadeTR();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFadeTR");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeTR:TransitionFadeTR",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeTR_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeTR_easeActionWithAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeTR* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionFadeTR",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionFadeTR*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionFadeTR_easeActionWithAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ActionInterval* arg0;

        ok &= luaval_to_object<cocos2d::ActionInterval>(tolua_S, 2, "cc.ActionInterval",&arg0, "cc.TransitionFadeTR:easeActionWithAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeTR_easeActionWithAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->easeActionWithAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeTR:easeActionWithAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeTR_easeActionWithAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeTR_actionWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeTR* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionFadeTR",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionFadeTR*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionFadeTR_actionWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TransitionFadeTR:actionWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeTR_actionWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->actionWithSize(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeTR:actionWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeTR_actionWithSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeBL_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeBL* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeBL_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFadeBL();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFadeBL");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeBL:TransitionFadeBL",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeBL_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeUp_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeUp* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeUp_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFadeUp();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFadeUp");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeUp:TransitionFadeUp",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeUp_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionFadeDown_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionFadeDown* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionFadeDown_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionFadeDown();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionFadeDown");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionFadeDown:TransitionFadeDown",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionFadeDown_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionPageTurn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionPageTurn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionPageTurn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionPageTurn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionPageTurn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionPageTurn:TransitionPageTurn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionPageTurn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionPageTurn_actionWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionPageTurn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TransitionPageTurn",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TransitionPageTurn*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TransitionPageTurn_actionWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TransitionPageTurn:actionWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionPageTurn_actionWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->actionWithSize(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionPageTurn:actionWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionPageTurn_actionWithSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgress_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgress* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgress_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgress();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgress");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgress:TransitionProgress",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgress_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressRadialCCW_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressRadialCCW* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressRadialCCW_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressRadialCCW();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressRadialCCW");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressRadialCCW:TransitionProgressRadialCCW",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressRadialCCW_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressRadialCW_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressRadialCW* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressRadialCW_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressRadialCW();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressRadialCW");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressRadialCW:TransitionProgressRadialCW",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressRadialCW_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressHorizontal_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressHorizontal* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressHorizontal_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressHorizontal();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressHorizontal");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressHorizontal:TransitionProgressHorizontal",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressHorizontal_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressVertical_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressVertical* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressVertical_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressVertical();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressVertical");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressVertical:TransitionProgressVertical",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressVertical_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressInOut:TransitionProgressInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TransitionProgressOutIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TransitionProgressOutIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TransitionProgressOutIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TransitionProgressOutIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TransitionProgressOutIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TransitionProgressOutIn:TransitionProgressOutIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TransitionProgressOutIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Camera();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Camera");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:Camera",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_getViewProjectionMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_getViewProjectionMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getViewProjectionMatrix'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getViewProjectionMatrix();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getViewProjectionMatrix",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getViewProjectionMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_lookAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_lookAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Camera:lookAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_lookAt'", nullptr);
            return 0;
        }
        cobj->lookAt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Camera:lookAt");

        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.Camera:lookAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_lookAt'", nullptr);
            return 0;
        }
        cobj->lookAt(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:lookAt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_lookAt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_getProjectionMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_getProjectionMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getProjectionMatrix'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProjectionMatrix();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getProjectionMatrix",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getProjectionMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_setAdditionalProjection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_setAdditionalProjection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Mat4 arg0;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Camera:setAdditionalProjection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_setAdditionalProjection'", nullptr);
            return 0;
        }
        cobj->setAdditionalProjection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setAdditionalProjection",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_setAdditionalProjection'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_isVisibleInFrustum(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_isVisibleInFrustum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const cocos2d::AABB* arg0;

        ok &= luaval_to_object<const cocos2d::AABB>(tolua_S, 2, "cc.AABB",&arg0, "cc.Camera:isVisibleInFrustum");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_isVisibleInFrustum'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isVisibleInFrustum(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:isVisibleInFrustum",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_isVisibleInFrustum'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_setDepth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_setDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "cc.Camera:setDepth");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_setDepth'", nullptr);
            return 0;
        }
        cobj->setDepth(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:setDepth",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_setDepth'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_projectGL(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_projectGL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Camera:projectGL");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_projectGL'", nullptr);
            return 0;
        }
        auto&& ret = cobj->projectGL(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:projectGL",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_projectGL'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_getViewMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_getViewMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getViewMatrix'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getViewMatrix();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getViewMatrix",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getViewMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_project(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_project'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Camera:project");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_project'", nullptr);
            return 0;
        }
        auto&& ret = cobj->project(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:project",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_project'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_getDepthInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Camera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Camera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Camera_getDepthInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Mat4 arg0;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Camera:getDepthInView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getDepthInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDepthInView(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Camera:getDepthInView",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getDepthInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Camera_getVisitingCamera(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getVisitingCamera'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Camera::getVisitingCamera();
        object_to_luaval<cocos2d::Camera>(tolua_S, "cc.Camera",(cocos2d::Camera*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:getVisitingCamera",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getVisitingCamera'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Camera_getDefaultViewport(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_getDefaultViewport'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Camera::getDefaultViewport();
        #pragma warning NO CONVERSION FROM NATIVE FOR Viewport;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:getDefaultViewport",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_getDefaultViewport'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Camera_setDefaultViewport(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Camera",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Viewport arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR Viewport
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Camera_setDefaultViewport'", nullptr);
            return 0;
        }
        cocos2d::Camera::setDefaultViewport(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Camera:setDefaultViewport",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Camera_setDefaultViewport'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_CameraBackgroundBrush_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundBrush_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CameraBackgroundBrush();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CameraBackgroundBrush");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundBrush:CameraBackgroundBrush",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundBrush_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundBrush_createColorBrush(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CameraBackgroundBrush",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Color4F arg0;
        double arg1;
        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.CameraBackgroundBrush:createColorBrush");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.CameraBackgroundBrush:createColorBrush");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundBrush_createColorBrush'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::CameraBackgroundBrush::createColorBrush(arg0, arg1);
        object_to_luaval<cocos2d::CameraBackgroundColorBrush>(tolua_S, "cc.CameraBackgroundColorBrush",(cocos2d::CameraBackgroundColorBrush*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundBrush:createColorBrush",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundBrush_createColorBrush'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_CameraBackgroundDepthBrush_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundDepthBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundDepthBrush_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CameraBackgroundDepthBrush();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CameraBackgroundDepthBrush");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundDepthBrush:CameraBackgroundDepthBrush",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundDepthBrush_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundColorBrush_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundColorBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundColorBrush_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CameraBackgroundColorBrush();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CameraBackgroundColorBrush");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundColorBrush:CameraBackgroundColorBrush",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundColorBrush_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundColorBrush_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundColorBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CameraBackgroundColorBrush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CameraBackgroundColorBrush*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CameraBackgroundColorBrush_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.CameraBackgroundColorBrush:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundColorBrush_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundColorBrush:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundColorBrush_setColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundColorBrush_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CameraBackgroundColorBrush",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Color4F arg0;
        double arg1;
        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.CameraBackgroundColorBrush:create");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.CameraBackgroundColorBrush:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundColorBrush_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::CameraBackgroundColorBrush::create(arg0, arg1);
        object_to_luaval<cocos2d::CameraBackgroundColorBrush>(tolua_S, "cc.CameraBackgroundColorBrush",(cocos2d::CameraBackgroundColorBrush*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CameraBackgroundColorBrush:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundColorBrush_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_CameraBackgroundSkyBoxBrush_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundSkyBoxBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CameraBackgroundSkyBoxBrush();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CameraBackgroundSkyBoxBrush");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:CameraBackgroundSkyBoxBrush",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundSkyBoxBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CameraBackgroundSkyBoxBrush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CameraBackgroundSkyBoxBrush*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextureCube* arg0;

        ok &= luaval_to_object<cocos2d::TextureCube>(tolua_S, 2, "cc.TextureCube",&arg0, "cc.CameraBackgroundSkyBoxBrush:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CameraBackgroundSkyBoxBrush* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CameraBackgroundSkyBoxBrush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CameraBackgroundSkyBoxBrush*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::TextureCube>(tolua_S, "cc.TextureCube",(cocos2d::TextureCube*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CameraBackgroundSkyBoxBrush:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CameraBackgroundSkyBoxBrush_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_setGridSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_setGridSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:setGridSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_setGridSize'", nullptr);
            return 0;
        }
        cobj->setGridSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setGridSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_setGridSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_setGridRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_setGridRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.GridBase:setGridRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_setGridRect'", nullptr);
            return 0;
        }
        cobj->setGridRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setGridRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_setGridRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_getGridRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_getGridRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_getGridRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getGridRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:getGridRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_getGridRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_getGridSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_getGridSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_getGridSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getGridSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:getGridSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_getGridSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_getStep(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_getStep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_getStep'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStep();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:getStep",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_getStep'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_setStep(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_setStep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:setStep");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridBase_setStep'", nullptr);
            return 0;
        }
        cobj->setStep(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridBase:setStep",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_setStep'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridBase_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridBase* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridBase",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::GridBase*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridBase_initWithSize'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool ret = cobj->initWithSize(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool ret = cobj->initWithSize(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool ret = cobj->initWithSize(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "cc.GridBase:initWithSize");

            if (!ok) { break; }
            bool ret = cobj->initWithSize(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.GridBase:initWithSize",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridBase_initWithSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Grid3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Grid3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Grid3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Grid3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Grid3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Grid3D:Grid3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Grid3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Grid3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Grid3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Grid3D* ret = cocos2d::Grid3D::create(arg0, arg1);
            object_to_luaval<cocos2d::Grid3D>(tolua_S, "cc.Grid3D",(cocos2d::Grid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Grid3D* ret = cocos2d::Grid3D::create(arg0);
            object_to_luaval<cocos2d::Grid3D>(tolua_S, "cc.Grid3D",(cocos2d::Grid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.Grid3D:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Grid3D* ret = cocos2d::Grid3D::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Grid3D>(tolua_S, "cc.Grid3D",(cocos2d::Grid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.Grid3D:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "cc.Grid3D:create");
            if (!ok) { break; }
            cocos2d::Grid3D* ret = cocos2d::Grid3D::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::Grid3D>(tolua_S, "cc.Grid3D",(cocos2d::Grid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Grid3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Grid3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TiledGrid3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TiledGrid3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::TiledGrid3D* ret = cocos2d::TiledGrid3D::create(arg0, arg1);
            object_to_luaval<cocos2d::TiledGrid3D>(tolua_S, "cc.TiledGrid3D",(cocos2d::TiledGrid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::TiledGrid3D* ret = cocos2d::TiledGrid3D::create(arg0);
            object_to_luaval<cocos2d::TiledGrid3D>(tolua_S, "cc.TiledGrid3D",(cocos2d::TiledGrid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::TiledGrid3D* ret = cocos2d::TiledGrid3D::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::TiledGrid3D>(tolua_S, "cc.TiledGrid3D",(cocos2d::TiledGrid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "cc.TiledGrid3D:create");
            if (!ok) { break; }
            cocos2d::TiledGrid3D* ret = cocos2d::TiledGrid3D::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::TiledGrid3D>(tolua_S, "cc.TiledGrid3D",(cocos2d::TiledGrid3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.TiledGrid3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TiledGrid3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_DirectionLight_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DirectionLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DirectionLight_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::DirectionLight();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DirectionLight");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirectionLight:DirectionLight",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DirectionLight_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DirectionLight_getDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DirectionLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DirectionLight",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DirectionLight*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DirectionLight_getDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DirectionLight_getDirection'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDirection();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirectionLight:getDirection",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DirectionLight_getDirection'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DirectionLight_getDirectionInWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DirectionLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DirectionLight",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DirectionLight*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DirectionLight_getDirectionInWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DirectionLight_getDirectionInWorld'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDirectionInWorld();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirectionLight:getDirectionInWorld",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DirectionLight_getDirectionInWorld'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DirectionLight_setDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DirectionLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DirectionLight",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DirectionLight*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DirectionLight_setDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.DirectionLight:setDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DirectionLight_setDirection'", nullptr);
            return 0;
        }
        cobj->setDirection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DirectionLight:setDirection",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DirectionLight_setDirection'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DirectionLight_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.DirectionLight",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Color3B arg1;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.DirectionLight:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "cc.DirectionLight:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DirectionLight_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::DirectionLight::create(arg0, arg1);
        object_to_luaval<cocos2d::DirectionLight>(tolua_S, "cc.DirectionLight",(cocos2d::DirectionLight*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.DirectionLight:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DirectionLight_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_PointLight_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PointLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PointLight_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::PointLight();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.PointLight");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PointLight:PointLight",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PointLight_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PointLight_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PointLight",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Color3B arg1;
        double arg2;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.PointLight:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "cc.PointLight:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PointLight:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PointLight_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::PointLight::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PointLight>(tolua_S, "cc.PointLight",(cocos2d::PointLight*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PointLight:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PointLight_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_SpotLight_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpotLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpotLight_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SpotLight();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SpotLight");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:SpotLight",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpotLight_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpotLight_setDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpotLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpotLight",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpotLight*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpotLight_setDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.SpotLight:setDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpotLight_setDirection'", nullptr);
            return 0;
        }
        cobj->setDirection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:setDirection",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpotLight_setDirection'.",&tolua_err);
#endif

    return 0;
}
