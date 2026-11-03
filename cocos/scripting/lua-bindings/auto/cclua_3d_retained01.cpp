#include "scripting/lua-bindings/auto/cclua_3d_auto.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cc_3d_Animation3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Animation3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Animation3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Animation3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation3D:Animation3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Animation3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Animation3D_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animation3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animation3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animation3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Animation3D_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Animation3DData arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR Animation3DData
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Animation3D_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animation3D:init",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Animation3D_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Animate3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Animate3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Animate3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Animate3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:Animate3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Animate3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Animate3D_setKeyFrameUserInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Animate3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Animate3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Animate3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Animate3D_setKeyFrameUserInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        cocos2d::ValueMap arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Animate3D:setKeyFrameUserInfo");

        ok &= luaval_to_ccvaluemap(tolua_S, 3, &arg1, "cc.Animate3D:setKeyFrameUserInfo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Animate3D_setKeyFrameUserInfo'", nullptr);
            return 0;
        }
        cobj->setKeyFrameUserInfo(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Animate3D:setKeyFrameUserInfo",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Animate3D_setKeyFrameUserInfo'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_TextureCube_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TextureCube* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_TextureCube_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::TextureCube();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TextureCube");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCube:TextureCube",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_TextureCube_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_TextureCube_getImagePaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TextureCube* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TextureCube",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TextureCube*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_TextureCube_getImagePaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_TextureCube_getImagePaths'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getImagePaths();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCube:getImagePaths",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_TextureCube_getImagePaths'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_TextureCube_setTexParameters(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TextureCube* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TextureCube",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::TextureCube*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_TextureCube_setTexParameters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D::TexParams arg0;

        ok &= luaval_to_texparams(tolua_S, 2, &arg0, "cc.TextureCube:setTexParameters");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_TextureCube_setTexParameters'", nullptr);
            return 0;
        }
        cobj->setTexParameters(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TextureCube:setTexParameters",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_TextureCube_setTexParameters'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_AttachNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::AttachNode* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_AttachNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::AttachNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AttachNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AttachNode:AttachNode",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_AttachNode_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_AttachNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AttachNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Bone3D* arg0;
        ok &= luaval_to_object<cocos2d::Bone3D>(tolua_S, 2, "cc.Bone3D",&arg0, "cc.AttachNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_AttachNode_create'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::AttachNode::create(arg0);
        object_to_luaval<cocos2d::AttachNode>(tolua_S, "cc.AttachNode",(cocos2d::AttachNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AttachNode:create",argc, 1);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_AttachNode_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_3d_BillBoard_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillBoard* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_BillBoard_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::BillBoard();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BillBoard");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillBoard:BillBoard",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_BillBoard_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_BillBoard_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.BillBoard",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard::Mode arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create();
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::BillBoard::Mode arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard::Mode arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.BillBoard:create");
            if (!ok) { break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::BillBoard>(tolua_S, "cc.BillBoard",(cocos2d::BillBoard*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.BillBoard:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_BillBoard_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_3d_Mesh_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Mesh();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Mesh");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:Mesh",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_getMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_getMaterial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_getMaterial'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMaterial();
        object_to_luaval<cocos2d::Material>(tolua_S, "cc.Material",(cocos2d::Material*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getMaterial",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_getMaterial'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_setMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_setMaterial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Material* arg0;

        ok &= luaval_to_object<cocos2d::Material>(tolua_S, 2, "cc.Material",&arg0, "cc.Mesh:setMaterial");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_setMaterial'", nullptr);
            return 0;
        }
        cobj->setMaterial(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setMaterial",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_setMaterial'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_getMeshVertexAttribute(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_getMeshVertexAttribute'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Mesh:getMeshVertexAttribute");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_getMeshVertexAttribute'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMeshVertexAttribute(arg0);
        mesh_vertex_attrib_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getMeshVertexAttribute",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_getMeshVertexAttribute'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 8) 
    {
        cocos2d::Renderer* arg0;
        double arg1;
        cocos2d::Mat4 arg2;
        unsigned int arg3;
        unsigned int arg4;
        cocos2d::Vec4 arg5;
        bool arg6;
        bool arg7;

        ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.Mesh:draw");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.Mesh:draw");

        ok &= luaval_to_mat4(tolua_S, 4, &arg2, "cc.Mesh:draw");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "cc.Mesh:draw");

        ok &= luaval_to_uint32(tolua_S, 6,&arg4, "cc.Mesh:draw");

        ok &= luaval_to_vec4(tolua_S, 7, &arg5, "cc.Mesh:draw");

        ok &= luaval_to_boolean(tolua_S, 8,&arg6, "cc.Mesh:draw");

        ok &= luaval_to_boolean(tolua_S, 9,&arg7, "cc.Mesh:draw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_draw'", nullptr);
            return 0;
        }
        cobj->draw(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:draw",argc, 8);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_draw'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_setMeshIndexData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_setMeshIndexData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::MeshIndexData* arg0;

        ok &= luaval_to_object<cocos2d::MeshIndexData>(tolua_S, 2, "cc.MeshIndexData",&arg0, "cc.Mesh:setMeshIndexData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_setMeshIndexData'", nullptr);
            return 0;
        }
        cobj->setMeshIndexData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setMeshIndexData",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_setMeshIndexData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_getProgramState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_getProgramState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_getProgramState'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getProgramState();
        object_to_luaval<cocos2d::backend::ProgramState>(tolua_S, "ccb.ProgramState",(cocos2d::backend::ProgramState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:getProgramState",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_getProgramState'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.Mesh:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Mesh_setSkin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Mesh* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Mesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Mesh*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Mesh_setSkin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::MeshSkin* arg0;

        ok &= luaval_to_object<cocos2d::MeshSkin>(tolua_S, 2, "cc.MeshSkin",&arg0, "cc.Mesh:setSkin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Mesh_setSkin'", nullptr);
            return 0;
        }
        cobj->setSkin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Mesh:setSkin",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Mesh_setSkin'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Skeleton3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Skeleton3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:Skeleton3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_addBone(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skeleton3D_addBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Bone3D* arg0;

        ok &= luaval_to_object<cocos2d::Bone3D>(tolua_S, 2, "cc.Bone3D",&arg0, "cc.Skeleton3D:addBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_addBone'", nullptr);
            return 0;
        }
        cobj->addBone(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:addBone",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_addBone'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_getBoneByName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skeleton3D_getBoneByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Skeleton3D:getBoneByName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_getBoneByName'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneByName(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneByName",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_getBoneByName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_getRootBone(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skeleton3D_getRootBone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Skeleton3D:getRootBone");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_getRootBone'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getRootBone(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getRootBone",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_getRootBone'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_getBoneByIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skeleton3D_getBoneByIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Skeleton3D:getBoneByIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_getBoneByIndex'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneByIndex(arg0);
        object_to_luaval<cocos2d::Bone3D>(tolua_S, "cc.Bone3D",(cocos2d::Bone3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneByIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_getBoneByIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skeleton3D_getBoneIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skeleton3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skeleton3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skeleton3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skeleton3D_getBoneIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Bone3D* arg0;

        ok &= luaval_to_object<cocos2d::Bone3D>(tolua_S, 2, "cc.Bone3D",&arg0, "cc.Skeleton3D:getBoneIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skeleton3D_getBoneIndex'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBoneIndex(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skeleton3D:getBoneIndex",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skeleton3D_getBoneIndex'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skybox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skybox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skybox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Skybox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Skybox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skybox:Skybox",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skybox_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Skybox_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Skybox* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Skybox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Skybox*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Skybox_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        std::string_view arg0;
        std::string_view arg1;
        std::string_view arg2;
        std::string_view arg3;
        std::string_view arg4;
        std::string_view arg5;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Skybox:init");

        ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.Skybox:init");

        ok &= luaval_to_std_string_view(tolua_S, 4,&arg2, "cc.Skybox:init");

        ok &= luaval_to_std_string_view(tolua_S, 5,&arg3, "cc.Skybox:init");

        ok &= luaval_to_std_string_view(tolua_S, 6,&arg4, "cc.Skybox:init");

        ok &= luaval_to_std_string_view(tolua_S, 7,&arg5, "cc.Skybox:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Skybox_init'", nullptr);
            return 0;
        }
        auto&& ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Skybox:init",argc, 6);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Skybox_init'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.MeshRenderer:setTexture");

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
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MeshRenderer:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MeshRenderer:setTexture",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_setTexture'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getMaterial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getMaterial'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMaterial();
        object_to_luaval<cocos2d::Material>(tolua_S, "cc.Material",(cocos2d::Material*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.MeshRenderer:getMaterial");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getMaterial'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMaterial(arg0);
        object_to_luaval<cocos2d::Material>(tolua_S, "cc.Material",(cocos2d::Material*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMaterial",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getMaterial'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getMeshes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getMeshes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getMeshes'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMeshes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMeshes",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getMeshes'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_setMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);
#if CC_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_setMaterial'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Material* arg0;
            ok &= luaval_to_object<cocos2d::Material>(tolua_S, 2, "cc.Material",&arg0, "cc.MeshRenderer:setMaterial");

            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.MeshRenderer:setMaterial");

            if (!ok) { break; }
            cobj->setMaterial(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Material* arg0;
            ok &= luaval_to_object<cocos2d::Material>(tolua_S, 2, "cc.Material",&arg0, "cc.MeshRenderer:setMaterial");

            if (!ok) { break; }
            cobj->setMaterial(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.MeshRenderer:setMaterial",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_setMaterial'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getMesh(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getMesh'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getMesh'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMesh();
        object_to_luaval<cocos2d::Mesh>(tolua_S, "cc.Mesh",(cocos2d::Mesh*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMesh",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getMesh'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getBlendFunc'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getBlendFunc",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.MeshRenderer:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:setBlendFunc",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getSkeleton(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getSkeleton'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getSkeleton'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getSkeleton();
        object_to_luaval<cocos2d::Skeleton3D>(tolua_S, "cc.Skeleton3D",(cocos2d::Skeleton3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getSkeleton",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getSkeleton'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_getMeshByName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRenderer* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::MeshRenderer*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_MeshRenderer_getMeshByName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string_view arg0;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MeshRenderer:getMeshByName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRenderer_getMeshByName'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getMeshByName(arg0);
        object_to_luaval<cocos2d::Mesh>(tolua_S, "cc.Mesh",(cocos2d::Mesh*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRenderer:getMeshByName",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_getMeshByName'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRenderer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MeshRenderer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MeshRenderer:create");
            if (!ok) { break; }
            cocos2d::MeshRenderer* ret = cocos2d::MeshRenderer::create(arg0);
            object_to_luaval<cocos2d::MeshRenderer>(tolua_S, "cc.MeshRenderer",(cocos2d::MeshRenderer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::MeshRenderer* ret = cocos2d::MeshRenderer::create();
            object_to_luaval<cocos2d::MeshRenderer>(tolua_S, "cc.MeshRenderer",(cocos2d::MeshRenderer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string_view arg0;
            ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.MeshRenderer:create");
            if (!ok) { break; }
            std::string_view arg1;
            ok &= luaval_to_std_string_view(tolua_S, 3,&arg1, "cc.MeshRenderer:create");
            if (!ok) { break; }
            cocos2d::MeshRenderer* ret = cocos2d::MeshRenderer::create(arg0, arg1);
            object_to_luaval<cocos2d::MeshRenderer>(tolua_S, "cc.MeshRenderer",(cocos2d::MeshRenderer*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.MeshRenderer:create",argc, 2);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRenderer_create'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_3d_MeshRendererCache_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::MeshRendererCache* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRendererCache_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::MeshRendererCache();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.MeshRendererCache");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.MeshRendererCache:MeshRendererCache",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRendererCache_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_MeshRendererCache_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MeshRendererCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRendererCache_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::MeshRendererCache::destroyInstance();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshRendererCache:destroyInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRendererCache_destroyInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_3d_MeshRendererCache_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.MeshRendererCache",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_MeshRendererCache_getInstance'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::MeshRendererCache::getInstance();
        object_to_luaval<cocos2d::MeshRendererCache>(tolua_S, "cc.MeshRendererCache",(cocos2d::MeshRendererCache*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.MeshRendererCache:getInstance",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_MeshRendererCache_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_cc_3d_Terrain_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Terrain();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Terrain");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:Terrain",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_getHeightData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_getHeightData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_getHeightData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getHeightData();
        ccvector_float_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getHeightData",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_getHeightData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_setDetailMap(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_setDetailMap'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        unsigned int arg0;
        cocos2d::Terrain::DetailMap arg1;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.Terrain:setDetailMap");

        #pragma warning NO CONVERSION TO NATIVE FOR DetailMap
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_setDetailMap'", nullptr);
            return 0;
        }
        cobj->setDetailMap(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setDetailMap",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_setDetailMap'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_setLightDir(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_setLightDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Terrain:setLightDir");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_setLightDir'", nullptr);
            return 0;
        }
        cobj->setLightDir(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:setLightDir",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_setLightDir'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_convertToTerrainSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_convertToTerrainSpace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.Terrain:convertToTerrainSpace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_convertToTerrainSpace'", nullptr);
            return 0;
        }
        auto&& ret = cobj->convertToTerrainSpace(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:convertToTerrainSpace",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_convertToTerrainSpace'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_initWithTerrainData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_initWithTerrainData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Terrain::TerrainData arg0;
        cocos2d::Terrain::CrackFixedType arg1;

        #pragma warning NO CONVERSION TO NATIVE FOR TerrainData
		ok = false;

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Terrain:initWithTerrainData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_initWithTerrainData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->initWithTerrainData(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:initWithTerrainData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_initWithTerrainData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_getTerrainSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_getTerrainSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_getTerrainSize'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getTerrainSize();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getTerrainSize",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_getTerrainSize'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Terrain_getNormal(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Terrain* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Terrain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Terrain*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Terrain_getNormal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Terrain:getNormal");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.Terrain:getNormal");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Terrain_getNormal'", nullptr);
            return 0;
        }
        auto&& ret = cobj->getNormal(arg0, arg1);
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Terrain:getNormal",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Terrain_getNormal'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Bundle3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Bundle3D();
        tolua_pushusertype(tolua_S,(void*)cobj,"cc.Bundle3D");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:Bundle3D",argc, 0);
    return 0;

#if CC_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_constructor'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_loadSkinData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Bundle3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Bundle3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Bundle3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Bundle3D_loadSkinData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        cocos2d::SkinData* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Bundle3D:loadSkinData");

        #pragma warning NO CONVERSION TO NATIVE FOR SkinData*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_loadSkinData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadSkinData(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:loadSkinData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_loadSkinData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_loadMaterials(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Bundle3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Bundle3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Bundle3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Bundle3D_loadMaterials'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::MaterialDatas arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_loadMaterials'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadMaterials(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:loadMaterials",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_loadMaterials'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_loadNodes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Bundle3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Bundle3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Bundle3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Bundle3D_loadNodes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NodeDatas arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_loadNodes'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadNodes(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:loadNodes",argc, 1);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_loadNodes'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_loadAnimationData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Bundle3D* cobj = nullptr;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if CC_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Bundle3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Bundle3D*)tolua_tousertype(tolua_S,1,0);

#if CC_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cc_3d_Bundle3D_loadAnimationData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string_view arg0;
        cocos2d::Animation3DData* arg1;

        ok &= luaval_to_std_string_view(tolua_S, 2,&arg0, "cc.Bundle3D:loadAnimationData");

        #pragma warning NO CONVERSION TO NATIVE FOR Animation3DData*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_loadAnimationData'", nullptr);
            return 0;
        }
        auto&& ret = cobj->loadAnimationData(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Bundle3D:loadAnimationData",argc, 2);
    return 0;

#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_loadAnimationData'.",&tolua_err);
#endif

    return 0;
}

int lua_cc_3d_Bundle3D_createBundle(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if CC_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if CC_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Bundle3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cc_3d_Bundle3D_createBundle'", nullptr);
            return 0;
        }
        auto&& ret = cocos2d::Bundle3D::createBundle();
        object_to_luaval<cocos2d::Bundle3D>(tolua_S, "cc.Bundle3D",(cocos2d::Bundle3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Bundle3D:createBundle",argc, 0);
    return 0;
#if CC_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cc_3d_Bundle3D_createBundle'.",&tolua_err);
#endif
    return 0;
}
