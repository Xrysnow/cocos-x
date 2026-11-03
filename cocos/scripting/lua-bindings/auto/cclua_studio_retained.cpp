#include "scripting/lua-bindings/auto/cclua_studio_auto.hpp"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCComExtensionData.h"
#include "scripting/lua-bindings/manual/cocostudio/lua-cocostudio-conversions.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cc_studio_ActionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:ActionFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionFrame_setEasingParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionFrame_setEasingParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<float> arg0;

        ok &= luaval_to_std_vector_float(tolua_S, 2, &arg0, "ccs.ActionFrame:setEasingParameter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionFrame_setEasingParameter'", nullptr);
            return 0;
        }
        cobj->setEasingParameter(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFrame:setEasingParameter",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionFrame_setEasingParameter'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionMoveFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionMoveFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionMoveFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionMoveFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:ActionMoveFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionMoveFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionMoveFrame_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionMoveFrame_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.ActionMoveFrame:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionMoveFrame_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionMoveFrame_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionMoveFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionMoveFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionMoveFrame:getAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionMoveFrame_getAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:getAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionMoveFrame_getAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionMoveFrame_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionMoveFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionMoveFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionMoveFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionMoveFrame_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionMoveFrame_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionMoveFrame:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionMoveFrame_getPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionScaleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionScaleFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionScaleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionScaleFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:ActionScaleFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionScaleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionScaleFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionScaleFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionScaleFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionScaleFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionScaleFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionScaleFrame:getAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionScaleFrame_getAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionScaleFrame:getAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionScaleFrame_getAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionRotationFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionRotationFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionRotationFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionRotationFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionRotationFrame:ActionRotationFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionRotationFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionRotationFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionRotationFrame* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionRotationFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ActionRotationFrame*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionRotationFrame_getAction'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionRotationFrame:getAction");

            if (!ok) { break; }
            cocostudio::ActionFrame* arg1;
            ok &= luaval_to_object<cocostudio::ActionFrame>(tolua_S, 3, "ccs.ActionFrame",&arg1, "ccs.ActionRotationFrame:getAction");

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0, arg1);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionRotationFrame:getAction");

            if (!ok) { break; }
            cocos2d::ActionInterval* ret = cobj->getAction(arg0);
            object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ActionRotationFrame:getAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionRotationFrame_getAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionFadeFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionFadeFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionFadeFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionFadeFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:ActionFadeFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionFadeFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionFadeFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionFadeFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionFadeFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionFadeFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionFadeFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionFadeFrame:getAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionFadeFrame_getAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionFadeFrame:getAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionFadeFrame_getAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTintFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTintFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionTintFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTintFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:ActionTintFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTintFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTintFrame_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTintFrame_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTintFrame_getColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:getColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTintFrame_getColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTintFrame_getAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTintFrame_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.ActionTintFrame:getAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTintFrame_getAction'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAction(arg0);
        object_to_luaval<cocos2d::ActionInterval>(tolua_S, "cc.ActionInterval",(cocos2d::ActionInterval*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:getAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTintFrame_getAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTintFrame_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionTintFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTintFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ActionTintFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTintFrame_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccs.ActionTintFrame:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTintFrame_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTintFrame:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTintFrame_setColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionObject_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ActionObject* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionObject_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ActionObject();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionObject");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionObject:ActionObject",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionObject_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionManagerEx_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionManagerEx_destroyInstance'", nullptr);
            return 0;
        }
        cocostudio::ActionManagerEx::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionManagerEx:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionManagerEx_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_ActionManagerEx_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionManagerEx_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocostudio::ActionManagerEx::getInstance();
        object_to_luaval<cocostudio::ActionManagerEx>(tolua_S, "ccs.ActionManagerEx",(cocostudio::ActionManagerEx*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionManagerEx:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionManagerEx_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_BaseData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BaseData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::BaseData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BaseData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:BaseData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BaseData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BaseData_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BaseData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BaseData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BaseData_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BaseData_getColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:getColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BaseData_getColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BaseData_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BaseData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BaseData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::BaseData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BaseData_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccs.BaseData:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BaseData_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BaseData:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BaseData_setColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::DisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.DisplayData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayData:DisplayData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayData_changeDisplayToTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.DisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.DisplayData:changeDisplayToTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayData_changeDisplayToTexture'", nullptr);
            return 0;
        }
        auto&& ret = cocostudio::DisplayData::changeDisplayToTexture(arg0);
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.DisplayData:changeDisplayToTexture",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayData_changeDisplayToTexture'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_SpriteDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SpriteDisplayData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SpriteDisplayData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::SpriteDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.SpriteDisplayData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SpriteDisplayData:SpriteDisplayData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SpriteDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SpriteDisplayData_copy(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SpriteDisplayData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SpriteDisplayData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SpriteDisplayData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SpriteDisplayData_copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::DisplayData* arg0;

        ok &= luaval_to_object<cocostudio::DisplayData>(tolua_S, 2, "ccs.DisplayData",&arg0, "ccs.SpriteDisplayData:copy");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SpriteDisplayData_copy'", nullptr);
            return 0;
        }
        cobj->copy(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SpriteDisplayData:copy",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SpriteDisplayData_copy'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDisplayData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDisplayData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ArmatureDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureDisplayData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDisplayData:ArmatureDisplayData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ParticleDisplayData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ParticleDisplayData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ParticleDisplayData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ParticleDisplayData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ParticleDisplayData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ParticleDisplayData:ParticleDisplayData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ParticleDisplayData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::BoneData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::BoneData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BoneData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneData:BoneData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ArmatureData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:ArmatureData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureData_getBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureData_getBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureData:getBoneData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureData_getBoneData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneData(arg0);
        object_to_luaval<cocostudio::BoneData>(tolua_S, "ccs.BoneData",(cocostudio::BoneData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureData:getBoneData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureData_getBoneData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_FrameData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::FrameData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_FrameData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::FrameData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.FrameData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.FrameData:FrameData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_FrameData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_FrameData_copy(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::FrameData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.FrameData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::FrameData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_FrameData_copy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const cocostudio::BaseData* arg0;

        ok &= luaval_to_object<const cocostudio::BaseData>(tolua_S, 2, "ccs.BaseData",&arg0, "ccs.FrameData:copy");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_FrameData_copy'", nullptr);
            return 0;
        }
        cobj->copy(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.FrameData:copy",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_FrameData_copy'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_MovementBoneData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementBoneData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_MovementBoneData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::MovementBoneData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.MovementBoneData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementBoneData:MovementBoneData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_MovementBoneData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_MovementData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_MovementData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::MovementData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.MovementData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:MovementData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_MovementData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_MovementData_getMovementBoneData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::MovementData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.MovementData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::MovementData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_MovementData_getMovementBoneData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.MovementData:getMovementBoneData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_MovementData_getMovementBoneData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMovementBoneData(arg0);
        object_to_luaval<cocostudio::MovementBoneData>(tolua_S, "ccs.MovementBoneData",(cocostudio::MovementBoneData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.MovementData:getMovementBoneData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_MovementData_getMovementBoneData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AnimationData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AnimationData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::AnimationData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.AnimationData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:AnimationData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AnimationData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AnimationData_getMovement(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::AnimationData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnimationData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::AnimationData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_AnimationData_getMovement'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.AnimationData:getMovement");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AnimationData_getMovement'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMovement(arg0);
        object_to_luaval<cocostudio::MovementData>(tolua_S, "ccs.MovementData",(cocostudio::MovementData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnimationData:getMovement",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AnimationData_getMovement'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ContourData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ContourData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ContourData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ContourData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ContourData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:ContourData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ContourData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ContourData_addVertex(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ContourData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ContourData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ContourData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ContourData_addVertex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.ContourData:addVertex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ContourData_addVertex'", nullptr);
            return 0;
        }
        cobj->addVertex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ContourData:addVertex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ContourData_addVertex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_TextureData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::TextureData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_TextureData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::TextureData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.TextureData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureData:TextureData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_TextureData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Tween_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Tween_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::Tween();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Tween");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:Tween",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Tween_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Tween_play(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Tween* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Tween",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Tween*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Tween_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocostudio::MovementBoneData* arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;

        ok &= luaval_to_object<cocostudio::MovementBoneData>(tolua_S, 2, "ccs.MovementBoneData",&arg0, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccs.Tween:play");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "ccs.Tween:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Tween_play'", nullptr);
            return 0;
        }
        cobj->play(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Tween:play",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Tween_play'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::DisplayManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.DisplayManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:DisplayManager",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_getAnchorPointInPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_getAnchorPointInPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_getAnchorPointInPoints'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPointInPoints();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getAnchorPointInPoints",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_getAnchorPointInPoints'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_getContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_getContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_getContentSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getContentSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getContentSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_getContentSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_getBoundingBox(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_getBoundingBox'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_getBoundingBox'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoundingBox();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getBoundingBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_getBoundingBox'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_containPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_containPoint'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            bool ret = cobj->containPoint(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccs.DisplayManager:containPoint");

            if (!ok) { break; }
            bool ret = cobj->containPoint(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.DisplayManager:containPoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_containPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_changeDisplayWithName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_changeDisplayWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        bool arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.DisplayManager:changeDisplayWithName");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.DisplayManager:changeDisplayWithName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_changeDisplayWithName'", nullptr);
            return 0;
        }
        cobj->changeDisplayWithName(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:changeDisplayWithName",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_changeDisplayWithName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_getAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_getAnchorPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getAnchorPoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_DisplayManager_getDecorativeDisplayList(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::DisplayManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.DisplayManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::DisplayManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_DisplayManager_getDecorativeDisplayList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_DisplayManager_getDecorativeDisplayList'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDecorativeDisplayList();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.DisplayManager:getDecorativeDisplayList",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_DisplayManager_getDecorativeDisplayList'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::Bone();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Bone");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:Bone",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccs.Bone:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_updateColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_updateColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_updateColor'", nullptr);
            return 0;
        }
        cobj->updateColor();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:updateColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_updateColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Bone:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_removeFromParent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_removeFromParent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccs.Bone:removeFromParent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_removeFromParent'", nullptr);
            return 0;
        }
        cobj->removeFromParent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:removeFromParent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_removeFromParent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_changeDisplayWithName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Bone* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Bone*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Bone_changeDisplayWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        bool arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Bone:changeDisplayWithName");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.Bone:changeDisplayWithName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Bone_changeDisplayWithName'", nullptr);
            return 0;
        }
        cobj->changeDisplayWithName(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Bone:changeDisplayWithName",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_changeDisplayWithName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Bone_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Bone",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Bone:create");
            if (!ok) { break; }
            cocostudio::Bone* ret = cocostudio::Bone::create(arg0);
            object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Bone* ret = cocostudio::Bone::create();
            object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccs.Bone:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Bone_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_ArmatureAnimation_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ArmatureAnimation();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ArmatureAnimation");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:ArmatureAnimation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureAnimation_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureAnimation_play(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureAnimation_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_play'", nullptr);
            return 0;
        }
        cobj->play(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        int arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_play'", nullptr);
            return 0;
        }
        cobj->play(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string_view arg0;
        int arg1;
        int arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:play");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccs.ArmatureAnimation:play");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_play'", nullptr);
            return 0;
        }
        cobj->play(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:play",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureAnimation_play'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureAnimation_playWithIndexes(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureAnimation_playWithIndexes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<int> arg0;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithIndexes'", nullptr);
            return 0;
        }
        cobj->playWithIndexes(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::vector<int> arg0;
        int arg1;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithIndexes'", nullptr);
            return 0;
        }
        cobj->playWithIndexes(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::vector<int> arg0;
        int arg1;
        bool arg2;

        ok &= luaval_to_std_vector_int(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithIndexes");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccs.ArmatureAnimation:playWithIndexes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithIndexes'", nullptr);
            return 0;
        }
        cobj->playWithIndexes(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithIndexes",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureAnimation_playWithIndexes'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureAnimation_playWithNames(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureAnimation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureAnimation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureAnimation_playWithNames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<std::string> arg0;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithNames'", nullptr);
            return 0;
        }
        cobj->playWithNames(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::vector<std::string> arg0;
        int arg1;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithNames'", nullptr);
            return 0;
        }
        cobj->playWithNames(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::vector<std::string> arg0;
        int arg1;
        bool arg2;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ArmatureAnimation:playWithNames");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccs.ArmatureAnimation:playWithNames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureAnimation_playWithNames'", nullptr);
            return 0;
        }
        cobj->playWithNames(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureAnimation:playWithNames",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureAnimation_playWithNames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_removeAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_removeAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeAnimationData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_removeAnimationData'", nullptr);
            return 0;
        }
        cobj->removeAnimationData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeAnimationData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_removeAnimationData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        cocostudio::ArmatureData* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureData");

        ok &= luaval_to_object<cocostudio::ArmatureData>(tolua_S, 3, "ccs.ArmatureData",&arg1, "ccs.ArmatureDataManager:addArmatureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addArmatureData'", nullptr);
            return 0;
        }
        cobj->addArmatureData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string_view arg0;
        cocostudio::ArmatureData* arg1;
        std::string_view arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureData");

        ok &= luaval_to_object<cocostudio::ArmatureData>(tolua_S, 3, "ccs.ArmatureData",&arg1, "ccs.ArmatureDataManager:addArmatureData");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addArmatureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addArmatureData'", nullptr);
            return 0;
        }
        cobj->addArmatureData(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addArmatureData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addArmatureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addArmatureFileInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addArmatureFileInfo'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            cobj->addArmatureFileInfo(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addArmatureFileInfo");

            if (!ok) { break; }
            cobj->addArmatureFileInfo(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.ArmatureDataManager:addArmatureFileInfo",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addArmatureFileInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_removeArmatureFileInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_removeArmatureFileInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeArmatureFileInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_removeArmatureFileInfo'", nullptr);
            return 0;
        }
        cobj->removeArmatureFileInfo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeArmatureFileInfo",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_removeArmatureFileInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getTextureDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getTextureDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getTextureDatas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getTextureDatas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getTextureDatas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getTextureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getTextureData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureData(arg0);
        object_to_luaval<cocostudio::TextureData>(tolua_S, "ccs.TextureData",(cocostudio::TextureData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getTextureData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getTextureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getArmatureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getArmatureData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getArmatureData(arg0);
        object_to_luaval<cocostudio::ArmatureData>(tolua_S, "ccs.ArmatureData",(cocostudio::ArmatureData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getArmatureData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getArmatureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getAnimationData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getAnimationData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnimationData(arg0);
        object_to_luaval<cocostudio::AnimationData>(tolua_S, "ccs.AnimationData",(cocostudio::AnimationData*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getAnimationData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getAnimationData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        cocostudio::AnimationData* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addAnimationData");

        ok &= luaval_to_object<cocostudio::AnimationData>(tolua_S, 3, "ccs.AnimationData",&arg1, "ccs.ArmatureDataManager:addAnimationData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addAnimationData'", nullptr);
            return 0;
        }
        cobj->addAnimationData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string_view arg0;
        cocostudio::AnimationData* arg1;
        std::string_view arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addAnimationData");

        ok &= luaval_to_object<cocostudio::AnimationData>(tolua_S, 3, "ccs.AnimationData",&arg1, "ccs.ArmatureDataManager:addAnimationData");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addAnimationData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addAnimationData'", nullptr);
            return 0;
        }
        cobj->addAnimationData(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addAnimationData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addAnimationData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_removeArmatureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_removeArmatureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeArmatureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_removeArmatureData'", nullptr);
            return 0;
        }
        cobj->removeArmatureData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeArmatureData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_removeArmatureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getArmatureDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getArmatureDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getArmatureDatas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getArmatureDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getArmatureDatas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getArmatureDatas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addRelativeData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addRelativeData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addRelativeData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addRelativeData'", nullptr);
            return 0;
        }
        cobj->addRelativeData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addRelativeData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addRelativeData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_removeTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_removeTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:removeTextureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_removeTextureData'", nullptr);
            return 0;
        }
        cobj->removeTextureData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:removeTextureData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_removeTextureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getRelativeData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getRelativeData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:getRelativeData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getRelativeData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRelativeData(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR RelativeData*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getRelativeData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getRelativeData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addTextureData(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addTextureData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        cocostudio::TextureData* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addTextureData");

        ok &= luaval_to_object<cocostudio::TextureData>(tolua_S, 3, "ccs.TextureData",&arg1, "ccs.ArmatureDataManager:addTextureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addTextureData'", nullptr);
            return 0;
        }
        cobj->addTextureData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string_view arg0;
        cocostudio::TextureData* arg1;
        std::string_view arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addTextureData");

        ok &= luaval_to_object<cocostudio::TextureData>(tolua_S, 3, "ccs.TextureData",&arg1, "ccs.ArmatureDataManager:addTextureData");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addTextureData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addTextureData'", nullptr);
            return 0;
        }
        cobj->addTextureData(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addTextureData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addTextureData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_getAnimationDatas(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_getAnimationDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_getAnimationDatas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnimationDatas();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:getAnimationDatas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_getAnimationDatas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ArmatureDataManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ArmatureDataManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addSpriteFrameFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile'", nullptr);
            return 0;
        }
        cobj->addSpriteFrameFromFile(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ArmatureDataManager:addSpriteFrameFromFile");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccs.ArmatureDataManager:addSpriteFrameFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile'", nullptr);
            return 0;
        }
        cobj->addSpriteFrameFromFile(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ArmatureDataManager:addSpriteFrameFromFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::Armature();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Armature");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:Armature",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_getBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_getBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Armature:getBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_getBone'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBone(arg0);
        object_to_luaval<cocostudio::Bone>(tolua_S, "ccs.Bone",(cocostudio::Bone*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBone",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_getBone'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_changeBoneParent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_changeBoneParent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        std::string_view arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0, "ccs.Armature:changeBoneParent");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.Armature:changeBoneParent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_changeBoneParent'", nullptr);
            return 0;
        }
        cobj->changeBoneParent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:changeBoneParent",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_changeBoneParent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_init'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Armature:init");

            if (!ok) { break; }
            cocostudio::Bone* arg1;
            ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 3, "ccs.Bone",&arg1, "ccs.Armature:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Armature:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.Armature:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_addBone(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_addBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocostudio::Bone* arg0;
        std::string_view arg1;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0, "ccs.Armature:addBone");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.Armature:addBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_addBone'", nullptr);
            return 0;
        }
        cobj->addBone(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:addBone",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_addBone'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_getOffsetPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_getOffsetPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_getOffsetPoints'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOffsetPoints();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getOffsetPoints",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_getOffsetPoints'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccs.Armature:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_getBoneDic(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Armature* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::Armature*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Armature_getBoneDic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Armature_getBoneDic'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneDic();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Armature:getBoneDic",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_getBoneDic'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Armature_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Armature",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Armature:create");
            if (!ok) { break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0);
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Armature* ret = cocostudio::Armature::create();
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Armature:create");
            if (!ok) { break; }
            cocostudio::Bone* arg1;
            ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 3, "ccs.Bone",&arg1, "ccs.Armature:create");
            if (!ok) { break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0, arg1);
            object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccs.Armature:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Armature_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_Skin_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::Skin* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Skin_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::Skin();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Skin");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Skin:Skin",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Skin_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Skin_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Skin:create");
            if (!ok) { break; }
            cocostudio::Skin* ret = cocostudio::Skin::create(arg0);
            object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocostudio::Skin* ret = cocostudio::Skin::create();
            object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccs.Skin:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Skin_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_Skin_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.Skin",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.Skin:createWithSpriteFrameName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Skin_createWithSpriteFrameName'", nullptr);
            return 0;
        }
        auto&& ret = cocostudio::Skin::createWithSpriteFrameName(arg0);
        object_to_luaval<cocostudio::Skin>(tolua_S, "ccs.Skin",(cocostudio::Skin*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.Skin:createWithSpriteFrameName",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Skin_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_ComAttribute_getFloat(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_getFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getFloat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getFloat'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFloat(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        double arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getFloat");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.ComAttribute:getFloat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getFloat'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFloat(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getFloat",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_getFloat'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getString(arg0);
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getString");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ComAttribute:getString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getString(arg0, arg1);
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getString",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_getString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_setFloat(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_setFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        double arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:setFloat");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccs.ComAttribute:setFloat");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_setFloat'", nullptr);
            return 0;
        }
        cobj->setFloat(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setFloat",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_setFloat'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_setString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:setString");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ComAttribute:setString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_setString'", nullptr);
            return 0;
        }
        cobj->setString(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setString",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_setString'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_getBool(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_getBool'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getBool");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getBool'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBool(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        bool arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getBool");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAttribute:getBool");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getBool'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBool(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getBool",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_getBool'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_setInt(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_setInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        int arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:setInt");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ComAttribute:setInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_setInt'", nullptr);
            return 0;
        }
        cobj->setInt(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setInt",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_setInt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_parse(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_parse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:parse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_parse'", nullptr);
            return 0;
        }
        auto&& ret = cobj->parse(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:parse",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_parse'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_getInt(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_getInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getInt'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getInt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        int arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:getInt");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.ComAttribute:getInt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_getInt'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getInt(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:getInt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_getInt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAttribute_setBool(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAttribute* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAttribute",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAttribute*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAttribute_setBool'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        bool arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComAttribute:setBool");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.ComAttribute:setBool");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAttribute_setBool'", nullptr);
            return 0;
        }
        cobj->setBool(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAttribute:setBool",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAttribute_setBool'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAudio_start(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAudio_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAudio_start'", nullptr);
            return 0;
        }
        cobj->start();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:start",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAudio_start'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComAudio_stop(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComAudio* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComAudio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComAudio*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComAudio_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComAudio_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComAudio:stop",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComAudio_stop'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComController* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComController_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ComController();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ComController");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComController:ComController",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComController_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_GUIReader_setFilePath(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::GUIReader* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.GUIReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::GUIReader*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_GUIReader_setFilePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.GUIReader:setFilePath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_GUIReader_setFilePath'", nullptr);
            return 0;
        }
        cobj->setFilePath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.GUIReader:setFilePath",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_GUIReader_setFilePath'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SceneReader_setTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SceneReader_setTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Ref *, void *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SceneReader_setTarget'", nullptr);
            return 0;
        }
        cobj->setTarget(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:setTarget",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SceneReader_setTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SceneReader_createNodeWithSceneFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::SceneReader* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::SceneReader*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SceneReader_createNodeWithSceneFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.SceneReader:createNodeWithSceneFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SceneReader_createNodeWithSceneFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createNodeWithSceneFile(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        cocostudio::SceneReader::AttachComponentType arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.SceneReader:createNodeWithSceneFile");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccs.SceneReader:createNodeWithSceneFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SceneReader_createNodeWithSceneFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createNodeWithSceneFile(arg0, arg1);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SceneReader:createNodeWithSceneFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SceneReader_createNodeWithSceneFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SceneReader_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.SceneReader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SceneReader_destroyInstance'", nullptr);
            return 0;
        }
        cocostudio::SceneReader::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.SceneReader:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SceneReader_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_ActionTimelineCache_createActionFromJson(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_createActionFromJson'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionFromJson");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_createActionFromJson'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createActionFromJson(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionFromJson",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_createActionFromJson'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionWithFlatBuffersFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createActionWithFlatBuffersFile(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionWithFlatBuffersFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithFlatBuffersFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadAnimationActionWithFlatBuffersFile(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithFlatBuffersFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_createActionFromContent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_createActionFromContent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionFromContent");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ActionTimelineCache:createActionFromContent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_createActionFromContent'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createActionFromContent(arg0, arg1);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionFromContent",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_createActionFromContent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_loadAnimationActionWithContent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithContent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithContent");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ActionTimelineCache:loadAnimationActionWithContent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithContent'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadAnimationActionWithContent(arg0, arg1);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithContent",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithContent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:loadAnimationActionWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadAnimationActionWithFile(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:loadAnimationActionWithFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_removeAction(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_removeAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:removeAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_removeAction'", nullptr);
            return 0;
        }
        cobj->removeAction(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:removeAction",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_removeAction'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersForSimulator(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersForSimulator'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createActionWithFlatBuffersForSimulator");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersForSimulator'", nullptr);
            return 0;
        }
        auto&& ret = cobj->createActionWithFlatBuffersForSimulator(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineCache:createActionWithFlatBuffersForSimulator",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersForSimulator'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineCache_createAction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccs.ActionTimelineCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimelineCache:createAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineCache_createAction'", nullptr);
            return 0;
        }
        auto&& ret = cocostudio::timeline::ActionTimelineCache::createAction(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccs.ActionTimelineCache:createAction",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineCache_createAction'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_studio_Frame_getEasingParams(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Frame_getEasingParams'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Frame_getEasingParams'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEasingParams();
        ccvector_float_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:getEasingParams",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Frame_getEasingParams'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Frame_setEasingParams(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Frame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Frame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Frame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Frame_setEasingParams'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<float> arg0;

        ok &= luaval_to_std_vector_float(tolua_S, 2, &arg0, "ccs.Frame:setEasingParams");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Frame_setEasingParams'", nullptr);
            return 0;
        }
        cobj->setEasingParams(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Frame:setEasingParams",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Frame_setEasingParams'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_VisibleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::VisibleFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_VisibleFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::VisibleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.VisibleFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.VisibleFrame:VisibleFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_VisibleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_TextureFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_TextureFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::TextureFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.TextureFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:TextureFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_TextureFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_TextureFrame_setTextureName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::TextureFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.TextureFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::TextureFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_TextureFrame_setTextureName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.TextureFrame:setTextureName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_TextureFrame_setTextureName'", nullptr);
            return 0;
        }
        cobj->setTextureName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.TextureFrame:setTextureName",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_TextureFrame_setTextureName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_RotationFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_RotationFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::RotationFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.RotationFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationFrame:RotationFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_RotationFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkewFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkewFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SkewFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::SkewFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.SkewFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkewFrame:SkewFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkewFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_RotationSkewFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::RotationSkewFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_RotationSkewFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::RotationSkewFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.RotationSkewFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.RotationSkewFrame:RotationSkewFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_RotationSkewFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_PositionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_PositionFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::PositionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.PositionFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:PositionFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_PositionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_PositionFrame_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_PositionFrame_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccs.PositionFrame:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_PositionFrame_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_PositionFrame_setPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_PositionFrame_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PositionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.PositionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::PositionFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_PositionFrame_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_PositionFrame_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PositionFrame:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_PositionFrame_getPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ScaleFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ScaleFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ScaleFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ScaleFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ScaleFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ScaleFrame:ScaleFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ScaleFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AnchorPointFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AnchorPointFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::AnchorPointFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.AnchorPointFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:AnchorPointFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AnchorPointFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AnchorPointFrame_setAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnchorPointFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::AnchorPointFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_AnchorPointFrame_setAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccs.AnchorPointFrame:setAnchorPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AnchorPointFrame_setAnchorPoint'", nullptr);
            return 0;
        }
        cobj->setAnchorPoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:setAnchorPoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AnchorPointFrame_setAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AnchorPointFrame_getAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AnchorPointFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AnchorPointFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::AnchorPointFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_AnchorPointFrame_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AnchorPointFrame_getAnchorPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPoint();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AnchorPointFrame:getAnchorPoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AnchorPointFrame_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_InnerActionFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_InnerActionFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::InnerActionFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.InnerActionFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:InnerActionFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_InnerActionFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_InnerActionFrame_setAnimationName(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::InnerActionFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.InnerActionFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::InnerActionFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_InnerActionFrame_setAnimationName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.InnerActionFrame:setAnimationName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_InnerActionFrame_setAnimationName'", nullptr);
            return 0;
        }
        cobj->setAnimationName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.InnerActionFrame:setAnimationName",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_InnerActionFrame_setAnimationName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ColorFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ColorFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ColorFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ColorFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:ColorFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ColorFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ColorFrame_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ColorFrame_getColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ColorFrame_getColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:getColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ColorFrame_getColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ColorFrame_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ColorFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ColorFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ColorFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ColorFrame_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccs.ColorFrame:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ColorFrame_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ColorFrame:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ColorFrame_setColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AlphaFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AlphaFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AlphaFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::AlphaFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.AlphaFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AlphaFrame:AlphaFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AlphaFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_AlphaFrame_setAlpha(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::AlphaFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.AlphaFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::AlphaFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_AlphaFrame_setAlpha'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccs.AlphaFrame:setAlpha");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_AlphaFrame_setAlpha'", nullptr);
            return 0;
        }
        cobj->setAlpha(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.AlphaFrame:setAlpha",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_AlphaFrame_setAlpha'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_EventFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::EventFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_EventFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::EventFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.EventFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:EventFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_EventFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_EventFrame_setEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::EventFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.EventFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::EventFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_EventFrame_setEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.EventFrame:setEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_EventFrame_setEvent'", nullptr);
            return 0;
        }
        cobj->setEvent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.EventFrame:setEvent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_EventFrame_setEvent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ZOrderFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ZOrderFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ZOrderFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ZOrderFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ZOrderFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ZOrderFrame:ZOrderFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ZOrderFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BlendFuncFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BlendFuncFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BlendFuncFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::BlendFuncFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BlendFuncFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BlendFuncFrame:BlendFuncFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BlendFuncFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BlendFuncFrame_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BlendFuncFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BlendFuncFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BlendFuncFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BlendFuncFrame_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BlendFuncFrame_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BlendFuncFrame:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BlendFuncFrame_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BlendFuncFrame_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BlendFuncFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BlendFuncFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BlendFuncFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BlendFuncFrame_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccs.BlendFuncFrame:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BlendFuncFrame_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BlendFuncFrame:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BlendFuncFrame_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_PlayableFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::PlayableFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_PlayableFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::PlayableFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.PlayableFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.PlayableFrame:PlayableFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_PlayableFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Timeline_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Timeline_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::Timeline();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.Timeline");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:Timeline",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Timeline_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_Timeline_getFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::Timeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.Timeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::Timeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_Timeline_getFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_Timeline_getFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFrames();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.Timeline:getFrames",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_Timeline_getFrames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ActionTimelineData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTimelineData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineData:ActionTimelineData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ActionTimeline();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTimeline");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:ActionTimeline",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_setAnimationEndCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_setAnimationEndCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::function<void ()> arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.ActionTimeline:setAnimationEndCallFunc");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_setAnimationEndCallFunc'", nullptr);
            return 0;
        }
        cobj->setAnimationEndCallFunc(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setAnimationEndCallFunc",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_setAnimationEndCallFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_start(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_start'", nullptr);
            return 0;
        }
        cobj->start();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:start",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_start'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_setLastFrameCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_setLastFrameCallFunc'", nullptr);
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
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_setLastFrameCallFunc'", nullptr);
            return 0;
        }
        cobj->setLastFrameCallFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:setLastFrameCallFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_setLastFrameCallFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_getTimelines(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_getTimelines'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_getTimelines'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTimelines();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getTimelines",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_getTimelines'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_getAnimationInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_getAnimationInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimeline:getAnimationInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_getAnimationInfo'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnimationInfo(arg0);
        animationInfo_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:getAnimationInfo",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_getAnimationInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_addFrameEndCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_addFrameEndCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        std::string_view arg1;
        std::function<void ()> arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:addFrameEndCallFunc");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ActionTimeline:addFrameEndCallFunc");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_addFrameEndCallFunc'", nullptr);
            return 0;
        }
        cobj->addFrameEndCallFunc(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:addFrameEndCallFunc",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_addFrameEndCallFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_addAnimationInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_addAnimationInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocostudio::timeline::AnimationInfo arg0;

        ok &= luaval_to_animationInfo(tolua_S, 2, &arg0, "ccs.ActionTimeline:addAnimationInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_addAnimationInfo'", nullptr);
            return 0;
        }
        cobj->addAnimationInfo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:addAnimationInfo",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_addAnimationInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_IsAnimationInfoExists(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_IsAnimationInfoExists'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ActionTimeline:IsAnimationInfoExists");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_IsAnimationInfoExists'", nullptr);
            return 0;
        }
        auto&& ret = cobj->IsAnimationInfoExists(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:IsAnimationInfoExists",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_IsAnimationInfoExists'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimeline_removeFrameEndCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimeline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimeline*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimeline_removeFrameEndCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string_view arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccs.ActionTimeline:removeFrameEndCallFunc");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccs.ActionTimeline:removeFrameEndCallFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimeline_removeFrameEndCallFunc'", nullptr);
            return 0;
        }
        cobj->removeFrameEndCallFunc(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimeline:removeFrameEndCallFunc",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimeline_removeFrameEndCallFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::ActionTimelineNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ActionTimelineNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:ActionTimelineNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ActionTimelineNode_init(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::ActionTimelineNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ActionTimelineNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::ActionTimelineNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ActionTimelineNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        cocostudio::timeline::ActionTimeline* arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccs.ActionTimelineNode:init");

        ok &= luaval_to_object<cocostudio::timeline::ActionTimeline>(tolua_S, 3, "ccs.ActionTimeline",&arg1, "ccs.ActionTimelineNode:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ActionTimelineNode_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ActionTimelineNode:init",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ActionTimelineNode_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::BoneNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.BoneNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:BoneNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getChildBones(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getChildBones'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.BoneNode:getChildBones",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getChildBones'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getAllSubBones(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getAllSubBones'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_getAllSubBones'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAllSubBones();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getAllSubBones",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getAllSubBones'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccs.BoneNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getVisibleSkinsRect(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getVisibleSkinsRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_getVisibleSkinsRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleSkinsRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getVisibleSkinsRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getVisibleSkinsRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getAllSubSkins(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getAllSubSkins'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_getAllSubSkins'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAllSubSkins();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getAllSubSkins",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getAllSubSkins'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_displaySkin(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_displaySkin'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.BoneNode:displaySkin");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.BoneNode:displaySkin");

            if (!ok) { break; }
            cobj->displaySkin(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccs.BoneNode:displaySkin");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccs.BoneNode:displaySkin");

            if (!ok) { break; }
            cobj->displaySkin(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.BoneNode:displaySkin",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_displaySkin'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getSkins(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getSkins'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.BoneNode:getSkins",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getSkins'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_getVisibleSkins(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_getVisibleSkins'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_getVisibleSkins'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVisibleSkins();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:getVisibleSkins",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_getVisibleSkins'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_BoneNode_setDebugDrawColor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::BoneNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.BoneNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::BoneNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_BoneNode_setDebugDrawColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "ccs.BoneNode:setDebugDrawColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_BoneNode_setDebugDrawColor'", nullptr);
            return 0;
        }
        cobj->setDebugDrawColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.BoneNode:setDebugDrawColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_BoneNode_setDebugDrawColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkeletonNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SkeletonNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::timeline::SkeletonNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.SkeletonNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkeletonNode:SkeletonNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkeletonNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkeletonNode_getBoneNode(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkeletonNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkeletonNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SkeletonNode_getBoneNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.SkeletonNode:getBoneNode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SkeletonNode_getBoneNode'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneNode(arg0);
        object_to_luaval<cocostudio::timeline::BoneNode>(tolua_S, "ccs.BoneNode",(cocostudio::timeline::BoneNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkeletonNode:getBoneNode",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkeletonNode_getBoneNode'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkeletonNode_changeSkins(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkeletonNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocostudio::timeline::SkeletonNode*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SkeletonNode_changeSkins'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.SkeletonNode:changeSkins");

            if (!ok) { break; }
            cobj->changeSkins(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            tsl::robin_map<std::string, std::string, hlookup::string_hash, hlookup::equal_to> arg0;
            ok &= luaval_to_std_map_string_string(tolua_S, 2, &arg0, "ccs.SkeletonNode:changeSkins");

            if (!ok) { break; }
            cobj->changeSkins(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccs.SkeletonNode:changeSkins",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkeletonNode_changeSkins'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkeletonNode_addSkinGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkeletonNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkeletonNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SkeletonNode_addSkinGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        tsl::robin_map<std::string, std::string, hlookup::string_hash, hlookup::equal_to> arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccs.SkeletonNode:addSkinGroup");

        ok &= luaval_to_std_map_string_string(tolua_S, 3, &arg1, "ccs.SkeletonNode:addSkinGroup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SkeletonNode_addSkinGroup'", nullptr);
            return 0;
        }
        cobj->addSkinGroup(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkeletonNode:addSkinGroup",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkeletonNode_addSkinGroup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_SkeletonNode_getAllSubBonesMap(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.SkeletonNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::timeline::SkeletonNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_SkeletonNode_getAllSubBonesMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_SkeletonNode_getAllSubBonesMap'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAllSubBonesMap();
        ccmap_string_key_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.SkeletonNode:getAllSubBonesMap",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_SkeletonNode_getAllSubBonesMap'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComExtensionData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComExtensionData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComExtensionData_constructor'", nullptr);
            return 0;
        }
        cobj = new cocostudio::ComExtensionData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccs.ComExtensionData");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComExtensionData:ComExtensionData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComExtensionData_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_studio_ComExtensionData_setCustomProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocostudio::ComExtensionData* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccs.ComExtensionData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocostudio::ComExtensionData*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_studio_ComExtensionData_setCustomProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccs.ComExtensionData:setCustomProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_studio_ComExtensionData_setCustomProperty'", nullptr);
            return 0;
        }
        cobj->setCustomProperty(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccs.ComExtensionData:setCustomProperty",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_studio_ComExtensionData_setCustomProperty'.",&tolua_err);
