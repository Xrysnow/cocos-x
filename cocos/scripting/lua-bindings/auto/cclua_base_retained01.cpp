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

int lua_cc_base_Console_setCommandSeparator(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Console* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Console",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Console*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Console_setCommandSeparator'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "cc.Console:setCommandSeparator");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Console_setCommandSeparator'", nullptr);
            return 0;
        }
        cobj->setCommandSeparator(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Console:setCommandSeparator",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Console_setCommandSeparator'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerCustom_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerCustom* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerCustom_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerCustom();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerCustom");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerCustom:EventListenerCustom",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerCustom_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Texture2D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Texture2D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:Texture2D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_updateWithMipmaps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_updateWithMipmaps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        cocos2d::_MipmapInfo* arg0;
        int arg1;
        cocos2d::backend::PixelFormat arg2;
        cocos2d::backend::PixelFormat arg3;
        int arg4;
        int arg5;

        #pragma warning NO CONVERSION TO NATIVE FOR _MipmapInfo*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:updateWithMipmaps");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateWithMipmaps'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateWithMipmaps(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 7) 
    {
        cocos2d::_MipmapInfo* arg0;
        int arg1;
        cocos2d::backend::PixelFormat arg2;
        cocos2d::backend::PixelFormat arg3;
        int arg4;
        int arg5;
        bool arg6;

        #pragma warning NO CONVERSION TO NATIVE FOR _MipmapInfo*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "cc.Texture2D:updateWithMipmaps");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateWithMipmaps'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateWithMipmaps(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 8) 
    {
        cocos2d::_MipmapInfo* arg0;
        int arg1;
        cocos2d::backend::PixelFormat arg2;
        cocos2d::backend::PixelFormat arg3;
        int arg4;
        int arg5;
        bool arg6;
        int arg7;

        #pragma warning NO CONVERSION TO NATIVE FOR _MipmapInfo*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "cc.Texture2D:updateWithMipmaps");

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "cc.Texture2D:updateWithMipmaps");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateWithMipmaps'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateWithMipmaps(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:updateWithMipmaps",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_updateWithMipmaps'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_initWithString'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            cocos2d::FontDefinition arg1;
            ok &= luaval_to_fontdefinition(tolua_S, 3, &arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 6) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextVAlignment arg5;
            ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 7) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextVAlignment arg5;
            ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool arg6;
            ok &= luaval_to_boolean(tolua_S, 8,&arg6, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 8) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Texture2D:initWithString"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            cocos2d::TextVAlignment arg5;
            ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool arg6;
            ok &= luaval_to_boolean(tolua_S, 8,&arg6, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            int arg7;
            ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "cc.Texture2D:initWithString");

            if (!ok) { break; }
            bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Texture2D:initWithString",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_initWithString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_drawInRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_drawInRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Rect arg0;
        double arg1;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.Texture2D:drawInRect");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Texture2D:drawInRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_drawInRect'", nullptr);
            return 0;
        }
        cobj->drawInRect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:drawInRect",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_drawInRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_getContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_getContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_getContentSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getContentSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getContentSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_getContentSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_updateTextureDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_updateTextureDescriptor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::TextureDescriptor arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR TextureDescriptor
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateTextureDescriptor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateTextureDescriptor(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::backend::TextureDescriptor arg0;
        bool arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR TextureDescriptor
		ok = false;

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Texture2D:updateTextureDescriptor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateTextureDescriptor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateTextureDescriptor(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:updateTextureDescriptor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_updateTextureDescriptor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_getContentSizeInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_getContentSizeInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_getContentSizeInPixels'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getContentSizeInPixels();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:getContentSizeInPixels",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_getContentSizeInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_drawAtPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_drawAtPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Texture2D:drawAtPoint");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Texture2D:drawAtPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_drawAtPoint'", nullptr);
            return 0;
        }
        cobj->drawAtPoint(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:drawAtPoint",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_drawAtPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Texture2D_updateWithSubData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Texture2D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Texture2D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Texture2D_updateWithSubData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        void* arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:updateWithSubData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateWithSubData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateWithSubData(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 6) 
    {
        void* arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        int arg5;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Texture2D:updateWithSubData");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Texture2D:updateWithSubData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Texture2D_updateWithSubData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->updateWithSubData(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Texture2D:updateWithSubData",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Texture2D_updateWithSubData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Touch();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Touch");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:Touch",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getPreviousLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getPreviousLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getPreviousLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPreviousLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getPreviousLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getPreviousLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getDelta(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getDelta'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getDelta'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDelta();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getDelta",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getDelta'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getStartLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getStartLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getStartLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getStartLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getStartLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getStartLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getStartLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getStartLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getStartLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getStartLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getID'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getID",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getID'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Touch_getPreviousLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Touch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Touch",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Touch*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Touch_getPreviousLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Touch_getPreviousLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPreviousLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Touch:getPreviousLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Touch_getPreviousLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Event_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Event* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Event::Type arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Event:Event");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Event_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Event(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Event");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Event:Event",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Event_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventTouch_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventTouch* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventTouch_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventTouch();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventTouch");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventTouch:EventTouch",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventTouch_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventKeyboard_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventKeyboard* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::EventKeyboard::KeyCode arg0;
        bool arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventKeyboard:EventKeyboard");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.EventKeyboard:EventKeyboard");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventKeyboard_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventKeyboard(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventKeyboard");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventKeyboard:EventKeyboard",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventKeyboard_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Node();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Node");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:Node",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_addChild(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_addChild'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:addChild");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Node:addChild");

            if (!ok) { break; }
            cobj->addChild(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:addChild");

            if (!ok) { break; }
            cobj->addChild(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:addChild");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Node:addChild");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Node:addChild");

            if (!ok) { break; }
            cobj->addChild(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:addChild");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Node:addChild");

            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.Node:addChild");

            if (!ok) { break; }
            cobj->addChild(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:addChild",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_addChild'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_removeComponent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_removeComponent'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Component* arg0;
            ok &= luaval_to_object<cocos2d::Component>(tolua_S, 2, "cc.Component",&arg0, "cc.Node:removeComponent");

            if (!ok) { break; }
            bool ret = cobj->removeComponent(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Node:removeComponent");

            if (!ok) { break; }
            bool ret = cobj->removeComponent(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:removeComponent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_removeComponent'.",&tolua_err);
#endif

    return 0;
}

#if CC_USE_PHYSICS
int lua_cc_base_Node_setPhysicsBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setPhysicsBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PhysicsBody* arg0;

        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.Node:setPhysicsBody");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setPhysicsBody'", nullptr);
            return 0;
        }
        cobj->setPhysicsBody(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPhysicsBody",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setPhysicsBody'.",&tolua_err);
#endif

    return 0;
}
#endif

int lua_cc_base_Node_getOnExitTransitionDidStartCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getOnExitTransitionDidStartCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getOnExitTransitionDidStartCallback'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOnExitTransitionDidStartCallback();
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getOnExitTransitionDidStartCallback",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getOnExitTransitionDidStartCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getChildren(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getChildren'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::Node *>& ret = cobj->getChildren();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::Node *>& ret = cobj->getChildren();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getChildren",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getChildren'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setOnExitCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setOnExitCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setOnExitCallback'", nullptr);
            return 0;
        }
        cobj->setOnExitCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOnExitCallback",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setOnExitCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertToWorldSpaceAR(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertToWorldSpaceAR'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:convertToWorldSpaceAR");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertToWorldSpaceAR'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToWorldSpaceAR(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertToWorldSpaceAR",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertToWorldSpaceAR'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_updateDisplayedOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_updateDisplayedOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.Node:updateDisplayedOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_updateDisplayedOpacity'", nullptr);
            return 0;
        }
        cobj->updateDisplayedOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:updateDisplayedOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_updateDisplayedOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setCameraMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setCameraMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned short arg0;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.Node:setCameraMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setCameraMask'", nullptr);
            return 0;
        }
        cobj->setCameraMask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        unsigned short arg0;
        bool arg1;

        ok &= luaval_to_ushort(tolua_S, 2, &arg0, "cc.Node:setCameraMask");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Node:setCameraMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setCameraMask'", nullptr);
            return 0;
        }
        cobj->setCameraMask(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setCameraMask",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setCameraMask'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getNodeToWorldAffineTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getNodeToWorldAffineTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getNodeToWorldAffineTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNodeToWorldAffineTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getNodeToWorldAffineTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getNodeToWorldAffineTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getNodeToWorldTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getNodeToWorldTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getNodeToWorldTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNodeToWorldTransform();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getNodeToWorldTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getNodeToWorldTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getPosition3D(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getPosition3D'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getPosition3D'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition3D();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPosition3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getPosition3D'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertToWorldSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertToWorldSpace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:convertToWorldSpace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertToWorldSpace'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToWorldSpace(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertToWorldSpace",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertToWorldSpace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setOnEnterCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setOnEnterCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setOnEnterCallback'", nullptr);
            return 0;
        }
        cobj->setOnEnterCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOnEnterCallback",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setOnEnterCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setNormalizedPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setNormalizedPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:setNormalizedPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setNormalizedPosition'", nullptr);
            return 0;
        }
        cobj->setNormalizedPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setNormalizedPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setNormalizedPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertTouchToNodeSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertTouchToNodeSpace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "cc.Node:convertTouchToNodeSpace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertTouchToNodeSpace'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertTouchToNodeSpace(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertTouchToNodeSpace",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertTouchToNodeSpace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            bool arg0;
            ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Node:removeAllChildrenWithCleanup");

            if (!ok) { break; }
            cobj->removeAllChildrenWithCleanup(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->removeAllChildren();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:removeAllChildren",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setOnEnterTransitionDidFinishCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setOnEnterTransitionDidFinishCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setOnEnterTransitionDidFinishCallback'", nullptr);
            return 0;
        }
        cobj->setOnEnterTransitionDidFinishCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOnEnterTransitionDidFinishCallback",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setOnEnterTransitionDidFinishCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setProgramState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setProgramState'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::ProgramState* arg0;
            ok &= luaval_to_object<cocos2d::backend::ProgramState>(tolua_S, 2, "ccb.ProgramState",&arg0, "cc.Node:setProgramState");

            if (!ok) { break; }
            bool ret = cobj->setProgramState(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::backend::ProgramState* arg0;
            ok &= luaval_to_object<cocos2d::backend::ProgramState>(tolua_S, 2, "ccb.ProgramState",&arg0, "cc.Node:setProgramState");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Node:setProgramState");

            if (!ok) { break; }
            bool ret = cobj->setProgramState(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            unsigned int arg0;
            ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Node:setProgramState");

            if (!ok) { break; }
            cobj->setProgramState(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:setProgramState",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setProgramState'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getNodeToParentAffineTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getNodeToParentAffineTransform'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:getNodeToParentAffineTransform");

            if (!ok) { break; }
            cocos2d::AffineTransform ret = cobj->getNodeToParentAffineTransform(arg0);
            affinetransform_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::AffineTransform ret = cobj->getNodeToParentAffineTransform();
            affinetransform_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getNodeToParentAffineTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getNodeToParentAffineTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getRotation3D(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getRotation3D'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getRotation3D'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRotation3D();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getRotation3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getRotation3D'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getNodeToParentTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getNodeToParentTransform'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Node:getNodeToParentTransform");

            if (!ok) { break; }
            cocos2d::Mat4 ret = cobj->getNodeToParentTransform(arg0);
            mat4_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Mat4& ret = cobj->getNodeToParentTransform();
            mat4_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getNodeToParentTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getNodeToParentTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertTouchToNodeSpaceAR(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertTouchToNodeSpaceAR'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0, "cc.Node:convertTouchToNodeSpaceAR");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertTouchToNodeSpaceAR'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertTouchToNodeSpaceAR(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertTouchToNodeSpaceAR",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertTouchToNodeSpaceAR'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertToNodeSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertToNodeSpace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:convertToNodeSpace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertToNodeSpace'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToNodeSpace(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertToNodeSpace",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertToNodeSpace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setPositionNormalized(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setPositionNormalized'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:setPositionNormalized");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setPositionNormalized'", nullptr);
            return 0;
        }
        cobj->setPositionNormalized(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPositionNormalized",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setPositionNormalized'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setPosition'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Node:setPosition");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Node:setPosition");

            if (!ok) { break; }
            cobj->setPosition(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:setPosition");

            if (!ok) { break; }
            cobj->setPosition(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setRotation3D(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setRotation3D'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Node:setRotation3D");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setRotation3D'", nullptr);
            return 0;
        }
        cobj->setRotation3D(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setRotation3D",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setRotation3D'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setNodeToParentTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setNodeToParentTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Mat4 arg0;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Node:setNodeToParentTransform");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setNodeToParentTransform'", nullptr);
            return 0;
        }
        cobj->setNodeToParentTransform(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setNodeToParentTransform",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setNodeToParentTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getAnchorPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getAnchorPoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_convertToNodeSpaceAR(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_convertToNodeSpaceAR'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:convertToNodeSpaceAR");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_convertToNodeSpaceAR'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToNodeSpaceAR(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:convertToNodeSpaceAR",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_convertToNodeSpaceAR'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_visit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_visit'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cobj->visit();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Renderer* arg0;
            ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.Node:visit");

            if (!ok) { break; }
            cocos2d::Mat4 arg1;
            ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Node:visit");

            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Node:visit");

            if (!ok) { break; }
            cobj->visit(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:visit",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_visit'.",&tolua_err);
#endif

    return 0;
}

#if CC_USE_PHYSICS
int lua_cc_base_Node_getPhysicsBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getPhysicsBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getPhysicsBody'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPhysicsBody();
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPhysicsBody",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getPhysicsBody'.",&tolua_err);
#endif

    return 0;
}
#endif

int lua_cc_base_Node_getAnchorPointInPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getAnchorPointInPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getAnchorPointInPoints'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPointInPoints();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getAnchorPointInPoints",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getAnchorPointInPoints'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getOnEnterTransitionDidFinishCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getOnEnterTransitionDidFinishCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getOnEnterTransitionDidFinishCallback'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOnEnterTransitionDidFinishCallback();
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getOnEnterTransitionDidFinishCallback",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getOnEnterTransitionDidFinishCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getDisplayedColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getDisplayedColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getDisplayedColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDisplayedColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getDisplayedColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getDisplayedColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getScheduler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getScheduler'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::Scheduler* ret = cobj->getScheduler();
            object_to_luaval<cocos2d::Scheduler>(tolua_S, "cc.Scheduler",(cocos2d::Scheduler*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::Scheduler* ret = cobj->getScheduler();
            object_to_luaval<cocos2d::Scheduler>(tolua_S, "cc.Scheduler",(cocos2d::Scheduler*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getScheduler",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getScheduler'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getParentToNodeAffineTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getParentToNodeAffineTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getParentToNodeAffineTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getParentToNodeAffineTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getParentToNodeAffineTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getParentToNodeAffineTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getPositionNormalized(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getPositionNormalized'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getPositionNormalized'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPositionNormalized();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getPositionNormalized",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getPositionNormalized'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.Node:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getParent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getParent'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::Node* ret = cobj->getParent();
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::Node* ret = cobj->getParent();
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getParent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getParent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_hitTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_hitTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Node:hitTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_hitTest'", nullptr);
            return 0;
        }
        auto&& ret = cobj->hitTest(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:hitTest",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_hitTest'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_updateDisplayedColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_updateDisplayedColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.Node:updateDisplayedColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_updateDisplayedColor'", nullptr);
            return 0;
        }
        cobj->updateDisplayedColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:updateDisplayedColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_updateDisplayedColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getParentToNodeTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getParentToNodeTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getParentToNodeTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getParentToNodeTransform();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getParentToNodeTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getParentToNodeTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_isScheduled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_isScheduled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Node:isScheduled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_isScheduled'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isScheduled(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:isScheduled",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_isScheduled'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getWorldPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getWorldPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getWorldPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWorldPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getWorldPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getWorldPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getWorldToNodeAffineTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getWorldToNodeAffineTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getWorldToNodeAffineTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWorldToNodeAffineTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getWorldToNodeAffineTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getWorldToNodeAffineTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.Node:setOpacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setOpacity'", nullptr);
            return 0;
        }
        cobj->setOpacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOpacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setOpacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getContentSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getContentSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getContentSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getContentSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getBoundingBox(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getBoundingBox'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getBoundingBox'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoundingBox();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getBoundingBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getBoundingBox'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_draw'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cobj->draw();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Renderer* arg0;
            ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.Node:draw");

            if (!ok) { break; }
            cocos2d::Mat4 arg1;
            ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Node:draw");

            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Node:draw");

            if (!ok) { break; }
            cobj->draw(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:draw",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_draw'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_removeFromParentAndCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_removeFromParentAndCleanup'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            bool arg0;
            ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Node:removeFromParentAndCleanup");

            if (!ok) { break; }
            cobj->removeFromParentAndCleanup(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->removeFromParent();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:removeFromParent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_removeFromParentAndCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setPosition3D(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setPosition3D'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Node:setPosition3D");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setPosition3D'", nullptr);
            return 0;
        }
        cobj->setPosition3D(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setPosition3D",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setPosition3D'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getWorldToNodeTransform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getWorldToNodeTransform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getWorldToNodeTransform'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWorldToNodeTransform();
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getWorldToNodeTransform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getWorldToNodeTransform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getNormalizedPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getNormalizedPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_getNormalizedPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNormalizedPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:getNormalizedPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getNormalizedPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_setOnExitTransitionDidStartCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_setOnExitTransitionDidStartCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Node_setOnExitTransitionDidStartCallback'", nullptr);
            return 0;
        }
        cobj->setOnExitTransitionDidStartCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setOnExitTransitionDidStartCallback",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_setOnExitTransitionDidStartCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Node_getActionManager(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Node_getActionManager'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::ActionManager* ret = cobj->getActionManager();
            object_to_luaval<cocos2d::ActionManager>(tolua_S, "cc.ActionManager",(cocos2d::ActionManager*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::ActionManager* ret = cobj->getActionManager();
            object_to_luaval<cocos2d::ActionManager>(tolua_S, "cc.ActionManager",(cocos2d::ActionManager*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Node:getActionManager",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Node_getActionManager'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Scene_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Scene();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Scene");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:Scene",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_constructor'.",&tolua_err);
#endif

    return 0;
}

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initWithPhysics(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_initWithPhysics'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_initWithPhysics'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithPhysics();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:initWithPhysics",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_initWithPhysics'.",&tolua_err);
#endif

    return 0;
}
#endif

int lua_cc_base_Scene_render(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_render'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;

        ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.Scene:render");

        ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Scene:render");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_render'", nullptr);
            return 0;
        }
        cobj->render(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::Renderer* arg0;
        cocos2d::Mat4 arg1;
        const cocos2d::Mat4* arg2;

        ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.Scene:render");

        ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Scene:render");

        ok &= luaval_to_object<const cocos2d::Mat4>(tolua_S, 4, "cc.Mat4",&arg2, "cc.Scene:render");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_render'", nullptr);
            return 0;
        }
        cobj->render(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:render",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_render'.",&tolua_err);
#endif

    return 0;
}

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION) || CC_USE_NAVMESH)
int lua_cc_base_Scene_stepPhysicsAndNavigation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_stepPhysicsAndNavigation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Scene:stepPhysicsAndNavigation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_stepPhysicsAndNavigation'", nullptr);
            return 0;
        }
        cobj->stepPhysicsAndNavigation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:stepPhysicsAndNavigation",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_stepPhysicsAndNavigation'.",&tolua_err);
#endif

    return 0;
}
#endif

