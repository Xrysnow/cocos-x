#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "physics3d/CCPhysics3D.h"

int lua_cc_physics3d_Physics3DShape_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DShape* cobj = nullptr;
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
        cobj = new cocos2d::Physics3DShape();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
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

int lua_cc_physics3d_Physics3DShape_getbtShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DShape* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DShape*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DShape_getbtShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DShape_getbtShape'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getbtShape();
        object_to_luaval<btCollisionShape>(tolua_S, "btCollisionShape",(btCollisionShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DShape:getbtShape",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DShape_getbtShape'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DShape_createConvexHull(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Physics3DShape",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const cocos2d::Vec3* arg0;
        int arg1;
        ok &= luaval_to_object<const cocos2d::Vec3>(tolua_S, 2, "cc.Vec3",&arg0, "cc.Physics3DShape:createConvexHull");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Physics3DShape:createConvexHull");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DShape_createConvexHull'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Physics3DShape::createConvexHull(arg0, arg1);
        object_to_luaval<cocos2d::Physics3DShape>(tolua_S, "cc.Physics3DShape",(cocos2d::Physics3DShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Physics3DShape:createConvexHull",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DShape_createConvexHull'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_physics3d_Physics3DObject_setUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DObject* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DObject*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DObject_setUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DObject_setUserData'", nullptr);
            return 0;
        }
        cobj->setUserData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DObject:setUserData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DObject_setUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DObject_getUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DObject* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DObject*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DObject_getUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DObject_getUserData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getUserData();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DObject:getUserData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DObject_getUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DObject_getCollisionCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DObject* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DObject",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DObject*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DObject_getCollisionCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DObject_getCollisionCallback'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCollisionCallback();
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DObject:getCollisionCallback",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DObject_getCollisionCallback'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DRigidBody_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DRigidBody* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DRigidBody_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3DRigidBody();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DRigidBody");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DRigidBody:Physics3DRigidBody",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DRigidBody_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DRigidBody_getRigidBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DRigidBody* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DRigidBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DRigidBody*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DRigidBody_getRigidBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DRigidBody_getRigidBody'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRigidBody();
        object_to_luaval<btRigidBody>(tolua_S, "btRigidBody",(btRigidBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DRigidBody:getRigidBody",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DRigidBody_getRigidBody'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DComponent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DComponent* cobj = nullptr;
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
        cobj = new cocos2d::Physics3DComponent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
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

int lua_cc_physics3d_PhysicsMeshRenderer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsMeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_PhysicsMeshRenderer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::PhysicsMeshRenderer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.PhysicsMeshRenderer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsMeshRenderer:PhysicsMeshRenderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_PhysicsMeshRenderer_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DWorld_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DWorld* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DWorld_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3DWorld();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DWorld");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DWorld:Physics3DWorld",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DWorld_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DConstraint_getUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DConstraint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DConstraint*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DConstraint_getUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DConstraint_getUserData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getUserData();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DConstraint:getUserData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DConstraint_getUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DConstraint_setUserData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DConstraint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DConstraint*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DConstraint_setUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DConstraint_setUserData'", nullptr);
            return 0;
        }
        cobj->setUserData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DConstraint:setUserData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DConstraint_setUserData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DConstraint_getbtContraint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Physics3DConstraint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Physics3DConstraint*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_physics3d_Physics3DConstraint_getbtContraint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DConstraint_getbtContraint'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getbtContraint();
        object_to_luaval<btTypedConstraint>(tolua_S, "btTypedConstraint",(btTypedConstraint*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DConstraint:getbtContraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DConstraint_getbtContraint'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DPointToPointConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DPointToPointConstraint* cobj = nullptr;
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
        cobj = new cocos2d::Physics3DPointToPointConstraint();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
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

int lua_cc_physics3d_Physics3DHingeConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DHingeConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DHingeConstraint_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3DHingeConstraint();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DHingeConstraint");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DHingeConstraint:Physics3DHingeConstraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DHingeConstraint_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DSliderConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DSliderConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DSliderConstraint_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3DSliderConstraint();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DSliderConstraint");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DSliderConstraint:Physics3DSliderConstraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DSliderConstraint_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3DConeTwistConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3DConeTwistConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3DConeTwistConstraint_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3DConeTwistConstraint();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3DConeTwistConstraint");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3DConeTwistConstraint:Physics3DConeTwistConstraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3DConeTwistConstraint_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_physics3d_Physics3D6DofConstraint_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Physics3D6DofConstraint* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_physics3d_Physics3D6DofConstraint_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Physics3D6DofConstraint();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Physics3D6DofConstraint");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Physics3D6DofConstraint:Physics3D6DofConstraint",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_physics3d_Physics3D6DofConstraint_constructor'.",&tolua_err);
#endif

    return 0;
}

int register_all_cc_physics3d_retained(lua_State* L)
{
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DShape");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DShape_constructor);
        tolua_function(L, "getbtShape", lua_cc_physics3d_Physics3DShape_getbtShape);
        tolua_function(L, "createConvexHull", lua_cc_physics3d_Physics3DShape_createConvexHull);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DObject");
    if (lua_istable(L, -1)) {
        tolua_function(L, "setUserData", lua_cc_physics3d_Physics3DObject_setUserData);
        tolua_function(L, "getUserData", lua_cc_physics3d_Physics3DObject_getUserData);
        tolua_function(L, "getCollisionCallback", lua_cc_physics3d_Physics3DObject_getCollisionCallback);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DRigidBody");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DRigidBody_constructor);
        tolua_function(L, "getRigidBody", lua_cc_physics3d_Physics3DRigidBody_getRigidBody);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DComponent");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DComponent_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.PhysicsMeshRenderer");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_PhysicsMeshRenderer_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DWorld");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DWorld_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "getUserData", lua_cc_physics3d_Physics3DConstraint_getUserData);
        tolua_function(L, "setUserData", lua_cc_physics3d_Physics3DConstraint_setUserData);
        tolua_function(L, "getbtContraint", lua_cc_physics3d_Physics3DConstraint_getbtContraint);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DPointToPointConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DPointToPointConstraint_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DHingeConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DHingeConstraint_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DSliderConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DSliderConstraint_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3DConeTwistConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3DConeTwistConstraint_constructor);
    }
    lua_pop(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, "cc.Physics3D6DofConstraint");
    if (lua_istable(L, -1)) {
        tolua_function(L, "new", lua_cc_physics3d_Physics3D6DofConstraint_constructor);
    }
    lua_pop(L, 1);
    return 0;
}
#endif