#endif

    return 0;
}

int register_all_cc_studio_retained(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionFrame_constructor);
        tolua_function(L, "setEasingParameter", lua_cc_studio_ActionFrame_setEasingParameter);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionMoveFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionMoveFrame_constructor);
        tolua_function(L, "setPosition", lua_cc_studio_ActionMoveFrame_setPosition);
        tolua_function(L, "getAction", lua_cc_studio_ActionMoveFrame_getAction);
        tolua_function(L, "getPosition", lua_cc_studio_ActionMoveFrame_getPosition);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionScaleFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionScaleFrame_constructor);
        tolua_function(L, "getAction", lua_cc_studio_ActionScaleFrame_getAction);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionRotationFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionRotationFrame_constructor);
        tolua_function(L, "getAction", lua_cc_studio_ActionRotationFrame_getAction);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionFadeFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionFadeFrame_constructor);
        tolua_function(L, "getAction", lua_cc_studio_ActionFadeFrame_getAction);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionTintFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionTintFrame_constructor);
        tolua_function(L, "getColor", lua_cc_studio_ActionTintFrame_getColor);
        tolua_function(L, "getAction", lua_cc_studio_ActionTintFrame_getAction);
        tolua_function(L, "setColor", lua_cc_studio_ActionTintFrame_setColor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionObject");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionObject_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionManagerEx");
    if (lua_istable(L, -1)) {
        tolua_function(L, "destroyInstance", lua_cc_studio_ActionManagerEx_destroyInstance);
        tolua_function(L, "getInstance", lua_cc_studio_ActionManagerEx_getInstance);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.BaseData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_BaseData_constructor);
        tolua_function(L, "getColor", lua_cc_studio_BaseData_getColor);
        tolua_function(L, "setColor", lua_cc_studio_BaseData_setColor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.DisplayData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_DisplayData_constructor);
        tolua_function(L, "changeDisplayToTexture", lua_cc_studio_DisplayData_changeDisplayToTexture);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.SpriteDisplayData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_SpriteDisplayData_constructor);
        tolua_function(L, "copy", lua_cc_studio_SpriteDisplayData_copy);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ArmatureDisplayData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ArmatureDisplayData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ParticleDisplayData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ParticleDisplayData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.BoneData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_BoneData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ArmatureData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ArmatureData_constructor);
        tolua_function(L, "getBoneData", lua_cc_studio_ArmatureData_getBoneData);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.FrameData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_FrameData_constructor);
        tolua_function(L, "copy", lua_cc_studio_FrameData_copy);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.MovementBoneData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_MovementBoneData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.MovementData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_MovementData_constructor);
        tolua_function(L, "getMovementBoneData", lua_cc_studio_MovementData_getMovementBoneData);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.AnimationData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_AnimationData_constructor);
        tolua_function(L, "getMovement", lua_cc_studio_AnimationData_getMovement);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ContourData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ContourData_constructor);
        tolua_function(L, "addVertex", lua_cc_studio_ContourData_addVertex);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.TextureData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_TextureData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Tween");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_Tween_constructor);
        tolua_function(L, "play", lua_cc_studio_Tween_play);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.DisplayManager");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_DisplayManager_constructor);
        tolua_function(L, "getAnchorPointInPoints", lua_cc_studio_DisplayManager_getAnchorPointInPoints);
        tolua_function(L, "getContentSize", lua_cc_studio_DisplayManager_getContentSize);
        tolua_function(L, "getBoundingBox", lua_cc_studio_DisplayManager_getBoundingBox);
        tolua_function(L, "containPoint", lua_cc_studio_DisplayManager_containPoint);
        tolua_function(L, "changeDisplayWithName", lua_cc_studio_DisplayManager_changeDisplayWithName);
        tolua_function(L, "getAnchorPoint", lua_cc_studio_DisplayManager_getAnchorPoint);
        tolua_function(L, "getDecorativeDisplayList", lua_cc_studio_DisplayManager_getDecorativeDisplayList);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Bone");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_Bone_constructor);
        tolua_function(L, "setBlendFunc", lua_cc_studio_Bone_setBlendFunc);
        tolua_function(L, "updateColor", lua_cc_studio_Bone_updateColor);
        tolua_function(L, "init", lua_cc_studio_Bone_init);
        tolua_function(L, "getBlendFunc", lua_cc_studio_Bone_getBlendFunc);
        tolua_function(L, "removeFromParent", lua_cc_studio_Bone_removeFromParent);
        tolua_function(L, "changeDisplayWithName", lua_cc_studio_Bone_changeDisplayWithName);
        tolua_function(L, "create", lua_cc_studio_Bone_create);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ArmatureAnimation");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ArmatureAnimation_constructor);
        tolua_function(L, "play", lua_cc_studio_ArmatureAnimation_play);
        tolua_function(L, "playWithIndexes", lua_cc_studio_ArmatureAnimation_playWithIndexes);
        tolua_function(L, "playWithNames", lua_cc_studio_ArmatureAnimation_playWithNames);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ArmatureDataManager");
    if (lua_istable(L, -1)) {
        tolua_function(L, "removeAnimationData", lua_cc_studio_ArmatureDataManager_removeAnimationData);
        tolua_function(L, "addArmatureData", lua_cc_studio_ArmatureDataManager_addArmatureData);
        tolua_function(L, "addArmatureFileInfo", lua_cc_studio_ArmatureDataManager_addArmatureFileInfo);
        tolua_function(L, "removeArmatureFileInfo", lua_cc_studio_ArmatureDataManager_removeArmatureFileInfo);
        tolua_function(L, "getTextureDatas", lua_cc_studio_ArmatureDataManager_getTextureDatas);
        tolua_function(L, "getTextureData", lua_cc_studio_ArmatureDataManager_getTextureData);
        tolua_function(L, "getArmatureData", lua_cc_studio_ArmatureDataManager_getArmatureData);
        tolua_function(L, "getAnimationData", lua_cc_studio_ArmatureDataManager_getAnimationData);
        tolua_function(L, "addAnimationData", lua_cc_studio_ArmatureDataManager_addAnimationData);
        tolua_function(L, "removeArmatureData", lua_cc_studio_ArmatureDataManager_removeArmatureData);
        tolua_function(L, "getArmatureDatas", lua_cc_studio_ArmatureDataManager_getArmatureDatas);
        tolua_function(L, "addRelativeData", lua_cc_studio_ArmatureDataManager_addRelativeData);
        tolua_function(L, "removeTextureData", lua_cc_studio_ArmatureDataManager_removeTextureData);
        tolua_function(L, "getRelativeData", lua_cc_studio_ArmatureDataManager_getRelativeData);
        tolua_function(L, "addTextureData", lua_cc_studio_ArmatureDataManager_addTextureData);
        tolua_function(L, "getAnimationDatas", lua_cc_studio_ArmatureDataManager_getAnimationDatas);
        tolua_function(L, "addSpriteFrameFromFile", lua_cc_studio_ArmatureDataManager_addSpriteFrameFromFile);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Armature");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_Armature_constructor);
        tolua_function(L, "getBone", lua_cc_studio_Armature_getBone);
        tolua_function(L, "changeBoneParent", lua_cc_studio_Armature_changeBoneParent);
        tolua_function(L, "init", lua_cc_studio_Armature_init);
        tolua_function(L, "getBlendFunc", lua_cc_studio_Armature_getBlendFunc);
        tolua_function(L, "addBone", lua_cc_studio_Armature_addBone);
        tolua_function(L, "getOffsetPoints", lua_cc_studio_Armature_getOffsetPoints);
        tolua_function(L, "setBlendFunc", lua_cc_studio_Armature_setBlendFunc);
        tolua_function(L, "getBoneDic", lua_cc_studio_Armature_getBoneDic);
        tolua_function(L, "create", lua_cc_studio_Armature_create);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Skin");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_Skin_constructor);
        tolua_function(L, "create", lua_cc_studio_Skin_create);
        tolua_function(L, "createWithSpriteFrameName", lua_cc_studio_Skin_createWithSpriteFrameName);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ComAttribute");
    if (lua_istable(L, -1)) {
        tolua_function(L, "getFloat", lua_cc_studio_ComAttribute_getFloat);
        tolua_function(L, "getString", lua_cc_studio_ComAttribute_getString);
        tolua_function(L, "setFloat", lua_cc_studio_ComAttribute_setFloat);
        tolua_function(L, "setString", lua_cc_studio_ComAttribute_setString);
        tolua_function(L, "getBool", lua_cc_studio_ComAttribute_getBool);
        tolua_function(L, "setInt", lua_cc_studio_ComAttribute_setInt);
        tolua_function(L, "parse", lua_cc_studio_ComAttribute_parse);
        tolua_function(L, "getInt", lua_cc_studio_ComAttribute_getInt);
        tolua_function(L, "setBool", lua_cc_studio_ComAttribute_setBool);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ComAudio");
    if (lua_istable(L, -1)) {
        tolua_function(L, "start", lua_cc_studio_ComAudio_start);
        tolua_function(L, "stop", lua_cc_studio_ComAudio_stop);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ComController");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ComController_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.GUIReader");
    if (lua_istable(L, -1)) {
        tolua_function(L, "setFilePath", lua_cc_studio_GUIReader_setFilePath);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.SceneReader");
    if (lua_istable(L, -1)) {
        tolua_function(L, "setTarget", lua_cc_studio_SceneReader_setTarget);
        tolua_function(L, "createNodeWithSceneFile", lua_cc_studio_SceneReader_createNodeWithSceneFile);
        tolua_function(L, "destroyInstance", lua_cc_studio_SceneReader_destroyInstance);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionTimelineCache");
    if (lua_istable(L, -1)) {
        tolua_function(L, "createActionFromJson", lua_cc_studio_ActionTimelineCache_createActionFromJson);
        tolua_function(L, "createActionWithFlatBuffersFile", lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersFile);
        tolua_function(L, "loadAnimationActionWithFlatBuffersFile", lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFlatBuffersFile);
        tolua_function(L, "createActionFromContent", lua_cc_studio_ActionTimelineCache_createActionFromContent);
        tolua_function(L, "loadAnimationActionWithContent", lua_cc_studio_ActionTimelineCache_loadAnimationActionWithContent);
        tolua_function(L, "loadAnimationActionWithFile", lua_cc_studio_ActionTimelineCache_loadAnimationActionWithFile);
        tolua_function(L, "removeAction", lua_cc_studio_ActionTimelineCache_removeAction);
        tolua_function(L, "createActionWithFlatBuffersForSimulator", lua_cc_studio_ActionTimelineCache_createActionWithFlatBuffersForSimulator);
        tolua_function(L, "createAction", lua_cc_studio_ActionTimelineCache_createAction);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Frame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "getEasingParams", lua_cc_studio_Frame_getEasingParams);
        tolua_function(L, "setEasingParams", lua_cc_studio_Frame_setEasingParams);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.VisibleFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_VisibleFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.TextureFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_TextureFrame_constructor);
        tolua_function(L, "setTextureName", lua_cc_studio_TextureFrame_setTextureName);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.RotationFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_RotationFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.SkewFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_SkewFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.RotationSkewFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_RotationSkewFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.PositionFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_PositionFrame_constructor);
        tolua_function(L, "setPosition", lua_cc_studio_PositionFrame_setPosition);
        tolua_function(L, "getPosition", lua_cc_studio_PositionFrame_getPosition);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ScaleFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ScaleFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.AnchorPointFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_AnchorPointFrame_constructor);
        tolua_function(L, "setAnchorPoint", lua_cc_studio_AnchorPointFrame_setAnchorPoint);
        tolua_function(L, "getAnchorPoint", lua_cc_studio_AnchorPointFrame_getAnchorPoint);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.InnerActionFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_InnerActionFrame_constructor);
        tolua_function(L, "setAnimationName", lua_cc_studio_InnerActionFrame_setAnimationName);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ColorFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ColorFrame_constructor);
        tolua_function(L, "getColor", lua_cc_studio_ColorFrame_getColor);
        tolua_function(L, "setColor", lua_cc_studio_ColorFrame_setColor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.AlphaFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_AlphaFrame_constructor);
        tolua_function(L, "setAlpha", lua_cc_studio_AlphaFrame_setAlpha);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.EventFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_EventFrame_constructor);
        tolua_function(L, "setEvent", lua_cc_studio_EventFrame_setEvent);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ZOrderFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ZOrderFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.BlendFuncFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_BlendFuncFrame_constructor);
        tolua_function(L, "getBlendFunc", lua_cc_studio_BlendFuncFrame_getBlendFunc);
        tolua_function(L, "setBlendFunc", lua_cc_studio_BlendFuncFrame_setBlendFunc);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.PlayableFrame");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_PlayableFrame_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.Timeline");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_Timeline_constructor);
        tolua_function(L, "getFrames", lua_cc_studio_Timeline_getFrames);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionTimelineData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionTimelineData_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionTimeline");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionTimeline_constructor);
        tolua_function(L, "setAnimationEndCallFunc", lua_cc_studio_ActionTimeline_setAnimationEndCallFunc);
        tolua_function(L, "start", lua_cc_studio_ActionTimeline_start);
        tolua_function(L, "setLastFrameCallFunc", lua_cc_studio_ActionTimeline_setLastFrameCallFunc);
        tolua_function(L, "getTimelines", lua_cc_studio_ActionTimeline_getTimelines);
        tolua_function(L, "getAnimationInfo", lua_cc_studio_ActionTimeline_getAnimationInfo);
        tolua_function(L, "addFrameEndCallFunc", lua_cc_studio_ActionTimeline_addFrameEndCallFunc);
        tolua_function(L, "addAnimationInfo", lua_cc_studio_ActionTimeline_addAnimationInfo);
        tolua_function(L, "IsAnimationInfoExists", lua_cc_studio_ActionTimeline_IsAnimationInfoExists);
        tolua_function(L, "removeFrameEndCallFunc", lua_cc_studio_ActionTimeline_removeFrameEndCallFunc);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ActionTimelineNode");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ActionTimelineNode_constructor);
        tolua_function(L, "init", lua_cc_studio_ActionTimelineNode_init);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.BoneNode");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_BoneNode_constructor);
        tolua_function(L, "getChildBones", lua_cc_studio_BoneNode_getChildBones);
        tolua_function(L, "getBlendFunc", lua_cc_studio_BoneNode_getBlendFunc);
        tolua_function(L, "getAllSubBones", lua_cc_studio_BoneNode_getAllSubBones);
        tolua_function(L, "setBlendFunc", lua_cc_studio_BoneNode_setBlendFunc);
        tolua_function(L, "getVisibleSkinsRect", lua_cc_studio_BoneNode_getVisibleSkinsRect);
        tolua_function(L, "getAllSubSkins", lua_cc_studio_BoneNode_getAllSubSkins);
        tolua_function(L, "displaySkin", lua_cc_studio_BoneNode_displaySkin);
        tolua_function(L, "getSkins", lua_cc_studio_BoneNode_getSkins);
        tolua_function(L, "getVisibleSkins", lua_cc_studio_BoneNode_getVisibleSkins);
        tolua_function(L, "setDebugDrawColor", lua_cc_studio_BoneNode_setDebugDrawColor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.SkeletonNode");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_SkeletonNode_constructor);
        tolua_function(L, "getBoneNode", lua_cc_studio_SkeletonNode_getBoneNode);
        tolua_function(L, "changeSkins", lua_cc_studio_SkeletonNode_changeSkins);
        tolua_function(L, "addSkinGroup", lua_cc_studio_SkeletonNode_addSkinGroup);
        tolua_function(L, "getAllSubBonesMap", lua_cc_studio_SkeletonNode_getAllSubBonesMap);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "ccs.ComExtensionData");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_studio_ComExtensionData_constructor);
        tolua_function(L, "setCustomProperty", lua_cc_studio_ComExtensionData_setCustomProperty);
    }
    lua_pop(L, 1);
    return 0;
}
