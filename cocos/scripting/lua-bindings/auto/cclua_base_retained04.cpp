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

int lua_cc_base_Label_getFontAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getFontAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getFontAtlas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFontAtlas();
        object_to_luaval<cocos2d::FontAtlas>(tolua_S, "cc.FontAtlas",(cocos2d::FontAtlas*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getFontAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getFontAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_enableOutline(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_enableOutline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableOutline'", nullptr);
            return 0;
        }
        cobj->enableOutline(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Color4B arg0;
        int arg1;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableOutline");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Label:enableOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableOutline'", nullptr);
            return 0;
        }
        cobj->enableOutline(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableOutline",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_enableOutline'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getEffectColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getEffectColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getEffectColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEffectColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getEffectColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getEffectColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Label:removeAllChildrenWithCleanup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_removeAllChildrenWithCleanup'", nullptr);
            return 0;
        }
        cobj->removeAllChildrenWithCleanup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:removeAllChildrenWithCleanup",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setCharMap(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setCharMap'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:setCharMap");

            if (!ok) { break; }
            bool ret = cobj->setCharMap(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:setCharMap");

            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:setCharMap");

            if (!ok) { break; }
            bool ret = cobj->setCharMap(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setCharMap");

            if (!ok) { break; }
            bool ret = cobj->setCharMap(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Label:setCharMap",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setCharMap'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getDimensions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getDimensions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getDimensions'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDimensions();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getDimensions",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getDimensions'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getShadowColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getShadowColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getShadowColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getShadowColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getShadowColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getShadowColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getTTFConfig(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getTTFConfig'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getTTFConfig'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTTFConfig();
        ttfconfig_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getTTFConfig",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getTTFConfig'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:setTextColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_setTextColor'", nullptr);
            return 0;
        }
        cobj->setTextColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setTextColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setTextColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_enableGlow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_enableGlow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableGlow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableGlow'", nullptr);
            return 0;
        }
        cobj->enableGlow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableGlow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_enableGlow'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Label* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Label*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.Label:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_createWithBMFont(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 6)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Rect arg4;
            ok &= luaval_to_rect(tolua_S, 6, &arg4, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            bool arg5;
            ok &= luaval_to_boolean(tolua_S, 7,&arg5, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithBMFont(arg0, arg1, arg2, arg3, arg4, arg5);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithBMFont(arg0, arg1);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithBMFont(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithBMFont(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            std::string_view arg4;
            ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.Label:createWithBMFont");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithBMFont(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Label:createWithBMFont",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_createWithBMFont'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Label_createWithCharMap(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 4)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithCharMap(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithCharMap(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithCharMap");
            if (!ok) { break; }
            cocos2d::Label* ret = cocos2d::Label::createWithCharMap(arg0);
            object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Label:createWithCharMap",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_createWithCharMap'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Label_createWithSystemFont(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string_view arg0;
        std::string_view arg1;
        double arg2;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithSystemFont");
        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithSystemFont");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:createWithSystemFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_createWithSystemFont'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Label::createWithSystemFont(arg0, arg1, arg2);
        object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string_view arg0;
        std::string_view arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithSystemFont");
        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithSystemFont");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:createWithSystemFont");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:createWithSystemFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_createWithSystemFont'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Label::createWithSystemFont(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
        return 1;
    }
    if (argc == 5)
    {
        std::string_view arg0;
        std::string_view arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        cocos2d::TextHAlignment arg4;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithSystemFont");
        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithSystemFont");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:createWithSystemFont");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:createWithSystemFont");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Label:createWithSystemFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_createWithSystemFont'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Label::createWithSystemFont(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
        return 1;
    }
    if (argc == 6)
    {
        std::string_view arg0;
        std::string_view arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        cocos2d::TextHAlignment arg4;
        cocos2d::TextVAlignment arg5;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:createWithSystemFont");
        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:createWithSystemFont");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:createWithSystemFont");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:createWithSystemFont");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Label:createWithSystemFont");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Label:createWithSystemFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_createWithSystemFont'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Label::createWithSystemFont(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::Label>(tolua_S, "cc.Label",(cocos2d::Label*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Label:createWithSystemFont",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_createWithSystemFont'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_LabelAtlas_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LabelAtlas_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LabelAtlas();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LabelAtlas");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelAtlas:LabelAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LabelAtlas_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LabelAtlas_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LabelAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LabelAtlas_setString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:setString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LabelAtlas_setString'", nullptr);
            return 0;
        }
        cobj->setString(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelAtlas:setString",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LabelAtlas_setString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LabelAtlas_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelAtlas* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelAtlas",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LabelAtlas*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LabelAtlas_initWithString'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelAtlas:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LabelAtlas:initWithString",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LabelAtlas_initWithString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LabelAtlas_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LabelAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LabelAtlas_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LabelAtlas_getString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getString();
        lua_pushlstring(tolua_S,ret.data(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelAtlas:getString",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LabelAtlas_getString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LabelAtlas_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LabelAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.LabelAtlas:create");
            if (!ok) { break; }
            cocos2d::LabelAtlas* ret = cocos2d::LabelAtlas::create(arg0, arg1);
            object_to_luaval<cocos2d::LabelAtlas>(tolua_S, "cc.LabelAtlas",(cocos2d::LabelAtlas*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelAtlas:create");
            if (!ok) { break; }
            cocos2d::LabelAtlas* ret = cocos2d::LabelAtlas::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::LabelAtlas>(tolua_S, "cc.LabelAtlas",(cocos2d::LabelAtlas*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.LabelAtlas:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelAtlas:create");
            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelAtlas:create");
            if (!ok) { break; }
            cocos2d::LabelAtlas* ret = cocos2d::LabelAtlas::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::LabelAtlas>(tolua_S, "cc.LabelAtlas",(cocos2d::LabelAtlas*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LabelAtlas:create",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LabelAtlas_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Sprite_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Sprite();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Sprite");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:Sprite",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setSpriteFrame'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.Sprite:setSpriteFrame");

            if (!ok) { break; }
            cobj->setSpriteFrame(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Sprite:setSpriteFrame");

            if (!ok) { break; }
            cobj->setSpriteFrame(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite:setSpriteFrame",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setSpriteFrame'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Sprite:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getOffsetPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getOffsetPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getOffsetPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOffsetPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getOffsetPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getOffsetPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getCenterRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getCenterRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getCenterRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCenterRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getCenterRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getCenterRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setCenterRectNormalized(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setCenterRectNormalized'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Sprite:setCenterRectNormalized");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_setCenterRectNormalized'", nullptr);
            return 0;
        }
        cobj->setCenterRectNormalized(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setCenterRectNormalized",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setCenterRectNormalized'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setTextureRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setTextureRect'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Sprite:setTextureRect");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Sprite:setTextureRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Sprite:setTextureRect");

            if (!ok) { break; }
            cobj->setTextureRect(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Sprite:setTextureRect");

            if (!ok) { break; }
            cobj->setTextureRect(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite:setTextureRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setTextureRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextureAtlas* arg0;

        ok &= luaval_to_object<cocos2d::TextureAtlas>(tolua_S, 2, "cc.TextureAtlas",&arg0, "cc.Sprite:setTextureAtlas");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_setTextureAtlas'", nullptr);
            return 0;
        }
        cobj->setTextureAtlas(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setTextureAtlas",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setCenterRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setCenterRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Sprite:setCenterRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_setCenterRect'", nullptr);
            return 0;
        }
        cobj->setCenterRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setCenterRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setCenterRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Sprite:removeAllChildrenWithCleanup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_removeAllChildrenWithCleanup'", nullptr);
            return 0;
        }
        cobj->removeAllChildrenWithCleanup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:removeAllChildrenWithCleanup",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getCenterRectNormalized(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getCenterRectNormalized'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getCenterRectNormalized'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCenterRectNormalized();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getCenterRectNormalized",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getCenterRectNormalized'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_initWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_initWithTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            bool ret = cobj->initWithTexture(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            bool ret = cobj->initWithTexture(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Sprite:initWithTexture");

            if (!ok) { break; }
            bool ret = cobj->initWithTexture(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite:initWithTexture",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_initWithTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getTextureRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getTextureRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getTextureRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getTextureRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getTextureRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_initWithFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Sprite:initWithFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_initWithFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.Sprite:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_getTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_getTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_getTextureAtlas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureAtlas();
        object_to_luaval<cocos2d::TextureAtlas>(tolua_S, "cc.TextureAtlas",(cocos2d::TextureAtlas*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:getTextureAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_getTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_setVertexRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sprite_setVertexRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Sprite:setVertexRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sprite_setVertexRect'", nullptr);
            return 0;
        }
        cobj->setVertexRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite:setVertexRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_setVertexRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sprite_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            cocos2d::Sprite* ret = cocos2d::Sprite::createWithTexture(arg0, arg1);
            object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            cocos2d::Sprite* ret = cocos2d::Sprite::createWithTexture(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Sprite:createWithTexture");
            if (!ok) { break; }
            cocos2d::Sprite* ret = cocos2d::Sprite::createWithTexture(arg0);
            object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Sprite:createWithTexture",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sprite_createWithTexture'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_LayerColor_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerColor* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerColor_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LayerColor();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LayerColor");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerColor:LayerColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerColor_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerColor_initWithColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerColor* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerColor",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LayerColor*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerColor_initWithColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerColor:initWithColor");

            if (!ok) { break; }
            bool ret = cobj->initWithColor(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerColor:initWithColor");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LayerColor:initWithColor");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LayerColor:initWithColor");

            if (!ok) { break; }
            bool ret = cobj->initWithColor(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LayerColor:initWithColor",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerColor_initWithColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerColor_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LayerColor",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerColor:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LayerColor:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LayerColor:create");
            if (!ok) { break; }
            cocos2d::LayerColor* ret = cocos2d::LayerColor::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::LayerColor>(tolua_S, "cc.LayerColor",(cocos2d::LayerColor*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::LayerColor* ret = cocos2d::LayerColor::create();
            object_to_luaval<cocos2d::LayerColor>(tolua_S, "cc.LayerColor",(cocos2d::LayerColor*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerColor:create");
            if (!ok) { break; }
            cocos2d::LayerColor* ret = cocos2d::LayerColor::create(arg0);
            object_to_luaval<cocos2d::LayerColor>(tolua_S, "cc.LayerColor",(cocos2d::LayerColor*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LayerColor:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerColor_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_LayerGradient_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LayerGradient();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LayerGradient");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:LayerGradient",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_getStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_getStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_getStartColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:getStartColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_getStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_setVector(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_setVector'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.LayerGradient:setVector");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_setVector'", nullptr);
            return 0;
        }
        cobj->setVector(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setVector",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_setVector'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_setStartOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_setStartOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.LayerGradient:setStartOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_setStartOpacity'", nullptr);
            return 0;
        }
        cobj->setStartOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setStartOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_setStartOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_setEndOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_setEndOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.LayerGradient:setEndOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_setEndOpacity'", nullptr);
            return 0;
        }
        cobj->setEndOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setEndOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_setEndOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_getVector(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_getVector'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_getVector'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVector();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:getVector",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_getVector'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_setEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_setEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LayerGradient:setEndColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_setEndColor'", nullptr);
            return 0;
        }
        cobj->setEndColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setEndColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_setEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_initWithColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_initWithColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerGradient:initWithColor");

            if (!ok) { break; }
            cocos2d::Color4B arg1;
            ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerGradient:initWithColor");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.LayerGradient:initWithColor");

            if (!ok) { break; }
            bool ret = cobj->initWithColor(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerGradient:initWithColor");

            if (!ok) { break; }
            cocos2d::Color4B arg1;
            ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerGradient:initWithColor");

            if (!ok) { break; }
            bool ret = cobj->initWithColor(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LayerGradient:initWithColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_initWithColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_getEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_getEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_getEndColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEndColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:getEndColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_getEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_setStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerGradient_setStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LayerGradient:setStartColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerGradient_setStartColor'", nullptr);
            return 0;
        }
        cobj->setStartColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerGradient:setStartColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_setStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerGradient_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LayerGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerGradient:create");
            if (!ok) { break; }
            cocos2d::Color4B arg1;
            ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerGradient:create");
            if (!ok) { break; }
            cocos2d::LayerGradient* ret = cocos2d::LayerGradient::create(arg0, arg1);
            object_to_luaval<cocos2d::LayerGradient>(tolua_S, "cc.LayerGradient",(cocos2d::LayerGradient*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::LayerGradient* ret = cocos2d::LayerGradient::create();
            object_to_luaval<cocos2d::LayerGradient>(tolua_S, "cc.LayerGradient",(cocos2d::LayerGradient*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerGradient:create");
            if (!ok) { break; }
            cocos2d::Color4B arg1;
            ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerGradient:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.LayerGradient:create");
            if (!ok) { break; }
            cocos2d::LayerGradient* ret = cocos2d::LayerGradient::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::LayerGradient>(tolua_S, "cc.LayerGradient",(cocos2d::LayerGradient*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LayerGradient:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerGradient_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_LayerRadialGradient_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LayerRadialGradient();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LayerRadialGradient");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:LayerRadialGradient",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getStartColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getStartColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getStartColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getStartColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getStartColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getStartColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getStartColor3B'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setCenter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setCenter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_setCenter'", nullptr);
            return 0;
        }
        cobj->setCenter(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setCenter",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setCenter'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getEndColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEndColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getEndColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setStartOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setStartOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.LayerRadialGradient:setStartOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_setStartOpacity'", nullptr);
            return 0;
        }
        cobj->setStartOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setStartOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setStartOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getCenter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getCenter'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCenter();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getCenter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getCenter'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setEndOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setEndOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.LayerRadialGradient:setEndOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_setEndOpacity'", nullptr);
            return 0;
        }
        cobj->setEndOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setEndOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setEndOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_initWithColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_initWithColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocos2d::Color4B arg0;
        cocos2d::Color4B arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        double arg4;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:initWithColor");

        ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerRadialGradient:initWithColor");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LayerRadialGradient:initWithColor");

        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.LayerRadialGradient:initWithColor");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.LayerRadialGradient:initWithColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_initWithColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithColor(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:initWithColor",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_initWithColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setEndColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setEndColor");

            if (!ok) { break; }
            cobj->setEndColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setEndColor");

            if (!ok) { break; }
            cobj->setEndColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LayerRadialGradient:setEndColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_getEndColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_getEndColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_getEndColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEndColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:getEndColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_getEndColor3B'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setStartColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setStartColor");

            if (!ok) { break; }
            cobj->setStartColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setStartColor");

            if (!ok) { break; }
            cobj->setStartColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LayerRadialGradient:setStartColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerRadialGradient* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerRadialGradient*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerRadialGradient_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.LayerRadialGradient:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerRadialGradient_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerRadialGradient:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerRadialGradient_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LayerRadialGradient",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 0)
        {
            cocos2d::LayerRadialGradient* ret = cocos2d::LayerRadialGradient::create();
            object_to_luaval<cocos2d::LayerRadialGradient>(tolua_S, "cc.LayerRadialGradient",(cocos2d::LayerRadialGradient*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.LayerRadialGradient:create");
            if (!ok) { break; }
            cocos2d::Color4B arg1;
            ok &=luaval_to_color4b(tolua_S, 3, &arg1, "cc.LayerRadialGradient:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LayerRadialGradient:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.LayerRadialGradient:create");
            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.LayerRadialGradient:create");
            if (!ok) { break; }
            cocos2d::LayerRadialGradient* ret = cocos2d::LayerRadialGradient::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::LayerRadialGradient>(tolua_S, "cc.LayerRadialGradient",(cocos2d::LayerRadialGradient*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LayerRadialGradient:create",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerRadialGradient_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_LayerMultiplex_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerMultiplex* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerMultiplex_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LayerMultiplex();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LayerMultiplex");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerMultiplex:LayerMultiplex",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerMultiplex_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_LayerMultiplex_initWithArray(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LayerMultiplex* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LayerMultiplex",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LayerMultiplex*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_LayerMultiplex_initWithArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::Node *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.LayerMultiplex:initWithArray");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_LayerMultiplex_initWithArray'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithArray(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LayerMultiplex:initWithArray",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_LayerMultiplex_initWithArray'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItem_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItem_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItem();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItem");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:MenuItem",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItem_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItem_rect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItem*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItem_rect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItem_rect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->rect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItem:rect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItem_rect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemLabel_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemLabel* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemLabel_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemLabel();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemLabel");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:MenuItemLabel",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemLabel_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemLabel_getDisabledColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemLabel* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemLabel*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemLabel_getDisabledColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemLabel_getDisabledColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDisabledColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:getDisabledColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemLabel_getDisabledColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemLabel_initWithLabel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemLabel* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemLabel*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemLabel_initWithLabel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        std::function<void (cocos2d::Ref *)> arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.MenuItemLabel:initWithLabel");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemLabel_initWithLabel'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithLabel(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:initWithLabel",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemLabel_initWithLabel'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemLabel_setDisabledColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemLabel* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemLabel*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemLabel_setDisabledColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.MenuItemLabel:setDisabledColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemLabel_setDisabledColor'", nullptr);
            return 0;
        }
        cobj->setDisabledColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemLabel:setDisabledColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemLabel_setDisabledColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemAtlasFont_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemAtlasFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemAtlasFont_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemAtlasFont();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemAtlasFont");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemAtlasFont:MenuItemAtlasFont",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemAtlasFont_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemAtlasFont_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemAtlasFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemAtlasFont",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemAtlasFont*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemAtlasFont_initWithString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        std::string_view arg0;
        std::string_view arg1;
        int arg2;
        int arg3;
        int32_t arg4;
        std::function<void (cocos2d::Ref *)> arg5;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MenuItemAtlasFont:initWithString");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.MenuItemAtlasFont:initWithString");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.MenuItemAtlasFont:initWithString");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.MenuItemAtlasFont:initWithString");

        ok &= luaval_to_int32(tolua_S, 6,&arg4, "cc.MenuItemAtlasFont:initWithString");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemAtlasFont_initWithString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemAtlasFont:initWithString",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemAtlasFont_initWithString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemFont_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemFont_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemFont();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemFont");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:MenuItemFont",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemFont_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemFont_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemFont",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemFont*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemFont_initWithString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::function<void (cocos2d::Ref *)> arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MenuItemFont:initWithString");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemFont_initWithString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithString(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemFont:initWithString",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemFont_initWithString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemSprite_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemSprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemSprite_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemSprite();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemSprite");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:MenuItemSprite",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemSprite_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemSprite_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemSprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemSprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemSprite_setEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.MenuItemSprite:setEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemSprite_setEnabled'", nullptr);
            return 0;
        }
        cobj->setEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:setEnabled",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemSprite_setEnabled'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemSprite_selected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemSprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemSprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemSprite_selected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemSprite_selected'", nullptr);
            return 0;
        }
        cobj->selected();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:selected",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemSprite_selected'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemSprite_initWithNormalSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemSprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemSprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemSprite_initWithNormalSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;
        cocos2d::Node* arg2;
        std::function<void (cocos2d::Ref *)> arg3;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.MenuItemSprite:initWithNormalSprite");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1, "cc.MenuItemSprite:initWithNormalSprite");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 4, "cc.Node",&arg2, "cc.MenuItemSprite:initWithNormalSprite");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemSprite_initWithNormalSprite'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithNormalSprite(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:initWithNormalSprite",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemSprite_initWithNormalSprite'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemSprite_unselected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemSprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemSprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemSprite_unselected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemSprite_unselected'", nullptr);
            return 0;
        }
        cobj->unselected();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemSprite:unselected",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemSprite_unselected'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemImage_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemImage* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemImage_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemImage();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemImage");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:MenuItemImage",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemImage_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemImage_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemImage* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemImage*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemImage_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemImage_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:init",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemImage_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemImage_initWithNormalImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemImage* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemImage*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemImage_initWithNormalImage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::function<void (cocos2d::Ref *)> arg3;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MenuItemImage:initWithNormalImage");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.MenuItemImage:initWithNormalImage");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.MenuItemImage:initWithNormalImage");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemImage_initWithNormalImage'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithNormalImage(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemImage:initWithNormalImage",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemImage_initWithNormalImage'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemToggle_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemToggle* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemToggle_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MenuItemToggle();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MenuItemToggle");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:MenuItemToggle",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemToggle_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MenuItemToggle_setSubItems(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MenuItemToggle* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MenuItemToggle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MenuItemToggle*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MenuItemToggle_setSubItems'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::MenuItem *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.MenuItemToggle:setSubItems");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MenuItemToggle_setSubItems'", nullptr);
            return 0;
        }
        cobj->setSubItems(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MenuItemToggle:setSubItems",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MenuItemToggle_setSubItems'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Menu_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Menu* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Menu_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Menu();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Menu");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:Menu",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Menu_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Menu_initWithArray(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Menu* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Menu",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Menu*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Menu_initWithArray'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::MenuItem *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Menu:initWithArray");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Menu_initWithArray'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithArray(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Menu:initWithArray",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Menu_initWithArray'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MotionStreak();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MotionStreak");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:MotionStreak",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.MotionStreak:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_tintWithColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_tintWithColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.MotionStreak:tintWithColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_tintWithColor'", nullptr);
            return 0;
        }
        cobj->tintWithColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:tintWithColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_tintWithColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.MotionStreak:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_initWithFade(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MotionStreak*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak_initWithFade'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 5) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            cocos2d::Texture2D* arg4;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 6, "cc.Texture2D",&arg4, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            bool ret = cobj->initWithFade(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            std::string_view arg4;
            ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.MotionStreak:initWithFade");

            if (!ok) { break; }
            bool ret = cobj->initWithFade(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MotionStreak:initWithFade",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_initWithFade'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MotionStreak",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 5)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak:create");
            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg4;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 6, "cc.Texture2D",&arg4, "cc.MotionStreak:create");
            if (!ok) { break; }
            cocos2d::MotionStreak* ret = cocos2d::MotionStreak::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::MotionStreak>(tolua_S, "cc.MotionStreak",(cocos2d::MotionStreak*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak:create");
            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak:create");
            if (!ok) { break; }
            std::string_view arg4;
            ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.MotionStreak:create");
            if (!ok) { break; }
            cocos2d::MotionStreak* ret = cocos2d::MotionStreak::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::MotionStreak>(tolua_S, "cc.MotionStreak",(cocos2d::MotionStreak*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.MotionStreak:create",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_NodeGrid_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NodeGrid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_NodeGrid_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NodeGrid();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NodeGrid");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NodeGrid:NodeGrid",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_NodeGrid_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_NodeGrid_setGridRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NodeGrid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NodeGrid",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NodeGrid*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_NodeGrid_setGridRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.NodeGrid:setGridRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_NodeGrid_setGridRect'", nullptr);
            return 0;
        }
        cobj->setGridRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NodeGrid:setGridRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_NodeGrid_setGridRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_NodeGrid_getGrid(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NodeGrid* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NodeGrid",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::NodeGrid*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_NodeGrid_getGrid'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::GridBase* ret = cobj->getGrid();
            object_to_luaval<cocos2d::GridBase>(tolua_S, "cc.GridBase",(cocos2d::GridBase*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::GridBase* ret = cobj->getGrid();
            object_to_luaval<cocos2d::GridBase>(tolua_S, "cc.GridBase",(cocos2d::GridBase*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.NodeGrid:getGrid",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_NodeGrid_getGrid'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_NodeGrid_getGridRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NodeGrid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NodeGrid",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NodeGrid*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_NodeGrid_getGridRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_NodeGrid_getGridRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getGridRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NodeGrid:getGridRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_NodeGrid_getGridRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_NodeGrid_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NodeGrid",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.NodeGrid:create");
            if (!ok) { break; }
            cocos2d::NodeGrid* ret = cocos2d::NodeGrid::create(arg0);
            object_to_luaval<cocos2d::NodeGrid>(tolua_S, "cc.NodeGrid",(cocos2d::NodeGrid*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::NodeGrid* ret = cocos2d::NodeGrid::create();
            object_to_luaval<cocos2d::NodeGrid>(tolua_S, "cc.NodeGrid",(cocos2d::NodeGrid*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.NodeGrid:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_NodeGrid_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParticleBatchNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleBatchNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleBatchNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:ParticleBatchNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.ParticleBatchNode:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_setTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_setTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextureAtlas* arg0;

        ok &= luaval_to_object<cocos2d::TextureAtlas>(tolua_S, 2, "cc.TextureAtlas",&arg0, "cc.ParticleBatchNode:setTextureAtlas");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_setTextureAtlas'", nullptr);
            return 0;
        }
        cobj->setTextureAtlas(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:setTextureAtlas",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_setTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.ParticleBatchNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ParticleBatchNode:removeAllChildrenWithCleanup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup'", nullptr);
            return 0;
        }
        cobj->removeAllChildrenWithCleanup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:removeAllChildrenWithCleanup",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_getTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_getTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_getTextureAtlas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureAtlas();
        object_to_luaval<cocos2d::TextureAtlas>(tolua_S, "cc.TextureAtlas",(cocos2d::TextureAtlas*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:getTextureAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_getTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleBatchNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleBatchNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleBatchNode_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleBatchNode:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleBatchNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrameCache_getSpriteSheetLoader(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrameCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrameCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrameCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrameCache_getSpriteSheetLoader'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.SpriteFrameCache:getSpriteSheetLoader");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrameCache_getSpriteSheetLoader'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSpriteSheetLoader(arg0);
        object_to_luaval<cocos2d::ISpriteSheetLoader>(tolua_S, "cc.ISpriteSheetLoader",(cocos2d::ISpriteSheetLoader*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:getSpriteSheetLoader",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrameCache_getSpriteSheetLoader'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrameCache_addSpriteFramesWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrameCache* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrameCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SpriteFrameCache*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrameCache_addSpriteFramesWithFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            unsigned int arg1;
            ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cocos2d::Texture2D* arg1;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 3, "cc.Texture2D",&arg1, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.SpriteFrameCache:addSpriteFramesWithFile");

            if (!ok) { break; }
            cobj->addSpriteFramesWithFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.SpriteFrameCache:addSpriteFramesWithFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrameCache_addSpriteFramesWithFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrameCache_getSpriteFrameByName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrameCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrameCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrameCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrameCache_getSpriteFrameByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrameCache:getSpriteFrameByName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrameCache_getSpriteFrameByName'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSpriteFrameByName(arg0);
        object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:getSpriteFrameByName",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrameCache_getSpriteFrameByName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrameCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrameCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrameCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::SpriteFrame* arg0;
        cocos2d::Rect arg1;
        cocos2d::Texture2D* arg2;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.SpriteFrameCache:addSpriteFrameCapInset");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrameCache:addSpriteFrameCapInset");

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 4, "cc.Texture2D",&arg2, "cc.SpriteFrameCache:addSpriteFrameCapInset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset'", nullptr);
            return 0;
        }
        cobj->addSpriteFrameCapInset(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrameCache:addSpriteFrameCapInset",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrameCache_addSpriteFrameCapInset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleData();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.ParticleData");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleData:ParticleData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleEmissionMaskCache_bakeEmissionMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleEmissionMaskCache* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleEmissionMaskCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ParticleEmissionMaskCache*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleEmissionMaskCache_bakeEmissionMask'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cocos2d::Image* arg1;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 3, "cc.Image",&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cocos2d::Image* arg1;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 3, "cc.Image",&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cocos2d::Image* arg1;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 3, "cc.Image",&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cocos2d::Image* arg1;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 3, "cc.Image",&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            bool arg3;
            ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            int arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.ParticleEmissionMaskCache:bakeEmissionMask");

            if (!ok) { break; }
            cobj->bakeEmissionMask(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleEmissionMaskCache:bakeEmissionMask",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleEmissionMaskCache_bakeEmissionMask'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleEmissionMaskCache_getEmissionMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleEmissionMaskCache* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleEmissionMaskCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ParticleEmissionMaskCache*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleEmissionMaskCache_getEmissionMask'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:getEmissionMask");

            if (!ok) { break; }
            const cocos2d::ParticleEmissionMaskDescriptor& ret = cobj->getEmissionMask(arg0);
            #pragma warning NO CONVERSION FROM NATIVE FOR ParticleEmissionMaskDescriptor;
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            unsigned int arg0;
            ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.ParticleEmissionMaskCache:getEmissionMask");

            if (!ok) { break; }
            const cocos2d::ParticleEmissionMaskDescriptor& ret = cobj->getEmissionMask(arg0);
            #pragma warning NO CONVERSION FROM NATIVE FOR ParticleEmissionMaskDescriptor;
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleEmissionMaskCache:getEmissionMask",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleEmissionMaskCache_getEmissionMask'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParticleSystem();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParticleSystem");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:ParticleSystem",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setAnimationDescriptor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setAnimationDescriptor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::vector<unsigned short> arg0;
            ok &= luaval_to_std_vector_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            cobj->setAnimationDescriptor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::vector<unsigned short> arg0;
            ok &= luaval_to_std_vector_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            cobj->setAnimationDescriptor(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            std::vector<unsigned short> arg3;
            ok &= luaval_to_std_vector_ushort(tolua_S, 5, &arg3, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            cobj->setAnimationDescriptor(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            std::vector<unsigned short> arg3;
            ok &= luaval_to_std_vector_ushort(tolua_S, 5, &arg3, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.ParticleSystem:setAnimationDescriptor");

            if (!ok) { break; }
            cobj->setAnimationDescriptor(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleSystem:setAnimationDescriptor",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setAnimationDescriptor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getTexture(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getStartColor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getStartColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getStartColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setPosVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setPosVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:setPosVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setPosVar'", nullptr);
            return 0;
        }
        cobj->setPosVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setPosVar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setPosVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setHSVVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setHSVVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::HSV arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR HSV
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setHSVVar'", nullptr);
            return 0;
        }
        cobj->setHSVVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHSVVar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setHSVVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getGravity(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getGravity'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getGravity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getGravity",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getGravity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setEndColor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.ParticleSystem:setEndColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setEndColor'", nullptr);
            return 0;
        }
        cobj->setEndColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_addAnimationIndex(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_addAnimationIndex'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            cocos2d::SpriteFrame* arg1;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 3, "cc.SpriteFrame",&arg1, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            unsigned short arg0;
            ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.ParticleSystem:addAnimationIndex");

            if (!ok) { break; }
            bool ret = cobj->addAnimationIndex(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleSystem:addAnimationIndex",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_addAnimationIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setTexture(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.ParticleSystem:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getPosVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getPosVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getPosVar'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosVar();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getPosVar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getPosVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getSourcePosition(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getSourcePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getSourcePosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSourcePosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getSourcePosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getSourcePosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setEndColorVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setEndColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.ParticleSystem:setEndColorVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setEndColorVar'", nullptr);
            return 0;
        }
        cobj->setEndColorVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEndColorVar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setEndColorVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setEmissionShape(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setEmissionShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned short arg0;
        cocos2d::EmissionShape arg1;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setEmissionShape");

        #pragma warning NO CONVERSION TO NATIVE FOR EmissionShape
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setEmissionShape'", nullptr);
            return 0;
        }
        cobj->setEmissionShape(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setEmissionShape",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setEmissionShape'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setRectForUndefinedIndices(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setRectForUndefinedIndices'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.ParticleSystem:setRectForUndefinedIndices");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setRectForUndefinedIndices'", nullptr);
            return 0;
        }
        cobj->setRectForUndefinedIndices(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setRectForUndefinedIndices",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setRectForUndefinedIndices'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getHSVVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getHSVVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getHSVVar'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHSVVar();
        #pragma warning NO CONVERSION FROM NATIVE FOR HSV;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHSVVar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getHSVVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getHSV(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getHSV'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getHSV'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHSV();
        #pragma warning NO CONVERSION FROM NATIVE FOR HSV;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getHSV",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getHSV'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setSourcePosition(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setSourcePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:setSourcePosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setSourcePosition'", nullptr);
            return 0;
        }
        cobj->setSourcePosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setSourcePosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setSourcePosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_stop(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:stop",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_stop'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_start(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_start'", nullptr);
            return 0;
        }
        cobj->start();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:start",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_start'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_addEmissionShape(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_addEmissionShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EmissionShape arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR EmissionShape
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_addEmissionShape'", nullptr);
            return 0;
        }
        cobj->addEmissionShape(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:addEmissionShape",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_addEmissionShape'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setStartColor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.ParticleSystem:setStartColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setStartColor'", nullptr);
            return 0;
        }
        cobj->setStartColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setStartColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setGravity(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ParticleSystem:setGravity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setGravity'", nullptr);
            return 0;
        }
        cobj->setGravity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setGravity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setGravity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getEndColorVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getEndColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getEndColorVar'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEndColorVar();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndColorVar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getEndColorVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getEndColor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getEndColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEndColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getEndColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getEndColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<unsigned short> arg0;

        ok &= luaval_to_std_vector_ushort(tolua_S, 2, &arg0, "cc.ParticleSystem:setMultiAnimationRandomSpecific");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific'", nullptr);
            return 0;
        }
        cobj->setMultiAnimationRandomSpecific(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setMultiAnimationRandomSpecific",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setMultiAnimationRandomSpecific'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setHSV(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setHSV'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::HSV arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR HSV
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setHSV'", nullptr);
            return 0;
        }
        cobj->setHSV(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setHSV",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setHSV'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_getBlendFunc(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_setStartColorVar(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_setStartColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.ParticleSystem:setStartColorVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParticleSystem_setStartColorVar'", nullptr);
            return 0;
        }
        cobj->setStartColorVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem:setStartColorVar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_setStartColorVar'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParticleSystem_initWithDictionary(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParticleSystem_initWithDictionary'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.ParticleSystem:initWithDictionary");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.ParticleSystem:initWithDictionary");

            if (!ok) { break; }
            bool ret = cobj->initWithDictionary(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.ParticleSystem:initWithDictionary");

            if (!ok) { break; }
            bool ret = cobj->initWithDictionary(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleSystem:initWithDictionary",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParticleSystem_initWithDictionary'.",&tolua_err);
#endif

    return 0;
}
