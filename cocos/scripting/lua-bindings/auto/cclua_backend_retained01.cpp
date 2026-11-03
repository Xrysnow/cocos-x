#include "scripting/lua-bindings/auto/cclua_backend_auto.hpp"
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/VertexLayout.h"
#include "renderer/backend/Device.h"
#include "renderer/backend/RenderTarget.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"


int lua_cc_backend_Program_getVertexLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Program_getVertexLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Program_getVertexLayout'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getVertexLayout();
        object_to_luaval<cocos2d::backend::VertexLayout>(tolua_S, "ccb.VertexLayout",(cocos2d::backend::VertexLayout*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getVertexLayout",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Program_getVertexLayout'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Program_getUniformLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Program_getUniformLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Uniform arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getUniformLocation");

            if (!ok) { break; }
            cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
            uniformLocation_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.Program:getUniformLocation");

            if (!ok) { break; }
            cocos2d::backend::UniformLocation ret = cobj->getUniformLocation(arg0);
            uniformLocation_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.Program:getUniformLocation",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Program_getUniformLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Program_getActiveAttributes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Program_getActiveAttributes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Program_getActiveAttributes'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getActiveAttributes();
        program_activeattrs_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Program:getActiveAttributes",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Program_getActiveAttributes'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Program_getAttributeLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Program* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Program",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::Program*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Program_getAttributeLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Attribute arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Program:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.Program:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.Program:getAttributeLocation",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Program_getAttributeLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_VertexLayout_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_VertexLayout_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::backend::VertexLayout();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccb.VertexLayout");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:VertexLayout",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_VertexLayout_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_VertexLayout_setAttribute(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_VertexLayout_setAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        std::string_view arg0;
        unsigned int arg1;
        cocos2d::backend::VertexFormat arg2;
        unsigned int arg3;
        bool arg4;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.VertexLayout:setAttribute");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccb.VertexLayout:setAttribute");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_VertexLayout_setAttribute'", nullptr);
            return 0;
        }
        cobj->setAttribute(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:setAttribute",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_VertexLayout_setAttribute'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_VertexLayout_setStride(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::VertexLayout* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.VertexLayout",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::VertexLayout*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_VertexLayout_setStride'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.VertexLayout:setStride");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_VertexLayout_setStride'", nullptr);
            return 0;
        }
        cobj->setStride(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.VertexLayout:setStride",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_VertexLayout_setStride'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::Program* arg0;

        ok &= luaval_to_object<cocos2d::backend::Program>(tolua_S, 2, "ccb.Program",&arg0, "ccb.ProgramState:ProgramState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_ProgramState_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::backend::ProgramState(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccb.ProgramState");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:ProgramState",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_ProgramState_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            cocos2d::backend::UniformLocation arg0;
            ok &= luaval_to_uniformLocation(tolua_S, 2, arg0, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            cocos2d::backend::TextureBackend* arg2;
            ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 4, "ccb.TextureBackend",&arg2, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::backend::TextureBackend* arg0;
            ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 2, "ccb.TextureBackend",&arg0, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::backend::UniformLocation arg0;
            ok &= luaval_to_uniformLocation(tolua_S, 2, arg0, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            cocos2d::backend::TextureBackend* arg3;
            ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 5, "ccb.TextureBackend",&arg3, "ccb.ProgramState:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.ProgramState:setTexture",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_getAttributeLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_ProgramState_getAttributeLocation'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::backend::Attribute arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.ProgramState:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.ProgramState:getAttributeLocation");

            if (!ok) { break; }
            int ret = cobj->getAttributeLocation(arg0);
            tolua_pushnumber(tolua_S,(lua_Number)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccb.ProgramState:getAttributeLocation",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_getAttributeLocation'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_setVertexLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_ProgramState_setVertexLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::VertexLayout arg0;

        ok &= luaval_to_vertexLayout(tolua_S, 2, arg0, "ccb.ProgramState:setVertexLayout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_ProgramState_setVertexLayout'", nullptr);
            return 0;
        }
        cobj->setVertexLayout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setVertexLayout",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_setVertexLayout'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_setVertexAttrib(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_ProgramState_setVertexAttrib'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        std::string_view arg0;
        unsigned int arg1;
        cocos2d::backend::VertexFormat arg2;
        unsigned int arg3;
        bool arg4;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "ccb.ProgramState:setVertexAttrib");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.ProgramState:setVertexAttrib");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccb.ProgramState:setVertexAttrib");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.ProgramState:setVertexAttrib");

        ok &= luaval_to_boolean(tolua_S, 6,&arg4, "ccb.ProgramState:setVertexAttrib");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_ProgramState_setVertexAttrib'", nullptr);
            return 0;
        }
        cobj->setVertexAttrib(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:setVertexAttrib",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_setVertexAttrib'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_ProgramState_validateSharedVertexLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::ProgramState* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.ProgramState",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::ProgramState*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_ProgramState_validateSharedVertexLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::backend::Program *)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_ProgramState_validateSharedVertexLayout'", nullptr);
            return 0;
        }
        cobj->validateSharedVertexLayout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.ProgramState:validateSharedVertexLayout",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_ProgramState_validateSharedVertexLayout'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_TextureBackend_updateSamplerDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_TextureBackend_updateSamplerDescriptor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::SamplerDescriptor arg0;

        ok &= luaval_to_samplerDescriptor(tolua_S, 2, arg0, "ccb.TextureBackend:updateSamplerDescriptor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_TextureBackend_updateSamplerDescriptor'", nullptr);
            return 0;
        }
        cobj->updateSamplerDescriptor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:updateSamplerDescriptor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_TextureBackend_updateSamplerDescriptor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_TextureBackend_updateTextureDescriptor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_TextureBackend_updateTextureDescriptor'", nullptr);
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
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_TextureBackend_updateTextureDescriptor'", nullptr);
            return 0;
        }
        cobj->updateTextureDescriptor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::backend::TextureDescriptor arg0;
        int arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR TextureDescriptor
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccb.TextureBackend:updateTextureDescriptor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_TextureBackend_updateTextureDescriptor'", nullptr);
            return 0;
        }
        cobj->updateTextureDescriptor(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureBackend:updateTextureDescriptor",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_TextureBackend_updateTextureDescriptor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_getHeight'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:getHeight",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_getHeight'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_getWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_getWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_getWidth'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:getWidth",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_getWidth'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_updateData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_updateData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateData'", nullptr);
            return 0;
        }
        cobj->updateData(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 5) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        int arg4;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateData");

        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "ccb.Texture2DBackend:updateData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateData'", nullptr);
            return 0;
        }
        cobj->updateData(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateData",argc, 4);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_updateData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_updateCompressedData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_updateCompressedData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateCompressedData'", nullptr);
            return 0;
        }
        cobj->updateCompressedData(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 6) 
    {
        unsigned char* arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        int arg5;

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedData");

        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "ccb.Texture2DBackend:updateCompressedData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateCompressedData'", nullptr);
            return 0;
        }
        cobj->updateCompressedData(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateCompressedData",argc, 5);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_updateCompressedData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_updateSubData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_updateSubData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned char* arg5;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateSubData'", nullptr);
            return 0;
        }
        cobj->updateSubData(arg0, arg1, arg2, arg3, arg4, arg5);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 7) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned char* arg5;
        int arg6;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 8,(int *)&arg6, "ccb.Texture2DBackend:updateSubData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateSubData'", nullptr);
            return 0;
        }
        cobj->updateSubData(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateSubData",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_updateSubData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Texture2DBackend_updateCompressedSubData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Texture2DBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Texture2DBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Texture2DBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Texture2DBackend_updateCompressedSubData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 7) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned int arg5;
        unsigned char* arg6;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 7,&arg5, "ccb.Texture2DBackend:updateCompressedSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateCompressedSubData'", nullptr);
            return 0;
        }
        cobj->updateCompressedSubData(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 8) 
    {
        unsigned int arg0;
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned int arg5;
        unsigned char* arg6;
        int arg7;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "ccb.Texture2DBackend:updateCompressedSubData");

        ok &= luaval_to_uint32(tolua_S, 7,&arg5, "ccb.Texture2DBackend:updateCompressedSubData");

        #pragma warning NO CONVERSION TO NATIVE FOR unsigned char*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "ccb.Texture2DBackend:updateCompressedSubData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Texture2DBackend_updateCompressedSubData'", nullptr);
            return 0;
        }
        cobj->updateCompressedSubData(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Texture2DBackend:updateCompressedSubData",argc, 7);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Texture2DBackend_updateCompressedSubData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_TextureCubemapBackend_updateFaceData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::TextureCubemapBackend* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.TextureCubemapBackend",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::TextureCubemapBackend*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_TextureCubemapBackend_updateFaceData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::backend::TextureCubeFace arg0;
        void* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.TextureCubemapBackend:updateFaceData");

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_TextureCubemapBackend_updateFaceData'", nullptr);
            return 0;
        }
        cobj->updateFaceData(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::backend::TextureCubeFace arg0;
        void* arg1;
        int arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.TextureCubemapBackend:updateFaceData");

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccb.TextureCubemapBackend:updateFaceData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_TextureCubemapBackend_updateFaceData'", nullptr);
            return 0;
        }
        cobj->updateFaceData(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.TextureCubemapBackend:updateFaceData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_TextureCubemapBackend_updateFaceData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Device_newDefaultRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Device* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Device",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Device*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Device_newDefaultRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::TargetBufferFlags arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Device:newDefaultRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newDefaultRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newDefaultRenderTarget(arg0);
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Device:newDefaultRenderTarget",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Device_newDefaultRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Device_newRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Device* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Device",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Device*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Device_newRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::backend::TargetBufferFlags arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Device:newRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newRenderTarget(arg0);
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::backend::TargetBufferFlags arg0;
        cocos2d::backend::TextureBackend* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 3, "ccb.TextureBackend",&arg1, "ccb.Device:newRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newRenderTarget(arg0, arg1);
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    if (argc == 3) 
    {
        cocos2d::backend::TargetBufferFlags arg0;
        cocos2d::backend::TextureBackend* arg1;
        cocos2d::backend::TextureBackend* arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 3, "ccb.TextureBackend",&arg1, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 4, "ccb.TextureBackend",&arg2, "ccb.Device:newRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newRenderTarget(arg0, arg1, arg2);
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    if (argc == 4) 
    {
        cocos2d::backend::TargetBufferFlags arg0;
        cocos2d::backend::TextureBackend* arg1;
        cocos2d::backend::TextureBackend* arg2;
        cocos2d::backend::TextureBackend* arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 3, "ccb.TextureBackend",&arg1, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 4, "ccb.TextureBackend",&arg2, "ccb.Device:newRenderTarget");

        ok &= luaval_to_object<cocos2d::backend::TextureBackend>(tolua_S, 5, "ccb.TextureBackend",&arg3, "ccb.Device:newRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newRenderTarget'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newRenderTarget(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::backend::RenderTarget>(tolua_S, "ccb.RenderTarget",(cocos2d::backend::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Device:newRenderTarget",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Device_newRenderTarget'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_backend_Device_newDepthStencilState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::backend::Device* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccb.Device",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::backend::Device*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_backend_Device_newDepthStencilState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_backend_Device_newDepthStencilState'", nullptr);
            return 0;
        }
        auto&& ret = cobj->newDepthStencilState();
        object_to_luaval<cocos2d::backend::DepthStencilState>(tolua_S, "ccb.DepthStencilState",(cocos2d::backend::DepthStencilState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccb.Device:newDepthStencilState",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_backend_Device_newDepthStencilState'.",&tolua_err);
#endif

    return 0;
}
