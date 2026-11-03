#pragma once
// Retained UI contracts; class definitions belong only to cclua_ui_auto.
#include "ui/CocosGUI.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cc_ui_LayoutParameter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutParameter* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutParameter_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::LayoutParameter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.LayoutParameter");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutParameter:LayoutParameter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutParameter_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LinearLayoutParameter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LinearLayoutParameter* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LinearLayoutParameter_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::LinearLayoutParameter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.LinearLayoutParameter");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LinearLayoutParameter:LinearLayoutParameter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LinearLayoutParameter_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RelativeLayoutParameter_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RelativeLayoutParameter* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RelativeLayoutParameter_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RelativeLayoutParameter();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RelativeLayoutParameter");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeLayoutParameter:RelativeLayoutParameter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RelativeLayoutParameter_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Widget();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Widget");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:Widget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_setSizePercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_setSizePercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:setSizePercent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_setSizePercent'", nullptr);
            return 0;
        }
        cobj->setSizePercent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSizePercent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_setSizePercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getCustomSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getCustomSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getCustomSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCustomSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCustomSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getCustomSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getSizePercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getSizePercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getSizePercent'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSizePercent();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getSizePercent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getSizePercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_setPositionPercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_setPositionPercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:setPositionPercent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_setPositionPercent'", nullptr);
            return 0;
        }
        cobj->setPositionPercent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPositionPercent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_setPositionPercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getLayoutSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getLayoutSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getLayoutSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLayoutSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLayoutSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getLayoutSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getVirtualRendererSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getVirtualRendererSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getVirtualRendererSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVirtualRendererSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getVirtualRendererSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getVirtualRendererSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getLayoutParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getLayoutParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getLayoutParameter'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLayoutParameter();
        object_to_luaval<cocos2d::ui::LayoutParameter>(tolua_S, "ccui.LayoutParameter",(cocos2d::ui::LayoutParameter*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLayoutParameter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getLayoutParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getTouchBeganPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getTouchBeganPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getTouchBeganPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTouchBeganPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchBeganPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getTouchBeganPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_updateSizeAndPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_updateSizeAndPosition'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:updateSizeAndPosition");

            if (!ok) { break; }
            cobj->updateSizeAndPosition(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->updateSizeAndPosition();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Widget:updateSizeAndPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_updateSizeAndPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getTouchMovePosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getTouchMovePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getTouchMovePosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTouchMovePosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchMovePosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getTouchMovePosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getTouchEndPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getTouchEndPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getTouchEndPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTouchEndPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchEndPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getTouchEndPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_getPositionPercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_getPositionPercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_getPositionPercent'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPositionPercent();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getPositionPercent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_getPositionPercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Widget_isClippingParentContainsPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Widget_isClippingParentContainsPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:isClippingParentContainsPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Widget_isClippingParentContainsPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->isClippingParentContainsPoint(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isClippingParentContainsPoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Widget_isClippingParentContainsPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Layout();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Layout");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:Layout",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_setBackGroundColorVector(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_setBackGroundColorVector'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Layout:setBackGroundColorVector");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_setBackGroundColorVector'", nullptr);
            return 0;
        }
        cobj->setBackGroundColorVector(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundColorVector",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_setBackGroundColorVector'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_setBackGroundImageColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_setBackGroundImageColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.Layout:setBackGroundImageColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_setBackGroundImageColor'", nullptr);
            return 0;
        }
        cobj->setBackGroundImageColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundImageColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_setBackGroundImageColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundColorVector(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundColorVector'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundColorVector'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundColorVector();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundColorVector",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundColorVector'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getRenderFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getRenderFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getRenderFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getRenderFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getRenderFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_setBackGroundColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_setBackGroundColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.Layout:setBackGroundColor");

            if (!ok) { break; }
            cocos2d::Color3B arg1;
            ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.Layout:setBackGroundColor");

            if (!ok) { break; }
            cobj->setBackGroundColor(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.Layout:setBackGroundColor");

            if (!ok) { break; }
            cobj->setBackGroundColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Layout:setBackGroundColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_setBackGroundColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundImageCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundImageCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundImageCapInsets'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundImageCapInsets();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundImageCapInsets",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundImageCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundImageColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundImageColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundImageColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundImageColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundImageColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundImageColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundEndColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundEndColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundEndColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundEndColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_setBackGroundImageCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_setBackGroundImageCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Layout:setBackGroundImageCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_setBackGroundImageCapInsets'", nullptr);
            return 0;
        }
        cobj->setBackGroundImageCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:setBackGroundImageCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_setBackGroundImageCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundImageTextureSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundImageTextureSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundImageTextureSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundImageTextureSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundImageTextureSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundImageTextureSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Layout_getBackGroundStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Layout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Layout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Layout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Layout_getBackGroundStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Layout_getBackGroundStartColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackGroundStartColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Layout:getBackGroundStartColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Layout_getBackGroundStartColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Button();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Button");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:Button",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getNormalTextureSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getNormalTextureSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getNormalTextureSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNormalTextureSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getNormalTextureSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getNormalTextureSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getDisabledFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getDisabledFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getDisabledFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDisabledFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getDisabledFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getDisabledFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getCapInsetsDisabledRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getCapInsetsDisabledRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getCapInsetsDisabledRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsDisabledRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getCapInsetsDisabledRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getCapInsetsDisabledRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_setTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_setTitleColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.Button:setTitleColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_setTitleColor'", nullptr);
            return 0;
        }
        cobj->setTitleColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setTitleColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_setTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getNormalFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getNormalFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getNormalFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNormalFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getNormalFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getNormalFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_setCapInsetsDisabledRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_setCapInsetsDisabledRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Button:setCapInsetsDisabledRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_setCapInsetsDisabledRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsDisabledRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setCapInsetsDisabledRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_setCapInsetsDisabledRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Button:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Button:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string_view arg0;
        std::string_view arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Button:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Button:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Button:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Button:init");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.Button:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;
        cocos2d::ui::Widget::TextureResType arg3;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Button:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Button:init");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.Button:init");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccui.Button:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_setCapInsetsNormalRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_setCapInsetsNormalRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Button:setCapInsetsNormalRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_setCapInsetsNormalRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsNormalRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setCapInsetsNormalRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_setCapInsetsNormalRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getCapInsetsNormalRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getCapInsetsNormalRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getCapInsetsNormalRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsNormalRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getCapInsetsNormalRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getCapInsetsNormalRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getCapInsetsPressedRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getCapInsetsPressedRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getCapInsetsPressedRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsPressedRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getCapInsetsPressedRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getCapInsetsPressedRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_setCapInsetsPressedRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_setCapInsetsPressedRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Button:setCapInsetsPressedRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_setCapInsetsPressedRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsPressedRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:setCapInsetsPressedRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_setCapInsetsPressedRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getPressedFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getPressedFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getPressedFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPressedFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getPressedFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getPressedFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Button_getTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Button* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Button",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Button*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Button_getTitleColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Button_getTitleColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTitleColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Button:getTitleColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Button_getTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_getCrossDisabledFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_getCrossDisabledFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_getCrossDisabledFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCrossDisabledFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getCrossDisabledFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_getCrossDisabledFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_getBackDisabledFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_getBackDisabledFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_getBackDisabledFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackDisabledFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getBackDisabledFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_getBackDisabledFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_getCrossNormalFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_getCrossNormalFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_getCrossNormalFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCrossNormalFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getCrossNormalFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_getCrossNormalFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_getBackPressedFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_getBackPressedFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_getBackPressedFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackPressedFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getBackPressedFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_getBackPressedFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5)
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::string_view arg3;
        std::string_view arg4;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.AbstractCheckButton:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 6)
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::string_view arg3;
        std::string_view arg4;
        cocos2d::ui::Widget::TextureResType arg5;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.AbstractCheckButton:init");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccui.AbstractCheckButton:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:init",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_AbstractCheckButton_getBackNormalFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::AbstractCheckButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.AbstractCheckButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::AbstractCheckButton*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_AbstractCheckButton_getBackNormalFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_AbstractCheckButton_getBackNormalFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackNormalFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.AbstractCheckButton:getBackNormalFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_AbstractCheckButton_getBackNormalFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_CheckBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::CheckBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_CheckBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::CheckBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.CheckBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.CheckBox:CheckBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_CheckBox_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RadioButton_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RadioButton* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RadioButton_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RadioButton();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RadioButton");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButton:RadioButton",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RadioButton_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RadioButtonGroup_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RadioButtonGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RadioButtonGroup_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RadioButtonGroup();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RadioButtonGroup");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RadioButtonGroup:RadioButtonGroup",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RadioButtonGroup_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RadioButtonGroup_setSelectedButtonWithoutEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RadioButtonGroup* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RadioButtonGroup",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::RadioButtonGroup*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RadioButtonGroup_setSelectedButtonWithoutEvent'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::ui::RadioButton* arg0;
            ok &= luaval_to_object<cocos2d::ui::RadioButton>(tolua_S, 2, "ccui.RadioButton",&arg0, "ccui.RadioButtonGroup:setSelectedButtonWithoutEvent");

            if (!ok) { break; }
            cobj->setSelectedButtonWithoutEvent(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RadioButtonGroup:setSelectedButtonWithoutEvent");

            if (!ok) { break; }
            cobj->setSelectedButtonWithoutEvent(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.RadioButtonGroup:setSelectedButtonWithoutEvent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RadioButtonGroup_setSelectedButtonWithoutEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RadioButtonGroup_setSelectedButton(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RadioButtonGroup* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RadioButtonGroup",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::RadioButtonGroup*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RadioButtonGroup_setSelectedButton'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::ui::RadioButton* arg0;
            ok &= luaval_to_object<cocos2d::ui::RadioButton>(tolua_S, 2, "ccui.RadioButton",&arg0, "ccui.RadioButtonGroup:setSelectedButton");

            if (!ok) { break; }
            cobj->setSelectedButton(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RadioButtonGroup:setSelectedButton");

            if (!ok) { break; }
            cobj->setSelectedButton(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.RadioButtonGroup:setSelectedButton",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RadioButtonGroup_setSelectedButton'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::ImageView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.ImageView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:ImageView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccui.ImageView:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.ImageView:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::ui::Widget::TextureResType arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.ImageView:init");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.ImageView:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_setTextureRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_setTextureRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.ImageView:setTextureRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_setTextureRect'", nullptr);
            return 0;
        }
        cobj->setTextureRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:setTextureRect",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_setTextureRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.ImageView:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_getRenderFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_getRenderFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_getRenderFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:getRenderFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_getRenderFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ImageView_getCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ImageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ImageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ImageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ImageView_getCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ImageView_getCapInsets'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsets();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ImageView:getCapInsets",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ImageView_getCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Text();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Text");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:Text",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_enableShadow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_enableShadow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableShadow'", nullptr);
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

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableShadow");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.Text:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableShadow'", nullptr);
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

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableShadow");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.Text:enableShadow");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.Text:enableShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableShadow'", nullptr);
            return 0;
        }
        cobj->enableShadow(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:enableShadow",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_enableShadow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getTextColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getTextColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getTextColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getShadowOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getShadowOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getShadowOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getShadowOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getShadowOffset",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getShadowOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        std::string_view arg0;
        std::string_view arg1;
        double arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Text:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Text:init");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "ccui.Text:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:init",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_setTextAreaSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_setTextAreaSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Text:setTextAreaSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_setTextAreaSize'", nullptr);
            return 0;
        }
        cobj->setTextAreaSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setTextAreaSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_setTextAreaSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getAutoRenderSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getAutoRenderSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getAutoRenderSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAutoRenderSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getAutoRenderSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getAutoRenderSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_enableOutline(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_enableOutline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableOutline'", nullptr);
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

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableOutline");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.Text:enableOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableOutline'", nullptr);
            return 0;
        }
        cobj->enableOutline(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:enableOutline",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_enableOutline'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getEffectColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getEffectColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getEffectColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEffectColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getEffectColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getEffectColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getShadowColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getShadowColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getShadowColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getShadowColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getShadowColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getShadowColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_setTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_setTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:setTextColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_setTextColor'", nullptr);
            return 0;
        }
        cobj->setTextColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setTextColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_setTextColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_enableGlow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_enableGlow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.Text:enableGlow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_enableGlow'", nullptr);
            return 0;
        }
        cobj->enableGlow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:enableGlow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_enableGlow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccui.Text:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Text_getTextAreaSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Text* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Text",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Text*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Text_getTextAreaSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Text_getTextAreaSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextAreaSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Text:getTextAreaSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Text_getTextAreaSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextAtlas_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextAtlas_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::TextAtlas();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.TextAtlas");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:TextAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextAtlas_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextAtlas_getRenderFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextAtlas_getRenderFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextAtlas_getRenderFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:getRenderFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextAtlas_getRenderFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextAtlas_adaptRenderers(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextAtlas_adaptRenderers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextAtlas_adaptRenderers'", nullptr);
            return 0;
        }
        cobj->adaptRenderers();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextAtlas:adaptRenderers",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextAtlas_adaptRenderers'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LoadingBar_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LoadingBar* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LoadingBar_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::LoadingBar();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.LoadingBar");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:LoadingBar",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LoadingBar_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LoadingBar_getRenderFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LoadingBar* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LoadingBar",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LoadingBar*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LoadingBar_getRenderFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LoadingBar_getRenderFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:getRenderFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LoadingBar_getRenderFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LoadingBar_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LoadingBar* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LoadingBar",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LoadingBar*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LoadingBar_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.LoadingBar:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LoadingBar_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LoadingBar_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LoadingBar_getCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LoadingBar* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LoadingBar",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LoadingBar*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LoadingBar_getCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LoadingBar_getCapInsets'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsets();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LoadingBar:getCapInsets",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LoadingBar_getCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LoadingBar_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.LoadingBar",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0);
            object_to_luaval<cocos2d::ui::LoadingBar>(tolua_S, "ccui.LoadingBar",(cocos2d::ui::LoadingBar*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.LoadingBar:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::LoadingBar>(tolua_S, "ccui.LoadingBar",(cocos2d::ui::LoadingBar*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 0)
        {
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create();
            object_to_luaval<cocos2d::ui::LoadingBar>(tolua_S, "ccui.LoadingBar",(cocos2d::ui::LoadingBar*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::LoadingBar>(tolua_S, "ccui.LoadingBar",(cocos2d::ui::LoadingBar*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 3)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.LoadingBar:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "ccui.LoadingBar:create");
            if (!ok) { break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::LoadingBar>(tolua_S, "ccui.LoadingBar",(cocos2d::ui::LoadingBar*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.LoadingBar:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LoadingBar_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_ScrollView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::ScrollView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.ScrollView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:ScrollView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getScrolledPercentBothDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getScrolledPercentBothDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getScrolledPercentBothDirection'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScrolledPercentBothDirection();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrolledPercentBothDirection",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getScrolledPercentBothDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setScrollBarColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setScrollBarColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.ScrollView:setScrollBarColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setScrollBarColor'", nullptr);
            return 0;
        }
        cobj->setScrollBarColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setScrollBarColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setInnerContainerPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setInnerContainerPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:setInnerContainerPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setInnerContainerPosition'", nullptr);
            return 0;
        }
        cobj->setInnerContainerPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setInnerContainerPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setInnerContainerPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_scrollToPercentBothDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_scrollToPercentBothDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        double arg1;
        bool arg2;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:scrollToPercentBothDirection");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccui.ScrollView:scrollToPercentBothDirection");

        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.ScrollView:scrollToPercentBothDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_scrollToPercentBothDirection'", nullptr);
            return 0;
        }
        cobj->scrollToPercentBothDirection(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:scrollToPercentBothDirection",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_scrollToPercentBothDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setInnerContainerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setInnerContainerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:setInnerContainerSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setInnerContainerSize'", nullptr);
            return 0;
        }
        cobj->setInnerContainerSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setInnerContainerSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setInnerContainerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getInnerContainerPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getInnerContainerPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getInnerContainerPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getInnerContainerPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getInnerContainerPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getInnerContainerPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:setScrollBarPositionFromCornerForHorizontal");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal'", nullptr);
            return 0;
        }
        cobj->setScrollBarPositionFromCornerForHorizontal(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarPositionFromCornerForHorizontal",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getScrollBarColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getScrollBarColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getScrollBarColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScrollBarColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getScrollBarColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScrollBarPositionFromCornerForHorizontal();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarPositionFromCornerForHorizontal",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_jumpToPercentBothDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_jumpToPercentBothDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:jumpToPercentBothDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_jumpToPercentBothDirection'", nullptr);
            return 0;
        }
        cobj->jumpToPercentBothDirection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:jumpToPercentBothDirection",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_jumpToPercentBothDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setScrollBarPositionFromCorner(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCorner'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:setScrollBarPositionFromCorner");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCorner'", nullptr);
            return 0;
        }
        cobj->setScrollBarPositionFromCorner(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarPositionFromCorner",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCorner'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForVertical(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForVertical'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ScrollView:setScrollBarPositionFromCornerForVertical");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForVertical'", nullptr);
            return 0;
        }
        cobj->setScrollBarPositionFromCornerForVertical(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:setScrollBarPositionFromCornerForVertical",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForVertical'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForVertical(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForVertical'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForVertical'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScrollBarPositionFromCornerForVertical();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getScrollBarPositionFromCornerForVertical",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForVertical'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ScrollView_getInnerContainerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ScrollView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ScrollView_getInnerContainerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ScrollView_getInnerContainerSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getInnerContainerSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ScrollView:getInnerContainerSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ScrollView_getInnerContainerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::ListView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.ListView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:ListView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_scrollToItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_scrollToItem'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cobj->scrollToItem(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "ccui.ListView:scrollToItem");

            if (!ok) { break; }
            cobj->scrollToItem(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.ListView:scrollToItem",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_scrollToItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_jumpToItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_jumpToItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        ssize_t arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:jumpToItem");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.ListView:jumpToItem");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "ccui.ListView:jumpToItem");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_jumpToItem'", nullptr);
            return 0;
        }
        cobj->jumpToItem(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:jumpToItem",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_jumpToItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_insertDefaultItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_insertDefaultItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:insertDefaultItem");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_insertDefaultItem'", nullptr);
            return 0;
        }
        cobj->insertDefaultItem(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:insertDefaultItem",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_insertDefaultItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_doLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_doLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_doLayout'", nullptr);
            return 0;
        }
        cobj->doLayout();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:doLayout",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_doLayout'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_getItems(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_getItems'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_getItems'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getItems();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getItems",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_getItems'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_getItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_getItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:getItem");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_getItem'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getItem(arg0);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getItem",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_getItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_removeItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_removeItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.ListView:removeItem");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_removeItem'", nullptr);
            return 0;
        }
        cobj->removeItem(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:removeItem",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_removeItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_getClosestItemToPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_getClosestItemToPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ListView:getClosestItemToPosition");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.ListView:getClosestItemToPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_getClosestItemToPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getClosestItemToPosition(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getClosestItemToPosition",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_getClosestItemToPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_getClosestItemToPositionInCurrentView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_getClosestItemToPositionInCurrentView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.ListView:getClosestItemToPositionInCurrentView");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.ListView:getClosestItemToPositionInCurrentView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_getClosestItemToPositionInCurrentView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getClosestItemToPositionInCurrentView(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:getClosestItemToPositionInCurrentView",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_getClosestItemToPositionInCurrentView'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_ListView_insertCustomItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::ListView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::ListView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_ListView_insertCustomItem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::ui::Widget* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 2, "ccui.Widget",&arg0, "ccui.ListView:insertCustomItem");

        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "ccui.ListView:insertCustomItem");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_ListView_insertCustomItem'", nullptr);
            return 0;
        }
        cobj->insertCustomItem(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.ListView:insertCustomItem",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_ListView_insertCustomItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Slider();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Slider");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:Slider",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getBallNormalFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getBallNormalFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getBallNormalFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBallNormalFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getBallNormalFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getBallNormalFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getBallPressedFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getBallPressedFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getBallPressedFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBallPressedFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getBallPressedFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getBallPressedFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_setCapInsetProgressBarRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_setCapInsetProgressBarRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Slider:setCapInsetProgressBarRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_setCapInsetProgressBarRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetProgressBarRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setCapInsetProgressBarRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_setCapInsetProgressBarRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getProgressBarFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getProgressBarFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getProgressBarFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProgressBarFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getProgressBarFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getProgressBarFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getCapInsetsBarRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getCapInsetsBarRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getCapInsetsBarRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsBarRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getCapInsetsBarRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getCapInsetsBarRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getCapInsetsProgressBarRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getCapInsetsProgressBarRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getCapInsetsProgressBarRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsProgressBarRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getCapInsetsProgressBarRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getCapInsetsProgressBarRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getBackFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getBackFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getBackFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBackFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getBackFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getBackFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_getBallDisabledFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_getBallDisabledFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_getBallDisabledFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBallDisabledFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:getBallDisabledFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_getBallDisabledFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_setCapInsetsBarRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_setCapInsetsBarRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Slider:setCapInsetsBarRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_setCapInsetsBarRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsBarRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setCapInsetsBarRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_setCapInsetsBarRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Slider_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Slider* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Slider*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Slider_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Slider:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Slider_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Slider:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Slider_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::TextField();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.TextField");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:TextField",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_getTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_getTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_getTextColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getTextColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_getTextColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setTextAreaSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setTextAreaSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.TextField:setTextAreaSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_setTextAreaSize'", nullptr);
            return 0;
        }
        cobj->setTextAreaSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextAreaSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setTextAreaSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_getAutoRenderSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_getAutoRenderSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_getAutoRenderSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAutoRenderSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getAutoRenderSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_getAutoRenderSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_getPlaceHolderColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_getPlaceHolderColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_getPlaceHolderColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPlaceHolderColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPlaceHolderColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_getPlaceHolderColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setCursorFromPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setCursorFromPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        const cocos2d::Camera* arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.TextField:setCursorFromPoint");

        ok &= luaval_to_object<const cocos2d::Camera>(tolua_S, 3, "cc.Camera",&arg1, "ccui.TextField:setCursorFromPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_setCursorFromPoint'", nullptr);
            return 0;
        }
        cobj->setCursorFromPoint(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setCursorFromPoint",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setCursorFromPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setPlaceHolderColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setPlaceHolderColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.TextField:setPlaceHolderColor");

            if (!ok) { break; }
            cobj->setPlaceHolderColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.TextField:setPlaceHolderColor");

            if (!ok) { break; }
            cobj->setPlaceHolderColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.TextField:setPlaceHolderColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setPlaceHolderColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.TextField:setTextColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_setTextColor'", nullptr);
            return 0;
        }
        cobj->setTextColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setTextColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setCursorChar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setCursorChar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccui.TextField:setCursorChar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_setCursorChar'", nullptr);
            return 0;
        }
        cobj->setCursorChar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setCursorChar",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setCursorChar'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_setTouchSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_setTouchSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.TextField:setTouchSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_setTouchSize'", nullptr);
            return 0;
        }
        cobj->setTouchSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTouchSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_setTouchSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextField_getTouchSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextField_getTouchSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextField_getTouchSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTouchSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getTouchSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextField_getTouchSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextBMFont_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextBMFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextBMFont_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::TextBMFont();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.TextBMFont");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:TextBMFont",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextBMFont_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TextBMFont_getRenderFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextBMFont* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextBMFont",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextBMFont*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TextBMFont_getRenderFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TextBMFont_getRenderFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderFile();
        resourceData_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextBMFont:getRenderFile",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TextBMFont_getRenderFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::PageView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.PageView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:PageView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_setIndicatorSelectedIndexColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_setIndicatorSelectedIndexColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.PageView:setIndicatorSelectedIndexColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_setIndicatorSelectedIndexColor'", nullptr);
            return 0;
        }
        cobj->setIndicatorSelectedIndexColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorSelectedIndexColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_setIndicatorSelectedIndexColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_getIndicatorPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_getIndicatorPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_getIndicatorPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getIndicatorPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_getIndicatorPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_setCurrentPageIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_setCurrentPageIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:setCurrentPageIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_setCurrentPageIndex'", nullptr);
            return 0;
        }
        cobj->setCurrentPageIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setCurrentPageIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_setCurrentPageIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_getIndicatorIndexNodesColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_getIndicatorIndexNodesColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_getIndicatorIndexNodesColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getIndicatorIndexNodesColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorIndexNodesColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_getIndicatorIndexNodesColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_getIndicatorSelectedIndexColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_getIndicatorSelectedIndexColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_getIndicatorSelectedIndexColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getIndicatorSelectedIndexColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorSelectedIndexColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_getIndicatorSelectedIndexColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_setIndicatorPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_setIndicatorPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.PageView:setIndicatorPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_setIndicatorPosition'", nullptr);
            return 0;
        }
        cobj->setIndicatorPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_setIndicatorPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_scrollToPage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_scrollToPage'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:scrollToPage");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ccui.PageView:scrollToPage");

            if (!ok) { break; }
            cobj->scrollToPage(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:scrollToPage");

            if (!ok) { break; }
            cobj->scrollToPage(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.PageView:scrollToPage",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_scrollToPage'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_setIndicatorPositionAsAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_setIndicatorPositionAsAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.PageView:setIndicatorPositionAsAnchorPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_setIndicatorPositionAsAnchorPoint'", nullptr);
            return 0;
        }
        cobj->setIndicatorPositionAsAnchorPoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorPositionAsAnchorPoint",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_setIndicatorPositionAsAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_scrollToItem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_scrollToItem'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:scrollToItem");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "ccui.PageView:scrollToItem");

            if (!ok) { break; }
            cobj->scrollToItem(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            ssize_t arg0;
            ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:scrollToItem");

            if (!ok) { break; }
            cobj->scrollToItem(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.PageView:scrollToItem",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_scrollToItem'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_setIndicatorIndexNodesColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_setIndicatorIndexNodesColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.PageView:setIndicatorIndexNodesColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_setIndicatorIndexNodesColor'", nullptr);
            return 0;
        }
        cobj->setIndicatorIndexNodesColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:setIndicatorIndexNodesColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_setIndicatorIndexNodesColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_getIndicatorPositionAsAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_getIndicatorPositionAsAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_getIndicatorPositionAsAnchorPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getIndicatorPositionAsAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:getIndicatorPositionAsAnchorPoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_getIndicatorPositionAsAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_PageView_removePageAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::PageView* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::PageView*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_PageView_removePageAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "ccui.PageView:removePageAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_PageView_removePageAtIndex'", nullptr);
            return 0;
        }
        cobj->removePageAtIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.PageView:removePageAtIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_PageView_removePageAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Helper_convertBoundingBoxToScreen(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Helper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Node* arg0;
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "ccui.Helper:convertBoundingBoxToScreen");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Helper_convertBoundingBoxToScreen'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::Helper::convertBoundingBoxToScreen(arg0);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:convertBoundingBoxToScreen",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Helper_convertBoundingBoxToScreen'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_Helper_restrictCapInsetRect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Helper",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Rect arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Helper:restrictCapInsetRect");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccui.Helper:restrictCapInsetRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Helper_restrictCapInsetRect'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::Helper::restrictCapInsetRect(arg0, arg1);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Helper:restrictCapInsetRect",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Helper_restrictCapInsetRect'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RichElement_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElement* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElement_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElement();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElement");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:RichElement",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElement_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElement_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElement* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElement*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichElement_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElement:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElement:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElement:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElement_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:init",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElement_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElement_setColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElement* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElement*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichElement_setColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.RichElement:setColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElement_setColor'", nullptr);
            return 0;
        }
        cobj->setColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:setColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElement_setColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementText_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementText();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementText");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementText:RichElementText",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementText_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementText_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichElementText_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 8)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 9)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 10)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 11)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 12)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:init");

        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 13)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;
        int arg12;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:init");

        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 14,(int *)&arg12, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 14)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;
        int arg12;
        cocos2d::Color3B arg13;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:init");

        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:init");

        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:init");

        ok &= luaval_to_int32(tolua_S, 14,(int *)&arg12, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 15, &arg13, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementText:init",argc, 8);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementText_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementText_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementText",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 7)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 8)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 9)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 10)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 11)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 12)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:create");
        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 13)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;
        int arg12;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:create");
        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 14,(int *)&arg12, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    if (argc == 14)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        double arg5;
        unsigned int arg6;
        std::string_view arg7;
        cocos2d::Color3B arg8;
        int arg9;
        cocos2d::Color3B arg10;
        cocos2d::Vec2 arg11;
        int arg12;
        cocos2d::Color3B arg13;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "ccui.RichElementText:create");
        ok &= luaval_to_std_string_view(tolua_S, 9,&arg7, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 10, &arg8, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 11,(int *)&arg9, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 12, &arg10, "ccui.RichElementText:create");
        ok &= luaval_to_vec2(tolua_S, 13, &arg11, "ccui.RichElementText:create");
        ok &= luaval_to_int32(tolua_S, 14,(int *)&arg12, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 15, &arg13, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementText_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementText:create",argc, 6);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementText_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RichElementImage_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementImage* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementImage();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementImage");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:RichElementImage",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementImage_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementImage_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementImage* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementImage",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementImage*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichElementImage_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementImage:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 6)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        cocos2d::ui::Widget::TextureResType arg5;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementImage:init");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccui.RichElementImage:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:init",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementImage_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementImage_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementImage",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementImage::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ui::RichElementImage>(tolua_S, "ccui.RichElementImage",(cocos2d::ui::RichElementImage*)ret);
        return 1;
    }
    if (argc == 5)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementImage:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementImage::create(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<cocos2d::ui::RichElementImage>(tolua_S, "ccui.RichElementImage",(cocos2d::ui::RichElementImage*)ret);
        return 1;
    }
    if (argc == 6)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string_view arg3;
        std::string_view arg4;
        cocos2d::ui::Widget::TextureResType arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "ccui.RichElementImage:create");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccui.RichElementImage:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementImage_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementImage::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::ui::RichElementImage>(tolua_S, "ccui.RichElementImage",(cocos2d::ui::RichElementImage*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementImage:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementImage_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RichElementCustomNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementCustomNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementCustomNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementCustomNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementCustomNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementCustomNode:RichElementCustomNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementCustomNode_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementCustomNode_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementCustomNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementCustomNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementCustomNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichElementCustomNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 5, "cc.Node",&arg3, "ccui.RichElementCustomNode:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementCustomNode_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementCustomNode:init",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementCustomNode_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementCustomNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementCustomNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 5, "cc.Node",&arg3, "ccui.RichElementCustomNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementCustomNode_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementCustomNode::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ui::RichElementCustomNode>(tolua_S, "ccui.RichElementCustomNode",(cocos2d::ui::RichElementCustomNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementCustomNode:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementCustomNode_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RichElementNewLine_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementNewLine* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementNewLine_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementNewLine();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementNewLine");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementNewLine:RichElementNewLine",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementNewLine_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichElementNewLine_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementNewLine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementNewLine:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementNewLine:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementNewLine:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichElementNewLine_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichElementNewLine::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::ui::RichElementNewLine>(tolua_S, "ccui.RichElementNewLine",(cocos2d::ui::RichElementNewLine*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementNewLine:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichElementNewLine_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RichText_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichText();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichText");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:RichText",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_setAnchorTextOutline(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_setAnchorTextOutline'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextOutline'", nullptr);
            return 0;
        }
        cobj->setAnchorTextOutline(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        bool arg0;
        cocos2d::Color3B arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextOutline");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextOutline'", nullptr);
            return 0;
        }
        cobj->setAnchorTextOutline(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        bool arg0;
        cocos2d::Color3B arg1;
        int arg2;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextOutline");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextOutline");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.RichText:setAnchorTextOutline");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextOutline'", nullptr);
            return 0;
        }
        cobj->setAnchorTextOutline(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextOutline",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_setAnchorTextOutline'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_setAnchorTextShadow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_setAnchorTextShadow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextShadow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextShadow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        bool arg0;
        cocos2d::Color3B arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextShadow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextShadow(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        bool arg0;
        cocos2d::Color3B arg1;
        cocos2d::Vec2 arg2;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "ccui.RichText:setAnchorTextShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextShadow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextShadow(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 4)
    {
        bool arg0;
        cocos2d::Color3B arg1;
        cocos2d::Vec2 arg2;
        int arg3;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "ccui.RichText:setAnchorTextShadow");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccui.RichText:setAnchorTextShadow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextShadow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextShadow(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextShadow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_setAnchorTextShadow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_setAnchorTextGlow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_setAnchorTextGlow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextGlow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextGlow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextGlow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        bool arg0;
        cocos2d::Color3B arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.RichText:setAnchorTextGlow");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichText:setAnchorTextGlow");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setAnchorTextGlow'", nullptr);
            return 0;
        }
        cobj->setAnchorTextGlow(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setAnchorTextGlow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_setAnchorTextGlow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getAnchorTextOutlineColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getAnchorTextOutlineColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getAnchorTextOutlineColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorTextOutlineColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextOutlineColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getAnchorTextOutlineColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_stringWithColor4B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_stringWithColor4B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.RichText:stringWithColor4B");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_stringWithColor4B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->stringWithColor4B(arg0);
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:stringWithColor4B",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_stringWithColor4B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_initWithXML(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_initWithXML'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::ValueMap arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.RichText:initWithXML");

        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "ccui.RichText:initWithXML");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_initWithXML'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithXML(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::ValueMap arg1;
        std::function<void (std::string_view)> arg2;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.RichText:initWithXML");

        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "ccui.RichText:initWithXML");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_initWithXML'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithXML(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:initWithXML",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_initWithXML'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getAnchorFontColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getAnchorFontColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getAnchorFontColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorFontColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorFontColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getAnchorFontColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getAnchorTextGlowColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getAnchorTextGlowColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getAnchorTextGlowColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorTextGlowColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextGlowColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getAnchorTextGlowColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getDefaults(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getDefaults'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getDefaults'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDefaults();
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getDefaults",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getDefaults'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_setDefaults(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_setDefaults'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "ccui.RichText:setDefaults");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_setDefaults'", nullptr);
            return 0;
        }
        cobj->setDefaults(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setDefaults",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_setDefaults'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_removeElement(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_removeElement'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::ui::RichElement* arg0;
            ok &= luaval_to_object<cocos2d::ui::RichElement>(tolua_S, 2, "ccui.RichElement",&arg0, "ccui.RichText:removeElement");

            if (!ok) { break; }
            cobj->removeElement(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichText:removeElement");

            if (!ok) { break; }
            cobj->removeElement(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.RichText:removeElement",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_removeElement'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getAnchorTextShadowOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getAnchorTextShadowOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getAnchorTextShadowOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorTextShadowOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextShadowOffset",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getAnchorTextShadowOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getAnchorTextShadowColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getAnchorTextShadowColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getAnchorTextShadowColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorTextShadowColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getAnchorTextShadowColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getAnchorTextShadowColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_stringWithColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_stringWithColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.RichText:stringWithColor3B");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_stringWithColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->stringWithColor3B(arg0);
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:stringWithColor3B",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_stringWithColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_getFontColor3B(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_getFontColor3B'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_getFontColor3B'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFontColor3B();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:getFontColor3B",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_getFontColor3B'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_color3BWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RichText_color3BWithString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.RichText:color3BWithString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_color3BWithString'", nullptr);
            return 0;
        }
        auto&& ret = cobj->color3BWithString(arg0);
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:color3BWithString",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_color3BWithString'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RichText_createWithXML(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::ValueMap arg1;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.RichText:createWithXML");
        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "ccui.RichText:createWithXML");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_createWithXML'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichText::createWithXML(arg0, arg1);
        object_to_luaval<cocos2d::ui::RichText>(tolua_S, "ccui.RichText",(cocos2d::ui::RichText*)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string_view arg0;
        cocos2d::ValueMap arg1;
        std::function<void (std::string_view)> arg2;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.RichText:createWithXML");
        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "ccui.RichText:createWithXML");
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RichText_createWithXML'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ui::RichText::createWithXML(arg0, arg1, arg2);
        object_to_luaval<cocos2d::ui::RichText>(tolua_S, "ccui.RichText",(cocos2d::ui::RichText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichText:createWithXML",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RichText_createWithXML'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_HBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::HBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_HBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::HBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.HBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.HBox:HBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_HBox_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_HBox_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::HBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.HBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::HBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_HBox_initWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.HBox:initWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_HBox_initWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.HBox:initWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_HBox_initWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_HBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.HBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.HBox:create");
            if (!ok) { break; }
            cocos2d::ui::HBox* ret = cocos2d::ui::HBox::create(arg0);
            object_to_luaval<cocos2d::ui::HBox>(tolua_S, "ccui.HBox",(cocos2d::ui::HBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 0)
        {
            cocos2d::ui::HBox* ret = cocos2d::ui::HBox::create();
            object_to_luaval<cocos2d::ui::HBox>(tolua_S, "ccui.HBox",(cocos2d::ui::HBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.HBox:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_HBox_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_VBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::VBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_VBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::VBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.VBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.VBox:VBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_VBox_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_VBox_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::VBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.VBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::VBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_VBox_initWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.VBox:initWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_VBox_initWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.VBox:initWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_VBox_initWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_VBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.VBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.VBox:create");
            if (!ok) { break; }
            cocos2d::ui::VBox* ret = cocos2d::ui::VBox::create(arg0);
            object_to_luaval<cocos2d::ui::VBox>(tolua_S, "ccui.VBox",(cocos2d::ui::VBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 0)
        {
            cocos2d::ui::VBox* ret = cocos2d::ui::VBox::create();
            object_to_luaval<cocos2d::ui::VBox>(tolua_S, "ccui.VBox",(cocos2d::ui::VBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.VBox:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_VBox_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_RelativeBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RelativeBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RelativeBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RelativeBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RelativeBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeBox:RelativeBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RelativeBox_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RelativeBox_initWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RelativeBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RelativeBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RelativeBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_RelativeBox_initWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.RelativeBox:initWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_RelativeBox_initWithSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RelativeBox:initWithSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RelativeBox_initWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_RelativeBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RelativeBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 1)
        {
            cocos2d::Vec2 arg0;
            ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.RelativeBox:create");
            if (!ok) { break; }
            cocos2d::ui::RelativeBox* ret = cocos2d::ui::RelativeBox::create(arg0);
            object_to_luaval<cocos2d::ui::RelativeBox>(tolua_S, "ccui.RelativeBox",(cocos2d::ui::RelativeBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 0)
        {
            cocos2d::ui::RelativeBox* ret = cocos2d::ui::RelativeBox::create();
            object_to_luaval<cocos2d::ui::RelativeBox>(tolua_S, "ccui.RelativeBox",(cocos2d::ui::RelativeBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.RelativeBox:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_RelativeBox_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_Scale9Sprite_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Scale9Sprite();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Scale9Sprite");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:Scale9Sprite",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_updateWithSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_updateWithSprite'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg5;
            ok &= luaval_to_rect(tolua_S, 7, &arg5, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:updateWithSprite",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_updateWithSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_resizableSpriteWithCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_resizableSpriteWithCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:resizableSpriteWithCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_resizableSpriteWithCapInsets'", nullptr);
            return 0;
        }
        auto&& ret = cobj->resizableSpriteWithCapInsets(arg0);
        object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:resizableSpriteWithCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_resizableSpriteWithCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_getCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_getCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_getCapInsets'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsets();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getCapInsets",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_getCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_initWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrameName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        std::string_view arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithSpriteFrameName");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithSpriteFrameName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrameName'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrameName(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:initWithSpriteFrameName",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrameName'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_init'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg5;
            ok &= luaval_to_rect(tolua_S, 7, &arg5, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:init",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_setPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_setPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Scale9Sprite:setPreferredSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_setPreferredSize'", nullptr);
            return 0;
        }
        cobj->setPreferredSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setPreferredSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_setPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_setSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_setSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::SpriteFrame* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "ccui.Scale9Sprite:setSpriteFrame");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:setSpriteFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_setSpriteFrame'", nullptr);
            return 0;
        }
        cobj->setSpriteFrame(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setSpriteFrame",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_setSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_getOriginalSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_getOriginalSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_getOriginalSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOriginalSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getOriginalSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_getOriginalSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_initWithFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:initWithFile",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_initWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_initWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::SpriteFrame* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "ccui.Scale9Sprite:initWithSpriteFrame");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithSpriteFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrame'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrame(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:initWithSpriteFrame",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_initWithSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_getPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_getPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_getPreferredSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPreferredSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getPreferredSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_getPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_Scale9Sprite_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_Scale9Sprite_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_Scale9Sprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 3)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 0)
        {
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create();
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_Scale9Sprite_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:createWithSpriteFrameName",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_Scale9Sprite_createWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 2)
        {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "ccui.Scale9Sprite:createWithSpriteFrame");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:createWithSpriteFrame");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 1)
        {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "ccui.Scale9Sprite:createWithSpriteFrame");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:createWithSpriteFrame",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_Scale9Sprite_createWithSpriteFrame'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_EditBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::EditBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.EditBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:EditBox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_keyboardDidShow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_keyboardDidShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_keyboardDidShow'", nullptr);
            return 0;
        }
        cobj->keyboardDidShow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardDidShow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_keyboardDidShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_initWithSizeAndBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_initWithSizeAndBackgroundSprite'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg2;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 4, "ccui.Scale9Sprite",&arg2, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg3;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 5, "ccui.Scale9Sprite",&arg3, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:initWithSizeAndBackgroundSprite",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_initWithSizeAndBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_keyboardDidHide(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_keyboardDidHide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_keyboardDidHide'", nullptr);
            return 0;
        }
        cobj->keyboardDidHide(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardDidHide",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_keyboardDidHide'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_getCapInsetsDisabledRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_getCapInsetsDisabledRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_getCapInsetsDisabledRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsDisabledRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getCapInsetsDisabledRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_getCapInsetsDisabledRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setCapInsetsDisabledRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setCapInsetsDisabledRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.EditBox:setCapInsetsDisabledRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_setCapInsetsDisabledRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsDisabledRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setCapInsetsDisabledRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setCapInsetsDisabledRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_keyboardWillShow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_keyboardWillShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_keyboardWillShow'", nullptr);
            return 0;
        }
        cobj->keyboardWillShow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardWillShow",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_keyboardWillShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setPlaceholderFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setPlaceholderFontColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.EditBox:setPlaceholderFontColor");

            if (!ok) { break; }
            cobj->setPlaceholderFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.EditBox:setPlaceholderFontColor");

            if (!ok) { break; }
            cobj->setPlaceholderFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:setPlaceholderFontColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setPlaceholderFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setFontColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.EditBox:setFontColor");

            if (!ok) { break; }
            cobj->setFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.EditBox:setFontColor");

            if (!ok) { break; }
            cobj->setFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:setFontColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_keyboardWillHide(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_keyboardWillHide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_keyboardWillHide'", nullptr);
            return 0;
        }
        cobj->keyboardWillHide(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardWillHide",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_keyboardWillHide'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setCapInsetsNormalRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setCapInsetsNormalRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.EditBox:setCapInsetsNormalRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_setCapInsetsNormalRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsNormalRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setCapInsetsNormalRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setCapInsetsNormalRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_getFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_getFontColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_getFontColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFontColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getFontColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_getFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_initWithSizeAndTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Size arg0;
        std::string_view arg1;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSizeAndTexture(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Size arg0;
        std::string_view arg1;
        std::string_view arg2;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:initWithSizeAndTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSizeAndTexture(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Size arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::string_view arg3;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.EditBox:initWithSizeAndTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSizeAndTexture(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5)
    {
        cocos2d::Size arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::string_view arg3;
        cocos2d::ui::Widget::TextureResType arg4;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.EditBox:initWithSizeAndTexture");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "ccui.EditBox:initWithSizeAndTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSizeAndTexture(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:initWithSizeAndTexture",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_initWithSizeAndTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_getCapInsetsNormalRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_getCapInsetsNormalRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_getCapInsetsNormalRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsNormalRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getCapInsetsNormalRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_getCapInsetsNormalRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_getCapInsetsPressedRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_getCapInsetsPressedRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_getCapInsetsPressedRenderer'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCapInsetsPressedRenderer();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getCapInsetsPressedRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_getCapInsetsPressedRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setCapInsetsPressedRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setCapInsetsPressedRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.EditBox:setCapInsetsPressedRenderer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_setCapInsetsPressedRenderer'", nullptr);
            return 0;
        }
        cobj->setCapInsetsPressedRenderer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setCapInsetsPressedRenderer",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setCapInsetsPressedRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_getPlaceholderFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_getPlaceholderFontColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_getPlaceholderFontColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPlaceholderFontColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getPlaceholderFontColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_getPlaceholderFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_EditBox_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.EditBox:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_EditBox_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setCapInsets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_EditBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do
    {
        if (argc == 3)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 3)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg2;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 4, "ccui.Scale9Sprite",&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 4)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg2;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 4, "ccui.Scale9Sprite",&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg3;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 5, "ccui.Scale9Sprite",&arg3, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 3)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 4)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg3;
            ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 5)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string_view arg3;
            ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.EditBox:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_EditBox_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cc_ui_LayoutComponent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::LayoutComponent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.LayoutComponent");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:LayoutComponent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_constructor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_getAnchorPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_getAnchorPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_getAnchorPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPosition();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getAnchorPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_getAnchorPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_getSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_getSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_getSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_getSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_setAnchorPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_setAnchorPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccui.LayoutComponent:setAnchorPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_setAnchorPosition'", nullptr);
            return 0;
        }
        cobj->setAnchorPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setAnchorPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_setAnchorPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_getPercentContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_getPercentContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_getPercentContentSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPercentContentSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPercentContentSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_getPercentContentSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "ccui.LayoutComponent:setPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_setPosition'", nullptr);
            return 0;
        }
        cobj->setPosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_setPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_getPosition'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPosition();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:getPosition",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_getPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_setPercentContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_setPercentContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.LayoutComponent:setPercentContentSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_setPercentContentSize'", nullptr);
            return 0;
        }
        cobj->setPercentContentSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setPercentContentSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_setPercentContentSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_LayoutComponent_setSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::LayoutComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.LayoutComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::LayoutComponent*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_LayoutComponent_setSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.LayoutComponent:setSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_LayoutComponent_setSize'", nullptr);
            return 0;
        }
        cobj->setSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.LayoutComponent:setSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_LayoutComponent_setSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TabHeader_getTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TabHeader* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TabHeader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TabHeader*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TabHeader_getTitleColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TabHeader_getTitleColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTitleColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:getTitleColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TabHeader_getTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TabHeader_setTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TabHeader* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TabHeader",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TabHeader*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TabHeader_setTitleColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.TabHeader:setTitleColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TabHeader_setTitleColor'", nullptr);
            return 0;
        }
        cobj->setTitleColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabHeader:setTitleColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TabHeader_setTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TabControl_setSelectTab(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TabControl* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TabControl",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::TabControl*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TabControl_setSelectTab'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::ui::TabHeader* arg0;
            ok &= luaval_to_object<cocos2d::ui::TabHeader>(tolua_S, 2, "ccui.TabHeader",&arg0, "ccui.TabControl:setSelectTab");

            if (!ok) { break; }
            cobj->setSelectTab(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.TabControl:setSelectTab");

            if (!ok) { break; }
            cobj->setSelectTab(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.TabControl:setSelectTab",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TabControl_setSelectTab'.",&tolua_err);
#endif

    return 0;
}
int lua_cc_ui_TabControl_setTabChangedEventListener(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TabControl* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TabControl",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TabControl*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_ui_TabControl_setTabChangedEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::function<void (int, cocos2d::ui::TabControl::EventType)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_ui_TabControl_setTabChangedEventListener'", nullptr);
            return 0;
        }
        cobj->setTabChangedEventListener(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TabControl:setTabChangedEventListener",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_ui_TabControl_setTabChangedEventListener'.",&tolua_err);
