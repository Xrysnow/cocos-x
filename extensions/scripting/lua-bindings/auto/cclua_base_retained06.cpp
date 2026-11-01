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

int lua_cc_base_SpotLight_getDirection(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpotLight_getDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpotLight_getDirection'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDirection();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getDirection",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpotLight_getDirection'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpotLight_getDirectionInWorld(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpotLight_getDirectionInWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpotLight_getDirectionInWorld'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDirectionInWorld();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpotLight:getDirectionInWorld",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpotLight_getDirectionInWorld'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpotLight_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SpotLight",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Color3B arg2;
        double arg3;
        double arg4;
        double arg5;
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.SpotLight:create");
        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.SpotLight:create");
        ok &= luaval_to_color3b(tolua_S, 4, &arg2, "cc.SpotLight:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.SpotLight:create");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.SpotLight:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.SpotLight:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpotLight_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::SpotLight::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::SpotLight>(tolua_S, "cc.SpotLight",(cocos2d::SpotLight*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SpotLight:create",argc, 6);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpotLight_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_AmbientLight_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AmbientLight* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AmbientLight_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AmbientLight();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AmbientLight");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AmbientLight:AmbientLight",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AmbientLight_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AmbientLight_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AmbientLight",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Color3B arg0;
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.AmbientLight:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AmbientLight_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::AmbientLight::create(arg0);
        object_to_luaval<cocos2d::AmbientLight>(tolua_S, "cc.AmbientLight",(cocos2d::AmbientLight*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AmbientLight:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AmbientLight_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_RenderState_bindPass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::RenderState* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.RenderState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::RenderState*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_RenderState_bindPass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Pass* arg0;
        cocos2d::MeshCommand* arg1;

        ok &= luaval_to_object<cocos2d::Pass>(tolua_S, 2, "cc.Pass",&arg0, "cc.RenderState:bindPass");

        ok &= luaval_to_object<cocos2d::MeshCommand>(tolua_S, 3, "cc.MeshCommand",&arg1, "cc.RenderState:bindPass");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_RenderState_bindPass'", nullptr);
            return 0;
        }
        cobj->bindPass(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.RenderState:bindPass",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_RenderState_bindPass'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Technique_getPasses(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Technique* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Technique",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Technique*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Technique_getPasses'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Technique_getPasses'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPasses();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:getPasses",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Technique_getPasses'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Technique_getPassByIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Technique* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Technique",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Technique*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Technique_getPassByIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.Technique:getPassByIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Technique_getPassByIndex'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPassByIndex(arg0);
        object_to_luaval<cocos2d::Pass>(tolua_S, "cc.Pass",(cocos2d::Pass*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Technique:getPassByIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Technique_getPassByIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Material_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Material* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Material",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Material*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Material_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 8) 
    {
        cocos2d::MeshCommand* arg0;
        double arg1;
        cocos2d::backend::Buffer* arg2;
        cocos2d::backend::Buffer* arg3;
        cocos2d::backend::PrimitiveType arg4;
        cocos2d::backend::IndexFormat arg5;
        unsigned int arg6;
        cocos2d::Mat4 arg7;

        ok &= luaval_to_object<cocos2d::MeshCommand>(tolua_S, 2, "cc.MeshCommand",&arg0, "cc.Material:draw");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Material:draw");

        ok &= luaval_to_object<cocos2d::backend::Buffer>(tolua_S, 4, "ccb.Buffer",&arg2, "cc.Material:draw");

        ok &= luaval_to_object<cocos2d::backend::Buffer>(tolua_S, 5, "ccb.Buffer",&arg3, "cc.Material:draw");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Material:draw");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Material:draw");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "cc.Material:draw");

        ok &= luaval_to_mat4(tolua_S, 9, &arg7, "cc.Material:draw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Material_draw'", nullptr);
            return 0;
        }
        cobj->draw(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:draw",argc, 8);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Material_draw'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Material_getTechniqueByIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Material* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Material",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Material*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Material_getTechniqueByIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.Material:getTechniqueByIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Material_getTechniqueByIndex'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTechniqueByIndex(arg0);
        object_to_luaval<cocos2d::Technique>(tolua_S, "cc.Technique",(cocos2d::Technique*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getTechniqueByIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Material_getTechniqueByIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Material_getTechniques(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Material* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Material",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Material*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Material_getTechniques'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Material_getTechniques'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTechniques();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Material:getTechniques",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Material_getTechniques'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformPointLightPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformPointLightPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformPointLightPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformPointLightPosition'", nullptr);
            return 0;
        }
        cobj->setUniformPointLightPosition(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformPointLightPosition",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformPointLightPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformDirLightDir(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformDirLightDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformDirLightDir");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformDirLightDir'", nullptr);
            return 0;
        }
        cobj->setUniformDirLightDir(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformDirLightDir",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformDirLightDir'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_getVertexAttributeBinding(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_getVertexAttributeBinding'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_getVertexAttributeBinding'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVertexAttributeBinding();
        object_to_luaval<cocos2d::VertexAttribBinding>(tolua_S, "cc.VertexAttribBinding",(cocos2d::VertexAttribBinding*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:getVertexAttributeBinding",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_getVertexAttributeBinding'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightOuterAngleCos(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightOuterAngleCos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightOuterAngleCos");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightOuterAngleCos'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightOuterAngleCos(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightOuterAngleCos",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightOuterAngleCos'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightDir(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightDir");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightDir'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightDir(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightDir",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightDir'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformMatrixPalette(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformMatrixPalette'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformMatrixPalette");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformMatrixPalette'", nullptr);
            return 0;
        }
        cobj->setUniformMatrixPalette(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformMatrixPalette",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformMatrixPalette'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightRangeInverse(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightRangeInverse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightRangeInverse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightRangeInverse'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightRangeInverse(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightRangeInverse",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightRangeInverse'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 8) 
    {
        cocos2d::MeshCommand* arg0;
        double arg1;
        cocos2d::backend::Buffer* arg2;
        cocos2d::backend::Buffer* arg3;
        cocos2d::backend::PrimitiveType arg4;
        cocos2d::backend::IndexFormat arg5;
        unsigned int arg6;
        cocos2d::Mat4 arg7;

        ok &= luaval_to_object<cocos2d::MeshCommand>(tolua_S, 2, "cc.MeshCommand",&arg0, "cc.Pass:draw");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Pass:draw");

        ok &= luaval_to_object<cocos2d::backend::Buffer>(tolua_S, 4, "ccb.Buffer",&arg2, "cc.Pass:draw");

        ok &= luaval_to_object<cocos2d::backend::Buffer>(tolua_S, 5, "ccb.Buffer",&arg3, "cc.Pass:draw");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.Pass:draw");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.Pass:draw");

        ok &= luaval_to_uint32(tolua_S, 8,&arg6, "cc.Pass:draw");

        ok &= luaval_to_mat4(tolua_S, 9, &arg7, "cc.Pass:draw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_draw'", nullptr);
            return 0;
        }
        cobj->draw(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:draw",argc, 8);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_draw'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformPointLightRangeInverse(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformPointLightRangeInverse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformPointLightRangeInverse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformPointLightRangeInverse'", nullptr);
            return 0;
        }
        cobj->setUniformPointLightRangeInverse(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformPointLightRangeInverse",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformPointLightRangeInverse'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_updateMVPUniform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_updateMVPUniform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Mat4 arg0;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Pass:updateMVPUniform");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_updateMVPUniform'", nullptr);
            return 0;
        }
        cobj->updateMVPUniform(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:updateMVPUniform",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_updateMVPUniform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightColor'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightColor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformAmbientLigthColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformAmbientLigthColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformAmbientLigthColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformAmbientLigthColor'", nullptr);
            return 0;
        }
        cobj->setUniformAmbientLigthColor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformAmbientLigthColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformAmbientLigthColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformDirLightColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformDirLightColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformDirLightColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformDirLightColor'", nullptr);
            return 0;
        }
        cobj->setUniformDirLightColor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformDirLightColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformDirLightColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightPosition'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightPosition(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightPosition",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightPosition'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setVertexAttribBinding(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setVertexAttribBinding'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::VertexAttribBinding* arg0;

        ok &= luaval_to_object<cocos2d::VertexAttribBinding>(tolua_S, 2, "cc.VertexAttribBinding",&arg0, "cc.Pass:setVertexAttribBinding");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setVertexAttribBinding'", nullptr);
            return 0;
        }
        cobj->setVertexAttribBinding(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setVertexAttribBinding",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setVertexAttribBinding'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformSpotLightInnerAngleCos(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformSpotLightInnerAngleCos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformSpotLightInnerAngleCos");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformSpotLightInnerAngleCos'", nullptr);
            return 0;
        }
        cobj->setUniformSpotLightInnerAngleCos(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformSpotLightInnerAngleCos",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformSpotLightInnerAngleCos'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformColor'", nullptr);
            return 0;
        }
        cobj->setUniformColor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Pass_setUniformPointLightColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Pass* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Pass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Pass*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Pass_setUniformPointLightColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const void* arg0;
        unsigned int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.Pass:setUniformPointLightColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Pass_setUniformPointLightColor'", nullptr);
            return 0;
        }
        cobj->setUniformPointLightColor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Pass:setUniformPointLightColor",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Pass_setUniformPointLightColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Renderer();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.Renderer");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:Renderer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_setDepthStencilDesc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_setDepthStencilDesc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::DepthStencilDescriptor arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR DepthStencilDescriptor
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_setDepthStencilDesc'", nullptr);
            return 0;
        }
        cobj->setDepthStencilDesc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setDepthStencilDesc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_setDepthStencilDesc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getViewport(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getViewport'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getViewport'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getViewport();
        #pragma warning NO CONVERSION FROM NATIVE FOR Viewport;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getViewport",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getViewport'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_addCallbackCommand(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_addCallbackCommand'", nullptr);
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
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_addCallbackCommand'", nullptr);
            return 0;
        }
        cobj->addCallbackCommand(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        std::function<void ()> arg0;
        double arg1;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Renderer:addCallbackCommand");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_addCallbackCommand'", nullptr);
            return 0;
        }
        cobj->addCallbackCommand(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:addCallbackCommand",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_addCallbackCommand'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRenderTarget();
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getRenderTarget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_addCommand(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_addCommand'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::RenderCommand* arg0;
            ok &= luaval_to_object<cocos2d::RenderCommand>(tolua_S, 2, "cc.RenderCommand",&arg0, "cc.Renderer:addCommand");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Renderer:addCommand");

            if (!ok) { break; }
            cobj->addCommand(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::RenderCommand* arg0;
            ok &= luaval_to_object<cocos2d::RenderCommand>(tolua_S, 2, "cc.RenderCommand",&arg0, "cc.Renderer:addCommand");

            if (!ok) { break; }
            cobj->addCommand(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Renderer:addCommand",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_addCommand'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_addDrawnVertices(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_addDrawnVertices'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.Renderer:addDrawnVertices");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_addDrawnVertices'", nullptr);
            return 0;
        }
        cobj->addDrawnVertices(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:addDrawnVertices",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_addDrawnVertices'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getDepthStencilDesc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getDepthStencilDesc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getDepthStencilDesc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDepthStencilDesc();
        #pragma warning NO CONVERSION FROM NATIVE FOR DepthStencilDescriptor;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDepthStencilDesc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getDepthStencilDesc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getScissorRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getScissorRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getScissorRect'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getScissorRect();
        #pragma warning NO CONVERSION FROM NATIVE FOR ScissorRect;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getScissorRect",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getScissorRect'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_addDrawnBatches(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_addDrawnBatches'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.Renderer:addDrawnBatches");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_addDrawnBatches'", nullptr);
            return 0;
        }
        cobj->addDrawnBatches(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:addDrawnBatches",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_addDrawnBatches'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_nextCallbackCommand(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_nextCallbackCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_nextCallbackCommand'", nullptr);
            return 0;
        }
        auto&& ret = cobj->nextCallbackCommand();
        object_to_luaval<cocos2d::CallbackCommand>(tolua_S, "cc.CallbackCommand",(cocos2d::CallbackCommand*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:nextCallbackCommand",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_nextCallbackCommand'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_checkVisibility(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_checkVisibility'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Mat4 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Renderer:checkVisibility");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.Renderer:checkVisibility");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_checkVisibility'", nullptr);
            return 0;
        }
        auto&& ret = cobj->checkVisibility(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:checkVisibility",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_checkVisibility'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getNextGroupCommand(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getNextGroupCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getNextGroupCommand'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNextGroupCommand();
        object_to_luaval<cocos2d::GroupCommand>(tolua_S, "cc.GroupCommand",(cocos2d::GroupCommand*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getNextGroupCommand",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getNextGroupCommand'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getClearColor'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getClearColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getClearColor",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getClearColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getOffscreenRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getOffscreenRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getOffscreenRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getOffscreenRenderTarget();
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getOffscreenRenderTarget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getOffscreenRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_clear(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        cocos2d::backend::TargetBufferFlags arg0;
        cocos2d::Color4F arg1;
        double arg2;
        unsigned int arg3;
        double arg4;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Renderer:clear");

        ok &=luaval_to_color4f(tolua_S, 3, &arg1, "cc.Renderer:clear");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.Renderer:clear");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.Renderer:clear");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.Renderer:clear");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_clear'", nullptr);
            return 0;
        }
        cobj->clear(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:clear",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_clear'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_setRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_setRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::RenderTarget* arg0;

        ok &= luaval_to_object<cocos2d::backend::RenderTarget>(tolua_S, 2, "ccb.RenderTarget",&arg0, "cc.Renderer:setRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_setRenderTarget'", nullptr);
            return 0;
        }
        cobj->setRenderTarget(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:setRenderTarget",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_setRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_readPixels(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_readPixels'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::backend::RenderTarget* arg0;
        std::function<void (const cocos2d::backend::PixelBufferDescriptor &)> arg1;

        ok &= luaval_to_object<cocos2d::backend::RenderTarget>(tolua_S, 2, "ccb.RenderTarget",&arg0, "cc.Renderer:readPixels");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_readPixels'", nullptr);
            return 0;
        }
        cobj->readPixels(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:readPixels",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_readPixels'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Renderer_getDefaultRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Renderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Renderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Renderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Renderer_getDefaultRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Renderer_getDefaultRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getDefaultRenderTarget();
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Renderer:getDefaultRenderTarget",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Renderer_getDefaultRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TextureCache_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TextureCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TextureCache_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TextureCache();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TextureCache");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCache:TextureCache",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TextureCache_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TextureCache_addImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TextureCache* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TextureCache",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TextureCache*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TextureCache_addImage'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::Texture2D* ret = cobj->addImage(arg0, arg1);
            object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::Texture2D* ret = cobj->addImage(arg0);
            object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Image* arg0;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 2, "cc.Image",&arg0, "cc.TextureCache:addImage");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::Texture2D* ret = cobj->addImage(arg0, arg1);
            object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Image* arg0;
            ok &= luaval_to_object<cocos2d::Image>(tolua_S, 2, "cc.Image",&arg0, "cc.TextureCache:addImage");

            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::backend::PixelFormat arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.TextureCache:addImage");

            if (!ok) { break; }
            cocos2d::Texture2D* ret = cobj->addImage(arg0, arg1, arg2);
            object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TextureCache:addImage",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TextureCache_addImage'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_getTargetPlatform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_getTargetPlatform'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_getTargetPlatform'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getTargetPlatform();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:getTargetPlatform",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_getTargetPlatform'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_getCurrentLanguage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_getCurrentLanguage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_getCurrentLanguage'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getCurrentLanguage();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:getCurrentLanguage",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_getCurrentLanguage'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_getCurrentLanguageCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_getCurrentLanguageCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_getCurrentLanguageCode'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getCurrentLanguageCode();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:getCurrentLanguageCode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_getCurrentLanguageCode'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_openURL(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_openURL'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Application:openURL");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_openURL'", nullptr);
            return 0;
        }
        auto&& ret = cobj->openURL(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:openURL",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_openURL'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_getVersion'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVersion();
        lua_pushlstring(tolua_S,ret.c_str(),ret.length());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:getVersion",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_getVersion'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_setAnimationInterval(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_Application_setAnimationInterval'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Application:setAnimationInterval");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_setAnimationInterval'", nullptr);
            return 0;
        }
        cobj->setAnimationInterval(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:setAnimationInterval",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_setAnimationInterval'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_Application_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_Application_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Application::getInstance();
        object_to_luaval<cocos2d::Application>(tolua_S, "cc.Application",(cocos2d::Application*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Application:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_Application_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_AnimationCache_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationCache_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AnimationCache();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AnimationCache");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:AnimationCache",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationCache_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationCache_addAnimationsWithDictionary(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimationCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimationCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AnimationCache_addAnimationsWithDictionary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ValueMap arg0;
        std::string_view arg1;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.AnimationCache:addAnimationsWithDictionary");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.AnimationCache:addAnimationsWithDictionary");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationCache_addAnimationsWithDictionary'", nullptr);
            return 0;
        }
        cobj->addAnimationsWithDictionary(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:addAnimationsWithDictionary",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationCache_addAnimationsWithDictionary'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_AnimationCache_addAnimationsWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AnimationCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AnimationCache",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::AnimationCache*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_AnimationCache_addAnimationsWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.AnimationCache:addAnimationsWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_AnimationCache_addAnimationsWithFile'", nullptr);
            return 0;
        }
        cobj->addAnimationsWithFile(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AnimationCache:addAnimationsWithFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_AnimationCache_addAnimationsWithFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::SpriteBatchNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.SpriteBatchNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:SpriteBatchNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteBatchNode:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_removeChildAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_removeChildAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        ssize_t arg0;
        bool arg1;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.SpriteBatchNode:removeChildAtIndex");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SpriteBatchNode:removeChildAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_removeChildAtIndex'", nullptr);
            return 0;
        }
        cobj->removeChildAtIndex(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:removeChildAtIndex",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_removeChildAtIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_initWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_initWithTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteBatchNode:initWithTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_initWithTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTexture(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Texture2D* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteBatchNode:initWithTexture");

        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:initWithTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_initWithTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTexture(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:initWithTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_initWithTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_setTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_setTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextureAtlas* arg0;

        ok &= luaval_to_object<cocos2d::TextureAtlas>(tolua_S, 2, "cc.TextureAtlas",&arg0, "cc.SpriteBatchNode:setTextureAtlas");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_setTextureAtlas'", nullptr);
            return 0;
        }
        cobj->setTextureAtlas(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:setTextureAtlas",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_setTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_reserveCapacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_reserveCapacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize_t(tolua_S, 2, &arg0, "cc.SpriteBatchNode:reserveCapacity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_reserveCapacity'", nullptr);
            return 0;
        }
        cobj->reserveCapacity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:reserveCapacity",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_reserveCapacity'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.SpriteBatchNode:removeAllChildrenWithCleanup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup'", nullptr);
            return 0;
        }
        cobj->removeAllChildrenWithCleanup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:removeAllChildrenWithCleanup",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_insertQuadFromSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_insertQuadFromSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Sprite* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "cc.SpriteBatchNode:insertQuadFromSprite");

        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:insertQuadFromSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_insertQuadFromSprite'", nullptr);
            return 0;
        }
        cobj->insertQuadFromSprite(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:insertQuadFromSprite",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_insertQuadFromSprite'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_initWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteBatchNode:initWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_initWithFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        std::string_view arg0;
        ssize_t arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteBatchNode:initWithFile");

        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:initWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_initWithFile'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithFile(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:initWithFile",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_initWithFile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.SpriteBatchNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_rebuildIndexInOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_rebuildIndexInOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Sprite* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "cc.SpriteBatchNode:rebuildIndexInOrder");

        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:rebuildIndexInOrder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_rebuildIndexInOrder'", nullptr);
            return 0;
        }
        auto&& ret = cobj->rebuildIndexInOrder(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:rebuildIndexInOrder",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_rebuildIndexInOrder'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_getTextureAtlas(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_SpriteBatchNode_getTextureAtlas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_getTextureAtlas'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTextureAtlas();
        object_to_luaval<cocos2d::TextureAtlas>(tolua_S, "cc.TextureAtlas",(cocos2d::TextureAtlas*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:getTextureAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_getTextureAtlas'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_SpriteBatchNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string_view arg0;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteBatchNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::SpriteBatchNode::create(arg0);
        object_to_luaval<cocos2d::SpriteBatchNode>(tolua_S, "cc.SpriteBatchNode",(cocos2d::SpriteBatchNode*)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string_view arg0;
        ssize_t arg1;
        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.SpriteBatchNode:create");
        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::SpriteBatchNode::create(arg0, arg1);
        object_to_luaval<cocos2d::SpriteBatchNode>(tolua_S, "cc.SpriteBatchNode",(cocos2d::SpriteBatchNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SpriteBatchNode:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_SpriteBatchNode_createWithTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Texture2D* arg0;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteBatchNode:createWithTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_createWithTexture'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::SpriteBatchNode::createWithTexture(arg0);
        object_to_luaval<cocos2d::SpriteBatchNode>(tolua_S, "cc.SpriteBatchNode",(cocos2d::SpriteBatchNode*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Texture2D* arg0;
        ssize_t arg1;
        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.SpriteBatchNode:createWithTexture");
        ok &= luaval_to_ssize_t(tolua_S, 3, &arg1, "cc.SpriteBatchNode:createWithTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_SpriteBatchNode_createWithTexture'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::SpriteBatchNode::createWithTexture(arg0, arg1);
        object_to_luaval<cocos2d::SpriteBatchNode>(tolua_S, "cc.SpriteBatchNode",(cocos2d::SpriteBatchNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SpriteBatchNode:createWithTexture",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_SpriteBatchNode_createWithTexture'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_ParallaxNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParallaxNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParallaxNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ParallaxNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ParallaxNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParallaxNode:ParallaxNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParallaxNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParallaxNode_addChild(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParallaxNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParallaxNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParallaxNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParallaxNode_addChild'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocos2d::Node* arg0;
        int arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0, "cc.ParallaxNode:addChild");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ParallaxNode:addChild");

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.ParallaxNode:addChild");

        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.ParallaxNode:addChild");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParallaxNode_addChild'", nullptr);
            return 0;
        }
        cobj->addChild(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParallaxNode:addChild",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParallaxNode_addChild'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParallaxNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParallaxNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParallaxNode*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ParallaxNode:removeAllChildrenWithCleanup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup'", nullptr);
            return 0;
        }
        cobj->removeAllChildrenWithCleanup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParallaxNode:removeAllChildrenWithCleanup",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_ParallaxNode_removeAllChildrenWithCleanup'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXObjectGroup();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXObjectGroup");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:TMXObjectGroup",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_setPositionOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_setPositionOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TMXObjectGroup:setPositionOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_setPositionOffset'", nullptr);
            return 0;
        }
        cobj->setPositionOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:setPositionOffset",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_setPositionOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_getProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_getProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.TMXObjectGroup:getProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_getProperty'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProperty(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:getProperty",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_getProperty'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_getPositionOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_getPositionOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_getPositionOffset'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPositionOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:getPositionOffset",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_getPositionOffset'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_getObject(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_getObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.TMXObjectGroup:getObject");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_getObject'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getObject(arg0);
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:getObject",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_getObject'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_getObjects(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_getObjects'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueVector& ret = cobj->getObjects();
            ccvaluevector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueVector& ret = cobj->getObjects();
            ccvaluevector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXObjectGroup:getObjects",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_getObjects'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_getProperties'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXObjectGroup:getProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_getProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.TMXObjectGroup:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:setProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_setProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXObjectGroup_setObjects(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXObjectGroup* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXObjectGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXObjectGroup*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXObjectGroup_setObjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueVector arg0;

        ok &= luaval_to_ccvaluevector(tolua_S, 2, &arg0, "cc.TMXObjectGroup:setObjects");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXObjectGroup_setObjects'", nullptr);
            return 0;
        }
        cobj->setObjects(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXObjectGroup:setObjects",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXObjectGroup_setObjects'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXLayerInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXLayerInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXLayerInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXLayerInfo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXLayerInfo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayerInfo:TMXLayerInfo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXLayerInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXLayerInfo_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXLayerInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXLayerInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXLayerInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXLayerInfo_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.TMXLayerInfo:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXLayerInfo_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayerInfo:setProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXLayerInfo_setProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXLayerInfo_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXLayerInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXLayerInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXLayerInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXLayerInfo_getProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXLayerInfo_getProperties'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProperties();
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayerInfo:getProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXLayerInfo_getProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXTilesetInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTilesetInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTilesetInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXTilesetInfo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXTilesetInfo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTilesetInfo:TMXTilesetInfo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTilesetInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXTilesetInfo_getRectForGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTilesetInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXTilesetInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXTilesetInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXTilesetInfo_getRectForGID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.TMXTilesetInfo:getRectForGID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTilesetInfo_getRectForGID'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRectForGID(arg0);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTilesetInfo:getRectForGID",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTilesetInfo_getRectForGID'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXMapInfo();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXMapInfo");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:TMXMapInfo",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TMXMapInfo:setTileSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setTileSize'", nullptr);
            return 0;
        }
        cobj->setTileSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setTileSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setObjectGroups'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::TMXObjectGroup *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.TMXMapInfo:setObjectGroups");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setObjectGroups'", nullptr);
            return 0;
        }
        cobj->setObjectGroups(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setObjectGroups",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setObjectGroups'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setLayers(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setLayers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::TMXLayerInfo *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.TMXMapInfo:setLayers");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setLayers'", nullptr);
            return 0;
        }
        cobj->setLayers(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setLayers",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setLayers'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getLayers(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getLayers'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::TMXLayerInfo *>& ret = cobj->getLayers();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::TMXLayerInfo *>& ret = cobj->getLayers();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXMapInfo:getLayers",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getLayers'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getTilesets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getTilesets'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::TMXTilesetInfo *>& ret = cobj->getTilesets();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::TMXTilesetInfo *>& ret = cobj->getTilesets();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXMapInfo:getTilesets",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getTilesets'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_getTileSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTileSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getTileSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getTileProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getTileProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_getTileProperties'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTileProperties();
        ccvaluemapintkey_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getTileProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getTileProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getObjectGroups'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXMapInfo:getObjectGroups",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getObjectGroups'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.TMXMapInfo:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setTileProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setTileProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMapIntKey arg0;

        ok &= luaval_to_ccvaluemapintkey(tolua_S, 2, &arg0, "cc.TMXMapInfo:setTileProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setTileProperties'", nullptr);
            return 0;
        }
        cobj->setTileProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setTileProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setTileProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TMXMapInfo:setMapSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setMapSize'", nullptr);
            return 0;
        }
        cobj->setMapSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setMapSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setMapSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_getMapSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMapSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:getMapSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getMapSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_setTilesets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_setTilesets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::TMXTilesetInfo *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.TMXMapInfo:setTilesets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXMapInfo_setTilesets'", nullptr);
            return 0;
        }
        cobj->setTilesets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXMapInfo:setTilesets",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_setTilesets'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXMapInfo_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXMapInfo* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXMapInfo",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXMapInfo*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXMapInfo_getProperties'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.TMXMapInfo:getProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXMapInfo_getProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TileMapAtlas_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TileMapAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TileMapAtlas_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TileMapAtlas();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TileMapAtlas");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TileMapAtlas:TileMapAtlas",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TileMapAtlas_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TileMapAtlas_getTileAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TileMapAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TileMapAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TileMapAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TileMapAtlas_getTileAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TileMapAtlas:getTileAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TileMapAtlas_getTileAt'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTileAt(arg0);
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TileMapAtlas:getTileAt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TileMapAtlas_getTileAt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TileMapAtlas_setTile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TileMapAtlas* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TileMapAtlas",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TileMapAtlas*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TileMapAtlas_setTile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Color3B arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.TileMapAtlas:setTile");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.TileMapAtlas:setTile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TileMapAtlas_setTile'", nullptr);
            return 0;
        }
        cobj->setTile(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TileMapAtlas:setTile",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TileMapAtlas_setTile'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FastTMXLayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FastTMXLayer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:FastTMXLayer",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getAnimTileCoord(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getAnimTileCoord'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getAnimTileCoord'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getAnimTileCoord();
        object_to_luaval<std::unordered_map<unsigned int, std::vector<cocos2d::Vec2>>>(tolua_S, "std::unordered_map<unsigned int, std::vector<cocos2d::Vec2>>*",(std::unordered_map<unsigned int, std::vector<cocos2d::Vec2>>*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getAnimTileCoord",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getAnimTileCoord'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getPositionAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getPositionAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXLayer:getPositionAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getPositionAt'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPositionAt(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getPositionAt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getPositionAt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getLayerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getLayerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getLayerSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getLayerSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getLayerSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getLayerSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_setMapTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_setMapTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXLayer:setMapTileSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_setMapTileSize'", nullptr);
            return 0;
        }
        cobj->setMapTileSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setMapTileSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_setMapTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.FastTMXLayer:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_setProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_removeTileAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_removeTileAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXLayer:removeTileAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_removeTileAt'", nullptr);
            return 0;
        }
        cobj->removeTileAt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:removeTileAt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_removeTileAt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getProperties'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FastTMXLayer:getProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_setupTileSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_setupTileSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Sprite* arg0;
        cocos2d::Vec2 arg1;
        unsigned int arg2;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "cc.FastTMXLayer:setupTileSprite");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FastTMXLayer:setupTileSprite");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.FastTMXLayer:setupTileSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_setupTileSprite'", nullptr);
            return 0;
        }
        cobj->setupTileSprite(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setupTileSprite",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_setupTileSprite'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_setTileGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_setTileGID'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.FastTMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FastTMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::TMXTileFlags_ arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.FastTMXLayer:setTileGID");

            if (!ok) { break; }
            cobj->setTileGID(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.FastTMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.FastTMXLayer:setTileGID");

            if (!ok) { break; }
            cobj->setTileGID(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FastTMXLayer:setTileGID",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_setTileGID'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getMapTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getMapTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getMapTileSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMapTileSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getMapTileSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getMapTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FastTMXLayer:getProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getProperty'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProperty(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getProperty",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getProperty'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_setLayerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_setLayerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXLayer:setLayerSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_setLayerSize'", nullptr);
            return 0;
        }
        cobj->setLayerSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:setLayerSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_setLayerSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXLayer_getTileAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXLayer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXLayer_getTileAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXLayer:getTileAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXLayer_getTileAt'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTileAt(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXLayer:getTileAt",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXLayer_getTileAt'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXTileAnimTask_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTileAnimTask* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::FastTMXLayer* arg0;
        cocos2d::TMXTileAnimInfo* arg1;
        cocos2d::Vec2 arg2;

        ok &= luaval_to_object<cocos2d::FastTMXLayer>(tolua_S, 2, "cc.FastTMXLayer",&arg0, "cc.TMXTileAnimTask:TMXTileAnimTask");

        #pragma warning NO CONVERSION TO NATIVE FOR TMXTileAnimInfo*
		ok = false;

        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.TMXTileAnimTask:TMXTileAnimTask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTileAnimTask_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXTileAnimTask(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXTileAnimTask");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimTask:TMXTileAnimTask",argc, 3);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTileAnimTask_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXTileAnimTask_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TMXTileAnimTask",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::FastTMXLayer* arg0;
        cocos2d::TMXTileAnimInfo* arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_object<cocos2d::FastTMXLayer>(tolua_S, 2, "cc.FastTMXLayer",&arg0, "cc.TMXTileAnimTask:create");
        #pragma warning NO CONVERSION TO NATIVE FOR TMXTileAnimInfo*
		ok = false;
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.TMXTileAnimTask:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTileAnimTask_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::TMXTileAnimTask::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::TMXTileAnimTask>(tolua_S, "cc.TMXTileAnimTask",(cocos2d::TMXTileAnimTask*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TMXTileAnimTask:create",argc, 3);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTileAnimTask_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_base_TMXTileAnimManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTileAnimManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::FastTMXLayer* arg0;

        ok &= luaval_to_object<cocos2d::FastTMXLayer>(tolua_S, 2, "cc.FastTMXLayer",&arg0, "cc.TMXTileAnimManager:TMXTileAnimManager");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTileAnimManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TMXTileAnimManager(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TMXTileAnimManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimManager:TMXTileAnimManager",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTileAnimManager_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_TMXTileAnimManager_getTasks(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTileAnimManager* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXTileAnimManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TMXTileAnimManager*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_TMXTileAnimManager_getTasks'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_TMXTileAnimManager_getTasks'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTasks();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTileAnimManager:getTasks",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_TMXTileAnimManager_getTasks'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::FastTMXTiledMap();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.FastTMXTiledMap");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:FastTMXTiledMap",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_setObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_setObjectGroups'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::TMXObjectGroup *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.FastTMXTiledMap:setObjectGroups");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_setObjectGroups'", nullptr);
            return 0;
        }
        cobj->setObjectGroups(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setObjectGroups",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_setObjectGroups'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.FastTMXTiledMap:getProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_getProperty'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProperty(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getProperty",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getProperty'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_setMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_setMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXTiledMap:setMapSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_setMapSize'", nullptr);
            return 0;
        }
        cobj->setMapSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setMapSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_setMapSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getObjectGroups'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.FastTMXTiledMap:getObjectGroups",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getObjectGroups'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_getTileSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTileSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getTileSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_getMapSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMapSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getMapSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getMapSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_getProperties'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProperties();
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getProperties",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_getPropertiesForGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_getPropertiesForGID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.FastTMXTiledMap:getPropertiesForGID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_getPropertiesForGID'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getPropertiesForGID(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:getPropertiesForGID",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_getPropertiesForGID'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_setTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_setTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.FastTMXTiledMap:setTileSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_setTileSize'", nullptr);
            return 0;
        }
        cobj->setTileSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setTileSize",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_setTileSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_FastTMXTiledMap_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FastTMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FastTMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FastTMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_FastTMXTiledMap_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.FastTMXTiledMap:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_FastTMXTiledMap_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.FastTMXTiledMap:setProperties",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_FastTMXTiledMap_setProperties'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MotionStreak3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.MotionStreak3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:MotionStreak3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.MotionStreak3D:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_getTexture'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:getTexture",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_getTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_tintWithColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_tintWithColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color3B arg0;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.MotionStreak3D:tintWithColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_tintWithColor'", nullptr);
            return 0;
        }
        cobj->tintWithColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:tintWithColor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_tintWithColor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_getSweepAxis(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_getSweepAxis'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_getSweepAxis'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSweepAxis();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:getSweepAxis",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_getSweepAxis'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.MotionStreak3D:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_initWithFade(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_initWithFade'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 5) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            cocos2d::Texture2D* arg4;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 6, "cc.Texture2D",&arg4, "cc.MotionStreak3D:initWithFade");

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
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            std::string_view arg4;
            ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.MotionStreak3D:initWithFade");

            if (!ok) { break; }
            bool ret = cobj->initWithFade(arg0, arg1, arg2, arg3, arg4);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MotionStreak3D:initWithFade",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_initWithFade'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_setSweepAxis(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MotionStreak3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MotionStreak3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_base_MotionStreak3D_setSweepAxis'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.MotionStreak3D:setSweepAxis");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_base_MotionStreak3D_setSweepAxis'", nullptr);
            return 0;
        }
        cobj->setSweepAxis(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MotionStreak3D:setSweepAxis",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_setSweepAxis'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_base_MotionStreak3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MotionStreak3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 5)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            cocos2d::Texture2D* arg4;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 6, "cc.Texture2D",&arg4, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            cocos2d::MotionStreak3D* ret = cocos2d::MotionStreak3D::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::MotionStreak3D>(tolua_S, "cc.MotionStreak3D",(cocos2d::MotionStreak3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            cocos2d::Color3B arg3;
            ok &= luaval_to_color3b(tolua_S, 5, &arg3, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            std::string_view arg4;
            ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.MotionStreak3D:create");
            if (!ok) { break; }
            cocos2d::MotionStreak3D* ret = cocos2d::MotionStreak3D::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::MotionStreak3D>(tolua_S, "cc.MotionStreak3D",(cocos2d::MotionStreak3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.MotionStreak3D:create",argc, 5);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_base_MotionStreak3D_create'.",&tolua_err);
#endif
    return 0;
}