#if CC_USE_PHYSICS
int lua_cc_base_Scene_getPhysicsWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_getPhysicsWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_getPhysicsWorld'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPhysicsWorld();
        object_to_luaval<cocos2d::PhysicsWorld>(tolua_S, "cc.PhysicsWorld",(cocos2d::PhysicsWorld*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:getPhysicsWorld",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_getPhysicsWorld'.",&tolua_err);
#endif

    return 0;
}
#endif

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_initPhysicsWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_initPhysicsWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_initPhysicsWorld'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initPhysicsWorld();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:initPhysicsWorld",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_initPhysicsWorld'.",&tolua_err);
#endif

    return 0;
}
#endif

int lua_cc_base_Scene_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scene* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scene*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scene_initWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Scene:initWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_initWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scene:initWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_initWithSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Scene_createWithSize(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Scene:createWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_createWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Scene::createWithSize(arg0);
        object_to_luaval<cocos2d::Scene>(tolua_S, "cc.Scene",(cocos2d::Scene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Scene:createWithSize",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_createWithSize'.",&tolua_err);
#endif
    return 0;
}

#if (CC_USE_PHYSICS || (CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION))
int lua_cc_base_Scene_createWithPhysics(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Scene",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scene_createWithPhysics'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Scene::createWithPhysics();
        object_to_luaval<cocos2d::Scene>(tolua_S, "cc.Scene",(cocos2d::Scene*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Scene:createWithPhysics",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scene_createWithPhysics'.",&tolua_err);
#endif
    return 0;
}
#endif

int lua_cc_base_GLView_getViewPortRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getViewPortRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getViewPortRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getViewPortRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getViewPortRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getViewPortRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getSafeAreaRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getSafeAreaRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getSafeAreaRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSafeAreaRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getSafeAreaRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getSafeAreaRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getFrameSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getFrameSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getFrameSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFrameSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getFrameSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getFrameSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getVisibleOrigin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getVisibleOrigin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getVisibleOrigin'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleOrigin();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getVisibleOrigin",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getVisibleOrigin'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getDesignResolutionSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getDesignResolutionSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getDesignResolutionSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDesignResolutionSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getDesignResolutionSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getDesignResolutionSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_setIcon(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_setIcon'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::vector<std::string_view> arg0;
            ok &= luaval_to_std_vector_string_view(tolua_S, 2, &arg0, "cc.GLView:setIcon");

            if (!ok) { break; }
            cobj->setIcon(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.GLView:setIcon");

            if (!ok) { break; }
            cobj->setIcon(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.GLView:setIcon",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_setIcon'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getScissorRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getScissorRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getScissorRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScissorRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getScissorRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getScissorRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getVisibleRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getVisibleRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getVisibleRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getVisibleRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getVisibleRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_getVisibleSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GLView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GLView_getVisibleSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getVisibleSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLView:getVisibleSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getVisibleSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GLView_setGLContextAttrs(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        GLContextAttrs arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR GLContextAttrs
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_setGLContextAttrs'", nullptr);
            return 0;
        }
        cocos2d::GLView::setGLContextAttrs(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLView:setGLContextAttrs",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_setGLContextAttrs'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_GLView_getGLContextAttrs(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GLView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GLView_getGLContextAttrs'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::GLView::getGLContextAttrs();
        #pragma warning NO CONVERSION FROM NATIVE FOR GLContextAttrs;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GLView:getGLContextAttrs",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GLView_getGLContextAttrs'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Director_getAxmolThreadId(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getAxmolThreadId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getAxmolThreadId'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCocos2dThreadId();
        std_thread_id_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getAxmolThreadId",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getAxmolThreadId'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getWinSizeInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getWinSizeInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getWinSizeInPixels'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWinSizeInPixels();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getWinSizeInPixels",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getWinSizeInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getSafeAreaRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getSafeAreaRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getSafeAreaRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSafeAreaRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getSafeAreaRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getSafeAreaRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_loadMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_loadMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::MATRIX_STACK_TYPE arg0;
        cocos2d::Mat4 arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Director:loadMatrix");

        ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Director:loadMatrix");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_loadMatrix'", nullptr);
            return 0;
        }
        cobj->loadMatrix(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:loadMatrix",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_loadMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getWinSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getWinSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getWinSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWinSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getWinSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getWinSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getVisibleOrigin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getVisibleOrigin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getVisibleOrigin'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleOrigin();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getVisibleOrigin",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getVisibleOrigin'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_convertToUI(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_convertToUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Director:convertToUI");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_convertToUI'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToUI(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:convertToUI",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_convertToUI'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::MATRIX_STACK_TYPE arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Director:getMatrix");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getMatrix'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMatrix(arg0);
        mat4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getMatrix",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_setClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_setClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.Director:setClearColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_setClearColor'", nullptr);
            return 0;
        }
        cobj->setClearColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:setClearColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_setClearColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_convertToGL(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_convertToGL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Director:convertToGL");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_convertToGL'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToGL(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:convertToGL",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_convertToGL'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderer();
        object_to_luaval<cocos2d::Renderer>(tolua_S, "cc.Renderer",(cocos2d::Renderer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getRenderer'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_multiplyMatrix(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_multiplyMatrix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::MATRIX_STACK_TYPE arg0;
        cocos2d::Mat4 arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Director:multiplyMatrix");

        ok &= luaval_to_mat4(tolua_S, 3, &arg1, "cc.Director:multiplyMatrix");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_multiplyMatrix'", nullptr);
            return 0;
        }
        cobj->multiplyMatrix(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:multiplyMatrix",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_multiplyMatrix'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getVisibleSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Director* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Director*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Director_getVisibleSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getVisibleSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Director:getVisibleSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getVisibleSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Director_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Director",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Director_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Director::getInstance();
        object_to_luaval<cocos2d::Director>(tolua_S, "cc.Director",(cocos2d::Director*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Director:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Director_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Scheduler_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scheduler* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scheduler_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Scheduler();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Scheduler");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scheduler:Scheduler",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scheduler_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Scheduler_performFunctionInCocosThread(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Scheduler* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Scheduler*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Scheduler_performFunctionInCocosThread'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Scheduler_performFunctionInCocosThread'", nullptr);
            return 0;
        }
        cobj->performFunctionInCocosThread(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Scheduler:performFunctionInCocosThread",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Scheduler_performFunctionInCocosThread'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AsyncTaskPool_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AsyncTaskPool* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AsyncTaskPool_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AsyncTaskPool();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.AsyncTaskPool");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AsyncTaskPool:AsyncTaskPool",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AsyncTaskPool_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AsyncTaskPool_enqueue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AsyncTaskPool* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AsyncTaskPool",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::AsyncTaskPool*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AsyncTaskPool_enqueue'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::AsyncTaskPool::TaskType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.AsyncTaskPool:enqueue");

            if (!ok) { break; }
            std::function<void ()> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->enqueue(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::AsyncTaskPool::TaskType arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.AsyncTaskPool:enqueue");

            if (!ok) { break; }
            std::function<void (void *)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            void* arg2;
            #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

            if (!ok) { break; }
            std::function<void ()> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->enqueue(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.AsyncTaskPool:enqueue",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AsyncTaskPool_enqueue'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AsyncTaskPool_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AsyncTaskPool",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AsyncTaskPool_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::AsyncTaskPool::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AsyncTaskPool:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AsyncTaskPool_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_AsyncTaskPool_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AsyncTaskPool",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AsyncTaskPool_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::AsyncTaskPool::getInstance();
        object_to_luaval<cocos2d::AsyncTaskPool>(tolua_S, "cc.AsyncTaskPool",(cocos2d::AsyncTaskPool*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AsyncTaskPool:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AsyncTaskPool_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Speed_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Speed* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Speed_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Speed();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Speed");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Speed:Speed",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Speed_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Follow_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Follow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Follow();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Follow");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Follow:Follow",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Follow_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Follow_initWithTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Follow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Follow",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Follow*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Follow_initWithTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:initWithTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_initWithTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTarget(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:initWithTarget");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Follow:initWithTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_initWithTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTarget(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Follow:initWithTarget",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Follow_initWithTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Follow_initWithTargetAndOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Follow* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Follow",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Follow*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Follow_initWithTargetAndOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Node* arg0;
        double arg1;
        double arg2;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:initWithTargetAndOffset");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Follow:initWithTargetAndOffset");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Follow:initWithTargetAndOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_initWithTargetAndOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTargetAndOffset(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4) 
    {
        cocos2d::Node* arg0;
        double arg1;
        double arg2;
        cocos2d::Rect arg3;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:initWithTargetAndOffset");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Follow:initWithTargetAndOffset");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Follow:initWithTargetAndOffset");

        ok &= luaval_to_rect(tolua_S, 5, &arg3, "cc.Follow:initWithTargetAndOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_initWithTargetAndOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTargetAndOffset(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Follow:initWithTargetAndOffset",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Follow_initWithTargetAndOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Follow_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Follow",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Follow::create(arg0);
        object_to_luaval<cocos2d::Follow>(tolua_S, "cc.Follow",(cocos2d::Follow*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Node* arg0;
        cocos2d::Rect arg1;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:create");
        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Follow:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Follow::create(arg0, arg1);
        object_to_luaval<cocos2d::Follow>(tolua_S, "cc.Follow",(cocos2d::Follow*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Follow:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Follow_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Follow_createWithOffset(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Follow",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::Node* arg0;
        double arg1;
        double arg2;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:createWithOffset");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Follow:createWithOffset");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Follow:createWithOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_createWithOffset'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Follow::createWithOffset(arg0, arg1, arg2);
        object_to_luaval<cocos2d::Follow>(tolua_S, "cc.Follow",(cocos2d::Follow*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Node* arg0;
        double arg1;
        double arg2;
        cocos2d::Rect arg3;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.Follow:createWithOffset");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Follow:createWithOffset");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Follow:createWithOffset");
        ok &= luaval_to_rect(tolua_S, 5, &arg3, "cc.Follow:createWithOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Follow_createWithOffset'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Follow::createWithOffset(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Follow>(tolua_S, "cc.Follow",(cocos2d::Follow*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Follow:createWithOffset",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Follow_createWithOffset'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Image_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Image* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Image_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Image();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Image");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Image:Image",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Image_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::PolygonInfo();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.PolygonInfo");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:PolygonInfo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_getRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PolygonInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PolygonInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_PolygonInfo_getRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_getRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:getRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_getRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_setQuads(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PolygonInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PolygonInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_PolygonInfo_setQuads'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::V3F_C4B_T2F_Quad* arg0;
        int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR V3F_C4B_T2F_Quad*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.PolygonInfo:setQuads");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_setQuads'", nullptr);
            return 0;
        }
        cobj->setQuads(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:setQuads",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_setQuads'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_setQuad(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PolygonInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PolygonInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_PolygonInfo_setQuad'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::V3F_C4B_T2F_Quad* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR V3F_C4B_T2F_Quad*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_setQuad'", nullptr);
            return 0;
        }
        cobj->setQuad(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:setQuad",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_setQuad'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_setTriangles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PolygonInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PolygonInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_PolygonInfo_setTriangles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TrianglesCommand::Triangles arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR Triangles
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_setTriangles'", nullptr);
            return 0;
        }
        cobj->setTriangles(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:setTriangles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_setTriangles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PolygonInfo_setRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PolygonInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PolygonInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PolygonInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_PolygonInfo_setRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.PolygonInfo:setRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PolygonInfo_setRect'", nullptr);
            return 0;
        }
        cobj->setRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PolygonInfo:setRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PolygonInfo_setRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AutoPolygon_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AutoPolygon* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.AutoPolygon:AutoPolygon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AutoPolygon_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AutoPolygon(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.AutoPolygon");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AutoPolygon:AutoPolygon",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AutoPolygon_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SpriteFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SpriteFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:SpriteFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.SpriteFrame:setAnchorPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setAnchorPoint'", nullptr);
            return 0;
        }
        cobj->setAnchorPoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setAnchorPoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setOffsetInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setOffsetInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.SpriteFrame:setOffsetInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setOffsetInPixels'", nullptr);
            return 0;
        }
        cobj->setOffsetInPixels(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setOffsetInPixels",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setOffsetInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getOriginalSizeInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getOriginalSizeInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getOriginalSizeInPixels'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOriginalSizeInPixels();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getOriginalSizeInPixels",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getOriginalSizeInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setOriginalSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setOriginalSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.SpriteFrame:setOriginalSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setOriginalSize'", nullptr);
            return 0;
        }
        cobj->setOriginalSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setOriginalSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setOriginalSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getCenterRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getCenterRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getCenterRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCenterRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getCenterRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getCenterRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setRectInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setRectInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.SpriteFrame:setRectInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setRectInPixels'", nullptr);
            return 0;
        }
        cobj->setRectInPixels(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setRectInPixels",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setRectInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setCenterRectInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setCenterRectInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.SpriteFrame:setCenterRectInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setCenterRectInPixels'", nullptr);
            return 0;
        }
        cobj->setCenterRectInPixels(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setCenterRectInPixels",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setCenterRectInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.SpriteFrame:setOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setOffset'", nullptr);
            return 0;
        }
        cobj->setOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setOffset",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_initWithTextureFilename(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_initWithTextureFilename'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            bool ret = cobj->initWithTextureFilename(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:initWithTextureFilename");

            if (!ok) { break; }
            bool ret = cobj->initWithTextureFilename(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.SpriteFrame:initWithTextureFilename",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_initWithTextureFilename'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.SpriteFrame:setRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setRect'", nullptr);
            return 0;
        }
        cobj->setRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_initWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_initWithTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 5) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            bool ret = cobj->initWithTexture(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:initWithTexture");

            if (!ok) { break; }
            bool ret = cobj->initWithTexture(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.SpriteFrame:initWithTexture",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_initWithTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getOriginalSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getOriginalSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getOriginalSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOriginalSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getOriginalSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getOriginalSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getRectInPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getRectInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getRectInPixels'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRectInPixels();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getRectInPixels",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getRectInPixels'.",&tolua_err);
#endif

    return 0;
}