#endif

    return 0;
}
inline void register_all_cc_ui_retained(lua_State* L)
{
    luaL_getmetatable(L, "ccui.LayoutParameter");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_LayoutParameter_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.LinearLayoutParameter");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_LinearLayoutParameter_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RelativeLayoutParameter");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RelativeLayoutParameter_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Widget");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Widget_constructor);
        tolua_function(L, "setSizePercent", lua_cc_ui_Widget_setSizePercent);
        tolua_function(L, "getCustomSize", lua_cc_ui_Widget_getCustomSize);
        tolua_function(L, "getSizePercent", lua_cc_ui_Widget_getSizePercent);
        tolua_function(L, "setPositionPercent", lua_cc_ui_Widget_setPositionPercent);
        tolua_function(L, "getLayoutSize", lua_cc_ui_Widget_getLayoutSize);
        tolua_function(L, "getVirtualRendererSize", lua_cc_ui_Widget_getVirtualRendererSize);
        tolua_function(L, "getLayoutParameter", lua_cc_ui_Widget_getLayoutParameter);
        tolua_function(L, "getTouchBeganPosition", lua_cc_ui_Widget_getTouchBeganPosition);
        tolua_function(L, "updateSizeAndPosition", lua_cc_ui_Widget_updateSizeAndPosition);
        tolua_function(L, "getTouchMovePosition", lua_cc_ui_Widget_getTouchMovePosition);
        tolua_function(L, "getTouchEndPosition", lua_cc_ui_Widget_getTouchEndPosition);
        tolua_function(L, "getPositionPercent", lua_cc_ui_Widget_getPositionPercent);
        tolua_function(L, "isClippingParentContainsPoint", lua_cc_ui_Widget_isClippingParentContainsPoint);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Layout");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Layout_constructor);
        tolua_function(L, "setBackGroundColorVector", lua_cc_ui_Layout_setBackGroundColorVector);
        tolua_function(L, "setBackGroundImageColor", lua_cc_ui_Layout_setBackGroundImageColor);
        tolua_function(L, "getBackGroundColorVector", lua_cc_ui_Layout_getBackGroundColorVector);
        tolua_function(L, "getRenderFile", lua_cc_ui_Layout_getRenderFile);
        tolua_function(L, "setBackGroundColor", lua_cc_ui_Layout_setBackGroundColor);
        tolua_function(L, "getBackGroundImageCapInsets", lua_cc_ui_Layout_getBackGroundImageCapInsets);
        tolua_function(L, "getBackGroundColor", lua_cc_ui_Layout_getBackGroundColor);
        tolua_function(L, "getBackGroundImageColor", lua_cc_ui_Layout_getBackGroundImageColor);
        tolua_function(L, "getBackGroundEndColor", lua_cc_ui_Layout_getBackGroundEndColor);
        tolua_function(L, "setBackGroundImageCapInsets", lua_cc_ui_Layout_setBackGroundImageCapInsets);
        tolua_function(L, "getBackGroundImageTextureSize", lua_cc_ui_Layout_getBackGroundImageTextureSize);
        tolua_function(L, "getBackGroundStartColor", lua_cc_ui_Layout_getBackGroundStartColor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Button");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Button_constructor);
        tolua_function(L, "getNormalTextureSize", lua_cc_ui_Button_getNormalTextureSize);
        tolua_function(L, "getDisabledFile", lua_cc_ui_Button_getDisabledFile);
        tolua_function(L, "getCapInsetsDisabledRenderer", lua_cc_ui_Button_getCapInsetsDisabledRenderer);
        tolua_function(L, "setTitleColor", lua_cc_ui_Button_setTitleColor);
        tolua_function(L, "getNormalFile", lua_cc_ui_Button_getNormalFile);
        tolua_function(L, "setCapInsetsDisabledRenderer", lua_cc_ui_Button_setCapInsetsDisabledRenderer);
        tolua_function(L, "setCapInsets", lua_cc_ui_Button_setCapInsets);
        tolua_function(L, "init", lua_cc_ui_Button_init);
        tolua_function(L, "setCapInsetsNormalRenderer", lua_cc_ui_Button_setCapInsetsNormalRenderer);
        tolua_function(L, "getCapInsetsNormalRenderer", lua_cc_ui_Button_getCapInsetsNormalRenderer);
        tolua_function(L, "getCapInsetsPressedRenderer", lua_cc_ui_Button_getCapInsetsPressedRenderer);
        tolua_function(L, "setCapInsetsPressedRenderer", lua_cc_ui_Button_setCapInsetsPressedRenderer);
        tolua_function(L, "getPressedFile", lua_cc_ui_Button_getPressedFile);
        tolua_function(L, "getTitleColor", lua_cc_ui_Button_getTitleColor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.AbstractCheckButton");
    if (lua_istable(L, -1)) {
        tolua_function(L, "getCrossDisabledFile", lua_cc_ui_AbstractCheckButton_getCrossDisabledFile);
        tolua_function(L, "getBackDisabledFile", lua_cc_ui_AbstractCheckButton_getBackDisabledFile);
        tolua_function(L, "getCrossNormalFile", lua_cc_ui_AbstractCheckButton_getCrossNormalFile);
        tolua_function(L, "getBackPressedFile", lua_cc_ui_AbstractCheckButton_getBackPressedFile);
        tolua_function(L, "init", lua_cc_ui_AbstractCheckButton_init);
        tolua_function(L, "getBackNormalFile", lua_cc_ui_AbstractCheckButton_getBackNormalFile);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.CheckBox");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_CheckBox_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RadioButton");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RadioButton_constructor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RadioButtonGroup");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RadioButtonGroup_constructor);
        tolua_function(L, "setSelectedButtonWithoutEvent", lua_cc_ui_RadioButtonGroup_setSelectedButtonWithoutEvent);
        tolua_function(L, "setSelectedButton", lua_cc_ui_RadioButtonGroup_setSelectedButton);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.ImageView");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_ImageView_constructor);
        tolua_function(L, "getBlendFunc", lua_cc_ui_ImageView_getBlendFunc);
        tolua_function(L, "setBlendFunc", lua_cc_ui_ImageView_setBlendFunc);
        tolua_function(L, "init", lua_cc_ui_ImageView_init);
        tolua_function(L, "setTextureRect", lua_cc_ui_ImageView_setTextureRect);
        tolua_function(L, "setCapInsets", lua_cc_ui_ImageView_setCapInsets);
        tolua_function(L, "getRenderFile", lua_cc_ui_ImageView_getRenderFile);
        tolua_function(L, "getCapInsets", lua_cc_ui_ImageView_getCapInsets);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Text");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Text_constructor);
        tolua_function(L, "enableShadow", lua_cc_ui_Text_enableShadow);
        tolua_function(L, "getTextColor", lua_cc_ui_Text_getTextColor);
        tolua_function(L, "getBlendFunc", lua_cc_ui_Text_getBlendFunc);
        tolua_function(L, "getShadowOffset", lua_cc_ui_Text_getShadowOffset);
        tolua_function(L, "init", lua_cc_ui_Text_init);
        tolua_function(L, "setTextAreaSize", lua_cc_ui_Text_setTextAreaSize);
        tolua_function(L, "getAutoRenderSize", lua_cc_ui_Text_getAutoRenderSize);
        tolua_function(L, "enableOutline", lua_cc_ui_Text_enableOutline);
        tolua_function(L, "getEffectColor", lua_cc_ui_Text_getEffectColor);
        tolua_function(L, "getShadowColor", lua_cc_ui_Text_getShadowColor);
        tolua_function(L, "setTextColor", lua_cc_ui_Text_setTextColor);
        tolua_function(L, "enableGlow", lua_cc_ui_Text_enableGlow);
        tolua_function(L, "setBlendFunc", lua_cc_ui_Text_setBlendFunc);
        tolua_function(L, "getTextAreaSize", lua_cc_ui_Text_getTextAreaSize);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.TextAtlas");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_TextAtlas_constructor);
        tolua_function(L, "getRenderFile", lua_cc_ui_TextAtlas_getRenderFile);
        tolua_function(L, "adaptRenderers", lua_cc_ui_TextAtlas_adaptRenderers);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.LoadingBar");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_LoadingBar_constructor);
        tolua_function(L, "getRenderFile", lua_cc_ui_LoadingBar_getRenderFile);
        tolua_function(L, "setCapInsets", lua_cc_ui_LoadingBar_setCapInsets);
        tolua_function(L, "getCapInsets", lua_cc_ui_LoadingBar_getCapInsets);
        tolua_function(L, "create", lua_cc_ui_LoadingBar_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.ScrollView");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_ScrollView_constructor);
        tolua_function(L, "getScrolledPercentBothDirection", lua_cc_ui_ScrollView_getScrolledPercentBothDirection);
        tolua_function(L, "setScrollBarColor", lua_cc_ui_ScrollView_setScrollBarColor);
        tolua_function(L, "setInnerContainerPosition", lua_cc_ui_ScrollView_setInnerContainerPosition);
        tolua_function(L, "scrollToPercentBothDirection", lua_cc_ui_ScrollView_scrollToPercentBothDirection);
        tolua_function(L, "setInnerContainerSize", lua_cc_ui_ScrollView_setInnerContainerSize);
        tolua_function(L, "getInnerContainerPosition", lua_cc_ui_ScrollView_getInnerContainerPosition);
        tolua_function(L, "setScrollBarPositionFromCornerForHorizontal", lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForHorizontal);
        tolua_function(L, "getScrollBarColor", lua_cc_ui_ScrollView_getScrollBarColor);
        tolua_function(L, "getScrollBarPositionFromCornerForHorizontal", lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForHorizontal);
        tolua_function(L, "jumpToPercentBothDirection", lua_cc_ui_ScrollView_jumpToPercentBothDirection);
        tolua_function(L, "setScrollBarPositionFromCorner", lua_cc_ui_ScrollView_setScrollBarPositionFromCorner);
        tolua_function(L, "setScrollBarPositionFromCornerForVertical", lua_cc_ui_ScrollView_setScrollBarPositionFromCornerForVertical);
        tolua_function(L, "getScrollBarPositionFromCornerForVertical", lua_cc_ui_ScrollView_getScrollBarPositionFromCornerForVertical);
        tolua_function(L, "getInnerContainerSize", lua_cc_ui_ScrollView_getInnerContainerSize);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.ListView");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_ListView_constructor);
        tolua_function(L, "scrollToItem", lua_cc_ui_ListView_scrollToItem);
        tolua_function(L, "jumpToItem", lua_cc_ui_ListView_jumpToItem);
        tolua_function(L, "insertDefaultItem", lua_cc_ui_ListView_insertDefaultItem);
        tolua_function(L, "doLayout", lua_cc_ui_ListView_doLayout);
        tolua_function(L, "getItems", lua_cc_ui_ListView_getItems);
        tolua_function(L, "getItem", lua_cc_ui_ListView_getItem);
        tolua_function(L, "removeItem", lua_cc_ui_ListView_removeItem);
        tolua_function(L, "getClosestItemToPosition", lua_cc_ui_ListView_getClosestItemToPosition);
        tolua_function(L, "getClosestItemToPositionInCurrentView", lua_cc_ui_ListView_getClosestItemToPositionInCurrentView);
        tolua_function(L, "insertCustomItem", lua_cc_ui_ListView_insertCustomItem);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Slider");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Slider_constructor);
        tolua_function(L, "getBallNormalFile", lua_cc_ui_Slider_getBallNormalFile);
        tolua_function(L, "getBallPressedFile", lua_cc_ui_Slider_getBallPressedFile);
        tolua_function(L, "setCapInsetProgressBarRenderer", lua_cc_ui_Slider_setCapInsetProgressBarRenderer);
        tolua_function(L, "getProgressBarFile", lua_cc_ui_Slider_getProgressBarFile);
        tolua_function(L, "getCapInsetsBarRenderer", lua_cc_ui_Slider_getCapInsetsBarRenderer);
        tolua_function(L, "getCapInsetsProgressBarRenderer", lua_cc_ui_Slider_getCapInsetsProgressBarRenderer);
        tolua_function(L, "getBackFile", lua_cc_ui_Slider_getBackFile);
        tolua_function(L, "getBallDisabledFile", lua_cc_ui_Slider_getBallDisabledFile);
        tolua_function(L, "setCapInsetsBarRenderer", lua_cc_ui_Slider_setCapInsetsBarRenderer);
        tolua_function(L, "setCapInsets", lua_cc_ui_Slider_setCapInsets);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.TextField");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_TextField_constructor);
        tolua_function(L, "getTextColor", lua_cc_ui_TextField_getTextColor);
        tolua_function(L, "setTextAreaSize", lua_cc_ui_TextField_setTextAreaSize);
        tolua_function(L, "getAutoRenderSize", lua_cc_ui_TextField_getAutoRenderSize);
        tolua_function(L, "getPlaceHolderColor", lua_cc_ui_TextField_getPlaceHolderColor);
        tolua_function(L, "setCursorFromPoint", lua_cc_ui_TextField_setCursorFromPoint);
        tolua_function(L, "setPlaceHolderColor", lua_cc_ui_TextField_setPlaceHolderColor);
        tolua_function(L, "setTextColor", lua_cc_ui_TextField_setTextColor);
        tolua_function(L, "setCursorChar", lua_cc_ui_TextField_setCursorChar);
        tolua_function(L, "setTouchSize", lua_cc_ui_TextField_setTouchSize);
        tolua_function(L, "getTouchSize", lua_cc_ui_TextField_getTouchSize);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.TextBMFont");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_TextBMFont_constructor);
        tolua_function(L, "getRenderFile", lua_cc_ui_TextBMFont_getRenderFile);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.PageView");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_PageView_constructor);
        tolua_function(L, "setIndicatorSelectedIndexColor", lua_cc_ui_PageView_setIndicatorSelectedIndexColor);
        tolua_function(L, "getIndicatorPosition", lua_cc_ui_PageView_getIndicatorPosition);
        tolua_function(L, "setCurrentPageIndex", lua_cc_ui_PageView_setCurrentPageIndex);
        tolua_function(L, "getIndicatorIndexNodesColor", lua_cc_ui_PageView_getIndicatorIndexNodesColor);
        tolua_function(L, "getIndicatorSelectedIndexColor", lua_cc_ui_PageView_getIndicatorSelectedIndexColor);
        tolua_function(L, "setIndicatorPosition", lua_cc_ui_PageView_setIndicatorPosition);
        tolua_function(L, "scrollToPage", lua_cc_ui_PageView_scrollToPage);
        tolua_function(L, "setIndicatorPositionAsAnchorPoint", lua_cc_ui_PageView_setIndicatorPositionAsAnchorPoint);
        tolua_function(L, "scrollToItem", lua_cc_ui_PageView_scrollToItem);
        tolua_function(L, "setIndicatorIndexNodesColor", lua_cc_ui_PageView_setIndicatorIndexNodesColor);
        tolua_function(L, "getIndicatorPositionAsAnchorPoint", lua_cc_ui_PageView_getIndicatorPositionAsAnchorPoint);
        tolua_function(L, "removePageAtIndex", lua_cc_ui_PageView_removePageAtIndex);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Helper");
    if (lua_istable(L, -1)) {
        tolua_function(L, "convertBoundingBoxToScreen", lua_cc_ui_Helper_convertBoundingBoxToScreen);
        tolua_function(L, "restrictCapInsetRect", lua_cc_ui_Helper_restrictCapInsetRect);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichElement");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichElement_constructor);
        tolua_function(L, "init", lua_cc_ui_RichElement_init);
        tolua_function(L, "setColor", lua_cc_ui_RichElement_setColor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichElementText");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichElementText_constructor);
        tolua_function(L, "init", lua_cc_ui_RichElementText_init);
        tolua_function(L, "create", lua_cc_ui_RichElementText_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichElementImage");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichElementImage_constructor);
        tolua_function(L, "init", lua_cc_ui_RichElementImage_init);
        tolua_function(L, "create", lua_cc_ui_RichElementImage_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichElementCustomNode");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichElementCustomNode_constructor);
        tolua_function(L, "init", lua_cc_ui_RichElementCustomNode_init);
        tolua_function(L, "create", lua_cc_ui_RichElementCustomNode_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichElementNewLine");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichElementNewLine_constructor);
        tolua_function(L, "create", lua_cc_ui_RichElementNewLine_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RichText");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RichText_constructor);
        tolua_function(L, "setAnchorTextOutline", lua_cc_ui_RichText_setAnchorTextOutline);
        tolua_function(L, "setAnchorTextShadow", lua_cc_ui_RichText_setAnchorTextShadow);
        tolua_function(L, "setAnchorTextGlow", lua_cc_ui_RichText_setAnchorTextGlow);
        tolua_function(L, "getAnchorTextOutlineColor3B", lua_cc_ui_RichText_getAnchorTextOutlineColor3B);
        tolua_function(L, "stringWithColor4B", lua_cc_ui_RichText_stringWithColor4B);
        tolua_function(L, "initWithXML", lua_cc_ui_RichText_initWithXML);
        tolua_function(L, "getAnchorFontColor3B", lua_cc_ui_RichText_getAnchorFontColor3B);
        tolua_function(L, "getAnchorTextGlowColor3B", lua_cc_ui_RichText_getAnchorTextGlowColor3B);
        tolua_function(L, "getDefaults", lua_cc_ui_RichText_getDefaults);
        tolua_function(L, "setDefaults", lua_cc_ui_RichText_setDefaults);
        tolua_function(L, "removeElement", lua_cc_ui_RichText_removeElement);
        tolua_function(L, "getAnchorTextShadowOffset", lua_cc_ui_RichText_getAnchorTextShadowOffset);
        tolua_function(L, "getAnchorTextShadowColor3B", lua_cc_ui_RichText_getAnchorTextShadowColor3B);
        tolua_function(L, "stringWithColor3B", lua_cc_ui_RichText_stringWithColor3B);
        tolua_function(L, "getFontColor3B", lua_cc_ui_RichText_getFontColor3B);
        tolua_function(L, "color3BWithString", lua_cc_ui_RichText_color3BWithString);
        tolua_function(L, "createWithXML", lua_cc_ui_RichText_createWithXML);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.HBox");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_HBox_constructor);
        tolua_function(L, "initWithSize", lua_cc_ui_HBox_initWithSize);
        tolua_function(L, "create", lua_cc_ui_HBox_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.VBox");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_VBox_constructor);
        tolua_function(L, "initWithSize", lua_cc_ui_VBox_initWithSize);
        tolua_function(L, "create", lua_cc_ui_VBox_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.RelativeBox");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_RelativeBox_constructor);
        tolua_function(L, "initWithSize", lua_cc_ui_RelativeBox_initWithSize);
        tolua_function(L, "create", lua_cc_ui_RelativeBox_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.Scale9Sprite");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_Scale9Sprite_constructor);
        tolua_function(L, "updateWithSprite", lua_cc_ui_Scale9Sprite_updateWithSprite);
        tolua_function(L, "resizableSpriteWithCapInsets", lua_cc_ui_Scale9Sprite_resizableSpriteWithCapInsets);
        tolua_function(L, "getCapInsets", lua_cc_ui_Scale9Sprite_getCapInsets);
        tolua_function(L, "initWithSpriteFrameName", lua_cc_ui_Scale9Sprite_initWithSpriteFrameName);
        tolua_function(L, "init", lua_cc_ui_Scale9Sprite_init);
        tolua_function(L, "setPreferredSize", lua_cc_ui_Scale9Sprite_setPreferredSize);
        tolua_function(L, "setSpriteFrame", lua_cc_ui_Scale9Sprite_setSpriteFrame);
        tolua_function(L, "getOriginalSize", lua_cc_ui_Scale9Sprite_getOriginalSize);
        tolua_function(L, "initWithFile", lua_cc_ui_Scale9Sprite_initWithFile);
        tolua_function(L, "initWithSpriteFrame", lua_cc_ui_Scale9Sprite_initWithSpriteFrame);
        tolua_function(L, "getPreferredSize", lua_cc_ui_Scale9Sprite_getPreferredSize);
        tolua_function(L, "setCapInsets", lua_cc_ui_Scale9Sprite_setCapInsets);
        tolua_function(L, "create", lua_cc_ui_Scale9Sprite_create);
        tolua_function(L, "createWithSpriteFrameName", lua_cc_ui_Scale9Sprite_createWithSpriteFrameName);
        tolua_function(L, "createWithSpriteFrame", lua_cc_ui_Scale9Sprite_createWithSpriteFrame);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.EditBox");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_EditBox_constructor);
        tolua_function(L, "keyboardDidShow", lua_cc_ui_EditBox_keyboardDidShow);
        tolua_function(L, "initWithSizeAndBackgroundSprite", lua_cc_ui_EditBox_initWithSizeAndBackgroundSprite);
        tolua_function(L, "keyboardDidHide", lua_cc_ui_EditBox_keyboardDidHide);
        tolua_function(L, "getCapInsetsDisabledRenderer", lua_cc_ui_EditBox_getCapInsetsDisabledRenderer);
        tolua_function(L, "setCapInsetsDisabledRenderer", lua_cc_ui_EditBox_setCapInsetsDisabledRenderer);
        tolua_function(L, "keyboardWillShow", lua_cc_ui_EditBox_keyboardWillShow);
        tolua_function(L, "setPlaceholderFontColor", lua_cc_ui_EditBox_setPlaceholderFontColor);
        tolua_function(L, "setFontColor", lua_cc_ui_EditBox_setFontColor);
        tolua_function(L, "keyboardWillHide", lua_cc_ui_EditBox_keyboardWillHide);
        tolua_function(L, "setCapInsetsNormalRenderer", lua_cc_ui_EditBox_setCapInsetsNormalRenderer);
        tolua_function(L, "getFontColor", lua_cc_ui_EditBox_getFontColor);
        tolua_function(L, "initWithSizeAndTexture", lua_cc_ui_EditBox_initWithSizeAndTexture);
        tolua_function(L, "getCapInsetsNormalRenderer", lua_cc_ui_EditBox_getCapInsetsNormalRenderer);
        tolua_function(L, "getCapInsetsPressedRenderer", lua_cc_ui_EditBox_getCapInsetsPressedRenderer);
        tolua_function(L, "setCapInsetsPressedRenderer", lua_cc_ui_EditBox_setCapInsetsPressedRenderer);
        tolua_function(L, "getPlaceholderFontColor", lua_cc_ui_EditBox_getPlaceholderFontColor);
        tolua_function(L, "setCapInsets", lua_cc_ui_EditBox_setCapInsets);
        tolua_function(L, "create", lua_cc_ui_EditBox_create);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.LayoutComponent");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_ui_LayoutComponent_constructor);
        tolua_function(L, "getAnchorPosition", lua_cc_ui_LayoutComponent_getAnchorPosition);
        tolua_function(L, "getSize", lua_cc_ui_LayoutComponent_getSize);
        tolua_function(L, "setAnchorPosition", lua_cc_ui_LayoutComponent_setAnchorPosition);
        tolua_function(L, "getPercentContentSize", lua_cc_ui_LayoutComponent_getPercentContentSize);
        tolua_function(L, "setPosition", lua_cc_ui_LayoutComponent_setPosition);
        tolua_function(L, "getPosition", lua_cc_ui_LayoutComponent_getPosition);
        tolua_function(L, "setPercentContentSize", lua_cc_ui_LayoutComponent_setPercentContentSize);
        tolua_function(L, "setSize", lua_cc_ui_LayoutComponent_setSize);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.TabHeader");
    if (lua_istable(L, -1)) {
        tolua_function(L, "getTitleColor", lua_cc_ui_TabHeader_getTitleColor);
        tolua_function(L, "setTitleColor", lua_cc_ui_TabHeader_setTitleColor);
    }
    lua_pop(L, 1);
    luaL_getmetatable(L, "ccui.TabControl");
    if (lua_istable(L, -1)) {
        tolua_function(L, "setSelectTab", lua_cc_ui_TabControl_setSelectTab);
        tolua_function(L, "setTabChangedEventListener", lua_cc_ui_TabControl_setTabChangedEventListener);
    }
    lua_pop(L, 1);
}
