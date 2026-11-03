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

int lua_cc_base_EaseSineOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseSineOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseSineOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseSineOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseSineOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseSineOut:EaseSineOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseSineOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseSineInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseSineInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseSineInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseSineInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseSineInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseSineInOut:EaseSineInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseSineInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBounceIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBounceIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBounceIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBounceIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBounceIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBounceIn:EaseBounceIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBounceIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBounceOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBounceOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBounceOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBounceOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBounceOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBounceOut:EaseBounceOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBounceOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBounceInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBounceInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBounceInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBounceInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBounceInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBounceInOut:EaseBounceInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBounceInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBackIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBackIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBackIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBackIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBackIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBackIn:EaseBackIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBackIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBackOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBackOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBackOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBackOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBackOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBackOut:EaseBackOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBackOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBackInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBackInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBackInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBackInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBackInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBackInOut:EaseBackInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBackInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuadraticActionIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuadraticActionIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuadraticActionIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuadraticActionIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuadraticActionIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuadraticActionIn:EaseQuadraticActionIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuadraticActionIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuadraticActionOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuadraticActionOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuadraticActionOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuadraticActionOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuadraticActionOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuadraticActionOut:EaseQuadraticActionOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuadraticActionOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuadraticActionInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuadraticActionInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuadraticActionInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuadraticActionInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuadraticActionInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuadraticActionInOut:EaseQuadraticActionInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuadraticActionInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuarticActionIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuarticActionIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuarticActionIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuarticActionIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuarticActionIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuarticActionIn:EaseQuarticActionIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuarticActionIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuarticActionOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuarticActionOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuarticActionOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuarticActionOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuarticActionOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuarticActionOut:EaseQuarticActionOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuarticActionOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuarticActionInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuarticActionInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuarticActionInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuarticActionInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuarticActionInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuarticActionInOut:EaseQuarticActionInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuarticActionInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuinticActionIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuinticActionIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuinticActionIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuinticActionIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuinticActionIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuinticActionIn:EaseQuinticActionIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuinticActionIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuinticActionOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuinticActionOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuinticActionOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuinticActionOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuinticActionOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuinticActionOut:EaseQuinticActionOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuinticActionOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseQuinticActionInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseQuinticActionInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseQuinticActionInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseQuinticActionInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseQuinticActionInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseQuinticActionInOut:EaseQuinticActionInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseQuinticActionInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCircleActionIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCircleActionIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCircleActionIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCircleActionIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCircleActionIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCircleActionIn:EaseCircleActionIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCircleActionIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCircleActionOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCircleActionOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCircleActionOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCircleActionOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCircleActionOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCircleActionOut:EaseCircleActionOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCircleActionOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCircleActionInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCircleActionInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCircleActionInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCircleActionInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCircleActionInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCircleActionInOut:EaseCircleActionInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCircleActionInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCubicActionIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCubicActionIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCubicActionIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCubicActionIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCubicActionIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCubicActionIn:EaseCubicActionIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCubicActionIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCubicActionOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCubicActionOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCubicActionOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCubicActionOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCubicActionOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCubicActionOut:EaseCubicActionOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCubicActionOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseCubicActionInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseCubicActionInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseCubicActionInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseCubicActionInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseCubicActionInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseCubicActionInOut:EaseCubicActionInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseCubicActionInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseIn:EaseIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseOut:EaseOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseInOut:EaseInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseElasticIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseElasticIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseElasticIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseElasticIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseElasticIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElasticIn:EaseElasticIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseElasticIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseElasticOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseElasticOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseElasticOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseElasticOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseElasticOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElasticOut:EaseElasticOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseElasticOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseElasticInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseElasticInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseElasticInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseElasticInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseElasticInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseElasticInOut:EaseElasticInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseElasticInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseBezierAction_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseBezierAction* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseBezierAction_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseBezierAction();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseBezierAction");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseBezierAction:EaseBezierAction",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseBezierAction_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Show_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Show* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Show_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Show();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Show");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Show:Show",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Show_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Hide_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Hide* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Hide_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Hide();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Hide");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Hide:Hide",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Hide_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ToggleVisibility_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ToggleVisibility* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ToggleVisibility_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ToggleVisibility();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ToggleVisibility");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ToggleVisibility:ToggleVisibility",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ToggleVisibility_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RemoveSelf_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RemoveSelf* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RemoveSelf_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::RemoveSelf();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RemoveSelf");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RemoveSelf:RemoveSelf",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RemoveSelf_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FlipX_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FlipX* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FlipX_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FlipX();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FlipX");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipX:FlipX",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FlipX_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FlipY_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FlipY* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FlipY_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FlipY();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FlipY");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipY:FlipY",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FlipY_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Place_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Place* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Place_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Place();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Place");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Place:Place",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Place_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Place_initWithPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Place* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Place",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Place*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Place_initWithPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Place:initWithPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Place_initWithPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithPosition(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Place:initWithPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Place_initWithPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Place_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Place",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Place:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Place_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Place::create(arg0);
        object_to_luaval<cocos2d::Place>(tolua_S, "cc.Place",(cocos2d::Place*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Place:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Place_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_CallFunc_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CallFunc* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CallFunc_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CallFunc();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CallFunc");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CallFunc:CallFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CallFunc_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_GridAction_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GridAction* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridAction",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::GridAction*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_GridAction_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.GridAction:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.GridAction:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_GridAction_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridAction:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_GridAction_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Grid3DAction_getGridRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Grid3DAction* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Grid3DAction",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Grid3DAction*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Grid3DAction_getGridRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Grid3DAction_getGridRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getGridRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Grid3DAction:getGridRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Grid3DAction_getGridRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_StopGrid_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::StopGrid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_StopGrid_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::StopGrid();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.StopGrid");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.StopGrid:StopGrid",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_StopGrid_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ReuseGrid_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ReuseGrid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ReuseGrid_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ReuseGrid();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ReuseGrid");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ReuseGrid:ReuseGrid",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ReuseGrid_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Waves3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Waves3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Waves3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Waves3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:Waves3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Waves3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Waves3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Waves3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Waves3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Waves3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Waves3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Waves3D:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Waves3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Waves3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Waves3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Waves3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Waves3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Waves3D:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Waves3D:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Waves3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Waves3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Waves3D>(tolua_S, "cc.Waves3D",(cocos2d::Waves3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Waves3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FlipX3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FlipX3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FlipX3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FlipX3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FlipX3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipX3D:FlipX3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FlipX3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FlipX3D_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FlipX3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FlipX3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FlipX3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FlipX3D_initWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FlipX3D:initWithSize");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.FlipX3D:initWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FlipX3D_initWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSize(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipX3D:initWithSize",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FlipX3D_initWithSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FlipY3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FlipY3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FlipY3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FlipY3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FlipY3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FlipY3D:FlipY3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FlipY3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Lens3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Lens3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Lens3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Lens3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Lens3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:Lens3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Lens3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Lens3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Lens3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Lens3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Lens3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Lens3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        double arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Lens3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Lens3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Lens3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Lens3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Lens3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Lens3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Lens3D_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Lens3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Lens3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Lens3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Lens3D_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Lens3D:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Lens3D_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Lens3D_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Lens3D_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Lens3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Lens3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Lens3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Lens3D_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Lens3D_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Lens3D:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Lens3D_getPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Lens3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Lens3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Lens3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Lens3D:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Lens3D:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Lens3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Lens3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Lens3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Lens3D>(tolua_S, "cc.Lens3D",(cocos2d::Lens3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Lens3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Lens3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Ripple3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Ripple3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Ripple3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Ripple3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Ripple3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:Ripple3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Ripple3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Ripple3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Ripple3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Ripple3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Ripple3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Ripple3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        double arg3;
        unsigned int arg4;
        double arg5;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Ripple3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Ripple3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Ripple3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Ripple3D:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "cc.Ripple3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.Ripple3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Ripple3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:initWithDuration",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Ripple3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Ripple3D_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Ripple3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Ripple3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Ripple3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Ripple3D_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Ripple3D:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Ripple3D_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Ripple3D_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Ripple3D_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Ripple3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Ripple3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Ripple3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Ripple3D_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Ripple3D_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ripple3D:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Ripple3D_getPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Ripple3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Ripple3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        double arg3;
        unsigned int arg4;
        double arg5;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Ripple3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Ripple3D:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Ripple3D:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Ripple3D:create");
        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "cc.Ripple3D:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.Ripple3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Ripple3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Ripple3D::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::Ripple3D>(tolua_S, "cc.Ripple3D",(cocos2d::Ripple3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Ripple3D:create",argc, 6);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Ripple3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Shaky3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Shaky3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Shaky3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Shaky3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Shaky3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Shaky3D:Shaky3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Shaky3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Shaky3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Shaky3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Shaky3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Shaky3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Shaky3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Shaky3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Shaky3D:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Shaky3D:initWithDuration");

        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.Shaky3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Shaky3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Shaky3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Shaky3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Shaky3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Shaky3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Shaky3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Shaky3D:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Shaky3D:create");
        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.Shaky3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Shaky3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Shaky3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Shaky3D>(tolua_S, "cc.Shaky3D",(cocos2d::Shaky3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Shaky3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Shaky3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Liquid_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Liquid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Liquid_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Liquid();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Liquid");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:Liquid",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Liquid_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Liquid_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Liquid* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Liquid",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Liquid*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Liquid_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Liquid:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Liquid:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Liquid:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Liquid:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Liquid_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Liquid:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Liquid_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Liquid_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Liquid",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Liquid:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Liquid:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Liquid:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Liquid:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Liquid_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Liquid::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::Liquid>(tolua_S, "cc.Liquid",(cocos2d::Liquid*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Liquid:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Liquid_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Waves_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Waves* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Waves();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Waves");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:Waves",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Waves_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Waves* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Waves",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Waves*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Waves_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        bool arg4;
        bool arg5;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Waves:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Waves:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Waves:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Waves:initWithDuration");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.Waves:initWithDuration");

        ok &= luaval_to_boolean(tolua_S, 7,&arg5, "cc.Waves:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Waves:initWithDuration",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Waves_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Waves",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        bool arg4;
        bool arg5;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Waves:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Waves:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Waves:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Waves:create");
        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.Waves:create");
        ok &= luaval_to_boolean(tolua_S, 7,&arg5, "cc.Waves:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Waves_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Waves::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::Waves>(tolua_S, "cc.Waves",(cocos2d::Waves*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Waves:create",argc, 6);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Waves_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Twirl_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Twirl* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Twirl_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Twirl();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Twirl");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:Twirl",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Twirl_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Twirl_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Twirl* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Twirl",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Twirl*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Twirl_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        unsigned int arg3;
        double arg4;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Twirl:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Twirl:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Twirl:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.Twirl:initWithDuration");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.Twirl:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Twirl_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:initWithDuration",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Twirl_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Twirl_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Twirl* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Twirl",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Twirl*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Twirl_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Twirl:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Twirl_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Twirl_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Twirl_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Twirl* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Twirl",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Twirl*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Twirl_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Twirl_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Twirl:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Twirl_getPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Twirl_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Twirl",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        unsigned int arg3;
        double arg4;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Twirl:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Twirl:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.Twirl:create");
        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.Twirl:create");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.Twirl:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Twirl_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Twirl::create(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<cocos2d::Twirl>(tolua_S, "cc.Twirl",(cocos2d::Twirl*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Twirl:create",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Twirl_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ActionManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ActionManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ActionManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:ActionManager",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionManager_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionManager_resumeTargets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionManager_resumeTargets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::Node *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.ActionManager:resumeTargets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionManager_resumeTargets'", nullptr);
            return 0;
        }
        cobj->resumeTargets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:resumeTargets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionManager_resumeTargets'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionManager_pauseAllRunningActions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionManager_pauseAllRunningActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionManager_pauseAllRunningActions'", nullptr);
            return 0;
        }
        auto&& ret = cobj->pauseAllRunningActions();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionManager:pauseAllRunningActions",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionManager_pauseAllRunningActions'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_PageTurn3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PageTurn3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PageTurn3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PageTurn3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_PageTurn3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::PageTurn3D::create(arg0, arg1);
        object_to_luaval<cocos2d::PageTurn3D>(tolua_S, "cc.PageTurn3D",(cocos2d::PageTurn3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PageTurn3D:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_PageTurn3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ProgressTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ProgressTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ProgressTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressTo:ProgressTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ProgressFromTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProgressFromTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ProgressFromTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ProgressFromTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ProgressFromTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProgressFromTo:ProgressFromTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ProgressFromTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShakyTiles3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShakyTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShakyTiles3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ShakyTiles3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ShakyTiles3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShakyTiles3D:ShakyTiles3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShakyTiles3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShakyTiles3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShakyTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ShakyTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ShakyTiles3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ShakyTiles3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShakyTiles3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShakyTiles3D:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.ShakyTiles3D:initWithDuration");

        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ShakyTiles3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShakyTiles3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShakyTiles3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShakyTiles3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShakyTiles3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShakyTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShakyTiles3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShakyTiles3D:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.ShakyTiles3D:create");
        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ShakyTiles3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShakyTiles3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ShakyTiles3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ShakyTiles3D>(tolua_S, "cc.ShakyTiles3D",(cocos2d::ShakyTiles3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShakyTiles3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShakyTiles3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ShatteredTiles3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShatteredTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShatteredTiles3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ShatteredTiles3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ShatteredTiles3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShatteredTiles3D:ShatteredTiles3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShatteredTiles3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShatteredTiles3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShatteredTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ShatteredTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ShatteredTiles3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ShatteredTiles3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShatteredTiles3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShatteredTiles3D:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.ShatteredTiles3D:initWithDuration");

        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ShatteredTiles3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShatteredTiles3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShatteredTiles3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShatteredTiles3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShatteredTiles3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShatteredTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        int arg2;
        bool arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShatteredTiles3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShatteredTiles3D:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.ShatteredTiles3D:create");
        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.ShatteredTiles3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShatteredTiles3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ShatteredTiles3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ShatteredTiles3D>(tolua_S, "cc.ShatteredTiles3D",(cocos2d::ShatteredTiles3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShatteredTiles3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShatteredTiles3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ShuffleTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShuffleTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShuffleTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ShuffleTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ShuffleTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShuffleTiles:ShuffleTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShuffleTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShuffleTiles_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShuffleTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ShuffleTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ShuffleTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ShuffleTiles_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShuffleTiles:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShuffleTiles:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.ShuffleTiles:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShuffleTiles_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShuffleTiles:initWithDuration",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShuffleTiles_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShuffleTiles_getDelta(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ShuffleTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ShuffleTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ShuffleTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ShuffleTiles_getDelta'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ShuffleTiles:getDelta");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShuffleTiles_getDelta'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDelta(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ShuffleTiles:getDelta",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShuffleTiles_getDelta'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ShuffleTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShuffleTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ShuffleTiles:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.ShuffleTiles:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.ShuffleTiles:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ShuffleTiles_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ShuffleTiles::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::ShuffleTiles>(tolua_S, "cc.ShuffleTiles",(cocos2d::ShuffleTiles*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShuffleTiles:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ShuffleTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FadeOutTRTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutTRTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeOutTRTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeOutTRTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutTRTiles:FadeOutTRTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutTRTiles_turnOnTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutTRTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FadeOutTRTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FadeOutTRTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FadeOutTRTiles_turnOnTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FadeOutTRTiles:turnOnTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_turnOnTile'", nullptr);
            return 0;
        }
        cobj->turnOnTile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutTRTiles:turnOnTile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_turnOnTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutTRTiles_turnOffTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutTRTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FadeOutTRTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FadeOutTRTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FadeOutTRTiles_turnOffTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FadeOutTRTiles:turnOffTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_turnOffTile'", nullptr);
            return 0;
        }
        cobj->turnOffTile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutTRTiles:turnOffTile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_turnOffTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutTRTiles_transformTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutTRTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FadeOutTRTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FadeOutTRTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FadeOutTRTiles_transformTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FadeOutTRTiles:transformTile");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.FadeOutTRTiles:transformTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_transformTile'", nullptr);
            return 0;
        }
        cobj->transformTile(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutTRTiles:transformTile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_transformTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutTRTiles_testFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutTRTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FadeOutTRTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FadeOutTRTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FadeOutTRTiles_testFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FadeOutTRTiles:testFunc");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.FadeOutTRTiles:testFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_testFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->testFunc(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutTRTiles:testFunc",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_testFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutTRTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FadeOutTRTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeOutTRTiles:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FadeOutTRTiles:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutTRTiles_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FadeOutTRTiles::create(arg0, arg1);
        object_to_luaval<cocos2d::FadeOutTRTiles>(tolua_S, "cc.FadeOutTRTiles",(cocos2d::FadeOutTRTiles*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeOutTRTiles:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutTRTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FadeOutBLTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutBLTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutBLTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeOutBLTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeOutBLTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutBLTiles:FadeOutBLTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutBLTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutBLTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FadeOutBLTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeOutBLTiles:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FadeOutBLTiles:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutBLTiles_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FadeOutBLTiles::create(arg0, arg1);
        object_to_luaval<cocos2d::FadeOutBLTiles>(tolua_S, "cc.FadeOutBLTiles",(cocos2d::FadeOutBLTiles*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeOutBLTiles:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutBLTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FadeOutUpTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutUpTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutUpTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeOutUpTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeOutUpTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutUpTiles:FadeOutUpTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutUpTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutUpTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FadeOutUpTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeOutUpTiles:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FadeOutUpTiles:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutUpTiles_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FadeOutUpTiles::create(arg0, arg1);
        object_to_luaval<cocos2d::FadeOutUpTiles>(tolua_S, "cc.FadeOutUpTiles",(cocos2d::FadeOutUpTiles*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeOutUpTiles:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutUpTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FadeOutDownTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOutDownTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutDownTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeOutDownTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeOutDownTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOutDownTiles:FadeOutDownTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutDownTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOutDownTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FadeOutDownTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeOutDownTiles:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FadeOutDownTiles:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOutDownTiles_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FadeOutDownTiles::create(arg0, arg1);
        object_to_luaval<cocos2d::FadeOutDownTiles>(tolua_S, "cc.FadeOutDownTiles",(cocos2d::FadeOutDownTiles*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeOutDownTiles:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOutDownTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TurnOffTiles_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TurnOffTiles_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TurnOffTiles();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TurnOffTiles");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TurnOffTiles:TurnOffTiles",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TurnOffTiles_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TurnOffTiles_turnOnTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TurnOffTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TurnOffTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TurnOffTiles_turnOnTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TurnOffTiles:turnOnTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TurnOffTiles_turnOnTile'", nullptr);
            return 0;
        }
        cobj->turnOnTile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TurnOffTiles:turnOnTile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TurnOffTiles_turnOnTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TurnOffTiles_turnOffTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TurnOffTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TurnOffTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TurnOffTiles_turnOffTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TurnOffTiles:turnOffTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TurnOffTiles_turnOffTile'", nullptr);
            return 0;
        }
        cobj->turnOffTile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TurnOffTiles:turnOffTile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TurnOffTiles_turnOffTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TurnOffTiles_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TurnOffTiles* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TurnOffTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TurnOffTiles*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TurnOffTiles_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TurnOffTiles:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.TurnOffTiles:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.TurnOffTiles:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TurnOffTiles_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TurnOffTiles:initWithDuration",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TurnOffTiles_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TurnOffTiles_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TurnOffTiles",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TurnOffTiles:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.TurnOffTiles:create");
            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.TurnOffTiles:create");
            if (!ok) { break; }
            cocos2d::TurnOffTiles* ret = cocos2d::TurnOffTiles::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::TurnOffTiles>(tolua_S, "cc.TurnOffTiles",(cocos2d::TurnOffTiles*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TurnOffTiles:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.TurnOffTiles:create");
            if (!ok) { break; }
            cocos2d::TurnOffTiles* ret = cocos2d::TurnOffTiles::create(arg0, arg1);
            object_to_luaval<cocos2d::TurnOffTiles>(tolua_S, "cc.TurnOffTiles",(cocos2d::TurnOffTiles*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.TurnOffTiles:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TurnOffTiles_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_WavesTiles3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::WavesTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_WavesTiles3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::WavesTiles3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.WavesTiles3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:WavesTiles3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_WavesTiles3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_WavesTiles3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::WavesTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.WavesTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::WavesTiles3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_WavesTiles3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.WavesTiles3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.WavesTiles3D:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.WavesTiles3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.WavesTiles3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_WavesTiles3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.WavesTiles3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_WavesTiles3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_WavesTiles3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.WavesTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.WavesTiles3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.WavesTiles3D:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.WavesTiles3D:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.WavesTiles3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_WavesTiles3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::WavesTiles3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::WavesTiles3D>(tolua_S, "cc.WavesTiles3D",(cocos2d::WavesTiles3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.WavesTiles3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_WavesTiles3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_JumpTiles3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTiles3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::JumpTiles3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.JumpTiles3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:JumpTiles3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTiles3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpTiles3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpTiles3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.JumpTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::JumpTiles3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_JumpTiles3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpTiles3D:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpTiles3D:initWithDuration");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.JumpTiles3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.JumpTiles3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTiles3D_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTiles3D:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTiles3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpTiles3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.JumpTiles3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;
        double arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpTiles3D:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpTiles3D:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.JumpTiles3D:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.JumpTiles3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTiles3D_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::JumpTiles3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::JumpTiles3D>(tolua_S, "cc.JumpTiles3D",(cocos2d::JumpTiles3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.JumpTiles3D:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTiles3D_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_SplitRows_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SplitRows* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SplitRows_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SplitRows();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SplitRows");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SplitRows:SplitRows",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SplitRows_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SplitCols_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SplitCols* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SplitCols_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SplitCols();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SplitCols");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SplitCols:SplitCols",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SplitCols_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AtlasNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AtlasNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:AtlasNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.AtlasNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_setTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_setTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextureAtlas* arg0;

        ok &= luaval_to_object<cocos2d::TextureAtlas>(tolua_S, 2, "cc.TextureAtlas",&arg0, "cc.AtlasNode:setTextureAtlas");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_setTextureAtlas'", nullptr);
            return 0;
        }
        cobj->setTextureAtlas(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:setTextureAtlas",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_setTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_getTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_getTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_getTextureAtlas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureAtlas();
        object_to_luaval<cocos2d::TextureAtlas>(tolua_S, "cc.TextureAtlas",(cocos2d::TextureAtlas*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:getTextureAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_getTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.AtlasNode:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AtlasNode_setQuadsToDraw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AtlasNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AtlasNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AtlasNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AtlasNode_setQuadsToDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.AtlasNode:setQuadsToDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AtlasNode_setQuadsToDraw'", nullptr);
            return 0;
        }
        cobj->setQuadsToDraw(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AtlasNode:setQuadsToDraw",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AtlasNode_setQuadsToDraw'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ClippingNode_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ClippingNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ClippingNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ClippingNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ClippingNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.ClippingNode:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ClippingNode_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingNode:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ClippingNode_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ClippingRectangleNode_getClippingRegion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ClippingRectangleNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ClippingRectangleNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ClippingRectangleNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ClippingRectangleNode_getClippingRegion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ClippingRectangleNode_getClippingRegion'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getClippingRegion();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingRectangleNode:getClippingRegion",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ClippingRectangleNode_getClippingRegion'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ClippingRectangleNode_setClippingRegion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ClippingRectangleNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ClippingRectangleNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ClippingRectangleNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ClippingRectangleNode_setClippingRegion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.ClippingRectangleNode:setClippingRegion");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ClippingRectangleNode_setClippingRegion'", nullptr);
            return 0;
        }
        cobj->setClippingRegion(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ClippingRectangleNode:setClippingRegion",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ClippingRectangleNode_setClippingRegion'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ClippingRectangleNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ClippingRectangleNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 0)
        {
            cocos2d::ClippingRectangleNode* ret = cocos2d::ClippingRectangleNode::create();
            object_to_luaval<cocos2d::ClippingRectangleNode>(tolua_S, "cc.ClippingRectangleNode",(cocos2d::ClippingRectangleNode*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.ClippingRectangleNode:create");
            if (!ok) { break; }
            cocos2d::ClippingRectangleNode* ret = cocos2d::ClippingRectangleNode::create(arg0);
            object_to_luaval<cocos2d::ClippingRectangleNode>(tolua_S, "cc.ClippingRectangleNode",(cocos2d::ClippingRectangleNode*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.ClippingRectangleNode:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ClippingRectangleNode_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_DrawNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::DrawNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DrawNode");
        return 1;
    }
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.DrawNode:DrawNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::DrawNode(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DrawNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:DrawNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawLine(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawLine'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Color4B arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawLine");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawLine");

        ok &=luaval_to_color4b(tolua_S, 4, &arg2, "cc.DrawNode:drawLine");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawLine'", nullptr);
            return 0;
        }
        cobj->drawLine(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawLine",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawLine'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawRect'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 5) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Color4B arg4;
            ok &=luaval_to_color4b(tolua_S, 6, &arg4, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cobj->drawRect(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cocos2d::Color4B arg2;
            ok &=luaval_to_color4b(tolua_S, 4, &arg2, "cc.DrawNode:drawRect");

            if (!ok) { break; }
            cobj->drawRect(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.DrawNode:drawRect",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawSolidCircle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawSolidCircle'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 7) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg5;
            ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg6;
            ok &=luaval_to_color4b(tolua_S, 8, &arg6, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cobj->drawSolidCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 9) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg5;
            ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg6;
            ok &=luaval_to_color4b(tolua_S, 8, &arg6, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg7;
            ok &= luaval_to_number(tolua_S, 9,&arg7, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg8;
            ok &=luaval_to_color4b(tolua_S, 10, &arg8, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cobj->drawSolidCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg4;
            ok &=luaval_to_color4b(tolua_S, 6, &arg4, "cc.DrawNode:drawSolidCircle");

            if (!ok) { break; }
            cobj->drawSolidCircle(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.DrawNode:drawSolidCircle",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawSolidCircle'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawDot(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawDot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        double arg1;
        cocos2d::Color4B arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawDot");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawDot");

        ok &=luaval_to_color4b(tolua_S, 4, &arg2, "cc.DrawNode:drawDot");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawDot'", nullptr);
            return 0;
        }
        cobj->drawDot(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawDot",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawDot'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawSegment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawSegment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        double arg2;
        cocos2d::Color4B arg3;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawSegment");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawSegment");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawSegment");

        ok &=luaval_to_color4b(tolua_S, 5, &arg3, "cc.DrawNode:drawSegment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawSegment'", nullptr);
            return 0;
        }
        cobj->drawSegment(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawSegment",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawSegment'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawCircle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawCircle'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 6) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg5;
            ok &=luaval_to_color4b(tolua_S, 7, &arg5, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            cobj->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 8) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            unsigned int arg3;
            ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            bool arg4;
            ok &= luaval_to_boolean(tolua_S, 6,&arg4, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg5;
            ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            double arg6;
            ok &= luaval_to_number(tolua_S, 8,&arg6, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            cocos2d::Color4B arg7;
            ok &=luaval_to_color4b(tolua_S, 9, &arg7, "cc.DrawNode:drawCircle");

            if (!ok) { break; }
            cobj->drawCircle(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.DrawNode:drawCircle",argc, 8);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawCircle'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawQuadBezier(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawQuadBezier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        unsigned int arg3;
        cocos2d::Color4B arg4;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawQuadBezier");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawQuadBezier");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.DrawNode:drawQuadBezier");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.DrawNode:drawQuadBezier");

        ok &=luaval_to_color4b(tolua_S, 6, &arg4, "cc.DrawNode:drawQuadBezier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawQuadBezier'", nullptr);
            return 0;
        }
        cobj->drawQuadBezier(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawQuadBezier",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawQuadBezier'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawTriangle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawTriangle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Color4B arg3;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawTriangle");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawTriangle");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.DrawNode:drawTriangle");

        ok &=luaval_to_color4b(tolua_S, 5, &arg3, "cc.DrawNode:drawTriangle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawTriangle'", nullptr);
            return 0;
        }
        cobj->drawTriangle(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawTriangle",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawTriangle'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.DrawNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawSolidRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawSolidRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Color4B arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawSolidRect");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawSolidRect");

        ok &=luaval_to_color4b(tolua_S, 4, &arg2, "cc.DrawNode:drawSolidRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawSolidRect'", nullptr);
            return 0;
        }
        cobj->drawSolidRect(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawSolidRect",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawSolidRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec2 arg0;
        double arg1;
        cocos2d::Color4B arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawPoint");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.DrawNode:drawPoint");

        ok &=luaval_to_color4b(tolua_S, 4, &arg2, "cc.DrawNode:drawPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawPoint'", nullptr);
            return 0;
        }
        cobj->drawPoint(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawPoint",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_DrawNode_drawCubicBezier(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_DrawNode_drawCubicBezier'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        unsigned int arg4;
        cocos2d::Color4B arg5;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.DrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.DrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.DrawNode:drawCubicBezier");

        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.DrawNode:drawCubicBezier");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "cc.DrawNode:drawCubicBezier");

        ok &=luaval_to_color4b(tolua_S, 7, &arg5, "cc.DrawNode:drawCubicBezier");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DrawNode_drawCubicBezier'", nullptr);
            return 0;
        }
        cobj->drawCubicBezier(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode:drawCubicBezier",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DrawNode_drawCubicBezier'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_enableShadow(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_enableShadow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Color4B arg0;
        cocos2d::Vec2 arg1;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableShadow");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Label:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::Color4B arg0;
        cocos2d::Vec2 arg1;
        int arg2;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "cc.Label:enableShadow");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Label:enableShadow");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:enableShadow",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_enableShadow'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getString(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getString();
        lua_pushlstring(tolua_S,ret.data(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getString",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setTTFConfig(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setTTFConfig'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::_ttfConfig arg0;

        ok &= luaval_to_ttfconfig(tolua_S, 2, &arg0, "cc.Label:setTTFConfig");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_setTTFConfig'", nullptr);
            return 0;
        }
        auto&& ret = cobj->setTTFConfig(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setTTFConfig",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setTTFConfig'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getTextColor(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getTextColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getTextColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getTextColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getBlendFunc(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_getShadowOffset(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_getShadowOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_getShadowOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getShadowOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:getShadowOffset",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_getShadowOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setString(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Label_setString'", nullptr);
            return 0;
        }
        cobj->setString(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Label:setString",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_setBMFontFilePath(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_setBMFontFilePath'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:setBMFontFilePath");

            if (!ok) { break; }
            bool ret = cobj->setBMFontFilePath(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Label:setBMFontFilePath",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_setBMFontFilePath'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Label_initWithTTF(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Label_initWithTTF'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::_ttfConfig arg0;
            ok &= luaval_to_ttfconfig(tolua_S, 2, &arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::_ttfConfig arg0;
            ok &= luaval_to_ttfconfig(tolua_S, 2, &arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::_ttfConfig arg0;
            ok &= luaval_to_ttfconfig(tolua_S, 2, &arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            int arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 6) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Label:initWithTTF");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Label:initWithTTF");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Label:initWithTTF");

            if (!ok) { break; }
            cocos2d::TextVAlignment arg5;
            ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Label:initWithTTF");

            if (!ok) { break; }
            bool ret = cobj->initWithTTF(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Label:initWithTTF",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Label_initWithTTF'.",&tolua_err);
#endif

    return 0;
}
