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

int lua_cc_base_SpriteFrame_getOffset(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getOffset",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_setOriginalSizeInPixels(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_setOriginalSizeInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.SpriteFrame:setOriginalSizeInPixels");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_setOriginalSizeInPixels'", nullptr);
            return 0;
        }
        cobj->setOriginalSizeInPixels(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:setOriginalSizeInPixels",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_setOriginalSizeInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getAnchorPoint(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getAnchorPoint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getAnchorPoint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getAnchorPoint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_getOffsetInPixels(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteFrame_getOffsetInPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteFrame_getOffsetInPixels'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOffsetInPixels();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteFrame:getOffsetInPixels",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_getOffsetInPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 5)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:create");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::SpriteFrame* ret = cocos2d::SpriteFrame::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:create");
            if (!ok) { break; }
            cocos2d::SpriteFrame* ret = cocos2d::SpriteFrame::create(arg0, arg1);
            object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.SpriteFrame:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_SpriteFrame_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SpriteFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 5)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::SpriteFrame* ret = cocos2d::SpriteFrame::createWithTexture(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.SpriteFrame:createWithTexture");
            if (!ok) { break; }
            cocos2d::SpriteFrame* ret = cocos2d::SpriteFrame::createWithTexture(arg0, arg1);
            object_to_luaval<cocos2d::SpriteFrame>(tolua_S, "cc.SpriteFrame",(cocos2d::SpriteFrame*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.SpriteFrame:createWithTexture",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteFrame_createWithTexture'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_AnimationFrame_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationFrame_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AnimationFrame();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AnimationFrame");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:AnimationFrame",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationFrame_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationFrame_getUserInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationFrame* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimationFrame",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::AnimationFrame*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AnimationFrame_getUserInfo'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueMap& ret = cobj->getUserInfo();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueMap& ret = cobj->getUserInfo();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.AnimationFrame:getUserInfo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationFrame_getUserInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationFrame_setUserInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimationFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AnimationFrame_setUserInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.AnimationFrame:setUserInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationFrame_setUserInfo'", nullptr);
            return 0;
        }
        cobj->setUserInfo(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:setUserInfo",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationFrame_setUserInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationFrame_initWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationFrame* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimationFrame*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AnimationFrame_initWithSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::SpriteFrame* arg0;
        double arg1;
        cocos2d::ValueMap arg2;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.AnimationFrame:initWithSpriteFrame");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.AnimationFrame:initWithSpriteFrame");

        ok &= luaval_to_ccvaluemap(tolua_S, 4, &arg2, "cc.AnimationFrame:initWithSpriteFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationFrame_initWithSpriteFrame'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrame(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationFrame:initWithSpriteFrame",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationFrame_initWithSpriteFrame'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationFrame_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AnimationFrame",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::SpriteFrame* arg0;
        double arg1;
        cocos2d::ValueMap arg2;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.AnimationFrame:create");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.AnimationFrame:create");
        ok &= luaval_to_ccvaluemap(tolua_S, 4, &arg2, "cc.AnimationFrame:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationFrame_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::AnimationFrame::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::AnimationFrame>(tolua_S, "cc.AnimationFrame",(cocos2d::AnimationFrame*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AnimationFrame:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationFrame_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Animation_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Animation();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Animation");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:Animation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_initWithAnimationFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animation_initWithAnimationFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vector<cocos2d::AnimationFrame *> arg0;
        double arg1;
        unsigned int arg2;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:initWithAnimationFrames");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:initWithAnimationFrames");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Animation:initWithAnimationFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_initWithAnimationFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithAnimationFrames(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:initWithAnimationFrames",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_initWithAnimationFrames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_setFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animation_setFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::AnimationFrame *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:setFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_setFrames'", nullptr);
            return 0;
        }
        cobj->setFrames(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:setFrames",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_setFrames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_getFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animation_getFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_getFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getFrames();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:getFrames",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_getFrames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_initWithSpriteFrames(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animation_initWithSpriteFrames'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:initWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_initWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrames(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;
        double arg1;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:initWithSpriteFrames");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:initWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_initWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrames(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;
        double arg1;
        unsigned int arg2;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:initWithSpriteFrames");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:initWithSpriteFrames");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Animation:initWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_initWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithSpriteFrames(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:initWithSpriteFrames",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_initWithSpriteFrames'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_addSpriteFrameWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animation_addSpriteFrameWithTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Texture2D* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.Animation:addSpriteFrameWithTexture");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.Animation:addSpriteFrameWithTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_addSpriteFrameWithTexture'", nullptr);
            return 0;
        }
        cobj->addSpriteFrameWithTexture(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation:addSpriteFrameWithTexture",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_addSpriteFrameWithTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animation_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Vector<cocos2d::AnimationFrame *> arg0;
            ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:create");
            if (!ok) { break; }
            cocos2d::Animation* ret = cocos2d::Animation::create(arg0, arg1);
            object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Vector<cocos2d::AnimationFrame *> arg0;
            ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:create");
            if (!ok) { break; }
            unsigned int arg2;
            ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Animation:create");
            if (!ok) { break; }
            cocos2d::Animation* ret = cocos2d::Animation::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::Animation* ret = cocos2d::Animation::create();
            object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Animation:create",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Animation_createWithSpriteFrames(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Animation",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;
        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:createWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_createWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Animation::createWithSpriteFrames(arg0);
        object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;
        double arg1;
        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:createWithSpriteFrames");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:createWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_createWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Animation::createWithSpriteFrames(arg0, arg1);
        object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Vector<cocos2d::SpriteFrame *> arg0;
        double arg1;
        unsigned int arg2;
        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Animation:createWithSpriteFrames");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Animation:createWithSpriteFrames");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.Animation:createWithSpriteFrames");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animation_createWithSpriteFrames'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Animation::createWithSpriteFrames(arg0, arg1, arg2);
        object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Animation:createWithSpriteFrames",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animation_createWithSpriteFrames'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Sequence_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sequence* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sequence_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Sequence();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Sequence");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sequence:Sequence",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sequence_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Sequence_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sequence* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sequence",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sequence*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Sequence_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::FiniteTimeAction *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Sequence:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Sequence_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sequence:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Sequence_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Repeat_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Repeat* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Repeat_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Repeat();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Repeat");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Repeat:Repeat",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Repeat_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RepeatForever_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RepeatForever* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RepeatForever_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::RepeatForever();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RepeatForever");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RepeatForever:RepeatForever",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RepeatForever_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Spawn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Spawn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Spawn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Spawn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Spawn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Spawn:Spawn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Spawn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Spawn_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Spawn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Spawn",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Spawn*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Spawn_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::FiniteTimeAction *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Spawn:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Spawn_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Spawn:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Spawn_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RotateTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RotateTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RotateTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::RotateTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RotateTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RotateTo:RotateTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RotateTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RotateTo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RotateTo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::RotateTo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RotateTo_initWithDuration'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateTo:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.RotateTo:initWithDuration");

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
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateTo:initWithDuration");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateTo:initWithDuration");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.RotateTo:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.RotateTo:initWithDuration",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RotateTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.RotateTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateTo:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateTo:create");
            if (!ok) { break; }
            cocos2d::RotateTo* ret = cocos2d::RotateTo::create(arg0, arg1);
            object_to_luaval<cocos2d::RotateTo>(tolua_S, "cc.RotateTo",(cocos2d::RotateTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateTo:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateTo:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.RotateTo:create");
            if (!ok) { break; }
            cocos2d::RotateTo* ret = cocos2d::RotateTo::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::RotateTo>(tolua_S, "cc.RotateTo",(cocos2d::RotateTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateTo:create");
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.RotateTo:create");
            if (!ok) { break; }
            cocos2d::RotateTo* ret = cocos2d::RotateTo::create(arg0, arg1);
            object_to_luaval<cocos2d::RotateTo>(tolua_S, "cc.RotateTo",(cocos2d::RotateTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.RotateTo:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateTo_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_RotateBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RotateBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RotateBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::RotateBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.RotateBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RotateBy:RotateBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RotateBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RotateBy* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RotateBy",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::RotateBy*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RotateBy_initWithDuration'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.RotateBy:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.RotateBy:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_RotateBy_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.RotateBy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateBy:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.RotateBy:create");
            if (!ok) { break; }
            cocos2d::RotateBy* ret = cocos2d::RotateBy::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::RotateBy>(tolua_S, "cc.RotateBy",(cocos2d::RotateBy*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.RotateBy:create");
            if (!ok) { break; }
            cocos2d::RotateBy* ret = cocos2d::RotateBy::create(arg0, arg1);
            object_to_luaval<cocos2d::RotateBy>(tolua_S, "cc.RotateBy",(cocos2d::RotateBy*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.RotateBy:create");
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.RotateBy:create");
            if (!ok) { break; }
            cocos2d::RotateBy* ret = cocos2d::RotateBy::create(arg0, arg1);
            object_to_luaval<cocos2d::RotateBy>(tolua_S, "cc.RotateBy",(cocos2d::RotateBy*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.RotateBy:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RotateBy_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_MoveBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MoveBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MoveBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MoveBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MoveBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MoveBy:MoveBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MoveBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MoveBy* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MoveBy",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MoveBy*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MoveBy_initWithDuration'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveBy:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.MoveBy:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveBy:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.MoveBy:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MoveBy:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MoveBy_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MoveBy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveBy:create");
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.MoveBy:create");
            if (!ok) { break; }
            cocos2d::MoveBy* ret = cocos2d::MoveBy::create(arg0, arg1);
            object_to_luaval<cocos2d::MoveBy>(tolua_S, "cc.MoveBy",(cocos2d::MoveBy*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveBy:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.MoveBy:create");
            if (!ok) { break; }
            cocos2d::MoveBy* ret = cocos2d::MoveBy::create(arg0, arg1);
            object_to_luaval<cocos2d::MoveBy>(tolua_S, "cc.MoveBy",(cocos2d::MoveBy*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.MoveBy:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveBy_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_MoveTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MoveTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MoveTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MoveTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MoveTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MoveTo:MoveTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MoveTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MoveTo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MoveTo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MoveTo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MoveTo_initWithDuration'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveTo:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.MoveTo:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveTo:initWithDuration");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.MoveTo:initWithDuration");

            if (!ok) { break; }
            bool ret = cobj->initWithDuration(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MoveTo:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MoveTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MoveTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveTo:create");
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.MoveTo:create");
            if (!ok) { break; }
            cocos2d::MoveTo* ret = cocos2d::MoveTo::create(arg0, arg1);
            object_to_luaval<cocos2d::MoveTo>(tolua_S, "cc.MoveTo",(cocos2d::MoveTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MoveTo:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.MoveTo:create");
            if (!ok) { break; }
            cocos2d::MoveTo* ret = cocos2d::MoveTo::create(arg0, arg1);
            object_to_luaval<cocos2d::MoveTo>(tolua_S, "cc.MoveTo",(cocos2d::MoveTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.MoveTo:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MoveTo_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_SkewTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SkewTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SkewTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SkewTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SkewTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SkewTo:SkewTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SkewTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SkewBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SkewBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SkewBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SkewBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SkewBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SkewBy:SkewBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SkewBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::JumpBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.JumpBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpBy:JumpBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.JumpBy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::JumpBy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_JumpBy_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        double arg2;
        int arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpBy:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpBy:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpBy:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpBy:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpBy_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpBy:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpBy_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.JumpBy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        double arg2;
        int arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpBy:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpBy:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpBy:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpBy:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpBy_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::JumpBy::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::JumpBy>(tolua_S, "cc.JumpBy",(cocos2d::JumpBy*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.JumpBy:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpBy_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_JumpTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::JumpTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.JumpTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTo:JumpTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.JumpTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::JumpTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_JumpTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec2 arg1;
        double arg2;
        int arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpTo:initWithDuration");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpTo:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpTo:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpTo:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTo:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_JumpTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.JumpTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec2 arg1;
        double arg2;
        int arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpTo:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.JumpTo:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpTo:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpTo:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_JumpTo_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::JumpTo::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::JumpTo>(tolua_S, "cc.JumpTo",(cocos2d::JumpTo*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.JumpTo:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_JumpTo_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_BezierBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BezierBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_BezierBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::BezierBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BezierBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BezierBy:BezierBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_BezierBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_BezierBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BezierBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BezierBy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BezierBy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_BezierBy_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::_ccBezierConfig arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BezierBy:initWithDuration");

        #pragma warning NO CONVERSION TO NATIVE FOR _ccBezierConfig
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_BezierBy_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BezierBy:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_BezierBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_BezierTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BezierTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_BezierTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::BezierTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BezierTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BezierTo:BezierTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_BezierTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_BezierTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BezierTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BezierTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BezierTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_BezierTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::_ccBezierConfig arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BezierTo:initWithDuration");

        #pragma warning NO CONVERSION TO NATIVE FOR _ccBezierConfig
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_BezierTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BezierTo:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_BezierTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ScaleTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ScaleTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ScaleTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ScaleTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ScaleTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScaleTo:ScaleTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ScaleTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ScaleBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ScaleBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ScaleBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ScaleBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ScaleBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScaleBy:ScaleBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ScaleBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Blink_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Blink* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Blink_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Blink();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Blink");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Blink:Blink",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Blink_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeTo:FadeTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FadeTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FadeTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FadeTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        uint16_t arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeTo:initWithDuration");

        ok &= luaval_to_uint16(tolua_S, 3,&arg1, "cc.FadeTo:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeTo:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FadeTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        uint16_t arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.FadeTo:create");
        ok &= luaval_to_uint16(tolua_S, 3,&arg1, "cc.FadeTo:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeTo_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FadeTo::create(arg0, arg1);
        object_to_luaval<cocos2d::FadeTo>(tolua_S, "cc.FadeTo",(cocos2d::FadeTo*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FadeTo:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeTo_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FadeIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeIn:FadeIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FadeOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FadeOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FadeOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FadeOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FadeOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FadeOut:FadeOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FadeOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TintTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TintTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TintTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TintTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TintTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TintTo:TintTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TintTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TintTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TintTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TintTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TintTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        uint16_t arg1;
        uint16_t arg2;
        uint16_t arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TintTo:initWithDuration");

        ok &= luaval_to_uint16(tolua_S, 3,&arg1, "cc.TintTo:initWithDuration");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "cc.TintTo:initWithDuration");

        ok &= luaval_to_uint16(tolua_S, 5,&arg3, "cc.TintTo:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TintTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TintTo:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TintTo_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TintTo",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TintTo:create");
            if (!ok) { break; }
            cocos2d::Color3B arg1;
            ok &= luaval_to_color3b(tolua_S, 3, &arg1, "cc.TintTo:create");
            if (!ok) { break; }
            cocos2d::TintTo* ret = cocos2d::TintTo::create(arg0, arg1);
            object_to_luaval<cocos2d::TintTo>(tolua_S, "cc.TintTo",(cocos2d::TintTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TintTo:create");
            if (!ok) { break; }
            uint16_t arg1;
            ok &= luaval_to_uint16(tolua_S, 3,&arg1, "cc.TintTo:create");
            if (!ok) { break; }
            uint16_t arg2;
            ok &= luaval_to_uint16(tolua_S, 4,&arg2, "cc.TintTo:create");
            if (!ok) { break; }
            uint16_t arg3;
            ok &= luaval_to_uint16(tolua_S, 5,&arg3, "cc.TintTo:create");
            if (!ok) { break; }
            cocos2d::TintTo* ret = cocos2d::TintTo::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::TintTo>(tolua_S, "cc.TintTo",(cocos2d::TintTo*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.TintTo:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintTo_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TintBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TintBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TintBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TintBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TintBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TintBy:TintBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TintBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TintBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TintBy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TintBy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TintBy_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        int32_t arg1;
        int32_t arg2;
        int32_t arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TintBy:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 3,&arg1, "cc.TintBy:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 4,&arg2, "cc.TintBy:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 5,&arg3, "cc.TintBy:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TintBy_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TintBy:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TintBy_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TintBy",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        int32_t arg1;
        int32_t arg2;
        int32_t arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.TintBy:create");
        ok &= luaval_to_int32(tolua_S, 3,&arg1, "cc.TintBy:create");
        ok &= luaval_to_int32(tolua_S, 4,&arg2, "cc.TintBy:create");
        ok &= luaval_to_int32(tolua_S, 5,&arg3, "cc.TintBy:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TintBy_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::TintBy::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::TintBy>(tolua_S, "cc.TintBy",(cocos2d::TintBy*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TintBy:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TintBy_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_DelayTime_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DelayTime* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_DelayTime_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::DelayTime();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DelayTime");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DelayTime:DelayTime",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_DelayTime_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animate_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Animate_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Animate();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Animate");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate:Animate",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animate_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Animate_getAnimation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Animate*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Animate_getAnimation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::Animation* ret = cobj->getAnimation();
            object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::Animation* ret = cobj->getAnimation();
            object_to_luaval<cocos2d::Animation>(tolua_S, "cc.Animation",(cocos2d::Animation*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Animate:getAnimation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Animate_getAnimation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TargetedAction_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TargetedAction* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TargetedAction_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TargetedAction();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TargetedAction");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TargetedAction:TargetedAction",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TargetedAction_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TargetedAction_getForcedTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TargetedAction* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TargetedAction",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TargetedAction*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TargetedAction_getForcedTarget'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const cocos2d::Node* ret = cobj->getForcedTarget();
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cocos2d::Node* ret = cobj->getForcedTarget();
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TargetedAction:getForcedTarget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TargetedAction_getForcedTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionFloat_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionFloat* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionFloat_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ActionFloat();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ActionFloat");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionFloat:ActionFloat",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionFloat_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionFloat_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionFloat* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionFloat",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionFloat*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionFloat_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        double arg1;
        double arg2;
        std::function<void (float)> arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ActionFloat:initWithDuration");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ActionFloat:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ActionFloat:initWithDuration");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionFloat_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionFloat:initWithDuration",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionFloat_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionFloat_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ActionFloat",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        double arg1;
        double arg2;
        std::function<void (float)> arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ActionFloat:create");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ActionFloat:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ActionFloat:create");
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionFloat_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::ActionFloat::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ActionFloat>(tolua_S, "cc.ActionFloat",(cocos2d::ActionFloat*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ActionFloat:create",argc, 4);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionFloat_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Properties_getColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getColor"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            cocos2d::Vec4* arg1;
            ok &= luaval_to_object<cocos2d::Vec4>(tolua_S, 3, "cc.Vec4",&arg1, "cc.Properties:getColor");

            if (!ok) { break; }
            bool ret = cobj->getColor(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getColor"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            cocos2d::Vec3* arg1;
            ok &= luaval_to_object<cocos2d::Vec3>(tolua_S, 3, "cc.Vec3",&arg1, "cc.Properties:getColor");

            if (!ok) { break; }
            bool ret = cobj->getColor(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Properties:getColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getNamespace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getNamespace'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const char* ret = cobj->getNamespace();
            tolua_pushstring(tolua_S,(const char*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Properties:getNamespace");

            if (!ok) { break; }
            cocos2d::Properties* ret = cobj->getNamespace(arg0);
            object_to_luaval<cocos2d::Properties>(tolua_S, "cc.Properties",(cocos2d::Properties*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Properties:getNamespace");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Properties:getNamespace");

            if (!ok) { break; }
            cocos2d::Properties* ret = cobj->getNamespace(arg0, arg1);
            object_to_luaval<cocos2d::Properties>(tolua_S, "cc.Properties",(cocos2d::Properties*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Properties:getNamespace");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.Properties:getNamespace");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.Properties:getNamespace");

            if (!ok) { break; }
            cocos2d::Properties* ret = cobj->getNamespace(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Properties>(tolua_S, "cc.Properties",(cocos2d::Properties*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Properties:getNamespace",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getNamespace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getNextNamespace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getNextNamespace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getNextNamespace'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNextNamespace();
        object_to_luaval<cocos2d::Properties>(tolua_S, "cc.Properties",(cocos2d::Properties*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getNextNamespace",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getNextNamespace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getVec3(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getVec3'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Vec3* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getVec3"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Vec3>(tolua_S, 3, "cc.Vec3",&arg1, "cc.Properties:getVec3");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getVec3'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVec3(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getVec3",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getVec3'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getVec2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getVec2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Vec2* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getVec2"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Vec2>(tolua_S, 3, "cc.Vec2",&arg1, "cc.Properties:getVec2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getVec2'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVec2(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getVec2",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getVec2'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getVec4(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getVec4'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Vec4* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getVec4"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Vec4>(tolua_S, 3, "cc.Vec4",&arg1, "cc.Properties:getVec4");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getVec4'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVec4(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getVec4",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getVec4'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getQuaternionFromAxisAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getQuaternionFromAxisAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Quaternion* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getQuaternionFromAxisAngle"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Quaternion>(tolua_S, 3, "cc.Quaternion",&arg1, "cc.Properties:getQuaternionFromAxisAngle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getQuaternionFromAxisAngle'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getQuaternionFromAxisAngle(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getQuaternionFromAxisAngle",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getQuaternionFromAxisAngle'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        std::string* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getPath"); arg0 = arg0_tmp.c_str();

        #pragma warning NO CONVERSION TO NATIVE FOR basic_string*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getPath'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPath(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getPath",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getPath'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_getMat4(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Properties* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Properties*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Properties_getMat4'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        cocos2d::Mat4* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:getMat4"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<cocos2d::Mat4>(tolua_S, 3, "cc.Mat4",&arg1, "cc.Properties:getMat4");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_getMat4'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMat4(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Properties:getMat4",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_getMat4'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Properties_parseColor(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseColor"); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::Vec4* arg1;
            ok &= luaval_to_object<cocos2d::Vec4>(tolua_S, 3, "cc.Vec4",&arg1, "cc.Properties:parseColor");
            if (!ok) { break; }
            bool ret = cocos2d::Properties::parseColor(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseColor"); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            cocos2d::Vec3* arg1;
            ok &= luaval_to_object<cocos2d::Vec3>(tolua_S, 3, "cc.Vec3",&arg1, "cc.Properties:parseColor");
            if (!ok) { break; }
            bool ret = cocos2d::Properties::parseColor(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.Properties:parseColor",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_parseColor'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Properties_parseVec3(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        cocos2d::Vec3* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseVec3"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_object<cocos2d::Vec3>(tolua_S, 3, "cc.Vec3",&arg1, "cc.Properties:parseVec3");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_parseVec3'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Properties::parseVec3(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Properties:parseVec3",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_parseVec3'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Properties_parseAxisAngle(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        cocos2d::Quaternion* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseAxisAngle"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_object<cocos2d::Quaternion>(tolua_S, 3, "cc.Quaternion",&arg1, "cc.Properties:parseAxisAngle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_parseAxisAngle'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Properties::parseAxisAngle(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Properties:parseAxisAngle",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_parseAxisAngle'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Properties_parseVec2(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        cocos2d::Vec2* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseVec2"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_object<cocos2d::Vec2>(tolua_S, 3, "cc.Vec2",&arg1, "cc.Properties:parseVec2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_parseVec2'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Properties::parseVec2(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Properties:parseVec2",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_parseVec2'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_Properties_parseVec4(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Properties",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        cocos2d::Vec4* arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.Properties:parseVec4"); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_object<cocos2d::Vec4>(tolua_S, 3, "cc.Vec4",&arg1, "cc.Properties:parseVec4");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Properties_parseVec4'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Properties::parseVec4(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Properties:parseVec4",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Properties_parseVec4'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_UserDefault_setLargeIntForKey(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::UserDefault* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::UserDefault*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_UserDefault_setLargeIntForKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        long long arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.UserDefault:setLargeIntForKey"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_long_long(tolua_S, 3,&arg1, "cc.UserDefault:setLargeIntForKey");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_UserDefault_setLargeIntForKey'", nullptr);
            return 0;
        }
        cobj->setLargeIntForKey(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.UserDefault:setLargeIntForKey",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_UserDefault_setLargeIntForKey'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_UserDefault_getLargeIntForKey(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::UserDefault* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::UserDefault*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_UserDefault_getLargeIntForKey'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.UserDefault:getLargeIntForKey"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            long long arg1;
            ok &= luaval_to_long_long(tolua_S, 3,&arg1, "cc.UserDefault:getLargeIntForKey");

            if (!ok) { break; }
            long long ret = cobj->getLargeIntForKey(arg0, arg1);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.UserDefault:getLargeIntForKey"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            long long ret = cobj->getLargeIntForKey(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.UserDefault:getLargeIntForKey",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_UserDefault_getLargeIntForKey'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_UserDefault_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_UserDefault_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::UserDefault::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.UserDefault:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_UserDefault_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FileUtils_removeFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_removeFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:removeFile");

            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->removeFile(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:removeFile");

            if (!ok) { break; }
            bool ret = cobj->removeFile(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:removeFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_removeFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_listFilesRecursivelyAsync(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_listFilesRecursivelyAsync'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::function<void (std::vector<std::string>)> arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:listFilesRecursivelyAsync");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_listFilesRecursivelyAsync'", nullptr);
            return 0;
        }
        cobj->listFilesRecursivelyAsync(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:listFilesRecursivelyAsync",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_listFilesRecursivelyAsync'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_renameFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_renameFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::function<void (bool)> arg3;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->renameFile(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg2;
            ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            bool ret = cobj->renameFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            bool ret = cobj->renameFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:renameFile");

            if (!ok) { break; }
            std::function<void (bool)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->renameFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:renameFile",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_renameFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getValueVectorFromFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getValueVectorFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:getValueVectorFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getValueVectorFromFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getValueVectorFromFile(arg0);
        ccvaluevector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getValueVectorFromFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getValueVectorFromFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getSearchPaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getSearchPaths'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSearchPaths();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getSearchPaths",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getSearchPaths'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_writeToFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_writeToFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ValueMap arg0;
        std::string_view arg1;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.FileUtils:writeToFile");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeToFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_writeToFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->writeToFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:writeToFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_writeToFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getOriginalSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getOriginalSearchPaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getOriginalSearchPaths'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOriginalSearchPaths();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getOriginalSearchPaths",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getOriginalSearchPaths'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_listFiles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_listFiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:listFiles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_listFiles'", nullptr);
            return 0;
        }
        auto&& ret = cobj->listFiles(arg0);
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:listFiles",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_listFiles'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getValueMapFromFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getValueMapFromFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:getValueMapFromFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getValueMapFromFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getValueMapFromFile(arg0);
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getValueMapFromFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getValueMapFromFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getFileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getFileSize'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:getFileSize");

            if (!ok) { break; }
            std::function<void (long long)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->getFileSize(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:getFileSize");

            if (!ok) { break; }
            long long ret = cobj->getFileSize(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:getFileSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getFileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_getValueMapFromData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_getValueMapFromData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.FileUtils:getValueMapFromData"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.FileUtils:getValueMapFromData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getValueMapFromData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getValueMapFromData(arg0, arg1);
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:getValueMapFromData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getValueMapFromData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_removeDirectory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_removeDirectory'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:removeDirectory");

            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->removeDirectory(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:removeDirectory");

            if (!ok) { break; }
            bool ret = cobj->removeDirectory(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:removeDirectory",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_removeDirectory'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_setSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_setSearchPaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<std::string> arg0;

        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "cc.FileUtils:setSearchPaths");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_setSearchPaths'", nullptr);
            return 0;
        }
        cobj->setSearchPaths(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:setSearchPaths",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_setSearchPaths'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_writeStringToFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_writeStringToFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.FileUtils:writeStringToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeStringToFile");

            if (!ok) { break; }
            std::function<void (bool)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->writeStringToFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:writeStringToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeStringToFile");

            if (!ok) { break; }
            bool ret = cobj->writeStringToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:writeStringToFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_writeStringToFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_writeValueVectorToFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_writeValueVectorToFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::ValueVector arg0;
            ok &= luaval_to_ccvaluevector(tolua_S, 2, &arg0, "cc.FileUtils:writeValueVectorToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeValueVectorToFile");

            if (!ok) { break; }
            std::function<void (bool)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->writeValueVectorToFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::ValueVector arg0;
            ok &= luaval_to_ccvaluevector(tolua_S, 2, &arg0, "cc.FileUtils:writeValueVectorToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeValueVectorToFile");

            if (!ok) { break; }
            bool ret = cobj->writeValueVectorToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:writeValueVectorToFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_writeValueVectorToFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_isFileExist(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_isFileExist'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:isFileExist");

            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->isFileExist(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:isFileExist");

            if (!ok) { break; }
            bool ret = cobj->isFileExist(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:isFileExist",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_isFileExist'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_writeValueMapToFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_writeValueMapToFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.FileUtils:writeValueMapToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeValueMapToFile");

            if (!ok) { break; }
            std::function<void (bool)> arg2;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->writeValueMapToFile(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.FileUtils:writeValueMapToFile");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.FileUtils:writeValueMapToFile");

            if (!ok) { break; }
            bool ret = cobj->writeValueMapToFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:writeValueMapToFile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_writeValueMapToFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_isDirectoryExist(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_isDirectoryExist'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:isDirectoryExist");

            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->isDirectoryExist(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:isDirectoryExist");

            if (!ok) { break; }
            bool ret = cobj->isDirectoryExist(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:isDirectoryExist",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_isDirectoryExist'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_createDirectory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_createDirectory'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:createDirectory");

            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

            if (!ok) { break; }
            cobj->createDirectory(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:createDirectory");

            if (!ok) { break; }
            bool ret = cobj->createDirectory(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FileUtils:createDirectory",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_createDirectory'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_listFilesAsync(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_listFilesAsync'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::function<void (std::vector<std::string>)> arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:listFilesAsync");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_listFilesAsync'", nullptr);
            return 0;
        }
        cobj->listFilesAsync(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:listFilesAsync",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_listFilesAsync'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_listFilesRecursively(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FileUtils_listFilesRecursively'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        std::vector<std::string>* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FileUtils:listFilesRecursively");

        ok &= luaval_to_object<std::vector<std::string>>(tolua_S, 3, "std::vector<std::string>*",&arg1, "cc.FileUtils:listFilesRecursively");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_listFilesRecursively'", nullptr);
            return 0;
        }
        cobj->listFilesRecursively(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FileUtils:listFilesRecursively",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_listFilesRecursively'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FileUtils_writeBinaryToFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        const void* arg0;
        unsigned int arg1;
        std::string_view arg2;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.FileUtils:writeBinaryToFile");
        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.FileUtils:writeBinaryToFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_writeBinaryToFile'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FileUtils::writeBinaryToFile(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FileUtils:writeBinaryToFile",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_writeBinaryToFile'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FileUtils_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::FileUtils::getInstance();
        object_to_luaval<cocos2d::FileUtils>(tolua_S, "cc.FileUtils",(cocos2d::FileUtils*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FileUtils:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_FileUtils_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FileUtils_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::FileUtils::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.FileUtils:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FileUtils_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_EventCustom_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventCustom* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventCustom:EventCustom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventCustom_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventCustom(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventCustom");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventCustom:EventCustom",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventCustom_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventDispatcher_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventDispatcher* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventDispatcher_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventDispatcher();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventDispatcher");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:EventDispatcher",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventDispatcher_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventDispatcher_dispatchCustomEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventDispatcher* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventDispatcher*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventDispatcher_dispatchCustomEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventDispatcher:dispatchCustomEvent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventDispatcher_dispatchCustomEvent'", nullptr);
            return 0;
        }
        cobj->dispatchCustomEvent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        void* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.EventDispatcher:dispatchCustomEvent");

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventDispatcher_dispatchCustomEvent'", nullptr);
            return 0;
        }
        cobj->dispatchCustomEvent(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventDispatcher:dispatchCustomEvent",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventDispatcher_dispatchCustomEvent'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventFocus_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventFocus* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ui::Widget* arg0;
        cocos2d::ui::Widget* arg1;

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 2, "ccui.Widget",&arg0, "cc.EventFocus:EventFocus");

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 3, "ccui.Widget",&arg1, "cc.EventFocus:EventFocus");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventFocus_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventFocus(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventFocus");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventFocus:EventFocus",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventFocus_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerAcceleration_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerAcceleration* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerAcceleration_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerAcceleration();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerAcceleration");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerAcceleration:EventListenerAcceleration",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerAcceleration_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerAcceleration_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerAcceleration* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventListenerAcceleration",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventListenerAcceleration*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventListenerAcceleration_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Acceleration *, cocos2d::Event *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerAcceleration_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerAcceleration:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerAcceleration_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerFocus_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerFocus* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerFocus_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerFocus();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerFocus");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerFocus:EventListenerFocus",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerFocus_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerKeyboard_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerKeyboard* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerKeyboard_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerKeyboard();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerKeyboard");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerKeyboard:EventListenerKeyboard",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerKeyboard_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EventMouse::MouseEventType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventMouse:EventMouse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventMouse(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventMouse");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:EventMouse",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getPreviousLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getPreviousLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getPreviousLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPreviousLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getPreviousLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getPreviousLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getPreviousLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getPreviousLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getPreviousLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPreviousLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getPreviousLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getPreviousLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getDelta(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getDelta'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getDelta'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDelta();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getDelta",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getDelta'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getStartLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getStartLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getStartLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getStartLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getStartLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getStartLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getStartLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getStartLocation'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getStartLocation();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getStartLocation",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getStartLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventMouse_getLocationInView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventMouse",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventMouse*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_EventMouse_getLocationInView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventMouse_getLocationInView'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLocationInView();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventMouse:getLocationInView",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventMouse_getLocationInView'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerMouse_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerMouse* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerMouse_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerMouse();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerMouse");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerMouse:EventListenerMouse",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerMouse_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerTouchOneByOne_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerTouchOneByOne* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerTouchOneByOne_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerTouchOneByOne();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerTouchOneByOne");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchOneByOne:EventListenerTouchOneByOne",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerTouchOneByOne_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EventListenerTouchAllAtOnce_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerTouchAllAtOnce* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EventListenerTouchAllAtOnce_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EventListenerTouchAllAtOnce();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EventListenerTouchAllAtOnce");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerTouchAllAtOnce:EventListenerTouchAllAtOnce",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EventListenerTouchAllAtOnce_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ActionCamera();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ActionCamera");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:ActionCamera",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_setEye(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_setEye'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ActionCamera:setEye");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ActionCamera:setEye");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ActionCamera:setEye");

            if (!ok) { break; }
            cobj->setEye(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Vec3 arg0;
            ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.ActionCamera:setEye");

            if (!ok) { break; }
            cobj->setEye(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ActionCamera:setEye",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_setEye'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_getEye(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_getEye'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_getEye'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getEye();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:getEye",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_getEye'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_setUp(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_setUp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.ActionCamera:setUp");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_setUp'", nullptr);
            return 0;
        }
        cobj->setUp(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:setUp",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_setUp'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_getCenter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_getCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_getCenter'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCenter();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:getCenter",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_getCenter'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_setCenter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_setCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.ActionCamera:setCenter");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_setCenter'", nullptr);
            return 0;
        }
        cobj->setCenter(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:setCenter",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_setCenter'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ActionCamera_getUp(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ActionCamera_getUp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ActionCamera_getUp'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getUp();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:getUp",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ActionCamera_getUp'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_OrbitCamera_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::OrbitCamera* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_OrbitCamera_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::OrbitCamera();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.OrbitCamera");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OrbitCamera:OrbitCamera",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_OrbitCamera_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CardinalSplineTo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CardinalSplineTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CardinalSplineTo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CardinalSplineTo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CardinalSplineTo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CardinalSplineTo:CardinalSplineTo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CardinalSplineTo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CardinalSplineTo_getPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CardinalSplineTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CardinalSplineTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CardinalSplineTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CardinalSplineTo_getPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CardinalSplineTo_getPoints'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPoints();
        object_to_luaval<cocos2d::PointArray>(tolua_S, "cc.PointArray",(cocos2d::PointArray*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CardinalSplineTo:getPoints",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CardinalSplineTo_getPoints'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CardinalSplineTo_updatePosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CardinalSplineTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CardinalSplineTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CardinalSplineTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CardinalSplineTo_updatePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.CardinalSplineTo:updatePosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CardinalSplineTo_updatePosition'", nullptr);
            return 0;
        }
        cobj->updatePosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CardinalSplineTo:updatePosition",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CardinalSplineTo_updatePosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CardinalSplineTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CardinalSplineTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CardinalSplineTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CardinalSplineTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CardinalSplineTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        double arg0;
        cocos2d::PointArray* arg1;
        double arg2;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.CardinalSplineTo:initWithDuration");

        ok &= luaval_to_object<cocos2d::PointArray>(tolua_S, 3, "cc.PointArray",&arg1, "cc.CardinalSplineTo:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.CardinalSplineTo:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CardinalSplineTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CardinalSplineTo:initWithDuration",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CardinalSplineTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CardinalSplineBy_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CardinalSplineBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CardinalSplineBy_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::CardinalSplineBy();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.CardinalSplineBy");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CardinalSplineBy:CardinalSplineBy",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CardinalSplineBy_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CatmullRomTo_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CatmullRomTo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CatmullRomTo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CatmullRomTo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CatmullRomTo_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::PointArray* arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.CatmullRomTo:initWithDuration");

        ok &= luaval_to_object<cocos2d::PointArray>(tolua_S, 3, "cc.PointArray",&arg1, "cc.CatmullRomTo:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CatmullRomTo_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CatmullRomTo:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CatmullRomTo_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_CatmullRomBy_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::CatmullRomBy* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.CatmullRomBy",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::CatmullRomBy*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_CatmullRomBy_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::PointArray* arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.CatmullRomBy:initWithDuration");

        ok &= luaval_to_object<cocos2d::PointArray>(tolua_S, 3, "cc.PointArray",&arg1, "cc.CatmullRomBy:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_CatmullRomBy_initWithDuration'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithDuration(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.CatmullRomBy:initWithDuration",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_CatmullRomBy_initWithDuration'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseExponentialIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseExponentialIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseExponentialIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseExponentialIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseExponentialIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseExponentialIn:EaseExponentialIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseExponentialIn_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseExponentialOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseExponentialOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseExponentialOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseExponentialOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseExponentialOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseExponentialOut:EaseExponentialOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseExponentialOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseExponentialInOut_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseExponentialInOut* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseExponentialInOut_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseExponentialInOut();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseExponentialInOut");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseExponentialInOut:EaseExponentialInOut",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseExponentialInOut_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_EaseSineIn_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EaseSineIn* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_EaseSineIn_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::EaseSineIn();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.EaseSineIn");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EaseSineIn:EaseSineIn",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_EaseSineIn_constructor'.",&tolua_err);
#endif

    return 0;
}
