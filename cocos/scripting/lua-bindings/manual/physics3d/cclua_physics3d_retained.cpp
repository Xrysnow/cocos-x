#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "physics3d/Physics3D.h"

#include <utility>

int lua_cc_physics3d_Physics3DShape_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cc::Physics3DShape* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DShape_constructor'", nullptr);
            return 0;
        }
        auto owner = cc::IntrusivePtr{new cc::Physics3DShape()};
        cobj = cc::transferToAutoreleasePool(std::move(owner));
        int ID =  (int)cobj->getScriptObjectID() ;
        int* luaID =  &cobj->getScriptIdentity().luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DShape");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DShape:Physics3DShape",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DShape_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DComponent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cc::Physics3DComponent* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DComponent_constructor'", nullptr);
            return 0;
        }
        auto owner = cc::IntrusivePtr{new cc::Physics3DComponent()};
        cobj = cc::transferToAutoreleasePool(std::move(owner));
        int ID =  (int)cobj->getScriptObjectID() ;
        int* luaID =  &cobj->getScriptIdentity().luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DComponent");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DComponent:Physics3DComponent",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DComponent_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DPointToPointConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cc::Physics3DPointToPointConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DPointToPointConstraint_constructor'", nullptr);
            return 0;
        }
        auto owner = cc::IntrusivePtr{new cc::Physics3DPointToPointConstraint()};
        cobj = cc::transferToAutoreleasePool(std::move(owner));
        int ID =  (int)cobj->getScriptObjectID() ;
        int* luaID =  &cobj->getScriptIdentity().luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DPointToPointConstraint");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DPointToPointConstraint:Physics3DPointToPointConstraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DPointToPointConstraint_constructor'.",&tolua_err);
#endif

    return 0;
}

int register_all_cc_physics3d_retained(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DShape");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DShape_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DComponent");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DComponent_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DPointToPointConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DPointToPointConstraint_constructor);
    }
    lua_pop(L, 1);
    return 0;
}
#endif
